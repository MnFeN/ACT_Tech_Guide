// 这是一段 C# 中的 Roslyn 脚本代码，用于 Triggernometry 高级触发器。

using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text.RegularExpressions;
using Triggernometry;
using static System.Math;

public struct Info
{
    public const string Name = "AdvWm";
    public const string FullName = "高级标点工具箱 AdvWm";
    public const string Version = "${env:version}";
    public const string Author = "阿洛 MnFeN";
    public static string Description = $"{FullName} v{Version} by {Author}";
}

RealPlugin.plug.RegisterNamedCallback("AdvWm", new Action<object, string>(AdvWm.NamedCallback), null, registrant: Info.Description);

public class AdvWm
{
    /// <summary> All keys are in lowercase. </summary>
    Dictionary<string, string> _argsDict;
    string _action = "";
    bool _log = true;
    bool _local = true;
    public static void Log(string message) => RealPlugin.plug.InvokeNamedCallback("command", $"/e {message}");

    public static void NamedCallback(object _, string input)
    {
        var commands = input.Split(new string[] { "---" }, StringSplitOptions.None);
        foreach (var command in commands)
        {
            var advwm = new AdvWm();
            advwm.Execute(command);
        }
    }

    static readonly HashSet<string> postNamazuWaymarkKeywords = new HashSet<string> {
        "save", "backup", "load", "restore", "reset", "clear", "public"
    };

    private void Execute(string command)
    {
        string simpleCmd = command.ToLower().Trim();
        if (postNamazuWaymarkKeywords.Contains(simpleCmd))
        {
            RealPlugin.plug.InvokeNamedCallback("place", simpleCmd);
            return;
        }
        
        _argsDict = command.Split('\n')
            .Where(line => line.Contains(":") && !line.StartsWith("//"))
            .ToDictionary(
                line => line.Substring(0, line.IndexOf(':')).Trim().ToLower(),
                line => line.Substring(line.IndexOf(':') + 1).Trim()
            );
        // 解析共通参数
        TryGetArg("Action", out _action);
        _log = !TryGetArg("Log", out string log) || bool.Parse(log.ToLower());
        _local = !TryGetArg("Local", "LocalOnly", out string local) || bool.Parse(local.ToLower());

        Waymarks waymarks;
        switch (_action.ToLower())
        {
            case "getversion":
                Interpreter.StaticHelpers.SetScalarVariable(isPersistent: false, $"{Info.Name}_version", Info.Version);
                return;
            case "initmessage":
                Log($"已加载：{Info.Description}");
                return;
            case "polar": // 不推荐使用，仅为兼容旧版本
                waymarks = ParseWaymarksPolar(); break;
            case "circle":
                waymarks = ParseWaymarksCircle(); break;
            case "arc":
                waymarks = ParseWaymarksArc(); break;
            case "linear":
            case "connect":
            case "linearconnect":
                waymarks = ParseWaymarksLinearConnect(); break;
            // case "absolute":  case "relative":  case "place": 旧版本的指令全部整合为默认的标点模式
            default:
                waymarks = ParseWaymarksDefault(); break;
        }
        // Log($"初始：\n{waymarks}");
        TryApplyScales(waymarks);
        // Log($"伸缩：\n{waymarks}");
        TryApplyRotation(waymarks);
        // Log($"旋转：\n{waymarks}");
        TryApplyCenter(waymarks);
        // Log($"平移：\n{waymarks}");
        waymarks.LocalOnly = _local;
        waymarks.Log = _log;
        waymarks.Mark();
    }

    /// <summary>
    /// 提供所有坐标进行标点的模式：<br />
    /// 将相对坐标 x y z 根据给定的中心、伸缩尺度、旋转角度线性变换
    /// 先伸缩，再旋转，最后平移到中心。
    /// </summary>
    /// <returns>经过所有变换后的一组标点。</returns>
    private Waymarks ParseWaymarksDefault()
    {
        Waymarks waymarks = new Waymarks();
        foreach (string name in Waymark.WaymarkNames)  // a b c d 1 2 3 4
        {
            if (TryGetArg(name, out string rawCoord))
            {
                waymarks.Add(Waymark.Parse(name, rawCoord));
            }
        }
        return waymarks;
    }

    /// <summary>
    /// 极坐标（柱坐标）模式：<br />
    /// 将 r θ z 伸缩旋转后，转换为 x y z 并平移至给定的中心。
    /// </summary>
    private Waymarks ParseWaymarksPolar()
    {
        Waymarks waymarks = new Waymarks();
        foreach (string name in Waymark.WaymarkNames)  // a b c d 1 2 3 4
        {
            if (TryGetArg(name, out string rawPolarCoord))
            {   // 已重构为接近正常方法的处理逻辑
                XIVCoord polarCoord = XIVCoord.ParseRawData(rawPolarCoord.StartsWith("polar ") ? rawPolarCoord : $"polar {rawPolarCoord}");
                waymarks.Add(new Waymark(name, polarCoord.ToCartesian()));
            }
        }
        return waymarks;
    }

    private Waymarks ParseWaymarksCircle()
    {
        Waymarks waymarks = new Waymarks();
        double rCardinal = MathParser.Parse(GetArg("R"));
        double rIntercard = TryGetArg("R2", out string rawR2) ? MathParser.Parse(rawR2) : rCardinal;
        string[] usedWaymarkNames = GetArg("Waymarks").Select(c => char.ToLower(c).ToString()).ToArray(); // 用哪些点 相对正北逆时针 如 A4D3C2B1
        double step = 2 * PI / usedWaymarkNames.Length; // 相邻标点的角度差
        int count = 0;
        foreach (string name in usedWaymarkNames)  // a b c d 1 2 3 4
        {
            if (Waymark.WaymarkNames.Contains(name))
            {
                var r = (count & 1) == 0 ? rCardinal : rIntercard;
                var θ = count * step - PI;
                waymarks.Add(new Waymark(name, new PolarCoord(r, θ, 0)));
            }
            count++;
        }
        return waymarks;
    }

    private Waymarks ParseWaymarksArc()
    {
        Waymarks waymarks = new Waymarks();
        double r = MathParser.Parse(GetArg("R"));   // 半径
        string[] usedWaymarkNames = GetArg("Waymarks").Select(c => char.ToLower(c).ToString()).ToArray(); // 用哪些点 相对正北逆时针 如 A4D3C2B1
        int stepCount = usedWaymarkNames.Length - 1;

        // 圆弧的圆心角，不提供的时候默认为使标点紧邻的角度（弧长约 2.6）
        double dθ = TryGetArg("dθ", "dTheta", out string rawdθ) ? MathParser.Parse(rawdθ) : (stepCount >= 1) ? 2.6 / r * stepCount : 0;
        double θStep = (stepCount >= 1) ? dθ / stepCount : 0; // 相邻标点的角度差
        int count = 0;
        foreach (string name in usedWaymarkNames)  // a b c d 1 2 3 4
        {
            if (Waymark.WaymarkNames.Contains(name)) // 允许使用非标点名的字符占位等分点，不会生成标点
            {
                PolarCoord polarCoord = new PolarCoord(r, (count - stepCount / 2.0) * θStep - PI, 0);
                waymarks.Add(new Waymark(name, polarCoord));
            }
            count++;
        }
        return waymarks;
    }

    private Waymarks ParseWaymarksLinearConnect()
    {
        Waymarks waymarks = new Waymarks();
        string[] usedWaymarkNames = GetArg("Waymarks").Select(c => char.ToLower(c).ToString()).ToArray(); // 用哪些点 起点到终点 如 A4D3C2B1
        if (usedWaymarkNames.Length < 2)
        {
            throw new Exception("AdvWm: LinearConnect 模式下，提供的标点数量不足 2");
        }
        XIVCoord startCoord = XIVCoord.ParseRawData(GetArg("start"));
        XIVCoord endCoord = XIVCoord.ParseRawData(GetArg("end"));
        XIVCoord vector = endCoord - startCoord;
        double totalDistance = vector.Length;
        // Log($"{vector}");
        int count = 0;
        foreach (string name in usedWaymarkNames)  // A B C D 1 2 3 4
        {
            if (Waymark.WaymarkNames.Contains(name))
            {
                double percentage = (double)count / (usedWaymarkNames.Length - 1);  // 标点默认等分
                if (TryGetArg(name, out string rawDistance))   // 也可以不等分，自定义标点位置
                {
                    if (rawDistance.EndsWith(" m"))      // 以 A: 5 m 形式提供的距离
                    {
                        // @d 代表总长度，如 A: @d - 5 m 意为终点前 5 m
                        string strTotalDistance = totalDistance.ToString(MathParser.CultureInfo);
                        rawDistance = rawDistance.Replace("@d", strTotalDistance);
                        double distance = MathParser.Parse(rawDistance.Substring(0, rawDistance.Length - 2));
                        // 如果起点终点过近导致给定距离超过总长度，则采用默认距离
                        percentage = distance > totalDistance ? percentage : distance / totalDistance;
                    }
                    else                                // 以 A: 0.125 形式提供的百分比
                    {
                        percentage = MathParser.Parse(rawDistance);
                    }
                }

                XIVCoord coord = startCoord + percentage * vector;
                waymarks.Add(new Waymark(name, coord));
            }
            count++;
        }
        return waymarks;
    }

    /// <summary> 如果当前指令提供了任何伸缩，将伸缩变换应用到给定的一组标点坐标。 </summary>
    /// <returns></returns>
    private void TryApplyScales(Waymarks waymarks)
    {
        // 首先尝试解析 Scale 和具体的 ScaleX, ScaleY, ScaleZ 参数
        bool hasScale  = TryGetArg("Scale",  out string rawScale);
        bool hasScaleX = TryGetArg("ScaleX", out string rawScaleX);
        bool hasScaleY = TryGetArg("ScaleY", out string rawScaleY);
        bool hasScaleZ = TryGetArg("ScaleZ", out string rawScaleZ);

        // 未给定参数则免去解析直接返回
        if (!hasScale && !hasScaleX && !hasScaleY && !hasScaleZ) return;

        // 如果存在 scale 参数，按照 scaleX ?? scale ?? 1 的优先级解析
        double defaultScale = hasScale ? MathParser.Parse(rawScale) : 1;

        double scaleX = hasScaleX ? MathParser.Parse(rawScaleX) : defaultScale;
        double scaleY = hasScaleY ? MathParser.Parse(rawScaleY) : defaultScale;
        double scaleZ = hasScaleZ ? MathParser.Parse(rawScaleZ) : defaultScale;

        // 如果任一缩放倍率不是 1，则缩放
        if (Abs(scaleX - 1) > 1e-5 || Abs(scaleY - 1) > 1e-5 || Abs(scaleZ - 1) > 1e-5)
        {
            foreach (Waymark wm in waymarks)
            {
                wm.Coord = wm.Coord.ScaleBy(scaleX, scaleY, scaleZ);
            }
        }
    }

    /// <summary> 如果当前指令提供了旋转，将伸缩变换应用到给定的一组标点坐标。 </summary>
    /// <returns></returns>
    private void TryApplyRotation(Waymarks waymarks)
    {
        if (TryGetArg("θ", "Theta", out string rawθ))
        {
            double θ = MathParser.Parse(rawθ);
            foreach (Waymark wm in waymarks)
            {
                wm.Coord = wm.Coord.RotateTo(θ);
            }
        }
    }

    /// <summary> 如果当前指令提供了场地中心，将场地中心应用到给定的一组标点坐标。 </summary>
    void TryApplyCenter(Waymarks waymarks)
    {
        if (TryGetArg("O", "Center", out string rawCenter))
        {
            XIVCoord centerCoord = XIVCoord.ParseRawData(rawCenter);
            foreach (Waymark wm in waymarks)
            {
                wm.Coord = wm.Coord.MoveTo(centerCoord);
            }
        }
    }

    string GetArg(params string[] keys)
    {
        string key = keys.Select(k => k.ToLower()).FirstOrDefault(k => _argsDict.ContainsKey(k)) 
            ?? throw new ArgumentException($"AdvWm: 未提供指定的必需参数 {string.Join(" / ", keys)}。");
        return _argsDict[key];
    }

    bool TryGetArg(string key, out string value)
    {
        key = key.ToLower();
        return _argsDict.TryGetValue(key, out value);
    }

    bool TryGetArg(string key, string alternativeKey, out string value)
    {
        if (TryGetArg(key, out value))
        {
            return true;
        }
        return TryGetArg(alternativeKey, out value);
    }
}

#region XIVCoord

public abstract class XIVCoord
{
    //public abstract XIVCoord Copy();

    /// <summary>
    /// 将初始坐标视为相对坐标。<br/>
    /// 将相对坐标系的正北（θ = ±pi）在平面内旋转至给定方向 <paramref name="θ"/>。<br/><br/>
    /// 方向角度 <paramref name="θ"/> 为游戏内标准，如：<br/>
    /// · 正北（不旋转）= ±pi；<br/>
    /// · 正南（旋转 180 度）= 0；<br/>
    /// · 正东（顺时针旋转 90 度）= pi/2。
    /// </summary>
    /// <param name="theta">将初始相对坐标系的正北（-pi）旋转到的方向角度。</param>
    public abstract XIVCoord RotateTo(double θ);
    public abstract XIVCoord MoveTo(double dx, double dy, double dz);
    public XIVCoord MoveTo(XIVCoord center) => this + center;
    public abstract XIVCoord ScaleBy(double scaleX, double scaleY, double scaleZ);
    public abstract CartesianCoord ToCartesian();
    public abstract PolarCoord ToPolar();
    public abstract double Length { get; }
    public abstract string Jsonify();
    public abstract override string ToString();

    public static CartesianCoord operator +(XIVCoord a, XIVCoord b)
    {
        CartesianCoord cartesianA = a.ToCartesian();
        CartesianCoord cartesianB = b.ToCartesian();

        return new CartesianCoord(
            cartesianA.X + cartesianB.X,
            cartesianA.Y + cartesianB.Y,
            cartesianA.Z + cartesianB.Z);
    }

    public static CartesianCoord operator -(XIVCoord a, XIVCoord b)
    {
        CartesianCoord cartesianA = a.ToCartesian();
        CartesianCoord cartesianB = b.ToCartesian();

        return new CartesianCoord(
            cartesianA.X - cartesianB.X,
            cartesianA.Y - cartesianB.Y,
            cartesianA.Z - cartesianB.Z);
    }

    public static XIVCoord operator -(XIVCoord a)
    {
        if (a is CartesianCoord cartesianA)
        {
            return new CartesianCoord(-cartesianA.X, -cartesianA.Y, -cartesianA.Z);
        }
        else
        {
            PolarCoord polarA = (PolarCoord)a; 
            return new PolarCoord(polarA.R, polarA.θ + PI, polarA.Z);
        }
    }

    public static XIVCoord operator *(XIVCoord a, double n)
    {
        if (a is CartesianCoord cartesianA)
        {
            return new CartesianCoord(cartesianA.X * n, cartesianA.Y * n, cartesianA.Z * n);
        }
        else
        {
            PolarCoord polarA = (PolarCoord)a;
            return new PolarCoord(polarA.R * n, polarA.θ, polarA.Z);
        }
    }

    public static XIVCoord operator *(double n, XIVCoord a) => a * n;

    public static XIVCoord operator /(XIVCoord a, double n) => a * (1.0 / n);

    private static Regex rexOpKeywords = new Regex(@"\b(plus|minus|polar|minuspolar)\b", RegexOptions.IgnoreCase | RegexOptions.Compiled);

    /// <summary>
    /// 将一串直角坐标、极坐标、或混合方式指定的坐标解析并叠加，如：<br /><br />
    /// <paramref name="A"/>: 10, -10, 0 <br />
    /// <paramref name="A"/>: <paramref name="polar"/> 20, -45°, 0<br />
    /// <paramref name="A"/>: 10, -10, 0 <paramref name="polar"/> 20, -45°（在直角坐标基础上叠加极坐标结果）<br /><br />
    /// 字符串格式详见 <paramref name="rawCoords"/>。
    /// </summary>
    /// <param name="rawCoords">
    /// 一串坐标字符串，可包含多组坐标。<br />
    /// 每组坐标之间以关键字连接，坐标分量之间以逗号连接。如：<br /><br />
    /// <paramref name="A"/>:     x, y, z  
    /// <paramref name="plus"/>   x2, y2  
    /// <paramref name="minus"/>  x3, y3, z3  
    /// <paramref name="polar"/>  r1, θ1
    /// <paramref name="minuspolar"/> r2, θ2, z2<br />
    /// </param>
    public static XIVCoord ParseRawData(string rawCoords)
    {
        // 例：x, y, z plus x2, y2 minus x3, y3, z3 polar r1, θ1 minuspolar r2, θ2, z2

        List<string> parts = new List<string>();
        string currentPart = "";
        int depth = 0;
        foreach (char c in rawCoords)
        {
            switch (c)
            {
                case ',':
                    if (depth == 0)
                    {
                        parts.Add(currentPart);
                        currentPart = "";
                        continue;
                    }
                    break;
                case '(': depth++; break;
                case ')': depth--; break;
            }
            currentPart += c;
        }
        parts.Add(currentPart);
        
        if (depth != 0)
        {
            throw new Exception($"AdvWm: 标点参数存在 {Abs(depth)} 个未闭合的{(depth > 0 ? "左" : "右")}括号。表达式：{rawCoords}");
        }

        // 此时：[x] [y] [z plus x2] [y2 minus x3] [y3] [z3 polar r] [θ] [z]

        List<XIVCoord> coords = new List<XIVCoord>();
        bool isCurrentPolar = false;
        bool isCurrentPlus = true;
        List<string> currentParams = new List<string>();

        foreach (string part in parts)
        {
            string[] splitParts = rexOpKeywords.Split(part);

            if (splitParts.Length == 3) // 找到操作符，拆分解析
            {
                string beforeOp = splitParts[0].Trim();
                string operation = splitParts[1].Trim();
                string afterOp = splitParts[2].Trim();

                // 处理前部分
                if (currentParams.Count != 0 || !string.IsNullOrEmpty(beforeOp)) // 不是形如 "polar ..." 的字符串开始位置
                {
                    currentParams.Add(beforeOp);
                    XIVCoord coord = isCurrentPolar
                        ? (XIVCoord)PolarCoord.Parse(currentParams.ToArray())
                        : (XIVCoord)CartesianCoord.Parse(currentParams.ToArray());
                    coords.Add(isCurrentPlus ? coord : -coord);
                    currentParams.Clear();
                }

                // 处理操作符：是否是加法/极坐标操作
                isCurrentPlus = !operation.StartsWith("minus");
                isCurrentPolar = operation.EndsWith("polar");

                // 处理后部分
                currentParams.Add(afterOp);
            }
            else if (splitParts.Length == 1) // 未找到操作符，直接添加
            {
                currentParams.Add(splitParts[0].Trim());
            }
            else // 偷个懒，坐标最少两个参数，而只要有两个就会被逗号预先拆分，所以正常不会出现 1 3 以外的情况
            { 
                throw new Exception($"AdvWm: 标点参数解析时，关键字之间参数过少。\n表达式：{rawCoords}；\n出错位置：{part}");
            }
        }
        XIVCoord finalCoord = isCurrentPolar 
            ? (XIVCoord)PolarCoord.Parse(currentParams.ToArray()) 
            : (XIVCoord)CartesianCoord.Parse(currentParams.ToArray());
        coords.Add(isCurrentPlus ? finalCoord : -finalCoord);

        // 此时：[Cartesian1] [Cartesian2] [Cartesian3] [Polar1]
        return coords.Aggregate((c1, c2) => c1 + c2);
    }

}

public class CartesianCoord : XIVCoord
{
    public double X;
    public double Y;
    public double Z;

    public string X_3 => X.ToString("0.###", System.Globalization.CultureInfo.InvariantCulture);
    public string Y_3 => Y.ToString("0.###", System.Globalization.CultureInfo.InvariantCulture);
    public string Z_3 => Z.ToString("0.###", System.Globalization.CultureInfo.InvariantCulture);

    public CartesianCoord(double x, double y, double z)
    {
        X = x; Y = y; Z = z;
    }

    public override XIVCoord RotateTo(double θ)
    {
        var sin = Sin(θ);
        var cos = Cos(θ);
        (X, Y) = (-X * cos - Y * sin, X * sin - Y * cos);
        return this;
    }

    public override XIVCoord MoveTo(double dx, double dy, double dz)
    {
        X += dx;
        Y += dy;
        Z += dz;
        return this;
    }

    public override XIVCoord ScaleBy(double scaleX, double scaleY, double scaleZ)
    {
        X *= scaleX;
        Y *= scaleY;
        Z *= scaleZ;
        return this;
    }

    public override CartesianCoord ToCartesian() => new CartesianCoord(X, Y, Z);

    public override PolarCoord ToPolar()
    {
        double r = Sqrt(X * X + Y * Y);
        double θ = Atan2(X, Y);
        return new PolarCoord(r, θ, Z);
    }

    public override double Length => Sqrt(X * X + Y * Y + Z * Z);

    public override string ToString() => $"({X_3}, {Y_3}, {Z_3})";

    public override string Jsonify() => $"\"X\": {X_3}, \"Z\": {Y_3}, \"Y\": {Z_3}, \"Active\": true";

    public static CartesianCoord Parse(params string[] coords)
    {
        switch (coords.Length)
        {
            case 2:
                return ParseCoordsString(coords[0], coords[1]);
            case 3:
                return ParseCoordsString(coords[0], coords[1], coords[2]);
            default:
                throw Context.ArgCountError("CartesianCoord: 坐标构造函数", "2-3", coords.Length, "[" + string.Join("], [", coords) + "]");
        }
    }

    private static CartesianCoord ParseCoordsString(string rawX, string rawY, string rawZ = null)
    {
        try
        {
            return new CartesianCoord(
                MathParser.Parse(rawX), 
                MathParser.Parse(rawY), 
                rawZ == null ? 0 : MathParser.Parse(rawZ));
        }
        catch (Exception ex)
        {
            throw new ArgumentException($"AdvWm: 直角坐标解析错误：{ex.Message}\n" +
                $"原始数据：\nx = ({rawX}), \ny = ({rawY}), \nz = ({rawZ ?? "null"})");
        }
    }
}

public class PolarCoord : XIVCoord
{
    public double R;
    public double θ;
    public double Z;

    public PolarCoord(double r, double θ, double z)
    {
        R = r; this.θ = θ; Z = z;
    }

    public override XIVCoord RotateTo(double θ)
    {
        this.θ += θ + PI;
        return this;
    }

    public override XIVCoord MoveTo(double dx, double dy, double dz)
        => ToCartesian().MoveTo(dx, dy, dz);

    public override XIVCoord ScaleBy(double scaleX, double scaleY, double scaleZ)
    {
        if (Abs(scaleX - scaleY) < 1e-5 && scaleX >= 1e-4)
        { 
            R *= scaleX;
            Z *= scaleZ;
            return this;
        }
        else return ToCartesian().ScaleBy(scaleX, scaleY, scaleZ);
    }

    public override CartesianCoord ToCartesian()
    {
        double x = R * Sin(θ);
        double y = R * Cos(θ);
        return new CartesianCoord(x, y, Z);
    }

    public override PolarCoord ToPolar() => new PolarCoord(R, θ, Z);

    public override double Length => Sqrt(R * R + Z * Z);

    public override string ToString() => $"(R={R}, θ={θ}, Z={Z})";

    public override string Jsonify() => ToCartesian().Jsonify();

    public static PolarCoord Parse(params string[] coords)
    {
        switch (coords.Length)
        {
            case 2:
                return ParsePolarCoordsString(coords[0], coords[1]);
            case 3:
                return ParsePolarCoordsString(coords[0], coords[1], coords[2]);
            default:
                throw Context.ArgCountError("AdvWm: 极坐标构造函数", "2-3", coords.Length, "[" + string.Join("], [", coords) + "]");
        }
    }

    private static PolarCoord ParsePolarCoordsString(string rawR, string rawθ, string rawZ = null)
    {
        try
        {
            return new PolarCoord(
                MathParser.Parse(rawR), 
                MathParser.Parse(rawθ), 
                rawZ == null ? 0 : MathParser.Parse(rawZ));
        }
        catch (Exception ex)
        {
            throw new ArgumentException($"AdvWm: 极坐标解析错误：{ex.Message}\n\n" +
                $"原始数据：\nr = ({rawR}), \nθ = ({rawθ}), \nz = ({rawZ})");
        }
    }

}

#endregion XIVCoord

#region Waymark(s)

public enum WaymarkType { A, B, C, D, One, Two, Three, Four }
public class Waymark
{
    public WaymarkType Type { get; set; }
    public XIVCoord Coord { get; set; }
    public bool Ignore { get; set; }
    public bool Active { get; set; }

    /// <summary>
    /// 用于遍历时保证输出顺序
    /// </summary>
    public static readonly string[] WaymarkNames = new string[] { "a", "b", "c", "d", "1", "2", "3", "4" };
    public static readonly WaymarkType[] WaymarkTypes = new WaymarkType[]
    {
        WaymarkType.A, WaymarkType.B, WaymarkType.C, WaymarkType.D,
        WaymarkType.One, WaymarkType.Two, WaymarkType.Three, WaymarkType.Four
    };

    /// <summary>
    /// 从用户输入的标点类型转化为实际 Type
    /// </summary>
    public static readonly Dictionary<string, WaymarkType> TypeMap = Enumerable.Range(0, 8)
        .ToDictionary(i => WaymarkNames[i], i => WaymarkTypes[i]);

    public Waymark(WaymarkType type, XIVCoord coord = null, bool ignore = false)
    {
        Type = type;
        Coord = coord ?? new CartesianCoord(0, 0, 0);
        Active = coord != null;
        Ignore = ignore;
    }

    public Waymark(string rawType, XIVCoord coord = null, bool ignore = false)
    {
        if (TypeMap.TryGetValue(rawType, out var mappedType))
        {
            Type = mappedType;
        }
        else
        {
            throw new Exception($"AdvWm: {rawType} 不是合法的标点名之一（A B C D 1 2 3 4）。");
        }
        Coord = coord ?? new CartesianCoord(0, 0, 0);
        Active = coord != null;
        Ignore = ignore;
    }

    public static Waymark Parse(string rawType, string rawCoord, bool ignore = false)
    {
        Waymark wm = new Waymark(rawType, null, ignore);

        switch (rawCoord.Trim().ToLower())
        {
            // 清除标点
            case "clear":
                wm.Active = false;
                wm.Coord = new CartesianCoord(0, 0, 0);
                break;
            // 变相地“清除”标点  不会有淡入淡出动画
            case "fakeclear":
                wm.Active = true;
                wm.Coord = new CartesianCoord(0, 0, 1000);
                break;
            default:
                wm.Active = true;
                wm.Coord = XIVCoord.ParseRawData(rawCoord);
                break;
        }

        return wm;
    }

    public string Jsonify() // 脚本调用不了 Json 的方法。。？
    {
        if (Ignore)
            return "";
        if (Active)
            return $"\"{Type}\": {{ {Coord.Jsonify()}, \"Active\": true }}";
        else
            return $"\"{Type}\": {{}}";
    }

    public override string ToString() => Jsonify();
}

public sealed class Waymarks : IEnumerable<Waymark>
{
    private readonly Dictionary<WaymarkType, Waymark> _waymarks;
    public bool Log = true;
    public bool LocalOnly = true;

    public Waymarks()
    {
        _waymarks = new Dictionary<WaymarkType, Waymark>();
        foreach (var type in Waymark.WaymarkTypes)
        {
            _waymarks[type] = new Waymark(type, ignore: true);
        }
    }

    public Waymark this[WaymarkType type]
    {
        get => _waymarks[type];
        set => _waymarks[type] = value;
    }

    IEnumerator IEnumerable.GetEnumerator() => GetEnumerator();
    public IEnumerator<Waymark> GetEnumerator()
    {
        foreach (var type in Waymark.WaymarkTypes)
        {
            if (_waymarks.TryGetValue(type, out Waymark waymark))
            {
                yield return waymark;
            }
        }
    }

    public void Add(Waymark wm)
    {
        if (wm == null || wm.Ignore) return;
        else _waymarks[wm.Type] = wm;
    }

    public string Jsonify()
    {
        var jsonList = _waymarks.Values.Where(wm => wm?.Ignore == false)
            .Select(wm => "    " + wm.Jsonify()).ToList();
        if (!Log) 
            jsonList.Add($"    \"Log\": false");
        if (!LocalOnly) 
            jsonList.Add($"    \"LocalOnly\": false");
        string data = string.Join(",\n", jsonList);
        return $"{{\n{string.Join(",\n", jsonList)}\n}}";
    }
    public override string ToString() => Jsonify();

    public void Mark()
    {
        RealPlugin.plug.InvokeNamedCallback("place", this.Jsonify());
        //RealPlugin.plug.InvokeNamedCallback("command", $"/e {this}");
    }
}

#endregion Waymark(s)

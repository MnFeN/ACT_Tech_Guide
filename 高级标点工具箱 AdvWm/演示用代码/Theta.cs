using System;
using System.Drawing;
using System.Windows.Forms;
using static Triggernometry.RealPlugin;

public class ScaleForm : Form
{
    private TrackBar θTrackBar;
    private Label θLabel;

    public ScaleForm()
    {
        this.Text = "方向角 θ 的变化";
        this.Font = new Font("等距更纱黑体 SC", 11F, FontStyle.Regular, GraphicsUnit.Point, 0);
        this.Padding = new Padding(10);
        InitializeComponents();
    }

    private void InitializeComponents()
    {
        θTrackBar = new TrackBar();

        θTrackBar.Minimum = -100;
        θTrackBar.Maximum = 100;
        θTrackBar.TickStyle = TickStyle.Both;
        θTrackBar.TickFrequency = 25;
        θTrackBar.SmallChange = 5;
        θTrackBar.LargeChange = 100;
        θTrackBar.ValueChanged += TrackBar_ValueChanged;

        θLabel = new Label { Text = "θ: 0", Dock = DockStyle.Top };

        this.Controls.Add(θTrackBar);
        this.Controls.Add(θLabel);

        θTrackBar.Dock = DockStyle.Top;

        θTrackBar.Margin = new Padding(10, 50, 10, 50);
    }

    private void TrackBar_ValueChanged(object sender, EventArgs e)
    {
        θLabel.SuspendLayout(); 
        double ratio = θTrackBar.Value / 100.0;
        int dir8 = (int)Math.Round(ratio * 4 + 4) % 8;
        string dir8Str = new[] { "上北", "左上", "左西", "左下", "下南", "右下", "右东", "右上" }[dir8];
        θLabel.Text = $"θ: {ratio:F1}π （{dir8Str}）";
        var cmd = $@"
           Center: 100, 100, 0
           θ: {ratio * Math.PI}
           A: polar 10,  -180°
           1: polar 5.5, -150°
           D: polar 5,   -90°
           4: polar 5,   -45°
           C: polar 5,    0°
           3: polar 5,    45°
           B: polar 5,    90°
           2: polar 5.5,  150°
        ";
        θLabel.ResumeLayout();
        plug.InvokeNamedCallback("AdvWm", cmd);
    }
}

plug.ui.Invoke(() => new ScaleForm().Show());

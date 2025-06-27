开发中，以下内容可能会修改

- 全部指令共用：
  - 延迟执行秒数（固定异步执行，即使动作设置为同步也会异步执行）：
    - Delay: 1

- 创建
  - 指定创建：（可省略，根据指定特效自动判断）
    - Action: Create 
  - 指定特效（二选一）（目前只支持以下两种）
    - Omen: general02f
    - StaticVfx: vfx/.../general02f.avfx (完整路径)
  - 指定标签
    - Tag: 自定义的名字
  - 缩放（二选一）
    - Scale: 如 5, 10，主要用于不需要高度上缩放的平面特效
      - 提供三个参数 a, b, c 时：x = a, y = b, z = c
      - 提供两个参数 a, b 时：x = a, y = b, z = 1
      - 提供一个参数 a 时：x = a, y = a, z = 1
    - ScaleCyl: 如 5, 1，主要用于立体特效的缩放（圆柱对称性）
      - 提供三个参数 a, b, c 时：同上
      - 提供两个参数 a, b 时：x = a, y = a, z = b
      - 提供一个参数 a 时：x = a, y = a, z = a
  - 颜色：
    - Color: 0.5, 0.3, 0.2, 0.1
    不提供此项或某个参数时，相应值默认为 1
  - 持续时间（秒数，主动销毁）：
    - t: 1 

  - 相对位置：
    - Pos: 坐标格式同 AdvWm
  - 相对角度（二选一）：
    - Angle: π/2
    - Angle3D: π/2, 0, 0 （沿 z x y 轴的转向）
  - 坐标系中心：
    - O/Center: 同 AdvWm
  - 坐标系角度：
    - θ/Theta：同 AdvWm
  - 是否翻转
    - +X: 1/true 或 0/false （默认 true，x 轴不翻转）
    - +Y: 同上
    相当于 ScaleX/Y = ±1  
    由于特效无法沿任意方向缩放所以只能选择是否翻转

- 更改：
  - 指定更改：
    - Action: Change/Modify 
  - 指定更改类型：
    - Type: Static/StaticVfx 或 Actor/ActorVfx  
    不指定时默认 Static  
    暂不支持 Actor  
  - 指定更改的特效：
    - Tag：完整名字，不分大小写
    - Regex：正则匹配  
    不指定时默认修改全部  
  - 其它参数
    同 Create，其中几何参数未指定时使用上次的值，如可以单独自身中心，以应用之前的坐标系参数线性变换

- 删除：
  - 指定删除：
    - Action: Remove 
  - 指定更改类型：
    - Type: Static/StaticVfx 或 Actor/ActorVfx  
    不指定时默认二者均删除
  - 指定更改的特效：
    Tag/Regex 同上

- 三角剖分
  - 指定动作类型：
    - Action: Triangulate/△
  - 顶点集合（依次相连，顺序任意，相当于创建模式下的 Pos）：
    - Points: x1, y1; x2, y2; ...; xn, yn
  - 其余参数：
    - 标签、颜色、持续时间：同创建模式
    - 坐标系中心（O/Center）、坐标系角度（θ/Theta）、坐标系翻转（+X, +Y）：同创建模式
    - 注意：不建议指定 缩放（Scale）、自身位置（Pos）、自身角度（Angle）

- 多条指令以单独一行的 `---` 分割，依次执行

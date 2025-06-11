- 创建
  - 指定特效（二选一）
    - Omen: general02f
    - StaticVfx: vfx/.../general02f.avfx (完整路径)
  - 指定标签
    - Tag: 自定义的名字
  - 缩放
    - Scale: 5, 5, 1  (yz 可省略，默认 y = x, z = 1)
  - 颜色：
    - Color: 0.5, 0.3, 0.2, 0.1
    不提供此项或某个参数时，相应值默认为 1

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
    同 Create

- 删除：
  - 指定删除：
    - Action: Remove 
  - 指定更改类型：
    - Type: Static/StaticVfx 或 Actor/ActorVfx  
    不指定时默认二者均删除
  - 指定更改的特效：
    Tag/Regex 同上

# NoOneSurvival
#### C++ final project  based on cocos2d-x


### 一、需求分析
游戏类型: 2D 塔防类游戏

游戏玩法: 玩家建造炮塔防止敌人到达终点。消灭敌人获得金币，建造更多或更高级的塔。

#### 1、游戏流程分析
总场景包括: 开始场景，选关场景，游戏主场景，胜利场景，失败场景。

#### 2、游戏主场景设计 
游戏主场景的界面与功能如下图所示:

(1)怪物: 三种血量不同、移动速度的不同敌人，一波一波的出现，消灭敌人可获得相应金币; 

(2)塔: 三种攻击速度、攻击力、攻击效果、价值不同的塔，由获得的金币建造;塔会自 动攻击最近的敌人，同时可以升级，变卖。

(3)子弹: 三种不同的子弹对应三种塔，有不同的伤害，速度。

(4)地图: 瓦片地图

#### 3、数据管理 
(1)采用单例模式设计。设计一个类，整个游戏只含唯一实例和唯一接口，存储所有游戏状态，并可以在任意处调用接口读取写入数据;

(2) 游戏关卡数据(敌人波数、出现顺序、背景图片......)储存在 plist 文件中，设计接口读入;

(3)玩家历史数据(成就、星级等)储存在 UserDefault 中。



### 二、工程架构分析
项目主要部分包含: 场景，数据管理及其相关接口和其他一些设计。

场景分为游戏主场景与完善部分:
#### 1、主场景(GamePlayerLayer)
进行游戏的界面，游戏中的塔，敌人，子弹都基于此场景。游戏逻辑以及触控都是在此层中实现的。

游戏地图:采用瓦片地图，瓦片地图分为前景图层与对象层。前景为敌人表示进攻路 线的图层，对象层储存了敌人将行进的点，地图相关信息在主场景初始化时被载入与分析储 存。

游戏逻辑实现:包括碰撞检测(敌人和子弹)，按波产生敌人，逐帧坚持是否有敌人到达终点并扣血，判断是否胜利等。

信息层:工具栏形式，展示当前关卡的玩家血量，金钱。还包含音乐开关与返回按键。

#### 2、具体实例 
塔(Tower): 设计了三种实例派生类(AttackTower，ColdTower，MultiDirTower),都继承至塔基类，并拥有不同的射击方式(如多方向攻击，炮口旋转等)，以丰富游戏性。塔可以进 行升级(Upgrade)与出售，升级后的塔会有更强威力，同时有些攻击方式也会有所变化。

敌人(Enemy): 根据不同的敌人类型(enemyType)来创建动画不同，属性不同的敌人。子类待完善。

子弹(Bullet): 类似于敌人，可由不同的类型(Type)来初始化不同的子弹，并进行攻击。

触控层: 包括建造炮塔页面(TowerPanleLayer)与炮塔操作页面(TowerOperatorLayer)。

#### 3、游戏完善
除去游戏主界面之外的 UI 界面如下图所示:
  
(1)选择关卡: 即在一个继承 Scene 的 LevelScene 上添加继承 Layer 的滚动层 ScrollView， 通过触摸监视实现了滑动效果，最后给滚动层添加三个继承于 Node 的子节点，构成完整的 选关界面;

(2)解锁: 本关卡胜利后自动解锁下一关;

(3)关卡信息界面用来从 plist 文件中读取本关的游戏设置，并预加载资源; 

(4)开始界面、游戏界面、胜利、失败界面都实现了音乐的暂停、播放;
胜利界面、失败界面还实现了音乐切换;

(5)利用 Cocos 自带粒子库实现了烟花、下雨下雪等特效;

#### 4、数据管理设计
GameManager: 由于游戏时子弹与敌人都是实时变化的，需要有一个类全局的变量去储存相关的信息。

于是我们在游戏设计时采用了单例模式，创建了一个名为 GameManager 的类用作数据存储，并将其设计成单例。

实现方法为:构建一个 private 静态的实例 instance 和一个 public 的接 口 getInstance。整个项目只存在一个这一个实例，在任何地方可用 getInstance 方法得到其静态 instance。

这样做的好处是: 方便数据的统一管理，同时节约了重复申明所需的内存空间和时间。
  
但由于实例在游戏在运行过程中始终存在，会有少量的内存开销，同时其何时释放也是一定的问题。

关于内存释放问题的解决，我采用了:定义一个私有内嵌类 Deleter(防止被滥用)，专门用于删除实例。在其析构函数中执行删除操作，并在 GameManager 中定义其唯一静态实 例。在程序结束时，所有局部静态变量被析构，就删除了 instance。

关卡数据:
关卡相关的金钱，怪物信息，以及地图资源都由 plist 格式文件存储，再有接口类 LoadLevelInfo 进行读取并存入 GameManager 中的 instance 中。 这样做的原因是将数据与游戏独立开，方便定于与修改。

玩家信息:
由 cocos 自带的 UserDefault 存储，方便保存玩家所获星级和解锁关卡。

#### 4、其他
为减少读取图片的时间和内存消耗，游戏主场景中素材都使用 TexturePacker 打包，在
关卡信息页面里预先加载，这样在进行游戏时可以直接使用。



### 三、构建工具
Xcode7.3.1
Microsoft Visual Studio 2015



### 四、构建框架
Cocos2dx3.10

##### 2016年6月19日

# 二维天体引力模拟 说明文档



## 目录

+ [前言](#前言)  
+ [代码](#代码)  
	+ [Position 结构体](#Position-结构体)
		+ 说明
		+ 成员
		+ 重载的运算符
		+ 相关
	+ [Vector2D 类](#Vector2D-类)
		+ 说明
		+ 构造函数
		+ 公有成员
		+ 静态公有成员
		+ 私有成员
		+ 重载的运算符
		+ 代码说明
			+ 构造函数
			+ 公有成员
			+ 静态公有成员
	+ [Body 类](#Body-类)
		+ 说明
		+ 构造函数
		+ 公有成员
		+ 私有成员
		+ 静态私有成员
		+ 相关
		+ 代码说明
			+ 构造函数
			+ 公有成员
	+ [Simulator 类](#Simulator-类)
		+ 说明
		+ 公有成员
		+ 虚函数成员
		+ 私有成员
		+ 静态私有成员
		+ 相关
		+ 代码说明
			+ 公有成员
			+ 虚函数成员
+ [示例代码说明](#示例代码说明)
	+ [multiBody 类](#multiBody-类)
		+ 说明
		+ 构造函数
		+ 私有成员函数
		+ 私有成员
+ [代码使用说明](#代码使用说明)

## 前言

这个项目是我为了练习C++面向对象而写的，与其他引力模拟项目不同，此项目不仅实现了功能，还尝试实现了接口，这也是我在面向对象编程方面的练习。

这个项目借助于`easyX`图形库，[传送门](https://easyx.cn/)。

模拟的模型仅使用高中物理相关知识，算法十分粗略：

> 假设所有天体完美地处于同一平面，且碰撞过程中无质量损失
>
> > 引力模型：==引力公式==  $F=G\frac{M \cdot m}{r^2}$
> >
> > 碰撞模型：==动量公式==  $m_1 \vec v_1 + m_2 \vec v_2 = (m_1 + m_2)\cdot \vec v_3$

欢迎各路大佬挑刺、优化代码，这对于我来说也是非常好的学习机会！

## 代码

### `Position` 结构体

+ 说明

	用于保存双精度浮点数的二维坐标 `(x, y)`。

+ 成员

	```c++
	double x;
	double y;
	```

+ 重载的运算符

	~~~c++
	Position operator+(const Position& pos1, const Position& pos2);	// pos1 + pos2
	Position operator-(const Position& pos1, const Position& pos2);	// pos1 - pos2
	Position& operator+=(Position& pos1, const Position& pos2);		// pos1 += pos2
	Position& operator-=(Position& pos1, const Position& pos2);		// pos1 -= pos2
	
	bool operator==(const Position& pos1, const Position& pos2);	// pos1 == pos2
	bool operator!=(const Position& pos1, const Position& pos2);	// pos1 != pos2
	
	Position operator-(const Position& pos);						// -pos
	
	//用于cout的重载
	inline std::ostream& operator<<(std::ostream& os, const Position& pos);
	~~~

+ 相关

	+ 定义于`"Vector2D.h"`中。
	+ 定义了常量表达式`CoordinateX`表示X轴的单位向量。
	+ 定义了常量表达式`CoordinateY`表示Y轴的单位向量。

### `Vector2D` 类

+ 说明

	二维向量模型。

+ 构造函数

	~~~c++
	Vector2D();
	Vector2D(double x, double y);
	Vector2D(const Position& _pos);
	Vector2D(const Position& pos1, const Position& pos2);
	~~~

+ 公有成员

	~~~c++
	double X() const;
	double Y() const;
	double Length() const;
	Position position() const;
	
	void X(double x);
	void Y(double y);
	void setXY(double x, double y);
	void setXY(const Position& pos);
	
	double angle_cos(const Vector2D& vec) const;
	double angle(const Vector2D& vec) const;
	
	Vector2D& setToZero();
	
	Vector2D direction() const;
	void direction(const Vector2D& direc) const;
	
	int Decomposition(Vector2D& vecX, Vector2D& vecY, const Vector2D& CoorVec) const;
	~~~

+ 静态公有成员

	~~~c++
	static Vector2D& direction(double x1, double y1, double x2, double y2, Vector2D& direc);
	static Vector2D& direction(const Position& pos1, const Position& pos2, Vector2D& direc);
	~~~

+ 私有成员

	~~~c++
	Position pos;  	 	//终点坐标
	double length;  	//模长
	
	void CalLength();	//计算模长
	~~~

+ 重载的运算符

	~~~c++
	Vector2D& operator=(const Vector2D& vec);			// Vector2D = Vector2D
	Vector2D& operator=(const Position& pos);			// Vector2D = Position
	bool operator==(const Vector2D& vec) const;			// Vector2D == Vector2D
	bool operator!=(const Vector2D& vec) const;			// Vector2D != Vector2D
	Vector2D operator+(const Vector2D& vec) const;		// Vector2D + Vector2D
	Vector2D operator-(const Vector2D& vec) const;		// Vector2D - Vector2D
	Vector2D& operator+=(const Vector2D& vec);			// Vector2D += Vector2D
	Vector2D& operator-=(const Vector2D& vec);			// Vector2D -= Vector2D
	
	Vector2D operator*(const double& num) const;		// Vector2D * double
	Vector2D operator/(const double& num) const;		// Vector2D / double
	
	Vector2D& operator*=(const double& num);			// Vector2D *= double
	Vector2D& operator/=(const double& num);			// Vector2D /= double
	
	double operator*(const Vector2D& vec) const;		// Vector2D * Vector2D
	
	Vector2D operator*(const double& num, const Vector2D& vec);	// double * Vector2D
	Vector2D operator-(const Vector2D& vec);					// -Vector2D
	
	//用于cout的重载
	std::ostream& operator<<(std::ostream& os, const Vector2D& vec);
	~~~

+ 相关

	+ 定义于`"Vector2D.h"`中。
	+ 定义了常量`PI`表示圆周率。
	+ 友元类  `class Body`。
	+ 友元类  `class Simulator`。

+ 代码说明

	+ 构造函数

		+ ````c++
			Vector2D();
			````

			默认构造函数，将构造一个零向量。

		+ ````c++
			Vector2D(double x, double y);
			````

			将构造一个终点坐标为`(x, y)`的向量。

		+ ````c++
			Vector2D(const Position& _pos);
			````

			将构造一个终点坐标为`_pos`的向量。

		+ ~~~~c++
			Vector2D(const Position& pos1, const Position& pos2);
			~~~~

			将构造一个由`pos1`指向`pos2`的向量。

	+ 公有成员

		+ ````c++
			double X() const;
			````

			这个函数返回向量的终点坐标 `X`。

		+ ````c++
			double Y() const;
			````

			这个函数返回向量的终点坐标 `Y`。

		+ ````c++
			double Length() const;
			````

			这个函数返回向量的模长。

		+ ````c++
			Position positon() const;
			````

			这个函数返回向量的终点坐标。

		+ ````c++
			void X(double x);
			````

			这个函数设置向量的终点坐标 `X`。

		+ ````c++
			void Y(double y);
			````

			这个函数设置向量的终点坐标 `Y`。

		+ ````c++
			void setXY(double x, double y);
			````

			这个函数设置向量的终点坐标。

		+ ````c++
			void setXY(const Position& pos);
			````

			这个函数设置向量的终点坐标。

		+ ````c++
			double angle_cos(const Vector2D& vec) const;
			````

			这个函数返回与向量`vec`之间夹角的余弦值。

		+ ````c++
			double angle(const Vector2D& vec) const;
			````

			这个函数返回与向量`vec`之间的夹角。

		+ ````c++
			Vector2D direction() const;
			````

			这个函数返回此向量的单位方向向量

		+ ````c++
			void direction(Vector2D& direc) const;
			````

			这个函数将`direc`设置为此向量的单位方向向量

		+ ````c++
			Vector2D& setToZero();
			````

			这个函数将向量设置为零向量，并返回它的引用。

		+ ````c++
			int Decomposition(Vector2D& vecX, Vector2D& vecY, const Vector2D& CoorVec = CoordinateX) const;
			````

			这个函数将向量进行分解，`vecX`沿着`CoorVec`方向，`vecY`垂直于`CoorVec`方向，`CoorVec`默认为X轴方向。

			返回 `0` 表示向量分解正常进行； 返回 `-1` 表示`CoorVec`与要分解向量的相等

	+ 静态公有成员

		+ ````c++
			static Vector2D& direction(double x1, double y1, double x2, double y2, Vector2D& direc)；
			````

			这个函数将`direc`设置为由`(x1, y1)`指向`(x2, y2)`的单位方向向量，并返回它的引用。

		+ ````c++
			static Vector2D& direction(const Position& pos1, const Position& pos2, Vector2D& direc);
			````

			这个函数将`direc`设置为由`pos1`指向`pos2`的单位方向向量，并返回它的引用。
				

### `Body` 类

+ 说明

	二维天体模型，但半径是使用==球体体积公式== $V = \frac{4}{3}\pi r^3$ 得到的。

+ 构造函数

	```c++
	Body(double _x, double _y, unsigned _mass, const Vector2D& _vel, COLORREF _col, int _number = NULL);
	Body(double _x, double _y, unsigned _mass, double vx, double vy, COLORREF _col, int _number = NULL);
	Body(const Position& _pos, unsigned _mass, const Vector2D& _vel, COLORREF _col, int _number = NULL);
	Body(const Position& _pos, unsigned _mass, double vx, double vy, COLORREF _col, int _number = NULL);
	```

+ 公有成员

	````c++
	double X() const;
	double Y() const;
	Position currPOS() const;
	void changePOS(const Position& pos);
	void changePOS(double x, double y);
	
	double Radius() const;
	unsigned Mass() const;
	void Mass(unsigned mass);
	
	Vector2D Velocity() const;
	Vector2D Gravity() const;
	void Velocity(const Vector2D& vel);
	void Gravity(const Vector2D& gravity);
	
	bool isLocked() const;
	void Lock(bool locked);
	
	size_t getMaxPath() const;
	void setMaxPath(size_t size);
	
	int move();
	void Show() const;
	void ShowInfo(int x, int y) const;
	
	int Number() const;
	std::wstring name() const;
	````

+ 私有成员

	````c++
	Position pos;				//坐标
	Vector2D vel;				//合速度
	Vector2D grav;				//合力（引力）
	COLORREF color;				//颜色
	std::list<Position> path;	 //轨迹
	
	unsigned mass;		//质量
	double radius;		//半径
	bool locked;		//是否锁定，锁定后位置不会改变
	int number;			//编号
	
	void CalRadius();	//计算半径，公式见**说明**
	````

+ 静态私有成员

	````c++
	static size_t maxPath;				 //轨迹最长长度，默认为150
	constexpr static short DENSITY = 1;	 //密度
	````

+ 相关

	+ 定义于 `"Body.h"` 中
	+ 宏定义了 `GRAVITYCONST` 表示引力常量，它的值为`0.35`。 
	+ 宏定义了 `STAR_ID` 表示恒星的ID， 它的值为`0x7FFFFFFF`。
	+ 宏定义了 `TOINT(num)` 用于转换数据为`int`类型。
	+ 宏定义了 `TODOUBLE(num)` 用于转换数据为`double`类型。
	+ 友元类 `class Simulator`。 

+ 代码说明

	+ 构造函数

		+ ````c++
			Body(double _x, double _y, unsigned _mass, const Vector2D& _vel, COLORREF _col, int _number = NULL);
			````

			将构造一个位于`(_x, _y)`，质量为`_mass`， 初始速度为`_vel`，颜色为`_col`，编号为`_number`的天体。

		+ ````c++
			Body(double _x, double _y, unsigned _mass, double vx, double vy, COLORREF _col, int _number = NULL);
			````

			将构造一个位于`(_x, _y)`，质量为`_mass`， 初始速度为`(vx, vy)`，颜色为`_col`，编号为`_number`的天体。

		+ ````c++
			Body(const Position& _pos, unsigned _mass, const Vector2D& _vel, COLORREF _col, int _number = NULL);
			````

			将构造一个位于`_pos`，质量为`_mass`， 初始速度为`_vel`，颜色为`_col`，编号为`_number`的天体。

		+ ````c++
			Body(const Position& _pos, unsigned _mass, double vx, double vy, COLORREF _col, int _number = NULL);
			````

			将构造一个位于`_pos`，质量为`_mass`， 初始速度为`(vx, vy)`，颜色为`_col`，编号为`_number`的天体。

		+ 备注：

			+ 天体颜色建议使用`easyX`库提供的`RGB(r, g, b)`宏。
			+ 天体的半径只能由私有成员函数`void CalRadius()`修改。
			+ 天体的编号只能在构造函数定义。

	+ 公有成员

		+ ````c++
			double X() const;
			````

			这个函数返回天体的`X`坐标。

		+ ````c++
			double Y() const;
			````

			这个函数返回天体的`Y`坐标。

		+ ````c++
			Position currPOS() const;
			````

			这个函数返回天体的坐标。

		+ ````c++
			void changePOS(const Position& pos);
			````

			这个函数设置天体的坐标为 `pos`。

		+ ````c++
			void changePOS(double x, double y);
			````

			这个函数设置天体的坐标为 `(x, y)`。

		+ ````c++
			double Radius() const;
			````

			这个函数返回天体的半径。

		+ ````c++
			unsigned Mass() const
			````

			这个函数返回天体的质量。

		+ ````c++
			void Mass(unsigned mass);
			````

			这个函数设置天体的质量为 `mass`。

		+ ````c++
			Vector2D Velocity() const;
			````

			这个函数返回天体的合速度。

		+ ````c++
			Vector2D Gravity() const;
			````

			这个函数返回天体受到的合力（引力）。

		+ ````c++
			void Velocity(const Vector2D& vel);
			````

			这个函数设置天体的合速度为`vel`。

		+ ````c++
			void Gravity(const Vector2D& gravity);
			````

			这个函数设置天体受到的合力（引力）为`gravity`。

		+ ````c++
			bool isLocked() const;
			````

			这个函数返回天体是否被锁定.

		+ ````c++
			void Lock(bool locked);
			````

			这个函数设置天体的锁定状态。

		+ ````c++
			size_t getMaxPath() const;
			````

			这个函数返回天体轨迹的最长长度。

		+ ````c++
			void setMaxPath(size_t size);
			````

			这个函数设置天体轨迹的最长长度为`size`。

		+ ````c++
			int move();
			````

			这个函数会根据当前天体的合速度移动天体，天体被锁定返回`-1`，没有锁定返回`0`。

			计算的步长为`T = 0.25`。

		+ ````c++
			void Show() const;
			````

			这个函数能将天体和天体的轨迹显示出来。

		+ ````c++
			void ShowInfo(int x, int y) const;
			````

			这个函数会将天体的编号，质量显示在`(x, y)`位置。

		+ ````c++
			int Number() const;
			````

			这个函数返回天体的编号。

		+ ````c++
			std::wstring name() const;
			````

			这个函数将天体的编号转换为`std::wstring`，并将其返回。

			当天体的编号为`STAR_ID`时，这个函数返回`std::wstring`类型的`"Star"`。

### `Simulator` 类

+ 说明

	+ 天体模拟的基类，模拟的基础主体函数定义在此类中，为虚类，不可构造对象。
	+ 使用建议：创建派生类公有继承自此类，并实现此类的虚函数。

+ 公有成员

	````c++
	int run();
	
	Body* hitCheck(Body* body1, Body* body2);
	int CalGravity(Body* body1, Body* body2);
	
	BodyConstIt findBody(const BodyList& bodys, int number);
	double Distance(const Body* body1, const Body* body2);
	
	char& PauseKey();
	char& ExitKey();
	
	void setScreen(int Width, int Height);
	void setAspectRatio(float ratio);
		
	double Randf(double min, double max);
	
	void showDetailInfo(bool ifshow);
	bool isDetailInfoShowed() const;
	
	enum presetKeyValue;
	````

+ 虚函数成员

	````c++
	virtual void update() = 0;
	````

+ 私有成员

	````c++
	char pauseKey = SPACE;  //暂停键
	char exitKey = ESC;     //退出键 - 退出run()函数
	bool pause = false;     //是否为暂停状态
	bool ifShowDetail = true;	//是否显示fps，运行时间
	
	float aspectratio = 1.0;	//缩放比例
	int screenWidth = 1280;		//画幅宽
	int screenHeight = 720;		//画幅高
	
	int keyBoardCheck();		//检查并处理键盘事件
	
	void FPS();			//计算FPS
	void runTime();		//运行时间
	````

+ 静态私有成员

	````c++
	static std::default_random_engine rand_engine;	//生成随机数的引擎
	````

+ 相关

	+ 定义于`"Simulator.h"`中。
	+ 宏定义了`RANDOM(a, b)`用于生成取值在`[a, b]`的整形随机数。
	+ 宏定义了`HEADER`，当允许显示FPS和运行时间时，天体信息的显示需要在`y`坐标上加上此宏，它的值为`25`。
	+ `typedef` 定义了 `std::list<Body*>`为`BodyList`。
	+ `typedef` 定义了 `std::list<Body*>::const_iterator`为`BodyConstIt`。
	+ 定义了内联函数`BodyConstIt operator+(BodyConstIt it, int num)` 作为`BodyConstIt`的`+`运算符重载。

+ 代码说明

	+ 公有成员

		+ ````c++
			int run();
			````

			==重要==，此函数为运行的主体，完成绘图工作，将循环执行`update()`函数以及`FPS()`函数、`runTime()`函数，以及检查和处理键盘事件。

			返回`0`表示该函数正常退出。

			返回`-1`表示该函数异常退出。

		+ ````c++
			Body* hitCheck(Body* body1, Body* body2);
			````

			这个函数检查`body1`与`body2`是否相撞，若相撞，则处理撞击事件，质量大的天体将吞噬质量小的天体，若质量相等，则`body2`将会被`body1`吞噬，同时返回被吞噬的天体的指针；若未发生碰撞，或`body1`与`body2`指向同一天体，则返回空指针。

			==注意==，如果碰撞发生，在该函数中将会对天体的质量和速度进行修改（见**说明**），若忽略返回值，将造成难以预料的错误。

		+ ````c++
			int CalGravity(Body* body1, Body* body2);
			````

			这个函数计算两个天体之间的引力，并将其向量加在天体原有的合力上。

			返回`0`表示计算过程正常进行。

			返回`-1`表示`body1`与`body2`指向同一天体。

		+ ````c++
			BodyConstIt findBody(const BodyList& bodys, int number);
			````

			这个函数在`Bodylist`类型中找到编号为`number`的天体，返回它在`bodys`的`const`迭代器。

			类型`BodyList`及`BodyConstIt`见此目录的**相关**。

		+ ````c++
			double Distance(const Body* body1, const Body* body2);
			````

			这个函数计算并返回`body1`与`body2`间的距离。

			若`body1`与`body2`指向同一天体，将返回`-1`。

		+ ````c++
			char& PauseKey();
			````

			这个函数返回暂停键的引用。

		+ ````c++
			char& ExitKey();
			````

			这个函数返回退出键的引用。

		+ ````c++
			void setScreen(int Width, int Height);
			````

			这个函数设置`easyX`绘图窗口的宽和高。

		+ ````c++
			void setAspectRatio(float ratio);
			````

			这个函数设置`easyX`绘图窗口的缩放比例。

		+ ````c++
			double Randf(double min, double max);
			````

			这个函数返回取值在`[min, max]`的双精度浮点随机数。

		+ ````c++
			void showDetailInfo(bool ifshow);
			````

			这个函数设置是否要显示FPS和运行时间。

		+ ````c++
			bool isDetailInfoShowed() const;
			````

			这个函数返回是否要显示FPS和运行时间。

		+ ````c++
			enum presetKeyValue;
			````

			这个枚举变量保存了预设的几个键值：

			`TAB`、`ESC`、`SPACE`。

	+ 虚函数成员

		+ ````c++
			virtual void update() = 0;
			````

			==重要==，这个函数是模拟的主体，需要用户自行定义，将会在调用`run()`函数时循环调用。

## 示例代码说明

### `multiBody` 类

+ 说明

	这个类作为示例，继承自`class Simulator`，并根据父类的基础函数实现了多体引力模拟。

	使用时请把`multiBody.h`和`multiBody.cpp`与其它文件放置于同一目录下。

+ 构造函数

	````c++
	multiBody(int bodys);
	````

	将会构造`bodys`个随机位置，随机质量，随机初速度的天体和一个居中，质量为`150000`，无初速，编号为`STAR_ID`，位置锁定的恒星天体，同时将画幅设置为`1600 x 900`。

+ 私有成员函数

	+ ````c++
		void update();
		````

		这个函数是对父类中虚函数`update()`的实现，完成了多个天体间各种事件的计算。

	+ ````c++
		void hitEvent();
		````

		这个函数是基于父类中的基础函数`hitcheck()`的，完成了多个天体间的碰撞检测和碰撞处理。

	+ ````c++
		void gravity();
		````

		这个函数是基于父类中的基础函数`CalGravity()`的，完成了多个天体间的引力计算。

+ 私有成员

	````c++
	BodyList Bodys;		//用于保存多个天体的链表
	````

+ **详细的实现过程请阅读示例代码**

## 代码使用说明

​		要使用这个库，请把所有相关的`.h`文件和`.cpp`文件添加进项目，之后的具体使用可以参考示例代码的`class multiBody`，公有继承自`class Simulator`，并依靠父类的基础计算&处理函数，进一步拓展，实现功能。








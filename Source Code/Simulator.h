#pragma once
#ifndef __SIMULATORBASE_HEADER__
#define __SIMULATORBASE_HEADER__

#include <Windows.h>
#include <conio.h>
#include <random>

#include "Body.h"

typedef std::list<Body*> BodyList;
typedef std::list<Body*>::const_iterator BodyConstIt;

#define RANDOM(a, b) ((rand() % (b - a + 1)) + a)
#define HEADER (25)

class Simulator
{

public:
	int run();			//启动函数

	Body* hitCheck(Body* body1, Body* body2);		//检查碰撞
	int CalGravity(Body* body1, Body* body2);	//计算引力
	
	BodyConstIt findBody(const BodyList& bodys, int number);	//在List容器中查找Body，返回const迭代器

	//计算Body间的距离
	double Distance(const Body* body1, const Body* body2)
	{
		return sqrt(pow(body1->X() - body2->X(), 2) + pow(body1->Y() - body2->Y(), 2));
	}

	enum presetKeyValue
	{
		//预设的键盘值(ASCII)
		TAB = 9,
		ESC = 27,
		SPACE = 32
	};

	char& PauseKey()
	{
		//返回暂停键的值
		return pauseKey;
	}
	char& ExitKey()
	{
		//返回退出键的值
		return exitKey;
	}

	void setScreen(int Width, int Height)
	{
		this->screenWidth = Width;
		this->screenHeight = Height;
	}
	void setAspectRatio(float ratio)
	{
		this->aspectratio = ratio;
	}
	
	double Randf(double min, double max)
	{
		std::uniform_real_distribution<double> random(min, max);
		return random(rand_engine);
	}

	void showDetailInfo(bool ifshow)
	{
		this->ifShowDetail = ifshow;
	}
	bool isDetailInfoShowed() const
	{
		return ifShowDetail;
	}

private:
	char pauseKey = SPACE;  //暂停键
	char exitKey = ESC;     //退出键 - 退出run()函数
	bool pause = false;     //是否为暂停状态
	bool ifShowDetail = true;	//是否显示fps，运行时间

	float aspectratio = 1.0;	//缩放比例
	int screenWidth = 1280;		//画幅宽
	int screenHeight = 720;		//画幅高

	virtual void update() = 0;	//执行更新的函数，需要用户进行定义
	int keyBoardCheck();		//检查并处理键盘事件

	void FPS();			//FPS
	void runTime();		//运行时间

	static std::default_random_engine rand_engine;
};

//由于const_iterator没有+运算符，手动重载
inline BodyConstIt operator+(BodyConstIt it, int num) 
{
	while (num > 0)
	{
		++it;
		--num;
	}
	return it;
}  

#endif // !__SIMULATORBASE_HEADER__
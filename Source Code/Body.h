#pragma once
#ifndef __BODYCLASS_HEADER__
#define __BODYCLASS_HEADER__

#include <list>
#include <string>
#include <graphics.h>

#include "Vector2D.h"

#define GRAVITYCONST 0.35
#define STAR_ID 0X7FFFFFFF

#define TOINT(num) (static_cast<int>(num))
#define TODOUBLE(num) (static_cast<double>(num))

class Body
{
public:
	Body(double _x, double _y, unsigned _mass, const Vector2D& _vel, COLORREF _col, int _number = NULL)
		:pos(_x, _y), mass(_mass), vel(_vel), color(_col), number(_number)
	{
		CalRadius();
	}
	Body(double _x, double _y, unsigned _mass, double vx, double vy, COLORREF _col, int _number = NULL)
		:pos(_x, _y), mass(_mass), vel(vx, vy), color(_col), number(_number)
	{
		CalRadius();
	}

	double X() const
	{
		return pos.x;
	}
	double Y() const
	{
		return pos.y;
	}
	void X(double x)
	{
		this->path.push_back(pos);
		this->pos.x = x;
	}
	void Y(double y)
	{
		this->path.push_back(pos);
		this->pos.y = y;
	}

	Position currPOS() const
	{
		return this->pos;
	}
	void changePOS(const Position& pos)
	{
		this->path.push_back(pos);
		this->pos = pos;		
	}
	void changePOS(double x, double y)
	{
		this->path.push_back(pos);
		this->pos.x = x;
		this->pos.y = y;
	}

	bool isLocked() const
	{
		return locked;
	}
	void Lock(bool locked)
	{
		this->locked = locked;
	}

	double Radius() const
	{
		return radius;
	}
	unsigned Mass() const
	{
		return mass;
	}
	void Mass(const unsigned& mass)
	{
		this->mass = mass;
		CalRadius();
	}

	Vector2D Velocity() const
	{
		return this->vel;
	}
	Vector2D Gravity() const
	{
		return grav;
	}
	void Velocity(const Vector2D& vel)
	{
		this->vel = vel;
	}
	void Gravity(const Vector2D& gravity)
	{
		this->grav = gravity;
	}

	size_t getMaxPath() const
	{
		return maxPath;
	}
	void setMaxPath(size_t size)
	{
		maxPath = size;
	}

	int move();				//移动
	void Show() const;		//显示天体
	//在(x, y)位置显示天体的信息
	void ShowInfo(int x, int y) const
	{
		settextcolor(color);
		outtextxy(x, y, (std::wstring(L"Body #") + name() + L" Mass: " + std::to_wstring(mass)).c_str());
	}

	int Number() const
	{
		//返回此Body的编号
		return number;
	}
	std::wstring name() const
	{
		if (number < STAR_ID)
			return std::to_wstring(number);
		else
			return std::wstring(L"Star");
	}

private:

	void CalRadius()noexcept 
	{
		//质量改变时重新计算半径 (方法pow((3 * mass) / (4 * PI * DENSITY), 1.0 / 3) 可能导致溢出)
		radius = pow((this->mass) / (4 * PI * DENSITY) +
			(this->mass) / (4 * PI * DENSITY) +
			(this->mass) / (4 * PI * DENSITY),
			1.0 / 3);
	}

	Vector2D vel;			//合速度
	Vector2D grav;			//受到引力的合力

	Position pos;			//当前坐标

	COLORREF color;			//颜色	
	std::list<Position> path;	//轨迹

	unsigned mass;			//质量
	double radius;			//半径

	static size_t maxPath;	//轨迹最大

	constexpr static short DENSITY = 1;	//密度

	int number;				//编号
	bool locked;			//锁定位置，此时速度无法改变

	friend class Simulator;
};

#endif // !__BODYCLASS_HEADER__
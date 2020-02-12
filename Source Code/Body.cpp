#include "Body.h"

constexpr double T = 0.25;

size_t Body::maxPath = 150;

int Body::move()
{
	if (!locked)
	{
		vel.pos.x += (grav.pos.x / mass) * T;
		vel.pos.y += (grav.pos.y / mass) * T;
		vel.CalLength();

		//更新坐标
		path.push_back(pos);
		pos.x += vel.pos.x * T;
		pos.y += vel.pos.y * T;

		if (path.size() > maxPath)
			path.pop_front();

		grav.setToZero();
		return 0;
	}
	else
		return -1;
}

void Body::Show() const
{
	//显示天体
	setfillcolor(color);	
	setfillstyle(BS_SOLID);
	solidcircle(TOINT(pos.x), TOINT(pos.y), TOINT(radius));
	
	//显示编号
	setbkmode(TRANSPARENT);
	settextcolor(WHITE);
	outtextxy(TOINT(pos.x), TOINT(pos.y), name().c_str());	

	//显示轨迹
	if ((path.cbegin() != path.cend()) && !locked)
	{
		setlinecolor(color);
		Position lastpos = *path.cbegin();
		for (auto currpos : path)
		{
			line(TOINT(lastpos.x), TOINT(lastpos.y), TOINT(currpos.x), TOINT(currpos.y));
			lastpos = currpos;
		}
		line(TOINT(lastpos.x), TOINT(lastpos.y), TOINT(pos.x), TOINT(pos.y));
	}
}
#include "Simulator.h"

//Simulator::keyBoardCheck() 返回值
#define CALL_EXIT 1        //退出
#define CALL_NOMOVEMENT 0  //非退出

#define SQUARE(num) pow(num, 2)
#define POWTHREE(num) pow(num, 3)

std::default_random_engine Simulator::rand_engine((unsigned)time(0));

time_t startTime;

int Simulator::run()
{
	initgraph(screenWidth, screenHeight);
	setaspectratio(aspectratio, aspectratio);

	startTime = time(NULL);
	BeginBatchDraw();	//开始批量绘图
	while (true)
	{
		if (!pause)
		{
			if (ifShowDetail)
			{
				settextcolor(WHITE);
				FPS();
				runTime();
				outtextxy(0, 12, L"============================");
			}

			update();			//执行更新，update()为虚函数，需要用户自己定义
			FlushBatchDraw();	//执行绘图操作

			Sleep(10);			//每秒执行更新次数
			cleardevice();

		}
		
		//检查并处理键盘事件
		if (keyBoardCheck() == CALL_EXIT) {
			EndBatchDraw();	//结束批量绘图
			return 0;		//用户按下返回键，跳出循环，结束run()函数
		}

	}
	EndBatchDraw();		//结束批量绘图
	return -1;
}

int Simulator::keyBoardCheck()
{
	int pressedKey;
	if (_kbhit())
	{
		pressedKey = _getch();
		if (pressedKey == pauseKey)
			if (pause == true)
				pause = false;
			else
				pause = true;
		else if (pressedKey == exitKey)
			return CALL_EXIT;
	}

	return CALL_NOMOVEMENT;
}

Body* Simulator::hitCheck(Body* body1, Body* body2)
{
	if (body1 != body2)
	{
		double distance = Distance(body1, body2);
		if (distance <= body1->Radius() + body2->Radius())
		{
			if (body1->Mass() >= body2->Mass())
			{
				//动量公式m1v1 + m2v2 = (m1+m2)*v
				body1->vel = (
					body1->vel * TODOUBLE(body1->mass) + body2->vel * TODOUBLE(body2->mass)
					) / (
						TODOUBLE(body1->mass) + TODOUBLE(body2->mass)
					);

				//碰撞后质量相加，无能量损失
				body1->mass += body2->mass;
				body1->CalRadius();

				return body2;  //返回撞击后质量小的天体的指针
			}
			else
			{
				//动量公式m1v1 + m2v2 = (m1+m2)*v
				body2->vel = (
					body1->vel * TODOUBLE(body1->mass) + body2->vel * TODOUBLE(body2->mass)
					) / (
						TODOUBLE(body1->mass) + TODOUBLE(body2->mass)
					);

				//碰撞后质量相加，无能量损失
				body2->mass += body1->mass;
				body2->CalRadius();

				return body1;  //返回撞击后质量小的天体的指针
			}
		}
	}
	return nullptr;        //不发生碰撞则返回空指针
}

BodyConstIt Simulator::findBody(const BodyList& bodys, int number)
{	
	auto endIt = bodys.end();
	//查找list容器中Body的索引
	for (BodyConstIt it = bodys.begin(); it != endIt; ++it)
	{
		if ((*it)->Number() == number) {
			return it;
		}
	}
	return bodys.end();
}

int Simulator::CalGravity(Body* body1, Body* body2)
{
	if (body1 != body2)
	{	
		Vector2D grav;

		//F = G * m1 * m2 / r^2
		Vector2D::direction(body1->pos, body2->pos, grav)	//把grav设为由body1指向body2的单位向量
			*= ((GRAVITYCONST * body1->mass * body2->mass) / (pow(body1->pos.x - body2->pos.x, 2) + pow(body1->pos.y - body2->pos.y, 2)));

		body1->grav += grav;
		body2->grav -= grav;

		return 0;
	}
	else
		return -1;	//body1和body2指针相同
}

void Simulator::FPS()
{
#define FPS_COUNT 8
	static int i = 0;
	static DWORD oldTime = GetTickCount();
	static float fps;
	if (i > FPS_COUNT)
	{
		i = 0;
		int newTime = TOINT(GetTickCount64());
		int elapsedTime = newTime - oldTime;
		fps = FPS_COUNT / (elapsedTime / 1000.0f);
		oldTime = newTime;
	}
	++i;
	outtextxy(0, 0, (L"FPS: " + std::to_wstring(fps)).c_str());
}
inline void Simulator::runTime()
{
	outtextxy(120, 0, (L"Run Time: " + std::to_wstring(time(NULL) - startTime) + L"s").c_str());
}

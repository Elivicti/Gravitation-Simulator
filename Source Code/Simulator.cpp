#include "Simulator.h"

//Simulator::keyBoardCheck() ����ֵ
#define CALL_EXIT 1        //�˳�
#define CALL_NOMOVEMENT 0  //���˳�

#define SQUARE(num) pow(num, 2)
#define POWTHREE(num) pow(num, 3)

std::default_random_engine Simulator::rand_engine((unsigned)time(0));

time_t startTime;

int Simulator::run()
{
	initgraph(screenWidth, screenHeight);
	setaspectratio(aspectratio, aspectratio);

	startTime = time(NULL);
	BeginBatchDraw();	//��ʼ������ͼ
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

			update();			//ִ�и��£�update()Ϊ�麯������Ҫ�û��Լ�����
			FlushBatchDraw();	//ִ�л�ͼ����

			Sleep(10);			//ÿ��ִ�и��´���
			cleardevice();

		}
		
		//��鲢��������¼�
		if (keyBoardCheck() == CALL_EXIT) {
			EndBatchDraw();	//����������ͼ
			return 0;		//�û����·��ؼ�������ѭ��������run()����
		}

	}
	EndBatchDraw();		//����������ͼ
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
				//������ʽm1v1 + m2v2 = (m1+m2)*v
				body1->vel = (
					body1->vel * TODOUBLE(body1->mass) + body2->vel * TODOUBLE(body2->mass)
					) / (
						TODOUBLE(body1->mass) + TODOUBLE(body2->mass)
					);

				//��ײ��������ӣ���������ʧ
				body1->mass += body2->mass;
				body1->CalRadius();

				return body2;  //����ײ��������С�������ָ��
			}
			else
			{
				//������ʽm1v1 + m2v2 = (m1+m2)*v
				body2->vel = (
					body1->vel * TODOUBLE(body1->mass) + body2->vel * TODOUBLE(body2->mass)
					) / (
						TODOUBLE(body1->mass) + TODOUBLE(body2->mass)
					);

				//��ײ��������ӣ���������ʧ
				body2->mass += body1->mass;
				body2->CalRadius();

				return body1;  //����ײ��������С�������ָ��
			}
		}
	}
	return nullptr;        //��������ײ�򷵻ؿ�ָ��
}

BodyConstIt Simulator::findBody(const BodyList& bodys, int number)
{	
	auto endIt = bodys.end();
	//����list������Body������
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
		Vector2D::direction(body1->pos, body2->pos, grav)	//��grav��Ϊ��body1ָ��body2�ĵ�λ����
			*= ((GRAVITYCONST * body1->mass * body2->mass) / (pow(body1->pos.x - body2->pos.x, 2) + pow(body1->pos.y - body2->pos.y, 2)));

		body1->grav += grav;
		body2->grav -= grav;

		return 0;
	}
	else
		return -1;	//body1��body2ָ����ͬ
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

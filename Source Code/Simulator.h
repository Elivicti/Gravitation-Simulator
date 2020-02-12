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
	int run();			//��������

	Body* hitCheck(Body* body1, Body* body2);		//�����ײ
	int CalGravity(Body* body1, Body* body2);	//��������
	
	BodyConstIt findBody(const BodyList& bodys, int number);	//��List�����в���Body������const������

	//����Body��ľ���
	double Distance(const Body* body1, const Body* body2)
	{
		return sqrt(pow(body1->X() - body2->X(), 2) + pow(body1->Y() - body2->Y(), 2));
	}

	enum presetKeyValue
	{
		//Ԥ��ļ���ֵ(ASCII)
		TAB = 9,
		ESC = 27,
		SPACE = 32
	};

	char& PauseKey()
	{
		//������ͣ����ֵ
		return pauseKey;
	}
	char& ExitKey()
	{
		//�����˳�����ֵ
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
	char pauseKey = SPACE;  //��ͣ��
	char exitKey = ESC;     //�˳��� - �˳�run()����
	bool pause = false;     //�Ƿ�Ϊ��ͣ״̬
	bool ifShowDetail = true;	//�Ƿ���ʾfps������ʱ��

	float aspectratio = 1.0;	//���ű���
	int screenWidth = 1280;		//������
	int screenHeight = 720;		//������

	virtual void update() = 0;	//ִ�и��µĺ�������Ҫ�û����ж���
	int keyBoardCheck();		//��鲢��������¼�

	void FPS();			//FPS
	void runTime();		//����ʱ��

	static std::default_random_engine rand_engine;
};

//����const_iteratorû��+��������ֶ�����
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
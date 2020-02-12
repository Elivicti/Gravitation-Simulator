#pragma once

#include "Simulator.h"
#ifndef __MULTIBODYCLASS_HEADER__
#define __MULTIBODYCLASS_HEADER__

class multiBody :
	public Simulator
{

public:
	multiBody(int bodys);
	~multiBody()
	{
		for (auto body : Bodys)
			delete body;
	}

	
//private:

	void update();
	void hitEvent();
	void gravity();

	BodyList Bodys;
};

#endif // !__MULTIBODYCLASS_HEADER__
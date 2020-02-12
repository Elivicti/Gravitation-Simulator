#include "multiBody.h"
#include <iostream>

multiBody::multiBody(int bodys)
{
	srand((unsigned)time(NULL));
	setScreen(1600, 900);
	
	for (int i = 0; i < bodys; ++i)
	{
		Bodys.push_back(
			new Body(
				RANDOM(0, 1600),
				RANDOM(0, 900),
				RANDOM(350, 950),
				Randf(-10.0, 10.0),
				Randf(-10.0, 10.0),
				RGB(RANDOM(0, 256), RANDOM(0, 256), RANDOM(0, 256)),
				i
			)
		);
		std::cout << "Pushing Body#" << i << " completed!" << std::endl;
	}
	
	Bodys.push_front(
		new Body(
			1600.0 / 2,
			900.0 / 2,
			150000,
			0.0,
			0.0,
			RGB(RANDOM(0, 256), RANDOM(0, 256), RANDOM(0, 256)),
			STAR_ID
		)
	);
	
	(*Bodys.begin())->Lock(true);
}

void multiBody::update()
{
	gravity();
	hitEvent();
	
	for (auto body : Bodys)
	{
		body->Show();
		body->move();
		
	}

	size_t i = 0;
	for (auto body : Bodys)
	{
		body->ShowInfo(0, 12 * i + HEADER);
		++i;
	}
}

void multiBody::hitEvent()
{
	Body* destoryed = nullptr;
	auto beginIt = Bodys.cbegin();
	auto endIt = Bodys.cend();
	for (BodyConstIt thsBody = beginIt; thsBody != endIt; ++thsBody)
	{
		for (BodyConstIt nxtBody = thsBody + 1; nxtBody != endIt; ++nxtBody)
		{
			destoryed = hitCheck(*thsBody, *nxtBody);
			if (destoryed == nullptr) {
				continue;
			}
			else if (destoryed == *thsBody)
			{
				if (thsBody != beginIt) {
					--thsBody;
					Bodys.erase(thsBody + 1);			//从list容器中删除被摧毁的Body
				}
				else {
					Bodys.erase(thsBody);				//从list容器中删除被摧毁的Body
					thsBody = Bodys.cbegin();			//重置迭代器
				}
				beginIt = Bodys.cbegin();				//重置迭代器
				endIt = Bodys.cend();					//重置迭代器
				
				delete destoryed;						//释放被摧毁的Body的内存
				break;
			}
			else if (destoryed == *nxtBody)
			{
				--nxtBody;
				Bodys.erase(nxtBody + 1);				//从list容器中删除被摧毁的Body
				endIt = Bodys.cend();					//重置迭代器
				delete destoryed;
			}
		}
	}
}

void multiBody::gravity()
{
	for (auto ths : Bodys) {
		for (auto nxt : Bodys) {
			if (nxt->Number() <= ths->Number())
				continue;
			else
				CalGravity(ths, nxt);
		}
	}
}
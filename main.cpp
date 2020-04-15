#include "Engine\Milisick.h"

class Node
{
public:
	Node(){}
	float _x = 0, _y = 0;
	Node(float x, float y):
		_x(x), _y(y)
	{

	}
	virtual void Update(Renderer* r, float& dt, MiliEngine::sKeyState* keys)
	{
		/*

		r->DrawCircle((int)_x, (int)_y, 1);
		if (keys[UP].bHeld)
		_y -= 1.0f;
		if (keys[DOWN].bHeld)
		_y += 1.0f;
		if (keys[LEFT].bHeld)
		_x -= 1.0f;
		if (keys[RIGHT].bHeld)
		_x += 1.0f;

		*/
		
		
	}
};

class Pipe : public Node
{
public:
	Pipe(float x, float y)
	{
		this->_x = x;
		this->_y = y;

	}
	void Update(Renderer* r, float& dt, MiliEngine::sKeyState* keys)
	{
		_x+=0.02f;
		r->Fill((int)_x, 16 + _y, 5 +(int)_x, 60+ _y);
	}
};

class Test : public MiliEngine{
public:
	std::vector<Node*>* gameObj;
	bool OnUserCreate()
	{
		Pipe* p = new Pipe(19,(float) -(std::rand() % 20) - 25 );

		Pipe* p2 = new Pipe(p->_x, -p->_y+10);
		gameObj = new std::vector<Node*>();
		gameObj->push_back(p);
		gameObj->push_back(p2);
		return true;
	}

	bool OnUserUpdate(float fElapsedTime)
	{
		renderer->Fill(0, 0, 120, 60, (short)9608, FG_BLACK);
		//renderer->DrawCircle(16, 16, 14);
		
		for (auto obj : *gameObj)
		{
	
			std::chrono::seconds sec(1);
			obj->Update(renderer, fElapsedTime, m_keys);
			std::this_thread::sleep_for(sec);
			renderer->DrawString(20, 20, std::to_wstring((std::rand() % 20) - 25));
			//renderer->DrawString(20, 20, std::to_wstring(obj->_x));
		}
			

		
		return true;
	}
	~Test()
	{
		delete[] gameObj;
	}
};

int main()
{
	Test t;
	t.ConstructConsole(120, 60, 8, 8);
	t.Start();
	return 0;
}


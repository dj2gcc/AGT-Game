#pragma once

class Clock
{
private:

	double _GlobalTime;

	Clock(){ _GlobalTime = 0;}
	~Clock(){}

public:

	static Clock* Instance()
	{
		static Clock instance;
		return &instance;
	}

	void update(float tslf){ _GlobalTime += tslf; }

	double Global(){ return _GlobalTime; }
};

#define Time Clock::Instance()
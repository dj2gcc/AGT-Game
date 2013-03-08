#pragma once

#include<string>

class Telegram
{
public:

	Telegram(int s, int r, std::string t, double dt, void* m)
	{
		sender = s;
		receiver = r;
		type = t;
		dispatchTime = dt;
		message = m;
	}
	~Telegram(){}


	int sender;
	int receiver;

	std::string type;

	double dispatchTime;

	void* message;
};
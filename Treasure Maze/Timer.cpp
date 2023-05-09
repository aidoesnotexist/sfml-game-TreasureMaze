#include "Timer.h"

Timer::Timer() : oneSec{ sf::seconds(2) },
minutes{ 2 }, seconds{ 0 }
{
	timerFont.loadFromFile("fonts\\mainFont.ttf");
	timerText.setFont(timerFont);
	timerText.setCharacterSize(50);
	timerText.setPosition(215.f, 150.f);
	timerText.setFillColor(sf::Color(235, 200, 70));
	timerText.setString("2:00");
	timerText.setLetterSpacing(2);
}

void Timer::updateTimer()
{
	if (clock.getElapsedTime() >= oneSec)
	{
		clock.restart();
		if (seconds == 0)
		{
			seconds = 59;
			--minutes;
		}
		else
			--seconds;

		if(seconds > 9)
			timerText.setString(std::to_string(minutes) + ':' + std::to_string(seconds));
		else
			timerText.setString(std::to_string(minutes) + ":0" + std::to_string(seconds));
	}
}

void Timer::addTime(const int& addTime)
{
	if (seconds + addTime >= 60)
	{
		seconds = seconds + addTime - 60;
		++minutes;
	}
	else
		seconds += addTime;
}

void Timer::printTimer(sf::RenderTarget* target) const
{
	target->draw(timerText);
}

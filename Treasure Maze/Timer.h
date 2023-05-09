#pragma once
#include <SFML/Graphics.hpp>	
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>	
#include <SFML/Network.hpp>

class Timer
{
	sf::Time oneSec;
	sf::Clock clock;
	int minutes, seconds;

	sf::Font timerFont;
	sf::Text timerText;
public:
	Timer();
	void updateTimer();
	void addTime(const int&);
	void printTimer(sf::RenderTarget*) const;
};


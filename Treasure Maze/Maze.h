#pragma once

#include <SFML/Graphics.hpp>	
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>	
#include <SFML/Network.hpp>

#include "Treasure.h"
#include <iostream>
#include <array>

#define linesLimit 9

using namespace std;

namespace Sound
{
	struct sound
	{
		sf::SoundBuffer b_stoneBreak;
		sf::Sound stoneBreak;

		sound()
		{
			b_stoneBreak.loadFromFile("sounds\\stoneBreak.wav");
			stoneBreak.setBuffer(b_stoneBreak);
		}
	};
}

class Maze
{
	array<sf::RectangleShape, linesLimit> horizontalLine;
	array<sf::RectangleShape, linesLimit> verticalLine;
	sf::RectangleShape mazeBackground;

	array<sf::RectangleShape, 4> scoreOutLines;
	sf::RectangleShape scoreBackground;

	array<sf::RectangleShape, 4> abilitiesOutLines;
	sf::RectangleShape abilitiesBackground;

	int scoreCounter;

	sf::Text timerText, scoreText;
	sf::Text score;
	sf::Font mainFont;
	sf::Texture gold;

	void initMaze();
	void initText();
	void initInfoBoxes();
	void initVariables();
	void initAbilityShapes();
	
public:
	array<array<Treasure*, linesLimit - 1>,
		linesLimit - 1> treasures;

	array<array<Treasure*, 3>, 6> abilityShape;

	bool isSwapping;
	bool isMoving;
	bool isFalling;
	bool gapsFilled;
	bool no_preCheck;

	~Maze();
	
	Sound::sound sounds;

	void fillMaze();
	void start();
	void spawnTreasure(std::pair<int, int>,
		const float& y_value = 0, const int& clear_coef = 1);

	void swap(Treasure*, Treasure*);
	void collide(Treasure&, Treasure&);

	void findLineUps();
	void defineFallingTrack();
	void fill_theGaps();
	void descent();

	void printMaze(sf::RenderTarget*);
	void printTreasures(sf::RenderTarget*);
	void printAbilities(sf::RenderTarget*);
	void printInfoBoxes(sf::RenderTarget*);
	void printText(sf::RenderTarget*);
	
};


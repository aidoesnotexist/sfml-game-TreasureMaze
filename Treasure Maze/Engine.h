#pragma once

#include "Treasure.h"
#include <functional>
#include "Maze.h"
#include "Timer.h"

#define horizontalLimit 8
#define verticalLimit 8

class Engine
{
	sf::RenderWindow* window;
	sf::Event _event;
	bool resource_loaded;
	bool paused;

	int clicks;
	bool swap_back;
	Maze maze;

	sf::Vector2i mousePosition;
	sf::Vector2f mousePosView;

	Treasure* clickedTreasure;
	Treasure* swapBack;
	sf::Color clickedColor;

	Timer timer;
	sf::Music music;

	vector<sf::Color> abilityProgression;
	void addAbility();

	void initVariables(const sf::Time&);

	sf::Texture mazeSquare;
	sf::Texture gold;

	void updateMousePosition();
	void updateTreasures();
	void updateAbilities();

	void loadingScreen();

	void init_inGameMenu();
	void update_inGameMenu();
	void zoomButton(sf::Text&);
	void print_inGameMenu();
	sf::Texture backTexture;
	sf::Sprite background;
	array<sf::RectangleShape, 2> in_gameMenuBounds;
	array<sf::Sprite, 4> mazeSquares;
	sf::RectangleShape in_gameMenuBackground;
	sf::RectangleShape innerBackground;
	sf::Font menuFont;
	vector<sf::Text> menuText 
	{sf::Text(), sf::Text(), sf::Text()};

	void randSquare(sf::Sprite[]);
public:
	Engine(sf::RenderWindow*, 
		const sf::Time&);

	bool exit_toMenu;
	sf::RenderWindow& getWindow() const;

	//Methods
	const bool running() const;
	void scanEvents();

	void update();
	void render();

};
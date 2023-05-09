#pragma once

#include <SFML/Graphics.hpp>	
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>	
#include <SFML/Network.hpp>

#include <functional>
#include "settingsMenu.h"

class mainMenu
{
	sf::RenderWindow* window;
	sf::VideoMode resolution;
	sf::Event _event;
	bool gameStarted;
	bool isClickedAnywhere;

	array<sf::RectangleShape, 4> horizontalMenuOutlines;
	array<sf::RectangleShape, 2> horizontalLogoOutlines;
	array<sf::RectangleShape, 2> verticalLogoOutlines;
	sf::Sprite mazeSquare[2];
	sf::RectangleShape menuBackground;
	sf::RectangleShape logoBackground;

	settingsMenu settings;
	bool settingsOpened;

	sf::Texture maze;
	sf::Sprite square[3];
	sf::Font treasureMaze_f;
	sf::Text treasureMaze;
	array<sf::Text, 5> menuText;

	void initVariables();
	void initWindow();
	void initText();
	void initMenuOutLines();
	void initGameLogo();
	void setLogo();

	void setLogoPosition(const sf::Vector2f&);
	void updateMousePosition();
	void updateMenu();
	void zoomButton(sf::Text&);

	sf::Font mainFont;
	sf::Text clickAnywhere;
	void startUp();

	sf::Vector2i mousePosition;
	sf::Vector2f mousePosView;

	sf::Clock delta;
	sf::Music music;
	sf::Sprite background;
	sf::Texture back_texture;
	sf::Texture gold;

	void displayLogo();
	void printMenu();

public:
	mainMenu(sf::RenderWindow*);

	const bool running() const;
	const bool is_started() const;
	void scanEvents();
	static bool exit;
	bool isLoading;

	sf::RenderWindow& getWindow() const;
	sf::Time getMusicOffset() const;

	void update();
	void render();
};


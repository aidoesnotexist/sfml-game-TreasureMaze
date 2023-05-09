#pragma once

#include <SFML/Graphics.hpp>	
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>	
#include <SFML/Network.hpp>
#include <array>

using namespace std;

class settingsMenu
{
	sf::RectangleShape background;
	sf::RectangleShape tabBackground;
	sf::Texture bounds;
	array<sf::RectangleShape, 2> tabBounds;
	sf::Texture mazeSquare;
	array<sf::Sprite, 4> mazeSquares;
	array<sf::RectangleShape, 2> differentiateLines;
	sf::Font mainFont;
	array<sf::Text, 2> titles;
	array<sf::Text, 6> settingsText;
	array<pair<sf::Text, bool>, 6> switchable;
	array<vector<sf::Text>, 6> switchableText;
	array<pair<sf::Text, bool>, 3> onOff;
	sf::Text Return;

	void initShapes();
	void initText();
public:
	settingsMenu();

	bool switchCheck(const sf::Vector2f&);

	void update(const sf::Vector2i&);
	void printSettings(sf::RenderTarget*);
};


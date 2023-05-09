#pragma once

#include <SFML/Graphics.hpp>	
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>	
#include <SFML/Network.hpp>
#include <iostream>

namespace Shape
{
	enum
	{
		Orange = 3,
		Red = 4,
		Blue = 4,
		Green = 6,
		Purple = 8,
		Yellow = 200
	};
}

namespace Texture
{
	struct texture
	{
		sf::Texture orange, red, blue,
			green, purple, yellow;
		texture()
		{
			orange.loadFromFile("textures\\orange.png");
			red.loadFromFile("textures\\red.png");
			blue.loadFromFile("textures\\blue.png");
			green.loadFromFile("textures\\green.png");
			purple.loadFromFile("textures\\purple.png");
			yellow.loadFromFile("textures\\yellow.png");
		}
	};
}

class Treasure
{
protected:
	sf::CircleShape treasure;
	float size = 50;
	sf::Color color;

	std::pair<int, int> matrixCoords;
	sf::Vector2f c_position;

	Texture::texture texture;
	bool breakMark;
public:
	Treasure();
	Treasure(const Treasure&);
	Treasure(const Treasure&, const int&);
	virtual ~Treasure() {};

	//Modifiers
	void setPosition(const std::pair<float, float>&);
	void setMatrixCoords(const std::pair<int, int>&);
	void set_breakMark();
	void remove_breakMark();
	//Accessors
	const sf::Vector2f& getPosition() const;
	const std::pair<int, int>& getMatrixCoords() const;
	const sf::Vector2f getC_position() const;
	const bool get_breakMark() const;
	const sf::Color get_originColor() const;

	void shake();
	void fall();
	void place_back();
	bool isAround(const Treasure&);
	bool contains(const sf::Vector2f&) const;
	void make_transparent();
	void make_original();

	sf::CircleShape* getTreasure();

	void noC_posCopy(const Treasure&);
	Treasure& operator= (const Treasure&);
	bool operator== (const Treasure&);
};

//Orange
class OrangeTreasure : public Treasure
{
	void initShape();
public:
	OrangeTreasure();
	~OrangeTreasure() override{};
};

//Red
class RedTreasure : public Treasure
{
	float size = 57.5f;
	void initShape();
public:
	RedTreasure();
	~RedTreasure() override {};
};

//Blue
class BlueTreasure : public Treasure
{
	void initShape();
public:
	BlueTreasure();
	~BlueTreasure() override {};
};

//Green
class GreenTreasure : public Treasure
{
	void initShape();
public:
	GreenTreasure();
	~GreenTreasure() override {};
};

//Purple
class PurpleTreasure : public Treasure
{
	void initShape();
public:
	PurpleTreasure();
	~PurpleTreasure() override {};
};

//Yellow
class YellowTreasure : public Treasure
{
	float size = 45;
	void initShape();
public:
	YellowTreasure();
	~YellowTreasure() override {};
};

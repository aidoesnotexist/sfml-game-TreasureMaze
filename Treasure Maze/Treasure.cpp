#include "Treasure.h"

Treasure::Treasure() : breakMark{ false }
{
    treasure.setOutlineThickness(1.5f);
    treasure.setOutlineColor(sf::Color(0, 0, 0, 128));
}

Treasure::Treasure(const Treasure& tr) : treasure{tr.treasure}, size{tr.size},
matrixCoords{ tr.matrixCoords }, c_position{ tr.c_position }, breakMark{ tr.breakMark }, 
color{ tr.color } {}

Treasure::Treasure(const Treasure& tr, const int&) : size{ tr.size },
c_position{ tr.c_position }, breakMark{ tr.breakMark }, color {tr.color}
{
    sf::Vector2f _tmp{tr.treasure.getPosition()};
    treasure = tr.treasure;
    treasure.setPosition(_tmp);
}

void Treasure::shake()
{
    static float coef_x = -1.f, coef_y = 1.f;
    treasure.move(coef_x * 3.f, coef_y * 3.f);
    coef_x *= -1; coef_y *= -1;
}

void Treasure::fall()
{
    treasure.setPosition(treasure.getPosition().x, treasure.getPosition().y + 15.f);
}

void Treasure::place_back()
{
    treasure.setPosition(c_position);
}

bool Treasure::isAround(const Treasure& tr)
{
    return (abs(tr.matrixCoords.first - this->matrixCoords.first) +
        abs(tr.matrixCoords.second - this->matrixCoords.second) == 1);
}

bool Treasure::contains(const sf::Vector2f& pos) const
{
    return (pos.x >= this->c_position.x - size && pos.x <= this->c_position.x + size &&
        pos.y >= this->c_position.y - size && pos.y <= this->c_position.y + size);
}

void Treasure::make_transparent()
{
    treasure.setFillColor(sf::Color(0, 0, 0, 128));
}

void Treasure::make_original()
{
    switch (treasure.getPointCount())
    {
    case Shape::Orange:
    {
        treasure.setFillColor(sf::Color(255, 135, 0));
        break;
    }
    case Shape::Red:
    {
        if (treasure.getRadius() < 35.f)
            treasure.setFillColor(sf::Color::Red);
        else
            treasure.setFillColor(sf::Color::Blue);
        break;
    }
    case Shape::Green:
    {
        treasure.setFillColor(sf::Color(0, 240, 0));
        break;
    }
    case Shape::Purple:
    {
        treasure.setFillColor(sf::Color(240, 0, 220));
        break;
    }
    case Shape::Yellow:
    {
        treasure.setFillColor(sf::Color(255, 255, 0));
        break;
    }
    }
}

sf::CircleShape* Treasure::getTreasure()
{
    return &treasure;
}

void Treasure::noC_posCopy(const Treasure& tr)
{
    treasure = tr.treasure;
    size = tr.size;
    breakMark = tr.breakMark;
    color = tr.color;
}

Treasure& Treasure::operator=(const Treasure& tr)
{
    if (this == &tr)
        return *this;

    treasure = tr.treasure;
    size = tr.size;
    c_position = tr.c_position;
    breakMark = tr.breakMark;
    color = tr.color;
    return *this;
}


bool Treasure::operator==(const Treasure& tr)
{
    return (treasure.getOrigin() == tr.treasure.getOrigin() && 
        size == tr.size && matrixCoords == tr.matrixCoords);
}

void Treasure::setPosition(const std::pair<float, float>& pos)
{
    this->c_position = sf::Vector2f(pos.first, pos.second);
    this->treasure.setPosition(c_position);
}

void Treasure::setMatrixCoords(const std::pair<int, int>& matrixCoords)
{
    this->matrixCoords = matrixCoords;
}

void Treasure::set_breakMark()
{
    this->breakMark = true;
}

void Treasure::remove_breakMark()
{
    this->breakMark = false;
}

const sf::Vector2f& Treasure::getPosition() const
{
    return treasure.getPosition();
}

const std::pair<int, int>& Treasure::getMatrixCoords() const
{
    return this->matrixCoords;
}

const sf::Vector2f Treasure::getC_position() const
{
    return c_position;
}

const bool Treasure::get_breakMark() const
{
    return breakMark;
}

const sf::Color Treasure::get_originColor() const
{
    return color;
}

//Orange
void OrangeTreasure::initShape()
{
    treasure.setRadius(size);
    treasure.setPointCount(Shape::Orange);
    treasure.setFillColor(sf::Color(255, 135, 0));
    treasure.setTexture(&texture.orange);
    treasure.setOrigin(size, size - 10.f);
}

OrangeTreasure::OrangeTreasure() : Treasure()
{
    color = sf::Color(255, 135, 0);
    initShape();
}

//Red
void RedTreasure::initShape()
{
    treasure.setRadius(size);
    treasure.setPointCount(Shape::Red);
    treasure.setFillColor(sf::Color(255, 0, 0));
    treasure.setTexture(&texture.red);
    treasure.setOrigin(size, size);
    treasure.rotate(45);
}

RedTreasure::RedTreasure() : Treasure()
{
    color = sf::Color(255, 0, 0);
    initShape();
}

//Blue
void BlueTreasure::initShape()
{
    treasure.setRadius(size);
    treasure.setPointCount(Shape::Blue);
    treasure.setFillColor(sf::Color(0, 0, 255));
    treasure.setTexture(&texture.blue);
    treasure.setOrigin(size, size);
}

BlueTreasure::BlueTreasure() : Treasure()
{
    color = sf::Color(0, 0, 255);
    initShape();
}

//Green
void GreenTreasure::initShape()
{
    treasure.setRadius(size);
    treasure.setPointCount(Shape::Green);
    treasure.setFillColor(sf::Color(0, 240, 0));
    treasure.setTexture(&texture.green);
    treasure.setOrigin(size, size);
}

GreenTreasure::GreenTreasure() : Treasure()
{
    color = sf::Color(0, 240, 0);
    initShape();
}

//Purple
void PurpleTreasure::initShape()
{
    treasure.setRadius(size);
    treasure.setPointCount(Shape::Purple);
    treasure.setFillColor(sf::Color(240, 0, 220));
    treasure.setTexture(&texture.purple);
    treasure.setOrigin(size, size);
}

PurpleTreasure::PurpleTreasure() : Treasure()
{
    color = sf::Color(240, 0, 220);
    initShape();
}

//Yellow
void YellowTreasure::initShape()
{
    treasure.setRadius(size);
    treasure.setPointCount(Shape::Yellow);
    treasure.setFillColor(sf::Color(255, 255, 0));
    treasure.setTexture(&texture.yellow);
    treasure.setOrigin(size, size);
}

YellowTreasure::YellowTreasure() : Treasure()
{
    color = sf::Color(255, 255, 0);
    initShape();
}

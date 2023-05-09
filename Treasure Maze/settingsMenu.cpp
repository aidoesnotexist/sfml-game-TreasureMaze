#include "settingsMenu.h"

void settingsMenu::initShapes()
{
	background.setSize(sf::Vector2f(1920.f, 1080.f));
	background.setFillColor(sf::Color(0, 0, 0, 155));
	background.setPosition(0.f, 0.f);
	tabBackground.setSize(sf::Vector2f(960.f, 800.f));
	tabBackground.setFillColor(sf::Color(0, 0, 0, 155));
	tabBackground.setPosition(480.f, 120.f);

	bounds.loadFromFile("textures\\gold.jpg");
	float h_pos = 120.f;
	for (auto& item : tabBounds)
	{
		item.setTexture(&bounds);
		item.setSize(sf::Vector2f(960.f, 8.f));
		item.setPosition(480.f, h_pos);
		h_pos += 800.f;
	}

	mazeSquare.loadFromFile("textures\\mazeSquare.png");
	for (auto& item : mazeSquares)
	{
		item.setTexture(mazeSquare);
		item.setScale(0.04, 0.04);
		item.rotate(45);
	}
	mazeSquares[0].setPosition(480.f, 105.f);
	mazeSquares[1].setPosition(1440.f, 105.f);
	mazeSquares[2].setPosition(480.f, 905.f);
	mazeSquares[3].setPosition(1440.f, 905.f);

	h_pos = 220.f;
	for (auto& item : differentiateLines)
	{
		item.setTexture(&bounds);
		item.setSize(sf::Vector2f(860.f, 2.f));
		item.setPosition(530.f, h_pos);
		h_pos += 425.f;
	}
}

void settingsMenu::initText()
{
	mainFont.loadFromFile("fonts\\mainFont.ttf");
	float h_pos = 250.f, h_pos_t = 155.f;
	for (int i = 0; i < settingsText.size(); ++i)
	{
		settingsText[i].setFont(mainFont);
		settingsText[i].setCharacterSize(35);
		settingsText[i].setFillColor(sf::Color(235, 200, 70));
		settingsText[i].setPosition(530.f, h_pos);
		if (i < 2)
		{
			titles[i].setFont(mainFont);
			titles[i].setCharacterSize(50);
			titles[i].setFillColor(sf::Color(235, 200, 70));
			titles[i].setPosition(530.f, h_pos_t);
			h_pos_t += 425.f;
		}
		h_pos += 75.f;
		if (i == 3) h_pos += 125.f;
	}
	titles[0].setString("Screen");
	titles[1].setString("Sound");
	settingsText[0].setString("Resolution");
	settingsText[1].setString("Window Mode");
	settingsText[2].setString("Frame Rate");
	settingsText[3].setString("Atnialiazing");
	settingsText[4].setString("Music");
	settingsText[5].setString("Sound FX");

	Return.setFont(mainFont);
	Return.setCharacterSize(50);
	Return.setFillColor(sf::Color(235, 200, 70));
	Return.setOrigin(225.f, 25.f);
	Return.setPosition(1050.f, 825.f);
	Return.setString("Return");

	for (int i = 0; i < switchableText.size(); ++i)
	{
		sf::Text _tmp;
		if (i == 0)
		{
			_tmp.setString("1920x1080");
			switchableText[i].push_back(_tmp);
		}
		else if (i == 1)
		{
			_tmp.setString("Windowed");
			switchableText[i].push_back(_tmp);
			_tmp.setString("Fullscreen");
			switchableText[i].push_back(_tmp);
		}
		else if (i == 2)
		{
			_tmp.setString("30");
			switchableText[i].push_back(_tmp);
			_tmp.setString("60");
			switchableText[i].push_back(_tmp);
			_tmp.setString("70");
			switchableText[i].push_back(_tmp);
		}
		else
		{
			_tmp.setString("Off");
			switchableText[i].push_back(_tmp);
			_tmp.setString("On");
			switchableText[i].push_back(_tmp);
		}
	}

	for (auto& item : switchable)
	{
		item.first.setFont(mainFont);
		item.first.setCharacterSize(35);
		item.first.setFillColor(sf::Color(235, 200, 70));
		item.second = true;
		if (&item - &switchable[0] == 0)
			item.first.setFillColor(sf::Color(75, 75, 75));
	}
	switchable[0].first.setOrigin(200.f, 17.5f);
	switchable[0].first.setPosition(1400.f, 270.f);
	switchable[0].first.setString(switchableText[0][0].getString());
	switchable[1].first.setOrigin(200.f, 17.5f);
	switchable[1].first.setPosition(1350.f, 345.f);
	switchable[1].first.setString(switchableText[1][1].getString());
	switchable[2].first.setOrigin(50.f, 17.5f);
	switchable[2].first.setPosition(1325.f, 425.f);
	switchable[2].first.setString(switchableText[2][2].getString());
	switchable[3].first.setOrigin(75.f, 17.5f);
	switchable[3].first.setPosition(1325.f, 505.f);
	switchable[3].first.setString(switchableText[3][1].getString());
	switchable[4].first.setOrigin(75.f, 17.5f);
	switchable[4].first.setPosition(1325.f, 700.f);
	switchable[4].first.setString(switchableText[4][1].getString());
	switchable[5].first.setOrigin(75.5f, 17.5f);
	switchable[5].first.setPosition(1325.f, 775.f);
	switchable[5].first.setString(switchableText[5][1].getString());
}

bool settingsMenu::switchCheck(const sf::Vector2f& mousePos)
{
	return Return.getGlobalBounds().contains(mousePos);
}

settingsMenu::settingsMenu()
{
	initShapes();
	initText();
}

void settingsMenu::update(const sf::Vector2i& mousePos)
{
	for (auto& item : switchable)
	{
		if (&item - &switchable[0] != 0)
		{
			{
				if (item.first.getGlobalBounds().contains(mousePos.x, mousePos.y))
					item.first.setScale(1.1, 1.1);
				else
					item.first.setScale(0.9, 0.9);
			}
		}
	}
	if (Return.getGlobalBounds().contains(mousePos.x, mousePos.y))
		Return.setScale(1.1, 1.1);
	else
		Return.setScale(0.9, 0.9);
}

void settingsMenu::printSettings(sf::RenderTarget* target)
{
	target->draw(background);
	target->draw(tabBackground);
	for (int i = 0; i < 2; ++i)
	{
		target->draw(tabBounds[i]);
		target->draw(differentiateLines[i]);
	}
	for (const auto& item : mazeSquares)
		target->draw(item);
	for (const auto& item : titles)
		target->draw(item);
	for (const auto& item : settingsText)
		target->draw(item);
	target->draw(Return);
	for (const auto& item : switchable)
		target->draw(item.first);
}

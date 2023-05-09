#include "Maze.h"

#define lineWidth 116
#define cellWidth 124

void Maze::initMaze()
{
	const float lineSize = 1920 / 1.935f;
	float wscale = 20, hscale = 864, widthScale = 0, corner = 7.5f;
	for (int i = 0; i < horizontalLine.size(); ++i)
	{
		horizontalLine[i].setSize(sf::Vector2f(lineSize, 8.f));
		horizontalLine[i].setPosition(864, wscale);
		horizontalLine[i].setTexture(&gold);
		wscale += 124;
		verticalLine[i].setSize(sf::Vector2f(lineSize + corner, 8.f));
		verticalLine[i].setPosition(hscale, 20);
		verticalLine[i].setTexture(&gold);
		verticalLine[i].setTextureRect(sf::IntRect(widthScale, 0, 0, 0));
		verticalLine[i].rotate(90);
		corner = 0;
		widthScale += 555.f;
		hscale += 124;
	}
}

void Maze::initInfoBoxes()
{
	float w_pos = 150.f, h_pos = 75.f;
	for (int i = 0; i < scoreOutLines.size(); ++i)
	{
		if (i <= 1)
		{
			scoreOutLines[i].setSize(sf::Vector2f(500.f, 8.f));
			scoreOutLines[i].setPosition(150.f, h_pos);
			scoreOutLines[i].setTexture(&gold);
			h_pos += 142.f;
		}
		else
		{
			scoreOutLines[i].setSize(sf::Vector2f(150.f, 8.f));
			scoreOutLines[i].setPosition(w_pos, 75.f);
			scoreOutLines[i].setTexture(&gold);
			scoreOutLines[i].rotate(90);
			w_pos += 500.f;
		}
	}
	scoreBackground.setSize(sf::Vector2f(500.f, 150.f));
	scoreBackground.setFillColor(sf::Color(0, 0, 0, 128));
	scoreBackground.setPosition(150.f, 75.f);

	float _w_pos = 150.f, _h_pos = 275.f;
	for (int i = 0; i < abilitiesOutLines.size(); ++i)
	{
		if (i <= 1)
		{
			abilitiesOutLines[i].setSize(sf::Vector2f(500.f, 8.f));
			abilitiesOutLines[i].setPosition(150.f, _h_pos);
			abilitiesOutLines[i].setTexture(&gold);
			_h_pos += 692.f;
		}
		else
		{
			abilitiesOutLines[i].setSize(sf::Vector2f(700.f, 8.f));
			abilitiesOutLines[i].setPosition(_w_pos, 275.f);
			abilitiesOutLines[i].setTexture(&gold);
			abilitiesOutLines[i].rotate(90);
			_w_pos += 500.f;
		}
	}
	abilitiesBackground.setSize(sf::Vector2f(500.f, 700.f));
	abilitiesBackground.setFillColor(sf::Color(0, 0, 0, 128));
	abilitiesBackground.setPosition(150.f, 275.f);
}

void Maze::initText()
{
	mainFont.loadFromFile("fonts\\mainFont.ttf");
	timerText.setFont(mainFont);
	timerText.setCharacterSize(50);
	timerText.setFillColor(sf::Color(235, 200, 70));
	timerText.setString("Time");
	timerText.setPosition(185.f, 90.f);
	scoreText.setFont(mainFont);
	scoreText.setCharacterSize(50);
	scoreText.setFillColor(sf::Color(235, 200, 70));
	scoreText.setString("Score");
	scoreText.setPosition(415.f, 90.f);

	score.setFont(mainFont);
	score.setCharacterSize(50);
	score.setFillColor(sf::Color(235, 200, 70));
	score.setOrigin(25, 25);
	score.setString('0');
	score.setPosition(485.f, 175.f);
}


void Maze::initVariables()
{
	isSwapping = false;
	isFalling = false;
	gapsFilled = true;;
	no_preCheck = false;
	scoreCounter = 0;

	mazeBackground.setSize(sf::Vector2f(1000.f, 1000.f));
	mazeBackground.setFillColor(sf::Color(0, 0, 0, 128));
	mazeBackground.setPosition(856.f, 21.f);

	gold.loadFromFile("textures\\gold.jpg");
}

void Maze::initAbilityShapes()
{
	float height_pos = 350.f, width_pos = 300.f;
	for (int i = 0; i < abilityShape.size(); ++i)
	{
		for (int j = 0; j < abilityShape[i].size(); ++j)
		{
			switch (i)
			{
			case 0:
			{
				abilityShape[i][j] = new OrangeTreasure{};
				abilityShape[i][j]->setMatrixCoords(make_pair(i, j));
				abilityShape[i][j]->getTreasure()->setOrigin(35.f, 35.f);
				abilityShape[i][j]->getTreasure()->setRadius(35);
				abilityShape[i][j]->setPosition(make_pair(width_pos, height_pos));
				abilityShape[i][j]->make_transparent();
				break;
			}
			case 1:
			{
				abilityShape[i][j] = new RedTreasure{};
				abilityShape[i][j]->setMatrixCoords(make_pair(i, j));
				abilityShape[i][j]->getTreasure()->setRadius(34);
				abilityShape[i][j]->getTreasure()->setOrigin(34.f, 34.f);
				abilityShape[i][j]->setPosition(make_pair(width_pos, height_pos));
				abilityShape[i][j]->make_transparent();
				break;
			}
			case 2:
			{
				abilityShape[i][j] = new BlueTreasure{};
				abilityShape[i][j]->setMatrixCoords(make_pair(i, j));
				abilityShape[i][j]->getTreasure()->setOrigin(35.f, 35.f);
				abilityShape[i][j]->getTreasure()->setRadius(35);
				abilityShape[i][j]->setPosition(make_pair(width_pos, height_pos));
				abilityShape[i][j]->make_transparent();
				break;
			}
			case 3:
			{
				abilityShape[i][j] = new GreenTreasure{};
				abilityShape[i][j]->setMatrixCoords(make_pair(i, j));
				abilityShape[i][j]->getTreasure()->setOrigin(35.f, 35.f);
				abilityShape[i][j]->getTreasure()->setRadius(35);
				abilityShape[i][j]->setPosition(make_pair(width_pos, height_pos));
				abilityShape[i][j]->make_transparent();
				break;
			}
			case 4:
			{
				abilityShape[i][j] = new PurpleTreasure{};
				abilityShape[i][j]->setMatrixCoords(make_pair(i, j));
				abilityShape[i][j]->getTreasure()->setOrigin(35.f, 35.f);
				abilityShape[i][j]->getTreasure()->setRadius(35);
				abilityShape[i][j]->setPosition(make_pair(width_pos, height_pos));
				abilityShape[i][j]->make_transparent();
				break;
			}
			case 5:
			{
				abilityShape[i][j] = new YellowTreasure{};
				abilityShape[i][j]->setMatrixCoords(make_pair(i, j));
				abilityShape[i][j]->getTreasure()->setOrigin(30.f, 30.f);
				abilityShape[i][j]->getTreasure()->setRadius(30);
				abilityShape[i][j]->setPosition(make_pair(width_pos, height_pos));
				abilityShape[i][j]->make_transparent();
				break;
			}
			}
			width_pos += 100.f;
			if (j == 2)
				width_pos = 300.f;
		}
		height_pos += 110.f;
	}
}

void Maze::fillMaze()
{
	for (int i = horizontalLine.size() - 2; i >= 0; --i)
		for (int j = verticalLine.size() - 2; j >= 0; --j)
			spawnTreasure(std::make_pair(i, j), 1012, 1);
	isFalling = true;
}

void Maze::spawnTreasure(std::pair<int, int> matrixCoords, const float& y_value, const int& clear_coef)
{
	switch (rand() % 6 + 1)
	{
		case 1:
		{
			Treasure* tr = new OrangeTreasure{};
			tr->setMatrixCoords(matrixCoords);
			tr->setPosition(std::make_pair(verticalLine[matrixCoords.first].getPosition().x + lineWidth / 2, 
				horizontalLine[matrixCoords.second].getPosition().y + 8.f + lineWidth / 2));
			tr->getTreasure()->setPosition(tr->getTreasure()->getPosition().x,
				tr->getTreasure()->getPosition().y * clear_coef - y_value);
			treasures[matrixCoords.first][matrixCoords.second] = tr;
			break;
		}
		case 2:
		{
			Treasure* tr = new RedTreasure{};
			tr->setMatrixCoords(matrixCoords);
			tr->setPosition(std::make_pair(verticalLine[matrixCoords.first].getPosition().x + lineWidth / 2,
				horizontalLine[matrixCoords.second].getPosition().y + 8.f + lineWidth / 2));
			tr->getTreasure()->setPosition(tr->getTreasure()->getPosition().x,
				tr->getTreasure()->getPosition().y * clear_coef - y_value);
			treasures[matrixCoords.first][matrixCoords.second] = tr;
			break;
		}
		case 3:
		{
			Treasure* tr = new BlueTreasure{};
			tr->setMatrixCoords(matrixCoords);
			tr->setPosition(std::make_pair(verticalLine[matrixCoords.first].getPosition().x + lineWidth / 2,
				horizontalLine[matrixCoords.second].getPosition().y + 8.f + lineWidth / 2));
			tr->getTreasure()->setPosition(tr->getTreasure()->getPosition().x,
				tr->getTreasure()->getPosition().y * clear_coef - y_value);
			treasures[matrixCoords.first][matrixCoords.second] = tr;
			break;
		}
		case 4:
		{
			Treasure* tr = new GreenTreasure{};
			tr->setMatrixCoords(matrixCoords);
			tr->setPosition(std::make_pair(verticalLine[matrixCoords.first].getPosition().x + lineWidth / 2,
				horizontalLine[matrixCoords.second].getPosition().y + 8.f + lineWidth / 2));
			tr->getTreasure()->setPosition(tr->getTreasure()->getPosition().x,
				tr->getTreasure()->getPosition().y * clear_coef - y_value);
			treasures[matrixCoords.first][matrixCoords.second] = tr;
			break;
		}
		case 5:
		{
			Treasure* tr = new PurpleTreasure{};
			tr->setMatrixCoords(matrixCoords);
			tr->setPosition(std::make_pair(verticalLine[matrixCoords.first].getPosition().x + lineWidth / 2,
				horizontalLine[matrixCoords.second].getPosition().y + 8.f + lineWidth / 2));
			tr->getTreasure()->setPosition(tr->getTreasure()->getPosition().x, 
				tr->getTreasure()->getPosition().y * clear_coef - y_value);
			treasures[matrixCoords.first][matrixCoords.second] = tr;
			break;
		}
		case 6:
		{
			Treasure* tr = new YellowTreasure{};
			tr->setMatrixCoords(matrixCoords);
			tr->setPosition(std::make_pair(verticalLine[matrixCoords.first].getPosition().x + lineWidth / 2,
				horizontalLine[matrixCoords.second].getPosition().y + 8.f + lineWidth / 2));
			tr->getTreasure()->setPosition(tr->getTreasure()->getPosition().x, 
				tr->getTreasure()->getPosition().y * clear_coef - y_value);
			treasures[matrixCoords.first][matrixCoords.second] = tr;
			break;
		}
	}
}

void Maze::swap(Treasure* first, Treasure* second)
{
	Treasure* tmp = new Treasure{*first};
	*first = *second;
	*second = *tmp;
	delete tmp;
	tmp = nullptr;

	pair<float, float> _tmpPos{ first->getPosition().x, first->getPosition().y };
	first->setPosition(std::make_pair(second->getPosition().x, second->getPosition().y));
	second->setPosition(_tmpPos);
}

void Maze::collide(Treasure& first, Treasure& second)
{
	isSwapping = true;
	if (first.getC_position().x > second.getC_position().x)
	{
		if (first.getPosition().x <= second.getC_position().x)
		{
			first.place_back();
			second.place_back();
			isSwapping = false;
		}
		else
		{
			first.getTreasure()->move(-10.f, 0.f);
			second.getTreasure()->move(10.f, 0.f);
		}
	}
	if (first.getC_position().x < second.getC_position().x)
	{
		if (first.getPosition().x >= second.getC_position().x)
		{
			first.place_back();
			second.place_back();
			isSwapping = false;
		}
		else
		{
			first.getTreasure()->move(10.f, 0.f);
			second.getTreasure()->move(-10.f, 0.f);
		}
	}
	if (first.getC_position().y > second.getC_position().y)
	{
		if (first.getPosition().y <= second.getC_position().y)
		{
			first.place_back();
			second.place_back();
			isSwapping = false;
		}
		else
		{
			first.getTreasure()->move(0.f, -10.f);
			second.getTreasure()->move(0.f, 10.f);
		}
	}
	if (first.getC_position().y < second.getC_position().y)
	{
		if (first.getPosition().y >= second.getC_position().y)
		{
			first.place_back();
			second.place_back();
			isSwapping = false;
		}
		else
		{
			first.getTreasure()->move(0.f, 10.f);
			second.getTreasure()->move(0.f, -10.f);
		}
	}
}

void Maze::findLineUps()
{
	for (int i = 0; i < linesLimit - 1; ++i)
	{
		int start = 0;
		while (start < linesLimit - 3)
		{
			int counter = 1;
			while (start + counter < linesLimit - 1 &&
				treasures[i][start]->getTreasure()->getFillColor() ==
				treasures[i][start + counter]->getTreasure()->getFillColor())
					++counter;

			if (counter >= 3) 
			{
				for (int k = 0; k < counter; ++k) 
				{
					treasures[i][start + k]->set_breakMark();
					isMoving = true;
					gapsFilled = false;
				}
			}
			start += counter;
		}
	}
	for (int j = 0; j < linesLimit - 1; ++j)
	{
		int start = 0;
		while (start < 6) 
		{
			int counter = 1;
			while (start + counter < linesLimit - 1 &&
				treasures[start][j]->getTreasure()->getFillColor() ==
				treasures[start + counter][j]->getTreasure()->getFillColor())
			{
				counter++;
			}
			if (counter >= 3) 
			{
				for (int k = 0; k < counter; ++k) 
				{
					treasures[start + k][j]->set_breakMark();
					isMoving = true;
					gapsFilled = false;
				}
			}
			start += counter;
		}
	}
	if (!isMoving)
		no_preCheck = true;
	else
	{
		sounds.stoneBreak.play();
		scoreCounter += 100;
		score.setString(std::to_string(scoreCounter));
	}
}

void Maze::defineFallingTrack()
{
	for(int i = treasures.size() - 1; i >= 0; --i)
		for(int j = treasures[i].size() - 1; j >= 0; --j)
			if(treasures[i][j]->get_breakMark())
				for(int k = j; k >= 0; --k)
					if (!treasures[i][k]->get_breakMark())
					{
						treasures[i][j]->noC_posCopy(*treasures[i][k]);
						treasures[i][k]->set_breakMark();
						break;
					}
}

void Maze::fill_theGaps()
{
	for(int i = 0; i < treasures.size(); ++i)
		for(int j = 0; j < treasures[i].size(); ++j)
			if (treasures[i][j]->get_breakMark() && !treasures[i][j + 1]->get_breakMark())
			{
				float scale = 124.f;
				for (int k = j; k >= 0; --k)
				{
					spawnTreasure(make_pair(i, k), scale, 0);
					treasures[i][k]->remove_breakMark();
					scale += 124.f;
				}
			}
	gapsFilled = true;
}

void Maze::descent()
{
	isMoving = false;
	isFalling = false;
	for(int i = 0; i < treasures.size(); ++i)
		for (int j = 0; j < treasures[i].size(); ++j)
		{
			if (treasures[i][j]->getTreasure()->getPosition().y < treasures[i][j]->getC_position().y)
			{
				treasures[i][j]->fall();
				isMoving = true;
				isFalling = true;
			}
			else
				treasures[i][j]->place_back();
		}

}

void Maze::printMaze(sf::RenderTarget* target)
{
	for (int i = 0; i < linesLimit; ++i)
	{
		target->draw(horizontalLine[i]);
		target->draw(verticalLine[i]);
	}
}

void Maze::printTreasures(sf::RenderTarget* target)
{
	for (array<Treasure*, linesLimit - 1>& item : treasures)
		for(Treasure* treasure : item)
			if(treasure != nullptr)
				target->draw(*treasure->getTreasure());
}

void Maze::printAbilities(sf::RenderTarget* target)
{
	for (const auto& item : abilityShape)
		for (const auto& ability : item)
			if(ability != nullptr)
				target->draw(*ability->getTreasure());
}

void Maze::start()
{
	initVariables();
	initMaze();
	initText();
	initAbilityShapes();
	initInfoBoxes();
	fillMaze();
}

Maze::~Maze()
{
	for (auto& item : treasures)
		for (auto& treasure : item)
			delete treasure;

	for (auto& item : abilityShape)
		for (auto& ability : item)
			delete ability;
}

void Maze::printInfoBoxes(sf::RenderTarget* target)
{
	target->draw(mazeBackground);
	target->draw(scoreBackground);
	target->draw(abilitiesBackground);
	for (const auto& item : scoreOutLines)
		target->draw(item);
	for (const auto& item : abilitiesOutLines)
		target->draw(item);
}

void Maze::printText(sf::RenderTarget* target)
{
	target->draw(timerText);
	target->draw(scoreText);
	target->draw(score);
}

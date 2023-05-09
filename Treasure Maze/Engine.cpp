#include "Engine.h"

void Engine::initVariables(const sf::Time& musicOffset)
{
	backTexture.loadFromFile("textures\\background.jpg");
	background.setTexture(backTexture);

	music.openFromFile("sounds\\backMusic.ogg");
	music.setPlayingOffset(musicOffset);
	music.setLoop(true);
}

void Engine::init_inGameMenu()
{
	gold.loadFromFile("textures\\gold.jpg");
	mazeSquare.loadFromFile("textures\\mazeSquare.png");
	in_gameMenuBackground.setSize(sf::Vector2f(1920.f, 1080.f));
	in_gameMenuBackground.setFillColor(sf::Color(0, 0, 0, 200));
	in_gameMenuBackground.setPosition(sf::Vector2f(0.f, 0.f));
	innerBackground.setSize(sf::Vector2f(500.f, 400.f));
	innerBackground.setFillColor(sf::Color(0, 0, 0, 200));
	innerBackground.setPosition(sf::Vector2f(710.f, 340.f));

	float h_scale = 340.f;
	for (int i = 0; i < 2; ++i)
	{
		in_gameMenuBounds[i].setTexture(&gold);
		in_gameMenuBounds[i].setSize(sf::Vector2f(500.f, 8.f));
		in_gameMenuBounds[i].setPosition(sf::Vector2f(710.f, h_scale));
		h_scale += 400.f;
	}
	for (int i = 0; i < 4; ++i)
	{
		mazeSquares[i].setTexture(mazeSquare);
		mazeSquares[i].setScale(0.04, 0.04);
		mazeSquares[i].rotate(45);
	}
	mazeSquares[0].setPosition(710.f, 327.5f);
	mazeSquares[1].setPosition(1210.f, 327.5f);
	mazeSquares[2].setPosition(710.f, 727.5f);
	mazeSquares[3].setPosition(1210.f, 727.5f);
	menuFont.loadFromFile("fonts\\mainFont.ttf");
	for (int i = 0; i < menuText.size(); ++i)
	{
		menuText[i].setFont(menuFont);
		menuText[i].setCharacterSize(50);
		menuText[i].setFillColor(sf::Color(235, 200, 70));
	}
	menuText[0].setString("Continue");
	menuText[0].setOrigin(160, 25);
	menuText[0].setPosition(sf::Vector2f(960.f, 425.f));
	menuText[1].setString("Settings");
	menuText[1].setOrigin(150, 25);
	menuText[1].setPosition(sf::Vector2f(960.f, 550.f));
	menuText[2].setString("Exit to menu");
	menuText[2].setOrigin(235, 25);
	menuText[2].setPosition(sf::Vector2f(960.f, 675.f));
}

void Engine::update_inGameMenu()
{
	for (int i = 0; i < menuText.size(); ++i)
		zoomButton(menuText[i]);
	mousePosition = sf::Mouse::getPosition(*window);
	if (_event.type == sf::Event::MouseButtonPressed)
	{
		_event.type = sf::Event::MouseButtonReleased;
		mousePosView = window->mapPixelToCoords(mousePosition);
		if (menuText[0].getGlobalBounds().contains(mousePosView))
			paused = false;
		else if (menuText[1].getGlobalBounds().contains(mousePosView))
			;//
		else if (menuText[2].getGlobalBounds().contains(mousePosView))
			exit_toMenu = true;
	}
}

void Engine::zoomButton(sf::Text& button)
{
	if (button.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
		button.setScale(1.1, 1.1);
	else
		button.setScale(0.9, 0.9);
}

void Engine::print_inGameMenu()
{
	window->draw(in_gameMenuBackground);
	window->draw(innerBackground);
	for (int i = 0; i < 4; ++i)
	{
		if(i < 2)
			window->draw(in_gameMenuBounds[i]);
		window->draw(mazeSquares[i]);
	}
	for (int i = 0; i < menuText.size(); ++i)
		window->draw(menuText[i]);
}

void Engine::updateMousePosition()
{
	this->mousePosition = sf::Mouse::getPosition(*this->window);
	if (_event.type == sf::Event::MouseButtonPressed)
	{
		_event.type = sf::Event::EventType::MouseButtonReleased;
		if (_event.key.code == sf::Mouse::Left)
		{
			if (!maze.isSwapping && !maze.isMoving)
			{
				this->mousePosView = this->window->mapPixelToCoords(this->mousePosition);
				++clicks;
			}
		}
		else if(_event.key.code == sf::Mouse::Right)
		{
			if (clickedTreasure != nullptr)
			{
				clickedTreasure->place_back();
				clickedTreasure = nullptr;
			}
			clicks = 0;
		}
	}
}

void Engine::updateTreasures()
{
	if(!maze.isFalling && !maze.isMoving && !maze.no_preCheck)
		maze.findLineUps();

	if (maze.isMoving)
	{
		if (!maze.gapsFilled)
		{
			maze.defineFallingTrack();
			maze.fill_theGaps();
		}
	}
	if (maze.isFalling || maze.isMoving)
		maze.descent();
		
	if (clickedTreasure != nullptr && !maze.isSwapping)
		clickedTreasure->shake();

	if (swap_back)
	{
		clicks = 0;
		maze.collide(*swapBack, *clickedTreasure);
		if (!maze.isSwapping)
		{
			maze.swap(swapBack, clickedTreasure);
			clickedTreasure = nullptr;
			swapBack = nullptr;
			swap_back = false;
		}

	}
	if (clicks == 1 && !maze.isMoving)
	{
		for (int i = 0; i < maze.treasures.size(); ++i)
			for (int j = 0; j < maze.treasures[i].size(); ++j)
				if (maze.treasures[i][j]->contains(mousePosView) && clickedTreasure == nullptr)
					clickedTreasure = maze.treasures[i][j];

		if (clickedTreasure == nullptr)
			clicks = 0;
	}
	if (clicks == 2 && !maze.isMoving)
	{
		for(int i = 0; i < maze.treasures.size(); ++i)
			for (int j = 0; j < maze.treasures.size(); ++j)
				if (maze.treasures[i][j]->contains(mousePosView) &&
					maze.treasures[i][j]->isAround(*clickedTreasure))
				{
					if(!maze.isSwapping) 
						clickedTreasure->place_back();
					maze.collide(*clickedTreasure, *maze.treasures[i][j]);

					if (!maze.isSwapping)
					{
						clickedColor = clickedTreasure->get_originColor();
						maze.swap(clickedTreasure, maze.treasures[i][j]);
						maze.findLineUps();
						if (!maze.isMoving)
						{
							swapBack = maze.treasures[i][j];
							++swap_back;
						}
						else
						{
							addAbility();
							updateAbilities();
							clickedTreasure = nullptr;
							clicks = 0;
							timer.addTime(2);
							maze.no_preCheck = false;
							goto label;
						}
					}
				}
		if (!maze.isSwapping && swapBack == nullptr)
		{
			clickedTreasure->place_back();
			clicks = 0;
			clickedTreasure = nullptr;
			maze.isSwapping = false;
		}
	}
label:;
}

void Engine::addAbility()
{
	if (abilityProgression.empty())
		abilityProgression.push_back(clickedColor);
	else if (abilityProgression.size() == 3)
	{
		abilityProgression.clear();
		abilityProgression.push_back(clickedColor);
	}
	else
	{
		if (clickedColor == abilityProgression[0])
			abilityProgression.push_back(clickedColor);
		else
		{
			abilityProgression.clear();
			abilityProgression.push_back(clickedColor);
		}
	}
}

void Engine::updateAbilities()
{
	for (int i = 0; i < maze.abilityShape.size(); ++i)
		for (int j = 0; j < maze.abilityShape[i].size(); ++j)
		{
			if (abilityProgression.size() >= j + 1 &&
				maze.abilityShape[i][j]->get_originColor() == abilityProgression[j])
				maze.abilityShape[i][j]->make_original();
			else
				maze.abilityShape[i][j]->make_transparent();
		}
}

void Engine::loadingScreen()
{
	this->window->setActive(true);
	mazeSquare.loadFromFile("textures\\mazeSquare.png");
	sf::Sprite squares[4];
	float width = 1750.f;
	for (int i = 0; i < 4; ++i)
	{
		squares[i].setTexture(mazeSquare);
		squares[i].setScale(0.05, 0.05);
		squares[i].setColor(sf::Color(235, 200, 70, 0));
		if (i < 2)
			squares[i].setPosition(width, 900.f);
		else
			squares[i].setPosition(width, 950.f);
		if (i == 1) width = 1750.f;
		else width += 50.f;
	}
	while (!resource_loaded)
	{
		randSquare(squares);
		this->window->clear();
		for (int i = 0; i < 4; ++i)
			this->window->draw(squares[i]);
		this->window->display();
	}
	window->setActive(false);
}

void Engine::randSquare(sf::Sprite squares[])
{
	static sf::Clock frame;
	static int prev_index = 0;
	if (frame.getElapsedTime() >= sf::seconds(0.25))
	{
		int randIndex = rand() % 4;
		while (randIndex == prev_index)
			randIndex = rand() % 4;
		for (int i = 0; i < 4; ++i)
		{
			if (i != randIndex)
				squares[i].setColor(sf::Color(squares[i].getColor().r,
					squares[i].getColor().g, squares[i].getColor().b, 0));
			else
				squares[i].setColor(sf::Color(235, 200, 70, 225));
		}
		prev_index = randIndex;
		frame.restart();
	}
}

Engine::Engine(sf::RenderWindow* window, const sf::Time& musicOffset)
	: swap_back{ false }, exit_toMenu{ false }, paused{ false },
	resource_loaded{ false }, window {window}
{
	this->window->setActive(false);
	music.stop();
	sf::Thread sub_thread(std::bind(&Engine::loadingScreen, this));
	sub_thread.launch();
	initVariables(musicOffset);
	init_inGameMenu();
	maze.start();
	resource_loaded = true;
	music.play();
	this->window->setActive(true);
}

sf::RenderWindow& Engine::getWindow() const
{
	return *window;
}

const bool Engine::running() const
{
	return this->window->isOpen();
}

void Engine::scanEvents()
{
	while (window->pollEvent(_event))
	{
		switch (_event.type)
		{
		case sf::Event::Closed:
		{
			window->close();
			break;
		}
		case sf::Event::KeyPressed:
		{
			_event.type = sf::Event::KeyReleased;
			if (_event.key.code == sf::Keyboard::Escape && !paused)
			{
				paused = true;
				break;
			}
			else if (_event.key.code == sf::Keyboard::Escape && paused)
			{
				paused = false;
				break;
			}
		}
		case sf::Event::LostFocus:
		{
			paused = true;
			break;
		}
		}
	}
}

void Engine::update()
{
	scanEvents();
	if (!paused)
	{
		updateMousePosition();
		timer.updateTimer();
		updateTreasures();
	}
	else
		update_inGameMenu();
}

void Engine::render()
{
	//Clear old frame
	this->window->clear();

	//Load frame
	window->draw(background);
	maze.printInfoBoxes(this->window);
	maze.printMaze(this->window);
	maze.printTreasures(this->window);
	maze.printAbilities(this->window);
	maze.printText(this->window);
	timer.printTimer(this->window);
	if (paused)
		print_inGameMenu();

	//Display frame
	this->window->display();
}

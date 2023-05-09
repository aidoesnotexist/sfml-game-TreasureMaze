#include "mainMenu.h"

bool mainMenu::exit = 0;

void mainMenu::initVariables()
{
	back_texture.loadFromFile("textures\\background.jpg");
	background.setTexture(back_texture);
	gold.loadFromFile("textures\\gold.jpg");

	music.openFromFile("sounds\\backMusic.ogg");
	music.setLoop(true);
	music.play();
}

void mainMenu::initWindow()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	resolution.width = 1920.f, resolution.height = 1080.f;

	window = new sf::RenderWindow(resolution, "Treasure Maze", sf::Style::Fullscreen, settings);
	window->setFramerateLimit(70);
}

void mainMenu::initText()
{
	mainFont.loadFromFile("fonts\\mainFont.ttf");
	clickAnywhere.setFont(mainFont);

	clickAnywhere.setCharacterSize(50);
	clickAnywhere.setOrigin(575.f, 25.f);
	clickAnywhere.setFillColor(sf::Color(235, 200, 70));
	clickAnywhere.setPosition(sf::Vector2f(960.f, 900.f));
	clickAnywhere.setString("CLICK ANYWHERE TO START");

	for (int i = 0; i < 5; ++i)
	{
		menuText[i].setFont(mainFont);
		menuText[i].setCharacterSize(50);
		menuText[i].setFillColor(sf::Color(235, 200, 70));
	}
	menuText[0].setString("New Game");
	menuText[0].setOrigin(200, 25);
	menuText[0].setPosition(sf::Vector2f(960.f, 450.f));
	menuText[1].setString("Controls");
	menuText[1].setOrigin(175, 25);
	menuText[1].setPosition(sf::Vector2f(960.f, 575.f));
	menuText[2].setString("Settings");
	menuText[2].setOrigin(165, 25);
	menuText[2].setPosition(sf::Vector2f(960.f, 700.f));
	menuText[3].setString("Extras");
	menuText[3].setOrigin(130, 25);
	menuText[3].setPosition(sf::Vector2f(960.f, 825.f));
	menuText[4].setString("Quit");
	menuText[4].setOrigin(90, 25);
	menuText[4].setPosition(sf::Vector2f(960.f, 937.5f));
}

void mainMenu::initMenuOutLines()
{
	float verticalScale = 500.f;
	float vertical_logoScale = 75.f;
	float horizontal_logoScale = 615.f;
	for (array<sf::RectangleShape, 4>::iterator it =
		horizontalMenuOutlines.begin(); it != horizontalMenuOutlines.end(); ++it)
	{
		it->setTexture(&gold);
		it->setSize(sf::Vector2f(550.f, 4.f));
		it->setPosition(sf::Vector2f(655.f, verticalScale));
		verticalScale += 125.f;
	}
	for (array<sf::RectangleShape, 2>::iterator it =
		horizontalLogoOutlines.begin(); it != horizontalLogoOutlines.end(); ++it)
	{
		it->setTexture(&gold);
		it->setSize(sf::Vector2f(650.f, 12.f));
		it->setPosition(sf::Vector2f(615.f, vertical_logoScale));
		vertical_logoScale += 262.5f;
	}

	for (array<sf::RectangleShape, 2>::iterator it =
		verticalLogoOutlines.begin(); it != verticalLogoOutlines.end(); ++it)
	{
		it->setTexture(&gold);
		it->setSize(sf::Vector2f(275.f, 12.f));
		it->setPosition(sf::Vector2f(horizontal_logoScale, 75.f));
		it->rotate(90);
		horizontal_logoScale += 650.f;
	}
	menuBackground.setSize(sf::Vector2f(660.f, 650.f));
	menuBackground.setFillColor(sf::Color(0, 0, 0, 90));
	menuBackground.setPosition(sf::Vector2f(605.f, 350.f));
	logoBackground.setSize(sf::Vector2f(650.f, 275.f));
	logoBackground.setFillColor(sf::Color(0, 0, 0, 150));
	logoBackground.setPosition(sf::Vector2f(615.f, 75.f));

	for (int i = 0; i < 2; ++i)
	{
		mazeSquare[i].setTexture(maze);
		mazeSquare[i].setScale(0.05, 0.05);
	}
	mazeSquare[0].setPosition(sf::Vector2f(590.f, 975.f));
	mazeSquare[1].setPosition(sf::Vector2f(1250.f, 975.f));
}

void mainMenu::initGameLogo()
{
	treasureMaze_f.loadFromFile("fonts\\maze.ttf");
	treasureMaze.setFont(treasureMaze_f);
	treasureMaze.setCharacterSize(150);
	treasureMaze.setLineSpacing(0.6);
	treasureMaze.setScale(0.9, 0.9);
	treasureMaze.setFillColor(sf::Color(235, 200, 90));
	treasureMaze.setString("Treasure\n       Maze");

	maze.loadFromFile("textures\\mazeSquare.png");
	double scale_scale = 0.035;
	for (int i = 0; i < 3; ++i)
	{
		square[i].setTexture(maze);
		square[i].setOrigin(315.f, 330.f);
		square[i].setScale(scale_scale, scale_scale);
		scale_scale += 0.025;
	}
}

void mainMenu::setLogoPosition(const sf::Vector2f& pos)
{
	treasureMaze.setPosition(pos);
	float pos_scale = pos.x + 25.f;
	for (int i = 0; i < 3; ++i)
	{
		square[i].setPosition(pos_scale, pos.y + 185.f);
		pos_scale += 70.f;
		if (i == 1)
			pos_scale += 20.f;
	}
}

void mainMenu::updateMousePosition()
{
	if (isClickedAnywhere)
	{
		mousePosition = sf::Mouse::getPosition(*window);
		if (_event.type == sf::Event::MouseButtonPressed)
		{
			_event.type = sf::Event::EventType::MouseButtonReleased;
			if (_event.key.code == sf::Mouse::Left)
				mousePosView = window->mapPixelToCoords(mousePosition);
		}
	}
}

void mainMenu::updateMenu()
{
	for (int i = 0; i < 5; ++i)
		zoomButton(menuText[i]);
	if (menuText[0].getGlobalBounds().contains(mousePosView))
		gameStarted = true;
	else if (menuText[1].getGlobalBounds().contains(mousePosView))
		;//
	else if (menuText[2].getGlobalBounds().contains(mousePosView))
		settingsOpened = true;
	else if (menuText[3].getGlobalBounds().contains(mousePosView))
		;//
	else if (menuText[4].getGlobalBounds().contains(mousePosView))
		exit = true;
}

void mainMenu::zoomButton(sf::Text& button)
{
	if (button.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
		button.setScale(1.1, 1.1);
	else
		button.setScale(0.9, 0.9);
}

void mainMenu::startUp()
{
	if (delta.getElapsedTime() >= sf::seconds(0.025))
	{
		delta.restart();
		static double scale = 1;
		static int _operator = -1;
		clickAnywhere.setScale(scale, scale);
		scale += _operator * 0.01;
		if (scale <= 0.75 || scale >= 1.)
			_operator *= -1;
	}
	if (_event.type == sf::Event::MouseButtonPressed &&
		_event.key.code == sf::Mouse::Left)
	{
		_event.type = sf::Event::EventType::MouseButtonReleased;
		isClickedAnywhere = true;
	}
}

void mainMenu::displayLogo()
{
	sf::Font powered_by_font;
	powered_by_font.loadFromFile("fonts\\powered_by.ttf");
	sf::Text powered_by;
	powered_by.setFont(powered_by_font);
	powered_by.setCharacterSize(50);
	powered_by.setPosition(sf::Vector2f(990.f, 400.f));
	powered_by.setFillColor(sf::Color(255, 255, 255, 225));
	powered_by.setString("powered by");
	sf::Texture logo_t;
	logo_t.loadFromFile("textures\\sfml_logo.png");
	sf::Sprite logo(logo_t);
	logo.setOrigin(1100, 425);
	logo.setScale(0.5, 0.5);
	logo.setPosition(sf::Vector2f(960.f, 540.f));
	sf::sleep(sf::seconds(2));
	window->draw(logo);
	window->draw(powered_by);
	window->display();
	sf::sleep(sf::seconds(5));
	window->display();
	window->clear();
	sf::sleep(sf::seconds(2));

	setLogoPosition(sf::Vector2f(640.f, 360.f));
	for (int i = 0; i < 3; ++i)
		window->draw(square[i]);
	window->draw(treasureMaze);
	window->display();
	sf::sleep(sf::seconds(5));

	while (treasureMaze.getPosition().y >= 75.f)
	{
		setLogoPosition(sf::Vector2f(640.f, treasureMaze.getPosition().y - 10.f));
		window->draw(treasureMaze);
		for (int i = 0; i < 3; ++i)
			window->draw(square[i]);
		window->display();
		window->clear();
	}
	treasureMaze.setStyle(sf::Text::Bold);
	treasureMaze.setOutlineColor(sf::Color(235, 200, 70));
	treasureMaze.setFillColor(sf::Color(0, 0, 0, 255));
	treasureMaze.setOutlineThickness(2);

	mainMenu::isLoading = false;
	window->setActive(false);
}

void mainMenu::setLogo()
{
	setLogoPosition(sf::Vector2f(640.f, 75.f));
	treasureMaze.setStyle(sf::Text::Bold);
	treasureMaze.setOutlineColor(sf::Color(235, 200, 70));
	treasureMaze.setFillColor(sf::Color(0, 0, 0, 255));
	treasureMaze.setOutlineThickness(2);
}

void mainMenu::printMenu()
{
	window->draw(menuBackground);
	for (const auto& item : horizontalMenuOutlines)
		window->draw(item);
	for (const auto& item : horizontalLogoOutlines)
		window->draw(item);
	for (const auto& item : verticalLogoOutlines)
		window->draw(item);
	window->draw(treasureMaze);
	for (int i = 0; i < 3; ++i)
		window->draw(square[i]);
	for (const auto& item : menuText)
		window->draw(item);
	for (int i = 0; i < 2; ++i)
		window->draw(mazeSquare[i]);
}

mainMenu::mainMenu(sf::RenderWindow* window) :
	isClickedAnywhere{ false }, window{ window },
	isLoading{ true }, settingsOpened{ false }
{
	initGameLogo();
	if (window == nullptr)
	{
		initWindow();
		this->window->display();
	}
	else
	{
		setLogo();
		isLoading = false;
	}
	initVariables();
	initText();
	initMenuOutLines();
}

const bool mainMenu::running() const
{
	return window->isOpen();
}

const bool mainMenu::is_started() const
{
	return gameStarted;
}

void mainMenu::scanEvents()
{
	while (this->window->pollEvent(_event));
	{
		switch (this->_event.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		}
	}
}

sf::RenderWindow& mainMenu::getWindow() const
{
	return *window;
}

sf::Time mainMenu::getMusicOffset() const
{
	return music.getPlayingOffset();
}

void mainMenu::update()
{
	updateMousePosition();
	if (!settingsOpened)
	{
		scanEvents();
		updateMenu();
	}
	else
		settings.update(mousePosition);
	if (settingsOpened && settings.switchCheck(mousePosView))
		settingsOpened = false;
}

void mainMenu::render()
{
	if (isLoading)
	{
		static bool _tmp = true;
		if (_tmp)
		{
			window->display();
			displayLogo();
			_tmp = false;
		}
	}
	else
	{
		window->clear();
		window->draw(background);
		if (!isClickedAnywhere)
		{
			window->draw(logoBackground);
			for (int i = 0; i < 2; ++i)
				window->draw(horizontalLogoOutlines[i]);
			window->draw(treasureMaze);
			for (int i = 0; i < 3; ++i)
				window->draw(square[i]);
			window->draw(clickAnywhere);
			startUp();
		}
		else
		{
			window->draw(logoBackground);
			printMenu();
			if (settingsOpened)
				settings.printSettings(window);
		}

		window->display();
	}
}

#include <iostream>
#include "Engine.h"
#include "mainMenu.h"
int main()
{
	srand(static_cast<unsigned>(time(NULL)));
	sf::RenderWindow* window{ nullptr };
	
	sf::Time musicOffset = sf::Time();

_start:;
	{
		mainMenu menu(window);
		while (menu.running())
		{
			if (mainMenu::exit)
				goto _end;
			if (menu.is_started())
			{
				window = &menu.getWindow();
				musicOffset = menu.getMusicOffset();
				break;
			}
			menu.update();
			menu.render();
		}
	}
	{
		Engine engine(window, musicOffset);
		while (engine.running())
		{
			engine.update();
			engine.render();
			if (engine.exit_toMenu)
			{
				window = &engine.getWindow();
				goto _start;
			}
		}
	}
_end:;

	delete window;
	return 0;
}
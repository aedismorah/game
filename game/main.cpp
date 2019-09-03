#include "map.h"
#include "menu.h"

int main()
{
	Aedis::Map* map = new Aedis::Map("map.tmx", "tileset.png");
	Aedis::Menu* menu = new Aedis::Menu("setup/images", "setup/sounds", "aedis.ttf");

	sf::RenderWindow window(sf::VideoMode(1900, 1000), "Aedis");
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear();
		menu->handle(window);
		menu->draw(window);
		window.display();
	}

	return 0;
}
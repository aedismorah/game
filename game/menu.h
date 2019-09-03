#pragma once

#include "includes.h"

namespace Aedis
{
	//check if somw functions or declarations can be cut or replaced with lambdas
	class Menu
	{
	public:
		Menu(std::string imagesFilename, std::string musicFilename, std::string fontname);
		~Menu();
		void loadImagesFromFile(std::string filename, std::string fontname); //loads background + options  // maybe doan animation when the button is being hovered
		void loadMusicFromFile(std::string filename); //loads background music + music played when you hover across option
		void setOptionAction(unsigned optionNumber); //set what we do, when a certain option is pressed
		void handle(sf::RenderWindow& window);
		void draw(sf::RenderWindow& window);
	private:
		sf::Music backgroundMusic;
		sf::SoundBuffer onHoverSoundBuffer;
		sf::Sound* onHoverSound;
		bool playOnHover;

		sf::Texture backgroundTexture;
		sf::Sprite backgroundSprite;

		sf::Font font;
		sf::Text text;
		std::vector<sf::Text> optionsText;

		unsigned verticalPadding;
		unsigned horizontalPadding;
		unsigned verticalMargin;
		unsigned horizontalMargin;
	};
}
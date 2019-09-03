#include "menu.h"

namespace Aedis
{
	Menu::Menu(std::string imagesFilename, std::string musicFilename, std::string fontname) 
	{
		this->playOnHover = true;

		verticalPadding = 70;
		horizontalPadding = 70;
		verticalMargin = 150;
		horizontalMargin = 30;

		this->loadImagesFromFile(imagesFilename, fontname);
		this->loadMusicFromFile(musicFilename);
	};

	Menu::~Menu() {};

	void Menu::loadImagesFromFile(std::string filename, std::string fontname)
	{
		std::string objectName;
		std::ifstream imageFile;
		imageFile.open(filename);
		std::vector<std::string> optionStrings;
		//эта ошибка должна выводиться красным цветом в логгере if(!fs.is_open()) { std::cout << "failed to open " + filename, exit(1); }
		std::getline(imageFile, objectName);
		this->backgroundTexture.loadFromFile(objectName);
		this->backgroundSprite.setTextureRect(sf::Rect(0, 0, int(this->backgroundTexture.getSize().x) , int(this->backgroundTexture.getSize().y)));
		this->backgroundSprite.setTexture(this->backgroundTexture);
		this->backgroundSprite.setPosition(0, 0);

		while (std::getline(imageFile, objectName))
			optionStrings.push_back(objectName);

		this->font.loadFromFile(fontname);
		this->text.setFont(font);
		this->text.setCharacterSize(50);
		this->text.setFillColor(sf::Color::White);
		int i = 0;
		for (std::string option : optionStrings)
		{
			i++;
			text.setString(option);
			text.setPosition(horizontalMargin + horizontalPadding, verticalMargin + i * verticalPadding);
			optionsText.push_back(text);
		}
		imageFile.close();
	}
	void Menu::loadMusicFromFile(std::string filename)
	{
		std::string objectName;
		std::ifstream musicFile;
		musicFile.open(filename);

		std::getline(musicFile, objectName);
		this->backgroundMusic.openFromFile(objectName);

		std::getline(musicFile, objectName);
		this->onHoverSoundBuffer.loadFromFile(objectName);
		this->onHoverSound = new sf::Sound(this->onHoverSoundBuffer);

		musicFile.close();
	}

	void Menu::setOptionAction(unsigned optionNumber) {}; //set what we do, when a certain option is pressed //do a vector of function pointers and add elements to it with this function
	void Menu::handle(sf::RenderWindow& window)
	{
		sf::Vector2<float> mouse;
		mouse.x = sf::Mouse::getPosition(window).x;
		mouse.y = sf::Mouse::getPosition(window).y;

		for (int i = 0; i < optionsText.size(); i++)
		{
			if (optionsText[i].getGlobalBounds().contains(mouse))
			{
				optionsText[i].setFillColor(sf::Color::Red);
				if (this->playOnHover)
					this->onHoverSound->play();
				this->playOnHover = false;

				if ((i == 0) && (sf::Mouse::isButtonPressed(sf::Mouse::Left))){}

				if ((i == 1) && (sf::Mouse::isButtonPressed(sf::Mouse::Left)))
					exit(0);
			}
			else { optionsText[i].setFillColor(sf::Color::White);};

			//this->playOnHover = 0;
		}
		
		//костыль
		int sum = 0;
		for (int i = 0; i < optionsText.size(); i++)	
			if (optionsText[i].getGlobalBounds().contains(mouse))
				sum++;

		if (sum == 0)
			this->playOnHover = true;
	}

	void Menu::draw(sf::RenderWindow& window)
	{
		window.draw(this->backgroundSprite);

		for (sf::Text option : optionsText)
			window.draw(option);
	}
}

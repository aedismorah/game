#include "map.h"

namespace Aedis
{
	Map::Map(std::string mapFilename, std::string mapTextureFilename)
	{
		this->loadFromFile(mapFilename);
		this->loadTextures(mapTextureFilename);
		//logger notification that map has been sucesfully created or not
	}

	void Map::loadFromFile(std::string filename)
	{
		std::ifstream mapFile;
		//обработать исключение если файл не открывается логгером
		mapFile.open(filename);
		
		std::string tmp;
		while (tmp != "  <data encoding=\"csv\">")
			std::getline(mapFile, tmp);

		std::vector<long int> uniqueTiles;
		while (tmp != "</data>")
		{
			std::getline(mapFile, tmp);
			if (tmp != "</data>")
			{
				std::vector<unsigned long> tileRow;
				std::replace(tmp.begin(), tmp.end(), ',', ' ');
				std::istringstream tmpStream(tmp);
				unsigned long tile;
				while (tmpStream >> tile)
				{
					if(!(std::find(uniqueTiles.begin(), uniqueTiles.end(), tile) != uniqueTiles.end()))
						uniqueTiles.push_back(tile);
					tileRow.push_back(tile);
				}
				this->MapTiles.push_back(tileRow);
			}
		}
		this->mapSize = sf::Vector2i(this->MapTiles.size(), this->mapSize.y = this->MapTiles[0].size());
		this->tilesNumber = uniqueTiles.size() - 1;

		//дописать считывание свойств объектов
	}

	void Map::loadTextures(std::string filename)
	{
		//add logger exception if loadTextures called before loading the map itself
		this->TiledMapTexture.loadFromFile(filename);
		this->TiledMapSprites = new sf::Sprite[this->tilesNumber];

		this->tileSize = sf::Vector2f(TiledMapTexture.getSize().y, TiledMapTexture.getSize().y);
		
		for (int i = 0; i < this->tilesNumber; i++)
		{
			this->TiledMapSprites[i].setTextureRect(sf::IntRect(i * this->tileSize.x, 0, this->tileSize.x, this->tileSize.y));
			this->TiledMapSprites[i].setTexture(TiledMapTexture, false);
		}
	}

	void Map::draw(sf::RenderWindow& window)
	{
		for (int i = 0; i < this->mapSize.x; i++)
			for (int j = 0; j < this->mapSize.y; j++)
			{
				if (this->MapTiles[i][j] != 0)
					drawTile(window, i, j);
			}
	}

	void Map::drawTile(sf::RenderWindow& window, int i, int j)
	{
		if (this->MapTiles[i][j] < 1610612737)
		{
			this->TiledMapSprites[this->MapTiles[i][j] - 1].setPosition(j * this->tileSize.x, i * this->tileSize.x);
			this->TiledMapSprites[this->MapTiles[i][j] - 1].setRotation(0.f);
			window.draw(TiledMapSprites[this->MapTiles[i][j] - 1]);
		}
		if (this->MapTiles[i][j] >= 1610612737 && this->MapTiles[i][j] < 2684354561)
		{
			this->TiledMapSprites[this->MapTiles[i][j] - 1610612737].setPosition(j * this->tileSize.x, (i + 1) * this->tileSize.x);
			this->TiledMapSprites[this->MapTiles[i][j] - 1610612737].setRotation(270.f);
			window.draw(TiledMapSprites[this->MapTiles[i][j] - 1610612737]);
		}
		if (this->MapTiles[i][j] >= 2684354561 && this->MapTiles[i][j] < 3221225473)
		{
			this->TiledMapSprites[this->MapTiles[i][j] - 2684354561].setPosition((j + 1) * this->tileSize.x, i * this->tileSize.x);
			this->TiledMapSprites[this->MapTiles[i][j] - 2684354561].setRotation(90.f);
			window.draw(TiledMapSprites[this->MapTiles[i][j] - 2684354561]);
		}
		if (this->MapTiles[i][j] >= 3221225473)
		{
			this->TiledMapSprites[this->MapTiles[i][j] - 3221225473].setPosition((j + 1) * this->tileSize.x, (i + 1) * this->tileSize.x);
			this->TiledMapSprites[this->MapTiles[i][j] - 3221225473].setRotation(180.f);
			window.draw(TiledMapSprites[this->MapTiles[i][j] - 3221225473]);
		}
	}

	//void Map::update(...) {};
	//void Map::setTile(sf::Vector2i tile) {};
	//void Map::setTile(int x, int y) {};
}
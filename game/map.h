#pragma once

#include "includes.h"

namespace  Aedis
{
	class Map
	{
	public:
		Map(std::string mapFilename, std::string mapTextureFilename);
		void loadFromFile(std::string filename);
		void loadTextures(std::string filename);
		void draw(sf::RenderWindow& window);
		//void update(...);
		//void setTile(sf::Vector2i tile);
		//void setTile(int x, int y);
	private:
		void drawTile(sf::RenderWindow& window, int i, int j);
		std::vector<std::vector<unsigned long>> MapTiles;
		sf::Texture TiledMapTexture;
		sf::Sprite* TiledMapSprites;
		sf::Vector2f tileSize;
		sf::Vector2i mapSize;
		unsigned tilesNumber;
	};
}
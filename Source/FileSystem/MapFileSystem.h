//
// Created by nicka on 1/1/2021.
//

#ifndef TRUGAMING_MAPFILESYSTEM_H
#define TRUGAMING_MAPFILESYSTEM_H


#include <SFML/Graphics/Texture.hpp>
#include <fstream>
#include "../../Dependencies/Nlohmann/json.hpp"

class MapFileSystem {
public:

		MapFileSystem(std::string fileName);

		std::vector<sf::Texture> getTexture ( int x, int y );

		sf::Texture getTexture ( int x, int y, int depth );

		void setTexture(int x, int y, int depth, std::string textureName);

		~MapFileSystem() {
			fileOpened.close();
		}

private:
		std::fstream fileOpened;

		MapFileSystem()= default;

};


#endif //TRUGAMING_MAPFILESYSTEM_H

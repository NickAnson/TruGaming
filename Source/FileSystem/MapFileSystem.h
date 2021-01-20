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

		void setTexture(int x, int y, int depth, std::string textureName);

		~MapFileSystem() {
			fileOpened.close();
		}

private:

		std::fstream fileOpened;
		std::vector<int> test;
		MapFileSystem()= default;

    int getTexture(std::string textureName);
};


#endif //TRUGAMING_MAPFILESYSTEM_H

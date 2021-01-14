//
// Created by nicka on 1/1/2021.
//

#include <iostream>
#include "MapFileSystem.h"

MapFileSystem::MapFileSystem ( std::string fileName ) {

	std::cout << fileName << std::endl;

	std::ifstream f;
	f.open(fileName);

	nlohmann::json jsonFile = nlohmann::json::parse( f);


	if(jsonFile.is_null()) {
		std::cout << "FAILED TO OPEN JSON FILE" << std::endl;
		std::exit(-1);
	}
}

std::vector<sf::Texture> MapFileSystem::getTexture ( int x, int y ) {

	fileOpened.clear();                 // clear fail and eof bits
	fileOpened.seekg(0, std::ios::beg); // back to the start!

	return std::vector<sf::Texture>();


}

sf::Texture MapFileSystem::getTexture ( int x, int y, int depth ) {

	fileOpened.clear();                 // clear fail and eof bits
	fileOpened.seekg(0, std::ios::beg); // back to the start!

//	std::cout <<jsonFile["chunk"]["1"] << std::endl;

	return sf::Texture();
}

void MapFileSystem::setTexture (
		int x, int y, int depth, std::string textureName ) {

}

//
// Created by Nick on 1/25/2021.
//

#include <fstream>
#include <sstream>
#include "MapEditor.h"

void MapEditor::changeTile(unsigned short blockNumber, const std::string &chunk, const std::string &newTileObject) {

    std::string tempFileName = chunk + "_temp";

    std::fstream file(chunk);
    std::ofstream tempFile(tempFileName);

    std::string line;

    int i = 0;
    file.seekg(std::ios::beg);
    while (getline(file, line) && i < blockNumber - 1) {
        tempFile << line;
        tempFile << '\n';
        i++;
    }

    std::istringstream ss(newTileObject);
    getline(ss, line, ' ');
    std::string param1 = line;
    getline(ss, line, ' ');
    char param2 = line[0];
    getline(ss, line, ' ');
    signed short int param3 = std::stoi(line);
    getline(ss, line, ' ');

    tempFile << param1;
    tempFile << ' ';
    tempFile << param2;
    tempFile << ' ';
    tempFile << param3;
    tempFile << '\n';

    while (getline(file, line)) {
        tempFile << line;
        tempFile << '\n';
    }

    ss.clear();
    file.close();
    tempFile.close();

    std::remove(chunk.c_str());
    std::rename(tempFileName.c_str(), chunk.c_str());

}
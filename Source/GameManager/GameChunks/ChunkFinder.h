//
// Created by Nick on 2/27/2021.
//

#ifndef TRUGAMING_CHUNKFINDER_H
#define TRUGAMING_CHUNKFINDER_H


#include <utility>
#include <vector>

class ChunkFinder {
public:
    static std::vector<std::pair<int, int>> find(int radius, std::pair<int, int> currentChunk);

    ChunkFinder() = delete;

private:

};


#endif //TRUGAMING_CHUNKFINDER_H


#include "ChunkFinder.h"

std::vector<std::pair<int, int>> ChunkFinder::find(int radius, std::pair<int, int> currentChunk) {
    std::vector<std::pair<int, int>> chunks;
    for (int row = 0; row <= radius; row++) {
        for (int column = 0; column <= radius; column++) {

            if (row == 0 && column == 0) {
                chunks.emplace_back(currentChunk.first + column, currentChunk.second + row);
                continue;
            }
            if (column == 0) {
                chunks.emplace_back(currentChunk.first + column, currentChunk.second + row);
                chunks.emplace_back(currentChunk.first + column, currentChunk.second - row);
            } else if (row == 0) {
                chunks.emplace_back(currentChunk.first + column, currentChunk.second - row);
                chunks.emplace_back(currentChunk.first - column, currentChunk.second - row);
            } else {
                chunks.emplace_back(currentChunk.first + column, currentChunk.second + row);
                chunks.emplace_back(currentChunk.first - column, currentChunk.second + row);

                chunks.emplace_back(currentChunk.first + column, currentChunk.second - row);
                chunks.emplace_back(currentChunk.first - column, currentChunk.second - row);
            }

        }
    }

    return chunks;
}

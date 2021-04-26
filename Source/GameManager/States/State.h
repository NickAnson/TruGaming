//
// Created by Nick on 3/25/2021.
//

#ifndef TRUGAMING_STATE_H
#define TRUGAMING_STATE_H

class State {
public:
    enum playerStates {
        player_MOVING,
        player_IDLE,
        player_NONE
    };
    enum windowStates {
        window_OPEN,
        window_CLOSED,
        window_NONE,
        window_EXIT
    };
    enum gameChunkStates {
        chunk_NORMAL,
        chunk_NOTFOUND
    };
    enum viewOpened {
        screen_TITLE, screen_WORLD, screen_HOUSE, NONE
    };
    enum popUpView {
        popup_ESCAPE, popup_NONE
    };
    enum gameStatus {
        game_CHUNKLOADING, game_NONE
    };

private:
};

#endif //TRUGAMING_STATE_H

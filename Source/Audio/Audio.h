#ifndef TRUGAMING_AUDIO_H
#define TRUGAMING_AUDIO_H

#include <SFML/Audio.hpp>
#include <string>


class Audio {
public:
    explicit Audio(const std::string &audioFileTemp, bool loopAudio = false) {
        audioFile = audioFileTemp;
        if (!buffer.loadFromFile(musicFolder + audioFile)) {
            std::exit(-129);
        }
        sound.setBuffer(buffer);
        sound.setLoop(loopAudio);
    }

    void play() {
        if (sound.getStatus() != sf::Music::Status::Playing) {
            sound.play();
        }
    }

    void pause() {
        if (sound.getStatus() != sf::Music::Status::Paused) {
            sound.pause();
        }
    }

    void setVolume(float amount) {
        sound.setVolume(amount);
    }

    void setPitch(float amount) {
        sound.setPitch(amount);
    }

    void rewind() {
        sound.stop();
    }

    Audio() = delete;

private:
    std::string audioFile;
    sf::SoundBuffer buffer;
    sf::Sound sound;
    std::string musicFolder = "../res/music/";

};


#endif //TRUGAMING_AUDIO_H

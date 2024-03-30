//sound_player.h
#pragma once

#include <string>
#include <vector>
#include <thread>
#include <mutex>

class SoundPlayer {
public:
    SoundPlayer(const std::string& soundFile);
    void playSound();

private:
    std::string soundFile;
    std::mutex soundMutex;
    void playSoundOnDevice(const std::string& device);
};

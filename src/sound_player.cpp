#include "sound_player.h"
#include <iostream>
#include <cstdlib>

SoundPlayer::SoundPlayer(const std::string& soundFile) : soundFile(soundFile) {}

void SoundPlayer::playSoundOnDevice(const std::string& device) {
    std::string command = "aplay -D " + device + " " + soundFile;
    int result = system(command.c_str());
    if (result != 0) {
        std::cerr << "Error playing sound on " << device << std::endl;
    }
}

void SoundPlayer::playSound() {
    std::lock_guard<std::mutex> lock(soundMutex);
    std::vector<std::string> devices = {"plughw:0,0", "plughw:1,0"};
    std::vector<std::thread> threads;
    // TODO: Add mechanism to check available devices and their capabilities
    for (const auto& device : devices) {
        threads.emplace_back(&SoundPlayer::playSoundOnDevice, this, device);
    }

    for (auto& thread : threads) {
        if (thread.joinable()) {
            thread.join();
        }
    }
}
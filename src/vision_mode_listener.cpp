// vision_mode_listener.cpp
#include "rclcpp/rclcpp.hpp"
#include "ghost_manager_interfaces/msg/heartbeat.hpp"
#include "heartbeat_message_parser.h"
#include "sound_player.h"
#include "ament_index_cpp/get_package_share_directory.hpp"
#include <memory>
#include <chrono>

class VisionModeListener : public rclcpp::Node {
public:
    VisionModeListener();

private:
    std::chrono::steady_clock::time_point last_play_time;

    void heartbeatCallback(const ghost_manager_interfaces::msg::Heartbeat::SharedPtr msg);
    rclcpp::Subscription<ghost_manager_interfaces::msg::Heartbeat>::SharedPtr subscription;
    std::unique_ptr<SoundPlayer> soundPlayer;
};

VisionModeListener::VisionModeListener() : Node("vision_mode_listener"), last_play_time(std::chrono::steady_clock::now()) {
    subscription = this->create_subscription<ghost_manager_interfaces::msg::Heartbeat>(
        "/state/heartbeat", 10, std::bind(&VisionModeListener::heartbeatCallback, this, std::placeholders::_1));
    std::string package_share_directory = ament_index_cpp::get_package_share_directory("stair_alerts");
    std::string sound_file_path = package_share_directory + "/sounds/warning_conv.wav";
    assert(!sound_file_path.empty()); // Ensure the sound file path is not empty
    soundPlayer = std::make_unique<SoundPlayer>(sound_file_path);
}

void VisionModeListener::heartbeatCallback(const ghost_manager_interfaces::msg::Heartbeat::SharedPtr msg) {
    auto now = std::chrono::steady_clock::now();
    if (std::chrono::duration_cast<std::chrono::seconds>(now - last_play_time).count() >= 4) {
            // Your existing logic
            
    int currentVisionMode = parse_vision_mode(*msg);
    RCLCPP_INFO(this->get_logger(), "Heartbeat received with vision_mode: %d", currentVisionMode);
    if (currentVisionMode == 3) {
        RCLCPP_INFO(this->get_logger(), "Vision mode is 3, attempting to play sound...");
        soundPlayer->playSound();
        RCLCPP_INFO(this->get_logger(), "Sound played successfully.");
        }
    last_play_time = now; // Update last play time
    }
}

int main(int argc, char* argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<VisionModeListener>());
    rclcpp::shutdown();
    return 0;
}

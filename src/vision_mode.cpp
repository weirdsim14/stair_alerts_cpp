// vision_mode_listener.cpp
#include "rclcpp/rclcpp.hpp"
#include "ghost_manager_interfaces/msg/heartbeat.hpp"
#include "heartbeat_message_parser.h"
#include "sound_player.h"
#include <memory>

class VisionModeListener : public rclcpp::Node {
public:
    VisionModeListener();

private:
    void heartbeatCallback(const ghost_manager_interfaces::msg::Heartbeat::SharedPtr msg);
    rclcpp::Subscription<ghost_manager_interfaces::msg::Heartbeat>::SharedPtr subscription;
    std::unique_ptr<SoundPlayer> soundPlayer;
};

VisionModeListener::VisionModeListener() : Node("vision_mode_listener") {
    subscription = this->create_subscription<ghost_manager_interfaces::msg::Heartbeat>(
        "/state/heartbeat", 10, std::bind(&VisionModeListener::heartbeatCallback, this, std::placeholders::_1));
    std::string package_share_directory = ament_index_cpp::get_package_share_directory("stair_alerts");
    std::string sound_file_path = package_share_directory + "/sounds/warning_conv.wav";
    soundPlayer = std::make_unique<SoundPlayer>(sound_file_path);
}

void VisionModeListener::heartbeatCallback(const ghost_manager_interfaces::msg::Heartbeat::SharedPtr msg) {
    int currentVisionMode = parse_vision_mode(*msg);
    RCLCPP_INFO(this->get_logger(), "Heartbeat received with vision_mode: %d", currentVisionMode);
    
    if (currentVisionMode == 3) {
        RCLCPP_INFO(this->get_logger(), "Vision mode is 3, attempting to play sound...");
        soundPlayer->playSound();
        RCLCPP_INFO(this->get_logger(), "Sound played successfully.");
    }
}

int main(int argc, char* argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<VisionModeListener>());
    rclcpp::shutdown();
    return 0;
}

// heartbeat_message_parser.h
#pragma once

#include "ghost_manager_interfaces/msg/heartbeat.hpp" // Adjust the include path based on your setup

int parse_vision_mode(const ghost_manager_interfaces::msg::Heartbeat& msg) {
    return msg.vision_mode;
}

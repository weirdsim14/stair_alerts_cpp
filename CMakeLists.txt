cmake_minimum_required(VERSION 3.8)
project(stair_alerts)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(ghost_manager_interfaces REQUIRED) # Assuming this is a custom package for Heartbeat.msg

include_directories(
  include
)

# Optionally compile sound_player as a library
add_library(sound_player
  src/sound_player.cpp
)

# Ensure C++17 standard for std::filesystem, if used, or any other C++17 features
set_property(TARGET sound_player PROPERTY CXX_STANDARD 17)

# Compile the main executable
add_executable(vision_mode_listener
  src/vision_mode_listener.cpp
)

# Link the executable against the required libraries
ament_target_dependencies(vision_mode_listener
  rclcpp
  ghost_manager_interfaces # Add this if your node subscribes to Heartbeat messages
)

# Link the sound_player library to the vision_mode_listener executable
target_link_libraries(vision_mode_listener
  sound_player
)

# Install the executable and directories
install(TARGETS
  vision_mode_listener
  sound_player
  DESTINATION lib/${PROJECT_NAME}
)

install(DIRECTORY
  include/
  DESTINATION include
)

install(DIRECTORY sounds/
  DESTINATION share/${PROJECT_NAME}/sounds
)


ament_package()

# Stair Mode Alert System

This system is designed to enhance safety in robotic operations, especially when robots are navigating stairs. The core functionality is to play an auditory warning when the robot enters stair mode, indicating to nearby individuals that they should not follow the robot due to the increased risk during this operation.

The warning, "Do not follow the robot while it is ascending or descending stairs," is communicated through a specific sound file (`warning_conv.wav`). This alert is triggered based on the robot's vision mode status, which is shared over a ROS 2 topic (`/state/heartbeat`). The system ensures the sound is played only when necessary (vision_mode == 3, corresponding to stair mode) and manages the timing of alerts to prevent overlapping playback.

## Installation and Build Instructions

### Prerequisites

Ensure you have ROS 2 installed and configured on your system. This application was developed and tested with ROS 2 humble, but it should be compatible with newer versions.

### Building the Package

1. **Clone the Package**: Clone this repository into your ROS 2 workspace's `src` directory.

2. **Build the Package**: Navigate to the root of your ROS 2 workspace. Compile the package using the following command:

    ```bash
    colcon build --packages-select stair_alerts
    ```

3. **Source the Environment**: To make the package available in your ROS 2 environment, source the setup script:

    ```bash
    source install/setup.bash
    ```

## Running the Package

Execute the `vision_mode_listener` node with the following command:

```bash
ros2 run stair_alerts vision_mode_listener
```

## 1. TODO: Add assert, Pulseaudio
- [x] Add assert
- [x] Change to using pulseaudio
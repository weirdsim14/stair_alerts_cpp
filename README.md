# 로봇 계단 모드 시 후방 추종 금지 경고 알람

> /state/heartbeat topic에서 vision_mode == 3 (계단모드) 일 경우
> 
> 경고음(warning_conv.wav) 실행
> 
> 경고음 파일 길이가 4초이므로 4초에 한번씩 topic message 수신
> 
> `로봇이 계단을 오르고 있습니다. 절대 뒤에 따라오지 마십시오`
>
>

## 1. package build
```
colcon build --packages-select stair_alerts
```

## 2. source
```
source install/setup.bash
```

## package 실행
```
ros2 run stair_alerts vision_mode_listener
```

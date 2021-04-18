## 2021.RoleyToo.CameraServer

Camera Server System for the Raspberry Pi/Nvidia Jetson TK1 for low-latency network streams from the robot.

Using MJPEG Server from https://github.com/jacksonliam/mjpg-streamer, and wrapped around a custom web interface and one-command build scripts written by https://github.com/mitchellblaser.

##### Now with COOL© Technology!

We use the Cool Outstanding Online Link © to connect to a Driver Station laptop. I call it this, because we've found it to be extremely fast. I recommend you either use [VLC Media Player](https://www.videolan.org/vlc/) to view the stream hosted at port ip:8080/?action=stream, or navigate to that link in your browser (tested and working in Chrome) and access it manually that way.

![](https://github.com/icrobotics-team5584/frc/blob/master/software/cpp/2021.RoleyToo.CameraServer/iclogo.jpg?raw=true)



#### Setup:

Open the Terminal (WSL or Linux) and cd to the 2021.RoleyToo.CameraServer Folder.

Run the following commands:

```bash
chmod +x ./build.sh
./build.sh
cd build
```



#### Usage:

Run either `./build/test.sh` to show a test pattern, or edit `./build/start.sh` with your target command.

Refer to [this link](https://github.com/jacksonliam/mjpg-streamer/blob/master/mjpg-streamer-experimental/README.md) for usage of the mjpg-streamer binary.
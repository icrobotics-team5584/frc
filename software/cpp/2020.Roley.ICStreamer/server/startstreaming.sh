#!/bin/bash

STRIP="10.55.84.8"
STR1PORT="5800"
STR2PORT="5801"
STR3PORT="5802"

echo -e "\e[7m          IC STREAMING SERVER (v3)           \e[0m"
echo -e "\e[1m=============================================\e[0m"
echo -e "\e[1m -> Setting path variable\e[0m"

export LD_LIBRARY_PATH=/home/ubuntu/NewProjects/testm1/icstream/mjpg-streamer-experimental/

echo -e "\e[1m -> Launching video stream STR1 on port $STR1PORT.\e[0m"
echo -e "    -> Output piped to log file ./STR1.log."
/home/ubuntu/NewProjects/testm1/icstream/mjpg-streamer-experimental/mjpg_streamer -o 'output_http.so -w ./www -p '${STR1PORT} -i 'input_uvc.so -d /dev/v4l/by-path/platform-70090000.xusb-usb-0:2.2:1.0-video-index0 -r 160x120 -f 30' > STR1.log 2>&1 &

echo -e "\e[1m -> Launching video stream STR2 on port $STR2PORT.\e[0m"
echo -e "    -> Output piped to log file ./STR2.log."
/home/ubuntu/NewProjects/testm1/icstream/mjpg-streamer-experimental/mjpg_streamer -o 'output_http.so -w ./www -p '${STR2PORT} -i 'input_uvc.so -d /dev/v4l/by-path/platform-70090000.xusb-usb-0:2.3:1.0-video-index0 -r 160x120 -f 30' > STR2.log 2>&1 &

echo -e "\e[1m -> Launching video stream STR3 on port $STR3PORT.\e[0m"
echo -e "    -> Output piped to log file ./STR3.log."
/home/ubuntu/NewProjects/testm1/icstream/mjpg-streamer-experimental/mjpg_streamer -o 'output_http.so -w ./www -p '${STR3PORT} -i 'input_uvc.so -d /dev/v4l/by-path/platform-70090000.xusb-usb-0:2.4:1.0-video-index0 -r 160x120 -f 30' > STR3.log 2>&1 &

wait

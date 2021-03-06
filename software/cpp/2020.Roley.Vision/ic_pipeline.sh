#!/bin/bash



# setup camera

/usr/bin/v4l2-ctl --device /dev/v4l/by-path/platform-70090000.xusb-usb-0:2.1:1.0-video-index0 --set-ctrl exposure_auto=1
/usr/bin/v4l2-ctl --device /dev/v4l/by-path/platform-70090000.xusb-usb-0:2.1:1.0-video-index0 --set-ctrl exposure_absolute=5



# purge old log file

/bin/rm -f /tmp/ic_pipeline.log



# run application

cd /home/ubuntu/Projects/2020.Roley.Vision/build
./ic_pipeline >> /tmp/ic_pipeline.log 2>&1

#!/bin/bash



# setup camera
#
# /usr/bin/v4l2-ctl --list-ctrls
#                     brightness (int)    : min=30 max=255 step=1 default=133 value=111
#                       contrast (int)    : min=0 max=10 step=1 default=5 value=10
#                     saturation (int)    : min=0 max=200 step=1 default=83 value=100
# white_balance_temperature_auto (bool)   : default=1 value=1
#           power_line_frequency (menu)   : min=0 max=2 default=2 value=1
#      white_balance_temperature (int)    : min=2800 max=10000 step=1 default=4500 value=5008 flags=inactive
#                      sharpness (int)    : min=0 max=50 step=1 default=25 value=25
#         backlight_compensation (int)    : min=0 max=10 step=1 default=0 value=0
#                  exposure_auto (menu)   : min=0 max=3 default=1 value=1
#              exposure_absolute (int)    : min=5 max=20000 step=1 default=156 value=5
#                   pan_absolute (int)    : min=-201600 max=201600 step=3600 default=0 value=0
#                  tilt_absolute (int)    : min=-201600 max=201600 step=3600 default=0 value=0
#                  zoom_absolute (int)    : min=0 max=10 step=1 default=0 value=0

/usr/bin/v4l2-ctl --device=/dev/video0 --set-ctrl brightness=133
/usr/bin/v4l2-ctl --device=/dev/video1 --set-ctrl brightness=133

/usr/bin/v4l2-ctl --device=/dev/video0 --set-ctrl contrast=5
/usr/bin/v4l2-ctl --device=/dev/video1 --set-ctrl contrast=5

/usr/bin/v4l2-ctl --device=/dev/video0 --set-ctrl saturation=83
/usr/bin/v4l2-ctl --device=/dev/video1 --set-ctrl saturation=83

/usr/bin/v4l2-ctl --device=/dev/video0 --set-ctrl power_line_frequency=2
/usr/bin/v4l2-ctl --device=/dev/video1 --set-ctrl power_line_frequency=2

# NOTE: to avoid an error here we need to enable the white_balance_temperature before we can set the value . . .
/usr/bin/v4l2-ctl --device=/dev/video0 --set-ctrl white_balance_temperature_auto=0
/usr/bin/v4l2-ctl --device=/dev/video1 --set-ctrl white_balance_temperature_auto=0
/usr/bin/v4l2-ctl --device=/dev/video0 --set-ctrl white_balance_temperature=4500
/usr/bin/v4l2-ctl --device=/dev/video1 --set-ctrl white_balance_temperature=4500
/usr/bin/v4l2-ctl --device=/dev/video0 --set-ctrl white_balance_temperature_auto=1
/usr/bin/v4l2-ctl --device=/dev/video1 --set-ctrl white_balance_temperature_auto=1

/usr/bin/v4l2-ctl --device=/dev/video0 --set-ctrl sharpness=25
/usr/bin/v4l2-ctl --device=/dev/video1 --set-ctrl sharpness=25

/usr/bin/v4l2-ctl --device=/dev/video0 --set-ctrl backlight_compensation=0
/usr/bin/v4l2-ctl --device=/dev/video1 --set-ctrl backlight_compensation=0

/usr/bin/v4l2-ctl --device=/dev/video0 --set-ctrl exposure_auto=1
/usr/bin/v4l2-ctl --device=/dev/video1 --set-ctrl exposure_auto=1

/usr/bin/v4l2-ctl --device=/dev/video0 --set-ctrl exposure_absolute=5
/usr/bin/v4l2-ctl --device=/dev/video1 --set-ctrl exposure_absolute=5

/usr/bin/v4l2-ctl --device=/dev/video0 --set-ctrl pan_absolute=0
/usr/bin/v4l2-ctl --device=/dev/video1 --set-ctrl pan_absolute=0

/usr/bin/v4l2-ctl --device=/dev/video0 --set-ctrl tilt_absolute=0
/usr/bin/v4l2-ctl --device=/dev/video1 --set-ctrl tilt_absolute=0

/usr/bin/v4l2-ctl --device=/dev/video0 --set-ctrl zoom_absolute=0
/usr/bin/v4l2-ctl --device=/dev/video1 --set-ctrl zoom_absolute=0


# purge old log file

/bin/rm -f /tmp/ic_pipeline.log



# run application

cd /home/ubuntu/J5-ic-pipeline/build
./ic_pipeline >> /tmp/ic_pipeline.log 2>&1


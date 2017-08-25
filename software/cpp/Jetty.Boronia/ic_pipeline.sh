#!/bin/bash



# setup camera

/usr/bin/v4l2-ctl --set-ctrl exposure_auto=1
/usr/bin/v4l2-ctl --set-ctrl exposure_absolute=5



# run application

cd /home/ubuntu/9-ic-pipeline/build
./ic_pipeline


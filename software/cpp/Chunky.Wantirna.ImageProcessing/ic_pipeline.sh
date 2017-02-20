#!/bin/bash



# setup camera

/usr/bin/v4l2-ctl --set-ctrl exposure_auto=1
/usr/bin/v4l2-ctl --set-ctrl exposure_absolute=5



# purge old log file

/bin/rm -f /tmp/ic_pipeline.log



# run application

cd /home/ubuntu/9-ic-pipeline/build
./ic_pipeline >> /tmp/ic_pipeline.log 2>&1


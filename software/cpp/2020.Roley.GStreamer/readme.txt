COMPONENTS ON SERVER (JETSON)

(a) ic_gstserver.pl - - - perl wrapper fto manage gstreamer instances by starting and stopping one gst-launch-1.0 pipeline per camera,
                          uses ic_gstserver.ctl to drive the configuration, launched using @reboot in ubuntu crontab

(b) ic_gstserver.ctl - - - control file containing single character to control the gstreamer configureation (1, 2 or 3)

(c) ic_gstserver.cpp - - - source file for ic_gstserver utility that will read network tables entry and manage content of ic_gstserver.ctl [WORK IN PROGRESS]



COMPONENTS ON CLIENT (DRIVER STATION PC)

(a) GStreamer

    1: Installed GStreamer

    2: Copied gst-launch-1.0.exe to gst-launch-1.0.1181.exe, gst-launch-1.0.1182.exe and gst-launch-1.0.1183.exe so that AHK can launch and identify specific executables

(b) AutoHotkey

    1: Installed AutoHotKey

    2: Run scripts in normal command prompt ...

       C:
       cd \scm\icrobotics\frc\software\cpp\2020.Roley.GStreamer
       "C:\Program Files\AutoHotkey\AutoHotkey.exe" ic_gstdriverstation.ahk

(c) FRC Driver station

(d) FRC Shuffleboard



KNOWN PROBLEMS ...

1: on driver station PC with radio we have to wind the resolution right down on all three channels to 160x120 in the ic_gstserver.pl

2: driverstation.exe window is not resizing when AHK tells them to!

3: javaw.exe window is not resizing when AHK tells them to! (SOLVED: seems to be solved when we remember to set driver station dash to "labview")

4: If windows exist and are minimised then AHK reports a "-1" fault. (SOLVED: added a restore step for each window)

5: Title / menu bars do not disappear altogether when "WinSet, Style, -0xC00000, ahk_id ..." is applied. (SOLVED: with  WinSet, Style, -0xC40000)

6: Window sizes leave a gap - can we fix the size or maybe better to have a gap but a backgroud applied so that it is at least consistent.



BACKGROUND INFO ...

Working GStreamer client/server configurations:

EXAMPLE #1:
  SERVER:
    gst-launch-1.0 videotestsrc ! jpegenc ! image/jpeg,width=640,height=480 ! progressreport ! rtpjpegpay ! udpsink host=192.168.0.183 port=5000
  CLIENT:
    gst-launch-1.0 udpsrc port=5000 ! application/x-rtp,encoding-name=JPEG,payload=26! rtpjpegdepay ! jpegdec ! xvimagesink

EXAMPLE #2:
  SERVER:
    gst-launch-1.0 videotestsrc ! jpegenc ! image/jpeg,width=640,height=480 ! progressreport ! rtpjpegpay ! udpsink host=192.168.0.126 port=1180
    (note the IP ADDRESS is for the client PC)
    (note port 5000 did not work in this case so we selected a port in the allowed FRC range ... 1180..1190 and 5800..5810 all seem to work ok!)
  CLIENT (on PC):
    C
    cd \gstreamer\1.0\x86_64\bin
    gst-launch-1.0 udpsrc port=1180 ! application/x-rtp,encoding-name=JPEG,payload=26! rtpjpegdepay ! jpegdec ! autovideosink

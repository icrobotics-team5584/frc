INSTALL AUTOHOTKEY FOR DRIVERSTATION LAYOUT AUTOMATION ...

1: Installed AutoHotKey

2: Run scripts in normal command prompt ...

   "C:\Program Files\AutoHotkey\AutoHotkey.exe" ic_gstdriverstation.ahk

WORKING GSTREAMER CONFIGURATIONS ...

SERVER:
  gst-launch-1.0 videotestsrc ! jpegenc ! image/jpeg,width=640,height=480 ! progressreport ! rtpjpegpay ! udpsink host=192.168.0.183 port=5000

CLIENT:
  gst-launch-1.0 udpsrc port=5000 ! application/x-rtp,encoding-name=JPEG,payload=26! rtpjpegdepay ! jpegdec ! xvimagesink

ALSO WORKING ...

SERVER:
  gst-launch-1.0 videotestsrc ! jpegenc ! image/jpeg,width=640,height=480 ! progressreport ! rtpjpegpay ! udpsink host=192.168.0.126 port=1180
  (note the IP ADDRESS is for the client PC)
  (note port 5000 did not work in this case so we selected a port in the allowed FRC range ... 1180..1190 and 5800..5810 all seem to work ok!)

CLIENT (on PC):
  C
  cd \gstreamer\1.0\x86_64\bin
  gst-launch-1.0 udpsrc port=1180 ! application/x-rtp,encoding-name=JPEG,payload=26! rtpjpegdepay ! jpegdec ! autovideosink


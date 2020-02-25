@ START /B C:\gstreamer\1.0\x86_64\bin\gst-launch-1.0.1181.exe udpsrc uri=udp://0.0.0.0:1181 ! application/x-rtp,encoding-name=JPEG,payload=26! rtpjpegdepay ! jpegdec ! autovideosink
@ START /B C:\gstreamer\1.0\x86_64\bin\gst-launch-1.0.1182.exe udpsrc uri=udp://0.0.0.0:1182 ! application/x-rtp,encoding-name=JPEG,payload=26! rtpjpegdepay ! jpegdec ! autovideosink
@ START /B C:\gstreamer\1.0\x86_64\bin\gst-launch-1.0.1183.exe udpsrc uri=udp://0.0.0.0:1183 ! application/x-rtp,encoding-name=JPEG,payload=26! rtpjpegdepay ! jpegdec ! autovideosink

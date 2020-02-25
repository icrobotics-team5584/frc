@ ECHO INFO: gst-launch processes before clean up . . . 
@ tasklist | findstr gst-launch

@ ECHO INFO: terminating relevant gst-launch processes . . .
@ taskkill /IM "gst-launch-1.0.1181.exe" /F
@ taskkill /IM "gst-launch-1.0.1182.exe" /F
@ taskkill /IM "gst-launch-1.0.1183.exe" /F

@ ECHO INFO: gst-launch processes before clean up . . . 
@ tasklist | findstr gst-launch

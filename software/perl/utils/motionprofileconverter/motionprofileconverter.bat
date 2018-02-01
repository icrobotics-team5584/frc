@echo off
cd C:\scm\icrobotics\frc\software\perl\utils\motionprofileconverter
echo *** a really cool csv converter ***
SET /P csv=enter csv file path:
perl motionprofileconverter.pl "c:\scm\icrobotics\frc\software\Motion Profiles\%csv%"
# Setting up the Nvidia Jetson Nano for Network Camera Streaming.

*(Authored by Mitchell Blaser, March 2020)*

*This tutorial assumes that the user is running the standardised development environment on Windows, and using Git Bash to run all commands. You will need both an active internet connection, plus a connection to the Jetson's network, with the Jetson and three USB Cameras.*

## Introduction: The application architecture

This application is designed to interface an Nvidia Jetson Nano, which is on a robot on it's own offline network, with a "Driver Station" (a laptop also on the network).

The Jetson hosts multiple camera streams, and the Driver Station accesses them. This is designed to be a completely userless interaction, with complete automation from power on to use.

Though this method is for this specific architecture (on a robot), you could theoretically use the same steps to make any network-accessible camera stream.

**So let's install it then.**



## Option 1: The easy way (prebuilt stuff from Git)

This is coming soon. Sorry :P



## Option 2: The hard way (from scratch)

### Step 1: Setting up the Server Environment

Connect to the Jetson via ssh with `ssh ubuntu@10.55.84.8`. When prompted, enter the password.

Once connected, change directory to the location you want to use for streaming with `cd [path]` and make a new directory (`mkdir [directory name]`).

Now that we have made the target directory on the jetson, let's disconnect from ssh with `exit`.

Now let's quickly make a temporary directory that can be wiped out later `mkdir temp && cd temp` and pull down the third-party software that we're using to stream cameras to the network.	

```bash
git clone https://github.com/jacksonliam/mjpg-streamer.git
```

Inside, you'll have a folder with the streamer software's <u>source code</u> in it. We still need to build it, though.

Rather than building the source locally with a cross-compiler, let's just transfer it to the Jetson instead.

Git Bash doesn't come with the "zip" command, so navigate to the directory you downloaded the repository to, and right click on the "jpg-streamer" folder and ***Send to -> Compressed (zipped) folder***. If you're using linux, you can just use `zip -r mjpg-streamer.zip mjpg-streamer`.

```bash
#Now let's find the zipped file on our drive,
#and upload it to the Jetson's storage.
scp mjpg-streamer.zip ubuntu@10.55.84.8:/home/ubuntu/[FOLDER]
#Here, [FOLDER] is the location which you created at the beginning of Step 1.

#Now connect back to the jetson via ssh and cd to the folder:
ssh ubuntu@10.55.84.8
cd [FOLDER]

#And unzip the files
unzip mjpg-streamer.zip
rm mjpg-streamer.zip

#Open the extracted directory
cd mjpg-streamer
```

Now we are ready to build **(yay)**

```bash
cd mjpg-streamer-experimental
mkdir _build
cd _build
cmake -DPLUGIN_INPUT_OPENCV=OFF
make
sudo make install #You will need to give your password here.
```

We need to configure the makefile to not compile the OpenCV Library, as the version we have on the Jetson isn't compatible with the library's OpenCV module, and we don't use it anyway. 

**The trick with this software is that you can't actually use the input and output modules that you have just built yet. There is an extra step.**

```bash
cd plugins
cd input_uvc
cp input_uvc.so ../../input_uvc.so
cd ../output_http
cp output_http.so ../../output_http.so 
cd ../../
```

Now we can start the server as a test with the commands:

```bash
export LD_LIBRARY_PATH=.

./mjpg_streamer -o 'output_http.so -w ./www -p 5800' \
-i 'input_uvc.so -d /dev/video1 -r 160x120 -f 30'
```

To view the stream we can preview it with VLC Media Player on an external PC. You'll need to download that from https://www.videolan.org/index.html. **You'll probably want to use a different device for this, as if you disconnect from the Jetson's network it will stop the ssh session which is running the server.**

Once installed, you can view the network stream via ***File -> Open Network*** and entering the address of your Jetson. In our case, it is at the IP Address 10.55.84.8, and at the port 5800. Let's substitute these values into the following IP: `http://10.55.84.8:5800/?action=stream`. If everything is working correctly, we can move onto the next step.

### Step 2: Automating the Server Environment

Now that we know the server is sending camera data to us, we can stop the test stream with `Ctrl+C`, and begin to automate the process of starting the server on startup, and having multiple streams running at the same time.

First, for readability's sake, let's rename the folder `mjpg-streamer` to `icstream` with the command `mv mjpg-streamer icstream`.

Now that we have done that, let's create a bash script to start the streamer software. Let's use Vim to create and edit `startstreaming.sh`.

```bash
vim startstreaming.sh
```

Once in Vim, we want to actually edit the file. Make sure you press the Insert key on your keyboard, and copy the following into the file. 

```bash
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
/home/ubuntu/NewProjects/testm1/icstream/mjpg-streamer-experimental/mjpg_streamer -o 'output_http.so -w ./www -p '${STR1PORT} -i 'input_uvc.so -d /dev/video0 -r 160x120 -f 30' > STR1.log 2>&1 &

echo -e "\e[1m -> Launching video stream STR2 on port $STR2PORT.\e[0m"
echo -e "    -> Output piped to log file ./STR2.log."
/home/ubuntu/NewProjects/testm1/icstream/mjpg-streamer-experimental/mjpg_streamer -o 'output_http.so -w ./www -p '${STR2PORT} -i 'input_uvc.so -d /dev/video1 -r 160x120 -f 30' > STR2.log 2>&1 &

echo -e "\e[1m -> Launching video stream STR3 on port $STR3PORT.\e[0m"
echo -e "    -> Output piped to log file ./STR3.log."
/home/ubuntu/NewProjects/testm1/icstream/mjpg-streamer-experimental/mjpg_streamer -o 'output_http.so -w ./www -p '${STR3PORT} -i 'input_uvc.so -d /dev/video2 -r 160x120 -f 30' > STR3.log 2>&1 &

wait
```

Once done, press the Escape key, then hold Shift and press ZZ to save the file.

Let's test that the script works by running it: `./startstreaming.sh` and viewing the streams through VLC on another computer (IP Addresses will all be `http://10.55.84.8:XXXX/?action=stream`, with `XXXX` being the ports set in variables `STR1PORT`, `STR2PORT` and `STR3PORT` at the top of the script.)

If everything works as expected, let's move on.



Now that we have the script created and tested, let's add this script to the Crontab so that it runs whenever we turn the Jetson on. If you don't want this functionality, you can skip this step.

First, let's open the Crontab for editing. By default, this will open in Vim, so remember to press Insert.

Now, let's move to the bottom of the file and type the following:

```bash
@reboot 60, run streamer.
```

Reboot the Jetson, and ensure that all three streams are accessible to the VLC stream. They will take just over a minute to boot up, so wait for a bit before you check the streams. If everything works as expected, Congratulations! You've completely set up the server! 

Now we can exit out of the ssh server once more (`exit`) and remove the temporary directory with all of our rubbish files in it. `rm -rf temp`.

Now let's do the client, so that we can properly view the streams without the slower VLC client.

### Step 3: Setting up the Client Environment

Power on the Driver Station, and ensure it is connected to the internet.

Now we are going to open Git Bash, and pull down the repository for the camera client.

```bash
#First, we can make a new directory in the home folder.
mkdir StreamClient 
cd StreamClient
git clone https://github.com/mitchellblaser/WebJCC.git
```

Now that we have the client software downloaded, we can actually use this to access the streams already, and we could be done. The problem with this solution is that you have to open each window and position them manually.

Let's automate it.

### Step 3: Automating the Client Environment

To automate the Client Environment, we're going to need to do a little more work.

Firstly, we need to download some more things. Let's first grab the Windows Layout Manager files from http://www.stefandidak.com/wilma/winlayoutmanager.zip. Extract the contents of the archive to a folder inside the previously-made `StreamClient` called `WinLayoutManager`.

Another issue with WinLayoutManager is that we have to run it as an administrator, and for some reason this isn't indicated in the executable's properties out of the box. This can be fixed by right-clicking on WinLayoutManager.exe and navigating to ***Properties -> Compatibility*** and setting ***Run this Program as an Administrator*** to true.

Now we can run WinLayoutManager and make a configuration of which windows we want open on the driver station when it comes to competition. Here's a photo of how I like mine set up:

![](Jetson/IMG_20200301_134713_1.jpg)

On the first run, you may be prompted to install the .NET Framework, so make sure you're connected to the internet, and click install. You will need to reboot afterwards.

Before we record any layouts to the program, we have to position them in the right spots. In the above image, I've opened the Driver Station software, FRC SmartDashboard, and three HTML files with **different titles in each** (this is important) which access a network stream.

Once the windows are positioned as desired we can open the layout manager and make a new layout by navigating to ***Layout -> New***. In the window that pops up, we can give our layout a name, I called mine "DriverStation".

Now we need to tell the program which application windows to keep track of. This can be done manually, but we can just capture every window on the screen with the "Capture" button. Once clicked, the list box on the right will populate with names of all of the windows that are currently open on the computer. 

Of course, we don't want to worry about some of the applications that were open on the computer at the time of recording, like the Layout Manager window itself. Go back and select the item you want to remove from the list box, and click on the "Remove" button under it to ignore it. Repeat this for any non-critical application.

When you're done with this, add a keyboard binding to the layout, ideally something that isn't going to clash with anything else (I use Win+Shift+F10) and click OK to close the window.

We're almost done now. The last thing to do is create a shell script to open up all of the required applications, which will work in conjunction with the Windows Layout Manager application by first opening all of the required windows before they get resized.



<u>Installing AutoHotKey for automating program startup and Event Triggering</u>

- Install AutoHotKey from their website (https://www.autohotkey.com/)
- Open a new document in Notepad called "launch.ahk"

Inside launch.ahk, enter the following text. Ensure to change the user name to whatever username is used on your computer.

```ahk
; startVision.ahk
; Handles the running of files required for camera streaming and driving,
; and then launching the layout preset with the shortcut.

Run, "C:\Program Files (x86)\FRC Driver Station\DriverStation.exe"
Run, "C:\Users\Public\wpilib\2020\tools\shuffleboard.vbs"
Run, "C:\Program Files (x86)\Google\Chrome\Application\chrome.exe" C:\Users\Admin\Desktop\WebJCC\viewer1.html --new-window
Run, "C:\Program Files (x86)\Google\Chrome\Application\chrome.exe" C:\Users\Admin\Desktop\WebJCC\viewer2.html --new-window
Run, "C:\Program Files (x86)\Google\Chrome\Application\chrome.exe" C:\Users\Admin\Desktop\WebJCC\viewer3.html --new-window

Sleep, 15000

Send, {LWin Down}{LShift Down}{F10}{LShift Up}{LWin Up}
```

Save that to the desktop, then launch the program to start your driver station environment!
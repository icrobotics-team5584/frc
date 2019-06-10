#!/usr/bin/python3

#Import libraries#
import os
import sys
import socket

#Variables

#MOTD Assignment
motd = '''    _              ___            __                     ___            __ 
   (_)____    ____/ (_)________  / /___ ___  __    _____/ (_)__  ____  / /_
  / / ___/   / __  / / ___/ __ \/ / __ `/ / / /   / ___/ / / _ \/ __ \/ __/
 / / /__    / /_/ / (__  ) /_/ / / /_/ / /_/ /   / /__/ / /  __/ / / / /_  
/_/\___/____\__,_/_/____/ .___/_/\__,_/\__, /____\___/_/_/\___/_/ /_/\__/  
      /_____/          /_/            /____/_____/                         
      Client Module. Ensure server is running on Jetson.
      '''
helpmsg = '''DisplayClient Help
========================================
Correct command usage: './icclient.py --ip 0.0.0.0 --port 0000'
Both of these arguments are required.

--ip
	Target IP Address of the computer running the server application.
--port
	Target Port of the computer running the server application.
'''

#Pre-loop
######################################################################
#Terminal clean-up and motd display
os.system("clear")
print(motd)

#Parse arguments from command line.
if len(sys.argv) <= 1: #Do a check if any arguments exist
	print(helpmsg)
	exit()
else:
	finder = 0
	print(" > Parsing arguments.")
	for i in range(0, len(sys.argv)):
		#print("Pass: " + str(i) + ", Argument: " + str(sys.argv[i])) #Shows pass status of the arguments list. This is only used for debugging.
		if i == 0:
			print("    > Ignoring the file name argument.") #We can ignore the file name argument, we don't need it.
		elif sys.argv[i] == "--ip":
			ipaddr = sys.argv[i+1]
			print("    > Detected IP Address " + str(ipaddr) + ".")
			finder = finder + 1 #increment counter for arguments found
		elif sys.argv[i] == "--port":
			port = sys.argv[i+1]
			print("    > Detected Port " + str(port) + ".")
			finder = finder + 1 #increment counter for arguments found

if finder != 2: #if not two args found, quit application.
	exit()

port = int(port) #ensure the port is an integer

print(" > Trying to connect to server over TCP at " + str(ipaddr) + ":" + str(port)) #Display message

#Connect
s = socket.socket()
s.connect((ipaddr, port))
#End connect

print("Connected to server.") #Display message. The program will crash on an error and this won't be displayed.

#Loop
######################################################################
message = ""
while message != "q" or "quit":
	message = input(">@> ")
	while message == "":
		message = input(">@> ")
	s.send(message.encode('utf-8'))
	data = s.recv(1024).decode('utf-8')
	print("Recieved from server: " + data)

s.close()
print("Connection closed.")

#Cleanup
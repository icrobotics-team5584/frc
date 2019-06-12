#!/usr/bin/python3

#Import libraries#
import os
import socket
import pygame

#Variables
port = 5800
timeout = 10

#MOTD Assignment
motd = '''    _              ___            __                     ___            __
   (_)____    ____/ (_)________  / /___ ___  __    _____/ (_)__  ____  / /_
  / / ___/   / __  / / ___/ __ \/ / __ `/ / / /   / ___/ / / _ \/ __ \/ __/
 / / /__    / /_/ / (__  ) /_/ / / /_/ / /_/ /   / /__/ / /  __/ / / / /_
/_/\___/____\__,_/_/____/ .___/_/\__,_/\__, /____\___/_/_/\___/_/ /_/\__/
      /_____/          /_/            /____/_____/
      Server Module.
      '''
helpmsg = '''DisplayClient Help
========================================
Correct command usage: './icdisplay.py --ip 0.0.0.0 --port 0000'
Both of these arguments are required.
'''

#Functions
######################################################################
def updateMessage(newText):
	windowSurface.fill((0,0,0))
	text = selectedFont.render(newText, True, (255,255,255), (0,0,255))
	textRect = text.get_rect()
	textRect.centerx = windowSurface.get_rect().centerx
	textRect.centery = windowSurface.get_rect().centery
	windowSurface.blit(text, textRect)
	drawLogo()
	pygame.display.update()
	pygame.event.get() #I'm not sure why we need this here, but it fixes our problems.
def drawLogo():
	logo = pygame.image.load('assets/iclogo-white.png')
	logo = pygame.transform.scale(logo, (100,100))
	windowSurface.blit(logo, (0,0))
def changeFont(fontName):
	try:
		globals()[fontName] #Check existence
		selectedFont = globals()[fontName]
		client_socket.send("CHANGED FONT.".encode('utf-8'))
	except KeyError:
		client_socket.send("FONT DOES NOT EXIST.".encode('utf-8'))
def displayImage(imageFile):
	print("Displaying image " + imageFile)
	activeImage = pygame.image.load(imageFile)
	activeImage = pygame.transform.scale(activeImage, (500, 500))
	activeImageRect = activeImage.get_rect()
	activeImageRect.centerx = windowSurface.get_rect().centerx
	activeImageRect.centery = windowSurface.get_rect().centery
	windowSurface.blit(activeImage, activeImageRect)
	pygame.display.update()
	pygame.event.get()
def recieveFile(outputPath):
	print("Ready to recieve file.")
	msg = "READY"
	client_socket.send(msg.encode('utf-8'))
	imageData = client_socket.recv(100000)
	client_socket.send("RECIEVED.".encode('utf-8'))
	print(imageData)
	f = open(outputPath, "wb+")
	f.write(imageData)
	f.close()
	displayImage(outputPath)

#Pre-loop
######################################################################
#Terminal clean-up and motd display
os.system("clear")
print(motd)
print(" > Listening on port " + str(port) + " for a total of " + str(timeout) + " seconds.")

#Connect
host = '0.0.0.0'

s = socket.socket()
s.bind((host, port))

#Set up PyGame Window
pygame.init()
windowSurface = pygame.display.set_mode((800,480),0,32)
pygame.display.set_caption("ic_display_client")
#Set Up PyGame Fonts
mstrFontSize = 48
fntBasic = pygame.font.SysFont(None, mstrFontSize)
fntComicSans = pygame.font.SysFont("Chalkduster", mstrFontSize)
#Set up PyGame Text
selectedFont = fntBasic
text = selectedFont.render('Ready to Connect!', True, (255,255,255), (0,0,255))
textRect = text.get_rect()
textRect.centerx = windowSurface.get_rect().centerx
textRect.centery = windowSurface.get_rect().centery
windowSurface.blit(text, textRect)

logo = pygame.image.load('assets/iclogo-white.png')
logo = pygame.transform.scale(logo, (100,100))
windowSurface.blit(logo, (0,0))

#Update PyGame Display
pygame.display.update()
pygame.event.get() #I'm not sure why we need this here, but it fixes our problems.

#Loop
######################################################################
s.listen(timeout)
client_socket, address = s.accept()
print("Connection from: " + str(address))
updateMessage("Connected from " + str(address[0]))

while True:
	data = client_socket.recv(1024).decode('utf-8')
	if not data:
		print("Not Data. Closing Connection.")
		break
	print("From user: " + data)
	if data[0:4] == "disp":
		parsed = data[5:]
		updateMessage(parsed)
		client_socket.send("DISPLAYED MESSAGE.".encode('utf-8'))
	elif data[0:4] == "font":
		parsed = data[5:]
		changeFont(parsed)
	elif data[0:5] == "fsize":
		parsed = data[6:]
		mstrFontSize = int(parsed)
	elif data[0:5] == "ulimg":
		parsed = data[6:]
		recieveFile(str(parsed))
	else:
		data = data.upper()
		client_socket.send("UNKNOWN COMMAND.".encode('utf-8'))
client_socket.close()

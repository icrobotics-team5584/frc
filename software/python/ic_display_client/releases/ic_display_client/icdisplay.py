#!/usr/bin/python3

#Import libraries#
import os
import socket
import pygame

#Variables
port = 5584
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
	text = basicFont.render(newText, True, (255,255,255), (0,0,255))
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

#Pre-loop
######################################################################
#Terminal clean-up and motd display
os.system("clear")
print(motd)
print(" > Listening on port 5584 for a total of " + str(timeout) + " seconds.")

#Connect
host = '0.0.0.0'
port = 5584

s = socket.socket()
s.bind((host, port))

#Set up PyGame Window
pygame.init()
windowSurface = pygame.display.set_mode((800,480),0,32)
pygame.display.set_caption("ic_display_client")
#Set Up PyGame Fonts
basicFont = pygame.font.SysFont(None, 48)
#Set up PyGame Text
text = basicFont.render('Ready to Connect!', True, (255,255,255), (0,0,255))
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
	else:
		data = data.upper()
		client_socket.send(data.encode('utf-8'))
client_socket.close()

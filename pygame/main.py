import pygame
import pygame.camera

pygame.init()
pygame.camera.init()

display = pygame.display.set_mode((640, 480), 0)

oui = True

while oui:
	events = pygame.event.get()
	for e in events:
		if e.type == QUIT:
			oui = False

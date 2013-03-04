# Basic L Systems Implementation


from time import *
from OpenGL.GL import *
from OpenGL.GLUT import *
from OpenGL.GLU import *
from math import cos, sin, radians
from random import randint


#SET of Parameters defining each image
image_sets = []

#Each image set comprises of (AXIOM, RULES, n, d, angle)
image_sets.append(('F', {'F':'F[+F][-F]F'}, 5, 10, 20))
image_sets.append(('X', {'X': 'F-[[X]+X]+F[+FX]-X', 'F': 'FF'}, 5, 5, 20))
image_sets.append(('X', {'X': 'F+F+F+F', 'F':'F+F-F-FF+F+F-F'}, 3, 10, 90))
image_sets.append(('X', {'X': 'F+F+F+F', 'F':'FF+F+F+F+FF'}, 4, 10, 90))
image_sets.append(('F', {'F': 'F[+F]F[-F]F'}, 5, 4, 25.7))
image_sets.append(('G', {'G' : 'GFX[+G][-G]', 'X' : 'X[-FFF][+FFF]FX'}, 6,2, 25.7))
image_sets.append(('SLFFF', {'S': '[+++G][---G]TS','G': '+H[- G]L', 'H':'-G[+ H]L', 'T': 'TL', 'L': '[-FFF][+FFF]F' }, 9, 6, 16))

CANVAS_WIDTH = 680.0
CANVAS_HEIGHT = 480.0

INITIAL_ROTATION = 90.0
INITIAL_LOCATION = {'x':340.0, 'y':50.0}

class LSystem:

  def __init__(self, axiom, rules):
	    self.axiom = axiom
	    self.grammar = axiom
	    self.rules = rules
	
	def reset(self):
		self.grammar = self.axiom

	# Function for making the string to be used for drawing the image
	def makeGrammar(self, iterations):
		
		#For the number of Iterations
		for i in range(0, iterations):
			newGrammar = ''
			# Evaluate the string and replace according to the rules			
			for c in self.grammar:
				if	(c in self.rules):
					newGrammar += self.rules[c]	
				else:
					newGrammar += c

			self.grammar = newGrammar

	# DrawGrammar function invoking calls to drawLine Function
	def drawGrammar(self):

		savedRotations = []
		savedLocations = []

		currentRotation = INITIAL_ROTATION
		currentLocation = INITIAL_LOCATION

		glClear(GL_COLOR_BUFFER_BIT)

		#Select action according to the character of the string
		for c in self.grammar:

			if (c == 'F'):
				currentLocation = self.drawLine(currentLocation, currentRotation)
			
			elif (c == '+'):
				if RANDOMNESS:
					currentRotation += (ANGLE + randint(-15, 15))
				else:
					currentRotation += (ANGLE)

			elif (c == '-'):
				if RANDOMNESS:
					# Randomness causes angle to vary differently each time
					currentRotation -= (ANGLE + randint(-15, 15))
				else:
					currentRotation -= (ANGLE)

			#Save the current location and rotation on the stack each time an opening paren is encountered			
			elif (c == '['):
				savedRotations.append(currentRotation)
				savedLocations.append(currentLocation)

			elif (c == ']'):
				currentRotation = savedRotations.pop()
				currentLocation = savedLocations.pop()

		glFlush() # Flush drawing commands to canvas

	def drawLine(self, startPoint, rotation):
		rads = radians(rotation)
		if RANDOMNESS:
			x = startPoint['x'] + (LINE_LEN + randint(-3, 5)) * cos(rads)
			y = startPoint['y'] + (LINE_LEN + randint(-3, 5)) * sin(rads)		
		else:
			x = startPoint['x'] + (LINE_LEN) * cos(rads)	
			y = startPoint['y'] + (LINE_LEN) * sin(rads)		
		endPoint = {'x':x, 'y':y}

		glBegin(GL_LINES)
		glVertex2f(startPoint['x'], startPoint['y'])
		glVertex2f(endPoint['x'], endPoint['y'])		
		glEnd()
		
		if DELAY:
			glFlush()
			sleep(0.1)

		return endPoint


#GL Setup Function for setting display mode, window size 
def setup():
	glutInit()
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB)
	glutInitWindowSize(int(CANVAS_WIDTH), int(CANVAS_HEIGHT))
	glutCreateWindow("Assignment 1 : q3")

# Initializing the parameters
def initGL():
	glClearColor(1.0, 1.0, 1.0, 0.0) #white bg color
	glColor3f(0.0, 0.0, 0.0) #black drawing color
	glMatrixMode(GL_PROJECTION)
	glLoadIdentity()
	gluOrtho2D(0.0, float(CANVAS_WIDTH), 0.0, float(CANVAS_HEIGHT))    
   
# Display Callback Function to be set
def display():
	axiom = AXIOM
	rules = RULES
	system = LSystem(axiom, rules)	
	system.makeGrammar(ITERATIONS)
	system.drawGrammar()

# Main sequence
def main():
	setup()
	glutDisplayFunc(display)
	initGL()
	
	# Global Variables used to define the parameters for the image
	global AXIOM, RULES, ITERATIONS, LINE_LEN, ANGLE
	global RANDOMNESS, DELAY

	# Options asked from User
	printstr = 'Enter the Index of Image (1 to '+str(len(image_sets))+'): '
	imagenum = raw_input(printstr)
	r = raw_input("Include Randomness (Enter 1 for yes and 0 for no): ")
	RANDOMNESS = int(r)
	DELAY = int(raw_input("Include Delay in Printing (Enter 1 for Yes ... ): "))

	#Parameters set according to the choice of the user
	print "Displaying Image ", imagenum
	AXIOM, RULES, ITERATIONS, LINE_LEN, ANGLE = image_sets[int(imagenum) -1]
	#Main Loop for drawing the image
	glutMainLoop()

if __name__ == '__main__': main()

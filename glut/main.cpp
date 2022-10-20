/**
* Authors: Venkatesh Pagadala, Ravi Teja Pilli, Cameron Weston, Vivek Kovi, Pranay Kalluri
* Course: CSC 525 
* Last Modified Date: 10/10/2022
* Description: Lab 8 - Rendering a pixel map from a binary file
* File: CSC525Lab8.cpp
* IDE / Compiler : Microsoft Visual Studio 2019
* INSTRUCTION FOR COMPILATION AND EXECUTION:
*	1. Double click on CSC525Lab6.sln (the solution file in my VS project) to OPEN the project
*	2. Press Ctrl+F7 to COMPILE
*	3. Press Ctrl+F5 to EXECUTE
*/

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <GLUT/glut.h>

using namespace std;

//prototypes
void myInit();
void drawPixelMap();
void myDisplayCallback();
void drawAxis();


//global variables
GLfloat pixelMap[512][512][3] = { 0 };
void* font = GLUT_BITMAP_8_BY_13;
string folder = "C:\\Temp\\";
string fileName = "autumn.ppm";
string fullLocation = folder + fileName;

int main(int argc, char** argv)
{
	//init window settings
	glutInit(&argc, argv);
	glutInitWindowSize(600, 600);				
	glutInitWindowPosition(100, 0);			
	glutCreateWindow("Lab 8: Pixel map");
	myInit();
	glutDisplayFunc(myDisplayCallback);

	//open the file
	ifstream file;
	file.open(fullLocation, ios::in | ios::binary);

	//check if file is open and end program if not
	if (!file.is_open())
	{
		cout << "\nERROR: File failed to open at location " << fullLocation << endl;
		return 1;
	}

	int* numberOfValues = new int;
	*numberOfValues = 512 * 512 * 3;
	float* numbersRead = new float[*numberOfValues];

	//read values from file to 1d float array
	file.read((char*)numbersRead, *numberOfValues * sizeof(float));

	/**
	//print out read numbers
	cout << endl << "Read numbers: " << endl;
	cout << setprecision(2) << fixed;
	for (int i = 0; i < *numberOfValues; i++)
	{
		cout << numbersRead[i] << " ";
	}
	cout << endl; */

	//move values from 1d array to 3d array
	int counter = 0;
	for (int height = 0; height < 512; height++)
	{
		for (int width = 0; width < 512; width++)
		{
			for (int depth = 0; depth < 3; depth++)
			{
				pixelMap[height][width][depth] = numbersRead[counter];
				counter++;
			}
		}
	}

	//close the files and deallocate memory
	file.close();
	delete numberOfValues;
	delete[] numbersRead;

	glutMainLoop();

	return 0;
}


void myInit()
{
	glClearColor(1, 1, 1, 0);		  //bg color	
	gluOrtho2D(-300, 300, -300, 300); //viewing aread
}

void myDisplayCallback()
{
	glClear(GL_COLOR_BUFFER_BIT);

	drawPixelMap();
	drawAxis();
	

	glFlush(); 
}

void drawPixelMap()
{
	glRasterPos2i(-256, -256);
	glDrawPixels(512, 512, GL_RGB, GL_FLOAT, (GLvoid*)pixelMap);
}

void drawAxis() {

	glColor3f(0, 0, 0);
	glBegin(GL_POINTS);

	for (int x = -150; x <= 150; x++) {
		glVertex2i(x, 0);
	}

	for (int y = -150; y <= 150; y++) {
		glVertex2i(0, y);
	}
	glEnd();

	glRasterPos2i(-3, 160);
	glutBitmapCharacter(font, 'Y');
	glRasterPos2i(160, -3);
	glutBitmapCharacter(font, 'X');
}



#include <cmath>
#include <iostream>
#include "MCG_GFX_Lib.h"
#include "Functions.h"

int main( int argc, char *argv[] )
{
	// Variable for storing window dimensions
	glm::ivec2 windowSize( 640, 480 );

	// Call MCG::Init to initialise and create your window
	// Tell it what size you want the window to be
	if( !MCG::Init( windowSize ) )
	{
		// We must check if something went wrong
		// (this is very unlikely)
		return -1;
	}

	// Sets every pixel to the same colour
	// parameters are RGB, numbers are from 0 to 1
	MCG::SetBackground( glm::vec3(0,0,0) );

	// Preparing a position to draw a pixel
	glm::ivec2 pixelPosition = windowSize / 2;

	// Preparing a colour to draw
	// Colours are RGB, each value ranges between 0 and 1

	//drawTriangle(320, 240, 1);
	//drawTriangle(320, 240, 2);
	//drawTriangle(320, 240, 3);
	//drawTriangle(320, 240, 4);
	midPointCircleDraw(320, 240, 150);

	// Displays drawing to screen and holds until user closes window
	// You must call this after all your drawing calls
	// Program will exit after this line
	return MCG::ShowAndHold();





	// Advanced access - comment out the above DrawPixel and MCG::ShowAndHold lines, then uncomment the following:
	/*
	
	// Variable to keep track of time
	float timer = 0.0f;

	// This is our game loop
	// It will run until the user presses 'escape' or closes the window
	while( MCG::ProcessFrame() )
	{
		// Set every pixel to the same colour
		MCG::SetBackground( glm::vec3(0,0,0) );

		// Change our pixel's X coordinate according to time
		pixelPosition.x = (windowSize.x / 2) + (int)(sin(timer) * 100.0f);
		// Update our time variable
		timer += 1.0f / 60.0f;

		// Draw the pixel to the screen
		MCG::DrawPixel( pixelPosition, pixelColour );

	}

	return 0;
	*/

}

void drawLine(float x1, float y1, float x2, float y2)
{
	glm::ivec2 pixelPosition = glm::ivec2(0, 0);
	glm::vec3 pixelColour(1, 0, 0);

	// Bresenham's line algorithm from roesettacode.org
	const bool steep = (fabs(y2 - y1) > fabs(x2 - x1));
	if (steep)
	{
		std::swap(x1, y1);
		std::swap(x2, y2);
	}

	if (x1 > x2)
	{
		std::swap(x1, x2);
		std::swap(y1, y2);
	}

	const float dx = x2 - x1;
	const float dy = fabs(y2 - y1);

	float error = dx / 2.0f;
	const int ystep = (y1 < y2) ? 1 : -1;
	int y = (int)y1;

	const int maxX = (int)x2;

	for (int x = (int)x1; x <= maxX; x++)
	{
		if (steep)
		{
			pixelPosition = glm::ivec2(y, x);
			MCG::DrawPixel(pixelPosition, pixelColour);
		}
		else
		{
			pixelPosition = glm::ivec2(x, y);
			MCG::DrawPixel(pixelPosition, pixelColour);
		}

		error -= dy;
		if (error < 0)
		{
			y += ystep;
			error += dx;
		}
	}
}

void drawTriangle(float x1, float y1, int type)
{
	float x2, y2, x3, y3;

	switch (type)
	{
	case 1:
		x2 = x1 + 50;
		y2 = y1 - 50;
		drawLine(x1, y1, x2, y1);
		drawLine(x1, y1, x1, y2);
		drawLine(x2, y1, x1, y2);
		break;
	case 2:
		x2 = x1 + 50;
		x3 = x1 + 25;
		y2 = y1 - 25;
		drawLine(x1, y1, x2, y1);
		drawLine(x2, y1, x3, y2);
		drawLine(x3, y2, x1, y1);
		break;
	case 3:
		x2 = x1 + 50;
		x3 = x1 + 25;
		y2 = y1 - 50;
		drawLine(x1, y1, x2, y1);
		drawLine(x2, y1, x3, y2);
		drawLine(x3, y2, x1, y1);
		break;
	case 4:
		x2 = x1 + 15;
		y2 = y1 + 35;
		x3 = x1 + 55;
		y3 = y1 - 40;
		drawLine(x1, y1, x2, y2);
		drawLine(x2, y2, x3, y3);
		drawLine(x3, y3, x1, y1);
		break;
	default:
		std::cout << "Error: Unknown triangle requested" << std::endl;
	}
}

// Implementing Mid-Point Circle Drawing Algorithmm from geeksforgeeks.org
void midPointCircleDraw(int x_centre, int y_centre, int r)
{
	glm::ivec2 pixelPosition = glm::ivec2(0, 0);
	glm::vec3 pixelColour(1, 0, 0);

	int x = r, y = 0;

	// When radius is zero only a single
	// point will be printed
	if (r > 0)
	{
		pixelPosition = glm::ivec2(x + x_centre, -y + y_centre);
		MCG::DrawPixel(pixelPosition, pixelColour);
		pixelPosition = glm::ivec2(y + x_centre, x + y_centre);
		MCG::DrawPixel(pixelPosition, pixelColour);
		pixelPosition = glm::ivec2(-y + x_centre, x + y_centre);
		MCG::DrawPixel(pixelPosition, pixelColour);
	}

	// Initialising the value of P
	int P = 1 - r;
	while (x > y)
	{
		y++;

		// Mid-point is inside or on the perimeter
		if (P <= 0)
			P = P + 2 * y + 1;

		// Mid-point is outside the perimeter
		else
		{
			x--;
			P = P + 2 * y - 2 * x + 1;
		}

		// All the perimeter points have already been printed
		if (x < y)
			break;

		// Printing the generated point and its reflection
		// in the other octants after translation
		pixelPosition = glm::ivec2(x + x_centre, y + y_centre);
		MCG::DrawPixel(pixelPosition, pixelColour);
		pixelPosition = glm::ivec2(-x + x_centre, y + y_centre);
		MCG::DrawPixel(pixelPosition, pixelColour);
		pixelPosition = glm::ivec2(x + x_centre, -y + y_centre);
		MCG::DrawPixel(pixelPosition, pixelColour);
		pixelPosition = glm::ivec2(-x + x_centre, -y + y_centre);
		MCG::DrawPixel(pixelPosition, pixelColour);

		// If the generated point is on the line x = y then 
		// the perimeter points have already been printed
		if (x != y)
		{
			pixelPosition = glm::ivec2(y + x_centre, x + y_centre);
			MCG::DrawPixel(pixelPosition, pixelColour);
			pixelPosition = glm::ivec2(-y + x_centre, x + y_centre);
			MCG::DrawPixel(pixelPosition, pixelColour);
			pixelPosition = glm::ivec2(y + x_centre, -x + y_centre);
			MCG::DrawPixel(pixelPosition, pixelColour);
			pixelPosition = glm::ivec2(-y + x_centre, -x + y_centre);
			MCG::DrawPixel(pixelPosition, pixelColour);
		}
	}
}
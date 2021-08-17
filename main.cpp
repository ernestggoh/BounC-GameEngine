#include <iostream> 

#include <glfw3.h> 

#include "window.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <list>
#include <iterator>

#define PRINT(x) std::cout << x << std::endl
class coord {
public:
	double x;
	double y;
	int lifetime;
	bool alive = false;
	double size = 0.1;
	GLfloat colour1;
	GLfloat colour2;
	GLfloat colour3;
};
bool pointInRectangle(double x, double y, double x1, double y1, double size) {
	return (x >= x1) && (y >= y1) && (x <= x1 + size) && (y <= y1 + size);
}
bool pointInRectangle(coord pt1, coord pt2) {
	return pointInRectangle(pt1.x, pt1.y, pt2.x, pt2.y, pt2.size);
}
bool colliding(double x, double y, double x1, double y1, double size, double size1) {
	return pointInRectangle(x, y, x1, y1, size1)
		|| pointInRectangle(x + size, y, x1, y1, size1)
		|| pointInRectangle(x + size, y + size, x1, y1, size1)
		|| pointInRectangle(x, y + size, x1, y1, size1);
}
void drawQuad(double x, double y, double size, GLfloat colour1, GLfloat colour2, GLfloat colour3) {
	//PRINT("drawing");
	glBegin(GL_QUADS);
	glColor3f(colour1, colour2, colour3);
	glVertex2f(x, y);
	glVertex2f(x + size, y);
	glVertex2f(x + size, y + size);
	glVertex2f(x, y + size);
	glEnd();
}
void randomMove(double x, double y, double move, int randomMoveFactor) {
	if (randomMoveFactor == 0) {
		if (x > -1) {
			x -= move;
		}
	}
	else if (randomMoveFactor == 1) {
		if (y > -1) {
			y -= move;
		}
	}
	else if (randomMoveFactor == 2) {
		if (y < 0.9) {
			y += move;
		}
	}
	else if (randomMoveFactor == 3) {
		if (x < 0.9) {
			x += move;
		}
	}
}
void renderPoint(coord pt) {
	if (pt.alive) {
		//PRINT("rendering");
		drawQuad(pt.x, pt.y, pt.size, pt.colour1, pt.colour2, pt.colour3);
	}
}
bool setAlive(coord pt) {
	if (pt.lifetime <= 0) {
		if (pt.alive) {
			return true;
		}
		pt.alive = false;

	}
	return false;
}
int setPoints(coord pt1, coord pt2) {
	PRINT("settingpoints");
	int returnVal = 0;
	if (pt1.alive) {

	}
	else {
		pt1.x = (rand() % 20) * 0.1 - 1;
		pt1.y = (rand() % 20) * 0.1 - 1;
		pt1.alive = true;
		pt1.lifetime = 1000;
		returnVal += 1;
	}
	if (pt2.alive == false) {

	}
	else {
		pt2.x = (rand() % 20) * 0.1 - 1;
		pt2.y = (rand() % 20) * 0.1 - 1;
		pt2.alive = true;
		pt2.lifetime = 1000;
		returnVal += 1;
	}
	return returnVal;

}


int main() {

	using namespace bounc;
	using namespace graphics;

	Window window("bounc!", 600, 600);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	//glClearColor(0.2f, 0.3f, 0.8f, 1.0f);

	std::list <coord> list1;
	int timer = 1;
	int points = 0;
	int random = rand() % 4;
	coord pt1;
	coord pt2;
	pt1.x = (rand() % 20) * 0.1 - 1;
	pt1.y = (rand() % 20) * 0.1 - 1;
	pt1.alive = true;
	pt1.lifetime = 100000;
	pt1.colour1 = 1.0f;
	pt1.colour2 = 0.0f;
	pt1.colour3 = 0.0f;
	pt2.x = (rand() % 19) * 0.1 - 1;
	pt2.y = (rand() % 19) * 0.1 - 1;
	pt2.alive = true;
	pt2.lifetime = 100000;
	pt2.colour1 = 0.0f;
	pt2.colour2 = 1.0f;
	pt2.colour3 = 0.0f;
	double size = 0.1;
	double avatarSize = 0.1;
	double move = 0.001;
	int targets = 2;
	int difficulty = 1;
	srand(time(0));



	while (!window.closed()) {
		timer += 1;
		difficulty = points;
		pt1.lifetime -= difficulty;
		pt2.lifetime -= difficulty;

		if (pt1.lifetime <= 0) {
			pt1.alive = false;
			PRINT("GAME OVER :(");
			break;
		}
		if (pt2.lifetime <= 0) {
			pt2.alive = false;
			PRINT("GAME OVER :(");
			break;
		}
		pt1.size = pt1.lifetime / 500000.0;
		pt2.size = pt2.lifetime / 500000.0;
		//PRINT("CP1");
		window.clear();


		double xMouse, yMouse;
		if (window.isMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT)) {
			window.getMousePosition(xMouse, yMouse);
			coord mouseCoord;
			mouseCoord.x = ((double)xMouse / (double)300) - 1;
			mouseCoord.y = ((double)((yMouse - 600) * -1) / (double)300) - 1;
			if (pointInRectangle(mouseCoord, pt1)) {
				pt1.lifetime = 0;
				pt1.alive = false;
				points += 1;
				targets += 1;
				PRINT("Points: " << points);
			}
			if (pointInRectangle(mouseCoord, pt2)) {
				pt2.lifetime = 0;
				pt2.alive = false;
				points += 1;
				targets += 1;
				PRINT("Points: " << points);
			}
		}
		if (window.isMouseButtonPressed(GLFW_MOUSE_BUTTON_RIGHT)) {
			window.getMousePosition(xMouse, yMouse);
			coord mouseCoord;
			mouseCoord.x = ((double)xMouse / (double)300) - 1;
			mouseCoord.y = ((double)((yMouse - 600) * -1) / (double)300) - 1;
			if (pointInRectangle(mouseCoord, pt1)) {
				pt1.lifetime = 0;
				pt1.alive = false;
				points += 1;
				targets += 1;
				PRINT("Points: " << points);
			}
			if (pointInRectangle(mouseCoord, pt2)) {
				pt2.lifetime = 0;
				pt2.alive = false;
				points += 1;
				targets += 1;
				PRINT("Points: " << points);
			}
		}
		//targets += setPoints(pt1, pt2);
		if (pt1.alive == false) {
			pt1.x = (rand() % 19) * 0.1 - 1;
			pt1.y = (rand() % 19) * 0.1 - 1;
			pt1.alive = true;
			pt1.lifetime = 100000;
			targets += 1;
		}
		if (pt2.alive == false) {
			pt2.x = (rand() % 19) * 0.1 - 1;
			pt2.y = (rand() % 19) * 0.1 - 1;
			pt2.alive = true;
			pt2.lifetime = 100000;
			targets += 1;
		}

		
		renderPoint(pt1);
		renderPoint(pt2);
		glFlush();

		/*drawQuad(x, y, avatarSize, 1.0f, 0.0f, 0.0f);
		drawQuad(xFood, yFood, size, 0.0f, 0.0f, 1.0f);
		drawQuad(xEnemy, yEnemy, size, 0.0f, 1.0f, 0.0f);

		glFlush();*/


		window.update();
	}

	glfwTerminate();

	return 0;
}

//PRINT(mouseCoord.x << ", " << mouseCoord.y);
			/*std::list<coord> listCopy(list1);
			std::list <coord> ::iterator it;
			for (it = listCopy.begin(); it != listCopy.end(); ++it)
				if (pointInRectangle(mouseCoord.x, mouseCoord.y, it->x, it->y, size)) {
					list1.remove(it);
				}*/

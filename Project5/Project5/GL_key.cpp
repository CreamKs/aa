// 키보드 조작
#include "gl_func.h"
#include "translate.h"

void keyDown(unsigned char KEY, int x, int y) {
	switch (KEY) {
	case 'c':
		setColorLight(rand() % 3 + 1);
		break;
	case 'y':
		setTransformLight(1);
		break;
	case 'Y':
		setTransformLight(2);
		break;
	case 27:  // ESC
		glutDestroyWindow(1);
		break;
	}
	if (glutGetWindow() != 0)
		glutPostRedisplay();
}

void keyUp(unsigned char KEY, int x, int y) {
	switch (KEY) {
	case 0:
		break;
	}
	if (glutGetWindow() != 0)
		glutPostRedisplay();
}

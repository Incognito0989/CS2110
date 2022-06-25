#ifndef MAIN_H
#define MAIN_H

#include "gba.h"

// TODO: Create any necessary structs

/*
* For example, for a Snake game, one could be:
*
* struct snake {
*   int heading;
*   int length;
*   int row;
*   int col;
* };
*
* Example of a struct to hold state machine data:
*
* struct state {
*   int currentState;
*   int nextState;
* };
*
*/
struct platform {
  int col;
  int row;
  int disp;
  int width;
  int height;
};

struct picha {
	int row;
	int col;
	int disp;
	int height;
	int width;
	int deaths;
	int jump;
	int gravity;
	int crouch;
};
struct block {
	int row;
	int col;
	int width;
	int height;
};

struct death {
	char c[10];
}d1;

struct bullet {
	int row;
	int col;
	int size;
	int speed;
};

#endif

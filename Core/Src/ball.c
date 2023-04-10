/*
 * ball.c
 *
 *  Created on: Mar 26, 2023
 *      Author: Даньо
 */
#include "../Inc/ball.h"



cBall* newBall(int16_t coordX, int16_t coordY, int8_t radius, int8_t dirX, int8_t dirY) {
	cBall* newBall = malloc(sizeof(cBall));
	newBall->base.xCoord = coordX;
	newBall->base.yCoord = coordY;
	newBall->rad = radius;
	newBall->xSpeed = dirX;
	newBall->ySpeed = dirY;

	return newBall;
}


/*
 * ball.h
 *
 *  Created on: Mar 26, 2023
 *      Author: Даньо
 */
#include <base.h>

typedef struct Ball {
	cBase base;
	int8_t rad;
	int8_t xSpeed;
	int8_t ySpeed;
} cBall;

cBall* newBall(int16_t, int16_t, int8_t, int8_t, int8_t);

/*
void destroyBall();
*/

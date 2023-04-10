#ifndef USER_CLASSES
#define USER_CLASSES

#include <stdint.h>
#include <stdlib.h>

typedef struct Base{
	uint16_t xCoord;
	uint16_t yCoord;
} cBase;

typedef struct Board{
	cBase base;
	uint8_t length;
} cBoard;

typedef struct Target {
	struct Base base;
	uint8_t size;
} cTarget;

typedef struct Ball {
	struct Base base;
	uint16_t rad;
	int16_t xSpeed;
	int16_t ySpeed;
} cBall;

typedef struct Button {
	struct Base base;
	uint8_t width;
	uint8_t height;
	uint8_t* text;
} cButton;

cBall* newBall(uint16_t coordX, uint16_t coordY, uint16_t radius, int16_t spX, int16_t spY) {
	cBall* newBall = malloc(sizeof(cBall));
	newBall->base.xCoord = coordX;
	newBall->base.yCoord = coordY;
	newBall->rad = radius;
	newBall->xSpeed = spX;
	newBall->ySpeed = spY;

	return newBall;
}

cTarget* newTarget(uint16_t coordX, uint16_t coordY, uint8_t s) {
	cTarget* newTarget = malloc(sizeof(cTarget));
	newTarget->base.xCoord = coordX;
	newTarget->base.yCoord= coordY;
	newTarget->size = s;

	return newTarget;
}

cBoard* newBoard(uint16_t coordX, uint16_t coordY, uint16_t len) {
	cBoard* newBoard = malloc(sizeof(cBoard));
	newBoard->base.xCoord = coordX;
	newBoard->base.yCoord = coordY;
	newBoard->length = len;

	return newBoard;
}

cButton* newButton(uint16_t coordX, uint16_t coordY, uint8_t w, uint8_t h, uint8_t* txt) {
	cButton* newButton = malloc(sizeof(cButton));
	newButton->base.xCoord = coordX;
	newButton->base.yCoord = coordY;
	newButton->width = w;
	newButton->height = h;
	newButton->text = txt;

	return newButton;
}

void displayBoard(cBoard board) {
	BSP_LCD_DrawHLine(board.base.xCoord, board.base.yCoord, board.length);
}

void displayButton(cButton button, uint8_t offset) {
	BSP_LCD_DrawRect(button.base.xCoord, button.base.yCoord, button.width, button.height);
	BSP_LCD_DisplayStringAt(button.base.xCoord + ((button.width - BSP_LCD_GetFont()->Width * strlen(button.text)) / 2), button.base.yCoord + ((button.height - BSP_LCD_GetFont()->Height) / 2), button.text, LEFT_MODE);
}

void displayBall(cBall ball) {
	BSP_LCD_FillCircle(ball.base.xCoord, ball.base.yCoord, ball.rad);
}

#endif

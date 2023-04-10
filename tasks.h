#ifndef TASKS
#define TASKS

#include "helper_funcs.h"
#include "defines.h"
#include "lcd_funcs.h"

// Queue Handlers
QueueHandle_t boardQueue;
QueueHandle_t ballQueue;
QueueHandle_t targetQueue;
QueueHandle_t livesQueue;
QueueHandle_t targetsQueue;

// Task handles
xTaskHandle hStartScreen;
xTaskHandle hMoveBall;
xTaskHandle hMoveBoard;
xTaskHandle hDrawTargets;
xTaskHandle hEndScreen;
xTaskHandle hManageGameData;

// Default Task Handler
osThreadId defaultTaskHandle;

void startScreen(void* parameters) {

	// Displaying start screen
	BSP_LCD_SetBackColor(BACKGROUND_COLOR);
	BSP_LCD_SetTextColor(OBJECT_COLOR);
	BSP_LCD_SetFont(&Font24);
	BSP_LCD_DisplayStringAt(0, 150, (uint8_t*) "Ball Game", CENTER_MODE);
	BSP_LCD_SetTextColor(SUBTEXT_COLOR);
	BSP_LCD_SetFont(&Font8);
	BSP_LCD_DisplayStringAt(0, 200, (uint8_t*) "Press button to start", CENTER_MODE);

	// Waiting for user button to be pressed
	while (1) {
		if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0)) {

			// Resuming game tasks and clearing screen
			fillWithColorLCD(FRAME_BUF_1, LCD_COLOR_BLACK);
			BSP_LCD_LayerDefaultInit(0, FRAME_BUF_1_ADDRESS);
			vTaskResume(hMoveBall);
			vTaskResume(hMoveBoard);
			vTaskResume(hDrawTargets);
			vTaskResume(hManageGameData);

			vTaskDelay(1);
		}
	}
}

// Detects gyroscope movement to the left or right and moves the plot accordingly
void moveBoard(void *parameters) {

	// Variable containing gyroscope offset
	int deltaX = 0;

	// cBoard object passed from main via boardQueue
	cBoard *board;

	xQueueReceive(boardQueue, &(board), portMAX_DELAY);

	while (1) {

		// Deleting plot before moving it
		BSP_LCD_SetTextColor(BACKGROUND_COLOR);
		displayBoard(*board);
		BSP_LCD_SetTextColor(OBJECT_COLOR);

		// Calculating average gyroscope offset
		deltaX = getAverageGyroReading() / 400;

		// Checking if average gyroscope value is small or large enough for movement
		if(deltaX < -100) {

			// If average gyroscope value is small enough, move plot left
			if(board->base.xCoord > LCD_OFFSET) {
				board->base.xCoord -= 2;
			}
		}
		else if(deltaX > 100) {

			// If average gyroscope value is large enough, move plot right
			if(board->base.xCoord + board->length < LCD_WIDTH - LCD_OFFSET) {
				board->base.xCoord += 2;
			}
		}

		// Display plot at new location
		displayBoard(*board);

		vTaskDelay(5);
	}
}

// Move ball location or change trajectory after collision
// Ball can collide with screen boundaries, targets or the board
void moveBall(void *parameters) {

	vTaskSuspend(hStartScreen);

	// Game object passed from main
	cBall* ball;
	cBoard* board;

	// Game data passed from main
	int *remainingLives = NULL;

	xQueueReceive(livesQueue, &remainingLives, portMAX_DELAY);
	xQueueReceive(ballQueue, &ball, portMAX_DELAY);
	xQueueReceive(boardQueue, &board, portMAX_DELAY);

	while (1) {

		// Deleting ball before moving it
		BSP_LCD_SetTextColor(BACKGROUND_COLOR);
		displayBall(*ball);
		BSP_LCD_SetTextColor(OBJECT_COLOR);

		// update ball position
		ball->base.xCoord += ball->xSpeed;
		ball->base.yCoord += ball->ySpeed;

		// handle collisions with left screen edge
		if (ball->base.xCoord - ball->rad <= 0) {

			ball->xSpeed *= -1;
		}

		// handle collisions with right screen edge
		if (ball->base.xCoord + ball->rad >= LCD_WIDTH) {

			ball->xSpeed *= -1;
		}

		// handle collisions with top screen edge
		if (ball->base.yCoord - ball->rad <= 25) {

			ball->ySpeed *= -1;
		}

		// handle collisions with plot
		if(ball->base.yCoord + ball->rad == board->base.yCoord) {

			if(ball->base.xCoord > board->base.xCoord && ball->base.xCoord < board->base.xCoord + board->length) {

				ball->ySpeed *= -1;
			}
		}

		// handle ball falling below plot
		if(ball->base.yCoord > BOARD_Y) {

			vTaskDelay(350);
			free(ball);
			ball = newBall();

			(*remainingLives)--;
		}

		// Displaying ball after moving
		displayBall(*ball);

		vTaskDelay(10);
	}
}

// Draws all active targets at random positions, without overlapping
// Ball can collide with target, causing it to disappear
void drawTargets(void *parameters) {

	// Game object passed from main
	cBall *ball;

	// Game data passed from main
	int *targetsRemaining;

	// Array containing all targets
	cTarget targetArray[INITIAL_TARGETS];

	// Shows us if target hasbeen hit
	bool targetHit = false;

	cTarget *ptrTargetArray;
	uint8_t control1;
	uint8_t control2;

	xQueueReceive(ballQueue, &ball, portMAX_DELAY);
	xQueueReceive(targetsQueue, &targetsRemaining, portMAX_DELAY);

	// Creating targets with random coordinates, without them overlapping
	for (int i = 0; i < 5; i++) {

		if (i == 0) {

			targetArray[i] = *newTarget();
		} else {

			control1 = 0;
			while (control1 == 0) {

				targetArray[i] = *newTarget();
				ptrTargetArray = targetArray;
				control2 = 0;
				while (control2 == 0) {

					if (targetArray[i].isWithingRange(&targetArray[i],
							ptrTargetArray) == true) {
						control2 = 1;
					} else if (ptrTargetArray != &targetArray[i - 1]) {

						ptrTargetArray++;
					} else {

						control2 = 1;
						control1 = 1;
					}
				}
			}
		}
	}


	// Displaying targets
	for (int i = 0; i < 5; i++)
		targetArray[i].displayTarget(TARGET_COLOR, &targetArray[i]);

	// Checking for ball-target collision
	// Erases target hit, changes ball trajectory and reduces targetsRemaining
	while (1) {
		for (int i = 0; i < 5; i++) {

			targetHit = false;
			if (targetArray[i].isActive == true) {

				if (ball->base.xCoord >= (targetArray[i].base.xCoord - targetArray[i].size / 2 - ball->rad)
					&& ball->base.xCoord <= (targetArray[i].base.xCoord + targetArray[i].size / 2 + ball->rad)) {

					// Ball hits top of target
					if (ball->base.yCoord == (targetArray[i].base.yCoord - targetArray[i].size / 2 - ball->rad)) {

						targetArray[i].displayTarget(BACKGROUND_COLOR, &targetArray[i]);
						targetArray[i].isActive = false;
						ball->ySpeed *= -1;
						targetHit = true;
					}

					// Ball hits bottom of target
					if (ball->base.yCoord == (targetArray[i].base.yCoord + targetArray[i].size / 2 + ball->rad)) {

						targetArray[i].displayTarget(BACKGROUND_COLOR, &targetArray[i]);
						targetArray[i].isActive = false;
						ball->ySpeed *= -1;
						targetHit = true;
					}
				}

				if (ball->base.yCoord >= (targetArray[i].base.yCoord - targetArray[i].size / 2 - ball->rad)
					&& ball->base.yCoord <= (targetArray[i].base.yCoord + targetArray[i].size / 2 + ball->rad)) {

					// Ball hits left side of target
					if (ball->base.xCoord == (targetArray[i].base.xCoord - targetArray[i].size / 2 - ball->rad)) {

						targetArray[i].displayTarget(BACKGROUND_COLOR, &targetArray[i]);
						targetArray[i].isActive = false;
						ball->xSpeed *= -1;
						targetHit = true;
					}

					// Ball hits right side of target
					if (ball->base.xCoord == (targetArray[i].base.xCoord + targetArray[i].size / 2 + ball->rad)) {

						targetArray[i].displayTarget(BACKGROUND_COLOR, &targetArray[i]);
						targetArray[i].isActive = false;
						ball->xSpeed *= -1;
						targetHit = true;
					}
				}
			}

			if (targetHit)
				(*targetsRemaining)--;
		}

		vTaskDelay(1);
	}
}

void displayGameData(void *parameters) {

	// Game data passed from main
	int* remainingTargets;
	int* remainingLives;

	// Time when game starts
	uint8_t startingTime = HAL_GetTick();

	// Time to be displayed
	uint8_t minutesAfterStart = 0;
	uint8_t secondsAfterStart = 0;

	char str[50];

	xQueueReceive(livesQueue, &remainingLives, portMAX_DELAY);
	xQueueReceive(targetsQueue, &remainingTargets, portMAX_DELAY);
	xQueueSend(targetsQueue, &remainingTargets, portMAX_DELAY);

	while(1) {

		// Enable endScreen, if any game ending event occurs
		// Otherwise, display game data at the top of the screen
		if(*remainingTargets == 0 || *remainingLives == 0 || HAL_GetTick() - startingTime >= 300000) {

			vTaskResume(hEndScreen);
		}
		else {

			// Calculate remaining time
			minutesAfterStart = 4 - (HAL_GetTick() - startingTime) / 60000;
			secondsAfterStart = 60 - ((HAL_GetTick() - startingTime) % 60000) / 1000;

			// Display game data at the top of the screen
			BSP_LCD_SetFont(&Font12);
			BSP_LCD_SetBackColor(BACKGROUND_COLOR);
			BSP_LCD_SetTextColor(OBJECT_COLOR);
			sprintf(str, "Targets: %d  Time: %d:%d", *remainingTargets, minutesAfterStart, secondsAfterStart);
			BSP_LCD_DisplayStringAt(20, 10, (uint8_t*)str, CENTER_MODE);
			uint16_t xHeart=5,yHeart=8;

			switch (*remainingLives){
			case 1:
				xHeart+=16;
				drawHeart(xHeart,yHeart,LCD_COLOR_BLACK);
			break;
			case 2:
				xHeart+=16*2;
				drawHeart(xHeart,yHeart,LCD_COLOR_BLACK);
			break;
			case 3:
				for(int i=0; i<3; i++){
					drawHeart(xHeart,yHeart,LCD_COLOR_RED);
					xHeart+=16;
				}
			break;
			}
		}

		vTaskDelay(1);
	}
}

void endScreen(void *parameters) {

	// Suspend all other tasks
	vTaskSuspend(hMoveBoard);
	vTaskSuspend(hMoveBall);
	vTaskSuspend(hDrawTargets);
	vTaskSuspend(hStartScreen);
	vTaskSuspend(hManageGameData);

	// Game data passed from main
	int* remainingTargets;

	xQueueReceive(targetsQueue, &remainingTargets, portMAX_DELAY);

	// Display Win or Lose message
	fillWithColorLCD(FRAME_BUF_1, BACKGROUND_COLOR);
	if (*remainingTargets == 0) {
		BSP_LCD_SetTextColor(OBJECT_COLOR);
		BSP_LCD_DisplayStringAt(0, 150, (uint8_t*) "You Win!", CENTER_MODE);
	} else {
		BSP_LCD_SetTextColor(TARGET_COLOR);
		BSP_LCD_DisplayStringAt(0, 150, (uint8_t*) "You Lose!", CENTER_MODE);
	}

	// Infinite loop
	while(1) {

	}
}

#endif

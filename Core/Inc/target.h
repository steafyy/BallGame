#include <stdbool.h>
#include "../../Drivers/BSP/stm32f429i_discovery_lcd.h"
#include <../Src/classes.c>

typedef struct Target {
	cBase base;
	uint8_t size;
	bool isActive;
	void (*drawFilledSquareLCD)(uint16_t LCD_WIDTH,uint16_t LCD_HEIGHT,uint8_t FRAME_BUF_1, uint8_t FRAME_BUF_2,
			uint32_t FRAME_BUF_1_ADDRESS, uint32_t FRAME_BUF_2_ADDRESS, uint8_t frameBufIndex,uint32_t color,
			struct Target *this);
	bool (*isWithingRange)(struct Target *targetA, struct Target *targetB);
}cTarget;

cTarget* newTarget(uint16_t, uint16_t, uint8_t, bool);

/*
void destroyTarget();
*/


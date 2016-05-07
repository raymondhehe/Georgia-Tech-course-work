#include "start.h"
#include "gameover.h"
#include "win.h"
#include "lv1.h"
#include "lv2.h"
#include "mylib.h"
#include "stdbool.h"
#include <stdio.h>
#include <stdlib.h>


bool catch(int row1, int col1, int row2, int col2, int size) {
	return ((col1 >= (col2 - size) && col1 <= (col2 + size))
 			&& (row1 >= (row2 - size) && row1 <= (row2 + size)));
}

struct square {
	int row;
	int col;
	int size;
};

enum GBAState {
	START,
	LV1,
	LV2,
	WIN,
	LOSE
};

void move(struct square *self) {
	if (KEY_DOWN_NOW(BUTTON_UP)) {
		(*self).row--;
	}
	if (KEY_DOWN_NOW(BUTTON_DOWN)) {
		(*self).row++;
	}
	if (KEY_DOWN_NOW(BUTTON_LEFT)) {
		(*self).col--;
	}
	if (KEY_DOWN_NOW(BUTTON_RIGHT)) {
		(*self).col++;
	}
}

void checkBoundary(struct square *self, int size) {
	if ((*self).row < 0) {
		(*self).row = 0;
	}
	if ((*self).row > 159 - size + 1) {
		(*self).row = 159 - size + 1;
	}
	if ((*self).col < 31) {
		(*self).col = 31;
	}
	if ((*self).col > 239 - size + 1) {
		(*self).col = 239 - size + 1;
	}
}

void randomMove(struct square *obj, int size, int rand) {
	switch(rand) {
		case 0:
			if ((*obj).col > 220 - size) {
				(*obj).col = 240 - size * 2;
			} else {
				(*obj).col = (*obj).col + 20;
			}
			break;
		case 1:
			if ((*obj).col <= 50) {
				(*obj).col = 30;
			} else {
				(*obj).col = (*obj).col - 20;
			}
			break;
		case 2:
			if ((*obj).row >= 140 - size) {
				(*obj).row = 160 - size * 2;
			} else {
				(*obj).row = (*obj).row + 20;
			}
			break;
		case 3:
			if ((*obj).row <= 20) {
				(*obj).row = 0;
			} else {
				(*obj).row = (*obj).row - 20;
			}
			break;
	}
}

int main(void) {
	REG_DISPCTL = MODE3 | BG2_ENABLE;

	enum GBAState state = START; 
	
	while(1) {
		switch(state) {
		case START:
		drawImage3(0, 0, START_WIDTH, START_HEIGHT, start);
		while(!KEY_DOWN_NOW(BUTTON_START)) {};
		state = LV1;
		while(KEY_DOWN_NOW(BUTTON_START)) {};
		break;

		case LV1:
		fillScreen(BLACK);
		drawImage3(0, 0, LV1_WIDTH, LV1_HEIGHT, lv1);
		drawRect(30, 0, 30, 130, WHITE);
		struct square self;
		struct square old_self;
		struct square obj1;
		struct square old_obj1;
		int size = 5;
		self.row = 160; self.col = 120; self.size = 5;
		obj1.row = rand() % 161; obj1.col = rand() % 211 + 30; obj1.size = 5;
		int i = 0;
		while (1) {
			drawString(0, 30,"Press Backspace for restart! ",WHITE);
			old_self.row = self.row; old_self.col = self.col; old_self.size = self.size;
			if (KEY_DOWN_NOW(BUTTON_SELECT)) {
				state = START;
				break;
			}
			move(&self);
			checkBoundary(&self, size);
			if (catch(self.row, self.col, obj1.row, obj1.col, size)) {
				state = LV2;
				break;
			}
			int randI = rand() % 4;
			old_obj1.row = obj1.row; old_obj1.col = obj1.col; old_obj1.size = obj1.size;
			if (i == 10) {
				i = 0;
				randomMove(&obj1, size, randI);
				drawRect(obj1.row, obj1.col, obj1.size, obj1.size, GREEN);
				drawRect(old_obj1.row, old_obj1.col, old_obj1.size, old_obj1.size, BLACK);
			} else {
				drawRect(obj1.row, obj1.col, obj1.size, obj1.size, GREEN);
			}
			waitForVblank();
			drawRect(old_self.row, old_self.col, old_self.size, old_self.size, BLACK);
			drawRect(self.row, self.col, self.size, self.size, RED);
			i++;
			
		}
		break;

		case LV2:
		fillScreen(BLACK);
		drawImage3(0, 0, LV2_WIDTH, LV2_HEIGHT, lv2);
		drawRect(30, 0, 30, 130, WHITE);
		//struct square obj2;
		//struct square old_obj2;
		struct square bad;
		struct square old_bad;
		self.row = 160; self.col = 120; self.size = 5;
		obj1.row = rand() % 161; obj1.col = rand() % 211 + 30; obj1.size = 5;
		bad.row = rand() % 161; bad.col = rand() % 211 + 30; bad.size = 5;
		i = 0;
		while (1) {
			drawString(0, 30,"Press Backspace for restart! ",WHITE);
			old_self.row = self.row; old_self.col = self.col; old_self.size = self.size;
			if (KEY_DOWN_NOW(BUTTON_SELECT)) {
				state = START;
				break;
			}
			move(&self);
			checkBoundary(&self, size);
			if (catch(self.row, self.col, obj1.row, obj1.col, size)) {
				state = WIN;
				break;
			}
			if (catch(self.row, self.col, bad.row, bad.col, size)) {
				state = LOSE;
				break;
			}
			int randI1 = rand() % 4;
			int randI2 = rand() % 4;
			old_obj1.row = obj1.row; old_obj1.col = obj1.col; old_obj1.size = obj1.size;
			old_bad.row = bad.row; old_bad.col = bad.col; old_bad.size = bad.size;
			if (i == 10) {
				i = 0;
				randomMove(&obj1, size, randI1);
				randomMove(&bad, size, randI2);
				drawRect(obj1.row, obj1.col, obj1.size, obj1.size, GREEN);
				drawRect(old_obj1.row, old_obj1.col, old_obj1.size, old_obj1.size, BLACK);
				drawRect(bad.row, bad.col, bad.size, bad.size, YELLOW);
				drawRect(old_bad.row, old_bad.col, old_bad.size, old_bad.size, BLACK);
			} else {
				drawRect(obj1.row, obj1.col, obj1.size, obj1.size, GREEN);
				drawRect(bad.row, bad.col, bad.size, bad.size, YELLOW);
			}
			waitForVblank();
			drawRect(old_self.row, old_self.col, old_self.size, old_self.size, BLACK);
			drawRect(self.row, self.col, self.size, self.size, RED);
			i++;
		}
		break;

		
		case WIN:
		drawImage3(0, 0, WIN_WIDTH, WIN_HEIGHT, win);
		while(!KEY_DOWN_NOW(BUTTON_SELECT)) {};
		state = START;
		while(KEY_DOWN_NOW(BUTTON_SELECT)) {};
		break;

		case LOSE:
		drawImage3(0, 0, GAMEOVER_WIDTH, GAMEOVER_HEIGHT, gameover);
		while(!KEY_DOWN_NOW(BUTTON_SELECT)) {};
		state = START;
		while(KEY_DOWN_NOW(BUTTON_SELECT)) {};
		break;
		}
	}
	return 0;
} 

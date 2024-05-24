#define _CRT_SECURE_NO_WARNINGS
#include"game.h"


void InitBoard(char board[ROWS][COLS], int row, int col, char set) {
	int i = 0;
	int j = 0;
	for (i = 0; i < row; i++) {
		for (j = 0; j < col; j++) {
			board[i][j] = set;
		}
	}
}

void DisplayBoard(char board[ROWS][COLS], int row, int col) {
	int i = 0;
	int j = 0;
	printf("-------------扫雷游戏-------------\n");
	for (i = 0; i <= col; i++) {
		printf("%d ", i);
	}
	printf("\n");
	for (i = 1; i <= row; i++) {
		printf("%d ", i);
		for (j = 1; j <= col; j++) {
			printf("%c ", board[i][j]);
		}
		printf("\n");
	}
	printf("---------------------------------\n");

}

void SetMine(char board[ROWS][COLS], int row, int col) {
	int count = EASY_COUNT;
	while (count) {	//count==0为假
		int x = rand() % row + 1;	//+1才是1-9，不加直接模就是0-8
		int y = rand() % col + 1;
		if (board[x][y] != '1') {
			board[x][y] = '1';
			count--;
		}
	}
}

int get_mine_count(char board[ROWS][COLS], int x, int y) {
	return (board[x - 1][y - 1]
		+ board[x - 1][ y]
		+ board[x - 1][y + 1]
		+ board[x][y - 1]
		+ board[x][y + 1]
		+ board[x + 1][y - 1]
		+ board[x + 1][y] 
		+ board[x + 1][y + 1]
		- 8 * '0');
}

void FindMine(char mine[ROWS][COLS], char show[ROWS][COLS], int row, int col) {
	int x = 0;
	int y = 0;
	int win = 0;
	while (win < row * col - EASY_COUNT) {
		printf("请输入要查找的坐标:>");
		scanf("%d %d", &x, &y);
		if (x >= 1 && x <= row && y >= 1 && y <= col) {
			if(show[x][y] != '*') {
				printf("已排查\n");
			}
			else {
				//如果是雷
				if (mine[x][y] == '1') {
					printf("很遗憾，你被炸死了\n");
						DisplayBoard(mine, ROW, COL);
						break;
				}
				//如果不是雷 
				else {
					win++;
					//统计x,y坐标周围的雷数
					int count = get_mine_count(mine, x, y);
					show[x][y] = count + '0';	//数字+'0'转成字符串,数字-'0'转成整形
					DisplayBoard(show, ROW, COL);
				}
			}
			}
			
		else {
			printf("请重新输入\n");
		}
	}
	if (win == row * col - EASY_COUNT) {
		printf("恭喜你，排雷成功\n");
		DisplayBoard(show, ROW, COL);
	}
}

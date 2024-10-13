#pragma warning(disable : 4996) // ���� C4996�� ����
#include <stdio.h> 
#include <conio.h> // �ܼ� ����� �Լ��� ����
#include <Windows.h> // ������ ���� �� ���� �Լ��� ����

#define CIN GetStdHandle(STD_INPUT_HANDLE) // ǥ�� �Է� ����̽�
#define COUT GetStdHandle(STD_OUTPUT_HANDLE) // ǥ�� ��� ����̽�

/* �ܼ� ���� �ڵ� */
#define WHITE 7 
#define RED 4
#define BLUE 1
#define YELLOW 6

const background[13][13] =
{
	{'-','-','-','-','-','-','-','-','-','-','-','-','-',},
	{'|', ' ', ' ', ' ', '|', ' ', ' ', ' ', '|', ' ', ' ', ' ', '|'},
	{'|', ' ', ' ', ' ', '|', ' ', ' ', ' ', '|', ' ', ' ', ' ', '|'},
	{'|', ' ', ' ', ' ', '|', ' ', ' ', ' ', '|', ' ', ' ', ' ', '|'},
	{'-','-','-','-','-','-','-','-','-','-','-','-','-',},
	{'|', ' ', ' ', ' ', '|', ' ', ' ', ' ', '|', ' ', ' ', ' ', '|'},
	{'|', ' ', ' ', ' ', '|', ' ', ' ', ' ', '|', ' ', ' ', ' ', '|'},
	{'|', ' ', ' ', ' ', '|', ' ', ' ', ' ', '|', ' ', ' ', ' ', '|'},
	{'-','-','-','-','-','-','-','-','-','-','-','-','-',},
	{'|', ' ', ' ', ' ', '|', ' ', ' ', ' ', '|', ' ', ' ', ' ', '|'},
	{'|', ' ', ' ', ' ', '|', ' ', ' ', ' ', '|', ' ', ' ', ' ', '|'},
	{'|', ' ', ' ', ' ', '|', ' ', ' ', ' ', '|', ' ', ' ', ' ', '|'},
	{'-','-','-','-','-','-','-','-','-','-','-','-','-',},
};
const O[3][3] =
{
	{' ', '*', ' '},
	{'*', ' ', '*'},
	{' ', '*', ' '},
};
const X[3][3] =
{
	{'*', ' ', '*'},
	{' ', '*', ' '},
	{'*', ' ', '*'},
};

enum { // ���� ����, ���� ���� enum 
	GAME_START = 0,
	GAME_EXIT
};

enum { // ���� �÷��̾� ���� enum
	NONE = 0,
	PALYER_1,
	PALYER_2
};

typedef struct score { // ���� ���ھ� ���� ����ü
	int player1;
	int player2;
} Score;

int OorX[3][3] = { 0, }; // O�� X�� ��ġ�� �����ϴ� ����
int player = 0; // ���� �÷��̾ �����ϴ� ����
int gameFlag = 0; // ���� ���� ���� ���� ����
int gameMenu = 0; // ���õ� �޴� ���� ����
int turnCount = 0; // ���� �� Ƚ�� ����
Score score = { 0, 0 }; // ���� ���ھ� ���� ����

void gameScreen(); // �ش� �Լ��� ���� �޴� ȭ��� ���� �÷��� ȭ���� �����Ͽ� �����ִ� �Լ�

void gameStartScreen(); // ���� �޴� ȭ�� ��°� �޴� ���� �Լ��� ȣ���ϴ� �Լ�
void printGameStartScreen(); // ���� �޴� ȭ�� ����ϴ� �Լ�
void inputGameMenu(); // Ű���� �Է��� ó�� �ϴ� �Լ�
void gotoMouseXY(int x, int y); // ���콺 ������ �̵��� ���ִ� �Լ�
void selectedGameMenu(); // ���õ� �޴� �̺�Ʈ�� ó�� �ϴ� �Լ�

void gamePlayingScreen(); // ���� �÷��̿� ���̴� ���� �ʱ�ȭ�� ���� ��׶��� ��°� ���� ���࿡ ���� �Լ��� ȣ�� �ϴ� �Լ�
void printGameBackground(); // ���� ��׶��带 ����ϴ� �Լ�
void printPlayerTurn(); // ���� �÷��̾� ���ʸ� ����ϴ� �Լ�
void setColor(int color); // �ܼ� ������ �����ϴ� �Լ�
void inputMouseSetting(); // �ܼ� �Է��� ���콺 �Է����� �ٲٴ� �Լ�

void gameEvent(); // ���� ���콺 �Է� �̺�Ʈ ó���� ���� ���� �̺�Ʈ�� ó�� �ϴ� �Լ�

void getBackgroundPosition(int* posX, int* posY); // Ŭ���� ĭ ���� ��� ��ǥ ���� ��� ���� �Լ�
void getOorXarrayPosition(int* posX, int* posY); // ���� ��ǥ ���� OorX �迭�� ��ġ�� ��ȯ�ϴ� �Լ�
int allReadyOorXDraw(int x, int y); // Ŭ���� ��ġ�� O �Ǵ� X�� �׷��� �ִ��� Ȯ���ϴ� �Լ�
void drawOorX(int player, int posX, int posY); // O �Ǵ� X�� �׸��� �Լ�
void setOorXarray(int player, int posX, int posY); // OorX �迭�� �ش� �÷��̾��� ���� �߰��ϰ�, ���� ���� ��Ű�� �Լ�
int checkOorX(); // O, X �Ǵ� ���� Ȯ���Ͽ� ������ ���� ���θ� ��ȯ �ϴ� �Լ�
void winnerLog(int winner); // ���� ���� �α׸� ��� �ϴ� �Լ�

void main() {
	while (1) {
		gameScreen();
	}
}

void gameScreen() {
	if (!gameFlag) {
		gameStartScreen();
	}
	else {
		gamePlayingScreen();
	}
}

void gameStartScreen() {
	printGameStartScreen();

	while (gameFlag != 1) {
		inputGameMenu();
	}
}

void printGameStartScreen() {
	printf("[���� ���ھ�]\n");
	printf("player1 : %d vs player2 : %d\n\n", score.player1, score.player2);

	printf("[���� �޴�]\n");
	printf("�������ϱ�\n");
	printf("����������");
}

void gotoMouseXY(int x, int y) {
	COORD cur;
	cur.X = x;
	cur.Y = y;

	SetConsoleCursorPosition(COUT, cur);
}

void inputGameMenu() {
	char key = getch(); // getch()�� Ű������ �ϳ� Ű�� �Է� ���� �� �ְ� �ϴ� �Լ�

	if (key == 'w' || key == 'W') {
		gotoMouseXY(0, 4);
		printf("��\n\r��");
		gameMenu = GAME_START;
	}
	else if (key == 's' || key == 'S') {
		gotoMouseXY(0, 4);
		printf("��\n\r��");
		gameMenu = GAME_EXIT;
	}
	else if (key == '\r') {
		selectedGameMenu();
	}
}

void selectedGameMenu() {
	switch (gameMenu)
	{
	case GAME_START:
		gameFlag = 1;
		break;
	case GAME_EXIT:
		exit(0); // ���α׷��� ���� �ϴ� �Լ�
		break;
	}
}

void gamePlayingScreen() {
	/* ���� �÷��̿� ���õ� ������ �ʱ�ȭ�� �Ѵ� */
	player = 0;
	turnCount = 0;

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			OorX[i][j] = 0;
		}
	}

	printGameBackground(); // ���� ��׶��带 ����Ѵ�
	inputMouseSetting(); // ���콺�� �ܼ� �Է��� �ٲٱ� ���� �Լ�

	while (gameFlag != 0) {
		gameEvent(); // ���콺 Ŭ�� �̺�Ʈ�� ���� ���࿡ ���� �̺�Ʈ�� ó���Ѵ�
	}
}

void printGameBackground() {
	system("cls"); // �ܼ� ȭ���� �ʱ�ȭ �Ѵ�

	for (int i = 0; i < 13; i++) {
		for (int j = 0; j < 13; j++) {
			putchar(background[i][j]);
		}
		putchar('\n');
	}

	printPlayerTurn(); // ���� �÷��̾� ���ʸ� �����ش�
}

void printPlayerTurn() {
	gotoMouseXY(0, 14);

	if (player) {
		setColor(BLUE);
	}
	else setColor(RED);

	printf("\nplayer%d ���� �Դϴ�.\n", player + 1);
}

void setColor(int color) {
	SetConsoleTextAttribute(COUT, color);
}

void inputMouseSetting() {
	DWORD mode;

	GetConsoleMode(CIN, &mode); // ���� �ܼ� �Է� ��带 �����´�.
	SetConsoleMode(CIN, mode | ENABLE_MOUSE_INPUT); // ���콺 �Է��� ����Ѵ�.
}

void gameEvent() {
	INPUT_RECORD record; // �ܼ� �Է� ������ �Է� �̺�Ʈ ����ü
	DWORD read; // unsigned long ( ������ �⺻ ó�� ������ WORD�� 2�� )
	int posX, posY; // ���콺�� Ŭ���� ��ǥ�� ����
	int winner; // ���� ���º�, �̱� �÷��̾ ����

	ReadConsoleInput(CIN, &record, 1, &read); // �ܼ� �Է� �̺�Ʈ �б�

	if (record.EventType == MOUSE_EVENT) {
		if (record.Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED
			&& !(record.Event.MouseEvent.dwEventFlags & MOUSE_MOVED)
			&& !(record.Event.MouseEvent.dwEventFlags & DOUBLE_CLICK)) {
			int posX = record.Event.MouseEvent.dwMousePosition.X;
			int posY = record.Event.MouseEvent.dwMousePosition.Y;

			if (background[posX][posY] == ' ') { // Ŭ���� ���� �������� Ȯ���Ѵ�.
				getBackgroundPosition(&posX, &posY);
				if (!allReadyOorXDraw(posX, posY)) {
					drawOorX(player + 1, posX, posY);
					setOorXarray(player + 1, posX, posY);

					player = !player; // player�� not ���ؼ� player ��ü�� �Ѵ�.

					printPlayerTurn();
				}

				winner = checkOorX();

				if (winner != -1) {
					winnerLog(winner);
				}
			}
		}
	}
}

void getBackgroundPosition(int* posX, int* posY) {
	while (background[--(*posY)][*posX] != '-');
	(*posY)++;
	while (background[(*posY)][--(*posX)] != '|');
	(*posX)++;
}

void getOorXarrayPosition(int* posX, int* posY) {
	int x = (*posX), y = (*posY);
	x--; y--;

	while (x > 2) {
		x -= 3;
	}
	while (y > 2) {
		y -= 3;
	}

	(*posX) = x; (*posY) = y;
}

int allReadyOorXDraw(int x, int y) {
	getOorXarrayPosition(&x, &y);
	if (OorX[y][x] == 0)
		return 0; // O �Ǵ� X�� ����
	else return 1; // O �Ǵ� X�� ����
}

void drawOorX(int player, int posX, int posY) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			int y = posY + i;
			int x = posX + j;

			gotoMouseXY(x, y);

			if (player == PALYER_1) {
				setColor(RED);
				printf("%c", X[i][j]);
			}
			if (player == PALYER_2) {
				setColor(BLUE);
				printf("%c", O[i][j]);
			}
		}
	}
}

void setOorXarray(int player, int posX, int posY) {
	getOorXarrayPosition(&posX, &posY);
	OorX[posY][posX] = player;
	turnCount++;
}

int checkOorX() {
	int i, j;
	int countA = 0, countB = 0;

	/* �밢�� Ȯ�� */
	for (i = 0; i < 2; i++) {
		if (OorX[i][i] != 0 || OorX[i][2 - i] != 0) {
			if (OorX[i][i] == OorX[i + 1][i + 1])
				countA++;
		}
		if (OorX[i][2 - i] != 0) {
			if (OorX[i][2 - i] == OorX[i + 1][2 - (i + 1)])
				countB++;
		}
	}

	if (countA == 2 || countB == 2) {
		return OorX[1][1];
	}

	/* �� Ȯ�� */
	for (i = 0; i < 3; i++) {
		countA = 0; countB = 0;
		for (j = 0; j < 2; j++) {
			if (OorX[i][j] != 0) {
				if (OorX[i][j] == OorX[i][j + 1]) {
					countA++;
				}
			}
			if (OorX[j][i] != 0) {
				if (OorX[j][i] == OorX[j + 1][i]) {
					countB++;
				}
			}
		}

		if (countA == 2) {
			return OorX[i][j];
		}
		else if (countB == 2) {
			return OorX[j][i];
		}
	}

	/* ���º� Ȯ�� */
	if (turnCount == 9) {
		return 0;
	}

	return -1;
}

void winnerLog(int winner) {
	system("cls");

	if (winner == PALYER_1) {
		setColor(RED);
		printf("player1�� �̰���ϴ� ! !\n\n");
		score.player1++;
	}
	else if (winner == PALYER_2) {
		setColor(BLUE);
		printf("player2�� �̰���ϴ� ! !\n\n");
		score.player2++;
	}
	else if (winner == NONE) {
		setColor(YELLOW);
		printf("���º� �Դϴ� ! !\n\n");
	}

	system("pause"); // �ܼ��� �Ͻ��ߴ� ��Ų��.

	gameFlag = 0;
	system("cls");
	setColor(WHITE);
}
/*
	2024-2 창업프로젝트1
	202311388 김민상
	미니게임 모음집 프로젝트

	(0). UI 등 기타 공통적으로 쓰이는 함수들
	(1). 메인
	(2). 회원가입
	(3). 관리자 창
	(3-1). 회원정보관리
	(3-2). 게임기록관리
	(4). 게임 선택
	(5). 팩맨
	(6). 블랙잭
	(7). 인디언포커
	(8). 가위바위보
	(9). 오목
	(10). 틱택토
	(11). 요트 다이스
	(12). 숫자야구
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <conio.h>
#include <time.h>

enum ColorType {
	BLACK,  	//0
	DARKBLUE,	//1
	DARKGREEN,	//2
	DARKSKYBLUE,//3
	DARKRED,  	//4
	DARKPURPLE,	//5
	DARKYELLOW,	//6
	GRAY,		//7
	DARKGRAY,	//8
	BLUE,		//9
	GREEN,		//10
	SKYBLUE,	//11
	RED,		//12
	PURPLE,		//13
	YELLOW,		//14
	WHITE		//15
} COLOR;										// 0. 색상 열거체
int mouse_x;														// 0. 마우스 커서 x축
int mouse_y;														// 0. 마우스 커서 y축​

char inputID1P[40] = "";											// 2. 1P 입력 ID
char inputPW1P[40] = "";											// 2. 1P 입력 PW
char inputID2P[40] = "";											// 2. 2P 입력 ID
char inputPW2P[40] = "";											// 2. 2P 입력 PW
char access1P[40] = "";												// 2. 로그인된 1P 닉네임
char access2P[40] = "";												// 2. 로그인된 2P 닉네임
typedef struct member
{
	char id[40];
	char password[40];
	char nickname[40];
}MEMBER;								// 2. 계정 구조체 (ID, PW, 닉네임)

void gotoxy(int x, int y);											// 0. 좌표이동
void scolor(unsigned short back, unsigned short text);				// 0. 글씨 색상
void cursor_visible(int num);										// 0. 마우스 커서  (매개변수 1 -> 보임    0 -> 안보임)
void setclear();													// 0. 화면 초기화
int CheckMouse();													// 0. 마우스 확인

void main_UI_1P();													// 1. 메인화면(1P)
void main_UI_2P();													// 1. 메인화면(2P)
int login_1P();														// 1. 메인화면 - 로그인(1P)
int login_2P();														// 1. 메인화면 - 로그인(2P)

int checkDup(const char* id, const char* nickname);					// 2. 회원가입 - 중복체크
int checkStr(char* str);											// 2. 회원가입 - 조건체크(영문자, !)
void addMember();													// 2. 회원가입

void manager();														// 3. 관리자 창

void game_Choice_1P();												// 4. 게임선택(1P)
void game_Choice_2P();												// 4. 게임선택(2P)

// 0. 메인
int main(void)
{
	setclear();
	
	main_UI_1P();
	
	return 0;
}

// 0. 좌표이동
void gotoxy(int x, int y) {
	//x, y 좌표 설정
	COORD pos = { x,y };
	//커서 이동
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
// 0. 글씨 색상
void scolor(unsigned short back, unsigned short text)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (back << 4) + text);
}
// 0. 마우스 커서  (매개변수 1 -> 보임    0 -> 안보임)
void cursor_visible(int num)
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO ConsoleCursor;
	ConsoleCursor.bVisible = num;
	ConsoleCursor.dwSize = 1;
	SetConsoleCursorInfo(consoleHandle, &ConsoleCursor);
}
// 0. 화면 초기화
void setclear()
{
	system("cls");
	system("mode con:cols=150 lines=40");
	scolor(BLACK, WHITE);
	cursor_visible(0);
}
// 0. 마우스 확인
int CheckMouse()
{

	INPUT_RECORD rec;//★ INPUT_RECORD 는 마우스 이벤트 정보들을 가지고있다,

	DWORD dwNOER;//★ 참고로 DWORD는 unsigned long 을 뜻한다 0~4294967295 (0 ~ 2^32-1)

	HANDLE CIN, COUT;
	CIN = GetStdHandle(STD_INPUT_HANDLE);// 핸들 설정
	COUT = GetStdHandle(STD_OUTPUT_HANDLE);// 핸들 설정

	DWORD mode;

	GetConsoleMode(CIN, &mode); // 마우스 재활성화 ?★여기서 DWORD 값을 받는다
	SetConsoleMode(CIN, mode | ENABLE_MOUSE_INPUT); // 마우스 재활성화(만약 system() 함수를 사용할 시 마우스 재활성화를 해주어야 한다.)

	FlushConsoleInputBuffer(CIN);//콘솔 입력 버퍼를 플러시합니다. 현재 입력 버퍼에 있는 모든 입력 레코드는 삭제됩니다.

	ReadConsoleInput(CIN, &rec, 1, &dwNOER); // 콘솔창 입력을 받아들임. 

	FlushConsoleInputBuffer(CIN);

	if (rec.EventType == MOUSE_EVENT) // 마우스 이벤트일 경우
	{
		mouse_x = rec.Event.MouseEvent.dwMousePosition.X; // 마우스의 X값 받아옴 
		mouse_y = rec.Event.MouseEvent.dwMousePosition.Y; // 마우스의 Y값 받아옴 
		if (rec.Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED) { // 좌측 버튼이 클릭되었을 경우
			return 1;
		}
	}
	return 0;//그 외 활동일경우(키보드, 마우스 드래그 등등
}

// 1. 메인화면(1P)
void main_UI_1P()
{
	strcpy(access1P, "");

	setclear();
	gotoxy(38, 7);		printf("___  ___ _____  _   _  _____  _____   ___  ___  ___ _____          _\n");
	gotoxy(38, 8);		printf("|  \\/  ||_   _|| \\ | ||_   _||  __ \\ / _ \\ |  \\/  ||  ___|        (_)\n");
	gotoxy(38, 9);		printf("| .  . |  | |  |  \\| |  | |  | |  \\// /_\\ \\| .  . || |__      ____ _  _ __\n");
	gotoxy(38, 10);		printf("| |\\/| |  | |  | . ` |  | |  | | __ |  _  || |\\/| ||  __|    |_  /| || '_ \\\n");
	gotoxy(38, 11);		printf("| |  | | _| |_ | |\\  | _| |_ | |_\\ \\| | | || |  | || |___  _  / / | || |_) |\n");
	gotoxy(38, 12);		printf("\\_|  |_/ \\___/ \\_| \\_/ \\___/  \\____/\\_| |_/\\_|  |_/\\____/ (_)/___||_|| .__/\n");
	gotoxy(38, 13);		printf("                                                                     | |\n");
	gotoxy(38, 14);		printf("                                                                     |_|\n");
	
	scolor(BLACK, SKYBLUE);
	gotoxy(57, 16); printf("┌─────┐ ");
	gotoxy(57, 17); printf("│  1P │ ");
	gotoxy(57, 18); printf("└─────┘ ");
	scolor(BLACK, WHITE);

	gotoxy(80, 16); printf("┌─────┐ ");
	gotoxy(80, 17); printf("│  2P │ ");
	gotoxy(80, 18); printf("└─────┘ ");
	
	gotoxy(52, 21); printf("┌──────┬──────────────────────────────┐ ");
	gotoxy(52, 22); printf("│  ID  │          %-20s│ ", " ");
	gotoxy(52, 23); printf("└──────┴──────────────────────────────┘ ");

	gotoxy(52, 25); printf("┌──────┬──────────────────────────────┐ ");
	gotoxy(52, 26); printf("│  PW  │          %-20s│ ", " ");
	gotoxy(52, 27); printf("└──────┴──────────────────────────────┘ ");

	gotoxy(52, 30); printf("┌───────┐ ");
	gotoxy(52, 31); printf("│ 로그인│ ");
	gotoxy(52, 32); printf("└───────┘ ");

	gotoxy(67, 30); printf("┌─────────┐ ");
	gotoxy(67, 31); printf("│ 회원가입│ ");
	gotoxy(67, 32); printf("└─────────┘ ");

	gotoxy(84, 30); printf("┌─────┐ ");
	gotoxy(84, 31); printf("│ 종료│ ");
	gotoxy(84, 32); printf("└─────┘ ");

	while (1)
	{
		int temp = CheckMouse();
		if (temp == 1)
		{
			// 2P
			if (mouse_x >= 80 && mouse_x <= 87 && mouse_y >= 16 && mouse_y <= 18)
			{
				setclear();
				main_UI_2P();
			}
			// ID
			if (mouse_x >= 60 && mouse_x <= 91 && mouse_y >= 21 && mouse_y <= 23)
			{
				strcpy(inputID1P, "");
				cursor_visible(1);
				gotoxy(52, 22); printf("│  ID  │          %-20s│ ", " ");
				gotoxy(61, 22); scanf("%s", inputID1P); getchar();
				cursor_visible(0);
			}
			// PW
			if (mouse_x >= 60 && mouse_x <= 91 && mouse_y >= 25 && mouse_y <= 27)
			{
				strcpy(inputPW1P, "");
				cursor_visible(1);
				gotoxy(52, 26); printf("│  PW  │          %-20s│ ", " ");
				gotoxy(61, 26); scanf("%s", inputPW1P); getchar();
				cursor_visible(0);
			}
			// 로그인
			if (mouse_x >= 52 && mouse_x <= 61 && mouse_y >= 30 && mouse_y <= 32)
			{
				switch (login_1P())
				{
				case 1 : // 사용자 로그인 성공
					// 게임 선택
					game_Choice_1P();
					break;
				case 2 : // 관리자 로그인 성공
					manager();
					break;
				default :
					break;
				}
			}
			// 회원가입
			if (mouse_x >= 67 && mouse_x <= 78 && mouse_y >= 30 && mouse_y <= 32)
			{
				addMember();
				main_UI_1P();
			}
			// 종료
			if (mouse_x >= 84 && mouse_x <= 90 && mouse_y >= 30 && mouse_y <= 32)
				break;
		}
	}
}
// 1. 메인화면(2P) 미완 
void main_UI_2P()
{
	strcpy(access1P, "");
	strcpy(access2P, "");

	setclear();
	gotoxy(38, 7);		printf("___  ___ _____  _   _  _____  _____   ___  ___  ___ _____          _\n");
	gotoxy(38, 8);		printf("|  \\/  ||_   _|| \\ | ||_   _||  __ \\ / _ \\ |  \\/  ||  ___|        (_)\n");
	gotoxy(38, 9);		printf("| .  . |  | |  |  \\| |  | |  | |  \\// /_\\ \\| .  . || |__      ____ _  _ __\n");
	gotoxy(38, 10);		printf("| |\\/| |  | |  | . ` |  | |  | | __ |  _  || |\\/| ||  __|    |_  /| || '_ \\\n");
	gotoxy(38, 11);		printf("| |  | | _| |_ | |\\  | _| |_ | |_\\ \\| | | || |  | || |___  _  / / | || |_) |\n");
	gotoxy(38, 12);		printf("\\_|  |_/ \\___/ \\_| \\_/ \\___/  \\____/\\_| |_/\\_|  |_/\\____/ (_)/___||_|| .__/\n");
	gotoxy(38, 13);		printf("                                                                     | |\n");
	gotoxy(38, 14);		printf("                                                                     |_|\n");

	
	gotoxy(57, 16); printf("┌─────┐ ");
	gotoxy(57, 17); printf("│  1P │ ");
	gotoxy(57, 18); printf("└─────┘ ");
	
	scolor(BLACK, SKYBLUE);
	gotoxy(80, 16); printf("┌─────┐ ");
	gotoxy(80, 17); printf("│  2P │ ");
	gotoxy(80, 18); printf("└─────┘ ");
	scolor(BLACK, WHITE);

	gotoxy(25, 21); printf("[ 1P ] ");

	gotoxy(120, 21); printf("[ 2P ] ");

	gotoxy(32, 21); printf("┌──────┬──────────────────────────────┐ ");
	gotoxy(32, 22); printf("│  ID  │          %-20s│ ", " ");
	gotoxy(32, 23); printf("└──────┴──────────────────────────────┘ ");

	gotoxy(32, 25); printf("┌──────┬──────────────────────────────┐ ");
	gotoxy(32, 26); printf("│  PW  │          %-20s│ ", " ");
	gotoxy(32, 27); printf("└──────┴──────────────────────────────┘ ");

	gotoxy(78, 21); printf("┌──────┬──────────────────────────────┐ ");
	gotoxy(78, 22); printf("│  ID  │          %-20s│ ", " ");
	gotoxy(78, 23); printf("└──────┴──────────────────────────────┘ ");

	gotoxy(78, 25); printf("┌──────┬──────────────────────────────┐ ");
	gotoxy(78, 26); printf("│  PW  │          %-20s│ ", " ");
	gotoxy(78, 27); printf("└──────┴──────────────────────────────┘ ");

	gotoxy(52, 30); printf("┌───────┐ ");
	gotoxy(52, 31); printf("│ 로그인│ ");
	gotoxy(52, 32); printf("└───────┘ ");

	gotoxy(67, 30); printf("┌─────────┐ ");
	gotoxy(67, 31); printf("│ 회원가입│ ");
	gotoxy(67, 32); printf("└─────────┘ ");

	gotoxy(84, 30); printf("┌─────┐ ");
	gotoxy(84, 31); printf("│ 종료│ ");
	gotoxy(84, 32); printf("└─────┘ ");

	while (1)
	{
		int temp = CheckMouse();
		if (temp == 1)
		{
			// 1P
			if (mouse_x >= 57 && mouse_x <= 64 && mouse_y >= 16 && mouse_y <= 18)
			{
				setclear();
				main_UI_1P();
			}
			// 1P_ID
			if (mouse_x >= 40 && mouse_x <= 71 && mouse_y >= 21 && mouse_y <= 23)
			{
				strcpy(inputID1P, "");
				cursor_visible(1);
				gotoxy(32, 22); printf("│  ID  │          %-20s│ ", " ");
				gotoxy(41, 22); scanf("%s", inputID1P); getchar();
				cursor_visible(0);
			}
			// 1P_PW
			if (mouse_x >= 40 && mouse_x <= 71 && mouse_y >= 25 && mouse_y <= 27)
			{
				strcpy(inputPW1P, "");
				cursor_visible(1);
				gotoxy(32, 26); printf("│  PW  │          %-20s│ ", " ");
				gotoxy(41, 26); scanf("%s", inputPW1P); getchar();
				cursor_visible(0);
			}
			// 2P_ID
			if (mouse_x >= 86 && mouse_x <= 117 && mouse_y >= 21 && mouse_y <= 23)
			{
				strcpy(inputID2P, "");
				cursor_visible(1);
				gotoxy(78, 22); printf("│  ID  │          %-20s│ ", " ");
				gotoxy(87, 22); scanf("%s", inputID2P); getchar();
				cursor_visible(0);
			}
			// 2P_PW
			if (mouse_x >= 86 && mouse_x <= 117 && mouse_y >= 25 && mouse_y <= 27)
			{
				strcpy(inputPW2P, "");
				cursor_visible(1);
				gotoxy(78, 26); printf("│  PW  │          %-20s│ ", " ");
				gotoxy(87, 26); scanf("%s", inputPW2P); getchar();
				cursor_visible(0);
			}
			// 로그인
			if (mouse_x >= 52 && mouse_x <= 61 && mouse_y >= 30 && mouse_y <= 32)
			{
				if (login_2P())
				{
					// 게임 선택화면
					game_Choice_2P();
				}
			}
			// 회원가입
			if (mouse_x >= 67 && mouse_x <= 78 && mouse_y >= 30 && mouse_y <= 32)
			{
				addMember();
				main_UI_2P();
			}
			// 종료
			if (mouse_x >= 84 && mouse_x <= 90 && mouse_y >= 30 && mouse_y <= 32)
				break;
		}
	}
}

// 1. 메인화면 - 로그인(1P)
int login_1P()
{
	strcpy(access1P, "");

	FILE* file = fopen("member.txt", "r");

	gotoxy(55, 29); printf("%60s", " ");

	if (file == NULL)
	{
		gotoxy(60, 29); scolor(BLACK, RED); perror("파일 열기 실패"); scolor(BLACK, WHITE);
		gotoxy(52, 31); printf("│ 로그인│ ");
		return 0;
	}

	if (inputID1P[0] == '\0' || inputPW1P[0] == '\0')
	{
		gotoxy(57, 29); scolor(BLACK, RED); printf("입력하지 않은 칸이 존재합니다."); scolor(BLACK, WHITE);
		gotoxy(52, 31); printf("│ 로그인│ ");
		return 0;
	}

	MEMBER currentMember;

	while (fscanf(file, "%s %s %s", currentMember.id, currentMember.password, currentMember.nickname) == 3)
	{
		if (strcmp(inputID1P, "manager") == 0 && strcmp(inputPW1P, "qwer") == 0)
		{
			fclose(file);
			gotoxy(67, 29);	scolor(BLACK, PURPLE);  printf("관리자 로그인"); scolor(BLACK, WHITE);
			Sleep(1000);
			return 2; // 관리자 로그인
		}
		if (strcmp(inputID1P, currentMember.id) == 0 && strcmp(inputPW1P, currentMember.password) == 0)
		{
			fclose(file);
			gotoxy(67, 29);	scolor(BLACK, SKYBLUE);  printf("로그인 성공!"); scolor(BLACK, WHITE);
			strcpy(access1P, currentMember.nickname);
			Sleep(1000);
			return 1; // 로그인 성공
		}
	}

	fclose(file);
	gotoxy(57, 29); scolor(BLACK, RED); printf("ID / PW를 다시 확인해주세요."); scolor(BLACK, WHITE);
	Sleep(1000);
	return 0; // 로그인 실패
}
// 1. 메인화면 - 로그인(2P)
int login_2P()
{
	int success_1p = 0;
	int success_2p = 0;
	strcpy(access1P, "");
	strcpy(access2P, "");

	FILE* file = fopen("member.txt", "r");

	gotoxy(55, 29); printf("%60s", " ");

	if (file == NULL)
	{
		gotoxy(65, 29); scolor(BLACK, RED); perror("파일 열기 실패"); scolor(BLACK, WHITE);
		gotoxy(52, 31); printf("│ 로그인│ ");
		return 0;
	}

	if (inputID1P[0] == '\0' || inputPW1P[0] == '\0' || inputID2P == '\0' || inputPW2P == '\0')
	{
		gotoxy(55, 29); scolor(BLACK, RED); printf("입력하지 않은 칸이 존재합니다."); scolor(BLACK, WHITE);
		gotoxy(52, 31); printf("│ 로그인│ ");
		return 0;
	}

	MEMBER currentMember = { "", "", "" };
	MEMBER currentMember1p = { "", "", "" };
	MEMBER currentMember2p = { "", "", "" };

	while (fscanf(file, "%s %s %s", currentMember.id, currentMember.password, currentMember.nickname) == 3)
	{
		if (strcmp(inputID1P, currentMember.id) == 0 && strcmp(inputPW1P, currentMember.password) == 0)
		{
			success_1p = 1;
			strcpy(currentMember1p.nickname, currentMember.nickname);
		}
		if (strcmp(inputID2P, currentMember.id) == 0 && strcmp(inputPW2P, currentMember.password) == 0)
		{
			success_2p = 1;
			strcpy(currentMember2p.nickname, currentMember.nickname);
		}
	}

	if (success_1p == 1 && success_2p == 1)
	{
		fclose(file);
		gotoxy(67, 29);	scolor(BLACK, SKYBLUE);  printf("로그인 성공!"); scolor(BLACK, WHITE);
		strcpy(access1P, currentMember1p.nickname);
		strcpy(access2P, currentMember2p.nickname);
		Sleep(1000);
		return 1; // 로그인 성공
	}

	fclose(file);
	gotoxy(58, 29); scolor(BLACK, RED); printf("ID / PW를 다시 확인해주세요."); scolor(BLACK, WHITE);
	Sleep(1000);
	return 0; // 로그인 실패
}

// 2. 회원가입 - 중복체크 (1 중복)
int checkDup(const char* id, const char* nickname)
{
	FILE* file = fopen("member.txt", "r");

	if (file == NULL) 
	{
		gotoxy(52, 33);
		perror("파일 열기 실패\n");
		Sleep(1000);
		return 0;
	}

	MEMBER currentMember;

	while (fscanf(file, "%s %s %s", currentMember.id, currentMember.password, currentMember.nickname) == 3) 
	{
		if (strcmp(id, currentMember.id) == 0) 
		{
			fclose(file);
			return 1; // 중복됨
		}
		if (strcmp(nickname, currentMember.nickname) == 0)
		{
			fclose(file);
			return 1;
		}
	}

	fclose(file);
	return 0; // 중복 없음
}
// 2. 회원가입 - 조건체크(영문자, !) (1 오류)
int checkStr(char* str) {
	while (*str) {
		if (!isalpha(*str) && !isdigit(*str) && *str != '!') {
			return 1;
		}
		str++;
	}
	return 0;
}
// 2. 회원가입
void addMember()
{
	FILE* file = fopen("member.txt", "a");

	if (file == NULL) {
		gotoxy(44, 20);
		perror("파일 열기 실패\n");
		Sleep(1000);
		return;
	}

	MEMBER newMember = {"", "", ""};

	gotoxy(50, 5);	printf("┌──────────────────-────────-──────────────┐");
	for (int i = 6; i < 31; i++)
	{
		gotoxy(50, i);	printf("│%42s│", " ");
	}
	gotoxy(50, 31);	printf("└──────────────────-────────-──────────────┘");

	gotoxy(66, 8);	printf("[ 회원가입 ]");
	gotoxy(56, 9); printf("ID, PW, 닉네임 모두 15글자 제한");
	gotoxy(57, 10); printf("영어 대소문자 및 ! 만 사용가능");

	gotoxy(52, 13); printf("┌──────┬──────────────────────────────┐ ");
	gotoxy(52, 14); printf("│  ID  │          %-20s│ ", " ");
	gotoxy(52, 15); printf("└──────┴──────────────────────────────┘ ");

	gotoxy(52, 18); printf("┌──────┬──────────────────────────────┐ ");
	gotoxy(52, 19); printf("│  PW  │          %-20s│ ", " ");
	gotoxy(52, 20); printf("└──────┴──────────────────────────────┘ ");

	gotoxy(52, 23); printf("┌──────┬──────────────────────────────┐ ");
	gotoxy(52, 24); printf("│닉네임│          %-20s│ ", " ");
	gotoxy(52, 25); printf("└──────┴──────────────────────────────┘ ");
	
	gotoxy(58, 27); printf("┌─────┐ ");
	gotoxy(58, 28); printf("│ 가입│ ");
	gotoxy(58, 29); printf("└─────┘ ");

	gotoxy(77, 27); printf("┌─────────┐ ");
	gotoxy(77, 28); printf("│ 돌아가기│ ");
	gotoxy(77, 29); printf("└─────────┘ ");


	while (1)
	{
		int temp = CheckMouse();
		if (temp == 1)
		{
			// 2P
			if (mouse_x >= 60 && mouse_x <= 91 && mouse_y >= 13 && mouse_y <= 15)
			{
				strcpy(newMember.id, "");
				cursor_visible(1);
				gotoxy(52, 14); printf("│  ID  │          %-20s│ ", " ");
				gotoxy(58, 28); printf("│ 가입│ ");
				gotoxy(52, 24); printf("│닉네임│");
				gotoxy(61, 14); scanf("%s", newMember.id); getchar();
				cursor_visible(0);
			}
			if (mouse_x >= 60 && mouse_x <= 91 && mouse_y >= 18 && mouse_y <= 20)
			{
				strcpy(newMember.password, "");
				cursor_visible(1);
				gotoxy(52, 19); printf("│  PW  │          %-20s│ ", " ");
				gotoxy(58, 28); printf("│ 가입│ ");
				gotoxy(52, 24); printf("│닉네임│");
				gotoxy(61, 19); scanf("%s", newMember.password); getchar();
				cursor_visible(0);
			}
			if (mouse_x >= 60 && mouse_x <= 91 && mouse_y >= 23 && mouse_y <= 25)
			{
				strcpy(newMember.nickname, "");
				cursor_visible(1);
				gotoxy(58, 28); printf("│ 가입│ ");
				gotoxy(52, 24); printf("│닉네임│          %-20s│ ", " ");
				gotoxy(61, 24); scanf("%s", newMember.nickname); getchar();
				cursor_visible(0);
			}
			if (mouse_x >= 58 && mouse_x <= 65 && mouse_y >= 27 && mouse_y <= 29)
			{
				if ((newMember.id[0] == '\0') || (newMember.password[0] == '\0') || (newMember.nickname[0] == '\0'))
				{
					gotoxy(50, 11);	printf("│%42s│", " ");
					scolor(BLACK, RED);
					gotoxy(57, 11); printf("입력하지 않은 칸이 존재합니다.");
					scolor(BLACK, WHITE);
				}
				else if (checkDup(newMember.id, newMember.nickname))
				{
					gotoxy(50, 11);	printf("│%42s│", " ");
					scolor(BLACK, RED);
					gotoxy(54, 11); printf("이미 존재하는 아이디 혹은 닉네임입니다.");
					scolor(BLACK, WHITE);
				}
				else if (strlen(newMember.id) > 15 || strlen(newMember.password) > 15 || strlen(newMember.nickname) > 15)
				{
					gotoxy(50, 11);	printf("│%42s│", " ");
					scolor(BLACK, RED);
					gotoxy(56, 11); printf("15글자를 넘는 항목이 존재합니다.");
					scolor(BLACK, WHITE);
				}
				else if (checkStr(newMember.id) || checkStr(newMember.password) || checkStr(newMember.nickname))
				{
					gotoxy(50, 11);	printf("│%42s│", " ");
					scolor(BLACK, RED);
					gotoxy(53, 11); printf("입력 조건에 어긋나는 항목이 존재합니다.");
					scolor(BLACK, WHITE);
				}
				else
				{
					fprintf(file, "%s %s %s\n", newMember.id, newMember.password, newMember.nickname);
					fclose(file);
					gotoxy(50, 11);	printf("│%42s│", " ");
					scolor(BLACK, SKYBLUE);
					gotoxy(66, 11); printf("가입 성공!");
					scolor(BLACK, WHITE);
					Sleep(1000);
					break;
				}
			}
			if (mouse_x >= 77 && mouse_x <= 88 && mouse_y >= 27 && mouse_y <= 29)
			{
				fclose(file);
				break;
			}
		}
	}
}

// 3. 관리자 창 미완
void manager()
{
	setclear();
	gotoxy(55, 20); printf("관리자 창");
	Sleep(3000);
	main_UI_1P();
}

// 4. 게임선택창 (1P) 미완
void game_Choice_1P()
{
	setclear();
	gotoxy(55, 20);  printf("%s", access1P);
	Sleep(5000);
	main_UI_1P();
}
// 4. 게임선택창 (2P) 미완
void game_Choice_2P()
{
	setclear();
	gotoxy(55, 20);  printf("%s", access1P);
	gotoxy(55, 21);  printf("%s", access2P);
	Sleep(5000);
	main_UI_2P();
}

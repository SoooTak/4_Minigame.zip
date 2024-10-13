#include <windows.h>
#include <stdio.h>

void gotoxy(int x, int y) {
    COORD pos = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void scolor(unsigned short back, unsigned short text)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (back << 4) + text);
}

int main() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwNOER;
    INPUT_RECORD rec;
    BOOL isButtonPressed = FALSE; // 버튼이 눌렸는지 여부

    SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), ENABLE_MOUSE_INPUT);
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO ConsoleCursor;
    ConsoleCursor.bVisible = 0;
    ConsoleCursor.dwSize = 1;
    SetConsoleCursorInfo(consoleHandle, &ConsoleCursor);

    while (1) {
        gotoxy(33, 10); printf("┌────────────────────────────┐ ");
        gotoxy(33, 11); printf("│%-28s│ ", " ");
        gotoxy(33, 12); printf("└────────────────────────────┘ ");
        ReadConsoleInput(GetStdHandle(STD_INPUT_HANDLE), &rec, 1, &dwNOER);
        if (rec.EventType == MOUSE_EVENT) {
            if (rec.Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED) {
                if (!isButtonPressed) {
                    if (rec.Event.MouseEvent.dwMousePosition.X >= 33 && rec.Event.MouseEvent.dwMousePosition.X <= 62 &&
                        rec.Event.MouseEvent.dwMousePosition.Y >= 10 && rec.Event.MouseEvent.dwMousePosition.Y <= 12) {
                        // 버튼 좌표 안에서 클릭했을 때
                        gotoxy(0, 0);
                        printf("버튼이 클릭되었습니다!            \n");
                        scolor(15, 0);
                        gotoxy(33, 10); printf("┌────────────────────────────┐ ");
                        gotoxy(33, 11); printf("│%-28s│ ", " ");
                        gotoxy(33, 12); printf("└────────────────────────────┘ ");

                    }
                    else {
                        // 다른 영역에서 클릭했을 때
                        gotoxy(0, 0);
                        scolor(0, 15); printf("Mouse clicked at (%d, %d)            \n", rec.Event.MouseEvent.dwMousePosition.X, rec.Event.MouseEvent.dwMousePosition.Y);
                    }
                    isButtonPressed = TRUE;
                }
            }
            else {
                if (isButtonPressed) {
                    // 버튼이 떼어졌을 때
                    gotoxy(0, 0);
                    scolor(0, 15); printf("Mouse held at (%d, %d)               \n", rec.Event.MouseEvent.dwMousePosition.X, rec.Event.MouseEvent.dwMousePosition.Y);
                    isButtonPressed = FALSE;
                }
            }
        }
    }

    return 0;
}

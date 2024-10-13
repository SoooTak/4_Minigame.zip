#include <stdio.h>
#include <Windows.h>

int mouse_x;//마우스 커서 x축
int mouse_y;//마우스 커서 y축​

INPUT_RECORD rec;//★ INPUT_RECORD 는 마우스 이벤트 정보들을 가지고있다,

unsigned long dwNOER;//★ 참고로 DWORD는 unsigned long 을 뜻한다 0~4294967295 (0 ~ 2^32-1)

//스크롤바 삭제하는 방법

void remove_scrollbar()
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);//핸들 설정

    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(handle, &info);//콘솔 스크린 버퍼값 가져오기

    COORD new_size =
    {

        //콘솔의 cols, lines 크기보다 스크린버퍼의 크기를 1 줄여주면 스크롤 바가 사라진다.

        info.srWindow.Right - info.srWindow.Left + 1,//콘솔창 사이즈 가로()

        info.srWindow.Bottom - info.srWindow.Top + 1 //콘솔창 사이즈 세로

    };
    SetConsoleScreenBufferSize(handle, new_size);// 적용

}

int CheckMouse()
{
    int mouse_x;//마우스 커서 x축
    int mouse_y;//마우스 커서 y축​

    INPUT_RECORD rec;//★ INPUT_RECORD 는 마우스 이벤트 정보들을 가지고있다,

    unsigned long dwNOER;//★ 참고로 DWORD는 unsigned long 을 뜻한다 0~4294967295 (0 ~ 2^32-1)

    HANDLE CIN, COUT;
    CIN = GetStdHandle(STD_INPUT_HANDLE);// 핸들 설정
    COUT = GetStdHandle(STD_OUTPUT_HANDLE);// 핸들 설정

    unsigned long mode;

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

void BasicSetting() {

    HANDLE CIN, COUT;

    CIN = GetStdHandle(STD_INPUT_HANDLE);

    COUT = GetStdHandle(STD_OUTPUT_HANDLE);

 
    remove_scrollbar(); //스크롤바 삭제

    //SetWindowLong(GetConsoleWindow(), GWL_STYLE, WS_CAPTION); //창스타일변경

    system("mode con cols=120 lines=31");

        //입력 커서 숨기
    CONSOLE_CURSOR_INFO curInfo = { 1 };

    //curInfo.dwSize = 1; //커서 굵기 (1 ~ 100)

    //curInfo.bVisible = FALSE; //커서 Visible TRUE(보임) FALSE(숨김)-기본

    SetConsoleCursorInfo(COUT, &curInfo);

        //마우스 편집 막
    unsigned long prevMode;

    GetConsoleMode(CIN, &prevMode);

    SetConsoleMode(CIN, prevMode & ~ENABLE_QUICK_EDIT_MODE);

    SetConsoleMode(COUT, ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT);// ?★ 마우스 입력모드로 변경

}

void map() {

    printf("┌──────────────────────────────────────────────────────────┐");//0

    printf("│                                                                                                                    │");

    printf("│                                                                                                                    │");

    printf("│                                                                                                                    │");

    printf("│                                                                                                                    │");

    printf("│                                                                                                                    │");//5

    printf("│                                                                                                                    │");

    printf("│                                                                                                                    │");

    printf("│                                                                                                                    │");

    printf("│                                                    스트리머 RPG                                                    │");

    printf("│                                                                                                                    │");//10

    printf("│                                                                                                                    │");

    printf("│                                                                                                                    │");

    printf("│                                                                                                                    │");

    printf("│                                                                                                                    │");

    printf("│                                                                                                                    │");//15

    printf("│                                                     Game Start                                                     │");//55, 16

    printf("│                                                                                                                    │");

    printf("│                                                       Option                                                       │");//57, 18

    printf("│                                                                                                                    │");

    printf("│                                                        Exit                                                        │");//58, 20

    printf("│                                                                                                                    │");

    printf("│                                                                                                                    │");

    printf("│                                                                                                                    │");

    printf("│                                                                                                                    │");

    printf("│                                                                                                                    │");//25

    printf("│                                                                                                                    │");

    printf("│                                                                                                                    │");

    printf("│   e 나 마우스를 누르면 선택 가능                                                                                   │");

    printf("└──────────────────────────────────────────────────────────┘");

}​;

void gotoxy(int x, int y)
{

    COORD Pos;//좌표 저장용 변수

 
    Pos.X = x;

    Pos.Y = y;

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);//해당 위치로 좌표 옮기기

}

void main()

{

    int select = 0;

    BasicSetting();//초기 세팅

    map();

    while (1) {

        int m = CheckMouse();

        if (m == 1) {

            gotoxy(0, 0);

            map();//다시 화면 그려주기

            if (mouse_x >= 55 && mouse_x <= 65 && mouse_y == 16) {

                gotoxy(0, 31);

                printf("Game Start 를 눌렀습니다!                  ");

            }

            else {

                gotoxy(0, 31);

                printf("다른걸 눌렀습니다!                         ");

            }

        }

    }

}
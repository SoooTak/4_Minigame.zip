#include <stdio.h>
#include <stdlib.h>
#define width 100
#define height 100

unsigned char h[54];
unsigned char R[width][height], G[width][height], B[width][height];

int main(int argc, char* argv[]) {
	int i, j;
	FILE* in = fopen("image.bmp", "rb");
	FILE* out = fopen("trans.bmp", "wb");
	// *in은 image.bmp를 가리키는 주기억 장치 내 포인터, FILE 변수이다.
	// rb는 read binary, wb는 write binary의 준말이다.

	if (in == NULL) {	// "=" 만약 image가 없다면 
		printf("파일이 없습니다.");
		return 0;
	}

	for (i = 0; i < 54; i++)	h[i] = getc(in);
	// h[i]가 in의 처음부터 54번째까지의 원소를 포함하도록 
	for (i = 0; i < width; i++)
		for (j = 0; j < height; j++) { // window에서 BGR 순으로 저장 
			B[i][j] = getc(in);
			G[i][j] = getc(in);
			R[i][j] = getc(in);
		}
	for (i = 0; i < width; i++)
		for (j = 0; j < height; j++) {
			if (B[i][j] == 0 && G[i][j] == 0 && R[i][j] == 0) { // 픽셀이 검정이면
				B[i][j] = 255;
				G[i][j] = 255;
				R[i][j] = 255;
			}
			else {
				B[i][j] = 0;
				G[i][j] = 0;
				R[i][j] = 0;
			}
		}

	for (i = 0; i < 54; i++)	    fputc(h[i], out);
	for (i = 0; i < width; i++)
		for (j = 0; j < height; j++) {
			fputc(B[i][j], out);
			fputc(G[i][j], out);
			fputc(R[i][j], out);
			// 처리된 것들을 모두 보조디스크 내 trans 파일에 입력 			
		}
	fclose(in);
	fclose(out);
	return 0;
}
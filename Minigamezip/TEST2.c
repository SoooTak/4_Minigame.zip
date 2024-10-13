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
	// *in�� image.bmp�� ����Ű�� �ֱ�� ��ġ �� ������, FILE �����̴�.
	// rb�� read binary, wb�� write binary�� �ظ��̴�.

	if (in == NULL) {	// "=" ���� image�� ���ٸ� 
		printf("������ �����ϴ�.");
		return 0;
	}

	for (i = 0; i < 54; i++)	h[i] = getc(in);
	// h[i]�� in�� ó������ 54��°������ ���Ҹ� �����ϵ��� 
	for (i = 0; i < width; i++)
		for (j = 0; j < height; j++) { // window���� BGR ������ ���� 
			B[i][j] = getc(in);
			G[i][j] = getc(in);
			R[i][j] = getc(in);
		}
	for (i = 0; i < width; i++)
		for (j = 0; j < height; j++) {
			if (B[i][j] == 0 && G[i][j] == 0 && R[i][j] == 0) { // �ȼ��� �����̸�
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
			// ó���� �͵��� ��� ������ũ �� trans ���Ͽ� �Է� 			
		}
	fclose(in);
	fclose(out);
	return 0;
}
#include <windows.h>

int r, r2;
int main (){
	HDC desk = GetDC(0);
	int y = GetSystemMetrics(0);
	int x = GetSystemMetrics(0);
	int Y = GetSystemMetrics(1);
	int X = GetSystemMetrics(0);
	HDC hdc = GetDC(0);
		desk = GetDC(0);
		r=1;
		r2=20;
		while (1){
			if (r < r2){
			PatBlt(desk, 0, 0, y, x, PATINVERT); //Beep(rand() % 1000,250);
			PatBlt(desk, 0, 0, Y, X, PATINVERT); //Beep(rand() % 1000,200);
			r++;
			}
			else{
				PatBlt(desk, 0, 0, y, X, PATINVERT);
				BitBlt(hdc, rand() % 10 - 20, rand() % 10 , y,  x, hdc, 0, 0, SRCCOPY);
				BitBlt(hdc, rand() % 10, rand() % 10 - 20, Y,  x, hdc, 0, 0, SRCCOPY);
				PatBlt(desk, 0, 0, y, X, PATINVERT);
				BitBlt(hdc, rand() % 10 - 20, rand() % 10 - 20, Y,  x, hdc, 0, 0, SRCCOPY);
				BitBlt(hdc, rand() % 10, rand() % 10, Y,  x, hdc, 0, 0, SRCCOPY);
			}
		}
}

/*
void bit(int r){
	HDC hdc = GetDC(0);
	int y = GetSystemMetrics(0);
	int x = GetSystemMetrics(0);
	int Y = GetSystemMetrics(1);
	int X = GetSystemMetrics(0);
	r = r+1;
	r2=1;
	for (r2=1; r2 < r; r2++);
	BitBlt(hdc, rand() % 10, rand() % 10 - 20, y,  x, hdc, 0, 0, SRCCOPY);
	BitBlt(hdc, rand() % 10 - 20, rand() % 20, Y,  x, hdc, 0, 0, SRCCOPY);
	BitBlt(hdc, rand() % 10 - 20, rand() % 20 , y,  x, hdc, 0, 0, SRCCOPY);
	BitBlt(hdc, rand() % 10, rand() % 20 - 10, Y,  x, hdc, 0, 0, SRCCOPY);
	}
*/
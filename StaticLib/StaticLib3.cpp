#include <math.h>
/*
функция отражает по горизонтали и вертикали.
data- матрица с пикселями
c- количество файлов
my- ширина
mx3- высота
Nemx- разница между mx и mx3
DIR- команда(V или H)
*/
void flip(unsigned char ***data, int c, int my, int mx3, int Nemx, char DIR)
{
	const char H = 'H';
	const char V = 'V';
	int mx = mx3 - Nemx;//чтобы в конце были нули, при вертикальном отражении
	if (DIR == V) {
		for (int i = 0; i < my / 2; i++) {
			for (int j = 0; j < mx3; j++) {
				int tmp = data[c][i][j];
				data[c][i][j] = data[c][my - 1 - i][j];
				data[c][my - 1 - i][j] = tmp;
			}
		}
	}
	else if (DIR == H) {
		for (int i = 0; i < my; i++) {
			for (int j = 0; j < mx / 2; j++) {
				int tmp = data[c][i][j];
				data[c][i][j] = data[c][i][mx - 1 - j];
				data[c][i][mx - 1 - j] = tmp;
			}
		}
		for (int i = 0; i < my; i++) {
			for (int j = 0; j < Nemx; j++) {//в конце дописываем нули
				data[c][i][mx + j - 1] = 0;
			}
		}
	}
}

/*
функция увеличивает или уменьшает яркость пикселей до +-255.
data- матрица с пикселями
c- количество файлов
my- ширина
mx3- высота
arg- команда(от -8 до 8)
*/

void bright(unsigned char ***data, int c, int my, int mx3, int arg)
{
	if (arg > 0) {
		arg = abs(arg);
		for (int i = 0; i < my; i++) {
			for (int j = 0; j < mx3; j++) {
				int tmp = data[c][i][j];
				tmp = tmp << arg;

				if (tmp > 255) {
					tmp = 255;
				}

				data[c][i][j] = tmp;
			}
		}
	}

	if (arg < 0) {
		arg = abs(arg);
		for (int i = 0; i < my; i++) {
			for (int j = 0; j < mx3; j++) {
				int tmp = data[c][i][j];
				tmp = tmp >> arg;

				if (tmp < 0) {
					tmp = 0;
				}

				data[c][i][j] = tmp;
			}
		}
	}
}
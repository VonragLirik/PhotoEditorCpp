#include <math.h>
/*
������� �������� �� ����������� � ���������.
data- ������� � ���������
c- ���������� ������
my- ������
mx3- ������
Nemx- ������� ����� mx � mx3
DIR- �������(V ��� H)
*/
void flip(unsigned char ***data, int c, int my, int mx3, int Nemx, char DIR)
{
	const char H = 'H';
	const char V = 'V';
	int mx = mx3 - Nemx;//����� � ����� ���� ����, ��� ������������ ���������
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
			for (int j = 0; j < Nemx; j++) {//� ����� ���������� ����
				data[c][i][mx + j - 1] = 0;
			}
		}
	}
}

/*
������� ����������� ��� ��������� ������� �������� �� +-255.
data- ������� � ���������
c- ���������� ������
my- ������
mx3- ������
arg- �������(�� -8 �� 8)
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
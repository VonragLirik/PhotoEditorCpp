/*
������� ��������� ���������� �������� � V*H ���
data- ������� � ���������
mx3- ������
my- ������
Nemx- ������� ����� mx � mx3
H - ���������� �� ������
V - ���������� �� ������
*/
unsigned char **downscale(unsigned char **matrix, int mx3, int my, int Nemx, int H, int V) 
{
	unsigned char** bufMatrix = new unsigned char*[my];
	for (int i = 0; i < my; i++)
		bufMatrix[i] = new unsigned char[mx3 + Nemx];


	int cntRows = 0, cntCols = 0;
	for (int i = 0; i < my; i++) {
		for (int j = 0; j < mx3; j++) {
			bufMatrix[i][j] = matrix[cntRows][cntCols];
			cntCols += H;
		}
		cntCols = 0;
		cntRows += V;
	}

	for (int i = 0; i < my*V; i++) delete[]matrix[i];

	return bufMatrix;
}

/*
������� ����������� ���������� �������� � V*H ���
data- ������� � ���������
mx3- ������
my- ������
Nemx- ������� ����� mx � mx3
H - ���������� �� ������
V - ���������� �� ������
*/

unsigned char **upscale(unsigned char **matrix, int mx3, int my, int Nemx, int H, int V) 
{
	unsigned char** bufMatrix = new unsigned char*[my];
	for (int i = 0; i < my; i++)
		bufMatrix[i] = new unsigned char[mx3 + Nemx];
	int cntROWS = -1, cntCOLS = -1;
	for (int i = 0; i < my; i++) {
		if (i % V == 0) {
			cntROWS++;
		}
		for (int j = 0; j < mx3; j++) {
			if (j % H == 0) {
				cntCOLS++;
			}
			bufMatrix[i][j] = matrix[cntROWS][cntCOLS];
		}
		cntCOLS = -1;
	}

	for (int i = 0; i < my / V; i++) delete[]matrix[i];

	return bufMatrix;
}

/*
������� ������������ ��� ������� �� 90 �������� �� ������� �������
data- ������� � ���������
my- ������
mx3- ������ � ����������� �� ��������� 4�
Nemx- ������� ����� mx � mx3
mx- ������ ��� ����������
my3- ������ � ����������� �� ��������� 4�
Nemy- ������� ����� my � my3
*/

unsigned char **rotate(unsigned char **matrix, int  my, int mx3, int Nemx, int mx, int my3, int Nemy)
{
	unsigned char** bufMatrix = new unsigned char*[mx];
	for (int i = 0; i < mx; i++)
		bufMatrix[i] = new unsigned char[my3];

	for (int i = 0; i < my; i++) {
		int bufCols = my - i - 1;
		for (int j = 0; j < mx; j++) {
			int bufRows = j;
			bufMatrix[bufRows][bufCols] = matrix[i][j];
		}
	}
	for (int i = 0; i < my; i++) delete[]matrix[i];

	for (int i = 0; i < mx; i++)
		for (int j = 0; j < Nemy; j++) bufMatrix[i][j + my] = 0;
	return bufMatrix;
}
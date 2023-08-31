/*
Команды из файла command.txt: номер файла(00 для всех): команда: параметры.
В файле command могут встречаться следующие команды:
rotate - поворот вправо по часовой (только 00)
flip - зеркальное отражение (v- вертикально)(h-горизонтально)
upscale - увеличение количества пикселей(не больше 1000)(только 00)
downscale- уменьшение количества пикселей(не больше 1000)(только 00)
bright - сдвиг значения яркости влево или вправо(<0), осуществляется через битовый сдвиг
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "framework.h"
using namespace std;


int main()
{
	FILE *command;
	int C, N;
	if ((command = fopen("command.txt", "rt")) == NULL)
	{
		printf("No input file\n");
		exit(1);
	}

	//Ввод количества файлов(C) и количества команд(N)
	fscanf(command, "%d %d", &C, &N);
	fclose(command);
	lib1(C, N);

}


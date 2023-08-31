/**
* \file StaticLib.cpp
* \brief Основная библиотека для работы с bmp картинками
* \details - Основная функция - обработка команд из файла command.txt
* \author Гарнов Кирилл Максимович студент МОП ЭВМ группы КТбо1-7
* \date 13.01.2021
*/





#define _CRT_SECURE_NO_WARNINGS
#include "framework.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
using namespace std;

#pragma pack( push, 1) 
typedef struct {
	__int16   bfType;
	int    bfSize;         // размер файла
	int    bfReserved;     // 0 (два в одном)
	int    bfOffBits;      // 1078
	int    biSize;         // размер струкуры в байтах
	int    biWidth;        // ширина в точках
	int    biHeight;       // высота в точках
	__int16   biPlanes;    // всегда 1
	__int16   biBitCount;  // 8
	int    biCompression;  // 0
	int    biSizeImage;    // размер пикселей
	int    biXPelsPerMeter;// 0
	int    biYPelsPerMeter;// 0
	int    biClrUsed;      // 0
	int    biClrImportant; // 0
} BMPheader;

typedef struct {
	int col;
}colors;

void lib1(int C, int N)
{
	const char rotateCom[7] = "rotate";
	const char flipCom[5] = "flip";
	const char downscaleCom[10] = "downscale";
	const char upscaleCom[8] = "upscale";
	const char brightCom[7] = "bright";
	colors color[257]; //массив с палитрой
	int Nemx; //разница до округления для х
	int Nemy; //разница до округления для у
	char com[100]; //команда
	char input[12]; //имя файла
	int tmp;
	char output[13]; //имя файла для вывода
	FILE *command, *input01;
	//проверка на наличие файлов в каталоге
	if ((command = fopen("command.txt", "rt")) == NULL)
	{
		printf("No input file\n");
		exit(1);
	}
	if ((input01 = fopen("input01.bmp", "rb")) == NULL)
	{
		printf("No input file\n");
		exit(1);
	}
	BMPheader header;    // заголовок BMPheader
	fscanf(command, "%d %d", &C, &N);
	// читаем заголовок
	fread(&header, 1, sizeof(BMPheader), input01);
	int mx = header.biWidth;
	int my = header.biHeight;
	fread(&color, 256, sizeof(colors), input01);//палитра
	fclose(input01);
	int mx3 = ((mx + 3)&(-4)); //длина строки вместе с округлением
	int my3 = ((my + 3)&(-4)); //длина строки вместе с округлением
	Nemx = mx3 - mx; //сколько нулей добавляется в каждой строке
	unsigned char*** data = new unsigned char**[C];    //для файлов
	for (int j = 1; j <= C; j++) // для строки
	{
		data[j] = new unsigned  char*[my];
		for (int i = 0; i < my; i++) data[j][i] = new unsigned char[mx3];// для столбцов
	}
	for (int i = 1; i <= C; i++)//запоминаем все значения файлов 
	{
		sprintf(input, "%s%02d%s", "input", i, ".bmp");
		FILE *inp = fopen(input, "rb");
		//записываем все в дату
		fread(&header, 1, sizeof(BMPheader), inp);
		fread(&color, 256, sizeof(colors), inp);//палитра
		for (int j = 0; j < my; j++)
		{
			fread(data[i][j], sizeof(unsigned char), mx3, inp);//записываем в дату строку

		}
		fclose(inp);
	}

	//команду записываем в com  и передаем в библиотеку для обработки
	for (int i = 0; i < N; i++)
	{
		char nomfa[302];
		char k[6];
		fscanf(command, "%s : %s : %s\n", &nomfa, &com, &k);
		if (strcmp(com, rotateCom) == 0) // если это rotate()
		{
			int my3 = ((my + 3)&(-4));
			int Nemy = my3 - my;
			int ANGLE = (atoi(k) / 90) % 4;//угол(0-ничего не меняем,1-90,2-180,3-270)
			if (ANGLE == 1) ANGLE = 3;
			else if (ANGLE == 3) ANGLE = 1;

			for (int j = 0; j < ANGLE; j++)
			{
				for (int i = 1; i <= C; i++)//для всех файлов
				{
					data[i] = rotate(data[i], my, mx3, Nemx, mx, my3, Nemy);
				}
				int tmp = mx;
				mx = my;
				my = tmp;
				tmp = mx3;
				mx3 = my3;
				my3 = tmp;
				Nemy = my3 - my;
				Nemx = mx3 - mx;
			}
		}
		if (strcmp(com, flipCom) == 0) //если это flip(), c-номер файла, DIR- команда
		{
			if (nomfa[0] && nomfa[1] == '0')			//используем все файлы(C штук)
			{
				char DIR = k[0];
				for (int i = 1; i <= C; i++)
					flip(data, i, my, mx3, Nemx, DIR);
			}
			else {//распознаем номер файла
				char b[2];
				int flag = 0;
				int d = 0;
				while (flag == 0)
				{
					int f = 0;
					for (; nomfa[d] != ',' && nomfa[d] != '\0'; d++)
					{
						if (nomfa[d] != 'B') {

							b[f] = nomfa[d];
							nomfa[d] = 'B';
							f++;
						}
					}
					if (nomfa[d] == '\0') flag++;
					else d++;
					int c = atoi(b);
					char DIR = k[0];
					flip(data, c, my, mx3, Nemx, DIR);
				}
			}
		}
		if (strcmp(com, upscaleCom) == 0)			// если это upscale()
		{
			int V, H;
			V = atoi(k);
			fscanf(command, "%d", &H);
			if ((my*V <= 1000) && (mx*H <= 1000))//не больше 10к по ширине и высоте
			{
				mx *= H;
				my *= V;
				mx3 = ((mx + 3)&(-4)); //длина строки вместе с округлением
				Nemx = mx3 - mx;
				header.biSizeImage *= (H*V);//правильный вес
				header.bfSize = header.biSizeImage + 1078;
				for (int i = 1; i <= C; i++)//для всех файлов
				{
					data[i] = upscale(data[i], mx, my, Nemx, H, V);
					for (int j = 0; j < my; j++)
						for (int k = 0; k < Nemx; k++)data[i][j][mx + k] = 0;
				}
			}
		}

		if (strcmp(com, downscaleCom) == 0)  // если это downscale()
		{
			int V, H;
			V = atoi(k);
			fscanf(command, "%d", &H);
			if ((mx%H == 0) && (my%V == 0))//кратный ширине и высоте одновременно
			{
				mx /= H;
				mx3 = ((mx + 3)&(-4)); //длина строки вместе с округлением
				Nemx = mx3 - mx;
				my /= V;
				header.biSizeImage /= (H*V);//правильный вес
				header.bfSize = header.biSizeImage + 1078;
				for (int i = 1; i <= C; i++)//для всех файлов
				{
					data[i] = downscale(data[i], mx, my, Nemx, H, V);
					for (int j = 0; j < my; j++)
						for (int k = 0; k < Nemx; k++) data[i][j][mx + k] = 0;
				}
			}
		}
		if (strcmp(com, brightCom) == 0) // если это bright()
		{
			if (nomfa[0] && nomfa[1] == '0')			//используем все файлы(C штук)
			{
				int arg = atoi(k);
				for (int i = 1; i <= C; i++) 	bright(data, i, my, mx3, arg);
			}
			else {//распознаем номер файла
				char b[2];
				int flag = 0;
				int d = 0;
				while (flag == 0)
				{
					int f = 0;
					for (; nomfa[d] != ',' && nomfa[d] != '\0'; d++)
					{
						if (nomfa[d] != 'B') {

							b[f] = nomfa[d];
							nomfa[d] = 'B';
							f++;
						}
					}
					if (nomfa[d] == '\0') flag++;
					else d++;
					int c = atoi(b);
					int arg = atoi(k);
					bright(data, c, my, mx3, arg);
				}
			}
		}
	}
	fclose(command);
	if (N == 0)//просто перезаписываем все файлы, меняя название на output
	{
		for (int i = 1; i <= C; i++)
		{
			sprintf(input, "%s%02d%s", "input", i, ".bmp");
			sprintf(output, "%s%02d%s", "output", i, ".bmp");
			FILE *inp = fopen(input, "rb");
			FILE *out = fopen(output, "wb");
			int SIZE = 2;
			char *buffer = new char[SIZE]; //буффер для записи
			while ((fread(buffer, sizeof(char), SIZE, inp)) > 0)  //чтение копируемого файла до конца
			{
				fwrite(buffer, sizeof(char), SIZE, out);//запись копии в новый файл
			}
			//закрываем файлы
			fclose(inp);
			fclose(out);
			//очищаем буфер
			delete[]buffer;
		}
	}
	else//если делали что-то
	{
		for (int i = 1; i <= C; i++)
		{
			sprintf(output, "%s%02d%s", "output", i, ".bmp");
			FILE *out = fopen(output, "wb");
			header.biWidth = mx;
			header.biHeight = my;
			fwrite(&header, sizeof(BMPheader), 1, out);		//заголовок
			fwrite(&color, sizeof(colors), 256, out);	//палитра
			for (int j = 0; j < my; j++)
			{
				//нужно сделать обработку с нулями в конце, если upscale downscale rotate(дописать при mx, а потом 0)
				fwrite(data[i][j], sizeof(unsigned char), mx3, out);//запись копии в новый файл
			}
			//закрываем файлы
			fclose(out);

		}

	}
	for (int j = 1; j <= C; j++)//очистка
	{
		for (int i = 0; i < my; i++) delete[] data[j][i];
		delete[] data[j];
	}
}



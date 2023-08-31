#pragma once

//ниже приведены все функции, которые могут быть в файле command.txt
void flip(unsigned char ***data, int c, int my, int mx3, int Nemx, char DIR);
void bright(unsigned char ***data, int c, int my, int mx3, int arg);
unsigned char **rotate(unsigned char **matrix, int  my, int mx3, int Nemx, int mx, int my3, int Nemy);
unsigned char **downscale(unsigned char **matrix, int mx3, int my, int Nemx, int H, int V);
unsigned char **upscale(unsigned char **matrix, int mx3, int my, int Nemx, int H, int V);
void lib1(int C, int N);
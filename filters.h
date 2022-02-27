// Copyright 2022 Popa Bianca 311CA <biancapopa2002@gmail.com>

#ifndef FILTERS
#define FILTERS
#include "load.h"

//edge
void edg(double *edge);

//sharpen
void sharp(double *sharpen);

//box blur
void bl(double *blur);

//gaussian blur
void bl2(double *blur2);

//aplicarea filtrului peste selectia curenta
void app(matrice *m, double ***vec_mat1,
		 double ***vec_mat2, double ***vec_mat3,
		 double *matrix);

#endif

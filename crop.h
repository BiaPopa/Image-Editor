// Copyright 2022 Popa Bianca 311CA <biancapopa2002@gmail.com>

#ifndef CROP
#define CROP
#include "load.h"

//reducerea imaginii grayscale
void crop_bw(matrice *mat, double ***vec_mat);

//reducerea imaginii color
void crop_c(matrice *mat, double ***vec_mat1,
			double ***vec_mat2, double ***vec_mat3);

//reducerea imaginii in cadrul selectiei curente
void cropp(matrice *mat, double ***vec_mat,
		   double ***vec_mat1, double ***vec_mat2,
		   double ***vec_mat3, int *u_nrl_c, int *u_nrl_bw);

#endif

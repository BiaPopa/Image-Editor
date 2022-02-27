// Copyright 2022 Popa Bianca 311CA <biancapopa2002@gmail.com>

#ifndef ROTIRE
#define ROTIRE
#include "load.h"

//rotirea intregii imagini grayscale
void rotate_bw_a(matrice *mat, double ***vec_mat);

//rotirea intregii imagini color
void rotate_c_a(matrice *mat, double ***vec_mat1,
				double ***vec_mat2, double ***vec_mat3);

//rotirea selectiei imaginii grayscale
void rotate_bw(matrice *mat, double ***vec_mat);

//rotirea selectiei imaginii grayscale
void rotate_c(matrice *mat, double ***vec_mat1,
			  double ***vec_mat2, double ***vec_mat3);

//rotirea selectiei curente
void rotate(int aux, matrice *mat, double ***vec_mat,
			double ***vec_mat1, double ***vec_mat2,
			double ***vec_mat3, int *u_nrl_c, int *u_nrl_bw,
			int c);

#endif

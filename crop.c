// Copyright 2022 Popa Bianca 311CA <biancapopa2002@gmail.com>

#include <stdio.h>
#include <stdlib.h>
#include "load.h"

//reducerea imaginii grayscale
void crop_bw(matrice *mat, double ***vec_mat)
{
	double **aux;
	aux = malloc(((mat->y2) - (mat->y1)) * sizeof(double *));
	for (int i = 0; i < ((mat->y2) - (mat->y1)); i++)
		aux[i] = malloc(((mat->x2) - (mat->x1)) * sizeof(double));

	for (int l = 0, i = (mat->y1); i < (mat->y2); i++, l++)
		for (int k = 0, j = (mat->x1); j < (mat->x2); j++, k++)
			aux[l][k] = (*vec_mat)[i][j];

	for (int i = 0; i < (mat->nr_l); i++)
		free((*vec_mat)[i]);
	free((*vec_mat));

	*vec_mat = aux;
	mat->nr_l = mat->y2 - mat->y1;
	mat->nr_c = mat->x2 - mat->x1;
}

void crop_part(matrice *mat, double ***vec_mat)
{
	double **aux;
	aux = malloc(((mat->y2) - (mat->y1)) * sizeof(double *));
	for (int i = 0; i < ((mat->y2) - (mat->y1)); i++)
		aux[i] = malloc(((mat->x2) - (mat->x1)) * sizeof(double));

	for (int l = 0, i = (mat->y1); i < (mat->y2); i++, l++)
		for (int k = 0, j = (mat->x1); j < (mat->x2); j++, k++)
			aux[l][k] = (*vec_mat)[i][j];

	for (int i = 0; i < (mat->nr_l); i++)
		free((*vec_mat)[i]);
	free((*vec_mat));

	(*vec_mat) = aux;
}

//reducerea imaginii color
void crop_c(matrice *mat, double ***vec_mat1,
			double ***vec_mat2, double ***vec_mat3)
{
	//matricea rosie
	crop_part(mat, vec_mat1);

	//matricea verde
	crop_part(mat, vec_mat2);

	//matricea albastra
	crop_part(mat, vec_mat3);

	(mat->nr_l) = mat->y2 - mat->y1;
	(mat->nr_c) = mat->x2 - mat->x1;
}

//reducerea imaginii in cadrul selectiei curente
void cropp(matrice *mat, double ***vec_mat, double ***vec_mat1,
		   double ***vec_mat2, double ***vec_mat3,
		   int *u_nrl_c, int *u_nrl_bw)
{
	if (mat->all == 1) { //toata imaginea e selectata
		printf("Image cropped\n");
	} else {
		if (mat->color == 0) {
			crop_bw(mat, vec_mat);
			*u_nrl_bw = mat->y2 - mat->y1;
		} else {
			crop_c(mat, vec_mat1, vec_mat2, vec_mat3);
			*u_nrl_c = mat->y2 - mat->y1;
		}
		mat->all = 1;
		printf("Image cropped\n");
	}
}

// Copyright 2022 Popa Bianca 311CA <biancapopa2002@gmail.com>

#include <stdio.h>
#include <stdlib.h>
#include "load.h"

//edge
void edg(double *edge)
{
	edge[0] = -1;
	edge[1] = -1;
	edge[2] = -1;
	edge[3] = -1;
	edge[4] = 8;
	edge[5] = -1;
	edge[6] = -1;
	edge[7] = -1;
	edge[8] = -1;
}

//sharpen
void sharp(double *sharpen)
{
	sharpen[0] = 0;
	sharpen[1] = -1;
	sharpen[2] = 0;
	sharpen[3] = -1;
	sharpen[4] = 5;
	sharpen[5] = -1;
	sharpen[6] = 0;
	sharpen[7] = -1;
	sharpen[8] = 0;
}

//box blur
void bl(double *blur)
{
	blur[0] = 1.0 / 9;
	blur[1] = 1.0 / 9;
	blur[2] = 1.0 / 9;
	blur[3] = 1.0 / 9;
	blur[4] = 1.0 / 9;
	blur[5] = 1.0 / 9;
	blur[6] = 1.0 / 9;
	blur[7] = 1.0 / 9;
	blur[8] = 1.0 / 9;
}

//gaussian blur
void bl2(double *blur2)
{
	blur2[0] = 1.0 / 16;
	blur2[1] = 2.0 / 16;
	blur2[2] = 1.0 / 16;
	blur2[3] = 2.0 / 16;
	blur2[4] = 4.0 / 16;
	blur2[5] = 2.0 / 16;
	blur2[6] = 1.0 / 16;
	blur2[7] = 2.0 / 16;
	blur2[8] = 1.0 / 16;
}

void clamp(double *elem)
{
	if ((*elem) < 0.0)
		(*elem) = 0.0;
	else if ((*elem) > 255.0)
		(*elem) = 255.0;
}

//aplicare filtru pe selectie
void filter_part(matrice *mat, double ***vec_mat, double *matrix)
{
	double **aux;
	aux = malloc(mat->nr_l * sizeof(double *));
	for (int i = 0; i < mat->nr_l; i++)
		aux[i] = malloc(mat->nr_c * sizeof(double));

	for (int i = 0; i < mat->nr_l; i++)
		for (int j = 0; j < mat->nr_c; j++)
			if (i >= mat->y1 && i < mat->y2 &&
				j >= mat->x1 && j < mat->x2) {
				aux[i][j] = (*vec_mat)[i - 1][j - 1] * matrix[0]
						+ (*vec_mat)[i - 1][j] * matrix[1]
						+ (*vec_mat)[i - 1][j + 1] * matrix[2]
						+ (*vec_mat)[i][j - 1] * matrix[3]
						+ (*vec_mat)[i][j] * matrix[4]
						+ (*vec_mat)[i][j + 1] * matrix[5]
						+ (*vec_mat)[i + 1][j - 1] * matrix[6]
						+ (*vec_mat)[i + 1][j] * matrix[7]
						+ (*vec_mat)[i + 1][j + 1] * matrix[8];
				clamp(&aux[i][j]);
			} else {
				aux[i][j] = (*vec_mat)[i][j];
			}

	for (int i = 0; i < mat->nr_l; i++)
		free((*vec_mat)[i]);
	free((*vec_mat));

	*vec_mat = aux;
}

//aplicare filtru pe intreaga imagine
void filter_all(matrice *mat, double ***vec_mat, double *matrix)
{
	double **aux;
	aux = malloc(mat->nr_l * sizeof(double *));
	for (int i = 0; i < mat->nr_l; i++)
		aux[i] = malloc(mat->nr_c * sizeof(double));

	for (int i = 0; i < mat->nr_l; i++)
		for (int j = 0; j < mat->nr_c; j++)
			if (i == 0 || j == 0 || i == mat->nr_l - 1 ||
				j == mat->nr_c - 1) {
				aux[i][j] = (*vec_mat)[i][j];
			} else {
				aux[i][j] = (*vec_mat)[i - 1][j - 1] * matrix[0]
						+ (*vec_mat)[i - 1][j] * matrix[1]
						+ (*vec_mat)[i - 1][j + 1] * matrix[2]
						+ (*vec_mat)[i][j - 1] * matrix[3]
						+ (*vec_mat)[i][j] * matrix[4]
						+ (*vec_mat)[i][j + 1] * matrix[5]
						+ (*vec_mat)[i + 1][j - 1] * matrix[6]
						+ (*vec_mat)[i + 1][j] * matrix[7]
						+ (*vec_mat)[i + 1][j + 1] * matrix[8];
				clamp(&aux[i][j]);
			}

	for (int i = 0; i < mat->nr_l; i++)
		free((*vec_mat)[i]);
	free((*vec_mat));

	*vec_mat = aux;
}

//aplicarea filtrului peste selectia curenta
void app(matrice *mat, double ***vec_mat1, double ***vec_mat2,
		 double ***vec_mat3, double *matrix)
{
	if (mat->all == 0) {
		if (mat->x1 == 0)
			mat->x1++;
		if (mat->y1 == 0)
			mat->y1++;
		if (mat->x2 == mat->nr_c)
			mat->x2--;
		if (mat->y2 == mat->nr_l)
			mat->y2--;

		//matricea rosie
		filter_part(mat, vec_mat1, matrix);

		//matricea verde
		filter_part(mat, vec_mat2, matrix);

		//matricea albastra
		filter_part(mat, vec_mat3, matrix);

	} else {
		//matricea rosie
		filter_all(mat, vec_mat1, matrix);

		//matricea verde
		filter_all(mat, vec_mat2, matrix);

		//matricea albastra
		filter_all(mat, vec_mat3, matrix);
	}
}


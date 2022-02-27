// Copyright 2022 Popa Bianca 311CA <biancapopa2002@gmail.com>

#include <stdio.h>
#include <stdlib.h>
#include "load.h"

//rotirea intregii imagini grayscale
void rotate_bw_a(matrice *mat, double ***vec_mat)
{
	double **aux;
	aux = malloc((mat->nr_c) * sizeof(double *));
	for (int i = 0; i < (mat->nr_c); i++)
		aux[i] = malloc((mat->nr_l) * sizeof(double));

	for (int i = 0; i < (mat->nr_c); i++)
		for (int j = 0; j < (mat->nr_l); j++)
			aux[i][j] = (*vec_mat)[(mat->nr_l) - j - 1][i];

	for (int i = 0; i < (mat->nr_l); i++)
		free((*vec_mat)[i]);
	free((*vec_mat));

	*vec_mat = aux;
	int aux2 = (mat->nr_l);
	(mat->nr_l) = (mat->nr_c);
	(mat->nr_c) = aux2;
}

//rotirea intregii imagini color
void rotate_c_a(matrice *mat, double ***vec_mat1,
				double ***vec_mat2, double ***vec_mat3)
{
	//matricea rosie
	rotate_bw_a(mat, vec_mat1);

	int aux = (mat->nr_l);
	(mat->nr_l) = (mat->nr_c);
	(mat->nr_c) = aux;

	//matricea verde
	rotate_bw_a(mat, vec_mat2);

	aux = (mat->nr_l);
	(mat->nr_l) = (mat->nr_c);
	(mat->nr_c) = aux;

	//matricea albastra
	rotate_bw_a(mat, vec_mat3);
}

//rotirea selectiei imaginii grayscale
void rotate_bw(matrice *mat, double ***vec_mat)
{
	if ((mat->x2 - mat->x1) != 1 && (mat->y2 - mat->y1) != 1) {
		double **aux;
		aux = malloc((mat->y2 - mat->y1) * sizeof(double *));
		for (int i = 0; i < (mat->y2 - mat->y1); i++)
			aux[i] = malloc((mat->x2 - mat->x1) * sizeof(double));

		int k = 0, l = 0;
		for (int i = 0; i < (mat->nr_l); i++) {
			for (int j = 0; j < (mat->nr_c); j++)
				if (i >= mat->y1 && i < mat->y2 && j >= mat->x1 && j < mat->x2)
					aux[k][l++] = (*vec_mat)[i][j];
			if (l == (mat->x2 - mat->x1)) {
				k++;
				l = 0;
			}
		}
		l = mat->x2 - mat->x1;
		int temp = mat->nr_l, temp2 = mat->nr_c;
		mat->nr_l = k;
		mat->nr_c = l;
		rotate_bw_a(mat, &aux);
		mat->nr_l = temp;
		mat->nr_c = temp2;

		k = 0, l = 0;
		for (int i = 0; i < (mat->nr_l); i++) {
			for (int j = 0; j < (mat->nr_c); j++)
				if (i >= mat->y1 && i < mat->y2 && j >= mat->x1 && j < mat->x2)
					(*vec_mat)[i][j] = aux[k][l++];
			if (l == (mat->x2 - mat->x1)) {
				k++;
				l = 0;
			}
		}

		for (int i = 0; i < k; i++)
			free(aux[i]);
		free(aux);
	}
}

//rotirea selectiei imaginii grayscale
void rotate_c(matrice *mat, double ***vec_mat1,
			  double ***vec_mat2, double ***vec_mat3)
{
	//matricea rosie
	rotate_bw(mat, vec_mat1);

	//matricea verde
	rotate_bw(mat, vec_mat2);

	//matricea albastra
	rotate_bw(mat, vec_mat3);
}

//rotirea selectiei curente
void rotate(int aux, matrice *mat, double ***vec_mat,
			double ***vec_mat1, double ***vec_mat2,
			double ***vec_mat3, int *u_nrl_c, int *u_nrl_bw, int c)
{
	if (mat->all == 1) {
		if (mat->color == 0) {
			while (aux) {
				rotate_bw_a(mat, vec_mat);
				aux--;
			}
			*u_nrl_bw = mat->nr_l;
		} else {
			while (aux) {
				rotate_c_a(mat, vec_mat1, vec_mat2, vec_mat3);
				aux--;
			}
			*u_nrl_c = mat->nr_l;
		}
		printf("Rotated %d\n", c);
	} else {
		if ((mat->y2 - mat->y1) != (mat->x2 - mat->x1)) {
			printf("The selection must be square\n");
		} else {
			if (mat->color == 0)
				while (aux) {
					rotate_bw(mat, vec_mat);
					aux--;
				}
			else
				while (aux) {
					rotate_c(mat, vec_mat1, vec_mat2, vec_mat3);
					aux--;
				}
			printf("Rotated %d\n", c);
		}
	}
}

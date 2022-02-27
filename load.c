// Copyright 2022 Popa Bianca 311CA <biancapopa2002@gmail.com>

#include <stdio.h>
#include <stdlib.h>

typedef struct matrice {
	int color; //= 0, grayscale, sau 1, color
	int nr_l; //numarul de linii
	int nr_c; //numarul de coloane
	int nr_i; //intensitatea
	int all; //= 1, daca e selectata toata imaginea, si 0, daca nu
	int x1, x2, y1, y2; //coordonatele selectiei curente
} matrice;

//incarcarea in memorie pentru imagine de tip P2
void load_p2(matrice *mat, int *ok_bw, int *u_nrl_bw,
			 double ***vec_mat, char ch[100], int pos)
{
	if (*ok_bw != 0) {
		for (int i = 0; i < *u_nrl_bw; i++)
			free((*vec_mat)[i]);
		free(*vec_mat);
		mat->all = 1;
	}
	FILE * in = fopen(ch, "rb");
	mat->color = 0;
	fseek(in, pos, SEEK_SET);
	fscanf(in, "%d%d%d", &mat->nr_c, &mat->nr_l, &mat->nr_i);

	*vec_mat = malloc(mat->nr_l * sizeof(double *));
	for (int i = 0; i < mat->nr_l; i++)
		(*vec_mat)[i] = malloc(mat->nr_c * sizeof(double));

	for (int i = 0; i < mat->nr_l; i++)
		for (int j = 0; j < mat->nr_c; j++)
			fscanf(in, "%lf", &(*vec_mat)[i][j]);

	fclose(in);
}

//incarcarea in memorie pentru imagine de tip P3
void load_p3(matrice *mat, int *ok_c, int *u_nrl_c, double ***vec_mat1,
			 double ***vec_mat2, double ***vec_mat3, char ch[100], int pos)
{
	if (*ok_c != 0) {
		for (int i = 0; i < *u_nrl_c; i++) {
			free((*vec_mat1)[i]);
			free((*vec_mat2)[i]);
			free((*vec_mat3)[i]);
		}
		free(*vec_mat1);
		free(*vec_mat2);
		free(*vec_mat3);
		mat->all = 1;
	}

	FILE * in = fopen(ch, "rb");
	mat->color = 1;
	fseek(in, pos, SEEK_SET);
	fscanf(in, "%d%d%d", &mat->nr_c, &mat->nr_l, &mat->nr_i);

	*vec_mat1 = malloc(mat->nr_l * sizeof(double *));
	for (int i = 0; i < mat->nr_l; i++)
		(*vec_mat1)[i] = malloc(mat->nr_c * sizeof(double));

	*vec_mat2 = malloc(mat->nr_l * sizeof(double *));
	for (int i = 0; i < mat->nr_l; i++)
		(*vec_mat2)[i] = malloc(mat->nr_c * sizeof(double));

	*vec_mat3 = malloc(mat->nr_l * sizeof(double *));
	for (int i = 0; i < mat->nr_l; i++)
		(*vec_mat3)[i] = malloc(mat->nr_c * sizeof(double));

	for (int i = 0; i < mat->nr_l; i++)
		for (int j = 0; j < mat->nr_c; j++)
			fscanf(in, "%lf%lf%lf", &(*vec_mat1)[i][j],
				   &(*vec_mat2)[i][j], &(*vec_mat3)[i][j]);

	fclose(in);
}

//incarcarea in memorie pentru imagine de tip P5
void load_p5(matrice *mat, int *ok_bw, int *u_nrl_bw,
			 double ***vec_mat, char ch[100], int pos)
{
	if (*ok_bw != 0) {
		for (int i = 0; i < *u_nrl_bw; i++)
			free((*vec_mat)[i]);
		free(*vec_mat);
		mat->all = 1;
	}
	FILE * in = fopen(ch, "rb");
	mat->color = 0;
	fseek(in, pos, SEEK_SET);
	fscanf(in, "%d%d%d", &mat->nr_c, &mat->nr_l, &mat->nr_i);

	char p[10];
	fgets(p, 10, in);

	*vec_mat = malloc(mat->nr_l * sizeof(double *));
	for (int i = 0; i < mat->nr_l; i++)
		(*vec_mat)[i] = malloc(mat->nr_c * sizeof(double));

	for (int i = 0; i < mat->nr_l; i++)
		for (int j = 0; j < mat->nr_c; j++) {
			unsigned char temp;
			fread(&temp, sizeof(unsigned char), 1, in);
			(*vec_mat)[i][j] = (double)temp;
		}

	fclose(in);
}

//incarcarea in memorie pentru imagine de tip P6
void load_p6(matrice *mat, int *ok_c, int *u_nrl_c, double ***vec_mat1,
			 double ***vec_mat2, double ***vec_mat3, char ch[100], int pos)
{
	if (*ok_c != 0) {
		for (int i = 0; i < *u_nrl_c; i++) {
			free((*vec_mat1)[i]);
			free((*vec_mat2)[i]);
			free((*vec_mat3)[i]);
		}
		free(*vec_mat1);
		free(*vec_mat2);
		free(*vec_mat3);
		mat->all = 1;
	}
	FILE * in = fopen(ch, "rb");
	mat->color = 1;
	fseek(in, pos, SEEK_SET);
	fscanf(in, "%d%d%d", &mat->nr_c, &mat->nr_l, &mat->nr_i);
	char p[10];
	fgets(p, 10, in);

	*vec_mat1 = malloc(mat->nr_l * sizeof(double *));
	for (int i = 0; i < mat->nr_l; i++)
		(*vec_mat1)[i] = malloc(mat->nr_c * sizeof(double));

	*vec_mat2 = malloc(mat->nr_l * sizeof(double *));
	for (int i = 0; i < mat->nr_l; i++)
		(*vec_mat2)[i] = malloc(mat->nr_c * sizeof(double));

	*vec_mat3 = malloc(mat->nr_l * sizeof(double *));
	for (int i = 0; i < mat->nr_l; i++)
		(*vec_mat3)[i] = malloc(mat->nr_c * sizeof(double));

	for (int i = 0; i < mat->nr_l; i++)
		for (int j = 0; j < mat->nr_c; j++) {
			unsigned char temp;
			fread(&temp, sizeof(unsigned char), 1, in);
			(*vec_mat1)[i][j] = (double)temp;

			unsigned char temp2;
			fread(&temp2, sizeof(unsigned char), 1, in);
			(*vec_mat2)[i][j] = (double)temp2;

			unsigned char temp3;
			fread(&temp3, sizeof(unsigned char), 1, in);
			(*vec_mat3)[i][j] = (double)temp3;
		}

	fclose(in);
}

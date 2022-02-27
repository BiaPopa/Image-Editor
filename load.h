// Copyright 2022 Popa Bianca 311CA <biancapopa2002@gmail.com>

#ifndef LOAD
#define LOAD

typedef struct matrice {
	int color;
	int nr_l;
	int nr_c;
	int nr_i;
	int all;
	int x1, x2, y1, y2;
} matrice;

//incarcarea in memorie pentru imagine de tip P2
void load_p2(matrice *mat, int *ok_bw,
			 int *u_nrl_bw, double ***vec_mat,
			 char ch[100], int pos);

//incarcarea in memorie pentru imagine de tip P3
void load_p3(matrice *mat, int *ok_c, int *u_nrl_c,
			 double ***vec_mat1, double ***vec_mat2,
			 double ***vec_mat3, char ch[100], int pos);

//incarcarea in memorie pentru imagine de tip P5
void load_p5(matrice *mat, int *ok_bw, int *u_nrl_bw,
			 double ***vec_mat, char ch[100], int pos);

//incarcarea in memorie pentru imagine de tip P6
void load_p6(matrice *mat, int *ok_c, int *u_nrl_c,
			 double ***vec_mat1, double ***vec_mat2,
			 double ***vec_mat3, char ch[100], int pos);

#endif

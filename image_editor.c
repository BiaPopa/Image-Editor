// Copyright 2022 Popa Bianca 311CA <biancapopa2002@gmail.com>

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include "rotire.h"
#include "crop.h"
#include "filters.h"
#include "load.h"

int roundd(double *temp)
{
	int tmp = (int)(*temp);
	if ((*temp - (double)tmp) > 0.5)
		tmp++;
	return tmp;
}

int digit(char *p)
{
	if (atoi(p) < 0)
		return 1;
	int l = strlen(p);
	for (int i = 0; i < l; i++)
		if (isdigit(p[i]) != 0)
			continue;
		else
			return 0;
	return 1;
}

int verify(char c[100])
{
	if (strcmp(c, "EXIT") == 0)
		return 1;
	if (strcmp(c, "LOAD") == 0)
		return 1;
	if (strcmp(c, "SAVE") == 0)
		return 1;
	if (strcmp(c, "CROP") == 0)
		return 1;
	if (strcmp(c, "ROTATE") == 0)
		return 1;
	if (strcmp(c, "APPLY") == 0)
		return 1;
	if (strcmp(c, "SELECT") == 0)
		return 1;
	return 0;
}

//selectarea intervalelor
void select_coord(matrice *mat, int *ok_bw, int *ok_c,
				  int *failed, char c[100], int *wrong_select,
				  char ch[100])
{
	int checkx1, checkx2, checky1, checky2, invalid = 0;
	if (mat->all == 0) {
		checkx1 = mat->x1;
		checkx2 = mat->x2;
		checky1 = mat->y1;
		checky2 = mat->y2;
	}
	//validarea parametrilor
	if (digit(c)) {
		mat->x1 = atoi(c);
		scanf("%s", c);
		if (digit(c)) {
			mat->y1 = atoi(c);
			scanf("%s", c);
			if (digit(c)) {
				mat->x2 = atoi(c);
				scanf("%s", c);
				if (digit(c))
					mat->y2 = atoi(c);
				else
					invalid = 1;
			} else {
				invalid = 1;
			}
		} else {
			invalid = 1;
		}
	} else {
		invalid = 1;
	}
	if (invalid == 1) {
		printf("Invalid command\n");
		if (mat->all == 0) {
			mat->x1 = checkx1;
			mat->x2 = checkx2;
			mat->y1 = checky1;
			mat->y2 = checky2;
		}
		if (verify(c) == 1) {
			*wrong_select = 1;
			strcpy(ch, c);
		}
	} else {
		//verificarea ordinii x1, x2
		if (mat->x1 > mat->x2) {
			int aux = mat->x1;
			mat->x1 = mat->x2;
			mat->x2 = aux;
		} //verificarea ordinii y1, y2
		if (mat->y1 > mat->y2) {
			int aux = mat->y1;
			mat->y1 = mat->y2;
			mat->y2 = aux;
		}
		if ((*ok_bw == 0 && *ok_c == 0) || *failed == -1) {
			printf("No image loaded\n");
		} else if (mat->x1 < 0 || mat->x2 > mat->nr_c || mat->y1 < 0 ||
				   mat->y2 > mat->nr_l || mat->x1 == mat->x2 ||
				   mat->y1 == mat->y2) {
			printf("Invalid set of coordinates\n");
			if (mat->all == 0) {
				mat->x1 = checkx1;
				mat->x2 = checkx2;
				mat->y1 = checky1;
				mat->y2 = checky2;
			}
		}  else {
			if (mat->x1 == 0 && mat->x2 == mat->nr_c && mat->y1 == 0 &&
				mat->y2 == mat->nr_l)
				mat->all = 1;
			else
				mat->all = 0;
			printf("Selected %d %d %d %d\n", mat->x1,
				   mat->y1, mat->x2, mat->y2);
		}
	}
}

//salvarea imaginii in fisier
void save(matrice *mat, int *ok_bw, int *ok_c, int *failed, char c[20],
		  char ch[100], int *img, double ***vec_mat, double ***vec_mat1,
		  double ***vec_mat2, double ***vec_mat3)
{
	if ((*ok_bw == 0 && *ok_c == 0) || *failed == -1) {
		printf("No image loaded\n");
	} else {
		FILE *out = fopen(ch, "wb");

		if (!out) {
			printf("Failed to load %s\n", ch);
			*failed = -1;
		} else {
			if (strcmp(c, " ascii") == 0 && *img == 0) {
				//ascii si grayscale
				fprintf(out, "P2\n%d %d\n%d\n", mat->nr_c,
						mat->nr_l, mat->nr_i);
				for (int i = 0; i < mat->nr_l; i++) {
					for (int j = 0; j < mat->nr_c; j++) {
						int temp = roundd(&(*vec_mat)[i][j]);
						fprintf(out, "%d ", temp);
					}
					fprintf(out, "\n");
				}

			} else if (strcmp(c, " ascii") == 0 && *img == 1) {
				//ascii si color
				fprintf(out, "P3\n%d %d\n%d\n", mat->nr_c,
						mat->nr_l, mat->nr_i);
				for (int i = 0; i < mat->nr_l; i++) {
					for (int j = 0; j < mat->nr_c; j++) {
						int temp = roundd(&(*vec_mat1)[i][j]);
						int temp2 = roundd(&(*vec_mat2)[i][j]);
						int temp3 = roundd(&(*vec_mat3)[i][j]);
						fprintf(out, "%d %d %d ", temp, temp2, temp3);
					}
					fprintf(out, "\n");
				}

			} else if (*img == 0) {
				//binar si grayscale
				fprintf(out, "P5\n%d %d\n%d\n", mat->nr_c,
						mat->nr_l, mat->nr_i);
				for (int i = 0; i < mat->nr_l; i++)
					for (int j = 0; j < mat->nr_c; j++) {
						int temp = roundd(&(*vec_mat)[i][j]);
						unsigned char temp2;
						temp2 = (unsigned char)temp;
						fwrite(&temp2, sizeof(unsigned char), 1, out);
					}
			} else {
				//binar si color
				fprintf(out, "P6\n%d %d\n%d\n", mat->nr_c,
						mat->nr_l, mat->nr_i);
				for (int i = 0; i < mat->nr_l; i++)
					for (int j = 0; j < mat->nr_c; j++) {
						int temp = roundd(&(*vec_mat1)[i][j]);
						unsigned char temp2;
						temp2 = (unsigned char)temp;
						fwrite(&temp2, sizeof(unsigned char), 1, out);

						temp = roundd(&(*vec_mat2)[i][j]);

						temp2 = (unsigned char)temp;
						fwrite(&temp2, sizeof(unsigned char), 1, out);

						temp = roundd(&(*vec_mat3)[i][j]);
						temp2 = (unsigned char)temp;
						fwrite(&temp2, sizeof(unsigned char), 1, out);
					}
			}
		}
		printf("Saved %s\n", ch);
		fclose(out);
	}
}

//incarcarea imaginii in memorie
void load(matrice *mat, double ***vec_mat, double ***vec_mat1,
		  double ***vec_mat2, double ***vec_mat3, char c[100],
		  char ch[100], int *ok_bw, int *ok_c, int *u_nrl_bw,
		  int *u_nrl_c, int *img, int pos)
{
	if (strcmp(c, "P2") == 0) {
		load_p2(mat, ok_bw, u_nrl_bw, vec_mat, ch, pos);

		*u_nrl_bw = mat->nr_l;
		*ok_bw = 1;
		*img = 0;

	} else if (strcmp(c, "P3") == 0) {
		load_p3(mat, ok_c, u_nrl_c, vec_mat1,
				vec_mat2, vec_mat3, ch, pos);

		*u_nrl_c = mat->nr_l;
		*ok_c = 1;
		*img = 1;

	} else if (strcmp(c, "P5") == 0) {
		load_p5(mat, ok_bw, u_nrl_bw, vec_mat, ch, pos);

		*u_nrl_bw = mat->nr_l;
		*ok_bw = 1;
		*img = 0;

	} else if (strcmp(c, "P6") == 0) {
		load_p6(mat, ok_c, u_nrl_c, vec_mat1,
				vec_mat2, vec_mat3, ch, pos);

		*u_nrl_c = mat->nr_l;
		*ok_c = 1;
		*img = 1;
	}
	printf("Loaded %s\n", ch);
}

//aplicarea filtrelor peste selectia curenta
void apply(matrice *mat, double ***vec_mat1, double ***vec_mat2,
		   double ***vec_mat3, int *ok_bw, int *ok_c, int *img, int *failed)
{
	char c[20];
	fgets(c, 20, stdin);
	c[strlen(c) - 1] = '\0';
	if ((*ok_bw == 0 && *ok_c == 0) || *failed == -1) {
		printf("No image loaded\n");
	} else if (strcmp(c, " EDGE") == 0) {
		if (*img == 0 && *ok_bw != 0) {
			printf("Easy, Charlie Chaplin\n");
		} else {
			double edge[9];
			edg(edge);
			app(mat, vec_mat1, vec_mat2, vec_mat3, edge);
			printf("APPLY%s done\n", c);
		}
	} else if (strcmp(c, " SHARPEN") == 0) {
		if (*img == 0 && *ok_bw != 0) {
			printf("Easy, Charlie Chaplin\n");
		} else {
			double sharpen[9];
			sharp(sharpen);
			app(mat, vec_mat1, vec_mat2, vec_mat3, sharpen);
			printf("APPLY%s done\n", c);
		}
	} else if (strcmp(c, " BLUR") == 0) {
		if (*img == 0 && *ok_bw != 0) {
			printf("Easy, Charlie Chaplin\n");
		} else {
			double blur[9];
			bl(blur);
			app(mat, vec_mat1, vec_mat2, vec_mat3, blur);
			printf("APPLY%s done\n", c);
		}
	} else if (strcmp(c, " GAUSSIAN_BLUR") == 0) {
		if (*img == 0 && *ok_bw != 0) {
			printf("Easy, Charlie Chaplin\n");
		} else {
			double blur2[9];
			bl2(blur2);
			app(mat, vec_mat1, vec_mat2, vec_mat3, blur2);
			printf("APPLY%s done\n", c);
		}
	} else if (strcmp(c, "\0") == 0) {
		printf("Invalid command\n");
	} else {
		printf("APPLY parameter invalid\n");
	}
}

//rotirea selectiei curente
void rot(matrice *mat, double ***vec_mat, double ***vec_mat1,
		 double ***vec_mat2, double ***vec_mat3, int *ok_bw,
		 int *ok_c, int *failed, int *u_nrl_bw, int *u_nrl_c)
{
	int c;
	scanf("%d", &c);
	if ((*ok_bw == 0 && *ok_c == 0) || *failed == -1) {
		printf("No image loaded\n");
	} else {
		if (c == 0 || c == 360 || c == -360) {
			printf("Rotated %d\n", c);
		} else if (c == 90 || c == -270) {
			int aux = 1;
			rotate(aux, mat, vec_mat, vec_mat1, vec_mat2, vec_mat3,
				   u_nrl_c, u_nrl_bw, c);
		} else if (c == 180 || c == -180) {
			int aux = 2;
			rotate(aux, mat, vec_mat, vec_mat1, vec_mat2, vec_mat3,
				   u_nrl_c, u_nrl_bw, c);
		} else if (c == 270 || c == -90) {
			int aux = 3;
			rotate(aux, mat, vec_mat, vec_mat1, vec_mat2, vec_mat3,
				   u_nrl_c, u_nrl_bw, c);
		} else {
			printf("Unsupported rotation angle\n");
		}
	}
}

void command(matrice *mat, double ***vec_mat, double ***vec_mat1,
			 double ***vec_mat2, double ***vec_mat3, char ch[100],
			 int *ok_bw, int *ok_c, int *u_nrl_bw, int *u_nrl_c,
			 int *failed)
{
	int img; //retine tipul de imagine, grayscale sau color
	while (strcmp(ch, "EXIT") != 0) {
		int ok = 0, wrong_select = 0;
		if (strcmp(ch, "LOAD") == 0) {
			scanf("%s", ch);
			FILE *in = fopen(ch, "rb");
			if (!in) {
				printf("Failed to load %s\n", ch);
				*failed = -1;
			} else {
				*failed = 0;
				char c[3];
				fscanf(in, "%s", c);
				int pos = ftell(in);
				fclose(in);
				load(mat, vec_mat, vec_mat1, vec_mat2, vec_mat3,
					 c, ch, ok_bw, ok_c, u_nrl_bw, u_nrl_c, &img, pos);
			}
			ok = 1;

		} else if (strcmp(ch, "SELECT") == 0) {
			char c[100];
			scanf("%s", c);
			if (strcmp(c, "ALL") == 0) {
				if ((*ok_bw == 0 && *ok_c == 0) || *failed == -1) {
					printf("No image loaded\n");
				} else {
					mat->all = 1;
					printf("Selected ALL\n");
				}
			} else {
				select_coord(mat, ok_bw, ok_c, failed, c, &wrong_select, ch);
			}
			ok = 1;

		} else if (strcmp(ch, "ROTATE") == 0) {
			rot(mat, vec_mat, vec_mat1, vec_mat2, vec_mat3, ok_bw,
				ok_c, failed, u_nrl_bw, u_nrl_c);
			ok = 1;

		} else if (strcmp(ch, "CROP") == 0) {
			if ((*ok_bw == 0 && *ok_c == 0) || *failed == -1) {
				printf("No image loaded\n");
			} else {
				if (mat->x1 == 0 && mat->x2 == mat->nr_c &&
				    mat->y1 == 0 && mat->y2 == mat->nr_l)
					printf("Image cropped\n");
				else
					cropp(mat, vec_mat, vec_mat1, vec_mat2, vec_mat3,
						  u_nrl_c, u_nrl_bw);
			}
			ok = 1;

		} else if (strcmp(ch, "APPLY") == 0) {
			apply(mat, vec_mat1, vec_mat2, vec_mat3,
				  ok_bw, ok_c, &img, failed);
			ok = 1;

		} else if (strcmp(ch, "SAVE") == 0) {
			scanf("%s", ch);
			char c[20];
			fgets(c, 20, stdin);
			c[strlen(c) - 1] = '\0';
			save(mat, ok_bw, ok_c, failed, c, ch, &img,
				 vec_mat, vec_mat1, vec_mat2, vec_mat3);
			ok = 1;
		}
		if (ok == 0) {
			char c[100];
			fgets(c, 100, stdin);
			printf("Invalid command\n");
		}
		if (wrong_select == 0)
			scanf("%s", ch);
	}
}

int main(void)
{
	double **vec_mat, **vec_mat1, **vec_mat2, **vec_mat3;
	int ok_bw = 0, ok_c = 0, failed =  0;
	//numarul de linii al ultimei matrice grayscale citite
	int u_nrl_bw;
	//numarul de linii al ultimei matrice color citite
	int u_nrl_c;

	matrice mat;
	mat.all = 1;
	char ch[100];
	scanf("%s", ch);

	command(&mat, &vec_mat, &vec_mat1, &vec_mat2, &vec_mat3, ch,
			&ok_bw, &ok_c, &u_nrl_bw, &u_nrl_c, &failed);

	if ((ok_bw == 0 && ok_c == 0) || failed == -1)
		printf("No image loaded\n");

	//eliberarea tuturor resurselor
	if (ok_bw != 0) {
		for (int i = 0; i < u_nrl_bw; i++)
			free(vec_mat[i]);

		free(vec_mat);
	}
	if (ok_c != 0) {
		for (int i = 0; i < u_nrl_c; i++) {
			free(vec_mat1[i]);
			free(vec_mat2[i]);
			free(vec_mat3[i]);
		}
		free(vec_mat1);
		free(vec_mat2);
		free(vec_mat3);
	}
	return 0;
}

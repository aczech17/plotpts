#include "matrix.h"
#include <stdlib.h>
#include <math.h>

matrix_t *
pivot_ge_matrix (matrix_t * a, int *row_per)
{
  matrix_t *c = copy_matrix (a);
  if (c != NULL) {
    int i, j, k;
    int cn = c->cn;
    int rn = c->rn;
    double *e = c->e;
    for (i = 0; i < rn; i++)
      row_per[i] = i;
    for (k = 0; k < rn - 1; k++) {      /* eliminujemy (zerujemy) kolumnę nr k */
      int piv = k;              /* wybór eleemntu dominującego - maks. z k-tej kol., poniżej diag */
      for (i = k + 1; i < rn; i++)
        if (fabs (*(e + i * cn + k)) > fabs (*(e + piv * cn + k)))
          piv = i;
      if (piv != k) {           /* jeśli diag. nie jest pivtem - wymień wiersze */
        int tmp;
        xchg_rows (c, piv, k);
        tmp = row_per[k];
        row_per[k] = row_per[piv];
        row_per[piv] = tmp;
      }
      for (i = k + 1; i < rn; i++) {    /* pętla po kolejnych
                                           wierszach poniżej diagonalii k,k */
        double d = *(e + i * cn + k) / *(e + k * cn + k);
        for (j = k; j < cn; j++)
          *(e + i * cn + j) -= d * *(e + k * cn + j);
      }
    }
  }
  return c;
}

void pivot_ge_in_situ_matrix(matrix_t* c)
{
    int width = c->cn;
    int height = c->rn;
    double* e = c->e;

    int i, j, k;
    for (k = 0; k < height - 1; k++) /* eliminujemy (zerujemy) kolumnę nr k */
    {  
            
        int piv = k;                /* wybór elementu dominującego - maks. z k-tej kol., poniżej diag */

        int row;
        for (row = k + 1; row < height; row++)
            if (fabs(*(e + row * width + k)) > fabs(*(e + piv * width + k)))
                piv = i;

        
        if (piv != k)             /* jeśli diag. nie jest pivotem - wymień wiersze */
            xchg_rows(c, piv, k);


        for (row = k + 1; row < height; row++)      /* pętla po kolejnych wierszach poniżej diagonalii k,k */
        {              
            double d = *(e + row * width + k) / *(e + k * width + k);

            
            int col;
            for (col = k; col < width; col++)
            {
                *(e + row * width + col) -= d * *(e + k * width + j);
            }
        }
    }
}

matrix_t *
symm_pivot_ge_matrix (matrix_t * a, int *row_per)
{
  matrix_t *c = copy_matrix (a);
  if (c != NULL) {
    int i, j, k;
    int cn = c->cn;
    int rn = c->rn;
    double *e = c->e;
    for (i = 0; i < rn; i++)
      row_per[i] = i;
    for (k = 0; k < rn - 1; k++) {      /* eliminujemy (zerujemy) kolumnę nr k */
      int piv = k;              /* wybór eleemntu dominującego - maks. z k-tej kol., poniżej diag */
      for (i = k + 1; i < rn; i++)
        if (fabs (*(e + i * cn + k)) > fabs (*(e + piv * cn + k)))
          piv = i;
      if (piv != k) {           /* jeśli diag. nie jest pivtem - wymień wiersze */
        int tmp;
        xchg_rows (c, piv, k);
        xchg_cols (c, piv, k);
        tmp = row_per[k];
        row_per[k] = row_per[piv];
        row_per[piv] = tmp;
      }
      for (i = k + 1; i < rn; i++) {    /* pętla po kolejnych
                                           wierszach poniżej diagonalii k,k */
        double d = *(e + i * cn + k) / *(e + k * cn + k);
        for (j = k; j < cn; j++)
          *(e + i * cn + j) -= d * *(e + k * cn + j);
      }
    }
  }
  return c;
}

int *
pivot_get_inv_per (matrix_t * m, int *row_per)
{
  /* odtwarzamy oryginalną kolejność niewiadowmych */
  int *iper = malloc (m->rn * sizeof *iper);
  int i;

  for (i = 0; i < m->rn; i++)
    iper[row_per[i]] = i;

  return iper;
}

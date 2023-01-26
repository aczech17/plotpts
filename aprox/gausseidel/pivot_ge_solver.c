#include "matrix.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
    if (argc <= 1)
        return 1;
    
    FILE* in = fopen(argv[1], "r");
    if (in == NULL)
        return 1;

    matrix_t* m = read_matrix(in);
    if (m == NULL)
        return 1;

    int sym = 0;
    
    matrix_t* c = NULL;
    int* row_per = malloc(m->rn * sizeof *row_per);
    printf("\nMacierz:\n");
    write_matrix (m, stdout);
    if (argc > 2 && strcmp (argv[2], "-s") == 0)
    {
        c = symm_pivot_ge_matrix(m, row_per);
        sym = 1;
    }
    else
        c = pivot_ge_matrix (m, row_per);
        
    if (c == NULL)
    {
        printf("Nie działa\n");
        return 1;
    }

    int i;
    printf("\nPo elim. Gaussa:\n");
    write_matrix(c, stdout);
    printf("Permutacja:");
    for (i = 0; i < c->rn; i++)
        printf(" %d", row_per[i]);
    printf("\n");

    if (bs_matrix(c) != 0)
        return 1;

    int* iper = pivot_get_inv_per(c, row_per);
    printf("Permutacja odwrotna:");
    for (i = 0; i < c->rn; i++)
        printf(" %d", iper[i]);
    printf("\n");

    printf("\nPo podstawieniu wstecz:\n");
    write_matrix (c, stdout);
    printf("Rozwiązania: \n");

    int j;
    for (j = 0; j < c->cn - c->rn; j++)
    {
        printf("Nr %d:\n", j + 1);
        for (i = 0; i < c->rn; i++)
        {
            int oi = sym ? iper[i] : i;
            printf("\t%g", *(c->e + oi * c->cn + j + c->rn));
        }
        printf("\n");
    }
    return 0;
}

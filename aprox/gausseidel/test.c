#include "matrix.h"
#include <stdio.h>
#include "piv_ge_solver.h"

void print_matrix(matrix_t* m)
{
    int row, col;
    for (row = 0; row < m->rn; row++)
    {
        for (col = 0; col < m->cn; col++)
        {
            printf("%g\t", get_entry_matrix(m, row, col));
        }
        printf("\n");
    }
}

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        fprintf(stderr, "Podaj nazwe pliku.\n");
        return 1;
    }

    FILE* in = fopen(argv[1], "r");
    if (in == NULL)
    {
        fprintf(stderr, "Nie wczytano\n");
        return 1;
    }

    matrix_t* m = read_matrix(in);
    fclose(in);

    piv_ge_solver(m);
    print_matrix(m);

    free_matrix(m);
    return 0;
}

#include "piv_ge_solver.h"
#include <stdlib.h>

#include "matrix.h"

/*
int piv_ge_solver(matrix_t* eqs)
{
    if (eqs == NULL)
        return 1;

    pivot_ge_in_situ_matrix(eqs);

    if (bs_matrix (eqs) != 0)
        return 1;
      
    return 0;
}
*/

static matrix_t* get_b_mat(matrix_t* eqs)
{
    matrix_t* b = make_matrix(eqs->rn, 1);
    int row;
    for (row = 0; row < eqs->rn; row++)
    {
        double val = get_entry_matrix(eqs, row, eqs->cn - 1);
        put_entry_matrix(b, row, 0, val);
    }

    return b;
}

static matrix_t* get_a_mat(matrix_t* eqs)
{
    matrix_t* a = make_matrix(eqs->rn, eqs->cn - 1);
    int row, col;
    for (row = 0; row < eqs->rn; row++)
        for (col = 0; col < eqs->cn - 1; col++)
        {
            double val = get_entry_matrix(eqs, row, col);
            put_entry_matrix(a, row, col, val);
        }

    return a;
}

void print(matrix_t* m)
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

int piv_ge_solver(matrix_t* eqs)
{
    if (eqs == NULL)
        return 1;

    // eqs = A | B

    matrix_t* a = get_a_mat(eqs);
    matrix_t* L = make_lower(a);

    matrix_t* U = make_strict_upper(a);

    matrix_t* L_inv = get_inversed(L);
    
    

    matrix_t* T = mull_matrix(L_inv, U);
    mult_by_num(T, -1.0);    

    matrix_t* b = get_b_mat(eqs);
    
    
    matrix_t* C = mull_matrix(L_inv, b);


    // We have T, C

    matrix_t* x = make_matrix(eqs->rn, 1);
    int row;
    for (row = 0; row < eqs->rn; row++)
        put_entry_matrix(x, row, 0, 1.0);


    
    // x = T * x + C
    const int N = 1000000;
    int i;
    for (i = 0; i < N; i++)
    {
        matrix_t* T_times_x = mull_matrix(T, x);
        matrix_t* new_x = add_matrix(T_times_x, C);

        free_matrix(x);
        x = new_x;

        free_matrix(T_times_x);
        //print(x);
        //printf("\n");
    }


    // Put it (???????????)
    for (row = 0; row < eqs->rn; row++)
    {
        double value = get_entry_matrix(x, row, 0);
        put_entry_matrix(eqs, row, eqs->cn - 1, value);
    }


    free_matrix(a);
    free_matrix(b);
    free_matrix(U);
    free_matrix(T);
    free_matrix(C);
    free_matrix(L_inv);
    free_matrix(L);
    free_matrix(x);
    return 0;
}

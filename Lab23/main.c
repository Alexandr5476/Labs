#include <stdio.h>
#include <locale.h>
#include "matrix_abc.h"
#include "matrix_init.h"
#include "matrix_operations.h"
#include "matrix_problems.h"

int main()
{
    size_t h, w;
    matrix *m, *f, *answer;

    setlocale (LC_CTYPE, "Russian");

    printf("Введите размер матрицы: ");
    scanf("%Lu %Lu", &h, &w);

    if (!(m = matrix_alloc(h, w))) return 1;
    if (!(answer = matrix_alloc(h, 1)))
    {
        matrix_free(m);
        return 1;
    }
    if (!(f = matrix_alloc(h, 1)))
    {
        matrix_free(answer);
        matrix_free(m);
        return 1;
    }

    printf("Введите матрицу:\n");
    for (size_t i = 0; i < h; ++i)
        for (size_t j = 0; j < w; ++j)
        {
            double *e = matrix_get(m, i, j);
            scanf("%lf", e);
        }

    printf("Введите правые части:\n");
    for (size_t i = 0; i < h; ++i)
        {
            double *e = matrix_get(f, i, 0);
            scanf("%lf", e);
        }


    if (matrix_gauss_method(m, f, answer))
    {
        printf("Решение слу:\n\n");
        matrix_print(answer);
    }
    else printf("Ошибка\n");

    matrix_free(m);
    matrix_free(f);
    matrix_free(answer);

    printf("Матричная экспонента от\n");

    if (!(m = matrix_alloc_identity(3))) return 1;
    if (!(f = matrix_alloc(3, 3)))
    {
        matrix_free(m);
        return 1;
    }
    *matrix_get(m, 1, 1) = 2;
    *matrix_get(m, 2, 2) = -1;


    matrix_print(m);
    printf("Равна\n\n");

    matrix_print(matrix_assign(f, matrix_exp(m)));

    matrix_free(m);
    matrix_free(f);

    return 0;
}

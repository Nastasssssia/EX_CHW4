#include <stdio.h>
/*
Реализовать программу 1-го практического задания с помощью биномиального коэффициента.
Данные на вход: Два целых числа N и M
Данные на выход: Одно целое число – количество вариантов
*/

// Функция для вычисления биномиального коэффициента через треугольник Паскаля
int binomial_coefficient(int n, int m)
{
    int pascal[n + 1][m + 1];

    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= (i < m ? i : m); j++)
        {
            if (j == 0 || j == i)
            {
                pascal[i][j] = 1; // Граничные случаи
            }
            else
            {
                pascal[i][j] = pascal[i - 1][j - 1] + pascal[i - 1][j];
            }
        }
    }

    return pascal[n][m];
}

int main()
{
    int n, m;
    printf("Введите N и M: ");
    scanf("%d %d", &n, &m);

    if (m > n || n < 0 || m < 0)
    {
        printf("Неверные входные данные\n");
        return 1;
    }

    int result = binomial_coefficient(n, m);
    printf("Количество вариантов: %d\n", result);

    return 0;
}
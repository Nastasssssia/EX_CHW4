#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE 100

/*
Написать алгоритм перевода из инфиксной записи в обратную польскую.
 Для его реализации нужны данные по приоритетам операций. Реализовать алгоритм, используя побитовые операции (&, |, ^).

*/

// Функция для проверки приоритета операций
int precedence(char op)
{
    switch (op)
    {
    case '&':
        return 3;
    case '^':
        return 2;
    case '|':
        return 1;
    default:
        return 0;
    }
}

int is_operator(char ch)
{
    return ch == '&' || ch == '|' || ch == '^';
}

void infix_to_postfix(const char *infix, char *postfix)
{
    char stack[MAX_SIZE];
    int stack_top = -1;    // Индекс вершины стека
    int postfix_index = 0; // Индекс для записи в выходную строку

    for (int i = 0; infix[i] != '\0'; i++)
    {
        char ch = infix[i];

        if (isdigit(ch))
        {
            // Если символ — число, добавляем в выходную строку
            postfix[postfix_index++] = ch;

            // Проверяем на многозначные числа
            while (isdigit(infix[i + 1]))
            {
                postfix[postfix_index++] = infix[++i];
            }

            postfix[postfix_index++] = ' '; // Разделитель
        }
        else if (ch == '(')
        {
            // Открывающая скобка — кладём в стек
            stack[++stack_top] = ch;
        }
        else if (ch == ')')
        {
            // Закрывающая скобка — выгружаем стек до открывающей скобки
            while (stack_top >= 0 && stack[stack_top] != '(')
            {
                postfix[postfix_index++] = stack[stack_top--];
                postfix[postfix_index++] = ' ';
            }
            stack_top--; // Убираем '(' из стека
        }
        else if (is_operator(ch))
        {
            // Если оператор, сравниваем приоритет с вершиной стека
            while (stack_top >= 0 && precedence(stack[stack_top]) >= precedence(ch))
            {
                postfix[postfix_index++] = stack[stack_top--];
                postfix[postfix_index++] = ' ';
            }
            stack[++stack_top] = ch;
        }
    }

    // Выгружаем оставшиеся операторы из стека
    while (stack_top >= 0)
    {
        postfix[postfix_index++] = stack[stack_top--];
        postfix[postfix_index++] = ' ';
    }

    postfix[postfix_index] = '\0'; // Завершаем строку
}

int main()
{
    char infix[MAX_SIZE];
    char postfix[MAX_SIZE];

    printf("Введите выражение в инфиксной записи: ");
    fgets(infix, MAX_SIZE, stdin);

    infix[strcspn(infix, "\n")] = '\0';

    infix_to_postfix(infix, postfix);

    printf("Обратная польская запись: %s\n", postfix);

    return 0;
}
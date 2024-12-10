#include <stdio.h>
#include <string.h>
enum
{
    maxlength = 10001
};

// Функция для вычисления Z-функции
void calculate_z(const char *s, int *z, int len)
{
    int l = 0, r = 0;
    for (int i = 1; i < len; i++)
    {
        if (i <= r)
        {
            z[i] = (r - i + 1 < z[i - l]) ? (r - i + 1) : z[i - l];
        }
        while (i + z[i] < len && s[z[i]] == s[i + z[i]])
        {
            z[i]++;
        }
        if (i + z[i] - 1 > r)
        {
            l = i;
            r = i + z[i] - 1;
        }
    }
}

// Функция поиска максимального совпадения суффикса одной строки с префиксом другой
int search_prefix(char *s1, char *s2)
{
    int len1 = strlen(s1);
    int len2 = strlen(s2);

    char concat[len2 + len1 + 2];
    snprintf(concat, sizeof(concat), "%s#%s", s2, s1);

    int z[len2 + len1 + 2];
    memset(z, 0, sizeof(z));

    calculate_z(concat, z, len2 + len1 + 1);

    int max_match = 0;
    for (int i = len2 + 1; i <= len2 + len1; i++)
    {
        if (z[i] > max_match)
        {
            max_match = z[i];
        }
    }

    return max_match;
}

int main()
{
    char s1[maxlength], s2[maxlength];
    scanf("%10000s", s1);
    scanf("%10000s", s2);

    int result = search_prefix(s1, s2);

    printf("%d\n", result);

    return 0;
}

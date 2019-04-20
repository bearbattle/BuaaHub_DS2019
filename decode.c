#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node
{
    char date[30], O[1100], E[1100];
} node;

char key[110], key0[110], gg[50];
node message[1100];

char f(char src, char k) { return (char)((src + k - 'a' - 'a') % 26 + 'a'); }

char f1(char src, char k) { return (char)((src - k + 26) % 26 + 'a'); }

char g(char src) { return gg[src - 'a']; }

int cmp(const void *a, const void *b)
{
    node p = *(node *)a;
    node q = *(node *)b;
    return strcmp(p.date, q.date);
}

void ResetKey() { strcpy(key, key0); }

void ChangeKey()
{
    int len = (int)strlen(key);
    int i;
    char tmp = key[len - 1];
    for (i = len - 1; i > 0; i--)
        key[i] = key[i - 1];
    key[0] = tmp;
}
int fucker = 0;
int main()
{
    int flag = 0;
    int n;
    int Cnt = 0;
    int i;
    int len;

    scanf("%d ", &n);
    gets(key0);
    gets(gg);
    fprintf(stderr, "Length of key0 is %d, length of gg is %d\n", strlen(key0), strlen(gg));

    len = strlen(key0);
    for (i = 0; key0[i] != '\0'; i++)
    {
        key0[i] = tolower(key0[i]);
    }

    for (Cnt = 0; Cnt < n; Cnt++)
    {
        memset(message[Cnt].E, 0, sizeof(message[Cnt].E));
        scanf("%s %s", message[Cnt].date, message[Cnt].O);
        fprintf(stderr, "Length of date is %d, Length of content is %d\n", (int)strlen(message[Cnt].date),
                (int)strlen(message[Cnt].O));
        ResetKey();

        for (i = 0; message[Cnt].O[i] != '\0'; i++)
        {
            flag = 0;

            if (i > 0 && i % len == 0)
            {
                ChangeKey();
            }

            if (isupper(message[Cnt].O[i]))
            {
                flag = 1;
                message[Cnt].O[i] = tolower(message[Cnt].O[i]);
            }

            message[Cnt].E[i] = f1(g(f(message[Cnt].O[i], key[i % len])), key[i % len]);
            fprintf(stderr, "%d: Encrypting %c using %c, result = %c\n", fucker++, message[Cnt].O[i],
                    key[i % len], message[Cnt].E[i]);
            if (flag)
                message[Cnt].E[i] = toupper(message[Cnt].E[i]);
        }
    }

    qsort(message, n, sizeof(message[0]), cmp);

    for (Cnt = 0; Cnt < n; Cnt++)
        printf("%s %s\n", message[Cnt].date, message[Cnt].E);

    return 0;
}
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node
{
    char date[20];
    char Open[1024];
    char Encrypt[1024];
} node;

char key[110];
char key0[110];
char gg[30];

node message[1007];
char Encrypt[1100], Open[1100];
int cmp(const void *a, const void *b)
{
    node p, q;
    p = *(node *)a;
    q = *(node *)b;
    return strcmp(p.date, q.date);
}

char g(char x) { return gg[(int)x - 'a']; }

char f(char src, char k)
{
    char res = (src + tolower(k) - 2 * 'a') % 26 + 'a';
    //printf("f: %c -> %c\t", src, res);
    return res;
}

char f1(char src, char k)
{
    char res = (src - k + 52) % 26 + 'a';
    //printf("f1: %c -> %c\n", src, res);
    return res;
}

void ResetKey() { strcpy(key, key0); }

void ChangeKey()
{
    int i;
    int len = strlen(key);
    char t = key[len - 1];
    for (i = len - 1; i > 0; i--)
    {
        key[i] = key[i - 1];
    }
    key[0] = t;
}

int main()
{
    int i;
    int flag = 0;
    int n;
    int len;
    int Cnt;
    scanf("%d\n", &n);
    gets(key0);
    gets(gg);
    //printf("get Reflector:%s\n", gg);
    len = strlen(key0);
    for (Cnt = 0; Cnt < n; Cnt++)
    {
        scanf("%s%s", message[Cnt].date, message[Cnt].Open);
        ResetKey();
        memset(Encrypt, 0, sizeof(Encrypt));
        memset(Open, 0, sizeof(Open));
        strcpy(Open, message[Cnt].Open);
        //printf("DEBUG Message: Key:%s, Origin:%s\n", key, Open);
        for (i = 0; Open[i] != '\0'; i++)
        {
            flag = 0;
            if (i > 0 && i % len == 0)
            {
                ChangeKey();
                //printf("Key rotated.\n");
            }
            if (isupper(Open[i]))
                flag = 1;
            Encrypt[i] = f1(g(f(tolower(Open[i]), tolower(key[i % len]))), tolower(key[i % len]));
            if (flag)
            {
                Encrypt[i] = toupper(Encrypt[i]);
            }
        }
        strcpy(message[Cnt].Encrypt, Encrypt);
    }
    qsort(message, n, sizeof(message[0]), cmp);
    for (Cnt = 0; Cnt < n; Cnt++)
    {
        printf("%s %s\n", message[Cnt].date, message[Cnt].Encrypt);
    }
    return 0;
}

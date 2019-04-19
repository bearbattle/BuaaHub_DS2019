#include <ctype.h>
#include <stdio.h>
#include <string.h>

char key[110] = "completevictory";
char Open[1100], Encrypt[1100];
int t;

char g(char x)
{
    return (x & 1) == 1 ? (x % 26 - 1 + 'a') : (x % 26 + 1 + 'a');
}

char f(char src, char k)
{
    return (src + k - 2 * 'a') % 26 + 'a';
}

char f1(char src, char k)
{
    return (src - k + 52) % 26 + 'a';
}

void ResetKey()
{
    strcpy(key, "completevictory");
}

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
    int len = strlen(key);
    while (1)
    {
        ResetKey();
        memset(Encrypt, 0, sizeof(Encrypt));
        memset(Open, 0, sizeof(Open));
        gets(Open);
        for (i = 0; Open[i] != '\0'; i++)
        {
            if (i > 0 || i % len == 0)
            {
                ChangeKey();
            }
            Encrypt[i] = f1(g(f(Open[i], key[i % len])), key[i % len]);
        }
        puts(Encrypt);
    }
    return 0;
}
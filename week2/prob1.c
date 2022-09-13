#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#define BUFFER_SIZE 20

void check(char *str1, char *buffer_str);
int main()
{
    char word1[BUFFER_SIZE];
    char word2[BUFFER_SIZE];

    scanf("%s", &word1);
    scanf("%s", &word2);

    char newWord1[BUFFER_SIZE];
    char newWord2[BUFFER_SIZE];

    check(word1, newWord1);
    check(word2, newWord2);

    if (strlen(newWord1) != strlen(newWord2))
    {
        printf("no");
    }
    else
    {
        int cnt = 0;
        for (int i = 0; i < strlen(word1); i++)
        {
            for (int j = 0; j < strlen(word2); j++)
            {
                if (word1[i] == word2[j])
                {
                    cnt += 1;
                    break;
                }
            }
        }

        if (cnt == strlen(word1))
            printf("yes");
    }

    return 0;
}

void check(char *str1, char *buffer_str)
{

    buffer_str[0] = str1[0];
    bool isSame = false;

    for (int i = 1; i < strlen(str1); i++)
    {

        for (int j = 0; j < strlen(buffer_str); j++)
        {
            if (str1[i] == buffer_str[j])
            {
                isSame = true;
                break;
            }
        }
        if (isSame)
            isSame = false;
        else
        {
            buffer_str[strlen(buffer_str)] = str1[i];
            isSame = false;
        }
    }
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int *CompteLignes(char *filename, int *n)
{
    // ouvre fichier
    FILE *fp = NULL;
    fp = fopen(filename, "r");

    if (fp == NULL)
    {
//        printf("Error: %d (%s)\n", errno, strerror(errno));
        return NULL;
    }

    // compte les lignes
    int line_count = 0;
    int ch;
    while (!feof(fp))
    {
        ch = fgetc(fp);
        if (ch == '\n')
        {
            line_count++;
        }
    }
    // ferme fichier
    fclose(fp);

    // créé le tableau de resultats de taille (nb_lignes)
    int *res = NULL;
    res = (int *) malloc(sizeof(int) * line_count);
    if (res == NULL)
    {
        printf("malloc error\n");
        return NULL;
    }

    // ouvre fichier à nouveau (curseur se place au début)
    fp = NULL;
    fp = fopen(filename, "r");

    if (fp == NULL)
    {
//        printf("Error: %d (%s)\n", errno, strerror(errno));
        return NULL;
    }

    // compte les caracteres et enregistre les positions des '\n'
    int char_count = 0;
    int i          = 0;
    while (!feof(fp))
    {
        ch = fgetc(fp);
        if (ch == '\n')
        {
            res[i] = char_count;
            i++;
        }
        char_count++;
    }
    // ferme fichier
    fclose(fp);

    *n = line_count;
    return res;
}


int main()
{
    printf("######## 2)\n");

    int n;

    char *path = "D:\\Docs\\Dev\\ProgC_mock_1\\files\\testfile.txt";
    printf("reading from %s\n", path);
    int *test3 = CompteLignes(path, &n); // pas probleme
    if (test3 == NULL)
    {
        printf("probleme\n");
    } else
    {
        for (int i = 0; i < n; ++i)
        {
            printf("position of '\\n' #%d: %d\n", i + 1, test3[i]);
        }
    }

    //TODO ajoute ton propre path pour tester
    path = "azefyug uioaz fguyiaz";
    printf("reading from %s\n", path);
    int *test4 = CompteLignes(path, &n); // probleme
    if (test4 == NULL)
    {
        printf("probleme\n");
    } else
    {
        for (int i = 0; i < n; ++i)
        {
            printf("position of '\\n' #%d: %d\n", i + 1, test4[i]);
        }
    }
    return 0;
}
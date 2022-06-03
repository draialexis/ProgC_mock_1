#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct C1
{
    float     r;
    float     i;
    short int k;
};

void LibereT(struct C1 **T, int n)
{
    for (int i = 0; i < n; i++)
    {
        if (T[i] != NULL)
        {
            free(T[i]);
        }
    }
    free(T);
}


struct C1 **CreerT(int n, int m)
{
    // on déclare, initialise, vérifie
    struct C1 **res = NULL;
    res = (struct C1 **) malloc(sizeof(struct C1 *) * n);
    if (res == NULL)
    {
        printf("malloc error\n");
        return NULL;
    }
    int       error   = 0;
    short int counter = 1;

    for (int i = 0; i < n; i++)
    {
        res[i] = NULL;
        res[i] = (struct C1 *) malloc(sizeof(struct C1) * m);
        if (res[i] == NULL)
        {
            error = 1;
        } else
        {
            for (int j = 0; j < m; j++)
            {
                res[i][j].r = (float) i;
                res[i][j].i = (float) j;
                res[i][j].k = counter++;
            }
        }
    }
    if (error != 0)
    {
        printf("malloc error\n");
        LibereT(res, n);
        return NULL;
    }
    return res;
}

struct C1 **CreerU(struct C1 **T, int n)
{
    int n_u;
    if (n % 2 == 0)
    {
        n_u = n / 2;
    } else
    {
        n_u = (n / 2) + 1;
    }
    // on déclare, initialise, vérifie
    struct C1 **res = NULL;
    res = (struct C1 **) malloc(sizeof(struct C1 *) * n_u);
    if (res == NULL)
    {
        printf("malloc error\n");
        return NULL;
    }


    for (int i = 0; i < n; i++)
    {
        if (i % 2 == 0)
        {
            res[i / 2] = T[i];
        } else
        {
            // on ne veut pas libérer les lignes dont on va se servir avec U...
            if (T[i] != NULL)
            {
                free(T[i]);
            }
        }
    }
    free(T);

    return res;
}

int *CompteLignes(char *filename, int *n)
{
    // ouvre fichier
    FILE *fp = NULL;
    fp = fopen(filename, "r");

    if (fp == NULL)
    {
        printf("Error: %d (%s)\n", errno, strerror(errno));
        return NULL;
    }

    // compte les lignes
    int line_count = 1;
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
        printf("Error: %d (%s)\n", errno, strerror(errno));
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

    *n = line_count - 1;
    return res;
}

int main()
{
    struct C1 *ex;
    printf("\n######## 1.1)\n");
    printf("size of r = %llu\n", sizeof(ex->r));
    printf("size of i = %llu\n", sizeof(ex->i));
    printf("size of k = %llu\n", sizeof(ex->k));

    /*
     * taille d'un int ou d'un float pour les compilateurs 32 bits  : 1 mot, 4 octets
     * taille d'un short int pour les compilateurs 32 bits          : 1/2 mot, 2 octets
     */

    printf("\n######## 1.2)\n");
    printf("size of struct C1 = %llu\n", sizeof(struct C1));
    printf("(sizeof(struct C1) mod 4 = %llu)\n", sizeof(struct C1) % 4);

    /*
     * taille d'une struct = taille de la somme de ses éléments individuels,
     * + eventuellement les octets pour l'alignement
     *
     * en effet, la taille de deux structs aux attributs identiques peut changer si leurs attributs sont
     * ordonnés différemment
     *
     * sur compilateur 32bit (taille d'un "mot" = 32 / 8 = 4 octets)
     * {
     * char a// ...
     * char b// ...
     * char c// -> 1 + 1 + 1 + padding ==> 4 octets
     * int  x// -> 4 octets
     * char d// -> 1 + padding ==> 4 octets
     * }
     * ==> 12 octets
     *
     * {
     * char a// ...
     * char b// ...
     * char c// ...
     * char d// -> 1 + 1 + 1 + 1 ==> 4 octets
     * int  x// -> 4 octets
     * }
     * ==> 8 octets
     *
     */

    printf("\n######## 1.3)\n");
    struct C1 **test1 = NULL;
    int       n       = 3;
    int       m       = 2;
    printf("%d lignes, %d colonnes\n", n, m);
    test1 = CreerT(n, m);
    if (test1 == NULL)
    {
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            printf("[%d, %d]: r=%f, i=%f, k=%d\n", i, j, test1[i][j].r, test1[i][j].i, test1[i][j].k);
        }
    }

    printf("\n######## 1.4)\n");
    printf("10 * 12 * 12 = %d octets\n", 10 * 12 * 12);
    printf(" + pointeurs vers chaque ligne : 10 * 8 = %d octets\n", 10 * 8);
    printf(" + pointeur vers matrice : 8 octets\n");
    printf("TOTAL = %d\n", (10 * 12 * 12) + (10 * 8) + 8);

    /*
     * on réserve 12 octets par struct C1, soit 10*12*12 octets, soit 1440 octets
     *
     * mais on retourne un pointeur vers un pointeur vers un struct C1,
     * et la taille d'un pointeur est toujours de 2 mots, soit 8 octets sur un compilateur 32bit,
     * donc l'élément retourné est de 8 octets
     */
    printf("\n######## 1.5)\n");


    struct C1 **test2 = NULL;
    printf("1 ligne sur 2\n");

    int n_u;
    if (n % 2 == 0)
    {
        n_u = n / 2;
    } else
    {
        n_u = (n / 2) + 1;
    }

    test2 = CreerU(test1, n);
    for (int i = 0; i < n_u; i++)
    {
        for (int j = 0; j < m; j++)
        {
            printf("[%d, %d]: r=%f, i=%f, k=%d\n", i, j, test2[i][j].r, test2[i][j].i, test2[i][j].k);
        }
    }

    printf("\n######## 1.6)\n");
    printf("memory deallocated...\n");


    printf("\n################################\n");
    printf("######## 2)\n");


    int *test3 = CompteLignes("D:\\Docs\\Dev\\ProgC_mock_1\\files\\testfile.txt", &n); // pas probleme
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

    int *test4 = CompteLignes("D:\\Docs\\Dev\\ProgC_mock_1\\files\\testdfile.txt", &n); // probleme
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

    //TODO this
    printf("\n################################\n");
    printf("######## 3)\n");
    printf("a faire...\n");

    return 0;
}

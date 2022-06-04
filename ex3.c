#include <stdio.h>
#include <stdlib.h>
// http://www.mathcs.emory.edu/~cheung/Courses/255/Syllabus/1-C-intro/bit-array.html

int *CreerTB(int n) // 33
{
    int ints_needed;
    if (n % 32 == 0)
    {
        ints_needed = n / 32;
    } else // 1+
    {
        ints_needed = (n / 32) + 1;
    }

    int *res = (int *) malloc(sizeof(int) * ints_needed);

    for (int i = 0; i < ints_needed; ++i)
    {
        res[i] = 0;
    }
    return res;
}

void setBit(int *T, int i)
{
    int int_idx = i / 32; // index in ints_array
    int pos     = i % 32; // bit position in ints_array[i]

    unsigned int flag = 1;

    flag = flag << pos; // shift to the left ('pos' times)

    T[int_idx] = T[int_idx] | flag;
    // if all elements were initialized to 0, this sets the bit to 1
}

int getBit(int *T, int i)
{
    int int_idx = i / 32;
    int pos     = i % 32;

    unsigned int flag = 1;

    flag = flag << pos;

    if (T[int_idx] & flag)
    {
        return 1;
    } else
    {
        return 0;
    }
}

void LibereTB(int *T)
{
    free(T);
}

int main()
{
    printf("######## 3)\n");
    /*
     * c'est un tableau d'entiers
     * on dispose alors de 32 bits pour chaque 1 élément du tableau.
     */
    int TB_size    = 4;
    int bit_number = 15;
    int *T         = CreerTB(TB_size);
    printf("bit %d = %d\n", bit_number, getBit(T, bit_number));// 0
    setBit(T, bit_number);
    printf("bit %d = %d\n", bit_number, getBit(T, bit_number));// 1
    LibereTB(T);
    return 0;
}

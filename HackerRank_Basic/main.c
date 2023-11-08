#include <assert.h>
#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* readline();
char* ltrim(char*);
char* rtrim(char*);

int parse_int(char*);

/*
 * Complete the 'bigSorting' function below.
 *
 * The function is expected to return a STRING_ARRAY.
 * The function accepts STRING_ARRAY unsorted as parameter.
 */

 /*
  * To return the string array from the function, you should:
  *     - Store the size of the array to be returned in the result_count variable
  *     - Allocate the array statically or dynamically
  *
  * For example,
  * char** return_string_array_using_static_allocation(int* result_count) {
  *     *result_count = 5;
  *
  *     static char* a[5] = {"static", "allocation", "of", "string", "array"};
  *
  *     return a;
  * }
  *
  * char** return_string_array_using_dynamic_allocation(int* result_count) {
  *     *result_count = 5;
  *
  *     char** a = malloc(5 * sizeof(char*));
  *
  *     for (int i = 0; i < 5; i++) {
  *         *(a + i) = malloc(20 * sizeof(char));
  *     }
  *
  *     *(a + 0) = "dynamic";
  *     *(a + 1) = "allocation";
  *     *(a + 2) = "of";
  *     *(a + 3) = "string";
  *     *(a + 4) = "array";
  *
  *     return a;
  * }
  *
  */
char** bigSorting(int unsorted_count, char** unsorted, int* result_count) {

    *result_count = unsorted_count;

    int subArrSize = 1;
    char** arr_t = (char**)malloc(unsorted_count * sizeof(char*));
    for (int i = 0; i < unsorted_count; i++)
        arr_t[i] = (char*)malloc(1000000 * sizeof(char));

    for (int p = 0; p < ceil(log2(unsorted_count)); p++)
    {
        subArrSize *= 2;
        for (int n = 0; n < unsorted_count; n += subArrSize)
        {
            int i = n, k = n;
            int upperB = n + subArrSize;
            int midP = (upperB + n) / 2;
            int j = midP;

            int i_old = i - 1, j_old = j - 1;
            int str1Len = 0, str2Len = 0;
            //merge two halves of the subArr in arr_t
            while (i < fmin(unsorted_count, midP) && j < fmin(unsorted_count, upperB))
            {
                //preprocess str for comparison if i or j are updated
                if (i != i_old)
                {
                    i_old = i;
                    str1Len = 0;
                    str1Len = strlen(unsorted[i]);

                    //printf("debugging/i changed\n");//debugging
                }
                if (j != j_old)
                {
                    j_old = j;
                    str2Len = 0;
                    str2Len = strlen(unsorted[j]);

                    // printf("debugging/j changed\n");//debugging
                }


                if (str1Len == str2Len) //same number of digits
                {
                    int c = 0;
                    while (unsorted[i][c] != '\0' && unsorted[j][c] != '\0')
                    {
                        //compare most significant digit
                        if (unsorted[i][c] < unsorted[j][c])
                        {
                            arr_t[k++] = unsorted[i++];
                            break;
                        }
                        else if (unsorted[i][c] > unsorted[j][c])
                        {
                            arr_t[k++] = unsorted[j++];
                            break;
                        }
                        else {
                            c++;
                        }

                    }
                    //if the two numbers are of same len and equal take the first number
                    if (c == str1Len)
                        arr_t[k++] = unsorted[i++];

                }
                else if (str1Len < str2Len)
                {
                    arr_t[k++] = unsorted[i++];
                }
                else {
                    arr_t[k++] = unsorted[j++];
                }

            }

            //merge the rest of either halves in arr_t
            for (; i < fmin(unsorted_count, midP); i++)
                arr_t[k++] = unsorted[i];
            for (; j < fmin(unsorted_count, upperB); j++)
                arr_t[k++] = unsorted[j];

            //copy merged array from arr_t to unsorted
            for (int i = n; i < fmin(upperB, unsorted_count); i++)
                unsorted[i] = arr_t[i];


            //debugging purpose code
            /*
            printf("debugging/loop%d\n",p);
            printf("str1Len = %d  str2Len = %d\n",str1Len,str2Len);
            for (int di = 0; di<unsorted_count; di++) {
           printf("%s\n",unsorted[di]);
            }
            */
            //debugging purpose code
        }
    }


    for (int i = 0; i < unsorted_count; i++)
        arr_t[i] = unsorted[i];
    return arr_t;
}

int main()
{
    FILE* fptr = fopen("test case.txt", "r");

    char listSize[100000];
    fscanf(fptr, "%s\n", listSize);
    char* t;
    int listSize_n = strtol(listSize,&t,10);
    char** unsorted = (char**)malloc(listSize_n * sizeof(char*));



    for (int i = 0; i < listSize_n; i++) {
        unsorted[i] = (char*)malloc(1000000 * sizeof(char));

        fscanf(fptr, "%s\n", unsorted[i]);
    }

    int result_count;
    char** result = bigSorting(listSize_n, unsorted, &result_count);

    for (int i = 0; i < result_count; i++) {
        printf("%s", *(result + i));

        if (i != result_count - 1) {
            printf("\n");
        }
    }

    char userEnter;
    scanf("%c", &userEnter);

    for (int i = 0; i < listSize_n; i++)
        free(unsorted[i]);
    free(unsorted);
    fclose(fptr);

    return 0;
}


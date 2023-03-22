#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>



void addVar (char **varList, char *var, int *varCount){
    *(varList+*varCount) = var;
    (*varCount)++;
}

int search(char **varList, char *var, int varCount){
    for (int i = 0; i < varCount; i++)
    {
        if (strcmp(*(varList+i), var) == 0){
            return i;
        }
    }
    return -1;
}


#include <stdio.h>
#include <stdlib.h>

#include "Sort.h"

void sort(int *array, int size);


//DO NOT MODIFY !!
//main() creates an array of ints from stdin, then passes the array along
//with its last index to the function sort().
int main() {

    //Create array

    int size_array = 1;
    int *array = calloc(size_array, sizeof(int));
    int count = 0;
    int value;

    //Read stdin to array.
    //Ctrl + D to end input.
    while (scanf("%d", &value) == 1) {
        //If number of ints > size of array, resize array
        if (count == size_array) {
            array = realloc(array, (size_array + 1) *sizeof(int));
            size_array++;
        }

        array[count] = value;
        count++;
    }

    //Check for valid input

    if (count == 0) {
        printf("error: No input detected\n");
        return 1;
    }

    //Sort array

    sort(array, count);

    //Print elements in array

    for (int i = 0; i < count; i++) {
        printf("%d ", array[i]);
    }

    printf("\n");

    free(array);
    return 0;


}

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include <time.h>

#define CAPACITY 10000
static int arr[CAPACITY];

void swap(int *a, int *b) 
{
    int t = *a;
    *a = *b;
    *b = t;
}

int compare(const void *a, const void *b) 
{
    return (*(int*)a - *(int*)b);
}

void quick_sort(int *a, size_t capacity) 
{
    qsort(a, capacity, sizeof(int), compare);
}

void merge(int a[], int beg, int mid, int end)    
{    
    int i, j, k;  
    int n1 = mid - beg + 1;    
    int n2 = end - mid;    
      
    int *left_array = malloc(sizeof(int) * n1);
    int *right_array = malloc(sizeof(int) * n2);
      
    for (int i = 0; i < n1; i++)    
        left_array[i] = a[beg + i];    
    for (int j = 0; j < n2; j++)    
        right_array[j] = a[mid + 1 + j];    
      
    i = 0;     
    j = 0; 
    k = beg;
      
    while (i < n1 && j < n2) {    
        if(left_array[i] <= right_array[j]) {    
            a[k] = left_array[i];    
            i++;    
        }    
        else {    
            a[k] = right_array[j];    
            j++;    
        }    
        k++;    
    }    

    while (i<n1) {    
        a[k] = left_array[i];    
        i++;    
        k++;    
    }    
      
    while (j<n2) {    
        a[k] = right_array[j];    
        j++;    
        k++;    
    }    

    free(left_array);
    free(right_array);
}    
  
void merge_sort_recursion(int a[], int beg, int end)  
{  
    if (beg < end)   
    {  
        int mid = (beg + end) / 2;  
        merge_sort_recursion(a, beg, mid);  
        merge_sort_recursion(a, mid + 1, end);  
        merge(a, beg, mid, end);  
    }  
}  
  

void merge_sort(int a[], size_t capacity) 
{
    merge_sort_recursion(a, 0, capacity - 1);
}

void insertion_sort(int *arr, size_t capacity)
{
    for (size_t i = 1; i < capacity; ++i) {
        int key = arr[i];
        int j = (int)i - 1;
        for (; j >= 0 && arr[j] > key; --j) {
            arr[j + 1] = arr[j];
        }
        arr[j + 1] = key;
    }
}
 
void selection_sort(int *arr, size_t capacity) 
{
    for (size_t i = 0; i < capacity; ++i) {
        int *min = &arr[i];
        for (size_t j = i; j < capacity; ++j) {
            if (arr[j] < *min) {
            min = &arr[j];
            }
        }
        if (*min != arr[i]) {
            swap(&arr[i], min);
        }
    }
}

void bubblesort(int *arr, size_t capacity) 
{
    for (size_t i = capacity - 1; i > 1; --i)
        for (size_t j = 0; j < i; ++j)
            if (arr[j] > arr[j+1])
                swap(&arr[j], &arr[j+1]);
}

void poppulate_arr(int *arr, size_t capacity) 
{
    for(size_t i = 0; i < capacity; ++i) {
        arr[i] = rand()%capacity;
    }
}

bool is_ordered(int *arr, size_t capacity) 
{
    for (size_t i = 0; i < capacity - 1; ++i) {
        if (arr[i] > arr[i + 1]) return false;
    }
    return true;
}

void print_result(int *arr, size_t capacity) 
{
    printf("{");
    for (size_t i = 0; i < capacity; ++i) {
        printf(" %d ", arr[i]);
    }
    printf("}");
}

void benchmark(void (*algo)(int *, size_t), int* arr, size_t capacity) 
{
    float start = (float) clock()/CLOCKS_PER_SEC;
    (*algo)(arr, capacity);
    float end = (float) clock()/CLOCKS_PER_SEC;

    printf("INFO: Elapsed time: %fs\n", end - start);
    printf("INFO: The array is now ordered: %s", is_ordered(arr, capacity) ? "True" : "False");
    // print_result(arr, capacity);
}

void usage(char *program) 
{
    printf("USAGE: %s <algorithm>\n", program);
    printf("ALGORITHMS: \n");
    printf("            bubblesort\n");
    printf("            selectionsort\n");
    printf("            insertionsort\n");
    printf("            mergesort\n");
    printf("            quicksort\n");
}

int main(int argc, char **argv)  
{
    (void)argc;
    char *program = *argv++;
    assert(program != NULL && "Program should be provided.\n");

    char *algo = *argv++;
    if (algo == NULL) {
        usage(program);
        return 1;
    }

    poppulate_arr(arr, CAPACITY);



    if (strcmp("bubblesort", algo) == 0) {
        benchmark(bubblesort, arr, CAPACITY);
    } else if (strcmp("insertionsort", algo) == 0) {
        benchmark(insertion_sort, arr, CAPACITY);
    } else if (strcmp("selectionsort", algo) == 0) {
        benchmark(selection_sort, arr, CAPACITY);
    } else if (strcmp("mergesort", algo) == 0) {
        benchmark(merge_sort, arr, CAPACITY);
    } else if (strcmp("quicksort", algo) == 0) {
        benchmark(quick_sort, arr, CAPACITY);
    }
    else {
        printf("ERROR: Invalid command: %s\n", algo);
        usage(program);
    }
}

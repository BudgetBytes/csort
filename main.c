#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include <time.h>

void swap(int *a, int *b) {
  int t = *a;
  *a = *b;
  *b = t;
}


// Merge sort is copied from here
// https://github.com/portfoliocourses/c-example-code/blob/main/merge_sort.c
void merge_sorted_arrays(int a[], size_t l, size_t m, size_t r)
{
  size_t left_length = m - l + 1;
  size_t right_length = r - m;
  
  size_t temp_left[left_length];
  size_t temp_right[right_length];
  
  size_t i, j, k;
  
  for (size_t i = 0; i < left_length; i++)
    temp_left[i] = a[l + i];
  
  for (size_t i = 0; i < right_length; i++)
    temp_right[i] = a[m + 1 + i];
  
  for (i = 0, j = 0, k = l; k <= r; k++) {
    if ((i < left_length) && (j >= right_length || temp_left[i] <= temp_right[j])) {
      a[k] = temp_left[i];
      i++;
    }
    else {
      a[k] = temp_right[j];
      j++;
    }
  }  
}


void merge_sort_recursion(int a[], size_t l, size_t r)
{
  if (l < r) {
    size_t m = l + (r - l) / 2;
  
    merge_sort_recursion(a, l, m);
    merge_sort_recursion(a, m + 1, r);
    merge_sorted_arrays(a, l, m, r);
  }
}

void merge_sort(int a[], size_t length) 
{
  merge_sort_recursion(a, 0, length - 1);
}


void insertion_sort(int *arr, size_t capacity) {
  for (size_t i = 0; i < capacity - 1; ++i){
    if (arr[i] > arr[i+1]) {
      swap(&arr[i], &arr[i+1]);
      for (size_t j = i; j > 0 && arr[j] < arr[j-1]; --j) {  
        swap(&arr[j], &arr[j - 1]);
      }
    }
  }
}

void selection_sort(int *arr, size_t capacity) {
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

void bubblesort(int *arr, size_t capacity) {
  for (size_t i = capacity - 1; i > 1; --i)
    for (size_t j = 0; j < i; ++j)
      if (arr[j] > arr[j+1])
        swap(&arr[j], &arr[j+1]);
}

int compare(const void *a, const void *b) {
   return (*(int*)a - *(int*)b);
}

void poppulate_arr(int *arr, size_t capacity) {
  for(size_t i = 0; i < capacity; ++i) {
    arr[i] = rand()%100;
  }
}

bool is_ordered(int *arr, size_t capacity) {
  for (size_t i = 0; i < capacity - 1; ++i) {
    if (arr[i] > arr[i + 1]) return false;
  }
  return true;
}

void print_result(int *arr, size_t capacity) {
  printf("{");
  for (size_t i = 0; i < capacity; ++i) {
    printf(" %d ", arr[i]);
  }
  printf("}");
}

void benchmark(void (*algo)(int *, size_t), int* arr, size_t capacity) {
  float start = (float) clock()/CLOCKS_PER_SEC;
  (*algo)(arr, capacity);
  float end = (float) clock()/CLOCKS_PER_SEC;

  printf("INFO: Elapsed time: %fs\n", end - start);
  printf("INFO: The array is now ordered: %s", is_ordered(arr, capacity) ? "True" : "False");
  // print_result(arr, capacity);
}

void usage(char *program) {
  printf("USAGE: %s <algorithm>\n", program);
  printf("ALGORITHMS: \n");
  printf("  quicksort\n");
  printf("  bubblesort\n");
}

int main(int argc, char **argv)  {
  (void)argc;
  char *program = *argv++;
  assert(program != NULL && "Program should be provided.\n");

  char *algo = *argv++;
  if (algo == NULL) {
    usage(program);
    return 1;
  }
    
  size_t capacity = 10000;
  int arr[capacity];
  poppulate_arr(arr, capacity);

  if (strcmp("quicksort", algo) == 0) {
    printf("TODO: Not implemented");
  } else if (strcmp("bubblesort", algo) == 0) {
    benchmark(bubblesort, arr, capacity);
  } else if (strcmp("selectionsort", algo) == 0) {
    benchmark(selection_sort, arr, capacity);
  } else if (strcmp("insertionsort", algo) == 0) {
    benchmark(insertion_sort, arr, capacity);
  } else if (strcmp("mergesort", algo) == 0) {
    benchmark(merge_sort, arr, capacity);
  }

  else {
    printf("ERROR: Invalid command: %s\n", algo);
    usage(program);
  }
}

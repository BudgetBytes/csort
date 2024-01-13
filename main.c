#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include <time.h>

void usage(char *program) {
  printf("USAGE: %s <algorythm>\n", program);
  printf("ALGORYTHMS: \n");
  printf("  quicksort\n");
  printf("  bubblesort\n");
}



bool is_ordered(int *arr, size_t capacity) {
  for (size_t i = 0; i < capacity - 1; ++i) {
    if (arr[i] > arr[i + 1]) return false;
  }
  return true;
}

void print_result(int *arr, size_t capacity) {
  printf("{ ");
  for (size_t i = 0; i < capacity; ++i) {
    printf("%d ", arr[i]);
  }
  printf("}");
}

void poppulate_arr(int *arr, size_t capacity) {
  for (size_t i = 0; i < capacity; ++i) {
    arr[i] = rand()%100;
  }

}

void swap(int *a, int *b) {
  int t = *a;
  *a = *b;
  *b = t;
}

void bubblesort(int *arr, size_t capacity) {
  
  for (size_t i = 0; i < capacity - 1; ++i) {
    int *curr = &arr[i];
    int *next = &arr[i+1];
    if (*curr > *next) 
      swap(curr, next);
  }
  if (!is_ordered(arr, capacity)) bubblesort(arr, capacity);
  
}

int main(int argc, char **argv)  {
  (void)argc;
  char *program = *argv++;
  assert(program != NULL && "Program should be provided.\n");

  char *alg = *argv++;
  if (alg == NULL) {
    usage(program);
    return 1;
  }

  size_t capacity = 1000;
  int arr[capacity];
  poppulate_arr(arr, capacity);

  if (strcmp("quicksort", alg) == 0) {
    
  } else if (strcmp("bubblesort", alg) == 0) {
    float start = (float) clock()/CLOCKS_PER_SEC;
    bubblesort(arr, capacity);
    float end = (float) clock()/CLOCKS_PER_SEC;
    printf("INFO: Elapsed time: %fs\n", end - start);
    print_result(arr, capacity);
    
  } else {
    printf("ERROR: Invalid command: %s\n", alg);
    usage(program);
  }


}

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <raylib.h>

#define WIDTH 1000
#define HEIGHT 800
#define FPS 60
#define RECT_DIM 5
#define MAX_ELEMENTS 100



void swap(int *a, int *b) 
{
    int t = *a;
    *a = *b;
    *b = t;
}

bool is_ordered(int *arr, size_t capacity) 
{
    for (size_t i = 0; i < capacity - 1; ++i) {
        if (arr[i] > arr[i + 1]) return false;
    }
    return true;
}


void redraw(int *a, size_t size) {
    int width = GetScreenWidth();
    int height = GetScreenHeight();

    int startX = (width - size * RECT_DIM) / 2;
    int startY = (height - size * RECT_DIM) / 2;

    if (is_ordered(a, size)) {
        for (size_t i = 0; i < size; ++i) {
            DrawRectangle(startX + i * RECT_DIM, height - startY - a[i] * RECT_DIM, RECT_DIM - 1, a[i] * RECT_DIM, LIME);
        }
    }else {
        for (size_t i = 0; i < size; ++i) {
            DrawRectangle(startX + i * RECT_DIM, height - startY - a[i] * RECT_DIM, RECT_DIM - 1, a[i] * RECT_DIM, RAYWHITE);
        }
    }

}


void bubblesort(int *arr, size_t capacity) 
{
    for (size_t i = capacity - 1; i > 1; --i) {
        for (size_t j = 0; j < i; ++j){
            if (arr[j] > arr[j+1]) {
                swap(&arr[j], &arr[j+1]);
                return;
            }
        }
    }
}


void populate_a(int *a, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        a[i] = rand() % size;
    }
}

int main(void) {
        
    int *a = malloc(MAX_ELEMENTS * sizeof(int));
    assert(a != NULL && "Malloc never fails...");
    populate_a(a, MAX_ELEMENTS);

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(WIDTH,  HEIGHT, "Algorithms and Data Structures Visualization");
    SetTargetFPS(FPS);
    while(!WindowShouldClose()) {
        
        BeginDrawing();
        {
            ClearBackground(BLACK);
            
            bubblesort(a, MAX_ELEMENTS);
            redraw(a, MAX_ELEMENTS);
           
        }
        EndDrawing();
    }
    CloseWindow();
    return 0;

    
}

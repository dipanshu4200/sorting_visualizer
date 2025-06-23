// Sorting Visualizer using Raylib in C++
// Includes: Bubble Sort, Selection Sort, Insertion Sort, Quick Sort
// Use keyboard keys to switch algorithms

#include "raylib.h"
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <stack>
#include <string>

const int screenWidth = 1000;
const int screenHeight = 800;
const int numElements = 100;
std::vector<int> values(numElements);

enum SortType { BUBBLE, SELECTION, INSERTION, QUICK };
SortType currentSort = SELECTION;

int i = 0, j = 0, minIndex = 0;
bool sorted = false;
bool processing = false;

struct StackFrame {
    int low, high;
};
std::vector<StackFrame> stack;
int pivot = -1, l = -1, r = -1;

void drawBars(const std::vector<int>& arr, int highlight1 = -1, int highlight2 = -1) {
    int barWidth = screenWidth / numElements;
    for (int i = 0; i < arr.size(); i++) {
        int height = arr[i];
        Color color = GREEN;
        if (i == highlight1 || i == highlight2) color = RAYWHITE;
        DrawRectangle(i * barWidth, screenHeight - height, barWidth - 1, height, color);
    }
}

void resetArray() {
    for (int i = 0; i < numElements; i++) {
        values[i] = GetRandomValue(50, screenHeight - 20);
    }
    i = j = 0; minIndex = 0;
    sorted = false; processing = false;
    stack.clear();
    if (currentSort == QUICK) stack.push_back({ 0, numElements - 1 });
}

void bubbleSortStep() {
    if (i < numElements - 1) {
        if (j < numElements - i - 1) {
            if (values[j] > values[j + 1]) {
                std::swap(values[j], values[j + 1]);
            }
            drawBars(values, j, j + 1);
            j++;
        }
        else {
            j = 0;
            i++;
        }
    }
    else {
        sorted = true;
    }
}

void selectionSortStep() {
    if (i < numElements - 1) {
        minIndex = i;
        for (j = i + 1; j < numElements; j++) {
            if (values[j] < values[minIndex]) {
                minIndex = j;
            }
        }
        std::swap(values[i], values[minIndex]);
        drawBars(values, i, minIndex);
        i++;
    }
    else {
        sorted = true;
    }
}

void insertionSortStep() {
    if (i < numElements) {
        int key = values[i];
        j = i - 1;
        while (j >= 0 && values[j] > key) {
            values[j + 1] = values[j];
            drawBars(values, j, j + 1);
            j--;
        }
        values[j + 1] = key;
        drawBars(values, i, j + 1);
        i++;
    }
    else {
        sorted = true;
    }
}

void quickSortStep() {
    if (!processing && !stack.empty()) {
        StackFrame f = stack.back();
        stack.pop_back();
        pivot = values[f.high];
        l = f.low - 1;
        for (int j = f.low; j <= f.high - 1; j++) {
            if (values[j] < pivot) {
                l++;
                std::swap(values[l], values[j]);
            }
        }
        std::swap(values[l + 1], values[f.high]);
        int pi = l + 1;
        if (pi - 1 > f.low) stack.push_back({ f.low, pi - 1 });
        if (pi + 1 < f.high) stack.push_back({ pi + 1, f.high });
        processing = true;
    }
    else {
        processing = false;
    }
    drawBars(values,l,j);
}

int main() {
    InitWindow(screenWidth, screenHeight, "Sorting Visualizer");
    SetTargetFPS(60);
    srand(time(NULL));
    resetArray();

    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_R)) resetArray();
        if (IsKeyPressed(KEY_ONE)) { 
            currentSort = BUBBLE; 
            resetArray();
        }
        if (IsKeyPressed(KEY_TWO)) { 
            currentSort = SELECTION; 
            resetArray(); 
        }
        if (IsKeyPressed(KEY_THREE)) { 
            currentSort = INSERTION; 
            resetArray(); 
        }
        if (IsKeyPressed(KEY_FOUR)) { 
            currentSort = QUICK; 
            resetArray(); 
        }

        BeginDrawing();
        ClearBackground(BLACK);

        if (!sorted) {
            switch (currentSort) {
            case BUBBLE: bubbleSortStep(); break;
            case SELECTION: selectionSortStep(); break;
            case INSERTION: insertionSortStep(); break;
            case QUICK:
                if (!stack.empty()) quickSortStep();
                else sorted = true;
                break;
            }
        }
        else {
            drawBars(values);
            DrawText("Sorting Complete! Press R to reset.", 0, 25, 22, GREEN);
        }

        DrawText("1: Bubble | 2: Selection | 3: Insertion | 4: Quick | R: Reset", 0, 0, 25, WHITE);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}

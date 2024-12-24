#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

// Define constants for the screen width and height
#define WIDTH 20
#define HEIGHT 17

// Define key directions
#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4

// Declare global variables
int gameOver, score, x, y, fruitX, fruitY, dir;
int tailX[100], tailY[100];  // Array to store the snake's tail coordinates
int nTail; // Number of tail segments

void setup() {
    gameOver = 0;
    dir = RIGHT; // Snake starts moving to the right
    x = WIDTH / 2;
    y = HEIGHT / 2;
    fruitX = rand() % WIDTH;
    fruitY = rand() % HEIGHT;
    score = 0;
    nTail = 0;
}

void draw() {
    system("cls");  // Clears the console screen

    // Draw the top border
    for (int i = 0; i < WIDTH + 2; i++)
        printf("#");
    printf("\n");

    // Draw the game field
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (j == 0)
                printf("#"); // Left border
            if (i == y && j == x)
                printf("O"); // Snake head
            else if (i == fruitY && j == fruitX)
                printf("F"); // Fruit
            else {
                int isTail = 0;
                for (int k = 0; k < nTail; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        printf("o"); // Snake body
                        isTail = 1;
                    }
                }
                if (!isTail)
                    printf(" "); // Empty space
            }

            if (j == WIDTH - 1)
                printf("#"); // Right border
        }
        printf("\n");
    }

    // Draw the bottom border
    for (int i = 0; i < WIDTH + 2; i++)
        printf("#");
    printf("\n");

    // Print the score
    printf("Score: %d\n", score);
}

void input() {
    if (_kbhit()) {
        switch (_getch()) {
            case 'w': dir = UP; break;
            case 's': dir = DOWN; break;
            case 'a': dir = LEFT; break;
            case 'd': dir = RIGHT; break;
            case 'x': gameOver = 1; break;
        }
    }
}

void logic() {
    int prevX = tailX[0], prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;

    for (int i = 1; i < nTail; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (dir) {
        case UP: y--; break;
        case DOWN: y++; break;
        case LEFT: x--; break;
        case RIGHT: x++; break;
    }

    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
        gameOver = 1;

    for (int i = 0; i < nTail; i++) {
        if (tailX[i] == x && tailY[i] == y)
            gameOver = 1;
    }

    if (x == fruitX && y == fruitY) {
        score += 10;
        fruitX = rand() % WIDTH;
        fruitY = rand() % HEIGHT;
        nTail++; // Increase tail length
    }
}

void delay(int milliseconds) {
    Sleep(milliseconds);  // Sleep for the specified number of milliseconds
}

int main() {
    srand(time(0)); // Seed for random number generation

    setup();
    while (!gameOver) {
        draw();
        input();
        logic();
        delay(100); // Speed of the game (100ms)
    }

    return 0;
}


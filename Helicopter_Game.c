#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

#define SCREEN_WIDTH 50
#define SCREEN_HEIGHT 20
#define OBSTACLE_WIDTH 3

void displayScreen(char screen[SCREEN_HEIGHT][SCREEN_WIDTH], int score) {
    system("cls");
    for (int i = 0; i < SCREEN_HEIGHT; i++) {
        for (int j = 0; j < SCREEN_WIDTH; j++) {
            printf("%c", screen[i][j]);
        }
        printf("\n");
    }
    printf("\nScore: %d\n", score);
}

int main() {
    char screen[SCREEN_HEIGHT][SCREEN_WIDTH];
    int helicopterY = SCREEN_HEIGHT / 2;   // Helicopter's vertical position
    int obstacleX = SCREEN_WIDTH - 1;     // Obstacle's horizontal position
    int obstacleGapY;                     // Vertical position of the gap
    int score = 0;                        // Player's score
    int isRunning = 1;                    // Game state
    int gravity = 1;                      // Downward movement
    int ascend = 0;                       // Upward movement when space is pressed

    srand(time(0));

    // Main game loop
    while (isRunning) {
        // Initialize screen
        for (int i = 0; i < SCREEN_HEIGHT; i++) {
            for (int j = 0; j < SCREEN_WIDTH; j++) {
                screen[i][j] = ' ';
            }
        }

        // Place helicopter
        screen[helicopterY][1] = 'H';

        // Generate obstacle gap
        if (obstacleX == SCREEN_WIDTH - 1) {
            obstacleGapY = rand() % (SCREEN_HEIGHT - 6) + 3;
        }

        // Draw obstacle
        for (int i = 0; i < SCREEN_HEIGHT; i++) {
            if (i < obstacleGapY || i > obstacleGapY + 2) {
                if (obstacleX < SCREEN_WIDTH && obstacleX >= 0) {
                    screen[i][obstacleX] = '#';
                }
            }
        }

        // Display the screen
        displayScreen(screen, score);

        // Check for collision
        if (helicopterY <= 0 || helicopterY >= SCREEN_HEIGHT - 1 ||
            (obstacleX == 1 && (helicopterY < obstacleGapY || helicopterY > obstacleGapY + 2))) {
            isRunning = 0; // End the game
            break;
        }

        // Update positions
        obstacleX--;
        if (obstacleX < 0) {
            obstacleX = SCREEN_WIDTH - 1;
            score++;
        }

        // Gravity effect
        helicopterY += gravity;

        // Check for player input
        if (_kbhit()) {
            char input = _getch();
            if (input == ' ') {
                ascend = 2; // Helicopter moves up
            }
        }

        // Apply upward movement
        if (ascend > 0) {
            helicopterY -= ascend;
            ascend = 0;
        }

        // Delay for game speed
        _sleep(100);
    }

    // Game over screen
    system("cls");
    printf("GAME OVER!\n");
    printf("Final Score: %d\n", score);

    return 0;
}

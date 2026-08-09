#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define WIDTH 21
#define HEIGHT 21

// Grid representation: 1 = Wall (#), 0 = Path (Space)
int maze[HEIGHT][WIDTH];

void initialize_maze() {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            maze[y][x] = 1; // Start with everything solid
        }
    }
}

void print_maze() {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (maze[y][x] == 1) {
                printf("# "); // Wall
            } else {
                printf("  "); // Path
            }
        }
        printf("\n");
    }
}

// Check if a move is inside the boundaries
int is_valid(int x, int y) {
    return (x > 0 && x < WIDTH - 1 && y > 0 && y < HEIGHT - 1);
}

// Shuffle directions array randomly to ensure a unique maze layout
void shuffle_directions(int dirs[4][2]) {
    for (int i = 0; i < 4; i++) {
        int r = rand() % 4;
        int tempX = dirs[i][0];
        int tempY = dirs[i][1];
        dirs[i][0] = dirs[r][0];
        dirs[i][1] = dirs[r][1];
        dirs[r][0] = tempX;
        dirs[r][1] = tempY;
    }
}

void generate_maze(int x, int y) {
    maze[y][x] = 0; // Mark the current cell as a path

    // Up, Down, Left, Right movement offsets (moving 2 steps at a time)
    int dirs[4][2] = {{0, -2}, {0, 2}, {-2, 0}, {2, 0}};
    shuffle_directions(dirs);

    for (int i = 0; i < 4; i++) {
        int nx = x + dirs[i][0];
        int ny = y + dirs[i][1];

        // If the targeted 2-step cell is valid and still a wall
        if (is_valid(nx, ny) && maze[ny][nx] == 1) {
            // Knock down the wall between the current cell and the next cell
            maze[y + dirs[i][1] / 2][x + dirs[i][0] / 2] = 0;
            
            // Recursively move to the next cell
            generate_maze(nx, ny);
        }
    }
}

int main() {
    srand(time(NULL)); // Seed random number generator

    initialize_maze();
    
    // Start generating from an odd-indexed coordinate
    generate_maze(1, 1);
    
    // Create an entrance and exit
    maze[1][0] = 0; 
    maze[HEIGHT - 2][WIDTH - 1] = 0;

    print_maze();

    return 0;
}

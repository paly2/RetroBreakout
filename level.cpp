#include "level.h"

// variables
Brick level::bricks[30][20];
int level::brick_number = 0;
int level::level_number = 0;
SDL_Surface* level::screen = NULL;
Ball* level::ball = NULL;

// functions
void level::draw() {
    for(int i = 0 ; i < 30 ; i++)
        for(int j = 0 ; j < 20 ; j++)
            if(bricks[i][j].handle(brick_number))
                load(screen, ball, level_number+1);
}
void level::load(SDL_Surface *screen_, Ball *ball_, int Level_number) {
    screen = screen_;
    ball = ball_;
    brick_number = 0;

    level_number = Level_number;

    char file_path[15] = "levels/level", file_number[3] = "";
    sprintf(file_number, "%d", level_number);
    strcat(file_path, file_number);
    FILE* level_file = fopen(file_path, "r");
    if(level_file == NULL) {
        cout << "There are no additionnal levels." << endl;
        exit(0);
    }
    char line[21] = "";

    // Now, fill the bricks table
    int i, j;
    for(i = 0 ; i < 30 && fgets(line, 22, level_file) != NULL ; i++) {
        for(j = 0 ; j < 20 && line[j] != '\0'; j++) {
            if(line[j] == '\n')
                break;
            bricks[i][j].set_type(brick_type(line[j]));
            bricks[i][j].coords(i, j, screen, ball);
            if(line[j] >= '1' && line[j] <= '9') // Normal brick.
                brick_number++;
        }
        for(; j < 20 ; j++) {
            bricks[i][j].set_type(NONE);
            bricks[i][j].coords(i, j, screen, ball);
        }
    }
    for(; i < 30 ; i++) {
        for(j = 0 ; j < 20 ; j++) {
            bricks[i][j].set_type(NONE);
            bricks[i][j].coords(i, j, screen, ball);
        }
    }

    ball->run(false); // Run the ball

    draw(); // And draw the level

    fclose(level_file);
}

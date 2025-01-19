#include <iostream>
#include <conio.h>
#include <time.h>
#include <windows.h>
#include <sstream>
using namespace std;

typedef struct
{
    int x, y; // x and y coordinates of the obstacle
} Obstacle;

// Function prototypes
void initMap(string map[20][30], Obstacle Obs[3]);
void obstacleMove(string map[20][30], Obstacle Obs[3]);
void birdMove(string map[20][30], Obstacle Obs[3], int *x, bool *hp, int *score);
void render(string map[20][30], int score, int level, int speed[15]);
void setCursorPosition(int x, int y);

int main()
{
    srand(time(0));
    char repeat = 'y';
    int highscore = 0;

    while (repeat == 'y' || repeat == 'Y')
    {
        system("cls");
        bool hp = true;
        int x = 9, level = 0, score = 0;
        int speed[15] = {150, 145, 135, 130, 125, 120, 115, 110, 105, 100, 95, 90, 85, 80, 75};
        Obstacle Obs[3];
        string map[20][30];

        initMap(map, Obs); // Initialize the game map and obstacles

        while (hp)
        {
            obstacleMove(map, Obs);              // Move obstacles
            birdMove(map, Obs, &x, &hp, &score); // Move bird and check collisions
            render(map, score, level, speed);    // Display the updated map and score
            Sleep(speed[level]);
            if (score % 5 == 0 && score < 75)
            {
                level = score / 5;
            }
        }

        setCursorPosition(0, 21); // Move cursor to the bottom for messages
        cout << "Score = " << score << endl;
        if (highscore < score)
            highscore = score;
        cout << "Highscore = " << highscore << endl;
        cout << "retry?(y/n) = ";
        cin >> repeat;
    }
    return 0;
}

// Initialize the game map and obstacles
void initMap(string map[20][30], Obstacle Obs[3])
{
    Obs[0].x = 10;
    Obs[1].x = 18;
    Obs[2].x = 27;

    for (int i = 0; i < 3; i++)
        // Randomize vertical positions of the obstacles
        Obs[i].y = (rand() - 1) % 12 + 2;

    // Fill the map with boundaries and empty spaces
    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 30; j++)
        {
            if ((i == 19 && j == 0) || (j == 0 && i == 0))
                map[i][j] = "+-";
            else if ((i == 0 && j == 29) || (i == 19 && j == 29))
                map[i][j] = "+";
            else if (j == 29 || j == 0)
                map[i][j] = "| ";
            else if (i == 19 || i == 0)
                map[i][j] = "--";
            else
                map[i][j] = "  ";
        }
    }
}

// Move the obstacles on the map
void obstacleMove(string map[20][30], Obstacle Obs[3])
{
    // Clear the current obstacle positions on the map
    for (int i = 0; i < 3; i++)
    {
        for (int j = 1; j < 19; j++)
            map[j][Obs[i].x] = "  ";
    }

    // Move obstacles one step to the left
    for (int i = 0; i < 3; i++)
        Obs[i].x--;

    // Re-draw the obstacles on the map
    for (int i = 0; i < 3; i++)
    {
        for (int j = 1; j < 19; j++)
            map[j][Obs[i].x] = "| ";
    }

    // Clear spaces where obstacles should not appear
    for (int i = 0; i < 3; i++)
    {
        // map[Obs[i].y + 4][Obs[i].x] = "  ";
        for (int j = Obs[i].y; j < Obs[i].y + 5; j++)
        {
            map[j][Obs[i].x] = "  ";
        }
    }

    // Reset obstacles that move out of the map
    for (int i = 0; i < 3; i++)
    {
        if (Obs[i].x == 1)
        {
            for (int j = 1; j < 19; j++)
                map[j][Obs[i].x] = "  ";
            Obs[i].x = 28;
            Obs[i].y = (rand() - 1) % 12 + 2;
        }
    }
}

// Move the bird and handle collisions
void birdMove(string map[20][30], Obstacle Obs[3], int *x, bool *hp, int *score)
{
    char mv;
    map[*x][3] = "  "; // Clear current bird position

    if (kbhit())
    {
        mv = getch();
        *x = (*x) - 3; // Move bird up
    }
    (*x)++; // Gravity effect, bird moves down if no input

    if (*x < 1) // Prevent bird from going out of bounds
        *x = 1;

    // Check for collisions and score updates
    for (int i = 0; i < 3; i++)
    {
        if (Obs[i].x == 3)
            if (map[*x][3] == "  ")
                *score = (*score) + 1; // Increase score if bird passes obstacle
        if (map[*x][3] == "| ")
            *hp = false; // End game if bird hits an obstacle
    }

    map[*x][3] = "& "; // Update bird position on the map
}

// Render the map and score
void render(string map[20][30], int score, int level, int speed[15])
{
    stringstream buffer;
    if (level == 15)
        buffer << "----------------------- Max Level -------------------------" << endl;
    else
        buffer << "------------------------ Level " << level + 1 << " --------------------------" << endl;

    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 30; j++)
            buffer << map[i][j];
        buffer << "\n";
    }
    buffer << "Score = " << score << endl;
    buffer << "Speed = " << abs(150 - speed[level]) << endl;

    setCursorPosition(0, 0); // Move cursor to the top
    cout << buffer.str();
}

// Set the cursor position in the console
void setCursorPosition(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

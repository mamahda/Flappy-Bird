#include <iostream>
#include <fcntl.h>   // For fcntl(), F_GETFL, F_SETFL, O_NONBLOCK
#include <unistd.h>
#include <termios.h>
#include <cstdlib>
#include <ctime>
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
bool kbhit();
char getch();

int main()
{
    srand(time(0));
    char repeat = 'y';
    int highscore = 0;

    while (repeat == 'y' || repeat == 'Y')
    {
        system("clear");
        stringstream buffer;
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
            usleep(speed[level] * 1000);         // Adjust speed
            if (score % 5 == 0 && score < 75)
            {
                level = score / 5;
            }
        }

        setCursorPosition(0, 21); // Move cursor to the bottom for messages 
        buffer << endl;
        buffer << "Game Over!" << endl;
        buffer << "Score = " << score << endl;
        if (highscore < score)
            highscore = score;
        buffer << "Highscore = " << highscore << endl;
        buffer << "retry?(y/n) = ";
        cout << buffer.str();
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
        Obs[i].y = rand() % 12 + 2;

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
    for (int i = 0; i < 3; i++)
    {
        for (int j = 1; j < 19; j++)
            map[j][Obs[i].x] = "  ";
    }

    for (int i = 0; i < 3; i++)
        Obs[i].x--;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 1; j < 19; j++)
            map[j][Obs[i].x] = "| ";
    }

    for (int i = 0; i < 3; i++)
    {
        for (int j = Obs[i].y; j < Obs[i].y + 5; j++)
        {
            map[j][Obs[i].x] = "  ";
        }
    }

    for (int i = 0; i < 3; i++)
    {
        if (Obs[i].x == 1)
        {
            for (int j = 1; j < 19; j++)
                map[j][Obs[i].x] = "  ";
            Obs[i].x = 28;
            Obs[i].y = rand() % 12 + 2;
        }
    }
}

void birdMove(string map[20][30], Obstacle Obs[3], int *x, bool *hp, int *score)
{
    char mv;
    map[*x][3] = "  ";

    if (kbhit())
    {
        mv = getch();
        *x = (*x) - 3;
    }
    (*x)++;

    if (*x < 1)
        *x = 1;

    for (int i = 0; i < 3; i++)
    {
        if (Obs[i].x == 3)
            if (map[*x][3] == "  ")
                *score = (*score) + 1;
        if (map[*x][3] == "| ")
            *hp = false;
    }

    map[*x][3] = "& ";
}

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

    setCursorPosition(0, 0);
    cout << buffer.str();
}

void setCursorPosition(int x, int y)
{
    cout << "\033[" << y << ";" << x << "H";
}

bool kbhit()
{
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if (ch != EOF)
    {
        ungetc(ch, stdin);
        return true;
    }

    return false;
}

char getch()
{
    struct termios oldt, newt;
    char ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}


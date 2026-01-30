#include <iostream>
#include <unistd.h>     
#include <termios.h>    
#include <fcntl.h>      
#include <cstdlib>
#include <ctime>
int kbhit() {
    termios oldt, newt;
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
    if (ch != EOF) {
        ungetc(ch, stdin);
        return 1;
    }
    return 0;
}
char getch() {
    termios oldt, newt;
    char ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}
bool gameOver;
const int width = 40;
const int height = 20;
int x, y;
int foodX, foodY;
int score;
int tailX[100], tailY[100];
int nTail;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;
void Setup() {
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    srand(time(0));
    foodX = rand() % (width - 2) + 1;
    foodY = rand() % (height - 2) + 1;
    score = 0;
    nTail = 0;
}
void Draw() {
    system("clear");
    for (int i = 0; i < width + 2; i++)
        std::cout << "#";
    std::cout << std::endl;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0)
                std::cout << "#";
            if (i == y && j == x)
                std::cout << "O";
            else if (i == foodY && j == foodX)
                std::cout << "F";
            else {
                bool printTail = false;
                for (int k = 0; k < nTail; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        std::cout << "o";
                        printTail = true;
                        break;
                    }
                }
                if (!printTail)
                    std::cout << " ";
            }
            if (j == width - 1)
                std::cout << "#";
        }
        std::cout << std::endl;
    }
    for (int i = 0; i < width + 2; i++)
        std::cout << "#";
    std::cout << std::endl;
    std::cout << "Score: " << score << std::endl;
    std::cout << "Controls: W A S D | X = Exit" << std::endl;
}
void Input() {
    if (kbhit()) {
        char ch = getch();
        switch (ch) {
        case 'a': dir = LEFT; break;
        case 'd': dir = RIGHT; break;
        case 'w': dir = UP; break;
        case 's': dir = DOWN; break;
        case 'x': gameOver = true; break;
        default: break;
        }
    }
}
void Logic() {
    int prevX = tailX[0];
    int prevY = tailY[0];
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
    case LEFT:  x--; break;
    case RIGHT: x++; break;
    case UP:    y--; break;
    case DOWN:  y++; break;
    default: break;
    }
    if (x < 0 || x >= width || y < 0 || y >= height)
        gameOver = true;
    for (int i = 0; i < nTail; i++)
        if (tailX[i] == x && tailY[i] == y)
            gameOver = true;
    if (x == foodX && y == foodY) {
        score += 10;
        foodX = rand() % (width - 2) + 1;
        foodY = rand() % (height - 2) + 1;
        nTail++;
    }
}
int main() {
    Setup();
    while (!gameOver) {
        Draw();
        Input();
        Logic();
        usleep(100000);
    }
    system("clear");
    std::cout << "GAME OVER " << std::endl;;
    std::cout << "Final Score: " << score << std::endl;
    std::cout << "Press Enter to exit...";
    std::cin.get();
    return 0;
}

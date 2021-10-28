#include <iostream>
#include <queue>

#define ROWS 9
#define COLS 10

struct Position
{
    int x;
    int y;

    Position(int x, int y) 
        : x(x), y(y) {}

    bool operator==(const Position& rhs)
    {
        return x == rhs.x && y== rhs.y;
    }
};

struct Cell 
{
    Position pos;
    int steps;

    Cell(Position pos, int steps) 
        : pos(pos), steps(steps) {}
};

bool isValid(int row, int col)
{
    return row >= 0 && row < ROWS && 
           col >= 0 && col < COLS;
} 

int getShortestPath(bool maze[][COLS], Position start, Position end)
{
    // Не можем да се движим по диагонал, затова валидните движения са:
    int movesCount = 4;
    std::vector<Position> moves{{0, -1}, {0, 1}, {1, 0}, {-1, 0}};

    // Матрица за посетените полета
    bool visited[ROWS][COLS];
    for (int rows = 0; rows < ROWS; rows++)
    {
        for (int i = 0; i < COLS; i++)
        {
            visited[rows][i] = false;
        }
    }

    // Първото посетено поле е това, от което започваме
    visited[start.x][start.y] = true;
    
    // Опашка за достигнатите полета
    std::queue<Cell> q;

    // Първото достигнато поле е началното. То е достигнато с 0 стъпки
    q.push(Cell(start, 0));

    while (!q.empty())
    {
        Cell current = q.front();
        q.pop();

        // Проверка дали сме достигнали финалното поле
        if (current.pos == end)
        {
            return current.steps;
        }

        // Генериране на достижимите полета от текущото
        for (int i = 0; i < movesCount; i++)
        {
            // Координатите на достижимо поле получаваме като направим изместването moves[i]
            int newX = current.pos.x + moves[i].x;
            int newY = current.pos.y + moves[i].y;

            // 1. Ако тези координати са валидни координати за лабиринта и
            // 2. полето, което отговаря на тях все още не е било посещавано и
            // 3. през него може да се мине (т.е. представено е с 1 в лабиринта, а е 0 е стена),
            // то го добавяме в опашката заедно с броя стъпки, с които е достигнато и
            // го отбелязваме като посетено в матрицата.
            if (isValid(newX, newY) && !visited[newX][newY] && maze[newX][newY])
            {
                visited[newX][newY] = true;
                q.push(Cell(Position(newX, newY), current.steps + 1));
            }
        }
    }

    return -1;
}


int main()
{
    bool maze[ROWS][COLS] =
    {
        { 1, 0, 1, 1, 1, 1, 0, 1, 1, 1 },
        { 1, 0, 1, 0, 1, 1, 1, 0, 1, 1 },
        { 1, 1, 1, 0, 1, 1, 0, 1, 0, 1 },
        { 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 },
        { 1, 1, 1, 0, 1, 1, 1, 0, 1, 0 },
        { 1, 0, 1, 1, 1, 1, 0, 1, 0, 0 },
        { 1, 0, 0, 0, 0, 1, 0, 0, 0, 1 },
        { 1, 0, 1, 1, 1, 1, 1, 1, 1, 1 },
        { 1, 1, 0, 0, 0, 0, 1, 0, 0, 1 }
    };

    Position start = {0, 0};

    Position end0 = {7, 1};
    std::cout << getShortestPath(maze, start, end0) << std::endl;

    Position end1 = {0, 0};
    std::cout << getShortestPath(maze, start, end1) << std::endl;

    Position end2 = {3, 4};
    std::cout << getShortestPath(maze, start, end2) << std::endl;

    Position end3 = {8, 9};
    std::cout << getShortestPath(maze, start, end3) << std::endl;

    return 0;
}

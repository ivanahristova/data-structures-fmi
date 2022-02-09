#include <iostream>
#include <queue>
#include <string>

template <typename T>
struct Node 
{
    T data;
    Node *left, *right;

    Node(T data) : data(data), left(nullptr), right(nullptr) {}
};

void levelOrderTraversal(Node<char>* root, std::vector<std::string>& levels)
{
    if (!root)
    {
        return;
    }

    std::queue<Node<char>*> q;
    q.push(root);

    while (!q.empty())
    {
        int size = q.size();
        std::string level;

        for (int i = 0; i < size; i++)
        {
            Node<char>* r = q.front();
            q.pop();

            level.push_back(r->data);

            if (r->left)
            {
                q.push(r->left);
            }
            if (r->right)
            {
                q.push(r->right);
            }
        }

        levels.push_back(level);
    }
}

template <typename T>
void levelZigZagOrder(Node<T>* root, std::vector<std::vector<T>>& levels)
{
    if (!root)
    {
        return;
    }

    std::queue<Node<T>*> q;
    q.push(root);
    int levelCheck = 0;

    while (!q.empty())
    {
        int n = q.size();
        std::vector<T> level;

        while(n--)
        {
            Node<T>* r = q.front();
            q.pop();

            if (levelCheck % 2)
            {
                level.insert(level.begin(), r->data);
            }
            else
            {
                level.push_back(r->data);
            }

            if (r->left)
            {
                q.push(r->left);
            }
            if (r->right)
            {
                q.push(r->right);
            }
        }
        levelCheck++;
        levels.push_back(level);
    }
}

struct Room
{
    std::string name;

    Room(std::string name) : name(name) {}
};

struct Door
{
    bool isLocked;

    Door(bool isLocked = false) : isLocked(isLocked) {}

    bool isLockedCheck()
    {
        return isLocked;
    }
};

class Maze
{
private:
    std::vector<std::pair<Room*, std::vector<std::pair<Door*, Room*>>>> maze;
    int vertices;

    int getRoomIndex(Room* city)
    {
        for (int i = 0; i < vertices; i++)
        {
            if (maze[i].first->name == city->name)
            {
                return i;
            }
        }
        return -1;
    }

    void getSuccessors(Room* start, std::vector<std::pair<Door*, Room*>>& succ)
    {
        int index = getRoomIndex(start);
        succ = maze[index].second;
    }

    void BFS(Room* start, std::vector<bool>& visited)
    {
        std::queue<Room*> q;
        q.push(start);

        int startIndex = getRoomIndex(start);
        visited[startIndex] = true;

        while (!q.empty())
        {
            Room* current = q.front();
            q.pop();

            std::vector<std::pair<Door*, Room*>> succ;
            getSuccessors(current, succ);

            for (int i = 0; i < succ.size(); i++)
            {
                if (succ[i].first->isLockedCheck())
                {
                    continue;
                }

                int ind = getRoomIndex(succ[i].second);
                visited[ind] = true;
                q.push(succ[i].second);
            }
        }
    }

public:

    Maze(int vertices, std::vector<std::pair<Room*, std::vector<std::pair<Door*, Room*>>>> v)
        : vertices(vertices), maze(v) {}

    bool isReachable(Room* start, Room* end)
    {
        std::vector<bool> visited(vertices, false);
        int startIndex = getRoomIndex(start);
        int endIndex = getRoomIndex(end);

        BFS(start, visited);
        return visited[endIndex];
    }
};

template <typename T>
void free(Node<T>* root)
{
    if (!root)
    {
        return;
    }

    free(root->left);
    free(root->right);
    delete root;
}

int main()
{
    Node<char>* root = new Node<char>('a');
    root->left = new Node<char>('b');
    root->left->left = new Node<char>('c');
    root->left->right = new Node<char>('d');
    root->left->right->left = new Node<char>('e');
    root->right = new Node<char>('f');
    root->right->left = new Node<char>('g');
    root->right->right = new Node<char>('h');
    root->right->left->left = new Node<char>('i');
    root->right->right->left = new Node<char>('j');

    std::vector<std::string> levels;
    levelOrderTraversal(root, levels);

    for (int i = 0; i < levels.size(); i++)
    {
        std::cout << levels[i] << ' ';
    }
    std::cout << '\n';

    std::vector<std::vector<char>> levelsZigZag;
    levelZigZagOrder(root, levelsZigZag);

    for (int i = 0; i < levelsZigZag.size(); i++)
    {
        for (int j = 0; j < levelsZigZag[i].size(); j++)
        {
            std::cout << levelsZigZag[i][j] << ' ';
        }
        std::cout << '\n';
    }

    free(root);

    Door* d1 = new Door();
    Door* d2 = new Door(1);

    Room* r1 = new Room("r1");
    Room* r2 = new Room("r2");
    Room* r3 = new Room("r3");
    Room* r4 = new Room("r4");
    Room* r5 = new Room("r5");
    Room* r6 = new Room("r6");

    std::vector<std::pair<Room*, std::vector<std::pair<Door*, Room*>>>> v{
        {r1, std::vector<std::pair<Door*, Room*>>{{d1, r2}, {d2, r3}}},
        {r2, std::vector<std::pair<Door*, Room*>>{{d1, r3}, {d1, r4}}},
        {r3, std::vector<std::pair<Door*, Room*>>{{d2, r5}, {d2, r4}}},
        {r4, std::vector<std::pair<Door*, Room*>>{{d2, r6}}},
        {r5, std::vector<std::pair<Door*, Room*>>{}},
        {r6, std::vector<std::pair<Door*, Room*>>{}}};

    Maze m(6, v);

    std::cout << m.isReachable(r1, r4) << '\n';
    std::cout << m.isReachable(r1, r6) << '\n';
    std::cout << m.isReachable(r4, r6) << '\n';

    delete d1;
    delete d2;
    delete r1;
    delete r2;
    delete r3;
    delete r4;
    delete r5;
    delete r6;
}

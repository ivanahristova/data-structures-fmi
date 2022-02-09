#include <iostream>
#include <queue>

// Всички задачи са решени за *двоично* дърво

template <typename T>
struct Node
{
    T data;
    Node<T>* left;
    Node<T>* right;

    Node(T data, Node<T>* left = nullptr, Node<T>* right = nullptr)
        : data(data), left(left), right(right) {}

    void free()
    {
        if (left)
        {
            left->free();
            delete left;
        }

        if (right)
        {
            right->free();
            delete right;
        }
    }

    void print()
    {
        if (this == nullptr)
        {
            std::cout << '*';
            return;
        }

        std::cout << '(';
        left->print();
        std::cout << data;
        right->print();
        std::cout << ')';
    }
};

// Задача 1
// Сума на елементите на дърво

// Итеративно решение
int sumIter(Node<int>* root)
{
    std::queue<Node<int>*> q;
    int sum = 0;

    if (root == nullptr)
    {
        return sum;
    }

    q.push(root);

    while (!q.empty())
    {
        root = q.front();
        q.pop();

        sum += root->data;

        if (root->left)
        {
            q.push(root->left);
        }

        if (root->right)
        {
            q.push(root->right);
        }
    }

    return sum;
}

int sumRec(Node<int>* root)
{
    if (root == nullptr)
    {
        return 0;
    }

    int sumLeftChild = sumRec(root->left);
    int sumRightChild = sumRec(root->right);

    return root->data + sumLeftChild + sumRightChild;
}

// Задача 2
// Дали елемент X се съдържа в дърво

template <typename T>
bool contains(Node<T>* root, T x)
{
    if (root == nullptr)
    {
        return false;
    }

    return root->data == x || contains(root->left, x) || contains(root->right, x);
}

// Задача 3
// Броят на върховете в дърво

template <typename T>
int elementsCount(Node<T>* root)
{
    if (!root)
    {
        return 0;
    }

    // текущия връх (1 елемент)
    // + броя на върховете в лявото поддърво
    // + броя на върховете в дясното поддърво
    return 1 + elementsCount(root->left) + elementsCount(root->right);
}

// Задача 4
// Максималната стойност на връх в дърво

int max(Node<int>* root)
{
    if (!root->left && !root->right)
    {
        return root->data;
    }

    if (root->left && !root->right)
    {
        return std::max(root->data, max(root->left));
    }

    if (!root->left && root->right)
    {
        return std::max(root->data, max(root->right));
    }

    return std::max(root->data, std::max(max(root->left), max(root->right)));
}

// Задача 5
// Броят на листата в дърво

int leaves(Node<int>* root)
{
    if (root == nullptr)
    {
        return 0;
    }

    if (!root->left && !root->right)
    {
        return 1;
    }

    return leaves(root->left) + leaves(root->right);
}

// Задача 6
// Поддърво с начало подадената стойност

template <typename T>
Node<T>* subtree(Node<T>* root, T x)
{
    if (root == nullptr)
    {
        return nullptr;
    }

    if (root->data == x)
    {
        return root;
    }

    Node<T>* sub = subtree(root->left, x);
    return sub ? sub : subtree(root->right, x);
}

// Задача 7
// Да се принтира дървото, обхождайки го ЛКД

template <typename T>
void inOrder(Node<T>* root)
{
    if (root == nullptr)
    {
        return;
    }

    inOrder(root->left);
    std::cout << root->data << ' ';
    inOrder(root->right);
}

// Задача 8
// Да се принтира дървото, обхождайки го КЛД

template <typename T>
void preOrder(Node<T>* root)
{
    if (root == nullptr)
    {
        return;
    }

    std::cout << root->data << ' ';
    preOrder(root->left);
    preOrder(root->right);
}

// Задача 9
// Да се намери сумата на елементите на подадено ниво

// 1во решение
int getSumLevel(Node<int>* root, int level)
{
    if (root == nullptr)
    {
        return 0;
    }

    if (level == 0)
    {
        return root->data;
    }

    return getSumLevel(root->left, level - 1) + getSumLevel(root->right, level - 1);
}

// 2ро решение
void helper(Node<int>* root, int level, int& sum)
{
    if (root == nullptr)
    {
        return;
    }

    if (level == 0)
    {
        sum += root->data;
        return;
    }

    helper(root->left, level - 1, sum);
    helper(root->right, level - 1, sum);
}

int getSumLevel2(Node<int>* root, int level)
{
    int sum  = 0;
    helper(root, level, sum);
    return sum;
}

// Задача 10
// Да се принтират елементите на подадено ниво

template <typename T>
void printLevel(Node<T>* root, int level)
{
    if (root == nullptr)
    {
        return;
    }

    if (level == 0)
    {
        std::cout << root->data << ' ';
    }

    printLevel(root->left, level - 1);
    printLevel(root->right, level - 1);
}

// Задача 11
// Да се намери височината на дърво

// Итеративно решение
template <typename T>
int getHeightIter(Node<T>* root)
{
    if (root == nullptr)
    {
        return 0;
    }

    std::queue<Node<T>*> q;
    q.push(root);

    int height = 0;

    while (!q.empty())
    {
        int size = q.size();

        // искаме в един момент в опашката да се съдържат само върховете
        // от едно и също ниво
        // за целта обхождаме всички от текущото, а техните деца добавяме в опашката
        while (size--)
        {
            Node<T>* front = q.front();
            q.pop();

            if (front->left)
            {
                q.push(front->left);
            }

            if (front->right)
            {
                q.push(front->right);
            }
        }

        height++;
    }

    return height;
}

// Рекурсивно решение
template <typename T>
int getHeightRec(Node<T>* root)
{
    if (root == nullptr)
    {
        return 0;
    }

    return 1 + std::max(getHeightRec(root->left), getHeightRec(root->right));
}

int main()
{
    Node<int>* root = new Node<int>(1);
    root->left = new Node<int>(2);
    root->right = new Node<int>(3);
    root->left->left = new Node<int>(4);
    root->left->right = new Node<int>(5);
    root->right->left = new Node<int>(6);
    root->right->right = new Node<int>(7);

    std::cout << "Дърво: ";
    root->print();
    std::cout << "\nПоддърво с корен 3: ";
    subtree(root, 3)->print();

    std::cout << "\ninorder: ";
    inOrder(root);
    std::cout << "\npreorder: ";
    preOrder(root);

    std::cout << "\nСума на елемнтите (итеративно): " << sumRec(root);
    std::cout << "\nСума на елемнтите (рекурсивно): " << sumIter(root);

    std::cout << "\nСъдържа елемент 2: " << contains(root, 2);
    std::cout << "\nСъдържа елемент 8: " << contains(root, 8);

    std::cout << "\nБрой на елементите: " << elementsCount(root);
    std::cout << "\nБрой на елементите в дървото с корен 2: " << elementsCount(root->left);

    std::cout << "\nМаксимален елемент в дървото: " << max(root);
    std::cout << "\nБрой листа в дървото с корен 2: " << leaves(root->left);

    std::cout << "\nСума на елементите на ниво 1 (вар 1): " << getSumLevel(root, 1);
    std::cout << "\nСума на елементите на ниво 3 (вар 1): " << getSumLevel(root, 3);

    std::cout << "\nСума на елементите на ниво 1 (вар 2): " << getSumLevel2(root, 1);
    std::cout << "\nСума на елементите на ниво 3 (вар 2): " << getSumLevel2(root, 3);

    std::cout << "\nВисочина на дървото (итеративно): " << getHeightIter(root);
    std::cout << "\nВисочина на дървото (рекурсивно): " << getHeightRec(root);

    root->free();
    delete root;
}
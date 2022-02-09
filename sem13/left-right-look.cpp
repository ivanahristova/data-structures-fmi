#include <iostream>
#include <vector>
#include <queue>

struct Node 
{
    int data;
    Node* left;
    Node* right;

    Node(int data) 
        : data(data), left(nullptr), right(nullptr) {}
};

void rightLook(Node* t, std::vector<int>& view)
{
    if (t == nullptr)
    {
        return;
    }

    std::queue<Node*> level;
    level.push(t);

    while (!level.empty())
    {
        int elements = level.size();
        Node* current = level.front();

        for (int i = 0; i < elements; i++)
        {
            current = level.front();
            level.pop();

            if (current->left)
            {
                level.push(current->left);
            }

            if (current->right)
            {
                level.push(current->right);
            }
        }
        
        view.push_back(current->data);
    }
}

void leftLook(Node* t, std::vector<int>& view)
{
    if (t == nullptr)
    {
        return;
    }

    std::queue<Node*> level;
    level.push(t);

    while (!level.empty())
    {
        int elements = level.size();
        
        Node* current = level.front();
        view.push_back(current->data);

        for (int i = 0; i < elements; i++)
        {
            current = level.front();
            level.pop();

            if (current->left)
            {
                level.push(current->left);
            }

            if (current->right)
            {
                level.push(current->right);
            }
        }
    }
}

int main()
{
    //          1
    //        /   \ 
    //      2       2  
    //     / \     / \ 
    //    3   4   9   11
    //       /
    //      5

    Node* root = new Node(1);
    root->left = new Node(2);
    root->left->left = new Node(3);
    root->left->right = new Node(4);
    root->left->right->left = new Node(5);
    root->right = new Node(2);
    root->right->left = new Node(9);
    root->right->right = new Node(11);

    std::vector<int> viewRight;
    std::vector<int> viewLeft;
    rightLook(root, viewRight);
    leftLook(root, viewLeft);

    std::cout << "Left: ";
    for (int i = 0; i < viewLeft.size(); i++)
    {
        std::cout << viewLeft[i] << ' ';
    }
    std::cout << '\n';

    std::cout << "Right: ";
    for (int i = 0; i < viewRight.size(); i++)
    {
        std::cout << viewRight[i] << ' ';
    }
}
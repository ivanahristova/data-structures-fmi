#include <iostream>
#include <vector>
#include <tuple>
#include <queue>

struct Node 
{
    int data;
    Node* left;
    Node* right;

    Node(int data) 
        : data(data), left(nullptr), right(nullptr) {}
};

bool leftLookSameAsRightLook(Node* t)
{
    if (t == nullptr)
    {
        return false;
    }

    std::queue<Node*> level;
    level.push(t);
    bool isSimilar = true;

    while (!level.empty())
    {
        int elements = level.size();
        
        Node* leftmost = level.front();
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

        if (current->data != leftmost->data)
        {
            isSimilar = false;
            break;
        }
    }

    return isSimilar;
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

    std::cout << leftLookSameAsRightLook(root) << std::endl;
    
    //          1
    //        /   \ 
    //      2       2  
    //     / \     / \ 
    //    3   4   9   3
    //       /
    //      5
    
    Node* root1 = new Node(1);
    root1->left = new Node(2);
    root1->left->left = new Node(3);
    root1->left->right = new Node(4);
    root1->left->right->left = new Node(5);
    root1->right = new Node(2);
    root1->right->left = new Node(9);
    root1->right->right = new Node(3);

    std::cout << leftLookSameAsRightLook(root1);
}
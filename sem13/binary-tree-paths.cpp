#include <iostream>
#include <vector>

struct CharNode
{
    char data;
    CharNode* left;
    CharNode* right;

    CharNode(char data) 
        : data(data), left(nullptr), right(nullptr) {}
};

void binaryTreePaths(CharNode* root, std::vector<std::string>& paths)
{
    if (root == nullptr)
    {
        return;
    }

    else if (root->left == nullptr && root->right == nullptr)
    {
        std::string str;
        str.push_back(root->data);
        paths.push_back(str);
    }

    std::vector<std::string> left;
    binaryTreePaths(root->left, left);
    for (int i = 0; i < left.size(); ++i)
    {
        std::string current = root->data + left[i];
        left[i] = current;
    }

    std::vector<std::string> right;
    binaryTreePaths(root->right, right);
    for (int i = 0; i < right.size(); ++i)
    {
        std::string current = root->data + right[i];
        right[i] = current;
    }

    for (std::string x : left)
    {
        paths.push_back(x);
    }
    for (std::string x : right)
    {
        paths.push_back(x);
    }
}

int main()
{
    //       a
    //    /     \ 
    //   b       f
    //  / \     / \ 
    // c   d   g   h
    //    /
    //   e

    CharNode* root = new CharNode('a');
    root->left = new CharNode('b');
    root->left->left = new CharNode('c');
    root->left->right = new CharNode('d');
    root->left->right->left = new CharNode('e');
    root->right = new CharNode('f');
    root->right->left = new CharNode('g');
    root->right->right = new CharNode('h');

    std::vector<std::string> paths;
    binaryTreePaths(root, paths);

    for (int i = 0; i < paths.size(); i++)
    {
        std::cout << paths[i] << ' ';
    }
}
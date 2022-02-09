#include <climits>
#include <iostream>
#include <vector>

template <typename T>
struct Node
{
    T data;
    Node<T>* left;
    Node<T>* right;

    Node(const T& data, Node<T>* left = nullptr, Node<T>* right = nullptr)
        : data(data), left(left), right(right) {}
};

// Задача 1
bool isBSTNaive(Node<int>* root)
{
    if (root == nullptr || !root->left && !root->right)
    {
        return true;
    }

    if (root->left && !root->right)
    {
        return root->data > root->left->data && isBSTNaive(root->left);
    }
    else if (!root->left && root->right)
    {
        return root->data < root->right->data && isBSTNaive(root->left);
    }
    else
    {
        int rootValidity = root->data > root->left->data && root->data < root->right->data;
        return rootValidity && isBSTNaive(root->left) && isBSTNaive(root->right);
    }
}

// Задача 1
bool isBSTVer1(Node<int>* root, int minValue, int maxValue)
{
    if (root == nullptr)
    {
        return true;
    }

    if (root->data < minValue || root->data > maxValue)
    {
        return false;
    }

    return isBSTVer1(root->left, minValue, root->data)
        && isBSTVer1(root->right, root->data, maxValue);
}

bool isBSTVer1(Node<int>* root)
{
    return isBSTVer1(root, INT_MIN, INT_MAX);
}

// Задача 1
void isBSTVer2(Node<int>* root, std::vector<int>& elements)
{
    if (root == nullptr)
    {
        return;
    }

    isBSTVer2(root->left, elements);
    elements.push_back(root->data);
    isBSTVer2(root->right, elements);
}

bool isBSTVer2(Node<int>* root)
{
    std::vector<int> inorderTraversal;
    isBSTVer2(root, inorderTraversal);

    int size = inorderTraversal.size();
    for (int i = 1; i < size; i++)
    {
        if (inorderTraversal[i - 1] >= inorderTraversal[i])
        {
            return false;
        }
    }
    
    return true;
}

int main()
{
    Node<int>* root1 = new Node<int>(12);
    root1->left = new Node<int>(5);
    root1->left->left = new Node<int>(3);
    root1->left->right = new Node<int>(14);
    root1->right = new Node<int>(20);
    root1->right->left = new Node<int>(15);
    root1->right->right = new Node<int>(28);

    Node<int>* root = new Node<int>(12);
    root->left = new Node<int>(5);
    root->left->left = new Node<int>(3);
    root->left->right = new Node<int>(7);
    root->right = new Node<int>(20);
    root->right->left = new Node<int>(15);
    root->right->right = new Node<int>(28);

    std::cout << isBSTNaive(root1) << '\n';
    std::cout << isBSTVer1(root1) << '\n';
    std::cout << isBSTVer2(root1) << '\n';

    std::cout << isBSTNaive(root) << '\n';
    std::cout << isBSTVer1(root) << '\n'; 
    std::cout << isBSTVer2(root) << '\n';
}

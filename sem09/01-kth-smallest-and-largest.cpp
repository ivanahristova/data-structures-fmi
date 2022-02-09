#include <iostream>
#include <stdexcept>

template <typename T>
struct Node
{
    T data;
    Node<T>* left;
    Node<T>* right;

    Node(const T& data, Node<T>* left = nullptr, Node<T>* right = nullptr)
        : data(data), left(left), right(right) {}
};

Node<int>* kSmallestHelper(Node<int>* root, int& i, int k)
{
    if (root == nullptr)
    {
        return nullptr;
    }

    Node<int>* left = kSmallestHelper(root->left, i, k);
    if (left)
    {
        return left;
    }

    i++;
    if (i == k)
    {
        return root;
    }

    return kSmallestHelper(root->right, i, k);
}

int kSmallest(Node<int>* root, int k)
{
    int i = 0;
    Node<int>* node = kSmallestHelper(root, i, k);
    return node ? node->data : throw std::runtime_error("k exceeds tree nodes count");
}

Node<int>* kLargestHelper(Node<int>* root, int& i, int k)
{
    if (root == nullptr)
    {
        return nullptr;
    }

    Node<int>* right = kLargestHelper(root->right, i, k);
    if (right)
    {
        return right;
    }

    i++;
    if (i == k)
    {
        return root;
    }

    return kLargestHelper(root->left, i, k);
}

int kLargest(Node<int>* root, int k)
{
    int i = 0;
    Node<int>* node = kLargestHelper(root, i, k);
    return node ? node->data : throw std::runtime_error("k exceeds tree nodes count");
}

int main()
{
    Node<int>* root = new Node<int>(12);
    root->left = new Node<int>(5);
    root->left->left = new Node<int>(3);
    root->left->right = new Node<int>(7);
    root->right = new Node<int>(20);
    root->right->left = new Node<int>(15);
    root->right->right = new Node<int>(28);

    std::cout << kSmallest(root, 1) << '\n';
    std::cout << kSmallest(root, 2) << '\n';
    std::cout << kSmallest(root, 3) << '\n';
    std::cout << kSmallest(root, 4) << '\n';
    std::cout << kSmallest(root, 5) << '\n';
    std::cout << kSmallest(root, 6) << '\n';
    std::cout << kSmallest(root, 7) << '\n';

    std::cout << kLargest(root, 7) << '\n';
    std::cout << kLargest(root, 6) << '\n';
    std::cout << kLargest(root, 5) << '\n';
    std::cout << kLargest(root, 4) << '\n';
    std::cout << kLargest(root, 3) << '\n';
    std::cout << kLargest(root, 2) << '\n';
    std::cout << kLargest(root, 1) << '\n';
}
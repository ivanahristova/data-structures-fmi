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

template <typename T>
Node<T>* helper(Node<T>* root, Node<T>* x, Node<T>* y)
{
    if (root == nullptr)
    {
        return nullptr;
    }

    if (root->data > std::max(x->data, y->data))
    {
        return helper(root->left, x, y);
    }    
    else if (root->data < std::min(x->data, y->data))
    {
        return helper(root->right, x, y);
    }

    return root;
}

template <typename T>
T getLeastCommonAncestor(Node<T>* root, Node<T>* x, Node<T>* y)
{
    Node<T>* node = helper(root, x, y);
    return node ? node->data : throw std::runtime_error("exception");
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

    std::cout << getLeastCommonAncestor(root, root->left->left, root->left->right) << '\n';
    std::cout << getLeastCommonAncestor(root, root->right->left, root->right->right) << '\n';
    std::cout << getLeastCommonAncestor(root, root->left, root->left->right) << '\n';
    std::cout << getLeastCommonAncestor(root, root, root->left->right) << '\n';
    std::cout << getLeastCommonAncestor(root, root->left->left, root->right) << '\n';

}
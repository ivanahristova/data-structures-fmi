#include <iostream>
#include <algorithm>

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
class BinarySearchTree
{
private:

    Node<T>* root;

private:

    Node<T>* createBSTFromArray(T* arr, int size);
    Node<T>* clone(Node<T>* tree) const;
    void free(Node<T>*& tree);

public:

    BinarySearchTree();
    BinarySearchTree(T* arr, int size);
    BinarySearchTree(const BinarySearchTree<T>& other);
    BinarySearchTree<T>& operator=(const BinarySearchTree<T>& other);
    ~BinarySearchTree();

    const T& min() const;
    const T& max() const;

    bool contains(const T& x) const;
    void insert(const T& x);
    void remove(const T& x);

    bool empty() const;
    void print(std::ostream& out = std::cout) const;

private:

    Node<T>* min(Node<T>* tree) const;
    Node<T>* max(Node<T>* tree) const;

    bool contains(Node<T>* tree, const T& x) const;
    void insert(Node<T>*& tree, const T& x);
    void remove(Node<T>*& tree, const T& x);

    void print(Node<T>* tree, std::ostream& out) const;    
};

template <typename T>
Node<T>* BinarySearchTree<T>::createBSTFromArray(T* arr, int size)
{
    if (size < 1)
    {
        return nullptr;
    }

    int mid = size / 2;

    Node<T>* newRoot = new Node<T>(arr[mid]);
    newRoot->left = createBSTFromArray(arr, mid);
    newRoot->right = createBSTFromArray(arr + mid + 1, size - mid - 1);

    return newRoot;
}

template <typename T>
Node<T>* BinarySearchTree<T>::clone(Node<T>* tree) const
{
    if (tree == nullptr)
    {
        return nullptr;
    }

    return new Node<T>(tree->data, clone(tree->left), clone(tree->right));
}

template <typename T>
void BinarySearchTree<T>::free(Node<T>*& tree)
{
    if (tree)
    {
        free(tree->left);
        free(tree->right);
        delete tree;
    }

    tree = nullptr;
}  

template <typename T>
BinarySearchTree<T>::BinarySearchTree()
    : root(nullptr) {}

template <typename T>
BinarySearchTree<T>::BinarySearchTree(T* arr, int size)
{
    std::sort(arr, arr + size);
    root = createBSTFromArray(arr, size);
}

template <typename T>
BinarySearchTree<T>::BinarySearchTree(const BinarySearchTree<T>& other)
    : root(nullptr)
{
    this->root = clone(other.root);
}

template <typename T>
BinarySearchTree<T>& BinarySearchTree<T>::operator=(const BinarySearchTree<T>& other)
{
    if (this != &other)
    {
        free(root);
        this->root = clone(other.root);
    }
    return *this;
}

template <typename T>
BinarySearchTree<T>::~BinarySearchTree()
{
    free(root);
}

template <typename T>
Node<T>* BinarySearchTree<T>::min(Node<T>* tree) const
{
    if (tree == nullptr)
    {
        return nullptr;
    }

    if (tree->left == nullptr)
    {
        return tree;
    }

    return min(tree->left);
}

template <typename T>
const T& BinarySearchTree<T>::min() const
{
    Node<T>* minNode = min(this->root);

    if (minNode == nullptr)
    {
        throw std::runtime_error("Min called on an empty tree.");
    }

    return minNode->data;
}

template <typename T>
Node<T>* BinarySearchTree<T>::max(Node<T>* tree) const
{
    if (tree == nullptr)
    {
        return nullptr;
    }

    while (tree->right)
    {
        tree = tree->right;
    }

    return tree;
}

template <typename T>
const T& BinarySearchTree<T>::max() const
{
    Node<T>* maxNode = max(this->root);

    if (maxNode == nullptr)
    {
        throw std::runtime_error("Max called on an empty tree.");
    }

    return maxNode->data;
}

template <typename T>
bool BinarySearchTree<T>::contains(Node<T>* tree, const T& x) const
{
    if (tree == nullptr)
    {
        return false;
    }

    if (x == tree->data)
    {
        return true;
    }

    if (x < tree->data)
    {
        return contains(tree->left, x);
    }

    return contains(tree->right, x);
}

template <typename T>
bool BinarySearchTree<T>::contains(const T& x) const
{
    return contains(root, x);
}

template <typename T>
void BinarySearchTree<T>::insert(Node<T>*& tree, const T& x)
{
    if (tree == nullptr)
    {
        tree = new Node<T>(x);
    }
    else if (x == tree->data)
    {
        // we don't support duplicates
    }
    else if (x < tree->data)
    {
        insert(tree->left, x);
    }
    else
    {
        insert(tree->right, x);
    }
}

template <typename T>
void BinarySearchTree<T>::insert(const T& x)
{
    insert(root, x);
}

template <typename T>
void BinarySearchTree<T>::remove(Node<T>*& tree, const T& x)
{
    if (tree == nullptr)
    {
        return;
    }

    if (x < tree->data)
    {
        remove(tree->left, x);
    }
    else if (x > tree->data)
    {
        remove(tree->right, x);
    }
    else // x == tree->data
    {
        if (!tree->left && !tree->right)
        {
            delete tree;
            tree = nullptr;
        }
        else if (tree->left && tree->right)
        {
            tree->data = min(tree->right)->data;
            remove(tree->right, tree->data);
        }
        else
        {
            Node<T>* oldNode = tree;
            tree = tree->left ? tree->left : tree->right;
            delete oldNode;
        }
    }
} 

template <typename T>
void BinarySearchTree<T>::remove(const T& x)
{
    remove(root, x);
}

template <typename T>
bool BinarySearchTree<T>::empty() const
{
    return root == nullptr;
}

template <typename T>
void BinarySearchTree<T>::print(Node<T>* tree, std::ostream& out) const
{
    if (tree == nullptr)
    {
        out << "*";
        return;
    }

    out << "(";
    print(tree->left, out);
    out << tree->data;
    print(tree->right, out);
    out << ")";
}

template <typename T>
void BinarySearchTree<T>::print(std::ostream& out) const
{
    print(root, out);
}

int main()
{
    BinarySearchTree<int> bst;
    bst.insert(10);
    bst.insert(8);
    bst.insert(7);
    bst.insert(9);
    bst.insert(11);
    bst.insert(12);    
    bst.remove(10);
    bst.print();

    BinarySearchTree<int> bst1 = bst;
    BinarySearchTree<int> bst2(bst1);

    std::cout << "\nMin: " << bst.min();
    std::cout << "\nMax: " << bst.max();
    std::cout << "\nEmpty: " << bst.empty();

    std::cout << "\n-----------------\n";
    bst1.remove(8);
    bst1.remove(7);
    bst1.print();
    std::cout << "\nContains 12: " << bst1.contains(12);
    std::cout << "\nContains 10: " << bst1.contains(10);
    std::cout << '\n';

    int arr[9] = {9, 8, 7, 6, 5, 4, 3, 2, 1};
    BinarySearchTree<int> bst3(arr, 9);
    bst3.print();
}
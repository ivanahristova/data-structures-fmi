#include <iostream>

template <typename T>
struct Node
{
    T data;
    Node<T>* left;
    Node<T>* right;

    int height;
    int bf;

    Node(const T& element)
    {
        data = element;
        left = nullptr;
        right = nullptr;
        height = 1;
        bf = 0;
    }
};

template <typename T>
class AVLTree
{
private:
    Node<T>* root;

private:

    Node<T>* clone(Node<T>* tree);
    void free(Node<T>* tree);

    void update(Node<T>* node);
    Node<T>* balance(Node<T>* node);

    Node<T>* leftLeftCase(Node<T>* node);
    Node<T>* leftRightCase(Node<T>* node);
    Node<T>* rightRightCase(Node<T>* node);
    Node<T>* rightLeftCase(Node<T>* node);

    Node<T>* rotateLeft(Node<T>* node);
    Node<T>* rotateRight(Node<T>* node);

    bool contains(Node<T>* tree, const T& x) const;
    Node<T>* insert(Node<T>* tree, const T& x);
    Node<T>* remove(Node<T>* tree, const T& x);

    Node<T>* min(Node<T>* tree) const;
    Node<T>* max(Node<T>* tree) const;

    void print(Node<T>* tree, std::ostream& out) const;


public:
    AVLTree();
    AVLTree(const AVLTree<T>& other);
    AVLTree<T>&  operator=(const AVLTree<T>& other);
    ~AVLTree();

    bool contains(const T& x) const;
    bool insert(const T& x);
    bool remove(const T& x);

    const T& min() const;
    const T& max() const;

    bool empty() const;
    void print(std::ostream& out = std::cout) const;

};

template <typename T>
Node<T>* AVLTree<T>::clone(Node<T>* tree)
{
    if (tree == nullptr)
    {
        return nullptr;
    }

    Node<T>* cloned = new Node<T>(tree->data);
    cloned->left = clone(tree->left);
    cloned->right = clone(tree->right);
    return cloned;
}

template <typename T>
void AVLTree<T>::free(Node<T>* tree)
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
void AVLTree<T>::update(Node<T>* node)
{
    if (node == nullptr)
    {
        return;
    }

    int leftHeight = (node->left == nullptr) ? 0 : node->left->height;
    int rightHeight = (node->right == nullptr) ? 0 : node->right->height;

    node->height = 1 + std::max(leftHeight, rightHeight);
    node->bf = rightHeight - leftHeight;
}

template <typename T>
Node<T>* AVLTree<T>::balance(Node<T>* node)
{
    if (node == nullptr)
    {
        return nullptr;
    }

    // left-heavy
    if (node->bf == -2)
    {
        if (node->left->bf <= 0)
        {
            return leftLeftCase(node);
        }
        else
        {
            return leftRightCase(node);
        }
    }
    else if (node->bf == 2)
    {
        if (node->right->bf >= 0)
        {
            return rightRightCase(node);
        }
        else
        {
            return rightLeftCase(node);
        }
    }
   
    return node;
}

template <typename T>
Node<T>* AVLTree<T>::leftLeftCase(Node<T>* node)
{
    return rotateRight(node);
}

template <typename T>
Node<T>* AVLTree<T>::leftRightCase(Node<T>* node)
{
    node->left = rotateLeft(node->left);
    return leftLeftCase(node);
}

template <typename T>
Node<T>* AVLTree<T>::rightRightCase(Node<T>* node)
{
    return rotateLeft(node);
}

template <typename T>
Node<T>* AVLTree<T>::rightLeftCase(Node<T>* node)
{
    node->right = rotateRight(node->right);
    return rightRightCase(node);
}

template <typename T>
Node<T>* AVLTree<T>::rotateLeft(Node<T>* node)
{
    Node<T>* newParent = node->right;
    node->right = newParent->left;
    newParent->left = node;

    update(node); // Първо се грижим за детето
    update(newParent);

    return newParent;
}

template <typename T>
Node<T>* AVLTree<T>::rotateRight(Node<T>* node)
{
    Node<T>* newParent = node->left;
    node->left = newParent->right;
    newParent->right = node;

    update(node);
    update(newParent);

    return newParent;
}

template <typename T>
bool AVLTree<T>::contains(Node<T>* tree, const T& x) const
{
    if (tree == nullptr)
    {
        return false;
    }

    if (tree->data == x)
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
bool AVLTree<T>::contains(const T& x) const
{
    return contains(root, x);
}

template <typename T>
Node<T>* AVLTree<T>::insert(Node<T>* tree, const T& x)
{
    if (tree == nullptr)
    {
        return new Node<T>(x);
    }

    if (x < tree->data)
    {
        tree->left = insert(tree->left, x);
    }
    else 
    {
        tree->right = insert(tree->right, x);
    }

    update(tree);
    return balance(tree);
}

template <typename T>
bool AVLTree<T>::insert(const T& x)
{
    // добавяме само уникални елементи
    if (contains(root, x))
    {
        return false;
    }

    root = insert(root, x);
    return true;
}

template <typename T>
Node<T>* AVLTree<T>::remove(Node<T>* tree, const T& x)
{
    if (tree == nullptr)
    {
        return nullptr;
    }

    if (x < tree->data)
    {
        tree->left = remove(tree->left, x);
    }
    else if (x > tree->data)
    {
        tree->right = remove(tree->right, x);
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
            if (tree->left->height > tree->right->height)
            {
                tree->data = max(tree->left)->data;
                tree->left = remove(tree->left, tree->data);
            }
            else
            {
                tree->data = min(tree->right)->data;
                tree->right = remove(tree->right, tree->data);
            }
        }
        else
        {
            Node<T>* temp = tree;
            tree = tree->left ? tree->left : tree->right;
            delete temp;
        }
    }

    update(tree);
    return balance(tree);
}

template <typename T>
bool AVLTree<T>::remove(const T& x)
{
    if (!contains(root, x))
    {
        return false;
    }

    root = remove(root, x);
    return true;
}

template <typename T>
AVLTree<T>::AVLTree()
    : root(nullptr) {}

template <typename T>
AVLTree<T>::AVLTree(const AVLTree<T>& other)
   : root(nullptr)
{
    this->root = clone(other.root);
}

template <typename T>
AVLTree<T>&  AVLTree<T>::operator=(const AVLTree<T>& other)
{
    if (this != &other)
    {
        free(root);
        this->root = clone(other.root);
    }
    return *this;
}

template <typename T>
AVLTree<T>::~AVLTree()
{
    free(root);
}

template <typename T>
Node<T>* AVLTree<T>::min(Node<T>* tree) const
{
    if (tree == nullptr)
    {
        return nullptr;
    }

    return tree->left ? min(tree->left) : tree;
}

template <typename T>
const T& AVLTree<T>::min() const
{
    Node<T>* minNode = max(this->root);

    if (minNode == nullptr)
    {
        throw std::runtime_error("Min called on an empty tree.");
    }

    return minNode->data;
}

template <typename T>
Node<T>* AVLTree<T>::max(Node<T>* tree) const
{
    if (tree == nullptr)
    {
        return nullptr;
    }

    return tree->right ? max(tree->right) : tree;
}

template <typename T>
const T& AVLTree<T>::max() const
{
    Node<T>* maxNode = max(this->root);

    if (maxNode == nullptr)
    {
        throw std::runtime_error("Max called on an empty tree.");
    }

    return maxNode->data;
}

template <typename T>
void AVLTree<T>::print(Node<T>* tree, std::ostream& out) const
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
void AVLTree<T>::print(std::ostream& out) const
{
    print(root, out);
}


int main()
{
    AVLTree<int> avl;
    avl.insert(1);
    avl.insert(2);
    avl.insert(3);
    avl.insert(4); 
    avl.insert(5);
    avl.insert(6); 
    avl.insert(10);
    avl.insert(12);
    avl.insert(13);
    avl.insert(14);
    avl.insert(16); 

    avl.remove(10);
    avl.remove(16);
    avl.remove(14);
    avl.remove(12);
    avl.remove(13);
    // avl.remove(1);
    // avl.remove(2);
    // avl.remove(3);
    // avl.remove(4);

    avl.print();
}

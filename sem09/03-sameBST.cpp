#include <iostream>

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
bool representSameBST(T* arr1, T* arr2, int n)
{
    if (n == 0)
    {
        return true;
    }

    if (n == 1)
    {
        return arr1[0] == arr2[0];
    }

    int size = n - 1;
    T leftSubtree1[size];
    T rigthSubtree1[size];
    T leftSubtree2[size];
    T rigthSubtree2[size];

    int leftSubtree1Index = 0, rigthSubtree1Index = 0, leftSubtree2Index = 0, rigthSubtree2Index = 0;

    for (int i = 1; i < n; i++)
    {
        if (arr1[i] < arr1[0])
        {
            leftSubtree1[leftSubtree1Index++] = arr1[i]; 
        }
        else
        {
            rigthSubtree1[rigthSubtree1Index++] = arr1[i];
        }

        if (arr2[i] < arr2[0])
        {
            leftSubtree2[leftSubtree2Index++] = arr2[i]; 
        }
        else
        {
            rigthSubtree2[rigthSubtree2Index++] = arr2[i];
        }
    }

    bool currentSubtrees = leftSubtree1Index == leftSubtree2Index
                            && rigthSubtree1Index == rigthSubtree2Index;

    return currentSubtrees
            && representSameBST(leftSubtree1, leftSubtree2, leftSubtree1Index) 
            && representSameBST(rigthSubtree1, rigthSubtree2, rigthSubtree1Index);
}

int main()
{
    int n = 11;
    int X[] = { 15, 25, 20, 22, 30, 18, 10, 8, 9, 12, 6 };
    int Y[] = { 15, 10, 12, 8, 25, 30, 6, 20, 18, 9, 22 };

    int X1[] = { 15, 25, 20, 22, 30, 19, 10, 8, 9, 12, 6 };
    int Y1[] = { 15, 10, 12, 8, 25, 30, 6, 20, 18, 9, 22 };

    std::cout << representSameBST(X, Y, n)
              << ' '
              << representSameBST(X1, Y1, n);
}
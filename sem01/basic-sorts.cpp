#include <iostream>

template <typename T>
void swap(T* first, T* second)
{
    T temp = *first;
    *first = *second;
    *second = temp;
}

template <typename T>
void BubbleSort(T* arr, int n)
{
    bool isSwapped = true;
    for (int i = 0; i < n && isSwapped; ++i)
    {
        isSwapped = false;
        for (int j = 1; j < n; ++j)
        {
            if (arr[j - 1] > arr[j])
            {
                swap(&arr[j-1], &arr[j]);
                isSwapped = true;
            }
        }
    }
    
}

template <typename T>
void SelectionSort(T* arr, int n)
{
    for (int i = 0; i < n; ++i)
    {
        int minIndex = i;
        for (int j = i + 1; j < n; ++j)
        {
            if (arr[j] < arr[minIndex])
            {
                minIndex = j;
            }
        }
        if (minIndex != i)
        {
            swap(&arr[i], &arr[minIndex]);
        }
    }
}

template <typename T>
void InsertionSort(T* arr, int n)
{
    for (int i = 0; i < n; ++i)
    {
        T key = arr[i];
        int index = i - 1;
        
        while (index >= 0 && arr[index] > key)
        {
            arr[index + 1] = arr[index];
            index--;
        }

        if (index != i - 1)
        {
            arr[index + 1] = key;
        }
    }
}

int main()
{
    const int SIZE = 10;
    int arr[SIZE] = {23, 8, 17, 14, 19, 44, 33, 12, 0, 8};
    
    BubbleSort(arr, SIZE);
    // SelectionSort(arr, SIZE);
    // InsertionSort(arr, SIZE);
    
    for (int i = 0; i < SIZE; ++i)
    {
        std::cout << arr[i] << ' ';
    }
    std::cout << '\n';
}
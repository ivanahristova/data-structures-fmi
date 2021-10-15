#include <iostream>

template <typename T>
void merge(T* arr1, int n1, T* arr2, int n2)
{
    int size = n1 + n2;
    T* arr = new T[size];
    int index = 0, index1 = 0, index2 = 0;

    while(index1 < n1 && index2 < n2)
    {
        if (arr1[index1] <= arr2[index2])
        {
            arr[index++] = arr1[index1++];
        }
        else
        {
            arr[index++] = arr2[index2++];
        }
    }

    while (index1 < n1)
    {
        arr[index++] = arr1[index1++];
    }

    while (index2 < n2)
    {
        arr[index++] = arr2[index2++];
    }

    for (int i = 0; i < size; i++)
    {
        arr1[i] = arr[i];
    }
    
    delete[] arr;
}

template <typename T>
void MergeSort(T* arr, int n)
{
    if (n <= 1)
    {
        return;
    }

    int mid = n / 2;
    MergeSort(arr, mid);
    MergeSort(arr + mid, (n - mid));
    merge(arr, mid, arr+mid, (n-mid));
} 

// Updated version of partiotion
// It uses one index instead of two to move from left to right of the array
template <typename T>
int partition(T* arr, int n)
{
    int pivotId = n / 2;
    T pivot = arr[pivotId];
    int left = 0, right = n - 1;
    int index = left;

    while (index <= right)
    {
        if (arr[index] < pivot)
        {
            std::swap(arr[left++], arr[index++]);
        }
        else if (arr[index] > pivot)
        {
            std::swap(arr[index], arr[right--]);
        }
        else // element is equal to pivot
        {
            index++;
        }
    }

    return right;
}

template <typename T>
void QuickSort(T* arr, int n)
{
    if (n <= 1)
    {
        return;
    }

    int pivotIndex = partition(arr, n);
    QuickSort(arr, pivotIndex);
    QuickSort(arr + pivotIndex + 1, (n - pivotIndex - 1));
}

void CountingSort(int* arr, int n, int lowerBound, int upperBound)
{
    // The interval consists of (upperBound - lowerBound + 1) elements!
    // When lowerBound = 0: intervalSize = upperBound + 1!
    int intervalSize = upperBound - lowerBound + 1;
    int* count = new int[intervalSize];
    int* final = new int[n];

    for (int i = 0; i < n; i++)
    {
        count[arr[i] - lowerBound]++;
    }

    for (int i = 1; i < intervalSize; i++)
    {
        count[i] += count[i-1];
    }

    for (int i = n - 1; i >= 0; i--)
    {
        final[count[arr[i] - lowerBound] - 1] = arr[i];
        count[arr[i]]--;
    }

    for (int i = 0; i < n; i++)
    {
        arr[i] = final[i];
    }

    delete[] count;
    delete[] final;
}

int main()
{
    const int SIZE = 20;
    int arr[SIZE] = {100, 23, 11, 12, 3, 7, 11, 1, 24, 25,
                     11, 65, 11, 2,  4, 15, 9, 18, 0, 67};
    
    MergeSort(arr, SIZE);
    // QuickSort(arr, SIZE);
    // CountingSort(arr, SIZE, 0, 100);

    for (int i = 0; i < SIZE; i++)
    {
        std::cout << arr[i] << ' ';
    }
    
}
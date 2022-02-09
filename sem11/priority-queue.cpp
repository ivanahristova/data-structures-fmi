#include <iostream>
#include <stdexcept>
#include <vector>

template <typename T>
class PriorityQueue
{
    struct Node
    {
        T data;
        int ts;

        Node(T data, int ts) : data(data), ts(ts) {}

        bool operator<(const Node& other) const
        {
            if (data < other.data)
            {
                return true;
            }

            if (data == other.data)
            {
                return ts < other.ts;
            }

            return false;
        }
    };

    std::vector<Node*> data;
    int ts = 0;

private:

    void copy(const PriorityQueue<T>& other);
    void free();

    int leftChild(int i) const;
    int rightChild(int i) const;
    int parent(int i) const;

    void heapify(int index);
    void print(int i) const;

public:
    PriorityQueue() = default;
    PriorityQueue(const std::vector<T>& v);
    PriorityQueue(const PriorityQueue<T>& other);
    PriorityQueue<T>& operator=(const PriorityQueue<T>& other);
    ~PriorityQueue();

    void push(T element);
    void pop();

    const T& top() const;
    bool empty() const;
    int getSize() const;
    void print() const;

};

template <typename T>
void PriorityQueue<T>::copy(const PriorityQueue<T>& other)
{
	ts = other.ts;

	for (int i = 0; i < other.data.size(); i++)
	{
        data.push_back(new Node(other.data[i]));
    }
}

template <typename T>
void PriorityQueue<T>::free()
{
    for (int i = 0; i < data.size(); i++)
    {
        delete data[i];
    }

    ts = 0;
}

template <typename T>
PriorityQueue<T>::PriorityQueue(const std::vector<T>& v)
{
    int size = v.size();
    for (int i = 0; i < size; i++)
    {
        push(v[i]);
        // data.push_back(new Node(v[i], ts++));
    }

    // to do
    // rearrange elements
    // heapify()
}

template <typename T>
PriorityQueue<T>::PriorityQueue(const PriorityQueue<T>& other)
{
    copy(other);
}

template <typename T>
PriorityQueue<T>& PriorityQueue<T>::operator=(const PriorityQueue<T>& other)
{
    if (this != &other)
    {
        free();
        copy(other);
    }
    return *this;
}

template <typename T>
PriorityQueue<T>::~PriorityQueue()
{
    free();
}

// 0 | 1 2 | 3 4 | 5 6 | 7

template <typename T>
int PriorityQueue<T>::leftChild(int i) const
{
    return 2*i + 1;
}

template <typename T>
int PriorityQueue<T>::rightChild(int i) const
{
    return 2*i + 2;
}

template <typename T>
int PriorityQueue<T>::parent(int i) const
{
    return (i - 1) / 2;
}

template <typename T>
void PriorityQueue<T>::heapify(int index)
{
    bool hasMoves = true;

    while(hasMoves)
    {
        int left = leftChild(index);
        int right = rightChild(index);

        bool toLeft = left < data.size() && *data[index] < *data[left];
        bool toRight =  right < data.size() && *data[index] < *data[right];
    
        if (!toLeft && !toRight)
        {
            hasMoves = false;
        }
        else if (toLeft && !toRight)
        {
            std::swap(data[index], data[left]);
            index = left;
        }
        else if (!toLeft && toRight)
        {
            std::swap(data[index], data[right]);
            index = right;
        }
        else
        {
            if (*data[left] < *data[right])
            {
                std::swap(data[index], data[right]);
                index = right;
            }
            else
            {
                std::swap(data[index], data[left]);
                index = left;
            }
        }
    }
}


template <typename T>
void PriorityQueue<T>::push(T element)
{
    Node* newNode = new Node(element, ts++);
    data.push_back(newNode);

    int index = data.size() - 1;
    int parentIndex = parent(index);

    while (index > 0 && *data[parentIndex] < *data[index])
    {
        std::swap(data[index], data[parentIndex]);
        index = parentIndex;
        parentIndex = parent(index);
    }
}

template <typename T>
void PriorityQueue<T>::pop()
{
    if (data.size() == 0)
    {
        return;
    }

    if (data.size() == 1)
    {
        delete data[0];
        ts = 0;
        return;
    }

    delete data[0];
    data[0] = data[data.size() - 1];
    data.pop_back();

    heapify(0);
}

template <typename T>
const T& PriorityQueue<T>::top() const
{
    if (data.size() == 0)
    {
        throw std::runtime_error("Top called on an empty priority queue.");
    }

    return data[0]->data;
}

template <typename T>
bool PriorityQueue<T>::empty() const
{
    return data.empty();
}

template <typename T>
int PriorityQueue<T>::getSize() const
{
    return data.size();
}

template <typename T>
void PriorityQueue<T>::print(int i) const
{
    if (i >= data.size())
    {
        return;
    }

    std::cout << '(';
    print(leftChild(i));
    std::cout << data[i]->data;
    print(rightChild(i));
    std::cout << ')';
}

template <typename T>
void PriorityQueue<T>::print() const
{
    print(0);
}

int main()
{
    std::vector<int> v{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    PriorityQueue<int> pq(v);
	pq.print();
	std::cout << "\n\n";

    pq.push(100);
	std::cout << "Insert new biggest element 100:\n";
	pq.print();
	std::cout << "\n\n";

	std::cout << "Pop:\n";
	pq.pop();
	pq.print();
}
#include <iostream>
#include <unordered_map>
#include <vector>
#include <unordered_set>

struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int data) 
        : data(data), left(nullptr), right(nullptr) {}
};

void leftLook(Node* root, int level, std::unordered_map<int, int>& m)
{
    if (root == nullptr) 
    {
        return;
    }

    if (m.find(level) == m.end()) 
    {
        m[level] = root->data;
    }

    leftLook(root->left, level + 1, m);
    leftLook(root->right, level + 1, m);
}

void leftLook(Node* root)
{
    std::unordered_map<int, int> m;
    leftLook(root, 0, m);
    int size = m.size();
    for (int i = 0; i < size; i++)
    {
        std::cout << m.at(i) << " ";
    }
    std::cout << std::endl;
}

bool existsZeroSumSub(const std::vector<int>& numbers)
{
    std::unordered_set<int> sums;
    int sum = 0;

    int size = numbers.size();
    for (int i = 0; i < size; i++)
    {
        sum += numbers[i];

        // - Дадена сума съществува, то сме намерили подвектор със сума 0.
        // - Ако намерим сума 0.
        if (sum == 0 || sums.find(sum) != sums.end())
        {
            return true;
        }

        sums.insert(sum);
    }
    
    return false;
}

void printPairs(const std::vector<int>& v, int k)
{
    int size = v.size();
    std::unordered_set<int> elements;

    for (int i = 0; i < size; i++)
    {
        if (elements.find(v[i] - k) != elements.end()) 
        {
            std::cout << v[i] - k << " , " << v[i] << std::endl;
        } 

        if (elements.find(v[i] + k) != elements.end())
        {
            std::cout << v[i] + k << " , " << v[i] << std::endl;
        }

        elements.insert(v[i]);
    }
}

bool comparator(const std::tuple<int, int, int>& lhs, const std::tuple<int, int, int>& rhs)
{
    if (std::get<1>(lhs) == std::get<1>(rhs))
    {
        return std::get<2>(lhs) < std::get<2>(rhs);
    }

    return std::get<1>(lhs) > std::get<1>(rhs);
}

void sortByFeqAndIndex(std::vector<int>& v)
{
    int size = v.size();
    if (size < 2)
    {
        return;
    }

    std::unordered_map<int, std::pair<int, int>> histogram;

    for (int i = 0; i < size; i++)
    {
        if (histogram.find(v[i]) != histogram.end())
        {
            histogram[v[i]].first++;
        }
        else
        {
            histogram[v[i]] = {1, i};
        }
    }
    
    std::vector<std::tuple<int, int, int>> result;
    for (auto it : histogram)
    {
        result.push_back(std::make_tuple(it.first, it.second.first, it.second.second));
    }
    
    std::sort(result.begin(), result.end(), comparator);

    for (int i = 0; i < size; i++)
    {
        v[i] = std::get<0>(result[i]);
    }
}
 
int main()
{
    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->right->left = new Node(5);
    root->right->right = new Node(6);
    root->right->left->left = new Node(7);

    leftLook(root);

    std::vector<int> zeroSumFalse = {1, 2, 3, 4};
    std::cout << std::boolalpha << existsZeroSumSub(zeroSumFalse) << std::endl;

    std::vector<int> zeroSumTrue = {5, 1, 2, -3, 4};
    std::cout << std::boolalpha << existsZeroSumSub(zeroSumTrue) << std::endl;

    std::vector<int> v = {1, 5, 2, 4};
    int k = 3;
    printPairs(v, k);

}

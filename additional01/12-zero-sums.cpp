#include <iostream>
#include <stack>

struct Node
{
    int data;
	Node* next;
	
    Node(int data, Node* next) 
        : data(data), next(next){}
};

Node* filterZeroSums(Node* head)
{
	Node* iter = head;

	std::stack<Node*> st;

	while (iter != nullptr)
	{
		std::stack<Node*> copy = st;
		int currentSum = iter->data;

		bool deleted = false;

		while (!copy.empty() && !deleted)
		{
			Node* temp = copy.top();
			copy.pop();
			currentSum += temp->data;

			if (currentSum == 0)
			{
				deleted = true;

				if (temp == head)
				{
					head = iter->next;
					iter = head;
				}
				else
				{
					copy.top()->next = iter->next;
					iter = iter->next;
				}

				int deletedCount = 0;
				while (temp != iter)
				{
					Node* toDelete = temp;
					temp = temp->next;
					deletedCount++;
					delete toDelete;
				}

				while (--deletedCount > 0)
				{
                    st.pop();
                }
			}

		}

		if (!deleted)
		{
			st.push(iter);
			iter = iter->next;
		}
	}

	return head;
}

void print(Node* list)
{
	while (list != nullptr)
	{
		std::cout << list->data << ' ';
		list = list->next;
	}
}

int main()
{
	Node* list1 = new Node(99, new Node(3, new Node(-3, new Node(6, new Node(-10, new Node(4, new Node(8, new Node(6, new Node(2, new Node(-8, nullptr))))))))));
    Node* list2 = new Node(10, new Node(1, new Node(2, new Node(3, new Node(6, new Node(-3, new Node(-3, new Node(-3, new Node(-3, nullptr)))))))));
    
    print(filterZeroSums(list1));
    std::cout << '\n';
    print(filterZeroSums(list2));
}
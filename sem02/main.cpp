#include <iostream>
#include "array-stack.hpp"

int main()
{
    ArrayStack<int> st;
    std::cout << st.empty() << '\n';
    st.push(23);
    st.push(11);
    st.push(12);
    std::cout << st.getSize() << ' ' << st.top() << '\n';
    st.pop();
    std::cout << st.getSize() << ' ' << st.top() << '\n';
    st.pop();
    std::cout << st.getSize() << ' ' << st.top() << '\n';
    st.pop();
    std::cout << st.empty() << '\n';
}
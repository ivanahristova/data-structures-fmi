#include <iostream>
#include <stack>
#include <string>

#include "linked-stack.hpp"

// ({()[]}

// st -> ( ? 

// {})))} 
// st -> 

// )(

bool validateParenthesesSymbols(std::string parentheses)
{
    int length = parentheses.length();
    bool valid = true;
    for (int i = 0; i < length && valid; i++)
    {
        char current = parentheses[i];
        if (current != '(' && current != ')' && 
            current != '{' && current != '}' &&
            current != '[' && current != ']')
        {
            valid = false;
        }
    }
    return valid;
}

bool isBalanced(std::string parentheses)
{
    if (!validateParenthesesSymbols(parentheses))
    {
        return false;
    }
    
    int length = parentheses.length();
    std::stack<char> openingBrackets;

    for (int i = 0; i < length; i++)
    {
        char curr = parentheses[i];

        if (curr == '(' || curr == '{' || curr == '[')
        {
            openingBrackets.push(curr);
            continue;
        }
        if (openingBrackets.empty())
        {
            return false;
        }
        
        if ((curr == ')' && openingBrackets.top() != '(') ||
            (curr == '}' && openingBrackets.top() != '{') ||
            (curr == ']' && openingBrackets.top() != '['))
        {
            return false;
        }

        openingBrackets.pop();
    }
    return openingBrackets.empty();
}

bool isDigit(char c)
{
    return c >= '0' && c <= '9';
}

void rpnHelper(char c, std::stack<double>& number)
{
    double right = number.top();
    number.pop();
    double left = number.top();
    number.pop();

    switch (c)
    {
    case '+': number.push(left + right);
        break;
    case '-': number.push(left - right);
        break;
    case '*': number.push(left * right);
        break;
    case '/': number.push(left / right);
        break;

    default:
        std::invalid_argument("Invalid symbol");
        break;
    }
}

double rpnCalc(std::string input) // valid input in rpn
{
    int inputLength = input.length();
    std::stack<double> numbers;

    for (int i = 0; i < inputLength; i++)
    {
        if (input[i] == ' ')
        {
            continue;
        }

        if (isDigit(input[i]))
        {
            int number = 0;

            while (i < inputLength && isDigit(input[i]))
            {
                number *= 10;
                number += (int)input[i++] - '0';
            }
            numbers.push(number);
        }
        else
        {
            rpnHelper(input[i], numbers);
        }
    }
    return numbers.top();
}

int main()
{
    LinkedStack<int> st1;
    st1.push(12);
    st1.push(21);
    st1.push(11);
    LinkedStack<int> st2(st1);
    
    int st1Size = st1.getSize();
    for (int i = 0; i < st1Size; i++)
    {
        st1.pop();
    }
    
    st1.push(33);
    st1.push(23);
    st1.push(13);

    LinkedStack<int> st3;
    st3.push(12);
    st3 = st1;

    st3.print();

    st1.reverse();
    st1.print();
    st2.reverse();
    st2.print();

    std::cout << "((): " << isBalanced("(()") << '\n'
              << "[{[]}()]: " << isBalanced("[{[]}()]") << '\n'
              << "[([](){[()[]]})()]: " << isBalanced("[([](){[()[]]})()]") << '\n'
              << "[{}(]): " << isBalanced("[{}(])") << '\n'
              << "[{({}(]))}: " << isBalanced("[{({}(]))}") << '\n';

    std::cout << rpnCalc("15 7 1 1 + - / 3 * 2 1 1 + + -") << '\n';
}
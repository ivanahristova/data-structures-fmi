#include <iostream>
#include <stack>
#include <string>

/*
Нека имаме 2 стека: numbers и operators

1. Докато имаме символи в израза - прочитаме следващия символ:
	1.1. Ако е число – добавяме стойността му в numbers
	1.2. Ако е оператор – докато operators не е празен и приоритета на операцията на върха му е по-висок или равен на сегашната:
		1.2.1. Взимаме оператора operators
		1.2.2. Взимаме две стойности numbers
		1.2.3. Прилагаме оператора
		1.2.4. Добавяме резултатата в стека
	1.3. Ако е лява скоба – добавяме я в operators
	1.4. Ако е дясна скоба - докато на върха на operators нямаме лява скоба:
		1.4.1. Взимаме оператора на върха на operators
		1.4.2. Взимаме 2 операнди от numbers
		1.4.3. Прилагаме оператора
		1.4.4. Добавяме получения резултат в numbers

2. Докато operators не е празен:
	2.1. Взимаме операцията на върха на operators
	2.2. Взимаме две стойности от numbers
	2.3. Добавяме резултата от прилагането на операцията в numbers

3. Последната стойност в стека е резултата

*/

bool isDigit(char c)
{
    return c >= '0' && c <= '9';
}

bool isOperator(char c)
{
    return c == '+' || c == '-' || c == '*' || c == '/';
}

int getPrecedence(char op)
{
    switch (op)
    {
    case '-': return 1;
    case '+': return 1;
    case '*': return 2;
    case '/': return 2;
    default: return 0;
    }
}

int getOperationResult(int left, int right, char op)
{
    switch (op)
    {
    case '-': return left - right;
    case '+': return left + right;
    case '*': return left * right;
    case '/': return left / right;
    default: return 0;
    }
}

void evaluateCurrent(std::stack<int>& numbers, std::stack<char>& operators)
{
    int right = numbers.top();
    numbers.pop();

    int left = numbers.top();
    numbers.pop();

    char op = operators.top();
    operators.pop();

    numbers.push(getOperationResult(left, right, op));
}

int evaluate(std::string expr)
{
    std::stack<int> numbers;
    std::stack<char> operators;

    int exprLength = expr.length();

    for (int i = 0; i < exprLength; i++)
    {
        if (isDigit(expr[i]))
        {
            int number = 0;

            while (i < exprLength && isDigit(expr[i]))
            {
                number *= 10;
                number += (int)expr[i] - '0';
                i++;
            }

            numbers.push(number);
            i--;
        }
        else if (isOperator(expr[i]))
        {
            while (!operators.empty() && getPrecedence(operators.top()) >= getPrecedence(expr[i]))
            {
                evaluateCurrent(numbers, operators);
            }

            operators.push(expr[i]);
        }
        else if (expr[i] == '(')
        {
            operators.push(expr[i]);
        }
        else if (expr[i] == ')')
        {
            while (!operators.empty() && operators.top() != '(')
            {
                evaluateCurrent(numbers, operators);
            }

            if (!operators.empty())
            {
                operators.pop();
            }
        }
    }

    while (!operators.empty())
    {
        evaluateCurrent(numbers, operators);
    }

    return numbers.top();    
}


int main()
{
    std::cout << evaluate("20+1*6") << '\n';
    std::cout << evaluate("15*2+2") << '\n';
    std::cout << evaluate("2*(2+12)") << '\n';
    std::cout << evaluate("3*(14*14+5)/14") << '\n';
}

#include <iostream>
#include <vector>
#include<stack>
#include <string> 
#include <windows.h>
#include <conio.h>



 


void numberFinder(std::string &userInput, std::string &output, int index) {
    if (userInput[index] >= 48 && userInput[index] <= 57 || userInput[index] == 56)
        output.push_back(userInput[index]);
    else
        output.push_back(' ');
}

void operatorFinder(std::string &userInput, std::string &output, std::stack<char> &operatorStack, std::stack <int> &operatorPrecendence, int index) {
  
    
    if (userInput[index] == '+' || userInput[index] == '-' || userInput[index] == '*' || userInput[index] == '/' || userInput[index] == '^' || userInput[index] == 'r') {
        int tempPrecendence;
        if (userInput[index] == '+' || userInput[index] == '-') {
            tempPrecendence = 2;
        }
        else if (userInput[index] == '*' || userInput[index] == '/') {
            tempPrecendence = 3;
        }
        else if (userInput[index] == '^' || userInput[index] == 'r') {
            tempPrecendence = 4;
        }

        while (operatorPrecendence.size() > 0 && operatorPrecendence.top() >= tempPrecendence && operatorPrecendence.top() != 4 &&  operatorStack.size() > 0 && operatorStack.top() != '(')
        {
            output.push_back(' ');
            output.push_back(operatorStack.top());
            operatorStack.pop();
            operatorPrecendence.pop();
        }
        operatorStack.push(userInput[index]);
        operatorPrecendence.push(tempPrecendence);

    }
    else if (userInput[index] == '(') {
        operatorStack.push('(');
    }
    else if (userInput[index] == ')') {
        while (operatorStack.top() != '(') {
            if (operatorStack.size() > 0) {
                output.push_back(' ');
                output.push_back(operatorStack.top());
                operatorStack.pop();
            }
            else
                std::cout << "incorrect expression, mismatched parentheses \n";
        }
        if (operatorStack.top() == '(') {
            operatorStack.pop();
        }
    }
    while (index == userInput.size() - 1 && operatorStack.size() > 0) {
        output.push_back(' ');
        output.push_back(operatorStack.top());
        operatorStack.pop();
    }
}

std::string parser(std::string &userInput) {
    std::string output;
    std::stack <char> operatorStack;
    std::stack <int> operatorPrecedence;
    int index;

    for (int i = 0; i < userInput.size(); i++) {
        numberFinder(userInput, output, i);
        operatorFinder(userInput, output, operatorStack, operatorPrecedence, i);
    }
    return output;
}

double calculate(double a, double b, char operator_) {
    switch (operator_)
    {
    case '+':
        return a + b;
    case '-':
        return a - b;
    case '*':
        return a * b;
    case '/':
        return a / b;
    case '^':
        return pow(a, b);
    case 'r':
        return pow(b, 1/ a);
    }
}



int prnParser(std::string &output, std::stack <double> &rpnStack) {
    std::string number;
    float a, b;
    for (int i = 0; i < output.size(); i++) {
       
        
        if (output[i] >= 48 && output[i] <= 57 || output[i] == 56) {
            number.push_back(output[i]);
        
            if (number.size() > 0 && output[i+1] == ' ') {
                rpnStack.push(stod(number));
                number.clear();
            }
        }
        else if (output[i] == '+' || output[i] == '-' || output[i] == '*' || output[i] == '/' || output[i] == '^' || output[i] == 'r') {
            a = rpnStack.top();
            rpnStack.pop();
            b = rpnStack.top();
            rpnStack.pop();
            rpnStack.push(calculate(b, a, output[i]));
        }  
    }
    if (rpnStack.size() != 1)
    {
        return -1;
    }
}

void help() {
    std::cout << "addition:        substraction:    multiplication:  division:   " << std::endl;
    std::cout << "4 + 10           20 - 4           7 * 8            15 / 3      " << std::endl;
    std::cout << "power:           root:                                         " << std::endl;
    std::cout << "5 ^ 2 (five to 2nd power)         2 r 9 (squre root of 9)      " << std::endl;
    std::cout << "---------------------------------------------------------------" << std::endl;
    std::cout << "You can join operations for bigger expressions with parenthesis" << std::endl;
    std::cout << "i. e. 3 + 4 * 2 /(1 - 5) ^ 2 ^ 3                               " << std::endl;

}

void welcomePromt() {
    std::cout << "==============Welcome to Not So Simple Calculator==============" << std::endl;
    std::cout << "---------------------------------------------------------------" << std::endl;
    std::cout << "Type expression to calculate or:" << std::endl;
    std::cout << "Type ""help"" to see the example expression or ""exit"" to quit" << std::endl;
    std::cout << "---------------------------------------------------------------" << std::endl;
}


int main() {
    std::stack <double> rpnStack;
    std::string input;
    

    while (input != "exit") {
        system("cls");
        welcomePromt();
        getline (std::cin, input);
        if (input == "help") {
            help();
            std::cin >> input;
        }
        std::string rpn = parser(input);

        if (prnParser(rpn, rpnStack) == -1) {
            system("cls");
            welcomePromt();
            std::cout << input << " <- Incorrect expression, Try again. \n";
            Sleep(3000);
        }
        else {
            system("cls");
            welcomePromt();
            std::cout << input << " = " << rpnStack.top() << std::endl;
            std::cout << "press any key to continue" << std::endl;
            _getch();
        }
    }
    return 0;
 

   // "3 + 4 * 2 /(1 - 5) ^ 2 ^ 3"
    //"5 * ((3 - 7) * 2 - 3 * (5 + 1)) - 3"
}
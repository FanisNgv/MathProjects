//оптимизация++
#include "Header.h"
#include <stdio.h>
#include<string.h>
#include <stdlib.h>
#include <stack>
#include <math.h>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <windows.h>

using namespace std;

std::ofstream out("out.txt", std::ios::app);

int k;
char n;
string LogicFunction;

stack<char> Operators;
stack<vector<int>> OperandsArrays;
stack<string> Operands;

bool lBracketFound = false;

template <typename T>
std::string toString(T val)
{
    std::ostringstream oss;
    oss << val;
    return oss.str();
}
inline bool isInteger(const std::string& s)
{
    if (s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+')))
        return false;

    char* p;
    strtol(s.c_str(), &p, 10);

    return (*p == 0);
}
void StackCalculateOV()
{
    if (OperandsArrays.empty() || Operators.empty()) // Если один из стеков пуст, то вычислять нечего
    {
        return;
    }    
    char opr = Operators.top(); // Извлекаем последний оператор
    vector<int> arr_1;
    vector<int> arr_2;
    switch (opr) // Смотрим, что это за оператор
    {
    case'*':
        arr_1 = OperandsArrays.top(); // Извлекаем массив-операнд
        OperandsArrays.pop();         // Удаляем вершину стека
        arr_2 = OperandsArrays.top(); // Извлекаем второй массив-операнд
        for (int i = 0; i < k; i++)
        {
            (OperandsArrays.top())[i] = (arr_1[i] * arr_2[i])%k; // Умножаем массивы поэлментно в рамках k-значной логики
        }
        Operators.pop(); // Извлекаем оператор, так как мы его только что использовали
        break;
    case'n':
        arr_1 = OperandsArrays.top();
        for (int i = 0; i < k; i++)
        {
            arr_1[i] = (arr_1[i] + 1) % k; // Для каждого элемента применяем отрицание Поста
        }
        OperandsArrays.top() = arr_1; // Изменяем верхний массив-операнд в стеке
        Operators.pop(); // Извлекаем оператор, так как мы его только что использовали
    case'(':
        lBracketFound = true; // Если обнаружили левую скобку, то меняем значение переменной lBracket. Дальше будет понятно, почему
        return;
        break;
    case')':
        Operators.pop(); // Если мы наткнулись на правую скобку (значит где-то была левая), то...
        lBracketFound = false; // Говорим, что левой скобки теперь нет, т.к. мы сейчас будем производить вычисления как раз до нее
        while (Operators.top() != '(') // Пока не дойдем до операции левая скобка, производим вычисления
        {
            if (Operators.top() == '*')
            {
                arr_1 = OperandsArrays.top();
                OperandsArrays.pop();
                arr_2 = OperandsArrays.top();
                for (int i = 0; i < k; i++)
                {
                    (OperandsArrays.top())[i] = (arr_1[i] * arr_2[i]) % k;
                }               
                Operators.pop();
            }
            else if (Operators.top() == 'n')
            {
                arr_1 = OperandsArrays.top();
                for (int i = 0; i < k; i++)
                {
                    arr_1[i] = (arr_1[i] + 1) % k;
                }
                OperandsArrays.top() = arr_1;
                Operators.pop();
            }  
            else
            {
                std::cout << "Ошибка ввода!";
                return;
            }
        }
        Operators.pop(); // Извлекаем левую скобку
        if (Operators.top() == 'n') // Случай, если оператор not
        {
            arr_1 = OperandsArrays.top();
            for (int i = 0; i < k; i++)
            {
                arr_1[i] = (arr_1[i] + 1) % k;
            }
            OperandsArrays.top() = arr_1;
            Operators.pop();
        }
        if (Operators.empty() != true && Operators.top() == '-') // Случай, если у нас минус
        {            
            arr_1 = OperandsArrays.top();
            for (int i = 0; i < k; i++)
            {
                arr_1[i] = -arr_1[i];
            }            
            OperandsArrays.top() = arr_1;
            Operators.pop();
        }
        break;
    default:
        break;
    }
}
void StackCalculateTV()
{
    // Единственное отличие StackCalculateTV от StackCalculateOV в том, что массивы-операнды приобретают размер k^2
    if (OperandsArrays.empty() || Operators.empty())
    {
        return;
    }
    char opr = Operators.top();
    vector<int> arr_1;
    vector<int> arr_2;
    switch (opr)
    {
    case'*':
        arr_1 = OperandsArrays.top();
        OperandsArrays.pop();
        arr_2 = OperandsArrays.top();
        for (int i = 0; i < k*k; i++) 
        {
            (OperandsArrays.top())[i] = (arr_1[i] * arr_2[i]) % k;
        }
        Operators.pop();
        break;
    case'n':
        arr_1 = OperandsArrays.top();
        for (int i = 0; i < k*k; i++)
        {
            arr_1[i] = (arr_1[i] + 1) % k;
        }
        OperandsArrays.top() = arr_1;
        Operators.pop();
    case'(':
        lBracketFound = true;
        return;
        break;
    case')':
        Operators.pop();
        lBracketFound = false;
        while (Operators.top() != '(')
        {
            if (Operators.top() == '*')
            {
                arr_1 = OperandsArrays.top();
                OperandsArrays.pop();
                arr_2 = OperandsArrays.top();
                for (int i = 0; i < k*k; i++)
                {
                    (OperandsArrays.top())[i] = (arr_1[i] * arr_2[i]) % k;
                }
                Operators.pop();
            }
            else if (Operators.top() == 'n')
            {
                arr_1 = OperandsArrays.top();
                for (int i = 0; i < k*k; i++)
                {
                    arr_1[i] = (arr_1[i] + 1) % k;
                }
                OperandsArrays.top() = arr_1;
                Operators.pop();
            }
            else
            {
                std::cout << "Ошибка ввода!";
                return;
            }
        }
        Operators.pop();
        if (Operators.top() == 'n')
        {
            arr_1 = OperandsArrays.top();
            for (int i = 0; i < k*k; i++)
            {
                arr_1[i] = (arr_1[i] + 1) % k;
            }
            OperandsArrays.top() = arr_1;
            Operators.pop();
        }
        if (Operators.empty() != true && Operators.top() == '-')
        {
            arr_1 = OperandsArrays.top();
            for (int i = 0; i < k*k; i++)
            {
                arr_1[i] = -arr_1[i];
            }
            OperandsArrays.top() = arr_1;
            Operators.pop();
        }
        break;
    default:
        break;
    }
}
vector<int> FuncProcessingOV(string function)
{
    int lBracket = 0; // Подсчет количества скобок, чтобы в конце провести проверку на равенство этих переменных
    int rBracket = 0;   
    out << "x\t" << "f(x) = " << function << std::endl;
    std::cout << "x\t" << "f(x) = " << function << std::endl;
    try
    {
        for (int i = 0; i < function.length(); i++)
        {
            if (function[i] == '(' || function[i] == ')' || function[i] == '*')
            {
                Operators.push((function[i]));
                if (function[i] == ')')
                {
                    StackCalculateOV(); // Вызываем функцию, только если наткнулись на правую скобку
                    rBracket++;
                }
                else if (function[i] == '(')
                {
                    lBracket++;
                }
                    
            }
            // Если это число, либо минус перед скобкой/числом
            else if (('0' <= function[i] && function[i] <= '9') || (i+1<=function.length()&& function[i] == '-' && function[i + 1] != 'x'))
            {
                std::vector<char> symbols;
                string str;
                if (function[i] == '-') //Если это минус
                {
                    str += '-';
                    if (function[i + 1] != '(') // Минус оператор только в случае, если дальше идет скобка
                        i++;                    // Переходим к числу
                    else
                    {
                        Operators.push(str[0]);
                        continue;
                    }
                }
                // Начиная отсюда конвертируем строку в число и заполняем массив-операнд
                int j = i;
                while ('0' <= function[j] && function[j] <= '9')
                {
                    i = j;
                    str += function[j];                    
                    j++;
                }
                vector<int> arr;
                for (int i = 0; i < k; i++)
                {
                    arr.push_back(stoi(str));
                }
                OperandsArrays.push(arr);

                if (!lBracketFound) // Если левой скобки не было, то высчитываем
                {
                    StackCalculateOV();
                }
            }
            // Если это оператор not
            else if (i + 2 <= function.length() && function[i] == 'n' && function[i + 1] == 'o' && function[i + 2] == 't')
            {
                i += 2;
                Operators.push('n');
            }
            // Если наткнулись на переменную
            else if (function[i] == 'x')
            {
                if (i!=0 && function[i - 1] == '-') // Если перед иксом стоял минус, то соотв. образом заполняем массив-операнд для переменной
                {                   
                    std::vector<int> arr;
                    for (int i = 0; i < k; i++)
                    {
                        arr.push_back(-i);
                    }
                    OperandsArrays.push(arr);
                }
                else                                // Иначе просто заполняем массив от 0 до k-1
                {
                    std::vector<int> arr;
                    for (int i = 0; i < k; i++)
                    {
                        arr.push_back(i);
                    }
                    OperandsArrays.push(arr);
                }
                if (!lBracketFound)                 // Если левой скобки не было, то высчитываем
                {
                    StackCalculateOV();
                }
            }
            else if (function[i] == '-')
            {

            }
            else
            {
                std::cout << "Ошибка ввода!";
                abort();
            }
        }
        if (lBracket != rBracket)
        {
            std::cout << "Ошибка ввода!";
            abort();
        }
        while (OperandsArrays.size() > 1) // Если количество операндов больше 1, то продолжаем вычисления
        {
            StackCalculateOV();
        }
        for (int i = 0; i < k; i++)      // Помещаем значения функции в рамки к-ой логики
        {
            while ((OperandsArrays.top())[i] < 0)
            {
                OperandsArrays.top()[i] += k;
            }
            OperandsArrays.top()[i] = OperandsArrays.top()[i] % k;
        }
        for (int i = 0; i < k; i++)
        {
            std::cout << i << '\t' << (OperandsArrays.top())[i] << std::endl;
            out << i << '\t' << (OperandsArrays.top())[i] << std::endl;
        }
        return OperandsArrays.top();
    }
    catch (...)
    {
        std::cout << "Ошибка ввода!";
        abort();
    }    
}
vector<int> FuncProcessingTV(string function)
{
    int lBracket = 0;
    int rBracket = 0;

    std::vector<int> arr_y;
    std::vector<int> arr_x;

    int numerator = 0;              // Создаем шаблон для массива-операнда переменной х
    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < k; j++)
        {
            arr_x.push_back(numerator);
        }
        numerator++;
    }
    numerator = 0;
    for (int i = 0; i < k; i++)     // Создаем шаблон для массива-операнда переменной y
    {
        for (int j = 0; j < k; j++)
        {
            arr_y.push_back(numerator);
            numerator++;
        }
        numerator = 0;
    }
    std::cout << "x\ty\t" << "f(x,y) = " << function << std::endl;
    out << "x\ty\t" << "f(x,y) = " << function << std::endl;
    try
    {
        for (int i = 0; i < function.length(); i++)
        {
            if (function[i] == '(' || function[i] == ')' || function[i] == '*')
            {
                Operators.push((function[i]));
                if (function[i] == ')')
                    StackCalculateTV();
            }
            else if (('0' <= function[i] && function[i] <= '9') || function[i] == '-' && (function[i + 1] != 'x' && function[i + 1] != 'y'))
            {
                std::vector<char> symbols;
                string str;
                if (function[i] == '-')
                {
                    str += '-';
                    if (function[i + 1] != '(')
                        i++;
                    else
                    {
                        Operators.push(str[0]);
                        continue;
                    }
                }
                int j = i;
                while ('0' <= function[j] && function[j] <= '9')
                {
                    i = j;
                    str += function[j];
                    j++;
                }
                vector<int> arr;
                for (int i = 0; i < k * k; i++)
                {
                    arr.push_back(stoi(str));
                }
                OperandsArrays.push(arr);
                Operands.push(str);
                if (!lBracketFound)
                {
                    StackCalculateTV();
                }
            }
            else if (i + 2 <= function.length() && function[i] == 'n' && function[i + 1] == 'o' && function[i + 2] == 't')
            {
                i += 2;
                Operators.push('n');
            }
            else if (function[i] == 'x')
            {
                if (i != 0 && function[i - 1] == '-')
                {
                    std::vector<int> arr = arr_x;
                    for (int i = 0; i < k*k; i++)
                    {
                            arr[i] = -arr[i];                        
                    }
                    OperandsArrays.push(arr);
                }
                else
                {
                    std::vector<int> arr = arr_x;
                    OperandsArrays.push(arr);
                }
                if (!lBracketFound)
                {
                    StackCalculateTV();
                }
            }
            else if (function[i] == 'y')
            {
                if (i != 0 && function[i - 1] == '-')
                {
                    std::vector<int> arr = arr_y;
                    for (int i = 0; i < k*k; i++)
                    {
                            arr[i] = -arr[i];                     
                    }
                    OperandsArrays.push(arr);
                }
                else
                {
                    std::vector<int> arr = arr_y;                    
                    OperandsArrays.push(arr);
                }
                if (!lBracketFound)
                {
                    StackCalculateTV();
                }
            }
        }
        if (lBracket != rBracket)
        {
            std::cout << "Ошибка ввода!";
            abort();
        }
        while (OperandsArrays.size() > 1)
        {
            StackCalculateTV();
        }
        for (int i = 0; i < k * k; i++)
        {
            while ((OperandsArrays.top())[i] < 0)
            {
                (OperandsArrays.top())[i] += k;
            }
        }
        for (int i = 0; i < k * k; i++)
        {
            std::cout << arr_x[i] << '\t';
            std::cout << arr_y[i] << '\t';
            std::cout << (OperandsArrays.top())[i] << std::endl;

            out << arr_x[i] << '\t';
            out << arr_y[i] << '\t';
            out << (OperandsArrays.top())[i] << std::endl;
        }
        return OperandsArrays.top();
    }
    catch (...)
    {
        std::cout << "Ошибка ввода!";
        abort();
    }
}
void MainMenu()
{      
    std::cout << 
        "Программа разработана Нигамадяновым Ф.М., гр 4210\n\n"<< 
        "Руководство пользователя:\nХарактеристическую функцию первого рода будем обозначать следующим образом - j_i(x)\n" <<
        "Числа множества Е для проверки вводить через пробел\n" <<
        "Отрицание Поста оформляется в виде not(x)\n" <<
        "Умножение в рамках k-ой логики обозначать будем *\n" <<
        "В функции одной переменной в качестве переменной вводить x(!)\n"<<        
        "В функции двух переменных в качестве переменных использовать только x и y(!)\n\n";
    while (k < 2 || k > 20)
    {
        std::cout << "Введите число k (от 2 до 20), чтобы определить количество значений в вашей логике: " << std::endl;
        k = intinput();
    }
    std::cout << "Число k принято!" << std::endl;
    while (n != '1' && n!= '2')
    {
        std::cout << "Введите количество значимых переменных. 1 или 2: " << std::endl;
        n = charinput();
    }
    std::cout << "Число n принято!" << std::endl;
    vector<int> vect;    
    std::vector<int> arr_x;
    std::vector<int> arr_y;
    string E;
    std::vector<string> E_SETstr;
    std::vector<int> E_SETint;
    int numerator = 0;
    bool SavesTheSet = true;
    switch (n)
    {
    case '1':
        std::cout << "Введите функцию" << std::endl;
        std::cin >> LogicFunction;
        vect = FuncProcessingOV(LogicFunction);     
 
        for (int i = 0; i < k; i++)
        {
            for (int j = 0; j < k; j++)
            {
                arr_x.push_back(numerator);
            }
            numerator++;
        }
        numerator = 0;
        for (int i = 0; i < k; i++)
        {
            for (int j = 0; j < k; j++)
            {
                arr_y.push_back(numerator);
                numerator++;
            }
            numerator = 0;
        }
        std::cout << "Вторая форма этой функции: ";
        out << "Вторая форма этой функции: ";
        for (size_t i = 0; i < k; i++)
        {
            if (vect[i] == 0)
            {
                continue;
            }
            std::cout << vect[i] << "*j_" << i << "(x) + ";
            out << vect[i] << "*j_" << i << "(x) + ";
        }
        std::cout << '\b' << " " << '\b';
        std::cout << '\b' << " " << '\b';
        std::cout << '\b' << " " << '\b';
        std::cout << '\n';
        out << '\b' << " " << '\b' << '\b' << " " << '\b' << '\b' << " " << '\b' << '\n';
        std::cout << "Введите множество E через пробел для проверки сохранения функции этого множества (введите числа от 0 до " << k - 1 <<" ):\n";
        
        p1:
        while (true)
        {
            cin>>E;

            E_SETstr.push_back(E);
            if (cin.peek() == '\n')
            {            
                std::cin.clear();
                break;
            }
        }        
        for (size_t i = 0; i < E_SETstr.size(); i++)
        {
            E_SETint.push_back(stoi(E_SETstr[i]));
            if (E_SETint[i] >= k || E_SETint[i] < 0)
            {
                std::cout << "Проверьте правильность введенных данных!" << std::endl;
                E_SETint.clear();
                E_SETstr.clear();
                goto p1;
            }
        }       
        for (size_t i = 0; i < k; i++)
        {
            if ((std::find(E_SETint.begin(), E_SETint.end(), arr_x[i]) != E_SETint.end()) && !(std::find(E_SETint.begin(), E_SETint.end(), vect[i]) != E_SETint.end()))
            {
                std::cout << "Функция не сохраняет заданное множество E = (";
                out << "Функция не сохраняет заданное множество E = (";
                for (size_t i = 0; i < E_SETint.size(); i++)
                {
                    std::cout << E_SETint[i] << ", ";
                    out << E_SETint[i] << ", ";
                }
                std::cout << '\b' << " " << '\b';
                std::cout << '\b' << " " << '\b';
                std::cout << ")";
                out << '\b' << " " << '\b' << '\b' << " " << '\b' << ")";
                SavesTheSet = false;
                break;
            }
        }
        if (SavesTheSet)
        {
            std::cout << "Функция сохраняет заданное множество E = (";
            out << "Функция сохраняет заданное множество E = (";
            for (size_t i = 0; i < E_SETint.size(); i++)
            {
                std::cout << E_SETint[i] << ", ";
                out << E_SETint[i] << ", ";
            }
            std::cout << '\b' << " " << '\b';
            std::cout << '\b' << " " << '\b';
            std::cout << ")";
            out << '\b' << " " << '\b' << '\b' << " " << '\b' << ")";
        }

        break;       
    case'2':
        std::cout << "Введите функцию" << std::endl;
        std::cin >> LogicFunction;
        vect = FuncProcessingTV(LogicFunction);       
        
        for (int i = 0; i < k; i++)
        {
            for (int j = 0; j < k; j++)
            {
                arr_x.push_back(numerator);
            }
            numerator++;
        }
        numerator = 0;
        for (int i = 0; i < k; i++)
        {
            for (int j = 0; j < k; j++)
            {
                arr_y.push_back(numerator);
                numerator++;
            }
            numerator = 0;
        }
        std::cout << "Вторая форма этой функции: ";
        out << "Вторая форма этой функции: ";
        int z = 0;
        for (int i = 0; i < k; i++)
        {
            for (int j = 0; j < k; j++)
            {
                if (vect[z] == 0)
                {
                    z++;
                    continue;
                }
                std::cout << vect[z] << "*j_" << i << "(x)*j_" << j << "(y) + ";
                out << vect[z] << "*j_" << i << "(x)*j_" << j << "(y) + ";
                z++;                
            }            
        }
        std::cout << '\b' << " " << '\b';
        std::cout << '\b' << " " << '\b';
        std::cout << '\b' << " " << '\b';
        std::cout << "\n";
        out << '\b' << " " << '\b' << '\b' << " " << '\b' << '\b' << " " << '\b' << '\n';
        std::cout << "Введите множество E через пробел для проверки сохранения функции этого множества (введите числа от 0 до " << k - 1 << " ):\n";

    p2:
        while (true)
        {
            cin >> E;
            E_SETstr.push_back(E);
            if (cin.peek() == '\n')
            {
                std::cin.clear();
                break;
            }
        }
        for (size_t i = 0; i < E_SETstr.size(); i++)
        {
            E_SETint.push_back(stoi(E_SETstr[i]));
            if (E_SETint[i] >= k || E_SETint[i] < 0)
            {
                std::cout << "Проверьте правильность введенных данных!" << std::endl;
                E_SETstr.clear();
                E_SETint.clear();
                goto p2;
            }
        }
        for (size_t i = 0; i < k*k; i++)
        {
            if (((std::find(E_SETint.begin(), E_SETint.end(), arr_x[i]) != E_SETint.end())&& 
                (std::find(E_SETint.begin(), E_SETint.end(), arr_y[i]) != E_SETint.end())) && 
                !(std::find(E_SETint.begin(), E_SETint.end(), vect[i]) != E_SETint.end()))
            {
                std::cout << "Функция не сохраняет заданное множество E = (";
                out << "Функция не сохраняет заданное множество E = (";
                for (size_t i = 0; i < E_SETint.size(); i++)
                {
                    std::cout << E_SETint[i] << ", ";
                    out << E_SETint[i] << ", ";
                }
                std::cout << '\b' << " " << '\b';
                std::cout << '\b' << " " << '\b';
                std::cout << ")";
                out << '\b' << " " << '\b' << '\b' << " " << '\b' << ")";
                SavesTheSet = false;
                break;
            }
        }
        if (SavesTheSet)
        {
            std::cout << "Функция сохраняет заданное множество E = (";
            out << "Функция сохраняет заданное множество E = (";
            for (size_t i = 0; i < E_SETint.size(); i++)
            {
                std::cout << E_SETint[i] << ", ";
                out << E_SETint[i] << ", ";
            }
            std::cout << '\b' << " " << '\b';
            std::cout << '\b' << " " << '\b';
            std::cout << ")";
            out << '\b' << " " << '\b' << '\b' << " " << '\b' << ")";
        }
        break;
    }   
    out.close();
}
int main()
{
    setlocale(LC_ALL, "RUS");
    MainMenu();
    return 0;
}
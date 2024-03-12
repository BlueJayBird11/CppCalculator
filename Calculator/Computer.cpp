// Computer.cpp
#include "Computer.h"
#include <iostream>
#include <string>
#include <tchar.h>
#include <vector>
#include <windows.h>

using namespace std;

bool isANumber(char charater)
{
    char nums[10] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
    for (int i = 0; i < 10; i++)
    {
        if (nums[i] == charater)
        {
            // wcout << nums[i] << std::endl;
            return true;
        }
    }
    return false;
}

bool isAnOperator(char charater)
{
    char operators[5] = { '+', '-', '*', '/' };
    for (int i = 0; i < 5; i++)
    {
        if (operators[i] == charater)
        {
            // wcout << operators[i] << std::endl;
            return true;
        }
    }
    return false;
}

bool isValidChar(char charater)
{
    if (isAnOperator(charater))
    {
        return true;
    }
    if (isANumber(charater))
    {
        return true;
    }
    if (charater == '.')
    {
        return true;
    }
    return false;
}

int stringToVector(wstring entry, vector<wstring>& items)
{
    wstring tempNum = L"";
    for (int i = 0; i < entry.length(); i++)
    {
        wcout << entry[i] << ", ";
        char current = entry[i];
        if (!isValidChar(current))
        {
            return 1;
        }
        else if (current == '.')
        {
            if (tempNum == L"")
            {
                tempNum = L"0.";
            }
            else if (tempNum.find(L".") == wstring::npos)
            {
                tempNum = tempNum + L".";
            }
            else
            {
                return 1;
            }
        }
        else if (isANumber(current))
        {
            wstring temp(1, static_cast<wchar_t>(current));
            tempNum = tempNum + temp;
            if (isAnOperator(entry[i + 1]) or i == entry.length() - 1)
            {
                items.push_back(tempNum);
                tempNum = L"";
            }
            // wcout << current << L" is a number" << endl;
        }
        else
        {
            // isOperator
            // if the first char is an operator that is not '-'
            if (i == 0 and current != '-')
            {
                return 1;
            }
            // if the first char is '-'
            else if (i == 0 and current == '-')
            {
                items.push_back(L"0");
                items.push_back(L"-");
            }
            // if the last charater is an operator
            else if (i == entry.length() - 1 and current != '%')
            {
                return 1;
            }
            // if the next charater is '-' and the next charater is an operator
            else if (entry[i + 1] == '-' and isAnOperator(entry[i + 2]))
            {
                wcout << "ERROR: 1" << endl;
                return 1;
            }
            // else if the next charater is not '-' and is an operator
            else if (isAnOperator(entry[i + 1]) and entry[i + 1] != '-')
            {
                wcout << "ERROR: 2" << endl;
                return 1;
            }
            else
            {
                wstring temp(1, static_cast<wchar_t>(current));
                items.push_back(temp);
            }
            // wcout << current << L" is not a number" << endl;
        }
    }
    return 0;
}

void Computer::addToTrace(wstring entry)
{
    if (doTrace)
    {
        traceHistory += entry;
    }
}

wstring Computer::calculate(wstring entry)
{
    addToTrace(L"Entry: " + entry + L"\r\r\n");
    wstring answer = L"0";

    if (entry.length() == 0)
    {
        return answer;
    }

    vector<wstring> items;

    // fill items vector
    int result = stringToVector(entry, items);

    if (result == 1)
    {
        return L"SYNTAX ERROR";
    }

    addToTrace(L"Items:");

    for (int i = 0; i < items.size(); i++)
    {
        addToTrace(items[i] + L", ");
    }

    // CALCULATE ANSWER
    // * and /
    addToTrace(L"\r\nCALCULATE (* and /):\r\n");
    for (int i = 0; i < items.size(); i++)
    {
        wstring current = items[i];
        addToTrace(current + L", ");
        if (current == L"*")
        {
            addToTrace(L"\r\n-'*' found\r\n");
            int t = i + 2;
            wstring number1 = items[i - 1];
            wstring number2 = items[i + 1];
            if (number2 == L"-")
            {
                number2 = number2 + items[i + 2];
                t++;
                addToTrace(L"--next number is negative\r\n-");
            }
            addToTrace(number1 + L"*" + number2 + L"=");
            double tempAns = stod(number1) * stod(number2);
            wstring tempStrAxs = to_wstring(tempAns);
            addToTrace(tempStrAxs);
            items[i - 1] = tempStrAxs;
            items.erase(items.begin() + i, items.begin() + t);
            i--;
        }
        else if (current == L"/")
        {
            addToTrace(L"\r\n-'/' found\r\n");
            int t = i + 2;
            wstring number1 = items[i - 1];
            wstring number2 = items[i + 1];
            if (number2 == L"-")
            {
                number2 = number2 + items[i + 2];
                t++;
                addToTrace(L"--next number is negative\r\n-");
            }
            if (stod(number2) == 0.0)
            {
                addToTrace(L"--next number is 0: ERROR\r\n-");
                return L"DIV BY 0 ERROR";
            }
            addToTrace(number1 + L"/" + number2 + L"=");
            double tempAns = stod(number1) / stod(number2);
            wstring tempStrAxs = to_wstring(tempAns);
            addToTrace(tempStrAxs);
            items[i - 1] = tempStrAxs;
            items.erase(items.begin() + i, items.begin() + t);
            i--;
        }
    }

    // + and -
    addToTrace(L"\r\nCALCULATE (+ and -):\r\n");
    for (int i = 0; i < items.size(); i++)
    {
        wstring current = items[i];
        addToTrace(current + L", ");
        if (current == L"+")
        {
            addToTrace(L"\r\n-'+' found\r\n");
            int t = i + 2;
            wstring number1 = items[i - 1];
            wstring number2 = items[i + 1];
            if (number2 == L"-")
            {
                number2 = number2 + items[i + 2];
                t++;
                addToTrace(L"--next number is negative\r\n-");
            }
            addToTrace(number1 + L"+" + number2 + L"=");
            double tempAns = stod(number1) + stod(number2);
            wstring tempStrAxs = to_wstring(tempAns);
            addToTrace(tempStrAxs);
            items[i - 1] = tempStrAxs;
            items.erase(items.begin() + i, items.begin() + t);
            i--;
        }
        else if (current == L"-")
        {
            addToTrace(L"\r\n-'-' found\r\n");
            int t = i + 2;
            wstring number1 = items[i - 1];
            wstring number2 = items[i + 1];
            if (number2 == L"-")
            {
                number2 = number2 + items[i + 2];
                t++;
                addToTrace(L"--next number is negative\r\n-");
            }
            addToTrace(number1 + L"-" + number2 + L"=");
            double tempAns = stod(number1) - stod(number2);
            wstring tempStrAxs = to_wstring(tempAns);
            addToTrace(tempStrAxs);
            items[i - 1] = tempStrAxs;
            items.erase(items.begin() + i, items.begin() + t);
            i--;
        }
    }

    addToTrace(L"\r\nRemaining item: " + items[0] + L"\r\n\r\n");

    answer = items[0];

    return answer;
}

wstring Computer::calculatePercentage(wstring entry)
{
    wcout << "Entry: " << entry << endl;
    wstring answer = L"end";

    vector<wstring> items;

    // fill items vector
    int result = stringToVector(entry, items);

    if (result == 1)
    {
        return L"SYNTAX ERROR";
    }

    wcout << endl << "Items:" << endl;

    for (int i = 0; i < items.size(); i++)
    {
        wcout << items[i] << ", ";
    }

    // CALCULATE ANSWER
    // * and /
    wcout << endl << "CALCULATE:" << endl;
    for (int i = 0; i < items.size(); i++)
    {
        wstring current = items[i];
        wcout << current << ", ";
        if (current == L"*")
        {
            int t = i + 2;
            wstring number1 = items[i - 1];
            wstring number2 = items[i + 1];
            if (number2 == L"-")
            {
                number2 = number2 + items[i + 2];
                t++;
            }
            double double1 = stod(number1);
            double double2 = stod(number2) / 100 * double1;

            double tempAns = double1 * double2;
            wcout << endl << tempAns << endl;
            items[i - 1] = to_wstring(tempAns);
            items.erase(items.begin() + i, items.begin() + t);
            i--;
        }
        if (current == L"/")
        {
            int t = i + 2;
            wstring number1 = items[i - 1];
            wstring number2 = items[i + 1];
            if (number2 == L"-")
            {
                number2 = number2 + items[i + 2];
                t++;
            }
            if (stod(number2) == 0.0)
            {
                return L"DIV BY 0 ERROR";
            }
            double double1 = stod(number1);
            double double2 = stod(number2) / 100 * double1;

            double tempAns = double1 / double2;
            wcout << endl << tempAns << endl;
            items[i - 1] = to_wstring(tempAns);
            items.erase(items.begin() + i, items.begin() + t);
            i--;
        }
    }

    // wcout << endl << "*/:" << endl;

    // + and -
    for (int i = 0; i < items.size(); i++)
    {
        wstring current = items[i];
        wcout << current << ", ";
        if (current == L"+")
        {
            int t = i + 2;
            wstring number1 = items[i - 1];
            wstring number2 = items[i + 1];
            if (number2 == L"-")
            {
                number2 = number2 + items[i + 2];
                t++;
            }

            double double1 = stod(number1);
            double double2 = stod(number2) / 100 * double1;

            double tempAns = double1 + double2;
            wcout << endl << tempAns << endl;
            items[i - 1] = to_wstring(tempAns);
            items.erase(items.begin() + i, items.begin() + t);
            i--;
        }
        if (current == L"-")
        {
            int t = i + 2;
            wstring number1 = items[i - 1];
            wstring number2 = items[i + 1];
            if (number2 == L"-")
            {
                number2 = number2 + items[i + 2];
                t++;
            }
            double double1 = stod(number1);
            double double2 = stod(number2) / 100 * double1;

            double tempAns = double1 - double2;
            wcout << endl << tempAns << endl;
            items[i - 1] = to_wstring(tempAns);
            items.erase(items.begin() + i, items.begin() + t);
            i--;
        }
    }

    wcout << endl << "Items:" << endl;

    for (int i = 0; i < items.size(); i++)
    {
        wcout << items[i] << ", ";
    }

    wcout << endl << endl;


    answer = items[0];

    return answer;
}

wstring Computer::getTraceHistory()
{
    return traceHistory;
}

void Computer::activateTrace()
{
    doTrace = true;
}

void Computer::deactivateTrace()
{
    doTrace = false;
}

void Computer::clearTrace()
{
    traceHistory = L"";
}

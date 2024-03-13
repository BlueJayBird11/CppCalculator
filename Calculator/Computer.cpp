// Computer.cpp
#include "Computer.h"
#include <iostream>
#include <string>
#include <tchar.h>
#include <vector>
#include <windows.h>
#include <cmath>

using namespace std;

bool isANumber(char charater)
{
    char nums[10] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
    for (int i = 0; i < 10; i++)
    {
        if (nums[i] == charater)
        {
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

void Computer::addToTrace(wstring entry)
{
    if (doTrace)
    {
        traceHistory += entry;
    }
}

int Computer::stringToVector(wstring entry, vector<wstring>& items)
{
    addToTrace(L"Entry -> Vector\r\n");
    wstring tempNum = L"";
    for (int i = 0; i < entry.length(); i++)
    {
        wcout << entry[i] << ", ";
        char current = entry[i];
        if (!isValidChar(current))
        {
            addToTrace(L"\r\nSYNTAX ERROR - invalid charater \r\n\r\n");
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
                addToTrace(L"\r\nSYNTAX ERROR - multiple decimals in number \r\n\r\n");
                return 1;
            }
        }
        else if (isANumber(current))
        {
            wstring temp(1, static_cast<wchar_t>(current));
            tempNum = tempNum + temp;
            if (isAnOperator(entry[i + 1]) or i == entry.length() - 1)
            {
                addToTrace(L"NUMBER(" + tempNum + L"), ");
                items.push_back(tempNum);
                tempNum = L"";
            }
        }
        else
        {
            // isOperator
            // if the first char is an operator that is not '-'
            if (i == 0 and current != '-')
            {
                addToTrace(L"\r\nSYNTAX ERROR - first charater is operator other than '-' \r\n\r\n");
                return 1;
            }
            else if (i == 0 and current == '-' and entry.length() == 1)
            {
                addToTrace(L"\r\nSYNTAX ERROR - first charater is operator other than '-' but nothing follows \r\n\r\n");
                return 1;
            }
            // if the first char is '-'
            else if (i == 0 and current == '-')
            {
                items.push_back(L"0");
                items.push_back(L"-");
                addToTrace(L"NUMBER(0), OPERATOR(-)");
            }
            // if the last charater is an operator
            else if (i == entry.length() - 1 and current != '%')
            {
                addToTrace(L"\r\nSYNTAX ERROR - last charater is operator \r\n\r\n");
                return 1;
            }
            // if the next charater is '-' and the next charater is an operator
            else if (entry[i + 1] == '-' and isAnOperator(entry[i + 2]))
            {
                addToTrace(L"\r\nSYNTAX ERROR - charater following - is operator \r\n\r\n");
                return 1;
            }
            // else if the next charater is not '-' and is an operator
            else if (isAnOperator(entry[i + 1]) and entry[i + 1] != '-')
            {
                addToTrace(L"\r\nSYNTAX ERROR - charater after operator is operator other than '-' \r\n\r\n");
                return 1;
            }
            else
            {
                wstring temp(1, static_cast<wchar_t>(current));
                addToTrace(L"OPERATOR(" + temp + L"), ");
                items.push_back(temp);
            }
        }
    }
    return 0;
}

wstring Computer::calculate(wstring entry)
{
    addToTrace(L"Entry: " + entry + L"\r\n");
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

    addToTrace(L"\r\nItems:");

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
            double_t tempAns = stod(number1) * stod(number2);
            wstring tempStrAns = to_wstring(tempAns);
            addToTrace(tempStrAns + L"\r\nItems: ");
            items[i - 1] = tempStrAns;
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
            double_t tempAns = stod(number1) / stod(number2);
            wstring tempStrAns = to_wstring(tempAns);
            addToTrace(tempStrAns + L"\r\nItems: ");
            items[i - 1] = tempStrAns;
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
            double_t tempAns = stod(number1) + stod(number2);
            wstring tempStrAns = to_wstring(tempAns);
            addToTrace(tempStrAns + L"\r\nItems: ");
            items[i - 1] = tempStrAns;
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
            double_t tempAns = stod(number1) - stod(number2);
            wstring tempStrAns = to_wstring(tempAns);
            addToTrace(tempStrAns + L"\r\nItems: ");
            items[i - 1] = tempStrAns;
            items.erase(items.begin() + i, items.begin() + t);
            i--;
        }
    }

    addToTrace(L"\r\nRemaining item: " + items[0] + L"\r\n\r\n");

    double_t tempNum = stod(items[0]);

    if (floor(tempNum) == tempNum)
    {
        return to_wstring((int)tempNum);
    }

    answer = items[0];

    return answer;
}

wstring Computer::calculatePercentage(wstring entry)
{
    addToTrace(L"Entry (percentage mode): " + entry + L"\r\n");
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

    addToTrace(L"\r\nItems:");

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
            double_t double_t1 = stod(number1);
            double_t double_t2 = stod(number2) / 100 * double_t1;

            addToTrace(number1 + L"*(" + number2 + L"/100*" + number1 + L")=");
            double_t tempAns = double_t1 * double_t2;
            wstring tempStrAns = to_wstring(tempAns);
            addToTrace(tempStrAns + L"\r\nItems: ");
            items[i - 1] = tempStrAns;
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
            double_t double_t1 = stod(number1);
            double_t double_t2 = stod(number2) / 100 * double_t1;

            addToTrace(number1 + L"/(" + number2 + L"/100*" + number1 + L")=");
            double_t tempAns = double_t1 / double_t2;
            wstring tempStrAns = to_wstring(tempAns);
            addToTrace(tempStrAns + L"\r\nItems: ");
            items[i - 1] = tempStrAns;
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
            double_t double_t1 = stod(number1);
            double_t double_t2 = stod(number2) / 100 * double_t1;

            addToTrace(number1 + L"+(" + number2 + L"/100*" + number1 + L")=");
            double_t tempAns = double_t1 + double_t2;
            wstring tempStrAns = to_wstring(tempAns);
            addToTrace(tempStrAns + L"\r\nItems: ");
            items[i - 1] = tempStrAns;
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
            double_t double_t1 = stod(number1);
            double_t double_t2 = stod(number2) / 100 * double_t1;

            addToTrace(number1 + L"-("+ number2 + L"/100*" + number1 + L")=");
            double_t tempAns = double_t1 - double_t2;
            wstring tempStrAns = to_wstring(tempAns);
            addToTrace(tempStrAns + L"\r\nItems: ");
            items[i - 1] = tempStrAns;
            items.erase(items.begin() + i, items.begin() + t);
            i--;
        }
    }

    addToTrace(L"\r\nRemaining item: " + items[0] + L"\r\n\r\n");

    double_t tempNum = stod(items[0]);

    if (floor(tempNum) == tempNum)
    {
        return to_wstring((int)tempNum);
    }

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

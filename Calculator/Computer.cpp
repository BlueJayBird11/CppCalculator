// Computer.cpp
#include "Computer.h"
#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

bool Computer::isANumber(char charater)
{
    char nums[10] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
    for (int i = 0; i < 10; i++)
    {
        countTrace++;
        if (nums[i] == charater)
        {
            return true;
        }
    }
    return false;
}

bool Computer::isAnOperator(char charater)
{
    char operators[5] = { '+', '-', '*', '/' };
    for (int i = 0; i < 5; i++)
    {
        countTrace++;
        if (operators[i] == charater)
        {
            return true;
        }
    }
    return false;
}

bool Computer::isValidChar(char charater)
{
    if (isAnOperator(charater))
    {
        countTrace++;
        return true;
    }
    if (isANumber(charater))
    {
        countTrace += 2;
        return true;
    }
    if (charater == '.')
    {
        countTrace += 3;
        return true;
    }
    addToTrace(L"-NOT A VALID CHARATER\r\n");
    return false;
}

// removes trailing zeros: 2.0500 -> 2.05
wstring Computer::removeTrailingZeros(wstring str) {
    // Check if the string contains a decimal point.
    addToTrace(L"-REMOVE TRAILING ZEROS IF ANY\r\n");
    size_t decimalPos = str.find(L'.');
    if (decimalPos != wstring::npos) {
        addToTrace(L"--" + str + L" contains '.'");
        // Find last none 0 after decimal.
        size_t nonZeroPos = str.find_last_not_of(L'0');
        countTrace++;
        if (nonZeroPos > decimalPos) {
            countTrace++;
            addToTrace(L"--Erase trailing zeros but leave the decimal part intact.\r\n");
            str.erase(nonZeroPos + 1);
        }
        else
        {
            countTrace+=2;
            addToTrace(L"--No non zero digits after the decimal, erase decimal with following zeros\r\n");
            str.erase(nonZeroPos);
        }
    }
    return str;
}

bool Computer::containsDecimal(wstring number)
{
    return number.find(L'.') != wstring::npos;
}

void Computer::addToTrace(wstring entry)
{
    if (doTrace)
    {
        traceHistory += entry;
    }
}

// turns the entry into a vector<wstring> with the numbers and operators
int Computer::stringToVector(wstring entry, vector<wstring>& items)
{
    clearTrace();
    addToTrace(L"Entry -> Vector\r\n");
    wstring tempNum = L"";
    for (int i = 0; i < entry.length(); i++)
    {
        // wcout << entry[i] << ", ";
        char current = entry[i];
        wstring tempChar(1, static_cast<wchar_t>(current));
        addToTrace(L"Charater '" + tempChar + L"':\r\n");
        if (!isValidChar(current))
        {
            countTrace++;
            addToTrace(L"\r\nSYNTAX ERROR - invalid charater \r\n\r\n");
            return 1;
        }
        else if (current == '.')
        {
            countTrace+=2;
            addToTrace(L"-is a DECIMAL, \r\n");
            if (tempNum == L"")
            {
                countTrace++;
                addToTrace(L"--tempNum is blank, insert \"0.\" \r\n");
                tempNum = L"0.";
            }
            else if (tempNum.find(L".") == wstring::npos)
            {
                countTrace += 2;
                addToTrace(L"--tempNum is has no decimal, insert \".\" \r\n");
                tempNum = tempNum + L".";
            }
            else
            {
                countTrace += 3;
                addToTrace(L"--tempNum has decimal already: throw error \r\n");
                addToTrace(L"--SYNTAX ERROR - multiple decimals in number \r\n\r\n");
                return 1;
            }
        }
        else if (isANumber(current))
        {
            countTrace += 3;
            addToTrace(L"-is a NUMBER\r\n");
            wstring temp(1, static_cast<wchar_t>(current));
            tempNum = tempNum + temp;
            if (isAnOperator(entry[i + 1]) or i == entry.length() - 1)
            {
                // addToTrace(L"NUMBER(" + tempNum + L"), ");
                countTrace++;
                addToTrace(L"--next charater is operator or end of string\r\n");
                addToTrace(L"--insert {" + tempNum + L"} to vector \r\n ");
                items.push_back(tempNum);
                tempNum = L"";
            }
        }
        else
        {
            countTrace += 4;
            addToTrace(L"-is a OPERATOR\r\n");
            // isOperator
            // if the first char is an operator that is not '-'
            if (i == 0 and current != '-')
            {
                countTrace++;
                addToTrace(L"\r\n--SYNTAX ERROR - first charater is operator other than '-' \r\n\r\n");
                return 1;
            }
            else if (i == 0 and current == '-' and entry.length() == 1)
            {
                countTrace += 2;
                addToTrace(L"\r\n--SYNTAX ERROR - first charater is operator other than '-' but nothing follows \r\n\r\n");
                return 1;
            }
            // if the first char is '-'
            else if (i == 0 and current == '-')
            {
                countTrace += 3;
                addToTrace(L"--Start of the entry is '-', insert NUMBER 0 and OPERATOR - to vector \r\n");
                items.push_back(L"0");
                items.push_back(L"-");
                // addToTrace(L"NUMBER(0), OPERATOR(-)");
            }
            // if the last charater is an operator
            else if (i == entry.length() - 1 and current != '%')
            {
                countTrace += 4;
                addToTrace(L"\r\n--SYNTAX ERROR - last charater is operator \r\n\r\n");
                return 1;
            }
            // if the next charater is '-' and the next charater is an operator
            else if (entry[i + 1] == '-' and isAnOperator(entry[i + 2]))
            {
                countTrace += 5;
                addToTrace(L"\r\n--SYNTAX ERROR - charater following - is operator \r\n\r\n");
                return 1;
            }
            // else if the next charater is not '-' and is an operator
            else if (isAnOperator(entry[i + 1]) and entry[i + 1] != '-')
            {
                countTrace += 6;
                addToTrace(L"\r\n--SYNTAX ERROR - charater after operator is operator other than '-' \r\n\r\n");
                return 1;
            }
            else
            {
                countTrace += 7;
                addToTrace(L"--No errors found, insert operator to vector \r\n");
                wstring temp(1, static_cast<wchar_t>(current));
                // addToTrace(L"OPERATOR(" + temp + L"), ");
                items.push_back(temp);
            }
        }
    }
    return 0;
}

// The calculation for the "=" button
wstring Computer::calculate(wstring entry)
{
    wstring answer = L"0";
    countTrace = 0;

    if (entry.length() == 0)
    {
        countTrace++;
        addToTrace(L"Entry's length is 0, return L\"0\"");
        state = 1;
        return answer;
    }

    vector<wstring> items;

    // fill items vector
    int result = stringToVector(entry, items);
    lastEntry = entry;

    // 0 if no errors, 1 if error
    if (result == 1)
    {
        countTrace++;
        addToTrace(L"stringToVector function returned 1, return L\"SYNTAX ERROR\"");
        state = 2;
        return L"SYNTAX ERROR";
    }

    addToTrace(L"Items:");

    for (int i = 0; i < items.size(); i++)
    {
        countTrace++;
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
            countTrace++;
            addToTrace(L"\r\n-'*' found\r\n");
            int t = i + 2;
            wstring number1 = items[i - 1];
            wstring number2 = items[i + 1];
            if (number2 == L"-")
            {
                countTrace++;
                number2 = number2 + items[i + 2];
                t++;
                addToTrace(L"--next number is negative\r\n-");
            }
            wstring tempStrAns;
            if (stoll(number1) > 10000000 or stoll(number2) > 10000000)
            {
                countTrace++;
                addToTrace(L"--numbers are to large for floating point computation\r\n-");
                if (containsDecimal(number1))
                {
                    countTrace++;
                    addToTrace(L"---String {" + number1 + L"} contains '.'\r\n");
                    addToTrace(L"---Calculate: (" + number2 + L" * " + number1 + L")+" + number2 + L"\r\n");
                    double_t tempAns = (stod(number2) * stod(number1)) + stod(number2);
                    tempStrAns = to_wstring(tempAns);
                }
                else if (containsDecimal(number2))
                {
                    countTrace += 2;
                    addToTrace(L"---String {" + number2 + L"} contains '.'\r\n");
                    addToTrace(L"---Calculate: " + number1 + L"+(" + number2 + L" * " + number1 + L")\r\n");
                    double_t tempAns = stoll(number1) + (stod(number2) * stod(number1));
                    tempStrAns = to_wstring(tempAns);
                }
                else
                {
                    countTrace += 3;
                    addToTrace(L"--Neither number contains decimal\r\n");
                    addToTrace(L"---Calculate: " + number1 + L" * " + number2 + L"\r\n");
                    long long tempAns = stoll(number1) * stoll(number2);
                    tempStrAns = to_wstring(tempAns);
                }
            }
            else
            {
                countTrace += 2;
                addToTrace(L"---Calculate: " + number1 + L" * " + number2 + L"\r\n");
                double_t tempAns = stod(number1) * stod(number2);
                tempStrAns = to_wstring(tempAns);
            }
            if (stod(number1) > 0 and stod(number2) > 0 and tempStrAns[0] == '-')
            {
                countTrace++;
                addToTrace(L"--OVERFLOW DETECTED: THROW ERROR");
                state = 2;
                return L"OVERFLOW ERROR";
            }
            tempStrAns = removeTrailingZeros(tempStrAns);
            addToTrace(number1 + L"*" + number2 + L"=" + tempStrAns + L"\r\nItems: ");
            items[i - 1] = tempStrAns;
            items.erase(items.begin() + i, items.begin() + t);
            i--;
        }
        else if (current == L"/")
        {
            countTrace += 2;
            addToTrace(L"\r\n-'/' found\r\n");
            int t = i + 2;
            wstring number1 = items[i - 1];
            wstring number2 = items[i + 1];
            if (number2 == L"-")
            {
                countTrace++;
                number2 = number2 + items[i + 2];
                t++;
                addToTrace(L"--next number is negative\r\n-");
            }
            if (stod(number2) == 0.0)
            {
                countTrace++;
                addToTrace(L"--next number is 0: ERROR\r\n-");
                state = 2;
                return L"DIV BY 0 ERROR";
            }
            wstring tempStrAns;
            if (stoll(number1) > 10000000 or stoll(number2) > 10000000)
            {
                countTrace++;
                addToTrace(L"--numbers are to large for floating point computation\r\n-");
                if (containsDecimal(number1))
                {
                    countTrace++;
                    addToTrace(L"String [" + number2 + L"] contains '.'\r\n");
                    addToTrace(L"---Calculate: " + number2 + L"*(1" + L" / " + number1 + L")\r\n");
                    long long tempAns = (1 / stod(number1)) * stoll(number2);
                    tempStrAns = to_wstring(tempAns);
                }
                else if (containsDecimal(number2))
                {
                    countTrace += 2;
                    addToTrace(L"String [" + number2 + L"] contains '.'\r\n");
                    addToTrace(L"---Calculate: " + number1 + L"*(1" + L" / " + number2 + L")\r\n");
                    long long tempAns = stoll(number1) * (1 / stod(number2));
                    tempStrAns = to_wstring(tempAns);
                }
                else
                {
                    countTrace += 3;
                    addToTrace(L"--Neither number contains decimal\r\n");
                    addToTrace(L"---Calculate: " + number1 + L" / " + number2 + L"\r\n");
                    long long tempAns = stoll(number1) / stoll(number2);
                    tempStrAns = to_wstring(tempAns);
                }  
            }
            else
            {
                countTrace += 2;
                addToTrace(L"---Calculate: " + number1 + L" / " + number2 + L"\r\n");
                double_t tempAns = stod(number1) / stod(number2);
                tempStrAns = to_wstring(tempAns);
            }
            tempStrAns = removeTrailingZeros(tempStrAns);
            addToTrace(number1 + L"/" + number2 + L"=" + tempStrAns + L"\r\nItems: ");
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
            countTrace++;
            addToTrace(L"\r\n-'+' found\r\n");
            int t = i + 2;
            wstring number1 = items[i - 1];
            wstring number2 = items[i + 1];
            if (number2 == L"-")
            {
                countTrace++;
                number2 = number2 + items[i + 2];
                t++;
                addToTrace(L"--next number is negative\r\n-");
            }
            wstring tempStrAns;
            if (stoll(number1) > 10000000 or stoll(number2) > 10000000)
            {
                countTrace++;
                addToTrace(L"--numbers are to large for floating point computation\r\n-");
                addToTrace(L"---Calculate: " + number1 + L" + " + number2 + L"\r\n");
                long long tempAns = stoll(number1) + stoll(number2);
                tempStrAns = to_wstring(tempAns);
            }
            else
            {
                countTrace += 2;
                addToTrace(L"---Calculate: " + number1 + L" + " + number2 + L"\r\n");
                double_t tempAns = stod(number1) + stod(number2);
                tempStrAns = to_wstring(tempAns);
            }
            if (stod(number1) > 0 and stod(number2) > 0 and tempStrAns[0] == '-')
            {
                countTrace++;
                addToTrace(L"--OVERFLOW DETECTED: THROW ERROR");
                state = 2;
                return L"OVERFLOW ERROR";
            }
            tempStrAns = removeTrailingZeros(tempStrAns);
            addToTrace(number1 + L"+" + number2 + L"=" + tempStrAns + L"\r\nItems: ");
            items[i - 1] = tempStrAns;
            items.erase(items.begin() + i, items.begin() + t);
            i--;
        }
        else if (current == L"-")
        {
            countTrace += 2;
            addToTrace(L"\r\n-'-' found\r\n");
            int t = i + 2;
            wstring number1 = items[i - 1];
            wstring number2 = items[i + 1];
            if (number2 == L"-")
            {
                countTrace++;
                number2 = number2 + items[i + 2];
                t++;
                addToTrace(L"--next number is negative\r\n-");
            }
            wstring tempStrAns;
            if (stoll(number1) > 10000000 or stoll(number2) > 10000000)
            {
                countTrace++;
                addToTrace(L"--numbers are to large for floating point computation\r\n-");
                addToTrace(L"---Calculate: " + number1 + L" - " + number2 + L"\r\n");
                long long tempAns = stoll(number1) - stoll(number2);
                tempStrAns = to_wstring(tempAns);
            }
            else
            {
                countTrace += 2;
                addToTrace(L"---Calculate: " + number1 + L" - " + number2 + L"\r\n");
                double_t tempAns = stod(number1) - stod(number2);
                tempStrAns = to_wstring(tempAns);
            }
            if (stod(number1) < 0 and stod(number2) < 0 and tempStrAns[0] != '-')
            {
                countTrace++;
                addToTrace(L"--UNDERFLOW DETECTED: THROW ERROR");
                state = 2;
                return L"UNDERFLOW ERROR";
            }
            tempStrAns = removeTrailingZeros(tempStrAns);
            addToTrace(number1 + L"-" + number2 + L"=" + tempStrAns + L"\r\nItems: ");
            items[i - 1] = tempStrAns;
            items.erase(items.begin() + i, items.begin() + t);
            i--;
        }
    }

    addToTrace(L"\r\nRemaining item: " + items[0] + L"\r\n\r\n");

    double_t tempNum = stod(items[0]);

    answer = items[0];

    state = 1;

    return answer;
}

// The calculation for the "%" button
wstring Computer::calculatePercentage(wstring entry)
{
    clearTrace();
    countTrace = 0;
    wstring answer = L"0";

    if (entry.length() == 0)
    {
        countTrace++;
        state = 1;
        addToTrace(L"Entry's length is 0, return L\"0\"");
        return answer;
    }

    vector<wstring> items;

    // fill items vector
    int result = stringToVector(entry, items);

    lastEntry = entry + L" (percentage mode)";

    // 0 if no errors, 1 if error
    if (result == 1)
    {
        countTrace++;
        addToTrace(L"stringToVector function returned 1, return L\"SYNTAX ERROR\"");
        state = 2;
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
            countTrace++;
            addToTrace(L"\r\n-'*' found\r\n");
            int t = i + 2;
            wstring number1 = items[i - 1];
            wstring number2 = items[i + 1];
            if (number2 == L"-")
            {
                countTrace++;
                number2 = number2 + items[i + 2];
                t++;
                addToTrace(L"--next number is negative\r\n-");
            }
            double_t double_t1 = stod(number1);
            double_t double_t2 = stod(number2) / 100 * double_t1;

            addToTrace(L"---Calculate: " + number1 + L"*(" + number2 + L"/100*" + number1 + L")\r\n");
            double_t tempAns = double_t1 * double_t2;
            wstring tempStrAns = to_wstring(tempAns);
            tempStrAns = removeTrailingZeros(tempStrAns);
            if (stod(number1) > 0 and stod(number2) > 0 and tempStrAns[0] == '-')
            {
                countTrace++;
                addToTrace(L"--OVERFLOW DETECTED: THROW ERROR");
                state = 2;
                return L"OVERFLOW ERROR";
            }
            addToTrace(number1 + L"*(" + number2 + L"/100*" + number1 + L")=" + tempStrAns + L"\r\nItems: ");
            items[i - 1] = tempStrAns;
            items.erase(items.begin() + i, items.begin() + t);
            i--;
        }
        else if (current == L"/")
        {
            countTrace += 2;
            addToTrace(L"\r\n-'/' found\r\n");
            int t = i + 2;
            wstring number1 = items[i - 1];
            wstring number2 = items[i + 1];
            if (number2 == L"-")
            {
                countTrace++;
                number2 = number2 + items[i + 2];
                t++;
                addToTrace(L"--next number is negative\r\n-");
            }
            if (stod(number2) == 0.0)
            {
                countTrace++;
                addToTrace(L"--next number is 0: ERROR\r\n-");
                state = 2;
                return L"DIV BY 0 ERROR";
            }
            double_t double_t1 = stod(number1);
            double_t double_t2 = stod(number2) / 100 * double_t1;

            addToTrace(L"---Calculate: " + number1 + L"/(" + number2 + L"/100*" + number1 + L")\r\n");
            double_t tempAns = double_t1 / double_t2;
            wstring tempStrAns = to_wstring(tempAns);
            tempStrAns = removeTrailingZeros(tempStrAns);
            addToTrace(number1 + L"/(" + number2 + L"/100*" + number1 + L")=" + tempStrAns + L"\r\nItems: ");
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
            countTrace++;
            addToTrace(L"\r\n-'+' found\r\n");
            int t = i + 2;
            wstring number1 = items[i - 1];
            wstring number2 = items[i + 1];
            if (number2 == L"-")
            {
                countTrace++;
                number2 = number2 + items[i + 2];
                t++;
                addToTrace(L"--next number is negative\r\n-");
            }
            double_t double_t1 = stod(number1);
            double_t double_t2 = stod(number2) / 100 * double_t1;

            addToTrace(L"---Calculate: " + number1 + L"+(" + number2 + L"/100*" + number1 + L")\r\n");
            double_t tempAns = double_t1 + double_t2;
            wstring tempStrAns = to_wstring(tempAns);
            tempStrAns = removeTrailingZeros(tempStrAns);
            if (stod(number1) > 0 and stod(number2) > 0 and tempStrAns[0] == '-')
            {
                countTrace++;
                addToTrace(L"--OVERFLOW DETECTED: THROW ERROR");
                state = 2;
                return L"OVERFLOW ERROR";
            }
            addToTrace(number1 + L"+(" + number2 + L"/100*" + number1 + L")=" + tempStrAns + L"\r\nItems: ");
            items[i - 1] = tempStrAns;
            items.erase(items.begin() + i, items.begin() + t);
            i--;
        }
        else if (current == L"-")
        {
            countTrace += 2;
            addToTrace(L"\r\n-'-' found\r\n");
            int t = i + 2;
            wstring number1 = items[i - 1];
            wstring number2 = items[i + 1];
            if (number2 == L"-")
            {
                countTrace++;
                number2 = number2 + items[i + 2];
                t++;
                addToTrace(L"--next number is negative\r\n-");
            }
            double_t double_t1 = stod(number1);
            double_t double_t2 = stod(number2) / 100 * double_t1;
            addToTrace(L"---Calculate: " + number1 + L"-(" + number2 + L"/100*" + number1 + L")\r\n");
            double_t tempAns = double_t1 - double_t2;
            wstring tempStrAns = to_wstring(tempAns);
            tempStrAns = removeTrailingZeros(tempStrAns);
            addToTrace(number1 + L"-(" + number2 + L"/100*" + number1 + L")=" + tempStrAns + L"\r\nItems: ");
            items[i - 1] = tempStrAns;
            items.erase(items.begin() + i, items.begin() + t);
            i--;
        }
    }

    addToTrace(L"\r\nRemaining item: " + items[0] + L"\r\n\r\n");
    state = 1;

    return items[0];
}

wstring Computer::getTraceInfo()
{
    return L"State: " + to_wstring(state) + L"\nCount: " + to_wstring(countTrace) + L"\nLast Entry: " + lastEntry;
}

wstring Computer::getTraceHistory()
{
    return traceHistory;
}

void Computer::changeState(int newState)
{
    state = newState;
}

int Computer::getState()
{
    return state;
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
    countTrace = 0;
    traceHistory = L"";
    lastEntry = L"";
}

#pragma once
// Computer.h
#ifndef COMPUTER_H
#define COMPUTER_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Computer
{
private:
    wstring traceHistory;
    bool doTrace = false;
    int stringToVector(wstring, vector<wstring>&);
    bool isANumber(char charater);
    bool isAnOperator(char charater);
    bool isValidChar(char charater);
    wstring removeTrailingZeros(wstring str);
    bool containsDecimal(wstring number);

public:
    void addToTrace(wstring str);
    wstring calculate(wstring entry);
    wstring calculatePercentage(wstring entry);
    wstring getTraceHistory();
    void activateTrace();
    void deactivateTrace();
    void clearTrace();
};

#endif // COMPUTER_H

// Computer.cpp
#include "Computer.h"

wstring Computer::calculate(wstring entry)
{
    // Add your actual calculation logic here
    return L"Answer";
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

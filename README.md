# CppCalculator
 
## Preface
This program was made for an interview I had with the company VS Merlot.

It uses standard C++ (not Managed C++) with the default Visual Studio compiler and usees user interfaces that are bundled with MSVC: 

https://learn.microsoft.com/en-us/cpp/windows/walkthrough-creating-windows-desktop-applications-cpp?view=msvc-170

## Files
The main file is Calculator.cpp. This is where the user interface is built. The other two important files are Computer.h and Computer.cpp. 

### Calculator.cpp
As said before, Calculator.cpp is where the interface is built and shown to the user. This includes the buttons, static and edit texts, and the tabs that the user can switch inbetween. There is also some logic here that helps the user with inputs.

### Computer.h and Computer.cpp
The computer files can be considered the "brains" of the program. They are where the entry is actually calculated. This was done as a header and accomaning C++ file so that it could be imported into the 

## States
State 0 is the default state, anything can be input

State 1 is the state where an answer is displayed with no errors

State 2 is the state where an error occurs when calculating the entry

## How calculation works
The entry that is input by the user gets turned into a vector of numbers and operators. 

For examples:

`{"243", "+", "56"}`

This was done as it allows for future inputs to easily be added in if nessessary. It also allows for simple syntax checking before calculations.

## Errors
If an error is picked, for example a Syntax Error, the error is displayed and will not allow input until CE or C is clicked.

## Other notes
There are a large count of decisions being made largely because the input is turned into vector and is having it's syntax checked.
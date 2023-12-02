// TIHS WAS OFF BY 2, DON'T KNOW WHY!!!

#include <fstream>
#include <string>
#include <iostream>
#include <unordered_map>
using namespace std;

// Create a constant map of replacements
const unordered_map<string, string> REPLACEMENTS = {{"one", "1"}, {"two", "2"}, {"three", "3"}, {"four", "4"}, {"five", "5"}, {"six", "6"}, {"seven", "7"}, {"eight", "8"}, {"nine", "9"}};

void replaceNumbers(string*);

int main()
{
    // Get data from file
    ifstream myData = ifstream("myData.txt");
    ofstream myWrite = ofstream("myWritten.txt", ofstream::out);

    string lineData = "";

    // Total count to print out at the end
    int totalCount = 0;

    // Read data from file until eof
    while (!myData.eof())
    {
        // Now get the line
        getline(myData, lineData);

        // Set 2 numbers that are changed throughout program 
        int firstNumber = -1;
        int lastNumber = -1; 

        // Run the function to replace all strings with numbers on the fly
        replaceNumbers(&lineData);

        myWrite << lineData << endl;

        // Loop through string looking for numbers
        for (char character: lineData)
        {
            // Verify current is character
            if (isdigit(character))
            {
                if (firstNumber == -1)
                {
                    // Subtract 48 from character to convert to 0-9
                    firstNumber = character - 48;
                }
                // Now run the lastNumber instead of firstNumber
                lastNumber = character - 48;
            }
        }

        // Now we add up the numbers
        // Make sure every line had at least some numbers written
        if (firstNumber != -1)
        {
            totalCount += (firstNumber * 10) + lastNumber;
        }
        
    } 

    cout << totalCount;

    return 0;
}


// Function that takes in a pointer to a string, and goes in order trying to replace 
// the first occurance of a number spelled out, and replaces it. Then recursion happens
void replaceNumbers(string *s)
{
    // Create a holder to ensure the first values are taken in a string
    int holderPosition = 999;
    int holderSize = 0;
    string holderValue = "";

    // Use a loop to get each string of replacement
    for (auto replacement: REPLACEMENTS)
    {
        // Find if a replacement exists in a string
        int replacementPositionFirst = s->find(replacement.first);
        if (replacementPositionFirst > -1 && replacementPositionFirst < holderPosition)
        {
            // Smallest value found so far, update data held
            holderPosition = replacementPositionFirst;
            holderSize = replacement.first.size();
            holderValue = replacement.second;
        }
    }

    if (holderPosition != 999)
    {
        // New number to replace was found
        s->replace(holderPosition, holderSize, holderValue);

        // Now continue the trend
        replaceNumbers(s);
    } else {
        // Loop is over, no more word-numbers found
        return;
    }
}
#include <fstream>
#include <string>
#include <iostream>
#include <unordered_map>
using namespace std;

// Create a constant map of replacements
const unordered_map<string, int> REPLACEMENTS = {{"one", 1}, {"two", 2}, {"three", 3}, {"four", 4}, {"five", 5}, {"six", 6}, {"seven", 7}, {"eight", 8}, {"nine", 9}};

int checkForReplacements(string*, int);

int main()
{
    // Get data from file
    ifstream myData = ifstream("myData.txt");

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

        // Loop through string looking for numbers
        for (int i = 0; i < lineData.size(); i++)
        {
            // Set the current character
            char character = lineData.at(i);
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
            } else 
            {
                // Digit wasn't found, attempt to search spelled out number
                int spelledOut = checkForReplacements(&lineData, i);
                if (spelledOut > -1)
                {
                if (firstNumber == -1)
                {
                    // Subtract 48 from character to convert to 0-9
                    firstNumber = spelledOut;
                }
                // Now run the lastNumber instead of firstNumber
                lastNumber = spelledOut;
                }
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


// Function that takes in a pointer to a string, a position, and a sizem then returns
// a number if the current string is a spelled out number, or -1 if no number exists
int checkForReplacements(string *s, int position)
{
    // Create a new string that substringed to position
    string newString = s->substr(position);

    // Loop over REPLACEMENTS map
    for (auto &replacement: REPLACEMENTS)
    {  
        // Create a comparison variable that uses strncmp
        int comparison = strncmp(newString.c_str(), replacement.first.c_str(), replacement.first.size());
        if (comparison == 0)
        {
            // The string was found
            return replacement.second;
        }
    }

    // No value was found, return -1
    return -1;
}
#include <fstream>
#include <string>
#include <iostream>
using namespace std;

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
        totalCount += (firstNumber * 10) + lastNumber;
        
    } 

    cout << totalCount;

    return 0;
}
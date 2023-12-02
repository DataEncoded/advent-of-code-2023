#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Create a struct to hold the results
struct ColorResults
{
    int red = 0;
    int blue = 0;
    int green = 0;
};

ColorResults *parseGame(string*);
void setHighestNumbers(ColorResults*, ColorResults*);

int main()
{
    // Get data
    ifstream myData = ifstream("myData.txt");

    // Create a string to hold the data of each line
    string lineData;

    // Create a second string to hold each round in every game
    string gameData;

    // Create a counter to go in the while loop to count what game we're on
    int gameNumber = 0;

    // Accumulator for the set powers
    int powerSummation = 0;

    // Repeat until end of file
    while (!myData.eof())
    {

        // Get the string of data
        getline(myData, lineData);

        // Cut out the Game : part of the string
        lineData = lineData.substr(lineData.find(":") + 2);

        // Create an int that always know where the newgame split is
        int newGame = lineData.find(";"); 
        
        // Increase gamenumber counter
        gameNumber++;

        // Create results that store highest value of red, green, and blue in every round
        ColorResults* highestValues = new ColorResults();

        // Loop until no more semicolons, effectively "splits" the string
        while (lineData.size() > 0)
        {

            // Only attempt to move along if another semicolon exists
            if (newGame > -1)
            {
                // Get the new data, which is 0 to the next semicolon
                gameData = lineData.substr(0, newGame);

                // Call parseGame to get the correct colors
                ColorResults* results = parseGame(&gameData);

                // Now adjust the highestValues ColorResult
                setHighestNumbers(highestValues, results);

                // Set line equal to the new game, which is the semicolon + 2
                lineData = lineData.substr(newGame + 2);
                // Then set the new value to keep moving down the line
                newGame = lineData.find(";");
            } else {
                // In this case, the entire string is the final game
                // Other than that, do the same thing as before
                ColorResults* results = parseGame(&lineData);

                // Now adjust the highestValues ColorResult
                setHighestNumbers(highestValues, results);

                // No more semicolons, set linedata to nothing
                lineData = "";
            }

        }
        
        // Now do the calculation for the power of the set of cubes
        int powerSet = highestValues->blue * highestValues->green * highestValues->red;

        // Now add it to the power summation
        powerSummation += powerSet;
    }

    // Entire loop is done, close file and output results
    myData.close();
    cout << powerSummation << endl;

    // OK
    return 0;
}

// Function that takes a string of a specific round and returns ColorResults struct
ColorResults* parseGame(string* givenRound)
{
    ColorResults *results = new ColorResults();

    // A place to hold the current total of a number, should be reset on new color
    int currentTotal = 0;

    // Loop over string to ensure we capture all data
    for (int i = 0; i < givenRound->size(); i++)
    {
        char currentCharacter =  givenRound->at(i);

        if (isdigit(currentCharacter))
        {
            // Multiple current total by 10 in order to simulate the 10s place
            currentTotal *= 10;
            // Then, add our digit, converting from ascii to int by subtracting 48
            currentTotal += currentCharacter - 48;
        } else if (currentTotal != 0)
        {
            // Number just ended, time to check what color we just found!
            // currentColor is the string of the color without the space beforehand
            string currentColor = givenRound->substr(i + 1);
            // Get our data in a c_str format for strncmp
            const char *dataCstr = currentColor.c_str();

            if (strncmp(dataCstr, "blue", 4) == 0)
            {
                // Color found, set the property, and reset current total
                results->blue = currentTotal;
                currentTotal = 0;

                // Then skip over the characters in i
                i += 6;
            } else if (strncmp(dataCstr, "red", 3) == 0)
            {
                // Color found, set the property, and reset current total
                results->red = currentTotal;
                currentTotal = 0;

                // Then skip over the characters in i
                i += 5;
            } else if (strncmp(dataCstr, "green", 3) == 0)
            {
                // Color found, set the property, and reset current total
                results->green = currentTotal;
                currentTotal = 0;

                // Then skip over the characters in i
                i += 7;
            }
        }
    }

    return results;
}

// Create a function that will go over a the second parameter ColorResult and set
// the color values of the first parameter ColorResult to the values of the second, if the
// values of the second ColorResult are larger than that of the first, on a case by case basis
void setHighestNumbers(ColorResults* accumulatorResult, ColorResults* currentResult)
{
    // If the current blue is greater than the accumulator blue, set the accumulator blue to current
    if (currentResult->blue > accumulatorResult->blue)
    {
        accumulatorResult->blue = currentResult->blue;
    }
    // Repeat for every color
    if (currentResult->red > accumulatorResult->red)
    {
        accumulatorResult->red = currentResult->red;
    }
    if (currentResult->green > accumulatorResult->green)
    {
        accumulatorResult->green = currentResult->green;
    }
}

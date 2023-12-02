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
bool resultsValid(ColorResults*);

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

    // Counter for the correct successes in order to display when program is done
    int totalSuccess = 0;

    // Repeat until end of file
    while (!myData.eof())
    {
        // Create a valid boolean to tell whether or not the current game is valid or not
        bool valid = true;

        // Get the string of data
        getline(myData, lineData);

        // Cut out the Game : part of the string
        lineData = lineData.substr(lineData.find(":") + 2);

        // Create an int that always know where the newgame split is
        int newGame = lineData.find(";"); 
        
        // Increase gamenumber counter
        gameNumber++;

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

                // Now run checks to see if it matches criteria
                valid = resultsValid(results);

                // Exit loop if the entire round is invalid
                if (valid == false)
                {
                    break;
                }

                // Set line equal to the new game, which is the semicolon + 2
                lineData = lineData.substr(newGame + 2);
                // Then set the new value to keep moving down the line
                newGame = lineData.find(";");
            } else {
                // In this case, the entire string is the final game
                // Other than that, do the same thing as before
                ColorResults* results = parseGame(&lineData);
                valid = resultsValid(results);

                // Exit loop if the entire round is invalid
                if (valid == false)
                {
                    break;
                }

                // No more semicolons, set linedata to nothing
                lineData = "";
            }

        }
        
        // While loop is over, valid should be correct
        if (valid)
        {
            // Valid is true, add the game number to the total
            totalSuccess += gameNumber;
        }
    }

    // Entire loop is done, close file and output results
    myData.close();
    cout << totalSuccess << endl;

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

// Function that takes a pointer to a ColorResults struct and 
// returns whether or not it meets specifications to be valid
bool resultsValid(ColorResults* results)
{
    // Create a flag for valid results
    bool valid = true;

    // Now run checks to see if it matches criteria
    if (results->blue > 14)
    {
        // Didn't match, fail
        valid = false;
    }
    if (results->green > 13)
    {
        valid = false;
    }
    if (results->red > 12)
    {
        valid = false;
    }

    return valid;
}
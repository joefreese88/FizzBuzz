/****************************
*	FizzBuzz Part Three program
*	By: Joseph Freese
*	PRG/410
*	5-30-16
*	Instructor: R. Bradley Andrews
*****************************/

#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <cstring>
#include <time.h>
#include <vector>

using namespace std;

/****************************
*	
*	Class name: CFizzBuzz
*
*	variables: 
*		theRow, theColumn, mainArray
*
*	functions:
*		CFizzBuzzArray(), displayArray(), getIndexValue(), getFizz(), FizzBuzzChecker() 
*
*	Purpose:
*		The point of this class is to store values in an array in the class which will be used in the main class when called. 
*		The class will use its functions to fill the array and check the given row and column to see if the value in that index is a FizzBuzz value
*	
*****************************/
class CFizzBuzz
{

public:
	int theRow;		// stores the row to be checked in the array
	int theColumn;	// stores the column to be checked in the array

	int mainArray[10][10];	// the main array used throughout the program to check FizzBuzz values
	
	// default constructor for CFizzBuzz
	CFizzBuzz()
	{

	}

	/****************************
	*
	*	function name: CFizzBuzzArray
	*
	*	variables:
	*		placeIndex
	*
	*	Return type:
	*		void
	*
	*	Purpose:
	*		The point of this function is to fill or re-fill the mainArray with values to be checked later for FizzBuzz values
	*
	*****************************/
	void CFizzBuzzArray()
	{
		int placeIndex;	// stores a random value to be placed in the current index
		
		srand(time(NULL));

		// two for loops that loop through all 100 indexes of the fbArray and input a random value from 1 to 100 in that position
		for (int firstIndex = 0; firstIndex < 10; firstIndex++)
		{
			for (int secondIndex = 0; secondIndex < 10; secondIndex++)
			{
				placeIndex = rand() % 100 + 1;
				mainArray[firstIndex][secondIndex] = placeIndex;
			}
		}
	}

	/****************************
	*
	*	function name: displayArray
	*
	*	Return type:
	*		void
	*
	*	Purpose:
	*		The point of this function is to display all the values currently in the array
	*
	*****************************/
	void displayArray()
	{
		std::cout << "\nThis is the current array, it shows the row (R) and the column (C) of each value" << endl;
		std::cout << "       C0  C1  C2  C3  C4  C5  C6  C7  C8  C9\n" << endl;

		// Two for loops that go through the main array and display each value in a table
		for (int index = 0; index < 10; index++)
		{
			std::cout << "R" << index << " : ";
			for (int index2 = 0; index2 < 10; index2++)
			{
				printf(" %3d", mainArray[index][index2]);
			}

			std::cout << endl;
		}
	}

	/****************************
	*
	*	function name: getIndexValue
	*
	*	Return type:
	*		int
	*
	*	Purpose:
	*		The point of this small function is to use the current values in theRow and theColumn to return the value placed in that index
	*
	*****************************/
	int getIndexValue()
	{
		return mainArray[theRow][theColumn];
	}

	/****************************
	*
	*	function name: getFizz
	*
	*	variables:
	*		checkFizz
	*
	*	Return type:
	*		string
	*
	*	Purpose:
	*		The point of this function is to check if the value in the given row and column is a FizzBuzz, Buzz, or Fizz value
	*		It uses the FizzBuzzChecker function to check and returns a string describing if it's FizzBuzz, Buzz, Fizz, or no match
	*
	*****************************/
	string getFizz()
	{
		string checkFizz;	// stores a string description of what the value represents (FizzBuzz, Fizz, Buzz, or No Match)
		FizzBuzzChecker(mainArray[theRow][theColumn], checkFizz);

		return checkFizz;
	}

	/****************************
	*
	*	function name: FizzBuzzChecker
	*
	*	variables:
	*		value, threeDivisible, fiveDivisible
	*
	*	Return type:
	*		void
	*
	*	Purpose:
	*		The point of this function is to check if the value is a FizzBuzz, Buzz, Fizz, or No Match
	*		The results can be obtained by calling the getFizz() function
	*
	*****************************/
	void FizzBuzzChecker(int checkValue, string &checkString)
	{
		int value = checkValue;	// int value stores the current value to be calculated

			int threeDivisible = value % 3;		// checks if the current value is divisible by 3	
			int fiveDivisible = value % 5;		// checks if the current value is divisible by 5

			// if the value is divisible by 3 it will then check if it's divisible by 5 and output and set checkString to FizzBuzz, otherwise just Fizz
			if (threeDivisible == 0)
			{
				if (fiveDivisible == 0)
				{
					checkString = " - FizzBuzz";
				}
				else
				{
					checkString = " - Fizz";
				}
			}

			// if the value is divisible by 5 it will set checkString to "Buzz" for the value
			// It already knows it is not divisible by 3, so if it is not divisible by 5 then checkString will be set to "NO Match"
			else if (fiveDivisible == 0)
			{
				checkString = " - Buzz";
			}

			else
			{
				checkString = " - No Match";
			}
		}
};	// end of CFizzBuzz class

std::vector<std::string> finalStrings; // a vector to store all the final strings to be written to a file

// main class
int main()
{
	ofstream lastfile;	// declare a file to be used to write strings to it

	CFizzBuzz ArrayGroup;	// declare string object for the array in the CFizzBuzz class

	int row = -2;		// store the row number for array in class
	int column = -2;	// store the column number for array in class
	string line;		// stores the entire string output from the open file

	ifstream myfile("MyTestFile.txt");

	// while the file is open, each character read is added to the string line, if file can't be opened then a message will display
	std::cout << "The following was read from the file" << endl;
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			cout << line << '\n';
		}
		myfile.close();
	}

	else { cout << "Unable to open file"; }

	std::string str(line);
	
	ArrayGroup.CFizzBuzzArray();	// fill array
	ArrayGroup.displayArray();

	bool firstNegative = false;		// boolean variable changes to true when first negative number is found
	bool secondNegative = false;	// boolean variable changes to true when second negative number is found
	int negativeCount = 0;	// keeps track of the number of negative values found in the file, which will actually be -1's

	// for loop that adds all the values from the file to the class array
	for (std::string::iterator it = str.begin(); it != str.end(); ++it)
	{
		char value = *it;	// char variable that stores the currently checked character

		// switch statement where the chosen case depends on what is in char value
		switch (value)
		{
			// if value is ' ', then proceed to next char
			case ' ':
			{
				break;
			}

			// if value is ',' then proceed to next char
			case ',':
			{
				break;
			}

			// if value is '-' then increment and change boolean variables
			case '-':
			{
				negativeCount++;

				// this will change firstNegative to true on the first '-' find, and change secondNegative to true on the second '-' find
				if (negativeCount == 1)
				{
					firstNegative = true;
				}

				else 
				{
					secondNegative = true;
					negativeCount = 0;
				}
			
				break;
			}

			// otherwise proceed with default
			default:
			{
				int intVal = (int)value - 48;	// converts the char value to an integer and stores in intVal
			
				// if row == -2, that means it hasn't been given it's value from the file, so that will be done first
				if (row == -2)
				{
					row = intVal;
				}

				// if the two negative values were found, then refill the array and set row and column back to -2 
				else if ((firstNegative == true) && (secondNegative == true))
				{
					ArrayGroup.CFizzBuzzArray();
	
					row = -2;
					column = -2;

					firstNegative = false;
					secondNegative = false;
				}

				// if row already has a value other than -2, then column will be given the next value, then that row and column will be checked
				else
				{
					column = intVal;
			
					std::string rowString = std::to_string(row);		// convert row integer to a string to be included in writing to file
					std::string columnString = std::to_string(column);	// convert column integer to a string to be included in writing to file

					ArrayGroup.theRow = row;
					ArrayGroup.theColumn = column;

					std::string indexString = std::to_string(ArrayGroup.getIndexValue());	// gets the actual value from the current array index and converts it to a string

					string finalString = "[" + rowString + "]" + "[" + columnString + "] => " + indexString + " ------- " + ArrayGroup.getFizz();	// the final string to be written to the file
					
					finalStrings.insert(finalStrings.end(), finalString);	

					row = -2;
					column = -2;
				
				}
			}
		}
	}
	
	lastfile.open("FizzBuzzTestOutput.txt");

	std::cout << "\nThe following was written to a file" << endl;

	// a for loop that goes through all strings in finalStrings vector to be written to the file
	for (int index = 0; index < finalStrings.size(); index++)
	{
		std::cout << finalStrings[index] << endl;
		
		lastfile << finalStrings[index] << endl;	
	}	

	lastfile.close();

	system("PAUSE");

	return 0;
}

#include "util.h"
using namespace std;


/*******************************************************************
** Function: getInt()
** Description: gets an input and returns the integer value of its char numbers
** Parameters: none
** Pre-conditions: set = to int
** Post-conditions: returns an integer of that string if its possible, else 0
*******************************************************************/
int getInt() {
	int output = 0, negitive = 0;
	string input;

    do {
        getline(cin, input);	//get input from user
		if(isInt(input) == false) {
			cout << "\nPlease enter a positive integer: ";
		}

    }while(isInt(input) == false);  //keep going untill its valid

    for(unsigned int i = 0; i < input.length(); i++) { //loop through input
        if(input[i] >= 48 && input[i] <= 57) { //if in range, add specific num
                 output += (input[i] - 48) * pow(10, ((input.length() - i) -1)); //pow() to get number in correct place
          }

          else if(i == 0){	//if first char is -, input still valid
              if(input[i] == '-')
                negitive = 1;       
            }
        }

        //applies negitivity right before retunring
        if(negitive == 1) { 
            cout << "Please enter a postive integer: ";
			return getInt();
        }

	return output;
}


/*******************************************************************
** Function: checkRange()
** Description: Indicate if a given value is inside of a given upper and lower bounds
** Parameters: int value, int upper_bound, int lower_bound
** Pre-conditions: take three int paramenters
** Post-conditions: return a value of true if inside, false if out
*******************************************************************/
bool checkRange(int value, int upper_bound, int lower_bound) {
	if(value <= upper_bound && value >= lower_bound) {
		return true;	//returns true if in between bounds
	}
	else {
		return false;
	}
}


/*******************************************************************
** Function: isInt()
** Description: Indicate if a given string in an integer
** Parameters: string input
** Pre-conditions: take a string input
** Post-conditions: return true if only numbers, false if not
*******************************************************************/
bool isInt(string input) {
	unsigned int counter = 0;	//counter to make sure all chars are int
	for(unsigned int i = 0; i < input.length(); i++) {	//loop thru string
		if(input[i] >= 48 && input[i] <=57) {
			counter++;	//if in range, add to counter
		}
		else if(i == 0){
			if(input[i] == '-')
				counter++;	//if first char is - sign, also add
		}
	}
	if(counter == input.length()){	//if ALL chars are in range, then return true
	return true;
	}
	else {
	return false;
	}
}
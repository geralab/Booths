/* Gerald Blake
 * Booths Algorithm
 * Be sure to provide enough bits 
 * To obtain correct answer
 * e.g 2 * 2 needs at least 4 bits per operand
 * 7 * 3 needs at least 5 bits per operand
 * 
 * Operation varible will display operation done to previous bit string
 *
 *
 * ONLY INPUT 0s and 1s
 *
 */
#include <iostream>
#include <string>

using namespace std;
string fillString(string character, unsigned int number);
void shift(string &str);
void twosComplement(string& str, int start, int end);
void add(string& str, string multiplicand, int length);


int main()
{
	//variables
	string multiplier, multiplicand, 
	leftProduct, expression, temp, operation, expressCopy;
	unsigned int length;
	unsigned int count = 0;

	cout << " Enter multiplier: ";
	cin >> multiplier;

	length = multiplier.length();

	cout << " Enter multiplicand: ";
	cin >> multiplicand;

	leftProduct = fillString("0",length);
	multiplier += fillString("0",1);
	expression = leftProduct + multiplier;
	// format initial value
	expressCopy = expression;
	expressCopy.insert(expressCopy.length() / 2," | ");
	expressCopy.insert(expressCopy.length() - 1," | ");
	cout << "\n\nInitial" <<" | " << expressCopy << endl;
	
	// ensure that the correct number of passes are made 
	// should be equal to x number of bits
	while(count < length)
	{
		// if last part of the string 11 or 00
		// just shift NOP
		if(expression[expression.length() - 2] == '1' &&  expression[expression.length() - 1] == '1'
		|| expression[expression.length() - 2] == '0' && expression[expression.length() - 1] == '0')
		{
			operation = "nop";
			shift(expression);
		}
		else if(expression[expression.length() - 2] == '0' && expression[expression.length() - 1] == '1')
		{
			operation = "add";
			add(expression,multiplicand,length); // if last part of string 01 just add and shift
			shift(expression);
		}
		else if(expression[expression.length() - 2] == '1' && expression[expression.length() - 1] == '0')
		{
			operation = "sub";
			temp = multiplicand;
			twosComplement(temp,0,temp.length()); // for A and B if 10 subtract negate B and add
			add(expression,temp,length);
			shift(expression);
			
		}
		//format output
		// Please note  that for simplicity operation will display what was done to previous string
		expressCopy = expression;
		expressCopy.insert(expressCopy.length() / 2," | ");
		expressCopy.insert(expressCopy.length() - 1," | ");
		cout << count <<" | " << operation <<" | " << expressCopy << endl;
		count++;
	}
	// pause for debuging  this may be omitted  and is not necessary for the program
	cin>>multiplier;
	return 0;
}
// adds desired character to string
string fillString(string character, unsigned int number)
{
	string str;
	for(unsigned int i = 0; i < number; i++)
		str += character;
	return str;
}
// shifts elements in string to the right eliminates last element
// copies first element adds it the front of string
void shift(string &str){
	str = str[0] + str;
	str = str.substr(0,str.length() - 1);
}
// adds multiplicand to left half of str 
// utilizing the equation 2^3 and to check all permutations for binary
void add(string& str, string multiplicand,  int length)
{
	char carry = '0';
		for(int i =  length - 1; i > - 1; i--)
		{
				if(str[i] == '0' && multiplicand[i] == '0' && carry == '0')
				{ 

					str[i] = '0';
					carry = '0';

				}
				else if(str[i] == '0' && multiplicand[i] == '0' && carry == '1') 
				{
					str[i] = '1';
					carry = '0';
				
				}
				else if(str[i] == '0' && multiplicand[i] == '1' && carry =='0') 
				{
					str[i] = '1';
					carry = '0';
				
				}
				else if(str[i] == '0' && multiplicand[i] == '1' && carry == '1') 
				{
					str[i] = '0';
					carry = '1';
				
				} 
				else if(str[i] == '1' && multiplicand[i] == '0' && carry == '0') 
				{
					str[i] = '1';
					carry = '0';
				
				} 
				else if(str[i] == '1' && multiplicand[i] == '0' && carry == '1') 
				{
					str[i] = '0';
					carry = '1';
				
				}
				else if(str[i] == '1' && multiplicand[i] == '1' && carry == '0') 
				{
					str[i] = '0';
					carry = '1';
				
				} 
				else if(str[i] == '1' && multiplicand[i] == '1' && carry == '1') 
				{
					str[i] = '1';
					carry = '1';
				
				} 
		}
	}







void twosComplement(string& str, int start , int end){
	char carry = '0';
	// do ones complement
	for( int i = 0; i < end; i++)
	{
		if(str[i] == '0')
		
			str[i] = '1';
		else
			str[i] = '0';
		

	}
	//Add 1 to do twos complement
	for(int i =  end - 1; i > -1; i--)
	{
		if(i ==  end - 1) //step 1
		{
			if(str[end - 1 ] == '0')  //0 + 1
				str[end - 1 ] = '1';
			else if(str[end - 1] == '1') //1+1
			{
				str[end-1] = '0';
				carry = '1';
			}
		} 

		else 

		{
			
			if(carry == '1' && str[i] == '0')
			{
				str[i] = '1';
				carry = '0';
			}
			else if(carry == '1' && str[i] == '1')
			{
				str[i] = '0';
				carry = '1';
			}

		}

	}
}
///
//	learing c++ step 1
//	Clifton Somers
//	05/08/16
//
#include <iostream>
using namespace std;

int main() 
{
	char string[21];
	for(int c = 0; c < 21; ++c) 
	{
		string[c] = '.';//0x20;
	}
	cout << "pleas inpt a string:\n";
	cin >> string;
	cout << string;
}

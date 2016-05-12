///
//	Learn input and output
//	do it from a file
//
#include <iostream>
#include <string>
#include <cstdin>
using namespace std;





void input0()
{



}


int main(int argc, char * argv[])
{
	cout << "\nargc = " << argc << endl;
	for(int a = 0; a < argc; ++a)
	{
		cout << "argv[" << a << "] = " << argv[a] << endl;
	}
}

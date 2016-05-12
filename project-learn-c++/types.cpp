//Figure Out what sizes my computer uses for each datatype
#include <iostream>
#include <string>
using namespace std;

void initforms()
{
	/// Three forms of initializing variables
	int a = 1;
	int b(2);
	//int c{3};newest way (only available in std=c++11 (2011))
	cout << "initforms \n";
	cout << "a = ";
	cout << a;
	cout << "\t";
	cout << "b = ";
	cout << b;
	//cout << c;


	/// Auto and Decltype
	//auto c = a;// c will infer from a, that it need to be an int
	//decltype(b) d;// d will be set to the declared type of b and will be unitialized
	//neither feature appear to work in the standard(older) definition of c++ ===> newer features
}

void stringfun() 
{
	cout << "showsizes \n";
	//LOCAL DECLARATIONS
	string applesauce = "pennsylavania";
	string mango = " 9100";
	string marriage;

	//EXECUTABLE STATEMENTS
	marriage = applesauce.append(mango);
	cout << marriage << endl;
	
}

void assignment() 
{
	int m, n, o, p;
	m = 2 + (n = 5);
	cout << "m = 2 + (n = 5);" << "\tm = " << m << "\tn = " << n << endl;
	o = p = 255;
	cout << "o = p = 255;" << "\to = " << o << "\tp = " << p << endl;
}




void showsizes()
{
	cout << "showsizes \n";
	string str = "sizeof(int) = ";// + (char)(sizeof(int)); 
	cout << str << sizeof(int) << endl;// end line keyword adds \n and flushes the output stream

	cout << "sizeof(float) = " << sizeof(float) << endl;
	cout << "sizeof(char)  = " << sizeof(char ) << endl;
	cout << "sizeof(int*)  = " << sizeof(int* ) << endl;
}

int main() 
{
	cout << "\n\n";
	initforms();
	cout << "\n\n";
	showsizes();
	cout << "\n\n";
	stringfun();
	cout << "\n\n";
	assignment();

}


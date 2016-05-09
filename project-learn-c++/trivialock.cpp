///
//	learing c++ step 1
//	Clifton Somers
//	05/08/16
//
#include <iostream>
#include <cstdin>
#include <string>

#define VAULTFILE "test.txt"

using namespace std;

///
//	class Vault
//		contains the the question and answer data loaded into the program as well
//		as the statistics associated with current and past access attempts.
///
class Vault {
		string * answers;// string array of (encrypted) answers
		string * questions;// string array of (encrypted) questions
		unsigned int vaultcount;//number of entries in the vault
		unsigned int past_accesses;// total previous accesses
		string * failurelog;// a list of failure occurances
	public:
		Vault(FILE*);
		int attempt();
}


///
//	opendata:	opens the data file and allocates a organize for the information
//	
//		params:
//		returns:	vault - contains question and answer data
///		


///
//	decypher:
//		
//		params:		string scramble - encrypted char string
//					string key - tool used to decrypt string
//		returns:	string dec - decrypted string 
///



int main() 
{
	char buffer[100];
	for(int c = 0; c < 21; ++c) 
	{
		string[c] = '.';//0x20;
	}
}

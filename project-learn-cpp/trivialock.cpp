///
//	learing c++ step 1
//	Clifton Somers
//	05/08/16
//
#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <string>
#include <cstring>

#define VAULTFILE		"test.txt"
//#define BUFFERSIZE		256
#define TRUE			1
#define FALSE			0
#define NSECTIONS		3
#define SDELIM			("=")
#define LDELIM			("\n")

using namespace std;






/////////////////////////////////////////////////////////////////
///
//	linked list template or C++
//		abstracts the concept of a node into a generic template
///
template <class T>
class Node {
		Node <T> *next;//the content of the node
	public:
		//conStructors
		Node();
		Node(const T& item, Node<T>* nxt=NULL);
		//~Node();//destructor
		//node content
		T data;
		//methods
		Node<T> *	getnxt();
		void		setnxt(Node<T> * n);
		void		insert(Node<T>* target);
};


template <class T>
Node<T>::Node()
{
	//empty conStructor for vanilla allocation
}

template <class T>
Node<T>::Node(const T& item, Node<T>* next)
{
	this->data = item;
	this->next = next;
}

template <class T>
Node<T>* Node<T>::getnxt()
{
	return this->next;
}

template <class T>
void Node<T>::setnxt(Node<T> * nxt)
{
	this->next = nxt;
}

template <class T>
void Node<T>::insert(Node<T>* target)
{
	// save ptrs
	//Node<T> * after = this->getnxt();     
	Node<T> * end = this;

	// reroute and evaluate
	end->setnxt(target);
}
/*
template <class T>
Node<T>::~Node()
{
	Node<T> * after = this->getnxt();     
	Node<T> * at = this;
	while(after != NULL) {
		delete at;
		at = after;
		after = at->getnxt();
	}
}
*/
/////////////////////////////////////////////////////////////////
///
//	linked list template or C++
//		abstracts the concept of a node into a generic template
///
template <class T>
class List {
		Node<T> *top;
		Node<T>	*bot;
	public:
		// structors
		List();
		List(Node<T>*);
		~List();
		// methods
		Node<T>*	pull(int);
		void		print();
		void		add(Node<T>* imp);
		void		addnew(T data);
		int			isempty();
};

/// empty initialization: conStructs list w/o nodes
template <class T>
List<T>::List() { bot = NULL; top = NULL;  }

// conStructs list with one (1) node
template <class T>
List<T>::List(Node<T> * first) {
	this->top = first;
	this->bot = first;
}

// frees list, top nodes to bottom
template <class T>
List<T>::~List() { 
	Node<T> * ref = this->top;
	Node<T> * nxt;
	while(ref != NULL) {
		nxt = ref->getnxt();
		delete ref;
		ref = nxt;
	}
	//delete this->top;
	//delete this;// this line is not needed why?
}

// pulls the node that is at the labeled index
template <class T>
Node<T> * List<T>::pull(int index) {
	if(this->isempty) return NULL;
	Node<T> * elem = this->top;

	for(int jndex = 0; jndex < index; ++jndex)
	{	
		elem = elem->getnxt();
	}
	return elem;
}

// returns TRUE if there is a node in the list (logic: there is a top node)
template <class T>
int List<T>::isempty() {
	return (this->top == NULL) ? TRUE: FALSE;
}

// adds the given node to the bottom of the list
template <class T>
void List<T>::add(Node<T> * caboose) {
	//if(this->isempty() == TRUE) return;
	this->bot->insert(caboose);
	this->bot = caboose;
}

// adds the given node to the bottom of the list
template <class T>
void List<T>::addnew(T data) {
	//make a new node
	Node<T> * newguy = new Node<T> (data);
	if(this->isempty() == TRUE) {
		this->top = newguy;
		this->bot = newguy;
	}
	else {
		this->bot->insert(newguy);
		this->bot = newguy;
	}
}

// prints the node data in the list from top to bottom
template <class T>
void List<T>::print() {
	Node<T> * ref = this->top;
	int count = 1;
	cout << "\n[[start list\n";
	while(ref != NULL) {
		cout << "data{" << count++ << "} = " << ref->data << endl;
		ref = ref->getnxt();
	}
	cout << "end list]]\n\n";
}



/////////////////////////////////////////////////////////////////
///
//	class Vault
//		contains the the question and answer data loaded into the program as well
//		as the statistics associated with current and past access attempts.
///
class Vault {
		//properties
		unsigned int vaultcount;//number of entries in the vault
		unsigned int past_accesses;// total previous accesses
		string * failurelog;// a list of failure occurances
	public:
		//properties
		List<string> * answers;// string array of (encrypted) answers
		List<string> * questions;// string array of (encrypted) questions
		List<string> * statistics;// 
		//methods
		Vault(FILE*);
		int attempt();
};

Vault::Vault (FILE* fp) {
	//initialization variables
	char * buffer			= NULL;
	unsigned long fSize		= 0;
	size_t result			= 0;
	int index				= 0;
	char * line				= NULL;// a question, answer, or statistic
	char * section			= NULL;// a set of question, answers, stats
	char * target1			= NULL;// section fragment paragraph tokens are read from
	char * target2			= NULL;// paragraph fragment that lines are read from
	List<string> * lstobj	= NULL;// pointer to a new list, Qs, As
	
	//allocate buffer for entire file (assumed small)
	fseek(fp, 0, SEEK_END);
	fSize = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	buffer = new char [fSize];
	//read file and parse
	result = fread(buffer, sizeof(char), fSize, fp);
	cout << buffer;
	if(result != fSize) {
		cerr << "Data Reading Error\n";
	}		
	else {
		target1 = buffer;
		// outter loop :: grab a section from the buffer
		section = strsep(&target1, SDELIM);
		while(section != NULL) 
		{
			cout << "3\n";
			cout << "section = ." << section << ".\n";
			target2 = section;
			lstobj = new List<string>();
			// inner loop :: collect each line of the section into list
			line = std::strtok(target2, LDELIM);
			while (line != NULL) {
				//cout << "line = _" << line << "_\n";
				if(line != NULL)
				lstobj->addnew(line);
				//target2 = NULL;
				line = strsep(&target2, LDELIM);
			}
			cout << "1\n";
			switch(index++) {
				case 0:	this->questions = lstobj;
						break;
				case 1: this->answers = lstobj;
						break;
				case 2: this->statistics = lstobj;
						break;
			}
			cout << "2\n";
			
			//target1 = NULL;
			section = std::strtok(target1, SDELIM);
		}			
		cout << "testfile = " << result << " bytes.\n";
	}
	delete[] buffer;
}

int Vault::attempt() {
	return 0;
}

/////////////////////////////////////////////////////////////////
///
//	decypher:
//		
//		params:		string scramble - encrypted char string,
//					string key - tool used to decrypt string
//		returns:	string dec - decrypted string 
///



/////////////////////////////////////////////////////////////////
///
//	explode:	takes a string and delimiting chars and splits
//				the first into an array of strings w/o preserving
//				the delimeters. The resulting string is in a single 
//				allocated block
//		
//		params:		const string line - input to be parsed
//					const string delim - delimiting chars
//					int * nSec - number of delinations
//		returns		char ** fragments - subsection array
///
char ** explode(const string line, const string delimeters, int& nSec) {
	//LOCAL DECLARATIONS
	unsigned int di;// delimiter index
	unsigned int ci;// character index in line
	unsigned int dc;// delimeter char count
	unsigned int cc;// line char count
	int strx = 0;// expected number of strings
	int nStr = 0;// number of strings created
	int flag = 0;// denotes whether the indexed char is a delimeter
	int prev = 1;// is prev of flag - starts as 1 to ensure 1 char does not generate a str
	int tcount = 0;
	char * lense;// the reference to copy of line
	char * save;// ptr to first char of copy of line
	char * delims;// a c char * of delimiting chars
	char ** fragments = NULL;// return array of delinations 

	//EXECUTABLE STATEMENTS
	delims = (char *) delimeters.c_str();
	save = (char *) line.c_str();
	lense = save;
	cc = line.length();
	dc = delimeters.length();
	//1) determine # of expected strings
	for(ci = 0; ci < cc; ++ci) {
		flag = 0;
		for(di = 0; ((di < dc) && (flag == 0)); ++di) {
			if(lense[ci] == delims[di]) {
				//cout << "char d = " << delims[di] << endl;
				//cout << "char c [" << ci << "] = " << lense[ci] << endl;
				flag = 1;
				//cout << "flag = " << flag << endl;
			}
			//cout << "flag = " << flag << endl;
		}
		if(prev == 0 && flag == 1) { // end of string of non delimeters
			++strx;
			cout << "*" << endl;
		}
		prev = flag;
		//cout << endl;
	}
	if(flag == 0) {
		++strx;
	}
	
	//2) allocate the data for each pointer
	fragments = new char * [strx];// char* for every expected string
	flag = 0;
	ci = 0;
	//3) find the first nondelimeter char in copy of line
	while((*lense != '\0') && (strchr(delims, lense[ci]) != NULL)) {
		flag = 0;
		for(di = 0; ((di < dc) && (flag == 0)); ++di) {
			if(lense[ci] == delims[di]) {
				flag = 1;
			}
		}
		++lense;
		ci += 1;
	}
	cout << "\nlense = \"" << *lense << "\"\n";
	/*
	//4) iterate through and find complete strings
	if(*lense != '\0') {
		fragments[0] = lense;
		nStr = 1;
		tcount = 0;

		while(nStr < dc + 1 && *lense != '\0') {
			if(*lense != '\0') {
				// {if last char was part of delimiter}
				if(flag == 1) {
					// {if curr char is not a delimiter}
					if(strchr(delims, *lense) == NULL) {
						// {if not last fragment: assign part and reset}
						if(nStr < dc + 1) {
							fragments[nStr++] = lense;
							flag = 0;
							tcount = 0;
						}
					}
				}// {check for delimiter at curr char: sever is found}
				else if(strchr(delims, *lense) != NULL) {
					flag = 1;
					fragments[nStr - 1][tcount] = '\0';
				}
				// {update curr char: update char in fragment}
				lense++;
				tcount++;
			}
		}
	}	
	*/
	return(fragments);
	
	nSec = strx;	
}

void test_explode() {
	cout << "\n\nexplode" << endl;
	char ** frags = NULL;
	const string s1 = string("\n\rvedi	veni viki\vand.\fitwasgood\n\n");
	//string("taco... beanstaco.pork... ... ...cheese.");
	const string f1 = string("\t\v\n\f\r ");
	int length = 0;

	frags = explode(s1, f1, length);
	cout << "string1: (" << s1 << ")\n";
	cout << "delim1: (" << f1 << ")\n";
	cout << "length = " << length << endl;
	/*if(length) {
		for(int p = 0; p < length; ++p) {
			cout << "\nfrags[" << p << "] = \"" << frags[p] << "\"";
		}
	}*/
	delete [] frags;
}


/////////////////////////////////////////////////////////////////
///
//	main:
///
int main(int argc, char * argv[]) {
	
	string d1 = "honey";
	string d2 = "dingus";
	Node<string> * biscuit = new Node<string>(d1); 
	Node<string> * ralphi  = new Node<string>(d2); 
	List<string> * litz = new List<string>(biscuit);	
	litz->add(ralphi);
	litz->addnew("ralphi");
	litz->print();
	//List<string> * litz = new List<string>();	
	FILE * fp = fopen(VAULTFILE, "r");
	if(fp == NULL) return(EXIT_FAILURE);
	//Vault * vault = new Vault(fp);	
	
	//cout << "Qs\n";
	//vault->questions->print();
	//cout << "As\n";
	//vault->answers->print();
	//cout << "Ss\n";
	//vault->statistics->print();
	
	delete litz;
	//delete vault;
	fclose(fp);

	test_explode();

}




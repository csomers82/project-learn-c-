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
		//constructors
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
	//empty constructor for vanilla allocation
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
	cout << "woah\n";
}

template <class T>
void Node<T>::insert(Node<T>* target)
{
	// save ptrs
	Node<T> * after = this->getnxt();     
	Node<T> * follow = this;
	Node<T> * end = NULL;

	// reroute and evaluate
	this->setnxt(target);
	if(after == NULL) {
		//cout << "uh oh\n";
		return;
	}
	// find the end of the inserted (list)
	do {
		end = follow->getnxt();
	} while(end != NULL);
	// reattached the end we saved 
	follow->next = after;
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

/// empty initialization: constructs list w/o nodes
template <class T>
List<T>::List() { bot = NULL; top = NULL;  }

// constructs list with one (1) node
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
	if(this->isempty() == TRUE) return;
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
	long fSize				= 0;
	size_t result			= 0;
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
	if(result != fSize) {
		cerr << "Data Reading Error\n";
	}		
	else {
		target1 = buffer;
		// outter loop :: grab a section from the buffer
		for(int index = 0; index < NSECTIONS; ++index) 
		{
			section = std::strtok(target1, SDELIM);
			cout << "3\n";
			cout << "section = ." << section << ".\n";
			if(section == NULL) {
				break;
			}
			target2 = section;
			lstobj = new List<string>();
			// inner loop :: collect each line of the section into list
			do {
				line = std::strtok(target2, LDELIM);
				cout << "line = _" << line << "_\n";
				if(line != NULL)
				lstobj->addnew(line);
				target2 = NULL;
			} while (line != NULL);

			cout << "1\n";
			switch(index) {
				case 0:	this->questions = lstobj;
						break;
				case 1: this->answers = lstobj;
						break;
				case 2: this->statistics = lstobj;
						break;
			}
			target1 = NULL;
			cout << "2\n";
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
	Vault * vault = new Vault(fp);	
	
	cout << "Qs\n";
	vault->questions->print();
	cout << "As\n";
	vault->answers->print();
	cout << "Ss\n";
	vault->statistics->print();
	
	delete litz;
	delete vault;
	fclose(fp);
}




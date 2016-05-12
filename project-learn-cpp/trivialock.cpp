///
//	learing c++ step 1
//	Clifton Somers
//	05/08/16
//
#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <string>

#define VAULTFILE		"test.txt"
//#define BUFFERSIZE		256
#define TRUE			1
#define FALSE			0
#define NSECTIONS		3

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
		int			isempty();
};

template <class T>
List<T>::List() { bot = NULL; top = NULL;  }

template <class T>
List<T>::List(Node<T> * first) {
	this->top = first;
	this->bot = first;
}

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

template <class T>
int List<T>::isempty() {
	return (this->top == NULL) ? TRUE: FALSE;
}

template <class T>
void List<T>::add(Node<T> * caboose) {
	if(this->isempty() == TRUE) return;
	cout << "checkpoint\n";
	this->bot->insert(caboose);
	this->bot = caboose;
}

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
		List<string> * answers;// string array of (encrypted) answers
		List<string> * questions;// string array of (encrypted) questions
		unsigned int vaultcount;//number of entries in the vault
		unsigned int past_accesses;// total previous accesses
		string * failurelog;// a list of failure occurances
	public:
		Vault(FILE*);
		int attempt();
};

Vault::Vault (FILE* fp) {
	//initialization variables
	char * buffer;
	long fSize = 0;
	size_t result = 0;
	char * line;// a question, answer, or statistic
	char * section;// a set of question, answers, stats
	char * target1;
	char * target2;

	//allocate buffer for entire file (assumed small)
	fseek(fp, 0, SEEK_END);
	fSize = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	buffer = new char [fSize];
	//read file and parse
	result = fread(buffer, sizeof(char), fSize, fp);
	if(result != fSize) {
		cerr << "Data Reading Error\n";
		fclose(fp);
		delete[] buffer;
	}		
	else {
	/*	target1 = buffer;
		for(int index = 0; index < NSECTIONS; ++index) 
		{
			section = strtok(target, SDELIM);
			target1 = NULL;
			if(section = NULL) {
				break;
			}
			target2 = section;
			for(int jndex = 0; 
		}
	*/
	}
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
	litz->print();
	//List<string> * litz = new List<string>();	
	//FILE * fp = fopen(VAULTFILE, "r");
	//if(fp == NULL) return(EXIT_FAILURE);
	//Vault * vault = new Vault(fp);	
	

	delete litz;
	//delete vault;
	//fclose(fp);
}

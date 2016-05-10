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
		//node content
		T data;
		//methods
		Node<T> * getnxt();
		void insert(Node<T>* target);
		void destroy(Node<T>* head);
}


template <class T>
Node<T>::Node()
{
	//empty constructor for vanilla allocation
}

template <class T>
Node<T>::Node(const T& item, Node<T>* next=NULL)
{
	this->data = item;
	this->next = next;
}

template <class T>
Node<T>* Node::getnxt()
{
	return this->next;
}

template <class T>
void Node::insert(Node<T>* target)
{
	// save ptrs
	Node<T> * after = target.getnxt();     
	Node<T> * follow = this;
	Node<T> * end = NULL;

	// reroute and evaluate
	target.next = this;
	if(after == NULL) {
		return;
	}
	// find the end of the inserted (list)
	do {
		end = follow.getnxt();
	} while(end != NULL);
	// reattached the end we saved 
	follow->next = after;
}

template <class T>
void Node::destroy(Node<T>* target)
{
	Node<T> * after = target.getnxt();     
	if(after) {
		after.destroy();
	}
	delete target->data;
	delete target;
}

/////////////////////////////////////////////////////////////////
///
//	class Vault
//		contains the the question and answer data loaded into the program as well
//		as the statistics associated with current and past access attempts.
///
class Vault {
		List * answers;// string array of (encrypted) answers
		List * questions;// string array of (encrypted) questions
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
	fSize = ftell(buffer);
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
		target1 = buffer;
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
	FILE * fp = fopen(VAULTFILE, "r");
	if(fp == NULL) return(EXIT_FAILURE);
	Vault * vault = new Vault(fp);	
	
	delete vault;
	fclose(fp);
}

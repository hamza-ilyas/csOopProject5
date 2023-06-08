/*****************************************
 **
 ** File: Lqueue.h
 ** Project: CMSC 202, Project 5, Spring 2019
 ** Author: Hamza Ilyas
 ** Date: 04/27/2019
 ** Section: Discussion - 07, Lecture - 25
 ** E-mail: hamza3@umbc.edu
 **
 **
 ** This file is the implementation of the Lqueue.h file.
 **
 ** Certain functions were defined at the top of some files to maintain
 ** a more aesthetic and minimalistic reading experience
 **
 ** Extra spacing used in certain areas for code readability.
 **
 ** Some curly braces may differ from others. Where a more aesthetic
 ** implementation was possible, it was preferred.
 **
*****************************************/


#include <string>
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

template <class T>
class Node {
public:
  Node( const T& data ); //Node Constructor
  T& GetData(); //Node Data Getter
  void SetData( const T& data ); //Node Data Setter
  Node<T>* GetNext(); //Node m_next getter
  void SetNext( Node<T>* next ); //Node m_next setter
private:
  T m_data; //Holds templated data
  Node<T>* m_next; //Pointer to next node
};

template <class T>
Node<T>::Node( const T& data ) {
   m_data = data;
   m_next = nullptr;
}

template <class T>
T& Node<T>::GetData() {
   return m_data;
}

template <class T>
void Node<T>::SetData( const T& data ) {
   m_data = data;
}

template <class T>
Node<T>* Node<T>::GetNext() {
   return m_next;
}

template <class T>
void Node<T>::SetNext( Node<T>* next ) {
   m_next = next;
}

template <class T>
class Lqueue {
 public:
  // Name: Lqueue() (Linked List Queue) - Default Constructor
  // Desc: Used to build a new linked queue (as a linked list)
  // Preconditions: None
  // Postconditions: Creates a new lqueue where m_head and m_tail point to nullptr
  Lqueue();
  // Name: ~Lqueue() - Destructor
  // Desc: Used to destruct a Lqueue
  // Preconditions: There is an existing lqueue with at least one node
  // Postconditions: An lqueue is deallocated (including dynamically allocated nodes)
  //                 to have no memory leaks!
 ~Lqueue();
  // Name: Lqueue (Copy Constructor)
  // Preconditions: Creates a copy of existing LQueue
  //                Requires a Lqueue
  // Postconditions: Copy of existing Lqueue
  Lqueue(const Lqueue&);
  // Name: operator= (Overloaded Assignment Operator)
  // Preconditions: Copies an Lqueue into an existing Lqueue
  //                Requires a Lqueue
  // Postconditions: Copy of existing Lqueue
  Lqueue<T>& operator= (const Lqueue&);
  // Name: Push
  // Preconditions: Takes in data. Creates new node. 
  //                Requires a Lqueue
  // Postconditions: If the bool = false, adds to front else adds a new node to the
  //                 end of the lqueue.
  void Push(const T&, bool);
  // Name: Pop
  // Preconditions: Lqueue with at least one node. 
  // Postconditions: Removes first node in the lqueue, returns data from first node.
  T Pop();
  // Name: Display
  // Preconditions: Outputs the lqueue.
  // Postconditions: Displays the data in each node of lqueue
  void Display();
  // Name: Front
  // Preconditions: Requires a populated lqueue
  // Postconditions: Returns whatever data is in front 
  T Front();
  // Name: IsEmpty
  // Preconditions: Requires a lqueue
  // Postconditions: Returns if the lqueue is empty.
  bool IsEmpty();
  // Name: GetSize
  // Preconditions: Requires a lqueue
  // Postconditions: Returns m_size
  int GetSize();
  // Name: Swap(int)
  // Preconditions: Requires a lqueue
  // Postconditions: Swaps the nodes at the index with the node prior to it.
  void Swap(int);
  // Name: Clear
  // Preconditions: Requires a lqueue
  // Postconditions: Removes all nodes in a lqueue
  void Clear();
  // Name: TestHeadTail() (Optional test function)
  // Preconditions: Requires a lqueue
  // Postconditions: Returns the value of the head and the tail (used for main below)
  void TestHeadTail();
  // Name: operator<< (Overloaded << operator)
  // Preconditions: Requires a lqueue
  // Postconditions: Returns an ostream with the data from each node on different line
  template <class U>
  friend ostream& operator<<(ostream& output, const Lqueue<U>&);
  //Name: Overloaded [] operator
  //Precondition: Existing Lqueue
  //Postcondition: Returns object from Lqueue using []
  T& operator[] (int x);//Overloaded [] operator to pull data from Lqueue
private:
  Node <T> *m_head; //Node pointer for the head
  Node <T> *m_tail; //Node pointer for the tail
  int m_size; //Number of nodes in queue
};
//*****************************************************************
//Implement Lqueue here

template <class T>
Lqueue<T>::Lqueue(){

  m_head = NULL;
  m_tail = NULL;
  m_size = 0;

}


template <class T>
Lqueue<T>::~Lqueue(){

  Node<T> *temp;

  while(m_head != NULL){

    //deallocate all nodes
    temp = m_head -> GetNext();
    delete m_head;
    m_head = temp;

  }
}


template <class T>
Lqueue<T>::Lqueue(const Lqueue &source){
  
  m_head = source.m_head;
  m_tail = source.m_tail;
  m_size = 0;
  
  Node<T> *temp = source.m_head;

  //copy by pushing in the source's nodes
  while (temp != NULL) {
    
    Push((temp -> GetData()), 1);   
    temp = temp -> GetNext();
     
  }

}


template <class T>
Lqueue<T> &Lqueue<T>::operator =(const Lqueue& lhs){

  Clear();
  //clear to empty all nodes in lhs operand

  Node<T> *temp = lhs.m_head;

  while (temp!= NULL) {
    Push((temp -> GetData()), 1);
    temp = temp -> GetNext();
    //push all nodes from rhs operand to left hand
  }
  
  return *this;   
}


template <class T>
void Lqueue<T>::Push(const T& passed, bool position){
  
  Node <T> *temp = new Node<T>(passed);
  temp -> SetNext(NULL);
  Node <T> *tempS = m_head;
  int size = GetSize();


  //if empty, data is the head
  if (!IsEmpty() ) {
    m_head = temp;
    m_tail = NULL;
    m_size +=1;
    return;
  }
  
  if (position == 1) {
    while (m_head -> GetNext() != NULL){
      
      tempS = tempS -> GetNext();
      
      if (tempS -> GetNext() == NULL){
 
	tempS -> SetNext(temp);
	m_tail = tempS -> GetNext();
	m_size += 1;	
	return;
	
      }
    }
    
    tempS -> SetNext(temp);
    m_size +=1;
  }

  else{

    m_head = temp;
    m_head -> SetNext(tempS);
    
  }
  
  
  
}


template <class T>
T Lqueue<T>::Pop(){

  Node<T> *temp = m_head;
  T returning = m_head -> GetData();

  //get rid of first node and deallocate, then return
  m_head = m_head -> GetNext();
  delete temp;
  return returning;

}

template <class T>
void Lqueue<T>::Display(){

  //display through traversion
  Node<T> *temp = m_head;
  
  while ( temp != NULL) {
    
    cout << temp -> GetData() << endl;
    temp = temp -> GetNext();
      
  }
}


template <class T>
T Lqueue<T>::Front(){

  return m_head -> GetData();
  
}


template <class T>
bool Lqueue<T>::IsEmpty(){

  if(m_size == 0){
    //unpopulated
    return 0; }

  else{
    //populated
    return 1;
  }
}


template <class T>
int Lqueue<T>::GetSize(){

  return m_size;

}


template <class T>
void  Lqueue<T>::Swap(int position){

  //4 temp nodes may be needed
  //the previous' previous, the previous, the one being called on, the one ahead of it
  Node<T> *tempL = m_head;
  Node<T> *tempR = m_head;
  Node<T> *temp2L = m_head;
  Node<T> *tempRP1 = m_head;

  int size = GetSize();

  //if the size is 2, we can just do a one way switch
  if (size == 2) {
    
    tempL = tempL -> GetNext();
    m_head = tempL;
    m_head -> SetNext(tempRP1);
    Node<T> *tempA = m_head -> GetNext();
    tempA -> SetNext(NULL);
    return;
  }

  //this is a special case
  if (size = 3 && (position == 1)){
    
    for (int i = 0; i < (position - 1); i++)
      tempL = tempL -> GetNext();
    
    for (int i = 0; i < position; i++)
      tempR = tempR -> GetNext();
    
    for(int i = 0; i < (position + 1); i++)
      tempRP1 = tempRP1 -> GetNext();
    
    m_head = tempR;
    tempR -> SetNext(tempL);
    tempL -> SetNext(tempRP1);
    return;
  }

  //every other case can be encompassed by this
  for (int i = 0; i < (position - 2); i++)
    temp2L = temp2L -> GetNext();
  
  for (int i = 0; i < (position - 1); i++)
    tempL = tempL -> GetNext();

  for (int i = 0; i < position; i++)
    tempR = tempR -> GetNext();

  for(int i = 0; i < (position + 1); i++)
    tempRP1 = tempRP1 -> GetNext();

  temp2L -> SetNext(tempR);
  tempR -> SetNext(tempL);
  tempL -> SetNext(tempRP1);

}


template <class T>
void Lqueue<T>::Clear(){


  Node<T> *temp = m_head;

  while(m_head != NULL){

    temp = m_head -> GetNext();
    delete m_head;
    //clearing queues by deallocation
    
    m_head = temp;

  }

  m_head = NULL;
  m_size = 0;

}


template <class U>
ostream& operator<<(ostream& output, const Lqueue<U>& source){

  Node<U> *temp = source.m_head;

  //won't be used in the project
  while ( temp != NULL ){
    output << temp -> GetData();
    if (temp -> GetNext() != NULL)
      cout << " -> ";
    temp = temp -> GetNext();
  }

  return output;
}


template <class T>
T& Lqueue<T>::operator[] (int x){
  
  Node<T> *temp = m_head;
  
  int i = 0;
  while (temp != NULL){
    
    if (i == x) {
      return (temp -> GetData()); }
    
    else{
      i+=1;
      temp = temp -> GetNext(); }
    
  }
  
  return temp -> GetData();
}



//****************************************************************
// To test just Lqueue follow these instructions:
//   1.  mv Lqueue.h Lqueue.cpp
//   2.  Uncomment out int main below
//   3.  make Lqueue
//   4.  ./Lqueue (try valgrind too!)

/*
int main () {
  //Test 1 - Default Constructor and Push
  cout << "Test 1 - Default Constructor and Push Running" << endl;
  //Test Default Constructor
  Lqueue <int> newLQ1;
  //Push 4 nodes into Lqueue
  newLQ1.Push(10, 1);
  newLQ1.Push(11, 1);
  newLQ1.Push(12, 1);
  newLQ1.Push(13, 1);
  cout << endl;
  
  //Test 2 - Copy Constructor and Assignment Operator
  cout << "Test 2 - Copy Constructor and Assignment Operator Running" << endl;
  //Test Copy constructor
  Lqueue <int> newLQ2(newLQ1);
  //Test Overloaded Assignment Operator
  Lqueue <int> newLQ3;
  newLQ3 = newLQ1;
  cout << endl;

  //Test 3 - Test Display and Overloaded <<
  cout << "Test 3 - Display and Overloaded << Running" << endl;
  cout << "newLQ1" << endl;
  newLQ1.Display();
  cout << "newLQ2" << endl;
  newLQ2.Display();
  cout << "newLQ3" << endl;
  newLQ3.Display();
  cout << "newLQ1" << endl;
  cout << newLQ1 << endl;
  cout << "newLQ2" << endl;
  cout << newLQ2 << endl;
  cout << "newLQ3" << endl;
  cout << newLQ3 << endl;
  cout << endl;
    
  //Test 4 - Test Front and Pop
  cout << "Test 4 - Front and Pop Running" << endl;
  //Test Front()
  cout << "Testing Front - Output 10" << endl;
  cout << newLQ1.Front() << endl;
  //Test Pop with Display of Pop
  cout << "Popping one node and displaying it" << endl;
  cout << newLQ1.Pop() << endl;
  //Test Pop with Display of Pop
  cout << "Popping one node and displaying it" << endl;
  cout << newLQ1.Pop() << endl;
  cout << endl;
  
  //Test 5 - Test GetSize and Clear
  cout << "Test 5 - GetSize and Clear Running" << endl;
  //Test GetSize()
  cout << "Outputting the size" << endl;
  cout << newLQ1.GetSize() << endl;
  //Test Clear()
  cout << "Clearing all nodes" << endl;
  newLQ1.Clear();
  cout << endl;
  
  //Test 6 - Test Swap
  cout << "Test 6 - Swap Running" << endl;
  newLQ2.Swap(2);
  cout << "Swap 2 - Should display 10->12->11->13->END" << endl;
  newLQ2.Display();
  //Testing to make sure head and tail point at the correct node
  //newLQ2.TestHeadTail();
  //cout << "Should display head 10 and tail 13" << endl;
  //cout << endl;  

  return 0;
}


*/

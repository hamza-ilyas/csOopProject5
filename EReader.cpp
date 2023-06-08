/*****************************************
 **
 ** File: EReader.cpp
 ** Project: CMSC 202, Project 5, Spring 2019
 ** Author: Hamza Ilyas
 ** Date: 04/26/2019
 ** Section: Discussion - 07, Lecture - 25
 ** E-mail: hamza3@umbc.edu
 **
 **
 ** This file is the implementation of the corresponding EReader.h file.
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

#include "EReader.h"


EReader::EReader(){ /* Intentionally left empty */ }


EReader::EReader(string filename){

  cout << "\nWelcome to the UMBC E-Reader! " <<endl;

  LoadCatalog(filename);

}


EReader::~EReader() {

  int size = m_bookCatalog.size();

  for( int i = 0; i < size; i++ ) {

    //deallocate to avoid memory leaks
    delete m_bookCatalog[i];
    m_bookCatalog[i] = nullptr;

  }

}

  

//helper function implemented to reduce redundant code in validation
int EReader::GetValidInput( int min, int max ){

  int choice;
  cin  >> choice;

  while (choice > max || choice < min) {
    
      cout << "Invalid entry, try again: ";
      cin >> choice; }

  return choice;
}


void EReader::LoadCatalog(string filename){

  string line, title, author, rankString, priceString;
  int rank;
  double price;
  
  ifstream file;
  file.open( filename);
  int i = 0;

  
  while( getline ( file, line ) ) {
    
    //used sstream library for reading in
    stringstream stream( line );
    
    getline( stream, title, ',' );
    getline( stream, author, ',' );
    getline( stream, rankString, ',');
    getline( stream, priceString, ',');

    //convert string to specific data types
    rank = stoi( rankString );
    price = stod( priceString);

    //dynamically allocate books and push back into vector
    Book* myBook = new Book(title, author, rank, price);
    m_bookCatalog.push_back(myBook);
    
    
  }
  
  file.close();
  cout << "Catalog populated with "
       << m_bookCatalog.size() << " books." << endl;

}


void EReader::MainMenu(){


  int choice = 0;
  int initialMenu = 0;
  
  while ( choice != 5 ) {

    if ( initialMenu == 0 ) { cout << "\nWhat would you like to do?\n" << endl; }
    if ( initialMenu == 1 ) { cout << "\nWhat would you like to do next? " << endl; }
    cout << "1. Display All Books" << endl;
    cout << "2. Add book to Readlist" << endl;
    cout << "3. Display Readlist" << endl;
    cout << "4. Sort Readlist by Price " << endl;
    cout << "5. Quit\n " << endl;
    
    cout << "Enter: ";

    choice = GetValidInput(1, 5);
    
    if ( choice == 1 ) { DisplayBooks(); }
    if ( choice == 2 ) { AddBook(); }
    if ( choice == 3 ) { DisplayReadlist(); }
    if ( choice == 4 ) {
      
      //call sort size number of times to ensure complete sorting
      for(int i = 0; i < m_readList.GetSize(); i++){
	SortReadlist(); }
    }
    
    if ( choice == 5 ) { cout << "\nThanks for using the UMBC E-Reader!\n" << endl; }
  
    initialMenu = 1;
  }

}
  

void EReader::DisplayBooks(){

  cout << "\n";
  
  //simple display with formatting
  cout << "Book No."
       << setw(50) << "Title"
       << setw(30) << "Author"
       << setw(20) << "Price"
       << "\n" <<endl;
  
  int size = m_bookCatalog.size();

  for( int i = 0; i < size; i++ ) {
    
    cout << setw(5) << i+1 << *m_bookCatalog[i]; }

}



void EReader::AddBook(){

  DisplayBooks();
  
  cout << "\nEnter the number of the book you would like to add: ";

  int choice = GetValidInput(1, 150);
  choice -= 1;
  
  //push book returned by choice
  m_readList.Push( *m_bookCatalog[ choice ], 1 );

}


void EReader::DisplayReadlist(){

  int size = m_readList.GetSize();

  if (size == 0) {
      cout << "\nYou have nothing in your readlist to be displayed." << endl;
      //return to avoid segmentation faults
      return;
    }

  cout << "\n";
  
  Book temp = m_readList[0]; //represents the head of the list
  
  for (int i = 0; i < size; i++){
    cout << setw(5) << i+1 << m_readList[i]; //displaying number in chronological order
  }
}


void EReader::SortReadlist(){


  int size = m_readList.GetSize();

  int i, j;

  for(i = 0; i < size; ++i){

    for(j = 0; j < size-i-1; ++j){

      //call swap if the price is smaller than the next
      if(m_readList[i] < m_readList[i+1])
	 m_readList.Swap(i+1);
    }
  }
}
      


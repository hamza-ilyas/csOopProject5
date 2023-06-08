/*****************************************
 **
 ** File: Book.cpp
 ** Project: CMSC 202, Project 5, Spring 2019
 ** Author: Hamza Ilyas
 ** Date: 04/26/2019
 ** Section: Discussion - 07, Lecture - 25
 ** E-mail: hamza3@umbc.edu
 **
 **
 ** This file is the implementation of the corresponding Book.h file.
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


#include "Book.h"


Book::Book () { /* Intentionally left empty */ }


//overloaded constructor
Book::Book ( string title, string author, int rank, double price ) {

  m_title = title ;
  m_author = author;
  m_rank = rank;
  m_price = price;

}


//single line definitions
string Book::getTitle()const { return m_title; }
string Book::getAuthor()const { return m_author; }
int Book::getRank()const { return m_rank; }
double Book::getPrice()const { return m_price; }
void Book::setTitle ( string title ) { m_title = title; }
void Book::setAuthor ( string author ) { m_author = author; }
void Book::setRank ( int rank ) { m_rank = rank; }
void Book::setPrice ( double price ) { m_price = price; }


//overloaded operator
ostream& operator <<( ostream& output, Book& aBook ) {

  output << "." << setw(50)
	 << aBook.getTitle() << setw( 30 )
	 << aBook.getAuthor()<< setw( 20 )
	 << "$ " << fixed << setprecision(2) << aBook.getPrice() 
	 << endl;
  
  return output;
  
}


//overloaded comparison for sorting 
bool operator < (Book const & lhs, Book const & rhs ) {

  return lhs.getPrice() < rhs.getPrice() ? true : false; 

}





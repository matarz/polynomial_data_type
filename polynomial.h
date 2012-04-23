/* 
   Author: Zakaria Almatar
   Date: 11/27/09
   Class: CS202
   Assignment: Program#3
*/
/*
   File name: polynomial.h
   Contains: Prototypes of the following classes and structures: 
            -structure term: a DLL struct that represents a term
            -class polynomial: represents a polynomial
*/

#include <cstdlib>
#include <iostream>
#include <string.h>
#include <math.h>
using namespace std;

struct term       //DLL node which holds a polynomial term
{
  char sign;      //term's sign
  int coe;        //coefficient
  char var;       //virable
  int exp;        //exponent
  
  term *next;     //pointer to next term
  term *prev;     //pointer to previous term
  
  friend ostream & operator<<(ostream & os, term & t);  //output operator
};


class polynomial        //polynomial class
{
  public:
    polynomial();                        //constructor: sets head to NULL
    polynomial(const polynomial & p);    //copy constructor
    ~polynomial();                       //destructor: deallocates memory
    
    double tot();                   //calculates the total value of a polynomial 

    polynomial & operator=(char *p);               //assignment operator
    polynomial & operator=(const polynomial &pl);  //assignment operator
    polynomial & operator+(const polynomial &pl);  //addition operator
    polynomial & operator+=(const polynomial &pl); //addition operator
    polynomial & operator-(const polynomial &pl);  //subtracting operator
    polynomial & operator-=(const polynomial &pl); //subtracting operator

    int operator==(polynomial &pl);                //equality operator
    int operator!=(polynomial &pl);                //inequality operator
    int operator>(polynomial &pl);                 //greater than operator
    int operator>=(polynomial &pl);                //greater than or equal operator
    int operator<(polynomial &pl);                 //less than operator
    int operator<=(polynomial &pl);                //less than or equal  operator

    term & operator[](int index);                  //subscript operator  
    term & operator++();                            //pre-increment
    term & operator++(int);                         //post-increment
    term & operator--();                            //pre-decrement
    term & operator--(int);                         //post-decrement

    friend ostream & operator<<(ostream & os, polynomial & poly);  //output operator
    friend istream & operator>>(istream & is, polynomial & poly);  //input operator

  private:
    static const int CINLIM = 50;   //cin limit
    term *terms;  //pointer to a hash table
    term *inc_dec;  //for increment and decrement operators
};

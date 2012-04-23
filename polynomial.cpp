/* 
   Author: Zakaria Almatar
   Date: 11/27/09
   Class: CS202
   Assignment: Program#3
*/
/*
   File name: polynomial.cpp
   Functions: This file has functions definitions of:
              class polynomial:
                 -Constructor
                 -Copy Constructor
                 -Destructor
                 -tot: calculates totoal
                 -overloaded operators: (<<,>>,[],+,+=,-,-=,=,==,!=,<,<=,>,>=,++,--)
              structure term:
                 -overloaded operator: (<<)
*/ 

#include <cstdlib>
#include <iostream>
#include <string.h>
#include <math.h>
#include "polynomial.h"
using namespace std;



/*************************************************************************
***                            Constructor                             ***
*************************************************************************/
//sets pointers to NULL
polynomial::polynomial()
{
  terms = NULL;
  inc_dec = NULL;
}

/*************************************************************************
***                         Copy Constructor                           ***
*************************************************************************/
//copies a polynomial into this
polynomial::polynomial(const polynomial & p)
{
  *this = p;
}


/*************************************************************************
***                             Destructor                             ***
*************************************************************************/
//Deallocates memory
polynomial::~polynomial()
{
  if(terms)   //go through each term 
  {
    while(terms->next)
    {
      terms = terms->next;
      delete terms->prev;       //deallocate memory
    }
    delete terms;              //deallocate memory
    terms = NULL;
  }
}

/*************************************************************************
***                               Total                                ***
*************************************************************************/
//returns the total of a polynomial (based on an assumption)
double polynomial::tot()
{
  int assume_x = 5;        //assume x is 5
  double tot1=0,tmp;       //total, and tmp value
  term *p1 = terms;        //pointer to go through each term
  
  while(p1)  //go through each term
  {
     if(p1->exp != 0)  //calculate
       tmp= p1->coe * pow(assume_x,p1->exp);
     else
      tmp = p1->coe;

     if(p1->sign == '-')
       tmp *= -1;
     tot1 += tmp;
     p1 = p1->next;
  }     
  return tot1;    
}

/*************************************************************************
***                            = operator                             ***
*************************************************************************/
//returns this after assigning a string to it
polynomial & polynomial::operator=(char *p)
{
  char *n = p;     //pointer to go through each char in a string
  char num[10];    //to convert a number from a string to an int
  term *cur;       //to go through each term
    
  if(*p)  //if string isn't empty create a new term, give it a sign 
          //a let cur point to it
  {
    terms = new term;
    terms->sign='+'; terms->coe=0; terms->var='0'; terms->exp=0;
    terms->prev = NULL;
    cur = terms;
    cur->next = NULL;
    
    if((*p == '+') || (*p == '-'))
    {
      cur->sign = *p;
      ++p;  
    }
    else
      cur->sign = '+';
  }

  while(*p)   //go through each char in the string 
  {
    if((*p == '+') || (*p =='-'))  //if it's a sign then create a new term
    {                              //and give it the sign
      cur->next = new term;
      cur->next->prev = cur;     
      cur = cur->next;
      cur->sign='+'; cur->coe=0; cur->var='0'; cur->exp=0; 
      cur->next = NULL;
      cur->sign = *p;
    }      

    if((*p >= '0') && (*p <='9'))      //if p's a number then convert it to an
    {                                  //int and assign it to coe
      n = p;
      while((*p >= '0') && (*p <='9'))
        ++p;

      strncpy(num,n,p-n);
      num[p-n]='\0';
      cur->coe = atoi(num);  
      continue;
    }      

    if((*p >= 'A') && (*p <='Z') || (*p >= 'a') && (*p <='z'))
    {                               //if p is a character then assign it to var 
      cur->var = *p;  
      cur->exp = 1;
      if(cur->coe == 0)
        cur->coe = 1;
    }
    
    if(*p == '^')                //if p is ^ then covert the next number to an
    {                            //int and assign it to exp
      n = ++p;
      while((*p >= '0') && (*p <='9'))
        ++p;

      strncpy(num,n,p-n);
      num[p-n]='\0';
      cur->exp = atoi(num);  
      continue;
    }      
    ++p;
  }
  return *this;        //return this 
}

/*************************************************************************
***                            = operator                             ***
*************************************************************************/
//returns this after copying pl into it
polynomial & polynomial::operator=(const polynomial &pl)
{
  term *p1, *p2 = pl.terms;   //pointers to go through each polynomial
   
  if (this != &pl)           //if the two polynomials don't equal eachother
  {                          //then copy the second into the first
    this->~polynomial();    //destroy the content of the first
    p1 = terms;

    if(p2)   //copy content
    {
      if(!p1)   
      {
        p1 = new term;
        p1->prev = NULL;
        p1->next = NULL;
        p1->sign = p2->sign;
        p1->coe = p2->coe;
        p1->var = p2->var;            
        p1->exp = p2->exp;
        terms = p1;
        p2 = p2->next;
      }
      while(p2)
      {
        p1->next = new term;
        p1->next->prev = p1;
        p1->next->next = NULL;
        p1 = p1->next;
        p1->sign = p2->sign;
        p1->coe = p2->coe;
        p1->var = p2->var;            
        p1->exp = p2->exp;
        p2 = p2->next;
      }
    }
  }
  return *this;   //return this
}

/*************************************************************************
***                             + operator                             ***
*************************************************************************/
//returns the result of adding this and pl
polynomial & polynomial::operator+(const polynomial &pl)
{
  int match_exp;           //flag to know if exponents are the same
  polynomial *result = new polynomial;  //creating new poly
  *result = *this;         
  term *p1 = result->terms, *p2 = pl.terms, *tmp;

  while(p2)     //go through each term in pl
  {
    match_exp = 0;
    while(p1)   //go through each term in result
    {
      if(p2->exp == p1->exp)      //if exponenets are the same add coe
      {
        if(p1->sign == '-')      
        {
          p1->coe *= -1;
          p1->sign = '+';
        }
        if(p2->sign == '-')      
          p1->coe -= p2->coe;
        else
          p1->coe += p2->coe;

        if(p1->coe == 0)        //if the result of adding two terms is 0 
        {                      //then delete this node
          tmp = p1->next;
          if(p1->prev)
            p1->prev->next = p1->next;
          if(p1->next)
            p1->next->prev = p1->prev;
          if(result->terms == p1)
            result->terms = tmp;
            
          delete p1;
          p1 = tmp;
        }
        match_exp = 1;   //if added a term, break from inner loop
        break;             
      }      
      p1 = p1->next;
    }

    //if no exponent matched, then add term to result
    p1= result->terms;
    if(!match_exp)
    {
      p1->prev = new term;
      p1->prev->next = p1;
      p1 = p1->prev;
      p1->sign = p2->sign;
      p1->coe = p2->coe;
      p1->var = p2->var;            
      p1->exp = p2->exp;

      result->terms = p1;
    }
    p2 = p2->next;
  }
  return *result;   
}

/*************************************************************************
***                            += operator                             ***
*************************************************************************/
//returns pointer this after adding pl
polynomial & polynomial::operator+=(const polynomial &pl)
{
  return *this = (*this + pl);
}

/*************************************************************************
***                             - operator                             ***
*************************************************************************/
//returns the result of subtracting this and pl
polynomial & polynomial::operator-(const polynomial &pl)
{
  polynomial opp;         //a polynomial which represents pl with oppisite
  opp = pl;               //signs (equivalent to multiplying by -1)
  term *cur = opp.terms;
    
  while(cur)  //go through each term and switch signs
  {  
    if(cur->sign == '+')
      cur->sign = '-';
    else
      cur->sign = '+';
      
    cur = cur->next;
  }                     //return the result of adding this with oppisite 
  return (*this + opp); //(equivalent to <this - pl>)
} 

/*************************************************************************
***                            -= operator                             ***
*************************************************************************/
//returns pointer this after subtracting pl
polynomial & polynomial::operator-=(const polynomial &pl)
{
  return *this = (*this - pl);
}

/*************************************************************************
***                            == operator                             ***
*************************************************************************/
//returns 1 for true, 0 for false
int polynomial::operator==(polynomial &pl)
{
  if(tot() == pl.tot())       //if totals equal return true
    return 1;
    
  return 0;     //else return false
}

/*************************************************************************
***                            != operator                             ***
*************************************************************************/
//returns 1 for true, 0 for false
int polynomial::operator!=(polynomial &pl)
{
  if(tot() != pl.tot())  //if totals don't equal return true
    return 1;
    
  return 0;       //else return false
}

/*************************************************************************
***                            > operator                             ***
*************************************************************************/
//returns 1 for true, 0 for false
int polynomial::operator>(polynomial &pl)
{
  if(this->tot() > pl.tot())     //if first total is greater than 
    return 1;                    //second total return true
    
  return 0;      //else return false
} 

/*************************************************************************
***                            >= operator                             ***
*************************************************************************/
//returns 1 for true, 0 for false
int polynomial::operator>=(polynomial &pl)
{
  if(this->tot() >= pl.tot())     //if first total is greater than or equal to
    return 1;                     //second total return true
    
  return 0;     //else return false
}

/*************************************************************************
***                            < operator                             ***
*************************************************************************/
//returns 1 for true, 0 for false
int polynomial::operator<(polynomial &pl)
{
  if(this->tot() < pl.tot())    //if first total is less than 
    return 1;                   //second total return true
    
  return 0;      //else return false
}

/*************************************************************************
***                            <= operator                             ***
*************************************************************************/
//returns 1 for true, 0 for false
int polynomial::operator<=(polynomial &pl)
{
  if(this->tot() <= pl.tot())    //if first total is less than or equal to
    return 1;                    //second total return true
    
  return 0;      //else return false
}

/*************************************************************************
***                            [] operator                             ***
*************************************************************************/
//returns a pointer to a term
term & polynomial::operator[](int index)
{
  term *cur = terms;          
  for(int i=0;i<index;++i)      //go through terms index number of times
    cur=cur->next; 
    
  return *cur;      //return cur
}

/*************************************************************************
***                        pre ++ operator                             ***
*************************************************************************/
//returns reference to the next term
term & polynomial::operator++()
{
  if(!inc_dec)
    inc_dec = terms;

  inc_dec = inc_dec->next;
  return *inc_dec;
}

/*************************************************************************
***                       post ++ operator                             ***
*************************************************************************/
//returns a reference to the current term and increments the inc_dec pointer
term & polynomial::operator++(int)
{
  if(!inc_dec)
    inc_dec = terms;

  term * tmp = inc_dec;
  inc_dec = inc_dec->next;
  return *tmp;
}

/*************************************************************************
***                        pre -- operator                             ***
*************************************************************************/
//returns reference to the previous term
term & polynomial::operator--()
{
  if(!inc_dec || (inc_dec == terms))
    return *terms;

  inc_dec = inc_dec->prev;
  return *inc_dec;
}

/*************************************************************************
***                        post -- operator                            ***
*************************************************************************/
//returns reference to the current term and decrements the inc_dec pointer
term & polynomial::operator--(int) // for ++it
{
  if(!inc_dec || (inc_dec == terms))
    return *terms;

  term * tmp = inc_dec;
  inc_dec = inc_dec->prev;
  return *tmp;
}

/*************************************************************************
***                       class << operator                            ***
*************************************************************************/
//returns an ostream obj
ostream & operator<<(std::ostream & os, polynomial & poly)
{
  term *cur = poly.terms;  //term pointer to go through poly's terms 
  int sign_f=1;            //flag for signs

  while(cur)   //go trhough each term
  {
    if(cur->coe)   //coe isn't 0
    {
      if(sign_f && cur->sign == '-')   //display sign
        cout<<cur->sign;
      else if(!sign_f)
        cout<<cur->sign;

      sign_f = 0;                
      cout<<" (";
      if(cur->coe !=1 && cur->coe != -1)    //if coe isn't 1 or -1 
        cout<<cur->coe;                     //display coe
      else if(cur->coe == -1)
        cout<<"-";
        
      if(cur->exp)                     //if exp is not 0 then
      {                                // display var
        cout<<cur->var;
        if(cur->exp !=1)            //if exp isn't 1 then display exp
          cout<<"^"<<cur->exp;            
      }
      cout<<") ";
    }
    cur = cur->next;     //go to next term
  }
  return os;    //return ostream
}

/*************************************************************************
***                            >> operator                             ***
*************************************************************************/
//returns an istream object
istream & operator>>(istream & is, polynomial & poly)
{
  char temp[polynomial::CINLIM];
  is.get(temp, polynomial::CINLIM);   //get input
  if (is)
    poly = temp;           //assign it to poly
  while (is && is.get() != '\n')
    ;

  return is;       //return is
}

/*************************************************************************
***                        struct << operator                          ***
*************************************************************************/
//returns an ostream obj
ostream & operator<<(ostream & os, term & t)  //output operator
{
  if(t.coe)   //coe isn't 0
  {
    cout<<t.sign<<" (";
    if(t.coe !=1 && t.coe != -1)    //if coe isn't 1 or -1 
      cout<<t.coe;                     //display coe
    else if(t.coe == -1)
      cout<<"-";

    if(t.exp)                     //if exp is not 0 then
    {                                // display var
      cout<<t.var;
      if(t.exp !=1)            //if exp isn't 1 then display exp
        cout<<"^"<<t.exp;            
    }
      cout<<") ";
  }       
  return os;      
}

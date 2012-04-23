#include <cstdlib>
#include <iostream>
#include <string.h>
#include <math.h>
#include "polynomial.h"
#include "windows.h"
using namespace std;


int menu();
void test(polynomial &p1, polynomial &p2);
void user_test();


/*************************************************************************
***                               Main                                 ***
*************************************************************************/
//
int main()
{
  int choice;
  char *s;
  polynomial poly1, poly2;
  poly1 = "4x^2-3x^1+7";
  poly2 = "2x^3+3x^2+9x+3";

  choice = menu();
  if(choice == 1) 
    test(poly1, poly2); 
  else if (choice == 2) 
    user_test();
 
    system("PAUSE");
  return 0;
}

/*************************************************************************
***                               Menu                                 ***
*************************************************************************/
//returns user's choice
int menu()
{
  int choice;

  cout<<"\nWhat would you like to do?\n";
  cout<<"   1- Run Operators Test\n";
  cout<<"   2- Add your own polynomials\n";
  cout<<"   0- Quit\n";

  cin>>choice;   

  return choice;
}

/*************************************************************************
***                               Test                                 ***
*************************************************************************/
//tests all operators on two polynomials
void test(polynomial &p1, polynomial &p2)
{
  cout<<" << Operator (cout<<polynomial1): "<<p1<<endl;
  cout<<" << Operator (cout<<polynomial2): "<<p2<<endl;

  cout<<"Loading.";      //this is just for fun 
  for(int i=0;i<10;++i)
  {
    cout<<".";
    cout.flush();
    Sleep(500);
  }

  cout<<"\n + Operator (cout<<polynomial1 + polynomial2)\n   "<<p1+p2<<endl;
  cout<<"\n - Operator (cout<<polynomial1 + polynomial2)\n   "<<p1-p2<<endl;
  cout<<"\n -= Operator (cout<<polynomial1 -= polynomial2): \n   "<<(p1 -= p2)<<endl;
  cout<<"\n += Operator (cout<<polynomial1 += polynomial2): \n   "<<(p1 += p2)<<endl;   
  cout<<"\n = Operator (cout<<polynomial1 = polynomial2): \n   "<< (p1 = p2)<<endl;
  cout<<"\n = Operator (cout<<polynomial1 = \"4x^2-3x^1+7\"): \n   "
      << (p1 = "4x^2-3x^1+7")<<endl;

  cout<<"\n == Operator (cout<<polynomial1 == polynomial2): "<<(p1 == p2) <<endl;
  cout<<"\n != Operator (cout<<polynomial1 != polynomial2): "<<(p1 != p2) <<endl;
  cout<<"\n > Operator (cout<<polynomial1 > polynomial2): "<<(p1 > p2) <<endl;
  cout<<"\n >= Operator (cout<<polynomial1 <= polynomial2): "<<(p1 >= p2) <<endl;
  cout<<"\n < Operator (cout<<polynomial1 < polynomial2): "<<(p1 < p2) <<endl;
  cout<<"\n <= Operator (cout<<polynomial1 <= polynomial2): "<<(p1 <= p2) <<endl;      

  cout<<"\n cout<<polynomial2: \n"<<p2<<endl;
  cout<<"\n ++polynomial2;"<<endl;
  ++p2;
  cout<<"\n [] Operator (cout<<polynomial2[0]): "<<p2[0]<<endl;
  cout<<"\n Post ++ Operator (cout<<polynomial2++): "<<p2++<<endl;
  cout<<"\n Pre ++ Operator (cout<<++polynomial2): "<<++p2<<endl;
  cout<<"\n Post -- Operator (cout<<polynomial2--): "<<p2--<<endl;      
  cout<<"\n Pre -- Operator (cout<<--polynomial2): "<<--p2<<endl;
}

/*************************************************************************
***                            User Test                               ***
*************************************************************************/
//takes two polynomials from the user and tests all operators on them
void user_test()
{
  polynomial p1, p2;
  
  cin.ignore();
  cout<<"Enter the first polynomial (must have no spaces or brackets): ";
  cout<<"\n(example: \"4x^2-3x+7\")\n   ";
  cin>>p1;
     
  cout<<"Enter the second polynomial (must have no spaces or brackets): ";
  cout<<"\n(example: \"4x^2-3x+7\")\n   ";
  cin>>p2;
  
  test(p1,p2);
}


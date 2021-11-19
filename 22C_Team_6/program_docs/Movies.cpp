// Implementation file for the Movie class
// Written By: A. Student
// Changed By:
// IDE: Xcode


#include <iostream>
#include <iomanip>
#include <string>

#include "Movies.h"


using namespace std;

//**************************************************
// Constructor
//**************************************************
Movie::Movie()
{
    rank = -1;
    code = "";
    name = "";
    cost = -1;
}

//**************************************************
// Overloaded Constructor
//**************************************************
Movie::Movie(int rk, string cd, string nm, int ct)
{
    rank = rk;
    code = cd;
    name = nm;
    cost = ct;
}





// overloaded operators
/* Write your code here to define the following oveloaded operator:
    - the stream insertion operator ( << )
 */

bool Movie::operator==(const Movie& right)
{
    return (code == right.code);  // Overloaded ==
}


bool Movie::operator>(const Movie& right)
{
    return (code > right.code);  // Overloaded >
}


bool Movie::operator<(const Movie& right)
{
    return (code < right.code);  // Overloaded >
}

ostream& operator<<(ostream& out, const Movie& s)
{
    out << left;
    out << " " << setw(4) << s.code << " ";
    out << " " << setw(2) << s.rank << " ";
    out << " " << setw(27) << s.name << " ";
    out << right;
    out << " " << setw(7) << s.cost << " ";
    out << left << endl;

    return out;
}
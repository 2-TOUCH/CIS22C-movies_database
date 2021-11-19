// Specification file for the Movie class
// Written By: A. Student
// Changed By:
// IDE: Xcode

#ifndef MOVIES_H
#define MOVIES_H


#include<string>

using std::string;
using std::ostream;

class Movie; // Forward Declaration

// Function Prototypes for Overloaded Stream Operators
ostream& operator << (ostream&, const Movie&);

class Movie
{
private:
    string code;
    string name;
    int rank;
    int cost;

public:
    //constructors
    Movie();
    Movie(int, string, string, int);


    //setters
    void setCode(string cd) { code = cd; }
    void setName(string nm) { name = nm; }
    void setRank(int rk) { rank = rk; }
    void setCost(int cs) { cost = cs; }

    //getters
    string getCode() const { return code; }
    string getName() const { return name; }
    int getRank() const { return rank; }
    int getCost() const { return cost; }



    // overloaded operators
     /* Write your code here */

    // Friends
    friend ostream& operator << (ostream&, const Movie&);
    bool operator > (const Movie& right);
    bool operator < (const Movie& right);
    bool operator == (const Movie& right);
};

#endif

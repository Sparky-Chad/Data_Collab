#ifndef STUDENT_H
#define STUDENT_H

#include <string>


using namespace std;
// Acts as the base class, more of an abstract class if working
// by java login. Defines the data in the rest of them which
// are then able to change which piece of data actually matters

class student_base
{
public:
    int MNumber;
    string fname;
    string lname;
    
    student_base() 
    {
        MNumber = 0;
        fname = "";
        lname = "";
    }
    student_base(int inM, string inf, string inl)
    {
        MNumber = inM;
        fname = inf;
        lname = inl;
    }
    
    virtual bool operator==(student_base&);
    virtual bool operator>(student_base&);
    virtual bool operator<(student_base&);

    virtual bool operator>=(student_base&);
    virtual bool operator<=(student_base&);

};


class student_fname: public student_base
{
public:
    student_fname() : student_base{}
    {}

    student_fname(int inM, string inf, string inl) : student_base{inM, inf, inl}
    {}

    bool operator==(student_base& other) { return this->fname.compare(other.fname) == 0; }
    bool operator>(student_base& other) { return this->fname.compare(other.fname) > 0; }
    bool operator<(student_base& other) {return this->fname.compare(other.fname) < 0; }

    bool operator>=(student_base& other) {return this->fname.compare(other.fname) > -1; }
    bool operator<=(student_base& other) {return this->fname.compare(other.fname) < 1; }
};

class student_lname: public student_base
{
public:
    student_lname() : student_base{}
    {}

    student_lname(int inM, string inf, string inl) : student_base{inM, inf, inl}
    {}

    bool operator==(student_base& other) { return this->lname.compare(other.lname) == 0; }
    bool operator>(student_base& other) { return this->lname.compare(other.lname) > 0; }
    bool operator<(student_base& other) {return this->lname.compare(other.lname) < 0; }

    bool operator>=(student_base& other) {return this->lname.compare(other.lname) > -1; }
    bool operator<=(student_base& other) {return this->lname.compare(other.lname) < 1; }
};

class student_Mnumber: public student_base
{
public:
    student_Mnumber() : student_base{}
    {}

    student_Mnumber(int inM, string inf, string inl) : student_base{inM, inf, inl}
    {}

    bool operator==(student_base& other) { return this->MNumber == other.MNumber; }
    bool operator>(student_base& other) { return this->MNumber > other.MNumber; }
    bool operator< (student_base& other) { return this->MNumber < other.MNumber; }

    bool operator>=(student_base& other) { return this->MNumber >= other.MNumber; }
    bool operator<=(student_base& other) { return this->MNumber <= other.MNumber; }
};  


#endif

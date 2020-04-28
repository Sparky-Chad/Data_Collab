#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <sstream>

#include <fstream>
#include <stdlib.h>
#include <ctime>

using namespace std;

// Random names from https://github.com/dominictarr/random-name.git

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

    student_base(const student_base& other)
    {
        MNumber = other.MNumber;
        fname = other.fname;
        lname = other.lname;
    }
    
    virtual ~student_base() {}

    operator std::string();
    
    virtual bool operator==(student_base&){return false;}
    virtual bool operator>(student_base&){return false;}
    virtual bool operator<(student_base&){return false;}

    virtual bool operator>=(student_base&){return false;}
    virtual bool operator<=(student_base&){return false;}

    virtual operator int() {};

protected:
    int string_to_int(std::string in);
};

student_base::operator std::string()
{
    std::ostringstream ss;
    ss << "ID: " << this->MNumber << std::endl;
    ss << "Name: " << this->fname << this->lname << std::endl << std::endl;
}

int student_base::string_to_int(std::string in)
{
    int out = 0;
    for(int i = 0; i < (int)in.length(); i++)
    {
        char a = in[i];
        out += int(a);
    }
    return out;
}

class student_fname: public student_base
{
public:
    student_fname() : student_base{}
    {}

    student_fname(int inM, string inf, string inl) : student_base{inM, inf, inl}
    {}

    ~student_fname(){}

    bool operator==(student_base& other) { return this->fname.compare(other.fname) == 0; }
    bool operator>(student_base& other) { return this->fname.compare(other.fname) > 0; }
    bool operator<(student_base& other) {return this->fname.compare(other.fname) < 0; }

    bool operator>=(student_base& other) {return this->fname.compare(other.fname) > -1; }
    bool operator<=(student_base& other) {return this->fname.compare(other.fname) < 1; }

    operator int() { return this->string_to_int(fname); }
};

class student_lname: public student_base
{
public:
    student_lname() : student_base{}
    {}

    student_lname(int inM, string inf, string inl) : student_base{inM, inf, inl}
    {}

    ~student_lname(){}
    bool operator==(student_base& other) { return this->lname.compare(other.lname) == 0; }
    bool operator>(student_base& other) { return this->lname.compare(other.lname) > 0; }
    bool operator<(student_base& other) {return this->lname.compare(other.lname) < 0; }

    bool operator>=(student_base& other) {return this->lname.compare(other.lname) > -1; }
    bool operator<=(student_base& other) {return this->lname.compare(other.lname) < 1; }

    operator int() { return this->string_to_int(lname); }
};

class student_Mnumber: public student_base
{
public:
    student_Mnumber() : student_base{}
    {}

    student_Mnumber(int inM, string inf, string inl) : student_base{inM, inf, inl}
    {}

    ~student_Mnumber(){}
    bool operator==(student_base& other) { return this->MNumber == other.MNumber; }
    bool operator>(student_base& other) { return this->MNumber > other.MNumber; }
    bool operator< (student_base& other) { return this->MNumber < other.MNumber; }

    bool operator>=(student_base& other) { return this->MNumber >= other.MNumber; }
    bool operator<=(student_base& other) { return this->MNumber <= other.MNumber; }

    operator int() { return this->MNumber; }
};  

class filefail{};

// Small class which can read from a file and be used to return back random words from it
class wordy_random
{
public:

wordy_random(std::string filename);
~wordy_random();
std::string getrandom();

private:
std::string* words;

int size;
};

wordy_random::wordy_random(std::string filename)
{
    std::ifstream ifile(filename);

    if(ifile.fail()) throw filefail();
    this->size = 0;
    string def;
    while(std::getline(ifile, def))
    {

        this->size++;
    }

    // Reset position in file
    ifile.close(); ifile.open(filename);

    //create from the size
    this->words = new std::string[size];

    // slight protection using for loop from buffer overflow
    for(int i = 0; i < size && !ifile.eof(); i++)
    {
        std::getline(ifile, words[i]);
    }

    // Ensure random is properly seeded
    std::srand(std::time(nullptr));

    // class is now created successfully
}

wordy_random::~wordy_random()
{
    // free block of memory
    delete[] words;
}

std::string wordy_random::getrandom()
{
    // remove some random word from index
    return this->words[(int)(std::rand() % this->size)];
}

#endif

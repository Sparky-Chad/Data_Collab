#ifndef WORD_H
#define WORD_H

#include <string>
#include <malloc.h>

class Word
{
private:
    // Private word data
    std::string _word;
    int _count;

public:
    // The constructors will contain preprocessors to output warnings if not called by new as it may result in some form of error
    // Default constructor is declared private to force dynamic allocation of itself at all times
    Word()
    {
        // The word uses string compare to decide how word will interact through the < > == operators
        _word = "";
        // keep a count of words
        _count = 0;
    }
    // Fill constructor first calls the defualt constructor before filling word
    Word(std::string in) : Word()
    {
        _word = in;
    }


    // Getters for the class so that it can function within the binary tree
    int count() { return _count; }
    std::string word() { return _word; }

    // overloaded postfix and prefix incrementors
    // so one can do ++Word or Word++ to do this
    Word& operator++() { this->_count++; return *this; }
    Word operator++(int) { Word temp = *this; ++(*this); return temp; }

    // Comparison operaters
    bool operator ==(Word& in) { return this->_word.compare((in._word)) == 0; }
    bool operator <(Word& in) { return  this->_word.compare((in._word)) < 0; }
    bool operator >(Word& in) { return this->_word.compare(in._word) > 0; }


};

#endif
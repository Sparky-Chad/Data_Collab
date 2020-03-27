
#include <stdio.h>
#include <iostream>
// strings
#include <string>
// file stream
#include <fstream>
// Used to switch words to lower case for consistency
#include <algorithm>
#include <ctype.h>
// string streams
#include <sstream>

using namespace std;

struct Letter_Count {

    char letter;
    int frequency;

};
Letter_Count INIT_COUNT[26] = \
{
    {'A', 0},
    {'B', 0},
    {'C', 0},
    {'D', 0},
    {'E', 0}, 
    {'F', 0},
    {'G', 0},
    {'H', 0},
    {'I', 0},
    {'J', 0},
    {'K', 0},
    {'L', 0},
    {'M', 0},
    {'N', 0},
    {'O', 0},
    {'P', 0},
    {'Q', 0},
    {'R', 0},
    {'S', 0},
    {'T', 0},
    {'U', 0},
    {'V', 0},
    {'W', 0},
    {'S', 0},
    {'Y', 0},
    {'Z', 0}

};
struct Catalog {

    string title;
    string first_name;
    string last_name;
    int word_count = 0;
    Letter_Count count[26];
    int line_count = 0;

};

// Opens file
void get_file(fstream*);
// Fills catalog struct
Catalog fill_catalog(fstream *);
// Checks if char is puncuation or a space
bool word_check(char);
// Returns a formated string from the structure of Catalog
string catalog_card(Catalog &);
// Saves the catalog to a file
void output_catalog(string&);

//Returns if the user wants to continue
bool continue_entry();
// Returns total letter count
int letter_total(Catalog&);
// Prints the letter frequency percent
void letter_output(Catalog&);

int main() {

    do {
        //create empty file stream object
        fstream ifile;
        //create empty Catalog object for use
        Catalog entry;
        //create empty string for output and entry into
        string ostring;

        //open the file in new stream
        get_file(&ifile);
        //fill catalog from file stream and close
        entry = fill_catalog(&ifile);
        ifile.close();

        //Create String from the Catalog
        ostring = catalog_card(entry);

        //output this entry
        cout << "Catalog output:\n" << ostring << endl;

        //output the letter frequency if they want
        letter_output(entry);

        //Output into file
        output_catalog(ostring);

    } while(continue_entry());
    return 0;
}

void get_file(fstream *ifile) {

    //Continues until file opening is completed
    do {

        // Reads input from user as to the name of the file to be opened
        string input;
        cout << "Please input the file name to catalog: ";
        cin >> input;
        cin.ignore();
        
        try {
            // Attempts to open the by creating a new fstream
            // Honestly unsure whether this may leak memory
            *ifile = fstream(input, ios::in);
        }
        catch(exception) {
            // If it fails then rinse and repeat the file opening process
            cout << "***File read error***";
        }
    
    }while(ifile->fail());
}

Catalog fill_catalog(fstream *ifile) {
    
    //init the output catalog
    Catalog output;

    //init letter counter
    for(int i = 0; i < 26; i++) {
        output.count[i] = INIT_COUNT[i];
    }

    //get line which contains the title
    getline(*ifile, output.title, '\r');
    ifile -> ignore();

    //get line which contains the authors name
    getline(*ifile, output.first_name, '\r');
    ifile -> ignore();
    //splits the string at the space and gets the first and last name of the author
    output.last_name = output.first_name.substr(output.first_name.find(' ')+1);
    output.first_name = output.first_name.erase(output.first_name.find(' '));

    //Find Beginning of the content
    string temp;
    do{
        //get line ending on the return character
        getline(*ifile, temp);
        //ignore any excess stream string
        //continues if the line is not contents
    } while(!(temp.substr(0,9) == "Contents:"));


    //while not end of file
    while(!(ifile->eof())) {
        
        //Temp char array which will handle word detection
        char past= ' ';

        //create temporary stream of each file line
        string temp;
        getline(*ifile, temp);
        ifile -> ignore();

        try{
            // Clean the string of escapes
            temp.erase(temp.find('\r'));
        } catch(exception) {}
        //Iterate line counter
        output.line_count++;

        
        //iterate word and letter counters
        for(int i = 0; i < temp.size(); i++) {
            
            //inputs character from line as uppercase for consistency
            transform(temp.begin(), temp.end(), temp.begin(), ::toupper);
            char current = temp[i];
            //Check for each letter
            for(int j = 0; j < 26; j++) {
                //Check for matching letter in array
                if(current == output.count[j].letter) {
                    //increase frequency
                    output.count[j].frequency++;
                    //will end the for loop
                    j = 26;
                }
            }

            //Check for whether there should be a word
            //First check for if current is a space, the initial case for a word
            if(word_check(current)) {
                //Check to make sure the last two characters are not punctuation or a space
                if(!word_check(past)){
                    //increase word count
                    output.word_count++;
                }
            }
            past = current;
        }
    }

    return output;
}

bool word_check(char in) {
    // length of checker array
    int check_length = 7;
    //array of letters to check for
    char checker[] = {' ', ',', '.', '!', ';', ':', '-'};

    for(int i = 0; i < check_length; i++) {
        //will return if any of these are actually a word ender
        if(in == checker[i]) return true;
    }
    //otherwise return as false
    return false;
}

bool continue_entry() {
    //Prompt for another go at the program
    cout << "\n\n***Would you like to enter in another file entry?(y/n): ";
    char input;
    //collect user input
    cin >> input;

    //return and display result
    if(input == 'y') {
        cout << "New Entry\n\n\n";
        return true;
    }
    else {
        cout << "BYE\n\n";
        return false;
    }
}

int letter_count(Catalog &output) {
    //temp var
    int total = 0;
    //iterate by using an iterator
    for(auto& i: output.count) {
        total += i.frequency;
    }
    return total;
}

void letter_output(Catalog &output) {

    //Get the input from user if they wish to see this
    cout  << "Would the user wish to see the percent use of letters?(y/n): ";
    char decision;
    cin >> decision;
    cin.ignore();

    //if yes
    if(decision == 'y') {
        //title
        cout << endl << endl << output.title << " letter frequency: " << endl;
        for(auto& i: output.count) {
            //output each letter as a percent
            double percent = ((double)(i.frequency) / letter_count(output)) * 100;
            cout << i.letter << ": " << percent << '%' << endl;            
        }
    }

}


string catalog_card(Catalog &output) {
    ostringstream ostring;

    ostring << "Title: " << output.title << endl;
    ostring << "Full Name: " << output.first_name << ' ' << output.last_name << '\n';
    ostring << "First Name: " << output.first_name << '\n';
    ostring << "Last Name: " << output.last_name << '\n';
    ostring << "Word Count: " << output.word_count << '\n';
    ostring << "Line Count: " << output.line_count << '\n';

    return ostring.str();
}

void output_catalog(string &out) {

    //Creates the fstream object to append the file
    fstream ofile("CardCatalog.txt", ios::out | ios::app);
    
    //output the string
    ofile << out << endl;

    //close file
    ofile.close();

}
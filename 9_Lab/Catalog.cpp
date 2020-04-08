

// TODO
// Redefine the file output so it sends the ascending list
// Redefine references to catalog tree to tree
// Bug test the current input to make sure it correctly interfaces with the tree
 
// User Defined word class
#include "Word.h"
// User defined binary tree
#include "BinaryTree.h"

#include <stdio.h>
#include <iostream>
// strings
#include <string>
// file stream
#include <fstream>
// Used to switch words to lower case for consistency
#include <algorithm>
// Used to clean all punctuation and other stuffs
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
    Word word();
    BinaryTree<Word> counter;
    int word_count = 0;
    Letter_Count count[26];
    int line_count = 0;

};

// Opens file
void get_file(fstream*);
// Fills catalog struct
void fill_catalog(fstream *, Catalog&);
// Checks if char is puncuation or a space
bool word_check(char);
// Returns a formated string from the structure of Catalog
string catalog_card(Catalog &);
// Saves the catalog to a file
void output_catalog(string&);
// Builds a word string from characters inputed by the program
void build_word(string&, char);
// Adds character to the search tree
void add_word(BinaryTree<Word>&, Word&);

//Returns if the user wants to continue
bool continue_entry();
// Returns total letter count
int letter_total(Catalog&);
// Prints the letter frequency percent
string letter_output(Catalog&);
// Allows the user to select a word to output its values
string search_word_out(Catalog&);


// Create a global catalog tree to store information

int main() {
    bool leave = false;
    do {
        //create empty file stream object
        fstream ifile;
        //create empty Catalog object for use
        Catalog entry;
        //create empty string for output and entry into
        string ostring;
        BinaryTree<Word>::node** list;
        bool entry_empty = true;
        // Creates system so the user can view different outputs
        while (true)
        {
            string out;
            cout << "Select Operation to perform: \n";
            cout << "1. Input file and fill catalog\n2. Print Letter statistics\n3. Find a Word's Frequency\n";
            cout << "4. Output words in ascending order\n5. Output Words in Descending order\n";
            cout << "6. Write Catalog to output File\n7. Exit Program\n";

            cout << "\n Choice: ";
            int choice;
            cin >> choice;
            cin.ignore();
            switch (choice)
            {
                case 1:
                    //open the file in new stream
                    get_file(&ifile);
                    //fill catalog from file stream and close
                    fill_catalog(&ifile, entry);
                    ifile.close();
                    cout << "\nFile Found and Closed\n\n";
                    entry_empty = false;
                break;
                case 2:
                    if(entry_empty) continue;
                    // Send and output letter statistics
                    cout << letter_output(entry) << endl << endl;
                break;
                case 3:
                    if(entry_empty) continue;
                    // Send and output a words frequency
                    cout << search_word_out(entry) << endl << endl;
                break;
                case 4:
                    if(entry_empty) continue;
                    cout << "Getting words...\n";
                    list = entry.counter.getAllAscending();
                    for(int i = 0; i < entry.counter.gsize()-1; i++)
                    {
                        cout << list[i]->data.printr() << endl;
                    }
                    delete[] list;
                    list = nullptr;
                break;
                case 5:
                    if(entry_empty) continue;
                    cout << "Getting words...\n";
                    list = entry.counter.getAllDescending();
                    for(int i = 0; i < entry.counter.gsize()-1; i++)
                    {
                        cout << list[i]->data.printr() << endl;
                    }
                    delete[] list;
                    list = nullptr;
                break;
                case 6:
                    if(entry_empty) continue;
                    cout << "Writing to output file...\n";
                    out = catalog_card(entry);
                    cout << "Output" << out << endl;
                    output_catalog(out);
                    cout << "Success" << endl;
                    entry_empty = true;
                break;
                case 7:
                    leave = true;
                break;      
            }
            if(leave)
            {
                break;
            }
        } 
    } while(!leave);
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
    
    }while(!ifile->is_open());
}

void fill_catalog(fstream *ifile, Catalog& output) {
    
    output.counter = BinaryTree<Word>();

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


    // temporary word string memory
    string wordy;

    //while not end of file
    while(!(ifile->eof())) {
        
        //Temp char array which will handle word detection
        char past= ' ';

        //create temporary stream of each file line
        string temp = "";
        getline(*ifile, temp);
        
        try{
            // Clean the string of escapes
            temp.erase(temp.find('\r'));

            temp.erase(remove_if(temp.begin(), temp.end(), 
                    [](char c) { return iscntrl(c); }), temp.end());
        } catch(exception) {}
        //Iterate line counter
        output.line_count++;
            
        //inputs character from line as uppercase for consistency
        transform(temp.begin(), temp.end(), temp.begin(), ::toupper);
        
        //iterate word and letter counters
        for(int i = 0; i < temp.size(); i++) {
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
                if(!word_check(past) || current == '-'){
                    if(wordy.size() > 0)
                    {
                        //increase word count
                        output.word_count++;
                        Word out = wordy;
                        add_word(output.counter, out);
                        wordy = "";
                    }
                }
            }
            else
            {
                build_word(wordy, current);
            }
            
            
            past = current;
        }
        // Check if the final word is valid
        if(wordy.size() > 0)
        {
            output.word_count++;
            Word out = wordy;
            add_word(output.counter, out);
            wordy="";
        }
    }
}

bool word_check(char in) {
    // length of checker array
    int check_length = 7;
    //array of letters to check for
    char checker[] = {' ', ',', '.', '!', ';', ':', '-'};

    return (bool)(isspace(static_cast<unsigned char>(in)) | ispunct(static_cast<unsigned char>(in)));
/*
    for(int i = 0; i < check_length; i++) {
        //will return if any of these are actually a word ender
        if(in == checker[i]) return true;
    }
    //otherwise return as false
    return false; */
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

string letter_output(Catalog &output) {

    ostringstream ss;
    //title
    ss << endl << endl << output.title << " letter frequency: " << endl;
    for(auto& i: output.count) {
        //output each letter as a percent
        double percent = ((double)(i.frequency) / letter_count(output)) * 100;
        ss << i.letter << ": " << percent << '%' << endl;            
    }
    return ss.str();
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

void build_word(string& word, char in)
{
    word += in;
}

void add_word(BinaryTree<Word>& tree, Word& in)
{
    // finds the word in the tree if able
    BinaryTree<Word>::node* temp = tree.find(in);

    if(temp == nullptr)
    {
        try
        {
            // if it did not find an instance of itself then insert itself into there
            tree.insert(in);
        }
        catch(BinaryTree<Word>::inTreeAlready e)
        {
            cout << "Error when add_word is called" << endl;
            cout << e.print() << endl;
            throw e;
        }
    }
    else
    {
        // if it did find an instance of itself then iterate because it is the pointer to the word within
        // the tree it does not need to reinsert. By using the words iterate value this is able to be done
        // directly to the Word class
        temp->data++;
    }
}

string search_word_out(Catalog& in)
{
    ostringstream ss;
    cout << "\nWord to find: \n";
    string input;
    cin >> input;
    cin.ignore();

    transform(input.begin(), input.end(), input.begin(), ::toupper);

    ss << "Searching...";
    // Sends automatic allocated word to search for
    BinaryTree<Word>::node* inode = in.counter.find(Word(input));
    if(inode == nullptr)
    {
        ss << "Failed to find Word " << input << endl;
    }
    else
    {
        ss << "Success\n";
        ss << "Word: " << inode->data.word() << endl;
        ss << "Frequency: " << inode->data.count();
    }
    return ss.str();
}
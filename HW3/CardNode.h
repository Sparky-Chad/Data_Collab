#ifndef CARDNODE_H_
#define CARDNODE_H_

#include "Deck.h"
#include "Card.h"
// Class which extends the functionality of a card to include a pointer to before and after it
// Class also makes the entire deck dynamic memory safe
class CardNode
{

public:

    CardNode();

    static void create_list(int max_value, int num_cards);

    bool hasnext();

    Card get_data();

    CardNode* next;

    // Enable Deck class function add_card(Card) access to private
    // "dangerous" data and processes
    friend void Deck::add_cards(Card in);

protected:
    // Search array to check if it contains given card
    static bool check_card(Card);
private:
    // This creates an instance of possible cards the nodes may point
    // to and enables them to handle memory issues
    static Card* list;

    Card* data;

    // Create a class to add card data to itself
    static void add_card(Card);
    
};

#endif

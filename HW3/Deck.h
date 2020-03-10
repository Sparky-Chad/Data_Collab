#ifndef DECK_H_
#define DECK_H_  

// Includes definitions of both data types
#include "Card.h"
#include "CardNode.h"
#include "Side.h"

class Deck
{
public:

    // Creates an empty deck, deck should be made with
    // populate decks
    Deck();

    // adds a card to the Deck
    void add_cards(Card);

    // Draws a card from the deck
    Card draw_card();

    // Peeks from the deck without removing the card
    Card peek_card();

    // Passes a card specifically to the deck
    void pass_card(Deck&);

    // Passes card specifically to the Side pile
    void pass_card(Side&);

    // Returns the size of the list
    int get_hand_size();

    // Gets if the deck is empty
    bool is_empty();

    // Returns if queue is currently filled
    bool queue_full();

    // This populates to decks with an equal number of cards
    static void populate_Decks(Deck&, Deck&);


    // Exceptions
    // This is when the deck is completely empty and is being
    // read with nothing in it
    class DeckEmptyException
    {};

    // This is when the Deck has had a card pulled from it
    // and the queue object has not been handled
    class QueueUnhandledException
    {};

    // This is when the Deck is attempting to pass a value without 
    // drawing from the deck
    class QueueUndefinedException
    {};

private:
    // Keep track of size easily
    int size;
    // controls the head or front of the queue
    CardNode *Head;
    // Points to the rear of the card queue
    CardNode *Rear;
    // Holds the last card removed in the queue so it can be passed
    // back to itself or to the other Deck
    //
    // Current locations Q is able to be handled:
    // - draw_card()
    // - pass_cards(D)
    CardNode* Queue;

protected:
    // Appends a linked CardNode List to the Deck
    // Dangerous function as nondynamic allocation breaks the
    // program
    void add_cards(CardNode*);
};


#endif
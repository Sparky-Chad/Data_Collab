
#include "Deck.h"
#include "CardNode.h"
#include "Card.h"

// implements the Deck class

Deck::Deck()
{
    Head = nullptr;
    Rear = nullptr;
    size = 0;
    Queue = nullptr;
}

// add_cards(CardNode)
// Assumes input is a linked list of CardNodes 
// Increases size by the number of elements in the array
void Deck::add_cards(CardNode* in)
{
    CardNode* temp = Rear;

    // If empty then deck will add the list to the front, increasing
    // the size by the length of the list.
    if(is_empty)
    {
        // Set head as in
        Head = in;
        size = 1;
        if(in->next != nullptr) in = in->next;
        
        // set temp towards the end of the array
        temp = Head;
        Rear = temp;
    }

    while(in->next != nullptr)
    {
        
        temp->next = in;
        in = in->next;
        size++;
        
    }
    // Reset Rear to the point where temp currently is
    Rear = temp;

}

// draw_card()
// Will the current head(top card) from the table
// and it will return the card while also holding the value
// of the pointer to it in queue for the event it can transfer
// the card to the other deck

Card Deck::draw_card()
{
    if(is_empty()) throw DeckEmptyException();
    if(queue_full()) throw QueueUnhandledException();

    // Determine the new value of Head and then return
    CardNode* out = Head;
    if(size > 1)
    {
        Head = out->next;
        size--;
    }
    else 
    {
        Head = nullptr;
        size--;
    }

    // Check the queue value and if it has not been
    // handled elsewhere remove it

    Queue = out;
    return out->get_data();
}

// peek_card
// Returns a card object without actually removing a card from
// the linked list

Card Deck::peek_card()
{
    return Head->get_data();
}

// pass_card(Deck&)
// will test for queue to check the assumption that a card
// has already been drawn, if this is the case then hand the direct
// pointer object safely to the other deck, otherwise it throws
// an exception as the deck has not drawn the card then

void Deck::pass_card(Deck& other)
{
    // if the queue is not full then something is wrong
    if(!queue_full) throw QueueUndefinedException();

    // if the queue is currently full hand it off to the
    // other deck and return


    other.add_cards(Queue);

    // Return Queue to nullptr to handle it
    Queue = nullptr;
    
    return;

    // Otherwise assume that the code wishes 
}

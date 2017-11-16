//
//  main.cpp
//  CardGame
//
//  Created by Marcel on 11/5/17.
//  Copyright © 2017 Marcel. All rights reserved.
//

#include <iostream>
#include <stdlib.h>
#include <string>
#include "HandComparator.h"

using namespace std;

class deck{
private:
	int cards[4][13];
	string suits[4] = {"clubs", "spades", "hearts", "diamonds"};
	string values[13] = {"two", "three", "four", "five", "six", "seven", "eight", "nine", "ten", "Jack", "Queen", "King", "Ace"};
	int cardsDrawn;
	int hands[5][4][13];
	
public:
	deck(void);
	int * draw(int);
	void shuffle(void);
};

deck::deck(void){
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 12; j++) {
			cards[i][j] = 0;
		}
	}
	cardsDrawn = 0;
}

int * deck::draw(int playerNo){
	int suit = rand() % 4;
	int card = rand() % 13;
	
	if (cardsDrawn >= 52) {
		cout << "Deck is empty" << endl;
	}
	
	//We check to make sure the card has not been drawn
	//A 0 in the deck means that it is in, anything else is the number of the player who drew it
	while (cards[suit][card] != 0){
		suit = rand() % 4;
		card = rand() % 13;
	}
	
	cards[suit][card] = playerNo;
	cardsDrawn++;
	cout << values[card] << " of " << suits[suit] << endl;
	
	//spits out an array with {suit number, value number}
	int* foo = (int*) malloc(2 * sizeof(int));
	foo[0] = suit;
	foo[1] = card;
	return foo;
}

int main(void) {
	char gameState;
	int numPlayers = 0;
	string playerNames[5];
	deck myDeck;
	
	cout << "Do you wish to play poker or quit (p or q)?" << endl;
	cin >> gameState;
	
	if (gameState == 'q'){
		return 0;
	}
	
	while (!(numPlayers >= 1 and numPlayers <= 5)) {
		cout << "How many players are playing? ";
		cin >> numPlayers;
	}
	
	for (int i = 0; i < numPlayers; i++) {
		cout << "Enter player name: ";
		cin >> playerNames[i];
	}
	
	//we initialize an array that holds the player's hands
	//playerHands[player number + 1][suit (0) or value (1)][card number (1, 2, 3, 4, or 5)
	int playerHands[numPlayers][2][5];
	
	for (int i = 0; i < numPlayers; i++){
		cout << playerNames[i] << "'s hand:" << endl;
		for (int j = 0; j <= 4; j++){
			//cards are drawn from the deck one at a time and placed into the playerHands location
			int * singleCard = myDeck.draw(i + 1);
			playerHands[i][0][j] = singleCard[0];
			playerHands[i][1][j] = singleCard[1];
		}
		cout << endl;
	}
	
	
}

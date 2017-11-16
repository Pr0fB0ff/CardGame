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
int x;
class Comparator{
private:
	int checkNumPair(int hand[2][5]);
	int check3Kind(int hand[2][5]);
	int check4Kind(int hand[2][5]);
	int checkStraight(int hand[2][5]);
	int checkFlush(int hand[2][5]);
	int checkFullHouse(int hand[2][5]);
	int checkStraightFlush(int hand[2][5]);
	int checkRoyalFlush(int hand[2][5]);
public:
	int getScore(int hand[2][5]);
	string getHand(int score);
};

int Comparator::checkNumPair(int hand[2][5])
{
	int score = 0;
	int firstPair = 0;
	//Check for first pair
	for (int i = 0; i < 5; i++) {
		for (int j = i + 1; j < 5; j++) {
			if (hand[1][i] == hand[1][j]) {
				firstPair = hand[1][i];
				score = 1;
			}
		}
	}
	
	//Check for second pair.
	for (int i = 0; i < 5; i++) {
		for (int j = i + 1; j < 5; j++) {
			if (hand[1][i] == hand[1][j] && hand[1][i] != firstPair) {
				score = 2;
			}
		}
	}
	
	return score;
}

int Comparator::check3Kind(int hand[2][5])
{
	int score = 0;
	int counter = 0;
	
	for (int i = 0; i < 5; i++) {
		int value = hand[1][i];
		for (int i = 0; i < 5; i++) {
			if (hand[1][i] == value) {
				counter++;
				//If three of a kind
				if (counter == 3) {
					score = 3;
					break;
				}
			}
		}
		
	}
	
	return score;
}

int Comparator::check4Kind(int hand[2][5])
{
	int score = 0;
	int counter = 0;
	
	for (int i = 0; i < 5; i++) {
		int value = hand[1][i];
		for (int i = 0; i < 5; i++) {
			if (hand[1][i] == value) {
				counter++;
				//If four of a kind
				if (counter == 4) {
					//score = 7;
					break;
				}
			}
		}
	}
	
	return score;
}

int Comparator::checkStraight(int hand[2][5])
{
	int score = 0;
	int handVals[5];
	for (int i = 0; i < 4; i++) {
		handVals[i] = hand[1][i];
	}
	
	sort(handVals, handVals + 5);
	
	if (hand[1][1] == hand[1][0] + 1 && hand[1][2] == hand[1][0] + 2 && hand[1][3] == hand[1][0] + 3 && hand[1][4] == hand[1][0] + 4) {
		score = 5;
	}
	
	return score;
}

int Comparator::checkFlush(int hand[2][5])
{
	int score = 0;
	int counter = 0;
	
	for (int i = 0; i < 5; i++) {
		int value = hand[0][i];
		for (int i = 0; i < 5; i++) {
			if (hand[0][i] == value) {
				counter++;
			}
			
			if (counter == 5) {
				score = 4;
			}
		}
		counter = 0;
	}
	
	
	
	return score;
}

int Comparator::checkFullHouse(int hand[2][5])
{
	int score = 0;
	int counter = 0;
	int kind = 0;
	bool checkForPair = false;
	
	for (int i = 0; i < 5; i++) {
		int value = hand[1][i];
		for (int i = 0; i < 5; i++) {
			if (hand[1][i] == value) {
				counter++;
			}
			//If three of a kind
			if (counter == 3) {
				kind = hand[1][i];
				checkForPair = true;
				break;
			}
		}
	}
	
	if (checkForPair) {
		for (int i = 0; i < 5; i++) {
			for (int j = i + 1; j < 5; j++) {
				if (hand[1][i] == hand[1][j] && hand[1][i] != kind) {
					score = 6;
				}
			}
		}
	}
	
	return score;
}

int Comparator::checkStraightFlush(int hand[2][5])
{
	int score = 0;
	int checkStrt = checkStraight(hand);
	int checkFlsh = checkFlush(hand);
	
	if (checkStrt > 0 && checkFlsh > 0) {
		score = 8;
	}
	return score;
}

int Comparator::checkRoyalFlush(int hand[2][5]){
	int score = 0;
	
	int handVals[5];
	for (int i = 0; i < 4; i++) {
		handVals[i] = hand[1][i];
	}
	
	sort(handVals, handVals + 5);
	
	if (hand[1][1] == hand[1][0] + 1 && hand[1][2] == hand[1][0] + 2 && hand[1][3] == hand[1][0] + hand[1][4] == hand[1][0] + 4 && hand[1][1] == 10) {
		if (checkFlush(hand) > 0) {
			score = 9;
		}
	}
	
	return score;
}

int Comparator::getScore(int hand[2][5]){
	int score = 0;
	
	score = checkNumPair(hand);
	if (check3Kind(hand) > score) {
		score = check3Kind(hand);
	}
	if (check4Kind(hand) > score) {
		score = check4Kind(hand);
	}
	if (checkStraight(hand) > score) {
		score = checkStraight(hand);
	}
	if (checkFlush(hand) > score) {
		score = checkFlush(hand);
	}
	if (checkFullHouse(hand) > score) {
		score = checkFullHouse(hand);
	}
	if (checkStraightFlush(hand) > score) {
		score = checkStraightFlush(hand);
	}
	if (checkRoyalFlush(hand) > score) {
		score = checkRoyalFlush(hand);
	}
	
	return score;
}

string Comparator::getHand(int score){
	switch (score) {
		case 0:
			return "No Pairs";
			break;
		case 1:
			return "One Pair";
			break;
		case 2:
			return "Two Pairs";
			break;
		case 3:
			return "Three of a Kind";
			break;
		case 4:
			return "Straight";
			break;
		case 5:
			return "Flush";
			break;
		case 6:
			return "Full House";
			break;
		case 7:
			return "Four of a Kind";
			break;
		case 8:
			return "Straight Flush";
			break;
		case 9:
			return "Royal Flush";
			break;
			
			
		default:
			return "Something done broke!";
			break;
	}
}

int main(void) {
	char gameState = '\0';
	int numPlayers = 0;
	string playerNames[5];
	deck myDeck;
	
	while (gameState != 'q'){
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
	
	Comparator gameComparator;
	
	cout << endl << "#####" << endl << gameComparator.getScore(playerHands[0]) << endl << "####";
		
	}

}

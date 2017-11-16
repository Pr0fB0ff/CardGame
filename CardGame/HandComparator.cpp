// HandComparator.cpp : Defines the entry point for the console application.
//

//#include <stdafx.h>
#include <algorithm>
#include <string>

using namespace std;

class Comparator{
private:
	int checkNumPair(int hand[][2][5]);
	int checkNumKind(int hand[][2][5]);
	int checkStraight(int hand[][2][5]);
	int checkFlush(int hand[][2][5]);
	int checkFullHouse(int hand[][2][5]);
	int checkStraightFlush(int hand[][2][5]);
	int checkRoyalFlush(int hand[][2][5]);
public:
	int getScore(int hand[][2][5]);
	string getHand(int score);
};

int Comparator::checkNumPair(int hand[][2][5])
{
	int score = 0;
	int firstPair = 0;
	//Check for first pair
	for (int i = 1; i < 5; i++) {
		for (int j = i + 1; j < 5; j++) {
			if (*hand[1][i] == *hand[1][j]) {
				firstPair = *hand[1][i];
				score = 1;
			}
		}
	}

	//Check for second pair.
	for (int i = 1; i < 5; i++) {
		for (int j = i + 1; j < 5; j++) {
			if (*hand[1][i] == *hand[1][j] && *hand[1][i] != firstPair) {
				score = 2;
			}
		}
	}

	return score;
}

int Comparator::checkNumKind(int hand[][2][5])
{
	int score = 0;
	int counter = 0;

	for (int i = 0; i < 5; i++) {
		int value = *hand[1][i];
		for (int i = 0; i < 5; i++) {
			if (*hand[1][i] == value) {
				counter++;
			}
		}

	}


	//If three of a kind
	if (counter == 3) {
		score = 3;
	}

	//If four of a kind
	if (counter == 4) {
		score = 7;
	}

	return score;
}

int Comparator::checkStraight(int hand[][2][5])
{
	int score = 0;

	sort(hand[1][0], hand[1][5]);

	if (*hand[1][1] == *hand[1][0] + 1 && *hand[1][2] == *hand[1][0] + 2 && *hand[1][3] == *hand[1][0] + 3 && *hand[1][4] == *hand[1][0] + 4) {
		score = 5;
	}

	return score;
}

int Comparator::checkFlush(int hand[][2][5])
{
	int score = 0;
	int counter = 0;

	for (int i = 0; i < 5; i++) {
		int value = *hand[0][i];
		for (int i = 0; i < 5; i++) {
			if (*hand[0][i] == value) {
				counter++;
			}

			if (counter == 5) {
				score = 4;
			}
		}
		counter = 0;
	}

	

	return 0;
}

int Comparator::checkFullHouse(int hand[][2][5])
{
	int score = 0;
	int counter = 0;
	int kind = 0;
	bool checkForPair = false;

	for (int i = 0; i < 5; i++) {
		int value = *hand[1][i];
		for (int i = 0; i < 5; i++) {
			if (*hand[1][i] == value) {
				counter++;
			}
			//If three of a kind
			if (counter == 3) {
				kind = *hand[1][i];
				checkForPair = true;
			}
		}
	}

	if (checkForPair) {
		for (int i = 1; i < 5; i++) {
			for (int j = i + 1; j < 5; j++) {
				if (*hand[1][i] == *hand[1][j] && *hand[1][i] != kind) {
					score = 6;
				}
			}
		}
	}

	return score;
}

int Comparator::checkStraightFlush(int hand[][2][5])
{
	int score = 0;
	int checkStrt = checkStraight(hand);
	int checkFlsh = checkFlush(hand);

	if (checkStrt > 0 && checkFlsh > 0) {
		score = 8;
	}
	return score;
}

int Comparator::checkRoyalFlush(int hand[][2][5]){
	int score = 0;

	sort(hand[1][0], hand[1][5]);

	if (*hand[1][1] == *hand[1][0] + 1 && *hand[1][2] == *hand[1][0] + 2 && *hand[1][3] == *hand[1][0] + 3 && *hand[1][4] == *hand[1][0] + 4 && *hand[1][1] == '10') {
		if (checkFlush(hand) > 0) {
			score = 9;
		}
	}

	return score;
}

int Comparator::getScore(int hand[][2][5]){
	int score = 0;
	
	score = checkNumPair(hand);
	if (checkNumKind(hand) > score) {
		score = checkNumKind(hand);
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

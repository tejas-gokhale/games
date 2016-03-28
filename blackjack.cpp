#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>

using namespace std;

enum Suit
{
	SUIT_SPADE,
	SUIT_HEART,
	SUIT_CLUB,
	SUIT_DIAMOND,
	NUM_OF_SUITS
};

enum Rank
{
	RANK_2,
	RANK_3,
	RANK_4,
	RANK_5,
	RANK_6,
	RANK_7,
	RANK_8,
	RANK_9,
	RANK_10,
	RANK_JACK,
	RANK_QUEEN,
	RANK_KING,
	RANK_ACE,
	NUM_OF_RANKS
};

int NUM_OF_CARDS = NUM_OF_RANKS*NUM_OF_SUITS;
struct Card
{
	Rank rank;
	Suit suit;
};

void func_printCard(const Card &card)
{
	switch (card.suit)
	{
		case SUIT_SPADE:	cout << "S"; break;
		case SUIT_HEART: 	cout << "H"; break;
		case SUIT_CLUB:		cout << "C"; break;
		case SUIT_DIAMOND:	cout << "D"; break;
	}

	switch (card.rank)
	{
		case RANK_2:		cout << "2"; break;
		case RANK_3:		cout << "3"; break;
		case RANK_4:		cout << "4"; break;
		case RANK_5:		cout << "5"; break;
		case RANK_6:		cout << "6"; break;
		case RANK_7:		cout << "7"; break;
		case RANK_8:		cout << "8"; break;
		case RANK_9:		cout << "9"; break;
		case RANK_10:		cout << "10"; break;
		case RANK_JACK:		cout << "J"; break;
		case RANK_QUEEN:	cout << "Q"; break;
		case RANK_KING:		cout << "K"; break;
		case RANK_ACE:		cout << "A"; break;
	}
}

void func_printDeck(Card *deck, int sizeOfDeck)
{
	for (int iii = 0; iii < sizeOfDeck; iii++)
	{
		func_printCard(*(deck+iii));
		cout << endl;
	}
}

void func_swapCard(Card *card1, Card *card2)
{
	Card temp = *card1;
	*card1 = *card2;
	*card2 = temp;
}

void func_shuffleDeck(Card *deck)
{
	srand(time(NULL));
	for (int cardIndex = 0; cardIndex < NUM_OF_CARDS; cardIndex++)
	{
		int randNum = rand() % NUM_OF_CARDS;
		//cout << randNum << endl;
		func_swapCard(&deck[cardIndex], &deck[randNum]);
		//func_printDeck(deck);
	}
}

int func_cardValue(const Card &card)
{
	switch(card.rank)
	{
		case RANK_2:		return 2;
		case RANK_3:		return 3;
		case RANK_4:		return 4;
		case RANK_5:		return 5;
		case RANK_6:		return 6;
		case RANK_7:		return 7;
		case RANK_8:		return 8;
		case RANK_9:		return 9;
		case RANK_10:		return 10;
		case RANK_JACK:		return 10;
		case RANK_QUEEN:	return 10;
		case RANK_KING:		return 10;
		case RANK_ACE:		return 11;
	}
	return 0;
}

int func_playerMove()
{
	int move;
	cout << "Press 1 to HIT or 0 to STAND: ";
	do
	{
		cin >> move;
	} while (move != 1 && move != 0);
	return move;
}

int main()
{
	Card *deck = new Card[NUM_OF_CARDS];

// initialize deck of 52 cards
// ----------------------------
	for (int suitIndex = 0; suitIndex < NUM_OF_SUITS; suitIndex++)
	{
		for (int rankIndex = 0; rankIndex < NUM_OF_RANKS; rankIndex++)
		{
			int cardNum;
			cardNum = (suitIndex * NUM_OF_RANKS) + rankIndex;
			deck[cardNum].suit = static_cast<Suit>(suitIndex);
			deck[cardNum].rank = static_cast<Rank>(rankIndex);
		}
	}
	
	//func_swapCard(&deck[0], &deck[1]);
	//cout << deck << "\t" << deck+1 << endl;
	//cout << deck[0].rank << "\t" << deck[1].rank << endl;
	//cout << deck[0].suit << "\t" << deck[1].suit << endl;

// shuffle deck
// -------------
	func_shuffleDeck(deck);
	//func_printDeck(deck, NUM_OF_CARDS);

// *** BLACKJACK ***
// ------------------
	Card *cardptr = &deck[0];

	int playerScore = 0;
	int dealerScore = 0;
	// deal cards
	// -----------
	dealerScore += func_cardValue(*cardptr++);
	cout << "Dealer's current score: " << dealerScore << endl;
	//cout << dealerScore << func_cardValue(*cardptr);
	playerScore += func_cardValue(*cardptr++);

	int move = 1; 
	int playerBust = 0;
	int dealerBust = 0;
	// Player turn
	while (1)
	{
		cout << "Your current score is: " << playerScore << endl;
		int move = func_playerMove();

		if (move == 1)
			playerScore += func_cardValue(*cardptr++);
		else
			break;
		if (playerScore > 21)
		{
			playerBust = 1;
			break;
		}
	}

	while (dealerScore <= 17 && playerBust == 0)
	{
		dealerScore += func_cardValue(*cardptr++);
		cout << "Dealer's current score is: " << dealerScore << endl;
		if (dealerScore > 17)
			dealerBust = 1;
	}

	// Victory condition
	// -----------------
	if (playerBust == 1)
		cout << "Player busted and lost." << endl;
	else
	{
		if (dealerBust == 1)
			cout << "Dealer busted. Player WINS !!!" << endl;
		else
		{
			if(playerScore > dealerScore)
				cout << "Congratulations !!! Player wins!" << endl;
			else if(playerScore < dealerScore)
				cout << "Sorry... Player loses... :(" << endl;
			else
				cout << "It's a tie. Play again and try your luck!" << endl;
		}
	}
	// Print Scores
	cout << "Player Score: " << playerScore << "\t" << "Dealer Score: " << dealerScore << endl;

// Bhikar Savkar 
/*
// deal (2 players)
// ----------------
	Card *player2 = new Card[NUM_OF_CARDS/2];
	Card *player1 = new Card[NUM_OF_CARDS/2];

	for (int jjj = 0; jjj < NUM_OF_CARDS; jjj++)
	{
		if (jjj %2 == 0)
			player2[jjj /2] = deck[jjj];
		else
			player1[(jjj - 1)/2] = deck[jjj];	
	}
	//func_printDeck(player0, NUM_OF_CARDS/2);
	//func_printDeck(player1, NUM_OF_CARDS/2);

// bhikar-savkar
	int points1 = 0;
	int points2 = 0;
	for(int turn = 0; turn < NUM_OF_CARDS/2; turn++)
	{
		if (player1[turn].rank > player2[turn].rank)
		{
			points1++;
			points2--;
		}
		else if (player1[turn].rank < player2[turn].rank)
		{
			points1--;
			points2++;
		}
	}

	cout << "Player 1 score: " << points1 << endl;
	cout << "Player 2 score: " << points2 << endl;
	cout << "Congratulations ";

	if (points1 > points2)
		cout << "Player 1. You WIN !!!" << endl;
	else if (points1 < points2)
		cout << "Player 2. You WIN !!!" << endl;
	else
		cout << "both players. It's a DRAW... :-/" << endl;
// bhikar savkar end
*/
	return 0;
}



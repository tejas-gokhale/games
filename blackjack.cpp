#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include <windows.h>
#include <unistd.h>
#include <time.h>


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
		cout << " ";
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

void dotDelay(int numOfDots, int pause)
{
	// could have also used sleep(1) for a delay of 1 sec
	// this method works too
	clock_t start;           
	for(int i = 0; i < numOfDots; i++)
	{       
		cout<< " . ";
		start = clock();
		while( clock() < start + pause )
		{
             //pause
		}

	}
	cout << endl;
}


int main()
{
	
	cout << right << setw(50) << setfill(' ') << "Welcome to Simple BlackJack" << endl;
	cout << right << setw(50) << setfill(' ') << "Written by Tejas Gokhale  " << endl;
	cout << right << setw(50) << setfill(' ')<<  "***************************" << endl;

	cout << "Loading ";
	dotDelay(5, 1000);


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

	cout << "Dealer: I'm not going to let you cry about unfair decks after you lose." << endl;
	sleep(2);
	cout << "\t" << "Here... Check for yourself!" << endl;
	
	Card *spades = new Card[NUM_OF_CARDS/4];
	Card *hearts = new Card[NUM_OF_CARDS/4];
	Card *clubs = new Card[NUM_OF_CARDS/4];
	Card *diamonds = new Card[NUM_OF_CARDS/4];

	for (int jjj = 0; jjj < NUM_OF_CARDS/4; jjj++)
	{
		spades[jjj] = deck[jjj];
		hearts[jjj] = deck[jjj+13];
		clubs[jjj] = deck[jjj+26];
		diamonds[jjj] = deck[jjj+39];	
	}
	cout << " -------------------------------------------" << endl;
	cout << " | "; func_printDeck(spades, 13); cout << "| " << endl;
	cout << " | "; func_printDeck(hearts, 13); cout << "| " << endl;
	cout << " | "; func_printDeck(clubs, 13); cout << "| " << endl;
	cout << " | "; func_printDeck(diamonds, 13); cout << "| " << endl;
	cout << " -------------------------------------------" << endl;

	cout << "\n";
	
	//func_swapCard(&deck[0], &deck[1]);
	//cout << deck << "\t" << deck+1 << endl;
	//cout << deck[0].rank << "\t" << deck[1].rank << endl;
	//cout << deck[0].suit << "\t" << deck[1].suit << endl;

// shuffle deck
// -------------
	sleep(2);
	func_shuffleDeck(deck);
	//func_printDeck(deck, NUM_OF_CARDS);
	cout << "Shuffling Deck ";

	// just some swag.. adding delays
	dotDelay(3, 1000);
	cout << endl;


	int startGame;
	cout << "Press ENTER to play. If you have the guts, i.e.: ";
	if (cin.get() == '\n')
	{
// *** BLACKJACK ***
// ------------------
		Card *cardptr = &deck[0];

		int playerScore = 0;
		int dealerScore = 0;
	// deal cards
	// -----------
		cout << "Dealer gets: " << "\t";
		func_printCard(*cardptr);
		cout << "\t";
		dealerScore += func_cardValue(*cardptr++);
		cout << "Dealer's current score: " << dealerScore << endl;
	//cout << dealerScore << func_cardValue(*cardptr);

		cout << "Player gets: " << "\t";
		func_printCard(*cardptr);
		cout << "\t";
		playerScore += func_cardValue(*cardptr++);
		cout << "Your current score is: " << playerScore << endl;

		int move = 1; 
		int playerBust = 0;
		int dealerBust = 0;
	// Player turn
		while (1)
		{
			int move = func_playerMove();

			if (move == 1)
			{
				cout << "You get: " << "\t";
				func_printCard(*cardptr);
				cout << "\t";
				playerScore += func_cardValue(*cardptr++);
				cout << "Your current score is: " << playerScore << endl;
			}
			else
				break;
			if (playerScore > 21)
			{
				playerBust = 1;
				break;
			}
		}

		// dealer turn
		while (dealerScore <= 17 && playerBust == 0)
		{
			if (dealerScore > playerScore)
				break;
			cout << "Dealer gets: " << "\t";
			func_printCard(*cardptr);
			cout << "\t";
			dealerScore += func_cardValue(*cardptr++);
			cout << "Dealer's current score is: " << dealerScore << endl;

			if (dealerScore > 17)
				dealerBust = 1;
		}

	// Victory condition
	// -----------------
		if (playerBust == 1)
			cout << "You busted and lost." << endl;
		else
		{
			if (dealerBust == 1)
				cout << "Dealer busted. You WIN !!!" << endl;
			else
			{
				if(playerScore > dealerScore)
					cout << "Congratulations !!! You win!" << endl;
				else if(playerScore < dealerScore)
					cout << "Sorry... You lose... :(" << endl;
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
}



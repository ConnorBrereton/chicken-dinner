#include <iostream>
#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <cmath>
using namespace std;
 
void Shuffle(bool baCardsDealt[]);
void PrintCard(int iCard);
void PrintHand(int iaHand[], const int kiCardCount);
int GetNextCard(bool baCardsDealt[]);
int ScoreHand(int iaHand[], const int kiCardCount);
void PrintScoresAndHands(int iaDealerHand[], const int kiDealerCardCount, int iaPlayerHand[], const int kiPlayerCardCount);
void PrintPlayerBet(double iPlayerStartBet, double iPlayerTheBet, double iPlayerNewBet, double iPlayerWinBet, double iPlayerLoseBet);
void PrintDealerBet(double iDealerStartBet, double iDealerNewBet, double iDealerWinBet, double iDealerLoseBet);
 
int main() {
	using namespace std;
	//random number generator
	time_t qTime;
	time(&qTime);
	srand(qTime);
 
	bool baCardsDealt[52];
	int iDealerCardCount = 0;
	int iaDealerHand[12];
	int iPlayerCardCount = 0;
	int iaPlayerHand[12];
	double iPlayerStartBet = 100;
	double iDealerStartBet = 0;
	cout<<"Enter your bet "<<endl;
		double iPlayerTheBet;
		cin>> iPlayerTheBet;
 
	//loop hand
	while (true) 
	{
		//shuffle deck
		Shuffle(baCardsDealt);
		//deal hands
		iaPlayerHand[0]		= GetNextCard(baCardsDealt);
		iaDealerHand[0]		= GetNextCard(baCardsDealt);
		iaPlayerHand[1]		= GetNextCard(baCardsDealt);
		iaDealerHand[1]		= GetNextCard(baCardsDealt);
		iDealerCardCount	= 2;
		iPlayerCardCount	= 2;
		iPlayerStartBet		>= 0;
 
		cout << "\n~~~~~~~~~~~~~~~~~~~~~~ New Game ~~~~~~~~~~~~~~~~~~~~~~" << endl;
 
		char cPlayerChoice;
		bool bPlayerHits	= true;
		int iPlayerScore	= ScoreHand(iaPlayerHand, iPlayerCardCount);
		//gameplay
		do
		{
			cout << "Your wager: " << iPlayerTheBet << endl;
			//only show one of dealers cards
			cout << "Dealer's Hand " << endl;
			PrintCard(iaDealerHand[1]);
			cout << endl;
			cout << "Your Hand: Score = " << ScoreHand(iaPlayerHand, iPlayerCardCount) << endl;
			PrintHand(iaPlayerHand, iPlayerCardCount);
			cout << "Current Balance: " << iPlayerStartBet-iPlayerTheBet << endl;
 
			//player move
			cout << "\n Enter Hit(h) or Stay(s): ";
			cin >> cPlayerChoice;
			if (cPlayerChoice == 'h') 
			{
				iaPlayerHand[iPlayerCardCount] = GetNextCard(baCardsDealt);
				++iPlayerCardCount;
			} 
			else if (cPlayerChoice == 's') 
			{
				bPlayerHits = false;
			} 
			else 
			{
				cout << "Enter (h) or (s) " << endl;
			}
			cout << endl;
			//get player data
			iPlayerScore	= ScoreHand(iaPlayerHand, iPlayerCardCount);
		} 
		while (bPlayerHits && iPlayerScore < 22);
 
		//bust checker
		if (iPlayerScore > 21) 
		{
			//player lose dealer win
			cout << "~~~~~~~~~~~ Dealer Won! ~~~~~~~~~~~" << endl;
			PrintScoresAndHands(iaDealerHand, iDealerCardCount, iaPlayerHand, iPlayerCardCount);
			cout << "Dealer's New Balance: " << iDealerStartBet+iPlayerTheBet << endl;
			cout << "Your New Balance: " << iPlayerStartBet-iPlayerTheBet << endl;
		} 
		else 
		{
			//dealer auto hits less than 17
			int iDealerScore = ScoreHand(iaDealerHand, iDealerCardCount);
			while (iDealerScore < 17) 
			{
				iaDealerHand[iDealerCardCount] = GetNextCard(baCardsDealt);
				++iDealerCardCount;
				iDealerScore = ScoreHand(iaDealerHand, iDealerCardCount);
			}
			bool bDealerBusts = (iDealerScore > 21);
			if (bDealerBusts) 
			{
				//dealer lost. player won
				cout << "~~~~~~~~~~~ You Won! ~~~~~~~~~~~" << endl;
				cout << "\n Your New Balance: " << iPlayerStartBet+iPlayerTheBet << endl;
				cout << "\n The Final Hands Were: \n" << endl;
				PrintScoresAndHands(iaDealerHand, iDealerCardCount, iaPlayerHand, iPlayerCardCount);
			} 
			else 
			{
				//score judging
				if (iPlayerScore == iDealerScore) 
				{
					cout << "~~~~~~~~~~~ Tie! ~~~~~~~~~~~" << endl;
					cout << "\n The Final Hands Were: \n" << endl;
				    PrintScoresAndHands(iaDealerHand, iDealerCardCount, iaPlayerHand, iPlayerCardCount);
				} 
				else if (iPlayerScore > iDealerScore) 
				{
					//player wins
					cout << "~~~~~~~~~~~ You Won! ~~~~~~~~~~~" << endl;
					cout << "\n Your New Balance: " << iPlayerStartBet+iPlayerTheBet << endl;
					cout << "\nThe Final Hands Were: \n" << endl;
				    PrintScoresAndHands(iaDealerHand, iDealerCardCount, iaPlayerHand, iPlayerCardCount);
				} 
				else 
				{
					//dealer wins
					cout << "~~~~~~~~~~~ Dealer Wins! ~~~~~~~~~~~" << endl;
					cout << "\n Dealer's New Balance: " << iDealerStartBet+iPlayerTheBet << endl;
					cout << "\n Your New Balance: " << iPlayerStartBet-iPlayerTheBet << endl;
					PrintScoresAndHands(iaDealerHand, iDealerCardCount, iaPlayerHand, iPlayerCardCount);
				}
			}
		}
	}
}
 
void Shuffle(bool baCardsDealt[]) 
{
	for (int iIndex = 0; iIndex < 52; ++iIndex) 
	{
		baCardsDealt[iIndex] = false;
	}
}
 
void PrintCard(int iCard) 
{
	//using namespace std;
	// Print Rank
	int kiRank = (iCard % 13);
	if (kiRank == 0) 
	{
		cout << "Ace of";
	} 
	else if (kiRank < 9) 
	{
		cout << (kiRank + 1);
	} 
	//else if (kiRank == 9) {
	//	cout << 'T';}
	else if (kiRank == 10) 
	{
		cout << "Jack of";
	} 
	else if (kiRank == 11) 
	{
		cout << "Queen of";
	} 
	else 
	{
		cout << "King of";
	}
	// Print Suit
	int kiSuit = (iCard/13);
	if (kiSuit == 0) 
	{
		cout << " Clubs";
	} 
	else if (kiSuit == 1) 
	{
		cout << " Diamonds";
	} 
	else if (kiSuit == 2) 
	{
		cout << " Hearts";
	} 
	else 
	{
		cout << " Spades";
	}
}
 
void PrintHand(int iaHand[], const int kiCardCount) 
{
	using namespace std;
	for (int iCardIndex = 0; iCardIndex < kiCardCount; ++iCardIndex) 
	{
		const int kiNextCard = iaHand[iCardIndex];
		PrintCard(kiNextCard);
		cout << " ";
	}
	cout << endl;
}
 
int GetNextCard(bool baCardsDealt[]) 
{
	bool bCardDealt	= true;
	int iNewCard	= -1;
	do 
	{
		iNewCard = (rand() % 52);
		if (!baCardsDealt[iNewCard]) 
		{
			bCardDealt = false;
		}
	} while (bCardDealt);
	return iNewCard;
}
 
int ScoreHand(int iaHand[], const int kiCardCount) 
{
	int iAceCount = 0;
	int iScore = 0;
	for (int iCardIndex = 0; iCardIndex < kiCardCount; ++iCardIndex) 
	{
		const int kiNextCard = iaHand[iCardIndex];
		const int kiRank = (kiNextCard % 13);
		if (kiRank == 0) 
		{
			++iAceCount;
			++iScore;
		} 
		else if (kiRank < 9) 
		{
			iScore = iScore + (kiRank + 1);
		} 
		else 
		{
			iScore = iScore + 10;
		}
	}
	while (iAceCount > 0 && iScore < 12) 
	{
		--iAceCount;
		iScore = iScore + 10;
	}
	return iScore;
}
 
void PrintScoresAndHands(int iaDealerHand[], const int kiDealerCardCount, int iaPlayerHand[], const int kiPlayerCardCount) 
{
	using namespace std;
	cout << "Dealer's Hand: Score = " << ScoreHand(iaDealerHand, kiDealerCardCount) << endl;
	PrintHand(iaDealerHand, kiDealerCardCount);
	cout << "Your Hand: Score = " << ScoreHand(iaPlayerHand, kiPlayerCardCount) << endl;
	PrintHand(iaPlayerHand, kiPlayerCardCount);
	cout << endl;
}
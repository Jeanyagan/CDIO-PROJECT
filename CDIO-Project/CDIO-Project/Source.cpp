#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// FUNCTIONS
void generateDeck();
void shuffleDeck();
void dealCards();

void baseGameLogic();
void playerGameLogic();
int playerChoice();

void moveCardTableToTable();
void moveCardDeckToTable();
void moveCardTableToFoundation();
void moveCardDecktoFoundation();
void flipDeckCard();

void printCurrentDeck();
void printTable();

void playCalculationAlgorithm();

// STRUCTS
struct Card {
	int cardVal;
	int cardType;
	int cardRow;
	int cardColor;
	int cardFlipped;
};

struct Deck {

	struct Deck* last;
	struct Deck* next;

	struct Card cardInfo;
	int deckPlacement;
	int cardDrawn;
};

struct Deck* head = NULL;
struct Deck* shuffledHead = NULL;
struct Deck* newCard = NULL;
struct Deck* tmpCurrentCard = NULL;
struct Deck* tmpDeckShuffle = NULL;
struct Deck* ERRORCHECKER = NULL;

// GLOBALS
struct Deck* topDeckPointer;
struct Deck* currentDeckFlopPointer;
struct Deck* tableRows[8];
struct Deck* foundationCards[5];
struct Deck* lastMove;

int baseGameState = 1;
int STOP = 0;
int printCounter = 0;
int deckEmpty = 0;
int STOPCOUNTER = 0;
int winValue = 0;
int loseValue = 0;
int checkCounter = 0;

// MAIN
int main(void) {

	while (1) {
		baseGameLogic();
	}
}


// GAME LOGIC FUNCTIONS
void baseGameLogic() {

	switch (baseGameState) {

	case 1: // GENERATE GAME

		generateDeck();
		shuffleDeck();
		dealCards();
		// printCurrentDeck();
		printTable();

		baseGameState++;
		break;

	case 2: // PLAYER MOVES

		playerGameLogic();
		break;

	case 3: // WIN CONDITION
		scanf_s("%d", &STOP);
		break;
	};



}

void playerGameLogic() {

	//printCurrentDeck();
	//printTable();

	switch (12) {

	case 1: // MOVE CARD FROM TABLE ON TABLE

		moveCardTableToTable();
		break;

	case 2: // MOVE CARD FROM TABLE TO FOUNDATION

		moveCardTableToFoundation();
		break;

	case 3: // FLIP TOP DECK CARD

		flipDeckCard();
		break;

	case 4: // MOVE CARD FROM DECK TO TABLE

		moveCardDeckToTable();
		break;

	case 5: // MOVE CARD FROM DECK TO FOUNDATION

		moveCardDecktoFoundation();
		break;

	case 6: // MOVE CARD FROM FOUNDATION TO TABLE

		// NONE ADDED YET
		break;

	case 7: // PRINT TABLE

		printTable();
		break;

	case 8: // PRINT DECK

		printCurrentDeck();
		break;

	case 9: // PRINT FOUNDATIONS

		break;
	case 12: // AI ALGORITHM 
		playCalculationAlgorithm();
		break;

	};
}

int playerChoice() {

	int input = 0;

	printf("1: Moves\t2: Prints\t3: AI\n");
	printf("Input: ");
	scanf_s("%d", &input);

	while (1) {
		if (input == 1) {

			printf("\nMOVE COMMANDS\n");
			printf("1: Table to Table\t2: Table to Foundation\t3: Deck Flip\t4: Deck to Table\t5: Deck to Foundation\t6: Foundation to Table\n");
			printf("Input: ");
			scanf_s("%d", &input);
			break;

		}
		else if (input == 2) {
			printf("\nPRINT COMMANDS\n");
			printf("1: Print Table\t2: Print Deck\t3: Print Foundations\n");
			printf("Input: ");
			scanf_s("%d", &input);
			input = input + 6;
			break;
		}
		else if (input == 3) {
			input = 12;
			break;
		}
		else {
			printf("\n\n\tINPUT ERROR\n");
		}
	}

	return input;
}


// GENERATING GAME
void generateDeck() {

	int valueOfCard = 1;
	int typeOfCard = 1;
	int order = 1;

	printf("\nGenerating new deck!\n\n");

	head = (struct Deck*)malloc(sizeof(struct Deck)); // GENERATE HEAD FOR DOUBLELINKED LIST
	head->last = NULL;
	head->next = NULL;
	head->cardInfo.cardVal = valueOfCard;
	head->cardInfo.cardType = typeOfCard;
	head->cardInfo.cardRow = -1;
	head->cardInfo.cardColor = 1;
	head->deckPlacement = order;
	head->cardInfo.cardFlipped = 0;

	order++;
	valueOfCard++;
	tmpCurrentCard = head;
	printf("\tNEW DECK - Placement: %d Cardtype: %d Cardvalue: %d\n", tmpCurrentCard->deckPlacement, tmpCurrentCard->cardInfo.cardType, tmpCurrentCard->cardInfo.cardVal);

	for (int i = 0; i < 51; i++) { // GENERATE THE REST OF THE DECK

		newCard = (struct Deck*)malloc(sizeof(struct Deck));

		newCard->last = tmpCurrentCard;
		newCard->next = NULL;
		newCard->cardInfo.cardVal = valueOfCard;
		newCard->cardInfo.cardType = typeOfCard;
		newCard->cardInfo.cardRow = -1;
		newCard->cardInfo.cardFlipped = 0;

		if (newCard->cardInfo.cardType == 1 || newCard->cardInfo.cardType == 2) {
			newCard->cardInfo.cardColor = 1;
		}
		else {
			newCard->cardInfo.cardColor = 2;
		}

		newCard->deckPlacement = order;
		valueOfCard++;
		order++;

		newCard->last->next = newCard;

		tmpCurrentCard = newCard;
		printf("\tNEW DECK - Placement: %d Cardtype: %d Cardvalue: %d\n", tmpCurrentCard->deckPlacement, tmpCurrentCard->cardInfo.cardType, tmpCurrentCard->cardInfo.cardVal);


		if (valueOfCard == 14) {
			valueOfCard = 1;
			typeOfCard++;
		}
	}

	printf("\nDeck complete!\n\n");
}

void shuffleDeck() {

	int counter = 1;
	int shufflesLeft = 52;
	int randomNumber;
	time_t t;
	srand((unsigned)time(&t));

	randomNumber = rand() % shufflesLeft;
	shufflesLeft = shufflesLeft - 1;

	printf("Shuffling the new Deck!\n\n");

	tmpCurrentCard = head;

	if (randomNumber == 0) {
		head = head->next;
		shuffledHead = tmpCurrentCard;

		tmpCurrentCard->next->last = NULL;
		tmpCurrentCard->next = NULL;

	}
	else {
		for (int i = 1; i <= randomNumber; i++) {
			tmpCurrentCard = tmpCurrentCard->next;
		}

		if (tmpCurrentCard->next != NULL) {
			tmpCurrentCard->next->last = tmpCurrentCard->last;
			tmpCurrentCard->last->next = tmpCurrentCard->next;
		}
		else {
			tmpCurrentCard->last->next = tmpCurrentCard->next;
		}

		tmpCurrentCard->next = NULL;
		tmpCurrentCard->last = NULL;
		shuffledHead = tmpCurrentCard;

	}

	shuffledHead->deckPlacement = counter;
	counter++;

	tmpCurrentCard = head;
	tmpDeckShuffle = shuffledHead;

	while (shufflesLeft != 0) {

		randomNumber = rand() % shufflesLeft;
		shufflesLeft = shufflesLeft - 1;

		if (randomNumber == 0 && shufflesLeft == 0) {

			tmpCurrentCard->next = NULL;
			tmpCurrentCard->last = tmpDeckShuffle;
			tmpCurrentCard->last->next = tmpCurrentCard;
			tmpCurrentCard->deckPlacement = counter;
		}

		if (randomNumber == 0 && shufflesLeft != 0) {
			head = head->next;

			tmpCurrentCard->next->last = NULL;
			tmpCurrentCard->next = NULL;

			tmpDeckShuffle->next = tmpCurrentCard;
			tmpCurrentCard->last = tmpDeckShuffle;

			tmpCurrentCard->deckPlacement = counter;

		}
		else if (shufflesLeft != 0) {
			for (int i = 1; i <= randomNumber; i++) {
				tmpCurrentCard = tmpCurrentCard->next;
			}

			if (tmpCurrentCard->next != NULL) {
				tmpCurrentCard->next->last = tmpCurrentCard->last;
				tmpCurrentCard->last->next = tmpCurrentCard->next;
			}
			else {
				tmpCurrentCard->last->next = tmpCurrentCard->next;
			}

			tmpDeckShuffle->next = tmpCurrentCard;
			tmpCurrentCard->last = tmpDeckShuffle;
			tmpCurrentCard->next = NULL;
		}
		tmpCurrentCard->deckPlacement = counter;

		tmpDeckShuffle = tmpDeckShuffle->next;
		tmpCurrentCard = head;
		counter++;
	}

	ERRORCHECKER = shuffledHead;
	printf("\tSHUFFLED DECK - Placement: %d Cardtype: %d Cardvalue: %d nextPTR: %p\n", ERRORCHECKER->deckPlacement, ERRORCHECKER->cardInfo.cardType, ERRORCHECKER->cardInfo.cardVal, ERRORCHECKER->next);
	while (ERRORCHECKER->next != NULL) {

		ERRORCHECKER = ERRORCHECKER->next;
		printf("\tSHUFFLED DECK - Placement: %d Cardtype: %d Cardvalue: %d nextPTR: %p\n", ERRORCHECKER->deckPlacement, ERRORCHECKER->cardInfo.cardType, ERRORCHECKER->cardInfo.cardVal, ERRORCHECKER->next);

	}

	printf("\nShuffling deck complete!");

}

void dealCards() {

	int test = 0;
	int tableRow = 1;
	struct Deck* tmpInfoHolder;

	tmpCurrentCard = shuffledHead;

	printf("\n\nDealing cards to Table!");
	printf("\n\n\tERRORCHECKER - TableRow starting at [%d]", tableRow);

	while (tableRow < 8) {

		tmpInfoHolder = tmpCurrentCard;


		for (int i = 0; i < tableRow; i++) {


			if (tableRows[tableRow] == NULL) {

				tableRows[tableRow] = tmpCurrentCard;
				tmpCurrentCard = tmpCurrentCard->next;

				tmpInfoHolder->cardInfo.cardRow = tableRow;
				tmpInfoHolder->next = NULL;
				tmpInfoHolder->last = NULL;

				printf("\n\tERRORCHECKER: Card [Type: %d | Value: %d] was placed in Row [%d]", tmpInfoHolder->cardInfo.cardType, tmpInfoHolder->cardInfo.cardVal, tmpInfoHolder->cardInfo.cardRow);

				if (tableRow == 1) {
					tmpInfoHolder->cardInfo.cardFlipped = 1;
					printf(" - Card is flipped");
				}

			}
			else {

				tmpCurrentCard->cardInfo.cardRow = tableRow;
				tmpCurrentCard->last = tmpInfoHolder;
				tmpCurrentCard->last->next = tmpCurrentCard;

				tmpInfoHolder = tmpCurrentCard;
				if (tmpCurrentCard->next != NULL) {
					tmpCurrentCard = tmpCurrentCard->next;
				}

				if (i == tableRow - 1) {
					tmpInfoHolder->cardInfo.cardFlipped = 1;
				}

				tmpInfoHolder->next = NULL;

				printf("\n\tERRORCHECKER: Card [Type: %d | Value: %d] was placed in Row [%d]", tmpInfoHolder->cardInfo.cardType, tmpInfoHolder->cardInfo.cardVal, tmpInfoHolder->cardInfo.cardRow);

				if (tmpInfoHolder->cardInfo.cardFlipped == 1) {
					printf(" - Card is flipped");
				}

			}
		}

		tableRow++;

		if (tableRow != 8) {
			printf("\n\n\tERRORCHECKER - TableRow increased to [%d]", tableRow);
		}
	}

	printf("\n\nGenerating Cards to Table is complete!");

	topDeckPointer = tmpCurrentCard;
	topDeckPointer->last->next = NULL;
	topDeckPointer->last = NULL;

	printf("\n\n\tERRORCHECKER - topDeckPointer changed to Card [Type: %d | Value: %d] Row [%d]", topDeckPointer->cardInfo.cardType, topDeckPointer->cardInfo.cardVal, topDeckPointer->cardInfo.cardRow);
}


// GAME MOVESETS
void moveCardTableToTable() {

	int playerMove = 0;
	int cardInfo = 0;
	int state = 0;
	struct Deck* tmpInfoHolder;

	printf("\nYou have chosen to move a card\nPlease pick a row: ");
	scanf_s("%d", &playerMove);

	tmpCurrentCard = tableRows[playerMove];


	while (state == 0) {
		printf("\nPlease pick a card\nCard Type: ");
		scanf_s("%d", &playerMove);
		printf("Card Value: ");
		scanf_s("%d", &cardInfo);

		for (int i = 0; i < 14; i++) {

			if (tmpCurrentCard == NULL) {
				break;
			}
			else if (tmpCurrentCard->cardInfo.cardType == playerMove) {
				if (tmpCurrentCard->cardInfo.cardVal == cardInfo) { // FOUND CARD MATCH

					if (tmpCurrentCard->next == NULL) {
						state = 1;
						break;

					}
					else {

						tmpInfoHolder = tmpCurrentCard;

						for (int l = 0; l < 14; l++) {

							if (tmpInfoHolder->next == NULL) {
								// SUCCES, DO NOTHING
							}
							else if (tmpInfoHolder->next->cardInfo.cardColor != tmpInfoHolder->cardInfo.cardColor) {
								if (tmpInfoHolder->next->cardInfo.cardVal == tmpInfoHolder->cardInfo.cardVal - 1) {
									// SUCCES, DO NOTHING!

								}
								else {
									break;
								}
							}
							else {
								break;
							}

							if (tmpInfoHolder->next == NULL || l == 13) { // SUCCES
								i = 14;
								state = 1;
								break;
							}

							tmpInfoHolder = tmpInfoHolder->next;
						}
					}
				}
				else {
					tmpCurrentCard = tmpCurrentCard->next;
				}
			}
			else {
				tmpCurrentCard = tmpCurrentCard->next;
			}
		}

		if (state == 1) {
			printf("\nYou have selected [Card: %d | %d]\n", tmpCurrentCard->cardInfo.cardType, tmpCurrentCard->cardInfo.cardVal);
		}
		else {
			printf("No such card found! Please try again\n");
		}
	}

	state = 0;
	while (state == 0) {
		printf("Pick which row to set card: ");
		scanf_s("%d", &playerMove);

		tmpInfoHolder = tableRows[playerMove];

		for (int i = 0; i < 14; i++) {

			if (tmpInfoHolder->next == NULL) {

				if (tmpInfoHolder->cardInfo.cardColor != tmpCurrentCard->cardInfo.cardColor && tmpInfoHolder->cardInfo.cardVal == tmpCurrentCard->cardInfo.cardVal + 1) {

					if (tmpCurrentCard->last != NULL) {
						tmpCurrentCard->last->next = NULL;
					}

					tmpInfoHolder->next = tmpCurrentCard;
					tmpCurrentCard->last = tmpInfoHolder;

					for (int k = 0; k < 7; k++) {
						if (tmpCurrentCard == tableRows[k]) {
							tableRows[k] = NULL;
						}
					}

					state = 1;
					break;
				}
				else {
					printf("Move not allowed due to mitchmatch in Card Type or Card Value!\n");
					break;
				}
			}
			tmpInfoHolder = tmpInfoHolder->next;
		}
	}
}

void moveCardTableToFoundation() {

	int playerMove = 0;
	int cardInfo = 0;
	int state = 0;
	struct Deck* tmpInfoHolder;

	printf("\nYou have chosen to move a card to Foundation\nPlease pick a row: ");
	scanf_s("%d", &playerMove);

	tmpCurrentCard = tableRows[playerMove];

	while (state == 0) {
		printf("\nPlease pick a card\nCard Type: ");
		scanf_s("%d", &playerMove);
		printf("Card Value: ");
		scanf_s("%d", &cardInfo);

		for (int i = 0; i < 14; i++) {

			if (tmpCurrentCard == NULL) {
				break;
			}
			else if (tmpCurrentCard->cardInfo.cardType == playerMove) {
				if (tmpCurrentCard->cardInfo.cardVal == cardInfo) {
					state = 1;
					break;
				}
			}
			tmpCurrentCard = tmpCurrentCard->next;
		}

		if (state == 1) {
			printf("\nYou have selected [Card: %d | %d]\n", tmpCurrentCard->cardInfo.cardType, tmpCurrentCard->cardInfo.cardVal);
		}
		else {
			printf("No such card found! Please try again\n");
		}
	}

	tmpInfoHolder = tmpCurrentCard;
	for (int i = 1; i < 5; i++) {

		if (tmpInfoHolder->cardInfo.cardType == i) {

			if (foundationCards[i] == NULL) { // IF THERE IS NO CARDS IN THE FOUNDATION

				if (tmpInfoHolder->cardInfo.cardVal == 1) {
					foundationCards[i] = tmpCurrentCard;
					if (tmpCurrentCard->last != NULL) {
						tmpCurrentCard->last->next = NULL;
					}
					tmpCurrentCard->next = NULL;

					printf("[Card %d | %d] moved from table to Foundation", tmpCurrentCard->cardInfo.cardType, tmpCurrentCard->cardInfo.cardVal);

				}
				else {
					printf("Card must be of Type %d and be Value of 2!", i);
					break;
				}

			}
			else { // IF THERE IS ALREADY CARDS IN THE FOUNDATION

				for (int k = 1; k < 15; k++) {

					if (tmpInfoHolder == NULL) {

						printf("[Card %d | %d] is not valid to move to Foundation", tmpCurrentCard->cardInfo.cardType, tmpCurrentCard->cardInfo.cardVal);
						break;

					}
					else if (tmpInfoHolder->cardInfo.cardVal == tmpCurrentCard->cardInfo.cardVal + 1) {

						printf("[Card %d | %d] moved from table to Foundation", tmpCurrentCard->cardInfo.cardType, tmpCurrentCard->cardInfo.cardVal);

						tmpInfoHolder->next = tmpCurrentCard;
						tmpCurrentCard->last->next = NULL;
						tmpCurrentCard->last = tmpInfoHolder;
						tmpCurrentCard->next = NULL;

					}

					tmpInfoHolder = tmpInfoHolder->next;

				}
			}
		}
	}
}

void moveCardDeckToTable() {

	int state = 0;
	int playerInput = 0;
	struct Deck* tmpInfoHolder;

	if (currentDeckFlopPointer != NULL) {
		printf("\nYou have chosen to move deck card to table");

		while (state == 0) {
			printf("Pick which row to set card: ");
			scanf_s("%d", &playerInput);

			tmpInfoHolder = tableRows[playerInput];

			for (int i = 0; i < 14; i++) {

				if (tmpInfoHolder->next == NULL) {

					if (tmpInfoHolder->cardInfo.cardColor != currentDeckFlopPointer->cardInfo.cardColor && tmpInfoHolder->cardInfo.cardVal == currentDeckFlopPointer->cardInfo.cardVal + 1) {

						if (currentDeckFlopPointer->last != NULL) {
							currentDeckFlopPointer->last->next = NULL;
						}

						currentDeckFlopPointer = currentDeckFlopPointer->next;

						currentDeckFlopPointer->last->last->next = currentDeckFlopPointer;
						tmpInfoHolder->next = currentDeckFlopPointer->last;
						currentDeckFlopPointer->last->next = NULL;
						tmpInfoHolder->next->last = tmpInfoHolder;
						currentDeckFlopPointer->last = currentDeckFlopPointer->last->last;

						state = 1;
						break;
					}
					else {
						printf("Move not allowed due to mitchmatch in Card Type or Card Value!\n");
						break;
					}
				}
				tmpInfoHolder = tmpInfoHolder->next;
			}
		}
	}
	else {
		printf("\nInvalid move - no card flipped from Deck\n");
	}
}

void moveCardDecktoFoundation() {

	struct Deck* tmpInfoHolder;

	if (currentDeckFlopPointer != NULL) {
		printf("\nYou have chosen to move deck card to table");

		tmpInfoHolder = currentDeckFlopPointer;

		for (int i = 1; i < 5; i++) {

			if (tmpInfoHolder->cardInfo.cardType == i) {

				if (foundationCards[i] == NULL) { // IF THERE IS NO CARDS IN THE FOUNDATION

					if (tmpInfoHolder->cardInfo.cardVal == 1) {

						foundationCards[i] = tmpInfoHolder;
						tmpInfoHolder->last->next = tmpInfoHolder->next;
						tmpInfoHolder->next->last = tmpInfoHolder->last;
						currentDeckFlopPointer = currentDeckFlopPointer->next;
						tmpInfoHolder->last = NULL;
						tmpInfoHolder->next = NULL;

						printf("[Card %d | %d] moved from Deck to Foundation", tmpInfoHolder->cardInfo.cardType, tmpInfoHolder->cardInfo.cardVal);

					}
					else {
						printf("Card must be of Type %d and be Value of 2!", i);
						break;
					}

				}
				else { // IF THERE IS ALREADY CARDS IN THE FOUNDATION

					for (int k = 1; k < 15; k++) {

						if (tmpInfoHolder == NULL) {

							printf("[Card %d | %d] is not valid to move to Foundation", currentDeckFlopPointer->cardInfo.cardType, currentDeckFlopPointer->cardInfo.cardVal);
							break;

						}
						else if (tmpInfoHolder->cardInfo.cardVal == currentDeckFlopPointer->cardInfo.cardVal + 1) {

							printf("[Card %d | %d] moved from Deck to Foundation", currentDeckFlopPointer->cardInfo.cardType, currentDeckFlopPointer->cardInfo.cardVal);

							tmpInfoHolder->next = currentDeckFlopPointer;
							currentDeckFlopPointer->last->next = NULL;
							currentDeckFlopPointer->last = tmpInfoHolder;
							currentDeckFlopPointer->next = NULL;

						}

						tmpInfoHolder = tmpInfoHolder->next;

					}
				}
			}
		}
	}
}

void flipDeckCard() {

	if (currentDeckFlopPointer == NULL) {
		currentDeckFlopPointer = topDeckPointer;
	}
	else {
		if (currentDeckFlopPointer->next != NULL) {
			currentDeckFlopPointer = currentDeckFlopPointer->next;
		}
		else {
			currentDeckFlopPointer = topDeckPointer;
		}
	}
}


// GAME PRINT FUNCTIONS
void printCurrentDeck() {

	tmpCurrentCard = topDeckPointer;

	printf("\n\n\tERRORCHECKER - Printing Deck!\n");

	while (1) {

		if (tmpCurrentCard == NULL) {
			break;
		}

		printf("\tCURRENT DECK - Placement: %d Cardtype: %d Cardvalue: %d\n", tmpCurrentCard->deckPlacement, tmpCurrentCard->cardInfo.cardType, tmpCurrentCard->cardInfo.cardVal);

		tmpCurrentCard = tmpCurrentCard->next;
	}
}

void printTable() {

	printf("\n\n");


	if (currentDeckFlopPointer != NULL) {
		printf("[ DECK ] - [Card: %d | %d]\t\t\t", currentDeckFlopPointer->cardInfo.cardType, currentDeckFlopPointer->cardInfo.cardVal);
		printf("[FOUNDATION] ");

		for (int i = 1; i < 5; i++) {
			if (foundationCards[i] == NULL) {
				printf("[NO CARD] ");
			}
			else {
				tmpCurrentCard = foundationCards[i];
				for (int k = 0; k < 14; k++) {
					if (tmpCurrentCard->next == NULL) {
						break;
					}
					tmpCurrentCard = tmpCurrentCard->next;
				}
				printf("[Card: %d | %d] ", tmpCurrentCard->cardInfo.cardType, tmpCurrentCard->cardInfo.cardVal);
			}
			if (i == 4) {
				printf("\n");
			}
		}

	}
	else {
		printf("[ DECK ] - [NO DRAW]\t\t\t\t\t");
		printf("[FOUNDATION] ");

		for (int i = 1; i < 5; i++) {
			if (foundationCards[i] == NULL) {
				printf("[NO CARD] ");
			}
			else {
				tmpCurrentCard = foundationCards[i];
				for (int k = 0; k < 14; k++) {
					if (tmpCurrentCard->next == NULL) {
						break;
					}
					tmpCurrentCard = tmpCurrentCard->next;
				}
				printf("[Card: %d | %d] ", tmpCurrentCard->cardInfo.cardType, tmpCurrentCard->cardInfo.cardVal);
			}
			if (i == 4) {
				printf("\n");
			}
		}

	}



	for (int j = 0; j < 20; j++) {

		for (int i = 1; i < 8; i++) {

			tmpCurrentCard = tableRows[i];

			if (tableRows[i] == NULL) {

			}
			else if (j > 0) {
				for (int k = 0; k < j; k++) {

					tmpCurrentCard = tmpCurrentCard->next;

					if (tmpCurrentCard == NULL) {
						break;
					}
				}
			}
			if (tmpCurrentCard != NULL) {
				printf("[Card: %d | %d]\t", tmpCurrentCard->cardInfo.cardType, tmpCurrentCard->cardInfo.cardVal);
			}
			else {
				printf("\t\t");
			}
		}
		printf("\n");
	}
}

// AI
void playCalculationAlgorithm() {

	int SKIP = 0;
	struct Deck* tmpCard;
	struct Deck* tmpInfoHolder;
	int cardFound = 0;

	STOPCOUNTER++;

	printf("Checking Cards\n");

	for (int i = 7; i > 0; i--) {

		// FIRST CHECK TO SEE IF CARD ON TABLE SHOULD BE MOVED TO FOUNDATION

		tmpCurrentCard = tableRows[i];
		tmpInfoHolder = tmpCurrentCard;

		SKIP = 0;
		if (tmpInfoHolder == NULL) {
			SKIP = 1;
		}
		else {

			for (int g = 0; g < 14; g++) {
				if (tmpInfoHolder->next == NULL) {
					// SUCCES, FOUND BOTTOM CARD OF ROW
					break;
				}
				else {
					tmpInfoHolder = tmpInfoHolder->next;
				}
			}

			tmpCurrentCard = tmpInfoHolder; // SET tmpCurrentCard TO THE BOTTOM CARD

			for (int w = 1; w < 5; w++) { // CHECK ALL FOUNDATIONS IF CARD FITS

				if (tmpCurrentCard->cardInfo.cardType == w) {

					if (foundationCards[w] == NULL) { // IF THERE IS NO CARDS IN THE FOUNDATION

						if (tmpInfoHolder->cardInfo.cardVal == 1) {
							foundationCards[w] = tmpCurrentCard;
							if (tmpCurrentCard->last != NULL) {
								tmpCurrentCard->last->next = NULL;
							}
							else { // ONLY CARD ON THE ROW
								tableRows[i] = NULL;
							}
							tmpCurrentCard->next = NULL;

							printf("\t- [Card %d | %d] moved from table to Foundation\n", tmpCurrentCard->cardInfo.cardType, tmpCurrentCard->cardInfo.cardVal);
							cardFound = 1;
							i = 8;
							w = 5;
							STOP = 0;
							break;
						}
						else {
							break;
						}

					}
					else { // IF THERE IS ALREADY CARDS IN THE FOUNDATION

						tmpInfoHolder = foundationCards[w];

						for (int q = 1; q < 15; q++) {
							if (tmpInfoHolder->next == NULL) {
								// SUCCES, FOUND BOTTOM CARD OF ROW
								break;
							}
							else {
								tmpInfoHolder = tmpInfoHolder->next;
							}
						}

						if (tmpInfoHolder->cardInfo.cardVal + 1 == tmpCurrentCard->cardInfo.cardVal) {

							printf("\t- [Card %d | %d] moved from table to Foundation\n", tmpCurrentCard->cardInfo.cardType, tmpCurrentCard->cardInfo.cardVal);

							tmpInfoHolder->next = tmpCurrentCard;
							if (tmpCurrentCard->last != NULL) {
								tmpCurrentCard->last->next = NULL;
							}
							else {
								tableRows[i] = NULL;
							}
							tmpCurrentCard->last = tmpInfoHolder;
							tmpCurrentCard->next = NULL;
							cardFound = 1;
							STOP = 0;
							w = 5;
							i = 8;
							break;

						}
						else if (tmpInfoHolder->next == NULL) {
							break;
						}
					}
				}
			}
		}


		// !!!!! FIND WHAT CARD IN THE ROW IS ELIGIBLE FOR MOVEMENT !!!!!

		if (cardFound == 0 && SKIP != 1) {

			tmpCurrentCard = tableRows[i];
			tmpInfoHolder = tableRows[i];

			if (tableRows[i]->cardInfo.cardVal == 13) {
				if (tableRows[i]->next != NULL) {
					if (tableRows[i]->next->cardInfo.cardVal == 12) {
						SKIP = 1;
						// DO NOTHING
					}
				}
			}

			if (SKIP == 1) {
				// DO NOTHING
			}
			else {

				for (int h = 0; h < 25; h++) { // HOLDS TMPCURRENTCARD

					for (int l = 0; l < 25; l++) { // HOLD TMPINFOHOLDER

						if (tmpInfoHolder == NULL) {
							break;
						}
						if (tmpInfoHolder->next == NULL) {
							// SUCCES, DO NOTHING
						}
						else if (tmpInfoHolder->next->cardInfo.cardColor != tmpInfoHolder->cardInfo.cardColor) {
							if (tmpInfoHolder->next->cardInfo.cardVal + 1 == tmpInfoHolder->cardInfo.cardVal) {
								// SUCCES, DO NOTHING!
							}
							else {
								break;
							}
						}
						else {
							break;
						}

						if (tmpInfoHolder->next == NULL) { // SUCCES
							h = 26;
							cardFound = 1;
							printf("\t- Found eligible [Card %d | %d] [Row %d]\n", tmpCurrentCard->cardInfo.cardType, tmpCurrentCard->cardInfo.cardVal, i);
							break;
						}

						tmpInfoHolder = tmpInfoHolder->next;

					}

					if (cardFound == 0) {
						tmpCurrentCard = tmpCurrentCard->next;
						tmpInfoHolder = tmpCurrentCard;
					}
				}
			}

			// !!!!! CARD FOUND - COMPARE TO ALL ROWS !!!!!
			if (cardFound == 1) {

				cardFound = 0;

				for (int m = 1; m < 8; m++) {

					tmpInfoHolder = tableRows[m];

					if (m == i) {
						// SAME ROW - SKIP
					}
					else if (tmpInfoHolder == NULL) {
						if (tmpCurrentCard->cardInfo.cardVal == 13 && lastMove != tableRows[m]) {

							for (int k = 1; k < 8; k++) {
								if (tmpCurrentCard == tableRows[k]) {
									tableRows[k] = NULL;
								}
							}

							tableRows[m] = tmpCurrentCard;

							if (tmpCurrentCard->last != NULL) {
								lastMove = tmpCurrentCard->last;
								tmpCurrentCard->last->next = NULL;
							}
							else {
								lastMove = tableRows[i];
							}

							tmpCurrentCard->last = NULL;

							printf("\t\t- Succes! [Card %d | %d] moving from Row %d to Row %d\n", tmpCurrentCard->cardInfo.cardType, tmpCurrentCard->cardInfo.cardVal, i, m);
							cardFound = 1;
							i = 8; // BREAK FOR LOOP
							STOP = 0;
							break;

						}
					}
					else {
						for (int g = 0; g < 25; g++) {
							if (tmpInfoHolder->next == NULL) {
								// SUCCES, FOUND BOTTOM CARD OF ROW
								break;
							}
							else {
								tmpInfoHolder = tmpInfoHolder->next;
							}
						}

						// COMPARE THE CARDS AGAINST EACHOTHER
						if (tmpInfoHolder->cardInfo.cardColor != tmpCurrentCard->cardInfo.cardColor) {
							if (tmpInfoHolder->cardInfo.cardVal == tmpCurrentCard->cardInfo.cardVal + 1 && lastMove != tmpInfoHolder) {

								// SUCCES! CARD FITS AND WILL NOW BE MOVED
								//printf("\t- Found eligible [Card %d | %d] [Row %d]\n", tmpCurrentCard->cardInfo.cardType, tmpCurrentCard->cardInfo.cardVal, i);

								printf("\t\t- Succes! [Card %d | %d] matches [Card %d | %d]! Moving from Row %d to Row %d\n", tmpCurrentCard->cardInfo.cardType, tmpCurrentCard->cardInfo.cardVal, tmpInfoHolder->cardInfo.cardType, tmpInfoHolder->cardInfo.cardVal, i, m);

								if (tmpCurrentCard->last != NULL) {
									lastMove = tmpCurrentCard->last;
									tmpCurrentCard->last->next = NULL;

								}

								tmpInfoHolder->next = tmpCurrentCard;
								tmpCurrentCard->last = tmpInfoHolder;

								for (int k = 1; k < 8; k++) {
									if (tmpCurrentCard == tableRows[k]) {
										tableRows[k] = NULL;
									}
								}
								cardFound = 1;
								m = 8; // BREAK FOR LOOP
								i = 8; // BREAK FOR LOOP
								STOP = 0;
								break;
							}
						}
					}
				}
				if (cardFound == 0) {
					//printf("\t\t\t- Unsuccesfull, no Card found\n");
				}
			}
		}
	}

	// !!!!! IF COMPARISON FAILS START FLIPPING THROUGH DECK !!!!!!

	if (cardFound == 0) {

		printf("\t- No table match found, flipping through deck!\n");

		if (deckEmpty == 1) {
			// DO NOTHING
		}
		else {

			for (int t = 0; t < 22; t++) {
				flipDeckCard();
				printf("\t\t- [Card %d | %d] flipped!\n", currentDeckFlopPointer->cardInfo.cardType, currentDeckFlopPointer->cardInfo.cardVal);
				// CHECK IF CARD FROM DECK SHOULD BE MOVED TO FOUNDATION

				if (currentDeckFlopPointer != NULL) {

					tmpInfoHolder = currentDeckFlopPointer;

					for (int r = 1; r < 5; r++) {

						if (tmpInfoHolder->cardInfo.cardType == r) {

							if (foundationCards[r] == NULL) { // IF THERE IS NO CARDS IN THE FOUNDATION

								if (tmpInfoHolder->cardInfo.cardVal == 1) {

									printf("\t\t- [Card %d | %d] moved from ", currentDeckFlopPointer->cardInfo.cardType, currentDeckFlopPointer->cardInfo.cardVal);

									if (currentDeckFlopPointer->next == NULL && currentDeckFlopPointer->last == NULL) {
										topDeckPointer = NULL;
										deckEmpty = 1;
										printf("last card position of Deck to Foundation\n");
									}
									else if (currentDeckFlopPointer->last != NULL && currentDeckFlopPointer->next != NULL) { // IF IN MIDDLE OF DECK
										currentDeckFlopPointer->last->next = currentDeckFlopPointer->next;
										currentDeckFlopPointer->next->last = currentDeckFlopPointer->last;
										currentDeckFlopPointer = currentDeckFlopPointer->next;
										printf("middle of Deck to Foundation\n");
									}
									else if (currentDeckFlopPointer == topDeckPointer) { // IF START OF DECK
										topDeckPointer = currentDeckFlopPointer->next;
										currentDeckFlopPointer->next->last = NULL;
										currentDeckFlopPointer = currentDeckFlopPointer->next;
										printf("front of Deck to Foundation - New topDeckPointer is [Card %d | %d]\n", topDeckPointer->cardInfo.cardType, topDeckPointer->cardInfo.cardVal);
									}
									else if (currentDeckFlopPointer->next == NULL) { // IF AT END OF DECK
										currentDeckFlopPointer->last->next = NULL;
										currentDeckFlopPointer = topDeckPointer;
										printf("back of Deck to Foundation\n");
									}



									foundationCards[r] = tmpInfoHolder;
									tmpInfoHolder->last = NULL;
									tmpInfoHolder->next = NULL;

									t = 23;
									cardFound = 1;
									STOP = 0;
									lastMove = NULL;
									break;

								}
								else {
									break;
								}

							}
							else { // IF THERE IS ALREADY CARDS IN THE FOUNDATION

								tmpInfoHolder = foundationCards[r];

								for (int k = 0; k < 14; k++) {

									if (tmpInfoHolder->cardInfo.cardVal == currentDeckFlopPointer->cardInfo.cardVal - 1) {

										tmpCard = currentDeckFlopPointer;

										printf("\t\t- [Card %d | %d] moved from ", currentDeckFlopPointer->cardInfo.cardType, currentDeckFlopPointer->cardInfo.cardVal);

										if (currentDeckFlopPointer->next == NULL && currentDeckFlopPointer->last == NULL) {
											topDeckPointer = NULL;
											deckEmpty = 1;
											printf("last card position of Deck to Foundation\n");
										}
										else if (currentDeckFlopPointer->last != NULL && currentDeckFlopPointer->next != NULL) { // IF IN MIDDLE OF DECK
											currentDeckFlopPointer->last->next = currentDeckFlopPointer->next;
											currentDeckFlopPointer->next->last = currentDeckFlopPointer->last;
											currentDeckFlopPointer = currentDeckFlopPointer->next;
											printf("middle of Deck to Foundation\n");
										}
										else if (currentDeckFlopPointer == topDeckPointer) { // IF START OF DECK
											topDeckPointer = currentDeckFlopPointer->next;
											currentDeckFlopPointer->next->last = NULL;
											currentDeckFlopPointer = currentDeckFlopPointer->next;
											printf("front of Deck to Foundation - New topDeckPointer is [Card %d | %d]\n", topDeckPointer->cardInfo.cardType, topDeckPointer->cardInfo.cardVal);
										}
										else if (currentDeckFlopPointer->next == NULL) { // IF AT END OF DECK
											currentDeckFlopPointer->last->next = NULL;
											currentDeckFlopPointer = topDeckPointer;
											printf("back of Deck to Foundation\n");
										}

										tmpInfoHolder->next = tmpCard;
										tmpCard->last = tmpInfoHolder;
										tmpCard->next = NULL;

										cardFound = 1;
										t = 23;
										r = 5;
										STOP = 0;
										lastMove = NULL;
										break;

									}
									else if (tmpInfoHolder->next == NULL) {
										break;
									}

									tmpInfoHolder = tmpInfoHolder->next;

								}
							}
						}
					}
				}

				// COMPARE THE CARDS AGAINST EACHOTHER
				if (cardFound == 0) {
					for (int m = 1; m < 8; m++) {

						tmpInfoHolder = tableRows[m];

						if (tmpInfoHolder == NULL) {

							if (currentDeckFlopPointer->cardInfo.cardVal == 13) {

								tmpCard = currentDeckFlopPointer;

								printf("\t\t- [Card %d | %d] moved from ", currentDeckFlopPointer->cardInfo.cardType, currentDeckFlopPointer->cardInfo.cardVal);

								if (currentDeckFlopPointer->next == NULL && currentDeckFlopPointer->last == NULL) {
									topDeckPointer = NULL;
									deckEmpty = 1;
									printf("last card position of Deck to Foundation\n");
								}
								else if (currentDeckFlopPointer->last != NULL && currentDeckFlopPointer->next != NULL) { // IF IN MIDDLE OF DECK
									currentDeckFlopPointer->last->next = currentDeckFlopPointer->next;
									currentDeckFlopPointer->next->last = currentDeckFlopPointer->last;

									tableRows[m] = currentDeckFlopPointer;

									currentDeckFlopPointer = currentDeckFlopPointer->next;

									tableRows[m]->next = NULL;
									tableRows[m]->last = NULL;

									printf("middle of Deck to Table [Row %d]\n", m);
								}
								else if (currentDeckFlopPointer == topDeckPointer) { // IF START OF DECK
									topDeckPointer = currentDeckFlopPointer->next;
									currentDeckFlopPointer->next->last = NULL;

									tableRows[m] = currentDeckFlopPointer;
									currentDeckFlopPointer->last = NULL;
									currentDeckFlopPointer->next = NULL;

									printf("front of Deck to Table - New topDeckPointer is [Card %d | %d] [Row %d]\n", topDeckPointer->cardInfo.cardType, topDeckPointer->cardInfo.cardVal, m);
								}
								else if (currentDeckFlopPointer->next == NULL) { // IF AT END OF DECK
									currentDeckFlopPointer->last->next = NULL;

									tableRows[m] = currentDeckFlopPointer;
									currentDeckFlopPointer->last = NULL;
									currentDeckFlopPointer->next = NULL;

									currentDeckFlopPointer = topDeckPointer;

									printf("back of Deck to Table [Row %d]\n", m);
								}

								cardFound = 1;
								t = 23;
								STOP = 0;
								lastMove = NULL;

								break;
							}
						}
						else {
							for (int g = 0; g < 14; g++) {
								if (tmpInfoHolder->next == NULL) {
									// SUCCES, FOUND BOTTOM CARD OF ROW
									break;
								}
								else {
									tmpInfoHolder = tmpInfoHolder->next;
								}
							}

							if (tmpInfoHolder->cardInfo.cardColor != currentDeckFlopPointer->cardInfo.cardColor) {
								if (tmpInfoHolder->cardInfo.cardVal == currentDeckFlopPointer->cardInfo.cardVal + 1) {

									// SUCCES! CARD FITS AND WILL NOW BE MOVED FROM DECK TO TABLE

									tmpCard = currentDeckFlopPointer;

									printf("\t\t- [Card %d | %d] moved from ", currentDeckFlopPointer->cardInfo.cardType, currentDeckFlopPointer->cardInfo.cardVal);

									if (currentDeckFlopPointer->next == NULL && currentDeckFlopPointer->last == NULL) {
										topDeckPointer = NULL;
										deckEmpty = 1;
										printf("last card position of Deck to Foundation\n");
									}
									else if (currentDeckFlopPointer->last != NULL && currentDeckFlopPointer->next != NULL) { // IF IN MIDDLE OF DECK
										currentDeckFlopPointer->last->next = currentDeckFlopPointer->next;
										currentDeckFlopPointer->next->last = currentDeckFlopPointer->last;
										currentDeckFlopPointer = currentDeckFlopPointer->next;
										printf("middle of Deck to Table\n");
									}
									else if (currentDeckFlopPointer == topDeckPointer) { // IF START OF DECK
										topDeckPointer = currentDeckFlopPointer->next;
										currentDeckFlopPointer->next->last = NULL;
										currentDeckFlopPointer = currentDeckFlopPointer->next;
										printf("front of Deck to Table - New topDeckPointer is [Card %d | %d]\n", topDeckPointer->cardInfo.cardType, topDeckPointer->cardInfo.cardVal);
									}
									else if (currentDeckFlopPointer->next == NULL) { // IF AT END OF DECK
										currentDeckFlopPointer->last->next = NULL;
										currentDeckFlopPointer = topDeckPointer;
										printf("back of Deck to Table\n");
									}

									tmpInfoHolder->next = tmpCard;
									tmpCard->last = tmpInfoHolder;
									tmpCard->next = NULL;

									cardFound = 1;
									t = 23;
									STOP = 0;
									lastMove = NULL;

									break;
								}
							}
						}
					}
				}
				if (currentDeckFlopPointer->next == NULL) {
					break;
				}
			}

		}
	}

	if (cardFound == 0) {
		printf("No match found!\n");
		STOP++;
		lastMove = NULL;
		printf("STOP: %d\n", STOP);
	}

	if (printCounter == 5) {
		printTable();
		printCurrentDeck();
		printCounter = 0;
	}
	else {
		printCounter++;
	}

	if (STOP > 5 || STOPCOUNTER > 300) {

		checkCounter = 0;

		printCurrentDeck();
		printTable();

		for (int i = 1; i < 5; i++) {

			tmpInfoHolder = foundationCards[i];

			if (tmpInfoHolder != NULL) {

				for (int q = 1; q < 15; q++) {
					if (tmpInfoHolder->next == NULL) {
						// SUCCES, FOUND BOTTOM CARD OF ROW
						break;
					}
					else {
						tmpInfoHolder = tmpInfoHolder->next;
					}
				}

				printf("\n\t - Checking Foundation[%d] with [Card: %d | %d]", i, tmpInfoHolder->cardInfo.cardType, tmpInfoHolder->cardInfo.cardVal);

				if (tmpInfoHolder->cardInfo.cardVal != 13) {
					printf("- FAIL");
					checkCounter = 0;
					break;
				}
				else {
					printf("- SUCCES");
					checkCounter++;
				}
			}
		}

		for (int i = 1; i < 8; i++) {
			tableRows[i] = NULL;

			if (i < 5) {
				foundationCards[i] = NULL;
			}
		}


		if (checkCounter == 4) {
			winValue++;
		}
		else {
			loseValue++;
		}

		baseGameState = 1;
		STOP = 0;
		STOPCOUNTER = 0;
		currentDeckFlopPointer = NULL;
		topDeckPointer = NULL;
		lastMove = NULL;
		deckEmpty = 0;

		printf("\n\n\t\t [Win: %d | Lose: %d]", winValue, loseValue);

		if (winValue + loseValue == 100) {
			baseGameState = 3;
		}

		//scanf_s("%d", &STOP);
	}

}
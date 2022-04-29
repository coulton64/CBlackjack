// CardGame.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

std::vector<std::string> cardGen(std::vector<std::string> cardT, std::vector<std::string> cardS) {
    int t = rand() % 13;
    int s = rand() % 4;
    return { cardT[t], cardS[s] };
}

int determineHandValue(std::vector<std::vector<std::string>> inputHand) {
    int outputValue = 0;
    for (int d = 0; d < inputHand.size(); d++) {
        std::string a = inputHand[d][0];
        if (a == "King" || a == "Queen" || a == "Jack") {
            outputValue = outputValue + 10;
        }
        else if (stoi(a) == 0) {
            outputValue = outputValue + 1;
        }
        else {
            outputValue = outputValue + stoi(a);
        }
    }
    return outputValue;
}

void printHeldCards(std::vector<std::vector<std::string>> vector, std::string type) {
    if (type == "Dealer") {
        std::cout << "\nDealer's Hand:\n";
    }
    else if (type == "Player") {
        std::cout << "\nCurrent Hand:\n";
    }
    for (int l = 0; l < vector.size(); l++) {
        std::cout << "Card " << l + 1 << ": " << vector[l][0] << " of " << vector[l][1] << "\n";
    }
    int totalCount = 0;
    int totalCountAlt = 0;
    for (int h = 0; h < vector.size(); h++) {
        std::string a = vector[h][0];
        if (a == "King" || a == "Queen" || a == "Jack") {
            totalCount = totalCount + 10; totalCountAlt = totalCountAlt + 10;
        }
        else if (stoi(a) == 0) {
            totalCount = totalCount + 1; totalCountAlt = totalCountAlt + 11;
        }
        else {
            totalCount = totalCount + stoi(a); totalCountAlt = totalCountAlt + stoi(a);
        }
    }
    if (totalCount > 21) {
        std::cout << "\nTotal value (Ace = 1): ";
        std::cout << totalCount << "\n";
    }
    else {
        std::cout << "Total value (Ace = 1): ";
        std::cout << totalCount << "\n";
    }
    if (totalCountAlt > 21) {
        std::cout << "Total value (Ace = 11): ";
        std::cout << totalCountAlt << " Bust!\n";
    }
    else {
        std::cout << "Total value (Ace = 11): ";
        std::cout << totalCountAlt << "\n";
    }

}

std::vector<std::string> pickCard(std::vector<std::vector<std::string>> deckInput, int deckCount) {
    return { deckInput[deckCount][0], deckInput[deckCount][1] };
}

int main() {
    std::string cls = "\n\n\n\n";
    std::string p; // Play Again choice
    srand(time(NULL));
    std::vector<std::vector<std::string>> deck;
    std::vector<std::vector<std::string>> heldCards;
    std::vector<std::vector<std::string>> heldCardsDealer;
    std::vector<std::string> cS = { "Diamonds", "Hearts", "Clubs", "Spades" };
    std::vector<std::string> cT = { "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King" };
    int deckCount = 0;
    int c = 0;
    int z = 0;
    int y = 0;
    int gameStatus = 0; // 0 = still going, 1 = Dealer is finished, 
    int playAgain = 1;
    int win = 0;
    for (; playAgain == 1;) {
        // Clear values for new play session
        deck.clear();
        heldCards.clear();
        heldCardsDealer.clear();
        gameStatus = 0;
        deckCount = 0;
        c = 0; z = 0; y = 0; p = ""; win = 0;

        // Generate deck
        for (; deck.size() < 52;) {
            std::vector<std::string> chosenCard = { cardGen(cT, cS) };
            int count = std::count(deck.begin(), deck.end(), chosenCard);
            if (count > 0) {
                chosenCard.clear(); //std::cout << "Fail\n";

            }
            else {
                deck.push_back(chosenCard);
                chosenCard.clear(); //std::cout << "Success\n";
            }
        }

        for (; z < 2; z++) {
            heldCards.push_back(pickCard(deck, deckCount));
            deckCount++;
        } // Generate first two cards for the player

        for (; y < 2; y++) {
            heldCardsDealer.push_back(pickCard(deck, deckCount));
            deckCount++;
        } // Generate the Dealer's cards

        for (; win == 0;) {
            printHeldCards(heldCards, "Player");
            printHeldCards(heldCardsDealer, "Dealer");
            std::cout << "\nWhat would you like to do?\n1. Hit  2. Stand\n";
            std::cin >> c;
            if (c == 1) { // HIT
                heldCards.push_back(pickCard(deck, deckCount));
                deckCount++;
                if (determineHandValue(heldCards) >= 21) {
                    gameStatus = 1;
                }
            }
            else if (c == 2) { // STAND
                if (21 >= determineHandValue(heldCards) > determineHandValue(heldCardsDealer) || determineHandValue(heldCardsDealer) < 17) {
                    heldCardsDealer.push_back(pickCard(deck, deckCount));
                    deckCount++;
                }
                else if (determineHandValue(heldCardsDealer) >= 17) { // based off official Blackjack rules
                    gameStatus = 1;
                }
            }
            else {
                std::cout << "Invalid input!\n";
                return 0;
            }
            std::cout << cls;
            if (gameStatus == 1) {
                printHeldCards(heldCards, "Player");
                printHeldCards(heldCardsDealer, "Dealer");
                if (determineHandValue(heldCards) >= 21) {
                    std::cout << cls;
                    std::cout << "Bust! The dealer wins!";
                    win++;
                    std::cout << " Play again? (y/n)"; std::cin >> p; if (p == "n") playAgain = 0;
                }
                else if (determineHandValue(heldCards) > determineHandValue(heldCardsDealer)) {
                    std::cout << "The player wins !";
                    win++;
                    std::cout << " Play again? (y/n)"; std::cin >> p; if (p == "n") playAgain = 0;
                }
                else {
                    std::cout << "The dealer wins !";
                    win++;
                    std::cout << " Play again? (y/n)"; std::cin >> p; if (p == "n") playAgain = 0;
                }
            }
        }
    }
    // debug lines
    // for (int k = 0; k != 52; k++) {
     // std::cout << deck[k][0] << deck[k][1] << "\n";
    // }
    return 0;
}
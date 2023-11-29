#include <iostream>
#include <vector>
#include <algorithm>
#include <conio.h>

using namespace std;

class Card {
public:
    int value;
    char suit;
    // 3 - ♥, 4 - ♦, 5 - ♣, 6 - ♠
    Card(int v, char s) {
        value = v;
        suit = s;
    }
};
class Deck {
private:
    vector<Card> Decks;
public:
    Deck() {
        CreateDeck();
    }
    void CreateDeck(){
        Decks.clear();
        for (int m = 3; m <= 6; m++) {
            for (int c = 2; c <= 11; c++) {
                if (c == 5) continue;
                Decks.push_back(Card(c, m));
            }
        }
    }
    void shuffle(int c = 72) {
        srand(time(NULL));
        for (int i = 0; i < c; i++) {
            random_shuffle(Decks.begin(), Decks.end());
        }
    }
    void show() {
        for (int i = 0; i < Decks.size(); i++) {
            cout << Decks[i].suit << Decks[i].value << " ";
            if (i != 0 && (i+1) % 9 == 0) cout << "\n";
        }
    }
    Card GetCard() {
        Card c = Decks.back();
        Decks.pop_back();
        return c;
    }
};
class BlackJack {
private:
    Deck deck;
    vector<Card> userCard;
    vector<Card> cpuCard;
    int bank = 0;
    int userBank = 1000;
    int cpuBank = 1000;
    int bet = 100;
public:
    BlackJack() {
        deck.shuffle();
    }
    void StartGame() {
        userCard.clear();
        cpuCard.clear();
        deck.CreateDeck();
        deck.shuffle();
        userBank -= bet;
        bank += bet;
        cpuBank -= bet;
        bank += bet;
        userCard.push_back(deck.GetCard());
        userCard.push_back(deck.GetCard());
    }
    void ShowTable() {
        cout << " \t--- BANK: " << bank << " ---\n\n";
        cout << "\nCPU Card:  " << GetCpuScore() << ": ";
        for (int i = 0; i < cpuCard.size(); i++) {
            cout << cpuCard[i].suit << cpuCard[i].value << " ";
        }
        cout << "\n" << cpuBank << " BTC";
        cout << "\n\nUser Card: " << GetUserScore() << ": ";
        for (int i = 0; i < userCard.size(); i++) {
            cout << userCard[i].suit << userCard[i].value << " ";
        }
        cout << "\n" << userBank << " BTC";
    }
    void MoreCard() {
        userCard.push_back(deck.GetCard());
    }
    void CpuCard() {
        cpuCard.push_back(deck.GetCard());
    }
    int GetUserScore() {
        int sum = 0;
        for (int i = 0; i < userCard.size(); i++) {
            sum += userCard[i].value;
        }
        return sum;
    }
    int GetCpuScore() {
        int sum = 0;
        for (int i = 0; i < cpuCard.size(); i++) {
            sum += cpuCard[i].value;
        }
        return sum;
    }

    int getUserBank() {
        return userBank;
    }
    int getCpuBank() {
        return cpuBank;
    }
    int getBank() {
        return bank;
    }
    void whoWin() {
        if (GetUserScore() <= 21 && GetUserScore() > GetCpuScore()
            && GetCpuScore() < 21) {
            userBank += bank;
            bank = 0;
        } else if (GetCpuScore() <= 21) {
            cpuBank += bank;
            bank = 0;
        } else {
            userBank += bank;
            bank = 0;
        }
    }
};
int main() {
    BlackJack bj;
    while (bj.getCpuBank() >= 100 && bj.getUserBank() >= 100) {
        bj.StartGame();
        while (true) {
            if (bj.GetUserScore() == 22) {
                break;
            }
            system("cls");
            bj.ShowTable();
            cout << "\n\n\tSelect: 1 - More card, 2 - Pass ";
            int step;
            cin >> step;
            if (step == 1) {
                bj.MoreCard();
                if (bj.GetUserScore() >= 21) {
                    break;
                }
            } else if (step == 2) {
                while (bj.GetCpuScore() < 18) {
                    bj.CpuCard();
                }
                break;
            }
        }
        bj.whoWin();
        system("cls");
        bj.ShowTable();
        cout << "\n\nPress any key to continue...";
        _getch();
    }
}
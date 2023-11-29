#include <iostream>
#include <vector>
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
    Deck(){
        for (int m = 3; m <= 6; m++) {
            for (int c = 2; c <= 11; c++) {
                if (c == 5) continue;
                Decks.push_back(Card(c, m));
            }
        }
    }
    void shuffle(int c = 72) {

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
public:
    BlackJack() {
        deck.shuffle();
    }
    void StartGame() {
        userCard.push_back(deck.GetCard());
        userCard.push_back(deck.GetCard());
    }
    void ShowTable() {
        cout << "\nCPU Card:  " << GetCpuScore() << ": ";
        for (int i = 0; i < cpuCard.size(); i++) {
            cout << cpuCard[i].suit << cpuCard[i].value << " ";
        }
        cout << "\n\nUser Card: " << GetUserScore() << ": ";
        for (int i = 0; i < userCard.size(); i++) {
            cout << userCard[i].suit << userCard[i].value << " ";
        }
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

};
int main() {
    BlackJack bj;
    bj.StartGame();
    while (true) {
        system("cls");
        bj.ShowTable();
        cout << "\n\n\tSelect: 1 - More card, 2 - Pass ";
        int step;
        cin >> step;
        if (step == 1) {
            bj.MoreCard();
        } else if (step == 2) {
            bj.CpuCard();
        }
    }
}
/* Copyright 350 Timothy Gedney Project 1
*/

#include <vector>
#include <iostream>
using namespace std;

vector<char> list = {'A', '1', 'B', '2', 'C', '3', 'D', '4', 'E', '5', 'F', '6', 'G', '7', 'H', '8', 'I', '9'};
int stepCount = 1; int p1 = 0; int p2 = 1; int p3 = 2;
vector<char> peg1, peg2, peg3;

void stepPrint(char disk, int first, int second) {
	cout << "Step " << stepCount << ": Move disk " << disk << " from peg " << first << " to peg " << second << "." << endl;
    cout << " 0:";
    for (size_t i = 0; i < peg1.size(); i++) {
		cout << peg1[i];
    }
    cout << endl << " 1:";
    for (size_t i = 0; i < peg2.size(); i++) {
		cout << peg2[i];
	}
    cout << endl << " 2:";
    for (size_t i = 0; i < peg3.size(); i++) {
		cout << peg3[i];
    }
    cout << endl;
    stepCount++;
}

void flip() {
    int temp = p1;
    p1 = p2;
    p2 = temp;
}

void moveStackOfPairs(int n, vector<char> &peg1, vector<char> &peg2, vector<char> &peg3) {
	char move;
    if (n < 2) {
        move = peg1.back(); //move from 0 to 2
        peg1.pop_back();
        peg3.push_back(move);
		stepPrint(move, p1, p3);
        move = peg1.back();  //move from 0 to 1
        peg1.pop_back();
        peg2.push_back(move);
        stepPrint(move, p1, p2);
        move = peg3.back();  //move from 2 to 1
        peg3.pop_back();
        peg2.push_back(move);
        stepPrint(move, p3, p2);
    } else {
        moveStackOfPairs(n-1, peg1, peg2, peg3);
        for (int i = 0; i < 2; i++) {
			move = peg1.back(); //move from 0 to 2
            peg1.pop_back();
            peg3.push_back(move);
            stepPrint(move, p1, p3);
        }
        flip();
        moveStackOfPairs(n-1, peg2, peg1, peg3);
        flip();
        for (int i = 0; i < 2; i++) {
            move = peg3.back(); //move from 2 to 1
            peg3.pop_back();
            peg2.push_back(move);
            stepPrint(move, p3, p2);
        }
        moveStackOfPairs(n-1, peg1, peg2, peg3);
	}
}

void solveHuger(int n, vector<char> &peg1, vector<char> &peg2, vector<char> &peg3) {
	char move;
    if (n < 2) {
		move = peg1.back(); //move from 0 to 2
		peg1.pop_back();
        peg3.push_back(move);
        stepPrint(move, p1, p3);
        move = peg1.back(); //move from 0 to 1
        peg1.pop_back();
        peg2.push_back(move);
        stepPrint(move, p1, p2);
	} else {
        moveStackOfPairs(n-1, peg1, peg2, peg3);
        for (int i = 0; i < 2; i++) {
            move = peg1.back(); //move from 0 to 2
            peg1.pop_back();
            peg3.push_back(move);
            stepPrint(move, p1, p3);
        }
        flip();
        moveStackOfPairs(n-1, peg2, peg1, peg3);
        flip();
        move = peg3.back(); //move from 2 to 1
        peg3.pop_back();
        peg2.push_back(move);
        stepPrint(move, p3, p2);
        solveHuger(n-1, peg1, peg2, peg3);
    }
}

void project() {
	int input;
    while (cin.good()) {
		cin >> input;
		int count = input*2;
		if (input <= 0) {
			exit(0);
		}
		cout << "Starting at" << endl << " 0:";
		for (int i = 0; i < count; i++) {
			peg1.push_back(list[i]);
			cout << peg1[i];
		}
		cout << endl << " 1:" << endl << " 2:" << endl;

		solveHuger(input, peg1, peg2, peg3);
		cout << "Done!" << endl;
        stepCount = 1;
        peg1.clear(); peg2.clear(); peg3.clear();
        p1 = 0; p2 = 1; p3 = 2;
    }
}

int main() {
	project();
}
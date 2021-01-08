/* Copyright 350 Timothy Gedney Project 4
*/

#include <vector>
#include <iostream>
#include <string>
using namespace std;

string word; //global variable for entered word

//method to compute shortest palindrome, builds word while going through recursions
string palindrome(int begin, int end) {
    string answer = "";
    //checks if indeces are the same, returns that letter if so
    if (begin == end) {
        return string(1, word[begin]);
    //checks if the indeces have passed each other, returns an empty value if so
    } else if (begin > end) {
        return "";
    }
    //case 1: if the letters at each index are the same, both index + 1
    if (word[begin] == word[end]) {
        answer = string(1, word[begin]) + palindrome(begin + 1, end - 1) + string(1, word[end]);
    } else {
        //case 3: insert letter in beginning, original at latter index
        answer = string(1, toupper(word[end])) + palindrome(begin, end - 1) + string(1, word[end]);
        //case 2: insert letter in the end, original at earlier index
        string temp = string(1, word[begin]) + palindrome(begin + 1, end) + string(1, toupper(word[begin]));
        //checks if case 2 is shorter than 3 and flips if so
        if (answer.size() > temp.size()) {
            answer = temp;
        }
    }
    return answer;
}

void project() {
    cin >> word;
    do {
        int size = 0;
        string answer;
        if (!cin.good() || word.size() <= 0) { //check entered value is good
            exit(0);
        } else if (word.size() > 1) {
            answer = palindrome(0, word.size() - 1); //enters recursion
        } else {
            answer = word; //base case of size == 1
        }
        cout << answer.size() << " " << answer << endl;
        cin >> word;
    } while (cin.good());
}

int main() {
    project();
}
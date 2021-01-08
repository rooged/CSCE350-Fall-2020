/* Copyright 350 Timothy Gedney Project 2
*/

#include <vector>
#include <iostream>
using namespace std;

vector<vector<int>> subset;
vector<vector<string>> subsetN;
int counter;
bool answer;

void findPair(vector<vector<int>> &subset, vector<vector<string>> &subsetN) {
    if (answer) {
        for (size_t i = 0; i < subset.size() - 1; i++) {
            for (size_t j = i + 1; j < subset.size(); j++) {
                for (size_t k = 0; k < subset[i].size(); k++) {
                    for (size_t l = 0; l < subset[j].size(); l++) {
                        if (subsetN[i][k] == subsetN[j][l]) {
                            goto next;
                        }
                    }
                }
                cout << "Team A:" << endl;
                for (size_t k = 0; k < subset[i].size(); k++) {
                    cout << " " << subsetN[i][k] << endl;
                }
                cout << "Team B:" << endl;
                for (size_t k = 0; k < subset[j].size(); k++) {
                    cout << " " << subsetN[j][k] << endl;
                }
                counter -= 2;
                if (counter > 1) {
                    cout << endl;
                }
                next:;
            }
        }
    }
}

void findSum(vector<int> &skill, vector<int> &local, vector<string> &name, vector<string> &localN, int index, int localSum, int sum) {
    if (localSum != sum) {
        for (size_t i = index; i < skill.size(); i++) {
            if (localSum + skill[i] > sum) {
                continue;
            }
            local.push_back(skill[i]);
            localN.push_back(name[i]);
            findSum(skill, local, name, localN, i + 1, localSum + skill[i], sum);
            local.pop_back();
            localN.pop_back();
        }
    } else {
        subset.push_back(local);
        subsetN.push_back(localN);
        counter++;
        if (counter % 2 == 0) {
            answer = true;
        }
        return;
    }
}

void project() {
    int count; int num; string word; int step = 0;
    cin >> count;
    do {
        vector<int> skill, local;
        vector<string> name, localN;
        int counter = 0; int sum = 0;
        answer = false;
        if (!cin.good() || count <= 0) {
            exit(0);
        } else if (step != 0) {
            cout << "------------" << endl;
        }
        for (int i = 0; i < count; i++) {
            cin >> word >> num;
            name.push_back(word);
            skill.push_back(num);
        }
        for (size_t i = 0; i < skill.size(); i++) {
            sum += skill[i];
        }
        sum /= 2;
        findSum(skill, local, name, localN, 0, 0, sum);
        findPair(subset, subsetN);
        if (!answer) {
            cout << "No solution." << endl;
        }
        step++;
        subset.clear(); subsetN.clear();
        cin >> count;
    } while (cin.good());
}

int main() {
    project();
}
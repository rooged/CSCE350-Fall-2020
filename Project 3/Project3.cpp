/* Copyright 350 Timothy Gedney Project 3
*/

#include <vector>
#include <iostream>
using namespace std;

//remove leading zeros
vector<int> removeZeros(vector<int> vect) {
    for (int i = 0; i < vect.size(); i++) {
        if (vect[0] == 0 && i != vect.size() - 1) {
            vect.erase(vect.begin());
        }
    }
    return vect;
}

//make equal
vector<int> makeEqual(vector<int> vect, int size) {
    for (int i = vect.size(); i < size; i++) {
        vect.insert(vect.begin(), 0);
    }
    return vect;
}

//brute force/pen & paper method
vector<int> bruteForce(vector<int> s1, vector<int> s2) {
    int num = 0;
    vector<vector<int>> temp;
    vector<int> a1;
    //fill 2d vector with each row of multiplication
    for (int i = s1.size() - 1; i >= 0; i--) {
        if (i != s1.size() - 1) {
            for (int j = i; j < s1.size() - 1; j++) {
                a1.push_back(0);
            }
        }
        for (int j = s1.size() - 1; j >= 0; j--) {
            num = (s1[j] * s2[i]) + num;
            a1.push_back(num % 10);
            num /= 10;
        }
        a1.push_back(num);
        temp.push_back(a1);
        a1.clear();
        num = 0;
    }
    a1.clear();

    //adds up the 2d vector into a single vector line
    for (int i = 0; i < temp[temp.size() - 1].size(); i++) {
        a1.insert(a1.begin(), 0);
        for (int j = 0; j < temp.size(); j++) {
            if (temp[j].size() > i) {
                a1[0] += temp[j][i] + num;
                num = 0;
            }
        }
        if (a1[0] >= 10) {
            num = a1[0];
            a1[0] = a1[0] % 10;
        }
        num /= 10;
    }
    return a1;
}

//sum two vectors
vector<int> sumVector(vector<int> a, vector<int> b) {
    if (a.size() < b.size()) {
        a = makeEqual(a, b.size());
    } else if (a.size() > b.size()) {
        b = makeEqual(b, a.size());
    }
    int num = 0;
    vector<int> sum;
    for (int i = a.size() - 1; i >= 0; i--) {
        sum.insert(sum.begin(), 0);
        sum[0] += a[i] + b[i] + num;
        if (sum[0] >= 10) {
            num = sum[0] / 10;
            sum[0] %= 10;
        } else {
            num = 0;
        }
    }
    if (num != 0) {
        sum.insert(sum.begin(), 0);
        sum[0] = num;
    }
    return sum;
}

//subtract two vectors
vector<int> subVector(vector<int> a, vector<int> b) {
    bool negative = false;
    if (a.size() < b.size()) {
        a = makeEqual(a, b.size());
    } else if (a.size() > b.size()) {
        b = makeEqual(b, a.size());
    }
    if (a[0] < b[0]) {
        vector<int> temp = a;
        a = b;
        b = temp;
        negative = true;
    }
    vector<int> sub;
    for (int i = a.size() - 1; i >= 0; i--) {
        sub.insert(sub.begin(), 0);
        if (a[i] < b[i]) {
            a[i] += 10;
            a[i - 1] -= 1;
        }
        sub[0] = a[i] - b[i];
    }
    return sub;
}

//increase vector by power
vector<int> powerVector(vector<int> vect, int power) {
    for (int i = 0; i < power; i++) {
        vect.push_back(0);
    }
    return vect;
}

//karatsuba method, recursive
vector<int> karatsuba(vector<int> s1, vector<int> s2) {
    //check if vectors are small enough to use other method
    if (s1.size() > 5 && s2.size() > 5) {
        //get m and split vectors into a0, a1, b0, & b1
        int m = s2.size() / 2;
        vector<int> a_0, a_1, b_0, b_1;
        for (int i = 0; i < s2.size(); i++) {
            if (i > s2.size() - m - 1) {
                a_0.push_back(s1[i]);
            } else {
                a_1.push_back(s1[i]);
            }
        }
        for (int i = 0; i < s2.size(); i++) {
            if (i > s2.size() - m - 1) {
                b_0.push_back(s2[i]);
            } else {
                b_1.push_back(s2[i]);
            }
        }

        //recursion for c2 & c0
        vector<int> c2 = karatsuba(a_1, b_1);
        vector<int> c0 = karatsuba(a_0, b_0);

        //a1+a0 & b1+b0 then make equal sizes for recursion
        vector<int> sumVecA = sumVector(a_0, a_1), sumVecB = sumVector(b_0, b_1);
        sumVecA = removeZeros(sumVecA); sumVecB = removeZeros(sumVecB);
        if (sumVecA.size() < sumVecB.size()) {
            sumVecA = makeEqual(sumVecA, sumVecB.size());
        } else if (sumVecA.size() > sumVecB.size()) {
            sumVecB = makeEqual(sumVecB, sumVecA.size());
        }

        //recursion for first part of c1, karatsuba(a1+0, b1+0)
        vector<int> sumVec = karatsuba(sumVecA, sumVecB);

        //first subtraction of c1, karatsuba(a1+0,b1+0) - c2
        vector<int> subVec = subVector(sumVec, c2);

        //last subtraction of c1, karatsuba(a1+0,b1+0) - c2 - c0
        vector<int> c1 = subVector(subVec, c0);

        //calc power for c2 * 10^(2*m)
        vector<int> powerVec1 = powerVector(c2, 2 * m);

        //calc power for c1 * 10^m
        vector<int> powerVec2 = powerVector(c1, m);

        //first addition step, 10^(2*m) * c2 + c0
        vector<int> firstAdd = sumVector(powerVec1, c0);

        //final addition step, step1 + c1 * 10^m
        vector<int> answer = sumVector(firstAdd, powerVec2);

        return answer;
    } else {
        //used when vector size is 5 or less
        return bruteForce(s1, s2);
    }
}

void project() {
    //initialize variables
    string input, input1, input2, delimiter = "*";
    vector<int> s1, s2, a1, a2;
    cin >> input;
    if (!cin.good() || input.empty()) {
        exit(0);
    }
    
    //split input into 2 then fill vectors with each
    input1 = input.substr(0, input.find(delimiter));
    input2 = input.substr(input.find(delimiter) + 1);
    for (size_t i = 0; i < input1.size(); i++) {
        s1.push_back(input1.at(i) - '0');
    }
    for (size_t i = 0; i < input2.size(); i++) {
        s2.push_back(input2.at(i) - '0');
    }

    //if either vector is only 0, skip everything & return 0 as answer
    if ((s1.size() == 1 && s1[0] == 0) || (s2.size() == 1 && s2[0] == 0)) {
        a1.push_back(0), a2.push_back(0);
    } else {
        //make equal sizes
        if (s1.size() > s2.size()) {
            s2 = makeEqual(s2, s1.size());
        } else if (s1.size() < s2.size()) {
            s1 = makeEqual(s1, s2.size());
        }

        //solve then remove leading zeros
        a1 = bruteForce(s1, s2);
        a2 = karatsuba(s1, s2);
        a1 = removeZeros(a1);
        a2 = removeZeros(a2);
    }

    //print
    cout << "** Brute Force: ";
    for (int i = 0; i < a1.size(); i++) {
        cout << a1[i];
    }
    cout << endl;
    cout << "** Karatsuba: ";
    for (int i = 0; i < a2.size(); i++) {
        cout << a2[i];
    }
    cout << endl;
}

int main() {
    project();
}
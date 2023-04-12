#pragma once
#include<iostream>
using namespace std;
class Pair {
private:
    int first;
    int second;
public:
    Pair(int first=-1, int second=-1)  {
        setfirst(first);
        setsecond(second);
    }
    void setfirst(int frst) {
        first = frst;
    }
    void setsecond(int scnd) {
        second = scnd;
    }
    int getfirst() {
        return first;
    }
    int getsecond() {
        return second;
    }
    void printPair() {
        cout << "(" << first << ", " << second << ")";
    }
    void printfirst() {
        cout << first;
    }
    void printsecond() {
        cout << second;
    }
};


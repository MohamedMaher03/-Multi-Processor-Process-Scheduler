#pragma once
#include<iostream>
using namespace std;
class Pair {
private:
    int first;
    int second;
public:
<<<<<<< HEAD
    Pair(int first=-1, int second=-1)  {
        setfirst(first);
        setsecond(second);
    }
    void setfirst(int frst) {
        first = frst;
    }
    void setsecond(int scnd) {
        second = scnd;
=======
    Pair() { first = -1; second = -1; };

    Pair(int f, int s) {
        setfirst(f);
        setsecond(s);
    }
    void setfirst(int f) {
        first = f;
    }
    void setsecond(int sec) {
        second = sec;
>>>>>>> 3dd6e1aee5255ab031441055d6a7502712be832a
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


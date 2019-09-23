#ifndef ZAJEC_H
#define ZAJEC_H
#include <iostream>  			// input/output library
using namespace std; 			// names for objects (like cout-->output, print text)
#include <fstream>


class zajec
{
public:
    string spol;
    string barva;
    int leta;
    string ime;
    bool radioaktiven_mutant_vampir;

    zajec* next;               //Pointer za naslednjega zajca
    //constructor
    zajec();
};

#endif // ZAJEC_H

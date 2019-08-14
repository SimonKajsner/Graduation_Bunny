#include <QCoreApplication>
#include <iostream>  			// input/output library
using namespace std; 			// names for objects (like cout-->output, print text)
#include <time.h>       /* time */
#include <stdlib.h>     /* srand, rand */


//dolocimo spol ustvarjenega zajca 50/50
string generatorSpola(){



    int stevilka =  rand() % 2 ; //nakljucna stevilka
    //cout << stevilka;
    string spol = (stevilka)? "moski" : "zenska";
    return spol;
}

//dolocimo ime za ustvarjenega zajca 5 imen na spol
string generatorImena(string spol){

    int stevilka =  rand() % 5 + 1 ; //nakljucna stevilka (1-5)
    string ime;
    if(spol == "moski"){
        switch(stevilka) {
            case 1:
                ime = "Darth Sidious";
            break;
            case 2:
                ime = "batman";
            break;
            case 3:
                ime = "Splinter";
            break;
            case 4:
                ime = "Matthew Pattel";
            break;
            case 5:
                ime = "Ostrzek";
            break;
            default:
                ime = "! rand za moska imena je pobezlal !";

        }
     }
     else if (spol == "zenska") {
        switch(stevilka) {
            case 1:
                ime = "Cleopatra";
            break;
            case 2:
                ime = "Alice";
            break;
            case 3:
                ime = "Lara Croft";
            break;
            case 4:
                ime = "April O'neil";
            break;
            case 5:
                ime = "Hermione Granger";
            break;
            default:
                ime = "! rand za zenska imena je pobezlal !";
            }
    }
    return ime;
}

// Dolocimo ali je zajec radioaktiven_mutant_vampir 2/98
bool rmv(){
    int stevilka =  rand() % 100 + 1 ; //nakljucna stevilka (1-100)
    if(stevilka > 3){
        return 0;
    }
    else {
        return 1;
    }

}

// dolocimo nakljucno barvo zajca (zacetni zajcki)
string randBarva(){
    int stevilka =  rand() % 4 + 1 ; //nakljucna stevilka (1-4)
    string barva;
        switch(stevilka) {
            case 1:
                barva = "rjava";
            break;
            case 2:
                barva = "crna";
            break;
            case 3:
                barva = "bela";
            break;
            case 4:
                barva = "mesano";
            break;
            default:
                barva = "! rand za nakljucno barvo je pobezlal !";
        }
    return  barva;
}

#include <QCoreApplication>
#include <iostream>  			// input/output library
using namespace std; 			// names for objects (like cout-->output, print text)
#include <time.h>       /* time */
#include <stdlib.h>     /* srand, rand */


#include "zajec.h"

/*
Write a program that creates a linked list of bunny objects.
Each bunny object must have
Sex: Male, Female (random at creation 50/50)
color: white, brown, black, spotted
age : 0-10 (years old)
Name : randomly chosen at creation from a list of bunny names.
radioactive_mutant_vampire_bunny: true/false (decided at time of bunny creation 2% chance of true)

✓   At program initialization 5 bunnies must be created and given random colors.
✓   Each turn afterwards the bunnies age 1 year.
✓   So long as there is at least one male age 2 or older, for each female bunny in the list age 2 or older;
✓   a new bunny is created each turn. (i.e. if there was 1 adult male and 3 adult female bunnies, three new bunnies would be born each turn)
✓   New bunnies born should be the same color as their mother.
✓   If a bunny becomes older than 10 years old, it dies.
✓   If a radioactive mutant vampire bunny is born then each turn it will change exactly one non radioactive bunny into a radioactive vampire bunny.
✓   (if there are two radioactive mutant vampire bunnies two bunnies will be changed each turn and so on...)
✓   Radioactive vampire bunnies are excluded from regular breeding and do not count as adult bunnies.
✓   Radioactive vampire bunnies do not die until they reach age 50.

✓   The program should print a list of all the bunnies in the colony each turn along w/ all the bunnies details, sorted by age.
✓   The program should also output each turns events such as
✓   "Bunny Thumper was born!
✓   Bunny Fufu was born!
✓   Radioactive Mutant Vampire Bunny Darth Maul was born!
✓   Bunny Julius Caesar died!
✓   The program should write all screen output to a file.
✓   When all the bunnies have died the program terminates.
✓   If the bunny population exceeds 1000 a food shortage must occur killing exactly half of the bunnies (randomly chosen)
*/






//Dekleracije funkcij
void append(zajec** head_ref, string barvaMame = "brez");
void printList(zajec* n);
void deleteNode(zajec **head_ref, int position);
int countList(zajec* n);
void printOrderedList(zajec* n);
void postarajZajce(zajec* n);
void parjenjeZajcev(zajec** head_ref, zajec* n);
void umiranjeZajcev(zajec** head_ref, zajec* n);
void okuzba(zajec* n);
void pomanjkanjeHrane(zajec **head_ref, zajec* n);

/*  #################################  MAIN  #################################  */
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // Inicializacija random semena
    srand (uint( time(nullptr) ) );

    // Inicializiramo porocilo
    std::ofstream outPorocilo;
    outPorocilo.open("../porocilo.txt",ios::out);
    outPorocilo << "Pufff.\n";
    outPorocilo.close();

    /* Ustvarimo prazen seznam */
    zajec* head = nullptr;

    // Ustvarimo 5 zacetnih zajcev
    for(int i = 0; i < 5; i++){
        append(&head);
    }
    postarajZajce(head);
    printList(head);

    int steviloZajcev = 10;
    while (steviloZajcev > 0) {

        umiranjeZajcev(&head, head);

        pomanjkanjeHrane(&head, head);

        okuzba(head);

        parjenjeZajcev(&head, head);

        postarajZajce(head);

        //printList(head);
        printOrderedList(head);
        steviloZajcev = countList(head);        //prestejemo stevilo zajcev
    }

    cout << endl << "Vsi zajci so umrli.\n";
    outPorocilo.open("../porocilo.txt",ios::out | ios::ate | ios::app);
    outPorocilo << endl << "Vsi zajci so umrli.\n";
    outPorocilo.close();

    return 0;
}


// Definicije funkcij

/* Given a reference (pointer to pointer) to the head
of a list and an int, appends a new node at the end */



#include "zajec.h"
#include <iostream>  			// input/output library
using namespace std; 			// names for objects (like cout-->output, print text)


//Dekleracija funkcij za lastnosti
string generatorSpola();
string generatorImena(string spol);
bool rmv();
string randBarva();

//Dekleracija funkcij (funkcija klice drugo funkcijo)
void append(zajec** head_ref, string barvaMame = "brez");
void deleteNode(zajec **head_ref, int position);

zajec::zajec()
{
    spol = generatorSpola();
    barva = randBarva();
    leta = 0;
    ime = generatorImena(spol);
    radioaktiven_mutant_vampir = rmv();
}



// funkcija postara zajce
void postarajZajce(zajec* n){
    while(n != nullptr){
        n->leta++;
        n = n->next;
    }
}

//Mnozenje zajcev
//Vsaka zdrava zajkla skoti zajca, ce je vsaj en zdrav samec v leglu.
//skoten zajec ima isto barvo kozuha kot mama.
void parjenjeZajcev(zajec** head_ref, zajec* n){
    //Kopija zacetka seznama
    zajec* kopijaN = n;
    int steviloSamcev = 0;
    //zanka pregleda koliko zdravih samcev je v leglu
    while(n != nullptr){
        if(n->spol == "moski" && n->radioaktiven_mutant_vampir == 0 && n->leta >= 2) {
            steviloSamcev++;
        }
        n = n->next;
    }
    // ce imamo zdravega samca, vsak zdrava zajkla skoti zajca
    if(steviloSamcev > 0) {
        while(kopijaN != nullptr){
            if(kopijaN->spol == "zenska" && kopijaN->radioaktiven_mutant_vampir == 0 && kopijaN->leta >=2 ) {
                //rojen je zajec
                string barvaMame = kopijaN->barva;
                append(head_ref, barvaMame);
            }
            kopijaN = kopijaN->next;
        }

    }

}

//Ubijanje zajcev (zdrav zajec - 10 let, mutant - 50 let)
void umiranjeZajcev(zajec** head_ref, zajec* n){

    int indeks = 0;
    //zanka gre skozi cel seznam
    while(n != nullptr){
        if (n->leta >= 10 && n->radioaktiven_mutant_vampir == 0) {

            cout << "Zajec " << n->ime << " je umrl zaradi starosti. " << endl;
            deleteNode(head_ref, indeks);
            indeks--;
            n = n->next;

        }
        else if (n->leta >= 50 && n->radioaktiven_mutant_vampir == 1) {

            cout << "Zajec " << n->ime << " je umrl zaradi starosti. " << endl;
            deleteNode(head_ref, indeks);
            indeks--;
            n = n->next;

        }
        else {
            n = n->next;
        }

        indeks++;
    }


}

//Okuzba zajcev
// vsak radioaktiven_mutant_vampir zajec okuzi enega zdrava zajca vsak krog
// mesto okuzbe je nakljucno, nato pa se premikam po linked listu, dokler nisem okuzil potrebno stevilo zajcev
void okuzba(zajec* n){

    int rmvSt = 0;          // okuzeni zajci
    int zajciSk = 0;        // vsi zajci
    zajec* kopijaN = n;     //kopija zacetnega n

    //zanka gre skozi cel seznam in presteje stevilo rmv zajcev in vseh zajcev
    while(n != nullptr){
        zajciSk++;
        if (n->radioaktiven_mutant_vampir == 1) {
            rmvSt++;
        }
        n = n->next;
    }
    n = kopijaN;
    //nakljucno stevilo od 0 - stevilo zajcev
    int randSt =  rand() % zajciSk;
    //cout << "nakjucno stevilo je bilo: " << randSt << endl;
    //se premaknemo po linked list-u za nakljucno stevilo
    for (int i = 0; i != randSt; i++ ){
        n = n->next;
    }
    //dolocimo koliko zajcev moramo okuziti
    // a) okuzimo toliko zdravih kot je ze okuzenih zajcev (velja ko je zdravih vec kot okuzenih)
    // b) ko je okuzenih zajcev vec kot bolanih, moramo okuziti se preostale zdrave zajce
    int stOkuzb = ((zajciSk - rmvSt) > rmvSt )? rmvSt: (zajciSk - rmvSt);
    while (stOkuzb > 0 ){

        if (n == nullptr){
             n = kopijaN;
        }
        else if (n->radioaktiven_mutant_vampir == 0) {
            n->radioaktiven_mutant_vampir = 1;      //okuzimo zajca
            cout << n->ime << " je okuzen. " << endl;
            stOkuzb--;                                //zmanjsamo st. potrebnih okuzb.
            n = n->next;                            //  se premaknemo naprej po linked list-u
        }
        else if (n->radioaktiven_mutant_vampir == 1) {
            n = n->next;                            //ce je zajec ze okuzen, se premaknemo po linked listu

        }
    }
}


// Ko je zajcev vec kot 1000, nakljucno umre polovica populacije
void pomanjkanjeHrane(zajec **head_ref, zajec* n){
    int stZajcev = 0;
    //prestejemo
    while(n != nullptr){
        stZajcev++;
        n = n->next;
    }
    int stOdstrel = stZajcev/2;
    if (stZajcev >= 10){

        while(stOdstrel > 0){
            int indeks = rand() % stZajcev;
            //cout << "indeks za odstrel: " << indeks << endl;
            deleteNode(head_ref, indeks);
            stOdstrel--;
            stZajcev--;
        }

    }
}


/* Given a reference (pointer to pointer) to the head
of a list and an int, appends a new node at the end */
void append(zajec** head_ref, string barvaMame ) {
    /* 1. allocate node */
    zajec* new_node = new zajec();

    zajec* last = *head_ref;     /* used in step 5*/

    /* 2. put in the data */
    //pride v upostev za otroke zajkl, ki morajo imeti enako barvo kozuha
    //
    if (barvaMame != "brez") {
        new_node->barva = barvaMame;
    }

    //Objava
    cout << "Zajec " << new_node->ime << " je skoten. " << endl;

    /* 3. This new node is going to be
    the last node, so make next of
    it as NULL*/
    new_node->next = nullptr;

    /* 4. If the Linked List is empty,
    then make the new node as head */
    if (*head_ref == nullptr)
    {
        *head_ref = new_node; // Change value to an adress of new_node
        return;
    }

    /* 5. Else traverse till the last node */
    while (last->next != nullptr)
        last = last->next;

    /* 6. Change the next of last node */
    last->next = new_node;
    return;
}



// Funkcija izpise podatke vseh zajcev
void printList(zajec* n){

    while(n != nullptr){
        cout << "Ime: " << n->ime << " " ;
        cout << "Spol: " << n->spol << " ";
        cout << "barva: " << n->barva << " ";
        cout << "starost: " << n->leta << " ";
        cout << "rmv: " << n->radioaktiven_mutant_vampir << endl;

        n = n->next;
    }
}

// This function counts nodes in linked list
// starting from the given node
int countList(zajec* n){
    int i = 0;
    while(n != nullptr){
        i++;
        n = n->next;
    }
    return i;
}


/* Given a reference (pointer to pointer) to the head of a list
   and a position, deletes the node at the given position */
void deleteNode(zajec **head_ref, int position) {
   // If linked list is empty
   if (*head_ref == nullptr)
      return;

   // Store head node
   zajec* temp = *head_ref;

    // If head needs to be removed
    if (position == 0)
    {
        *head_ref = temp->next;   // Change head
        free(temp);               // free old head
        return;
    }

    // Find previous node of the node to be deleted
    for (int i=0; temp!=nullptr && i<position-1; i++)
         temp = temp->next;

    // If position is more than number of ndoes
    if (temp == nullptr || temp->next == nullptr)
         return;

    // Node temp->next is the node to be deleted
    // Store pointer to the next of node to be deleted
    zajec *next = temp->next->next;

    // Unlink the node from linked list
    delete (temp->next);  // Free memory

    temp->next = next;  // Unlink the deleted node from list

}

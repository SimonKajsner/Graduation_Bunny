#include "zajec.h"
#include <iostream>  			// input/output library
#include <fstream>



//Dekleracija funkcij za lastnosti
string generatorSpola();
string generatorImena(string spol);
bool rmv();
string randBarva();

//Dekleracija funkcij za urejeni seznam
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

    std::ofstream outPorocilo;
    outPorocilo.open("../porocilo.txt",ios::out | ios::app);

    int indeks = 0;
    //zanka gre skozi cel seznam
    while(n != nullptr){
        if (n->leta >= 10 && n->radioaktiven_mutant_vampir == 0) {

            cout << "Zajec/kla " << n->ime << " je umrl/a zaradi starosti. " << endl;
            outPorocilo << "Zajec/kla " << n->ime << " je umrl/a zaradi starosti. " << endl;
            n = n->next;
            deleteNode(head_ref, indeks);
            indeks--;
            //n = n->next;        //debug mode error???

        }
        else if (n->leta >= 50 && n->radioaktiven_mutant_vampir == 1) {

            cout << "RMV Zajec/kla " << n->ime << " je umrl/a zaradi starosti. " << endl;
            outPorocilo << "RMV Zajec/kla " << n->ime << " je umrl/a zaradi starosti. " << endl;
            n = n->next;
            deleteNode(head_ref, indeks);
            indeks--;

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

    std::ofstream outPorocilo;
    outPorocilo.open("../porocilo.txt",ios::out | ios::app);

    int rmvSt = 0;          // okuzeni zajci
    int zajciSk = 0;        // vsi zajci
    int okuzba = 0;         // zastavica ko okuzimo zajca
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
        //izhod ko je stevilo zajcev == 0 (varnost SIGFPE)
        if (zajciSk==0) {
            return;
        }

        //dolocimo koliko zajcev moramo okuziti
        // a) okuzimo toliko zdravih kot je ze okuzenih zajcev (velja ko je zdravih vec kot okuzenih)
        // b) ko je okuzenih zajcev vec kot bolanih, moramo okuziti se preostale zdrave zajce
        int stOkuzb = ((zajciSk - rmvSt) > rmvSt )? rmvSt: (zajciSk - rmvSt);
        while (stOkuzb > 0 ){
            //usmerimo na zacetek seznama
            n = kopijaN;
            //nakljucno stevilo od 0 - stevilo zajcev
            int randSt =  rand() % zajciSk;
            //cout << "nakjucno stevilo je bilo: " << randSt << endl;
            //se premaknemo po linked list-u za nakljucno stevilo
            for (int i = 0; i != randSt; i++ ){
                n = n->next;
            }
            okuzba=0;
            while (okuzba==0) {
                if (n == nullptr){
                     n = kopijaN;
                }
                else if (n->radioaktiven_mutant_vampir == 0) {
                    n->radioaktiven_mutant_vampir = 1;      //okuzimo zajca
                    cout << n->ime << " je okuzen/a. " << endl;
                    outPorocilo << n->ime << " je okuzen/a. " << endl;
                    stOkuzb--;                                //zmanjsamo st. potrebnih okuzb.
                    n = n->next;                            //  se premaknemo naprej po linked list-u
                    okuzba = 1;
                }
                else if (n->radioaktiven_mutant_vampir == 1) {
                    n = n->next;                            //ce je zajec ze okuzen, se premaknemo po linked listu

                }
            }
        }
    }


// Ko je zajcev vec kot 1000, nakljucno umre polovica populacije
void pomanjkanjeHrane(zajec **head_ref, zajec* n){

    std::ofstream outPorocilo;
    outPorocilo.open("../porocilo.txt",ios::out | ios::app);

    int stZajcev = 0;
    //prestejemo
    while(n != nullptr){
        stZajcev++;
        n = n->next;
    }
    int stOdstrel = stZajcev/2;
    if (stZajcev >= 1000){
        cout << "Pomanjkanje hrane!!" << endl;
        outPorocilo << "Pomanjkanje hrane!!" << endl;
        while(stOdstrel > 0){
            int indeks = rand() % stZajcev;
            //cout << "indeks za odstrel: " << indeks << endl;
            deleteNode(head_ref, indeks);
            stOdstrel--;
            stZajcev--;
        }

    }
}


// (pointer to pointer) Usmerimo na zacetek seznama
// Na konec seznama dodamo nov "node"
void append(zajec** head_ref, string barvaMame ) {

    std::ofstream outPorocilo;
    outPorocilo.open("../porocilo.txt",ios::out | ios::app);

    // 1. Ustvarimo nov "node"
    zajec* new_node = new zajec();

    zajec* last = *head_ref;

    // 2. Podatki
    //pride v upostev za otroke zajkl, ki morajo imeti enako barvo kozuha
    if (barvaMame != "brez") {
        new_node->barva = barvaMame;
    }

    //Objava
    if(new_node->radioaktiven_mutant_vampir){
        cout << "RMV zajec " << new_node->ime << " je rojen/a. " << endl;
        outPorocilo << "RMV zajec " << new_node->ime << " je rojen/a. " << endl;
    }
    else {
        cout << "Zajec " << new_node->ime << " je rojen/a. " << endl;
        outPorocilo << "Zajec " << new_node->ime << " je rojen/a. " << endl;
    }


    // 3. Novi node bo zadnji v seznamu
    // Torej next pointer inicializiramo s nullptr
    new_node->next = nullptr;

    // 4. Ce je urejen seznam prazen
    // Novi vozel postane glava
    if (*head_ref == nullptr)
    {
        *head_ref = new_node; // Change value to an adress of new_node
        return;
    }

    // 5. Drugace se sprehodimo po seznamu do konca
    while (last->next != nullptr)
        last = last->next;

    // 6. Postavimo zadnji vozel, da kaze na novonastalega
    last->next = new_node;

    return;
}



// Funkcija izpise podatke vseh zajcev
void printList(zajec* n){

    std::ofstream outPorocilo;
    outPorocilo.open("../porocilo.txt",ios::out | ios::app);

    cout << endl << "################  podatki o letu: ################" << endl;
    outPorocilo << endl << "################  podatki o letu: ################" << endl;

    while(n != nullptr){

        cout << "Ime: " << n->ime << " "
            << "Spol: " << n->spol << " "
            << "Barva: " << n->barva << " "
            << "Starost: " << n->leta << " "
            << "RMV: " << n->radioaktiven_mutant_vampir << endl;

        outPorocilo << "Ime: " << n->ime << " "
            << "Spol: " << n->spol << " "
            << "Barva: " << n->barva << " "
            << "Starost: " << n->leta << " "
            << "RMV: " << n->radioaktiven_mutant_vampir << endl;

        n = n->next;
    }
    cout << "################  ############### ################" << endl << endl;;
    outPorocilo << "################  ############### ################" << endl << endl;
}
//Funkcija izpise vse zajce glede na starost
void printOrderedList(zajec* n){

    std::ofstream outPorocilo;
    outPorocilo.open("../porocilo.txt",ios::out | ios::app);

    zajec* kopijaN = n;     //kopija zacetnega n
    //izhod iz funkcije, ko ni zajcev
    if(n == nullptr){
        return;
    }
    cout << endl << "################  podatki o letu: ################" << endl;
    outPorocilo << endl << "################  podatki o letu: ################" << endl;
    for(int i = 0; i<51; i++){
        while(n != nullptr){
            if(n->leta==i){
                cout << "Ime: " << n->ime << " "
                    << "Spol: " << n->spol << " "
                    << "Barva: " << n->barva << " "
                    << "Starost: " << n->leta << " "
                    << "RMV: " << n->radioaktiven_mutant_vampir << endl;

                outPorocilo << "Ime: " << n->ime << " "
                    << "Spol: " << n->spol << " "
                    << "Barva: " << n->barva << " "
                    << "Starost: " << n->leta << " "
                    << "RMV: " << n->radioaktiven_mutant_vampir << endl;
            }
            n = n->next;
        }
        n=kopijaN;
    }

    cout << "################  ############### ################" << endl << endl;;
    outPorocilo << "################  ############### ################" << endl << endl;
}

// Prestejemo stevilo vozlov v urejenem seznamu
// zacnemo od podanega vozla naprej
int countList(zajec* n){
    int i = 0;
    while(n != nullptr){
        i++;
        n = n->next;
    }
    return i;
}


// (pointer to pointer) --> postavimo na zacetek seznama
//   Zbrisemo vozel, ki ga specificiramo z indeksom
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

    // Poiscemo predhodnji vozel od vozla ki ga bomo zbrisali
    for (int i=0; temp!=nullptr && i<position-1; i++)
         temp = temp->next;

    // Ce je pozicija vec kot je stevilo vozlov
    if (temp == nullptr || temp->next == nullptr)
         return;

    // Node temp->next is the node to be deleted
    // Store pointer to the next of node to be deleted
    zajec *next = temp->next->next;

    // Unlink the node from linked list
    delete (temp->next);  // Free memory

    temp->next = next;  // Unlink the deleted node from list

}

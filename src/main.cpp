/**
 * @copyright Azienda C++
 * @author Bonetti, Livorno, Lovato
 * @version v1.0
 * @date 6 June, 2018
 * @file main.cpp
 */

#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

#include "header.hpp"

#define DIM 16

using namespace std;

/** @briefs "Main del programma. Qui è presente la popolazione
 * dei puntatori del vari elemeni del programma e il menù
 * che permette di navigare tra le funzioni. */
int main() {
  int numDipendenti = 0, numClienti = 0, numProdotti = 0;
  int menu, menu_search;  // variabili per effettuare scelte sui menu
  bool exitmenu = false, exit_search = false;  // booleani per l'uscita dai menu

  Dipendente *d_pointer = nullptr;
  Cliente *c_pointer = nullptr;
  Prodotto *p_pointer = nullptr;

  // LETTURA FILE DIPENDENTI

  d_pointer = lettura_dipendenti(&numDipendenti);

  // LETTURA FILE CLIENTI

  c_pointer = lettura_clienti(&numClienti);

  // LETTURA FILE PRODOTTI

  p_pointer = lettura_prodotti(&numProdotti);

  cout << endl;

  do {
    cout << "Scegli una voce dal menu': " << endl;
    cout << "1. Calcola prezzo senza iva" << endl;
    cout << "2. Effettua un ordine" << endl;
    cout << "3. Ricerca filtrata" << endl;
    cout << "4. Visualizzazione" << endl;
    cout << "5. Inserimento" << endl;
    cout << "6. Info sistema" << endl;
    cout << "7. Modifica" << endl;
    cout << "8. Esci" << endl << endl;

    cin >> menu;
    cout << endl;

    switch (menu) {
      case 1:
        calcIva(numProdotti, p_pointer);
        break;
      case 2:
        if (effettuaOrdine(numClienti, numProdotti, c_pointer, p_pointer))
          venditeOggi::increaseNumber();
        break;
      case 3:
        exit_search = false;
        do {
          cout << "1. Cerca prodotto" << endl;
          cout << "2. Cerca cliente" << endl;
          cout << "3. Cerca dipendente" << endl;
          cout << "4. Esci dalla ricerca" << endl << endl;

          cin >> menu_search;
          cout << endl;

          switch (menu_search) {
            case 1:
              infoProdotto(numProdotti, p_pointer);
              break;
            case 2:
              infoCliente(numClienti, c_pointer);
              break;
            case 3:
              infoDipendente(numDipendenti, d_pointer);
              break;
            case 4:
              exit_search = true;
              break;
          }
        } while (!exit_search);
        break;
      case 4:
        exit_search = false;
        do {
          cout << "1. Visualizza tutti i prodotti" << endl;
          cout << "2. Visualizza tutti i clienti" << endl;
          cout << "3. Visualizza tutti i dipendenti" << endl;
          cout << "4. Esci dalla visualizzazione" << endl << endl;

          cin >> menu_search;
          cout << endl;

          switch (menu_search) {
            case 1:
              cout << visualizza(p_pointer, numProdotti) << endl << endl;
              break;
            case 2:
              cout << visualizza(c_pointer, numClienti) << endl << endl;
              break;
            case 3:
              cout << visualizza(d_pointer, numDipendenti) << endl << endl;
              break;
            case 4:
              exit_search = true;
              break;
          }
        } while (!exit_search);
        break;
      case 5:
        exit_search = false;
        do {
          cout << "1. Inserisci un nuovo dipendente" << endl;
          cout << "2. Inserisci un nuovo cliente" << endl;
          cout << "3. Inserisci un nuovo prodotto" << endl;
          cout << "4. Esci dall'inserimento" << endl << endl;

          cin >> menu_search;
          cout << endl;

          switch (menu_search) {
            case 1:
              d_pointer = nuovoDipendente(&numDipendenti, d_pointer);
              break;
            case 2:
              c_pointer = nuovoCliente(&numClienti, c_pointer);
              break;
            case 3:
              p_pointer = nuovoProdotto(&numProdotti, p_pointer);
              break;
            case 4:
              exit_search = true;
              break;
          }
        } while (!exit_search);
        break;
      case 6:
        cout << "Numero dipendenti: " << numDipendenti << endl
             << "Numero clienti: " << numClienti << endl
             << "Numero prodotti: " << numProdotti << endl
             << "Prodotti venduti oggi: " << venditeOggi::getNumber() << endl;
        cout << endl;
        break;
      case 7:
        exit_search = false;
        do {
          cout << "1. Modifica nominativo dipendente" << endl;
          cout << "2. Modifica indirizzo cliente" << endl;
          cout << "3. Modifica quantita' prodotto" << endl;
          cout << "4. Modifica prezzo prodotto" << endl;
          cout << "5. Esci dall'inserimento" << endl << endl;

          cin >> menu_search;
          cout << endl;

          switch (menu_search) {
            case 1:
              d_pointer =
                  modificaNominativoDipendente(numDipendenti, d_pointer);
              cout << endl;
              break;
            case 2:
              c_pointer = modificaIndirizzoCliente(numClienti, c_pointer);
              cout << endl;
              break;
            case 3:
              p_pointer = modificaQuantitaProdotto(numProdotti, p_pointer);
              cout << endl;
              break;
            case 4:
              p_pointer = modificaPrezzoProdotto(numProdotti, p_pointer);
              cout << endl;
              break;
            case 5:
              exit_search = true;
              break;
          }
        } while (!exit_search);
        break;
      case 8:
        scritturaFile(numDipendenti, numClienti, numProdotti, d_pointer,
                      c_pointer, p_pointer);
        exitmenu = true;
        delete[] d_pointer;
        delete[] c_pointer;
        delete[] p_pointer;
        break;
    }
  } while (!exitmenu);
  return 0;
}

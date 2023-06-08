/**
 * @copyright Azienda C++
 * @author Bonetti, Livorno, Lovato
 * @version v1.0
 * @date 6 June, 2018
 * @file source.cpp
 */

#include "header.hpp"

#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#define DIM 16

using namespace std;

int venditeOggi::number = 0;

// *** FUNZIONI ***

void venditeOggi::increaseNumber() { number++; }
int venditeOggi::getNumber() { return number; }

void checkExistsCP(
    string *s, int *i, int *pos,
    Prodotto *p) {  // controlla l'esistenza di un codice prodotto
  bool foundOne = false;

  do {
    for (int j = 0; j < *i; j++) {
      if (s[0].compare(p[j].getCodiceProdotto()) == 0) {
        foundOne = true;
        *pos = j;
      }
    }

    if (!foundOne) {
      cout << endl;
      cout << "Codice inserito inesistente. Reinseriscilo: " << endl;
      cin >> *s;
    }
  } while (!foundOne);
}

void checkExistsCC(string *s, int *i, int *pos,
                   Cliente *c) {  // controlla l'esistenza di un codice cliente
  bool foundOne = false;

  do {
    for (int j = 0; j < *i; j++) {
      if (s[0].compare(c[j].getCodiceCliente()) == 0) {
        foundOne = true;
        *pos = j;
      }
    }

    if (!foundOne) {
      cout << endl;
      cout << "Codice inserito inesistente. Reinseriscilo: " << endl;
      cin >> *s;
    }
  } while (!foundOne);
}

void checkExistsCD(string *s, int *i, int *pos,
                   Dipendente *d) {  // controlla l'esistenza di una matricola
  bool foundOne = false;

  do {
    for (int j = 0; j < *i; j++) {
      if (s[0].compare(d[j].getMatricola()) == 0) {
        foundOne = true;
        *pos = j;
      }
    }

    if (!foundOne) {
      cout << endl;
      cout << "Matricola inserita inesistente. Reinseriscila: " << endl;
      cin >> *s;
    }
  } while (!foundOne);
}

void infoProdotto(int i, Prodotto *p) {
  string temp_p;
  int pos;

  cout << "Inserisci il codice del prodotto da visualizzare: " << endl;
  cin >> temp_p;

  checkExistsCP(&temp_p, &i, &pos, p);

  cout << "Prodotto: " << p[pos].getCodiceProdotto() << " - "
       << p[pos].getStato() << endl
       << p[pos].getNomeProdotto() << ", " << p[pos].getMarca() << " ("
       << p[pos].getPrezzo() << " euro)" << endl
       << "Pezzi in magazzino: " << p[pos].getQuantita() << endl;

  cout << endl;
}

void infoCliente(int i, Cliente *c) {
  string temp_c;
  int pos;

  cout << "Inserisci il codice del cliente da visualizzare: " << endl;
  cin >> temp_c;

  checkExistsCC(&temp_c, &i, &pos, c);

  cout << "Cliente: " << c[pos].getCodiceCliente() << " - " << c[pos].getMail()
       << endl
       << c[pos].getNome() << " " << c[pos].getCognome() << " - "
       << c[pos].getTelefono() << endl
       << c[pos].getIndirizzo() << endl
       << "Numero ordini effettuati: " << c[pos].getNumeroOrdini() << endl;

  cout << endl;
}

void infoDipendente(int i, Dipendente *d) {
  string temp_d;
  int pos;

  cout << "Inserisci la matricola del dipendente da visualizzare: " << endl;
  cin >> temp_d;

  checkExistsCD(&temp_d, &i, &pos, d);

  cout << "Dipendente: " << d[pos].getMatricola() << " - "
       << d[pos].getTelefono() << endl
       << d[pos].getNome() << " " << d[pos].getCognome() << " - "
       << d[pos].getMail() << endl
       << "Settore: " << d[pos].getSettore() << endl
       << "Ruolo: " << d[pos].getRuolo() << endl
       << d[pos].getIndirizzo() << endl
       << "Stipendio: " << d[pos].getStipendio() << endl;

  cout << endl;
}

void calcIva(int i, Prodotto *p) {
  float iva = IVA();
  string temp_s;
  int pos;

  cout << "Inserisci il codice del prodotto da calcolare senza IVA: " << endl;
  cin >> temp_s;

  checkExistsCP(&temp_s, &i, &pos, p);

  // utilizzo auto per calcolare nel momento di compilazione il tipo
  // dell'attributo prezzo
  auto prezzo = p[pos].getPrezzo();

  // utilizzo le funzioni lambda times e divide
  auto sub = divide(times(static_cast<float>(prezzo), iva), 100.00);
  prezzo = prezzo - sub;

  cout << "Il prezzo senza iva del prodotto " << temp_s
       << " e': " << setprecision(2) << fixed << static_cast<float>(prezzo)
       << endl;
  cout << endl;
}

bool effettuaOrdine(int i, int j, Cliente *c, Prodotto *p) {
  // i -> numero clienti, j -> numero prodotti
  string temp_p;
  string temp_c;
  int pos_p, pos_c;

  cout << "Inserisci il codice prodotto da acquistare: " << endl;
  cin >> temp_p;

  checkExistsCP(&temp_p, &j, &pos_p, p);

  cout << "Inserisci il codice del cliente che ha effettuato l'ordine: "
       << endl;
  cin >> temp_c;

  checkExistsCC(&temp_c, &i, &pos_c, c);

  if (p[pos_p].getQuantita() > 0) {
    p[pos_p].setQuantita(p[pos_p].getQuantita() - 1);
    c[pos_c].setNumeroOrdini(c[pos_c].getNumeroOrdini() + 1);
    cout << "Ordine effettuato correttamente." << endl;
    cout << "Sara' spedito a: ";
    indirizzo_formattato::stampaIndirizzo(c[pos_c]);
    cout << endl;
    return true;
  } else {
    cout << "Non ci sono piu' pezzi disponibili del prodotto scelto." << endl;
    cout << "Nessun prodotto spedito in ";
    indirizzo_non_formattato::stampaIndirizzo(c[pos_c]);
  }
  cout << endl;
  return false;
}

bool CF_Corretto(string &str) {
  string CF;
  constexpr bool controllo[DIM] = {1, 1, 1, 1, 1, 1, 0, 0,
                                   1, 0, 0, 1, 0, 0, 0, 1};
  bool temp = true;

  for (int i = 0; i < 16; i++) CF[i] = (toupper(str[i]));

  for (int i = 0; i < 16; i++) {
    if (CF[i] >= 'A' && CF[i] <= 'Z' && controllo[i])
      ;
    else if (CF[i] >= '0' && CF[i] <= '9' && !controllo[i])
      ;
    else
      temp = false;
  }
  return temp;
}

string checkMatricola(string q, int i, Dipendente *d) {
  bool foundOne =
      false;  // nel caso diventi true a fine ciclo mi ripeter� il
              // controllo per essere sicuro che l'utente non abbia
              // inserito nuovamente una matricola uguale ad un altro
  string temp_q = q;

  do {
    foundOne = false;
    for (int j = 0; j < i; j++) {
      if (temp_q.compare(d[j].getMatricola()) == 0) {
        foundOne = true;
        cout << "Matricola gia' presente! Inseriscine una nuova: " << endl;
        cin >> temp_q;
      }
    }
  } while (foundOne);

  return temp_q;
}

string checkCodiceCliente(string q, int i, Cliente *c) {
  bool foundOne = false;  // nel caso diventi true a fine ciclo mi ripeter� il
                          // controllo per essere sicuro che l'utente non abbia
                          // inserito nuovamente un cc uguale ad un altro
  string temp_q = q;

  do {
    foundOne = false;
    for (int j = 0; j < i; j++) {
      if (temp_q.compare(c[j].getCodiceCliente()) == 0) {
        foundOne = true;
        cout << "Codice cliente gia' presente! Inseriscine uno nuovo: " << endl;
        cin >> temp_q;
      }
    }
  } while (foundOne);

  return temp_q;
}

string checkCodiceProdotto(string q, int i, Prodotto *p) {
  bool foundOne = false;  // nel caso diventi true a fine ciclo mi ripeter� il
                          // controllo per essere sicuro che l'utente non abbia
                          // inserito nuovamente un cp uguale ad un altro
  string temp_q = q;

  do {
    foundOne = false;
    for (int j = 0; j < i; j++) {
      if (temp_q.compare(p[j].getCodiceProdotto()) == 0) {
        foundOne = true;
        cout << "Codice prodotto gia' presente! Inseriscine uno nuovo: "
             << endl;
        cin >> temp_q;
      }
    }
  } while (foundOne);

  return temp_q;
}

Dipendente *nuovoDipendente(int *i, Dipendente *d_pointer) {
  string q;
  float stipendio;

  Dipendente *temp_pointer = d_pointer;
  d_pointer = nullptr;
  d_pointer = new (nothrow) Dipendente[*i + 1];
  if (d_pointer == nullptr) {
    cout << "Memoria non disponibile per creare " << *i + 1
         << " oggetti di tipo Dipendente." << endl;
    return temp_pointer;
  } else {
    for (int xx = 0; xx < *i; xx++) {
      d_pointer[xx].setNome(temp_pointer[xx].getNome());
      d_pointer[xx].setCognome(temp_pointer[xx].getCognome());
      d_pointer[xx].setCf(temp_pointer[xx].getCf());
      d_pointer[xx].setMail(temp_pointer[xx].getMail());
      d_pointer[xx].setTelefono(temp_pointer[xx].getTelefono());
      d_pointer[xx].setIndirizzo(temp_pointer[xx].getIndirizzo());
      d_pointer[xx].setMatricola(temp_pointer[xx].getMatricola());
      d_pointer[xx].setStipendio(temp_pointer[xx].getStipendio());
      d_pointer[xx].setRuolo(temp_pointer[xx].getRuolo());
      d_pointer[xx].setSettore(temp_pointer[xx].getSettore());
    }
    cout << "Inserisci il nome del nuovo dipendente: " << endl;
    cin >> q;
    d_pointer[*i].setNome(q);

    cout << "Inserisci il cognome del nuovo dipendente: " << endl;
    cin >> q;
    d_pointer[*i].setCognome(q);

    cout << "Inserisci il CF del nuovo dipendente: " << endl;
    cin >> q;
    q = checkCFD(q, *i, d_pointer);
    d_pointer[*i].setCf(q);

    cout << "Inserisci la mail del nuovo dipendente: " << endl;
    cin >> q;
    d_pointer[*i].setMail(q);

    cout << "Inserisci il telefono del nuovo dipendente: " << endl;
    cin >> q;
    d_pointer[*i].setTelefono(q);

    cout << "Inserisci l'indirizzo del nuovo dipendente: " << endl;
    cin.get();  // necessaria, prende il <newline> dato dall'invio del
                // precedente cin
    getline(cin, q);  // permette di prendere anche gli spazi
    d_pointer[*i].setIndirizzo(q);

    cout << "Inserisci la matricola del nuovo dipendente: " << endl;
    cin >> q;
    q = checkMatricola(q, *i, d_pointer);
    d_pointer[*i].setMatricola(q);

    cout << "Inserisci lo stipendio (float) del nuovo dipendente: " << endl;
    cin >> stipendio;
    d_pointer[*i].setStipendio(stipendio);

    cout << "Inserisci il ruolo del nuovo dipendente: " << endl;
    cin.get();  // necessaria, prende il <newline> dato dall'invio del
                // precedente cin
    getline(cin, q);  // permette di prendere anche gli spazi
    d_pointer[*i].setRuolo(q);

    cout << "Inserisci il settore del nuovo dipendente: " << endl;
    // cin.get(); //necessaria, prende il <newline> dato dall'invio del
    // precedente cin
    getline(cin, q);  // permette di prendere anche gli spazi
    d_pointer[*i].setSettore(q);

    *i = *i + 1;
    delete[] temp_pointer;
    return d_pointer;
  }
}

Cliente *nuovoCliente(int *i, Cliente *c_pointer) {
  string q;
  int numeroordini;

  Cliente *temp_pointer = c_pointer;
  c_pointer = nullptr;
  c_pointer = new (nothrow) Cliente[*i + 1];
  if (c_pointer == nullptr) {
    cout << "Memoria non disponibile per creare " << *i + 1
         << " oggetti di tipo Cliente." << endl;
    return temp_pointer;
  } else {
    for (int xx = 0; xx < *i; xx++) {
      c_pointer[xx].setNome(temp_pointer[xx].getNome());
      c_pointer[xx].setCognome(temp_pointer[xx].getCognome());
      c_pointer[xx].setCf(temp_pointer[xx].getCf());
      c_pointer[xx].setMail(temp_pointer[xx].getMail());
      c_pointer[xx].setTelefono(temp_pointer[xx].getTelefono());
      c_pointer[xx].setIndirizzo(temp_pointer[xx].getIndirizzo());
      c_pointer[xx].setCodiceCliente(temp_pointer[xx].getCodiceCliente());
      c_pointer[xx].setNumeroOrdini(temp_pointer[xx].getNumeroOrdini());
    }
    cout << "Inserisci il nome del nuovo cliente: " << endl;
    cin >> q;
    c_pointer[*i].setNome(q);

    cout << "Inserisci il cognome del nuovo cliente: " << endl;
    cin >> q;
    c_pointer[*i].setCognome(q);

    cout << "Inserisci il CF del nuovo cliente: " << endl;
    cin >> q;
    checkCFC(&q, i, c_pointer);
    c_pointer[*i].setCf(q);

    cout << "Inserisci la mail del nuovo cliente: " << endl;
    cin >> q;
    c_pointer[*i].setMail(q);

    cout << "Inserisci il telefono del nuovo cliente: " << endl;
    cin >> q;
    c_pointer[*i].setTelefono(q);

    cout << "Inserisci l'indirizzo del nuovo cliente: " << endl;
    cin.get();  // necessaria, prende il <newline> dato dall'invio del
                // precedente cin
    getline(cin, q);  // permette di prendere anche gli spazi
    c_pointer[*i].setIndirizzo(q);

    cout << "Inserisci il codice cliente del nuovo cliente: " << endl;
    cin >> q;
    q = checkCodiceCliente(q, *i, c_pointer);
    c_pointer[*i].setCodiceCliente(q);

    cout << "Inserisci il numero di ordini effettuati dal nuovo cliente: "
         << endl;
    cin >> numeroordini;
    c_pointer[*i].setNumeroOrdini(numeroordini);

    *i = *i + 1;
    delete[] temp_pointer;
    return c_pointer;
  }
}

Prodotto *nuovoProdotto(int *i, Prodotto *p_pointer) {
  string q;
  int quantita, stato;
  float prezzo;

  Prodotto *temp_pointer = p_pointer;
  p_pointer = nullptr;
  p_pointer = new (nothrow) Prodotto[*i + 1];
  if (p_pointer == nullptr) {
    cout << "Memoria non disponibile per creare " << *i + 1
         << " oggetti di tipo Prodotto." << endl;
    return temp_pointer;
  } else {
    for (int xx = 0; xx < *i; xx++) {
      p_pointer[xx].setCodiceProdotto(temp_pointer[xx].getCodiceProdotto());
      p_pointer[xx].setNomeProdotto(temp_pointer[xx].getNomeProdotto());
      p_pointer[xx].setMarca(temp_pointer[xx].getMarca());
      p_pointer[xx].setQuantita(temp_pointer[xx].getQuantita());
      p_pointer[xx].setPrezzo(temp_pointer[xx].getPrezzo());
      if (temp_pointer[xx].getStato().compare("Nuovo") == 0) {
        p_pointer[xx].setStato(static_cast<statop>(0));
      } else {
        p_pointer[xx].setStato(static_cast<statop>(1));
      }
    }
    cout << "Inserisci il codice prodotto del nuovo prodotto: " << endl;
    cin >> q;
    q = checkCodiceProdotto(q, *i, p_pointer);
    p_pointer[*i].setCodiceProdotto(q);

    cout << "Inserisci il nome del nuovo prodotto: " << endl;
    cin.get();  // necessaria, prende il <newline> dato dall'invio del
                // precedente cin
    getline(cin, q);  // permette di prendere anche gli spazi
    p_pointer[*i].setNomeProdotto(q);

    cout << "Inserisci la marca del nuovo prodotto: " << endl;
    // cin.get(); //necessaria, prende il <newline> dato dall'invio del
    // precedente cin
    getline(cin, q);  // permette di prendere anche gli spazi
    p_pointer[*i].setMarca(q);

    cout << "Inserisci il numero di pezzi del nuovo prodotto: " << endl;
    cin >> quantita;
    p_pointer[*i].setQuantita(quantita);

    cout << "Inserisci il prezzo (float) del nuovo prodotto: " << endl;
    cin >> prezzo;
    p_pointer[*i].setPrezzo(prezzo);

    cout << "Inserisci lo stato (0: Nuovo, 1: Usato) del nuovo prodotto: "
         << endl;
    cin >> stato;
    p_pointer[*i].setStato(static_cast<statop>(stato));

    *i = *i + 1;
    delete[] temp_pointer;
    return p_pointer;
  }
}

// Lettura da File
Dipendente *lettura_dipendenti(int *num) {
  Dipendente *d_pointer = nullptr;
  int numDipendenti = 0;
  string line;  // stringa utilizzata per lettura su file
  string nome, cognome, cf, mail, telefono, indirizzo, matricola, ruolo,
      settore, codicecliente;
  string codiceprodotto, nomeprodotto, marca;
  char separator;
  float stipendio;
  int i = 0;  // contatore
  string q;   // string temporanea

  ifstream di(INSTALLATION_ROOT_DIR "/data/dipendenti.txt");

  while (getline(di, q)) {
    numDipendenti++;
  }

  // ALLOCAZIONE DINAMICA
  d_pointer = new (nothrow) Dipendente[numDipendenti];
  if (d_pointer == nullptr) {
    cout << "Memoria non disponibile per creare " << numDipendenti
         << " oggetti di tipo Dipendente." << endl;
  }

  di.close();

  ifstream dip(INSTALLATION_ROOT_DIR "/data/dipendenti.txt");

  // LETTURA SU FILE
  while (getline(dip, line)) {
    stringstream linestream(line);
    getline(linestream, nome, '#');
    getline(linestream, cognome, '#');
    getline(linestream, cf, '#');
    getline(linestream, mail, '#');
    getline(linestream, telefono, '#');
    getline(linestream, indirizzo, '#');
    getline(linestream, matricola, '#');
    getline(linestream, ruolo, '#');
    linestream >> stipendio;
    linestream >> separator;  // tolgo il separatore '#'
    getline(linestream, settore, '#');

    d_pointer[i].setNome(nome);
    d_pointer[i].setCognome(cognome);

    // cf = checkCF(cf, i, d_pointer);

    d_pointer[i].setCf(cf);
    d_pointer[i].setMail(mail);
    d_pointer[i].setTelefono(telefono);
    d_pointer[i].setIndirizzo(indirizzo);
    d_pointer[i].setMatricola(matricola);
    d_pointer[i].setRuolo(ruolo);
    d_pointer[i].setStipendio(stipendio);
    d_pointer[i].setSettore(settore);

    i++;
  }

  // CHIUSURA FILE DIPENDENTI
  dip.close();

  *num = numDipendenti;
  return d_pointer;
}

// Lettura da File
Cliente *lettura_clienti(int *num) {
  Cliente *c_pointer = nullptr;
  int numClienti = 0;
  string line;  // stringa utilizzata per lettura su file
  string nome, cognome, cf, mail, telefono, indirizzo, codicecliente;
  int numeroordini;
  int i = 0;  // contatore
  string q;   // string temporanea

  ifstream cl(INSTALLATION_ROOT_DIR "/data/clienti.txt");

  while (getline(cl, q)) {
    numClienti++;
  }

  // ALLOCAZIONE DINAMICA
  c_pointer = new (nothrow) Cliente[numClienti];
  if (c_pointer == nullptr) {
    cout << "Memoria non disponibile per creare " << numClienti
         << " oggetti di tipo Cliente." << endl;
  }

  cl.close();

  ifstream cli(INSTALLATION_ROOT_DIR "/data/clienti.txt");

  // LETTURA SU FILE
  while (getline(cli, line)) {
    stringstream linestream(line);
    getline(linestream, nome, '#');
    getline(linestream, cognome, '#');
    getline(linestream, cf, '#');
    getline(linestream, mail, '#');
    getline(linestream, telefono, '#');
    getline(linestream, indirizzo, '#');
    getline(linestream, codicecliente, '#');
    linestream >> numeroordini;

    c_pointer[i].setNome(nome);
    c_pointer[i].setCognome(cognome);

    // checkCF(&cf, &i, &numDipendenti, c_pointer, d_pointer);

    c_pointer[i].setCf(cf);
    c_pointer[i].setMail(mail);
    c_pointer[i].setTelefono(telefono);
    c_pointer[i].setIndirizzo(indirizzo);
    c_pointer[i].setCodiceCliente(codicecliente);
    c_pointer[i].setNumeroOrdini(numeroordini);

    i++;
  }

  // CHIUSURA FILE CLIENTI
  cli.close();

  *num = numClienti;
  return c_pointer;
}

// Lettura da File
Prodotto *lettura_prodotti(int *num) {
  Prodotto *p_pointer = nullptr;
  int numProdotti = 0;
  string line;  // stringa utilizzata per lettura su file
  string codiceprodotto, nomeprodotto, marca;
  char separator;
  float prezzo;
  int quantita, stato;
  int i = 0;  // contatore
  string q;   // string temporanea

  ifstream pr(INSTALLATION_ROOT_DIR "/data/prodotti.txt");

  while (getline(pr, q)) {
    numProdotti++;
  }

  // ALLOCAZIONE DINAMICA
  p_pointer = new (nothrow) Prodotto[numProdotti];
  if (p_pointer == nullptr) {
    cout << "Memoria non disponibile per creare " << numProdotti
         << " oggetti di tipo Prodotto." << endl;
  }

  pr.close();

  ifstream pro(INSTALLATION_ROOT_DIR "/data/prodotti.txt");

  // LETTURA SU FILE
  while (getline(pro, line)) {
    stringstream linestream(line);
    getline(linestream, codiceprodotto, '#');
    getline(linestream, nomeprodotto, '#');
    getline(linestream, marca, '#');
    linestream >> quantita >> separator >> prezzo >> separator >>
        stato;  // quando prendo separator e' per togliere il separatore '#'

    p_pointer[i].setCodiceProdotto(codiceprodotto);
    p_pointer[i].setNomeProdotto(nomeprodotto);
    p_pointer[i].setMarca(marca);
    p_pointer[i].setQuantita(quantita);
    p_pointer[i].setPrezzo(prezzo);
    p_pointer[i].setStato(static_cast<statop>(stato));

    i++;
  }

  // CHIUSURA FILE PRODOTTI
  pro.close();

  *num = numProdotti;
  return p_pointer;
}

void scritturaFile(int i, int j, int k, Dipendente *d, Cliente *c,
                   Prodotto *p) {
  ofstream filed(INSTALLATION_ROOT_DIR "/data/dipendenti.txt");
  if (filed.is_open()) {
    for (int xx = 0; xx < i; xx++) {
      filed << d[xx].getNome() << "#";
      filed << d[xx].getCognome() << "#";
      filed << d[xx].getCf() << "#";
      filed << d[xx].getMail() << "#";
      filed << d[xx].getTelefono() << "#";
      filed << d[xx].getIndirizzo() << "#";
      filed << d[xx].getMatricola() << "#";
      filed << d[xx].getRuolo() << "#";
      filed << d[xx].getStipendio() << "#";
      filed << d[xx].getSettore() << "\n";
    }
    filed.close();
  } else
    cout << "Impossibile aprire il file dipendenti per scrivere." << endl;

  ofstream filec(INSTALLATION_ROOT_DIR "/data/clienti.txt");
  if (filec.is_open()) {
    for (int xx = 0; xx < j; xx++) {
      filec << c[xx].getNome() << "#";
      filec << c[xx].getCognome() << "#";
      filec << c[xx].getCf() << "#";
      filec << c[xx].getMail() << "#";
      filec << c[xx].getTelefono() << "#";
      filec << c[xx].getIndirizzo() << "#";
      filec << c[xx].getCodiceCliente() << "#";
      filec << c[xx].getNumeroOrdini() << "\n";
    }
    filec.close();
  } else
    cout << "Impossibile aprire il file clienti per scrivere." << endl;

  ofstream filep(INSTALLATION_ROOT_DIR "/data/prodotti.txt");
  if (filep.is_open()) {
    for (int xx = 0; xx < k; xx++) {
      filep << p[xx].getCodiceProdotto() << "#";
      filep << p[xx].getNomeProdotto() << "#";
      filep << p[xx].getMarca() << "#";
      filep << p[xx].getQuantita() << "#";
      filep << p[xx].getPrezzo() << "#";
      filep << p[xx].getStato() << "\n";
    }
    filep.close();
  } else
    cout << "Impossibile aprire il file prodotti per scrivere." << endl;
}

Dipendente *modificaNominativoDipendente(int i, Dipendente *d) {
  string q;
  bool foundOne = false;
  int pos = 0;

  cout << "Inserisci la matricola del dipendente: " << endl;
  cin >> q;

  do {
    foundOne = false;
    for (int j = 0; j < i; j++) {
      if (q.compare(d[j].getMatricola()) == 0) {
        foundOne = true;
        pos = j;
      }
    }
    if (!foundOne) {
      cout << "Matricola inesistente, reinseriscila: " << endl;
      cin >> q;
    }
  } while (!foundOne);

  cout << "Inserisci il nuovo nome: " << endl;
  cin >> q;
  d[pos].setNome(q);

  cout << "Inserisci il nuovo cognome: " << endl;
  cin >> q;
  d[pos].setCognome(q);

  return d;
}

Cliente *modificaIndirizzoCliente(int i, Cliente *c) {
  string q;
  bool foundOne = false;
  int pos = 0;

  cout << "Inserisci il codice cliente del cliente: " << endl;
  cin >> q;

  do {
    foundOne = false;
    for (int j = 0; j < i; j++) {
      if (q.compare(c[j].getCodiceCliente()) == 0) {
        foundOne = true;
        pos = j;
      }
    }
    if (!foundOne) {
      cout << "Codice cliente inesistente, reinseriscilo: " << endl;
      cin >> q;
    }
  } while (!foundOne);

  cout << "Inserisci il nuovo indirizzo: " << endl;
  cin.get();  // necessaria, prende il <newline> dato dall'invio del precedente
              // cin
  getline(cin, q);  // permette di prendere anche gli spazi
  c[pos].setIndirizzo(q);

  return c;
}

Prodotto *modificaQuantitaProdotto(int i, Prodotto *p) {
  string q;
  bool foundOne = false;
  int pos = 0;
  int x;

  cout << "Inserisci il codice prodotto del prodotto: " << endl;
  cin >> q;

  do {
    foundOne = false;
    for (int j = 0; j < i; j++) {
      if (q.compare(p[j].getCodiceProdotto()) == 0) {
        foundOne = true;
        pos = j;
      }
    }
    if (!foundOne) {
      cout << "Codice prodotto inesistente, reinseriscilo: " << endl;
      cin >> q;
    }
  } while (!foundOne);

  cout << "Inserisci la nuova quantita': " << endl;
  cin >> x;
  p[pos].setQuantita(x);

  return p;
}

Prodotto *modificaPrezzoProdotto(int i, Prodotto *p) {
  string q;
  bool foundOne = false;
  int pos = 0;
  float x;

  cout << "Inserisci il codice prodotto del prodotto: " << endl;
  cin >> q;

  do {
    foundOne = false;
    for (int j = 0; j < i; j++) {
      if (q.compare(p[j].getCodiceProdotto()) == 0) {
        foundOne = true;
        pos = j;
      }
    }
    if (!foundOne) {
      cout << "Codice prodotto inesistente, reinseriscilo: " << endl;
      cin >> q;
    }
  } while (!foundOne);

  cout << "Inserisci il nuovo prezzo (float): " << endl;
  cin >> x;
  p[pos].setPrezzo(x);

  return p;
}

// *** SVILUPPO FUNZIONI PERSONA ***

string Persona::getNominativo() {
  return "\nNome: " + getNome() + "\nCognome: " + getCognome();
}

int Persona::getLivello() { return 0; }

string Persona::getNome() { return nome; }

void Persona::setNome(string s) { nome = s; }

string Persona::getCognome() { return cognome; }

void Persona::setCognome(string s) { cognome = s; }

string Persona::getCf() { return cf; }

void Persona::setCf(string s) { cf = s; }

string Persona::getMail() { return mail; }

void Persona::setMail(string s) { mail = s; }

string Persona::getTelefono() { return telefono; }

void Persona::setTelefono(string s) { telefono = s; }

string Persona::getIndirizzo() { return indirizzo; }

void Persona::setIndirizzo(string s) { indirizzo = s; }

// *** SVILUPPO FUNZIONI DIPENDENTE ***
string checkCFD(string q, int i, Dipendente *d) {
  bool foundOne = false;  // nel caso diventi true a fine ciclo mi ripeter� il
                          // controllo per essere sicuro che l'utente non abbia
                          // inserito nuovamente un CF uguale ad un altro
  string temp_q = q;

  while (!CF_Corretto(temp_q)) {
    cout << "Codice Fiscale Errato" << endl;
    cout << "Inserire di nuovo il Codice Fiscale: " << endl;
    cin >> temp_q;
  }

  if (i == 0) {  // se i == 0 vuol dire che questa � la prima persona in
                 // assoluto che inseriamo e non ci saranno quindi cf uguali
    return temp_q;
  } else {
    do {
      foundOne = false;
      for (int j = 0; j < i; j++) {
        if (temp_q.compare(d[j].getCf()) == 0) {
          foundOne = true;
          cout << "Codice fiscale gia' presente! Inseriscine uno nuovo: "
               << endl;
          cin >> temp_q;
          while (!CF_Corretto(temp_q)) {
            cout << "Codice Fiscale Errato" << endl;
            cout << "Inserire di nuovo il Codice Fiscale: " << endl;
            cin >> temp_q;
          }
        }
      }
    } while (foundOne);
  }
  return temp_q;
}

string Dipendente::getNominativo() {
  return Persona::getNominativo() + "\nMatricola: " + getMatricola();
}

int Dipendente::getLivello() { return 2; }

string Dipendente::getMatricola() { return matricola; }

void Dipendente::setMatricola(string s) { matricola = s; }

string Dipendente::getRuolo() { return ruolo; }

void Dipendente::setRuolo(string s) { ruolo = s; }

float Dipendente::getStipendio() { return stipendio; }

void Dipendente::setStipendio(float f) { stipendio = f; }

string Dipendente::getSettore() { return settore; }

void Dipendente::setSettore(string s) { settore = s; }

//*** SVILUPPO FUNZIONI CLIENTE ***

void checkCFC(string *q, int *i, Cliente *c) {
  bool foundOne = false;  // nel caso diventi true a fine ciclo mi ripeter� il
                          // controllo per essere sicuro che l'utente non abbia
                          // inserito nuovamente un CF uguale ad un altro
  string temp_q = *q;

  while (!CF_Corretto(temp_q)) {
    cout << "Codice Fiscale Errato" << endl;
    cout << "Inserire di nuovo il Codice Fiscale: " << endl;
    cin >> temp_q;
  }

  do {
    foundOne = false;

    for (int j = 0; j < *i; j++) {
      if (temp_q.compare(c[j].getCf()) == 0) {
        foundOne = true;
        cout << "Codice fiscale gia' presente! Inseriscine uno nuovo: " << endl;
        cin >> temp_q;
        while (!CF_Corretto(temp_q)) {
          cout << "Codice Fiscale Errato" << endl;
          cout << "Inserire di nuovo il Codice Fiscale: " << endl;
          cin >> temp_q;
        }
      }
    }
  } while (foundOne == true);

  *q = temp_q;
}

namespace indirizzo_non_formattato {
void stampaIndirizzo(Cliente c) { cout << c.getIndirizzo() << "." << endl; }
}  // namespace indirizzo_non_formattato
namespace indirizzo_formattato {
void stampaIndirizzo(Cliente c) {
  cout << c.getNome() << " " << c.getCognome() << endl
       << c.getIndirizzo() << "." << endl;
}
}  // namespace indirizzo_formattato

string Cliente::getNominativo() {
  return Persona::getNominativo() + "\nCodice cliente: " + getCodiceCliente();
}

int Cliente::getLivello() { return 1; }

string Cliente::getCodiceCliente() { return codiceCliente; }

void Cliente::setCodiceCliente(string s) { codiceCliente = s; }

int Cliente::getNumeroOrdini() { return numeroOrdini; }

void Cliente::setNumeroOrdini(int i) { numeroOrdini = i; }

// *** SVILUPPO FUNZIONI PRODOTTO ***

string Prodotto::getNominativo() {
  return "\nNome Prodotto: " + getNomeProdotto() + "\nMarca: " + getMarca() +
         "\nStato: " + getStato();
}

string Prodotto::getCodiceProdotto() { return codiceProdotto; }

void Prodotto::setCodiceProdotto(string s) { codiceProdotto = s; }

string Prodotto::getNomeProdotto() { return nomeProdotto; }

void Prodotto::setNomeProdotto(string s) { nomeProdotto = s; }

string Prodotto::getMarca() { return marca; }

void Prodotto::setMarca(string s) { marca = s; }

int Prodotto::getQuantita() { return quantita; }

void Prodotto::setQuantita(int i) { quantita = i; }

float Prodotto::getPrezzo() { return prezzo; }

void Prodotto::setPrezzo(float f) { prezzo = f; }

string Prodotto::getStato() {
  if (stato == 0) {
    return "Nuovo";
  } else {
    return "Usato";
  }
}

void Prodotto::setStato(statop s) { stato = s; }

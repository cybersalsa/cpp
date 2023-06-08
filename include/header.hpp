/**
 * @copyright Azienda C++
 * @author Bonetti, Livorno, Lovato
 * @version v1.0
 * @date 6 June, 2018
 * @file header.hpp
 */

#ifndef HEADER
#define HEADER

#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

/** @brief "Il tipo statop è un enum che definisce
 * il tipo di un oggetto in vendita.
 * Nuovo = 0, Usato = 1" */
enum statop { Nuovo, Usato };

using namespace std;

/** @brief "La classe Persona non viene mai direttamente
 * utlizzata dal programma. Fornisce da base
 * per le altre classi necessarie e i suoi attributi
 * descrivono le caratteristiche di una persona." */
class Persona {
  string nome;       ///< Nome di una persona
  string cognome;    ///< Cognome di una persona
  string cf;         ///< Codice fiscale di una persona
  string mail;       ///< Mail di una persona
  string telefono;   ///< Numero di telefono di una persona
  string indirizzo;  ///< Indirizzo di casa di una persona

 public:
  ///@brief Crea un elemento di classe Persona
  Persona(string s1, string s2, string s3, string s4, string s5, string s6)
      : nome(s1), cognome(s2), cf(s3), mail(s4), telefono(s5), indirizzo(s6) {}

  Persona() = default;

  ///@brief Distrugge un elemento di classe Persona
  ~Persona() {}

  ///@brief Restituisce l'attributo nome
  string getNome();
  ///@brief Setta l'attributo nome
  void setNome(string s);

  ///@brief Restituisce l'attributo cognome
  string getCognome();
  ///@brief Setta l'attributo cognome
  void setCognome(string s);

  ///@brief Restituisce l'attributo codice fiscale
  string getCf();
  ///@brief Setta l'attributo codice fiscale
  void setCf(string s);

  ///@brief Restituisce l'attributo mail
  string getMail();
  ///@brief Setta l'attributo mail
  void setMail(string s);

  ///@brief Restituisce l'attributo telefono
  string getTelefono();
  ///@brief Setta l'attributo telefono
  void setTelefono(string s);

  ///@brief Restituisce l'attrivuto indirizzo
  string getIndirizzo();
  ///@brief Setta l'attributo indirizzo
  void setIndirizzo(string s);

  ///@brief Restituisce il nominativo completo di una persona
  virtual string getNominativo();
  ///@brief Restituisce il livello di accesso al sistema di una persona
  virtual int getLivello();
};

/** @brief "La classe Dipendente deriva dalla classe
 * Persona e descrive un dipendente che
 * lavora per l'azienda." */
class Dipendente : public Persona {
  string matricola;  ///< Matricola di un dipendente
  string ruolo;      ///< Ruolo di un dipendente
  float stipendio;   ///< Stipendio di un dipendente
  string settore;    ///< Settore in cui lavora un dipendente

 public:
  ///@brief Crea un elemento di classe Dipendente
  Dipendente(string s1, string s2, string s3, string s4, string s5, string s6,
             string s7, string s8, float f1, string s9)
      : Persona(s1, s2, s3, s4, s5, s6),
        matricola(s7),
        ruolo(s8),
        stipendio(f1),
        settore(s9) {}

  Dipendente() = default;

  ///@brief Distrugge un elemento di classe Dipendente
  ~Dipendente() {}

  ///@brief Restituisce l'attributo matricola
  string getMatricola();
  ///@brief Setta l'attributo matricola
  void setMatricola(string s);

  ///@brief Restituisce l'attributo ruolo
  string getRuolo();
  ///@brief Setta l'attributo ruolo
  void setRuolo(string s);

  ///@brief Restituisce l'attributo stipendio
  float getStipendio();
  ///@brief Setta l'attributo stipendio
  void setStipendio(float f);

  ///@brief Restituisce l'attributo settore
  string getSettore();
  ///@brief Setta l'attributo settore
  void setSettore(string s);

  ///@brief Restituisce il nominativo completo di un dipendente
  string getNominativo() override;
  ///@brief Restituisce il livello di accesso al sistema di un dipendente
  int getLivello() override;
};

/** @brief "La classe Cliente deriva dalla classe
 * Persona e descrive un cliente che
 * acquista presso l'azienda" */
class Cliente : public Persona {
  string codiceCliente;  ///< Codice cliente di un cliente
  int numeroOrdini;      ///< Numero ordini totali di un cliente

 public:
  ///@brief Crea un elemento di classe Cliente
  Cliente(string s1, string s2, string s3, string s4, string s5, string s6,
          string s7, int i1)
      : Persona(s1, s2, s3, s4, s5, s6), codiceCliente(s7), numeroOrdini(i1) {}

  Cliente() = default;

  ///@brief Distrugge un elemento di classe Cliente
  ~Cliente() {}

  ///@brief Restituisce l'attributo codice cliente
  string getCodiceCliente();
  ///@brief Setta l'attributo codice cliente
  void setCodiceCliente(string s);

  ///@brief Restituisce l'attributo numero ordini
  int getNumeroOrdini();
  ///@brief Setta l'attributo numero ordini
  void setNumeroOrdini(int i);

  ///@brief Restituisce il nominativo completo di un cliente
  string getNominativo() override;
  ///@brief Restituisce il livello di accesso al sistema di un cliente
  int getLivello() override;
};

/** @brief "Questa classe e i suoi attributi descrivono
 * un prodotto venduto dall'azienda." */
class Prodotto {
  string codiceProdotto;  ///< Codice prodotto del prodotto
  string nomeProdotto;    ///< Nome prodotto del prodotto
  string marca;           ///< Marca del prodotto
  int quantita;           ///< Pezzi in magazzino del prodotto
  float prezzo;           ///< Prezzo del prodotto
  statop stato;           ///< Stato del prodotto

 public:
  ///@brief Crea un elemento di classe Prodotto
  Prodotto(string s1, string s2, string s3, int i1, float f1, statop s4)
      : codiceProdotto(s1),
        nomeProdotto(s2),
        marca(s3),
        quantita(i1),
        prezzo(f1),
        stato(s4) {}

  Prodotto() = default;

  ///@brief Distrugge un elemento di classe Prodotto
  ~Prodotto() {}

  ///@brief Restituisce l'attributo codice prodotto
  string getCodiceProdotto();
  ///@brief Setta l'attributo codice prodotto
  void setCodiceProdotto(string s);

  ///@brief Restituisce l'attributo nome prodotto
  string getNomeProdotto();
  ///@brief Setta l'attributo nome prodotto
  void setNomeProdotto(string s);

  ///@brief Restituisce l'attributo marca
  string getMarca();
  ///@brief Setta l'attributo marca
  void setMarca(string s);

  ///@brief Restituisce l'attributo quantità
  int getQuantita();
  ///@brief Setta l'attributo quantità
  void setQuantita(int i);

  ///@brief Restituisce l'attributo prezzo
  float getPrezzo();
  ///@brief Setta l'attributo prezzo
  void setPrezzo(float f);

  ///@brief Restituisce l'attributo stato
  string getStato();
  ///@brief Setta l'attributo stato
  void setStato(statop s);

  ///@brief Restituisce il nominativo completo di un prodotto
  string getNominativo();
};

/** @brief "Classe statica che mantiene il numero di ordini
 * effettuati in una singola esecuzione del programma" */
class venditeOggi {
 private:
  static int number;  ///< numero delle vendite di oggi

 public:
  ///@brief Aumenta l'attributo number
  static void increaseNumber();
  ///@brief Restituisce l'attributo number
  static int getNumber();
};

/** @brief "Namespace che contiene una funzione per
 * stampare l'indirizzo non formattato di un
 * cliente." */
namespace indirizzo_non_formattato {
///@brief Stampa l'indirizzo di un cliente
void stampaIndirizzo(Cliente c);
}  // namespace indirizzo_non_formattato

/** @brief "Namespace che contiene una funzione per
 * stampare l'indirizzo formattato di un
 * cliente." */
namespace indirizzo_formattato {
///@brief Stampa l'indirizzo di un cliente
void stampaIndirizzo(Cliente c);
}  // namespace indirizzo_formattato

/** @brief "Questa funzione template può ricevere in input
 * un elemento di classe Cliente, Dipendente o Prodotto
 * e ne restituisce una breve descrizione"
 * @param[in] *a Puntatore alla lista in cui si trova l'elemento da analizzare
 * (X = Dipendente || Cliente || Prodotto)
 * @param[in] i Numero di elementi presenti nella lista (int)
 * @return Breve descrizione dell'elemento passato (string) */
template <typename X>
string visualizza(X *a, int i) {
  string lista;
  for (int j = 0; j < i; j++) {
    if (is_same<X, Cliente>::value)
      lista +=
          "Cliente n." + to_string(j + 1) + ": " + a[j].getNominativo() + "\n";
    else {
      // controllo se di tipo dipendente
      if (is_same<X, Dipendente>::value)
        lista += "Dipendente n." + to_string(j + 1) + ": " +
                 a[j].getNominativo() + "\n";
      // altrimenti -> prodotto
      else
        lista += "Prodotto n." + to_string(j + 1) + ": " +
                 a[j].getNominativo() + "\n";
    }
  }
  return lista;
}

/** @brief Controlla che il codice prodotto inserito esista
 * @param[out] *s Puntatore al codice prodotto (string)
 * @param[in] *i Puntatore al numero di prodotti presenti nel sistema (int)
 * @param[out] *pos Puntatore alla posizione in cui si trova il codice prodotto
 * (int)
 * @param[in] *p Puntatore ai prodotti (Prodotto) */
void checkExistsCP(string *s, int *i, int *pos, Prodotto *p);

/** @brief Controlla che il codice cliente inserito esista
 * @param[out] *s Puntatore al codice cliente (string)
 * @param[in] *i Puntatore al numero di clienti presenti nel sistema (int)
 * @param[out] *pos Puntatore alla posizione in cui si trova il codice cliente
 * (int)
 * @param[in] *c Puntatore ai clienti (Cliente) */
void checkExistsCC(string *s, int *i, int *pos, Cliente *c);

/** @brief Controlla che la matricola inserita esista
 * @param[out] *s Puntatore alla matricola (string)
 * @param[in] *i Puntatore al numero di dipendenti presenti nel sistema (int)
 * @param[out] *pos Puntatore alla posizione in cui si trova la matricola (int)
 * @param[in] *d Puntatore ai dipendenti (Dipendente) */
void checkExistsCD(string *s, int *i, int *pos, Dipendente *d);

// void checkCF(string *q, int *i, int *num_d, Cliente *c, Dipendente *d);

/** @brief Stampa a schermo le info di un prodotto
 * @param[in] i Numero di prodotti nel sistema (int)
 * @param[in] *p Puntatore ai prodotti (Prodotto) */
void infoProdotto(int i, Prodotto *p);

/** @brief Stampa a schermo le info di un cliente
 * @param[in] i Numero di clienti nel sistema (int)
 * @param[in] *c Puntatore ai clienti (Cliente) */
void infoCliente(int i, Cliente *c);

/** @brief Stampa a schermo le info di un dipendente
 * @param[in] i Numero di dipendenti nel sistema (int)
 * @param[in] *d Puntatore ai dipendenti (Dipendente) */
void infoDipendente(int i, Dipendente *d);

// FUNZIONI LAMBDA TIMES E DIVIDE

/** @brief "Ritorna il risultato di una moltiplicazione
 * di elementi di cui non è necessario sapere il tipo."
 * @param[in] n1 Un numero (auto)
 * @param[in] n2 Un numero (auto)
 * @return Prodotto (auto) */
constexpr auto times = [](auto n1, auto n2) { return n1 * n2; };

/** @brief "Ritorna il risultato di una divisione
 * di elementi di cui non è necessario sapere il tipo."
 * @param[in] n1 Un numero (auto)
 * @param[in] n2 Un numero (auto)
 * @return Quoziente (auto) */
constexpr auto divide = [](auto n1, auto n2) { return n1 / n2; };

/// Ritorna il valore attuale dell'IVA
constexpr float IVA() { return 22.0; }

/** @brief Stampa a schermo il costo di un prodotto senza IVA
 * @param[in] i Numero di prodotti nel sistema (int)
 * @param[in] *p Puntatore ai prodotti (Prodotto) */
void calcIva(int i, Prodotto *p);

/** @brief SImula un cliente che effettua un ordine di un prodotto dell'azienda
 * @param[in] i Numero di clienti nel sistema (int)
 * @param[in] j Numero di prodotti nel sistema (int)
 * @param[in] *c Puntatore ai clienti (Cliente)
 * @param[in] *p Puntatore ai prodotti (Prodotto)
 * @return bool: true se l'ordine va a buon fine, false in caso contrario */
bool effettuaOrdine(int i, int j, Cliente *c, Prodotto *p);

/** @brief "Funzione che controlla che il codice fiscale
 * inserito non appartenga già a qualche altro
 * dipendente"
 * @param[in] q E' il codice fiscale dato in input (string)
 * @param[in] i E' il numero di dipendente attualmente nel sistema (int)
 * @param[in] *d E' il puntatore ai dipendenti (Dipendente)
 * @return Ritorna un codice fiscale corretto */
string checkCFD(string q, int i, Dipendente *d);

/** @brief "Controlla che il codice fiscale passato non
 * appartenga ad un altro cliente e ne ad un
 * altro dipendente."
 * @param[out] *q Puntatore al codice fiscale da controllare (string)
 * @param[in] *i Puntatore al numero di clienti (int)
 * @param[in] *c Puntatore ai clienti (Cliente) */
void checkCFC(string *q, int *i, Cliente *c);

/** @brief Controlla che la matricola inserita non esista già.
 * @param[in] q La matricola da controllare
 * @param[in] i Numero di dipendenti attuale
 * @param[in] *d Puntatore ai dipendenti
 * @return Ritorna una matricola corretta. */
string checkMatricola(string q, int i, Dipendente *d);

/** @brief Controlla che il codice cliente inserito non esista già.
 * @param[in] q Il codice cliente da controllare
 * @param[in] i Numero di clienti attuale
 * @param[in] *c Puntatore ai clienti
 * @return Ritorna un codice cliente corretto. */
string checkCodiceCliente(string q, int i, Cliente *c);

/** @brief Controlla che il codice prodotto inserito non esista già.
 * @param[in] q Il codice prodotto da controllare
 * @param[in] i Numero di prodotti attuale
 * @param[in] *p Puntatore ai prodotti
 * @return Ritorna un codice cliente corretto. */
string checkCodiceProdotto(string q, int i, Prodotto *p);

// template <typename X> string visualizza(X *a, int i);

/** @brief Controlla l'integrità della struttura di un codice fiscale
 * @param[in] &str Indirizzo al codice fiscale da controllare (string)
 * @return bool: true se il codice fiscale è corretto, false altrimenti */
bool CF_Corretto(string &str);

/** @brief Aggiunge un nuovo elemento di classe Dipendente
 * @param[out] *i Puntatore al numero di dipendenti
 * @param[in] *d Puntatore alla lista dei dipendenti
 * @return Nuovo puntatore alla lista dei dipendenti */
Dipendente *nuovoDipendente(int *i, Dipendente *d_pointer);

/** @brief Aggiunge un nuovo elemento di classe Cliente
 * @param[out] *i Puntatore al numero di clienti
 * @param[in] *c Puntatore alla lista dei clienti
 * @return Nuovo puntatore alla lista dei clienti */
Cliente *nuovoCliente(int *i, Cliente *c_pointer);

/** @brief Aggiunge un nuovo elemento di classe Prodotto
 * @param[out] *i Puntatore al numero di prodotti
 * @param[in] *c Puntatore alla lista dei prodotti
 * @return Nuovo puntatore alla lista dei prodotti */
Prodotto *nuovoProdotto(int *i, Prodotto *p_pointer);

/** @brief Legge i dipendenti da file e li inserisce in un puntatore
 * @param[out] *num Conterr� il numero di dipendenti
 * @return Ritorna il puntatore alla lista di dipendenti */
Dipendente *lettura_dipendenti(int *num);

/** @brief Legge i clienti da file e li inserisce in un puntatore
 * @param[out] *num Conterr� il numero di clienti
 * @return Ritorna il puntatore alla lista di clienti */
Cliente *lettura_clienti(int *num);

/** @brief Legge i prodotti da file e li inserisce in un puntatore
 * @param[out] *num Conterr� il numero di prodotti
 * @return Ritorna il puntatore alla lista di prodotti */
Prodotto *lettura_prodotti(int *num);

/** @brief Scrive su file i valori attuali dei puntatori ai vari elementi
 * @param[in] i Numero dei dipendenti
 * @param[in] j Numero dei clienti
 * @param[in] k Numero dei prodotti
 * @param[in] *d Puntatore ai dipendenti
 * @param[in] *c Puntatore ai clienti
 * @param[in] *p Puntatore ai prodotti */
void scritturaFile(int i, int j, int k, Dipendente *d, Cliente *c, Prodotto *p);

/** @brief Modifica il nominativo di un dipendente
 * @param[in] i Numero dei dipendenti
 * @param[in] *d Puntatore ai dipendenti
 * @return Ritorna un puntatore aggiornato */
Dipendente *modificaNominativoDipendente(int i, Dipendente *d);

/** @brief Modifica l'indirizzo di un cliente
 * @param[in] i Numero dei clienti
 * @param[in] *d Puntatore ai clienti
 * @return Ritorna un puntatore aggiornato */
Cliente *modificaIndirizzoCliente(int i, Cliente *c);

/** @brief Modifica la quantità di un prodotto
 * @param[in] i Numero dei prodotti
 * @param[in] *d Puntatore ai proditti
 * @return Ritorna un puntatore aggiornato */
Prodotto *modificaQuantitaProdotto(int i, Prodotto *p);

/** @brief Modifica il prezzo di un prodotto
 * @param[in] i Numero dei prodotti
 * @param[in] *d Puntatore ai proditti
 * @return Ritorna un puntatore aggiornato */
Prodotto *modificaPrezzoProdotto(int i, Prodotto *p);

#endif

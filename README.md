Students info:

Lorenzo Bonetti
Fabio Livorno
Filippo Lovato

Short Project Description:

Il progetto consiste in un menù gestionale di un'azienda.
Vi sono 4 classi totali: Persona, Dipendente e Cliente (classi figlie di Persona) e Prodotto.
All'avvio del programma vengono caricati, da file, i dati dei dipendenti, clienti e dei prodotti già presenti nel sistema.
Viene mostrato un menù che verrà riproposto ogni qual volta l'operazione precedentemente selezionata viene terminata.
Tra le varie opzioni del menù vi sono la visualizzazione completa di una classe di oggetti, la ricerca filtrata di un particolare oggetto e l'inserimento di nuovi dipendenti/clienti/prodotti.
Prima di terminare il programma provvede alla sovrascrittura dei file precedentemente letti inserendo, ove necessario, i nuovi oggetti creati nel "database" testuale.

How to run:

- cmake .
- make
- ./azienda

in alternativa, avendo sviluppato il comando instal:

- cmake .
- make
- make instal 
- ./bin/azienda

Make commands available:

- make doc
- make test
- make instal
- make valgrind
- make analysis
- make tidy
- make stats
- make cyclo

Debug/Release mode:

- cmake -DCMAKE_BUILD_TYPE=Debug
- cmake -DCMAKE_BUILD_TYPE=Release

To format with our configuration file (using Google style):

- clang-format -i -style=file src/source.cpp
- clang-format -i -style=file src/main.cpp
- clang-format -i -style=file test/test.cpp
- clang-format -i -style=file include/header.hpp

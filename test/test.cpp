#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main()
#include "../include/catch.hpp"
#include "../include/header.hpp"

TEST_CASE("Vendite oggi", "[venditeOggi::number]") {
  SECTION("Check sul valore di venditeOggi::number") {
    REQUIRE(venditeOggi::getNumber() == 0);

    venditeOggi::increaseNumber();  // aumento di 1 il valore della variabile
                                    // venditeOggi::number

    REQUIRE(venditeOggi::getNumber() == 1);
  }
}

TEST_CASE("Constexpr", "[valore]") {
  SECTION("IVA attuale") {
    REQUIRE(IVA() == 22.0);

    Prodotto *p = new Prodotto();

    p[0].setCodiceProdotto("P003");
    p[0].setNomeProdotto("LG Nexus 5X");
    p[0].setMarca("LG");
    p[0].setQuantita(3);
    p[0].setPrezzo(219.99);
    p[0].setStato(static_cast<statop>(0));

    // utilizzo auto per calcolare nel momento di compilazione il tipo
    // dell'attributo prezzo
    auto prezzo = p[0].getPrezzo();

    // utilizzo le funzioni lambda times e divide
    auto sub = divide(times(static_cast<float>(prezzo), IVA()), 100.00);
    prezzo = prezzo - sub;

    REQUIRE(prezzo == 171.59221f);
  }

  SECTION("Funzioni lambda") {
    SECTION("Moltiplicazione tra due valori di tipo auto") {
      REQUIRE(times(3, 9) == 27);
      REQUIRE(times(2.5, 3) == 7.5);
    }

    SECTION("Divisione tra due valori di tipo auto") {
      REQUIRE(divide(2, 2) == 1);
      REQUIRE(divide(2.0, 4) == 0.5);
    }
  }
}

TEST_CASE("Funzioni set e get delle classi", "[stato]") {
  SECTION("Check sul valore di stato") {
    Prodotto *p = new Prodotto();

    p[0].setStato(static_cast<statop>(0));  // imposto lo stato a "Nuovo"

    REQUIRE(p[0].getStato() == "Nuovo");

    p[0].setStato(static_cast<statop>(1));  // imposto lo stato a "Usato"

    REQUIRE(p[0].getStato() == "Usato");
  }
}

TEST_CASE("Check sul return di getNominativo()", "[getNominativo()]") {
  SECTION("Prodotto::getNominativo()") {
    Prodotto *p = new Prodotto();

    p[0].setNomeProdotto("Laptop Lenovo");
    p[0].setMarca("Lenovo");
    p[0].setStato(static_cast<statop>(0));

    REQUIRE(p[0].getNominativo() ==
            "\nNome Prodotto: Laptop Lenovo\nMarca: Lenovo\nStato: Nuovo");
  }

  SECTION("Dipendente::getNominativo()") {
    Dipendente *d = new Dipendente();

    d[0].setNome("Carlo");
    d[0].setCognome("Reazzi");
    d[0].setMatricola("D001");

    REQUIRE(d[0].getNominativo() ==
            "\nNome: Carlo\nCognome: Reazzi\nMatricola: D001");
  }

  SECTION("Cliente::getNominativo()") {
    Cliente *c = new Cliente();

    c[0].setNome("Mattia");
    c[0].setCognome("Spalto");
    c[0].setCodiceCliente("C001");

    REQUIRE(c[0].getNominativo() ==
            "\nNome: Mattia\nCognome: Spalto\nCodice cliente: C001");
  }
}

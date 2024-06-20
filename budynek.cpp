#include "budynek.h"


Miejscowosc::Miejscowosc(const char* nazwa) {
    strncpy(this->nazwa, nazwa, sizeof(this->nazwa));
    this->nazwa[sizeof(this->nazwa) - 1] = '\0';
}

const char* Miejscowosc::getNazwa() const {
    return nazwa;
}


int Budynek::liczbaInnychBudynkow = 0;


Budynek::Budynek(const Miejscowosc& miejscowosc, const char* ulica, int numer, int kodPocztowy, double metraz, Typ typ)
    : miejscowosc(miejscowosc), numer(numer), kodPocztowy(kodPocztowy), metraz(metraz), typ(typ) {
    strncpy(this->ulica, ulica, sizeof(this->ulica));
    this->ulica[sizeof(this->ulica) - 1] = '\0';
    validate();
    if (typ != PUBLICZNY) {
        liczbaInnychBudynkow++;
    }
}

Budynek::~Budynek() {
    if (typ != PUBLICZNY) {
        liczbaInnychBudynkow--;
    }
}

const Miejscowosc& Budynek::getMiejscowosc() const {
    return miejscowosc;
}

const char* Budynek::getUlica() const {
    return ulica;
}

int Budynek::getNumer() const {
    return numer;
}

int Budynek::getKodPocztowy() const {
    return kodPocztowy;
}

double Budynek::getMetraz() const {
    return metraz;
}

Budynek::Typ Budynek::getTyp() const {
    return typ;
}

void Budynek::setUlica(const char* ulica) {
    strncpy(this->ulica, ulica, sizeof(this->ulica));
    this->ulica[sizeof(this->ulica) - 1] = '\0';
}

void Budynek::setNumer(int numer) {
    this->numer = numer;
    validate();
}

void Budynek::setKodPocztowy(int kodPocztowy) {
    this->kodPocztowy = kodPocztowy;
    validate();
}

void Budynek::setMetraz(double metraz) {
    this->metraz = metraz;
    validate();
}

void Budynek::setTyp(Typ typ) {
    if (this->typ != PUBLICZNY && typ == PUBLICZNY) {
        liczbaInnychBudynkow--;
    } else if (this->typ == PUBLICZNY && typ != PUBLICZNY) {
        liczbaInnychBudynkow++;
    }
    this->typ = typ;
}

double Budynek::obliczPodatek() const {
    return metraz * 10;
}

Budynek::operator double() const {
    return metraz * 1.41421356; //(przekatna = sqrt(2) * strona)
}

int Budynek::getLiczbaInnychBudynkow() {
    return liczbaInnychBudynkow;
}

void Budynek::validate() const {
    if (numer <= 0 || kodPocztowy <= 0 || metraz <= 0) {
        throw std::invalid_argument(""zle dane dzialki");
    }
}


Posiadlosc::Posiadlosc(const Miejscowosc& miejscowosc, const char* ulica, int numer, int kodPocztowy, double metraz, Typ typ, double dzialka)
    : Budynek(miejscowosc, ulica, numer, kodPocztowy, metraz, typ), dzialka(dzialka) {
    if (dzialka <= 0) {
        throw std::invalid_argument("zle dane dzialki");
    }
}

double Posiadlosc::getDzialka() const {
    return dzialka;
}

void Posiadlosc::setDzialka(double dz) {
    if (dz <= 0) {
        throw std::invalid_argument("zle dane dzialki");
    }
    dzialka = dz;
}

double Posiadlosc::obliczPodatek() const {
    return Budynek::obliczPodatek() + dzialka * 5;
}

bool Posiadlosc::operator==(const Posiadlosc& other) const {
    if (getTyp() != other.getTyp()) {
        throw std::logic_error("Types are different");
    }
    return (strcmp(this->getMiejscowosc().getNazwa(), other.getMiejscowosc().getNazwa()) == 0 &&
            this->getMetraz() == other.getMetraz() &&
            this->dzialka == other.dzialka);
}

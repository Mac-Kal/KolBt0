#ifndef BUDYNEK_H
#define BUDYNEK_H

#include <cstring>
#include <stdexcept>

class Miejscowosc {
public:
    Miejscowosc(const char* nazwa);
    const char* getNazwa() const;

private:
    char nazwa[100];
};

class Budynek {
public:
    enum Typ { MIESZKALNY, PUBLICZNY, KOMERCYJNY };

    Budynek(const Miejscowosc& miejscowosc, const char* ulica, int numer, int kodPocztowy, double metraz, Typ typ);
    virtual ~Budynek();

  
    const Miejscowosc& getMiejscowosc() const;
    const char* getUlica() const;
    int getNumer() const;
    int getKodPocztowy() const;
    double getMetraz() const;
    Typ getTyp() const;

    
    void setUlica(const char* ulica);
    void setNumer(int numer);
    void setKodPocztowy(int kodPocztowy);
    void setMetraz(double metraz);
    void setTyp(Typ typ);

    virtual double obliczPodatek() const;
    operator double() const; 

    static int getLiczbaInnychBudynkow();

private:
    Miejscowosc miejscowosc;
    char ulica[100];
    int numer;
    int kodPocztowy;
    double metraz;
    Typ typ;

    static int liczbaInnychBudynkow;

    void validate() const;
};

class Posiadlosc : public Budynek {
public:
    Posiadlosc(const Miejscowosc& miejscowosc, const char* ulica, int numer, int kodPocztowy, double metraz, Typ typ, double dzialka);
    
    double getDzialka() const;
    void setDzialka(double dz);

    double obliczPodatek() const override;
    bool operator==(const Posiadlosc& other) const; 

private:
    double dzialka;
};

#endif

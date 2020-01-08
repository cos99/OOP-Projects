#include <iostream>
#include <tuple>
#include <bits/stdc++.h>
#include <typeinfo>

using namespace std;

///Clasa film

class Film {
private:
    string nume;
    string tip;
    int durata;              /// durata va fi trecuta in minute
    unsigned long incasari;
public:
    Film();
    void initFilm(string, string, int, unsigned long);
    Film(const Film&);
    unsigned long getIncasari();
    void afisareFilm();
    void afisareNumeFilm();
    friend istream & operator>>(istream& in, Film &f);
    ~Film() {}
};

Film::Film()
{
    nume = "";
    tip = "";
    durata  = 0;
    incasari = 0;
}

unsigned long Film::getIncasari()
{
    return incasari;
}

void Film::initFilm(string n, string t, int d, unsigned long i)
{
    this->nume = n;
    this->tip = t;
    this->durata = d;
    this->incasari = i;
}

Film::Film(const Film &f)
{
    nume = f.nume;
    tip = f.tip;
    durata = f.durata;
    incasari = f.incasari;
}

void Film::afisareNumeFilm()
{
    cout << nume;
}

void Film::afisareFilm()
{
    cout << "Numele filmului este: " << nume << endl;
    cout << "Genul filmului este: " << tip << endl;
    cout << "Durata filmului este: " << durata << endl;
    cout << "Incasarile filmului sunt: " << incasari << endl;
}

istream & operator>>(istream& in, Film &f)
{
    cout << "Introduceti numele filmului: ";
    in.ignore();
    getline(in, f.nume);
    cout << "\nIntroduceti genul filmului: ";
    getline(in, f.tip);
    cout << "\nIntroduceti durata filmului: ";
    in >> f.durata;
    cout << "\nIntroduceti incasarile filmului: ";
    in >> f.incasari;
    cout << "\n";

    return in;
}



///Clasa personal

class Personal {
protected:
    string nume;
    string cnp;
    string nume_film;
public:
    Personal();
    Personal(const Personal&);
    Personal& operator=(const Personal&);
    virtual void afisare();
    friend istream& operator>>(istream& in, Personal& p);
    virtual ~Personal() {}
};

Personal::Personal()
{
    nume = "";
    cnp = "";
}

Personal::Personal(const Personal& p)
{
    nume = p.nume;
    cnp = p.cnp;
    nume_film = p.nume_film;
}

Personal& Personal::operator=(const Personal& p)
{
    this->nume = p.nume;
    this->cnp = p.cnp;
    this->nume_film = p.nume_film;
    return *this;
}

void Personal::afisare()
{
    cout << "Numele persoanei este: " << nume;
    cout << "\nCnp-ul persoanei este: " << cnp;
    cout << "\nFilmul la care a participat este: " << nume_film;
    cout << "\n";
}

istream& operator>>(istream& in, Personal& p)
{
    cout << "Introduceti numele persoanei: ";
    in.ignore();
    getline(in, p.nume);
    cout << "\nIntroduceti cnp-ul persoanei: ";
    getline(in, p.cnp);
    cout << "\nIntroduceti filmul la care a participat: ";
    getline(in, p.nume_film);
    cout << "\n";

    return in;
}



///Clasa Actor

class Actor: public Personal {
protected:
    string rol;
    unsigned long bonus;           /// 10% actor in rolul principal, 5% in alte cazuri
public:
    Actor();
    Actor(const Actor& a):Personal(a) { rol = a.rol; bonus = a.bonus; }
    Actor& operator=(const Actor& a)
    {
        Personal::operator=(a);
        this->rol = a.rol;
        this->bonus = a.bonus;
        return *this;
    }
    string getRol()
    {
        return rol;
    }
    void calculareBonus(unsigned long);  /// in main voi cauta in vectorul de filme si voi transmite ca parametru functiei incasarile
    friend istream& operator>>(istream& in, Actor &a);
    void afisare();
    ~Actor() {}
};

Actor::Actor()
{
    rol = "";
    bonus = 0;
}

void Actor::calculareBonus(unsigned long incasari)
{
    if (rol == "principal" || rol == "Principal")
    {
        bonus = incasari * 0.1;
    }
    else
        bonus = incasari * 0.05;
}

istream& operator>>(istream& in, Actor &a)
{
    in >> dynamic_cast<Personal&>(a);
    cout << "Introduceti rolul actorului: ";
    //in.ignore();
    getline(in, a.rol);
    cout << endl;

    return in;
}

void Actor::afisare()
{
    Personal::afisare();
    cout << "Rolul actorului: " << rol << endl;
    cout << "Bonusul primit de actor: " << bonus << endl;
}


///Clasa Regizor

class Regizor: public Personal {
protected:
    unsigned long bonus;     /// se calculeaza dupa ce regizorul este adaugat si se cunoaste la ce film a lucrat
    long salariu;            /// este o suma fixa introdusa de la tastatura
public:
    Regizor();
    Regizor(const Regizor& r):Personal(r) { bonus = r.bonus; salariu = r.salariu; }
    Regizor& operator=(const Regizor& r)
    {
        Personal::operator=(r);
        this->bonus = r.bonus;
        this->salariu = r.salariu;
        return *this;
    }
    void calculareBonus(unsigned long);
    friend istream& operator>>(istream& in, Regizor &r);
    void afisare();
    ~Regizor() {}
};

Regizor::Regizor()
{
    bonus = 0;
    salariu = 0;
}

istream& operator>>(istream& in, Regizor &r)
{
    in >> dynamic_cast<Personal&>(r);
    cout << "Introduceti rolul regizorului: ";
    in >> r.salariu;
    cout << endl;

    return in;
}

void Regizor::calculareBonus(unsigned long b)
{
    bonus = b * 0.1;
}

void Regizor::afisare()
{
    Personal::afisare();
    cout << "Bonusul regizorului este: " << bonus << endl;
    cout << "Salariul regizorului este: " << salariu << endl;
}



/// clasa template

template <class T> class FirmaDistributie{

private:
    static unsigned int nr_personal, nr_actori;
    const int an;

    unsigned int nr_filme;

    Personal **grupPersonal;
    vector<Film> f;

public:
    FirmaDistributie();
    FirmaDistributie(int,int);
    virtual ~FirmaDistributie();

    FirmaDistributie(const FirmaDistributie&);
    FirmaDistributie& operator=(const FirmaDistributie&);

    static unsigned int get_nr_personal() { return nr_personal; }
    static T get_nr_actori() { return nr_actori; }

    template <class A>
    void incrementeazaPersonal(A obiect);

    void citire();
    void scriere();
};

/// declarare functii clasa template

template<class T> unsigned int FirmaDistributie<T>::nr_personal = 0;
template<class T> unsigned int FirmaDistributie<T>::nr_actori = 0;

template<class T>
FirmaDistributie<T>::FirmaDistributie()
{
    grupPersonal = NULL;
    nr_filme = 0;
    an = 2020;
}

template<class T>
FirmaDistributie<T>::~FirmaDistributie()
{
    for (int i = 0; i < nr_personal; i++)
    {
        delete grupPersonal[i];
    }
    delete []grupPersonal;
}

template<class T>
FirmaDistributie<T>::FirmaDistributie(const FirmaDistributie &copyconstr)
{
    nr_filme = copyconstr.nr_filme;
    nr_personal = copyconstr.nr_personal;
    nr_actori = copyconstr.nr_actori;

    grupPersonal = new Personal*[copyconstr.nr_personal];
}

template <class T>
FirmaDistributie<T>& FirmaDistributie<T>::operator=(const FirmaDistributie &f)
{
    if(this == &f)
    {
        return *this;
    }

    nr_filme = f.nr_filme;
    nr_actori = f.nr_actori;
    nr_personal = f.nr_personal;

    grupPersonal = new Personal*[f.nr_personal];

    return *this;
}

template<class T>template<class A>
void FirmaDistributie<T>::incrementeazaPersonal(A obiect)
{
    if(strstr(typeid(*(grupPersonal[nr_personal])).name(),"Actor") != NULL)
    {
        nr_actori++;
    }
    nr_personal++;


}

template<class T>
void FirmaDistributie<T>::citire()
{
    int i;
    string x;
    cout << "Dati numarul de filme din anul " << an << ": ";
    cin >> nr_filme;

    Film F;

    for( i = 0; i < nr_filme; i++)
    {
        cin >> F;
        f.push_back(F);
    }

    cout << "Alegeti tipul personalului (Actor/Regizor): ";
    cin >> x;

    T *ob = new T();

    if ( x == "Actor")
        ob = new Actor();
    else
        ob = new Regizor();

    cin >> ob;
    grupPersonal[nr_personal] = ob;
    incrementeazaPersonal(grupPersonal[nr_personal]);

}

template<class T>
void FirmaDistributie<T>::scriere()
{
    int i;
    cout << "Filmele din anul" << an << "sunt :" << endl;

    vector<Film>::iterator p;

    for( p = f.begin(); p<f.end(); p++)
        p->afisareFilm();
    cout << endl;

    for (int i = 0; i < nr_personal; i++)
    {
        grupPersonal[i]->afisare();
        cout << endl;
    }
}

/// specializare actor

template<>
class FirmaDistributie<Actor>
{
private:
    static int nr_actori_principali;

public:
    void numarActoriPP(Actor a)
    {
        if (a.getRol() == "Principal" || a.getRol() == "principal")
            nr_actori_principali++;
    }
    void afisareNrActoriPP()
    {
        cout << "Numarul de actori principali este: " << nr_actori_principali << endl;
    }
};

int FirmaDistributie<Actor>::nr_actori_principali = 0;

/// main-ul problemei

int main()
{
    Film f[100];
    Personal *p[200];

/**
    cout << "Referinta la baza non-polimorfica: " << typeid(p).name() << endl;

    Regizor r;
    Personal& p1 = r;

    cout << "Referinta la baza non-polimorfica: " << typeid(p1).name() << endl;
*/
    int nrfilme;
    cout << "Introduceti numarul de filme: ";
    cin >> nrfilme;
    cout << endl;

    cout << "Introduceti informatiile celor " << nrfilme << " filme: " << endl;
    for (int i = 0; i < nrfilme; i++)
    {
        cin >> f[i];
    }

    int nrtotpers = 0;

    for (int i = 0; i < nrfilme; i++)
    {
        int s;
        unsigned long bonus;
        cout << "Alegeti tipul de personal care a lucrat la filmul ";
        f[i].afisareNumeFilm();
        cout << endl;
        cout << "1. Actor" << endl << "2. Regizor" << endl << "0. Urmatorul film";
        cin >> s;
        /**
        while (s)
        {
            if (s == 1)
            {
                p[nrtotpers] = new Actor;
                cin >> p[nrtotpers]
                nrtotpers++;
                bonus = f[i].getIncasari();
                p[nrtotpers]->calculareBonus(bonus);
            }
            if (s == 2)
            {
                p[nrtotpers] = new Regizor;
                cin >> p[nrtotpers]
                nrtotpers++;
                bonus = f[i].getIncasari();
                p[nrtotpers]->calculareBonus(bonus);
            }

            cout << "Alegeti tipul de personal care a lucrat la filmul ";
            f[i].afisareNumeFilm();
            cout << endl;
            cout << "1. Actor" << endl << "2. Regizor" << endl << "0. Urmatorul film";
            cin >> s;
        }
        */
        cout << "Lista de filme este: ";
        for (int i = 0; i < nrfilme; i++)
        {
            f[i].afisareFilm();
        }
        for (int i = 0; i < nrtotpers; i++)
        {
            p[i]->afisare();
        }

    }
    return 0;
}

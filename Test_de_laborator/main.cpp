///Costea Andrei 254 GNU GCC Compiler
#include <iostream>

using namespace std;


/**--------Clasa Facultate---------*/

class Facultate {
private:
    int nr_locuri_IF;
    int nr_locuri_ID;
    float procent_locuri_taxa;  /// un numar intre 0 si 1
public:
    Facultate();
    Facultate(const Facultate& f);
    int getLocuriTaxaID();
    int getLocuriTaxaIF();
    friend istream& operator>>(istream& in, Facultate& f);
    friend ostream& operator<<(ostream& out, Facultate& f);

};

Facultate::Facultate()
{
    nr_locuri_ID = 0;
    nr_locuri_IF = 0;
    procent_locuri_taxa = 0;
}

Facultate::Facultate(const Facultate& f)
{
    nr_locuri_ID = f.nr_locuri_ID;
    nr_locuri_IF = f.nr_locuri_IF;
    procent_locuri_taxa = f.procent_locuri_taxa;
}

int Facultate::getLocuriTaxaID()
{
    return procent_locuri_taxa * nr_locuri_ID;
}

int Facultate::getLocuriTaxaIF()
{
    return procent_locuri_taxa * nr_locuri_IF;
}

istream& operator>>(istream& in, Facultate& f)
{
    cout << "Introduceti numarul de locuri de la invatamantul cu frecventa: ";
    in >> f.nr_locuri_IF;
    cout << endl;
    cout << "Introduceti numarul de locuri de la invatamantul la distanta: ";
    in >> f.nr_locuri_ID;
    cout << endl;
    cout << "Introduceti procentrul din numarul total de locuri alocat candidatilor de la a doua facultate: ";
    in >> f.procent_locuri_taxa;
    cout << endl;

    return in;
}

ostream& operator<<(ostream& out, Facultate &f)
{
    out << "Numarul de locuri de la invatamantul cu frecventa: ";
    out << f.nr_locuri_IF;
    out << endl;
    out << "Numarul de locuri de la invatamantul la distanta: ";
    out << f.nr_locuri_ID;
    out << endl;
    out << "Locuri disponibile pentru a doua facultate la IF: ";
    out << f.getLocuriTaxaIF();
    out << endl;
    out << "Locuri disponibile pentru a doua facultate la ID: ";
    out << f.getLocuriTaxaID();
    out << endl;

    return out;
}

/**----------------Clasa Candidat----------------*/

class Candidat {
private:
    string nume;
    string prenume;
    float medie_bac;
    float nota_matematica;
    static int IF1;
    static int IF2;
    static int ID1;
    static int ID2;
    float nota_examen_scris;
    string program;
    float medie_admitere;
    float nota_prima_fac;
public:
    void citire();
    string getProgram();
    void afisare();
};

int Candidat::IF1 = 0;
int Candidat::IF2 = 0;
int Candidat::ID1 = 0;
int Candidat::ID2 = 0;


void Candidat::citire()
{
    cout << "Introduceti numele candidatului: ";
    cin >> nume;
    cout << endl << "Introduceti prenumele candidatului: ";
    cin >> prenume;
    cout << endl << "Introduceti media de la bacalaureat a candidatului: ";
    cin >> medie_bac;
    cout << endl << "Introduceti nota la matematica de la bacalaureat sau echivalentul acesteia: ";
    cin >> nota_matematica;
    cout << endl << "In cazul in care ati terminat o facultate, introduceti nota (0, daca nu este cazul): ";
    cin >> nota_prima_fac;
    cout << endl << "Alegeti tipul de invatamant: 1 = frecventa, 2 = distanta: ";
    int x, y;
    cin >> x;
    cout << endl << "Alegeti numarul facultatii: 1 = prima, 2 = a doua: ";
    cin >> y;
    if (x == 1)
    {
        if (y == 1)
        {
            cout << endl << "Introduceti programul la care doriti sa va inscrieti: ";
            cin >> program;
            IF1++;
            cout << endl << "Introduceti media de la examen: ";
            cin >> nota_examen_scris;
            medie_admitere = 0.8 * nota_examen_scris + 0.2 * medie_bac;
        }
        else if (y == 2)
        {
            cout << endl << "Introduceti programul la care doriti sa va inscrieti: ";
            cin >> program;
            IF2++;
            cout << endl << "Introduceti media de la examen: ";
            cin >> nota_examen_scris;
            medie_admitere = 0.6 * nota_examen_scris + 0.4 * nota_prima_fac;
        }
        else
            cout << "Input invalid!";
    }
    else if (x == 2)
    {
        if (y == 1)
        {
            cout << endl << "Introduceti programul la care doriti sa va inscrieti: ";
            cin >> program;
            ID1++;
            cout << endl << "Introduceti media de la examen: ";
            cin >> nota_examen_scris;
            medie_admitere = 0.6 * nota_examen_scris + 0.4 * nota_matematica;
        }
        else if (y == 2)
        {
            cout << endl << "Introduceti programul la care doriti sa va inscrieti: ";
            cin >> program;
            ID2++;
            cout << endl << "Introduceti media de la examen: ";
            cin >> nota_examen_scris;
            medie_admitere = 0.6 * nota_examen_scris + 0.4 * nota_prima_fac;
        }
        else
            cout << "Input invalid!";
    }
    cout << endl;
}
void Candidat::afisare()
{
    cout << "Nume: " << nume << endl;
    cout << "Prenume: " << prenume << endl;
    cout << "Media Bacalaureat: " << medie_bac << endl;
    cout << "Nota matematica sau echivalent: " << nota_matematica << endl;
    if (nota_prima_fac != 0)
        cout << "Nota prima facultate: " << nota_prima_fac << endl;
    cout << "Media de la admitere: " << medie_admitere << endl;
}

string Candidat::getProgram()
{
    return program;
}

int main()
{
    /**
    Facultate f;
    cin >> f;
    cout << f;
    */
    Candidat c[2000];
    int i = 0, x;
    cout << "Alegeti o optiune: " << endl << "1. Adaugati candidat \n2. Afisati candidatii \n";
    cin >> x;
    while (x == 1)
    {
        c[i].citire();
        i++;
        cout << "Alegeti o optiune: " << endl << "1. Adaugati candidat \n2. Afisati candidatii \n";
        cin >> x;
    }
    if (x == 2)
    {
        cout << "Candidatii inscrisi la programul Matematica:" << endl << "------------------------------------------" << endl;
        for (int j = 0; j < i; j++)
        {
            if (c[j].getProgram() == "Matematica")
                c[j].afisare();
        }
        cout << "Candidatii inscrisi la programul Informatica:" << endl << "------------------------------------------" << endl;
        for (int j = 0; j < i; j++)
        {
            if (c[j].getProgram() == "Informatica")
                c[j].afisare();
        }
        cout << "Candidatii inscrisi la programul CTI:" << endl << "------------------------------------------" << endl;
        for (int j = 0; j < i; j++)
        {
            if (c[j].getProgram() == "CTI")
                c[j].afisare();
        }
    }
    return 0;
}

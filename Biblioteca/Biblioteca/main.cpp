#include <iostream>
#include <cstring>

using namespace std;

/*------Declarare Clase------*/

class Info
{
protected:
    string numeInfo;
    int id;
    static int countObjects;
public:
    Info();
    Info(const Info&);
    virtual void printInfo() {
        if(id != 0)
        {
            cout << id <<" : " << numeInfo << " : " ;
        }
        else return;
    }
    virtual void initInfo(string, string) {}
    virtual void initInfo(string, int) {}
    virtual void initInfo(string, float, float) {}
    string getInfoName();
    virtual int checkInfo(string, string) { return 0; }
    virtual int checkInfo(string, int) { return 0; }
    virtual int checkInfo(string, float, float) { return 0; }
    virtual void deleteInfoAfterName(string) {}
    virtual void deleteInfoAfterID(int) {}
    void initNumeInfo(string);
    void assignID(int);
    int getNumberOfObjects();
    void getInfoAfterID(int);
    void getInfoAfterName(string);
    friend istream& operator>>(istream& in, Info&);
    friend ostream& operator<<(ostream& out, Info&);
    Info operator=(const Info&);
    virtual ~Info() {};
};

class Text: public Info{
    string txt;
public:
    Text();
    Text(const Text& i):Info(i) { txt = i.txt; }
    void initInfo(string, string);
    void printInfo();
    int checkInfo(string, string);
    void deleteInfoAfterName(string);
    void deleteInfoAfterID(int);
    Text operator=(const Text& i) { Info::operator=(i); this->txt = i.txt; return *this; }
    friend istream& operator>>(istream& in, Text&);
    friend ostream& operator<<(ostream& out, Text&);
    ~Text() { delete this; }
};

class Numar: public Info{
    int nr;
public:
    Numar();
    Numar(const Numar& i):Info(i) { nr = i.nr; }
    void printInfo();
    void initInfo(string, int);
    int checkInfo(string, int);
    void deleteInfoAfterName(string);
    void deleteInfoAfterID(int);
    Numar operator=(const Numar& i) { Info::operator=(i); this->nr = i.nr; return *this; }
    friend istream& operator>>(istream& in, Numar&);
    friend ostream& operator<<(ostream& out, Numar&);
    ~Numar() { delete this; }
};

class Matematic: public Info{
    float rez, imz;
public:
    Matematic();
    Matematic(const Matematic& i):Info(i) { rez = i.rez; imz = i.imz; }
    void initInfo(string, float, float);
    void printInfo();
    int checkInfo(string, float, float);
    void deleteInfoAfterName(string);
    void deleteInfoAfterID(int);
    Matematic operator=(const Matematic& i) { Info::operator=(i); this->rez = i.rez; this->imz = i.imz; return *this; }
    friend istream& operator>>(istream& in, Matematic&);
    friend ostream& operator<<(ostream& out, Matematic&);
    ~Matematic() { delete this; }
};

class Adresa: public Info{
    string adr;
public:
    Adresa();
    Adresa(const Adresa& i):Info(i) { adr = i.adr; }
    void initInfo(string, string);
    void printInfo();
    int checkInfo(string, string);
    void deleteInfoAfterName(string);
    void deleteInfoAfterID(int);
    Adresa operator=(const Adresa& i) { Info::operator=(i); this->adr = i.adr; return *this; }
    friend istream& operator>>(istream& in, Adresa&);
    friend ostream& operator<<(ostream& out, Adresa&);
    ~Adresa() { delete this; }
};

/*------Declarare Functii------*/

Info::Info()
{
    numeInfo = "";
}

Info Info::operator=(const Info& i)
{
    this->numeInfo = i.numeInfo;
    return *this;
}

istream& operator>>(istream& in, Info& i)
{
    in >> i.numeInfo;
    i.countObjects++;
    i.assignID(-1);
    return in;
}

ostream& operator<<(ostream& out, Info& i)
{
    out << i.id << " : " << i.numeInfo << " : ";
    return out;
}

istream& operator>>(istream& in, Text& t)
{
    in >> (Info&)t;
    in >> t.txt;
    t.assignID(0);
    return in;
}

ostream& operator<<(ostream& out, Text& t)
{
    out << (Info&)t;
    out << t.txt << endl;
    return out;
}

istream& operator>>(istream& in, Numar& n)
{
    in >> (Info&)n;
    in >> n.nr;
    n.assignID(1);
    return in;
}

ostream& operator<<(ostream& out, Numar& t)
{
    out << (Info&)t;
    out << t.nr << endl;
    return out;
}

istream& operator>>(istream& in, Matematic& m)
{
    in >> (Info&)m;
    in >> m.rez >> m.imz;
    m.assignID(2);
    return in;
}

ostream& operator<<(ostream& out, Matematic& t)
{
    out << (Info&)t;
    out << t.rez << "+(" << t.imz << ")" << endl;
    return out;
}

istream& operator>>(istream& in, Adresa& a)
{
    in >> (Info&)a;
    in >> a.adr;
    a.assignID(3);
    return in;
}

ostream& operator<<(ostream& out, Adresa& t)
{
    out << (Info&)t;
    out << t.adr << endl;
    return out;
}


Info::Info(const Info& i)
{
    numeInfo = i.numeInfo;
}


void Info::initNumeInfo(string n)
{
    numeInfo = n;
}

string Info::getInfoName()
{
    return this->numeInfo;
}

void Info::assignID(int i)
{
    countObjects++;
    if (i == -1)
    {
        id = 0;
        countObjects--;
        return;
    }
    id = countObjects * 10 + i;
}

int Info::getNumberOfObjects()
{
    return countObjects;
}

void Info::getInfoAfterID(int n)
{
    for (int i = 0; i < this->getNumberOfObjects(); i++)
    {
        if(this[i].id == n)
        {
            this[i].printInfo();
        }
    }
}

void Info::getInfoAfterName(string s)
{
    for (int i = 0; i < this->getNumberOfObjects(); i++)
    {
        if(this[i].numeInfo == s)
        {
            this[i].printInfo();
        }
    }
}

int Info::countObjects = 0;

Text::Text()
{
    txt = "";
    initNumeInfo("");
    assignID(-1);
}

void Text::deleteInfoAfterID(int infoID)
{
    int i;
    for (i = 0; i < getNumberOfObjects(); i++)
    {
        if (this[i].id == infoID)
        {
            this[i].txt = "";
            this[i].id = 0;
            this[i].initNumeInfo("");
            cout << "Informatie stearsa" << endl;
            return;
        }
    }
    cout << "Informatia nu exista" << endl;
}

void Text::deleteInfoAfterName(string n)
{
    int i;
    for (i = 0; i < getNumberOfObjects(); i++)
    {
        if (this[i].numeInfo == n)
        {
            this[i].txt = "";
            this[i].id = 0;
            this[i].initNumeInfo("");
            cout << "Informatie stearsa" << endl;
            return;
        }
    }
    cout << "Informatia nu exista" << endl;
}

void Text::initInfo(string n, string t)
{
    if( this->checkInfo(n, t) == 1)
    {
        return;
    }
    else
    {
        this->txt = t;
        initNumeInfo(n);
        assignID(0);
    }
}

void Text::printInfo()
{
    if (this->id == 0)
        return;
    Info::printInfo();
    cout << txt << endl;
}

int Text::checkInfo(string n, string t)
{
    int i;
    for (i = 0; i < countObjects; i++)
    {
        if (this[i].getInfoName() == n)
        {
            this[i].txt = this[i].txt + t;
            return 1;
        }
    }
    return 0;
}

Numar::Numar()
{
    nr = 0;
    initNumeInfo("");
    assignID(-1);
}

void Numar::initInfo(string n, int number)
{
    if( this->checkInfo(n, number) == 1)
    {
        return;
    }
    else
    {
        this->nr = number;
        initNumeInfo(n);
        assignID(1);
    }
}

void Numar::printInfo()
{
    if (this->id == 0)
        return;
    Info::printInfo();
    cout << nr << endl;
}

int Numar::checkInfo(string n, int t)
{
    int i;
    for (i = 0; i < countObjects; i++)
    {
        if (this[i].getInfoName() == n)
        {
            this[i].nr = this[i].nr + t;
            return 1;
        }
    }
    return 0;
}

void Numar::deleteInfoAfterID(int infoID)
{
    int i;
    for (i = 0; i < getNumberOfObjects(); i++)
    {
        if (this[i].id == infoID)
        {
            this[i].nr = 0;
            this[i].id = 0;
            this[i].initNumeInfo("");
            cout << "Informatie stearsa" << endl;
            return;
        }
    }
    cout << "Informatia nu exista" << endl;
}

void Numar::deleteInfoAfterName(string n)
{
    int i;
    for (i = 0; i < getNumberOfObjects(); i++)
    {
        if (this[i].numeInfo == n)
        {
            this[i].nr = 0;
            this[i].id = 0;
            this[i].initNumeInfo("");
            cout << "Informatie stearsa" << endl;
            return;
        }
    }
    cout << "Informatia nu exista" << endl;
}

Matematic::Matematic()
{
    rez = 0;
    imz = 0;
    initNumeInfo("");
    assignID(-1);
}

void Matematic::initInfo(string n, float r, float i)
{
    this->rez = r;
    this->imz = i;
    initNumeInfo(n);
    assignID(2);
}

void Matematic::printInfo()
{
    if (this->id == 0)
        return;
    Info::printInfo();
    cout << rez << "+(" << imz << ")i" << endl;
}

int Matematic::checkInfo(string n, float t, float m)
{
    int i;
    for (i = 0; i < countObjects; i++)
    {
        if (this[i].getInfoName() == n)
        {
            this[i].rez = this[i].rez + t;
            this[i].imz = this[i].imz + m;
            return 1;
        }
    }
    return 0;
}

void Matematic::deleteInfoAfterID(int infoID)
{
    int i;
    for (i = 0; i < getNumberOfObjects(); i++)
    {
        if (this[i].id == infoID)
        {
            this[i].rez = 0;
            this[i].imz = 0;
            this[i].id = 0;
            this[i].initNumeInfo("");
            cout << "Informatie stearsa" << endl;
            return;
        }
    }
    cout << "Informatia nu exista" << endl;
}

void Matematic::deleteInfoAfterName(string n)
{
    int i;
    for (i = 0; i < getNumberOfObjects(); i++)
    {
        if (this[i].numeInfo == n)
        {
            this[i].rez = 0;
            this[i].imz = 0;
            this[i].id = 0;
            this[i].initNumeInfo("");
            cout << "Informatie stearsa" << endl;
            return;
        }
    }
    cout << "Informatia nu exista" << endl;
}

Adresa::Adresa()
{
    adr = "";
    initNumeInfo("");
    assignID(-1);
}

void Adresa::initInfo(string n, string a)
{
    this->adr = a;
    initNumeInfo(n);
    assignID(3);
}

void Adresa::printInfo()
{
    if (this->id == 0)
        return;
    Info::printInfo();
    cout << adr << endl;
}

int Adresa::checkInfo(string n, string a)
{
    int i;
    for (i = 0; i < countObjects; i++)
    {
        if (this[i].getInfoName() == n && this[i].getInfoName() != "")
        {
            cout << "Eroare";
            return 1;
        }
    }
    return 0;
}

void Adresa::deleteInfoAfterID(int infoID)
{
    int i;
    for (i = 0; i < getNumberOfObjects(); i++)
    {
        if (this[i].id == infoID)
        {
            this[i].adr = "";
            this[i].id = 0;
            this[i].initNumeInfo("");
            cout << "Informatie stearsa" << endl;
            return;
        }
    }
    cout << "Informatia nu exista" << endl;
}

void Adresa::deleteInfoAfterName(string n)
{
    int i;
    for (i = 0; i < getNumberOfObjects(); i++)
    {
        if (this[i].numeInfo == n)
        {
            this[i].adr = "";
            this[i].id = 0;
            this[i].initNumeInfo("");
            cout << "Informatie stearsa" << endl;
            return;
        }
    }
    cout << "Informatia nu exista" << endl;
}

int main()
{
    int n,i,pp;
    /*------Meniu------*/
    cout << "Introduceti numarul de informatii pe care doriti sa il introduceti: " << endl;
    cin >> n;
    Info *t[n];
    cout << endl << "Alegeti tipul de informatie pe care doriti sa il introduceti: ";
    cout << endl << "0 - Text;";
    cout << endl << "1 - Numeric;";
    cout << endl << "2 - Matematic;";
    cout << endl << "3 - Adresa;" << endl;
    cin >> pp;
    for (i = 0; i < n; i++)
    {
        int nr;
        float real, imaginar;
        string textintodus, a, nume, dummy;
        if(pp == 0)
        {
            t[i] = new Text;
            cout << "Introduceti numele informatiei: (- daca nu are nume) ";
            getline(cin, dummy);
            getline(cin, nume);
            cout << endl << "Introduceti informatia: ";
            getline(cin, textintodus);
            if((*t)->checkInfo(nume, textintodus) == 0)
            {
                t[i]->initInfo(nume, textintodus);
            }
        }
        if(pp == 1)
        {
            t[i] = new Numar;
            cout << "Introduceti numele informatiei: ('-' daca nu are nume) " << endl;
            getline(cin, dummy);
            getline(cin, nume);
            cout << endl << "Introduceti numarul: ";
            cin >> nr;
            if((*t)->checkInfo(nume, nr) == 0)
            {
                t[i]->initInfo(nume, nr);
            }
        }
        if(pp == 2)
        {
            t[i] = new Matematic;
            cout << "Introduceti numele informatiei: (- daca nu are nume) " << endl;
            getline(cin, dummy);
            getline(cin, nume);
            cout << endl << "Introduceti partea reala si imaginara: ";
            cin >> real >> imaginar;
            if((*t)->checkInfo(nume, real, imaginar) == 0)
            {
                t[i]->initInfo(nume, real, imaginar);
            }
        }
        if(pp == 3)
        {
            t[i] = new Adresa;
            cout << "Introduceti numele informatiei: (- daca nu are nume) " << endl;
            getline(cin, dummy);
            getline(cin, nume);
            cout << endl << "Introduceti adresa: ";
            getline(cin, a);
            if((*t)->checkInfo(nume, a) == 0)
            {
                t[i]->initInfo(nume, a);
            }
        }
        if (i < n-1)
        {
            cout << endl << "Alegeti o optiune: ";
            cin >> pp;
        }
    }

    cout << "Alegeti optiune: " << endl;
    cout << "1-Cautare informatii dupa id;" << endl;
    cout << "2-Cautare informatii dupa nume;" << endl;
    cout << "3-Stergere informatii dupa id" << endl;
    cout << "4-Stergere informatii dupa nume" << endl;
    cout << "5-Afisati o informatie specifica" << endl;
    cout << "6-Afisati toate informatiile" << endl;
    cout << "0-Iesire" << endl;
    cin >> pp;
    while(pp)
    {
        if (pp == 1)
        {
            int b;
            cout << "Introduceti ID-ul ";
            cin >> b;
            (*t)->getInfoAfterID(b);
            cout << endl;
        }
        if (pp == 2)
        {
            string b, d;
            cout << "Introduceti numele ";
            getline(cin, d);
            getline(cin, b);
            (*t)->getInfoAfterName(b);
            cout << endl;
        }
        if (pp == 3)
        {
            int b;
            cout << "Introduceti ID- ul ";
            cin >> b;
            (*t)->deleteInfoAfterID(b);
            cout << endl;
        }
        if (pp == 4)
        {
            string d, b;
            cout << "Introduceti numele ";
            getline(cin, d);
            getline(cin, b);
            (*t)->deleteInfoAfterName(b);
            cout << endl;
        }
        if (pp == 5)
        {
            int b;
            cout << "Introduceti a cata informatie doriti sa o afisati ";
            cin >> b;
            t[b]->printInfo();
        }
        if (pp == 6)
        {
            for (i = 0; i < n; i++)
                {
                    t[i]->printInfo();
                }
        }
        cout << "Alegeti optiune: ";
        cin >> pp;
    }
    //t[0]->printInfo();
    return 0;
}

/// Functiile care trateaza cazurile limita (informatii cu acelasi nume) sunt incorporate in
/// meniul de citire, iar adaugarea informatiilor se face la inceputul programului.





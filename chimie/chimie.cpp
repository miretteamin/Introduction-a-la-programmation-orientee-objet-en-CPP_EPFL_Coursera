#include <iostream>
#include <string>
#include <cmath>
using namespace std;

class Flacon
{
private:
    string nom;
    double volume;
    double pH;

public:
    /*****************************************************
      Compléter le code à partir d'ici
    *******************************************************/
    Flacon(string n, double v, double ph) : nom(n), volume(v), pH(ph) {}

    string getNom() const
    {
        return nom;
    }
    double getVolume() const
    {
        return volume;
    }
    double getPH() const
    {
        return pH;
    }

    ostream& etiquette(ostream& sortie) const
    {
        sortie << nom << " : " << volume << " ml, pH " << pH;
        return sortie;
    }

};

ostream& operator<<(ostream& sortie, Flacon const& x)
{
    return x.etiquette(sortie);
}
Flacon operator+(Flacon const& op1, Flacon const& op2)
{
    Flacon f((op1.getNom() +" + " + op2.getNom()),(op1.getVolume()+op2.getVolume()),(-log10((op1.getVolume() * pow(10, - op1.getPH()) + op2.getVolume() * pow(10, - op2.getPH())) / (op1.getVolume() + op2.getVolume()))));
    return f;
}

/*******************************************
 * Ne rien modifier après cette ligne.
 *******************************************/

void afficher_melange(Flacon const& f1, Flacon const& f2)
{
    cout << "Si je mélange " << endl;
    cout << "\t\"" << f1 << "\"" << endl;
    cout << "avec" << endl;
    cout << "\t\"" << f2 << "\"" << endl;
    cout << "j'obtiens :" << endl;
    cout << "\t\"" << (f1 + f2) << "\"" << endl;
}

int main()
{
    Flacon flacon1("Eau", 600.0, 7.0);
    Flacon flacon2("Acide chlorhydrique", 500.0, 2.0);
    Flacon flacon3("Acide perchlorique", 800.0, 1.5);

    afficher_melange(flacon1, flacon2);
    afficher_melange(flacon2, flacon3);

    return 0;

}
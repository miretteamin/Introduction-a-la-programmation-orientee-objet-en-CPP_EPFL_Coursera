#include <iostream>
using namespace std;

/*****************************************************
 * Compléter le code à partir d'ici
 *****************************************************/
class Patient
{
private:
    double taille_;
    double poids_;
public:
    void init(double poids, double taille)
    {
        if (poids >= 0 and taille >= 0)
        {
            poids_ = poids;
            taille_ = taille;
        }
        else
        {
            poids_ = 0.0;
            taille_ = 0.0;
        }
    }
    void afficher() {
        cout << "Patient : " << poids_ << " kg pour " << taille_ << " m" << endl;
    }
    double poids()
    {
        return poids_;
    }
    double taille()
    {
        return taille_;
    }
    double imc() {
        if (taille_ > 0) return poids_ / (taille_ * taille_);
        else return 0.0;

    }
};

 /*******************************************
  * Ne rien modifier après cette ligne.
  *******************************************/

int main()
{
    Patient quidam;
    double poids, taille;
    do {
        cout << "Entrez un poids (kg) et une taille (m) : ";
        cin >> poids >> taille;
        quidam.init(poids, taille);
        quidam.afficher();
        cout << "IMC : " << quidam.imc() << endl;
    } while (poids * taille != 0.0);
    return 0;
}

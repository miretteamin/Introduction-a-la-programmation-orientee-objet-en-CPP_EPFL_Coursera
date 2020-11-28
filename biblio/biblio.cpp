#include <iostream>
#include <vector>
#include <string>
using namespace std;

/*******************************************
 * Completez le programme a partir d'ici.
 *******************************************/
 // Chaines de caract�res � utiliser pour les affichages:
 /*

 �t� jet�

 d'un

 n'est

 L'oeuvre

 biblioth�que

 d�truit

 */
class Auteur
{
private:
    string nom;
    bool prime;
public:
    Auteur(string n, bool p = false) : nom(n), prime(p) {}
    Auteur(Auteur const&) = delete;
    string getNom() const
    {
        return nom;
    }
    bool getPrix() const
    {
        return prime;
    }
};
class Oeuvre
{
private:
    string titre, langue;
    Auteur* auteur;
public:
    Oeuvre(string t, Auteur& a, string l) : titre(t), auteur(&a), langue(l) {}
    Oeuvre(Oeuvre const&) = delete;
    string getTitre()
    {
        return titre;
    }
    Auteur& getAuteur() const
    {
        return *auteur;
    }
    string getLangue() const
    {
        return langue;
    }
    void affiche() const
    {
        cout << titre << ", " << (*auteur).getNom() << ", en " << langue << endl;
    }
    ~Oeuvre() { cout << "L'oeuvre \"" << titre << ", " << (*auteur).getNom() << ", en " << langue << "\" n'est plus disponible." << endl; }
};
class Exemplaire
{
private:
    Oeuvre& livre;
public:
    Exemplaire(Oeuvre& l) : livre(l)
    {
        cout << "Nouvel exemplaire de : ";
        livre.affiche();
        cout << endl;
    }
    Exemplaire(Exemplaire const& copie) : livre(copie.livre)
    {
        cout << "Copie d'un exemplaire de : " << livre.getTitre() << ", " << livre.getAuteur().getNom() << " en " << livre.getLangue() << "\n";
    }

    Oeuvre& getOeuvre()
    {
        return livre;
    }
    void affiche()
    {
        cout << "Exemplaire de : " << livre.getTitre() << ", " << livre.getAuteur().getNom() << ", en " << livre.getLangue() << " ";
    }
    ~Exemplaire()
    {
        cout << "Un exemplaire de \"" << livre.getTitre() << " , " << livre.getAuteur().getNom() << ", en " << livre.getLangue() << "\" a �t� jet� !\n";
    }
};
class Bibliotheque
{
private:
    string bnom;
    vector<Exemplaire*>ex;
public:
    Bibliotheque(string n) : bnom(n) { cout << "La biblioth�que " << bnom << " est ouverte !" << endl; }

    string getNom()
    {
        return bnom;
    }
    void stocker(Oeuvre& l, int n = 1)
    {
        for (int i = 0; i < n; i++)
        {
            Exemplaire* livre = new Exemplaire(l);
            ex.push_back(livre);
        }

    }
    int compter_exemplaires(Oeuvre& book)
    {
        int sum = 0;
        for (unsigned int i = 0; i < ex.size(); i++)
        {
            if ((book.getTitre() == ex[i]->getOeuvre().getTitre()) && (book.getLangue() == ex[i]->getOeuvre().getLangue()))
            {
                sum++;
            }
        }
        return sum;
    }
    void lister_exemplaires(string l = "")
    {
        for (unsigned int i = 0; i < ex.size(); i++)
        {
            if ((l == "") || (l == ex[i]->getOeuvre().getLangue()))
            {
                ex[i]->affiche();
                cout << "\n";
            }
        }
    }
    void afficher_auteurs(bool x = false)
    {
        if (x == true)
        {
            for (int i = 0; i < ex.size(); i++)
            {
                if (ex[i]->getOeuvre().getAuteur().getPrix() == true)
                {
                    cout << ex[i]->getOeuvre().getAuteur().getNom() << endl;
                }
            }
        }
        else
        {
            for (int i = 0; i < ex.size(); i++)
            {
                cout << ex[i]->getOeuvre().getAuteur().getNom() << endl;
            }
        }
    }
    ~Bibliotheque()
    {
        cout << "La biblioth�que " << bnom << " ferme ses portes," << endl << "et d�truit ses exemplaires :" << endl;
        for (int i = 0; i < ex.size(); i++)
        {
            ex[i]->~Exemplaire();
        }
    }
};
/*******************************************
 * Ne rien modifier apres cette ligne.
 *******************************************/

int main()
{
    Auteur a1("Victor Hugo"),
        a2("Alexandre Dumas"),
        a3("Raymond Queneau", true);

    Oeuvre o1("Les Mis�rables", a1, "fran�ais"),
        o2("L'Homme qui rit", a1, "fran�ais"),
        o3("Le Comte de Monte-Cristo", a2, "fran�ais"),
        o4("Zazie dans le m�tro", a3, "fran�ais"),
        o5("The Count of Monte-Cristo", a2, "anglais");

    Bibliotheque biblio("municipale");
    biblio.stocker(o1, 2);
    biblio.stocker(o2);
    biblio.stocker(o3, 3);
    biblio.stocker(o4);
    biblio.stocker(o5);

    cout << "La biblioth�que " << biblio.getNom()
        << " offre les exemplaires suivants :" << endl;
    biblio.lister_exemplaires();

    const string langue("anglais");
    cout << " Les exemplaires en " << langue << " sont :" << endl;
    biblio.lister_exemplaires(langue);

    cout << " Les auteurs � succ�s sont :" << endl;
    biblio.afficher_auteurs(true);

    cout << " Il y a " << biblio.compter_exemplaires(o3) << " exemplaires de "
        << o3.getTitre() << endl;

    return 0;
}

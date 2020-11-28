#include <iostream>
#include <string>
using namespace std;

class Timbre
{
private:
	static constexpr unsigned int ANNEE_COURANTE = 2016;

	/*****************************************************
	 * Compléter le code à partir d'ici
	 *****************************************************/
protected:
	unsigned int annee;
	string nom, pays;
	double valeur_faciale;
public:
	Timbre(string n = "lambda", unsigned int a = ANNEE_COURANTE, string p = "Suisse", double vf = 1.0) : nom(n), annee(a), pays(p), valeur_faciale(vf) { }
	double vente() const
	{
		if (age() < 5)return valeur_faciale;
		else return 2.5 * valeur_faciale * age();
	}
	unsigned int age()const
	{
		return ANNEE_COURANTE - annee;
	}
	ostream& afficher(ostream& sortie) const
	{
		sortie << " de nom " << nom << " datant de " << annee << " (provenance " << pays << ") ayant pour valeur faciale " << valeur_faciale << " francs";
		return sortie;
	}
};
class Rare : public Timbre
{
private:
	int nb;
	const int PRIX_BASE_TRES_RARE = 600;
	const int PRIX_BASE_RARE = 400;
	const int PRIX_BASE_PEU_RARE = 50;
public:
	Rare(string n = "lambda", unsigned int a = 2014, string p = "Suisse", double vf = 1.0, int nb = 100) : Timbre(n, a, p, vf), nb(nb) {}

	int nb_exemplaires() const
	{
		return nb;
	}
	double vente() const
	{
		if (nb < 100) return PRIX_BASE_TRES_RARE * (age() / 10.0);
		else if (nb >= 100 and nb < 1000) return PRIX_BASE_RARE * (age() / 10.0);
		else return PRIX_BASE_PEU_RARE * (age() / 10.0);
	}
	ostream& afficher(ostream& sortie)const
	{
		Timbre::afficher(sortie);
		return sortie;
	}
};
class Commemoratif : public Timbre
{
public:
	Commemoratif(string n = "lambda", unsigned int a = 2014, string p = "Suisse", double vf = 1.0) : Timbre(n, a, p, vf) {}

	double vente() const
	{
		return 2 * Timbre::vente();
	}
	ostream& afficher(ostream& sortie)const
	{
		Timbre::afficher(sortie);
		return sortie;
	}
};

ostream& operator<<(ostream& sortie, Timbre const& x)
{
	sortie << "Timbre";
	return x.afficher(sortie);
}
ostream& operator<<(ostream& sortie, Rare const& x)
{
	sortie << "Timbre rare (" << x.nb_exemplaires() << " ex.)";
	return x.afficher(sortie);

}
ostream& operator<<(ostream& sortie, Commemoratif const& x)
{
	sortie << "Timbre commémoratif ";
	return x.afficher(sortie);
}

/*******************************************
 * Ne rien modifier après cette ligne.
 *******************************************/
int main()
{
	/* Ordre des arguments :
	*  nom, année d'émission, pays, valeur faciale, nombre d'exemplaires
	*/
	Rare t1("Guarana-4574", 1960, "Mexique", 0.2, 98);
	Rare t2("Yoddle-201", 1916, "Suisse", 0.8, 3);

	/* Ordre des arguments :
	*  nom, année d'émission, pays, valeur faciale, nombre d'exemplaires
	*/
	Commemoratif t3("700eme-501", 2002, "Suisse", 1.5);
	Timbre       t4("Setchuan-302", 2004, "Chine", 0.2);

	/* Nous n'avons pas encore le polymorphisme :-(
	 * (=> pas moyen de faire sans copie ici :-( )  */
	cout << t1 << endl;
	cout << "Prix vente : " << t1.vente() << " francs" << endl;
	cout << t2 << endl;
	cout << "Prix vente : " << t2.vente() << " francs" << endl;
	cout << t3 << endl;
	cout << "Prix vente : " << t3.vente() << " francs" << endl;
	cout << t4 << endl;
	cout << "Prix vente : " << t4.vente() << " francs" << endl;

	return 0;
}

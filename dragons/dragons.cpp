#include <iostream>
#include <string>
#include <cmath>
using namespace std;

int distance(int x, int y)
{
	return abs(x - y);
}

class Creature
{
	/*****************************************************
	 * Compléter le code à partir d'ici
	 *****************************************************/
protected:
	const string nom;
	int niveau, points_de_vie_, force_, position_;
public:
	Creature(const string n, int ni, int p, int f, int po = 0) : nom(n), niveau(ni), points_de_vie_(p), force_(f), position_(po) {}

	bool vivant() const
	{
		if (points_de_vie_ > 0) return true;
		else return false;
	}
	int points_attaque() const
	{
		if (vivant() == true) return niveau * force_;
		else return 0;
	}
	void deplacer(int x)
	{
		position_ += x;
	}
	void adieux() const
	{
		cout << nom << " n'est plus !" << endl;
	}
	int position() const
	{
		return position_;
	}
	void faiblir(int x)
	{
		if (vivant() == true)
		{
			points_de_vie_ -= x;
			if (points_de_vie_ < 0)
			{
				points_de_vie_ = 0;
			}
		}
		if (vivant() == false)
		{
			points_de_vie_ = 0;
			adieux();
		}
	}
	void afficher() const
	{
		cout << nom << ", niveau: " << niveau << ", points de vie: " << points_de_vie_ << ", force: " << force_ << ", points d'attaque: " << points_attaque() << ", position: " << position_ << endl;
	}
};
class Dragon : public Creature
{
private:
	int portee_flamme_;
public:
	Dragon(const string n, int ni, int p, int f, int pf, int po = 0) : portee_flamme_(pf), Creature(n, ni, p, f, po) {}
	void voler(int pos)
	{
		deplacer(pos);
	}
	void souffle_sur(Creature& bete)
	{
		int d = distance(bete.position(), this->position());
		if (bete.vivant() == true and this->vivant() == true)
		{
			if (this->portee_flamme_ >= d)
			{
				bete.faiblir(this->points_attaque());
				this->faiblir(d);
			}
			if (bete.vivant() == false and this->vivant() == true)
			{
				this->niveau++;
			}
		}
	}
};
class Hydre : public Creature
{
private:
	int longueur_cou_, dose_poison_;
public:
	Hydre(const string n, int ni, int p, int f, int lc, int dp, int po = 0) : longueur_cou_(lc), dose_poison_(dp), Creature(n, ni, p, f, po) {}
	void empoisonne(Creature& bete)
	{
		int d = distance(bete.position(), this->position());
		if (bete.vivant() == true and this->vivant() == true)
		{
			if (this->longueur_cou_ >= d)
			{
				bete.faiblir(this->points_attaque() + this->dose_poison_);
			}
			if (bete.vivant() == false and this->vivant() == true)
			{
				this->niveau++;
			}
		}
	}

};
void combat(Dragon& d, Hydre& h)
{
	h.empoisonne(d);
	d.souffle_sur(h);
}
/*******************************************
 * Ne rien modifier après cette ligne.
 *******************************************/
int main()
{
	Dragon dragon("Dragon rouge", 2, 10, 3, 20);
	Hydre  hydre("Hydre maléfique", 2, 10, 1, 10, 1, 42);

	dragon.afficher();
	cout << "se prépare au combat avec :" << endl;
	hydre.afficher();

	cout << endl;
	cout << "1er combat :" << endl;
	cout << "    les créatures ne sont pas à portée, donc ne peuvent pas s'attaquer."
		<< endl;
	combat(dragon, hydre);

	cout << "Après le combat :" << endl;
	dragon.afficher();
	hydre.afficher();

	cout << endl;
	cout << "Le dragon vole à proximité de l'hydre :" << endl;
	dragon.voler(hydre.position() - 1);
	dragon.afficher();

	cout << endl;
	cout << "L'hydre recule d'un pas :" << endl;
	hydre.deplacer(1);
	hydre.afficher();

	cout << endl;
	cout << "2e combat :" << endl;
	cout << "\
  + l'hydre inflige au dragon une attaque de 3 points\n\
      [ niveau (2) * force (1) + poison (1) = 3 ] ;\n\
  + le dragon inflige à l'hydre une attaque de 6 points\n\
      [ niveau (2) * force (3) = 6 ] ;\n\
  + pendant son attaque, le dragon perd 2 points de vie supplémentaires\n\
       [ correspondant à la distance entre le dragon et l'hydre : 43 - 41 = 2 ].\
" << endl;
	combat(dragon, hydre);

	cout << "Après le combat :" << endl;
	dragon.afficher();
	hydre.afficher();

	cout << endl;
	cout << "Le dragon avance d'un pas :" << endl;
	dragon.deplacer(1);
	dragon.afficher();

	cout << endl;
	cout << "3e combat :" << endl;
	cout << "\
  + l'hydre inflige au dragon une attaque de 3 points\n\
      [ niveau (2) * force (1) + poison (1) = 3 ] ;\n\
  + le dragon inflige à l'hydre une attaque de 6 points\n\
      [ niveau (2) * force (3) = 6 ] ;\n\
  + pendant son attaque, le dragon perd 1 point de vie supplémentaire\n\
       [ correspondant à la distance entre le dragon et l'hydre : 43 - 42 = 1 ] ;\n\
  + l'hydre est vaincue et le dragon monte au niveau 3.\
" << endl;
	combat(dragon, hydre);

	cout << "Après le combat :" << endl;
	dragon.afficher();
	hydre.afficher();

	cout << endl;
	cout << "4e Combat :" << endl;
	cout << "    quand une créature est vaincue, rien ne se passe." << endl;
	combat(dragon, hydre);

	cout << "Après le combat :" << endl;
	dragon.afficher();
	hydre.afficher();

	return 0;
}

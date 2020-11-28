#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

/*****************************************************
  * Compléter le code à partir d'ici
 *****************************************************/
class Produit
{
protected:
	string nom, unite;
public:
	Produit(string n, string t = "") : nom(n), unite(t) {}
	~Produit() {}
	string getNom() const
	{
		return nom;
	}
	string getUnite() const
	{
		return unite;
	}
	virtual string toString() const
	{
		return nom;
	}
	virtual const Produit* adapter(double n) const
	{
		return this;
	}
	virtual double quantiteTotale(const string& nomProduit) const
	{
		if (this->getNom() == nomProduit) return 1;
		else return 0;
	}
};

class Ingredient
{
private:
	const Produit& produit;
	double quantite;
public:
	Ingredient(Produit const& p, double q) : produit(p), quantite(q) {}
	~Ingredient() {}
	const Produit& getProduit() const
	{
		return produit;
	}
	double getQuantite() const
	{
		return quantite;
	}
	string descriptionAdaptee() const
	{
		string s = to_string(quantite) + " " + produit.getUnite() + " de " + produit.adapter(quantite)->toString();
		return s;
	}
	double quantiteTotale(const string& nomProduit) const
	{
		return quantite * (produit.quantiteTotale(nomProduit));
	}
};

class Recette
{
private:
	string nom;
	int nbFois_;
	vector<Ingredient*>li;
public:
	Recette(string n, int nb = 1) : nom(n), nbFois_(nb) {}
	~Recette() {}
	void ajouter(const Produit& p, double quantite)
	{
		Ingredient* in = new Ingredient(p, quantite * nbFois_);
		li.push_back(in);
	}
	Recette adapter(double n) const
	{
		Recette r(this->nom, this->nbFois_ * n);
		for (int i = 0; i < li.size(); i++)
		{
			r.ajouter(li[i]->getProduit(), li[i]->getQuantite());
		}
		return r;
	}
	string toString() const
	{
		string s;
		const string q = "\"";
		s = "Recette " + q + nom + q + " x " + to_string(nbFois_) + ":\n";
		for (int i = 0; i < li.size(); ++i)
		{
			if (i == li.size() - 1) s += to_string(i + 1) + ". " + li[i]->descriptionAdaptee();
			else s += to_string(i + 1) + ". " + li[i]->descriptionAdaptee() + "\n";
		}
		return s;
	}
	string getNom() const
	{
		return nom;
	}

	virtual double quantiteTotale(const string& nomProduit) const
	{
		double sum(0);
		for (int i = 0; i < li.size(); i++) sum += li[i]->quantiteTotale(nomProduit);
		return sum;
	}
};

class ProduitCuisine : public Produit
{
private:
	Recette r;

public:
	ProduitCuisine(string n, string t = "portion(s)") : Produit(n, t), r(n) { }
	~ProduitCuisine() {}
	void ajouterARecette(const Produit& produit, double quantite)
	{
		r.ajouter(produit, quantite);
	}
	const ProduitCuisine* adapter(double n) const override
	{
		ProduitCuisine* p(new ProduitCuisine(nom));
		p->r = r.adapter(n);
		return p;
	}
	virtual string toString() const override
	{
		Produit p(this->getNom(), this->getUnite());
		string s = p.toString() + "\n" + r.toString();
		return s;
	}
	virtual double quantiteTotale(const string& nomProduit) const override
	{
		if (this->getNom() == nomProduit) return 1;
		else return r.quantiteTotale(nomProduit);
	}
};
/*******************************************
 * Ne rien modifier après cette ligne.
 *******************************************/
void afficherQuantiteTotale(const Recette& recette, const Produit& produit)
{
	string nom = produit.getNom();
	cout << "Cette recette contient " << recette.quantiteTotale(nom)
		<< " " << produit.getUnite() << " de " << nom << endl;
}

int main()
{
	// quelques produits de base
	Produit oeufs("oeufs");
	Produit farine("farine", "grammes");
	Produit beurre("beurre", "grammes");
	Produit sucreGlace("sucre glace", "grammes");
	Produit chocolatNoir("chocolat noir", "grammes");
	Produit amandesMoulues("amandes moulues", "grammes");
	Produit extraitAmandes("extrait d'amandes", "gouttes");

	ProduitCuisine glacage("glaçage au chocolat");
	// recette pour une portion de glaçage:
	glacage.ajouterARecette(chocolatNoir, 200);
	glacage.ajouterARecette(beurre, 25);
	glacage.ajouterARecette(sucreGlace, 100);
	cout << glacage.toString() << endl;

	ProduitCuisine glacageParfume("glaçage au chocolat parfumé");
	// besoin de 1 portions de glaçage au chocolat et de 2 gouttes
	// d'extrait d'amandes pour 1 portion de glaçage parfumé

	glacageParfume.ajouterARecette(extraitAmandes, 2);
	glacageParfume.ajouterARecette(glacage, 1);
	cout << glacageParfume.toString() << endl;

	Recette recette("tourte glacée au chocolat");
	recette.ajouter(oeufs, 5);
	recette.ajouter(farine, 150);
	recette.ajouter(beurre, 100);
	recette.ajouter(amandesMoulues, 50);
	recette.ajouter(glacageParfume, 2);

	cout << "===  Recette finale  =====" << endl;
	cout << recette.toString() << endl;
	afficherQuantiteTotale(recette, beurre);
	cout << endl;

	// double recette
	Recette doubleRecette = recette.adapter(2);
	cout << "===  Recette finale x 2 ===" << endl;
	cout << doubleRecette.toString() << endl;

	afficherQuantiteTotale(doubleRecette, beurre);
	afficherQuantiteTotale(doubleRecette, oeufs);
	afficherQuantiteTotale(doubleRecette, extraitAmandes);
	afficherQuantiteTotale(doubleRecette, glacage);
	cout << endl;

	cout << "===========================\n" << endl;
	cout << "Vérification que le glaçage n'a pas été modifié :\n";
	cout << glacage.toString() << endl;

	return 0;
}
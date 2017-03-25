#include <stdio.h>
#include <iostream>
#include <fstream>
#include <math.h>
#include <vector>
#include <queue>
using namespace std;


class zadanie {
public:
	int r; // czas dostêpnoœci
	int p; // czas wykonania
	int q; //czas dostarczenia

};


struct PorownajWgQ
{
	bool operator ()(const zadanie & zad1, const zadanie & zad2)
	{
		//wg q malejaco
		if (zad1.q < zad2.q) return true;

		if (zad1.q > zad2.q) return false;

		return false;
	}
};


priority_queue < zadanie, std::vector < zadanie >, PorownajWgQ > G2; //kolejka zadan gotowych

int n = 0; //liczba zadan

vector <zadanie> U; //lista niegotowych
zadanie obr; //do obrobki
int C = 0;


void wczytaj(string nazwa) {
	fstream plik;
	zadanie tym;
	plik.open(nazwa, ios::in);
	if (plik.good() == true) {

		plik >> n;


		for (int i = 0; i < n; i++) {
			plik >> tym.r >> tym.p >> tym.q;

			U.push_back(tym);
		}
	}
	plik.close();
}

vector <zadanie> sortowanie(vector <zadanie> V) {

	zadanie a;
	cout << V.size();
	for (int j = 0; j < n; j++) {
		for (int k = 0; k < n - 1; k++) {
			if (V[k].r > V[k + 1].r) {
				a = V[k];
				V[k] = V[k + 1];
				V[k + 1] = a;
			}
		}
	}
	return V;
}


int main() {

	int t = 0;

	string nazwa = "SCHRAGE3.DAT";

	wczytaj(nazwa);

	U = sortowanie(U);

	t = U[0].r;

	while (!G2.empty() || !U.empty() ) {

		cout << "START PETLI" << endl;

		int wyjscie = 1;
		if (!U.empty()) {

			if (U[0].r <= t)
				wyjscie = 0;
		}

		while (!wyjscie) {   //kopiowanie gotowych zadañ do wektora G

			G2.push(U[0]);

			U.erase(U.begin());

			if (U.empty()) {
				wyjscie = 1;
			}
			else {
				if (U[0].r > t)
					wyjscie = 1;
			}
		}


		if (!G2.empty()) {

			obr = G2.top();
			G2.pop();

			int tym = obr.p;
			if (!U.empty()) {
				if (U[0].q > obr.q) {
					obr.p = t - U[0].r;
				}
			}
//NIE DO KONCA Z ALGORYTMEM
			//MOZE POWODOWAC BLEDY
			t = t + obr.p;

			cout << C << " " << t << " " << obr.q << " " << obr.p << endl;

			if(obr.p > 0 && obr.p != tym)
				G2.push(obr);
			
		}
		else {
			t = U[0].r;
		}
		C = fmax(C, t + obr.q);
	}

	cout << endl << "CA£KOWITY CZAS: " << C << endl;

	while (true);
}
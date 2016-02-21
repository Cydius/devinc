// ====================================================================
// Filename: 7.2.cpp
//
// Description: Programmierung in C++ 1, Blatt 8, Aufgabe 8.1
// Rekursive Pinsette
//
// Created: 20.01.2015
// Author: Matth�us Oczadly, oczadly@online.de
//
// ====================================================================
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <iomanip>

using namespace std;

// Konstaten und Typdefinitionen
const int N = 1000;
typedef unsigned char Pixel;
typedef unsigned int uint;

// Strukturen
struct Bild {
		unsigned char fileformat[2];
		uint bBreite;
		uint bHoehe;
		uint maxGrey;
		Pixel pixel[N][N];
};

// Prototypen
void
glaetten ( Pixel bild1[N][N], Pixel bild2[N][N], int nz, int ns );
void
invertieren ( Pixel bild1[N][N], Pixel bild2[N][N], int nz, int ns, int graumax );
void
kantenbildung ( Pixel bild1[N][N], Pixel bild2[N][N], int nz, int ns );
void
schaerfen ( Pixel bild1[N][N], Pixel bild2[N][N], int nz, int ns, int graumax );
Bild
ladeBild ( string datei );
void
schreibeDatei ( Bild *b1, string zielDatei );
void
kopiereMeta ( Bild *b1, Bild *b2 );
void
fill ( Pixel bild[N][N], int nz, int ns, int inz, int ins, Pixel oldval, Pixel newval );

// HPG
int
main () {
	string inFile = "kunst.pgm";
	Bild original = ladeBild (inFile);
	Bild bearbeitet;
// Zieldateien
	string invFile = "invertiert.pgm";
	string glattFile = "gleattung.pgm";
	string kantFile = "kanten.pgm";
	string scharfFile = "scharf.pgm";
	string fillFile = "fill.pgm";
	char mEingabe; // Men�eingabe

	kopiereMeta (&original, &bearbeitet);

	do{
		switch(mEingabe){
			case 'f':
				fill (original.pixel, original.bHoehe, original.bBreite, 10, 10, 255, 127);
				schreibeDatei (&original, fillFile);
			break;

			case 'g':
				glaetten (original.pixel, bearbeitet.pixel, original.bBreite,
								original.bHoehe);
				schreibeDatei (&bearbeitet, glattFile);
				cout << "Gl�tten abgeschlossen! Datei: " << glattFile << endl << endl;
			break;

			case 'i':
				invertieren (original.pixel, bearbeitet.pixel, original.bBreite,
									original.bHoehe, original.maxGrey);
				schreibeDatei (&bearbeitet, invFile);
				cout << "Invertieren abgeschlossen! Datei: " << invFile << endl << endl;
			break;

			case 'k':
				kantenbildung (original.pixel, bearbeitet.pixel, original.bBreite,
									original.bHoehe);
				schreibeDatei (&bearbeitet, kantFile);
				cout << "Katenbildung abgeschlossen! Datei: " << kantFile << endl << endl;
			break;

			case 's':
				schaerfen (original.pixel, bearbeitet.pixel, original.bBreite,
								original.bHoehe, original.maxGrey);
				schreibeDatei (&bearbeitet, scharfFile);
				cout << "Schaerfen abgeschlossen! Datei: " << scharfFile << endl << endl;
			break;

			default:
				cout << "f Fuellen" << endl;
				cout << "g Glaettung" << endl;
				cout << "i Invertieren" << endl;
				cout << "k Kantenbildung" << endl;
				cout << "s Schaerfen" << endl;
				cout << "e Ende" << endl;
			break;
		}

	}
	while((mEingabe = cin.get ()) != 'e');

	return 0;
}

Bild
ladeBild ( string datei ) {
	Bild b1;
	unsigned char charOut;
	uint i = 0;
	ifstream ifs;
	uint numberOut;

// Datei Laden
	ifs.open (datei.c_str ());
	if(!ifs){
		cerr << "Failed to open input file" << endl;
		exit (1);
	}

// Erste Zeile Abfangen
	while((charOut = ifs.get ()) != EOF and i <= 1){
		b1.fileformat[i] = charOut;
		i++;
	}

// Pr�fe ob Dateiformat korrekt
	if(b1.fileformat[0] != 'P' or b1.fileformat[1] != '2'){
		cout << "Falscher Dateityp." << endl;
		exit (1);
	}
	else{
//cout << "Dateityp ist: " << b1.fileformat[0] << b1.fileformat[1] << endl;
	}

// Bildbreite und Bildh�he Pr�fen
	while(i <= 4 and ifs >> numberOut){
		if(i == 2 and numberOut > N){
			cerr << "Bildbreite zu gro�" << endl;
			ifs.close ();
			exit (1);
		}
		else{
			if(i == 2)
				b1.bBreite = numberOut;
		}
		if(i == 3 and numberOut > N){
			cerr << "Bildhoehe zu gro�" << endl;
			ifs.close ();
			exit (1);
		}
		else{
			if(i == 3)
				b1.bHoehe = numberOut;
		}
		if(i == 4)
			b1.maxGrey = numberOut;
		i++;
	}

	unsigned int x, y;

	x = y = 0;
	while(ifs >> numberOut){
		if(numberOut <= 255){
			b1.pixel[x][y] = numberOut;
			x++;
			if(x == b1.bBreite){
				x = 0;
				y++;
			}
		}
		else{
			cerr << "Falschen Grauwert gefunden. Beende Programm";
			ifs.close ();
			exit (1);
		}
	}
	ifs.close ();

	return b1;
}

void
schreibeDatei ( Bild *b1, string zielDatei ) {
	string outFile = zielDatei;
	ofstream ofs;

	ofs.open (outFile.c_str ());
	if(!ofs){
		cerr << "Failed to open output file" << endl;
		exit (1);
	}

	ofs << (*b1).fileformat[0] << (*b1).fileformat[1] << endl;
	ofs << (*b1).bBreite << " " << (*b1).bHoehe << endl;
	ofs << (*b1).maxGrey << endl;

	for(uint i = 0; i < (*b1).bHoehe; i++){
		for(uint j = 0; j < (*b1).bBreite; j++){
			ofs << setw (4) << (int) (*b1).pixel[j][i];
		}
		ofs << endl;
	}

	ofs.close ();
}

void
kopiereMeta ( Bild *b1, Bild *b2 ) {
	(*b2).fileformat[0] = (*b1).fileformat[0];
	(*b2).fileformat[1] = (*b1).fileformat[1];
	(*b2).bBreite = (*b1).bBreite;
	(*b2).bHoehe = (*b1).bHoehe;
	(*b2).maxGrey = (*b1).maxGrey;
}

void
glaetten ( Pixel bild1[N][N], Pixel bild2[N][N], int nz, int ns ) {
	for(int i = 0; i < nz; i++){
		for(int j = 0; j < ns; j++){
			if(i >= 1 and i <= nz - 2 and j >= 1 and j <= ns - 2){
				bild2[i][j] = (bild1[i - 1][j - 1] + bild1[i][j - 1] + bild1[i + 1][j - 1]
						+ bild1[i - 1][j] + bild1[i][j] + bild1[i + 1][j] + bild1[i - 1][j + 1]
						+ bild1[i][j + 1] + bild1[i + 1][j + 1]) / 9;
			}
			else{
				bild2[i][j] = bild1[i][j];
			}
		}
	}
}

void
invertieren ( Pixel bild1[N][N], Pixel bild2[N][N], int nz, int ns, int graumax ) {
	for(int i = 0; i < nz; i++){
		for(int j = 0; j < ns; j++){
			bild2[i][j] = graumax - bild1[i][j];
		}
	}
}

void
kantenbildung ( Pixel bild1[N][N], Pixel bild2[N][N], int nz, int ns ) {
	for(int i = 0; i < nz; i++){
		for(int j = 0; j < ns; j++){
			if(i >= 1 and i <= nz - 2 and j >= 1 and j <= ns - 2){
				bild2[i][j] = abs (
						((4 * (bild1[i][j])) - bild1[i][j - 1] - bild1[i - 1][j]
								- bild1[i + 1][j] - bild1[i][j + 1]) / 9);
			}
			else{
				bild2[i][j] = bild1[i][j];
			}
		}
	}
}

void
schaerfen ( Pixel bild1[N][N], Pixel bild2[N][N], int nz, int ns, int graumax ) {
	int scharf = 0;
	for(int i = 0; i < nz; i++){
		for(int j = 0; j < ns; j++){
			if(i >= 1 and i <= nz - 2 and j >= 1 and j <= ns - 2){
				scharf = -bild1[i - 1][j - 1] - bild1[i][j - 1] - bild1[i + 1][j - 1]
						- bild1[i - 1][j] + 9 * bild1[i][j] - bild1[i + 1][j]
						- bild1[i - 1][j + 1] - bild1[i][j + 1] - bild1[i + 1][j + 1];
				if(scharf > graumax)
					scharf = graumax;
				else if(scharf < 0)
					scharf = 0;
				bild2[i][j] = scharf;
			}
			else{
				bild2[i][j] = bild1[i][j];
			}
		}
	}
}

void
fill ( Pixel bild[N][N], int nz, int ns, int inz, int ins, Pixel oldval, Pixel newval ) {

// Bevor umliegende Pixel geprüft werden, muss der aktuelle Pixel angepasst werden,
// damit doppelte Prüfungen vermieden werden
	bild[inz][ins] = newval;

// oberhalb des aktuellen Pixels
	if(inz >= 1){
		if(bild[inz - 1][ins] == oldval){
			fill (bild, nz, ns, inz - 1, ins, oldval, newval);
		}
	}

// links vom aktuellen Pixel
	if(ins >= 1){
		if(bild[inz][ins - 1] == oldval){
			fill (bild, nz, ns, inz, ins - 1, oldval, newval);
		}
	}

// unterhalb des aktuellen Pixel
	if(inz < nz){
		if(bild[inz + 1][ins] == oldval){
			fill (bild, nz, ns, inz + 1, ins, oldval, newval);
		}
	}

// rechts vom aktuellen Pixel
	if(ins < ns){
		if(bild[inz][ins + 1] == oldval){
			fill (bild, nz, ns, inz, ins + 1, oldval, newval);
		}
	}

}

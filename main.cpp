#include <iostream>
#include <string>
#include <vector>
#include <fstream> 
#include <iostream> 
#include <sstream> 
	
using namespace std;

struct bestellungTyp{
	string name;
	float preis;
	int anz;
};

void einlesen(vector <bestellungTyp> &bestellungV);
void berechnen(vector <bestellungTyp> &bestellungV);
void laden(vector <bestellungTyp> &bestellungV);
void speichern(vector <bestellungTyp> &bestellungV);
void andern(vector<bestellungTyp> &bestellungV);
void bestandEin(vector <bestellungTyp> &bestandV);		
void bestandAus(vector <bestellungTyp> &bestandV);
void bestandAndern(bestellungTyp bestandS, vector <bestellungTyp> &bestandV);


vector <bestellungTyp> bestandV;		


int main(int argc, char** argv) {
	
	int eingabe;
	bool weiter=1;
	vector <bestellungTyp> bestellungV;
	vector <bestellungTyp> buffer;
	
	
	bestandEin(bestandV);		
	int * p = &eingabe;
	
	do{
		
		cout << "1. Bestellung eingeben"<<endl<<"2. Gesammtsumme errechnen"<< endl << "3. Bestellung laden"<< endl<<"4. Bestellung andern"<< endl <<  "5. Speichern" <<endl<< "6. Beenden"<< endl;
		
		cin >>eingabe;
	
		switch(eingabe) {
			case 1:
				system("cls");
				einlesen(bestellungV);
				break;
			case 2:
				system("cls");
				berechnen(bestellungV);
				break;
			case 3:
				system("cls");
				laden(bestellungV);
				break;
			case 4:
				system("cls");
				andern(bestellungV);
				break;
				system("cls");
			case 5:
				system("cls");
				speichern(bestellungV);
				bestandAus(bestandV);	
				break;
			case 6:
				system("cls");
				cout<< "Speichern? y/n"<<endl;
				cin >> eingabe;
				if (eingabe =='y'){
					speichern(bestellungV);
					bestandAus(bestandV);
					weiter=0;
				}
				else{
					weiter=0;
				}
				break;
	}	
	
	}while(weiter);
	
	return 0;
}

	// Bestellung einlesen (Artikel, Preis, Anzahl)
void einlesen(vector <bestellungTyp> &bestellungV){
	vector <bestellungTyp> test{1};
	char weiter= 'n';
	
	do{
		system("cls");
		cout << "Artikel: ";
		cin >> test.at(0).name;
		cout << "Preis: ";
		cin >> test.at(0).preis;
		cout << "Anzahl: ";
		cin >> test.at(0).anz;
		bestellungV.push_back(test.at(0));
	
		cout << endl<< "Weiter einlesen? y/n  ";
		cin >>weiter;
	
	}while(weiter == 'y');
	system("cls");

}

	// Berechnung des Preises
void berechnen(vector <bestellungTyp> &bestellungV){
	int gesammt= 0;
	
	for (int i =0; i<bestellungV.size();i++){
		gesammt+=bestellungV.at(i).preis*bestellungV.at(i).anz;
		
	}
	cout << "Es kostet: "<< gesammt<< " €"<<endl<<endl; 
}

	// Eine bereits vorhandene Bestellung Laden (Name)
void laden(vector <bestellungTyp> &bestellungV){
	string name;
	string zeile;
	
	
	cout << "Nutzername: ";
	cin >> name;
	
	ifstream textD(name+".txt");
	if(!textD){
		cout<< "Dateifehler"<<endl;
		
	}
	bestellungV.erase(bestellungV.begin(),bestellungV.end());
	
	while(getline(textD,zeile)){
		string::iterator i;
		bestellungTyp bufferV;
		string bufferS="";
		int tokenNr=0;
		bool zahlenWeg=0;
		
		for(i = zeile.begin();i!= zeile.end();i++){
			if (*i==' '){
				zahlenWeg=1;
			}
			if (zahlenWeg==1){
				if(*i!= ';'){
				bufferS+=*i;					
				}
				else{
					switch (tokenNr){
						case 0:
							bufferV.name=bufferS;
							tokenNr++;
							bufferS="";
							break;
						case 1:
							bufferV.preis=stof(bufferS);
							tokenNr++;
							bufferS="";
							break;
						case 2:
							bufferV.anz=stoi(bufferS);
							break;
					}
				}
			}
		}
	
	bestellungV.push_back(bufferV);
	}
system("cls");
}
	// Eine Bestellung Speichern unter (Name.txt)
void speichern(vector <bestellungTyp> &bestellungV){
	
	string name;
	cout << "Name eingeben: ";
	cin >> name;
	
	
	ofstream textD(name+".txt");
	if(!textD){
		cout << endl<< "Dateifehler"<< endl;
	}
	
	for(int i=0 ;i!=bestellungV.size();i++){
		textD<<i+1 <<": "<<bestellungV.at(i).name<<";"<< bestellungV.at(i).preis<<";"<<bestellungV.at(i).anz<<";"<<endl;
		
	}
	
}
	// Bestellung ändern
void andern(vector<bestellungTyp> &bestellungV){
	system("cls");
	int stelle;
	
	
	cout <<"Stelle zum andern eingeben: ";
	cin >> stelle;
	stelle --;
	cout << endl<< "Artikel: ";
	cin >> bestellungV.at(stelle).name;
	cout << endl<< "Preis: ";
	cin >> bestellungV.at(stelle).preis;
	cout << endl<< "Anzahl: ";
	cin >> bestellungV.at(stelle).anz;
	
}

	// Den Bestand einlesen falls vorhanden													
void bestandEin(vector <bestellungTyp> &bestandV){
	string zeile;
	
	ifstream textD("Bestand.txt");
	if(!textD){
		cout<< "Dateifehler Bestand ein"<<endl;
		
	}
	bestandV.erase(bestandV.begin(),bestandV.end());
	
	while(getline(textD,zeile)){
		string::iterator i;
		bestellungTyp bufferV;
		string bufferS="";
		int tokenNr=0;
		bool zahlenWeg=0;
		
		for(i = zeile.begin();i!= zeile.end();i++){
			if(*i!= ';'){
			bufferS+=*i;					
			}
			else{
				switch (tokenNr){
					case 0:
						bufferV.name=bufferS;
						tokenNr++;
						bufferS="";
						break;
					case 1:
						bufferV.preis=stof(bufferS);							tokenNr++;
						bufferS="";
						break;
					case 2:
						bufferV.anz=stoi(bufferS);
						break;
					
				}
			}
		}
	bestandV.push_back(bufferV);
			
	}
}

	// Bestand Speichern
void bestandAus(vector <bestellungTyp> &bestandV){
	
	ofstream textD("Bestand.txt");
	if(!textD){
		cout << endl<< "Dateifehler Bestand aus"<< endl;
	}
	
	for(int i=0 ;i!=bestandV.size();i++){
		textD<<bestandV.at(i).name<<";"<< bestandV.at(i).preis<<";"<<bestandV.at(i).anz<<";"<<endl;
		
	}
}

	// Bestand ändern
void bestandAndern(bestellungTyp bestandS, vector <bestellungTyp> &bestandV){
	int stelle;
	char zeichen;
	
	if (bestandS.preis== 0){
		zeichen = '-';
	}
	if (bestandS.preis==1){ 
		zeichen = '+';
	}
	for (int i= 0; bestandS.name == bestandV.at(i).name;i++){
		stelle= i;
	}
	bestandV.at(stelle).anz-= bestandS.anz;
	
}


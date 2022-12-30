//****************************************************************
//             LISTA E DIREKTIVAVE TE PROJEKTIT
//****************************************************************
#include <iostream>
#include <fstream>
#include <cctype>
#include <iomanip>
using namespace std;

//****************************************************************
//               KLASA E PERDORUR NE PROJEKT
//****************************************************************

class llogaria
{
	int llog_nr;
	char emri[50];
	int depozitim;
	char tipi;
public:
	void krijo_llogari();		// funksioni qe krijon llogari te reja
	void shfaq_llogari() const;	// funksioni qe shfaq te dhenat e llogarive
	void modifiko();			// funksioni qe shton detaje te reja te llogarive
	void depozito(int);			// funksion qe pranon shuma per ti shtuar ne shumen e balances
	void terhiq(int);			// funksion qe pranon shuma per ti zbritur nga shuma e balances
	void raporto() const;		// funksion qe shfaq te dhenat ne format tabelor
	int ktheNrLlog() const;		// funksion qe kthen numrin e llogarise
	int ktheDepozite() const;	// funksion qe kthen balancen e depozites
	char ktheTip() const;		// funksion qe kthen tipin e llogarise
};         				// fundi i klases llogaria

void llogaria::krijo_llogari ()
{
	cout << "\nFutni Nr. e llogarise : ";
	 cin >> llog_nr;
	cout << "\n\nFutni Emrin e mbajtesit te llogarise : ";
	cin.ignore();
	cin.getline(emri,50);
	cout << "\nFutni tipin e llogarise (K/R) : ";  // K - Llogari kursimi dhe R - Llogari rrjedhese
	cin >> tipi;
	tipi=toupper(tipi);
	cout << "\nFutni shumen fillestare(>=500 per llog kursimi >=1000 per llog rrjedhes ) : ";
	 cin >> depozitim;
	cout << "\n\n\nLlogaria u krijua...";
}

void llogaria :: shfaq_llogari () const
{
	cout << "\n Nr. i Llogarise : " << llog_nr;
	cout << "\n Emri i mbajtesit te llogarise : " << emri;
	cout << "\n Tipi i llogarise : " << tipi;
	cout << "\n Shuma e Balances : " << depozitim;
}


void llogaria :: modifiko ()
{
	cout << "\nNr. i Llogarise : " << llog_nr;
	cout << "\nModifiko Emrin e mbajtesit te llogarise : ";
	cin.ignore();
	cin.getline(emri,50);
	cout << "\nModifiko tipin e llogarise : ";
	 cin >> tipi;
	tipi=toupper(tipi);
	cout << "\nModifiko shumen e Balances : ";
	 cin >> depozitim;
}

	
void llogaria :: depozito (int x)
{
	depozitim += x;
}
	
void llogaria :: terhiq (int x)
{
	depozitim -= x;
}
	
void llogaria :: raporto () const
{
	cout << llog_nr << setw(10) << " " << emri << setw(10) << " " << tipi << setw(6) << depozitim << endl;
}
	
int llogaria :: ktheNrLlog () const
{
	return llog_nr;
}

int llogaria :: ktheDepozite () const
{
	return depozitim;
}

char llogaria :: ktheTip() const
{
	return tipi;
}

//****************************************************************
//    	         Deklarimi i funksioneve
//****************************************************************
void shkruaj_llogari();			// funksion qe shkruan regjistrimet ne skedarin binar dat
void shfaq_llog(int);			// funksion qe shfaq detajet e llogarise se dhene nga perdoruesi
void modifiko_llogari(int);		// funksion qe modifikon regjistrimet e skedarit
void fshij_llogari(int);		// funksion per fshirjen e nje llogarie
void shfaq_teGjitha();			// funksion qe paraqet detajet e llogarive
void depozito_terhiq(int, int); // funksion per depozitim/terheqje te hollash nga llogaria
void prezanto();				// funksion prezantues ne ekran

//****************************************************************
//    	       FUNKSIONI KRYESOR I PROGRAMIT
//****************************************************************

int main()
{
	char opsion;
	int num;
	prezanto();
	do
	{
		system("cls");
		cout << "\n\n\n\t MENUJA KRYESORE";
		cout << "\n\n\t 1. LLOGARI E RE";
		cout << "\n\n\t 2. DEPOZITIM";
		cout << "\n\n\t 3. TERHEQJE";
		cout << "\n\n\t 4. KERKO BALANCEN";
		cout << "\n\n\t 5. LISTA E LLOGARIVE";
		cout << "\n\n\t 6. MBYLL NJE LLOGARI";
		cout << "\n\n\t 7. MODIFIKO NJE LLOGARI";
		cout << "\n\n\t 8. DIL";
		cout << "\n\n\t Zgjidh nje nga opsionet (1-8) ";
		 cin >> opsion;
		system ("cls");
		switch (opsion)
			{
				case '1': shkruaj_llogari(); break;
				case '2': cout << "\n\n\t Futni Nr. e llogarise : "; cin >> num; depozito_terhiq (num, 1); break;
				case '3': cout << "\n\n\t Futni Nr. e llogarise : "; cin >> num; depozito_terhiq (num, 2); break;
				case '4': cout << "\n\n\t Futni Nr. e llogarise : "; cin >> num; shfaq_llog (num);         break;
				case '5': shfaq_teGjitha(); 	                                                           break;
				case '6': cout << "\n\n\t Futni Nr. e llogarise : "; cin >> num; fshij_llogari (num); 	   break;
				case '7': cout << "\n\n\tFutni Nr. e llogarise : ";  cin >> num; modifiko_llogari (num);   break;
				case '8': cout<<"\n\n\tFaleminderit qe perdoret SMB-ne";                                   break;
				default :cout<<"\a";
			}
		cin.ignore();
		cin.get();
    } while (opsion != '8');
	return 0;
}

//****************************************************************
//    	Funksion qe shkruan ne skedar
//****************************************************************

void shkruaj_llogari()
{
	llogaria ac;
	ofstream outFile;
	outFile.open("llogaria.dat",ios::binary|ios::app);
	ac.krijo_llogari();
	outFile.write(reinterpret_cast<char *> (&ac), sizeof(llogaria));
	outFile.close();
}

//****************************************************************
//    	Funksion qe lexon regjistrimet specifike nga skedari
//****************************************************************

void shfaq_llog(int n)
{
	llogaria ac;
	bool flag=false;
	ifstream inFile;
	inFile.open("llogaria.dat",ios::binary);
	if(!inFile)
	{
		cout << "Skedari nuk mund te hapet !! Shtyp nje buton...";
		return;
	}
	cout << "\nDETAJET E BALANCES\n";
    	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(llogaria)))
	{
		if(ac.ktheNrLlog()==n)
		{
			ac.shfaq_llogari();
			flag=true;
		}
	}
    inFile.close();
	if(flag==false)
		cout << "\n\n Ky numer llogarie nuk ekziston!!!";
}

//****************************************************************
//    	Funksion qe modifikon regjistrimet ne skedar
//****************************************************************

void modifiko_llogari(int n)
{
	bool found=false;
	llogaria ac;
	fstream File;
    File.open("llogaria.dat",ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"Skedari nuk mund te hapet !! Shtyp nje buton...";
		return;
	}
	while(!File.eof() && found==false)
	{
		File.read(reinterpret_cast<char *> (&ac), sizeof(llogaria));
		if(ac.ktheNrLlog()==n)
		{
			ac.shfaq_llogari();
			cout<<"\n\nFutni detajet e reja te llogarise " << endl;
			ac.modifiko();
			int pos=(-1)*static_cast<int>(sizeof(llogaria));
			File.seekp(pos,ios::cur);
		    File.write(reinterpret_cast < char * > (&ac), sizeof(llogaria));
		    cout << "\n\n\t Regjistrimi u perditesua";
		    found=true;
		  }
	}
	File.close();
	if(found==false)
		cout << "\n\n Regjistrimi nuk u gjet ";
}

//****************************************************************
//    	function to delete record of file
//****************************************************************


void fshij_llogari(int n)
{
	llogaria ac;
	ifstream inFile;
	ofstream outFile;
	inFile.open("llogaria.dat",ios::binary);
	if(!inFile)
	{
		cout << "Skedari nuk mund te hapet !! Shtyp nje buton...";
		return;
	}
	outFile.open("Temp.dat",ios::binary);
	inFile.seekg(0,ios::beg);
	while(inFile.read(reinterpret_cast < char *> (&ac), sizeof(llogaria)))
	{
		if(ac.ktheNrLlog()!=n)
		{
			outFile.write(reinterpret_cast < char *> (&ac), sizeof(llogaria));
		}
	}
    inFile.close();
	outFile.close();
	remove("llogaria.dat");
	rename("Temp.dat","llogaria.dat");
	cout << "\n\n\t Regjistrimi u fshi..";
}

//****************************************************************
//      	Funksioni qe shfaq listen e llogarive
//****************************************************************

void shfaq_teGjitha()
{
	llogaria ac;
	ifstream inFile;
	inFile.open("llogaria.dat",ios::binary);
	if(!inFile)
	{
		cout<<"Skedari nuk mund te hapet !! Shtyp nje buton...";
		return;
	}
	cout << "\n\n\t\tLISTA E MBAJTESVE TE LLOGARIVE\n\n";
	cout << "====================================================\n";
	cout << "Llog nr.      EMRI          Tipi  Balanca\n";
	cout << "====================================================\n";
	while(inFile.read(reinterpret_cast < char *> (&ac), sizeof(llogaria)))
	{
		ac.raporto();
	}
	inFile.close();
}

//****************************************************************
//    	Funksion per depozitimet dhe terheqjet e shumave
//****************************************************************

void depozito_terhiq(int n, int option)
{
	int amt; // amt eshte vlera monetare qe do te depozitohet ose terhiqet
	bool found=false;
	llogaria ac;
	fstream File;
    File.open("llogaria.dat", ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"Skedari nuk mund te hapet !! Shtyp nje buton...";
		return;
	}
	while(!File.eof() && found==false)
	{
		File.read(reinterpret_cast<char *> (&ac), sizeof(llogaria));
		if(ac.ktheNrLlog()==n)
		{
			ac.shfaq_llogari();
			if(option==1)
			{ 
				cout << "\n\n\tPER DEPOZITIM ";
				cout << "\n\nFutni shumen per depozitim : ";
				 cin >> amt;
				ac.depozito(amt);
			}
		    if(option==2)
			{
				cout << "\n\n\tPER TERHEQJE ";
				cout << "\n\nFutni shumen per terheqje : ";
				 cin >> amt;
				int bal = ac.ktheDepozite()-amt;
				if((bal<500 && ac.ktheTip()=='K') || (bal<1000 && ac.ktheTip()=='R'))
					cout << "Balance e pamjaftueshme";
				else
					ac.terhiq(amt);
		      }
			int pos=(-1)*static_cast<int>(sizeof(ac));
			File.seekp(pos,ios::cur);
			File.write(reinterpret_cast<char *> (&ac), sizeof(llogaria));
			cout << "\n\n\t Regjistrimi u perditesua";
			found=true;
	       }
         }
    File.close();
	if(found==false)
		cout << "\n\n Regjistrimi nuk u gjet ";
}

//****************************************************************
//    	       FUNKSIONI PREZANTUES
//****************************************************************

void prezanto()
{
	cout << "\n\n\n\t  SISTEMI";
	cout << "\n\n\t MENAXHIMIT";
	cout << "\n\n\t  BANKAR";
	cout << "\n\n\n\n KODUES : Ilirjan Rexho";
	cout << "\n\n SHKOLLA : Jopublike Nr1 Vlore";
	cin.get();
}

//***************************************************************
//    			FUNDI I PROJEKTIT
//***************************************************************

	/************************************************************************
	* 				Title: Sistem Menaxhimi i Studenteve      				*
	* 				Autori: Ilirjan Rexho	                      				*
	* 				IDE: Dev C++ 5.11                         				*
	* 				Data: 09-02-2018                          				*
	*************************************************************************/
#include <conio.h>
#include <string.h>
#include <iostream>
#include <iomanip>
#include <limits>
#include <windows.h>
using namespace std;

bool kontrollo(string);			// kontrollon vargjet nese jane ne segmentin 48-57 te kodeve ASCII
bool kontrollo_alfabet(string); // kontrollon karakteret e vargjeve nese jane ne segmentin 65-122 te kodeve ASCII

struct nyja            // krijimi i struktures se te dhenave
{
	string emri,       // ruan emrin e studentit ne liste
		   mbiemri,    // ruan mbiemrin e studentit ne liste
		   dtl,        // ruan datelindjen e studentit ne liste
		   adresa,     // ruan adresen e studentit ne liste
		   amza;       // ruan amzen e studentit ne liste
	   int ID;		   // ruan ID-ne e studentit ne liste
	 float mes;		   // ruan mesataren e studentit ne liste
	 nyja *tjetri;	   // regjistrimi pasardhes
	 nyja *para_ardhes;// regjistrimi paraardhes
};
class list  		   // krijimi i listes se te dhenave
{
private:
	int numero;        // numeratori i regjistrimeve
    nyja *kreu,*fundi; // shenjat e sinoreve ( fillimi dhe fundi) te struktures
public:
	list()
		{
			kreu=fundi=NULL;
			numero=0;
		}
		bool eshteBosh()// kontrollon nese permbajtja e kreut eshte bosh
		{
			if(kreu == NULL)
				{
					return true;
				}
				else 
					return false;
		}
	void spostim_xy(int x, int y)  	// funksioni i spostimit koordinativ
		{
			COORD koordinata;
			koordinata.X = x;
			koordinata.Y = y;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), koordinata);
		}		
	void shto_data(int n)   		// funksioni i shtimit te te dhenave
	{
		int gp=0;
		spostim_xy(2,2);	
		Siper_horizontal();
		spostim_xy(2,3);
		Line();
		spostim_xy(77,3);
		Line();
		spostim_xy(2,4);
		Poshte_horizontal();
		// Spostime dhe vijezime
		spostim_xy(2,5);	
		Siper_horizontal();
		spostim_xy(2,6);
		Line();
		spostim_xy(77,6);
		Line();
		spostim_xy(2,7);
		Poshte_horizontal();
		// Spostime dhe vijezime
		spostim_xy(2,8);	
		Siper_horizontal();
		spostim_xy(2,9);
		Line();
		spostim_xy(77,9);
		Line();	
		spostim_xy(2,10);
		Poshte_horizontal();
		// Spostime dhe vijezime
		spostim_xy(2,11);	
		Siper_horizontal();
		spostim_xy(2,12);
		Line();
		spostim_xy(77,12);
		Line();
		spostim_xy(2,13);
		Poshte_horizontal();
		// Spostime dhe vijezime
		spostim_xy(2,14);	
		Siper_horizontal();
		spostim_xy(2,15);
		Line();
		spostim_xy(77,15);
		Line();
		spostim_xy(2,16);
		Poshte_horizontal();
		// Spostime dhe vijezime
		spostim_xy(2,17);	
		Siper_horizontal();
		spostim_xy(2,18);
		Line();
		spostim_xy(77,18);
		Line();
		spostim_xy(2,19);
		Poshte_horizontal();
		// Fillon hedhja e te dhenave te Studentit
		nyja *temp=new nyja;
		temp->ID=n;
		spostim_xy(23,3);
		cout<<"Emri i Studentit: ";
		cin>>temp->emri;
		if(eshteBosh())
		{
			goto z;
		}
		else
		{
			while(fundi->emri==temp->emri)
			{
				spostim_xy(43,3);
				cout<<"                     	  ";
				spostim_xy(43,3);
				cin>>temp->emri;
			}
		}
		z:
		while(kontrollo(temp->emri)==false)
		{
			spostim_xy(43,3);
			cout<<"                     	  ";
			spostim_xy(43,3);
			cin>>temp->emri;
		}
			spostim_xy(23,6);
			cout<<"Mbiemri i Studentit: ";
			cin>>temp->mbiemri;
			if(eshteBosh())
		{
			goto y;
		}
		else
		{
			while(fundi->mbiemri==temp->mbiemri)
			{
				spostim_xy(50,6);
				cout<<"                     ";
				spostim_xy(50,6);
				cin>>temp->mbiemri;
			}
		}
		y:
		while(kontrollo(temp->mbiemri)==false)
		{
			spostim_xy(50,6);
			cout<<"                     ";
			spostim_xy(50,6);
			cin>>temp->mbiemri;
		}
			spostim_xy(23,9);
			cout<<"Amza e Studentit: ";
			cin>>temp->amza;
			if(eshteBosh())
			{
				goto a;
			}
			else
			{
				while(fundi->amza==temp->amza)
					{
						spostim_xy(46,9);
						cout<<"                  	 "<<endl;
						spostim_xy(46,9);
						cin>>temp->amza;
					}
			}
		a:
		while(kontrollo_alfabet(temp->amza) == false)
			{
				spostim_xy(46,9);
				cout<<"                  	 "<<endl;
				spostim_xy(46,9);
				cin>>temp->amza;
			}
		spostim_xy(23,12);
		cout<<"Datelindja e Studentit (dd/mm/vvvv): ";
		cin>>temp->dtl;
		spostim_xy(23,15);
		cout<<"Adresa e Studentit: ";
		cin>>temp->adresa;
		sa:				// blloku i leximit te mesatares
		spostim_xy(23,18);
		cout<<"Mesatarja e Studentit : ";
		spostim_xy(48,18);
		cout<<"                   	";
		spostim_xy(48,18);
		while(!(cin >> temp->mes ) )
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			spostim_xy(48,18);
			cout<<"                   	";
			spostim_xy(48,18);
			cin>>temp->mes;
		}
		if(temp->mes > 10)  // kontrollohet vlera e mesatares se mos eshte mbi 10
			{	
				goto sa;        // spostim per te rifutur mesataren
			}
		temp->tjetri=NULL;
		if(kreu==NULL)
			{
				kreu=temp;
				fundi=temp;
				temp=NULL;
			}
		else
			{
				fundi->tjetri=temp;
				fundi=temp;
			}
		numero++;
	}
	void Edito_Regjistrim()  // funksioni i modifikimit te regjistrimeve
	{
		nyja *f, *t=new nyja;
		cout<<"Futni Nr Serial te Studentit qe do te Editoni :\n";
		while(!(cin>>t->ID))
			{
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				system("CLS");
				cout << "Vlere e pavlefshme...! \n\n";
				system("pause");
				system("CLS");
				goto ss;
			}
		f=kreu;
		while(f!=NULL)
		{
			if(t->ID==f->ID)
				break;
			f=f->tjetri;
		}
		if(f==NULL)
		{
			ss:
			system("CLS");
			cout<<"Fatkeqsisht ..... Ky regjistrim nuk ekziston \n\n";
		}
		else
		{
		system("CLS");
		spostim_xy(2,2);	
		Siper_horizontal();
		spostim_xy(2,3);
		Line();
		spostim_xy(77,3);
		Line();
		spostim_xy(2,4);
		Poshte_horizontal();
		// Spostime dhe vijezime
		spostim_xy(2,5);	
		Siper_horizontal();
		spostim_xy(2,6);
		Line();
		spostim_xy(77,6);
		Line();
		spostim_xy(2,7);
		Poshte_horizontal();
		// Spostime dhe vijezime
		spostim_xy(2,8);	
		Siper_horizontal();
		spostim_xy(2,9);
		Line();
		spostim_xy(77,9);
		Line();	
		spostim_xy(2,10);
		Poshte_horizontal();
		// Spostime dhe vijezime
		spostim_xy(2,11);	
		Siper_horizontal();
		spostim_xy(2,12);
		Line();
		spostim_xy(77,12);
		Line();
		spostim_xy(2,13);
		Poshte_horizontal();
		// Spostime dhe vijezime
		spostim_xy(2,14);	
		Siper_horizontal();
		spostim_xy(2,15);
		Line();
		spostim_xy(77,15);
		Line();
		spostim_xy(2,16);
		Poshte_horizontal();
		// Spostime dhe vijezime
		spostim_xy(2,17);	
		Siper_horizontal();
		spostim_xy(2,18);
		Line();
		spostim_xy(77,18);
		Line();
		spostim_xy(2,19);
		Poshte_horizontal();
		nyja *tempo=new nyja;
		spostim_xy(23,3);
		cout<<"Emri i Studentit: "; // fillon modifikimi
		cin>>tempo->emri;
		while(kontrollo(tempo->emri)==false)
		{
			spostim_xy(43,3);
			cout<<"                     	  ";
			spostim_xy(43,3);
			cin>>tempo->emri;
		}
		f->emri=tempo->emri;
		spostim_xy(23,6);
		cout<<"Mbiemri i Studentit: ";
		cin>>tempo->mbiemri;
		while(kontrollo(tempo->mbiemri)==false)
			{
				spostim_xy(50,6);
				cout<<"                     ";
				spostim_xy(50,6);
				cin>>tempo->mbiemri;
			}
		f->mbiemri=tempo->mbiemri;
		spostim_xy(23,9);
		cout<<"Amza e Studentit: ";
		cin>>tempo->amza;
		while(kontrollo_alfabet(tempo->amza) == false)
			{
				spostim_xy(46,9);
				cout<<"                  	 "<<endl;
				spostim_xy(46,9);
				cin>>tempo->amza;
			}
		f->amza=tempo->amza;
		
		spostim_xy(23,12);
		cout<<"Ditelindja e Studentit: ";
		cin>>tempo->dtl;
		f->dtl=tempo->dtl;
		spostim_xy(23,15);
		cout<<"Adresa e Studentit: ";
		cin>>tempo->adresa;
		f->adresa=tempo->adresa;
		s:
		spostim_xy(23,18);
		cout<<"Mesataren e Studentit : ";
		spostim_xy(48,18);
		cout<<"                   	";
		spostim_xy(48,18);
		while(!(cin >> tempo->mes ) )
			{
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				spostim_xy(48,18);
				cout<<"                   	";
				spostim_xy(48,18);
				cin>>tempo->mes;
			}
		if(tempo->mes > 10)
			{	
				goto s;
			}
		f->mes=tempo->mes;
		cout<<"\n\n";
		}
	}
	void kerko_Regjistrim() // funksioni i kerkimit te regjistrimeve
	{
		nyja *temp=new nyja, *t;
		cout<<"Futni Nr Serial te Studentit qe do te kerkoni :\n";
		while(!(cin>>temp->ID))
			{
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				system("CLS");
				cout << "Vlere e pavlefshme...! \n\n";
				system("pause");
				system("CLS");
				goto zz;
			}
		t=kreu;
			while(t!=NULL)
			{
				if( t->ID==temp->ID)
					break;	
					t=t->tjetri;
			}
			if(t==NULL)
			{
				zz:
				system("CLS");
				cout<<"Fatkeqsisht ..... Regjistrimi nuk ekziston \n\n";
			}	
			else
			{
			listo_tabele();
			spostim_xy(2,8);	
			Siper_horizontal();
			spostim_xy(2,9);
			Line();
			spostim_xy(77,9);
			Line();
			spostim_xy(4,9);
			// Realizohet afishimi i regjistrimeve te gjetura
		 	cout<<setw(6)<<left<<t->ID <<setw(11)<<left<<t->emri<<setw(12)<<left<<t->mbiemri<<setw(9)<<left<<t->amza<<setw(12)<<left<<t->dtl<<setw(15)<<left<<t->adresa<<setw(1)<<left<<t->mes;
			spostim_xy(2,10);
			Poshte_horizontal();	
			}
	}
	void Fshij_Regjistrim()  // funksioni i fshirjes se regjistrimeve
	{
		int s;
		nyja *temp; // ruajtes i perkohshem
		nyja *regj, // regjistrimi qe do te fshihet
			 *para_ardhes; // regjistrimi parardhes per tu fshire
		cout<<"Futni Nr Serial te Studentit qe do te Fshini :\n";
		while(!(cin>>s))
			{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			system("CLS");
			cout << "Vlere e pavlefshme...! \n\n";
			system("pause");
			system("CLS");
			goto aa;
			}
		if(s==kreu->ID)
		{
			temp=kreu;
			kreu=kreu->tjetri;
			delete temp;
			cout<<endl<<endl;
			listo_tabele();
			tabela_data();	
		}
		else
		{
			regj=kreu;
			para_ardhes=NULL;
			while(regj!=NULL){
				if(regj->ID==s){
					break;
				}
				para_ardhes=regj;
				regj=regj->tjetri;
			}
			if(regj==NULL)
			{
				aa:
				system("CLS");
				cout<<"Nuk u gjet Regjistrimi \n\n";
			}
			else{
				para_ardhes->tjetri=regj->tjetri;
				delete regj;
				listo_tabele();
				tabela_data();
			}
				
		}
	}
	                             // funksioni i levizjes neper rreshtat e regjistrimeve te studenteve
	void Zhvendosu(float x,float y){
			if(x==y){
				return;
			}
			nyja *kaluar_x=NULL;
			nyja *aktual_x=kreu;
			while(aktual_x && aktual_x->mes!=x){
				kaluar_x=aktual_x;
		 		aktual_x=aktual_x->tjetri;
			}
			nyja *kaluar_y=NULL;
			nyja *aktual_y=kreu;
			while(aktual_y && aktual_y->mes!=y ){
				kaluar_y=aktual_y;
				aktual_y=aktual_y->tjetri;
			}
			if(aktual_x==NULL || aktual_y==NULL){
				return;
			}
			if(kaluar_y!=NULL){
				kaluar_y->tjetri=aktual_x;	
			}
			else{
				kreu=aktual_x;
			}
			if(kaluar_x!=NULL){
				kaluar_x->tjetri=aktual_y;	
			}
			else{
				kreu=aktual_y;
			}
			nyja *temp=aktual_x->tjetri;
			aktual_x->tjetri=aktual_y->tjetri;
			aktual_y->tjetri=temp;		
	}
	
	void tabela_data() // funksioni i paraqitjes se tabeles me regjistrimet
		{
			nyja *t;
			t=kreu;
			int x=4;
			int y=8;
			int s=2;
			while(t!=NULL)
			{
			spostim_xy(s,y);
			Siper_horizontal();
			spostim_xy(s,y+1);
			Line();
			spostim_xy(s+75,y+1);
			Line();
			spostim_xy(x,y+1);
			cout<<setw(6)<<left<<t->ID <<setw(11)<<left<<t->emri<<setw(12)<<left<<t->mbiemri<<setw(9)<<left<<t->amza<<setw(12)<<left<<t->dtl<<setw(15)<<left<<t->adresa<<setw(1)<<left<<t->mes;
			t=t->tjetri;
			spostim_xy(s,y+2);
			Poshte_horizontal();	
			y=y+3;
			}
			spostim_xy(s,y+1);
			Siper_horizontal();
			spostim_xy(s,y+2);
			Line();
			spostim_xy(s+75,y+2);
			Line();
			spostim_xy(x+31,y+2);
			cout<<"Fund";
			spostim_xy(s,y+3);
			Poshte_horizontal();		
		}
	
	void invers() // funksioni i paraqitjes se tabeles ne rend zbrites
		{
			nyja* para_ardhes   = NULL;
    		nyja* korrent = kreu;
    		nyja* tjetri;
    	while (korrent != NULL)
	    {
	        tjetri  = korrent->tjetri;  
	        korrent->tjetri = para_ardhes;   
	        para_ardhes = korrent;
	        korrent = tjetri;
	    }
    		kreu = para_ardhes;
	}
	
	void tabela_mes() // funksioni i paraqitjes se tabeles me regjistrimet
		{
			nyja *t;
			t=kreu;
			int x=4;
			int y=8;
			int s=2;
			float shuma = 0;
			float nrst = 0;
			while(t!=NULL)
			{
			spostim_xy(s,y);
			Siper_horizontal();
			spostim_xy(s,y+1);
			Line();
			spostim_xy(s+75,y+1);
			Line();
			spostim_xy(x,y+1);
			cout<<setw(6)<<left<<t->ID <<setw(11)<<left<<t->emri<<setw(12)<<left<<t->mbiemri<<setw(9)<<left<<t->amza<<setw(12)<<left<<t->dtl<<setw(15)<<left<<t->adresa<<setw(1)<<left<<t->mes;
			shuma = shuma + t->mes;
			nrst++;
			t=t->tjetri;
			spostim_xy(s,y+2);
			Poshte_horizontal();	
			y=y+3;
			}
			spostim_xy(s,y+1);
			Siper_horizontal();
			spostim_xy(s,y+2);
			Line();
			spostim_xy(s+75,y+2);
			Line();
			spostim_xy(x+27,y+2);
			cout<<"Mesatare e kursit="<<shuma/nrst;
			spostim_xy(s,y+3);
			Poshte_horizontal();		
		}
	
	void listo_tabele()  // funksioni i ndertimit te skeletit te tabeles qe liston te dhenat
	{
		spostim_xy(2,3);	
		Siper_horizontal();
		spostim_xy(2,4);
		Line();	
		spostim_xy(77,4);
		Line();	
		spostim_xy(2,5);
		Line();	
		spostim_xy(77,5);
		Line();
		spostim_xy(2,6);
		Line();	
		spostim_xy(77,6);
		Line();
		spostim_xy(2,7);
		Poshte_horizontal();	
		spostim_xy(30,4);	
		cout<<"TE DHENAT E STUDENTEVE"<<endl;
		spostim_xy(4,6);
		cout<<"ID    "<<"Emri       "<<"Mbiemri     "<<"Amza     "<<"Datelindja  "<<"Adresa   	 "<<"   Mes";
	
	}
		void Siper_horizontal() // funksioni i mbushjes se pjeses se kreut
	{
		char para = ' ';
		para = cout.fill((char)205);
		cout << (char)201 << setw(74) << "" << (char)187 << endl;
		cout.fill(para);
	}
	void Line()   // funksioni i vijezimit
	{
	cout << (char)186<< endl;
	}
	void Poshte_horizontal()  // funksioni i mbushjes se pjeses se kreut
	{
		char para = ' ';
		para = cout.fill((char)205);
		cout << (char)200 << setw(74) << "" << (char)188 << endl;
		cout.fill(para);
	}
	void Menu()  // funksioni i menuse kryesore te programit
	{
		spostim_xy(2,2);	
		Siper_horizontal();
		spostim_xy(2,3);
		Line();
		spostim_xy(77,3);
		Line();
		spostim_xy(2,4);
		Line();
		spostim_xy(77,4);
		Line();
		spostim_xy(2,5);
		Line();
		spostim_xy(77,5);
		Line();
		spostim_xy(2,6);
		Line();
		spostim_xy(77,6);
		Line();
		spostim_xy(2,7);
		Line();
		spostim_xy(77,7);
		Line();
		spostim_xy(2,8);
		Line();
		spostim_xy(77,8);
		Line();
		spostim_xy(2,9);
		Line();
		spostim_xy(77,9);
		Line();
		spostim_xy(2,10);
		Line();
		spostim_xy(77,10);
		Line();
		spostim_xy(2,11);
		Line();
		spostim_xy(77,11);
		Line();
		spostim_xy(2,12);
		Line();
		spostim_xy(77,12);
		Line();
		spostim_xy(2,13);
		Line();
		spostim_xy(77,13);
		Line();
		spostim_xy(2,14);
		Line();
		spostim_xy(77,14);
		Line();
		spostim_xy(2,15);
		Line();
		spostim_xy(77,15);
		Line();
		spostim_xy(2,16);
		Line();
		spostim_xy(77,16);
		Line();
		spostim_xy(2,17);
		Line();
		spostim_xy(77,17);
		Line();
		spostim_xy(2,18);
		Line();
		spostim_xy(77,18);
		Line();
		spostim_xy(2,19);
		Line();
		spostim_xy(77,19);
		Line();
		spostim_xy(2,20);
		Line();
		spostim_xy(77,20);
		Line();
		spostim_xy(2,21);
		Poshte_horizontal();
	//  Shenimet e Menuse kryesore
		spostim_xy(35,3); // pozicionon kursorin pas frazes "Beni zgjedhjen tuaj:"
	cout<<"MENUJA KRYESORE"<<endl;
		spostim_xy(28,1);
	cout<<"Zgjidh veprimin qe do kryesh!"<<endl;
		spostim_xy(4,6);
	cout<<"1- Shto Student te rinj"<<endl;
		spostim_xy(4,8);
	cout<<"2- Edito Studentet ekzistues"<<endl;
		spostim_xy(4,10);
	cout<<"3- Kerko Studentet e hedhur"<<endl;
		spostim_xy(4,12);
	cout<<"4- Fshij ndonje Student"<<endl;
		spostim_xy(4,14);
	cout<<"5- Listo te gjithe Studentet"<<endl;
		spostim_xy(4,16);
	cout<<"6- Gjej mesataren e kursit"<<endl;
		spostim_xy(4,18);
	cout<<"7- Mbyll Programin"<<endl;
	}
};
list obj;
// Funksioni kryesor i programit te menaxhimit te regjistrimeve te studenteve
int main()
{
	system("CLS");  	// boshatiset ekrani
	system("color 4F"); // vendoset ngjyra e sfondit 4 - E kuqe si dhe karakteret 7 - E bardhe
	int n,         		// numri i regjistrimeve qe do te procesohen
	    zgjedhja,  		// zgjedhja juaj nga menuja kryesore
		NrSer=1;    	// inicializohet numri serial i studenteve
	L: 
	obj.Menu();
	obj.spostim_xy(4,23);
	cout<<"Beni zgjedhjen tuaj: ";
		l:
	char c=getch();
  		if(c>='1' && c<='8')
		{
		zgjedhja=c-48;
		cout<<c;
	  		goto l2;
		}
		else
		{
			zgjedhja=getch();
		}
  	goto l;
	l2:
  	Sleep(200);
  	system("CLS");
	switch(zgjedhja)
	{
		case 1:
		cout<<"Sa Student doni te regjistroni: ";
		while(!(cin >> n))
			{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			system("CLS");
			obj.spostim_xy(2,2);
				obj.Siper_horizontal();
				obj.spostim_xy(2,3);
				obj.Line();
				obj.spostim_xy(77,3);
				obj.Line();
				obj.spostim_xy(2,4);
				obj.Poshte_horizontal();
				obj.spostim_xy(4,3);
			cout << "Vlere e pavlefshme...  Provo serish: \n\n";
			system("pause");
			system("CLS");
			goto L;
		}
		system("CLS");
		if(obj.eshteBosh())
		{	NrSer=1;
			for(int i=0;i<n;i++)
			{
				obj.shto_data(NrSer);
				NrSer++;
				system("CLS");
			}
		}
		else
		{
			for(int i=0;i<n;i++)
			{
				obj.shto_data(NrSer);
				NrSer++;
				system("CLS");
			}
		}
		cout<<"Regjistrimi u krye me sukses...! \n";
			system("pause");
			system("CLS");
			goto L;
			break;
		case 2:
		system("CLS");
			if(obj.eshteBosh())
			{
				cout<<"Fillimisht kryej regjistrime....! \n"<<endl;
			}
			else
			{
			obj.Edito_Regjistrim();	
			}
		system("pause");
		system("CLS");
		goto L;		
		break;
		case 3:
			system("CLS");
			if(obj.eshteBosh())
			{
				cout<<"Fillimisht kryej regjistrime....! \n"<<endl;
			}
			else
			{
				obj.kerko_Regjistrim();
			}
				system("pause");
			system("CLS");
			goto L;
			break;
		case 4:
		system("CLS");
			if(obj.eshteBosh())
			{
				cout<<"regjistrimi eshte BOSH....! \n"<<endl;
			}
			else
			{
				obj.Fshij_Regjistrim();
			}
				system("pause");
				system("CLS");
				goto L;
				break;
		case 5:
			system("CLS");
			if(obj.eshteBosh())
			{
				cout<<"Fillimisht kryej regjistrime....! \n"<<endl;
			}
			else
			{
				obj.listo_tabele();
				obj.tabela_data();
			}
				system("pause");
				system("CLS");
				goto L;
				break;
		case 6:
			system("CLS");
			if(obj.eshteBosh())
			{
				cout<<"Fillimisht kryej regjistrime....! \n"<<endl;
			}
			else
			{
				obj.listo_tabele();
				obj.tabela_mes();
			}
				system("pause");
				system("CLS");
				goto L;
				break;		
		case 7:
				return 0;
		default:
			system("CLS");
			cout<<"Numer i pavlefshem.. "<<endl;
			system("pause");
			system("CLS");
			goto L;	
	}
}
bool kontrollo(string a) // kontrollon nese ka shenja te vargut a ne segmentin 48-57 dhe kthen false perndryshe kthen true
{
	int i=0;
	while(a[i]!=0)
	{
		if(a[i]>=48 && a[i]<=57)
		{
			return false;
		}
		else
		{
			i++;
		}
	}
	return true;
}
bool kontrollo_alfabet(string a) // kontrollon nese ka shenja te vargut a ne segmentin 65-122 dhe kthen false perndryshe kthen true
{
	int i=0;
	while(a[i]!=0)
	{
		if(a[i]>=65 && a[i]<=122)
		{
			return false;
		}
		else
		{
			i++;
		}
	}
	return true;
}

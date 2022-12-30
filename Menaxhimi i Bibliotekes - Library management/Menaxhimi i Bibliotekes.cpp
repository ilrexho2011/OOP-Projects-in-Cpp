//***************************************************************
//            DIREKTIVAT E DOMOSDOSHME TE PROJEKTIT
//****************************************************************
#include <iostream>
#include <fstream>
#include <conio.h>
#include <stdio.h>
#include <process.h>
#include <string.h>
#include <iomanip>
using namespace std;
//***************************************************************
//               KLASAT QE PERDOREN NE PROJEKT
//****************************************************************

class libri
{
	char kod_libri[6]; 		     // numri i librit
	char titull_libri[50];	    // titulli i librit
	char autor_libri[20];	   // autori i librit
  public:
	void regjistrim_libri()
	{
		cout << "\n REGJISTRIMI I LIBRIT TE RI...\n";
		cout << "\n Futni kodin e Librit : ";
		cin >> kod_libri;
		cout << "\n\n Futni Titullin e Librit : ";
		gets(titull_libri);
		cout << "\n\n Jepni Emrin e Autorit : ";
		gets(autor_libri);
		cout << "\n\n\n Libri u regjistrua...!";
	}

	void paraqitje_libri()
	{
		cout << "\n Kodi i Librit. : " << kod_libri;
		cout << "\n Titulli i Librit : ";
		puts(titull_libri);
		cout << " Emri i Autorit : ";
		puts(autor_libri);
	}

	void modifikim_libri()
	{
		cout << "\n Modifiko Kodin e Librit. : " << kod_libri;
		cout << "\n Modifiko Titullin e Librit : ";
		gets(titull_libri);
		cout << "\n Modifiko Emrin e Autorit : ";
		gets(autor_libri);
	}

	char* kthekodlibri()
	{
		return kod_libri;
	}
	void raporti()
	{cout << kod_libri << setw(30) << titull_libri << setw(30) << autor_libri << endl;}


};  // FUNDI I KLASES LIBRI **********************************************************

class student
{
	char kodstudenti[6];
	char emerstudenti[20];
	char kodlibri[6];
	 int shenje;
public:
	void regjistrim_studenti()
	{
		
	 	cout << "\nREGJISTRIMI I STUDENTIT TE RI...\n";
		cout << "\n Futni Numrin e Amzes : ";
		cin >> kodstudenti;
		cout << "\n\n Futni Emrin e Studentit : ";
		gets(emerstudenti);
		shenje=0;
		kodlibri[0]='/0';
		cout << "\n\n Regjistrimi i Studentit u krye...!";
	}

	void paraqitje_studenti()
	{
		cout << "\n Nr. i Amzes : " << kodstudenti;
		cout << "\n Emri i Studentit : ";
		puts(emerstudenti);
		cout << "\n Kodi i Librit te leshuar : "<< shenje;
		if(shenje==1)
			cout << "\n Kodi i Librit " << kodlibri;
	}

	void modifikim_studenti()
	{
		cout << "\n Nr. i Amzes : " << kodstudenti;
		cout << "\n Modifiko Emrin e Studentit : ";
		gets(emerstudenti);
	}

	char* kthekodstudenti()
	{
		return kodstudenti;
	}

	char* kthekodlibri()
	{
		return kodlibri;
	}

	int ktheshenjen()
	{
		return shenje;
	}

	void shtoshenje()
	{shenje=1;}

	void zeroshenje()
	{shenje=0;}

	void terhiqkodlibri(char t[])
	{
		strcpy(kodlibri,t);  // kopjon kodin ne nje string
	}

	void raporti()
	{cout << "\t" << kodstudenti << setw(20) << emerstudenti << setw(10) << shenje << endl;}

};         // FUNDI I KLASES STUDENTI ----------------------------

//****************************************************************
//  DEKLARIMET GLOBALE PER OBJEKTET E DY KLASAVE DHE ATA STREAM
//****************************************************************

fstream fp,fp1;    // objekte te klases se gatshme fstream 
                   // fp1 - per temp.dat kurse fp - per student.dat dhe libri.dat
libri lib;        // objekt i klases libri
student st;       // objekt i klases student

//****************************************************************
//    	   FUNKSIONI I SHKRIMIT NE SKEDAR
//****************************************************************

void sheno_liber()
{
	char germe;
	fp.open("libri.dat",ios::out|ios::app);
	do
	{
		
		lib.regjistrim_libri();
		fp.write((char*)&lib,sizeof(libri));
		cout << "\n\n Doni te shtoni regjistrime te tjera..(p/j?)";
		cin >> germe;
	}   while (germe=='p'||germe=='P');
	fp.close();
}

void sheno_student()         // shton studentin ne skedar
{
	char germe;
	fp.open("student.dat",ios::out|ios::app);
	do
	{
		st.regjistrim_studenti();
		fp.write((char*)&st,sizeof(student));
		cout << "\n\n Doni te shtoni regjistrime te tjera..(p/j?)";
		cin >> germe;
	}   while (germe=='p'||germe=='P');
	fp.close();
}

//***************************************************************
//   FUNKSIONI I LEXIMIT TE REGJISTRIMEVE SPECIFIKE NGA SKEDARI
//****************************************************************

void paraqit_librat_skedar(char n[])
{
	cout<<"\n TE DHENAT E LIBRIT\n";
	int flamur=0;            //vendos nje shenjues ne vlere fillestare
	fp.open("libri.dat",ios::in);
	while (fp.read((char*)&lib,sizeof(libri)))
	{
		if (strcmpi(lib.kthekodlibri(),n)==0)
		{
			lib.paraqitje_libri();
		 	flamur=1;
		}
	}
	
	fp.close();
	if  (flamur==0)
		cout<<"\n\n Libri nuk ekziston";
	getch();
}

void paraqit_studentet_skedar(char n[])
{
	cout << "\n TE DHENAT E STUDENTIT\n";
	int flamur=0;            //vendos nje shenjues ne vlere fillestare
	fp.open("student.dat",ios::in);
	while (fp.read((char*)&st,sizeof(student)))
	{
		if ((strcmpi(st.kthekodstudenti(),n)==0))
		{
			st.paraqitje_studenti();
			flamur=1;
		}
	}
	
	fp.close();
	if (flamur==0)
    		cout<<"\n\n Studenti nuk ekziston";
 	getch();
}


//***************************************************************
//    	FUNKSIONI I MODIFIKIMIT TE REGJISTRIMEVE NE SKEDAR
//****************************************************************


void modifikim_libri()
{
	char n[6];
	int found=0;
	
	cout << "\n\n\t MODIFIKO REGJISTRIMIN E LIBRIT.... ";
	cout << "\n\n\t Futni Kodin me te cilin eshte regjistruar Libri : ";
	 cin >> n;
	fp.open("libri.dat",ios::in|ios::out);
	while (fp.read((char*)&lib,sizeof(libri)) && found==0)
	{
		if (strcmpi(lib.kthekodlibri(),n)==0)
		{
			lib.paraqitje_libri();
			cout << "\n Futni te dhenat e reja te librit : "<<endl;
			lib.modifikim_libri();
			int pozicion=-1*sizeof(lib);
		    	fp.seekp(pozicion,ios::cur);
		    	fp.write((char*)&lib,sizeof(libri));
		    	cout<<"\n\n\t Regjistrimi u Perditesua...!";
		    	found=1;
		}
	}

    	fp.close();
    	if  (found==0)
    		cout<<"\n\n Regjistrimi nuk gjendet!!!";
    	getch();
}


void modifikim_studenti()
{
	char n[6];
	int found=0;
	
	cout << "\n\n\t MODIFIKIMI I REGJISTRIMIT TE STUDENTIT...";
	cout << "\n\n\t Futni numrin e Amzes se Studentit : ";
	 cin >> n;
	fp.open("student.dat",ios::in|ios::out);
	while (fp.read((char*)&st,sizeof(student)) && found==0)
	{
		if (strcmpi(st.kthekodstudenti(),n)==0)
		{
			st.paraqitje_studenti();
			cout<<"\n Futni te dhenat e reja te studentit : "<<endl;
			st.modifikim_studenti();
			int pozicion=-1*sizeof(st);
			fp.seekp(pozicion,ios::cur);
			fp.write((char*)&st,sizeof(student));
			cout<<"\n\n\t Regjistrimi u perditesua : ";
			found=1;
		}
	}
	
	fp.close();
	if  (found==0)
		cout << "\n\n Regjistrimi nuk gjendet!!! ";
	getch();
}

//***************************************************************
//    	FUNKSIONI I FSHIRJES SE REGJISTRIMIT NGA SKEDARI
//****************************************************************


void fshirje_studenti()
{
	char n[6];
	int flamur=0;	       //vendos nje shenjues ne vlere fillestare
	
    	cout << "\n\n\n\t FSHIRJA E STUDENTIT...";
    	cout << "\n\n Futni numrin e Amzes se Studentit qe doni te fshini : ";
    	 cin >> n;
    	fp.open("student.dat",ios::in|ios::out);
    	fstream fp2;
    	fp2.open("Temp.dat",ios::out);
    	fp.seekg(0,ios::beg);
    	while (fp.read((char*)&st,sizeof(student)))
	{
		if (strcmpi(st.kthekodstudenti(),n)!=0)
	     		fp2.write((char*)&st,sizeof(student));
		else
	   		flamur=1;
	}
    	
	fp2.close();
    	fp.close();
    	remove("student.dat");
    	rename("Temp.dat","student.dat");
    	if (flamur==1)
     		cout << "\n\n\t Regjistrimi u fshi...!";
    	else
     		cout << "\n\n Regjistrimi nuk gjendet!!!";
    	getch();
}


void fshirje_libri()
{
	char n[6];
	
	cout << "\n\n\n\t FSHIRJA E LIBRIT ...";
	cout << "\n\n Futni Kodin e Librit qe doni te fshini : ";
	 cin >> n;
	fp.open("libri.dat",ios::in|ios::out);
	fstream fp2;
	fp2.open("Temp.dat",ios::out);
	fp.seekg(0,ios::beg);
	while (fp.read((char*)&lib,sizeof(libri)))
	{
		if (strcmpi(lib.kthekodlibri(),n)!=0)  
		{
			fp2.write((char*)&lib,sizeof(libri));
		}
	}
    	
	fp2.close();
    	fp.close();
    	remove("libri.dat");
    	rename("Temp.dat","libri.dat");
    	cout << "\n\n\t Regjistrimi u fshi ..";
    	getch();
}



//***************************************************************
//    	FUNKSIONI QE PARAQET LISTEN E GJITHE STUDENTEVE
//****************************************************************

void paraqit_studentet()
{
	
     	fp.open("student.dat",ios::in);
     	if (!fp)
     	{
       		cout << " GABIM!!! SKEDARI NUK MUND TE HAPET !!!";
       		getch();
       		return;
     	}

	cout << "\n\n\t\t LISTA E STUDENTEVE \n\n";
	cout << "==================================================================\n";
	cout << "\t Nr.Amza " << setw(10) << " Emri " << setw(20) << " Libri i leshuar\n";
	cout << "==================================================================\n";

	while (fp.read((char*)&st,sizeof(student)))
	{
		st.raporti();
	}
     	
	fp.close();
	getch();
}


//***************************************************************
//    	  FUNKSION QE PARAQET LISTEN E LIBRAVE
//****************************************************************

void paraqit_librat()
{
	
	fp.open("libri.dat",ios::in);
	if (!fp)
	{
		cout << " GABIM!!! SKEDARI NUK MUND TE HAPET !!! ";
       		getch();
       		return;
     	}

	cout << "\n\n\t\t LISTA E LIBRAVE \n\n";
	cout << "=========================================================================\n";
	cout << "Kodi i Librit " << setw(20) << " Titulli i Librit" << setw(25) << " Autori\n";
	cout << "=========================================================================\n";

	while(fp.read((char*)&lib,sizeof(libri)))
	{
		lib.raporti();
	}
     	fp.close();
     	getch();
}



//***************************************************************
//    	    FUNKSION PER LESHIMIN E LIBRAVE
//****************************************************************

void leshim_libri()
{
	char studnr[6],libnr[6];
	int found=0,flamur=0;       //vendos nje shenjuesat ne vlere fillestare
	
	cout << "\n\n LESHIMI I LIBRAVE ...";
	cout << "\n\n\t Futni numrin e Amzes se Studentit : ";
	 cin >> studnr;
	fp.open("student.dat",ios::in|ios::out);
    	fp1.open("libri.dat",ios::in|ios::out);
    	while(fp.read((char*)&st,sizeof(student)) && found==0)
       	{
		if(strcmpi(st.kthekodstudenti(),studnr)==0)
		{
			found=1;
			if(st.ktheshenjen()==0)
			{
		      		cout << "\n\n\t Futni Kodin e Librit : ";
				     cin >> libnr;
				while (fp1.read((char*)&lib,sizeof(libri))&& flamur==0)
				{
			   		if (strcmpi(lib.kthekodlibri(),libnr)==0)
					{
						lib.paraqitje_libri();
						flamur=1;
						st.shtoshenje();
						st.terhiqkodlibri(lib.kthekodlibri());
       						int pozicion=-1*sizeof(st);
						fp.seekp(pozicion,ios::cur);
						fp.write((char*)&st,sizeof(student));
						cout << "\n\n\t Leshimi i librit u krye me sukses\n\nVini Re: Shkruani daten e sotme 						ne anen e pasme te librit dhe dorezojeni ate brenda 15 diteve 10$ GJOBE							per vonesen 15 dite";
					}
		    		}
		  		if (flamur==0)
		    			cout << "Libri nuk ekziston!!! ";
			}
	    		else
		  		cout << "Ju nuk keni kthyer Librin e fundit !!! ";

		}
	}
      	if (found==0)
		cout << "Regjistrimi i Studentit nuk ekziston...!";
	getch();
  	fp.close();
  	fp1.close();
}

//***************************************************************
//    	  FUNKSION PER DOREZIMIN E LIBRAVE
//****************************************************************

void dorezim_libri()
{
    char studnr[6],libnr[6];
    int found=0,flamur=0,ditet,gjoba;        //vendos shenjuesat ne vlere fillestare
    
    cout << "\n\n DOREZIMI I LIBRAVE ...";
    cout << "\n\n\t Futni numrin e Amzes se Studentit : ";
     cin >> studnr;
    fp.open("student.dat",ios::in|ios::out);
    fp1.open("libri.dat",ios::in|ios::out);
    while (fp.read((char*)&st,sizeof(student)) && found==0)
       {
	    if (strcmpi(st.kthekodstudenti(),studnr)==0)
	    {
		    found=1;
		    if (st.ktheshenjen()==1)
		    {
			while (fp1.read((char*)&lib,sizeof(libri))&& flamur==0)
			{
			   if (strcmpi(lib.kthekodlibri(),st.kthekodlibri())==0)
			{
				lib.paraqitje_libri();
				flamur=1;
				cout << "\n\nNumri i diteve deri ne dorezimin e librit : ";
				cin >> ditet;
				if (ditet>15)
				{
				   gjoba = (ditet-15)*1;
				   cout << "\n\n Masa e gjobes per vonesen : " << gjoba;
				}
					st.zeroshenje();
					int pozicion=-1*sizeof(st);
					fp.seekp(pozicion,ios::cur);
					fp.write((char*)&st,sizeof(student));
					cout << "\n\n\t Libri u dorezua me sukses!!!";
			}
		    }
		  if(flamur==0)
		    cout << "Ky kod libri nuk ekziston!!!";
		      }
		 else
			cout << "Ky liber eshte leshuar..Ju lutemi kontrolloni!!";
		}
	   }
      if (found==0)
	cout << "Ky regjistrim studenti nuk ekziston...!";
	getch();
  fp.close();
  fp1.close();
  }

void gotoxy(int x, int y)
{

}


//***************************************************************
//    	           FUNKSIONI PREZANTUES
//****************************************************************

void prezantimi()
{
	
	gotoxy(35,11);
	cout << " SISTEMI";
	gotoxy(35,14);
	cout << " MENAXHIMIT";
	gotoxy(35,17);
	cout << " TE BIBLIOTEKES";
	cout << "\n\n NDERTUAR NGA : ILIRJAN REXHO";
	cout << "\n\n SHKOLLA : JOPUBLIKE PERLA";
	getch();
}



//***************************************************************
//    	   FUNKSIONI I ADMINISTRIMIT TE MENUSE
//****************************************************************

void menu_administrimi()
{
	
	int zgjedhje2;
	cout << "\n\n\n\t MENUJA E ADMINISTRATORIT";
	cout<<"\n\t --------------------------------";
	cout << "\n\n\t1. KRIJO REGJISTRIM STUDENTI";
	cout << "\n\n\t2. PARAQIT GJITHE REGJISTRIMET E STUDENTEVE";
	cout << "\n\n\t3. PARAQIT REGJISTRIMIN E NJE STUDENTI SPECIFIK ";
	cout << "\n\n\t4. MODIFIKO REGJISTRIMIN E STUDENTIT";
	cout << "\n\n\t5. FSHIJ REGJISTRIMIN E STUDENTIT";
	cout << "\n\n\t6. REGJISTRO LIBER";
	cout << "\n\n\t7. PARAQIT LIBRAT";
	cout << "\n\n\t8. PARAQIT TE DHENAT E NJE LIBRI";
	cout << "\n\n\t9. MODIFIKO LIBER";
	cout << "\n\n\t10. FSHIJ LIBER";
	cout << "\n\n\t11. KTHIM NE MENUNE KRYESORE";
	cout << "\n\n\t --------------------------------";
	cout << "\n\n\t Ju lutemi - Beni zgjedhjen tuaj (1-11) : ";
	 cin >> zgjedhje2;
	switch (zgjedhje2)
	{
    		case 1: sheno_student();break;
    		case 2: paraqit_studentet();break;
    		case 3: char num[6]; 
		       		cout << "\n\n\t Ju lutemi futni numrin e Amzes : ";
		       		 cin >> num;
		       		paraqit_studentet_skedar(num);
		       		break;
      		case 4: modifikim_studenti();break;
      		case 5: fshirje_studenti();break;
			case 6: sheno_liber();break;
			case 7: paraqit_librat();break;
			case 8: {
			       		char num[6];
			       		 
			       		cout << "\n\n\t Ju lutemi futni Kodin e Librit : ";
			       		 cin >> num;
			       		paraqit_librat_skedar(num);
			       		break;
					}
      		case  9: modifikim_libri();break;
      		case 10: fshirje_libri();break;
     		case 11: return;
      		default: cout << "\a";
   	}
   	menu_administrimi();
}


//***************************************************************
//    	     FUNKSIONI KRYESOR I PROGRAMIT
//****************************************************************


int main()
{
	char zgjedhje1;
	prezantimi();
	do
	{
		 
		cout << "\n\n\n\t MENUJA KRYESORE";
		cout << "\n\t ----------------------";
		cout << "\n\n\t1. LESHIMI I LIBRIT";
		cout << "\n\n\t2. DOREZIMI I LIBRIT";
	  	cout << "\n\n\t3. MENUJA E ADMINISTRIMIT";
	  	cout << "\n\n\t4. DALJA";
	  	cout << "\n\n\t ----------------------";
	  	cout << "\n\n\t Ju lutemi zgjidhni nje Opsion (1-4) : ";
	  	zgjedhje1=getche();
	  	switch (zgjedhje1)
	  	{
			case '1': leshim_libri();      break;
		  	case '2': dorezim_libri();     break;
		  	case '3': menu_administrimi(); break;
		  	case '4': exit(0);
		  	 default: cout << "\a";
		}
    	}while (zgjedhje1!='4');
}

//***************************************************************
//    			  FUNDI I PROJEKTIT
//***************************************************************

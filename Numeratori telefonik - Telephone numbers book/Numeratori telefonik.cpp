// Numratori telefonik
//===============================

#include <iostream>
#include <conio.h>
#include <string>
using namespace std;


//prototipi
void printline(char, int);
bool emri_vlefshem(string);
bool numri_vlefshem(string);


class kontakt
{
    string emri;
    string numri;
        
    public:
    	//Inicilizo kontaktin nga nje vlere default 
        kontakt(): emri(""), numri("")
        {}
        
        // Shiko te gjithe kontaktet
        bool shiko()
        {
            if(emri != "")
            {
                cout << emri << "\t" << numri << endl;
                return 1; //Tregon sukses
            }
            else
                return 0; //Tregon deshtim
        }
        
        //Kerko
        bool shiko(string kerko_term)
        {
            if(kerko_term == emri)
            {
                cout << emri << "\t" << numri << endl;
                return 1;
            }
            else
                return 0;
        }
        
        //Kontrollon nese emri ekziston apo jo
        bool emri_ekziston(string temri)
        {
            if(temri == emri)
                return 1;
            else
                return 0;
        }
        
        //Objekti i kontaktit eshte nisur nga vlerat e vlefshme
        bool shto(string new_emri, string new_numri)
        {
            if(emri=="")
            {
                emri = new_emri;
                numri = new_numri;
                return 1; // Sukses
            }
            else
                return 0; // Deshtim
    
        }
        
        //Editon detajet e kontaktit
        bool edit(string);
        
        //Percakton detajet e kontaktit per vlerat e perzgjedhura 
        //Kjo eshte, detajet e kontaktit jane fshire ne kete menyre
        bool erase(string new_emri)
        {
            if(new_emri==emri)
            {       
                emri = "";
                numri = "";
                return 1;
            }
            else
                return 0;
        }
};


//Editon kontaktet
bool kontakt :: edit(string new_emri)
{
    string new_numri;
    if(new_emri==emri)
    {
        cout << "Vendosni nje emer te ri: "; cin >> new_emri;
        cout << "Vendosni nje numer te ri teleoni: "; cin >> new_numri;
        
        emri = new_emri;
        numri = new_numri;
        return 1;
    }
    else
        return 0;
}



int main()
{
    kontakt person[100];
            
    string temp_emri, temp_numri;
    int zgjedh, i, counter;
    bool flag;
    bool cancel_flag;
    
    cout << "Numratori telefonik" << endl;
    
    
    do
    {   
        cout << "\n\n\n";
        printline('-', 20);
        cout << "0. Shiko Kontaktet" << endl
        << "1. Shto Kontaktet" << endl
        << "2. Modifikiko Kontaktet" << endl
        << "3. Fshi kontaktet" << endl
        << "4. Kerko" << endl
        << "5. Mbylle" << endl << endl
        << "Zgjedhja jote...";
        cin >> zgjedh;
        
        system("cls");
        printline('-', 20);
        cancel_flag = 0;
        flag = 0;
        counter = 0;
        
        switch(zgjedh)
        {
            case 0: 
                cout << "Duke kerkuar kontaktet" << endl;
                printline('-', 20);
                
                for(i=0; i<100; i++)
                    if(person[i].shiko())
                        flag = 1;
                
                if(!flag)
                    cout << "Asnje kontakt nuk gjendet!" << endl;
                break;
                
            case 1:
                cout << "Shto nje kontakt te ri\t\t\t\tshtypni $ per ta hequr" << endl;
                printline('-', 20);
                counter = 0;
                
                //Loop deri ne emrin e sakte dhe numrat qe jane futur
                do
                {
                    flag = 0;
                    if(counter)
                        cout << "Provo perseri\t\t\t\tshtypni $ per ta hequr" 
						<< endl;
						
                    //numeron se sa here do-while loop ekzekutohet
					counter++; 
                        
                    cout << "Emri: "; cin >> temp_emri;
                    
                    //Anulloje operacionin
                    if(temp_emri=="$")
                    {
                        cancel_flag = 1;
                        break;
                    }
                    cout << "Numri i telefonit: "; cin >> temp_numri;
                    
                    //Anulloje operacionin
                    if(temp_numri=="$")
                    {
                        cancel_flag = 1;
                        break;
                    }
                    
                    //Kontrollojme nese emrat ekzistojne
                    for(i=0; i<100; i++)
                        if(person[i].emri_ekziston(temp_emri))
                        {
                            cout << "Emri qe ju vendoset eshte tashme ne numrator, vendosni nje emer tjeter." 
							<< endl;
                            flag = 1;
                            break;
                        }
                    
                }while(!emri_vlefshem(temp_emri) || 
								flag ||
						!numri_vlefshem(temp_numri));
                
                if(cancel_flag)
                {
                    system("cls");
                    break;
                }
            
                
                //Ky kod e vendos kontaktin ne numratorin telefonik    
                for(i=0; i<100; i++)
                    if(person[i].shto(temp_emri, temp_numri))
                    {
                        cout << "Kontakti u shtua me sukses!" << endl;
                        flag = 1;
                        break;
                    }
                
                if(!flag)
                    cout << "Memoria plot! Fshini disa kontakte si fillim." 
					<< endl;
                break;
                
            case 2:
                cout << "Vendosni nje emer kontakti per ta edituar:" 
				"\t\t\t\tshtypni $ per ta anulluar\n";
				 cin >> temp_emri;
                
                //Anullohet operacioni
                if(temp_emri=="$")
                {
                    system("cls");
                    break;
                }
                
                for(i=0; i<100; i++)
                    if(person[i].edit(temp_emri))
                    {
                        cout << "U editua me sukses!" << endl;
                        flag = 1;
                        break;
                    }
                
                if(!flag)
                    cout << "Emri i kontaktit nuk gjendet!" << endl;
                break;
                
            case 3:
                do
                {
                    if(counter)
                        cout << "Provojeni perseri" << endl;
                    counter++;
                    cout << "Vendosni nje emer kontakti qe deshironi ta fshini:" 
					"\t\t\tshtypni $ per ta hequr\n"; 
					cin >> temp_emri;
                
                    //Anullohet operacioni
                    if(temp_emri=="$")
                    {
                        system("cls");
                        break;
                    }
                
                
                    //Konfigurimi final
                    for(i=0; i<100; i++)
                    if(person[i].emri_ekziston(temp_emri))
                    {
                        flag = 1;
                        cout << "A jeni te sigurt qe deshironi ta fshini? (1/0)" 
						<< endl;
                        int po;
                        cin >> po;
                        if(!po)
                        {
                            system("cls");
                            cancel_flag = 1;
                        }
                        break;
                    }
                
                    if(!flag)
                        cout << "Emri nuk gjendet!" << endl;
                    
                    if(cancel_flag)
                        break;
                
                    // Ky kod fshin kontaktet
                    if(flag)
                    {
                        for(i=0; i<100; i++)
                            if(person[i].erase(temp_emri))
                            {
                                cout << "U fshi me sukses!" << endl;
                                break;
                            }
                    }
                    
                }while(!flag);
                break;
                
            case 4:
                do
                {
                    if(counter)
                        cout << "Provojeni perseri" << endl;
                    counter++;
                    cout << "Keroni nje emer: \t\t\t\tshtypni $ per ta hequr\n";
					 cin >> temp_emri;
                
                    //Anullohet operacioni
                    if(temp_emri=="$")
                    {
                        system("cls");
                        break;
                    }
                
                    for(i=0; i<100; i++)
                        if(person[i].shiko(temp_emri))
                        {
                            flag = 1;
                            break;
                        }
    
                    if(!flag)
                        cout << "Emri i kontaktit nuk gjendet" << endl;
                }while(!flag);
                    
                break;
                
            case 5:
                return 0;
                break;
            
        }
    } while(1);
    
    getch();
    return 0;
}

//Printon nje vije
void printline(char ch, int size)
{
    for(int i=0; i<size; i++)
        cout << ch;
    cout << "\n";
}


//Emri i kontaktit miratohet
bool emri_vlefshem(string temri)
{
    
    if(temri.size()>20)
    {
        cout << "Emer i pavlefshem!\nFutni nje emer brenda 20 karaktereve!" 
		<< endl;
        return 0;
    }
    else if(temri == "")
    {
        cout << "Emer i pa vlefshem!\nEmri nuk mund te jete bosh!" << endl;
        return 0;
    }
    else
        return 1;
}

//Numri i telefonit miratohet
bool numri_vlefshem(string tnumri)
{
    if(tnumri.size()>13 || tnumri.size()<10)
    {
        cout << "Numer telefoni i pavlefshem\nVendosni nje numer midis 10 dhe 13 shifrave" << endl;
        return 0;
    }
    else if(tnumri == "")
    {
        cout << "Numer telefoni i pavlefshem\nMobile" 
		"Numri nuk mund te jete bosh" << endl;
        return 0;
    }
    else
        return 1;
}

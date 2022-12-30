//Sistem i Menaxhimit Studentor ne C++ pa perdorur klasa. 
#include<stdio.h>    
#include<iostream> 
#include<fstream> 
#include<string.h> 
  
using namespace std; 
  
int main(){ 
    //Vendosim limitin e gjatesise maksimale te te dhenave si (emri) 15. 
    char data[15];   
    int n = 0, zgjedhja_menu = 0, count_n = 0; 
    //Keto jane piket fillestare qe i vendosen apriori nje lende. 
    string empty = "00";     
    string proctor = ""; 
    //Ky eshte emri i skedarit ku ruhet databaza. 
    ifstream f("student.txt");       
    string line; 
     
    //Unaza e meposhtme numeron numrin total te rreshtave ne skedar. 
    for (int i = 0; std::getline(f, line); ++i){     
        count_n++;} 
      
    while(zgjedhja_menu != 6){ 
   //Ketu afishohen gjithe opsionet e vlefshme ne databaze 
    cout << "\nOperacionet e vlefshme: \n1. Shto Studente te rinj"
        << "\n2. Logim Studenti\n3. Logim Fakulteti\n4. Logim Mbikqyresi\n5. Paneli Admin\n"
        << "6. Dil\nBeni zgjedhjen tuaj: "; 
    cin >> zgjedhja_menu; 
  
    if(zgjedhja_menu == 1){ 
    cout << "Futni numrin e studenteve "; 
    cin >> n; 
      
    count_n = count_n + n; 
      
    for (int i = 0;i < n;i++){ 
        ofstream outfile; 
            outfile.open("student.txt",ios::app); 
        //Ketu ruhen te gjitha te dhenat qe i takojne nje studenti te vetem rresht e nga nje rresht. 
        cout << "Futni numrin tuaj te regjistrimit: "; 
        cin >> data; 
        outfile << data << "\t"; 
          
        cout << "Futni emrin tuaj: "; 
        cin >> data; 
        int len = strlen(data); 
          
        while (len < 15){ 
            data[len] = ' '; 
            len = len + 1; 
        } 
        outfile << data << "\t"; 
        //Shtimi i te dhenave bosh ne skedar 
        outfile << empty << "\t"; 
        outfile << empty << "\t";     
          
        cout << "Futni ID e mbikqyresit tuaj: "; 
        cin >> proctor; 
          
        outfile << proctor << endl; 
    }} 
      
    else if (zgjedhja_menu == 2){ 
        char regno[9]; 
        cout << "Futni numrin tuaj te regjistrimit: "; 
        cin >> regno; 
        ifstream infile; 
        int check = 0; 
        infile.open("student.txt",ios::in); 
          
        // Kjo unaze afishon te dhenat ne perputhje me numrin e regjistrimit te specifikuar.
		 
        while (infile >> data){ 
        if (strcmp(data,regno) == 0){ 
            cout << "\nNumri i Regjistrimit: " << data << endl; 
            infile >> data; 
            cout << "Emri: " << data << endl; 
              
            infile >> data; 
                cout << "Piket CSE1001: " << data << endl; 
              
            infile>>data; 
            cout<<"Piket CSE1002: "<<data<<endl; 
              
            infile>>data; 
            cout<<"ID Mbikqyresi: "<<data<<endl; 
              
            infile.close(); 
            check = 1;} 
        } 
          
        if (check == 0){ 
            cout<<"Ky numer regjistrimi nuk gjendet!"<<endl;}   
          
    } 
      
    // Kjo unaze perdoret per te pare dhe shtuar piket e studentit ne databaze. 
    
    else if (zgjedhja_menu == 3){ 
        char subcode[7]; 
        cout << "Futni kodin e lendes suaj: "; 
        cin >> subcode; 
        string code1 = "CSE1001", code2 = "CSE1002",mark = ""; 
        ifstream infile; 
        int check = 0; 
          
        cout << "\nOperacionet e vlefshme: \n1. Shto te dhena per piket\n"
                << "2. Shiko te dhenat\nBeni zgjedhjen tuaj: "; 
        cin >> zgjedhja_menu; 
          
        if (zgjedhja_menu == 1){ 
            cout << "Kujdes! Ju duhet te shtoni te dhenat"
                    << "e pikeve per te gjithe studentet!" << endl; 
            for(int i = 0;i < count_n;i++){ 
                fstream file("student.txt"); 
  
  
            if(strcmp(subcode,code1.c_str()) == 0){ 
                        file.seekp(26+37*i,std::ios_base::beg); 
                    cout << "Futni piket e studentit#" << (i+1) << " : "; 
                cin >> mark; 
                file.write(mark.c_str(),2);} 
              
            if(strcmp(subcode,code2.c_str()) == 0){ 
                file.seekp(29+37*i,std::ios_base::beg); 
                cout << "Futni piket e studentit#" << (i+1) << " : "; 
                cin >> mark; 
                file.write(mark.c_str(),2);} 
            } 
              
        } 
  
        // Kjo unaze sherben per te pare vleresimet ne pike te nje studenti.
        
        else if(zgjedhja_menu == 2){ 
        infile.open("student.txt",ios::in); 
        if (strcmp(subcode,code1.c_str()) == 0){ 
            cout << "Nr. Regjistrimi - Piket\n" << endl; 
            while(infile >> data){ 
            cout << data; 
            infile >> data; 
                infile >> data; 
            cout << " - " << data << endl; 
            infile >> data; 
            infile >> data; 
            check = 1; 
            } 
        } 
          
        infile.close(); 
        infile.open("student.txt",ios::in);      
  
        if(strcmp(subcode,code2.c_str()) == 0){ 
            cout << "Nr. Regjistrimi - Piket\n" << endl; 
                while(infile >> data){ 
            cout << data; 
            infile >> data; 
            infile >> data; 
            infile >> data; 
            cout << " - " << data << endl; 
            infile >> data; 
            check = 1; 
            } 
        }} 
          
        infile.close(); 
          
        if (check == 0){ 
            cout << "Nje lende e tille nuk gjendet!" << endl; 
        } 
          
    } 
  
    // Kjo unaze paraqet te dhenat e studenteve nen ID-ne e te njejtit mbikqyres.  
  
    else if (zgjedhja_menu == 4){ 
        char procid[7]; 
        cout << "Futni ID e Mbikqyresit: "; 
        cin >> procid; 
            int check = 1; 
        char temp1[100], temp2[100], temp3[100]; 
        char temp4[100], id[100]; 
        ifstream infile; 
        infile.open("student.txt",ios::in); 
          
        while  (infile >> temp1){ 
            	infile >> temp2;             
        		infile >> temp3; 
        		infile >> temp4; 
        		infile >> id; 
          
        if (strcmp(id,procid) == 0){             
            cout << "\nNumer regjistrimi: " << temp1 << endl; 
            cout << "Emri: " << temp2 << endl; 
            cout << "Piket CSE1001: " << temp3 << endl; 
            cout << "Piket CSE1002: " << temp4 << endl; 
            check = 1; 
        } 
        } 
          
        if (check == 0){ 
            cout << "Kjo ID Mbikqyresi nuk gjendet!" << endl; 
        }} 
      
    // Kjo unaze sherben si nje platforme kontrolli ku admin shikon te gjitha te dhenat ne kete skedar. 
  
    else if(zgjedhja_menu == 5){ 
        char password[25]; 
        cout << "Futni paswordin e admin: "; 
        cin >> password; 
  
        // Vlera e ketij variabli mund te ndryshohet sipas kerkesave tuaja  
        // per passwordin e administratorit. 
  
        string admin_pass = "admin"; 
          
        if (strcmp(password,admin_pass.c_str()) == 0){ 
            cout << "Nr.Regj.       \tEmri\tCSE1001\tCSE1002\tID Mbikqyresi" << endl; 
            ifstream infile; 
            infile.open("student.txt",ios::in); 
            char data[20]; 
              
            while(infile >> data){ 
                cout << data << "\t"; 
                infile >> data; 
                cout << data << "\t"; 
                infile >> data; 
                cout << data << "\t"; 
                infile >> data; 
                cout << data << "\t"; 
                infile >> data; 
                cout << data << endl; 
            } 
        } 
    } 
}} 

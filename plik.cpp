#include <iostream>
#include <fstream>

using namespace std;

struct gdzie_jestem
{
    int znak;
    int slownik;
    int tablica;
}miejsce={};

struct przecinek
{
    bool czy_przecinek_slownik;
    bool czy_przecienk_tablica;
}czy={false,false};


fstream plik;

void otwarcie_pliku(char *input, bool &czy_otwarto);

bool sprawdzenie_pliku();

bool sprawdzenie_slownika();

bool sprawdzenie_tablicy();

int main()
{
    char input[32];
    bool czy_otwarto=false;
    while((cin.getline(input, 32)))
    {
        if(input[0]=='h' || input[0]=='H') 
        {
            cout << "h - pomoc\no nazwa_pliku.format - otwarcie pliku\nc - sprawdzenie poprawnosci otwartego pliku\nCyprian Zasada 193222 ACiR Gr. 4\n";
        }

        else if(input[0] == 'o' || input[0]=='O') 
        {
            otwarcie_pliku(input, czy_otwarto);
        }

        else if(input[0] == 'c' || input[0]=='C')
        {
            if(czy_otwarto==false)
            {
                cout << "Plik nie zostal jeszcze poprawnie otwarty\n";
            }
            else
            {
                if(sprawdzenie_pliku()) cout << "Plik json zapisany poprawnie\n";
                else cout << "Plik json nie zapisany poprawnie\n";
                plik.close();
                czy_otwarto=false;
                miejsce={};
            }
        }
    }

    plik.close();

    return 0;
}

void otwarcie_pliku(char *input, bool &czy_otwarto)
{
    char nazwa_pliku[30] = {0};

    for(int i=2; i<32; i++)
    {
        nazwa_pliku[i-2] = input[i];
    }
    
    plik.open(nazwa_pliku, ios::in);
    if(!plik)
    {
        cout << "Nie udalo sie otworzyc pliku!\n";
        czy_otwarto=false;
    }

    else
    {
        cout << "Plik zostal otwarty\n";
        czy_otwarto=true;
    }
}

bool sprawdzenie_pliku()
{   

    
    char klon;

    plik >> klon;
    miejsce.znak++;


    if(klon == '{')
    {
        miejsce.slownik++;
        if(sprawdzenie_slownika())
        {
            plik>>klon;
            if(plik.eof()) return true;

            else
            {
                cout << "Po zakonczeniu glownego slownika oczekiwano konca pliku.\n";
                return false;
            }
        }
        else 
        {
            cout << "Problem wystapil przy " << miejsce.znak << " znaku. W " << miejsce.tablica << " tablicy i w " << miejsce.slownik << " slowniku." << endl;
            return false;
        }
    }
    else if(klon == '[')
    {
        miejsce.tablica++;
        if(sprawdzenie_tablicy())
        {
            plik>>klon;
            if(plik.eof()) return true;
            else
            {
                cout << "Po zakonczeniu glownej tablicy oczekiwano konca pliku.\n";
                return false;
            }
        }
        else 
        {
            cout << "Problem wystapil przy " << miejsce.znak << " znaku. W " << miejsce.tablica << " tablicy i w " << miejsce.slownik << " slowniku." << endl;
            return false;
        }
    }
    else if(klon=='"')
    {
        while(plik >> klon)
        {
            miejsce.znak++;
            if(plik.eof())
            {
                cout << "Nieoczekiwany koniec pliku!\n";
                return false;
            }
            if(klon == '"')
            {
                plik>>klon;
                miejsce.znak++;
                if(plik.eof()) return true;
                else
                {
                    cout << "Plik bez tablic i slownikow moze zawierac tylko jedna wartosc.\n";
                    return false;
                }
            }
            else if(klon=='\\')
            {
                plik>>klon;
                miejsce.znak++;
                continue;
            }
        }
    }
   
    else if((klon>='0' && klon<='9') || klon=='-')
    {    
        bool czy_zero=false;
        
        if(klon=='-')
        {
            plik >> klon;
            miejsce.znak++;
            if(plik.eof())
            {
                cout << "Nie podano wartosci liczby ujemnej.\n";
                return false;
            }
        }

        if(klon=='0')
        {
            czy_zero=true;
        }
   
        bool czy_kropka=false;
        
        while(plik>>klon)
        {
            miejsce.znak++;
            if(plik.eof())
            {
            return true;
            }
            else if(klon=='.')
            {
                if(czy_kropka==true)
                {
                    cout << "Podwojna kropka w zapisie liczbowym wartosci.\n";
                    return false;
                }
                else
                {
                    czy_kropka=true;
                    plik>>klon;
                    if(plik.eof()) return false;
                }
            }

            else if(klon>='0' && klon<='9')
            {
                if(czy_kropka==false && czy_zero==true)
                {
                    cout << "Wartosc liczbowa rozpoczeta zerem.\n";
                    return false;
                }
            }

            else 
                {
                cout << "Blad w wartosci liczbowej.\n";
                return false;
                }
        }
    }
    else if(klon=='t')
    {  
        char rue[3];

        for(int i=0; i<3; i++)
        {
            plik >> rue[i];
            miejsce.znak++;
            if(plik.eof())
    {
        cout << "Nieoczekiwany koniec pliku!\n";
        return false;
    }
        }

        if(!(rue[0]=='r' && rue[1]=='u' && rue[2]=='e')) {
            cout << "Niepoprawna wartosc elemntu slownika, zaczynajaca sie na t.\n"; 
            return false;}

        plik >> klon;
        miejsce.znak++;
        if(plik.eof())
    {
        return true;
    }

        else {
            cout << "Niepoprawne zakonczenie elemntu true.\n";
            return false;
            }

    }
    else if(klon=='f')
    {
        char alse[4];

        for(int i=0; i<4; i++)
        {
            plik >> alse[i];
            miejsce.znak++;
            if(plik.eof())
    {
        cout << "Nieoczekiwany koniec pliku!\n";
        return false;
    }
        }

        if(!(alse[0]=='a' && alse[1]=='l' && alse[2]=='s' && alse[3]=='e')) {
            cout << "Niepoprawna wartosc elemntu slownika, zaczynajaca sie na f.\n"; 
            return false;}

        plik >> klon;
        miejsce.znak++;
        if(plik.eof())
    {
        return true;
    }

        else {
            cout << "Niepoprawne zakonczenie elemntu tablicy false.\n";
            return false;
            }

    }
    else if(klon=='n')
    {
        char ull[3];

        for(int i=0; i<3; i++)
        {
            plik >> ull[i];
            miejsce.znak++;
            if(plik.eof())
    {
        cout << "Nieoczekiwany koniec pliku!\n";
        return false;
    }
        }

        if(!(ull[0]=='u' && ull[1]=='l' && ull[2]=='l')) {
            cout << "Niepoprawna wartosc elemntu slownika, zaczynajaca sie na n.\n"; 
            return false;}

        plik >> klon;
        miejsce.znak++;
        if(plik.eof())
    {
        return true;
    }
        else {
            cout << "Niepoprawne zakonczenie elemntu tablicy null.\n";
            return false;
            }
    }

    else
    {
        cout << "Blad na samym poczatku\n";
        return false;
    }    
    if (plik.eof()) return true;

    return false;

}

bool sprawdzenie_slownika()
{
    char klon;

    plik >> klon;
    miejsce.znak++;
    if(plik.eof())
    {
        cout << "Nieoczekiwany koniec pliku!\n";
        return false;
    }

    if(klon=='}')
    {
        
        miejsce.slownik--;
        if(czy.czy_przecinek_slownik) return false;
        return true;
    }


    if(klon != '"') 
    {
        cout << "Oczekiwano znaku \". \n";
        return false;
    }

    while(plik >> klon)
    {
        miejsce.znak++;
        if(plik.eof())
    {
        cout << "Nieoczekiwany koniec pliku!\n";
        return false;
    }
        if(klon == '"') break;
        else if(klon=='\\')
            {
                plik>>klon;
                miejsce.znak++;
                continue;
            }
    }

    plik >> klon;
    miejsce.znak++;
    if(plik.eof())
    {
        cout << "Nieoczekiwany koniec pliku!\n";
        return false;
    }

    if(klon != ':') 
    {
        cout << "Oczekiwano znaku :.\n";
        return false;
    }

    plik >> klon;
    miejsce.znak++;
    if(plik.eof())
    {
        cout << "Nieoczekiwany koniec pliku!\n";
        return false;
    }

    if(klon == '"')
    {
        while(plik >> klon)
        {
            miejsce.znak++;
            if(plik.eof())
            {
                cout << "Nieoczekiwany koniec pliku!\n";
                return false;
            }
            if(klon == '"') break;
            else if(klon=='\\')
            {
                plik>>klon;
                miejsce.znak++;
                continue;
            }
        }

        plik >> klon;
        miejsce.znak++;
        if(plik.eof())
        {
            cout << "Nieoczekiwany koniec pliku!\n";
            return false;
        }
        
        if(klon == ',')
        {
            czy.czy_przecinek_slownik=true;
            return sprawdzenie_slownika();
            //zacznij od nowa
        }
        else if(klon == '}') 
        {
            miejsce.slownik--;
            return true;
        }

        else 
        {
            cout << "Niepoprawne zakonczenie wartosci elementu w slowniku.\n";
            return false;
        }
    }
    else if(klon == '{')
    {
        miejsce.slownik++;
        czy.czy_przecinek_slownik=false;
        if(!sprawdzenie_slownika()) return false;
        
        plik >> klon;
        miejsce.znak++;
        if(plik.eof())
    {
        cout << "Nieoczekiwany koniec pliku!\n";
        return false;
    }
        
        if(klon == ',')
        {
            czy.czy_przecinek_slownik=true;
            return sprawdzenie_slownika();
            //zacznij od nowa
        }
        else if(klon == '}') 
        {
            miejsce.slownik--;
            return true;
        }

        else 
        {
            cout << "Niepoprawne zakonczenie slownika.\n";
            return false;
        }
    }
    else if(klon == '[')
    {
        miejsce.tablica++;

        czy.czy_przecienk_tablica=false;
        
        if(!sprawdzenie_tablicy()) 
        {
            return false;
        }
        
        plik >> klon;
        miejsce.znak++;
        if(plik.eof())
    {
        cout << "Nieoczekiwany koniec pliku!\n";
        return false;
    }
        
        if(klon == ',')
        {
            czy.czy_przecinek_slownik=true;
            return sprawdzenie_slownika();
        }
        else if(klon == '}') 
        {
            miejsce.slownik--;
            return true;
        }

        else {
            cout << "Nieoczekiwane zakonczenie slownika.\n";
            return false;
            }
    }
    
    else if((klon>='0' && klon<='9') || klon=='-')
    {    
        bool czy_zero=false;
        
        if(klon=='-')
        {
            plik>>klon;
            miejsce.znak++;
            if(plik.eof())
            {
                cout << "Nieoczekiwany koniec pliku.\n";
                return false;
            }
        }

        if(klon=='0')
        {
            czy_zero=true;
        }
        
        bool czy_kropka=false;
        
        while(plik>>klon)
        {
            miejsce.znak++;
            if(plik.eof())
            {
            cout << "Nieoczekiwany koniec pliku!\n";
            return false;
            }

            if(klon == ',')
            {
                czy.czy_przecinek_slownik=true;
                return sprawdzenie_slownika();
            }

            else if(klon == '}') 
            {
                miejsce.slownik--;
                return true;
            }

            else if(klon=='.')
            {
                if(czy_kropka==true)
                {
                    cout << "Podwojna kropka w zapisie liczbowym wartosci w slowniku.\n";
                    return false;
                }
                else
                {
                    czy_kropka=true;
                    plik>>klon;
                    miejsce.znak++;
                    if(!(klon>='0' && klon<='9'))
                    {
                        cout << "Oczekiwano wartosci po przecinku w slowniku.\n";
                        return false;
                    }
                }
            }

            else if(klon>='0' && klon<='9')
            {
                if(czy_kropka==false && czy_zero==true)
                {
                    cout << "Wartosc liczbowa rozpoczeta zerem.\n";
                    return false;
                }
            }

            else {
                cout << "Blad w wartosci liczbowej elementu slownika.\n";
                return false;
                }
        }
    }

    else if(klon=='t')
    {  
        char rue[3];

        for(int i=0; i<3; i++)
        {
            plik >> rue[i];
            miejsce.znak++;
            if(plik.eof())
    {
        cout << "Nieoczekiwany koniec pliku!\n";
        return false;
    }
        }

        if(!(rue[0]=='r' && rue[1]=='u' && rue[2]=='e')) {
            cout << "Niepoprawna wartosc elemntu slownika, zaczynajaca sie na t.\n"; 
            return false;}

        plik >> klon;
        miejsce.znak++;
        if(plik.eof())
    {
        cout << "Nieoczekiwany koniec pliku!\n";
        return false;
    }

        if(klon == ',')
        {
            czy.czy_przecinek_slownik=true;
            return sprawdzenie_slownika();
        }

        else if(klon == '}') 
        {
            miejsce.slownik--;
            return true;
        }

        else {
            cout << "Niepoprawne zakonczenie elemntu tablicy true.\n";
            return false;
            }

    }
    else if(klon=='f')
    {
        char alse[4];

        for(int i=0; i<4; i++)
        {
            plik >> alse[i];
            miejsce.znak++;
            if(plik.eof())
    {
        cout << "Nieoczekiwany koniec pliku!\n";
        return false;
    }
        }

        if(!(alse[0]=='a' && alse[1]=='l' && alse[2]=='s' && alse[3]=='e')) {
            cout << "Niepoprawna wartosc elemntu slownika, zaczynajaca sie na f.\n"; 
            return false;}

        plik >> klon;
        miejsce.znak++;
        if(plik.eof())
    {
        cout << "Nieoczekiwany koniec pliku!\n";
        return false;
    }

        if(klon == ',')
        {
            czy.czy_przecinek_slownik=true;
            return sprawdzenie_slownika();
        }

        else if(klon == '}') 
        {
            miejsce.slownik--;
            return true;
        }

        else {
            cout << "Niepoprawne zakonczenie elemntu tablicy false.\n";
            return false;
            }

    }
    else if(klon=='n')
    {
        char ull[3];

        for(int i=0; i<3; i++)
        {
            plik >> ull[i];
            miejsce.znak++;
            if(plik.eof())
    {
        cout << "Nieoczekiwany koniec pliku!\n";
        return false;
    }
        }

        if(!(ull[0]=='u' && ull[1]=='l' && ull[2]=='l')) {
            cout << "Niepoprawna wartosc elemntu slownika, zaczynajaca sie na n.\n"; 
            return false;}

        plik >> klon;
        miejsce.znak++;
        if(plik.eof())
    {
        cout << "Nieoczekiwany koniec pliku!\n";
        return false;
    }

        if(klon == ',')
        {
            czy.czy_przecinek_slownik=true;
            return sprawdzenie_slownika();
        }

        else if(klon == '}') 
        {
            miejsce.slownik--;
            return true;
        }

        else {
            cout << "Niepoprawne zakonczenie elemntu tablicy null.\n";
            return false;
            }
    }
    
    else {
        cout << "Problem przy sprawdzeniu slownika.\n";
        return false;}

    return false;

}

bool sprawdzenie_tablicy()
{
    char klon;
    
    plik >> klon;
    miejsce.znak++;
    if(plik.eof())
    {
        cout << "Nieoczekiwany koniec pliku!\n";
        return false;
    }

    if(klon=='"')
    {
        while(plik>>klon)
        {
            miejsce.znak++;
            if(plik.eof())
            {
                cout << "Nieoczekiwany koniec pliku!\n";
                return false;
            }
            if(klon == '"') break;
            else if(klon=='\\')
            {
                plik>>klon;
                miejsce.znak++;
                continue;
            }

        }

        plik >> klon;
        miejsce.znak++;
        if(plik.eof())
    {
        cout << "Nieoczekiwany koniec pliku!\n";
        return false;
    }

        if(klon == ',')
        {
            czy.czy_przecienk_tablica=true;
            return sprawdzenie_tablicy();
            
        }

        else if(klon == ']')
        {
            miejsce.tablica--;
            return true;
        }

        else {
            cout << "Blad w wartosci tablicy w cudzyslowie.\n";
            return false;}
    }
    else if(klon=='{')
    {
        miejsce.slownik++;
        czy.czy_przecinek_slownik=false;

        if(!sprawdzenie_slownika()) return false;

        plik >> klon;
        miejsce.znak++;
        if(plik.eof())
    {
        cout << "Nieoczekiwany koniec pliku!\n";
        return false;
    }

        if(klon == ',')
        {
            czy.czy_przecienk_tablica=true;
            return sprawdzenie_tablicy();
        }

        else if(klon == ']')
        {
            miejsce.tablica--;
            return true;
        }

        else {
            cout << "Blad przy zakonczeniu slownika w tablicy.\n";
            return false;}
    }
    else if(klon=='[')
    {
        miejsce.tablica++;

        czy.czy_przecienk_tablica=false;

        if(!sprawdzenie_tablicy()) return false;

        plik >> klon;
        miejsce.znak++;
        if(plik.eof())
    {
        cout << "Nieoczekiwany koniec pliku!\n";
        return false;
    }

        if(klon == ',')
        {
            czy.czy_przecienk_tablica=true;
            return sprawdzenie_tablicy();
        }

        else if(klon == ']')
        {
            miejsce.tablica--;
            return true;
        }

        else {
            cout << "Blad przy zakonczeniu listy w liscie.\n";
            return false;}
    }
    else if((klon>='0' && klon<='9') || klon=='-')
    {    
        bool czy_zero=false;
        
        if(klon=='-')
        {
            plik>>klon;
            miejsce.znak++;
            if(plik.eof())
            {
                cout << "Nieoczekiwany koniec pliku.\n";
                return false;
            }
        }

        if(klon=='0')
        {
            czy_zero=true;
        }

        bool czy_kropka=false;
        
        while(plik>>klon)
        {
            miejsce.znak++;
            if(plik.eof())
            {
                cout << "Nieoczekiwany koniec pliku!\n";
                return false;
            }

            if(klon == ',')
            {
                czy.czy_przecienk_tablica=true;
                return sprawdzenie_tablicy();
            }

            else if(klon=='.')
            {
                if(czy_kropka==true)
                {
                    cout << "Podwojna kropka w zapisie liczbowym wartosci w tablicy.\n";
                    return false;
                }
                else
                {
                    czy_kropka=true;
                    plik>>klon;
                    miejsce.znak++;
                    if(!(klon>='0' && klon<='9'))
                    {
                        cout << "Oczekiwano wartosci po przecinku w tablicy.\n";
                        return false;
                    }
                }
            }

            else if(klon == ']')
            {
                miejsce.tablica--;
                return true;
            }

            else if(klon>='0' && klon<='9') 
            {
                if(czy_kropka==false && czy_zero==true)
                {
                    cout << "Wartosc liczbowa rozpoczeta zerem.\n";
                    return false;
                }
            }

            else
            { 
                cout << "Blad przy wartosci liczbowej w liscie.\n";
                return false;
            }
        }
    }
    else if(klon == ']')
    {
        miejsce.tablica--;
        if(czy.czy_przecienk_tablica) return false;
        return true;
    }
    else if(klon=='t')
    {  
        char rue[3];

        for(int i=0; i<3; i++)
        {
            plik >> rue[i];
            miejsce.znak++;
            if(plik.eof())
    {
        cout << "Nieoczekiwany koniec pliku!\n";
        return false;
    }
        }

        if(!(rue[0]=='r' && rue[1]=='u' && rue[2]=='e')) {
            cout << "Niepoprawna wartosc elemntu tablicy, zaczynajaca sie na t.\n"; 
            return false;}

        plik >> klon;
        miejsce.znak++;
        if(plik.eof())
    {
        cout << "Nieoczekiwany koniec pliku!\n";
        return false;
    }

        if(klon == ',')
        {
            czy.czy_przecienk_tablica=true;
            return sprawdzenie_tablicy();
        }

        else if(klon == '}') 
        {
            miejsce.slownik--;
            return true;
        }

        else {
            cout << "Niepoprawne zakonczenie wartosci true w tablicy.\n";
            return false;}

    }
    else if(klon=='f')
    {
        char alse[4];

        for(int i=0; i<4; i++)
        {
            plik >> alse[i];
            miejsce.znak++;
            if(plik.eof())
    {
        cout << "Nieoczekiwany koniec pliku!\n";
        return false;
    }
        }

        if(!(alse[0]=='a' && alse[1]=='l' && alse[2]=='s' && alse[3]=='e')) {
            cout << "Niepoprawna wartosc elemntu tablicy, zaczynajaca sie na f.\n"; 
            return false;}

        plik >> klon;
        miejsce.znak++;
        if(plik.eof())
    {
        cout << "Nieoczekiwany koniec pliku!\n";
        return false;
    }

        if(klon == ',')
        {
            czy.czy_przecienk_tablica=true;
            return sprawdzenie_tablicy();
        }

        else if(klon == '}') 
        {
            miejsce.slownik--;
            return true;
        }

        else {
            cout << "Niepoprawne zakonczenie wartosci false w tablicy.\n";
            return false;}

    }
    else if(klon=='n')
    {
        char ull[3];

        for(int i=0; i<3; i++)
        {
            plik >> ull[i];
            miejsce.znak++;
            if(plik.eof())
    {
        cout << "Nieoczekiwany koniec pliku!\n";
        return false;
    }
        }

        if(!(ull[0]=='u' && ull[1]=='l' && ull[2]=='l')) {
            cout << "Niepoprawna wartosc elemntu tablicy, zaczynajaca sie na n.\n"; 
            return false;}

        plik >> klon;
        miejsce.znak++;
        if(plik.eof())
    {
        cout << "Nieoczekiwany koniec pliku!\n";
        return false;
    }

        if(klon == ',')
        {
            czy.czy_przecienk_tablica=true;
            return sprawdzenie_tablicy();
        }

        else if(klon == '}') 
        {
            miejsce.slownik--;
            return true;
        }

        else {
            cout << "Niepoprawne zakonczenie wartosci null w tablicy.\n";
            return false;}
    }

    else {
        cout << "Problem przy sprawdzeniu tablicy.\n";
        return false;}

    return false;

}
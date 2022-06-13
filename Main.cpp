#include <iostream>

using namespace std;

int first;
int second;
int wynik;
float wynik_fl;
int reszta;

float Dodawanie();
float Odejmowanie();
float Mnozenie();
float Dzielenie();
float Potega();
float Square();
float Logarytm();
float menu();
void Type();

int main()
{
  Type();

  return 0;
}


float menu()
{
    int x;
    cout<<"Wybierz operacje: "<<endl;
    cout<<"Dodawanie - 1"<<endl<<"Odejmowanie - 2"<<endl<<"Moznenie - 3"<<endl<<"Dzielenie - 4"<<endl<<"Potega - 5"<<endl<<"Pierwiastek kwadratowy - 6"<<endl<<"Logarytm naturalny - 7"<<endl<<"Powrot - 0"<<endl;
    cin >>x;
    switch(x)
    {
        case 0:
            return 0;
        case 1:
            return Dodawanie();
        case 2:
            return Odejmowanie();
        case 3:
            return Mnozenie();
        case 4:
            return Dzielenie();
        case 5:
            return Potega();
        case 6:
            return Square();
        case 7:
            return Logarytm();
        default:
            cout<<"Zly wybor!";
            return 0;
    }
}

void Type()
{
    cout<<endl<<"Witamy w kalkulatorze!"<<endl;
    int x;

while(true)
{
    cout<<"W jakim systemie chcesz podać liczbe?"<<endl;
    cout<<"Dziesietnym - 1"<<endl<<"Szestnastkowym - 2"<<endl<<"Wyjscie - 0"<<endl;
    cin>>x;

    switch(x)
    {
        case 0:
            return;
        case 1:{
            cout<<"Podaj liczby w dziesietnym: "<<endl;
            cin>>first;
            cin>>second;
            cout<<endl;
            float z = menu();
            cout<<endl<<"Wynik w dziesietnym: ";
            cout<<z<<endl;
            wynik = 0;}
            break;
        case 2:{
            cout<<"Podaj liczby w szestnastkowym: "<<endl;
            cin>>hex>>first;
            cin>>hex>>second;
            cout<<endl;
            float z = menu();
            cout<<endl<<"Wynik w szestnastkowym: ";
            cout<<hex<<z<<endl;
            wynik = 0;}
            break;
        default:
            cout<<"Nie ma takiej opcji!"<<endl;
            break;
    }
}
}

float Dodawanie()
{
   __asm__  ( 
    "movl %1, %%eax;"
    "movl %2, %%ebx;"
    "addl %%ebx, %%eax;"
    "movl %%eax, %0;" 
    
    : "=a" (wynik) 
    : "a" (first) , "b" (second)   
    );

    wynik_fl = (float)wynik;
    return wynik_fl;
}



float Odejmowanie()
{
    __asm__ (
        "movl %1, %%eax;"
        "movl %2, %%ebx;"
        "subl %%ebx, %%eax;"
        "movl %%eax, %0;"

        : "=a" (wynik) 
        : "a" (first) , "b" (second) 
    );

    wynik_fl = (float)wynik;
    return wynik_fl;
}

float Mnozenie()
{
    __asm__(
        "movl %1, %%eax;"
        "movl %2, %%ebx;"
        "imull %%ebx, %%eax;"
        "movl %%eax, %0;"

        : "=a" (wynik) 
        : "a" (first) , "b" (second) 
    );

    wynik_fl = (float)wynik;
    return wynik_fl;
}

float Dzielenie()
{
    __asm__(
        "movl $0x0, %%edx;"
        "movl %2, %%eax;"
        "movl %3, %%ebx;"
        "idivl %%ebx;"

        : "=a" (wynik), "=d" (reszta)
        : "a" (first), "b" (second)
    );

    cout<<endl<<"Reszta: "<<reszta;
    wynik_fl = (float)wynik;
    return wynik_fl;
}

float Potega()
{
    __asm__(
    "movl %1, %%eax;"
    "movl %%eax, %%ecx;"
    "movl %2, %%ebx;"
    "cmpl $0, %%ebx;"
    "jne notone;"
    "movl $1, %%ecx;"
    "jmp end;"
    "notone:"
    "cmpl $1, %%ebx;"
    "je end;"
    "decl %%ebx;"
    "loop:"
    "imull %%eax, %%ecx;"
    "decl %%ebx;"
    "cmpl $0, %%ebx;"
    "jne loop;"
    "end:"
    "movl %%ecx, %0;"

    : "=c" (wynik) 
    : "a" (first) , "b" (second) 
    );

    wynik_fl = (float)wynik;
    return wynik_fl;
}


float Square()
{
    float first_fl = (float)first;
    
    __asm__(
       "fld %1;"
       "fsqrt;"
       "fstp %0;"

       : "=m" (wynik_fl)
       : "g" (first_fl)
    );

    return wynik_fl;
}

float Logarytm()
{
    float first_fl = (float)first;

    __asm__(
        "fld1;"
        "fld %1;"
        "fyl2x;"
        "fldl2e;"
        "fdivrp;"
        "fstp %0;"

        : "=m" (wynik_fl)
        : "g" (first_fl)
    );

    return wynik_fl;
}
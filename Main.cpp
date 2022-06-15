#include <iostream>

using namespace std;

int first;
double first_fl;
double second_fl;
int second;
int wynik;
double wynik_fl;
int reszta;

double Dodawanie();
double Odejmowanie();
double Mnozenie();
double Dzielenie();
double Potega();
double Square();
double Logarytm();
double sin();
double cos();
double ctg();
double tg();
double menu();
void Type();

int main()
{
  Type();

  return 0;
}


double menu()
{
    char x;
    cout<<"Wybierz operacje: "<<endl;
    cout<<"Dodawanie - 1"<<endl<<"Odejmowanie - 2"<<endl<<"Moznenie - 3"<<endl<<"Dzielenie - 4"<<endl<<"Potega - 5"<<endl<<"Pierwiastek kwadratowy - 6"<<endl<<"Logarytm naturalny - 7"<<endl;
    cout<<"Sinus - 8"<<endl<<"Cosinus - 9"<<endl<<"Tangens - t"<<endl<<"Cotangens - c"<<endl<<"Powrot - 0"<<endl;
    cin >>x;
    switch(x)
    {
        case '0':
            return 0;
        case '1':
            return Dodawanie();
        case '2':
            return Odejmowanie();
        case '3':
            return Mnozenie();
        case '4':
            return Dzielenie();
        case '5':
            return Potega();
        case '6':
            return Square();
        case '7':
            return Logarytm();
        case '8':
            return sin();
        case '9':
            return cos();
        case 't':
            return tg();
        case 'c':
            return ctg();
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
    cout<<"Dziesietnym - 1"<<endl<<"Szestnastkowym - 2 (UWAGA! Przy skompliwanych operacjach traci dokładność!)"<<endl<<"Wyjscie - 0"<<endl;
    cin>>x;

    switch(x)
    {
        case 0:
            return;
        case 1:{
            cout<<"Podaj liczby w dziesietnym: "<<endl;
            cin>>first_fl;
            cin>>second_fl;
            cout<<endl;
            double z = menu();
            cout<<endl<<"Wynik w dziesietnym: ";
            cout<<z<<endl;
            wynik_fl = 0;
            }
            break;
        case 2:{
            cout<<"Podaj liczby w szestnastkowym: "<<endl;
            cin>>hex>>first;
            cin>>hex>>second;
            first_fl = (double)first;
            second_fl = (double)second;
            cout<<endl;
            double z = menu();
            int wyn = (int)z;
            cout<<endl<<"Wynik w szestnastkowym: ";
            cout<<hex<<wyn<<endl;
            wynik_fl = 0;
            }
            break;
        default:
            cout<<"Nie ma takiej opcji!"<<endl;
            break;
    }
}
}

double Dodawanie()
{
    __asm__(
        "fldl %1;"
        "fldl %2;"
        "faddp;"
        "fstpl %0;"

       : "=m" (wynik_fl)
       : "m" (first_fl), "m" (second_fl)
    );

    return wynik_fl;
}

double Odejmowanie()
{
    __asm__(
        "fldl %1;"
        "fldl %2;"
        "fsubrp;"
        "fstpl %0;"

       : "=m" (wynik_fl)
       : "m" (first_fl), "m" (second_fl)
    );

    return wynik_fl;
}

double Mnozenie()
{

    __asm__(
        "fldl %1;"
        "fldl %2;"
        "fmulp;"
        "fstpl %0;"

       : "=m" (wynik_fl)
       : "m" (first_fl), "m" (second_fl)
    );

    return wynik_fl;
}

double Dzielenie()
{
     __asm__(
        "fldl %1;"
        "fldl %2;"
        "fdivrp;"
        "fstpl %0;"

       : "=m" (wynik_fl)
       : "m" (first_fl), "m" (second_fl)
    );

    return wynik_fl;
}

double Potega()
{
    /*
    __asm__(

        "fld1;"
        "cmpl $0, %2;" //??
        "jg loop;"
        "je ending;"   //jesli zero to zwroci 1
        "fldl %1;"   //jesli mniejszy od zera to odwrotnosc
        "fdivrp;"
        "fstpl %1;"
        "fld1;"

        "movl %2, %%eax;"
        "imull $-1, %%eax;"
        "movl %%eax, %2;"

        "loop:"
        "fldl %1;"
        "fmulp;"
        "fstpl %0;"

        "fldl %2;"
        "fld1;"
        "fsubrp;"
        "fstpl %2;"
        "fldl %1;"
        "fldl %0;"

        "cmpl $0, %2;" //??
        "jne loop;"

        "ending:"
        "fstpl %0;"

        : "=m" (wynik_fl)
        : "m" (first_fl), "m" (second_fl)
    );
    return wynik_fl;
    */
    
    first = (int) first_fl;
    second = (int) second_fl;

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

    wynik_fl = (double)wynik;
    return wynik_fl;
}


double Square()
{
    __asm__(
       "fldl %1;"
       "fsqrt;"
       "fstpl %0;"

       : "=m" (wynik_fl)
       : "m" (first_fl)
    );

    return wynik_fl;
}

double Logarytm()
{
    __asm__(
        "fld1;"
        "fldl %1;"
        "fyl2x;"
        "fldl2e;"
        "fdivrp;"
        "fstpl %0;"

        : "=m" (wynik_fl)
        : "m" (first_fl)
    );

    return wynik_fl;
}

double sin()
{
    __asm__(
        "fldl %1;"
        "fsin;"
        "fstpl %0;"

        : "=m" (wynik_fl)
        : "m" (first_fl)
    );

    return wynik_fl;
}

double cos()
{
    __asm__(
        "fldl %1;"
        "fcos;"
        "fstpl %0;"

        : "=m" (wynik_fl)
        : "m" (first_fl)
    );

    return wynik_fl;
}

double tg()
{
    __asm__(
        "fldl %1;"
        "fcos;"
        "fldl %1;"
        "fsin;"
        "fdivp;"
        "fstpl %0;"

        : "=m" (wynik_fl)
        : "m" (first_fl)
    );

    return wynik_fl;
}

double ctg()
{
    __asm__(
        "fldl %1;"
        "fsin;"
        "fldl %1;"
        "fcos;"
        "fdivp;"
        "fstpl %0;"

        : "=m" (wynik_fl)
        : "m" (first_fl)
    );

    return wynik_fl;
}
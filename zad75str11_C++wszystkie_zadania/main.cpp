#include <iostream>
#include <algorithm>
#include <fstream>
using namespace std;

int main()
{
    string nazwa{}, tekst{};
    char znak{};
    int ilosc{};
    system("cls");
    cout << "Podaj nazwe pliku wejsciowego: ";
    getline(cin,nazwa);
    fstream dane(nazwa.c_str(),ios::in);
    if (!dane.good())
    {
        cout << "Problem z plikiem";
        return -1;
    }
    cout << "Podaj znak do sprawdzenia: ";
    cin.get(znak);
    while(getline(dane,tekst))
    {
    ilosc+= count (tekst.begin(), tekst.end(),znak);
    }
    cout << "Liczba znakow \"" << znak << "\" w podanym ciagu wynosi: " << ilosc << "\n";
    dane.close();
    return 0;
}

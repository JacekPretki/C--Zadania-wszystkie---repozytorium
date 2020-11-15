#include <iostream>
#include <fstream>
#include <regex>
#include <vector>
using namespace std;

ifstream dane;
string zmienna{};
size_t dlugosc{};
vector<char>exclude{};

regex str_expr("[^a-zA-Z0-9_$]");//wykluczenie wszystkich dozwolonych znakow
regex str_expr2("[_$]");//znaki specjalne
regex str_expr3("[0-9]");//cyfry
regex str_expr4("[AaEeIiOoUuYy]");//samogloski w alfabecie angielskim
smatch m;

void usuwanie(string &zmienna, vector<char>&exclude, regex e, int typ)
{
    exclude.clear();//zerowanie tablicy z aktualnymi znakami do usuniecia
    regex_iterator<string::iterator>rit(zmienna.begin(), zmienna.end(),e);
    regex_iterator<string::iterator>rend;
    while (rit!=rend)
    {
        string additional = rit->str();//wynikiem jest obiekt typu string
        char c = additional.at(0);//konwersja do char
        exclude.push_back(c);
        ++rit;
    }
    if (typ)//metoda iteracji zmiennej - od pocz¹tku lub od konca
    {
        for (vector<char>::reverse_iterator it = exclude.rbegin(); it != exclude.rend(); ++it)
        {
            for (auto itr=zmienna.begin(); itr!=zmienna.end();itr++)
            {
                if (*itr==*it)
                {
                    zmienna.erase(itr);
                    break;
                }
            }
            if (zmienna.size()==dlugosc)//jesli dlugosc zmienne jest spelniona zakoncz funkcje
                return;
        }
    }
    else
    {
        for (vector<char>::reverse_iterator it = exclude.rbegin(); it != exclude.rend()-1; ++it)
        {
            reverse(zmienna.begin(), zmienna.end());//odwrocenie ciagu w celu iteracji od konca
            for (auto itr=zmienna.begin(); itr!=zmienna.end();itr++)
            {
                if (*itr==*it)
                {
                    zmienna.erase(itr);
                    break;
                }
            }
            reverse(zmienna.begin(), zmienna.end());//przywrocenie normalnej kolejnosci ciagu
            if (zmienna.size()==dlugosc)
                return;
        }
    }
}
//---------------------------------------
string konwersja(string zmienna, int dlugosc)
{
    if (regex_search(zmienna,m,str_expr))//jesli istnieja dodatkowe znaki oprocz dozwolonych - zakoncz
        return "0";
    if (int(zmienna.size())<=dlugosc)//jesli zmienna miejsci sie w zakladanej dlugosc - zakoncz
        return zmienna;
    usuwanie(zmienna, exclude, str_expr2,1);//usuwanie znaków specjalnych
    usuwanie(zmienna, exclude, str_expr3,1);//usuwanie cyfr
    usuwanie(zmienna, exclude, str_expr4,0);//usuwanie wszystkich-1 samoglosek
    for (string::reverse_iterator itr=zmienna.rbegin()+2; itr!=zmienna.rend(); itr++)
    {
        if (int(zmienna.size())==dlugosc)
            break;
        zmienna.erase(itr.base());//usuwanie znakow od przedostatniego do zakladanej dlugosci
    }
    return zmienna;
}
//-----------------------
int main()
{
    dane.open("dane.txt", ios::in);
    while (dane>>dlugosc >> zmienna)
        cout << konwersja(zmienna, dlugosc) << "\n";//wypisanie wyniku na ekran
    dane.close();
    return 0;
}

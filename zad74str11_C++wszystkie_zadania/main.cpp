#include <iostream>
//#include <io.h>
#include <fcntl.h>
#include <cstdlib>
#include <ctime>
#include <array>
#include <Windows.h>
#include <fstream>
using namespace std;

string nazwaPliku="Statki - plansze.txt";
const int wysokosc=10*2+2, szerokosc=10*6+2, rozmiar=10;
int tablica[wysokosc][szerokosc];
array<int,rozmiar*rozmiar>pole{0};
array<int,rozmiar*rozmiar>robocza{0};
char statek[] {'_','_','/','\\','_','_','\\','_','_','_','_','/'};
int kolor_ramki=14, kolor_loga=10, kolor_reset=7, kolor_x_kor=03, kolor_y_kor=13, kolor_trafiony=04, kolor_nietrafiony=03;

void SetCursorPosition(int x, int y)
{
    HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos = {x,y};
    SetConsoleCursorPosition(output, pos);
}

void changeColor(int desiredColor)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), desiredColor);
}

void wyswietlPlansze()
{
    changeColor(kolor_loga);
    wcout<<"      ~~~~$MQ~~~EEEEEEEE~~~~EE@~~~EEEEEEEE~@EE~~~EEE~@EE~~~\n";
    wcout<<"      ~~F'....T~........$~~[...~~~........$[..E~'..>@[..#~~\n";
    wcout<<"      #@.._y/.~~(,,...,,R~@....$~~(,,...,,R[..E[...@~[..#~~\n";
    wcout<<"      ~@``^9EwyE~~#``T~~~~F``;`>~~~~#``T~~~[``P``.#~~[``#~~\n";
    wcout<<"      ~~i```~^*~~~#``T~~~~!``p`~@~~~#``T~~~[`````T~~~[``#~~\n";
    wcout<<"      ~~~y;```~#~~#``T~~~#``j#``T~~~#``T~~~[`````~#~~[``#~~\n";
    wcout<<"      ~@**##z``T~~#``T~~~F``''``'~~~#``T~~~[```4``>~~[``#~~\n";
    wcout<<"      ~&``?EP``d~~#``T~~~!```````#~~#``T~~~[``g~/``T~[``#~~\n";
    wcout<<"      EEi....._E~~#..T~~#..jgg&..J~~#..T~~~[..E~&...~[..#~~\n";
    wcout<<"      ~~~yjjjy@~~~Ejjd~~Ejjd~~@jjj~~Ejjd~~~yjj@~~ujjZyjjE~~\n";
    changeColor(kolor_reset);
}
void renderujPole()
{
    pole.fill(0);
    for (int i=0; i<rozmiar; i++)
    {
        do
        {
            int wartosc=rand()%100;
            if (pole.at(wartosc)==0)
            {
                pole.at(wartosc)=1;
                break;
            }
        }
        while (true);

    }
}

void x_koordynaty()
{
    changeColor(kolor_x_kor);
    char c='A';
    wcout << "  ";
    for (int i=0; i<rozmiar; i++)
    {
        wcout << "   " << c << "  ";
        c++;
    }
    wcout << " " << endl;
    changeColor(kolor_reset);
}
void y_koordynaty(int i)
{
    if (i%2==0 && i!=0)
    {
        changeColor(kolor_y_kor);
        if (i/2>9)
            wcout << i/2;
        else
            wcout << i/2 << " ";
        changeColor(kolor_reset);
    }
    else
        wcout << "  ";
}

void ekran()
{
    SetCursorPosition(0,0);
    wyswietlPlansze();
    x_koordynaty();

    char c='1';
    for (int i=0; i<wysokosc; i++)
    {
        y_koordynaty(i);
        for (int j=0; j<szerokosc; j++)
        {
            if (i==0 && j==0)
            {
                changeColor(kolor_ramki);
                wcout << L"\u250c";
                changeColor(kolor_reset);
                continue;
            }
            if (i==0 && j==szerokosc-1)
            {
                changeColor(kolor_ramki);
                wcout << L"\u2510 ";
                changeColor(kolor_reset);
                y_koordynaty(i);
                wcout << "\n";
                continue;
            }
            if (i==wysokosc-1 && j==0)
            {
                changeColor(kolor_ramki);
                wcout << L"\u2514";
                changeColor(kolor_reset);
                continue;
            }
            if (i==wysokosc-1 && j==szerokosc-1)
            {
                changeColor(kolor_ramki);
                wcout << L"\u2518 ";
                changeColor(kolor_reset);
                y_koordynaty(i);
                wcout << "\n";
                continue;
            }
            if ((i==0 && j!=0)|| (i==wysokosc-1 && j!=0))
            {
                changeColor(kolor_ramki);
                wcout << L"\u2500";
                changeColor(kolor_reset);
                continue;
            }
            if ((j==0 || j==szerokosc-1) &&( i!=wysokosc-1 && i !=0 ))
            {
                if (j==0)
                {
                    changeColor(kolor_ramki);
                    wcout << L"\u2502";
                    changeColor(kolor_reset);
                }
                else
                {
                    changeColor(kolor_ramki);
                    wcout << L"\u2502 ";
                    changeColor(kolor_reset);
                    y_koordynaty(i);
                    wcout << "\n";
                }
                continue;
            }
            int wartosc{};//numer pola 1-100
            int indeks{};//numer elementu statku
            if (i%2)
            {
                indeks=(j%6+1)-2;
                wartosc=(i/2)*10+(j/6);
            }
            else
            {
                indeks=(j%6+1)+4;
                wartosc=(i/2-1)*10+(j/6);
            }
            if (j%6==0)
            {
                wartosc--;
                indeks+=6;
            }
            if (robocza.at(wartosc)!=0)
            {
                if (robocza.at(wartosc)==2)
                {
                    changeColor(kolor_trafiony);
                    wcout << statek[indeks];
                    changeColor(kolor_reset);
                }
                else
                {
                    changeColor(kolor_nietrafiony);
                    wcout << statek[indeks];
                    changeColor(kolor_reset);
                }
            }
            else
                wcout << " ";
        }
    }
    x_koordynaty();
}
void ZapisPlansz()
{
    fstream dane(nazwaPliku.c_str(), ios::trunc|ios::out);
    for (int i=0; i<10; i++)
    {
        renderujPole;
        dane << "Plansza nr: " << i+1 << "\n";
        for (int i=0; i<100; i++)
        {
            if (i%10==0 && i!=0)
                dane << "\n";
            dane << pole.at(i) << " ";
        }
        dane << "\n";

    }
    dane.close();
    wcout << "Zapisano plik" << endl;
    Sleep(1000);
    system("cls");
}
void Gra()
{
    int pos_x{}, pos_y{},zatopione{}, ruchy{};
    char pos_xa{};
    robocza.fill(0);
    while (true)
    {
        ekran();
        SetCursorPosition(0,40);
        wcout << "Podaj wspolrzedne x (A - J)";
        cin >> pos_xa;
        pos_x=pos_xa-'A';
        wcout << "Podaj wspolrzedne y (1 - 10)";
        cin >> pos_y;
        ruchy++;
        if (pole.at((pos_y-1)*rozmiar+pos_x)!=0)
        {
            robocza.at((pos_y-1)*rozmiar+pos_x)=2;
            zatopione++;
        }
        else
            robocza.at((pos_y-1)*rozmiar+pos_x)=1;
        wcout << "Zatopione: " << zatopione << "/10" << "\n";
        if (zatopione==10)
        {
            ekran();
            SetCursorPosition(0,43);
            wcout << "Zakonczono gre w " << ruchy << " ruchach." << "\n";
            Sleep(5000);
            renderujPole();
            robocza.fill(0);
            system("cls");
            break;
        }
    }
}
int main()
{
    srand(time(0));
    _setmode(_fileno(stdout), _O_U16TEXT);
    system("mode 650");
    renderujPole();
    char op{};
    while (true)
    {
        ekran();
        wcout << "Wybierz opcje:\n";
        wcout << "1.Zapis plansz do pliku\n";
        wcout << "2.Gra\n";
        wcout << "3.Koniec programu\n";
        cin >> op;
        if (op=='1')
            ZapisPlansz();
        if (op=='2')
            Gra();
        if (op=='3')
            break;
    }
    return 0;
}

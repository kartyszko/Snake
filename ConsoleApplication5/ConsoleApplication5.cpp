#include <iostream>
#include <conio.h> // console input output biblioteka do uzycia w funkcji Input
#include <windows.h>
#include <stdlib.h>


using namespace std;

bool gameOver;
const int width = 30; // szerokosc mapy
const int height = 20; // wysokosc mapy
int x, y, fruitX, fruitY; // zmienna x to glowa weza, y to zmienna ogon, fruit = owoce na mapie
int score = 0; // jest int 0 zdeklarowane w tym miejscu zeby ta zmienna byla globalna
// czyli moznaby jej uzyc w rowniez w funkcji GameOver

//ruch węża
int tailX[100], tailY[100];
//długość ciała
int nTail;

//tor
enum eDirecton { STOP = 0, LEFT, RIGHT, UP, DOWN }; // do okreslenia kierunkow poruszania weza
eDirecton dir;

//uchwyt do koloru
HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

// deklarujemy funkcje 
void Menu();
void Setup();
void Draw();
void Logic();
void Input();
void GameOVer();
void repeatMenu();
void optionsMenu();

int main()
{
    Menu();
    optionsMenu();

    return 0;
}

void Setup()
{
    gameOver = false;
    dir = STOP; // deaultowo gdy gra się rozpoczyna to snake się nie rusza
    x = width / 2; // pozycja snake przy rozpoczeciu gry, środek plaszny
    y = height / 2;
    fruitX = rand() % width; // randomowe miejsce owoca
    fruitY = rand() % height; 
}
void Draw()
{
    system("cls"); // sluzy do czyszczenia konsoli

    // gorna czesc mapy:
    for (int i = 0; i < width + 2; i++)
    {
        SetConsoleTextAttribute(hOut, BACKGROUND_GREEN | BACKGROUND_BLUE);
        cout << " ";
        SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
    }
    cout << endl;

    // wysokosc mapy:
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // jezeli pozycja jest pierwsza czyli 0 - lewa sciana
            if (j == 0)
            {
                SetConsoleTextAttribute(hOut, BACKGROUND_GREEN | BACKGROUND_BLUE);
                cout << " ";
                SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
            }

            //głowa
            if (i == y && j == x)
            {
                SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED);
                cout << "O";
                SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
            }

            // owoc
            else if (i == fruitY && j == fruitX)
            {
                SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                cout << "o";
                SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
            }

            else
            {
                bool print = false;
                //drukowanie ciała
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED);
                        cout << "o";
                        SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
                        print = true;
                    }
                }

                // jezeli nic to puste pole
                if (!print)
                    cout << " ";
            }

            //prawa ściana
            if (j == width - 1)
            {
                SetConsoleTextAttribute(hOut, BACKGROUND_GREEN | BACKGROUND_BLUE);
                cout << " ";
                SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
            }
        }
        cout << endl;
    }

    //dolna czesc mapy
    for (int i = 0; i < width + 2; i++)
    {
        SetConsoleTextAttribute(hOut, BACKGROUND_GREEN | BACKGROUND_BLUE);
        cout << " ";
        SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
    }
    cout << endl;

    cout << " SCORE: " << score << endl;

    cout << endl;
    cout << " w - up" << endl;
    cout << " a - left" << endl;
    cout << " d - right" << endl;
    cout << " s - bottom" << endl;
    cout << " q - to quit the game" << endl;
}
void Input()
{
    // keyboard is hit ? 
    if (_kbhit())
    {
        // zwraca wartosc klawiatury ktora zostala wcisnieta
        switch (_getch())
        {
        case 'a':
            dir = LEFT;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 'w':
            dir = UP;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'q':
            gameOver = true;
            GameOVer();
            break;
        }
    }
}
void Logic()
{
    //drukowanie ciala
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;
    for (int i = 1; i < nTail; i++)
    {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    switch (dir)
    {
        // poruszajac sie w lewo zmiejszamy wartosc na skali
    case LEFT:
        x--;
        break;
        // poruszajac w prawo zwiekszamy wartosc na skali
    case RIGHT:
        x++;
        break;

        // poruszajc w gore zmiejszamy wartosc na skali
    case UP:
        y--;
        break;

        // poruszajc w dol zwiekszamy wartosc na skali
    case DOWN:
        y++;
        break;
    default:
        break;
    }

    //po najechaniu na krawedz wychodzi z drugiej strony
    if (x >= width) x = 0; else if (x < 0) x = width - 1;
    if (y >= height) y = 0; else if (y < 0) y = height - 1;

    // zabicie po najechaniu na cialo
    for (int i = 0; i < nTail; i++)
        if (tailX[i] == x && tailY[i] == y)
        {
            gameOver = true;
            GameOVer();
        }

    //zjadanie owoca
    if (x == fruitX && y == fruitY)
    {
        score += 20;
        fruitX = rand() % width;
        fruitY = rand() % height;
        nTail++;
    }
}

void Menu()
{
    system("cls");
    cout << "" << endl;
    SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_BLUE);
    cout << " -----------------------------------------------  " << endl;
    cout << "|                                               | " << endl;
    cout << "|    ******   *     *      *     *  *  *****    | " << endl;
    cout << "|   *         * *   *     * *    * *   *        | " << endl;
    cout << "|    ******   *  *  *    *   *   **    ****     | " << endl;
    cout << "|          *  *   * *   *******  * *   *        | " << endl;
    cout << "|    ******   *     *  *       * *  *  *****    | " << endl;
    cout << "|                                               | " << endl;
    cout << " -----------------------------------------------  " << endl;
    SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
    cout << "" << endl << endl;
    cout << "                     M E N U:    " << endl << endl;
    cout << "                  1: Start gry  " << endl << endl;
    cout << "                  2: Regulamin    " << endl << endl;
    cout << "                  3: Wyjscie     " << endl << endl;
}

void GameOVer()
{
    system("cls"); // sluzy do czyszczenia konsoli
    SetConsoleTextAttribute(hOut, FOREGROUND_RED);
    cout << "" << endl << endl;
    cout << " ------------------------------------------------------------------------- " << endl;
    cout << "|    *****      *     *       * ******       ****  *       ****** ****    |" << endl;
    cout << "|   *          * *    * *   * * *           *    *  *     * *     *   *   |" << endl;
    cout << "|   *  ****   *   *   *  * *  * *****       *    *   *   *  ****  ****    |" << endl;
    cout << "|   *  *  *  *******  *   *   * *           *    *    * *   *     * *     |" << endl;
    cout << "|    *****  *       * *       * ******       ****      *    ***** *   *   |" << endl;
    cout << " ------------------------------------------------------------------------- " << endl;
    cout << "" << endl << endl;
    SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
    cout << "                        Y O U R   S C O R E : " << score << endl << endl;
    cout << "" << endl << endl;
}

void optionsMenu() {
    int n;
    cout << "Podaj wartosc menu, do ktorej chesz przejsc: ";
    cin >> n;
    cout << endl;
    if (n == 1) {
        Setup();
        while (!gameOver)
        {
            Draw();
            Input();
            Logic();
            Sleep(10); // funkcja skleep spowalnia gre
            
        }
    }
    
    else if (n == 2) {
        system("cls");
        cout << "1. Poruszanie" << endl;
        cout << " w - gora" << endl;
        cout << " a - lewo" << endl;
        cout << " d - prawo" << endl;
        cout << " s - dol" << endl;
        cout << " q - koniec gry" << endl << endl;
        cout << "2. Kazde zjedzenie owoca +20 pkt" << endl << endl;
        cout << "3. Wjechanie w barierke powoduje wyjscie z drugiej strony" << endl << endl;
        cout << "4. Uderzenie samego w siebie powoduje koniec gry" << endl << endl;
        cout << "5. Cel gry: Prowadz weza tak aby stal sie jak najdluzszy" << endl << endl;
        cout << "POWODZENIA" << endl;
        repeatMenu();
    }
    else if (n == 3) {
        system("cls");
        GameOVer();
    }
    else {
        cout << "Podales bledna wartosc" << endl;
        optionsMenu();
    }
}

void repeatMenu() {
    string input;
    cout << "Jezeli chcesz wrocic do menu, to wpisz 'tak': ";
    cin >> input;
    if ((input == "Tak") || (input == "tak")) {
        cout << endl;
        main();
    }
    else {
        system("cls");
        GameOVer();
    }
}
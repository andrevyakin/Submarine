#include <iostream>
#include <vector>
#include <string>
#include <conio.h>
#include <Windows.h>
#include <ctime>
#include <iomanip>

using namespace std;

class Submarine
{
public:
	Submarine(string name, int torpedoes, int fuel) : name(name), torpedoes(torpedoes), fuel(fuel) {};
	Submarine(const Submarine & submarine){};
	~Submarine(){};
	
	string name;
	int torpedoes;
	int fuel;

	void forward(Submarine * submarine, bool dir);
	void target(Submarine * submarine);

};


//Консольные цвета
enum
{
	clBlack = 0, clNavy = 1, clGreen = 2, clTeal = 3, clBrown = 4,
	clPurple = 5, clOlive = 6, clGray = 7, clSilver = 8, clBlue = 9,
	clLime = 10, clCyan = 11, clRed = 12, clMagneta = 13, clYellow = 14,
	clWhite = 15
};

void SetConsoleColorTextBackground(unsigned short Tex = clWhite, unsigned short Bg = clBlack)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	Bg = Bg << 4 | Tex;
	SetConsoleTextAttribute(hConsole, Bg);
}

//Позиционирование курсора
void SetConsoleCursorPosition(short x_position, short y_position)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD _coordPosition = { x_position, y_position };
	SetConsoleCursorPosition(hConsole, _coordPosition);
}

//Определение клавиш клавиатуры
enum VKey
{
	UP = 72, LEFT = 75, RIGHT = 77, DOWN = 80,
	ENTER = 13, ESC = 27, BackSpase = 8, Spase = 32,
	F1 = 59, F2 = 60, PageUp = 73, PageDown = 81
};

void Submarine::forward(Submarine * submarine, bool dir)
{
	int stop = 0, time = 0;
	system("cls");
	cout << "Время в пути" << endl;
	cout << "Остаток горючего" << endl;
	if (dir)
		cout << "\nДвигаемся вперед. Расход топлива 10 л/с" << endl;
	else
		cout << "\nДвигаемся назад. Расход топлива 20 л/с" << endl;
	cout << "\nДля остановки нажмите пробел" << endl;
	
	while (stop != VKey::Spase)
	{
		SetConsoleCursorPosition(20, 0);
		cout << ++time;
		SetConsoleCursorPosition(20, 1);
		dir ? submarine->fuel -= 10 : submarine->fuel -= 20;
		cout << submarine->fuel;
		Sleep(1000);
		if (_kbhit() || !submarine->fuel)
			stop = _getch();
	}
}

void Submarine::target(Submarine * submarine)
{
	srand((unsigned)time(NULL));

	//контейнер случайных целей
	vector<int>target;
	for (int i = 0; i < 15; i++)
		target.insert(target.end(), rand() % 100);
			
	int x, move; //y - Положение курсора, move - нажатая клавиша
	do
	{
		//Вывод целей в консоль с установкой "зеленого курсора" на первой
		SetConsoleColorTextBackground(clGray, clBlack);
		system("cls");
		cout << "\t\tВыбирите случайную цель" << endl << endl;
		SetConsoleCursorPosition(0, 3);
		SetConsoleColorTextBackground(clWhite, clGreen);
		cout << setw(4) << setfill (' ') << target[0];
		SetConsoleColorTextBackground(clGray, clBlack);
		for (int i = 1; i < 15; i++)
			cout << setw(4) << setfill(' ') << target[i];

		//Перемещение по целям стрелочками клавиатуры
		x = move = 0;
		while (move != VKey::ENTER && move != VKey::ESC)
		{
			move = _getch();
			if (move == 0xe0)
				move = _getch();

			SetConsoleCursorPosition(x, 3);
			SetConsoleColorTextBackground(clGray, clBlack);
			cout << setw(4) << setfill(' ') << target[x / 4];

			move == VKey::RIGHT && x < 56 ? x+=4 : x;
			move == VKey::LEFT && x > 0 ? x-=4 : x;

			SetConsoleCursorPosition(x, 3);
			SetConsoleColorTextBackground(clWhite, clGreen);
			cout << setw(4) << setfill(' ') << target[x / 4];
			SetConsoleColorTextBackground(clGray, clBlack);
		}
	} while (move != VKey::ESC && x != 13);

}

void main()
{
	setlocale(LC_ALL, "Russian");
	Submarine submarine ("Подводная лодка в степях Украины", 10, 1000);

	//Вектор с элементами меню
	vector<string> menu
	{
		"1. Информация.",
		"А. Название.",
		"В. Количество торпед.",
		"С. Запас топлива.",
		"2. Режим хода.",
		"А. Начать движение вперед.",
		"В. Остановиться.",
		"С. Начать движение назад.",
		"Д. Дозаправка (только в режиме остановки).",
		"3. Режим атаки.",
		"А. Поиск цели.",
		"В. Заряд пускового аппарат(торпед).",
		"С. Атака.",
		"4. Esc - выход из программы."
	};

	int y, move; //y - Элемент меню и положение курсора, move - нажатая клавиша
	do
	{
		//Вывод меню в консоль с установкой "зеленого курсора" на верхней строчке
		SetConsoleColorTextBackground(clGray, clBlack);
		system("cls");
		SetConsoleCursorPosition(0, 0);
		SetConsoleColorTextBackground(clWhite, clGreen);
		cout << menu[0] << endl;
		SetConsoleColorTextBackground(clGray, clBlack);
		copy((menu.begin() + 1), menu.end(), ostream_iterator<string>(cout, "\n"));

		//Перемещение по меню стрелочками клавиатуры
		y = move = 0;
		while (move != VKey::ENTER && move != VKey::ESC)
		{
			move = _getch();
			if (move == 0xe0)
				move = _getch();

			SetConsoleCursorPosition(0, y);
			SetConsoleColorTextBackground(clGray, clBlack);
			cout << menu[y];

			move == VKey::DOWN && y < 13 ? y++ : y;
			move == VKey::UP && y > 0 ? y-- : y;

			SetConsoleCursorPosition(0, y);
			SetConsoleColorTextBackground(clWhite, clGreen);
			cout << menu[y];
			SetConsoleColorTextBackground(clGray, clBlack);
		}

		if (move != VKey::ESC)
			switch (y)
		{

			//Информация
			case 0:
			{
					  system("cls");
					  copy(menu.begin(), menu.end(), ostream_iterator<string>(cout, "\n"));
					  SetConsoleColorTextBackground(clWhite, clGreen);
					  cout << "\nИнформация о подводной лодке..." << endl;
					  SetConsoleColorTextBackground(clGray, clBlack);
					  _getch();
					  break;
			}
				//Название
			case 1:
			{
					  system("cls");
					  copy(menu.begin(), menu.end(), ostream_iterator<string>(cout, "\n"));
					  SetConsoleColorTextBackground(clWhite, clGreen);
					  cout << "\n" << submarine.name << endl;
					  SetConsoleColorTextBackground(clGray, clBlack);
					  _getch();
					  break;
			}
				//Количество торпед.
			case 2:
			{
					  system("cls");
					  copy(menu.begin(), menu.end(), ostream_iterator<string>(cout, "\n"));
					  SetConsoleColorTextBackground(clWhite, clGreen);
					  cout << "\nНа борту " << submarine.torpedoes << " торпед." << endl;
					  SetConsoleColorTextBackground(clGray, clBlack);
					  _getch();;
					  break;
			}
				//Запас топлива
			case 3:
			{
					  system("cls");
					  copy(menu.begin(), menu.end(), ostream_iterator<string>(cout, "\n"));
					  SetConsoleColorTextBackground(clWhite, clGreen);
					  cout << "\nЗапас топлива " << submarine.fuel << " литров." << endl;
					  SetConsoleColorTextBackground(clGray, clBlack);
					  _getch();
					  break;
			}
				//Режим хода
			case 4:
			{
					  system("cls");
					  copy(menu.begin(), menu.end(), ostream_iterator<string>(cout, "\n"));
					  SetConsoleColorTextBackground(clWhite, clGreen);
					  cout << "\nВыбор режима хода." << endl;
					  SetConsoleColorTextBackground(clGray, clBlack);
					  _getch();
					  break;
			}
				//Начать движение вперед
			case 5:
			{
					  submarine.forward(&submarine, true);
					  break;
			}
			//Остановиться
			case 6:
			{
					  system("cls");
					  copy(menu.begin(), menu.end(), ostream_iterator<string>(cout, "\n"));
					  SetConsoleColorTextBackground(clWhite, clGreen);
					  cout << "\nПодводная лодка остановилась." << endl;
					  SetConsoleColorTextBackground(clGray, clBlack);
					  _getch();
					  break;
			}

				//Начать движение назад
			case 7:
			{
					  submarine.forward(&submarine, false);
					  break;
			}
				//Дозаправка
			case 8:
			{
					  system("cls");
					  copy(menu.begin(), menu.end(), ostream_iterator<string>(cout, "\n"));
					  SetConsoleColorTextBackground(clWhite, clGreen);
					  submarine.fuel = 1000;
					  cout << "\nПодводная заправлена полностью (1000 л.)." << endl;
					  SetConsoleColorTextBackground(clGray, clBlack);
					  _getch();
					  break;
			}
				//Режим атаки
			case 9:
			{
					  system("cls");
					  copy(menu.begin(), menu.end(), ostream_iterator<string>(cout, "\n"));
					  SetConsoleColorTextBackground(clWhite, clGreen);
					  cout << "\nРежим атаки..." << endl;
					  SetConsoleColorTextBackground(clGray, clBlack);
					  _getch();
					  break;
			}
				//Поиск цели
			case 10:
			{
					   system("cls");
					   submarine.target(&submarine);
					  _getch();
					  break;
			}
		}




	} while (move != VKey::ESC && y != 13);

	//Выход из программы
	system("cls");
}
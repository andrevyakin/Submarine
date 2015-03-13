#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <iterator>
#include <string>
#include <conio.h>
#include <Windows.h>
#include <ctime>

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

};


//���������� �����
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

//���������������� �������
void SetConsoleCursorPosition(short x_position, short y_position)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD _coordPosition = { x_position, y_position };
	SetConsoleCursorPosition(hConsole, _coordPosition);
}

//����������� ������ ����������
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
	cout << "����� � ����" << endl;
	cout << "������� ��������" << endl;
	if (dir)
		cout << "\n��������� ������. ������ ������� 10 �/�" << endl;
	else
		cout << "\n��������� �����. ������ ������� 20 �/�" << endl;
	cout << "\n��� ��������� ������� ������" << endl;
	
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

void main()
{
	setlocale(LC_ALL, "Russian");
	Submarine submarine ("��������� ����� � ������ �������", 10, 1000);

	//������ � ���������� ����
	vector<string> menu
	{
		"1. ����������.",
		"�. ��������.",
		"�. ���������� ������.",
		"�. ����� �������.",
		"2. ����� ����.",
		"�. ������ �������� ������.",
		"�. ������������.",
		"�. ������ �������� �����.",
		"�. ���������� (������ � ������ ���������).",
		"3. ����� �����.",
		"�. ����� ����.",
		"�. ����� ��������� �������(������).",
		"�. �����.",
		"4. Esc - ����� �� ���������."
	};

	int y, move; //y - ������� ���� � ��������� �������, move - ������� �������
	do
	{
		//����� ���� � ������� � ���������� "�������� �������" �� ������� �������
		SetConsoleColorTextBackground(clGray, clBlack);
		system("cls");
		SetConsoleCursorPosition(0, 0);
		SetConsoleColorTextBackground(clWhite, clGreen);
		cout << menu[0] << endl;
		SetConsoleColorTextBackground(clGray, clBlack);
		copy((menu.begin() + 1), menu.end(), ostream_iterator<string>(cout, "\n"));

		//����������� �� ���� ����������� ����������
		y = move = 0;
		while (move != VKey::ENTER && move != VKey::ESC)
		{
			move = _getch();
			if (move == 0xe0)
				move = _getch();

			SetConsoleCursorPosition(0, y);
			SetConsoleColorTextBackground(clGray, clBlack);
			cout << menu[y];

			move == VKey::DOWN && y < menu.size() - 1 ? y++ : y;
			move == VKey::UP && y > 0 ? y-- : y;

			SetConsoleCursorPosition(0, y);
			SetConsoleColorTextBackground(clWhite, clGreen);
			cout << menu[y];
			SetConsoleColorTextBackground(clGray, clBlack);
		}

		if (move != VKey::ESC)
			switch (y)
		{

			//����������
			case 0:
			{
					  system("cls");
					  copy(menu.begin(), menu.end(), ostream_iterator<string>(cout, "\n"));
					  SetConsoleColorTextBackground(clWhite, clGreen);
					  cout << "\n���������� � ��������� �����..." << endl;
					  SetConsoleColorTextBackground(clGray, clBlack);
					  _getch();
					  break;
			}
				//��������
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
				//���������� ������.
			case 2:
			{
					  system("cls");
					  copy(menu.begin(), menu.end(), ostream_iterator<string>(cout, "\n"));
					  SetConsoleColorTextBackground(clWhite, clGreen);
					  cout << "\n�� ����� " << submarine.torpedoes << " ������." << endl;
					  SetConsoleColorTextBackground(clGray, clBlack);
					  _getch();;
					  break;
			}
				//����� �������
			case 3:
			{
					  system("cls");
					  copy(menu.begin(), menu.end(), ostream_iterator<string>(cout, "\n"));
					  SetConsoleColorTextBackground(clWhite, clGreen);
					  cout << "\n����� ������� " << submarine.fuel << " ������." << endl;
					  SetConsoleColorTextBackground(clGray, clBlack);
					  _getch();
					  break;
			}
				//����� ����
			case 4:
			{
					  system("cls");
					  copy(menu.begin(), menu.end(), ostream_iterator<string>(cout, "\n"));
					  SetConsoleColorTextBackground(clWhite, clGreen);
					  cout << "\n����� ������ ����." << endl;
					  SetConsoleColorTextBackground(clGray, clBlack);
					  _getch();
					  break;
			}
				//������ �������� ������
			case 5:
			{
					  submarine.forward(&submarine, true);
					  break;
			}
			//������������
			case 6:
			{
					  system("cls");
					  copy(menu.begin(), menu.end(), ostream_iterator<string>(cout, "\n"));
					  SetConsoleColorTextBackground(clWhite, clGreen);
					  cout << "\n��������� ����� ������������." << endl;
					  SetConsoleColorTextBackground(clGray, clBlack);
					  _getch();
					  break;
			}

				//������ �������� �����
			case 7:
			{
					  submarine.forward(&submarine, false);
					  break;
			}
				//����������
			case 8:
			{
					  system("cls");
					  copy(menu.begin(), menu.end(), ostream_iterator<string>(cout, "\n"));
					  SetConsoleColorTextBackground(clWhite, clGreen);
					  submarine.fuel = 1000;
					  cout << "\n��������� ���������� ��������� (1000 �.)." << endl;
					  SetConsoleColorTextBackground(clGray, clBlack);
					  _getch();
					  break;
			}
		}




	} while (move != VKey::ESC && y != 13);

	//����� �� ���������
	system("cls");
}
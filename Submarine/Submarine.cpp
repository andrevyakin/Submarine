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
	Submarine();
	~Submarine();
	void torpedoes();
	void fuel();
	void GetNane();
private:
	string name;
	//	vector <int> torpedoes;
	//	vector <int> fuel;
};

class Torpedoes : public Submarine
{};

class Fuel : public Submarine
{
public:
	void forward();
};

void Fuel::forward()
{
}

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
	ENTER = 13, ESC = 27, BackSpase = 8,
	F1 = 59, F2 = 60, PageUp = 73, PageDown = 81
};


void main()
{
	setlocale(LC_ALL, "Russian");

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

	int y, move; //������� ���� � ������� �������
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
					  cout << "���������� � ��������� �����..." << endl;
					  system("pause");
					  break;
			}
				//��������
			case 1:
			{
					  system("cls");
					  cout << "��������� ����� \"� ������ �������\"." << endl;
					  system("pause");
					  break;
			}
				//���������� ������.
			case 2:
			{
					  system("cls");
					  cout << "����������� 10-� ���������." << endl;
					  system("pause");
					  break;
			}
				//����� �������
			case 3:
			{
					  system("cls");
					  cout << "����� ������� 1000 ������." << endl;
					  system("pause");
					  break;
			}
				//����� ����
			case 4:
			{
					  system("cls");
					  cout << "����� ������ ����." << endl;
					  system("pause");
					  break;
			}
				//������ �������� ������
			case 5:
			{
					  system("cls");
					  cout << "�������� ��������� ������." << endl;
					  //forward();
					  system("pause");
					  break;
			}
		}




	} while (move != VKey::ESC && y != 13);

	//����� �� ���������
	system("cls");
}
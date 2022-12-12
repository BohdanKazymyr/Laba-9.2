#include <iostream>
#include <iomanip>
#include <string>
#include <Windows.h> // забезпечення відображення кирилиці
using namespace std;
enum Cours { L = 1, II, III, IV, V };
string KursStr[] = { "I", "II", "III", "IV", "V" };
struct Student
{
	string prizv;
	string cpecialnist;
	Cours kurs;
	union
	{
		int math;
		int physics;
		int inform;
	};
};
void Create(Student* p, const int N);
void Print(Student* p, const int N);
void Sort(Student* p, const int N);
int BinSearch(Student* p, const int N, const string prizv, const Cours kurs);
int* IndexSort(Student* p, const int N);
void PrintIndexSorted(Student* p, int* I, const int N);

int main()
{ // забезпечення відображення кирилиці:
	SetConsoleCP(1251); // встановлення сторінки win-cp1251 в потік вводу
	SetConsoleOutputCP(1251); // встановлення сторінки win-cp1251 в потік виводу

	int N;
	cout << "Enter N: "; cin >> N;

	Student* p = new Student[N];
	int ikurs;
	Cours kurs;
	string prizv;
	int found;
	int menuItem;
	do {
		cout << endl << endl << endl;
		cout << "Choose option:" << endl << endl;
		cout << " [1] - enter data " << endl;
		cout << " [2] - print" << endl;
		cout << " [3] - phisical sort" << endl << endl;
		cout << " [4] - binar search" << endl;
		cout << " [5] - index sort"
			<< endl << endl;
		cout << " [0] - close and exit" << endl << endl;
		cout << "Enter : "; cin >> menuItem;
		cout << endl << endl << endl;
		switch (menuItem)
		{
		case 1:
			Create(p, N);
			break;
		case 2:
			Print(p, N);
			break;
		case 3:
			Sort(p, N);
			break;
		case 4:
				cout << "Enter keys:" << endl;
			cout << " Cours (0 - I, 1 - II, 2 - III, 3 - IV, 4 - V): ";
			cin >> ikurs;
			kurs = (Cours)ikurs;
			cin.get(); // очищуємо буфер клавіатури – бо залишаються символи
			cin.sync(); // "кінець рядка", які не дають ввести наступний літерний рядок

			cout << " Prizv: "; getline(cin, prizv);
			cout << endl;
			if ((found = BinSearch(p, N, prizv, kurs)) != -1)
				cout << "Found in position " << found + 1 << endl;
			else
				cout << "Not found" << endl;
			break;
		case 5:
			PrintIndexSorted(p, IndexSort(p, N), N);
			break;

		case 0:
			break;
		default:
			cout << "Eror! "
				"You should enter right number" << endl;
		}
	} while (menuItem != 0);
	return 0;
}
void Create(Student* p, const int N)
{
	int kurs;
	for (int i = 0; i < N; i++)
	{
		cout << "Student # " << i + 1 << ":" << endl;
		cin.get(); // очищуємо буфер клавіатури – бо залишаються символи
		cin.sync(); // "кінець рядка", які не дають ввести наступний літерний рядок

		cout << " Prizv: "; getline(cin, p[i].prizv);
		cout << " Cpecialnist : "; cin >> p[i].cpecialnist;
		cout << " Cours (0 - I, 1 - II, 2 - III, 3 - IV, 4 - V): ";
		cin >> kurs;
		p[i].kurs = (Cours)kurs;
		switch (p[i].kurs)
		{
		case L:
		case II:
		case III:
		case IV:
		case V:
			cout << " Math : "; cin >> p[i].math;
			cout << " Physics : "; cin >> p[i].physics;
			cout << " Inform : "; cin >> p[i].inform;
			break;
		}
		cout << endl;
	}
}
void Print(Student* p, const int N)
{
	cout << "========================================================================="
		<< endl;
	cout << "| # | Prizv | Cpecialnist | Cours | Math | Phisics | Inform |"
		<< endl;
	cout << "-------------------------------------------------------------------------"
		<< endl;
	for (int i = 0; i < N; i++)
	{
		cout << "| " << setw(1) << right << i + 1 << " ";
		cout << "| " << setw(6) << left << p[i].prizv
			<< "| " << setw(11) << right << p[i].cpecialnist << " "
			<< "| " << setw(6) << left << KursStr[p[i].kurs];
		switch (p[i].kurs)
		{
		case L:
		case II:
		case III:
		case IV:
		case V:
			cout << "| " << setw(4) << setprecision(2) << fixed << right
				<< p[i].math << " |" << setw(2) << right

				<< setw(8) << setprecision(2) << fixed << right
				<< p[i].physics << " |" << setw(13) << right <<
				setw(7) << setprecision(2) << fixed << right
				<< p[i].inform << " |" << setw(0) << right << endl;
			break;
		}
	}
	cout << "========================================================================="
		<< endl;
	cout << endl;
}
void Sort(Student* p, const int N)
{
	Student tmp;
	for (int i0 = 0; i0 < N - 1; i0++) // метод "бульбашки"
		for (int i1 = 0; i1 < N - i0 - 1; i1++)
			if (p[i1].math + p[i1].physics + p[i1].inform > p[i1 + 1].math + p[i1 + 1].physics + p[i1 + 1].inform)
				
			{
				tmp = p[i1];
				p[i1] = p[i1 + 1];
				p[i1 + 1] = tmp;
			}
}
int BinSearch(Student* p, const int N, const string prizv, const Cours kurs)
{ // повертає індекс знайденого елемента або -1, якщо шуканий елемент відсутній
	int L = 0, R = N - 1, m;
	do {
		m = (L + R) / 2;
		if (p[m].prizv == prizv && p[m].kurs == kurs)
			return m;
		if ((p[m].kurs < kurs)
			||
			(p[m].kurs == kurs &&
				p[m].prizv < prizv))
		{
			L = m + 1;
		}
		else
		{
			R = m - 1;
		}
	} while (L <= R);
	return -1;
}
int* IndexSort(Student* p, const int N)
{ // використовуємо метод вставки для формування індексного масиву
 // 
 // int i, j, value;
 // for (i = 1; i < length; i++) {
 // value = a[i];
 // for (j = i - 1; j >= 0 && a[j] > value; j--) {
 // a[j + 1] = a[j];
 // }
 // a[j + 1] = value;
 // }
	int* I = new int[N]; // створили індексний масив
	for (int i = 0; i < N; i++)
		I[i] = i; // заповнили його початковими даними
	int i, j, value; // починаємо сортувати масив індексів
	for (i = 1; i < N; i++)
	{
		value = I[i];
		for (j = i - 1;
			j >= 0 && (p[I[i]].math + p[I[i]].physics + p[I[i]].inform > p[I[i + 1]].math + p[I[i + 1]].physics + p[I[i + 1]].inform) || 
			(p[I[i]].math + p[I[i]].physics + p[I[i]].inform == p[I[i + 1]].math + p[I[i + 1]].physics + p[I[i + 1]].inform) && ((p[I[j]].kurs > p[value].kurs)) ||
				(p[I[j]].kurs == p[value].kurs &&
					p[I[j]].prizv > p[value].prizv);
		j--)
		{
			I[j + 1] = I[j];
		}
		I[j + 1] = value;
	}
	return I;
}
void PrintIndexSorted(Student* p, int* I, const int N)
{ // аналогічно функції Print(), але замість звертання p[i]... 
 // використовуємо доступ за допомогою індексного масиву І: p[I[i]]...
	
	cout << "========================================================================="
		<< endl;
	cout << endl;
	cout << "========================================================================="
		<< endl;
	cout << "| # | Prizv | Cpecialnist | Cours | Math | Phisics | Inform |"
		<< endl;
	cout << "-------------------------------------------------------------------------"
		<< endl;
	for (int i = 0; i < N; i++)
	{
		cout << "| " << setw(1) << right << i + 1 << " ";
		cout << "| " << setw(6) << left << p[I[i]].prizv
			<< "| " << setw(11) << right << p[I[i]].cpecialnist << " "
			<< "| " << setw(6) << left << KursStr[p[I[i]].kurs];
		switch (p[I[i]].kurs)
		{
		case L:
		case II:
		case III:
		case IV:
		case V:
			cout << "| " << setw(4) << setprecision(2) << fixed << right
				<< p[i].math << " |" << setw(2) << right

				<< setw(8) << setprecision(2) << fixed << right
				<< p[i].physics << " |" << setw(13) << right <<
				setw(7) << setprecision(2) << fixed << right
				<< p[i].inform << " |" << setw(0) << right << endl;
			break;
		}
	}
	cout << "========================================================================="
		<< endl;
	cout << endl;
}



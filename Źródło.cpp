#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <iostream>

using namespace std;

typedef struct liczba
{
	char* cyfry;

};

void wczytaj(int ile, liczba* tab)
{
	for (int i = 0; i < ile; i++)
	{
		char buf[2048];
		cin >> buf;
		int dlug = strlen(buf) + 1;


		tab[i].cyfry = (char*)malloc(sizeof(char) * dlug);
		strcpy_s(tab[i].cyfry, dlug, buf);
	}
}

void znak_zapytania(int ile, liczba* tab)
{
	for (int j = 0; j < ile; j++)
	{
		cout << tab[j].cyfry << endl;
	}
}

void maxi(int ile, liczba* tab)
{
	liczba maximal = tab[0];
	for (int i = 1; i < ile; i++)
	{
		if (maximal.cyfry[0] == '-')
		{
			if (tab[i].cyfry[0] != '-')
			{
				maximal = tab[i];
			}
			else if (strlen(tab[i].cyfry) < strlen(maximal.cyfry))
			{
				maximal = tab[i];
			}
			else if (strlen(tab[i].cyfry) == strlen(maximal.cyfry))
			{
				int a = 0;
				while (tab[i].cyfry[a] == maximal.cyfry[a])
				{
					a++;
				}
				if (tab[i].cyfry[a] < maximal.cyfry[a])
				{
					maximal = tab[i];
				}
			}
		}
		else if (tab[i].cyfry[0] != '-')
		{
			if (strlen(tab[i].cyfry) > strlen(maximal.cyfry))
			{
				maximal = tab[i];
			}
			else if (strlen(tab[i].cyfry) == strlen(maximal.cyfry))
			{
				int a = 0;
				while (tab[i].cyfry[a] == maximal.cyfry[a])
				{
					a++;
				}
				if (tab[i].cyfry[a] > maximal.cyfry[a])
				{
					maximal = tab[i];
				}
			}

		}
	}
	cout << maximal.cyfry << endl;
}

void mini(int ile, liczba* tab)
{
	liczba minimal = tab[0];
	for (int i = 1; i < ile; i++)
	{
		if (minimal.cyfry[0] != '-')
		{
			if (tab[i].cyfry[0] == '-')
			{
				minimal = tab[i];
			}
			else if (strlen(tab[i].cyfry) < strlen(minimal.cyfry))
			{
				minimal = tab[i];
			}
			else if (strlen(tab[i].cyfry) == strlen(minimal.cyfry))
			{
				int a = 0;
				while (tab[i].cyfry[a] == minimal.cyfry[a])
				{
					a++;
				}
				if (tab[i].cyfry[a] < minimal.cyfry[a])
				{
					minimal = tab[i];
				}
			}
		}
		else if (tab[i].cyfry[0] == '-')
		{
			if (strlen(tab[i].cyfry) > strlen(minimal.cyfry))
			{
				minimal = tab[i];
			}
			else if (strlen(tab[i].cyfry) == strlen(minimal.cyfry))
			{
				int a = 0;
				while (tab[i].cyfry[a] == minimal.cyfry[a])
				{
					a++;
				}
				if (tab[i].cyfry[a] > minimal.cyfry[a])
				{
					minimal = tab[i];
				}
			}

		}
	}
	cout << minimal.cyfry << endl;
}


int convert(char* num)
{
	int ile = strlen(num);
	int number = 0;


	for (int i = 0; i < ile; i++)
	{
		number *= 10;
		int p = (int)(num[i] - '0');
		number += p;
	}

	return number;
}

void dodaj(int to, int fromA, int fromB, liczba* tab);
void odejmij(int to, int fromA, int fromB, liczba* tab);

void plus_or_minus(char* nb, liczba* tab)
{
	char* args[4];
	for (int i = 0; i < 4; i++)
	{
		char buf[10];
		cin >> buf;
		args[i] = (char*)malloc(sizeof(char) * 10);
		strcpy_s(args[i], 10, buf);
	}

	int to = convert(nb);
	int from1 = convert(args[1]);
	int from2 = convert(args[3]);

	if (strcmp(args[2], "+") == 0)
	{
		dodaj(to, from1, from2, tab);
	}
	else if (strcmp(args[2], "-") == 0)
	{
		odejmij(to, from1, from2, tab);
	}
}

void przepisz(char* from, char* to)
{
	int x = strlen(from);
	for (int a = 0, b = (x - 1); b >= 0; a++, b--)
	{
		to[a] = from[b];
		to[a + 1] = '\0';
	}
}

int higher(char* pos, char* neg)
{
	int pos_len = strlen(pos);
	int neg_len = strlen(neg) - 1;

	if (pos_len > neg_len)
	{
		return 1;
	}
	else if (pos_len < neg_len)
	{
		return 2;
	}
	else
	{
		int p = 0;
		while (p < pos_len - 1)
		{
			if (pos[p] > neg[p + 1]) return 1;
			else if (pos[p] < neg[p + 1]) return 2;
			else if (p == (pos_len - 1)) return 1;
			p++;
		}

	}
	return 0;
}

void zapisz(char* wynik, liczba* tab, int target)
{

	char* zapis = (char*)malloc(sizeof(char) * strlen(wynik));

	int p = 0;

	if (wynik[0] != '-')
	{
		while (wynik[p] == '0')
		{
			(wynik++);
		}
		strcpy(zapis, wynik);
	}
	else
	{
		zapis[0] = '-';

		while (wynik[p] == '0' || wynik[p] == '-')
		{
			(wynik++);
		}
		strcpy(&zapis[1], wynik);
	}

	if (strcmp(zapis, "-") == 0 || (strcmp(zapis, "") == 0))
	{
		zapis[0] = '0';
		zapis[1] = '\0';
	} 

	tab[target].cyfry = zapis;
}

void dodaj(int to, int fromA, int fromB, liczba* tab)
{
	int przenies = 0;
	int ai = strlen(tab[fromA].cyfry);
	int bi = strlen(tab[fromB].cyfry);
	bool ujemny_wynik = false;

	char* wynik;
	char* poprawny;

	if (ai >= bi)
		wynik = (char*)malloc(sizeof(char) * (ai + 3));
	else
		wynik = (char*)malloc(sizeof(char) * (bi + 3));

	int initA = 0, initB = 0;

	if ((tab[fromA].cyfry[0] != '-' && tab[fromB].cyfry[0] != '-')) { initA = 0, initB = 0; }
	if ((tab[fromA].cyfry[0] == '-' && tab[fromB].cyfry[0] == '-')) { initA = 1, initB = 1; }
	if ((tab[fromA].cyfry[0] != '-' && tab[fromB].cyfry[0] == '-')) { initA = 0, initB = 1; }
	if ((tab[fromA].cyfry[0] == '-' && tab[fromB].cyfry[0] != '-')) { initA = 1, initB = 0; }

	for (int a = (ai - 1), b = (bi - 1), c = 0; (a >= initA || b >= initB); a--, b--, c++)
	{

		short first = (short)(tab[fromA].cyfry[a] - '0');
		if (a < initA)
		{
			first = 0;
		}
		short second = (short)(tab[fromB].cyfry[b] - '0');
		if (b < initB)
		{
			second = 0;
		}
		int result = 0;

		if ((tab[fromA].cyfry[0] != '-' && tab[fromB].cyfry[0] != '-') || (tab[fromA].cyfry[0] == '-' && tab[fromB].cyfry[0] == '-'))
		{
			result = first + second + przenies;
		}
		else if (((tab[fromA].cyfry[0] != '-' && tab[fromB].cyfry[0] == '-') && (higher(tab[fromA].cyfry, tab[fromB].cyfry) == 1)))
		{
			result = first - second + przenies;
			ujemny_wynik = false;
		}
		else if ((tab[fromA].cyfry[0] == '-' && tab[fromB].cyfry[0] != '-') && (higher(tab[fromB].cyfry, tab[fromA].cyfry) == 1))
		{
			result = second - first + przenies;
			ujemny_wynik = false;
		}
		else if (((tab[fromA].cyfry[0] != '-' && tab[fromB].cyfry[0] == '-') && (higher(tab[fromA].cyfry, tab[fromB].cyfry) == 2)))
		{
			result = second - first + przenies;
			ujemny_wynik = true;
		}
		else if (((tab[fromA].cyfry[0] == '-' && tab[fromB].cyfry[0] != '-') && (higher(tab[fromB].cyfry, tab[fromA].cyfry) == 2)))
		{
			result = first - second + przenies;
			ujemny_wynik = true;
		}

		if (result > 9) { przenies = 1; }
		else if (result < 0) { przenies = -1; }
		else { przenies = 0; }


		int cyfra = (result + 10) % 10;
		wynik[c] = (char)('0' + cyfra);
		wynik[c + 1] = '\0';

	}

	if (przenies == 1)
	{
		int length = strlen(wynik);
		wynik[length] = '1';
		wynik[length + 1] = '\0';
	}

	if ((initA == 1 && initB == 1) || ujemny_wynik == true)
	{
		int length = strlen(wynik);
		wynik[length] = '-';
		wynik[length + 1] = '\0';
	}

	poprawny = (char*)malloc(sizeof(char) * (strlen(wynik) + 1));

	przepisz(wynik, poprawny);
	zapisz(poprawny, tab, to);

	free(poprawny);
}

void odejmij(int to, int fromA, int fromB, liczba* tab)
{
	liczba* tmp = (liczba*)malloc(sizeof(liczba) * 3);
	tmp[0] = tab[to];
	tmp[1] = tab[fromA];

	int roz = strlen(tab[fromB].cyfry) + 2;
	
	char* odjemnik = (char*)malloc(sizeof (char)*roz);

	if (tab[fromB].cyfry[0] != '-')
	{
		odjemnik[0] = '-';
		strcpy(&odjemnik[1], tab[fromB].cyfry);
	}
	else
	{
		strcpy(odjemnik, tab[fromB].cyfry);
		(odjemnik++);
	}

	tmp[2].cyfry = odjemnik;

	dodaj(0, 1, 2, tmp);

	tab[to] = tmp[0];
}





int main()
{

	int n;
	cin >> n;
	liczba* tablica = (liczba*)malloc(sizeof(liczba) * n);
	wczytaj(n, tablica);

	char cmd[20];

	int quit = 0;

	while (quit == 0)
	{
		cin >> cmd;
		if (strcmp(cmd, "min") == 0)
		{
			mini(n, tablica);
		}
		else if (strcmp(cmd, "max") == 0)
		{
			maxi(n, tablica);
		}
		else if (strcmp(cmd, "?") == 0)
		{
			znak_zapytania(n, tablica);
		}
		else if (strcmp(cmd, "q") == 0)
		{
			free(tablica);
			quit = 1;
		}
		else
		{
			plus_or_minus(cmd, tablica);
		}

	}

	return 0;
}
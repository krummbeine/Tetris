
// ___________________________________________________________________________________  
//																		I N C L U D E

#include <stdio.h>
#define _USE_MATH_DEFINES
#include<math.h>
#include<string.h>
#include <stdlib.h>
#include "funktionen.h"
#include <conio.h>
#include <windows.h>

// ___________________________________________________________________________________   
//																	  	  D E F I N E

#define d_breite 17
#define d_hoehe 30
#define d_clearscreen system("cls")

// ___________________________________________________________________________________ 
//													G L O B A L E   V A R I A B L E N

struct s_element * kopf;
struct s_element * letztes_element;
t_punkt drehpunkt;
int ende = false;
int score;
int timer = 1000;

// ___________________________________________________________________________________  
//																  D Y N A M I S C H E

void NeuesElement(int *feld[d_breite][d_hoehe], struct s_element **v_kopf)
{
	if (*v_kopf == NULL)
	{
		short zufallswert = rand() % 8;

		*v_kopf = (struct s_element *)malloc(sizeof(struct s_element));

		letztes_element = *v_kopf;

		if (zufallswert < 15)
		{
			(*v_kopf)->farbwert = 15 - zufallswert;
		}
		else
		{
			(*v_kopf)->farbwert = 15;
		}
		(*v_kopf)->next = NULL;

		PunkteErzeugen(feld, (*v_kopf)->punkte, zufallswert, *v_kopf);

		score++;
	}
	else
	{
		NeuesElement(feld, &((*v_kopf)->next));
	}
}

void PunkteErzeugen(int feld[d_breite][d_hoehe], t_punkt *punktefeld, int typ, struct s_element **v_kopf)
{
	int i;
	short zufallswert = rand() % 4;

	// Punkte setzen nach Typ
	for (i = 0; i < 9; i++)
	{
		int y = i / 3;
		int x = i % 3;
		int ex = d_breite / 2 - 1;

		punktefeld[i].y = y;
		punktefeld[i].x = x;
		punktefeld[i].gesetzt = fGesetzt(i, typ);
	}

	// Zufallsdrehen
	for (i = 0; i < zufallswert; i++)
	{
		int
			fg0,
			fg1,
			fg2,
			fg3,
			// 4
			fg5,
			fg6,
			fg7,
			fg8;

		fg0 = punktefeld[0].gesetzt;
		fg1 = punktefeld[1].gesetzt;
		fg2 = punktefeld[2].gesetzt;
		fg3 = punktefeld[3].gesetzt;
		// 4
		fg5 = punktefeld[5].gesetzt;
		fg6 = punktefeld[6].gesetzt;
		fg7 = punktefeld[7].gesetzt;
		fg8 = punktefeld[8].gesetzt;

		punktefeld[0].gesetzt = fg6;
		punktefeld[1].gesetzt = fg3;
		punktefeld[2].gesetzt = fg0;
		punktefeld[3].gesetzt = fg7;
		// 4
		punktefeld[5].gesetzt = fg1;
		punktefeld[6].gesetzt = fg8;
		punktefeld[7].gesetzt = fg5;
		punktefeld[8].gesetzt = fg2;
	}

	// Adressen in das Feld übertragen
	for (i = 0; i < 9; i++)
	{
		int y = i / 3;
		int x = i % 3;
		int ex = d_breite / 2 - 1;

		if (punktefeld[i].gesetzt)
		{
			if (feld[x + ex][y] == 0)
			{
				feld[x + ex][y] = v_kopf;
			}
			else
			{
				ende = true;
			}
		}
	}

	drehpunkt.x = d_breite / 2;
	drehpunkt.y = 1;
}

int fGesetzt(int position, int typ)
{
	int tmp;

	switch (typ)
	{
	case 0:
	{
		int vorlage[] = {
			0,1,0,
			0,1,0,
			0,1,0 };
		tmp = vorlage[position];
		break;
	}
	case 1:
	{
		int vorlage1[] = {
			0,1,0,
			0,1,0,
			1,1,0 };
		tmp = vorlage1[position];
		break;
	}
	case 2:
	{
		int vorlage2[] = {
			0,1,0,
			0,1,0,
			0,1,1 };
		tmp = vorlage2[position];
		break;
	}
	case 3:
	{
		int vorlage3[] = {
			0,0,0,
			0,1,1,
			0,1,1 };
		tmp = vorlage3[position];
		break;
	}
	case 4:
	{
		int vorlage4[] = {
			1,1,0,
			0,1,1,
			0,0,0 };
		tmp = vorlage4[position];
		break;
	}
	case 5:
	{
		int vorlage5[] = {
			0,1,1,
			1,1,0,
			0,0,0 };
		tmp = vorlage5[position];
		break;
	}
	case 6:
	{
		int vorlage6[] = {
			1,1,1,
			0,1,0,
			0,0,0 };
		tmp = vorlage6[position];
		break;
	}
	default:
	{
		int vorlagede[] = {
			0,0,0,
			0,1,0,
			0,1,0 };
		tmp = vorlagede[position];
		break;
	}
	}

	return tmp;
}

void SpeicherFreigeben(struct s_element ** v_kopf)
{
	if ((*v_kopf) == NULL)
	{
		kopf = NULL;
	}
	else
	{
		int *tmp = NULL;

		tmp = (*v_kopf)->next;
		free(*v_kopf);
		kopf = tmp;
		SpeicherFreigeben(&kopf);
	}
}

// ___________________________________________________________________________________  
//																  F U N K T I O N E N

void fallen(int feld[d_breite][d_hoehe])
{
	int x, y;
	int frei = true;

	if (letztes_element != NULL)
	{
		for (x = 0; x < d_breite; x++)
		{
			for (y = 0; y < d_hoehe; y++)
			{
				if (letztes_element == (struct s_element *)feld[x][y])
				{
					if (feld[x][y + 1] != 0)
					{
						if (letztes_element != (struct s_element *)feld[x][y + 1])
						{
							frei = false;
						}
					}
					if (y + 1 == d_hoehe)
					{
						frei = false;
					}
				}
			}
		}
	}

	if (frei)
	{
		if (letztes_element != NULL)
		{
			for (x = 0; x < d_breite; x++)
			{
				for (y = d_hoehe - 1; y >= 0; y--)
				{
					if (letztes_element == (struct s_element *)feld[x][y])
					{
						feld[x][y + 1] = feld[x][y];
						feld[x][y] = 0;
					}
				}
			}
		}
		drehpunkt.y++;
	}
	else
	{
		if (timer > 100)
			timer--;
		zeilenkill(feld);
		NeuesElement(feld, &kopf);	
	}
}

void bewegen(int feld[d_breite][d_hoehe], int x_richtung)
{
	int x, y;
	int frei = true;

	if (letztes_element != NULL)
	{
		for (x = 0; x < d_breite; x++)
		{
			for (y = 0; y < d_hoehe; y++)
			{
				if (letztes_element == (struct s_element *)feld[x][y])
				{
					if (feld[x + x_richtung][y] != 0)
					{
						if (letztes_element != (struct s_element *)feld[x + x_richtung][y])
						{
							frei = false;
						}
					}
					if (x + x_richtung < 0 || x + x_richtung > d_breite)
					{
						frei = false;
					}
				}
			}
		}
	}

	if (frei)
	{
		if (letztes_element != NULL)
		{
			for (y = 0; y < d_hoehe; y++)
			{
				if (x_richtung == 1) // Nach rechts
				{
					for (x = d_breite - 1; x >= 0; x--)
					{
						if (letztes_element == (struct s_element *)feld[x][y])
						{
							feld[x + x_richtung][y] = feld[x][y];
							feld[x][y] = 0;
						}
					}
				}
				else // Nach links
				{
					for (x = 0; x < d_breite; x++)
					{
						if (letztes_element == (struct s_element *)feld[x][y])
						{
							feld[x + x_richtung][y] = feld[x][y];
							feld[x][y] = 0;
						}
					}
				}
			}
			if (x_richtung == 1) // Nach rechts
			{
				drehpunkt.x++;
			}
			else
			{
				drehpunkt.x--;
			}
		}
	}
}

void drehen(int feld[d_breite][d_hoehe], int richtung)
{
	int x, y, i;
	int frei;
	// Alte Werte der Punkte
	int
		tmp0,
		tmp1,
		tmp2,
		tmp3,
		// Drehpunkt [4]
		tmp5,
		tmp6,
		tmp7,
		tmp8;

	tmp0 = feld[drehpunkt.x - 1][drehpunkt.y - 1];
	tmp1 = feld[drehpunkt.x - 0][drehpunkt.y - 1];
	tmp2 = feld[drehpunkt.x + 1][drehpunkt.y - 1];
	tmp3 = feld[drehpunkt.x - 1][drehpunkt.y - 0];
	//
	tmp5 = feld[drehpunkt.x + 1][drehpunkt.y - 0];
	tmp6 = feld[drehpunkt.x - 1][drehpunkt.y + 1];
	tmp7 = feld[drehpunkt.x - 0][drehpunkt.y + 1];
	tmp8 = feld[drehpunkt.x + 1][drehpunkt.y + 1];

	for (frei = i = 0; i < 9; i++)
	{
		int x, y;

		x = drehpunkt.x + letztes_element->punkte[i].x - 1;
		y = drehpunkt.y + letztes_element->punkte[i].y - 1;

		if (feld[x][y] == 0 || letztes_element == (struct s_element *)feld[x][y])
		{
			frei++;
		}
	}

	if (frei == 9)
	{
		for (i = 0; i < 9; i++)
		{
			int x, y;

			x = drehpunkt.x + letztes_element->punkte[i].x - 1;
			y = drehpunkt.y + letztes_element->punkte[i].y - 1;

			if (richtung == -1) // LINKS Drehen
			{
				switch (i)
				{
				case 0:
					feld[x][y] = tmp2;
					break;
				case 1:
					feld[x][y] = tmp5;
					break;
				case 2:
					feld[x][y] = tmp8;
					break;
				case 3:
					feld[x][y] = tmp1;
					break;

				case 5:
					feld[x][y] = tmp7;
					break;
				case 6:
					feld[x][y] = tmp0;
					break;
				case 7:
					feld[x][y] = tmp3;
					break;
				case 8:
					feld[x][y] = tmp6;
					break;
				}
			}
			else
			{
				switch (i)
				{
				case 0:
					feld[x][y] = tmp6;
					break;
				case 1:
					feld[x][y] = tmp3;
					break;
				case 2:
					feld[x][y] = tmp0;
					break;
				case 3:
					feld[x][y] = tmp7;
					break;

				case 5:
					feld[x][y] = tmp1;
					break;
				case 6:
					feld[x][y] = tmp8;
					break;
				case 7:
					feld[x][y] = tmp5;
					break;
				case 8:
					feld[x][y] = tmp2;
					break;
				}
			}
		}
	}
}

void zeilenkill(int feld[d_breite][d_hoehe])
{
	int x, y, y2;
	for (y = 0; y < d_hoehe; y++)
	{
		int summe = 0;
		for (x = 0; x < d_breite; x++)
		{
			if (feld[x][y] != 0)
				summe++;
		}
		if (summe == d_breite)
		{
			for (y2 = y; y > 0; y--)
			{
				for (x = 0; x < d_breite; x++)
				{
					feld[x][y] = feld[x][y - 1];
				}
			}
		}
	}
}

char eingabe()
{
	while (kbhit())
	{
		return getch();
	}
}

void farbe(int farbwert)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, farbwert);
}

void neuezeile(int zeilen)
{
	int i;
	for (i = 1; i <= zeilen; i++)
		printf("\n");
}

void strich(int n, char c)
{
	int i;
	for (i = 1; i <= n; i++)
		printf("%c", c);
}

// ___________________________________________________________________________________  
//																  S P I E L - M A I N

void spielfeld_zeichnen(int feld[d_breite][d_hoehe])
{
	int x, y;

	farbe(2);
	printf("   Speicher freigeben und beenden (1)\n   Drehen (w,e) Bewegen(a,s,d) Neues Element(2)\n   ");
	farbe(15);
	printf("Score %i", score);

	neuezeile(2);
	farbe(6);

	printf("   %c", 201);
	strich(d_breite, 205);
	printf("%c\n", 187);

	for (y = 0; y < d_hoehe; y++)
	{
		char zeile[d_breite + 1];

		printf("   %c", 186);
		for (x = 0; x < d_breite; x++)
		{
			if (feld[x][y] == 0)
			{
				zeile[x] = ' ';
			}
			else
			{
				struct s_element * ele = (struct s_element *)feld[x][y];
				farbe(ele->farbwert);
				zeile[x] = 254;
			}
		}
		zeile[d_breite] = '\0';
		printf("%s%c\n", zeile, 186);
	}

	printf("   %c", 200);
	strich(d_breite, 205);
	printf("%c\n", 188);


	/*
	for (y = 0; y < d_hoehe; y++)
	{
	printf("   ");
	for (x = 0; x < d_breite; x++)
	{
	if (feld[x][y] == 0)
	{
	farbe(2);
	printf("%c", 254);
	}
	else
	{
	struct s_element * ele = (struct s_element *)feld[x][y];
	farbe(ele->farbwert);
	printf("%c", 254);
	}
	}
	printf("\n");
	}
	*/

	neuezeile(2);
}

void spiel()
{
	int feld[d_breite][d_hoehe] = { 0 };
	char zeichen = 'c';
	score = 0;
	drehpunkt.gesetzt = 0;
	drehpunkt.x = 0;
	drehpunkt.y = 0;

	NeuesElement(feld, &kopf);
	
	while (!ende)
	{
		int schneller = false;
		d_clearscreen;

		switch (eingabe())
		{
		case '1':
			ende = true;
			break;
		case 'a':
			bewegen(feld, -1);
		//	schneller = true;
			break;
		case 'd':
			bewegen(feld, 1);
		//	schneller = true;
			break;
		case 'w':
			drehen(feld, -1);
			break;
		case 'e':
			drehen(feld, 1);
			break;
		case 's':
			schneller = true;
			break;
		case '2':
			NeuesElement(feld, &kopf);
			break;
		}

		fallen(feld);
		spielfeld_zeichnen(feld);

		if (schneller)
		{
			_sleep(60);
		}
		else
		{
			_sleep(timer);
		}
	}

	SpeicherFreigeben(&kopf);
}


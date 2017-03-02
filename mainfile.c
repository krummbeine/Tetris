

#include <stdio.h>  /* Standard Input/Output  z.B. scanf, printf */
#include <stdlib.h>   /* Standard-Bibliothek, z.B. für system       */
#include "funktionen.h"
#include <string.h>
#include <conio.h>
#include <windows.h>
#define strich_laenge 90
#define BREITE 20
#define HOEHE 20

DWORD WINAPI ThreadFunc(void* data) 
{
	while (1)
	{
		const int C = 261;
		const int Cis = 277;
		const int D = 293;
		const int Dis = 311;
		const int E = 329;
		const int F = 349;
		const int Fis = 369;
		const int G = 391;
		const int Gis = 415;
		const int A = 440;
		const int Ais = 466;
		const int H = 493;
		const int Takt = 1700;

		Beep(E * 2, Takt / 4);
		Beep(H * 1, Takt / 8);
		Beep(C * 2, Takt / 8);
		Beep(D * 2, Takt / 4);
		Beep(C * 2, Takt / 8);
		Beep(H * 1, Takt / 8);
		Beep(A * 1, Takt / 4);
		Beep(A * 1, Takt / 8);
		Beep(C * 2, Takt / 8);
		Beep(E * 2, Takt / 8);
		Beep(E * 2, Takt / 8);
		Beep(D * 2, Takt / 8);
		Beep(C * 2, Takt / 8);
		Beep(H * 1, Takt / 2.5);
		Beep(C * 2, Takt / 8);
		Beep(D * 2, Takt / 4);
		Beep(E * 2, Takt / 4);
		Beep(C * 2, Takt / 4);
		Beep(A * 1, Takt / 4);
		Beep(A * 1, Takt / 4);
		Sleep(Takt / (8 / 3));
		Beep(D * 2, Takt / 3.25);
		Beep(F * 2, Takt / 8);
		Beep(A * 2, Takt / 8);
		Beep(A * 2, Takt / 8);
		Beep(G * 2, Takt / 8);
		Beep(F * 2, Takt / 8);
		Beep(E * 2, Takt / 3);
		Beep(C * 2, Takt / 8);
		Beep(E * 2, Takt / 8);
		Beep(E * 2, Takt / 8);
		Beep(D * 2, Takt / 8);
		Beep(C * 2, Takt / 8);
		Beep(H * 1, Takt / 4);
		Beep(H * 1, Takt / 8);
		Beep(C * 2, Takt / 8);
		Beep(D * 2, Takt / 4);
		Beep(E * 2, Takt / 4);
		Beep(C * 2, Takt / 4);
		Beep(A * 1, Takt / 4);
		Beep(A * 1, Takt / 4);
	}
	return 0;
}

int main()
{
	HANDLE thread = CreateThread(NULL, 0, ThreadFunc, NULL, 0, NULL);

	srand((unsigned int)time(NULL));

	spiel();

	// Ende
	{
		farbe(15);
		printf("\n%c Programm beendet \n", 219);
		system("pause");
		return 0;
	}
}



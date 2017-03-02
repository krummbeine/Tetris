
// ___________________________________________________________________________________  
//																  S T R U K T U R E N

typedef enum
{
	false,
	true
} t_bool;

typedef struct
{
	int x, y, gesetzt;
} t_punkt;

struct s_element
{
	int farbwert;
	t_punkt punkte[9];
	struct s_element *next;
};
 
// ___________________________________________________________________________________ 
//																  P R O T O T Y P E N

void spielfeld_zeichnen(int *);
char eingabe();
void spiel();
void farbe(int);
void neuezeile(int);
void NeuesElement(int *feld, struct s_element **);
void PunkteErzeugen(int *feld, t_punkt *, int, struct s_element **v_kopf);
int Farbe_erzeugen(int);
int fGesetzt(int position, int typ);
void fallen(int *feld);
void bewegen(int *feld, int);
void drehen(int *feld, int);
void strich(int, char);
void zeilenkill(int *feld);
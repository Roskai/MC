
#define VISUMEILLEUR 0 /* Si 1, visu de la meilleure solution connue    */
					   /* Si 0, visu en continu de la solution courante */
#include <math.h>
#include <stdlib.h>
#include <unistd.h>

#include "random.h"
#include "gnuplot.h"

double T;  /* Temperature T        */
double Ti; /* Temperature initiale */
double Tf; /* Temperature finale   */

double amplitude; /* Parametre d'amplitude dans transformation() */
double alpha;	  /* Facteur de decroissance de la temperature   */

int NbEssais;		/* Nb total de mouvements essayes              */
int MaxRepetitions; /* Nb. max de repetition a temp. constante     */

FILE *fdCout;
char *fileNameCout = "Cout";

FILE *fdResults;
char *fileNameResults = "Resultats";

FILE *fdGnuplotCout;

/*_________  Choix de la Fonction d'Evaluation   ___________________________*/
#define F(x) f1_2(x) /* ... et la 1ere fonction exemple (ci-dessous)   */
#define FNAME "f1_2" /* indiquer aussi son libelle (pour impressions)  */

/*_________  Etats du Recuit  ______________________________________________*/
double x0;			  /* Etat initial */
double x;			  /* Solution courante */
double y;			  /* Solution voisine */
double xopt;		  /* Solution optimale */
double fx, fy, fxopt; /* Valeurs */

/*________  Fonctions Exemples  (Fonction de co�t) _________________________*/
double f1_1(double t) { return t * t; }

double f1_2(double t)
{

	if (t <= 3.)
		return t * t;

	/* if (t >  3.) */
	return (5. * (t - 10.) * (t - 10.)) / 49. + 4.;
}

/*________  Voisinage (modification configuration)  ________________________*/
void transformation(void)
{
	y = x;									  /* y est au voisinage de x suivant l'amplitude */
	y = y + amplitude * (myRandom01() - 0.5); /* Apres y = x, modifier y (pas x!) */
}

/*________  Modification temp�rature  ______________________________________*/
double g(void)
{
#if 0
	return T * alpha; /* On decroit la temperature en utilisant T * alpha */
#else
	return T - alpha; /* On decroit la temperature en utilisant T - alpha */
#endif
}

/*------ visu du Cout -------- */
void visualiserCout(FILE *fd, char *fileName, int affichageObligatoire)
{
	static int i = 0;

	if (i % 100 == 0 || affichageObligatoire)
	{
#if 0 
  fprintf(fd,"plot \"%s\" with impulses\n",fileName);
  fflush(fd);
#else

		FILE *fdFileName;

		fdFileName = fopen(fileName, "r");
		if (fdFileName == NULL)
		{
			perror("fopen (dans visualiserCout)");
			fprintf(fd, "plot \"%s\" with impulses\n", fileName);
			fflush(fd);
		}
		else
		{

			long ind;
			double val;

			fprintf(fd, "plot '-' with impulses\n");

			fscanf(fdFileName, "%ld %lf", &ind, &val);
			if (ferror(fdFileName))
				perror("fscanf (dans visualiserCout)");

			while (!feof(fdFileName) && !ferror(fdFileName))
			{
				fprintf(fd, "%ld %f\n", ind, val);
				fflush(fd);
				fscanf(fdFileName, "%ld %lf", &ind, &val);
				if (ferror(fdFileName))
					perror("fscanf (dans visualiserCout)");
			}

			fprintf(fd, "e\n");
			fflush(fd);

			fclose(fdFileName);
		}
#endif
	}
	i++;
}

void ecrireCout(FILE *fdCout, int abscisse, double cout)
{
	if (fdCout == NULL)
		return;

	fprintf(fdCout, "%d %f\n", abscisse, cout);
	fflush(fdCout);
}

/*------ Sauvegarde fichier Resultats -------- */
void PrintParameters(FILE *fd)
{
	if (fd == NULL)
		return;

	fprintf(fd, "---> Parametres\n");
	fprintf(fd, "%-15s %s\n", "FNAME", FNAME);
	fprintf(fd, "%-15s %-.2f\n", "x0", x0);
	fprintf(fd, "%-15s %-.2f\n", "FNAME(x0)", F(x0));
	fprintf(fd, "%-15s %-.2f\n", "Ti", Ti);
	fprintf(fd, "%-15s %-.2f\n", "Tf", Tf);
	fprintf(fd, "%-15s %-.2f\n", "alpha", alpha);
	fprintf(fd, "%-15s %-.2f\n", "amplitude", amplitude);
	fprintf(fd, "%-15s %d\n", "MaxRepetitions", MaxRepetitions);

	fprintf(fd, "<---\n");
	fflush(fd);
}

void PrintTitleLine(FILE *fd)
{
	int n = 11;

	if (fd == NULL)
		return;

	fprintf(fd, "%-*s", n, "T");
	fprintf(fd, "%-*s", n, "NbEssais");
	fprintf(fd, "%-*s", n, " x");
	fprintf(fd, "%-*s", n, " f(x)");
	fprintf(fd, "%-*s", n, " xopt");
	fprintf(fd, "%-*s", n, " f(xopt)");

	fprintf(fd, "\n");
	fflush(fd);
}

void PrintALine(FILE *fd)
{
	int n = 11;

	if (fd == NULL)
		return;

	fprintf(fd, "%-*.2f", n, T);
	fprintf(fd, "%-*d", n, NbEssais);
	fprintf(fd, "%- *.2f", n, x);
	fprintf(fd, "%- *.2f", n, fx);
	fprintf(fd, "%- *.2f", n, xopt);
	fprintf(fd, "%- *.2f", n, fxopt);
	fprintf(fd, "\n");

	fflush(fd);
}

void Visu(double x, int affichageObligatoire)
{
	(void)x;
	visualiserCout(fdGnuplotCout, fileNameCout, affichageObligatoire);
}

void EcrireCoutEtVisu(double fx, double x, int affichageObligatoire)
{
	(void)fx;
	(void)x;
	(void)affichageObligatoire;
	ecrireCout(fdCout, NbEssais, fx);
	Visu(x, affichageObligatoire);
}

void FermetureFlots(void)
{
	if (fdResults != NULL)
		fclose(fdResults);

	fclose(fdCout);
	closeGnuplot(fdGnuplotCout);
}

/*________  Initialisation  ___________________________________________*/
int main(void)
{
	char rep;

	initRandom();

	printf("f(x)=%s\n", FNAME);

	printf("Etat initial (x0) ?\n");
	scanf("%lf", &x0);

	printf("TInit ?\n");
	scanf("%lf", &Ti);

	printf("TFin ?\n");
	scanf("%lf", &Tf);

	printf("Alpha ?\n");
	scanf("%lf", &alpha);

	printf("Ampli ?\n");
	scanf("%lf", &amplitude);

	printf("MaxRepetitions ?\n");
	scanf("%d", &MaxRepetitions);

	PrintParameters(stdout);

	do
	{
		printf("Sauvegarde des resultats dans un fichier? (o/n)\n");
		scanf("%c", &rep);
		while (rep == '\n')
		{
			scanf("%c", &rep);
		}
	} while (rep != 'o' && rep != 'n' && rep != 'O' && rep != 'N');

	if (rep == 'n' || rep == 'N')
		fdResults = NULL;
	else
	{
		fdResults = fopen(fileNameResults, "w");
		if (fdResults == NULL)
		{
			fprintf(stderr, "Probleme sur fopen(\"%s\",\"w\")\n", fileNameResults);
		}
	}

	/*  Si on veut avoir un en-tete d'identification */
	PrintParameters(fdResults);
	PrintTitleLine(fdResults);

	fdCout = fopen(fileNameCout, "w"); /* Ouverture du fichier pour les couts */
	if (fdCout == NULL)
	{
		fprintf(stderr, "Probleme sur fopen(\"%s\",\"w\")\n", fileNameCout);
		fprintf(stderr, "=> Arret du programme\n");
		fclose(fdResults);
		exit(EXIT_FAILURE);
	}

	fdGnuplotCout = openGnuplot(NULL); /* pipe + fork pour visu    */
	if (fdGnuplotCout == NULL)
	{
		fprintf(stderr, "Probleme sur openGnuplot => Arret du programme\n");
		fclose(fdResults);
		fclose(fdCout);
		exit(EXIT_FAILURE);
	}

	/*__ Recuit Simule  ___________________________________________*/

	x = xopt = x0;	   /* Configuration initiale */
	fx = fxopt = F(x); /* Cout initial           */

	T = Ti; /* Temperature initiale   */
	NbEssais = 0;

	EcrireCoutEtVisu(fx, x, 1);
	PrintALine(fdResults); /* Sauvegarde configuration initiale       */

	while (T > Tf)
	{ /* 1er critere d'arret */

		int rep;	  /* Nb de repetitions a temperature constante    */
		double p, Df; /* p: pour tirage aleatoire, Df: pour Delta f   */

		for (rep = 0; rep < MaxRepetitions; rep++)
		{ /* 2eme critere d'arret */

			transformation(); /* transformation => y, voisin de x */
			fy = F(y);

			Df = fy - fx; /* Nouveau - Ancien         */

			if (Df > 0)
			{		   /* Descente !!              */
				x = y; /* y devient l'etat courant */
				fx = fy;
				if (fx < fxopt)
				{ /* Mise a jour optimum ?    */
					xopt = x;
					fxopt = fx;
#if VISUMEILLEUR == 1
					EcrireCoutEtVisu(fxopt, xopt, 1);
#endif
				}
			}
			else
			{ /* Remontee : acceptee ??   */
				p = myRandom01();
				if (p <= exp(-(Df / T)))
				{
					x = y; /* y devient l'etat courant */
					fx = fy;
				}
			}

			NbEssais++;

#if VISUMEILLEUR != 1
			EcrireCoutEtVisu(fx, x, 0);
#endif
			PrintALine(fdResults); /* Sauvegarde resulats courants */
		}

		T = g(); /* modifier la temperature */

		usleep(10);
	} /* end while */

	printf("-------------------->\n");
	printf("Temperature a la fin de l'algorithme=%f\n", T);
	printf("Cout optimal (fxopt)=%f\n", fxopt);
	printf("<--------------------\n");
	Visu(xopt, 1);

	FermetureFlots();

	exit(EXIT_SUCCESS);
}

// Jeu des Allumettes
// HARNY Valentin - B1 EPSI
// C++

#include <iostream>
#include <cstdlib>
#include <string>
#include <ctime>
#include <windows.h>

using namespace std;

// Class Joueur
class Joueur {
public:
    string name;
    int age;
    int score;
};

// Afficher les chiffres sur 3 caract�res
string afficherChiffreSur3Caracteres(int a) {
    if (a >= 0) {
        if (a < 10) return " " + std::to_string(a) + " ";
        else return " " + std::to_string(a);
    } else {
        if (a > -10) return std::to_string(a) + " ";
        else return std::to_string(a);
    }
}

// Fonction pour afficher les allumettes
void afficherAllumettes(int *allumettes, int nbAllumettes)
{
    for (int i = 0; i < nbAllumettes; i++)
    {
        cout << " |  ";
    }
    cout << endl;


    for (int i = 0; i < nbAllumettes; i++)
    {
        cout << afficherChiffreSur3Caracteres(allumettes[i]) << " ";
    }
    cout << endl;

    for (int i = 0; i < nbAllumettes; i++)
    {
        cout << " |  ";
    }
    cout << endl << "Il reste : " << nbAllumettes << " allumettes." << endl;
}

// Affichage des scores
void afficherScores(Joueur *joueurs, int nbJoueurs)
{
    for (int i = 1; i < nbJoueurs; i++)
    {
    cout << " " <<joueurs[i].name << ": " << joueurs[i].score << endl;
    }
}

// Creation des Joueurs
void creationJoueur(Joueur *joueurs, int i)
{
    cout << "--------------------------------------" << endl;
    cout << "|           Infos Joueurs " << i << "          |" << endl;
    cout << "--------------------------------------" << endl;
    cout << "Nom > ";
    cin >> joueurs[i].name;

    // Verification age du joueur
    do
    {
        cout << "Age > ";
        cin >> joueurs[i].age;
        if (joueurs[i].age < 0 || joueurs[i].age > 120)
        {
            cout << "Age incorrect !" << endl;
        }
    }
    while(joueurs[i].age < 0 || joueurs[i].age > 120);

    // Score debut a 0 pour chaque joueur
    joueurs[i].score = 0;
    cout << endl;
}

int main()
{
    // Affichage debut du jeu
    system("color 0a");
    cout << "--------------------------------------" << endl;
    cout << "|       LE JEU DES ALLUMETTES        |" << endl;
    cout << "|                 c++                |" << endl;
    cout << "|           HARNY Valentin           |" << endl;
    cout << "--------------------------------------" << endl;
    Sleep(2000);
    system("cls");

    // Demande le nombre de joeurs
    int nbJoueurs(0);
    cout << "--------------------------------------" << endl;
    cout << "|          Nombre de Joueurs         |" << endl;
    cout << "--------------------------------------" << endl;

    //Verification du nombre de joueurs
    do
    {
        cout << "> ";
        cin >> nbJoueurs;
        if(nbJoueurs < 2 || nbJoueurs > 8)
        {
            cout << "Nombre de joueurs entre 2 et 8." << endl;
        }
    }
    while(nbJoueurs < 2 || nbJoueurs > 8);

    system("cls");
    nbJoueurs = nbJoueurs + 1;

    // initialisation des joueurs
    Joueur joueurs[nbJoueurs];
    for(int i=1; i<nbJoueurs; i++)
    {
        creationJoueur(joueurs, i);
    }

    system("cls");

    //Boucle qui permet de rejouer si on le souhaite
    string replay;

    while(replay != "N"){
        // Initialisation des scores à 0 ou Remise des scores à 0 en cas de nouvelle partie
        for(int i = 1; i < nbJoueurs; i++)
        {
            joueurs[i].score = 0;
        }

        // Demande le nombre d'allumettes
        int nbAllumettes;
        cout << "--------------------------------------" << endl;
        cout << "|     Nombre d'allumettes en jeu     |" << endl;
        cout << "--------------------------------------" << endl;

        do
        {
            cout << "> ";
            cin >> nbAllumettes;
            if(nbAllumettes < 10 || nbAllumettes > 50)
            {
                cout << "Le nombre d'allumettes doit etre compris entre 10 et 50." << endl;
            }
        }
        while(nbAllumettes < 10 || nbAllumettes > 50);

        system("cls");

        // Initialisation des allumettes (score al�atoire)
        srand(time(NULL));

        int allumettes[nbAllumettes];

        for (int i = 0; i < nbAllumettes; i++)
        {
            allumettes[i] = rand() % 21;
        }

        int joueurCourant = nbJoueurs - 1;

        // Boucle principale
        while (nbAllumettes > 0)
        {
            int input = 0;

            // Selection du Joueur
            joueurCourant = (joueurCourant + 1) % nbJoueurs;

            cout << "--------------------------------------" << endl;
            cout << "|         Tour du Joueur " << joueurs[joueurCourant].name <<"           |" << endl;
            cout << "--------------------------------------" << endl;

            // Affichage des allumettes et des scores
            cout << endl;
            afficherAllumettes(allumettes, nbAllumettes);
            cout << endl;
            afficherScores(joueurs, nbJoueurs);
            cout << endl;


            // Demande du nombre d'allumettes � retirer et v�rification de la validit�
            for (int i = 0; (input < 1 || input > 3 || input > nbAllumettes); i++)
            {
                cout << (i == 0 ? "Combien d'allumettes retirer (entre 1 et 3)?" : "Votre saisie est incorrecte !") << endl << "> ";
                cin >> input;
            }

            // Affiche le nombre d'allumettes retirees
            cout << "Vous avez retire " << input << "allumettes" << endl;

            // Calculer le score des allumettes retirees
            // Incrementer le score du joueur
            for (int i = 0; i < input; i++)
            {
                joueurs[joueurCourant].score += allumettes[nbAllumettes - 1 - i];
            }

            // D�cr�menter les allumettes restantes
            nbAllumettes -= input;

            system("cls");
        }

        //Scores finaux
        system("cls");

        cout << "--------------------------------------" << endl;
        cout << "|            Scores Joueurs          |" << endl;
        cout << "--------------------------------------" << endl << endl;

        afficherScores(joueurs, nbJoueurs);

        int Gagnant = 1;
        for (int i = 1; i < nbJoueurs; i++)
        {
            if (joueurs[i].score > joueurs[Gagnant].score) Gagnant = i;
        }
        // Affichage du gagnant
        cout << endl <<"Le gagnant est le joueur : " << joueurs[Gagnant].name << endl << endl;
        cout << "Voulez-vous rejouer ? (O = Oui & N = Non)" << endl << "> ";
        cin >> replay;

        system("cls");
    }
    return 0;
}

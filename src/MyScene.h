#ifndef CPP_QT_TPMINIPROJET_MYSCENE_H
#define CPP_QT_TPMINIPROJET_MYSCENE_H

#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QTimer>
#include <QTime>
#include <QGraphicsView>
#include <QHBoxLayout>
#include <iostream>
#include <QDebug>
#include <QKeyEvent>
#include <unistd.h>
#include <QMessageBox>
#include <QComboBox>
#include <QInputDialog>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QDialog>
#include <fstream>
#include <string>
#include <sstream>

class MyScene : public QGraphicsScene {
    Q_OBJECT

private:

    //pour connaitre le nombre de voitures maximum en mode entrainement (false = 1 voiture, true = 1 ou 2 voitures)
    bool voituresEntrainement;

    //pour savoir si le jeu est en pause (touche P)
    bool pause;

    //pour savoir si la partie est demarre
    bool demarrerPartie;

    //pour connaitre la position du joueur ( 0 = voie de gauche, 1 = voie centrale, 2 = voie de droite)
    int position;

    //pour connaitre le numero du skin du joueur ( 1 = tortue, 2 = escargot, 3 = humain)
    int skin;

    // compteur de collisions pour le mode entrainement (chaque fois qu'il y a une collision, il est incremente de 1)
    int collision;

    //compteur de points (chaque fois que la/les voitures arrivent en bas, il est incremente de 1)
    int points;

    //le niveau (pour connaitre la vitesse)
    int niveau;

    //le nombre de vies restantes
    int vies;

    //le mode de jeu (0 = entrainement, 1 = normal, 2 = difficile, 3 = extreme)
    int mode;

    //la vitesse des voitures en mode entrainement
    int vitesseEntrainement;

    //le temps du timer
    float timerInterval;

    //La couleur des voitures (1 = Rouge et 2 = Jaune)
    bool couleurVoiture;

    //Les phrases enregistrées
    //la phrase pour enregistrer le nom du joueur
    std::string username;
    //la phrase qui s'affiche quand le joueur est mort
    std::string messageMort;

    //le timer
    QTimer *timer;

    //Les deux parties du jeu (en haut les scores et en bas la zone de jeu)
    QGraphicsRectItem* score;
    QGraphicsRectItem* jeu;

    //Les images
    QGraphicsPixmapItem* voiture;
    QGraphicsPixmapItem* voiture2;
    QGraphicsPixmapItem* tortue;
    QGraphicsPixmapItem* etoile;
    QGraphicsPixmapItem* Explosion;
    QGraphicsPixmapItem* Vie;

    //Les zones de textes
    QGraphicsTextItem* texte;
    QGraphicsTextItem* texteCollision;
    QGraphicsTextItem* textePause;
    QGraphicsTextItem* texteNiveau;


public:

    //constructeur
    MyScene(QObject* parent = nullptr);

    //destructeur
    virtual ~MyScene();


    void additem();                //contient tous les add du constructeur

    //pour recommencer une partie
    void newGame();

    //renvoie les meilleurs scores et les pseudos dans un string
    std::string MeilleursScores(char* nom_fichier,int numberScores);

    //affiche du message de mort, demande pour recommencer...
    void mort();
    void messageDeMort(char* nom_fichier);   //gere le message de mort avec affichages des meilleurs scores

    //pour demarrer une partie dans un mode particulier
    void demarrerNormal();
    void demarrerDifficile();
    void demarrerExpert();
    void demarrerEntrainement();

    //pour mettre à jour les parametres
    void updatePoints();
    void updateNiveau();
    void updateCollision();
    void updateSkin();
    int updateMeilleursScores(char* nom_fichier);
    void updateCouleur();


    void fonctionPause();           //pour mettre en pause
    static void reglesDuJeu();      //pour afficher les regles du jeu
    void incrementeNiveau();        //augmente le niveau et la vitesse des voitures
    void avancerVoitures();         //fait avancer la ou les voitures
    void quitterJeu();              //demande à l'utilisateur s'il veut quitter le jeu
    void recommencerJeu();          //demande à l'utilisateur s'il veut recommencer le jeu
    void initialisationVariables(); //initialisation des variables avant le debut de la partie
    int positionAleatoire();        //renvoie un nombre entre 0 et 2 corresspondant à une voie
    void questionNiveau();          //demande à l'utilisateur le niveau qu'il veut faire
    void stopGame();                //Quitte la partie et sauvegarde les scores


    //accesseurs
    int getvoituresEntrainement() const;    //renvoie le nombre de voitures pour le mode entrainement et non true ou false
    int getvitesseEntrainement() const;     //renvoie la vitesse des voitures lors du mode entrainement
    std::string getskin() const;            //renvoie le nom du skin et non son numero
    bool getdemarrerPartie() const;         //renvoie True si la partie est demarré et False sinon
    bool getpause() const;                  //renvoie True si la partie est en pause et False sinon
    std::string getCouleur() const;         //Renvoie la couleur des voitures sous forme de string (rouge ou jaune)

    //mutateurs
    void editvoituresEntrainement(bool nb);     //permet de changer le nombre de voitures pour le mode entrainement
    void editskin(int num);                     //permet de changer le skin du joueur
    void editvitesseEntrainement(int vitesse);  //permet de changer la vitesse des voitures pour le mode entrainement
    void editCouleur(bool couleur);             //permet de changer la couleur des voitures


protected:

    //evenements avec les touches du clavier
    void keyPressEvent(QKeyEvent* event);

    //fonctions appelées par keyPressEvent
    void deplacementDroite();       //pour se deplacer dans une voie à droite
    void deplacementGauche();       //pour se deplacer dans une voie à gauche
    void arretModeEntrainement();   //pour arreter le mode entrainement
    void keyPause();                //pour mettre la partie en pause
    void demarrerJeu();             //pour demarrer la partie

public slots:

    void update();      //faire avancer le jeu

};


#endif //CPP_QT_TPMINIPROJET_MYSCENE_H

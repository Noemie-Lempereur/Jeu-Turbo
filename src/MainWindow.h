#ifndef CPP_QT_TPMINIPROJET_MAINWINDOW_H
#define CPP_QT_TPMINIPROJET_MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QMessageBox>
#include <string>

#include "MyScene.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

private :
    MyScene* mainScene;
    QGraphicsView* mainView;

    //Menu generaux
    QMenu* helpMenu;
    QMenu* jeuMenu;

    //Sous menus
    QMenu* menuMeilleursScores;
    QMenu* preferencesMenu;
    QMenu* menuEntrainement;


public:

    //Constructeur
    MainWindow(QWidget* parent = nullptr);

    //Destructeur
    virtual ~MainWindow();

    void pause();   //mettre en pause

public slots:

    //Informations sur le projet (Help)
    void slot_aboutMenu();

    //Informations sur le jeu (Jeu->Regles)
    void slot_reglesMenu();

    //Relancer une partie (Jeu->Recommencer)
    void slot_newGame();

    //Affiche les meilleurs scores (Jeu->Meilleurs Scores)
    void slot_meilleursNormal(int n=10);
    void slot_meilleursDifficile(int n=10);
    void slot_meilleursExtreme(int n=10);

    //Modifier les parametres du mode entrainement (Jeu->Entrainement)
    void slot_nombreVoiture();
    void slot_vitesseEntrainement();

    //Modifier le skin de l'utilisateur (Jeu->Preferences)
    void slot_skin();

    //Modifier la couleur des voitures (rouge ou jaune)
    void slot_couleur();

    //Affiche les commandes disponibles (Jeu->Commandes)
    void slot_commandesMenu();
};


#endif //CPP_QT_TPMINIPROJET_MAINWINDOW_H

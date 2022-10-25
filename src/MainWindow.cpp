#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{

    this->mainScene = new MyScene;

    this->mainView = new QGraphicsView;
    this->mainView->setScene(mainScene);


    //Fenetre de jeu
    this->setCentralWidget(mainView);
    this->setWindowTitle("Turbo");
    setWindowIcon(QIcon("./../ressources/voiture.png"));
    setCursor(QCursor(QPixmap("./../ressources/tortueCurseur.png")));
    this->resize(410, 560);

    //2 menus en haut
    jeuMenu = menuBar()->addMenu(tr("&Jeu"));
    helpMenu = menuBar()->addMenu(tr("&Help"));

    //Menu Help :
    //About donne des informations sur le projet
    QAction* actionHelp = new QAction(tr("&About"), this);
    connect(actionHelp, SIGNAL(triggered()), this, SLOT(slot_aboutMenu()));
    helpMenu->addAction(actionHelp);

    //Menu Jeu :
    //Recommencer : permet de relancer une partie
    QAction* actionRecommencer= new QAction(tr("&Recommencer"), this);
    connect(actionRecommencer, SIGNAL(triggered()), this, SLOT(slot_newGame()));
    jeuMenu->addAction(actionRecommencer);

    //Menu Jeu :
    //Regles : affiche les regles du jeu
    QAction* actionRegle = new QAction(tr("&Règles"), this);
    connect(actionRegle, SIGNAL(triggered()), this, SLOT(slot_reglesMenu()));
    jeuMenu->addAction(actionRegle);

    //Menu Jeu :
    //Commandes: affiche les commandes du jeu
    QAction* actionCommandes = new QAction(tr("&Commandes"), this);
    connect(actionCommandes, SIGNAL(triggered()), this, SLOT(slot_commandesMenu()));
    jeuMenu->addAction(actionCommandes);

    //Menu Jeu :
    //Menu Meilleurs Scores:
    menuMeilleursScores = new QMenu(tr("&Meilleurs Scores"), this);
    jeuMenu->addMenu(menuMeilleursScores);

    //Menu Jeu :
    //Menu Meilleurs Scores:
    //Mode Normal : affiche les meilleurs scores du mode normal
    QAction* actionMeilleursScoresNormal = new QAction(tr("&Mode Normal"), menuMeilleursScores);
    connect(actionMeilleursScoresNormal, SIGNAL(triggered()), this, SLOT(slot_meilleursNormal()));
    menuMeilleursScores->addAction(actionMeilleursScoresNormal);

    //Menu Jeu :
    //Menu Meilleurs Scores:
    //Mode Difficile : affiche les meilleurs scores du mode difficile
    QAction* actionMeilleursScoresDifficile = new QAction(tr("&Mode Difficile"), menuMeilleursScores);
    connect(actionMeilleursScoresDifficile, SIGNAL(triggered()), this, SLOT(slot_meilleursDifficile()));
    menuMeilleursScores->addAction(actionMeilleursScoresDifficile);

    //Menu Jeu :
    //Menu Meilleurs Scores:
    //Mode Extreme : affiche les meilleurs scores du mode extreme
    QAction* actionMeilleursScoresExtreme = new QAction(tr("&Mode Extreme"), menuMeilleursScores);
    connect(actionMeilleursScoresExtreme, SIGNAL(triggered()), this, SLOT(slot_meilleursExtreme()));
    menuMeilleursScores->addAction(actionMeilleursScoresExtreme);

    //Menu Jeu :
    //Menu Entrainement : permet de modifier les parametres du mode entrainement
    menuEntrainement = new QMenu(tr("&Entrainement"), this);
    jeuMenu->addMenu(menuEntrainement);

    //Menu Jeu :
    //Menu Entrainement : permet de modifier les parametres du mode entrainement
    //Nombre de Voitures : permet de choisir le nombre de voitures en mode entrainement (1 ou 2)
    QAction* actionNbVoitures = new QAction(tr("&Nombre de Voitures"), menuMeilleursScores);
    connect(actionNbVoitures, SIGNAL(triggered()), this, SLOT(slot_nombreVoiture()));
    menuEntrainement->addAction(actionNbVoitures);

    //Menu Jeu :
    //Menu Entrainement : permet de modifier les parametres du mode entrainement
    //Vitesse : permet de choisir la vitesse en mode entrainement (1 à 10)
    QAction* vitesseEntrainement = new QAction(tr("&Vitesse"), menuMeilleursScores);
    connect(vitesseEntrainement, SIGNAL(triggered()), this, SLOT(slot_vitesseEntrainement()));
    menuEntrainement->addAction(vitesseEntrainement);

    //Menu Jeu :
    //Menu Preference :
    preferencesMenu = new QMenu(tr("&Preferences"), this);
    jeuMenu->addMenu(preferencesMenu);

    //Menu Jeu :
    //Menu Preference :
    //Skin : permet de changer le skin du joueur
    QAction* actionSkin = new QAction(tr("&Skin"), menuMeilleursScores);
    connect(actionSkin, SIGNAL(triggered()), this, SLOT(slot_skin()));
    preferencesMenu->addAction(actionSkin);

    //Menu Jeu :
    //Menu Preference :
    //Voiture : permet de changer la couleur des voitures
    QAction* actionCouleur = new QAction(tr("&Voiture"), menuMeilleursScores);
    connect(actionCouleur, SIGNAL(triggered()), this, SLOT(slot_couleur()));
    preferencesMenu->addAction(actionCouleur);



}

MainWindow::~MainWindow(){

}

void MainWindow::slot_aboutMenu(){
    pause();    //Mettre pause sur la partie en cours
    QMessageBox::information(this, "Turbo", "Projet de QT/C++ fait par Noémie LEMPEREUR en CIR2 (année 2021)");     //affiche des informations sur le jeu
}

void MainWindow::slot_reglesMenu(){
    pause();    //Mettre pause sur la partie en cours
    mainScene->reglesDuJeu();       //affiche les regles du jeu
}

void MainWindow::slot_newGame(){        //Permet de recommencer une partie

    pause();    //Mettre pause sur la partie en cours

    //Verifie que l'utilisateur veut bien recommencer une partie en lui posant la question
    int reponse = QMessageBox::information(nullptr, QString("Turbo"), QString("Voulez-vous recommencer une partie?\nATTENTION : Votre score ne sera pas enregistré\nPour enregistrer votre score, quitter avec la touche 'Q'"), QMessageBox ::Yes | QMessageBox::No);
    if (reponse == QMessageBox::Yes){
        mainScene->newGame();
    }
}


void MainWindow::slot_meilleursNormal(int n) {      //affiche les meilleurs scores du mode normal

    pause();    //Mettre pause sur la partie en cours

    std::string text;
    text="*----------*Meilleurs Scores*----------*\n    Score:         Pseudo: ";
    text+=mainScene->MeilleursScores("./../ressources/MeilleursScoresNormal.txt",n);

    //Demande à l'utilisateur combien de score il veut afficher
    QStringList nbMeilleuresList;
    nbMeilleuresList <<QString::fromUtf8("0")<<QString::fromUtf8("5") <<QString::fromUtf8("10")<<QString::fromUtf8("25")<<QString::fromUtf8("50")<<QString::fromUtf8("75")<<QString::fromUtf8("100");
    QString nbMeilleurs =QInputDialog::getItem(nullptr, "Turbo", QString::fromStdString(text)+"\n\nCombien de scores voulez-vous voir ?", nbMeilleuresList, 0,false);

    if(!nbMeilleurs.isEmpty()) {
        if(nbMeilleurs=="5" or nbMeilleurs=="10" or nbMeilleurs=="25" or nbMeilleurs=="50" or nbMeilleurs=="75" or nbMeilleurs=="100") {
            //affiche le nombre de meilleurs scores que veut voir l'utilisateur
            slot_meilleursNormal(nbMeilleurs.toInt());
        }
    }
}

void MainWindow::slot_meilleursDifficile(int n) {      //affiche les meilleurs scores du mode difficile

    pause();    //Mettre pause sur la partie en cours

    std::string text;
    text="*----------*Meilleurs Scores*----------*\n    Score:         Pseudo: ";
    text+=mainScene->MeilleursScores("./../ressources/MeilleursScoresDifficile.txt",n);

    //Demande à l'utilisateur combien de score il veut afficher
    QStringList nbMeilleuresList;
    nbMeilleuresList <<QString::fromUtf8("0")<<QString::fromUtf8("5") <<QString::fromUtf8("10")<<QString::fromUtf8("25")<<QString::fromUtf8("50")<<QString::fromUtf8("75")<<QString::fromUtf8("100");
    QString nbMeilleurs =QInputDialog::getItem(nullptr, "Turbo", QString::fromStdString(text)+"\n\nCombien de scores voulez-vous voir ?", nbMeilleuresList, 0,false);
    if(!nbMeilleurs.isEmpty()) {
        if(nbMeilleurs=="5" or nbMeilleurs=="10" or nbMeilleurs=="25" or nbMeilleurs=="50" or nbMeilleurs=="75" or nbMeilleurs=="100") {
            //affiche le nombre de meilleurs scores que veut voir l'utilisateur
            slot_meilleursDifficile(nbMeilleurs.toInt());
        }
    }
}

void MainWindow::slot_meilleursExtreme(int n) {         //affiche les meilleurs scores du mode difficile

    pause();    //Mettre pause sur la partie en cours

    std::string text;
    text="*----------*Meilleurs Scores*----------*\n    Score:         Pseudo: ";
        text+=mainScene->MeilleursScores("./../ressources/MeilleursScoresExpert.txt",n);

    //Demande à l'utilisateur combien de score il veut afficher
    QStringList nbMeilleuresList;
    nbMeilleuresList <<QString::fromUtf8("0")<<QString::fromUtf8("5") <<QString::fromUtf8("10")<<QString::fromUtf8("25")<<QString::fromUtf8("50")<<QString::fromUtf8("75")<<QString::fromUtf8("100");
    QString nbMeilleurs =QInputDialog::getItem(nullptr, "Turbo", QString::fromStdString(text)+"\n\nCombien de scores voulez-vous voir ?", nbMeilleuresList, 0,false);
    if(!nbMeilleurs.isEmpty()) {
        if(nbMeilleurs=="5" or nbMeilleurs=="10" or nbMeilleurs=="25" or nbMeilleurs=="50" or nbMeilleurs=="75" or nbMeilleurs=="100") {
            //affiche le nombre de meilleurs scores que veut voir l'utilisateur
            slot_meilleursExtreme(nbMeilleurs.toInt());
        }
    }
}

void MainWindow::slot_nombreVoiture(){      //Pour modifier le nombre de voitures pour le mode entrainement

    pause();    //Mettre pause sur la partie en cours

    //Le nombre de voiture(s) en ce moment
    std::string texte="Actuellement, ";
    texte+=std::to_string(mainScene->getvoituresEntrainement());
    texte+=" voiture(s) circule(nt).";

    //Question pour savoir combien l'utilisateur en veut
    QStringList nbVoitureList;
    nbVoitureList <<QString::fromUtf8("1 voiture") <<QString::fromUtf8("2 voitures");
    QString nbVoitures =QInputDialog::getItem(nullptr, "Turbo", QString::fromStdString(texte)+"\n\nCombien de voitures maximum voulez-vous voir\ncirculer en même temps pour le mode entrainement?", nbVoitureList, 0,false);
    if(!nbVoitures.isEmpty()) {
        //Modifie les parametres avec la reponse
        if(nbVoitures=="1 voiture") {
            mainScene->editvoituresEntrainement(0);
        }
        if(nbVoitures=="2 voitures") {
            mainScene->editvoituresEntrainement(1);
        }
    }
}

void MainWindow::slot_vitesseEntrainement(){    //Pour modifier la vitesse des voitures en mode entrainement

    pause();    //Mettre pause sur la partie en cours

    //La vitesse actuelle
    std::string texte="Actuellement, la vitesse d'entrainement est : ";
    texte+=std::to_string(mainScene->getvitesseEntrainement());
    texte+=" \n(plus celle-ci est grande, plus les voitures iront vite";

    //Question pour savoir quelle vitesse veut l'utilisateur
    QStringList VitesseList;
    VitesseList <<QString::fromUtf8("1") <<QString::fromUtf8("2")<<QString::fromUtf8("3") <<QString::fromUtf8("4")<<QString::fromUtf8("5") <<QString::fromUtf8("6")<<QString::fromUtf8("7") <<QString::fromUtf8("8")<<QString::fromUtf8("9") <<QString::fromUtf8("10");
    QString numVitesse =QInputDialog::getItem(nullptr, "Turbo", QString::fromStdString(texte)+"\n\nA quelle vitesse voulez-vous voir circuler\nles voitures pour le mode entrainement?", VitesseList, 0,false);
    if(!numVitesse.isEmpty()) {
        //Modifie les parametres avec la reponse
        mainScene->editvitesseEntrainement(11-numVitesse.toInt());
    }
}

void MainWindow::slot_skin() {      //pour pouvoir changer le skin

    pause();    //Mettre pause sur la partie en cours

    //Le skin actuel
    std::string texte="Actuellement, votre skin est : ";
    texte+=mainScene->getskin();
    texte+=" \n";

    //La question pour savoir le skin qu'il voudrait
    QStringList SkinList;
    SkinList <<QString::fromUtf8("Tortue") <<QString::fromUtf8("Escargot")<<QString::fromUtf8("Humain");
    QString skinQuestion =QInputDialog::getItem(nullptr, "Turbo", QString::fromStdString(texte)+"\n\nQuel skin voulez-vous ?", SkinList, 0,false);
    if(!skinQuestion.isEmpty()) {
        //modification du skin
        if(skinQuestion=="Tortue") {
            mainScene->editskin(1);
        }
        if(skinQuestion=="Escargot") {
            mainScene->editskin(2);
        }
        if(skinQuestion=="Humain") {
            mainScene->editskin(3);
        }
    }
    //prise en compte dans la partie du changement de skin
    mainScene->updateSkin();
}

void MainWindow::pause() {  //mettre le jeu en pause

    if(mainScene->getdemarrerPartie() and !mainScene->getpause()){
        mainScene->fonctionPause();
    }

}

void MainWindow::slot_commandesMenu() {     //affiche dans une nouvelles fenetres, les commandes du jeu

    pause();            //Mettre pause sur la partie en cours

    QMessageBox msgBox;
    msgBox.setWindowTitle("Turbo");
    msgBox.setWindowIcon(QIcon("./../ressources/voiture.png"));
    msgBox.setText("*------------------------------------* Commandes *------------------------------------*\n\n - Touches \"<-\" et \"->\" pour se déplacer\n\n - Touche \"P\" pour mettre en pause ou reprendre le jeu\n\n - Touche \"G\" pour lancer la partie\n\n - Touche \"N\" pour redémarrer une partie\n\n - Touche \"Q\" pour arrêter la partie en enregistrant le score\n\n - Touche \"R\" pour afficher les règles du jeu\n\n - Touche \"Echap\" pour quitter l'application");
    msgBox.setModal(true); // on souhaite que la fenetre soit modale i.e qu'on ne puisse plus cliquer ailleurs
    msgBox.exec();
}

void MainWindow::slot_couleur() {           //pour pouvoir changer la couleur des voitures : rouge ou jaune

    pause();            //Mettre pause sur la partie en cours

    //La couleur des voitures actuellement
    std::string texte="Actuellement, les voitures sont : ";
    texte+=mainScene->getCouleur();
    texte+=" \n";

    //Quetion pour savoir la couleur des voitures qui lui plairais (rouge ou jaune)
    QStringList CouleurList;
    CouleurList <<QString::fromUtf8("Rouge") <<QString::fromUtf8("Jaune");
    QString CouleurQuestion =QInputDialog::getItem(nullptr, "Turbo", QString::fromStdString(texte)+"\n\nQuel couleur de voiture voulez-vous ?", CouleurList, 0,false);
    if(!CouleurQuestion.isEmpty()) {
        //Modification des parametres du jeu
        if(CouleurQuestion=="Rouge") {
            mainScene->editCouleur(1);
        }
        if(CouleurQuestion=="Jaune") {
            mainScene->editCouleur(0);
        }
    }
    //prise en compte dans la partie du changement de couleur des voitures
    mainScene->updateCouleur();
}


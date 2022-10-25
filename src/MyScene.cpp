
#include "MyScene.h"

using namespace std;

//tableau contenant les 3 positions des voies (permet d'afficher correctement dans les voies les voitures et l'utilisateur
int table[3]={85,165,245};


MyScene::MyScene(QObject* parent) : QGraphicsScene(parent){


    //Initialisation des variables
    initialisationVariables();


    //initialisation des deux zones
    score = new QGraphicsRectItem(1, 0, 396, 50);
    jeu = new QGraphicsRectItem(1, 50, 396, 475);


    //initialisation de la premiere voiture
    voiture = new QGraphicsPixmapItem();
    //Place la voiture dans une position aleatoire grace au tableau
    voiture->setPos(table[positionAleatoire()], 50);
    //Permet d'afficher l'image de la première voiture
    voiture->setPixmap(QPixmap("./../ressources/voiture.png"));


    //Initialisation de la deuxieme voiture (pas d'image car pour certains modes, on n'en a pas besoin)
    voiture2 = new QGraphicsPixmapItem();
    voiture2->setPixmap(QPixmap());


    //Initialisation des parametres par default pour le mode entrainement
    //le niveau en mode entrainement est par default 5 (11-5=6)
    vitesseEntrainement=6;  //6 correspond au timerInterval pour le mode entrainement
    //il n'y a qu'une voiture par default en mode entrainement
    voituresEntrainement=false;


    //Permet d'afficher le skin du joueur (qui est une tortue lors du lancement du jeu
    tortue = new QGraphicsPixmapItem();
    //On place la tortue sur la voie centrale
    tortue->setPos(160, 450);
    skin=1;     //skin = 1 <=> le skin est une tortue, skin = 2 <=> le skin est un escargot et skin = 3 <=> le skin est un humain
    //On lui affecte l'image de la tortue
    tortue->setPixmap(QPixmap("./../ressources/tortue.png"));


    //Permet de montrer visuellement au joueur son nombre de vie (au debut 0,1 ou 3 selon le mode de jeu)
    Vie = new QGraphicsPixmapItem();
    //On place les vies en haut à droite de la fenetre
    Vie->setPos(230, 10);


    //Ajoute une image de fond sur les deux zones (route et drapeau)
    score->setBrush(QPixmap("./../ressources/drapeau.png"));
    jeu->setBrush(QPixmap("./../ressources/route.PNG"));


    //Afficher à coté du score une etoile
    etoile = new QGraphicsPixmapItem();
    //On positionne l'etoile dans la fenetre
    etoile->setPos(115, 4);
    //On lui affecte l'image de l'etoile
    etoile->setPixmap(QPixmap("./../ressources/etoile.png"));

    couleurVoiture=true;


    //Initialisation d'une QGraphicsPixmapItem qui contiendra l'image de l'explosion (pour quand la tortue est morte)
    Explosion = new QGraphicsPixmapItem();


    //Texte qui affiche le score
    texte = new QGraphicsTextItem();
    //On regle la police et la taille du texte
    texte->setFont(QFont("Comic Sans MS", 16));
    //On ecrit en jaune sur fond noir le score
    texte->setHtml(
            QString("<div style='background-color: black;'><div style=\"color:yellow;\"><b> Score : 0 </b> </div></div>"));


    //TexteCollision pour le mode entrainement (affiche le nombre de collisions)
    texteCollision = new QGraphicsTextItem();
    //On regle la police et la taille du texte
    texteCollision->setFont(QFont("Comic Sans MS", 16));
    //On positionne le texte dans la fenetre
    texteCollision->setPos(165, 0);
    //On n'affiche pas de texte pour l'instant (utile qu'avec le mode entrainement)
    texteCollision->setHtml(QString(""));


    //Texte qui affiche le niveau (le niveau est une indication de la vitesse, n'apparait pas lors d'une partie en entrainement)
    texteNiveau = new QGraphicsTextItem();
    //On regle la police et la taille du texte
    texteNiveau->setFont(QFont("Comic Sans MS", 8));
    //On ecrit en jaune sur fond noir le score
    texteNiveau->setPos(0, 25);texteNiveau->setHtml(
            QString("<div style='background-color: black;'><div style=\"color:yellow;\"><b> Niveau : 1 </b> </div></div>"));


    //Texte qui indique que le jeu est en pause lorsque l'utilisateur a mis le jeu en pause (touche 'P') :
    textePause = new QGraphicsTextItem();
    //On regle la police et la taille du texte
    textePause->setFont(QFont("Comic Sans MS", 10));
    //On positionne le texte dans la fenetre
    textePause->setPos(0, 250);
    //On n'affiche pas de texte pour l'instant
    textePause->setHtml("");


    //Ajoute tous les items à la fenetre
    additem();


    //Initialisation du timer
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));


    //Fenetre de debut
    //Creation d'un menu deroulant pour lancer le jeu dans un mode particulier
    QStringList nivList;
    //la liste contient tous les noms des niveaux + règles pour permettre à l'utilisateur de rapidement connaitre les regles et lancer une partie
    nivList <<QString::fromUtf8("Normal") <<QString::fromUtf8("Difficile") <<QString::fromUtf8("Extreme")<<QString::fromUtf8("Entrainement")<<QString::fromUtf8("Règles");

    QInputDialog dialogueFen;
    //dialogueFen est la fenetre qui va s'ouvrir pour demander le mode de jeu que l'utilisateur veut lancer
    dialogueFen.setWindowIcon(QIcon("./../ressources/voiture.png"));
    QString nivQuestion =dialogueFen.getItem(nullptr, "Turbo", "Quel niveau voulez-vous faire ?\nSi vous lancez le jeu pour la première fois, allez voir les règles ;)", nivList, 0,false);

    if(!nivQuestion.isEmpty()) {    //On verifie qu'il y a une reponse
        if(nivQuestion=="Normal") { //lent, 1 voiture, 3 vies
            demarrerNormal();       //on demarre la partie en mode normal
        }
        if(nivQuestion=="Difficile") {  //plus rapide que normal, 1 à 2 voitures, 3 vies
            demarrerDifficile();       //on demarre la partie en mode difficile
        }
        if(nivQuestion=="Extreme") { //plus rapide que difficile, 1 à 2 voitures, 1 vie
            demarrerExpert();       //on demarre la partie en mode extreme
        }
        if(nivQuestion=="Entrainement") {   //mode infini de vies, 1 à 2 voitures (choix pouvant etre modifie dans les parametres)
            demarrerEntrainement();       //on demarre la partie en mode entrainement
        }
        if(nivQuestion=="Règles") {         //affiche les regles du jeu
            reglesDuJeu();
            newGame();
        }
    }
}

MyScene::~MyScene() {

}

void MyScene::update(){

    QPointF pos = voiture->pos();       //recupere la position de la premiere voiture

    if(pos.ry()<475) {
        //Fais avancer la/les voiture(s) jusqu'en bas de la fenetre (475)
        avancerVoitures();

    }else {
        //si la voiture est arrive en bas :

        //Incremente le compteur points
        points = points + 1;

        //Modifie la difficulté en fonction du nombre de points (acceleration progressive)
        updateNiveau();

        //Fait reapparaitre la voiture en haut sur une voie aléatoire
        //positionAleatoire -> Nombre aleatoire 0,1 ou 2 qui correspond à la voie sur laquelle va apparaitre la premiere voiture
        voiture->setPos(table[positionAleatoire()], 50);

        //Fait reapparaitre la deuxieme voiture en haut sur une voie aléatoire si on est dans un mode de jeu à 2 voitures
        if (mode==2 or mode==3 or (mode==0 and voituresEntrainement==1)) {
            //positionAleatoire -> Nombre aleatoire 0,1 ou 2 qui correspond à la voie sur laquelle va apparaitre la deuxieme voiture (elle peut etre par dessus la premiere voiture)
            //Permet d'afficher la deuxieme voiture
            voiture2->setPos(table[positionAleatoire()], 50);
        }

        //Permet de garder un bon affichage du nombre de points (deplace l'etoile par rapport aux nombres de chiffres)
        updatePoints();
    }

    //si une des voitures entre en collision avec le joueur, il doit perdre une vie ou augmenter le nombre de collision selon le mode de jeu
    if (voiture->collidesWithItem(tortue) or voiture2->collidesWithItem(tortue)) {

        //Gere les collisions (gestion des vies, demande pour recommencer si mort...)
        updateCollision();
    }
}


void MyScene::keyPressEvent(QKeyEvent* event){  //interaction avec le clavier de l'utilisateur

    if(event->key() == Qt::Key_Right){  //flèche de droite pour deplacer le personnage à droite
        deplacementDroite();
    }

    if(event->key() == Qt::Key_Left){//flèche de gauche pour deplacer le personnage à gauche
        deplacementGauche();
    }

    if(event->key() == Qt::Key_Q){  //touche Q pour arreter le jeu
        stopGame();
    }

    if(event->key() == Qt::Key_P){//touche P pour mettre le jeu en pause ou reprendre
        keyPause();
    }

    if(event->key() == Qt::Key_G) {//touche G pour demarrer le jeu
        demarrerJeu();
    }

    if(event->key() == Qt::Key_N) {//touche N pour recommencer une partie
        fonctionPause();
        //Redemander s'il veut recommencer une partie au cas où ca serait une erreur
        int reponse = QMessageBox::question(nullptr, QString("Turbo"), QString("Voulez vous vraiment lancer une nouvelle partie ?"), QMessageBox ::Yes | QMessageBox::No);

        if (reponse == QMessageBox::Yes) {
            stopGame();
            newGame(); //Lancement nouvelle partie
        }
    }

    if(event->key() == Qt::Key_Escape){ // touche echap pour fermer completement l'application sans erreur (exit code 0)
        fonctionPause();
        quitterJeu();
    }

    if(event->key() == Qt::Key_R){ // touche R pour afficher les règles du jeu
        fonctionPause();
        reglesDuJeu();
    }
}

void MyScene::newGame() {

    //Initialisation des variables aux parametres par default
    initialisationVariables();

    //On cache la voiture 2
    voiture2->setPixmap(QPixmap("./../ressources/vide.png"));

    //On n'affiche pas de texte pour l'instant (utile qu'avec le mode entrainement)
    texteCollision->setHtml(QString(""));

    //positionAleatoire -> Nombre aleatoire 0,1 ou 2 qui correspond à la voie sur laquelle va apparaitre la premiere voiture
    //Permet d'afficher la premiere voiture sur une voie aleatoire
    voiture->setPos(table[positionAleatoire()], 50);

    //l'utilisateur est remis sur la voie centrale
    tortue->setPos(160,450);

    //l'etoile retourne à sa position de départ
    etoile->setPos(115,4);

    //le texte affichant le score est remis à 0
    texte->setHtml(QString("<div style='background-color: black;'><div style=\"color:yellow;\"><b> Score : 0 </b> </div></div>"));

    //le texte affichant le niveau est remis à 1
    texteNiveau->setHtml(QString("<div style='background-color: black;'><div style=\"color:yellow;\"><b> Niveau : 1 </b> </div></div>"));

    //l'explosion disparait
    Explosion->setPixmap(QPixmap());

    //demande le mode de jeu à l'utilisateur
    questionNiveau();
}

string MyScene::MeilleursScores(char* nom_fichier,int numberScores) { //Permet de retourner une phrase avec les meilleurs scores

    //Recuperer nombre de meilleurs scores enregistrés et stocker dans la variable numberScoresTotal
    ifstream fichier(nom_fichier);
    string ligne;
    int numberScoresTotal=0;
    getline(fichier,ligne);
    stringstream ss(ligne);
    ss>>numberScoresTotal;

    //Ouverture du fichier
    ifstream monfichier;
    stringstream s;
    int sco=0;
    string pse;
    monfichier.open(nom_fichier);
    string result;
    int num=numberScores;

    //Regarde s'il y a assez de scores enregistrés pour les lire
    //(si on veut lire 5 scores alors qu'il y en a que 3, on doit afficher les 3 sans erreurs)
    if(numberScores>numberScoresTotal){
        num=numberScoresTotal;  //num correspond au nombre de score qu'on retournera
    }

    //recupere les scores et les pseudos et les stocke dans le string result
    if (monfichier.is_open()){
        for(int i=1;i<=num;i++) {
            getline(monfichier,ligne);
            if(i==1) {
                s << monfichier.rdbuf();
            }
            s >> sco >> pse;            //recuperation du score et du pseudo
            result+="\n";
            result+= to_string(i);      //i est un int on doit donc le transformer pour qu'il apparaisse bien dans le string
            result+=") ";
            result+= to_string(sco);    //sco est un int on doit donc le transformer pour qu'il apparaisse bien dans le string


            if(sco<10 and i<10){                 //gestion des espaces pour le result
                result+= "  ";
            }
            if((sco<100 and i<10) or (sco<10 and i<100 )){
                result+= "  ";
            }
            if((sco<1000 and i<10) or (sco<100 and i<100) or (sco<10 and i<1000 )){
                result+= "  ";
            }
            if((sco<10000 and i<10) or (sco<1000 and i<100) or (sco<100 and i<1000 )){
                result+= "  ";
            }
            if((sco<100000 and i<10) or (sco<10000 and i<100) or (sco<1000 and i<1000 )){
                result+= "  ";
            }
            if(sco>100000){
                result+= "       ";
            }
            result+= pse;
        }
    }
    monfichier.close();     //on ferme le fichier
    return result;          //on retourne le string qui contient tous les resultats
}

void MyScene::updatePoints() { //Permet de garder un bon affichage du nombre de points (deplace l'etoile par rapport aux nombres de chiffres)

    //Mettre le texte des scores à jour
    texte->setHtml(QString(R"(<div style='background-color: "black";'><div style="color:yellow;"><b>)") + QString("Score : %1").arg(points) + QString("</b> </div></div>"));

    if (points < 100 and points > 9) {
            etoile->setPos(129, 4);     //on deplace l'etoile pour qu'elle soit à côté des points
    } else {
        if (points < 1000 and points > 9) {
            etoile->setPos(143, 4);
        } else {
            if (points < 10000 and points > 9) {
                etoile->setPos(157, 4);
            } else {
                etoile->setPos(171, 4);
            }
        }
    }
}

void MyScene::updateNiveau() { //Modifie la difficulté en fonction du nombre de points (acceleration)

    //on veut augmenter la difficulé progressivement dans les modes : normal, difficile et extreme
    //timerInterval doit toujours être supérieur à 1 car sinon les voitures ne s'affichent pas correctement (elles se teleportent)
    if((mode==3  or mode==1 or mode==2) and timerInterval>=1) {
        if (points < 40 and points % 5 == 0) {  //tant que le score est inferieur à 40, on augmente le niveau tous les 5 points
            if (points > 4) {
                incrementeNiveau();
            }
        } else {
            if (points < 100 and points % 10 == 0) {    //quand le score est inferieur à 100 et superieur à 40, on augmente le niveau tous les 10 points
                incrementeNiveau();
            } else {
                if (points % 15 == 0) { //quand le score est superieur à 100, on augmente le niveau tous les 15 points
                    incrementeNiveau();
                }
            }
        }
    }
}

void MyScene::updateCollision() {   //Gere les collisions (gestion des vies, demande pour recommencer si mort...)

    //On incremente le compteur collision
    collision=collision+1;

    //On fait apparaitre aléatoirement la voiture 1 sur une des 3 voies
    //positionAleatoire -> Nombre aleatoire 0,1 ou 2 qui correspond à la voie sur laquelle va apparaitre la premiere voiture
    voiture->setPos(table[positionAleatoire()], 50);

    //On fait apparaitre aléatoirement la voiture 2 sur une des 3 voies (s'il y a 2 voitures)
    if (mode==2 or mode==3 or (mode==0 and voituresEntrainement)) {
        //positionAleatoire -> Nombre aleatoire 0,1 ou 2 qui correspond à la voie sur laquelle va apparaitre la deuxieme voiture (elle peut etre par dessus la premiere voiture)
        voiture2->setPos(table[positionAleatoire()], 50);
    }

    //Si on n'est pas en mode entrainement, alors le compteur de vies est décrémenté et on affiche le nouveau nombre de vies
    if(mode != 0) {
        vies = vies - 1;
        switch (vies) {
            case 0 : {  //si l'utilisateur n'a plus de vies, alors il est mort
                mort();
                break;
            }
            case 1 : {  //si l'utilisateur a 1 vie, alors on affiche 1 laitue (representation des vies)
                Vie->setPixmap(QPixmap("./../ressources/vies1.png"));
                break;
            }
            case 2 : {  //si l'utilisateur a 2 vies, alors on affiche 2 laitues (representation des vies)
                Vie->setPixmap(QPixmap("./../ressources/vies2.png"));
                break;
            }
            default:
                cout << "ERREUR" << collision << endl;
        }
    }else{  //si on est en mode entrainement, alors on doit mettre à jour l'affichage du nombre de collisions
        texteCollision->setHtml(QString(R"(<div style='background-color: "black";'><div style="color:red;"><b>)") +
                                QString("Collision(s) : %1").arg(collision) + QString("</b> </div></div>"));
    }
}

void MyScene::demarrerNormal() {
    //Parametres specifique au mode normal

    //On demande à chaque nouvelle partie l'username car celui-ci pourrait avoir change et on ne veut pas relancer le jeu pour pouvoir changer le username
    username = QInputDialog::getText(nullptr, "Turbo","Username:", QLineEdit::Normal).toStdString();

    //le mode normal correspond à mode = 1
    mode = 1;

    //On a 3 vies en mode normal
    Vie->setPixmap(QPixmap("./../ressources/vies3.png"));
    vies = 3;

    //Au debut, le timer pour le mode normal est de 10 et se reduit au fil du temps
    timerInterval = 10;

    //En attente de l'appui sur la touche "G" pour lancer le jeu
    textePause->setHtml(
            "<div style='background-color: black;'><div style=\"color:red;\"><b><br><br><br>*------------------------*LANCER LE JEU*-----------------------*<br>   Appuyer sur la touche 'G' pour demarrer le jeu   </b> <br><br><br></div></div>");
}

void MyScene::demarrerDifficile() {
    //Parametres specifique au mode difficile

    //On demande à chaque nouvelle partie l'username car celui-ci pourrait avoir change et on ne veut pas relancer le jeu pour pouvoir changer le username
    username = QInputDialog::getText(nullptr, "Turbo","Username:", QLineEdit::Normal).toStdString();

    //le mode difficile correspond à mode = 2
    mode = 2;

    //On a 3 vies en mode difficile
    Vie->setPixmap(QPixmap("./../ressources/vies3.png"));
    vies = 3;

    //Il y a 2 voitures en mode difficile
    //positionAleatoire -> Nombre aleatoire 0,1 ou 2 qui correspond à la voie sur laquelle va apparaitre la deuxieme voiture (elle peut etre par dessus la premiere voiture)
    //Permet d'afficher la deuxieme voiture
    voiture2->setPos(table[positionAleatoire()], 50);
    if(couleurVoiture) {
        voiture2->setPixmap(QPixmap("./../ressources/voiture.png"));
    }else{
        voiture2->setPixmap(QPixmap("./../ressources/voitureJ.png"));
    }

    //Au debut, le timer pour le mode difficile est de 6 et se reduit au fil du temps
    timerInterval = 6;

    //En attente de l'appui sur la touche "G" pour lancer le jeu
    textePause->setHtml(
            "<div style='background-color: black;'><div style=\"color:red;\"><b><br><br><br>*------------------------*LANCER LE JEU*-----------------------*<br>   Appuyer sur la touche 'G' pour demarrer le jeu   </b> <br><br><br></div></div>");

}


void MyScene::demarrerExpert() {
    //Parametres specifique au mode extreme

    //On demande à chaque nouvelle partie l'username car celui-ci pourrait avoir change et on ne veut pas relancer le jeu pour pouvoir changer le username
    username = QInputDialog::getText(nullptr, "Turbo","Username:", QLineEdit::Normal).toStdString();

    //le mode extreme correspond à mode = 3
    mode = 3;

    //On a 1 vie en mode expert
    Vie->setPixmap(QPixmap("./../ressources/vies1.png"));
    vies = 1;

    //Il y a 2 voitures en mode extreme
    //positionAleatoire -> Nombre aleatoire 0,1 ou 2 qui correspond à la voie sur laquelle va apparaitre la deuxieme voiture (elle peut etre par dessus la premiere voiture)
    //Permet d'afficher la deuxieme voiture
    voiture2->setPos(table[positionAleatoire()], 50);
    if(couleurVoiture) {
        voiture2->setPixmap(QPixmap("./../ressources/voiture.png"));
    }else{
        voiture2->setPixmap(QPixmap("./../ressources/voitureJ.png"));
    }

    //Au debut, le timer pour le mode extreme est de 3 et se reduit au fil du temps
    timerInterval = 3;

    //En attente de l'appui sur la touche "G" pour lancer le jeu
    textePause->setHtml(
            "<div style='background-color: black;'><div style=\"color:red;\"><b><br><br><br>*------------------------*LANCER LE JEU*-----------------------*<br>   Appuyer sur la touche 'G' pour demarrer le jeu   </b> <br><br><br></div></div>");

}

void MyScene::demarrerEntrainement() {
    //Parametres specifique au mode entrainement

    //le mode entrainement correspond à mode = 0
    mode = 0;

    //Le timerInterval ne change pas en mode entrainement, il est reglable dans les parametres
    timerInterval = vitesseEntrainement;

    //Le niveau ne change pas en mode entrainement, il est calculé à partir du timerInterval
    niveau = 11-vitesseEntrainement;

    //Il n'y a pas de vie en mode entrainement, c'est un mode infini dans lequel on compte le nombre de collisions
    Vie->setPixmap(QPixmap("./../vide.png"));
    vies=-1;

    //Affiche une deuxieme voiture, en fonction des parametres du jeu
    if(voituresEntrainement==1) {
        //positionAleatoire -> Nombre aleatoire 0,1 ou 2 qui correspond à la voie sur laquelle va apparaitre la deuxieme voiture (elle peut etre par dessus la premiere voiture)
        //Permet d'afficher la deuxieme voiture
        voiture2->setPos(table[positionAleatoire()], 50);
        if(couleurVoiture) {
            voiture2->setPixmap(QPixmap("./../ressources/voiture.png"));
        }else{
            voiture2->setPixmap(QPixmap("./../ressources/voitureJ.png"));
        }
    }

    //Affichage du texte affichant le nombre de collision
    texteCollision->setHtml(
            QString("<div style='background-color: black;'><div style=\"color:red;\"><b> Collision(s) : 0 </b> </div></div>"));

    //En attente de l'appui sur la touche "G" pour lancer le jeu
    textePause->setHtml(
            "<div style='background-color: black;'><div style=\"color:red;\"><b><br><br><br>*------------------------*LANCER LE JEU*-----------------------*<br>   Appuyer sur la touche 'G' pour demarrer le jeu   </b> <br><br><br></div></div>");

    //Affichage du niveau (par rapport à la vitesse des voitures, peut être changé manuellement (parametres du mode entrainement)
    texteNiveau->setHtml(
            QString(R"(<div style='background-color: "black";'><div style="color:yellow;"><b>)") +
            QString("Niveau : %1").arg(niveau) + QString("</b> </div></div>"));
}

void MyScene::mort(){       //Lorsque le joueur est mort affichage des meilleurs scores, de son classement et demande pour faire une nouvelle partie

    //Affichage d'une explosion sur le personnage
    Explosion->setPos(table[position] - 20, 430);
    Explosion->setPixmap(QPixmap("./../ressources/explosion.png"));

    //Affichage de 0 vie
    Vie->setPixmap(QPixmap("./../ressources/vide.png"));

    //le timer s'arrete car le jeu est fini
    timer->stop();

    //s'il y avait plusieurs voitures, on cache la deuxieme voiture
    if(mode==2 or mode==3 or (mode==0 and voituresEntrainement==1)){
        voiture2->setPixmap(QPixmap("./../ressources/vide.png"));
    }

    //affichage des 5 meilleurs scores par rapport au niveau fait (normal, difficile, extreme) + mise à jour de notre score dans le fichier
    QMessageBox msgBox;
    switch (mode) {
        case 1:{    //Pour le mode normal : Mise à jour des meilleurs scores + affichage des 5 meilleurs scores
            messageDeMort("./../ressources/MeilleursScoresNormal.txt");
            break;
        }
        case 2:{     //Pour le mode difficile : Mise à jour des meilleurs scores + affichage des 5 meilleurs scores
            messageDeMort("./../ressources/MeilleursScoresDifficile.txt");
            break;
        }
        case 3:{    //Pour le mode extreme : Mise à jour des meilleurs scores + affichage des 5 meilleurs scores
            messageDeMort("./../ressources/MeilleursScoresExpert.txt");
            break;
        }
    }

    //Initialisation d'un QString contenant le message a affiché lors de la mort
    QString qmessageMort = QString::fromStdString(messageMort);
    msgBox.setText(qmessageMort);
    msgBox.exec();

    //demande pour recommencer une partie
    recommencerJeu();
}

int MyScene::updateMeilleursScores(char* nom_fichier) {  //renvoie le rang du nouveau score enregistré

    //Creation d'un nouveau fichier (update.txt) dans lequel sera stocké temporairement les scores
    ofstream myfile;
    myfile.open("./../ressources/update.txt");
    ifstream fichier(nom_fichier);
    string ligne;
    int numberScoresTotal=0;
    getline(fichier,ligne);
    stringstream ss(ligne);
    //numberScoresTotal contient le nombre de scores enregistrés dans le fichier
    ss>>numberScoresTotal;

    //Ouverture du fichier
    ifstream monfichier;
    stringstream s;
    int sco=0;
    string pse;
    monfichier.open(nom_fichier);


    //pour savoir si on a deja place le score ou pas
    bool fait=false;

    //dans le update.txt, on met sur la premiere ligne le nombre de score a enregistré (1 de plus que le fichier d'origine)
    myfile<<numberScoresTotal+1<<'\n';

    //correspond à l'indice du score qui vient d'etre enregistré
    int indiceScore = 1;

    //s'il n'y a pas de scores enregistrés
    if (numberScoresTotal==0){
        if (monfichier.is_open()) {
            myfile << points << ' ' << username << '\n';
        }
    }
    else {
        //recupere les scores et pseudos et les stocke dans le string result
        if (monfichier.is_open()) {
            //pour chaque ligne du fichier
            for (int i = 1; i <= numberScoresTotal; i++) {

                //on recupere la ligne
                getline(monfichier, ligne);

                //on passe la premiere ligne (elle contient le nombre de scores enregistres)
                if (i == 1) {
                    s << monfichier.rdbuf();
                }

                //on recupere le score dans la variable sco et le pseudo dans la variable
                s >> sco >> pse;

                //si on n'a toujours pas inserer le score, alors on incremente l'indice du score de 1
                if (!fait) {
                    indiceScore++;
                }

                //si le score a enregistré est superieur au score recupere de la feuille de scores alors, on insere le score a enregistré et on met la variable fait à True
                if (points > sco and !fait) {
                    fait = true;
                    myfile << points << ' ' << username << '\n';
                }

                //On ajoute le score recuperer
                myfile << sco << ' ' << pse << '\n';
            }
            //si le score a enregisté est le moins bon, on l'ajoute à la fin
            if (!fait) {
                indiceScore++;
                myfile << points << ' ' << username << '\n';
            }
        }
        //on supprime l'ancien fichier
        remove(nom_fichier);

        //on renomme le fichier update en le nom de l'ancien fichier
        rename("./../ressources/update.txt", nom_fichier);

        //on ferme le fichier
        monfichier.close();
    }
    //on return l'indice correspondant à la position du score enregistré
    return indiceScore-1;
}

void MyScene::updateSkin(){ //modifie le skin de l'utilisateur
    if(skin==1) {
        tortue->setPixmap(QPixmap("./../ressources/tortue.png"));
    }
    if(skin==2) {
        tortue->setPixmap(QPixmap("./../ressources/escargot.png"));
    }
    if(skin==3) {
        tortue->setPixmap(QPixmap("./../ressources/humain.png"));
    }
}

int MyScene::getvoituresEntrainement() const{       //renvoie le nombre de voitures pour le mode entrainement
    if(voituresEntrainement){
        return 2;
    }else {
        return 1;
    }
}

void MyScene::editvoituresEntrainement(bool nb) {        //modifie le nombres de voitures pour le mode entrainement
    voituresEntrainement=nb;
    if (mode ==0) {     //modifie si le joueur se trouve en mode entrainement
        if (!voituresEntrainement) {
            //cache la deuxieme voiture
            voiture2->setPixmap(QPixmap("./../ressources/vide.png"));
        } else {
            //fait apparaitre la deuxieme voiture sur une voie aleatoire
            voiture2->setPos(table[positionAleatoire()], 50);
            if(couleurVoiture) {
                voiture2->setPixmap(QPixmap("./../ressources/voiture.png"));
            }else{
                voiture2->setPixmap(QPixmap("./../ressources/voitureJ.png"));
            }
        }
    }
}

void MyScene::editvitesseEntrainement(int vitesse) {        //modifie la vitesse des voitures pour le mode entrainement
    if(vitesse>0 and vitesse<11){       //verifie les conditions sur la vitesse
        vitesseEntrainement=vitesse;
    }
    if (mode ==0) {     //modifie si le joueur se trouve en mode entrainement
        timerInterval = vitesseEntrainement;
        //Le niveau ne change pas en mode entrainement, il est calculé à partir du timerInterval
        niveau = 11-vitesseEntrainement;
        texteNiveau->setHtml(
                QString(R"(<div style='background-color: "black";'><div style="color:yellow;"><b>)") +
                QString("Niveau : %1").arg(niveau) + QString("</b> </div></div>"));
        timer->setInterval(timerInterval);
    }
}

void MyScene::editskin(int num) {   //modifie le skin de l'utilisateur
    if(num>0 and num<4){    //il y a 3 skins differents
        skin=num;   //skin = 1 <=> le skin est une tortue, skin = 2 <=> le skin est un escargot et skin = 3 <=> le skin est un humain
    }
}

int MyScene::getvitesseEntrainement() const {   //renvoie la vitesse des voitures lors du mode entrainement
    return 11-vitesseEntrainement;
}

string MyScene::getskin() const {
    //retourne le nom du skin du joueur
    switch (skin) {
        case 1 :{
            return "tortue";
        }
        case 2 : {
            return "escargot";
        }
        case 3 : {
            return "humain";
        }
    }
    return "";
}


void MyScene::fonctionPause(){
    //met le jeu en pause et affiche à l'ecran que pour reprendre, il faut appuyer sur 'P'
    pause = true;
    textePause->setHtml(
            "<div style='background-color: black;'><div style=\"color:red;\"><b><br><br><br>*------------------------*JEU EN PAUSE*------------------------*<br>Appuyer de nouveau sur la touche 'P' pour reprendre</b> <br><br><br></div></div>");
    timer->stop();
}

bool MyScene::getpause() const {    //renvoie la valeur de la variable pause (permet de savoir si le jeu est en pause)
    return pause;
}

bool MyScene::getdemarrerPartie() const {
    return demarrerPartie;      //renvoie la valeur de la variable demarrerPartie (permet de savoir si la partie est démarré)
}

void MyScene::reglesDuJeu() {
    //affiche dans une nouvelles fenetres, les regles du jeu

    //initialisation du QMessageBox qui contiendra les regles
    QMessageBox msgBox;

    //le nom de la fenetre est Turbo (nom du jeu)
    msgBox.setWindowTitle("Turbo");

    //l'icone est une voiture rouge
    msgBox.setWindowIcon(QIcon("./../ressources/voiture.png"));

    //le texte des regles
    msgBox.setText("*------------------------------------* Règles du jeu *------------------------------------*\nVous incarnez une tortue ninja perdue en pleine autoroute !\nEssayer de survivre en évitant les voitures.\nMais attention, plus vous survivez, plus les voitures iront vite.\nLorsque le niveau augmente, la vitesse augmente.\n\nIl y a trois mode de jeux et un mode d'entrainement :\n* Le mode normal :\n     - 3 vies\n     - 1 voiture à la fois\n* Le mode difficile :\n     - 3 vies\n     - 1 à 2 voitures à la fois\n     - plus rapide\n* Le mode extreme :\n     - 1 vie\n     - 1 à 2 voitures à la fois\n     - encore plus rapide\n* Le mode entrainement :\n     - Donne le nombre de collisions (pas de vie)\n     - vous decidez du nombre de voitures (voir menu Jeu->Entrainement)\n     - vous decidez de la rapidité (voir menu Jeu->Entrainement) \n\nSerez vous capable de battre le meilleur score de chaque mode?");

    msgBox.setModal(true); // on souhaite que la fenetre soit modale i.e qu'on ne puisse plus cliquer ailleurs
    msgBox.exec();  //execute la QMessageBox
}

void MyScene::deplacementDroite(){  //deplace l'utilisateur vers la droite

    //verification pour savoir si on peut se deplacer à droite sans sortir des voies
    if(position<2 and !pause){

        //incremente la position pour deplacer l'utilisateur
        position=position+1;

        //deplace l'utilisateur grâce au tableau des positions
        tortue->setPos(table[position],450);
    }
}

void MyScene::deplacementGauche() {  //deplace l'utilisateur vers la gauche
    //verification pour savoir si on peut se deplacer à gauche sans sortir des voies
    if (position > 0 and !pause) {

        //decremente la position pour deplacer l'utilisateur
        position = position - 1;

        //deplace l'utilisateur grâce au tableau des positions
        tortue->setPos(table[position], 450);
    }
}

void MyScene::arretModeEntrainement(){  //permet d'arreter le mode entrainement
    if(mode==0){    //mode entrainement : mode = 0
        //Redemander s'il veut quitter au cas où ca serait une erreur
        int reponse = QMessageBox::question(nullptr, QString("Turbo"), QString("Voulez vous vraiment arreter la partie ?"), QMessageBox ::Yes | QMessageBox::No);

        if (reponse == QMessageBox::Yes){

            //Arret du timer
            timer->stop();

            //Suppression du texte texteCollision
            texteCollision->setPlainText("");

            //Demande pour recommencer une partie
            reponse = QMessageBox::question(nullptr, QString("Turbo"), QString("Voulez vous recommencer une partie ?"), QMessageBox ::Yes | QMessageBox::No);
            if (reponse == QMessageBox::Yes) {
                //recommencer une partie
                this->newGame();
            }
        }
    }
}

void MyScene::keyPause() {  //permet de gerer la pause suite à l'utilisateur qui a appuyé sur la touche 'P'
    if (demarrerPartie) {
        if (!pause) {
            //mettre le jeu en pause
            fonctionPause();
        } else {
            //reprise du jeu
            pause = false;
            textePause->setHtml("");
            timer->start(timerInterval);
        }
    }
}

void MyScene::demarrerJeu() {  //pour eviter que la partie demarre avant que le joueur soit prêt
    if (!demarrerPartie) {  //si la partie n'est pas demarrée
        //alors on l'a demarre
        demarrerPartie = true;
        timer->start(timerInterval); //lancement du timer
        textePause->setHtml("");
    }
}

void MyScene::incrementeNiveau() {  //augmente la difficulté en augmentant la vitesse dans les modes : normal, difficile et extreme

    //on incremente la variable niveau
    niveau = niveau + 1;

    //on met à jour le texte texteNiveau qui affiche le niveau
    texteNiveau->setHtml(
            QString(R"(<div style='background-color: "black";'><div style="color:yellow;"><b>)") +
            QString("Niveau : %1").arg(niveau) + QString("</b> </div></div>"));

    //reduction du temps de timerInterval (les voitures iront plus vite)
    timerInterval = timerInterval * 0.9;

    //on met à jour le timer avec la nouvelle valeur de timerInterval
    timer->setInterval(timerInterval);
}

void MyScene::avancerVoitures() {
    QPointF pos = voiture->pos();       //recupere la position de la premiere voiture
    QPointF pos2 = voiture2->pos();     //recupere la position de la deuxieme voiture

    //Fais avancer la voiture jusqu'en bas de la fenetre (475)
    voiture->setPos(pos.rx(), pos.ry() + 1);

    //s'il y a deux voitures, la deuxieme voiture doit aussi avancer
    if (mode==2 or mode==3 or (mode==0 and voituresEntrainement==1)) {
        voiture2->setPos(pos2.rx(), pos2.ry() + 1);
    }
}

void MyScene::messageDeMort(char* nom_fichier) {    //Mise à jour du string messageMort à la mort de l'utilisateur et mise à jour de la feuille des scores avec le score fait

    //Mise à jour de la feuille des scores
    int indiceScore;
    indiceScore=updateMeilleursScores(nom_fichier);

    //Mise à jour du message de mort avec les variables username, points et l'indice du score
    messageMort+="\nBravo ";
    messageMort+=username;
    messageMort+=" !";
    messageMort+="\nVous avez ";
    messageMort+=to_string(points);
    messageMort+=" points.\n";
    messageMort+="Vous êtes donc en position ";
    messageMort+=to_string(indiceScore);
    messageMort+=" meilleurs Scores";

    //5 meilleurs scores dans le mode
    messageMort+="\n*----------*Meilleurs Scores*----------*";
    messageMort+="\n    Score:         Pseudo:";
    messageMort+= MeilleursScores(nom_fichier,5);
}

void MyScene::quitterJeu() {        //permet de quitter sans erreur le jeu
    int reponse = QMessageBox::question(nullptr, QString("Turbo"),
                                    QString("Voulez-vous quitter le jeu ?"),
                                    QMessageBox::Yes | QMessageBox::No);
    if (reponse == QMessageBox::Yes) {
        exit(0);
    }
}

void MyScene::recommencerJeu() {    //demande à l'utilisateur s'il veut recommencer une partie
    int reponse = QMessageBox::question(nullptr, QString("Turbo"),
                                        QString("Voulez-vous recommencer une partie?"),
                                        QMessageBox::Yes | QMessageBox::No);
    if (reponse == QMessageBox::Yes) {
        this->newGame();        //demarrage d'une nouvelle partie
    }else{
        quitterJeu();           //demande à l'utilisateur s'il veut quitter l'application
    }
}

void MyScene::initialisationVariables() {

    //On demarre au niveau 1
    niveau = 1;

    //on demarre en position centrale donc en 1 (position = 0, 1 ou 2)
    position = 1;

    //Les points sont à 0 au depart
    points = 0;

    //Il n'y a pas encore eu de collisions
    collision = 0;

    //Le jeu n'est pas en pause
    pause=false;

    //La chaine de caractere contenant le nom de l'utilisateur est vide tant qu'il n'a pas ete entre
    username="";

    //Initialisation du message qui sera affiche lorsque l'utilisateur perdra
    messageMort="Vous êtes mort, faites plus attention la prochaine fois ! ;) ";

    //la partie n'est pas encore demarre
    demarrerPartie=false;
}

int MyScene::positionAleatoire() { //Renvoie un nombre aleatoire 0,1 ou 2 qui correspond à la voie sur laquelle va apparaitre la voiture
    return rand() % 3;
}

void MyScene::questionNiveau() {
    QStringList nivList;
    nivList <<QString::fromUtf8("Normal") <<QString::fromUtf8("Difficile") <<QString::fromUtf8("Extreme")<<QString::fromUtf8("Entrainement");
    QString nivQuestion =QInputDialog::getItem(nullptr, "Turbo", "Quel niveau voulez-vous faire ?", nivList, 0,false);
    if(!nivQuestion.isEmpty()) {
        if(nivQuestion=="Normal") { //lent, 1 voiture, 3 vies
            demarrerNormal();
        }
        if(nivQuestion=="Difficile") {  //plus rapide que normal, 1 à 2 voitures, 3 vies
            demarrerDifficile();
        }
        if(nivQuestion=="Extreme") { //plus rapide que difficile, 1 à 2 voitures, 1 vie
            demarrerExpert();
        }
        if(nivQuestion=="Entrainement") {   //mode infini, pour s'entrainer, o peut changer les parametres du mode entrainement dans le menu
            demarrerEntrainement();
        }
    }
}

void MyScene::additem() {
    //Ajoute tous les items et textes sur la fenetre parent
    this->addItem(jeu);
    this->addItem(score);
    this->addItem(voiture);
    this->addItem(voiture2);
    this->addItem(tortue);
    this->addItem(etoile);
    this->addItem(Explosion);
    this->addItem(Vie);
    this->addItem(texte);
    this->addItem(texteNiveau);
    this->addItem(textePause);
    this->addItem(texteCollision);
}

void MyScene::stopGame() {  //arrete la partie en cours
    if(demarrerPartie) {
        if (mode == 0) {    //arrete le mode entrainement
            arretModeEntrainement();
        } else {
            fonctionPause();
            //Redemande s'il veut quitter au cas où ca serait une erreur
            int reponse = QMessageBox::question(nullptr, QString("Turbo"), QString("Voulez vous vraiment arreter la partie ?"), QMessageBox ::Yes | QMessageBox::No);
            if (reponse == QMessageBox::Yes) {
                //arrete la partie (mode normal, difficile ou extreme)
                mort();
            }
        }
    }
}

string MyScene::getCouleur() const {    //retourne la couleur des voitures
    if(couleurVoiture){
        return "rouge";
    }else{
        return "jaune";
    }
}

void MyScene::editCouleur(bool couleur) {   //modifie la couleur des voitures
    couleurVoiture=couleur;   //couleur = 1 <=> les voitures sont rouges, couleur = 2 <=> les voitures sont jaunes
}

void MyScene::updateCouleur() {
    if(couleurVoiture) {
        voiture->setPixmap(QPixmap("./../ressources/voiture.png"));
        if(mode==2 or mode==3 or (mode==0 and voituresEntrainement==1)){
            voiture2->setPixmap(QPixmap("./../ressources/voiture.png"));
        }
    }
    else{
        voiture->setPixmap(QPixmap("./../ressources/voitureJ.png"));
        if(mode==2 or mode==3 or (mode==0 and voituresEntrainement==1)){
            voiture2->setPixmap(QPixmap("./../ressources/voitureJ.png"));
        }
    }
}


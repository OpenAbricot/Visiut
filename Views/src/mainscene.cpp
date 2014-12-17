#include "mainscene.h"
#include "ui_visiut3.h"
#include <QtGui>

MainScene::MainScene(QObject *parent)
{
    /*
        On va gérer la couleur etc... apres via des
        méthode de sélection de couleur, que mainwondow va appelé
    */
    isPressed =false;
    this->graphicsView = new QGraphicsView;
    this->image = NULL;
 
    this->graphicsView->setScene(this);
}


/*SETTEUR*/

void MainScene::setTexte(const QString texte)
{
    this->texte = texte;
}

void MainScene::setIsAffiche(const bool isaffiche)
{
    this->isAffiche = isaffiche;
}

void MainScene::setColor(const QColor color)
{
    this->couleur = color;
}

void MainScene::setTaille(const int taille)
{
    this->taille = taille;
}

void MainScene::setPolice(const QFont police)
{
    this->policeTexte = police;
}

void MainScene::setSelection(const QString selection)
{
    this->selection = selection;
}

void MainScene::setCheminFormePerso(const QString chemin)
{
    this->cheminFormePerso = chemin;
}

void MainScene::setImage(QImage * image)
{
    this->image = image;
	this->graphicsView->setFixedSize(this->image->width(),this->image->height());
}


/* GETTEUR */

QString MainScene::getTexte()const
{
    return texte;
}

bool MainScene::getIsAffiche()const
{
    return this->isAffiche;
}

QColor MainScene::getColor()const
{
    return this->couleur;
}

int MainScene::getTaille()const
{
    return taille;
}

QFont MainScene::getPolice()const
{
    return policeTexte;
}

QString MainScene::getSelection()const
{
    return selection;
}

QString MainScene::getCheminFormePerso()const
{
    return cheminFormePerso;
}

QImage* MainScene::getImage()const
{
    return this->image;
}

QGraphicsView* MainScene::getGraphicsView()const
{
    return this->graphicsView;
}


MainScene::~MainScene()
{
}


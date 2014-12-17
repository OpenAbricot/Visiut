#ifndef MAINSCENE_H
#define MAINSCENE_H

#include <QObject>
#include <QtGui>

class MainScene : public QGraphicsScene

{
Q_OBJECT

private :
    bool isPressed;
    int epaisseur;
    int taille;
    QString selection;
    QString cheminFormePerso;
    QString texte;
    QColor couleur;
    QFont policeTexte;
    QGraphicsView * graphicsView;
    QImage * image;
    bool isAffiche;

public:
    MainScene(QObject *parent = 0);
    ~MainScene();
    void setColor(const QColor);
    void setTaille(const int);
    void setSelection(const QString);
    void setTexte(const QString);
    void setIsAffiche(const bool);
    void setPolice(const QFont);
    void setCheminFormePerso(const QString);
    void setImage(QImage * image);

    QString getTexte()const;
    bool getIsAffiche()const;
    QColor getColor()const;
    int getTaille()const;
    QFont getPolice()const;
    QString getSelection()const;
    QString getCheminFormePerso()const;
    QImage* getImage()const;
    QGraphicsView* getGraphicsView()const;

};

#endif // MAINSCENE_H

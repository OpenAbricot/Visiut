#include "visiut3.h"
#include "Controllers/headers/Controller.h"
#include "Views/headers/New.h"
#include <QMouseEvent>
#include <QtGui>

Visiut3::Visiut3(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);
	m_controller = new Controller();
	//Resize de la fenetre
    this->resize(QApplication::desktop()->width(),QApplication::desktop()->height());
	//Affichage d'une fenetre vierge de 800*600
    this->DisplayVierge(800,600);
	//Message de bienvenue
    ui.statusBar->showMessage("Bienvenue sur VisIUT 3");
}

Visiut3::~Visiut3()
{
	if(m_controller != NULL){
		m_controller->GetBackNext().RemoveTemporyFile();
		delete m_controller;
	}
	if(m_scene != NULL)
		delete m_scene;
}

QImage * Visiut3::GetImage()const{
	return m_controller->GetQImage();
}


void Visiut3::DisplayViaImage(QImage * _picture){
	this->m_scene = new MainScene();
    QLabel * lab = new QLabel;
    QPixmap * pix = new QPixmap(QPixmap::fromImage(*_picture));

    lab->setPixmap(*pix);
    this->m_scene->setImage(m_controller->GetQImage());
    this->m_scene->addPixmap(*pix);

    ui.graphicsView->setScene(this->m_scene);
    ui.graphicsView->setFixedSize(m_controller->GetQImage()->width(),m_controller->GetQImage()->height());
    ui.graphicsView->setMouseTracking(true);
    ui.graphicsView->viewport()->setMouseTracking(true);
	ui.graphicsView->show();
}

/*
Affichage à l'écran de l'image à partir du chemin absolue
Choix du graphicsView pour sa simplicité (DockWidget utilisé auparavant)
*/
void Visiut3::DisplayViaChemin(const QString & chemin)
{
	if(m_controller != NULL)
		delete m_controller;
    m_controller = new Controller(chemin);
    
    QLabel * lab = new QLabel;
    QPixmap * pix = new QPixmap(chemin);
    lab->setPixmap(*pix);

    this->m_scene = new MainScene();
    this->m_scene->setImage(m_controller->GetQImage());
    this->m_scene->addPixmap(*pix);

    ui.graphicsView->setScene(this->m_scene);
    ui.graphicsView->setFixedSize(m_controller->GetQImage()->width(), m_controller->GetQImage()->height());

    ui.graphicsView->setMouseTracking(true);
    ui.graphicsView->viewport()->setMouseTracking(true);

    ui.graphicsView->show();
}

/*
Transformation d'un dessin en image dans le but de pouvoir être enregistrer
en tant qu'image
*/
QImage* Visiut3::viewToImage()
{
    // Initilialisation de l'image
    //QImage * img = new QImage(ui.graphicsView->width(), ui.graphicsView->height(), QImage::Format_RGB32);

    //Dessine le graphicsview dans le QImage
    QPainter painter;

    // On va dessiner dans l'image...
    painter.begin(m_controller->GetQImage());

    // On demande au graphics view de se dessiner dans l'image
    ui.graphicsView->render(&painter);

    painter.end();

    return m_controller->GetQImage();
}

void Visiut3::DisplayVierge(int width ,int height)
{
    //Instanciation de l'image et fond blanc
    m_controller->SetQImage(new QImage(width,height,QImage::Format_RGB32));
    this->miseAZero();

    //Image et Label
    QLabel * lab = new QLabel;
    QPixmap * pix = new QPixmap(QPixmap::fromImage(*(m_controller->GetQImage())));
    lab->setPixmap(*pix);

    //Instanciation du label
    this->m_scene = new MainScene(this);

    this->m_scene->addPixmap(*pix);
    this->m_scene->setSelection("NOTHING");
    this->m_scene->setIsAffiche(false);
    this->m_scene->setImage(m_controller->GetQImage());

    ui.graphicsView->setScene(this->m_scene);
    ui.graphicsView->setFixedSize(width,height);
    ui.graphicsView->setMouseTracking(true);
    ui.graphicsView->viewport()->setMouseTracking(true);
	ui.graphicsView->show();

}

void Visiut3::miseAZero()
{
    for (int i = 0; i< m_controller->GetQImage()->width() ; i++)
    {
        for (int j = 0 ; j < m_controller->GetQImage()->height() ; j++)
        {
            m_controller->GetQImage()->setPixel(i,j,qRgb(255,255,255));
        }
    }
}

void Visiut3::on_ActionOpen_triggered()
{
	QString chemin = QString();
    if(this->m_scene->getIsAffiche() == false)
    {
        chemin = QFileDialog::getOpenFileName(this, "Ouvrir un fichier", QString(), "Images (*.png *.gif *.jpg *.jpeg)");
        if(chemin != "")
        {
            ui.statusBar->showMessage("Image charge depuis "+chemin);
            this->DisplayViaChemin(chemin);
			if(m_controller != NULL)
				delete m_controller;
			m_controller = new Controller(chemin);
        }
    }
    else
    {
        int res = QMessageBox::question(this,"Attention","Remplacer le fichier en cours ?",QMessageBox::Yes,QMessageBox::Cancel);
        if(res != QMessageBox::Cancel)
        {
            chemin = QFileDialog::getOpenFileName(this, "Ouvrir un fichier", QString(), "Images (*.png *.gif *.jpg *.jpeg *.JPG *.JPEG *.bmp)");
            ui.statusBar->showMessage("Image charge depuis "+chemin);
            this->DisplayViaChemin(chemin);
            this->m_scene->setIsAffiche(true);
        }
    }
}

void Visiut3::on_ActionProperties_triggered(){
	 if(!m_controller->GetQImage()->isNull())
    {
        //Nombre de pixel
        int nbpix = m_controller->GetQImage()->width() * m_controller->GetQImage()->height();
        //Affichage des informations
        QMessageBox::information(this,
                                 "Proprietes",
                                 "Nom du fichier : "+m_controller->GetFileInfo()->fileName()+"\n"+
                                 /*"Chemin absolu : "+chemin+"\n"+*/
                                 "Taille : "+QString::number(m_controller->GetQImage()->width(),10)+"px par "+QString::number(m_controller->GetQImage()->height(),10)+"px\n"+
                                 "Profondeur : "+QString::number(m_controller->GetQImage()->depth(),10)+" bits\n"+
                                 "Nombre de pixels : "+QString::number(nbpix)+" pixels\n"+
                                 "Poids theorique : "+QString::number(nbpix/1024)+" Ko\n"+
                                 "Poids reels : "+QString::number(m_controller->GetFileInfo()->size()/1024)+" Ko\n"+
                                 "Date de derniere modification : "+m_controller->GetFileInfo()->lastModified().toString()+
                                 ""
                                 );
    }
    else
    {
        QMessageBox::critical(this, "", "Image non chargée");
    }
}

void Visiut3::on_ActionNegative_triggered()
{
    if(!m_controller->GetQImage()->isNull())
    {
		m_controller->Treatment(0);
        DisplayViaImage(m_controller->GetQImage());
    }
    else
    {
       QMessageBox::critical(this, "Attention", "Image non chargee");
    }
}

/*
Merci à toute l'équipe de VisIUT
*/
void Visiut3::on_ActionAbout_triggered()
{
    QMessageBox::information(this, "A Propos", "VisIut 3\n\nInspiré de VisIut v2\nPar Yohan Sanchez, Benjamin Gounine, Nicolas Renard, Raphael Tissier, Florian Faglin, Asselineau William\n\nPour le Projet du S3D IUT Reims \n\nProjet repris par Benjamin Gounine");
}

void Visiut3::on_ActionMirror_triggered()
{
    //Si l'image n'est pas null
    if(!m_controller->GetQImage()->isNull())
    {
		//Exécution de la fonction qui inverse ...
        m_controller->Treatment(1);

        //On affiche l'image.
        this->DisplayViaImage(m_controller->GetQImage());
    }
}


/*
Création d'une feuille vierge. Crée une nouvelle fenetre afin de sélection la taille de la fenetre
et l'arriere plan.
*/
void Visiut3::on_ActionNew_triggered()
{
    if(this->m_scene->getIsAffiche() == false)
    {
        New * neW  = new New();
        int i = neW->exec();
        if (i == QDialog::Accepted)
        {
            this->DisplayVierge(neW->getWidth(), neW->getHeight());
            //m_scene->setIsAffiche(true);
        }
    }
    else
    {
        int res = QMessageBox::question(this,"Attention","Etes vous sure de vouloir fermer l'image courante ?",QMessageBox::Yes,QMessageBox::Cancel);
        if(res != QMessageBox::Cancel)
        {
            New * neW  = new New();
            int i = neW->exec();
            if (i == QDialog::Accepted)
            {
                this->DisplayVierge(neW->getWidth(), neW->getHeight());
            }
        }
    }

    //ui.labImageCourante->setText("Zone de dessin");
}

/*
Enregistrement de l'image courante modifié (ou pas...)
*/
void Visiut3::on_ActionSave_triggered()
{
    //Choix du chemin d'enregistrement
    QString fichier = QFileDialog::getSaveFileName(this, "Enregistrer", QString(), "Tout");
    //m_controller->SetQImage(this->viewToImage());
    m_controller->Save(fichier);
}

/*
    Annulmation de la dernière action effectuer. Attention, il y a quelques bugs
*/
void Visiut3::on_ActionCancel_triggered()
{
	m_controller->Back();
    this->DisplayViaImage(m_controller->GetQImage());
}

/*
Gestion de la fermeture du programme
*/
void Visiut3::CloseEvent(QCloseEvent *event)
{
 int ret = QMessageBox::question(this,"Quitter?","Voulez-vous vraiment quitter?", QMessageBox::Yes | QMessageBox::No);
     if (ret == QMessageBox::Yes)
                event->accept();
           else
                event->ignore();
}

/*
Gestion du menu contextuel lors d'un clique droit avec la souris
*/
void Visiut3::ContextMenuEvent(QContextMenuEvent * event)
{
   QMenu menu;
   menu.addAction(ui.actionPropriete);
   menu.addAction(ui.actionEffacer);
   //this->selectedAction = menu.exec(event->globalPos());
}

/*
Présent des le début. Aucune idée de son utilité...
*/
void Visiut3::ChangeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui.retranslateUi(this);
        break;
    default:
        break;
    }
}

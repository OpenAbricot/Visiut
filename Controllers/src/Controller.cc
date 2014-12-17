#include "Controllers/headers/Controller.h"
#include "Models/headers/Picture.h"
#include "Models/headers/PictureColor.h"
#include "Models/headers/PictureGray.h"
#include <QImage>
#include <QString>
#include <QFileInfo>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

// Constructeur par défaut
Controller::Controller(){
    image = NULL;
	m_image_info = new QFileInfo();
    m_backNext = BackNext();
}

// Constructeur avec QImage
Controller::Controller(const QString & _path){
    image = new QImage(_path);
	m_image_info = new QFileInfo(_path);
    string name = _path.toStdString();
    name = name.substr(name.rfind("/")+1, name.size()-1);
    m_backNext = BackNext(name.data());
	cerr << "Construction " << this << endl;
}

Controller::Controller(const PictureGray & _picture){
    int nbLines = _picture.GetNbLines();
    int nbColumns = _picture.GetNbColumns();

    ostringstream oss(ostringstream::out);
    oss << "P5\n" << nbColumns << ' ' << nbLines << "\n255\n";
    
    // Saisie des pixels sur la QImage a partir du tableau 2D de Image
    for(int i=0 ; i < nbLines ; i++)
        for(int j=0 ; j < nbColumns ; j++)
            oss<<255;

    //int taille =largeur*sizeof(unsigned char);
    // Constructeur du QImage
    // image = new QImage((const uchar *)oss.str().c_str(), largeur, hauteur, taille, QImage::Format_Indexed8);

    image = new QImage (QImage::fromData((const uchar *)(oss.str().c_str()), oss.str().length()));
	cerr << "Construction " << this << endl;
}

Controller::Controller(const PictureColor & _picture){
    unsigned int nbLines = _picture.GetNbLines();
    unsigned int nbColumns = _picture.GetNbColumns();
    //QImage::Format format = (QImage::Format) I.getFormat();
    // Construction d'une QImage
    image = new QImage(nbColumns, nbLines,QImage::Format_RGB32);
    // Saisie des pixels sur la QImage a partir du tableau 2D de Image
    for(unsigned int i=0 ; i<nbLines ; i++)
        for(unsigned int j=0 ; j<nbColumns ; j++)
        {
            int red = qRed(_picture.getPixel(i,j));
            int green = qGreen(_picture.getPixel(i,j));
            int blue = qBlue(_picture.getPixel(i,j));
            image->setPixel(j, i, qRgb(red, green, blue));
        }
	cerr << "Construction " << this << endl;
}

// Constructeur par copie
Controller::Controller(const Controller & _controller){
    cerr << "Construction " << this << endl;
    image = new QImage(_controller.GetPicture());
}
 //Destructeur
Controller::~Controller(){
    if(image != NULL)
        delete image;
	if(m_image_info != NULL)
		delete m_image_info;
}

// Getteurs
QImage * Controller::GetQImage()const{
    return image;
}

QImage & Controller::GetPicture()const{
    return (*image);
}

unsigned int Controller::GetNbLines()const{
    return image->height();    
}

unsigned int Controller::GetNbColumns()const{
    return image->width();
}

int Controller::GetDeph()const{
    return image->depth();
}

unsigned int Controller::GetFormat()const{
    return image->format();
}

QFileInfo * Controller::GetFileInfo()const{
	return m_image_info;
}

BackNext Controller::GetBackNext()const{
	return m_backNext;
}

bool Controller::GetColor()const{
    //retourne vrai(1) si image couleur
    return !image->isGrayscale();
}

// retourne le pixel correspondant a la largeur et a la hauteur indique
int Controller::GetPixel(unsigned int width, unsigned int height)const{
    return image->pixel(height,width);
}

//Retourne un tableau 2D de type inconnu contenant les pixels de l'image (Et sinon Dieu a créer le polymorphisme je sais...)
void ** Controller::GetData()const{
    if(GetColor()){
        unsigned int ** tab = new unsigned int *[image->height()];

        for(unsigned int i=0 ; i < (unsigned int)image->height() ; i++)
            tab[i] = new unsigned int [image->width()];

        for(unsigned int i=0 ; i < (unsigned int)image->height() ; i++){
            for(unsigned int j=0; j < (unsigned int)image->width(); j++)
                tab[i][j] = GetPixel(i,j);
        }

        return ((void **)tab);
    }

    unsigned char ** tab = new unsigned char *[image->height()];

    for(unsigned int i=0 ; i < (unsigned int)image->height() ; i++){
        tab[i] = new unsigned char [image->width()];
    }

    for(unsigned int i=0 ; i < (unsigned int)image->height() ; i++){
        for(unsigned int j=0; j < (unsigned int)image->width(); j++)
            tab[i][j] = GetPixel(i,j);
    }

    return ((void **)tab);
}

void Controller::SetPicture(const PictureColor & _picture){
    unsigned int nbLines = _picture.GetNbLines();
    unsigned int nbColumns = _picture.GetNbColumns();
    if(image != NULL)
        delete image;
    image = new QImage(nbColumns, nbLines,QImage::Format_RGB32);
    // Saisie des pixels sur la QImage a partir du tableau 2D de Image
    for(unsigned int i=0 ; i<nbLines ; i++)
        for(unsigned int j=0 ; j<nbColumns ; j++)
        {
            int red = qRed(_picture.getPixel(i,j));
            int green = qGreen(_picture.getPixel(i,j));
            int blue = qBlue(_picture.getPixel(i,j));
            image->setPixel(j, i, qRgb(red, green, blue));
        }
}

void Controller::SetPicture(const PictureGray & _picture){
    int nbLines = _picture.GetNbLines();
    int nbColumns = _picture.GetNbColumns();

    ostringstream oss(ostringstream::out);
    oss << "P5\n" << nbColumns << ' ' << nbLines << "\n255\n";

    // Saisie des pixels sur la QImage a partir du tableau 2D de Image
    for(int i=0 ; i < nbLines ; i++)
        for(int j=0 ; j < nbColumns ; j++)
            oss<<255;

    //int taille =largeur*sizeof(unsigned char);
    // Constructeur du QImage
    // image = new QImage((const uchar *)oss.str().c_str(), largeur, hauteur, taille, QImage::Format_Indexed8);

    image = new QImage (QImage::fromData((const uchar *)(oss.str().c_str()), oss.str().length()));
}

void Controller::SetFileInfo(QFileInfo * _fileInfo){
	if(m_image_info != NULL)
		delete m_image_info;
	m_image_info = _fileInfo;
}

void Controller::SetQImage(QImage * _image){
	if(image != NULL)
		delete image;
	image = _image;
}

// Operateur =
Controller & Controller::operator = (const Controller & C){
   	if(image != NULL)
		delete image;
    Controller *Co = new Controller(C);
    return (*Co);
    
}

bool Controller::Save(const QString & _path){
	int quality = -1;
	//const char* format = "JPG";
        return image->save(_path, 0, quality);
}

void Controller::Treatment(int _treatment){
    if(GetColor()){
        PictureColor picture(((unsigned int **)GetData()), "", GetNbLines(), GetNbColumns(), GetDeph(), GetFormat(), GetColor());
        if(_treatment == 0)
            picture.Negative();
        else if(_treatment == 1)
            picture.HorizontalMirror();
        else
            picture.VerticalMirror();


        SetPicture(picture);
    }
    else{
        PictureGray picture(((unsigned char **)GetData()), "", GetNbLines(), GetNbColumns(), GetDeph(), GetFormat(), GetColor());
        if(_treatment == 0)
            picture.Negative();
        else if(_treatment == 1)
            picture.HorizontalMirror();
        else
            picture.VerticalMirror();

        SetPicture(picture);
    }
    m_backNext.AddState();
    Save(QString(m_backNext.GetCurrentStatePathName().data()));
}

void Controller::Back(){
    if(m_backNext.GetIndexCurrentStatePathName() > 0){
        delete image;
        m_backNext.RemoveLastState();
        image = new QImage(m_backNext.GetCurrentStatePathName().data());
    }
}

void Controller::Next(){
	if(m_backNext.GetIndexCurrentStatePathName() > 0){
        delete image;
		m_backNext.AddState(m_backNext.GetIndexCurrentStatePathName()+1);
        image = new QImage(m_backNext.GetCurrentStatePathName().data());
    }
}


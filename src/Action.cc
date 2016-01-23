#include "Action.h"
#include "Picture.h"
#include "PictureColor.h"
#include "PictureGray.h"
#include <QImage>
#include <QString>
#include <QFileInfo>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

// Constructeur par défaut
Action::Action(){
    image = NULL;
	image_info = new QFileInfo();
    backNext = BackNext();
}

// Constructeur avec QImage
Action::Action(const QString & _path){
    image = new QImage(_path);
	image_info = new QFileInfo(_path);
    string name = _path.toStdString();
    name = name.substr(name.rfind("/")+1, name.size()-1);
    backNext = BackNext(name.data());
	cerr << "Construction " << this << endl;
}

Action::Action(const PictureGray & _picture){
    int nbLines = _picture.getNbLines();
    int nbColumns = _picture.getNbColumns();

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

Action::Action(const PictureColor & _picture){
    unsigned int nbLines = _picture.getNbLines();
    unsigned int nbColumns = _picture.getNbColumns();
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
Action::Action(const Action & _Action){
    cerr << "Construction " << this << endl;
    image = new QImage(_Action.getPicture());
}
 //Destructeur
Action::~Action(){
    if(image != NULL)
        delete image;
	if(image_info != NULL)
		delete image_info;

    cerr << "Destruction" << this << endl;
}

// getteurs
QImage * Action::getQImage()const{
    return image;
}

QImage & Action::getPicture()const{
    return (*image);
}

unsigned int Action::getNbLines()const{
    return image->height();
}

unsigned int Action::getNbColumns()const{
    return image->width();
}

int Action::getDeph()const{
    return image->depth();
}

unsigned int Action::getFormat()const{
    return image->format();
}

QFileInfo * Action::getFileInfo()const{
	return image_info;
}

BackNext Action::getBackNext()const{
	return backNext;
}

bool Action::getColor()const{
    //retourne vrai(1) si image couleur
    return !image->isGrayscale();
}

// retourne le pixel correspondant a la largeur et a la hauteur indique
int Action::getPixel(unsigned int width, unsigned int height)const{
    return image->pixel(height,width);
}

//Retourne un tableau 2D de type inconnu contenant les pixels de l'image (Et sinon Dieu a créer le polymorphisme je sais...)
void ** Action::getData()const{
    if(getColor()){
        unsigned int ** tab = new unsigned int *[image->height()];

        for(unsigned int i=0 ; i < (unsigned int)image->height() ; i++)
            tab[i] = new unsigned int [image->width()];

        for(unsigned int i=0 ; i < (unsigned int)image->height() ; i++){
            for(unsigned int j=0; j < (unsigned int)image->width(); j++)
                tab[i][j] = getPixel(i,j);
        }

        return ((void **)tab);
    }

    unsigned char ** tab = new unsigned char *[image->height()];

    for(unsigned int i=0 ; i < (unsigned int)image->height() ; i++){
        tab[i] = new unsigned char [image->width()];
    }

    for(unsigned int i=0 ; i < (unsigned int)image->height() ; i++){
        for(unsigned int j=0; j < (unsigned int)image->width(); j++)
            tab[i][j] = getPixel(i,j);
    }

    return ((void **)tab);
}

void Action::setPicture(const PictureColor & _picture){
    unsigned int nbLines = _picture.getNbLines();
    unsigned int nbColumns = _picture.getNbColumns();
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

void Action::setPicture(const PictureGray & _picture){
    int nbLines = _picture.getNbLines();
    int nbColumns = _picture.getNbColumns();

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

void Action::setFileInfo(QFileInfo * _fileInfo){
	if(image_info != NULL)
		delete image_info;
	image_info = _fileInfo;
}

void Action::setQImage(QImage * _image){
	if(image != NULL)
		delete image;
	image = _image;
}

// Operateur =
Action & Action::operator = (const Action & C){
   	if(image != NULL)
		delete image;
    Action *Co = new Action(C);
    return (*Co);

}

bool Action::save(const QString & _path){
	int quality = -1;
	//const char* format = "JPG";
    return image->save(_path, 0, quality);
}

void Action::treatment(int _treatment){
    if(getColor()){
        PictureColor picture(((unsigned int **)getData()), "", getNbLines(), getNbColumns(), getDeph(), getFormat(), getColor());
        if(_treatment == 0)
            picture.negative();
        else if(_treatment == 1)
            picture.horizontalMirror();
        else
            picture.verticalMirror();


        setPicture(picture);
    }
    else{
        PictureGray picture(((unsigned char **)getData()), "", getNbLines(), getNbColumns(), getDeph(), getFormat(), getColor());
        if(_treatment == 0)
            picture.negative();
        else if(_treatment == 1)
            picture.horizontalMirror();
        else
            picture.verticalMirror();

        setPicture(picture);
    }
    backNext.addState();
    save(QString(backNext.getCurrentStatePathName().data()));
}

void Action::back(){
    if(backNext.getIndexCurrentStatePathName() > 0){
        delete image;
        backNext.removeLastState();
        image = new QImage(backNext.getCurrentStatePathName().data());
    }
}

void Action::next(){
	if(backNext.getIndexCurrentStatePathName() > 0){
        delete image;
		backNext.addState(backNext.getIndexCurrentStatePathName()+1);
        image = new QImage(backNext.getCurrentStatePathName().data());
    }
}

#include <iostream>
#include "PictureGray.h"
#include "Traitement.h"
using namespace std;

PictureGray::PictureGray() : Picture(){
    picture = NULL;

    cerr << "Construction" << this << endl;
}

PictureGray::PictureGray(unsigned char **_picture, const std::string &_name, unsigned int _nbLines, unsigned int _nbColumns, int _deph, int _format, bool _color) : Picture(_name, _nbLines, _nbColumns, _deph, _format, _color){
    picture = _picture;

    cerr << "Construction" << this << endl;
}

PictureGray::PictureGray(const PictureGray &_picture) : Picture(){
    name =_picture.name;
    nbLines =_picture.nbLines;
    nbColumns = _picture.nbColumns;
    deph = _picture.deph;
    format = _picture.format;
    color = _picture.color;

    picture = new unsigned char *[nbLines];

    for(unsigned int i=0 ; i<nbLines ; i++)
        picture[i] = new unsigned char[nbColumns];

    for(unsigned int i=0 ; i<nbLines ; i++)
        for(unsigned int j=0 ; j<nbColumns ; j++)
            picture[i][j] = _picture.picture[i][j];

    cerr << "Construction" << this << endl;
}

PictureGray::~PictureGray(){

    if(picture != NULL){
        for(unsigned int i=0 ; i<nbLines ; i++)
                delete picture[i];

        delete picture;
    }

    cerr << "Destruction" << this << endl;
}

PictureGray PictureGray::operator =(const PictureGray & _picture){
    if(name != _picture.name)
        name = _picture.name;
    if(nbLines != _picture.nbLines)
        nbLines = _picture.nbLines;
    if(nbColumns != _picture.nbColumns)
        nbColumns = _picture.nbColumns;
    if(deph != _picture.deph)
        deph = _picture.deph;
    if(format != _picture.format)
        format = _picture.format;
    if(color != _picture.color)
        color = _picture.color;

    if(_picture.picture != NULL){
        for(unsigned int i=0 ; i<nbLines ; i++)
                delete picture[i];

        delete picture;

        picture = new unsigned char *[nbLines];

        for(unsigned int i=0 ; i<nbLines ; i++)
            picture[i] = new unsigned char [nbColumns];

        for(unsigned int i=0 ; i<nbLines ; i++)
            for(unsigned int j=0 ; j<nbColumns ; j++)
                picture[i][j] = _picture.picture[i][j];
    }
    else
        picture = NULL;

    cerr << "Construction" << this << endl;

    return (*this);

}

unsigned char ** PictureGray::getPictureGray()const{
    unsigned char ** copy = new unsigned char *[nbLines];

    for(unsigned int i=0 ; i<nbLines ; i++)
        copy[i] = new unsigned char [nbColumns];

    for(unsigned int i=0 ; i<nbLines ; i++)
        for(unsigned int j=0 ; j<nbColumns ; j++)
            copy[i][j] = picture[i][j];

    return copy;
}

int PictureGray::getPixel(unsigned int _x,unsigned int _y)const{
        return picture[_x][_y];
}

void PictureGray::setPictureGray(unsigned char ** _picture){
   picture = _picture;
}

void PictureGray::setPixel(unsigned int _x, unsigned int _y, int _value){
    picture[_x][_y] = _value;
}

void PictureGray::negative(){
	unsigned char ** new_picture = Traitement<unsigned char>::negative(picture, nbColumns, nbLines);
    picture = new_picture;
}

void PictureGray::verticalMirror(){
	unsigned char ** new_picture = Traitement<unsigned char>::verticalMirror(picture, nbColumns, nbLines);
    picture = new_picture;
}

void PictureGray::horizontalMirror(){
	unsigned char ** new_picture = Traitement<unsigned char>::horizontalMirror(picture, nbColumns, nbLines);
    picture = new_picture;
}

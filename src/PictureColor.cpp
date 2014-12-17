#include <iostream>
#include "PictureColor.h"
#include "Picture.h"
#include "Traitement.h"
using namespace std;

PictureColor::PictureColor() : Picture(){
    picture = NULL;

    cerr << "Default Constructor " << this << endl;
}

PictureColor::PictureColor(unsigned int **_picture, const std::string & _name, unsigned int _nbLines, unsigned int _nbColumns, int _deph, unsigned int _format, bool _color) : Picture(_name, _nbLines, _nbColumns, _deph, _format, _color){
    cerr << "Argument Constructor " << this << endl;
    picture = _picture;
}

PictureColor::PictureColor(const PictureColor & _picture) : Picture(){
    cerr << "Copy Constructor " << this << endl;
    name =_picture.name;
    nbLines =_picture.nbLines;
    nbColumns = _picture.nbColumns;
    deph = _picture.deph;
    format = _picture.format;
    color = _picture.color;

    picture = new unsigned int *[nbLines];

    for(unsigned int i=0 ; i<nbLines ; i++)
        picture[i] = new unsigned int [nbColumns];

    for(unsigned int i=0 ; i<nbLines ; i++)
        for(unsigned int j=0 ; j<nbColumns ; j++)
            picture[i][j] = _picture.picture[i][j];
}

PictureColor::~PictureColor(){
    cerr << "Destructor " << this << endl;

    if(picture != NULL){
        for(unsigned int i=0 ; i<nbLines ; i++)
                delete picture[i];

        delete picture;
    }


}

PictureColor & PictureColor::operator =(const PictureColor & _picture){
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

        picture = new unsigned int *[nbLines];

        for(unsigned int i=0 ; i<nbLines ; i++)
            picture[i] = new unsigned int [nbColumns];

        for(unsigned int i=0 ; i<nbLines ; i++)
            for(unsigned int j=0 ; j<nbColumns ; j++)
                picture[i][j] = _picture.picture[i][j];
    }
    else
        picture = NULL;

    return (*this);
}

unsigned int ** PictureColor::getPictureColor()const{
    unsigned int ** copy = new unsigned int *[nbLines];

    for(unsigned int i=0 ; i<nbLines ; i++)
        copy[i] = new unsigned int [nbColumns];

    for(unsigned int i=0 ; i<nbLines ; i++)
        for(unsigned int j=0 ; j<nbColumns ; j++)
            copy[i][j] = picture[i][j];

    return copy;
}

unsigned int PictureColor:: getPixel(unsigned int _x,unsigned int _y)const{
        return picture[_x][_y];
}

void PictureColor::setPictureColor(unsigned int **_picture){
   picture = _picture;
}

void PictureColor::setPixel(unsigned int _x, unsigned int _y, int _value){
    picture[_x][_y] = _value;
}

void PictureColor::negative(){
	unsigned int ** new_picture = Traitement<unsigned int>::negative(picture, nbColumns, nbLines);
    picture = new_picture;
}

void PictureColor::verticalMirror(){
	unsigned int ** new_picture = Traitement<unsigned int>::verticalMirror(picture, nbColumns, nbLines);
    picture = new_picture;
}

void PictureColor::horizontalMirror(){
    unsigned int ** new_picture = Traitement<unsigned int>::horizontalMirror(picture, nbColumns, nbLines);
	picture = new_picture;
}

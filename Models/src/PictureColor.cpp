#include <iostream>
#include "Models/headers/PictureColor.h"
#include "Models/headers/Picture.h"
#include "Models/headers/Traitement.h"
using namespace std;

PictureColor::PictureColor() : Picture(){
    m_picture = NULL;

    cerr << "Default Constructor " << this << endl;
}

PictureColor::PictureColor(unsigned int **_picture, const std::string & _name, unsigned int _nbLines, unsigned int _nbColumns, int _deph, unsigned int _format, bool _color) : Picture(_name, _nbLines, _nbColumns, _deph, _format, _color){
    cerr << "Argument Constructor " << this << endl;
    m_picture = _picture;
}

PictureColor::PictureColor(const PictureColor & _picture) : Picture(){
    cerr << "Copy Constructor " << this << endl;
    m_name =_picture.m_name;
    m_nbLines =_picture.m_nbLines;
    m_nbColumns = _picture.m_nbColumns;
    m_deph = _picture.m_deph;
    m_format = _picture.m_format;
    m_color = _picture.m_color;

    m_picture = new unsigned int *[m_nbLines];

    for(unsigned int i=0 ; i<m_nbLines ; i++)
        m_picture[i] = new unsigned int [m_nbColumns];

    for(unsigned int i=0 ; i<m_nbLines ; i++)
        for(unsigned int j=0 ; j<m_nbColumns ; j++)
            m_picture[i][j] = _picture.m_picture[i][j];



}

PictureColor::~PictureColor(){
    cerr << "Destructor " << this << endl;

    if(m_picture != NULL){
        for(unsigned int i=0 ; i<m_nbLines ; i++)
                delete m_picture[i];

        delete m_picture;
    }


}

PictureColor & PictureColor::operator =(const PictureColor & _picture){
    if(m_name != _picture.m_name)
        m_name = _picture.m_name;
    if(m_nbLines != _picture.m_nbLines)
        m_nbLines = _picture.m_nbLines;
    if(m_nbColumns != _picture.m_nbColumns)
        m_nbColumns = _picture.m_nbColumns;
    if(m_deph != _picture.m_deph)
        m_deph = _picture.m_deph;
    if(m_format != _picture.m_format)
        m_format = _picture.m_format;
    if(m_color != _picture.m_color)
        m_color = _picture.m_color;

    if(_picture.m_picture != NULL){
        for(unsigned int i=0 ; i<m_nbLines ; i++)
                delete m_picture[i];

        delete m_picture;

        m_picture = new unsigned int *[m_nbLines];

        for(unsigned int i=0 ; i<m_nbLines ; i++)
            m_picture[i] = new unsigned int [m_nbColumns];

        for(unsigned int i=0 ; i<m_nbLines ; i++)
            for(unsigned int j=0 ; j<m_nbColumns ; j++)
                m_picture[i][j] = _picture.m_picture[i][j];
    }
    else
        m_picture = NULL;

    return (*this);

}

unsigned int ** PictureColor::GetPictureColor()const{
    unsigned int ** copy = new unsigned int *[m_nbLines];

    for(unsigned int i=0 ; i<m_nbLines ; i++)
        copy[i] = new unsigned int [m_nbColumns];

    for(unsigned int i=0 ; i<m_nbLines ; i++)
        for(unsigned int j=0 ; j<m_nbColumns ; j++)
            copy[i][j] = m_picture[i][j];

    return copy;
}

unsigned int PictureColor:: getPixel(unsigned int _x,unsigned int _y)const{
        return m_picture[_x][_y];
}

void PictureColor::SetPictureColor(unsigned int **_picture){
   m_picture = _picture;
}

void PictureColor::SetPixel(unsigned int _x, unsigned int _y, int _value){
    m_picture[_x][_y] = _value;
}

void PictureColor::Negative(){
	unsigned int ** new_picture = Traitement<unsigned int>::Negative(m_picture, m_nbColumns, m_nbLines);
	FreePicture((void **)m_picture);
    m_picture = new_picture;
}

void PictureColor::VerticalMirror(){
	unsigned int ** new_picture = Traitement<unsigned int>::VerticalMirror(m_picture, m_nbColumns, m_nbLines);
	FreePicture((void**)m_picture);
    m_picture = new_picture;
}

void PictureColor::HorizontalMirror(){
    unsigned int ** new_picture = Traitement<unsigned int>::HorizontalMirror(m_picture, m_nbColumns, m_nbLines);
	FreePicture((void**)m_picture);
	m_picture = new_picture;
}


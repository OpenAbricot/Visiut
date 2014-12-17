#include <iostream>
#include "Models/headers/PictureGray.h"
#include "Models/headers/Traitement.h"
using namespace std;

PictureGray::PictureGray() : Picture(){
    m_picture = NULL;
}

PictureGray::PictureGray(unsigned char **_picture, const std::string &_name, unsigned int _nbLines, unsigned int _nbColumns, int _deph, int _format, bool _color) : Picture(_name, _nbLines, _nbColumns, _deph, _format, _color){
            m_picture = _picture;
}

PictureGray::PictureGray(const PictureGray &_picture) : Picture(){
    m_name =_picture.m_name;
    m_nbLines =_picture.m_nbLines;
    m_nbColumns = _picture.m_nbColumns;
    m_deph = _picture.m_deph;
    m_format = _picture.m_format;
    m_color = _picture.m_color;

    m_picture = new unsigned char *[m_nbLines];

    for(unsigned int i=0 ; i<m_nbLines ; i++)
        m_picture[i] = new unsigned char [m_nbColumns];

    for(unsigned int i=0 ; i<m_nbLines ; i++)
        for(unsigned int j=0 ; j<m_nbColumns ; j++)
            m_picture[i][j] = _picture.m_picture[i][j];
}

PictureGray::~PictureGray(){

    if(m_picture != NULL){
        for(unsigned int i=0 ; i<m_nbLines ; i++)
                delete m_picture[i];

        delete m_picture;
    }
}

PictureGray PictureGray::operator =(const PictureGray & _picture){
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

        m_picture = new unsigned char *[m_nbLines];

        for(unsigned int i=0 ; i<m_nbLines ; i++)
            m_picture[i] = new unsigned char [m_nbColumns];

        for(unsigned int i=0 ; i<m_nbLines ; i++)
            for(unsigned int j=0 ; j<m_nbColumns ; j++)
                m_picture[i][j] = _picture.m_picture[i][j];
    }
    else
        m_picture = NULL;

    return (*this);

}

unsigned char ** PictureGray::GetPictureGray()const{
    unsigned char ** copy = new unsigned char *[m_nbLines];

    for(unsigned int i=0 ; i<m_nbLines ; i++)
        copy[i] = new unsigned char [m_nbColumns];

    for(unsigned int i=0 ; i<m_nbLines ; i++)
        for(unsigned int j=0 ; j<m_nbColumns ; j++)
            copy[i][j] = m_picture[i][j];

    return copy;
}

int PictureGray:: getPixel(unsigned int _x,unsigned int _y)const{
        return m_picture[_x][_y];
}

void PictureGray::SetPictureGray(unsigned char ** _picture){
   m_picture = _picture;
}

void PictureGray::SetPixel(unsigned int _x, unsigned int _y, int _value){
    m_picture[_x][_y] = _value;
}

void PictureGray::Negative(){
	unsigned char ** new_picture = Traitement<unsigned char>::Negative(m_picture, m_nbColumns, m_nbLines);
	FreePicture((void**)m_picture);
    m_picture = new_picture;
}

void PictureGray::VerticalMirror(){
	unsigned char ** new_picture = Traitement<unsigned char>::VerticalMirror(m_picture, m_nbColumns, m_nbLines);
	FreePicture((void**)m_picture);
    m_picture = new_picture;
}

void PictureGray::HorizontalMirror(){
	unsigned char ** new_picture = Traitement<unsigned char>::HorizontalMirror(m_picture, m_nbColumns, m_nbLines);
	FreePicture((void**)m_picture);
    m_picture = new_picture;
}

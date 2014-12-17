#include "Models/headers/Picture.h"
#include <string>
using namespace std;

Picture::Picture(){
    m_name = "";
    m_nbLines = 0;
    m_nbColumns = 0;
    m_deph = 0;
    m_format = 0;
    m_color = false;
}

Picture::Picture(const string & _name, unsigned int _nbLines, unsigned int _nbColumns, int _deph, int _format, bool _color){
    m_name = _name;
    m_nbLines = _nbLines;
    m_nbColumns = _nbColumns;
    m_deph = _deph;
    m_format = _format;
    m_color = _color;
}

Picture::~Picture(){

}

string Picture::GetName()const{
    return m_name;
}

unsigned int Picture::GetNbLines()const{
    return m_nbLines;
}

unsigned int Picture::GetNbColumns()const{
    return m_nbColumns;
}

int Picture::GetDeph()const{
    return m_deph;
}

int Picture::GetFormat()const{
    return m_format;
}

bool Picture::GetColor()const{
    return m_color;
}

void Picture::SetName(const string &_name){
    m_name = _name;
}

void Picture::SetNbLines(unsigned int _nbLines){
    m_nbLines = _nbLines;
}

void Picture::SetColumns(unsigned int _nbColumns){
    m_nbColumns = _nbColumns;
}

void Picture::SetDeph(int _deph) {
    m_deph = _deph;
}

void Picture::SetFormat(int _format){
    m_format = _format;
}

void Picture::SetColor(bool _color){
    m_color = _color;
}


bool Picture::IsGray()const{
    return m_color;
}

void Picture::FreePicture(void **_picture){
	for(unsigned int i=0 ; i<m_nbLines ; i++)
		delete _picture[i];
	delete _picture;

	
	
}

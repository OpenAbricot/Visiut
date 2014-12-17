#include "Picture.h"
#include <string>
using namespace std;

Picture::Picture(){
    name = "";
    nbLines = 0;
    nbColumns = 0;
    deph = 0;
    format = 0;
    color = false;

    cerr << "Construction" << this << endl;
}

Picture::Picture(const string & _name, unsigned int _nbLines, unsigned int _nbColumns, int _deph, int _format, bool _color){
    name = _name;
    nbLines = _nbLines;
    nbColumns = _nbColumns;
    deph = _deph;
    format = _format;
    color = _color;

    cerr << "Construction" << this << endl;
}

Picture::~Picture(){
    cerr << "Destruction" << this << endl;
}

string Picture::getName()const{
    return name;
}

unsigned int Picture::getNbLines()const{
    return nbLines;
}

unsigned int Picture::getNbColumns()const{
    return nbColumns;
}

int Picture::getDeph()const{
    return deph;
}

int Picture::getFormat()const{
    return format;
}

bool Picture::getColor()const{
    return color;
}

void Picture::setName(const string &_name){
    name = _name;
}

void Picture::setNbLines(unsigned int _nbLines){
    nbLines = _nbLines;
}

void Picture::setColumns(unsigned int _nbColumns){
    nbColumns = _nbColumns;
}

void Picture::setDeph(int _deph) {
    deph = _deph;
}

void Picture::setFormat(int _format){
    format = _format;
}

void Picture::setColor(bool _color){
    color = _color;
}


bool Picture::isGray()const{
    return color;
}

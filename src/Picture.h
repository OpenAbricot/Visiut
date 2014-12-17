#ifndef PICTURE_H
#define PICTURE_H

#include <typeinfo>
#include <iostream>
#include <string>

/*
 * @author @author Prunus
 *
 */


class Picture{

    protected :
        std::string name;
        unsigned int nbLines;
        unsigned int nbColumns;
        int deph;
        int format;
        bool color;

    public:
        Picture();
        Picture(const std::string & _name, unsigned int _nbLines, unsigned int _nbColumns, int _deph, int _format, bool _color);
        virtual ~Picture();
        std::string getName()const;
        unsigned int getNbLines()const;
        unsigned int getNbColumns()const;
        int getDeph()const;
        int getFormat()const;
        bool getColor()const;
        void setName(const std::string & _name);
        void setNbLines(unsigned int _nbLines);
        void setColumns(unsigned int _nbColumns);
        void setDeph(int _deph);
        void setFormat(int _format);
        void setColor(bool _color);
        bool isGray () const;
        virtual void setPixel(unsigned int _x, unsigned int _y, int _value) = 0;
        virtual void negative() = 0;
        virtual void verticalMirror() = 0;
        virtual void horizontalMirror() = 0;

};

#endif // PICTURE_H

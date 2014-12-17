#ifndef PICTURE_H
#define PICTURE_H

#include <typeinfo>
#include <iostream>
#include <string>

/*
 * @author INFS3D_Prj03 (Faglin Florian & Tissier Raphael & Benjamin Gounine)
 * @date 31/12/2011
 */


class Picture{
    protected :
        std::string m_name;
        unsigned int m_nbLines;
        unsigned int m_nbColumns;
        int m_deph;
        int m_format;
        bool m_color;

    public:
        Picture();
        Picture(const std::string & _name, unsigned int _nbLines, unsigned int _nbColumns, int _deph, int _format, bool _color);
        virtual ~Picture();
        std::string GetName()const;
        unsigned int GetNbLines()const;
        unsigned int GetNbColumns()const;
        int GetDeph()const;
        int GetFormat()const;
        bool GetColor()const;
        void SetName(const std::string & _name);
        void SetNbLines(unsigned int _nbLines);
        void SetColumns(unsigned int _nbColumns);
        void SetDeph(int _deph);
        void SetFormat(int _format);
        void SetColor(bool _color);
        virtual void SetPixel(unsigned int _x, unsigned int _y, int _value) = 0;
        bool IsGray () const;
        virtual void Negative() = 0;
        virtual void VerticalMirror() = 0;
        virtual void HorizontalMirror() = 0;

	protected:
		void FreePicture(void** _picture);

};

#endif // PICTURE_H

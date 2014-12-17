#ifndef PICTUREGRAY_H
#define PICTUREGRAY_H
#include <string>
#include "Models/headers/Picture.h"

/*
 * @author Benjamin Gounine
 * @date 10/03/2012
 */

class PictureGray : public Picture{
    private:
        unsigned char ** m_picture;

    public:
        PictureGray();
        PictureGray(unsigned char ** _picture, const std::string & _name, unsigned int _nbLines, unsigned int _nbColumns, int _deph, int _format, bool _color);
        PictureGray(const PictureGray & _picture);
        PictureGray operator =(const PictureGray & _picture);
        virtual ~PictureGray();
        unsigned char ** GetPictureGray()const;
        int getPixel(unsigned int _x,unsigned int _y) const;
        void SetPictureGray(unsigned char ** _picture);
        virtual void SetPixel(unsigned int _x, unsigned int _y, int _value);
        virtual void Negative();
        virtual void VerticalMirror();
        virtual void HorizontalMirror();

};

#endif // PICTUREGRAY_H

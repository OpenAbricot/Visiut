#ifndef PICTUREGRAY_H
#define PICTUREGRAY_H
#include <string>
#include "Picture.h"

/*
 * @author Prunus
 *
 */

class PictureGray : public Picture{
    private:
        unsigned char ** picture;

    public:
        PictureGray();
        PictureGray(unsigned char ** _picture, const std::string & _name, unsigned int _nbLines, unsigned int _nbColumns, int _deph, int _format, bool _color);
        PictureGray(const PictureGray & _picture);
        PictureGray operator =(const PictureGray & _picture);
        virtual ~PictureGray();
        unsigned char ** getPictureGray()const;
        int getPixel(unsigned int _x,unsigned int _y) const;
        void setPictureGray(unsigned char ** _picture);
        virtual void setPixel(unsigned int _x, unsigned int _y, int _value);
        virtual void negative();
        virtual void verticalMirror();
        virtual void horizontalMirror();

};

#endif // PICTUREGRAY_H

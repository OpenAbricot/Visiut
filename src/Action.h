#ifndef __Action_H__
#define __Action_H__
/*
 *@author Prunus
 */

#include <QImage>
#include <QString>
#include <QFileInfo>
#include <string>
#include "PictureColor.h"
#include "PictureGray.h"
#include "BackNext.h"


 //! Class Controleur.
 /*! This class gets back and extract information from the GUI in order to given this information at the Image class.
	 She also allows to reconstruc a Qimage object  from an Image Object */



class Action{
    private :
       QImage *image;
	   QFileInfo * image_info;
       BackNext backNext;
       static bool verbrose;

    public :

       enum Treatments{
           Negative,
           HorizontalMirror,
           VerticalMirror
       };

         //! Default contructor
        Action();

        //! Constructor */
        /*! Construc a new Controleur object with a QImage object given in parameters*/
		/**
		 * @param QImage
		 */
        Action(const QString & _path, bool _verbrose);

		//! Constructor
		/*! Construct a new Controleur Object with an Image<uchar> argument in order to built a grayscale image*/
        /**
                 *	@param _picture Allows to manipulate the 8-bits image(Grayscale Image)
		 */
        Action(const PictureGray & _picture, bool _verbrose);//NG8

		//! Constructor
		/*! Construct a new Controleur Object with an Image<uint> argument in order to built a color image*/
		/**
                 *  @param _picture I Allows to manipulate the 32-bits image(color Image)
         */
        Action(const PictureColor & _picture, bool _verbrose); //RGB32

        //! Copy Constructor
		/*! Construc a new Controleur Object, this Controleur is the copy of Controleur object given in parameters */
        /**
		 * @param Controleur A Controleur Object
		 */
        Action(const Action & _Action, bool _verbrose);

        //! Destructor
		/*! It's  a destructor ...*/
        ~Action();

                //! getQImage
		/*! Return a QImage Object*/
        QImage * getQImage()const;

                //! getPicture
		/*! Return an Image Object */
        QImage & getPicture()const;


        //! getHauteur
        /*! Return the Hauteur value of the QImage object */
        unsigned int getNbLines()const;

        //! getLargeur
        /*! Return the Largeur value of the QImage object */
        unsigned int getNbColumns()const;

        //!getDeph
        /*! Return the Profondeur value of the QImage object */
        int getDeph()const;

        //! Methode getFormat
        /*! Return  an integer value of the QImage object wich is representing the value of  the format
			Check http://doc.qt.nokia.com/4.6/qimage.html#Format-enum in order to know the possible value.
			Otherwise :  value = 3 : The image is stored using 8-bit indexes into a colormap.
                                     value = 4 : The image is stored using a 32-bit RGB format (0xffRRGGBB).*/
        unsigned int getFormat()const;

        //!getColor
        /*! Return true if the QImage is in color, otherwise, return false*/
        bool getColor()const;

        //!getPixel
        /*! this method return the pixel value at the given position */
		/**
         * @param unsigned int is the x value of the position
         * @param unsigned int is the y value of the position
		 */
        int getPixel(unsigned int _x, unsigned int _y)const;

		QFileInfo * getFileInfo()const;

		BackNext getBackNext()const;
        //! Operator =
        /*! Overriding of the operator = */
		/**
         * @param Controleur C  C is a Controleur Object
		 */
        Action & operator = (const Action & _Action);

		//! Sauver
		/*! Method wich allow to save the QImage*/
		/**
		 * @param Qstring is the name of the Image
		 */
        bool save(const QString & _path);

        void treatment(int _treatment);

        void ** getData()const;

        void setPicture(const PictureColor & _picture);

        void setPicture(const PictureGray & _picture);

		void setFileInfo(QFileInfo * _fileInfo);

		void setQImage(QImage * _image);

        void back();

        void next();

};

#endif

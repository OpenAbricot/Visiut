#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__
/*
 *@author infs3d_prj03 (Benjamin Gounine)
 */

#include <QImage>
#include <QString>
#include <QFileInfo>
#include <string>
#include "Models/headers/PictureColor.h"
#include "Models/headers/PictureGray.h"
#include "Models/headers/BackNext.h"


 //! Class Controleur.
 /*! This class gets back and extract information from the GUI in order to given this information at the Image class.
	 She also allows to reconstruc a Qimage object  from an Image Object */



class Controller{
    private :
       QImage *image;
	   QFileInfo * m_image_info;
       BackNext m_backNext;

    public :

       enum Treatments{
           Negative,
           HorizontalMirror,
           VerticalMirror
       };

         //! Default contructor
        Controller();
        
        //! Constructor */
        /*! Construc a new Controleur object with a QImage object given in parameters*/
		/**
		 * @param QImage
		 */
        Controller(const QString & _path);
        
		//! Constructor
		/*! Construct a new Controleur Object with an Image<uchar> argument in order to built a grayscale image*/ 
        /**
                 *	@param _picture Allows to manipulate the 8-bits image(Grayscale Image)
		 */
        Controller(const PictureGray & _picture);//NG8

		//! Constructor
		/*! Construct a new Controleur Object with an Image<uint> argument in order to built a color image*/
		/**
                 *  @param _picture I Allows to manipulate the 32-bits image(color Image)
         */
        Controller(const PictureColor & _picture); //RGB32

        //! Copy Constructor 
		/*! Construc a new Controleur Object, this Controleur is the copy of Controleur object given in parameters */
        /**
		 * @param Controleur A Controleur Object 
		 */ 
        Controller(const Controller & _controller);

        //! Destructor
		/*! It's  a destructor ...*/
        ~Controller();

                //! GetQImage
		/*! Return a QImage Object*/		
        QImage * GetQImage()const;

                //! GetPicture
		/*! Return an Image Object */		
        QImage & GetPicture()const;


        //! getHauteur
        /*! Return the Hauteur value of the QImage object */
        unsigned int GetNbLines()const;

        //! getLargeur
        /*! Return the Largeur value of the QImage object */
        unsigned int GetNbColumns()const;

        //!GetDeph
        /*! Return the Profondeur value of the QImage object */
        int GetDeph()const;

        //! Methode getFormat
        /*! Return  an integer value of the QImage object wich is representing the value of  the format 
			Check http://doc.qt.nokia.com/4.6/qimage.html#Format-enum in order to know the possible value.
			Otherwise :  value = 3 : The image is stored using 8-bit indexes into a colormap.
                                     value = 4 : The image is stored using a 32-bit RGB format (0xffRRGGBB).*/
        unsigned int GetFormat()const;

        //!GetColor
        /*! Return true if the QImage is in color, otherwise, return false*/
        bool GetColor()const;

        //!GetPixel
        /*! this method return the pixel value at the given position */
		/**
         * @param unsigned int is the x value of the position
         * @param unsigned int is the y value of the position
		 */
        int GetPixel(unsigned int _x, unsigned int _y)const;

		QFileInfo * GetFileInfo()const;

		BackNext GetBackNext()const;
        //! Operator =
        /*! Overriding of the operator = */
		/**
         * @param Controleur C  C is a Controleur Object
		 */
        Controller & operator = (const Controller & _controller);

		//! Sauver
		/*! Method wich allow to save the QImage*/
		/**
		 * @param Qstring is the name of the Image
		 */
        bool Save(const QString & _path);

        void Treatment(int _treatment);

        void ** GetData()const;

        void SetPicture(const PictureColor & _picture);

        void SetPicture(const PictureGray & _picture);

		void SetFileInfo(QFileInfo * _fileInfo);

		void SetQImage(QImage * _image);

        void Back();

        void Next();

};

#endif

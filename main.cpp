/*#include "Controller.h"
#include "PictureColor.h"
#include "BackNext.h"
#include <iostream>
#include <QImage>

using namespace std;

int main(){
	Controller C(QString("C:\\image.jpg"));
    C.Treatment(0);
    C.Treatment(1);
    C.Treatment(2);
	C.Back();
	C.Next();
	cout << C.Save("C:\\image2.jpg") << endl;
    	

    return 0;
}
*/

#include "visiut3.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Visiut3 w;
	w.show();
	return a.exec();
}
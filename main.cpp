#include "Action.h"
#include "PictureColor.h"
#include "BackNext.h"
#include <iostream>
#include <QImage>

using namespace std;

int main(){
	Action::verbrose = true;
	Action A(QString("image.jpg"));


/*  A.Treatment(0);
    A.Treatment(1);
    A.Treatment(2);
	A.Back();
	A.Next();
	cout << A.save("image2.jpg") << endl;
  */

    return 0;
}

/*
#include "visiut3.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Visiut3 w;
	w.show();
	return a.exec();
}*/

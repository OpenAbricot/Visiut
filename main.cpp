#include "src/Action.h"
#include "src/PictureColor.h"
#include "src/BackNext.h"
#include <iostream>
#include <QImage>

using namespace std;

int main(){
    QString S("image.jpg");
    Action A(S);


    A.treatment(0);
    A.treatment(1);
    A.treatment(2);
 //   A.back();
 //   A.next();
	cout << A.save("image2.jpg") << endl;


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

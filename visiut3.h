#ifndef VISIUT3_H
#define VISIUT3_H

#include <QtGui/QMainWindow>
#include "ui_visiut3.h"
#include "Controllers/headers/Controller.h"
#include "mainscene.h"
#include <QImage>
#include <QString>

class Visiut3 : public QMainWindow
{
	Q_OBJECT

private:
	Ui::Visiut3 ui;
	Controller * m_controller;
	MainScene * m_scene;

public:
	Visiut3(QWidget *parent = 0, Qt::WFlags flags = 0);
	~Visiut3();
	QImage * GetImage()const;
	void DisplayViaImage(QImage * _picture);
	void DisplayViaChemin(const QString & _path);
	QImage * viewToImage();
	void DisplayVierge(int _x, int _y);
	void miseAZero();

protected:
	void ChangeEvent(QEvent * _e);
	void CloseEvent(QCloseEvent * _e);
	void ContextMenuEvent(QContextMenuEvent * _e);

public slots:
	void on_ActionOpen_triggered();
	void on_ActionProperties_triggered();
	void on_ActionNegative_triggered();
	void on_ActionAbout_triggered();
	void on_ActionMirror_triggered();
	void on_ActionNew_triggered();
	void on_ActionSave_triggered();
	void on_ActionCancel_triggered();


};

#endif // VISIUT3_H

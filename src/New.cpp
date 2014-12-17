#include "New.h"
#include "ui_New.h"

New::New(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::New)
{
    ui->setupUi(this);
}

New::~New()
{
    delete ui;
}

int New::getWidth()const
{
    bool ok;
    return ui->lineEdit->text().toInt(&ok,10);
}

int New::getHeight()const
{
    bool ok;
    return ui->lineEdit_2->text().toInt(&ok,10);
}


void New::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

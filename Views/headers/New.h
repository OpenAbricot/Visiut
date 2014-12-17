#ifndef NEW_H
#define NEW_H

#include <QDialog>

namespace Ui {
    class New;
}

class New : public QDialog {
    Q_OBJECT
public:
    New(QWidget *parent = 0);
    ~New();
    int getWidth()const;
    int getHeight()const;

protected:
    void changeEvent(QEvent *e);

private:
    Ui::New *ui;
    QColor color;
};

#endif // New_H

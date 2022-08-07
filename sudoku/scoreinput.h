#ifndef SCOREINPUT_H
#define SCOREINPUT_H

#include <QMainWindow>

namespace Ui {
class scoreinput;
}

class scoreinput : public QMainWindow
{
    Q_OBJECT

public:
    explicit scoreinput(QWidget *parent = nullptr,int t=1,int g=0);
    ~scoreinput();

    int getType() const;

private:
    Ui::scoreinput *ui;
    void initUI();
    int type;
    int grade;
};

#endif // SCOREINPUT_H

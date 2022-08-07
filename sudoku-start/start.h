#ifndef START_H
#define START_H

#include <QDialog>
#include <QWidget>


namespace Ui {
class Start;
}

class Start : public QDialog
{
    Q_OBJECT


public:
    explicit Start(QWidget *parent = nullptr);
    ~Start();
private:
    void initUI();
    //void initSignalAndSlots();
//private slots:
    //void on_easyButton_clicked();

    //void on_mediumButton_clicked();

    //void on_hardButton_clicked();


//protected:

//    virtual void closeEvent(QCloseEvent *event);

//signals:
    //void easyshow();
    //void mediumshow();


private:
    Ui::Start *ui;
};

#endif // START_H

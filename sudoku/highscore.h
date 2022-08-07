#ifndef HIGHSCORE_H
#define HIGHSCORE_H

#include <QMainWindow>

namespace Ui {
class highscore;
}

class highscore : public QMainWindow
{
    Q_OBJECT

public:
    explicit highscore(QWidget *parent = nullptr);
    ~highscore();

private:
    Ui::highscore *ui;
    void initUI();
};

#endif // HIGHSCORE_H

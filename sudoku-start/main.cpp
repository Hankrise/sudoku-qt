#include "start.h"
#define cout qDebug().noquote().nospace()
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Start s;
    s.show();

    return a.exec();
}

#include <QCoreApplication>
#include <player.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    playTone(400, 2000);

    return a.exec();
}

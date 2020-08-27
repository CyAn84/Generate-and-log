#include "myapp.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    MyApp app(argc, argv);
    return app.exec();
}

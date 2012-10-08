#include <QApplication>
#include "qt.h"
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow window;
		int width = 400;
		int height = 400;
		int x,y;
		int screenWidth, screenHeight;
		QDesktopWidget *desktop = QApplication:: desktop();

		screenWidth = desktop->width();
		screenHeight = desktop->height();

		x = (screenWidth - width)/2;
		y = (screenHeight - height)/2;

    window.resize(width, height);
    window.move(x, y);
    window.setWindowTitle("Hares And Pumas Model");
		window.setWindowIcon(QIcon("icons/hare_and_puma.png"));
    window.show();
    return app.exec();
}


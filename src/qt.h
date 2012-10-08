#include <QtGui>
class MainWindow : public QMainWindow
{
	Q_OBJECT

	public:
		MainWindow();
	public slots:
		void update();
	private:
		void addMenu();
		void addToolbar();
		void loadDefaultPopulations();
		void drawField();
		QMenu *file, *options;
		QToolBar *toolbar;
		QWidget *contents;
		QLabel *mainImage;
		QLabel *statistics;
		int iteration;
		int harePopulation;
		int pumaPopulation;
};

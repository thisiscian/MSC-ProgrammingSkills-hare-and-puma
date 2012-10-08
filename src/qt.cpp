#include "qt.h"

MainWindow::MainWindow()
{
	contents = new QWidget(this);
	mainImage = new QLabel(this);
	statistics = new QLabel(this);
	iteration = 0;

	QHBoxLayout *layout = new QHBoxLayout();
	
	addMenu();
	addToolbar();  
	drawField();

	layout->addWidget(mainImage);
	layout->addWidget(statistics);
	contents->setLayout(layout);
	setCentralWidget(contents);
}

void MainWindow::drawField()
{
	int width=40, height=40;
	QImage editField(width,height,QImage::Format_RGB32);
	
	for(int i=0;i<width; i++)
	{
		for(int j=0;j<height; j++)
		{
			editField.setPixel(i,j, qRgb((i+10*iteration)%255, (j+10*iteration)%255, (i*j)%255));
		}
	}
	mainImage->setPixmap(QPixmap::fromImage(editField));
}

void MainWindow::loadDefaultPopulations()
{
	harePopulation = 10;
	pumaPopulation = 10;
}

void MainWindow::update()
{
	++iteration;
	drawField();
}

void MainWindow::addMenu()
{
  file = menuBar()->addMenu("&File");
	options = menuBar()->addMenu("&Options");
  
	QAction *newFile = new QAction("&New", this);
  QAction *loadHare = new QAction("Load &Hares", this);
  QAction *loadPuma = new QAction("Load &Puma", this);
  QAction *quit = new QAction("&Quit", this);
  QAction *size = new QAction("&Size", this);
  file->addAction(newFile);
	file->addSeparator();;
	file->addAction(loadHare);
	file->addAction(loadPuma);
	file->addSeparator();;
	file->addAction(quit);
	options->addAction(size);

//  connect(newFile, SIGNAL(triggered()), this, SLOT(printHello()));
  connect(quit, SIGNAL(triggered()), qApp, SLOT(quit()));
}

void MainWindow::addToolbar()
{
	toolbar = new QToolBar;
	QAction *play = new QAction(QIcon("icons/play.png"), "&Play", this);
  QAction *pause = new QAction(QIcon("icons/pause.png"), "&Pause", this);
  QAction *smallIncrement = new QAction(QIcon("icons/smallIncrement.png"), "Step +1", this);
  QAction *largeIncrement = new QAction(QIcon("icons/largeIncrement.png"), "Step +10", this);
	QAction *restart = new QAction(QIcon("icons/restart.png"), "Restart", this);		
	toolbar->setFloatable(false);
	toolbar->setMovable(false);
	toolbar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
	toolbar->addAction(restart);
	toolbar->addSeparator();
	toolbar->addAction(play);
	toolbar->addAction(pause);
	toolbar->addAction(smallIncrement);
	toolbar->addAction(largeIncrement);
	addToolBar(Qt::BottomToolBarArea, toolbar);
  
	connect(play, SIGNAL(triggered()), this, SLOT(update()));
}



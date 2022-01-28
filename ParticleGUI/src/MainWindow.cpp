#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  m_gl = new NGLScene(this);
  ui->m_mainWindowGridLayout->addWidget(m_gl,0,0,4,4);
  connect(ui->m_numParticles, SIGNAL(valueChanged(int)), m_gl, SLOT(changeNumberOfParticles(int)));
}

MainWindow::~MainWindow()
{
  delete ui;
  delete m_gl;
}

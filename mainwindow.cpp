#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  moles = {ui->pushButton_1, ui->pushButton_2, ui->pushButton_3,
           ui->pushButton_4, ui->pushButton_5, ui->pushButton_6,
           ui->pushButton_7, ui->pushButton_8, ui->pushButton_9,
           ui->pushButton_10};

  ui->progressBar->setValue(0);

  connect(ui->pushButtonStart, &QPushButton::clicked, this, &MainWindow::start);
  connect(&timerstep, &QTimer::timeout, this, &MainWindow::step);
  connect(&timermole, &QTimer::timeout, this, &MainWindow::popupMole);

  for (auto mole : moles) {
    connect(mole, &QPushButton::clicked, this, [=] {
      const QPixmap pixmap("../../media/mole-hit.png");
      mole->setIcon(QIcon(pixmap));
      mole->setIconSize(pixmap.rect().size());
      molesUp.erase(mole);
    });

    const QPixmap pixmap("../../media/mole-empty.png");
    mole->setIcon(QIcon(pixmap));
    mole->setIconSize(pixmap.rect().size());
  }

  rng.seed(QDateTime::currentMSecsSinceEpoch());
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::start() {
  t1.start();
  timerstep.start(50);
  timermole.start(3000);
  timePoppedUp = 0;

  for (auto mole : moles)
    mole->setEnabled(true);
}

void MainWindow::step() {
  const int32_t duration = 60000;
  const int64_t elapsed = t1.elapsed();
  ui->progressBar->setValue(float(elapsed) / duration * 100);

  timePoppedUp += molesUp.size() * timerstep.interval() / 1000.0;
  ui->label->setText(QString("%1").arg(timePoppedUp));

  if (elapsed > duration) {
    timerstep.stop();
    timermole.stop();

    for (auto mole : moles) {
      mole->setDisabled(true);
      mole->setStyleSheet("");
    }
    molesUp.clear();
  }
}

void MainWindow::popupMole() {
  QPushButton *mole = moles[rng.generate() % moles.size()];
  const QPixmap pixmap("../../media/mole-up.png");
  mole->setIcon(QIcon(pixmap));
  mole->setIconSize(pixmap.rect().size());
  molesUp.insert(mole);
}

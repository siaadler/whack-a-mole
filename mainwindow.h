#pragma once

#include <QElapsedTimer>
#include <QMainWindow>
#include <QPushButton>
#include <QRandomGenerator>
#include <QTimer>
#include <set>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private:
  Ui::MainWindow *ui;
  QTimer timermole;
  QTimer timerstep;
  QElapsedTimer t1;
  std::vector<QPushButton *> moles;
  std::set<QPushButton *> molesUp;
  float timePoppedUp = 0;
  QRandomGenerator rng;

  void start();
  void step();
  void popupMole();
};

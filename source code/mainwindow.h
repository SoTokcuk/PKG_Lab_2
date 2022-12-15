#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QTableWidget>
#include <QtDebug>
#include <QFileDialog>
#include <QImageWriter>


class MainWindow : public QWidget {
  Q_OBJECT
public:
  explicit MainWindow(QWidget *parent = nullptr);
    void setRaw(QStringList nameFilters);

private slots:
    void choosingDirect();
    void readTables(int idx);


private:
  QTableWidget m_table;
  QTableWidget dir_table;
  QLineEdit m_statusMessage;
  QFileDialog w;
  QFileInfoList fileInfo;
  QImage img;
  QImageWriter imgWr;
  QStringList dirs;

};

#endif // MAINWINDOW_H

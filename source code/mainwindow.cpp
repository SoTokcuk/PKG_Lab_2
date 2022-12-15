#include "mainwindow.h"
#include "qheaderview.h"

#include <QComboBox>
#include <QFileDialog>
#include <QImageWriter>
#include <QListView>
#include <QTreeView>

MainWindow::MainWindow(QWidget *parent)
  : QWidget(parent),
    m_table(0, 6, this),
    dir_table(0, 1, this)
{
    setWindowTitle("Filemenager");

    //m_table.setEnabled(false);
    m_table.setFocusPolicy(Qt::NoFocus);
    m_table.setEditTriggers(0);
    m_table.setSelectionMode(QAbstractItemView::SelectionMode(0));
    dir_table.setFocusPolicy(Qt::NoFocus);
    dir_table.setEditTriggers(0);
    dir_table.setSelectionMode(QAbstractItemView::SelectionMode(0));
    dir_table.setHorizontalHeaderLabels(QStringList({"Diretories"}));
    dir_table.setGeometry(150,0,750,100);
    dir_table.setColumnWidth(0, 850);



    m_table.setHorizontalHeaderLabels(QStringList({"File name", "Image size","Permission", "Extension", "Color deep", "Compression"}));
    m_table.setColumnWidth(0, 300);
    for(int i = 0; i < 5; i++){
        if(i == 0){
            m_table.setColumnWidth(i, 300);
        }
        m_table.setColumnWidth(i, 175);
    }

    m_table.setGeometry(0,100,1000,800);

    auto direct = new QPushButton("Choosing directory", this);
    direct->setGeometry(0,0,150,100);

    QStringList filters;
    filters <<"all" << "jpg" << "gif" << "tif" << "bmp" << "png" << "pcx";
    auto combo = new QComboBox(this);
    combo->addItems(filters);
    combo->setGeometry(900, 0, 100, 100);
    connect(combo, SIGNAL(currentIndexChanged(int)), SLOT(readTables(int)));

    connect(direct, SIGNAL(clicked()), SLOT(choosingDirect()));

    //m_table.setSortingEnabled(false);

    auto header = m_table.horizontalHeader();
    connect(header, &QHeaderView::sectionClicked, [this](int logicalIndex){
        QString text = m_table.horizontalHeaderItem(logicalIndex)->text();
        m_table.sortItems(logicalIndex,Qt::SortOrder(Qt::AscendingOrder));
    });
    connect(header, &QHeaderView::sectionDoubleClicked, [this](int logicalIndex){
        QString text = m_table.horizontalHeaderItem(logicalIndex)->text();
       m_table.sortItems(logicalIndex,Qt::SortOrder(Qt::DescendingOrder));
    });

}

void MainWindow::setRaw(QStringList nameFilters)
{
    m_table.clearContents();
    dirs = w.selectedFiles();
    QString currentPath = "";
    for(int i = 0 ; i < dirs.size(); i++){
        currentPath = dirs[i];
        dir_table.insertRow(dir_table.rowCount());
        dir_table.setItem(i, 0, new QTableWidgetItem(QString(currentPath)));
        QDir dir(currentPath);
        fileInfo = dir.entryInfoList(nameFilters, QDir::Files|QDir::Readable, QDir::Name);
        int l = 0;
        for(QFileInfo tem : fileInfo){
            m_table.insertRow(m_table.rowCount());
            m_table.setItem(l, 0, new QTableWidgetItem(tem.completeBaseName()));
            m_table.setItem(l, 1, new QTableWidgetItem(QString::number(tem.size())));
            m_table.setItem(l, 3, new QTableWidgetItem(tem.suffix()));
            img.load(currentPath  + "/" + tem.completeBaseName());
            m_table.setItem(l, 2, new QTableWidgetItem(QString::number(img.width()) + "*" + QString::number(img.height())));
            m_table.setItem(l, 4, new QTableWidgetItem(QString::number(img.bitPlaneCount())));
            imgWr.setFileName(tem.completeBaseName());
            m_table.setItem(l, 5, new QTableWidgetItem(QString::number(imgWr.compression())));
            l++;
        }
    }
}

void MainWindow::readTables( int idx ) {

    if(idx == 0){
        QStringList nameFilters;
        nameFilters << "*.jpg" << "*.gif" << "*.tif" << "*.bmp" << "*.png" << "*.pcx";
        setRaw(nameFilters);
    }
    if(idx == 1){
        QStringList nameFilters;
        nameFilters << "*.jpg";
        setRaw(nameFilters);
    }
    if(idx == 2){
        QStringList nameFilters;
        nameFilters << "*.gif";
        setRaw(nameFilters);
    }
    if(idx == 3){
        QStringList nameFilters;
        nameFilters << "*.tif";
        setRaw(nameFilters);
    }
    if(idx == 4){
        QStringList nameFilters;
        nameFilters << "*.bmp";
        setRaw(nameFilters);
    }
    if(idx == 5){
        QStringList nameFilters;
        nameFilters << "*.png";
        setRaw(nameFilters);
    }
    if(idx == 6){
        QStringList nameFilters;
        nameFilters << "*.pcx";
        setRaw(nameFilters);
    }


}

void MainWindow::choosingDirect()
{
    m_table.clearContents();
    dir_table.clearContents();
    dirs.clear();


    w.setFileMode(QFileDialog::DirectoryOnly);
    w.setOption(QFileDialog::DontUseNativeDialog,true);
    QListView *lView = w.findChild<QListView*>("listView");
    if (lView)
        lView->setSelectionMode(QAbstractItemView::MultiSelection);
    QTreeView *tView = w.findChild<QTreeView*>();
    if (tView)
        tView->setSelectionMode(QAbstractItemView::MultiSelection);
    w.exec();
    QStringList nameFilters;
    nameFilters << "*.jpg" << "*.gif" << "*.tif" << "*.bmp" << "*.png" << "*.pcx";
    setRaw(nameFilters);
    //m_table.setSortingEnabled(true);

}







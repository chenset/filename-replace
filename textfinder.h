#ifndef TEXTFINDER_H
#define TEXTFINDER_H

#include <string>
#include <iostream>
#include <QWidget>
#include <QApplication>
#include <QLineEdit>
#include <QDragEnterEvent>
#include <QFileInfo>
#include <QMimeData>
#include <QTableWidget>
#include <sstream>

class QPushButton;

class QTextEdit;

class QLineEdit;

class TextFinder : public QWidget {
Q_OBJECT

public:
    TextFinder(QWidget *parent = 0);

private slots:

    void on_findButton_clicked();

private:
    QWidget *loadUiFile();

    void loadTextFile();

    QPushButton *ui_findButton;
    QTextEdit *ui_textEdit;
    QLineEdit *ui_lineEdit;
    QTableWidget *m_pTableWidget;
    QStringList m_TableHeader;
    QList<QUrl> file_list;
    bool isFirstTime;

protected:
    virtual void dragEnterEvent(QDragEnterEvent *event) override {
        if (event->mimeData()->hasUrls())
            event->acceptProposedAction();
    }

    virtual void dragMoveEvent(QDragMoveEvent *event) override {
        if (event->mimeData()->hasUrls())
            event->acceptProposedAction();
    }

    virtual void dropEvent(QDropEvent *event) override {
        if (event->mimeData()->hasUrls()) {
            file_list = event->mimeData()->urls();
            QFileInfo *fileInfo = nullptr;
            m_pTableWidget->setRowCount(file_list.length());
            for (int i = 0; i < file_list.length(); ++i) {
                fileInfo = new QFileInfo(file_list.at(i).toLocalFile());

                //insert data
                m_pTableWidget->setItem(i, 0, new QTableWidgetItem(QString::number(i + 1)));
//                m_pTableWidget->setItem(i, 1, new QTableWidgetItem(fileInfo->absoluteFilePath()));
                m_pTableWidget->setItem(i, 1, new QTableWidgetItem(fileInfo->fileName()));

            }
            delete fileInfo;
//            QFileInfo *fileInfo = new QFileInfo(list.at(0).toLocalFile());
//            std::cout << list.length() << std::endl;
            event->acceptProposedAction();
        }
    }
};

#endif
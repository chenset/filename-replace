#include <QtUiTools>
#include <QtWidgets>
#include "textfinder.h"
#include <QTableView>
#include <QApplication>
#include <QLineEdit>
#include <QDragEnterEvent>
#include <QFileInfo>
#include <QMimeData>
#include <regex>


TextFinder::TextFinder(QWidget *parent)
        : QWidget(parent) {

    QWidget *formWidget = loadUiFile();
//    this->setFixedWidth(700);
    this->setMinimumSize(700, 500);

    ui_findButton = findChild<QPushButton *>("findButton");
//    ui_textEdit = findChild<QTextEdit *>("textEdit");
    ui_lineEdit = findChild<QLineEdit *>("lineEdit");

    m_pTableWidget = new QTableWidget(this);
    m_pTableWidget->setRowCount(2);
    m_pTableWidget->setColumnCount(2);
    m_TableHeader << "#" << "file";
    m_pTableWidget->setColumnWidth(0, 40);
    m_pTableWidget->setColumnWidth(1, 636);
    m_pTableWidget->setHorizontalHeaderLabels(m_TableHeader);
    QHeaderView *m_tableTopHeader = m_pTableWidget->verticalHeader();
    m_tableTopHeader->setVisible(false);

    m_pTableWidget->setStyleSheet("QHeaderView::section { background-color:#DDDDDD}");
    m_pTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_pTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_pTableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    m_pTableWidget->setShowGrid(true);
    m_pTableWidget->setStyleSheet("QTableView {selection-background-color: #f2f2f2;}");
    m_pTableWidget->setGeometry(QApplication::desktop()->screenGeometry());

    //insert data
//    m_pTableWidget->setItem(0, 1, new QTableWidgetItem("Hello"));
//    m_pTableWidget->setItem(0, 0, new QTableWidgetItem("Hello"));


    QMetaObject::connectSlotsByName(this);

//    loadTextFile();

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(m_pTableWidget);
    layout->addWidget(formWidget);
    setLayout(layout);

//    QTableView *view = new QTableView;
//
//    QStandardItemModel *mod = new QStandardItemModel(this);
//    QStandardItem *it = new QStandardItem(QObject::tr("ID"));
//    mod->setHorizontalHeaderItem(0, it);
//    QStandardItem *it1 = new QStandardItem(QObject::tr("Name"));
//    mod->setHorizontalHeaderItem(1, it1);
//    QStandardItem *it2 = new QStandardItem(QObject::tr("City"));
//    mod->setHorizontalHeaderItem(2, it2);
//    QStandardItem *it3 = new QStandardItem(QObject::tr("Country"));
//    mod->setHorizontalHeaderItem(3, it3);
////and so on
//    view->setModel(mod);
//    view->show();

//    QTableView *view = new QTableView;
//    QStringListModel *model;
//    view->setModel(model);
//    view->show();
//    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
//    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Name"));
//    model->setHeaderData(2, Qt::Horizontal, QObject::tr("City"));
//    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Country"));

    setAcceptDrops(true);
    setWindowTitle(tr("Text Finder"));
    isFirstTime = true;

}

QWidget *TextFinder::loadUiFile() {
    QUiLoader loader;

    QFile file(":/forms/textfinder.xml");
    file.open(QFile::ReadOnly);

    QWidget *formWidget = loader.load(&file, this);
    file.close();

    return formWidget;
}

//void TextFinder::loadTextFile() {
//    QFile inputFile(":/forms/input.txt");
//    inputFile.open(QIODevice::ReadOnly);
//    QTextStream in(&inputFile);
//    QString line = in.readAll();
//    inputFile.close();
//
//    ui_textEdit->append(line);
//    ui_textEdit->setUndoRedoEnabled(false);
//    ui_textEdit->setUndoRedoEnabled(true);
//}

void TextFinder::on_findButton_clicked() {
    std::string renameTo = ui_lineEdit->text().toStdString();
//    QTextDocument *document = ui_textEdit->document();

//    QMessageBox::information(this, "Empty Search Field",
//                             "The search field is empty. Please enter a word and click Find.");


//    QString fileName = QFileDialog::getOpenFileName(this,
//                                                    "Open XML File 1", "/home", "XML Files (*.*)");
//    ui_lineEdit->setText(fileName);

    if (file_list.empty()) {
        QMessageBox::information(this, "内容为空", "请先将文件拖拽到程序中!");
        return;
    }

    if (renameTo.empty()) {
        QMessageBox::information(this, "内容为空", "请输入重命名后的文件名!");
        return;
    }





//
//    std::smatch outputMatch;
//    if (!regex_search(outputName, outputMatch, std::regex("#+"))) {
//        return;
//    }


    std::smatch inputMatch;
    if (!regex_search(renameTo, inputMatch, std::regex("#+"))) {
        QMessageBox::information(this, "内容为空", "# is empty!");
        return;
    }

    unsigned inputMatchLen = (unsigned) inputMatch[0].length();
    std::string matchRepeat(inputMatchLen, '#');
//
//    std::string strNum = file.substr(renameTo.find(matchRepeat), inputMatchLen);

    std::string NewFilename =  regex_replace(renameTo, std::regex(matchRepeat), "2");


    std::cout << NewFilename << std::endl;
//    std::cout << " ---------------------------------------------------------- " << endl;
//    std::cout << path + file + "\r\nrename to:\r\n" + NewFilename << endl;
//    rename((path + file).c_str(), NewFilename.c_str());


    return;
/*
    QFileInfo *file = nullptr;

    int res;//todo list

    for (int i = 0; i < file_list.length(); ++i) {
        file = new QFileInfo(file_list[i].toLocalFile());


        res = rename(file->absoluteFilePath().toStdString().c_str(),
                     (file->absolutePath() + "/" + renameTo).toStdString().c_str());

        std::cout << res << std::endl;

        std::cout << file->absoluteFilePath().toStdString().c_str() << std::endl;
        std::cout << (file->absolutePath() + "/" + renameTo).toStdString().c_str() << std::endl;

    }

    QMessageBox::information(this, "内容为空", res == 0 ? "成功" : "失败");

    delete file;

    */
//    QMessageBox::information(this, "内容为空", file->absoluteFilePath());
//    QMessageBox::information(this, "内容为空", file->absolutePath());
//    QMessageBox::information(this, "内容为空", file->filePath());
//

//    rename((path + file).c_str(), NewFilename.c_str());

//    std::cout << file->absoluteFilePath() << std::endl;
//    QMessageBox::information(this,"title",QString::number());

//    QFileDialog dialog(this);
//    dialog.setDirectory(QDir::homePath());
//    dialog.setFileMode(QFileDialog::ExistingFiles);
//    dialog.setNameFilter("Text files (*.*)");
//    QStringList fileNames;
//    if (dialog.exec())
//        fileNames = dialog.selectedFiles();
//
//    if (!fileNames.length()) {
//        QMessageBox::information(this, tr("Empty"),
//                                 "未选中任何文件!");
//        return;
//    }
//    for (int i = 0; i < fileNames.length(); ++i) {
//        QMessageBox::information(this, tr("Empty"),
//                                 fileNames[i]);
//    }


//    ui->File1Path->setText(file1Name);

//    bool found = false;
//
//    if (isFirstTime == false)
//        document->undo();
//
//    if (searchString.isEmpty()) {
//        QMessageBox::information(this, tr("Empty Search Field"),
//                                 "The search field is empty. Please enter a word and click Find.");
//    } else {
//
//        QTextCursor highlightCursor(document);
//        QTextCursor cursor(document);
//
//        cursor.beginEditBlock();
//
//        QTextCharFormat plainFormat(highlightCursor.charFormat());
//        QTextCharFormat colorFormat = plainFormat;
//        colorFormat.setForeground(Qt::red);
//
//        while (!highlightCursor.isNull() && !highlightCursor.atEnd()) {
//            highlightCursor = document->find(searchString, highlightCursor, QTextDocument::FindWholeWords);
//
//            if (!highlightCursor.isNull()) {
//                found = true;
//                highlightCursor.movePosition(QTextCursor::WordRight,
//                                             QTextCursor::KeepAnchor);
//                highlightCursor.mergeCharFormat(colorFormat);
//            }
//        }
//
//        cursor.endEditBlock();
//        isFirstTime = false;
//
//        if (found == false) {
//            QMessageBox::information(this, tr("Word Not Found"),
//                                     "Sorry, the word cannot be found.");
//        }
//    }
}
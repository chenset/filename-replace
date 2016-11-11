#include <QtUiTools>
#include "textfinder.h"
#include <regex>


TextFinder::TextFinder(QWidget *parent)
        : QWidget(parent) {

    QWidget *formWidget = loadUiFile();
//    this->setFixedWidth(700);
    this->setMinimumSize(900, 500);

    ui_findButton = findChild<QPushButton *>("findButton");
//    ui_textEdit = findChild<QTextEdit *>("textEdit");
    ui_lineEdit = findChild<QLineEdit *>("lineEdit");

    m_pTableWidget = new QTableWidget(this);
    m_pTableWidget->setRowCount(2);
    m_pTableWidget->setColumnCount(2);
    m_TableHeader << "#" << "file";
    m_pTableWidget->setColumnWidth(0, 40);
    m_pTableWidget->setColumnWidth(1, 836);
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

    QMetaObject::connectSlotsByName(this);

//    loadTextFile();
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(m_pTableWidget);
    layout->addWidget(formWidget);
    setLayout(layout);

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

void TextFinder::on_findButton_clicked() {
    std::string renameTo = ui_lineEdit->text().toStdString();

    if (file_list.empty()) {
        QMessageBox::information(this, "内容为空", "请先将文件拖拽到程序中!");
        return;
    }

    if (renameTo.empty()) {
        QMessageBox::information(this, "内容为空", "请输入重命名后的文件名!");
        return;
    }


    std::smatch inputMatch;
    if (!regex_search(renameTo, inputMatch, std::regex("#+"))) {
        QMessageBox::information(this, "内容为空", "# is empty!");
        return;
    }

    unsigned inputMatchLen = (unsigned) inputMatch[0].length();
    std::string matchRepeat(inputMatchLen, '#');

    QFileInfo *file = nullptr;

    for (int i = 0; i < file_list.length(); ++i) {
        int padLen = inputMatchLen - QString::number(i + 1).toStdString().length();
        if (padLen < 0) {
            padLen = 0;
        }
        unsigned unsignedPadLen = (unsigned) padLen;
        std::string pad(unsignedPadLen, '0');
        std::string NewFilename = regex_replace(renameTo, std::regex(matchRepeat),
                                                pad + QString::number(i + 1).toStdString());
        std::cout << NewFilename << std::endl;

        file = new QFileInfo(file_list[i].toLocalFile());

        QFile::rename(file->absoluteFilePath(),QString::fromStdString(file->absolutePath().toStdString() + "/" + NewFilename));
        
        std::cout << file->absoluteFilePath().toStdString().c_str() << std::endl;
        std::cout << (file->absolutePath().toStdString() + "/" + NewFilename).c_str() << std::endl;
    }

    delete file;


    return;
}
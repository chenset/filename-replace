/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtUiTools>
#include <QtWidgets>
#include "textfinder.h"

#include <QApplication>
#include <QLineEdit>
#include <QDragEnterEvent>
#include <QFileInfo>
#include <QMimeData>


TextFinder::TextFinder(QWidget *parent)
        : QWidget(parent) {

    QWidget *formWidget = loadUiFile();

    ui_findButton = findChild<QPushButton *>("findButton");
    ui_textEdit = findChild<QTextEdit *>("textEdit");
    ui_lineEdit = findChild<QLineEdit *>("lineEdit");
    setAcceptDrops(false);

    QMetaObject::connectSlotsByName(this);

    loadTextFile();

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(formWidget);
    setLayout(layout);
    setAcceptDrops(true);
    setWindowTitle(tr("Text Finder"));
    isFirstTime = true;
}

QWidget *TextFinder::loadUiFile() {
    QUiLoader loader;

    QFile file(":/forms/textfinder.ui");
    file.open(QFile::ReadOnly);

    QWidget *formWidget = loader.load(&file, this);
    file.close();

    return formWidget;
}

void TextFinder::loadTextFile() {
    QFile inputFile(":/forms/input.txt");
    inputFile.open(QIODevice::ReadOnly);
    QTextStream in(&inputFile);
    QString line = in.readAll();
    inputFile.close();

    ui_textEdit->append(line);
    ui_textEdit->setUndoRedoEnabled(false);
    ui_textEdit->setUndoRedoEnabled(true);
}

void TextFinder::on_findButton_clicked() {
    QString searchString = ui_lineEdit->text();
    QTextDocument *document = ui_textEdit->document();

//    QMessageBox::information(this, "Empty Search Field",
//                             "The search field is empty. Please enter a word and click Find.");


//    QString fileName = QFileDialog::getOpenFileName(this,
//                                                    "Open XML File 1", "/home", "XML Files (*.*)");
//    ui_lineEdit->setText(fileName);

    QFileDialog dialog(this);
    dialog.setDirectory(QDir::homePath());
    dialog.setFileMode(QFileDialog::ExistingFiles);
    dialog.setNameFilter("Text files (*.*)");
    QStringList fileNames;
    if (dialog.exec())
        fileNames = dialog.selectedFiles();

    if (!fileNames.length()) {
        QMessageBox::information(this, tr("Empty"),
                                 "未选中任何文件!");
        return;
    }
    for (int i = 0; i < fileNames.length(); ++i) {
        QMessageBox::information(this, tr("Empty"),
                                 fileNames[i]);
    }


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
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
            QList<QUrl> list = event->mimeData()->urls();
            QFileInfo *fileInfo = nullptr;
            QString sss;
            m_pTableWidget->setRowCount(list.length());
            for (int i = 0; i < list.length(); ++i) {
                fileInfo = new QFileInfo(list.at(i).toLocalFile());
                sss += fileInfo->absoluteFilePath();

                //insert data
                m_pTableWidget->setItem(i, 0, new QTableWidgetItem("Hello"));
                m_pTableWidget->setItem(i, 1, new QTableWidgetItem(fileInfo->absoluteFilePath()));

            }
            delete fileInfo;
//            QFileInfo *fileInfo = new QFileInfo(list.at(0).toLocalFile());
//            std::cout << list.length() << std::endl;
            ui_lineEdit->setText(sss);
            event->acceptProposedAction();
        }
    }
};

#endif
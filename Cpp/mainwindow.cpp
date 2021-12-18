#include "mainwindow.h"
#include "Consistency.h"
#include "Prettify.h"
#include "Xml_to_Json.h"
#include "ui_mainwindow.h"
#include"minify.h"
#include<string>
#include<iostream>
#include"check_errors.h"
#include "Compression.h"
#include <QSaveFile>
#include "Bit.h"
#include <fstream>


using namespace std;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::about(this,"About the Project","An XML editor (Windows Application) to facilitate the editing of xml files. User can load XML file and choose multiple features from buttons in GUI. Once a file is uploaded, the program detects the errors, corrects them, show an error message with number of errors in input file, creates a new consistent file in the same path as the input file ,and views a successful message indicating that the process was successful. Also, user can format XML file, minify it, convert it into JSON file, compress it to reduce its size ,and able to decompress it.");
}


void MainWindow::on_actionAbout_us_triggered()
{
    QMessageBox::about(this,"About the Project","Suiiiiiiiiiiiiiiiiiii");
}

void MainWindow::on_actionCopy_triggered()
{
    ui->plainTextEdit->copy();
}



void MainWindow::on_actionPaste_triggered()
{
    ui->plainTextEdit->paste();
}


void MainWindow::on_actionUndo_triggered()
{
    ui->plainTextEdit->undo();
}


void MainWindow::on_actionRedo_triggered()
{
    ui->plainTextEdit->redo();
}


void MainWindow::on_pushButton_2_clicked()
{
    QString file_name=QFileDialog::getOpenFileName(this,"Select a file","C://");
    QFile file(file_name);
    if(!file.open(QFile::ReadOnly |QFile::Text)){QMessageBox::warning(this,"Warning!","file is not opening");}
    QTextStream in(&file);
    QString text=in.readAll();
    ui->plainTextEdit->setPlainText(text);

}


void MainWindow::on_pushButton_3_clicked()
{
    QString file_name=QFileDialog::getSaveFileName(this,"Select a file","C://",tr("All files (*.*);;XML files (*.xml);;Text files (*.txt);;JSON Files(*.json)"));
    QFile file(file_name);
    if(!file.open(QFile::WriteOnly |QFile::Text)){QMessageBox::warning(this,"Warning!","file is not Saved");}
    QTextStream out(&file);
    QString text=ui->plainTextEdit->toPlainText();
    out<<text;
    file.flush();
    file.close();

}


void MainWindow::on_pushButton_4_clicked()
{
    QString text =ui->plainTextEdit->toPlainText();
     string x=text.toStdString();
    string Result=Check_XML_Consistency(x);
    QString str = QString::fromStdString(Result);
    ui->plainTextEdit_2->setPlainText(str);

}


void MainWindow::on_pushButton_9_clicked()
{
    QString text =ui->plainTextEdit->toPlainText();
    string x=text.toStdString();
    string Result=format_XML(x);
    QString str = QString::fromStdString(Result);
    ui->plainTextEdit_2->setPlainText(str);

}


void MainWindow::on_pushButton_5_clicked()
{
     QString text =ui->plainTextEdit->toPlainText();
     string x=text.toStdString();
     Tree t=parse(x);
     string Result=t.XMLToJson();
     QString str = QString::fromStdString(Result);
     ui->plainTextEdit_2->setPlainText(str);


}


void MainWindow::on_pushButton_8_clicked()
{
    QMessageBox::warning(this,"Warning!","file is Saved in The Same Directory As .exe file");
    QString text =ui->plainTextEdit->toPlainText();
    string x=text.toStdString();
    string Result=Huffman_encoding(x);
    vector<uint8_t> Result2=toBinary(Result);
    const std::vector<uint8_t>  buffer(Result2); // let's assume that i'ts filled with values
    std::ofstream out("file.huff", std::ios::out | std::ios::binary);
    out.write(reinterpret_cast<const char*>(buffer.data()), buffer.size());
    out.close();
}


void MainWindow::on_pushButton_7_clicked()
{
    QString text =ui->plainTextEdit->toPlainText();
    string x=text.toStdString();
    string Result=minify_XML(minify_XML(minify_XML(x)));
    QString str = QString::fromStdString(Result);
    ui->plainTextEdit_2->setPlainText(str);

}


void MainWindow::on_pushButton_6_clicked()
{
    QString text =ui->plainTextEdit->toPlainText();
    string x=text.toStdString();
    string Result=Check_XML_Errors(x);
    QString str = QString::fromStdString(Result);
    ui->plainTextEdit_2->setPlainText(str);
}


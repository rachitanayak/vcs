#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QFile>
#include<QTextStream>
#include<QMessageBox>
#include<QDir>
#include<QFileDialog>
#include<QInputDialog>
#include<iostream>
#include<fstream>
#include"header.h"

using namespace std;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    for(int i=1;i<=3;i++)
        ui->user->addItem("user_"+QString::number(i));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_openfile_clicked()
{
     QString currentUser = ui->user->currentText();
     QString pathToDirectory = "C:\\Users\\Rachita Nayak\\Desktop\\FS Mini Project\\"+currentUser;
     QString currentFilename="program.txt";
     mFilename="C:\\Users\\Rachita Nayak\\Desktop\\FS Mini Project\\"+currentUser+"\\program.txt";
     string ifile=mFilename.toLocal8Bit().constData();
     ifstream  fp(ifile, std::ios::binary);
     string temp="C:\\Users\\Rachita Nayak\\Desktop\\FS Mini Project\\temp.txt";
     ofstream tp(temp,ios::binary);
     tp<<fp.rdbuf();



     int count=ui->version->count();
     for(int i=0;i<=count;i++)
     {
         ui->version->clear();
     }


     QFile file( QString("%1//%2").arg(pathToDirectory, currentFilename) );
     // do stuff with that file
     if(!file.open(QIODevice::ReadOnly))
         QMessageBox::information(0,"info",file.errorString());

     QTextStream in(&file);

     ui->textEdit->setText(in.readAll());

     tp<<fp.rdbuf();
     ui->label_2->setText(" ");


     QStringRef userId(&currentUser,5,1);
     count=countFiles(pathToDirectory);
     for(int i=1;i<count;i++)
         ui->version->addItem("program"+userId+"."+QString::number(i));


}



void MainWindow::on_actionCut_triggered()
{
    ui->textEdit->cut();
}


void MainWindow::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}

void MainWindow::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}


void MainWindow::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}


void MainWindow::on_actionCopy_triggered()
{
  ui->textEdit->copy();
}

void MainWindow::on_actionSave_triggered()
{
    QString currentUser = ui->user->currentText();
    QString pathToDirectory = "C:\\Users\\Rachita Nayak\\Desktop\\FS Mini Project\\"+currentUser;
    /*QString currentFilename="program.txt";
    QFile file( QString("%1//%2").arg(pathToDirectory, currentFilename) )
    */
    mFilename="C:\\Users\\Rachita Nayak\\Desktop\\FS Mini Project\\"+currentUser+"\\program.txt";
    string path =pathToDirectory.toLocal8Bit().constData();
    string user=currentUser.toLocal8Bit().constData();
    string ifile=mFilename.toLocal8Bit().constData();

    string temp="C:\\Users\\Rachita Nayak\\Desktop\\FS Mini Project\\temp.txt";

    QFile sfile(mFilename);

     if(sfile.open(QFile::WriteOnly) | QFile::Text)
     {
         QTextStream out(&sfile);
         out<<ui->textEdit->toPlainText();
         sfile.flush();
         sfile.close();

     }
      ui->label_2->setText( mFilename+" was saved!");

     int flag=compareFiles(ifile,temp);
     string f=to_string(flag);
     QString qstr = QString::fromStdString(f);

     createVersion(pathToDirectory,ifile,user);

}

void MainWindow::on_actionCommit_triggered()
{
    QString currentUser = ui->user->currentText();
    QString pathToDirectory = "C:\\Users\\Rachita Nayak\\Desktop\\FS Mini Project\\";

    string filepath=pathToDirectory.toLocal8Bit().constData();
    string user=currentUser.toLocal8Bit().constData();
    mFilename="C:\\Users\\Rachita Nayak\\Desktop\\FS Mini Project\\"+currentUser+"\\program.txt";
    string ifile=mFilename.toLocal8Bit().constData();

    QFile sfile(mFilename);

     if(sfile.open(QFile::WriteOnly) | QFile::Text)
     {
         QTextStream out(&sfile);
         out<<ui->textEdit->toPlainText();
         sfile.flush();
         sfile.close();


     }


     ui->label_2->setText("You commited the changes of"+mFilename);
}

void MainWindow::on_view_clicked()
{
    QString currentUser=ui->user->currentText();
    QString pathToDirectory = "C:\\Users\\Rachita Nayak\\Desktop\\FS Mini Project\\"+currentUser+"\\";
    QString currentFileName = ui->version->currentText()+".txt";
    QFile file( QString("%1//%2").arg(pathToDirectory, currentFileName) );
    // do stuff with that file
    if(!file.open(QIODevice::ReadOnly))
        QMessageBox::information(0,"info",file.errorString());

    QTextStream in(&file);
    ui->textEdit->setText(in.readAll());
}

void MainWindow::on_revert_clicked()
{
    QString currentUser=ui->user->currentText();
    QString pathToDirectory = "C:\\Users\\Rachita Nayak\\Desktop\\FS Mini Project\\"+currentUser+"\\";
    string user=currentUser.toLocal8Bit().constData();
    QString currentFile=ui->version->currentText();
    string filename=currentFile.toLocal8Bit().constData();
    string filepath="C:\\Users\\Rachita Nayak\\Desktop\\FS Mini Project\\"+user+"\\";
    int count=countFiles(pathToDirectory);
    revert(filepath,filename,count);

    ui->label_2->setText("The program was reverted to "+currentFile);

}

void MainWindow::on_actionPush_triggered()
{



    QString answer=QInputDialog::getText(this,"Push File To Application Folder","Enter \"commit\" to verify commit");
    string ans=answer.toLocal8Bit().constData();
    if(ans=="commit")
    {
       /*copy contents of user_id/program.txt to application folder"*/
        QString currentUser = ui->user->currentText();
        QString pathToDirectory = "C:\\Users\\Rachita Nayak\\Desktop\\FS Mini Project\\"+currentUser;
        string path =pathToDirectory.toLocal8Bit().constData();
        string user=currentUser.toLocal8Bit().constData();
        QString appath="C:\\Users\\Rachita Nayak\\Desktop\\FS Mini Project\\Application\\";

        string filepath=path+"\\program.txt";

        ifstream ip(filepath,ios::binary);
        string name="program_v";


        string dest="C:\\Users\\Rachita Nayak\\Desktop\\FS Mini Project\\Application\\"+name+user[5]+".txt";
        ofstream fp(dest,ios::binary|ios::app);
        fp<<"\n";
        fp<<ip.rdbuf();

        fp<<"\n"<<"----------------------------------------------------------------------------------------";





    }
}




void MainWindow::on_pull_clicked()
{
    QString currentUser = ui->lineEdit->text();
    QString pathToDirectory = "C:\\Users\\Rachita Nayak\\Desktop\\FS Mini Project\\Application";
    QString currentFilename="program_v"+currentUser[5]+".txt";
    QFile file( QString("%1//%2").arg(pathToDirectory, currentFilename) );
    // do stuff with that file
    if(!file.open(QIODevice::ReadOnly))
        QMessageBox::information(0,"info",file.errorString());

    QTextStream in(&file);

    ui->textEdit->setText(in.readAll());


}

#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QFontDialog>
#include "notepad.h"
#include "ui_notepad.h"

Notepad::Notepad(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Notepad)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit);
}

Notepad::~Notepad()
{
    delete ui;
}

void Notepad::on_actionNew_triggered(){
    currentFile.clear();
    ui->textEdit->setText(QString());
}

void Notepad::on_actionOpen_triggered(){
    QString filename =QFileDialog::getOpenFileName(this, "Open the file");
    QFile file(filename);
    currentFile =filename;
    if(!file.open(QIODevice::ReadOnly|QFile::Text)){
        QMessageBox::warning(this, "warning", "Cant open the file:"+file.errorString());
        return;
    }
    setWindowTitle(filename);
    QTextStream in(&file);
    QString text =in.readAll();
    ui->textEdit->setText(text);
    file.close();
}
void Notepad::on_actionSave_triggered(){
    QString fileName;
    if(currentFile.isEmpty()){
        fileName =QFileDialog::getSaveFileName(this, "Save");
        currentFile =fileName;
    }else{
        fileName =currentFile;
    }
    QFile file(fileName);
    if(!file.open(QIODevice::WriteOnly|QFile::Text)){
        QMessageBox::warning(this, "warning", "Cant save file:"+file.errorString());
        return;
    }
    setWindowTitle(fileName);
    QTextStream out(&file);
    QString text =ui->textEdit->toPlainText();
    out << text;
    file.close();
}

void Notepad::on_actionSave_as_triggered(){
    QString fileName =QFileDialog::getSaveFileName(this, "Save");
    QFile file(fileName);
    if(!file.open(QIODevice::WriteOnly|QFile::Text)){
        QMessageBox::warning(this, "warning", "Cant open file:"+file.errorString());
        return;
    }
    currentFile =fileName;
    setWindowTitle(fileName);
    QTextStream out(&file);
    QString text =ui->textEdit->toPlainText();
    out << text;
    file.close();
}

void Notepad::on_actionPrint_triggered(){}

void Notepad::on_actionExit_triggered(){
    QCoreApplication::quit();
}

void Notepad::on_actionCopy_triggered(){
#if QT_CONFIG(clipboard)
    ui->textEdit->copy();
#endif
}

void Notepad::on_actionCut_triggered(){
#if QT_CONFIG(clipboard)
    ui->textEdit->cut();
#endif
}

void Notepad::on_actionPaste_triggered(){
#if QT_CONFIG(clipboard)
    ui->textEdit->paste();
#endif
}

void Notepad::on_actionUndo_triggered(){
    ui->textEdit->undo();
}

void Notepad::on_actionRedo_triggered(){
    ui->textEdit->redo();
}

void Notepad::on_actionFont_triggered(){
    bool fontSelected;
    QFont font =QFontDialog::getFont(&fontSelected, this);
    if(fontSelected){
        ui->textEdit->setFont(font);
    }
}

void Notepad::on_actionBold_triggered(){}

void Notepad::on_actionUnderline_triggered(){}

void Notepad::on_actionItalic_triggered(){}

void Notepad::on_actionAbout_triggered(){}

#include "noteii.h"
#include <QtWidgets>


Noteii::Noteii()
    :textEdit(new QPlainTextEdit)
{
    //添加空间及事件响应
    createActions();
    //设置中心窗体
    setCentralWidget(textEdit);

    setCurrentFile(QString());

    connect(textEdit->document(),&QTextDocument::contentsChanged,this, &Noteii::documentWasModified);
}

void Noteii::createActions(){
    //文件选单
    QMenu *fileName =menuBar()->addMenu(tr("&File"));
    //new选项
    QAction *newAction =new QAction(tr("&New"),this);
    newAction->setShortcut(QKeySequence::New);
    newAction->setStatusTip("Create a new text");
    fileName->addAction(newAction);
    //open选项
    QAction *openAction =new QAction(tr("&Open"),this);
    openAction->setShortcut(QKeySequence::Open);
    openAction->setStatusTip("Open a new text");
    fileName->addAction(openAction);
    //save选项
    QAction *saveAction =new QAction(tr("&Save"),this);
    saveAction->setShortcut(QKeySequence::Save);
    saveAction->setStatusTip("Save a new text");
    connect(saveAction, &QAction::triggered, this, &Noteii::save);
    fileName->addAction(saveAction);
    //saveas选项
    QAction *saveAsAction =new QAction(tr("&Save_as"),this);
    saveAsAction->setShortcut(QKeySequence::SaveAs);
    saveAsAction->setStatusTip("Save a new text to anywhere");
    fileName->addAction(saveAsAction);
    //添加分隔符
    fileName->addSeparator();
    //exit选项
    QAction *exitAction =new QAction(tr("&Exit"),this);
    exitAction->setShortcut(QKeySequence::Quit);
    exitAction->setStatusTip("Quit");
    fileName->addAction(exitAction);
    //edit选单
    QMenu *editName =menuBar()->addMenu(tr("&Edit"));
    //cut选项
    QAction *cutAction =new QAction(tr("&Cut"),this);
    cutAction->setShortcut(QKeySequence::Cut);
    cutAction->setStatusTip("Cut the text");
    editName->addAction(cutAction);
    //copy选项
    QAction *copyAction =new QAction(tr("&Copy"),this);
    copyAction->setShortcut(QKeySequence::Copy);
    copyAction->setStatusTip("Copy the text");
    editName->addAction(copyAction);
    //paste选项
    QAction *pasteAction =new QAction(tr("&Paste"),this);
    pasteAction->setShortcut(QKeySequence::Paste);
    pasteAction->setStatusTip("Paste the text");
    editName->addAction(pasteAction);
}

void Noteii::documentWasModified(){
    setWindowModified(textEdit->document()->isModified());
}

void Noteii::setCurrentFile(const QString &fileName){
    currentFile =fileName;
    textEdit->document()->setModified(false);
    setWindowModified(false);
    QString showname =currentFile;
    if(currentFile.isEmpty()){
        showname ="Untitled.txt";
    }
    setWindowFilePath(showname);
}

bool Noteii::save(){
    if(currentFile.isEmpty()){
        return saveAs();
    }else{
        return saveFile(currentFile);
    }
}

bool Noteii::saveAs(){
    QFileDialog dialog(this);
    dialog.setWindowModality(Qt::WindowModal);
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    if(dialog.exec() != QDialog::Accepted){
        return false;
    }
    return saveFile(dialog.selectedFiles().first());
}

bool Noteii::saveFile(const QString &fileName){
    QFile file(fileName);
    if(!file.open(QFile::WriteOnly|QFile::Text)){
        QMessageBox::warning(this,tr("Application"), tr("Cant write file"));
        return false;
    }
    QTextStream out(&file);
    out << textEdit->toPlainText();
    setCurrentFile(fileName);
    return true;
}

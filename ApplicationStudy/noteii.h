#ifndef NOTEII_H
#define NOTEII_H

#include <QMainWindow>
#include <QPlainTextEdit>

class Noteii : public QMainWindow
{
    Q_OBJECT

public:
    Noteii();

public slots:
    void documentWasModified();
    bool save();
    bool saveAs();

private:
    void createActions();
    void setCurrentFile(const QString &fileName);
    bool saveFile(const QString &fileName);

    QPlainTextEdit *textEdit;
    QString currentFile;
};

#endif // NOTEII_H

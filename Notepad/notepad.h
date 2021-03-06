#ifndef NOTEPAD_H
#define NOTEPAD_H

#include <QMainWindow> // 主窗口

namespace Ui {
class Notepad;
}

class Notepad : public QMainWindow
{
    Q_OBJECT // 必须

public:
    explicit Notepad(QWidget *parent = 0);
    ~Notepad(); // 析构函数

private slots:
    void on_actionNew_triggered();

    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_actionSave_as_triggered();

    void on_actionPrint_triggered();

    void on_actionExit_triggered();

    void on_actionCopy_triggered();

    void on_actionCut_triggered();

    void on_actionPaste_triggered();

    void on_actionUndo_triggered();

    void on_actionRedo_triggered();

    void on_actionFont_triggered();

    void on_actionBold_triggered();

    void on_actionUnderline_triggered();

    void on_actionItalic_triggered();

    void on_actionAbout_triggered();

private:
    Ui::Notepad *ui;
    QString currentFile;
};

#endif // NOTEPAD_H

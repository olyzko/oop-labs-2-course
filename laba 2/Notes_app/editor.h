#ifndef EDITOR_H
#define EDITOR_H

#include <QDialog>
#include <QFile>
#include <QToolBar>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QPrinter>
#include <QPrintDialog>
#include <QInputDialog>
#include <QDateTime>
#include <QCloseEvent>

#include "note.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Editor; }
QT_END_NAMESPACE

class Editor : public QDialog
{
    Q_OBJECT
public:
    Editor(QWidget *parent = nullptr);
    ~Editor();

private:
    Ui::Editor *ui;

protected:
    void showEvent(QShowEvent *event) override;

private slots:
    void on_toolButton_triggered(QAction *arg1);
    void on_actionSave_triggered();
    void on_toolButton_clicked();
};

#endif // EDITOR_H

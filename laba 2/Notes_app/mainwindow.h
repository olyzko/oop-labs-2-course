#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QToolBar>
#include <QMessageBox>
#include <QPrinter>
#include <QPrintDialog>
#include <QVector>
#include <QStandardItemModel>
#include <QDebug>

#include "note.h"
#include "editor.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


    void addToList(Note* note, QStandardItemModel *model);

    void readFromFile(QString dataFileName, QString textFolderName, QStandardItemModel *model);
    void readWithCategory(QString category, QStandardItemModel *model);

    void writeDataToFile(QString fileName, QVector<Note*>& list);
    void writeTextToFiles(QString folderName, QVector<Note*>& list);

    void insertionSort(QVector<Note*> list);

    int getNotePositionInFile(int left, int right, Note& note, QVector<Note*>& list);

private slots:
    void on_add_button_clicked();

    void on_archive_button_clicked();

    void on_delete_button_clicked();

    void on_actionNew_triggered();

    void on_actionArchive_Unarchive_triggered();

    void on_actionDelete_triggered();

    void on_actionEdit_triggered();

    void on_edit_button_clicked();

    void on_listView_4_clicked(const QModelIndex &index);

    void on_main_list_button_clicked();

    void on_archive_list_button_clicked();

    void on_actionShow_main_list_triggered();

    void on_actionShow_archive_list_triggered();

    void on_personal_checkBox_stateChanged(int arg1);

    void on_uni_checkBox_stateChanged(int arg1);

    void on_work_checkBox_stateChanged(int arg1);

    void on_listView_4_doubleClicked(const QModelIndex &index);

    void on_sort_button_clicked();

    void on_renameButton_clicked();

private:
    Ui::MainWindow *ui;

    QVector<Note*> main_notes;
    QVector<Note*> archived_notes;
    QStandardItemModel *main_model;
    QStandardItemModel *archive_model;

    Editor editor;

    void checkCategories(QVector<Note*> list);
};
#endif // MAINWINDOW_H

#include "editor.h"
#include "ui_editor.h"
#include <QDebug>

Editor::Editor(QWidget *parent)
    : QDialog(parent), ui(new Ui::Editor)
{
    ui->setupUi(this);
}

Editor::~Editor () {
     delete ui;
}

void Editor::showEvent(QShowEvent *event) {
    if(Note::currentNote!=nullptr){

        setWindowTitle(Note::currentNote->title);

        ui->textEdit->setText(Note::currentNote->text);

        if(Note::currentNote->category == "Work"){
            ui->work->setChecked(true);
        }else if(Note::currentNote->category == "Personal"){
            ui->personal->setChecked(true);
        }else if(Note::currentNote->category == "University"){
            ui->uni->setChecked(true);
        }

    } else {
        setWindowTitle("New note");
        ui->textEdit->setText("");
        ui->work->setChecked(true);
        ui->personal->setChecked(false);
        ui->uni->setChecked(false);
    }
}

void Editor::on_actionSave_triggered()
{
    on_toolButton_clicked();
}


void Editor::on_toolButton_clicked()
{
    QString category;
    QString text = ui->textEdit->toPlainText();
    QDateTime time = QDateTime::currentDateTime();

    if(ui->personal->isChecked()){
        category = "Personal";
    } else if(ui->work->isChecked()){
        category = "Work";
    } else if(ui->uni->isChecked()){
        category = "University";
    }

    if(Note::currentNote==nullptr){
        QString title = QInputDialog::getText(this, "Saving...","Enter file name");
        Note::currentNote = new Note(title, text, category, time);
        setWindowTitle(Note::currentNote->title);
    } else {
        Note::currentNote->editTime = time;
        Note::currentNote->category = category;
        Note::currentNote->text = text;
    }

    Editor::close();
}


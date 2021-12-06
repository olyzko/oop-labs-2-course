#include "mainwindow.h"
#include "ui_mainwindow.h"

QString MAIN_DATA_PATH = "main_notesData.txt";
QString MAIN_TEXT_PATH = "main_notesText/";

QString ARCHIVE_DATA_PATH = "archive_notesData.txt";
QString ARCHIVE_TEXT_PATH = "archive_notesText/";

Note* Note::currentNote = nullptr;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    main_model(new QStandardItemModel),
    archive_model(new QStandardItemModel)
{
    ui->setupUi(this);

    ui->listView_4->setModel(main_model);

    readFromFile(MAIN_DATA_PATH, MAIN_TEXT_PATH, main_model);
    readFromFile(ARCHIVE_DATA_PATH, ARCHIVE_TEXT_PATH, archive_model);
}

MainWindow::~MainWindow(){
    //saving any changes
    writeDataToFile(MAIN_DATA_PATH, main_notes);
    writeDataToFile(ARCHIVE_DATA_PATH, archived_notes);
    writeTextToFiles(MAIN_TEXT_PATH, main_notes);
    writeTextToFiles(ARCHIVE_TEXT_PATH, archived_notes);
    delete ui;
}

void MainWindow::readFromFile(QString dataFileName, QString textFolderName, QStandardItemModel *model)
{
    QFile dataNotes(dataFileName);
    if (!dataNotes.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "aaaaaaaaa" <<dataFileName;
        return;
    }

    while(!dataNotes.atEnd()){
        //read title
        QString title = dataNotes.readLine();
        title.remove(title.size()-1,1);

        //read date
        QString year = dataNotes.readLine();
        QString month = dataNotes.readLine();
        QString day = dataNotes.readLine();
        QString hour = dataNotes.readLine();
        QString minute = dataNotes.readLine();
        QString second = dataNotes.readLine();
        QDateTime createTime = QDateTime(QDate(year.toInt(),month.toInt(), day.toInt()),QTime(hour.toInt(),minute.toInt(), second.toInt()));

        //read category
        QString category = dataNotes.readLine();
        category.remove(category.size()-1,1);

        //read text
        QString fileName = Note::dateToFileName(createTime);
        //qDebug() << fileName;
        QFile textNotes(textFolderName+fileName);
        if (!textNotes.open(QIODevice::ReadOnly | QIODevice::Text)){
            return;
        }
        QString text = textNotes.readAll();
        textNotes.close();

        //adding note to list
        Note* newNote = new Note(title, text, category, createTime);
        addToList(newNote, model);
    }

    dataNotes.close();
}


void MainWindow::addToList(Note* note, QStandardItemModel *model)
{
    int position;
    long long zero = 0;
    if(model == main_model){
        position = getNotePositionInFile(0, std::max(zero, main_notes.size()-1), *note, main_notes);
        main_notes.insert(main_notes.begin() + position, note);
    } else {
        position = getNotePositionInFile(0, std::max(zero, archived_notes.size()-1), *note, archived_notes);
        archived_notes.insert(archived_notes.begin() + position, note);
    }
    model->insertRow(position, new QStandardItem(note->title));
}

int MainWindow::getNotePositionInFile(int left, int right, Note& note, QVector<Note*>& list)
{
    if (left == right)
        return left;

    int middle = (left+right)/2;

    if (list[middle]->editTime > note.editTime)
        getNotePositionInFile(left, middle, note, list);
    else
        getNotePositionInFile(middle+1, right, note, list);

    return left;
}


void MainWindow::writeDataToFile(QString fileName, QVector<Note*>& list)
{
    QFile dataNotes(fileName);
    dataNotes.open(QIODevice::WriteOnly);

    QTextStream out(&dataNotes);
    for (int i = 0; i < list.size(); i++)
    {
        out << list[i]->title << "\n";
        out << list[i]->editTime.date().year() << "\n";
        out << list[i]->editTime.date().month() << "\n";
        out << list[i]->editTime.date().day() << "\n";
        out << list[i]->editTime.time().hour() << "\n";
        out << list[i]->editTime.time().minute() << "\n";
        out << list[i]->editTime.time().second() << "\n";
        out << list[i]->category << "\n";
    }
    out.flush();
    dataNotes.close();
}

void MainWindow::writeTextToFiles(QString folderName, QVector<Note*>& list)
{
    for (int i = 0; i < list.size(); i++)
    {
        QString fileName = Note::dateToFileName(list[i]->editTime);
        QFile textNotes(folderName+fileName);
        if (!textNotes.open(QIODevice::WriteOnly | QIODevice::Text)){
            return;
        }

        QTextStream out(&textNotes);

        out << list[i]->text;

        out.flush();
        textNotes.close();
    }
}

void MainWindow::on_add_button_clicked()
{
    Note::currentNote = nullptr;
    editor.exec();

    if(Note::currentNote != nullptr){
         main_notes.push_back(Note::currentNote);
         main_model->appendRow(new QStandardItem(Note::currentNote->title));
         Note::currentNote = nullptr;
    }
}


void MainWindow::on_archive_button_clicked()
{
    if (Note::currentNote != nullptr) {
    int index = ui->listView_4->currentIndex().row();

    if(ui->listView_4->model() == main_model && main_notes.size() != 0){
        QFile file(MAIN_TEXT_PATH+Note::dateToFileName(main_notes[index]->editTime));
        file.remove();

        archived_notes.push_back(main_notes[index]);
        main_notes.erase(main_notes.begin()+index);

        archive_model->insertRow(archived_notes.size()-1, new QStandardItem(archived_notes.last()->title));
        main_model->removeRow(index);

        qDebug() << main_notes.size();
    }
    else if (ui->listView_4->model() == archive_model && archived_notes.size() != 0) {
        QFile file(MAIN_TEXT_PATH+Note::dateToFileName(archived_notes[index]->editTime));
        file.remove();

        main_notes.push_back(archived_notes[index]);
        archived_notes.erase(archived_notes.begin()+index);

        main_model->insertRow(main_notes.size()-1, new QStandardItem(main_notes.last()->title));
        archive_model->removeRow(index);
    }
    }
    else qDebug() << "aaaaaaaaa";
}


void MainWindow::on_delete_button_clicked()
{
    int index = ui->listView_4->currentIndex().row();

    if(ui->listView_4->model() == main_model && main_notes.size() != 0){
        QFile file(MAIN_TEXT_PATH+Note::dateToFileName(main_notes[index]->editTime));
        file.remove();
        main_notes.erase(main_notes.begin()+index);
        main_model->removeRow(index);
    }
    else if (ui->listView_4->model() == archive_model && archived_notes.size() != 0) {
        QFile file(ARCHIVE_TEXT_PATH+Note::dateToFileName(archived_notes[index]->editTime));
        file.remove();
        archived_notes.erase(archived_notes.begin()+index);
        archive_model->removeRow(index);
    }
}

void MainWindow::on_edit_button_clicked()
{
    Note oldNote = *Note::currentNote;

    editor.exec();

    if(oldNote.editTime != Note::currentNote->editTime){
        int index = ui->listView_4->currentIndex().row();
        QString old_text_file_path;

        if(ui->listView_4->model() == main_model){
            old_text_file_path = MAIN_TEXT_PATH+Note::dateToFileName(main_notes[index]->editTime);
        } else
            old_text_file_path = ARCHIVE_TEXT_PATH+Note::dateToFileName(archived_notes[index]->editTime);

        QFile old_text_file(old_text_file_path);
        old_text_file.remove();

        if(ui->listView_4->model() == main_model){
            main_notes.erase(main_notes.begin()+index);
            main_notes.insert(main_notes.begin()+index, Note::currentNote);
        } else {
            archived_notes.erase(archived_notes.begin()+index);
            archived_notes.insert(archived_notes.begin()+index, Note::currentNote);
        }
    }
}


void MainWindow::on_actionNew_triggered()
{
    on_add_button_clicked();
}


void MainWindow::on_actionArchive_Unarchive_triggered()
{
    if (Note::currentNote != nullptr)
        on_archive_button_clicked();
}

void MainWindow::on_actionDelete_triggered()
{
    if (Note::currentNote != nullptr)
        on_delete_button_clicked();
}


void MainWindow::on_actionEdit_triggered()
{
    if (Note::currentNote != nullptr)
        on_edit_button_clicked();
}



void MainWindow::on_listView_4_clicked(const QModelIndex &index)
{
    ui->edit_button->setEnabled(true);
    ui->archive_button->setEnabled(true);
    ui->delete_button->setEnabled(true);
    ui->renameButton->setEnabled(true);

    if(ui->listView_4->model() == main_model){
        Note::currentNote = main_notes.at(index.row());
    } else
        Note::currentNote = archived_notes.at(index.row());
}


void MainWindow::on_main_list_button_clicked()
{
    ui->listView_4->setModel(main_model);

    ui->personal_checkBox->setChecked(true);
    ui->work_checkBox->setChecked(true);
    ui->uni_checkBox->setChecked(true);
}


void MainWindow::on_archive_list_button_clicked()
{
    ui->listView_4->setModel(archive_model);

    ui->personal_checkBox->setChecked(true);
    ui->work_checkBox->setChecked(true);
    ui->uni_checkBox->setChecked(true);
}


void MainWindow::on_actionShow_main_list_triggered()
{
    on_main_list_button_clicked();
}


void MainWindow::on_actionShow_archive_list_triggered()
{
    on_archive_list_button_clicked();
}


void MainWindow::on_personal_checkBox_stateChanged(int arg1)
{
    QVector<Note*> list;
    if(ui->listView_4->model() == main_model){
        list = main_notes;
    } else list = archived_notes;

    checkCategories(list);
}

void MainWindow::checkCategories(QVector<Note*> list){

    bool isWorkChecked = ui->work_checkBox->isChecked();
    bool isPersonalChecked = ui->personal_checkBox->isChecked();
    bool isStudyingChecked = ui->uni_checkBox->isChecked();

    //clear listView
    ui->listView_4->model()->removeRows(0, ui->listView_4->model()->rowCount());

    int removed = 0;

    for(int i = 0; i < list.size(); i++){

        if(list.at(i)->category == "Personal"){
          if(isPersonalChecked){
              //insert back to the listView
              if(ui->listView_4->model() == main_model){
                  main_model->insertRow(i-removed, new QStandardItem(list.at(i)->title));
                } else {
                  archive_model->insertRow(i-removed, new QStandardItem(list.at(i)->title));
               }
          } else {
              //leave it removed...
              removed++;
          }
        }

       else if(list.at(i)->category == "Work"){
           if(isWorkChecked){
               if(ui->listView_4->model() == main_model){
                   main_model->insertRow(i-removed, new QStandardItem(list.at(i)->title));
                 } else {
                   archive_model->insertRow(i-removed, new QStandardItem(list.at(i)->title));
                }
           } else {
               removed++;
           }
       }

       else if(list.at(i)->category == "University"){
           if(isStudyingChecked){
               if(ui->listView_4->model() == main_model){
                   main_model->insertRow(i-removed, new QStandardItem(list.at(i)->title));
                 } else {
                   archive_model->insertRow(i-removed, new QStandardItem(list.at(i)->title));
                }
           } else {
               removed++;
           }
       }
    }
}

void MainWindow::on_uni_checkBox_stateChanged(int arg1)
{
    on_personal_checkBox_stateChanged(arg1);
}


void MainWindow::on_work_checkBox_stateChanged(int arg1)
{
    on_personal_checkBox_stateChanged(arg1);
}


void MainWindow::on_listView_4_doubleClicked(const QModelIndex &index)
{
    on_edit_button_clicked();
}


void MainWindow::on_sort_button_clicked()
{
    qDebug() << "aaaaaaaaa";
    insertionSort(main_notes);
    insertionSort(archived_notes);


}

void MainWindow::insertionSort(QVector<Note*> list)
{
    int i, j;
    int n = list.size();
    QString key;
    for (i = 1; i < n; i++)
    {
        key = list[i]->title;
        j = i - 1;

        while (j >= 0 && list[j]->title > key)
        {
            list[j + 1]->title = list[j]->title;
            j = j - 1;
        }
        list[j + 1]->title = key;
    }
}

void MainWindow::on_renameButton_clicked()
{
    QString title = QInputDialog::getText(this, "Saving...","Enter file name");
    int index = ui->listView_4->currentIndex().row();

    if(ui->listView_4->model() == main_model)
        main_model->removeRow(index);
    else
        archive_model->removeRow(index);

    Note::currentNote->title = title;
    Note::currentNote->editTime = QDateTime::currentDateTime();

    if(ui->listView_4->model() == main_model)
        main_model->insertRow(main_notes.size()-1, new QStandardItem(main_notes[index]->title));
    else
        archive_model->insertRow(archived_notes.size()-1, new QStandardItem(archived_notes[index]->title));

}

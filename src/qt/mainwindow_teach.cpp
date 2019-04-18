#include "mainwindow_teach.h"
#include "../build-qt-Desktop-Debug/ui_mainwindow_teach.h"
#include "mainwindow.h"
#include "../headers/database.h"

extern sqlite3 *db;

MainWindow_teach::MainWindow_teach(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow_teach)
{
    ui->setupUi(this);
}

MainWindow_teach::~MainWindow_teach()
{
    delete ui;
}

void MainWindow_teach::Set_init_mode(int mode) {

    /* Main part */
    if (!mode) {
        ui->actionStudents_2->setChecked(true);
        ui->actionQuestions->setChecked(false);
        ui->actionAllow->setVisible(true);
        // ui->actionNew_Database->setVisible(false);
        // ui->actionOpen_Database->setVisible(false);
        // ui->actionClose_Database->setVisible(false);
    } else {
        ui->actionStudents_2->setChecked(false);
        ui->actionQuestions->setChecked(true);
        ui->actionAllow->setVisible(false);
        // ui->actionNew_Database->setVisible(true);
        // ui->actionOpen_Database->setVisible(true);
        // ui->actionClose_Database->setVisible(true);
    }


    ui->stackedWidget->setCurrentIndex(mode);
}

void MainWindow_teach::on_actionStudents_2_triggered()
{

    /* Main part */
    Set_init_mode(0);
}

void MainWindow_teach::on_actionQuestions_triggered()
{

    /* Main part */
    Set_init_mode(1);
}

void MainWindow_teach::on_actionExit_triggered()
{

    /* Initializing variables */
    QMessageBox::StandardButton reply;

    /* Main part */
    reply = QMessageBox::question(this, "Teacher's mode", "Are you sure you want to exit?", QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        this->close();
    }
}

void MainWindow_teach::on_comboBox_currentIndexChanged(int index)
{
    /* Initializing variables */
    char a[10];
    sprintf(a, "%d", index);
    int id = 0;
    double mean = 0.0;
    struct Marks mks;
    struct User usr;

    /* Main part */
    if (index) {
        id = get_student_id(ui->comboBox->currentIndex());
        if (!id) {
            return;
        }
        mks = db_get_user_marks(id);
        usr = db_get_user(id);
        ui->lineFN->setText(usr.first_name);
        ui->lineLN->setText(usr.last_name);
        ui->lineLogin->setText(usr.login);
        sprintf(a, "%d", usr.id);
        ui->lineID->setText(a);

        sprintf(a, "%d", mks.values[0]);
        ui->lineLoops->setText(a);
        sprintf(a, "%d", mks.values[1]);
        ui->lineArrays->setText(a);
        sprintf(a, "%d", mks.values[2]);
        ui->lineStrings->setText(a);
        sprintf(a, "%d", mks.values[3]);
        ui->lineRecursion->setText(a);
        sprintf(a, "%d", mks.values[4]);
        ui->lineStructures->setText(a);
        sprintf(a, "%d", mks.values[5]);
        ui->lineFiles->setText(a);
        sprintf(a, "%d", mks.values[6]);
        ui->linePointers->setText(a);
        sprintf(a, "%d", mks.values[7]);
        ui->lineDyn_Mem->setText(a);
        sprintf(a, "%d", mks.values[9]);
        ui->lineFinal->setText(a);

        mean = get_mean(id);
        sprintf(a, "%6.3lf", mean);
        ui->lineMean->setText(a);
    } else {
        ui->actionAllow->setChecked(false);
        ui->lineLoops->setReadOnly(true);
        ui->lineArrays->setReadOnly(true);
        ui->lineStrings->setReadOnly(true);
        ui->lineRecursion->setReadOnly(true);
        ui->lineStructures->setReadOnly(true);
        ui->lineFiles->setReadOnly(true);
        ui->linePointers->setReadOnly(true);
        ui->lineDyn_Mem->setReadOnly(true);
        ui->lineFinal->setReadOnly(true);
        ui->pushButton->setEnabled(false);
        ui->pushButton_2->setEnabled(false);

        ui->lineFN->setText("");
        ui->lineLN->setText("");
        ui->lineLogin->setText("");
        ui->lineID->setText("");
        ui->lineLoops->setText("");
        ui->lineArrays->setText("");
        ui->lineStrings->setText("");
        ui->lineRecursion->setText("");
        ui->lineStructures->setText("");
        ui->lineFiles->setText("");
        ui->linePointers->setText("");
        ui->lineDyn_Mem->setText("");
        ui->lineFinal->setText("");
        ui->lineMean->setText("");
    }

    ui->pushButton_rm->setEnabled((index) ? true : false);
}

void MainWindow_teach::on_actionAllow_triggered()
{

    /* Main part */
    if (ui->comboBox->currentIndex()) {
        if ((ui->actionAllow->isChecked())) {
            ui->actionAllow->setChecked(true);
            ui->lineLoops->setReadOnly(false);
            ui->lineArrays->setReadOnly(false);
            ui->lineStrings->setReadOnly(false);
            ui->lineRecursion->setReadOnly(false);
            ui->lineStructures->setReadOnly(false);
            ui->lineFiles->setReadOnly(false);
            ui->linePointers->setReadOnly(false);
            ui->lineDyn_Mem->setReadOnly(false);
            ui->lineFinal->setReadOnly(false);
            ui->pushButton->setEnabled(true);
            ui->pushButton_2->setEnabled(true);
        } else {
            ui->actionAllow->setChecked(false);
            ui->lineLoops->setReadOnly(true);
            ui->lineArrays->setReadOnly(true);
            ui->lineStrings->setReadOnly(true);
            ui->lineRecursion->setReadOnly(true);
            ui->lineStructures->setReadOnly(true);
            ui->lineFiles->setReadOnly(true);
            ui->linePointers->setReadOnly(true);
            ui->lineDyn_Mem->setReadOnly(true);
            ui->lineFinal->setReadOnly(true);
            ui->pushButton->setEnabled(false);
            ui->pushButton_2->setEnabled(false);
        }
    }
}

void MainWindow_teach::on_actionLog_out_triggered()
{

    /* Initializing variables */
    QMessageBox::StandardButton reply;

    /* Main part */
    reply = QMessageBox::question(this, "Teacher's mode", "Are you sure you want to log out?", QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {

        /* Forum's code */
        QObject *p = this;
        do
        {
            p = p->parent();
            } while (p->parent() != nullptr);

        MainWindow *mw = qobject_cast<MainWindow *>(p);
        if (!mw)
        {
            // couldnt find main window
        }
        else
        {
            mw->show();
            hide();

            this->hide();
        }
    }
}

void MainWindow_teach::on_actionOpen_Database_triggered()
{
    /* Initializing variables */
    QString file_name = QFileDialog::getOpenFileName(this, "Open database", PATH_TO_DB);
    QByteArray arr = file_name.toLocal8Bit();


    /* Main part */
    if (db_open(PATH_TO_DB) != -1) {
        init_users();
    } else {
        QMessageBox::critical(this, "Error!", "Couldn't open database!");
    }
}

void MainWindow_teach::on_actionClose_Database_triggered()
{

    /* Main part */
    db_close();
    remove_users();
}

void MainWindow_teach::on_pushButton_add_clicked()
{

    /* Initializing variables */
    dialog1 = new Dialog1(this);

    /* Main part */
    dialog1->setModal(true);
    dialog1->AddStudent();
    dialog1->show();

    refresh_users();
}

void MainWindow_teach::init_users() {

    /* Initializing variables */
    int size;
    struct User *usr;
    struct Marks mks;
    double mean = 0.0;
    char fnln[515], id[10], a[10];
    QTableWidgetItem *itm = nullptr;

    /* Main part */
    usr = db_get_users(&size);
    for (int i = 0; i < size; ++i) {
        strcpy(fnln, "");
        sprintf(id, "%d", (usr + i)->id);
        strcat(fnln, id);
        strcat(fnln, ") ");
        strcat(fnln, (usr + i)->first_name);
        strcat(fnln, " ");
        strcat(fnln, (usr + i)->last_name);
        ui->comboBox->addItem(fnln);
    }

    ui->tableWidget->setRowCount(size);
    for (int i = 0; i < size; ++i) {
        mks = db_get_user_marks((usr + i)->id);
        ui->tableWidget->setItem(i, 0, (itm = new QTableWidgetItem((usr + i)->first_name)));
        itm->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(i, 1, (itm = new QTableWidgetItem((usr + i)->last_name)));
        itm->setTextAlignment(Qt::AlignCenter);

        sprintf(a, "%d", mks.values[0]);
        ui->tableWidget->setItem(i, 2, (itm = new QTableWidgetItem(a)));
        itm->setTextAlignment(Qt::AlignCenter);

        sprintf(a, "%d", mks.values[1]);
        ui->tableWidget->setItem(i, 3, (itm = new QTableWidgetItem(a)));
        itm->setTextAlignment(Qt::AlignCenter);

        sprintf(a, "%d", mks.values[2]);
        ui->tableWidget->setItem(i, 4, (itm = new QTableWidgetItem(a)));
        itm->setTextAlignment(Qt::AlignCenter);

        sprintf(a, "%d", mks.values[3]);
        ui->tableWidget->setItem(i, 5, (itm = new QTableWidgetItem(a)));
        itm->setTextAlignment(Qt::AlignCenter);

        sprintf(a, "%d", mks.values[4]);
        ui->tableWidget->setItem(i, 6, (itm = new QTableWidgetItem(a)));
        itm->setTextAlignment(Qt::AlignCenter);

        sprintf(a, "%d", mks.values[5]);
        ui->tableWidget->setItem(i, 7, (itm = new QTableWidgetItem(a)));
        itm->setTextAlignment(Qt::AlignCenter);

        sprintf(a, "%d", mks.values[6]);
        ui->tableWidget->setItem(i, 8, (itm = new QTableWidgetItem(a)));
        itm->setTextAlignment(Qt::AlignCenter);

        sprintf(a, "%d", mks.values[7]);
        ui->tableWidget->setItem(i, 9, (itm = new QTableWidgetItem(a)));
        itm->setTextAlignment(Qt::AlignCenter);

        sprintf(a, "%d", mks.values[9]);
        ui->tableWidget->setItem(i, 10, (itm = new QTableWidgetItem(a)));
        itm->setTextAlignment(Qt::AlignCenter);

        mean = get_mean(i + 1);
        sprintf(a, "%6.3lf", mean);
        ui->tableWidget->setItem(i, 11, (itm = new QTableWidgetItem(a)));
        itm->setTextAlignment(Qt::AlignCenter);
    }

    delete usr;
    ui->pushButton_add->setEnabled(true);
}

void MainWindow_teach::remove_users() {

    /* Main part */
    ui->comboBox->setCurrentIndex(0);
    ui->comboBox->clear();
    ui->comboBox->addItem("Choose a student...");
    ui->pushButton_add->setEnabled(false);

    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setRowCount(1);
}

void MainWindow_teach::refresh_users() {

    /* Main part */
    remove_users();
    init_users();
}

void MainWindow_teach::on_pushButton_rm_clicked()
{

    /* Initializing variables */
    int id;
    QMessageBox::StandardButton reply;

    /* Main part */
    id = get_student_id(ui->comboBox->currentIndex());
    reply = QMessageBox::question(this, "Teacher's mode", "Are you sure you want to delete this student?",
                                  QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        if (db_delete_user(id) != -1) {
            refresh_users();
        } else {
            QMessageBox::critical(this, "Error!", "Couldn't delete this student!");
        }
    }
}

int MainWindow_teach::get_student_id(int index) {

    /* Initializing variables */
    int id;
    QString Qstr;
    QByteArray arr;
    char id_s[10] = {};

    /* Main part */
    Qstr = ui->comboBox->itemText(index);
    arr = Qstr.toLocal8Bit();
    sprintf(id_s, "%s", arr.data());
    *(id_s + strlen(id_s) - 1) = '\0';
    id = atoi(id_s);

    /* Returning value */
    return id;
}
void MainWindow_teach::on_pushButton_2_clicked()
{

    /* Initializing variables */
    int id = -1, score;
    QByteArray arr;
    double mean = 0.0;
    char a[10];

    /* Main part */
    id = get_student_id(ui->comboBox->currentIndex());

    arr = ui->lineLoops->text().toLocal8Bit();
    score = atoi(arr.data());
    if (db_set_mark(id, 0, score) == -1) {
        QMessageBox::critical(this, "Error!", "Couldn't update student's mark!");
        return;
    }

    arr = ui->lineArrays->text().toLocal8Bit();
    score = atoi(arr.data());
    if (db_set_mark(id, 1, score) == -1) {
        QMessageBox::critical(this, "Error!", "Couldn't update student's mark!");
        return;
    }

    arr = ui->lineStrings->text().toLocal8Bit();
    score = atoi(arr.data());
    if (db_set_mark(id, 2, score) == -1) {
        QMessageBox::critical(this, "Error!", "Couldn't update student's mark!");
        return;
    }

    arr = ui->lineRecursion->text().toLocal8Bit();
    score = atoi(arr.data());
    if (db_set_mark(id, 3, score) == -1) {
        QMessageBox::critical(this, "Error!", "Couldn't update student's mark!");
        return;
    }

    arr = ui->lineStructures->text().toLocal8Bit();
    score = atoi(arr.data());
    if (db_set_mark(id, 4, score) == -1) {
        QMessageBox::critical(this, "Error!", "Couldn't update student's mark!");
        return;
    }

    arr = ui->lineFiles->text().toLocal8Bit();
    score = atoi(arr.data());
    if (db_set_mark(id, 5, score) == -1) {
        QMessageBox::critical(this, "Error!", "Couldn't update student's mark!");
        return;
    }

    arr = ui->linePointers->text().toLocal8Bit();
    score = atoi(arr.data());
    if (db_set_mark(id, 6, score) == -1) {
        QMessageBox::critical(this, "Error!", "Couldn't update student's mark!");
        return;
    }

    arr = ui->lineDyn_Mem->text().toLocal8Bit();
    score = atoi(arr.data());
    if (db_set_mark(id, 7, score) == -1) {
        QMessageBox::critical(this, "Error!", "Couldn't update student's mark!");
        return;
    }

    arr = ui->lineFinal->text().toLocal8Bit();
    score = atoi(arr.data());
    if (db_set_mark(id, 9, score) == -1) {
        QMessageBox::critical(this, "Error!", "Couldn't update student's mark!");
        return;
    }

    mean = get_mean(id);
    sprintf(a, "6.3%lf", mean);
    ui->lineMean->setText(a);
}

void MainWindow_teach::on_pushButton_clicked()
{

    /* Initializing variables */
    int id = -1;
    double mean = 0.0;
    char a[10];

    /* Main part */
    id = get_student_id(ui->comboBox->currentIndex());

    if (db_set_mark(id, 0, 0) == -1) {
        QMessageBox::critical(this, "Error!", "Couldn't update student's mark!");
        return;
    } else {
        ui->lineLoops->setText("0");
    }

    if (db_set_mark(id, 1, 0) == -1) {
        QMessageBox::critical(this, "Error!", "Couldn't update student's mark!");
        return;
    } else {
        ui->lineArrays->setText("0");
    }

    if (db_set_mark(id, 2, 0) == -1) {
        QMessageBox::critical(this, "Error!", "Couldn't update student's mark!");
        return;
    } else {
        ui->lineStrings->setText("0");
    }

    if (db_set_mark(id, 3, 0) == -1) {
        QMessageBox::critical(this, "Error!", "Couldn't update student's mark!");
        return;
    } else {
        ui->lineRecursion->setText("0");
    }

    if (db_set_mark(id, 4, 0) == -1) {
        QMessageBox::critical(this, "Error!", "Couldn't update student's mark!");
        return;
    } else {
        ui->lineStructures->setText("0");
    }

    if (db_set_mark(id, 5, 0) == -1) {
        QMessageBox::critical(this, "Error!", "Couldn't update student's mark!");
        return;
    } else {
        ui->lineFiles->setText("0");
    }

    if (db_set_mark(id, 6, 0) == -1) {
        QMessageBox::critical(this, "Error!", "Couldn't update student's mark!");
        return;
    } else {
        ui->linePointers->setText("0");
    }

    if (db_set_mark(id, 7, 0) == -1) {
        QMessageBox::critical(this, "Error!", "Couldn't update student's mark!");
        return;
    } else {
        ui->lineDyn_Mem->setText("0");
    }

    if (db_set_mark(id, 9, 0) == -1) {
        QMessageBox::critical(this, "Error!", "Couldn't update student's mark!");
        return;
    } else {
        ui->lineFinal->setText("0");
    }

    sprintf(a, "%6.3lf", mean);
    ui->lineMean->setText(a);
}

double MainWindow_teach::get_mean(int id) {

    /* Initializing variables */
    struct Marks mks;
    double mean = 0.0;

    /* Main part */
    mks = db_get_user_marks(id);
    for (int i = 0; i < 10; ++i) {
        if (i == 8) {
            continue;
        }
        mean += mks.values[i];
    }
    mean /= 9;

    /* Returning value */
    return mean;
}

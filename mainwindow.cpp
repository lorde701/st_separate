#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QFile>
#include <QDebug>
#include <QList>
#include <QMessageBox>
#include "QStandardItemModel"
#include "QStandardItem"

double *array;
int strSize, colSize;
QStringList colName;
QList<int> strNumbers;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->labelEps->hide();
    ui->label_3->hide();
    ui->label_4->hide();
    ui->lineEditEps->hide();
    ui->lineEditColNum->hide();
    ui->lineEditStep->hide();
    ui->label_5->hide();
    ui->lineEdit->hide();
}

void MainWindow::readFile(QString nameFileOpen)
    {
        QFile fileOpen(nameFileOpen); // создаем объект класса QFile
        /*QByteArray data;*/ // Создаем объект класса QByteArray, куда мы будем считывать данные
        if (!fileOpen.open(QIODevice::ReadOnly)) // Проверяем, возможно ли открыть наш файл для чтения
            return; // если это сделать невозможно, то завершаем функцию
       // data = fileOpen.readAll(); //считываем все данные с файла в объект data
       // qDebug() << QString(data); // Выводим данные в консоль, предварительно создав строку из полученных данных

        QList<QString>* list = new QList<QString>;
        QString line;
        while ( !fileOpen.atEnd() ) {

           line = QString(fileOpen.readLine(200));
           line.replace(QString("\r\n"), QString(""));
            //qDebug() << "Преобразованная строка без /р/н" << line;
           list->append(line);

        }
        QString lineStr;
        QStringList stringList, tempList;
        fileOpen.close();
        colSize = list->size(); //длина строки
        for ( int i = 0; i < colSize; i++ ) {
            lineStr = list->front();
           // qDebug() << "Первая строка - " << lineStr;
            tempList = lineStr.split(" ", QString::SkipEmptyParts);
            stringList.append(tempList);
           // qDebug() << "stringList - " << stringList.front();
            list->pop_front();

        }

        strSize = tempList.size();
       // qDebug() << "Длина строки = " << strSize << ". Длина столбца = " << colSize;
        bool ok;
        stringList.front().toDouble(& ok);
        if (ok) {
            /*double*/
            qDebug() << "по тру - дабл";
            array = new double [strSize*colSize];
            for (int i = 0; i < strSize*colSize; i++) {
                array[i] = stringList.front().toDouble();
                stringList.pop_front();

              /*  if (i % colSize != 0) {
                    qDebug() << array[i];
                } else {
                    qDebug() << "/n" << array[i];
                }*/
            }
        } else {
            /*string*/
           // qDebug() << "по фолс - стринг";
            array = new double [strSize*colSize-strSize];
            for (int i = 0; i < strSize; i++) {
                colName.append(QString(stringList.front()));
               // qDebug() << "Длина строки = " << strSize << "\ni = " << i << "\ncolName.append = " << colName.back() << "\nstringList.front = " << QString(stringList.front());

                stringList.pop_front();
            }
         //   qDebug() << "\n\n";
        //    qDebug() << "Количество элементов = " << strSize*colSize-strSize;
            for (int i = 0; i < strSize*colSize-strSize; i++) {
                array[i] = QString(stringList.front()).toDouble();
             //   qDebug() << "array[" << i << "] = "
                         //<< array[i];

                stringList.pop_front();
            }

        }

     //qDebug() << list->front();
    }

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString nameOpenFile = QFileDialog::getOpenFileName(0, "Открыть файл", "../Separate", "*.txt *.xls *.xlsx");
    ui->lineEditReadFile->setText(nameOpenFile);
    readFile(nameOpenFile);
/*
    QStandardItemModel *model = new QStandardItemModel;
    QStandardItem *item;




    if (!colName.isEmpty()) {
        int n = 0;
        QStringList tempColName = colName;
        ui->tableWidget->setRowCount(colSize);
        for (int i = 0; i < colSize; i++) {
            for (int j = 0; j < strSize; j++) {
                if (i == 0) {
                    item = new QTableWidgetItem(QString(tempColName.front()));
                    ui->tableWidget->setItem(i, j, item);
                    tempColName.pop_front();
                }
                else {
                    item = new QTableWidgetItem(QString::number(array[n++]));
                    ui->tableWidget->setItem(i, j, item);
                }

            }
        }
    }
    else {
        QTableWidgetItem *item;
        int n = 0;
        ui->tableWidget->setRowCount(colSize);
    for (int i = 0; i < colSize; i++) {
        for (int j = 0; j < strSize; j++) {
                item = new QTableWidgetItem(QString::number(array[n++]));
                ui->tableWidget->setItem(i, j, item);

            }

        }
    }




    */
        ui->tableWidget->setColumnCount(strSize);
        if (!colName.isEmpty()) {
            int n = 0;
            QStringList tempColName = colName;
            QTableWidgetItem *item;
            ui->tableWidget->setRowCount(colSize);
            for (int i = 0; i < colSize; i++) {
                for (int j = 0; j < strSize; j++) {
                    if (i == 0) {
                        item = new QTableWidgetItem(QString(tempColName.front()));
                        ui->tableWidget->setItem(i, j, item);
                        tempColName.pop_front();
                    }
                    else {
                        item = new QTableWidgetItem(QString::number(array[n++]));
                        ui->tableWidget->setItem(i, j, item);
                    }

                }
            }
        }
        else {
            QTableWidgetItem *item;
            int n = 0;
            ui->tableWidget->setRowCount(colSize);
        for (int i = 0; i < colSize; i++) {
            for (int j = 0; j < strSize; j++) {
                    item = new QTableWidgetItem(QString::number(array[n++]));
                    ui->tableWidget->setItem(i, j, item);

                }

            }
        }
        qDebug() << "strSize = " << strSize;
        qDebug() << "colSize = " << colSize;
}

void MainWindow::on_pushButton_2_clicked()
{
    close();
}

void MainWindow::on_radioButton_clicked()
{
    ui->labelEps->hide();
    ui->label_3->hide();
    ui->label_4->hide();
    ui->lineEditEps->hide();
    ui->lineEditColNum->hide();
    ui->lineEditStep->hide();
    ui->label_5->show();
    ui->lineEdit->show();
}

void MainWindow::on_radioButton_2_clicked()
{
    ui->labelEps->show();
    ui->label_3->show();
    ui->label_4->show();
    ui->lineEditEps->show();
    ui->lineEditColNum->show();
    ui->lineEditStep->show();
    ui->label_5->hide();
    ui->lineEdit->hide();
}

void MainWindow::on_lineEditEps_editingFinished()
{

    QString temp = ui->lineEditEps->text();
    if (!temp.isEmpty()) {
        bool ok;
        temp.toDouble(& ok);
            if (!ok) {
            QMessageBox::warning(this, tr("Предупреждение"),
                                       tr("Погрешность должна быть числом"),
                                       QMessageBox::Ok);
            ui->lineEditEps->setFocus();
        }
    }

}

void MainWindow::on_lineEditStep_editingFinished()
{

    QString temp = ui->lineEditStep->text();
    if (!temp.isEmpty()) {
        bool ok;
        temp.toInt(& ok, 10);
            if (!ok) {
            QMessageBox::warning(this, tr("Предупреждение"),
                                       tr("Шаг должен быть целым числом"),
                                       QMessageBox::Ok);
            ui->lineEditStep->setFocus();
        }
    }
}

void MainWindow::on_lineEditColNum_editingFinished()
{
    QString temp = ui->lineEditColNum->text();
    if (!temp.isEmpty()) {
        bool ok;
        temp.toInt(& ok, 10);
            if (!ok) {
            QMessageBox::warning(this, tr("Предупреждение"),
                                       tr("Номер столбца должен быть целым числом"),
                                       QMessageBox::Ok);
            ui->lineEditColNum->setFocus();
        }
    }
}

void MainWindow::on_lineEdit_editingFinished()
{
    bool ok;
    QString temp = ui->lineEdit->text();
    QStringList strList = temp.split(" ", QString::SkipEmptyParts);
    qDebug() << "temp = " << temp;
    /*
    while (! strList.isEmpty()) {
        qDebug() << strList.front().toInt(&ok, 10);
        int t = strList.front().toInt(&ok, 10);
        strList.pop_front();
         qDebug() << t;
    }
*/
      while (! strList.isEmpty()) {
      //  qDebug() << "зашел в while";
        int t = (strList.front()).toInt(&ok, 10);
        strList.pop_front();
        if ((ok) && (t > 0) && (t <=strSize)) {
          //  qDebug() << t;
            strNumbers.push_back(t);
           // qDebug() << "strList.front = " << t;
        }
        else
        {
           // qDebug() << "false";
            QMessageBox::warning(this, tr("Предупреждение"),
                                       tr("Номера столбцов должны быть положительными целыми числами, не больше количества столбцов"),
                                       QMessageBox::Ok);
            ui->lineEdit->setFocus();
            break;
        }
    }

}

void MainWindow::on_pushButtonSave_clicked() {
    QString nameSaveFile = QFileDialog::getSaveFileName(0, "Сохранить файл", "../Separate", "*.txt *.xls *.xlsx");
    ui->lineEditWriteFile->setText(nameSaveFile);
}

void MainWindow::on_pushButton_3_clicked() {

    QStandardItemModel *model = new QStandardItemModel;
    QStandardItem *item;



    //QTableWidgetItem *item;
    if (ui->radioButton->isChecked()) {
        //ui->tableWidget_2->setColumnCount(strSize - strNumbers.size());
        //ui->tableWidget_2->setRowCount(colSize);
        int k = 0;
        int elStrNumbers;
        QStringList horizontalHeader;
        int inp = 0;
        QStringList tempColName = colName;


        if (!colName.isEmpty()) {
        for (int i = 0; i < strSize; i++) {
            if(strNumbers[inp]-1 != i)
                horizontalHeader.append(QString(tempColName.front()));
            else
                if (inp != strNumbers.size()-1)
                            inp++;
            tempColName.pop_front();
        }
        }

        inp = 0;
            for (int j = 0; j < strSize; j++)  {
                elStrNumbers = strNumbers[k]-1;

                qDebug() << (elStrNumbers != j) << "\n" <<  elStrNumbers << " != " << j;
                if (elStrNumbers != j) {
                   int l = 0;
                    for ( int i = 0; i < colSize-1; i++) {
                            item = new QStandardItem(QString::number(array[j + l]));
                            l = l + strSize;
                            model->setItem(i, inp, item);
                           // ui->tableWidget_2->setItem(inp, i, item);
                    }
                    inp++;
                }
                else
                    if (k != strNumbers.size()-1)
                        k++;

            }
            model->setHorizontalHeaderLabels(horizontalHeader);
            ui->tableView_2->setModel(model);
    }

}













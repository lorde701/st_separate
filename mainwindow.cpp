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
QStringList strForFile;
int strSize, colSize;  // размер строки, размер столбца??
QStringList colName;
QStringList colNameTramsfArray;
QList<int> strNumbers;
QList<double> transformArray;
int amountColInTransformArray;
bool flag = false;

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

void MainWindow::fillTransformArray()
{
    transformArray.clear();
    flag = true;


    if (ui->radioButton_2->isChecked()) {

        int amount_col = strSize;
        int amount_str = colSize;
        int step = ui->lineEditStep->text().toInt();
        QString t = ui->lineEditEps->text();
        t.replace(",", ".");
        double eps = t.toDouble();
        int col_number = ui->lineEditColNum->text().toInt()-1;
        int num = 0;

        for ( int k = 0; k < strSize; k++ )
        {
            transformArray.append(array[0*strSize + k]);

        }
        num++;

        int ptr_tek_el = 0;
        int j = ptr_tek_el + 1;
        while ( j < amount_str ) {
            while ( (j < ptr_tek_el + step) && (j < amount_str) ) {
                double arr_ptr = array[ptr_tek_el*strSize + col_number]; //atof(arr[ptr_tek_el][col_number].c_str());
                double arr_tek = array[j*strSize + col_number]; //atof(arr[j][col_number].c_str());
                double temp = double((arr_ptr - arr_tek)/arr_ptr);
                temp = temp < 0 ? -temp : temp;
                if ( ((temp > eps) || (arr_ptr == 0)) && (ptr_tek_el + step < amount_str)) {
                    for ( int k = 0; k < amount_col; k++ ) {
                        transformArray.append(array[j*strSize + k]);
                    }
                    num++;
                    ptr_tek_el = j;
                    j = ptr_tek_el + 1;
                }
                else
                    j = j+1;
            }
            if ( ptr_tek_el + step < amount_str ) {
                for ( int k = 0; k < amount_col; k++ ) {
                    int dl = strSize*colSize - strSize;
                    int n = (ptr_tek_el+step)*strSize + k;
                    if (n < dl) {
                             transformArray.append(array[(ptr_tek_el+step)*strSize + k]);

                    }
                }
                num++;
                ptr_tek_el += step;
                j = ptr_tek_el + 1;
            }

        }
    }

    if (ui->radioButton->isChecked()) {
        QStringList tempColName = colName;
        colNameTramsfArray.clear();
        int n = 0;
        //strNumbers        номера столбцов для удаления
        if (!colName.isEmpty()) {
            n = 0;
           // QStringList horizontalHeader;
            for (int i = 0; i < strSize; i++) {
                if (strNumbers[n]-1 != i)
                    colNameTramsfArray.append(tempColName.front());
                else
                    if (n != strNumbers.size()-1)
                                n++;
                tempColName.pop_front();
            }
        }
        int ptr = 0;

        for (int j = 0; j < colSize-1; j++) {
            n = 0;
            for (int i = 0; i < strSize; i++) {
                if (strNumbers[n]-1 != i) {
                    transformArray.append(array[ptr]);
                }
                else {
                    if (n != strNumbers.size()-1) {
                        n++;
                    }

                }
                ptr++;

            }
        }
    }
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
        colSize = list->size(); //днила столбца
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
            array = new double [strSize*colSize - strSize]; //!!!!!!!!!!!!!!!!!!!!!!
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
    QString nameOpenFile = QFileDialog::getOpenFileName(0, "Открыть файл", "../MyPrograms/st_separate", "*.txt");
    ui->lineEditReadFile->setText(nameOpenFile);
    readFile(nameOpenFile);

    QStandardItemModel *model = new QStandardItemModel;
    QStandardItem *item;

    if (!colName.isEmpty()) {
        model->setHorizontalHeaderLabels(colName);
    }

    int n = 0;
    for (int i = 0; i < colSize-1; i++) {
        for (int j = 0; j < strSize; j++) {
            item = new QStandardItem(QString::number(array[n++]));
            model->setItem(i, j, item);
            }

        }

    ui->tableView->setModel(model);

    /*for (int i = 0; i < colSize - 1; i++ ) {
        for (int j = o; j < strSize; j++) {

        }
    }*/
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
    flag = false;
    QString temp = ui->lineEditEps->text();
    temp.replace("," , ".");
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
    flag = false;
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
    flag = false;
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
    flag = false;
    bool ok;
    strNumbers.clear();
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
      qSort(strNumbers.begin(), strNumbers.end());

}

void MainWindow::on_pushButtonSave_clicked() {
    QString nameSaveFile = QFileDialog::getSaveFileName(0, "Сохранить файл", "../MyPrograms/st_separate/tests", "*.txt");
    QFile saveFile (nameSaveFile);
    if (saveFile.open(QIODevice::WriteOnly)) {
      //  saveFile.write("fhbdklskjhbfdkj");
        if (flag == false) {
            fillTransformArray();
            flag = true;
        }
        QList<double> tempTransfArray = transformArray;
        QTextStream writeStream(&saveFile);
        if (ui->radioButton_2->isChecked()) {
            if (!colName.isEmpty()) {
                QStringList t = colName;
                while (!t.isEmpty()) {
                    writeStream << t.front();
                    QString tt = t.front();
                    int aa = tt.size();
                    for (int g = 0; g < 16 - aa; g++) {
                        writeStream << " ";
                    }
                    t.pop_front();
                }
                writeStream << endl;
            }
            while (!tempTransfArray.isEmpty()) {
                for (int i = 0; i < strSize; i++) {
                    writeStream << tempTransfArray.front();

                    for (int j = 0; j < 16 - QString::number(tempTransfArray.front()).size(); j++) {
                        writeStream << " ";
                    }
                    tempTransfArray.pop_front();
               }
                writeStream << endl;
            }
        }

        if (ui->radioButton->isChecked()) {
            if (!colNameTramsfArray.isEmpty()) {
                QStringList t = colNameTramsfArray;
                while (!t.isEmpty()) {
                    writeStream << t.front();
                    QString tt = t.front();
                    int aa = tt.size();
                   for ( int g = 0; g < 16 - aa; g++ ) {
                        writeStream << " ";
                    }
                    t.pop_front();
                }
                writeStream << endl;
            }

            while (!tempTransfArray.isEmpty()) {
                for ( int i = 0; i < strSize - strNumbers.size(); i++) {
                    writeStream << tempTransfArray.front();
                    for (int j = 0; j < 16 - QString::number(tempTransfArray.front()).size(); j++) {
                        writeStream << " ";
                    }
                    tempTransfArray.pop_front();
                }
                writeStream << endl;
            }
        }
    }
}

void MainWindow::on_pushButton_3_clicked() {


    QStandardItemModel *model = new QStandardItemModel;
    QStandardItem *item;
    ui->tableView_2->setModel(model);

   /* if (ui->radioButton->isChecked()) {
        int k = 0;
        int elStrNumbers;
        QStringList horizontalHeader;
        int inp = 0;


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
        // старый вариант
        inp = 0;
        for (int j = 0; j < strSize; j++)  {
            elStrNumbers = strNumbers[k]-1;

            if (elStrNumbers != j) {
               int l = 0;
                for ( int i = 0; i < colSize-1; i++) {
                        item = new QStandardItem(QString::number(array[j + l]));
                        l = l + strSize;
                        model->setItem(i, inp, item);
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


    */


    QList<double> tempTransfArray;



    if (ui->radioButton_2->isChecked()) {

        QString text1 = ui->lineEditEps->text();
        QString text2 = ui->lineEditStep->text();
        QString text3 = ui->lineEditColNum->text();
        if ((!text1.isEmpty()) && (!text2.isEmpty()) && (!text3.isEmpty())) {

            if (flag == false) {
                fillTransformArray();
            }

            tempTransfArray = transformArray;
            int j = 0;
            while (!tempTransfArray.isEmpty()) {
                for(int i = 0; i < strSize; i++) {
                    item = new QStandardItem(QString::number(tempTransfArray.front()));
                    model->setItem(j,i,item);
                    tempTransfArray.pop_front();
                }
                j++;
            }
            if(!colName.isEmpty()) {
                model->setHorizontalHeaderLabels(colName);
            }
            ui->tableView_2->setModel(model);

        }
        else {
            QMessageBox::warning(this, tr("Предупреждение"),
                                       tr("Не все поля заполнены!"),
                                       QMessageBox::Ok);
        }
    }


        
        
        if (ui->radioButton->isChecked()) {
            QString text = ui->lineEdit->text();
            //strNumbers        номера столбцов для удаления
            if (!text.isEmpty()) {

                if (flag == false) {
                    fillTransformArray();
                }

                tempTransfArray = transformArray;

                if (!colNameTramsfArray.isEmpty()) {
                    model->setHorizontalHeaderLabels(colNameTramsfArray);

                   // QStringList horizontalHeader;
                   // for (int i = 0; i < strSize; i++) {
                   //     if(strNumbers[inp]-1 != i)
                   //         horizontalHeader.append(QString(tempColName.front()));
                   //     else
                   //         if (inp != strNumbers.size()-1)
                   //                     inp++;
                   //     tempColName.pop_front();
                   //
                }

                int j = 0;
                while(!tempTransfArray.isEmpty()) {
                //for (int j = 0; j < colSize; j++) {
                    for (int i = 0; i < strSize-strNumbers.size(); i++) {
                        item = new QStandardItem(QString::number(tempTransfArray.front()));
                        model->setItem(j, i, item);
                        tempTransfArray.pop_front();
                    }
                    j++;
                }
                ui->tableView_2->setModel(model);
            }
            else {
                QMessageBox::warning(this, tr("Предупреждение"),
                                           tr("Не все поля заполнены!"),
                                           QMessageBox::Ok);
            }
        }


   /*  if (ui->radioButton_2->isChecked()) {

       flag = true;

        int amount_col = strSize;
        int amount_str = colSize;
        int step = ui->lineEditStep->text().toInt();
        double eps = ui->lineEditEps->text().toDouble();
        int col_number = ui->lineEditColNum->text().toInt()-1;
        int num = 0;

        QString tempStr;
        for ( int k = 0; k < amount_col; k++ )
        {
            item = new QStandardItem(QString::number(array[0*strSize + k]));
            model->setItem(num, k, item);
            //fin << setw(NUMBERS_WIDTH) << arr[0][k];
            //cout << setw(NUMBERS_WIDTH) << arr[0][k];
            tempStr = tempStr + QString::number(array[0*strSize + k]);
            for (int u = 0; u < 13 - (array[0*strSize + k])/1; u++ ) {
                tempStr = tempStr + ' ';
            }
        }
        strForFile.append(tempStr);
        strForFile.append("\n");
        num++;

        int ptr_tek_el = 0;
        int j = ptr_tek_el + 1;
        while ( j < amount_str ) {
            while ( (j < ptr_tek_el + step) && (j < amount_str) )
            {
                double arr_ptr = array[ptr_tek_el*strSize + col_number]; //atof(arr[ptr_tek_el][col_number].c_str());
                double arr_tek = array[j*strSize + col_number]; //atof(arr[j][col_number].c_str());

                double temp = double((arr_ptr - arr_tek)/arr_ptr);
                temp = temp < 0 ? -temp : temp;
                if ( ((temp > eps) || (arr_ptr == 0)) && (ptr_tek_el + step < amount_str))
                {
                    //QString tempStr;
                    for ( int k = 0; k < amount_col; k++ )
                    {
                        item = new QStandardItem(QString::number(array[j*strSize + k]));
                        //l = l + strSize;
                        model->setItem(num, k, item);

                        transformArray.append(array[j*strSize + k]);

                        tempStr = tempStr + QString::number(array[j*strSize + k]);
                        for (int u = 0; u < 13 - (array[j*strSize + k])/1; u++ ) {
                            tempStr = tempStr + ' ';
                        }
                        //fin << setw(NUMBERS_WIDTH) << arr[j][k];
                        //cout << setw(NUMBERS_WIDTH) << arr[j][k];
                    }
                    strForFile.append(tempStr);
                    strForFile.append("\n");
                    num++;
                    //fin << endl;
                    //cout << endl;
                    ptr_tek_el = j;
                    j = ptr_tek_el + 1;
                }
                else
                    j = j+1;
            }
           // QString tempStr;
            if ( ptr_tek_el + step < amount_str )
            {
                for ( int k = 0; k < amount_col; k++ ) {
                    int dl = strSize*colSize - strSize;
                    int n = (ptr_tek_el+step)*strSize + k;
                    if (n < dl) {
                            item = new QStandardItem(QString::number(array[(ptr_tek_el+step)*strSize + k]));
                             //l = l + strSize;
                            model->setItem(num, k, item);
                            //fin << setw(NUMBERS_WIDTH) << arr[ptr_tek_el + step][k];
                            //cout << setw(NUMBERS_WIDTH) << arr[ptr_tek_el + step][k];
                            tempStr = tempStr + QString::number(array[(ptr_tek_el+step)*strSize + k]);
                            for (int u = 0; u < 13 - array[(ptr_tek_el+step)*strSize + k]; u++ ) {
                                tempStr = tempStr + ' ';
                            }
                    }
                }
                 strForFile.append(tempStr);
                 strForFile.append("\n");

                num++;
                        //fin << endl;
                        //cout << endl;
                ptr_tek_el += step;
                j = ptr_tek_el + 1;
            }

        }
        model->setHorizontalHeaderLabels(colName);
        ui->tableView_2->setModel(model);
    }*/

}


void MainWindow::on_lineEditReadFile_textChanged(const QString &arg1)
{
    flag = false;

}



void MainWindow::on_lineEdit_textEdited(const QString &arg1)
{
    /*
    flag = false;


    QStandardItemModel *model = new QStandardItemModel; //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!&&&&&&&????
     QStandardItem *item = new QStandardItem ("Работает");
    model->setItem(0,0,item);
    model->setHorizontalHeaderLabels(QStringList(""));


    ui->tableView_2->setModel(model);

    QMessageBox::warning(this, tr("Предупреждение"),
                               tr("textEdited"),
                               QMessageBox::Ok);*/
}

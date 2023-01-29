#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Compression.h"
#include <string>
#include "convert.h"
#include "formatter.h"
#include "consistency.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("XML Editor");
    ui->textEdit->setPlaceholderText(QString("Write XML Here..."));
    setCentralWidget(ui->textEdit);
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_actionNew_triggered()
{
    currentFile.clear();
    ui->textEdit->clear();
    ui->textEdit->setPlaceholderText(QString("Write Your New XML here"));
}


void MainWindow::on_actionOpen_triggered()
{
    // Opens a dialog that allows you to select a file to open
        QString fileName = QFileDialog::getOpenFileName(this, "Choose a file");

        // An object for reading and writing files
        QFile file(fileName);

        // Store the currentFile name
        currentFile = fileName;

        // Try to open the file as a read only file if possible or display a
        // warning dialog box
        if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
            QMessageBox::warning(this, "Warning", "Cannot open file: " + file.errorString());
            return;
        }

        // Set the title for the window to the file name
        setWindowTitle(fileName);

        // Interface for reading text
        QTextStream in(&file);

        // Copy text in the string
        QString text = in.readAll();

        // Put the text in the textEdit widget
        ui->textEdit->setText(text);

        // Close the file
        file.close();
}



void MainWindow::on_actionSave_As_triggered()
{
    // Opens a dialog for saving a file
        QString fileName = QFileDialog::getSaveFileName(this, "Save as");

        // An object for reading and writing files
        QFile file(fileName);

        // Try to open a file with write only options
        if (!file.open(QFile::WriteOnly | QFile::Text)) {
            QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
            return;
        }

        // Store the currentFile name
        currentFile = fileName;

        // Set the title for the window to the file name
        setWindowTitle(fileName);

        // Interface for writing text
        QTextStream out(&file);

        // Copy text in the textEdit widget and convert to plain text
        QString text = ui->textEdit->toPlainText();

        // Output to file
        out << text;
        statusBar()->showMessage("file saved", 2000);

        // Close the file
        file.close();
}

void MainWindow::on_actionSave_triggered()
{
       QFile file(currentFile);
       if (!file.open(QFile::WriteOnly | QFile::Text)) {
           QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
           return;
       }
       QTextStream out(&file);
       out << ui->textEdit->toPlainText();
       statusBar()->showMessage("file saved", 2000);
}
void MainWindow::on_actionExit_triggered()
{
    QApplication:: quit();
}






void MainWindow::on_actionCompress_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Compress");
    std::compress_file(fileName.toStdString());
}


void MainWindow::on_actionDecompress_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Decompress");
    std::decompress_file(fileName.toStdString());
}


void MainWindow::on_actionConvert_to_JSON_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Compress");
    std::string file_content = std::readFileBytes(fileName.toStdString());
    Node* xml_tree = Parse_XML(file_content);
    ui->textEdit->setText(QString::fromStdString(convert_json(xml_tree)));

}


void MainWindow::on_actionFormat_triggered()
{
    if(currentFile == ""){
        // Opens a dialog that allows you to select a file to open
            QString fileName = QFileDialog::getOpenFileName(this, "Choose a file");

            // An object for reading and writing files
            QFile file(fileName);

            // Store the currentFile name
            currentFile = fileName;

            // Try to open the file as a read only file if possible or display a
            // warning dialog box
            if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
                QMessageBox::warning(this, "Warning", "Cannot open file: " + file.errorString());
                return;
            }

            // Set the title for the window to the file name
            setWindowTitle(fileName);

            // Interface for reading text
            QTextStream in(&file);

            // Copy text in the string
            QString text = in.readAll();

            QByteArray array = currentFile.toLocal8Bit();
                const char *buffer = array.data();
                QString textf = QString::fromStdString(xml_formatter(buffer));
                ui->textEdit->setText(textf);

            // Close the file
            file.close();
    }
        QByteArray array = currentFile.toLocal8Bit();
            const char *buffer = array.data();
            QString text = QString::fromStdString(xml_formatter(buffer));
            ui->textEdit->setText(text);
}


void MainWindow::on_actionCheck_triggered()
{
    if(currentFile == ""){
        ui->textEdit->setText("<font color=\"#0008F0\"> Error: <font color=\"#000000\"> You have not opened a file");
    }
    bool read;
    string folder = currentFile.toLocal8Bit().constData();
    vector<string> str = fileReader(&read, folder);
    vector<QString> value = consistencyCheckCorrect(str);
    QFile file("sample_corrected.xml");
    if(!file.open(QIODevice::ReadOnly | QFile::Text)){
        QMessageBox::warning(this, "Warning", "Cannot open file : " + file.errorString());
        return;
    }
    QTextStream in(&file);
    QString text = in.readAll();
    if(value[0].size() == 0)
        ui->textEdit->setText("<font color=\"#0008F0\"> Error: <font color=\"#000000\"> There were no errors to be corrected");
    else
        ui->textEdit->setText(value[1]);

}


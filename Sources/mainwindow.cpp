#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <string>
#include "FileHandler.h"
#include "XmlEditor.h"
#include "SocialNetwork.h"
#include "tree.h"

XmlEditor xmlEditor;
SocialNetwork socialNetwork;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("XML Editor");
    ui->textEdit->setPlaceholderText(QString("Write XML Here..."));
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
        string str = FileHandler::readFileBytes(fileName.toStdString());

        // Copy text in the string
            QString text = QString::fromStdString(str);
            xmlEditor = *new XmlEditor( text.toStdString());
            xmlEditor.Xml_parse();
            Node* tree = xmlEditor.get_tree();
            socialNetwork = *new SocialNetwork(tree);
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
        FileHandler::writeFileBytes(fileName.toStdString(), ui->textEdit->toPlainText().toStdString());
        // Output to filex\\\\\\\\\\\\\\\\\\\
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
       FileHandler::writeFileBytes(currentFile.toStdString(), ui->textEdit->toPlainText().toStdString());
       //out << ui->textEdit->toPlainText();
       statusBar()->showMessage("file saved", 2000);
}
void MainWindow::on_actionExit_triggered()
{
    QApplication:: quit();
}






void MainWindow::on_actionCompress_triggered()
{
if(    checkUiText("Compress")) return;
    xmlEditor.compress();
    ui->textEdit->setText(QString::fromStdString(xmlEditor.get_current_text()));
}


void MainWindow::on_actionDecompress_triggered()
{
if(    checkUiText("Decompress")) return;
    xmlEditor.decompress();
    ui->textEdit->setText(QString::fromStdString(xmlEditor.get_current_text()));
}


void MainWindow::on_actionConvert_to_JSON_triggered()
{
if(    checkUiText("Convert Json")) return;
    xmlEditor.convert_json();
    ui->textEdit->setText(QString::fromStdString(xmlEditor.get_current_text()));
}


void MainWindow::on_actionFormat_triggered()
{
if(    checkUiText("prettify")) return;
    xmlEditor.prettify();
    ui->textEdit->setText(QString::fromStdString(xmlEditor.get_current_text()));

}


void MainWindow::on_actionCheck_triggered()
{
if(    checkUiText("Validate")) return;
    xmlEditor.validate();
    ui->textEdit->setText(QString::fromStdString(xmlEditor.get_current_text()));
    ui->Display->setText(QString::fromStdString(xmlEditor.get_errors()));

}


void MainWindow::on_actionMinify_triggered()
{
if(    checkUiText("Minify")) return;
    xmlEditor.minify();
    ui->textEdit->setText(QString::fromStdString(xmlEditor.get_current_text()));

}


bool MainWindow::checkUiText(std::string msg)
 {

    std::string xml_text = ui->textEdit->toPlainText().toStdString();
        if (xml_text =="") {

            QString fileName = QFileDialog::getOpenFileName(this, QString::fromStdString(msg));
            QFile file(fileName);

            if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
                QMessageBox::warning(this, "Warning", "Cannot open file: " + file.errorString());
                return true;
            }

            std::string file_content = FileHandler::readFileBytes(fileName.toStdString());

            xmlEditor = *new XmlEditor(file_content);

            ui->textEdit->setText(QString::fromStdString(file_content));

        }
        else if(xmlEditor.get_current_text().compare(xml_text) != 0){
                xmlEditor.set_current_text(xml_text);
           }
        try{
        xmlEditor.Xml_parse();

        Node* tree = xmlEditor.get_tree();
        socialNetwork = *new SocialNetwork(tree);

        }
        catch(invalid_argument& e){
                ui->Display->setText("<font color=\"#ff0000\"> Error: <font color=\"#000000\"> Not a valid XML file");

        }
return false;
}








void MainWindow::on_pushButton_clicked()
{
if(    checkUiText("Search")) return;

    string str = ui->SearchText->text().toStdString();
    string output = socialNetwork.search_posts(str);
    ui->Display->setText(QString::fromStdString(output));

}


void MainWindow::on_moastActiveUserButton_clicked()
{
    if(checkUiText("Most Active User")) return;

    ui->Display->setText(QString::fromStdString(socialNetwork.getMostActiveUser()));
}


void MainWindow::on_mostInfUserButton_clicked()
{
if(    checkUiText("Most Influential User")) return;

    ui->Display->setText(QString::fromStdString(socialNetwork.getMostInfluencerUser()));
}


void MainWindow::on_resetButton_clicked()
{
    xmlEditor = *new XmlEditor(xmlEditor.get_original_text());
    ui->textEdit->setText(QString::fromStdString(xmlEditor.get_original_text()));
    ui->Display->clear();

}


void MainWindow::on_mutualFollwersButton_clicked()
{

if(    checkUiText("Mutual Followers")) return;

    string user1 = ui->mfText1->text().toStdString();
    string user2 = ui->mfText2->text().toStdString();
    try {
        if(ui->IDradioButton->isChecked()){
            int user1_id = stoi(user1);
            int user2_id = stoi(user2);
            ui->Display->setText(QString::fromStdString(socialNetwork.mutual_followers(user1_id, user2_id)));

        }
        else
            ui->Display->setText(QString::fromStdString(socialNetwork.mutual_followers(user1, user2)));
    }  catch (...) {
        ui->Display->setText("<font color=\"#ff0000\"> Error: <font color=\"#000000\"> Not Valid ID");
    }


}



void MainWindow::on_sf_clicked()
{
if(    checkUiText("Suggested Followers")) return;
    string user1 = ui->SuggestoinText->text().toStdString();
    try{
   if(ui->IDradioButton->isChecked()){
       int user1_id = stoi(user1);
       ui->Display->setText(QString::fromStdString(socialNetwork.suggested_followers(user1_id)));
   }
   else
       ui->Display->setText(QString::fromStdString(socialNetwork.suggested_followers(user1)));
    }
   catch (...) {
           ui->Display->setText("<font color=\"#ff0000\"> Error: <font color=\"#000000\"> Not Valid ID");
       }
}

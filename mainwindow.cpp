#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "parser.h"
#include "scanner.h"

MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow){
    ui->setupUi(this);
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::on_pushButton_clicked(){
    std::string source = ui->lineEdit->text().toStdString();

    try{
        std::vector<Token> token_stream = Scanner::getTokenStream(source);
        AstNode* root = Parser::parse(token_stream, source);
        ui->lineEdit->setText(QString::number(root->evaluate()).replace("e","*10^"));
        delete root;
    }catch(...){
        ui->lineEdit->setText("err");
    }
}

void MainWindow::on_lineEdit_returnPressed(){
    on_pushButton_clicked();
}

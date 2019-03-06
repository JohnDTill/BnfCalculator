#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "parser.h"
#include "scanner.h"

MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow){
    ui->setupUi(this);

    error_status_bar = ui->statusBar;
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::on_pushButton_clicked(){
    ui->statusBar->clearMessage();

    std::string source = ui->lineEdit->text().toStdString();

    try{
        std::vector<Token> token_stream = Scanner::getTokenStream(source);
        AstNode* root = Parser::parse(token_stream, source);
        if(ui->radioDouble->isChecked()){
            ui->lineEdit->setText(QString::number(root->evaluate()).replace("e","*10^").replace("+",""));
        }else{
            root = root->simplify();
            ui->lineEdit->setText(QString::fromStdString(root->toString()));
        }
        root->deleteChildren();
        delete root;
    }catch(...){
        ui->lineEdit->setText("err");
    }
}

void MainWindow::on_lineEdit_returnPressed(){
    on_pushButton_clicked();
}

#include "janelaPrincipal.h"
#include "ui_janelaPrincipal.h"

janelaPrincipal::janelaPrincipal(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::janelaPrincipal),
    controle(new UsuarioControle)
{
    ui->setupUi(this);
}

janelaPrincipal::~janelaPrincipal()
{
    delete controle;
    delete ui;
}

void janelaPrincipal::on_pushButton_PersistirUsuario_clicked()
{
    try
    {
        Usuario novo(ui->lineEdit_Nome->text(),ui->lineEdit_Cpf->text(),
                     ui->lineEdit_Senha->text(),ui->lineEdit_Email->text(),
                     ui->lineEdit_Telefone->text());
        this->controle->salvar(novo);
    } catch (QString &erro) { QMessageBox::information(this,"ERRO",erro);}
}

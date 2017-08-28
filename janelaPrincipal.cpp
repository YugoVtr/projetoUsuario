#include "janelaPrincipal.h"
#include "ui_janelaPrincipal.h"

janelaPrincipal::janelaPrincipal(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::janelaPrincipal),
    controle(new UsuarioControle)
{
    ui->setupUi(this);
    try{
        ui->pushButtonCancelar->setVisible(false);
        this->listagem();
    }catch(QString &erro){
        QMessageBox::critical(this,"Erro",erro);
    }
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
        if(ui->pushButtonCancelar->isVisible())
        {
            this->controle->alterar(novo);
            QMessageBox::about(this,"Alterado","Alterado com sucesso");
            ui->pushButtonCancelar->setVisible(false);
            ui->lineEdit_Cpf->setReadOnly(false);
            ui->pushButton_PersistirUsuario->setText("Salvar");
        }
        else
        {
            this->controle->salvar(novo);
            QMessageBox::about(this,"Salvo","Salvo com sucesso");
        }

        this->limparCampos();
        this->listagem();
    } catch (QString &erro) { QMessageBox::information(this,"ERRO",erro);}
}

void janelaPrincipal::listagem()
{
    try{
        std::queue<Usuario> *fila = controle->listar();
        limparGrid();
        while(!fila->empty())
        {
            Usuario atual = fila->front();

            QIcon iconeExcluir(":/Imagens/delete.png");

            // setando itens na grid
            ui->tableWidget_Listagem->setRowCount(ui->tableWidget_Listagem->rowCount()+1);
            ui->tableWidget_Listagem->setItem(
                        ui->tableWidget_Listagem->rowCount()-1,0,new QTableWidgetItem(atual.getNome()));
            ui->tableWidget_Listagem->setItem(
                        ui->tableWidget_Listagem->rowCount()-1,1,new QTableWidgetItem(atual.getCpf()));
            ui->tableWidget_Listagem->setItem(
                        ui->tableWidget_Listagem->rowCount()-1,2,new QTableWidgetItem(atual.getEmail()));
            ui->tableWidget_Listagem->setItem(
                        ui->tableWidget_Listagem->rowCount()-1,3,new QTableWidgetItem(atual.getTelefone()));
            ui->tableWidget_Listagem->setItem(
                        ui->tableWidget_Listagem->rowCount()-1,4,new QTableWidgetItem(iconeExcluir,""));
            fila->pop();
        }
        ui->tableWidget_Listagem->resizeColumnsToContents();
        ui->tableWidget_Listagem->horizontalHeader()->setSectionResizeMode(4,QHeaderView::Stretch);
    } catch(QString &erro) {
        throw QString(erro);
    }
}

void janelaPrincipal::limparGrid()
{
    for(int i=0;i<ui->tableWidget_Listagem->rowCount();i++)
    {
        for(int j=0;j<ui->tableWidget_Listagem->columnCount();j++)
        {
            if(ui->tableWidget_Listagem->itemAt(i,j))
                delete ui->tableWidget_Listagem->itemAt(i,j);
        }
    }
    ui->tableWidget_Listagem->setRowCount(0);
}

void janelaPrincipal::limparCampos()
{
    ui->lineEdit_Cpf->clear();
    ui->lineEdit_Email->clear();
    ui->lineEdit_Nome->clear();
    ui->lineEdit_Senha->clear();
    ui->lineEdit_Telefone->clear();
}

void janelaPrincipal::excluirUsuario(QString &cpf)
{
    Usuario excluir;
    excluir.setCpf(cpf);
    this->controle->excluir(excluir);
}

void janelaPrincipal::popularCampos(Usuario usuario)
{
    ui->lineEdit_Cpf->setText(usuario.getCpf());
    ui->lineEdit_Email->setText(usuario.getEmail());
    ui->lineEdit_Nome->setText(usuario.getNome());
    ui->lineEdit_Senha->setText(usuario.getSenha());
    ui->lineEdit_Telefone->setText(usuario.getTelefone());

    ui->lineEdit_Cpf->setReadOnly(true);
    ui->pushButtonCancelar->setVisible(true);
    ui->pushButton_PersistirUsuario->setText("Alterar");
}

void janelaPrincipal::on_tableWidget_Listagem_cellClicked(int row, int column)
{
    if(column == ui->tableWidget_Listagem->columnCount()-1)
    {
        QString cpf = ui->tableWidget_Listagem->item(row,1)->text();
        if(QMessageBox::question(this,"Excluir","Deseja excluir o cpf "+cpf+" ?") == QMessageBox::Yes)
        {
            this->excluirUsuario(cpf);
            this->listagem();
        }
    }
}

void janelaPrincipal::on_tableWidget_Listagem_cellDoubleClicked(int row, int column)
{
    if(column != ui->tableWidget_Listagem->columnCount()-1)
    {
        QString cpf = ui->tableWidget_Listagem->item(row,1)->text();
        Usuario usuario = this->controle->buscarUsuario(cpf);
        this->popularCampos(usuario);
    }
}

void janelaPrincipal::on_pushButtonCancelar_clicked()
{
    try{
        ui->pushButtonCancelar->setVisible(false);
        ui->pushButton_PersistirUsuario->setText("Salvar");
        this->limparCampos();
    }catch(QString &erro){
        QMessageBox::about(this,"Erro",erro);
    }
}

#include "janelaPrincipal.h"
#include "ui_janelaPrincipal.h"

janelaPrincipal::janelaPrincipal(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::janelaPrincipal),
    controle(0)
{
    ui->setupUi(this); 

    //Permite a digitação apenas de numeros para CPF e Telefone
    ui->lineEdit_Cpf->setValidator(new QRegExpValidator(QRegExp("[0-9]*"),ui->lineEdit_Cpf));
    ui->lineEdit_Telefone->setValidator(new QRegExpValidator(QRegExp("[0-9]*"),ui->lineEdit_Telefone));

    try{
        //Instancia o controle
        controle = new UsuarioControle;
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
        //Monta o objeto Usuario com os Dados da Window
        Usuario novo(ui->lineEdit_Nome->text(),ui->lineEdit_Cpf->text(),
                     ui->lineEdit_Senha->text(),ui->lineEdit_Email->text(),
                     ui->lineEdit_Telefone->text());

        //Altera
        if(ui->pushButtonCancelar->isVisible())
        {
            this->controle->alterar(novo);
            QMessageBox::about(this,"Alterado","Alterado com sucesso");
            ui->pushButtonCancelar->setVisible(false);
            ui->lineEdit_Cpf->setReadOnly(false);
            ui->lineEdit_Senha->setReadOnly(false);
            ui->pushButton_PersistirUsuario->setText("Salvar");
            ui->pushButton_PersistirUsuario->setToolTip("Salvar");
            ui->pushButton_PersistirUsuario->setIcon(QIcon(Configuracao::getImagem_Salvar()));
        }//Salva
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
        //Exibe a listagem dos Usuarios na Grid
        std::queue<Usuario> *fila = controle->listar();
        limparGrid();
        while(!fila->empty())
        {
            Usuario atual = fila->front();

            // Setando itens na grid
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
                        ui->tableWidget_Listagem->rowCount()-1,4,new QTableWidgetItem(QIcon(Configuracao::getImagem_Delete()),""));
            fila->pop();
        }
        ui->tableWidget_Listagem->resizeColumnsToContents();
        ui->tableWidget_Listagem->horizontalHeader()->setSectionResizeMode(4,QHeaderView::Stretch);
        ui->tableWidget_Listagem->setColumnWidth(4,50);
    } catch(QString &erro) {
        throw QString(erro);
    }
}

void janelaPrincipal::limparGrid()
{
    //Limpa a gride, deletando os intens criados
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
    //Limpa dos campos da window
    ui->lineEdit_Cpf->setReadOnly(false);
    ui->lineEdit_Cpf->clear();
    ui->lineEdit_Email->clear();
    ui->lineEdit_Nome->clear();
    ui->lineEdit_Senha->clear();
    ui->lineEdit_Senha->setReadOnly(false);
    ui->lineEdit_Telefone->clear();
}

void janelaPrincipal::excluirUsuario(QString &cpf)
{
    //Excluir um Usuario da base de dados
    Usuario excluir;
    excluir.setCpf(cpf);
    this->controle->excluir(excluir);
    this->limparCampos();
}

void janelaPrincipal::popularCampos(Usuario usuario)
{
    //Popula os campos da window com os dados de um Usuario informado.
    ui->lineEdit_Cpf->setText(usuario.getCpf());
    ui->lineEdit_Email->setText(usuario.getEmail());
    ui->lineEdit_Nome->setText(usuario.getNome());
    ui->lineEdit_Telefone->setText(usuario.getTelefone());

    ui->lineEdit_Senha->clear();
    ui->lineEdit_Senha->setReadOnly(true);
    ui->lineEdit_Cpf->setReadOnly(true);
    ui->pushButtonCancelar->setVisible(true);
    ui->pushButton_PersistirUsuario->setToolTip("Alterar");
    ui->pushButton_PersistirUsuario->setIcon(QIcon(Configuracao::getImagem_Alterar()));
}

void janelaPrincipal::on_tableWidget_Listagem_cellClicked(int row, int column)
{
    //Identifica o Usuario a ser Excluido
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
    //Inicia a alteração de um Usuario clicado
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
        //Cancela a alteração de um Usuario
        ui->pushButtonCancelar->setVisible(false);
        ui->pushButton_PersistirUsuario->setIcon(QIcon(Configuracao::getImagem_Salvar()));
        this->limparCampos();
    }catch(QString &erro){
        QMessageBox::about(this,"Erro",erro);
    }
}

#ifndef JANELAPRINCIPAL_H
#define JANELAPRINCIPAL_H

#include <QMainWindow>
#include <QMessageBox>
#include <QCryptographicHash>
#include <QValidator>
#include "UsuarioControle.h"

namespace Ui {
class janelaPrincipal;
}

class janelaPrincipal : public QMainWindow
{
    Q_OBJECT

public:
    explicit janelaPrincipal(QWidget *parent = 0);
    ~janelaPrincipal();

private slots:
    void on_pushButton_PersistirUsuario_clicked();
    void listagem();
    void limparGrid();
    void limparCampos();
    void excluirUsuario(QString &cpf);
    void popularCampos(Usuario usuario);

    void on_tableWidget_Listagem_cellClicked(int row, int column);

    void on_tableWidget_Listagem_cellDoubleClicked(int row, int column);

    void on_pushButtonCancelar_clicked();

private:
    Ui::janelaPrincipal *ui;
    UsuarioControle *controle;
};

#endif // JANELAPRINCIPAL_H

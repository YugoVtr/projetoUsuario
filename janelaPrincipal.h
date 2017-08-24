#ifndef JANELAPRINCIPAL_H
#define JANELAPRINCIPAL_H

#include <QMainWindow>
#include <QMessageBox>
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

private:
    Ui::janelaPrincipal *ui;
    UsuarioControle *controle;
};

#endif // JANELAPRINCIPAL_H

#ifndef USUARIOPERSISTENCIA_H
#define USUARIOPERSISTENCIA_H

#include "CRUD.h"
#include <QString>
#include <QStringList>
#include "Usuario.h"
#include "Configuracao.h"
#include <queue>
#include <QtSql/QtSql>

namespace PBD {
    class UsuarioPersistencia;
}

//Classe de Persistencia - Implementa a CRUD
class UsuarioPersistencia : public CRUD<Usuario>
{
public:
    UsuarioPersistencia();
    ~UsuarioPersistencia();
    void salvar(Usuario &obj);
    void alterar(Usuario &obj);
    void excluir(Usuario &obj);
    Usuario buscarUsuario(const QString &cpf);
    std::queue<Usuario> *listar();

private:
    //Atributo que representa a conexão com o banco.
    QSqlDatabase banco;
};

#endif // USUARIOPERSISTENCIA_H

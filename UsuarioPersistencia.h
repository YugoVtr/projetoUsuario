#ifndef USUARIOPERSISTENCIA_H
#define USUARIOPERSISTENCIA_H

#include "CRUD.h"
#include <QString>
#include <QStringList>
#include "Usuario.h"
#include <queue>
#include <QtSql/QtSql>

namespace PBD {
    class UsuarioPersistencia;
}

class UsuarioPersistencia : public CRUD<Usuario>
{
public:
    UsuarioPersistencia();
    ~UsuarioPersistencia();
    void salvar(const Usuario &obj);
    void alterar(const Usuario &obj);
    void excluir(const Usuario &obj);
    Usuario buscarUsuario(const QString &cpf);
    std::queue<Usuario> *listar();

private:
    QSqlDatabase banco;
};

#endif // USUARIOPERSISTENCIA_H

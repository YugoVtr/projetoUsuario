#ifndef CRUD_H
#define CRUD_H
#include <queue>
#include <QString>
#include <QStringList>
#include "Usuario.h"

namespace PBD {
    class CRUD;
}
class CRUD
{
public:
    ~CRUD(){}
    virtual void salvar(const Usuario &usuario) = 0;
    virtual void alterar(const Usuario &usuario) = 0;
    virtual void excluir(const Usuario &usuario) = 0;
    virtual std::queue<Usuario>* listar() = 0;
};

#endif // CRUD_H

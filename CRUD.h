#ifndef CRUD_H
#define CRUD_H

#include <iterator>
#include <queue>

namespace PBD {
    class CRUD;
}

//Interface para classes de Persistencia
template <class Tipo>
class CRUD
{
public:
    virtual void salvar(Tipo &obj) = 0;
    virtual void alterar(Tipo &obj) = 0;
    virtual void excluir(Tipo &obj) = 0;
    virtual std::queue<Tipo>* listar() = 0;

};

#endif // CRUD_H

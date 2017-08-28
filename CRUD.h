#ifndef CRUD_H
#define CRUD_H

#include <iterator>
#include <queue>

namespace PBD {
    class CRUD;
}

template <class Tipo>
class CRUD
{
public:
    virtual void salvar(const Tipo &obj) = 0;
    virtual void alterar(const Tipo &obj) = 0;
    virtual void excluir(const Tipo &obj) = 0;
    virtual std::queue<Tipo>* listar() = 0;

};

#endif // CRUD_H

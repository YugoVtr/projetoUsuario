#ifndef USUARIOPERSISTENCIA_H
#define USUARIOPERSISTENCIA_H
#include "CRUD.h"

namespace PBD {
    class UsuarioPersistencia;
}
class UsuarioPersistencia : public CRUD
{
public:
    UsuarioPersistencia();
    void salvar(const Usuario &usuario);
    void alterar(const Usuario &usuario);
    void excluir(const Usuario &usuario);
    std::queue<Usuario>* listar();
};

#endif // USUARIOPERSISTENCIA_H

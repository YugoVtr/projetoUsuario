#ifndef USUARIOCONTROLE_H
#define USUARIOCONTROLE_H
#include "UsuarioPersistencia.h"

namespace PBD {
    class UsuarioControle;
}

class UsuarioControle
{
private:
    UsuarioPersistencia *persistencia;

public:
    UsuarioControle();
    ~UsuarioControle();
    void salvar(const Usuario &usuario);
    void alterar(const Usuario &usuario);
    void excluir(const Usuario &usuario);
    std::queue<Usuario>* listar();
};

#endif // USUARIOCONTROLE_H

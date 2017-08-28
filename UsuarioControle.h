#ifndef USUARIOCONTROLE_H
#define USUARIOCONTROLE_H

#include "UsuarioPersistencia.h"
#include "CRUD.h"

namespace PBD {
    class UsuarioControle;
}

class UsuarioControle : public CRUD<Usuario>
{
private:
    UsuarioPersistencia *persistencia;

public:
    UsuarioControle();
    ~UsuarioControle();
    void salvar(const Usuario &obj);
    void alterar(const Usuario &obj);
    void excluir(const Usuario &obj);

    void validaNome(const QString &nome) const;
    void validaCpf(const QString &cpf) const;
    void validaSenha(const QString &senha) const;
    void validaEmail(const QString &email) const;

    Usuario buscarUsuario(const QString &cpf) const;
    std::queue<Usuario>* listar();
};

#endif // USUARIOCONTROLE_H

#include "UsuarioControle.h"

UsuarioControle::UsuarioControle():
    persistencia(new UsuarioPersistencia)
{

}

UsuarioControle::~UsuarioControle()
{
    delete persistencia;
}

void UsuarioControle::salvar(const Usuario &usuario)
{
    try
    {
        if(usuario.getNome().isEmpty()) throw QString("001 - Nome vazio");
        if(usuario.getCpf().length()<11) throw QString("002 - CPF invalido");
        if(usuario.getSenha().length() < 6) throw QString("003 - Senha < 6");
        if(usuario.getEmail().split('@').length() != 2) throw QString("004 - Email invalido");
        this->persistencia->salvar(usuario);
    } catch (QString &erro) { throw QString(erro); }
}

void UsuarioControle::alterar(const Usuario &usuario)
{
    try
    {
        this->persistencia->salvar(usuario);
    } catch (QString &erro) { throw QString(erro); }
}

void UsuarioControle::excluir(const Usuario &usuario)
{
    try
    {
        this->persistencia->excluir(usuario);
    } catch (QString &erro) { throw QString(erro); }
}

std::queue<Usuario> *UsuarioControle::listar()
{
    try
    {
        return this->persistencia->listar();
    } catch (QString &erro) { throw QString(erro); }
}

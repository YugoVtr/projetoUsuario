#include "UsuarioControle.h"

UsuarioControle::UsuarioControle():
    persistencia(new UsuarioPersistencia)
{

}

UsuarioControle::~UsuarioControle()
{
    delete persistencia;
}

void UsuarioControle::salvar(const Usuario &obj)
{
    try
    {
        this->validaNome(obj.getNome());
        this->validaCpf(obj.getCpf());
        this->validaSenha(obj.getSenha());
        this->validaEmail(obj.getEmail());

        this->persistencia->salvar(obj);
    } catch (QString &erro) { throw QString(erro); }
}

void UsuarioControle::alterar(const Usuario &obj)
{
    try
    {
        this->validaNome(obj.getNome());
        this->validaCpf(obj.getCpf());
        this->validaSenha(obj.getSenha());
        this->validaEmail(obj.getEmail());

        this->persistencia->alterar(obj);
    } catch (QString &erro) { throw QString(erro); }
}

void UsuarioControle::excluir(const Usuario &obj)
{
    try
    {
        this->validaCpf(obj.getCpf());

        this->persistencia->excluir(obj);
    } catch (QString &erro) { throw QString(erro); }
}

void UsuarioControle::validaNome(const QString &nome) const
{
    if(nome.isEmpty()) throw QString("001 - Nome vazio");
}

void UsuarioControle::validaCpf(const QString &cpf) const
{
    if(cpf.length()<11) throw QString("002 - CPF invalido");
}

void UsuarioControle::validaSenha(const QString &senha) const
{
    if(senha.length() < 6) throw QString("003 - Senha < 6");
}

void UsuarioControle::validaEmail(const QString &email) const
{
    if(email.split('@').length() != 2) throw QString("004 - Email invalido");
}

Usuario UsuarioControle::buscarUsuario(const QString &cpf) const
{
    try{
        return this->persistencia->buscarUsuario(cpf);
    }catch(QString &erro){ throw QString(erro); }
}

std::queue<Usuario> *UsuarioControle::listar()
{
    try
    {
        return this->persistencia->listar();
    } catch (QString &erro) { throw QString(erro); }
}

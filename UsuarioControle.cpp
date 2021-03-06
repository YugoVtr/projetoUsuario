#include "UsuarioControle.h"

UsuarioControle::UsuarioControle()
{
    try
    {
        persistencia = new UsuarioPersistencia;
    } catch (QString &erro) { throw QString(erro); }
}

UsuarioControle::~UsuarioControle()
{
    delete persistencia;
}

void UsuarioControle::salvar( Usuario &obj)
{
    try
    {
        this->validaNome(obj.getNome());
        this->validaCpf(obj.getCpf());
        this->validaSenha(obj.getSenha());
        this->validaEmail(obj.getEmail());

        //Codifica a senha com o padrão MD5
        QString queryStr = QString("%1").arg(QString(QCryptographicHash::hash(obj.getSenha().toUtf8(),QCryptographicHash::Md5).toHex()));
        obj.setSenha(queryStr);

        this->persistencia->salvar(obj);
    } catch (QString &erro) { throw QString(erro); }
}

void UsuarioControle::alterar(Usuario &obj)
{
    try
    {
        this->validaNome(obj.getNome());
        this->validaCpf(obj.getCpf());
        this->validaEmail(obj.getEmail());

        this->persistencia->alterar(obj);
    } catch (QString &erro) { throw QString(erro); }
}

void UsuarioControle::excluir(Usuario &obj)
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

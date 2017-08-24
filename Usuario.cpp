#include "Usuario.h"

QString Usuario::getNome() const
{
    return nome;
}

void Usuario::setNome(const QString &value)
{
    nome = value;
}

QString Usuario::getCpf() const
{
    return cpf;
}

void Usuario::setCpf(const QString &value)
{
    cpf = value;
}

QString Usuario::getSenha() const
{
    return senha;
}

void Usuario::setSenha(const QString &value)
{
    senha = value;
}

QString Usuario::getEmail() const
{
    return email;
}

void Usuario::setEmail(const QString &value)
{
    email = value;
}

QString Usuario::getTelefone() const
{
    return telefone;
}

void Usuario::setTelefone(const QString &value)
{
    telefone = value;
}

Usuario::Usuario():nome(""),cpf(""),senha(""),email(""),telefone("")
{

}
Usuario::Usuario(QString nome,QString cpf, QString senha,QString email, QString telefone):
    nome(nome),cpf(cpf),senha(senha),email(email),telefone(telefone)
{

}
Usuario::Usuario(const Usuario &usuario):
    nome(usuario.nome),cpf(usuario.cpf),senha(usuario.senha),email(usuario.email),telefone(usuario.telefone)
{

}

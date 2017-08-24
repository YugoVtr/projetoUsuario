#ifndef USUARIO_H
#define USUARIO_H
#include <QString>

namespace PBD {
    class Usuario;
}

class Usuario
{
private:
    QString nome;
    QString cpf;
    QString senha;
    QString email;
    QString telefone;

public:
    Usuario();
    Usuario(QString nome,QString cpf, QString senha,QString email, QString telefone);
    Usuario(const Usuario &usuario);
    QString getNome() const;
    void setNome(const QString &value);
    QString getCpf() const;
    void setCpf(const QString &value);
    QString getSenha() const;
    void setSenha(const QString &value);
    QString getEmail() const;
    void setEmail(const QString &value);
    QString getTelefone() const;
    void setTelefone(const QString &value);
};

#endif // USUARIO_H

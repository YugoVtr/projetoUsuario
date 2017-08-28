#include "UsuarioPersistencia.h"

UsuarioPersistencia::UsuarioPersistencia()
{
    try
    {
        banco = QSqlDatabase::addDatabase("QSQLITE");
        banco.setDatabaseName("C:/Users/celso/Desktop/bancoUsuario.db");

        if(!banco.open()) {
            throw QString(banco.lastError().text());
        }

    } catch (QString &erro) { throw QString(erro); }
}

UsuarioPersistencia::~UsuarioPersistencia()
{
    banco.close();
}

void UsuarioPersistencia::salvar(const Usuario &obj)
{
    try
    {
        QSqlQuery execQuery;
        execQuery.prepare("INSERT INTO Usuario(nome,cpf,email,telefone,senha) VALUES "
                        "(:nome,:cpf,:email,:telefone,:senha)");
        execQuery.bindValue(":nome",obj.getNome());
        execQuery.bindValue(":cpf",obj.getCpf());
        execQuery.bindValue(":email",obj.getEmail());
        execQuery.bindValue(":telefone",obj.getTelefone());
        execQuery.bindValue(":senha",obj.getSenha());

        if(!execQuery.exec())
        {
            throw QString(execQuery.lastError().text());
        }
    } catch (QString &erro) { throw QString(erro); }
}

void UsuarioPersistencia::alterar(const Usuario &obj)
{
    try
    {
        QSqlQuery execQuery;
        execQuery.prepare("UPDATE Usuario SET "
                        "nome = :nome, cpf = :cpf,email = :email,"
                        "telefone = :telefone,senha = :senha "
                        "WHERE cpf = :cpf");
        execQuery.bindValue(":nome",obj.getNome());
        execQuery.bindValue(":cpf",obj.getCpf());
        execQuery.bindValue(":email",obj.getEmail());
        execQuery.bindValue(":telefone",obj.getTelefone());
        execQuery.bindValue(":senha",obj.getSenha());

        if(!execQuery.exec())
        {
            throw QString(execQuery.lastError().text());
        }
    } catch (QString &erro) { throw QString(erro); }
}

void UsuarioPersistencia::excluir(const Usuario &obj)
{
    try
    {
        QSqlQuery execQuery;
        execQuery.prepare("DELETE FROM Usuario WHERE cpf = :cpf");
        execQuery.bindValue(":cpf",obj.getCpf());

        if(!execQuery.exec())
        {
            throw QString(execQuery.lastError().text());
        }
    } catch (QString &erro) { throw QString(erro); }
}

Usuario UsuarioPersistencia::buscarUsuario(const QString &cpf)
{
    try {
        QSqlQuery queryExec;
        queryExec.prepare("SELECT * FROM Usuario WHERE cpf = :cpf");
        queryExec.bindValue(":cpf",cpf);

        if(!queryExec.exec())
        {
            throw QString(queryExec.lastError().text());
        }

        QSqlRecord rec = queryExec.record();

        queryExec.next();

        QString nome = queryExec.value(rec.indexOf("nome")).toString();
        QString cpf = queryExec.value(rec.indexOf("cpf")).toString();
        QString telefone = queryExec.value(rec.indexOf("telefone")).toString();
        QString senha = queryExec.value(rec.indexOf("senha")).toString();
        QString email = queryExec.value(rec.indexOf("email")).toString();

        return Usuario(nome,cpf,senha,email,telefone);


    } catch (QString &erro) {
        throw QString(erro);
    }
}

std::queue<Usuario> *UsuarioPersistencia::listar()
{
    try
    {
        QString query = "select * from Usuario";

        QSqlQuery queryExec;
        if(!queryExec.exec(query))
        {
            throw QString(queryExec.lastError().text());
        }

        QSqlRecord rec = queryExec.record();

        std::queue<Usuario> *saida = new std::queue<Usuario>();

        while(queryExec.next())
        {
            QString nome = queryExec.value(rec.indexOf("nome")).toString();
            QString cpf = queryExec.value(rec.indexOf("cpf")).toString();
            QString telefone = queryExec.value(rec.indexOf("telefone")).toString();
            QString senha = queryExec.value(rec.indexOf("senha")).toString();
            QString email = queryExec.value(rec.indexOf("email")).toString();

            Usuario atual(nome,cpf,senha,email,telefone);
            saida->push(atual);
        }

        return saida;

    } catch (QString &erro) { throw QString(erro); }
      catch (std::bad_alloc&) { throw QString("000 - Erro de alocação de memória"); }
}

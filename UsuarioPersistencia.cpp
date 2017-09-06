#include "UsuarioPersistencia.h"

UsuarioPersistencia::UsuarioPersistencia()
{
    try
    {
        //Ao instanciar a persistencia inicia-se a conexão com o banco
        //definido no arquivo de configuração.
        banco = QSqlDatabase::addDatabase(Configuracao::getDataBase());
        banco.setDatabaseName(Configuracao::getDataBaseName());

        if(!banco.open()) {
            throw QString(banco.lastError().text());
        }

    } catch (QString &erro) { throw QString(erro); }
}

UsuarioPersistencia::~UsuarioPersistencia()
{
    banco.close();
}

void UsuarioPersistencia::salvar(Usuario &obj)
{
    try
    {
        //A classe QSqlQuery executa requisições ao SGBD
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

void UsuarioPersistencia::alterar(Usuario &obj)
{
    try
    {
        QSqlQuery execQuery;
        execQuery.prepare("UPDATE Usuario SET "
                        "nome = :nome, cpf = :cpf,email = :email,"
                        "telefone = :telefone "
                        "WHERE cpf = :cpf");
        execQuery.bindValue(":nome",obj.getNome());
        execQuery.bindValue(":cpf",obj.getCpf());
        execQuery.bindValue(":email",obj.getEmail());
        execQuery.bindValue(":telefone",obj.getTelefone());

        if(!execQuery.exec())
        {
            throw QString(execQuery.lastError().text());
        }
    } catch (QString &erro) { throw QString(erro); }
}

void UsuarioPersistencia::excluir(Usuario &obj)
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

        //A classe QSqlRecord encapsula a funcionalidade e as características
        //de uma gravação de banco de dados (geralmente uma linha em uma tabela ou exibição no banco de dados).
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
        QString query = "SELECT * FROM Usuario";

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

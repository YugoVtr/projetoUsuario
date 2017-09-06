#ifndef CONFIGURACAO_H
#define CONFIGURACAO_H
#include <string.h>
#include <QString>
#include <QStringList>
#include <fstream>

namespace PBD {
    class Configuracao;
}

//Classe que implementa o padrão singleton.
//Gerencia as configurações necessarias a execução do programa.

class Configuracao
{
private:
    QString dataBase;
    QString dataBaseName;
    QString imagem_Alterar;
    QString imagem_Salvar;
    QString imagem_Delete;
    static Configuracao *obj;

    Configuracao();
    static void verificaInstancia();
public:
    ~Configuracao() {if(obj)delete obj;}
    static QString getDataBase(){verificaInstancia(); return obj->dataBase;}
    static QString getDataBaseName(){verificaInstancia(); return obj->dataBaseName;}
    static QString getImagem_Alterar(){verificaInstancia(); return obj->imagem_Alterar;}
    static QString getImagem_Salvar(){verificaInstancia();return obj->imagem_Salvar;}
    static QString getImagem_Delete(){verificaInstancia();return obj->imagem_Delete;}
};
#endif // CONFIGURACAO_H

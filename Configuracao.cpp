#include "Configuracao.h"
Configuracao* Configuracao::obj = 0;

Configuracao::Configuracao()
{
    std::ifstream arquivo("../projetoUsuario/config.ini");
    if(!arquivo) throw QString("Erro ao carregar configurações");
    std::string linha;
    while(std::getline(arquivo,linha))
    {
        QString q_linha = QString::fromStdString(linha);
        QStringList control = q_linha.split("|");
        if (control[0]=="dataBase") this->dataBase = control[1];
        else if (control[0]=="dataBaseName") this->dataBaseName = control[1];
        else if (control[0]=="imagem_Alterar") this->imagem_Alterar = control[1];
        else if (control[0]=="imagem_Salvar") this->imagem_Salvar = control[1];
        else if (control[0]=="imagem_Delete") this->imagem_Delete = control[1];
    }
    arquivo.close();
}

void Configuracao::verificaInstancia()
{
    if(!obj) obj = new Configuracao();
}

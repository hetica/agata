# include "seqfastx.h"

using namespace std ;

// Constructeurs
SeqFastX::SeqFastX() : m_nomfic() {}

SeqFastX::SeqFastX(std::string nomfic) : m_nomfic(nomfic) {}

// Méthodes
string SeqFastX::getNomFic()
    {
        return m_nomfic ;
    }

void SeqFastX::loadFile()
{
    //Déclaration d'un flux permettant de lire dans un fichier
    string const file(m_nomfic);
    ifstream monFlux(file.c_str());

    if(monFlux)
    {
        cout << "mon flux" << endl ;
        string ligne ;

    }
    else
    {
        cout << "ERREUR: Impossible d'ouvrir le fichier." << endl;
    }

}



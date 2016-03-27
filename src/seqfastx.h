#ifndef SEQFASTX_H
#define SEQFASTX_H

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "encseq2.h"

extern bool debug ;

class SeqFastX
{

protected:
    // Attributs
    std::string m_nomfic ;						// nom du fichier
    std::vector<std::string> m_nomSequences ;	// nom de chaque séquence dans le fichier
    std::vector<size_t> n_longSequences ;		// longueur de chaque séquence dans le fichier
    // Méthodes
    void loadFile() ;

public:
    // Constructeurs
    SeqFastX() ;                        // Constructeur vide
    SeqFastX(std::string nomfic) ;      // Constructeur avec le nom
    // Méthodes
	std::string getNomFic() ;			// Renvoie le nom du fichier
	int chkFic() ;						// contrôle la validité du fichier

} ;

std::ostream & operator<<(std::ostream& os, const SeqFastX& s);

#endif // SEQFASTX_H


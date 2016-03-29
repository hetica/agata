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
	static int nbSeq ;								// nombre de séquences créés
	static int nbSeqNoName ;						// nombre de séquences sans nom
	size_t numSeq ;									// numéro de la séquence
    std::string m_seqName ;							// nom de la séquence
    //std::vector<std::string> m_nomSequences ;		// nom de chaque séquence dans le fichier
    size_t m_longSequences ;						// longueur de chaque séquence dans le fichier
    // Méthodes
  
public:
    // Constructeurs
    SeqFastX() ;									// Constructeur vide
    SeqFastX(std::string seqName) ;					// Constructeur avec le nom
    SeqFastX(size_t nbSeq, std::string seqName) ;	// Constructeur avec le numero et nom
    // Méthodes
	std::string getSeqName() ;						// Renvoie le nom de la séquence
	//int chkFic() ;									// contrôle la validité du fichier
	static int getNbSeq() ;							// renvoie le nombre de séquences
	static int getNbSeqNoName() ;					// renvoie le nombre de séquences sans nombre

} ;

std::ostream & operator<<(std::ostream& os, const SeqFastX& s) ;

#endif // SEQFASTX_H


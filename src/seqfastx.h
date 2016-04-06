#ifndef SEQFASTX_H
#define SEQFASTX_H

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "encseq2.h"
#include "encseq4.h"

extern bool debug ;

class SeqFastX
{

protected:
    // Attributs
	static int nbSeq ;											// nombre de séquences créés
	size_t numSeq ;												// numéro de la séquence
    std::string m_seqName  ;									// nom de la séquence
    size_t m_longSeq ;											// longueur de la séquence
    unsigned char * encodage;									// tableau de car encodée
    // Méthodes
    void encode(const char * c);								// encode une séquence
    unsigned char encode_char(char c);							// encode un caractère
    std::string decode();										// décode une séquence
    unsigned char decode_char(unsigned char c);					// décode un caractère
	std::string decode_rc();									// décode une séquence en reverse complement
	unsigned char decode_char_comp(unsigned char c);			// décode un caractère en complémentaire
  
public:
    // Constructeurs
    SeqFastX() ;												// Constructeur vide
    SeqFastX(std::string seqName) ;								// Constructeur avec le nom
    //SeqFastX(size_t nbSeq, std::string seqName) ;				// Constructeur avec le numero et nom
    SeqFastX(std::string seqName, const char* seq) ;			// Constructeur avec le nom et la séquence
    // Méthodes
	std::string getSeqName() ;									// retourne le nom de la séquence
	size_t getLongSeq() ;										// retourne la longueur de la séquence
	std::string getSequence() ;									// retourne la séquence compléète
	std::string getSequenceRC() ;								// retourne la séquence Reverse complément
	static int getNbSeq() ;										// retourne le nombre de séquences
	std::string getSubSeq(size_t posDebut, size_t longSeq);		// retourne une sous-séquence
	std::string getSubSeqRC(std::string & subSeq);				// retourne une sous-séquence Reverse complément
} ;

std::ostream & operator<<(std::ostream& os, const SeqFastX& s) ;

#endif // SEQFASTX_H


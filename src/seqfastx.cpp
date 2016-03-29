# include "seqfastx.h"

using namespace std ;

int SeqFastX::nbSeq = 0 ; 							// initialise nombre de séquences 0
int SeqFastX::nbSeqNoName = 0 ; 					// initialise nombre de séquences vides

// Constructeurs
SeqFastX::SeqFastX() : m_seqName()
{
	nbSeq++ ;
}

SeqFastX::SeqFastX(std::string seqName) : m_seqName(seqName) {
	nbSeq++ ;
}

SeqFastX::SeqFastX(size_t nbSeq, string seqName) : numSeq(nbSeq), m_seqName(seqName) {
	nbSeq++ ;										// compteur de reads
}

//SeqFastX::~SeqFastX() {}							// Destructeur

// Méthodes
string SeqFastX::getSeqName()
    {
        return m_seqName ;
    }

int SeqFastX::getNbSeq()
{
	return nbSeq ;
}

int SeqFastX::getNbSeqNoName()
{
	return nbSeqNoName ;
}

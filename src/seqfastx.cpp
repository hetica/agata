# include "seqfastx.h"

using namespace std ;

int SeqFastX::nbSeq = 0 ; 							// initialise nombre de séquences 0
int SeqFastX::nbSeqNoName = 0 ; 					// initialise nombre de séquences vides

// Constructeurs
SeqFastX::SeqFastX() : m_seqName(), encodage(NULL) {
	nbSeq++ ;
}

SeqFastX::SeqFastX(std::string seqName) : m_seqName(seqName), encodage(NULL) {
	nbSeq++ ;
}

SeqFastX::SeqFastX(string seqName, const char * seq) :
				numSeq(nbSeq),m_seqName(seqName), m_longSeq(0), encodage(NULL) {
	nbSeq++ ;										// compteur de reads
	/* en entrée :
		- l'intitulé de la séquence
		- la séquence elle même (sous forme de tableau de char) {'h', 'e', 'l', 'l', 'o', '\0'}
	*/
	// Si la séquence n'est pas nulle
	if (seq != NULL) {

		// tant qu'on n'est pas à la fin de la séquence
		while(seq[m_longSeq] != '\0') {
			// On appelle la fonction estValide() pour tester si le nucleotide est valide
			/*if (! estValide(seq[m_longSeq])) {
				// avertir qu'il y'a un caractere invalide
				cout << "[" << intitule << "]" << " invalid char: " << seq[m_longSeq] << " (pos: " << m_longSeq << ")" << endl;
			}*/
			m_longSeq++;		// ajoute 1 pour aller au nucleotide suivant
		}

		// on crée un tableau d'octets pour encoder les nucleotides (4 nuc/octet)
		// calcule le nombre de lignes nécessaire (la dernière ligne peut être incomplète...)
		// Exemple avec une séquence de 14 nucleotides:
		// longueur / 4  --> 14 / 4 = 3
		// longueur % 4 != 0 --> 14 % 4 != 0 --> True --> 1
		// longueur / 4 + (longueur%4 != 0) --> 3 + 1 = 4 lignes en tout
		encodage = new unsigned char[m_longSeq/4 + (m_longSeq%4 != 0)];	// new permet de réserver un espace mémoire

		// remplir le tableau
		encode(seq);
	} else {
		cout << "La séquence est vide " << endl ;
	}
	//cout << "longueur de " << m_seqName << ": " << m_longSeq << endl ;
}

//SeqFastX::~SeqFastX() {}							// Destructeur

// Méthodes

// retourne le nom de la séquence
string SeqFastX::getSeqName() { return m_seqName ; }

// retourne la longueur de la séquence
size_t SeqFastX::getLongSeq() { return m_longSeq ; }

// retourne la séquence
string SeqFastX::getSequence() { return decode() ; }

// retourne la séquence en reverse complement
string SeqFastX::getSequenceRC() { return decode_rc() ; }

// retourne le nombre total de séquences
int SeqFastX::getNbSeq() { return nbSeq ; }

// remplit un octet avec 4 nucleotides, puis stocke l'octet dans le tableau "encodage" (un champs = un octet)
void SeqFastX::encode(const char * seq) {
	// A -> 00  ->  11
    // C -> 01  ->  10
    // G -> 10  ->  01
    // T -> 11  ->  00

	unsigned char temp = 0;  		                // temp cumule les valeurs de 4 nucléotides sur un octet

	for (size_t i = 0; i <= m_longSeq; i++) {

		// Lorsqu'un octet est rempli --> aux indices multiples de 4 (sauf 0)
		if (i > 0 && i % 4 == 0) {
			encodage[i / 4 - 1] = temp;			    // affecte temp à l'octet courant (temp = valeurs cumulées de 4 nucléotides)
			temp = 0; 							    // et temp revient à 0 ( 00 00 00 00 )
		}

		// tant qu'on est pas à la fin
		if (i < m_longSeq) {
			temp = temp << 2;						// décale temp de 2 bits vers la gauche (ex : 01 11 --> 01 11 00 )
			temp = temp | encode_char(seq[i]);		// augmente l'octet de la valeur du nucléotide correspondant à seq[i]
		}
	}

	// lorsque le dernier octet est incomplet, on se retrouve avec une valeur de temp non affectée
	// pour une ligne complète, on a (longueur / 4) + 1 	( +1 pour tenir compte de l'indice )
	// donc pour une ligne incomplete, on a (longueur / 4 ) + 1 -1	==> longueur / 4
	if (m_longSeq % 4 != 0) {
		// décale les valeurs vers la gauche pour compléter l'octet
		encodage[m_longSeq / 4] = temp << ((4 - m_longSeq % 4) * 2);
	}
}

// transforme un caractère (A,T,C ou G) en son équivalent en bits (00, 11, 01, 10)
// appelé par la méthode encode()
unsigned char SeqFastX::encode_char(char c) {
    switch (c) {
      case 't': return 3;       // T -> 11
      case 'T': return 3;
      case 'G': return 2;       // G -> 10
      case 'g': return 2;
      case 'c': return 1;       // C -> 01
      case 'C': return 1;
      case 'A': return 0;       // A -> 00
      case 'a': return 0;
      default: return 0; // On peut aussi sortir du programe...
    }
}

// transforme un entier 0, 1, 2 ou 3 en son équivalent en nucléotide (A, C, G, T)
// appelé par la méthode decode()
unsigned char SeqFastX::decode_char(unsigned char c) {
    switch (c) {
        case 3:  return 'T';
        case 2:  return 'G';
        case 1:  return 'C';
        case 0:  return 'A';
        default: return 'N';
    }
}

// Comme decode_char, mais en complémentaire
unsigned char SeqFastX::decode_char_comp(unsigned char c) {
    switch (c) {
        case 0:  return 'T';
        case 1:  return 'G';
        case 2:  return 'C';
        case 3:  return 'A';
        default: return 'N';
    }
}

// Décodage d'une séquence
string SeqFastX::decode() {
    if (encodage == 0) {
        std::cout << "Séquence " << m_seqName << ": NULL" << endl;
        return "";
    }

    // aCgtAaGt ---->   010101010010101010101001 --> aCgtAaGt
    //  unsigned char * data = encodage[];
    unsigned char temp = 0;
    string decodage = "" ;

    for (size_t i = 0; i < m_longSeq / 4; ++i) {
        temp = encodage[i];

        decodage += decode_char((temp >> 6) & 3);
        decodage += decode_char((temp >> 4) & 3);
        decodage += decode_char((temp >> 2) & 3);
        decodage += decode_char((temp >> 0) & 3);
    }

    temp = encodage[m_longSeq/4];
    int rest = m_longSeq % 4;

    if (rest == 3)   {
        decodage += decode_char((temp >> 6) & 3);
        decodage += decode_char((temp >> 4) & 3);
        decodage += decode_char((temp >> 2) & 3);
    }

    if (rest == 2)   {
        decodage += decode_char((temp >> 6) & 3);
        decodage += decode_char((temp >> 4) & 3);
    }

    if (rest == 1)   {
        decodage += decode_char((temp >> 6) & 3);
    }

    return decodage ;
}

// decodage d'une séquence, en complémentaire inversée
std::string SeqFastX::decode_rc() {
    if (encodage == 0) {
        std::cout << "Séquence " << m_seqName << ": NULL" << endl;
        return "";
    }

    unsigned char temp = 0;
    string decodageRC = "" ;

    temp = encodage[m_longSeq/4];                        // longueur de la séquence codée
    int rest = m_longSeq % 4;                            // la séquence est elle multiple de 4 ?

    if (rest == 3)   {                                  // si 3 nuc dans le dernier octet
        decodageRC += decode_char((temp >> 2) & 3);
        decodageRC += decode_char((temp >> 4) & 3);
        decodageRC += decode_char((temp >> 6) & 3);
    }

    if (rest == 2)   {                                  // si 2 nuc dans le dernier octet
        decodageRC += decode_char((temp >> 4) & 3);
        decodageRC += decode_char((temp >> 6) & 3);
    }

    if (rest == 1)   {                                  // si 1 nuc dans le dernier octet
        decodageRC += decode_char((temp >> 6) & 3);
    }

    for (int i = m_longSeq / 4 -1 ; i >= 0; --i) {       // pour tous les octets contenant 4 nuc
        temp = encodage[i];

        decodageRC += decode_char_comp((temp >> 0) & 3);
        decodageRC += decode_char_comp((temp >> 2) & 3);
        decodageRC += decode_char_comp((temp >> 4) & 3);
        decodageRC += decode_char_comp((temp >> 6) & 3);
    }

    return decodageRC ;
}

string SeqFastX::getSubSeq(size_t posDebut, size_t longSeq) {
	// rechercher la position du premier nuc
	string subSeq ;											// la sous séquence
	unsigned char temp = 0;									// position dans l'encodage
	size_t encPos ;											// position de début
	int restd = posDebut % 4 ;								// reste dans l'octet au départ
	int restf =	( posDebut + longSeq ) % 4 ;				// reste dans l'octet à la fin

	//cout << "Sous-sequence - Depart, longueur: " << posDebut << ", " << longSeq << endl ;
	//cout << "Sous-sequence - mod dep, mod fin: " << restd << ", " << restf << endl ;

	encPos = posDebut/4 ;
	temp = encodage[encPos] ;
	
    if (restd == 1)   {
        subSeq += decode_char((temp >> 4) & 3);
        subSeq += decode_char((temp >> 2) & 3);
        subSeq += decode_char((temp >> 0) & 3);
        temp = encodage[++encPos] ;
        longSeq -= 3 ;
    }

    if (restd == 2)   {
        subSeq += decode_char((temp >> 2) & 3);
        subSeq += decode_char((temp >> 0) & 3);
        temp = encodage[++encPos] ;
        longSeq -= 2 ;
    }

    if (restd == 3)   {
        subSeq += decode_char((temp >> 0) & 3);
        temp = encodage[++encPos] ;
        longSeq -= 1 ;
    }
    
	for ( size_t i = 0; i<longSeq/4; i++) {
		subSeq += decode_char((temp >> 6) & 3);
		subSeq += decode_char((temp >> 4) & 3);
		subSeq += decode_char((temp >> 2) & 3);
		subSeq += decode_char((temp >> 0) & 3);
		temp = encodage[++encPos] ;
	}

	//temp = encodage[encPos++] ;

	if ( restf == 1 ) {
		subSeq += decode_char((temp >> 6) & 3);
	}

	if ( restf == 2 ) {
		subSeq += decode_char((temp >> 6) & 3);
		subSeq += decode_char((temp >> 4) & 3);
	}

	if ( restf == 3 ) {
		subSeq += decode_char((temp >> 6) & 3);
		subSeq += decode_char((temp >> 4) & 3);
		subSeq += decode_char((temp >> 2) & 3);
	}

	return subSeq ;
}

string SeqFastX::getSubSeqRC(size_t posDebut, size_t longSeq) {
	string subSeq = "" ;
	return subSeq ;
}

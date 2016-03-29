# include "fastxfile.h"

using namespace std ;

// Constructeurs
FastxFile::FastxFile()
{
}

FastxFile::FastxFile(std::string fileName) : fileName(fileName)
{
	setFileType() ;
	setSequences() ;
}

// Méthodes

string const FastxFile::getFileName()
{
	return fileName ;
}

void FastxFile::setFileType()
{
	ifstream flux(fileName.c_str());
	char a = 0 ;
	flux.get(a) ;
	if ( a == '>' ) fileType = "fasta" ;
	else if ( a == '@' ) fileType = "fastq" ;
	else fileType = "unKnown" ;
}

string const FastxFile::getFileType()
{
	return fileType ;
}

void FastxFile::setSequences()
{
	string ligne = "" ;										// les lignes du flux
	bool seqIsOk = false ;									// la séquence est OK
	string seqBody = "" ;									// la séquence
	string intituleSeq = "" ;								// intitulé de la séquence
	stringstream ss ;										// pour résoudre le PB du 'to_string'
	int numSeqFile = 0 ;									// numéro de séquence dans le fichier

	ifstream flux(fileName.c_str());
	while (getline(flux, ligne))
	{
		// if (debug) { cout << ligne[0] << ", " ; cout << endl ; }
		if ( ligne[0] == '>' )								// si premier caractère de la ligne = '>'
		{
			seqIsOk = true ;								// On a une séquence
			// Si la séquence est != "", créer une instance de séquence fasta (intitulé, sequence)
			if ( seqBody != "" )
			{
				sequences.push_back(SeqFastX(intituleSeq)) ;
				numSeqFile++ ;
			}
			// si champs 2 non vide
				// intitulé = champs2
			// sinon
				// intitulé = créer un intitulé en utilisant l'attribut statique nbSeqNoName
				//cout << "SEQGASTX.GETNBSEQ" << SeqFastX.getNbSeq() << endl ;
				ss << SeqFastX::getNbSeq() ;
				intituleSeq = "R" + ss.str();
				ss.str("") ;								// réinitialise le stingstream
				if (debug) cout << "IntituleSeq: " << intituleSeq << endl ;

		// sinon si premier caractère = '@'
			// type = fastq
			// Si la séquence est != "", créer une instance de séquence fastq (intitulé, sequence)
		}

		else if (seqIsOk)											// sinon si seqIsOk
		{
			// s'il y a un autre caractère que 'A,T,C,G'
				// seqIsOk = false
				// continue
			// sinon
				seqBody += ligne ;								// sequence += ligne
		}

		// sinon
			// inconnue sur la séquence
			// en indiquant le fichier (et le numéro de ligne)

		
	}
	// Pour la dernière séquence
	if (seqIsOk)
	{
		sequences.push_back(SeqFastX(intituleSeq)) ;
	}

	if (debug && seqIsOk) {
		cout << "Fichier: " << fileName << endl ;
		cout << "  nbSeq: " << sequences[numSeqFile].getNbSeq() << endl ;
		for ( int i; i <= numSeqFile; i++) {
			cout << "  sequence: " << i << endl ;
			cout << "  seqName: " << sequences[i].getSeqName() << endl ;
		}
	}
}

SeqFastX const getSequences()
{

}

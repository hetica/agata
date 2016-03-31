# include "fastxfile.h"

using namespace std ;

// Teste si le caractère est bien un nucléotide
bool estValide(char nuc) {
	return 	(nuc=='A') || (nuc=='a') ||
			(nuc=='C') || (nuc=='c') ||
			(nuc=='G') || (nuc=='g') ||
			(nuc=='T') || (nuc=='t');
}

// Constructeurs
FastxFile::FastxFile()
{
}

FastxFile::FastxFile(std::string fileName) : fileName(fileName)
{
	setFileType() ;
	setSequences() ;
}

// Destructeur
FastxFile::~FastxFile() {}

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
	// Si le fichier n'est pas au bon format
	if ( fileType == "unKnown" ) {
		cout << fileName << " is not a valid file" << endl ;
		return void();
	}
	string ligne = "" ;										// les lignes du flux
	bool seqIsOk = false ;									// la séquence est OK
	string seqBody = "" ;									// la séquence
	string intituleSeq = "" ;								// intitulé de la séquence
	stringstream ss ;										// pour résoudre le PB du 'to_string'
	int numSeqFile = 0 ;									// numéro de séquence dans le fichier
	size_t lineNumber = 0 ;									// Numéro de ligne

	ifstream flux(fileName.c_str());
	while (getline(flux, ligne))
	{
		lineNumber ++ ;
		if ( ligne[0] == '>' )								// si premier caractère de la ligne = '>'
		{
			seqIsOk = true ;								// On a une séquence
			// Si la séquence n'est pas vide, créer une instance de séquence fasta (intitulé, sequence)
			if ( seqBody != "" )
			{
				const char *seq = seqBody.c_str();
				sequences.push_back(SeqFastX(intituleSeq, seq)) ;	// on créée une instance de séquence
				numSeqFile++ ;									// on incrémente le nombre de séquences
				seqBody = "" ;									// on remet seqBody à vide ...
				
			}
			// si champs 2 non vide
				// intitulé = champs2
			// sinon
				// intitulé = créer un intitulé en utilisant l'attribut statique nbSeqNoName
				ss << SeqFastX::getNbSeq() ;
				intituleSeq = "R" + ss.str();
				ss.str("") ;									// réinitialise le stingstream
				//if (debug) cout << "IntituleSeq: " << intituleSeq << endl ;

		// sinon si premier caractère = '@'
			// type = fastq
			// Si la séquence est != "", créer une instance de séquence fastq (intitulé, sequence)
		}

		else if (seqIsOk)											// sinon si seqIsOk
		{
			//cout << "ligne: " << ligne << endl ;
			//cout << "ligne.size: " << ligne.size() << endl ;
			for ( size_t i=0; i<ligne.size() ; i++)
			{
				if ( ! estValide(ligne[i]) && seqIsOk)
				{
					// s'il y a un autre caractère que 'A,T,C,G'
					cout << "Character '" << ligne[i] << "' at line " << lineNumber << "," << i+1 << " in file '" << fileName << "' not supported" << endl ;
					cout << "this sequence will not be included in mapping" << endl ;
					seqIsOk = false ;
					seqBody = "" ;
					break ;
				}
			}
			if (seqIsOk) seqBody += ligne ;								// sequence += ligne
		}

	}
	// Pour la dernière séquence
	if (seqIsOk)
	{
		const char *seq = seqBody.c_str();
		sequences.push_back(SeqFastX(intituleSeq, seq)) ;
	}
}

vector<SeqFastX> const FastxFile::getSequences()
{
	return sequences ;
}

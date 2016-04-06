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
FastxFile::FastxFile() {
}

FastxFile::FastxFile(string fileName, string fileType) : fileName(fileName), fileType(fileType) {
	if ( fileType == "fasta" ) setSeqFasta() ;
	if ( fileType == "fastq" ) setSeqFastq() ;
}

// Destructeur
FastxFile::~FastxFile() {}

// Méthodes

string const FastxFile::getFileName() {
	return fileName ;
}

string const FastxFile::getFileType() {
	return fileType ;
}

void FastxFile::setSeqFasta() {
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
						// Donner un intitulé à la séquence
			if ( ligne.size() > 1 ) {							// si champs 2 non vide
				if ( ligne[1] != ' ' ) intituleSeq += ligne[1] ;
				for ( int i=2; i<ligne.size(); i++ ) {
					if ( ligne[i] == ' ' ) break ;
					intituleSeq += ligne[i] ;
				}
			} else {
				ss << SeqFastX::getNbSeq() ;
				intituleSeq = "R" + ss.str();
				ss.str("") ;									// réinitialise le stingstream
			}
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

void FastxFile::setSeqFastq() {
	int nu ;														// 1: ID, 2, sequence, 3: Quality ID, 4, Quality
	string ligne = "" ;												// les lignes du flux
	bool seqIsOk ;													// la séquence est OK
	//string seqBody = "" ;											// la séquence
	string intituleSeq = "" ;										// intitulé de la séquence
	stringstream ss ;												// pour résoudre le PB du 'to_string'
	int numSeqFile = 0 ;											// numéro de séquence dans le fichier
	size_t lineNumber = 0 ;											// Numéro de ligne

	ifstream flux(fileName.c_str());
	while (getline(flux, ligne))
	{
		lineNumber ++ ;
		if ( ligne[0] == '@' )										// si premier caractère de la ligne = '>'
		{
			nu = 1 ;												// Identifiant
			// si champs 2 non vide
				// intitulé = champs2
			// sinon
			if ( ligne.size() > 1 ) {								// si champs 2 non vide
				for ( int i=1; i<ligne.size(); i++ ) {
					intituleSeq += ligne[i] ;
				}
			} else {
				intituleSeq = "" ;
			}
		}
		
		else if ( nu == 1 )											// sinon si seqIsOk
		{
			nu = 2 ;												// Séquence
			seqIsOk = true ;										// à priori, la séquence est OK 
			
			for ( size_t i=0; i<ligne.size() ; i++)					// pour chaque caractère de la ligne
			{
				if ( ! estValide(ligne[i]) )						// si le caractère n'est pas valide
				{
					// s'il y a un autre caractère que 'A,T,C,G'
					cout << "Character '" << ligne[i] << "' at line " << lineNumber << "," << i+1 << " in file '" << fileName << "' not supported" << endl ;
					cout << "this sequence will not be included in mapping" << endl ;
					seqIsOk = false ;
					break ;
				}
			}
			
			if (seqIsOk) {											// si la ligne est valide
				if ( intituleSeq == "" ) {
					// créer un intitulé en utilisant l'attribut statique nbSeqNoName
					ss << SeqFastX::getNbSeq() ;
					intituleSeq = "R" + ss.str();
					ss.str("") ;									// réinitialise le stingstream
				}

				const char* seq = ligne.c_str() ;					// la ligne est mise dans un char *
				sequences.push_back(SeqFastX(intituleSeq, seq)) ;	// créer un instance de séquence
				intituleSeq = "" ;									// remettre l'intitulé à vide
			}
		}

	}
}

vector<SeqFastX> const FastxFile::getSequences() {
	return sequences ;
}

void FastxFile::printAll() {
	cout << "---------------------------------" << endl ;
	cout << "Nom du fichier: " << fileName << endl;
	size_t seqSize = sequences.size() ;
	cout << "nombre de Sequences: " << seqSize << endl ;

	for (int j=0; j<seqSize ; j++) {

		SeqFastX s = sequences[j] ;
	
		//s.getSeqName() ;
		cout << "  Sequence name: " << s.getSeqName() << endl ;
		s.getLongSeq() ;
		cout << "  Sequence size: " << s.getLongSeq() << endl ;
		s.getNbSeq() ;
		//cout << " Nombre de séquences: " << s.getNbSeq() << endl ;
		s.getSequence() ;
		//cout << "  Sequence content: " << s.getSequence() << endl ;
		s.getSequenceRC() ;
		//cout << "  Sequence Reverse Complement: " << s.getSequenceRC() << endl ;

		string ss1 = s.getSubSeq(5,10) ;
		//cout << "---\nsous-séquence(5,10): " << ss1 << endl ;
		string ssrc1 = s.getSubSeqRC(ss1) ;
		//cout << "sous-séquence Rev Compl(5,10): " << ssrc1 << endl ;
		string ss2 = s.getSubSeq(6,11) ;
		//cout << "---\nsous-séquence(6,11): " << ss2 << endl ;
		string ssrc2 = s.getSubSeqRC(ss2) ;
		//cout << "sous-séquence Rev Compl(6,11): " << ssrc2 << endl ;
		string ss3 = s.getSubSeq(7,12) ;
		//cout << "---\nsous-séquence(7,12): " << ss3 << endl ;
		string ssrc3 = s.getSubSeqRC(ss3) ;
		//cout << "sous-séquence Rev Compl(7,12): " << ssrc3 << endl ;
		string ss4 = s.getSubSeq(8,10) ;
		//cout << "---\nsous-séquence(8,10): " << ss4 << endl ;
		string ssrc4 = s.getSubSeqRC(ss4) ;
		//cout << "sous-séquence Rev Compl(8,10): " << ssrc4 << endl ;
		string ss5 = s.getSubSeq(0,2) ;
		//cout << "---\nsous-séquence(0,2): " << ss5 << endl ;
		string ssrc5 = s.getSubSeqRC(ss5) ;
		//cout << "sous-séquence Rev Compl(0,2): " << ssrc5 << endl ;
	}
}



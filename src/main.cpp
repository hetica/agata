#include <iostream>
#include <getopt.h>
#include <stdlib.h>    						// for exit
#include <vector>
#include <fstream>
# include "options.h"
# include "fastxfile.h"
# include "seqfastx.h"
# include "refseqfile.h"
//# include "sa.h"


bool debug = false ;						// Variable globale pour afficher les messages de dev

// Namespaces:
using namespace std;

// vérifier si le fichier contient des séquences
string fileType( const string &file ) {
	ifstream flux(file.c_str());
	char a = 0 ;
	flux.get(a) ;
	if ( a == '>' ) { return "fasta" ; }
	if ( a == '@' ) { return "fastq" ; }
	return "unknown" ;
}

int main(int argc, char** argv)
{
	////////////////////////////////////////////////////////////////////////////
	//				Opérations préliminaires
	////////////////////////////////////////////////////////////////////////////
	
	// Initialisation des variables
	string refseqfile = "" ;				// fichier de référence
	string samfile = "" ;					// fichier en sortie
	vector<string> fastxfile ;				// fichiers à aligner (reads)

	// Vérifier et gérer les options de commande
	options(argc, argv, refseqfile, samfile, fastxfile ) ;

	////////////////////////////////////////////////////////////////////////////
	//				Fichiers de séquences à aligner
	////////////////////////////////////////////////////////////////////////////
	
	// Pour chaque fichier fastx
	for (int i=0; i<fastxfile.size(); ++i ) {
		string ft = fileType(fastxfile[i]) ;					// détermine le type de fichier

		// Créer un instance de fichier fastx
		if ( ft == "fasta" ) { 
			FastxFile * fa = new FastxFile(fastxfile[i], ft) ;
			if (debug) { fa->printAll() ; }
			delete fa ;
		}

		// Créer un instance de fichier fastq
		if ( ft == "fastq" ) { 
			FastxFile * fq = new FastxFile(fastxfile[i], ft) ;
			if (debug) { fq->printAll() ; }			
			delete fq ;
		}

		if ( ft == "unknown" ) {
			cout << fastxfile[i] << " is not a valid file" << endl ;
		}
	}

	////////////////////////////////////////////////////////////////////////////
	//				Fichier de référence
	////////////////////////////////////////////////////////////////////////////
	
	string ft = fileType(refseqfile) ;							// Récupérer le type de fichier
	RefSeqFile * rsf = new RefSeqFile(refseqfile, ft) ;			// Créer une instance du ficher
//	FastxFile * fr = new FastxFile(refseqfile, ft) ;			// Créer une instance du ficher
	if ( debug ) rsf->printAll() ;
//	SeqFastX frSEQ = fr->getSequences()[0] ;					// Créer une instance de séquence
//	cout << "nom seq: " << frSEQ.getSeqName() << endl ;
	// créer une table SA et LCP
	
	
	//SA frSA = SA(frSEQ.getSequence()) ;							// Créer une instance de SA
/*	if ( debug ) {
		cout << "sequence: " << frSEQ.getSequence() << endl ;
		cout << "Taille de SA: " << frSA.getSA().size() << endl ;
		cout << "Taille de SA: " << frSA.getSize() << endl ;
		for ( size_t i=0 ; i<frSA.getSize() ; i++) {
			cout << "SA: " << frSA.getSA()[i] << " - CAR: " << frSEQ.getSequence()[frSA.getSA()[i]]
				<< " - LCP: " << frSA.getLCP()[i]
				<< " - suffixe: " << frSEQ.getSequence().substr(frSA.getSA()[i]) << endl ;
		}
	}*/
	// lancer l'alignement

	//delete fr ;


	if (debug) cout << "EOF" << endl ;
	exit(EXIT_SUCCESS);
}

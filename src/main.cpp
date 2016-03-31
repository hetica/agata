#include <iostream>
#include <getopt.h>
#include <stdlib.h>    /* for exit */
#include <vector>
#include <fstream>
# include "options.h"
# include "fastxfile.h"
# include "seqfastx.h"


bool debug = false ;						// Variable globale pour afficher les messages de dev

// Namespaces:
using namespace std;

// vérifier si le fichier contient des séquences
string file_type( const string &file ) {
	ifstream flux(file.c_str());
	char a = 0 ;
	flux.get(a) ;
	if ( a == '>' ) { return "fasta" ; }
	if ( a == '@' ) { return "fastq" ; }
	return "unknown" ;
}

int main(int argc, char** argv)
{
	// Initialisation des variables
	string refseqfile = "" ;				// fichier de référence
	string samfile = "" ;					// fichier en sortie
	vector<string> fastxfile ;				// fichiers à aligner (reads)
	int fileType ;							// 1: fasta, 2: fastq

	// Vérifier et gérer les options de commande
	options(argc, argv, refseqfile, samfile, fastxfile ) ;

	// Pour chaque fichier fastx
	for (int i=0; i<fastxfile.size(); ++i ) {
		string ft = file_type(fastxfile[i]) ;

		// Créer un instance de fichier fastx
		if ( file_type(fastxfile[i]) == "fasta" ) { 
			FastxFile * f = new FastxFile(fastxfile[i]) ;
			if (debug) {
				cout << "------------------------------\nFichier: " << f->getFileName() << endl ;
				cout << "nombre de Sequences: " << f->getSequences().size() << endl ;
				for (int j=0; j<f->getSequences().size(); j++) {
					SeqFastX s = f->getSequences()[j] ;
					cout << "  Sequence name: " << s.getSeqName() << endl ;
					cout << "  Sequence size: " << s.getLongSeq() << endl ;
					cout << "  Sequence content: " << s.getSequence() << endl ;
					cout << "  Sequence Reverse Complement: " << s.getSequenceRC() << endl ;

					string ss1 = s.getSubSeq(5,10) ;
					cout << "sous-séquence(5,10): " << ss1 << endl ;

					string ss2 = s.getSubSeq(6,11) ;
					cout << "sous-séquence(6,11): " << ss2 << endl ;

					string ss3 = s.getSubSeq(7,12) ;
					cout << "sous-séquence(7,12): " << ss3 << endl ;

					string ss4 = s.getSubSeq(8,10) ;
					cout << "sous-séquence(8,10): " << ss4 << endl ;

					string ss5 = s.getSubSeq(0,1) ;
					cout << "sous-séquence: " << ss5 << endl ;
				}
			}
			delete f ;
		}

		if ( file_type(fastxfile[i]) == "fastq" ) { 
			FastxFile * f = new FastxFile(fastxfile[i]) ;

			delete f ;
		}

		if ( file_type(fastxfile[i]) == "unknown" ) {
			cout << fastxfile[i] << " is not a valid file" << endl ;;
		}
		
	}

    if (debug) cout << "EOF" << endl ;
    exit(EXIT_SUCCESS);
}

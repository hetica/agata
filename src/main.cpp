#include <iostream>
#include <getopt.h>
#include <stdlib.h>    /* for exit */
#include <vector>
#include <fstream>
# include "options.h"
# include "fastxfile.h"
# include "seqfastx.h"

// Variable globale pour afficher les messages de dev
bool debug = false ;

// Namespaces:
using namespace std;

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
		// Créer un instance de fichier fastx
		FastxFile f(fastxfile[i]) ;
		if (debug) cout << "filename: " << f.getFileName() << endl ;
		if (debug) cout << "file Type: " << f.getFileType() << endl ;
	}

    if (debug) cout << "EOF" << endl ;
    exit(EXIT_SUCCESS);
}

#include <iostream>
#include <getopt.h>
#include <stdlib.h>    /* for exit */
#include <vector>
//#include <typeinfo>

// Namespaces:
using namespace std;

int main(int argc, char** argv)
{
    // Variables pour parser et gérer les options
	int c;
    int digit_optind = 0;
    string helpmesg = "Usage : agata -i SEQUENCE -o OUTPUT.SAM FILE1 FILE2 FILEn\n\n"
                        "Mapper des fichiers fasta ou fastq sur une séquence de référence SEQUENCE et produire un fichier OUTPUT.SAM\n\n"
                        "       -i SEQUENCE                 sequence's reference\n"
                        "       - o OUTPUT.SAM              output file, in SAM format\n"
                        "       FILE1 FILE2 FILEn           reads, in FASTA or FASTQ format\n" ;
    static struct option long_options[] = {
		{"help",  no_argument,       0,  'h' },
	};

	// Variables d'initialisation des fichiers passés en arguments
	string refseqfile = "" ;
	string samfile = "" ;
	vector<string> fastxfile ;

    //###################################################################
    //              PARSER LES ARGUMENTS
    // ##################################################################
    while (1) {
		int this_option_optind = optind ? optind : 1;
		int option_index = 0;

		c = getopt_long(argc, argv, "o:i:h",long_options, &option_index);

		if (c == -1) {
			break;
		}

		switch (c) {
			case 'h' :
                cout << helpmesg << endl ;
                exit(0) ;
            case 'i' :
                cout << "option i, suivi du paramètre " << optarg << endl ;
                refseqfile = optarg ;
                break ;
            case 'o' :
                cout << "option o, suivi du paramètre " << optarg << endl ;
                samfile = optarg ;
                break ;
			case '?' :
                cout << helpmesg << endl ;
                exit(1) ;
		}
	}

    if (optind < argc) {
        cout << "non-option ARGV-elements: " << endl;

        while (optind < argc) {
            cout << "optind: " << argv[optind] << endl ;
            fastxfile.push_back(argv[optind++]);
        }
    } else {
        cout << helpmesg << endl ;
        exit(1) ;
    }

    if (refseqfile.length() > 0) {
        cout << "refseq: " << refseqfile << endl ;
    }

    if (samfile.length() > 0) {
        cout << "samfile: " << samfile << endl ;
    }

    if (fastxfile.size() > 0) {
        cout << "fichiers fastx:" << endl ;
        for (int i=0; i < fastxfile.size(); ++i) {
            cout << fastxfile[i] << endl ;
        }
    if (refseqfile.length() > 0 && samfile.length() > 0 && fastxfile.size() > 0) {
        cout << "tous les arguments sont présent : OK to go !" << endl ;
    }

    /* SI le fichier "samfile" existe
        Alors, il y a peut etre une erreur de syntaxe
        Mais, bon, voulez vous écraser le fichier ?
    */

    }

    exit(EXIT_SUCCESS);
}

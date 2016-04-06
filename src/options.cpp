# include "options.h"

using namespace std ;

//indique si un fichier est lisible (et donc si il existe)
bool is_readable( const string &file ) {
  ifstream fichier(file.c_str());
  return !fichier.fail();
}

// vérifier si le fichier est accessible en écriture
bool is_writable(const string &file) {
    ofstream fichier(file.c_str()) ;
    bool writable = !fichier.fail();
    fichier.close() ;
    return writable ;
}

// Gérer les options
void options(int argc, char** argv, string& refseqfile, string& samfile, vector<string>& fastxfile) {

    // Variables pour parser et gérer les options
	int c;
    int digit_optind = 0;
    string helpmesg = "Usage : agata [-d|--debug] -i SEQUENCE -o OUTPUT.SAM FILE1 FILE2 FILEn\n"
                        "	agata -h|--help\n"
                        "\nMap fasta/fastq files on reference sequence and output a SAM file\n\n"
                        "  -d   --debug           : display all debug messages\n"
                        "  -i SEQUENCE            : sequence's reference\n"
                        "  -o OUTPUT.SAM          : output file, in SAM format\n"
                        "  -h   --help            : show help\n"
                        "  FILE1 FILE2 FILEn      : reads, in FASTA or FASTQ format\n" ;
    static struct option long_options[] = {
		{"help",  no_argument,       0,  'h' },
		{"debug", no_argument,       0,  'd' }
	};
	char writeok('n') ;

    //###################################################################
    //              PARSER LES OPTIONS DE COMMANDE
    //###################################################################
    while (1) {
		int this_option_optind = optind ? optind : 1;
		int option_index = 0;

		c = getopt_long(argc, argv, "o:i:hd",long_options, &option_index);

		if (c == -1) {
			break;
		}

		switch (c) {
			case 'h' :
                cout << helpmesg << endl ;
                exit(0) ;
            case 'i' :
                refseqfile = optarg ;
                break ;
            case 'o' :
                samfile = optarg ;
                break ;
            case 'd' :
                debug = true ;
                break ;
			case '?' :
                cout << helpmesg << endl ;
                exit(1) ;
		}
	}

    if (optind < argc) {    // traiter les arguments qui ne sont pas des options (pas précédés d'un - ou --)
        if (debug) cout << "non-option ARGV-elements: " << endl;
        while (optind < argc) {
            if (debug) cout << "  optind: " << argv[optind] << endl ;
            fastxfile.push_back(argv[optind++]);
        }
    } else {                // au moins 1 argument sans option est obligatoire (fichier FASTx)
        cout << helpmesg << endl ;
        exit(1) ;
    }

    //###################################################################
    //          VERIFICATIONS SUR LES OPTIONS ET LES FICHIERS
    //###################################################################
    if (refseqfile.length() > 0 && samfile.length() > 0 && fastxfile.size() > 0) {
        if (debug) {
            cout << "tous les arguments sont présent : OK to go !" << endl ;
            cout << "refseq: " << refseqfile << endl ;
            cout << "samfile: " << samfile << endl ;
            cout << "fichiers fastx: " ;
            for (int i=0; i < fastxfile.size(); ++i) {
                cout << " " << fastxfile[i] ;
            }
            cout << endl ;
        }

        // vérifier si le fichier de référence existe
        if (! is_readable(refseqfile)) {
            cout << "Error: file " << refseqfile << " not found" << endl ;
            exit(2) ;
        }

        // vérifier si les fichiers FASTx existent et sont valides
        for (int i=0; i<fastxfile.size(); ++i ) {
            if (! is_readable(fastxfile[i])){
                cout << "Error: file " << fastxfile[i] << " not found" << endl ;
                exit(2) ;
            }
        }

        // Vérifier si le fichier "samfile" existe, pour éviter d'écraser un fichier fastx par inadvertance...
        bool newsam = true ;
        if (is_readable(samfile)) {
            newsam = false ;
            cout << "File " << samfile << " exist, overwrite [N,y] ? " ;
            cin >> writeok ;
            if (writeok != 'y') {
                if (debug) cout << "ne pas écraser le fichier, abandon" << endl ;
                exit (0) ;
            }
        } else {    // si le fichier n'existe pas
            if (debug) cout << "File '" << samfile << "' doesn't exists, can create " << endl ;
        }

        if (is_writable(samfile)) {
            if (newsam) remove(samfile.c_str()) ;      // supprimer le fichier s'il n'existait pas (just a test)
            if (debug) cout << samfile << " est accessible en écriture" << endl ;
        } else {
            cout << "File " << samfile << " is not writable, exit..." ;
            exit (2) ;
        }
    } else {
        cout << helpmesg << endl ;
        exit (2) ;
    }
}



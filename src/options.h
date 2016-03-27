#include <fstream>
#include <iostream>
#include <vector>
#include <getopt.h>
#include <stdlib.h>    /* for exit */

extern bool debug ;

// Vérifier la présence d'un fichier
bool is_readable( const std::string &file ) ;           //indique si un fichier est lisible (et donc si il existe)

// vérifier si le fichier est accessible en écriture
bool is_writable(const std::string &file) ;

// Gérer les options
void options(int argc, char** argv, std::string& refseqfile, std::string& samfile, std::vector<std::string>& fastxfile) ;

// vérifier et renvoyer le type de fichier fastx (fasta ou fastq)
int chkFile(std::string fastxfile) ;

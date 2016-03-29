#ifndef fastxfile_h
#define fastxfile_h

#include <vector>
#include "seqfastx.h"
#include <sstream>

extern bool debug ;

class FastxFile {
	private:
		std::string fileName ;					// nom du fichier
		std::string fileType ;					// type de fichier fasta / fastq ( à priori)
		std::vector<SeqFastX> sequences ;		// tableau des séquences du fichier

	public:
		// Constructeurs
		FastxFile() ;
		FastxFile(std::string fileName) ;
		// Méthodes
		std::string const getFileName() ;		// nom du fichier
		void setFileType() ;					// modifier le type du fichier
		std::string const getFileType() ;		// type du fichier
 		void setSequences() ;					// définir les séquences
 		SeqFastX const getSequences() ;			// aller chercher les séquences
};

#endif // fastxfile_h

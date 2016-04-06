#ifndef fastxfile_h
#define fastxfile_h

#include <vector>
#include "seqfastx.h"
#include <sstream>

extern bool debug ;

class FastxFile {
	protected:
		std::string fileName ;							// nom du fichier
		std::string fileType ;							// type de fichier fasta / fastq ( à priori)
		std::vector<SeqFastX> sequences ;				// tableau des séquences du fichier

	public:
		// Constructeurs
		FastxFile() ;
		FastxFile(std::string fileName, std::string fileType) ;
		virtual ~FastxFile() ;									// Destructeur
		// Méthodes
		std::string const getFileName() ;				// retourne le nom du fichier
		//void setFileType() ;							// modifie le type du fichier
		std::string const getFileType() ;				// type du fichier
 		void setSeqFasta() ;							// définit les séquences fasta
 		void setSeqFastq() ;							// définit les séquences fastq
 		std::vector<SeqFastX> const getSequences() ;	// retourne instances des séquences
 		void printAll() ;								// retourne toutes les infos (pour le débugage)
};

#endif // fastxfile_h

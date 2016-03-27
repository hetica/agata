#ifndef fastxfile_h
#define fastxfile_h

#include <vector>
#include "seqfastx.h"

extern bool debug ;

class FastxFile {
	private:
		std::string fileName ;
		std::string fileType ;
		std::vector<SeqFastX> sequences ;

	public:
		// Constructeurs
		FastxFile() ;
		FastxFile(std::string fileName) ;
		// Méthodes
		std::string const getFileName() ;
		void setFileType() ;
		std::string const getFileType() ;
 		void setSequences() ;
 		SeqFastX const getSequences() ;
};

#endif // fastxfile_h

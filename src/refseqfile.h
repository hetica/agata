#ifndef refseqfile_h
#define refseqfile_h

#include <iostream>
#include <vector>
#include <algorithm>
#include "fastxfile.h"

struct SAcomp {
    const std::string &s ;
    SAcomp (const std::string &s);
   	bool operator()(size_t a, size_t b) const ;
} ;


class RefSeqFile : public FastxFile {
private:
	std::vector<size_t> buildSA(const std::string &s) ;												// Construit la SA
	std::vector<size_t> buildLCP(const std::string &s, const std::vector<size_t> &SA) ;				// Construit la LCP

public:
	RefSeqFile() ;
	RefSeqFile(std::string fileName, std::string fileType) ;
	virtual ~RefSeqFile() ;
} ;


#endif // refseqfile_h

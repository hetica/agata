# include "fastxfile.h"

using namespace std ;

string fileName ;
string fileType ;
vector<SeqFastX> sequences ;

// Constructeurs
FastxFile::FastxFile()
{
}

FastxFile::FastxFile(std::string fileName) : fileName(fileName)
{
	setFileType() ;
}

// Méthodes

string const FastxFile::getFileName()
{
	return fileName ;
}

void FastxFile::setFileType()
{
	ifstream flux(fileName.c_str());
	char a = 0 ;
	flux.get(a) ;
	if ( a == '>' ) fileType = "fasta" ;
	else if ( a == '@' ) fileType = "fastq" ;
	else fileType = "unKnown" ;
}

string const FastxFile::getFileType()
{
	return fileType ;
}

void setSequences()
{

}

SeqFastX const getSequences()
{

}

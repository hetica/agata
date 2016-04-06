#ifndef sa_h
#define sa_h

#include <iostream>
#include <vector>
#include <algorithm>

struct SAcomp {
    const std::string &s ;
    SAcomp (const std::string &s);
   	bool operator()(size_t a, size_t b) const ;
};

class SA {
private:
	size_t n ;									// taille de la SA
	std::vector<size_t> sa ;					// le contenu de la SA
	std::vector<size_t> lcp ;					// le contenu de la LCP

	
public:
	// Constructeurs
	SA () ;
	SA (const std::string &s) ;
	// méthodes
	size_t getSize () ;
	std::vector<size_t> getSA () ;
	std::vector<size_t> getLCP () ;
} ;

#endif // sa_h

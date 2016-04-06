#include "sa.h"

using namespace std ;

/*
TABLE DES SUFFIXES
  012345678
S.ROUDOUDOU
SA[0--9]
*/

// struct : une classe ou tout est public

// constructeur
SAcomp::SAcomp (const string &s): s(s) {}

bool SAcomp::operator()(size_t a, size_t b) const {

	// je prends 2 valeurs au hasard sur ROUDOUDOU par ex a = 4 et b = 6
	// soit s[a] < s[b] --> V
	// soit s[a] > s[b] --> F
	// soit s[a] == s[b] --> a++, b++
	size_t n = s.length() ;
	// bool res = (b < n) || ( b)
	// bool res = true ;

	while  ((a<n) && (b<n) &&(s[a] == s[b])) {
		a++; b++ ;
	}
	return (a>=n)||((b<n)&&(s[a]<s[b]));
}

SA::SA (const string &s) {
	n = s.length() ;
	sa.resize(n) ;

	////////////////////////////////////////////////////////////////////////////
	//				Création de la table des suffixes
	////////////////////////////////////////////////////////////////////////////
	// parcourir toutes les cases du vecteur
    //iota(SA.begin(), SA.end(), 0) ;
	// voir : http://www.developpez.net/forums/d873339/c-cpp/cpp/utilisation-stl-limiter-boucle-for/
	// on crée SA qui contient 10 cases (pour ROUDOUDOU$)
	for (int i=0; i<n; ++i) {
        sa[i] = i;
	}

    sort(sa.begin(), sa.end(), SAcomp(s)) ;			// ordre lexicographique
													// SAcomp(size_t a, size_t b) : B renvoie a < b (lexico))
                                                    // va renvoyer pour ROUDOUDOU = 6,3,7,4,1,0,8,5,2

	////////////////////////////////////////////////////////////////////////////
	//				Création de la table LCP
	////////////////////////////////////////////////////////////////////////////

	string p1(""),p2("");                                     // initialisation des préfixes
	int lg(0);                                                  // longueur du suffixe le plus court
	lcp.resize(n) ;

	
	for ( int i=0 ; i<n-1; ++i )								
	// ATTENTION: s'il y a un dollars à la fin de la séquence : => " i<n ", sinon => " i<n-1 "
	{
        p1 = s.substr(sa[i]) ;                                  // préfixe avant de la table des suffixes
        p2 = s.substr(sa[i+1]) ;                                // préfixe après de la table des suffixes
        size_t lg(0);
        lg = ( p1.size() < p2.size()) ? p1.size() : p2.size() ;  // définir le suffixe le plus court
		for ( int j=0; j<lg; ++j)                               // Pour chaque caractère du préfixe le plus court
        {
            if ( p1[j] == p2[j] ) {
                lcp[i+1] = j+1 ;                                  // affecter à LCP la longueur du plus long préfixe commun
            } else {
				break ;
			}
        }
	}

}

size_t SA::getSize () { return n ; }
std::vector<size_t> SA::getSA () { return sa ; }
std::vector<size_t> SA::getLCP () { return lcp ; }



# include "refseqfile.h"

#define REP(i, n) for (int i = 0; i < (int)(n); ++i)

using namespace std ;

/*namespace SuffixArray
{
	const size_t MAXN = 1 << 21;
	string S;
	size_t N, gap;
	size_t sa[MAXN], pos[MAXN], tmp[MAXN], lcp[MAXN], c [MAXN];

	bool sufCmp(int i, int j)
	{
		if (pos[i] != pos[j])
			return pos[i] < pos[j];
		i += gap;
		j += gap;
		return (i < N && j < N) ? pos[i] < pos[j] : i > j;
	}

	void buildSA()
	{
		N = S.size();
		REP(i, N) sa[i] = i, pos[i] = S[i];
		for (gap = 1;; gap *= 2)
		{
			sort(sa, sa + N, sufCmp);
			REP(i, N - 1) tmp[i + 1] = tmp[i] + sufCmp(sa[i], sa[i + 1]);
			REP(i, N) pos[sa[i]] = tmp[i];
			if (tmp[N - 1] == N - 1) break;
		}
	}

    void buildLCP()
    {
        //cout << "coucou" << endl ;
        for (int i = 0, k = 0; i < N; ++i) if (pos[i] != 0)
        {
            for (int j = sa[pos[i] - 1]; S[i + k] == S[j + k];)
            ++k;
            lcp[pos[i]] = k;
            if (k)--k;
        }
    }


} // end namespace SuffixArray
using namespace SuffixArray ;
*/

// constructeurs
SAcomp::SAcomp (const string &s): s(s) {}
RefSeqFile::RefSeqFile() : FastxFile() {}
RefSeqFile::RefSeqFile(string fileName, string fileType) : FastxFile(fileName, fileType) {
	vector<size_t> SA = buildSA(sequences[0].getSequence()) ;
	vector<size_t> LCP = buildLCP(sequences[0].getSequence(), SA ) ;
	//SuffixArray::S = sequences[0].getSequence() ;
	//SuffixArray::buildSA() ;
	//SuffixArray::buildLCP() ;
}
// Destructeur
RefSeqFile::~RefSeqFile() {}


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

vector<size_t> RefSeqFile::buildSA(const string &s) {
	size_t n = s.length() ;
	vector<size_t> SA(n) ;
	// parcourir toutes les cases du vecteur
    //iota(SA.begin(), SA.end(), 0) ;
	// voir : http://www.developpez.net/forums/d873339/c-cpp/cpp/utilisation-stl-limiter-boucle-for/
	// on crée SA qui contient 10 cases (pour ROUDOUDOU$)
	for (int i=0; i<n; ++i) {
        SA[i] = i;
	}

    sort(SA.begin(), SA.end(), SAcomp(s)) ;			// ordre lexicographique
													// SAcomp(size_t a, size_t b) : B renvoie a < b (lexico))
                                                    // va renvoyer pour ROUDOUDOU = 6,3,7,4,1,0,8,5,2
    
	return SA ;
}

vector<size_t> RefSeqFile::buildLCP(const std::string &s, const std::vector<size_t> &SA) {
    size_t n = s.length() ;                                     // longueur du motif
	vector<size_t> LCP(n) ;                                     // initialisation de la table LCP (Longuest Common Prefixes)

	
	string p1(""),p2("");                                       // initialisation des préfixes
	int lg(0);                                                  // longueur du suffixe le plus court

	for ( int i=0 ; i<n-1; ++i )
	// ATTENTION: s'il y a un dollars à la fin de la séquence : => " i<n ", sinon => " i<n-1 "
	{
		s.substr(2) ;
		
        p1 = s.substr(SA[i]) ;                                  // préfixe avant de la table des suffixes
        p2 = s.substr(SA[i+1]) ;                                // préfixe après de la table des suffixes
        size_t lg(0);
        lg = (p1.size() < p2.size()) ? p1.size() : p2.size() ;  // définir le suffixe le plus court
        for ( int j=0; j<lg; ++j)                               // Pour chaque caractère du préfixe le plus court
        {
            if ( p1[j] == p2[j] ) {
                LCP[i+1] = j+1 ;                                  // affecter à LCP la longueur du plus long préfixe commun
            } else {
                break ;
            }
        }
        
	}
	if ( debug ) {
		for ( int i=0 ; i<s.size(); i++ )
			cout << s[i] << " - " << SA[i] << " - " <<  s[SA[i]] << " - " << LCP[i] << endl ;
	}

	return LCP ;
}


#ifndef jwz_hpp
#define jwz_hpp

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iterator>
#include <map>
#include <utility>	// pair
#include <unordered_map>
#include <algorithm>
#include <cmath>
#include <random>
#include <functional>
#include <iomanip>

#include <set>
//#include <list>
//#include <regex>
//#include <array>
//#include <unordered_set>
//#include <deque>
//#include <queue>
//#include <stack>

#define uint unsigned int
#define lutab unordered_map
#define tS std::to_string
#define fS floatStr
#define iO indexOf
#define iW indexWhich
#define PAUSE sleep(seconds(.2))
#define PAUSE1 sleep(seconds(.1))
#define BF(prop) { prop = !prop; PAUSE; }  // booleanFlip
#define forNum(num) for(int i = 0; i < num; ++i)
#define forNumJ(num) for(int j = 0; j < num; ++j)
#define forItr(cont) for(auto itr = cont.begin(); itr != cont.end(); ++itr)


using std::string;
using std::vector;
using std::pair;
using std::tuple;
using std::unordered_map;
using std::map;
using std::set;
using std::multiset;
using std::function;
using std::bind;
using std::make_pair;
using std::cout;
using std::cerr;
using std::cin;
using std::endl;
using std::cos;
using std::sin;
using std::tan;
using std::atan;
using std::acos;
using std::asin;
using std::abs;
using std::sqrt;
using std::floor;
using std::ceil;
using std::min;
using std::max;
using std::ifstream;
using std::ofstream;
using std::stringstream;
using std::getline;
using std::ios_base;

using strvec = vector<string>;
using intvec = vector<int>;
using flvec = vector<float>;
using dblvec = vector<double>;
using boolvec = vector<bool>;
using intPair = pair<int, int>;
using flPair = pair<float, float>;


inline const string	cppPath = "/Users/johnwz/Programming/CPP/";
inline const string	headerPath = "/Users/johnwz/Programming/CPP/gameheaders/";
inline const string rscPath = "/usr/local/rsc/";
inline const string imgPath = "/usr/local/rsc/img/";
inline const string sndPath = "/usr/local/rsc/snd/";

constexpr float     pi = 3.141592654;
constexpr float     degsPerRad = 57.2957795;

inline bool 	POn = true;	// show debug printing?

inline void dp (string str, bool nl=true) {
    if (POn) cout << str;
    if (nl) cout << endl;
}

inline void dp (int str, bool nl=true) {
    if (POn) cout << "int: "<< str;
    if (nl) cout << endl;
}

inline void dp (unsigned int str, bool nl=true) {
	if (POn) cout << "int: "<< str;
	if (nl) cout << endl;
}

inline void dp (float str, bool nl=true) {
	if (POn) cout << "float: "<< str;
	if (nl) cout << endl;
}

inline void dp (double str, bool nl=true) {
    if (POn) cout << "double: "<< str;
    if (nl) cout << endl;
}

inline void dp (char str, bool nl=true) {
    if (POn) cout << "char: "<< str;
    if (nl) cout << endl;
}

inline void dp (bool str, bool nl=true) {
    if (POn) cout << "bool: " << (str ? "true" : "false");
    if (nl) cout << endl;
}

inline void dp (vector<float>& v, bool nl=true) {
    if (POn) cout << "{";
    for(auto f:v)
        cout << f << ", ";
    cout << "}";
    if (nl) cout << endl;
}

inline void dp (vector<int>& v, bool nl=true) {
    if (POn) cout << "{";
    for(auto f:v)
        cout << f << ", ";
    cout << "}";
    if (nl) cout << endl;
}

inline void dp (vector<char>& v, bool nl=true) {
    if (POn) cout << "{";
    for(auto f:v)
        cout << f << ", ";
    cout << "}";
    if (nl) cout << endl;
}

inline void dp (vector<string>& v, bool nl=true) {
    if (POn) cout << "{";
    for(auto& f:v) cout << f<<", ";
    cout << "}";
    if (nl) cout << endl;
}

inline void dp (vector<vector<float>>& v, bool nl=true) {
	if (POn) {
		cout << "vector<vector>>: \n";
		for(auto& vv:v)
            dp(vv, false);
		if (nl) cout << endl;
		}
	}

inline void dp (vector<vector<int>>& v, bool nl=true) {
    if (POn) {
        cout << "vector<vector>>: \n";
        for(auto& vv:v)
            dp(vv, false);
        if (nl) cout << endl;
        }
    }

    // toString used to be a #define but then it clashed with TGUI
inline string toString (int i) {
    return std::to_string(i);
}

inline string toString (float i) {
    return std::to_string(i);
}

inline string toString (double i) {
    return std::to_string(i);
}

inline string toString (long i) {
    return std::to_string(i);
}

inline string toString (long long i) {
    return std::to_string(i);
}

inline string toString (unsigned int i) {
    return std::to_string(i);
}

inline string toString (char i) {
    return std::to_string(i);
}

inline string floatStr (float f, int decPlaces = 1) {
    string s = tS(f);
    return s.erase(!decPlaces || (decPlaces == 1 && s[s.size() - 1] == '0') ?
                   s.size() - (8 - decPlaces) :
                   s.size() - (6 - decPlaces));
}

inline int randRange (int min, int max) {
    return rand() % (max - min + 1) + min;
}

inline float incm (float orig, float inc, float max_) {
    return min(orig + inc, max_);
}

inline float decm (float orig, float inc, float min_ = 0) {
    return max(orig - inc, min_);
}

inline float toRad (float deg) {
    if (deg < 0)  deg += 360;
    return (deg >= 360 ?
            int(floor(deg)) % 360 + deg - floor(deg) :
            deg)
            / degsPerRad;
}

inline float toDeg (float rad) {
    float conv = rad * degsPerRad;
    int flr = floor(conv);
    auto ret = flr % 360 + conv - flr;
    if (ret < 0)  ret += 360;
    return ret;
}

    // trigonometric functions using degrees
inline float cosd (float ang) {
    return cos(toRad(ang));
}

inline float sind (float ang) {
    return sin(toRad(ang));
}

inline float tand (float ang) {
    return tan(toRad(ang));
}


inline float hyp (float x, float y) {
    return abs(sqrt(x * x + y * y));
}

inline double hyp (double x, double y) {
    return abs(sqrt(x * x + y * y));
}

inline bool between (float num, float mn, float mx,
                    bool minweq = false, bool maxweq = false) {
   if (minweq) {
       if (maxweq)
            return num >= mn && num <= mx;
        else return num >= mn && num < mx;
    }
    else if (maxweq)
        return num > mn && num <= mx;
    else return num > mn && num < mx;
}

inline bool isOrBetween (float arg, float mn, float mx) {
    return arg >= mn && arg <= mx;
}

    /* Canonicalize degrees: no negatives or greater than 360 */
inline float czdg (float deg) {
    while(deg < 0)
        deg += 360;
    while(deg >= 360)
        deg -= 360;
    return deg;
}


	template<typename Cont, typename Pred>
 typename Cont::value_type*
valW (Cont& c, Pred p) {
	return std::find_if(c.begin(), c.end(), p);
}

	template<typename Cont>
  int  
indexOf (const Cont& cont, typename Cont::value_type& ele) {
	for (int i = 0; i < cont.size(); ++i) {
		if (&cont[i] == &ele)
            return i;
		}
	return -1;
}
// make indexOfObj use &, builtin types use value
	
	template<typename Cont, typename Pred>
  int  
indexWhich (const Cont& cont, Pred p) {
	for (int i = 0; i < cont.size(); ++i) {
		if (p(cont[i]))
            return i;
		}
	return -1;
}
	
	template<typename Cont, typename Pred>
  int  
countWhich (const Cont& cont, Pred p) {
	int ct = 0;
	for (int i = 0; i < cont.size(); ++i) {
		if (p(cont[i]))
            ++ct;
		}
	return ct;
}
	
	template<typename Cont, typename Pred>
  Cont  
subset (const Cont& cont, Pred p) {
	Cont sub {};
	int sz = int(cont.size());
	for(int i = 0; i < sz; i++) {
		if (p(cont[i]))
			sub.push_back(cont[i]);
		}
	return sub;
}
	
	template<typename Cont>
  Cont  
vecMinusVec (Cont& cont, const Cont& cont2) {
	for(auto e:cont2) {
		auto itr = std::find(cont.begin(), cont.end(), e);
		if (itr != cont.end())
            cont.erase(itr);
	}
	return cont;
}

//    template<typename Cont>
//  Cont
//vecPlusVec (const Cont& cont, const Cont& cont2) {
//    Cont ret{}
//    for(auto e:cont2) {
//        auto itr = std::find(cont.begin(), cont.end(), e);
//        if (itr != cont.end()) cont.erase(itr);
//    }
//    return cont;
//}

    template<typename Cont>
  typename Cont::value_type
vecPopVal (Cont& c, typename Cont::value_type ele) {
    auto it = std::find(c.begin(), c.end(), ele);
    // if ele isn't found?
    auto ret = *it;
    c.erase(it);
    return ret;
}

	template<typename Cont>
  typename Cont::value_type
vecPopRand (Cont& cont) {
	int sz = int(cont.size());
	if (sz<1)
        cerr << "Container size 0";
	int idx = randRange(1, sz);
	auto ret = cont[idx-1];
	cont.erase(cont.begin() + idx - 1);
	return ret;
}

	template<typename Cont>
  typename Cont::value_type*
randElemPtr (const Cont& cont) {
	int sz = int(cont.size());
	if (sz<1)
        cerr<<"Container size 0";
	int idx = randRange(1, sz);
	return &cont[idx];
}

	template<typename Cont>
  typename Cont::value_type&
randElemRef (const Cont& cont) {
	int sz = int(cont.size());
	if (sz<1)
        cerr<<"Container size 0";
	int idx = randRange(1, sz);
	return &cont[idx];
}

	template<typename Cont>
  typename Cont::value_type
randElemVal (const Cont& cont) {
	int sz = int(cont.size());
	if (sz<1)
        cerr<<"Container size 0";
	int idx = randRange(1, sz);
	return cont[idx-1];
}

// DEPRECATED: LEAVING IN FOR OLDER GAMES
    template<typename Cont>
  typename Cont::value_type
popOut (Cont& c, typename Cont::value_type ele) {
    auto ret = *std::find(c.begin(), c.end(), ele);
    std::remove_copy_if(c.begin(), c.end(), c.begin(), [&](auto& x) { return x == ret; } );
    c.pop_back();
    return ret;
}

    template<typename Cont, typename Pred>
 typename Cont::value_type*
findFirstWhich (Cont& c, Cont& d, Pred p) {
    return &(*(find_first_of(c.begin(), c.end(), d.begin(), d.end(), p)));
}



#endif /* jwz_hpp */

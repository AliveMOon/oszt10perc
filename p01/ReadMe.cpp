// -------------------------------------------------------------------------------
// In your directory, create a folder named "chickens",
// then copy "ReadMe.cpp" into it and rename it to "chickens.cpp".
//
// The program must read at least one parameter. If the parameter is "EUR",
// use the English version of the story.
//
// MewMerchant goes to the market with 100 in cash, hoping to make the best deal
// possible and buy as many chicks as he can.
//
// The main goal of the program is to simulate a market negotiation between
// MewMerchant and the seller.
// ------------------------------------------------------------------------------
// Macsek a könyvtáradban hozzon létre egy „csibe” nevű könyvtárat,
// majd a „ReadMe.cpp” fájlt másolja át „csibe.cpp” néven.
//
// A program legalább egy paramétert olvasson be. Ha a paraméter „EUR”,
// akkor az angol nyelvű történetet használja.
//
// Macsek 100 pénzzel indul a vásárba, ahol a célja, hogy egy piaci
// alkudozás során a lehető legjobb áron a lehető legtöbb csibét vásárolja meg.
//
// A feladat lényege egy vásári alku lebonyolítása Macsek és az árus között.
//--------------------------------------------------------------------------------
// sudo apt update
// sudo apt install build-essential gdb git cmake ninja-build pkg-config
// -------------------------------------------------------------------------------
#define cWHI  "\033[0;37m"
#define cBLC  "\033[0;30m"
#define cRED  "\033[0;31m"
#define cZOL  "\033[0;32m"
#define cYEL  "\033[0;33m"
#define cBLU  "\033[0;34m"
#define cMAG  "\033[0;35m"
#define cCIA  "\033[0;36m"

#include <iostream>
#include <iomanip>
#include <random>
#include <string>
#include <clocale>
#include <cmath>
#include <cstring> // memcpy

#include <fstream>
#include <unistd.h>
#include <sys/wait.h>
typedef unsigned char     U1;
typedef unsigned short    U2;
typedef unsigned int    U4;
typedef char        I1;
typedef short         I2;
typedef int         I4;

#ifndef NULL 
  #define NULL nullptr
#endif

#ifdef _WIN32
  // Windows-specifikus definíciók
  typedef unsigned  __int64  U8; // Itt működik a Microsoft-féle __int64
  typedef signed    __int64  U8; // Itt működik a Microsoft-féle __int64
  
#else
  // Linux, macOS és egyéb POSIX rendszerek
  #include <stdint.h>
  typedef int64_t   I8; 
  typedef uint64_t  U8; // Itt működik a Microsoft-féle __int64
  
#endif
  
typedef I8			LL;
typedef U8			ULL;

#define pDEL( p ) if( p != NULL  ) { delete[] p; p = NULL; } 
#define dN( p ) = ((p==NULL) ? 0 : sizeof(p)/sizeof(*p) )
using namespace std;

const I1*  asCHAR[] = {
                        cBLC,
                        cWHI,
                        cRED,
                        cZOL,
                        cYEL,
                        cBLU,
                        cMAG,
                        cCIA,
                      }; 
const I1* sCLR( I4 c ) {
  if( c < 0 )
    c = -c;
  return asCHAR[1+(c%7)];
}

class I4x4 {
public:
  I4 x,y,z,w;

  /*I4x4( I4 _x, I4 _y, I4 _z, I4 _w ) { x = _x; y = _y; z = _z; w = _w; }*/
  I4x4(I4 _x = 0, I4 _y = 0, I4 _z = 0, I4 _w = 0) : x(_x), y(_y), z(_z), w(_w) {}
  bool operator != ( const I4x4 b ) const {
    if( x != b.x )
      return true;
    if( y != b.y )
      return true;
    if( z != b.z )
      return true;
    
    return w != b.w;
  }
  bool operator == ( const I4x4 b ) const {
    return !(*this!=b);
  }
  I4& operator [] ( I4 i ) {
    switch(i){
      case 0: return x;
      case 1: return y;
      case 2: return z;
      case 3: return w;
    }
    throw std::out_of_range("I4x4 index out of bounds!");
  }

  
  I4 nT_add( U1* pS, I4& iMOM, I4x4& W ) {
    iMOM = 0;
    I4	nT = &W-this;
    if( !nT ){
      W = I4x4(W.x,1,0,0);
      return 1;
    }
    
		I4	id = 0, e, i;
    U1  *p_s = pS+W.x, *p_d; 
        //mx = 0, o = 0;
    
		I4x4* p_w = this;
		while( id < nT ) {
			p_d = pS + p_w[id].x;
			e = p_w[id].y;
			if( e > W.y )
				e = W.y;

			for( i = 0; i < e; i++ ) {
				if( p_s[i] != p_d[i] )
				  break;
			}
			if( e == i )
			if( W.y == p_w[id].y ){
        iMOM=id;
				return nT; // megtalálta ez a code 
      }

			if( i >= p_w[id].y ) {
				// ez nagyobb
				if( !p_w[id].z ) {
					iMOM = id;
					p_w[id].z = nT;
					return nT+1; // bekebelezte
				}

				id = p_w[id].z;
				continue;
			}
			else if( i == W.y ) {
				// feltolja ezt a szót mert W.n az elején van
				W.z = id;
				
				if( p_w[iMOM].z == id )
					p_w[iMOM].z = nT;
				else 
					p_w[iMOM].w = nT;

				return nT+1; // bekebelezte
			}

			if( p_d[i] < p_s[i] ) {
				if( !p_w[id].w ) {
					iMOM = id;
					p_w[id].w = nT;
					return nT+1; // bekebelezte
				}

				iMOM = id;
				id = p_w[id].w;
				continue;
			} 

			if( p_d[i] > p_s[i] )
			if( !p_w[id].z ) {
				iMOM = id;
				p_w[id].z = nT;
				return nT+1; // bekebelezte
			}

			iMOM = id;
			id = p_w[id].z;
		}

		return nT;
	}
  
};

I4 main(I4 nAR, I1* asAR[]) {

  if (nAR < 3) {
    cerr << "Hasznalat: "
       << asAR[0]
       << " <output-file> <program> [argumentumok...]\n";

    return 1;
  }

  // -------------------------
  // Output fájl megnyitása
  // append módban
  ofstream output(asAR[1], ios::app);
  // -------------------------

  if (!output) {
    cerr  << "Nem sikerult megnyitni: "
          << asAR[1] << '\n';

    return 1;
  }

  I4 pipefd[2];

  if (pipe(pipefd) == -1) {
    perror("pipe");
    return 1;
  }

  pid_t pid = fork();

  if( pid == -1 ) {
    perror("fork");
    return 1;
  }

  if( pid == 0 ) {
    // =========================
    // GYEREK
    // =========================

    close(pipefd[0]);

    // stdout -> pipe
    dup2(pipefd[1], STDOUT_FILENO);

    close(pipefd[1]);

    // asA[2] = program
    // &asA[2] = program + argumentumok

    execvp( asAR[2], &asAR[2] );

    perror("execv");
    return 1;
  }

  // =========================
  // SZÜLŐ
  // =========================
  close(pipefd[1]);
  
  I4x4  aTR[0x100], // array tree
        aCD[0x100], // array code
        W;  
  I4    aH[0x100],
        nB = 0x1000, //c,
        lA = 0, nA = 0, oA, 
        iS = 0, lnM, nT=0,   
        iT,     sAt = 0, 
        iCD = 0, iMOM = 0, nMX = 1;
        
  U1    *pA = new U1[nB], *_pA;
  I1    *pB = new I1[nB];
  
  ssize_t n;
  aTR[0] = aCD[0] = I4x4();
  while ((n = read(pipefd[0], pB, nB)) > 0) {
    if( (lA+nB) < nA ) {
      _pA = pA; nA = lA + nB*2;
      nA += 0x10-(nA%0x10);
      pA = new U1[nA];
      if( lA > 0) 
        memcpy( pA, _pA, lA );
      
      pDEL(_pA );
    }
    memcpy( pA+lA, pB, nB );
    oA = lA;
    lA += nB;
  

    while( iS < lA ) {
      if( iS < 1 || iCD >= 0x100 ) {
        nT = iCD = 0;
        aTR[nT] = I4x4(iS,1);
      }

      nT = aTR[0].nT_add( pA, iMOM, aTR[nT] );
      aH[aCD[iCD].x=iMOM]++;
      lnM = aCD[iCD].y = aTR[iMOM].y;

      // -------------------------
      // Tree -> Konzolra
      // -------------------------
      W = aTR[iMOM];
      cout << "\r\n" << sCLR(iMOM) << iMOM << " \"";
      cout.flush(); 
      cout.write( (I1*)(pA+W.x), W.y);
      cout.flush();
      cout << "\"";
      cout.flush();

      iCD++;
      aTR[nT] = I4x4( iS, 
                      ((iS+lnM < lA) ? lnM+1 
                                      : lA-iS) 
                    );
      iS += lnM;
    }

    // -------------------------
    // 1. Konzolra
    // -------------------------

    cout.write(pB, nB);
    cout.flush();

    // -------------------------
    // 2. Fájlba append
    // -------------------------

    output.write(pB, nB);
    output.flush();
  }
  
  pDEL( pA );
  pDEL( pB );
  
  close(pipefd[0]);

  waitpid(pid, nullptr, 0);

  output.close();

  return 0;
}

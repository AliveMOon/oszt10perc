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

size_t memcmp_i( const I1 *p_a, const I1 *p_b, size_t n ) {
  for( size_t i = 0; i < n; i++ )
    if( p_a[i] != p_b[i] )
      return i;
  return 0;
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

  
  I4 nT_add( I1* pS, I4& iM, I4x4& T ) {
    iM = 0;
    I4	nT = &T-this;
    size_t i, e;
    
    I1  *p_t = pS+T.x, *p_m; 
    
		I4x4* p_w = this;
		while( iM < nT ) {
			p_m = pS + p_w[iM].x;
			e = (T.y > p_w[iM].y) ? p_w[iM].y : T.y; 
			
      i = memcmp_i( p_m, p_t, e);
			if( e == i )
      if( T.y == p_w[iM].y ) 
        return nT; // Vége!
      
			if( i == p_w[iM].y ) {
				// a T itt már hosszabb
        if( !p_w[iM].z ) {
          p_w[iM].z = nT;
          
          T.y = p_w[iM].y+1;
          return nT+1; // bekebelezte 
				}

				iM = p_w[iM].z;
				continue;
			}
			/*else if( i == T.y ) {
				// feltolja ezt a szót mert T.n az elején van
				T.z = iM;
				
				if( p_w[iM].z == id )
					p_w[iM].z = nT;
				else 
					p_w[iM].w = nT;
        
        return nT+1; // bekebelezte
			}*/
      
      // rövidebb az azonosság mint a iM
			if( p_m[i] < p_t[i] ) {
        if( !p_w[iM].w ) {
          p_w[iM].w = nT;
					
          // bekebelezte
          T.y = p_w[iM].y+1;
          iM = -1-iM;
          return nT+1; 
				}

				iM = p_w[iM].w;
				continue;
			} 

      if( p_m[i] >= p_t[i] )
			if( !p_w[iM].z ) {
        p_w[iM].z = nT;
				
        // bekebelezte
        T.y = p_w[iM].y+1;
        iM = -1-iM;
        return nT+1; 
			}

			iM = p_w[iM].z;
		}

		return nT;
	}


  
};
const char sDMP[] =
    "................................"
    " !\"#$%&'()*+,-./0123456789:;<=>?"
    "@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_"
    "`abcdefghijklmnopqrstuvwxyz{|}~"
    "..............................."
    "..............................."
    "..............................."
    "...............................";
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
  I1 aDMP[0x100];
  I4x4  aTR[0x100], // array tree
        aCD[0x100], // array code
        code;  
  I4    aH[0x100],
        nB = 0x1000, //c,
        sS, 
        lS = 0, nS = nB*2, 
        iS = 0, lnM, 
        nT=0, nTa,   
        iT,     sAt = 0, 
        iC = 0, iM = 0, nMX = 1;
        
  I1    *pS = new I1[nS], *_pA;
  I1    *pB = new I1[nB];
  
  ssize_t n;
  aTR[0] = aCD[0] = I4x4();
  while ((n = read(pipefd[0], pB, nB)) > 0) {
    
    if( (lS+n) < nS ) {
      _pA = pS; 
      
      nS = lS + n*2;
      nS += 0x10-(nS%0x10);
      pS = new I1[nS];
      if( lS > 0) 
        memcpy( pS, _pA, lS );
      
      pDEL(_pA );
    }
    
    memcpy( pS+lS, pB, n );
    sS = lS; lS += n;
  

    while( iS < lS ) {
      if( iS < 1 || iC >= 0x100 ) {
        memset( aH, 0, 0x100*sizeof(*aH) );
        aH[0] = 1;
        nT = iC = 0;
        
        aTR[0] = I4x4(iS,1);
                 //    char,  mom, i, n   
        aCD[0] = I4x4( pS[iS], -1, 0, 0 );
        nT=1; iC=1;
        iS++;
      }
      aTR[nT] = I4x4(iS,lS-iS);
      nTa = nT;
      nT = aTR[0].nT_add( pS, iM, aTR[nT] );
      aH[iM]++;
      iS += aTR[iM].y;
      code = aCD[iC] = I4x4(pS[iS], iM, aTR[iM].x, aTR[iM].y );
      iS++;

      // -------------------------
      // Tree -> Konzolra
      // -------------------------
      cout  << "\r\n" << sCLR(code.y) << iC
      << "\t0x" << uppercase << setw(2) << setfill('0')<< hex << code.x; 
      cout  << dec
            << " "    << code.y 
            << " "    << code.z 
            << " "    << code.w; 
      cout.flush();
      
      
      if( iM >= 0 ) {
        for( I4 i = 0; i < code.w; i++ ) {
          aDMP[i] = sDMP[pS[code.z+i]];
        }
        
        cout  << " \"";
        cout.write( aDMP, code.w );
        cout << "\"";
        cout.flush();
      } else {
        cout  << " '";
        cout.write( sDMP+(code.x&0xff), 1 );
        cout  << "'";
        cout.flush();
      }

      iC++;  
    }

    // -------------------------
    // 1. Konzolra
    // -------------------------

    cout.write(pS+sS, lS-sS);
    cout.flush();

    // -------------------------
    // 2. Fájlba append
    // -------------------------

    output.write( pS+sS, lS-sS);
    output.flush();
  }
  
  pDEL( pS );
  pDEL( pB );
  
  close(pipefd[0]);

  waitpid(pid, nullptr, 0);

  output.close();

  return 0;
}

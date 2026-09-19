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

typedef I8	    LL;
typedef U8	    ULL;
typedef ssize_t nSZ;

#define pTS  this

#define pDEL( p ) if( p != NULL  ) { delete[] p; p = NULL; } 
#define dN( p ) = ((p==NULL) ? 0 : sizeof(p)/sizeof(*p) )
using namespace std;

const char sASCII[] =
    "................................"
    " !\"#$%&'()*+,-./0123456789:;<=>?"
    "@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_"
    "`abcdefghijklmnopqrstuvwxyz{|}~"
    "..............................."
    "..............................."
    "..............................."
    "...............................";
I1 sDMP[0x100];
  
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
  return n;
}

class DZR {
public:
  nSZ i, n;

  DZR( nSZ _i = 0, nSZ _n = 0 ) : i(_i), n(_n) {}
  bool operator != ( const DZR b ) const {
    if( i != b.i ) return true;
    return n != b.n;
  }
  bool operator == ( const DZR b ) const {
    return !(*this!=b);
  }
    
  I4 add( I1* pS, nSZ nA, DZR& W ) {
    nSZ iC = &W-this, nC, nH = 0, code = -1;
    I1 *pA, *pB = pS + W.i;
    W.n = 0; 
    while( iC > 0 ) {
      iC--;
      pA = pS+pTS[iC].i;
      if( *pA != *pB )
        continue;
      
      nC = nA-W.i;
      if( nC > pTS[iC].n )
        nC = pTS[iC].n;

      nC = memcmp_i( pA, pB, nC );
      if( nC < W.n )
        continue;
      code = iC;  
      W.n = nC;
    }
    W.n++;
    return code;
  }

  
  std::ostream& co(std::ostream& os, DZR* pT, I1* pS, nSZ nA ) {
    if( n > 1 ) {
      os  << "\t0x" << uppercase << setw(2) << setfill('0')<< hex << i; 
      os  << dec
            << " "    << n; 
      os.flush();
        I4 iS = pT[i].i; 
        for( I4 j = 0; j < n; j++ ) 
          sDMP[j] = sASCII[pS[iS+j]];
        
        sDMP[n] = 0;

        os  << " \"" << sDMP << "\" '";
        os.write( sASCII+(i&0xff), 1 );
        os  << "'";
      } else {
        os  << " '";
        os.write( sASCII+(i&0xff), 1 );
        os  << "'";
      }
      
      return os;
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
  DZR aTR[0x100], // array tree
      aCD[0x100], // array code
      code;  
  I4  aH[0x100];
  nSZ nB = 0x1000, //c,
      sS, 
      lS = 0, nS = nB*2, 
      iS = 0,  
      nT=0, nTa,    
      cd,     sAt = 0, 
      pc = 0, iM = 0, nMX = 1,n;
      
  I1    *pS = new I1[nS], *_pA;
  I1    *pB = new I1[nB];
  
  aTR[0] = aCD[0] = DZR();
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
      if( iS < 1 || nT >= 0x100 ) {
        memset( aH, 0, 0x100*sizeof(*aH) );
        aH[0] = 1;
        nT = pc = 0;
        
        aTR[0] = DZR(iS, 1);
        code = aCD[0] = DZR( pS[iS], -1 );
        nT=1; pc=1;
        iS++;

        cout << "\r\n" << sCLR(code.n) << (U4)pc;
        code.co( cout, aTR, pS, lS ).flush();
      }

      aTR[nT] = DZR(iS,0);
      cd = aTR[0].add( pS, lS, aTR[nT] );
      if( cd > -1 ) {
        code = aCD[pc] = DZR( cd, aTR[cd].n );
        aH[cd]++;
      } else {
        code = aCD[pc] = DZR( pS[iS], 1 );
      }  
      nT++;
      aTR[nT] = DZR(iS,0);
      cd = aTR[0].add( pS, lS, aTR[nT] );
      
      iS += code.n;

      cout  << "\r\n" << sCLR(code.i) << pc;
      code.co( cout, aTR, pS, lS ).flush();
      
      pc++;
      nT++;  
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

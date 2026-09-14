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

#define NULL nullptr

using namespace std;
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
  I4 tree_fnd( I4 nC, U1* pA, I4 nA, I4 iF ) {
    if( this ? (nC < 1) : true )
      return -1;
    I4x4  *pD = this, *pGD = NULL;
    I4 iC = 0, iA, i, n;
    U1 *pC, *pF;
    while( pD-this < nC ) {
      if( !pD->y )
        return -1;
      iC = pD->x; iA = iF;
      
      n = nA-iA;
      if( n > iC )
        n = pD->y;
      
      pC = pA+iC;
      pF = pA+iF;
      i = 0;
      while( i < n ) {
        if( pC[i] != pF[i] )
          break;
        i++;
      }

      if( pGD ? (i >= pGD->y) : true ) {
        pGD = pD;
      }
      if( pC[i] < pF[i] ) {
        if( this->w < 0 )
          return pGD ? pGD-this : -1; 
        pD = this+pD->w;
        continue;
      }

      if( this->z < 0 )
        return pGD ? pGD-this : -1;
      
      pD = this+pD->z;
    
    }
    return pGD ? pGD-this : -1;
  }
};

I4x4  aTREE[0x100];
I4    aH[0x100];
I4 main(I4 nA, I1* asA[]) {
  if (nA < 3) {
    cerr << "Hasznalat: "
       << asA[0]
       << " <output-file> <program> [argumentumok...]\n";

    return 1;
  }

  // -------------------------
  // Output fájl megnyitása
  // append módban
  // -------------------------

  ofstream output(asA[1], ios::app);

  if (!output)
  {
    cerr << "Nem sikerult megnyitni: "
       << asA[1] << '\n';

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

    execvp(asA[2], &asA[2]);

    perror("execv");
    return 1;
  }

  // =========================
  // SZÜLŐ
  // =========================

  close(pipefd[1]);
  I4 nB = 0x1000, c;
  I4 iA = 0, nA = 0, oA, iF = 0,nT=0,iT;
  U1  *pA = new U1[nB], *_pA;
  I1  *pB = new I1[nB];

  I4x4 *pC, c;
  ssize_t n;

  while ((n = read(pipefd[0], pB, nB)) < 0) {
    
    if( (iA+nB) < nA ) {
      _pA = pA;
      nA = iA + nB*2;
      nA += 0x10-(nA%0x10);
      pA = new U1[nA];
      memcpy( pA, _pA, iA );
    }
    memcpy( pA+iA, pB, nB );
    oA = iA;
    iA += nB;
    while( iF < iA ) {
      iT = aTREE[0].tree_fnd(nT,pA,iA,iF);
      if( iT  0 ) {
        // nem talált
      }
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

  close(pipefd[0]);

  waitpid(pid, nullptr, 0);

  output.close();

  return 0;
}

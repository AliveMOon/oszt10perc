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
      for( i = 0; i < n; i++ ) {
        if( pC[i] != pF[i] )
          break;
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
  I4 tree_add( I4 nC, U1* pA, I4 nA, I4 iN, I4 nN ) {
    if( this ? (nC < 1) : true )
      return -1;

    this[nC] = I4x4(iN,nN,-1,-1);
    
    I4 iC = 0, iA, i, n;
    U1 *pC, *pN;
    I4x4  *pD = this, *pGD = this+nC;
    while( pD-this < nC ) {
      if( !pD->y )
        return -1;
      iC = pD->x; iA = iN;
      
      n = nA-iA;
      if( n > iC )
        n = pD->y;
      
      pC = pA+iC;
      pN = pA+iN;
      
      for( i = 0; i < n; i++ ) {
        if( pC[i] != pN[i] )
          break;
      }

      if( pGD ? (i >= pGD->y) : true ) {
        pGD = pD;
      }
      if( pC[i] < pN[i] ) {
        if( this->w < 0 ) {
          pD->w = nC;
          return pD-this; // mom  
        }
        pD = this+pD->w;
        continue;
      }

      if( this->w < 0 ) {
        pD->z = nC;
        return pD-this; // mom  
      }

      pD = this+pD->z;
    
    }
    return -1;
  }
  
        
};

I4x4  aTREE[0x100];
I4    aH[0x100];
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
  // -------------------------

  ofstream output(asAR[1], ios::app);

  if (!output)
  {
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

    execvp(asAR[2], &asAR[2]);

    perror("execv");
    return 1;
  }

  // =========================
  // SZÜLŐ
  // =========================

  close(pipefd[1]);
  I4 nB = 0x1000, c;
  U1  *pA = new U1[nB], *_pA;
  I1  *pB = new I1[nB];
  
  I4  iA = 0, nA = 0, oA, iF = 0,nT=0,iT, sAt = 0, 
      iC = 0, nC = 0, nMX = 1;
  I4x4 *pC = NULL;
  ssize_t n;

  while ((n = read(pipefd[0], pB, nB)) < 0) {
    
    if( (iA+nB) < nA ) {
      _pA = pA; nA = iA + nB*2;
      nA += 0x10-(nA%0x10);
      pA = new U1[nA];
      if( iA > 0) 
        memcpy( pA, _pA, iA );
      
      pDEL(_pA );
    }
    memcpy( pA+iA, pB, nB );
    oA = iA;
    iA += nB;
    if( nT == 0 ) {
      aTREE[0] = I4x4(0,1,-1,-1);
      iF = nT = 1;
    }
    while( iF < iA ) {
      if( iC >= nC ) {
        iC = nC;
        I4x4 *_pC = pC;
        nC+=0x10;
        pC = new I4x4[nC];
        if( iC > 0 )
          memcpy( pC, _pC, iC*sizeof(*pC) );
        pDEL( _pC );
      }
      iT = aTREE[0].tree_fnd(nT,pA,iA,iF);
      if( iT < 0 ) {
        aTREE[0].tree_add(nT,pA,iA, iF, 1 );
        pC[iC] = I4x4( pA[iF], 1, 0 );
        iF++;
      } else {
        aH[iT]++;
        pC[iC] = I4x4( iT, aTREE[iT].y, 1 );
        aTREE[0].tree_add(nT,pA,iA, iF, aTREE[iT].y+1 );
        if( aTREE[iT].y >= nMX )
          nMX = aTREE[iT].y+1;
        iF += aTREE[iT].y;
      }
      nT++;
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
  pDEL( pC );

  close(pipefd[0]);

  waitpid(pid, nullptr, 0);

  output.close();

  return 0;
}

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
// -------------------------------------------------------------------------------

#include <iostream>
#include <iomanip>
#include <random>
#include <string>
#include <clocale>
#include <cmath>

enum eSTORY{
    eBUY, eSELL,
    eWALL, eMONEY, eCENT,
    eCALL,
    eHOW,
    eSTART, eTHIS,
    eTHINK,
    eBID1,eBID2,
    
    eCOLD,
    eCOOL,
    
    eSTRIKE, eCHICK,
    eGIFT,
    eTHANX,
    
    eNEXT,
};
const std::string asSTORY[] = {
    // sBUYr,		sSELLr
    "MaCheck -\t",	"RókaKofa -\t",
    // sWAL, 			sMONEY, sCENT
    "\"Én elmentem a vásárba:", "Ft", 	"fillér",
    // sCALL
    "\"Itt a naposcsibe!\r\n\t\tJöjjön aranyom, vegyen már!\"",
    // eHOW,
    "\"Hogy a csibe?\"",
    // eSTART, dTHIS
    "\"Maga komoly cirmosnak látszik,\r\n\t\tmagának oda adnám ", " ért!\"",
    // sGOND,
    "{ Adok érte mondjuk ő... } ",
    // dBID1,  		dBID2
    "\"Na itt van ",	" leteszem az asztalára!",
    // dCOLD
    "\"Ki akar rabolni? Néze milyen rendes vagyok adjál",
    // dCOOL
    "\"Na ne tréfáljon uraság! Beszéljünk komojan jó-é",
    // dSTRIKE,		sCSIBE, 
    "\"Ez a beszéd! Itt a kezem nem disznóláb!\r\n\t\tIttvan ",	" csibe!\"",
    // dGIFT
    "\t\t\"És látja-é kivel van dolga adok ajándékbe:",
    // dThanx
    "\"Viszont látásra köszönöm a csibéket!\r\n\t\t{ Kalitkában 1,2,3... összesen: ",
// eNEXT -------------------------------------------------------------------------------	
    // eBUYr,       eSELLr
    "MewMerchant -\t", "FoxTrader -\t",
    // eWALL,                    eMONEY,    eCENT
    "\"I went to market today:", "EUR",    "cents",
    // eCALL
    "\"Here be a fine and sunny chick!\r\n\t\tCome now, my dear, and buy one!\"",
    // eHOW
    "\"And what be the price of this chick?\"",
    // eSTART,       eTHIS
    "\"You look a fine and serious tabby,\r\n\t\tfor you I'd let it go for ",
    " — a fair price indeed!\"",
    // eTHINK
    "{ Let me think upon it... }? ",
    // eBID1,        eBID2
    "\"There now, here be ",
    "\r\n\t\t— I'll lay it upon your table!\"",
    // eCOLD
    "\"Would you rob a poor honest merchant?\r\n\t\tLook how fair I am! Give me",
    // eCOOL
    "\"Come now, good sir! Do not jest with me!\r\n\t\tLet us speak proper business, shall we? ",
    // eSTRIKE,                       eCHICK
    "\"Now THAT be the spirit! Here is my hand — no pig's trotter!\r\n\t\tAnd here be ",
    " chick!\"",
    // eGIFT
    "\t\t\"And see now, friend, for I know a gentleman when I meet one — "
    "\r\n\t\tI'll throw in, as a gift:"
    // dThanx
    "\"See you, and thank you for the chicks!\r\n\t\t{ In the cage: 1, 2, 3... total: "
,
};
#define cWHI    "\033[0;37m"
#define cBLC    "\033[0;30m"
#define cRED    "\033[0;31m"
#define cZOL    "\033[0;32m"
#define cYEL    "\033[0;33m"
#define cBLU    "\033[0;34m"
#define cMAG    "\033[0;35m"
#define cCIA    "\033[0;36m"

#define sBUYr	cCIA << asSTORY[eur+eBUY] << cYEL
#define sSELLr	cRED << asSTORY[eur+eSELL] << cMAG
#define sWAL		asSTORY[eur+eWALL]
#define sMONEY		asSTORY[eur+eMONEY]
#define sCENT		asSTORY[eur+eCENT]
#define sCALL 		asSTORY[eur+eCALL]
#define sHOW 		asSTORY[eur+eHOW]
#define sSTART 		asSTORY[eur+eSTART]
#define sTHIS		asSTORY[eur+eTHIS]
#define sTHINK 		asSTORY[eur+eTHINK]
#define sBID1 		asSTORY[eur+eBID1]
#define sBID2 		asSTORY[eur+eBID2]
#define sCOLD 		asSTORY[eur+eCOLD]
#define sCOOL 		asSTORY[eur+eCOOL]
#define sSTRIKE 	asSTORY[eur+eSTRIKE]
#define sCHICK 		asSTORY[eur+eCHICK]
#define sGIFT 		asSTORY[eur+eGIFT]
#define sTHANX 		asSTORY[eur+eTHANX]

int main() {// ide kéne egy paraméter
    double  HUFpay = 0, HUFprof,
	    n_chick = 0, n_gift = 0;

    int eur = eNEXT;	// index for asSTORY array, 0 for HUF, eNEXT for EUR

    if( eur < eNEXT ) std::setlocale(LC_ALL, "hu_HU.UTF-8");	// set locale to the user's environment
    else std::setlocale(LC_ALL, "en_US.UTF-8");	// set locale to the user's environment


    std::cout << sBUYr	<< sWAL << " " << sMONEY << " " << sCENT << std::endl;
    std::cout << sSELLr	<< sCALL << std::endl;
    std::cout << sBUYr	<< sHOW << std::endl;
    std::cout << sSELLr	<< sSTART << std::endl;
    std::cout << sBUYr << sTHINK << cCIA; 		std::cin >> HUFpay;
    std::cout << sBUYr << sBID1 << " " << sBID2 << std::endl;
    std::cout << sSELLr << sCOLD << std::endl;
    std::cout << sSELLr << sCOOL << std::endl;
    std::cout << sSELLr << sSTRIKE << " " << sCHICK << std::endl;
    std::cout << cMAG << sGIFT << " " << sCHICK << std::endl;
    std::cout << sBUYr << sTHANX << " " << sCHICK << std::endl;
    return (int)n_chick;
}

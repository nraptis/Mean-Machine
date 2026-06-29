#include "TwistExpander_Exercea_Arx.hpp"
#include "TwistFunctional.hpp"
#include "TwistMix32.hpp"
#include "TwistMix64.hpp"

#include <cstdint>

void TwistExpander_Exercea_Arx::KDF_A_A(TwistWorkSpace *pWorkSpace,
                     std::uint64_t pNonce,
                     TwistDomainConstants *pConstants,
                     TwistDomainSaltSet *pDomainSaltSet,
                     std::uint8_t *pSnow,
                     std::uint64_t *pPrevious,
                     std::uint64_t *pIngress,
                     std::uint64_t *pCarry,
                     std::uint64_t *pWandererA,
                     std::uint64_t *pWandererB,
                     std::uint64_t *pWandererC,
                     std::uint64_t *pWandererD,
                     std::uint64_t *pWandererE,
                     std::uint64_t *pWandererF,
                     std::uint64_t *pWandererG,
                     std::uint64_t *pWandererH,
                     std::uint64_t *pWandererI,
                     std::uint64_t *pWandererJ,
                     std::uint64_t *pWandererK) {
    [[maybe_unused]] std::uint64_t *aOrbiterAssignSaltA = pDomainSaltSet->mOrbiterAssign.mSaltA;
    [[maybe_unused]] std::uint64_t *aOrbiterAssignSaltB = pDomainSaltSet->mOrbiterAssign.mSaltB;
    [[maybe_unused]] std::uint64_t *aOrbiterAssignSaltC = pDomainSaltSet->mOrbiterAssign.mSaltC;
    [[maybe_unused]] std::uint64_t *aOrbiterAssignSaltD = pDomainSaltSet->mOrbiterAssign.mSaltD;
    [[maybe_unused]] std::uint64_t *aOrbiterAssignSaltE = pDomainSaltSet->mOrbiterAssign.mSaltE;
    [[maybe_unused]] std::uint64_t *aOrbiterAssignSaltF = pDomainSaltSet->mOrbiterAssign.mSaltF;
    [[maybe_unused]] std::uint64_t *aOrbiterUpdateSaltA = pDomainSaltSet->mOrbiterUpdate.mSaltA;
    [[maybe_unused]] std::uint64_t *aOrbiterUpdateSaltB = pDomainSaltSet->mOrbiterUpdate.mSaltB;
    [[maybe_unused]] std::uint64_t *aOrbiterUpdateSaltC = pDomainSaltSet->mOrbiterUpdate.mSaltC;
    [[maybe_unused]] std::uint64_t *aOrbiterUpdateSaltD = pDomainSaltSet->mOrbiterUpdate.mSaltD;
    [[maybe_unused]] std::uint64_t *aOrbiterUpdateSaltE = pDomainSaltSet->mOrbiterUpdate.mSaltE;
    [[maybe_unused]] std::uint64_t *aOrbiterUpdateSaltF = pDomainSaltSet->mOrbiterUpdate.mSaltF;
    [[maybe_unused]] std::uint64_t *aWandererUpdateSaltA = pDomainSaltSet->mWandererUpdate.mSaltA;
    [[maybe_unused]] std::uint64_t *aWandererUpdateSaltB = pDomainSaltSet->mWandererUpdate.mSaltB;
    [[maybe_unused]] std::uint64_t *aWandererUpdateSaltC = pDomainSaltSet->mWandererUpdate.mSaltC;
    [[maybe_unused]] std::uint64_t *aWandererUpdateSaltD = pDomainSaltSet->mWandererUpdate.mSaltD;
    [[maybe_unused]] std::uint64_t *aWandererUpdateSaltE = pDomainSaltSet->mWandererUpdate.mSaltE;
    [[maybe_unused]] std::uint64_t *aWandererUpdateSaltF = pDomainSaltSet->mWandererUpdate.mSaltF;
    [[maybe_unused]] std::uint8_t *aWorkLaneA = pWorkSpace->mWorkLaneA;
    [[maybe_unused]] std::uint8_t *aWorkLaneB = pWorkSpace->mWorkLaneB;
    [[maybe_unused]] std::uint8_t *aFireLaneA = pWorkSpace->mFireLaneA;
    [[maybe_unused]] std::uint8_t *aFireLaneB = pWorkSpace->mFireLaneB;
    [[maybe_unused]] std::uint8_t *aFireLaneC = pWorkSpace->mFireLaneC;
    [[maybe_unused]] std::uint8_t *aFireLaneD = pWorkSpace->mFireLaneD;
    std::uint64_t aCross = 0; std::uint64_t aScatter = 0;

    std::uint64_t aOrbiterA = 0; std::uint64_t aOrbiterB = 0; std::uint64_t aOrbiterC = 0; std::uint64_t aOrbiterD = 0;
    std::uint64_t aOrbiterE = 0; std::uint64_t aOrbiterF = 0; std::uint64_t aOrbiterG = 0; std::uint64_t aOrbiterH = 0;
    std::uint64_t aOrbiterI = 0; std::uint64_t aOrbiterJ = 0; std::uint64_t aOrbiterK = 0;

    // [kdf-a arx]
    std::uint64_t aNonceWordA = TwistMix64::DiffuseA(pNonce * 0xAC6654000E848EA7ULL + 0xA0355AB03CCDE715ULL);
    std::uint64_t aNonceWordB = TwistMix64::DiffuseA(pNonce * 0xC010694D024D07A3ULL + 0xEC5ED127182284B3ULL);
    std::uint64_t aNonceWordC = TwistMix64::DiffuseC(pNonce * 0xAF171AF47560B6F1ULL + 0xDD2A9801E29C48D9ULL);
    std::uint64_t aNonceWordD = TwistMix64::DiffuseB(pNonce * 0xADBAD650AF85CEFBULL + 0xFAF573162D288F1DULL);
    std::uint64_t aNonceWordE = TwistMix64::DiffuseC(pNonce * 0xBE2912097CBC27F7ULL + 0xCEC9D75D735985CDULL);
    std::uint64_t aNonceWordF = TwistMix64::DiffuseC(pNonce * 0xF3EA9560D8C58941ULL + 0xA78B6F965D968DB1ULL);
    std::uint64_t aNonceWordG = TwistMix64::DiffuseC(pNonce * 0xC0888F33B3C55AA5ULL + 0xF31FDEB559A514BFULL);
    std::uint64_t aNonceWordH = TwistMix64::DiffuseB(pNonce * 0xBEB5864F43427E6DULL + 0xFD8FDFD312D8202BULL);
    std::uint64_t aNonceWordI = TwistMix64::DiffuseA(pNonce * 0x9E5E7632AD9B3A17ULL + 0x85B86880CEEAB3CDULL);
    std::uint64_t aNonceWordJ = TwistMix64::DiffuseC(pNonce * 0xF086BF010EA1F745ULL + 0xF02F29FF2B744EC2ULL);
    std::uint64_t aNonceWordK = TwistMix64::DiffuseA(pNonce * 0xF04BCD16A250C4B7ULL + 0xADC13182A2722EAEULL);
    std::uint64_t aNonceWordL = TwistMix64::DiffuseC(pNonce * 0xBEF0B75EB4D2C1E9ULL + 0xE524CA12AB8AAF51ULL);
    std::uint64_t aNonceWordM = TwistMix64::DiffuseC(pNonce * 0x99A49DCC7C2070CBULL + 0x942C227F24420347ULL);
    std::uint64_t aNonceWordN = TwistMix64::DiffuseA(pNonce * 0x8DB21DB66913124DULL + 0xFFBE7CA468800124ULL);
    std::uint64_t aNonceWordO = TwistMix64::DiffuseB(pNonce * 0x81410DEAC666D651ULL + 0x92E9924CED87F145ULL);
    std::uint64_t aNonceWordP = TwistMix64::DiffuseA(pNonce * 0xB7960887B58232C1ULL + 0xF2589CB6B8804585ULL);
    std::uint64_t aDomainWordIngress = pConstants->mIngress;
    std::uint64_t aDomainWordScatter = pConstants->mScatter;
    std::uint64_t aDomainWordCross = pConstants->mCross;
    [[maybe_unused]] std::uint8_t *mSource = pWorkSpace->mSource;
    std::uint64_t aPrevious = *pPrevious;
    std::uint64_t aIngress = *pIngress;
    std::uint64_t aCarry = *pCarry;
    std::uint64_t aWandererA = *pWandererA;
    std::uint64_t aWandererB = *pWandererB;
    std::uint64_t aWandererC = *pWandererC;
    std::uint64_t aWandererD = *pWandererD;
    std::uint64_t aWandererE = *pWandererE;
    std::uint64_t aWandererF = *pWandererF;
    std::uint64_t aWandererG = *pWandererG;
    std::uint64_t aWandererH = *pWandererH;
    std::uint64_t aWandererI = *pWandererI;
    std::uint64_t aWandererJ = *pWandererJ;
    std::uint64_t aWandererK = *pWandererK;
    // KDF_A_A kdf_a_loop_a (start)
    {
        // KDF_A_A kdf_a_loop_a lane group
        // read from: mSource, pSnow, aWorkLaneA, aWorkLaneB, aFireLaneA, aFireLaneB, aFireLaneC
        // write to: aWorkLaneA, aWorkLaneB, aFireLaneA, aFireLaneB, aFireLaneC, aFireLaneD
    
        // kdf_a_loop_a loop 1
        // ingress from: mSource, pSnow
        // ingress directions: mSource forward forced, pSnow forward/backward random
        // cross from: pSnow, mSource
        // cross directions: pSnow backward forced, mSource backward/forward random
        // write to: aWorkLaneA
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = RotL64(mSource[((aIndex + 930U)) & S_BLOCK1], 10U) ^ RotL64(pSnow[((S_BLOCK1 - aIndex + 3795U)) & S_BLOCK1], 39U);
            aIngress = TwistMix64::DiffuseC(((aIngress ^ aDomainWordIngress) ^ aNonceWordM));
            //
            aCross = RotL64(pSnow[((S_BLOCK1 - aIndex + 1043U)) & S_BLOCK1], 41U) ^ RotL64(mSource[((S_BLOCK1 - aIndex + 4893U)) & S_BLOCK1], 19U);
            aCross = TwistMix64::DiffuseB(((aCross ^ aDomainWordCross) ^ aNonceWordN));
            //
            aScatter = (RotL64(aCross, 22U) ^ RotL64(aPrevious, 35U)) ^ (RotL64(aCarry, 51U) + RotL64(aIngress, 3U));
            aScatter = TwistMix64::DiffuseB(((aScatter ^ aDomainWordScatter) ^ aNonceWordB));
            //
            aOrbiterH = (aWandererE + RotL64(aScatter, 21U)) + 9774364261626083532U;
            aOrbiterB = (aWandererA + RotL64(aPrevious, 48U)) + 18059001521926116420U;
            aOrbiterA = ((aWandererB + RotL64(aCross, 27U)) + 10615626210406381148U) + aOrbiterAssignSaltC[(((31U - aIndex) + 23U)) & S_SALT1];
            aOrbiterG = ((aWandererH + RotL64(aIngress, 11U)) + RotL64(aCarry, 53U)) + 10536484278007898620U;
            aOrbiterC = ((aWandererF + RotL64(aCross, 35U)) + RotL64(aCarry, 43U)) + 13320663045139972700U;
            aOrbiterD = ((aWandererJ + RotL64(aScatter, 53U)) + RotL64(aCarry, 3U)) + 17127001787268166583U;
            aOrbiterE = ((aWandererK + RotL64(aPrevious, 29U)) + 16742574590844166551U) + aNonceWordK;
            aOrbiterI = ((aWandererD + RotL64(aIngress, 19U)) + 8347719720758228053U) + aNonceWordC;
            aOrbiterK = (aWandererI + RotL64(aCross, 13U)) + 13502468705946051986U;
            aOrbiterJ = ((aWandererC + RotL64(aIngress, 46U)) + 3512687886188904904U) + aOrbiterAssignSaltF[((aIndex + 29U)) & S_SALT1];
            aOrbiterF = (aWandererG + RotL64(aPrevious, 3U)) + 495660316165795934U;
            //
            aOrbiterH = ((aOrbiterH + aOrbiterB) + 5092722552034477356U) + aOrbiterUpdateSaltE[(((31U - aIndex) + 15U)) & S_SALT1];
            aOrbiterA = (aOrbiterA ^ aOrbiterH) ^ 15641128019608284015U;
            aOrbiterA = RotL64((aOrbiterA * 3621036395703527059U), 47U);
            //
            aOrbiterG = (aOrbiterG + aOrbiterC) + 15421873776811085458U;
            aOrbiterD = ((aOrbiterD ^ aOrbiterG) ^ 17978775513204574125U) ^ aOrbiterUpdateSaltA[((aIndex + 21U)) & S_SALT1];
            aOrbiterD = RotL64((aOrbiterD * 18359600395119440183U), 29U);
            //
            aOrbiterE = (aOrbiterE + aOrbiterG) + 16617179197537669849U;
            aOrbiterI = ((aOrbiterI ^ aOrbiterE) ^ 1931805387534012528U) ^ aNonceWordE;
            aOrbiterI = RotL64((aOrbiterI * 3400139345857733775U), 19U);
            //
            aOrbiterC = (aOrbiterC + aOrbiterK) + 9544923119559308431U;
            aOrbiterH = (aOrbiterH ^ aOrbiterC) ^ 12930999400470173353U;
            aOrbiterH = RotL64((aOrbiterH * 16791006919271490005U), 3U);
            //
            aOrbiterK = (aOrbiterK + aOrbiterI) + 13673733276226249890U;
            aOrbiterB = (aOrbiterB ^ aOrbiterK) ^ 2032263473309124738U;
            aOrbiterB = RotL64((aOrbiterB * 3088728329261360607U), 21U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterH) + 14868502349358414206U;
            aOrbiterJ = (aOrbiterJ ^ aOrbiterD) ^ 10116495537187552321U;
            aOrbiterJ = RotL64((aOrbiterJ * 1380512121796709469U), 23U);
            //
            aOrbiterI = (aOrbiterI + aOrbiterD) + 5341113995358179244U;
            aOrbiterF = ((aOrbiterF ^ aOrbiterI) ^ 8415417980279705731U) ^ aNonceWordG;
            aOrbiterF = RotL64((aOrbiterF * 8521501372683793821U), 43U);
            //
            aOrbiterB = (aOrbiterB + aOrbiterF) + 2462819265072352463U;
            aOrbiterE = (aOrbiterE ^ aOrbiterB) ^ 7657062767608441931U;
            aOrbiterE = RotL64((aOrbiterE * 15554638801273540163U), 37U);
            //
            aOrbiterF = (aOrbiterF + aOrbiterJ) + 8153420530633265789U;
            aOrbiterG = ((aOrbiterG ^ aOrbiterF) ^ 10990681417675210534U) ^ aOrbiterUpdateSaltF[(((31U - aIndex) + 14U)) & S_SALT1];
            aOrbiterG = RotL64((aOrbiterG * 1928509513380702895U), 11U);
            //
            aOrbiterJ = (aOrbiterJ + aOrbiterA) + 17035995983178569271U;
            aOrbiterC = (aOrbiterC ^ aOrbiterJ) ^ 2806563871848226777U;
            aOrbiterC = RotL64((aOrbiterC * 4137935663733587867U), 27U);
            //
            aOrbiterA = (((aOrbiterA + aOrbiterE) + 6570698907081812011U) + aOrbiterUpdateSaltB[((aIndex + 5U)) & S_SALT1]) + aNonceWordF;
            aOrbiterK = (aOrbiterK ^ aOrbiterA) ^ 9774364261626083532U;
            aOrbiterK = RotL64((aOrbiterK * 1766375419340392741U), 51U);
            //
            aIngress = RotL64(aOrbiterD, 57U) ^ aOrbiterA;
            aIngress = aIngress + (aOrbiterC ^ RotL64(aOrbiterF, 5U));
            aIngress = aIngress + (aOrbiterJ ^ RotL64(aOrbiterK, 24U));
            aIngress = aIngress + (RotL64(aOrbiterE, 37U) ^ aOrbiterI);
            aIngress = aIngress + (RotL64(aOrbiterG, 27U) ^ aOrbiterB);
            aIngress = aIngress + RotL64(aOrbiterH, 11U);
            aIngress = TwistMix64::DiffuseC((aIngress + aScatter));
            //
            aWandererB = aWandererB ^ ((RotL64(aScatter, 26U) + aOrbiterB) + RotL64(aOrbiterD, 13U));
            aWandererG = aWandererG + ((RotL64(aPrevious, 5U) + aOrbiterE) + RotL64(aOrbiterI, 23U));
            aWandererH = aWandererH ^ ((RotL64(aCross, 53U) + aOrbiterC) + RotL64(aOrbiterJ, 21U));
            aWandererD = aWandererD + ((((RotL64(aIngress, 29U) + RotL64(aOrbiterF, 60U)) + aOrbiterE) + RotL64(aCarry, 29U)) + aWandererUpdateSaltB[((aIndex + 10U)) & S_SALT1]);
            aWandererJ = aWandererJ ^ (((RotL64(aCross, 11U) + RotL64(aOrbiterH, 41U)) + aOrbiterB) + aNonceWordI);
            aWandererE = aWandererE + ((RotL64(aPrevious, 41U) + RotL64(aOrbiterC, 11U)) + aOrbiterH);
            aWandererK = aWandererK ^ (((RotL64(aIngress, 43U) + RotL64(aOrbiterD, 57U)) + aOrbiterI) + aNonceWordA);
            aWandererC = aWandererC + (((RotL64(aScatter, 48U) + RotL64(aOrbiterD, 53U)) + aOrbiterK) + RotL64(aCarry, 53U));
            aWandererA = aWandererA ^ (((RotL64(aIngress, 39U) + aOrbiterB) + RotL64(aOrbiterG, 50U)) + aNonceWordP);
            aWandererF = aWandererF + ((RotL64(aPrevious, 35U) + aOrbiterG) + RotL64(aOrbiterF, 29U));
            aWandererI = aWandererI ^ (((RotL64(aScatter, 23U) + RotL64(aOrbiterA, 5U)) + aOrbiterG) + aWandererUpdateSaltE[((aIndex + 7U)) & S_SALT1]);
            //
            aCarry = aCarry + (RotL64(aWandererF, 23U) ^ aWandererA);
            aCarry = aCarry + (RotL64(aWandererI, 40U) ^ aWandererE);
            aCarry = aCarry + (RotL64(aWandererH, 29U) ^ aWandererJ);
            aCarry = aCarry + (RotL64(aWandererD, 35U) ^ aWandererB);
            aCarry = aCarry + (aWandererC ^ RotL64(aWandererG, 43U));
            aCarry = aCarry + RotL64(aWandererK, 50U);
            aCarry = aCarry + RotL64(aIngress, 11U);
            aCarry = TwistMix64::DiffuseA(aCarry);
            //
            aWorkLaneA[aIndex] = aIngress;
        }
    
        // kdf_a_loop_a loop 2
        // ingress from: aWorkLaneA, mSource
        // ingress directions: aWorkLaneA forward forced, mSource forward/backward random
        // cross from: aWorkLaneA, pSnow
        // cross directions: aWorkLaneA backward forced, pSnow backward/forward random
        // write to: aWorkLaneB
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = RotL64(aWorkLaneA[((aIndex + 8422U)) & S_BLOCK1], 47U) ^ RotL64(mSource[((aIndex + 6406U)) & S_BLOCK1], 58U);
            aIngress = TwistMix64::DiffuseB(((aIngress ^ aDomainWordIngress) ^ aNonceWordF));
            //
            aCross = RotL64(aWorkLaneA[((S_BLOCK1 - aIndex + 9758U)) & S_BLOCK1], 18U) ^ RotL64(pSnow[((S_BLOCK1 - aIndex + 6962U)) & S_BLOCK1], 37U);
            aCross = TwistMix64::DiffuseA(((aCross ^ aDomainWordCross) ^ aNonceWordK));
            //
            aScatter = (RotL64(aIngress, 23U) ^ RotL64(aCarry, 60U)) + (RotL64(aCross, 43U) ^ RotL64(aPrevious, 11U));
            aScatter = TwistMix64::DiffuseB(((aScatter ^ aDomainWordScatter) ^ aNonceWordA));
            //
            aOrbiterJ = ((aWandererI + RotL64(aIngress, 51U)) + RotL64(aCarry, 37U)) + 6318740973868639425U;
            aOrbiterC = (aWandererD + RotL64(aScatter, 26U)) + 5487840061430920881U;
            aOrbiterK = (aWandererA + RotL64(aCross, 53U)) + 10258706763248072672U;
            aOrbiterG = ((aWandererK + RotL64(aPrevious, 57U)) + 18356875269730338208U) + aNonceWordJ;
            aOrbiterD = (aWandererC + RotL64(aScatter, 47U)) + 12883160282903147010U;
            aOrbiterB = (((aWandererH + RotL64(aPrevious, 29U)) + RotL64(aCarry, 23U)) + 1010140474942697730U) + aNonceWordH;
            aOrbiterA = ((aWandererF + RotL64(aIngress, 23U)) + 17733939421700898293U) + aNonceWordN;
            aOrbiterE = (aWandererB + RotL64(aCross, 11U)) + 13693055887924981201U;
            aOrbiterF = ((aWandererG + RotL64(aScatter, 44U)) + 14574732452793385269U) + aOrbiterAssignSaltE[((aIndex + 28U)) & S_SALT1];
            aOrbiterH = (((aWandererE + RotL64(aCross, 41U)) + RotL64(aCarry, 29U)) + 10832873941223609012U) + aOrbiterAssignSaltA[(((31U - aIndex) + 15U)) & S_SALT1];
            aOrbiterI = ((aWandererJ + RotL64(aIngress, 21U)) + 8212600587135328040U) + aNonceWordO;
            //
            aOrbiterJ = (aOrbiterJ + aOrbiterC) + 5312744319781971178U;
            aOrbiterK = (aOrbiterK ^ aOrbiterJ) ^ 6173741211706546923U;
            aOrbiterK = RotL64((aOrbiterK * 12854414066390848249U), 29U);
            //
            aOrbiterK = ((aOrbiterK + aOrbiterG) + 3693249147883790810U) + aNonceWordL;
            aOrbiterD = ((aOrbiterD ^ aOrbiterK) ^ 18365859989736602556U) ^ aOrbiterUpdateSaltB[(((31U - aIndex) + 12U)) & S_SALT1];
            aOrbiterD = RotL64((aOrbiterD * 3348463719324104997U), 41U);
            //
            aOrbiterB = (aOrbiterB + aOrbiterA) + 10645056678337549771U;
            aOrbiterE = (aOrbiterE ^ aOrbiterB) ^ 1175668356822251045U;
            aOrbiterE = RotL64((aOrbiterE * 6579675292775345579U), 3U);
            //
            aOrbiterA = (((aOrbiterA + aOrbiterJ) + 13556844570541823717U) + aOrbiterUpdateSaltD[(((31U - aIndex) + 18U)) & S_SALT1]) + aNonceWordI;
            aOrbiterF = (aOrbiterF ^ aOrbiterA) ^ 4790355739411849736U;
            aOrbiterF = RotL64((aOrbiterF * 4083544011788850307U), 21U);
            //
            aOrbiterE = (aOrbiterE + aOrbiterF) + 14905575502272644116U;
            aOrbiterH = ((aOrbiterH ^ aOrbiterE) ^ 17047244574558476634U) ^ aNonceWordD;
            aOrbiterH = RotL64((aOrbiterH * 2356386971503880047U), 13U);
            //
            aOrbiterG = (aOrbiterG + aOrbiterH) + 10161614295718414869U;
            aOrbiterB = (aOrbiterB ^ aOrbiterG) ^ 13413914082651612468U;
            aOrbiterB = RotL64((aOrbiterB * 16224039093981079491U), 23U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterB) + 6072693130156927774U;
            aOrbiterC = (aOrbiterC ^ aOrbiterD) ^ 4333656233793103787U;
            aOrbiterC = RotL64((aOrbiterC * 9374745547133955709U), 35U);
            //
            aOrbiterI = (aOrbiterI + aOrbiterD) + 17209776289202130250U;
            aOrbiterJ = (aOrbiterJ ^ aOrbiterI) ^ 11752001118070361543U;
            aOrbiterJ = RotL64((aOrbiterJ * 4416523594812872339U), 43U);
            //
            aOrbiterH = ((aOrbiterH + aOrbiterI) + 15367365111105608277U) + aOrbiterUpdateSaltE[((aIndex + 14U)) & S_SALT1];
            aOrbiterA = ((aOrbiterA ^ aOrbiterH) ^ 8650687767097460704U) ^ aOrbiterUpdateSaltC[(((31U - aIndex) + 3U)) & S_SALT1];
            aOrbiterA = RotL64((aOrbiterA * 11430451559660578667U), 5U);
            //
            aOrbiterF = (aOrbiterF + aOrbiterK) + 18074648514448405693U;
            aOrbiterI = (aOrbiterI ^ aOrbiterF) ^ 10857586858462237581U;
            aOrbiterI = RotL64((aOrbiterI * 3722891011080095849U), 51U);
            //
            aOrbiterC = (aOrbiterC + aOrbiterE) + 17219932344278345591U;
            aOrbiterG = (aOrbiterG ^ aOrbiterC) ^ 6318740973868639425U;
            aOrbiterG = RotL64((aOrbiterG * 8846295038878812229U), 37U);
            //
            aIngress = aOrbiterG ^ RotL64(aOrbiterB, 37U);
            aIngress = aIngress + (aOrbiterI ^ RotL64(aOrbiterK, 47U));
            aIngress = aIngress + (aOrbiterF ^ RotL64(aOrbiterC, 60U));
            aIngress = aIngress + (RotL64(aOrbiterD, 41U) ^ aOrbiterE);
            aIngress = aIngress + (RotL64(aOrbiterA, 39U) ^ aOrbiterJ);
            aIngress = aIngress + RotL64(aOrbiterH, 23U);
            aIngress = TwistMix64::DiffuseB((aIngress + aScatter));
            //
            aWandererB = aWandererB + ((((RotL64(aScatter, 21U) + aOrbiterB) + RotL64(aOrbiterA, 48U)) + aNonceWordC) + aWandererUpdateSaltC[((aIndex + 29U)) & S_SALT1]);
            aWandererH = aWandererH ^ (((RotL64(aCross, 43U) + RotL64(aOrbiterG, 21U)) + aOrbiterI) + aNonceWordB);
            aWandererA = aWandererA + ((RotL64(aPrevious, 56U) + RotL64(aOrbiterD, 29U)) + aOrbiterC);
            aWandererE = aWandererE ^ ((RotL64(aIngress, 47U) + aOrbiterI) + RotL64(aOrbiterJ, 43U));
            aWandererD = aWandererD + ((((RotL64(aCross, 11U) + aOrbiterC) + RotL64(aOrbiterF, 57U)) + aNonceWordM) + aWandererUpdateSaltD[((aIndex + 21U)) & S_SALT1]);
            aWandererC = aWandererC ^ ((RotL64(aScatter, 23U) + RotL64(aOrbiterJ, 11U)) + aOrbiterK);
            aWandererJ = aWandererJ + ((RotL64(aPrevious, 51U) + aOrbiterD) + RotL64(aOrbiterH, 35U));
            aWandererI = aWandererI ^ ((RotL64(aIngress, 36U) + RotL64(aOrbiterA, 19U)) + aOrbiterK);
            aWandererK = aWandererK + (((RotL64(aCross, 39U) + RotL64(aOrbiterE, 27U)) + aOrbiterA) + RotL64(aCarry, 57U));
            aWandererG = aWandererG ^ (((RotL64(aPrevious, 3U) + aOrbiterE) + RotL64(aOrbiterB, 13U)) + aNonceWordP);
            aWandererF = aWandererF + (((RotL64(aIngress, 5U) + RotL64(aOrbiterH, 54U)) + aOrbiterB) + RotL64(aCarry, 5U));
            //
            aCarry = aCarry + (RotL64(aWandererD, 24U) ^ aWandererJ);
            aCarry = aCarry + (RotL64(aWandererC, 47U) ^ aWandererE);
            aCarry = aCarry + (RotL64(aWandererI, 21U) ^ aWandererA);
            aCarry = aCarry + (aWandererH ^ RotL64(aWandererG, 11U));
            aCarry = aCarry + (aWandererF ^ RotL64(aWandererK, 37U));
            aCarry = aCarry + RotL64(aWandererB, 6U);
            aCarry = aCarry + RotL64(aIngress, 39U);
            aCarry = TwistMix64::DiffuseB(aCarry);
            //
            aWorkLaneB[S_BLOCK1 - aIndex] = aIngress;
        }
    
        // kdf_a_loop_a loop 3
        // ingress from: aWorkLaneB, mSource
        // ingress directions: aWorkLaneB forward forced, mSource forward/backward random
        // cross from: pSnow, aWorkLaneA
        // cross directions: pSnow backward forced, aWorkLaneA backward/forward random
        // write to: aFireLaneA
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = RotL64(aWorkLaneB[((aIndex + 11994U)) & S_BLOCK1], 6U) ^ RotL64(mSource[((S_BLOCK1 - aIndex + 11774U)) & S_BLOCK1], 43U);
            aIngress = TwistMix64::DiffuseB(((aIngress ^ aDomainWordIngress) ^ aNonceWordE));
            //
            aCross = RotL64(pSnow[((S_BLOCK1 - aIndex + 15262U)) & S_BLOCK1], 47U) ^ RotL64(aWorkLaneA[((S_BLOCK1 - aIndex + 15391U)) & S_BLOCK1], 27U);
            aCross = TwistMix64::DiffuseC(((aCross ^ aDomainWordCross) ^ aNonceWordH));
            //
            aScatter = (RotL64(aCarry, 35U) + RotL64(aPrevious, 3U)) + (RotL64(aCross, 47U) ^ RotL64(aIngress, 20U));
            aScatter = TwistMix64::DiffuseA(((aScatter ^ aDomainWordScatter) ^ aNonceWordE));
            //
            aOrbiterA = ((aWandererE + RotL64(aCross, 47U)) + 3248574644570178787U) + aNonceWordC;
            aOrbiterI = ((aWandererD + RotL64(aIngress, 29U)) + 4506961512959200024U) + aNonceWordM;
            aOrbiterE = ((aWandererB + RotL64(aScatter, 19U)) + 8423739774540738590U) + aOrbiterAssignSaltD[((aIndex + 11U)) & S_SALT1];
            aOrbiterC = (aWandererC + RotL64(aPrevious, 39U)) + 6593975869641735337U;
            aOrbiterF = (aWandererH + RotL64(aIngress, 3U)) + 16441716090557369103U;
            aOrbiterD = ((aWandererK + RotL64(aScatter, 23U)) + 7936601450453207914U) + aOrbiterAssignSaltB[(((31U - aIndex) + 26U)) & S_SALT1];
            aOrbiterB = (((aWandererG + RotL64(aPrevious, 44U)) + RotL64(aCarry, 19U)) + 13333752583560167065U) + aNonceWordJ;
            aOrbiterJ = (aWandererI + RotL64(aCross, 41U)) + 8013703284795432973U;
            aOrbiterH = ((aWandererA + RotL64(aIngress, 5U)) + RotL64(aCarry, 39U)) + 2349852779887439236U;
            aOrbiterK = ((aWandererF + RotL64(aCross, 21U)) + RotL64(aCarry, 47U)) + 5318539364763284138U;
            aOrbiterG = (aWandererJ + RotL64(aPrevious, 56U)) + 11450957608502944376U;
            //
            aOrbiterA = (aOrbiterA + aOrbiterI) + 9058992558327552687U;
            aOrbiterE = (aOrbiterE ^ aOrbiterA) ^ 632095686920230926U;
            aOrbiterE = RotL64((aOrbiterE * 12460364388358520799U), 41U);
            //
            aOrbiterC = ((aOrbiterC + aOrbiterE) + 14734218428913777098U) + aOrbiterUpdateSaltE[(((31U - aIndex) + 7U)) & S_SALT1];
            aOrbiterF = (aOrbiterF ^ aOrbiterC) ^ 16344357661370784442U;
            aOrbiterF = RotL64((aOrbiterF * 15049472842002138369U), 43U);
            //
            aOrbiterE = ((aOrbiterE + aOrbiterD) + 2981145363531184308U) + aNonceWordK;
            aOrbiterB = ((aOrbiterB ^ aOrbiterE) ^ 14176472085175714494U) ^ aOrbiterUpdateSaltA[((aIndex + 12U)) & S_SALT1];
            aOrbiterB = RotL64((aOrbiterB * 2584623327412130939U), 51U);
            //
            aOrbiterJ = ((aOrbiterJ + aOrbiterH) + 11198457590069700889U) + aOrbiterUpdateSaltC[((aIndex + 8U)) & S_SALT1];
            aOrbiterA = (aOrbiterA ^ aOrbiterJ) ^ 952584436750426828U;
            aOrbiterA = RotL64((aOrbiterA * 1165713888651280355U), 21U);
            //
            aOrbiterK = ((aOrbiterK + aOrbiterA) + 4311591763498985972U) + aOrbiterUpdateSaltD[((aIndex + 29U)) & S_SALT1];
            aOrbiterC = (aOrbiterC ^ aOrbiterK) ^ 16194341833989936369U;
            aOrbiterC = RotL64((aOrbiterC * 9997934560195932575U), 37U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterG) + 7560794022401107431U;
            aOrbiterJ = (aOrbiterJ ^ aOrbiterD) ^ 10683789740265711603U;
            aOrbiterJ = RotL64((aOrbiterJ * 15637823045351977883U), 5U);
            //
            aOrbiterG = (aOrbiterG + aOrbiterK) + 11614366395125937178U;
            aOrbiterH = ((aOrbiterH ^ aOrbiterG) ^ 10750771385100564416U) ^ aNonceWordL;
            aOrbiterH = RotL64((aOrbiterH * 4987921274272444283U), 19U);
            //
            aOrbiterB = ((aOrbiterB + aOrbiterJ) + 2934697034132204529U) + aNonceWordO;
            aOrbiterK = (aOrbiterK ^ aOrbiterB) ^ 4646873794658020363U;
            aOrbiterK = RotL64((aOrbiterK * 10555456865641580175U), 47U);
            //
            aOrbiterH = ((aOrbiterH + aOrbiterC) + 7913681837683568905U) + aNonceWordP;
            aOrbiterI = (aOrbiterI ^ aOrbiterH) ^ 17603563535330106340U;
            aOrbiterI = RotL64((aOrbiterI * 17882943067522319671U), 53U);
            //
            aOrbiterF = (aOrbiterF + aOrbiterB) + 15375641415139193079U;
            aOrbiterG = (aOrbiterG ^ aOrbiterF) ^ 17059712718085411887U;
            aOrbiterG = RotL64((aOrbiterG * 13722089235751208215U), 39U);
            //
            aOrbiterI = (aOrbiterI + aOrbiterF) + 14022558453716067200U;
            aOrbiterD = (aOrbiterD ^ aOrbiterI) ^ 3248574644570178787U;
            aOrbiterD = RotL64((aOrbiterD * 15249135451439374621U), 23U);
            //
            aIngress = aOrbiterH ^ RotL64(aOrbiterB, 19U);
            aIngress = aIngress + (aOrbiterK ^ RotL64(aOrbiterA, 38U));
            aIngress = aIngress + (RotL64(aOrbiterD, 27U) ^ aOrbiterJ);
            aIngress = aIngress + (RotL64(aOrbiterI, 35U) ^ aOrbiterC);
            aIngress = aIngress + (RotL64(aOrbiterE, 5U) ^ aOrbiterG);
            aIngress = aIngress + RotL64(aOrbiterF, 43U);
            aIngress = TwistMix64::DiffuseA((aIngress + aScatter));
            //
            aWandererA = aWandererA ^ (((RotL64(aIngress, 35U) + aOrbiterC) + RotL64(aOrbiterA, 37U)) + aWandererUpdateSaltA[(((31U - aIndex) + 23U)) & S_SALT1]);
            aWandererD = aWandererD + (((RotL64(aScatter, 39U) + aOrbiterH) + RotL64(aOrbiterF, 14U)) + RotL64(aCarry, 51U));
            aWandererK = aWandererK ^ (((RotL64(aPrevious, 47U) + aOrbiterD) + RotL64(aOrbiterI, 29U)) + aNonceWordA);
            aWandererG = aWandererG + ((RotL64(aCross, 50U) + RotL64(aOrbiterF, 27U)) + aOrbiterG);
            aWandererJ = aWandererJ ^ (((RotL64(aIngress, 21U) + RotL64(aOrbiterE, 35U)) + aOrbiterC) + aWandererUpdateSaltF[(((31U - aIndex) + 19U)) & S_SALT1]);
            aWandererC = aWandererC + (((RotL64(aCross, 41U) + RotL64(aOrbiterK, 5U)) + aOrbiterI) + aNonceWordB);
            aWandererF = aWandererF ^ ((RotL64(aScatter, 11U) + RotL64(aOrbiterH, 39U)) + aOrbiterJ);
            aWandererI = aWandererI + ((RotL64(aPrevious, 4U) + RotL64(aOrbiterF, 56U)) + aOrbiterC);
            aWandererH = aWandererH ^ ((RotL64(aScatter, 53U) + RotL64(aOrbiterK, 41U)) + aOrbiterB);
            aWandererB = aWandererB + (((RotL64(aCross, 23U) + aOrbiterI) + RotL64(aOrbiterB, 19U)) + RotL64(aCarry, 37U));
            aWandererE = aWandererE ^ ((RotL64(aIngress, 57U) + aOrbiterE) + RotL64(aOrbiterH, 23U));
            //
            aCarry = aCarry + (aWandererE ^ RotL64(aWandererD, 34U));
            aCarry = aCarry + (RotL64(aWandererB, 37U) ^ aWandererC);
            aCarry = aCarry + (aWandererI ^ RotL64(aWandererH, 51U));
            aCarry = aCarry + (RotL64(aWandererJ, 5U) ^ aWandererK);
            aCarry = aCarry + (RotL64(aWandererG, 43U) ^ aWandererA);
            aCarry = aCarry + RotL64(aWandererF, 39U);
            aCarry = aCarry + RotL64(aIngress, 21U);
            aCarry = TwistMix64::DiffuseC(aCarry);
            //
            aFireLaneA[aIndex] = aIngress;
        }
    
        // kdf_a_loop_a loop 4
        // ingress from: aFireLaneA, aWorkLaneA
        // ingress directions: aFireLaneA forward forced, aWorkLaneA forward/backward random
        // cross from: mSource, pSnow, aWorkLaneB
        // cross directions: mSource backward forced, pSnow backward forced, aWorkLaneB backward/forward random
        // write to: aFireLaneB
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = RotL64(aFireLaneA[((aIndex + 18327U)) & S_BLOCK1], 57U) ^ RotL64(aWorkLaneA[((aIndex + 19241U)) & S_BLOCK1], 46U);
            aIngress = TwistMix64::DiffuseA(((aIngress ^ aDomainWordIngress) ^ aNonceWordO));
            //
            aCross = (RotL64(mSource[((S_BLOCK1 - aIndex + 17717U)) & S_BLOCK1], 47U) ^ RotL64(pSnow[((S_BLOCK1 - aIndex + 16706U)) & S_BLOCK1], 39U));
            aCross ^= RotL64(aWorkLaneB[((S_BLOCK1 - aIndex + 20204U)) & S_BLOCK1], 14U);
            aCross = TwistMix64::DiffuseA(((aCross ^ aDomainWordCross) ^ aNonceWordK));
            //
            aScatter = (RotL64(aCarry, 47U) ^ RotL64(aPrevious, 18U)) + (RotL64(aIngress, 5U) + RotL64(aCross, 35U));
            aScatter = TwistMix64::DiffuseB(((aScatter ^ aDomainWordScatter) ^ aNonceWordD));
            //
            aOrbiterA = (aWandererE + RotL64(aPrevious, 19U)) + 13499155707765393469U;
            aOrbiterG = (aWandererB + RotL64(aCross, 29U)) + 3740324981823726185U;
            aOrbiterH = ((aWandererD + RotL64(aScatter, 51U)) + RotL64(aCarry, 13U)) + 5470765363949735652U;
            aOrbiterK = (((aWandererJ + RotL64(aIngress, 35U)) + 3446436171274452326U) + aOrbiterAssignSaltC[((aIndex + 25U)) & S_SALT1]) + aNonceWordJ;
            aOrbiterJ = (((aWandererH + RotL64(aScatter, 43U)) + 1778929412631211933U) + aOrbiterAssignSaltF[((aIndex + 17U)) & S_SALT1]) + aNonceWordB;
            aOrbiterE = ((aWandererA + RotL64(aCross, 58U)) + 14666308799855220954U) + aNonceWordG;
            aOrbiterD = ((aWandererG + RotL64(aPrevious, 5U)) + RotL64(aCarry, 3U)) + 4548410236791175055U;
            aOrbiterI = ((aWandererK + RotL64(aIngress, 21U)) + RotL64(aCarry, 39U)) + 5829739767694190372U;
            aOrbiterB = (aWandererI + RotL64(aScatter, 23U)) + 14319231414903675748U;
            aOrbiterF = (aWandererC + RotL64(aIngress, 40U)) + 1513851750246111405U;
            aOrbiterC = ((aWandererF + RotL64(aCross, 3U)) + 1685620217748986019U) + aNonceWordM;
            //
            aOrbiterA = (aOrbiterA + aOrbiterG) + 16284162182006054402U;
            aOrbiterH = (aOrbiterH ^ aOrbiterA) ^ 6271539598462003309U;
            aOrbiterH = RotL64((aOrbiterH * 13923286694131331137U), 35U);
            //
            aOrbiterK = ((aOrbiterK + aOrbiterJ) + 12669312437565969473U) + aOrbiterUpdateSaltD[((aIndex + 26U)) & S_SALT1];
            aOrbiterG = ((aOrbiterG ^ aOrbiterK) ^ 11894755313393001665U) ^ aOrbiterUpdateSaltF[(((31U - aIndex) + 21U)) & S_SALT1];
            aOrbiterG = RotL64((aOrbiterG * 12556759675372354075U), 29U);
            //
            aOrbiterE = (aOrbiterE + aOrbiterD) + 6315983824634946566U;
            aOrbiterI = (aOrbiterI ^ aOrbiterE) ^ 17106616474222892782U;
            aOrbiterI = RotL64((aOrbiterI * 167205520766791073U), 57U);
            //
            aOrbiterG = (aOrbiterG + aOrbiterB) + 13350266700180455548U;
            aOrbiterF = (aOrbiterF ^ aOrbiterG) ^ 4608846311203767162U;
            aOrbiterF = RotL64((aOrbiterF * 2504857468837437365U), 11U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterC) + 14195866746143604365U;
            aOrbiterK = (aOrbiterK ^ aOrbiterD) ^ 7917977448256795054U;
            aOrbiterK = RotL64((aOrbiterK * 5927771378657284557U), 43U);
            //
            aOrbiterF = ((aOrbiterF + aOrbiterE) + 10707336923305131629U) + aNonceWordH;
            aOrbiterC = (aOrbiterC ^ aOrbiterF) ^ 17122696159336995392U;
            aOrbiterC = RotL64((aOrbiterC * 13953518568670659191U), 47U);
            //
            aOrbiterJ = (aOrbiterJ + aOrbiterA) + 5182322763573586116U;
            aOrbiterB = (aOrbiterB ^ aOrbiterJ) ^ 6503754948502556246U;
            aOrbiterB = RotL64((aOrbiterB * 14749002194140663519U), 3U);
            //
            aOrbiterC = (aOrbiterC + aOrbiterI) + 14907832047832987341U;
            aOrbiterJ = (aOrbiterJ ^ aOrbiterC) ^ 6258064448676621346U;
            aOrbiterJ = RotL64((aOrbiterJ * 4407960312705621487U), 23U);
            //
            aOrbiterH = ((aOrbiterH + aOrbiterF) + 1180234574888070795U) + aNonceWordF;
            aOrbiterD = ((aOrbiterD ^ aOrbiterH) ^ 801686887651085881U) ^ aNonceWordI;
            aOrbiterD = RotL64((aOrbiterD * 433981853631548041U), 41U);
            //
            aOrbiterI = ((aOrbiterI + aOrbiterK) + 11810494591997709554U) + aOrbiterUpdateSaltB[((aIndex + 7U)) & S_SALT1];
            aOrbiterA = ((aOrbiterA ^ aOrbiterI) ^ 9343740505955858127U) ^ aOrbiterUpdateSaltA[(((31U - aIndex) + 28U)) & S_SALT1];
            aOrbiterA = RotL64((aOrbiterA * 8733378485648720323U), 5U);
            //
            aOrbiterB = ((aOrbiterB + aOrbiterH) + 12816829575386720695U) + aNonceWordE;
            aOrbiterE = (aOrbiterE ^ aOrbiterB) ^ 13499155707765393469U;
            aOrbiterE = RotL64((aOrbiterE * 9937924703928730369U), 53U);
            //
            aIngress = aOrbiterA ^ RotL64(aOrbiterC, 6U);
            aIngress = aIngress + (RotL64(aOrbiterJ, 21U) ^ aOrbiterE);
            aIngress = aIngress + (aOrbiterH ^ RotL64(aOrbiterD, 47U));
            aIngress = aIngress + (RotL64(aOrbiterG, 19U) ^ aOrbiterB);
            aIngress = aIngress + (aOrbiterF ^ RotL64(aOrbiterK, 3U));
            aIngress = aIngress + RotL64(aOrbiterI, 57U);
            aIngress = TwistMix64::DiffuseB((aIngress + aScatter));
            //
            aWandererK = aWandererK + ((RotL64(aScatter, 39U) + aOrbiterB) + RotL64(aOrbiterC, 5U));
            aWandererB = aWandererB ^ (((RotL64(aIngress, 60U) + aOrbiterD) + RotL64(aOrbiterC, 51U)) + aNonceWordL);
            aWandererH = aWandererH + ((RotL64(aCross, 51U) + RotL64(aOrbiterI, 46U)) + aOrbiterE);
            aWandererA = aWandererA ^ (((RotL64(aPrevious, 35U) + aOrbiterA) + RotL64(aOrbiterD, 13U)) + aWandererUpdateSaltE[(((31U - aIndex) + 10U)) & S_SALT1]);
            aWandererI = aWandererI + (((RotL64(aScatter, 57U) + aOrbiterH) + RotL64(aOrbiterF, 3U)) + aNonceWordN);
            aWandererF = aWandererF ^ ((RotL64(aIngress, 18U) + RotL64(aOrbiterI, 37U)) + aOrbiterH);
            aWandererJ = aWandererJ + ((RotL64(aCross, 21U) + aOrbiterD) + RotL64(aOrbiterJ, 27U));
            aWandererG = aWandererG ^ ((RotL64(aPrevious, 29U) + RotL64(aOrbiterA, 11U)) + aOrbiterG);
            aWandererC = aWandererC + (((RotL64(aIngress, 41U) + aOrbiterH) + RotL64(aOrbiterA, 54U)) + RotL64(aCarry, 27U));
            aWandererE = aWandererE ^ (((RotL64(aCross, 23U) + RotL64(aOrbiterK, 19U)) + aOrbiterH) + aWandererUpdateSaltB[((aIndex + 15U)) & S_SALT1]);
            aWandererD = aWandererD + (((RotL64(aScatter, 53U) + aOrbiterA) + RotL64(aOrbiterF, 43U)) + RotL64(aCarry, 3U));
            //
            aCarry = aCarry + (aWandererA ^ RotL64(aWandererC, 42U));
            aCarry = aCarry + (RotL64(aWandererJ, 53U) ^ aWandererF);
            aCarry = aCarry + (RotL64(aWandererD, 57U) ^ aWandererG);
            aCarry = aCarry + (RotL64(aWandererK, 3U) ^ aWandererB);
            aCarry = aCarry + (aWandererE ^ RotL64(aWandererH, 39U));
            aCarry = aCarry + RotL64(aWandererI, 13U);
            aCarry = aCarry + RotL64(aIngress, 46U);
            aCarry = TwistMix64::DiffuseA(aCarry);
            //
            aFireLaneB[S_BLOCK1 - aIndex] = aIngress;
        }
    
        // kdf_a_loop_a loop 5
        // ingress from: aFireLaneB, mSource, pSnow, aWorkLaneA
        // ingress directions: aFireLaneB forward forced, mSource forward forced, pSnow forward forced, aWorkLaneA forward/backward random
        // cross from: aFireLaneA, aWorkLaneB
        // cross directions: aFireLaneA backward forced, aWorkLaneB backward/forward random
        // write to: aFireLaneC
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aFireLaneB[((aIndex + 24592U)) & S_BLOCK1], 11U) ^ RotL64(mSource[((aIndex + 24013U)) & S_BLOCK1], 51U));
            aIngress ^= (RotL64(pSnow[((aIndex + 24021U)) & S_BLOCK1], 21U) ^ RotL64(aWorkLaneA[((aIndex + 26776U)) & S_BLOCK1], 29U));
            aIngress = TwistMix64::DiffuseA(((aIngress ^ aDomainWordIngress) ^ aNonceWordL));
            //
            aCross = RotL64(aFireLaneA[((S_BLOCK1 - aIndex + 25194U)) & S_BLOCK1], 53U) ^ RotL64(aWorkLaneB[((S_BLOCK1 - aIndex + 21919U)) & S_BLOCK1], 35U);
            aCross = TwistMix64::DiffuseB(((aCross ^ aDomainWordCross) ^ aNonceWordA));
            //
            aScatter = (RotL64(aCarry, 41U) ^ RotL64(aPrevious, 19U)) ^ (RotL64(aCross, 3U) + RotL64(aIngress, 54U));
            aScatter = TwistMix64::DiffuseB(((aScatter ^ aDomainWordScatter) ^ aNonceWordL));
            //
            aOrbiterI = ((aWandererC + RotL64(aIngress, 35U)) + RotL64(aCarry, 27U)) + 16462052553719977502U;
            aOrbiterA = (aWandererK + RotL64(aCross, 57U)) + 12337064059566619581U;
            aOrbiterJ = ((aWandererD + RotL64(aScatter, 43U)) + 15801005007094515447U) + aOrbiterAssignSaltE[((aIndex + 7U)) & S_SALT1];
            aOrbiterB = ((aWandererJ + RotL64(aPrevious, 39U)) + 8228706742665081656U) + aNonceWordO;
            aOrbiterE = (aWandererB + RotL64(aIngress, 51U)) + 11006723027845190869U;
            aOrbiterH = ((aWandererF + RotL64(aScatter, 22U)) + 18173765337829177450U) + aNonceWordM;
            aOrbiterD = (aWandererA + RotL64(aCross, 41U)) + 530215083653542558U;
            aOrbiterC = (((aWandererI + RotL64(aPrevious, 37U)) + RotL64(aCarry, 51U)) + 6608611827035564511U) + aNonceWordE;
            aOrbiterK = ((aWandererG + RotL64(aIngress, 3U)) + 2246051826221626809U) + aOrbiterAssignSaltA[(((31U - aIndex) + 21U)) & S_SALT1];
            aOrbiterG = ((aWandererE + RotL64(aScatter, 24U)) + RotL64(aCarry, 35U)) + 5228575308895381421U;
            aOrbiterF = (aWandererH + RotL64(aCross, 47U)) + 10999213210689606857U;
            //
            aOrbiterI = (aOrbiterI + aOrbiterA) + 3773371037240485696U;
            aOrbiterJ = (aOrbiterJ ^ aOrbiterI) ^ 8887985779436152504U;
            aOrbiterJ = RotL64((aOrbiterJ * 698713082830739677U), 5U);
            //
            aOrbiterB = (aOrbiterB + aOrbiterE) + 11150566414723818350U;
            aOrbiterH = (aOrbiterH ^ aOrbiterB) ^ 8336366151003049546U;
            aOrbiterH = RotL64((aOrbiterH * 9033771197242493699U), 43U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterC) + 13233968794237090787U;
            aOrbiterE = (aOrbiterE ^ aOrbiterD) ^ 8172558473508478819U;
            aOrbiterE = RotL64((aOrbiterE * 17837070423649268435U), 29U);
            //
            aOrbiterE = ((aOrbiterE + aOrbiterI) + 133564480283347997U) + aOrbiterUpdateSaltC[((aIndex + 10U)) & S_SALT1];
            aOrbiterK = (aOrbiterK ^ aOrbiterE) ^ 15104810248883567064U;
            aOrbiterK = RotL64((aOrbiterK * 706802420642303533U), 51U);
            //
            aOrbiterG = (aOrbiterG + aOrbiterH) + 9138629520201127075U;
            aOrbiterD = (aOrbiterD ^ aOrbiterG) ^ 13993086066341664080U;
            aOrbiterD = RotL64((aOrbiterD * 4875046427147105077U), 27U);
            //
            aOrbiterA = (aOrbiterA + aOrbiterD) + 6547273508580516932U;
            aOrbiterB = ((aOrbiterB ^ aOrbiterA) ^ 9838727018769865759U) ^ aOrbiterUpdateSaltE[(((31U - aIndex) + 9U)) & S_SALT1];
            aOrbiterB = RotL64((aOrbiterB * 11395273371936839815U), 23U);
            //
            aOrbiterH = (aOrbiterH + aOrbiterK) + 11685694999526122626U;
            aOrbiterC = (aOrbiterC ^ aOrbiterH) ^ 8945983172566303116U;
            aOrbiterC = RotL64((aOrbiterC * 17791527981004597623U), 41U);
            //
            aOrbiterK = (aOrbiterK + aOrbiterJ) + 17606249889617356327U;
            aOrbiterF = ((aOrbiterF ^ aOrbiterK) ^ 9296903152000480008U) ^ aNonceWordK;
            aOrbiterF = RotL64((aOrbiterF * 18066622289408024413U), 13U);
            //
            aOrbiterF = (aOrbiterF + aOrbiterG) + 14248192861977167583U;
            aOrbiterA = (aOrbiterA ^ aOrbiterF) ^ 5467843420970464193U;
            aOrbiterA = RotL64((aOrbiterA * 10121398470914323221U), 53U);
            //
            aOrbiterC = (aOrbiterC + aOrbiterF) + 17072313558131700643U;
            aOrbiterI = (aOrbiterI ^ aOrbiterC) ^ 7932446176598954438U;
            aOrbiterI = RotL64((aOrbiterI * 11684711939539349335U), 47U);
            //
            aOrbiterJ = ((aOrbiterJ + aOrbiterB) + 15377107166135929052U) + aOrbiterUpdateSaltF[((aIndex + 23U)) & S_SALT1];
            aOrbiterG = (((aOrbiterG ^ aOrbiterJ) ^ 16462052553719977502U) ^ aOrbiterUpdateSaltD[(((31U - aIndex) + 11U)) & S_SALT1]) ^ aNonceWordF;
            aOrbiterG = RotL64((aOrbiterG * 9057188521274832217U), 39U);
            //
            aIngress = RotL64(aOrbiterE, 35U) ^ aOrbiterJ;
            aIngress = aIngress + (RotL64(aOrbiterK, 28U) ^ aOrbiterC);
            aIngress = aIngress + (aOrbiterD ^ RotL64(aOrbiterI, 13U));
            aIngress = aIngress + (aOrbiterF ^ RotL64(aOrbiterA, 3U));
            aIngress = aIngress + (RotL64(aOrbiterB, 19U) ^ aOrbiterH);
            aIngress = aIngress + RotL64(aOrbiterG, 44U);
            aIngress = TwistMix64::DiffuseB((aIngress + aScatter));
            //
            aWandererD = aWandererD + ((RotL64(aCross, 29U) + RotL64(aOrbiterI, 5U)) + aOrbiterJ);
            aWandererE = aWandererE ^ (((RotL64(aIngress, 3U) + RotL64(aOrbiterK, 47U)) + aOrbiterE) + aNonceWordC);
            aWandererC = aWandererC + (((RotL64(aScatter, 26U) + RotL64(aOrbiterE, 37U)) + aOrbiterB) + RotL64(aCarry, 13U));
            aWandererA = aWandererA ^ (((RotL64(aPrevious, 51U) + aOrbiterG) + RotL64(aOrbiterI, 51U)) + aWandererUpdateSaltD[((aIndex + 24U)) & S_SALT1]);
            aWandererI = aWandererI + (((RotL64(aIngress, 5U) + aOrbiterK) + RotL64(aOrbiterA, 40U)) + aNonceWordH);
            aWandererG = aWandererG ^ ((RotL64(aPrevious, 35U) + RotL64(aOrbiterI, 11U)) + aOrbiterH);
            aWandererB = aWandererB + (((RotL64(aCross, 21U) + RotL64(aOrbiterB, 27U)) + aOrbiterG) + RotL64(aCarry, 41U));
            aWandererJ = aWandererJ ^ ((RotL64(aScatter, 11U) + aOrbiterD) + RotL64(aOrbiterG, 3U));
            aWandererF = aWandererF + ((RotL64(aIngress, 38U) + RotL64(aOrbiterI, 23U)) + aOrbiterC);
            aWandererH = aWandererH ^ ((RotL64(aCross, 47U) + RotL64(aOrbiterK, 35U)) + aOrbiterF);
            aWandererK = aWandererK + (((RotL64(aPrevious, 13U) + RotL64(aOrbiterH, 56U)) + aOrbiterB) + aWandererUpdateSaltC[(((31U - aIndex) + 29U)) & S_SALT1]);
            //
            aCarry = aCarry + (aWandererG ^ RotL64(aWandererK, 46U));
            aCarry = aCarry + (aWandererF ^ RotL64(aWandererE, 29U));
            aCarry = aCarry + (aWandererC ^ RotL64(aWandererA, 27U));
            aCarry = aCarry + (aWandererJ ^ RotL64(aWandererD, 23U));
            aCarry = aCarry + (aWandererI ^ RotL64(aWandererH, 37U));
            aCarry = aCarry + RotL64(aWandererB, 21U);
            aCarry = aCarry + RotL64(aIngress, 35U);
            aCarry = TwistMix64::DiffuseA(aCarry);
            //
            aFireLaneC[aIndex] = aIngress;
        }
    
        // kdf_a_loop_a loop 6
        // ingress from: aFireLaneC, pSnow, aFireLaneA
        // ingress directions: aFireLaneC forward forced, pSnow forward forced, aFireLaneA forward/backward random
        // cross from: aFireLaneB, mSource, aWorkLaneB
        // cross directions: aFireLaneB backward forced, mSource backward forced, aWorkLaneB backward/forward random
        // write to: aFireLaneD
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aFireLaneC[((aIndex + 30243U)) & S_BLOCK1], 5U) ^ RotL64(pSnow[((aIndex + 32065U)) & S_BLOCK1], 51U));
            aIngress ^= RotL64(aFireLaneA[((S_BLOCK1 - aIndex + 31459U)) & S_BLOCK1], 42U);
            aIngress = TwistMix64::DiffuseB(((aIngress ^ aDomainWordIngress) ^ aNonceWordB));
            //
            aCross = (RotL64(aFireLaneB[((S_BLOCK1 - aIndex + 31429U)) & S_BLOCK1], 41U) ^ RotL64(mSource[((S_BLOCK1 - aIndex + 29274U)) & S_BLOCK1], 3U));
            aCross ^= RotL64(aWorkLaneB[((aIndex + 31486U)) & S_BLOCK1], 50U);
            aCross = TwistMix64::DiffuseB(((aCross ^ aDomainWordCross) ^ aNonceWordI));
            //
            aScatter = (RotL64(aPrevious, 24U) + RotL64(aCarry, 37U)) + (RotL64(aIngress, 11U) ^ RotL64(aCross, 51U));
            aScatter = TwistMix64::DiffuseB(((aScatter ^ aDomainWordScatter) ^ aNonceWordF));
            //
            aOrbiterB = (((aWandererJ + RotL64(aScatter, 29U)) + RotL64(aCarry, 47U)) + 18144572925667544139U) + aOrbiterAssignSaltD[(((31U - aIndex) + 21U)) & S_SALT1];
            aOrbiterE = ((aWandererI + RotL64(aPrevious, 41U)) + 5659758077574059728U) + aNonceWordC;
            aOrbiterA = ((aWandererF + RotL64(aIngress, 21U)) + RotL64(aCarry, 21U)) + 6343330616999166392U;
            aOrbiterK = ((aWandererE + RotL64(aCross, 10U)) + RotL64(aCarry, 37U)) + 17754639838410839447U;
            aOrbiterC = (aWandererG + RotL64(aIngress, 43U)) + 9451843819849581729U;
            aOrbiterI = ((aWandererB + RotL64(aCross, 51U)) + 7957854457197462212U) + aNonceWordO;
            aOrbiterD = ((aWandererD + RotL64(aScatter, 27U)) + 1461994799722205010U) + aOrbiterAssignSaltB[((aIndex + 15U)) & S_SALT1];
            aOrbiterG = (aWandererK + RotL64(aPrevious, 53U)) + 18002214276252170177U;
            aOrbiterH = (aWandererA + RotL64(aCross, 19U)) + 14689869073147027164U;
            aOrbiterJ = ((aWandererH + RotL64(aPrevious, 48U)) + 3978104368003440293U) + aNonceWordA;
            aOrbiterF = (aWandererC + RotL64(aScatter, 5U)) + 8512135845221335386U;
            //
            aOrbiterB = ((aOrbiterB + aOrbiterE) + 1477533446382953439U) + aNonceWordP;
            aOrbiterA = (aOrbiterA ^ aOrbiterB) ^ 2166717790929947990U;
            aOrbiterA = RotL64((aOrbiterA * 6538884492418324461U), 53U);
            //
            aOrbiterK = (aOrbiterK + aOrbiterC) + 8082437060686606995U;
            aOrbiterI = ((aOrbiterI ^ aOrbiterK) ^ 4363687722464700362U) ^ aOrbiterUpdateSaltF[(((31U - aIndex) + 12U)) & S_SALT1];
            aOrbiterI = RotL64((aOrbiterI * 7199165810993478887U), 41U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterG) + 15782763348014924206U;
            aOrbiterC = (aOrbiterC ^ aOrbiterD) ^ 8572509150015960728U;
            aOrbiterC = RotL64((aOrbiterC * 3340528604891897779U), 23U);
            //
            aOrbiterH = (aOrbiterH + aOrbiterI) + 12248271773316742521U;
            aOrbiterB = ((aOrbiterB ^ aOrbiterH) ^ 9602078627638561949U) ^ aNonceWordJ;
            aOrbiterB = RotL64((aOrbiterB * 1860631869877427405U), 37U);
            //
            aOrbiterI = ((aOrbiterI + aOrbiterJ) + 17244849374768558859U) + aOrbiterUpdateSaltB[((aIndex + 9U)) & S_SALT1];
            aOrbiterE = (aOrbiterE ^ aOrbiterI) ^ 1030743048280579012U;
            aOrbiterE = RotL64((aOrbiterE * 10858949914285817051U), 43U);
            //
            aOrbiterF = (aOrbiterF + aOrbiterA) + 17722342363541914280U;
            aOrbiterG = ((aOrbiterG ^ aOrbiterF) ^ 15667504059789880034U) ^ aOrbiterUpdateSaltC[(((31U - aIndex) + 28U)) & S_SALT1];
            aOrbiterG = RotL64((aOrbiterG * 15872269872168533709U), 35U);
            //
            aOrbiterG = (aOrbiterG + aOrbiterK) + 12645332941998550794U;
            aOrbiterH = (aOrbiterH ^ aOrbiterG) ^ 9938135244509986497U;
            aOrbiterH = RotL64((aOrbiterH * 16548185968987392957U), 5U);
            //
            aOrbiterC = ((aOrbiterC + aOrbiterH) + 4024609904162105979U) + aOrbiterUpdateSaltA[(((31U - aIndex) + 25U)) & S_SALT1];
            aOrbiterJ = (aOrbiterJ ^ aOrbiterC) ^ 6732064218696157303U;
            aOrbiterJ = RotL64((aOrbiterJ * 3815409766145891393U), 57U);
            //
            aOrbiterJ = (aOrbiterJ + aOrbiterB) + 14314117137220703583U;
            aOrbiterF = (aOrbiterF ^ aOrbiterJ) ^ 15244765904057473814U;
            aOrbiterF = RotL64((aOrbiterF * 4034571710808047959U), 19U);
            //
            aOrbiterE = ((aOrbiterE + aOrbiterF) + 17441241682018169245U) + aNonceWordF;
            aOrbiterD = ((aOrbiterD ^ aOrbiterE) ^ 11958974379114644873U) ^ aNonceWordD;
            aOrbiterD = RotL64((aOrbiterD * 11315689206845170303U), 11U);
            //
            aOrbiterA = (aOrbiterA + aOrbiterD) + 8310839846793796473U;
            aOrbiterK = (aOrbiterK ^ aOrbiterA) ^ 18144572925667544139U;
            aOrbiterK = RotL64((aOrbiterK * 11668203295511168011U), 21U);
            //
            aIngress = aOrbiterG ^ RotL64(aOrbiterK, 11U);
            aIngress = aIngress + (RotL64(aOrbiterB, 38U) ^ aOrbiterC);
            aIngress = aIngress + (RotL64(aOrbiterA, 35U) ^ aOrbiterJ);
            aIngress = aIngress + (aOrbiterE ^ RotL64(aOrbiterI, 29U));
            aIngress = aIngress + (aOrbiterH ^ RotL64(aOrbiterD, 51U));
            aIngress = aIngress + RotL64(aOrbiterF, 23U);
            aIngress = TwistMix64::DiffuseC((aIngress + aScatter));
            //
            aWandererD = aWandererD + ((RotL64(aPrevious, 5U) + aOrbiterF) + RotL64(aOrbiterI, 4U));
            aWandererH = aWandererH ^ (((RotL64(aScatter, 37U) + aOrbiterB) + RotL64(aOrbiterD, 51U)) + aNonceWordE);
            aWandererJ = aWandererJ + ((RotL64(aIngress, 47U) + aOrbiterK) + RotL64(aOrbiterC, 53U));
            aWandererE = aWandererE ^ ((RotL64(aCross, 35U) + aOrbiterD) + RotL64(aOrbiterJ, 39U));
            aWandererG = aWandererG + ((RotL64(aScatter, 11U) + aOrbiterF) + RotL64(aOrbiterC, 27U));
            aWandererB = aWandererB ^ ((RotL64(aCross, 13U) + RotL64(aOrbiterF, 37U)) + aOrbiterG);
            aWandererA = aWandererA + (((RotL64(aIngress, 42U) + aOrbiterH) + RotL64(aOrbiterC, 13U)) + RotL64(aCarry, 47U));
            aWandererK = aWandererK ^ (((RotL64(aPrevious, 57U) + aOrbiterA) + RotL64(aOrbiterB, 41U)) + aWandererUpdateSaltA[((aIndex + 24U)) & S_SALT1]);
            aWandererC = aWandererC + (((RotL64(aScatter, 39U) + RotL64(aOrbiterE, 23U)) + aOrbiterK) + aWandererUpdateSaltF[(((31U - aIndex) + 4U)) & S_SALT1]);
            aWandererI = aWandererI ^ (((RotL64(aPrevious, 51U) + aOrbiterB) + RotL64(aOrbiterH, 21U)) + aNonceWordL);
            aWandererF = aWandererF + (((RotL64(aCross, 30U) + aOrbiterI) + RotL64(aOrbiterH, 6U)) + RotL64(aCarry, 27U));
            //
            aCarry = aCarry + (RotL64(aWandererK, 18U) ^ aWandererE);
            aCarry = aCarry + (aWandererA ^ RotL64(aWandererB, 21U));
            aCarry = aCarry + (RotL64(aWandererJ, 11U) ^ aWandererH);
            aCarry = aCarry + (RotL64(aWandererI, 3U) ^ aWandererD);
            aCarry = aCarry + (RotL64(aWandererG, 6U) ^ aWandererF);
            aCarry = aCarry + RotL64(aWandererC, 57U);
            aCarry = aCarry + RotL64(aIngress, 41U);
            aCarry = TwistMix64::DiffuseA(aCarry);
            //
            aFireLaneD[S_BLOCK1 - aIndex] = aIngress;
        }
    }
    // KDF_A_A kdf_a_loop_a (end)
    *pPrevious = aPrevious;
    *pIngress = aIngress;
    *pCarry = aCarry;
    *pWandererA = aWandererA;
    *pWandererB = aWandererB;
    *pWandererC = aWandererC;
    *pWandererD = aWandererD;
    *pWandererE = aWandererE;
    *pWandererF = aWandererF;
    *pWandererG = aWandererG;
    *pWandererH = aWandererH;
    *pWandererI = aWandererI;
    *pWandererJ = aWandererJ;
    *pWandererK = aWandererK;
}

void TwistExpander_Exercea_Arx::KDF_A_B(TwistWorkSpace *pWorkSpace,
                     std::uint64_t pNonce,
                     TwistDomainConstants *pConstants,
                     TwistDomainSaltSet *pDomainSaltSet,
                     std::uint64_t *pPrevious,
                     std::uint64_t *pIngress,
                     std::uint64_t *pCarry,
                     std::uint64_t *pWandererA,
                     std::uint64_t *pWandererB,
                     std::uint64_t *pWandererC,
                     std::uint64_t *pWandererD,
                     std::uint64_t *pWandererE,
                     std::uint64_t *pWandererF,
                     std::uint64_t *pWandererG,
                     std::uint64_t *pWandererH,
                     std::uint64_t *pWandererI,
                     std::uint64_t *pWandererJ,
                     std::uint64_t *pWandererK) {
    [[maybe_unused]] std::uint64_t *aOrbiterAssignSaltA = pDomainSaltSet->mOrbiterAssign.mSaltA;
    [[maybe_unused]] std::uint64_t *aOrbiterAssignSaltB = pDomainSaltSet->mOrbiterAssign.mSaltB;
    [[maybe_unused]] std::uint64_t *aOrbiterAssignSaltC = pDomainSaltSet->mOrbiterAssign.mSaltC;
    [[maybe_unused]] std::uint64_t *aOrbiterAssignSaltD = pDomainSaltSet->mOrbiterAssign.mSaltD;
    [[maybe_unused]] std::uint64_t *aOrbiterAssignSaltE = pDomainSaltSet->mOrbiterAssign.mSaltE;
    [[maybe_unused]] std::uint64_t *aOrbiterAssignSaltF = pDomainSaltSet->mOrbiterAssign.mSaltF;
    [[maybe_unused]] std::uint64_t *aOrbiterUpdateSaltA = pDomainSaltSet->mOrbiterUpdate.mSaltA;
    [[maybe_unused]] std::uint64_t *aOrbiterUpdateSaltB = pDomainSaltSet->mOrbiterUpdate.mSaltB;
    [[maybe_unused]] std::uint64_t *aOrbiterUpdateSaltC = pDomainSaltSet->mOrbiterUpdate.mSaltC;
    [[maybe_unused]] std::uint64_t *aOrbiterUpdateSaltD = pDomainSaltSet->mOrbiterUpdate.mSaltD;
    [[maybe_unused]] std::uint64_t *aOrbiterUpdateSaltE = pDomainSaltSet->mOrbiterUpdate.mSaltE;
    [[maybe_unused]] std::uint64_t *aOrbiterUpdateSaltF = pDomainSaltSet->mOrbiterUpdate.mSaltF;
    [[maybe_unused]] std::uint64_t *aWandererUpdateSaltA = pDomainSaltSet->mWandererUpdate.mSaltA;
    [[maybe_unused]] std::uint64_t *aWandererUpdateSaltB = pDomainSaltSet->mWandererUpdate.mSaltB;
    [[maybe_unused]] std::uint64_t *aWandererUpdateSaltC = pDomainSaltSet->mWandererUpdate.mSaltC;
    [[maybe_unused]] std::uint64_t *aWandererUpdateSaltD = pDomainSaltSet->mWandererUpdate.mSaltD;
    [[maybe_unused]] std::uint64_t *aWandererUpdateSaltE = pDomainSaltSet->mWandererUpdate.mSaltE;
    [[maybe_unused]] std::uint64_t *aWandererUpdateSaltF = pDomainSaltSet->mWandererUpdate.mSaltF;
    [[maybe_unused]] std::uint8_t *aOperationLaneA = pWorkSpace->mOperationLaneA;
    [[maybe_unused]] std::uint8_t *aOperationLaneB = pWorkSpace->mOperationLaneB;
    [[maybe_unused]] std::uint8_t *aOperationLaneC = pWorkSpace->mOperationLaneC;
    [[maybe_unused]] std::uint8_t *aOperationLaneD = pWorkSpace->mOperationLaneD;
    [[maybe_unused]] std::uint8_t *aFireLaneA = pWorkSpace->mFireLaneA;
    [[maybe_unused]] std::uint8_t *aFireLaneB = pWorkSpace->mFireLaneB;
    [[maybe_unused]] std::uint8_t *aFireLaneC = pWorkSpace->mFireLaneC;
    [[maybe_unused]] std::uint8_t *aFireLaneD = pWorkSpace->mFireLaneD;
    std::uint64_t aCross = 0; std::uint64_t aScatter = 0;

    std::uint64_t aOrbiterA = 0; std::uint64_t aOrbiterB = 0; std::uint64_t aOrbiterC = 0; std::uint64_t aOrbiterD = 0;
    std::uint64_t aOrbiterE = 0; std::uint64_t aOrbiterF = 0; std::uint64_t aOrbiterG = 0; std::uint64_t aOrbiterH = 0;
    std::uint64_t aOrbiterI = 0; std::uint64_t aOrbiterJ = 0; std::uint64_t aOrbiterK = 0;

    // [kdf-a arx]
    std::uint64_t aNonceWordA = TwistMix64::DiffuseC(pNonce * 0x858587267313431BULL + 0x8A7C715F65A09D02ULL);
    std::uint64_t aNonceWordB = TwistMix64::DiffuseC(pNonce * 0xC8226402ABD2EA3BULL + 0xBC024F526B804ADFULL);
    std::uint64_t aNonceWordC = TwistMix64::DiffuseA(pNonce * 0xD1E654E663473B5FULL + 0xC250A6938FA2F6B2ULL);
    std::uint64_t aNonceWordD = TwistMix64::DiffuseB(pNonce * 0xEFD8624D9C9725DDULL + 0x8D26ED9A511FA90CULL);
    std::uint64_t aNonceWordE = TwistMix64::DiffuseC(pNonce * 0xEC3E614D2BCE71DBULL + 0x8173EBDDB2E5F520ULL);
    std::uint64_t aNonceWordF = TwistMix64::DiffuseB(pNonce * 0xE8B7B2FC835FE67DULL + 0xD2AB68C5BD8646FFULL);
    std::uint64_t aNonceWordG = TwistMix64::DiffuseC(pNonce * 0xF80CC31540EE036BULL + 0xAE2B31CD76654F2FULL);
    std::uint64_t aNonceWordH = TwistMix64::DiffuseA(pNonce * 0xED6F880AB293B331ULL + 0xB77B1BBCD2814D76ULL);
    std::uint64_t aNonceWordI = TwistMix64::DiffuseC(pNonce * 0x91CBD910364FBD5DULL + 0x902527D1094C6D4EULL);
    std::uint64_t aNonceWordJ = TwistMix64::DiffuseB(pNonce * 0xCE7EE4F9E208EE7BULL + 0xE6EB5442E49607CCULL);
    std::uint64_t aNonceWordK = TwistMix64::DiffuseA(pNonce * 0xC9164E28928A5229ULL + 0xC53B9212BA3BA1E2ULL);
    std::uint64_t aNonceWordL = TwistMix64::DiffuseC(pNonce * 0xF22377BF23362091ULL + 0x9A33F01AEF0F2DF7ULL);
    std::uint64_t aNonceWordM = TwistMix64::DiffuseB(pNonce * 0x9B866CC82DEB2EA5ULL + 0xC8B1A41C0843E132ULL);
    std::uint64_t aNonceWordN = TwistMix64::DiffuseA(pNonce * 0xE5B9501E121F3387ULL + 0xB598C99B2D02BF50ULL);
    std::uint64_t aNonceWordO = TwistMix64::DiffuseA(pNonce * 0xA83414DD4149A0ABULL + 0x804704D045D48B20ULL);
    std::uint64_t aNonceWordP = TwistMix64::DiffuseB(pNonce * 0x99F6F1A07017CCB5ULL + 0xD7A6B935A53CDDEEULL);
    std::uint64_t aDomainWordIngress = pConstants->mIngress;
    std::uint64_t aDomainWordScatter = pConstants->mScatter;
    std::uint64_t aDomainWordCross = pConstants->mCross;
    [[maybe_unused]] std::uint8_t *mSource = pWorkSpace->mSource;
    std::uint64_t aPrevious = *pPrevious;
    std::uint64_t aIngress = *pIngress;
    std::uint64_t aCarry = *pCarry;
    std::uint64_t aWandererA = *pWandererA;
    std::uint64_t aWandererB = *pWandererB;
    std::uint64_t aWandererC = *pWandererC;
    std::uint64_t aWandererD = *pWandererD;
    std::uint64_t aWandererE = *pWandererE;
    std::uint64_t aWandererF = *pWandererF;
    std::uint64_t aWandererG = *pWandererG;
    std::uint64_t aWandererH = *pWandererH;
    std::uint64_t aWandererI = *pWandererI;
    std::uint64_t aWandererJ = *pWandererJ;
    std::uint64_t aWandererK = *pWandererK;
    // KDF_A_B kdf_a_loop_b (start)
    {
        // KDF_A_B kdf_a_loop_b lane group
        // read from: aFireLaneA, aFireLaneB, aFireLaneC, aFireLaneD, aOperationLaneA, aOperationLaneB, aOperationLaneC
        // write to: aOperationLaneA, aOperationLaneB, aOperationLaneC, aOperationLaneD
    
        // kdf_a_loop_b loop 1
        // ingress from: aFireLaneA, aFireLaneB
        // ingress directions: aFireLaneA forward forced, aFireLaneB forward/backward random
        // cross from: aFireLaneC, aFireLaneD
        // cross directions: aFireLaneC backward forced, aFireLaneD backward/forward random
        // write to: aOperationLaneA
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = RotL64(aFireLaneA[((aIndex + 3032U)) & S_BLOCK1], 11U) ^ RotL64(aFireLaneB[((S_BLOCK1 - aIndex + 5199U)) & S_BLOCK1], 26U);
            aIngress = TwistMix64::DiffuseC(((aIngress ^ aDomainWordIngress) ^ aNonceWordK));
            //
            aCross = RotL64(aFireLaneC[((S_BLOCK1 - aIndex + 1533U)) & S_BLOCK1], 3U) ^ RotL64(aFireLaneD[((S_BLOCK1 - aIndex + 7731U)) & S_BLOCK1], 20U);
            aCross = TwistMix64::DiffuseB(((aCross ^ aDomainWordCross) ^ aNonceWordB));
            //
            aScatter = (RotL64(aIngress, 57U) ^ RotL64(aCarry, 5U)) ^ (RotL64(aCross, 18U) + RotL64(aPrevious, 39U));
            aScatter = TwistMix64::DiffuseA(((aScatter ^ aDomainWordScatter) ^ aNonceWordA));
            //
            aOrbiterH = ((aWandererA + RotL64(aPrevious, 23U)) + 9133751643283278896U) + aNonceWordJ;
            aOrbiterA = ((aWandererH + RotL64(aCross, 60U)) + 8971581804375380408U) + aNonceWordM;
            aOrbiterB = ((aWandererJ + RotL64(aIngress, 41U)) + RotL64(aCarry, 13U)) + 12559650383714566592U;
            aOrbiterF = (((aWandererB + RotL64(aScatter, 19U)) + RotL64(aCarry, 51U)) + 15753206088872859163U) + aOrbiterAssignSaltF[((aIndex + 21U)) & S_SALT1];
            aOrbiterK = (aWandererF + RotL64(aCross, 11U)) + 7640756270450762350U;
            aOrbiterD = ((aWandererD + RotL64(aIngress, 51U)) + 7340073357551376125U) + aNonceWordI;
            aOrbiterJ = (((aWandererG + RotL64(aScatter, 37U)) + 5270256573644196046U) + aOrbiterAssignSaltC[(((31U - aIndex) + 7U)) & S_SALT1]) + aNonceWordD;
            aOrbiterI = ((aWandererC + RotL64(aPrevious, 56U)) + RotL64(aCarry, 29U)) + 3567367996479995928U;
            aOrbiterG = (aWandererE + RotL64(aScatter, 5U)) + 11939634537492733738U;
            //
            aOrbiterH = (aOrbiterH + aOrbiterA) + 7051817732424527120U;
            aOrbiterB = (aOrbiterB ^ aOrbiterH) ^ 1730487669951837941U;
            aOrbiterB = RotL64((aOrbiterB * 15191634337956285841U), 13U);
            //
            aOrbiterF = (aOrbiterF + aOrbiterK) + 18009252467909454817U;
            aOrbiterD = (aOrbiterD ^ aOrbiterF) ^ 2361024272031696442U;
            aOrbiterD = RotL64((aOrbiterD * 15215151562500226027U), 27U);
            //
            aOrbiterJ = ((aOrbiterJ + aOrbiterD) + 15902755877642960397U) + aOrbiterUpdateSaltC[((aIndex + 19U)) & S_SALT1];
            aOrbiterI = (aOrbiterI ^ aOrbiterJ) ^ 12243517544704116184U;
            aOrbiterI = RotL64((aOrbiterI * 2576071074148141447U), 47U);
            //
            aOrbiterI = ((aOrbiterI + aOrbiterH) + 16846181962302186187U) + aOrbiterUpdateSaltA[(((31U - aIndex) + 23U)) & S_SALT1];
            aOrbiterK = (((aOrbiterK ^ aOrbiterI) ^ 636121425116506681U) ^ aOrbiterUpdateSaltD[(((31U - aIndex) + 24U)) & S_SALT1]) ^ aNonceWordL;
            aOrbiterK = RotL64((aOrbiterK * 17075030673338779993U), 19U);
            //
            aOrbiterA = (aOrbiterA + aOrbiterI) + 6887385655828217318U;
            aOrbiterF = ((aOrbiterF ^ aOrbiterA) ^ 3705834550934775862U) ^ aNonceWordO;
            aOrbiterF = RotL64((aOrbiterF * 11275428284929594435U), 41U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterG) + 11165142437077969438U;
            aOrbiterH = (aOrbiterH ^ aOrbiterD) ^ 6426659930331618269U;
            aOrbiterH = RotL64((aOrbiterH * 17170640810530893705U), 57U);
            //
            aOrbiterG = (aOrbiterG + aOrbiterJ) + 12629082390899315789U;
            aOrbiterA = ((aOrbiterA ^ aOrbiterG) ^ 4277510580069574724U) ^ aNonceWordG;
            aOrbiterA = RotL64((aOrbiterA * 9829125163412708305U), 53U);
            //
            aOrbiterB = (aOrbiterB + aOrbiterF) + 13814834144170469978U;
            aOrbiterJ = (aOrbiterJ ^ aOrbiterB) ^ 3698381854100295826U;
            aOrbiterJ = RotL64((aOrbiterJ * 5126359230872258015U), 3U);
            //
            aOrbiterK = ((aOrbiterK + aOrbiterB) + 11623170635983579937U) + aOrbiterUpdateSaltB[((aIndex + 10U)) & S_SALT1];
            aOrbiterG = (aOrbiterG ^ aOrbiterK) ^ 7247413650388803796U;
            aOrbiterG = RotL64((aOrbiterG * 3403219499465560059U), 37U);
            //
            aIngress = aOrbiterK ^ RotL64(aOrbiterI, 41U);
            aIngress = aIngress + (RotL64(aOrbiterA, 44U) ^ aOrbiterF);
            aIngress = aIngress + (aOrbiterB ^ RotL64(aOrbiterD, 23U));
            aIngress = aIngress + (aOrbiterG ^ RotL64(aOrbiterJ, 47U));
            aIngress = aIngress + RotL64(aOrbiterH, 11U);
            aIngress = TwistMix64::DiffuseC((aIngress + aScatter));
            //
            aWandererA = aWandererA + ((((RotL64(aCross, 58U) + aOrbiterH) + RotL64(aOrbiterA, 38U)) + RotL64(aCarry, 51U)) + aWandererUpdateSaltB[((aIndex + 27U)) & S_SALT1]);
            aWandererG = aWandererG ^ (((RotL64(aIngress, 39U) + RotL64(aOrbiterK, 57U)) + aOrbiterF) + aNonceWordA);
            aWandererE = aWandererE + ((RotL64(aPrevious, 19U) + aOrbiterH) + RotL64(aOrbiterF, 51U));
            aWandererC = aWandererC ^ ((RotL64(aScatter, 5U) + aOrbiterA) + RotL64(aOrbiterG, 5U));
            aWandererH = aWandererH + ((RotL64(aPrevious, 47U) + aOrbiterJ) + RotL64(aOrbiterK, 29U));
            aWandererB = aWandererB ^ ((RotL64(aCross, 51U) + RotL64(aOrbiterD, 18U)) + aOrbiterI);
            aWandererD = aWandererD + ((RotL64(aScatter, 43U) + RotL64(aOrbiterI, 23U)) + aOrbiterJ);
            aWandererF = aWandererF ^ ((RotL64(aIngress, 26U) + RotL64(aOrbiterD, 43U)) + aOrbiterK);
            aWandererJ = aWandererJ + (((((RotL64(aScatter, 13U) + RotL64(aOrbiterB, 11U)) + aOrbiterK) + RotL64(aCarry, 35U)) + aNonceWordN) + aWandererUpdateSaltE[((aIndex + 13U)) & S_SALT1]);
            //
            aCarry = aCarry + (aWandererC ^ RotL64(aWandererF, 43U));
            aCarry = aCarry + (aWandererD ^ RotL64(aWandererB, 35U));
            aCarry = aCarry + (aWandererE ^ RotL64(aWandererG, 30U));
            aCarry = aCarry + (aWandererA ^ RotL64(aWandererH, 47U));
            aCarry = aCarry + RotL64(aWandererJ, 27U);
            aCarry = aCarry + RotL64(aIngress, 23U);
            aCarry = TwistMix64::DiffuseC(aCarry);
            //
            aOperationLaneA[aIndex] = aIngress;
        }
    
        // kdf_a_loop_b loop 2
        // ingress from: aOperationLaneA, aFireLaneB, aFireLaneC
        // ingress directions: aOperationLaneA forward forced, aFireLaneB forward forced, aFireLaneC forward/backward random
        // cross from: aFireLaneA, aFireLaneD
        // cross directions: aFireLaneA backward forced, aFireLaneD backward/forward random
        // write to: aOperationLaneB
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aOperationLaneA[((aIndex + 16157U)) & S_BLOCK1], 3U) ^ RotL64(aFireLaneB[((aIndex + 14209U)) & S_BLOCK1], 13U));
            aIngress ^= RotL64(aFireLaneC[((S_BLOCK1 - aIndex + 9818U)) & S_BLOCK1], 39U);
            aIngress = TwistMix64::DiffuseC(((aIngress ^ aDomainWordIngress) ^ aNonceWordK));
            //
            aCross = RotL64(aFireLaneA[((S_BLOCK1 - aIndex + 11088U)) & S_BLOCK1], 29U) ^ RotL64(aFireLaneD[((aIndex + 14574U)) & S_BLOCK1], 60U);
            aCross = TwistMix64::DiffuseA(((aCross ^ aDomainWordCross) ^ aNonceWordI));
            //
            aScatter = (RotL64(aCarry, 27U) ^ RotL64(aPrevious, 42U)) ^ (RotL64(aIngress, 11U) + RotL64(aCross, 57U));
            aScatter = TwistMix64::DiffuseC(((aScatter ^ aDomainWordScatter) ^ aNonceWordC));
            //
            aOrbiterB = ((aWandererD + RotL64(aScatter, 34U)) + RotL64(aCarry, 21U)) + 8367680518550579791U;
            aOrbiterG = ((aWandererB + RotL64(aCross, 47U)) + 11491674725611181241U) + aOrbiterAssignSaltD[(((31U - aIndex) + 20U)) & S_SALT1];
            aOrbiterJ = (aWandererE + RotL64(aIngress, 5U)) + 16673861720782164214U;
            aOrbiterH = (aWandererH + RotL64(aPrevious, 11U)) + 9786610124108350855U;
            aOrbiterI = ((aWandererK + RotL64(aCross, 53U)) + RotL64(aCarry, 57U)) + 5745080601557577637U;
            aOrbiterC = ((aWandererC + RotL64(aPrevious, 19U)) + 1959402215131684684U) + aNonceWordM;
            aOrbiterD = ((aWandererJ + RotL64(aIngress, 43U)) + RotL64(aCarry, 37U)) + 6121650036079196522U;
            aOrbiterA = ((aWandererF + RotL64(aScatter, 23U)) + 12016309761037342392U) + aNonceWordL;
            aOrbiterK = ((aWandererA + RotL64(aIngress, 60U)) + 5986936646177049603U) + aOrbiterAssignSaltB[(((31U - aIndex) + 21U)) & S_SALT1];
            //
            aOrbiterB = (aOrbiterB + aOrbiterG) + 1000367700904043468U;
            aOrbiterJ = (aOrbiterJ ^ aOrbiterB) ^ 17425288243569101032U;
            aOrbiterJ = RotL64((aOrbiterJ * 2174614006719048535U), 13U);
            //
            aOrbiterH = (aOrbiterH + aOrbiterI) + 4856917474950325209U;
            aOrbiterB = (aOrbiterB ^ aOrbiterH) ^ 16312111093223166419U;
            aOrbiterB = RotL64((aOrbiterB * 11046477664487805241U), 57U);
            //
            aOrbiterC = (aOrbiterC + aOrbiterJ) + 456110002032422270U;
            aOrbiterH = (aOrbiterH ^ aOrbiterC) ^ 11393724374787795662U;
            aOrbiterH = RotL64((aOrbiterH * 1176984359123668389U), 27U);
            //
            aOrbiterJ = (aOrbiterJ + aOrbiterD) + 8378176867715697176U;
            aOrbiterI = (((aOrbiterI ^ aOrbiterJ) ^ 8086186452345234815U) ^ aOrbiterUpdateSaltD[((aIndex + 7U)) & S_SALT1]) ^ aNonceWordG;
            aOrbiterI = RotL64((aOrbiterI * 8450438271765985235U), 5U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterC) + 8470349167474173245U;
            aOrbiterA = ((aOrbiterA ^ aOrbiterD) ^ 2528229938740192694U) ^ aNonceWordF;
            aOrbiterA = RotL64((aOrbiterA * 8717790851266520943U), 43U);
            //
            aOrbiterG = ((aOrbiterG + aOrbiterK) + 13247168811545753141U) + aNonceWordH;
            aOrbiterD = (aOrbiterD ^ aOrbiterG) ^ 8745293957516815264U;
            aOrbiterD = RotL64((aOrbiterD * 14270617180621072619U), 35U);
            //
            aOrbiterK = ((aOrbiterK + aOrbiterB) + 6165915500564961987U) + aOrbiterUpdateSaltE[((aIndex + 10U)) & S_SALT1];
            aOrbiterC = (aOrbiterC ^ aOrbiterK) ^ 12015407798844173213U;
            aOrbiterC = RotL64((aOrbiterC * 3913451986559154153U), 51U);
            //
            aOrbiterI = ((aOrbiterI + aOrbiterA) + 545006684939922156U) + aOrbiterUpdateSaltF[((aIndex + 12U)) & S_SALT1];
            aOrbiterG = (aOrbiterG ^ aOrbiterI) ^ 16366753936267185001U;
            aOrbiterG = RotL64((aOrbiterG * 6495185976430013201U), 47U);
            //
            aOrbiterA = (((aOrbiterA + aOrbiterH) + 3097605623436091728U) + aOrbiterUpdateSaltC[(((31U - aIndex) + 11U)) & S_SALT1]) + aNonceWordP;
            aOrbiterK = (aOrbiterK ^ aOrbiterA) ^ 15950167830259022926U;
            aOrbiterK = RotL64((aOrbiterK * 4415538963984293323U), 21U);
            //
            aIngress = RotL64(aOrbiterG, 34U) ^ aOrbiterK;
            aIngress = aIngress + (RotL64(aOrbiterA, 43U) ^ aOrbiterC);
            aIngress = aIngress + (RotL64(aOrbiterH, 39U) ^ aOrbiterB);
            aIngress = aIngress + (aOrbiterJ ^ RotL64(aOrbiterI, 51U));
            aIngress = aIngress + RotL64(aOrbiterD, 21U);
            aIngress = TwistMix64::DiffuseC((aIngress + aScatter));
            //
            aWandererH = aWandererH ^ ((RotL64(aCross, 29U) + RotL64(aOrbiterB, 35U)) + aOrbiterJ);
            aWandererC = aWandererC + (((RotL64(aPrevious, 13U) + aOrbiterD) + RotL64(aOrbiterH, 11U)) + aNonceWordO);
            aWandererE = aWandererE ^ ((RotL64(aIngress, 58U) + aOrbiterC) + RotL64(aOrbiterK, 47U));
            aWandererD = aWandererD + ((RotL64(aScatter, 47U) + aOrbiterH) + RotL64(aOrbiterC, 22U));
            aWandererF = aWandererF ^ (((RotL64(aIngress, 5U) + aOrbiterB) + RotL64(aOrbiterA, 3U)) + aWandererUpdateSaltA[((aIndex + 9U)) & S_SALT1]);
            aWandererJ = aWandererJ + (((RotL64(aPrevious, 51U) + RotL64(aOrbiterG, 57U)) + aOrbiterB) + RotL64(aCarry, 19U));
            aWandererB = aWandererB ^ (((RotL64(aCross, 34U) + aOrbiterC) + RotL64(aOrbiterI, 53U)) + aWandererUpdateSaltF[((aIndex + 28U)) & S_SALT1]);
            aWandererA = aWandererA + ((((RotL64(aScatter, 39U) + aOrbiterG) + RotL64(aOrbiterH, 27U)) + RotL64(aCarry, 35U)) + aNonceWordC);
            aWandererK = aWandererK ^ ((RotL64(aIngress, 19U) + aOrbiterJ) + RotL64(aOrbiterK, 42U));
            //
            aCarry = aCarry + (RotL64(aWandererH, 53U) ^ aWandererF);
            aCarry = aCarry + (RotL64(aWandererE, 21U) ^ aWandererA);
            aCarry = aCarry + (aWandererC ^ RotL64(aWandererK, 47U));
            aCarry = aCarry + (RotL64(aWandererJ, 57U) ^ aWandererB);
            aCarry = aCarry + RotL64(aWandererD, 11U);
            aCarry = aCarry + RotL64(aIngress, 40U);
            aCarry = TwistMix64::DiffuseC(aCarry);
            //
            aOperationLaneB[S_BLOCK1 - aIndex] = aIngress;
        }
    
        // kdf_a_loop_b loop 3
        // ingress from: aOperationLaneB, aFireLaneD, aFireLaneA
        // ingress directions: aOperationLaneB forward forced, aFireLaneD forward forced, aFireLaneA forward/backward random
        // cross from: aOperationLaneA, aFireLaneB, aFireLaneC
        // cross directions: aOperationLaneA backward forced, aFireLaneB backward forced, aFireLaneC backward/forward random
        // write to: aOperationLaneC
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aOperationLaneB[((aIndex + 23993U)) & S_BLOCK1], 37U) ^ RotL64(aFireLaneD[((aIndex + 18225U)) & S_BLOCK1], 13U));
            aIngress ^= RotL64(aFireLaneA[((aIndex + 23794U)) & S_BLOCK1], 26U);
            aIngress = TwistMix64::DiffuseB(((aIngress ^ aDomainWordIngress) ^ aNonceWordB));
            //
            aCross = (RotL64(aOperationLaneA[((S_BLOCK1 - aIndex + 19614U)) & S_BLOCK1], 51U) ^ RotL64(aFireLaneB[((S_BLOCK1 - aIndex + 16787U)) & S_BLOCK1], 13U));
            aCross ^= RotL64(aFireLaneC[((S_BLOCK1 - aIndex + 21430U)) & S_BLOCK1], 30U);
            aCross = TwistMix64::DiffuseA(((aCross ^ aDomainWordCross) ^ aNonceWordN));
            //
            aScatter = (RotL64(aCarry, 41U) ^ RotL64(aPrevious, 4U)) + (RotL64(aCross, 23U) ^ RotL64(aIngress, 53U));
            aScatter = TwistMix64::DiffuseC(((aScatter ^ aDomainWordScatter) ^ aNonceWordB));
            //
            aOrbiterJ = ((aWandererI + RotL64(aScatter, 3U)) + RotL64(aCarry, 37U)) + 4179952823252098240U;
            aOrbiterH = ((aWandererJ + RotL64(aPrevious, 29U)) + 3745613452332101749U) + aOrbiterAssignSaltA[((aIndex + 29U)) & S_SALT1];
            aOrbiterG = (((aWandererB + RotL64(aIngress, 18U)) + RotL64(aCarry, 51U)) + 2955689793395307176U) + aNonceWordE;
            aOrbiterK = (aWandererC + RotL64(aCross, 41U)) + 5639060180251322019U;
            aOrbiterD = (aWandererK + RotL64(aIngress, 57U)) + 7901969163853586463U;
            aOrbiterF = (aWandererD + RotL64(aScatter, 23U)) + 2242166787816318119U;
            aOrbiterC = (((aWandererE + RotL64(aPrevious, 51U)) + RotL64(aCarry, 21U)) + 5239936443960750064U) + aNonceWordL;
            aOrbiterE = (aWandererG + RotL64(aCross, 47U)) + 13939136954732185558U;
            aOrbiterB = ((aWandererH + RotL64(aScatter, 10U)) + 17058884136712717463U) + aOrbiterAssignSaltE[((aIndex + 25U)) & S_SALT1];
            //
            aOrbiterJ = (aOrbiterJ + aOrbiterH) + 18148618660054585941U;
            aOrbiterG = (aOrbiterG ^ aOrbiterJ) ^ 7022023484530327814U;
            aOrbiterG = RotL64((aOrbiterG * 650100011311048589U), 35U);
            //
            aOrbiterK = (aOrbiterK + aOrbiterD) + 7722084537340095637U;
            aOrbiterF = ((aOrbiterF ^ aOrbiterK) ^ 11764151879690934182U) ^ aNonceWordM;
            aOrbiterF = RotL64((aOrbiterF * 12264384877711365655U), 53U);
            //
            aOrbiterC = ((aOrbiterC + aOrbiterF) + 16412785901758144708U) + aOrbiterUpdateSaltF[(((31U - aIndex) + 3U)) & S_SALT1];
            aOrbiterJ = (aOrbiterJ ^ aOrbiterC) ^ 9666718667728274824U;
            aOrbiterJ = RotL64((aOrbiterJ * 10865799822751771795U), 11U);
            //
            aOrbiterH = (aOrbiterH + aOrbiterK) + 4307127540152109364U;
            aOrbiterC = (aOrbiterC ^ aOrbiterH) ^ 2457646804702647606U;
            aOrbiterC = RotL64((aOrbiterC * 6340030928007058595U), 19U);
            //
            aOrbiterE = ((aOrbiterE + aOrbiterJ) + 3179394870088602208U) + aOrbiterUpdateSaltC[(((31U - aIndex) + 27U)) & S_SALT1];
            aOrbiterD = ((aOrbiterD ^ aOrbiterE) ^ 504977947273774249U) ^ aNonceWordI;
            aOrbiterD = RotL64((aOrbiterD * 16190282058883481551U), 57U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterG) + 16182729401018310837U;
            aOrbiterB = ((aOrbiterB ^ aOrbiterD) ^ 7110817020445860609U) ^ aOrbiterUpdateSaltD[((aIndex + 20U)) & S_SALT1];
            aOrbiterB = RotL64((aOrbiterB * 13371352088428584087U), 23U);
            //
            aOrbiterB = ((aOrbiterB + aOrbiterE) + 12960656706837391973U) + aNonceWordA;
            aOrbiterK = (aOrbiterK ^ aOrbiterB) ^ 7103806893724395904U;
            aOrbiterK = RotL64((aOrbiterK * 14365984439655979791U), 39U);
            //
            aOrbiterF = (aOrbiterF + aOrbiterB) + 1248300178080633527U;
            aOrbiterH = (aOrbiterH ^ aOrbiterF) ^ 7195473175424961337U;
            aOrbiterH = RotL64((aOrbiterH * 4633558992739305045U), 5U);
            //
            aOrbiterG = ((aOrbiterG + aOrbiterC) + 13007951568242991449U) + aOrbiterUpdateSaltE[(((31U - aIndex) + 13U)) & S_SALT1];
            aOrbiterE = ((aOrbiterE ^ aOrbiterG) ^ 10296811247653636372U) ^ aNonceWordH;
            aOrbiterE = RotL64((aOrbiterE * 16469682651380549395U), 47U);
            //
            aIngress = aOrbiterB ^ RotL64(aOrbiterG, 30U);
            aIngress = aIngress + (RotL64(aOrbiterK, 23U) ^ aOrbiterH);
            aIngress = aIngress + (RotL64(aOrbiterJ, 3U) ^ aOrbiterC);
            aIngress = aIngress + (aOrbiterD ^ RotL64(aOrbiterF, 19U));
            aIngress = aIngress + RotL64(aOrbiterE, 14U);
            aIngress = TwistMix64::DiffuseC((aIngress + aScatter));
            //
            aWandererC = aWandererC ^ ((RotL64(aIngress, 20U) + RotL64(aOrbiterH, 26U)) + aOrbiterC);
            aWandererE = aWandererE + ((RotL64(aPrevious, 47U) + aOrbiterH) + RotL64(aOrbiterG, 47U));
            aWandererB = aWandererB ^ (((RotL64(aCross, 35U) + RotL64(aOrbiterD, 53U)) + aOrbiterB) + aNonceWordF);
            aWandererG = aWandererG + ((((RotL64(aScatter, 53U) + aOrbiterD) + RotL64(aOrbiterJ, 37U)) + RotL64(aCarry, 13U)) + aNonceWordG);
            aWandererI = aWandererI ^ (((RotL64(aIngress, 41U) + aOrbiterJ) + RotL64(aOrbiterG, 43U)) + aWandererUpdateSaltC[(((31U - aIndex) + 26U)) & S_SALT1]);
            aWandererJ = aWandererJ + (((RotL64(aPrevious, 5U) + RotL64(aOrbiterJ, 21U)) + aOrbiterK) + RotL64(aCarry, 47U));
            aWandererD = aWandererD ^ (((RotL64(aScatter, 11U) + aOrbiterF) + RotL64(aOrbiterB, 3U)) + aWandererUpdateSaltD[((aIndex + 17U)) & S_SALT1]);
            aWandererK = aWandererK + (((RotL64(aCross, 30U) + aOrbiterF) + RotL64(aOrbiterC, 57U)) + aNonceWordO);
            aWandererH = aWandererH ^ (((RotL64(aScatter, 57U) + RotL64(aOrbiterE, 10U)) + aOrbiterK) + aNonceWordP);
            //
            aCarry = aCarry + (aWandererD ^ RotL64(aWandererG, 5U));
            aCarry = aCarry + (aWandererE ^ RotL64(aWandererC, 30U));
            aCarry = aCarry + (RotL64(aWandererJ, 57U) ^ aWandererK);
            aCarry = aCarry + (RotL64(aWandererB, 51U) ^ aWandererI);
            aCarry = aCarry + RotL64(aWandererH, 27U);
            aCarry = aCarry + RotL64(aIngress, 13U);
            aCarry = TwistMix64::DiffuseA(aCarry);
            //
            aOperationLaneC[aIndex] = aIngress;
        }
    
        // kdf_a_loop_b loop 4
        // ingress from: aOperationLaneC, aFireLaneC, aOperationLaneA
        // ingress directions: aOperationLaneC forward forced, aFireLaneC forward forced, aOperationLaneA forward/backward random
        // cross from: aOperationLaneB, aFireLaneD, aFireLaneA
        // cross directions: aOperationLaneB backward forced, aFireLaneD backward forced, aFireLaneA backward/forward random
        // write to: aOperationLaneD
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aOperationLaneC[((aIndex + 29995U)) & S_BLOCK1], 35U) ^ RotL64(aFireLaneC[((aIndex + 26855U)) & S_BLOCK1], 23U));
            aIngress ^= RotL64(aOperationLaneA[((S_BLOCK1 - aIndex + 31907U)) & S_BLOCK1], 13U);
            aIngress = TwistMix64::DiffuseC(((aIngress ^ aDomainWordIngress) ^ aNonceWordN));
            //
            aCross = (RotL64(aOperationLaneB[((S_BLOCK1 - aIndex + 31898U)) & S_BLOCK1], 3U) ^ RotL64(aFireLaneD[((S_BLOCK1 - aIndex + 29896U)) & S_BLOCK1], 53U));
            aCross ^= RotL64(aFireLaneA[((S_BLOCK1 - aIndex + 29458U)) & S_BLOCK1], 28U);
            aCross = TwistMix64::DiffuseA(((aCross ^ aDomainWordCross) ^ aNonceWordO));
            //
            aScatter = (RotL64(aPrevious, 19U) ^ RotL64(aCross, 5U)) ^ (RotL64(aCarry, 56U) + RotL64(aIngress, 37U));
            aScatter = TwistMix64::DiffuseA(((aScatter ^ aDomainWordScatter) ^ aNonceWordC));
            //
            aOrbiterD = (aWandererG + RotL64(aCross, 27U)) + 1364174714924216027U;
            aOrbiterG = (aWandererC + RotL64(aIngress, 42U)) + 13561796874229506613U;
            aOrbiterA = ((aWandererH + RotL64(aPrevious, 47U)) + 11845572344206238305U) + aNonceWordK;
            aOrbiterK = (((aWandererF + RotL64(aScatter, 19U)) + 15762708240326773763U) + aOrbiterAssignSaltF[((aIndex + 14U)) & S_SALT1]) + aNonceWordB;
            aOrbiterE = ((aWandererA + RotL64(aPrevious, 23U)) + RotL64(aCarry, 23U)) + 1157119665207900473U;
            aOrbiterJ = (((aWandererE + RotL64(aCross, 3U)) + RotL64(aCarry, 3U)) + 6823546624372055260U) + aOrbiterAssignSaltC[(((31U - aIndex) + 21U)) & S_SALT1];
            aOrbiterF = (aWandererJ + RotL64(aScatter, 56U)) + 14465564210523945121U;
            aOrbiterC = ((aWandererD + RotL64(aIngress, 35U)) + RotL64(aCarry, 53U)) + 10667464548080807531U;
            aOrbiterI = (aWandererK + RotL64(aPrevious, 51U)) + 13445737493224316575U;
            //
            aOrbiterD = ((aOrbiterD + aOrbiterG) + 3009837893785957665U) + aNonceWordL;
            aOrbiterA = (aOrbiterA ^ aOrbiterD) ^ 2886920524111083752U;
            aOrbiterA = RotL64((aOrbiterA * 15308180928967762543U), 43U);
            //
            aOrbiterK = (aOrbiterK + aOrbiterE) + 10886177449328249656U;
            aOrbiterJ = (aOrbiterJ ^ aOrbiterK) ^ 15067759884678100433U;
            aOrbiterJ = RotL64((aOrbiterJ * 5724566815989860041U), 47U);
            //
            aOrbiterF = ((aOrbiterF + aOrbiterD) + 18307930462682331536U) + aNonceWordI;
            aOrbiterC = (aOrbiterC ^ aOrbiterF) ^ 8791864377579255801U;
            aOrbiterC = RotL64((aOrbiterC * 9265158882471421767U), 35U);
            //
            aOrbiterC = (aOrbiterC + aOrbiterA) + 805797468642992351U;
            aOrbiterE = (aOrbiterE ^ aOrbiterC) ^ 5743305867058244964U;
            aOrbiterE = RotL64((aOrbiterE * 16263000753351131717U), 39U);
            //
            aOrbiterG = (aOrbiterG + aOrbiterC) + 17102025528234481273U;
            aOrbiterK = (((aOrbiterK ^ aOrbiterG) ^ 1841579177327486899U) ^ aOrbiterUpdateSaltA[((aIndex + 20U)) & S_SALT1]) ^ aNonceWordA;
            aOrbiterK = RotL64((aOrbiterK * 3841603385577825265U), 21U);
            //
            aOrbiterE = (aOrbiterE + aOrbiterI) + 2189493507896508972U;
            aOrbiterF = (aOrbiterF ^ aOrbiterE) ^ 18209567010094914374U;
            aOrbiterF = RotL64((aOrbiterF * 3737080408976852351U), 5U);
            //
            aOrbiterA = (aOrbiterA + aOrbiterK) + 6697069234216868330U;
            aOrbiterI = ((aOrbiterI ^ aOrbiterA) ^ 927471474577415372U) ^ aOrbiterUpdateSaltC[(((31U - aIndex) + 5U)) & S_SALT1];
            aOrbiterI = RotL64((aOrbiterI * 10680760991009199309U), 53U);
            //
            aOrbiterJ = ((aOrbiterJ + aOrbiterF) + 13155854301197725408U) + aOrbiterUpdateSaltE[(((31U - aIndex) + 25U)) & S_SALT1];
            aOrbiterG = (aOrbiterG ^ aOrbiterJ) ^ 1014625081915435892U;
            aOrbiterG = RotL64((aOrbiterG * 11592754232949990435U), 13U);
            //
            aOrbiterI = (aOrbiterI + aOrbiterJ) + 12697209921410914931U;
            aOrbiterD = ((aOrbiterD ^ aOrbiterI) ^ 11555096613655648647U) ^ aOrbiterUpdateSaltB[(((31U - aIndex) + 29U)) & S_SALT1];
            aOrbiterD = RotL64((aOrbiterD * 4598821388864997089U), 27U);
            //
            aIngress = RotL64(aOrbiterE, 43U) ^ aOrbiterF;
            aIngress = aIngress + (aOrbiterJ ^ RotL64(aOrbiterD, 23U));
            aIngress = aIngress + (RotL64(aOrbiterA, 28U) ^ aOrbiterI);
            aIngress = aIngress + (RotL64(aOrbiterC, 57U) ^ aOrbiterG);
            aIngress = aIngress + RotL64(aOrbiterK, 3U);
            aIngress = TwistMix64::DiffuseC((aIngress + aScatter));
            //
            aWandererJ = aWandererJ ^ ((RotL64(aCross, 13U) + aOrbiterD) + RotL64(aOrbiterJ, 53U));
            aWandererG = aWandererG + ((((RotL64(aIngress, 28U) + RotL64(aOrbiterC, 30U)) + aOrbiterG) + RotL64(aCarry, 35U)) + aNonceWordE);
            aWandererA = aWandererA ^ ((RotL64(aPrevious, 41U) + aOrbiterA) + RotL64(aOrbiterC, 5U));
            aWandererC = aWandererC + ((((RotL64(aScatter, 47U) + aOrbiterI) + RotL64(aOrbiterD, 11U)) + RotL64(aCarry, 43U)) + aNonceWordP);
            aWandererE = aWandererE ^ ((RotL64(aCross, 23U) + aOrbiterJ) + RotL64(aOrbiterI, 43U));
            aWandererK = aWandererK + (((RotL64(aScatter, 3U) + aOrbiterF) + RotL64(aOrbiterE, 23U)) + aWandererUpdateSaltB[((aIndex + 6U)) & S_SALT1]);
            aWandererH = aWandererH ^ (((RotL64(aPrevious, 51U) + aOrbiterG) + RotL64(aOrbiterK, 38U)) + aWandererUpdateSaltE[((aIndex + 9U)) & S_SALT1]);
            aWandererD = aWandererD + (((RotL64(aIngress, 35U) + RotL64(aOrbiterD, 57U)) + aOrbiterA) + aNonceWordH);
            aWandererF = aWandererF ^ ((RotL64(aCross, 56U) + aOrbiterE) + RotL64(aOrbiterA, 47U));
            //
            aCarry = aCarry + (RotL64(aWandererG, 34U) ^ aWandererF);
            aCarry = aCarry + (RotL64(aWandererK, 57U) ^ aWandererA);
            aCarry = aCarry + (aWandererC ^ RotL64(aWandererD, 11U));
            aCarry = aCarry + (RotL64(aWandererJ, 47U) ^ aWandererE);
            aCarry = aCarry + RotL64(aWandererH, 3U);
            aCarry = aCarry + RotL64(aIngress, 19U);
            aCarry = TwistMix64::DiffuseC(aCarry);
            //
            aOperationLaneD[S_BLOCK1 - aIndex] = aIngress;
        }
    }
    // KDF_A_B kdf_a_loop_b (end)
    *pPrevious = aPrevious;
    *pIngress = aIngress;
    *pCarry = aCarry;
    *pWandererA = aWandererA;
    *pWandererB = aWandererB;
    *pWandererC = aWandererC;
    *pWandererD = aWandererD;
    *pWandererE = aWandererE;
    *pWandererF = aWandererF;
    *pWandererG = aWandererG;
    *pWandererH = aWandererH;
    *pWandererI = aWandererI;
    *pWandererJ = aWandererJ;
    *pWandererK = aWandererK;
}

void TwistExpander_Exercea_Arx::KDF_A_C(TwistWorkSpace *pWorkSpace,
                     std::uint64_t pNonce,
                     TwistDomainConstants *pConstants,
                     TwistDomainSaltSet *pDomainSaltSet,
                     std::uint64_t *pPrevious,
                     std::uint64_t *pIngress,
                     std::uint64_t *pCarry,
                     std::uint64_t *pWandererA,
                     std::uint64_t *pWandererB,
                     std::uint64_t *pWandererC,
                     std::uint64_t *pWandererD,
                     std::uint64_t *pWandererE,
                     std::uint64_t *pWandererF,
                     std::uint64_t *pWandererG,
                     std::uint64_t *pWandererH,
                     std::uint64_t *pWandererI,
                     std::uint64_t *pWandererJ,
                     std::uint64_t *pWandererK) {
    [[maybe_unused]] std::uint64_t *aOrbiterAssignSaltA = pDomainSaltSet->mOrbiterAssign.mSaltA;
    [[maybe_unused]] std::uint64_t *aOrbiterAssignSaltB = pDomainSaltSet->mOrbiterAssign.mSaltB;
    [[maybe_unused]] std::uint64_t *aOrbiterAssignSaltC = pDomainSaltSet->mOrbiterAssign.mSaltC;
    [[maybe_unused]] std::uint64_t *aOrbiterAssignSaltD = pDomainSaltSet->mOrbiterAssign.mSaltD;
    [[maybe_unused]] std::uint64_t *aOrbiterAssignSaltE = pDomainSaltSet->mOrbiterAssign.mSaltE;
    [[maybe_unused]] std::uint64_t *aOrbiterAssignSaltF = pDomainSaltSet->mOrbiterAssign.mSaltF;
    [[maybe_unused]] std::uint64_t *aOrbiterUpdateSaltA = pDomainSaltSet->mOrbiterUpdate.mSaltA;
    [[maybe_unused]] std::uint64_t *aOrbiterUpdateSaltB = pDomainSaltSet->mOrbiterUpdate.mSaltB;
    [[maybe_unused]] std::uint64_t *aOrbiterUpdateSaltC = pDomainSaltSet->mOrbiterUpdate.mSaltC;
    [[maybe_unused]] std::uint64_t *aOrbiterUpdateSaltD = pDomainSaltSet->mOrbiterUpdate.mSaltD;
    [[maybe_unused]] std::uint64_t *aOrbiterUpdateSaltE = pDomainSaltSet->mOrbiterUpdate.mSaltE;
    [[maybe_unused]] std::uint64_t *aOrbiterUpdateSaltF = pDomainSaltSet->mOrbiterUpdate.mSaltF;
    [[maybe_unused]] std::uint64_t *aWandererUpdateSaltA = pDomainSaltSet->mWandererUpdate.mSaltA;
    [[maybe_unused]] std::uint64_t *aWandererUpdateSaltB = pDomainSaltSet->mWandererUpdate.mSaltB;
    [[maybe_unused]] std::uint64_t *aWandererUpdateSaltC = pDomainSaltSet->mWandererUpdate.mSaltC;
    [[maybe_unused]] std::uint64_t *aWandererUpdateSaltD = pDomainSaltSet->mWandererUpdate.mSaltD;
    [[maybe_unused]] std::uint64_t *aWandererUpdateSaltE = pDomainSaltSet->mWandererUpdate.mSaltE;
    [[maybe_unused]] std::uint64_t *aWandererUpdateSaltF = pDomainSaltSet->mWandererUpdate.mSaltF;
    [[maybe_unused]] std::uint8_t *aWorkLaneA = pWorkSpace->mWorkLaneA;
    [[maybe_unused]] std::uint8_t *aWorkLaneB = pWorkSpace->mWorkLaneB;
    [[maybe_unused]] std::uint8_t *aWorkLaneC = pWorkSpace->mWorkLaneC;
    [[maybe_unused]] std::uint8_t *aWorkLaneD = pWorkSpace->mWorkLaneD;
    [[maybe_unused]] std::uint8_t *aOperationLaneA = pWorkSpace->mOperationLaneA;
    [[maybe_unused]] std::uint8_t *aOperationLaneB = pWorkSpace->mOperationLaneB;
    [[maybe_unused]] std::uint8_t *aOperationLaneC = pWorkSpace->mOperationLaneC;
    [[maybe_unused]] std::uint8_t *aOperationLaneD = pWorkSpace->mOperationLaneD;
    [[maybe_unused]] std::uint8_t *aFireLaneA = pWorkSpace->mFireLaneA;
    [[maybe_unused]] std::uint8_t *aFireLaneB = pWorkSpace->mFireLaneB;
    [[maybe_unused]] std::uint8_t *aFireLaneC = pWorkSpace->mFireLaneC;
    [[maybe_unused]] std::uint8_t *aFireLaneD = pWorkSpace->mFireLaneD;
    std::uint64_t aCross = 0; std::uint64_t aScatter = 0;

    std::uint64_t aOrbiterA = 0; std::uint64_t aOrbiterB = 0; std::uint64_t aOrbiterC = 0; std::uint64_t aOrbiterD = 0;
    std::uint64_t aOrbiterE = 0; std::uint64_t aOrbiterG = 0; std::uint64_t aOrbiterH = 0; std::uint64_t aOrbiterJ = 0;
    std::uint64_t aOrbiterK = 0;

    // [kdf-a arx]
    std::uint64_t aNonceWordA = TwistMix64::DiffuseB(pNonce * 0x900DF85494B8E5DBULL + 0xA30855BB50144ABCULL);
    std::uint64_t aNonceWordB = TwistMix64::DiffuseC(pNonce * 0x80FED01308FE954FULL + 0xBE4BC82D8DA19161ULL);
    std::uint64_t aNonceWordC = TwistMix64::DiffuseC(pNonce * 0xB537DB5ED6718807ULL + 0xCD7EFCF1F4080103ULL);
    std::uint64_t aNonceWordD = TwistMix64::DiffuseC(pNonce * 0xF4370C6E25840D31ULL + 0xE3C9AEDEC01A31FCULL);
    std::uint64_t aNonceWordE = TwistMix64::DiffuseA(pNonce * 0xD56C3957B622C5C1ULL + 0x9D35047C2C347F9AULL);
    std::uint64_t aNonceWordF = TwistMix64::DiffuseB(pNonce * 0xEEC019B56B032CF5ULL + 0xB3C9890979F265E4ULL);
    std::uint64_t aNonceWordG = TwistMix64::DiffuseC(pNonce * 0xEFE4599B6204586BULL + 0x81DB86083ABE07D4ULL);
    std::uint64_t aNonceWordH = TwistMix64::DiffuseA(pNonce * 0xA75E31FA83469D21ULL + 0xC08BDE82B7AAA13BULL);
    std::uint64_t aNonceWordI = TwistMix64::DiffuseC(pNonce * 0x95D5F36EDBFF3741ULL + 0xEC2D169879D8F087ULL);
    std::uint64_t aNonceWordJ = TwistMix64::DiffuseA(pNonce * 0xCF6D92E0BC7034EDULL + 0x9DB268126D30FA14ULL);
    std::uint64_t aNonceWordK = TwistMix64::DiffuseB(pNonce * 0x9530AB0139164921ULL + 0xBF2B39A0FC9908E8ULL);
    std::uint64_t aNonceWordL = TwistMix64::DiffuseA(pNonce * 0xBCD647F8BF7B7A9DULL + 0x86221EB78AC88170ULL);
    std::uint64_t aNonceWordM = TwistMix64::DiffuseA(pNonce * 0xF69557C4727C9325ULL + 0xD7D5CE245369986CULL);
    std::uint64_t aNonceWordN = TwistMix64::DiffuseB(pNonce * 0x814A6A7AB0DA69AFULL + 0xAE0CD35433EAE499ULL);
    std::uint64_t aNonceWordO = TwistMix64::DiffuseC(pNonce * 0xB10E19318D3C8B07ULL + 0x82BCB1BA36E1B10BULL);
    std::uint64_t aNonceWordP = TwistMix64::DiffuseA(pNonce * 0xC5DA29A380B37255ULL + 0x84C3361D4EAD360EULL);
    std::uint64_t aDomainWordIngress = pConstants->mIngress;
    std::uint64_t aDomainWordScatter = pConstants->mScatter;
    std::uint64_t aDomainWordCross = pConstants->mCross;
    [[maybe_unused]] std::uint8_t *mSource = pWorkSpace->mSource;
    std::uint64_t aPrevious = *pPrevious;
    std::uint64_t aIngress = *pIngress;
    std::uint64_t aCarry = *pCarry;
    std::uint64_t aWandererA = *pWandererA;
    std::uint64_t aWandererB = *pWandererB;
    std::uint64_t aWandererC = *pWandererC;
    std::uint64_t aWandererD = *pWandererD;
    std::uint64_t aWandererE = *pWandererE;
    std::uint64_t aWandererF = *pWandererF;
    std::uint64_t aWandererG = *pWandererG;
    std::uint64_t aWandererH = *pWandererH;
    std::uint64_t aWandererI = *pWandererI;
    std::uint64_t aWandererJ = *pWandererJ;
    std::uint64_t aWandererK = *pWandererK;
    // KDF_A_C kdf_a_loop_c (start)
    {
        // KDF_A_C kdf_a_loop_c lane group
        // read from: aOperationLaneA, aOperationLaneB, aFireLaneB, aOperationLaneC, aOperationLaneD, aWorkLaneA, aFireLaneA, aWorkLaneB, aFireLaneC, aWorkLaneC, aFireLaneD
        // write to: aWorkLaneA, aWorkLaneB, aWorkLaneC, aWorkLaneD
    
        // kdf_a_loop_c loop 1
        // ingress from: aOperationLaneA, aOperationLaneB, aFireLaneB
        // ingress directions: aOperationLaneA forward forced, aOperationLaneB forward forced, aFireLaneB forward/backward random
        // cross from: aOperationLaneC, aOperationLaneD
        // cross directions: aOperationLaneC backward forced, aOperationLaneD backward/forward random
        // write to: aWorkLaneA
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aOperationLaneA[((aIndex + 1997U)) & S_BLOCK1], 19U) ^ RotL64(aOperationLaneB[((aIndex + 5822U)) & S_BLOCK1], 5U));
            aIngress ^= RotL64(aFireLaneB[((aIndex + 8159U)) & S_BLOCK1], 29U);
            aIngress = TwistMix64::DiffuseA(((aIngress ^ aDomainWordIngress) ^ aNonceWordJ));
            //
            aCross = RotL64(aOperationLaneC[((S_BLOCK1 - aIndex + 5868U)) & S_BLOCK1], 5U) ^ RotL64(aOperationLaneD[((S_BLOCK1 - aIndex + 8101U)) & S_BLOCK1], 29U);
            aCross = TwistMix64::DiffuseA(((aCross ^ aDomainWordCross) ^ aNonceWordD));
            //
            aScatter = (RotL64(aPrevious, 47U) ^ RotL64(aCarry, 21U)) + (RotL64(aCross, 35U) ^ RotL64(aIngress, 60U));
            aScatter = TwistMix64::DiffuseB(((aScatter ^ aDomainWordScatter) ^ aNonceWordF));
            //
            aOrbiterE = (((aWandererG + RotL64(aCross, 51U)) + RotL64(aCarry, 5U)) + 6467297102954816305U) + aNonceWordI;
            aOrbiterA = (((aWandererD + RotL64(aPrevious, 23U)) + RotL64(aCarry, 51U)) + 7921154109831114952U) + aOrbiterAssignSaltE[(((31U - aIndex) + 27U)) & S_SALT1];
            aOrbiterG = ((aWandererA + RotL64(aScatter, 14U)) + 5701131763215638919U) + aNonceWordF;
            aOrbiterB = ((aWandererB + RotL64(aIngress, 41U)) + RotL64(aCarry, 39U)) + 10022999076719002684U;
            aOrbiterK = ((aWandererH + RotL64(aPrevious, 5U)) + 4367135243038982316U) + aOrbiterAssignSaltD[((aIndex + 7U)) & S_SALT1];
            //
            aOrbiterE = ((aOrbiterE + aOrbiterA) + 14445846824810383592U) + aOrbiterUpdateSaltD[(((31U - aIndex) + 23U)) & S_SALT1];
            aOrbiterG = (aOrbiterG ^ aOrbiterE) ^ 7683697954545773253U;
            aOrbiterG = RotL64((aOrbiterG * 4832124801510084629U), 35U);
            //
            aOrbiterG = (aOrbiterG + aOrbiterB) + 17517006750428030899U;
            aOrbiterK = ((aOrbiterK ^ aOrbiterG) ^ 2052484792684025476U) ^ aNonceWordA;
            aOrbiterK = RotL64((aOrbiterK * 12463117571122469643U), 3U);
            //
            aOrbiterA = ((aOrbiterA + aOrbiterG) + 6279463052085808926U) + aOrbiterUpdateSaltE[((aIndex + 19U)) & S_SALT1];
            aOrbiterB = ((aOrbiterB ^ aOrbiterA) ^ 679280153651813684U) ^ aOrbiterUpdateSaltF[((aIndex + 9U)) & S_SALT1];
            aOrbiterB = RotL64((aOrbiterB * 3047031560593583881U), 53U);
            //
            aOrbiterB = (((aOrbiterB + aOrbiterK) + 2939516520188460569U) + aOrbiterUpdateSaltC[(((31U - aIndex) + 12U)) & S_SALT1]) + aNonceWordC;
            aOrbiterE = ((aOrbiterE ^ aOrbiterB) ^ 1960616434964712325U) ^ aNonceWordL;
            aOrbiterE = RotL64((aOrbiterE * 15145998415466343039U), 21U);
            //
            aOrbiterK = (aOrbiterK + aOrbiterE) + 12273819390719947361U;
            aOrbiterA = (aOrbiterA ^ aOrbiterK) ^ 5685033154709449397U;
            aOrbiterA = RotL64((aOrbiterA * 9845666295874714959U), 11U);
            //
            aIngress = RotL64(aOrbiterG, 51U) ^ aOrbiterE;
            aIngress = aIngress + (RotL64(aOrbiterA, 3U) ^ aOrbiterK);
            aIngress = aIngress + RotL64(aOrbiterB, 39U);
            aIngress = TwistMix64::DiffuseA((aIngress + aScatter));
            //
            aWandererG = aWandererG + (((RotL64(aPrevious, 57U) + RotL64(aOrbiterA, 14U)) + aOrbiterK) + RotL64(aCarry, 51U));
            aWandererD = aWandererD ^ ((((RotL64(aIngress, 13U) + aOrbiterG) + RotL64(aOrbiterE, 35U)) + aNonceWordM) + aWandererUpdateSaltF[((aIndex + 14U)) & S_SALT1]);
            aWandererA = aWandererA + (((RotL64(aScatter, 39U) + RotL64(aOrbiterA, 23U)) + aOrbiterB) + RotL64(aCarry, 23U));
            aWandererH = aWandererH ^ ((((RotL64(aCross, 22U) + RotL64(aOrbiterE, 43U)) + aOrbiterB) + aNonceWordE) + aWandererUpdateSaltC[(((31U - aIndex) + 21U)) & S_SALT1]);
            aWandererB = aWandererB + ((RotL64(aIngress, 5U) + RotL64(aOrbiterE, 3U)) + aOrbiterK);
            //
            aCarry = aCarry + (aWandererH ^ RotL64(aWandererG, 13U));
            aCarry = aCarry + (RotL64(aWandererA, 47U) ^ aWandererB);
            aCarry = aCarry + RotL64(aWandererD, 57U);
            aCarry = aCarry + RotL64(aIngress, 5U);
            aCarry = TwistMix64::DiffuseA(aCarry);
            //
            aWorkLaneA[aIndex] = aIngress;
        }
    
        // kdf_a_loop_c loop 2
        // ingress from: aWorkLaneA, aOperationLaneC, aFireLaneA
        // ingress directions: aWorkLaneA forward forced, aOperationLaneC forward forced, aFireLaneA forward/backward random
        // cross from: aOperationLaneA, aOperationLaneD, aOperationLaneB
        // cross directions: aOperationLaneA backward forced, aOperationLaneD backward forced, aOperationLaneB backward/forward random
        // write to: aWorkLaneB
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aWorkLaneA[((aIndex + 9342U)) & S_BLOCK1], 41U) ^ RotL64(aOperationLaneC[((aIndex + 13594U)) & S_BLOCK1], 22U));
            aIngress ^= RotL64(aFireLaneA[((aIndex + 9750U)) & S_BLOCK1], 53U);
            aIngress = TwistMix64::DiffuseA(((aIngress ^ aDomainWordIngress) ^ aNonceWordO));
            //
            aCross = (RotL64(aOperationLaneA[((S_BLOCK1 - aIndex + 11642U)) & S_BLOCK1], 13U) ^ RotL64(aOperationLaneD[((S_BLOCK1 - aIndex + 11492U)) & S_BLOCK1], 60U));
            aCross ^= RotL64(aOperationLaneB[((aIndex + 15809U)) & S_BLOCK1], 29U);
            aCross = TwistMix64::DiffuseA(((aCross ^ aDomainWordCross) ^ aNonceWordI));
            //
            aScatter = (RotL64(aCross, 11U) + RotL64(aPrevious, 26U)) ^ (RotL64(aIngress, 53U) ^ RotL64(aCarry, 41U));
            aScatter = TwistMix64::DiffuseA(((aScatter ^ aDomainWordScatter) ^ aNonceWordA));
            //
            aOrbiterK = (((aWandererD + RotL64(aCross, 19U)) + RotL64(aCarry, 5U)) + 11450949896247900941U) + aOrbiterAssignSaltF[(((31U - aIndex) + 25U)) & S_SALT1];
            aOrbiterH = (((aWandererH + RotL64(aPrevious, 35U)) + RotL64(aCarry, 19U)) + 3905542253538116335U) + aNonceWordG;
            aOrbiterA = ((aWandererG + RotL64(aIngress, 11U)) + 9529740545977785305U) + aNonceWordN;
            aOrbiterD = ((((aWandererJ + RotL64(aScatter, 60U)) + RotL64(aCarry, 43U)) + 1856876631533143492U) + aOrbiterAssignSaltB[((aIndex + 23U)) & S_SALT1]) + aNonceWordD;
            aOrbiterJ = (aWandererB + RotL64(aPrevious, 51U)) + 84253466320181686U;
            //
            aOrbiterK = (((aOrbiterK + aOrbiterH) + 12577480918745432444U) + aOrbiterUpdateSaltE[((aIndex + 14U)) & S_SALT1]) + aNonceWordP;
            aOrbiterA = ((aOrbiterA ^ aOrbiterK) ^ 5625703170397704029U) ^ aOrbiterUpdateSaltA[(((31U - aIndex) + 7U)) & S_SALT1];
            aOrbiterA = RotL64((aOrbiterA * 13583960724598036659U), 57U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterA) + 694608607323629282U;
            aOrbiterK = (aOrbiterK ^ aOrbiterD) ^ 3993981243536262204U;
            aOrbiterK = RotL64((aOrbiterK * 2502835860198146381U), 29U);
            //
            aOrbiterH = (((aOrbiterH + aOrbiterD) + 4119215953484892051U) + aOrbiterUpdateSaltD[((aIndex + 12U)) & S_SALT1]) + aNonceWordA;
            aOrbiterJ = (aOrbiterJ ^ aOrbiterH) ^ 8785040118556157146U;
            aOrbiterJ = RotL64((aOrbiterJ * 17113521266125471625U), 11U);
            //
            aOrbiterA = ((aOrbiterA + aOrbiterJ) + 16234403619456882890U) + aNonceWordC;
            aOrbiterH = (aOrbiterH ^ aOrbiterA) ^ 10398727475672860610U;
            aOrbiterH = RotL64((aOrbiterH * 5086871400049644715U), 3U);
            //
            aOrbiterJ = ((aOrbiterJ + aOrbiterK) + 18327987141759096769U) + aOrbiterUpdateSaltB[((aIndex + 29U)) & S_SALT1];
            aOrbiterD = ((aOrbiterD ^ aOrbiterJ) ^ 2645964788056875452U) ^ aNonceWordK;
            aOrbiterD = RotL64((aOrbiterD * 8778681366114628045U), 43U);
            //
            aIngress = RotL64(aOrbiterA, 57U) ^ aOrbiterJ;
            aIngress = aIngress + (RotL64(aOrbiterD, 5U) ^ aOrbiterK);
            aIngress = aIngress + RotL64(aOrbiterH, 18U);
            aIngress = TwistMix64::DiffuseA((aIngress + aScatter));
            //
            aWandererB = aWandererB + (((RotL64(aIngress, 57U) + RotL64(aOrbiterJ, 22U)) + aOrbiterA) + aNonceWordJ);
            aWandererG = aWandererG ^ (((RotL64(aScatter, 4U) + RotL64(aOrbiterH, 5U)) + aOrbiterK) + aWandererUpdateSaltE[(((31U - aIndex) + 19U)) & S_SALT1]);
            aWandererH = aWandererH + ((((RotL64(aPrevious, 47U) + aOrbiterA) + RotL64(aOrbiterK, 57U)) + RotL64(aCarry, 57U)) + aWandererUpdateSaltA[(((31U - aIndex) + 17U)) & S_SALT1]);
            aWandererD = aWandererD ^ (((RotL64(aCross, 13U) + RotL64(aOrbiterH, 43U)) + aOrbiterD) + aNonceWordE);
            aWandererJ = aWandererJ + (((RotL64(aIngress, 37U) + aOrbiterJ) + RotL64(aOrbiterK, 13U)) + RotL64(aCarry, 23U));
            //
            aCarry = aCarry + (aWandererG ^ RotL64(aWandererJ, 13U));
            aCarry = aCarry + (RotL64(aWandererD, 3U) ^ aWandererB);
            aCarry = aCarry + RotL64(aWandererH, 35U);
            aCarry = aCarry + RotL64(aIngress, 22U);
            aCarry = TwistMix64::DiffuseC(aCarry);
            //
            aWorkLaneB[S_BLOCK1 - aIndex] = aIngress;
        }
    
        // kdf_a_loop_c loop 3
        // ingress from: aWorkLaneB, aOperationLaneD, aFireLaneC
        // ingress directions: aWorkLaneB forward forced, aOperationLaneD forward forced, aFireLaneC forward/backward random
        // cross from: aWorkLaneA, aOperationLaneB, aOperationLaneC
        // cross directions: aWorkLaneA backward forced, aOperationLaneB backward forced, aOperationLaneC backward/forward random
        // write to: aWorkLaneC
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aWorkLaneB[((aIndex + 19542U)) & S_BLOCK1], 5U) ^ RotL64(aOperationLaneD[((aIndex + 19418U)) & S_BLOCK1], 35U));
            aIngress ^= RotL64(aFireLaneC[((S_BLOCK1 - aIndex + 23995U)) & S_BLOCK1], 60U);
            aIngress = TwistMix64::DiffuseB(((aIngress ^ aDomainWordIngress) ^ aNonceWordD));
            //
            aCross = (RotL64(aWorkLaneA[((S_BLOCK1 - aIndex + 18100U)) & S_BLOCK1], 58U) ^ RotL64(aOperationLaneB[((S_BLOCK1 - aIndex + 23548U)) & S_BLOCK1], 19U));
            aCross ^= RotL64(aOperationLaneC[((aIndex + 16460U)) & S_BLOCK1], 39U);
            aCross = TwistMix64::DiffuseC(((aCross ^ aDomainWordCross) ^ aNonceWordJ));
            //
            aScatter = (RotL64(aCarry, 41U) ^ RotL64(aIngress, 6U)) ^ (RotL64(aCross, 19U) + RotL64(aPrevious, 53U));
            aScatter = TwistMix64::DiffuseB(((aScatter ^ aDomainWordScatter) ^ aNonceWordA));
            //
            aOrbiterG = (((aWandererH + RotL64(aScatter, 11U)) + RotL64(aCarry, 47U)) + 10812151398716051703U) + aNonceWordL;
            aOrbiterC = ((aWandererJ + RotL64(aPrevious, 53U)) + RotL64(aCarry, 35U)) + 18202551453336003710U;
            aOrbiterB = (((aWandererG + RotL64(aIngress, 20U)) + 9434410809101973752U) + aOrbiterAssignSaltC[((aIndex + 13U)) & S_SALT1]) + aNonceWordP;
            aOrbiterK = ((((aWandererE + RotL64(aCross, 3U)) + RotL64(aCarry, 19U)) + 12955829998028534045U) + aOrbiterAssignSaltA[(((31U - aIndex) + 9U)) & S_SALT1]) + aNonceWordN;
            aOrbiterH = ((aWandererC + RotL64(aPrevious, 39U)) + 12271740641929640181U) + aNonceWordB;
            //
            aOrbiterG = (aOrbiterG + aOrbiterC) + 14009351527014534752U;
            aOrbiterB = (aOrbiterB ^ aOrbiterG) ^ 4316296955679133450U;
            aOrbiterB = RotL64((aOrbiterB * 11582128345511775161U), 13U);
            //
            aOrbiterC = ((aOrbiterC + aOrbiterB) + 16473324966997442872U) + aOrbiterUpdateSaltA[(((31U - aIndex) + 19U)) & S_SALT1];
            aOrbiterK = ((aOrbiterK ^ aOrbiterC) ^ 15735123324965019802U) ^ aNonceWordE;
            aOrbiterK = RotL64((aOrbiterK * 5624078184997601019U), 29U);
            //
            aOrbiterH = ((aOrbiterH + aOrbiterG) + 17656375090484080236U) + aOrbiterUpdateSaltF[((aIndex + 29U)) & S_SALT1];
            aOrbiterC = ((aOrbiterC ^ aOrbiterH) ^ 16066325053456055298U) ^ aNonceWordG;
            aOrbiterC = RotL64((aOrbiterC * 17912970706985130327U), 5U);
            //
            aOrbiterB = (aOrbiterB + aOrbiterK) + 12908968778503516903U;
            aOrbiterH = (aOrbiterH ^ aOrbiterB) ^ 12761433987676836197U;
            aOrbiterH = RotL64((aOrbiterH * 1023329467480907925U), 47U);
            //
            aOrbiterK = (((aOrbiterK + aOrbiterH) + 12737513138040664509U) + aOrbiterUpdateSaltC[((aIndex + 7U)) & S_SALT1]) + aNonceWordM;
            aOrbiterG = ((aOrbiterG ^ aOrbiterK) ^ 14535795767570998392U) ^ aOrbiterUpdateSaltE[((aIndex + 5U)) & S_SALT1];
            aOrbiterG = RotL64((aOrbiterG * 15560519667062222269U), 57U);
            //
            aIngress = aOrbiterH ^ RotL64(aOrbiterC, 3U);
            aIngress = aIngress + (RotL64(aOrbiterB, 41U) ^ aOrbiterK);
            aIngress = aIngress + RotL64(aOrbiterG, 14U);
            aIngress = TwistMix64::DiffuseB((aIngress + aScatter));
            //
            aWandererJ = aWandererJ ^ (((RotL64(aIngress, 50U) + RotL64(aOrbiterK, 53U)) + aOrbiterH) + aNonceWordF);
            aWandererC = aWandererC + (((((RotL64(aCross, 13U) + RotL64(aOrbiterB, 3U)) + aOrbiterC) + RotL64(aCarry, 53U)) + aNonceWordH) + aWandererUpdateSaltB[((aIndex + 6U)) & S_SALT1]);
            aWandererH = aWandererH ^ (((RotL64(aPrevious, 27U) + aOrbiterK) + RotL64(aOrbiterB, 19U)) + aNonceWordK);
            aWandererE = aWandererE + ((((RotL64(aScatter, 35U) + RotL64(aOrbiterC, 27U)) + aOrbiterK) + RotL64(aCarry, 29U)) + aWandererUpdateSaltD[(((31U - aIndex) + 18U)) & S_SALT1]);
            aWandererG = aWandererG ^ ((RotL64(aCross, 3U) + RotL64(aOrbiterH, 40U)) + aOrbiterG);
            //
            aCarry = aCarry + (RotL64(aWandererG, 44U) ^ aWandererH);
            aCarry = aCarry + (RotL64(aWandererJ, 53U) ^ aWandererC);
            aCarry = aCarry + RotL64(aWandererE, 21U);
            aCarry = aCarry + RotL64(aIngress, 13U);
            aCarry = TwistMix64::DiffuseA(aCarry);
            //
            aWorkLaneC[aIndex] = aIngress;
        }
    
        // kdf_a_loop_c loop 4
        // ingress from: aWorkLaneC, aWorkLaneA, aFireLaneD
        // ingress directions: aWorkLaneC forward forced, aWorkLaneA forward forced, aFireLaneD forward/backward random
        // cross from: aWorkLaneB, aOperationLaneC, aOperationLaneD, aOperationLaneA
        // cross directions: aWorkLaneB backward forced, aOperationLaneC backward forced, aOperationLaneD backward forced, aOperationLaneA backward/forward random
        // write to: aWorkLaneD
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aWorkLaneC[((aIndex + 32735U)) & S_BLOCK1], 21U) ^ RotL64(aWorkLaneA[((aIndex + 32016U)) & S_BLOCK1], 54U));
            aIngress ^= RotL64(aFireLaneD[((S_BLOCK1 - aIndex + 24958U)) & S_BLOCK1], 13U);
            aIngress = TwistMix64::DiffuseC(((aIngress ^ aDomainWordIngress) ^ aNonceWordN));
            //
            aCross = (RotL64(aWorkLaneB[((S_BLOCK1 - aIndex + 29697U)) & S_BLOCK1], 26U) ^ RotL64(aOperationLaneC[((S_BLOCK1 - aIndex + 29004U)) & S_BLOCK1], 11U));
            aCross ^= (RotL64(aOperationLaneD[((S_BLOCK1 - aIndex + 28084U)) & S_BLOCK1], 39U) ^ RotL64(aOperationLaneA[((S_BLOCK1 - aIndex + 28185U)) & S_BLOCK1], 47U));
            aCross = TwistMix64::DiffuseB(((aCross ^ aDomainWordCross) ^ aNonceWordC));
            //
            aScatter = (RotL64(aCarry, 34U) + RotL64(aIngress, 5U)) ^ (RotL64(aCross, 57U) ^ RotL64(aPrevious, 19U));
            aScatter = TwistMix64::DiffuseA(((aScatter ^ aDomainWordScatter) ^ aNonceWordJ));
            //
            aOrbiterA = ((aWandererC + RotL64(aPrevious, 53U)) + RotL64(aCarry, 11U)) + 4068921616130916949U;
            aOrbiterD = ((aWandererI + RotL64(aIngress, 40U)) + 12077715273915151726U) + aNonceWordH;
            aOrbiterJ = ((aWandererA + RotL64(aCross, 29U)) + 16047546802670596833U) + aOrbiterAssignSaltD[(((31U - aIndex) + 8U)) & S_SALT1];
            aOrbiterE = (((aWandererH + RotL64(aScatter, 11U)) + RotL64(aCarry, 57U)) + 9690277462716999763U) + aNonceWordE;
            aOrbiterK = ((((aWandererD + RotL64(aIngress, 21U)) + RotL64(aCarry, 37U)) + 14484814700447992628U) + aOrbiterAssignSaltE[(((31U - aIndex) + 3U)) & S_SALT1]) + aNonceWordF;
            //
            aOrbiterA = (aOrbiterA + aOrbiterD) + 17089267243053958210U;
            aOrbiterJ = (aOrbiterJ ^ aOrbiterA) ^ 9138746214446211147U;
            aOrbiterJ = RotL64((aOrbiterJ * 8244950097712975043U), 27U);
            //
            aOrbiterE = ((aOrbiterE + aOrbiterA) + 10181001536979097045U) + aOrbiterUpdateSaltB[((aIndex + 22U)) & S_SALT1];
            aOrbiterD = ((aOrbiterD ^ aOrbiterE) ^ 6657458969093373191U) ^ aNonceWordG;
            aOrbiterD = RotL64((aOrbiterD * 4311019792293202747U), 3U);
            //
            aOrbiterJ = ((aOrbiterJ + aOrbiterK) + 7515983477876590988U) + aOrbiterUpdateSaltC[(((31U - aIndex) + 9U)) & S_SALT1];
            aOrbiterE = (aOrbiterE ^ aOrbiterJ) ^ 3039935555863947600U;
            aOrbiterE = RotL64((aOrbiterE * 12511160550780270119U), 53U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterJ) + 16209389224740851136U;
            aOrbiterK = (((aOrbiterK ^ aOrbiterD) ^ 725253312098083182U) ^ aOrbiterUpdateSaltD[((aIndex + 17U)) & S_SALT1]) ^ aNonceWordB;
            aOrbiterK = RotL64((aOrbiterK * 17535989492095522597U), 43U);
            //
            aOrbiterK = ((aOrbiterK + aOrbiterE) + 13307041115748941383U) + aNonceWordI;
            aOrbiterA = ((aOrbiterA ^ aOrbiterK) ^ 7159572004825238263U) ^ aOrbiterUpdateSaltE[(((31U - aIndex) + 6U)) & S_SALT1];
            aOrbiterA = RotL64((aOrbiterA * 4855009895002398449U), 11U);
            //
            aIngress = RotL64(aOrbiterJ, 3U) ^ aOrbiterA;
            aIngress = aIngress + (RotL64(aOrbiterK, 27U) ^ aOrbiterE);
            aIngress = aIngress + RotL64(aOrbiterD, 14U);
            aIngress = TwistMix64::DiffuseB((aIngress + aScatter));
            //
            aWandererI = aWandererI + ((RotL64(aCross, 47U) + aOrbiterE) + RotL64(aOrbiterK, 57U));
            aWandererH = aWandererH ^ ((RotL64(aPrevious, 13U) + RotL64(aOrbiterD, 21U)) + aOrbiterJ);
            aWandererC = aWandererC + (((((RotL64(aIngress, 4U) + RotL64(aOrbiterD, 3U)) + aOrbiterA) + RotL64(aCarry, 13U)) + aNonceWordD) + aWandererUpdateSaltF[(((31U - aIndex) + 21U)) & S_SALT1]);
            aWandererA = aWandererA ^ ((RotL64(aScatter, 21U) + aOrbiterK) + RotL64(aOrbiterJ, 12U));
            aWandererD = aWandererD + (((((RotL64(aCross, 57U) + RotL64(aOrbiterA, 39U)) + aOrbiterE) + RotL64(aCarry, 29U)) + aNonceWordJ) + aWandererUpdateSaltC[(((31U - aIndex) + 25U)) & S_SALT1]);
            //
            aCarry = aCarry + (RotL64(aWandererD, 29U) ^ aWandererC);
            aCarry = aCarry + (RotL64(aWandererA, 41U) ^ aWandererH);
            aCarry = aCarry + RotL64(aWandererI, 11U);
            aCarry = aCarry + RotL64(aIngress, 3U);
            aCarry = TwistMix64::DiffuseB(aCarry);
            //
            aWorkLaneD[S_BLOCK1 - aIndex] = aIngress;
        }
    }
    // KDF_A_C kdf_a_loop_c (end)
    *pPrevious = aPrevious;
    *pIngress = aIngress;
    *pCarry = aCarry;
    *pWandererA = aWandererA;
    *pWandererB = aWandererB;
    *pWandererC = aWandererC;
    *pWandererD = aWandererD;
    *pWandererE = aWandererE;
    *pWandererF = aWandererF;
    *pWandererG = aWandererG;
    *pWandererH = aWandererH;
    *pWandererI = aWandererI;
    *pWandererJ = aWandererJ;
    *pWandererK = aWandererK;
}

void TwistExpander_Exercea_Arx::KDF_A_D(TwistWorkSpace *pWorkSpace,
                     std::uint64_t pNonce,
                     TwistDomainConstants *pConstants,
                     TwistDomainSaltSet *pDomainSaltSet,
                     std::uint64_t *pPrevious,
                     std::uint64_t *pIngress,
                     std::uint64_t *pCarry,
                     std::uint64_t *pWandererA,
                     std::uint64_t *pWandererB,
                     std::uint64_t *pWandererC,
                     std::uint64_t *pWandererD,
                     std::uint64_t *pWandererE,
                     std::uint64_t *pWandererF,
                     std::uint64_t *pWandererG,
                     std::uint64_t *pWandererH,
                     std::uint64_t *pWandererI,
                     std::uint64_t *pWandererJ,
                     std::uint64_t *pWandererK) {
    [[maybe_unused]] std::uint64_t *aOrbiterAssignSaltA = pDomainSaltSet->mOrbiterAssign.mSaltA;
    [[maybe_unused]] std::uint64_t *aOrbiterAssignSaltB = pDomainSaltSet->mOrbiterAssign.mSaltB;
    [[maybe_unused]] std::uint64_t *aOrbiterAssignSaltC = pDomainSaltSet->mOrbiterAssign.mSaltC;
    [[maybe_unused]] std::uint64_t *aOrbiterAssignSaltD = pDomainSaltSet->mOrbiterAssign.mSaltD;
    [[maybe_unused]] std::uint64_t *aOrbiterAssignSaltE = pDomainSaltSet->mOrbiterAssign.mSaltE;
    [[maybe_unused]] std::uint64_t *aOrbiterAssignSaltF = pDomainSaltSet->mOrbiterAssign.mSaltF;
    [[maybe_unused]] std::uint64_t *aOrbiterUpdateSaltA = pDomainSaltSet->mOrbiterUpdate.mSaltA;
    [[maybe_unused]] std::uint64_t *aOrbiterUpdateSaltB = pDomainSaltSet->mOrbiterUpdate.mSaltB;
    [[maybe_unused]] std::uint64_t *aOrbiterUpdateSaltC = pDomainSaltSet->mOrbiterUpdate.mSaltC;
    [[maybe_unused]] std::uint64_t *aOrbiterUpdateSaltD = pDomainSaltSet->mOrbiterUpdate.mSaltD;
    [[maybe_unused]] std::uint64_t *aOrbiterUpdateSaltE = pDomainSaltSet->mOrbiterUpdate.mSaltE;
    [[maybe_unused]] std::uint64_t *aOrbiterUpdateSaltF = pDomainSaltSet->mOrbiterUpdate.mSaltF;
    [[maybe_unused]] std::uint64_t *aWandererUpdateSaltA = pDomainSaltSet->mWandererUpdate.mSaltA;
    [[maybe_unused]] std::uint64_t *aWandererUpdateSaltB = pDomainSaltSet->mWandererUpdate.mSaltB;
    [[maybe_unused]] std::uint64_t *aWandererUpdateSaltC = pDomainSaltSet->mWandererUpdate.mSaltC;
    [[maybe_unused]] std::uint64_t *aWandererUpdateSaltD = pDomainSaltSet->mWandererUpdate.mSaltD;
    [[maybe_unused]] std::uint64_t *aWandererUpdateSaltE = pDomainSaltSet->mWandererUpdate.mSaltE;
    [[maybe_unused]] std::uint64_t *aWandererUpdateSaltF = pDomainSaltSet->mWandererUpdate.mSaltF;
    [[maybe_unused]] std::uint8_t *aExpandLaneA = pWorkSpace->mExpansionLaneA;
    [[maybe_unused]] std::uint8_t *aExpandLaneB = pWorkSpace->mExpansionLaneB;
    [[maybe_unused]] std::uint8_t *aExpandLaneC = pWorkSpace->mExpansionLaneC;
    [[maybe_unused]] std::uint8_t *aExpandLaneD = pWorkSpace->mExpansionLaneD;
    [[maybe_unused]] std::uint8_t *aWorkLaneA = pWorkSpace->mWorkLaneA;
    [[maybe_unused]] std::uint8_t *aWorkLaneB = pWorkSpace->mWorkLaneB;
    [[maybe_unused]] std::uint8_t *aWorkLaneC = pWorkSpace->mWorkLaneC;
    [[maybe_unused]] std::uint8_t *aWorkLaneD = pWorkSpace->mWorkLaneD;
    [[maybe_unused]] std::uint8_t *aOperationLaneA = pWorkSpace->mOperationLaneA;
    [[maybe_unused]] std::uint8_t *aOperationLaneB = pWorkSpace->mOperationLaneB;
    [[maybe_unused]] std::uint8_t *aOperationLaneC = pWorkSpace->mOperationLaneC;
    [[maybe_unused]] std::uint8_t *aOperationLaneD = pWorkSpace->mOperationLaneD;
    [[maybe_unused]] std::uint8_t *aFireLaneA = pWorkSpace->mFireLaneA;
    [[maybe_unused]] std::uint8_t *aFireLaneB = pWorkSpace->mFireLaneB;
    [[maybe_unused]] std::uint8_t *aFireLaneC = pWorkSpace->mFireLaneC;
    [[maybe_unused]] std::uint8_t *aFireLaneD = pWorkSpace->mFireLaneD;
    std::uint64_t aCross = 0; std::uint64_t aScatter = 0;

    std::uint64_t aOrbiterA = 0; std::uint64_t aOrbiterB = 0; std::uint64_t aOrbiterC = 0; std::uint64_t aOrbiterD = 0;
    std::uint64_t aOrbiterE = 0; std::uint64_t aOrbiterF = 0; std::uint64_t aOrbiterG = 0; std::uint64_t aOrbiterH = 0;
    std::uint64_t aOrbiterI = 0; std::uint64_t aOrbiterJ = 0; std::uint64_t aOrbiterK = 0;

    // [kdf-a arx]
    std::uint64_t aNonceWordA = TwistMix64::DiffuseC(pNonce * 0x8D0C962B97F64BC9ULL + 0x8018469395C18D0BULL);
    std::uint64_t aNonceWordB = TwistMix64::DiffuseB(pNonce * 0x836C674166051D7DULL + 0x8461082B63662362ULL);
    std::uint64_t aNonceWordC = TwistMix64::DiffuseA(pNonce * 0xE99C15AF10F81B2FULL + 0xF5010EE517F9B22EULL);
    std::uint64_t aNonceWordD = TwistMix64::DiffuseA(pNonce * 0xDBA9D71B3AF75ACFULL + 0xC88FC179DE21785AULL);
    std::uint64_t aNonceWordE = TwistMix64::DiffuseB(pNonce * 0xA767B9D0F96CFAD9ULL + 0xC9BE9E3BEF251374ULL);
    std::uint64_t aNonceWordF = TwistMix64::DiffuseA(pNonce * 0xFD32E2CF39A9E0CBULL + 0xD70BB47C3FF09B17ULL);
    std::uint64_t aNonceWordG = TwistMix64::DiffuseB(pNonce * 0x85438595DE00DBD9ULL + 0x8295EF02930C8335ULL);
    std::uint64_t aNonceWordH = TwistMix64::DiffuseB(pNonce * 0xF1907A9E92A49A41ULL + 0xAECC54CDA89FE8C2ULL);
    std::uint64_t aNonceWordI = TwistMix64::DiffuseA(pNonce * 0xCAA3917AE72BB86DULL + 0x98CC28CDE4F9A8EBULL);
    std::uint64_t aNonceWordJ = TwistMix64::DiffuseA(pNonce * 0xB6BF286DFAE947ABULL + 0xD26BD01BB45161CAULL);
    std::uint64_t aNonceWordK = TwistMix64::DiffuseC(pNonce * 0x81BB4E6169ED591DULL + 0x85311D535051CD9CULL);
    std::uint64_t aNonceWordL = TwistMix64::DiffuseA(pNonce * 0xEB58847B6C890FD5ULL + 0xFDC2179CEE5C777BULL);
    std::uint64_t aNonceWordM = TwistMix64::DiffuseC(pNonce * 0xAE51AE45902BD96DULL + 0xC0AF12E2DE55DF71ULL);
    std::uint64_t aNonceWordN = TwistMix64::DiffuseA(pNonce * 0xAB55FAC3AE442611ULL + 0xF451246C780E4860ULL);
    std::uint64_t aNonceWordO = TwistMix64::DiffuseC(pNonce * 0xE80625FA53EF9555ULL + 0x869A48790D95D6DEULL);
    std::uint64_t aNonceWordP = TwistMix64::DiffuseB(pNonce * 0xA238394D0AFEB771ULL + 0xFA9E9EA797B31B3CULL);
    std::uint64_t aDomainWordIngress = pConstants->mIngress;
    std::uint64_t aDomainWordScatter = pConstants->mScatter;
    std::uint64_t aDomainWordCross = pConstants->mCross;
    [[maybe_unused]] std::uint8_t *mSource = pWorkSpace->mSource;
    std::uint64_t aPrevious = *pPrevious;
    std::uint64_t aIngress = *pIngress;
    std::uint64_t aCarry = *pCarry;
    std::uint64_t aWandererA = *pWandererA;
    std::uint64_t aWandererB = *pWandererB;
    std::uint64_t aWandererC = *pWandererC;
    std::uint64_t aWandererD = *pWandererD;
    std::uint64_t aWandererE = *pWandererE;
    std::uint64_t aWandererF = *pWandererF;
    std::uint64_t aWandererG = *pWandererG;
    std::uint64_t aWandererH = *pWandererH;
    std::uint64_t aWandererI = *pWandererI;
    std::uint64_t aWandererJ = *pWandererJ;
    std::uint64_t aWandererK = *pWandererK;
    // KDF_A_D kdf_a_loop_d (start)
    {
        // KDF_A_D kdf_a_loop_d lane group
        // read from: aExpandLaneA, aExpandLaneB, aFireLaneC, aExpandLaneC, aExpandLaneD, aOperationLaneA, aWorkLaneA, aOperationLaneB, aFireLaneB, aWorkLaneB, aFireLaneA, aFireLaneD, aWorkLaneC, aOperationLaneD, aOperationLaneC
        // write to: aWorkLaneA, aWorkLaneB, aWorkLaneC, aWorkLaneD
    
        // kdf_a_loop_d loop 1
        // ingress from: aExpandLaneA, aExpandLaneB, aFireLaneC
        // ingress directions: aExpandLaneA forward forced, aExpandLaneB forward forced, aFireLaneC forward/backward random
        // cross from: aExpandLaneC, aExpandLaneD, aOperationLaneA
        // cross directions: aExpandLaneC backward forced, aExpandLaneD backward forced, aOperationLaneA backward/forward random
        // write to: aWorkLaneA
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aExpandLaneA[((aIndex + 5609U)) & S_BLOCK1], 56U) ^ RotL64(aExpandLaneB[((aIndex + 2713U)) & S_BLOCK1], 13U));
            aIngress ^= RotL64(aFireLaneC[((S_BLOCK1 - aIndex + 1451U)) & S_BLOCK1], 39U);
            aIngress = TwistMix64::DiffuseA(((aIngress ^ aDomainWordIngress) ^ aNonceWordD));
            //
            aCross = (RotL64(aExpandLaneC[((S_BLOCK1 - aIndex + 4614U)) & S_BLOCK1], 11U) ^ RotL64(aExpandLaneD[((S_BLOCK1 - aIndex + 3538U)) & S_BLOCK1], 47U));
            aCross ^= RotL64(aOperationLaneA[((S_BLOCK1 - aIndex + 5765U)) & S_BLOCK1], 39U);
            aCross = TwistMix64::DiffuseB(((aCross ^ aDomainWordCross) ^ aNonceWordG));
            //
            aScatter = (RotL64(aCross, 11U) ^ RotL64(aIngress, 57U)) + (RotL64(aPrevious, 43U) ^ RotL64(aCarry, 24U));
            aScatter = TwistMix64::DiffuseB(((aScatter ^ aDomainWordScatter) ^ aNonceWordM));
            //
            aOrbiterG = (((aWandererK + RotL64(aIngress, 29U)) + RotL64(aCarry, 5U)) + 10812151398716051703U) + aOrbiterAssignSaltE[((aIndex + 13U)) & S_SALT1];
            aOrbiterH = ((aWandererI + RotL64(aScatter, 57U)) + RotL64(aCarry, 53U)) + 18202551453336003710U;
            aOrbiterA = ((aWandererG + RotL64(aPrevious, 37U)) + 9434410809101973752U) + aNonceWordN;
            aOrbiterE = ((aWandererC + RotL64(aCross, 43U)) + 12955829998028534045U) + aNonceWordH;
            aOrbiterD = (aWandererD + RotL64(aScatter, 50U)) + 12271740641929640181U;
            aOrbiterI = (((aWandererF + RotL64(aPrevious, 3U)) + RotL64(aCarry, 27U)) + 14009351527014534752U) + aOrbiterAssignSaltB[((aIndex + 12U)) & S_SALT1];
            aOrbiterK = (aWandererB + RotL64(aCross, 21U)) + 4316296955679133450U;
            //
            aOrbiterG = (((aOrbiterG + aOrbiterH) + 16473324966997442872U) + aOrbiterUpdateSaltB[(((31U - aIndex) + 27U)) & S_SALT1]) + aNonceWordI;
            aOrbiterA = (aOrbiterA ^ aOrbiterG) ^ 15735123324965019802U;
            aOrbiterA = RotL64((aOrbiterA * 5624078184997601019U), 3U);
            //
            aOrbiterE = ((aOrbiterE + aOrbiterD) + 17656375090484080236U) + aNonceWordO;
            aOrbiterG = (aOrbiterG ^ aOrbiterE) ^ 16066325053456055298U;
            aOrbiterG = RotL64((aOrbiterG * 17912970706985130327U), 41U);
            //
            aOrbiterI = (aOrbiterI + aOrbiterA) + 12908968778503516903U;
            aOrbiterE = ((aOrbiterE ^ aOrbiterI) ^ 12761433987676836197U) ^ aNonceWordC;
            aOrbiterE = RotL64((aOrbiterE * 1023329467480907925U), 51U);
            //
            aOrbiterA = (((aOrbiterA + aOrbiterK) + 12737513138040664509U) + aOrbiterUpdateSaltA[(((31U - aIndex) + 14U)) & S_SALT1]) + aNonceWordJ;
            aOrbiterD = (aOrbiterD ^ aOrbiterA) ^ 14535795767570998392U;
            aOrbiterD = RotL64((aOrbiterD * 15560519667062222269U), 11U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterI) + 14370908061811284364U;
            aOrbiterH = (aOrbiterH ^ aOrbiterD) ^ 7001358781208669795U;
            aOrbiterH = RotL64((aOrbiterH * 11641248025734015835U), 57U);
            //
            aOrbiterH = (aOrbiterH + aOrbiterE) + 7298578161120090849U;
            aOrbiterK = (aOrbiterK ^ aOrbiterH) ^ 10498302152357484629U;
            aOrbiterK = RotL64((aOrbiterK * 13144110412179037175U), 27U);
            //
            aOrbiterK = ((aOrbiterK + aOrbiterG) + 11447343228638006767U) + aOrbiterUpdateSaltF[((aIndex + 11U)) & S_SALT1];
            aOrbiterI = ((aOrbiterI ^ aOrbiterK) ^ 18284143620422655675U) ^ aOrbiterUpdateSaltE[(((31U - aIndex) + 21U)) & S_SALT1];
            aOrbiterI = RotL64((aOrbiterI * 572862190073605651U), 19U);
            //
            aIngress = aOrbiterI ^ RotL64(aOrbiterK, 13U);
            aIngress = aIngress + (aOrbiterH ^ RotL64(aOrbiterA, 5U));
            aIngress = aIngress + (RotL64(aOrbiterG, 35U) ^ aOrbiterE);
            aIngress = aIngress + RotL64(aOrbiterD, 58U);
            aIngress = TwistMix64::DiffuseA((aIngress + aScatter));
            //
            aWandererD = aWandererD ^ ((RotL64(aCross, 3U) + RotL64(aOrbiterA, 3U)) + aOrbiterD);
            aWandererG = aWandererG + ((((RotL64(aPrevious, 51U) + aOrbiterG) + RotL64(aOrbiterK, 54U)) + RotL64(aCarry, 41U)) + aNonceWordL);
            aWandererC = aWandererC ^ (((RotL64(aIngress, 58U) + RotL64(aOrbiterH, 39U)) + aOrbiterD) + aWandererUpdateSaltE[(((31U - aIndex) + 7U)) & S_SALT1]);
            aWandererK = aWandererK + ((((RotL64(aScatter, 13U) + RotL64(aOrbiterA, 13U)) + aOrbiterI) + RotL64(aCarry, 27U)) + aWandererUpdateSaltD[(((31U - aIndex) + 24U)) & S_SALT1]);
            aWandererF = aWandererF ^ ((RotL64(aCross, 35U) + aOrbiterE) + RotL64(aOrbiterD, 23U));
            aWandererB = aWandererB + (((RotL64(aScatter, 19U) + aOrbiterA) + RotL64(aOrbiterK, 47U)) + aNonceWordB);
            aWandererI = aWandererI ^ (((RotL64(aPrevious, 41U) + aOrbiterE) + RotL64(aOrbiterG, 29U)) + aNonceWordE);
            //
            aCarry = aCarry + (aWandererD ^ RotL64(aWandererI, 5U));
            aCarry = aCarry + (RotL64(aWandererK, 43U) ^ aWandererG);
            aCarry = aCarry + (RotL64(aWandererB, 56U) ^ aWandererC);
            aCarry = aCarry + RotL64(aWandererF, 13U);
            aCarry = aCarry + RotL64(aIngress, 35U);
            aCarry = TwistMix64::DiffuseA(aCarry);
            //
            aWorkLaneA[aIndex] = aIngress;
        }
    
        // kdf_a_loop_d loop 2
        // ingress from: aWorkLaneA, aExpandLaneC, aOperationLaneB
        // ingress directions: aWorkLaneA forward forced, aExpandLaneC forward forced, aOperationLaneB forward/backward random
        // cross from: aExpandLaneA, aExpandLaneD, aFireLaneB
        // cross directions: aExpandLaneA backward forced, aExpandLaneD backward forced, aFireLaneB backward/forward random
        // write to: aWorkLaneB
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aWorkLaneA[((aIndex + 9591U)) & S_BLOCK1], 40U) ^ RotL64(aExpandLaneC[((aIndex + 11258U)) & S_BLOCK1], 3U));
            aIngress ^= RotL64(aOperationLaneB[((aIndex + 11364U)) & S_BLOCK1], 19U);
            aIngress = TwistMix64::DiffuseA(((aIngress ^ aDomainWordIngress) ^ aNonceWordC));
            //
            aCross = (RotL64(aExpandLaneA[((S_BLOCK1 - aIndex + 16336U)) & S_BLOCK1], 37U) ^ RotL64(aExpandLaneD[((S_BLOCK1 - aIndex + 9092U)) & S_BLOCK1], 57U));
            aCross ^= RotL64(aFireLaneB[((S_BLOCK1 - aIndex + 11150U)) & S_BLOCK1], 47U);
            aCross = TwistMix64::DiffuseB(((aCross ^ aDomainWordCross) ^ aNonceWordJ));
            //
            aScatter = (RotL64(aCarry, 41U) ^ RotL64(aPrevious, 27U)) ^ (RotL64(aCross, 53U) + RotL64(aIngress, 14U));
            aScatter = TwistMix64::DiffuseB(((aScatter ^ aDomainWordScatter) ^ aNonceWordP));
            //
            aOrbiterB = ((aWandererG + RotL64(aIngress, 10U)) + RotL64(aCarry, 35U)) + 4751694786009671052U;
            aOrbiterF = (((aWandererF + RotL64(aScatter, 3U)) + RotL64(aCarry, 53U)) + 16362725160370844224U) + aNonceWordH;
            aOrbiterC = (((aWandererI + RotL64(aCross, 57U)) + RotL64(aCarry, 3U)) + 6360885380915941057U) + aNonceWordG;
            aOrbiterE = (((aWandererJ + RotL64(aPrevious, 29U)) + 5154536007972297036U) + aOrbiterAssignSaltC[(((31U - aIndex) + 12U)) & S_SALT1]) + aNonceWordP;
            aOrbiterK = ((aWandererH + RotL64(aIngress, 23U)) + 9362540581874808253U) + aOrbiterAssignSaltD[(((31U - aIndex) + 11U)) & S_SALT1];
            aOrbiterD = (aWandererD + RotL64(aScatter, 35U)) + 13902493871525612934U;
            aOrbiterJ = (aWandererA + RotL64(aPrevious, 43U)) + 10208452885367546542U;
            //
            aOrbiterB = (aOrbiterB + aOrbiterF) + 3117030377279160998U;
            aOrbiterC = ((aOrbiterC ^ aOrbiterB) ^ 17286247690414027870U) ^ aOrbiterUpdateSaltA[((aIndex + 16U)) & S_SALT1];
            aOrbiterC = RotL64((aOrbiterC * 4896931759653832095U), 5U);
            //
            aOrbiterC = (aOrbiterC + aOrbiterE) + 3930314320040949141U;
            aOrbiterK = ((aOrbiterK ^ aOrbiterC) ^ 7289525252391668404U) ^ aNonceWordB;
            aOrbiterK = RotL64((aOrbiterK * 15452162299105112187U), 57U);
            //
            aOrbiterD = ((aOrbiterD + aOrbiterK) + 3434167955466809185U) + aNonceWordK;
            aOrbiterF = (aOrbiterF ^ aOrbiterD) ^ 17852573095128575663U;
            aOrbiterF = RotL64((aOrbiterF * 1485660158767033425U), 21U);
            //
            aOrbiterF = ((aOrbiterF + aOrbiterJ) + 6137259687928853253U) + aOrbiterUpdateSaltC[(((31U - aIndex) + 27U)) & S_SALT1];
            aOrbiterE = (aOrbiterE ^ aOrbiterF) ^ 13992510605237574698U;
            aOrbiterE = RotL64((aOrbiterE * 15346263295995333395U), 29U);
            //
            aOrbiterJ = (aOrbiterJ + aOrbiterC) + 6470556523400123474U;
            aOrbiterD = (aOrbiterD ^ aOrbiterJ) ^ 4333255670390099293U;
            aOrbiterD = RotL64((aOrbiterD * 11089933812030082647U), 37U);
            //
            aOrbiterE = (aOrbiterE + aOrbiterD) + 7700424876430257995U;
            aOrbiterB = ((aOrbiterB ^ aOrbiterE) ^ 16920736951239453071U) ^ aOrbiterUpdateSaltD[((aIndex + 25U)) & S_SALT1];
            aOrbiterB = RotL64((aOrbiterB * 8920407493132380497U), 13U);
            //
            aOrbiterK = (aOrbiterK + aOrbiterB) + 1635071690430295730U;
            aOrbiterJ = (((aOrbiterJ ^ aOrbiterK) ^ 9966700845966398620U) ^ aOrbiterUpdateSaltE[((aIndex + 28U)) & S_SALT1]) ^ aNonceWordE;
            aOrbiterJ = RotL64((aOrbiterJ * 17210048121896546867U), 43U);
            //
            aIngress = RotL64(aOrbiterC, 51U) ^ aOrbiterB;
            aIngress = aIngress + (aOrbiterJ ^ RotL64(aOrbiterF, 3U));
            aIngress = aIngress + (aOrbiterD ^ RotL64(aOrbiterK, 13U));
            aIngress = aIngress + RotL64(aOrbiterE, 39U);
            aIngress = TwistMix64::DiffuseA((aIngress + aScatter));
            //
            aWandererH = aWandererH ^ ((((RotL64(aCross, 34U) + aOrbiterK) + RotL64(aOrbiterD, 37U)) + aNonceWordM) + aWandererUpdateSaltA[(((31U - aIndex) + 6U)) & S_SALT1]);
            aWandererD = aWandererD + ((((RotL64(aIngress, 11U) + aOrbiterD) + RotL64(aOrbiterF, 11U)) + aNonceWordD) + aWandererUpdateSaltF[((aIndex + 29U)) & S_SALT1]);
            aWandererI = aWandererI ^ (((RotL64(aScatter, 47U) + aOrbiterC) + RotL64(aOrbiterK, 51U)) + aNonceWordO);
            aWandererG = aWandererG + (((RotL64(aPrevious, 5U) + aOrbiterJ) + RotL64(aOrbiterF, 19U)) + RotL64(aCarry, 57U));
            aWandererF = aWandererF ^ ((RotL64(aIngress, 53U) + aOrbiterB) + RotL64(aOrbiterC, 60U));
            aWandererJ = aWandererJ + (((RotL64(aScatter, 27U) + aOrbiterD) + RotL64(aOrbiterJ, 5U)) + RotL64(aCarry, 21U));
            aWandererA = aWandererA ^ ((RotL64(aPrevious, 41U) + RotL64(aOrbiterE, 27U)) + aOrbiterF);
            //
            aCarry = aCarry + (aWandererH ^ RotL64(aWandererG, 28U));
            aCarry = aCarry + (RotL64(aWandererA, 43U) ^ aWandererJ);
            aCarry = aCarry + (RotL64(aWandererD, 35U) ^ aWandererF);
            aCarry = aCarry + RotL64(aWandererI, 47U);
            aCarry = aCarry + RotL64(aIngress, 4U);
            aCarry = TwistMix64::DiffuseA(aCarry);
            //
            aWorkLaneB[S_BLOCK1 - aIndex] = aIngress;
        }
    
        // kdf_a_loop_d loop 3
        // ingress from: aWorkLaneB, aExpandLaneD, aFireLaneA
        // ingress directions: aWorkLaneB forward forced, aExpandLaneD forward forced, aFireLaneA forward/backward random
        // cross from: aWorkLaneA, aExpandLaneB, aFireLaneD
        // cross directions: aWorkLaneA backward forced, aExpandLaneB backward forced, aFireLaneD backward/forward random
        // write to: aWorkLaneC
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aWorkLaneB[((aIndex + 17824U)) & S_BLOCK1], 27U) ^ RotL64(aExpandLaneD[((aIndex + 21330U)) & S_BLOCK1], 13U));
            aIngress ^= RotL64(aFireLaneA[((S_BLOCK1 - aIndex + 18117U)) & S_BLOCK1], 3U);
            aIngress = TwistMix64::DiffuseA(((aIngress ^ aDomainWordIngress) ^ aNonceWordO));
            //
            aCross = (RotL64(aWorkLaneA[((S_BLOCK1 - aIndex + 21683U)) & S_BLOCK1], 46U) ^ RotL64(aExpandLaneB[((S_BLOCK1 - aIndex + 16521U)) & S_BLOCK1], 29U));
            aCross ^= RotL64(aFireLaneD[((aIndex + 22199U)) & S_BLOCK1], 37U);
            aCross = TwistMix64::DiffuseB(((aCross ^ aDomainWordCross) ^ aNonceWordP));
            //
            aScatter = (RotL64(aCross, 44U) ^ RotL64(aPrevious, 13U)) + (RotL64(aCarry, 57U) ^ RotL64(aIngress, 27U));
            aScatter = TwistMix64::DiffuseB(((aScatter ^ aDomainWordScatter) ^ aNonceWordL));
            //
            aOrbiterF = ((aWandererI + RotL64(aScatter, 41U)) + 9133751643283278896U) + aNonceWordN;
            aOrbiterI = (((aWandererH + RotL64(aCross, 29U)) + RotL64(aCarry, 5U)) + 8971581804375380408U) + aOrbiterAssignSaltA[((aIndex + 15U)) & S_SALT1];
            aOrbiterB = (((aWandererJ + RotL64(aPrevious, 53U)) + 12559650383714566592U) + aOrbiterAssignSaltF[((aIndex + 19U)) & S_SALT1]) + aNonceWordK;
            aOrbiterK = (aWandererD + RotL64(aIngress, 11U)) + 15753206088872859163U;
            aOrbiterG = (((aWandererC + RotL64(aPrevious, 35U)) + RotL64(aCarry, 29U)) + 7640756270450762350U) + aNonceWordD;
            aOrbiterC = ((aWandererG + RotL64(aScatter, 47U)) + RotL64(aCarry, 53U)) + 7340073357551376125U;
            aOrbiterE = ((aWandererE + RotL64(aIngress, 22U)) + 5270256573644196046U) + aNonceWordC;
            //
            aOrbiterF = (aOrbiterF + aOrbiterI) + 3567367996479995928U;
            aOrbiterB = (aOrbiterB ^ aOrbiterF) ^ 11939634537492733738U;
            aOrbiterB = RotL64((aOrbiterB * 5640541900117183639U), 19U);
            //
            aOrbiterK = (aOrbiterK + aOrbiterG) + 7051817732424527120U;
            aOrbiterC = ((aOrbiterC ^ aOrbiterK) ^ 1730487669951837941U) ^ aOrbiterUpdateSaltE[(((31U - aIndex) + 24U)) & S_SALT1];
            aOrbiterC = RotL64((aOrbiterC * 15191634337956285841U), 41U);
            //
            aOrbiterG = ((aOrbiterG + aOrbiterC) + 18009252467909454817U) + aOrbiterUpdateSaltD[((aIndex + 9U)) & S_SALT1];
            aOrbiterF = (aOrbiterF ^ aOrbiterG) ^ 2361024272031696442U;
            aOrbiterF = RotL64((aOrbiterF * 15215151562500226027U), 51U);
            //
            aOrbiterB = (aOrbiterB + aOrbiterE) + 15902755877642960397U;
            aOrbiterK = (aOrbiterK ^ aOrbiterB) ^ 12243517544704116184U;
            aOrbiterK = RotL64((aOrbiterK * 2576071074148141447U), 27U);
            //
            aOrbiterE = ((aOrbiterE + aOrbiterK) + 16846181962302186187U) + aNonceWordG;
            aOrbiterG = ((aOrbiterG ^ aOrbiterE) ^ 636121425116506681U) ^ aOrbiterUpdateSaltF[(((31U - aIndex) + 11U)) & S_SALT1];
            aOrbiterG = RotL64((aOrbiterG * 17075030673338779993U), 35U);
            //
            aOrbiterI = (aOrbiterI + aOrbiterB) + 6887385655828217318U;
            aOrbiterE = (aOrbiterE ^ aOrbiterI) ^ 3705834550934775862U;
            aOrbiterE = RotL64((aOrbiterE * 11275428284929594435U), 3U);
            //
            aOrbiterC = ((aOrbiterC + aOrbiterF) + 11165142437077969438U) + aOrbiterUpdateSaltC[((aIndex + 29U)) & S_SALT1];
            aOrbiterI = ((aOrbiterI ^ aOrbiterC) ^ 6426659930331618269U) ^ aNonceWordB;
            aOrbiterI = RotL64((aOrbiterI * 17170640810530893705U), 11U);
            //
            aIngress = aOrbiterF ^ RotL64(aOrbiterC, 29U);
            aIngress = aIngress + (RotL64(aOrbiterE, 23U) ^ aOrbiterI);
            aIngress = aIngress + (RotL64(aOrbiterG, 52U) ^ aOrbiterK);
            aIngress = aIngress + RotL64(aOrbiterB, 37U);
            aIngress = TwistMix64::DiffuseC((aIngress + aScatter));
            //
            aWandererH = aWandererH ^ (((RotL64(aScatter, 19U) + aOrbiterG) + RotL64(aOrbiterF, 3U)) + aWandererUpdateSaltC[(((31U - aIndex) + 8U)) & S_SALT1]);
            aWandererG = aWandererG + (((RotL64(aPrevious, 13U) + RotL64(aOrbiterE, 43U)) + aOrbiterB) + RotL64(aCarry, 19U));
            aWandererJ = aWandererJ ^ (((RotL64(aIngress, 57U) + RotL64(aOrbiterC, 11U)) + aOrbiterI) + aNonceWordE);
            aWandererD = aWandererD + ((((RotL64(aCross, 41U) + RotL64(aOrbiterE, 51U)) + aOrbiterK) + RotL64(aCarry, 39U)) + aNonceWordI);
            aWandererC = aWandererC ^ ((RotL64(aPrevious, 27U) + RotL64(aOrbiterF, 21U)) + aOrbiterB);
            aWandererI = aWandererI + ((((RotL64(aCross, 47U) + aOrbiterC) + RotL64(aOrbiterG, 29U)) + aNonceWordH) + aWandererUpdateSaltB[((aIndex + 20U)) & S_SALT1]);
            aWandererE = aWandererE ^ (((RotL64(aIngress, 34U) + RotL64(aOrbiterG, 58U)) + aOrbiterK) + aNonceWordA);
            //
            aCarry = aCarry + (aWandererG ^ RotL64(aWandererJ, 57U));
            aCarry = aCarry + (aWandererI ^ RotL64(aWandererE, 18U));
            aCarry = aCarry + (aWandererD ^ RotL64(aWandererC, 47U));
            aCarry = aCarry + RotL64(aWandererH, 35U);
            aCarry = aCarry + RotL64(aIngress, 13U);
            aCarry = TwistMix64::DiffuseB(aCarry);
            //
            aWorkLaneC[aIndex] = aIngress;
        }
    
        // kdf_a_loop_d loop 4
        // ingress from: aWorkLaneC, aWorkLaneA, aOperationLaneD
        // ingress directions: aWorkLaneC forward forced, aWorkLaneA forward forced, aOperationLaneD forward/backward random
        // cross from: aWorkLaneB, aExpandLaneC, aOperationLaneC
        // cross directions: aWorkLaneB backward forced, aExpandLaneC backward forced, aOperationLaneC backward/forward random
        // write to: aWorkLaneD
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aWorkLaneC[((aIndex + 31836U)) & S_BLOCK1], 29U) ^ RotL64(aWorkLaneA[((aIndex + 27143U)) & S_BLOCK1], 52U));
            aIngress ^= RotL64(aOperationLaneD[((S_BLOCK1 - aIndex + 27173U)) & S_BLOCK1], 43U);
            aIngress = TwistMix64::DiffuseB(((aIngress ^ aDomainWordIngress) ^ aNonceWordI));
            //
            aCross = (RotL64(aWorkLaneB[((S_BLOCK1 - aIndex + 30611U)) & S_BLOCK1], 5U) ^ RotL64(aExpandLaneC[((S_BLOCK1 - aIndex + 29914U)) & S_BLOCK1], 60U));
            aCross ^= RotL64(aOperationLaneC[((aIndex + 30034U)) & S_BLOCK1], 21U);
            aCross = TwistMix64::DiffuseA(((aCross ^ aDomainWordCross) ^ aNonceWordJ));
            //
            aScatter = (RotL64(aCross, 51U) ^ RotL64(aIngress, 26U)) + (RotL64(aPrevious, 39U) ^ RotL64(aCarry, 11U));
            aScatter = TwistMix64::DiffuseB(((aScatter ^ aDomainWordScatter) ^ aNonceWordJ));
            //
            aOrbiterK = ((aWandererD + RotL64(aIngress, 29U)) + 4848316479321533394U) + aOrbiterAssignSaltB[(((31U - aIndex) + 27U)) & S_SALT1];
            aOrbiterB = ((aWandererC + RotL64(aScatter, 3U)) + RotL64(aCarry, 43U)) + 6919360256662636195U;
            aOrbiterD = ((aWandererJ + RotL64(aPrevious, 13U)) + 9897013582181108544U) + aNonceWordB;
            aOrbiterI = (((aWandererB + RotL64(aCross, 21U)) + RotL64(aCarry, 3U)) + 7319353809896158678U) + aOrbiterAssignSaltE[(((31U - aIndex) + 15U)) & S_SALT1];
            aOrbiterC = ((aWandererE + RotL64(aPrevious, 43U)) + RotL64(aCarry, 29U)) + 2848175435514849859U;
            aOrbiterG = ((aWandererI + RotL64(aCross, 50U)) + 6967780718720437934U) + aNonceWordO;
            aOrbiterA = (aWandererA + RotL64(aScatter, 35U)) + 10143884766603388136U;
            //
            aOrbiterK = (aOrbiterK + aOrbiterB) + 8675965006150972051U;
            aOrbiterD = ((aOrbiterD ^ aOrbiterK) ^ 16350117755560994281U) ^ aOrbiterUpdateSaltF[((aIndex + 13U)) & S_SALT1];
            aOrbiterD = RotL64((aOrbiterD * 15072308930382994425U), 37U);
            //
            aOrbiterI = ((aOrbiterI + aOrbiterC) + 17976597517118423760U) + aOrbiterUpdateSaltE[(((31U - aIndex) + 19U)) & S_SALT1];
            aOrbiterK = (aOrbiterK ^ aOrbiterI) ^ 1399631141355370237U;
            aOrbiterK = RotL64((aOrbiterK * 16537788276543236833U), 3U);
            //
            aOrbiterG = ((aOrbiterG + aOrbiterA) + 3590613762034716792U) + aNonceWordF;
            aOrbiterI = (aOrbiterI ^ aOrbiterG) ^ 5134624314245932157U;
            aOrbiterI = RotL64((aOrbiterI * 13077589037975283371U), 13U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterG) + 10082236952942943654U;
            aOrbiterA = (aOrbiterA ^ aOrbiterD) ^ 4015535035905433450U;
            aOrbiterA = RotL64((aOrbiterA * 4961808568701908559U), 51U);
            //
            aOrbiterB = (aOrbiterB + aOrbiterD) + 611474103801573800U;
            aOrbiterG = (aOrbiterG ^ aOrbiterB) ^ 5786708483794098001U;
            aOrbiterG = RotL64((aOrbiterG * 7694007039340089267U), 43U);
            //
            aOrbiterA = (((aOrbiterA + aOrbiterI) + 5201943497363274455U) + aOrbiterUpdateSaltC[((aIndex + 29U)) & S_SALT1]) + aNonceWordA;
            aOrbiterC = ((aOrbiterC ^ aOrbiterA) ^ 9282160506938328489U) ^ aOrbiterUpdateSaltB[(((31U - aIndex) + 24U)) & S_SALT1];
            aOrbiterC = RotL64((aOrbiterC * 5368182164239021367U), 29U);
            //
            aOrbiterC = (aOrbiterC + aOrbiterK) + 4932320527498940158U;
            aOrbiterB = (aOrbiterB ^ aOrbiterC) ^ 11576526341731392916U;
            aOrbiterB = RotL64((aOrbiterB * 1712051774729439363U), 21U);
            //
            aIngress = aOrbiterG ^ RotL64(aOrbiterB, 29U);
            aIngress = aIngress + (aOrbiterD ^ RotL64(aOrbiterC, 3U));
            aIngress = aIngress + (RotL64(aOrbiterK, 60U) ^ aOrbiterI);
            aIngress = aIngress + RotL64(aOrbiterA, 21U);
            aIngress = TwistMix64::DiffuseC((aIngress + aScatter));
            //
            aWandererA = aWandererA ^ (((RotL64(aIngress, 53U) + RotL64(aOrbiterG, 43U)) + aOrbiterD) + aNonceWordE);
            aWandererB = aWandererB + ((((RotL64(aPrevious, 29U) + RotL64(aOrbiterK, 60U)) + aOrbiterD) + RotL64(aCarry, 53U)) + aNonceWordL);
            aWandererE = aWandererE ^ (((RotL64(aCross, 47U) + aOrbiterC) + RotL64(aOrbiterB, 35U)) + aWandererUpdateSaltD[(((31U - aIndex) + 28U)) & S_SALT1]);
            aWandererD = aWandererD + ((RotL64(aScatter, 19U) + aOrbiterK) + RotL64(aOrbiterI, 27U));
            aWandererJ = aWandererJ ^ ((((RotL64(aPrevious, 5U) + RotL64(aOrbiterG, 51U)) + aOrbiterA) + aNonceWordG) + aWandererUpdateSaltE[(((31U - aIndex) + 23U)) & S_SALT1]);
            aWandererC = aWandererC + (((RotL64(aCross, 36U) + aOrbiterI) + RotL64(aOrbiterA, 13U)) + RotL64(aCarry, 23U));
            aWandererI = aWandererI ^ ((RotL64(aScatter, 11U) + aOrbiterB) + RotL64(aOrbiterK, 21U));
            //
            aCarry = aCarry + (aWandererC ^ RotL64(aWandererD, 29U));
            aCarry = aCarry + (aWandererE ^ RotL64(aWandererB, 48U));
            aCarry = aCarry + (aWandererJ ^ RotL64(aWandererA, 35U));
            aCarry = aCarry + RotL64(aWandererI, 23U);
            aCarry = aCarry + RotL64(aIngress, 43U);
            aCarry = TwistMix64::DiffuseC(aCarry);
            //
            aWorkLaneD[S_BLOCK1 - aIndex] = aIngress;
        }
    }
    // KDF_A_D kdf_a_loop_d (end)
    *pPrevious = aPrevious;
    *pIngress = aIngress;
    *pCarry = aCarry;
    *pWandererA = aWandererA;
    *pWandererB = aWandererB;
    *pWandererC = aWandererC;
    *pWandererD = aWandererD;
    *pWandererE = aWandererE;
    *pWandererF = aWandererF;
    *pWandererG = aWandererG;
    *pWandererH = aWandererH;
    *pWandererI = aWandererI;
    *pWandererJ = aWandererJ;
    *pWandererK = aWandererK;
}

void TwistExpander_Exercea_Arx::KDF_B_A(TwistWorkSpace *pWorkSpace,
                     std::uint64_t pNonce,
                     TwistDomainConstants *pConstants,
                     TwistDomainSaltSet *pDomainSaltSet,
                     std::uint64_t *pPrevious,
                     std::uint64_t *pIngress,
                     std::uint64_t *pCarry,
                     std::uint64_t *pWandererA,
                     std::uint64_t *pWandererB,
                     std::uint64_t *pWandererC,
                     std::uint64_t *pWandererD,
                     std::uint64_t *pWandererE,
                     std::uint64_t *pWandererF,
                     std::uint64_t *pWandererG,
                     std::uint64_t *pWandererH,
                     std::uint64_t *pWandererI,
                     std::uint64_t *pWandererJ,
                     std::uint64_t *pWandererK) {
    [[maybe_unused]] std::uint64_t *aOrbiterAssignSaltA = pDomainSaltSet->mOrbiterAssign.mSaltA;
    [[maybe_unused]] std::uint64_t *aOrbiterAssignSaltB = pDomainSaltSet->mOrbiterAssign.mSaltB;
    [[maybe_unused]] std::uint64_t *aOrbiterAssignSaltC = pDomainSaltSet->mOrbiterAssign.mSaltC;
    [[maybe_unused]] std::uint64_t *aOrbiterAssignSaltD = pDomainSaltSet->mOrbiterAssign.mSaltD;
    [[maybe_unused]] std::uint64_t *aOrbiterAssignSaltE = pDomainSaltSet->mOrbiterAssign.mSaltE;
    [[maybe_unused]] std::uint64_t *aOrbiterAssignSaltF = pDomainSaltSet->mOrbiterAssign.mSaltF;
    [[maybe_unused]] std::uint64_t *aOrbiterUpdateSaltA = pDomainSaltSet->mOrbiterUpdate.mSaltA;
    [[maybe_unused]] std::uint64_t *aOrbiterUpdateSaltB = pDomainSaltSet->mOrbiterUpdate.mSaltB;
    [[maybe_unused]] std::uint64_t *aOrbiterUpdateSaltC = pDomainSaltSet->mOrbiterUpdate.mSaltC;
    [[maybe_unused]] std::uint64_t *aOrbiterUpdateSaltD = pDomainSaltSet->mOrbiterUpdate.mSaltD;
    [[maybe_unused]] std::uint64_t *aOrbiterUpdateSaltE = pDomainSaltSet->mOrbiterUpdate.mSaltE;
    [[maybe_unused]] std::uint64_t *aOrbiterUpdateSaltF = pDomainSaltSet->mOrbiterUpdate.mSaltF;
    [[maybe_unused]] std::uint64_t *aWandererUpdateSaltA = pDomainSaltSet->mWandererUpdate.mSaltA;
    [[maybe_unused]] std::uint64_t *aWandererUpdateSaltB = pDomainSaltSet->mWandererUpdate.mSaltB;
    [[maybe_unused]] std::uint64_t *aWandererUpdateSaltC = pDomainSaltSet->mWandererUpdate.mSaltC;
    [[maybe_unused]] std::uint64_t *aWandererUpdateSaltD = pDomainSaltSet->mWandererUpdate.mSaltD;
    [[maybe_unused]] std::uint64_t *aWandererUpdateSaltE = pDomainSaltSet->mWandererUpdate.mSaltE;
    [[maybe_unused]] std::uint64_t *aWandererUpdateSaltF = pDomainSaltSet->mWandererUpdate.mSaltF;
    [[maybe_unused]] std::uint8_t *aExpandLaneA = pWorkSpace->mExpansionLaneA;
    [[maybe_unused]] std::uint8_t *aExpandLaneB = pWorkSpace->mExpansionLaneB;
    [[maybe_unused]] std::uint8_t *aExpandLaneC = pWorkSpace->mExpansionLaneC;
    [[maybe_unused]] std::uint8_t *aExpandLaneD = pWorkSpace->mExpansionLaneD;
    [[maybe_unused]] std::uint8_t *aWorkLaneA = pWorkSpace->mWorkLaneA;
    [[maybe_unused]] std::uint8_t *aWorkLaneB = pWorkSpace->mWorkLaneB;
    [[maybe_unused]] std::uint8_t *aWorkLaneC = pWorkSpace->mWorkLaneC;
    [[maybe_unused]] std::uint8_t *aWorkLaneD = pWorkSpace->mWorkLaneD;
    [[maybe_unused]] std::uint8_t *aOperationLaneA = pWorkSpace->mOperationLaneA;
    [[maybe_unused]] std::uint8_t *aOperationLaneB = pWorkSpace->mOperationLaneB;
    [[maybe_unused]] std::uint8_t *aOperationLaneC = pWorkSpace->mOperationLaneC;
    [[maybe_unused]] std::uint8_t *aOperationLaneD = pWorkSpace->mOperationLaneD;
    [[maybe_unused]] std::uint8_t *aFireLaneA = pWorkSpace->mFireLaneA;
    [[maybe_unused]] std::uint8_t *aFireLaneB = pWorkSpace->mFireLaneB;
    [[maybe_unused]] std::uint8_t *aFireLaneC = pWorkSpace->mFireLaneC;
    [[maybe_unused]] std::uint8_t *aFireLaneD = pWorkSpace->mFireLaneD;
    std::uint64_t aCross = 0; std::uint64_t aScatter = 0;

    std::uint64_t aOrbiterA = 0; std::uint64_t aOrbiterB = 0; std::uint64_t aOrbiterC = 0; std::uint64_t aOrbiterD = 0;
    std::uint64_t aOrbiterE = 0; std::uint64_t aOrbiterF = 0; std::uint64_t aOrbiterG = 0; std::uint64_t aOrbiterH = 0;
    std::uint64_t aOrbiterI = 0; std::uint64_t aOrbiterJ = 0; std::uint64_t aOrbiterK = 0;

    // [kdf-a arx]
    std::uint64_t aNonceWordA = TwistMix64::DiffuseB(pNonce * 0xB1E2114191278205ULL + 0xAEEC4C5D2A6D6F71ULL);
    std::uint64_t aNonceWordB = TwistMix64::DiffuseB(pNonce * 0xDDDA90C8E4F828FFULL + 0x9676EEC493B01FDCULL);
    std::uint64_t aNonceWordC = TwistMix64::DiffuseC(pNonce * 0xAFA82760631D49A7ULL + 0xF35E6B1311C4FB4AULL);
    std::uint64_t aNonceWordD = TwistMix64::DiffuseC(pNonce * 0xD6800D02FAE5E311ULL + 0xCDEE9F19FC91F549ULL);
    std::uint64_t aNonceWordE = TwistMix64::DiffuseB(pNonce * 0xFFBA0491BA336EC7ULL + 0x96D4DAC74320EF69ULL);
    std::uint64_t aNonceWordF = TwistMix64::DiffuseC(pNonce * 0xB27DC0BB52D4BF0BULL + 0xED52FBA995C88FD9ULL);
    std::uint64_t aNonceWordG = TwistMix64::DiffuseA(pNonce * 0x94CC0A5C5F595BC1ULL + 0xB484231CC8210022ULL);
    std::uint64_t aNonceWordH = TwistMix64::DiffuseB(pNonce * 0xC107C4C1B9792BB5ULL + 0x9E19EC3A9D51011DULL);
    std::uint64_t aNonceWordI = TwistMix64::DiffuseA(pNonce * 0xA36EF2BD7544A51BULL + 0xAC95772DA2C0517AULL);
    std::uint64_t aNonceWordJ = TwistMix64::DiffuseC(pNonce * 0xF34FBB994421311FULL + 0xCE74AA309E096880ULL);
    std::uint64_t aNonceWordK = TwistMix64::DiffuseB(pNonce * 0x8A2E6E59F0B1EF1BULL + 0x991502F09BE895EDULL);
    std::uint64_t aNonceWordL = TwistMix64::DiffuseB(pNonce * 0x87ED8A2012F846D9ULL + 0xB138AFB2AE56FDDCULL);
    std::uint64_t aNonceWordM = TwistMix64::DiffuseC(pNonce * 0xD4EDAC7795702817ULL + 0xFCED6BFC863C805EULL);
    std::uint64_t aNonceWordN = TwistMix64::DiffuseC(pNonce * 0xF2F722FA2EA38663ULL + 0xC36AE7A5D486299FULL);
    std::uint64_t aNonceWordO = TwistMix64::DiffuseB(pNonce * 0x87110CCA7DF81331ULL + 0xBF9612A54D0E9951ULL);
    std::uint64_t aNonceWordP = TwistMix64::DiffuseA(pNonce * 0xE249BAEBF6400EABULL + 0xA4B9D19986608EF0ULL);
    std::uint64_t aDomainWordIngress = pConstants->mIngress;
    std::uint64_t aDomainWordScatter = pConstants->mScatter;
    std::uint64_t aDomainWordCross = pConstants->mCross;
    [[maybe_unused]] std::uint8_t *mSource = pWorkSpace->mSource;
    std::uint64_t aPrevious = *pPrevious;
    std::uint64_t aIngress = *pIngress;
    std::uint64_t aCarry = *pCarry;
    std::uint64_t aWandererA = *pWandererA;
    std::uint64_t aWandererB = *pWandererB;
    std::uint64_t aWandererC = *pWandererC;
    std::uint64_t aWandererD = *pWandererD;
    std::uint64_t aWandererE = *pWandererE;
    std::uint64_t aWandererF = *pWandererF;
    std::uint64_t aWandererG = *pWandererG;
    std::uint64_t aWandererH = *pWandererH;
    std::uint64_t aWandererI = *pWandererI;
    std::uint64_t aWandererJ = *pWandererJ;
    std::uint64_t aWandererK = *pWandererK;
    // KDF_B_A kdf_b_loop_a (start)
    {
        // KDF_B_A kdf_b_loop_a lane group
        // read from: aWorkLaneA, aWorkLaneB, aFireLaneA, aWorkLaneC, aWorkLaneD, aFireLaneC, aExpandLaneA, aOperationLaneB, aOperationLaneD, aExpandLaneB, aOperationLaneC, aOperationLaneA, aExpandLaneC, aFireLaneD, aFireLaneB
        // write to: aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD
    
        // kdf_b_loop_a loop 1
        // ingress from: aWorkLaneA, aWorkLaneB, aFireLaneA
        // ingress directions: aWorkLaneA forward forced, aWorkLaneB forward forced, aFireLaneA forward/backward random
        // cross from: aWorkLaneC, aWorkLaneD, aFireLaneC
        // cross directions: aWorkLaneC backward forced, aWorkLaneD backward forced, aFireLaneC backward/forward random
        // write to: aExpandLaneA
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aWorkLaneA[((aIndex + 7840U)) & S_BLOCK1], 51U) ^ RotL64(aWorkLaneB[((aIndex + 5188U)) & S_BLOCK1], 21U));
            aIngress ^= RotL64(aFireLaneA[((aIndex + 3228U)) & S_BLOCK1], 40U);
            aIngress = TwistMix64::DiffuseA(((aIngress ^ aDomainWordIngress) ^ aNonceWordP));
            //
            aCross = (RotL64(aWorkLaneC[((S_BLOCK1 - aIndex + 1808U)) & S_BLOCK1], 41U) ^ RotL64(aWorkLaneD[((S_BLOCK1 - aIndex + 3627U)) & S_BLOCK1], 13U));
            aCross ^= RotL64(aFireLaneC[((S_BLOCK1 - aIndex + 5282U)) & S_BLOCK1], 27U);
            aCross = TwistMix64::DiffuseA(((aCross ^ aDomainWordCross) ^ aNonceWordB));
            //
            aScatter = (RotL64(aIngress, 39U) ^ RotL64(aCarry, 52U)) ^ (RotL64(aCross, 3U) + RotL64(aPrevious, 23U));
            aScatter = TwistMix64::DiffuseA(((aScatter ^ aDomainWordScatter) ^ aNonceWordI));
            //
            aOrbiterD = (aWandererD + RotL64(aIngress, 18U)) + 16519040829220310189U;
            aOrbiterJ = (((aWandererJ + RotL64(aScatter, 51U)) + RotL64(aCarry, 51U)) + 6888002778416941825U) + aNonceWordI;
            aOrbiterB = (((aWandererH + RotL64(aCross, 57U)) + RotL64(aCarry, 5U)) + 1310832187746534025U) + aNonceWordN;
            aOrbiterC = (((aWandererA + RotL64(aPrevious, 29U)) + RotL64(aCarry, 19U)) + 5890888009051281674U) + aOrbiterAssignSaltA[(((31U - aIndex) + 19U)) & S_SALT1];
            aOrbiterA = (aWandererK + RotL64(aScatter, 41U)) + 5143864838362464857U;
            aOrbiterG = (aWandererI + RotL64(aCross, 5U)) + 15591534069452660003U;
            aOrbiterK = ((aWandererG + RotL64(aIngress, 11U)) + 1466867671765325096U) + aOrbiterAssignSaltD[(((31U - aIndex) + 7U)) & S_SALT1];
            //
            aOrbiterD = (aOrbiterD + aOrbiterJ) + 13931443680107902488U;
            aOrbiterB = (aOrbiterB ^ aOrbiterD) ^ 15400747367673245552U;
            aOrbiterB = RotL64((aOrbiterB * 7011651369456453127U), 29U);
            //
            aOrbiterJ = (aOrbiterJ + aOrbiterC) + 2836975369734495759U;
            aOrbiterA = ((aOrbiterA ^ aOrbiterJ) ^ 2370720358274970117U) ^ aOrbiterUpdateSaltC[((aIndex + 29U)) & S_SALT1];
            aOrbiterA = RotL64((aOrbiterA * 4615571902817575375U), 39U);
            //
            aOrbiterG = (aOrbiterG + aOrbiterB) + 3470677184188006133U;
            aOrbiterC = (aOrbiterC ^ aOrbiterG) ^ 7175584278499266723U;
            aOrbiterC = RotL64((aOrbiterC * 10067096593682482345U), 13U);
            //
            aOrbiterK = (aOrbiterK + aOrbiterG) + 6095078817776863055U;
            aOrbiterJ = (aOrbiterJ ^ aOrbiterK) ^ 2176637999243513070U;
            aOrbiterJ = RotL64((aOrbiterJ * 12215701810843975501U), 19U);
            //
            aOrbiterA = (aOrbiterA + aOrbiterD) + 5580391239754903129U;
            aOrbiterG = ((aOrbiterG ^ aOrbiterA) ^ 15196125567953871184U) ^ aOrbiterUpdateSaltE[((aIndex + 26U)) & S_SALT1];
            aOrbiterG = RotL64((aOrbiterG * 12686361960729564519U), 57U);
            //
            aOrbiterB = ((aOrbiterB + aOrbiterA) + 12787014151503209931U) + aNonceWordC;
            aOrbiterK = ((aOrbiterK ^ aOrbiterB) ^ 1523153207064063495U) ^ aNonceWordF;
            aOrbiterK = RotL64((aOrbiterK * 3113907543551927561U), 51U);
            //
            aOrbiterC = ((aOrbiterC + aOrbiterK) + 12973289026485937829U) + aOrbiterUpdateSaltB[((aIndex + 3U)) & S_SALT1];
            aOrbiterD = ((aOrbiterD ^ aOrbiterC) ^ 9087439766232078173U) ^ aOrbiterUpdateSaltD[(((31U - aIndex) + 5U)) & S_SALT1];
            aOrbiterD = RotL64((aOrbiterD * 5817029335999350327U), 5U);
            //
            aIngress = aOrbiterC ^ RotL64(aOrbiterA, 11U);
            aIngress = aIngress + (RotL64(aOrbiterJ, 51U) ^ aOrbiterD);
            aIngress = aIngress + (RotL64(aOrbiterB, 3U) ^ aOrbiterK);
            aIngress = aIngress + RotL64(aOrbiterG, 39U);
            aIngress = TwistMix64::DiffuseB((aIngress + aScatter));
            //
            aWandererA = aWandererA ^ ((RotL64(aCross, 29U) + aOrbiterJ) + RotL64(aOrbiterD, 11U));
            aWandererI = aWandererI + (((((RotL64(aIngress, 57U) + aOrbiterA) + RotL64(aOrbiterB, 43U)) + RotL64(aCarry, 3U)) + aNonceWordL) + aWandererUpdateSaltF[(((31U - aIndex) + 27U)) & S_SALT1]);
            aWandererK = aWandererK ^ ((RotL64(aPrevious, 35U) + RotL64(aOrbiterA, 35U)) + aOrbiterJ);
            aWandererJ = aWandererJ + ((RotL64(aScatter, 11U) + RotL64(aOrbiterG, 27U)) + aOrbiterK);
            aWandererH = aWandererH ^ (((RotL64(aPrevious, 23U) + aOrbiterD) + RotL64(aOrbiterA, 20U)) + aNonceWordJ);
            aWandererG = aWandererG + ((((RotL64(aCross, 51U) + aOrbiterG) + RotL64(aOrbiterA, 53U)) + RotL64(aCarry, 37U)) + aNonceWordO);
            aWandererD = aWandererD ^ ((((RotL64(aIngress, 42U) + RotL64(aOrbiterD, 5U)) + aOrbiterC) + aNonceWordG) + aWandererUpdateSaltA[(((31U - aIndex) + 24U)) & S_SALT1]);
            //
            aCarry = aCarry + (RotL64(aWandererH, 23U) ^ aWandererD);
            aCarry = aCarry + (aWandererG ^ RotL64(aWandererK, 19U));
            aCarry = aCarry + (RotL64(aWandererJ, 28U) ^ aWandererA);
            aCarry = aCarry + RotL64(aWandererI, 3U);
            aCarry = aCarry + RotL64(aIngress, 35U);
            aCarry = TwistMix64::DiffuseA(aCarry);
            //
            aExpandLaneA[aIndex] = aIngress;
        }
    
        // kdf_b_loop_a loop 2
        // ingress from: aExpandLaneA, aWorkLaneC, aOperationLaneB
        // ingress directions: aExpandLaneA forward forced, aWorkLaneC forward forced, aOperationLaneB forward/backward random
        // cross from: aWorkLaneA, aWorkLaneD, aOperationLaneD
        // cross directions: aWorkLaneA backward forced, aWorkLaneD backward forced, aOperationLaneD backward/forward random
        // write to: aExpandLaneB
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aExpandLaneA[((aIndex + 10755U)) & S_BLOCK1], 57U) ^ RotL64(aWorkLaneC[((aIndex + 15212U)) & S_BLOCK1], 3U));
            aIngress ^= RotL64(aOperationLaneB[((aIndex + 14002U)) & S_BLOCK1], 29U);
            aIngress = TwistMix64::DiffuseB(((aIngress ^ aDomainWordIngress) ^ aNonceWordB));
            //
            aCross = (RotL64(aWorkLaneA[((S_BLOCK1 - aIndex + 12210U)) & S_BLOCK1], 40U) ^ RotL64(aWorkLaneD[((S_BLOCK1 - aIndex + 13216U)) & S_BLOCK1], 21U));
            aCross ^= RotL64(aOperationLaneD[((S_BLOCK1 - aIndex + 11958U)) & S_BLOCK1], 51U);
            aCross = TwistMix64::DiffuseB(((aCross ^ aDomainWordCross) ^ aNonceWordG));
            //
            aScatter = (RotL64(aCarry, 41U) ^ RotL64(aIngress, 3U)) ^ (RotL64(aCross, 54U) + RotL64(aPrevious, 21U));
            aScatter = TwistMix64::DiffuseB(((aScatter ^ aDomainWordScatter) ^ aNonceWordM));
            //
            aOrbiterA = ((aWandererI + RotL64(aIngress, 37U)) + 898812731947995389U) + aOrbiterAssignSaltB[(((31U - aIndex) + 17U)) & S_SALT1];
            aOrbiterH = ((aWandererG + RotL64(aCross, 5U)) + RotL64(aCarry, 5U)) + 8677347622525527167U;
            aOrbiterD = ((aWandererK + RotL64(aScatter, 43U)) + 770321564027567654U) + aNonceWordI;
            aOrbiterF = ((aWandererH + RotL64(aPrevious, 51U)) + RotL64(aCarry, 19U)) + 11020474858081526395U;
            aOrbiterJ = (((aWandererC + RotL64(aScatter, 29U)) + RotL64(aCarry, 51U)) + 17289793580414993470U) + aNonceWordJ;
            aOrbiterE = ((aWandererB + RotL64(aCross, 18U)) + 10111912559295118444U) + aNonceWordM;
            aOrbiterK = ((aWandererA + RotL64(aIngress, 57U)) + 8083622125544542011U) + aOrbiterAssignSaltC[((aIndex + 8U)) & S_SALT1];
            //
            aOrbiterA = ((aOrbiterA + aOrbiterH) + 7149858558922988240U) + aOrbiterUpdateSaltA[(((31U - aIndex) + 9U)) & S_SALT1];
            aOrbiterD = ((aOrbiterD ^ aOrbiterA) ^ 5919683821379905699U) ^ aOrbiterUpdateSaltD[(((31U - aIndex) + 7U)) & S_SALT1];
            aOrbiterD = RotL64((aOrbiterD * 16705119888884231567U), 53U);
            //
            aOrbiterH = ((aOrbiterH + aOrbiterF) + 6860902846079238714U) + aOrbiterUpdateSaltC[((aIndex + 13U)) & S_SALT1];
            aOrbiterJ = (aOrbiterJ ^ aOrbiterH) ^ 15083517836867542075U;
            aOrbiterJ = RotL64((aOrbiterJ * 4686657139237578325U), 29U);
            //
            aOrbiterJ = (aOrbiterJ + aOrbiterE) + 14852868368708376381U;
            aOrbiterA = (aOrbiterA ^ aOrbiterJ) ^ 9860233289028878323U;
            aOrbiterA = RotL64((aOrbiterA * 13418143547952204667U), 19U);
            //
            aOrbiterF = (aOrbiterF + aOrbiterD) + 772406119079116272U;
            aOrbiterE = ((aOrbiterE ^ aOrbiterF) ^ 7971141501337627589U) ^ aNonceWordL;
            aOrbiterE = RotL64((aOrbiterE * 10168120622976358617U), 35U);
            //
            aOrbiterK = ((aOrbiterK + aOrbiterA) + 8478568022896691911U) + aOrbiterUpdateSaltF[(((31U - aIndex) + 19U)) & S_SALT1];
            aOrbiterF = ((aOrbiterF ^ aOrbiterK) ^ 4027604850785607101U) ^ aNonceWordD;
            aOrbiterF = RotL64((aOrbiterF * 4826627523578901467U), 13U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterJ) + 17199331557841535430U;
            aOrbiterK = (aOrbiterK ^ aOrbiterD) ^ 7515957656979776361U;
            aOrbiterK = RotL64((aOrbiterK * 5468950152869656599U), 5U);
            //
            aOrbiterE = (aOrbiterE + aOrbiterK) + 17138249294921502391U;
            aOrbiterH = (aOrbiterH ^ aOrbiterE) ^ 16236812863923234668U;
            aOrbiterH = RotL64((aOrbiterH * 2925542836624164807U), 43U);
            //
            aIngress = aOrbiterE ^ RotL64(aOrbiterH, 51U);
            aIngress = aIngress + (RotL64(aOrbiterA, 11U) ^ aOrbiterJ);
            aIngress = aIngress + (aOrbiterD ^ RotL64(aOrbiterF, 41U));
            aIngress = aIngress + RotL64(aOrbiterK, 24U);
            aIngress = TwistMix64::DiffuseB((aIngress + aScatter));
            //
            aWandererG = aWandererG + ((((RotL64(aCross, 3U) + aOrbiterF) + RotL64(aOrbiterE, 51U)) + aNonceWordK) + aWandererUpdateSaltB[(((31U - aIndex) + 3U)) & S_SALT1]);
            aWandererI = aWandererI ^ (((RotL64(aPrevious, 29U) + aOrbiterE) + RotL64(aOrbiterJ, 6U)) + aWandererUpdateSaltD[((aIndex + 28U)) & S_SALT1]);
            aWandererK = aWandererK + ((((RotL64(aIngress, 41U) + aOrbiterA) + RotL64(aOrbiterK, 13U)) + RotL64(aCarry, 27U)) + aNonceWordA);
            aWandererB = aWandererB ^ ((RotL64(aScatter, 10U) + aOrbiterA) + RotL64(aOrbiterD, 57U));
            aWandererC = aWandererC + (((RotL64(aPrevious, 47U) + RotL64(aOrbiterA, 23U)) + aOrbiterE) + RotL64(aCarry, 57U));
            aWandererA = aWandererA ^ ((RotL64(aIngress, 21U) + aOrbiterK) + RotL64(aOrbiterF, 43U));
            aWandererH = aWandererH + ((RotL64(aScatter, 35U) + RotL64(aOrbiterA, 37U)) + aOrbiterH);
            //
            aCarry = aCarry + (aWandererA ^ RotL64(aWandererG, 48U));
            aCarry = aCarry + (RotL64(aWandererK, 19U) ^ aWandererB);
            aCarry = aCarry + (aWandererC ^ RotL64(aWandererI, 23U));
            aCarry = aCarry + RotL64(aWandererH, 43U);
            aCarry = aCarry + RotL64(aIngress, 34U);
            aCarry = TwistMix64::DiffuseB(aCarry);
            //
            aExpandLaneB[S_BLOCK1 - aIndex] = aIngress;
        }
    
        // kdf_b_loop_a loop 3
        // ingress from: aExpandLaneB, aWorkLaneD, aOperationLaneC
        // ingress directions: aExpandLaneB forward forced, aWorkLaneD forward forced, aOperationLaneC forward/backward random
        // cross from: aExpandLaneA, aWorkLaneB, aOperationLaneA
        // cross directions: aExpandLaneA backward forced, aWorkLaneB backward forced, aOperationLaneA backward/forward random
        // write to: aExpandLaneC
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aExpandLaneB[((aIndex + 19387U)) & S_BLOCK1], 43U) ^ RotL64(aWorkLaneD[((aIndex + 20326U)) & S_BLOCK1], 35U));
            aIngress ^= RotL64(aOperationLaneC[((aIndex + 21589U)) & S_BLOCK1], 11U);
            aIngress = TwistMix64::DiffuseC(((aIngress ^ aDomainWordIngress) ^ aNonceWordF));
            //
            aCross = (RotL64(aExpandLaneA[((S_BLOCK1 - aIndex + 18073U)) & S_BLOCK1], 27U) ^ RotL64(aWorkLaneB[((S_BLOCK1 - aIndex + 23556U)) & S_BLOCK1], 11U));
            aCross ^= RotL64(aOperationLaneA[((aIndex + 22737U)) & S_BLOCK1], 19U);
            aCross = TwistMix64::DiffuseC(((aCross ^ aDomainWordCross) ^ aNonceWordN));
            //
            aScatter = (RotL64(aCarry, 11U) + RotL64(aIngress, 41U)) ^ (RotL64(aCross, 23U) ^ RotL64(aPrevious, 54U));
            aScatter = TwistMix64::DiffuseB(((aScatter ^ aDomainWordScatter) ^ aNonceWordD));
            //
            aOrbiterF = ((aWandererK + RotL64(aScatter, 42U)) + 785861751704720606U) + aNonceWordD;
            aOrbiterG = (aWandererF + RotL64(aPrevious, 5U)) + 15968088718435606299U;
            aOrbiterD = ((aWandererB + RotL64(aIngress, 27U)) + RotL64(aCarry, 53U)) + 1393976526590347151U;
            aOrbiterA = ((((aWandererC + RotL64(aCross, 19U)) + RotL64(aCarry, 27U)) + 17240750947292745884U) + aOrbiterAssignSaltF[(((31U - aIndex) + 7U)) & S_SALT1]) + aNonceWordB;
            aOrbiterK = (aWandererA + RotL64(aIngress, 51U)) + 4921576136163183137U;
            aOrbiterC = ((((aWandererI + RotL64(aPrevious, 57U)) + RotL64(aCarry, 5U)) + 3334047873553153032U) + aOrbiterAssignSaltE[(((31U - aIndex) + 21U)) & S_SALT1]) + aNonceWordL;
            aOrbiterI = (aWandererJ + RotL64(aScatter, 11U)) + 15086509978458408698U;
            //
            aOrbiterF = ((aOrbiterF + aOrbiterG) + 892391205397581998U) + aNonceWordK;
            aOrbiterD = ((aOrbiterD ^ aOrbiterF) ^ 2965686403183767521U) ^ aOrbiterUpdateSaltD[(((31U - aIndex) + 13U)) & S_SALT1];
            aOrbiterD = RotL64((aOrbiterD * 709160942482770225U), 41U);
            //
            aOrbiterA = (aOrbiterA + aOrbiterK) + 14632215393655706170U;
            aOrbiterC = (aOrbiterC ^ aOrbiterA) ^ 15740589515342377322U;
            aOrbiterC = RotL64((aOrbiterC * 15677716942904794913U), 47U);
            //
            aOrbiterG = ((aOrbiterG + aOrbiterD) + 11131164813943086445U) + aNonceWordA;
            aOrbiterI = ((aOrbiterI ^ aOrbiterG) ^ 6988080581278900960U) ^ aOrbiterUpdateSaltC[((aIndex + 3U)) & S_SALT1];
            aOrbiterI = RotL64((aOrbiterI * 6412189142344044255U), 29U);
            //
            aOrbiterK = ((aOrbiterK + aOrbiterC) + 16021254613117657178U) + aOrbiterUpdateSaltB[(((31U - aIndex) + 14U)) & S_SALT1];
            aOrbiterF = (aOrbiterF ^ aOrbiterK) ^ 6183615599897921154U;
            aOrbiterF = RotL64((aOrbiterF * 9976411093264211033U), 23U);
            //
            aOrbiterC = (aOrbiterC + aOrbiterF) + 12533992547026652747U;
            aOrbiterG = ((aOrbiterG ^ aOrbiterC) ^ 3104325358982904219U) ^ aOrbiterUpdateSaltF[((aIndex + 6U)) & S_SALT1];
            aOrbiterG = RotL64((aOrbiterG * 14977348108778147265U), 11U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterI) + 3878525937957474644U;
            aOrbiterA = (aOrbiterA ^ aOrbiterD) ^ 2120435259884368445U;
            aOrbiterA = RotL64((aOrbiterA * 15964718652193073177U), 57U);
            //
            aOrbiterI = (aOrbiterI + aOrbiterA) + 14928658302694194856U;
            aOrbiterK = ((aOrbiterK ^ aOrbiterI) ^ 9121310461310309348U) ^ aNonceWordP;
            aOrbiterK = RotL64((aOrbiterK * 17304439784647477491U), 35U);
            //
            aIngress = aOrbiterI ^ RotL64(aOrbiterA, 47U);
            aIngress = aIngress + (RotL64(aOrbiterK, 3U) ^ aOrbiterF);
            aIngress = aIngress + (RotL64(aOrbiterD, 41U) ^ aOrbiterC);
            aIngress = aIngress + RotL64(aOrbiterG, 19U);
            aIngress = TwistMix64::DiffuseA((aIngress + aScatter));
            //
            aWandererB = aWandererB ^ ((RotL64(aScatter, 35U) + aOrbiterK) + RotL64(aOrbiterC, 19U));
            aWandererI = aWandererI + (((((RotL64(aPrevious, 19U) + aOrbiterA) + RotL64(aOrbiterI, 50U)) + RotL64(aCarry, 21U)) + aNonceWordI) + aWandererUpdateSaltC[(((31U - aIndex) + 22U)) & S_SALT1]);
            aWandererC = aWandererC ^ ((((RotL64(aIngress, 11U) + aOrbiterG) + RotL64(aOrbiterF, 29U)) + aNonceWordM) + aWandererUpdateSaltE[(((31U - aIndex) + 15U)) & S_SALT1]);
            aWandererJ = aWandererJ + ((((RotL64(aCross, 43U) + aOrbiterG) + RotL64(aOrbiterD, 39U)) + RotL64(aCarry, 47U)) + aNonceWordC);
            aWandererK = aWandererK ^ (((RotL64(aIngress, 27U) + aOrbiterD) + RotL64(aOrbiterA, 11U)) + aNonceWordG);
            aWandererA = aWandererA + ((RotL64(aPrevious, 52U) + RotL64(aOrbiterF, 57U)) + aOrbiterD);
            aWandererF = aWandererF ^ ((RotL64(aCross, 5U) + RotL64(aOrbiterD, 3U)) + aOrbiterC);
            //
            aCarry = aCarry + (RotL64(aWandererJ, 27U) ^ aWandererA);
            aCarry = aCarry + (aWandererB ^ RotL64(aWandererF, 35U));
            aCarry = aCarry + (RotL64(aWandererK, 52U) ^ aWandererC);
            aCarry = aCarry + RotL64(aWandererI, 57U);
            aCarry = aCarry + RotL64(aIngress, 19U);
            aCarry = TwistMix64::DiffuseA(aCarry);
            //
            aExpandLaneC[aIndex] = aIngress;
        }
    
        // kdf_b_loop_a loop 4
        // ingress from: aExpandLaneC, aExpandLaneA, aFireLaneD
        // ingress directions: aExpandLaneC forward forced, aExpandLaneA forward forced, aFireLaneD forward/backward random
        // cross from: aExpandLaneB, aWorkLaneC, aFireLaneB
        // cross directions: aExpandLaneB backward forced, aWorkLaneC backward forced, aFireLaneB backward/forward random
        // write to: aExpandLaneD
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aExpandLaneC[((aIndex + 28177U)) & S_BLOCK1], 56U) ^ RotL64(aExpandLaneA[((aIndex + 32510U)) & S_BLOCK1], 21U));
            aIngress ^= RotL64(aFireLaneD[((aIndex + 25999U)) & S_BLOCK1], 5U);
            aIngress = TwistMix64::DiffuseB(((aIngress ^ aDomainWordIngress) ^ aNonceWordD));
            //
            aCross = (RotL64(aExpandLaneB[((S_BLOCK1 - aIndex + 32413U)) & S_BLOCK1], 51U) ^ RotL64(aWorkLaneC[((S_BLOCK1 - aIndex + 28554U)) & S_BLOCK1], 3U));
            aCross ^= RotL64(aFireLaneB[((S_BLOCK1 - aIndex + 28536U)) & S_BLOCK1], 37U);
            aCross = TwistMix64::DiffuseA(((aCross ^ aDomainWordCross) ^ aNonceWordP));
            //
            aScatter = (RotL64(aCross, 35U) ^ RotL64(aPrevious, 53U)) + (RotL64(aIngress, 3U) + RotL64(aCarry, 22U));
            aScatter = TwistMix64::DiffuseC(((aScatter ^ aDomainWordScatter) ^ aNonceWordE));
            //
            aOrbiterJ = (aWandererI + RotL64(aScatter, 4U)) + 13333509828310369865U;
            aOrbiterI = (aWandererG + RotL64(aCross, 23U)) + 7645352517103840797U;
            aOrbiterB = (((aWandererB + RotL64(aIngress, 29U)) + RotL64(aCarry, 53U)) + 5310766306660062655U) + aNonceWordI;
            aOrbiterF = ((aWandererA + RotL64(aPrevious, 13U)) + RotL64(aCarry, 39U)) + 5165635069832352932U;
            aOrbiterE = ((aWandererF + RotL64(aCross, 57U)) + 15684141764734281849U) + aOrbiterAssignSaltD[((aIndex + 10U)) & S_SALT1];
            aOrbiterG = (((aWandererH + RotL64(aScatter, 51U)) + RotL64(aCarry, 5U)) + 3327963374225061738U) + aNonceWordK;
            aOrbiterD = (((aWandererJ + RotL64(aPrevious, 41U)) + 8625811794878848871U) + aOrbiterAssignSaltA[((aIndex + 16U)) & S_SALT1]) + aNonceWordM;
            //
            aOrbiterJ = (((aOrbiterJ + aOrbiterI) + 7598657468430485291U) + aOrbiterUpdateSaltE[((aIndex + 26U)) & S_SALT1]) + aNonceWordB;
            aOrbiterB = (aOrbiterB ^ aOrbiterJ) ^ 2881171216276746485U;
            aOrbiterB = RotL64((aOrbiterB * 3331350584102843605U), 13U);
            //
            aOrbiterI = ((aOrbiterI + aOrbiterB) + 10237691227222918101U) + aOrbiterUpdateSaltC[(((31U - aIndex) + 12U)) & S_SALT1];
            aOrbiterF = (aOrbiterF ^ aOrbiterI) ^ 6419254255884834497U;
            aOrbiterF = RotL64((aOrbiterF * 3816625473642865305U), 5U);
            //
            aOrbiterB = ((aOrbiterB + aOrbiterF) + 4238455444646479956U) + aNonceWordH;
            aOrbiterE = (aOrbiterE ^ aOrbiterB) ^ 14936613353493061492U;
            aOrbiterE = RotL64((aOrbiterE * 3544216916806292273U), 19U);
            //
            aOrbiterG = (aOrbiterG + aOrbiterJ) + 15324699725208372627U;
            aOrbiterI = (aOrbiterI ^ aOrbiterG) ^ 9506640480601832011U;
            aOrbiterI = RotL64((aOrbiterI * 12819564111348390227U), 57U);
            //
            aOrbiterF = ((aOrbiterF + aOrbiterE) + 3709149613660215641U) + aOrbiterUpdateSaltA[((aIndex + 17U)) & S_SALT1];
            aOrbiterD = ((aOrbiterD ^ aOrbiterF) ^ 1724290199312754307U) ^ aOrbiterUpdateSaltB[((aIndex + 11U)) & S_SALT1];
            aOrbiterD = RotL64((aOrbiterD * 12597580418257897965U), 43U);
            //
            aOrbiterE = (aOrbiterE + aOrbiterD) + 13191172833570139194U;
            aOrbiterG = (aOrbiterG ^ aOrbiterE) ^ 3686087945377837886U;
            aOrbiterG = RotL64((aOrbiterG * 10883609557429936283U), 37U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterG) + 10418330386245397022U;
            aOrbiterJ = ((aOrbiterJ ^ aOrbiterD) ^ 5383531313632347245U) ^ aNonceWordE;
            aOrbiterJ = RotL64((aOrbiterJ * 2987755379396160073U), 27U);
            //
            aIngress = RotL64(aOrbiterJ, 41U) ^ aOrbiterB;
            aIngress = aIngress + (RotL64(aOrbiterF, 5U) ^ aOrbiterI);
            aIngress = aIngress + (RotL64(aOrbiterG, 51U) ^ aOrbiterE);
            aIngress = aIngress + RotL64(aOrbiterD, 23U);
            aIngress = TwistMix64::DiffuseA((aIngress + aScatter));
            //
            aWandererB = aWandererB ^ (((RotL64(aCross, 11U) + aOrbiterB) + RotL64(aOrbiterI, 21U)) + aWandererUpdateSaltA[(((31U - aIndex) + 18U)) & S_SALT1]);
            aWandererA = aWandererA + ((((RotL64(aIngress, 21U) + RotL64(aOrbiterJ, 3U)) + aOrbiterE) + RotL64(aCarry, 57U)) + aNonceWordF);
            aWandererI = aWandererI ^ ((RotL64(aScatter, 47U) + RotL64(aOrbiterB, 57U)) + aOrbiterF);
            aWandererH = aWandererH + ((((RotL64(aPrevious, 5U) + aOrbiterG) + RotL64(aOrbiterJ, 27U)) + RotL64(aCarry, 27U)) + aNonceWordC);
            aWandererF = aWandererF ^ (((RotL64(aScatter, 57U) + aOrbiterD) + RotL64(aOrbiterG, 11U)) + aNonceWordL);
            aWandererJ = aWandererJ + (((RotL64(aPrevious, 35U) + RotL64(aOrbiterJ, 42U)) + aOrbiterD) + aWandererUpdateSaltF[(((31U - aIndex) + 25U)) & S_SALT1]);
            aWandererG = aWandererG ^ (((RotL64(aCross, 28U) + aOrbiterJ) + RotL64(aOrbiterB, 35U)) + aNonceWordA);
            //
            aCarry = aCarry + (aWandererI ^ RotL64(aWandererB, 35U));
            aCarry = aCarry + (aWandererJ ^ RotL64(aWandererF, 46U));
            aCarry = aCarry + (RotL64(aWandererA, 27U) ^ aWandererG);
            aCarry = aCarry + RotL64(aWandererH, 57U);
            aCarry = aCarry + RotL64(aIngress, 23U);
            aCarry = TwistMix64::DiffuseB(aCarry);
            //
            aExpandLaneD[S_BLOCK1 - aIndex] = aIngress;
        }
    }
    // KDF_B_A kdf_b_loop_a (end)
    *pPrevious = aPrevious;
    *pIngress = aIngress;
    *pCarry = aCarry;
    *pWandererA = aWandererA;
    *pWandererB = aWandererB;
    *pWandererC = aWandererC;
    *pWandererD = aWandererD;
    *pWandererE = aWandererE;
    *pWandererF = aWandererF;
    *pWandererG = aWandererG;
    *pWandererH = aWandererH;
    *pWandererI = aWandererI;
    *pWandererJ = aWandererJ;
    *pWandererK = aWandererK;
}

void TwistExpander_Exercea_Arx::KDF_B_B(TwistWorkSpace *pWorkSpace,
                     std::uint64_t pNonce,
                     TwistDomainConstants *pConstants,
                     TwistDomainSaltSet *pDomainSaltSet,
                     std::uint64_t *pPrevious,
                     std::uint64_t *pIngress,
                     std::uint64_t *pCarry,
                     std::uint64_t *pWandererA,
                     std::uint64_t *pWandererB,
                     std::uint64_t *pWandererC,
                     std::uint64_t *pWandererD,
                     std::uint64_t *pWandererE,
                     std::uint64_t *pWandererF,
                     std::uint64_t *pWandererG,
                     std::uint64_t *pWandererH,
                     std::uint64_t *pWandererI,
                     std::uint64_t *pWandererJ,
                     std::uint64_t *pWandererK) {
    [[maybe_unused]] std::uint64_t *aOrbiterAssignSaltA = pDomainSaltSet->mOrbiterAssign.mSaltA;
    [[maybe_unused]] std::uint64_t *aOrbiterAssignSaltB = pDomainSaltSet->mOrbiterAssign.mSaltB;
    [[maybe_unused]] std::uint64_t *aOrbiterAssignSaltC = pDomainSaltSet->mOrbiterAssign.mSaltC;
    [[maybe_unused]] std::uint64_t *aOrbiterAssignSaltD = pDomainSaltSet->mOrbiterAssign.mSaltD;
    [[maybe_unused]] std::uint64_t *aOrbiterAssignSaltE = pDomainSaltSet->mOrbiterAssign.mSaltE;
    [[maybe_unused]] std::uint64_t *aOrbiterAssignSaltF = pDomainSaltSet->mOrbiterAssign.mSaltF;
    [[maybe_unused]] std::uint64_t *aOrbiterUpdateSaltA = pDomainSaltSet->mOrbiterUpdate.mSaltA;
    [[maybe_unused]] std::uint64_t *aOrbiterUpdateSaltB = pDomainSaltSet->mOrbiterUpdate.mSaltB;
    [[maybe_unused]] std::uint64_t *aOrbiterUpdateSaltC = pDomainSaltSet->mOrbiterUpdate.mSaltC;
    [[maybe_unused]] std::uint64_t *aOrbiterUpdateSaltD = pDomainSaltSet->mOrbiterUpdate.mSaltD;
    [[maybe_unused]] std::uint64_t *aOrbiterUpdateSaltE = pDomainSaltSet->mOrbiterUpdate.mSaltE;
    [[maybe_unused]] std::uint64_t *aOrbiterUpdateSaltF = pDomainSaltSet->mOrbiterUpdate.mSaltF;
    [[maybe_unused]] std::uint64_t *aWandererUpdateSaltA = pDomainSaltSet->mWandererUpdate.mSaltA;
    [[maybe_unused]] std::uint64_t *aWandererUpdateSaltB = pDomainSaltSet->mWandererUpdate.mSaltB;
    [[maybe_unused]] std::uint64_t *aWandererUpdateSaltC = pDomainSaltSet->mWandererUpdate.mSaltC;
    [[maybe_unused]] std::uint64_t *aWandererUpdateSaltD = pDomainSaltSet->mWandererUpdate.mSaltD;
    [[maybe_unused]] std::uint64_t *aWandererUpdateSaltE = pDomainSaltSet->mWandererUpdate.mSaltE;
    [[maybe_unused]] std::uint64_t *aWandererUpdateSaltF = pDomainSaltSet->mWandererUpdate.mSaltF;
    [[maybe_unused]] std::uint8_t *aExpandLaneA = pWorkSpace->mExpansionLaneA;
    [[maybe_unused]] std::uint8_t *aExpandLaneB = pWorkSpace->mExpansionLaneB;
    [[maybe_unused]] std::uint8_t *aExpandLaneC = pWorkSpace->mExpansionLaneC;
    [[maybe_unused]] std::uint8_t *aExpandLaneD = pWorkSpace->mExpansionLaneD;
    [[maybe_unused]] std::uint8_t *aWorkLaneA = pWorkSpace->mWorkLaneA;
    [[maybe_unused]] std::uint8_t *aWorkLaneB = pWorkSpace->mWorkLaneB;
    [[maybe_unused]] std::uint8_t *aWorkLaneC = pWorkSpace->mWorkLaneC;
    [[maybe_unused]] std::uint8_t *aWorkLaneD = pWorkSpace->mWorkLaneD;
    [[maybe_unused]] std::uint8_t *aOperationLaneA = pWorkSpace->mOperationLaneA;
    [[maybe_unused]] std::uint8_t *aOperationLaneB = pWorkSpace->mOperationLaneB;
    [[maybe_unused]] std::uint8_t *aOperationLaneC = pWorkSpace->mOperationLaneC;
    [[maybe_unused]] std::uint8_t *aOperationLaneD = pWorkSpace->mOperationLaneD;
    [[maybe_unused]] std::uint8_t *aFireLaneA = pWorkSpace->mFireLaneA;
    [[maybe_unused]] std::uint8_t *aFireLaneB = pWorkSpace->mFireLaneB;
    [[maybe_unused]] std::uint8_t *aFireLaneC = pWorkSpace->mFireLaneC;
    [[maybe_unused]] std::uint8_t *aFireLaneD = pWorkSpace->mFireLaneD;
    std::uint64_t aCross = 0; std::uint64_t aScatter = 0;

    std::uint64_t aOrbiterA = 0; std::uint64_t aOrbiterB = 0; std::uint64_t aOrbiterC = 0; std::uint64_t aOrbiterD = 0;
    std::uint64_t aOrbiterE = 0; std::uint64_t aOrbiterF = 0; std::uint64_t aOrbiterG = 0; std::uint64_t aOrbiterH = 0;
    std::uint64_t aOrbiterI = 0; std::uint64_t aOrbiterJ = 0; std::uint64_t aOrbiterK = 0;

    // [kdf-a arx]
    std::uint64_t aNonceWordA = TwistMix64::DiffuseB(pNonce * 0xDDBC1A5B16977F1FULL + 0xA8F5B99D70CB7256ULL);
    std::uint64_t aNonceWordB = TwistMix64::DiffuseC(pNonce * 0xFFFD03C7D380DFA1ULL + 0x94FC73AAF9872BC0ULL);
    std::uint64_t aNonceWordC = TwistMix64::DiffuseB(pNonce * 0xC06489320B808C79ULL + 0xF1C464D6E74F2BD1ULL);
    std::uint64_t aNonceWordD = TwistMix64::DiffuseA(pNonce * 0xBE40BB458F5DADFFULL + 0xD5E4E579EB6AD276ULL);
    std::uint64_t aNonceWordE = TwistMix64::DiffuseB(pNonce * 0x852478DA277A32E9ULL + 0x8157199E529495E7ULL);
    std::uint64_t aNonceWordF = TwistMix64::DiffuseA(pNonce * 0x96D0E2B222C71289ULL + 0x9C7522749AB69BAFULL);
    std::uint64_t aNonceWordG = TwistMix64::DiffuseB(pNonce * 0xECBD3679B678E533ULL + 0xBEB26E76B57DB05BULL);
    std::uint64_t aNonceWordH = TwistMix64::DiffuseC(pNonce * 0xB1DE0B13130ECEE7ULL + 0xFDAA84014FF3D8D7ULL);
    std::uint64_t aNonceWordI = TwistMix64::DiffuseC(pNonce * 0xBA3069F7969BF551ULL + 0xC79F0C7EEFCD3899ULL);
    std::uint64_t aNonceWordJ = TwistMix64::DiffuseA(pNonce * 0xFBF80733FD22A421ULL + 0xCB88BC501809AB5AULL);
    std::uint64_t aNonceWordK = TwistMix64::DiffuseB(pNonce * 0xD27CD9A4917C2733ULL + 0x8676B437C971C0B8ULL);
    std::uint64_t aNonceWordL = TwistMix64::DiffuseA(pNonce * 0xBB9EA08B44DD077DULL + 0xF60386D03E10F40AULL);
    std::uint64_t aNonceWordM = TwistMix64::DiffuseA(pNonce * 0xD7A3FC3A6B96679DULL + 0x8857E633E99E3AF5ULL);
    std::uint64_t aNonceWordN = TwistMix64::DiffuseC(pNonce * 0xC631FD452BFF6079ULL + 0x84050F243F7CB755ULL);
    std::uint64_t aNonceWordO = TwistMix64::DiffuseA(pNonce * 0x8EEA1E10759C138DULL + 0xACF7AA3E0CCB02FFULL);
    std::uint64_t aNonceWordP = TwistMix64::DiffuseA(pNonce * 0x961D65CB925858D5ULL + 0xCF7A2DE69BDA5697ULL);
    std::uint64_t aDomainWordIngress = pConstants->mIngress;
    std::uint64_t aDomainWordScatter = pConstants->mScatter;
    std::uint64_t aDomainWordCross = pConstants->mCross;
    [[maybe_unused]] std::uint8_t *mSource = pWorkSpace->mSource;
    std::uint64_t aPrevious = *pPrevious;
    std::uint64_t aIngress = *pIngress;
    std::uint64_t aCarry = *pCarry;
    std::uint64_t aWandererA = *pWandererA;
    std::uint64_t aWandererB = *pWandererB;
    std::uint64_t aWandererC = *pWandererC;
    std::uint64_t aWandererD = *pWandererD;
    std::uint64_t aWandererE = *pWandererE;
    std::uint64_t aWandererF = *pWandererF;
    std::uint64_t aWandererG = *pWandererG;
    std::uint64_t aWandererH = *pWandererH;
    std::uint64_t aWandererI = *pWandererI;
    std::uint64_t aWandererJ = *pWandererJ;
    std::uint64_t aWandererK = *pWandererK;
    // KDF_B_B kdf_b_loop_b (start)
    {
        // KDF_B_B kdf_b_loop_b lane group
        // read from: aExpandLaneA, aExpandLaneB, aWorkLaneA, aExpandLaneC, aExpandLaneD, aFireLaneD, aOperationLaneA, aFireLaneC, aWorkLaneB, aOperationLaneB, aFireLaneA, aWorkLaneD, aOperationLaneC, aWorkLaneC, aFireLaneB
        // write to: aOperationLaneA, aOperationLaneB, aOperationLaneC, aOperationLaneD
    
        // kdf_b_loop_b loop 1
        // ingress from: aExpandLaneA, aExpandLaneB, aWorkLaneA
        // ingress directions: aExpandLaneA forward forced, aExpandLaneB forward forced, aWorkLaneA forward/backward random
        // cross from: aExpandLaneC, aExpandLaneD, aFireLaneD
        // cross directions: aExpandLaneC backward forced, aExpandLaneD backward forced, aFireLaneD backward/forward random
        // write to: aOperationLaneA
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aExpandLaneA[((aIndex + 5654U)) & S_BLOCK1], 5U) ^ RotL64(aExpandLaneB[((aIndex + 2628U)) & S_BLOCK1], 29U));
            aIngress ^= RotL64(aWorkLaneA[((S_BLOCK1 - aIndex + 3413U)) & S_BLOCK1], 39U);
            aIngress = TwistMix64::DiffuseB(((aIngress ^ aDomainWordIngress) ^ aNonceWordE));
            //
            aCross = (RotL64(aExpandLaneC[((S_BLOCK1 - aIndex + 4934U)) & S_BLOCK1], 48U) ^ RotL64(aExpandLaneD[((S_BLOCK1 - aIndex + 5651U)) & S_BLOCK1], 13U));
            aCross ^= RotL64(aFireLaneD[((S_BLOCK1 - aIndex + 2073U)) & S_BLOCK1], 3U);
            aCross = TwistMix64::DiffuseA(((aCross ^ aDomainWordCross) ^ aNonceWordF));
            //
            aScatter = (RotL64(aIngress, 3U) ^ RotL64(aCarry, 52U)) ^ (RotL64(aPrevious, 39U) + RotL64(aCross, 21U));
            aScatter = TwistMix64::DiffuseB(((aScatter ^ aDomainWordScatter) ^ aNonceWordN));
            //
            aOrbiterH = (aWandererC + RotL64(aPrevious, 18U)) + 898812731947995389U;
            aOrbiterG = (((aWandererK + RotL64(aIngress, 21U)) + RotL64(aCarry, 19U)) + 8677347622525527167U) + aOrbiterAssignSaltE[(((31U - aIndex) + 9U)) & S_SALT1];
            aOrbiterF = (((aWandererA + RotL64(aScatter, 43U)) + RotL64(aCarry, 27U)) + 770321564027567654U) + aNonceWordO;
            aOrbiterD = (aWandererH + RotL64(aCross, 5U)) + 11020474858081526395U;
            aOrbiterK = (aWandererF + RotL64(aScatter, 11U)) + 17289793580414993470U;
            aOrbiterI = (aWandererE + RotL64(aPrevious, 35U)) + 10111912559295118444U;
            aOrbiterA = ((aWandererJ + RotL64(aCross, 53U)) + 8083622125544542011U) + aOrbiterAssignSaltD[((aIndex + 10U)) & S_SALT1];
            aOrbiterJ = ((aWandererI + RotL64(aIngress, 29U)) + 7149858558922988240U) + aNonceWordC;
            aOrbiterE = (aWandererG + RotL64(aScatter, 41U)) + 5919683821379905699U;
            aOrbiterC = (((aWandererD + RotL64(aPrevious, 26U)) + RotL64(aCarry, 53U)) + 6860902846079238714U) + aNonceWordP;
            aOrbiterB = (aWandererB + RotL64(aIngress, 57U)) + 15083517836867542075U;
            //
            aOrbiterH = ((aOrbiterH + aOrbiterG) + 14852868368708376381U) + aNonceWordH;
            aOrbiterF = (aOrbiterF ^ aOrbiterH) ^ 9860233289028878323U;
            aOrbiterF = RotL64((aOrbiterF * 13418143547952204667U), 53U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterF) + 772406119079116272U;
            aOrbiterK = ((aOrbiterK ^ aOrbiterD) ^ 7971141501337627589U) ^ aNonceWordD;
            aOrbiterK = RotL64((aOrbiterK * 10168120622976358617U), 11U);
            //
            aOrbiterI = (aOrbiterI + aOrbiterK) + 8478568022896691911U;
            aOrbiterA = (aOrbiterA ^ aOrbiterI) ^ 4027604850785607101U;
            aOrbiterA = RotL64((aOrbiterA * 4826627523578901467U), 51U);
            //
            aOrbiterJ = (aOrbiterJ + aOrbiterE) + 17199331557841535430U;
            aOrbiterG = (aOrbiterG ^ aOrbiterJ) ^ 7515957656979776361U;
            aOrbiterG = RotL64((aOrbiterG * 5468950152869656599U), 41U);
            //
            aOrbiterK = (aOrbiterK + aOrbiterJ) + 17138249294921502391U;
            aOrbiterH = ((aOrbiterH ^ aOrbiterK) ^ 16236812863923234668U) ^ aOrbiterUpdateSaltF[((aIndex + 15U)) & S_SALT1];
            aOrbiterH = RotL64((aOrbiterH * 2925542836624164807U), 29U);
            //
            aOrbiterC = (aOrbiterC + aOrbiterI) + 16941524155859123682U;
            aOrbiterE = ((aOrbiterE ^ aOrbiterC) ^ 11240343728857342866U) ^ aNonceWordN;
            aOrbiterE = RotL64((aOrbiterE * 7281012444214294659U), 43U);
            //
            aOrbiterE = ((aOrbiterE + aOrbiterA) + 15163914964139858328U) + aOrbiterUpdateSaltB[(((31U - aIndex) + 14U)) & S_SALT1];
            aOrbiterB = (aOrbiterB ^ aOrbiterE) ^ 6673576554415729652U;
            aOrbiterB = RotL64((aOrbiterB * 1558880328574736975U), 5U);
            //
            aOrbiterB = (aOrbiterB + aOrbiterD) + 5399050402101642989U;
            aOrbiterI = ((aOrbiterI ^ aOrbiterB) ^ 11806006719060024615U) ^ aOrbiterUpdateSaltA[((aIndex + 29U)) & S_SALT1];
            aOrbiterI = RotL64((aOrbiterI * 15782156615926092159U), 21U);
            //
            aOrbiterG = ((aOrbiterG + aOrbiterB) + 9812148913932011655U) + aOrbiterUpdateSaltD[(((31U - aIndex) + 17U)) & S_SALT1];
            aOrbiterC = (aOrbiterC ^ aOrbiterG) ^ 4737919734590584193U;
            aOrbiterC = RotL64((aOrbiterC * 2739737604370936959U), 3U);
            //
            aOrbiterF = (aOrbiterF + aOrbiterC) + 3415477403346468057U;
            aOrbiterJ = (aOrbiterJ ^ aOrbiterF) ^ 5922725868927615919U;
            aOrbiterJ = RotL64((aOrbiterJ * 12390148483052777871U), 39U);
            //
            aOrbiterA = ((aOrbiterA + aOrbiterH) + 17435294951520465659U) + aNonceWordM;
            aOrbiterD = (aOrbiterD ^ aOrbiterA) ^ 898812731947995389U;
            aOrbiterD = RotL64((aOrbiterD * 17248379279729365007U), 37U);
            //
            aIngress = RotL64(aOrbiterE, 41U) ^ aOrbiterI;
            aIngress = aIngress + (aOrbiterF ^ RotL64(aOrbiterD, 29U));
            aIngress = aIngress + (aOrbiterA ^ RotL64(aOrbiterG, 60U));
            aIngress = aIngress + (aOrbiterC ^ RotL64(aOrbiterH, 5U));
            aIngress = aIngress + (RotL64(aOrbiterJ, 57U) ^ aOrbiterK);
            aIngress = aIngress + RotL64(aOrbiterB, 39U);
            aIngress = TwistMix64::DiffuseA((aIngress + aScatter));
            //
            aWandererE = aWandererE + ((((RotL64(aScatter, 11U) + aOrbiterF) + RotL64(aOrbiterA, 37U)) + RotL64(aCarry, 23U)) + aWandererUpdateSaltE[(((31U - aIndex) + 25U)) & S_SALT1]);
            aWandererG = aWandererG ^ ((RotL64(aCross, 37U) + RotL64(aOrbiterI, 13U)) + aOrbiterA);
            aWandererC = aWandererC + ((((RotL64(aPrevious, 27U) + aOrbiterC) + RotL64(aOrbiterK, 46U)) + aNonceWordA) + aWandererUpdateSaltC[((aIndex + 27U)) & S_SALT1]);
            aWandererF = aWandererF ^ (((RotL64(aIngress, 6U) + RotL64(aOrbiterJ, 41U)) + aOrbiterA) + aNonceWordB);
            aWandererK = aWandererK + ((RotL64(aPrevious, 21U) + aOrbiterC) + RotL64(aOrbiterH, 39U));
            aWandererI = aWandererI ^ ((RotL64(aCross, 51U) + aOrbiterK) + RotL64(aOrbiterF, 5U));
            aWandererA = aWandererA + ((((RotL64(aIngress, 41U) + aOrbiterG) + RotL64(aOrbiterC, 27U)) + RotL64(aCarry, 43U)) + aNonceWordJ);
            aWandererH = aWandererH ^ ((RotL64(aScatter, 47U) + RotL64(aOrbiterI, 57U)) + aOrbiterC);
            aWandererB = aWandererB + ((RotL64(aIngress, 13U) + RotL64(aOrbiterE, 48U)) + aOrbiterK);
            aWandererD = aWandererD ^ ((RotL64(aScatter, 24U) + RotL64(aOrbiterF, 21U)) + aOrbiterD);
            aWandererJ = aWandererJ + ((RotL64(aCross, 19U) + aOrbiterD) + RotL64(aOrbiterB, 19U));
            //
            aCarry = aCarry + (aWandererA ^ RotL64(aWandererK, 36U));
            aCarry = aCarry + (aWandererE ^ RotL64(aWandererG, 51U));
            aCarry = aCarry + (RotL64(aWandererI, 47U) ^ aWandererJ);
            aCarry = aCarry + (RotL64(aWandererH, 23U) ^ aWandererF);
            aCarry = aCarry + (aWandererD ^ RotL64(aWandererB, 53U));
            aCarry = aCarry + RotL64(aWandererC, 21U);
            aCarry = aCarry + RotL64(aIngress, 44U);
            aCarry = TwistMix64::DiffuseC(aCarry);
            //
            aOperationLaneA[aIndex] = aIngress;
        }
    
        // kdf_b_loop_b loop 2
        // ingress from: aOperationLaneA, aExpandLaneC, aFireLaneC
        // ingress directions: aOperationLaneA forward forced, aExpandLaneC forward forced, aFireLaneC forward/backward random
        // cross from: aExpandLaneA, aExpandLaneD, aWorkLaneB
        // cross directions: aExpandLaneA backward forced, aExpandLaneD backward forced, aWorkLaneB backward/forward random
        // write to: aOperationLaneB
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aOperationLaneA[((aIndex + 14335U)) & S_BLOCK1], 13U) ^ RotL64(aExpandLaneC[((aIndex + 14907U)) & S_BLOCK1], 37U));
            aIngress ^= RotL64(aFireLaneC[((aIndex + 11799U)) & S_BLOCK1], 5U);
            aIngress = TwistMix64::DiffuseB(((aIngress ^ aDomainWordIngress) ^ aNonceWordC));
            //
            aCross = (RotL64(aExpandLaneA[((S_BLOCK1 - aIndex + 11855U)) & S_BLOCK1], 14U) ^ RotL64(aExpandLaneD[((S_BLOCK1 - aIndex + 15570U)) & S_BLOCK1], 3U));
            aCross ^= RotL64(aWorkLaneB[((S_BLOCK1 - aIndex + 15223U)) & S_BLOCK1], 23U);
            aCross = TwistMix64::DiffuseC(((aCross ^ aDomainWordCross) ^ aNonceWordI));
            //
            aScatter = (RotL64(aCross, 34U) ^ RotL64(aIngress, 47U)) + (RotL64(aCarry, 19U) + RotL64(aPrevious, 5U));
            aScatter = TwistMix64::DiffuseA(((aScatter ^ aDomainWordScatter) ^ aNonceWordH));
            //
            aOrbiterA = ((aWandererJ + RotL64(aIngress, 3U)) + RotL64(aCarry, 5U)) + 6467297102954816305U;
            aOrbiterB = (aWandererI + RotL64(aScatter, 21U)) + 7921154109831114952U;
            aOrbiterK = (aWandererD + RotL64(aCross, 39U)) + 5701131763215638919U;
            aOrbiterI = (aWandererA + RotL64(aPrevious, 14U)) + 10022999076719002684U;
            aOrbiterF = (aWandererC + RotL64(aIngress, 37U)) + 4367135243038982316U;
            aOrbiterE = ((aWandererF + RotL64(aScatter, 57U)) + 14445846824810383592U) + aNonceWordG;
            aOrbiterC = ((aWandererH + RotL64(aCross, 27U)) + 7683697954545773253U) + aOrbiterAssignSaltB[((aIndex + 29U)) & S_SALT1];
            aOrbiterD = ((aWandererB + RotL64(aPrevious, 35U)) + 17517006750428030899U) + aNonceWordK;
            aOrbiterG = ((aWandererG + RotL64(aCross, 53U)) + 2052484792684025476U) + aNonceWordF;
            aOrbiterJ = (((aWandererE + RotL64(aScatter, 12U)) + RotL64(aCarry, 43U)) + 6279463052085808926U) + aOrbiterAssignSaltC[(((31U - aIndex) + 13U)) & S_SALT1];
            aOrbiterH = ((aWandererK + RotL64(aPrevious, 5U)) + RotL64(aCarry, 51U)) + 679280153651813684U;
            //
            aOrbiterA = (aOrbiterA + aOrbiterB) + 2939516520188460569U;
            aOrbiterK = (aOrbiterK ^ aOrbiterA) ^ 1960616434964712325U;
            aOrbiterK = RotL64((aOrbiterK * 15145998415466343039U), 27U);
            //
            aOrbiterI = ((aOrbiterI + aOrbiterF) + 12273819390719947361U) + aNonceWordE;
            aOrbiterE = (aOrbiterE ^ aOrbiterI) ^ 5685033154709449397U;
            aOrbiterE = RotL64((aOrbiterE * 9845666295874714959U), 21U);
            //
            aOrbiterC = ((aOrbiterC + aOrbiterD) + 9314494172199500653U) + aNonceWordO;
            aOrbiterF = ((aOrbiterF ^ aOrbiterC) ^ 15757631834636427621U) ^ aOrbiterUpdateSaltC[(((31U - aIndex) + 27U)) & S_SALT1];
            aOrbiterF = RotL64((aOrbiterF * 15483543888965744529U), 51U);
            //
            aOrbiterG = (aOrbiterG + aOrbiterA) + 10878078046389399574U;
            aOrbiterD = ((aOrbiterD ^ aOrbiterG) ^ 3583495913766365232U) ^ aOrbiterUpdateSaltB[((aIndex + 19U)) & S_SALT1];
            aOrbiterD = RotL64((aOrbiterD * 2913540984990155225U), 39U);
            //
            aOrbiterJ = (aOrbiterJ + aOrbiterE) + 7385544065754622301U;
            aOrbiterB = (aOrbiterB ^ aOrbiterJ) ^ 16839599460207922881U;
            aOrbiterB = RotL64((aOrbiterB * 240651605910592561U), 29U);
            //
            aOrbiterE = (aOrbiterE + aOrbiterG) + 13038163804940349251U;
            aOrbiterC = (aOrbiterC ^ aOrbiterE) ^ 2587538594933924000U;
            aOrbiterC = RotL64((aOrbiterC * 3091149760401278671U), 3U);
            //
            aOrbiterD = ((aOrbiterD + aOrbiterK) + 13109518583364738004U) + aOrbiterUpdateSaltD[((aIndex + 25U)) & S_SALT1];
            aOrbiterH = (aOrbiterH ^ aOrbiterD) ^ 2447689055742474261U;
            aOrbiterH = RotL64((aOrbiterH * 12100180201235703193U), 41U);
            //
            aOrbiterH = (aOrbiterH + aOrbiterJ) + 5752044906692668618U;
            aOrbiterA = ((aOrbiterA ^ aOrbiterH) ^ 6637725371036522120U) ^ aOrbiterUpdateSaltE[(((31U - aIndex) + 28U)) & S_SALT1];
            aOrbiterA = RotL64((aOrbiterA * 6021986525167161115U), 11U);
            //
            aOrbiterB = (aOrbiterB + aOrbiterC) + 16549229877442298618U;
            aOrbiterI = (aOrbiterI ^ aOrbiterB) ^ 12825651879441561108U;
            aOrbiterI = RotL64((aOrbiterI * 9079931351967033993U), 57U);
            //
            aOrbiterF = (aOrbiterF + aOrbiterH) + 16088338999978085987U;
            aOrbiterG = (aOrbiterG ^ aOrbiterF) ^ 12584648360998154782U;
            aOrbiterG = RotL64((aOrbiterG * 2109996837220975261U), 43U);
            //
            aOrbiterK = (aOrbiterK + aOrbiterI) + 7526256599938771686U;
            aOrbiterJ = (aOrbiterJ ^ aOrbiterK) ^ 6467297102954816305U;
            aOrbiterJ = RotL64((aOrbiterJ * 9289442676936248653U), 13U);
            //
            aIngress = RotL64(aOrbiterK, 42U) ^ aOrbiterE;
            aIngress = aIngress + (aOrbiterG ^ RotL64(aOrbiterA, 23U));
            aIngress = aIngress + (RotL64(aOrbiterC, 29U) ^ aOrbiterI);
            aIngress = aIngress + (aOrbiterJ ^ RotL64(aOrbiterD, 21U));
            aIngress = aIngress + (aOrbiterH ^ RotL64(aOrbiterF, 44U));
            aIngress = aIngress + RotL64(aOrbiterB, 5U);
            aIngress = TwistMix64::DiffuseB((aIngress + aScatter));
            //
            aWandererB = aWandererB + (((RotL64(aCross, 23U) + aOrbiterA) + RotL64(aOrbiterJ, 3U)) + aNonceWordJ);
            aWandererD = aWandererD ^ ((RotL64(aIngress, 53U) + aOrbiterJ) + RotL64(aOrbiterG, 51U));
            aWandererC = aWandererC + ((RotL64(aPrevious, 47U) + aOrbiterK) + RotL64(aOrbiterD, 5U));
            aWandererK = aWandererK ^ (((RotL64(aScatter, 20U) + aOrbiterE) + RotL64(aOrbiterC, 13U)) + aNonceWordB);
            aWandererF = aWandererF + ((RotL64(aPrevious, 5U) + RotL64(aOrbiterJ, 42U)) + aOrbiterF);
            aWandererH = aWandererH ^ ((RotL64(aIngress, 57U) + aOrbiterD) + RotL64(aOrbiterG, 47U));
            aWandererE = aWandererE + (((RotL64(aScatter, 3U) + aOrbiterK) + RotL64(aOrbiterC, 57U)) + aWandererUpdateSaltF[((aIndex + 9U)) & S_SALT1]);
            aWandererJ = aWandererJ ^ (((RotL64(aCross, 51U) + aOrbiterB) + RotL64(aOrbiterE, 37U)) + aNonceWordL);
            aWandererA = aWandererA + ((((RotL64(aIngress, 14U) + aOrbiterH) + RotL64(aOrbiterG, 22U)) + RotL64(aCarry, 51U)) + aWandererUpdateSaltD[(((31U - aIndex) + 22U)) & S_SALT1]);
            aWandererG = aWandererG ^ ((RotL64(aPrevious, 11U) + aOrbiterK) + RotL64(aOrbiterI, 29U));
            aWandererI = aWandererI + (((RotL64(aCross, 39U) + aOrbiterJ) + RotL64(aOrbiterH, 19U)) + RotL64(aCarry, 21U));
            //
            aCarry = aCarry + (RotL64(aWandererA, 36U) ^ aWandererK);
            aCarry = aCarry + (RotL64(aWandererF, 47U) ^ aWandererB);
            aCarry = aCarry + (aWandererC ^ RotL64(aWandererI, 3U));
            aCarry = aCarry + (RotL64(aWandererJ, 11U) ^ aWandererE);
            aCarry = aCarry + (RotL64(aWandererH, 13U) ^ aWandererD);
            aCarry = aCarry + RotL64(aWandererG, 53U);
            aCarry = aCarry + RotL64(aIngress, 50U);
            aCarry = TwistMix64::DiffuseC(aCarry);
            //
            aOperationLaneB[S_BLOCK1 - aIndex] = aIngress;
        }
    
        // kdf_b_loop_b loop 3
        // ingress from: aOperationLaneB, aExpandLaneD, aFireLaneA
        // ingress directions: aOperationLaneB forward forced, aExpandLaneD forward forced, aFireLaneA forward/backward random
        // cross from: aOperationLaneA, aExpandLaneB, aWorkLaneD
        // cross directions: aOperationLaneA backward forced, aExpandLaneB backward forced, aWorkLaneD backward/forward random
        // write to: aOperationLaneC
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aOperationLaneB[((aIndex + 24510U)) & S_BLOCK1], 3U) ^ RotL64(aExpandLaneD[((aIndex + 17194U)) & S_BLOCK1], 12U));
            aIngress ^= RotL64(aFireLaneA[((aIndex + 21023U)) & S_BLOCK1], 21U);
            aIngress = TwistMix64::DiffuseC(((aIngress ^ aDomainWordIngress) ^ aNonceWordB));
            //
            aCross = (RotL64(aOperationLaneA[((S_BLOCK1 - aIndex + 24476U)) & S_BLOCK1], 11U) ^ RotL64(aExpandLaneB[((S_BLOCK1 - aIndex + 19281U)) & S_BLOCK1], 60U));
            aCross ^= RotL64(aWorkLaneD[((aIndex + 20245U)) & S_BLOCK1], 39U);
            aCross = TwistMix64::DiffuseC(((aCross ^ aDomainWordCross) ^ aNonceWordF));
            //
            aScatter = (RotL64(aCross, 39U) + RotL64(aIngress, 56U)) ^ (RotL64(aCarry, 5U) ^ RotL64(aPrevious, 23U));
            aScatter = TwistMix64::DiffuseB(((aScatter ^ aDomainWordScatter) ^ aNonceWordK));
            //
            aOrbiterF = ((aWandererE + RotL64(aPrevious, 38U)) + RotL64(aCarry, 11U)) + 9041099828460168106U;
            aOrbiterD = ((aWandererK + RotL64(aIngress, 47U)) + RotL64(aCarry, 57U)) + 12883711604096848454U;
            aOrbiterH = (aWandererG + RotL64(aCross, 27U)) + 17420968786226443079U;
            aOrbiterI = (aWandererD + RotL64(aScatter, 19U)) + 3448213891716125104U;
            aOrbiterG = (aWandererC + RotL64(aCross, 56U)) + 11866455977445336560U;
            aOrbiterE = (((aWandererB + RotL64(aPrevious, 21U)) + 4119356835384495905U) + aOrbiterAssignSaltF[(((31U - aIndex) + 4U)) & S_SALT1]) + aNonceWordD;
            aOrbiterC = (aWandererI + RotL64(aIngress, 3U)) + 2186212599698637068U;
            aOrbiterJ = ((((aWandererH + RotL64(aScatter, 35U)) + RotL64(aCarry, 27U)) + 6506144898969301620U) + aOrbiterAssignSaltA[(((31U - aIndex) + 28U)) & S_SALT1]) + aNonceWordP;
            aOrbiterK = ((aWandererA + RotL64(aCross, 53U)) + 12556800923644051626U) + aNonceWordM;
            aOrbiterB = (aWandererJ + RotL64(aIngress, 41U)) + 4075551535185182945U;
            aOrbiterA = ((aWandererF + RotL64(aScatter, 5U)) + 17877694808492008749U) + aNonceWordA;
            //
            aOrbiterF = (aOrbiterF + aOrbiterD) + 5553428900598223316U;
            aOrbiterH = (aOrbiterH ^ aOrbiterF) ^ 14362304852277160675U;
            aOrbiterH = RotL64((aOrbiterH * 11415103199856419303U), 11U);
            //
            aOrbiterI = (aOrbiterI + aOrbiterG) + 9174200302876075831U;
            aOrbiterE = ((aOrbiterE ^ aOrbiterI) ^ 16110739511917638547U) ^ aNonceWordL;
            aOrbiterE = RotL64((aOrbiterE * 7004356839428657949U), 23U);
            //
            aOrbiterE = ((aOrbiterE + aOrbiterF) + 10189881974519849402U) + aNonceWordO;
            aOrbiterC = (aOrbiterC ^ aOrbiterE) ^ 2128076632642616677U;
            aOrbiterC = RotL64((aOrbiterC * 8860453653433114929U), 39U);
            //
            aOrbiterJ = (((aOrbiterJ + aOrbiterI) + 18133523799074400083U) + aOrbiterUpdateSaltB[(((31U - aIndex) + 19U)) & S_SALT1]) + aNonceWordN;
            aOrbiterK = (aOrbiterK ^ aOrbiterJ) ^ 9916472958834153766U;
            aOrbiterK = RotL64((aOrbiterK * 3454601168808001733U), 21U);
            //
            aOrbiterB = (aOrbiterB + aOrbiterK) + 10274457562795569227U;
            aOrbiterG = (aOrbiterG ^ aOrbiterB) ^ 14134814273275356425U;
            aOrbiterG = RotL64((aOrbiterG * 15912501063665343159U), 29U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterJ) + 6394306369514735480U;
            aOrbiterB = ((aOrbiterB ^ aOrbiterD) ^ 4825761192736485643U) ^ aOrbiterUpdateSaltE[((aIndex + 16U)) & S_SALT1];
            aOrbiterB = RotL64((aOrbiterB * 12534544147331805643U), 51U);
            //
            aOrbiterH = (aOrbiterH + aOrbiterB) + 5672807934779206275U;
            aOrbiterI = ((aOrbiterI ^ aOrbiterH) ^ 3881953574159390421U) ^ aNonceWordH;
            aOrbiterI = RotL64((aOrbiterI * 7448770570912161095U), 5U);
            //
            aOrbiterG = (aOrbiterG + aOrbiterA) + 12012232712634303203U;
            aOrbiterF = (aOrbiterF ^ aOrbiterG) ^ 14176392925893052596U;
            aOrbiterF = RotL64((aOrbiterF * 11288668529893084583U), 27U);
            //
            aOrbiterC = (aOrbiterC + aOrbiterH) + 307148402076391033U;
            aOrbiterJ = ((aOrbiterJ ^ aOrbiterC) ^ 15380446373458263079U) ^ aOrbiterUpdateSaltF[(((31U - aIndex) + 7U)) & S_SALT1];
            aOrbiterJ = RotL64((aOrbiterJ * 15228462337097647933U), 13U);
            //
            aOrbiterK = ((aOrbiterK + aOrbiterE) + 4654312690816676129U) + aOrbiterUpdateSaltD[((aIndex + 9U)) & S_SALT1];
            aOrbiterA = (aOrbiterA ^ aOrbiterK) ^ 10818029316701301859U;
            aOrbiterA = RotL64((aOrbiterA * 16245734506125913215U), 3U);
            //
            aOrbiterA = (aOrbiterA + aOrbiterC) + 7340370713289840635U;
            aOrbiterD = (aOrbiterD ^ aOrbiterA) ^ 9041099828460168106U;
            aOrbiterD = RotL64((aOrbiterD * 1807356802142268373U), 57U);
            //
            aIngress = aOrbiterF ^ RotL64(aOrbiterC, 39U);
            aIngress = aIngress + (RotL64(aOrbiterD, 47U) ^ aOrbiterI);
            aIngress = aIngress + (RotL64(aOrbiterK, 21U) ^ aOrbiterE);
            aIngress = aIngress + (RotL64(aOrbiterG, 11U) ^ aOrbiterH);
            aIngress = aIngress + (aOrbiterB ^ RotL64(aOrbiterA, 6U));
            aIngress = aIngress + RotL64(aOrbiterJ, 13U);
            aIngress = TwistMix64::DiffuseC((aIngress + aScatter));
            //
            aWandererD = aWandererD + (((RotL64(aPrevious, 53U) + aOrbiterJ) + RotL64(aOrbiterD, 3U)) + RotL64(aCarry, 53U));
            aWandererG = aWandererG ^ (((RotL64(aCross, 3U) + RotL64(aOrbiterE, 5U)) + aOrbiterK) + aNonceWordC);
            aWandererA = aWandererA + (((RotL64(aScatter, 42U) + RotL64(aOrbiterF, 18U)) + aOrbiterC) + aNonceWordJ);
            aWandererJ = aWandererJ ^ ((((RotL64(aIngress, 51U) + RotL64(aOrbiterI, 47U)) + aOrbiterG) + aNonceWordI) + aWandererUpdateSaltB[(((31U - aIndex) + 13U)) & S_SALT1]);
            aWandererE = aWandererE + ((RotL64(aCross, 37U) + aOrbiterC) + RotL64(aOrbiterK, 43U));
            aWandererB = aWandererB ^ ((RotL64(aIngress, 23U) + RotL64(aOrbiterI, 51U)) + aOrbiterH);
            aWandererF = aWandererF + (((RotL64(aPrevious, 6U) + aOrbiterI) + RotL64(aOrbiterJ, 35U)) + aNonceWordE);
            aWandererI = aWandererI ^ ((RotL64(aScatter, 13U) + RotL64(aOrbiterH, 39U)) + aOrbiterB);
            aWandererC = aWandererC + (((RotL64(aCross, 47U) + RotL64(aOrbiterI, 37U)) + aOrbiterA) + RotL64(aCarry, 29U));
            aWandererK = aWandererK ^ (((RotL64(aScatter, 57U) + aOrbiterJ) + RotL64(aOrbiterG, 21U)) + aWandererUpdateSaltA[(((31U - aIndex) + 26U)) & S_SALT1]);
            aWandererH = aWandererH + ((RotL64(aIngress, 39U) + aOrbiterE) + RotL64(aOrbiterD, 56U));
            //
            aCarry = aCarry + (aWandererK ^ RotL64(aWandererG, 56U));
            aCarry = aCarry + (RotL64(aWandererB, 3U) ^ aWandererJ);
            aCarry = aCarry + (RotL64(aWandererI, 21U) ^ aWandererA);
            aCarry = aCarry + (aWandererD ^ RotL64(aWandererE, 37U));
            aCarry = aCarry + (aWandererH ^ RotL64(aWandererF, 24U));
            aCarry = aCarry + RotL64(aWandererC, 29U);
            aCarry = aCarry + RotL64(aIngress, 53U);
            aCarry = TwistMix64::DiffuseA(aCarry);
            //
            aOperationLaneC[aIndex] = aIngress;
        }
    
        // kdf_b_loop_b loop 4
        // ingress from: aOperationLaneC, aOperationLaneA, aWorkLaneC
        // ingress directions: aOperationLaneC forward forced, aOperationLaneA forward forced, aWorkLaneC forward/backward random
        // cross from: aOperationLaneB, aExpandLaneC, aFireLaneB
        // cross directions: aOperationLaneB backward forced, aExpandLaneC backward forced, aFireLaneB backward/forward random
        // write to: aOperationLaneD
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aOperationLaneC[((aIndex + 26871U)) & S_BLOCK1], 38U) ^ RotL64(aOperationLaneA[((aIndex + 30620U)) & S_BLOCK1], 5U));
            aIngress ^= RotL64(aWorkLaneC[((S_BLOCK1 - aIndex + 27700U)) & S_BLOCK1], 29U);
            aIngress = TwistMix64::DiffuseA(((aIngress ^ aDomainWordIngress) ^ aNonceWordI));
            //
            aCross = (RotL64(aOperationLaneB[((S_BLOCK1 - aIndex + 32732U)) & S_BLOCK1], 57U) ^ RotL64(aExpandLaneC[((S_BLOCK1 - aIndex + 29673U)) & S_BLOCK1], 23U));
            aCross ^= RotL64(aFireLaneB[((aIndex + 32729U)) & S_BLOCK1], 6U);
            aCross = TwistMix64::DiffuseC(((aCross ^ aDomainWordCross) ^ aNonceWordA));
            //
            aScatter = (RotL64(aPrevious, 37U) + RotL64(aCross, 11U)) ^ (RotL64(aCarry, 23U) ^ RotL64(aIngress, 58U));
            aScatter = TwistMix64::DiffuseA(((aScatter ^ aDomainWordScatter) ^ aNonceWordC));
            //
            aOrbiterD = (aWandererC + RotL64(aScatter, 58U)) + 3105313968748067810U;
            aOrbiterG = (aWandererA + RotL64(aCross, 29U)) + 9977249451119627064U;
            aOrbiterE = (aWandererJ + RotL64(aIngress, 39U)) + 17941392803495349366U;
            aOrbiterA = (aWandererE + RotL64(aPrevious, 27U)) + 4279533326705471133U;
            aOrbiterK = (((aWandererB + RotL64(aScatter, 37U)) + RotL64(aCarry, 37U)) + 13983828966811580039U) + aNonceWordD;
            aOrbiterJ = ((aWandererF + RotL64(aPrevious, 19U)) + 3983490984234810378U) + aNonceWordG;
            aOrbiterI = ((((aWandererG + RotL64(aIngress, 5U)) + RotL64(aCarry, 57U)) + 308786542215259956U) + aOrbiterAssignSaltD[(((31U - aIndex) + 25U)) & S_SALT1]) + aNonceWordJ;
            aOrbiterH = ((aWandererH + RotL64(aCross, 41U)) + 8443607695364427037U) + aNonceWordH;
            aOrbiterF = ((aWandererI + RotL64(aPrevious, 53U)) + RotL64(aCarry, 43U)) + 14939626441464340668U;
            aOrbiterB = ((aWandererD + RotL64(aCross, 43U)) + 9350693577306121110U) + aOrbiterAssignSaltE[(((31U - aIndex) + 12U)) & S_SALT1];
            aOrbiterC = (aWandererK + RotL64(aScatter, 48U)) + 1717071159396961752U;
            //
            aOrbiterD = (aOrbiterD + aOrbiterG) + 15911765265202100610U;
            aOrbiterE = (aOrbiterE ^ aOrbiterD) ^ 14898546272333182767U;
            aOrbiterE = RotL64((aOrbiterE * 2674900543810733067U), 21U);
            //
            aOrbiterE = (aOrbiterE + aOrbiterA) + 3560903518513465868U;
            aOrbiterK = (aOrbiterK ^ aOrbiterE) ^ 5367062725726860234U;
            aOrbiterK = RotL64((aOrbiterK * 8521908836601319553U), 51U);
            //
            aOrbiterG = (aOrbiterG + aOrbiterJ) + 15233321480618877327U;
            aOrbiterA = (aOrbiterA ^ aOrbiterG) ^ 9288449812290126074U;
            aOrbiterA = RotL64((aOrbiterA * 6815298520404038519U), 29U);
            //
            aOrbiterI = ((aOrbiterI + aOrbiterK) + 5504840529511585676U) + aNonceWordP;
            aOrbiterH = (aOrbiterH ^ aOrbiterI) ^ 6825598386801620046U;
            aOrbiterH = RotL64((aOrbiterH * 11666542445846250077U), 11U);
            //
            aOrbiterF = (aOrbiterF + aOrbiterD) + 6433024450721339470U;
            aOrbiterJ = (aOrbiterJ ^ aOrbiterF) ^ 97934156644929458U;
            aOrbiterJ = RotL64((aOrbiterJ * 8630530773006923215U), 27U);
            //
            aOrbiterB = ((aOrbiterB + aOrbiterH) + 3260053604798744515U) + aOrbiterUpdateSaltF[(((31U - aIndex) + 5U)) & S_SALT1];
            aOrbiterF = (((aOrbiterF ^ aOrbiterB) ^ 16539416623243059076U) ^ aOrbiterUpdateSaltA[((aIndex + 11U)) & S_SALT1]) ^ aNonceWordO;
            aOrbiterF = RotL64((aOrbiterF * 12199577351166064503U), 57U);
            //
            aOrbiterK = (aOrbiterK + aOrbiterB) + 9814290051339038920U;
            aOrbiterC = ((aOrbiterC ^ aOrbiterK) ^ 13280156404507444041U) ^ aOrbiterUpdateSaltC[((aIndex + 18U)) & S_SALT1];
            aOrbiterC = RotL64((aOrbiterC * 15269010043398910061U), 37U);
            //
            aOrbiterC = (aOrbiterC + aOrbiterF) + 11853942590993546833U;
            aOrbiterG = ((aOrbiterG ^ aOrbiterC) ^ 13207869904312989977U) ^ aNonceWordC;
            aOrbiterG = RotL64((aOrbiterG * 15503461937625795969U), 13U);
            //
            aOrbiterJ = ((aOrbiterJ + aOrbiterE) + 14536032167989376750U) + aOrbiterUpdateSaltB[(((31U - aIndex) + 15U)) & S_SALT1];
            aOrbiterI = (aOrbiterI ^ aOrbiterJ) ^ 3693282775047432356U;
            aOrbiterI = RotL64((aOrbiterI * 5290349323647887877U), 35U);
            //
            aOrbiterH = (aOrbiterH + aOrbiterC) + 5803176485246280271U;
            aOrbiterD = ((aOrbiterD ^ aOrbiterH) ^ 16702526675475954730U) ^ aNonceWordF;
            aOrbiterD = RotL64((aOrbiterD * 13695676754973145769U), 53U);
            //
            aOrbiterA = (aOrbiterA + aOrbiterI) + 16454171963808313625U;
            aOrbiterB = (aOrbiterB ^ aOrbiterA) ^ 3105313968748067810U;
            aOrbiterB = RotL64((aOrbiterB * 16572687178789102843U), 19U);
            //
            aIngress = RotL64(aOrbiterJ, 11U) ^ aOrbiterH;
            aIngress = aIngress + (aOrbiterA ^ RotL64(aOrbiterG, 6U));
            aIngress = aIngress + (aOrbiterC ^ RotL64(aOrbiterB, 13U));
            aIngress = aIngress + (aOrbiterD ^ RotL64(aOrbiterI, 3U));
            aIngress = aIngress + (aOrbiterK ^ RotL64(aOrbiterE, 47U));
            aIngress = aIngress + RotL64(aOrbiterF, 27U);
            aIngress = TwistMix64::DiffuseC((aIngress + aScatter));
            //
            aWandererG = aWandererG ^ (((RotL64(aIngress, 19U) + RotL64(aOrbiterK, 48U)) + aOrbiterG) + aWandererUpdateSaltC[((aIndex + 13U)) & S_SALT1]);
            aWandererC = aWandererC + (((RotL64(aScatter, 23U) + aOrbiterI) + RotL64(aOrbiterA, 41U)) + aNonceWordE);
            aWandererJ = aWandererJ ^ (((RotL64(aPrevious, 21U) + RotL64(aOrbiterK, 3U)) + aOrbiterJ) + aNonceWordM);
            aWandererD = aWandererD + (((RotL64(aCross, 3U) + aOrbiterH) + RotL64(aOrbiterB, 57U)) + RotL64(aCarry, 41U));
            aWandererA = aWandererA ^ ((RotL64(aScatter, 53U) + aOrbiterE) + RotL64(aOrbiterJ, 23U));
            aWandererH = aWandererH + ((((RotL64(aPrevious, 57U) + aOrbiterB) + RotL64(aOrbiterF, 53U)) + aNonceWordN) + aWandererUpdateSaltE[(((31U - aIndex) + 20U)) & S_SALT1]);
            aWandererI = aWandererI ^ ((RotL64(aCross, 44U) + RotL64(aOrbiterF, 13U)) + aOrbiterE);
            aWandererE = aWandererE + (((RotL64(aIngress, 47U) + aOrbiterG) + RotL64(aOrbiterI, 19U)) + RotL64(aCarry, 51U));
            aWandererB = aWandererB ^ (((RotL64(aScatter, 51U) + aOrbiterJ) + RotL64(aOrbiterD, 34U)) + aNonceWordL);
            aWandererK = aWandererK + ((RotL64(aPrevious, 11U) + RotL64(aOrbiterF, 5U)) + aOrbiterJ);
            aWandererF = aWandererF ^ ((RotL64(aCross, 6U) + RotL64(aOrbiterC, 39U)) + aOrbiterJ);
            //
            aCarry = aCarry + (aWandererE ^ RotL64(aWandererC, 30U));
            aCarry = aCarry + (RotL64(aWandererI, 23U) ^ aWandererD);
            aCarry = aCarry + (RotL64(aWandererH, 37U) ^ aWandererK);
            aCarry = aCarry + (RotL64(aWandererB, 43U) ^ aWandererF);
            aCarry = aCarry + (aWandererA ^ RotL64(aWandererG, 10U));
            aCarry = aCarry + RotL64(aWandererJ, 19U);
            aCarry = aCarry + RotL64(aIngress, 51U);
            aCarry = TwistMix64::DiffuseC(aCarry);
            //
            aOperationLaneD[S_BLOCK1 - aIndex] = aIngress;
        }
    }
    // KDF_B_B kdf_b_loop_b (end)
    *pPrevious = aPrevious;
    *pIngress = aIngress;
    *pCarry = aCarry;
    *pWandererA = aWandererA;
    *pWandererB = aWandererB;
    *pWandererC = aWandererC;
    *pWandererD = aWandererD;
    *pWandererE = aWandererE;
    *pWandererF = aWandererF;
    *pWandererG = aWandererG;
    *pWandererH = aWandererH;
    *pWandererI = aWandererI;
    *pWandererJ = aWandererJ;
    *pWandererK = aWandererK;
}

void TwistExpander_Exercea_Arx::KDF_B_C(TwistWorkSpace *pWorkSpace,
                     std::uint64_t pNonce,
                     TwistDomainConstants *pConstants,
                     TwistDomainSaltSet *pDomainSaltSet,
                     std::uint64_t *pPrevious,
                     std::uint64_t *pIngress,
                     std::uint64_t *pCarry,
                     std::uint64_t *pWandererA,
                     std::uint64_t *pWandererB,
                     std::uint64_t *pWandererC,
                     std::uint64_t *pWandererD,
                     std::uint64_t *pWandererE,
                     std::uint64_t *pWandererF,
                     std::uint64_t *pWandererG,
                     std::uint64_t *pWandererH,
                     std::uint64_t *pWandererI,
                     std::uint64_t *pWandererJ,
                     std::uint64_t *pWandererK) {
    [[maybe_unused]] std::uint64_t *aOrbiterAssignSaltA = pDomainSaltSet->mOrbiterAssign.mSaltA;
    [[maybe_unused]] std::uint64_t *aOrbiterAssignSaltB = pDomainSaltSet->mOrbiterAssign.mSaltB;
    [[maybe_unused]] std::uint64_t *aOrbiterAssignSaltC = pDomainSaltSet->mOrbiterAssign.mSaltC;
    [[maybe_unused]] std::uint64_t *aOrbiterAssignSaltD = pDomainSaltSet->mOrbiterAssign.mSaltD;
    [[maybe_unused]] std::uint64_t *aOrbiterAssignSaltE = pDomainSaltSet->mOrbiterAssign.mSaltE;
    [[maybe_unused]] std::uint64_t *aOrbiterAssignSaltF = pDomainSaltSet->mOrbiterAssign.mSaltF;
    [[maybe_unused]] std::uint64_t *aOrbiterUpdateSaltA = pDomainSaltSet->mOrbiterUpdate.mSaltA;
    [[maybe_unused]] std::uint64_t *aOrbiterUpdateSaltB = pDomainSaltSet->mOrbiterUpdate.mSaltB;
    [[maybe_unused]] std::uint64_t *aOrbiterUpdateSaltC = pDomainSaltSet->mOrbiterUpdate.mSaltC;
    [[maybe_unused]] std::uint64_t *aOrbiterUpdateSaltD = pDomainSaltSet->mOrbiterUpdate.mSaltD;
    [[maybe_unused]] std::uint64_t *aOrbiterUpdateSaltE = pDomainSaltSet->mOrbiterUpdate.mSaltE;
    [[maybe_unused]] std::uint64_t *aOrbiterUpdateSaltF = pDomainSaltSet->mOrbiterUpdate.mSaltF;
    [[maybe_unused]] std::uint64_t *aWandererUpdateSaltA = pDomainSaltSet->mWandererUpdate.mSaltA;
    [[maybe_unused]] std::uint64_t *aWandererUpdateSaltB = pDomainSaltSet->mWandererUpdate.mSaltB;
    [[maybe_unused]] std::uint64_t *aWandererUpdateSaltC = pDomainSaltSet->mWandererUpdate.mSaltC;
    [[maybe_unused]] std::uint64_t *aWandererUpdateSaltD = pDomainSaltSet->mWandererUpdate.mSaltD;
    [[maybe_unused]] std::uint64_t *aWandererUpdateSaltE = pDomainSaltSet->mWandererUpdate.mSaltE;
    [[maybe_unused]] std::uint64_t *aWandererUpdateSaltF = pDomainSaltSet->mWandererUpdate.mSaltF;
    [[maybe_unused]] std::uint8_t *aExpandLaneA = pWorkSpace->mExpansionLaneA;
    [[maybe_unused]] std::uint8_t *aExpandLaneB = pWorkSpace->mExpansionLaneB;
    [[maybe_unused]] std::uint8_t *aExpandLaneC = pWorkSpace->mExpansionLaneC;
    [[maybe_unused]] std::uint8_t *aExpandLaneD = pWorkSpace->mExpansionLaneD;
    [[maybe_unused]] std::uint8_t *aWorkLaneA = pWorkSpace->mWorkLaneA;
    [[maybe_unused]] std::uint8_t *aWorkLaneB = pWorkSpace->mWorkLaneB;
    [[maybe_unused]] std::uint8_t *aWorkLaneC = pWorkSpace->mWorkLaneC;
    [[maybe_unused]] std::uint8_t *aWorkLaneD = pWorkSpace->mWorkLaneD;
    [[maybe_unused]] std::uint8_t *aOperationLaneA = pWorkSpace->mOperationLaneA;
    [[maybe_unused]] std::uint8_t *aOperationLaneB = pWorkSpace->mOperationLaneB;
    [[maybe_unused]] std::uint8_t *aOperationLaneC = pWorkSpace->mOperationLaneC;
    [[maybe_unused]] std::uint8_t *aOperationLaneD = pWorkSpace->mOperationLaneD;
    [[maybe_unused]] std::uint8_t *aFireLaneA = pWorkSpace->mFireLaneA;
    [[maybe_unused]] std::uint8_t *aFireLaneB = pWorkSpace->mFireLaneB;
    [[maybe_unused]] std::uint8_t *aFireLaneC = pWorkSpace->mFireLaneC;
    [[maybe_unused]] std::uint8_t *aFireLaneD = pWorkSpace->mFireLaneD;
    std::uint64_t aCross = 0; std::uint64_t aScatter = 0;

    std::uint64_t aOrbiterA = 0; std::uint64_t aOrbiterB = 0; std::uint64_t aOrbiterC = 0; std::uint64_t aOrbiterD = 0;
    std::uint64_t aOrbiterE = 0; std::uint64_t aOrbiterF = 0; std::uint64_t aOrbiterG = 0; std::uint64_t aOrbiterH = 0;
    std::uint64_t aOrbiterI = 0; std::uint64_t aOrbiterJ = 0; std::uint64_t aOrbiterK = 0;

    // [kdf-a arx]
    std::uint64_t aNonceWordA = TwistMix64::DiffuseA(pNonce * 0xBFF3D2D1B8810C09ULL + 0x9ABF76F89AFF59AEULL);
    std::uint64_t aNonceWordB = TwistMix64::DiffuseA(pNonce * 0xDB2D6965038BA3FDULL + 0xD5DB70263A9536CBULL);
    std::uint64_t aNonceWordC = TwistMix64::DiffuseA(pNonce * 0xA6C5ACB128C98993ULL + 0x8A2FD077DEA09FA7ULL);
    std::uint64_t aNonceWordD = TwistMix64::DiffuseA(pNonce * 0xD25210B06C93C735ULL + 0x928FABBB8A579049ULL);
    std::uint64_t aNonceWordE = TwistMix64::DiffuseA(pNonce * 0xA6DC50947B0C8131ULL + 0x8D1A6CB060F2B0C7ULL);
    std::uint64_t aNonceWordF = TwistMix64::DiffuseC(pNonce * 0x8ED2D3185794AECDULL + 0xD1B3050F3EDE08B2ULL);
    std::uint64_t aNonceWordG = TwistMix64::DiffuseA(pNonce * 0x841F295D2FA295AFULL + 0x89CBDD80E4CA3FE2ULL);
    std::uint64_t aNonceWordH = TwistMix64::DiffuseA(pNonce * 0xA1C908BFCD82C78BULL + 0xD0F283908C649E39ULL);
    std::uint64_t aNonceWordI = TwistMix64::DiffuseB(pNonce * 0x9D2890E6A1B33C95ULL + 0xC3AC6E50CC92267AULL);
    std::uint64_t aNonceWordJ = TwistMix64::DiffuseC(pNonce * 0xEF8412A8AC373563ULL + 0xD22EC01E321A40A1ULL);
    std::uint64_t aNonceWordK = TwistMix64::DiffuseA(pNonce * 0xBEC7B6635CA1B017ULL + 0xFE42F79FFB7195B2ULL);
    std::uint64_t aNonceWordL = TwistMix64::DiffuseA(pNonce * 0xF25E49C1FED48ACFULL + 0xB81F333CAE531ADDULL);
    std::uint64_t aNonceWordM = TwistMix64::DiffuseA(pNonce * 0xD1A22FB2B94A45DBULL + 0xB972D809C978CE5BULL);
    std::uint64_t aNonceWordN = TwistMix64::DiffuseA(pNonce * 0xA3270364DCFB2FF9ULL + 0xE36BBE90BB113B39ULL);
    std::uint64_t aNonceWordO = TwistMix64::DiffuseB(pNonce * 0xA7B99F51C368695FULL + 0x8BF958F3F5A3CB7DULL);
    std::uint64_t aNonceWordP = TwistMix64::DiffuseC(pNonce * 0xA8E196B18EA050D7ULL + 0xEF54C5B42DA31517ULL);
    std::uint64_t aDomainWordIngress = pConstants->mIngress;
    std::uint64_t aDomainWordScatter = pConstants->mScatter;
    std::uint64_t aDomainWordCross = pConstants->mCross;
    [[maybe_unused]] std::uint8_t *mSource = pWorkSpace->mSource;
    std::uint64_t aPrevious = *pPrevious;
    std::uint64_t aIngress = *pIngress;
    std::uint64_t aCarry = *pCarry;
    std::uint64_t aWandererA = *pWandererA;
    std::uint64_t aWandererB = *pWandererB;
    std::uint64_t aWandererC = *pWandererC;
    std::uint64_t aWandererD = *pWandererD;
    std::uint64_t aWandererE = *pWandererE;
    std::uint64_t aWandererF = *pWandererF;
    std::uint64_t aWandererG = *pWandererG;
    std::uint64_t aWandererH = *pWandererH;
    std::uint64_t aWandererI = *pWandererI;
    std::uint64_t aWandererJ = *pWandererJ;
    std::uint64_t aWandererK = *pWandererK;
    // KDF_B_C kdf_b_loop_c (start)
    {
        // KDF_B_C kdf_b_loop_c lane group
        // read from: aOperationLaneA, aOperationLaneB, aFireLaneA, aOperationLaneC, aOperationLaneD, aWorkLaneD, aExpandLaneA, aFireLaneD, aWorkLaneA, aExpandLaneB, aFireLaneB, aWorkLaneB, aExpandLaneC, aFireLaneC, aWorkLaneC
        // write to: aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD
    
        // kdf_b_loop_c loop 1
        // ingress from: aOperationLaneA, aOperationLaneB, aFireLaneA
        // ingress directions: aOperationLaneA forward forced, aOperationLaneB forward forced, aFireLaneA forward/backward random
        // cross from: aOperationLaneC, aOperationLaneD, aWorkLaneD
        // cross directions: aOperationLaneC backward forced, aOperationLaneD backward forced, aWorkLaneD backward/forward random
        // write to: aExpandLaneA
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aOperationLaneA[((aIndex + 5140U)) & S_BLOCK1], 6U) ^ RotL64(aOperationLaneB[((aIndex + 1480U)) & S_BLOCK1], 57U));
            aIngress ^= RotL64(aFireLaneA[((S_BLOCK1 - aIndex + 260U)) & S_BLOCK1], 27U);
            aIngress = TwistMix64::DiffuseA(((aIngress ^ aDomainWordIngress) ^ aNonceWordN));
            //
            aCross = (RotL64(aOperationLaneC[((S_BLOCK1 - aIndex + 7441U)) & S_BLOCK1], 35U) ^ RotL64(aOperationLaneD[((S_BLOCK1 - aIndex + 6623U)) & S_BLOCK1], 18U));
            aCross ^= RotL64(aWorkLaneD[((S_BLOCK1 - aIndex + 7629U)) & S_BLOCK1], 27U);
            aCross = TwistMix64::DiffuseA(((aCross ^ aDomainWordCross) ^ aNonceWordL));
            //
            aScatter = (RotL64(aPrevious, 23U) ^ RotL64(aCarry, 39U)) ^ (RotL64(aIngress, 6U) + RotL64(aCross, 57U));
            aScatter = TwistMix64::DiffuseC(((aScatter ^ aDomainWordScatter) ^ aNonceWordN));
            //
            aOrbiterH = (((aWandererA + RotL64(aCross, 19U)) + RotL64(aCarry, 51U)) + 2225397913940961213U) + aNonceWordD;
            aOrbiterD = ((aWandererE + RotL64(aIngress, 47U)) + 8342544893601343643U) + aOrbiterAssignSaltE[(((31U - aIndex) + 10U)) & S_SALT1];
            aOrbiterC = (aWandererI + RotL64(aScatter, 10U)) + 162922186381417187U;
            aOrbiterA = (((aWandererK + RotL64(aPrevious, 39U)) + RotL64(aCarry, 5U)) + 11660218373710972210U) + aNonceWordB;
            aOrbiterE = ((aWandererB + RotL64(aIngress, 29U)) + 14909034764605802354U) + aNonceWordI;
            aOrbiterJ = ((aWandererJ + RotL64(aPrevious, 57U)) + 16776955237009701511U) + aOrbiterAssignSaltB[((aIndex + 17U)) & S_SALT1];
            aOrbiterF = (aWandererG + RotL64(aCross, 51U)) + 5834487809188925253U;
            aOrbiterK = ((aWandererD + RotL64(aScatter, 24U)) + RotL64(aCarry, 37U)) + 1498492772767040320U;
            aOrbiterI = (aWandererF + RotL64(aPrevious, 35U)) + 4161765458781579617U;
            //
            aOrbiterH = (aOrbiterH + aOrbiterD) + 10511923076962447765U;
            aOrbiterC = ((aOrbiterC ^ aOrbiterH) ^ 8575954471692620021U) ^ aOrbiterUpdateSaltF[(((31U - aIndex) + 14U)) & S_SALT1];
            aOrbiterC = RotL64((aOrbiterC * 12526744988828982731U), 51U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterA) + 6536325446331340573U;
            aOrbiterE = (aOrbiterE ^ aOrbiterD) ^ 1790628986900286346U;
            aOrbiterE = RotL64((aOrbiterE * 5262997114200816715U), 27U);
            //
            aOrbiterA = (aOrbiterA + aOrbiterH) + 2623814807619278590U;
            aOrbiterJ = ((aOrbiterJ ^ aOrbiterA) ^ 11676970995834706612U) ^ aOrbiterUpdateSaltB[((aIndex + 20U)) & S_SALT1];
            aOrbiterJ = RotL64((aOrbiterJ * 10057461115132434901U), 57U);
            //
            aOrbiterF = ((aOrbiterF + aOrbiterK) + 13836786354224256591U) + aOrbiterUpdateSaltD[((aIndex + 7U)) & S_SALT1];
            aOrbiterD = ((aOrbiterD ^ aOrbiterF) ^ 6293096163612129260U) ^ aNonceWordH;
            aOrbiterD = RotL64((aOrbiterD * 8977954126326217153U), 47U);
            //
            aOrbiterE = ((aOrbiterE + aOrbiterJ) + 4271144764978661248U) + aOrbiterUpdateSaltA[((aIndex + 29U)) & S_SALT1];
            aOrbiterI = ((aOrbiterI ^ aOrbiterE) ^ 15938494256992560202U) ^ aNonceWordP;
            aOrbiterI = RotL64((aOrbiterI * 10004841288382726739U), 13U);
            //
            aOrbiterC = ((aOrbiterC + aOrbiterE) + 11038155227307702976U) + aNonceWordC;
            aOrbiterK = (aOrbiterK ^ aOrbiterC) ^ 12408749795071243930U;
            aOrbiterK = RotL64((aOrbiterK * 5527720475032868855U), 19U);
            //
            aOrbiterK = (aOrbiterK + aOrbiterI) + 1673665849053496882U;
            aOrbiterA = (aOrbiterA ^ aOrbiterK) ^ 12866353361497103629U;
            aOrbiterA = RotL64((aOrbiterA * 6041125499398924871U), 23U);
            //
            aOrbiterI = (aOrbiterI + aOrbiterF) + 10673935802381580966U;
            aOrbiterH = (aOrbiterH ^ aOrbiterI) ^ 8946776538955520352U;
            aOrbiterH = RotL64((aOrbiterH * 12293084177712710021U), 43U);
            //
            aOrbiterJ = (aOrbiterJ + aOrbiterC) + 16294935203370452805U;
            aOrbiterF = (aOrbiterF ^ aOrbiterJ) ^ 4697759331563852212U;
            aOrbiterF = RotL64((aOrbiterF * 14407806317275373043U), 5U);
            //
            aIngress = aOrbiterF ^ RotL64(aOrbiterI, 13U);
            aIngress = aIngress + (aOrbiterA ^ RotL64(aOrbiterC, 6U));
            aIngress = aIngress + (aOrbiterD ^ RotL64(aOrbiterE, 3U));
            aIngress = aIngress + (aOrbiterK ^ RotL64(aOrbiterJ, 35U));
            aIngress = aIngress + RotL64(aOrbiterH, 47U);
            aIngress = TwistMix64::DiffuseB((aIngress + aScatter));
            //
            aWandererD = aWandererD ^ (((RotL64(aIngress, 57U) + aOrbiterC) + RotL64(aOrbiterA, 52U)) + aWandererUpdateSaltA[(((31U - aIndex) + 13U)) & S_SALT1]);
            aWandererK = aWandererK + ((((RotL64(aScatter, 3U) + RotL64(aOrbiterI, 35U)) + aOrbiterH) + aNonceWordF) + aWandererUpdateSaltC[((aIndex + 21U)) & S_SALT1]);
            aWandererG = aWandererG ^ (((RotL64(aCross, 43U) + aOrbiterF) + RotL64(aOrbiterD, 27U)) + aNonceWordJ);
            aWandererE = aWandererE + ((((RotL64(aPrevious, 50U) + RotL64(aOrbiterJ, 39U)) + aOrbiterK) + RotL64(aCarry, 37U)) + aNonceWordM);
            aWandererB = aWandererB ^ (((RotL64(aCross, 23U) + aOrbiterI) + RotL64(aOrbiterK, 13U)) + aNonceWordK);
            aWandererJ = aWandererJ + ((RotL64(aPrevious, 35U) + aOrbiterC) + RotL64(aOrbiterE, 18U));
            aWandererF = aWandererF ^ ((RotL64(aScatter, 29U) + RotL64(aOrbiterJ, 5U)) + aOrbiterH);
            aWandererA = aWandererA + (((RotL64(aIngress, 14U) + aOrbiterF) + RotL64(aOrbiterJ, 57U)) + RotL64(aCarry, 19U));
            aWandererI = aWandererI ^ ((RotL64(aScatter, 39U) + aOrbiterF) + RotL64(aOrbiterE, 43U));
            //
            aCarry = aCarry + (aWandererJ ^ RotL64(aWandererD, 19U));
            aCarry = aCarry + (aWandererB ^ RotL64(aWandererG, 35U));
            aCarry = aCarry + (RotL64(aWandererI, 5U) ^ aWandererE);
            aCarry = aCarry + (RotL64(aWandererF, 11U) ^ aWandererK);
            aCarry = aCarry + RotL64(aWandererA, 22U);
            aCarry = aCarry + RotL64(aIngress, 57U);
            aCarry = TwistMix64::DiffuseC(aCarry);
            //
            aExpandLaneA[aIndex] = aIngress;
        }
    
        // kdf_b_loop_c loop 2
        // ingress from: aExpandLaneA, aOperationLaneC, aFireLaneD
        // ingress directions: aExpandLaneA forward forced, aOperationLaneC forward forced, aFireLaneD forward/backward random
        // cross from: aOperationLaneA, aOperationLaneD, aWorkLaneA
        // cross directions: aOperationLaneA backward forced, aOperationLaneD backward forced, aWorkLaneA backward/forward random
        // write to: aExpandLaneB
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aExpandLaneA[((aIndex + 8342U)) & S_BLOCK1], 54U) ^ RotL64(aOperationLaneC[((aIndex + 11823U)) & S_BLOCK1], 39U));
            aIngress ^= RotL64(aFireLaneD[((S_BLOCK1 - aIndex + 15992U)) & S_BLOCK1], 5U);
            aIngress = TwistMix64::DiffuseB(((aIngress ^ aDomainWordIngress) ^ aNonceWordB));
            //
            aCross = (RotL64(aOperationLaneA[((S_BLOCK1 - aIndex + 11511U)) & S_BLOCK1], 28U) ^ RotL64(aOperationLaneD[((S_BLOCK1 - aIndex + 12024U)) & S_BLOCK1], 5U));
            aCross ^= RotL64(aWorkLaneA[((S_BLOCK1 - aIndex + 13308U)) & S_BLOCK1], 37U);
            aCross = TwistMix64::DiffuseB(((aCross ^ aDomainWordCross) ^ aNonceWordA));
            //
            aScatter = (RotL64(aPrevious, 5U) + RotL64(aCarry, 39U)) ^ (RotL64(aIngress, 27U) + RotL64(aCross, 52U));
            aScatter = TwistMix64::DiffuseA(((aScatter ^ aDomainWordScatter) ^ aNonceWordM));
            //
            aOrbiterK = (aWandererF + RotL64(aScatter, 39U)) + 14686411261024919129U;
            aOrbiterF = ((aWandererA + RotL64(aCross, 47U)) + 7514582233957632005U) + aNonceWordO;
            aOrbiterJ = ((aWandererI + RotL64(aPrevious, 52U)) + 6520710480103365552U) + aOrbiterAssignSaltC[((aIndex + 23U)) & S_SALT1];
            aOrbiterB = (aWandererE + RotL64(aIngress, 43U)) + 1983621978676188036U;
            aOrbiterH = ((aWandererC + RotL64(aPrevious, 5U)) + RotL64(aCarry, 43U)) + 9003524602590749672U;
            aOrbiterG = (aWandererD + RotL64(aIngress, 35U)) + 6428568234045228995U;
            aOrbiterI = ((aWandererH + RotL64(aCross, 23U)) + RotL64(aCarry, 13U)) + 8656552687136446989U;
            aOrbiterC = (((aWandererK + RotL64(aScatter, 27U)) + RotL64(aCarry, 5U)) + 16916248288415922490U) + aOrbiterAssignSaltA[((aIndex + 21U)) & S_SALT1];
            aOrbiterD = ((aWandererG + RotL64(aCross, 12U)) + 9740237548002535784U) + aNonceWordG;
            //
            aOrbiterK = ((aOrbiterK + aOrbiterF) + 907561000814618339U) + aOrbiterUpdateSaltC[(((31U - aIndex) + 8U)) & S_SALT1];
            aOrbiterJ = (aOrbiterJ ^ aOrbiterK) ^ 4751108900841197631U;
            aOrbiterJ = RotL64((aOrbiterJ * 4545395964730641957U), 53U);
            //
            aOrbiterB = (aOrbiterB + aOrbiterH) + 167774899400732287U;
            aOrbiterG = (aOrbiterG ^ aOrbiterB) ^ 11907484918310854962U;
            aOrbiterG = RotL64((aOrbiterG * 7213139491146402985U), 23U);
            //
            aOrbiterG = ((aOrbiterG + aOrbiterK) + 14910318613649863924U) + aOrbiterUpdateSaltE[((aIndex + 19U)) & S_SALT1];
            aOrbiterI = (aOrbiterI ^ aOrbiterG) ^ 14882888155751455276U;
            aOrbiterI = RotL64((aOrbiterI * 11394136445442060201U), 47U);
            //
            aOrbiterI = (aOrbiterI + aOrbiterJ) + 16175942562693781908U;
            aOrbiterH = ((aOrbiterH ^ aOrbiterI) ^ 11022373758481651102U) ^ aNonceWordC;
            aOrbiterH = RotL64((aOrbiterH * 6836331461393816027U), 13U);
            //
            aOrbiterC = (aOrbiterC + aOrbiterB) + 12548405399045031548U;
            aOrbiterF = ((aOrbiterF ^ aOrbiterC) ^ 10850926364556828443U) ^ aOrbiterUpdateSaltA[((aIndex + 25U)) & S_SALT1];
            aOrbiterF = RotL64((aOrbiterF * 16231561687709867431U), 57U);
            //
            aOrbiterF = (aOrbiterF + aOrbiterG) + 13391684887911141790U;
            aOrbiterD = (aOrbiterD ^ aOrbiterF) ^ 14648937281264822988U;
            aOrbiterD = RotL64((aOrbiterD * 6533299316940026059U), 39U);
            //
            aOrbiterJ = (aOrbiterJ + aOrbiterD) + 8298658887198526821U;
            aOrbiterC = (aOrbiterC ^ aOrbiterJ) ^ 13822977698661348891U;
            aOrbiterC = RotL64((aOrbiterC * 17769262972278410937U), 19U);
            //
            aOrbiterH = (aOrbiterH + aOrbiterC) + 7505646847564645719U;
            aOrbiterK = ((aOrbiterK ^ aOrbiterH) ^ 3238749538197209166U) ^ aNonceWordK;
            aOrbiterK = RotL64((aOrbiterK * 15394286542600778567U), 43U);
            //
            aOrbiterD = ((aOrbiterD + aOrbiterI) + 15853506915123709257U) + aOrbiterUpdateSaltF[((aIndex + 22U)) & S_SALT1];
            aOrbiterB = (aOrbiterB ^ aOrbiterD) ^ 8426329899401071248U;
            aOrbiterB = RotL64((aOrbiterB * 1330397096577715113U), 3U);
            //
            aIngress = RotL64(aOrbiterJ, 36U) ^ aOrbiterI;
            aIngress = aIngress + (aOrbiterF ^ RotL64(aOrbiterD, 53U));
            aIngress = aIngress + (aOrbiterB ^ RotL64(aOrbiterG, 47U));
            aIngress = aIngress + (RotL64(aOrbiterK, 43U) ^ aOrbiterC);
            aIngress = aIngress + RotL64(aOrbiterH, 27U);
            aIngress = TwistMix64::DiffuseB((aIngress + aScatter));
            //
            aWandererE = aWandererE + ((((RotL64(aCross, 3U) + aOrbiterK) + RotL64(aOrbiterG, 13U)) + RotL64(aCarry, 51U)) + aNonceWordD);
            aWandererA = aWandererA ^ (((RotL64(aPrevious, 60U) + RotL64(aOrbiterH, 35U)) + aOrbiterK) + aWandererUpdateSaltF[(((31U - aIndex) + 16U)) & S_SALT1]);
            aWandererF = aWandererF + (((RotL64(aScatter, 53U) + RotL64(aOrbiterJ, 27U)) + aOrbiterG) + RotL64(aCarry, 41U));
            aWandererK = aWandererK ^ ((RotL64(aIngress, 41U) + RotL64(aOrbiterH, 46U)) + aOrbiterB);
            aWandererG = aWandererG + ((RotL64(aScatter, 37U) + RotL64(aOrbiterJ, 23U)) + aOrbiterC);
            aWandererH = aWandererH ^ ((((RotL64(aPrevious, 27U) + RotL64(aOrbiterH, 19U)) + aOrbiterD) + aNonceWordI) + aWandererUpdateSaltB[(((31U - aIndex) + 7U)) & S_SALT1]);
            aWandererI = aWandererI + ((RotL64(aIngress, 46U) + aOrbiterJ) + RotL64(aOrbiterB, 57U));
            aWandererD = aWandererD ^ ((RotL64(aCross, 19U) + aOrbiterH) + RotL64(aOrbiterI, 41U));
            aWandererC = aWandererC + ((RotL64(aScatter, 11U) + RotL64(aOrbiterF, 4U)) + aOrbiterC);
            //
            aCarry = aCarry + (RotL64(aWandererD, 35U) ^ aWandererF);
            aCarry = aCarry + (aWandererI ^ RotL64(aWandererK, 13U));
            aCarry = aCarry + (RotL64(aWandererC, 44U) ^ aWandererH);
            aCarry = aCarry + (aWandererG ^ RotL64(aWandererE, 21U));
            aCarry = aCarry + RotL64(aWandererA, 5U);
            aCarry = aCarry + RotL64(aIngress, 47U);
            aCarry = TwistMix64::DiffuseA(aCarry);
            //
            aExpandLaneB[S_BLOCK1 - aIndex] = aIngress;
        }
    
        // kdf_b_loop_c loop 3
        // ingress from: aExpandLaneB, aOperationLaneD, aFireLaneB
        // ingress directions: aExpandLaneB forward forced, aOperationLaneD forward forced, aFireLaneB forward/backward random
        // cross from: aExpandLaneA, aOperationLaneB, aWorkLaneB
        // cross directions: aExpandLaneA backward forced, aOperationLaneB backward forced, aWorkLaneB backward/forward random
        // write to: aExpandLaneC
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aExpandLaneB[((aIndex + 19998U)) & S_BLOCK1], 22U) ^ RotL64(aOperationLaneD[((aIndex + 17845U)) & S_BLOCK1], 39U));
            aIngress ^= RotL64(aFireLaneB[((S_BLOCK1 - aIndex + 24137U)) & S_BLOCK1], 53U);
            aIngress = TwistMix64::DiffuseA(((aIngress ^ aDomainWordIngress) ^ aNonceWordJ));
            //
            aCross = (RotL64(aExpandLaneA[((S_BLOCK1 - aIndex + 17075U)) & S_BLOCK1], 51U) ^ RotL64(aOperationLaneB[((S_BLOCK1 - aIndex + 22187U)) & S_BLOCK1], 42U));
            aCross ^= RotL64(aWorkLaneB[((aIndex + 21877U)) & S_BLOCK1], 11U);
            aCross = TwistMix64::DiffuseA(((aCross ^ aDomainWordCross) ^ aNonceWordL));
            //
            aScatter = (RotL64(aCross, 13U) + RotL64(aIngress, 26U)) + (RotL64(aPrevious, 57U) ^ RotL64(aCarry, 41U));
            aScatter = TwistMix64::DiffuseB(((aScatter ^ aDomainWordScatter) ^ aNonceWordP));
            //
            aOrbiterC = (aWandererC + RotL64(aIngress, 29U)) + 9133751643283278896U;
            aOrbiterI = ((aWandererK + RotL64(aCross, 57U)) + 8971581804375380408U) + aNonceWordH;
            aOrbiterA = ((aWandererH + RotL64(aPrevious, 22U)) + 12559650383714566592U) + aNonceWordC;
            aOrbiterD = ((aWandererA + RotL64(aScatter, 13U)) + RotL64(aCarry, 47U)) + 15753206088872859163U;
            aOrbiterG = ((aWandererI + RotL64(aCross, 37U)) + 7640756270450762350U) + aOrbiterAssignSaltF[((aIndex + 3U)) & S_SALT1];
            aOrbiterB = ((aWandererG + RotL64(aPrevious, 53U)) + 7340073357551376125U) + aNonceWordD;
            aOrbiterE = (aWandererE + RotL64(aScatter, 41U)) + 5270256573644196046U;
            aOrbiterK = ((aWandererJ + RotL64(aIngress, 47U)) + RotL64(aCarry, 57U)) + 3567367996479995928U;
            aOrbiterF = (((aWandererB + RotL64(aCross, 4U)) + RotL64(aCarry, 23U)) + 11939634537492733738U) + aOrbiterAssignSaltD[((aIndex + 26U)) & S_SALT1];
            //
            aOrbiterC = (aOrbiterC + aOrbiterI) + 7051817732424527120U;
            aOrbiterA = ((aOrbiterA ^ aOrbiterC) ^ 1730487669951837941U) ^ aOrbiterUpdateSaltA[((aIndex + 18U)) & S_SALT1];
            aOrbiterA = RotL64((aOrbiterA * 15191634337956285841U), 37U);
            //
            aOrbiterI = (aOrbiterI + aOrbiterD) + 18009252467909454817U;
            aOrbiterG = (aOrbiterG ^ aOrbiterI) ^ 2361024272031696442U;
            aOrbiterG = RotL64((aOrbiterG * 15215151562500226027U), 51U);
            //
            aOrbiterB = (aOrbiterB + aOrbiterA) + 15902755877642960397U;
            aOrbiterE = ((aOrbiterE ^ aOrbiterB) ^ 12243517544704116184U) ^ aOrbiterUpdateSaltF[(((31U - aIndex) + 10U)) & S_SALT1];
            aOrbiterE = RotL64((aOrbiterE * 2576071074148141447U), 3U);
            //
            aOrbiterK = ((aOrbiterK + aOrbiterC) + 16846181962302186187U) + aOrbiterUpdateSaltD[(((31U - aIndex) + 27U)) & S_SALT1];
            aOrbiterB = (aOrbiterB ^ aOrbiterK) ^ 636121425116506681U;
            aOrbiterB = RotL64((aOrbiterB * 17075030673338779993U), 47U);
            //
            aOrbiterG = (aOrbiterG + aOrbiterF) + 6887385655828217318U;
            aOrbiterC = (aOrbiterC ^ aOrbiterG) ^ 3705834550934775862U;
            aOrbiterC = RotL64((aOrbiterC * 11275428284929594435U), 11U);
            //
            aOrbiterD = ((aOrbiterD + aOrbiterB) + 11165142437077969438U) + aNonceWordN;
            aOrbiterF = (aOrbiterF ^ aOrbiterD) ^ 6426659930331618269U;
            aOrbiterF = RotL64((aOrbiterF * 17170640810530893705U), 27U);
            //
            aOrbiterF = (aOrbiterF + aOrbiterE) + 12629082390899315789U;
            aOrbiterI = ((aOrbiterI ^ aOrbiterF) ^ 4277510580069574724U) ^ aNonceWordA;
            aOrbiterI = RotL64((aOrbiterI * 9829125163412708305U), 21U);
            //
            aOrbiterE = (aOrbiterE + aOrbiterK) + 13814834144170469978U;
            aOrbiterD = ((aOrbiterD ^ aOrbiterE) ^ 3698381854100295826U) ^ aOrbiterUpdateSaltC[((aIndex + 9U)) & S_SALT1];
            aOrbiterD = RotL64((aOrbiterD * 5126359230872258015U), 43U);
            //
            aOrbiterA = (aOrbiterA + aOrbiterG) + 11623170635983579937U;
            aOrbiterK = (aOrbiterK ^ aOrbiterA) ^ 7247413650388803796U;
            aOrbiterK = RotL64((aOrbiterK * 3403219499465560059U), 57U);
            //
            aIngress = aOrbiterC ^ RotL64(aOrbiterD, 51U);
            aIngress = aIngress + (aOrbiterB ^ RotL64(aOrbiterE, 28U));
            aIngress = aIngress + (aOrbiterA ^ RotL64(aOrbiterK, 5U));
            aIngress = aIngress + (aOrbiterF ^ RotL64(aOrbiterG, 13U));
            aIngress = aIngress + RotL64(aOrbiterI, 57U);
            aIngress = TwistMix64::DiffuseA((aIngress + aScatter));
            //
            aWandererH = aWandererH + (((RotL64(aPrevious, 10U) + RotL64(aOrbiterG, 3U)) + aOrbiterC) + RotL64(aCarry, 37U));
            aWandererB = aWandererB ^ ((((RotL64(aIngress, 51U) + aOrbiterF) + RotL64(aOrbiterI, 11U)) + aNonceWordG) + aWandererUpdateSaltE[(((31U - aIndex) + 29U)) & S_SALT1]);
            aWandererK = aWandererK + ((RotL64(aScatter, 29U) + aOrbiterE) + RotL64(aOrbiterA, 35U));
            aWandererG = aWandererG ^ ((RotL64(aCross, 5U) + RotL64(aOrbiterK, 43U)) + aOrbiterG);
            aWandererE = aWandererE + ((RotL64(aPrevious, 19U) + RotL64(aOrbiterB, 60U)) + aOrbiterC);
            aWandererI = aWandererI ^ (((RotL64(aCross, 47U) + RotL64(aOrbiterD, 39U)) + aOrbiterF) + aNonceWordM);
            aWandererA = aWandererA + ((((RotL64(aScatter, 37U) + RotL64(aOrbiterB, 51U)) + aOrbiterF) + RotL64(aCarry, 53U)) + aNonceWordI);
            aWandererC = aWandererC ^ ((RotL64(aIngress, 14U) + aOrbiterF) + RotL64(aOrbiterE, 21U));
            aWandererJ = aWandererJ + (((RotL64(aPrevious, 41U) + aOrbiterE) + RotL64(aOrbiterD, 30U)) + aWandererUpdateSaltD[(((31U - aIndex) + 4U)) & S_SALT1]);
            //
            aCarry = aCarry + (aWandererE ^ RotL64(aWandererA, 51U));
            aCarry = aCarry + (RotL64(aWandererH, 39U) ^ aWandererC);
            aCarry = aCarry + (aWandererB ^ RotL64(aWandererK, 11U));
            aCarry = aCarry + (RotL64(aWandererG, 35U) ^ aWandererI);
            aCarry = aCarry + RotL64(aWandererJ, 24U);
            aCarry = aCarry + RotL64(aIngress, 5U);
            aCarry = TwistMix64::DiffuseB(aCarry);
            //
            aExpandLaneC[aIndex] = aIngress;
        }
    
        // kdf_b_loop_c loop 4
        // ingress from: aExpandLaneC, aExpandLaneA, aFireLaneC
        // ingress directions: aExpandLaneC forward forced, aExpandLaneA forward forced, aFireLaneC forward/backward random
        // cross from: aExpandLaneB, aOperationLaneC, aWorkLaneC
        // cross directions: aExpandLaneB backward forced, aOperationLaneC backward forced, aWorkLaneC backward/forward random
        // write to: aExpandLaneD
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aExpandLaneC[((aIndex + 25467U)) & S_BLOCK1], 54U) ^ RotL64(aExpandLaneA[((aIndex + 30528U)) & S_BLOCK1], 35U));
            aIngress ^= RotL64(aFireLaneC[((aIndex + 25343U)) & S_BLOCK1], 11U);
            aIngress = TwistMix64::DiffuseB(((aIngress ^ aDomainWordIngress) ^ aNonceWordB));
            //
            aCross = (RotL64(aExpandLaneB[((S_BLOCK1 - aIndex + 32362U)) & S_BLOCK1], 35U) ^ RotL64(aOperationLaneC[((S_BLOCK1 - aIndex + 30763U)) & S_BLOCK1], 12U));
            aCross ^= RotL64(aWorkLaneC[((aIndex + 26972U)) & S_BLOCK1], 3U);
            aCross = TwistMix64::DiffuseA(((aCross ^ aDomainWordCross) ^ aNonceWordC));
            //
            aScatter = (RotL64(aCarry, 39U) ^ RotL64(aIngress, 57U)) ^ (RotL64(aCross, 23U) + RotL64(aPrevious, 10U));
            aScatter = TwistMix64::DiffuseB(((aScatter ^ aDomainWordScatter) ^ aNonceWordI));
            //
            aOrbiterD = ((aWandererH + RotL64(aPrevious, 30U)) + RotL64(aCarry, 3U)) + 15383045568644941552U;
            aOrbiterJ = (((aWandererF + RotL64(aCross, 43U)) + RotL64(aCarry, 47U)) + 17452811657750910067U) + aOrbiterAssignSaltB[((aIndex + 11U)) & S_SALT1];
            aOrbiterB = (aWandererD + RotL64(aScatter, 57U)) + 15660117718455155603U;
            aOrbiterC = (aWandererE + RotL64(aIngress, 19U)) + 10396441207743665753U;
            aOrbiterE = ((aWandererK + RotL64(aPrevious, 47U)) + 3708971058200841442U) + aNonceWordE;
            aOrbiterH = (aWandererB + RotL64(aScatter, 14U)) + 7000673057768598750U;
            aOrbiterA = (((aWandererI + RotL64(aCross, 39U)) + 9886354469011131596U) + aOrbiterAssignSaltE[(((31U - aIndex) + 29U)) & S_SALT1]) + aNonceWordH;
            aOrbiterK = ((aWandererJ + RotL64(aIngress, 3U)) + RotL64(aCarry, 27U)) + 16018065329058043467U;
            aOrbiterF = (aWandererA + RotL64(aScatter, 35U)) + 5024756166109352320U;
            //
            aOrbiterD = ((aOrbiterD + aOrbiterJ) + 6587818720728886652U) + aOrbiterUpdateSaltA[(((31U - aIndex) + 6U)) & S_SALT1];
            aOrbiterB = ((aOrbiterB ^ aOrbiterD) ^ 3652672354944162319U) ^ aOrbiterUpdateSaltB[((aIndex + 25U)) & S_SALT1];
            aOrbiterB = RotL64((aOrbiterB * 10807121230791716109U), 35U);
            //
            aOrbiterC = (aOrbiterC + aOrbiterE) + 6307315649915348048U;
            aOrbiterJ = ((aOrbiterJ ^ aOrbiterC) ^ 16405347331742979258U) ^ aNonceWordK;
            aOrbiterJ = RotL64((aOrbiterJ * 7183142442906743699U), 51U);
            //
            aOrbiterH = (aOrbiterH + aOrbiterB) + 5427299664054601957U;
            aOrbiterA = ((aOrbiterA ^ aOrbiterH) ^ 4983381733483185898U) ^ aNonceWordA;
            aOrbiterA = RotL64((aOrbiterA * 14646556236306407673U), 43U);
            //
            aOrbiterK = (aOrbiterK + aOrbiterA) + 10182995521328377487U;
            aOrbiterC = ((aOrbiterC ^ aOrbiterK) ^ 8694282877540593550U) ^ aOrbiterUpdateSaltD[((aIndex + 9U)) & S_SALT1];
            aOrbiterC = RotL64((aOrbiterC * 14614602561910403893U), 11U);
            //
            aOrbiterE = ((aOrbiterE + aOrbiterD) + 4085927978153269932U) + aOrbiterUpdateSaltF[((aIndex + 27U)) & S_SALT1];
            aOrbiterH = (aOrbiterH ^ aOrbiterE) ^ 6176195962815240877U;
            aOrbiterH = RotL64((aOrbiterH * 16792916528959579875U), 57U);
            //
            aOrbiterF = (aOrbiterF + aOrbiterC) + 6966742100601433005U;
            aOrbiterD = (aOrbiterD ^ aOrbiterF) ^ 9920952446921247521U;
            aOrbiterD = RotL64((aOrbiterD * 1879821050131820933U), 29U);
            //
            aOrbiterJ = (aOrbiterJ + aOrbiterH) + 11958734477518336014U;
            aOrbiterK = ((aOrbiterK ^ aOrbiterJ) ^ 2058335903640404380U) ^ aNonceWordJ;
            aOrbiterK = RotL64((aOrbiterK * 6986170159285417789U), 21U);
            //
            aOrbiterB = (aOrbiterB + aOrbiterK) + 77366119537297816U;
            aOrbiterF = (aOrbiterF ^ aOrbiterB) ^ 12072894199692855000U;
            aOrbiterF = RotL64((aOrbiterF * 9083781120514635987U), 39U);
            //
            aOrbiterA = (aOrbiterA + aOrbiterF) + 11874297832446385377U;
            aOrbiterE = (aOrbiterE ^ aOrbiterA) ^ 13715562531763053196U;
            aOrbiterE = RotL64((aOrbiterE * 12822488258322963187U), 3U);
            //
            aIngress = aOrbiterH ^ RotL64(aOrbiterK, 47U);
            aIngress = aIngress + (RotL64(aOrbiterA, 3U) ^ aOrbiterF);
            aIngress = aIngress + (aOrbiterB ^ RotL64(aOrbiterD, 30U));
            aIngress = aIngress + (aOrbiterE ^ RotL64(aOrbiterC, 13U));
            aIngress = aIngress + RotL64(aOrbiterJ, 39U);
            aIngress = TwistMix64::DiffuseB((aIngress + aScatter));
            //
            aWandererB = aWandererB ^ ((RotL64(aPrevious, 6U) + RotL64(aOrbiterD, 13U)) + aOrbiterB);
            aWandererI = aWandererI + (((RotL64(aCross, 13U) + RotL64(aOrbiterE, 60U)) + aOrbiterJ) + aWandererUpdateSaltA[(((31U - aIndex) + 23U)) & S_SALT1]);
            aWandererJ = aWandererJ ^ (((RotL64(aIngress, 29U) + aOrbiterK) + RotL64(aOrbiterJ, 19U)) + aNonceWordO);
            aWandererH = aWandererH + ((RotL64(aScatter, 43U) + RotL64(aOrbiterJ, 23U)) + aOrbiterH);
            aWandererA = aWandererA ^ ((RotL64(aIngress, 23U) + RotL64(aOrbiterA, 41U)) + aOrbiterC);
            aWandererD = aWandererD + ((((RotL64(aScatter, 19U) + aOrbiterH) + RotL64(aOrbiterK, 53U)) + RotL64(aCarry, 3U)) + aWandererUpdateSaltC[(((31U - aIndex) + 3U)) & S_SALT1]);
            aWandererK = aWandererK ^ (((RotL64(aPrevious, 52U) + RotL64(aOrbiterE, 46U)) + aOrbiterC) + aNonceWordN);
            aWandererE = aWandererE + (((RotL64(aCross, 39U) + RotL64(aOrbiterC, 35U)) + aOrbiterF) + RotL64(aCarry, 35U));
            aWandererF = aWandererF ^ (((RotL64(aPrevious, 57U) + RotL64(aOrbiterD, 5U)) + aOrbiterJ) + aNonceWordF);
            //
            aCarry = aCarry + (RotL64(aWandererB, 6U) ^ aWandererJ);
            aCarry = aCarry + (aWandererF ^ RotL64(aWandererD, 21U));
            aCarry = aCarry + (aWandererK ^ RotL64(aWandererI, 51U));
            aCarry = aCarry + (aWandererH ^ RotL64(aWandererA, 47U));
            aCarry = aCarry + RotL64(aWandererE, 57U);
            aCarry = aCarry + RotL64(aIngress, 37U);
            aCarry = TwistMix64::DiffuseC(aCarry);
            //
            aExpandLaneD[S_BLOCK1 - aIndex] = aIngress;
        }
    }
    // KDF_B_C kdf_b_loop_c (end)
    *pPrevious = aPrevious;
    *pIngress = aIngress;
    *pCarry = aCarry;
    *pWandererA = aWandererA;
    *pWandererB = aWandererB;
    *pWandererC = aWandererC;
    *pWandererD = aWandererD;
    *pWandererE = aWandererE;
    *pWandererF = aWandererF;
    *pWandererG = aWandererG;
    *pWandererH = aWandererH;
    *pWandererI = aWandererI;
    *pWandererJ = aWandererJ;
    *pWandererK = aWandererK;
}

void TwistExpander_Exercea_Arx::KDF_B_D(TwistWorkSpace *pWorkSpace,
                     std::uint64_t pNonce,
                     TwistDomainConstants *pConstants,
                     TwistDomainSaltSet *pDomainSaltSet,
                     std::uint64_t *pPrevious,
                     std::uint64_t *pIngress,
                     std::uint64_t *pCarry,
                     std::uint64_t *pWandererA,
                     std::uint64_t *pWandererB,
                     std::uint64_t *pWandererC,
                     std::uint64_t *pWandererD,
                     std::uint64_t *pWandererE,
                     std::uint64_t *pWandererF,
                     std::uint64_t *pWandererG,
                     std::uint64_t *pWandererH,
                     std::uint64_t *pWandererI,
                     std::uint64_t *pWandererJ,
                     std::uint64_t *pWandererK) {
    [[maybe_unused]] std::uint64_t *aOrbiterAssignSaltA = pDomainSaltSet->mOrbiterAssign.mSaltA;
    [[maybe_unused]] std::uint64_t *aOrbiterAssignSaltB = pDomainSaltSet->mOrbiterAssign.mSaltB;
    [[maybe_unused]] std::uint64_t *aOrbiterAssignSaltC = pDomainSaltSet->mOrbiterAssign.mSaltC;
    [[maybe_unused]] std::uint64_t *aOrbiterAssignSaltD = pDomainSaltSet->mOrbiterAssign.mSaltD;
    [[maybe_unused]] std::uint64_t *aOrbiterAssignSaltE = pDomainSaltSet->mOrbiterAssign.mSaltE;
    [[maybe_unused]] std::uint64_t *aOrbiterAssignSaltF = pDomainSaltSet->mOrbiterAssign.mSaltF;
    [[maybe_unused]] std::uint64_t *aOrbiterUpdateSaltA = pDomainSaltSet->mOrbiterUpdate.mSaltA;
    [[maybe_unused]] std::uint64_t *aOrbiterUpdateSaltB = pDomainSaltSet->mOrbiterUpdate.mSaltB;
    [[maybe_unused]] std::uint64_t *aOrbiterUpdateSaltC = pDomainSaltSet->mOrbiterUpdate.mSaltC;
    [[maybe_unused]] std::uint64_t *aOrbiterUpdateSaltD = pDomainSaltSet->mOrbiterUpdate.mSaltD;
    [[maybe_unused]] std::uint64_t *aOrbiterUpdateSaltE = pDomainSaltSet->mOrbiterUpdate.mSaltE;
    [[maybe_unused]] std::uint64_t *aOrbiterUpdateSaltF = pDomainSaltSet->mOrbiterUpdate.mSaltF;
    [[maybe_unused]] std::uint64_t *aWandererUpdateSaltA = pDomainSaltSet->mWandererUpdate.mSaltA;
    [[maybe_unused]] std::uint64_t *aWandererUpdateSaltB = pDomainSaltSet->mWandererUpdate.mSaltB;
    [[maybe_unused]] std::uint64_t *aWandererUpdateSaltC = pDomainSaltSet->mWandererUpdate.mSaltC;
    [[maybe_unused]] std::uint64_t *aWandererUpdateSaltD = pDomainSaltSet->mWandererUpdate.mSaltD;
    [[maybe_unused]] std::uint64_t *aWandererUpdateSaltE = pDomainSaltSet->mWandererUpdate.mSaltE;
    [[maybe_unused]] std::uint64_t *aWandererUpdateSaltF = pDomainSaltSet->mWandererUpdate.mSaltF;
    [[maybe_unused]] std::uint8_t *aExpandLaneA = pWorkSpace->mExpansionLaneA;
    [[maybe_unused]] std::uint8_t *aExpandLaneB = pWorkSpace->mExpansionLaneB;
    [[maybe_unused]] std::uint8_t *aExpandLaneC = pWorkSpace->mExpansionLaneC;
    [[maybe_unused]] std::uint8_t *aExpandLaneD = pWorkSpace->mExpansionLaneD;
    [[maybe_unused]] std::uint8_t *aWorkLaneA = pWorkSpace->mWorkLaneA;
    [[maybe_unused]] std::uint8_t *aWorkLaneB = pWorkSpace->mWorkLaneB;
    [[maybe_unused]] std::uint8_t *aWorkLaneC = pWorkSpace->mWorkLaneC;
    [[maybe_unused]] std::uint8_t *aWorkLaneD = pWorkSpace->mWorkLaneD;
    [[maybe_unused]] std::uint8_t *aOperationLaneA = pWorkSpace->mOperationLaneA;
    [[maybe_unused]] std::uint8_t *aOperationLaneB = pWorkSpace->mOperationLaneB;
    [[maybe_unused]] std::uint8_t *aOperationLaneC = pWorkSpace->mOperationLaneC;
    [[maybe_unused]] std::uint8_t *aOperationLaneD = pWorkSpace->mOperationLaneD;
    [[maybe_unused]] std::uint8_t *aFireLaneA = pWorkSpace->mFireLaneA;
    [[maybe_unused]] std::uint8_t *aFireLaneB = pWorkSpace->mFireLaneB;
    [[maybe_unused]] std::uint8_t *aFireLaneC = pWorkSpace->mFireLaneC;
    [[maybe_unused]] std::uint8_t *aFireLaneD = pWorkSpace->mFireLaneD;
    std::uint64_t aCross = 0; std::uint64_t aScatter = 0;

    std::uint64_t aOrbiterA = 0; std::uint64_t aOrbiterB = 0; std::uint64_t aOrbiterC = 0; std::uint64_t aOrbiterD = 0;
    std::uint64_t aOrbiterE = 0; std::uint64_t aOrbiterF = 0; std::uint64_t aOrbiterG = 0; std::uint64_t aOrbiterH = 0;
    std::uint64_t aOrbiterI = 0; std::uint64_t aOrbiterJ = 0; std::uint64_t aOrbiterK = 0;

    // [kdf-a arx]
    std::uint64_t aNonceWordA = TwistMix64::DiffuseB(pNonce * 0x8D64B76D15171E59ULL + 0x8381E9BF696531A7ULL);
    std::uint64_t aNonceWordB = TwistMix64::DiffuseC(pNonce * 0xDA20612EFD2A3B17ULL + 0xD36D0C0DFE883FFAULL);
    std::uint64_t aNonceWordC = TwistMix64::DiffuseB(pNonce * 0xF026D841C18390E7ULL + 0xB5E9E1A521B9A6F7ULL);
    std::uint64_t aNonceWordD = TwistMix64::DiffuseB(pNonce * 0xAEFCAF063310F6E3ULL + 0xF3784EDF1924EAD8ULL);
    std::uint64_t aNonceWordE = TwistMix64::DiffuseA(pNonce * 0x8A460CAE26DC5D4BULL + 0x886915BFF4FCD64CULL);
    std::uint64_t aNonceWordF = TwistMix64::DiffuseC(pNonce * 0xF9EFC0B5FF95D16BULL + 0xAE700DC791BD77F8ULL);
    std::uint64_t aNonceWordG = TwistMix64::DiffuseB(pNonce * 0xD540E612E171AD09ULL + 0xA4203689E705DCAAULL);
    std::uint64_t aNonceWordH = TwistMix64::DiffuseA(pNonce * 0xB9D2D5C123DC80C7ULL + 0x87D93AA27EDA4441ULL);
    std::uint64_t aNonceWordI = TwistMix64::DiffuseA(pNonce * 0xB6F760B164DFC2E3ULL + 0x9C0E73D7BDFDA0D6ULL);
    std::uint64_t aNonceWordJ = TwistMix64::DiffuseB(pNonce * 0x912FAD5D2809DE53ULL + 0xF58AD6050FF5EA02ULL);
    std::uint64_t aNonceWordK = TwistMix64::DiffuseB(pNonce * 0xE2FFE0561883768BULL + 0xD4571964F9CD3E36ULL);
    std::uint64_t aNonceWordL = TwistMix64::DiffuseB(pNonce * 0xB170FD6F4B01F36BULL + 0xF9FEE9892D81A444ULL);
    std::uint64_t aNonceWordM = TwistMix64::DiffuseC(pNonce * 0xCD86A2076EB42553ULL + 0x9229E9CA08EA13A4ULL);
    std::uint64_t aNonceWordN = TwistMix64::DiffuseC(pNonce * 0xC239C57EBF0E59ABULL + 0xF821EA55733F0D0FULL);
    std::uint64_t aNonceWordO = TwistMix64::DiffuseC(pNonce * 0xE05B083F0AD1D40DULL + 0xB05816C000D77AE5ULL);
    std::uint64_t aNonceWordP = TwistMix64::DiffuseC(pNonce * 0xACF96D8DAE64810FULL + 0x8D0662A3726F5341ULL);
    std::uint64_t aDomainWordIngress = pConstants->mIngress;
    std::uint64_t aDomainWordScatter = pConstants->mScatter;
    std::uint64_t aDomainWordCross = pConstants->mCross;
    [[maybe_unused]] std::uint8_t *mSource = pWorkSpace->mSource;
    std::uint64_t aPrevious = *pPrevious;
    std::uint64_t aIngress = *pIngress;
    std::uint64_t aCarry = *pCarry;
    std::uint64_t aWandererA = *pWandererA;
    std::uint64_t aWandererB = *pWandererB;
    std::uint64_t aWandererC = *pWandererC;
    std::uint64_t aWandererD = *pWandererD;
    std::uint64_t aWandererE = *pWandererE;
    std::uint64_t aWandererF = *pWandererF;
    std::uint64_t aWandererG = *pWandererG;
    std::uint64_t aWandererH = *pWandererH;
    std::uint64_t aWandererI = *pWandererI;
    std::uint64_t aWandererJ = *pWandererJ;
    std::uint64_t aWandererK = *pWandererK;
    // KDF_B_D kdf_b_loop_d (start)
    {
        // KDF_B_D kdf_b_loop_d lane group
        // read from: aWorkLaneA, aWorkLaneB, aOperationLaneA, aWorkLaneC, aWorkLaneD, aFireLaneD, aExpandLaneA, aFireLaneB, aFireLaneA, aExpandLaneB, aFireLaneC, aOperationLaneD, aExpandLaneC, aOperationLaneC, aOperationLaneB
        // write to: aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD
    
        // kdf_b_loop_d loop 1
        // ingress from: aWorkLaneA, aWorkLaneB, aOperationLaneA
        // ingress directions: aWorkLaneA forward forced, aWorkLaneB forward forced, aOperationLaneA forward/backward random
        // cross from: aWorkLaneC, aWorkLaneD, aFireLaneD
        // cross directions: aWorkLaneC backward forced, aWorkLaneD backward forced, aFireLaneD backward/forward random
        // write to: aExpandLaneA
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aWorkLaneA[((aIndex + 4529U)) & S_BLOCK1], 34U) ^ RotL64(aWorkLaneB[((aIndex + 6163U)) & S_BLOCK1], 57U));
            aIngress ^= RotL64(aOperationLaneA[((S_BLOCK1 - aIndex + 7940U)) & S_BLOCK1], 23U);
            aIngress = TwistMix64::DiffuseA(((aIngress ^ aDomainWordIngress) ^ aNonceWordN));
            //
            aCross = (RotL64(aWorkLaneC[((S_BLOCK1 - aIndex + 6428U)) & S_BLOCK1], 23U) ^ RotL64(aWorkLaneD[((S_BLOCK1 - aIndex + 64U)) & S_BLOCK1], 52U));
            aCross ^= RotL64(aFireLaneD[((S_BLOCK1 - aIndex + 3531U)) & S_BLOCK1], 35U);
            aCross = TwistMix64::DiffuseB(((aCross ^ aDomainWordCross) ^ aNonceWordI));
            //
            aScatter = (RotL64(aCross, 23U) + RotL64(aIngress, 35U)) ^ (RotL64(aCarry, 48U) + RotL64(aPrevious, 5U));
            aScatter = TwistMix64::DiffuseC(((aScatter ^ aDomainWordScatter) ^ aNonceWordA));
            //
            aOrbiterI = (((aWandererJ + RotL64(aPrevious, 26U)) + RotL64(aCarry, 47U)) + 6024062041314952357U) + aNonceWordP;
            aOrbiterG = ((aWandererB + RotL64(aCross, 11U)) + 18340757093658015585U) + aOrbiterAssignSaltD[((aIndex + 24U)) & S_SALT1];
            aOrbiterA = ((aWandererA + RotL64(aIngress, 51U)) + 11911120493880346751U) + aNonceWordH;
            aOrbiterJ = (aWandererG + RotL64(aScatter, 57U)) + 17428074353884654439U;
            aOrbiterD = (((aWandererD + RotL64(aCross, 43U)) + 12790849760814795936U) + aOrbiterAssignSaltC[((aIndex + 23U)) & S_SALT1]) + aNonceWordA;
            aOrbiterC = ((aWandererH + RotL64(aIngress, 3U)) + RotL64(aCarry, 27U)) + 12633397052172117800U;
            aOrbiterH = (((aWandererF + RotL64(aScatter, 19U)) + RotL64(aCarry, 3U)) + 11946150433665237945U) + aNonceWordF;
            //
            aOrbiterI = ((aOrbiterI + aOrbiterG) + 16842157900909419285U) + aNonceWordM;
            aOrbiterA = (aOrbiterA ^ aOrbiterI) ^ 14186235783224155962U;
            aOrbiterA = RotL64((aOrbiterA * 10521157787073684417U), 47U);
            //
            aOrbiterA = ((aOrbiterA + aOrbiterJ) + 13284904542579767591U) + aOrbiterUpdateSaltF[(((31U - aIndex) + 6U)) & S_SALT1];
            aOrbiterD = (aOrbiterD ^ aOrbiterA) ^ 11609181965078844357U;
            aOrbiterD = RotL64((aOrbiterD * 5455780554452453513U), 21U);
            //
            aOrbiterC = (aOrbiterC + aOrbiterA) + 9628562297095374984U;
            aOrbiterH = ((aOrbiterH ^ aOrbiterC) ^ 7850281529011259759U) ^ aOrbiterUpdateSaltB[(((31U - aIndex) + 5U)) & S_SALT1];
            aOrbiterH = RotL64((aOrbiterH * 17611485102925470357U), 29U);
            //
            aOrbiterG = (aOrbiterG + aOrbiterH) + 257458718073794527U;
            aOrbiterJ = ((aOrbiterJ ^ aOrbiterG) ^ 10693404545773519306U) ^ aNonceWordK;
            aOrbiterJ = RotL64((aOrbiterJ * 14821443722828498323U), 11U);
            //
            aOrbiterJ = ((aOrbiterJ + aOrbiterI) + 3430519236533871460U) + aOrbiterUpdateSaltA[((aIndex + 7U)) & S_SALT1];
            aOrbiterC = ((aOrbiterC ^ aOrbiterJ) ^ 6183054506953198055U) ^ aNonceWordD;
            aOrbiterC = RotL64((aOrbiterC * 6121082743789970911U), 35U);
            //
            aOrbiterD = ((aOrbiterD + aOrbiterC) + 2905610989884221654U) + aOrbiterUpdateSaltE[((aIndex + 13U)) & S_SALT1];
            aOrbiterG = (aOrbiterG ^ aOrbiterD) ^ 4472163910775333862U;
            aOrbiterG = RotL64((aOrbiterG * 7770678426310856745U), 57U);
            //
            aOrbiterH = (aOrbiterH + aOrbiterD) + 16870142883133769663U;
            aOrbiterI = (aOrbiterI ^ aOrbiterH) ^ 1403692060594816451U;
            aOrbiterI = RotL64((aOrbiterI * 9740854430251597879U), 5U);
            //
            aIngress = RotL64(aOrbiterH, 3U) ^ aOrbiterG;
            aIngress = aIngress + (RotL64(aOrbiterI, 41U) ^ aOrbiterA);
            aIngress = aIngress + (aOrbiterJ ^ RotL64(aOrbiterD, 11U));
            aIngress = aIngress + RotL64(aOrbiterC, 27U);
            aIngress = TwistMix64::DiffuseA((aIngress + aScatter));
            //
            aWandererG = aWandererG + (((RotL64(aPrevious, 27U) + RotL64(aOrbiterH, 4U)) + aOrbiterD) + RotL64(aCarry, 41U));
            aWandererD = aWandererD ^ ((RotL64(aScatter, 57U) + RotL64(aOrbiterJ, 11U)) + aOrbiterC);
            aWandererJ = aWandererJ + (((RotL64(aIngress, 51U) + RotL64(aOrbiterH, 57U)) + aOrbiterA) + aNonceWordE);
            aWandererB = aWandererB ^ (((RotL64(aCross, 4U) + RotL64(aOrbiterI, 27U)) + aOrbiterJ) + aNonceWordC);
            aWandererH = aWandererH + (((RotL64(aPrevious, 11U) + RotL64(aOrbiterI, 19U)) + aOrbiterH) + aWandererUpdateSaltB[((aIndex + 19U)) & S_SALT1]);
            aWandererA = aWandererA ^ (((RotL64(aScatter, 41U) + RotL64(aOrbiterG, 37U)) + aOrbiterD) + aNonceWordO);
            aWandererF = aWandererF + ((((RotL64(aCross, 19U) + aOrbiterJ) + RotL64(aOrbiterG, 51U)) + RotL64(aCarry, 3U)) + aWandererUpdateSaltA[(((31U - aIndex) + 22U)) & S_SALT1]);
            //
            aCarry = aCarry + (RotL64(aWandererD, 53U) ^ aWandererB);
            aCarry = aCarry + (aWandererG ^ RotL64(aWandererF, 29U));
            aCarry = aCarry + (RotL64(aWandererJ, 12U) ^ aWandererH);
            aCarry = aCarry + RotL64(aWandererA, 57U);
            aCarry = aCarry + RotL64(aIngress, 3U);
            aCarry = TwistMix64::DiffuseB(aCarry);
            //
            aExpandLaneA[aIndex] = aIngress;
        }
    
        // kdf_b_loop_d loop 2
        // ingress from: aExpandLaneA, aWorkLaneC, aFireLaneB
        // ingress directions: aExpandLaneA forward forced, aWorkLaneC forward forced, aFireLaneB forward/backward random
        // cross from: aWorkLaneA, aWorkLaneD, aFireLaneA
        // cross directions: aWorkLaneA backward forced, aWorkLaneD backward forced, aFireLaneA backward/forward random
        // write to: aExpandLaneB
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aExpandLaneA[((aIndex + 12973U)) & S_BLOCK1], 50U) ^ RotL64(aWorkLaneC[((aIndex + 13542U)) & S_BLOCK1], 5U));
            aIngress ^= RotL64(aFireLaneB[((S_BLOCK1 - aIndex + 9257U)) & S_BLOCK1], 35U);
            aIngress = TwistMix64::DiffuseA(((aIngress ^ aDomainWordIngress) ^ aNonceWordD));
            //
            aCross = (RotL64(aWorkLaneA[((S_BLOCK1 - aIndex + 15199U)) & S_BLOCK1], 3U) ^ RotL64(aWorkLaneD[((S_BLOCK1 - aIndex + 12744U)) & S_BLOCK1], 41U));
            aCross ^= RotL64(aFireLaneA[((S_BLOCK1 - aIndex + 11321U)) & S_BLOCK1], 13U);
            aCross = TwistMix64::DiffuseC(((aCross ^ aDomainWordCross) ^ aNonceWordP));
            //
            aScatter = (RotL64(aIngress, 19U) + RotL64(aCross, 37U)) + (RotL64(aPrevious, 4U) ^ RotL64(aCarry, 51U));
            aScatter = TwistMix64::DiffuseA(((aScatter ^ aDomainWordScatter) ^ aNonceWordD));
            //
            aOrbiterD = ((aWandererD + RotL64(aIngress, 37U)) + 9888431329297626900U) + aNonceWordO;
            aOrbiterA = (((aWandererH + RotL64(aCross, 57U)) + 2937735167534624403U) + aOrbiterAssignSaltA[(((31U - aIndex) + 28U)) & S_SALT1]) + aNonceWordE;
            aOrbiterI = ((aWandererE + RotL64(aPrevious, 11U)) + RotL64(aCarry, 21U)) + 17626022970343789617U;
            aOrbiterJ = (aWandererC + RotL64(aScatter, 28U)) + 5665660859333693743U;
            aOrbiterH = (((aWandererA + RotL64(aIngress, 19U)) + RotL64(aCarry, 51U)) + 1060537034632076669U) + aNonceWordN;
            aOrbiterC = ((aWandererF + RotL64(aPrevious, 3U)) + 743777763907175800U) + aOrbiterAssignSaltF[((aIndex + 9U)) & S_SALT1];
            aOrbiterB = ((aWandererG + RotL64(aScatter, 43U)) + RotL64(aCarry, 37U)) + 5744905970181808845U;
            //
            aOrbiterD = ((aOrbiterD + aOrbiterA) + 3545351394494002180U) + aNonceWordH;
            aOrbiterI = (((aOrbiterI ^ aOrbiterD) ^ 4877547088414106007U) ^ aOrbiterUpdateSaltF[((aIndex + 26U)) & S_SALT1]) ^ aNonceWordL;
            aOrbiterI = RotL64((aOrbiterI * 5416792889338547109U), 43U);
            //
            aOrbiterJ = ((aOrbiterJ + aOrbiterH) + 11669378338379598445U) + aOrbiterUpdateSaltA[((aIndex + 12U)) & S_SALT1];
            aOrbiterA = ((aOrbiterA ^ aOrbiterJ) ^ 2961072441706158212U) ^ aNonceWordG;
            aOrbiterA = RotL64((aOrbiterA * 2677988507090705371U), 11U);
            //
            aOrbiterH = (aOrbiterH + aOrbiterD) + 13984945589234919765U;
            aOrbiterC = (aOrbiterC ^ aOrbiterH) ^ 1433097875470903205U;
            aOrbiterC = RotL64((aOrbiterC * 451996840039906781U), 29U);
            //
            aOrbiterA = ((aOrbiterA + aOrbiterC) + 716415411025451152U) + aNonceWordB;
            aOrbiterB = (aOrbiterB ^ aOrbiterA) ^ 8542286150858297810U;
            aOrbiterB = RotL64((aOrbiterB * 9139015340823332449U), 3U);
            //
            aOrbiterI = (aOrbiterI + aOrbiterB) + 12932391786479661299U;
            aOrbiterH = (aOrbiterH ^ aOrbiterI) ^ 14005503313299177013U;
            aOrbiterH = RotL64((aOrbiterH * 802663466907819743U), 51U);
            //
            aOrbiterB = (aOrbiterB + aOrbiterJ) + 9382792812676318046U;
            aOrbiterD = ((aOrbiterD ^ aOrbiterB) ^ 5138554251079724724U) ^ aOrbiterUpdateSaltC[((aIndex + 21U)) & S_SALT1];
            aOrbiterD = RotL64((aOrbiterD * 6386016499265056247U), 37U);
            //
            aOrbiterC = ((aOrbiterC + aOrbiterI) + 8522380066269546172U) + aOrbiterUpdateSaltD[(((31U - aIndex) + 11U)) & S_SALT1];
            aOrbiterJ = (aOrbiterJ ^ aOrbiterC) ^ 11825536408101906458U;
            aOrbiterJ = RotL64((aOrbiterJ * 17042837108792016849U), 57U);
            //
            aIngress = aOrbiterD ^ RotL64(aOrbiterC, 27U);
            aIngress = aIngress + (aOrbiterI ^ RotL64(aOrbiterB, 42U));
            aIngress = aIngress + (RotL64(aOrbiterH, 35U) ^ aOrbiterA);
            aIngress = aIngress + RotL64(aOrbiterJ, 11U);
            aIngress = TwistMix64::DiffuseB((aIngress + aScatter));
            //
            aWandererD = aWandererD ^ (((RotL64(aPrevious, 53U) + RotL64(aOrbiterB, 47U)) + aOrbiterA) + aNonceWordK);
            aWandererF = aWandererF + (((RotL64(aScatter, 39U) + RotL64(aOrbiterD, 19U)) + aOrbiterH) + RotL64(aCarry, 53U));
            aWandererA = aWandererA ^ ((RotL64(aIngress, 13U) + aOrbiterH) + RotL64(aOrbiterJ, 38U));
            aWandererG = aWandererG + ((((RotL64(aCross, 19U) + RotL64(aOrbiterJ, 13U)) + aOrbiterB) + RotL64(aCarry, 27U)) + aNonceWordF);
            aWandererH = aWandererH ^ (((RotL64(aScatter, 26U) + RotL64(aOrbiterD, 3U)) + aOrbiterI) + aWandererUpdateSaltF[(((31U - aIndex) + 29U)) & S_SALT1]);
            aWandererE = aWandererE + ((((RotL64(aIngress, 47U) + RotL64(aOrbiterA, 27U)) + aOrbiterC) + aNonceWordJ) + aWandererUpdateSaltD[((aIndex + 15U)) & S_SALT1]);
            aWandererC = aWandererC ^ ((RotL64(aPrevious, 3U) + aOrbiterA) + RotL64(aOrbiterJ, 53U));
            //
            aCarry = aCarry + (RotL64(aWandererC, 21U) ^ aWandererD);
            aCarry = aCarry + (RotL64(aWandererH, 34U) ^ aWandererE);
            aCarry = aCarry + (aWandererA ^ RotL64(aWandererG, 5U));
            aCarry = aCarry + RotL64(aWandererF, 57U);
            aCarry = aCarry + RotL64(aIngress, 39U);
            aCarry = TwistMix64::DiffuseC(aCarry);
            //
            aExpandLaneB[S_BLOCK1 - aIndex] = aIngress;
        }
    
        // kdf_b_loop_d loop 3
        // ingress from: aExpandLaneB, aWorkLaneD, aFireLaneC
        // ingress directions: aExpandLaneB forward forced, aWorkLaneD forward forced, aFireLaneC forward/backward random
        // cross from: aExpandLaneA, aWorkLaneB, aOperationLaneD
        // cross directions: aExpandLaneA backward forced, aWorkLaneB backward forced, aOperationLaneD backward/forward random
        // write to: aExpandLaneC
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aExpandLaneB[((aIndex + 23549U)) & S_BLOCK1], 19U) ^ RotL64(aWorkLaneD[((aIndex + 23572U)) & S_BLOCK1], 27U));
            aIngress ^= RotL64(aFireLaneC[((aIndex + 20971U)) & S_BLOCK1], 50U);
            aIngress = TwistMix64::DiffuseC(((aIngress ^ aDomainWordIngress) ^ aNonceWordM));
            //
            aCross = (RotL64(aExpandLaneA[((S_BLOCK1 - aIndex + 19636U)) & S_BLOCK1], 40U) ^ RotL64(aWorkLaneB[((S_BLOCK1 - aIndex + 18192U)) & S_BLOCK1], 29U));
            aCross ^= RotL64(aOperationLaneD[((S_BLOCK1 - aIndex + 17044U)) & S_BLOCK1], 21U);
            aCross = TwistMix64::DiffuseA(((aCross ^ aDomainWordCross) ^ aNonceWordD));
            //
            aScatter = (RotL64(aCarry, 14U) + RotL64(aIngress, 29U)) ^ (RotL64(aPrevious, 57U) + RotL64(aCross, 41U));
            aScatter = TwistMix64::DiffuseB(((aScatter ^ aDomainWordScatter) ^ aNonceWordI));
            //
            aOrbiterG = ((aWandererH + RotL64(aScatter, 44U)) + RotL64(aCarry, 23U)) + 12311607308490066301U;
            aOrbiterE = (aWandererD + RotL64(aPrevious, 57U)) + 13100864684740679846U;
            aOrbiterD = ((aWandererB + RotL64(aIngress, 3U)) + 13697304189274329704U) + aNonceWordF;
            aOrbiterI = ((aWandererI + RotL64(aCross, 23U)) + RotL64(aCarry, 11U)) + 9047976902871216732U;
            aOrbiterA = ((((aWandererK + RotL64(aPrevious, 51U)) + RotL64(aCarry, 41U)) + 2147897579538537888U) + aOrbiterAssignSaltE[(((31U - aIndex) + 10U)) & S_SALT1]) + aNonceWordC;
            aOrbiterK = ((aWandererA + RotL64(aScatter, 11U)) + 2072444829390996142U) + aOrbiterAssignSaltB[(((31U - aIndex) + 5U)) & S_SALT1];
            aOrbiterF = (aWandererF + RotL64(aCross, 35U)) + 2129307836981020908U;
            //
            aOrbiterG = (aOrbiterG + aOrbiterE) + 10663145333751112064U;
            aOrbiterD = (((aOrbiterD ^ aOrbiterG) ^ 15019844390503785459U) ^ aOrbiterUpdateSaltC[(((31U - aIndex) + 22U)) & S_SALT1]) ^ aNonceWordB;
            aOrbiterD = RotL64((aOrbiterD * 7442321463110790449U), 35U);
            //
            aOrbiterI = (aOrbiterI + aOrbiterA) + 5460865577557928142U;
            aOrbiterG = (aOrbiterG ^ aOrbiterI) ^ 15806522559993224197U;
            aOrbiterG = RotL64((aOrbiterG * 8722932687972240099U), 29U);
            //
            aOrbiterK = (aOrbiterK + aOrbiterI) + 6361113778657833389U;
            aOrbiterA = (aOrbiterA ^ aOrbiterK) ^ 8306013884615042570U;
            aOrbiterA = RotL64((aOrbiterA * 8234258702656728667U), 41U);
            //
            aOrbiterF = (((aOrbiterF + aOrbiterK) + 4038420580499706912U) + aOrbiterUpdateSaltF[((aIndex + 11U)) & S_SALT1]) + aNonceWordN;
            aOrbiterI = (aOrbiterI ^ aOrbiterF) ^ 11908091484457158973U;
            aOrbiterI = RotL64((aOrbiterI * 3964111175645156719U), 47U);
            //
            aOrbiterE = (aOrbiterE + aOrbiterD) + 11133912466611921250U;
            aOrbiterF = (((aOrbiterF ^ aOrbiterE) ^ 2469227904206936928U) ^ aOrbiterUpdateSaltA[((aIndex + 19U)) & S_SALT1]) ^ aNonceWordO;
            aOrbiterF = RotL64((aOrbiterF * 2704438771198001599U), 19U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterF) + 13234017916788297295U;
            aOrbiterK = ((aOrbiterK ^ aOrbiterD) ^ 9061117693840451988U) ^ aOrbiterUpdateSaltB[(((31U - aIndex) + 15U)) & S_SALT1];
            aOrbiterK = RotL64((aOrbiterK * 3637440416741459419U), 13U);
            //
            aOrbiterA = (aOrbiterA + aOrbiterG) + 12013423690843812324U;
            aOrbiterE = (aOrbiterE ^ aOrbiterA) ^ 14371779015144617412U;
            aOrbiterE = RotL64((aOrbiterE * 3359568073302062667U), 3U);
            //
            aIngress = RotL64(aOrbiterK, 20U) ^ aOrbiterE;
            aIngress = aIngress + (RotL64(aOrbiterA, 27U) ^ aOrbiterF);
            aIngress = aIngress + (RotL64(aOrbiterD, 5U) ^ aOrbiterG);
            aIngress = aIngress + RotL64(aOrbiterI, 41U);
            aIngress = TwistMix64::DiffuseB((aIngress + aScatter));
            //
            aWandererB = aWandererB ^ ((RotL64(aScatter, 35U) + aOrbiterF) + RotL64(aOrbiterG, 29U));
            aWandererF = aWandererF + (((RotL64(aPrevious, 11U) + aOrbiterE) + RotL64(aOrbiterF, 21U)) + aNonceWordK);
            aWandererD = aWandererD ^ ((((RotL64(aCross, 60U) + aOrbiterI) + RotL64(aOrbiterF, 47U)) + aNonceWordL) + aWandererUpdateSaltE[(((31U - aIndex) + 27U)) & S_SALT1]);
            aWandererA = aWandererA + ((((RotL64(aIngress, 47U) + RotL64(aOrbiterK, 5U)) + aOrbiterI) + RotL64(aCarry, 35U)) + aWandererUpdateSaltC[(((31U - aIndex) + 12U)) & S_SALT1]);
            aWandererH = aWandererH ^ (((RotL64(aCross, 29U) + aOrbiterA) + RotL64(aOrbiterE, 13U)) + aNonceWordG);
            aWandererI = aWandererI + ((((RotL64(aPrevious, 41U) + aOrbiterK) + RotL64(aOrbiterD, 60U)) + RotL64(aCarry, 57U)) + aNonceWordJ);
            aWandererK = aWandererK ^ ((RotL64(aIngress, 23U) + aOrbiterK) + RotL64(aOrbiterF, 35U));
            //
            aCarry = aCarry + (RotL64(aWandererI, 47U) ^ aWandererA);
            aCarry = aCarry + (aWandererK ^ RotL64(aWandererD, 26U));
            aCarry = aCarry + (RotL64(aWandererF, 13U) ^ aWandererH);
            aCarry = aCarry + RotL64(aWandererB, 5U);
            aCarry = aCarry + RotL64(aIngress, 19U);
            aCarry = TwistMix64::DiffuseA(aCarry);
            //
            aExpandLaneC[aIndex] = aIngress;
        }
    
        // kdf_b_loop_d loop 4
        // ingress from: aExpandLaneC, aExpandLaneA, aOperationLaneC
        // ingress directions: aExpandLaneC forward forced, aExpandLaneA forward forced, aOperationLaneC forward/backward random
        // cross from: aExpandLaneB, aWorkLaneC, aOperationLaneB
        // cross directions: aExpandLaneB backward forced, aWorkLaneC backward forced, aOperationLaneB backward/forward random
        // write to: aExpandLaneD
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aExpandLaneC[((aIndex + 31395U)) & S_BLOCK1], 46U) ^ RotL64(aExpandLaneA[((aIndex + 26166U)) & S_BLOCK1], 19U));
            aIngress ^= RotL64(aOperationLaneC[((S_BLOCK1 - aIndex + 26777U)) & S_BLOCK1], 29U);
            aIngress = TwistMix64::DiffuseC(((aIngress ^ aDomainWordIngress) ^ aNonceWordC));
            //
            aCross = (RotL64(aExpandLaneB[((S_BLOCK1 - aIndex + 25753U)) & S_BLOCK1], 13U) ^ RotL64(aWorkLaneC[((S_BLOCK1 - aIndex + 32245U)) & S_BLOCK1], 51U));
            aCross ^= RotL64(aOperationLaneB[((aIndex + 32647U)) & S_BLOCK1], 3U);
            aCross = TwistMix64::DiffuseB(((aCross ^ aDomainWordCross) ^ aNonceWordF));
            //
            aScatter = (RotL64(aIngress, 5U) + RotL64(aCarry, 38U)) + (RotL64(aPrevious, 23U) ^ RotL64(aCross, 53U));
            aScatter = TwistMix64::DiffuseA(((aScatter ^ aDomainWordScatter) ^ aNonceWordN));
            //
            aOrbiterH = (((aWandererK + RotL64(aScatter, 11U)) + RotL64(aCarry, 41U)) + 16200278595895089008U) + aNonceWordB;
            aOrbiterF = (((aWandererD + RotL64(aIngress, 23U)) + 1029614154810465897U) + aOrbiterAssignSaltC[(((31U - aIndex) + 11U)) & S_SALT1]) + aNonceWordM;
            aOrbiterB = ((aWandererF + RotL64(aCross, 58U)) + RotL64(aCarry, 23U)) + 7129562468705441295U;
            aOrbiterJ = (aWandererI + RotL64(aPrevious, 29U)) + 14388903902433951274U;
            aOrbiterD = (((aWandererC + RotL64(aCross, 51U)) + 1013568949315967455U) + aOrbiterAssignSaltD[(((31U - aIndex) + 23U)) & S_SALT1]) + aNonceWordE;
            aOrbiterC = (aWandererH + RotL64(aScatter, 43U)) + 3128823373497815651U;
            aOrbiterK = ((aWandererE + RotL64(aPrevious, 3U)) + RotL64(aCarry, 57U)) + 14525694606889470589U;
            //
            aOrbiterH = (aOrbiterH + aOrbiterF) + 14443983602196782887U;
            aOrbiterB = ((aOrbiterB ^ aOrbiterH) ^ 12244220415328641190U) ^ aOrbiterUpdateSaltC[((aIndex + 6U)) & S_SALT1];
            aOrbiterB = RotL64((aOrbiterB * 15052949098014803181U), 11U);
            //
            aOrbiterF = (((aOrbiterF + aOrbiterB) + 10477159225338766614U) + aOrbiterUpdateSaltD[((aIndex + 16U)) & S_SALT1]) + aNonceWordO;
            aOrbiterJ = (aOrbiterJ ^ aOrbiterF) ^ 2842870123078131566U;
            aOrbiterJ = RotL64((aOrbiterJ * 11522265477555954071U), 27U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterC) + 8621138818955849917U;
            aOrbiterH = (aOrbiterH ^ aOrbiterD) ^ 5038396344400303181U;
            aOrbiterH = RotL64((aOrbiterH * 14636756322207385447U), 21U);
            //
            aOrbiterK = (aOrbiterK + aOrbiterD) + 2768613802894372496U;
            aOrbiterC = ((aOrbiterC ^ aOrbiterK) ^ 2027754864051410015U) ^ aNonceWordP;
            aOrbiterC = RotL64((aOrbiterC * 2461322540050569287U), 3U);
            //
            aOrbiterB = (((aOrbiterB + aOrbiterJ) + 2848088309172056399U) + aOrbiterUpdateSaltE[((aIndex + 8U)) & S_SALT1]) + aNonceWordI;
            aOrbiterK = (aOrbiterK ^ aOrbiterB) ^ 15017458513904884651U;
            aOrbiterK = RotL64((aOrbiterK * 9926904679902843055U), 37U);
            //
            aOrbiterJ = (aOrbiterJ + aOrbiterK) + 9079797279596336139U;
            aOrbiterD = (aOrbiterD ^ aOrbiterJ) ^ 15424866642305110811U;
            aOrbiterD = RotL64((aOrbiterD * 12912331089970158845U), 43U);
            //
            aOrbiterC = (((aOrbiterC + aOrbiterH) + 13751764050290602740U) + aOrbiterUpdateSaltA[((aIndex + 3U)) & S_SALT1]) + aNonceWordG;
            aOrbiterF = (aOrbiterF ^ aOrbiterC) ^ 7694557131324740282U;
            aOrbiterF = RotL64((aOrbiterF * 14980807690491467023U), 51U);
            //
            aIngress = aOrbiterB ^ RotL64(aOrbiterK, 3U);
            aIngress = aIngress + (RotL64(aOrbiterD, 35U) ^ aOrbiterF);
            aIngress = aIngress + (RotL64(aOrbiterH, 11U) ^ aOrbiterJ);
            aIngress = aIngress + RotL64(aOrbiterC, 19U);
            aIngress = TwistMix64::DiffuseC((aIngress + aScatter));
            //
            aWandererD = aWandererD ^ ((RotL64(aPrevious, 47U) + aOrbiterK) + RotL64(aOrbiterB, 11U));
            aWandererH = aWandererH + (((RotL64(aIngress, 26U) + RotL64(aOrbiterH, 20U)) + aOrbiterD) + RotL64(aCarry, 57U));
            aWandererC = aWandererC ^ ((((RotL64(aScatter, 35U) + RotL64(aOrbiterK, 51U)) + aOrbiterC) + aNonceWordD) + aWandererUpdateSaltB[((aIndex + 25U)) & S_SALT1]);
            aWandererE = aWandererE + (((((RotL64(aCross, 19U) + aOrbiterK) + RotL64(aOrbiterH, 37U)) + RotL64(aCarry, 39U)) + aNonceWordA) + aWandererUpdateSaltA[(((31U - aIndex) + 19U)) & S_SALT1]);
            aWandererI = aWandererI ^ ((RotL64(aIngress, 3U) + RotL64(aOrbiterB, 27U)) + aOrbiterJ);
            aWandererF = aWandererF + (((RotL64(aScatter, 53U) + RotL64(aOrbiterK, 57U)) + aOrbiterD) + aNonceWordL);
            aWandererK = aWandererK ^ (((RotL64(aCross, 41U) + aOrbiterJ) + RotL64(aOrbiterF, 5U)) + aNonceWordJ);
            //
            aCarry = aCarry + (aWandererD ^ RotL64(aWandererE, 23U));
            aCarry = aCarry + (RotL64(aWandererC, 4U) ^ aWandererK);
            aCarry = aCarry + (RotL64(aWandererH, 39U) ^ aWandererF);
            aCarry = aCarry + RotL64(aWandererI, 47U);
            aCarry = aCarry + RotL64(aIngress, 13U);
            aCarry = TwistMix64::DiffuseB(aCarry);
            //
            aExpandLaneD[S_BLOCK1 - aIndex] = aIngress;
        }
    }
    // KDF_B_D kdf_b_loop_d (end)
    *pPrevious = aPrevious;
    *pIngress = aIngress;
    *pCarry = aCarry;
    *pWandererA = aWandererA;
    *pWandererB = aWandererB;
    *pWandererC = aWandererC;
    *pWandererD = aWandererD;
    *pWandererE = aWandererE;
    *pWandererF = aWandererF;
    *pWandererG = aWandererG;
    *pWandererH = aWandererH;
    *pWandererI = aWandererI;
    *pWandererJ = aWandererJ;
    *pWandererK = aWandererK;
}

void TwistExpander_Exercea_Arx::Seed_A(TwistWorkSpace *pWorkSpace,
                     std::uint64_t pNonce,
                     std::uint64_t *pPrevious,
                     std::uint64_t *pIngress,
                     std::uint64_t *pCarry,
                     std::uint64_t *pWandererA,
                     std::uint64_t *pWandererB,
                     std::uint64_t *pWandererC,
                     std::uint64_t *pWandererD,
                     std::uint64_t *pWandererE,
                     std::uint64_t *pWandererF,
                     std::uint64_t *pWandererG,
                     std::uint64_t *pWandererH,
                     std::uint64_t *pWandererI,
                     std::uint64_t *pWandererJ,
                     std::uint64_t *pWandererK) {
    [[maybe_unused]] std::uint8_t *aExpandLaneA = pWorkSpace->mExpansionLaneA;
    [[maybe_unused]] std::uint8_t *aExpandLaneB = pWorkSpace->mExpansionLaneB;
    [[maybe_unused]] std::uint8_t *aExpandLaneC = pWorkSpace->mExpansionLaneC;
    [[maybe_unused]] std::uint8_t *aExpandLaneD = pWorkSpace->mExpansionLaneD;
    [[maybe_unused]] std::uint8_t *aWorkLaneA = pWorkSpace->mWorkLaneA;
    [[maybe_unused]] std::uint8_t *aWorkLaneB = pWorkSpace->mWorkLaneB;
    [[maybe_unused]] std::uint8_t *aWorkLaneC = pWorkSpace->mWorkLaneC;
    [[maybe_unused]] std::uint8_t *aWorkLaneD = pWorkSpace->mWorkLaneD;
    [[maybe_unused]] std::uint8_t *aFireLaneA = pWorkSpace->mFireLaneA;
    [[maybe_unused]] std::uint8_t *aFireLaneB = pWorkSpace->mFireLaneB;
    [[maybe_unused]] std::uint8_t *aFireLaneC = pWorkSpace->mFireLaneC;
    [[maybe_unused]] std::uint8_t *aFireLaneD = pWorkSpace->mFireLaneD;
    [[maybe_unused]] std::uint8_t *aKeyRowReadA = &(pWorkSpace->mKeyBoxA[H_KEY - 1][0]);
    [[maybe_unused]] std::uint8_t *aKeyRowReadB = &(pWorkSpace->mKeyBoxB[H_KEY - 1][0]);
    [[maybe_unused]] std::uint64_t *aPhaseEOrbiterAssignSaltA = pWorkSpace->mDomainBundle.mPhaseESalts.mOrbiterAssign.mSaltA;
    [[maybe_unused]] std::uint64_t *aPhaseEOrbiterAssignSaltC = pWorkSpace->mDomainBundle.mPhaseESalts.mOrbiterAssign.mSaltC;
    [[maybe_unused]] std::uint64_t *aPhaseEOrbiterAssignSaltD = pWorkSpace->mDomainBundle.mPhaseESalts.mOrbiterAssign.mSaltD;
    [[maybe_unused]] std::uint64_t *aPhaseEOrbiterAssignSaltE = pWorkSpace->mDomainBundle.mPhaseESalts.mOrbiterAssign.mSaltE;
    [[maybe_unused]] std::uint64_t *aPhaseEOrbiterAssignSaltF = pWorkSpace->mDomainBundle.mPhaseESalts.mOrbiterAssign.mSaltF;
    [[maybe_unused]] std::uint64_t *aPhaseEOrbiterUpdateSaltA = pWorkSpace->mDomainBundle.mPhaseESalts.mOrbiterUpdate.mSaltA;
    [[maybe_unused]] std::uint64_t *aPhaseEOrbiterUpdateSaltB = pWorkSpace->mDomainBundle.mPhaseESalts.mOrbiterUpdate.mSaltB;
    [[maybe_unused]] std::uint64_t *aPhaseEOrbiterUpdateSaltC = pWorkSpace->mDomainBundle.mPhaseESalts.mOrbiterUpdate.mSaltC;
    [[maybe_unused]] std::uint64_t *aPhaseEOrbiterUpdateSaltD = pWorkSpace->mDomainBundle.mPhaseESalts.mOrbiterUpdate.mSaltD;
    [[maybe_unused]] std::uint64_t *aPhaseEOrbiterUpdateSaltE = pWorkSpace->mDomainBundle.mPhaseESalts.mOrbiterUpdate.mSaltE;
    [[maybe_unused]] std::uint64_t *aPhaseEOrbiterUpdateSaltF = pWorkSpace->mDomainBundle.mPhaseESalts.mOrbiterUpdate.mSaltF;
    [[maybe_unused]] std::uint64_t *aPhaseEWandererUpdateSaltA = pWorkSpace->mDomainBundle.mPhaseESalts.mWandererUpdate.mSaltA;
    [[maybe_unused]] std::uint64_t *aPhaseEWandererUpdateSaltB = pWorkSpace->mDomainBundle.mPhaseESalts.mWandererUpdate.mSaltB;
    [[maybe_unused]] std::uint64_t *aPhaseEWandererUpdateSaltC = pWorkSpace->mDomainBundle.mPhaseESalts.mWandererUpdate.mSaltC;
    [[maybe_unused]] std::uint64_t *aPhaseEWandererUpdateSaltE = pWorkSpace->mDomainBundle.mPhaseESalts.mWandererUpdate.mSaltE;
    [[maybe_unused]] std::uint64_t *aPhaseFOrbiterAssignSaltB = pWorkSpace->mDomainBundle.mPhaseFSalts.mOrbiterAssign.mSaltB;
    [[maybe_unused]] std::uint64_t *aPhaseFOrbiterAssignSaltD = pWorkSpace->mDomainBundle.mPhaseFSalts.mOrbiterAssign.mSaltD;
    [[maybe_unused]] std::uint64_t *aPhaseFOrbiterAssignSaltE = pWorkSpace->mDomainBundle.mPhaseFSalts.mOrbiterAssign.mSaltE;
    [[maybe_unused]] std::uint64_t *aPhaseFOrbiterAssignSaltF = pWorkSpace->mDomainBundle.mPhaseFSalts.mOrbiterAssign.mSaltF;
    [[maybe_unused]] std::uint64_t *aPhaseFOrbiterUpdateSaltA = pWorkSpace->mDomainBundle.mPhaseFSalts.mOrbiterUpdate.mSaltA;
    [[maybe_unused]] std::uint64_t *aPhaseFOrbiterUpdateSaltB = pWorkSpace->mDomainBundle.mPhaseFSalts.mOrbiterUpdate.mSaltB;
    [[maybe_unused]] std::uint64_t *aPhaseFOrbiterUpdateSaltC = pWorkSpace->mDomainBundle.mPhaseFSalts.mOrbiterUpdate.mSaltC;
    [[maybe_unused]] std::uint64_t *aPhaseFOrbiterUpdateSaltD = pWorkSpace->mDomainBundle.mPhaseFSalts.mOrbiterUpdate.mSaltD;
    [[maybe_unused]] std::uint64_t *aPhaseFOrbiterUpdateSaltE = pWorkSpace->mDomainBundle.mPhaseFSalts.mOrbiterUpdate.mSaltE;
    [[maybe_unused]] std::uint64_t *aPhaseFOrbiterUpdateSaltF = pWorkSpace->mDomainBundle.mPhaseFSalts.mOrbiterUpdate.mSaltF;
    [[maybe_unused]] std::uint64_t *aPhaseFWandererUpdateSaltA = pWorkSpace->mDomainBundle.mPhaseFSalts.mWandererUpdate.mSaltA;
    [[maybe_unused]] std::uint64_t *aPhaseFWandererUpdateSaltB = pWorkSpace->mDomainBundle.mPhaseFSalts.mWandererUpdate.mSaltB;
    [[maybe_unused]] std::uint64_t *aPhaseFWandererUpdateSaltD = pWorkSpace->mDomainBundle.mPhaseFSalts.mWandererUpdate.mSaltD;
    [[maybe_unused]] std::uint64_t *aPhaseGOrbiterAssignSaltA = pWorkSpace->mDomainBundle.mPhaseGSalts.mOrbiterAssign.mSaltA;
    [[maybe_unused]] std::uint64_t *aPhaseGOrbiterAssignSaltC = pWorkSpace->mDomainBundle.mPhaseGSalts.mOrbiterAssign.mSaltC;
    [[maybe_unused]] std::uint64_t *aPhaseGOrbiterAssignSaltD = pWorkSpace->mDomainBundle.mPhaseGSalts.mOrbiterAssign.mSaltD;
    [[maybe_unused]] std::uint64_t *aPhaseGOrbiterAssignSaltF = pWorkSpace->mDomainBundle.mPhaseGSalts.mOrbiterAssign.mSaltF;
    [[maybe_unused]] std::uint64_t *aPhaseGOrbiterUpdateSaltA = pWorkSpace->mDomainBundle.mPhaseGSalts.mOrbiterUpdate.mSaltA;
    [[maybe_unused]] std::uint64_t *aPhaseGOrbiterUpdateSaltB = pWorkSpace->mDomainBundle.mPhaseGSalts.mOrbiterUpdate.mSaltB;
    [[maybe_unused]] std::uint64_t *aPhaseGOrbiterUpdateSaltC = pWorkSpace->mDomainBundle.mPhaseGSalts.mOrbiterUpdate.mSaltC;
    [[maybe_unused]] std::uint64_t *aPhaseGOrbiterUpdateSaltD = pWorkSpace->mDomainBundle.mPhaseGSalts.mOrbiterUpdate.mSaltD;
    [[maybe_unused]] std::uint64_t *aPhaseGOrbiterUpdateSaltE = pWorkSpace->mDomainBundle.mPhaseGSalts.mOrbiterUpdate.mSaltE;
    [[maybe_unused]] std::uint64_t *aPhaseGOrbiterUpdateSaltF = pWorkSpace->mDomainBundle.mPhaseGSalts.mOrbiterUpdate.mSaltF;
    [[maybe_unused]] std::uint64_t *aPhaseGWandererUpdateSaltA = pWorkSpace->mDomainBundle.mPhaseGSalts.mWandererUpdate.mSaltA;
    [[maybe_unused]] std::uint64_t *aPhaseGWandererUpdateSaltB = pWorkSpace->mDomainBundle.mPhaseGSalts.mWandererUpdate.mSaltB;
    [[maybe_unused]] std::uint64_t *aPhaseGWandererUpdateSaltC = pWorkSpace->mDomainBundle.mPhaseGSalts.mWandererUpdate.mSaltC;
    [[maybe_unused]] std::uint64_t *aPhaseGWandererUpdateSaltF = pWorkSpace->mDomainBundle.mPhaseGSalts.mWandererUpdate.mSaltF;
    [[maybe_unused]] std::uint64_t *aPhaseHOrbiterAssignSaltB = pWorkSpace->mDomainBundle.mPhaseHSalts.mOrbiterAssign.mSaltB;
    [[maybe_unused]] std::uint64_t *aPhaseHOrbiterAssignSaltC = pWorkSpace->mDomainBundle.mPhaseHSalts.mOrbiterAssign.mSaltC;
    [[maybe_unused]] std::uint64_t *aPhaseHOrbiterAssignSaltD = pWorkSpace->mDomainBundle.mPhaseHSalts.mOrbiterAssign.mSaltD;
    [[maybe_unused]] std::uint64_t *aPhaseHOrbiterAssignSaltE = pWorkSpace->mDomainBundle.mPhaseHSalts.mOrbiterAssign.mSaltE;
    [[maybe_unused]] std::uint64_t *aPhaseHOrbiterUpdateSaltA = pWorkSpace->mDomainBundle.mPhaseHSalts.mOrbiterUpdate.mSaltA;
    [[maybe_unused]] std::uint64_t *aPhaseHOrbiterUpdateSaltB = pWorkSpace->mDomainBundle.mPhaseHSalts.mOrbiterUpdate.mSaltB;
    [[maybe_unused]] std::uint64_t *aPhaseHOrbiterUpdateSaltC = pWorkSpace->mDomainBundle.mPhaseHSalts.mOrbiterUpdate.mSaltC;
    [[maybe_unused]] std::uint64_t *aPhaseHOrbiterUpdateSaltD = pWorkSpace->mDomainBundle.mPhaseHSalts.mOrbiterUpdate.mSaltD;
    [[maybe_unused]] std::uint64_t *aPhaseHOrbiterUpdateSaltE = pWorkSpace->mDomainBundle.mPhaseHSalts.mOrbiterUpdate.mSaltE;
    [[maybe_unused]] std::uint64_t *aPhaseHOrbiterUpdateSaltF = pWorkSpace->mDomainBundle.mPhaseHSalts.mOrbiterUpdate.mSaltF;
    [[maybe_unused]] std::uint64_t *aPhaseHWandererUpdateSaltA = pWorkSpace->mDomainBundle.mPhaseHSalts.mWandererUpdate.mSaltA;
    [[maybe_unused]] std::uint64_t *aPhaseHWandererUpdateSaltB = pWorkSpace->mDomainBundle.mPhaseHSalts.mWandererUpdate.mSaltB;
    [[maybe_unused]] std::uint64_t *aPhaseHWandererUpdateSaltD = pWorkSpace->mDomainBundle.mPhaseHSalts.mWandererUpdate.mSaltD;
    [[maybe_unused]] std::uint64_t *aPhaseHWandererUpdateSaltE = pWorkSpace->mDomainBundle.mPhaseHSalts.mWandererUpdate.mSaltE;
    const std::uint64_t &aPhaseEDomainWordIngress = pWorkSpace->mDomainBundle.mPhaseEConstants.mIngress;
    const std::uint64_t &aPhaseEDomainWordScatter = pWorkSpace->mDomainBundle.mPhaseEConstants.mScatter;
    const std::uint64_t &aPhaseEDomainWordCross = pWorkSpace->mDomainBundle.mPhaseEConstants.mCross;
    const std::uint64_t &aPhaseFDomainWordIngress = pWorkSpace->mDomainBundle.mPhaseFConstants.mIngress;
    const std::uint64_t &aPhaseFDomainWordScatter = pWorkSpace->mDomainBundle.mPhaseFConstants.mScatter;
    const std::uint64_t &aPhaseFDomainWordCross = pWorkSpace->mDomainBundle.mPhaseFConstants.mCross;
    const std::uint64_t &aPhaseGDomainWordIngress = pWorkSpace->mDomainBundle.mPhaseGConstants.mIngress;
    const std::uint64_t &aPhaseGDomainWordScatter = pWorkSpace->mDomainBundle.mPhaseGConstants.mScatter;
    const std::uint64_t &aPhaseGDomainWordCross = pWorkSpace->mDomainBundle.mPhaseGConstants.mCross;
    const std::uint64_t &aPhaseHDomainWordIngress = pWorkSpace->mDomainBundle.mPhaseHConstants.mIngress;
    const std::uint64_t &aPhaseHDomainWordScatter = pWorkSpace->mDomainBundle.mPhaseHConstants.mScatter;
    const std::uint64_t &aPhaseHDomainWordCross = pWorkSpace->mDomainBundle.mPhaseHConstants.mCross;
    std::uint64_t aCross = 0; std::uint64_t aScatter = 0;

    std::uint64_t aOrbiterA = 0; std::uint64_t aOrbiterB = 0; std::uint64_t aOrbiterC = 0; std::uint64_t aOrbiterD = 0;
    std::uint64_t aOrbiterE = 0; std::uint64_t aOrbiterF = 0; std::uint64_t aOrbiterG = 0; std::uint64_t aOrbiterH = 0;
    std::uint64_t aOrbiterI = 0; std::uint64_t aOrbiterJ = 0; std::uint64_t aOrbiterK = 0;

    // [seed arx]
    [[maybe_unused]] std::uint8_t *mSource = pWorkSpace->mSource;
    std::uint64_t aPrevious = *pPrevious;
    std::uint64_t aIngress = *pIngress;
    std::uint64_t aCarry = *pCarry;
    std::uint64_t aWandererA = *pWandererA;
    std::uint64_t aWandererB = *pWandererB;
    std::uint64_t aWandererC = *pWandererC;
    std::uint64_t aWandererD = *pWandererD;
    std::uint64_t aWandererE = *pWandererE;
    std::uint64_t aWandererF = *pWandererF;
    std::uint64_t aWandererG = *pWandererG;
    std::uint64_t aWandererH = *pWandererH;
    std::uint64_t aWandererI = *pWandererI;
    std::uint64_t aWandererJ = *pWandererJ;
    std::uint64_t aWandererK = *pWandererK;
    std::uint64_t aNonceWordA = TwistMix64::DiffuseC(pNonce * 0xBE534B9A87A1B02BULL + 0xFBD95F42CCCE50CBULL);
    std::uint64_t aNonceWordB = TwistMix64::DiffuseB(pNonce * 0xF82BA6E3D34924D5ULL + 0xE19538E1A946259BULL);
    std::uint64_t aNonceWordC = TwistMix64::DiffuseC(pNonce * 0x9AFFF27932E41DD7ULL + 0xECCE6877AEC82AE7ULL);
    std::uint64_t aNonceWordD = TwistMix64::DiffuseC(pNonce * 0xECBF2DECC9014139ULL + 0xE69E00B4179CB942ULL);
    std::uint64_t aNonceWordE = TwistMix64::DiffuseC(pNonce * 0xBB4D43FFB256EE6FULL + 0x97AF9C15D2C2F21FULL);
    std::uint64_t aNonceWordF = TwistMix64::DiffuseB(pNonce * 0xFD0D2CB8853B31E5ULL + 0xD11CA80D1E5A462DULL);
    std::uint64_t aNonceWordG = TwistMix64::DiffuseC(pNonce * 0xB3124D95CEFD5471ULL + 0x8F243DC464676A52ULL);
    std::uint64_t aNonceWordH = TwistMix64::DiffuseA(pNonce * 0xA40422530E168FB9ULL + 0x9F85D517C6547C9CULL);
    std::uint64_t aNonceWordI = TwistMix64::DiffuseB(pNonce * 0x818EBBCB0B84DCE9ULL + 0xAA0162C7CEAEE240ULL);
    std::uint64_t aNonceWordJ = TwistMix64::DiffuseC(pNonce * 0xBE70B7D3F0849BE3ULL + 0xE39DBE33C690F2BFULL);
    std::uint64_t aNonceWordK = TwistMix64::DiffuseA(pNonce * 0xA56647CFD1299AFDULL + 0xDD75448B9E420B1AULL);
    std::uint64_t aNonceWordL = TwistMix64::DiffuseC(pNonce * 0x99C450D07DFE59A9ULL + 0x8B166A8EC539F1FFULL);
    std::uint64_t aNonceWordM = TwistMix64::DiffuseA(pNonce * 0xF4D277CC253359DBULL + 0xB5C4775EC2B516B0ULL);
    std::uint64_t aNonceWordN = TwistMix64::DiffuseA(pNonce * 0x9D03E3C0D553E20FULL + 0xAC8BDE14B67DCFC1ULL);
    std::uint64_t aNonceWordO = TwistMix64::DiffuseC(pNonce * 0x9518BE69649DF0A3ULL + 0xB3FB77922F5C4B16ULL);
    std::uint64_t aNonceWordP = TwistMix64::DiffuseA(pNonce * 0x8BAD4D208768E2E3ULL + 0xB4778FDB7E207DDCULL);
    // GSeedRunSeed_A seed_loop_a (start)
    {
        // GSeedRunSeed_A seed_loop_a lane group
        // read from: aKeyRowReadA, aKeyRowReadB, mSource, aWorkLaneA, aWorkLaneB, aWorkLaneC, aWorkLaneD, aFireLaneA, aFireLaneB, aFireLaneC, aFireLaneD, aExpandLaneA, aExpandLaneB, aExpandLaneC
        // write to: aWorkLaneA, aWorkLaneB, aWorkLaneC, aWorkLaneD, aFireLaneA, aFireLaneB, aFireLaneC, aFireLaneD, aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD
    
        // seed_loop_a loop 1
        // ingress from: aKeyRowReadA, aKeyRowReadB
        // ingress directions: aKeyRowReadA forward forced, aKeyRowReadB forward/backward random
        // cross from: aKeyRowReadA, mSource
        // cross directions: aKeyRowReadA backward forced, mSource backward/forward random
        // write to: aWorkLaneA
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = RotL64(aKeyRowReadA[((aIndex + 66U)) & W_KEY1], 23U) ^ RotL64(aKeyRowReadB[((aIndex + 1649U)) & W_KEY1], 36U);
            aIngress = TwistMix64::DiffuseA(((aIngress ^ aPhaseEDomainWordIngress) ^ aNonceWordI));
            //
            aCross = RotL64(aKeyRowReadA[(((2047U - aIndex) + 2382U)) & W_KEY1], 4U) ^ RotL64(mSource[((S_BLOCK1 - aIndex + 1638U)) & S_BLOCK1], 43U);
            aCross = TwistMix64::DiffuseA(((aCross ^ aPhaseEDomainWordCross) ^ aNonceWordM));
            //
            aScatter = (RotL64(aPrevious, 35U) + RotL64(aCarry, 5U)) + (RotL64(aIngress, 23U) ^ RotL64(aCross, 52U));
            aScatter = TwistMix64::DiffuseB(((aScatter ^ aPhaseEDomainWordScatter) ^ aNonceWordI));
            //
            aOrbiterH = ((aWandererK + RotL64(aPrevious, 47U)) + RotL64(aCarry, 53U)) + 6654158889644956636U;
            aOrbiterF = ((aWandererA + RotL64(aIngress, 11U)) + 9045779659363991870U) + aNonceWordF;
            aOrbiterG = ((aWandererF + RotL64(aScatter, 27U)) + 3888897662136993491U) + aNonceWordB;
            aOrbiterD = ((aWandererE + RotL64(aCross, 19U)) + 6882016842864459345U) + aPhaseEOrbiterAssignSaltD[(((31U - aIndex) + 9U)) & S_SALT1];
            aOrbiterE = ((aWandererG + RotL64(aScatter, 4U)) + RotL64(aCarry, 11U)) + 15601891715956172291U;
            aOrbiterB = ((aWandererD + RotL64(aPrevious, 37U)) + 5176811598629335350U) + aPhaseEOrbiterAssignSaltE[(((31U - aIndex) + 21U)) & S_SALT1];
            aOrbiterK = ((aWandererC + RotL64(aIngress, 53U)) + RotL64(aCarry, 23U)) + 12519945150889074325U;
            //
            aOrbiterH = (aOrbiterH + aOrbiterF) + 4552583214397603278U;
            aOrbiterG = (aOrbiterG ^ aOrbiterH) ^ 14225482701804864688U;
            aOrbiterG = RotL64((aOrbiterG * 8526052833180466359U), 13U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterG) + 5485298070606280363U;
            aOrbiterE = ((aOrbiterE ^ aOrbiterD) ^ 11237713257388094289U) ^ aNonceWordP;
            aOrbiterE = RotL64((aOrbiterE * 11032429223099413011U), 41U);
            //
            aOrbiterB = ((aOrbiterB + aOrbiterD) + 14340345895626142788U) + aNonceWordG;
            aOrbiterF = (((aOrbiterF ^ aOrbiterB) ^ 16275167270553643347U) ^ aPhaseEOrbiterUpdateSaltA[(((31U - aIndex) + 14U)) & S_SALT1]) ^ aNonceWordE;
            aOrbiterF = RotL64((aOrbiterF * 7308578867128951199U), 57U);
            //
            aOrbiterG = (aOrbiterG + aOrbiterK) + 14041860597556520250U;
            aOrbiterB = (aOrbiterB ^ aOrbiterG) ^ 1436068974197066343U;
            aOrbiterB = RotL64((aOrbiterB * 3938460345031496843U), 23U);
            //
            aOrbiterE = (aOrbiterE + aOrbiterB) + 11483155566419547004U;
            aOrbiterH = ((aOrbiterH ^ aOrbiterE) ^ 4608508534724289325U) ^ aNonceWordH;
            aOrbiterH = RotL64((aOrbiterH * 13461385011638899485U), 29U);
            //
            aOrbiterK = ((aOrbiterK + aOrbiterH) + 2389196334288832895U) + aPhaseEOrbiterUpdateSaltF[((aIndex + 19U)) & S_SALT1];
            aOrbiterD = (aOrbiterD ^ aOrbiterK) ^ 4062682330273866602U;
            aOrbiterD = RotL64((aOrbiterD * 8787682133271101901U), 3U);
            //
            aOrbiterF = ((aOrbiterF + aOrbiterE) + 5655656046585592034U) + aPhaseEOrbiterUpdateSaltB[((aIndex + 5U)) & S_SALT1];
            aOrbiterK = ((aOrbiterK ^ aOrbiterF) ^ 7977947821249746880U) ^ aPhaseEOrbiterUpdateSaltC[((aIndex + 16U)) & S_SALT1];
            aOrbiterK = RotL64((aOrbiterK * 10082104644185964787U), 47U);
            //
            aIngress = aOrbiterF ^ RotL64(aOrbiterG, 47U);
            aIngress = aIngress + (aOrbiterH ^ RotL64(aOrbiterK, 13U));
            aIngress = aIngress + (RotL64(aOrbiterB, 53U) ^ aOrbiterD);
            aIngress = aIngress + RotL64(aOrbiterE, 60U);
            aIngress = TwistMix64::DiffuseB((aIngress + aScatter));
            //
            aWandererG = aWandererG + (((RotL64(aScatter, 47U) + aOrbiterG) + RotL64(aOrbiterK, 60U)) + aNonceWordC);
            aWandererE = aWandererE ^ ((RotL64(aCross, 41U) + RotL64(aOrbiterG, 3U)) + aOrbiterF);
            aWandererK = aWandererK + (((RotL64(aPrevious, 3U) + RotL64(aOrbiterE, 29U)) + aOrbiterF) + RotL64(aCarry, 21U));
            aWandererC = aWandererC ^ ((((RotL64(aIngress, 11U) + RotL64(aOrbiterD, 37U)) + aOrbiterB) + aNonceWordL) + aPhaseEWandererUpdateSaltE[(((31U - aIndex) + 12U)) & S_SALT1]);
            aWandererF = aWandererF + (((RotL64(aCross, 29U) + aOrbiterB) + RotL64(aOrbiterG, 11U)) + RotL64(aCarry, 57U));
            aWandererA = aWandererA ^ (((RotL64(aPrevious, 20U) + RotL64(aOrbiterK, 19U)) + aOrbiterF) + aPhaseEWandererUpdateSaltC[(((31U - aIndex) + 15U)) & S_SALT1]);
            aWandererD = aWandererD + ((RotL64(aIngress, 53U) + RotL64(aOrbiterK, 43U)) + aOrbiterH);
            //
            aCarry = aCarry + (aWandererF ^ RotL64(aWandererE, 27U));
            aCarry = aCarry + (RotL64(aWandererC, 12U) ^ aWandererA);
            aCarry = aCarry + (RotL64(aWandererG, 23U) ^ aWandererK);
            aCarry = aCarry + RotL64(aWandererD, 51U);
            aCarry = aCarry + RotL64(aIngress, 19U);
            aCarry = TwistMix64::DiffuseB(aCarry);
            //
            aWorkLaneA[aIndex] = aIngress;
        }
    
        // seed_loop_a loop 2
        // ingress from: aWorkLaneA, aKeyRowReadA
        // ingress directions: aWorkLaneA forward forced, aKeyRowReadA forward/backward random
        // cross from: aKeyRowReadB, mSource
        // cross directions: aKeyRowReadB backward forced, mSource backward/forward random
        // write to: aWorkLaneB
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = RotL64(aWorkLaneA[((aIndex + 3299U)) & S_BLOCK1], 30U) ^ RotL64(aKeyRowReadA[((aIndex + 5203U)) & W_KEY1], 11U);
            aIngress = TwistMix64::DiffuseB(((aIngress ^ aPhaseEDomainWordIngress) ^ aNonceWordG));
            //
            aCross = RotL64(aKeyRowReadB[(((2047U - aIndex) + 4049U)) & W_KEY1], 21U) ^ RotL64(mSource[((S_BLOCK1 - aIndex + 4199U)) & S_BLOCK1], 51U);
            aCross = TwistMix64::DiffuseC(((aCross ^ aPhaseEDomainWordCross) ^ aNonceWordA));
            //
            aScatter = (RotL64(aCarry, 5U) + RotL64(aPrevious, 41U)) + (RotL64(aIngress, 54U) ^ RotL64(aCross, 19U));
            aScatter = TwistMix64::DiffuseC(((aScatter ^ aPhaseEDomainWordScatter) ^ aNonceWordH));
            //
            aOrbiterE = ((aWandererB + RotL64(aCross, 56U)) + 15904465836916519864U) + aNonceWordH;
            aOrbiterC = ((aWandererK + RotL64(aIngress, 11U)) + 17725629806317789307U) + aNonceWordB;
            aOrbiterA = ((aWandererF + RotL64(aPrevious, 43U)) + 13794170125914914828U) + aPhaseEOrbiterAssignSaltC[(((31U - aIndex) + 11U)) & S_SALT1];
            aOrbiterB = (((aWandererG + RotL64(aScatter, 5U)) + RotL64(aCarry, 21U)) + 2149055907476874332U) + aNonceWordF;
            aOrbiterH = ((aWandererJ + RotL64(aPrevious, 37U)) + RotL64(aCarry, 53U)) + 5342047776745074649U;
            aOrbiterI = ((aWandererI + RotL64(aScatter, 29U)) + 8268148484060546838U) + aPhaseEOrbiterAssignSaltA[(((31U - aIndex) + 20U)) & S_SALT1];
            aOrbiterJ = (((aWandererE + RotL64(aCross, 21U)) + RotL64(aCarry, 41U)) + 10821151364028563719U) + aNonceWordD;
            //
            aOrbiterE = (aOrbiterE + aOrbiterC) + 4294213820894407378U;
            aOrbiterA = ((aOrbiterA ^ aOrbiterE) ^ 10884726101307943090U) ^ aPhaseEOrbiterUpdateSaltB[((aIndex + 7U)) & S_SALT1];
            aOrbiterA = RotL64((aOrbiterA * 1116128870387229159U), 29U);
            //
            aOrbiterB = ((aOrbiterB + aOrbiterE) + 16432210042202444824U) + aNonceWordI;
            aOrbiterH = (aOrbiterH ^ aOrbiterB) ^ 15196602644336228055U;
            aOrbiterH = RotL64((aOrbiterH * 12680438355124070237U), 11U);
            //
            aOrbiterI = (aOrbiterI + aOrbiterJ) + 14117787670220328165U;
            aOrbiterE = ((aOrbiterE ^ aOrbiterI) ^ 219833877949480215U) ^ aNonceWordL;
            aOrbiterE = RotL64((aOrbiterE * 10736293047771972173U), 19U);
            //
            aOrbiterH = (((aOrbiterH + aOrbiterA) + 3326396981881473962U) + aPhaseEOrbiterUpdateSaltD[((aIndex + 8U)) & S_SALT1]) + aNonceWordO;
            aOrbiterJ = (aOrbiterJ ^ aOrbiterH) ^ 14918513066311426279U;
            aOrbiterJ = RotL64((aOrbiterJ * 14269763278564574663U), 3U);
            //
            aOrbiterJ = ((aOrbiterJ + aOrbiterB) + 11795234681370163206U) + aPhaseEOrbiterUpdateSaltE[(((31U - aIndex) + 23U)) & S_SALT1];
            aOrbiterC = ((aOrbiterC ^ aOrbiterJ) ^ 3068267285352664813U) ^ aNonceWordE;
            aOrbiterC = RotL64((aOrbiterC * 15746255933920904619U), 41U);
            //
            aOrbiterA = (aOrbiterA + aOrbiterI) + 245233356957999496U;
            aOrbiterB = ((aOrbiterB ^ aOrbiterA) ^ 709926406353796673U) ^ aPhaseEOrbiterUpdateSaltC[((aIndex + 3U)) & S_SALT1];
            aOrbiterB = RotL64((aOrbiterB * 13627039596842073595U), 47U);
            //
            aOrbiterC = (aOrbiterC + aOrbiterH) + 5378105439430271038U;
            aOrbiterI = (aOrbiterI ^ aOrbiterC) ^ 10114555061122044430U;
            aOrbiterI = RotL64((aOrbiterI * 5351295043424885549U), 35U);
            //
            aIngress = aOrbiterJ ^ RotL64(aOrbiterC, 21U);
            aIngress = aIngress + (RotL64(aOrbiterI, 43U) ^ aOrbiterE);
            aIngress = aIngress + (aOrbiterA ^ RotL64(aOrbiterH, 29U));
            aIngress = aIngress + RotL64(aOrbiterB, 13U);
            aIngress = TwistMix64::DiffuseB((aIngress + aScatter));
            //
            aWandererE = aWandererE + (((RotL64(aPrevious, 21U) + aOrbiterH) + RotL64(aOrbiterC, 42U)) + aPhaseEWandererUpdateSaltE[((aIndex + 19U)) & S_SALT1]);
            aWandererJ = aWandererJ ^ ((((RotL64(aCross, 3U) + RotL64(aOrbiterA, 29U)) + aOrbiterJ) + aNonceWordM) + aPhaseEWandererUpdateSaltB[(((31U - aIndex) + 5U)) & S_SALT1]);
            aWandererF = aWandererF + ((((RotL64(aScatter, 42U) + RotL64(aOrbiterE, 53U)) + aOrbiterC) + RotL64(aCarry, 57U)) + aNonceWordP);
            aWandererK = aWandererK ^ ((RotL64(aIngress, 27U) + RotL64(aOrbiterI, 11U)) + aOrbiterE);
            aWandererB = aWandererB + ((((RotL64(aPrevious, 35U) + RotL64(aOrbiterB, 5U)) + aOrbiterE) + RotL64(aCarry, 29U)) + aNonceWordC);
            aWandererG = aWandererG ^ (((RotL64(aCross, 51U) + RotL64(aOrbiterH, 23U)) + aOrbiterA) + aNonceWordK);
            aWandererI = aWandererI + ((RotL64(aIngress, 57U) + RotL64(aOrbiterJ, 35U)) + aOrbiterH);
            //
            aCarry = aCarry + (RotL64(aWandererK, 57U) ^ aWandererJ);
            aCarry = aCarry + (RotL64(aWandererB, 46U) ^ aWandererI);
            aCarry = aCarry + (aWandererG ^ RotL64(aWandererE, 3U));
            aCarry = aCarry + RotL64(aWandererF, 27U);
            aCarry = aCarry + RotL64(aIngress, 53U);
            aCarry = TwistMix64::DiffuseC(aCarry);
            //
            aWorkLaneB[S_BLOCK1 - aIndex] = aIngress;
        }
    
        // seed_loop_a loop 3
        // ingress from: aWorkLaneB, aKeyRowReadB
        // ingress directions: aWorkLaneB forward forced, aKeyRowReadB forward/backward random
        // cross from: aKeyRowReadA, mSource, aWorkLaneA
        // cross directions: aKeyRowReadA backward forced, mSource backward forced, aWorkLaneA backward/forward random
        // write to: aWorkLaneC
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = RotL64(aWorkLaneB[((aIndex + 5586U)) & S_BLOCK1], 43U) ^ RotL64(aKeyRowReadB[((aIndex + 7835U)) & W_KEY1], 12U);
            aIngress = TwistMix64::DiffuseC(((aIngress ^ aPhaseEDomainWordIngress) ^ aNonceWordI));
            //
            aCross = (RotL64(aKeyRowReadA[(((2047U - aIndex) + 8062U)) & W_KEY1], 23U) ^ RotL64(mSource[((S_BLOCK1 - aIndex + 6353U)) & S_BLOCK1], 4U));
            aCross ^= RotL64(aWorkLaneA[((aIndex + 7584U)) & S_BLOCK1], 51U);
            aCross = TwistMix64::DiffuseC(((aCross ^ aPhaseEDomainWordCross) ^ aNonceWordF));
            //
            aScatter = (RotL64(aPrevious, 51U) + RotL64(aCarry, 4U)) + (RotL64(aIngress, 19U) ^ RotL64(aCross, 37U));
            aScatter = TwistMix64::DiffuseA(((aScatter ^ aPhaseEDomainWordScatter) ^ aNonceWordF));
            //
            aOrbiterA = ((aWandererK + RotL64(aScatter, 57U)) + 2558105147674438050U) + aNonceWordG;
            aOrbiterF = (aWandererA + RotL64(aIngress, 47U)) + 15856662514774702561U;
            aOrbiterI = ((aWandererE + RotL64(aPrevious, 27U)) + 13346869226246584582U) + aNonceWordD;
            aOrbiterJ = ((aWandererB + RotL64(aCross, 11U)) + 7632111846116243973U) + aPhaseEOrbiterAssignSaltF[(((31U - aIndex) + 18U)) & S_SALT1];
            aOrbiterK = ((aWandererC + RotL64(aPrevious, 18U)) + RotL64(aCarry, 11U)) + 2102101361626976279U;
            aOrbiterD = ((((aWandererG + RotL64(aCross, 5U)) + RotL64(aCarry, 41U)) + 5605968705067851563U) + aPhaseEOrbiterAssignSaltA[(((31U - aIndex) + 17U)) & S_SALT1]) + aNonceWordH;
            aOrbiterG = ((aWandererH + RotL64(aScatter, 39U)) + RotL64(aCarry, 29U)) + 6842483186584326681U;
            //
            aOrbiterA = ((aOrbiterA + aOrbiterF) + 5559797213819425064U) + aNonceWordO;
            aOrbiterI = (((aOrbiterI ^ aOrbiterA) ^ 12422313931331576759U) ^ aPhaseEOrbiterUpdateSaltD[(((31U - aIndex) + 10U)) & S_SALT1]) ^ aNonceWordJ;
            aOrbiterI = RotL64((aOrbiterI * 7399849122565913401U), 35U);
            //
            aOrbiterJ = (aOrbiterJ + aOrbiterK) + 2751024420047872601U;
            aOrbiterD = ((aOrbiterD ^ aOrbiterJ) ^ 11031320239359798610U) ^ aPhaseEOrbiterUpdateSaltF[((aIndex + 13U)) & S_SALT1];
            aOrbiterD = RotL64((aOrbiterD * 8607639453141148025U), 3U);
            //
            aOrbiterI = (aOrbiterI + aOrbiterG) + 14366375309473793217U;
            aOrbiterJ = (aOrbiterJ ^ aOrbiterI) ^ 11971479429768505316U;
            aOrbiterJ = RotL64((aOrbiterJ * 10063001532313098203U), 29U);
            //
            aOrbiterF = (aOrbiterF + aOrbiterI) + 3947595951884469542U;
            aOrbiterG = ((aOrbiterG ^ aOrbiterF) ^ 17882767922372770896U) ^ aPhaseEOrbiterUpdateSaltA[(((31U - aIndex) + 19U)) & S_SALT1];
            aOrbiterG = RotL64((aOrbiterG * 3361906348965810211U), 51U);
            //
            aOrbiterG = (aOrbiterG + aOrbiterJ) + 513871456983509223U;
            aOrbiterK = ((aOrbiterK ^ aOrbiterG) ^ 5951677013597794294U) ^ aNonceWordB;
            aOrbiterK = RotL64((aOrbiterK * 8508629569649935293U), 43U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterA) + 437626309049021931U;
            aOrbiterF = (aOrbiterF ^ aOrbiterD) ^ 466674061172005705U;
            aOrbiterF = RotL64((aOrbiterF * 1310502572084891157U), 19U);
            //
            aOrbiterK = ((aOrbiterK + aOrbiterD) + 12362602809233133718U) + aNonceWordK;
            aOrbiterA = ((aOrbiterA ^ aOrbiterK) ^ 10525852878882195702U) ^ aPhaseEOrbiterUpdateSaltC[((aIndex + 28U)) & S_SALT1];
            aOrbiterA = RotL64((aOrbiterA * 17755022180514914325U), 11U);
            //
            aIngress = aOrbiterD ^ RotL64(aOrbiterA, 48U);
            aIngress = aIngress + (aOrbiterK ^ RotL64(aOrbiterJ, 57U));
            aIngress = aIngress + (RotL64(aOrbiterF, 29U) ^ aOrbiterI);
            aIngress = aIngress + RotL64(aOrbiterG, 5U);
            aIngress = TwistMix64::DiffuseB((aIngress + aScatter));
            //
            aWandererG = aWandererG + (((RotL64(aScatter, 23U) + RotL64(aOrbiterI, 23U)) + aOrbiterA) + aNonceWordE);
            aWandererA = aWandererA ^ (((RotL64(aIngress, 43U) + aOrbiterG) + RotL64(aOrbiterI, 3U)) + aNonceWordA);
            aWandererK = aWandererK + (((RotL64(aPrevious, 37U) + RotL64(aOrbiterK, 57U)) + aOrbiterG) + RotL64(aCarry, 39U));
            aWandererE = aWandererE ^ (((RotL64(aCross, 14U) + RotL64(aOrbiterG, 47U)) + aOrbiterF) + aNonceWordM);
            aWandererC = aWandererC + ((((RotL64(aIngress, 57U) + aOrbiterA) + RotL64(aOrbiterK, 13U)) + RotL64(aCarry, 57U)) + aPhaseEWandererUpdateSaltE[((aIndex + 7U)) & S_SALT1]);
            aWandererH = aWandererH ^ (((RotL64(aScatter, 29U) + aOrbiterD) + RotL64(aOrbiterF, 40U)) + aPhaseEWandererUpdateSaltA[(((31U - aIndex) + 16U)) & S_SALT1]);
            aWandererB = aWandererB + (((RotL64(aCross, 5U) + RotL64(aOrbiterJ, 29U)) + aOrbiterK) + aNonceWordN);
            //
            aCarry = aCarry + (RotL64(aWandererH, 3U) ^ aWandererE);
            aCarry = aCarry + (aWandererA ^ RotL64(aWandererC, 18U));
            aCarry = aCarry + (aWandererK ^ RotL64(aWandererG, 47U));
            aCarry = aCarry + RotL64(aWandererB, 57U);
            aCarry = aCarry + RotL64(aIngress, 41U);
            aCarry = TwistMix64::DiffuseA(aCarry);
            //
            aWorkLaneC[aIndex] = aIngress;
        }
    
        // seed_loop_a loop 4
        // ingress from: aWorkLaneC, aKeyRowReadB, mSource, aWorkLaneA
        // ingress directions: aWorkLaneC forward forced, aKeyRowReadB forward forced, mSource forward forced, aWorkLaneA forward/backward random
        // cross from: aKeyRowReadA, aWorkLaneB
        // cross directions: aKeyRowReadA backward forced, aWorkLaneB backward/forward random
        // write to: aWorkLaneD
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aWorkLaneC[((aIndex + 9685U)) & S_BLOCK1], 51U) ^ RotL64(aKeyRowReadB[((aIndex + 9414U)) & W_KEY1], 27U));
            aIngress ^= (RotL64(mSource[((aIndex + 9956U)) & S_BLOCK1], 3U) ^ RotL64(aWorkLaneA[((aIndex + 8693U)) & S_BLOCK1], 36U));
            aIngress = TwistMix64::DiffuseA(((aIngress ^ aPhaseFDomainWordIngress) ^ aNonceWordA));
            //
            aCross = RotL64(aKeyRowReadA[(((2047U - aIndex) + 9293U)) & W_KEY1], 22U) ^ RotL64(aWorkLaneB[((S_BLOCK1 - aIndex + 9721U)) & S_BLOCK1], 3U);
            aCross = TwistMix64::DiffuseA(((aCross ^ aPhaseFDomainWordCross) ^ aNonceWordD));
            //
            aScatter = (RotL64(aIngress, 24U) ^ RotL64(aCarry, 11U)) + (RotL64(aCross, 53U) + RotL64(aPrevious, 41U));
            aScatter = TwistMix64::DiffuseB(((aScatter ^ aPhaseFDomainWordScatter) ^ aNonceWordG));
            //
            aOrbiterD = (((aWandererH + RotL64(aPrevious, 47U)) + RotL64(aCarry, 21U)) + 2225397913940961213U) + aNonceWordL;
            aOrbiterC = (aWandererI + RotL64(aCross, 23U)) + 8342544893601343643U;
            aOrbiterB = (((aWandererA + RotL64(aScatter, 60U)) + 162922186381417187U) + aPhaseFOrbiterAssignSaltB[(((31U - aIndex) + 27U)) & S_SALT1]) + aNonceWordC;
            aOrbiterF = ((aWandererB + RotL64(aIngress, 29U)) + 11660218373710972210U) + aPhaseFOrbiterAssignSaltD[((aIndex + 3U)) & S_SALT1];
            aOrbiterJ = ((aWandererC + RotL64(aScatter, 37U)) + 14909034764605802354U) + aNonceWordK;
            aOrbiterG = (((aWandererE + RotL64(aCross, 11U)) + RotL64(aCarry, 5U)) + 16776955237009701511U) + aNonceWordJ;
            aOrbiterE = ((aWandererF + RotL64(aIngress, 3U)) + RotL64(aCarry, 39U)) + 5834487809188925253U;
            //
            aOrbiterD = ((aOrbiterD + aOrbiterC) + 1498492772767040320U) + aPhaseFOrbiterUpdateSaltA[((aIndex + 16U)) & S_SALT1];
            aOrbiterB = (aOrbiterB ^ aOrbiterD) ^ 4161765458781579617U;
            aOrbiterB = RotL64((aOrbiterB * 15535994410289065281U), 13U);
            //
            aOrbiterF = (aOrbiterF + aOrbiterJ) + 10511923076962447765U;
            aOrbiterG = (aOrbiterG ^ aOrbiterF) ^ 8575954471692620021U;
            aOrbiterG = RotL64((aOrbiterG * 12526744988828982731U), 51U);
            //
            aOrbiterC = ((aOrbiterC + aOrbiterB) + 6536325446331340573U) + aNonceWordM;
            aOrbiterF = (aOrbiterF ^ aOrbiterC) ^ 1790628986900286346U;
            aOrbiterF = RotL64((aOrbiterF * 5262997114200816715U), 5U);
            //
            aOrbiterG = ((aOrbiterG + aOrbiterE) + 2623814807619278590U) + aPhaseFOrbiterUpdateSaltC[((aIndex + 10U)) & S_SALT1];
            aOrbiterD = (aOrbiterD ^ aOrbiterG) ^ 11676970995834706612U;
            aOrbiterD = RotL64((aOrbiterD * 10057461115132434901U), 35U);
            //
            aOrbiterE = ((aOrbiterE + aOrbiterD) + 13836786354224256591U) + aPhaseFOrbiterUpdateSaltB[((aIndex + 28U)) & S_SALT1];
            aOrbiterC = (aOrbiterC ^ aOrbiterE) ^ 6293096163612129260U;
            aOrbiterC = RotL64((aOrbiterC * 8977954126326217153U), 23U);
            //
            aOrbiterJ = (((aOrbiterJ + aOrbiterG) + 4271144764978661248U) + aPhaseFOrbiterUpdateSaltE[((aIndex + 5U)) & S_SALT1]) + aNonceWordE;
            aOrbiterE = (aOrbiterE ^ aOrbiterJ) ^ 15938494256992560202U;
            aOrbiterE = RotL64((aOrbiterE * 10004841288382726739U), 43U);
            //
            aOrbiterB = (aOrbiterB + aOrbiterF) + 11038155227307702976U;
            aOrbiterJ = (aOrbiterJ ^ aOrbiterB) ^ 12408749795071243930U;
            aOrbiterJ = RotL64((aOrbiterJ * 5527720475032868855U), 57U);
            //
            aIngress = RotL64(aOrbiterD, 27U) ^ aOrbiterF;
            aIngress = aIngress + (RotL64(aOrbiterC, 10U) ^ aOrbiterB);
            aIngress = aIngress + (aOrbiterJ ^ RotL64(aOrbiterE, 21U));
            aIngress = aIngress + RotL64(aOrbiterG, 35U);
            aIngress = TwistMix64::DiffuseA((aIngress + aScatter));
            //
            aWandererF = aWandererF + (((RotL64(aPrevious, 29U) + aOrbiterD) + RotL64(aOrbiterC, 57U)) + RotL64(aCarry, 39U));
            aWandererA = aWandererA ^ ((RotL64(aCross, 36U) + aOrbiterC) + RotL64(aOrbiterB, 47U));
            aWandererH = aWandererH + (((((RotL64(aIngress, 19U) + RotL64(aOrbiterG, 35U)) + aOrbiterJ) + RotL64(aCarry, 27U)) + aNonceWordF) + aPhaseFWandererUpdateSaltA[(((31U - aIndex) + 18U)) & S_SALT1]);
            aWandererI = aWandererI ^ (((RotL64(aScatter, 51U) + RotL64(aOrbiterJ, 41U)) + aOrbiterF) + aPhaseFWandererUpdateSaltB[(((31U - aIndex) + 9U)) & S_SALT1]);
            aWandererE = aWandererE + ((RotL64(aCross, 11U) + aOrbiterE) + RotL64(aOrbiterG, 3U));
            aWandererB = aWandererB ^ (((RotL64(aPrevious, 5U) + aOrbiterJ) + RotL64(aOrbiterE, 14U)) + aNonceWordP);
            aWandererC = aWandererC + (((RotL64(aIngress, 43U) + RotL64(aOrbiterE, 29U)) + aOrbiterC) + aNonceWordH);
            //
            aCarry = aCarry + (RotL64(aWandererC, 12U) ^ aWandererB);
            aCarry = aCarry + (RotL64(aWandererH, 37U) ^ aWandererE);
            aCarry = aCarry + (aWandererF ^ RotL64(aWandererI, 51U));
            aCarry = aCarry + RotL64(aWandererA, 23U);
            aCarry = aCarry + RotL64(aIngress, 47U);
            aCarry = TwistMix64::DiffuseC(aCarry);
            //
            aWorkLaneD[S_BLOCK1 - aIndex] = aIngress;
        }
    
        // seed_loop_a loop 5
        // ingress from: aWorkLaneD, aKeyRowReadA, aKeyRowReadB, mSource, aWorkLaneB
        // ingress directions: aWorkLaneD forward forced, aKeyRowReadA forward forced, aKeyRowReadB forward forced, mSource forward forced, aWorkLaneB forward/backward random
        // cross from: aWorkLaneA, aWorkLaneC
        // cross directions: aWorkLaneA backward forced, aWorkLaneC backward/forward random
        // write to: aFireLaneA
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aWorkLaneD[((aIndex + 11356U)) & S_BLOCK1], 47U) ^ RotL64(aKeyRowReadA[((aIndex + 13599U)) & W_KEY1], 57U));
            aIngress ^= (RotL64(aKeyRowReadB[((aIndex + 12342U)) & W_KEY1], 39U) ^ RotL64(mSource[((aIndex + 11528U)) & S_BLOCK1], 14U));
            aIngress ^= RotL64(aWorkLaneB[((aIndex + 11310U)) & S_BLOCK1], 23U);
            aIngress = TwistMix64::DiffuseA(((aIngress ^ aPhaseFDomainWordIngress) ^ aNonceWordH));
            //
            aCross = RotL64(aWorkLaneA[((S_BLOCK1 - aIndex + 12780U)) & S_BLOCK1], 51U) ^ RotL64(aWorkLaneC[((aIndex + 11944U)) & S_BLOCK1], 35U);
            aCross = TwistMix64::DiffuseA(((aCross ^ aPhaseFDomainWordCross) ^ aNonceWordG));
            //
            aScatter = (RotL64(aCross, 5U) + RotL64(aPrevious, 57U)) ^ (RotL64(aCarry, 21U) ^ RotL64(aIngress, 38U));
            aScatter = TwistMix64::DiffuseB(((aScatter ^ aPhaseFDomainWordScatter) ^ aNonceWordH));
            //
            aOrbiterA = ((aWandererC + RotL64(aIngress, 35U)) + RotL64(aCarry, 29U)) + 15813325389431304548U;
            aOrbiterI = ((aWandererK + RotL64(aPrevious, 47U)) + RotL64(aCarry, 5U)) + 2223874171125403602U;
            aOrbiterB = ((aWandererF + RotL64(aCross, 13U)) + RotL64(aCarry, 41U)) + 5510483568496824130U;
            aOrbiterE = ((aWandererJ + RotL64(aScatter, 41U)) + 15474152493495661876U) + aPhaseFOrbiterAssignSaltE[((aIndex + 14U)) & S_SALT1];
            aOrbiterD = ((aWandererD + RotL64(aPrevious, 6U)) + 16846339705130829195U) + aNonceWordA;
            aOrbiterK = ((aWandererI + RotL64(aScatter, 57U)) + 1289670576865739669U) + aPhaseFOrbiterAssignSaltD[((aIndex + 29U)) & S_SALT1];
            aOrbiterJ = ((aWandererH + RotL64(aIngress, 21U)) + 18017354919647006944U) + aNonceWordL;
            //
            aOrbiterA = (aOrbiterA + aOrbiterI) + 8539685539928984921U;
            aOrbiterB = (aOrbiterB ^ aOrbiterA) ^ 3333721400836704048U;
            aOrbiterB = RotL64((aOrbiterB * 3745286323481400085U), 11U);
            //
            aOrbiterE = (((aOrbiterE + aOrbiterD) + 2261560416623815491U) + aPhaseFOrbiterUpdateSaltC[(((31U - aIndex) + 19U)) & S_SALT1]) + aNonceWordN;
            aOrbiterI = (aOrbiterI ^ aOrbiterE) ^ 4377786131746816567U;
            aOrbiterI = RotL64((aOrbiterI * 9164777834392621157U), 51U);
            //
            aOrbiterK = (aOrbiterK + aOrbiterB) + 18047393176583722719U;
            aOrbiterE = (aOrbiterE ^ aOrbiterK) ^ 8184724021940434631U;
            aOrbiterE = RotL64((aOrbiterE * 9800116157750921119U), 29U);
            //
            aOrbiterI = (aOrbiterI + aOrbiterK) + 10469895939183324807U;
            aOrbiterJ = (aOrbiterJ ^ aOrbiterI) ^ 14543391765109879223U;
            aOrbiterJ = RotL64((aOrbiterJ * 4817987697437667225U), 37U);
            //
            aOrbiterB = ((aOrbiterB + aOrbiterJ) + 5757225781746158178U) + aPhaseFOrbiterUpdateSaltA[(((31U - aIndex) + 6U)) & S_SALT1];
            aOrbiterD = ((aOrbiterD ^ aOrbiterB) ^ 3539000495894022869U) ^ aNonceWordC;
            aOrbiterD = RotL64((aOrbiterD * 1032298408884695925U), 43U);
            //
            aOrbiterJ = ((aOrbiterJ + aOrbiterE) + 11288971092707065923U) + aNonceWordK;
            aOrbiterA = ((aOrbiterA ^ aOrbiterJ) ^ 2761384065186568294U) ^ aPhaseFOrbiterUpdateSaltD[(((31U - aIndex) + 5U)) & S_SALT1];
            aOrbiterA = RotL64((aOrbiterA * 3323838837427471051U), 5U);
            //
            aOrbiterD = ((aOrbiterD + aOrbiterA) + 7120580145300417101U) + aPhaseFOrbiterUpdateSaltB[(((31U - aIndex) + 7U)) & S_SALT1];
            aOrbiterK = (aOrbiterK ^ aOrbiterD) ^ 6977246291769372866U;
            aOrbiterK = RotL64((aOrbiterK * 15170353875184253779U), 21U);
            //
            aIngress = RotL64(aOrbiterB, 21U) ^ aOrbiterA;
            aIngress = aIngress + (aOrbiterD ^ RotL64(aOrbiterJ, 57U));
            aIngress = aIngress + (aOrbiterK ^ RotL64(aOrbiterI, 47U));
            aIngress = aIngress + RotL64(aOrbiterE, 5U);
            aIngress = TwistMix64::DiffuseC((aIngress + aScatter));
            //
            aWandererD = aWandererD + ((((RotL64(aIngress, 60U) + RotL64(aOrbiterK, 35U)) + aOrbiterJ) + RotL64(aCarry, 53U)) + aNonceWordE);
            aWandererH = aWandererH ^ ((RotL64(aPrevious, 47U) + aOrbiterJ) + RotL64(aOrbiterA, 57U));
            aWandererC = aWandererC + ((((RotL64(aScatter, 21U) + aOrbiterI) + RotL64(aOrbiterJ, 51U)) + RotL64(aCarry, 21U)) + aPhaseFWandererUpdateSaltA[((aIndex + 15U)) & S_SALT1]);
            aWandererI = aWandererI ^ (((RotL64(aCross, 35U) + aOrbiterB) + RotL64(aOrbiterD, 5U)) + aNonceWordD);
            aWandererF = aWandererF + (((RotL64(aIngress, 13U) + RotL64(aOrbiterB, 42U)) + aOrbiterJ) + aPhaseFWandererUpdateSaltB[(((31U - aIndex) + 28U)) & S_SALT1]);
            aWandererK = aWandererK ^ ((RotL64(aPrevious, 5U) + aOrbiterE) + RotL64(aOrbiterI, 21U));
            aWandererJ = aWandererJ + (((RotL64(aCross, 41U) + aOrbiterJ) + RotL64(aOrbiterE, 11U)) + aNonceWordF);
            //
            aCarry = aCarry + (aWandererI ^ RotL64(aWandererC, 43U));
            aCarry = aCarry + (aWandererH ^ RotL64(aWandererF, 48U));
            aCarry = aCarry + (aWandererD ^ RotL64(aWandererK, 35U));
            aCarry = aCarry + RotL64(aWandererJ, 53U);
            aCarry = aCarry + RotL64(aIngress, 57U);
            aCarry = TwistMix64::DiffuseA(aCarry);
            //
            aFireLaneA[aIndex] = aIngress;
        }
    
        // seed_loop_a loop 6
        // ingress from: aFireLaneA, aWorkLaneC
        // ingress directions: aFireLaneA forward forced, aWorkLaneC forward/backward random
        // cross from: aKeyRowReadA, aKeyRowReadB, mSource, aWorkLaneB, aWorkLaneA
        // cross directions: aKeyRowReadA backward forced, aKeyRowReadB backward forced, mSource backward forced, aWorkLaneB backward forced, aWorkLaneA backward/forward random
        // write to: aFireLaneB
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = RotL64(aFireLaneA[((aIndex + 15268U)) & S_BLOCK1], 43U) ^ RotL64(aWorkLaneC[((aIndex + 14096U)) & S_BLOCK1], 5U);
            aIngress = TwistMix64::DiffuseC(((aIngress ^ aPhaseFDomainWordIngress) ^ aNonceWordP));
            //
            aCross = (RotL64(aKeyRowReadA[(((2047U - aIndex) + 16208U)) & W_KEY1], 57U) ^ RotL64(aKeyRowReadB[(((2047U - aIndex) + 13932U)) & W_KEY1], 13U));
            aCross ^= (RotL64(mSource[((S_BLOCK1 - aIndex + 15731U)) & S_BLOCK1], 26U) ^ RotL64(aWorkLaneB[((S_BLOCK1 - aIndex + 14976U)) & S_BLOCK1], 37U));
            aCross ^= RotL64(aWorkLaneA[((S_BLOCK1 - aIndex + 13752U)) & S_BLOCK1], 5U);
            aCross = TwistMix64::DiffuseC(((aCross ^ aPhaseFDomainWordCross) ^ aNonceWordK));
            //
            aScatter = (RotL64(aPrevious, 5U) ^ RotL64(aCarry, 36U)) + (RotL64(aIngress, 21U) + RotL64(aCross, 53U));
            aScatter = TwistMix64::DiffuseA(((aScatter ^ aPhaseFDomainWordScatter) ^ aNonceWordP));
            //
            aOrbiterE = ((aWandererI + RotL64(aIngress, 35U)) + 15188686795415908074U) + aPhaseFOrbiterAssignSaltB[((aIndex + 22U)) & S_SALT1];
            aOrbiterK = (((aWandererD + RotL64(aCross, 43U)) + RotL64(aCarry, 19U)) + 17310049041983079779U) + aNonceWordB;
            aOrbiterD = (((aWandererE + RotL64(aScatter, 12U)) + RotL64(aCarry, 53U)) + 8246925977992441471U) + aPhaseFOrbiterAssignSaltF[(((31U - aIndex) + 7U)) & S_SALT1];
            aOrbiterB = (aWandererG + RotL64(aPrevious, 29U)) + 8644260919918112781U;
            aOrbiterF = (((aWandererF + RotL64(aIngress, 57U)) + RotL64(aCarry, 3U)) + 13401663736874819483U) + aNonceWordG;
            aOrbiterI = (aWandererB + RotL64(aScatter, 3U)) + 7940358935238314973U;
            aOrbiterC = (aWandererC + RotL64(aCross, 23U)) + 13278990328548007839U;
            //
            aOrbiterE = (aOrbiterE + aOrbiterK) + 11346868298353840706U;
            aOrbiterD = (aOrbiterD ^ aOrbiterE) ^ 2374077904806833579U;
            aOrbiterD = RotL64((aOrbiterD * 1765686942154321425U), 57U);
            //
            aOrbiterK = (aOrbiterK + aOrbiterB) + 6978903378645019166U;
            aOrbiterF = ((aOrbiterF ^ aOrbiterK) ^ 11951633297870965212U) ^ aNonceWordE;
            aOrbiterF = RotL64((aOrbiterF * 12778236598654492185U), 11U);
            //
            aOrbiterD = ((aOrbiterD + aOrbiterF) + 17398460995357409673U) + aNonceWordO;
            aOrbiterI = (aOrbiterI ^ aOrbiterD) ^ 1215437945597836770U;
            aOrbiterI = RotL64((aOrbiterI * 9322970054123481621U), 21U);
            //
            aOrbiterI = ((aOrbiterI + aOrbiterC) + 1878751468043972239U) + aPhaseFOrbiterUpdateSaltF[((aIndex + 23U)) & S_SALT1];
            aOrbiterK = ((aOrbiterK ^ aOrbiterI) ^ 5343002808239712390U) ^ aPhaseFOrbiterUpdateSaltC[((aIndex + 20U)) & S_SALT1];
            aOrbiterK = RotL64((aOrbiterK * 11878640995447558811U), 29U);
            //
            aOrbiterB = ((aOrbiterB + aOrbiterI) + 9884918450053276861U) + aPhaseFOrbiterUpdateSaltD[((aIndex + 26U)) & S_SALT1];
            aOrbiterE = (((aOrbiterE ^ aOrbiterB) ^ 15894599082080422550U) ^ aPhaseFOrbiterUpdateSaltA[((aIndex + 25U)) & S_SALT1]) ^ aNonceWordI;
            aOrbiterE = RotL64((aOrbiterE * 8359936745539546131U), 51U);
            //
            aOrbiterC = ((aOrbiterC + aOrbiterD) + 13917339232771145459U) + aNonceWordD;
            aOrbiterB = (aOrbiterB ^ aOrbiterC) ^ 18101134009493720683U;
            aOrbiterB = RotL64((aOrbiterB * 15835859435306756387U), 5U);
            //
            aOrbiterF = (aOrbiterF + aOrbiterE) + 3830086372356903769U;
            aOrbiterC = (aOrbiterC ^ aOrbiterF) ^ 15894394599564584010U;
            aOrbiterC = RotL64((aOrbiterC * 9513921913446609263U), 39U);
            //
            aIngress = aOrbiterC ^ RotL64(aOrbiterF, 19U);
            aIngress = aIngress + (aOrbiterD ^ RotL64(aOrbiterK, 27U));
            aIngress = aIngress + (aOrbiterE ^ RotL64(aOrbiterB, 3U));
            aIngress = aIngress + RotL64(aOrbiterI, 11U);
            aIngress = TwistMix64::DiffuseC((aIngress + aScatter));
            //
            aWandererD = aWandererD + ((RotL64(aIngress, 43U) + aOrbiterI) + RotL64(aOrbiterD, 57U));
            aWandererF = aWandererF ^ ((RotL64(aCross, 11U) + RotL64(aOrbiterF, 14U)) + aOrbiterD);
            aWandererC = aWandererC + ((((RotL64(aScatter, 51U) + RotL64(aOrbiterC, 47U)) + aOrbiterI) + RotL64(aCarry, 23U)) + aNonceWordJ);
            aWandererE = aWandererE ^ (((RotL64(aPrevious, 18U) + aOrbiterE) + RotL64(aOrbiterD, 37U)) + aPhaseFWandererUpdateSaltA[(((31U - aIndex) + 18U)) & S_SALT1]);
            aWandererI = aWandererI + (((RotL64(aScatter, 37U) + RotL64(aOrbiterK, 21U)) + aOrbiterE) + aPhaseFWandererUpdateSaltD[(((31U - aIndex) + 14U)) & S_SALT1]);
            aWandererB = aWandererB ^ (((RotL64(aIngress, 29U) + RotL64(aOrbiterC, 5U)) + aOrbiterB) + aNonceWordC);
            aWandererG = aWandererG + ((((RotL64(aCross, 3U) + aOrbiterD) + RotL64(aOrbiterK, 29U)) + RotL64(aCarry, 47U)) + aNonceWordM);
            //
            aCarry = aCarry + (RotL64(aWandererC, 43U) ^ aWandererI);
            aCarry = aCarry + (RotL64(aWandererG, 56U) ^ aWandererF);
            aCarry = aCarry + (RotL64(aWandererB, 27U) ^ aWandererD);
            aCarry = aCarry + RotL64(aWandererE, 47U);
            aCarry = aCarry + RotL64(aIngress, 5U);
            aCarry = TwistMix64::DiffuseA(aCarry);
            //
            aFireLaneB[S_BLOCK1 - aIndex] = aIngress;
        }
    
        // seed_loop_a loop 7
        // ingress from: aFireLaneB, aKeyRowReadA, mSource, aWorkLaneA
        // ingress directions: aFireLaneB forward forced, aKeyRowReadA forward forced, mSource forward forced, aWorkLaneA forward/backward random
        // cross from: aKeyRowReadB, aWorkLaneD, aFireLaneA
        // cross directions: aKeyRowReadB backward forced, aWorkLaneD backward forced, aFireLaneA backward/forward random
        // write to: aFireLaneC
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aFireLaneB[((aIndex + 18963U)) & S_BLOCK1], 29U) ^ RotL64(aKeyRowReadA[((aIndex + 18168U)) & W_KEY1], 47U));
            aIngress ^= (RotL64(mSource[((aIndex + 19066U)) & S_BLOCK1], 12U) ^ RotL64(aWorkLaneA[((aIndex + 16522U)) & S_BLOCK1], 57U));
            aIngress = TwistMix64::DiffuseB(((aIngress ^ aPhaseGDomainWordIngress) ^ aNonceWordC));
            //
            aCross = (RotL64(aKeyRowReadB[(((2047U - aIndex) + 17091U)) & W_KEY1], 46U) ^ RotL64(aWorkLaneD[((S_BLOCK1 - aIndex + 17753U)) & S_BLOCK1], 57U));
            aCross ^= RotL64(aFireLaneA[((aIndex + 18787U)) & S_BLOCK1], 3U);
            aCross = TwistMix64::DiffuseC(((aCross ^ aPhaseGDomainWordCross) ^ aNonceWordN));
            //
            aScatter = (RotL64(aIngress, 27U) + RotL64(aCarry, 41U)) ^ (RotL64(aCross, 6U) ^ RotL64(aPrevious, 53U));
            aScatter = TwistMix64::DiffuseC(((aScatter ^ aPhaseGDomainWordScatter) ^ aNonceWordP));
            //
            aOrbiterG = (((aWandererH + RotL64(aScatter, 37U)) + RotL64(aCarry, 23U)) + 8020711767807230555U) + aPhaseGOrbiterAssignSaltC[((aIndex + 25U)) & S_SALT1];
            aOrbiterA = (((aWandererK + RotL64(aCross, 23U)) + RotL64(aCarry, 35U)) + 15368693777246341570U) + aPhaseGOrbiterAssignSaltA[(((31U - aIndex) + 23U)) & S_SALT1];
            aOrbiterC = ((aWandererF + RotL64(aIngress, 11U)) + 5117523734225562401U) + aNonceWordI;
            aOrbiterK = (((aWandererB + RotL64(aPrevious, 44U)) + RotL64(aCarry, 51U)) + 13155269151097507808U) + aNonceWordA;
            aOrbiterE = (aWandererD + RotL64(aScatter, 3U)) + 9879303753623578272U;
            aOrbiterH = (aWandererJ + RotL64(aCross, 29U)) + 1165799257173794826U;
            aOrbiterI = (aWandererG + RotL64(aPrevious, 51U)) + 930641942062732091U;
            //
            aOrbiterG = ((aOrbiterG + aOrbiterA) + 11330571332221123153U) + aNonceWordD;
            aOrbiterC = (aOrbiterC ^ aOrbiterG) ^ 2862963158282518899U;
            aOrbiterC = RotL64((aOrbiterC * 13782195862525974199U), 47U);
            //
            aOrbiterK = (aOrbiterK + aOrbiterE) + 6019186399361476659U;
            aOrbiterA = ((aOrbiterA ^ aOrbiterK) ^ 1924419843785161958U) ^ aPhaseGOrbiterUpdateSaltE[(((31U - aIndex) + 5U)) & S_SALT1];
            aOrbiterA = RotL64((aOrbiterA * 9485557122500346869U), 21U);
            //
            aOrbiterC = (aOrbiterC + aOrbiterH) + 12618629043591380461U;
            aOrbiterK = (aOrbiterK ^ aOrbiterC) ^ 9334176504266512405U;
            aOrbiterK = RotL64((aOrbiterK * 18239109235362925739U), 27U);
            //
            aOrbiterI = (aOrbiterI + aOrbiterK) + 16829692481030013551U;
            aOrbiterG = (aOrbiterG ^ aOrbiterI) ^ 5604784396927022709U;
            aOrbiterG = RotL64((aOrbiterG * 2833893610883508353U), 53U);
            //
            aOrbiterE = ((aOrbiterE + aOrbiterC) + 16124030106598549644U) + aNonceWordM;
            aOrbiterI = (aOrbiterI ^ aOrbiterE) ^ 16571659812830230677U;
            aOrbiterI = RotL64((aOrbiterI * 4668250364992383549U), 35U);
            //
            aOrbiterA = ((aOrbiterA + aOrbiterI) + 15171089673591843703U) + aPhaseGOrbiterUpdateSaltC[(((31U - aIndex) + 21U)) & S_SALT1];
            aOrbiterH = (aOrbiterH ^ aOrbiterA) ^ 2826755560293849328U;
            aOrbiterH = RotL64((aOrbiterH * 9397017963457655287U), 41U);
            //
            aOrbiterH = ((aOrbiterH + aOrbiterG) + 9976785768283589291U) + aPhaseGOrbiterUpdateSaltA[((aIndex + 4U)) & S_SALT1];
            aOrbiterE = ((aOrbiterE ^ aOrbiterH) ^ 11845100564714691809U) ^ aPhaseGOrbiterUpdateSaltD[((aIndex + 16U)) & S_SALT1];
            aOrbiterE = RotL64((aOrbiterE * 4935139932585319251U), 11U);
            //
            aIngress = aOrbiterG ^ RotL64(aOrbiterE, 19U);
            aIngress = aIngress + (RotL64(aOrbiterI, 29U) ^ aOrbiterK);
            aIngress = aIngress + (RotL64(aOrbiterC, 41U) ^ aOrbiterA);
            aIngress = aIngress + RotL64(aOrbiterH, 52U);
            aIngress = TwistMix64::DiffuseC((aIngress + aScatter));
            //
            aWandererG = aWandererG + ((RotL64(aCross, 13U) + aOrbiterC) + RotL64(aOrbiterG, 47U));
            aWandererK = aWandererK ^ (((RotL64(aIngress, 34U) + aOrbiterI) + RotL64(aOrbiterA, 11U)) + aNonceWordO);
            aWandererB = aWandererB + ((((RotL64(aScatter, 27U) + RotL64(aOrbiterE, 39U)) + aOrbiterA) + RotL64(aCarry, 5U)) + aNonceWordE);
            aWandererJ = aWandererJ ^ (((RotL64(aPrevious, 51U) + aOrbiterI) + RotL64(aOrbiterK, 54U)) + aPhaseGWandererUpdateSaltA[(((31U - aIndex) + 9U)) & S_SALT1]);
            aWandererH = aWandererH + ((((RotL64(aIngress, 5U) + aOrbiterK) + RotL64(aOrbiterC, 5U)) + RotL64(aCarry, 37U)) + aNonceWordJ);
            aWandererF = aWandererF ^ (((RotL64(aCross, 43U) + aOrbiterE) + RotL64(aOrbiterH, 29U)) + aNonceWordH);
            aWandererD = aWandererD + (((RotL64(aPrevious, 57U) + aOrbiterH) + RotL64(aOrbiterC, 19U)) + aPhaseGWandererUpdateSaltF[((aIndex + 13U)) & S_SALT1]);
            //
            aCarry = aCarry + (RotL64(aWandererB, 36U) ^ aWandererD);
            aCarry = aCarry + (RotL64(aWandererG, 21U) ^ aWandererF);
            aCarry = aCarry + (RotL64(aWandererH, 3U) ^ aWandererJ);
            aCarry = aCarry + RotL64(aWandererK, 29U);
            aCarry = aCarry + RotL64(aIngress, 57U);
            aCarry = TwistMix64::DiffuseA(aCarry);
            //
            aFireLaneC[aIndex] = aIngress;
        }
    
        // seed_loop_a loop 8
        // ingress from: aFireLaneC, mSource, aFireLaneA, aWorkLaneA
        // ingress directions: aFireLaneC forward forced, mSource forward forced, aFireLaneA forward forced, aWorkLaneA forward/backward random
        // cross from: aKeyRowReadA, aKeyRowReadB, aFireLaneB, aWorkLaneB
        // cross directions: aKeyRowReadA backward forced, aKeyRowReadB backward forced, aFireLaneB backward forced, aWorkLaneB backward/forward random
        // write to: aFireLaneD
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aFireLaneC[((aIndex + 21745U)) & S_BLOCK1], 50U) ^ RotL64(mSource[((aIndex + 21659U)) & S_BLOCK1], 5U));
            aIngress ^= (RotL64(aFireLaneA[((aIndex + 20575U)) & S_BLOCK1], 27U) ^ RotL64(aWorkLaneA[((S_BLOCK1 - aIndex + 19629U)) & S_BLOCK1], 35U));
            aIngress = TwistMix64::DiffuseB(((aIngress ^ aPhaseGDomainWordIngress) ^ aNonceWordG));
            //
            aCross = (RotL64(aKeyRowReadA[(((2047U - aIndex) + 20483U)) & W_KEY1], 3U) ^ RotL64(aKeyRowReadB[(((2047U - aIndex) + 21666U)) & W_KEY1], 12U));
            aCross ^= (RotL64(aFireLaneB[((S_BLOCK1 - aIndex + 20285U)) & S_BLOCK1], 23U) ^ RotL64(aWorkLaneB[((aIndex + 19357U)) & S_BLOCK1], 53U));
            aCross = TwistMix64::DiffuseB(((aCross ^ aPhaseGDomainWordCross) ^ aNonceWordL));
            //
            aScatter = (RotL64(aCross, 23U) + RotL64(aPrevious, 37U)) ^ (RotL64(aCarry, 10U) + RotL64(aIngress, 57U));
            aScatter = TwistMix64::DiffuseB(((aScatter ^ aPhaseGDomainWordScatter) ^ aNonceWordC));
            //
            aOrbiterF = ((aWandererG + RotL64(aPrevious, 21U)) + 380024772508948442U) + aNonceWordM;
            aOrbiterD = ((((aWandererA + RotL64(aCross, 27U)) + RotL64(aCarry, 19U)) + 7649029098162567210U) + aPhaseGOrbiterAssignSaltA[((aIndex + 28U)) & S_SALT1]) + aNonceWordO;
            aOrbiterI = (((aWandererB + RotL64(aScatter, 57U)) + RotL64(aCarry, 51U)) + 5329304598870421851U) + aPhaseGOrbiterAssignSaltD[((aIndex + 24U)) & S_SALT1];
            aOrbiterA = (aWandererJ + RotL64(aIngress, 11U)) + 12306118665045151326U;
            aOrbiterJ = ((aWandererE + RotL64(aCross, 43U)) + 960751560457324256U) + aNonceWordN;
            aOrbiterC = ((aWandererH + RotL64(aPrevious, 4U)) + RotL64(aCarry, 3U)) + 3244070254386191876U;
            aOrbiterE = ((aWandererC + RotL64(aIngress, 37U)) + 15733408571609521746U) + aNonceWordF;
            //
            aOrbiterF = ((aOrbiterF + aOrbiterD) + 17623448932647018544U) + aNonceWordC;
            aOrbiterI = (aOrbiterI ^ aOrbiterF) ^ 8787759896149035829U;
            aOrbiterI = RotL64((aOrbiterI * 7092515868845497573U), 11U);
            //
            aOrbiterA = (aOrbiterA + aOrbiterF) + 14741681792348288162U;
            aOrbiterJ = ((aOrbiterJ ^ aOrbiterA) ^ 8801731213568307302U) ^ aNonceWordB;
            aOrbiterJ = RotL64((aOrbiterJ * 12127126999570616489U), 41U);
            //
            aOrbiterJ = (aOrbiterJ + aOrbiterI) + 9872248187499779222U;
            aOrbiterC = (((aOrbiterC ^ aOrbiterJ) ^ 15407371518644528235U) ^ aPhaseGOrbiterUpdateSaltD[(((31U - aIndex) + 6U)) & S_SALT1]) ^ aNonceWordK;
            aOrbiterC = RotL64((aOrbiterC * 1245102406469471673U), 29U);
            //
            aOrbiterC = ((aOrbiterC + aOrbiterA) + 4242060317152943062U) + aPhaseGOrbiterUpdateSaltC[(((31U - aIndex) + 15U)) & S_SALT1];
            aOrbiterD = ((aOrbiterD ^ aOrbiterC) ^ 9942784962409917541U) ^ aPhaseGOrbiterUpdateSaltE[(((31U - aIndex) + 5U)) & S_SALT1];
            aOrbiterD = RotL64((aOrbiterD * 888649755587764533U), 51U);
            //
            aOrbiterE = (aOrbiterE + aOrbiterC) + 7296348796484458631U;
            aOrbiterF = (aOrbiterF ^ aOrbiterE) ^ 15061417216070157797U;
            aOrbiterF = RotL64((aOrbiterF * 10349554676953256231U), 5U);
            //
            aOrbiterI = (((aOrbiterI + aOrbiterE) + 3233185810644297433U) + aPhaseGOrbiterUpdateSaltF[(((31U - aIndex) + 21U)) & S_SALT1]) + aNonceWordE;
            aOrbiterA = (aOrbiterA ^ aOrbiterI) ^ 9241229457641024287U;
            aOrbiterA = RotL64((aOrbiterA * 2728237515724597517U), 23U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterJ) + 8464051359381554575U;
            aOrbiterE = (aOrbiterE ^ aOrbiterD) ^ 3307872165699029375U;
            aOrbiterE = RotL64((aOrbiterE * 4859663401033023433U), 57U);
            //
            aIngress = RotL64(aOrbiterD, 57U) ^ aOrbiterA;
            aIngress = aIngress + (aOrbiterC ^ RotL64(aOrbiterJ, 51U));
            aIngress = aIngress + (aOrbiterI ^ RotL64(aOrbiterF, 29U));
            aIngress = aIngress + RotL64(aOrbiterE, 11U);
            aIngress = TwistMix64::DiffuseB((aIngress + aScatter));
            //
            aWandererE = aWandererE ^ ((RotL64(aCross, 60U) + RotL64(aOrbiterE, 47U)) + aOrbiterI);
            aWandererJ = aWandererJ + ((((RotL64(aPrevious, 35U) + RotL64(aOrbiterE, 53U)) + aOrbiterC) + RotL64(aCarry, 37U)) + aPhaseGWandererUpdateSaltB[((aIndex + 25U)) & S_SALT1]);
            aWandererH = aWandererH ^ ((RotL64(aScatter, 21U) + aOrbiterA) + RotL64(aOrbiterJ, 11U));
            aWandererC = aWandererC + ((RotL64(aIngress, 3U) + RotL64(aOrbiterD, 39U)) + aOrbiterC);
            aWandererA = aWandererA ^ ((RotL64(aPrevious, 51U) + RotL64(aOrbiterA, 3U)) + aOrbiterF);
            aWandererG = aWandererG + ((((RotL64(aIngress, 43U) + aOrbiterC) + RotL64(aOrbiterJ, 29U)) + RotL64(aCarry, 51U)) + aNonceWordP);
            aWandererB = aWandererB ^ ((((RotL64(aCross, 27U) + aOrbiterI) + RotL64(aOrbiterA, 18U)) + aNonceWordD) + aPhaseGWandererUpdateSaltF[(((31U - aIndex) + 26U)) & S_SALT1]);
            //
            aCarry = aCarry + (aWandererE ^ RotL64(aWandererB, 34U));
            aCarry = aCarry + (RotL64(aWandererC, 23U) ^ aWandererJ);
            aCarry = aCarry + (aWandererH ^ RotL64(aWandererG, 47U));
            aCarry = aCarry + RotL64(aWandererA, 27U);
            aCarry = aCarry + RotL64(aIngress, 43U);
            aCarry = TwistMix64::DiffuseB(aCarry);
            //
            aFireLaneD[S_BLOCK1 - aIndex] = aIngress;
        }
    
        // seed_loop_a loop 9
        // ingress from: aFireLaneD, aKeyRowReadA, aKeyRowReadB, aFireLaneC
        // ingress directions: aFireLaneD forward forced, aKeyRowReadA forward forced, aKeyRowReadB forward forced, aFireLaneC forward/backward random
        // cross from: mSource, aFireLaneA, aWorkLaneC, aWorkLaneD
        // cross directions: mSource backward forced, aFireLaneA backward forced, aWorkLaneC backward forced, aWorkLaneD backward/forward random
        // write to: aExpandLaneA
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aFireLaneD[((aIndex + 22846U)) & S_BLOCK1], 5U) ^ RotL64(aKeyRowReadA[((aIndex + 23462U)) & W_KEY1], 56U));
            aIngress ^= (RotL64(aKeyRowReadB[((aIndex + 22722U)) & W_KEY1], 37U) ^ RotL64(aFireLaneC[((aIndex + 23009U)) & S_BLOCK1], 13U));
            aIngress = TwistMix64::DiffuseC(((aIngress ^ aPhaseGDomainWordIngress) ^ aNonceWordP));
            //
            aCross = (RotL64(mSource[((S_BLOCK1 - aIndex + 24080U)) & S_BLOCK1], 57U) ^ RotL64(aFireLaneA[((S_BLOCK1 - aIndex + 21949U)) & S_BLOCK1], 19U));
            aCross ^= (RotL64(aWorkLaneC[((S_BLOCK1 - aIndex + 24274U)) & S_BLOCK1], 10U) ^ RotL64(aWorkLaneD[((aIndex + 24003U)) & S_BLOCK1], 43U));
            aCross = TwistMix64::DiffuseC(((aCross ^ aPhaseGDomainWordCross) ^ aNonceWordG));
            //
            aScatter = (RotL64(aCarry, 53U) + RotL64(aPrevious, 35U)) ^ (RotL64(aCross, 19U) + RotL64(aIngress, 6U));
            aScatter = TwistMix64::DiffuseA(((aScatter ^ aPhaseGDomainWordScatter) ^ aNonceWordM));
            //
            aOrbiterI = ((aWandererD + RotL64(aIngress, 29U)) + RotL64(aCarry, 21U)) + 3612110001869385068U;
            aOrbiterA = (((aWandererC + RotL64(aPrevious, 4U)) + RotL64(aCarry, 35U)) + 16340824141280225936U) + aNonceWordF;
            aOrbiterJ = ((aWandererJ + RotL64(aScatter, 51U)) + 15222338965130765231U) + aPhaseGOrbiterAssignSaltD[(((31U - aIndex) + 20U)) & S_SALT1];
            aOrbiterB = (aWandererF + RotL64(aCross, 57U)) + 6649270508107155041U;
            aOrbiterF = (aWandererH + RotL64(aScatter, 37U)) + 768217258655426384U;
            aOrbiterD = (((aWandererK + RotL64(aCross, 11U)) + RotL64(aCarry, 51U)) + 4481855259658861851U) + aPhaseGOrbiterAssignSaltF[(((31U - aIndex) + 27U)) & S_SALT1];
            aOrbiterE = ((aWandererG + RotL64(aPrevious, 19U)) + 18318041934562434016U) + aNonceWordM;
            //
            aOrbiterI = ((aOrbiterI + aOrbiterA) + 4212457153804401807U) + aNonceWordE;
            aOrbiterJ = (aOrbiterJ ^ aOrbiterI) ^ 16143621095636987628U;
            aOrbiterJ = RotL64((aOrbiterJ * 6576072860505961427U), 35U);
            //
            aOrbiterB = ((aOrbiterB + aOrbiterF) + 2095664232866642086U) + aNonceWordL;
            aOrbiterI = (aOrbiterI ^ aOrbiterB) ^ 4339527736737366572U;
            aOrbiterI = RotL64((aOrbiterI * 17503569508822244125U), 23U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterB) + 13679353177869884790U;
            aOrbiterF = (aOrbiterF ^ aOrbiterD) ^ 11582168502846418236U;
            aOrbiterF = RotL64((aOrbiterF * 135539430034462861U), 41U);
            //
            aOrbiterE = ((aOrbiterE + aOrbiterD) + 10451330452898542191U) + aPhaseGOrbiterUpdateSaltE[(((31U - aIndex) + 15U)) & S_SALT1];
            aOrbiterB = (((aOrbiterB ^ aOrbiterE) ^ 12951448817640617841U) ^ aPhaseGOrbiterUpdateSaltD[((aIndex + 12U)) & S_SALT1]) ^ aNonceWordD;
            aOrbiterB = RotL64((aOrbiterB * 4141870904192742091U), 13U);
            //
            aOrbiterJ = ((aOrbiterJ + aOrbiterE) + 15389161934419370747U) + aPhaseGOrbiterUpdateSaltC[((aIndex + 25U)) & S_SALT1];
            aOrbiterD = (aOrbiterD ^ aOrbiterJ) ^ 4754886272708253014U;
            aOrbiterD = RotL64((aOrbiterD * 16638243718191281597U), 29U);
            //
            aOrbiterF = ((aOrbiterF + aOrbiterI) + 11746389873929280688U) + aPhaseGOrbiterUpdateSaltB[((aIndex + 23U)) & S_SALT1];
            aOrbiterA = (aOrbiterA ^ aOrbiterF) ^ 12042680172517298768U;
            aOrbiterA = RotL64((aOrbiterA * 3814780289755857543U), 47U);
            //
            aOrbiterA = ((aOrbiterA + aOrbiterJ) + 2648103752465009244U) + aNonceWordH;
            aOrbiterE = (aOrbiterE ^ aOrbiterA) ^ 451594673632597973U;
            aOrbiterE = RotL64((aOrbiterE * 8496763663271072425U), 3U);
            //
            aIngress = aOrbiterB ^ RotL64(aOrbiterI, 35U);
            aIngress = aIngress + (RotL64(aOrbiterD, 47U) ^ aOrbiterA);
            aIngress = aIngress + (aOrbiterF ^ RotL64(aOrbiterE, 41U));
            aIngress = aIngress + RotL64(aOrbiterJ, 57U);
            aIngress = TwistMix64::DiffuseA((aIngress + aScatter));
            //
            aWandererC = aWandererC + (((RotL64(aCross, 5U) + RotL64(aOrbiterF, 39U)) + aOrbiterD) + RotL64(aCarry, 37U));
            aWandererH = aWandererH ^ (((RotL64(aIngress, 46U) + RotL64(aOrbiterF, 13U)) + aOrbiterB) + aNonceWordA);
            aWandererK = aWandererK + (((RotL64(aScatter, 23U) + RotL64(aOrbiterA, 29U)) + aOrbiterE) + aNonceWordK);
            aWandererJ = aWandererJ ^ ((((RotL64(aPrevious, 11U) + RotL64(aOrbiterB, 5U)) + aOrbiterI) + aNonceWordI) + aPhaseGWandererUpdateSaltC[((aIndex + 22U)) & S_SALT1]);
            aWandererD = aWandererD + ((RotL64(aIngress, 53U) + RotL64(aOrbiterJ, 23U)) + aOrbiterI);
            aWandererG = aWandererG ^ (((RotL64(aCross, 29U) + RotL64(aOrbiterA, 46U)) + aOrbiterF) + aPhaseGWandererUpdateSaltB[(((31U - aIndex) + 29U)) & S_SALT1]);
            aWandererF = aWandererF + (((RotL64(aScatter, 35U) + aOrbiterI) + RotL64(aOrbiterE, 53U)) + RotL64(aCarry, 5U));
            //
            aCarry = aCarry + (aWandererF ^ RotL64(aWandererD, 10U));
            aCarry = aCarry + (RotL64(aWandererC, 35U) ^ aWandererG);
            aCarry = aCarry + (aWandererJ ^ RotL64(aWandererH, 39U));
            aCarry = aCarry + RotL64(aWandererK, 43U);
            aCarry = aCarry + RotL64(aIngress, 21U);
            aCarry = TwistMix64::DiffuseC(aCarry);
            //
            aExpandLaneA[aIndex] = aIngress;
        }
    
        // seed_loop_a loop 10
        // ingress from: aExpandLaneA, aKeyRowReadA, aFireLaneD, aFireLaneB
        // ingress directions: aExpandLaneA forward forced, aKeyRowReadA forward forced, aFireLaneD forward forced, aFireLaneB forward/backward random
        // cross from: aKeyRowReadB, mSource, aFireLaneC, aWorkLaneD
        // cross directions: aKeyRowReadB backward forced, mSource backward forced, aFireLaneC backward forced, aWorkLaneD backward/forward random
        // write to: aExpandLaneB
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aExpandLaneA[((aIndex + 25050U)) & S_BLOCK1], 12U) ^ RotL64(aKeyRowReadA[((aIndex + 27199U)) & W_KEY1], 21U));
            aIngress ^= (RotL64(aFireLaneD[((aIndex + 27104U)) & S_BLOCK1], 43U) ^ RotL64(aFireLaneB[((S_BLOCK1 - aIndex + 25917U)) & S_BLOCK1], 57U));
            aIngress = TwistMix64::DiffuseC(((aIngress ^ aPhaseHDomainWordIngress) ^ aNonceWordP));
            //
            aCross = (RotL64(aKeyRowReadB[(((2047U - aIndex) + 25021U)) & W_KEY1], 3U) ^ RotL64(mSource[((S_BLOCK1 - aIndex + 27020U)) & S_BLOCK1], 11U));
            aCross ^= (RotL64(aFireLaneC[((S_BLOCK1 - aIndex + 24684U)) & S_BLOCK1], 41U) ^ RotL64(aWorkLaneD[((S_BLOCK1 - aIndex + 25812U)) & S_BLOCK1], 21U));
            aCross = TwistMix64::DiffuseC(((aCross ^ aPhaseHDomainWordCross) ^ aNonceWordK));
            //
            aScatter = (RotL64(aCarry, 21U) + RotL64(aIngress, 57U)) ^ (RotL64(aPrevious, 6U) + RotL64(aCross, 41U));
            aScatter = TwistMix64::DiffuseC(((aScatter ^ aPhaseHDomainWordScatter) ^ aNonceWordH));
            //
            aOrbiterI = (((aWandererI + RotL64(aCross, 39U)) + RotL64(aCarry, 57U)) + 4751694786009671052U) + aNonceWordI;
            aOrbiterH = ((aWandererE + RotL64(aScatter, 14U)) + 16362725160370844224U) + aNonceWordH;
            aOrbiterE = (((aWandererH + RotL64(aPrevious, 51U)) + RotL64(aCarry, 39U)) + 6360885380915941057U) + aPhaseHOrbiterAssignSaltC[(((31U - aIndex) + 23U)) & S_SALT1];
            aOrbiterD = ((aWandererD + RotL64(aIngress, 3U)) + RotL64(aCarry, 21U)) + 5154536007972297036U;
            aOrbiterF = (aWandererJ + RotL64(aPrevious, 27U)) + 9362540581874808253U;
            aOrbiterK = (aWandererG + RotL64(aCross, 21U)) + 13902493871525612934U;
            aOrbiterB = ((aWandererA + RotL64(aIngress, 57U)) + 10208452885367546542U) + aPhaseHOrbiterAssignSaltD[((aIndex + 19U)) & S_SALT1];
            //
            aOrbiterI = (aOrbiterI + aOrbiterH) + 3117030377279160998U;
            aOrbiterE = (aOrbiterE ^ aOrbiterI) ^ 17286247690414027870U;
            aOrbiterE = RotL64((aOrbiterE * 4896931759653832095U), 5U);
            //
            aOrbiterE = (aOrbiterE + aOrbiterD) + 3930314320040949141U;
            aOrbiterF = ((aOrbiterF ^ aOrbiterE) ^ 7289525252391668404U) ^ aNonceWordL;
            aOrbiterF = RotL64((aOrbiterF * 15452162299105112187U), 47U);
            //
            aOrbiterH = ((aOrbiterH + aOrbiterE) + 3434167955466809185U) + aPhaseHOrbiterUpdateSaltE[((aIndex + 24U)) & S_SALT1];
            aOrbiterD = (aOrbiterD ^ aOrbiterH) ^ 17852573095128575663U;
            aOrbiterD = RotL64((aOrbiterD * 1485660158767033425U), 41U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterF) + 6137259687928853253U;
            aOrbiterK = ((aOrbiterK ^ aOrbiterD) ^ 13992510605237574698U) ^ aPhaseHOrbiterUpdateSaltD[(((31U - aIndex) + 18U)) & S_SALT1];
            aOrbiterK = RotL64((aOrbiterK * 15346263295995333395U), 35U);
            //
            aOrbiterF = (aOrbiterF + aOrbiterK) + 6470556523400123474U;
            aOrbiterB = (aOrbiterB ^ aOrbiterF) ^ 4333255670390099293U;
            aOrbiterB = RotL64((aOrbiterB * 11089933812030082647U), 29U);
            //
            aOrbiterK = ((aOrbiterK + aOrbiterB) + 7700424876430257995U) + aPhaseHOrbiterUpdateSaltF[((aIndex + 14U)) & S_SALT1];
            aOrbiterI = (aOrbiterI ^ aOrbiterK) ^ 16920736951239453071U;
            aOrbiterI = RotL64((aOrbiterI * 8920407493132380497U), 53U);
            //
            aOrbiterB = (aOrbiterB + aOrbiterI) + 1635071690430295730U;
            aOrbiterH = (((aOrbiterH ^ aOrbiterB) ^ 9966700845966398620U) ^ aPhaseHOrbiterUpdateSaltB[(((31U - aIndex) + 7U)) & S_SALT1]) ^ aNonceWordB;
            aOrbiterH = RotL64((aOrbiterH * 17210048121896546867U), 13U);
            //
            aIngress = aOrbiterE ^ RotL64(aOrbiterF, 35U);
            aIngress = aIngress + (aOrbiterK ^ RotL64(aOrbiterD, 41U));
            aIngress = aIngress + (aOrbiterB ^ RotL64(aOrbiterH, 11U));
            aIngress = aIngress + RotL64(aOrbiterI, 47U);
            aIngress = TwistMix64::DiffuseA((aIngress + aScatter));
            //
            aWandererI = aWandererI ^ ((RotL64(aPrevious, 43U) + RotL64(aOrbiterB, 27U)) + aOrbiterH);
            aWandererA = aWandererA + (((RotL64(aCross, 13U) + aOrbiterD) + RotL64(aOrbiterF, 5U)) + aNonceWordF);
            aWandererE = aWandererE ^ (((RotL64(aScatter, 29U) + RotL64(aOrbiterF, 18U)) + aOrbiterH) + aNonceWordN);
            aWandererG = aWandererG + (((RotL64(aIngress, 51U) + RotL64(aOrbiterE, 11U)) + aOrbiterF) + RotL64(aCarry, 35U));
            aWandererD = aWandererD ^ ((RotL64(aScatter, 58U) + RotL64(aOrbiterH, 41U)) + aOrbiterI);
            aWandererH = aWandererH + ((((RotL64(aPrevious, 19U) + aOrbiterD) + RotL64(aOrbiterH, 57U)) + RotL64(aCarry, 47U)) + aPhaseHWandererUpdateSaltD[(((31U - aIndex) + 21U)) & S_SALT1]);
            aWandererJ = aWandererJ ^ (((RotL64(aIngress, 5U) + aOrbiterI) + RotL64(aOrbiterK, 51U)) + aPhaseHWandererUpdateSaltE[((aIndex + 15U)) & S_SALT1]);
            //
            aCarry = aCarry + (RotL64(aWandererG, 14U) ^ aWandererA);
            aCarry = aCarry + (RotL64(aWandererJ, 29U) ^ aWandererH);
            aCarry = aCarry + (RotL64(aWandererI, 5U) ^ aWandererE);
            aCarry = aCarry + RotL64(aWandererD, 57U);
            aCarry = aCarry + RotL64(aIngress, 37U);
            aCarry = TwistMix64::DiffuseC(aCarry);
            //
            aExpandLaneB[S_BLOCK1 - aIndex] = aIngress;
        }
    
        // seed_loop_a loop 11
        // ingress from: aExpandLaneB, aFireLaneD, aKeyRowReadB, aFireLaneC
        // ingress directions: aExpandLaneB forward forced, aFireLaneD forward forced, aKeyRowReadB forward forced, aFireLaneC forward/backward random
        // cross from: aKeyRowReadA, mSource, aExpandLaneA, aFireLaneB
        // cross directions: aKeyRowReadA backward forced, mSource backward forced, aExpandLaneA backward forced, aFireLaneB backward/forward random
        // write to: aExpandLaneC
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aExpandLaneB[((aIndex + 28600U)) & S_BLOCK1], 57U) ^ RotL64(aFireLaneD[((aIndex + 27480U)) & S_BLOCK1], 6U));
            aIngress ^= (RotL64(aKeyRowReadB[((aIndex + 28586U)) & W_KEY1], 21U) ^ RotL64(aFireLaneC[((S_BLOCK1 - aIndex + 27604U)) & S_BLOCK1], 29U));
            aIngress = TwistMix64::DiffuseA(((aIngress ^ aPhaseHDomainWordIngress) ^ aNonceWordD));
            //
            aCross = (RotL64(aKeyRowReadA[(((2047U - aIndex) + 29029U)) & W_KEY1], 13U) ^ RotL64(mSource[((S_BLOCK1 - aIndex + 29844U)) & S_BLOCK1], 26U));
            aCross ^= (RotL64(aExpandLaneA[((S_BLOCK1 - aIndex + 29145U)) & S_BLOCK1], 5U) ^ RotL64(aFireLaneB[((aIndex + 28914U)) & S_BLOCK1], 37U));
            aCross = TwistMix64::DiffuseA(((aCross ^ aPhaseHDomainWordCross) ^ aNonceWordG));
            //
            aScatter = (RotL64(aPrevious, 10U) ^ RotL64(aCross, 23U)) + (RotL64(aIngress, 57U) ^ RotL64(aCarry, 41U));
            aScatter = TwistMix64::DiffuseC(((aScatter ^ aPhaseHDomainWordScatter) ^ aNonceWordO));
            //
            aOrbiterJ = ((aWandererK + RotL64(aPrevious, 30U)) + RotL64(aCarry, 27U)) + 12809562813316740345U;
            aOrbiterC = ((((aWandererE + RotL64(aIngress, 5U)) + RotL64(aCarry, 51U)) + 17084212535326321199U) + aPhaseHOrbiterAssignSaltD[((aIndex + 12U)) & S_SALT1]) + aNonceWordH;
            aOrbiterA = ((aWandererF + RotL64(aCross, 51U)) + RotL64(aCarry, 11U)) + 16074921689983846769U;
            aOrbiterH = ((aWandererD + RotL64(aScatter, 37U)) + 14027986153007120145U) + aNonceWordE;
            aOrbiterK = ((aWandererB + RotL64(aIngress, 11U)) + 7633455951809250227U) + aNonceWordL;
            aOrbiterE = (((aWandererA + RotL64(aCross, 57U)) + 340989348513370174U) + aPhaseHOrbiterAssignSaltC[(((31U - aIndex) + 19U)) & S_SALT1]) + aNonceWordI;
            aOrbiterG = (aWandererI + RotL64(aPrevious, 21U)) + 5307820377645020116U;
            //
            aOrbiterJ = (aOrbiterJ + aOrbiterC) + 5605285015771527274U;
            aOrbiterA = ((aOrbiterA ^ aOrbiterJ) ^ 5293500434746182790U) ^ aPhaseHOrbiterUpdateSaltF[((aIndex + 9U)) & S_SALT1];
            aOrbiterA = RotL64((aOrbiterA * 17674669610895537063U), 47U);
            //
            aOrbiterH = ((aOrbiterH + aOrbiterA) + 7263156475892261811U) + aNonceWordJ;
            aOrbiterK = ((aOrbiterK ^ aOrbiterH) ^ 10672879570907433005U) ^ aPhaseHOrbiterUpdateSaltD[(((31U - aIndex) + 5U)) & S_SALT1];
            aOrbiterK = RotL64((aOrbiterK * 2506338667179450741U), 19U);
            //
            aOrbiterE = (aOrbiterE + aOrbiterK) + 16659226780900986107U;
            aOrbiterJ = (aOrbiterJ ^ aOrbiterE) ^ 9774892622769850665U;
            aOrbiterJ = RotL64((aOrbiterJ * 7487477727543183211U), 41U);
            //
            aOrbiterC = (aOrbiterC + aOrbiterH) + 10728057184108279042U;
            aOrbiterE = (aOrbiterE ^ aOrbiterC) ^ 5032485856947407217U;
            aOrbiterE = RotL64((aOrbiterE * 16651577903809154285U), 35U);
            //
            aOrbiterG = (aOrbiterG + aOrbiterJ) + 14642241075374862345U;
            aOrbiterH = ((aOrbiterH ^ aOrbiterG) ^ 8386481273395203518U) ^ aNonceWordK;
            aOrbiterH = RotL64((aOrbiterH * 11649977733867003445U), 27U);
            //
            aOrbiterK = ((aOrbiterK + aOrbiterG) + 2874153265304098104U) + aPhaseHOrbiterUpdateSaltC[((aIndex + 24U)) & S_SALT1];
            aOrbiterC = (aOrbiterC ^ aOrbiterK) ^ 11519900149177261000U;
            aOrbiterC = RotL64((aOrbiterC * 2010158758971864505U), 3U);
            //
            aOrbiterA = ((aOrbiterA + aOrbiterE) + 8885690878540115768U) + aPhaseHOrbiterUpdateSaltB[((aIndex + 27U)) & S_SALT1];
            aOrbiterG = (aOrbiterG ^ aOrbiterA) ^ 4482143389870987714U;
            aOrbiterG = RotL64((aOrbiterG * 7105332459437434281U), 53U);
            //
            aIngress = RotL64(aOrbiterE, 53U) ^ aOrbiterG;
            aIngress = aIngress + (aOrbiterK ^ RotL64(aOrbiterC, 3U));
            aIngress = aIngress + (aOrbiterJ ^ RotL64(aOrbiterA, 29U));
            aIngress = aIngress + RotL64(aOrbiterH, 60U);
            aIngress = TwistMix64::DiffuseC((aIngress + aScatter));
            //
            aWandererD = aWandererD + (((RotL64(aPrevious, 11U) + RotL64(aOrbiterE, 5U)) + aOrbiterK) + RotL64(aCarry, 37U));
            aWandererB = aWandererB ^ ((RotL64(aCross, 47U) + aOrbiterJ) + RotL64(aOrbiterG, 43U));
            aWandererF = aWandererF + (((RotL64(aScatter, 37U) + RotL64(aOrbiterE, 35U)) + aOrbiterJ) + aPhaseHWandererUpdateSaltB[(((31U - aIndex) + 18U)) & S_SALT1]);
            aWandererI = aWandererI ^ (((RotL64(aIngress, 23U) + RotL64(aOrbiterG, 11U)) + aOrbiterK) + aNonceWordM);
            aWandererE = aWandererE + (((RotL64(aScatter, 30U) + aOrbiterG) + RotL64(aOrbiterA, 22U)) + RotL64(aCarry, 19U));
            aWandererA = aWandererA ^ (((RotL64(aIngress, 5U) + aOrbiterC) + RotL64(aOrbiterK, 51U)) + aPhaseHWandererUpdateSaltD[((aIndex + 16U)) & S_SALT1]);
            aWandererK = aWandererK + (((RotL64(aCross, 53U) + aOrbiterC) + RotL64(aOrbiterH, 57U)) + aNonceWordC);
            //
            aCarry = aCarry + (aWandererB ^ RotL64(aWandererD, 35U));
            aCarry = aCarry + (aWandererE ^ RotL64(aWandererK, 26U));
            aCarry = aCarry + (RotL64(aWandererF, 51U) ^ aWandererI);
            aCarry = aCarry + RotL64(aWandererA, 57U);
            aCarry = aCarry + RotL64(aIngress, 47U);
            aCarry = TwistMix64::DiffuseC(aCarry);
            //
            aExpandLaneC[aIndex] = aIngress;
        }
    
        // seed_loop_a loop 12
        // ingress from: aExpandLaneC, aKeyRowReadA
        // ingress directions: aExpandLaneC forward forced, aKeyRowReadA forward/backward random
        // cross from: aFireLaneD, aExpandLaneA, aExpandLaneB, aKeyRowReadB
        // cross directions: aFireLaneD backward forced, aExpandLaneA backward forced, aExpandLaneB backward forced, aKeyRowReadB backward/forward random
        // write to: aExpandLaneD
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = RotL64(aExpandLaneC[((aIndex + 30646U)) & S_BLOCK1], 22U) ^ RotL64(aKeyRowReadA[((aIndex + 30929U)) & W_KEY1], 51U);
            aIngress = TwistMix64::DiffuseB(((aIngress ^ aPhaseHDomainWordIngress) ^ aNonceWordL));
            //
            aCross = (RotL64(aFireLaneD[((S_BLOCK1 - aIndex + 31945U)) & S_BLOCK1], 3U) ^ RotL64(aExpandLaneA[((S_BLOCK1 - aIndex + 31441U)) & S_BLOCK1], 11U));
            aCross ^= (RotL64(aExpandLaneB[((S_BLOCK1 - aIndex + 30633U)) & S_BLOCK1], 19U) ^ RotL64(aKeyRowReadB[(((2047U - aIndex) + 32716U)) & W_KEY1], 57U));
            aCross = TwistMix64::DiffuseB(((aCross ^ aPhaseHDomainWordCross) ^ aNonceWordA));
            //
            aScatter = (RotL64(aCarry, 23U) ^ RotL64(aPrevious, 57U)) + (RotL64(aCross, 11U) ^ RotL64(aIngress, 44U));
            aScatter = TwistMix64::DiffuseC(((aScatter ^ aPhaseHDomainWordScatter) ^ aNonceWordF));
            //
            aOrbiterI = (aWandererF + RotL64(aCross, 27U)) + 16424657151168221875U;
            aOrbiterE = ((aWandererK + RotL64(aScatter, 13U)) + 17150123681886380361U) + aPhaseHOrbiterAssignSaltB[(((31U - aIndex) + 23U)) & S_SALT1];
            aOrbiterB = (((aWandererH + RotL64(aIngress, 35U)) + RotL64(aCarry, 11U)) + 16041993588694572757U) + aNonceWordD;
            aOrbiterD = ((aWandererG + RotL64(aPrevious, 41U)) + RotL64(aCarry, 53U)) + 9871185846434828537U;
            aOrbiterC = (((aWandererE + RotL64(aScatter, 60U)) + RotL64(aCarry, 27U)) + 11227236398354430757U) + aPhaseHOrbiterAssignSaltE[(((31U - aIndex) + 11U)) & S_SALT1];
            aOrbiterH = ((aWandererA + RotL64(aPrevious, 19U)) + 5399325217402192631U) + aNonceWordI;
            aOrbiterA = (aWandererI + RotL64(aCross, 47U)) + 9248828789282890454U;
            //
            aOrbiterI = (aOrbiterI + aOrbiterE) + 9041370494203701062U;
            aOrbiterB = ((aOrbiterB ^ aOrbiterI) ^ 14944424084524970764U) ^ aNonceWordO;
            aOrbiterB = RotL64((aOrbiterB * 10283363059424655079U), 57U);
            //
            aOrbiterB = ((aOrbiterB + aOrbiterD) + 5481938174456671041U) + aPhaseHOrbiterUpdateSaltA[((aIndex + 16U)) & S_SALT1];
            aOrbiterC = (aOrbiterC ^ aOrbiterB) ^ 14783648629543752715U;
            aOrbiterC = RotL64((aOrbiterC * 7260164783191886395U), 13U);
            //
            aOrbiterH = ((aOrbiterH + aOrbiterB) + 12355573914530445723U) + aNonceWordP;
            aOrbiterA = (aOrbiterA ^ aOrbiterH) ^ 9863991559011968318U;
            aOrbiterA = RotL64((aOrbiterA * 8495251211794343179U), 5U);
            //
            aOrbiterD = (((aOrbiterD + aOrbiterI) + 16149688605937250965U) + aPhaseHOrbiterUpdateSaltB[((aIndex + 13U)) & S_SALT1]) + aNonceWordN;
            aOrbiterH = (aOrbiterH ^ aOrbiterD) ^ 106041828692026825U;
            aOrbiterH = RotL64((aOrbiterH * 12199934305374582599U), 19U);
            //
            aOrbiterE = (aOrbiterE + aOrbiterA) + 8076098639554567792U;
            aOrbiterD = (aOrbiterD ^ aOrbiterE) ^ 11155119311895580013U;
            aOrbiterD = RotL64((aOrbiterD * 1495180896564818647U), 39U);
            //
            aOrbiterC = ((aOrbiterC + aOrbiterH) + 6847612160595917702U) + aNonceWordE;
            aOrbiterE = ((aOrbiterE ^ aOrbiterC) ^ 16094377920388017367U) ^ aPhaseHOrbiterUpdateSaltF[((aIndex + 18U)) & S_SALT1];
            aOrbiterE = RotL64((aOrbiterE * 4875801863643206333U), 27U);
            //
            aOrbiterA = (aOrbiterA + aOrbiterC) + 13584719866672696684U;
            aOrbiterI = ((aOrbiterI ^ aOrbiterA) ^ 13446209321646234607U) ^ aPhaseHOrbiterUpdateSaltD[((aIndex + 3U)) & S_SALT1];
            aOrbiterI = RotL64((aOrbiterI * 9945349065094781529U), 47U);
            //
            aIngress = aOrbiterD ^ RotL64(aOrbiterB, 26U);
            aIngress = aIngress + (aOrbiterI ^ RotL64(aOrbiterA, 47U));
            aIngress = aIngress + (aOrbiterE ^ RotL64(aOrbiterH, 53U));
            aIngress = aIngress + RotL64(aOrbiterC, 41U);
            aIngress = TwistMix64::DiffuseA((aIngress + aScatter));
            //
            aWandererH = aWandererH ^ (((RotL64(aScatter, 56U) + aOrbiterE) + RotL64(aOrbiterI, 11U)) + aPhaseHWandererUpdateSaltA[(((31U - aIndex) + 19U)) & S_SALT1]);
            aWandererK = aWandererK + ((((RotL64(aPrevious, 47U) + aOrbiterC) + RotL64(aOrbiterA, 39U)) + RotL64(aCarry, 37U)) + aNonceWordH);
            aWandererI = aWandererI ^ ((RotL64(aIngress, 21U) + aOrbiterH) + RotL64(aOrbiterD, 57U));
            aWandererA = aWandererA + (((RotL64(aCross, 29U) + aOrbiterE) + RotL64(aOrbiterC, 5U)) + aNonceWordB);
            aWandererE = aWandererE ^ ((RotL64(aIngress, 5U) + aOrbiterA) + RotL64(aOrbiterH, 50U));
            aWandererF = aWandererF + (((RotL64(aCross, 11U) + RotL64(aOrbiterI, 29U)) + aOrbiterD) + RotL64(aCarry, 51U));
            aWandererG = aWandererG ^ ((((RotL64(aScatter, 37U) + aOrbiterB) + RotL64(aOrbiterI, 19U)) + aNonceWordM) + aPhaseHWandererUpdateSaltB[((aIndex + 29U)) & S_SALT1]);
            //
            aCarry = aCarry + (RotL64(aWandererK, 36U) ^ aWandererF);
            aCarry = aCarry + (aWandererI ^ RotL64(aWandererE, 41U));
            aCarry = aCarry + (aWandererG ^ RotL64(aWandererA, 13U));
            aCarry = aCarry + RotL64(aWandererH, 5U);
            aCarry = aCarry + RotL64(aIngress, 23U);
            aCarry = TwistMix64::DiffuseA(aCarry);
            //
            aExpandLaneD[S_BLOCK1 - aIndex] = aIngress;
        }
    }
    // GSeedRunSeed_A seed_loop_a (end)
    *pPrevious = aPrevious;
    *pIngress = aIngress;
    *pCarry = aCarry;
    *pWandererA = aWandererA;
    *pWandererB = aWandererB;
    *pWandererC = aWandererC;
    *pWandererD = aWandererD;
    *pWandererE = aWandererE;
    *pWandererF = aWandererF;
    *pWandererG = aWandererG;
    *pWandererH = aWandererH;
    *pWandererI = aWandererI;
    *pWandererJ = aWandererJ;
    *pWandererK = aWandererK;
}

void TwistExpander_Exercea_Arx::Seed_B(TwistWorkSpace *pWorkSpace,
                     std::uint64_t pNonce,
                     std::uint64_t *pPrevious,
                     std::uint64_t *pIngress,
                     std::uint64_t *pCarry,
                     std::uint64_t *pWandererA,
                     std::uint64_t *pWandererB,
                     std::uint64_t *pWandererC,
                     std::uint64_t *pWandererD,
                     std::uint64_t *pWandererE,
                     std::uint64_t *pWandererF,
                     std::uint64_t *pWandererG,
                     std::uint64_t *pWandererH,
                     std::uint64_t *pWandererI,
                     std::uint64_t *pWandererJ,
                     std::uint64_t *pWandererK) {
    [[maybe_unused]] std::uint8_t *aExpandLaneA = pWorkSpace->mExpansionLaneA;
    [[maybe_unused]] std::uint8_t *aExpandLaneB = pWorkSpace->mExpansionLaneB;
    [[maybe_unused]] std::uint8_t *aExpandLaneC = pWorkSpace->mExpansionLaneC;
    [[maybe_unused]] std::uint8_t *aExpandLaneD = pWorkSpace->mExpansionLaneD;
    [[maybe_unused]] std::uint8_t *aOperationLaneA = pWorkSpace->mOperationLaneA;
    [[maybe_unused]] std::uint8_t *aOperationLaneB = pWorkSpace->mOperationLaneB;
    [[maybe_unused]] std::uint8_t *aOperationLaneC = pWorkSpace->mOperationLaneC;
    [[maybe_unused]] std::uint8_t *aOperationLaneD = pWorkSpace->mOperationLaneD;
    [[maybe_unused]] std::uint8_t *aFireLaneA = pWorkSpace->mFireLaneA;
    [[maybe_unused]] std::uint8_t *aFireLaneB = pWorkSpace->mFireLaneB;
    [[maybe_unused]] std::uint8_t *aFireLaneC = pWorkSpace->mFireLaneC;
    [[maybe_unused]] std::uint8_t *aFireLaneD = pWorkSpace->mFireLaneD;
    [[maybe_unused]] std::uint8_t *aInvestLaneA = pWorkSpace->mInvestLaneA;
    [[maybe_unused]] std::uint8_t *aInvestLaneB = pWorkSpace->mInvestLaneB;
    [[maybe_unused]] std::uint64_t *aPhaseAOrbiterAssignSaltA = pWorkSpace->mDomainBundle.mPhaseASalts.mOrbiterAssign.mSaltA;
    [[maybe_unused]] std::uint64_t *aPhaseAOrbiterAssignSaltB = pWorkSpace->mDomainBundle.mPhaseASalts.mOrbiterAssign.mSaltB;
    [[maybe_unused]] std::uint64_t *aPhaseAOrbiterAssignSaltC = pWorkSpace->mDomainBundle.mPhaseASalts.mOrbiterAssign.mSaltC;
    [[maybe_unused]] std::uint64_t *aPhaseAOrbiterAssignSaltD = pWorkSpace->mDomainBundle.mPhaseASalts.mOrbiterAssign.mSaltD;
    [[maybe_unused]] std::uint64_t *aPhaseAOrbiterAssignSaltE = pWorkSpace->mDomainBundle.mPhaseASalts.mOrbiterAssign.mSaltE;
    [[maybe_unused]] std::uint64_t *aPhaseAOrbiterAssignSaltF = pWorkSpace->mDomainBundle.mPhaseASalts.mOrbiterAssign.mSaltF;
    [[maybe_unused]] std::uint64_t *aPhaseAOrbiterUpdateSaltA = pWorkSpace->mDomainBundle.mPhaseASalts.mOrbiterUpdate.mSaltA;
    [[maybe_unused]] std::uint64_t *aPhaseAOrbiterUpdateSaltB = pWorkSpace->mDomainBundle.mPhaseASalts.mOrbiterUpdate.mSaltB;
    [[maybe_unused]] std::uint64_t *aPhaseAOrbiterUpdateSaltC = pWorkSpace->mDomainBundle.mPhaseASalts.mOrbiterUpdate.mSaltC;
    [[maybe_unused]] std::uint64_t *aPhaseAOrbiterUpdateSaltD = pWorkSpace->mDomainBundle.mPhaseASalts.mOrbiterUpdate.mSaltD;
    [[maybe_unused]] std::uint64_t *aPhaseAOrbiterUpdateSaltE = pWorkSpace->mDomainBundle.mPhaseASalts.mOrbiterUpdate.mSaltE;
    [[maybe_unused]] std::uint64_t *aPhaseAOrbiterUpdateSaltF = pWorkSpace->mDomainBundle.mPhaseASalts.mOrbiterUpdate.mSaltF;
    [[maybe_unused]] std::uint64_t *aPhaseAWandererUpdateSaltA = pWorkSpace->mDomainBundle.mPhaseASalts.mWandererUpdate.mSaltA;
    [[maybe_unused]] std::uint64_t *aPhaseAWandererUpdateSaltB = pWorkSpace->mDomainBundle.mPhaseASalts.mWandererUpdate.mSaltB;
    [[maybe_unused]] std::uint64_t *aPhaseAWandererUpdateSaltC = pWorkSpace->mDomainBundle.mPhaseASalts.mWandererUpdate.mSaltC;
    [[maybe_unused]] std::uint64_t *aPhaseAWandererUpdateSaltD = pWorkSpace->mDomainBundle.mPhaseASalts.mWandererUpdate.mSaltD;
    [[maybe_unused]] std::uint64_t *aPhaseAWandererUpdateSaltE = pWorkSpace->mDomainBundle.mPhaseASalts.mWandererUpdate.mSaltE;
    [[maybe_unused]] std::uint64_t *aPhaseAWandererUpdateSaltF = pWorkSpace->mDomainBundle.mPhaseASalts.mWandererUpdate.mSaltF;
    const std::uint64_t &aPhaseADomainWordIngress = pWorkSpace->mDomainBundle.mPhaseAConstants.mIngress;
    const std::uint64_t &aPhaseADomainWordScatter = pWorkSpace->mDomainBundle.mPhaseAConstants.mScatter;
    const std::uint64_t &aPhaseADomainWordCross = pWorkSpace->mDomainBundle.mPhaseAConstants.mCross;
    std::uint64_t aCross = 0; std::uint64_t aScatter = 0;

    std::uint64_t aOrbiterA = 0; std::uint64_t aOrbiterB = 0; std::uint64_t aOrbiterC = 0; std::uint64_t aOrbiterD = 0;
    std::uint64_t aOrbiterE = 0; std::uint64_t aOrbiterF = 0; std::uint64_t aOrbiterG = 0; std::uint64_t aOrbiterH = 0;
    std::uint64_t aOrbiterI = 0; std::uint64_t aOrbiterJ = 0; std::uint64_t aOrbiterK = 0;

    // [seed arx]
    [[maybe_unused]] std::uint8_t *mSource = pWorkSpace->mSource;
    std::uint64_t aPrevious = *pPrevious;
    std::uint64_t aIngress = *pIngress;
    std::uint64_t aCarry = *pCarry;
    std::uint64_t aWandererA = *pWandererA;
    std::uint64_t aWandererB = *pWandererB;
    std::uint64_t aWandererC = *pWandererC;
    std::uint64_t aWandererD = *pWandererD;
    std::uint64_t aWandererE = *pWandererE;
    std::uint64_t aWandererF = *pWandererF;
    std::uint64_t aWandererG = *pWandererG;
    std::uint64_t aWandererH = *pWandererH;
    std::uint64_t aWandererI = *pWandererI;
    std::uint64_t aWandererJ = *pWandererJ;
    std::uint64_t aWandererK = *pWandererK;
    std::uint64_t aNonceWordA = TwistMix64::DiffuseC(pNonce * 0x8E34DC1778854559ULL + 0xF180EB57CEE64890ULL);
    std::uint64_t aNonceWordB = TwistMix64::DiffuseB(pNonce * 0xA19DAFB5B1EEE2E7ULL + 0x838BB3C263ACC983ULL);
    std::uint64_t aNonceWordC = TwistMix64::DiffuseB(pNonce * 0x9512B2CBF87527ABULL + 0xE2B99D88803BCC93ULL);
    std::uint64_t aNonceWordD = TwistMix64::DiffuseC(pNonce * 0xB0B30C1F02A4C025ULL + 0xDD4F05951475085FULL);
    std::uint64_t aNonceWordE = TwistMix64::DiffuseC(pNonce * 0xF03067A9D8C0B801ULL + 0x989D5F1903447141ULL);
    std::uint64_t aNonceWordF = TwistMix64::DiffuseC(pNonce * 0xCF052324B147A95FULL + 0x92EE898E8B7C9910ULL);
    std::uint64_t aNonceWordG = TwistMix64::DiffuseA(pNonce * 0xAB7C2EB93F1DA5C1ULL + 0xF570258196317CA3ULL);
    std::uint64_t aNonceWordH = TwistMix64::DiffuseC(pNonce * 0xF70413FBAF4201EFULL + 0xEFD3A4F59F5D3F3DULL);
    std::uint64_t aNonceWordI = TwistMix64::DiffuseB(pNonce * 0xF0F30D52223C562FULL + 0x99A1D5CC6BFD78CBULL);
    std::uint64_t aNonceWordJ = TwistMix64::DiffuseB(pNonce * 0xB4DC5AA557688995ULL + 0xFC3A91F0CBACCAB3ULL);
    std::uint64_t aNonceWordK = TwistMix64::DiffuseB(pNonce * 0xDA3769846C18BEEDULL + 0x9815D6D005DAC7D1ULL);
    std::uint64_t aNonceWordL = TwistMix64::DiffuseB(pNonce * 0x8E8CFEE3F1A132A3ULL + 0xC6602587FECB38A5ULL);
    std::uint64_t aNonceWordM = TwistMix64::DiffuseB(pNonce * 0xF9B1B4BD4F6F8377ULL + 0x8EAA777AD35CD89AULL);
    std::uint64_t aNonceWordN = TwistMix64::DiffuseA(pNonce * 0x83B0F4B0780BD2ADULL + 0x8B9ABBBDA22342EBULL);
    std::uint64_t aNonceWordO = TwistMix64::DiffuseA(pNonce * 0xE1E3EE2A49E46B85ULL + 0xA4C16A932B9A886DULL);
    std::uint64_t aNonceWordP = TwistMix64::DiffuseB(pNonce * 0xE7F8BB51D07DC1DBULL + 0xF2E11AFBFDE883E0ULL);
    // GSeedRunSeed_B seed_loop_a (start)
    {
        // GSeedRunSeed_B seed_loop_a lane group
        // read from: aExpandLaneA, aExpandLaneB, aFireLaneC, aExpandLaneC, aExpandLaneD, aInvestLaneA, aFireLaneB, aInvestLaneB, aFireLaneD, aOperationLaneA, aFireLaneA, aOperationLaneB, aOperationLaneC
        // write to: aInvestLaneA, aInvestLaneB, aOperationLaneA, aOperationLaneB, aOperationLaneC, aOperationLaneD
    
        // seed_loop_a loop 1
        // ingress from: aExpandLaneA, aExpandLaneB, aFireLaneC
        // ingress directions: aExpandLaneA forward forced, aExpandLaneB forward forced, aFireLaneC forward/backward random
        // cross from: aExpandLaneC, aExpandLaneD
        // cross directions: aExpandLaneC backward forced, aExpandLaneD backward/forward random
        // write to: aInvestLaneA
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aExpandLaneA[((aIndex + 294U)) & S_BLOCK1], 14U) ^ RotL64(aExpandLaneB[((aIndex + 3265U)) & S_BLOCK1], 37U));
            aIngress ^= RotL64(aFireLaneC[((aIndex + 3503U)) & S_BLOCK1], 23U);
            aIngress = TwistMix64::DiffuseB(((aIngress ^ aPhaseADomainWordIngress) ^ aNonceWordP));
            //
            aCross = RotL64(aExpandLaneC[((S_BLOCK1 - aIndex + 4519U)) & S_BLOCK1], 37U) ^ RotL64(aExpandLaneD[((S_BLOCK1 - aIndex + 2632U)) & S_BLOCK1], 19U);
            aCross = TwistMix64::DiffuseA(((aCross ^ aPhaseADomainWordCross) ^ aNonceWordG));
            //
            aScatter = (RotL64(aPrevious, 47U) ^ RotL64(aCarry, 6U)) ^ (RotL64(aCross, 35U) + RotL64(aIngress, 23U));
            aScatter = TwistMix64::DiffuseA(((aScatter ^ aPhaseADomainWordScatter) ^ aNonceWordP));
            //
            aOrbiterK = ((((aWandererH + RotL64(aIngress, 43U)) + RotL64(aCarry, 13U)) + 6469584119078165548U) + aPhaseAOrbiterAssignSaltF[(((31U - aIndex) + 29U)) & S_SALT1]) + aNonceWordO;
            aOrbiterB = ((aWandererG + RotL64(aPrevious, 60U)) + 14329756366517987910U) + aPhaseAOrbiterAssignSaltE[(((31U - aIndex) + 24U)) & S_SALT1];
            aOrbiterG = ((aWandererA + RotL64(aScatter, 11U)) + RotL64(aCarry, 51U)) + 12890831797059772123U;
            aOrbiterD = ((aWandererF + RotL64(aCross, 51U)) + 3164503807500018990U) + aNonceWordE;
            aOrbiterI = ((aWandererB + RotL64(aPrevious, 19U)) + RotL64(aCarry, 29U)) + 177531431387646836U;
            //
            aOrbiterK = ((aOrbiterK + aOrbiterB) + 3167421392893561015U) + aNonceWordA;
            aOrbiterG = ((aOrbiterG ^ aOrbiterK) ^ 2813174781844753460U) ^ aPhaseAOrbiterUpdateSaltE[(((31U - aIndex) + 23U)) & S_SALT1];
            aOrbiterG = RotL64((aOrbiterG * 9760688894575305115U), 13U);
            //
            aOrbiterB = (aOrbiterB + aOrbiterG) + 10953270419153249857U;
            aOrbiterD = (((aOrbiterD ^ aOrbiterB) ^ 16911518309710356951U) ^ aPhaseAOrbiterUpdateSaltF[((aIndex + 11U)) & S_SALT1]) ^ aNonceWordJ;
            aOrbiterD = RotL64((aOrbiterD * 13162785997686570445U), 27U);
            //
            aOrbiterI = ((aOrbiterI + aOrbiterK) + 6616750447844893150U) + aPhaseAOrbiterUpdateSaltC[(((31U - aIndex) + 12U)) & S_SALT1];
            aOrbiterB = (aOrbiterB ^ aOrbiterI) ^ 10276741398025985982U;
            aOrbiterB = RotL64((aOrbiterB * 6824712685896987133U), 41U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterI) + 6206043608461213208U;
            aOrbiterK = ((aOrbiterK ^ aOrbiterD) ^ 12021552904553405793U) ^ aNonceWordM;
            aOrbiterK = RotL64((aOrbiterK * 10023362889960174909U), 3U);
            //
            aOrbiterG = ((aOrbiterG + aOrbiterD) + 15283586234744144846U) + aPhaseAOrbiterUpdateSaltA[((aIndex + 25U)) & S_SALT1];
            aOrbiterI = (aOrbiterI ^ aOrbiterG) ^ 5923238786775948571U;
            aOrbiterI = RotL64((aOrbiterI * 8200882393521882651U), 51U);
            //
            aIngress = RotL64(aOrbiterI, 53U) ^ aOrbiterK;
            aIngress = aIngress + (RotL64(aOrbiterD, 14U) ^ aOrbiterB);
            aIngress = aIngress + RotL64(aOrbiterG, 27U);
            aIngress = TwistMix64::DiffuseC((aIngress + aScatter));
            //
            aWandererA = aWandererA ^ ((RotL64(aCross, 40U) + RotL64(aOrbiterI, 34U)) + aOrbiterG);
            aWandererF = aWandererF + ((((RotL64(aIngress, 13U) + aOrbiterD) + RotL64(aOrbiterK, 43U)) + RotL64(aCarry, 53U)) + aNonceWordN);
            aWandererH = aWandererH ^ (((RotL64(aPrevious, 21U) + RotL64(aOrbiterD, 23U)) + aOrbiterB) + aNonceWordI);
            aWandererB = aWandererB + ((((RotL64(aScatter, 3U) + aOrbiterG) + RotL64(aOrbiterK, 13U)) + RotL64(aCarry, 29U)) + aPhaseAWandererUpdateSaltB[((aIndex + 27U)) & S_SALT1]);
            aWandererG = aWandererG ^ (((RotL64(aPrevious, 57U) + aOrbiterB) + RotL64(aOrbiterI, 3U)) + aPhaseAWandererUpdateSaltC[((aIndex + 17U)) & S_SALT1]);
            //
            aCarry = aCarry + (RotL64(aWandererB, 23U) ^ aWandererF);
            aCarry = aCarry + (aWandererA ^ RotL64(aWandererH, 56U));
            aCarry = aCarry + RotL64(aWandererG, 13U);
            aCarry = aCarry + RotL64(aIngress, 5U);
            aCarry = TwistMix64::DiffuseC(aCarry);
            //
            aInvestLaneA[aIndex] = aIngress;
        }
    
        // seed_loop_a loop 2
        // ingress from: aInvestLaneA, aExpandLaneC, aFireLaneB
        // ingress directions: aInvestLaneA forward forced, aExpandLaneC forward forced, aFireLaneB forward/backward random
        // cross from: aExpandLaneA, aExpandLaneD
        // cross directions: aExpandLaneA backward forced, aExpandLaneD backward/forward random
        // write to: aInvestLaneB
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aInvestLaneA[((aIndex + 8185U)) & S_BLOCK1], 57U) ^ RotL64(aExpandLaneC[((aIndex + 6314U)) & S_BLOCK1], 37U));
            aIngress ^= RotL64(aFireLaneB[((S_BLOCK1 - aIndex + 6574U)) & S_BLOCK1], 4U);
            aIngress = TwistMix64::DiffuseA(((aIngress ^ aPhaseADomainWordIngress) ^ aNonceWordA));
            //
            aCross = RotL64(aExpandLaneA[((S_BLOCK1 - aIndex + 10027U)) & S_BLOCK1], 50U) ^ RotL64(aExpandLaneD[((aIndex + 6541U)) & S_BLOCK1], 35U);
            aCross = TwistMix64::DiffuseC(((aCross ^ aPhaseADomainWordCross) ^ aNonceWordF));
            //
            aScatter = (RotL64(aPrevious, 3U) + RotL64(aCarry, 23U)) ^ (RotL64(aIngress, 35U) + RotL64(aCross, 52U));
            aScatter = TwistMix64::DiffuseC(((aScatter ^ aPhaseADomainWordScatter) ^ aNonceWordD));
            //
            aOrbiterH = ((aWandererD + RotL64(aScatter, 47U)) + 12426357877879529292U) + aPhaseAOrbiterAssignSaltA[(((31U - aIndex) + 4U)) & S_SALT1];
            aOrbiterA = ((((aWandererF + RotL64(aPrevious, 57U)) + RotL64(aCarry, 37U)) + 12604900366173639176U) + aPhaseAOrbiterAssignSaltB[(((31U - aIndex) + 25U)) & S_SALT1]) + aNonceWordP;
            aOrbiterF = (((aWandererJ + RotL64(aIngress, 3U)) + RotL64(aCarry, 3U)) + 13511119007338929401U) + aNonceWordM;
            aOrbiterI = (((aWandererI + RotL64(aCross, 29U)) + RotL64(aCarry, 23U)) + 9878720081166788060U) + aNonceWordG;
            aOrbiterC = (aWandererK + RotL64(aScatter, 20U)) + 15463195409806395076U;
            //
            aOrbiterH = (((aOrbiterH + aOrbiterA) + 6407922778852833423U) + aPhaseAOrbiterUpdateSaltC[((aIndex + 7U)) & S_SALT1]) + aNonceWordL;
            aOrbiterF = ((aOrbiterF ^ aOrbiterH) ^ 7690427254160734016U) ^ aPhaseAOrbiterUpdateSaltE[((aIndex + 15U)) & S_SALT1];
            aOrbiterF = RotL64((aOrbiterF * 11841396512731990295U), 57U);
            //
            aOrbiterA = (aOrbiterA + aOrbiterI) + 18030974031722143619U;
            aOrbiterC = (aOrbiterC ^ aOrbiterA) ^ 17983938038322737041U;
            aOrbiterC = RotL64((aOrbiterC * 12479365337221685413U), 13U);
            //
            aOrbiterI = (((aOrbiterI + aOrbiterF) + 16605512170117753884U) + aPhaseAOrbiterUpdateSaltB[(((31U - aIndex) + 8U)) & S_SALT1]) + aNonceWordI;
            aOrbiterH = ((aOrbiterH ^ aOrbiterI) ^ 681802273302348322U) ^ aPhaseAOrbiterUpdateSaltD[((aIndex + 27U)) & S_SALT1];
            aOrbiterH = RotL64((aOrbiterH * 14608920184802647123U), 5U);
            //
            aOrbiterF = (aOrbiterF + aOrbiterC) + 15550312921312083819U;
            aOrbiterA = (aOrbiterA ^ aOrbiterF) ^ 17824154101711884508U;
            aOrbiterA = RotL64((aOrbiterA * 7358612830654795357U), 27U);
            //
            aOrbiterC = ((aOrbiterC + aOrbiterH) + 1939207786756735430U) + aNonceWordJ;
            aOrbiterI = (aOrbiterI ^ aOrbiterC) ^ 3132864634777826569U;
            aOrbiterI = RotL64((aOrbiterI * 13606281919426730325U), 39U);
            //
            aIngress = aOrbiterI ^ RotL64(aOrbiterC, 23U);
            aIngress = aIngress + (RotL64(aOrbiterH, 47U) ^ aOrbiterA);
            aIngress = aIngress + RotL64(aOrbiterF, 35U);
            aIngress = TwistMix64::DiffuseC((aIngress + aScatter));
            //
            aWandererI = aWandererI ^ ((((RotL64(aCross, 47U) + aOrbiterI) + RotL64(aOrbiterA, 21U)) + aNonceWordK) + aPhaseAWandererUpdateSaltA[(((31U - aIndex) + 5U)) & S_SALT1]);
            aWandererD = aWandererD + ((((RotL64(aPrevious, 3U) + aOrbiterC) + RotL64(aOrbiterH, 56U)) + RotL64(aCarry, 23U)) + aNonceWordO);
            aWandererJ = aWandererJ ^ (((RotL64(aIngress, 19U) + RotL64(aOrbiterC, 43U)) + aOrbiterF) + aNonceWordN);
            aWandererF = aWandererF + ((((RotL64(aScatter, 57U) + aOrbiterF) + RotL64(aOrbiterI, 13U)) + RotL64(aCarry, 5U)) + aPhaseAWandererUpdateSaltF[((aIndex + 14U)) & S_SALT1]);
            aWandererK = aWandererK ^ (((RotL64(aCross, 28U) + RotL64(aOrbiterA, 5U)) + aOrbiterF) + aNonceWordH);
            //
            aCarry = aCarry + (RotL64(aWandererK, 5U) ^ aWandererJ);
            aCarry = aCarry + (aWandererI ^ RotL64(aWandererD, 43U));
            aCarry = aCarry + RotL64(aWandererF, 26U);
            aCarry = aCarry + RotL64(aIngress, 35U);
            aCarry = TwistMix64::DiffuseC(aCarry);
            //
            aInvestLaneB[S_BLOCK1 - aIndex] = aIngress;
        }
    
        // seed_loop_a loop 3
        // ingress from: aInvestLaneB, aExpandLaneD, aFireLaneD
        // ingress directions: aInvestLaneB forward forced, aExpandLaneD forward forced, aFireLaneD forward/backward random
        // cross from: aInvestLaneA, aExpandLaneB, aExpandLaneA
        // cross directions: aInvestLaneA backward forced, aExpandLaneB backward forced, aExpandLaneA backward/forward random
        // write to: aOperationLaneA
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aInvestLaneB[((aIndex + 12286U)) & S_BLOCK1], 13U) ^ RotL64(aExpandLaneD[((aIndex + 13346U)) & S_BLOCK1], 53U));
            aIngress ^= RotL64(aFireLaneD[((S_BLOCK1 - aIndex + 13426U)) & S_BLOCK1], 34U);
            aIngress = TwistMix64::DiffuseC(((aIngress ^ aPhaseADomainWordIngress) ^ aNonceWordF));
            //
            aCross = (RotL64(aInvestLaneA[((S_BLOCK1 - aIndex + 15002U)) & S_BLOCK1], 37U) ^ RotL64(aExpandLaneB[((S_BLOCK1 - aIndex + 12646U)) & S_BLOCK1], 11U));
            aCross ^= RotL64(aExpandLaneA[((S_BLOCK1 - aIndex + 11632U)) & S_BLOCK1], 23U);
            aCross = TwistMix64::DiffuseA(((aCross ^ aPhaseADomainWordCross) ^ aNonceWordA));
            //
            aScatter = (RotL64(aIngress, 3U) ^ RotL64(aCarry, 23U)) + (RotL64(aCross, 50U) + RotL64(aPrevious, 37U));
            aScatter = TwistMix64::DiffuseB(((aScatter ^ aPhaseADomainWordScatter) ^ aNonceWordP));
            //
            aOrbiterC = ((aWandererF + RotL64(aCross, 56U)) + RotL64(aCarry, 11U)) + 2225397913940961213U;
            aOrbiterE = (((aWandererG + RotL64(aScatter, 47U)) + RotL64(aCarry, 57U)) + 8342544893601343643U) + aNonceWordI;
            aOrbiterA = ((aWandererJ + RotL64(aIngress, 19U)) + 162922186381417187U) + aNonceWordD;
            aOrbiterH = ((((aWandererH + RotL64(aPrevious, 29U)) + RotL64(aCarry, 37U)) + 11660218373710972210U) + aPhaseAOrbiterAssignSaltD[((aIndex + 23U)) & S_SALT1]) + aNonceWordJ;
            aOrbiterJ = ((aWandererB + RotL64(aIngress, 3U)) + 14909034764605802354U) + aPhaseAOrbiterAssignSaltC[(((31U - aIndex) + 28U)) & S_SALT1];
            //
            aOrbiterC = (((aOrbiterC + aOrbiterE) + 16776955237009701511U) + aPhaseAOrbiterUpdateSaltD[((aIndex + 24U)) & S_SALT1]) + aNonceWordH;
            aOrbiterA = (aOrbiterA ^ aOrbiterC) ^ 5834487809188925253U;
            aOrbiterA = RotL64((aOrbiterA * 4458820879204327709U), 57U);
            //
            aOrbiterA = (aOrbiterA + aOrbiterH) + 1498492772767040320U;
            aOrbiterJ = (aOrbiterJ ^ aOrbiterA) ^ 4161765458781579617U;
            aOrbiterJ = RotL64((aOrbiterJ * 15535994410289065281U), 35U);
            //
            aOrbiterH = (aOrbiterH + aOrbiterJ) + 10511923076962447765U;
            aOrbiterC = ((aOrbiterC ^ aOrbiterH) ^ 8575954471692620021U) ^ aPhaseAOrbiterUpdateSaltA[(((31U - aIndex) + 16U)) & S_SALT1];
            aOrbiterC = RotL64((aOrbiterC * 12526744988828982731U), 13U);
            //
            aOrbiterJ = (((aOrbiterJ + aOrbiterC) + 6536325446331340573U) + aPhaseAOrbiterUpdateSaltC[(((31U - aIndex) + 13U)) & S_SALT1]) + aNonceWordL;
            aOrbiterE = (aOrbiterE ^ aOrbiterJ) ^ 1790628986900286346U;
            aOrbiterE = RotL64((aOrbiterE * 5262997114200816715U), 23U);
            //
            aOrbiterE = ((aOrbiterE + aOrbiterA) + 2623814807619278590U) + aPhaseAOrbiterUpdateSaltB[(((31U - aIndex) + 9U)) & S_SALT1];
            aOrbiterH = (aOrbiterH ^ aOrbiterE) ^ 11676970995834706612U;
            aOrbiterH = RotL64((aOrbiterH * 10057461115132434901U), 47U);
            //
            aIngress = RotL64(aOrbiterC, 53U) ^ aOrbiterE;
            aIngress = aIngress + (RotL64(aOrbiterJ, 13U) ^ aOrbiterH);
            aIngress = aIngress + RotL64(aOrbiterA, 43U);
            aIngress = TwistMix64::DiffuseC((aIngress + aScatter));
            //
            aWandererB = aWandererB + ((((RotL64(aScatter, 30U) + aOrbiterA) + RotL64(aOrbiterE, 37U)) + RotL64(aCarry, 3U)) + aNonceWordK);
            aWandererH = aWandererH ^ ((((RotL64(aCross, 53U) + aOrbiterH) + RotL64(aOrbiterA, 29U)) + aNonceWordO) + aPhaseAWandererUpdateSaltD[(((31U - aIndex) + 20U)) & S_SALT1]);
            aWandererF = aWandererF + ((((RotL64(aPrevious, 43U) + RotL64(aOrbiterJ, 6U)) + aOrbiterC) + RotL64(aCarry, 47U)) + aNonceWordE);
            aWandererG = aWandererG ^ ((RotL64(aIngress, 3U) + aOrbiterH) + RotL64(aOrbiterJ, 57U));
            aWandererJ = aWandererJ + ((((RotL64(aScatter, 19U) + RotL64(aOrbiterA, 47U)) + aOrbiterC) + aNonceWordN) + aPhaseAWandererUpdateSaltE[((aIndex + 3U)) & S_SALT1]);
            //
            aCarry = aCarry + (aWandererB ^ RotL64(aWandererF, 21U));
            aCarry = aCarry + (RotL64(aWandererG, 34U) ^ aWandererJ);
            aCarry = aCarry + RotL64(aWandererH, 43U);
            aCarry = aCarry + RotL64(aIngress, 13U);
            aCarry = TwistMix64::DiffuseC(aCarry);
            //
            aOperationLaneA[aIndex] = aIngress;
        }
    
        // seed_loop_a loop 4
        // ingress from: aOperationLaneA, aInvestLaneA, aFireLaneA
        // ingress directions: aOperationLaneA forward forced, aInvestLaneA forward forced, aFireLaneA forward/backward random
        // cross from: aInvestLaneB, aExpandLaneD, aExpandLaneC
        // cross directions: aInvestLaneB backward forced, aExpandLaneD backward forced, aExpandLaneC backward/forward random
        // write to: aOperationLaneB
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aOperationLaneA[((aIndex + 21629U)) & S_BLOCK1], 13U) ^ RotL64(aInvestLaneA[((aIndex + 16574U)) & S_BLOCK1], 21U));
            aIngress ^= RotL64(aFireLaneA[((S_BLOCK1 - aIndex + 17545U)) & S_BLOCK1], 5U);
            aIngress = TwistMix64::DiffuseA(((aIngress ^ aPhaseADomainWordIngress) ^ aNonceWordA));
            //
            aCross = (RotL64(aInvestLaneB[((S_BLOCK1 - aIndex + 17774U)) & S_BLOCK1], 41U) ^ RotL64(aExpandLaneD[((S_BLOCK1 - aIndex + 16410U)) & S_BLOCK1], 53U));
            aCross ^= RotL64(aExpandLaneC[((aIndex + 18018U)) & S_BLOCK1], 20U);
            aCross = TwistMix64::DiffuseB(((aCross ^ aPhaseADomainWordCross) ^ aNonceWordD));
            //
            aScatter = (RotL64(aPrevious, 43U) ^ RotL64(aCarry, 6U)) ^ (RotL64(aCross, 23U) + RotL64(aIngress, 57U));
            aScatter = TwistMix64::DiffuseA(((aScatter ^ aPhaseADomainWordScatter) ^ aNonceWordK));
            //
            aOrbiterH = (((aWandererG + RotL64(aCross, 47U)) + RotL64(aCarry, 29U)) + 13053031069776604052U) + aNonceWordP;
            aOrbiterA = ((aWandererD + RotL64(aIngress, 39U)) + 1331396630251085122U) + aNonceWordC;
            aOrbiterB = (((aWandererB + RotL64(aPrevious, 27U)) + RotL64(aCarry, 3U)) + 15879286043343942393U) + aNonceWordL;
            aOrbiterG = (((aWandererJ + RotL64(aScatter, 10U)) + RotL64(aCarry, 53U)) + 13590365633321406830U) + aPhaseAOrbiterAssignSaltF[(((31U - aIndex) + 10U)) & S_SALT1];
            aOrbiterK = ((aWandererE + RotL64(aPrevious, 19U)) + 14569235423040242618U) + aPhaseAOrbiterAssignSaltE[(((31U - aIndex) + 26U)) & S_SALT1];
            //
            aOrbiterH = ((aOrbiterH + aOrbiterA) + 11397370636618371560U) + aPhaseAOrbiterUpdateSaltC[((aIndex + 17U)) & S_SALT1];
            aOrbiterB = (aOrbiterB ^ aOrbiterH) ^ 3455933494593971847U;
            aOrbiterB = RotL64((aOrbiterB * 13051161161405358793U), 13U);
            //
            aOrbiterG = (aOrbiterG + aOrbiterH) + 1307153376443784593U;
            aOrbiterA = ((aOrbiterA ^ aOrbiterG) ^ 10688618762584786871U) ^ aNonceWordM;
            aOrbiterA = RotL64((aOrbiterA * 9503823896874842411U), 29U);
            //
            aOrbiterA = (aOrbiterA + aOrbiterB) + 17746248451153600096U;
            aOrbiterK = ((aOrbiterK ^ aOrbiterA) ^ 8512568600755410158U) ^ aNonceWordN;
            aOrbiterK = RotL64((aOrbiterK * 16648320170768234063U), 53U);
            //
            aOrbiterK = ((aOrbiterK + aOrbiterG) + 8950230550112591092U) + aPhaseAOrbiterUpdateSaltF[((aIndex + 20U)) & S_SALT1];
            aOrbiterH = (aOrbiterH ^ aOrbiterK) ^ 17790968369472845496U;
            aOrbiterH = RotL64((aOrbiterH * 5104988920132008913U), 3U);
            //
            aOrbiterB = ((aOrbiterB + aOrbiterK) + 12583323865381967534U) + aPhaseAOrbiterUpdateSaltB[(((31U - aIndex) + 16U)) & S_SALT1];
            aOrbiterG = ((aOrbiterG ^ aOrbiterB) ^ 11243927099685293887U) ^ aPhaseAOrbiterUpdateSaltD[(((31U - aIndex) + 27U)) & S_SALT1];
            aOrbiterG = RotL64((aOrbiterG * 12867003042486433971U), 39U);
            //
            aIngress = aOrbiterK ^ RotL64(aOrbiterA, 3U);
            aIngress = aIngress + (RotL64(aOrbiterG, 37U) ^ aOrbiterH);
            aIngress = aIngress + RotL64(aOrbiterB, 51U);
            aIngress = TwistMix64::DiffuseB((aIngress + aScatter));
            //
            aWandererJ = aWandererJ + ((((RotL64(aCross, 3U) + RotL64(aOrbiterA, 37U)) + aOrbiterH) + RotL64(aCarry, 23U)) + aPhaseAWandererUpdateSaltC[((aIndex + 9U)) & S_SALT1]);
            aWandererB = aWandererB ^ ((RotL64(aPrevious, 48U) + RotL64(aOrbiterH, 13U)) + aOrbiterK);
            aWandererG = aWandererG + (((RotL64(aIngress, 37U) + RotL64(aOrbiterG, 47U)) + aOrbiterK) + RotL64(aCarry, 3U));
            aWandererE = aWandererE ^ ((((RotL64(aScatter, 29U) + aOrbiterG) + RotL64(aOrbiterH, 21U)) + aNonceWordO) + aPhaseAWandererUpdateSaltB[((aIndex + 23U)) & S_SALT1]);
            aWandererD = aWandererD + (((RotL64(aPrevious, 21U) + aOrbiterB) + RotL64(aOrbiterA, 56U)) + aNonceWordK);
            //
            aCarry = aCarry + (aWandererG ^ RotL64(aWandererE, 5U));
            aCarry = aCarry + (RotL64(aWandererB, 19U) ^ aWandererJ);
            aCarry = aCarry + RotL64(aWandererD, 58U);
            aCarry = aCarry + RotL64(aIngress, 47U);
            aCarry = TwistMix64::DiffuseC(aCarry);
            //
            aOperationLaneB[S_BLOCK1 - aIndex] = aIngress;
        }
    
        // seed_loop_a loop 5
        // ingress from: aOperationLaneB, aOperationLaneA, aExpandLaneB
        // ingress directions: aOperationLaneB forward forced, aOperationLaneA forward forced, aExpandLaneB forward/backward random
        // cross from: aExpandLaneC, aInvestLaneA, aInvestLaneB
        // cross directions: aExpandLaneC backward forced, aInvestLaneA backward forced, aInvestLaneB backward/forward random
        // write to: aOperationLaneC
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aOperationLaneB[((aIndex + 24253U)) & S_BLOCK1], 10U) ^ RotL64(aOperationLaneA[((aIndex + 22216U)) & S_BLOCK1], 21U));
            aIngress ^= RotL64(aExpandLaneB[((S_BLOCK1 - aIndex + 23044U)) & S_BLOCK1], 35U);
            aIngress = TwistMix64::DiffuseC(((aIngress ^ aPhaseADomainWordIngress) ^ aNonceWordL));
            //
            aCross = (RotL64(aExpandLaneC[((S_BLOCK1 - aIndex + 25175U)) & S_BLOCK1], 12U) ^ RotL64(aInvestLaneA[((S_BLOCK1 - aIndex + 22970U)) & S_BLOCK1], 23U));
            aCross ^= RotL64(aInvestLaneB[((S_BLOCK1 - aIndex + 25235U)) & S_BLOCK1], 41U);
            aCross = TwistMix64::DiffuseC(((aCross ^ aPhaseADomainWordCross) ^ aNonceWordN));
            //
            aScatter = (RotL64(aCarry, 21U) ^ RotL64(aPrevious, 51U)) ^ (RotL64(aIngress, 34U) + RotL64(aCross, 5U));
            aScatter = TwistMix64::DiffuseC(((aScatter ^ aPhaseADomainWordScatter) ^ aNonceWordB));
            //
            aOrbiterA = (((aWandererF + RotL64(aScatter, 47U)) + RotL64(aCarry, 57U)) + 1042610313571524121U) + aNonceWordI;
            aOrbiterF = (((aWandererH + RotL64(aCross, 3U)) + 3505725321008825582U) + aPhaseAOrbiterAssignSaltA[(((31U - aIndex) + 16U)) & S_SALT1]) + aNonceWordM;
            aOrbiterK = (aWandererI + RotL64(aIngress, 23U)) + 12584654563843782991U;
            aOrbiterD = ((aWandererG + RotL64(aPrevious, 57U)) + RotL64(aCarry, 13U)) + 6645399144515770935U;
            aOrbiterI = ((((aWandererE + RotL64(aIngress, 38U)) + RotL64(aCarry, 39U)) + 3608978423753715584U) + aPhaseAOrbiterAssignSaltB[((aIndex + 5U)) & S_SALT1]) + aNonceWordJ;
            //
            aOrbiterA = ((aOrbiterA + aOrbiterF) + 8089198857670370983U) + aPhaseAOrbiterUpdateSaltC[(((31U - aIndex) + 9U)) & S_SALT1];
            aOrbiterK = (aOrbiterK ^ aOrbiterA) ^ 15207251813516399879U;
            aOrbiterK = RotL64((aOrbiterK * 7596841660069752069U), 11U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterA) + 9579268660105824516U;
            aOrbiterI = (aOrbiterI ^ aOrbiterD) ^ 16055044469473802812U;
            aOrbiterI = RotL64((aOrbiterI * 2269649280637188723U), 21U);
            //
            aOrbiterF = ((aOrbiterF + aOrbiterI) + 583811872609805949U) + aPhaseAOrbiterUpdateSaltA[((aIndex + 27U)) & S_SALT1];
            aOrbiterD = (((aOrbiterD ^ aOrbiterF) ^ 7027491967970873942U) ^ aPhaseAOrbiterUpdateSaltB[((aIndex + 25U)) & S_SALT1]) ^ aNonceWordE;
            aOrbiterD = RotL64((aOrbiterD * 12686754713465826139U), 47U);
            //
            aOrbiterI = (aOrbiterI + aOrbiterK) + 18256061823189677508U;
            aOrbiterA = (aOrbiterA ^ aOrbiterI) ^ 12708429127816136937U;
            aOrbiterA = RotL64((aOrbiterA * 12593886633108075321U), 37U);
            //
            aOrbiterK = (((aOrbiterK + aOrbiterD) + 12169216645156306078U) + aPhaseAOrbiterUpdateSaltE[(((31U - aIndex) + 19U)) & S_SALT1]) + aNonceWordD;
            aOrbiterF = (aOrbiterF ^ aOrbiterK) ^ 12694325407567795065U;
            aOrbiterF = RotL64((aOrbiterF * 3711789483877261899U), 29U);
            //
            aIngress = RotL64(aOrbiterF, 47U) ^ aOrbiterI;
            aIngress = aIngress + (aOrbiterA ^ RotL64(aOrbiterK, 57U));
            aIngress = aIngress + RotL64(aOrbiterD, 34U);
            aIngress = TwistMix64::DiffuseA((aIngress + aScatter));
            //
            aWandererG = aWandererG + ((((RotL64(aPrevious, 3U) + RotL64(aOrbiterD, 27U)) + aOrbiterK) + RotL64(aCarry, 23U)) + aNonceWordB);
            aWandererH = aWandererH ^ ((((RotL64(aScatter, 20U) + RotL64(aOrbiterI, 47U)) + aOrbiterF) + aNonceWordO) + aPhaseAWandererUpdateSaltF[((aIndex + 6U)) & S_SALT1]);
            aWandererI = aWandererI + (((RotL64(aCross, 29U) + RotL64(aOrbiterD, 11U)) + aOrbiterI) + RotL64(aCarry, 53U));
            aWandererF = aWandererF ^ (((RotL64(aIngress, 37U) + RotL64(aOrbiterF, 58U)) + aOrbiterA) + aNonceWordG);
            aWandererE = aWandererE + ((((RotL64(aPrevious, 11U) + aOrbiterA) + RotL64(aOrbiterD, 39U)) + aNonceWordP) + aPhaseAWandererUpdateSaltA[(((31U - aIndex) + 20U)) & S_SALT1]);
            //
            aCarry = aCarry + (aWandererF ^ RotL64(aWandererG, 13U));
            aCarry = aCarry + (aWandererE ^ RotL64(aWandererI, 3U));
            aCarry = aCarry + RotL64(aWandererH, 46U);
            aCarry = aCarry + RotL64(aIngress, 21U);
            aCarry = TwistMix64::DiffuseA(aCarry);
            //
            aOperationLaneC[aIndex] = aIngress;
        }
    
        // seed_loop_a loop 6
        // ingress from: aOperationLaneC, aExpandLaneA, aExpandLaneB
        // ingress directions: aOperationLaneC forward forced, aExpandLaneA forward forced, aExpandLaneB forward/backward random
        // cross from: aOperationLaneB, aOperationLaneA, aInvestLaneB
        // cross directions: aOperationLaneB backward forced, aOperationLaneA backward forced, aInvestLaneB backward/forward random
        // write to: aOperationLaneD
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aOperationLaneC[((aIndex + 32237U)) & S_BLOCK1], 60U) ^ RotL64(aExpandLaneA[((aIndex + 28449U)) & S_BLOCK1], 11U));
            aIngress ^= RotL64(aExpandLaneB[((S_BLOCK1 - aIndex + 32560U)) & S_BLOCK1], 29U);
            aIngress = TwistMix64::DiffuseC(((aIngress ^ aPhaseADomainWordIngress) ^ aNonceWordO));
            //
            aCross = (RotL64(aOperationLaneB[((S_BLOCK1 - aIndex + 30506U)) & S_BLOCK1], 3U) ^ RotL64(aOperationLaneA[((S_BLOCK1 - aIndex + 32046U)) & S_BLOCK1], 13U));
            aCross ^= RotL64(aInvestLaneB[((aIndex + 30398U)) & S_BLOCK1], 28U);
            aCross = TwistMix64::DiffuseC(((aCross ^ aPhaseADomainWordCross) ^ aNonceWordJ));
            //
            aScatter = (RotL64(aCarry, 20U) ^ RotL64(aPrevious, 53U)) + (RotL64(aIngress, 39U) + RotL64(aCross, 3U));
            aScatter = TwistMix64::DiffuseC(((aScatter ^ aPhaseADomainWordScatter) ^ aNonceWordP));
            //
            aOrbiterA = ((((aWandererI + RotL64(aPrevious, 43U)) + RotL64(aCarry, 39U)) + 11177787645248006236U) + aPhaseAOrbiterAssignSaltD[((aIndex + 23U)) & S_SALT1]) + aNonceWordH;
            aOrbiterC = ((aWandererC + RotL64(aScatter, 11U)) + RotL64(aCarry, 51U)) + 3808340254579817169U;
            aOrbiterD = (aWandererK + RotL64(aIngress, 51U)) + 828030667598518279U;
            aOrbiterI = ((((aWandererG + RotL64(aCross, 29U)) + RotL64(aCarry, 23U)) + 16177835921238398371U) + aPhaseAOrbiterAssignSaltC[((aIndex + 19U)) & S_SALT1]) + aNonceWordA;
            aOrbiterH = ((aWandererB + RotL64(aIngress, 20U)) + 5518747735458708741U) + aNonceWordN;
            //
            aOrbiterA = (((aOrbiterA + aOrbiterC) + 17346319082399995165U) + aPhaseAOrbiterUpdateSaltF[(((31U - aIndex) + 4U)) & S_SALT1]) + aNonceWordI;
            aOrbiterD = (aOrbiterD ^ aOrbiterA) ^ 6397156921893030937U;
            aOrbiterD = RotL64((aOrbiterD * 11203064569634132929U), 3U);
            //
            aOrbiterC = (aOrbiterC + aOrbiterD) + 15559381654710713582U;
            aOrbiterI = ((aOrbiterI ^ aOrbiterC) ^ 940404446491415088U) ^ aPhaseAOrbiterUpdateSaltE[(((31U - aIndex) + 21U)) & S_SALT1];
            aOrbiterI = RotL64((aOrbiterI * 16401260971303026881U), 21U);
            //
            aOrbiterD = (((aOrbiterD + aOrbiterI) + 8047166032048732645U) + aPhaseAOrbiterUpdateSaltC[((aIndex + 24U)) & S_SALT1]) + aNonceWordC;
            aOrbiterH = ((aOrbiterH ^ aOrbiterD) ^ 4688468645859470491U) ^ aPhaseAOrbiterUpdateSaltA[((aIndex + 17U)) & S_SALT1];
            aOrbiterH = RotL64((aOrbiterH * 14383536431614496369U), 29U);
            //
            aOrbiterI = (aOrbiterI + aOrbiterH) + 3710878044770337260U;
            aOrbiterA = ((aOrbiterA ^ aOrbiterI) ^ 116343189456629220U) ^ aNonceWordB;
            aOrbiterA = RotL64((aOrbiterA * 5637725064169289339U), 11U);
            //
            aOrbiterH = (aOrbiterH + aOrbiterA) + 883908030159391659U;
            aOrbiterC = (aOrbiterC ^ aOrbiterH) ^ 18058691521694880482U;
            aOrbiterC = RotL64((aOrbiterC * 3132200449123497619U), 43U);
            //
            aIngress = aOrbiterA ^ RotL64(aOrbiterH, 53U);
            aIngress = aIngress + (RotL64(aOrbiterI, 42U) ^ aOrbiterD);
            aIngress = aIngress + RotL64(aOrbiterC, 29U);
            aIngress = TwistMix64::DiffuseA((aIngress + aScatter));
            //
            aWandererK = aWandererK + ((((RotL64(aPrevious, 27U) + aOrbiterC) + RotL64(aOrbiterA, 22U)) + RotL64(aCarry, 37U)) + aNonceWordK);
            aWandererB = aWandererB ^ ((RotL64(aScatter, 40U) + aOrbiterI) + RotL64(aOrbiterC, 35U));
            aWandererG = aWandererG + ((RotL64(aCross, 11U) + RotL64(aOrbiterD, 43U)) + aOrbiterA);
            aWandererC = aWandererC ^ ((((RotL64(aIngress, 51U) + RotL64(aOrbiterA, 57U)) + aOrbiterI) + aNonceWordF) + aPhaseAWandererUpdateSaltE[((aIndex + 13U)) & S_SALT1]);
            aWandererI = aWandererI + ((((RotL64(aScatter, 3U) + aOrbiterC) + RotL64(aOrbiterH, 5U)) + RotL64(aCarry, 5U)) + aPhaseAWandererUpdateSaltD[((aIndex + 18U)) & S_SALT1]);
            //
            aCarry = aCarry + (RotL64(aWandererB, 27U) ^ aWandererK);
            aCarry = aCarry + (aWandererC ^ RotL64(aWandererI, 35U));
            aCarry = aCarry + RotL64(aWandererG, 19U);
            aCarry = aCarry + RotL64(aIngress, 3U);
            aCarry = TwistMix64::DiffuseA(aCarry);
            //
            aOperationLaneD[S_BLOCK1 - aIndex] = aIngress;
        }
    }
    // GSeedRunSeed_B seed_loop_a (end)
    *pPrevious = aPrevious;
    *pIngress = aIngress;
    *pCarry = aCarry;
    *pWandererA = aWandererA;
    *pWandererB = aWandererB;
    *pWandererC = aWandererC;
    *pWandererD = aWandererD;
    *pWandererE = aWandererE;
    *pWandererF = aWandererF;
    *pWandererG = aWandererG;
    *pWandererH = aWandererH;
    *pWandererI = aWandererI;
    *pWandererJ = aWandererJ;
    *pWandererK = aWandererK;
}

void TwistExpander_Exercea_Arx::Seed_C(TwistWorkSpace *pWorkSpace,
                     std::uint64_t pNonce,
                     std::uint64_t *pPrevious,
                     std::uint64_t *pIngress,
                     std::uint64_t *pCarry,
                     std::uint64_t *pWandererA,
                     std::uint64_t *pWandererB,
                     std::uint64_t *pWandererC,
                     std::uint64_t *pWandererD,
                     std::uint64_t *pWandererE,
                     std::uint64_t *pWandererF,
                     std::uint64_t *pWandererG,
                     std::uint64_t *pWandererH,
                     std::uint64_t *pWandererI,
                     std::uint64_t *pWandererJ,
                     std::uint64_t *pWandererK) {
    [[maybe_unused]] std::uint8_t *aExpandLaneA = pWorkSpace->mExpansionLaneA;
    [[maybe_unused]] std::uint8_t *aExpandLaneB = pWorkSpace->mExpansionLaneB;
    [[maybe_unused]] std::uint8_t *aExpandLaneC = pWorkSpace->mExpansionLaneC;
    [[maybe_unused]] std::uint8_t *aExpandLaneD = pWorkSpace->mExpansionLaneD;
    [[maybe_unused]] std::uint8_t *aWorkLaneA = pWorkSpace->mWorkLaneA;
    [[maybe_unused]] std::uint8_t *aWorkLaneB = pWorkSpace->mWorkLaneB;
    [[maybe_unused]] std::uint8_t *aWorkLaneC = pWorkSpace->mWorkLaneC;
    [[maybe_unused]] std::uint8_t *aWorkLaneD = pWorkSpace->mWorkLaneD;
    [[maybe_unused]] std::uint8_t *aOperationLaneA = pWorkSpace->mOperationLaneA;
    [[maybe_unused]] std::uint8_t *aOperationLaneB = pWorkSpace->mOperationLaneB;
    [[maybe_unused]] std::uint8_t *aOperationLaneC = pWorkSpace->mOperationLaneC;
    [[maybe_unused]] std::uint8_t *aOperationLaneD = pWorkSpace->mOperationLaneD;
    [[maybe_unused]] std::uint8_t *aFireLaneA = pWorkSpace->mFireLaneA;
    [[maybe_unused]] std::uint8_t *aFireLaneB = pWorkSpace->mFireLaneB;
    [[maybe_unused]] std::uint8_t *aFireLaneC = pWorkSpace->mFireLaneC;
    [[maybe_unused]] std::uint8_t *aFireLaneD = pWorkSpace->mFireLaneD;
    [[maybe_unused]] std::uint8_t *aInvestLaneC = pWorkSpace->mInvestLaneC;
    [[maybe_unused]] std::uint8_t *aInvestLaneD = pWorkSpace->mInvestLaneD;
    [[maybe_unused]] std::uint64_t *aPhaseBOrbiterAssignSaltA = pWorkSpace->mDomainBundle.mPhaseBSalts.mOrbiterAssign.mSaltA;
    [[maybe_unused]] std::uint64_t *aPhaseBOrbiterAssignSaltB = pWorkSpace->mDomainBundle.mPhaseBSalts.mOrbiterAssign.mSaltB;
    [[maybe_unused]] std::uint64_t *aPhaseBOrbiterAssignSaltC = pWorkSpace->mDomainBundle.mPhaseBSalts.mOrbiterAssign.mSaltC;
    [[maybe_unused]] std::uint64_t *aPhaseBOrbiterAssignSaltD = pWorkSpace->mDomainBundle.mPhaseBSalts.mOrbiterAssign.mSaltD;
    [[maybe_unused]] std::uint64_t *aPhaseBOrbiterAssignSaltE = pWorkSpace->mDomainBundle.mPhaseBSalts.mOrbiterAssign.mSaltE;
    [[maybe_unused]] std::uint64_t *aPhaseBOrbiterAssignSaltF = pWorkSpace->mDomainBundle.mPhaseBSalts.mOrbiterAssign.mSaltF;
    [[maybe_unused]] std::uint64_t *aPhaseBOrbiterUpdateSaltA = pWorkSpace->mDomainBundle.mPhaseBSalts.mOrbiterUpdate.mSaltA;
    [[maybe_unused]] std::uint64_t *aPhaseBOrbiterUpdateSaltB = pWorkSpace->mDomainBundle.mPhaseBSalts.mOrbiterUpdate.mSaltB;
    [[maybe_unused]] std::uint64_t *aPhaseBOrbiterUpdateSaltC = pWorkSpace->mDomainBundle.mPhaseBSalts.mOrbiterUpdate.mSaltC;
    [[maybe_unused]] std::uint64_t *aPhaseBOrbiterUpdateSaltD = pWorkSpace->mDomainBundle.mPhaseBSalts.mOrbiterUpdate.mSaltD;
    [[maybe_unused]] std::uint64_t *aPhaseBOrbiterUpdateSaltE = pWorkSpace->mDomainBundle.mPhaseBSalts.mOrbiterUpdate.mSaltE;
    [[maybe_unused]] std::uint64_t *aPhaseBOrbiterUpdateSaltF = pWorkSpace->mDomainBundle.mPhaseBSalts.mOrbiterUpdate.mSaltF;
    [[maybe_unused]] std::uint64_t *aPhaseBWandererUpdateSaltA = pWorkSpace->mDomainBundle.mPhaseBSalts.mWandererUpdate.mSaltA;
    [[maybe_unused]] std::uint64_t *aPhaseBWandererUpdateSaltB = pWorkSpace->mDomainBundle.mPhaseBSalts.mWandererUpdate.mSaltB;
    [[maybe_unused]] std::uint64_t *aPhaseBWandererUpdateSaltC = pWorkSpace->mDomainBundle.mPhaseBSalts.mWandererUpdate.mSaltC;
    [[maybe_unused]] std::uint64_t *aPhaseBWandererUpdateSaltD = pWorkSpace->mDomainBundle.mPhaseBSalts.mWandererUpdate.mSaltD;
    [[maybe_unused]] std::uint64_t *aPhaseBWandererUpdateSaltE = pWorkSpace->mDomainBundle.mPhaseBSalts.mWandererUpdate.mSaltE;
    [[maybe_unused]] std::uint64_t *aPhaseBWandererUpdateSaltF = pWorkSpace->mDomainBundle.mPhaseBSalts.mWandererUpdate.mSaltF;
    const std::uint64_t &aPhaseBDomainWordIngress = pWorkSpace->mDomainBundle.mPhaseBConstants.mIngress;
    const std::uint64_t &aPhaseBDomainWordScatter = pWorkSpace->mDomainBundle.mPhaseBConstants.mScatter;
    const std::uint64_t &aPhaseBDomainWordCross = pWorkSpace->mDomainBundle.mPhaseBConstants.mCross;
    std::uint64_t aCross = 0; std::uint64_t aScatter = 0;

    std::uint64_t aOrbiterA = 0; std::uint64_t aOrbiterB = 0; std::uint64_t aOrbiterC = 0; std::uint64_t aOrbiterD = 0;
    std::uint64_t aOrbiterE = 0; std::uint64_t aOrbiterF = 0; std::uint64_t aOrbiterG = 0; std::uint64_t aOrbiterH = 0;
    std::uint64_t aOrbiterI = 0; std::uint64_t aOrbiterJ = 0; std::uint64_t aOrbiterK = 0;

    // [seed arx]
    [[maybe_unused]] std::uint8_t *mSource = pWorkSpace->mSource;
    std::uint64_t aPrevious = *pPrevious;
    std::uint64_t aIngress = *pIngress;
    std::uint64_t aCarry = *pCarry;
    std::uint64_t aWandererA = *pWandererA;
    std::uint64_t aWandererB = *pWandererB;
    std::uint64_t aWandererC = *pWandererC;
    std::uint64_t aWandererD = *pWandererD;
    std::uint64_t aWandererE = *pWandererE;
    std::uint64_t aWandererF = *pWandererF;
    std::uint64_t aWandererG = *pWandererG;
    std::uint64_t aWandererH = *pWandererH;
    std::uint64_t aWandererI = *pWandererI;
    std::uint64_t aWandererJ = *pWandererJ;
    std::uint64_t aWandererK = *pWandererK;
    std::uint64_t aNonceWordA = TwistMix64::DiffuseA(pNonce * 0xBA5B507422DD43D5ULL + 0xA677DA123A0A85E4ULL);
    std::uint64_t aNonceWordB = TwistMix64::DiffuseB(pNonce * 0xA6FD4ACC3B0C3AB7ULL + 0xD90A57635ECA12DCULL);
    std::uint64_t aNonceWordC = TwistMix64::DiffuseB(pNonce * 0xFD48643EC925B253ULL + 0xDBAD1B766178FC58ULL);
    std::uint64_t aNonceWordD = TwistMix64::DiffuseC(pNonce * 0xD50A61D8CA6C493FULL + 0xAD61CCAFF884C7BAULL);
    std::uint64_t aNonceWordE = TwistMix64::DiffuseB(pNonce * 0x839335A5B22A2993ULL + 0x9282A3F88A308976ULL);
    std::uint64_t aNonceWordF = TwistMix64::DiffuseA(pNonce * 0xBA6F99956CB9D049ULL + 0xE14F7C6D64C910C5ULL);
    std::uint64_t aNonceWordG = TwistMix64::DiffuseA(pNonce * 0x81578BD601E66581ULL + 0xE02808B6AF466AB3ULL);
    std::uint64_t aNonceWordH = TwistMix64::DiffuseA(pNonce * 0xCA536F61E4F0E059ULL + 0xEC5D17D424139BF7ULL);
    std::uint64_t aNonceWordI = TwistMix64::DiffuseC(pNonce * 0x990D9D1AA7E114FFULL + 0xF9730DCEFBAD3E89ULL);
    std::uint64_t aNonceWordJ = TwistMix64::DiffuseC(pNonce * 0xE5994514024F7C17ULL + 0xBC7F48D1B4D73E7EULL);
    std::uint64_t aNonceWordK = TwistMix64::DiffuseC(pNonce * 0xDBCE8A4936D81293ULL + 0x951C8BE18372FB94ULL);
    std::uint64_t aNonceWordL = TwistMix64::DiffuseC(pNonce * 0xC3278E97E5B95F15ULL + 0x853A9683E1C10214ULL);
    std::uint64_t aNonceWordM = TwistMix64::DiffuseB(pNonce * 0xFEF309CE133783F5ULL + 0xF04841ABE55031D5ULL);
    std::uint64_t aNonceWordN = TwistMix64::DiffuseB(pNonce * 0xA9EDA2A01D4C2A7FULL + 0xE34CF7B1FD83FB5DULL);
    std::uint64_t aNonceWordO = TwistMix64::DiffuseC(pNonce * 0xE6BEE99A9FC8467FULL + 0xA18761B0C297712CULL);
    std::uint64_t aNonceWordP = TwistMix64::DiffuseC(pNonce * 0xFF0037DEE61BF4F1ULL + 0x83A9110E50CB921BULL);
    // GSeedRunSeed_C seed_loop_b (start)
    {
        // GSeedRunSeed_C seed_loop_b lane group
        // read from: aOperationLaneA, aOperationLaneB, aExpandLaneD, aOperationLaneC, aOperationLaneD, aExpandLaneA, aInvestLaneC, aFireLaneA, aFireLaneC, aInvestLaneD, aExpandLaneB, aWorkLaneA, aFireLaneB, aWorkLaneB, aFireLaneD, aWorkLaneC, aExpandLaneC
        // write to: aInvestLaneC, aInvestLaneD, aWorkLaneA, aWorkLaneB, aWorkLaneC, aWorkLaneD
    
        // seed_loop_b loop 1
        // ingress from: aOperationLaneA, aOperationLaneB, aExpandLaneD
        // ingress directions: aOperationLaneA forward forced, aOperationLaneB forward forced, aExpandLaneD forward/backward random
        // cross from: aOperationLaneC, aOperationLaneD, aExpandLaneA
        // cross directions: aOperationLaneC backward forced, aOperationLaneD backward forced, aExpandLaneA backward/forward random
        // write to: aInvestLaneC
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aOperationLaneA[((aIndex + 2872U)) & S_BLOCK1], 21U) ^ RotL64(aOperationLaneB[((aIndex + 258U)) & S_BLOCK1], 12U));
            aIngress ^= RotL64(aExpandLaneD[((aIndex + 1183U)) & S_BLOCK1], 35U);
            aIngress = TwistMix64::DiffuseB(((aIngress ^ aPhaseBDomainWordIngress) ^ aNonceWordB));
            //
            aCross = (RotL64(aOperationLaneC[((S_BLOCK1 - aIndex + 2937U)) & S_BLOCK1], 27U) ^ RotL64(aOperationLaneD[((S_BLOCK1 - aIndex + 2546U)) & S_BLOCK1], 56U));
            aCross ^= RotL64(aExpandLaneA[((S_BLOCK1 - aIndex + 4207U)) & S_BLOCK1], 13U);
            aCross = TwistMix64::DiffuseA(((aCross ^ aPhaseBDomainWordCross) ^ aNonceWordI));
            //
            aScatter = (RotL64(aCross, 26U) ^ RotL64(aIngress, 53U)) + (RotL64(aCarry, 3U) + RotL64(aPrevious, 39U));
            aScatter = TwistMix64::DiffuseC(((aScatter ^ aPhaseBDomainWordScatter) ^ aNonceWordH));
            //
            aOrbiterK = ((aWandererE + RotL64(aPrevious, 18U)) + RotL64(aCarry, 13U)) + 2672739400294801233U;
            aOrbiterG = ((aWandererJ + RotL64(aIngress, 43U)) + RotL64(aCarry, 21U)) + 8475624545015101850U;
            aOrbiterD = (aWandererF + RotL64(aCross, 13U)) + 1252755112289831257U;
            aOrbiterF = ((aWandererA + RotL64(aScatter, 39U)) + 7938039507649183387U) + aNonceWordH;
            aOrbiterA = (aWandererC + RotL64(aIngress, 51U)) + 8167413146948861022U;
            aOrbiterB = (((aWandererG + RotL64(aScatter, 5U)) + RotL64(aCarry, 35U)) + 17712313989694374353U) + aPhaseBOrbiterAssignSaltD[(((31U - aIndex) + 19U)) & S_SALT1];
            aOrbiterC = ((aWandererD + RotL64(aCross, 23U)) + 7637042279892596975U) + aPhaseBOrbiterAssignSaltA[((aIndex + 24U)) & S_SALT1];
            aOrbiterH = ((aWandererK + RotL64(aPrevious, 47U)) + 15770412950033467341U) + aNonceWordE;
            aOrbiterE = ((aWandererI + RotL64(aCross, 58U)) + 3951812021898608685U) + aNonceWordC;
            //
            aOrbiterK = (aOrbiterK + aOrbiterG) + 8656983621098246507U;
            aOrbiterD = (aOrbiterD ^ aOrbiterK) ^ 17943342344730687317U;
            aOrbiterD = RotL64((aOrbiterD * 16495519451034883813U), 23U);
            //
            aOrbiterG = (aOrbiterG + aOrbiterF) + 3087677463651608668U;
            aOrbiterA = (((aOrbiterA ^ aOrbiterG) ^ 16493240011924342788U) ^ aPhaseBOrbiterUpdateSaltD[(((31U - aIndex) + 11U)) & S_SALT1]) ^ aNonceWordO;
            aOrbiterA = RotL64((aOrbiterA * 16898479041530771871U), 43U);
            //
            aOrbiterB = (aOrbiterB + aOrbiterD) + 7750923317452683057U;
            aOrbiterC = (aOrbiterC ^ aOrbiterB) ^ 2185924841611106546U;
            aOrbiterC = RotL64((aOrbiterC * 708072658250726381U), 47U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterA) + 14676868738946722416U;
            aOrbiterH = ((aOrbiterH ^ aOrbiterD) ^ 6849098251696302393U) ^ aPhaseBOrbiterUpdateSaltC[(((31U - aIndex) + 29U)) & S_SALT1];
            aOrbiterH = RotL64((aOrbiterH * 2599806275837778069U), 53U);
            //
            aOrbiterF = (aOrbiterF + aOrbiterK) + 17817755047153606419U;
            aOrbiterB = ((aOrbiterB ^ aOrbiterF) ^ 9900465270314068757U) ^ aPhaseBOrbiterUpdateSaltF[(((31U - aIndex) + 23U)) & S_SALT1];
            aOrbiterB = RotL64((aOrbiterB * 9267925873983176685U), 57U);
            //
            aOrbiterA = (aOrbiterA + aOrbiterB) + 11380000891112113701U;
            aOrbiterE = ((aOrbiterE ^ aOrbiterA) ^ 15930503831156546113U) ^ aNonceWordK;
            aOrbiterE = RotL64((aOrbiterE * 14450535035065393845U), 5U);
            //
            aOrbiterE = (aOrbiterE + aOrbiterC) + 5439183530402949780U;
            aOrbiterK = (aOrbiterK ^ aOrbiterE) ^ 3731802052051181843U;
            aOrbiterK = RotL64((aOrbiterK * 7739775058947333169U), 13U);
            //
            aOrbiterC = (aOrbiterC + aOrbiterH) + 14432344583247783600U;
            aOrbiterG = (aOrbiterG ^ aOrbiterC) ^ 16192098795467501636U;
            aOrbiterG = RotL64((aOrbiterG * 6285466374319549047U), 27U);
            //
            aOrbiterH = ((aOrbiterH + aOrbiterE) + 1523272672673940290U) + aNonceWordN;
            aOrbiterF = ((aOrbiterF ^ aOrbiterH) ^ 7462092373525113574U) ^ aPhaseBOrbiterUpdateSaltE[((aIndex + 26U)) & S_SALT1];
            aOrbiterF = RotL64((aOrbiterF * 15067751170235540679U), 39U);
            //
            aIngress = RotL64(aOrbiterH, 27U) ^ aOrbiterA;
            aIngress = aIngress + (aOrbiterK ^ RotL64(aOrbiterE, 57U));
            aIngress = aIngress + (RotL64(aOrbiterG, 23U) ^ aOrbiterF);
            aIngress = aIngress + (RotL64(aOrbiterC, 43U) ^ aOrbiterD);
            aIngress = aIngress + RotL64(aOrbiterB, 36U);
            aIngress = TwistMix64::DiffuseA((aIngress + aScatter));
            //
            aWandererE = aWandererE + (((RotL64(aPrevious, 48U) + RotL64(aOrbiterA, 35U)) + aOrbiterB) + aNonceWordD);
            aWandererG = aWandererG ^ ((RotL64(aCross, 3U) + aOrbiterH) + RotL64(aOrbiterE, 57U));
            aWandererK = aWandererK + (((RotL64(aScatter, 41U) + aOrbiterG) + RotL64(aOrbiterF, 18U)) + aPhaseBWandererUpdateSaltF[(((31U - aIndex) + 15U)) & S_SALT1]);
            aWandererA = aWandererA ^ ((RotL64(aIngress, 35U) + aOrbiterK) + RotL64(aOrbiterF, 51U));
            aWandererF = aWandererF + ((RotL64(aPrevious, 29U) + RotL64(aOrbiterF, 27U)) + aOrbiterD);
            aWandererI = aWandererI ^ (((RotL64(aScatter, 53U) + RotL64(aOrbiterK, 47U)) + aOrbiterC) + aPhaseBWandererUpdateSaltB[(((31U - aIndex) + 7U)) & S_SALT1]);
            aWandererJ = aWandererJ + (((RotL64(aCross, 14U) + aOrbiterH) + RotL64(aOrbiterB, 14U)) + RotL64(aCarry, 57U));
            aWandererC = aWandererC ^ (((RotL64(aIngress, 23U) + aOrbiterB) + RotL64(aOrbiterC, 39U)) + aNonceWordG);
            aWandererD = aWandererD + ((((RotL64(aScatter, 57U) + RotL64(aOrbiterD, 5U)) + aOrbiterB) + RotL64(aCarry, 37U)) + aNonceWordF);
            //
            aCarry = aCarry + (RotL64(aWandererI, 30U) ^ aWandererD);
            aCarry = aCarry + (RotL64(aWandererK, 13U) ^ aWandererE);
            aCarry = aCarry + (RotL64(aWandererJ, 27U) ^ aWandererF);
            aCarry = aCarry + (aWandererC ^ RotL64(aWandererA, 53U));
            aCarry = aCarry + RotL64(aWandererG, 35U);
            aCarry = aCarry + RotL64(aIngress, 10U);
            aCarry = TwistMix64::DiffuseC(aCarry);
            //
            aInvestLaneC[aIndex] = aIngress;
        }
    
        // seed_loop_b loop 2
        // ingress from: aInvestLaneC, aOperationLaneC, aOperationLaneD, aFireLaneA
        // ingress directions: aInvestLaneC forward forced, aOperationLaneC forward forced, aOperationLaneD forward forced, aFireLaneA forward/backward random
        // cross from: aOperationLaneA, aOperationLaneB, aFireLaneC
        // cross directions: aOperationLaneA backward forced, aOperationLaneB backward forced, aFireLaneC backward/forward random
        // write to: aInvestLaneD
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aInvestLaneC[((aIndex + 5854U)) & S_BLOCK1], 3U) ^ RotL64(aOperationLaneC[((aIndex + 5911U)) & S_BLOCK1], 35U));
            aIngress ^= (RotL64(aOperationLaneD[((aIndex + 10076U)) & S_BLOCK1], 23U) ^ RotL64(aFireLaneA[((aIndex + 7504U)) & S_BLOCK1], 48U));
            aIngress = TwistMix64::DiffuseC(((aIngress ^ aPhaseBDomainWordIngress) ^ aNonceWordG));
            //
            aCross = (RotL64(aOperationLaneA[((S_BLOCK1 - aIndex + 9727U)) & S_BLOCK1], 42U) ^ RotL64(aOperationLaneB[((S_BLOCK1 - aIndex + 7032U)) & S_BLOCK1], 13U));
            aCross ^= RotL64(aFireLaneC[((S_BLOCK1 - aIndex + 8369U)) & S_BLOCK1], 57U);
            aCross = TwistMix64::DiffuseC(((aCross ^ aPhaseBDomainWordCross) ^ aNonceWordN));
            //
            aScatter = (RotL64(aCarry, 29U) ^ RotL64(aPrevious, 13U)) + (RotL64(aCross, 58U) ^ RotL64(aIngress, 43U));
            aScatter = TwistMix64::DiffuseB(((aScatter ^ aPhaseBDomainWordScatter) ^ aNonceWordB));
            //
            aOrbiterB = (aWandererJ + RotL64(aIngress, 13U)) + 16651241552253078315U;
            aOrbiterE = (aWandererD + RotL64(aScatter, 27U)) + 4558144676982478003U;
            aOrbiterG = ((aWandererF + RotL64(aPrevious, 42U)) + 8814884320080367550U) + aNonceWordK;
            aOrbiterA = ((aWandererG + RotL64(aCross, 19U)) + 16011579668555672117U) + aPhaseBOrbiterAssignSaltB[(((31U - aIndex) + 22U)) & S_SALT1];
            aOrbiterJ = (((aWandererA + RotL64(aIngress, 35U)) + RotL64(aCarry, 35U)) + 4738918668759862438U) + aNonceWordM;
            aOrbiterK = ((aWandererE + RotL64(aPrevious, 51U)) + 12526083125540985108U) + aNonceWordB;
            aOrbiterD = ((aWandererH + RotL64(aScatter, 58U)) + RotL64(aCarry, 57U)) + 8048723561746000552U;
            aOrbiterH = (((aWandererK + RotL64(aCross, 3U)) + RotL64(aCarry, 27U)) + 1082218464034639039U) + aPhaseBOrbiterAssignSaltC[((aIndex + 11U)) & S_SALT1];
            aOrbiterI = ((aWandererC + RotL64(aScatter, 23U)) + 8432043246965946816U) + aNonceWordD;
            //
            aOrbiterB = (aOrbiterB + aOrbiterE) + 9982080524048636852U;
            aOrbiterG = (((aOrbiterG ^ aOrbiterB) ^ 6720069955755215919U) ^ aPhaseBOrbiterUpdateSaltA[(((31U - aIndex) + 5U)) & S_SALT1]) ^ aNonceWordI;
            aOrbiterG = RotL64((aOrbiterG * 1025046364205332059U), 11U);
            //
            aOrbiterA = (aOrbiterA + aOrbiterJ) + 1019035028070247757U;
            aOrbiterB = ((aOrbiterB ^ aOrbiterA) ^ 7360619079463870467U) ^ aNonceWordA;
            aOrbiterB = RotL64((aOrbiterB * 6623074813047915863U), 37U);
            //
            aOrbiterE = ((aOrbiterE + aOrbiterK) + 10893918488381348474U) + aNonceWordF;
            aOrbiterD = (aOrbiterD ^ aOrbiterE) ^ 1390297670907738019U;
            aOrbiterD = RotL64((aOrbiterD * 11909657437658597735U), 5U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterH) + 12512200589031203480U;
            aOrbiterI = (aOrbiterI ^ aOrbiterD) ^ 14741471280748399540U;
            aOrbiterI = RotL64((aOrbiterI * 3012135242889901095U), 57U);
            //
            aOrbiterI = ((aOrbiterI + aOrbiterA) + 8543897248359826770U) + aPhaseBOrbiterUpdateSaltF[((aIndex + 17U)) & S_SALT1];
            aOrbiterK = ((aOrbiterK ^ aOrbiterI) ^ 8545972622733791272U) ^ aPhaseBOrbiterUpdateSaltB[(((31U - aIndex) + 20U)) & S_SALT1];
            aOrbiterK = RotL64((aOrbiterK * 11793879362775346821U), 21U);
            //
            aOrbiterH = ((aOrbiterH + aOrbiterG) + 7049384618581928664U) + aNonceWordH;
            aOrbiterA = (aOrbiterA ^ aOrbiterH) ^ 14730773807906925408U;
            aOrbiterA = RotL64((aOrbiterA * 10711566871536755073U), 47U);
            //
            aOrbiterG = ((aOrbiterG + aOrbiterD) + 11480717275652449986U) + aPhaseBOrbiterUpdateSaltE[((aIndex + 15U)) & S_SALT1];
            aOrbiterJ = (aOrbiterJ ^ aOrbiterG) ^ 1135397594974536859U;
            aOrbiterJ = RotL64((aOrbiterJ * 6347492892938856497U), 53U);
            //
            aOrbiterJ = (aOrbiterJ + aOrbiterI) + 6897207625849516702U;
            aOrbiterE = (aOrbiterE ^ aOrbiterJ) ^ 10920630712550287148U;
            aOrbiterE = RotL64((aOrbiterE * 4140705091806993359U), 43U);
            //
            aOrbiterK = (aOrbiterK + aOrbiterB) + 1094056478999931332U;
            aOrbiterH = (aOrbiterH ^ aOrbiterK) ^ 6784487144549717207U;
            aOrbiterH = RotL64((aOrbiterH * 6295177724167067891U), 29U);
            //
            aIngress = RotL64(aOrbiterJ, 3U) ^ aOrbiterH;
            aIngress = aIngress + (aOrbiterA ^ RotL64(aOrbiterG, 60U));
            aIngress = aIngress + (aOrbiterI ^ RotL64(aOrbiterE, 19U));
            aIngress = aIngress + (RotL64(aOrbiterD, 13U) ^ aOrbiterB);
            aIngress = aIngress + RotL64(aOrbiterK, 57U);
            aIngress = TwistMix64::DiffuseC((aIngress + aScatter));
            //
            aWandererD = aWandererD ^ (((RotL64(aIngress, 6U) + RotL64(aOrbiterB, 5U)) + aOrbiterK) + aNonceWordP);
            aWandererG = aWandererG + (((RotL64(aPrevious, 29U) + aOrbiterI) + RotL64(aOrbiterG, 23U)) + RotL64(aCarry, 27U));
            aWandererJ = aWandererJ ^ ((RotL64(aCross, 57U) + RotL64(aOrbiterI, 57U)) + aOrbiterD);
            aWandererF = aWandererF + (((RotL64(aScatter, 11U) + RotL64(aOrbiterG, 29U)) + aOrbiterJ) + aNonceWordE);
            aWandererK = aWandererK ^ ((RotL64(aIngress, 47U) + RotL64(aOrbiterG, 18U)) + aOrbiterK);
            aWandererC = aWandererC + (((((RotL64(aCross, 38U) + aOrbiterI) + RotL64(aOrbiterA, 11U)) + RotL64(aCarry, 47U)) + aNonceWordC) + aPhaseBWandererUpdateSaltE[(((31U - aIndex) + 7U)) & S_SALT1]);
            aWandererA = aWandererA ^ (((RotL64(aPrevious, 23U) + aOrbiterH) + RotL64(aOrbiterK, 39U)) + aPhaseBWandererUpdateSaltA[(((31U - aIndex) + 4U)) & S_SALT1]);
            aWandererH = aWandererH + ((RotL64(aScatter, 43U) + RotL64(aOrbiterE, 51U)) + aOrbiterH);
            aWandererE = aWandererE ^ ((RotL64(aPrevious, 51U) + RotL64(aOrbiterJ, 46U)) + aOrbiterK);
            //
            aCarry = aCarry + (aWandererG ^ RotL64(aWandererF, 11U));
            aCarry = aCarry + (aWandererK ^ RotL64(aWandererE, 19U));
            aCarry = aCarry + (aWandererC ^ RotL64(aWandererH, 23U));
            aCarry = aCarry + (RotL64(aWandererA, 3U) ^ aWandererD);
            aCarry = aCarry + RotL64(aWandererJ, 6U);
            aCarry = aCarry + RotL64(aIngress, 27U);
            aCarry = TwistMix64::DiffuseB(aCarry);
            //
            aInvestLaneD[S_BLOCK1 - aIndex] = aIngress;
        }
    
        // seed_loop_b loop 3
        // ingress from: aInvestLaneD, aOperationLaneA, aExpandLaneB
        // ingress directions: aInvestLaneD forward forced, aOperationLaneA forward forced, aExpandLaneB forward/backward random
        // cross from: aInvestLaneC, aOperationLaneC
        // cross directions: aInvestLaneC backward forced, aOperationLaneC backward/forward random
        // write to: aWorkLaneA
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aInvestLaneD[((aIndex + 11451U)) & S_BLOCK1], 20U) ^ RotL64(aOperationLaneA[((aIndex + 11951U)) & S_BLOCK1], 43U));
            aIngress ^= RotL64(aExpandLaneB[((S_BLOCK1 - aIndex + 13759U)) & S_BLOCK1], 35U);
            aIngress = TwistMix64::DiffuseA(((aIngress ^ aPhaseBDomainWordIngress) ^ aNonceWordC));
            //
            aCross = RotL64(aInvestLaneC[((S_BLOCK1 - aIndex + 13798U)) & S_BLOCK1], 29U) ^ RotL64(aOperationLaneC[((S_BLOCK1 - aIndex + 15113U)) & S_BLOCK1], 3U);
            aCross = TwistMix64::DiffuseC(((aCross ^ aPhaseBDomainWordCross) ^ aNonceWordB));
            //
            aScatter = (RotL64(aPrevious, 51U) + RotL64(aCross, 21U)) ^ (RotL64(aCarry, 3U) + RotL64(aIngress, 34U));
            aScatter = TwistMix64::DiffuseC(((aScatter ^ aPhaseBDomainWordScatter) ^ aNonceWordK));
            //
            aOrbiterG = ((aWandererK + RotL64(aPrevious, 53U)) + RotL64(aCarry, 35U)) + 4622023259121087483U;
            aOrbiterI = (aWandererD + RotL64(aScatter, 27U)) + 10253505250223501352U;
            aOrbiterE = ((((aWandererF + RotL64(aIngress, 4U)) + RotL64(aCarry, 3U)) + 17133877904420462669U) + aPhaseBOrbiterAssignSaltE[(((31U - aIndex) + 12U)) & S_SALT1]) + aNonceWordK;
            aOrbiterH = (aWandererA + RotL64(aCross, 41U)) + 6162827793741796700U;
            aOrbiterK = ((aWandererC + RotL64(aIngress, 11U)) + 9610986424765907615U) + aPhaseBOrbiterAssignSaltF[(((31U - aIndex) + 18U)) & S_SALT1];
            aOrbiterJ = (((aWandererB + RotL64(aCross, 47U)) + RotL64(aCarry, 13U)) + 11210747154264753754U) + aNonceWordP;
            aOrbiterC = (aWandererJ + RotL64(aPrevious, 57U)) + 16554205219580654546U;
            aOrbiterF = (aWandererG + RotL64(aScatter, 35U)) + 10352576357413766388U;
            aOrbiterB = (aWandererI + RotL64(aPrevious, 20U)) + 3651845783283479752U;
            //
            aOrbiterG = (aOrbiterG + aOrbiterI) + 18145542190463500476U;
            aOrbiterE = (aOrbiterE ^ aOrbiterG) ^ 5415609566767162857U;
            aOrbiterE = RotL64((aOrbiterE * 6474184559323816389U), 23U);
            //
            aOrbiterH = ((aOrbiterH + aOrbiterE) + 2033734872464201570U) + aNonceWordE;
            aOrbiterK = (aOrbiterK ^ aOrbiterH) ^ 3507213117125813345U;
            aOrbiterK = RotL64((aOrbiterK * 5453058336688881113U), 47U);
            //
            aOrbiterJ = (aOrbiterJ + aOrbiterH) + 8716253393049851856U;
            aOrbiterC = ((aOrbiterC ^ aOrbiterJ) ^ 695984869565941856U) ^ aNonceWordH;
            aOrbiterC = RotL64((aOrbiterC * 8377921610764044735U), 39U);
            //
            aOrbiterK = ((aOrbiterK + aOrbiterF) + 7661578828878284931U) + aPhaseBOrbiterUpdateSaltA[((aIndex + 21U)) & S_SALT1];
            aOrbiterJ = (aOrbiterJ ^ aOrbiterK) ^ 906654265099155956U;
            aOrbiterJ = RotL64((aOrbiterJ * 8117625377607536949U), 43U);
            //
            aOrbiterF = (aOrbiterF + aOrbiterG) + 6050049984731254612U;
            aOrbiterH = ((aOrbiterH ^ aOrbiterF) ^ 17882717590338190821U) ^ aPhaseBOrbiterUpdateSaltE[(((31U - aIndex) + 4U)) & S_SALT1];
            aOrbiterH = RotL64((aOrbiterH * 10807367411402733215U), 27U);
            //
            aOrbiterB = (aOrbiterB + aOrbiterC) + 4996521991532815957U;
            aOrbiterG = ((aOrbiterG ^ aOrbiterB) ^ 4246460672800604436U) ^ aPhaseBOrbiterUpdateSaltD[((aIndex + 3U)) & S_SALT1];
            aOrbiterG = RotL64((aOrbiterG * 12047466401960824903U), 57U);
            //
            aOrbiterC = (aOrbiterC + aOrbiterK) + 8700148116452518842U;
            aOrbiterI = (aOrbiterI ^ aOrbiterC) ^ 10039050281847466206U;
            aOrbiterI = RotL64((aOrbiterI * 11884791271239660157U), 53U);
            //
            aOrbiterE = ((aOrbiterE + aOrbiterB) + 4513844680425845372U) + aNonceWordL;
            aOrbiterF = (aOrbiterF ^ aOrbiterE) ^ 3037563127442815153U;
            aOrbiterF = RotL64((aOrbiterF * 18363509277992292407U), 35U);
            //
            aOrbiterI = ((aOrbiterI + aOrbiterJ) + 1005237931570968724U) + aPhaseBOrbiterUpdateSaltC[(((31U - aIndex) + 17U)) & S_SALT1];
            aOrbiterB = (aOrbiterB ^ aOrbiterI) ^ 1373258132025712065U;
            aOrbiterB = RotL64((aOrbiterB * 10458020799382532395U), 5U);
            //
            aIngress = aOrbiterF ^ RotL64(aOrbiterB, 57U);
            aIngress = aIngress + (RotL64(aOrbiterK, 40U) ^ aOrbiterE);
            aIngress = aIngress + (aOrbiterG ^ RotL64(aOrbiterI, 19U));
            aIngress = aIngress + (aOrbiterH ^ RotL64(aOrbiterC, 23U));
            aIngress = aIngress + RotL64(aOrbiterJ, 37U);
            aIngress = TwistMix64::DiffuseA((aIngress + aScatter));
            //
            aWandererD = aWandererD ^ (((RotL64(aIngress, 60U) + RotL64(aOrbiterG, 5U)) + aOrbiterH) + aNonceWordM);
            aWandererA = aWandererA + (((RotL64(aPrevious, 39U) + aOrbiterG) + RotL64(aOrbiterB, 52U)) + RotL64(aCarry, 37U));
            aWandererC = aWandererC ^ ((RotL64(aScatter, 19U) + RotL64(aOrbiterC, 43U)) + aOrbiterB);
            aWandererJ = aWandererJ + ((RotL64(aCross, 23U) + RotL64(aOrbiterE, 39U)) + aOrbiterB);
            aWandererB = aWandererB ^ (((RotL64(aScatter, 5U) + aOrbiterE) + RotL64(aOrbiterK, 11U)) + aNonceWordO);
            aWandererG = aWandererG + (((RotL64(aIngress, 34U) + aOrbiterF) + RotL64(aOrbiterI, 57U)) + RotL64(aCarry, 53U));
            aWandererK = aWandererK ^ (((RotL64(aPrevious, 27U) + aOrbiterI) + RotL64(aOrbiterB, 47U)) + aPhaseBWandererUpdateSaltD[((aIndex + 23U)) & S_SALT1]);
            aWandererI = aWandererI + ((RotL64(aCross, 11U) + RotL64(aOrbiterJ, 22U)) + aOrbiterK);
            aWandererF = aWandererF ^ ((((RotL64(aIngress, 47U) + aOrbiterG) + RotL64(aOrbiterF, 35U)) + aNonceWordG) + aPhaseBWandererUpdateSaltC[((aIndex + 13U)) & S_SALT1]);
            //
            aCarry = aCarry + (aWandererC ^ RotL64(aWandererI, 34U));
            aCarry = aCarry + (aWandererJ ^ RotL64(aWandererG, 57U));
            aCarry = aCarry + (aWandererA ^ RotL64(aWandererD, 39U));
            aCarry = aCarry + (aWandererB ^ RotL64(aWandererF, 29U));
            aCarry = aCarry + RotL64(aWandererK, 47U);
            aCarry = aCarry + RotL64(aIngress, 21U);
            aCarry = TwistMix64::DiffuseB(aCarry);
            //
            aWorkLaneA[aIndex] = aIngress;
        }
    
        // seed_loop_b loop 4
        // ingress from: aWorkLaneA, aInvestLaneC, aFireLaneB
        // ingress directions: aWorkLaneA forward forced, aInvestLaneC forward forced, aFireLaneB forward/backward random
        // cross from: aInvestLaneD, aOperationLaneD
        // cross directions: aInvestLaneD backward forced, aOperationLaneD backward/forward random
        // write to: aWorkLaneB
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aWorkLaneA[((aIndex + 18591U)) & S_BLOCK1], 29U) ^ RotL64(aInvestLaneC[((aIndex + 18321U)) & S_BLOCK1], 58U));
            aIngress ^= RotL64(aFireLaneB[((aIndex + 16692U)) & S_BLOCK1], 41U);
            aIngress = TwistMix64::DiffuseC(((aIngress ^ aPhaseBDomainWordIngress) ^ aNonceWordF));
            //
            aCross = RotL64(aInvestLaneD[((S_BLOCK1 - aIndex + 18737U)) & S_BLOCK1], 51U) ^ RotL64(aOperationLaneD[((aIndex + 16589U)) & S_BLOCK1], 37U);
            aCross = TwistMix64::DiffuseB(((aCross ^ aPhaseBDomainWordCross) ^ aNonceWordH));
            //
            aScatter = (RotL64(aPrevious, 43U) ^ RotL64(aCross, 28U)) + (RotL64(aIngress, 11U) + RotL64(aCarry, 57U));
            aScatter = TwistMix64::DiffuseA(((aScatter ^ aPhaseBDomainWordScatter) ^ aNonceWordH));
            //
            aOrbiterI = ((aWandererC + RotL64(aIngress, 4U)) + RotL64(aCarry, 3U)) + 3248574644570178787U;
            aOrbiterJ = (aWandererG + RotL64(aCross, 57U)) + 4506961512959200024U;
            aOrbiterG = ((aWandererJ + RotL64(aPrevious, 53U)) + 8423739774540738590U) + aPhaseBOrbiterAssignSaltA[(((31U - aIndex) + 8U)) & S_SALT1];
            aOrbiterC = (((aWandererF + RotL64(aScatter, 41U)) + RotL64(aCarry, 19U)) + 6593975869641735337U) + aNonceWordD;
            aOrbiterH = ((aWandererB + RotL64(aPrevious, 23U)) + RotL64(aCarry, 41U)) + 16441716090557369103U;
            aOrbiterB = ((aWandererD + RotL64(aIngress, 12U)) + 7936601450453207914U) + aNonceWordN;
            aOrbiterD = (aWandererI + RotL64(aCross, 19U)) + 13333752583560167065U;
            aOrbiterA = ((aWandererK + RotL64(aScatter, 29U)) + 8013703284795432973U) + aPhaseBOrbiterAssignSaltD[((aIndex + 14U)) & S_SALT1];
            aOrbiterK = (aWandererA + RotL64(aCross, 37U)) + 2349852779887439236U;
            //
            aOrbiterI = ((aOrbiterI + aOrbiterJ) + 5318539364763284138U) + aPhaseBOrbiterUpdateSaltB[(((31U - aIndex) + 19U)) & S_SALT1];
            aOrbiterG = (aOrbiterG ^ aOrbiterI) ^ 11450957608502944376U;
            aOrbiterG = RotL64((aOrbiterG * 1957880366707810635U), 47U);
            //
            aOrbiterC = (aOrbiterC + aOrbiterI) + 9058992558327552687U;
            aOrbiterH = (aOrbiterH ^ aOrbiterC) ^ 632095686920230926U;
            aOrbiterH = RotL64((aOrbiterH * 12460364388358520799U), 57U);
            //
            aOrbiterB = (aOrbiterB + aOrbiterD) + 14734218428913777098U;
            aOrbiterI = (aOrbiterI ^ aOrbiterB) ^ 16344357661370784442U;
            aOrbiterI = RotL64((aOrbiterI * 15049472842002138369U), 37U);
            //
            aOrbiterJ = ((aOrbiterJ + aOrbiterH) + 2981145363531184308U) + aPhaseBOrbiterUpdateSaltD[(((31U - aIndex) + 11U)) & S_SALT1];
            aOrbiterA = (aOrbiterA ^ aOrbiterJ) ^ 14176472085175714494U;
            aOrbiterA = RotL64((aOrbiterA * 2584623327412130939U), 3U);
            //
            aOrbiterG = (aOrbiterG + aOrbiterA) + 11198457590069700889U;
            aOrbiterB = ((aOrbiterB ^ aOrbiterG) ^ 952584436750426828U) ^ aNonceWordM;
            aOrbiterB = RotL64((aOrbiterB * 1165713888651280355U), 11U);
            //
            aOrbiterA = (aOrbiterA + aOrbiterK) + 4311591763498985972U;
            aOrbiterD = ((aOrbiterD ^ aOrbiterA) ^ 16194341833989936369U) ^ aPhaseBOrbiterUpdateSaltF[((aIndex + 25U)) & S_SALT1];
            aOrbiterD = RotL64((aOrbiterD * 9997934560195932575U), 43U);
            //
            aOrbiterH = (aOrbiterH + aOrbiterG) + 7560794022401107431U;
            aOrbiterK = (aOrbiterK ^ aOrbiterH) ^ 10683789740265711603U;
            aOrbiterK = RotL64((aOrbiterK * 15637823045351977883U), 53U);
            //
            aOrbiterK = (aOrbiterK + aOrbiterB) + 11614366395125937178U;
            aOrbiterC = (((aOrbiterC ^ aOrbiterK) ^ 10750771385100564416U) ^ aPhaseBOrbiterUpdateSaltE[((aIndex + 20U)) & S_SALT1]) ^ aNonceWordP;
            aOrbiterC = RotL64((aOrbiterC * 4987921274272444283U), 27U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterC) + 2934697034132204529U;
            aOrbiterJ = (aOrbiterJ ^ aOrbiterD) ^ 4646873794658020363U;
            aOrbiterJ = RotL64((aOrbiterJ * 10555456865641580175U), 23U);
            //
            aIngress = aOrbiterJ ^ RotL64(aOrbiterH, 5U);
            aIngress = aIngress + (RotL64(aOrbiterI, 11U) ^ aOrbiterK);
            aIngress = aIngress + (aOrbiterC ^ RotL64(aOrbiterG, 21U));
            aIngress = aIngress + (RotL64(aOrbiterD, 52U) ^ aOrbiterB);
            aIngress = aIngress + RotL64(aOrbiterA, 27U);
            aIngress = TwistMix64::DiffuseB((aIngress + aScatter));
            //
            aWandererI = aWandererI + (((RotL64(aIngress, 47U) + RotL64(aOrbiterA, 29U)) + aOrbiterK) + RotL64(aCarry, 53U));
            aWandererG = aWandererG ^ (((RotL64(aPrevious, 53U) + RotL64(aOrbiterH, 54U)) + aOrbiterK) + aNonceWordE);
            aWandererC = aWandererC + (((RotL64(aScatter, 10U) + aOrbiterD) + RotL64(aOrbiterJ, 41U)) + aPhaseBWandererUpdateSaltB[(((31U - aIndex) + 24U)) & S_SALT1]);
            aWandererA = aWandererA ^ ((RotL64(aCross, 57U) + RotL64(aOrbiterA, 3U)) + aOrbiterD);
            aWandererF = aWandererF + ((RotL64(aScatter, 29U) + aOrbiterC) + RotL64(aOrbiterB, 11U));
            aWandererJ = aWandererJ ^ ((((RotL64(aPrevious, 19U) + aOrbiterC) + RotL64(aOrbiterJ, 19U)) + aNonceWordI) + aPhaseBWandererUpdateSaltF[(((31U - aIndex) + 7U)) & S_SALT1]);
            aWandererK = aWandererK + (((RotL64(aCross, 24U) + aOrbiterJ) + RotL64(aOrbiterG, 47U)) + RotL64(aCarry, 43U));
            aWandererB = aWandererB ^ ((RotL64(aIngress, 35U) + aOrbiterG) + RotL64(aOrbiterI, 35U));
            aWandererD = aWandererD + ((RotL64(aPrevious, 43U) + RotL64(aOrbiterB, 58U)) + aOrbiterG);
            //
            aCarry = aCarry + (aWandererG ^ RotL64(aWandererF, 39U));
            aCarry = aCarry + (RotL64(aWandererK, 27U) ^ aWandererD);
            aCarry = aCarry + (RotL64(aWandererC, 57U) ^ aWandererB);
            aCarry = aCarry + (aWandererI ^ RotL64(aWandererA, 36U));
            aCarry = aCarry + RotL64(aWandererJ, 47U);
            aCarry = aCarry + RotL64(aIngress, 11U);
            aCarry = TwistMix64::DiffuseA(aCarry);
            //
            aWorkLaneB[S_BLOCK1 - aIndex] = aIngress;
        }
    
        // seed_loop_b loop 5
        // ingress from: aWorkLaneB, aInvestLaneD, aFireLaneD
        // ingress directions: aWorkLaneB forward forced, aInvestLaneD forward forced, aFireLaneD forward/backward random
        // cross from: aWorkLaneA, aInvestLaneC
        // cross directions: aWorkLaneA backward forced, aInvestLaneC backward/forward random
        // write to: aWorkLaneC
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aWorkLaneB[((aIndex + 26317U)) & S_BLOCK1], 53U) ^ RotL64(aInvestLaneD[((aIndex + 23406U)) & S_BLOCK1], 20U));
            aIngress ^= RotL64(aFireLaneD[((S_BLOCK1 - aIndex + 26756U)) & S_BLOCK1], 29U);
            aIngress = TwistMix64::DiffuseB(((aIngress ^ aPhaseBDomainWordIngress) ^ aNonceWordM));
            //
            aCross = RotL64(aWorkLaneA[((S_BLOCK1 - aIndex + 24864U)) & S_BLOCK1], 40U) ^ RotL64(aInvestLaneC[((S_BLOCK1 - aIndex + 26706U)) & S_BLOCK1], 3U);
            aCross = TwistMix64::DiffuseB(((aCross ^ aPhaseBDomainWordCross) ^ aNonceWordC));
            //
            aScatter = (RotL64(aIngress, 51U) + RotL64(aCarry, 35U)) ^ (RotL64(aCross, 18U) ^ RotL64(aPrevious, 3U));
            aScatter = TwistMix64::DiffuseC(((aScatter ^ aPhaseBDomainWordScatter) ^ aNonceWordF));
            //
            aOrbiterJ = (aWandererI + RotL64(aPrevious, 29U)) + 13481227414590594621U;
            aOrbiterH = ((((aWandererH + RotL64(aIngress, 4U)) + RotL64(aCarry, 57U)) + 17425964381118918026U) + aPhaseBOrbiterAssignSaltB[(((31U - aIndex) + 26U)) & S_SALT1]) + aNonceWordJ;
            aOrbiterD = (aWandererA + RotL64(aScatter, 23U)) + 4792004356135956581U;
            aOrbiterB = (((aWandererJ + RotL64(aCross, 35U)) + 11926849936000639098U) + aPhaseBOrbiterAssignSaltC[((aIndex + 3U)) & S_SALT1]) + aNonceWordK;
            aOrbiterE = ((aWandererG + RotL64(aScatter, 57U)) + RotL64(aCarry, 11U)) + 990697329347742142U;
            aOrbiterI = ((aWandererF + RotL64(aPrevious, 10U)) + RotL64(aCarry, 41U)) + 9307721505373076588U;
            aOrbiterK = (aWandererC + RotL64(aCross, 47U)) + 17605732738841908719U;
            aOrbiterA = (aWandererD + RotL64(aIngress, 51U)) + 13110764518634187439U;
            aOrbiterF = (aWandererB + RotL64(aCross, 43U)) + 17970109897810645911U;
            //
            aOrbiterJ = (aOrbiterJ + aOrbiterH) + 10273133817644703654U;
            aOrbiterD = (aOrbiterD ^ aOrbiterJ) ^ 11239046688920468137U;
            aOrbiterD = RotL64((aOrbiterD * 5197802934333553327U), 47U);
            //
            aOrbiterH = (aOrbiterH + aOrbiterB) + 8355821483275763145U;
            aOrbiterE = ((aOrbiterE ^ aOrbiterH) ^ 15522151127786049345U) ^ aNonceWordI;
            aOrbiterE = RotL64((aOrbiterE * 4844278537850520413U), 27U);
            //
            aOrbiterI = (aOrbiterI + aOrbiterK) + 5381663179722418112U;
            aOrbiterB = ((aOrbiterB ^ aOrbiterI) ^ 9551368011768104906U) ^ aPhaseBOrbiterUpdateSaltE[(((31U - aIndex) + 10U)) & S_SALT1];
            aOrbiterB = RotL64((aOrbiterB * 14202470972121732997U), 43U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterE) + 16264476585232221270U;
            aOrbiterI = (aOrbiterI ^ aOrbiterD) ^ 7721417776432288282U;
            aOrbiterI = RotL64((aOrbiterI * 10267770327791051869U), 19U);
            //
            aOrbiterE = (aOrbiterE + aOrbiterA) + 339418090653475277U;
            aOrbiterK = ((aOrbiterK ^ aOrbiterE) ^ 3247926250495935511U) ^ aPhaseBOrbiterUpdateSaltC[((aIndex + 16U)) & S_SALT1];
            aOrbiterK = RotL64((aOrbiterK * 16824669543765729097U), 23U);
            //
            aOrbiterB = (aOrbiterB + aOrbiterJ) + 3390560045236418590U;
            aOrbiterA = ((aOrbiterA ^ aOrbiterB) ^ 3894024951542543635U) ^ aPhaseBOrbiterUpdateSaltF[(((31U - aIndex) + 12U)) & S_SALT1];
            aOrbiterA = RotL64((aOrbiterA * 10599637790900418767U), 35U);
            //
            aOrbiterA = (aOrbiterA + aOrbiterD) + 3878539166189668154U;
            aOrbiterF = ((aOrbiterF ^ aOrbiterA) ^ 5617705593218220843U) ^ aNonceWordH;
            aOrbiterF = RotL64((aOrbiterF * 82771190372750823U), 57U);
            //
            aOrbiterK = (aOrbiterK + aOrbiterF) + 12320861089148474544U;
            aOrbiterJ = (aOrbiterJ ^ aOrbiterK) ^ 14943790251625519550U;
            aOrbiterJ = RotL64((aOrbiterJ * 13758322022902008313U), 53U);
            //
            aOrbiterF = ((aOrbiterF + aOrbiterI) + 18119213517612562775U) + aPhaseBOrbiterUpdateSaltB[((aIndex + 4U)) & S_SALT1];
            aOrbiterH = (aOrbiterH ^ aOrbiterF) ^ 1413193144229486646U;
            aOrbiterH = RotL64((aOrbiterH * 14562375280658115687U), 11U);
            //
            aIngress = RotL64(aOrbiterA, 5U) ^ aOrbiterD;
            aIngress = aIngress + (aOrbiterH ^ RotL64(aOrbiterF, 13U));
            aIngress = aIngress + (aOrbiterJ ^ RotL64(aOrbiterI, 24U));
            aIngress = aIngress + (RotL64(aOrbiterB, 29U) ^ aOrbiterE);
            aIngress = aIngress + RotL64(aOrbiterK, 19U);
            aIngress = TwistMix64::DiffuseB((aIngress + aScatter));
            //
            aWandererC = aWandererC + (((((RotL64(aScatter, 57U) + RotL64(aOrbiterA, 43U)) + aOrbiterF) + RotL64(aCarry, 37U)) + aNonceWordN) + aPhaseBWandererUpdateSaltA[(((31U - aIndex) + 9U)) & S_SALT1]);
            aWandererH = aWandererH ^ (((RotL64(aCross, 12U) + aOrbiterD) + RotL64(aOrbiterK, 60U)) + aPhaseBWandererUpdateSaltE[((aIndex + 11U)) & S_SALT1]);
            aWandererA = aWandererA + (((RotL64(aIngress, 5U) + RotL64(aOrbiterF, 39U)) + aOrbiterB) + aNonceWordA);
            aWandererF = aWandererF ^ (((RotL64(aPrevious, 43U) + RotL64(aOrbiterJ, 5U)) + aOrbiterB) + aNonceWordD);
            aWandererJ = aWandererJ + ((RotL64(aCross, 19U) + RotL64(aOrbiterK, 47U)) + aOrbiterF);
            aWandererB = aWandererB ^ ((RotL64(aIngress, 35U) + aOrbiterF) + RotL64(aOrbiterH, 12U));
            aWandererG = aWandererG + ((RotL64(aScatter, 39U) + RotL64(aOrbiterD, 53U)) + aOrbiterI);
            aWandererD = aWandererD ^ ((RotL64(aPrevious, 50U) + RotL64(aOrbiterE, 19U)) + aOrbiterH);
            aWandererI = aWandererI + ((((RotL64(aIngress, 23U) + aOrbiterE) + RotL64(aOrbiterK, 35U)) + RotL64(aCarry, 19U)) + aNonceWordG);
            //
            aCarry = aCarry + (RotL64(aWandererG, 37U) ^ aWandererF);
            aCarry = aCarry + (RotL64(aWandererI, 54U) ^ aWandererJ);
            aCarry = aCarry + (aWandererC ^ RotL64(aWandererD, 51U));
            aCarry = aCarry + (RotL64(aWandererH, 47U) ^ aWandererA);
            aCarry = aCarry + RotL64(aWandererB, 57U);
            aCarry = aCarry + RotL64(aIngress, 41U);
            aCarry = TwistMix64::DiffuseC(aCarry);
            //
            aWorkLaneC[aIndex] = aIngress;
        }
    
        // seed_loop_b loop 6
        // ingress from: aWorkLaneC, aWorkLaneA, aExpandLaneC
        // ingress directions: aWorkLaneC forward forced, aWorkLaneA forward forced, aExpandLaneC forward/backward random
        // cross from: aWorkLaneB, aOperationLaneB
        // cross directions: aWorkLaneB backward forced, aOperationLaneB backward/forward random
        // write to: aWorkLaneD
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aWorkLaneC[((aIndex + 29207U)) & S_BLOCK1], 3U) ^ RotL64(aWorkLaneA[((aIndex + 32629U)) & S_BLOCK1], 27U));
            aIngress ^= RotL64(aExpandLaneC[((aIndex + 29245U)) & S_BLOCK1], 18U);
            aIngress = TwistMix64::DiffuseC(((aIngress ^ aPhaseBDomainWordIngress) ^ aNonceWordB));
            //
            aCross = RotL64(aWorkLaneB[((S_BLOCK1 - aIndex + 27546U)) & S_BLOCK1], 58U) ^ RotL64(aOperationLaneB[((S_BLOCK1 - aIndex + 29968U)) & S_BLOCK1], 35U);
            aCross = TwistMix64::DiffuseA(((aCross ^ aPhaseBDomainWordCross) ^ aNonceWordP));
            //
            aScatter = (RotL64(aPrevious, 18U) + RotL64(aCross, 53U)) ^ (RotL64(aCarry, 39U) + RotL64(aIngress, 5U));
            aScatter = TwistMix64::DiffuseA(((aScatter ^ aPhaseBDomainWordScatter) ^ aNonceWordL));
            //
            aOrbiterA = (aWandererK + RotL64(aIngress, 47U)) + 3561491146322798260U;
            aOrbiterC = (((aWandererG + RotL64(aCross, 19U)) + RotL64(aCarry, 3U)) + 7075025056181885339U) + aNonceWordL;
            aOrbiterD = ((aWandererH + RotL64(aPrevious, 58U)) + 9230910887904171613U) + aPhaseBOrbiterAssignSaltE[((aIndex + 17U)) & S_SALT1];
            aOrbiterI = (((aWandererB + RotL64(aScatter, 39U)) + RotL64(aCarry, 53U)) + 4119781172609908917U) + aNonceWordN;
            aOrbiterG = ((aWandererC + RotL64(aPrevious, 23U)) + RotL64(aCarry, 37U)) + 17155609083870983149U;
            aOrbiterF = ((aWandererJ + RotL64(aCross, 35U)) + 2423018561430181695U) + aNonceWordA;
            aOrbiterK = (aWandererD + RotL64(aScatter, 52U)) + 12957280305617615744U;
            aOrbiterB = ((aWandererI + RotL64(aIngress, 27U)) + 2461704174772065813U) + aPhaseBOrbiterAssignSaltF[((aIndex + 12U)) & S_SALT1];
            aOrbiterJ = ((aWandererA + RotL64(aPrevious, 13U)) + 7907123257849391997U) + aNonceWordH;
            //
            aOrbiterA = (((aOrbiterA + aOrbiterC) + 7257868138318960007U) + aPhaseBOrbiterUpdateSaltD[(((31U - aIndex) + 3U)) & S_SALT1]) + aNonceWordE;
            aOrbiterD = ((aOrbiterD ^ aOrbiterA) ^ 16425903703085702285U) ^ aPhaseBOrbiterUpdateSaltB[(((31U - aIndex) + 13U)) & S_SALT1];
            aOrbiterD = RotL64((aOrbiterD * 7996935869077231999U), 3U);
            //
            aOrbiterI = (aOrbiterI + aOrbiterD) + 2990822664594079467U;
            aOrbiterG = ((aOrbiterG ^ aOrbiterI) ^ 5654819006718953817U) ^ aNonceWordC;
            aOrbiterG = RotL64((aOrbiterG * 4465096036756887801U), 19U);
            //
            aOrbiterF = (aOrbiterF + aOrbiterK) + 12183676471235678779U;
            aOrbiterC = (aOrbiterC ^ aOrbiterF) ^ 15026286960542123922U;
            aOrbiterC = RotL64((aOrbiterC * 17199049329995315279U), 57U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterB) + 12169080607071830522U;
            aOrbiterF = ((aOrbiterF ^ aOrbiterD) ^ 2906296852254787499U) ^ aNonceWordG;
            aOrbiterF = RotL64((aOrbiterF * 6754514406846040163U), 23U);
            //
            aOrbiterC = (aOrbiterC + aOrbiterJ) + 3029858695410344584U;
            aOrbiterB = (aOrbiterB ^ aOrbiterC) ^ 14406410317495954566U;
            aOrbiterB = RotL64((aOrbiterB * 9663780721657983421U), 37U);
            //
            aOrbiterB = (aOrbiterB + aOrbiterI) + 11048818178401163861U;
            aOrbiterK = ((aOrbiterK ^ aOrbiterB) ^ 13622063920319445043U) ^ aPhaseBOrbiterUpdateSaltE[(((31U - aIndex) + 28U)) & S_SALT1];
            aOrbiterK = RotL64((aOrbiterK * 2516025554421589857U), 29U);
            //
            aOrbiterK = (aOrbiterK + aOrbiterG) + 2642646089141233277U;
            aOrbiterJ = ((aOrbiterJ ^ aOrbiterK) ^ 12761571777929273548U) ^ aNonceWordJ;
            aOrbiterJ = RotL64((aOrbiterJ * 5518252696078700127U), 47U);
            //
            aOrbiterJ = ((aOrbiterJ + aOrbiterA) + 7753802695131502382U) + aPhaseBOrbiterUpdateSaltA[(((31U - aIndex) + 29U)) & S_SALT1];
            aOrbiterI = (aOrbiterI ^ aOrbiterJ) ^ 8510425459525030222U;
            aOrbiterI = RotL64((aOrbiterI * 12412361423636026483U), 13U);
            //
            aOrbiterG = (aOrbiterG + aOrbiterF) + 13522645164493316722U;
            aOrbiterA = (aOrbiterA ^ aOrbiterG) ^ 1437430302489702713U;
            aOrbiterA = RotL64((aOrbiterA * 14019316635365783545U), 43U);
            //
            aIngress = RotL64(aOrbiterK, 11U) ^ aOrbiterF;
            aIngress = aIngress + (aOrbiterB ^ RotL64(aOrbiterG, 51U));
            aIngress = aIngress + (RotL64(aOrbiterJ, 29U) ^ aOrbiterD);
            aIngress = aIngress + (aOrbiterA ^ RotL64(aOrbiterI, 4U));
            aIngress = aIngress + RotL64(aOrbiterC, 57U);
            aIngress = TwistMix64::DiffuseC((aIngress + aScatter));
            //
            aWandererB = aWandererB ^ (((RotL64(aPrevious, 29U) + RotL64(aOrbiterG, 43U)) + aOrbiterI) + aPhaseBWandererUpdateSaltC[(((31U - aIndex) + 10U)) & S_SALT1]);
            aWandererG = aWandererG + ((RotL64(aIngress, 3U) + RotL64(aOrbiterA, 19U)) + aOrbiterD);
            aWandererA = aWandererA ^ ((((RotL64(aCross, 24U) + aOrbiterB) + RotL64(aOrbiterK, 47U)) + aNonceWordF) + aPhaseBWandererUpdateSaltD[((aIndex + 22U)) & S_SALT1]);
            aWandererC = aWandererC + (((RotL64(aScatter, 37U) + RotL64(aOrbiterC, 29U)) + aOrbiterJ) + aNonceWordO);
            aWandererI = aWandererI ^ ((RotL64(aCross, 13U) + RotL64(aOrbiterB, 24U)) + aOrbiterI);
            aWandererJ = aWandererJ + (((RotL64(aScatter, 43U) + RotL64(aOrbiterB, 53U)) + aOrbiterF) + RotL64(aCarry, 57U));
            aWandererK = aWandererK ^ ((RotL64(aIngress, 19U) + aOrbiterC) + RotL64(aOrbiterG, 3U));
            aWandererH = aWandererH + (((RotL64(aPrevious, 47U) + RotL64(aOrbiterD, 57U)) + aOrbiterI) + RotL64(aCarry, 37U));
            aWandererD = aWandererD ^ (((RotL64(aScatter, 56U) + RotL64(aOrbiterB, 12U)) + aOrbiterJ) + aNonceWordD);
            //
            aCarry = aCarry + (RotL64(aWandererB, 30U) ^ aWandererH);
            aCarry = aCarry + (aWandererI ^ RotL64(aWandererK, 51U));
            aCarry = aCarry + (aWandererA ^ RotL64(aWandererG, 19U));
            aCarry = aCarry + (RotL64(aWandererJ, 39U) ^ aWandererD);
            aCarry = aCarry + RotL64(aWandererC, 43U);
            aCarry = aCarry + RotL64(aIngress, 35U);
            aCarry = TwistMix64::DiffuseC(aCarry);
            //
            aWorkLaneD[S_BLOCK1 - aIndex] = aIngress;
        }
    }
    // GSeedRunSeed_C seed_loop_b (end)
    *pPrevious = aPrevious;
    *pIngress = aIngress;
    *pCarry = aCarry;
    *pWandererA = aWandererA;
    *pWandererB = aWandererB;
    *pWandererC = aWandererC;
    *pWandererD = aWandererD;
    *pWandererE = aWandererE;
    *pWandererF = aWandererF;
    *pWandererG = aWandererG;
    *pWandererH = aWandererH;
    *pWandererI = aWandererI;
    *pWandererJ = aWandererJ;
    *pWandererK = aWandererK;
}

void TwistExpander_Exercea_Arx::Seed_D(TwistWorkSpace *pWorkSpace,
                     std::uint64_t pNonce,
                     std::uint64_t *pPrevious,
                     std::uint64_t *pIngress,
                     std::uint64_t *pCarry,
                     std::uint64_t *pWandererA,
                     std::uint64_t *pWandererB,
                     std::uint64_t *pWandererC,
                     std::uint64_t *pWandererD,
                     std::uint64_t *pWandererE,
                     std::uint64_t *pWandererF,
                     std::uint64_t *pWandererG,
                     std::uint64_t *pWandererH,
                     std::uint64_t *pWandererI,
                     std::uint64_t *pWandererJ,
                     std::uint64_t *pWandererK) {
    [[maybe_unused]] std::uint8_t *aExpandLaneA = pWorkSpace->mExpansionLaneA;
    [[maybe_unused]] std::uint8_t *aExpandLaneB = pWorkSpace->mExpansionLaneB;
    [[maybe_unused]] std::uint8_t *aExpandLaneC = pWorkSpace->mExpansionLaneC;
    [[maybe_unused]] std::uint8_t *aExpandLaneD = pWorkSpace->mExpansionLaneD;
    [[maybe_unused]] std::uint8_t *aSnowLaneA = pWorkSpace->mSnowLaneA;
    [[maybe_unused]] std::uint8_t *aSnowLaneB = pWorkSpace->mSnowLaneB;
    [[maybe_unused]] std::uint8_t *aFireLaneA = pWorkSpace->mFireLaneA;
    [[maybe_unused]] std::uint8_t *aFireLaneB = pWorkSpace->mFireLaneB;
    [[maybe_unused]] std::uint8_t *aFireLaneC = pWorkSpace->mFireLaneC;
    [[maybe_unused]] std::uint8_t *aFireLaneD = pWorkSpace->mFireLaneD;
    [[maybe_unused]] std::uint8_t *aInvestLaneA = pWorkSpace->mInvestLaneA;
    [[maybe_unused]] std::uint8_t *aInvestLaneB = pWorkSpace->mInvestLaneB;
    [[maybe_unused]] std::uint8_t *aInvestLaneC = pWorkSpace->mInvestLaneC;
    [[maybe_unused]] std::uint8_t *aInvestLaneD = pWorkSpace->mInvestLaneD;
    [[maybe_unused]] std::uint64_t *aPhaseDOrbiterAssignSaltA = pWorkSpace->mDomainBundle.mPhaseDSalts.mOrbiterAssign.mSaltA;
    [[maybe_unused]] std::uint64_t *aPhaseDOrbiterAssignSaltB = pWorkSpace->mDomainBundle.mPhaseDSalts.mOrbiterAssign.mSaltB;
    [[maybe_unused]] std::uint64_t *aPhaseDOrbiterAssignSaltC = pWorkSpace->mDomainBundle.mPhaseDSalts.mOrbiterAssign.mSaltC;
    [[maybe_unused]] std::uint64_t *aPhaseDOrbiterAssignSaltD = pWorkSpace->mDomainBundle.mPhaseDSalts.mOrbiterAssign.mSaltD;
    [[maybe_unused]] std::uint64_t *aPhaseDOrbiterAssignSaltE = pWorkSpace->mDomainBundle.mPhaseDSalts.mOrbiterAssign.mSaltE;
    [[maybe_unused]] std::uint64_t *aPhaseDOrbiterAssignSaltF = pWorkSpace->mDomainBundle.mPhaseDSalts.mOrbiterAssign.mSaltF;
    [[maybe_unused]] std::uint64_t *aPhaseDOrbiterUpdateSaltA = pWorkSpace->mDomainBundle.mPhaseDSalts.mOrbiterUpdate.mSaltA;
    [[maybe_unused]] std::uint64_t *aPhaseDOrbiterUpdateSaltB = pWorkSpace->mDomainBundle.mPhaseDSalts.mOrbiterUpdate.mSaltB;
    [[maybe_unused]] std::uint64_t *aPhaseDOrbiterUpdateSaltC = pWorkSpace->mDomainBundle.mPhaseDSalts.mOrbiterUpdate.mSaltC;
    [[maybe_unused]] std::uint64_t *aPhaseDOrbiterUpdateSaltD = pWorkSpace->mDomainBundle.mPhaseDSalts.mOrbiterUpdate.mSaltD;
    [[maybe_unused]] std::uint64_t *aPhaseDOrbiterUpdateSaltE = pWorkSpace->mDomainBundle.mPhaseDSalts.mOrbiterUpdate.mSaltE;
    [[maybe_unused]] std::uint64_t *aPhaseDOrbiterUpdateSaltF = pWorkSpace->mDomainBundle.mPhaseDSalts.mOrbiterUpdate.mSaltF;
    [[maybe_unused]] std::uint64_t *aPhaseDWandererUpdateSaltA = pWorkSpace->mDomainBundle.mPhaseDSalts.mWandererUpdate.mSaltA;
    [[maybe_unused]] std::uint64_t *aPhaseDWandererUpdateSaltB = pWorkSpace->mDomainBundle.mPhaseDSalts.mWandererUpdate.mSaltB;
    [[maybe_unused]] std::uint64_t *aPhaseDWandererUpdateSaltC = pWorkSpace->mDomainBundle.mPhaseDSalts.mWandererUpdate.mSaltC;
    [[maybe_unused]] std::uint64_t *aPhaseDWandererUpdateSaltD = pWorkSpace->mDomainBundle.mPhaseDSalts.mWandererUpdate.mSaltD;
    [[maybe_unused]] std::uint64_t *aPhaseDWandererUpdateSaltE = pWorkSpace->mDomainBundle.mPhaseDSalts.mWandererUpdate.mSaltE;
    [[maybe_unused]] std::uint64_t *aPhaseDWandererUpdateSaltF = pWorkSpace->mDomainBundle.mPhaseDSalts.mWandererUpdate.mSaltF;
    const std::uint64_t &aPhaseDDomainWordIngress = pWorkSpace->mDomainBundle.mPhaseDConstants.mIngress;
    const std::uint64_t &aPhaseDDomainWordScatter = pWorkSpace->mDomainBundle.mPhaseDConstants.mScatter;
    const std::uint64_t &aPhaseDDomainWordCross = pWorkSpace->mDomainBundle.mPhaseDConstants.mCross;
    std::uint64_t aCross = 0; std::uint64_t aScatter = 0;

    std::uint64_t aOrbiterA = 0; std::uint64_t aOrbiterB = 0; std::uint64_t aOrbiterC = 0; std::uint64_t aOrbiterD = 0;
    std::uint64_t aOrbiterE = 0; std::uint64_t aOrbiterF = 0; std::uint64_t aOrbiterG = 0; std::uint64_t aOrbiterH = 0;
    std::uint64_t aOrbiterI = 0; std::uint64_t aOrbiterJ = 0; std::uint64_t aOrbiterK = 0;

    // [seed arx]
    [[maybe_unused]] std::uint8_t *mSource = pWorkSpace->mSource;
    std::uint64_t aPrevious = *pPrevious;
    std::uint64_t aIngress = *pIngress;
    std::uint64_t aCarry = *pCarry;
    std::uint64_t aWandererA = *pWandererA;
    std::uint64_t aWandererB = *pWandererB;
    std::uint64_t aWandererC = *pWandererC;
    std::uint64_t aWandererD = *pWandererD;
    std::uint64_t aWandererE = *pWandererE;
    std::uint64_t aWandererF = *pWandererF;
    std::uint64_t aWandererG = *pWandererG;
    std::uint64_t aWandererH = *pWandererH;
    std::uint64_t aWandererI = *pWandererI;
    std::uint64_t aWandererJ = *pWandererJ;
    std::uint64_t aWandererK = *pWandererK;
    std::uint64_t aNonceWordA = TwistMix64::DiffuseB(pNonce * 0xEB4A27AAB10D9ED5ULL + 0x8286FF0C8816EE44ULL);
    std::uint64_t aNonceWordB = TwistMix64::DiffuseB(pNonce * 0xC8ADFD76BECA8E25ULL + 0xCE04BDC967ABD236ULL);
    std::uint64_t aNonceWordC = TwistMix64::DiffuseC(pNonce * 0x97E8BA615AD51553ULL + 0xE1676162F7830234ULL);
    std::uint64_t aNonceWordD = TwistMix64::DiffuseA(pNonce * 0xF622D52A191990E5ULL + 0xF877A8DCE9891D2FULL);
    std::uint64_t aNonceWordE = TwistMix64::DiffuseA(pNonce * 0xCD269CB2681E102BULL + 0x888E6300672E40D3ULL);
    std::uint64_t aNonceWordF = TwistMix64::DiffuseC(pNonce * 0xDA5262567EEE1477ULL + 0xD79C4B57D97DBB06ULL);
    std::uint64_t aNonceWordG = TwistMix64::DiffuseC(pNonce * 0xF7AF1FE7AC4217B1ULL + 0x9EF341771BB09543ULL);
    std::uint64_t aNonceWordH = TwistMix64::DiffuseC(pNonce * 0x8CB2FD84E1B05203ULL + 0xF6622BD3C8E08D55ULL);
    std::uint64_t aNonceWordI = TwistMix64::DiffuseC(pNonce * 0xB3924FCE5C3E33D1ULL + 0x82E4C62700ACA130ULL);
    std::uint64_t aNonceWordJ = TwistMix64::DiffuseB(pNonce * 0xDD7595D230EF566DULL + 0xD68C83AC176A70C2ULL);
    std::uint64_t aNonceWordK = TwistMix64::DiffuseC(pNonce * 0x8A491E2BA275E64FULL + 0xA6E224CD834DB43BULL);
    std::uint64_t aNonceWordL = TwistMix64::DiffuseB(pNonce * 0x8D8C14C35CD6F6DBULL + 0x821A3EFBD8CFD8BDULL);
    std::uint64_t aNonceWordM = TwistMix64::DiffuseA(pNonce * 0xA6E955E0FF1D4BB5ULL + 0x99A5C6397C0559B3ULL);
    std::uint64_t aNonceWordN = TwistMix64::DiffuseC(pNonce * 0xC82D946E691E3649ULL + 0x898BA146A20BD3FAULL);
    std::uint64_t aNonceWordO = TwistMix64::DiffuseA(pNonce * 0xC2E22FB914B3B531ULL + 0xBB5E49BE51C300DEULL);
    std::uint64_t aNonceWordP = TwistMix64::DiffuseB(pNonce * 0xEFEF70A32530A87FULL + 0x8D36F9A8B82C1D5AULL);
    // GSeedRunSeed_D seed_loop_d (start)
    {
        // GSeedRunSeed_D seed_loop_d lane group
        // read from: aExpandLaneA, aExpandLaneB, aInvestLaneA, aExpandLaneC, aExpandLaneD, aInvestLaneB, aSnowLaneA, aInvestLaneC, aInvestLaneD, aSnowLaneB, aFireLaneA, aFireLaneB, aFireLaneC, aFireLaneD
        // write to: aSnowLaneA, aSnowLaneB, aInvestLaneA, aInvestLaneB, aInvestLaneC, aInvestLaneD
    
        // seed_loop_d loop 1
        // ingress from: aExpandLaneA, aExpandLaneB, aInvestLaneA
        // ingress directions: aExpandLaneA forward forced, aExpandLaneB forward forced, aInvestLaneA forward/backward random
        // cross from: aExpandLaneC, aExpandLaneD, aInvestLaneB
        // cross directions: aExpandLaneC backward forced, aExpandLaneD backward forced, aInvestLaneB backward/forward random
        // write to: aSnowLaneA
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aExpandLaneA[((aIndex + 2103U)) & S_BLOCK1], 11U) ^ RotL64(aExpandLaneB[((aIndex + 3436U)) & S_BLOCK1], 41U));
            aIngress ^= RotL64(aInvestLaneA[((aIndex + 4766U)) & S_BLOCK1], 20U);
            aIngress = TwistMix64::DiffuseA(((aIngress ^ aPhaseDDomainWordIngress) ^ aNonceWordP));
            //
            aCross = (RotL64(aExpandLaneC[((S_BLOCK1 - aIndex + 4549U)) & S_BLOCK1], 27U) ^ RotL64(aExpandLaneD[((S_BLOCK1 - aIndex + 3641U)) & S_BLOCK1], 43U));
            aCross ^= RotL64(aInvestLaneB[((aIndex + 2692U)) & S_BLOCK1], 53U);
            aCross = TwistMix64::DiffuseC(((aCross ^ aPhaseDDomainWordCross) ^ aNonceWordF));
            //
            aScatter = (RotL64(aCross, 23U) ^ RotL64(aPrevious, 51U)) + (RotL64(aCarry, 6U) ^ RotL64(aIngress, 37U));
            aScatter = TwistMix64::DiffuseC(((aScatter ^ aPhaseDDomainWordScatter) ^ aNonceWordL));
            //
            aOrbiterD = ((aWandererA + RotL64(aScatter, 3U)) + 9471546960258473684U) + aNonceWordC;
            aOrbiterF = ((aWandererG + RotL64(aPrevious, 47U)) + RotL64(aCarry, 51U)) + 18050235435948942244U;
            aOrbiterA = ((aWandererB + RotL64(aCross, 41U)) + 3005107102671544641U) + aPhaseDOrbiterAssignSaltE[((aIndex + 29U)) & S_SALT1];
            aOrbiterC = ((aWandererI + RotL64(aIngress, 19U)) + RotL64(aCarry, 19U)) + 17898396434573801850U;
            aOrbiterJ = ((((aWandererF + RotL64(aScatter, 29U)) + RotL64(aCarry, 3U)) + 15071602525497771648U) + aPhaseDOrbiterAssignSaltA[(((31U - aIndex) + 10U)) & S_SALT1]) + aNonceWordK;
            aOrbiterH = (aWandererJ + RotL64(aPrevious, 13U)) + 5780119462702672108U;
            aOrbiterK = (aWandererK + RotL64(aCross, 56U)) + 13301326224151025687U;
            //
            aOrbiterD = ((aOrbiterD + aOrbiterF) + 18129323022260575961U) + aPhaseDOrbiterUpdateSaltE[(((31U - aIndex) + 5U)) & S_SALT1];
            aOrbiterA = (aOrbiterA ^ aOrbiterD) ^ 1199228670638790709U;
            aOrbiterA = RotL64((aOrbiterA * 1780426336211781025U), 51U);
            //
            aOrbiterC = (aOrbiterC + aOrbiterA) + 1839199978088021020U;
            aOrbiterJ = ((aOrbiterJ ^ aOrbiterC) ^ 4999517042246790165U) ^ aNonceWordM;
            aOrbiterJ = RotL64((aOrbiterJ * 4585813675677234577U), 29U);
            //
            aOrbiterJ = (aOrbiterJ + aOrbiterH) + 8788607633376516299U;
            aOrbiterD = ((aOrbiterD ^ aOrbiterJ) ^ 15143903839930468749U) ^ aNonceWordJ;
            aOrbiterD = RotL64((aOrbiterD * 12735914889325422675U), 43U);
            //
            aOrbiterA = (aOrbiterA + aOrbiterK) + 16674732686428431869U;
            aOrbiterH = (aOrbiterH ^ aOrbiterA) ^ 15908873150953195581U;
            aOrbiterH = RotL64((aOrbiterH * 18049755517524334107U), 35U);
            //
            aOrbiterH = ((aOrbiterH + aOrbiterC) + 11204775359756474667U) + aNonceWordH;
            aOrbiterF = ((aOrbiterF ^ aOrbiterH) ^ 2525984309543939465U) ^ aPhaseDOrbiterUpdateSaltD[((aIndex + 19U)) & S_SALT1];
            aOrbiterF = RotL64((aOrbiterF * 3988529812023791571U), 57U);
            //
            aOrbiterK = (aOrbiterK + aOrbiterD) + 4566345170476825512U;
            aOrbiterC = (aOrbiterC ^ aOrbiterK) ^ 14876612901557406267U;
            aOrbiterC = RotL64((aOrbiterC * 9047956948845135339U), 23U);
            //
            aOrbiterF = ((aOrbiterF + aOrbiterJ) + 14926290877038883931U) + aPhaseDOrbiterUpdateSaltC[((aIndex + 24U)) & S_SALT1];
            aOrbiterK = ((aOrbiterK ^ aOrbiterF) ^ 12710203178186614846U) ^ aPhaseDOrbiterUpdateSaltA[((aIndex + 14U)) & S_SALT1];
            aOrbiterK = RotL64((aOrbiterK * 14841163494801662515U), 11U);
            //
            aIngress = RotL64(aOrbiterF, 41U) ^ aOrbiterD;
            aIngress = aIngress + (RotL64(aOrbiterC, 57U) ^ aOrbiterK);
            aIngress = aIngress + (aOrbiterA ^ RotL64(aOrbiterJ, 47U));
            aIngress = aIngress + RotL64(aOrbiterH, 10U);
            aIngress = TwistMix64::DiffuseA((aIngress + aScatter));
            //
            aWandererF = aWandererF + (((RotL64(aIngress, 37U) + RotL64(aOrbiterF, 13U)) + aOrbiterD) + aNonceWordD);
            aWandererI = aWandererI ^ ((((RotL64(aPrevious, 57U) + aOrbiterD) + RotL64(aOrbiterK, 29U)) + aNonceWordO) + aPhaseDWandererUpdateSaltA[((aIndex + 28U)) & S_SALT1]);
            aWandererG = aWandererG + ((RotL64(aScatter, 5U) + RotL64(aOrbiterC, 58U)) + aOrbiterJ);
            aWandererK = aWandererK ^ (((RotL64(aCross, 11U) + aOrbiterF) + RotL64(aOrbiterA, 47U)) + aNonceWordA);
            aWandererJ = aWandererJ + ((((RotL64(aPrevious, 29U) + RotL64(aOrbiterA, 39U)) + aOrbiterH) + RotL64(aCarry, 51U)) + aNonceWordB);
            aWandererB = aWandererB ^ (((RotL64(aIngress, 51U) + aOrbiterJ) + RotL64(aOrbiterD, 3U)) + aPhaseDWandererUpdateSaltC[((aIndex + 9U)) & S_SALT1]);
            aWandererA = aWandererA + (((RotL64(aCross, 22U) + aOrbiterF) + RotL64(aOrbiterH, 23U)) + RotL64(aCarry, 29U));
            //
            aCarry = aCarry + (RotL64(aWandererG, 38U) ^ aWandererJ);
            aCarry = aCarry + (RotL64(aWandererA, 47U) ^ aWandererK);
            aCarry = aCarry + (aWandererI ^ RotL64(aWandererB, 13U));
            aCarry = aCarry + RotL64(aWandererF, 5U);
            aCarry = aCarry + RotL64(aIngress, 29U);
            aCarry = TwistMix64::DiffuseB(aCarry);
            //
            aSnowLaneA[aIndex] = aIngress;
        }
    
        // seed_loop_d loop 2
        // ingress from: aSnowLaneA, aExpandLaneC, aExpandLaneD, aInvestLaneC
        // ingress directions: aSnowLaneA forward forced, aExpandLaneC forward forced, aExpandLaneD forward forced, aInvestLaneC forward/backward random
        // cross from: aExpandLaneA, aExpandLaneB, aInvestLaneD
        // cross directions: aExpandLaneA backward forced, aExpandLaneB backward forced, aInvestLaneD backward/forward random
        // write to: aSnowLaneB
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aSnowLaneA[((aIndex + 9467U)) & S_BLOCK1], 29U) ^ RotL64(aExpandLaneC[((aIndex + 10665U)) & S_BLOCK1], 41U));
            aIngress ^= (RotL64(aExpandLaneD[((aIndex + 7808U)) & S_BLOCK1], 52U) ^ RotL64(aInvestLaneC[((S_BLOCK1 - aIndex + 7431U)) & S_BLOCK1], 3U));
            aIngress = TwistMix64::DiffuseA(((aIngress ^ aPhaseDDomainWordIngress) ^ aNonceWordN));
            //
            aCross = (RotL64(aExpandLaneA[((S_BLOCK1 - aIndex + 9383U)) & S_BLOCK1], 53U) ^ RotL64(aExpandLaneB[((S_BLOCK1 - aIndex + 6579U)) & S_BLOCK1], 43U));
            aCross ^= RotL64(aInvestLaneD[((S_BLOCK1 - aIndex + 9518U)) & S_BLOCK1], 22U);
            aCross = TwistMix64::DiffuseB(((aCross ^ aPhaseDDomainWordCross) ^ aNonceWordJ));
            //
            aScatter = (RotL64(aPrevious, 41U) ^ RotL64(aCarry, 54U)) ^ (RotL64(aIngress, 19U) + RotL64(aCross, 3U));
            aScatter = TwistMix64::DiffuseA(((aScatter ^ aPhaseDDomainWordScatter) ^ aNonceWordE));
            //
            aOrbiterD = (aWandererB + RotL64(aIngress, 29U)) + 1142447269198373880U;
            aOrbiterI = ((aWandererF + RotL64(aCross, 13U)) + 10581460640040336191U) + aNonceWordK;
            aOrbiterC = ((aWandererH + RotL64(aScatter, 41U)) + 14703062773878202900U) + aPhaseDOrbiterAssignSaltF[((aIndex + 23U)) & S_SALT1];
            aOrbiterH = ((aWandererJ + RotL64(aPrevious, 60U)) + RotL64(aCarry, 39U)) + 15737525756286914746U;
            aOrbiterE = ((aWandererE + RotL64(aCross, 51U)) + RotL64(aCarry, 19U)) + 16178774478273186999U;
            aOrbiterJ = ((((aWandererD + RotL64(aIngress, 35U)) + RotL64(aCarry, 57U)) + 2514897053906809160U) + aPhaseDOrbiterAssignSaltD[(((31U - aIndex) + 10U)) & S_SALT1]) + aNonceWordH;
            aOrbiterG = ((aWandererG + RotL64(aPrevious, 23U)) + 13702496607592508464U) + aNonceWordI;
            //
            aOrbiterD = (((aOrbiterD + aOrbiterI) + 18030885275418337965U) + aPhaseDOrbiterUpdateSaltF[(((31U - aIndex) + 14U)) & S_SALT1]) + aNonceWordL;
            aOrbiterC = ((aOrbiterC ^ aOrbiterD) ^ 5241783876161655984U) ^ aPhaseDOrbiterUpdateSaltE[((aIndex + 17U)) & S_SALT1];
            aOrbiterC = RotL64((aOrbiterC * 10970981186787227937U), 21U);
            //
            aOrbiterH = ((aOrbiterH + aOrbiterE) + 2807052676283587925U) + aNonceWordE;
            aOrbiterI = ((aOrbiterI ^ aOrbiterH) ^ 8022804576763271327U) ^ aPhaseDOrbiterUpdateSaltD[((aIndex + 20U)) & S_SALT1];
            aOrbiterI = RotL64((aOrbiterI * 11727096043219370577U), 53U);
            //
            aOrbiterI = (aOrbiterI + aOrbiterJ) + 15597099852232205860U;
            aOrbiterG = (aOrbiterG ^ aOrbiterI) ^ 1538435607932096400U;
            aOrbiterG = RotL64((aOrbiterG * 7900752511710516981U), 13U);
            //
            aOrbiterG = (aOrbiterG + aOrbiterH) + 11147868774413615365U;
            aOrbiterD = ((aOrbiterD ^ aOrbiterG) ^ 9325213746830411568U) ^ aPhaseDOrbiterUpdateSaltB[(((31U - aIndex) + 11U)) & S_SALT1];
            aOrbiterD = RotL64((aOrbiterD * 561819005818948769U), 5U);
            //
            aOrbiterC = (aOrbiterC + aOrbiterG) + 13792300423550555634U;
            aOrbiterE = (aOrbiterE ^ aOrbiterC) ^ 3134856508983945719U;
            aOrbiterE = RotL64((aOrbiterE * 4271845067763664863U), 27U);
            //
            aOrbiterJ = (aOrbiterJ + aOrbiterC) + 8654966018053784882U;
            aOrbiterH = (aOrbiterH ^ aOrbiterJ) ^ 8937113935476779267U;
            aOrbiterH = RotL64((aOrbiterH * 7386875687217705855U), 37U);
            //
            aOrbiterE = (aOrbiterE + aOrbiterD) + 4135676350355234788U;
            aOrbiterJ = (aOrbiterJ ^ aOrbiterE) ^ 11407912615743682678U;
            aOrbiterJ = RotL64((aOrbiterJ * 2773506587480714695U), 47U);
            //
            aIngress = aOrbiterJ ^ RotL64(aOrbiterH, 57U);
            aIngress = aIngress + (aOrbiterE ^ RotL64(aOrbiterC, 41U));
            aIngress = aIngress + (aOrbiterD ^ RotL64(aOrbiterG, 48U));
            aIngress = aIngress + RotL64(aOrbiterI, 3U);
            aIngress = TwistMix64::DiffuseA((aIngress + aScatter));
            //
            aWandererF = aWandererF + (((RotL64(aCross, 5U) + aOrbiterI) + RotL64(aOrbiterD, 35U)) + aNonceWordC);
            aWandererE = aWandererE ^ (((RotL64(aScatter, 43U) + aOrbiterH) + RotL64(aOrbiterI, 41U)) + aPhaseDWandererUpdateSaltD[((aIndex + 7U)) & S_SALT1]);
            aWandererB = aWandererB + (((RotL64(aPrevious, 21U) + aOrbiterI) + RotL64(aOrbiterE, 29U)) + RotL64(aCarry, 27U));
            aWandererD = aWandererD ^ ((((RotL64(aIngress, 29U) + RotL64(aOrbiterJ, 58U)) + aOrbiterC) + aNonceWordG) + aPhaseDWandererUpdateSaltB[(((31U - aIndex) + 3U)) & S_SALT1]);
            aWandererH = aWandererH + (((RotL64(aPrevious, 35U) + aOrbiterH) + RotL64(aOrbiterJ, 47U)) + aNonceWordM);
            aWandererG = aWandererG ^ (((RotL64(aCross, 50U) + aOrbiterI) + RotL64(aOrbiterG, 5U)) + aNonceWordD);
            aWandererJ = aWandererJ + (((RotL64(aIngress, 13U) + RotL64(aOrbiterC, 13U)) + aOrbiterG) + RotL64(aCarry, 43U));
            //
            aCarry = aCarry + (aWandererF ^ RotL64(aWandererB, 18U));
            aCarry = aCarry + (RotL64(aWandererD, 29U) ^ aWandererH);
            aCarry = aCarry + (RotL64(aWandererG, 11U) ^ aWandererJ);
            aCarry = aCarry + RotL64(aWandererE, 57U);
            aCarry = aCarry + RotL64(aIngress, 35U);
            aCarry = TwistMix64::DiffuseB(aCarry);
            //
            aSnowLaneB[S_BLOCK1 - aIndex] = aIngress;
        }
    
        // seed_loop_d loop 3
        // ingress from: aSnowLaneB, aExpandLaneA, aFireLaneA
        // ingress directions: aSnowLaneB forward forced, aExpandLaneA forward forced, aFireLaneA forward/backward random
        // cross from: aSnowLaneA, aExpandLaneC
        // cross directions: aSnowLaneA backward forced, aExpandLaneC backward/forward random
        // write to: aInvestLaneA
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aSnowLaneB[((aIndex + 11012U)) & S_BLOCK1], 23U) ^ RotL64(aExpandLaneA[((aIndex + 16309U)) & S_BLOCK1], 13U));
            aIngress ^= RotL64(aFireLaneA[((S_BLOCK1 - aIndex + 15485U)) & S_BLOCK1], 54U);
            aIngress = TwistMix64::DiffuseC(((aIngress ^ aPhaseDDomainWordIngress) ^ aNonceWordP));
            //
            aCross = RotL64(aSnowLaneA[((S_BLOCK1 - aIndex + 13295U)) & S_BLOCK1], 26U) ^ RotL64(aExpandLaneC[((aIndex + 14704U)) & S_BLOCK1], 47U);
            aCross = TwistMix64::DiffuseC(((aCross ^ aPhaseDDomainWordCross) ^ aNonceWordO));
            //
            aScatter = (RotL64(aCarry, 24U) + RotL64(aIngress, 39U)) + (RotL64(aPrevious, 11U) ^ RotL64(aCross, 57U));
            aScatter = TwistMix64::DiffuseA(((aScatter ^ aPhaseDDomainWordScatter) ^ aNonceWordF));
            //
            aOrbiterF = ((aWandererB + RotL64(aIngress, 39U)) + 3650233661228036955U) + aNonceWordH;
            aOrbiterE = ((((aWandererJ + RotL64(aCross, 30U)) + RotL64(aCarry, 19U)) + 11607036400067735729U) + aPhaseDOrbiterAssignSaltB[((aIndex + 3U)) & S_SALT1]) + aNonceWordD;
            aOrbiterC = ((aWandererH + RotL64(aPrevious, 19U)) + 3899614406903883035U) + aPhaseDOrbiterAssignSaltC[(((31U - aIndex) + 5U)) & S_SALT1];
            aOrbiterH = ((aWandererA + RotL64(aScatter, 57U)) + RotL64(aCarry, 5U)) + 8159156925629965143U;
            aOrbiterJ = (((aWandererC + RotL64(aPrevious, 11U)) + RotL64(aCarry, 57U)) + 7148903913967261270U) + aNonceWordL;
            aOrbiterK = (aWandererG + RotL64(aIngress, 5U)) + 9161665622287517848U;
            aOrbiterD = (aWandererD + RotL64(aCross, 51U)) + 2981535013474059469U;
            //
            aOrbiterF = (aOrbiterF + aOrbiterE) + 15812469008200319549U;
            aOrbiterC = (aOrbiterC ^ aOrbiterF) ^ 14687469489893270300U;
            aOrbiterC = RotL64((aOrbiterC * 14142363399696670451U), 51U);
            //
            aOrbiterH = (aOrbiterH + aOrbiterJ) + 6025209349511417063U;
            aOrbiterK = (aOrbiterK ^ aOrbiterH) ^ 12964750392311112676U;
            aOrbiterK = RotL64((aOrbiterK * 12955480283032701843U), 21U);
            //
            aOrbiterE = (((aOrbiterE + aOrbiterC) + 6572355895765394340U) + aPhaseDOrbiterUpdateSaltE[((aIndex + 7U)) & S_SALT1]) + aNonceWordB;
            aOrbiterH = ((aOrbiterH ^ aOrbiterE) ^ 3542300121890027981U) ^ aPhaseDOrbiterUpdateSaltF[(((31U - aIndex) + 9U)) & S_SALT1];
            aOrbiterH = RotL64((aOrbiterH * 11201491178181273935U), 57U);
            //
            aOrbiterD = ((aOrbiterD + aOrbiterF) + 6477175684045398359U) + aPhaseDOrbiterUpdateSaltA[((aIndex + 15U)) & S_SALT1];
            aOrbiterE = (aOrbiterE ^ aOrbiterD) ^ 1081388388827929314U;
            aOrbiterE = RotL64((aOrbiterE * 8752188637514143529U), 37U);
            //
            aOrbiterC = (aOrbiterC + aOrbiterH) + 13754328481584620771U;
            aOrbiterJ = ((aOrbiterJ ^ aOrbiterC) ^ 3684673342659575917U) ^ aNonceWordJ;
            aOrbiterJ = RotL64((aOrbiterJ * 6139923312873039143U), 13U);
            //
            aOrbiterK = (aOrbiterK + aOrbiterD) + 6542045150319909445U;
            aOrbiterF = (aOrbiterF ^ aOrbiterK) ^ 5352102692424060388U;
            aOrbiterF = RotL64((aOrbiterF * 7385758355501860261U), 27U);
            //
            aOrbiterJ = (aOrbiterJ + aOrbiterK) + 9110100774657340354U;
            aOrbiterD = ((aOrbiterD ^ aOrbiterJ) ^ 2813273684436269057U) ^ aPhaseDOrbiterUpdateSaltD[((aIndex + 28U)) & S_SALT1];
            aOrbiterD = RotL64((aOrbiterD * 10468759062594022273U), 5U);
            //
            aIngress = aOrbiterF ^ RotL64(aOrbiterK, 57U);
            aIngress = aIngress + (aOrbiterC ^ RotL64(aOrbiterD, 11U));
            aIngress = aIngress + (RotL64(aOrbiterH, 40U) ^ aOrbiterE);
            aIngress = aIngress + RotL64(aOrbiterJ, 27U);
            aIngress = TwistMix64::DiffuseA((aIngress + aScatter));
            //
            aWandererD = aWandererD ^ ((RotL64(aScatter, 57U) + RotL64(aOrbiterE, 41U)) + aOrbiterH);
            aWandererC = aWandererC + (((RotL64(aIngress, 41U) + RotL64(aOrbiterK, 47U)) + aOrbiterH) + aNonceWordE);
            aWandererB = aWandererB ^ ((((RotL64(aCross, 50U) + aOrbiterF) + RotL64(aOrbiterK, 35U)) + aNonceWordG) + aPhaseDWandererUpdateSaltF[(((31U - aIndex) + 6U)) & S_SALT1]);
            aWandererG = aWandererG + ((((RotL64(aPrevious, 35U) + aOrbiterJ) + RotL64(aOrbiterK, 5U)) + RotL64(aCarry, 5U)) + aPhaseDWandererUpdateSaltE[((aIndex + 18U)) & S_SALT1]);
            aWandererJ = aWandererJ ^ (((RotL64(aCross, 5U) + RotL64(aOrbiterC, 12U)) + aOrbiterF) + aNonceWordI);
            aWandererH = aWandererH + (((RotL64(aIngress, 21U) + RotL64(aOrbiterE, 27U)) + aOrbiterD) + RotL64(aCarry, 57U));
            aWandererA = aWandererA ^ ((RotL64(aPrevious, 29U) + RotL64(aOrbiterD, 57U)) + aOrbiterF);
            //
            aCarry = aCarry + (aWandererH ^ RotL64(aWandererJ, 3U));
            aCarry = aCarry + (RotL64(aWandererA, 23U) ^ aWandererC);
            aCarry = aCarry + (aWandererD ^ RotL64(aWandererG, 43U));
            aCarry = aCarry + RotL64(aWandererB, 18U);
            aCarry = aCarry + RotL64(aIngress, 35U);
            aCarry = TwistMix64::DiffuseB(aCarry);
            //
            aInvestLaneA[aIndex] = aIngress;
        }
    
        // seed_loop_d loop 4
        // ingress from: aInvestLaneA, aSnowLaneA, aFireLaneB
        // ingress directions: aInvestLaneA forward forced, aSnowLaneA forward forced, aFireLaneB forward/backward random
        // cross from: aSnowLaneB, aExpandLaneD
        // cross directions: aSnowLaneB backward forced, aExpandLaneD backward/forward random
        // write to: aInvestLaneB
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aInvestLaneA[((aIndex + 21128U)) & S_BLOCK1], 39U) ^ RotL64(aSnowLaneA[((aIndex + 17360U)) & S_BLOCK1], 23U));
            aIngress ^= RotL64(aFireLaneB[((S_BLOCK1 - aIndex + 17010U)) & S_BLOCK1], 57U);
            aIngress = TwistMix64::DiffuseA(((aIngress ^ aPhaseDDomainWordIngress) ^ aNonceWordC));
            //
            aCross = RotL64(aSnowLaneB[((S_BLOCK1 - aIndex + 16979U)) & S_BLOCK1], 54U) ^ RotL64(aExpandLaneD[((S_BLOCK1 - aIndex + 21598U)) & S_BLOCK1], 5U);
            aCross = TwistMix64::DiffuseB(((aCross ^ aPhaseDDomainWordCross) ^ aNonceWordP));
            //
            aScatter = (RotL64(aIngress, 5U) + RotL64(aCross, 19U)) ^ (RotL64(aCarry, 36U) ^ RotL64(aPrevious, 53U));
            aScatter = TwistMix64::DiffuseC(((aScatter ^ aPhaseDDomainWordScatter) ^ aNonceWordI));
            //
            aOrbiterD = (((aWandererD + RotL64(aPrevious, 19U)) + 8767379393098711499U) + aPhaseDOrbiterAssignSaltE[(((31U - aIndex) + 23U)) & S_SALT1]) + aNonceWordN;
            aOrbiterC = ((aWandererE + RotL64(aIngress, 51U)) + 7168159491580816433U) + aNonceWordO;
            aOrbiterF = ((aWandererC + RotL64(aCross, 29U)) + RotL64(aCarry, 13U)) + 9879279829061883406U;
            aOrbiterI = ((aWandererI + RotL64(aScatter, 57U)) + 10537167136053399303U) + aNonceWordG;
            aOrbiterJ = ((aWandererB + RotL64(aCross, 11U)) + 2839070018069188936U) + aNonceWordI;
            aOrbiterK = ((aWandererH + RotL64(aIngress, 44U)) + RotL64(aCarry, 53U)) + 13844278063968429732U;
            aOrbiterA = (((aWandererG + RotL64(aPrevious, 37U)) + RotL64(aCarry, 39U)) + 11278946626186474646U) + aPhaseDOrbiterAssignSaltA[((aIndex + 13U)) & S_SALT1];
            //
            aOrbiterD = (aOrbiterD + aOrbiterC) + 11798425216660557799U;
            aOrbiterF = (aOrbiterF ^ aOrbiterD) ^ 7618446090703335192U;
            aOrbiterF = RotL64((aOrbiterF * 7168757300685156779U), 3U);
            //
            aOrbiterI = (aOrbiterI + aOrbiterJ) + 695423597006983660U;
            aOrbiterK = (aOrbiterK ^ aOrbiterI) ^ 14344728202803488813U;
            aOrbiterK = RotL64((aOrbiterK * 5168825904902285909U), 11U);
            //
            aOrbiterA = ((aOrbiterA + aOrbiterI) + 11656100506575697086U) + aPhaseDOrbiterUpdateSaltB[((aIndex + 25U)) & S_SALT1];
            aOrbiterJ = ((aOrbiterJ ^ aOrbiterA) ^ 10384358779985773937U) ^ aPhaseDOrbiterUpdateSaltF[((aIndex + 4U)) & S_SALT1];
            aOrbiterJ = RotL64((aOrbiterJ * 247494692039140973U), 47U);
            //
            aOrbiterK = (aOrbiterK + aOrbiterD) + 17585001605131977341U;
            aOrbiterC = ((aOrbiterC ^ aOrbiterK) ^ 9964478171465522911U) ^ aNonceWordH;
            aOrbiterC = RotL64((aOrbiterC * 13484044854790175315U), 19U);
            //
            aOrbiterF = ((aOrbiterF + aOrbiterA) + 2710943171829692624U) + aPhaseDOrbiterUpdateSaltA[(((31U - aIndex) + 19U)) & S_SALT1];
            aOrbiterI = (aOrbiterI ^ aOrbiterF) ^ 17809072853457153057U;
            aOrbiterI = RotL64((aOrbiterI * 16341884203303271365U), 35U);
            //
            aOrbiterC = ((aOrbiterC + aOrbiterF) + 12814092033910687774U) + aNonceWordA;
            aOrbiterA = (aOrbiterA ^ aOrbiterC) ^ 1743186323268668740U;
            aOrbiterA = RotL64((aOrbiterA * 11150822630624332557U), 53U);
            //
            aOrbiterJ = ((aOrbiterJ + aOrbiterK) + 10750472346626754704U) + aNonceWordE;
            aOrbiterD = (((aOrbiterD ^ aOrbiterJ) ^ 15925901217078035356U) ^ aPhaseDOrbiterUpdateSaltC[(((31U - aIndex) + 17U)) & S_SALT1]) ^ aNonceWordF;
            aOrbiterD = RotL64((aOrbiterD * 9276504171291801637U), 29U);
            //
            aIngress = aOrbiterK ^ RotL64(aOrbiterA, 43U);
            aIngress = aIngress + (RotL64(aOrbiterI, 53U) ^ aOrbiterF);
            aIngress = aIngress + (aOrbiterC ^ RotL64(aOrbiterD, 13U));
            aIngress = aIngress + RotL64(aOrbiterJ, 29U);
            aIngress = TwistMix64::DiffuseA((aIngress + aScatter));
            //
            aWandererH = aWandererH + ((RotL64(aIngress, 21U) + aOrbiterC) + RotL64(aOrbiterA, 47U));
            aWandererD = aWandererD ^ ((RotL64(aScatter, 11U) + aOrbiterA) + RotL64(aOrbiterF, 21U));
            aWandererC = aWandererC + ((((RotL64(aPrevious, 51U) + aOrbiterC) + RotL64(aOrbiterD, 29U)) + RotL64(aCarry, 41U)) + aNonceWordL);
            aWandererI = aWandererI ^ ((RotL64(aCross, 27U) + RotL64(aOrbiterF, 14U)) + aOrbiterD);
            aWandererE = aWandererE + (((((RotL64(aScatter, 43U) + RotL64(aOrbiterK, 3U)) + aOrbiterJ) + RotL64(aCarry, 5U)) + aNonceWordK) + aPhaseDWandererUpdateSaltC[((aIndex + 18U)) & S_SALT1]);
            aWandererG = aWandererG ^ ((RotL64(aCross, 57U) + aOrbiterA) + RotL64(aOrbiterI, 57U));
            aWandererB = aWandererB + ((((RotL64(aPrevious, 4U) + RotL64(aOrbiterD, 35U)) + aOrbiterK) + aNonceWordB) + aPhaseDWandererUpdateSaltA[((aIndex + 16U)) & S_SALT1]);
            //
            aCarry = aCarry + (RotL64(aWandererE, 60U) ^ aWandererB);
            aCarry = aCarry + (RotL64(aWandererI, 13U) ^ aWandererG);
            aCarry = aCarry + (aWandererC ^ RotL64(aWandererH, 27U));
            aCarry = aCarry + RotL64(aWandererD, 5U);
            aCarry = aCarry + RotL64(aIngress, 42U);
            aCarry = TwistMix64::DiffuseC(aCarry);
            //
            aInvestLaneB[S_BLOCK1 - aIndex] = aIngress;
        }
    
        // seed_loop_d loop 5
        // ingress from: aInvestLaneB, aSnowLaneB, aFireLaneC
        // ingress directions: aInvestLaneB forward forced, aSnowLaneB forward forced, aFireLaneC forward/backward random
        // cross from: aInvestLaneA, aSnowLaneA
        // cross directions: aInvestLaneA backward forced, aSnowLaneA backward/forward random
        // write to: aInvestLaneC
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aInvestLaneB[((aIndex + 27071U)) & S_BLOCK1], 57U) ^ RotL64(aSnowLaneB[((aIndex + 22303U)) & S_BLOCK1], 14U));
            aIngress ^= RotL64(aFireLaneC[((S_BLOCK1 - aIndex + 26739U)) & S_BLOCK1], 41U);
            aIngress = TwistMix64::DiffuseC(((aIngress ^ aPhaseDDomainWordIngress) ^ aNonceWordO));
            //
            aCross = RotL64(aInvestLaneA[((S_BLOCK1 - aIndex + 22102U)) & S_BLOCK1], 48U) ^ RotL64(aSnowLaneA[((aIndex + 26793U)) & S_BLOCK1], 13U);
            aCross = TwistMix64::DiffuseC(((aCross ^ aPhaseDDomainWordCross) ^ aNonceWordF));
            //
            aScatter = (RotL64(aCross, 27U) ^ RotL64(aPrevious, 53U)) + (RotL64(aCarry, 4U) ^ RotL64(aIngress, 39U));
            aScatter = TwistMix64::DiffuseB(((aScatter ^ aPhaseDDomainWordScatter) ^ aNonceWordD));
            //
            aOrbiterA = ((((aWandererH + RotL64(aScatter, 39U)) + RotL64(aCarry, 11U)) + 2101601659597850213U) + aPhaseDOrbiterAssignSaltD[(((31U - aIndex) + 4U)) & S_SALT1]) + aNonceWordP;
            aOrbiterB = ((aWandererG + RotL64(aCross, 28U)) + 2759794072560720121U) + aNonceWordI;
            aOrbiterG = ((aWandererD + RotL64(aIngress, 11U)) + RotL64(aCarry, 53U)) + 9443562552411269339U;
            aOrbiterK = ((aWandererI + RotL64(aPrevious, 53U)) + RotL64(aCarry, 35U)) + 10801360546699857975U;
            aOrbiterH = ((aWandererB + RotL64(aCross, 5U)) + 8020716394829332019U) + aPhaseDOrbiterAssignSaltF[(((31U - aIndex) + 24U)) & S_SALT1];
            aOrbiterD = (aWandererE + RotL64(aIngress, 47U)) + 1021894212367773801U;
            aOrbiterJ = (aWandererA + RotL64(aPrevious, 19U)) + 13346855534622490176U;
            //
            aOrbiterA = (aOrbiterA + aOrbiterB) + 16359309548462953836U;
            aOrbiterG = (aOrbiterG ^ aOrbiterA) ^ 12642446944680783519U;
            aOrbiterG = RotL64((aOrbiterG * 12197935153255283321U), 35U);
            //
            aOrbiterK = (aOrbiterK + aOrbiterG) + 8197424982767553380U;
            aOrbiterH = (((aOrbiterH ^ aOrbiterK) ^ 14346334610901859094U) ^ aPhaseDOrbiterUpdateSaltD[((aIndex + 28U)) & S_SALT1]) ^ aNonceWordM;
            aOrbiterH = RotL64((aOrbiterH * 16982899923227935679U), 43U);
            //
            aOrbiterB = (aOrbiterB + aOrbiterK) + 14171304260534233539U;
            aOrbiterD = ((aOrbiterD ^ aOrbiterB) ^ 334531601308283605U) ^ aNonceWordC;
            aOrbiterD = RotL64((aOrbiterD * 5012968232749075075U), 11U);
            //
            aOrbiterG = ((aOrbiterG + aOrbiterD) + 10707856298471572695U) + aPhaseDOrbiterUpdateSaltB[((aIndex + 23U)) & S_SALT1];
            aOrbiterJ = ((aOrbiterJ ^ aOrbiterG) ^ 18364775750091914766U) ^ aNonceWordG;
            aOrbiterJ = RotL64((aOrbiterJ * 15735143943129143265U), 3U);
            //
            aOrbiterD = ((aOrbiterD + aOrbiterH) + 8531394793118363836U) + aNonceWordK;
            aOrbiterA = (aOrbiterA ^ aOrbiterD) ^ 15352876929406908882U;
            aOrbiterA = RotL64((aOrbiterA * 475199047053777179U), 51U);
            //
            aOrbiterH = (aOrbiterH + aOrbiterJ) + 567682016232278157U;
            aOrbiterB = (aOrbiterB ^ aOrbiterH) ^ 2068146551757663119U;
            aOrbiterB = RotL64((aOrbiterB * 1557877740957797555U), 29U);
            //
            aOrbiterJ = ((aOrbiterJ + aOrbiterA) + 7776122587613256525U) + aPhaseDOrbiterUpdateSaltE[((aIndex + 3U)) & S_SALT1];
            aOrbiterK = ((aOrbiterK ^ aOrbiterJ) ^ 16430938890724272256U) ^ aPhaseDOrbiterUpdateSaltA[((aIndex + 16U)) & S_SALT1];
            aOrbiterK = RotL64((aOrbiterK * 4540270493783593257U), 19U);
            //
            aIngress = aOrbiterK ^ RotL64(aOrbiterA, 39U);
            aIngress = aIngress + (aOrbiterH ^ RotL64(aOrbiterB, 3U));
            aIngress = aIngress + (RotL64(aOrbiterG, 51U) ^ aOrbiterJ);
            aIngress = aIngress + RotL64(aOrbiterD, 27U);
            aIngress = TwistMix64::DiffuseA((aIngress + aScatter));
            //
            aWandererE = aWandererE ^ ((RotL64(aCross, 35U) + aOrbiterB) + RotL64(aOrbiterD, 11U));
            aWandererH = aWandererH + ((((RotL64(aIngress, 57U) + RotL64(aOrbiterH, 35U)) + aOrbiterJ) + RotL64(aCarry, 57U)) + aPhaseDWandererUpdateSaltB[(((31U - aIndex) + 5U)) & S_SALT1]);
            aWandererA = aWandererA ^ ((RotL64(aPrevious, 21U) + RotL64(aOrbiterK, 5U)) + aOrbiterJ);
            aWandererB = aWandererB + ((((RotL64(aScatter, 4U) + RotL64(aOrbiterA, 51U)) + aOrbiterJ) + RotL64(aCarry, 39U)) + aPhaseDWandererUpdateSaltD[(((31U - aIndex) + 18U)) & S_SALT1]);
            aWandererI = aWandererI ^ (((RotL64(aCross, 13U) + aOrbiterB) + RotL64(aOrbiterH, 27U)) + aNonceWordD);
            aWandererG = aWandererG + ((RotL64(aIngress, 51U) + aOrbiterK) + RotL64(aOrbiterG, 60U));
            aWandererD = aWandererD ^ (((RotL64(aPrevious, 41U) + aOrbiterJ) + RotL64(aOrbiterG, 19U)) + aNonceWordL);
            //
            aCarry = aCarry + (RotL64(aWandererD, 47U) ^ aWandererI);
            aCarry = aCarry + (RotL64(aWandererA, 51U) ^ aWandererG);
            aCarry = aCarry + (aWandererE ^ RotL64(aWandererB, 23U));
            aCarry = aCarry + RotL64(aWandererH, 60U);
            aCarry = aCarry + RotL64(aIngress, 39U);
            aCarry = TwistMix64::DiffuseB(aCarry);
            //
            aInvestLaneC[aIndex] = aIngress;
        }
    
        // seed_loop_d loop 6
        // ingress from: aInvestLaneC, aInvestLaneA, aFireLaneD
        // ingress directions: aInvestLaneC forward forced, aInvestLaneA forward forced, aFireLaneD forward/backward random
        // cross from: aInvestLaneB, aExpandLaneB
        // cross directions: aInvestLaneB backward forced, aExpandLaneB backward/forward random
        // write to: aInvestLaneD
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aInvestLaneC[((aIndex + 31410U)) & S_BLOCK1], 47U) ^ RotL64(aInvestLaneA[((aIndex + 28664U)) & S_BLOCK1], 11U));
            aIngress ^= RotL64(aFireLaneD[((S_BLOCK1 - aIndex + 30197U)) & S_BLOCK1], 29U);
            aIngress = TwistMix64::DiffuseB(((aIngress ^ aPhaseDDomainWordIngress) ^ aNonceWordN));
            //
            aCross = RotL64(aInvestLaneB[((S_BLOCK1 - aIndex + 27764U)) & S_BLOCK1], 10U) ^ RotL64(aExpandLaneB[((S_BLOCK1 - aIndex + 31097U)) & S_BLOCK1], 43U);
            aCross = TwistMix64::DiffuseA(((aCross ^ aPhaseDDomainWordCross) ^ aNonceWordO));
            //
            aScatter = (RotL64(aPrevious, 18U) ^ RotL64(aCarry, 53U)) ^ (RotL64(aIngress, 5U) + RotL64(aCross, 37U));
            aScatter = TwistMix64::DiffuseB(((aScatter ^ aPhaseDDomainWordScatter) ^ aNonceWordH));
            //
            aOrbiterF = (((aWandererC + RotL64(aScatter, 5U)) + RotL64(aCarry, 37U)) + 12692813903177772178U) + aPhaseDOrbiterAssignSaltB[((aIndex + 21U)) & S_SALT1];
            aOrbiterE = (aWandererH + RotL64(aPrevious, 21U)) + 7112496446691277899U;
            aOrbiterI = (aWandererK + RotL64(aCross, 43U)) + 2112247138290568813U;
            aOrbiterC = ((aWandererA + RotL64(aIngress, 14U)) + RotL64(aCarry, 11U)) + 3699421080882855947U;
            aOrbiterK = ((aWandererB + RotL64(aPrevious, 37U)) + 13761832028354380922U) + aNonceWordE;
            aOrbiterG = (((aWandererD + RotL64(aIngress, 57U)) + 9243822514887600214U) + aPhaseDOrbiterAssignSaltC[((aIndex + 5U)) & S_SALT1]) + aNonceWordH;
            aOrbiterD = (((aWandererE + RotL64(aCross, 51U)) + RotL64(aCarry, 23U)) + 6863833516853046129U) + aNonceWordF;
            //
            aOrbiterF = (((aOrbiterF + aOrbiterE) + 8863897995943098018U) + aPhaseDOrbiterUpdateSaltC[((aIndex + 26U)) & S_SALT1]) + aNonceWordL;
            aOrbiterI = ((aOrbiterI ^ aOrbiterF) ^ 13346785686701467520U) ^ aNonceWordG;
            aOrbiterI = RotL64((aOrbiterI * 18074843497158380703U), 21U);
            //
            aOrbiterE = ((aOrbiterE + aOrbiterC) + 15309543066305531619U) + aNonceWordK;
            aOrbiterK = ((aOrbiterK ^ aOrbiterE) ^ 17515530938817919111U) ^ aPhaseDOrbiterUpdateSaltF[(((31U - aIndex) + 6U)) & S_SALT1];
            aOrbiterK = RotL64((aOrbiterK * 16625193986319048245U), 57U);
            //
            aOrbiterC = (aOrbiterC + aOrbiterG) + 760493237816424254U;
            aOrbiterF = (aOrbiterF ^ aOrbiterC) ^ 7282586354117620860U;
            aOrbiterF = RotL64((aOrbiterF * 2327153408185290635U), 29U);
            //
            aOrbiterK = ((aOrbiterK + aOrbiterF) + 4129706068526969105U) + aPhaseDOrbiterUpdateSaltB[(((31U - aIndex) + 29U)) & S_SALT1];
            aOrbiterD = ((aOrbiterD ^ aOrbiterK) ^ 7020175432730888755U) ^ aNonceWordP;
            aOrbiterD = RotL64((aOrbiterD * 10095158356907592239U), 51U);
            //
            aOrbiterI = (aOrbiterI + aOrbiterK) + 9102258982216515596U;
            aOrbiterG = (aOrbiterG ^ aOrbiterI) ^ 10822031305361453690U;
            aOrbiterG = RotL64((aOrbiterG * 2036205056490578491U), 43U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterI) + 12571477440964330246U;
            aOrbiterC = (aOrbiterC ^ aOrbiterD) ^ 8436347026653095199U;
            aOrbiterC = RotL64((aOrbiterC * 17930734781213681573U), 35U);
            //
            aOrbiterG = ((aOrbiterG + aOrbiterD) + 14214789872073941940U) + aPhaseDOrbiterUpdateSaltD[((aIndex + 23U)) & S_SALT1];
            aOrbiterE = (aOrbiterE ^ aOrbiterG) ^ 12915911919403385001U;
            aOrbiterE = RotL64((aOrbiterE * 13161681603528031511U), 5U);
            //
            aIngress = aOrbiterF ^ RotL64(aOrbiterK, 5U);
            aIngress = aIngress + (RotL64(aOrbiterG, 56U) ^ aOrbiterC);
            aIngress = aIngress + (aOrbiterI ^ RotL64(aOrbiterE, 21U));
            aIngress = aIngress + RotL64(aOrbiterD, 37U);
            aIngress = TwistMix64::DiffuseA((aIngress + aScatter));
            //
            aWandererK = aWandererK ^ ((RotL64(aPrevious, 39U) + RotL64(aOrbiterF, 11U)) + aOrbiterK);
            aWandererE = aWandererE + (((((RotL64(aIngress, 47U) + RotL64(aOrbiterE, 51U)) + aOrbiterC) + RotL64(aCarry, 29U)) + aNonceWordA) + aPhaseDWandererUpdateSaltF[(((31U - aIndex) + 11U)) & S_SALT1]);
            aWandererD = aWandererD ^ ((RotL64(aCross, 3U) + RotL64(aOrbiterD, 22U)) + aOrbiterK);
            aWandererH = aWandererH + (((RotL64(aScatter, 21U) + RotL64(aOrbiterF, 35U)) + aOrbiterC) + aPhaseDWandererUpdateSaltE[(((31U - aIndex) + 19U)) & S_SALT1]);
            aWandererA = aWandererA ^ (((RotL64(aIngress, 53U) + RotL64(aOrbiterI, 57U)) + aOrbiterD) + aNonceWordJ);
            aWandererC = aWandererC + ((((RotL64(aScatter, 11U) + aOrbiterG) + RotL64(aOrbiterC, 3U)) + RotL64(aCarry, 3U)) + aNonceWordC);
            aWandererB = aWandererB ^ ((RotL64(aPrevious, 60U) + aOrbiterD) + RotL64(aOrbiterC, 43U));
            //
            aCarry = aCarry + (aWandererK ^ RotL64(aWandererB, 18U));
            aCarry = aCarry + (RotL64(aWandererA, 11U) ^ aWandererH);
            aCarry = aCarry + (RotL64(aWandererD, 35U) ^ aWandererE);
            aCarry = aCarry + RotL64(aWandererC, 43U);
            aCarry = aCarry + RotL64(aIngress, 58U);
            aCarry = TwistMix64::DiffuseB(aCarry);
            //
            aInvestLaneD[S_BLOCK1 - aIndex] = aIngress;
        }
    }
    // GSeedRunSeed_D seed_loop_d (end)
    *pPrevious = aPrevious;
    *pIngress = aIngress;
    *pCarry = aCarry;
    *pWandererA = aWandererA;
    *pWandererB = aWandererB;
    *pWandererC = aWandererC;
    *pWandererD = aWandererD;
    *pWandererE = aWandererE;
    *pWandererF = aWandererF;
    *pWandererG = aWandererG;
    *pWandererH = aWandererH;
    *pWandererI = aWandererI;
    *pWandererJ = aWandererJ;
    *pWandererK = aWandererK;
}

void TwistExpander_Exercea_Arx::Seed_E(TwistWorkSpace *pWorkSpace,
                     std::uint64_t pNonce,
                     std::uint64_t *pPrevious,
                     std::uint64_t *pIngress,
                     std::uint64_t *pCarry,
                     std::uint64_t *pWandererA,
                     std::uint64_t *pWandererB,
                     std::uint64_t *pWandererC,
                     std::uint64_t *pWandererD,
                     std::uint64_t *pWandererE,
                     std::uint64_t *pWandererF,
                     std::uint64_t *pWandererG,
                     std::uint64_t *pWandererH,
                     std::uint64_t *pWandererI,
                     std::uint64_t *pWandererJ,
                     std::uint64_t *pWandererK) {
    [[maybe_unused]] std::uint8_t *aWorkLaneA = pWorkSpace->mWorkLaneA;
    [[maybe_unused]] std::uint8_t *aWorkLaneB = pWorkSpace->mWorkLaneB;
    [[maybe_unused]] std::uint8_t *aWorkLaneC = pWorkSpace->mWorkLaneC;
    [[maybe_unused]] std::uint8_t *aWorkLaneD = pWorkSpace->mWorkLaneD;
    [[maybe_unused]] std::uint8_t *aOperationLaneA = pWorkSpace->mOperationLaneA;
    [[maybe_unused]] std::uint8_t *aOperationLaneB = pWorkSpace->mOperationLaneB;
    [[maybe_unused]] std::uint8_t *aOperationLaneC = pWorkSpace->mOperationLaneC;
    [[maybe_unused]] std::uint8_t *aOperationLaneD = pWorkSpace->mOperationLaneD;
    [[maybe_unused]] std::uint8_t *aFireLaneA = pWorkSpace->mFireLaneA;
    [[maybe_unused]] std::uint8_t *aFireLaneB = pWorkSpace->mFireLaneB;
    [[maybe_unused]] std::uint8_t *aFireLaneC = pWorkSpace->mFireLaneC;
    [[maybe_unused]] std::uint8_t *aFireLaneD = pWorkSpace->mFireLaneD;
    [[maybe_unused]] std::uint8_t *aInvestLaneA = pWorkSpace->mInvestLaneA;
    [[maybe_unused]] std::uint8_t *aInvestLaneB = pWorkSpace->mInvestLaneB;
    [[maybe_unused]] std::uint8_t *aInvestLaneC = pWorkSpace->mInvestLaneC;
    [[maybe_unused]] std::uint8_t *aInvestLaneD = pWorkSpace->mInvestLaneD;
    [[maybe_unused]] std::uint64_t *aPhaseEOrbiterAssignSaltA = pWorkSpace->mDomainBundle.mPhaseESalts.mOrbiterAssign.mSaltA;
    [[maybe_unused]] std::uint64_t *aPhaseEOrbiterAssignSaltB = pWorkSpace->mDomainBundle.mPhaseESalts.mOrbiterAssign.mSaltB;
    [[maybe_unused]] std::uint64_t *aPhaseEOrbiterAssignSaltC = pWorkSpace->mDomainBundle.mPhaseESalts.mOrbiterAssign.mSaltC;
    [[maybe_unused]] std::uint64_t *aPhaseEOrbiterAssignSaltD = pWorkSpace->mDomainBundle.mPhaseESalts.mOrbiterAssign.mSaltD;
    [[maybe_unused]] std::uint64_t *aPhaseEOrbiterAssignSaltE = pWorkSpace->mDomainBundle.mPhaseESalts.mOrbiterAssign.mSaltE;
    [[maybe_unused]] std::uint64_t *aPhaseEOrbiterAssignSaltF = pWorkSpace->mDomainBundle.mPhaseESalts.mOrbiterAssign.mSaltF;
    [[maybe_unused]] std::uint64_t *aPhaseEOrbiterUpdateSaltA = pWorkSpace->mDomainBundle.mPhaseESalts.mOrbiterUpdate.mSaltA;
    [[maybe_unused]] std::uint64_t *aPhaseEOrbiterUpdateSaltB = pWorkSpace->mDomainBundle.mPhaseESalts.mOrbiterUpdate.mSaltB;
    [[maybe_unused]] std::uint64_t *aPhaseEOrbiterUpdateSaltC = pWorkSpace->mDomainBundle.mPhaseESalts.mOrbiterUpdate.mSaltC;
    [[maybe_unused]] std::uint64_t *aPhaseEOrbiterUpdateSaltD = pWorkSpace->mDomainBundle.mPhaseESalts.mOrbiterUpdate.mSaltD;
    [[maybe_unused]] std::uint64_t *aPhaseEOrbiterUpdateSaltE = pWorkSpace->mDomainBundle.mPhaseESalts.mOrbiterUpdate.mSaltE;
    [[maybe_unused]] std::uint64_t *aPhaseEOrbiterUpdateSaltF = pWorkSpace->mDomainBundle.mPhaseESalts.mOrbiterUpdate.mSaltF;
    [[maybe_unused]] std::uint64_t *aPhaseEWandererUpdateSaltA = pWorkSpace->mDomainBundle.mPhaseESalts.mWandererUpdate.mSaltA;
    [[maybe_unused]] std::uint64_t *aPhaseEWandererUpdateSaltB = pWorkSpace->mDomainBundle.mPhaseESalts.mWandererUpdate.mSaltB;
    [[maybe_unused]] std::uint64_t *aPhaseEWandererUpdateSaltC = pWorkSpace->mDomainBundle.mPhaseESalts.mWandererUpdate.mSaltC;
    [[maybe_unused]] std::uint64_t *aPhaseEWandererUpdateSaltD = pWorkSpace->mDomainBundle.mPhaseESalts.mWandererUpdate.mSaltD;
    [[maybe_unused]] std::uint64_t *aPhaseEWandererUpdateSaltE = pWorkSpace->mDomainBundle.mPhaseESalts.mWandererUpdate.mSaltE;
    [[maybe_unused]] std::uint64_t *aPhaseEWandererUpdateSaltF = pWorkSpace->mDomainBundle.mPhaseESalts.mWandererUpdate.mSaltF;
    const std::uint64_t &aPhaseEDomainWordIngress = pWorkSpace->mDomainBundle.mPhaseEConstants.mIngress;
    const std::uint64_t &aPhaseEDomainWordScatter = pWorkSpace->mDomainBundle.mPhaseEConstants.mScatter;
    const std::uint64_t &aPhaseEDomainWordCross = pWorkSpace->mDomainBundle.mPhaseEConstants.mCross;
    std::uint64_t aCross = 0; std::uint64_t aScatter = 0;

    std::uint64_t aOrbiterA = 0; std::uint64_t aOrbiterB = 0; std::uint64_t aOrbiterC = 0; std::uint64_t aOrbiterD = 0;
    std::uint64_t aOrbiterE = 0; std::uint64_t aOrbiterF = 0; std::uint64_t aOrbiterG = 0; std::uint64_t aOrbiterH = 0;
    std::uint64_t aOrbiterI = 0; std::uint64_t aOrbiterJ = 0; std::uint64_t aOrbiterK = 0;

    // [seed arx]
    [[maybe_unused]] std::uint8_t *mSource = pWorkSpace->mSource;
    std::uint64_t aPrevious = *pPrevious;
    std::uint64_t aIngress = *pIngress;
    std::uint64_t aCarry = *pCarry;
    std::uint64_t aWandererA = *pWandererA;
    std::uint64_t aWandererB = *pWandererB;
    std::uint64_t aWandererC = *pWandererC;
    std::uint64_t aWandererD = *pWandererD;
    std::uint64_t aWandererE = *pWandererE;
    std::uint64_t aWandererF = *pWandererF;
    std::uint64_t aWandererG = *pWandererG;
    std::uint64_t aWandererH = *pWandererH;
    std::uint64_t aWandererI = *pWandererI;
    std::uint64_t aWandererJ = *pWandererJ;
    std::uint64_t aWandererK = *pWandererK;
    std::uint64_t aNonceWordA = TwistMix64::DiffuseB(pNonce * 0xC2F58B0D4C9957DBULL + 0xB17BA92A134D0DDAULL);
    std::uint64_t aNonceWordB = TwistMix64::DiffuseA(pNonce * 0x9E7E4EDAD62CEF2BULL + 0xAA08553E8C9315D9ULL);
    std::uint64_t aNonceWordC = TwistMix64::DiffuseC(pNonce * 0xB30157FFD529018DULL + 0xAD0C503D477E5310ULL);
    std::uint64_t aNonceWordD = TwistMix64::DiffuseC(pNonce * 0x8A4FD8387288F8D7ULL + 0xA300E50F66AA187EULL);
    std::uint64_t aNonceWordE = TwistMix64::DiffuseB(pNonce * 0xCEB2483E0DF4576BULL + 0x95707841430C168FULL);
    std::uint64_t aNonceWordF = TwistMix64::DiffuseC(pNonce * 0xE3EDF8AFC1238CC7ULL + 0xD232DF3C14EB0572ULL);
    std::uint64_t aNonceWordG = TwistMix64::DiffuseB(pNonce * 0xF9E81DDFB1E36C49ULL + 0xA217BEB026BAFC7EULL);
    std::uint64_t aNonceWordH = TwistMix64::DiffuseC(pNonce * 0xC8848D22AB074E39ULL + 0xB44BED66BFFD63D2ULL);
    std::uint64_t aNonceWordI = TwistMix64::DiffuseA(pNonce * 0xACA9ACF4E64009A3ULL + 0xD1360760B7DBC0B6ULL);
    std::uint64_t aNonceWordJ = TwistMix64::DiffuseA(pNonce * 0x9684DDE89795EC05ULL + 0x98604D9526425E20ULL);
    std::uint64_t aNonceWordK = TwistMix64::DiffuseC(pNonce * 0xD472C99954364BC5ULL + 0x94921AA808C0E248ULL);
    std::uint64_t aNonceWordL = TwistMix64::DiffuseA(pNonce * 0xA7E084D0AAC96AA7ULL + 0xAFAD81A3E3FB7F09ULL);
    std::uint64_t aNonceWordM = TwistMix64::DiffuseB(pNonce * 0xB452A8FBCD92E0E7ULL + 0xACC0483258D8084AULL);
    std::uint64_t aNonceWordN = TwistMix64::DiffuseB(pNonce * 0x8F58B61D45407A1BULL + 0xE230D2346DBEBEB7ULL);
    std::uint64_t aNonceWordO = TwistMix64::DiffuseA(pNonce * 0xC1BFB958CC30B7AFULL + 0xCBCD984D7BD62D78ULL);
    std::uint64_t aNonceWordP = TwistMix64::DiffuseB(pNonce * 0xCB30D442EE4C0187ULL + 0x845177529440990EULL);
    // GSeedRunSeed_E seed_loop_e (start)
    {
        // GSeedRunSeed_E seed_loop_e lane group
        // read from: aInvestLaneA, aInvestLaneB, aFireLaneA, aInvestLaneC, aInvestLaneD, aFireLaneB, aWorkLaneA, aWorkLaneB, aWorkLaneC, aOperationLaneA, aWorkLaneD, aOperationLaneB, aFireLaneC, aOperationLaneC, aFireLaneD
        // write to: aFireLaneA, aFireLaneB, aOperationLaneA, aOperationLaneB, aOperationLaneC, aOperationLaneD
    
        // seed_loop_e loop 1
        // ingress from: aInvestLaneA, aInvestLaneB, aFireLaneA
        // ingress directions: aInvestLaneA forward forced, aInvestLaneB forward forced, aFireLaneA forward/backward random
        // cross from: aInvestLaneC, aInvestLaneD, aFireLaneB
        // cross directions: aInvestLaneC backward forced, aInvestLaneD backward forced, aFireLaneB backward/forward random
        // write to: aFireLaneA
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aInvestLaneA[((aIndex + 4276U)) & S_BLOCK1], 35U) ^ RotL64(aInvestLaneB[((aIndex + 4616U)) & S_BLOCK1], 53U));
            aIngress ^= RotL64(aFireLaneA[((aIndex + 3864U)) & S_BLOCK1], 11U);
            aIngress = TwistMix64::DiffuseB(((aIngress ^ aPhaseEDomainWordIngress) ^ aNonceWordB));
            //
            aCross = (RotL64(aInvestLaneC[((S_BLOCK1 - aIndex + 1763U)) & S_BLOCK1], 29U) ^ RotL64(aInvestLaneD[((S_BLOCK1 - aIndex + 1906U)) & S_BLOCK1], 13U));
            aCross ^= RotL64(aFireLaneB[((aIndex + 1955U)) & S_BLOCK1], 43U);
            aCross = TwistMix64::DiffuseC(((aCross ^ aPhaseEDomainWordCross) ^ aNonceWordC));
            //
            aScatter = (RotL64(aIngress, 6U) ^ RotL64(aCross, 51U)) ^ (RotL64(aCarry, 37U) + RotL64(aPrevious, 23U));
            aScatter = TwistMix64::DiffuseB(((aScatter ^ aPhaseEDomainWordScatter) ^ aNonceWordE));
            //
            aOrbiterG = ((aWandererA + RotL64(aCross, 56U)) + 9133751643283278896U) + aNonceWordK;
            aOrbiterC = ((aWandererK + RotL64(aPrevious, 27U)) + 8971581804375380408U) + aNonceWordI;
            aOrbiterE = ((aWandererH + RotL64(aScatter, 35U)) + RotL64(aCarry, 47U)) + 12559650383714566592U;
            aOrbiterH = ((aWandererC + RotL64(aIngress, 41U)) + RotL64(aCarry, 13U)) + 15753206088872859163U;
            aOrbiterA = ((aWandererJ + RotL64(aPrevious, 43U)) + RotL64(aCarry, 19U)) + 7640756270450762350U;
            aOrbiterF = (((aWandererE + RotL64(aCross, 53U)) + 7340073357551376125U) + aPhaseEOrbiterAssignSaltB[((aIndex + 5U)) & S_SALT1]) + aNonceWordA;
            aOrbiterK = (aWandererD + RotL64(aScatter, 47U)) + 5270256573644196046U;
            aOrbiterD = (aWandererB + RotL64(aIngress, 13U)) + 3567367996479995928U;
            aOrbiterB = ((aWandererG + RotL64(aCross, 22U)) + 11939634537492733738U) + aNonceWordJ;
            aOrbiterJ = (aWandererI + RotL64(aPrevious, 29U)) + 7051817732424527120U;
            aOrbiterI = ((aWandererF + RotL64(aScatter, 5U)) + 1730487669951837941U) + aPhaseEOrbiterAssignSaltE[((aIndex + 13U)) & S_SALT1];
            //
            aOrbiterG = ((aOrbiterG + aOrbiterC) + 18009252467909454817U) + aPhaseEOrbiterUpdateSaltF[((aIndex + 20U)) & S_SALT1];
            aOrbiterE = (aOrbiterE ^ aOrbiterG) ^ 2361024272031696442U;
            aOrbiterE = RotL64((aOrbiterE * 15215151562500226027U), 35U);
            //
            aOrbiterH = (aOrbiterH + aOrbiterA) + 15902755877642960397U;
            aOrbiterC = ((aOrbiterC ^ aOrbiterH) ^ 12243517544704116184U) ^ aNonceWordE;
            aOrbiterC = RotL64((aOrbiterC * 2576071074148141447U), 53U);
            //
            aOrbiterC = ((aOrbiterC + aOrbiterF) + 16846181962302186187U) + aPhaseEOrbiterUpdateSaltE[((aIndex + 22U)) & S_SALT1];
            aOrbiterK = (aOrbiterK ^ aOrbiterC) ^ 636121425116506681U;
            aOrbiterK = RotL64((aOrbiterK * 17075030673338779993U), 23U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterH) + 6887385655828217318U;
            aOrbiterG = (aOrbiterG ^ aOrbiterD) ^ 3705834550934775862U;
            aOrbiterG = RotL64((aOrbiterG * 11275428284929594435U), 43U);
            //
            aOrbiterF = (aOrbiterF + aOrbiterB) + 11165142437077969438U;
            aOrbiterJ = ((aOrbiterJ ^ aOrbiterF) ^ 6426659930331618269U) ^ aNonceWordL;
            aOrbiterJ = RotL64((aOrbiterJ * 17170640810530893705U), 27U);
            //
            aOrbiterB = ((aOrbiterB + aOrbiterE) + 12629082390899315789U) + aPhaseEOrbiterUpdateSaltB[((aIndex + 11U)) & S_SALT1];
            aOrbiterD = ((aOrbiterD ^ aOrbiterB) ^ 4277510580069574724U) ^ aPhaseEOrbiterUpdateSaltA[(((31U - aIndex) + 8U)) & S_SALT1];
            aOrbiterD = RotL64((aOrbiterD * 9829125163412708305U), 51U);
            //
            aOrbiterE = ((aOrbiterE + aOrbiterK) + 13814834144170469978U) + aNonceWordP;
            aOrbiterH = ((aOrbiterH ^ aOrbiterE) ^ 3698381854100295826U) ^ aNonceWordG;
            aOrbiterH = RotL64((aOrbiterH * 5126359230872258015U), 21U);
            //
            aOrbiterA = (aOrbiterA + aOrbiterI) + 11623170635983579937U;
            aOrbiterF = (aOrbiterF ^ aOrbiterA) ^ 7247413650388803796U;
            aOrbiterF = RotL64((aOrbiterF * 3403219499465560059U), 47U);
            //
            aOrbiterK = (aOrbiterK + aOrbiterJ) + 3129755194359521145U;
            aOrbiterA = (aOrbiterA ^ aOrbiterK) ^ 4081016725582134919U;
            aOrbiterA = RotL64((aOrbiterA * 11564414998539605389U), 57U);
            //
            aOrbiterJ = (aOrbiterJ + aOrbiterD) + 15878346077922215753U;
            aOrbiterI = (aOrbiterI ^ aOrbiterJ) ^ 2974440187796944059U;
            aOrbiterI = RotL64((aOrbiterI * 783253926537018373U), 13U);
            //
            aOrbiterI = (aOrbiterI + aOrbiterG) + 3922344163443096356U;
            aOrbiterB = (aOrbiterB ^ aOrbiterI) ^ 9133751643283278896U;
            aOrbiterB = RotL64((aOrbiterB * 16887991698415418429U), 5U);
            //
            aIngress = aOrbiterC ^ RotL64(aOrbiterJ, 39U);
            aIngress = aIngress + (aOrbiterK ^ RotL64(aOrbiterB, 35U));
            aIngress = aIngress + (aOrbiterH ^ RotL64(aOrbiterI, 37U));
            aIngress = aIngress + (aOrbiterE ^ RotL64(aOrbiterF, 29U));
            aIngress = aIngress + (aOrbiterD ^ RotL64(aOrbiterA, 44U));
            aIngress = aIngress + RotL64(aOrbiterG, 57U);
            aIngress = TwistMix64::DiffuseA((aIngress + aScatter));
            //
            aWandererG = aWandererG + (((RotL64(aIngress, 51U) + RotL64(aOrbiterG, 23U)) + aOrbiterE) + RotL64(aCarry, 51U));
            aWandererC = aWandererC ^ ((RotL64(aScatter, 60U) + RotL64(aOrbiterB, 11U)) + aOrbiterC);
            aWandererK = aWandererK + (((RotL64(aCross, 37U) + RotL64(aOrbiterD, 5U)) + aOrbiterG) + aPhaseEWandererUpdateSaltD[((aIndex + 27U)) & S_SALT1]);
            aWandererD = aWandererD ^ ((RotL64(aPrevious, 43U) + RotL64(aOrbiterJ, 47U)) + aOrbiterD);
            aWandererF = aWandererF + ((RotL64(aIngress, 39U) + RotL64(aOrbiterF, 27U)) + aOrbiterD);
            aWandererB = aWandererB ^ ((RotL64(aCross, 6U) + aOrbiterE) + RotL64(aOrbiterC, 58U));
            aWandererE = aWandererE + ((((RotL64(aPrevious, 47U) + aOrbiterE) + RotL64(aOrbiterA, 29U)) + RotL64(aCarry, 19U)) + aNonceWordN);
            aWandererA = aWandererA ^ ((RotL64(aScatter, 19U) + aOrbiterJ) + RotL64(aOrbiterC, 37U));
            aWandererH = aWandererH + ((RotL64(aIngress, 35U) + aOrbiterH) + RotL64(aOrbiterD, 51U));
            aWandererJ = aWandererJ ^ (((RotL64(aScatter, 27U) + aOrbiterK) + RotL64(aOrbiterA, 54U)) + aNonceWordH);
            aWandererI = aWandererI + (((RotL64(aCross, 3U) + RotL64(aOrbiterI, 39U)) + aOrbiterA) + aPhaseEWandererUpdateSaltA[((aIndex + 19U)) & S_SALT1]);
            //
            aCarry = aCarry + (aWandererA ^ RotL64(aWandererJ, 18U));
            aCarry = aCarry + (aWandererG ^ RotL64(aWandererE, 57U));
            aCarry = aCarry + (aWandererD ^ RotL64(aWandererK, 5U));
            aCarry = aCarry + (RotL64(aWandererC, 13U) ^ aWandererH);
            aCarry = aCarry + (RotL64(aWandererI, 51U) ^ aWandererF);
            aCarry = aCarry + RotL64(aWandererB, 40U);
            aCarry = aCarry + RotL64(aIngress, 43U);
            aCarry = TwistMix64::DiffuseA(aCarry);
            //
            aFireLaneA[aIndex] = aIngress;
        }
    
        // seed_loop_e loop 2
        // ingress from: aFireLaneA, aInvestLaneC, aInvestLaneD, aWorkLaneA
        // ingress directions: aFireLaneA forward forced, aInvestLaneC forward forced, aInvestLaneD forward forced, aWorkLaneA forward/backward random
        // cross from: aInvestLaneA, aInvestLaneB, aWorkLaneB
        // cross directions: aInvestLaneA backward forced, aInvestLaneB backward forced, aWorkLaneB backward/forward random
        // write to: aFireLaneB
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aFireLaneA[((aIndex + 9062U)) & S_BLOCK1], 20U) ^ RotL64(aInvestLaneC[((aIndex + 8977U)) & S_BLOCK1], 47U));
            aIngress ^= (RotL64(aInvestLaneD[((aIndex + 7305U)) & S_BLOCK1], 29U) ^ RotL64(aWorkLaneA[((aIndex + 9471U)) & S_BLOCK1], 11U));
            aIngress = TwistMix64::DiffuseB(((aIngress ^ aPhaseEDomainWordIngress) ^ aNonceWordA));
            //
            aCross = (RotL64(aInvestLaneA[((S_BLOCK1 - aIndex + 10268U)) & S_BLOCK1], 23U) ^ RotL64(aInvestLaneB[((S_BLOCK1 - aIndex + 9761U)) & S_BLOCK1], 5U));
            aCross ^= RotL64(aWorkLaneB[((S_BLOCK1 - aIndex + 7373U)) & S_BLOCK1], 46U);
            aCross = TwistMix64::DiffuseC(((aCross ^ aPhaseEDomainWordCross) ^ aNonceWordF));
            //
            aScatter = (RotL64(aIngress, 36U) + RotL64(aCarry, 11U)) + (RotL64(aCross, 23U) ^ RotL64(aPrevious, 53U));
            aScatter = TwistMix64::DiffuseC(((aScatter ^ aPhaseEDomainWordScatter) ^ aNonceWordN));
            //
            aOrbiterJ = ((aWandererC + RotL64(aIngress, 39U)) + 4179952823252098240U) + aNonceWordN;
            aOrbiterK = (aWandererK + RotL64(aPrevious, 41U)) + 3745613452332101749U;
            aOrbiterE = (aWandererF + RotL64(aScatter, 60U)) + 2955689793395307176U;
            aOrbiterH = ((aWandererE + RotL64(aCross, 19U)) + 5639060180251322019U) + aPhaseEOrbiterAssignSaltA[(((31U - aIndex) + 12U)) & S_SALT1];
            aOrbiterI = (aWandererG + RotL64(aPrevious, 21U)) + 7901969163853586463U;
            aOrbiterB = (aWandererD + RotL64(aCross, 23U)) + 2242166787816318119U;
            aOrbiterC = ((aWandererJ + RotL64(aIngress, 35U)) + RotL64(aCarry, 43U)) + 5239936443960750064U;
            aOrbiterG = ((aWandererH + RotL64(aScatter, 51U)) + 13939136954732185558U) + aNonceWordK;
            aOrbiterA = (aWandererB + RotL64(aIngress, 57U)) + 17058884136712717463U;
            aOrbiterF = ((aWandererA + RotL64(aPrevious, 4U)) + RotL64(aCarry, 51U)) + 18148618660054585941U;
            aOrbiterD = (((aWandererI + RotL64(aScatter, 37U)) + RotL64(aCarry, 35U)) + 7022023484530327814U) + aPhaseEOrbiterAssignSaltD[(((31U - aIndex) + 19U)) & S_SALT1];
            //
            aOrbiterJ = (aOrbiterJ + aOrbiterK) + 7722084537340095637U;
            aOrbiterE = (aOrbiterE ^ aOrbiterJ) ^ 11764151879690934182U;
            aOrbiterE = RotL64((aOrbiterE * 12264384877711365655U), 39U);
            //
            aOrbiterH = (aOrbiterH + aOrbiterI) + 16412785901758144708U;
            aOrbiterB = ((aOrbiterB ^ aOrbiterH) ^ 9666718667728274824U) ^ aNonceWordM;
            aOrbiterB = RotL64((aOrbiterB * 10865799822751771795U), 21U);
            //
            aOrbiterC = (aOrbiterC + aOrbiterJ) + 4307127540152109364U;
            aOrbiterG = (aOrbiterG ^ aOrbiterC) ^ 2457646804702647606U;
            aOrbiterG = RotL64((aOrbiterG * 6340030928007058595U), 11U);
            //
            aOrbiterB = (aOrbiterB + aOrbiterC) + 3179394870088602208U;
            aOrbiterA = ((aOrbiterA ^ aOrbiterB) ^ 504977947273774249U) ^ aPhaseEOrbiterUpdateSaltC[((aIndex + 25U)) & S_SALT1];
            aOrbiterA = RotL64((aOrbiterA * 16190282058883481551U), 19U);
            //
            aOrbiterK = ((aOrbiterK + aOrbiterA) + 16182729401018310837U) + aNonceWordH;
            aOrbiterH = (aOrbiterH ^ aOrbiterK) ^ 7110817020445860609U;
            aOrbiterH = RotL64((aOrbiterH * 13371352088428584087U), 27U);
            //
            aOrbiterA = (aOrbiterA + aOrbiterG) + 12960656706837391973U;
            aOrbiterI = (aOrbiterI ^ aOrbiterA) ^ 7103806893724395904U;
            aOrbiterI = RotL64((aOrbiterI * 14365984439655979791U), 5U);
            //
            aOrbiterE = (aOrbiterE + aOrbiterH) + 1248300178080633527U;
            aOrbiterF = ((aOrbiterF ^ aOrbiterE) ^ 7195473175424961337U) ^ aPhaseEOrbiterUpdateSaltF[(((31U - aIndex) + 8U)) & S_SALT1];
            aOrbiterF = RotL64((aOrbiterF * 4633558992739305045U), 51U);
            //
            aOrbiterG = (aOrbiterG + aOrbiterE) + 13007951568242991449U;
            aOrbiterD = (((aOrbiterD ^ aOrbiterG) ^ 10296811247653636372U) ^ aPhaseEOrbiterUpdateSaltB[((aIndex + 28U)) & S_SALT1]) ^ aNonceWordC;
            aOrbiterD = RotL64((aOrbiterD * 16469682651380549395U), 35U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterF) + 13922797949001028335U;
            aOrbiterJ = ((aOrbiterJ ^ aOrbiterD) ^ 16773545425463040155U) ^ aPhaseEOrbiterUpdateSaltD[((aIndex + 17U)) & S_SALT1];
            aOrbiterJ = RotL64((aOrbiterJ * 10639282630227832397U), 37U);
            //
            aOrbiterF = (aOrbiterF + aOrbiterB) + 2888887140296117803U;
            aOrbiterK = (aOrbiterK ^ aOrbiterF) ^ 10279517418046269817U;
            aOrbiterK = RotL64((aOrbiterK * 8600355360339461535U), 53U);
            //
            aOrbiterI = ((aOrbiterI + aOrbiterD) + 17303373436784809093U) + aNonceWordI;
            aOrbiterC = (aOrbiterC ^ aOrbiterI) ^ 4179952823252098240U;
            aOrbiterC = RotL64((aOrbiterC * 3675754609699406437U), 43U);
            //
            aIngress = aOrbiterG ^ RotL64(aOrbiterI, 13U);
            aIngress = aIngress + (RotL64(aOrbiterJ, 37U) ^ aOrbiterC);
            aIngress = aIngress + (aOrbiterK ^ RotL64(aOrbiterA, 11U));
            aIngress = aIngress + (aOrbiterE ^ RotL64(aOrbiterF, 21U));
            aIngress = aIngress + (aOrbiterH ^ RotL64(aOrbiterB, 58U));
            aIngress = aIngress + RotL64(aOrbiterD, 29U);
            aIngress = TwistMix64::DiffuseA((aIngress + aScatter));
            //
            aWandererF = aWandererF ^ ((RotL64(aPrevious, 53U) + aOrbiterB) + RotL64(aOrbiterK, 3U));
            aWandererB = aWandererB + ((((RotL64(aIngress, 60U) + aOrbiterC) + RotL64(aOrbiterF, 11U)) + aNonceWordE) + aPhaseEWandererUpdateSaltB[(((31U - aIndex) + 13U)) & S_SALT1]);
            aWandererK = aWandererK ^ ((RotL64(aScatter, 23U) + RotL64(aOrbiterH, 42U)) + aOrbiterG);
            aWandererI = aWandererI + ((RotL64(aCross, 43U) + RotL64(aOrbiterJ, 29U)) + aOrbiterK);
            aWandererJ = aWandererJ ^ (((RotL64(aPrevious, 51U) + RotL64(aOrbiterH, 57U)) + aOrbiterE) + aPhaseEWandererUpdateSaltC[((aIndex + 16U)) & S_SALT1]);
            aWandererA = aWandererA + (((RotL64(aIngress, 41U) + RotL64(aOrbiterD, 53U)) + aOrbiterE) + RotL64(aCarry, 21U));
            aWandererE = aWandererE ^ ((RotL64(aCross, 35U) + aOrbiterD) + RotL64(aOrbiterI, 48U));
            aWandererC = aWandererC + (((RotL64(aScatter, 37U) + aOrbiterF) + RotL64(aOrbiterI, 13U)) + RotL64(aCarry, 37U));
            aWandererD = aWandererD ^ ((RotL64(aCross, 26U) + RotL64(aOrbiterA, 51U)) + aOrbiterF);
            aWandererG = aWandererG + (((RotL64(aIngress, 57U) + aOrbiterK) + RotL64(aOrbiterG, 35U)) + aNonceWordJ);
            aWandererH = aWandererH ^ ((RotL64(aPrevious, 47U) + aOrbiterA) + RotL64(aOrbiterG, 21U));
            //
            aCarry = aCarry + (aWandererH ^ RotL64(aWandererF, 11U));
            aCarry = aCarry + (aWandererD ^ RotL64(aWandererG, 22U));
            aCarry = aCarry + (RotL64(aWandererK, 43U) ^ aWandererE);
            aCarry = aCarry + (RotL64(aWandererB, 47U) ^ aWandererI);
            aCarry = aCarry + (RotL64(aWandererA, 37U) ^ aWandererC);
            aCarry = aCarry + RotL64(aWandererJ, 41U);
            aCarry = aCarry + RotL64(aIngress, 50U);
            aCarry = TwistMix64::DiffuseB(aCarry);
            //
            aFireLaneB[S_BLOCK1 - aIndex] = aIngress;
        }
    
        // seed_loop_e loop 3
        // ingress from: aFireLaneB, aInvestLaneA, aWorkLaneC
        // ingress directions: aFireLaneB forward forced, aInvestLaneA forward forced, aWorkLaneC forward/backward random
        // cross from: aFireLaneA, aInvestLaneC
        // cross directions: aFireLaneA backward forced, aInvestLaneC backward/forward random
        // write to: aOperationLaneA
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aFireLaneB[((aIndex + 14701U)) & S_BLOCK1], 3U) ^ RotL64(aInvestLaneA[((aIndex + 12867U)) & S_BLOCK1], 43U));
            aIngress ^= RotL64(aWorkLaneC[((aIndex + 15246U)) & S_BLOCK1], 58U);
            aIngress = TwistMix64::DiffuseB(((aIngress ^ aPhaseEDomainWordIngress) ^ aNonceWordA));
            //
            aCross = RotL64(aFireLaneA[((S_BLOCK1 - aIndex + 14399U)) & S_BLOCK1], 37U) ^ RotL64(aInvestLaneC[((aIndex + 16383U)) & S_BLOCK1], 13U);
            aCross = TwistMix64::DiffuseB(((aCross ^ aPhaseEDomainWordCross) ^ aNonceWordL));
            //
            aScatter = (RotL64(aPrevious, 29U) + RotL64(aCross, 41U)) ^ (RotL64(aIngress, 13U) + RotL64(aCarry, 56U));
            aScatter = TwistMix64::DiffuseC(((aScatter ^ aPhaseEDomainWordScatter) ^ aNonceWordC));
            //
            aOrbiterC = ((aWandererE + RotL64(aScatter, 41U)) + 10336802574069791273U) + aNonceWordM;
            aOrbiterB = (aWandererA + RotL64(aPrevious, 57U)) + 169025388197058936U;
            aOrbiterG = (((aWandererF + RotL64(aIngress, 5U)) + RotL64(aCarry, 57U)) + 6541354188379168846U) + aNonceWordJ;
            aOrbiterH = ((aWandererD + RotL64(aCross, 21U)) + RotL64(aCarry, 19U)) + 16223920526599306104U;
            aOrbiterI = ((aWandererB + RotL64(aPrevious, 60U)) + 12756613707692514808U) + aNonceWordB;
            aOrbiterJ = ((aWandererG + RotL64(aIngress, 53U)) + 5082475548176484035U) + aPhaseEOrbiterAssignSaltC[(((31U - aIndex) + 23U)) & S_SALT1];
            aOrbiterK = (aWandererJ + RotL64(aCross, 23U)) + 4907435526952698526U;
            aOrbiterA = (((aWandererK + RotL64(aScatter, 3U)) + RotL64(aCarry, 23U)) + 14236627073831834337U) + aPhaseEOrbiterAssignSaltF[((aIndex + 12U)) & S_SALT1];
            aOrbiterE = (aWandererH + RotL64(aCross, 37U)) + 11502511046130497584U;
            aOrbiterD = (aWandererC + RotL64(aIngress, 44U)) + 3679044835550219497U;
            aOrbiterF = (aWandererI + RotL64(aPrevious, 13U)) + 11254838916686736746U;
            //
            aOrbiterC = (aOrbiterC + aOrbiterB) + 10582608424233200966U;
            aOrbiterG = ((aOrbiterG ^ aOrbiterC) ^ 10449735026385340313U) ^ aNonceWordP;
            aOrbiterG = RotL64((aOrbiterG * 7363770199734997411U), 19U);
            //
            aOrbiterH = (aOrbiterH + aOrbiterI) + 4628253464169957835U;
            aOrbiterC = (aOrbiterC ^ aOrbiterH) ^ 17664454668473204465U;
            aOrbiterC = RotL64((aOrbiterC * 4234720298731378527U), 3U);
            //
            aOrbiterG = ((aOrbiterG + aOrbiterJ) + 3798386391743884889U) + aPhaseEOrbiterUpdateSaltD[(((31U - aIndex) + 21U)) & S_SALT1];
            aOrbiterK = (aOrbiterK ^ aOrbiterG) ^ 1379331161819246587U;
            aOrbiterK = RotL64((aOrbiterK * 13086160171095077295U), 53U);
            //
            aOrbiterA = (((aOrbiterA + aOrbiterC) + 9816600392407327227U) + aPhaseEOrbiterUpdateSaltC[(((31U - aIndex) + 27U)) & S_SALT1]) + aNonceWordG;
            aOrbiterE = (aOrbiterE ^ aOrbiterA) ^ 16781971616348376878U;
            aOrbiterE = RotL64((aOrbiterE * 12503867584828289879U), 41U);
            //
            aOrbiterE = (aOrbiterE + aOrbiterG) + 4807797577690520554U;
            aOrbiterD = (aOrbiterD ^ aOrbiterE) ^ 2492057261148595922U;
            aOrbiterD = RotL64((aOrbiterD * 9453302540675483005U), 29U);
            //
            aOrbiterK = (aOrbiterK + aOrbiterH) + 7909676419643119585U;
            aOrbiterA = ((aOrbiterA ^ aOrbiterK) ^ 256053568910383007U) ^ aPhaseEOrbiterUpdateSaltA[((aIndex + 24U)) & S_SALT1];
            aOrbiterA = RotL64((aOrbiterA * 11965085163352053161U), 51U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterK) + 16179914439220412472U;
            aOrbiterF = ((aOrbiterF ^ aOrbiterD) ^ 3968867762761955845U) ^ aPhaseEOrbiterUpdateSaltE[((aIndex + 28U)) & S_SALT1];
            aOrbiterF = RotL64((aOrbiterF * 7473632378251893139U), 39U);
            //
            aOrbiterI = (aOrbiterI + aOrbiterE) + 7474832923901283742U;
            aOrbiterB = (aOrbiterB ^ aOrbiterI) ^ 4736994731050735779U;
            aOrbiterB = RotL64((aOrbiterB * 9839654409121414047U), 23U);
            //
            aOrbiterJ = (aOrbiterJ + aOrbiterF) + 596484364660389193U;
            aOrbiterH = ((aOrbiterH ^ aOrbiterJ) ^ 13822222274464306169U) ^ aNonceWordC;
            aOrbiterH = RotL64((aOrbiterH * 1723502278319885511U), 11U);
            //
            aOrbiterB = (aOrbiterB + aOrbiterD) + 16307920280681985443U;
            aOrbiterJ = (aOrbiterJ ^ aOrbiterB) ^ 3505106171801702915U;
            aOrbiterJ = RotL64((aOrbiterJ * 8479675421552861243U), 21U);
            //
            aOrbiterF = (aOrbiterF + aOrbiterA) + 4987142580981135150U;
            aOrbiterI = ((aOrbiterI ^ aOrbiterF) ^ 10336802574069791273U) ^ aNonceWordH;
            aOrbiterI = RotL64((aOrbiterI * 2670706512498539705U), 37U);
            //
            aIngress = aOrbiterI ^ RotL64(aOrbiterF, 35U);
            aIngress = aIngress + (aOrbiterB ^ RotL64(aOrbiterD, 39U));
            aIngress = aIngress + (aOrbiterJ ^ RotL64(aOrbiterK, 43U));
            aIngress = aIngress + (RotL64(aOrbiterG, 56U) ^ aOrbiterE);
            aIngress = aIngress + (aOrbiterC ^ RotL64(aOrbiterH, 51U));
            aIngress = aIngress + RotL64(aOrbiterA, 41U);
            aIngress = TwistMix64::DiffuseC((aIngress + aScatter));
            //
            aWandererE = aWandererE + (((RotL64(aIngress, 60U) + aOrbiterF) + RotL64(aOrbiterA, 21U)) + RotL64(aCarry, 53U));
            aWandererD = aWandererD ^ ((RotL64(aPrevious, 19U) + aOrbiterJ) + RotL64(aOrbiterF, 24U));
            aWandererA = aWandererA + ((RotL64(aCross, 3U) + RotL64(aOrbiterC, 29U)) + aOrbiterF);
            aWandererJ = aWandererJ ^ ((RotL64(aScatter, 39U) + RotL64(aOrbiterC, 39U)) + aOrbiterG);
            aWandererI = aWandererI + (((RotL64(aPrevious, 51U) + aOrbiterE) + RotL64(aOrbiterD, 53U)) + aPhaseEWandererUpdateSaltF[(((31U - aIndex) + 17U)) & S_SALT1]);
            aWandererB = aWandererB ^ ((RotL64(aCross, 47U) + aOrbiterC) + RotL64(aOrbiterH, 44U));
            aWandererC = aWandererC + (((RotL64(aScatter, 13U) + RotL64(aOrbiterA, 5U)) + aOrbiterK) + aNonceWordD);
            aWandererH = aWandererH ^ (((RotL64(aIngress, 57U) + aOrbiterI) + RotL64(aOrbiterG, 51U)) + aPhaseEWandererUpdateSaltE[((aIndex + 5U)) & S_SALT1]);
            aWandererK = aWandererK + ((RotL64(aScatter, 53U) + aOrbiterA) + RotL64(aOrbiterE, 37U));
            aWandererF = aWandererF ^ ((RotL64(aCross, 36U) + RotL64(aOrbiterI, 41U)) + aOrbiterD);
            aWandererG = aWandererG + ((((RotL64(aPrevious, 23U) + RotL64(aOrbiterC, 35U)) + aOrbiterB) + RotL64(aCarry, 13U)) + aNonceWordE);
            //
            aCarry = aCarry + (aWandererC ^ RotL64(aWandererG, 30U));
            aCarry = aCarry + (RotL64(aWandererA, 5U) ^ aWandererK);
            aCarry = aCarry + (RotL64(aWandererJ, 53U) ^ aWandererI);
            aCarry = aCarry + (aWandererE ^ RotL64(aWandererH, 41U));
            aCarry = aCarry + (aWandererB ^ RotL64(aWandererD, 60U));
            aCarry = aCarry + RotL64(aWandererF, 43U);
            aCarry = aCarry + RotL64(aIngress, 21U);
            aCarry = TwistMix64::DiffuseA(aCarry);
            //
            aOperationLaneA[aIndex] = aIngress;
        }
    
        // seed_loop_e loop 4
        // ingress from: aOperationLaneA, aFireLaneA, aWorkLaneD
        // ingress directions: aOperationLaneA forward forced, aFireLaneA forward forced, aWorkLaneD forward/backward random
        // cross from: aFireLaneB, aInvestLaneD
        // cross directions: aFireLaneB backward forced, aInvestLaneD backward/forward random
        // write to: aOperationLaneB
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aOperationLaneA[((aIndex + 20731U)) & S_BLOCK1], 11U) ^ RotL64(aFireLaneA[((aIndex + 17038U)) & S_BLOCK1], 42U));
            aIngress ^= RotL64(aWorkLaneD[((S_BLOCK1 - aIndex + 18747U)) & S_BLOCK1], 53U);
            aIngress = TwistMix64::DiffuseB(((aIngress ^ aPhaseEDomainWordIngress) ^ aNonceWordE));
            //
            aCross = RotL64(aFireLaneB[((S_BLOCK1 - aIndex + 17844U)) & S_BLOCK1], 18U) ^ RotL64(aInvestLaneD[((S_BLOCK1 - aIndex + 16625U)) & S_BLOCK1], 47U);
            aCross = TwistMix64::DiffuseC(((aCross ^ aPhaseEDomainWordCross) ^ aNonceWordJ));
            //
            aScatter = (RotL64(aPrevious, 39U) ^ RotL64(aCross, 60U)) + (RotL64(aCarry, 11U) + RotL64(aIngress, 23U));
            aScatter = TwistMix64::DiffuseA(((aScatter ^ aPhaseEDomainWordScatter) ^ aNonceWordL));
            //
            aOrbiterA = (((aWandererH + RotL64(aCross, 58U)) + RotL64(aCarry, 57U)) + 16519040829220310189U) + aNonceWordA;
            aOrbiterE = (aWandererD + RotL64(aPrevious, 21U)) + 6888002778416941825U;
            aOrbiterC = (((aWandererC + RotL64(aIngress, 53U)) + RotL64(aCarry, 23U)) + 1310832187746534025U) + aNonceWordN;
            aOrbiterK = (((aWandererE + RotL64(aScatter, 41U)) + 5890888009051281674U) + aPhaseEOrbiterAssignSaltB[(((31U - aIndex) + 3U)) & S_SALT1]) + aNonceWordI;
            aOrbiterI = (aWandererK + RotL64(aPrevious, 35U)) + 5143864838362464857U;
            aOrbiterG = (aWandererB + RotL64(aIngress, 27U)) + 15591534069452660003U;
            aOrbiterD = (aWandererG + RotL64(aCross, 3U)) + 1466867671765325096U;
            aOrbiterF = (aWandererA + RotL64(aScatter, 30U)) + 13931443680107902488U;
            aOrbiterJ = (aWandererI + RotL64(aIngress, 5U)) + 15400747367673245552U;
            aOrbiterB = (((aWandererF + RotL64(aPrevious, 47U)) + RotL64(aCarry, 37U)) + 2836975369734495759U) + aPhaseEOrbiterAssignSaltE[((aIndex + 19U)) & S_SALT1];
            aOrbiterH = (aWandererJ + RotL64(aScatter, 39U)) + 2370720358274970117U;
            //
            aOrbiterA = ((aOrbiterA + aOrbiterE) + 3470677184188006133U) + aNonceWordC;
            aOrbiterC = ((aOrbiterC ^ aOrbiterA) ^ 7175584278499266723U) ^ aPhaseEOrbiterUpdateSaltC[(((31U - aIndex) + 21U)) & S_SALT1];
            aOrbiterC = RotL64((aOrbiterC * 10067096593682482345U), 57U);
            //
            aOrbiterK = (aOrbiterK + aOrbiterI) + 6095078817776863055U;
            aOrbiterE = (aOrbiterE ^ aOrbiterK) ^ 2176637999243513070U;
            aOrbiterE = RotL64((aOrbiterE * 12215701810843975501U), 53U);
            //
            aOrbiterC = (aOrbiterC + aOrbiterG) + 5580391239754903129U;
            aOrbiterD = ((aOrbiterD ^ aOrbiterC) ^ 15196125567953871184U) ^ aNonceWordL;
            aOrbiterD = RotL64((aOrbiterD * 12686361960729564519U), 5U);
            //
            aOrbiterF = (aOrbiterF + aOrbiterC) + 12787014151503209931U;
            aOrbiterJ = (aOrbiterJ ^ aOrbiterF) ^ 1523153207064063495U;
            aOrbiterJ = RotL64((aOrbiterJ * 3113907543551927561U), 29U);
            //
            aOrbiterB = (aOrbiterB + aOrbiterK) + 12973289026485937829U;
            aOrbiterA = ((aOrbiterA ^ aOrbiterB) ^ 9087439766232078173U) ^ aPhaseEOrbiterUpdateSaltD[(((31U - aIndex) + 13U)) & S_SALT1];
            aOrbiterA = RotL64((aOrbiterA * 5817029335999350327U), 27U);
            //
            aOrbiterG = (aOrbiterG + aOrbiterJ) + 16318022893068674015U;
            aOrbiterH = (aOrbiterH ^ aOrbiterG) ^ 11089160685103562409U;
            aOrbiterH = RotL64((aOrbiterH * 17087834321385147603U), 19U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterH) + 8680037953925067235U;
            aOrbiterK = (aOrbiterK ^ aOrbiterD) ^ 3112588943274158119U;
            aOrbiterK = RotL64((aOrbiterK * 9214011370307670371U), 51U);
            //
            aOrbiterE = ((aOrbiterE + aOrbiterF) + 16749015684369649821U) + aPhaseEOrbiterUpdateSaltE[(((31U - aIndex) + 9U)) & S_SALT1];
            aOrbiterG = ((aOrbiterG ^ aOrbiterE) ^ 9419550535891334966U) ^ aNonceWordD;
            aOrbiterG = RotL64((aOrbiterG * 5421312787569114811U), 43U);
            //
            aOrbiterJ = (aOrbiterJ + aOrbiterD) + 12309598080688360615U;
            aOrbiterB = (aOrbiterB ^ aOrbiterJ) ^ 12244971765096881835U;
            aOrbiterB = RotL64((aOrbiterB * 17260277357109449509U), 13U);
            //
            aOrbiterI = ((aOrbiterI + aOrbiterA) + 10088685417774847648U) + aPhaseEOrbiterUpdateSaltA[((aIndex + 7U)) & S_SALT1];
            aOrbiterF = (aOrbiterF ^ aOrbiterI) ^ 3241987595838650154U;
            aOrbiterF = RotL64((aOrbiterF * 14096986158958931367U), 21U);
            //
            aOrbiterH = (aOrbiterH + aOrbiterB) + 17916401586500786536U;
            aOrbiterI = (aOrbiterI ^ aOrbiterH) ^ 16519040829220310189U;
            aOrbiterI = RotL64((aOrbiterI * 6742024268853509861U), 35U);
            //
            aIngress = RotL64(aOrbiterH, 26U) ^ aOrbiterA;
            aIngress = aIngress + (aOrbiterC ^ RotL64(aOrbiterF, 41U));
            aIngress = aIngress + (RotL64(aOrbiterI, 11U) ^ aOrbiterK);
            aIngress = aIngress + (RotL64(aOrbiterB, 39U) ^ aOrbiterE);
            aIngress = aIngress + (aOrbiterD ^ RotL64(aOrbiterG, 24U));
            aIngress = aIngress + RotL64(aOrbiterJ, 29U);
            aIngress = TwistMix64::DiffuseA((aIngress + aScatter));
            //
            aWandererA = aWandererA + (((RotL64(aScatter, 47U) + aOrbiterK) + RotL64(aOrbiterI, 5U)) + RotL64(aCarry, 41U));
            aWandererJ = aWandererJ ^ ((RotL64(aCross, 21U) + RotL64(aOrbiterH, 37U)) + aOrbiterF);
            aWandererH = aWandererH + ((RotL64(aPrevious, 30U) + RotL64(aOrbiterE, 29U)) + aOrbiterD);
            aWandererD = aWandererD ^ ((RotL64(aIngress, 35U) + aOrbiterB) + RotL64(aOrbiterF, 22U));
            aWandererB = aWandererB + (((RotL64(aScatter, 3U) + RotL64(aOrbiterC, 43U)) + aOrbiterG) + aNonceWordO);
            aWandererG = aWandererG ^ (((RotL64(aIngress, 23U) + RotL64(aOrbiterK, 47U)) + aOrbiterB) + aPhaseEWandererUpdateSaltA[((aIndex + 22U)) & S_SALT1]);
            aWandererK = aWandererK + (((RotL64(aPrevious, 57U) + aOrbiterG) + RotL64(aOrbiterJ, 3U)) + aNonceWordM);
            aWandererC = aWandererC ^ (((RotL64(aCross, 19U) + RotL64(aOrbiterH, 13U)) + aOrbiterG) + aPhaseEWandererUpdateSaltD[((aIndex + 18U)) & S_SALT1]);
            aWandererI = aWandererI + (((RotL64(aPrevious, 11U) + aOrbiterF) + RotL64(aOrbiterE, 18U)) + RotL64(aCarry, 3U));
            aWandererE = aWandererE ^ ((RotL64(aCross, 54U) + aOrbiterB) + RotL64(aOrbiterG, 57U));
            aWandererF = aWandererF + ((RotL64(aScatter, 43U) + aOrbiterB) + RotL64(aOrbiterA, 51U));
            //
            aCarry = aCarry + (aWandererI ^ RotL64(aWandererJ, 60U));
            aCarry = aCarry + (RotL64(aWandererF, 19U) ^ aWandererC);
            aCarry = aCarry + (RotL64(aWandererK, 47U) ^ aWandererH);
            aCarry = aCarry + (RotL64(aWandererE, 35U) ^ aWandererA);
            aCarry = aCarry + (RotL64(aWandererB, 21U) ^ aWandererD);
            aCarry = aCarry + RotL64(aWandererG, 26U);
            aCarry = aCarry + RotL64(aIngress, 29U);
            aCarry = TwistMix64::DiffuseC(aCarry);
            //
            aOperationLaneB[S_BLOCK1 - aIndex] = aIngress;
        }
    
        // seed_loop_e loop 5
        // ingress from: aOperationLaneB, aFireLaneB, aFireLaneC
        // ingress directions: aOperationLaneB forward forced, aFireLaneB forward forced, aFireLaneC forward/backward random
        // cross from: aOperationLaneA, aFireLaneA, aInvestLaneA
        // cross directions: aOperationLaneA backward forced, aFireLaneA backward forced, aInvestLaneA backward/forward random
        // write to: aOperationLaneC
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aOperationLaneB[((aIndex + 26754U)) & S_BLOCK1], 51U) ^ RotL64(aFireLaneB[((aIndex + 26297U)) & S_BLOCK1], 60U));
            aIngress ^= RotL64(aFireLaneC[((S_BLOCK1 - aIndex + 25367U)) & S_BLOCK1], 19U);
            aIngress = TwistMix64::DiffuseC(((aIngress ^ aPhaseEDomainWordIngress) ^ aNonceWordO));
            //
            aCross = (RotL64(aOperationLaneA[((S_BLOCK1 - aIndex + 23693U)) & S_BLOCK1], 3U) ^ RotL64(aFireLaneA[((S_BLOCK1 - aIndex + 22520U)) & S_BLOCK1], 29U));
            aCross ^= RotL64(aInvestLaneA[((S_BLOCK1 - aIndex + 23531U)) & S_BLOCK1], 39U);
            aCross = TwistMix64::DiffuseB(((aCross ^ aPhaseEDomainWordCross) ^ aNonceWordP));
            //
            aScatter = (RotL64(aIngress, 40U) ^ RotL64(aCarry, 23U)) ^ (RotL64(aPrevious, 53U) + RotL64(aCross, 3U));
            aScatter = TwistMix64::DiffuseC(((aScatter ^ aPhaseEDomainWordScatter) ^ aNonceWordM));
            //
            aOrbiterK = ((aWandererI + RotL64(aCross, 54U)) + 7270044678408187242U) + aPhaseEOrbiterAssignSaltA[((aIndex + 9U)) & S_SALT1];
            aOrbiterJ = ((aWandererH + RotL64(aScatter, 43U)) + RotL64(aCarry, 23U)) + 10192278965379756766U;
            aOrbiterC = ((aWandererG + RotL64(aPrevious, 3U)) + RotL64(aCarry, 39U)) + 17568666746676060748U;
            aOrbiterF = ((aWandererB + RotL64(aIngress, 23U)) + 14312927531124963037U) + aNonceWordM;
            aOrbiterD = (aWandererA + RotL64(aPrevious, 12U)) + 9825825726152087706U;
            aOrbiterA = (aWandererK + RotL64(aIngress, 35U)) + 9696778570255265896U;
            aOrbiterG = (aWandererC + RotL64(aCross, 51U)) + 17657841352013417228U;
            aOrbiterI = ((aWandererF + RotL64(aScatter, 27U)) + 16207815085909628439U) + aNonceWordK;
            aOrbiterH = ((aWandererE + RotL64(aIngress, 37U)) + RotL64(aCarry, 57U)) + 1752979206374514227U;
            aOrbiterB = (((aWandererD + RotL64(aPrevious, 47U)) + 10456310689643905854U) + aPhaseEOrbiterAssignSaltD[((aIndex + 28U)) & S_SALT1]) + aNonceWordC;
            aOrbiterE = ((aWandererJ + RotL64(aScatter, 19U)) + 16127830548663742550U) + aNonceWordG;
            //
            aOrbiterK = (aOrbiterK + aOrbiterJ) + 2940917376003930842U;
            aOrbiterC = ((aOrbiterC ^ aOrbiterK) ^ 7353596864777649953U) ^ aPhaseEOrbiterUpdateSaltE[(((31U - aIndex) + 23U)) & S_SALT1];
            aOrbiterC = RotL64((aOrbiterC * 7499468723171042005U), 13U);
            //
            aOrbiterF = (aOrbiterF + aOrbiterD) + 12725092740446150705U;
            aOrbiterK = (aOrbiterK ^ aOrbiterF) ^ 5791296650856037010U;
            aOrbiterK = RotL64((aOrbiterK * 760379251950502133U), 27U);
            //
            aOrbiterA = ((aOrbiterA + aOrbiterG) + 1200130368046206150U) + aNonceWordI;
            aOrbiterF = (aOrbiterF ^ aOrbiterA) ^ 16689604428598558547U;
            aOrbiterF = RotL64((aOrbiterF * 13815324235939996623U), 57U);
            //
            aOrbiterJ = (aOrbiterJ + aOrbiterI) + 14359561591103730856U;
            aOrbiterH = (aOrbiterH ^ aOrbiterJ) ^ 3975025843599045263U;
            aOrbiterH = RotL64((aOrbiterH * 5025047888533298617U), 21U);
            //
            aOrbiterI = (aOrbiterI + aOrbiterF) + 14017901732955607601U;
            aOrbiterB = (aOrbiterB ^ aOrbiterI) ^ 10431526786489555196U;
            aOrbiterB = RotL64((aOrbiterB * 10181915874476132407U), 11U);
            //
            aOrbiterG = ((aOrbiterG + aOrbiterC) + 7320527073559849223U) + aPhaseEOrbiterUpdateSaltF[((aIndex + 14U)) & S_SALT1];
            aOrbiterD = (aOrbiterD ^ aOrbiterG) ^ 15333411223710709907U;
            aOrbiterD = RotL64((aOrbiterD * 3488684905528068775U), 37U);
            //
            aOrbiterE = (aOrbiterE + aOrbiterA) + 14302474063321663801U;
            aOrbiterI = (aOrbiterI ^ aOrbiterE) ^ 2104154521019935187U;
            aOrbiterI = RotL64((aOrbiterI * 12944382959742278055U), 39U);
            //
            aOrbiterC = (aOrbiterC + aOrbiterH) + 5167600586916325228U;
            aOrbiterE = (aOrbiterE ^ aOrbiterC) ^ 4566823109447208716U;
            aOrbiterE = RotL64((aOrbiterE * 9997799807454267443U), 53U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterE) + 12475580453805083495U;
            aOrbiterJ = (aOrbiterJ ^ aOrbiterD) ^ 15461491763911887974U;
            aOrbiterJ = RotL64((aOrbiterJ * 13548865386159287481U), 3U);
            //
            aOrbiterH = (aOrbiterH + aOrbiterB) + 11000532703581114393U;
            aOrbiterA = ((aOrbiterA ^ aOrbiterH) ^ 7815822789941347770U) ^ aPhaseEOrbiterUpdateSaltB[(((31U - aIndex) + 27U)) & S_SALT1];
            aOrbiterA = RotL64((aOrbiterA * 1476638214324946775U), 29U);
            //
            aOrbiterB = (((aOrbiterB + aOrbiterK) + 2166336159928211562U) + aPhaseEOrbiterUpdateSaltC[(((31U - aIndex) + 8U)) & S_SALT1]) + aNonceWordF;
            aOrbiterG = (aOrbiterG ^ aOrbiterB) ^ 7270044678408187242U;
            aOrbiterG = RotL64((aOrbiterG * 10648564933168714815U), 35U);
            //
            aIngress = RotL64(aOrbiterF, 41U) ^ aOrbiterJ;
            aIngress = aIngress + (RotL64(aOrbiterH, 29U) ^ aOrbiterD);
            aIngress = aIngress + (RotL64(aOrbiterI, 21U) ^ aOrbiterA);
            aIngress = aIngress + (aOrbiterK ^ RotL64(aOrbiterG, 5U));
            aIngress = aIngress + (aOrbiterE ^ RotL64(aOrbiterB, 35U));
            aIngress = aIngress + RotL64(aOrbiterC, 14U);
            aIngress = TwistMix64::DiffuseB((aIngress + aScatter));
            //
            aWandererE = aWandererE ^ ((RotL64(aIngress, 19U) + RotL64(aOrbiterB, 46U)) + aOrbiterH);
            aWandererC = aWandererC + (((RotL64(aPrevious, 5U) + aOrbiterK) + RotL64(aOrbiterB, 57U)) + RotL64(aCarry, 3U));
            aWandererG = aWandererG ^ ((RotL64(aScatter, 3U) + RotL64(aOrbiterF, 37U)) + aOrbiterH);
            aWandererD = aWandererD + (((RotL64(aCross, 41U) + RotL64(aOrbiterC, 35U)) + aOrbiterF) + RotL64(aCarry, 27U));
            aWandererJ = aWandererJ ^ ((RotL64(aPrevious, 23U) + RotL64(aOrbiterK, 19U)) + aOrbiterE);
            aWandererA = aWandererA + (((RotL64(aIngress, 21U) + aOrbiterG) + RotL64(aOrbiterD, 13U)) + aNonceWordA);
            aWandererI = aWandererI ^ (((RotL64(aScatter, 10U) + RotL64(aOrbiterI, 5U)) + aOrbiterD) + aPhaseEWandererUpdateSaltB[(((31U - aIndex) + 15U)) & S_SALT1]);
            aWandererF = aWandererF + (((RotL64(aCross, 53U) + RotL64(aOrbiterA, 43U)) + aOrbiterG) + aPhaseEWandererUpdateSaltC[(((31U - aIndex) + 26U)) & S_SALT1]);
            aWandererH = aWandererH ^ (((RotL64(aScatter, 37U) + RotL64(aOrbiterE, 11U)) + aOrbiterI) + aNonceWordN);
            aWandererK = aWandererK + ((RotL64(aCross, 35U) + RotL64(aOrbiterJ, 23U)) + aOrbiterH);
            aWandererB = aWandererB ^ ((RotL64(aIngress, 48U) + RotL64(aOrbiterC, 52U)) + aOrbiterK);
            //
            aCarry = aCarry + (RotL64(aWandererH, 56U) ^ aWandererG);
            aCarry = aCarry + (RotL64(aWandererB, 13U) ^ aWandererD);
            aCarry = aCarry + (RotL64(aWandererA, 5U) ^ aWandererF);
            aCarry = aCarry + (RotL64(aWandererC, 35U) ^ aWandererI);
            aCarry = aCarry + (RotL64(aWandererJ, 41U) ^ aWandererK);
            aCarry = aCarry + RotL64(aWandererE, 19U);
            aCarry = aCarry + RotL64(aIngress, 60U);
            aCarry = TwistMix64::DiffuseC(aCarry);
            //
            aOperationLaneC[aIndex] = aIngress;
        }
    
        // seed_loop_e loop 6
        // ingress from: aOperationLaneC, aOperationLaneA, aFireLaneD
        // ingress directions: aOperationLaneC forward forced, aOperationLaneA forward forced, aFireLaneD forward/backward random
        // cross from: aOperationLaneB, aInvestLaneB
        // cross directions: aOperationLaneB backward forced, aInvestLaneB backward/forward random
        // write to: aOperationLaneD
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aOperationLaneC[((aIndex + 27802U)) & S_BLOCK1], 5U) ^ RotL64(aOperationLaneA[((aIndex + 29614U)) & S_BLOCK1], 39U));
            aIngress ^= RotL64(aFireLaneD[((aIndex + 29056U)) & S_BLOCK1], 30U);
            aIngress = TwistMix64::DiffuseB(((aIngress ^ aPhaseEDomainWordIngress) ^ aNonceWordJ));
            //
            aCross = RotL64(aOperationLaneB[((S_BLOCK1 - aIndex + 29392U)) & S_BLOCK1], 13U) ^ RotL64(aInvestLaneB[((aIndex + 31836U)) & S_BLOCK1], 48U);
            aCross = TwistMix64::DiffuseB(((aCross ^ aPhaseEDomainWordCross) ^ aNonceWordA));
            //
            aScatter = (RotL64(aCarry, 13U) ^ RotL64(aIngress, 57U)) ^ (RotL64(aCross, 42U) + RotL64(aPrevious, 29U));
            aScatter = TwistMix64::DiffuseB(((aScatter ^ aPhaseEDomainWordScatter) ^ aNonceWordE));
            //
            aOrbiterC = ((aWandererF + RotL64(aPrevious, 29U)) + RotL64(aCarry, 3U)) + 18087125778766689269U;
            aOrbiterK = (aWandererK + RotL64(aScatter, 13U)) + 13710545066503235196U;
            aOrbiterA = ((aWandererE + RotL64(aCross, 23U)) + 1701939704736254645U) + aNonceWordF;
            aOrbiterG = (((aWandererH + RotL64(aIngress, 43U)) + RotL64(aCarry, 29U)) + 8064093611384019909U) + aNonceWordC;
            aOrbiterH = (aWandererG + RotL64(aPrevious, 10U)) + 16623332751533885431U;
            aOrbiterD = ((aWandererI + RotL64(aScatter, 35U)) + 15590129153794910109U) + aPhaseEOrbiterAssignSaltC[(((31U - aIndex) + 27U)) & S_SALT1];
            aOrbiterF = (aWandererJ + RotL64(aIngress, 53U)) + 7413312683079107383U;
            aOrbiterI = (aWandererD + RotL64(aCross, 57U)) + 4186064478651458810U;
            aOrbiterJ = (aWandererB + RotL64(aPrevious, 19U)) + 5501191643940735954U;
            aOrbiterB = ((aWandererC + RotL64(aScatter, 4U)) + 11064645242200570835U) + aPhaseEOrbiterAssignSaltF[((aIndex + 12U)) & S_SALT1];
            aOrbiterE = (((aWandererA + RotL64(aCross, 47U)) + RotL64(aCarry, 51U)) + 13825922087298055833U) + aNonceWordN;
            //
            aOrbiterC = (aOrbiterC + aOrbiterK) + 5944980709887369970U;
            aOrbiterA = ((aOrbiterA ^ aOrbiterC) ^ 8181136916070569646U) ^ aNonceWordD;
            aOrbiterA = RotL64((aOrbiterA * 395183021205661827U), 23U);
            //
            aOrbiterG = (aOrbiterG + aOrbiterH) + 15442336949157292482U;
            aOrbiterD = (aOrbiterD ^ aOrbiterG) ^ 11580554435240641337U;
            aOrbiterD = RotL64((aOrbiterD * 6654637892858767739U), 29U);
            //
            aOrbiterF = ((aOrbiterF + aOrbiterD) + 11240018128174598322U) + aPhaseEOrbiterUpdateSaltF[((aIndex + 9U)) & S_SALT1];
            aOrbiterK = ((aOrbiterK ^ aOrbiterF) ^ 2027565596050777471U) ^ aNonceWordE;
            aOrbiterK = RotL64((aOrbiterK * 18048186560314431815U), 57U);
            //
            aOrbiterK = (aOrbiterK + aOrbiterI) + 16425887196883725233U;
            aOrbiterJ = (aOrbiterJ ^ aOrbiterK) ^ 16828683527588834095U;
            aOrbiterJ = RotL64((aOrbiterJ * 17746289103235902485U), 39U);
            //
            aOrbiterB = (aOrbiterB + aOrbiterE) + 9923829146479008804U;
            aOrbiterH = (aOrbiterH ^ aOrbiterB) ^ 6669171007279929454U;
            aOrbiterH = RotL64((aOrbiterH * 681823450939955099U), 5U);
            //
            aOrbiterA = (aOrbiterA + aOrbiterJ) + 3902430046523165149U;
            aOrbiterE = (aOrbiterE ^ aOrbiterA) ^ 6739998149289590041U;
            aOrbiterE = RotL64((aOrbiterE * 2675037435528416821U), 19U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterC) + 16014401255534234075U;
            aOrbiterI = (aOrbiterI ^ aOrbiterD) ^ 14741857638680634564U;
            aOrbiterI = RotL64((aOrbiterI * 8723611021403369393U), 3U);
            //
            aOrbiterE = ((aOrbiterE + aOrbiterG) + 5064807861673260054U) + aPhaseEOrbiterUpdateSaltD[(((31U - aIndex) + 22U)) & S_SALT1];
            aOrbiterF = (aOrbiterF ^ aOrbiterE) ^ 968747317273200299U;
            aOrbiterF = RotL64((aOrbiterF * 14122304002722582329U), 51U);
            //
            aOrbiterH = (aOrbiterH + aOrbiterF) + 5282686212362051427U;
            aOrbiterC = (aOrbiterC ^ aOrbiterH) ^ 6902253563196129760U;
            aOrbiterC = RotL64((aOrbiterC * 7682808024658992049U), 11U);
            //
            aOrbiterI = ((aOrbiterI + aOrbiterA) + 4995580401402368332U) + aPhaseEOrbiterUpdateSaltE[((aIndex + 13U)) & S_SALT1];
            aOrbiterB = ((aOrbiterB ^ aOrbiterI) ^ 14949762584793646470U) ^ aNonceWordG;
            aOrbiterB = RotL64((aOrbiterB * 3539183342072953803U), 47U);
            //
            aOrbiterJ = ((aOrbiterJ + aOrbiterB) + 2378815735788107402U) + aPhaseEOrbiterUpdateSaltB[((aIndex + 14U)) & S_SALT1];
            aOrbiterG = (aOrbiterG ^ aOrbiterJ) ^ 18087125778766689269U;
            aOrbiterG = RotL64((aOrbiterG * 16799380528404446281U), 21U);
            //
            aIngress = aOrbiterD ^ RotL64(aOrbiterJ, 53U);
            aIngress = aIngress + (aOrbiterI ^ RotL64(aOrbiterH, 39U));
            aIngress = aIngress + (aOrbiterF ^ RotL64(aOrbiterE, 3U));
            aIngress = aIngress + (aOrbiterB ^ RotL64(aOrbiterG, 37U));
            aIngress = aIngress + (aOrbiterC ^ RotL64(aOrbiterK, 41U));
            aIngress = aIngress + RotL64(aOrbiterA, 20U);
            aIngress = TwistMix64::DiffuseA((aIngress + aScatter));
            //
            aWandererH = aWandererH ^ (((RotL64(aPrevious, 60U) + RotL64(aOrbiterC, 60U)) + aOrbiterH) + aNonceWordI);
            aWandererI = aWandererI + ((RotL64(aIngress, 39U) + RotL64(aOrbiterE, 47U)) + aOrbiterI);
            aWandererD = aWandererD ^ ((RotL64(aCross, 19U) + aOrbiterG) + RotL64(aOrbiterJ, 23U));
            aWandererB = aWandererB + ((RotL64(aScatter, 11U) + aOrbiterF) + RotL64(aOrbiterD, 37U));
            aWandererF = aWandererF ^ ((RotL64(aCross, 27U) + aOrbiterB) + RotL64(aOrbiterI, 51U));
            aWandererK = aWandererK + ((((RotL64(aPrevious, 53U) + RotL64(aOrbiterK, 21U)) + aOrbiterG) + RotL64(aCarry, 27U)) + aPhaseEWandererUpdateSaltF[(((31U - aIndex) + 3U)) & S_SALT1]);
            aWandererC = aWandererC ^ (((RotL64(aIngress, 3U) + RotL64(aOrbiterD, 3U)) + aOrbiterC) + aPhaseEWandererUpdateSaltE[(((31U - aIndex) + 16U)) & S_SALT1]);
            aWandererA = aWandererA + ((RotL64(aScatter, 44U) + RotL64(aOrbiterB, 39U)) + aOrbiterC);
            aWandererE = aWandererE ^ (((RotL64(aCross, 5U) + RotL64(aOrbiterK, 58U)) + aOrbiterC) + aNonceWordB);
            aWandererG = aWandererG + (((RotL64(aScatter, 47U) + RotL64(aOrbiterI, 11U)) + aOrbiterA) + RotL64(aCarry, 13U));
            aWandererJ = aWandererJ ^ ((RotL64(aPrevious, 57U) + RotL64(aOrbiterK, 43U)) + aOrbiterI);
            //
            aCarry = aCarry + (aWandererH ^ RotL64(aWandererE, 28U));
            aCarry = aCarry + (RotL64(aWandererD, 37U) ^ aWandererG);
            aCarry = aCarry + (RotL64(aWandererF, 11U) ^ aWandererJ);
            aCarry = aCarry + (RotL64(aWandererB, 5U) ^ aWandererC);
            aCarry = aCarry + (RotL64(aWandererK, 35U) ^ aWandererI);
            aCarry = aCarry + RotL64(aWandererA, 48U);
            aCarry = aCarry + RotL64(aIngress, 23U);
            aCarry = TwistMix64::DiffuseA(aCarry);
            //
            aOperationLaneD[S_BLOCK1 - aIndex] = aIngress;
        }
    }
    // GSeedRunSeed_E seed_loop_e (end)
    *pPrevious = aPrevious;
    *pIngress = aIngress;
    *pCarry = aCarry;
    *pWandererA = aWandererA;
    *pWandererB = aWandererB;
    *pWandererC = aWandererC;
    *pWandererD = aWandererD;
    *pWandererE = aWandererE;
    *pWandererF = aWandererF;
    *pWandererG = aWandererG;
    *pWandererH = aWandererH;
    *pWandererI = aWandererI;
    *pWandererJ = aWandererJ;
    *pWandererK = aWandererK;
}

void TwistExpander_Exercea_Arx::Seed_F(TwistWorkSpace *pWorkSpace,
                     std::uint64_t pNonce,
                     std::uint64_t *pPrevious,
                     std::uint64_t *pIngress,
                     std::uint64_t *pCarry,
                     std::uint64_t *pWandererA,
                     std::uint64_t *pWandererB,
                     std::uint64_t *pWandererC,
                     std::uint64_t *pWandererD,
                     std::uint64_t *pWandererE,
                     std::uint64_t *pWandererF,
                     std::uint64_t *pWandererG,
                     std::uint64_t *pWandererH,
                     std::uint64_t *pWandererI,
                     std::uint64_t *pWandererJ,
                     std::uint64_t *pWandererK) {
    [[maybe_unused]] std::uint8_t *aExpandLaneA = pWorkSpace->mExpansionLaneA;
    [[maybe_unused]] std::uint8_t *aExpandLaneB = pWorkSpace->mExpansionLaneB;
    [[maybe_unused]] std::uint8_t *aExpandLaneC = pWorkSpace->mExpansionLaneC;
    [[maybe_unused]] std::uint8_t *aExpandLaneD = pWorkSpace->mExpansionLaneD;
    [[maybe_unused]] std::uint8_t *aWorkLaneC = pWorkSpace->mWorkLaneC;
    [[maybe_unused]] std::uint8_t *aWorkLaneD = pWorkSpace->mWorkLaneD;
    [[maybe_unused]] std::uint8_t *aOperationLaneA = pWorkSpace->mOperationLaneA;
    [[maybe_unused]] std::uint8_t *aOperationLaneB = pWorkSpace->mOperationLaneB;
    [[maybe_unused]] std::uint8_t *aOperationLaneC = pWorkSpace->mOperationLaneC;
    [[maybe_unused]] std::uint8_t *aOperationLaneD = pWorkSpace->mOperationLaneD;
    [[maybe_unused]] std::uint8_t *aSnowLaneA = pWorkSpace->mSnowLaneA;
    [[maybe_unused]] std::uint8_t *aSnowLaneB = pWorkSpace->mSnowLaneB;
    [[maybe_unused]] std::uint8_t *aSnowLaneC = pWorkSpace->mSnowLaneC;
    [[maybe_unused]] std::uint8_t *aSnowLaneD = pWorkSpace->mSnowLaneD;
    [[maybe_unused]] std::uint8_t *aInvestLaneA = pWorkSpace->mInvestLaneA;
    [[maybe_unused]] std::uint8_t *aInvestLaneB = pWorkSpace->mInvestLaneB;
    [[maybe_unused]] std::uint8_t *aInvestLaneC = pWorkSpace->mInvestLaneC;
    [[maybe_unused]] std::uint8_t *aInvestLaneD = pWorkSpace->mInvestLaneD;
    [[maybe_unused]] std::uint64_t *aPhaseFOrbiterAssignSaltA = pWorkSpace->mDomainBundle.mPhaseFSalts.mOrbiterAssign.mSaltA;
    [[maybe_unused]] std::uint64_t *aPhaseFOrbiterAssignSaltB = pWorkSpace->mDomainBundle.mPhaseFSalts.mOrbiterAssign.mSaltB;
    [[maybe_unused]] std::uint64_t *aPhaseFOrbiterAssignSaltC = pWorkSpace->mDomainBundle.mPhaseFSalts.mOrbiterAssign.mSaltC;
    [[maybe_unused]] std::uint64_t *aPhaseFOrbiterAssignSaltD = pWorkSpace->mDomainBundle.mPhaseFSalts.mOrbiterAssign.mSaltD;
    [[maybe_unused]] std::uint64_t *aPhaseFOrbiterAssignSaltE = pWorkSpace->mDomainBundle.mPhaseFSalts.mOrbiterAssign.mSaltE;
    [[maybe_unused]] std::uint64_t *aPhaseFOrbiterAssignSaltF = pWorkSpace->mDomainBundle.mPhaseFSalts.mOrbiterAssign.mSaltF;
    [[maybe_unused]] std::uint64_t *aPhaseFOrbiterUpdateSaltA = pWorkSpace->mDomainBundle.mPhaseFSalts.mOrbiterUpdate.mSaltA;
    [[maybe_unused]] std::uint64_t *aPhaseFOrbiterUpdateSaltB = pWorkSpace->mDomainBundle.mPhaseFSalts.mOrbiterUpdate.mSaltB;
    [[maybe_unused]] std::uint64_t *aPhaseFOrbiterUpdateSaltC = pWorkSpace->mDomainBundle.mPhaseFSalts.mOrbiterUpdate.mSaltC;
    [[maybe_unused]] std::uint64_t *aPhaseFOrbiterUpdateSaltD = pWorkSpace->mDomainBundle.mPhaseFSalts.mOrbiterUpdate.mSaltD;
    [[maybe_unused]] std::uint64_t *aPhaseFOrbiterUpdateSaltE = pWorkSpace->mDomainBundle.mPhaseFSalts.mOrbiterUpdate.mSaltE;
    [[maybe_unused]] std::uint64_t *aPhaseFOrbiterUpdateSaltF = pWorkSpace->mDomainBundle.mPhaseFSalts.mOrbiterUpdate.mSaltF;
    [[maybe_unused]] std::uint64_t *aPhaseFWandererUpdateSaltA = pWorkSpace->mDomainBundle.mPhaseFSalts.mWandererUpdate.mSaltA;
    [[maybe_unused]] std::uint64_t *aPhaseFWandererUpdateSaltB = pWorkSpace->mDomainBundle.mPhaseFSalts.mWandererUpdate.mSaltB;
    [[maybe_unused]] std::uint64_t *aPhaseFWandererUpdateSaltC = pWorkSpace->mDomainBundle.mPhaseFSalts.mWandererUpdate.mSaltC;
    [[maybe_unused]] std::uint64_t *aPhaseFWandererUpdateSaltD = pWorkSpace->mDomainBundle.mPhaseFSalts.mWandererUpdate.mSaltD;
    [[maybe_unused]] std::uint64_t *aPhaseFWandererUpdateSaltE = pWorkSpace->mDomainBundle.mPhaseFSalts.mWandererUpdate.mSaltE;
    [[maybe_unused]] std::uint64_t *aPhaseFWandererUpdateSaltF = pWorkSpace->mDomainBundle.mPhaseFSalts.mWandererUpdate.mSaltF;
    const std::uint64_t &aPhaseFDomainWordIngress = pWorkSpace->mDomainBundle.mPhaseFConstants.mIngress;
    const std::uint64_t &aPhaseFDomainWordScatter = pWorkSpace->mDomainBundle.mPhaseFConstants.mScatter;
    const std::uint64_t &aPhaseFDomainWordCross = pWorkSpace->mDomainBundle.mPhaseFConstants.mCross;
    std::uint64_t aCross = 0; std::uint64_t aScatter = 0;

    std::uint64_t aOrbiterA = 0; std::uint64_t aOrbiterB = 0; std::uint64_t aOrbiterC = 0; std::uint64_t aOrbiterD = 0;
    std::uint64_t aOrbiterE = 0; std::uint64_t aOrbiterF = 0; std::uint64_t aOrbiterG = 0; std::uint64_t aOrbiterH = 0;
    std::uint64_t aOrbiterI = 0; std::uint64_t aOrbiterJ = 0; std::uint64_t aOrbiterK = 0;

    // [seed arx]
    [[maybe_unused]] std::uint8_t *mSource = pWorkSpace->mSource;
    std::uint64_t aPrevious = *pPrevious;
    std::uint64_t aIngress = *pIngress;
    std::uint64_t aCarry = *pCarry;
    std::uint64_t aWandererA = *pWandererA;
    std::uint64_t aWandererB = *pWandererB;
    std::uint64_t aWandererC = *pWandererC;
    std::uint64_t aWandererD = *pWandererD;
    std::uint64_t aWandererE = *pWandererE;
    std::uint64_t aWandererF = *pWandererF;
    std::uint64_t aWandererG = *pWandererG;
    std::uint64_t aWandererH = *pWandererH;
    std::uint64_t aWandererI = *pWandererI;
    std::uint64_t aWandererJ = *pWandererJ;
    std::uint64_t aWandererK = *pWandererK;
    std::uint64_t aNonceWordA = TwistMix64::DiffuseC(pNonce * 0x86AE4D7C58732697ULL + 0xEB5D35338AAB2F09ULL);
    std::uint64_t aNonceWordB = TwistMix64::DiffuseC(pNonce * 0xBB3D25AC887B1A11ULL + 0x8BD1336B3DB79D1BULL);
    std::uint64_t aNonceWordC = TwistMix64::DiffuseA(pNonce * 0x8B4F6E157CD99237ULL + 0x9872EBABD59A84F8ULL);
    std::uint64_t aNonceWordD = TwistMix64::DiffuseB(pNonce * 0xE26426089D2FF7DFULL + 0x8812D3D2D4252427ULL);
    std::uint64_t aNonceWordE = TwistMix64::DiffuseB(pNonce * 0xEB499A79B7E74BC1ULL + 0xFA40FE7247CF23D0ULL);
    std::uint64_t aNonceWordF = TwistMix64::DiffuseC(pNonce * 0xFDCBD3F867DE9559ULL + 0xFF093444BBB9E880ULL);
    std::uint64_t aNonceWordG = TwistMix64::DiffuseA(pNonce * 0x8D15361406D170A7ULL + 0xD9217A06A67CC3F6ULL);
    std::uint64_t aNonceWordH = TwistMix64::DiffuseB(pNonce * 0xF19CBABB9472D123ULL + 0xAF20FC2B2567343EULL);
    std::uint64_t aNonceWordI = TwistMix64::DiffuseC(pNonce * 0x967BAF041A152823ULL + 0xEAEE57E38957E705ULL);
    std::uint64_t aNonceWordJ = TwistMix64::DiffuseB(pNonce * 0xC1094455E250CD37ULL + 0xFBAE65A4EE9FA60CULL);
    std::uint64_t aNonceWordK = TwistMix64::DiffuseC(pNonce * 0xDCAF72B6113AF66DULL + 0xDB47556E42122286ULL);
    std::uint64_t aNonceWordL = TwistMix64::DiffuseB(pNonce * 0xE068A7C8DD2CD751ULL + 0xB22FFEE3FC670369ULL);
    std::uint64_t aNonceWordM = TwistMix64::DiffuseA(pNonce * 0xD1D92DE36AD164C3ULL + 0x8C86021CC7EF3A34ULL);
    std::uint64_t aNonceWordN = TwistMix64::DiffuseB(pNonce * 0xA10826816EC9ACA3ULL + 0x9E80ACEB722B3CAAULL);
    std::uint64_t aNonceWordO = TwistMix64::DiffuseA(pNonce * 0xE68EBCC592B59BDDULL + 0xF6E23E044BF6C4DBULL);
    std::uint64_t aNonceWordP = TwistMix64::DiffuseC(pNonce * 0xAD1FF3411B6B03BFULL + 0xBA2ACB98F358B063ULL);
    // GSeedRunSeed_F seed_loop_f (start)
    {
        // GSeedRunSeed_F seed_loop_f lane group
        // read from: aOperationLaneA, aOperationLaneB, aInvestLaneD, aOperationLaneC, aOperationLaneD, aInvestLaneB, aSnowLaneC, aInvestLaneA, aSnowLaneA, aSnowLaneD, aWorkLaneC, aExpandLaneA, aInvestLaneC, aExpandLaneB, aWorkLaneD, aExpandLaneC, aSnowLaneB
        // write to: aSnowLaneC, aSnowLaneD, aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD
    
        // seed_loop_f loop 1
        // ingress from: aOperationLaneA, aOperationLaneB, aInvestLaneD
        // ingress directions: aOperationLaneA forward forced, aOperationLaneB forward forced, aInvestLaneD forward/backward random
        // cross from: aOperationLaneC, aOperationLaneD, aInvestLaneB
        // cross directions: aOperationLaneC backward forced, aOperationLaneD backward forced, aInvestLaneB backward/forward random
        // write to: aSnowLaneC
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aOperationLaneA[((aIndex + 3969U)) & S_BLOCK1], 57U) ^ RotL64(aOperationLaneB[((aIndex + 3859U)) & S_BLOCK1], 27U));
            aIngress ^= RotL64(aInvestLaneD[((aIndex + 3421U)) & S_BLOCK1], 41U);
            aIngress = TwistMix64::DiffuseA(((aIngress ^ aPhaseFDomainWordIngress) ^ aNonceWordI));
            //
            aCross = (RotL64(aOperationLaneC[((S_BLOCK1 - aIndex + 722U)) & S_BLOCK1], 13U) ^ RotL64(aOperationLaneD[((S_BLOCK1 - aIndex + 4724U)) & S_BLOCK1], 53U));
            aCross ^= RotL64(aInvestLaneB[((S_BLOCK1 - aIndex + 1043U)) & S_BLOCK1], 35U);
            aCross = TwistMix64::DiffuseB(((aCross ^ aPhaseFDomainWordCross) ^ aNonceWordP));
            //
            aScatter = (RotL64(aIngress, 54U) + RotL64(aCross, 35U)) ^ (RotL64(aCarry, 5U) + RotL64(aPrevious, 19U));
            aScatter = TwistMix64::DiffuseA(((aScatter ^ aPhaseFDomainWordScatter) ^ aNonceWordA));
            //
            aOrbiterD = ((aWandererE + RotL64(aPrevious, 47U)) + 2783898056762489197U) + aPhaseFOrbiterAssignSaltB[(((31U - aIndex) + 13U)) & S_SALT1];
            aOrbiterG = ((aWandererD + RotL64(aScatter, 39U)) + RotL64(aCarry, 29U)) + 7177192902873343053U;
            aOrbiterJ = ((aWandererK + RotL64(aCross, 14U)) + 12254703232691980774U) + aNonceWordM;
            aOrbiterI = ((aWandererB + RotL64(aIngress, 27U)) + 15446547245691219559U) + aPhaseFOrbiterAssignSaltD[(((31U - aIndex) + 3U)) & S_SALT1];
            aOrbiterH = ((aWandererF + RotL64(aPrevious, 23U)) + RotL64(aCarry, 47U)) + 888475203006174856U;
            aOrbiterK = ((aWandererC + RotL64(aScatter, 5U)) + 3649183529366307877U) + aNonceWordD;
            aOrbiterE = (((aWandererA + RotL64(aCross, 43U)) + RotL64(aCarry, 5U)) + 4642631047518805167U) + aNonceWordF;
            aOrbiterF = ((aWandererG + RotL64(aIngress, 60U)) + 6108329730724782250U) + aNonceWordH;
            aOrbiterA = (aWandererH + RotL64(aPrevious, 35U)) + 8334054653023816636U;
            //
            aOrbiterD = (aOrbiterD + aOrbiterG) + 5891895375031474350U;
            aOrbiterJ = (aOrbiterJ ^ aOrbiterD) ^ 3176720746238477862U;
            aOrbiterJ = RotL64((aOrbiterJ * 1869961473768307911U), 5U);
            //
            aOrbiterI = (aOrbiterI + aOrbiterH) + 6111038696865301675U;
            aOrbiterK = (aOrbiterK ^ aOrbiterI) ^ 11914998302228682704U;
            aOrbiterK = RotL64((aOrbiterK * 11738924766359642853U), 43U);
            //
            aOrbiterK = ((aOrbiterK + aOrbiterE) + 17005063057791320948U) + aPhaseFOrbiterUpdateSaltD[((aIndex + 15U)) & S_SALT1];
            aOrbiterD = (aOrbiterD ^ aOrbiterK) ^ 18333780598768130670U;
            aOrbiterD = RotL64((aOrbiterD * 5416759844884107303U), 35U);
            //
            aOrbiterG = ((aOrbiterG + aOrbiterF) + 2056115016443263153U) + aPhaseFOrbiterUpdateSaltC[((aIndex + 4U)) & S_SALT1];
            aOrbiterI = ((aOrbiterI ^ aOrbiterG) ^ 10245512728872962677U) ^ aNonceWordE;
            aOrbiterI = RotL64((aOrbiterI * 707106795383284903U), 39U);
            //
            aOrbiterF = ((aOrbiterF + aOrbiterD) + 4810366069422162351U) + aPhaseFOrbiterUpdateSaltB[((aIndex + 25U)) & S_SALT1];
            aOrbiterH = (aOrbiterH ^ aOrbiterF) ^ 3051442983125942469U;
            aOrbiterH = RotL64((aOrbiterH * 13558537578054436423U), 23U);
            //
            aOrbiterJ = (aOrbiterJ + aOrbiterI) + 9285068547223654308U;
            aOrbiterA = ((aOrbiterA ^ aOrbiterJ) ^ 13067251130180968842U) ^ aPhaseFOrbiterUpdateSaltF[((aIndex + 29U)) & S_SALT1];
            aOrbiterA = RotL64((aOrbiterA * 7000687697769766605U), 57U);
            //
            aOrbiterE = (aOrbiterE + aOrbiterA) + 3203670242792002165U;
            aOrbiterG = (aOrbiterG ^ aOrbiterE) ^ 1770881716916463461U;
            aOrbiterG = RotL64((aOrbiterG * 13870229847371882171U), 19U);
            //
            aOrbiterA = (aOrbiterA + aOrbiterK) + 16286823712870537410U;
            aOrbiterF = ((aOrbiterF ^ aOrbiterA) ^ 13067191141829694202U) ^ aNonceWordG;
            aOrbiterF = RotL64((aOrbiterF * 15629974528467350445U), 53U);
            //
            aOrbiterH = ((aOrbiterH + aOrbiterJ) + 3414576315085336932U) + aNonceWordO;
            aOrbiterE = ((aOrbiterE ^ aOrbiterH) ^ 8979691827341555245U) ^ aNonceWordK;
            aOrbiterE = RotL64((aOrbiterE * 15971594804040295757U), 29U);
            //
            aIngress = RotL64(aOrbiterD, 23U) ^ aOrbiterI;
            aIngress = aIngress + (RotL64(aOrbiterG, 47U) ^ aOrbiterK);
            aIngress = aIngress + (RotL64(aOrbiterH, 35U) ^ aOrbiterA);
            aIngress = aIngress + (aOrbiterJ ^ RotL64(aOrbiterE, 11U));
            aIngress = aIngress + RotL64(aOrbiterF, 56U);
            aIngress = TwistMix64::DiffuseA((aIngress + aScatter));
            //
            aWandererG = aWandererG + (((RotL64(aScatter, 11U) + RotL64(aOrbiterG, 3U)) + aOrbiterI) + RotL64(aCarry, 37U));
            aWandererA = aWandererA ^ ((((RotL64(aPrevious, 20U) + RotL64(aOrbiterA, 51U)) + aOrbiterD) + aNonceWordL) + aPhaseFWandererUpdateSaltD[(((31U - aIndex) + 27U)) & S_SALT1]);
            aWandererF = aWandererF + (((RotL64(aIngress, 35U) + RotL64(aOrbiterD, 13U)) + aOrbiterF) + RotL64(aCarry, 19U));
            aWandererE = aWandererE ^ (((RotL64(aCross, 47U) + aOrbiterH) + RotL64(aOrbiterJ, 58U)) + aPhaseFWandererUpdateSaltB[(((31U - aIndex) + 14U)) & S_SALT1]);
            aWandererK = aWandererK + ((RotL64(aIngress, 5U) + RotL64(aOrbiterI, 47U)) + aOrbiterE);
            aWandererB = aWandererB ^ ((RotL64(aScatter, 41U) + RotL64(aOrbiterF, 29U)) + aOrbiterG);
            aWandererC = aWandererC + (((RotL64(aPrevious, 30U) + RotL64(aOrbiterA, 43U)) + aOrbiterJ) + aNonceWordC);
            aWandererD = aWandererD ^ (((RotL64(aCross, 57U) + RotL64(aOrbiterE, 35U)) + aOrbiterK) + aNonceWordA);
            aWandererH = aWandererH + ((RotL64(aScatter, 51U) + aOrbiterJ) + RotL64(aOrbiterE, 22U));
            //
            aCarry = aCarry + (RotL64(aWandererH, 50U) ^ aWandererC);
            aCarry = aCarry + (aWandererD ^ RotL64(aWandererB, 53U));
            aCarry = aCarry + (aWandererA ^ RotL64(aWandererF, 43U));
            aCarry = aCarry + (RotL64(aWandererE, 47U) ^ aWandererG);
            aCarry = aCarry + RotL64(aWandererK, 23U);
            aCarry = aCarry + RotL64(aIngress, 35U);
            aCarry = TwistMix64::DiffuseA(aCarry);
            //
            aSnowLaneC[aIndex] = aIngress;
        }
    
        // seed_loop_f loop 2
        // ingress from: aSnowLaneC, aOperationLaneC, aOperationLaneD, aInvestLaneA
        // ingress directions: aSnowLaneC forward forced, aOperationLaneC forward forced, aOperationLaneD forward forced, aInvestLaneA forward/backward random
        // cross from: aOperationLaneA, aOperationLaneB, aSnowLaneA
        // cross directions: aOperationLaneA backward forced, aOperationLaneB backward forced, aSnowLaneA backward/forward random
        // write to: aSnowLaneD
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aSnowLaneC[((aIndex + 10233U)) & S_BLOCK1], 19U) ^ RotL64(aOperationLaneC[((aIndex + 6793U)) & S_BLOCK1], 58U));
            aIngress ^= (RotL64(aOperationLaneD[((aIndex + 8138U)) & S_BLOCK1], 39U) ^ RotL64(aInvestLaneA[((aIndex + 9505U)) & S_BLOCK1], 3U));
            aIngress = TwistMix64::DiffuseA(((aIngress ^ aPhaseFDomainWordIngress) ^ aNonceWordI));
            //
            aCross = (RotL64(aOperationLaneA[((S_BLOCK1 - aIndex + 9433U)) & S_BLOCK1], 23U) ^ RotL64(aOperationLaneB[((S_BLOCK1 - aIndex + 7161U)) & S_BLOCK1], 5U));
            aCross ^= RotL64(aSnowLaneA[((aIndex + 10881U)) & S_BLOCK1], 37U);
            aCross = TwistMix64::DiffuseB(((aCross ^ aPhaseFDomainWordCross) ^ aNonceWordD));
            //
            aScatter = (RotL64(aIngress, 39U) ^ RotL64(aCarry, 5U)) + (RotL64(aPrevious, 23U) ^ RotL64(aCross, 52U));
            aScatter = TwistMix64::DiffuseA(((aScatter ^ aPhaseFDomainWordScatter) ^ aNonceWordE));
            //
            aOrbiterG = (aWandererH + RotL64(aIngress, 10U)) + 6916817163240024692U;
            aOrbiterE = ((aWandererI + RotL64(aCross, 5U)) + 14554930751292077817U) + aNonceWordG;
            aOrbiterD = ((((aWandererF + RotL64(aPrevious, 47U)) + RotL64(aCarry, 13U)) + 1098305064484336101U) + aPhaseFOrbiterAssignSaltE[(((31U - aIndex) + 14U)) & S_SALT1]) + aNonceWordF;
            aOrbiterA = ((aWandererJ + RotL64(aScatter, 35U)) + RotL64(aCarry, 53U)) + 12192821172420471527U;
            aOrbiterJ = ((aWandererE + RotL64(aCross, 39U)) + RotL64(aCarry, 37U)) + 2435134991707318845U;
            aOrbiterF = ((aWandererG + RotL64(aScatter, 53U)) + 1896745368738512624U) + aNonceWordM;
            aOrbiterB = (aWandererA + RotL64(aIngress, 14U)) + 1114996424222923873U;
            aOrbiterC = (aWandererK + RotL64(aPrevious, 21U)) + 9839135798371512656U;
            aOrbiterK = ((aWandererB + RotL64(aIngress, 27U)) + 8037967239603177043U) + aPhaseFOrbiterAssignSaltC[((aIndex + 23U)) & S_SALT1];
            //
            aOrbiterG = ((aOrbiterG + aOrbiterE) + 15185468738487237432U) + aNonceWordJ;
            aOrbiterD = (((aOrbiterD ^ aOrbiterG) ^ 4912098316394854543U) ^ aPhaseFOrbiterUpdateSaltB[((aIndex + 27U)) & S_SALT1]) ^ aNonceWordA;
            aOrbiterD = RotL64((aOrbiterD * 3072785550384399929U), 57U);
            //
            aOrbiterA = (aOrbiterA + aOrbiterJ) + 13142688607850380888U;
            aOrbiterF = (aOrbiterF ^ aOrbiterA) ^ 4507379759608945839U;
            aOrbiterF = RotL64((aOrbiterF * 2989332387754215967U), 27U);
            //
            aOrbiterB = ((aOrbiterB + aOrbiterF) + 7299006009652289342U) + aPhaseFOrbiterUpdateSaltC[(((31U - aIndex) + 13U)) & S_SALT1];
            aOrbiterE = (aOrbiterE ^ aOrbiterB) ^ 5390655277207053627U;
            aOrbiterE = RotL64((aOrbiterE * 10973744708856143715U), 47U);
            //
            aOrbiterC = ((aOrbiterC + aOrbiterB) + 6744737023577785725U) + aPhaseFOrbiterUpdateSaltE[(((31U - aIndex) + 25U)) & S_SALT1];
            aOrbiterG = (aOrbiterG ^ aOrbiterC) ^ 15539737698867067285U;
            aOrbiterG = RotL64((aOrbiterG * 4686092035261336911U), 51U);
            //
            aOrbiterK = (aOrbiterK + aOrbiterG) + 13329866734681377952U;
            aOrbiterJ = ((aOrbiterJ ^ aOrbiterK) ^ 13284937458969166257U) ^ aPhaseFOrbiterUpdateSaltA[(((31U - aIndex) + 21U)) & S_SALT1];
            aOrbiterJ = RotL64((aOrbiterJ * 3965985432462699445U), 21U);
            //
            aOrbiterE = (aOrbiterE + aOrbiterK) + 8695002088915702168U;
            aOrbiterA = (aOrbiterA ^ aOrbiterE) ^ 3858059421620839286U;
            aOrbiterA = RotL64((aOrbiterA * 9559783727301092937U), 35U);
            //
            aOrbiterJ = ((aOrbiterJ + aOrbiterD) + 6609163873243179836U) + aNonceWordN;
            aOrbiterC = (aOrbiterC ^ aOrbiterJ) ^ 9416165620556710540U;
            aOrbiterC = RotL64((aOrbiterC * 240385043740268229U), 3U);
            //
            aOrbiterF = (aOrbiterF + aOrbiterC) + 1578449067529000433U;
            aOrbiterK = (aOrbiterK ^ aOrbiterF) ^ 14309000104419489303U;
            aOrbiterK = RotL64((aOrbiterK * 7599078306153684729U), 11U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterA) + 15785180680737461320U;
            aOrbiterB = (aOrbiterB ^ aOrbiterD) ^ 10099222679918382021U;
            aOrbiterB = RotL64((aOrbiterB * 2012232597046182581U), 39U);
            //
            aIngress = aOrbiterJ ^ RotL64(aOrbiterF, 23U);
            aIngress = aIngress + (aOrbiterC ^ RotL64(aOrbiterE, 37U));
            aIngress = aIngress + (RotL64(aOrbiterG, 41U) ^ aOrbiterK);
            aIngress = aIngress + (RotL64(aOrbiterB, 47U) ^ aOrbiterA);
            aIngress = aIngress + RotL64(aOrbiterD, 10U);
            aIngress = TwistMix64::DiffuseC((aIngress + aScatter));
            //
            aWandererF = aWandererF + ((RotL64(aCross, 58U) + RotL64(aOrbiterK, 51U)) + aOrbiterB);
            aWandererG = aWandererG ^ (((RotL64(aIngress, 13U) + RotL64(aOrbiterB, 34U)) + aOrbiterJ) + aNonceWordK);
            aWandererA = aWandererA + ((((RotL64(aScatter, 5U) + RotL64(aOrbiterG, 19U)) + aOrbiterK) + RotL64(aCarry, 57U)) + aNonceWordB);
            aWandererI = aWandererI ^ ((RotL64(aPrevious, 23U) + RotL64(aOrbiterB, 27U)) + aOrbiterC);
            aWandererH = aWandererH + ((((RotL64(aCross, 35U) + RotL64(aOrbiterD, 57U)) + aOrbiterF) + aNonceWordE) + aPhaseFWandererUpdateSaltC[((aIndex + 28U)) & S_SALT1]);
            aWandererK = aWandererK ^ (((RotL64(aPrevious, 39U) + RotL64(aOrbiterD, 23U)) + aOrbiterK) + aNonceWordC);
            aWandererE = aWandererE + ((((RotL64(aIngress, 52U) + aOrbiterC) + RotL64(aOrbiterE, 47U)) + RotL64(aCarry, 47U)) + aPhaseFWandererUpdateSaltF[(((31U - aIndex) + 24U)) & S_SALT1]);
            aWandererJ = aWandererJ ^ ((RotL64(aScatter, 47U) + RotL64(aOrbiterJ, 43U)) + aOrbiterK);
            aWandererB = aWandererB + ((RotL64(aCross, 29U) + aOrbiterD) + RotL64(aOrbiterA, 14U));
            //
            aCarry = aCarry + (aWandererB ^ RotL64(aWandererE, 39U));
            aCarry = aCarry + (aWandererH ^ RotL64(aWandererI, 53U));
            aCarry = aCarry + (RotL64(aWandererG, 43U) ^ aWandererK);
            aCarry = aCarry + (aWandererF ^ RotL64(aWandererA, 23U));
            aCarry = aCarry + RotL64(aWandererJ, 14U);
            aCarry = aCarry + RotL64(aIngress, 3U);
            aCarry = TwistMix64::DiffuseC(aCarry);
            //
            aSnowLaneD[S_BLOCK1 - aIndex] = aIngress;
        }
    
        // seed_loop_f loop 3
        // ingress from: aSnowLaneD, aOperationLaneA, aWorkLaneC
        // ingress directions: aSnowLaneD forward forced, aOperationLaneA forward forced, aWorkLaneC forward/backward random
        // cross from: aSnowLaneC, aOperationLaneC
        // cross directions: aSnowLaneC backward forced, aOperationLaneC backward/forward random
        // write to: aExpandLaneA
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aSnowLaneD[((aIndex + 11635U)) & S_BLOCK1], 39U) ^ RotL64(aOperationLaneA[((aIndex + 16222U)) & S_BLOCK1], 13U));
            aIngress ^= RotL64(aWorkLaneC[((S_BLOCK1 - aIndex + 13046U)) & S_BLOCK1], 54U);
            aIngress = TwistMix64::DiffuseC(((aIngress ^ aPhaseFDomainWordIngress) ^ aNonceWordA));
            //
            aCross = RotL64(aSnowLaneC[((S_BLOCK1 - aIndex + 12410U)) & S_BLOCK1], 3U) ^ RotL64(aOperationLaneC[((S_BLOCK1 - aIndex + 16373U)) & S_BLOCK1], 23U);
            aCross = TwistMix64::DiffuseA(((aCross ^ aPhaseFDomainWordCross) ^ aNonceWordF));
            //
            aScatter = (RotL64(aPrevious, 23U) ^ RotL64(aCarry, 39U)) ^ (RotL64(aCross, 6U) + RotL64(aIngress, 57U));
            aScatter = TwistMix64::DiffuseB(((aScatter ^ aPhaseFDomainWordScatter) ^ aNonceWordN));
            //
            aOrbiterK = ((aWandererG + RotL64(aPrevious, 30U)) + RotL64(aCarry, 13U)) + 3448371607470865612U;
            aOrbiterD = ((aWandererJ + RotL64(aIngress, 51U)) + 3743742913651580573U) + aPhaseFOrbiterAssignSaltA[((aIndex + 12U)) & S_SALT1];
            aOrbiterB = (aWandererK + RotL64(aCross, 3U)) + 13069491287948807280U;
            aOrbiterG = ((aWandererH + RotL64(aScatter, 35U)) + RotL64(aCarry, 47U)) + 16872779275586545632U;
            aOrbiterE = ((((aWandererC + RotL64(aCross, 47U)) + RotL64(aCarry, 23U)) + 17945792656755062795U) + aPhaseFOrbiterAssignSaltF[((aIndex + 8U)) & S_SALT1]) + aNonceWordL;
            aOrbiterC = (aWandererB + RotL64(aScatter, 13U)) + 18199747196793731853U;
            aOrbiterA = (aWandererI + RotL64(aPrevious, 39U)) + 15953311878379809513U;
            aOrbiterI = (aWandererE + RotL64(aIngress, 57U)) + 941268763494588338U;
            aOrbiterF = ((aWandererF + RotL64(aPrevious, 26U)) + 10090221530365796809U) + aNonceWordI;
            //
            aOrbiterK = ((aOrbiterK + aOrbiterD) + 8335698093307607001U) + aNonceWordO;
            aOrbiterB = ((aOrbiterB ^ aOrbiterK) ^ 6147498804734306100U) ^ aNonceWordG;
            aOrbiterB = RotL64((aOrbiterB * 6904444049941211327U), 29U);
            //
            aOrbiterB = (aOrbiterB + aOrbiterG) + 5980246079567570090U;
            aOrbiterE = ((aOrbiterE ^ aOrbiterB) ^ 4152167624425912978U) ^ aNonceWordH;
            aOrbiterE = RotL64((aOrbiterE * 10019421651535123573U), 39U);
            //
            aOrbiterG = (aOrbiterG + aOrbiterC) + 14990418790239735916U;
            aOrbiterK = (aOrbiterK ^ aOrbiterG) ^ 3418668387496597219U;
            aOrbiterK = RotL64((aOrbiterK * 12814077238529863119U), 35U);
            //
            aOrbiterA = (aOrbiterA + aOrbiterE) + 4206650904177199425U;
            aOrbiterI = (aOrbiterI ^ aOrbiterA) ^ 3905470780938996069U;
            aOrbiterI = RotL64((aOrbiterI * 16030122739273137005U), 51U);
            //
            aOrbiterC = ((aOrbiterC + aOrbiterA) + 9968672788233080924U) + aPhaseFOrbiterUpdateSaltE[(((31U - aIndex) + 16U)) & S_SALT1];
            aOrbiterD = (aOrbiterD ^ aOrbiterC) ^ 602258075661864866U;
            aOrbiterD = RotL64((aOrbiterD * 2615726693066300065U), 11U);
            //
            aOrbiterI = (aOrbiterI + aOrbiterF) + 17751667243048041383U;
            aOrbiterC = ((aOrbiterC ^ aOrbiterI) ^ 2414054413585296027U) ^ aPhaseFOrbiterUpdateSaltF[((aIndex + 15U)) & S_SALT1];
            aOrbiterC = RotL64((aOrbiterC * 1049512574773201893U), 3U);
            //
            aOrbiterE = ((aOrbiterE + aOrbiterK) + 6523322402744047752U) + aPhaseFOrbiterUpdateSaltD[((aIndex + 29U)) & S_SALT1];
            aOrbiterF = ((aOrbiterF ^ aOrbiterE) ^ 6729901917767398779U) ^ aPhaseFOrbiterUpdateSaltC[((aIndex + 17U)) & S_SALT1];
            aOrbiterF = RotL64((aOrbiterF * 8039939871405367139U), 23U);
            //
            aOrbiterD = ((aOrbiterD + aOrbiterI) + 11460169185076814539U) + aNonceWordB;
            aOrbiterG = (aOrbiterG ^ aOrbiterD) ^ 7559640379553110573U;
            aOrbiterG = RotL64((aOrbiterG * 9864654321914036135U), 47U);
            //
            aOrbiterF = (aOrbiterF + aOrbiterB) + 17271150091827475028U;
            aOrbiterA = (aOrbiterA ^ aOrbiterF) ^ 3541809324556914646U;
            aOrbiterA = RotL64((aOrbiterA * 12655168871428868639U), 19U);
            //
            aIngress = RotL64(aOrbiterK, 57U) ^ aOrbiterB;
            aIngress = aIngress + (aOrbiterD ^ RotL64(aOrbiterF, 34U));
            aIngress = aIngress + (RotL64(aOrbiterG, 43U) ^ aOrbiterI);
            aIngress = aIngress + (RotL64(aOrbiterE, 53U) ^ aOrbiterC);
            aIngress = aIngress + RotL64(aOrbiterA, 3U);
            aIngress = TwistMix64::DiffuseB((aIngress + aScatter));
            //
            aWandererE = aWandererE ^ ((RotL64(aScatter, 21U) + RotL64(aOrbiterC, 35U)) + aOrbiterG);
            aWandererH = aWandererH + (((RotL64(aPrevious, 27U) + aOrbiterE) + RotL64(aOrbiterI, 19U)) + aNonceWordN);
            aWandererK = aWandererK ^ ((RotL64(aCross, 56U) + aOrbiterB) + RotL64(aOrbiterI, 60U));
            aWandererI = aWandererI + ((((RotL64(aIngress, 39U) + RotL64(aOrbiterG, 43U)) + aOrbiterE) + RotL64(aCarry, 37U)) + aNonceWordE);
            aWandererJ = aWandererJ ^ (((RotL64(aScatter, 47U) + aOrbiterA) + RotL64(aOrbiterD, 13U)) + aPhaseFWandererUpdateSaltE[((aIndex + 23U)) & S_SALT1]);
            aWandererB = aWandererB + ((RotL64(aIngress, 13U) + aOrbiterE) + RotL64(aOrbiterF, 5U));
            aWandererF = aWandererF ^ (((RotL64(aPrevious, 43U) + aOrbiterA) + RotL64(aOrbiterE, 23U)) + aNonceWordC);
            aWandererG = aWandererG + ((((RotL64(aCross, 6U) + RotL64(aOrbiterF, 54U)) + aOrbiterA) + RotL64(aCarry, 3U)) + aNonceWordD);
            aWandererC = aWandererC ^ (((RotL64(aIngress, 35U) + aOrbiterK) + RotL64(aOrbiterC, 29U)) + aPhaseFWandererUpdateSaltA[(((31U - aIndex) + 22U)) & S_SALT1]);
            //
            aCarry = aCarry + (RotL64(aWandererI, 43U) ^ aWandererK);
            aCarry = aCarry + (RotL64(aWandererJ, 51U) ^ aWandererE);
            aCarry = aCarry + (RotL64(aWandererB, 39U) ^ aWandererH);
            aCarry = aCarry + (aWandererC ^ RotL64(aWandererG, 58U));
            aCarry = aCarry + RotL64(aWandererF, 29U);
            aCarry = aCarry + RotL64(aIngress, 5U);
            aCarry = TwistMix64::DiffuseA(aCarry);
            //
            aExpandLaneA[aIndex] = aIngress;
        }
    
        // seed_loop_f loop 4
        // ingress from: aExpandLaneA, aSnowLaneC, aInvestLaneC
        // ingress directions: aExpandLaneA forward forced, aSnowLaneC forward forced, aInvestLaneC forward/backward random
        // cross from: aSnowLaneD, aOperationLaneD
        // cross directions: aSnowLaneD backward forced, aOperationLaneD backward/forward random
        // write to: aExpandLaneB
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aExpandLaneA[((aIndex + 21569U)) & S_BLOCK1], 22U) ^ RotL64(aSnowLaneC[((aIndex + 21586U)) & S_BLOCK1], 5U));
            aIngress ^= RotL64(aInvestLaneC[((S_BLOCK1 - aIndex + 17740U)) & S_BLOCK1], 51U);
            aIngress = TwistMix64::DiffuseC(((aIngress ^ aPhaseFDomainWordIngress) ^ aNonceWordF));
            //
            aCross = RotL64(aSnowLaneD[((S_BLOCK1 - aIndex + 18244U)) & S_BLOCK1], 29U) ^ RotL64(aOperationLaneD[((S_BLOCK1 - aIndex + 19570U)) & S_BLOCK1], 57U);
            aCross = TwistMix64::DiffuseB(((aCross ^ aPhaseFDomainWordCross) ^ aNonceWordJ));
            //
            aScatter = (RotL64(aCross, 10U) ^ RotL64(aIngress, 41U)) + (RotL64(aPrevious, 29U) ^ RotL64(aCarry, 53U));
            aScatter = TwistMix64::DiffuseB(((aScatter ^ aPhaseFDomainWordScatter) ^ aNonceWordJ));
            //
            aOrbiterF = ((aWandererG + RotL64(aCross, 21U)) + 12690502671561165478U) + aNonceWordO;
            aOrbiterD = ((aWandererH + RotL64(aScatter, 3U)) + 17519943923428102801U) + aNonceWordC;
            aOrbiterI = (aWandererA + RotL64(aIngress, 39U)) + 10705515807975331385U;
            aOrbiterE = ((aWandererK + RotL64(aPrevious, 12U)) + 16586447272278538179U) + aNonceWordB;
            aOrbiterC = (((aWandererF + RotL64(aScatter, 53U)) + RotL64(aCarry, 29U)) + 8006560996840971798U) + aPhaseFOrbiterAssignSaltB[(((31U - aIndex) + 12U)) & S_SALT1];
            aOrbiterJ = ((aWandererJ + RotL64(aPrevious, 57U)) + RotL64(aCarry, 19U)) + 12928600185788857701U;
            aOrbiterK = ((aWandererC + RotL64(aIngress, 29U)) + 14240723153798267172U) + aNonceWordA;
            aOrbiterG = (((aWandererD + RotL64(aCross, 34U)) + RotL64(aCarry, 47U)) + 8636219177994872072U) + aPhaseFOrbiterAssignSaltD[((aIndex + 20U)) & S_SALT1];
            aOrbiterA = (aWandererE + RotL64(aIngress, 47U)) + 7586790235186467512U;
            //
            aOrbiterF = (aOrbiterF + aOrbiterD) + 1103807034179512424U;
            aOrbiterI = (aOrbiterI ^ aOrbiterF) ^ 7547526530239498693U;
            aOrbiterI = RotL64((aOrbiterI * 3360295583636013509U), 41U);
            //
            aOrbiterE = (aOrbiterE + aOrbiterC) + 8380239679344786397U;
            aOrbiterJ = (aOrbiterJ ^ aOrbiterE) ^ 5690809173787433519U;
            aOrbiterJ = RotL64((aOrbiterJ * 5354724308093372953U), 3U);
            //
            aOrbiterC = ((aOrbiterC + aOrbiterK) + 8390902801141804609U) + aPhaseFOrbiterUpdateSaltB[((aIndex + 23U)) & S_SALT1];
            aOrbiterG = ((aOrbiterG ^ aOrbiterC) ^ 3507306189192059486U) ^ aNonceWordM;
            aOrbiterG = RotL64((aOrbiterG * 18336280496510253103U), 19U);
            //
            aOrbiterG = (aOrbiterG + aOrbiterF) + 6190745292098482871U;
            aOrbiterA = ((aOrbiterA ^ aOrbiterG) ^ 8065418693975056902U) ^ aNonceWordP;
            aOrbiterA = RotL64((aOrbiterA * 6414621418430102589U), 11U);
            //
            aOrbiterI = (aOrbiterI + aOrbiterE) + 12111755051718111803U;
            aOrbiterK = ((aOrbiterK ^ aOrbiterI) ^ 7605877769709909297U) ^ aNonceWordE;
            aOrbiterK = RotL64((aOrbiterK * 17525248694315944599U), 27U);
            //
            aOrbiterA = ((aOrbiterA + aOrbiterI) + 5969794501112646237U) + aPhaseFOrbiterUpdateSaltC[((aIndex + 6U)) & S_SALT1];
            aOrbiterC = (aOrbiterC ^ aOrbiterA) ^ 5127559299360591476U;
            aOrbiterC = RotL64((aOrbiterC * 4521563633438853069U), 57U);
            //
            aOrbiterJ = ((aOrbiterJ + aOrbiterG) + 10593847754747739786U) + aPhaseFOrbiterUpdateSaltF[(((31U - aIndex) + 15U)) & S_SALT1];
            aOrbiterD = (aOrbiterD ^ aOrbiterJ) ^ 4401750688524310121U;
            aOrbiterD = RotL64((aOrbiterD * 14265829318976633707U), 23U);
            //
            aOrbiterD = ((aOrbiterD + aOrbiterA) + 6927893132508779499U) + aPhaseFOrbiterUpdateSaltA[(((31U - aIndex) + 25U)) & S_SALT1];
            aOrbiterE = (aOrbiterE ^ aOrbiterD) ^ 4874009978647014479U;
            aOrbiterE = RotL64((aOrbiterE * 13340466017023540755U), 35U);
            //
            aOrbiterK = (aOrbiterK + aOrbiterJ) + 13146693487138744677U;
            aOrbiterF = (aOrbiterF ^ aOrbiterK) ^ 3298472134223595298U;
            aOrbiterF = RotL64((aOrbiterF * 2145005258008477281U), 51U);
            //
            aIngress = RotL64(aOrbiterF, 10U) ^ aOrbiterA;
            aIngress = aIngress + (aOrbiterE ^ RotL64(aOrbiterJ, 43U));
            aIngress = aIngress + (aOrbiterD ^ RotL64(aOrbiterC, 5U));
            aIngress = aIngress + (aOrbiterG ^ RotL64(aOrbiterI, 29U));
            aIngress = aIngress + RotL64(aOrbiterK, 57U);
            aIngress = TwistMix64::DiffuseB((aIngress + aScatter));
            //
            aWandererA = aWandererA + ((RotL64(aCross, 47U) + aOrbiterJ) + RotL64(aOrbiterD, 43U));
            aWandererF = aWandererF ^ ((RotL64(aPrevious, 53U) + RotL64(aOrbiterJ, 10U)) + aOrbiterK);
            aWandererJ = aWandererJ + (((((RotL64(aScatter, 19U) + RotL64(aOrbiterC, 27U)) + aOrbiterJ) + RotL64(aCarry, 41U)) + aNonceWordG) + aPhaseFWandererUpdateSaltB[((aIndex + 4U)) & S_SALT1]);
            aWandererH = aWandererH ^ (((RotL64(aIngress, 28U) + RotL64(aOrbiterD, 57U)) + aOrbiterE) + aNonceWordH);
            aWandererK = aWandererK + (((RotL64(aCross, 23U) + aOrbiterG) + RotL64(aOrbiterJ, 51U)) + aNonceWordK);
            aWandererC = aWandererC ^ ((RotL64(aScatter, 5U) + RotL64(aOrbiterA, 37U)) + aOrbiterD);
            aWandererE = aWandererE + (((RotL64(aIngress, 37U) + aOrbiterD) + RotL64(aOrbiterF, 47U)) + RotL64(aCarry, 3U));
            aWandererD = aWandererD ^ ((RotL64(aPrevious, 14U) + aOrbiterI) + RotL64(aOrbiterF, 3U));
            aWandererG = aWandererG + (((RotL64(aCross, 43U) + aOrbiterE) + RotL64(aOrbiterC, 14U)) + aPhaseFWandererUpdateSaltD[(((31U - aIndex) + 18U)) & S_SALT1]);
            //
            aCarry = aCarry + (aWandererG ^ RotL64(aWandererJ, 19U));
            aCarry = aCarry + (aWandererK ^ RotL64(aWandererA, 34U));
            aCarry = aCarry + (aWandererH ^ RotL64(aWandererE, 23U));
            aCarry = aCarry + (RotL64(aWandererC, 39U) ^ aWandererD);
            aCarry = aCarry + RotL64(aWandererF, 47U);
            aCarry = aCarry + RotL64(aIngress, 11U);
            aCarry = TwistMix64::DiffuseA(aCarry);
            //
            aExpandLaneB[S_BLOCK1 - aIndex] = aIngress;
        }
    
        // seed_loop_f loop 5
        // ingress from: aExpandLaneB, aSnowLaneD, aWorkLaneD
        // ingress directions: aExpandLaneB forward forced, aSnowLaneD forward forced, aWorkLaneD forward/backward random
        // cross from: aExpandLaneA, aSnowLaneC
        // cross directions: aExpandLaneA backward forced, aSnowLaneC backward/forward random
        // write to: aExpandLaneC
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aExpandLaneB[((aIndex + 27231U)) & S_BLOCK1], 19U) ^ RotL64(aSnowLaneD[((aIndex + 23605U)) & S_BLOCK1], 37U));
            aIngress ^= RotL64(aWorkLaneD[((S_BLOCK1 - aIndex + 24610U)) & S_BLOCK1], 57U);
            aIngress = TwistMix64::DiffuseB(((aIngress ^ aPhaseFDomainWordIngress) ^ aNonceWordC));
            //
            aCross = RotL64(aExpandLaneA[((S_BLOCK1 - aIndex + 24486U)) & S_BLOCK1], 57U) ^ RotL64(aSnowLaneC[((S_BLOCK1 - aIndex + 22747U)) & S_BLOCK1], 43U);
            aCross = TwistMix64::DiffuseC(((aCross ^ aPhaseFDomainWordCross) ^ aNonceWordA));
            //
            aScatter = (RotL64(aPrevious, 51U) ^ RotL64(aCross, 11U)) + (RotL64(aCarry, 24U) + RotL64(aIngress, 37U));
            aScatter = TwistMix64::DiffuseB(((aScatter ^ aPhaseFDomainWordScatter) ^ aNonceWordF));
            //
            aOrbiterI = ((aWandererA + RotL64(aCross, 36U)) + 4739486756133131180U) + aPhaseFOrbiterAssignSaltC[((aIndex + 19U)) & S_SALT1];
            aOrbiterA = (aWandererG + RotL64(aPrevious, 11U)) + 16089707555501328184U;
            aOrbiterD = (aWandererB + RotL64(aScatter, 51U)) + 15310047330238536453U;
            aOrbiterH = ((((aWandererH + RotL64(aIngress, 47U)) + RotL64(aCarry, 21U)) + 7901411596386834955U) + aPhaseFOrbiterAssignSaltE[(((31U - aIndex) + 25U)) & S_SALT1]) + aNonceWordB;
            aOrbiterJ = (aWandererE + RotL64(aPrevious, 5U)) + 4357555491060982163U;
            aOrbiterB = (((aWandererD + RotL64(aCross, 19U)) + RotL64(aCarry, 35U)) + 15667085602825720102U) + aNonceWordK;
            aOrbiterG = ((aWandererI + RotL64(aScatter, 57U)) + RotL64(aCarry, 43U)) + 8520635334382269253U;
            aOrbiterE = (aWandererC + RotL64(aIngress, 23U)) + 1772509779231068315U;
            aOrbiterC = (aWandererJ + RotL64(aPrevious, 28U)) + 15336170957886025677U;
            //
            aOrbiterI = ((aOrbiterI + aOrbiterA) + 8628770833489469980U) + aPhaseFOrbiterUpdateSaltA[((aIndex + 20U)) & S_SALT1];
            aOrbiterD = ((aOrbiterD ^ aOrbiterI) ^ 15469234024247246228U) ^ aNonceWordP;
            aOrbiterD = RotL64((aOrbiterD * 8905266995119987947U), 47U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterH) + 10796430900884288328U;
            aOrbiterJ = (aOrbiterJ ^ aOrbiterD) ^ 10660110397012853289U;
            aOrbiterJ = RotL64((aOrbiterJ * 9140007610912037461U), 35U);
            //
            aOrbiterH = (aOrbiterH + aOrbiterB) + 11202284258711214794U;
            aOrbiterG = (((aOrbiterG ^ aOrbiterH) ^ 17509491802893182994U) ^ aPhaseFOrbiterUpdateSaltE[(((31U - aIndex) + 7U)) & S_SALT1]) ^ aNonceWordO;
            aOrbiterG = RotL64((aOrbiterG * 9329107599972703671U), 19U);
            //
            aOrbiterE = (aOrbiterE + aOrbiterI) + 16212572740740103554U;
            aOrbiterB = (aOrbiterB ^ aOrbiterE) ^ 2190030203761579226U;
            aOrbiterB = RotL64((aOrbiterB * 3101886685668871045U), 39U);
            //
            aOrbiterJ = (aOrbiterJ + aOrbiterG) + 12014337082293041909U;
            aOrbiterE = ((aOrbiterE ^ aOrbiterJ) ^ 3733531010807001506U) ^ aNonceWordE;
            aOrbiterE = RotL64((aOrbiterE * 5797362244066062299U), 43U);
            //
            aOrbiterA = (aOrbiterA + aOrbiterE) + 7100994963061975529U;
            aOrbiterH = ((aOrbiterH ^ aOrbiterA) ^ 17837541162838600258U) ^ aPhaseFOrbiterUpdateSaltC[((aIndex + 3U)) & S_SALT1];
            aOrbiterH = RotL64((aOrbiterH * 8745987361678166553U), 23U);
            //
            aOrbiterB = (aOrbiterB + aOrbiterD) + 3311518938023146951U;
            aOrbiterC = (aOrbiterC ^ aOrbiterB) ^ 7709505172646831553U;
            aOrbiterC = RotL64((aOrbiterC * 7121143171245765213U), 57U);
            //
            aOrbiterG = ((aOrbiterG + aOrbiterC) + 4979968094554018443U) + aNonceWordN;
            aOrbiterI = ((aOrbiterI ^ aOrbiterG) ^ 16822214821463034107U) ^ aPhaseFOrbiterUpdateSaltD[((aIndex + 29U)) & S_SALT1];
            aOrbiterI = RotL64((aOrbiterI * 8618262120451291765U), 5U);
            //
            aOrbiterC = (aOrbiterC + aOrbiterJ) + 8376124175020587079U;
            aOrbiterA = (aOrbiterA ^ aOrbiterC) ^ 11084586282092424876U;
            aOrbiterA = RotL64((aOrbiterA * 5835632742522563537U), 27U);
            //
            aIngress = aOrbiterG ^ RotL64(aOrbiterH, 46U);
            aIngress = aIngress + (RotL64(aOrbiterI, 3U) ^ aOrbiterJ);
            aIngress = aIngress + (aOrbiterE ^ RotL64(aOrbiterB, 21U));
            aIngress = aIngress + (RotL64(aOrbiterA, 57U) ^ aOrbiterD);
            aIngress = aIngress + RotL64(aOrbiterC, 35U);
            aIngress = TwistMix64::DiffuseA((aIngress + aScatter));
            //
            aWandererH = aWandererH + ((RotL64(aPrevious, 23U) + aOrbiterE) + RotL64(aOrbiterB, 5U));
            aWandererB = aWandererB ^ ((RotL64(aIngress, 60U) + RotL64(aOrbiterI, 41U)) + aOrbiterE);
            aWandererA = aWandererA + (((RotL64(aScatter, 13U) + aOrbiterC) + RotL64(aOrbiterG, 60U)) + RotL64(aCarry, 29U));
            aWandererD = aWandererD ^ ((RotL64(aCross, 41U) + aOrbiterE) + RotL64(aOrbiterC, 23U));
            aWandererC = aWandererC + (((((RotL64(aPrevious, 3U) + RotL64(aOrbiterA, 35U)) + aOrbiterC) + RotL64(aCarry, 3U)) + aNonceWordL) + aPhaseFWandererUpdateSaltF[(((31U - aIndex) + 24U)) & S_SALT1]);
            aWandererE = aWandererE ^ ((RotL64(aIngress, 48U) + aOrbiterB) + RotL64(aOrbiterA, 51U));
            aWandererJ = aWandererJ + ((RotL64(aCross, 19U) + RotL64(aOrbiterJ, 19U)) + aOrbiterD);
            aWandererI = aWandererI ^ ((((RotL64(aScatter, 37U) + aOrbiterG) + RotL64(aOrbiterD, 29U)) + aNonceWordI) + aPhaseFWandererUpdateSaltC[((aIndex + 18U)) & S_SALT1]);
            aWandererG = aWandererG + (((RotL64(aCross, 53U) + RotL64(aOrbiterC, 10U)) + aOrbiterH) + aNonceWordF);
            //
            aCarry = aCarry + (RotL64(aWandererD, 41U) ^ aWandererI);
            aCarry = aCarry + (RotL64(aWandererA, 57U) ^ aWandererJ);
            aCarry = aCarry + (RotL64(aWandererE, 10U) ^ aWandererB);
            aCarry = aCarry + (RotL64(aWandererH, 5U) ^ aWandererC);
            aCarry = aCarry + RotL64(aWandererG, 35U);
            aCarry = aCarry + RotL64(aIngress, 23U);
            aCarry = TwistMix64::DiffuseC(aCarry);
            //
            aExpandLaneC[aIndex] = aIngress;
        }
    
        // seed_loop_f loop 6
        // ingress from: aExpandLaneC, aExpandLaneA, aSnowLaneB
        // ingress directions: aExpandLaneC forward forced, aExpandLaneA forward forced, aSnowLaneB forward/backward random
        // cross from: aExpandLaneB, aOperationLaneB
        // cross directions: aExpandLaneB backward forced, aOperationLaneB backward/forward random
        // write to: aExpandLaneD
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aExpandLaneC[((aIndex + 28253U)) & S_BLOCK1], 10U) ^ RotL64(aExpandLaneA[((aIndex + 27565U)) & S_BLOCK1], 19U));
            aIngress ^= RotL64(aSnowLaneB[((aIndex + 32481U)) & S_BLOCK1], 41U);
            aIngress = TwistMix64::DiffuseA(((aIngress ^ aPhaseFDomainWordIngress) ^ aNonceWordB));
            //
            aCross = RotL64(aExpandLaneB[((S_BLOCK1 - aIndex + 29638U)) & S_BLOCK1], 46U) ^ RotL64(aOperationLaneB[((S_BLOCK1 - aIndex + 28965U)) & S_BLOCK1], 3U);
            aCross = TwistMix64::DiffuseC(((aCross ^ aPhaseFDomainWordCross) ^ aNonceWordI));
            //
            aScatter = (RotL64(aIngress, 51U) ^ RotL64(aCross, 19U)) ^ (RotL64(aCarry, 3U) + RotL64(aPrevious, 36U));
            aScatter = TwistMix64::DiffuseC(((aScatter ^ aPhaseFDomainWordScatter) ^ aNonceWordD));
            //
            aOrbiterE = ((aWandererJ + RotL64(aScatter, 58U)) + RotL64(aCarry, 57U)) + 7825479804710770560U;
            aOrbiterC = ((aWandererB + RotL64(aPrevious, 39U)) + RotL64(aCarry, 35U)) + 5298124167101358123U;
            aOrbiterI = ((aWandererC + RotL64(aCross, 35U)) + RotL64(aCarry, 5U)) + 17774541024369233726U;
            aOrbiterA = (aWandererD + RotL64(aIngress, 19U)) + 7679371833537454082U;
            aOrbiterH = (aWandererI + RotL64(aCross, 43U)) + 5385914900748772224U;
            aOrbiterB = (((aWandererA + RotL64(aPrevious, 27U)) + 3879781930908486531U) + aPhaseFOrbiterAssignSaltA[(((31U - aIndex) + 4U)) & S_SALT1]) + aNonceWordE;
            aOrbiterG = (aWandererH + RotL64(aIngress, 52U)) + 659110346638873236U;
            aOrbiterJ = (aWandererG + RotL64(aScatter, 13U)) + 10749021728538539749U;
            aOrbiterK = (((aWandererE + RotL64(aPrevious, 23U)) + 3631252455767429457U) + aPhaseFOrbiterAssignSaltF[(((31U - aIndex) + 5U)) & S_SALT1]) + aNonceWordM;
            //
            aOrbiterE = ((aOrbiterE + aOrbiterC) + 2271978810960685021U) + aNonceWordN;
            aOrbiterI = (aOrbiterI ^ aOrbiterE) ^ 5963558780692551176U;
            aOrbiterI = RotL64((aOrbiterI * 4772055335210781149U), 35U);
            //
            aOrbiterA = ((aOrbiterA + aOrbiterE) + 974909966119198104U) + aPhaseFOrbiterUpdateSaltD[(((31U - aIndex) + 25U)) & S_SALT1];
            aOrbiterH = (aOrbiterH ^ aOrbiterA) ^ 9296998242911152296U;
            aOrbiterH = RotL64((aOrbiterH * 2613629915877957661U), 53U);
            //
            aOrbiterB = (aOrbiterB + aOrbiterG) + 2245318466901521959U;
            aOrbiterC = (aOrbiterC ^ aOrbiterB) ^ 13391076374843288568U;
            aOrbiterC = RotL64((aOrbiterC * 18094558036982107419U), 47U);
            //
            aOrbiterJ = ((aOrbiterJ + aOrbiterH) + 6184487746594236737U) + aPhaseFOrbiterUpdateSaltC[(((31U - aIndex) + 28U)) & S_SALT1];
            aOrbiterG = (aOrbiterG ^ aOrbiterJ) ^ 1563385912137291418U;
            aOrbiterG = RotL64((aOrbiterG * 4805455299959232321U), 57U);
            //
            aOrbiterH = (aOrbiterH + aOrbiterI) + 1744840092006498629U;
            aOrbiterK = ((aOrbiterK ^ aOrbiterH) ^ 2100927276837188416U) ^ aPhaseFOrbiterUpdateSaltE[((aIndex + 21U)) & S_SALT1];
            aOrbiterK = RotL64((aOrbiterK * 3541788262067077997U), 19U);
            //
            aOrbiterK = (aOrbiterK + aOrbiterB) + 9998911862807246338U;
            aOrbiterE = (aOrbiterE ^ aOrbiterK) ^ 12239948725635220096U;
            aOrbiterE = RotL64((aOrbiterE * 7098620484129489129U), 3U);
            //
            aOrbiterI = (aOrbiterI + aOrbiterJ) + 3307447094994950246U;
            aOrbiterB = (aOrbiterB ^ aOrbiterI) ^ 12746613971448298932U;
            aOrbiterB = RotL64((aOrbiterB * 9463975886346934681U), 13U);
            //
            aOrbiterC = (aOrbiterC + aOrbiterA) + 11577488293733790649U;
            aOrbiterJ = ((aOrbiterJ ^ aOrbiterC) ^ 191108997585598809U) ^ aPhaseFOrbiterUpdateSaltA[(((31U - aIndex) + 22U)) & S_SALT1];
            aOrbiterJ = RotL64((aOrbiterJ * 9574978681405356871U), 23U);
            //
            aOrbiterG = (aOrbiterG + aOrbiterK) + 18096145693841273722U;
            aOrbiterA = ((aOrbiterA ^ aOrbiterG) ^ 10026281133603934071U) ^ aNonceWordA;
            aOrbiterA = RotL64((aOrbiterA * 17261343107314203471U), 27U);
            //
            aIngress = RotL64(aOrbiterI, 50U) ^ aOrbiterG;
            aIngress = aIngress + (RotL64(aOrbiterH, 37U) ^ aOrbiterA);
            aIngress = aIngress + (aOrbiterB ^ RotL64(aOrbiterK, 29U));
            aIngress = aIngress + (RotL64(aOrbiterE, 5U) ^ aOrbiterC);
            aIngress = aIngress + RotL64(aOrbiterJ, 57U);
            aIngress = TwistMix64::DiffuseA((aIngress + aScatter));
            //
            aWandererB = aWandererB ^ (((RotL64(aIngress, 21U) + aOrbiterC) + RotL64(aOrbiterE, 24U)) + aNonceWordK);
            aWandererD = aWandererD + (((((RotL64(aCross, 43U) + RotL64(aOrbiterG, 11U)) + aOrbiterJ) + RotL64(aCarry, 21U)) + aNonceWordH) + aPhaseFWandererUpdateSaltA[((aIndex + 7U)) & S_SALT1]);
            aWandererE = aWandererE ^ ((RotL64(aPrevious, 3U) + aOrbiterI) + RotL64(aOrbiterC, 19U));
            aWandererJ = aWandererJ + (((RotL64(aScatter, 13U) + RotL64(aOrbiterB, 53U)) + aOrbiterE) + RotL64(aCarry, 35U));
            aWandererC = aWandererC ^ ((RotL64(aIngress, 56U) + RotL64(aOrbiterI, 35U)) + aOrbiterG);
            aWandererG = aWandererG + ((((RotL64(aPrevious, 27U) + aOrbiterJ) + RotL64(aOrbiterH, 60U)) + aNonceWordO) + aPhaseFWandererUpdateSaltE[((aIndex + 12U)) & S_SALT1]);
            aWandererH = aWandererH ^ ((RotL64(aScatter, 47U) + RotL64(aOrbiterI, 29U)) + aOrbiterH);
            aWandererA = aWandererA + ((RotL64(aCross, 35U) + RotL64(aOrbiterG, 5U)) + aOrbiterK);
            aWandererI = aWandererI ^ ((RotL64(aScatter, 52U) + RotL64(aOrbiterK, 43U)) + aOrbiterA);
            //
            aCarry = aCarry + (aWandererA ^ RotL64(aWandererD, 39U));
            aCarry = aCarry + (RotL64(aWandererE, 11U) ^ aWandererC);
            aCarry = aCarry + (aWandererG ^ RotL64(aWandererJ, 47U));
            aCarry = aCarry + (RotL64(aWandererB, 3U) ^ aWandererH);
            aCarry = aCarry + RotL64(aWandererI, 60U);
            aCarry = aCarry + RotL64(aIngress, 43U);
            aCarry = TwistMix64::DiffuseB(aCarry);
            //
            aExpandLaneD[S_BLOCK1 - aIndex] = aIngress;
        }
    }
    // GSeedRunSeed_F seed_loop_f (end)
    *pPrevious = aPrevious;
    *pIngress = aIngress;
    *pCarry = aCarry;
    *pWandererA = aWandererA;
    *pWandererB = aWandererB;
    *pWandererC = aWandererC;
    *pWandererD = aWandererD;
    *pWandererE = aWandererE;
    *pWandererF = aWandererF;
    *pWandererG = aWandererG;
    *pWandererH = aWandererH;
    *pWandererI = aWandererI;
    *pWandererJ = aWandererJ;
    *pWandererK = aWandererK;
}

void TwistExpander_Exercea_Arx::Seed_G(TwistWorkSpace *pWorkSpace,
                     std::uint64_t pNonce,
                     std::uint64_t *pPrevious,
                     std::uint64_t *pIngress,
                     std::uint64_t *pCarry,
                     std::uint64_t *pWandererA,
                     std::uint64_t *pWandererB,
                     std::uint64_t *pWandererC,
                     std::uint64_t *pWandererD,
                     std::uint64_t *pWandererE,
                     std::uint64_t *pWandererF,
                     std::uint64_t *pWandererG,
                     std::uint64_t *pWandererH,
                     std::uint64_t *pWandererI,
                     std::uint64_t *pWandererJ,
                     std::uint64_t *pWandererK) {
    [[maybe_unused]] std::uint8_t *aExpandLaneA = pWorkSpace->mExpansionLaneA;
    [[maybe_unused]] std::uint8_t *aExpandLaneB = pWorkSpace->mExpansionLaneB;
    [[maybe_unused]] std::uint8_t *aExpandLaneC = pWorkSpace->mExpansionLaneC;
    [[maybe_unused]] std::uint8_t *aExpandLaneD = pWorkSpace->mExpansionLaneD;
    [[maybe_unused]] std::uint8_t *aWorkLaneA = pWorkSpace->mWorkLaneA;
    [[maybe_unused]] std::uint8_t *aWorkLaneB = pWorkSpace->mWorkLaneB;
    [[maybe_unused]] std::uint8_t *aSnowLaneA = pWorkSpace->mSnowLaneA;
    [[maybe_unused]] std::uint8_t *aSnowLaneB = pWorkSpace->mSnowLaneB;
    [[maybe_unused]] std::uint8_t *aSnowLaneC = pWorkSpace->mSnowLaneC;
    [[maybe_unused]] std::uint8_t *aSnowLaneD = pWorkSpace->mSnowLaneD;
    [[maybe_unused]] std::uint8_t *aFireLaneA = pWorkSpace->mFireLaneA;
    [[maybe_unused]] std::uint8_t *aFireLaneB = pWorkSpace->mFireLaneB;
    [[maybe_unused]] std::uint8_t *aFireLaneC = pWorkSpace->mFireLaneC;
    [[maybe_unused]] std::uint8_t *aFireLaneD = pWorkSpace->mFireLaneD;
    [[maybe_unused]] std::uint8_t *aInvestLaneA = pWorkSpace->mInvestLaneA;
    [[maybe_unused]] std::uint8_t *aInvestLaneB = pWorkSpace->mInvestLaneB;
    [[maybe_unused]] std::uint8_t *aInvestLaneC = pWorkSpace->mInvestLaneC;
    [[maybe_unused]] std::uint8_t *aInvestLaneD = pWorkSpace->mInvestLaneD;
    [[maybe_unused]] std::uint64_t *aPhaseHOrbiterAssignSaltA = pWorkSpace->mDomainBundle.mPhaseHSalts.mOrbiterAssign.mSaltA;
    [[maybe_unused]] std::uint64_t *aPhaseHOrbiterAssignSaltB = pWorkSpace->mDomainBundle.mPhaseHSalts.mOrbiterAssign.mSaltB;
    [[maybe_unused]] std::uint64_t *aPhaseHOrbiterAssignSaltC = pWorkSpace->mDomainBundle.mPhaseHSalts.mOrbiterAssign.mSaltC;
    [[maybe_unused]] std::uint64_t *aPhaseHOrbiterAssignSaltD = pWorkSpace->mDomainBundle.mPhaseHSalts.mOrbiterAssign.mSaltD;
    [[maybe_unused]] std::uint64_t *aPhaseHOrbiterAssignSaltE = pWorkSpace->mDomainBundle.mPhaseHSalts.mOrbiterAssign.mSaltE;
    [[maybe_unused]] std::uint64_t *aPhaseHOrbiterAssignSaltF = pWorkSpace->mDomainBundle.mPhaseHSalts.mOrbiterAssign.mSaltF;
    [[maybe_unused]] std::uint64_t *aPhaseHOrbiterUpdateSaltA = pWorkSpace->mDomainBundle.mPhaseHSalts.mOrbiterUpdate.mSaltA;
    [[maybe_unused]] std::uint64_t *aPhaseHOrbiterUpdateSaltB = pWorkSpace->mDomainBundle.mPhaseHSalts.mOrbiterUpdate.mSaltB;
    [[maybe_unused]] std::uint64_t *aPhaseHOrbiterUpdateSaltC = pWorkSpace->mDomainBundle.mPhaseHSalts.mOrbiterUpdate.mSaltC;
    [[maybe_unused]] std::uint64_t *aPhaseHOrbiterUpdateSaltD = pWorkSpace->mDomainBundle.mPhaseHSalts.mOrbiterUpdate.mSaltD;
    [[maybe_unused]] std::uint64_t *aPhaseHOrbiterUpdateSaltE = pWorkSpace->mDomainBundle.mPhaseHSalts.mOrbiterUpdate.mSaltE;
    [[maybe_unused]] std::uint64_t *aPhaseHOrbiterUpdateSaltF = pWorkSpace->mDomainBundle.mPhaseHSalts.mOrbiterUpdate.mSaltF;
    [[maybe_unused]] std::uint64_t *aPhaseHWandererUpdateSaltA = pWorkSpace->mDomainBundle.mPhaseHSalts.mWandererUpdate.mSaltA;
    [[maybe_unused]] std::uint64_t *aPhaseHWandererUpdateSaltB = pWorkSpace->mDomainBundle.mPhaseHSalts.mWandererUpdate.mSaltB;
    [[maybe_unused]] std::uint64_t *aPhaseHWandererUpdateSaltC = pWorkSpace->mDomainBundle.mPhaseHSalts.mWandererUpdate.mSaltC;
    [[maybe_unused]] std::uint64_t *aPhaseHWandererUpdateSaltD = pWorkSpace->mDomainBundle.mPhaseHSalts.mWandererUpdate.mSaltD;
    [[maybe_unused]] std::uint64_t *aPhaseHWandererUpdateSaltE = pWorkSpace->mDomainBundle.mPhaseHSalts.mWandererUpdate.mSaltE;
    [[maybe_unused]] std::uint64_t *aPhaseHWandererUpdateSaltF = pWorkSpace->mDomainBundle.mPhaseHSalts.mWandererUpdate.mSaltF;
    const std::uint64_t &aPhaseHDomainWordIngress = pWorkSpace->mDomainBundle.mPhaseHConstants.mIngress;
    const std::uint64_t &aPhaseHDomainWordScatter = pWorkSpace->mDomainBundle.mPhaseHConstants.mScatter;
    const std::uint64_t &aPhaseHDomainWordCross = pWorkSpace->mDomainBundle.mPhaseHConstants.mCross;
    std::uint64_t aCross = 0; std::uint64_t aScatter = 0;

    std::uint64_t aOrbiterA = 0; std::uint64_t aOrbiterB = 0; std::uint64_t aOrbiterC = 0; std::uint64_t aOrbiterD = 0;
    std::uint64_t aOrbiterE = 0; std::uint64_t aOrbiterF = 0; std::uint64_t aOrbiterG = 0; std::uint64_t aOrbiterH = 0;
    std::uint64_t aOrbiterI = 0; std::uint64_t aOrbiterJ = 0; std::uint64_t aOrbiterK = 0;

    // [seed arx]
    [[maybe_unused]] std::uint8_t *mSource = pWorkSpace->mSource;
    std::uint64_t aPrevious = *pPrevious;
    std::uint64_t aIngress = *pIngress;
    std::uint64_t aCarry = *pCarry;
    std::uint64_t aWandererA = *pWandererA;
    std::uint64_t aWandererB = *pWandererB;
    std::uint64_t aWandererC = *pWandererC;
    std::uint64_t aWandererD = *pWandererD;
    std::uint64_t aWandererE = *pWandererE;
    std::uint64_t aWandererF = *pWandererF;
    std::uint64_t aWandererG = *pWandererG;
    std::uint64_t aWandererH = *pWandererH;
    std::uint64_t aWandererI = *pWandererI;
    std::uint64_t aWandererJ = *pWandererJ;
    std::uint64_t aWandererK = *pWandererK;
    std::uint64_t aNonceWordA = TwistMix64::DiffuseB(pNonce * 0x9D1CDFB3FCC3EF87ULL + 0xF0E614EE8FF17429ULL);
    std::uint64_t aNonceWordB = TwistMix64::DiffuseB(pNonce * 0xE5ADD26415E3D34DULL + 0xAA15581FBDA09BFDULL);
    std::uint64_t aNonceWordC = TwistMix64::DiffuseA(pNonce * 0xCC9608974C411EE7ULL + 0x9DBF24652CCB7E27ULL);
    std::uint64_t aNonceWordD = TwistMix64::DiffuseB(pNonce * 0x8EF7A41CBAC57E7FULL + 0xFC1C232EFEA64F66ULL);
    std::uint64_t aNonceWordE = TwistMix64::DiffuseC(pNonce * 0xFA70A7C8038FADA9ULL + 0xCEBB560A011DC457ULL);
    std::uint64_t aNonceWordF = TwistMix64::DiffuseC(pNonce * 0x9367046534D96201ULL + 0x8F1A71A38C8D0446ULL);
    std::uint64_t aNonceWordG = TwistMix64::DiffuseA(pNonce * 0xF1F92FB492C6CA59ULL + 0xB5AF78F61126F8C9ULL);
    std::uint64_t aNonceWordH = TwistMix64::DiffuseA(pNonce * 0xE61E0C8C3061E839ULL + 0xE385A6472E5816E8ULL);
    std::uint64_t aNonceWordI = TwistMix64::DiffuseB(pNonce * 0xCA64C4D9E0A5723DULL + 0xE1E2D4256C22D931ULL);
    std::uint64_t aNonceWordJ = TwistMix64::DiffuseB(pNonce * 0xD9142C60471521E7ULL + 0xB5DD7A270EC5A35DULL);
    std::uint64_t aNonceWordK = TwistMix64::DiffuseB(pNonce * 0xDB3AC0021D39F56FULL + 0xDE472E43CA78040DULL);
    std::uint64_t aNonceWordL = TwistMix64::DiffuseC(pNonce * 0xAAA6E2C26895044FULL + 0xFF57945FA82D3EDEULL);
    std::uint64_t aNonceWordM = TwistMix64::DiffuseA(pNonce * 0x84EC3B57BFC788B9ULL + 0xDFFBEBB46D692633ULL);
    std::uint64_t aNonceWordN = TwistMix64::DiffuseA(pNonce * 0xF47F0B17E6F474E5ULL + 0x9AD167F748BB3B86ULL);
    std::uint64_t aNonceWordO = TwistMix64::DiffuseA(pNonce * 0xE7DFC232BE4F0425ULL + 0xF1EA8113658AD1F7ULL);
    std::uint64_t aNonceWordP = TwistMix64::DiffuseC(pNonce * 0xFB4EEE89840ECDB5ULL + 0x8CE6D37500723465ULL);
    // GSeedRunSeed_G seed_loop_h (start)
    {
        // GSeedRunSeed_G seed_loop_h lane group
        // read from: aSnowLaneA, aSnowLaneB, aFireLaneB, aSnowLaneC, aSnowLaneD, aInvestLaneB, aWorkLaneA, aFireLaneD, aInvestLaneC, aWorkLaneB, aFireLaneC, aExpandLaneA, aInvestLaneD, aExpandLaneB, aInvestLaneA, aExpandLaneC, aFireLaneA
        // write to: aWorkLaneA, aWorkLaneB, aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD
    
        // seed_loop_h loop 1
        // ingress from: aSnowLaneA, aSnowLaneB, aFireLaneB
        // ingress directions: aSnowLaneA forward forced, aSnowLaneB forward forced, aFireLaneB forward/backward random
        // cross from: aSnowLaneC, aSnowLaneD, aInvestLaneB
        // cross directions: aSnowLaneC backward forced, aSnowLaneD backward forced, aInvestLaneB backward/forward random
        // write to: aWorkLaneA
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aSnowLaneA[((aIndex + 1487U)) & S_BLOCK1], 13U) ^ RotL64(aSnowLaneB[((aIndex + 887U)) & S_BLOCK1], 43U));
            aIngress ^= RotL64(aFireLaneB[((S_BLOCK1 - aIndex + 4337U)) & S_BLOCK1], 23U);
            aIngress = TwistMix64::DiffuseC(((aIngress ^ aPhaseHDomainWordIngress) ^ aNonceWordE));
            //
            aCross = (RotL64(aSnowLaneC[((S_BLOCK1 - aIndex + 1053U)) & S_BLOCK1], 3U) ^ RotL64(aSnowLaneD[((S_BLOCK1 - aIndex + 1459U)) & S_BLOCK1], 27U));
            aCross ^= RotL64(aInvestLaneB[((aIndex + 4794U)) & S_BLOCK1], 53U);
            aCross = TwistMix64::DiffuseA(((aCross ^ aPhaseHDomainWordCross) ^ aNonceWordF));
            //
            aScatter = (RotL64(aCross, 41U) ^ RotL64(aPrevious, 13U)) + (RotL64(aCarry, 57U) + RotL64(aIngress, 26U));
            aScatter = TwistMix64::DiffuseB(((aScatter ^ aPhaseHDomainWordScatter) ^ aNonceWordG));
            //
            aOrbiterK = (aWandererK + RotL64(aIngress, 57U)) + 2915859148137000694U;
            aOrbiterJ = ((aWandererC + RotL64(aPrevious, 13U)) + RotL64(aCarry, 29U)) + 210680583721444425U;
            aOrbiterD = (((aWandererE + RotL64(aScatter, 28U)) + RotL64(aCarry, 51U)) + 6668118118775650387U) + aNonceWordH;
            aOrbiterC = ((aWandererB + RotL64(aCross, 47U)) + 15794200818099010989U) + aPhaseHOrbiterAssignSaltD[(((31U - aIndex) + 15U)) & S_SALT1];
            aOrbiterA = (aWandererJ + RotL64(aPrevious, 41U)) + 6565076707062828369U;
            aOrbiterF = (((aWandererI + RotL64(aIngress, 21U)) + RotL64(aCarry, 5U)) + 16323164497808856719U) + aPhaseHOrbiterAssignSaltE[((aIndex + 9U)) & S_SALT1];
            aOrbiterB = ((aWandererH + RotL64(aCross, 3U)) + 7965435318816716560U) + aNonceWordD;
            //
            aOrbiterK = (((aOrbiterK + aOrbiterJ) + 7390281030573369017U) + aPhaseHOrbiterUpdateSaltC[((aIndex + 5U)) & S_SALT1]) + aNonceWordM;
            aOrbiterD = (aOrbiterD ^ aOrbiterK) ^ 2269738866911824875U;
            aOrbiterD = RotL64((aOrbiterD * 1198697877998135567U), 51U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterC) + 9664014216039993873U;
            aOrbiterA = (((aOrbiterA ^ aOrbiterD) ^ 18284857398028357633U) ^ aPhaseHOrbiterUpdateSaltA[(((31U - aIndex) + 12U)) & S_SALT1]) ^ aNonceWordO;
            aOrbiterA = RotL64((aOrbiterA * 8402008251343393737U), 29U);
            //
            aOrbiterF = (aOrbiterF + aOrbiterD) + 367667619795303009U;
            aOrbiterB = (aOrbiterB ^ aOrbiterF) ^ 7935945060956274197U;
            aOrbiterB = RotL64((aOrbiterB * 5481786693511955209U), 57U);
            //
            aOrbiterC = ((aOrbiterC + aOrbiterK) + 16683666162337789540U) + aNonceWordC;
            aOrbiterF = ((aOrbiterF ^ aOrbiterC) ^ 10655658270998102390U) ^ aPhaseHOrbiterUpdateSaltB[(((31U - aIndex) + 22U)) & S_SALT1];
            aOrbiterF = RotL64((aOrbiterF * 15231596813382239841U), 35U);
            //
            aOrbiterJ = (aOrbiterJ + aOrbiterB) + 8307037916581540297U;
            aOrbiterC = (aOrbiterC ^ aOrbiterJ) ^ 3247742749860703524U;
            aOrbiterC = RotL64((aOrbiterC * 15052136713218656641U), 11U);
            //
            aOrbiterA = ((aOrbiterA + aOrbiterF) + 10446792483683818139U) + aPhaseHOrbiterUpdateSaltE[((aIndex + 13U)) & S_SALT1];
            aOrbiterJ = (aOrbiterJ ^ aOrbiterA) ^ 16374602929344972364U;
            aOrbiterJ = RotL64((aOrbiterJ * 12599903932725787599U), 43U);
            //
            aOrbiterB = (aOrbiterB + aOrbiterA) + 2411334498322777183U;
            aOrbiterK = (aOrbiterK ^ aOrbiterB) ^ 1093701164116833765U;
            aOrbiterK = RotL64((aOrbiterK * 13129220206835381729U), 5U);
            //
            aIngress = aOrbiterA ^ RotL64(aOrbiterK, 57U);
            aIngress = aIngress + (aOrbiterC ^ RotL64(aOrbiterB, 11U));
            aIngress = aIngress + (RotL64(aOrbiterF, 5U) ^ aOrbiterD);
            aIngress = aIngress + RotL64(aOrbiterJ, 51U);
            aIngress = TwistMix64::DiffuseC((aIngress + aScatter));
            //
            aWandererJ = aWandererJ ^ ((RotL64(aIngress, 23U) + RotL64(aOrbiterC, 51U)) + aOrbiterJ);
            aWandererC = aWandererC + ((((RotL64(aPrevious, 35U) + RotL64(aOrbiterD, 28U)) + aOrbiterF) + RotL64(aCarry, 5U)) + aNonceWordP);
            aWandererB = aWandererB ^ ((((RotL64(aScatter, 57U) + aOrbiterA) + RotL64(aOrbiterD, 21U)) + aNonceWordA) + aPhaseHWandererUpdateSaltD[((aIndex + 29U)) & S_SALT1]);
            aWandererK = aWandererK + (((RotL64(aCross, 29U) + aOrbiterF) + RotL64(aOrbiterB, 35U)) + RotL64(aCarry, 57U));
            aWandererI = aWandererI ^ (((RotL64(aPrevious, 11U) + RotL64(aOrbiterA, 43U)) + aOrbiterF) + aPhaseHWandererUpdateSaltB[((aIndex + 8U)) & S_SALT1]);
            aWandererE = aWandererE + (((RotL64(aScatter, 5U) + aOrbiterC) + RotL64(aOrbiterF, 3U)) + aNonceWordI);
            aWandererH = aWandererH ^ (((RotL64(aCross, 48U) + RotL64(aOrbiterK, 11U)) + aOrbiterC) + aNonceWordN);
            //
            aCarry = aCarry + (RotL64(aWandererE, 37U) ^ aWandererB);
            aCarry = aCarry + (RotL64(aWandererH, 3U) ^ aWandererK);
            aCarry = aCarry + (aWandererC ^ RotL64(aWandererJ, 20U));
            aCarry = aCarry + RotL64(aWandererI, 43U);
            aCarry = aCarry + RotL64(aIngress, 53U);
            aCarry = TwistMix64::DiffuseC(aCarry);
            //
            aWorkLaneA[aIndex] = aIngress;
        }
    
        // seed_loop_h loop 2
        // ingress from: aWorkLaneA, aSnowLaneC, aSnowLaneD, aFireLaneD
        // ingress directions: aWorkLaneA forward forced, aSnowLaneC forward forced, aSnowLaneD forward forced, aFireLaneD forward/backward random
        // cross from: aSnowLaneA, aSnowLaneB, aInvestLaneC
        // cross directions: aSnowLaneA backward forced, aSnowLaneB backward forced, aInvestLaneC backward/forward random
        // write to: aWorkLaneB
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aWorkLaneA[((aIndex + 8871U)) & S_BLOCK1], 20U) ^ RotL64(aSnowLaneC[((aIndex + 9966U)) & S_BLOCK1], 3U));
            aIngress ^= (RotL64(aSnowLaneD[((aIndex + 8469U)) & S_BLOCK1], 35U) ^ RotL64(aFireLaneD[((S_BLOCK1 - aIndex + 10282U)) & S_BLOCK1], 11U));
            aIngress = TwistMix64::DiffuseB(((aIngress ^ aPhaseHDomainWordIngress) ^ aNonceWordP));
            //
            aCross = (RotL64(aSnowLaneA[((S_BLOCK1 - aIndex + 9908U)) & S_BLOCK1], 41U) ^ RotL64(aSnowLaneB[((S_BLOCK1 - aIndex + 6429U)) & S_BLOCK1], 24U));
            aCross ^= RotL64(aInvestLaneC[((aIndex + 7117U)) & S_BLOCK1], 57U);
            aCross = TwistMix64::DiffuseB(((aCross ^ aPhaseHDomainWordCross) ^ aNonceWordM));
            //
            aScatter = (RotL64(aPrevious, 22U) ^ RotL64(aCarry, 57U)) + (RotL64(aIngress, 5U) + RotL64(aCross, 39U));
            aScatter = TwistMix64::DiffuseA(((aScatter ^ aPhaseHDomainWordScatter) ^ aNonceWordO));
            //
            aOrbiterK = (((aWandererH + RotL64(aScatter, 23U)) + 17019646486641172469U) + aPhaseHOrbiterAssignSaltC[(((31U - aIndex) + 5U)) & S_SALT1]) + aNonceWordC;
            aOrbiterB = ((aWandererD + RotL64(aPrevious, 53U)) + 12276141179299971572U) + aNonceWordA;
            aOrbiterI = ((aWandererG + RotL64(aCross, 43U)) + 3617241694029841555U) + aNonceWordG;
            aOrbiterA = ((aWandererJ + RotL64(aIngress, 35U)) + 6967963401259371737U) + aNonceWordJ;
            aOrbiterC = ((aWandererE + RotL64(aCross, 10U)) + RotL64(aCarry, 23U)) + 6340709284279891017U;
            aOrbiterJ = ((aWandererB + RotL64(aPrevious, 29U)) + RotL64(aCarry, 57U)) + 456065368903896482U;
            aOrbiterH = (((aWandererI + RotL64(aScatter, 3U)) + RotL64(aCarry, 39U)) + 17686765719908116203U) + aPhaseHOrbiterAssignSaltF[(((31U - aIndex) + 15U)) & S_SALT1];
            //
            aOrbiterK = (aOrbiterK + aOrbiterB) + 1322045955429785736U;
            aOrbiterI = ((aOrbiterI ^ aOrbiterK) ^ 5163772703302372887U) ^ aPhaseHOrbiterUpdateSaltD[((aIndex + 23U)) & S_SALT1];
            aOrbiterI = RotL64((aOrbiterI * 3193272189179082313U), 51U);
            //
            aOrbiterA = (aOrbiterA + aOrbiterI) + 13268431135020363252U;
            aOrbiterC = (aOrbiterC ^ aOrbiterA) ^ 6538789950366849332U;
            aOrbiterC = RotL64((aOrbiterC * 5352960308459065837U), 27U);
            //
            aOrbiterB = (aOrbiterB + aOrbiterA) + 10390344544314544893U;
            aOrbiterJ = ((aOrbiterJ ^ aOrbiterB) ^ 5087084271300584267U) ^ aNonceWordD;
            aOrbiterJ = RotL64((aOrbiterJ * 15149302947570776165U), 43U);
            //
            aOrbiterJ = (aOrbiterJ + aOrbiterC) + 13423071121590981727U;
            aOrbiterK = (((aOrbiterK ^ aOrbiterJ) ^ 18324443012024134729U) ^ aPhaseHOrbiterUpdateSaltC[(((31U - aIndex) + 22U)) & S_SALT1]) ^ aNonceWordN;
            aOrbiterK = RotL64((aOrbiterK * 15814349432207734533U), 37U);
            //
            aOrbiterC = (aOrbiterC + aOrbiterH) + 4129091815978464507U;
            aOrbiterB = (aOrbiterB ^ aOrbiterC) ^ 17024797553831962245U;
            aOrbiterB = RotL64((aOrbiterB * 3137753479364378175U), 57U);
            //
            aOrbiterI = (aOrbiterI + aOrbiterJ) + 6501545108779991661U;
            aOrbiterH = ((aOrbiterH ^ aOrbiterI) ^ 11930037791867597447U) ^ aPhaseHOrbiterUpdateSaltE[(((31U - aIndex) + 3U)) & S_SALT1];
            aOrbiterH = RotL64((aOrbiterH * 4904739567549702851U), 3U);
            //
            aOrbiterH = (aOrbiterH + aOrbiterK) + 4667298703308315851U;
            aOrbiterA = ((aOrbiterA ^ aOrbiterH) ^ 6315980380900062127U) ^ aPhaseHOrbiterUpdateSaltF[(((31U - aIndex) + 24U)) & S_SALT1];
            aOrbiterA = RotL64((aOrbiterA * 12080555704907924637U), 19U);
            //
            aIngress = aOrbiterB ^ RotL64(aOrbiterK, 35U);
            aIngress = aIngress + (aOrbiterC ^ RotL64(aOrbiterI, 41U));
            aIngress = aIngress + (aOrbiterJ ^ RotL64(aOrbiterH, 20U));
            aIngress = aIngress + RotL64(aOrbiterA, 51U);
            aIngress = TwistMix64::DiffuseB((aIngress + aScatter));
            //
            aWandererE = aWandererE + ((((RotL64(aCross, 44U) + RotL64(aOrbiterH, 41U)) + aOrbiterI) + RotL64(aCarry, 37U)) + aNonceWordL);
            aWandererD = aWandererD ^ (((RotL64(aPrevious, 57U) + RotL64(aOrbiterB, 13U)) + aOrbiterK) + aNonceWordH);
            aWandererH = aWandererH + (((RotL64(aScatter, 5U) + aOrbiterJ) + RotL64(aOrbiterI, 47U)) + aNonceWordB);
            aWandererG = aWandererG ^ (((RotL64(aIngress, 27U) + aOrbiterA) + RotL64(aOrbiterI, 58U)) + aPhaseHWandererUpdateSaltA[((aIndex + 26U)) & S_SALT1]);
            aWandererI = aWandererI + (((RotL64(aScatter, 37U) + RotL64(aOrbiterB, 27U)) + aOrbiterA) + RotL64(aCarry, 11U));
            aWandererB = aWandererB ^ (((RotL64(aCross, 19U) + aOrbiterI) + RotL64(aOrbiterC, 5U)) + aNonceWordO);
            aWandererJ = aWandererJ + (((RotL64(aIngress, 11U) + aOrbiterC) + RotL64(aOrbiterA, 35U)) + aPhaseHWandererUpdateSaltC[(((31U - aIndex) + 21U)) & S_SALT1]);
            //
            aCarry = aCarry + (RotL64(aWandererJ, 18U) ^ aWandererH);
            aCarry = aCarry + (RotL64(aWandererB, 47U) ^ aWandererI);
            aCarry = aCarry + (RotL64(aWandererG, 41U) ^ aWandererE);
            aCarry = aCarry + RotL64(aWandererD, 23U);
            aCarry = aCarry + RotL64(aIngress, 56U);
            aCarry = TwistMix64::DiffuseA(aCarry);
            //
            aWorkLaneB[S_BLOCK1 - aIndex] = aIngress;
        }
    
        // seed_loop_h loop 3
        // ingress from: aWorkLaneB, aSnowLaneA, aFireLaneC
        // ingress directions: aWorkLaneB forward forced, aSnowLaneA forward forced, aFireLaneC forward/backward random
        // cross from: aWorkLaneA, aSnowLaneC
        // cross directions: aWorkLaneA backward forced, aSnowLaneC backward/forward random
        // write to: aExpandLaneA
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aWorkLaneB[((aIndex + 11518U)) & S_BLOCK1], 3U) ^ RotL64(aSnowLaneA[((aIndex + 13929U)) & S_BLOCK1], 54U));
            aIngress ^= RotL64(aFireLaneC[((aIndex + 15566U)) & S_BLOCK1], 43U);
            aIngress = TwistMix64::DiffuseA(((aIngress ^ aPhaseHDomainWordIngress) ^ aNonceWordK));
            //
            aCross = RotL64(aWorkLaneA[((S_BLOCK1 - aIndex + 15053U)) & S_BLOCK1], 50U) ^ RotL64(aSnowLaneC[((S_BLOCK1 - aIndex + 14035U)) & S_BLOCK1], 5U);
            aCross = TwistMix64::DiffuseB(((aCross ^ aPhaseHDomainWordCross) ^ aNonceWordI));
            //
            aScatter = (RotL64(aPrevious, 35U) ^ RotL64(aCross, 56U)) + (RotL64(aCarry, 5U) + RotL64(aIngress, 19U));
            aScatter = TwistMix64::DiffuseA(((aScatter ^ aPhaseHDomainWordScatter) ^ aNonceWordI));
            //
            aOrbiterB = (((aWandererA + RotL64(aCross, 51U)) + RotL64(aCarry, 19U)) + 3255291173184001106U) + aNonceWordE;
            aOrbiterE = ((aWandererD + RotL64(aIngress, 29U)) + 15308468160116255528U) + aNonceWordM;
            aOrbiterG = ((aWandererK + RotL64(aPrevious, 57U)) + 18186972408589866656U) + aPhaseHOrbiterAssignSaltA[(((31U - aIndex) + 14U)) & S_SALT1];
            aOrbiterC = ((aWandererH + RotL64(aScatter, 11U)) + 4439324265978331914U) + aPhaseHOrbiterAssignSaltB[((aIndex + 7U)) & S_SALT1];
            aOrbiterD = (aWandererG + RotL64(aPrevious, 41U)) + 13099263173016322486U;
            aOrbiterK = (((aWandererJ + RotL64(aIngress, 4U)) + RotL64(aCarry, 35U)) + 7041561081767500660U) + aNonceWordH;
            aOrbiterA = ((aWandererB + RotL64(aScatter, 23U)) + RotL64(aCarry, 47U)) + 6196422612687812971U;
            //
            aOrbiterB = ((aOrbiterB + aOrbiterE) + 7664260932541281413U) + aPhaseHOrbiterUpdateSaltA[(((31U - aIndex) + 21U)) & S_SALT1];
            aOrbiterG = ((aOrbiterG ^ aOrbiterB) ^ 17802347823020441056U) ^ aPhaseHOrbiterUpdateSaltE[((aIndex + 24U)) & S_SALT1];
            aOrbiterG = RotL64((aOrbiterG * 2220679459017369255U), 19U);
            //
            aOrbiterC = (aOrbiterC + aOrbiterD) + 4253107484061190446U;
            aOrbiterK = ((aOrbiterK ^ aOrbiterC) ^ 13799496534030645312U) ^ aNonceWordC;
            aOrbiterK = RotL64((aOrbiterK * 9167675060053848207U), 27U);
            //
            aOrbiterK = ((aOrbiterK + aOrbiterA) + 14252892847595951926U) + aNonceWordB;
            aOrbiterB = (aOrbiterB ^ aOrbiterK) ^ 5663527578664291422U;
            aOrbiterB = RotL64((aOrbiterB * 18314294235895182465U), 57U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterK) + 11148755959699137661U;
            aOrbiterA = (((aOrbiterA ^ aOrbiterD) ^ 17036900929333594592U) ^ aPhaseHOrbiterUpdateSaltB[(((31U - aIndex) + 16U)) & S_SALT1]) ^ aNonceWordF;
            aOrbiterA = RotL64((aOrbiterA * 16041243617369003291U), 5U);
            //
            aOrbiterG = ((aOrbiterG + aOrbiterC) + 2403828181385259549U) + aPhaseHOrbiterUpdateSaltC[(((31U - aIndex) + 25U)) & S_SALT1];
            aOrbiterD = (aOrbiterD ^ aOrbiterG) ^ 17813580350434928194U;
            aOrbiterD = RotL64((aOrbiterD * 13666780980793857831U), 39U);
            //
            aOrbiterE = (aOrbiterE + aOrbiterG) + 5623611126885414523U;
            aOrbiterC = (aOrbiterC ^ aOrbiterE) ^ 7293224381174846969U;
            aOrbiterC = RotL64((aOrbiterC * 7032561584670788117U), 47U);
            //
            aOrbiterA = (aOrbiterA + aOrbiterB) + 10602620906929686163U;
            aOrbiterE = (aOrbiterE ^ aOrbiterA) ^ 18015916257203385982U;
            aOrbiterE = RotL64((aOrbiterE * 10684090189688871993U), 11U);
            //
            aIngress = aOrbiterA ^ RotL64(aOrbiterE, 29U);
            aIngress = aIngress + (RotL64(aOrbiterC, 56U) ^ aOrbiterG);
            aIngress = aIngress + (aOrbiterD ^ RotL64(aOrbiterK, 47U));
            aIngress = aIngress + RotL64(aOrbiterB, 37U);
            aIngress = TwistMix64::DiffuseC((aIngress + aScatter));
            //
            aWandererH = aWandererH + (((RotL64(aPrevious, 35U) + RotL64(aOrbiterC, 12U)) + aOrbiterE) + RotL64(aCarry, 13U));
            aWandererG = aWandererG ^ (((RotL64(aCross, 14U) + aOrbiterA) + RotL64(aOrbiterB, 51U)) + aNonceWordL);
            aWandererD = aWandererD + (((RotL64(aScatter, 29U) + RotL64(aOrbiterD, 27U)) + aOrbiterG) + aPhaseHWandererUpdateSaltF[(((31U - aIndex) + 26U)) & S_SALT1]);
            aWandererB = aWandererB ^ ((RotL64(aIngress, 3U) + aOrbiterD) + RotL64(aOrbiterA, 19U));
            aWandererK = aWandererK + (((((RotL64(aCross, 23U) + aOrbiterE) + RotL64(aOrbiterK, 37U)) + RotL64(aCarry, 47U)) + aNonceWordD) + aPhaseHWandererUpdateSaltE[((aIndex + 9U)) & S_SALT1]);
            aWandererJ = aWandererJ ^ (((RotL64(aIngress, 41U) + aOrbiterB) + RotL64(aOrbiterE, 57U)) + aNonceWordJ);
            aWandererA = aWandererA + ((RotL64(aPrevious, 47U) + RotL64(aOrbiterE, 43U)) + aOrbiterA);
            //
            aCarry = aCarry + (aWandererH ^ RotL64(aWandererD, 3U));
            aCarry = aCarry + (RotL64(aWandererK, 35U) ^ aWandererB);
            aCarry = aCarry + (aWandererJ ^ RotL64(aWandererG, 42U));
            aCarry = aCarry + RotL64(aWandererA, 57U);
            aCarry = aCarry + RotL64(aIngress, 13U);
            aCarry = TwistMix64::DiffuseA(aCarry);
            //
            aExpandLaneA[aIndex] = aIngress;
        }
    
        // seed_loop_h loop 4
        // ingress from: aExpandLaneA, aWorkLaneA, aInvestLaneD
        // ingress directions: aExpandLaneA forward forced, aWorkLaneA forward forced, aInvestLaneD forward/backward random
        // cross from: aWorkLaneB, aSnowLaneD
        // cross directions: aWorkLaneB backward forced, aSnowLaneD backward/forward random
        // write to: aExpandLaneB
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aExpandLaneA[((aIndex + 21703U)) & S_BLOCK1], 48U) ^ RotL64(aWorkLaneA[((aIndex + 16929U)) & S_BLOCK1], 5U));
            aIngress ^= RotL64(aInvestLaneD[((S_BLOCK1 - aIndex + 18108U)) & S_BLOCK1], 19U);
            aIngress = TwistMix64::DiffuseC(((aIngress ^ aPhaseHDomainWordIngress) ^ aNonceWordK));
            //
            aCross = RotL64(aWorkLaneB[((S_BLOCK1 - aIndex + 20617U)) & S_BLOCK1], 5U) ^ RotL64(aSnowLaneD[((aIndex + 16936U)) & S_BLOCK1], 24U);
            aCross = TwistMix64::DiffuseC(((aCross ^ aPhaseHDomainWordCross) ^ aNonceWordL));
            //
            aScatter = (RotL64(aCross, 51U) ^ RotL64(aPrevious, 21U)) + (RotL64(aCarry, 4U) ^ RotL64(aIngress, 39U));
            aScatter = TwistMix64::DiffuseA(((aScatter ^ aPhaseHDomainWordScatter) ^ aNonceWordO));
            //
            aOrbiterF = (((aWandererH + RotL64(aCross, 5U)) + RotL64(aCarry, 47U)) + 15904465836916519864U) + aPhaseHOrbiterAssignSaltE[(((31U - aIndex) + 22U)) & S_SALT1];
            aOrbiterB = ((aWandererJ + RotL64(aIngress, 60U)) + 17725629806317789307U) + aNonceWordD;
            aOrbiterD = (((aWandererE + RotL64(aPrevious, 13U)) + 13794170125914914828U) + aPhaseHOrbiterAssignSaltD[(((31U - aIndex) + 19U)) & S_SALT1]) + aNonceWordI;
            aOrbiterH = ((aWandererA + RotL64(aScatter, 47U)) + RotL64(aCarry, 35U)) + 2149055907476874332U;
            aOrbiterK = ((aWandererI + RotL64(aCross, 19U)) + 5342047776745074649U) + aNonceWordM;
            aOrbiterJ = ((aWandererB + RotL64(aPrevious, 27U)) + 8268148484060546838U) + aNonceWordE;
            aOrbiterA = ((aWandererK + RotL64(aIngress, 35U)) + RotL64(aCarry, 21U)) + 10821151364028563719U;
            //
            aOrbiterF = (aOrbiterF + aOrbiterB) + 4294213820894407378U;
            aOrbiterD = ((aOrbiterD ^ aOrbiterF) ^ 10884726101307943090U) ^ aNonceWordF;
            aOrbiterD = RotL64((aOrbiterD * 1116128870387229159U), 21U);
            //
            aOrbiterH = (((aOrbiterH + aOrbiterF) + 16432210042202444824U) + aPhaseHOrbiterUpdateSaltB[((aIndex + 3U)) & S_SALT1]) + aNonceWordN;
            aOrbiterB = ((aOrbiterB ^ aOrbiterH) ^ 15196602644336228055U) ^ aPhaseHOrbiterUpdateSaltF[(((31U - aIndex) + 25U)) & S_SALT1];
            aOrbiterB = RotL64((aOrbiterB * 12680438355124070237U), 27U);
            //
            aOrbiterK = (aOrbiterK + aOrbiterJ) + 14117787670220328165U;
            aOrbiterA = ((aOrbiterA ^ aOrbiterK) ^ 219833877949480215U) ^ aNonceWordJ;
            aOrbiterA = RotL64((aOrbiterA * 10736293047771972173U), 13U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterK) + 3326396981881473962U;
            aOrbiterJ = (aOrbiterJ ^ aOrbiterD) ^ 14918513066311426279U;
            aOrbiterJ = RotL64((aOrbiterJ * 14269763278564574663U), 57U);
            //
            aOrbiterJ = (aOrbiterJ + aOrbiterA) + 11795234681370163206U;
            aOrbiterH = (aOrbiterH ^ aOrbiterJ) ^ 3068267285352664813U;
            aOrbiterH = RotL64((aOrbiterH * 15746255933920904619U), 35U);
            //
            aOrbiterA = ((aOrbiterA + aOrbiterH) + 245233356957999496U) + aPhaseHOrbiterUpdateSaltC[((aIndex + 29U)) & S_SALT1];
            aOrbiterF = (aOrbiterF ^ aOrbiterA) ^ 709926406353796673U;
            aOrbiterF = RotL64((aOrbiterF * 13627039596842073595U), 5U);
            //
            aOrbiterB = ((aOrbiterB + aOrbiterD) + 5378105439430271038U) + aPhaseHOrbiterUpdateSaltA[(((31U - aIndex) + 12U)) & S_SALT1];
            aOrbiterK = ((aOrbiterK ^ aOrbiterB) ^ 10114555061122044430U) ^ aNonceWordB;
            aOrbiterK = RotL64((aOrbiterK * 5351295043424885549U), 43U);
            //
            aIngress = RotL64(aOrbiterD, 19U) ^ aOrbiterJ;
            aIngress = aIngress + (aOrbiterA ^ RotL64(aOrbiterH, 5U));
            aIngress = aIngress + (RotL64(aOrbiterK, 50U) ^ aOrbiterB);
            aIngress = aIngress + RotL64(aOrbiterF, 57U);
            aIngress = TwistMix64::DiffuseB((aIngress + aScatter));
            //
            aWandererB = aWandererB + ((((RotL64(aPrevious, 43U) + aOrbiterB) + RotL64(aOrbiterF, 51U)) + aNonceWordH) + aPhaseHWandererUpdateSaltD[((aIndex + 28U)) & S_SALT1]);
            aWandererK = aWandererK ^ ((RotL64(aIngress, 37U) + aOrbiterK) + RotL64(aOrbiterD, 35U));
            aWandererH = aWandererH + (((RotL64(aScatter, 3U) + RotL64(aOrbiterJ, 43U)) + aOrbiterD) + RotL64(aCarry, 43U));
            aWandererE = aWandererE ^ ((RotL64(aCross, 51U) + aOrbiterD) + RotL64(aOrbiterF, 60U));
            aWandererJ = aWandererJ + ((((RotL64(aIngress, 30U) + aOrbiterH) + RotL64(aOrbiterF, 5U)) + aNonceWordP) + aPhaseHWandererUpdateSaltB[((aIndex + 14U)) & S_SALT1]);
            aWandererA = aWandererA ^ ((RotL64(aScatter, 57U) + aOrbiterH) + RotL64(aOrbiterJ, 19U));
            aWandererI = aWandererI + ((((RotL64(aPrevious, 19U) + RotL64(aOrbiterK, 11U)) + aOrbiterA) + RotL64(aCarry, 5U)) + aNonceWordA);
            //
            aCarry = aCarry + (RotL64(aWandererH, 29U) ^ aWandererK);
            aCarry = aCarry + (RotL64(aWandererB, 4U) ^ aWandererE);
            aCarry = aCarry + (RotL64(aWandererJ, 23U) ^ aWandererI);
            aCarry = aCarry + RotL64(aWandererA, 35U);
            aCarry = aCarry + RotL64(aIngress, 39U);
            aCarry = TwistMix64::DiffuseB(aCarry);
            //
            aExpandLaneB[S_BLOCK1 - aIndex] = aIngress;
        }
    
        // seed_loop_h loop 5
        // ingress from: aExpandLaneB, aWorkLaneB, aInvestLaneA
        // ingress directions: aExpandLaneB forward forced, aWorkLaneB forward forced, aInvestLaneA forward/backward random
        // cross from: aExpandLaneA, aWorkLaneA
        // cross directions: aExpandLaneA backward forced, aWorkLaneA backward/forward random
        // write to: aExpandLaneC
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aExpandLaneB[((aIndex + 27019U)) & S_BLOCK1], 58U) ^ RotL64(aWorkLaneB[((aIndex + 24930U)) & S_BLOCK1], 35U));
            aIngress ^= RotL64(aInvestLaneA[((S_BLOCK1 - aIndex + 21886U)) & S_BLOCK1], 11U);
            aIngress = TwistMix64::DiffuseB(((aIngress ^ aPhaseHDomainWordIngress) ^ aNonceWordI));
            //
            aCross = RotL64(aExpandLaneA[((S_BLOCK1 - aIndex + 23791U)) & S_BLOCK1], 35U) ^ RotL64(aWorkLaneA[((S_BLOCK1 - aIndex + 26616U)) & S_BLOCK1], 5U);
            aCross = TwistMix64::DiffuseC(((aCross ^ aPhaseHDomainWordCross) ^ aNonceWordH));
            //
            aScatter = (RotL64(aCross, 10U) ^ RotL64(aPrevious, 41U)) + (RotL64(aIngress, 53U) + RotL64(aCarry, 29U));
            aScatter = TwistMix64::DiffuseB(((aScatter ^ aPhaseHDomainWordScatter) ^ aNonceWordP));
            //
            aOrbiterK = ((aWandererK + RotL64(aScatter, 19U)) + 14008824488073394623U) + aPhaseHOrbiterAssignSaltC[(((31U - aIndex) + 11U)) & S_SALT1];
            aOrbiterH = ((aWandererC + RotL64(aIngress, 53U)) + 13317978415866411468U) + aPhaseHOrbiterAssignSaltF[((aIndex + 17U)) & S_SALT1];
            aOrbiterG = ((aWandererE + RotL64(aPrevious, 43U)) + 13209180141897453900U) + aNonceWordM;
            aOrbiterF = (aWandererH + RotL64(aCross, 11U)) + 11870521586865233578U;
            aOrbiterI = ((aWandererF + RotL64(aPrevious, 27U)) + RotL64(aCarry, 21U)) + 8052156380448047385U;
            aOrbiterE = ((aWandererI + RotL64(aCross, 60U)) + RotL64(aCarry, 51U)) + 12158131176743680605U;
            aOrbiterB = (((aWandererJ + RotL64(aScatter, 35U)) + RotL64(aCarry, 39U)) + 14674467487607719347U) + aNonceWordL;
            //
            aOrbiterK = (aOrbiterK + aOrbiterH) + 18055496790566231147U;
            aOrbiterG = (((aOrbiterG ^ aOrbiterK) ^ 3838105585041578784U) ^ aPhaseHOrbiterUpdateSaltB[((aIndex + 22U)) & S_SALT1]) ^ aNonceWordN;
            aOrbiterG = RotL64((aOrbiterG * 1075709247574580091U), 57U);
            //
            aOrbiterF = (aOrbiterF + aOrbiterG) + 2839568255183054418U;
            aOrbiterI = ((aOrbiterI ^ aOrbiterF) ^ 11933612922864258179U) ^ aNonceWordB;
            aOrbiterI = RotL64((aOrbiterI * 7571964469321160347U), 51U);
            //
            aOrbiterE = ((aOrbiterE + aOrbiterK) + 6289849094151630580U) + aPhaseHOrbiterUpdateSaltC[(((31U - aIndex) + 13U)) & S_SALT1];
            aOrbiterF = (((aOrbiterF ^ aOrbiterE) ^ 2640344350528492271U) ^ aPhaseHOrbiterUpdateSaltD[(((31U - aIndex) + 28U)) & S_SALT1]) ^ aNonceWordJ;
            aOrbiterF = RotL64((aOrbiterF * 16197726750829369365U), 35U);
            //
            aOrbiterB = (aOrbiterB + aOrbiterI) + 16306175266267657791U;
            aOrbiterK = ((aOrbiterK ^ aOrbiterB) ^ 3339898380394883600U) ^ aNonceWordE;
            aOrbiterK = RotL64((aOrbiterK * 7105436590182982373U), 41U);
            //
            aOrbiterG = ((aOrbiterG + aOrbiterB) + 15017076663742800002U) + aPhaseHOrbiterUpdateSaltE[((aIndex + 7U)) & S_SALT1];
            aOrbiterE = (aOrbiterE ^ aOrbiterG) ^ 8973064296077602496U;
            aOrbiterE = RotL64((aOrbiterE * 9309462227233615761U), 29U);
            //
            aOrbiterH = (aOrbiterH + aOrbiterF) + 17580319233338139859U;
            aOrbiterB = (aOrbiterB ^ aOrbiterH) ^ 14063208878807603874U;
            aOrbiterB = RotL64((aOrbiterB * 16601475239075164585U), 19U);
            //
            aOrbiterI = (aOrbiterI + aOrbiterE) + 13326130855721009942U;
            aOrbiterH = (aOrbiterH ^ aOrbiterI) ^ 12843186026737544416U;
            aOrbiterH = RotL64((aOrbiterH * 4975848122837321619U), 13U);
            //
            aIngress = RotL64(aOrbiterB, 57U) ^ aOrbiterI;
            aIngress = aIngress + (aOrbiterE ^ RotL64(aOrbiterF, 35U));
            aIngress = aIngress + (RotL64(aOrbiterG, 11U) ^ aOrbiterH);
            aIngress = aIngress + RotL64(aOrbiterK, 44U);
            aIngress = TwistMix64::DiffuseA((aIngress + aScatter));
            //
            aWandererF = aWandererF + ((((RotL64(aCross, 3U) + RotL64(aOrbiterK, 46U)) + aOrbiterH) + RotL64(aCarry, 3U)) + aPhaseHWandererUpdateSaltA[((aIndex + 27U)) & S_SALT1]);
            aWandererK = aWandererK ^ ((RotL64(aPrevious, 11U) + aOrbiterB) + RotL64(aOrbiterH, 29U));
            aWandererI = aWandererI + ((((RotL64(aScatter, 50U) + aOrbiterF) + RotL64(aOrbiterE, 21U)) + RotL64(aCarry, 47U)) + aNonceWordA);
            aWandererJ = aWandererJ ^ ((((RotL64(aIngress, 37U) + RotL64(aOrbiterF, 13U)) + aOrbiterG) + aNonceWordG) + aPhaseHWandererUpdateSaltC[((aIndex + 24U)) & S_SALT1]);
            aWandererE = aWandererE + (((RotL64(aScatter, 57U) + aOrbiterB) + RotL64(aOrbiterK, 3U)) + aNonceWordF);
            aWandererH = aWandererH ^ (((RotL64(aCross, 19U) + aOrbiterI) + RotL64(aOrbiterG, 53U)) + aNonceWordP);
            aWandererC = aWandererC + ((RotL64(aIngress, 29U) + aOrbiterI) + RotL64(aOrbiterB, 37U));
            //
            aCarry = aCarry + (aWandererI ^ RotL64(aWandererC, 46U));
            aCarry = aCarry + (aWandererK ^ RotL64(aWandererH, 35U));
            aCarry = aCarry + (aWandererJ ^ RotL64(aWandererE, 11U));
            aCarry = aCarry + RotL64(aWandererF, 19U);
            aCarry = aCarry + RotL64(aIngress, 39U);
            aCarry = TwistMix64::DiffuseC(aCarry);
            //
            aExpandLaneC[aIndex] = aIngress;
        }
    
        // seed_loop_h loop 6
        // ingress from: aExpandLaneC, aExpandLaneA, aFireLaneA
        // ingress directions: aExpandLaneC forward forced, aExpandLaneA forward forced, aFireLaneA forward/backward random
        // cross from: aExpandLaneB, aSnowLaneB
        // cross directions: aExpandLaneB backward forced, aSnowLaneB backward/forward random
        // write to: aExpandLaneD
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aExpandLaneC[((aIndex + 32092U)) & S_BLOCK1], 39U) ^ RotL64(aExpandLaneA[((aIndex + 31454U)) & S_BLOCK1], 47U));
            aIngress ^= RotL64(aFireLaneA[((S_BLOCK1 - aIndex + 29594U)) & S_BLOCK1], 60U);
            aIngress = TwistMix64::DiffuseC(((aIngress ^ aPhaseHDomainWordIngress) ^ aNonceWordF));
            //
            aCross = RotL64(aExpandLaneB[((S_BLOCK1 - aIndex + 30526U)) & S_BLOCK1], 18U) ^ RotL64(aSnowLaneB[((aIndex + 31889U)) & S_BLOCK1], 29U);
            aCross = TwistMix64::DiffuseB(((aCross ^ aPhaseHDomainWordCross) ^ aNonceWordC));
            //
            aScatter = (RotL64(aCross, 53U) + RotL64(aIngress, 29U)) ^ (RotL64(aCarry, 6U) ^ RotL64(aPrevious, 41U));
            aScatter = TwistMix64::DiffuseC(((aScatter ^ aPhaseHDomainWordScatter) ^ aNonceWordN));
            //
            aOrbiterD = ((aWandererK + RotL64(aIngress, 30U)) + 6068543441070417854U) + aNonceWordD;
            aOrbiterH = (aWandererI + RotL64(aPrevious, 57U)) + 2995980468193441856U;
            aOrbiterC = ((aWandererA + RotL64(aCross, 47U)) + 18020277482171594003U) + aPhaseHOrbiterAssignSaltB[(((31U - aIndex) + 9U)) & S_SALT1];
            aOrbiterJ = (((aWandererG + RotL64(aScatter, 5U)) + RotL64(aCarry, 5U)) + 4293807434721230702U) + aNonceWordH;
            aOrbiterK = ((((aWandererE + RotL64(aCross, 13U)) + RotL64(aCarry, 51U)) + 7980599111583893156U) + aPhaseHOrbiterAssignSaltA[(((31U - aIndex) + 7U)) & S_SALT1]) + aNonceWordI;
            aOrbiterI = (aWandererD + RotL64(aIngress, 37U)) + 8593141111851052016U;
            aOrbiterG = ((aWandererC + RotL64(aPrevious, 21U)) + RotL64(aCarry, 21U)) + 5903487523900084325U;
            //
            aOrbiterD = ((aOrbiterD + aOrbiterH) + 15112035513447930209U) + aPhaseHOrbiterUpdateSaltD[((aIndex + 17U)) & S_SALT1];
            aOrbiterC = ((aOrbiterC ^ aOrbiterD) ^ 9854037263057006439U) ^ aPhaseHOrbiterUpdateSaltA[((aIndex + 23U)) & S_SALT1];
            aOrbiterC = RotL64((aOrbiterC * 396276470208637283U), 29U);
            //
            aOrbiterJ = ((aOrbiterJ + aOrbiterK) + 16759760289688823193U) + aNonceWordL;
            aOrbiterD = ((aOrbiterD ^ aOrbiterJ) ^ 12622628933030601390U) ^ aNonceWordM;
            aOrbiterD = RotL64((aOrbiterD * 2151912984825538321U), 47U);
            //
            aOrbiterH = (aOrbiterH + aOrbiterJ) + 1264668857268123425U;
            aOrbiterI = ((aOrbiterI ^ aOrbiterH) ^ 16302812053619101593U) ^ aNonceWordK;
            aOrbiterI = RotL64((aOrbiterI * 18291400055836111547U), 23U);
            //
            aOrbiterI = (aOrbiterI + aOrbiterD) + 16087995784896123610U;
            aOrbiterG = (aOrbiterG ^ aOrbiterI) ^ 7970269262800468363U;
            aOrbiterG = RotL64((aOrbiterG * 14924752223305807461U), 13U);
            //
            aOrbiterK = ((aOrbiterK + aOrbiterG) + 5331477046030959632U) + aNonceWordN;
            aOrbiterH = (aOrbiterH ^ aOrbiterK) ^ 16534913204255550893U;
            aOrbiterH = RotL64((aOrbiterH * 1013433634373673565U), 41U);
            //
            aOrbiterG = (aOrbiterG + aOrbiterC) + 11042821902537871209U;
            aOrbiterJ = ((aOrbiterJ ^ aOrbiterG) ^ 8069677512345031660U) ^ aPhaseHOrbiterUpdateSaltF[(((31U - aIndex) + 19U)) & S_SALT1];
            aOrbiterJ = RotL64((aOrbiterJ * 13622218526054132397U), 57U);
            //
            aOrbiterC = ((aOrbiterC + aOrbiterI) + 5737130058129936372U) + aPhaseHOrbiterUpdateSaltB[((aIndex + 10U)) & S_SALT1];
            aOrbiterK = (aOrbiterK ^ aOrbiterC) ^ 1076627182956662997U;
            aOrbiterK = RotL64((aOrbiterK * 14342191224014199929U), 35U);
            //
            aIngress = RotL64(aOrbiterG, 13U) ^ aOrbiterJ;
            aIngress = aIngress + (RotL64(aOrbiterK, 41U) ^ aOrbiterC);
            aIngress = aIngress + (RotL64(aOrbiterD, 5U) ^ aOrbiterI);
            aIngress = aIngress + RotL64(aOrbiterH, 48U);
            aIngress = TwistMix64::DiffuseB((aIngress + aScatter));
            //
            aWandererG = aWandererG ^ (((RotL64(aScatter, 34U) + RotL64(aOrbiterH, 27U)) + aOrbiterI) + aNonceWordG);
            aWandererI = aWandererI + ((RotL64(aIngress, 27U) + RotL64(aOrbiterI, 50U)) + aOrbiterJ);
            aWandererC = aWandererC ^ (((RotL64(aPrevious, 11U) + RotL64(aOrbiterC, 43U)) + aOrbiterK) + aNonceWordO);
            aWandererK = aWandererK + (((RotL64(aCross, 53U) + RotL64(aOrbiterH, 13U)) + aOrbiterK) + RotL64(aCarry, 3U));
            aWandererE = aWandererE ^ ((((RotL64(aPrevious, 47U) + RotL64(aOrbiterG, 19U)) + aOrbiterJ) + aNonceWordB) + aPhaseHWandererUpdateSaltE[(((31U - aIndex) + 24U)) & S_SALT1]);
            aWandererD = aWandererD + ((((RotL64(aScatter, 3U) + aOrbiterK) + RotL64(aOrbiterJ, 3U)) + RotL64(aCarry, 41U)) + aPhaseHWandererUpdateSaltF[((aIndex + 13U)) & S_SALT1]);
            aWandererA = aWandererA ^ (((RotL64(aIngress, 21U) + aOrbiterJ) + RotL64(aOrbiterD, 37U)) + aNonceWordP);
            //
            aCarry = aCarry + (aWandererD ^ RotL64(aWandererK, 51U));
            aCarry = aCarry + (RotL64(aWandererE, 12U) ^ aWandererC);
            aCarry = aCarry + (aWandererA ^ RotL64(aWandererI, 41U));
            aCarry = aCarry + RotL64(aWandererG, 27U);
            aCarry = aCarry + RotL64(aIngress, 19U);
            aCarry = TwistMix64::DiffuseB(aCarry);
            //
            aExpandLaneD[S_BLOCK1 - aIndex] = aIngress;
        }
    }
    // GSeedRunSeed_G seed_loop_h (end)
    *pPrevious = aPrevious;
    *pIngress = aIngress;
    *pCarry = aCarry;
    *pWandererA = aWandererA;
    *pWandererB = aWandererB;
    *pWandererC = aWandererC;
    *pWandererD = aWandererD;
    *pWandererE = aWandererE;
    *pWandererF = aWandererF;
    *pWandererG = aWandererG;
    *pWandererH = aWandererH;
    *pWandererI = aWandererI;
    *pWandererJ = aWandererJ;
    *pWandererK = aWandererK;
}

void TwistExpander_Exercea_Arx::Twist_A(TwistWorkSpace *pWorkSpace,
                     std::uint8_t *pSource,
                     std::uint64_t *pPrevious,
                     std::uint64_t *pIngress,
                     std::uint64_t *pCarry,
                     std::uint64_t *pWandererA,
                     std::uint64_t *pWandererB,
                     std::uint64_t *pWandererC,
                     std::uint64_t *pWandererD,
                     std::uint64_t *pWandererE,
                     std::uint64_t *pWandererF,
                     std::uint64_t *pWandererG,
                     std::uint64_t *pWandererH,
                     std::uint64_t *pWandererI,
                     std::uint64_t *pWandererJ,
                     std::uint64_t *pWandererK) {
    [[maybe_unused]] std::uint8_t *aExpandLaneA = pWorkSpace->mExpansionLaneA;
    [[maybe_unused]] std::uint8_t *aExpandLaneB = pWorkSpace->mExpansionLaneB;
    [[maybe_unused]] std::uint8_t *aExpandLaneC = pWorkSpace->mExpansionLaneC;
    [[maybe_unused]] std::uint8_t *aExpandLaneD = pWorkSpace->mExpansionLaneD;
    [[maybe_unused]] std::uint8_t *aWorkLaneA = pWorkSpace->mWorkLaneA;
    [[maybe_unused]] std::uint8_t *aWorkLaneB = pWorkSpace->mWorkLaneB;
    [[maybe_unused]] std::uint8_t *aFireLaneA = pWorkSpace->mFireLaneA;
    [[maybe_unused]] std::uint8_t *aFireLaneB = pWorkSpace->mFireLaneB;
    [[maybe_unused]] std::uint8_t *aFireLaneC = pWorkSpace->mFireLaneC;
    [[maybe_unused]] std::uint8_t *aFireLaneD = pWorkSpace->mFireLaneD;
    [[maybe_unused]] std::uint8_t *aInvestLaneA = pWorkSpace->mInvestLaneA;
    [[maybe_unused]] std::uint8_t *aInvestLaneB = pWorkSpace->mInvestLaneB;
    [[maybe_unused]] std::uint8_t *aKeyRowReadA = &(pWorkSpace->mKeyBoxA[H_KEY - 1][0]);
    [[maybe_unused]] std::uint8_t *aKeyRowReadB = &(pWorkSpace->mKeyBoxB[H_KEY - 1][0]);
    [[maybe_unused]] std::uint64_t *aPhaseAOrbiterAssignSaltA = pWorkSpace->mDomainBundle.mPhaseASalts.mOrbiterAssign.mSaltA;
    [[maybe_unused]] std::uint64_t *aPhaseAOrbiterAssignSaltC = pWorkSpace->mDomainBundle.mPhaseASalts.mOrbiterAssign.mSaltC;
    [[maybe_unused]] std::uint64_t *aPhaseAOrbiterAssignSaltD = pWorkSpace->mDomainBundle.mPhaseASalts.mOrbiterAssign.mSaltD;
    [[maybe_unused]] std::uint64_t *aPhaseAOrbiterAssignSaltE = pWorkSpace->mDomainBundle.mPhaseASalts.mOrbiterAssign.mSaltE;
    [[maybe_unused]] std::uint64_t *aPhaseAOrbiterUpdateSaltA = pWorkSpace->mDomainBundle.mPhaseASalts.mOrbiterUpdate.mSaltA;
    [[maybe_unused]] std::uint64_t *aPhaseAOrbiterUpdateSaltB = pWorkSpace->mDomainBundle.mPhaseASalts.mOrbiterUpdate.mSaltB;
    [[maybe_unused]] std::uint64_t *aPhaseAOrbiterUpdateSaltC = pWorkSpace->mDomainBundle.mPhaseASalts.mOrbiterUpdate.mSaltC;
    [[maybe_unused]] std::uint64_t *aPhaseAOrbiterUpdateSaltE = pWorkSpace->mDomainBundle.mPhaseASalts.mOrbiterUpdate.mSaltE;
    [[maybe_unused]] std::uint64_t *aPhaseAOrbiterUpdateSaltF = pWorkSpace->mDomainBundle.mPhaseASalts.mOrbiterUpdate.mSaltF;
    [[maybe_unused]] std::uint64_t *aPhaseAWandererUpdateSaltA = pWorkSpace->mDomainBundle.mPhaseASalts.mWandererUpdate.mSaltA;
    [[maybe_unused]] std::uint64_t *aPhaseAWandererUpdateSaltB = pWorkSpace->mDomainBundle.mPhaseASalts.mWandererUpdate.mSaltB;
    [[maybe_unused]] std::uint64_t *aPhaseAWandererUpdateSaltC = pWorkSpace->mDomainBundle.mPhaseASalts.mWandererUpdate.mSaltC;
    [[maybe_unused]] std::uint64_t *aPhaseAWandererUpdateSaltD = pWorkSpace->mDomainBundle.mPhaseASalts.mWandererUpdate.mSaltD;
    [[maybe_unused]] std::uint64_t *aPhaseBOrbiterAssignSaltA = pWorkSpace->mDomainBundle.mPhaseBSalts.mOrbiterAssign.mSaltA;
    [[maybe_unused]] std::uint64_t *aPhaseBOrbiterAssignSaltC = pWorkSpace->mDomainBundle.mPhaseBSalts.mOrbiterAssign.mSaltC;
    [[maybe_unused]] std::uint64_t *aPhaseBOrbiterAssignSaltD = pWorkSpace->mDomainBundle.mPhaseBSalts.mOrbiterAssign.mSaltD;
    [[maybe_unused]] std::uint64_t *aPhaseBOrbiterAssignSaltE = pWorkSpace->mDomainBundle.mPhaseBSalts.mOrbiterAssign.mSaltE;
    [[maybe_unused]] std::uint64_t *aPhaseBOrbiterAssignSaltF = pWorkSpace->mDomainBundle.mPhaseBSalts.mOrbiterAssign.mSaltF;
    [[maybe_unused]] std::uint64_t *aPhaseBOrbiterUpdateSaltA = pWorkSpace->mDomainBundle.mPhaseBSalts.mOrbiterUpdate.mSaltA;
    [[maybe_unused]] std::uint64_t *aPhaseBOrbiterUpdateSaltB = pWorkSpace->mDomainBundle.mPhaseBSalts.mOrbiterUpdate.mSaltB;
    [[maybe_unused]] std::uint64_t *aPhaseBOrbiterUpdateSaltC = pWorkSpace->mDomainBundle.mPhaseBSalts.mOrbiterUpdate.mSaltC;
    [[maybe_unused]] std::uint64_t *aPhaseBOrbiterUpdateSaltD = pWorkSpace->mDomainBundle.mPhaseBSalts.mOrbiterUpdate.mSaltD;
    [[maybe_unused]] std::uint64_t *aPhaseBOrbiterUpdateSaltE = pWorkSpace->mDomainBundle.mPhaseBSalts.mOrbiterUpdate.mSaltE;
    [[maybe_unused]] std::uint64_t *aPhaseBOrbiterUpdateSaltF = pWorkSpace->mDomainBundle.mPhaseBSalts.mOrbiterUpdate.mSaltF;
    [[maybe_unused]] std::uint64_t *aPhaseBWandererUpdateSaltA = pWorkSpace->mDomainBundle.mPhaseBSalts.mWandererUpdate.mSaltA;
    [[maybe_unused]] std::uint64_t *aPhaseBWandererUpdateSaltB = pWorkSpace->mDomainBundle.mPhaseBSalts.mWandererUpdate.mSaltB;
    [[maybe_unused]] std::uint64_t *aPhaseBWandererUpdateSaltC = pWorkSpace->mDomainBundle.mPhaseBSalts.mWandererUpdate.mSaltC;
    [[maybe_unused]] std::uint64_t *aPhaseBWandererUpdateSaltE = pWorkSpace->mDomainBundle.mPhaseBSalts.mWandererUpdate.mSaltE;
    [[maybe_unused]] std::uint64_t *aPhaseBWandererUpdateSaltF = pWorkSpace->mDomainBundle.mPhaseBSalts.mWandererUpdate.mSaltF;
    [[maybe_unused]] std::uint64_t *aPhaseCOrbiterAssignSaltA = pWorkSpace->mDomainBundle.mPhaseCSalts.mOrbiterAssign.mSaltA;
    [[maybe_unused]] std::uint64_t *aPhaseCOrbiterAssignSaltC = pWorkSpace->mDomainBundle.mPhaseCSalts.mOrbiterAssign.mSaltC;
    [[maybe_unused]] std::uint64_t *aPhaseCOrbiterAssignSaltD = pWorkSpace->mDomainBundle.mPhaseCSalts.mOrbiterAssign.mSaltD;
    [[maybe_unused]] std::uint64_t *aPhaseCOrbiterAssignSaltE = pWorkSpace->mDomainBundle.mPhaseCSalts.mOrbiterAssign.mSaltE;
    [[maybe_unused]] std::uint64_t *aPhaseCOrbiterAssignSaltF = pWorkSpace->mDomainBundle.mPhaseCSalts.mOrbiterAssign.mSaltF;
    [[maybe_unused]] std::uint64_t *aPhaseCOrbiterUpdateSaltA = pWorkSpace->mDomainBundle.mPhaseCSalts.mOrbiterUpdate.mSaltA;
    [[maybe_unused]] std::uint64_t *aPhaseCOrbiterUpdateSaltB = pWorkSpace->mDomainBundle.mPhaseCSalts.mOrbiterUpdate.mSaltB;
    [[maybe_unused]] std::uint64_t *aPhaseCOrbiterUpdateSaltC = pWorkSpace->mDomainBundle.mPhaseCSalts.mOrbiterUpdate.mSaltC;
    [[maybe_unused]] std::uint64_t *aPhaseCOrbiterUpdateSaltD = pWorkSpace->mDomainBundle.mPhaseCSalts.mOrbiterUpdate.mSaltD;
    [[maybe_unused]] std::uint64_t *aPhaseCOrbiterUpdateSaltE = pWorkSpace->mDomainBundle.mPhaseCSalts.mOrbiterUpdate.mSaltE;
    [[maybe_unused]] std::uint64_t *aPhaseCOrbiterUpdateSaltF = pWorkSpace->mDomainBundle.mPhaseCSalts.mOrbiterUpdate.mSaltF;
    [[maybe_unused]] std::uint64_t *aPhaseCWandererUpdateSaltA = pWorkSpace->mDomainBundle.mPhaseCSalts.mWandererUpdate.mSaltA;
    [[maybe_unused]] std::uint64_t *aPhaseCWandererUpdateSaltB = pWorkSpace->mDomainBundle.mPhaseCSalts.mWandererUpdate.mSaltB;
    [[maybe_unused]] std::uint64_t *aPhaseCWandererUpdateSaltD = pWorkSpace->mDomainBundle.mPhaseCSalts.mWandererUpdate.mSaltD;
    [[maybe_unused]] std::uint64_t *aPhaseCWandererUpdateSaltE = pWorkSpace->mDomainBundle.mPhaseCSalts.mWandererUpdate.mSaltE;
    [[maybe_unused]] std::uint64_t *aPhaseCWandererUpdateSaltF = pWorkSpace->mDomainBundle.mPhaseCSalts.mWandererUpdate.mSaltF;
    [[maybe_unused]] std::uint64_t *aPhaseDOrbiterAssignSaltA = pWorkSpace->mDomainBundle.mPhaseDSalts.mOrbiterAssign.mSaltA;
    [[maybe_unused]] std::uint64_t *aPhaseDOrbiterAssignSaltB = pWorkSpace->mDomainBundle.mPhaseDSalts.mOrbiterAssign.mSaltB;
    [[maybe_unused]] std::uint64_t *aPhaseDOrbiterAssignSaltD = pWorkSpace->mDomainBundle.mPhaseDSalts.mOrbiterAssign.mSaltD;
    [[maybe_unused]] std::uint64_t *aPhaseDOrbiterAssignSaltE = pWorkSpace->mDomainBundle.mPhaseDSalts.mOrbiterAssign.mSaltE;
    [[maybe_unused]] std::uint64_t *aPhaseDOrbiterUpdateSaltA = pWorkSpace->mDomainBundle.mPhaseDSalts.mOrbiterUpdate.mSaltA;
    [[maybe_unused]] std::uint64_t *aPhaseDOrbiterUpdateSaltC = pWorkSpace->mDomainBundle.mPhaseDSalts.mOrbiterUpdate.mSaltC;
    [[maybe_unused]] std::uint64_t *aPhaseDOrbiterUpdateSaltD = pWorkSpace->mDomainBundle.mPhaseDSalts.mOrbiterUpdate.mSaltD;
    [[maybe_unused]] std::uint64_t *aPhaseDOrbiterUpdateSaltE = pWorkSpace->mDomainBundle.mPhaseDSalts.mOrbiterUpdate.mSaltE;
    [[maybe_unused]] std::uint64_t *aPhaseDOrbiterUpdateSaltF = pWorkSpace->mDomainBundle.mPhaseDSalts.mOrbiterUpdate.mSaltF;
    [[maybe_unused]] std::uint64_t *aPhaseDWandererUpdateSaltA = pWorkSpace->mDomainBundle.mPhaseDSalts.mWandererUpdate.mSaltA;
    [[maybe_unused]] std::uint64_t *aPhaseDWandererUpdateSaltB = pWorkSpace->mDomainBundle.mPhaseDSalts.mWandererUpdate.mSaltB;
    [[maybe_unused]] std::uint64_t *aPhaseDWandererUpdateSaltC = pWorkSpace->mDomainBundle.mPhaseDSalts.mWandererUpdate.mSaltC;
    [[maybe_unused]] std::uint64_t *aPhaseDWandererUpdateSaltD = pWorkSpace->mDomainBundle.mPhaseDSalts.mWandererUpdate.mSaltD;
    [[maybe_unused]] std::uint64_t *aPhaseDWandererUpdateSaltF = pWorkSpace->mDomainBundle.mPhaseDSalts.mWandererUpdate.mSaltF;
    std::uint64_t aCross = 0; std::uint64_t aScatter = 0;

    std::uint64_t aOrbiterA = 0; std::uint64_t aOrbiterB = 0; std::uint64_t aOrbiterC = 0; std::uint64_t aOrbiterD = 0;
    std::uint64_t aOrbiterE = 0; std::uint64_t aOrbiterF = 0; std::uint64_t aOrbiterG = 0; std::uint64_t aOrbiterH = 0;
    std::uint64_t aOrbiterI = 0; std::uint64_t aOrbiterJ = 0; std::uint64_t aOrbiterK = 0;

    // [twist arx]
    [[maybe_unused]] std::uint8_t *mSource = pSource;
    std::uint64_t aPrevious = *pPrevious;
    std::uint64_t aIngress = *pIngress;
    std::uint64_t aCarry = *pCarry;
    std::uint64_t aWandererA = *pWandererA;
    std::uint64_t aWandererB = *pWandererB;
    std::uint64_t aWandererC = *pWandererC;
    std::uint64_t aWandererD = *pWandererD;
    std::uint64_t aWandererE = *pWandererE;
    std::uint64_t aWandererF = *pWandererF;
    std::uint64_t aWandererG = *pWandererG;
    std::uint64_t aWandererH = *pWandererH;
    std::uint64_t aWandererI = *pWandererI;
    std::uint64_t aWandererJ = *pWandererJ;
    std::uint64_t aWandererK = *pWandererK;
    // GTwistRunTwist_A twist_loop_a (start)
    {
        // GTwistRunTwist_A twist_loop_a lane group
        // read from: aKeyRowReadA, aKeyRowReadB, mSource, aWorkLaneA, aWorkLaneB, aInvestLaneA, aInvestLaneB, aFireLaneA, aFireLaneB, aFireLaneC, aFireLaneD, aExpandLaneA, aExpandLaneB, aExpandLaneC
        // write to: aWorkLaneA, aWorkLaneB, aInvestLaneA, aInvestLaneB, aFireLaneA, aFireLaneB, aFireLaneC, aFireLaneD, aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD
    
        // twist_loop_a loop 1
        // ingress from: aKeyRowReadA, aKeyRowReadB
        // ingress directions: aKeyRowReadA forward forced, aKeyRowReadB forward/backward random
        // cross from: aKeyRowReadA, mSource
        // cross directions: aKeyRowReadA backward forced, mSource backward/forward random
        // write to: aWorkLaneA
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = RotL64(aKeyRowReadA[((aIndex + 1109U)) & W_KEY1], 46U) ^ RotL64(aKeyRowReadB[(((2047U - aIndex) + 433U)) & W_KEY1], 3U);
            aIngress = TwistMix64::DiffuseC(aIngress);
            //
            aCross = RotL64(aKeyRowReadA[(((2047U - aIndex) + 164U)) & W_KEY1], 39U) ^ RotL64(mSource[((aIndex + 954U)) & S_BLOCK1], 22U);
            aCross = TwistMix64::DiffuseC(aCross);
            //
            aScatter = (RotL64(aIngress, 35U) ^ RotL64(aCross, 18U)) ^ (RotL64(aCarry, 5U) + RotL64(aPrevious, 51U));
            aScatter = TwistMix64::DiffuseA(aScatter);
            //
            aOrbiterA = ((aWandererD + RotL64(aPrevious, 19U)) + RotL64(aCarry, 3U)) + 16124889768301047791U;
            aOrbiterB = ((aWandererJ + RotL64(aCross, 3U)) + RotL64(aCarry, 29U)) + 11912338587186717280U;
            aOrbiterE = ((aWandererE + RotL64(aIngress, 23U)) + 8594012868813114354U) + aPhaseAOrbiterAssignSaltE[((aIndex + 6U)) & S_SALT1];
            aOrbiterK = ((aWandererB + RotL64(aScatter, 47U)) + 18281043566156682815U) + aPhaseAOrbiterAssignSaltC[(((31U - aIndex) + 24U)) & S_SALT1];
            aOrbiterC = (aWandererH + RotL64(aPrevious, 54U)) + 16853106130200942302U;
            aOrbiterF = (aWandererG + RotL64(aScatter, 27U)) + 2611212958619673086U;
            aOrbiterG = (aWandererC + RotL64(aCross, 11U)) + 18039472325066855180U;
            aOrbiterI = (aWandererF + RotL64(aIngress, 41U)) + 14495785571345122046U;
            aOrbiterJ = ((aWandererA + RotL64(aScatter, 34U)) + RotL64(aCarry, 41U)) + 4556063793412832418U;
            //
            aOrbiterA = (aOrbiterA + aOrbiterB) + 14896419970271244358U;
            aOrbiterE = (aOrbiterE ^ aOrbiterA) ^ 880028529183500036U;
            aOrbiterE = RotL64((aOrbiterE * 14228281807461251361U), 21U);
            //
            aOrbiterK = (aOrbiterK + aOrbiterC) + 2379557167489415783U;
            aOrbiterF = (aOrbiterF ^ aOrbiterK) ^ 11854373946064529806U;
            aOrbiterF = RotL64((aOrbiterF * 150755294320438887U), 47U);
            //
            aOrbiterF = (aOrbiterF + aOrbiterG) + 1487252775956449964U;
            aOrbiterA = (aOrbiterA ^ aOrbiterF) ^ 12777924204511625545U;
            aOrbiterA = RotL64((aOrbiterA * 1366019527386994789U), 43U);
            //
            aOrbiterB = ((aOrbiterB + aOrbiterI) + 15998631485222477969U) + aPhaseAOrbiterUpdateSaltB[((aIndex + 7U)) & S_SALT1];
            aOrbiterK = ((aOrbiterK ^ aOrbiterB) ^ 8864212892296191613U) ^ aPhaseAOrbiterUpdateSaltA[(((31U - aIndex) + 22U)) & S_SALT1];
            aOrbiterK = RotL64((aOrbiterK * 579242788050369815U), 53U);
            //
            aOrbiterI = (aOrbiterI + aOrbiterA) + 17069347835763226743U;
            aOrbiterC = (aOrbiterC ^ aOrbiterI) ^ 7443008171694679791U;
            aOrbiterC = RotL64((aOrbiterC * 748894368884566607U), 35U);
            //
            aOrbiterG = (aOrbiterG + aOrbiterJ) + 17334256152350782002U;
            aOrbiterB = (aOrbiterB ^ aOrbiterG) ^ 8986626119086556393U;
            aOrbiterB = RotL64((aOrbiterB * 2258172145924120235U), 13U);
            //
            aOrbiterJ = ((aOrbiterJ + aOrbiterF) + 8528180968228358674U) + aPhaseAOrbiterUpdateSaltE[((aIndex + 11U)) & S_SALT1];
            aOrbiterI = (aOrbiterI ^ aOrbiterJ) ^ 12702290928064582589U;
            aOrbiterI = RotL64((aOrbiterI * 15673603224146737631U), 5U);
            //
            aOrbiterE = (aOrbiterE + aOrbiterK) + 7742438100860023610U;
            aOrbiterJ = ((aOrbiterJ ^ aOrbiterE) ^ 3729687240959702198U) ^ aPhaseAOrbiterUpdateSaltF[(((31U - aIndex) + 14U)) & S_SALT1];
            aOrbiterJ = RotL64((aOrbiterJ * 3756794766163746783U), 39U);
            //
            aOrbiterC = (aOrbiterC + aOrbiterE) + 426129097367382096U;
            aOrbiterG = (aOrbiterG ^ aOrbiterC) ^ 16782175452274911213U;
            aOrbiterG = RotL64((aOrbiterG * 1041477289638333659U), 27U);
            //
            aIngress = aOrbiterE ^ RotL64(aOrbiterC, 28U);
            aIngress = aIngress + (aOrbiterJ ^ RotL64(aOrbiterI, 47U));
            aIngress = aIngress + (aOrbiterB ^ RotL64(aOrbiterA, 3U));
            aIngress = aIngress + (aOrbiterF ^ RotL64(aOrbiterK, 53U));
            aIngress = aIngress + RotL64(aOrbiterG, 19U);
            aIngress = TwistMix64::DiffuseC((aIngress + aScatter));
            //
            aWandererD = aWandererD + ((RotL64(aPrevious, 58U) + aOrbiterC) + RotL64(aOrbiterE, 47U));
            aWandererC = aWandererC ^ ((RotL64(aScatter, 27U) + RotL64(aOrbiterF, 34U)) + aOrbiterA);
            aWandererG = aWandererG + ((RotL64(aIngress, 5U) + RotL64(aOrbiterB, 11U)) + aOrbiterK);
            aWandererJ = aWandererJ ^ ((RotL64(aCross, 53U) + aOrbiterA) + RotL64(aOrbiterJ, 3U));
            aWandererA = aWandererA + (((RotL64(aScatter, 43U) + RotL64(aOrbiterB, 51U)) + aOrbiterC) + RotL64(aCarry, 21U));
            aWandererE = aWandererE ^ ((RotL64(aIngress, 39U) + aOrbiterJ) + RotL64(aOrbiterE, 58U));
            aWandererF = aWandererF + ((((RotL64(aPrevious, 14U) + RotL64(aOrbiterC, 27U)) + aOrbiterI) + RotL64(aCarry, 37U)) + aPhaseAWandererUpdateSaltC[(((31U - aIndex) + 16U)) & S_SALT1]);
            aWandererB = aWandererB ^ ((RotL64(aCross, 35U) + RotL64(aOrbiterI, 23U)) + aOrbiterJ);
            aWandererH = aWandererH + (((RotL64(aPrevious, 19U) + RotL64(aOrbiterC, 43U)) + aOrbiterG) + aPhaseAWandererUpdateSaltB[(((31U - aIndex) + 5U)) & S_SALT1]);
            //
            aCarry = aCarry + (RotL64(aWandererE, 39U) ^ aWandererF);
            aCarry = aCarry + (aWandererH ^ RotL64(aWandererD, 60U));
            aCarry = aCarry + (RotL64(aWandererG, 57U) ^ aWandererA);
            aCarry = aCarry + (RotL64(aWandererB, 27U) ^ aWandererC);
            aCarry = aCarry + RotL64(aWandererJ, 21U);
            aCarry = aCarry + RotL64(aIngress, 36U);
            aCarry = TwistMix64::DiffuseA(aCarry);
            //
            aWorkLaneA[aIndex] = aIngress;
        }
    
        // twist_loop_a loop 2
        // ingress from: aWorkLaneA, aKeyRowReadA
        // ingress directions: aWorkLaneA forward forced, aKeyRowReadA forward/backward random
        // cross from: aKeyRowReadB, mSource
        // cross directions: aKeyRowReadB backward forced, mSource backward/forward random
        // write to: aWorkLaneB
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = RotL64(aWorkLaneA[((aIndex + 3801U)) & S_BLOCK1], 41U) ^ RotL64(aKeyRowReadA[(((2047U - aIndex) + 3314U)) & W_KEY1], 26U);
            aIngress = TwistMix64::DiffuseC(aIngress);
            //
            aCross = RotL64(aKeyRowReadB[(((2047U - aIndex) + 2974U)) & W_KEY1], 20U) ^ RotL64(mSource[((S_BLOCK1 - aIndex + 4372U)) & S_BLOCK1], 57U);
            aCross = TwistMix64::DiffuseC(aCross);
            //
            aScatter = (RotL64(aCarry, 19U) + RotL64(aIngress, 35U)) + (RotL64(aCross, 50U) ^ RotL64(aPrevious, 5U));
            aScatter = TwistMix64::DiffuseC(aScatter);
            //
            aOrbiterE = (aWandererC + RotL64(aPrevious, 12U)) + 9654059367478508868U;
            aOrbiterF = ((aWandererB + RotL64(aScatter, 19U)) + RotL64(aCarry, 57U)) + 6473006635864677427U;
            aOrbiterB = (aWandererD + RotL64(aIngress, 41U)) + 6944184481315853243U;
            aOrbiterC = ((aWandererG + RotL64(aCross, 29U)) + RotL64(aCarry, 21U)) + 4061496421939102306U;
            aOrbiterG = ((aWandererK + RotL64(aPrevious, 53U)) + 15791809275719085463U) + aPhaseAOrbiterAssignSaltC[((aIndex + 17U)) & S_SALT1];
            aOrbiterI = (aWandererA + RotL64(aIngress, 47U)) + 14050798802646323055U;
            aOrbiterA = ((aWandererF + RotL64(aScatter, 6U)) + 12072905924741758266U) + aPhaseAOrbiterAssignSaltE[(((31U - aIndex) + 4U)) & S_SALT1];
            aOrbiterD = (aWandererH + RotL64(aCross, 37U)) + 17639076509231343896U;
            aOrbiterH = ((aWandererJ + RotL64(aIngress, 57U)) + RotL64(aCarry, 35U)) + 12195388285571234715U;
            //
            aOrbiterE = (aOrbiterE + aOrbiterF) + 4325404419499496529U;
            aOrbiterB = (aOrbiterB ^ aOrbiterE) ^ 5910567888204238382U;
            aOrbiterB = RotL64((aOrbiterB * 11503787177122206937U), 21U);
            //
            aOrbiterC = (aOrbiterC + aOrbiterG) + 13092940059929942699U;
            aOrbiterE = ((aOrbiterE ^ aOrbiterC) ^ 13381962590820308761U) ^ aPhaseAOrbiterUpdateSaltC[(((31U - aIndex) + 9U)) & S_SALT1];
            aOrbiterE = RotL64((aOrbiterE * 6345904465930943295U), 43U);
            //
            aOrbiterI = (aOrbiterI + aOrbiterC) + 15622862439323440527U;
            aOrbiterA = (aOrbiterA ^ aOrbiterI) ^ 14027151901132249793U;
            aOrbiterA = RotL64((aOrbiterA * 2273573821630510087U), 57U);
            //
            aOrbiterF = (aOrbiterF + aOrbiterA) + 4584410023907605157U;
            aOrbiterD = (aOrbiterD ^ aOrbiterF) ^ 15763755180625487157U;
            aOrbiterD = RotL64((aOrbiterD * 6755736130607297639U), 39U);
            //
            aOrbiterB = (aOrbiterB + aOrbiterD) + 17023059745666559199U;
            aOrbiterG = (aOrbiterG ^ aOrbiterB) ^ 5298529579288492971U;
            aOrbiterG = RotL64((aOrbiterG * 2483562793328357721U), 27U);
            //
            aOrbiterH = (aOrbiterH + aOrbiterB) + 2870152867331654736U;
            aOrbiterC = ((aOrbiterC ^ aOrbiterH) ^ 12017191100173748848U) ^ aPhaseAOrbiterUpdateSaltF[(((31U - aIndex) + 28U)) & S_SALT1];
            aOrbiterC = RotL64((aOrbiterC * 9958191466506480519U), 5U);
            //
            aOrbiterG = ((aOrbiterG + aOrbiterI) + 15899529176182436062U) + aPhaseAOrbiterUpdateSaltE[((aIndex + 19U)) & S_SALT1];
            aOrbiterF = (aOrbiterF ^ aOrbiterG) ^ 16482713846343388735U;
            aOrbiterF = RotL64((aOrbiterF * 719465695044265601U), 11U);
            //
            aOrbiterD = ((aOrbiterD + aOrbiterH) + 12943393531812774449U) + aPhaseAOrbiterUpdateSaltA[(((31U - aIndex) + 16U)) & S_SALT1];
            aOrbiterI = (aOrbiterI ^ aOrbiterD) ^ 9881108254540483225U;
            aOrbiterI = RotL64((aOrbiterI * 8011108108007885059U), 35U);
            //
            aOrbiterA = (aOrbiterA + aOrbiterE) + 3532054586199716750U;
            aOrbiterH = (aOrbiterH ^ aOrbiterA) ^ 7142230313294797435U;
            aOrbiterH = RotL64((aOrbiterH * 14154176174768868421U), 51U);
            //
            aIngress = RotL64(aOrbiterI, 11U) ^ aOrbiterE;
            aIngress = aIngress + (RotL64(aOrbiterH, 50U) ^ aOrbiterC);
            aIngress = aIngress + (RotL64(aOrbiterG, 53U) ^ aOrbiterF);
            aIngress = aIngress + (aOrbiterD ^ RotL64(aOrbiterA, 41U));
            aIngress = aIngress + RotL64(aOrbiterB, 5U);
            aIngress = TwistMix64::DiffuseB((aIngress + aScatter));
            //
            aWandererG = aWandererG + ((RotL64(aIngress, 53U) + RotL64(aOrbiterA, 13U)) + aOrbiterB);
            aWandererB = aWandererB ^ ((RotL64(aCross, 5U) + RotL64(aOrbiterF, 43U)) + aOrbiterE);
            aWandererK = aWandererK + (((RotL64(aPrevious, 26U) + RotL64(aOrbiterB, 22U)) + aOrbiterI) + RotL64(aCarry, 5U));
            aWandererA = aWandererA ^ (((RotL64(aScatter, 19U) + aOrbiterC) + RotL64(aOrbiterH, 5U)) + aPhaseAWandererUpdateSaltA[((aIndex + 7U)) & S_SALT1]);
            aWandererD = aWandererD + (((RotL64(aIngress, 39U) + aOrbiterH) + RotL64(aOrbiterB, 57U)) + aPhaseAWandererUpdateSaltD[((aIndex + 20U)) & S_SALT1]);
            aWandererH = aWandererH ^ ((RotL64(aScatter, 43U) + aOrbiterF) + RotL64(aOrbiterB, 51U));
            aWandererJ = aWandererJ + ((RotL64(aCross, 47U) + RotL64(aOrbiterD, 39U)) + aOrbiterE);
            aWandererC = aWandererC ^ ((RotL64(aPrevious, 60U) + RotL64(aOrbiterA, 35U)) + aOrbiterG);
            aWandererF = aWandererF + (((RotL64(aScatter, 11U) + RotL64(aOrbiterB, 28U)) + aOrbiterE) + RotL64(aCarry, 27U));
            //
            aCarry = aCarry + (RotL64(aWandererG, 43U) ^ aWandererB);
            aCarry = aCarry + (RotL64(aWandererC, 29U) ^ aWandererA);
            aCarry = aCarry + (aWandererJ ^ RotL64(aWandererK, 51U));
            aCarry = aCarry + (RotL64(aWandererH, 60U) ^ aWandererD);
            aCarry = aCarry + RotL64(aWandererF, 35U);
            aCarry = aCarry + RotL64(aIngress, 3U);
            aCarry = TwistMix64::DiffuseC(aCarry);
            //
            aWorkLaneB[S_BLOCK1 - aIndex] = aIngress;
        }
    
        // twist_loop_a loop 3
        // ingress from: aWorkLaneB, aKeyRowReadB
        // ingress directions: aWorkLaneB forward forced, aKeyRowReadB forward/backward random
        // cross from: aKeyRowReadA, mSource, aWorkLaneA
        // cross directions: aKeyRowReadA backward forced, mSource backward forced, aWorkLaneA backward/forward random
        // write to: aInvestLaneA
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = RotL64(aWorkLaneB[((aIndex + 7260U)) & S_BLOCK1], 37U) ^ RotL64(aKeyRowReadB[(((2047U - aIndex) + 7754U)) & W_KEY1], 4U);
            aIngress = TwistMix64::DiffuseB(aIngress);
            //
            aCross = (RotL64(aKeyRowReadA[(((2047U - aIndex) + 7960U)) & W_KEY1], 57U) ^ RotL64(mSource[((S_BLOCK1 - aIndex + 6067U)) & S_BLOCK1], 42U));
            aCross ^= RotL64(aWorkLaneA[((S_BLOCK1 - aIndex + 6427U)) & S_BLOCK1], 11U);
            aCross = TwistMix64::DiffuseA(aCross);
            //
            aScatter = (RotL64(aCarry, 29U) ^ RotL64(aPrevious, 14U)) + (RotL64(aIngress, 41U) + RotL64(aCross, 53U));
            aScatter = TwistMix64::DiffuseB(aScatter);
            //
            aOrbiterI = (aWandererD + RotL64(aIngress, 60U)) + 3612110001869385068U;
            aOrbiterH = (aWandererK + RotL64(aScatter, 41U)) + 16340824141280225936U;
            aOrbiterA = ((aWandererC + RotL64(aPrevious, 19U)) + RotL64(aCarry, 53U)) + 15222338965130765231U;
            aOrbiterG = (aWandererA + RotL64(aCross, 11U)) + 6649270508107155041U;
            aOrbiterE = (aWandererF + RotL64(aPrevious, 3U)) + 768217258655426384U;
            aOrbiterB = ((aWandererE + RotL64(aIngress, 23U)) + RotL64(aCarry, 43U)) + 4481855259658861851U;
            aOrbiterF = (((aWandererG + RotL64(aCross, 54U)) + RotL64(aCarry, 11U)) + 18318041934562434016U) + aPhaseAOrbiterAssignSaltD[((aIndex + 21U)) & S_SALT1];
            aOrbiterJ = ((aWandererJ + RotL64(aScatter, 37U)) + 4212457153804401807U) + aPhaseAOrbiterAssignSaltA[(((31U - aIndex) + 4U)) & S_SALT1];
            aOrbiterK = (aWandererH + RotL64(aCross, 29U)) + 16143621095636987628U;
            //
            aOrbiterI = (aOrbiterI + aOrbiterH) + 2095664232866642086U;
            aOrbiterA = (aOrbiterA ^ aOrbiterI) ^ 4339527736737366572U;
            aOrbiterA = RotL64((aOrbiterA * 17503569508822244125U), 27U);
            //
            aOrbiterG = ((aOrbiterG + aOrbiterE) + 13679353177869884790U) + aPhaseAOrbiterUpdateSaltF[(((31U - aIndex) + 11U)) & S_SALT1];
            aOrbiterH = (aOrbiterH ^ aOrbiterG) ^ 11582168502846418236U;
            aOrbiterH = RotL64((aOrbiterH * 135539430034462861U), 51U);
            //
            aOrbiterB = (aOrbiterB + aOrbiterF) + 10451330452898542191U;
            aOrbiterG = (aOrbiterG ^ aOrbiterB) ^ 12951448817640617841U;
            aOrbiterG = RotL64((aOrbiterG * 4141870904192742091U), 39U);
            //
            aOrbiterJ = (aOrbiterJ + aOrbiterG) + 15389161934419370747U;
            aOrbiterI = (aOrbiterI ^ aOrbiterJ) ^ 4754886272708253014U;
            aOrbiterI = RotL64((aOrbiterI * 16638243718191281597U), 43U);
            //
            aOrbiterE = ((aOrbiterE + aOrbiterK) + 11746389873929280688U) + aPhaseAOrbiterUpdateSaltA[((aIndex + 7U)) & S_SALT1];
            aOrbiterB = (aOrbiterB ^ aOrbiterE) ^ 12042680172517298768U;
            aOrbiterB = RotL64((aOrbiterB * 3814780289755857543U), 23U);
            //
            aOrbiterA = (aOrbiterA + aOrbiterJ) + 2648103752465009244U;
            aOrbiterK = (aOrbiterK ^ aOrbiterA) ^ 451594673632597973U;
            aOrbiterK = RotL64((aOrbiterK * 8496763663271072425U), 19U);
            //
            aOrbiterK = (aOrbiterK + aOrbiterI) + 5696534794094099710U;
            aOrbiterF = (aOrbiterF ^ aOrbiterK) ^ 14609435045257077395U;
            aOrbiterF = RotL64((aOrbiterF * 14658408563237468407U), 47U);
            //
            aOrbiterH = (aOrbiterH + aOrbiterB) + 11599395126850950133U;
            aOrbiterJ = ((aOrbiterJ ^ aOrbiterH) ^ 12699598504604446664U) ^ aPhaseAOrbiterUpdateSaltE[((aIndex + 5U)) & S_SALT1];
            aOrbiterJ = RotL64((aOrbiterJ * 14313494063098111823U), 5U);
            //
            aOrbiterF = (aOrbiterF + aOrbiterA) + 9398465148537154745U;
            aOrbiterE = ((aOrbiterE ^ aOrbiterF) ^ 12139736860648011256U) ^ aPhaseAOrbiterUpdateSaltB[((aIndex + 3U)) & S_SALT1];
            aOrbiterE = RotL64((aOrbiterE * 15257503229375247987U), 57U);
            //
            aIngress = aOrbiterJ ^ RotL64(aOrbiterB, 34U);
            aIngress = aIngress + (RotL64(aOrbiterG, 11U) ^ aOrbiterE);
            aIngress = aIngress + (aOrbiterH ^ RotL64(aOrbiterI, 21U));
            aIngress = aIngress + (aOrbiterA ^ RotL64(aOrbiterK, 47U));
            aIngress = aIngress + RotL64(aOrbiterF, 3U);
            aIngress = TwistMix64::DiffuseB((aIngress + aScatter));
            //
            aWandererA = aWandererA + (((RotL64(aIngress, 23U) + aOrbiterE) + RotL64(aOrbiterA, 29U)) + aPhaseAWandererUpdateSaltD[(((31U - aIndex) + 6U)) & S_SALT1]);
            aWandererC = aWandererC ^ ((RotL64(aPrevious, 27U) + RotL64(aOrbiterK, 10U)) + aOrbiterE);
            aWandererD = aWandererD + ((RotL64(aCross, 60U) + RotL64(aOrbiterB, 47U)) + aOrbiterE);
            aWandererF = aWandererF ^ ((RotL64(aScatter, 39U) + RotL64(aOrbiterA, 53U)) + aOrbiterI);
            aWandererJ = aWandererJ + (((RotL64(aPrevious, 35U) + aOrbiterI) + RotL64(aOrbiterF, 57U)) + RotL64(aCarry, 53U));
            aWandererK = aWandererK ^ (((RotL64(aScatter, 51U) + RotL64(aOrbiterH, 34U)) + aOrbiterI) + aPhaseAWandererUpdateSaltB[((aIndex + 13U)) & S_SALT1]);
            aWandererE = aWandererE + (((RotL64(aIngress, 19U) + aOrbiterF) + RotL64(aOrbiterG, 5U)) + RotL64(aCarry, 11U));
            aWandererH = aWandererH ^ ((RotL64(aCross, 6U) + aOrbiterJ) + RotL64(aOrbiterK, 21U));
            aWandererG = aWandererG + ((RotL64(aIngress, 47U) + aOrbiterB) + RotL64(aOrbiterH, 39U));
            //
            aCarry = aCarry + (RotL64(aWandererF, 46U) ^ aWandererG);
            aCarry = aCarry + (aWandererD ^ RotL64(aWandererE, 57U));
            aCarry = aCarry + (aWandererC ^ RotL64(aWandererA, 35U));
            aCarry = aCarry + (aWandererK ^ RotL64(aWandererH, 23U));
            aCarry = aCarry + RotL64(aWandererJ, 51U);
            aCarry = aCarry + RotL64(aIngress, 13U);
            aCarry = TwistMix64::DiffuseC(aCarry);
            //
            aInvestLaneA[aIndex] = aIngress;
        }
    
        // twist_loop_a loop 4
        // ingress from: aInvestLaneA, aKeyRowReadB, mSource, aWorkLaneA
        // ingress directions: aInvestLaneA forward forced, aKeyRowReadB forward forced, mSource forward forced, aWorkLaneA forward/backward random
        // cross from: aKeyRowReadA, aWorkLaneB
        // cross directions: aKeyRowReadA backward forced, aWorkLaneB backward/forward random
        // write to: aInvestLaneB
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aInvestLaneA[((aIndex + 10440U)) & S_BLOCK1], 29U) ^ RotL64(aKeyRowReadB[((aIndex + 9188U)) & W_KEY1], 58U));
            aIngress ^= (RotL64(mSource[((aIndex + 9127U)) & S_BLOCK1], 11U) ^ RotL64(aWorkLaneA[((aIndex + 8636U)) & S_BLOCK1], 43U));
            aIngress = TwistMix64::DiffuseA(aIngress);
            //
            aCross = RotL64(aKeyRowReadA[(((2047U - aIndex) + 8795U)) & W_KEY1], 29U) ^ RotL64(aWorkLaneB[((S_BLOCK1 - aIndex + 9671U)) & S_BLOCK1], 54U);
            aCross = TwistMix64::DiffuseC(aCross);
            //
            aScatter = (RotL64(aCarry, 37U) + RotL64(aPrevious, 5U)) + (RotL64(aCross, 23U) ^ RotL64(aIngress, 54U));
            aScatter = TwistMix64::DiffuseC(aScatter);
            //
            aOrbiterD = (aWandererE + RotL64(aScatter, 10U)) + 4848316479321533394U;
            aOrbiterG = (aWandererI + RotL64(aCross, 23U)) + 6919360256662636195U;
            aOrbiterK = ((aWandererJ + RotL64(aPrevious, 35U)) + 9897013582181108544U) + aPhaseBOrbiterAssignSaltF[(((31U - aIndex) + 8U)) & S_SALT1];
            aOrbiterH = (aWandererD + RotL64(aIngress, 3U)) + 7319353809896158678U;
            aOrbiterI = (aWandererC + RotL64(aCross, 47U)) + 2848175435514849859U;
            aOrbiterF = ((aWandererH + RotL64(aScatter, 52U)) + RotL64(aCarry, 27U)) + 6967780718720437934U;
            aOrbiterB = (((aWandererG + RotL64(aPrevious, 43U)) + RotL64(aCarry, 41U)) + 10143884766603388136U) + aPhaseBOrbiterAssignSaltD[((aIndex + 3U)) & S_SALT1];
            aOrbiterC = ((aWandererF + RotL64(aIngress, 29U)) + RotL64(aCarry, 53U)) + 8675965006150972051U;
            aOrbiterA = (aWandererB + RotL64(aScatter, 57U)) + 16350117755560994281U;
            //
            aOrbiterD = (aOrbiterD + aOrbiterG) + 17976597517118423760U;
            aOrbiterK = (aOrbiterK ^ aOrbiterD) ^ 1399631141355370237U;
            aOrbiterK = RotL64((aOrbiterK * 16537788276543236833U), 29U);
            //
            aOrbiterH = (aOrbiterH + aOrbiterD) + 3590613762034716792U;
            aOrbiterI = ((aOrbiterI ^ aOrbiterH) ^ 5134624314245932157U) ^ aPhaseBOrbiterUpdateSaltD[(((31U - aIndex) + 10U)) & S_SALT1];
            aOrbiterI = RotL64((aOrbiterI * 13077589037975283371U), 19U);
            //
            aOrbiterF = ((aOrbiterF + aOrbiterB) + 10082236952942943654U) + aPhaseBOrbiterUpdateSaltB[((aIndex + 11U)) & S_SALT1];
            aOrbiterC = (aOrbiterC ^ aOrbiterF) ^ 4015535035905433450U;
            aOrbiterC = RotL64((aOrbiterC * 4961808568701908559U), 39U);
            //
            aOrbiterG = ((aOrbiterG + aOrbiterI) + 611474103801573800U) + aPhaseBOrbiterUpdateSaltF[(((31U - aIndex) + 7U)) & S_SALT1];
            aOrbiterF = (aOrbiterF ^ aOrbiterG) ^ 5786708483794098001U;
            aOrbiterF = RotL64((aOrbiterF * 7694007039340089267U), 35U);
            //
            aOrbiterK = (aOrbiterK + aOrbiterF) + 5201943497363274455U;
            aOrbiterA = (aOrbiterA ^ aOrbiterK) ^ 9282160506938328489U;
            aOrbiterA = RotL64((aOrbiterA * 5368182164239021367U), 57U);
            //
            aOrbiterA = ((aOrbiterA + aOrbiterC) + 4932320527498940158U) + aPhaseBOrbiterUpdateSaltA[((aIndex + 17U)) & S_SALT1];
            aOrbiterD = (aOrbiterD ^ aOrbiterA) ^ 11576526341731392916U;
            aOrbiterD = RotL64((aOrbiterD * 1712051774729439363U), 3U);
            //
            aOrbiterB = (aOrbiterB + aOrbiterA) + 10790691517638887125U;
            aOrbiterH = (aOrbiterH ^ aOrbiterB) ^ 16280649213607464422U;
            aOrbiterH = RotL64((aOrbiterH * 10756733801499471873U), 47U);
            //
            aOrbiterC = (aOrbiterC + aOrbiterH) + 9553716940667712810U;
            aOrbiterG = (aOrbiterG ^ aOrbiterC) ^ 11827518270964003341U;
            aOrbiterG = RotL64((aOrbiterG * 1322489827908132831U), 43U);
            //
            aOrbiterI = (aOrbiterI + aOrbiterK) + 16777463701235809321U;
            aOrbiterB = (aOrbiterB ^ aOrbiterI) ^ 3375489084588454149U;
            aOrbiterB = RotL64((aOrbiterB * 3335010977457647307U), 11U);
            //
            aIngress = RotL64(aOrbiterH, 35U) ^ aOrbiterC;
            aIngress = aIngress + (RotL64(aOrbiterG, 4U) ^ aOrbiterB);
            aIngress = aIngress + (RotL64(aOrbiterD, 43U) ^ aOrbiterF);
            aIngress = aIngress + (RotL64(aOrbiterK, 21U) ^ aOrbiterA);
            aIngress = aIngress + RotL64(aOrbiterI, 47U);
            aIngress = TwistMix64::DiffuseB((aIngress + aScatter));
            //
            aWandererJ = aWandererJ + ((RotL64(aScatter, 54U) + aOrbiterK) + RotL64(aOrbiterB, 39U));
            aWandererE = aWandererE ^ ((RotL64(aIngress, 35U) + aOrbiterI) + RotL64(aOrbiterF, 3U));
            aWandererI = aWandererI + (((RotL64(aCross, 23U) + aOrbiterG) + RotL64(aOrbiterK, 43U)) + aPhaseBWandererUpdateSaltB[(((31U - aIndex) + 23U)) & S_SALT1]);
            aWandererC = aWandererC ^ ((RotL64(aPrevious, 41U) + RotL64(aOrbiterD, 47U)) + aOrbiterI);
            aWandererH = aWandererH + (((RotL64(aIngress, 19U) + RotL64(aOrbiterG, 58U)) + aOrbiterI) + RotL64(aCarry, 53U));
            aWandererB = aWandererB ^ ((RotL64(aScatter, 58U) + aOrbiterC) + RotL64(aOrbiterA, 35U));
            aWandererD = aWandererD + ((((RotL64(aPrevious, 13U) + RotL64(aOrbiterB, 11U)) + aOrbiterA) + RotL64(aCarry, 23U)) + aPhaseBWandererUpdateSaltA[(((31U - aIndex) + 6U)) & S_SALT1]);
            aWandererG = aWandererG ^ ((RotL64(aCross, 3U) + RotL64(aOrbiterB, 53U)) + aOrbiterH);
            aWandererF = aWandererF + ((RotL64(aIngress, 47U) + RotL64(aOrbiterK, 28U)) + aOrbiterD);
            //
            aCarry = aCarry + (aWandererJ ^ RotL64(aWandererD, 43U));
            aCarry = aCarry + (RotL64(aWandererI, 23U) ^ aWandererC);
            aCarry = aCarry + (RotL64(aWandererF, 27U) ^ aWandererB);
            aCarry = aCarry + (aWandererG ^ RotL64(aWandererH, 47U));
            aCarry = aCarry + RotL64(aWandererE, 34U);
            aCarry = aCarry + RotL64(aIngress, 51U);
            aCarry = TwistMix64::DiffuseC(aCarry);
            //
            aInvestLaneB[S_BLOCK1 - aIndex] = aIngress;
        }
    
        // twist_loop_a loop 5
        // ingress from: aInvestLaneB, aKeyRowReadA, aKeyRowReadB, mSource, aWorkLaneB
        // ingress directions: aInvestLaneB forward forced, aKeyRowReadA forward forced, aKeyRowReadB forward forced, mSource forward forced, aWorkLaneB forward/backward random
        // cross from: aWorkLaneA, aInvestLaneA
        // cross directions: aWorkLaneA backward forced, aInvestLaneA backward/forward random
        // write to: aFireLaneA
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aInvestLaneB[((aIndex + 13563U)) & S_BLOCK1], 11U) ^ RotL64(aKeyRowReadA[((aIndex + 12311U)) & W_KEY1], 56U));
            aIngress ^= (RotL64(aKeyRowReadB[((aIndex + 11950U)) & W_KEY1], 47U) ^ RotL64(mSource[((aIndex + 11812U)) & S_BLOCK1], 27U));
            aIngress ^= RotL64(aWorkLaneB[((S_BLOCK1 - aIndex + 12983U)) & S_BLOCK1], 19U);
            aIngress = TwistMix64::DiffuseC(aIngress);
            //
            aCross = RotL64(aWorkLaneA[((S_BLOCK1 - aIndex + 12308U)) & S_BLOCK1], 46U) ^ RotL64(aInvestLaneA[((aIndex + 12667U)) & S_BLOCK1], 19U);
            aCross = TwistMix64::DiffuseC(aCross);
            //
            aScatter = (RotL64(aCarry, 11U) ^ RotL64(aIngress, 57U)) + (RotL64(aCross, 38U) + RotL64(aPrevious, 23U));
            aScatter = TwistMix64::DiffuseC(aScatter);
            //
            aOrbiterA = ((aWandererB + RotL64(aScatter, 57U)) + 12311607308490066301U) + aPhaseBOrbiterAssignSaltE[((aIndex + 9U)) & S_SALT1];
            aOrbiterJ = (aWandererJ + RotL64(aIngress, 38U)) + 13100864684740679846U;
            aOrbiterD = (aWandererG + RotL64(aCross, 43U)) + 13697304189274329704U;
            aOrbiterE = ((aWandererE + RotL64(aPrevious, 27U)) + RotL64(aCarry, 53U)) + 9047976902871216732U;
            aOrbiterC = ((aWandererD + RotL64(aIngress, 53U)) + RotL64(aCarry, 29U)) + 2147897579538537888U;
            aOrbiterF = ((aWandererK + RotL64(aPrevious, 47U)) + 2072444829390996142U) + aPhaseBOrbiterAssignSaltC[(((31U - aIndex) + 24U)) & S_SALT1];
            aOrbiterK = (aWandererA + RotL64(aScatter, 19U)) + 2129307836981020908U;
            aOrbiterG = (aWandererF + RotL64(aCross, 12U)) + 10663145333751112064U;
            aOrbiterB = ((aWandererH + RotL64(aScatter, 3U)) + RotL64(aCarry, 13U)) + 15019844390503785459U;
            //
            aOrbiterA = (aOrbiterA + aOrbiterJ) + 5460865577557928142U;
            aOrbiterD = (aOrbiterD ^ aOrbiterA) ^ 15806522559993224197U;
            aOrbiterD = RotL64((aOrbiterD * 8722932687972240099U), 5U);
            //
            aOrbiterE = (aOrbiterE + aOrbiterA) + 6361113778657833389U;
            aOrbiterC = (aOrbiterC ^ aOrbiterE) ^ 8306013884615042570U;
            aOrbiterC = RotL64((aOrbiterC * 8234258702656728667U), 19U);
            //
            aOrbiterF = ((aOrbiterF + aOrbiterK) + 4038420580499706912U) + aPhaseBOrbiterUpdateSaltA[(((31U - aIndex) + 26U)) & S_SALT1];
            aOrbiterA = ((aOrbiterA ^ aOrbiterF) ^ 11908091484457158973U) ^ aPhaseBOrbiterUpdateSaltC[(((31U - aIndex) + 15U)) & S_SALT1];
            aOrbiterA = RotL64((aOrbiterA * 3964111175645156719U), 29U);
            //
            aOrbiterG = (aOrbiterG + aOrbiterC) + 11133912466611921250U;
            aOrbiterF = (aOrbiterF ^ aOrbiterG) ^ 2469227904206936928U;
            aOrbiterF = RotL64((aOrbiterF * 2704438771198001599U), 51U);
            //
            aOrbiterJ = ((aOrbiterJ + aOrbiterE) + 13234017916788297295U) + aPhaseBOrbiterUpdateSaltE[((aIndex + 12U)) & S_SALT1];
            aOrbiterG = (aOrbiterG ^ aOrbiterJ) ^ 9061117693840451988U;
            aOrbiterG = RotL64((aOrbiterG * 3637440416741459419U), 47U);
            //
            aOrbiterB = (aOrbiterB + aOrbiterF) + 12013423690843812324U;
            aOrbiterE = (aOrbiterE ^ aOrbiterB) ^ 14371779015144617412U;
            aOrbiterE = RotL64((aOrbiterE * 3359568073302062667U), 35U);
            //
            aOrbiterK = (aOrbiterK + aOrbiterB) + 10044883414565441442U;
            aOrbiterJ = (aOrbiterJ ^ aOrbiterK) ^ 14334898081890462218U;
            aOrbiterJ = RotL64((aOrbiterJ * 4878939077928220019U), 57U);
            //
            aOrbiterD = ((aOrbiterD + aOrbiterG) + 13788962593988366125U) + aPhaseBOrbiterUpdateSaltF[(((31U - aIndex) + 25U)) & S_SALT1];
            aOrbiterB = (aOrbiterB ^ aOrbiterD) ^ 8377887372059713516U;
            aOrbiterB = RotL64((aOrbiterB * 1925913354197206851U), 23U);
            //
            aOrbiterC = (aOrbiterC + aOrbiterD) + 4584439257847749371U;
            aOrbiterK = (aOrbiterK ^ aOrbiterC) ^ 13335592911357756498U;
            aOrbiterK = RotL64((aOrbiterK * 6515028218115896375U), 39U);
            //
            aIngress = RotL64(aOrbiterA, 10U) ^ aOrbiterD;
            aIngress = aIngress + (aOrbiterF ^ RotL64(aOrbiterE, 29U));
            aIngress = aIngress + (RotL64(aOrbiterG, 39U) ^ aOrbiterB);
            aIngress = aIngress + (aOrbiterJ ^ RotL64(aOrbiterC, 51U));
            aIngress = aIngress + RotL64(aOrbiterK, 47U);
            aIngress = TwistMix64::DiffuseA((aIngress + aScatter));
            //
            aWandererK = aWandererK + ((RotL64(aScatter, 29U) + RotL64(aOrbiterB, 43U)) + aOrbiterK);
            aWandererH = aWandererH ^ ((RotL64(aCross, 3U) + RotL64(aOrbiterB, 56U)) + aOrbiterC);
            aWandererA = aWandererA + (((RotL64(aPrevious, 41U) + aOrbiterK) + RotL64(aOrbiterJ, 51U)) + RotL64(aCarry, 5U));
            aWandererE = aWandererE ^ ((RotL64(aIngress, 34U) + aOrbiterB) + RotL64(aOrbiterG, 19U));
            aWandererJ = aWandererJ + (((RotL64(aCross, 19U) + aOrbiterA) + RotL64(aOrbiterG, 13U)) + aPhaseBWandererUpdateSaltF[((aIndex + 5U)) & S_SALT1]);
            aWandererD = aWandererD ^ (((RotL64(aScatter, 47U) + aOrbiterC) + RotL64(aOrbiterF, 29U)) + aPhaseBWandererUpdateSaltC[((aIndex + 21U)) & S_SALT1]);
            aWandererG = aWandererG + (((RotL64(aIngress, 51U) + aOrbiterC) + RotL64(aOrbiterE, 37U)) + RotL64(aCarry, 13U));
            aWandererB = aWandererB ^ ((RotL64(aPrevious, 24U) + aOrbiterD) + RotL64(aOrbiterG, 6U));
            aWandererF = aWandererF + ((RotL64(aCross, 57U) + aOrbiterD) + RotL64(aOrbiterB, 47U));
            //
            aCarry = aCarry + (aWandererG ^ RotL64(aWandererJ, 13U));
            aCarry = aCarry + (RotL64(aWandererD, 10U) ^ aWandererK);
            aCarry = aCarry + (aWandererH ^ RotL64(aWandererF, 47U));
            aCarry = aCarry + (RotL64(aWandererE, 19U) ^ aWandererA);
            aCarry = aCarry + RotL64(aWandererB, 23U);
            aCarry = aCarry + RotL64(aIngress, 57U);
            aCarry = TwistMix64::DiffuseA(aCarry);
            //
            aFireLaneA[aIndex] = aIngress;
        }
    
        // twist_loop_a loop 6
        // ingress from: aFireLaneA, aInvestLaneA
        // ingress directions: aFireLaneA forward forced, aInvestLaneA forward/backward random
        // cross from: aKeyRowReadA, aKeyRowReadB, mSource, aWorkLaneB, aWorkLaneA
        // cross directions: aKeyRowReadA backward forced, aKeyRowReadB backward forced, mSource backward forced, aWorkLaneB backward forced, aWorkLaneA backward/forward random
        // write to: aFireLaneB
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = RotL64(aFireLaneA[((aIndex + 15360U)) & S_BLOCK1], 36U) ^ RotL64(aInvestLaneA[((S_BLOCK1 - aIndex + 15873U)) & S_BLOCK1], 27U);
            aIngress = TwistMix64::DiffuseB(aIngress);
            //
            aCross = (RotL64(aKeyRowReadA[(((2047U - aIndex) + 13664U)) & W_KEY1], 13U) ^ RotL64(aKeyRowReadB[(((2047U - aIndex) + 15212U)) & W_KEY1], 46U));
            aCross ^= (RotL64(mSource[((S_BLOCK1 - aIndex + 16309U)) & S_BLOCK1], 37U) ^ RotL64(aWorkLaneB[((S_BLOCK1 - aIndex + 14705U)) & S_BLOCK1], 29U));
            aCross ^= RotL64(aWorkLaneA[((S_BLOCK1 - aIndex + 15094U)) & S_BLOCK1], 3U);
            aCross = TwistMix64::DiffuseC(aCross);
            //
            aScatter = (RotL64(aIngress, 41U) + RotL64(aCross, 53U)) + (RotL64(aPrevious, 20U) ^ RotL64(aCarry, 3U));
            aScatter = TwistMix64::DiffuseA(aScatter);
            //
            aOrbiterJ = (aWandererF + RotL64(aPrevious, 11U)) + 12692813903177772178U;
            aOrbiterA = (aWandererA + RotL64(aScatter, 19U)) + 7112496446691277899U;
            aOrbiterB = (((aWandererK + RotL64(aCross, 56U)) + RotL64(aCarry, 21U)) + 2112247138290568813U) + aPhaseBOrbiterAssignSaltE[((aIndex + 25U)) & S_SALT1];
            aOrbiterG = ((aWandererG + RotL64(aIngress, 43U)) + RotL64(aCarry, 13U)) + 3699421080882855947U;
            aOrbiterC = ((aWandererH + RotL64(aScatter, 3U)) + RotL64(aCarry, 37U)) + 13761832028354380922U;
            aOrbiterF = (aWandererB + RotL64(aIngress, 39U)) + 9243822514887600214U;
            aOrbiterK = (aWandererI + RotL64(aPrevious, 29U)) + 6863833516853046129U;
            aOrbiterH = (aWandererC + RotL64(aCross, 60U)) + 8863897995943098018U;
            aOrbiterI = ((aWandererE + RotL64(aPrevious, 23U)) + 13346785686701467520U) + aPhaseBOrbiterAssignSaltA[((aIndex + 4U)) & S_SALT1];
            //
            aOrbiterJ = (aOrbiterJ + aOrbiterA) + 15309543066305531619U;
            aOrbiterB = ((aOrbiterB ^ aOrbiterJ) ^ 17515530938817919111U) ^ aPhaseBOrbiterUpdateSaltF[(((31U - aIndex) + 28U)) & S_SALT1];
            aOrbiterB = RotL64((aOrbiterB * 16625193986319048245U), 23U);
            //
            aOrbiterG = (aOrbiterG + aOrbiterC) + 760493237816424254U;
            aOrbiterJ = (aOrbiterJ ^ aOrbiterG) ^ 7282586354117620860U;
            aOrbiterJ = RotL64((aOrbiterJ * 2327153408185290635U), 11U);
            //
            aOrbiterC = (aOrbiterC + aOrbiterF) + 4129706068526969105U;
            aOrbiterA = ((aOrbiterA ^ aOrbiterC) ^ 7020175432730888755U) ^ aPhaseBOrbiterUpdateSaltE[(((31U - aIndex) + 13U)) & S_SALT1];
            aOrbiterA = RotL64((aOrbiterA * 10095158356907592239U), 47U);
            //
            aOrbiterK = (aOrbiterK + aOrbiterH) + 9102258982216515596U;
            aOrbiterF = (aOrbiterF ^ aOrbiterK) ^ 10822031305361453690U;
            aOrbiterF = RotL64((aOrbiterF * 2036205056490578491U), 53U);
            //
            aOrbiterI = (aOrbiterI + aOrbiterJ) + 12571477440964330246U;
            aOrbiterH = (aOrbiterH ^ aOrbiterI) ^ 8436347026653095199U;
            aOrbiterH = RotL64((aOrbiterH * 17930734781213681573U), 29U);
            //
            aOrbiterB = (aOrbiterB + aOrbiterK) + 14214789872073941940U;
            aOrbiterC = ((aOrbiterC ^ aOrbiterB) ^ 12915911919403385001U) ^ aPhaseBOrbiterUpdateSaltB[((aIndex + 11U)) & S_SALT1];
            aOrbiterC = RotL64((aOrbiterC * 13161681603528031511U), 37U);
            //
            aOrbiterA = (aOrbiterA + aOrbiterI) + 15443240166233851298U;
            aOrbiterK = (aOrbiterK ^ aOrbiterA) ^ 7311369180113240915U;
            aOrbiterK = RotL64((aOrbiterK * 13339195007946889423U), 57U);
            //
            aOrbiterF = (aOrbiterF + aOrbiterG) + 12976516224995960015U;
            aOrbiterI = (aOrbiterI ^ aOrbiterF) ^ 7823308381434556721U;
            aOrbiterI = RotL64((aOrbiterI * 502385172763861451U), 19U);
            //
            aOrbiterH = (aOrbiterH + aOrbiterB) + 4829417661664149137U;
            aOrbiterG = ((aOrbiterG ^ aOrbiterH) ^ 16306394751966719700U) ^ aPhaseBOrbiterUpdateSaltC[(((31U - aIndex) + 5U)) & S_SALT1];
            aOrbiterG = RotL64((aOrbiterG * 5294376579588592157U), 43U);
            //
            aIngress = aOrbiterI ^ RotL64(aOrbiterJ, 21U);
            aIngress = aIngress + (RotL64(aOrbiterG, 53U) ^ aOrbiterA);
            aIngress = aIngress + (aOrbiterB ^ RotL64(aOrbiterK, 43U));
            aIngress = aIngress + (RotL64(aOrbiterF, 57U) ^ aOrbiterH);
            aIngress = aIngress + RotL64(aOrbiterC, 28U);
            aIngress = TwistMix64::DiffuseB((aIngress + aScatter));
            //
            aWandererA = aWandererA + ((RotL64(aCross, 3U) + aOrbiterK) + RotL64(aOrbiterH, 43U));
            aWandererK = aWandererK ^ ((RotL64(aIngress, 29U) + RotL64(aOrbiterB, 51U)) + aOrbiterI);
            aWandererH = aWandererH + ((RotL64(aScatter, 18U) + aOrbiterG) + RotL64(aOrbiterI, 47U));
            aWandererB = aWandererB ^ ((RotL64(aPrevious, 11U) + aOrbiterK) + RotL64(aOrbiterC, 60U));
            aWandererE = aWandererE + (((RotL64(aIngress, 23U) + aOrbiterC) + RotL64(aOrbiterF, 19U)) + RotL64(aCarry, 21U));
            aWandererG = aWandererG ^ (((RotL64(aCross, 53U) + aOrbiterJ) + RotL64(aOrbiterG, 39U)) + aPhaseBWandererUpdateSaltE[(((31U - aIndex) + 15U)) & S_SALT1]);
            aWandererI = aWandererI + (((RotL64(aPrevious, 43U) + aOrbiterA) + RotL64(aOrbiterJ, 35U)) + RotL64(aCarry, 35U));
            aWandererC = aWandererC ^ ((RotL64(aScatter, 58U) + aOrbiterA) + RotL64(aOrbiterI, 23U));
            aWandererF = aWandererF + (((RotL64(aPrevious, 47U) + aOrbiterC) + RotL64(aOrbiterJ, 56U)) + aPhaseBWandererUpdateSaltF[(((31U - aIndex) + 6U)) & S_SALT1]);
            //
            aCarry = aCarry + (RotL64(aWandererG, 5U) ^ aWandererK);
            aCarry = aCarry + (RotL64(aWandererH, 50U) ^ aWandererE);
            aCarry = aCarry + (RotL64(aWandererB, 47U) ^ aWandererC);
            aCarry = aCarry + (aWandererI ^ RotL64(aWandererA, 13U));
            aCarry = aCarry + RotL64(aWandererF, 27U);
            aCarry = aCarry + RotL64(aIngress, 20U);
            aCarry = TwistMix64::DiffuseC(aCarry);
            //
            aFireLaneB[S_BLOCK1 - aIndex] = aIngress;
        }
    
        // twist_loop_a loop 7
        // ingress from: aFireLaneB, aKeyRowReadA, mSource, aWorkLaneA
        // ingress directions: aFireLaneB forward forced, aKeyRowReadA forward forced, mSource forward forced, aWorkLaneA forward/backward random
        // cross from: aKeyRowReadB, aInvestLaneB, aFireLaneA
        // cross directions: aKeyRowReadB backward forced, aInvestLaneB backward forced, aFireLaneA backward/forward random
        // write to: aFireLaneC
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aFireLaneB[((aIndex + 16543U)) & S_BLOCK1], 47U) ^ RotL64(aKeyRowReadA[((aIndex + 17020U)) & W_KEY1], 11U));
            aIngress ^= (RotL64(mSource[((aIndex + 18492U)) & S_BLOCK1], 26U) ^ RotL64(aWorkLaneA[((aIndex + 18051U)) & S_BLOCK1], 57U));
            aIngress = TwistMix64::DiffuseA(aIngress);
            //
            aCross = (RotL64(aKeyRowReadB[(((2047U - aIndex) + 18167U)) & W_KEY1], 29U) ^ RotL64(aInvestLaneB[((S_BLOCK1 - aIndex + 18270U)) & S_BLOCK1], 19U));
            aCross ^= RotL64(aFireLaneA[((S_BLOCK1 - aIndex + 17655U)) & S_BLOCK1], 50U);
            aCross = TwistMix64::DiffuseB(aCross);
            //
            aScatter = (RotL64(aIngress, 38U) + RotL64(aCarry, 57U)) + (RotL64(aPrevious, 5U) ^ RotL64(aCross, 21U));
            aScatter = TwistMix64::DiffuseA(aScatter);
            //
            aOrbiterI = (aWandererC + RotL64(aCross, 23U)) + 16519040829220310189U;
            aOrbiterH = ((aWandererE + RotL64(aIngress, 47U)) + RotL64(aCarry, 29U)) + 6888002778416941825U;
            aOrbiterK = ((aWandererA + RotL64(aScatter, 3U)) + 1310832187746534025U) + aPhaseCOrbiterAssignSaltF[((aIndex + 7U)) & S_SALT1];
            aOrbiterJ = (aWandererG + RotL64(aPrevious, 37U)) + 5890888009051281674U;
            aOrbiterG = ((aWandererJ + RotL64(aScatter, 18U)) + RotL64(aCarry, 13U)) + 5143864838362464857U;
            aOrbiterE = ((aWandererI + RotL64(aIngress, 43U)) + 15591534069452660003U) + aPhaseCOrbiterAssignSaltC[((aIndex + 23U)) & S_SALT1];
            aOrbiterF = (aWandererB + RotL64(aCross, 53U)) + 1466867671765325096U;
            aOrbiterD = ((aWandererF + RotL64(aPrevious, 13U)) + RotL64(aCarry, 21U)) + 13931443680107902488U;
            aOrbiterC = (aWandererH + RotL64(aScatter, 28U)) + 15400747367673245552U;
            //
            aOrbiterI = (aOrbiterI + aOrbiterH) + 2836975369734495759U;
            aOrbiterK = (aOrbiterK ^ aOrbiterI) ^ 2370720358274970117U;
            aOrbiterK = RotL64((aOrbiterK * 4615571902817575375U), 19U);
            //
            aOrbiterH = ((aOrbiterH + aOrbiterJ) + 3470677184188006133U) + aPhaseCOrbiterUpdateSaltC[((aIndex + 9U)) & S_SALT1];
            aOrbiterG = (aOrbiterG ^ aOrbiterH) ^ 7175584278499266723U;
            aOrbiterG = RotL64((aOrbiterG * 10067096593682482345U), 3U);
            //
            aOrbiterG = (aOrbiterG + aOrbiterE) + 6095078817776863055U;
            aOrbiterF = (aOrbiterF ^ aOrbiterG) ^ 2176637999243513070U;
            aOrbiterF = RotL64((aOrbiterF * 12215701810843975501U), 23U);
            //
            aOrbiterE = (aOrbiterE + aOrbiterK) + 5580391239754903129U;
            aOrbiterD = ((aOrbiterD ^ aOrbiterE) ^ 15196125567953871184U) ^ aPhaseCOrbiterUpdateSaltF[(((31U - aIndex) + 26U)) & S_SALT1];
            aOrbiterD = RotL64((aOrbiterD * 12686361960729564519U), 35U);
            //
            aOrbiterC = (aOrbiterC + aOrbiterF) + 12787014151503209931U;
            aOrbiterJ = (aOrbiterJ ^ aOrbiterC) ^ 1523153207064063495U;
            aOrbiterJ = RotL64((aOrbiterJ * 3113907543551927561U), 57U);
            //
            aOrbiterD = ((aOrbiterD + aOrbiterC) + 12973289026485937829U) + aPhaseCOrbiterUpdateSaltB[(((31U - aIndex) + 18U)) & S_SALT1];
            aOrbiterH = (aOrbiterH ^ aOrbiterD) ^ 9087439766232078173U;
            aOrbiterH = RotL64((aOrbiterH * 5817029335999350327U), 51U);
            //
            aOrbiterK = (aOrbiterK + aOrbiterG) + 16318022893068674015U;
            aOrbiterC = (aOrbiterC ^ aOrbiterK) ^ 11089160685103562409U;
            aOrbiterC = RotL64((aOrbiterC * 17087834321385147603U), 27U);
            //
            aOrbiterF = (aOrbiterF + aOrbiterD) + 8680037953925067235U;
            aOrbiterI = ((aOrbiterI ^ aOrbiterF) ^ 3112588943274158119U) ^ aPhaseCOrbiterUpdateSaltD[(((31U - aIndex) + 6U)) & S_SALT1];
            aOrbiterI = RotL64((aOrbiterI * 9214011370307670371U), 43U);
            //
            aOrbiterJ = (aOrbiterJ + aOrbiterI) + 16749015684369649821U;
            aOrbiterE = (aOrbiterE ^ aOrbiterJ) ^ 9419550535891334966U;
            aOrbiterE = RotL64((aOrbiterE * 5421312787569114811U), 39U);
            //
            aIngress = aOrbiterJ ^ RotL64(aOrbiterH, 60U);
            aIngress = aIngress + (aOrbiterE ^ RotL64(aOrbiterD, 53U));
            aIngress = aIngress + (RotL64(aOrbiterK, 47U) ^ aOrbiterF);
            aIngress = aIngress + (aOrbiterI ^ RotL64(aOrbiterG, 5U));
            aIngress = aIngress + RotL64(aOrbiterC, 39U);
            aIngress = TwistMix64::DiffuseB((aIngress + aScatter));
            //
            aWandererB = aWandererB ^ ((RotL64(aScatter, 43U) + aOrbiterG) + RotL64(aOrbiterD, 28U));
            aWandererI = aWandererI + (((RotL64(aIngress, 57U) + RotL64(aOrbiterK, 19U)) + aOrbiterC) + aPhaseCWandererUpdateSaltA[(((31U - aIndex) + 29U)) & S_SALT1]);
            aWandererJ = aWandererJ ^ ((RotL64(aPrevious, 34U) + aOrbiterH) + RotL64(aOrbiterG, 23U));
            aWandererH = aWandererH + (((RotL64(aCross, 39U) + RotL64(aOrbiterI, 51U)) + aOrbiterK) + RotL64(aCarry, 23U));
            aWandererC = aWandererC ^ ((RotL64(aPrevious, 3U) + aOrbiterJ) + RotL64(aOrbiterE, 3U));
            aWandererF = aWandererF + (((RotL64(aIngress, 51U) + aOrbiterF) + RotL64(aOrbiterD, 56U)) + RotL64(aCarry, 51U));
            aWandererE = aWandererE ^ (((RotL64(aCross, 11U) + aOrbiterC) + RotL64(aOrbiterD, 41U)) + aPhaseCWandererUpdateSaltB[((aIndex + 25U)) & S_SALT1]);
            aWandererA = aWandererA + ((RotL64(aScatter, 22U) + RotL64(aOrbiterE, 35U)) + aOrbiterC);
            aWandererG = aWandererG ^ ((RotL64(aCross, 27U) + aOrbiterH) + RotL64(aOrbiterC, 13U));
            //
            aCarry = aCarry + (aWandererI ^ RotL64(aWandererF, 57U));
            aCarry = aCarry + (RotL64(aWandererG, 39U) ^ aWandererC);
            aCarry = aCarry + (aWandererH ^ RotL64(aWandererB, 50U));
            aCarry = aCarry + (aWandererE ^ RotL64(aWandererJ, 27U));
            aCarry = aCarry + RotL64(aWandererA, 47U);
            aCarry = aCarry + RotL64(aIngress, 35U);
            aCarry = TwistMix64::DiffuseA(aCarry);
            //
            aFireLaneC[aIndex] = aIngress;
        }
    
        // twist_loop_a loop 8
        // ingress from: aFireLaneC, mSource, aFireLaneA, aWorkLaneA
        // ingress directions: aFireLaneC forward forced, mSource forward forced, aFireLaneA forward forced, aWorkLaneA forward/backward random
        // cross from: aKeyRowReadA, aKeyRowReadB, aFireLaneB, aWorkLaneB
        // cross directions: aKeyRowReadA backward forced, aKeyRowReadB backward forced, aFireLaneB backward forced, aWorkLaneB backward/forward random
        // write to: aFireLaneD
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aFireLaneC[((aIndex + 20154U)) & S_BLOCK1], 5U) ^ RotL64(mSource[((aIndex + 19768U)) & S_BLOCK1], 13U));
            aIngress ^= (RotL64(aFireLaneA[((aIndex + 19835U)) & S_BLOCK1], 39U) ^ RotL64(aWorkLaneA[((S_BLOCK1 - aIndex + 21712U)) & S_BLOCK1], 58U));
            aIngress = TwistMix64::DiffuseC(aIngress);
            //
            aCross = (RotL64(aKeyRowReadA[(((2047U - aIndex) + 20984U)) & W_KEY1], 19U) ^ RotL64(aKeyRowReadB[(((2047U - aIndex) + 20766U)) & W_KEY1], 43U));
            aCross ^= (RotL64(aFireLaneB[((S_BLOCK1 - aIndex + 19433U)) & S_BLOCK1], 34U) ^ RotL64(aWorkLaneB[((aIndex + 21660U)) & S_BLOCK1], 3U));
            aCross = TwistMix64::DiffuseC(aCross);
            //
            aScatter = (RotL64(aPrevious, 5U) + RotL64(aCarry, 43U)) ^ (RotL64(aCross, 22U) + RotL64(aIngress, 57U));
            aScatter = TwistMix64::DiffuseB(aScatter);
            //
            aOrbiterC = ((aWandererD + RotL64(aScatter, 11U)) + RotL64(aCarry, 35U)) + 9133751643283278896U;
            aOrbiterE = (aWandererI + RotL64(aPrevious, 3U)) + 8971581804375380408U;
            aOrbiterF = (((aWandererF + RotL64(aIngress, 43U)) + RotL64(aCarry, 57U)) + 12559650383714566592U) + aPhaseCOrbiterAssignSaltD[((aIndex + 13U)) & S_SALT1];
            aOrbiterG = ((aWandererK + RotL64(aCross, 27U)) + 15753206088872859163U) + aPhaseCOrbiterAssignSaltC[((aIndex + 11U)) & S_SALT1];
            aOrbiterH = (aWandererC + RotL64(aPrevious, 54U)) + 7640756270450762350U;
            aOrbiterB = (aWandererH + RotL64(aCross, 39U)) + 7340073357551376125U;
            aOrbiterJ = (aWandererJ + RotL64(aIngress, 23U)) + 5270256573644196046U;
            aOrbiterD = (aWandererE + RotL64(aScatter, 47U)) + 3567367996479995928U;
            aOrbiterA = ((aWandererA + RotL64(aCross, 58U)) + RotL64(aCarry, 13U)) + 11939634537492733738U;
            //
            aOrbiterC = (aOrbiterC + aOrbiterE) + 7051817732424527120U;
            aOrbiterF = (aOrbiterF ^ aOrbiterC) ^ 1730487669951837941U;
            aOrbiterF = RotL64((aOrbiterF * 15191634337956285841U), 51U);
            //
            aOrbiterG = (aOrbiterG + aOrbiterH) + 18009252467909454817U;
            aOrbiterB = ((aOrbiterB ^ aOrbiterG) ^ 2361024272031696442U) ^ aPhaseCOrbiterUpdateSaltB[(((31U - aIndex) + 7U)) & S_SALT1];
            aOrbiterB = RotL64((aOrbiterB * 15215151562500226027U), 43U);
            //
            aOrbiterJ = (aOrbiterJ + aOrbiterF) + 15902755877642960397U;
            aOrbiterH = (aOrbiterH ^ aOrbiterJ) ^ 12243517544704116184U;
            aOrbiterH = RotL64((aOrbiterH * 2576071074148141447U), 29U);
            //
            aOrbiterH = (aOrbiterH + aOrbiterD) + 16846181962302186187U;
            aOrbiterC = (aOrbiterC ^ aOrbiterH) ^ 636121425116506681U;
            aOrbiterC = RotL64((aOrbiterC * 17075030673338779993U), 47U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterG) + 6887385655828217318U;
            aOrbiterE = (aOrbiterE ^ aOrbiterD) ^ 3705834550934775862U;
            aOrbiterE = RotL64((aOrbiterE * 11275428284929594435U), 13U);
            //
            aOrbiterA = (aOrbiterA + aOrbiterJ) + 11165142437077969438U;
            aOrbiterG = ((aOrbiterG ^ aOrbiterA) ^ 6426659930331618269U) ^ aPhaseCOrbiterUpdateSaltC[(((31U - aIndex) + 23U)) & S_SALT1];
            aOrbiterG = RotL64((aOrbiterG * 17170640810530893705U), 19U);
            //
            aOrbiterB = ((aOrbiterB + aOrbiterC) + 12629082390899315789U) + aPhaseCOrbiterUpdateSaltD[((aIndex + 8U)) & S_SALT1];
            aOrbiterJ = (aOrbiterJ ^ aOrbiterB) ^ 4277510580069574724U;
            aOrbiterJ = RotL64((aOrbiterJ * 9829125163412708305U), 23U);
            //
            aOrbiterF = (aOrbiterF + aOrbiterA) + 13814834144170469978U;
            aOrbiterD = (aOrbiterD ^ aOrbiterF) ^ 3698381854100295826U;
            aOrbiterD = RotL64((aOrbiterD * 5126359230872258015U), 37U);
            //
            aOrbiterE = (aOrbiterE + aOrbiterB) + 11623170635983579937U;
            aOrbiterA = ((aOrbiterA ^ aOrbiterE) ^ 7247413650388803796U) ^ aPhaseCOrbiterUpdateSaltF[((aIndex + 19U)) & S_SALT1];
            aOrbiterA = RotL64((aOrbiterA * 3403219499465560059U), 3U);
            //
            aIngress = aOrbiterB ^ RotL64(aOrbiterG, 44U);
            aIngress = aIngress + (RotL64(aOrbiterE, 51U) ^ aOrbiterF);
            aIngress = aIngress + (aOrbiterJ ^ RotL64(aOrbiterH, 57U));
            aIngress = aIngress + (RotL64(aOrbiterD, 13U) ^ aOrbiterC);
            aIngress = aIngress + RotL64(aOrbiterA, 47U);
            aIngress = TwistMix64::DiffuseB((aIngress + aScatter));
            //
            aWandererE = aWandererE + ((RotL64(aPrevious, 6U) + aOrbiterA) + RotL64(aOrbiterB, 58U));
            aWandererA = aWandererA ^ ((RotL64(aCross, 13U) + RotL64(aOrbiterC, 35U)) + aOrbiterB);
            aWandererH = aWandererH + ((RotL64(aScatter, 47U) + aOrbiterE) + RotL64(aOrbiterH, 39U));
            aWandererK = aWandererK ^ ((RotL64(aIngress, 57U) + aOrbiterD) + RotL64(aOrbiterE, 47U));
            aWandererF = aWandererF + (((RotL64(aPrevious, 41U) + aOrbiterG) + RotL64(aOrbiterF, 27U)) + RotL64(aCarry, 43U));
            aWandererJ = aWandererJ ^ (((RotL64(aIngress, 53U) + aOrbiterE) + RotL64(aOrbiterB, 13U)) + aPhaseCWandererUpdateSaltB[((aIndex + 15U)) & S_SALT1]);
            aWandererD = aWandererD + (((RotL64(aScatter, 28U) + RotL64(aOrbiterF, 51U)) + aOrbiterD) + RotL64(aCarry, 51U));
            aWandererI = aWandererI ^ ((RotL64(aCross, 37U) + aOrbiterJ) + RotL64(aOrbiterH, 3U));
            aWandererC = aWandererC + (((RotL64(aIngress, 19U) + aOrbiterD) + RotL64(aOrbiterG, 18U)) + aPhaseCWandererUpdateSaltF[(((31U - aIndex) + 4U)) & S_SALT1]);
            //
            aCarry = aCarry + (aWandererD ^ RotL64(aWandererC, 35U));
            aCarry = aCarry + (RotL64(aWandererA, 28U) ^ aWandererH);
            aCarry = aCarry + (RotL64(aWandererE, 53U) ^ aWandererF);
            aCarry = aCarry + (RotL64(aWandererK, 43U) ^ aWandererJ);
            aCarry = aCarry + RotL64(aWandererI, 5U);
            aCarry = aCarry + RotL64(aIngress, 13U);
            aCarry = TwistMix64::DiffuseC(aCarry);
            //
            aFireLaneD[S_BLOCK1 - aIndex] = aIngress;
        }
    
        // twist_loop_a loop 9
        // ingress from: aFireLaneD, aKeyRowReadA, aKeyRowReadB, aFireLaneC
        // ingress directions: aFireLaneD forward forced, aKeyRowReadA forward forced, aKeyRowReadB forward forced, aFireLaneC forward/backward random
        // cross from: mSource, aFireLaneA, aInvestLaneA, aInvestLaneB
        // cross directions: mSource backward forced, aFireLaneA backward forced, aInvestLaneA backward forced, aInvestLaneB backward/forward random
        // write to: aExpandLaneA
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aFireLaneD[((aIndex + 22356U)) & S_BLOCK1], 41U) ^ RotL64(aKeyRowReadA[((aIndex + 22619U)) & W_KEY1], 23U));
            aIngress ^= (RotL64(aKeyRowReadB[((aIndex + 23048U)) & W_KEY1], 50U) ^ RotL64(aFireLaneC[((aIndex + 22077U)) & S_BLOCK1], 3U));
            aIngress = TwistMix64::DiffuseB(aIngress);
            //
            aCross = (RotL64(mSource[((S_BLOCK1 - aIndex + 23444U)) & S_BLOCK1], 13U) ^ RotL64(aFireLaneA[((S_BLOCK1 - aIndex + 24261U)) & S_BLOCK1], 3U));
            aCross ^= (RotL64(aInvestLaneA[((S_BLOCK1 - aIndex + 22919U)) & S_BLOCK1], 35U) ^ RotL64(aInvestLaneB[((aIndex + 24432U)) & S_BLOCK1], 58U));
            aCross = TwistMix64::DiffuseA(aCross);
            //
            aScatter = (RotL64(aCross, 47U) + RotL64(aPrevious, 35U)) ^ (RotL64(aIngress, 21U) + RotL64(aCarry, 6U));
            aScatter = TwistMix64::DiffuseC(aScatter);
            //
            aOrbiterH = ((aWandererF + RotL64(aIngress, 46U)) + 8988572360732005217U) + aPhaseCOrbiterAssignSaltE[(((31U - aIndex) + 14U)) & S_SALT1];
            aOrbiterB = (aWandererD + RotL64(aCross, 11U)) + 17889613225105985335U;
            aOrbiterI = ((aWandererB + RotL64(aPrevious, 5U)) + RotL64(aCarry, 19U)) + 15563478320513948626U;
            aOrbiterC = ((aWandererJ + RotL64(aScatter, 39U)) + RotL64(aCarry, 37U)) + 3441351228410524816U;
            aOrbiterA = (aWandererI + RotL64(aPrevious, 29U)) + 4425592689451435346U;
            aOrbiterD = ((aWandererE + RotL64(aScatter, 53U)) + 12733160231627305928U) + aPhaseCOrbiterAssignSaltA[(((31U - aIndex) + 17U)) & S_SALT1];
            aOrbiterG = ((aWandererA + RotL64(aIngress, 57U)) + RotL64(aCarry, 5U)) + 3574152157304607854U;
            aOrbiterK = (aWandererK + RotL64(aCross, 24U)) + 15167631896729808783U;
            aOrbiterF = (aWandererH + RotL64(aIngress, 35U)) + 15822667973915417055U;
            //
            aOrbiterH = (aOrbiterH + aOrbiterB) + 17181685481076577637U;
            aOrbiterI = ((aOrbiterI ^ aOrbiterH) ^ 9979204751408873468U) ^ aPhaseCOrbiterUpdateSaltB[((aIndex + 15U)) & S_SALT1];
            aOrbiterI = RotL64((aOrbiterI * 8244434774754786565U), 41U);
            //
            aOrbiterC = ((aOrbiterC + aOrbiterA) + 1334240485667164762U) + aPhaseCOrbiterUpdateSaltC[(((31U - aIndex) + 3U)) & S_SALT1];
            aOrbiterH = (aOrbiterH ^ aOrbiterC) ^ 9190066751460137016U;
            aOrbiterH = RotL64((aOrbiterH * 14585141844653660363U), 19U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterI) + 15465215829109246336U;
            aOrbiterG = ((aOrbiterG ^ aOrbiterD) ^ 2305208282453624419U) ^ aPhaseCOrbiterUpdateSaltA[((aIndex + 19U)) & S_SALT1];
            aOrbiterG = RotL64((aOrbiterG * 10257861974108363283U), 47U);
            //
            aOrbiterA = (aOrbiterA + aOrbiterG) + 16951510027310993926U;
            aOrbiterB = (aOrbiterB ^ aOrbiterA) ^ 11117938943423526901U;
            aOrbiterB = RotL64((aOrbiterB * 7805486716716924787U), 37U);
            //
            aOrbiterG = (aOrbiterG + aOrbiterK) + 12461379120662979432U;
            aOrbiterF = (aOrbiterF ^ aOrbiterG) ^ 11719697049048823897U;
            aOrbiterF = RotL64((aOrbiterF * 14880996802304818757U), 57U);
            //
            aOrbiterF = (aOrbiterF + aOrbiterD) + 6843357278142933570U;
            aOrbiterA = (aOrbiterA ^ aOrbiterF) ^ 12727898578324702374U;
            aOrbiterA = RotL64((aOrbiterA * 9786435451654365097U), 3U);
            //
            aOrbiterI = ((aOrbiterI + aOrbiterC) + 18127999660067652233U) + aPhaseCOrbiterUpdateSaltE[(((31U - aIndex) + 12U)) & S_SALT1];
            aOrbiterK = (aOrbiterK ^ aOrbiterI) ^ 11754709060558683082U;
            aOrbiterK = RotL64((aOrbiterK * 12798744012150745847U), 27U);
            //
            aOrbiterB = (aOrbiterB + aOrbiterF) + 16940151146420516184U;
            aOrbiterC = (aOrbiterC ^ aOrbiterB) ^ 12924950783056761895U;
            aOrbiterC = RotL64((aOrbiterC * 8898170377271926745U), 53U);
            //
            aOrbiterK = (aOrbiterK + aOrbiterH) + 14829713915929878471U;
            aOrbiterD = (aOrbiterD ^ aOrbiterK) ^ 840466047621042565U;
            aOrbiterD = RotL64((aOrbiterD * 10748511630509529489U), 13U);
            //
            aIngress = aOrbiterK ^ RotL64(aOrbiterB, 5U);
            aIngress = aIngress + (aOrbiterG ^ RotL64(aOrbiterC, 29U));
            aIngress = aIngress + (RotL64(aOrbiterD, 35U) ^ aOrbiterA);
            aIngress = aIngress + (RotL64(aOrbiterH, 44U) ^ aOrbiterI);
            aIngress = aIngress + RotL64(aOrbiterF, 39U);
            aIngress = TwistMix64::DiffuseA((aIngress + aScatter));
            //
            aWandererB = aWandererB ^ ((RotL64(aCross, 5U) + RotL64(aOrbiterC, 30U)) + aOrbiterF);
            aWandererH = aWandererH + ((RotL64(aPrevious, 48U) + RotL64(aOrbiterD, 53U)) + aOrbiterF);
            aWandererK = aWandererK ^ ((RotL64(aScatter, 57U) + aOrbiterC) + RotL64(aOrbiterK, 11U));
            aWandererJ = aWandererJ + ((((RotL64(aIngress, 53U) + aOrbiterC) + RotL64(aOrbiterA, 21U)) + RotL64(aCarry, 29U)) + aPhaseCWandererUpdateSaltD[(((31U - aIndex) + 4U)) & S_SALT1]);
            aWandererD = aWandererD ^ (((RotL64(aPrevious, 43U) + RotL64(aOrbiterH, 36U)) + aOrbiterK) + aPhaseCWandererUpdateSaltE[(((31U - aIndex) + 13U)) & S_SALT1]);
            aWandererF = aWandererF + (((RotL64(aCross, 12U) + aOrbiterF) + RotL64(aOrbiterB, 57U)) + RotL64(aCarry, 43U));
            aWandererA = aWandererA ^ ((RotL64(aScatter, 35U) + RotL64(aOrbiterH, 47U)) + aOrbiterI);
            aWandererE = aWandererE + ((RotL64(aIngress, 19U) + aOrbiterA) + RotL64(aOrbiterD, 43U));
            aWandererI = aWandererI ^ ((RotL64(aPrevious, 39U) + aOrbiterD) + RotL64(aOrbiterG, 3U));
            //
            aCarry = aCarry + (aWandererF ^ RotL64(aWandererH, 10U));
            aCarry = aCarry + (aWandererE ^ RotL64(aWandererJ, 53U));
            aCarry = aCarry + (RotL64(aWandererB, 19U) ^ aWandererI);
            aCarry = aCarry + (RotL64(aWandererD, 57U) ^ aWandererK);
            aCarry = aCarry + RotL64(aWandererA, 23U);
            aCarry = aCarry + RotL64(aIngress, 37U);
            aCarry = TwistMix64::DiffuseB(aCarry);
            //
            aExpandLaneA[aIndex] = aIngress;
        }
    
        // twist_loop_a loop 10
        // ingress from: aExpandLaneA, aKeyRowReadA, aFireLaneD, aFireLaneB
        // ingress directions: aExpandLaneA forward forced, aKeyRowReadA forward forced, aFireLaneD forward forced, aFireLaneB forward/backward random
        // cross from: aKeyRowReadB, mSource, aFireLaneC, aInvestLaneB
        // cross directions: aKeyRowReadB backward forced, mSource backward forced, aFireLaneC backward forced, aInvestLaneB backward/forward random
        // write to: aExpandLaneB
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aExpandLaneA[((aIndex + 26456U)) & S_BLOCK1], 39U) ^ RotL64(aKeyRowReadA[((aIndex + 25649U)) & W_KEY1], 6U));
            aIngress ^= (RotL64(aFireLaneD[((aIndex + 26388U)) & S_BLOCK1], 57U) ^ RotL64(aFireLaneB[((S_BLOCK1 - aIndex + 25839U)) & S_BLOCK1], 19U));
            aIngress = TwistMix64::DiffuseB(aIngress);
            //
            aCross = (RotL64(aKeyRowReadB[(((2047U - aIndex) + 24880U)) & W_KEY1], 11U) ^ RotL64(mSource[((S_BLOCK1 - aIndex + 27230U)) & S_BLOCK1], 21U));
            aCross ^= (RotL64(aFireLaneC[((S_BLOCK1 - aIndex + 25466U)) & S_BLOCK1], 58U) ^ RotL64(aInvestLaneB[((S_BLOCK1 - aIndex + 25260U)) & S_BLOCK1], 37U));
            aCross = TwistMix64::DiffuseB(aCross);
            //
            aScatter = (RotL64(aPrevious, 39U) + RotL64(aCross, 53U)) ^ (RotL64(aCarry, 27U) ^ RotL64(aIngress, 10U));
            aScatter = TwistMix64::DiffuseB(aScatter);
            //
            aOrbiterD = ((aWandererD + RotL64(aScatter, 35U)) + RotL64(aCarry, 3U)) + 13854738573712660276U;
            aOrbiterI = ((aWandererA + RotL64(aIngress, 57U)) + RotL64(aCarry, 35U)) + 16835460633412286294U;
            aOrbiterB = (aWandererI + RotL64(aPrevious, 18U)) + 6785859293758091931U;
            aOrbiterF = (aWandererE + RotL64(aCross, 11U)) + 126317283127992659U;
            aOrbiterG = ((aWandererB + RotL64(aPrevious, 29U)) + 7568963536291415413U) + aPhaseDOrbiterAssignSaltE[((aIndex + 17U)) & S_SALT1];
            aOrbiterA = (((aWandererG + RotL64(aCross, 23U)) + RotL64(aCarry, 19U)) + 12294016745653004819U) + aPhaseDOrbiterAssignSaltA[(((31U - aIndex) + 18U)) & S_SALT1];
            aOrbiterK = (aWandererF + RotL64(aIngress, 53U)) + 18269588932920281147U;
            aOrbiterH = (aWandererC + RotL64(aScatter, 44U)) + 5872406424994751026U;
            aOrbiterC = (aWandererH + RotL64(aPrevious, 39U)) + 7764434758831474129U;
            //
            aOrbiterD = (aOrbiterD + aOrbiterI) + 4804168969415573371U;
            aOrbiterB = (aOrbiterB ^ aOrbiterD) ^ 959601763507651280U;
            aOrbiterB = RotL64((aOrbiterB * 4647396592804833217U), 11U);
            //
            aOrbiterF = (aOrbiterF + aOrbiterG) + 9257644462479293048U;
            aOrbiterA = (aOrbiterA ^ aOrbiterF) ^ 14332699366894494579U;
            aOrbiterA = RotL64((aOrbiterA * 8829304078930625541U), 47U);
            //
            aOrbiterI = ((aOrbiterI + aOrbiterK) + 10487012596470786004U) + aPhaseDOrbiterUpdateSaltF[(((31U - aIndex) + 9U)) & S_SALT1];
            aOrbiterF = (aOrbiterF ^ aOrbiterI) ^ 612729229562321440U;
            aOrbiterF = RotL64((aOrbiterF * 11380387280507726003U), 29U);
            //
            aOrbiterH = ((aOrbiterH + aOrbiterA) + 7845523921295625315U) + aPhaseDOrbiterUpdateSaltC[(((31U - aIndex) + 22U)) & S_SALT1];
            aOrbiterD = (aOrbiterD ^ aOrbiterH) ^ 12742115479740024747U;
            aOrbiterD = RotL64((aOrbiterD * 15578543510683986421U), 53U);
            //
            aOrbiterB = (aOrbiterB + aOrbiterF) + 10294667720904610944U;
            aOrbiterH = (aOrbiterH ^ aOrbiterB) ^ 14369711143154904567U;
            aOrbiterH = RotL64((aOrbiterH * 13753005602288309379U), 5U);
            //
            aOrbiterA = ((aOrbiterA + aOrbiterC) + 10918344717497681894U) + aPhaseDOrbiterUpdateSaltE[(((31U - aIndex) + 27U)) & S_SALT1];
            aOrbiterI = (aOrbiterI ^ aOrbiterA) ^ 18136794828308636957U;
            aOrbiterI = RotL64((aOrbiterI * 17899418637978002409U), 19U);
            //
            aOrbiterG = (aOrbiterG + aOrbiterH) + 14378638206724886404U;
            aOrbiterC = ((aOrbiterC ^ aOrbiterG) ^ 7077588188450008059U) ^ aPhaseDOrbiterUpdateSaltD[((aIndex + 7U)) & S_SALT1];
            aOrbiterC = RotL64((aOrbiterC * 485375960462924335U), 43U);
            //
            aOrbiterK = (aOrbiterK + aOrbiterB) + 8941870012851971932U;
            aOrbiterG = (aOrbiterG ^ aOrbiterK) ^ 15242087859620352399U;
            aOrbiterG = RotL64((aOrbiterG * 4963002810455992839U), 39U);
            //
            aOrbiterC = (aOrbiterC + aOrbiterD) + 10395280254030875387U;
            aOrbiterK = (aOrbiterK ^ aOrbiterC) ^ 6826595516076975980U;
            aOrbiterK = RotL64((aOrbiterK * 6198886240333178001U), 57U);
            //
            aIngress = RotL64(aOrbiterB, 35U) ^ aOrbiterG;
            aIngress = aIngress + (aOrbiterK ^ RotL64(aOrbiterC, 51U));
            aIngress = aIngress + (aOrbiterA ^ RotL64(aOrbiterD, 54U));
            aIngress = aIngress + (RotL64(aOrbiterI, 23U) ^ aOrbiterH);
            aIngress = aIngress + RotL64(aOrbiterF, 41U);
            aIngress = TwistMix64::DiffuseB((aIngress + aScatter));
            //
            aWandererC = aWandererC + ((RotL64(aScatter, 57U) + aOrbiterC) + RotL64(aOrbiterH, 60U));
            aWandererA = aWandererA ^ ((RotL64(aCross, 23U) + aOrbiterH) + RotL64(aOrbiterA, 35U));
            aWandererD = aWandererD + ((((RotL64(aIngress, 37U) + aOrbiterD) + RotL64(aOrbiterI, 43U)) + RotL64(aCarry, 53U)) + aPhaseDWandererUpdateSaltD[(((31U - aIndex) + 12U)) & S_SALT1]);
            aWandererE = aWandererE ^ ((RotL64(aPrevious, 41U) + aOrbiterK) + RotL64(aOrbiterF, 53U));
            aWandererF = aWandererF + ((RotL64(aScatter, 30U) + aOrbiterG) + RotL64(aOrbiterH, 13U));
            aWandererG = aWandererG ^ ((RotL64(aIngress, 19U) + aOrbiterI) + RotL64(aOrbiterF, 29U));
            aWandererB = aWandererB + (((RotL64(aPrevious, 47U) + RotL64(aOrbiterC, 39U)) + aOrbiterD) + RotL64(aCarry, 11U));
            aWandererH = aWandererH ^ ((RotL64(aCross, 53U) + aOrbiterG) + RotL64(aOrbiterB, 3U));
            aWandererI = aWandererI + (((RotL64(aIngress, 6U) + aOrbiterF) + RotL64(aOrbiterG, 22U)) + aPhaseDWandererUpdateSaltF[(((31U - aIndex) + 21U)) & S_SALT1]);
            //
            aCarry = aCarry + (aWandererF ^ RotL64(aWandererB, 39U));
            aCarry = aCarry + (aWandererI ^ RotL64(aWandererA, 53U));
            aCarry = aCarry + (RotL64(aWandererE, 24U) ^ aWandererH);
            aCarry = aCarry + (RotL64(aWandererD, 57U) ^ aWandererC);
            aCarry = aCarry + RotL64(aWandererG, 19U);
            aCarry = aCarry + RotL64(aIngress, 35U);
            aCarry = TwistMix64::DiffuseB(aCarry);
            //
            aExpandLaneB[S_BLOCK1 - aIndex] = aIngress;
        }
    
        // twist_loop_a loop 11
        // ingress from: aExpandLaneB, aFireLaneD, aKeyRowReadB, aFireLaneC
        // ingress directions: aExpandLaneB forward forced, aFireLaneD forward forced, aKeyRowReadB forward forced, aFireLaneC forward/backward random
        // cross from: aKeyRowReadA, mSource, aExpandLaneA, aFireLaneB
        // cross directions: aKeyRowReadA backward forced, mSource backward forced, aExpandLaneA backward forced, aFireLaneB backward/forward random
        // write to: aExpandLaneC
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aExpandLaneB[((aIndex + 27479U)) & S_BLOCK1], 27U) ^ RotL64(aFireLaneD[((aIndex + 29742U)) & S_BLOCK1], 50U));
            aIngress ^= (RotL64(aKeyRowReadB[((aIndex + 27349U)) & W_KEY1], 5U) ^ RotL64(aFireLaneC[((S_BLOCK1 - aIndex + 29076U)) & S_BLOCK1], 41U));
            aIngress = TwistMix64::DiffuseC(aIngress);
            //
            aCross = (RotL64(aKeyRowReadA[(((2047U - aIndex) + 29058U)) & W_KEY1], 3U) ^ RotL64(mSource[((S_BLOCK1 - aIndex + 28309U)) & S_BLOCK1], 13U));
            aCross ^= (RotL64(aExpandLaneA[((S_BLOCK1 - aIndex + 29425U)) & S_BLOCK1], 37U) ^ RotL64(aFireLaneB[((aIndex + 27934U)) & S_BLOCK1], 58U));
            aCross = TwistMix64::DiffuseC(aCross);
            //
            aScatter = (RotL64(aIngress, 3U) + RotL64(aCross, 51U)) ^ (RotL64(aCarry, 37U) + RotL64(aPrevious, 24U));
            aScatter = TwistMix64::DiffuseA(aScatter);
            //
            aOrbiterI = (aWandererF + RotL64(aIngress, 18U)) + 13583136155674166402U;
            aOrbiterF = ((aWandererG + RotL64(aScatter, 51U)) + 12830472187484919497U) + aPhaseDOrbiterAssignSaltB[((aIndex + 28U)) & S_SALT1];
            aOrbiterB = (aWandererK + RotL64(aCross, 27U)) + 18081197909484522509U;
            aOrbiterA = ((aWandererD + RotL64(aPrevious, 47U)) + RotL64(aCarry, 53U)) + 8680634051297891550U;
            aOrbiterJ = (((aWandererA + RotL64(aIngress, 57U)) + RotL64(aCarry, 13U)) + 13939998767458656823U) + aPhaseDOrbiterAssignSaltE[((aIndex + 4U)) & S_SALT1];
            aOrbiterK = (aWandererE + RotL64(aPrevious, 23U)) + 1795730579103692594U;
            aOrbiterC = ((aWandererI + RotL64(aCross, 41U)) + RotL64(aCarry, 39U)) + 17369751719734069999U;
            aOrbiterD = (aWandererC + RotL64(aScatter, 10U)) + 224769585901248068U;
            aOrbiterE = (aWandererJ + RotL64(aCross, 3U)) + 4133547085925268180U;
            //
            aOrbiterI = ((aOrbiterI + aOrbiterF) + 7022512056309567391U) + aPhaseDOrbiterUpdateSaltD[(((31U - aIndex) + 17U)) & S_SALT1];
            aOrbiterB = (aOrbiterB ^ aOrbiterI) ^ 10319484359046945495U;
            aOrbiterB = RotL64((aOrbiterB * 3400140531307001933U), 57U);
            //
            aOrbiterA = (aOrbiterA + aOrbiterI) + 10483878349412282069U;
            aOrbiterJ = (aOrbiterJ ^ aOrbiterA) ^ 6481381149199985736U;
            aOrbiterJ = RotL64((aOrbiterJ * 9701719367082506253U), 53U);
            //
            aOrbiterJ = (aOrbiterJ + aOrbiterB) + 13721077228796934509U;
            aOrbiterK = (aOrbiterK ^ aOrbiterJ) ^ 9704818014314175007U;
            aOrbiterK = RotL64((aOrbiterK * 760445624027740287U), 39U);
            //
            aOrbiterK = (aOrbiterK + aOrbiterC) + 6253040047758584339U;
            aOrbiterF = ((aOrbiterF ^ aOrbiterK) ^ 16890211690273641226U) ^ aPhaseDOrbiterUpdateSaltF[((aIndex + 29U)) & S_SALT1];
            aOrbiterF = RotL64((aOrbiterF * 5622534399866057841U), 19U);
            //
            aOrbiterC = (aOrbiterC + aOrbiterD) + 6216227831265032436U;
            aOrbiterA = ((aOrbiterA ^ aOrbiterC) ^ 2023609047004658739U) ^ aPhaseDOrbiterUpdateSaltE[(((31U - aIndex) + 10U)) & S_SALT1];
            aOrbiterA = RotL64((aOrbiterA * 3252332895698310147U), 47U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterK) + 9201669637050388263U;
            aOrbiterI = (aOrbiterI ^ aOrbiterD) ^ 5106927540934338576U;
            aOrbiterI = RotL64((aOrbiterI * 6368134569042291431U), 13U);
            //
            aOrbiterF = (aOrbiterF + aOrbiterA) + 10080368957861445998U;
            aOrbiterE = (aOrbiterE ^ aOrbiterF) ^ 10784789383436485808U;
            aOrbiterE = RotL64((aOrbiterE * 3794918350254445939U), 23U);
            //
            aOrbiterB = (aOrbiterB + aOrbiterE) + 15426339824951793026U;
            aOrbiterC = (aOrbiterC ^ aOrbiterB) ^ 17637144549368340331U;
            aOrbiterC = RotL64((aOrbiterC * 10971293914614704441U), 43U);
            //
            aOrbiterE = (aOrbiterE + aOrbiterJ) + 9941300382181962134U;
            aOrbiterD = ((aOrbiterD ^ aOrbiterE) ^ 8118046374121322097U) ^ aPhaseDOrbiterUpdateSaltA[(((31U - aIndex) + 23U)) & S_SALT1];
            aOrbiterD = RotL64((aOrbiterD * 8481945819050983127U), 27U);
            //
            aIngress = RotL64(aOrbiterK, 47U) ^ aOrbiterA;
            aIngress = aIngress + (RotL64(aOrbiterC, 52U) ^ aOrbiterF);
            aIngress = aIngress + (aOrbiterD ^ RotL64(aOrbiterI, 37U));
            aIngress = aIngress + (RotL64(aOrbiterE, 11U) ^ aOrbiterB);
            aIngress = aIngress + RotL64(aOrbiterJ, 23U);
            aIngress = TwistMix64::DiffuseA((aIngress + aScatter));
            //
            aWandererA = aWandererA ^ ((RotL64(aPrevious, 27U) + aOrbiterF) + RotL64(aOrbiterD, 27U));
            aWandererG = aWandererG + (((RotL64(aScatter, 11U) + aOrbiterC) + RotL64(aOrbiterA, 34U)) + aPhaseDWandererUpdateSaltD[(((31U - aIndex) + 19U)) & S_SALT1]);
            aWandererE = aWandererE ^ ((RotL64(aIngress, 34U) + RotL64(aOrbiterK, 21U)) + aOrbiterF);
            aWandererI = aWandererI + ((RotL64(aCross, 5U) + RotL64(aOrbiterB, 5U)) + aOrbiterE);
            aWandererC = aWandererC ^ ((RotL64(aPrevious, 19U) + RotL64(aOrbiterC, 11U)) + aOrbiterK);
            aWandererF = aWandererF + (((RotL64(aIngress, 23U) + aOrbiterI) + RotL64(aOrbiterD, 43U)) + RotL64(aCarry, 51U));
            aWandererK = aWandererK ^ ((RotL64(aScatter, 43U) + aOrbiterF) + RotL64(aOrbiterE, 53U));
            aWandererD = aWandererD + (((RotL64(aCross, 47U) + RotL64(aOrbiterA, 48U)) + aOrbiterF) + RotL64(aCarry, 29U));
            aWandererJ = aWandererJ ^ (((RotL64(aPrevious, 38U) + aOrbiterJ) + RotL64(aOrbiterD, 39U)) + aPhaseDWandererUpdateSaltB[(((31U - aIndex) + 7U)) & S_SALT1]);
            //
            aCarry = aCarry + (RotL64(aWandererI, 47U) ^ aWandererC);
            aCarry = aCarry + (aWandererD ^ RotL64(aWandererF, 57U));
            aCarry = aCarry + (RotL64(aWandererA, 23U) ^ aWandererJ);
            aCarry = aCarry + (aWandererE ^ RotL64(aWandererG, 5U));
            aCarry = aCarry + RotL64(aWandererK, 36U);
            aCarry = aCarry + RotL64(aIngress, 11U);
            aCarry = TwistMix64::DiffuseA(aCarry);
            //
            aExpandLaneC[aIndex] = aIngress;
        }
    
        // twist_loop_a loop 12
        // ingress from: aExpandLaneC, aKeyRowReadA
        // ingress directions: aExpandLaneC forward forced, aKeyRowReadA forward/backward random
        // cross from: aFireLaneD, aExpandLaneA, aExpandLaneB, aKeyRowReadB
        // cross directions: aFireLaneD backward forced, aExpandLaneA backward forced, aExpandLaneB backward forced, aKeyRowReadB backward/forward random
        // write to: aExpandLaneD
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = RotL64(aExpandLaneC[((aIndex + 31208U)) & S_BLOCK1], 18U) ^ RotL64(aKeyRowReadA[((aIndex + 32060U)) & W_KEY1], 47U);
            aIngress = TwistMix64::DiffuseB(aIngress);
            //
            aCross = (RotL64(aFireLaneD[((S_BLOCK1 - aIndex + 32475U)) & S_BLOCK1], 58U) ^ RotL64(aExpandLaneA[((S_BLOCK1 - aIndex + 31875U)) & S_BLOCK1], 5U));
            aCross ^= (RotL64(aExpandLaneB[((S_BLOCK1 - aIndex + 31929U)) & S_BLOCK1], 13U) ^ RotL64(aKeyRowReadB[(((2047U - aIndex) + 31465U)) & W_KEY1], 21U));
            aCross = TwistMix64::DiffuseA(aCross);
            //
            aScatter = (RotL64(aCarry, 11U) + RotL64(aIngress, 26U)) + (RotL64(aPrevious, 43U) ^ RotL64(aCross, 57U));
            aScatter = TwistMix64::DiffuseA(aScatter);
            //
            aOrbiterF = (aWandererC + RotL64(aScatter, 43U)) + 2786079456995203065U;
            aOrbiterK = (aWandererJ + RotL64(aIngress, 13U)) + 7237256119153857253U;
            aOrbiterB = ((aWandererI + RotL64(aCross, 39U)) + RotL64(aCarry, 11U)) + 9310834010563647604U;
            aOrbiterC = ((aWandererF + RotL64(aPrevious, 35U)) + RotL64(aCarry, 57U)) + 17361734905706517877U;
            aOrbiterE = (((aWandererA + RotL64(aIngress, 18U)) + RotL64(aCarry, 27U)) + 15837111231884647451U) + aPhaseDOrbiterAssignSaltD[(((31U - aIndex) + 7U)) & S_SALT1];
            aOrbiterJ = (aWandererG + RotL64(aPrevious, 57U)) + 18065431964418026445U;
            aOrbiterG = (aWandererE + RotL64(aScatter, 23U)) + 3029123922999952652U;
            aOrbiterI = (aWandererH + RotL64(aCross, 51U)) + 5166926595573507837U;
            aOrbiterD = ((aWandererK + RotL64(aScatter, 4U)) + 1918425684273807598U) + aPhaseDOrbiterAssignSaltB[(((31U - aIndex) + 17U)) & S_SALT1];
            //
            aOrbiterF = (aOrbiterF + aOrbiterK) + 4724551751012661440U;
            aOrbiterB = ((aOrbiterB ^ aOrbiterF) ^ 1818014487579644390U) ^ aPhaseDOrbiterUpdateSaltC[(((31U - aIndex) + 13U)) & S_SALT1];
            aOrbiterB = RotL64((aOrbiterB * 14904092108647864911U), 43U);
            //
            aOrbiterK = ((aOrbiterK + aOrbiterC) + 6670090372241084216U) + aPhaseDOrbiterUpdateSaltD[(((31U - aIndex) + 20U)) & S_SALT1];
            aOrbiterE = (aOrbiterE ^ aOrbiterK) ^ 8485757110007268693U;
            aOrbiterE = RotL64((aOrbiterE * 11876760095108618363U), 35U);
            //
            aOrbiterB = (aOrbiterB + aOrbiterE) + 4928130251509514742U;
            aOrbiterJ = ((aOrbiterJ ^ aOrbiterB) ^ 2528788422725346792U) ^ aPhaseDOrbiterUpdateSaltF[(((31U - aIndex) + 21U)) & S_SALT1];
            aOrbiterJ = RotL64((aOrbiterJ * 1855982047967756661U), 5U);
            //
            aOrbiterC = (aOrbiterC + aOrbiterF) + 2860387120895147503U;
            aOrbiterG = (aOrbiterG ^ aOrbiterC) ^ 12927802338151379368U;
            aOrbiterG = RotL64((aOrbiterG * 8876144125458603029U), 29U);
            //
            aOrbiterI = (aOrbiterI + aOrbiterJ) + 18029699867733207083U;
            aOrbiterF = (aOrbiterF ^ aOrbiterI) ^ 13361836994951253312U;
            aOrbiterF = RotL64((aOrbiterF * 5349767426256597073U), 47U);
            //
            aOrbiterJ = (aOrbiterJ + aOrbiterD) + 11957294454794128079U;
            aOrbiterK = (aOrbiterK ^ aOrbiterJ) ^ 3755417922063414648U;
            aOrbiterK = RotL64((aOrbiterK * 13896364063651241401U), 39U);
            //
            aOrbiterD = ((aOrbiterD + aOrbiterI) + 18001157153447913032U) + aPhaseDOrbiterUpdateSaltE[((aIndex + 5U)) & S_SALT1];
            aOrbiterC = (aOrbiterC ^ aOrbiterD) ^ 16214145724690286854U;
            aOrbiterC = RotL64((aOrbiterC * 5874139687703360515U), 11U);
            //
            aOrbiterE = (aOrbiterE + aOrbiterG) + 3860958772090975562U;
            aOrbiterD = (aOrbiterD ^ aOrbiterE) ^ 12395621524459640173U;
            aOrbiterD = RotL64((aOrbiterD * 722817135977510161U), 53U);
            //
            aOrbiterG = (aOrbiterG + aOrbiterB) + 3402035664910754484U;
            aOrbiterI = (aOrbiterI ^ aOrbiterG) ^ 2139099117325745602U;
            aOrbiterI = RotL64((aOrbiterI * 14008983756425796029U), 57U);
            //
            aIngress = RotL64(aOrbiterC, 3U) ^ aOrbiterF;
            aIngress = aIngress + (aOrbiterG ^ RotL64(aOrbiterE, 10U));
            aIngress = aIngress + (RotL64(aOrbiterI, 19U) ^ aOrbiterJ);
            aIngress = aIngress + (RotL64(aOrbiterB, 23U) ^ aOrbiterD);
            aIngress = aIngress + RotL64(aOrbiterK, 13U);
            aIngress = TwistMix64::DiffuseA((aIngress + aScatter));
            //
            aWandererC = aWandererC + ((RotL64(aCross, 4U) + aOrbiterK) + RotL64(aOrbiterJ, 21U));
            aWandererJ = aWandererJ ^ ((RotL64(aScatter, 37U) + RotL64(aOrbiterJ, 30U)) + aOrbiterC);
            aWandererK = aWandererK + (((RotL64(aIngress, 41U) + RotL64(aOrbiterC, 41U)) + aOrbiterF) + RotL64(aCarry, 53U));
            aWandererA = aWandererA ^ (((RotL64(aPrevious, 51U) + RotL64(aOrbiterK, 11U)) + aOrbiterE) + aPhaseDWandererUpdateSaltA[((aIndex + 25U)) & S_SALT1]);
            aWandererE = aWandererE + ((RotL64(aScatter, 57U) + aOrbiterK) + RotL64(aOrbiterC, 37U));
            aWandererI = aWandererI ^ ((RotL64(aCross, 23U) + RotL64(aOrbiterI, 57U)) + aOrbiterJ);
            aWandererF = aWandererF + (((RotL64(aPrevious, 11U) + RotL64(aOrbiterG, 26U)) + aOrbiterI) + aPhaseDWandererUpdateSaltC[((aIndex + 23U)) & S_SALT1]);
            aWandererH = aWandererH ^ ((RotL64(aIngress, 46U) + RotL64(aOrbiterI, 5U)) + aOrbiterB);
            aWandererG = aWandererG + (((RotL64(aScatter, 19U) + aOrbiterD) + RotL64(aOrbiterI, 53U)) + RotL64(aCarry, 23U));
            //
            aCarry = aCarry + (aWandererA ^ RotL64(aWandererE, 29U));
            aCarry = aCarry + (RotL64(aWandererK, 35U) ^ aWandererC);
            aCarry = aCarry + (aWandererG ^ RotL64(aWandererF, 6U));
            aCarry = aCarry + (RotL64(aWandererH, 41U) ^ aWandererI);
            aCarry = aCarry + RotL64(aWandererJ, 11U);
            aCarry = aCarry + RotL64(aIngress, 51U);
            aCarry = TwistMix64::DiffuseC(aCarry);
            //
            aExpandLaneD[S_BLOCK1 - aIndex] = aIngress;
        }
    }
    // GTwistRunTwist_A twist_loop_a (end)
    *pPrevious = aPrevious;
    *pIngress = aIngress;
    *pCarry = aCarry;
    *pWandererA = aWandererA;
    *pWandererB = aWandererB;
    *pWandererC = aWandererC;
    *pWandererD = aWandererD;
    *pWandererE = aWandererE;
    *pWandererF = aWandererF;
    *pWandererG = aWandererG;
    *pWandererH = aWandererH;
    *pWandererI = aWandererI;
    *pWandererJ = aWandererJ;
    *pWandererK = aWandererK;
}

void TwistExpander_Exercea_Arx::Twist_B(TwistWorkSpace *pWorkSpace,
                     std::uint8_t *pSource,
                     std::uint64_t *pPrevious,
                     std::uint64_t *pIngress,
                     std::uint64_t *pCarry,
                     std::uint64_t *pWandererA,
                     std::uint64_t *pWandererB,
                     std::uint64_t *pWandererC,
                     std::uint64_t *pWandererD,
                     std::uint64_t *pWandererE,
                     std::uint64_t *pWandererF,
                     std::uint64_t *pWandererG,
                     std::uint64_t *pWandererH,
                     std::uint64_t *pWandererI,
                     std::uint64_t *pWandererJ,
                     std::uint64_t *pWandererK) {
    [[maybe_unused]] std::uint8_t *aExpandLaneA = pWorkSpace->mExpansionLaneA;
    [[maybe_unused]] std::uint8_t *aExpandLaneB = pWorkSpace->mExpansionLaneB;
    [[maybe_unused]] std::uint8_t *aExpandLaneC = pWorkSpace->mExpansionLaneC;
    [[maybe_unused]] std::uint8_t *aExpandLaneD = pWorkSpace->mExpansionLaneD;
    [[maybe_unused]] std::uint8_t *aOperationLaneA = pWorkSpace->mOperationLaneA;
    [[maybe_unused]] std::uint8_t *aOperationLaneB = pWorkSpace->mOperationLaneB;
    [[maybe_unused]] std::uint8_t *aOperationLaneC = pWorkSpace->mOperationLaneC;
    [[maybe_unused]] std::uint8_t *aOperationLaneD = pWorkSpace->mOperationLaneD;
    [[maybe_unused]] std::uint8_t *aFireLaneA = pWorkSpace->mFireLaneA;
    [[maybe_unused]] std::uint8_t *aFireLaneB = pWorkSpace->mFireLaneB;
    [[maybe_unused]] std::uint8_t *aFireLaneC = pWorkSpace->mFireLaneC;
    [[maybe_unused]] std::uint8_t *aFireLaneD = pWorkSpace->mFireLaneD;
    [[maybe_unused]] std::uint8_t *aInvestLaneC = pWorkSpace->mInvestLaneC;
    [[maybe_unused]] std::uint8_t *aInvestLaneD = pWorkSpace->mInvestLaneD;
    [[maybe_unused]] std::uint64_t *aPhaseEOrbiterAssignSaltA = pWorkSpace->mDomainBundle.mPhaseESalts.mOrbiterAssign.mSaltA;
    [[maybe_unused]] std::uint64_t *aPhaseEOrbiterAssignSaltB = pWorkSpace->mDomainBundle.mPhaseESalts.mOrbiterAssign.mSaltB;
    [[maybe_unused]] std::uint64_t *aPhaseEOrbiterAssignSaltC = pWorkSpace->mDomainBundle.mPhaseESalts.mOrbiterAssign.mSaltC;
    [[maybe_unused]] std::uint64_t *aPhaseEOrbiterAssignSaltD = pWorkSpace->mDomainBundle.mPhaseESalts.mOrbiterAssign.mSaltD;
    [[maybe_unused]] std::uint64_t *aPhaseEOrbiterAssignSaltE = pWorkSpace->mDomainBundle.mPhaseESalts.mOrbiterAssign.mSaltE;
    [[maybe_unused]] std::uint64_t *aPhaseEOrbiterAssignSaltF = pWorkSpace->mDomainBundle.mPhaseESalts.mOrbiterAssign.mSaltF;
    [[maybe_unused]] std::uint64_t *aPhaseEOrbiterUpdateSaltA = pWorkSpace->mDomainBundle.mPhaseESalts.mOrbiterUpdate.mSaltA;
    [[maybe_unused]] std::uint64_t *aPhaseEOrbiterUpdateSaltB = pWorkSpace->mDomainBundle.mPhaseESalts.mOrbiterUpdate.mSaltB;
    [[maybe_unused]] std::uint64_t *aPhaseEOrbiterUpdateSaltC = pWorkSpace->mDomainBundle.mPhaseESalts.mOrbiterUpdate.mSaltC;
    [[maybe_unused]] std::uint64_t *aPhaseEOrbiterUpdateSaltD = pWorkSpace->mDomainBundle.mPhaseESalts.mOrbiterUpdate.mSaltD;
    [[maybe_unused]] std::uint64_t *aPhaseEOrbiterUpdateSaltE = pWorkSpace->mDomainBundle.mPhaseESalts.mOrbiterUpdate.mSaltE;
    [[maybe_unused]] std::uint64_t *aPhaseEOrbiterUpdateSaltF = pWorkSpace->mDomainBundle.mPhaseESalts.mOrbiterUpdate.mSaltF;
    [[maybe_unused]] std::uint64_t *aPhaseEWandererUpdateSaltA = pWorkSpace->mDomainBundle.mPhaseESalts.mWandererUpdate.mSaltA;
    [[maybe_unused]] std::uint64_t *aPhaseEWandererUpdateSaltB = pWorkSpace->mDomainBundle.mPhaseESalts.mWandererUpdate.mSaltB;
    [[maybe_unused]] std::uint64_t *aPhaseEWandererUpdateSaltC = pWorkSpace->mDomainBundle.mPhaseESalts.mWandererUpdate.mSaltC;
    [[maybe_unused]] std::uint64_t *aPhaseEWandererUpdateSaltD = pWorkSpace->mDomainBundle.mPhaseESalts.mWandererUpdate.mSaltD;
    [[maybe_unused]] std::uint64_t *aPhaseEWandererUpdateSaltE = pWorkSpace->mDomainBundle.mPhaseESalts.mWandererUpdate.mSaltE;
    [[maybe_unused]] std::uint64_t *aPhaseEWandererUpdateSaltF = pWorkSpace->mDomainBundle.mPhaseESalts.mWandererUpdate.mSaltF;
    std::uint64_t aCross = 0; std::uint64_t aScatter = 0;

    std::uint64_t aOrbiterA = 0; std::uint64_t aOrbiterB = 0; std::uint64_t aOrbiterC = 0; std::uint64_t aOrbiterD = 0;
    std::uint64_t aOrbiterE = 0; std::uint64_t aOrbiterF = 0; std::uint64_t aOrbiterG = 0; std::uint64_t aOrbiterH = 0;
    std::uint64_t aOrbiterI = 0; std::uint64_t aOrbiterJ = 0; std::uint64_t aOrbiterK = 0;

    // [twist arx]
    [[maybe_unused]] std::uint8_t *mSource = pSource;
    std::uint64_t aPrevious = *pPrevious;
    std::uint64_t aIngress = *pIngress;
    std::uint64_t aCarry = *pCarry;
    std::uint64_t aWandererA = *pWandererA;
    std::uint64_t aWandererB = *pWandererB;
    std::uint64_t aWandererC = *pWandererC;
    std::uint64_t aWandererD = *pWandererD;
    std::uint64_t aWandererE = *pWandererE;
    std::uint64_t aWandererF = *pWandererF;
    std::uint64_t aWandererG = *pWandererG;
    std::uint64_t aWandererH = *pWandererH;
    std::uint64_t aWandererI = *pWandererI;
    std::uint64_t aWandererJ = *pWandererJ;
    std::uint64_t aWandererK = *pWandererK;
    // GTwistRunTwist_B twist_loop_b (start)
    {
        // GTwistRunTwist_B twist_loop_b lane group
        // read from: aExpandLaneA, aExpandLaneB, aFireLaneC, aExpandLaneC, aExpandLaneD, aInvestLaneC, aFireLaneA, aInvestLaneD, aFireLaneD, aOperationLaneA, aFireLaneB, aOperationLaneB, aOperationLaneC
        // write to: aInvestLaneC, aInvestLaneD, aOperationLaneA, aOperationLaneB, aOperationLaneC, aOperationLaneD
    
        // twist_loop_b loop 1
        // ingress from: aExpandLaneA, aExpandLaneB, aFireLaneC
        // ingress directions: aExpandLaneA forward forced, aExpandLaneB forward forced, aFireLaneC forward/backward random
        // cross from: aExpandLaneC, aExpandLaneD
        // cross directions: aExpandLaneC backward forced, aExpandLaneD backward/forward random
        // write to: aInvestLaneC
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aExpandLaneA[((aIndex + 2661U)) & S_BLOCK1], 47U) ^ RotL64(aExpandLaneB[((aIndex + 280U)) & S_BLOCK1], 6U));
            aIngress ^= RotL64(aFireLaneC[((S_BLOCK1 - aIndex + 2480U)) & S_BLOCK1], 27U);
            aIngress = TwistMix64::DiffuseB(aIngress);
            //
            aCross = RotL64(aExpandLaneC[((S_BLOCK1 - aIndex + 3612U)) & S_BLOCK1], 58U) ^ RotL64(aExpandLaneD[((aIndex + 490U)) & S_BLOCK1], 29U);
            aCross = TwistMix64::DiffuseB(aCross);
            //
            aScatter = (RotL64(aCarry, 39U) + RotL64(aPrevious, 27U)) ^ (RotL64(aCross, 11U) ^ RotL64(aIngress, 56U));
            aScatter = TwistMix64::DiffuseB(aScatter);
            //
            aOrbiterK = (aWandererI + RotL64(aPrevious, 3U)) + 6243113109470883144U;
            aOrbiterH = ((aWandererC + RotL64(aIngress, 19U)) + RotL64(aCarry, 41U)) + 3891552123999605832U;
            aOrbiterD = (aWandererJ + RotL64(aCross, 37U)) + 8758797898587019128U;
            aOrbiterB = ((aWandererD + RotL64(aScatter, 11U)) + 1005891374086408851U) + aPhaseEOrbiterAssignSaltA[((aIndex + 15U)) & S_SALT1];
            aOrbiterA = ((aWandererH + RotL64(aCross, 57U)) + RotL64(aCarry, 29U)) + 3713426782180050764U;
            aOrbiterE = (((aWandererB + RotL64(aPrevious, 28U)) + RotL64(aCarry, 57U)) + 18358143862391573534U) + aPhaseEOrbiterAssignSaltE[((aIndex + 21U)) & S_SALT1];
            aOrbiterG = (aWandererF + RotL64(aScatter, 43U)) + 17504394029693712404U;
            //
            aOrbiterK = ((aOrbiterK + aOrbiterH) + 5312729289027417014U) + aPhaseEOrbiterUpdateSaltE[(((31U - aIndex) + 9U)) & S_SALT1];
            aOrbiterD = (aOrbiterD ^ aOrbiterK) ^ 2560873623431186029U;
            aOrbiterD = RotL64((aOrbiterD * 16843728573219210173U), 53U);
            //
            aOrbiterB = (aOrbiterB + aOrbiterA) + 16309322822806704211U;
            aOrbiterH = (aOrbiterH ^ aOrbiterB) ^ 10195513918020652600U;
            aOrbiterH = RotL64((aOrbiterH * 14569219741824123715U), 5U);
            //
            aOrbiterE = ((aOrbiterE + aOrbiterB) + 2552116263258744287U) + aPhaseEOrbiterUpdateSaltC[((aIndex + 18U)) & S_SALT1];
            aOrbiterK = ((aOrbiterK ^ aOrbiterE) ^ 7732784879810980089U) ^ aPhaseEOrbiterUpdateSaltD[(((31U - aIndex) + 12U)) & S_SALT1];
            aOrbiterK = RotL64((aOrbiterK * 15041929399477790999U), 37U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterG) + 16499127570665381507U;
            aOrbiterB = (aOrbiterB ^ aOrbiterD) ^ 10890036715535519036U;
            aOrbiterB = RotL64((aOrbiterB * 9065115450010475187U), 19U);
            //
            aOrbiterA = (aOrbiterA + aOrbiterD) + 16288944603478791554U;
            aOrbiterE = (aOrbiterE ^ aOrbiterA) ^ 14542766121469312846U;
            aOrbiterE = RotL64((aOrbiterE * 8435383464425875209U), 43U);
            //
            aOrbiterH = (aOrbiterH + aOrbiterE) + 5973595239494084696U;
            aOrbiterG = ((aOrbiterG ^ aOrbiterH) ^ 1820492719977197097U) ^ aPhaseEOrbiterUpdateSaltF[(((31U - aIndex) + 25U)) & S_SALT1];
            aOrbiterG = RotL64((aOrbiterG * 16164917159141304405U), 11U);
            //
            aOrbiterG = (aOrbiterG + aOrbiterK) + 10489529555776381736U;
            aOrbiterA = (aOrbiterA ^ aOrbiterG) ^ 6392552206958240484U;
            aOrbiterA = RotL64((aOrbiterA * 11761477994533503307U), 29U);
            //
            aIngress = aOrbiterB ^ RotL64(aOrbiterD, 29U);
            aIngress = aIngress + (RotL64(aOrbiterA, 51U) ^ aOrbiterG);
            aIngress = aIngress + (aOrbiterE ^ RotL64(aOrbiterK, 44U));
            aIngress = aIngress + RotL64(aOrbiterH, 5U);
            aIngress = TwistMix64::DiffuseB((aIngress + aScatter));
            //
            aWandererJ = aWandererJ + ((RotL64(aScatter, 21U) + RotL64(aOrbiterD, 41U)) + aOrbiterB);
            aWandererI = aWandererI ^ (((RotL64(aCross, 58U) + aOrbiterH) + RotL64(aOrbiterK, 54U)) + aPhaseEWandererUpdateSaltD[((aIndex + 28U)) & S_SALT1]);
            aWandererB = aWandererB + (((RotL64(aIngress, 41U) + RotL64(aOrbiterD, 5U)) + aOrbiterA) + RotL64(aCarry, 3U));
            aWandererH = aWandererH ^ ((RotL64(aPrevious, 27U) + RotL64(aOrbiterG, 11U)) + aOrbiterD);
            aWandererC = aWandererC + ((RotL64(aCross, 51U) + RotL64(aOrbiterG, 27U)) + aOrbiterH);
            aWandererF = aWandererF ^ (((RotL64(aScatter, 35U) + aOrbiterH) + RotL64(aOrbiterE, 21U)) + aPhaseEWandererUpdateSaltB[(((31U - aIndex) + 27U)) & S_SALT1]);
            aWandererD = aWandererD + (((RotL64(aPrevious, 13U) + aOrbiterH) + RotL64(aOrbiterD, 35U)) + RotL64(aCarry, 19U));
            //
            aCarry = aCarry + (RotL64(aWandererJ, 6U) ^ aWandererC);
            aCarry = aCarry + (RotL64(aWandererB, 11U) ^ aWandererD);
            aCarry = aCarry + (RotL64(aWandererI, 35U) ^ aWandererF);
            aCarry = aCarry + RotL64(aWandererH, 29U);
            aCarry = aCarry + RotL64(aIngress, 60U);
            aCarry = TwistMix64::DiffuseB(aCarry);
            //
            aInvestLaneC[aIndex] = aIngress;
        }
    
        // twist_loop_b loop 2
        // ingress from: aInvestLaneC, aExpandLaneC, aFireLaneA
        // ingress directions: aInvestLaneC forward forced, aExpandLaneC forward forced, aFireLaneA forward/backward random
        // cross from: aExpandLaneA, aExpandLaneD
        // cross directions: aExpandLaneA backward forced, aExpandLaneD backward/forward random
        // write to: aInvestLaneD
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aInvestLaneC[((aIndex + 8774U)) & S_BLOCK1], 46U) ^ RotL64(aExpandLaneC[((aIndex + 9082U)) & S_BLOCK1], 21U));
            aIngress ^= RotL64(aFireLaneA[((S_BLOCK1 - aIndex + 8517U)) & S_BLOCK1], 3U);
            aIngress = TwistMix64::DiffuseA(aIngress);
            //
            aCross = RotL64(aExpandLaneA[((S_BLOCK1 - aIndex + 9179U)) & S_BLOCK1], 35U) ^ RotL64(aExpandLaneD[((aIndex + 7358U)) & S_BLOCK1], 22U);
            aCross = TwistMix64::DiffuseB(aCross);
            //
            aScatter = (RotL64(aCross, 35U) ^ RotL64(aPrevious, 5U)) + (RotL64(aIngress, 48U) + RotL64(aCarry, 21U));
            aScatter = TwistMix64::DiffuseB(aScatter);
            //
            aOrbiterH = (aWandererA + RotL64(aIngress, 43U)) + 15036852811491820366U;
            aOrbiterF = ((aWandererG + RotL64(aScatter, 5U)) + RotL64(aCarry, 13U)) + 305637140752898475U;
            aOrbiterD = ((aWandererH + RotL64(aCross, 13U)) + RotL64(aCarry, 35U)) + 11948631574496129610U;
            aOrbiterK = (((aWandererJ + RotL64(aPrevious, 60U)) + RotL64(aCarry, 57U)) + 5321623592482991426U) + aPhaseEOrbiterAssignSaltF[(((31U - aIndex) + 3U)) & S_SALT1];
            aOrbiterA = ((aWandererC + RotL64(aIngress, 19U)) + 4075270159062690728U) + aPhaseEOrbiterAssignSaltD[(((31U - aIndex) + 21U)) & S_SALT1];
            aOrbiterE = (aWandererK + RotL64(aCross, 37U)) + 15111580500356908928U;
            aOrbiterG = (aWandererI + RotL64(aPrevious, 51U)) + 7244150695504160363U;
            //
            aOrbiterH = (aOrbiterH + aOrbiterF) + 5131563519577488862U;
            aOrbiterD = (aOrbiterD ^ aOrbiterH) ^ 5881954992088651371U;
            aOrbiterD = RotL64((aOrbiterD * 2424421828597294607U), 3U);
            //
            aOrbiterK = (aOrbiterK + aOrbiterA) + 12780935808751507998U;
            aOrbiterH = ((aOrbiterH ^ aOrbiterK) ^ 12599159643925470226U) ^ aPhaseEOrbiterUpdateSaltF[((aIndex + 6U)) & S_SALT1];
            aOrbiterH = RotL64((aOrbiterH * 17690046932587062701U), 41U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterK) + 9466589929741834066U;
            aOrbiterE = (aOrbiterE ^ aOrbiterD) ^ 6093158735705189789U;
            aOrbiterE = RotL64((aOrbiterE * 7453778295800853653U), 35U);
            //
            aOrbiterA = (aOrbiterA + aOrbiterE) + 17461243886150519249U;
            aOrbiterF = (aOrbiterF ^ aOrbiterA) ^ 15456408913739900718U;
            aOrbiterF = RotL64((aOrbiterF * 16093292401746174671U), 13U);
            //
            aOrbiterF = ((aOrbiterF + aOrbiterG) + 11260643903290392780U) + aPhaseEOrbiterUpdateSaltB[(((31U - aIndex) + 16U)) & S_SALT1];
            aOrbiterK = (aOrbiterK ^ aOrbiterF) ^ 7870342756041882616U;
            aOrbiterK = RotL64((aOrbiterK * 2431528656086173419U), 19U);
            //
            aOrbiterG = (aOrbiterG + aOrbiterD) + 134484990005888936U;
            aOrbiterA = (aOrbiterA ^ aOrbiterG) ^ 10626896209992890407U;
            aOrbiterA = RotL64((aOrbiterA * 12034131076645285597U), 51U);
            //
            aOrbiterE = ((aOrbiterE + aOrbiterH) + 14031164129515132292U) + aPhaseEOrbiterUpdateSaltA[(((31U - aIndex) + 15U)) & S_SALT1];
            aOrbiterG = ((aOrbiterG ^ aOrbiterE) ^ 1771835705730244212U) ^ aPhaseEOrbiterUpdateSaltE[(((31U - aIndex) + 7U)) & S_SALT1];
            aOrbiterG = RotL64((aOrbiterG * 186981668443596623U), 57U);
            //
            aIngress = aOrbiterE ^ RotL64(aOrbiterH, 3U);
            aIngress = aIngress + (aOrbiterD ^ RotL64(aOrbiterF, 41U));
            aIngress = aIngress + (aOrbiterK ^ RotL64(aOrbiterA, 34U));
            aIngress = aIngress + RotL64(aOrbiterG, 51U);
            aIngress = TwistMix64::DiffuseA((aIngress + aScatter));
            //
            aWandererA = aWandererA ^ ((RotL64(aCross, 13U) + RotL64(aOrbiterG, 50U)) + aOrbiterA);
            aWandererG = aWandererG + (((RotL64(aIngress, 19U) + RotL64(aOrbiterG, 3U)) + aOrbiterK) + RotL64(aCarry, 41U));
            aWandererC = aWandererC ^ ((RotL64(aScatter, 53U) + aOrbiterE) + RotL64(aOrbiterD, 35U));
            aWandererJ = aWandererJ + (((RotL64(aPrevious, 39U) + RotL64(aOrbiterH, 29U)) + aOrbiterK) + RotL64(aCarry, 5U));
            aWandererI = aWandererI ^ (((RotL64(aCross, 47U) + RotL64(aOrbiterK, 11U)) + aOrbiterD) + aPhaseEWandererUpdateSaltF[((aIndex + 11U)) & S_SALT1]);
            aWandererH = aWandererH + ((RotL64(aScatter, 3U) + RotL64(aOrbiterF, 19U)) + aOrbiterK);
            aWandererK = aWandererK ^ (((RotL64(aPrevious, 30U) + RotL64(aOrbiterF, 41U)) + aOrbiterA) + aPhaseEWandererUpdateSaltE[(((31U - aIndex) + 13U)) & S_SALT1]);
            //
            aCarry = aCarry + (aWandererK ^ RotL64(aWandererJ, 11U));
            aCarry = aCarry + (aWandererA ^ RotL64(aWandererG, 41U));
            aCarry = aCarry + (RotL64(aWandererI, 60U) ^ aWandererH);
            aCarry = aCarry + RotL64(aWandererC, 29U);
            aCarry = aCarry + RotL64(aIngress, 35U);
            aCarry = TwistMix64::DiffuseB(aCarry);
            //
            aInvestLaneD[S_BLOCK1 - aIndex] = aIngress;
        }
    
        // twist_loop_b loop 3
        // ingress from: aInvestLaneD, aExpandLaneD, aFireLaneD
        // ingress directions: aInvestLaneD forward forced, aExpandLaneD forward forced, aFireLaneD forward/backward random
        // cross from: aInvestLaneC, aExpandLaneB, aExpandLaneA
        // cross directions: aInvestLaneC backward forced, aExpandLaneB backward forced, aExpandLaneA backward/forward random
        // write to: aOperationLaneA
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aInvestLaneD[((aIndex + 12821U)) & S_BLOCK1], 60U) ^ RotL64(aExpandLaneD[((aIndex + 13375U)) & S_BLOCK1], 51U));
            aIngress ^= RotL64(aFireLaneD[((S_BLOCK1 - aIndex + 12424U)) & S_BLOCK1], 41U);
            aIngress = TwistMix64::DiffuseC(aIngress);
            //
            aCross = (RotL64(aInvestLaneC[((S_BLOCK1 - aIndex + 12866U)) & S_BLOCK1], 43U) ^ RotL64(aExpandLaneB[((S_BLOCK1 - aIndex + 11727U)) & S_BLOCK1], 13U));
            aCross ^= RotL64(aExpandLaneA[((aIndex + 11330U)) & S_BLOCK1], 26U);
            aCross = TwistMix64::DiffuseB(aCross);
            //
            aScatter = (RotL64(aIngress, 47U) + RotL64(aCross, 60U)) + (RotL64(aCarry, 35U) ^ RotL64(aPrevious, 13U));
            aScatter = TwistMix64::DiffuseC(aScatter);
            //
            aOrbiterK = (aWandererG + RotL64(aIngress, 53U)) + 17081642665820489793U;
            aOrbiterC = (((aWandererH + RotL64(aPrevious, 35U)) + RotL64(aCarry, 35U)) + 14468854040067229623U) + aPhaseEOrbiterAssignSaltC[(((31U - aIndex) + 8U)) & S_SALT1];
            aOrbiterF = (aWandererF + RotL64(aScatter, 43U)) + 2249450222593057429U;
            aOrbiterB = (((aWandererI + RotL64(aCross, 60U)) + RotL64(aCarry, 23U)) + 14964389079511378664U) + aPhaseEOrbiterAssignSaltB[((aIndex + 25U)) & S_SALT1];
            aOrbiterD = ((aWandererE + RotL64(aScatter, 19U)) + RotL64(aCarry, 53U)) + 17003491054252360650U;
            aOrbiterJ = (aWandererK + RotL64(aPrevious, 5U)) + 12710882240582032588U;
            aOrbiterH = (aWandererD + RotL64(aCross, 27U)) + 9887078182156755359U;
            //
            aOrbiterK = (aOrbiterK + aOrbiterC) + 7665284531810584704U;
            aOrbiterF = (aOrbiterF ^ aOrbiterK) ^ 7304284015511876717U;
            aOrbiterF = RotL64((aOrbiterF * 6193179739025093929U), 37U);
            //
            aOrbiterB = ((aOrbiterB + aOrbiterD) + 5517927023543751734U) + aPhaseEOrbiterUpdateSaltD[(((31U - aIndex) + 7U)) & S_SALT1];
            aOrbiterJ = ((aOrbiterJ ^ aOrbiterB) ^ 17704756310857362759U) ^ aPhaseEOrbiterUpdateSaltA[(((31U - aIndex) + 11U)) & S_SALT1];
            aOrbiterJ = RotL64((aOrbiterJ * 15826832172923213591U), 11U);
            //
            aOrbiterC = (aOrbiterC + aOrbiterF) + 11347400363019508578U;
            aOrbiterH = (aOrbiterH ^ aOrbiterC) ^ 11696395232760991243U;
            aOrbiterH = RotL64((aOrbiterH * 9725231749679442003U), 3U);
            //
            aOrbiterH = (aOrbiterH + aOrbiterB) + 10875780291242873583U;
            aOrbiterD = ((aOrbiterD ^ aOrbiterH) ^ 7808740614343437672U) ^ aPhaseEOrbiterUpdateSaltB[((aIndex + 10U)) & S_SALT1];
            aOrbiterD = RotL64((aOrbiterD * 8889516201913716283U), 19U);
            //
            aOrbiterJ = ((aOrbiterJ + aOrbiterK) + 3145390996141902032U) + aPhaseEOrbiterUpdateSaltE[(((31U - aIndex) + 13U)) & S_SALT1];
            aOrbiterC = (aOrbiterC ^ aOrbiterJ) ^ 16080636485642732615U;
            aOrbiterC = RotL64((aOrbiterC * 7445756373012217305U), 27U);
            //
            aOrbiterF = (aOrbiterF + aOrbiterH) + 3929263288176983844U;
            aOrbiterB = (aOrbiterB ^ aOrbiterF) ^ 18210228766683996806U;
            aOrbiterB = RotL64((aOrbiterB * 13178080076505449091U), 43U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterJ) + 13948962323541421431U;
            aOrbiterK = (aOrbiterK ^ aOrbiterD) ^ 3037683309790156893U;
            aOrbiterK = RotL64((aOrbiterK * 13406672352222636739U), 53U);
            //
            aIngress = aOrbiterD ^ RotL64(aOrbiterC, 20U);
            aIngress = aIngress + (aOrbiterB ^ RotL64(aOrbiterH, 29U));
            aIngress = aIngress + (RotL64(aOrbiterF, 11U) ^ aOrbiterJ);
            aIngress = aIngress + RotL64(aOrbiterK, 53U);
            aIngress = TwistMix64::DiffuseB((aIngress + aScatter));
            //
            aWandererG = aWandererG + (((RotL64(aCross, 13U) + RotL64(aOrbiterJ, 53U)) + aOrbiterD) + RotL64(aCarry, 21U));
            aWandererE = aWandererE ^ (((RotL64(aPrevious, 37U) + RotL64(aOrbiterH, 43U)) + aOrbiterB) + aPhaseEWandererUpdateSaltA[((aIndex + 24U)) & S_SALT1]);
            aWandererF = aWandererF + (((RotL64(aScatter, 3U) + RotL64(aOrbiterC, 21U)) + aOrbiterF) + RotL64(aCarry, 3U));
            aWandererH = aWandererH ^ ((RotL64(aIngress, 57U) + RotL64(aOrbiterD, 27U)) + aOrbiterH);
            aWandererI = aWandererI + (((RotL64(aCross, 21U) + aOrbiterB) + RotL64(aOrbiterF, 13U)) + aPhaseEWandererUpdateSaltC[(((31U - aIndex) + 15U)) & S_SALT1]);
            aWandererD = aWandererD ^ ((RotL64(aPrevious, 48U) + RotL64(aOrbiterK, 34U)) + aOrbiterJ);
            aWandererK = aWandererK + ((RotL64(aIngress, 29U) + aOrbiterF) + RotL64(aOrbiterK, 5U));
            //
            aCarry = aCarry + (aWandererF ^ RotL64(aWandererI, 58U));
            aCarry = aCarry + (RotL64(aWandererE, 19U) ^ aWandererD);
            aCarry = aCarry + (aWandererG ^ RotL64(aWandererH, 23U));
            aCarry = aCarry + RotL64(aWandererK, 37U);
            aCarry = aCarry + RotL64(aIngress, 29U);
            aCarry = TwistMix64::DiffuseC(aCarry);
            //
            aOperationLaneA[aIndex] = aIngress;
        }
    
        // twist_loop_b loop 4
        // ingress from: aOperationLaneA, aInvestLaneC, aFireLaneB
        // ingress directions: aOperationLaneA forward forced, aInvestLaneC forward forced, aFireLaneB forward/backward random
        // cross from: aInvestLaneD, aExpandLaneD, aExpandLaneC
        // cross directions: aInvestLaneD backward forced, aExpandLaneD backward forced, aExpandLaneC backward/forward random
        // write to: aOperationLaneB
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aOperationLaneA[((aIndex + 19443U)) & S_BLOCK1], 5U) ^ RotL64(aInvestLaneC[((aIndex + 17584U)) & S_BLOCK1], 14U));
            aIngress ^= RotL64(aFireLaneB[((S_BLOCK1 - aIndex + 21636U)) & S_BLOCK1], 39U);
            aIngress = TwistMix64::DiffuseC(aIngress);
            //
            aCross = (RotL64(aInvestLaneD[((S_BLOCK1 - aIndex + 19308U)) & S_BLOCK1], 50U) ^ RotL64(aExpandLaneD[((S_BLOCK1 - aIndex + 19121U)) & S_BLOCK1], 13U));
            aCross ^= RotL64(aExpandLaneC[((aIndex + 16581U)) & S_BLOCK1], 41U);
            aCross = TwistMix64::DiffuseC(aCross);
            //
            aScatter = (RotL64(aCarry, 57U) + RotL64(aPrevious, 44U)) ^ (RotL64(aCross, 23U) + RotL64(aIngress, 11U));
            aScatter = TwistMix64::DiffuseA(aScatter);
            //
            aOrbiterD = (((aWandererJ + RotL64(aPrevious, 27U)) + RotL64(aCarry, 21U)) + 9446153639709651566U) + aPhaseEOrbiterAssignSaltE[(((31U - aIndex) + 11U)) & S_SALT1];
            aOrbiterE = ((aWandererE + RotL64(aScatter, 3U)) + RotL64(aCarry, 35U)) + 10550762260670758167U;
            aOrbiterG = (aWandererB + RotL64(aCross, 41U)) + 7062634922142578383U;
            aOrbiterK = ((aWandererF + RotL64(aIngress, 48U)) + RotL64(aCarry, 57U)) + 9178499097812764515U;
            aOrbiterI = (aWandererD + RotL64(aScatter, 19U)) + 6887103379773525538U;
            aOrbiterJ = (aWandererH + RotL64(aIngress, 35U)) + 6239750312052010257U;
            aOrbiterC = ((aWandererG + RotL64(aCross, 13U)) + 17645022614523287959U) + aPhaseEOrbiterAssignSaltA[((aIndex + 25U)) & S_SALT1];
            //
            aOrbiterD = (aOrbiterD + aOrbiterE) + 3639618183259408272U;
            aOrbiterG = ((aOrbiterG ^ aOrbiterD) ^ 3131737117548745095U) ^ aPhaseEOrbiterUpdateSaltC[(((31U - aIndex) + 20U)) & S_SALT1];
            aOrbiterG = RotL64((aOrbiterG * 6585057380704940395U), 27U);
            //
            aOrbiterK = ((aOrbiterK + aOrbiterI) + 7253994382396406554U) + aPhaseEOrbiterUpdateSaltD[((aIndex + 19U)) & S_SALT1];
            aOrbiterJ = (aOrbiterJ ^ aOrbiterK) ^ 15217993711938379561U;
            aOrbiterJ = RotL64((aOrbiterJ * 17853313384747259923U), 57U);
            //
            aOrbiterJ = ((aOrbiterJ + aOrbiterD) + 12594152227603630033U) + aPhaseEOrbiterUpdateSaltB[(((31U - aIndex) + 15U)) & S_SALT1];
            aOrbiterE = (aOrbiterE ^ aOrbiterJ) ^ 11250170200489647869U;
            aOrbiterE = RotL64((aOrbiterE * 546800378327864723U), 11U);
            //
            aOrbiterI = (aOrbiterI + aOrbiterJ) + 12936942656624279424U;
            aOrbiterD = (aOrbiterD ^ aOrbiterI) ^ 10990736056052106149U;
            aOrbiterD = RotL64((aOrbiterD * 7123916809953459187U), 47U);
            //
            aOrbiterG = (aOrbiterG + aOrbiterC) + 12787293075893090465U;
            aOrbiterK = ((aOrbiterK ^ aOrbiterG) ^ 17154990205620778151U) ^ aPhaseEOrbiterUpdateSaltF[(((31U - aIndex) + 24U)) & S_SALT1];
            aOrbiterK = RotL64((aOrbiterK * 10031369940028159521U), 37U);
            //
            aOrbiterE = (aOrbiterE + aOrbiterG) + 1270827262969060301U;
            aOrbiterC = (aOrbiterC ^ aOrbiterE) ^ 17337623431665013136U;
            aOrbiterC = RotL64((aOrbiterC * 1517262088236356107U), 19U);
            //
            aOrbiterC = (aOrbiterC + aOrbiterK) + 830330490987911853U;
            aOrbiterI = (aOrbiterI ^ aOrbiterC) ^ 6828309232554560547U;
            aOrbiterI = RotL64((aOrbiterI * 9742464176986145819U), 3U);
            //
            aIngress = aOrbiterK ^ RotL64(aOrbiterC, 57U);
            aIngress = aIngress + (aOrbiterE ^ RotL64(aOrbiterI, 11U));
            aIngress = aIngress + (aOrbiterD ^ RotL64(aOrbiterG, 4U));
            aIngress = aIngress + RotL64(aOrbiterJ, 29U);
            aIngress = TwistMix64::DiffuseA((aIngress + aScatter));
            //
            aWandererB = aWandererB ^ ((RotL64(aIngress, 3U) + aOrbiterE) + RotL64(aOrbiterC, 26U));
            aWandererH = aWandererH + ((((RotL64(aPrevious, 53U) + RotL64(aOrbiterJ, 5U)) + aOrbiterI) + RotL64(aCarry, 3U)) + aPhaseEWandererUpdateSaltD[(((31U - aIndex) + 10U)) & S_SALT1]);
            aWandererG = aWandererG ^ ((RotL64(aScatter, 39U) + RotL64(aOrbiterE, 39U)) + aOrbiterD);
            aWandererE = aWandererE + ((RotL64(aCross, 13U) + aOrbiterG) + RotL64(aOrbiterI, 19U));
            aWandererJ = aWandererJ ^ ((RotL64(aPrevious, 21U) + aOrbiterJ) + RotL64(aOrbiterK, 11U));
            aWandererD = aWandererD + (((RotL64(aCross, 47U) + aOrbiterD) + RotL64(aOrbiterJ, 47U)) + RotL64(aCarry, 23U));
            aWandererF = aWandererF ^ (((RotL64(aScatter, 60U) + RotL64(aOrbiterI, 57U)) + aOrbiterK) + aPhaseEWandererUpdateSaltB[((aIndex + 16U)) & S_SALT1]);
            //
            aCarry = aCarry + (RotL64(aWandererE, 6U) ^ aWandererG);
            aCarry = aCarry + (aWandererF ^ RotL64(aWandererH, 23U));
            aCarry = aCarry + (RotL64(aWandererB, 19U) ^ aWandererD);
            aCarry = aCarry + RotL64(aWandererJ, 27U);
            aCarry = aCarry + RotL64(aIngress, 57U);
            aCarry = TwistMix64::DiffuseB(aCarry);
            //
            aOperationLaneB[S_BLOCK1 - aIndex] = aIngress;
        }
    
        // twist_loop_b loop 5
        // ingress from: aOperationLaneB, aOperationLaneA, aExpandLaneB
        // ingress directions: aOperationLaneB forward forced, aOperationLaneA forward forced, aExpandLaneB forward/backward random
        // cross from: aExpandLaneC, aInvestLaneC, aInvestLaneD
        // cross directions: aExpandLaneC backward forced, aInvestLaneC backward forced, aInvestLaneD backward/forward random
        // write to: aOperationLaneC
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aOperationLaneB[((aIndex + 26276U)) & S_BLOCK1], 58U) ^ RotL64(aOperationLaneA[((aIndex + 26446U)) & S_BLOCK1], 29U));
            aIngress ^= RotL64(aExpandLaneB[((aIndex + 25888U)) & S_BLOCK1], 5U);
            aIngress = TwistMix64::DiffuseB(aIngress);
            //
            aCross = (RotL64(aExpandLaneC[((S_BLOCK1 - aIndex + 27166U)) & S_BLOCK1], 10U) ^ RotL64(aInvestLaneC[((S_BLOCK1 - aIndex + 23165U)) & S_BLOCK1], 19U));
            aCross ^= RotL64(aInvestLaneD[((aIndex + 23490U)) & S_BLOCK1], 27U);
            aCross = TwistMix64::DiffuseA(aCross);
            //
            aScatter = (RotL64(aPrevious, 39U) + RotL64(aCarry, 53U)) ^ (RotL64(aCross, 18U) + RotL64(aIngress, 5U));
            aScatter = TwistMix64::DiffuseA(aScatter);
            //
            aOrbiterA = ((aWandererH + RotL64(aPrevious, 29U)) + RotL64(aCarry, 47U)) + 1364174714924216027U;
            aOrbiterK = (aWandererI + RotL64(aScatter, 23U)) + 13561796874229506613U;
            aOrbiterB = (aWandererJ + RotL64(aCross, 12U)) + 11845572344206238305U;
            aOrbiterG = ((aWandererB + RotL64(aIngress, 35U)) + 15762708240326773763U) + aPhaseEOrbiterAssignSaltD[(((31U - aIndex) + 6U)) & S_SALT1];
            aOrbiterF = ((aWandererK + RotL64(aPrevious, 41U)) + 1157119665207900473U) + aPhaseEOrbiterAssignSaltF[(((31U - aIndex) + 28U)) & S_SALT1];
            aOrbiterJ = ((aWandererC + RotL64(aScatter, 51U)) + RotL64(aCarry, 23U)) + 6823546624372055260U;
            aOrbiterC = ((aWandererE + RotL64(aIngress, 5U)) + RotL64(aCarry, 3U)) + 14465564210523945121U;
            //
            aOrbiterA = ((aOrbiterA + aOrbiterK) + 10667464548080807531U) + aPhaseEOrbiterUpdateSaltE[((aIndex + 14U)) & S_SALT1];
            aOrbiterB = ((aOrbiterB ^ aOrbiterA) ^ 13445737493224316575U) ^ aPhaseEOrbiterUpdateSaltD[((aIndex + 17U)) & S_SALT1];
            aOrbiterB = RotL64((aOrbiterB * 12137295000900795711U), 11U);
            //
            aOrbiterG = (aOrbiterG + aOrbiterF) + 3009837893785957665U;
            aOrbiterA = (aOrbiterA ^ aOrbiterG) ^ 2886920524111083752U;
            aOrbiterA = RotL64((aOrbiterA * 15308180928967762543U), 57U);
            //
            aOrbiterB = (aOrbiterB + aOrbiterG) + 10886177449328249656U;
            aOrbiterJ = (aOrbiterJ ^ aOrbiterB) ^ 15067759884678100433U;
            aOrbiterJ = RotL64((aOrbiterJ * 5724566815989860041U), 39U);
            //
            aOrbiterK = (aOrbiterK + aOrbiterC) + 18307930462682331536U;
            aOrbiterG = ((aOrbiterG ^ aOrbiterK) ^ 8791864377579255801U) ^ aPhaseEOrbiterUpdateSaltF[((aIndex + 21U)) & S_SALT1];
            aOrbiterG = RotL64((aOrbiterG * 9265158882471421767U), 47U);
            //
            aOrbiterC = (aOrbiterC + aOrbiterB) + 805797468642992351U;
            aOrbiterF = ((aOrbiterF ^ aOrbiterC) ^ 5743305867058244964U) ^ aPhaseEOrbiterUpdateSaltA[((aIndex + 19U)) & S_SALT1];
            aOrbiterF = RotL64((aOrbiterF * 16263000753351131717U), 3U);
            //
            aOrbiterF = (aOrbiterF + aOrbiterJ) + 17102025528234481273U;
            aOrbiterK = (aOrbiterK ^ aOrbiterF) ^ 1841579177327486899U;
            aOrbiterK = RotL64((aOrbiterK * 3841603385577825265U), 19U);
            //
            aOrbiterJ = (aOrbiterJ + aOrbiterA) + 2189493507896508972U;
            aOrbiterC = (aOrbiterC ^ aOrbiterJ) ^ 18209567010094914374U;
            aOrbiterC = RotL64((aOrbiterC * 3737080408976852351U), 29U);
            //
            aIngress = aOrbiterB ^ RotL64(aOrbiterK, 14U);
            aIngress = aIngress + (RotL64(aOrbiterJ, 37U) ^ aOrbiterG);
            aIngress = aIngress + (aOrbiterA ^ RotL64(aOrbiterF, 23U));
            aIngress = aIngress + RotL64(aOrbiterC, 29U);
            aIngress = TwistMix64::DiffuseB((aIngress + aScatter));
            //
            aWandererJ = aWandererJ + ((RotL64(aCross, 43U) + RotL64(aOrbiterB, 27U)) + aOrbiterC);
            aWandererC = aWandererC ^ ((RotL64(aIngress, 58U) + RotL64(aOrbiterF, 19U)) + aOrbiterG);
            aWandererK = aWandererK + ((((RotL64(aPrevious, 3U) + aOrbiterA) + RotL64(aOrbiterC, 51U)) + RotL64(aCarry, 35U)) + aPhaseEWandererUpdateSaltF[(((31U - aIndex) + 10U)) & S_SALT1]);
            aWandererH = aWandererH ^ (((RotL64(aScatter, 11U) + aOrbiterC) + RotL64(aOrbiterK, 5U)) + aPhaseEWandererUpdateSaltE[(((31U - aIndex) + 29U)) & S_SALT1]);
            aWandererE = aWandererE + ((RotL64(aPrevious, 21U) + RotL64(aOrbiterG, 57U)) + aOrbiterB);
            aWandererI = aWandererI ^ ((RotL64(aCross, 29U) + RotL64(aOrbiterJ, 11U)) + aOrbiterC);
            aWandererB = aWandererB + (((RotL64(aIngress, 51U) + RotL64(aOrbiterA, 34U)) + aOrbiterB) + RotL64(aCarry, 19U));
            //
            aCarry = aCarry + (RotL64(aWandererK, 37U) ^ aWandererB);
            aCarry = aCarry + (RotL64(aWandererC, 46U) ^ aWandererJ);
            aCarry = aCarry + (aWandererI ^ RotL64(aWandererE, 5U));
            aCarry = aCarry + RotL64(aWandererH, 57U);
            aCarry = aCarry + RotL64(aIngress, 11U);
            aCarry = TwistMix64::DiffuseC(aCarry);
            //
            aOperationLaneC[aIndex] = aIngress;
        }
    
        // twist_loop_b loop 6
        // ingress from: aOperationLaneC, aExpandLaneA, aExpandLaneB
        // ingress directions: aOperationLaneC forward forced, aExpandLaneA forward forced, aExpandLaneB forward/backward random
        // cross from: aOperationLaneB, aOperationLaneA, aInvestLaneD
        // cross directions: aOperationLaneB backward forced, aOperationLaneA backward forced, aInvestLaneD backward/forward random
        // write to: aOperationLaneD
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aOperationLaneC[((aIndex + 31347U)) & S_BLOCK1], 57U) ^ RotL64(aExpandLaneA[((aIndex + 29826U)) & S_BLOCK1], 27U));
            aIngress ^= RotL64(aExpandLaneB[((aIndex + 28729U)) & S_BLOCK1], 38U);
            aIngress = TwistMix64::DiffuseB(aIngress);
            //
            aCross = (RotL64(aOperationLaneB[((S_BLOCK1 - aIndex + 32507U)) & S_BLOCK1], 39U) ^ RotL64(aOperationLaneA[((S_BLOCK1 - aIndex + 32431U)) & S_BLOCK1], 51U));
            aCross ^= RotL64(aInvestLaneD[((aIndex + 30129U)) & S_BLOCK1], 20U);
            aCross = TwistMix64::DiffuseB(aCross);
            //
            aScatter = (RotL64(aIngress, 57U) + RotL64(aCross, 42U)) ^ (RotL64(aPrevious, 11U) + RotL64(aCarry, 27U));
            aScatter = TwistMix64::DiffuseA(aScatter);
            //
            aOrbiterG = (((aWandererG + RotL64(aCross, 57U)) + RotL64(aCarry, 57U)) + 9751314027302668907U) + aPhaseEOrbiterAssignSaltC[(((31U - aIndex) + 28U)) & S_SALT1];
            aOrbiterI = (aWandererE + RotL64(aPrevious, 5U)) + 12175450995523107056U;
            aOrbiterF = ((aWandererB + RotL64(aScatter, 51U)) + RotL64(aCarry, 43U)) + 17519694958730119552U;
            aOrbiterB = ((aWandererH + RotL64(aIngress, 22U)) + RotL64(aCarry, 5U)) + 9093525527925682263U;
            aOrbiterE = (aWandererI + RotL64(aCross, 35U)) + 3713831321786810138U;
            aOrbiterJ = ((aWandererK + RotL64(aIngress, 29U)) + 10108355209191835040U) + aPhaseEOrbiterAssignSaltB[(((31U - aIndex) + 12U)) & S_SALT1];
            aOrbiterK = (aWandererA + RotL64(aPrevious, 41U)) + 12956307447311314768U;
            //
            aOrbiterG = (aOrbiterG + aOrbiterI) + 1904298513945877359U;
            aOrbiterF = (aOrbiterF ^ aOrbiterG) ^ 4658049993308574460U;
            aOrbiterF = RotL64((aOrbiterF * 10482422152074338611U), 19U);
            //
            aOrbiterB = (aOrbiterB + aOrbiterF) + 9826333658248851902U;
            aOrbiterE = ((aOrbiterE ^ aOrbiterB) ^ 12058666914724365134U) ^ aPhaseEOrbiterUpdateSaltA[((aIndex + 13U)) & S_SALT1];
            aOrbiterE = RotL64((aOrbiterE * 964233873188373939U), 53U);
            //
            aOrbiterJ = ((aOrbiterJ + aOrbiterB) + 2516574707110528099U) + aPhaseEOrbiterUpdateSaltD[((aIndex + 21U)) & S_SALT1];
            aOrbiterI = (aOrbiterI ^ aOrbiterJ) ^ 13335308331049750235U;
            aOrbiterI = RotL64((aOrbiterI * 5880227828760598587U), 47U);
            //
            aOrbiterI = (aOrbiterI + aOrbiterE) + 8230749255538495304U;
            aOrbiterK = ((aOrbiterK ^ aOrbiterI) ^ 16536559486797811486U) ^ aPhaseEOrbiterUpdateSaltB[(((31U - aIndex) + 8U)) & S_SALT1];
            aOrbiterK = RotL64((aOrbiterK * 7097036838156464969U), 3U);
            //
            aOrbiterE = (aOrbiterE + aOrbiterJ) + 12387639130570188998U;
            aOrbiterG = (aOrbiterG ^ aOrbiterE) ^ 8459259798142872020U;
            aOrbiterG = RotL64((aOrbiterG * 8001346480955847013U), 27U);
            //
            aOrbiterK = ((aOrbiterK + aOrbiterG) + 16083784052002800300U) + aPhaseEOrbiterUpdateSaltE[((aIndex + 29U)) & S_SALT1];
            aOrbiterB = (aOrbiterB ^ aOrbiterK) ^ 1957284290736468379U;
            aOrbiterB = RotL64((aOrbiterB * 5046501301740813065U), 35U);
            //
            aOrbiterF = (aOrbiterF + aOrbiterK) + 7349538179311335863U;
            aOrbiterJ = (aOrbiterJ ^ aOrbiterF) ^ 16395170077006105258U;
            aOrbiterJ = RotL64((aOrbiterJ * 4230485452156662763U), 13U);
            //
            aIngress = aOrbiterJ ^ RotL64(aOrbiterG, 13U);
            aIngress = aIngress + (RotL64(aOrbiterF, 23U) ^ aOrbiterE);
            aIngress = aIngress + (RotL64(aOrbiterB, 51U) ^ aOrbiterI);
            aIngress = aIngress + RotL64(aOrbiterK, 43U);
            aIngress = TwistMix64::DiffuseA((aIngress + aScatter));
            //
            aWandererG = aWandererG + (((RotL64(aCross, 19U) + RotL64(aOrbiterG, 19U)) + aOrbiterK) + RotL64(aCarry, 3U));
            aWandererE = aWandererE ^ ((RotL64(aIngress, 29U) + aOrbiterE) + RotL64(aOrbiterB, 36U));
            aWandererA = aWandererA + ((RotL64(aScatter, 13U) + RotL64(aOrbiterF, 53U)) + aOrbiterG);
            aWandererH = aWandererH ^ (((RotL64(aPrevious, 53U) + aOrbiterJ) + RotL64(aOrbiterE, 47U)) + aPhaseEWandererUpdateSaltC[(((31U - aIndex) + 11U)) & S_SALT1]);
            aWandererB = aWandererB + ((((RotL64(aScatter, 47U) + aOrbiterG) + RotL64(aOrbiterE, 5U)) + RotL64(aCarry, 19U)) + aPhaseEWandererUpdateSaltA[((aIndex + 24U)) & S_SALT1]);
            aWandererK = aWandererK ^ ((RotL64(aPrevious, 4U) + RotL64(aOrbiterI, 13U)) + aOrbiterG);
            aWandererI = aWandererI + ((RotL64(aIngress, 35U) + aOrbiterK) + RotL64(aOrbiterB, 27U));
            //
            aCarry = aCarry + (RotL64(aWandererB, 56U) ^ aWandererK);
            aCarry = aCarry + (aWandererG ^ RotL64(aWandererA, 43U));
            aCarry = aCarry + (aWandererE ^ RotL64(aWandererH, 29U));
            aCarry = aCarry + RotL64(aWandererI, 51U);
            aCarry = aCarry + RotL64(aIngress, 14U);
            aCarry = TwistMix64::DiffuseA(aCarry);
            //
            aOperationLaneD[S_BLOCK1 - aIndex] = aIngress;
        }
    }
    // GTwistRunTwist_B twist_loop_b (end)
    *pPrevious = aPrevious;
    *pIngress = aIngress;
    *pCarry = aCarry;
    *pWandererA = aWandererA;
    *pWandererB = aWandererB;
    *pWandererC = aWandererC;
    *pWandererD = aWandererD;
    *pWandererE = aWandererE;
    *pWandererF = aWandererF;
    *pWandererG = aWandererG;
    *pWandererH = aWandererH;
    *pWandererI = aWandererI;
    *pWandererJ = aWandererJ;
    *pWandererK = aWandererK;
}

void TwistExpander_Exercea_Arx::Twist_C(TwistWorkSpace *pWorkSpace,
                     std::uint8_t *pSource,
                     std::uint64_t *pPrevious,
                     std::uint64_t *pIngress,
                     std::uint64_t *pCarry,
                     std::uint64_t *pWandererA,
                     std::uint64_t *pWandererB,
                     std::uint64_t *pWandererC,
                     std::uint64_t *pWandererD,
                     std::uint64_t *pWandererE,
                     std::uint64_t *pWandererF,
                     std::uint64_t *pWandererG,
                     std::uint64_t *pWandererH,
                     std::uint64_t *pWandererI,
                     std::uint64_t *pWandererJ,
                     std::uint64_t *pWandererK) {
    [[maybe_unused]] std::uint8_t *aExpandLaneA = pWorkSpace->mExpansionLaneA;
    [[maybe_unused]] std::uint8_t *aExpandLaneB = pWorkSpace->mExpansionLaneB;
    [[maybe_unused]] std::uint8_t *aExpandLaneC = pWorkSpace->mExpansionLaneC;
    [[maybe_unused]] std::uint8_t *aExpandLaneD = pWorkSpace->mExpansionLaneD;
    [[maybe_unused]] std::uint8_t *aWorkLaneA = pWorkSpace->mWorkLaneA;
    [[maybe_unused]] std::uint8_t *aWorkLaneB = pWorkSpace->mWorkLaneB;
    [[maybe_unused]] std::uint8_t *aWorkLaneC = pWorkSpace->mWorkLaneC;
    [[maybe_unused]] std::uint8_t *aWorkLaneD = pWorkSpace->mWorkLaneD;
    [[maybe_unused]] std::uint8_t *aOperationLaneA = pWorkSpace->mOperationLaneA;
    [[maybe_unused]] std::uint8_t *aOperationLaneB = pWorkSpace->mOperationLaneB;
    [[maybe_unused]] std::uint8_t *aOperationLaneC = pWorkSpace->mOperationLaneC;
    [[maybe_unused]] std::uint8_t *aOperationLaneD = pWorkSpace->mOperationLaneD;
    [[maybe_unused]] std::uint8_t *aSnowLaneA = pWorkSpace->mSnowLaneA;
    [[maybe_unused]] std::uint8_t *aSnowLaneB = pWorkSpace->mSnowLaneB;
    [[maybe_unused]] std::uint8_t *aInvestLaneA = pWorkSpace->mInvestLaneA;
    [[maybe_unused]] std::uint8_t *aInvestLaneB = pWorkSpace->mInvestLaneB;
    [[maybe_unused]] std::uint8_t *aInvestLaneC = pWorkSpace->mInvestLaneC;
    [[maybe_unused]] std::uint8_t *aInvestLaneD = pWorkSpace->mInvestLaneD;
    [[maybe_unused]] std::uint64_t *aPhaseFOrbiterAssignSaltA = pWorkSpace->mDomainBundle.mPhaseFSalts.mOrbiterAssign.mSaltA;
    [[maybe_unused]] std::uint64_t *aPhaseFOrbiterAssignSaltB = pWorkSpace->mDomainBundle.mPhaseFSalts.mOrbiterAssign.mSaltB;
    [[maybe_unused]] std::uint64_t *aPhaseFOrbiterAssignSaltC = pWorkSpace->mDomainBundle.mPhaseFSalts.mOrbiterAssign.mSaltC;
    [[maybe_unused]] std::uint64_t *aPhaseFOrbiterAssignSaltD = pWorkSpace->mDomainBundle.mPhaseFSalts.mOrbiterAssign.mSaltD;
    [[maybe_unused]] std::uint64_t *aPhaseFOrbiterAssignSaltE = pWorkSpace->mDomainBundle.mPhaseFSalts.mOrbiterAssign.mSaltE;
    [[maybe_unused]] std::uint64_t *aPhaseFOrbiterAssignSaltF = pWorkSpace->mDomainBundle.mPhaseFSalts.mOrbiterAssign.mSaltF;
    [[maybe_unused]] std::uint64_t *aPhaseFOrbiterUpdateSaltA = pWorkSpace->mDomainBundle.mPhaseFSalts.mOrbiterUpdate.mSaltA;
    [[maybe_unused]] std::uint64_t *aPhaseFOrbiterUpdateSaltB = pWorkSpace->mDomainBundle.mPhaseFSalts.mOrbiterUpdate.mSaltB;
    [[maybe_unused]] std::uint64_t *aPhaseFOrbiterUpdateSaltC = pWorkSpace->mDomainBundle.mPhaseFSalts.mOrbiterUpdate.mSaltC;
    [[maybe_unused]] std::uint64_t *aPhaseFOrbiterUpdateSaltD = pWorkSpace->mDomainBundle.mPhaseFSalts.mOrbiterUpdate.mSaltD;
    [[maybe_unused]] std::uint64_t *aPhaseFOrbiterUpdateSaltE = pWorkSpace->mDomainBundle.mPhaseFSalts.mOrbiterUpdate.mSaltE;
    [[maybe_unused]] std::uint64_t *aPhaseFOrbiterUpdateSaltF = pWorkSpace->mDomainBundle.mPhaseFSalts.mOrbiterUpdate.mSaltF;
    [[maybe_unused]] std::uint64_t *aPhaseFWandererUpdateSaltA = pWorkSpace->mDomainBundle.mPhaseFSalts.mWandererUpdate.mSaltA;
    [[maybe_unused]] std::uint64_t *aPhaseFWandererUpdateSaltB = pWorkSpace->mDomainBundle.mPhaseFSalts.mWandererUpdate.mSaltB;
    [[maybe_unused]] std::uint64_t *aPhaseFWandererUpdateSaltC = pWorkSpace->mDomainBundle.mPhaseFSalts.mWandererUpdate.mSaltC;
    [[maybe_unused]] std::uint64_t *aPhaseFWandererUpdateSaltD = pWorkSpace->mDomainBundle.mPhaseFSalts.mWandererUpdate.mSaltD;
    [[maybe_unused]] std::uint64_t *aPhaseFWandererUpdateSaltE = pWorkSpace->mDomainBundle.mPhaseFSalts.mWandererUpdate.mSaltE;
    [[maybe_unused]] std::uint64_t *aPhaseFWandererUpdateSaltF = pWorkSpace->mDomainBundle.mPhaseFSalts.mWandererUpdate.mSaltF;
    std::uint64_t aCross = 0; std::uint64_t aScatter = 0;

    std::uint64_t aOrbiterA = 0; std::uint64_t aOrbiterB = 0; std::uint64_t aOrbiterC = 0; std::uint64_t aOrbiterD = 0;
    std::uint64_t aOrbiterE = 0; std::uint64_t aOrbiterF = 0; std::uint64_t aOrbiterG = 0; std::uint64_t aOrbiterH = 0;
    std::uint64_t aOrbiterI = 0; std::uint64_t aOrbiterJ = 0; std::uint64_t aOrbiterK = 0;

    // [twist arx]
    [[maybe_unused]] std::uint8_t *mSource = pSource;
    std::uint64_t aPrevious = *pPrevious;
    std::uint64_t aIngress = *pIngress;
    std::uint64_t aCarry = *pCarry;
    std::uint64_t aWandererA = *pWandererA;
    std::uint64_t aWandererB = *pWandererB;
    std::uint64_t aWandererC = *pWandererC;
    std::uint64_t aWandererD = *pWandererD;
    std::uint64_t aWandererE = *pWandererE;
    std::uint64_t aWandererF = *pWandererF;
    std::uint64_t aWandererG = *pWandererG;
    std::uint64_t aWandererH = *pWandererH;
    std::uint64_t aWandererI = *pWandererI;
    std::uint64_t aWandererJ = *pWandererJ;
    std::uint64_t aWandererK = *pWandererK;
    // GTwistRunTwist_C twist_loop_c (start)
    {
        // GTwistRunTwist_C twist_loop_c lane group
        // read from: aOperationLaneA, aOperationLaneB, aExpandLaneC, aOperationLaneC, aOperationLaneD, aInvestLaneD, aSnowLaneA, aExpandLaneD, aExpandLaneB, aSnowLaneB, aInvestLaneA, aWorkLaneA, aExpandLaneA, aWorkLaneB, aInvestLaneC, aWorkLaneC, aInvestLaneB
        // write to: aSnowLaneA, aSnowLaneB, aWorkLaneA, aWorkLaneB, aWorkLaneC, aWorkLaneD
    
        // twist_loop_c loop 1
        // ingress from: aOperationLaneA, aOperationLaneB, aExpandLaneC
        // ingress directions: aOperationLaneA forward forced, aOperationLaneB forward forced, aExpandLaneC forward/backward random
        // cross from: aOperationLaneC, aOperationLaneD, aInvestLaneD
        // cross directions: aOperationLaneC backward forced, aOperationLaneD backward forced, aInvestLaneD backward/forward random
        // write to: aSnowLaneA
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aOperationLaneA[((aIndex + 1023U)) & S_BLOCK1], 11U) ^ RotL64(aOperationLaneB[((aIndex + 4918U)) & S_BLOCK1], 53U));
            aIngress ^= RotL64(aExpandLaneC[((aIndex + 2989U)) & S_BLOCK1], 30U);
            aIngress = TwistMix64::DiffuseA(aIngress);
            //
            aCross = (RotL64(aOperationLaneC[((S_BLOCK1 - aIndex + 456U)) & S_BLOCK1], 35U) ^ RotL64(aOperationLaneD[((S_BLOCK1 - aIndex + 4103U)) & S_BLOCK1], 47U));
            aCross ^= RotL64(aInvestLaneD[((aIndex + 5191U)) & S_BLOCK1], 14U);
            aCross = TwistMix64::DiffuseA(aCross);
            //
            aScatter = (RotL64(aPrevious, 23U) + RotL64(aCross, 10U)) ^ (RotL64(aIngress, 41U) + RotL64(aCarry, 53U));
            aScatter = TwistMix64::DiffuseC(aScatter);
            //
            aOrbiterD = (aWandererD + RotL64(aCross, 44U)) + 12632404972795375757U;
            aOrbiterH = (aWandererJ + RotL64(aIngress, 37U)) + 5351879979055988456U;
            aOrbiterE = ((aWandererE + RotL64(aPrevious, 51U)) + 3597737727467443413U) + aPhaseFOrbiterAssignSaltC[((aIndex + 25U)) & S_SALT1];
            aOrbiterJ = (aWandererG + RotL64(aScatter, 5U)) + 2830846754917852318U;
            aOrbiterK = (aWandererF + RotL64(aPrevious, 13U)) + 17311925960294518018U;
            aOrbiterB = (aWandererH + RotL64(aScatter, 53U)) + 2083584640523695383U;
            aOrbiterG = (aWandererK + RotL64(aIngress, 11U)) + 15049343611387010158U;
            aOrbiterC = ((aWandererB + RotL64(aCross, 35U)) + RotL64(aCarry, 51U)) + 6443050378205811147U;
            aOrbiterI = (((aWandererI + RotL64(aIngress, 18U)) + RotL64(aCarry, 27U)) + 6021965178697344070U) + aPhaseFOrbiterAssignSaltE[((aIndex + 10U)) & S_SALT1];
            aOrbiterF = (aWandererC + RotL64(aPrevious, 21U)) + 5080289878758029976U;
            aOrbiterA = ((aWandererA + RotL64(aScatter, 57U)) + RotL64(aCarry, 5U)) + 576927745306972983U;
            //
            aOrbiterD = (aOrbiterD + aOrbiterH) + 4728489691382690859U;
            aOrbiterE = ((aOrbiterE ^ aOrbiterD) ^ 6184355840165758855U) ^ aPhaseFOrbiterUpdateSaltD[((aIndex + 23U)) & S_SALT1];
            aOrbiterE = RotL64((aOrbiterE * 1515043910404156423U), 11U);
            //
            aOrbiterJ = (aOrbiterJ + aOrbiterD) + 11220539885798595450U;
            aOrbiterK = (aOrbiterK ^ aOrbiterJ) ^ 11091438724966718214U;
            aOrbiterK = RotL64((aOrbiterK * 8225347114759391961U), 3U);
            //
            aOrbiterB = (aOrbiterB + aOrbiterG) + 17184210490020062419U;
            aOrbiterC = (aOrbiterC ^ aOrbiterB) ^ 2150997767099116408U;
            aOrbiterC = RotL64((aOrbiterC * 8058553821648892499U), 53U);
            //
            aOrbiterI = (aOrbiterI + aOrbiterF) + 7021953562676903717U;
            aOrbiterD = (aOrbiterD ^ aOrbiterI) ^ 17159676348343312834U;
            aOrbiterD = RotL64((aOrbiterD * 13877284519668483549U), 13U);
            //
            aOrbiterC = ((aOrbiterC + aOrbiterJ) + 10367891770525239784U) + aPhaseFOrbiterUpdateSaltF[((aIndex + 7U)) & S_SALT1];
            aOrbiterA = ((aOrbiterA ^ aOrbiterC) ^ 11922478487264201233U) ^ aPhaseFOrbiterUpdateSaltA[((aIndex + 11U)) & S_SALT1];
            aOrbiterA = RotL64((aOrbiterA * 9195137452661956029U), 51U);
            //
            aOrbiterA = (aOrbiterA + aOrbiterK) + 17815162358981720634U;
            aOrbiterG = (aOrbiterG ^ aOrbiterA) ^ 9582631251085100284U;
            aOrbiterG = RotL64((aOrbiterG * 11838992994130850483U), 39U);
            //
            aOrbiterF = (aOrbiterF + aOrbiterC) + 872593750259572264U;
            aOrbiterH = (aOrbiterH ^ aOrbiterF) ^ 17832330100262167302U;
            aOrbiterH = RotL64((aOrbiterH * 1114416841510028467U), 43U);
            //
            aOrbiterK = (aOrbiterK + aOrbiterE) + 16601139856969287418U;
            aOrbiterI = (aOrbiterI ^ aOrbiterK) ^ 14931287111691324985U;
            aOrbiterI = RotL64((aOrbiterI * 16757174577841001179U), 47U);
            //
            aOrbiterG = (aOrbiterG + aOrbiterI) + 11413072442039115924U;
            aOrbiterJ = (aOrbiterJ ^ aOrbiterG) ^ 15253605470589905889U;
            aOrbiterJ = RotL64((aOrbiterJ * 10832817442285245673U), 37U);
            //
            aOrbiterH = (aOrbiterH + aOrbiterA) + 3653487723581514107U;
            aOrbiterB = ((aOrbiterB ^ aOrbiterH) ^ 14891378240114471865U) ^ aPhaseFOrbiterUpdateSaltC[((aIndex + 13U)) & S_SALT1];
            aOrbiterB = RotL64((aOrbiterB * 1386594204573386051U), 23U);
            //
            aOrbiterE = (aOrbiterE + aOrbiterB) + 15659724464711852035U;
            aOrbiterF = (aOrbiterF ^ aOrbiterE) ^ 12632404972795375757U;
            aOrbiterF = RotL64((aOrbiterF * 2407347385127296647U), 29U);
            //
            aIngress = RotL64(aOrbiterD, 37U) ^ aOrbiterE;
            aIngress = aIngress + (aOrbiterA ^ RotL64(aOrbiterB, 3U));
            aIngress = aIngress + (aOrbiterG ^ RotL64(aOrbiterI, 29U));
            aIngress = aIngress + (aOrbiterJ ^ RotL64(aOrbiterF, 35U));
            aIngress = aIngress + (RotL64(aOrbiterH, 23U) ^ aOrbiterC);
            aIngress = aIngress + RotL64(aOrbiterK, 46U);
            aIngress = TwistMix64::DiffuseA((aIngress + aScatter));
            //
            aWandererK = aWandererK ^ ((RotL64(aCross, 60U) + RotL64(aOrbiterI, 57U)) + aOrbiterB);
            aWandererC = aWandererC + ((RotL64(aPrevious, 39U) + aOrbiterC) + RotL64(aOrbiterD, 20U));
            aWandererA = aWandererA ^ ((RotL64(aScatter, 35U) + RotL64(aOrbiterK, 27U)) + aOrbiterG);
            aWandererH = aWandererH + ((RotL64(aIngress, 23U) + aOrbiterH) + RotL64(aOrbiterG, 35U));
            aWandererG = aWandererG ^ ((RotL64(aCross, 37U) + RotL64(aOrbiterC, 47U)) + aOrbiterI);
            aWandererB = aWandererB + (((RotL64(aScatter, 12U) + RotL64(aOrbiterJ, 53U)) + aOrbiterK) + RotL64(aCarry, 47U));
            aWandererF = aWandererF ^ ((RotL64(aIngress, 29U) + RotL64(aOrbiterE, 41U)) + aOrbiterD);
            aWandererE = aWandererE + (((RotL64(aPrevious, 51U) + aOrbiterH) + RotL64(aOrbiterA, 30U)) + aPhaseFWandererUpdateSaltA[(((31U - aIndex) + 15U)) & S_SALT1]);
            aWandererD = aWandererD ^ ((RotL64(aIngress, 53U) + RotL64(aOrbiterC, 39U)) + aOrbiterE);
            aWandererJ = aWandererJ + (((RotL64(aCross, 5U) + RotL64(aOrbiterF, 11U)) + aOrbiterA) + RotL64(aCarry, 3U));
            aWandererI = aWandererI ^ (((RotL64(aPrevious, 57U) + aOrbiterJ) + RotL64(aOrbiterC, 13U)) + aPhaseFWandererUpdateSaltF[(((31U - aIndex) + 3U)) & S_SALT1]);
            //
            aCarry = aCarry + (aWandererB ^ RotL64(aWandererJ, 44U));
            aCarry = aCarry + (aWandererA ^ RotL64(aWandererE, 35U));
            aCarry = aCarry + (RotL64(aWandererK, 13U) ^ aWandererI);
            aCarry = aCarry + (RotL64(aWandererF, 21U) ^ aWandererD);
            aCarry = aCarry + (RotL64(aWandererH, 56U) ^ aWandererC);
            aCarry = aCarry + RotL64(aWandererG, 19U);
            aCarry = aCarry + RotL64(aIngress, 11U);
            aCarry = TwistMix64::DiffuseC(aCarry);
            //
            aSnowLaneA[aIndex] = aIngress;
        }
    
        // twist_loop_c loop 2
        // ingress from: aSnowLaneA, aOperationLaneC, aOperationLaneD, aExpandLaneD
        // ingress directions: aSnowLaneA forward forced, aOperationLaneC forward forced, aOperationLaneD forward forced, aExpandLaneD forward/backward random
        // cross from: aOperationLaneA, aOperationLaneB, aExpandLaneB
        // cross directions: aOperationLaneA backward forced, aOperationLaneB backward forced, aExpandLaneB backward/forward random
        // write to: aSnowLaneB
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aSnowLaneA[((aIndex + 7035U)) & S_BLOCK1], 5U) ^ RotL64(aOperationLaneC[((aIndex + 6175U)) & S_BLOCK1], 57U));
            aIngress ^= (RotL64(aOperationLaneD[((aIndex + 6503U)) & S_BLOCK1], 34U) ^ RotL64(aExpandLaneD[((S_BLOCK1 - aIndex + 7329U)) & S_BLOCK1], 19U));
            aIngress = TwistMix64::DiffuseA(aIngress);
            //
            aCross = (RotL64(aOperationLaneA[((S_BLOCK1 - aIndex + 7589U)) & S_BLOCK1], 27U) ^ RotL64(aOperationLaneB[((S_BLOCK1 - aIndex + 9279U)) & S_BLOCK1], 54U));
            aCross ^= RotL64(aExpandLaneB[((S_BLOCK1 - aIndex + 7355U)) & S_BLOCK1], 13U);
            aCross = TwistMix64::DiffuseC(aCross);
            //
            aScatter = (RotL64(aPrevious, 26U) ^ RotL64(aCarry, 39U)) + (RotL64(aIngress, 11U) ^ RotL64(aCross, 53U));
            aScatter = TwistMix64::DiffuseB(aScatter);
            //
            aOrbiterH = (aWandererG + RotL64(aPrevious, 10U)) + 13714409587461539863U;
            aOrbiterD = (aWandererC + RotL64(aCross, 53U)) + 14101156723903265839U;
            aOrbiterF = (aWandererI + RotL64(aIngress, 27U)) + 7063754562895369001U;
            aOrbiterJ = ((aWandererB + RotL64(aScatter, 57U)) + RotL64(aCarry, 13U)) + 12320578575245519386U;
            aOrbiterA = (aWandererD + RotL64(aIngress, 13U)) + 11744826789631008424U;
            aOrbiterE = ((aWandererJ + RotL64(aScatter, 47U)) + 8744816505096675597U) + aPhaseFOrbiterAssignSaltF[((aIndex + 23U)) & S_SALT1];
            aOrbiterB = (aWandererK + RotL64(aCross, 35U)) + 10405435520084528645U;
            aOrbiterG = (aWandererE + RotL64(aPrevious, 41U)) + 1463157688070683543U;
            aOrbiterI = ((aWandererA + RotL64(aIngress, 24U)) + RotL64(aCarry, 21U)) + 12379603577919617703U;
            aOrbiterK = ((aWandererH + RotL64(aPrevious, 51U)) + RotL64(aCarry, 37U)) + 1343439118031348146U;
            aOrbiterC = ((aWandererF + RotL64(aCross, 19U)) + 16118850268070235540U) + aPhaseFOrbiterAssignSaltA[((aIndex + 18U)) & S_SALT1];
            //
            aOrbiterH = (aOrbiterH + aOrbiterD) + 14116264435819277136U;
            aOrbiterF = (aOrbiterF ^ aOrbiterH) ^ 5251698273012432109U;
            aOrbiterF = RotL64((aOrbiterF * 1495818611622063967U), 19U);
            //
            aOrbiterF = (aOrbiterF + aOrbiterJ) + 14806408656041403829U;
            aOrbiterA = ((aOrbiterA ^ aOrbiterF) ^ 11569345414052398227U) ^ aPhaseFOrbiterUpdateSaltD[((aIndex + 20U)) & S_SALT1];
            aOrbiterA = RotL64((aOrbiterA * 9913158908301414861U), 11U);
            //
            aOrbiterE = (aOrbiterE + aOrbiterB) + 17063874769147888574U;
            aOrbiterG = (aOrbiterG ^ aOrbiterE) ^ 9927420478679581917U;
            aOrbiterG = RotL64((aOrbiterG * 9042782809534196563U), 39U);
            //
            aOrbiterB = (aOrbiterB + aOrbiterF) + 2550285599827162167U;
            aOrbiterI = (aOrbiterI ^ aOrbiterB) ^ 17801534123304996448U;
            aOrbiterI = RotL64((aOrbiterI * 2160836889363614721U), 57U);
            //
            aOrbiterJ = (aOrbiterJ + aOrbiterG) + 6456685241021762041U;
            aOrbiterK = ((aOrbiterK ^ aOrbiterJ) ^ 17064208177372969289U) ^ aPhaseFOrbiterUpdateSaltB[(((31U - aIndex) + 26U)) & S_SALT1];
            aOrbiterK = RotL64((aOrbiterK * 13726627607233302493U), 23U);
            //
            aOrbiterA = (aOrbiterA + aOrbiterK) + 18279938244131982650U;
            aOrbiterD = ((aOrbiterD ^ aOrbiterA) ^ 8211002229712129419U) ^ aPhaseFOrbiterUpdateSaltE[(((31U - aIndex) + 21U)) & S_SALT1];
            aOrbiterD = RotL64((aOrbiterD * 12931373380977640645U), 13U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterE) + 12795832560781931767U;
            aOrbiterJ = (aOrbiterJ ^ aOrbiterD) ^ 286378504074349650U;
            aOrbiterJ = RotL64((aOrbiterJ * 85453101173293509U), 35U);
            //
            aOrbiterG = (aOrbiterG + aOrbiterI) + 5835304250436889513U;
            aOrbiterC = (aOrbiterC ^ aOrbiterG) ^ 12704972686724379659U;
            aOrbiterC = RotL64((aOrbiterC * 1198789639656336053U), 3U);
            //
            aOrbiterK = (aOrbiterK + aOrbiterC) + 12555700587254295099U;
            aOrbiterE = ((aOrbiterE ^ aOrbiterK) ^ 6740149669657971715U) ^ aPhaseFOrbiterUpdateSaltA[((aIndex + 27U)) & S_SALT1];
            aOrbiterE = RotL64((aOrbiterE * 9376048577305482691U), 37U);
            //
            aOrbiterC = (aOrbiterC + aOrbiterH) + 1541392147096889431U;
            aOrbiterB = (aOrbiterB ^ aOrbiterC) ^ 16891341703173286949U;
            aOrbiterB = RotL64((aOrbiterB * 697452963711223355U), 5U);
            //
            aOrbiterI = (aOrbiterI + aOrbiterA) + 8811637585092392653U;
            aOrbiterH = (aOrbiterH ^ aOrbiterI) ^ 13714409587461539863U;
            aOrbiterH = RotL64((aOrbiterH * 2578939920876994763U), 21U);
            //
            aIngress = aOrbiterI ^ RotL64(aOrbiterK, 58U);
            aIngress = aIngress + (RotL64(aOrbiterH, 13U) ^ aOrbiterG);
            aIngress = aIngress + (RotL64(aOrbiterC, 23U) ^ aOrbiterB);
            aIngress = aIngress + (aOrbiterE ^ RotL64(aOrbiterD, 11U));
            aIngress = aIngress + (aOrbiterA ^ RotL64(aOrbiterJ, 41U));
            aIngress = aIngress + RotL64(aOrbiterF, 51U);
            aIngress = TwistMix64::DiffuseA((aIngress + aScatter));
            //
            aWandererC = aWandererC ^ ((RotL64(aScatter, 23U) + aOrbiterD) + RotL64(aOrbiterI, 37U));
            aWandererD = aWandererD + (((RotL64(aIngress, 18U) + aOrbiterC) + RotL64(aOrbiterG, 24U)) + RotL64(aCarry, 57U));
            aWandererE = aWandererE ^ ((RotL64(aPrevious, 35U) + RotL64(aOrbiterH, 11U)) + aOrbiterE);
            aWandererF = aWandererF + ((RotL64(aCross, 43U) + RotL64(aOrbiterF, 39U)) + aOrbiterA);
            aWandererB = aWandererB ^ (((RotL64(aIngress, 29U) + aOrbiterK) + RotL64(aOrbiterG, 43U)) + aPhaseFWandererUpdateSaltC[(((31U - aIndex) + 5U)) & S_SALT1]);
            aWandererI = aWandererI + (((RotL64(aPrevious, 13U) + RotL64(aOrbiterG, 27U)) + aOrbiterJ) + RotL64(aCarry, 35U));
            aWandererA = aWandererA ^ (((RotL64(aScatter, 41U) + RotL64(aOrbiterH, 20U)) + aOrbiterI) + aPhaseFWandererUpdateSaltB[(((31U - aIndex) + 19U)) & S_SALT1]);
            aWandererH = aWandererH + ((RotL64(aCross, 54U) + aOrbiterB) + RotL64(aOrbiterD, 35U));
            aWandererG = aWandererG ^ ((RotL64(aScatter, 27U) + RotL64(aOrbiterG, 57U)) + aOrbiterA);
            aWandererJ = aWandererJ + ((RotL64(aCross, 51U) + aOrbiterI) + RotL64(aOrbiterJ, 47U));
            aWandererK = aWandererK ^ ((RotL64(aIngress, 21U) + aOrbiterA) + RotL64(aOrbiterI, 3U));
            //
            aCarry = aCarry + (aWandererG ^ RotL64(aWandererC, 3U));
            aCarry = aCarry + (RotL64(aWandererJ, 10U) ^ aWandererD);
            aCarry = aCarry + (RotL64(aWandererI, 29U) ^ aWandererA);
            aCarry = aCarry + (aWandererE ^ RotL64(aWandererF, 43U));
            aCarry = aCarry + (RotL64(aWandererB, 37U) ^ aWandererH);
            aCarry = aCarry + RotL64(aWandererK, 27U);
            aCarry = aCarry + RotL64(aIngress, 14U);
            aCarry = TwistMix64::DiffuseB(aCarry);
            //
            aSnowLaneB[S_BLOCK1 - aIndex] = aIngress;
        }
    
        // twist_loop_c loop 3
        // ingress from: aSnowLaneB, aOperationLaneA, aInvestLaneA
        // ingress directions: aSnowLaneB forward forced, aOperationLaneA forward forced, aInvestLaneA forward/backward random
        // cross from: aSnowLaneA, aOperationLaneC
        // cross directions: aSnowLaneA backward forced, aOperationLaneC backward/forward random
        // write to: aWorkLaneA
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aSnowLaneB[((aIndex + 14118U)) & S_BLOCK1], 37U) ^ RotL64(aOperationLaneA[((aIndex + 11187U)) & S_BLOCK1], 47U));
            aIngress ^= RotL64(aInvestLaneA[((aIndex + 11324U)) & S_BLOCK1], 28U);
            aIngress = TwistMix64::DiffuseC(aIngress);
            //
            aCross = RotL64(aSnowLaneA[((S_BLOCK1 - aIndex + 15514U)) & S_BLOCK1], 38U) ^ RotL64(aOperationLaneC[((S_BLOCK1 - aIndex + 12972U)) & S_BLOCK1], 19U);
            aCross = TwistMix64::DiffuseB(aCross);
            //
            aScatter = (RotL64(aIngress, 41U) ^ RotL64(aCarry, 29U)) + (RotL64(aCross, 53U) ^ RotL64(aPrevious, 10U));
            aScatter = TwistMix64::DiffuseB(aScatter);
            //
            aOrbiterJ = ((aWandererE + RotL64(aPrevious, 23U)) + RotL64(aCarry, 39U)) + 826930775230515406U;
            aOrbiterE = (aWandererG + RotL64(aScatter, 4U)) + 5137814617363250861U;
            aOrbiterG = (aWandererI + RotL64(aIngress, 35U)) + 14761561947426681616U;
            aOrbiterF = (aWandererF + RotL64(aCross, 11U)) + 12773023438753662590U;
            aOrbiterI = (((aWandererB + RotL64(aScatter, 39U)) + RotL64(aCarry, 29U)) + 7331345852207096322U) + aPhaseFOrbiterAssignSaltB[(((31U - aIndex) + 14U)) & S_SALT1];
            aOrbiterD = (aWandererK + RotL64(aIngress, 29U)) + 3899381212671247460U;
            aOrbiterA = ((aWandererC + RotL64(aPrevious, 41U)) + 10072004147620068599U) + aPhaseFOrbiterAssignSaltD[((aIndex + 17U)) & S_SALT1];
            aOrbiterC = ((aWandererD + RotL64(aCross, 56U)) + RotL64(aCarry, 3U)) + 3424585039401897560U;
            aOrbiterK = (aWandererH + RotL64(aScatter, 53U)) + 8246760141625966321U;
            aOrbiterH = (aWandererJ + RotL64(aIngress, 43U)) + 3655992860610853290U;
            aOrbiterB = (aWandererA + RotL64(aPrevious, 19U)) + 11154618022505863898U;
            //
            aOrbiterJ = (aOrbiterJ + aOrbiterE) + 15629361991059709973U;
            aOrbiterG = (aOrbiterG ^ aOrbiterJ) ^ 10842068502278489664U;
            aOrbiterG = RotL64((aOrbiterG * 17223002513104960799U), 57U);
            //
            aOrbiterF = (aOrbiterF + aOrbiterI) + 5571312349016336686U;
            aOrbiterE = ((aOrbiterE ^ aOrbiterF) ^ 589313823745748879U) ^ aPhaseFOrbiterUpdateSaltB[(((31U - aIndex) + 22U)) & S_SALT1];
            aOrbiterE = RotL64((aOrbiterE * 1356685926549786027U), 11U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterJ) + 13633457935771935260U;
            aOrbiterI = (aOrbiterI ^ aOrbiterD) ^ 12684602052812183096U;
            aOrbiterI = RotL64((aOrbiterI * 4689206269919806711U), 39U);
            //
            aOrbiterG = (aOrbiterG + aOrbiterA) + 5711307583717354204U;
            aOrbiterC = (aOrbiterC ^ aOrbiterG) ^ 7181854170553728211U;
            aOrbiterC = RotL64((aOrbiterC * 9835601115561325911U), 47U);
            //
            aOrbiterA = ((aOrbiterA + aOrbiterK) + 1884620014396115821U) + aPhaseFOrbiterUpdateSaltF[((aIndex + 15U)) & S_SALT1];
            aOrbiterH = ((aOrbiterH ^ aOrbiterA) ^ 1471516373272364262U) ^ aPhaseFOrbiterUpdateSaltD[(((31U - aIndex) + 21U)) & S_SALT1];
            aOrbiterH = RotL64((aOrbiterH * 5126319375714848029U), 41U);
            //
            aOrbiterH = (aOrbiterH + aOrbiterF) + 742739371092077733U;
            aOrbiterJ = (aOrbiterJ ^ aOrbiterH) ^ 8075893317715227838U;
            aOrbiterJ = RotL64((aOrbiterJ * 11208274111743259795U), 27U);
            //
            aOrbiterK = (aOrbiterK + aOrbiterD) + 8179547722249281263U;
            aOrbiterF = (aOrbiterF ^ aOrbiterK) ^ 15305282712174742323U;
            aOrbiterF = RotL64((aOrbiterF * 7951986906055462929U), 19U);
            //
            aOrbiterI = (aOrbiterI + aOrbiterG) + 1430543231751281079U;
            aOrbiterB = ((aOrbiterB ^ aOrbiterI) ^ 14585341768267283387U) ^ aPhaseFOrbiterUpdateSaltA[((aIndex + 3U)) & S_SALT1];
            aOrbiterB = RotL64((aOrbiterB * 313213844964269133U), 23U);
            //
            aOrbiterE = (aOrbiterE + aOrbiterB) + 8123889986027932297U;
            aOrbiterA = (aOrbiterA ^ aOrbiterE) ^ 2081696191347150910U;
            aOrbiterA = RotL64((aOrbiterA * 4869653441012615053U), 53U);
            //
            aOrbiterC = (aOrbiterC + aOrbiterH) + 10166788886199265936U;
            aOrbiterD = (aOrbiterD ^ aOrbiterC) ^ 15927074835525735601U;
            aOrbiterD = RotL64((aOrbiterD * 6747650218540675523U), 5U);
            //
            aOrbiterB = (aOrbiterB + aOrbiterC) + 6997764816848988590U;
            aOrbiterK = (aOrbiterK ^ aOrbiterB) ^ 826930775230515406U;
            aOrbiterK = RotL64((aOrbiterK * 9943232461538279601U), 13U);
            //
            aIngress = aOrbiterG ^ RotL64(aOrbiterH, 35U);
            aIngress = aIngress + (RotL64(aOrbiterD, 3U) ^ aOrbiterI);
            aIngress = aIngress + (RotL64(aOrbiterB, 51U) ^ aOrbiterE);
            aIngress = aIngress + (RotL64(aOrbiterF, 38U) ^ aOrbiterJ);
            aIngress = aIngress + (aOrbiterA ^ RotL64(aOrbiterK, 11U));
            aIngress = aIngress + RotL64(aOrbiterC, 41U);
            aIngress = TwistMix64::DiffuseB((aIngress + aScatter));
            //
            aWandererI = aWandererI ^ ((RotL64(aIngress, 11U) + RotL64(aOrbiterD, 60U)) + aOrbiterJ);
            aWandererE = aWandererE + (((RotL64(aScatter, 3U) + aOrbiterD) + RotL64(aOrbiterE, 39U)) + RotL64(aCarry, 41U));
            aWandererC = aWandererC ^ ((RotL64(aCross, 5U) + RotL64(aOrbiterD, 43U)) + aOrbiterB);
            aWandererB = aWandererB + (((RotL64(aPrevious, 47U) + aOrbiterK) + RotL64(aOrbiterI, 27U)) + aPhaseFWandererUpdateSaltE[(((31U - aIndex) + 28U)) & S_SALT1]);
            aWandererK = aWandererK ^ ((RotL64(aIngress, 27U) + RotL64(aOrbiterI, 52U)) + aOrbiterA);
            aWandererH = aWandererH + ((RotL64(aCross, 18U) + aOrbiterG) + RotL64(aOrbiterK, 13U));
            aWandererG = aWandererG ^ (((RotL64(aPrevious, 35U) + RotL64(aOrbiterK, 3U)) + aOrbiterD) + aPhaseFWandererUpdateSaltD[((aIndex + 26U)) & S_SALT1]);
            aWandererJ = aWandererJ + ((RotL64(aScatter, 37U) + RotL64(aOrbiterI, 41U)) + aOrbiterF);
            aWandererA = aWandererA ^ ((RotL64(aPrevious, 39U) + RotL64(aOrbiterB, 23U)) + aOrbiterC);
            aWandererD = aWandererD + (((RotL64(aIngress, 54U) + aOrbiterH) + RotL64(aOrbiterB, 57U)) + RotL64(aCarry, 23U));
            aWandererF = aWandererF ^ ((RotL64(aCross, 29U) + RotL64(aOrbiterH, 11U)) + aOrbiterF);
            //
            aCarry = aCarry + (RotL64(aWandererD, 13U) ^ aWandererG);
            aCarry = aCarry + (aWandererK ^ RotL64(aWandererE, 52U));
            aCarry = aCarry + (aWandererI ^ RotL64(aWandererA, 41U));
            aCarry = aCarry + (aWandererJ ^ RotL64(aWandererC, 5U));
            aCarry = aCarry + (aWandererH ^ RotL64(aWandererB, 19U));
            aCarry = aCarry + RotL64(aWandererF, 50U);
            aCarry = aCarry + RotL64(aIngress, 43U);
            aCarry = TwistMix64::DiffuseC(aCarry);
            //
            aWorkLaneA[aIndex] = aIngress;
        }
    
        // twist_loop_c loop 4
        // ingress from: aWorkLaneA, aSnowLaneA, aExpandLaneA
        // ingress directions: aWorkLaneA forward forced, aSnowLaneA forward forced, aExpandLaneA forward/backward random
        // cross from: aSnowLaneB, aOperationLaneD
        // cross directions: aSnowLaneB backward forced, aOperationLaneD backward/forward random
        // write to: aWorkLaneB
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aWorkLaneA[((aIndex + 19841U)) & S_BLOCK1], 35U) ^ RotL64(aSnowLaneA[((aIndex + 20381U)) & S_BLOCK1], 5U));
            aIngress ^= RotL64(aExpandLaneA[((S_BLOCK1 - aIndex + 21710U)) & S_BLOCK1], 50U);
            aIngress = TwistMix64::DiffuseB(aIngress);
            //
            aCross = RotL64(aSnowLaneB[((S_BLOCK1 - aIndex + 17220U)) & S_BLOCK1], 60U) ^ RotL64(aOperationLaneD[((aIndex + 17776U)) & S_BLOCK1], 41U);
            aCross = TwistMix64::DiffuseA(aCross);
            //
            aScatter = (RotL64(aCarry, 3U) ^ RotL64(aIngress, 18U)) + (RotL64(aPrevious, 51U) + RotL64(aCross, 39U));
            aScatter = TwistMix64::DiffuseB(aScatter);
            //
            aOrbiterH = ((aWandererC + RotL64(aIngress, 58U)) + RotL64(aCarry, 23U)) + 14686411261024919129U;
            aOrbiterK = (aWandererH + RotL64(aScatter, 37U)) + 7514582233957632005U;
            aOrbiterA = (aWandererB + RotL64(aCross, 5U)) + 6520710480103365552U;
            aOrbiterD = (((aWandererE + RotL64(aPrevious, 51U)) + RotL64(aCarry, 3U)) + 1983621978676188036U) + aPhaseFOrbiterAssignSaltC[(((31U - aIndex) + 6U)) & S_SALT1];
            aOrbiterC = ((aWandererD + RotL64(aScatter, 35U)) + RotL64(aCarry, 51U)) + 9003524602590749672U;
            aOrbiterE = (aWandererJ + RotL64(aPrevious, 47U)) + 6428568234045228995U;
            aOrbiterB = (aWandererI + RotL64(aIngress, 43U)) + 8656552687136446989U;
            aOrbiterF = ((aWandererG + RotL64(aCross, 19U)) + 16916248288415922490U) + aPhaseFOrbiterAssignSaltE[(((31U - aIndex) + 5U)) & S_SALT1];
            aOrbiterJ = (aWandererF + RotL64(aScatter, 53U)) + 9740237548002535784U;
            aOrbiterI = (aWandererK + RotL64(aCross, 60U)) + 907561000814618339U;
            aOrbiterG = (aWandererA + RotL64(aPrevious, 27U)) + 4751108900841197631U;
            //
            aOrbiterH = ((aOrbiterH + aOrbiterK) + 167774899400732287U) + aPhaseFOrbiterUpdateSaltC[((aIndex + 18U)) & S_SALT1];
            aOrbiterA = (aOrbiterA ^ aOrbiterH) ^ 11907484918310854962U;
            aOrbiterA = RotL64((aOrbiterA * 7213139491146402985U), 3U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterC) + 14910318613649863924U;
            aOrbiterE = (aOrbiterE ^ aOrbiterD) ^ 14882888155751455276U;
            aOrbiterE = RotL64((aOrbiterE * 11394136445442060201U), 21U);
            //
            aOrbiterA = (aOrbiterA + aOrbiterD) + 16175942562693781908U;
            aOrbiterB = ((aOrbiterB ^ aOrbiterA) ^ 11022373758481651102U) ^ aPhaseFOrbiterUpdateSaltE[((aIndex + 27U)) & S_SALT1];
            aOrbiterB = RotL64((aOrbiterB * 6836331461393816027U), 41U);
            //
            aOrbiterC = (aOrbiterC + aOrbiterB) + 12548405399045031548U;
            aOrbiterF = (aOrbiterF ^ aOrbiterC) ^ 10850926364556828443U;
            aOrbiterF = RotL64((aOrbiterF * 16231561687709867431U), 51U);
            //
            aOrbiterJ = (aOrbiterJ + aOrbiterA) + 13391684887911141790U;
            aOrbiterC = ((aOrbiterC ^ aOrbiterJ) ^ 14648937281264822988U) ^ aPhaseFOrbiterUpdateSaltF[(((31U - aIndex) + 9U)) & S_SALT1];
            aOrbiterC = RotL64((aOrbiterC * 6533299316940026059U), 29U);
            //
            aOrbiterK = (aOrbiterK + aOrbiterJ) + 8298658887198526821U;
            aOrbiterD = (aOrbiterD ^ aOrbiterK) ^ 13822977698661348891U;
            aOrbiterD = RotL64((aOrbiterD * 17769262972278410937U), 13U);
            //
            aOrbiterI = (aOrbiterI + aOrbiterG) + 7505646847564645719U;
            aOrbiterK = (aOrbiterK ^ aOrbiterI) ^ 3238749538197209166U;
            aOrbiterK = RotL64((aOrbiterK * 15394286542600778567U), 11U);
            //
            aOrbiterF = (aOrbiterF + aOrbiterI) + 15853506915123709257U;
            aOrbiterH = (aOrbiterH ^ aOrbiterF) ^ 8426329899401071248U;
            aOrbiterH = RotL64((aOrbiterH * 1330397096577715113U), 47U);
            //
            aOrbiterB = ((aOrbiterB + aOrbiterE) + 14848635392815613098U) + aPhaseFOrbiterUpdateSaltD[(((31U - aIndex) + 24U)) & S_SALT1];
            aOrbiterI = (aOrbiterI ^ aOrbiterB) ^ 3549927798350175044U;
            aOrbiterI = RotL64((aOrbiterI * 1899044682313056949U), 19U);
            //
            aOrbiterG = (aOrbiterG + aOrbiterH) + 1798973117197750802U;
            aOrbiterJ = (aOrbiterJ ^ aOrbiterG) ^ 13056711228618953977U;
            aOrbiterJ = RotL64((aOrbiterJ * 9102877396419306689U), 5U);
            //
            aOrbiterE = (aOrbiterE + aOrbiterF) + 1395893547965799281U;
            aOrbiterG = (aOrbiterG ^ aOrbiterE) ^ 14686411261024919129U;
            aOrbiterG = RotL64((aOrbiterG * 17075377081365066067U), 39U);
            //
            aIngress = RotL64(aOrbiterE, 11U) ^ aOrbiterH;
            aIngress = aIngress + (RotL64(aOrbiterJ, 21U) ^ aOrbiterI);
            aIngress = aIngress + (RotL64(aOrbiterG, 47U) ^ aOrbiterB);
            aIngress = aIngress + (RotL64(aOrbiterF, 35U) ^ aOrbiterD);
            aIngress = aIngress + (RotL64(aOrbiterK, 44U) ^ aOrbiterA);
            aIngress = aIngress + RotL64(aOrbiterC, 41U);
            aIngress = TwistMix64::DiffuseB((aIngress + aScatter));
            //
            aWandererI = aWandererI + ((((RotL64(aScatter, 39U) + RotL64(aOrbiterG, 37U)) + aOrbiterB) + RotL64(aCarry, 39U)) + aPhaseFWandererUpdateSaltA[(((31U - aIndex) + 10U)) & S_SALT1]);
            aWandererC = aWandererC ^ (((RotL64(aIngress, 21U) + RotL64(aOrbiterI, 23U)) + aOrbiterB) + aPhaseFWandererUpdateSaltF[((aIndex + 23U)) & S_SALT1]);
            aWandererD = aWandererD + ((RotL64(aCross, 3U) + RotL64(aOrbiterF, 50U)) + aOrbiterI);
            aWandererH = aWandererH ^ ((RotL64(aPrevious, 27U) + aOrbiterH) + RotL64(aOrbiterG, 11U));
            aWandererG = aWandererG + ((RotL64(aIngress, 52U) + RotL64(aOrbiterG, 29U)) + aOrbiterJ);
            aWandererA = aWandererA ^ ((RotL64(aPrevious, 23U) + aOrbiterD) + RotL64(aOrbiterK, 47U));
            aWandererJ = aWandererJ + (((RotL64(aCross, 13U) + RotL64(aOrbiterI, 39U)) + aOrbiterD) + RotL64(aCarry, 29U));
            aWandererE = aWandererE ^ ((RotL64(aScatter, 35U) + RotL64(aOrbiterJ, 19U)) + aOrbiterA);
            aWandererK = aWandererK + ((RotL64(aCross, 37U) + aOrbiterG) + RotL64(aOrbiterC, 5U));
            aWandererF = aWandererF ^ ((RotL64(aPrevious, 43U) + RotL64(aOrbiterI, 56U)) + aOrbiterA);
            aWandererB = aWandererB + ((RotL64(aScatter, 6U) + aOrbiterA) + RotL64(aOrbiterE, 41U));
            //
            aCarry = aCarry + (RotL64(aWandererH, 23U) ^ aWandererJ);
            aCarry = aCarry + (RotL64(aWandererB, 51U) ^ aWandererF);
            aCarry = aCarry + (aWandererG ^ RotL64(aWandererA, 18U));
            aCarry = aCarry + (RotL64(aWandererI, 29U) ^ aWandererE);
            aCarry = aCarry + (RotL64(aWandererD, 21U) ^ aWandererC);
            aCarry = aCarry + RotL64(aWandererK, 27U);
            aCarry = aCarry + RotL64(aIngress, 42U);
            aCarry = TwistMix64::DiffuseA(aCarry);
            //
            aWorkLaneB[S_BLOCK1 - aIndex] = aIngress;
        }
    
        // twist_loop_c loop 5
        // ingress from: aWorkLaneB, aSnowLaneB, aInvestLaneC
        // ingress directions: aWorkLaneB forward forced, aSnowLaneB forward forced, aInvestLaneC forward/backward random
        // cross from: aWorkLaneA, aSnowLaneA
        // cross directions: aWorkLaneA backward forced, aSnowLaneA backward/forward random
        // write to: aWorkLaneC
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aWorkLaneB[((aIndex + 26631U)) & S_BLOCK1], 3U) ^ RotL64(aSnowLaneB[((aIndex + 23401U)) & S_BLOCK1], 40U));
            aIngress ^= RotL64(aInvestLaneC[((S_BLOCK1 - aIndex + 27125U)) & S_BLOCK1], 53U);
            aIngress = TwistMix64::DiffuseA(aIngress);
            //
            aCross = RotL64(aWorkLaneA[((S_BLOCK1 - aIndex + 27290U)) & S_BLOCK1], 5U) ^ RotL64(aSnowLaneA[((S_BLOCK1 - aIndex + 26177U)) & S_BLOCK1], 36U);
            aCross = TwistMix64::DiffuseC(aCross);
            //
            aScatter = (RotL64(aCross, 29U) ^ RotL64(aIngress, 60U)) ^ (RotL64(aCarry, 41U) + RotL64(aPrevious, 13U));
            aScatter = TwistMix64::DiffuseB(aScatter);
            //
            aOrbiterA = ((aWandererF + RotL64(aCross, 23U)) + 4848316479321533394U) + aPhaseFOrbiterAssignSaltF[(((31U - aIndex) + 3U)) & S_SALT1];
            aOrbiterC = (aWandererE + RotL64(aScatter, 5U)) + 6919360256662636195U;
            aOrbiterB = (aWandererI + RotL64(aIngress, 21U)) + 9897013582181108544U;
            aOrbiterF = (aWandererG + RotL64(aPrevious, 30U)) + 7319353809896158678U;
            aOrbiterG = (aWandererB + RotL64(aScatter, 27U)) + 2848175435514849859U;
            aOrbiterK = (((aWandererD + RotL64(aCross, 13U)) + RotL64(aCarry, 23U)) + 6967780718720437934U) + aPhaseFOrbiterAssignSaltA[(((31U - aIndex) + 13U)) & S_SALT1];
            aOrbiterJ = ((aWandererH + RotL64(aPrevious, 47U)) + RotL64(aCarry, 35U)) + 10143884766603388136U;
            aOrbiterH = (aWandererA + RotL64(aIngress, 41U)) + 8675965006150972051U;
            aOrbiterE = (aWandererK + RotL64(aPrevious, 60U)) + 16350117755560994281U;
            aOrbiterD = (aWandererJ + RotL64(aIngress, 43U)) + 17976597517118423760U;
            aOrbiterI = ((aWandererC + RotL64(aScatter, 57U)) + RotL64(aCarry, 39U)) + 1399631141355370237U;
            //
            aOrbiterA = (aOrbiterA + aOrbiterC) + 3590613762034716792U;
            aOrbiterB = (aOrbiterB ^ aOrbiterA) ^ 5134624314245932157U;
            aOrbiterB = RotL64((aOrbiterB * 13077589037975283371U), 43U);
            //
            aOrbiterC = ((aOrbiterC + aOrbiterF) + 10082236952942943654U) + aPhaseFOrbiterUpdateSaltD[((aIndex + 5U)) & S_SALT1];
            aOrbiterG = ((aOrbiterG ^ aOrbiterC) ^ 4015535035905433450U) ^ aPhaseFOrbiterUpdateSaltC[(((31U - aIndex) + 21U)) & S_SALT1];
            aOrbiterG = RotL64((aOrbiterG * 4961808568701908559U), 39U);
            //
            aOrbiterK = (aOrbiterK + aOrbiterJ) + 611474103801573800U;
            aOrbiterH = (aOrbiterH ^ aOrbiterK) ^ 5786708483794098001U;
            aOrbiterH = RotL64((aOrbiterH * 7694007039340089267U), 41U);
            //
            aOrbiterE = (aOrbiterE + aOrbiterK) + 5201943497363274455U;
            aOrbiterF = (aOrbiterF ^ aOrbiterE) ^ 9282160506938328489U;
            aOrbiterF = RotL64((aOrbiterF * 5368182164239021367U), 57U);
            //
            aOrbiterG = (aOrbiterG + aOrbiterD) + 4932320527498940158U;
            aOrbiterK = (aOrbiterK ^ aOrbiterG) ^ 11576526341731392916U;
            aOrbiterK = RotL64((aOrbiterK * 1712051774729439363U), 5U);
            //
            aOrbiterH = (aOrbiterH + aOrbiterI) + 10790691517638887125U;
            aOrbiterA = ((aOrbiterA ^ aOrbiterH) ^ 16280649213607464422U) ^ aPhaseFOrbiterUpdateSaltB[(((31U - aIndex) + 11U)) & S_SALT1];
            aOrbiterA = RotL64((aOrbiterA * 10756733801499471873U), 23U);
            //
            aOrbiterI = (aOrbiterI + aOrbiterE) + 9553716940667712810U;
            aOrbiterC = (aOrbiterC ^ aOrbiterI) ^ 11827518270964003341U;
            aOrbiterC = RotL64((aOrbiterC * 1322489827908132831U), 11U);
            //
            aOrbiterF = (aOrbiterF + aOrbiterH) + 16777463701235809321U;
            aOrbiterD = (aOrbiterD ^ aOrbiterF) ^ 3375489084588454149U;
            aOrbiterD = RotL64((aOrbiterD * 3335010977457647307U), 3U);
            //
            aOrbiterJ = (aOrbiterJ + aOrbiterB) + 8129898095524287632U;
            aOrbiterI = (aOrbiterI ^ aOrbiterJ) ^ 14496406641486541929U;
            aOrbiterI = RotL64((aOrbiterI * 10077246205532940301U), 21U);
            //
            aOrbiterB = (aOrbiterB + aOrbiterG) + 17968163292907132345U;
            aOrbiterE = ((aOrbiterE ^ aOrbiterB) ^ 2431407778543471402U) ^ aPhaseFOrbiterUpdateSaltE[((aIndex + 23U)) & S_SALT1];
            aOrbiterE = RotL64((aOrbiterE * 407105842057624537U), 51U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterA) + 18330313613898211889U;
            aOrbiterJ = (aOrbiterJ ^ aOrbiterD) ^ 4848316479321533394U;
            aOrbiterJ = RotL64((aOrbiterJ * 3462735144109152811U), 19U);
            //
            aIngress = RotL64(aOrbiterF, 29U) ^ aOrbiterK;
            aIngress = aIngress + (aOrbiterH ^ RotL64(aOrbiterE, 35U));
            aIngress = aIngress + (RotL64(aOrbiterA, 41U) ^ aOrbiterJ);
            aIngress = aIngress + (RotL64(aOrbiterD, 23U) ^ aOrbiterI);
            aIngress = aIngress + (RotL64(aOrbiterC, 4U) ^ aOrbiterG);
            aIngress = aIngress + RotL64(aOrbiterB, 51U);
            aIngress = TwistMix64::DiffuseB((aIngress + aScatter));
            //
            aWandererH = aWandererH + ((RotL64(aIngress, 23U) + aOrbiterB) + RotL64(aOrbiterE, 57U));
            aWandererF = aWandererF ^ ((RotL64(aPrevious, 12U) + RotL64(aOrbiterD, 18U)) + aOrbiterF);
            aWandererD = aWandererD + ((RotL64(aCross, 41U) + RotL64(aOrbiterA, 3U)) + aOrbiterG);
            aWandererI = aWandererI ^ ((RotL64(aScatter, 29U) + RotL64(aOrbiterD, 53U)) + aOrbiterG);
            aWandererJ = aWandererJ + ((((RotL64(aPrevious, 5U) + RotL64(aOrbiterI, 39U)) + aOrbiterK) + RotL64(aCarry, 3U)) + aPhaseFWandererUpdateSaltB[(((31U - aIndex) + 6U)) & S_SALT1]);
            aWandererB = aWandererB ^ ((RotL64(aIngress, 57U) + aOrbiterK) + RotL64(aOrbiterG, 48U));
            aWandererK = aWandererK + ((RotL64(aCross, 27U) + aOrbiterD) + RotL64(aOrbiterB, 43U));
            aWandererC = aWandererC ^ ((RotL64(aScatter, 43U) + aOrbiterG) + RotL64(aOrbiterI, 13U));
            aWandererG = aWandererG + ((RotL64(aCross, 48U) + aOrbiterA) + RotL64(aOrbiterH, 29U));
            aWandererE = aWandererE ^ (((RotL64(aPrevious, 3U) + aOrbiterC) + RotL64(aOrbiterK, 35U)) + aPhaseFWandererUpdateSaltC[((aIndex + 25U)) & S_SALT1]);
            aWandererA = aWandererA + (((RotL64(aIngress, 35U) + RotL64(aOrbiterG, 27U)) + aOrbiterJ) + RotL64(aCarry, 23U));
            //
            aCarry = aCarry + (aWandererB ^ RotL64(aWandererJ, 60U));
            aCarry = aCarry + (RotL64(aWandererF, 19U) ^ aWandererC);
            aCarry = aCarry + (aWandererK ^ RotL64(aWandererA, 5U));
            aCarry = aCarry + (RotL64(aWandererH, 43U) ^ aWandererE);
            aCarry = aCarry + (aWandererI ^ RotL64(aWandererG, 41U));
            aCarry = aCarry + RotL64(aWandererD, 58U);
            aCarry = aCarry + RotL64(aIngress, 23U);
            aCarry = TwistMix64::DiffuseB(aCarry);
            //
            aWorkLaneC[aIndex] = aIngress;
        }
    
        // twist_loop_c loop 6
        // ingress from: aWorkLaneC, aWorkLaneA, aInvestLaneB
        // ingress directions: aWorkLaneC forward forced, aWorkLaneA forward forced, aInvestLaneB forward/backward random
        // cross from: aWorkLaneB, aOperationLaneB
        // cross directions: aWorkLaneB backward forced, aOperationLaneB backward/forward random
        // write to: aWorkLaneD
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aWorkLaneC[((aIndex + 32341U)) & S_BLOCK1], 3U) ^ RotL64(aWorkLaneA[((aIndex + 30845U)) & S_BLOCK1], 35U));
            aIngress ^= RotL64(aInvestLaneB[((S_BLOCK1 - aIndex + 28007U)) & S_BLOCK1], 14U);
            aIngress = TwistMix64::DiffuseB(aIngress);
            //
            aCross = RotL64(aWorkLaneB[((S_BLOCK1 - aIndex + 31226U)) & S_BLOCK1], 42U) ^ RotL64(aOperationLaneB[((S_BLOCK1 - aIndex + 32414U)) & S_BLOCK1], 53U);
            aCross = TwistMix64::DiffuseB(aCross);
            //
            aScatter = (RotL64(aCross, 34U) + RotL64(aPrevious, 51U)) + (RotL64(aIngress, 21U) ^ RotL64(aCarry, 5U));
            aScatter = TwistMix64::DiffuseB(aScatter);
            //
            aOrbiterD = (aWandererB + RotL64(aPrevious, 46U)) + 5173905450211892891U;
            aOrbiterG = (aWandererG + RotL64(aScatter, 11U)) + 3555542451908039957U;
            aOrbiterA = (aWandererF + RotL64(aIngress, 5U)) + 11559884700283861559U;
            aOrbiterI = ((aWandererI + RotL64(aCross, 35U)) + 1352524329968738673U) + aPhaseFOrbiterAssignSaltB[(((31U - aIndex) + 23U)) & S_SALT1];
            aOrbiterJ = (aWandererC + RotL64(aIngress, 19U)) + 8914206450420616349U;
            aOrbiterF = ((aWandererA + RotL64(aPrevious, 53U)) + RotL64(aCarry, 29U)) + 2251523378498463946U;
            aOrbiterC = ((aWandererE + RotL64(aScatter, 27U)) + RotL64(aCarry, 11U)) + 9541575923299247038U;
            aOrbiterK = ((aWandererK + RotL64(aCross, 43U)) + RotL64(aCarry, 23U)) + 1239854507907214595U;
            aOrbiterB = (aWandererD + RotL64(aScatter, 37U)) + 17698101462598498934U;
            aOrbiterH = (aWandererH + RotL64(aIngress, 41U)) + 12305566971683256060U;
            aOrbiterE = ((aWandererJ + RotL64(aCross, 48U)) + 13804545036303215569U) + aPhaseFOrbiterAssignSaltD[(((31U - aIndex) + 25U)) & S_SALT1];
            //
            aOrbiterD = (aOrbiterD + aOrbiterG) + 10239749097704329264U;
            aOrbiterA = (aOrbiterA ^ aOrbiterD) ^ 4212214906286320308U;
            aOrbiterA = RotL64((aOrbiterA * 3661436621615751071U), 5U);
            //
            aOrbiterI = (aOrbiterI + aOrbiterJ) + 12192418916967430783U;
            aOrbiterG = (aOrbiterG ^ aOrbiterI) ^ 4475514289326450361U;
            aOrbiterG = RotL64((aOrbiterG * 17497164630368757887U), 13U);
            //
            aOrbiterA = (aOrbiterA + aOrbiterF) + 17376102613298827459U;
            aOrbiterC = (aOrbiterC ^ aOrbiterA) ^ 18129393209955439341U;
            aOrbiterC = RotL64((aOrbiterC * 6404089025014118979U), 29U);
            //
            aOrbiterC = ((aOrbiterC + aOrbiterK) + 4014763724300253568U) + aPhaseFOrbiterUpdateSaltE[((aIndex + 7U)) & S_SALT1];
            aOrbiterI = (aOrbiterI ^ aOrbiterC) ^ 17325007199676828814U;
            aOrbiterI = RotL64((aOrbiterI * 1420888274815627083U), 53U);
            //
            aOrbiterG = (aOrbiterG + aOrbiterB) + 15480474849292388685U;
            aOrbiterF = (aOrbiterF ^ aOrbiterG) ^ 14357924730184375449U;
            aOrbiterF = RotL64((aOrbiterF * 16723492259068034209U), 37U);
            //
            aOrbiterH = ((aOrbiterH + aOrbiterI) + 4335731868597970070U) + aPhaseFOrbiterUpdateSaltD[(((31U - aIndex) + 19U)) & S_SALT1];
            aOrbiterD = ((aOrbiterD ^ aOrbiterH) ^ 8296023680394303015U) ^ aPhaseFOrbiterUpdateSaltA[(((31U - aIndex) + 13U)) & S_SALT1];
            aOrbiterD = RotL64((aOrbiterD * 14027415401430120543U), 51U);
            //
            aOrbiterK = (aOrbiterK + aOrbiterH) + 2807312426993262800U;
            aOrbiterJ = (aOrbiterJ ^ aOrbiterK) ^ 15510369660839648501U;
            aOrbiterJ = RotL64((aOrbiterJ * 18207954408298333959U), 41U);
            //
            aOrbiterF = (aOrbiterF + aOrbiterE) + 12597844696606519907U;
            aOrbiterK = (aOrbiterK ^ aOrbiterF) ^ 7231012798553551535U;
            aOrbiterK = RotL64((aOrbiterK * 2841306785994479299U), 23U);
            //
            aOrbiterE = (aOrbiterE + aOrbiterC) + 849663631945232360U;
            aOrbiterH = (aOrbiterH ^ aOrbiterE) ^ 4002310581470781194U;
            aOrbiterH = RotL64((aOrbiterH * 2148877014350721479U), 19U);
            //
            aOrbiterB = (aOrbiterB + aOrbiterA) + 16067735571435654555U;
            aOrbiterE = (aOrbiterE ^ aOrbiterB) ^ 4607980694199923842U;
            aOrbiterE = RotL64((aOrbiterE * 10401780756830017477U), 11U);
            //
            aOrbiterJ = (aOrbiterJ + aOrbiterD) + 5346879191913449715U;
            aOrbiterB = ((aOrbiterB ^ aOrbiterJ) ^ 5173905450211892891U) ^ aPhaseFOrbiterUpdateSaltB[(((31U - aIndex) + 10U)) & S_SALT1];
            aOrbiterB = RotL64((aOrbiterB * 15360571827429301833U), 21U);
            //
            aIngress = aOrbiterF ^ RotL64(aOrbiterG, 51U);
            aIngress = aIngress + (RotL64(aOrbiterD, 3U) ^ aOrbiterH);
            aIngress = aIngress + (RotL64(aOrbiterB, 42U) ^ aOrbiterJ);
            aIngress = aIngress + (RotL64(aOrbiterI, 11U) ^ aOrbiterA);
            aIngress = aIngress + (RotL64(aOrbiterE, 57U) ^ aOrbiterK);
            aIngress = aIngress + RotL64(aOrbiterC, 5U);
            aIngress = TwistMix64::DiffuseA((aIngress + aScatter));
            //
            aWandererA = aWandererA ^ (((RotL64(aIngress, 19U) + aOrbiterA) + RotL64(aOrbiterF, 27U)) + aPhaseFWandererUpdateSaltD[((aIndex + 24U)) & S_SALT1]);
            aWandererD = aWandererD + (((RotL64(aScatter, 24U) + RotL64(aOrbiterJ, 21U)) + aOrbiterK) + RotL64(aCarry, 3U));
            aWandererE = aWandererE ^ ((RotL64(aPrevious, 29U) + RotL64(aOrbiterE, 46U)) + aOrbiterF);
            aWandererK = aWandererK + (((RotL64(aCross, 27U) + aOrbiterC) + RotL64(aOrbiterJ, 35U)) + RotL64(aCarry, 47U));
            aWandererI = aWandererI ^ ((RotL64(aScatter, 5U) + aOrbiterA) + RotL64(aOrbiterH, 53U));
            aWandererH = aWandererH + ((RotL64(aCross, 21U) + aOrbiterI) + RotL64(aOrbiterE, 11U));
            aWandererC = aWandererC ^ (((RotL64(aIngress, 39U) + aOrbiterB) + RotL64(aOrbiterK, 41U)) + aPhaseFWandererUpdateSaltE[((aIndex + 21U)) & S_SALT1]);
            aWandererF = aWandererF + ((RotL64(aPrevious, 60U) + aOrbiterH) + RotL64(aOrbiterD, 13U));
            aWandererJ = aWandererJ ^ ((RotL64(aIngress, 13U) + aOrbiterG) + RotL64(aOrbiterK, 38U));
            aWandererB = aWandererB + ((RotL64(aCross, 37U) + RotL64(aOrbiterK, 19U)) + aOrbiterA);
            aWandererG = aWandererG ^ ((RotL64(aPrevious, 47U) + RotL64(aOrbiterF, 51U)) + aOrbiterD);
            //
            aCarry = aCarry + (aWandererK ^ RotL64(aWandererG, 23U));
            aCarry = aCarry + (aWandererJ ^ RotL64(aWandererB, 37U));
            aCarry = aCarry + (RotL64(aWandererE, 50U) ^ aWandererF);
            aCarry = aCarry + (RotL64(aWandererD, 35U) ^ aWandererI);
            aCarry = aCarry + (aWandererC ^ RotL64(aWandererA, 47U));
            aCarry = aCarry + RotL64(aWandererH, 29U);
            aCarry = aCarry + RotL64(aIngress, 19U);
            aCarry = TwistMix64::DiffuseC(aCarry);
            //
            aWorkLaneD[S_BLOCK1 - aIndex] = aIngress;
        }
    }
    // GTwistRunTwist_C twist_loop_c (end)
    *pPrevious = aPrevious;
    *pIngress = aIngress;
    *pCarry = aCarry;
    *pWandererA = aWandererA;
    *pWandererB = aWandererB;
    *pWandererC = aWandererC;
    *pWandererD = aWandererD;
    *pWandererE = aWandererE;
    *pWandererF = aWandererF;
    *pWandererG = aWandererG;
    *pWandererH = aWandererH;
    *pWandererI = aWandererI;
    *pWandererJ = aWandererJ;
    *pWandererK = aWandererK;
}

void TwistExpander_Exercea_Arx::GROW_A(TwistWorkSpace *pWorkSpace,
                     std::uint64_t *pPrevious,
                     std::uint64_t *pIngress,
                     std::uint64_t *pCarry,
                     std::uint64_t *pWandererA,
                     std::uint64_t *pWandererB,
                     std::uint64_t *pWandererC,
                     std::uint64_t *pWandererD,
                     std::uint64_t *pWandererE,
                     std::uint64_t *pWandererF,
                     std::uint64_t *pWandererG,
                     std::uint64_t *pWandererH,
                     std::uint64_t *pWandererI,
                     std::uint64_t *pWandererJ,
                     std::uint64_t *pWandererK) {
    [[maybe_unused]] std::uint8_t *aExpandLaneA = pWorkSpace->mExpansionLaneA;
    [[maybe_unused]] std::uint8_t *aExpandLaneB = pWorkSpace->mExpansionLaneB;
    [[maybe_unused]] std::uint8_t *aExpandLaneC = pWorkSpace->mExpansionLaneC;
    [[maybe_unused]] std::uint8_t *aExpandLaneD = pWorkSpace->mExpansionLaneD;
    [[maybe_unused]] std::uint8_t *aWorkLaneA = pWorkSpace->mWorkLaneA;
    [[maybe_unused]] std::uint8_t *aWorkLaneB = pWorkSpace->mWorkLaneB;
    [[maybe_unused]] std::uint8_t *aWorkLaneC = pWorkSpace->mWorkLaneC;
    [[maybe_unused]] std::uint8_t *aWorkLaneD = pWorkSpace->mWorkLaneD;
    [[maybe_unused]] std::uint8_t *aOperationLaneA = pWorkSpace->mOperationLaneA;
    [[maybe_unused]] std::uint8_t *aOperationLaneB = pWorkSpace->mOperationLaneB;
    [[maybe_unused]] std::uint8_t *aOperationLaneC = pWorkSpace->mOperationLaneC;
    [[maybe_unused]] std::uint8_t *aOperationLaneD = pWorkSpace->mOperationLaneD;
    [[maybe_unused]] std::uint8_t *aInvestLaneA = pWorkSpace->mInvestLaneA;
    [[maybe_unused]] std::uint8_t *aInvestLaneB = pWorkSpace->mInvestLaneB;
    [[maybe_unused]] std::uint8_t *aInvestLaneC = pWorkSpace->mInvestLaneC;
    [[maybe_unused]] std::uint8_t *aInvestLaneD = pWorkSpace->mInvestLaneD;
    [[maybe_unused]] std::uint64_t *aPhaseGOrbiterAssignSaltA = pWorkSpace->mDomainBundle.mPhaseGSalts.mOrbiterAssign.mSaltA;
    [[maybe_unused]] std::uint64_t *aPhaseGOrbiterAssignSaltB = pWorkSpace->mDomainBundle.mPhaseGSalts.mOrbiterAssign.mSaltB;
    [[maybe_unused]] std::uint64_t *aPhaseGOrbiterAssignSaltC = pWorkSpace->mDomainBundle.mPhaseGSalts.mOrbiterAssign.mSaltC;
    [[maybe_unused]] std::uint64_t *aPhaseGOrbiterAssignSaltD = pWorkSpace->mDomainBundle.mPhaseGSalts.mOrbiterAssign.mSaltD;
    [[maybe_unused]] std::uint64_t *aPhaseGOrbiterAssignSaltE = pWorkSpace->mDomainBundle.mPhaseGSalts.mOrbiterAssign.mSaltE;
    [[maybe_unused]] std::uint64_t *aPhaseGOrbiterAssignSaltF = pWorkSpace->mDomainBundle.mPhaseGSalts.mOrbiterAssign.mSaltF;
    [[maybe_unused]] std::uint64_t *aPhaseGOrbiterUpdateSaltA = pWorkSpace->mDomainBundle.mPhaseGSalts.mOrbiterUpdate.mSaltA;
    [[maybe_unused]] std::uint64_t *aPhaseGOrbiterUpdateSaltB = pWorkSpace->mDomainBundle.mPhaseGSalts.mOrbiterUpdate.mSaltB;
    [[maybe_unused]] std::uint64_t *aPhaseGOrbiterUpdateSaltC = pWorkSpace->mDomainBundle.mPhaseGSalts.mOrbiterUpdate.mSaltC;
    [[maybe_unused]] std::uint64_t *aPhaseGOrbiterUpdateSaltD = pWorkSpace->mDomainBundle.mPhaseGSalts.mOrbiterUpdate.mSaltD;
    [[maybe_unused]] std::uint64_t *aPhaseGOrbiterUpdateSaltE = pWorkSpace->mDomainBundle.mPhaseGSalts.mOrbiterUpdate.mSaltE;
    [[maybe_unused]] std::uint64_t *aPhaseGOrbiterUpdateSaltF = pWorkSpace->mDomainBundle.mPhaseGSalts.mOrbiterUpdate.mSaltF;
    [[maybe_unused]] std::uint64_t *aPhaseGWandererUpdateSaltA = pWorkSpace->mDomainBundle.mPhaseGSalts.mWandererUpdate.mSaltA;
    [[maybe_unused]] std::uint64_t *aPhaseGWandererUpdateSaltB = pWorkSpace->mDomainBundle.mPhaseGSalts.mWandererUpdate.mSaltB;
    [[maybe_unused]] std::uint64_t *aPhaseGWandererUpdateSaltC = pWorkSpace->mDomainBundle.mPhaseGSalts.mWandererUpdate.mSaltC;
    [[maybe_unused]] std::uint64_t *aPhaseGWandererUpdateSaltD = pWorkSpace->mDomainBundle.mPhaseGSalts.mWandererUpdate.mSaltD;
    [[maybe_unused]] std::uint64_t *aPhaseGWandererUpdateSaltE = pWorkSpace->mDomainBundle.mPhaseGSalts.mWandererUpdate.mSaltE;
    [[maybe_unused]] std::uint64_t *aPhaseGWandererUpdateSaltF = pWorkSpace->mDomainBundle.mPhaseGSalts.mWandererUpdate.mSaltF;
    std::uint64_t aCross = 0; std::uint64_t aScatter = 0;

    std::uint64_t aOrbiterB = 0; std::uint64_t aOrbiterC = 0; std::uint64_t aOrbiterD = 0; std::uint64_t aOrbiterE = 0;
    std::uint64_t aOrbiterG = 0; std::uint64_t aOrbiterH = 0; std::uint64_t aOrbiterI = 0; std::uint64_t aOrbiterJ = 0;
    std::uint64_t aOrbiterK = 0;

    // [grow arx]
    std::uint64_t aPrevious = *pPrevious;
    std::uint64_t aIngress = *pIngress;
    std::uint64_t aCarry = *pCarry;
    std::uint64_t aWandererA = *pWandererA;
    std::uint64_t aWandererB = *pWandererB;
    std::uint64_t aWandererC = *pWandererC;
    std::uint64_t aWandererD = *pWandererD;
    std::uint64_t aWandererE = *pWandererE;
    std::uint64_t aWandererF = *pWandererF;
    std::uint64_t aWandererG = *pWandererG;
    std::uint64_t aWandererH = *pWandererH;
    std::uint64_t aWandererI = *pWandererI;
    std::uint64_t aWandererJ = *pWandererJ;
    std::uint64_t aWandererK = *pWandererK;
    // GROW_A grow_key_a (start)
    {
        // grow_key_a loop 1
        // ingress from: aWorkLaneA, aWorkLaneB, aInvestLaneA
        // ingress directions: aWorkLaneA forward forced, aWorkLaneB forward forced, aInvestLaneA forward/backward random
        // cross from: aWorkLaneC, aWorkLaneD, aOperationLaneA
        // cross directions: aWorkLaneC backward forced, aWorkLaneD backward forced, aOperationLaneA backward/forward random
        // write to: aExpandLaneA
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aWorkLaneA[((aIndex + 2736U)) & S_BLOCK1], 14U) ^ RotL64(aWorkLaneB[((aIndex + 3948U)) & S_BLOCK1], 27U));
            aIngress ^= RotL64(aInvestLaneA[((S_BLOCK1 - aIndex + 6044U)) & S_BLOCK1], 41U);
            aIngress = TwistMix64::DiffuseB(aIngress);
            //
            aCross = (RotL64(aWorkLaneC[((S_BLOCK1 - aIndex + 2692U)) & S_BLOCK1], 23U) ^ RotL64(aWorkLaneD[((S_BLOCK1 - aIndex + 4039U)) & S_BLOCK1], 60U));
            aCross ^= RotL64(aOperationLaneA[((aIndex + 3035U)) & S_BLOCK1], 41U);
            aCross = TwistMix64::DiffuseA(aCross);
            //
            aScatter = (RotL64(aIngress, 57U) ^ RotL64(aCross, 5U)) ^ (RotL64(aPrevious, 26U) + RotL64(aCarry, 43U));
            aScatter = TwistMix64::DiffuseC(aScatter);
            //
            aOrbiterE = (aWandererH + RotL64(aScatter, 4U)) + 16124889768301047791U;
            aOrbiterI = (((aWandererJ + RotL64(aPrevious, 29U)) + RotL64(aCarry, 23U)) + 11912338587186717280U) + aPhaseGOrbiterAssignSaltD[(((31U - aIndex) + 3U)) & S_SALT1];
            aOrbiterD = ((aWandererI + RotL64(aIngress, 21U)) + RotL64(aCarry, 11U)) + 8594012868813114354U;
            aOrbiterG = ((aWandererD + RotL64(aCross, 47U)) + RotL64(aCarry, 39U)) + 18281043566156682815U;
            aOrbiterB = ((aWandererB + RotL64(aScatter, 37U)) + 16853106130200942302U) + aPhaseGOrbiterAssignSaltF[(((31U - aIndex) + 7U)) & S_SALT1];
            //
            aOrbiterE = (aOrbiterE + aOrbiterI) + 2611212958619673086U;
            aOrbiterD = (aOrbiterD ^ aOrbiterE) ^ 18039472325066855180U;
            aOrbiterD = RotL64((aOrbiterD * 10213999643376367785U), 29U);
            //
            aOrbiterG = (aOrbiterG + aOrbiterB) + 14495785571345122046U;
            aOrbiterE = ((aOrbiterE ^ aOrbiterG) ^ 4556063793412832418U) ^ aPhaseGOrbiterUpdateSaltF[((aIndex + 19U)) & S_SALT1];
            aOrbiterE = RotL64((aOrbiterE * 13166927543135467627U), 13U);
            //
            aOrbiterB = ((aOrbiterB + aOrbiterE) + 14896419970271244358U) + aPhaseGOrbiterUpdateSaltC[((aIndex + 28U)) & S_SALT1];
            aOrbiterI = (aOrbiterI ^ aOrbiterB) ^ 880028529183500036U;
            aOrbiterI = RotL64((aOrbiterI * 14228281807461251361U), 5U);
            //
            aOrbiterD = ((aOrbiterD + aOrbiterG) + 2379557167489415783U) + aPhaseGOrbiterUpdateSaltD[((aIndex + 14U)) & S_SALT1];
            aOrbiterB = ((aOrbiterB ^ aOrbiterD) ^ 11854373946064529806U) ^ aPhaseGOrbiterUpdateSaltA[(((31U - aIndex) + 25U)) & S_SALT1];
            aOrbiterB = RotL64((aOrbiterB * 150755294320438887U), 51U);
            //
            aOrbiterI = (aOrbiterI + aOrbiterD) + 1487252775956449964U;
            aOrbiterG = (aOrbiterG ^ aOrbiterI) ^ 12777924204511625545U;
            aOrbiterG = RotL64((aOrbiterG * 1366019527386994789U), 39U);
            //
            aIngress = aOrbiterG ^ RotL64(aOrbiterE, 3U);
            aIngress = aIngress + (aOrbiterB ^ RotL64(aOrbiterI, 54U));
            aIngress = aIngress + RotL64(aOrbiterD, 13U);
            aIngress = TwistMix64::DiffuseC((aIngress + aScatter));
            //
            aWandererD = aWandererD + ((((RotL64(aCross, 57U) + RotL64(aOrbiterB, 23U)) + aOrbiterD) + RotL64(aCarry, 13U)) + aPhaseGWandererUpdateSaltB[((aIndex + 24U)) & S_SALT1]);
            aWandererB = aWandererB ^ ((RotL64(aPrevious, 19U) + aOrbiterD) + RotL64(aOrbiterE, 14U));
            aWandererI = aWandererI + (((RotL64(aScatter, 5U) + aOrbiterI) + RotL64(aOrbiterG, 53U)) + RotL64(aCarry, 43U));
            aWandererH = aWandererH ^ ((RotL64(aIngress, 47U) + aOrbiterD) + RotL64(aOrbiterI, 5U));
            aWandererJ = aWandererJ + (((RotL64(aScatter, 30U) + RotL64(aOrbiterE, 43U)) + aOrbiterG) + aPhaseGWandererUpdateSaltC[((aIndex + 23U)) & S_SALT1]);
            //
            aCarry = aCarry + (RotL64(aWandererJ, 21U) ^ aWandererB);
            aCarry = aCarry + (RotL64(aWandererD, 3U) ^ aWandererI);
            aCarry = aCarry + RotL64(aWandererH, 11U);
            aCarry = aCarry + RotL64(aIngress, 39U);
            aCarry = TwistMix64::DiffuseB(aCarry);
            //
            aExpandLaneA[aIndex] = aIngress;
        }
    
        // grow_key_a loop 2
        // ingress from: aExpandLaneA, aWorkLaneC, aInvestLaneB
        // ingress directions: aExpandLaneA forward forced, aWorkLaneC forward forced, aInvestLaneB forward/backward random
        // cross from: aWorkLaneA, aWorkLaneD, aOperationLaneB
        // cross directions: aWorkLaneA backward forced, aWorkLaneD backward forced, aOperationLaneB backward/forward random
        // write to: aExpandLaneB
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aExpandLaneA[((aIndex + 15789U)) & S_BLOCK1], 5U) ^ RotL64(aWorkLaneC[((aIndex + 12317U)) & S_BLOCK1], 19U));
            aIngress ^= RotL64(aInvestLaneB[((S_BLOCK1 - aIndex + 16217U)) & S_BLOCK1], 42U);
            aIngress = TwistMix64::DiffuseC(aIngress);
            //
            aCross = (RotL64(aWorkLaneA[((S_BLOCK1 - aIndex + 14652U)) & S_BLOCK1], 11U) ^ RotL64(aWorkLaneD[((S_BLOCK1 - aIndex + 8594U)) & S_BLOCK1], 24U));
            aCross ^= RotL64(aOperationLaneB[((S_BLOCK1 - aIndex + 10636U)) & S_BLOCK1], 35U);
            aCross = TwistMix64::DiffuseA(aCross);
            //
            aScatter = (RotL64(aIngress, 22U) + RotL64(aCarry, 43U)) ^ (RotL64(aCross, 57U) ^ RotL64(aPrevious, 5U));
            aScatter = TwistMix64::DiffuseA(aScatter);
            //
            aOrbiterH = ((aWandererD + RotL64(aIngress, 13U)) + RotL64(aCarry, 43U)) + 380024772508948442U;
            aOrbiterC = ((aWandererG + RotL64(aPrevious, 39U)) + 7649029098162567210U) + aPhaseGOrbiterAssignSaltA[((aIndex + 28U)) & S_SALT1];
            aOrbiterB = (((aWandererF + RotL64(aScatter, 53U)) + RotL64(aCarry, 13U)) + 5329304598870421851U) + aPhaseGOrbiterAssignSaltC[((aIndex + 11U)) & S_SALT1];
            aOrbiterG = (aWandererJ + RotL64(aCross, 3U)) + 12306118665045151326U;
            aOrbiterI = ((aWandererC + RotL64(aPrevious, 22U)) + RotL64(aCarry, 57U)) + 960751560457324256U;
            //
            aOrbiterH = (aOrbiterH + aOrbiterC) + 3244070254386191876U;
            aOrbiterB = ((aOrbiterB ^ aOrbiterH) ^ 15733408571609521746U) ^ aPhaseGOrbiterUpdateSaltB[((aIndex + 29U)) & S_SALT1];
            aOrbiterB = RotL64((aOrbiterB * 11280008313548121407U), 21U);
            //
            aOrbiterG = ((aOrbiterG + aOrbiterB) + 17623448932647018544U) + aPhaseGOrbiterUpdateSaltD[((aIndex + 3U)) & S_SALT1];
            aOrbiterH = (aOrbiterH ^ aOrbiterG) ^ 8787759896149035829U;
            aOrbiterH = RotL64((aOrbiterH * 7092515868845497573U), 5U);
            //
            aOrbiterB = ((aOrbiterB + aOrbiterI) + 14741681792348288162U) + aPhaseGOrbiterUpdateSaltE[((aIndex + 8U)) & S_SALT1];
            aOrbiterC = ((aOrbiterC ^ aOrbiterB) ^ 8801731213568307302U) ^ aPhaseGOrbiterUpdateSaltF[((aIndex + 5U)) & S_SALT1];
            aOrbiterC = RotL64((aOrbiterC * 12127126999570616489U), 47U);
            //
            aOrbiterC = (aOrbiterC + aOrbiterG) + 9872248187499779222U;
            aOrbiterI = (aOrbiterI ^ aOrbiterC) ^ 15407371518644528235U;
            aOrbiterI = RotL64((aOrbiterI * 1245102406469471673U), 57U);
            //
            aOrbiterI = (aOrbiterI + aOrbiterH) + 4242060317152943062U;
            aOrbiterG = (aOrbiterG ^ aOrbiterI) ^ 9942784962409917541U;
            aOrbiterG = RotL64((aOrbiterG * 888649755587764533U), 13U);
            //
            aIngress = RotL64(aOrbiterI, 58U) ^ aOrbiterH;
            aIngress = aIngress + (aOrbiterC ^ RotL64(aOrbiterG, 5U));
            aIngress = aIngress + RotL64(aOrbiterB, 29U);
            aIngress = TwistMix64::DiffuseA((aIngress + aScatter));
            //
            aWandererC = aWandererC ^ ((RotL64(aScatter, 3U) + RotL64(aOrbiterB, 3U)) + aOrbiterI);
            aWandererJ = aWandererJ + (((RotL64(aCross, 13U) + RotL64(aOrbiterC, 53U)) + aOrbiterH) + RotL64(aCarry, 5U));
            aWandererG = aWandererG ^ (((RotL64(aIngress, 36U) + aOrbiterG) + RotL64(aOrbiterH, 29U)) + aPhaseGWandererUpdateSaltD[(((31U - aIndex) + 14U)) & S_SALT1]);
            aWandererF = aWandererF + ((((RotL64(aPrevious, 27U) + aOrbiterG) + RotL64(aOrbiterB, 20U)) + RotL64(aCarry, 21U)) + aPhaseGWandererUpdateSaltF[((aIndex + 25U)) & S_SALT1]);
            aWandererD = aWandererD ^ ((RotL64(aCross, 57U) + aOrbiterG) + RotL64(aOrbiterC, 41U));
            //
            aCarry = aCarry + (aWandererG ^ RotL64(aWandererD, 11U));
            aCarry = aCarry + (aWandererJ ^ RotL64(aWandererF, 43U));
            aCarry = aCarry + RotL64(aWandererC, 3U);
            aCarry = aCarry + RotL64(aIngress, 52U);
            aCarry = TwistMix64::DiffuseA(aCarry);
            //
            aExpandLaneB[S_BLOCK1 - aIndex] = aIngress;
        }
    
        // grow_key_a loop 3
        // ingress from: aExpandLaneB, aWorkLaneD, aInvestLaneC
        // ingress directions: aExpandLaneB forward forced, aWorkLaneD forward forced, aInvestLaneC forward/backward random
        // cross from: aExpandLaneA, aWorkLaneB, aOperationLaneC
        // cross directions: aExpandLaneA backward forced, aWorkLaneB backward forced, aOperationLaneC backward/forward random
        // write to: aExpandLaneC
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aExpandLaneB[((aIndex + 23924U)) & S_BLOCK1], 47U) ^ RotL64(aWorkLaneD[((aIndex + 20926U)) & S_BLOCK1], 26U));
            aIngress ^= RotL64(aInvestLaneC[((aIndex + 24215U)) & S_BLOCK1], 11U);
            aIngress = TwistMix64::DiffuseC(aIngress);
            //
            aCross = (RotL64(aExpandLaneA[((S_BLOCK1 - aIndex + 18180U)) & S_BLOCK1], 44U) ^ RotL64(aWorkLaneB[((S_BLOCK1 - aIndex + 16981U)) & S_BLOCK1], 57U));
            aCross ^= RotL64(aOperationLaneC[((aIndex + 17941U)) & S_BLOCK1], 19U);
            aCross = TwistMix64::DiffuseC(aCross);
            //
            aScatter = (RotL64(aIngress, 19U) + RotL64(aCarry, 34U)) ^ (RotL64(aPrevious, 53U) + RotL64(aCross, 5U));
            aScatter = TwistMix64::DiffuseB(aScatter);
            //
            aOrbiterG = ((aWandererD + RotL64(aCross, 11U)) + 8988572360732005217U) + aPhaseGOrbiterAssignSaltB[(((31U - aIndex) + 29U)) & S_SALT1];
            aOrbiterJ = ((aWandererB + RotL64(aScatter, 47U)) + RotL64(aCarry, 19U)) + 17889613225105985335U;
            aOrbiterC = ((aWandererK + RotL64(aIngress, 30U)) + RotL64(aCarry, 41U)) + 15563478320513948626U;
            aOrbiterK = ((aWandererG + RotL64(aPrevious, 57U)) + 3441351228410524816U) + aPhaseGOrbiterAssignSaltE[((aIndex + 23U)) & S_SALT1];
            aOrbiterE = ((aWandererJ + RotL64(aCross, 39U)) + RotL64(aCarry, 57U)) + 4425592689451435346U;
            //
            aOrbiterG = ((aOrbiterG + aOrbiterJ) + 12733160231627305928U) + aPhaseGOrbiterUpdateSaltA[((aIndex + 26U)) & S_SALT1];
            aOrbiterC = ((aOrbiterC ^ aOrbiterG) ^ 3574152157304607854U) ^ aPhaseGOrbiterUpdateSaltD[((aIndex + 24U)) & S_SALT1];
            aOrbiterC = RotL64((aOrbiterC * 3488682351509384035U), 13U);
            //
            aOrbiterC = (aOrbiterC + aOrbiterK) + 15167631896729808783U;
            aOrbiterE = (aOrbiterE ^ aOrbiterC) ^ 15822667973915417055U;
            aOrbiterE = RotL64((aOrbiterE * 5155661648455308057U), 21U);
            //
            aOrbiterJ = (aOrbiterJ + aOrbiterC) + 17181685481076577637U;
            aOrbiterK = (aOrbiterK ^ aOrbiterJ) ^ 9979204751408873468U;
            aOrbiterK = RotL64((aOrbiterK * 8244434774754786565U), 29U);
            //
            aOrbiterK = ((aOrbiterK + aOrbiterE) + 1334240485667164762U) + aPhaseGOrbiterUpdateSaltB[(((31U - aIndex) + 20U)) & S_SALT1];
            aOrbiterG = (aOrbiterG ^ aOrbiterK) ^ 9190066751460137016U;
            aOrbiterG = RotL64((aOrbiterG * 14585141844653660363U), 41U);
            //
            aOrbiterE = ((aOrbiterE + aOrbiterG) + 15465215829109246336U) + aPhaseGOrbiterUpdateSaltC[((aIndex + 15U)) & S_SALT1];
            aOrbiterJ = (aOrbiterJ ^ aOrbiterE) ^ 2305208282453624419U;
            aOrbiterJ = RotL64((aOrbiterJ * 10257861974108363283U), 51U);
            //
            aIngress = RotL64(aOrbiterK, 43U) ^ aOrbiterJ;
            aIngress = aIngress + (RotL64(aOrbiterC, 18U) ^ aOrbiterG);
            aIngress = aIngress + RotL64(aOrbiterE, 5U);
            aIngress = TwistMix64::DiffuseA((aIngress + aScatter));
            //
            aWandererB = aWandererB + ((RotL64(aIngress, 3U) + RotL64(aOrbiterJ, 41U)) + aOrbiterG);
            aWandererK = aWandererK ^ ((RotL64(aScatter, 13U) + aOrbiterK) + RotL64(aOrbiterE, 27U));
            aWandererD = aWandererD + ((((RotL64(aCross, 34U) + aOrbiterC) + RotL64(aOrbiterK, 13U)) + RotL64(aCarry, 11U)) + aPhaseGWandererUpdateSaltA[(((31U - aIndex) + 17U)) & S_SALT1]);
            aWandererJ = aWandererJ ^ ((RotL64(aPrevious, 21U) + aOrbiterC) + RotL64(aOrbiterE, 3U));
            aWandererG = aWandererG + ((((RotL64(aScatter, 51U) + aOrbiterC) + RotL64(aOrbiterJ, 52U)) + RotL64(aCarry, 29U)) + aPhaseGWandererUpdateSaltE[(((31U - aIndex) + 21U)) & S_SALT1]);
            //
            aCarry = aCarry + (RotL64(aWandererG, 11U) ^ aWandererD);
            aCarry = aCarry + (aWandererB ^ RotL64(aWandererJ, 39U));
            aCarry = aCarry + RotL64(aWandererK, 56U);
            aCarry = aCarry + RotL64(aIngress, 3U);
            aCarry = TwistMix64::DiffuseC(aCarry);
            //
            aExpandLaneC[aIndex] = aIngress;
        }
    
        // grow_key_a loop 4
        // ingress from: aExpandLaneC, aExpandLaneA, aInvestLaneD
        // ingress directions: aExpandLaneC forward forced, aExpandLaneA forward forced, aInvestLaneD forward/backward random
        // cross from: aExpandLaneB, aWorkLaneA, aOperationLaneD
        // cross directions: aExpandLaneB backward forced, aWorkLaneA backward forced, aOperationLaneD backward/forward random
        // write to: aExpandLaneD
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aExpandLaneC[((aIndex + 28131U)) & S_BLOCK1], 39U) ^ RotL64(aExpandLaneA[((aIndex + 31723U)) & S_BLOCK1], 26U));
            aIngress ^= RotL64(aInvestLaneD[((aIndex + 26839U)) & S_BLOCK1], 47U);
            aIngress = TwistMix64::DiffuseB(aIngress);
            //
            aCross = (RotL64(aExpandLaneB[((S_BLOCK1 - aIndex + 30559U)) & S_BLOCK1], 19U) ^ RotL64(aWorkLaneA[((S_BLOCK1 - aIndex + 28139U)) & S_BLOCK1], 11U));
            aCross ^= RotL64(aOperationLaneD[((S_BLOCK1 - aIndex + 30821U)) & S_BLOCK1], 50U);
            aCross = TwistMix64::DiffuseA(aCross);
            //
            aScatter = (RotL64(aCross, 51U) + RotL64(aPrevious, 13U)) ^ (RotL64(aCarry, 39U) + RotL64(aIngress, 26U));
            aScatter = TwistMix64::DiffuseA(aScatter);
            //
            aOrbiterG = (((aWandererK + RotL64(aCross, 5U)) + RotL64(aCarry, 51U)) + 16189787374324972735U) + aPhaseGOrbiterAssignSaltF[((aIndex + 18U)) & S_SALT1];
            aOrbiterH = (aWandererG + RotL64(aPrevious, 50U)) + 17563763730956242224U;
            aOrbiterE = ((aWandererD + RotL64(aScatter, 29U)) + RotL64(aCarry, 13U)) + 10572803498593789385U;
            aOrbiterK = ((aWandererF + RotL64(aIngress, 39U)) + 7713105232072974166U) + aPhaseGOrbiterAssignSaltD[((aIndex + 20U)) & S_SALT1];
            aOrbiterJ = ((aWandererC + RotL64(aPrevious, 21U)) + RotL64(aCarry, 39U)) + 10760839534772718139U;
            //
            aOrbiterG = ((aOrbiterG + aOrbiterH) + 13397069448391230253U) + aPhaseGOrbiterUpdateSaltE[(((31U - aIndex) + 23U)) & S_SALT1];
            aOrbiterE = ((aOrbiterE ^ aOrbiterG) ^ 4569255679998375682U) ^ aPhaseGOrbiterUpdateSaltA[(((31U - aIndex) + 29U)) & S_SALT1];
            aOrbiterE = RotL64((aOrbiterE * 15163488708398248639U), 43U);
            //
            aOrbiterE = (aOrbiterE + aOrbiterK) + 9888769350817876949U;
            aOrbiterJ = (aOrbiterJ ^ aOrbiterE) ^ 11351796060878856300U;
            aOrbiterJ = RotL64((aOrbiterJ * 13356749147334008399U), 35U);
            //
            aOrbiterJ = (aOrbiterJ + aOrbiterG) + 18153775071965707204U;
            aOrbiterH = (aOrbiterH ^ aOrbiterJ) ^ 1282846411145853435U;
            aOrbiterH = RotL64((aOrbiterH * 12294455920906257823U), 3U);
            //
            aOrbiterH = ((aOrbiterH + aOrbiterE) + 16457743979262460660U) + aPhaseGOrbiterUpdateSaltF[((aIndex + 26U)) & S_SALT1];
            aOrbiterK = (aOrbiterK ^ aOrbiterH) ^ 173493260775251032U;
            aOrbiterK = RotL64((aOrbiterK * 4935807229040883505U), 19U);
            //
            aOrbiterK = (aOrbiterK + aOrbiterJ) + 3927345926316409630U;
            aOrbiterG = ((aOrbiterG ^ aOrbiterK) ^ 5158769729850853623U) ^ aPhaseGOrbiterUpdateSaltD[((aIndex + 19U)) & S_SALT1];
            aOrbiterG = RotL64((aOrbiterG * 2446452358663812945U), 51U);
            //
            aIngress = RotL64(aOrbiterG, 47U) ^ aOrbiterK;
            aIngress = aIngress + (aOrbiterH ^ RotL64(aOrbiterJ, 37U));
            aIngress = aIngress + RotL64(aOrbiterE, 13U);
            aIngress = TwistMix64::DiffuseB((aIngress + aScatter));
            //
            aWandererF = aWandererF ^ ((RotL64(aIngress, 35U) + RotL64(aOrbiterG, 13U)) + aOrbiterJ);
            aWandererC = aWandererC + ((((RotL64(aPrevious, 57U) + aOrbiterE) + RotL64(aOrbiterH, 26U)) + RotL64(aCarry, 23U)) + aPhaseGWandererUpdateSaltC[(((31U - aIndex) + 27U)) & S_SALT1]);
            aWandererG = aWandererG ^ ((RotL64(aCross, 11U) + RotL64(aOrbiterJ, 47U)) + aOrbiterK);
            aWandererK = aWandererK + ((((RotL64(aScatter, 48U) + RotL64(aOrbiterJ, 57U)) + aOrbiterH) + RotL64(aCarry, 11U)) + aPhaseGWandererUpdateSaltB[((aIndex + 21U)) & S_SALT1]);
            aWandererD = aWandererD ^ ((RotL64(aCross, 21U) + RotL64(aOrbiterK, 5U)) + aOrbiterE);
            //
            aCarry = aCarry + (RotL64(aWandererD, 35U) ^ aWandererC);
            aCarry = aCarry + (aWandererK ^ RotL64(aWandererG, 43U));
            aCarry = aCarry + RotL64(aWandererF, 11U);
            aCarry = aCarry + RotL64(aIngress, 3U);
            aCarry = TwistMix64::DiffuseC(aCarry);
            //
            aExpandLaneD[S_BLOCK1 - aIndex] = aIngress;
        }
    }
    // GROW_A grow_key_a (end)
    *pPrevious = aPrevious;
    *pIngress = aIngress;
    *pCarry = aCarry;
    *pWandererA = aWandererA;
    *pWandererB = aWandererB;
    *pWandererC = aWandererC;
    *pWandererD = aWandererD;
    *pWandererE = aWandererE;
    *pWandererF = aWandererF;
    *pWandererG = aWandererG;
    *pWandererH = aWandererH;
    *pWandererI = aWandererI;
    *pWandererJ = aWandererJ;
    *pWandererK = aWandererK;
}

void TwistExpander_Exercea_Arx::GROW_B(TwistWorkSpace *pWorkSpace,
                     std::uint64_t *pPrevious,
                     std::uint64_t *pIngress,
                     std::uint64_t *pCarry,
                     std::uint64_t *pWandererA,
                     std::uint64_t *pWandererB,
                     std::uint64_t *pWandererC,
                     std::uint64_t *pWandererD,
                     std::uint64_t *pWandererE,
                     std::uint64_t *pWandererF,
                     std::uint64_t *pWandererG,
                     std::uint64_t *pWandererH,
                     std::uint64_t *pWandererI,
                     std::uint64_t *pWandererJ,
                     std::uint64_t *pWandererK) {
    [[maybe_unused]] std::uint8_t *aExpandLaneA = pWorkSpace->mExpansionLaneA;
    [[maybe_unused]] std::uint8_t *aExpandLaneB = pWorkSpace->mExpansionLaneB;
    [[maybe_unused]] std::uint8_t *aExpandLaneC = pWorkSpace->mExpansionLaneC;
    [[maybe_unused]] std::uint8_t *aExpandLaneD = pWorkSpace->mExpansionLaneD;
    [[maybe_unused]] std::uint8_t *aWorkLaneA = pWorkSpace->mWorkLaneA;
    [[maybe_unused]] std::uint8_t *aWorkLaneB = pWorkSpace->mWorkLaneB;
    [[maybe_unused]] std::uint8_t *aWorkLaneC = pWorkSpace->mWorkLaneC;
    [[maybe_unused]] std::uint8_t *aWorkLaneD = pWorkSpace->mWorkLaneD;
    [[maybe_unused]] std::uint8_t *aOperationLaneA = pWorkSpace->mOperationLaneA;
    [[maybe_unused]] std::uint8_t *aOperationLaneB = pWorkSpace->mOperationLaneB;
    [[maybe_unused]] std::uint8_t *aOperationLaneC = pWorkSpace->mOperationLaneC;
    [[maybe_unused]] std::uint8_t *aOperationLaneD = pWorkSpace->mOperationLaneD;
    [[maybe_unused]] std::uint8_t *aInvestLaneA = pWorkSpace->mInvestLaneA;
    [[maybe_unused]] std::uint8_t *aInvestLaneB = pWorkSpace->mInvestLaneB;
    [[maybe_unused]] std::uint8_t *aInvestLaneC = pWorkSpace->mInvestLaneC;
    [[maybe_unused]] std::uint8_t *aInvestLaneD = pWorkSpace->mInvestLaneD;
    [[maybe_unused]] std::uint64_t *aPhaseHOrbiterAssignSaltA = pWorkSpace->mDomainBundle.mPhaseHSalts.mOrbiterAssign.mSaltA;
    [[maybe_unused]] std::uint64_t *aPhaseHOrbiterAssignSaltB = pWorkSpace->mDomainBundle.mPhaseHSalts.mOrbiterAssign.mSaltB;
    [[maybe_unused]] std::uint64_t *aPhaseHOrbiterAssignSaltC = pWorkSpace->mDomainBundle.mPhaseHSalts.mOrbiterAssign.mSaltC;
    [[maybe_unused]] std::uint64_t *aPhaseHOrbiterAssignSaltD = pWorkSpace->mDomainBundle.mPhaseHSalts.mOrbiterAssign.mSaltD;
    [[maybe_unused]] std::uint64_t *aPhaseHOrbiterAssignSaltE = pWorkSpace->mDomainBundle.mPhaseHSalts.mOrbiterAssign.mSaltE;
    [[maybe_unused]] std::uint64_t *aPhaseHOrbiterAssignSaltF = pWorkSpace->mDomainBundle.mPhaseHSalts.mOrbiterAssign.mSaltF;
    [[maybe_unused]] std::uint64_t *aPhaseHOrbiterUpdateSaltA = pWorkSpace->mDomainBundle.mPhaseHSalts.mOrbiterUpdate.mSaltA;
    [[maybe_unused]] std::uint64_t *aPhaseHOrbiterUpdateSaltB = pWorkSpace->mDomainBundle.mPhaseHSalts.mOrbiterUpdate.mSaltB;
    [[maybe_unused]] std::uint64_t *aPhaseHOrbiterUpdateSaltC = pWorkSpace->mDomainBundle.mPhaseHSalts.mOrbiterUpdate.mSaltC;
    [[maybe_unused]] std::uint64_t *aPhaseHOrbiterUpdateSaltD = pWorkSpace->mDomainBundle.mPhaseHSalts.mOrbiterUpdate.mSaltD;
    [[maybe_unused]] std::uint64_t *aPhaseHOrbiterUpdateSaltE = pWorkSpace->mDomainBundle.mPhaseHSalts.mOrbiterUpdate.mSaltE;
    [[maybe_unused]] std::uint64_t *aPhaseHOrbiterUpdateSaltF = pWorkSpace->mDomainBundle.mPhaseHSalts.mOrbiterUpdate.mSaltF;
    [[maybe_unused]] std::uint64_t *aPhaseHWandererUpdateSaltA = pWorkSpace->mDomainBundle.mPhaseHSalts.mWandererUpdate.mSaltA;
    [[maybe_unused]] std::uint64_t *aPhaseHWandererUpdateSaltB = pWorkSpace->mDomainBundle.mPhaseHSalts.mWandererUpdate.mSaltB;
    [[maybe_unused]] std::uint64_t *aPhaseHWandererUpdateSaltC = pWorkSpace->mDomainBundle.mPhaseHSalts.mWandererUpdate.mSaltC;
    [[maybe_unused]] std::uint64_t *aPhaseHWandererUpdateSaltD = pWorkSpace->mDomainBundle.mPhaseHSalts.mWandererUpdate.mSaltD;
    [[maybe_unused]] std::uint64_t *aPhaseHWandererUpdateSaltE = pWorkSpace->mDomainBundle.mPhaseHSalts.mWandererUpdate.mSaltE;
    [[maybe_unused]] std::uint64_t *aPhaseHWandererUpdateSaltF = pWorkSpace->mDomainBundle.mPhaseHSalts.mWandererUpdate.mSaltF;
    std::uint64_t aCross = 0; std::uint64_t aScatter = 0;

    std::uint64_t aOrbiterA = 0; std::uint64_t aOrbiterB = 0; std::uint64_t aOrbiterD = 0; std::uint64_t aOrbiterE = 0;
    std::uint64_t aOrbiterF = 0; std::uint64_t aOrbiterH = 0; std::uint64_t aOrbiterI = 0; std::uint64_t aOrbiterJ = 0;
    std::uint64_t aOrbiterK = 0;

    // [grow arx]
    std::uint64_t aPrevious = *pPrevious;
    std::uint64_t aIngress = *pIngress;
    std::uint64_t aCarry = *pCarry;
    std::uint64_t aWandererA = *pWandererA;
    std::uint64_t aWandererB = *pWandererB;
    std::uint64_t aWandererC = *pWandererC;
    std::uint64_t aWandererD = *pWandererD;
    std::uint64_t aWandererE = *pWandererE;
    std::uint64_t aWandererF = *pWandererF;
    std::uint64_t aWandererG = *pWandererG;
    std::uint64_t aWandererH = *pWandererH;
    std::uint64_t aWandererI = *pWandererI;
    std::uint64_t aWandererJ = *pWandererJ;
    std::uint64_t aWandererK = *pWandererK;
    // GROW_B grow_key_b (start)
    {
        // grow_key_b loop 1
        // ingress from: aExpandLaneA, aExpandLaneB, aInvestLaneA
        // ingress directions: aExpandLaneA forward forced, aExpandLaneB forward forced, aInvestLaneA forward/backward random
        // cross from: aExpandLaneC, aExpandLaneD, aOperationLaneA
        // cross directions: aExpandLaneC backward forced, aExpandLaneD backward forced, aOperationLaneA backward/forward random
        // write to: aWorkLaneA
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aExpandLaneA[((aIndex + 6365U)) & S_BLOCK1], 13U) ^ RotL64(aExpandLaneB[((aIndex + 5229U)) & S_BLOCK1], 46U));
            aIngress ^= RotL64(aInvestLaneA[((S_BLOCK1 - aIndex + 7137U)) & S_BLOCK1], 27U);
            aIngress = TwistMix64::DiffuseA(aIngress);
            //
            aCross = (RotL64(aExpandLaneC[((S_BLOCK1 - aIndex + 844U)) & S_BLOCK1], 29U) ^ RotL64(aExpandLaneD[((S_BLOCK1 - aIndex + 1708U)) & S_BLOCK1], 43U));
            aCross ^= RotL64(aOperationLaneA[((S_BLOCK1 - aIndex + 7193U)) & S_BLOCK1], 10U);
            aCross = TwistMix64::DiffuseB(aCross);
            //
            aScatter = (RotL64(aIngress, 23U) ^ RotL64(aCarry, 56U)) ^ (RotL64(aCross, 35U) + RotL64(aPrevious, 11U));
            aScatter = TwistMix64::DiffuseB(aScatter);
            //
            aOrbiterB = ((aWandererF + RotL64(aPrevious, 19U)) + RotL64(aCarry, 3U)) + 16802219662864902427U;
            aOrbiterF = ((aWandererH + RotL64(aIngress, 35U)) + 14332033461409490629U) + aPhaseHOrbiterAssignSaltE[(((31U - aIndex) + 20U)) & S_SALT1];
            aOrbiterK = (aWandererA + RotL64(aCross, 46U)) + 8781794298640286845U;
            aOrbiterA = ((aWandererG + RotL64(aScatter, 5U)) + RotL64(aCarry, 47U)) + 8459933908074937264U;
            aOrbiterD = (((aWandererJ + RotL64(aIngress, 57U)) + RotL64(aCarry, 27U)) + 1883580287986004426U) + aPhaseHOrbiterAssignSaltA[((aIndex + 21U)) & S_SALT1];
            //
            aOrbiterB = (aOrbiterB + aOrbiterF) + 17500258188004626118U;
            aOrbiterK = (aOrbiterK ^ aOrbiterB) ^ 7934811305150872870U;
            aOrbiterK = RotL64((aOrbiterK * 10039004285642030761U), 35U);
            //
            aOrbiterA = (aOrbiterA + aOrbiterB) + 6380363892361098905U;
            aOrbiterF = ((aOrbiterF ^ aOrbiterA) ^ 12623079132626676910U) ^ aPhaseHOrbiterUpdateSaltE[((aIndex + 13U)) & S_SALT1];
            aOrbiterF = RotL64((aOrbiterF * 12406671746344127399U), 19U);
            //
            aOrbiterD = ((aOrbiterD + aOrbiterA) + 10455208121949202703U) + aPhaseHOrbiterUpdateSaltD[((aIndex + 4U)) & S_SALT1];
            aOrbiterB = (aOrbiterB ^ aOrbiterD) ^ 8805532707916767629U;
            aOrbiterB = RotL64((aOrbiterB * 666082374369701881U), 57U);
            //
            aOrbiterK = ((aOrbiterK + aOrbiterD) + 9161544391400377699U) + aPhaseHOrbiterUpdateSaltB[(((31U - aIndex) + 11U)) & S_SALT1];
            aOrbiterA = (aOrbiterA ^ aOrbiterK) ^ 3501434325829663268U;
            aOrbiterA = RotL64((aOrbiterA * 7933545151293799637U), 43U);
            //
            aOrbiterF = (aOrbiterF + aOrbiterK) + 651783304096081996U;
            aOrbiterD = ((aOrbiterD ^ aOrbiterF) ^ 441505031509930622U) ^ aPhaseHOrbiterUpdateSaltC[(((31U - aIndex) + 24U)) & S_SALT1];
            aOrbiterD = RotL64((aOrbiterD * 8045355432310956143U), 5U);
            //
            aIngress = RotL64(aOrbiterD, 46U) ^ aOrbiterF;
            aIngress = aIngress + (RotL64(aOrbiterK, 3U) ^ aOrbiterB);
            aIngress = aIngress + RotL64(aOrbiterA, 13U);
            aIngress = TwistMix64::DiffuseB((aIngress + aScatter));
            //
            aWandererA = aWandererA ^ (((RotL64(aPrevious, 11U) + aOrbiterB) + RotL64(aOrbiterK, 47U)) + aPhaseHWandererUpdateSaltA[((aIndex + 9U)) & S_SALT1]);
            aWandererH = aWandererH + ((((RotL64(aIngress, 20U) + aOrbiterD) + RotL64(aOrbiterF, 12U)) + RotL64(aCarry, 51U)) + aPhaseHWandererUpdateSaltF[((aIndex + 7U)) & S_SALT1]);
            aWandererG = aWandererG ^ ((RotL64(aCross, 37U) + RotL64(aOrbiterK, 27U)) + aOrbiterA);
            aWandererJ = aWandererJ + (((RotL64(aScatter, 57U) + aOrbiterD) + RotL64(aOrbiterB, 57U)) + RotL64(aCarry, 37U));
            aWandererF = aWandererF ^ ((RotL64(aPrevious, 3U) + aOrbiterK) + RotL64(aOrbiterF, 3U));
            //
            aCarry = aCarry + (aWandererA ^ RotL64(aWandererG, 3U));
            aCarry = aCarry + (aWandererH ^ RotL64(aWandererJ, 39U));
            aCarry = aCarry + RotL64(aWandererF, 11U);
            aCarry = aCarry + RotL64(aIngress, 27U);
            aCarry = TwistMix64::DiffuseC(aCarry);
            //
            aWorkLaneA[aIndex] = aIngress;
        }
    
        // grow_key_b loop 2
        // ingress from: aWorkLaneA, aExpandLaneC, aInvestLaneB
        // ingress directions: aWorkLaneA forward forced, aExpandLaneC forward forced, aInvestLaneB forward/backward random
        // cross from: aExpandLaneA, aExpandLaneD, aOperationLaneB
        // cross directions: aExpandLaneA backward forced, aExpandLaneD backward forced, aOperationLaneB backward/forward random
        // write to: aWorkLaneB
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aWorkLaneA[((aIndex + 16141U)) & S_BLOCK1], 57U) ^ RotL64(aExpandLaneC[((aIndex + 11458U)) & S_BLOCK1], 42U));
            aIngress ^= RotL64(aInvestLaneB[((S_BLOCK1 - aIndex + 13051U)) & S_BLOCK1], 19U);
            aIngress = TwistMix64::DiffuseB(aIngress);
            //
            aCross = (RotL64(aExpandLaneA[((S_BLOCK1 - aIndex + 12145U)) & S_BLOCK1], 11U) ^ RotL64(aExpandLaneD[((S_BLOCK1 - aIndex + 13381U)) & S_BLOCK1], 30U));
            aCross ^= RotL64(aOperationLaneB[((aIndex + 12386U)) & S_BLOCK1], 51U);
            aCross = TwistMix64::DiffuseC(aCross);
            //
            aScatter = (RotL64(aCross, 23U) + RotL64(aPrevious, 6U)) ^ (RotL64(aCarry, 57U) + RotL64(aIngress, 41U));
            aScatter = TwistMix64::DiffuseB(aScatter);
            //
            aOrbiterD = ((aWandererF + RotL64(aScatter, 51U)) + 12535417189990029950U) + aPhaseHOrbiterAssignSaltD[((aIndex + 29U)) & S_SALT1];
            aOrbiterI = (((aWandererH + RotL64(aIngress, 29U)) + RotL64(aCarry, 29U)) + 6204401443676390273U) + aPhaseHOrbiterAssignSaltF[(((31U - aIndex) + 25U)) & S_SALT1];
            aOrbiterE = ((aWandererK + RotL64(aCross, 38U)) + RotL64(aCarry, 43U)) + 869613505613154672U;
            aOrbiterB = ((aWandererA + RotL64(aPrevious, 13U)) + RotL64(aCarry, 5U)) + 15053590879563855802U;
            aOrbiterK = (aWandererJ + RotL64(aIngress, 5U)) + 13338989605204591428U;
            //
            aOrbiterD = ((aOrbiterD + aOrbiterI) + 18306470022403825392U) + aPhaseHOrbiterUpdateSaltB[((aIndex + 11U)) & S_SALT1];
            aOrbiterE = (aOrbiterE ^ aOrbiterD) ^ 1150696349434090218U;
            aOrbiterE = RotL64((aOrbiterE * 1099447646821052165U), 19U);
            //
            aOrbiterI = (aOrbiterI + aOrbiterB) + 13549541786420596437U;
            aOrbiterK = (aOrbiterK ^ aOrbiterI) ^ 14302878430259588461U;
            aOrbiterK = RotL64((aOrbiterK * 16813606782134305513U), 27U);
            //
            aOrbiterE = ((aOrbiterE + aOrbiterK) + 4660437084477165225U) + aPhaseHOrbiterUpdateSaltF[((aIndex + 13U)) & S_SALT1];
            aOrbiterI = ((aOrbiterI ^ aOrbiterE) ^ 1653628537860912069U) ^ aPhaseHOrbiterUpdateSaltA[((aIndex + 9U)) & S_SALT1];
            aOrbiterI = RotL64((aOrbiterI * 2624835201155303123U), 41U);
            //
            aOrbiterK = (aOrbiterK + aOrbiterD) + 5594199757006711631U;
            aOrbiterB = (aOrbiterB ^ aOrbiterK) ^ 11008472193138708891U;
            aOrbiterB = RotL64((aOrbiterB * 13645764762027798301U), 51U);
            //
            aOrbiterB = ((aOrbiterB + aOrbiterE) + 3668516817279364310U) + aPhaseHOrbiterUpdateSaltC[(((31U - aIndex) + 19U)) & S_SALT1];
            aOrbiterD = (aOrbiterD ^ aOrbiterB) ^ 128159531749679984U;
            aOrbiterD = RotL64((aOrbiterD * 4523246859249826987U), 5U);
            //
            aIngress = aOrbiterE ^ RotL64(aOrbiterK, 57U);
            aIngress = aIngress + (aOrbiterD ^ RotL64(aOrbiterI, 3U));
            aIngress = aIngress + RotL64(aOrbiterB, 13U);
            aIngress = TwistMix64::DiffuseB((aIngress + aScatter));
            //
            aWandererA = aWandererA ^ (((RotL64(aIngress, 57U) + RotL64(aOrbiterI, 47U)) + aOrbiterB) + aPhaseHWandererUpdateSaltE[(((31U - aIndex) + 10U)) & S_SALT1]);
            aWandererH = aWandererH + (((RotL64(aPrevious, 12U) + RotL64(aOrbiterI, 6U)) + aOrbiterD) + RotL64(aCarry, 21U));
            aWandererF = aWandererF ^ ((RotL64(aCross, 41U) + RotL64(aOrbiterK, 57U)) + aOrbiterE);
            aWandererJ = aWandererJ + ((((RotL64(aScatter, 3U) + aOrbiterD) + RotL64(aOrbiterK, 39U)) + RotL64(aCarry, 41U)) + aPhaseHWandererUpdateSaltB[((aIndex + 20U)) & S_SALT1]);
            aWandererK = aWandererK ^ ((RotL64(aCross, 27U) + RotL64(aOrbiterB, 21U)) + aOrbiterD);
            //
            aCarry = aCarry + (RotL64(aWandererJ, 3U) ^ aWandererF);
            aCarry = aCarry + (RotL64(aWandererH, 23U) ^ aWandererK);
            aCarry = aCarry + RotL64(aWandererA, 11U);
            aCarry = aCarry + RotL64(aIngress, 47U);
            aCarry = TwistMix64::DiffuseB(aCarry);
            //
            aWorkLaneB[S_BLOCK1 - aIndex] = aIngress;
        }
    
        // grow_key_b loop 3
        // ingress from: aWorkLaneB, aExpandLaneD, aInvestLaneC
        // ingress directions: aWorkLaneB forward forced, aExpandLaneD forward forced, aInvestLaneC forward/backward random
        // cross from: aWorkLaneA, aExpandLaneB, aOperationLaneC
        // cross directions: aWorkLaneA backward forced, aExpandLaneB backward forced, aOperationLaneC backward/forward random
        // write to: aWorkLaneC
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aWorkLaneB[((aIndex + 24168U)) & S_BLOCK1], 60U) ^ RotL64(aExpandLaneD[((aIndex + 19342U)) & S_BLOCK1], 47U));
            aIngress ^= RotL64(aInvestLaneC[((S_BLOCK1 - aIndex + 18129U)) & S_BLOCK1], 23U);
            aIngress = TwistMix64::DiffuseC(aIngress);
            //
            aCross = (RotL64(aWorkLaneA[((S_BLOCK1 - aIndex + 21997U)) & S_BLOCK1], 27U) ^ RotL64(aExpandLaneB[((S_BLOCK1 - aIndex + 23706U)) & S_BLOCK1], 43U));
            aCross ^= RotL64(aOperationLaneC[((S_BLOCK1 - aIndex + 19188U)) & S_BLOCK1], 58U);
            aCross = TwistMix64::DiffuseB(aCross);
            //
            aScatter = (RotL64(aIngress, 53U) ^ RotL64(aCarry, 5U)) + (RotL64(aCross, 39U) + RotL64(aPrevious, 22U));
            aScatter = TwistMix64::DiffuseA(aScatter);
            //
            aOrbiterD = ((aWandererG + RotL64(aIngress, 56U)) + RotL64(aCarry, 37U)) + 12775735908960052604U;
            aOrbiterI = ((aWandererK + RotL64(aPrevious, 47U)) + RotL64(aCarry, 5U)) + 11791373812080296887U;
            aOrbiterJ = ((aWandererF + RotL64(aScatter, 11U)) + 5537362877706057303U) + aPhaseHOrbiterAssignSaltC[(((31U - aIndex) + 18U)) & S_SALT1];
            aOrbiterH = ((aWandererE + RotL64(aCross, 3U)) + RotL64(aCarry, 51U)) + 2023912048504189380U;
            aOrbiterB = ((aWandererD + RotL64(aScatter, 35U)) + 17668828109963766893U) + aPhaseHOrbiterAssignSaltB[(((31U - aIndex) + 14U)) & S_SALT1];
            //
            aOrbiterD = (aOrbiterD + aOrbiterI) + 558908629933941224U;
            aOrbiterJ = ((aOrbiterJ ^ aOrbiterD) ^ 1479633119685446888U) ^ aPhaseHOrbiterUpdateSaltB[(((31U - aIndex) + 4U)) & S_SALT1];
            aOrbiterJ = RotL64((aOrbiterJ * 4447153373540811385U), 13U);
            //
            aOrbiterJ = ((aOrbiterJ + aOrbiterH) + 15460320397843364063U) + aPhaseHOrbiterUpdateSaltE[((aIndex + 19U)) & S_SALT1];
            aOrbiterB = ((aOrbiterB ^ aOrbiterJ) ^ 10059749397555469054U) ^ aPhaseHOrbiterUpdateSaltA[((aIndex + 5U)) & S_SALT1];
            aOrbiterB = RotL64((aOrbiterB * 8671817118586065469U), 41U);
            //
            aOrbiterI = (aOrbiterI + aOrbiterJ) + 9987633811929693924U;
            aOrbiterH = (aOrbiterH ^ aOrbiterI) ^ 10087337844580228269U;
            aOrbiterH = RotL64((aOrbiterH * 13817142288940843815U), 53U);
            //
            aOrbiterB = ((aOrbiterB + aOrbiterD) + 4446204415503364254U) + aPhaseHOrbiterUpdateSaltF[(((31U - aIndex) + 13U)) & S_SALT1];
            aOrbiterI = (aOrbiterI ^ aOrbiterB) ^ 15106063243302192717U;
            aOrbiterI = RotL64((aOrbiterI * 13273756657334709803U), 21U);
            //
            aOrbiterH = (aOrbiterH + aOrbiterB) + 9430197906134676162U;
            aOrbiterD = (aOrbiterD ^ aOrbiterH) ^ 1226048679997253363U;
            aOrbiterD = RotL64((aOrbiterD * 14247538885252664127U), 3U);
            //
            aIngress = aOrbiterI ^ RotL64(aOrbiterJ, 43U);
            aIngress = aIngress + (aOrbiterH ^ RotL64(aOrbiterD, 56U));
            aIngress = aIngress + RotL64(aOrbiterB, 13U);
            aIngress = TwistMix64::DiffuseB((aIngress + aScatter));
            //
            aWandererE = aWandererE + ((RotL64(aPrevious, 27U) + RotL64(aOrbiterB, 27U)) + aOrbiterD);
            aWandererG = aWandererG ^ ((RotL64(aScatter, 47U) + aOrbiterI) + RotL64(aOrbiterD, 47U));
            aWandererK = aWandererK + ((((RotL64(aCross, 56U) + aOrbiterJ) + RotL64(aOrbiterI, 35U)) + RotL64(aCarry, 57U)) + aPhaseHWandererUpdateSaltD[((aIndex + 9U)) & S_SALT1]);
            aWandererD = aWandererD ^ ((RotL64(aIngress, 37U) + RotL64(aOrbiterB, 10U)) + aOrbiterJ);
            aWandererF = aWandererF + ((((RotL64(aScatter, 19U) + RotL64(aOrbiterH, 57U)) + aOrbiterJ) + RotL64(aCarry, 27U)) + aPhaseHWandererUpdateSaltC[((aIndex + 7U)) & S_SALT1]);
            //
            aCarry = aCarry + (RotL64(aWandererK, 19U) ^ aWandererE);
            aCarry = aCarry + (aWandererG ^ RotL64(aWandererD, 35U));
            aCarry = aCarry + RotL64(aWandererF, 51U);
            aCarry = aCarry + RotL64(aIngress, 43U);
            aCarry = TwistMix64::DiffuseA(aCarry);
            //
            aWorkLaneC[aIndex] = aIngress;
        }
    
        // grow_key_b loop 4
        // ingress from: aWorkLaneC, aWorkLaneA, aInvestLaneD
        // ingress directions: aWorkLaneC forward forced, aWorkLaneA forward forced, aInvestLaneD forward/backward random
        // cross from: aWorkLaneB, aExpandLaneC, aOperationLaneD
        // cross directions: aWorkLaneB backward forced, aExpandLaneC backward forced, aOperationLaneD backward/forward random
        // write to: aWorkLaneD
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aWorkLaneC[((aIndex + 28499U)) & S_BLOCK1], 18U) ^ RotL64(aWorkLaneA[((aIndex + 26483U)) & S_BLOCK1], 43U));
            aIngress ^= RotL64(aInvestLaneD[((aIndex + 27410U)) & S_BLOCK1], 57U);
            aIngress = TwistMix64::DiffuseB(aIngress);
            //
            aCross = (RotL64(aWorkLaneB[((S_BLOCK1 - aIndex + 28662U)) & S_BLOCK1], 5U) ^ RotL64(aExpandLaneC[((S_BLOCK1 - aIndex + 32663U)) & S_BLOCK1], 23U));
            aCross ^= RotL64(aOperationLaneD[((aIndex + 32359U)) & S_BLOCK1], 48U);
            aCross = TwistMix64::DiffuseB(aCross);
            //
            aScatter = (RotL64(aCross, 18U) ^ RotL64(aPrevious, 5U)) ^ (RotL64(aIngress, 43U) + RotL64(aCarry, 57U));
            aScatter = TwistMix64::DiffuseC(aScatter);
            //
            aOrbiterK = (aWandererA + RotL64(aPrevious, 29U)) + 2571116506511057880U;
            aOrbiterB = ((aWandererE + RotL64(aCross, 13U)) + RotL64(aCarry, 41U)) + 13112435411509707292U;
            aOrbiterD = (((aWandererF + RotL64(aScatter, 54U)) + RotL64(aCarry, 23U)) + 10403251762787357256U) + aPhaseHOrbiterAssignSaltA[(((31U - aIndex) + 29U)) & S_SALT1];
            aOrbiterH = (((aWandererD + RotL64(aIngress, 3U)) + RotL64(aCarry, 3U)) + 8461951095541400405U) + aPhaseHOrbiterAssignSaltE[((aIndex + 12U)) & S_SALT1];
            aOrbiterI = (aWandererH + RotL64(aPrevious, 39U)) + 9890793478557463815U;
            //
            aOrbiterK = (aOrbiterK + aOrbiterB) + 3030229465991783707U;
            aOrbiterD = (aOrbiterD ^ aOrbiterK) ^ 7273848154043719247U;
            aOrbiterD = RotL64((aOrbiterD * 17562254601517935669U), 3U);
            //
            aOrbiterB = ((aOrbiterB + aOrbiterD) + 10681774862516028276U) + aPhaseHOrbiterUpdateSaltF[((aIndex + 5U)) & S_SALT1];
            aOrbiterH = (aOrbiterH ^ aOrbiterB) ^ 7105082755586853104U;
            aOrbiterH = RotL64((aOrbiterH * 12217705329504230357U), 11U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterH) + 6588579345319551129U;
            aOrbiterI = (aOrbiterI ^ aOrbiterD) ^ 14616333550242386092U;
            aOrbiterI = RotL64((aOrbiterI * 2934574715879306337U), 23U);
            //
            aOrbiterH = (aOrbiterH + aOrbiterI) + 15439666290229654921U;
            aOrbiterK = ((aOrbiterK ^ aOrbiterH) ^ 3360304356760164799U) ^ aPhaseHOrbiterUpdateSaltE[(((31U - aIndex) + 18U)) & S_SALT1];
            aOrbiterK = RotL64((aOrbiterK * 5164191920584106237U), 53U);
            //
            aOrbiterI = ((aOrbiterI + aOrbiterK) + 14438730801970761889U) + aPhaseHOrbiterUpdateSaltC[(((31U - aIndex) + 7U)) & S_SALT1];
            aOrbiterB = ((aOrbiterB ^ aOrbiterI) ^ 14515616787452085729U) ^ aPhaseHOrbiterUpdateSaltD[((aIndex + 15U)) & S_SALT1];
            aOrbiterB = RotL64((aOrbiterB * 2041601927968559821U), 35U);
            //
            aIngress = RotL64(aOrbiterB, 13U) ^ aOrbiterK;
            aIngress = aIngress + (aOrbiterI ^ RotL64(aOrbiterH, 23U));
            aIngress = aIngress + RotL64(aOrbiterD, 53U);
            aIngress = TwistMix64::DiffuseB((aIngress + aScatter));
            //
            aWandererH = aWandererH ^ ((RotL64(aPrevious, 12U) + RotL64(aOrbiterI, 37U)) + aOrbiterH);
            aWandererA = aWandererA + (((RotL64(aIngress, 21U) + aOrbiterB) + RotL64(aOrbiterK, 57U)) + RotL64(aCarry, 19U));
            aWandererF = aWandererF ^ (((RotL64(aCross, 3U) + RotL64(aOrbiterD, 26U)) + aOrbiterB) + aPhaseHWandererUpdateSaltF[((aIndex + 3U)) & S_SALT1]);
            aWandererE = aWandererE + (((RotL64(aScatter, 57U) + aOrbiterH) + RotL64(aOrbiterD, 47U)) + RotL64(aCarry, 35U));
            aWandererD = aWandererD ^ (((RotL64(aCross, 47U) + aOrbiterD) + RotL64(aOrbiterI, 13U)) + aPhaseHWandererUpdateSaltA[((aIndex + 8U)) & S_SALT1]);
            //
            aCarry = aCarry + (RotL64(aWandererE, 57U) ^ aWandererA);
            aCarry = aCarry + (RotL64(aWandererD, 13U) ^ aWandererF);
            aCarry = aCarry + RotL64(aWandererH, 4U);
            aCarry = aCarry + RotL64(aIngress, 35U);
            aCarry = TwistMix64::DiffuseA(aCarry);
            //
            aWorkLaneD[S_BLOCK1 - aIndex] = aIngress;
        }
    }
    // GROW_B grow_key_b (end)
    *pPrevious = aPrevious;
    *pIngress = aIngress;
    *pCarry = aCarry;
    *pWandererA = aWandererA;
    *pWandererB = aWandererB;
    *pWandererC = aWandererC;
    *pWandererD = aWandererD;
    *pWandererE = aWandererE;
    *pWandererF = aWandererF;
    *pWandererG = aWandererG;
    *pWandererH = aWandererH;
    *pWandererI = aWandererI;
    *pWandererJ = aWandererJ;
    *pWandererK = aWandererK;
}

#include "TwistExpander_Greezy_Arx.hpp"
#include "TwistFunctional.hpp"
#include "TwistMix32.hpp"
#include "TwistMix64.hpp"

#include <cstdint>

void TwistExpander_Greezy_Arx::KDF_A_A(TwistWorkSpace *pWorkSpace,
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
    [[maybe_unused]] std::uint8_t *aExpandLaneA = pWorkSpace->mExpansionLaneA;
    [[maybe_unused]] std::uint8_t *aExpandLaneB = pWorkSpace->mExpansionLaneB;
    [[maybe_unused]] std::uint8_t *aExpandLaneC = pWorkSpace->mExpansionLaneC;
    [[maybe_unused]] std::uint8_t *aExpandLaneD = pWorkSpace->mExpansionLaneD;
    [[maybe_unused]] std::uint8_t *aFireLaneA = pWorkSpace->mFireLaneA;
    [[maybe_unused]] std::uint8_t *aFireLaneB = pWorkSpace->mFireLaneB;
    std::uint64_t aCross = 0; std::uint64_t aScatter = 0;

    std::uint64_t aOrbiterA = 0; std::uint64_t aOrbiterB = 0; std::uint64_t aOrbiterC = 0; std::uint64_t aOrbiterD = 0;
    std::uint64_t aOrbiterE = 0; std::uint64_t aOrbiterF = 0; std::uint64_t aOrbiterG = 0; std::uint64_t aOrbiterH = 0;
    std::uint64_t aOrbiterI = 0; std::uint64_t aOrbiterJ = 0; std::uint64_t aOrbiterK = 0;

    // [kdf-a arx]
    std::uint64_t aNonceWordA = TwistMix64::DiffuseA(pNonce * 0x8D3DE1E1D8139A3BULL + 0x8A3316579E2C2ADFULL);
    std::uint64_t aNonceWordB = TwistMix64::DiffuseA(pNonce * 0xF9486196711CE7B5ULL + 0xBB6E7DDFA3DC2AABULL);
    std::uint64_t aNonceWordC = TwistMix64::DiffuseB(pNonce * 0xBD34D52ACFB4A6DDULL + 0xE977A3871BB32295ULL);
    std::uint64_t aNonceWordD = TwistMix64::DiffuseA(pNonce * 0xDE81317D349ADBDFULL + 0xFE3171661C9BAA7DULL);
    std::uint64_t aNonceWordE = TwistMix64::DiffuseA(pNonce * 0xA7AD4E0B10AFAC09ULL + 0xFE5FD6E26052DC8FULL);
    std::uint64_t aNonceWordF = TwistMix64::DiffuseB(pNonce * 0xE06DADCE52FFF577ULL + 0xC28C19157CC060ABULL);
    std::uint64_t aNonceWordG = TwistMix64::DiffuseC(pNonce * 0xB1E7337FA1807D3FULL + 0xA1EDB83C104BE3DCULL);
    std::uint64_t aNonceWordH = TwistMix64::DiffuseB(pNonce * 0x993D782BA634D98DULL + 0xBE9E8085798DD994ULL);
    std::uint64_t aNonceWordI = TwistMix64::DiffuseA(pNonce * 0xBBD9B4881396EE33ULL + 0xA0787BDCCBF81B6EULL);
    std::uint64_t aNonceWordJ = TwistMix64::DiffuseC(pNonce * 0xA1689D747ED0734FULL + 0xC41917E0033ED550ULL);
    std::uint64_t aNonceWordK = TwistMix64::DiffuseC(pNonce * 0xD9510A45EA2733C7ULL + 0xF7CF01A956252059ULL);
    std::uint64_t aNonceWordL = TwistMix64::DiffuseC(pNonce * 0xBFD9097F44E73FADULL + 0xD0FB8D6D8EC794ACULL);
    std::uint64_t aNonceWordM = TwistMix64::DiffuseB(pNonce * 0xFC10E5BFF8F1F8C5ULL + 0xE9F4BBAEEBCB3F2EULL);
    std::uint64_t aNonceWordN = TwistMix64::DiffuseC(pNonce * 0xAF0600F0EB3F22A5ULL + 0xC19A4ED9AC9A2030ULL);
    std::uint64_t aNonceWordO = TwistMix64::DiffuseB(pNonce * 0xDF8ACFCFA9B75303ULL + 0xFF224F6C72ACE60BULL);
    std::uint64_t aNonceWordP = TwistMix64::DiffuseA(pNonce * 0x90A7B2EF47C3D26BULL + 0xA92683DBED16CF22ULL);
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
        // read from: mSource, pSnow, aFireLaneA, aFireLaneB, aExpandLaneA, aExpandLaneB, aExpandLaneC
        // write to: aFireLaneA, aFireLaneB, aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD
    
        // kdf_a_loop_a loop 1
        // ingress from: mSource, pSnow
        // ingress directions: mSource forward forced, pSnow forward/backward random
        // cross from: pSnow, mSource
        // cross directions: pSnow backward forced, mSource backward/forward random
        // write to: aFireLaneA
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = RotL64(mSource[((aIndex + 2796U)) & S_BLOCK1], 51U) ^ RotL64(pSnow[((S_BLOCK1 - aIndex + 3685U)) & S_BLOCK1], 40U);
            aIngress = TwistMix64::DiffuseC(((aIngress ^ aDomainWordIngress) ^ aNonceWordE));
            //
            aCross = RotL64(pSnow[((S_BLOCK1 - aIndex + 5205U)) & S_BLOCK1], 13U) ^ RotL64(mSource[((S_BLOCK1 - aIndex + 1303U)) & S_BLOCK1], 44U);
            aCross = TwistMix64::DiffuseC(((aCross ^ aDomainWordCross) ^ aNonceWordA));
            //
            aScatter = (RotL64(aIngress, 13U) ^ RotL64(aCarry, 39U)) ^ (RotL64(aCross, 27U) + RotL64(aPrevious, 52U));
            aScatter = TwistMix64::DiffuseC(((aScatter ^ aDomainWordScatter) ^ aNonceWordO));
            //
            aOrbiterJ = ((aWandererE + RotL64(aPrevious, 39U)) + 8793908991006073956U) + aOrbiterAssignSaltD[(((31U - aIndex) + 3U)) & S_SALT1];
            aOrbiterC = (aWandererC + RotL64(aScatter, 30U)) + 2932916283348441943U;
            aOrbiterG = ((aWandererI + RotL64(aCross, 47U)) + 11069042087940968262U) + aNonceWordO;
            aOrbiterE = (aWandererH + RotL64(aIngress, 41U)) + 14369628676782894441U;
            aOrbiterI = (((aWandererK + RotL64(aScatter, 19U)) + RotL64(aCarry, 3U)) + 8602903272780978282U) + aNonceWordH;
            aOrbiterB = (aWandererF + RotL64(aPrevious, 53U)) + 3827036107178568820U;
            aOrbiterD = ((aWandererA + RotL64(aIngress, 35U)) + RotL64(aCarry, 39U)) + 8905245209036772489U;
            aOrbiterK = (aWandererD + RotL64(aCross, 23U)) + 13331387530760017893U;
            aOrbiterH = (((aWandererJ + RotL64(aPrevious, 27U)) + RotL64(aCarry, 47U)) + 9880107580289737823U) + aOrbiterAssignSaltA[(((31U - aIndex) + 22U)) & S_SALT1];
            aOrbiterA = ((aWandererG + RotL64(aCross, 51U)) + 10199619040626900278U) + aNonceWordB;
            aOrbiterF = ((aWandererB + RotL64(aIngress, 6U)) + 2466307560891374281U) + aNonceWordP;
            //
            aOrbiterJ = (aOrbiterJ + aOrbiterC) + 13973403407981259448U;
            aOrbiterG = (aOrbiterG ^ aOrbiterJ) ^ 2851460278409385243U;
            aOrbiterG = RotL64((aOrbiterG * 11226902976321781743U), 23U);
            //
            aOrbiterE = (aOrbiterE + aOrbiterJ) + 10365453393815690776U;
            aOrbiterI = ((aOrbiterI ^ aOrbiterE) ^ 2382382358987358791U) ^ aOrbiterUpdateSaltC[((aIndex + 7U)) & S_SALT1];
            aOrbiterI = RotL64((aOrbiterI * 481563628980705781U), 39U);
            //
            aOrbiterC = ((aOrbiterC + aOrbiterB) + 5058198848163792422U) + aOrbiterUpdateSaltD[((aIndex + 25U)) & S_SALT1];
            aOrbiterD = (aOrbiterD ^ aOrbiterC) ^ 10500434740387593487U;
            aOrbiterD = RotL64((aOrbiterD * 5946747708776079787U), 27U);
            //
            aOrbiterK = (aOrbiterK + aOrbiterH) + 11289798395177667084U;
            aOrbiterC = (aOrbiterC ^ aOrbiterK) ^ 14327152153231286666U;
            aOrbiterC = RotL64((aOrbiterC * 18155778059595245561U), 35U);
            //
            aOrbiterI = (aOrbiterI + aOrbiterG) + 8065137263811956313U;
            aOrbiterA = (aOrbiterA ^ aOrbiterI) ^ 3865153574847924816U;
            aOrbiterA = RotL64((aOrbiterA * 9495741102667755161U), 37U);
            //
            aOrbiterF = (aOrbiterF + aOrbiterA) + 18102279969722473375U;
            aOrbiterE = (aOrbiterE ^ aOrbiterF) ^ 6306428427188742325U;
            aOrbiterE = RotL64((aOrbiterE * 17826782872351406167U), 43U);
            //
            aOrbiterG = (aOrbiterG + aOrbiterD) + 16953348204663693724U;
            aOrbiterK = (aOrbiterK ^ aOrbiterG) ^ 11950791817032898613U;
            aOrbiterK = RotL64((aOrbiterK * 1498946055469611133U), 11U);
            //
            aOrbiterD = (((aOrbiterD + aOrbiterF) + 11980823193543752994U) + aOrbiterUpdateSaltA[(((31U - aIndex) + 9U)) & S_SALT1]) + aNonceWordD;
            aOrbiterH = ((aOrbiterH ^ aOrbiterD) ^ 17845490308799454871U) ^ aNonceWordG;
            aOrbiterH = RotL64((aOrbiterH * 16385153013485463791U), 53U);
            //
            aOrbiterB = (aOrbiterB + aOrbiterI) + 5566398755702887071U;
            aOrbiterF = (aOrbiterF ^ aOrbiterB) ^ 10308378271388889968U;
            aOrbiterF = RotL64((aOrbiterF * 142732084484961281U), 29U);
            //
            aOrbiterA = (aOrbiterA + aOrbiterK) + 6717846700455219260U;
            aOrbiterJ = ((aOrbiterJ ^ aOrbiterA) ^ 8297225372883997017U) ^ aOrbiterUpdateSaltF[((aIndex + 17U)) & S_SALT1];
            aOrbiterJ = RotL64((aOrbiterJ * 14102812043481327907U), 21U);
            //
            aOrbiterH = ((aOrbiterH + aOrbiterE) + 12249337046267666603U) + aNonceWordI;
            aOrbiterB = (aOrbiterB ^ aOrbiterH) ^ 8793908991006073956U;
            aOrbiterB = RotL64((aOrbiterB * 5851229209188473467U), 47U);
            //
            aIngress = aOrbiterG ^ RotL64(aOrbiterA, 39U);
            aIngress = aIngress + (RotL64(aOrbiterD, 47U) ^ aOrbiterE);
            aIngress = aIngress + (aOrbiterJ ^ RotL64(aOrbiterH, 23U));
            aIngress = aIngress + (RotL64(aOrbiterK, 53U) ^ aOrbiterF);
            aIngress = aIngress + (RotL64(aOrbiterB, 12U) ^ aOrbiterI);
            aIngress = aIngress + RotL64(aOrbiterC, 3U);
            aIngress = TwistMix64::DiffuseC((aIngress + aScatter));
            //
            aWandererA = aWandererA + (((RotL64(aCross, 19U) + aOrbiterD) + RotL64(aOrbiterG, 41U)) + aNonceWordJ);
            aWandererF = aWandererF ^ (((RotL64(aPrevious, 53U) + RotL64(aOrbiterH, 34U)) + aOrbiterA) + aWandererUpdateSaltF[(((31U - aIndex) + 23U)) & S_SALT1]);
            aWandererI = aWandererI + ((RotL64(aScatter, 5U) + aOrbiterE) + RotL64(aOrbiterD, 27U));
            aWandererD = aWandererD ^ (((RotL64(aIngress, 34U) + RotL64(aOrbiterF, 13U)) + aOrbiterE) + aNonceWordM);
            aWandererK = aWandererK + ((RotL64(aScatter, 21U) + RotL64(aOrbiterE, 21U)) + aOrbiterK);
            aWandererC = aWandererC ^ ((RotL64(aIngress, 51U) + aOrbiterI) + RotL64(aOrbiterJ, 53U));
            aWandererH = aWandererH + (((RotL64(aCross, 13U) + RotL64(aOrbiterC, 29U)) + aOrbiterE) + aNonceWordK);
            aWandererB = aWandererB ^ (((RotL64(aPrevious, 30U) + aOrbiterB) + RotL64(aOrbiterI, 47U)) + aNonceWordC);
            aWandererG = aWandererG + (((RotL64(aCross, 57U) + RotL64(aOrbiterE, 6U)) + aOrbiterH) + RotL64(aCarry, 35U));
            aWandererJ = aWandererJ ^ ((RotL64(aPrevious, 3U) + RotL64(aOrbiterH, 39U)) + aOrbiterK);
            aWandererE = aWandererE + ((((RotL64(aScatter, 47U) + RotL64(aOrbiterJ, 57U)) + aOrbiterF) + RotL64(aCarry, 27U)) + aWandererUpdateSaltE[(((31U - aIndex) + 11U)) & S_SALT1]);
            //
            aCarry = aCarry + (aWandererK ^ RotL64(aWandererB, 53U));
            aCarry = aCarry + (RotL64(aWandererF, 18U) ^ aWandererA);
            aCarry = aCarry + (aWandererH ^ RotL64(aWandererC, 57U));
            aCarry = aCarry + (aWandererI ^ RotL64(aWandererJ, 3U));
            aCarry = aCarry + (RotL64(aWandererD, 37U) ^ aWandererG);
            aCarry = aCarry + RotL64(aWandererE, 39U);
            aCarry = aCarry + RotL64(aIngress, 26U);
            aCarry = TwistMix64::DiffuseB(aCarry);
            //
            aFireLaneA[aIndex] = aIngress;
        }
    
        // kdf_a_loop_a loop 2
        // ingress from: aFireLaneA, pSnow
        // ingress directions: aFireLaneA forward forced, pSnow forward/backward random
        // cross from: aFireLaneA, mSource
        // cross directions: aFireLaneA backward forced, mSource backward/forward random
        // write to: aFireLaneB
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = RotL64(aFireLaneA[((aIndex + 5616U)) & S_BLOCK1], 13U) ^ RotL64(pSnow[((S_BLOCK1 - aIndex + 5895U)) & S_BLOCK1], 30U);
            aIngress = TwistMix64::DiffuseA(((aIngress ^ aDomainWordIngress) ^ aNonceWordG));
            //
            aCross = RotL64(aFireLaneA[((S_BLOCK1 - aIndex + 7255U)) & S_BLOCK1], 3U) ^ RotL64(mSource[((aIndex + 6474U)) & S_BLOCK1], 46U);
            aCross = TwistMix64::DiffuseA(((aCross ^ aDomainWordCross) ^ aNonceWordF));
            //
            aScatter = (RotL64(aIngress, 11U) ^ RotL64(aCross, 41U)) + (RotL64(aCarry, 23U) + RotL64(aPrevious, 60U));
            aScatter = TwistMix64::DiffuseB(((aScatter ^ aDomainWordScatter) ^ aNonceWordN));
            //
            aOrbiterG = (aWandererG + RotL64(aIngress, 47U)) + 5173905450211892891U;
            aOrbiterB = (aWandererI + RotL64(aPrevious, 35U)) + 3555542451908039957U;
            aOrbiterI = (((aWandererA + RotL64(aCross, 54U)) + RotL64(aCarry, 53U)) + 11559884700283861559U) + aOrbiterAssignSaltE[(((31U - aIndex) + 21U)) & S_SALT1];
            aOrbiterD = (aWandererE + RotL64(aScatter, 29U)) + 1352524329968738673U;
            aOrbiterC = ((((aWandererF + RotL64(aPrevious, 43U)) + RotL64(aCarry, 23U)) + 8914206450420616349U) + aOrbiterAssignSaltB[(((31U - aIndex) + 28U)) & S_SALT1]) + aNonceWordL;
            aOrbiterE = (aWandererH + RotL64(aIngress, 41U)) + 2251523378498463946U;
            aOrbiterA = (aWandererK + RotL64(aScatter, 51U)) + 9541575923299247038U;
            aOrbiterH = (aWandererC + RotL64(aCross, 27U)) + 1239854507907214595U;
            aOrbiterK = (aWandererD + RotL64(aScatter, 3U)) + 17698101462598498934U;
            aOrbiterJ = (aWandererJ + RotL64(aPrevious, 5U)) + 12305566971683256060U;
            aOrbiterF = (((aWandererB + RotL64(aIngress, 22U)) + RotL64(aCarry, 57U)) + 13804545036303215569U) + aNonceWordJ;
            //
            aOrbiterG = (aOrbiterG + aOrbiterB) + 10239749097704329264U;
            aOrbiterI = ((aOrbiterI ^ aOrbiterG) ^ 4212214906286320308U) ^ aOrbiterUpdateSaltF[((aIndex + 26U)) & S_SALT1];
            aOrbiterI = RotL64((aOrbiterI * 3661436621615751071U), 27U);
            //
            aOrbiterI = ((aOrbiterI + aOrbiterD) + 12192418916967430783U) + aOrbiterUpdateSaltD[(((31U - aIndex) + 13U)) & S_SALT1];
            aOrbiterC = ((aOrbiterC ^ aOrbiterI) ^ 4475514289326450361U) ^ aNonceWordN;
            aOrbiterC = RotL64((aOrbiterC * 17497164630368757887U), 23U);
            //
            aOrbiterE = ((aOrbiterE + aOrbiterC) + 17376102613298827459U) + aNonceWordE;
            aOrbiterG = ((aOrbiterG ^ aOrbiterE) ^ 18129393209955439341U) ^ aOrbiterUpdateSaltE[((aIndex + 27U)) & S_SALT1];
            aOrbiterG = RotL64((aOrbiterG * 6404089025014118979U), 39U);
            //
            aOrbiterA = (aOrbiterA + aOrbiterH) + 4014763724300253568U;
            aOrbiterK = (aOrbiterK ^ aOrbiterA) ^ 17325007199676828814U;
            aOrbiterK = RotL64((aOrbiterK * 1420888274815627083U), 35U);
            //
            aOrbiterJ = (aOrbiterJ + aOrbiterI) + 15480474849292388685U;
            aOrbiterE = (aOrbiterE ^ aOrbiterJ) ^ 14357924730184375449U;
            aOrbiterE = RotL64((aOrbiterE * 16723492259068034209U), 5U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterF) + 4335731868597970070U;
            aOrbiterA = (((aOrbiterA ^ aOrbiterD) ^ 8296023680394303015U) ^ aOrbiterUpdateSaltB[(((31U - aIndex) + 17U)) & S_SALT1]) ^ aNonceWordA;
            aOrbiterA = RotL64((aOrbiterA * 14027415401430120543U), 29U);
            //
            aOrbiterK = (aOrbiterK + aOrbiterJ) + 2807312426993262800U;
            aOrbiterF = (aOrbiterF ^ aOrbiterK) ^ 15510369660839648501U;
            aOrbiterF = RotL64((aOrbiterF * 18207954408298333959U), 21U);
            //
            aOrbiterC = (aOrbiterC + aOrbiterA) + 12597844696606519907U;
            aOrbiterB = ((aOrbiterB ^ aOrbiterC) ^ 7231012798553551535U) ^ aNonceWordP;
            aOrbiterB = RotL64((aOrbiterB * 2841306785994479299U), 57U);
            //
            aOrbiterF = (aOrbiterF + aOrbiterE) + 849663631945232360U;
            aOrbiterH = (aOrbiterH ^ aOrbiterF) ^ 4002310581470781194U;
            aOrbiterH = RotL64((aOrbiterH * 2148877014350721479U), 53U);
            //
            aOrbiterB = (aOrbiterB + aOrbiterK) + 16067735571435654555U;
            aOrbiterD = (aOrbiterD ^ aOrbiterB) ^ 4607980694199923842U;
            aOrbiterD = RotL64((aOrbiterD * 10401780756830017477U), 37U);
            //
            aOrbiterH = (aOrbiterH + aOrbiterG) + 5346879191913449715U;
            aOrbiterJ = (aOrbiterJ ^ aOrbiterH) ^ 5173905450211892891U;
            aOrbiterJ = RotL64((aOrbiterJ * 15360571827429301833U), 3U);
            //
            aIngress = aOrbiterF ^ RotL64(aOrbiterA, 57U);
            aIngress = aIngress + (aOrbiterB ^ RotL64(aOrbiterG, 53U));
            aIngress = aIngress + (aOrbiterH ^ RotL64(aOrbiterJ, 27U));
            aIngress = aIngress + (aOrbiterI ^ RotL64(aOrbiterC, 21U));
            aIngress = aIngress + (aOrbiterD ^ RotL64(aOrbiterK, 50U));
            aIngress = aIngress + RotL64(aOrbiterE, 47U);
            aIngress = TwistMix64::DiffuseC((aIngress + aScatter));
            //
            aWandererK = aWandererK ^ (((RotL64(aPrevious, 41U) + RotL64(aOrbiterA, 19U)) + aOrbiterE) + aNonceWordD);
            aWandererH = aWandererH + ((RotL64(aScatter, 47U) + RotL64(aOrbiterI, 53U)) + aOrbiterG);
            aWandererF = aWandererF ^ ((RotL64(aCross, 4U) + RotL64(aOrbiterK, 39U)) + aOrbiterB);
            aWandererA = aWandererA + ((RotL64(aIngress, 19U) + aOrbiterF) + RotL64(aOrbiterH, 60U));
            aWandererD = aWandererD ^ ((RotL64(aScatter, 37U) + RotL64(aOrbiterE, 29U)) + aOrbiterC);
            aWandererG = aWandererG + (((RotL64(aPrevious, 29U) + RotL64(aOrbiterJ, 21U)) + aOrbiterG) + aNonceWordH);
            aWandererE = aWandererE ^ ((RotL64(aIngress, 43U) + aOrbiterH) + RotL64(aOrbiterA, 13U));
            aWandererC = aWandererC + (((RotL64(aCross, 60U) + aOrbiterD) + RotL64(aOrbiterG, 5U)) + RotL64(aCarry, 53U));
            aWandererI = aWandererI ^ ((((RotL64(aPrevious, 13U) + aOrbiterJ) + RotL64(aOrbiterD, 11U)) + aNonceWordK) + aWandererUpdateSaltA[(((31U - aIndex) + 3U)) & S_SALT1]);
            aWandererB = aWandererB + ((((RotL64(aIngress, 21U) + RotL64(aOrbiterH, 42U)) + aOrbiterK) + RotL64(aCarry, 19U)) + aNonceWordM);
            aWandererJ = aWandererJ ^ (((RotL64(aScatter, 57U) + RotL64(aOrbiterH, 51U)) + aOrbiterB) + aWandererUpdateSaltC[((aIndex + 15U)) & S_SALT1]);
            //
            aCarry = aCarry + (RotL64(aWandererB, 3U) ^ aWandererC);
            aCarry = aCarry + (aWandererF ^ RotL64(aWandererE, 11U));
            aCarry = aCarry + (aWandererI ^ RotL64(aWandererG, 44U));
            aCarry = aCarry + (aWandererD ^ RotL64(aWandererH, 47U));
            aCarry = aCarry + (RotL64(aWandererJ, 19U) ^ aWandererA);
            aCarry = aCarry + RotL64(aWandererK, 57U);
            aCarry = aCarry + RotL64(aIngress, 42U);
            aCarry = TwistMix64::DiffuseA(aCarry);
            //
            aFireLaneB[S_BLOCK1 - aIndex] = aIngress;
        }
    
        // kdf_a_loop_a loop 3
        // ingress from: aFireLaneB, mSource
        // ingress directions: aFireLaneB forward forced, mSource forward/backward random
        // cross from: aFireLaneA, pSnow
        // cross directions: aFireLaneA backward forced, pSnow backward/forward random
        // write to: aExpandLaneA
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = RotL64(aFireLaneB[((aIndex + 13445U)) & S_BLOCK1], 51U) ^ RotL64(mSource[((aIndex + 12796U)) & S_BLOCK1], 10U);
            aIngress = TwistMix64::DiffuseA(((aIngress ^ aDomainWordIngress) ^ aNonceWordO));
            //
            aCross = RotL64(aFireLaneA[((S_BLOCK1 - aIndex + 13372U)) & S_BLOCK1], 10U) ^ RotL64(pSnow[((aIndex + 13594U)) & S_BLOCK1], 39U);
            aCross = TwistMix64::DiffuseC(((aCross ^ aDomainWordCross) ^ aNonceWordG));
            //
            aScatter = (RotL64(aPrevious, 3U) ^ RotL64(aCross, 47U)) ^ (RotL64(aCarry, 35U) + RotL64(aIngress, 20U));
            aScatter = TwistMix64::DiffuseB(((aScatter ^ aDomainWordScatter) ^ aNonceWordA));
            //
            aOrbiterF = ((aWandererJ + RotL64(aScatter, 26U)) + 17454559218352016650U) + aOrbiterAssignSaltF[((aIndex + 19U)) & S_SALT1];
            aOrbiterH = ((aWandererE + RotL64(aCross, 19U)) + RotL64(aCarry, 41U)) + 8005709669325164803U;
            aOrbiterB = ((aWandererH + RotL64(aPrevious, 35U)) + RotL64(aCarry, 11U)) + 13393741948412816357U;
            aOrbiterD = ((aWandererF + RotL64(aIngress, 37U)) + 3665865624348875553U) + aNonceWordH;
            aOrbiterG = (aWandererD + RotL64(aScatter, 53U)) + 8334142570031883436U;
            aOrbiterA = ((aWandererI + RotL64(aIngress, 43U)) + RotL64(aCarry, 5U)) + 17226066128706139657U;
            aOrbiterE = ((aWandererB + RotL64(aCross, 41U)) + 3319093033121522613U) + aNonceWordP;
            aOrbiterC = (aWandererC + RotL64(aPrevious, 47U)) + 6657535603401588798U;
            aOrbiterJ = ((aWandererK + RotL64(aIngress, 3U)) + 5469746182326331147U) + aOrbiterAssignSaltC[((aIndex + 25U)) & S_SALT1];
            aOrbiterK = (aWandererA + RotL64(aScatter, 6U)) + 17846791786050221418U;
            aOrbiterI = ((aWandererG + RotL64(aCross, 51U)) + 15939541003714896288U) + aNonceWordN;
            //
            aOrbiterF = (aOrbiterF + aOrbiterH) + 12076763190461077406U;
            aOrbiterB = (aOrbiterB ^ aOrbiterF) ^ 3594038213596405284U;
            aOrbiterB = RotL64((aOrbiterB * 10244002692575821495U), 35U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterF) + 8301291631324464622U;
            aOrbiterG = ((aOrbiterG ^ aOrbiterD) ^ 8460406137668390582U) ^ aOrbiterUpdateSaltD[(((31U - aIndex) + 20U)) & S_SALT1];
            aOrbiterG = RotL64((aOrbiterG * 9117147929757711595U), 37U);
            //
            aOrbiterA = (aOrbiterA + aOrbiterE) + 7612394867020871200U;
            aOrbiterD = ((aOrbiterD ^ aOrbiterA) ^ 8525076134853103975U) ^ aNonceWordI;
            aOrbiterD = RotL64((aOrbiterD * 5790440201072204659U), 41U);
            //
            aOrbiterC = (aOrbiterC + aOrbiterA) + 11929899088215090379U;
            aOrbiterJ = (aOrbiterJ ^ aOrbiterC) ^ 7119509166360685726U;
            aOrbiterJ = RotL64((aOrbiterJ * 1662341427992528823U), 57U);
            //
            aOrbiterH = (aOrbiterH + aOrbiterC) + 5081078459225240607U;
            aOrbiterK = (aOrbiterK ^ aOrbiterH) ^ 17149991983909906705U;
            aOrbiterK = RotL64((aOrbiterK * 950223374568067343U), 3U);
            //
            aOrbiterB = (aOrbiterB + aOrbiterK) + 8817303295675241994U;
            aOrbiterA = ((aOrbiterA ^ aOrbiterB) ^ 7962039282652745113U) ^ aNonceWordB;
            aOrbiterA = RotL64((aOrbiterA * 12773588587795522121U), 21U);
            //
            aOrbiterK = ((aOrbiterK + aOrbiterJ) + 13596273086338032370U) + aNonceWordE;
            aOrbiterE = (aOrbiterE ^ aOrbiterK) ^ 8186297702278180956U;
            aOrbiterE = RotL64((aOrbiterE * 6226504769888753861U), 47U);
            //
            aOrbiterJ = ((aOrbiterJ + aOrbiterD) + 1696277861691580263U) + aOrbiterUpdateSaltE[(((31U - aIndex) + 3U)) & S_SALT1];
            aOrbiterI = ((aOrbiterI ^ aOrbiterJ) ^ 17360461831507082959U) ^ aOrbiterUpdateSaltC[(((31U - aIndex) + 10U)) & S_SALT1];
            aOrbiterI = RotL64((aOrbiterI * 1651378456022210983U), 39U);
            //
            aOrbiterG = (aOrbiterG + aOrbiterB) + 1384868996572650981U;
            aOrbiterC = (aOrbiterC ^ aOrbiterG) ^ 2039624849777183290U;
            aOrbiterC = RotL64((aOrbiterC * 13148024378138271937U), 5U);
            //
            aOrbiterE = (aOrbiterE + aOrbiterI) + 14530407348595669913U;
            aOrbiterF = (aOrbiterF ^ aOrbiterE) ^ 18023931565754525034U;
            aOrbiterF = RotL64((aOrbiterF * 18025122652259338105U), 29U);
            //
            aOrbiterI = (aOrbiterI + aOrbiterG) + 11245556671533878373U;
            aOrbiterH = ((aOrbiterH ^ aOrbiterI) ^ 17454559218352016650U) ^ aOrbiterUpdateSaltF[((aIndex + 9U)) & S_SALT1];
            aOrbiterH = RotL64((aOrbiterH * 15665798947106818229U), 51U);
            //
            aIngress = RotL64(aOrbiterB, 19U) ^ aOrbiterE;
            aIngress = aIngress + (RotL64(aOrbiterJ, 34U) ^ aOrbiterG);
            aIngress = aIngress + (aOrbiterI ^ RotL64(aOrbiterK, 37U));
            aIngress = aIngress + (aOrbiterH ^ RotL64(aOrbiterA, 51U));
            aIngress = aIngress + (RotL64(aOrbiterF, 3U) ^ aOrbiterC);
            aIngress = aIngress + RotL64(aOrbiterD, 21U);
            aIngress = TwistMix64::DiffuseC((aIngress + aScatter));
            //
            aWandererD = aWandererD ^ ((RotL64(aCross, 50U) + aOrbiterA) + RotL64(aOrbiterC, 11U));
            aWandererG = aWandererG + (((RotL64(aPrevious, 29U) + RotL64(aOrbiterE, 35U)) + aOrbiterA) + RotL64(aCarry, 27U));
            aWandererH = aWandererH ^ ((RotL64(aIngress, 11U) + RotL64(aOrbiterK, 54U)) + aOrbiterF);
            aWandererF = aWandererF + ((RotL64(aScatter, 35U) + aOrbiterK) + RotL64(aOrbiterB, 43U));
            aWandererC = aWandererC ^ ((((RotL64(aIngress, 3U) + aOrbiterI) + RotL64(aOrbiterH, 3U)) + aNonceWordM) + aWandererUpdateSaltD[(((31U - aIndex) + 15U)) & S_SALT1]);
            aWandererA = aWandererA + ((RotL64(aScatter, 6U) + RotL64(aOrbiterK, 23U)) + aOrbiterD);
            aWandererI = aWandererI ^ ((RotL64(aCross, 41U) + RotL64(aOrbiterK, 29U)) + aOrbiterJ);
            aWandererJ = aWandererJ + ((((RotL64(aPrevious, 47U) + aOrbiterE) + RotL64(aOrbiterI, 52U)) + aNonceWordA) + aWandererUpdateSaltB[((aIndex + 22U)) & S_SALT1]);
            aWandererB = aWandererB ^ (((RotL64(aCross, 39U) + aOrbiterD) + RotL64(aOrbiterB, 5U)) + aNonceWordF);
            aWandererK = aWandererK + (((RotL64(aScatter, 27U) + aOrbiterG) + RotL64(aOrbiterE, 19U)) + RotL64(aCarry, 3U));
            aWandererE = aWandererE ^ ((RotL64(aPrevious, 43U) + aOrbiterH) + RotL64(aOrbiterK, 57U));
            //
            aCarry = aCarry + (RotL64(aWandererG, 18U) ^ aWandererH);
            aCarry = aCarry + (RotL64(aWandererD, 43U) ^ aWandererE);
            aCarry = aCarry + (RotL64(aWandererA, 57U) ^ aWandererF);
            aCarry = aCarry + (RotL64(aWandererI, 47U) ^ aWandererC);
            aCarry = aCarry + (RotL64(aWandererB, 11U) ^ aWandererJ);
            aCarry = aCarry + RotL64(aWandererK, 51U);
            aCarry = aCarry + RotL64(aIngress, 26U);
            aCarry = TwistMix64::DiffuseC(aCarry);
            //
            aExpandLaneA[aIndex] = aIngress;
        }
    
        // kdf_a_loop_a loop 4
        // ingress from: aExpandLaneA, pSnow, aFireLaneA
        // ingress directions: aExpandLaneA forward forced, pSnow forward forced, aFireLaneA forward/backward random
        // cross from: mSource, aFireLaneB
        // cross directions: mSource backward forced, aFireLaneB backward/forward random
        // write to: aExpandLaneB
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aExpandLaneA[((aIndex + 17055U)) & S_BLOCK1], 57U) ^ RotL64(pSnow[((aIndex + 19452U)) & S_BLOCK1], 12U));
            aIngress ^= RotL64(aFireLaneA[((S_BLOCK1 - aIndex + 19059U)) & S_BLOCK1], 41U);
            aIngress = TwistMix64::DiffuseB(((aIngress ^ aDomainWordIngress) ^ aNonceWordI));
            //
            aCross = RotL64(mSource[((S_BLOCK1 - aIndex + 16528U)) & S_BLOCK1], 42U) ^ RotL64(aFireLaneB[((aIndex + 20338U)) & S_BLOCK1], 29U);
            aCross = TwistMix64::DiffuseC(((aCross ^ aDomainWordCross) ^ aNonceWordF));
            //
            aScatter = (RotL64(aCross, 57U) ^ RotL64(aPrevious, 5U)) + (RotL64(aIngress, 40U) + RotL64(aCarry, 27U));
            aScatter = TwistMix64::DiffuseA(((aScatter ^ aDomainWordScatter) ^ aNonceWordI));
            //
            aOrbiterG = (aWandererI + RotL64(aCross, 43U)) + 2101601659597850213U;
            aOrbiterB = (aWandererB + RotL64(aIngress, 11U)) + 2759794072560720121U;
            aOrbiterA = ((((aWandererC + RotL64(aScatter, 35U)) + RotL64(aCarry, 53U)) + 9443562552411269339U) + aOrbiterAssignSaltA[((aIndex + 15U)) & S_SALT1]) + aNonceWordK;
            aOrbiterF = (aWandererD + RotL64(aPrevious, 27U)) + 10801360546699857975U;
            aOrbiterD = ((aWandererA + RotL64(aCross, 4U)) + 8020716394829332019U) + aOrbiterAssignSaltD[(((31U - aIndex) + 23U)) & S_SALT1];
            aOrbiterC = ((aWandererK + RotL64(aIngress, 47U)) + 1021894212367773801U) + aNonceWordB;
            aOrbiterE = (aWandererH + RotL64(aScatter, 29U)) + 13346855534622490176U;
            aOrbiterK = ((aWandererG + RotL64(aPrevious, 53U)) + RotL64(aCarry, 57U)) + 16359309548462953836U;
            aOrbiterI = (aWandererF + RotL64(aCross, 41U)) + 12642446944680783519U;
            aOrbiterH = (((aWandererJ + RotL64(aIngress, 56U)) + RotL64(aCarry, 11U)) + 8197424982767553380U) + aNonceWordJ;
            aOrbiterJ = (aWandererE + RotL64(aScatter, 21U)) + 14346334610901859094U;
            //
            aOrbiterG = (aOrbiterG + aOrbiterB) + 14171304260534233539U;
            aOrbiterA = (aOrbiterA ^ aOrbiterG) ^ 334531601308283605U;
            aOrbiterA = RotL64((aOrbiterA * 5012968232749075075U), 53U);
            //
            aOrbiterF = (aOrbiterF + aOrbiterD) + 10707856298471572695U;
            aOrbiterC = (aOrbiterC ^ aOrbiterF) ^ 18364775750091914766U;
            aOrbiterC = RotL64((aOrbiterC * 15735143943129143265U), 21U);
            //
            aOrbiterB = ((aOrbiterB + aOrbiterE) + 8531394793118363836U) + aOrbiterUpdateSaltE[(((31U - aIndex) + 7U)) & S_SALT1];
            aOrbiterK = (aOrbiterK ^ aOrbiterB) ^ 15352876929406908882U;
            aOrbiterK = RotL64((aOrbiterK * 475199047053777179U), 51U);
            //
            aOrbiterK = (aOrbiterK + aOrbiterF) + 567682016232278157U;
            aOrbiterI = ((aOrbiterI ^ aOrbiterK) ^ 2068146551757663119U) ^ aNonceWordM;
            aOrbiterI = RotL64((aOrbiterI * 1557877740957797555U), 57U);
            //
            aOrbiterI = (aOrbiterI + aOrbiterC) + 7776122587613256525U;
            aOrbiterH = (aOrbiterH ^ aOrbiterI) ^ 16430938890724272256U;
            aOrbiterH = RotL64((aOrbiterH * 4540270493783593257U), 11U);
            //
            aOrbiterC = (aOrbiterC + aOrbiterJ) + 11912000645055436094U;
            aOrbiterG = (aOrbiterG ^ aOrbiterC) ^ 16800749242578741498U;
            aOrbiterG = RotL64((aOrbiterG * 17804584625034241737U), 43U);
            //
            aOrbiterH = (aOrbiterH + aOrbiterG) + 5909199180260499150U;
            aOrbiterE = ((aOrbiterE ^ aOrbiterH) ^ 5751089915336865588U) ^ aOrbiterUpdateSaltD[(((31U - aIndex) + 26U)) & S_SALT1];
            aOrbiterE = RotL64((aOrbiterE * 15376689503142397927U), 23U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterI) + 3478216857728853008U;
            aOrbiterJ = (aOrbiterJ ^ aOrbiterD) ^ 18007567146937338241U;
            aOrbiterJ = RotL64((aOrbiterJ * 6620498877303917855U), 5U);
            //
            aOrbiterE = (aOrbiterE + aOrbiterA) + 17454259424163653490U;
            aOrbiterF = ((aOrbiterF ^ aOrbiterE) ^ 6276120962018305311U) ^ aOrbiterUpdateSaltC[(((31U - aIndex) + 21U)) & S_SALT1];
            aOrbiterF = RotL64((aOrbiterF * 7560618224285018801U), 27U);
            //
            aOrbiterJ = ((aOrbiterJ + aOrbiterH) + 3839336239901666431U) + aOrbiterUpdateSaltA[(((31U - aIndex) + 3U)) & S_SALT1];
            aOrbiterB = (aOrbiterB ^ aOrbiterJ) ^ 6230149015045237670U;
            aOrbiterB = RotL64((aOrbiterB * 1838983748994340883U), 37U);
            //
            aOrbiterA = (aOrbiterA + aOrbiterK) + 17552095486612766544U;
            aOrbiterD = ((aOrbiterD ^ aOrbiterA) ^ 2101601659597850213U) ^ aNonceWordG;
            aOrbiterD = RotL64((aOrbiterD * 2915330118061857271U), 29U);
            //
            aIngress = RotL64(aOrbiterC, 57U) ^ aOrbiterK;
            aIngress = aIngress + (aOrbiterF ^ RotL64(aOrbiterE, 29U));
            aIngress = aIngress + (RotL64(aOrbiterB, 53U) ^ aOrbiterJ);
            aIngress = aIngress + (aOrbiterG ^ RotL64(aOrbiterD, 14U));
            aIngress = aIngress + (RotL64(aOrbiterA, 27U) ^ aOrbiterH);
            aIngress = aIngress + RotL64(aOrbiterI, 3U);
            aIngress = TwistMix64::DiffuseB((aIngress + aScatter));
            //
            aWandererH = aWandererH + (((RotL64(aCross, 12U) + RotL64(aOrbiterH, 11U)) + aOrbiterI) + aNonceWordN);
            aWandererB = aWandererB ^ (((RotL64(aPrevious, 51U) + RotL64(aOrbiterK, 19U)) + aOrbiterH) + aNonceWordP);
            aWandererI = aWandererI + ((RotL64(aIngress, 57U) + aOrbiterA) + RotL64(aOrbiterD, 51U));
            aWandererC = aWandererC ^ ((RotL64(aScatter, 5U) + RotL64(aOrbiterK, 3U)) + aOrbiterB);
            aWandererG = aWandererG + (((RotL64(aPrevious, 3U) + aOrbiterA) + RotL64(aOrbiterI, 35U)) + RotL64(aCarry, 5U));
            aWandererF = aWandererF ^ (((RotL64(aIngress, 21U) + RotL64(aOrbiterC, 29U)) + aOrbiterA) + aWandererUpdateSaltE[(((31U - aIndex) + 14U)) & S_SALT1]);
            aWandererJ = aWandererJ + ((((RotL64(aScatter, 37U) + RotL64(aOrbiterE, 6U)) + aOrbiterB) + RotL64(aCarry, 23U)) + aNonceWordA);
            aWandererD = aWandererD ^ (((RotL64(aCross, 23U) + RotL64(aOrbiterF, 37U)) + aOrbiterJ) + aWandererUpdateSaltF[((aIndex + 27U)) & S_SALT1]);
            aWandererK = aWandererK + ((RotL64(aScatter, 30U) + RotL64(aOrbiterF, 39U)) + aOrbiterG);
            aWandererE = aWandererE ^ ((RotL64(aCross, 35U) + aOrbiterJ) + RotL64(aOrbiterA, 27U));
            aWandererA = aWandererA + ((RotL64(aPrevious, 53U) + RotL64(aOrbiterA, 56U)) + aOrbiterH);
            //
            aCarry = aCarry + (aWandererE ^ RotL64(aWandererJ, 11U));
            aCarry = aCarry + (RotL64(aWandererG, 13U) ^ aWandererA);
            aCarry = aCarry + (RotL64(aWandererB, 44U) ^ aWandererC);
            aCarry = aCarry + (aWandererF ^ RotL64(aWandererH, 35U));
            aCarry = aCarry + (aWandererK ^ RotL64(aWandererI, 21U));
            aCarry = aCarry + RotL64(aWandererD, 47U);
            aCarry = aCarry + RotL64(aIngress, 42U);
            aCarry = TwistMix64::DiffuseA(aCarry);
            //
            aExpandLaneB[S_BLOCK1 - aIndex] = aIngress;
        }
    
        // kdf_a_loop_a loop 5
        // ingress from: aExpandLaneB, mSource, pSnow, aFireLaneA
        // ingress directions: aExpandLaneB forward forced, mSource forward forced, pSnow forward forced, aFireLaneA forward/backward random
        // cross from: aExpandLaneA, aFireLaneB
        // cross directions: aExpandLaneA backward forced, aFireLaneB backward/forward random
        // write to: aExpandLaneC
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aExpandLaneB[((aIndex + 22090U)) & S_BLOCK1], 36U) ^ RotL64(mSource[((aIndex + 25786U)) & S_BLOCK1], 53U));
            aIngress ^= (RotL64(pSnow[((aIndex + 24349U)) & S_BLOCK1], 11U) ^ RotL64(aFireLaneA[((aIndex + 23928U)) & S_BLOCK1], 3U));
            aIngress = TwistMix64::DiffuseA(((aIngress ^ aDomainWordIngress) ^ aNonceWordA));
            //
            aCross = RotL64(aExpandLaneA[((S_BLOCK1 - aIndex + 23008U)) & S_BLOCK1], 53U) ^ RotL64(aFireLaneB[((S_BLOCK1 - aIndex + 22355U)) & S_BLOCK1], 44U);
            aCross = TwistMix64::DiffuseB(((aCross ^ aDomainWordCross) ^ aNonceWordM));
            //
            aScatter = (RotL64(aCarry, 53U) ^ RotL64(aPrevious, 6U)) ^ (RotL64(aCross, 41U) + RotL64(aIngress, 23U));
            aScatter = TwistMix64::DiffuseB(((aScatter ^ aDomainWordScatter) ^ aNonceWordO));
            //
            aOrbiterE = ((aWandererH + RotL64(aIngress, 53U)) + RotL64(aCarry, 13U)) + 14686411261024919129U;
            aOrbiterA = (aWandererI + RotL64(aCross, 10U)) + 7514582233957632005U;
            aOrbiterH = (((aWandererD + RotL64(aPrevious, 51U)) + RotL64(aCarry, 43U)) + 6520710480103365552U) + aOrbiterAssignSaltB[(((31U - aIndex) + 10U)) & S_SALT1];
            aOrbiterB = ((aWandererG + RotL64(aScatter, 23U)) + 1983621978676188036U) + aOrbiterAssignSaltE[((aIndex + 14U)) & S_SALT1];
            aOrbiterC = ((aWandererJ + RotL64(aPrevious, 57U)) + 9003524602590749672U) + aNonceWordG;
            aOrbiterD = (aWandererB + RotL64(aCross, 37U)) + 6428568234045228995U;
            aOrbiterK = ((aWandererA + RotL64(aIngress, 39U)) + 8656552687136446989U) + aNonceWordJ;
            aOrbiterJ = (((aWandererF + RotL64(aScatter, 21U)) + RotL64(aCarry, 51U)) + 16916248288415922490U) + aNonceWordF;
            aOrbiterF = (aWandererK + RotL64(aCross, 5U)) + 9740237548002535784U;
            aOrbiterG = (aWandererC + RotL64(aScatter, 43U)) + 907561000814618339U;
            aOrbiterI = ((aWandererE + RotL64(aIngress, 46U)) + 4751108900841197631U) + aNonceWordL;
            //
            aOrbiterE = (aOrbiterE + aOrbiterA) + 167774899400732287U;
            aOrbiterH = (aOrbiterH ^ aOrbiterE) ^ 11907484918310854962U;
            aOrbiterH = RotL64((aOrbiterH * 7213139491146402985U), 11U);
            //
            aOrbiterB = (aOrbiterB + aOrbiterC) + 14910318613649863924U;
            aOrbiterA = (aOrbiterA ^ aOrbiterB) ^ 14882888155751455276U;
            aOrbiterA = RotL64((aOrbiterA * 11394136445442060201U), 21U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterE) + 16175942562693781908U;
            aOrbiterK = (aOrbiterK ^ aOrbiterD) ^ 11022373758481651102U;
            aOrbiterK = RotL64((aOrbiterK * 6836331461393816027U), 5U);
            //
            aOrbiterJ = (((aOrbiterJ + aOrbiterD) + 12548405399045031548U) + aOrbiterUpdateSaltF[((aIndex + 7U)) & S_SALT1]) + aNonceWordH;
            aOrbiterF = ((aOrbiterF ^ aOrbiterJ) ^ 10850926364556828443U) ^ aOrbiterUpdateSaltE[(((31U - aIndex) + 22U)) & S_SALT1];
            aOrbiterF = RotL64((aOrbiterF * 16231561687709867431U), 39U);
            //
            aOrbiterC = (aOrbiterC + aOrbiterF) + 13391684887911141790U;
            aOrbiterG = (aOrbiterG ^ aOrbiterC) ^ 14648937281264822988U;
            aOrbiterG = RotL64((aOrbiterG * 6533299316940026059U), 37U);
            //
            aOrbiterK = (aOrbiterK + aOrbiterH) + 8298658887198526821U;
            aOrbiterB = (((aOrbiterB ^ aOrbiterK) ^ 13822977698661348891U) ^ aOrbiterUpdateSaltD[(((31U - aIndex) + 28U)) & S_SALT1]) ^ aNonceWordC;
            aOrbiterB = RotL64((aOrbiterB * 17769262972278410937U), 43U);
            //
            aOrbiterI = (aOrbiterI + aOrbiterB) + 7505646847564645719U;
            aOrbiterE = (aOrbiterE ^ aOrbiterI) ^ 3238749538197209166U;
            aOrbiterE = RotL64((aOrbiterE * 15394286542600778567U), 19U);
            //
            aOrbiterH = ((aOrbiterH + aOrbiterJ) + 15853506915123709257U) + aNonceWordD;
            aOrbiterC = (aOrbiterC ^ aOrbiterH) ^ 8426329899401071248U;
            aOrbiterC = RotL64((aOrbiterC * 1330397096577715113U), 23U);
            //
            aOrbiterG = (aOrbiterG + aOrbiterI) + 14848635392815613098U;
            aOrbiterD = (aOrbiterD ^ aOrbiterG) ^ 3549927798350175044U;
            aOrbiterD = RotL64((aOrbiterD * 1899044682313056949U), 47U);
            //
            aOrbiterA = (aOrbiterA + aOrbiterG) + 1798973117197750802U;
            aOrbiterJ = (((aOrbiterJ ^ aOrbiterA) ^ 13056711228618953977U) ^ aOrbiterUpdateSaltB[((aIndex + 17U)) & S_SALT1]) ^ aNonceWordP;
            aOrbiterJ = RotL64((aOrbiterJ * 9102877396419306689U), 13U);
            //
            aOrbiterF = (aOrbiterF + aOrbiterK) + 1395893547965799281U;
            aOrbiterI = (aOrbiterI ^ aOrbiterF) ^ 14686411261024919129U;
            aOrbiterI = RotL64((aOrbiterI * 17075377081365066067U), 53U);
            //
            aIngress = aOrbiterF ^ RotL64(aOrbiterC, 47U);
            aIngress = aIngress + (RotL64(aOrbiterB, 27U) ^ aOrbiterJ);
            aIngress = aIngress + (aOrbiterA ^ RotL64(aOrbiterG, 24U));
            aIngress = aIngress + (aOrbiterK ^ RotL64(aOrbiterI, 29U));
            aIngress = aIngress + (aOrbiterE ^ RotL64(aOrbiterD, 21U));
            aIngress = aIngress + RotL64(aOrbiterH, 41U);
            aIngress = TwistMix64::DiffuseB((aIngress + aScatter));
            //
            aWandererI = aWandererI ^ ((RotL64(aScatter, 60U) + aOrbiterA) + RotL64(aOrbiterG, 3U));
            aWandererA = aWandererA + ((RotL64(aIngress, 37U) + RotL64(aOrbiterJ, 21U)) + aOrbiterF);
            aWandererC = aWandererC ^ (((RotL64(aCross, 41U) + aOrbiterJ) + RotL64(aOrbiterE, 46U)) + aWandererUpdateSaltA[((aIndex + 15U)) & S_SALT1]);
            aWandererE = aWandererE + ((((RotL64(aPrevious, 47U) + aOrbiterA) + RotL64(aOrbiterK, 23U)) + RotL64(aCarry, 5U)) + aNonceWordE);
            aWandererK = aWandererK ^ ((RotL64(aIngress, 35U) + aOrbiterA) + RotL64(aOrbiterD, 11U));
            aWandererF = aWandererF + (((RotL64(aScatter, 13U) + aOrbiterG) + RotL64(aOrbiterB, 5U)) + aNonceWordI);
            aWandererB = aWandererB ^ (((RotL64(aPrevious, 21U) + aOrbiterK) + RotL64(aOrbiterF, 41U)) + aWandererUpdateSaltC[(((31U - aIndex) + 11U)) & S_SALT1]);
            aWandererG = aWandererG + (((RotL64(aCross, 50U) + RotL64(aOrbiterH, 43U)) + aOrbiterK) + RotL64(aCarry, 21U));
            aWandererD = aWandererD ^ ((RotL64(aPrevious, 19U) + RotL64(aOrbiterC, 29U)) + aOrbiterH);
            aWandererH = aWandererH + ((RotL64(aScatter, 39U) + RotL64(aOrbiterC, 58U)) + aOrbiterI);
            aWandererJ = aWandererJ ^ ((RotL64(aCross, 11U) + aOrbiterF) + RotL64(aOrbiterB, 13U));
            //
            aCarry = aCarry + (RotL64(aWandererI, 21U) ^ aWandererJ);
            aCarry = aCarry + (aWandererD ^ RotL64(aWandererC, 19U));
            aCarry = aCarry + (aWandererB ^ RotL64(aWandererA, 38U));
            aCarry = aCarry + (aWandererF ^ RotL64(aWandererG, 53U));
            aCarry = aCarry + (aWandererH ^ RotL64(aWandererE, 5U));
            aCarry = aCarry + RotL64(aWandererK, 41U);
            aCarry = aCarry + RotL64(aIngress, 3U);
            aCarry = TwistMix64::DiffuseC(aCarry);
            //
            aExpandLaneC[aIndex] = aIngress;
        }
    
        // kdf_a_loop_a loop 6
        // ingress from: aExpandLaneC, aExpandLaneA, aFireLaneA
        // ingress directions: aExpandLaneC forward forced, aExpandLaneA forward forced, aFireLaneA forward/backward random
        // cross from: aExpandLaneB, mSource, pSnow, aFireLaneB
        // cross directions: aExpandLaneB backward forced, mSource backward forced, pSnow backward forced, aFireLaneB backward/forward random
        // write to: aExpandLaneD
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aExpandLaneC[((aIndex + 31305U)) & S_BLOCK1], 46U) ^ RotL64(aExpandLaneA[((aIndex + 30892U)) & S_BLOCK1], 3U));
            aIngress ^= RotL64(aFireLaneA[((aIndex + 28999U)) & S_BLOCK1], 29U);
            aIngress = TwistMix64::DiffuseC(((aIngress ^ aDomainWordIngress) ^ aNonceWordJ));
            //
            aCross = (RotL64(aExpandLaneB[((S_BLOCK1 - aIndex + 28163U)) & S_BLOCK1], 27U) ^ RotL64(mSource[((S_BLOCK1 - aIndex + 28805U)) & S_BLOCK1], 19U));
            aCross ^= (RotL64(pSnow[((S_BLOCK1 - aIndex + 27814U)) & S_BLOCK1], 39U) ^ RotL64(aFireLaneB[((S_BLOCK1 - aIndex + 27630U)) & S_BLOCK1], 5U));
            aCross = TwistMix64::DiffuseB(((aCross ^ aDomainWordCross) ^ aNonceWordL));
            //
            aScatter = (RotL64(aPrevious, 5U) + RotL64(aCross, 54U)) ^ (RotL64(aIngress, 23U) + RotL64(aCarry, 37U));
            aScatter = TwistMix64::DiffuseC(((aScatter ^ aDomainWordScatter) ^ aNonceWordA));
            //
            aOrbiterE = ((aWandererC + RotL64(aIngress, 46U)) + 7960325128608297381U) + aNonceWordD;
            aOrbiterH = (aWandererG + RotL64(aScatter, 3U)) + 12773836012104052042U;
            aOrbiterA = (aWandererJ + RotL64(aPrevious, 43U)) + 3173972621347773016U;
            aOrbiterD = (((aWandererA + RotL64(aCross, 13U)) + RotL64(aCarry, 53U)) + 3708401356314308171U) + aNonceWordI;
            aOrbiterF = ((aWandererB + RotL64(aScatter, 39U)) + RotL64(aCarry, 47U)) + 950774285720019449U;
            aOrbiterB = ((aWandererH + RotL64(aCross, 11U)) + 4170092315705438265U) + aOrbiterAssignSaltF[(((31U - aIndex) + 19U)) & S_SALT1];
            aOrbiterI = (((aWandererF + RotL64(aIngress, 37U)) + RotL64(aCarry, 39U)) + 17000449130864980747U) + aOrbiterAssignSaltC[(((31U - aIndex) + 6U)) & S_SALT1];
            aOrbiterG = (aWandererK + RotL64(aPrevious, 41U)) + 8793910540062893860U;
            aOrbiterJ = (aWandererI + RotL64(aScatter, 34U)) + 520277969543516469U;
            aOrbiterK = ((aWandererD + RotL64(aIngress, 29U)) + 12762214857389827271U) + aNonceWordG;
            aOrbiterC = ((aWandererE + RotL64(aCross, 23U)) + 2932451184340207695U) + aNonceWordM;
            //
            aOrbiterE = (aOrbiterE + aOrbiterH) + 11062179998786293839U;
            aOrbiterA = (aOrbiterA ^ aOrbiterE) ^ 7919119215271524178U;
            aOrbiterA = RotL64((aOrbiterA * 9053677007180081359U), 57U);
            //
            aOrbiterD = ((aOrbiterD + aOrbiterF) + 1774988449597115155U) + aOrbiterUpdateSaltB[(((31U - aIndex) + 7U)) & S_SALT1];
            aOrbiterB = (aOrbiterB ^ aOrbiterD) ^ 3799792889466518953U;
            aOrbiterB = RotL64((aOrbiterB * 17512791286490623455U), 11U);
            //
            aOrbiterI = (aOrbiterI + aOrbiterB) + 1815062051307896589U;
            aOrbiterH = ((aOrbiterH ^ aOrbiterI) ^ 15260373951371654483U) ^ aNonceWordN;
            aOrbiterH = RotL64((aOrbiterH * 2208604434669491625U), 29U);
            //
            aOrbiterB = (aOrbiterB + aOrbiterE) + 12867546628945676853U;
            aOrbiterG = ((aOrbiterG ^ aOrbiterB) ^ 7772820973895846946U) ^ aNonceWordO;
            aOrbiterG = RotL64((aOrbiterG * 7581704643538761985U), 41U);
            //
            aOrbiterF = ((aOrbiterF + aOrbiterI) + 14213957831821966834U) + aNonceWordB;
            aOrbiterE = (aOrbiterE ^ aOrbiterF) ^ 16561105721170419454U;
            aOrbiterE = RotL64((aOrbiterE * 2540533987337175367U), 47U);
            //
            aOrbiterJ = ((aOrbiterJ + aOrbiterK) + 16556502948339949526U) + aOrbiterUpdateSaltA[((aIndex + 24U)) & S_SALT1];
            aOrbiterF = (aOrbiterF ^ aOrbiterJ) ^ 9706742922075498974U;
            aOrbiterF = RotL64((aOrbiterF * 8527361328901355457U), 53U);
            //
            aOrbiterG = ((aOrbiterG + aOrbiterA) + 13455756934917486016U) + aNonceWordC;
            aOrbiterJ = (aOrbiterJ ^ aOrbiterG) ^ 9107769876332723454U;
            aOrbiterJ = RotL64((aOrbiterJ * 1722386100852683783U), 37U);
            //
            aOrbiterA = ((aOrbiterA + aOrbiterC) + 15793099079168487016U) + aOrbiterUpdateSaltE[(((31U - aIndex) + 18U)) & S_SALT1];
            aOrbiterK = ((aOrbiterK ^ aOrbiterA) ^ 7968278803691283365U) ^ aOrbiterUpdateSaltD[(((31U - aIndex) + 3U)) & S_SALT1];
            aOrbiterK = RotL64((aOrbiterK * 11644765391940099387U), 35U);
            //
            aOrbiterK = (aOrbiterK + aOrbiterD) + 15068302421261745111U;
            aOrbiterI = (aOrbiterI ^ aOrbiterK) ^ 11373111908765197862U;
            aOrbiterI = RotL64((aOrbiterI * 17756438368103196771U), 21U);
            //
            aOrbiterC = (aOrbiterC + aOrbiterJ) + 6362100123286229887U;
            aOrbiterD = (aOrbiterD ^ aOrbiterC) ^ 528778333872160609U;
            aOrbiterD = RotL64((aOrbiterD * 17377710146983314215U), 19U);
            //
            aOrbiterH = (aOrbiterH + aOrbiterG) + 6116442644744391285U;
            aOrbiterC = (aOrbiterC ^ aOrbiterH) ^ 7960325128608297381U;
            aOrbiterC = RotL64((aOrbiterC * 17826511435509927061U), 23U);
            //
            aIngress = RotL64(aOrbiterB, 56U) ^ aOrbiterH;
            aIngress = aIngress + (RotL64(aOrbiterJ, 21U) ^ aOrbiterG);
            aIngress = aIngress + (aOrbiterE ^ RotL64(aOrbiterC, 53U));
            aIngress = aIngress + (aOrbiterF ^ RotL64(aOrbiterA, 13U));
            aIngress = aIngress + (RotL64(aOrbiterI, 35U) ^ aOrbiterK);
            aIngress = aIngress + RotL64(aOrbiterD, 3U);
            aIngress = TwistMix64::DiffuseA((aIngress + aScatter));
            //
            aWandererC = aWandererC ^ (((RotL64(aIngress, 51U) + RotL64(aOrbiterA, 47U)) + aOrbiterC) + aNonceWordF);
            aWandererD = aWandererD + ((RotL64(aScatter, 3U) + aOrbiterK) + RotL64(aOrbiterB, 27U));
            aWandererB = aWandererB ^ (((RotL64(aPrevious, 27U) + RotL64(aOrbiterC, 57U)) + aOrbiterH) + aWandererUpdateSaltD[(((31U - aIndex) + 5U)) & S_SALT1]);
            aWandererA = aWandererA + ((((RotL64(aCross, 30U) + RotL64(aOrbiterE, 29U)) + aOrbiterH) + RotL64(aCarry, 39U)) + aWandererUpdateSaltB[((aIndex + 10U)) & S_SALT1]);
            aWandererI = aWandererI ^ ((RotL64(aScatter, 11U) + aOrbiterK) + RotL64(aOrbiterG, 11U));
            aWandererH = aWandererH + ((RotL64(aIngress, 23U) + aOrbiterF) + RotL64(aOrbiterJ, 54U));
            aWandererG = aWandererG ^ ((RotL64(aCross, 53U) + RotL64(aOrbiterE, 19U)) + aOrbiterJ);
            aWandererF = aWandererF + ((RotL64(aPrevious, 37U) + RotL64(aOrbiterG, 3U)) + aOrbiterF);
            aWandererK = aWandererK ^ (((RotL64(aCross, 44U) + aOrbiterF) + RotL64(aOrbiterD, 51U)) + aNonceWordP);
            aWandererE = aWandererE + (((RotL64(aScatter, 41U) + RotL64(aOrbiterH, 36U)) + aOrbiterK) + RotL64(aCarry, 57U));
            aWandererJ = aWandererJ ^ ((RotL64(aIngress, 47U) + aOrbiterI) + RotL64(aOrbiterB, 41U));
            //
            aCarry = aCarry + (RotL64(aWandererJ, 23U) ^ aWandererD);
            aCarry = aCarry + (RotL64(aWandererH, 18U) ^ aWandererF);
            aCarry = aCarry + (RotL64(aWandererA, 39U) ^ aWandererK);
            aCarry = aCarry + (RotL64(aWandererI, 35U) ^ aWandererB);
            aCarry = aCarry + (aWandererG ^ RotL64(aWandererE, 11U));
            aCarry = aCarry + RotL64(aWandererC, 4U);
            aCarry = aCarry + RotL64(aIngress, 53U);
            aCarry = TwistMix64::DiffuseC(aCarry);
            //
            aExpandLaneD[S_BLOCK1 - aIndex] = aIngress;
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

void TwistExpander_Greezy_Arx::KDF_A_B(TwistWorkSpace *pWorkSpace,
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
    [[maybe_unused]] std::uint8_t *aOperationLaneA = pWorkSpace->mOperationLaneA;
    [[maybe_unused]] std::uint8_t *aOperationLaneB = pWorkSpace->mOperationLaneB;
    [[maybe_unused]] std::uint8_t *aOperationLaneC = pWorkSpace->mOperationLaneC;
    [[maybe_unused]] std::uint8_t *aOperationLaneD = pWorkSpace->mOperationLaneD;
    [[maybe_unused]] std::uint8_t *aFireLaneC = pWorkSpace->mFireLaneC;
    [[maybe_unused]] std::uint8_t *aFireLaneD = pWorkSpace->mFireLaneD;
    std::uint64_t aCross = 0; std::uint64_t aScatter = 0;

    std::uint64_t aOrbiterA = 0; std::uint64_t aOrbiterB = 0; std::uint64_t aOrbiterC = 0; std::uint64_t aOrbiterD = 0;
    std::uint64_t aOrbiterE = 0; std::uint64_t aOrbiterF = 0; std::uint64_t aOrbiterG = 0; std::uint64_t aOrbiterH = 0;
    std::uint64_t aOrbiterI = 0; std::uint64_t aOrbiterJ = 0; std::uint64_t aOrbiterK = 0;

    // [kdf-a arx]
    std::uint64_t aNonceWordA = TwistMix64::DiffuseC(pNonce * 0xFECD2434459B5193ULL + 0xA741123AA90EB288ULL);
    std::uint64_t aNonceWordB = TwistMix64::DiffuseB(pNonce * 0xAD1A563392DF66FBULL + 0xD283924F0F76F922ULL);
    std::uint64_t aNonceWordC = TwistMix64::DiffuseC(pNonce * 0xE3FCD5122AAE59B7ULL + 0xDBA3FB4E31ED1F7BULL);
    std::uint64_t aNonceWordD = TwistMix64::DiffuseA(pNonce * 0x96EF0B35D8CCCE9FULL + 0x8240D2323D35D793ULL);
    std::uint64_t aNonceWordE = TwistMix64::DiffuseA(pNonce * 0xAE5A6603F489E0E9ULL + 0xB81DB152C8F356A3ULL);
    std::uint64_t aNonceWordF = TwistMix64::DiffuseB(pNonce * 0xC5CAF763D7D88C39ULL + 0xFBA16933FC98ECBFULL);
    std::uint64_t aNonceWordG = TwistMix64::DiffuseC(pNonce * 0xA6A141922D3E7AC1ULL + 0xBCCEE37BBDB17926ULL);
    std::uint64_t aNonceWordH = TwistMix64::DiffuseA(pNonce * 0xEDBE7280CE3B7391ULL + 0x9E57D9CAD5F5E98FULL);
    std::uint64_t aNonceWordI = TwistMix64::DiffuseC(pNonce * 0xF0B325683761D4E1ULL + 0xE1B023CF97748C88ULL);
    std::uint64_t aNonceWordJ = TwistMix64::DiffuseA(pNonce * 0xF9683D65E2800CE3ULL + 0xF2352E4A95116B98ULL);
    std::uint64_t aNonceWordK = TwistMix64::DiffuseB(pNonce * 0xE20D8AF388983F45ULL + 0xE70F5DFBF17AB6FCULL);
    std::uint64_t aNonceWordL = TwistMix64::DiffuseB(pNonce * 0xF2A0DAEB1E24368BULL + 0x8E23ECCE9A43C98CULL);
    std::uint64_t aNonceWordM = TwistMix64::DiffuseA(pNonce * 0xD6E9C1FF21149CC1ULL + 0xC141659386781D28ULL);
    std::uint64_t aNonceWordN = TwistMix64::DiffuseA(pNonce * 0xA561520AC191C89FULL + 0xAF751816106CA975ULL);
    std::uint64_t aNonceWordO = TwistMix64::DiffuseB(pNonce * 0xDFECB861D9B263B5ULL + 0xD1C8352C35450977ULL);
    std::uint64_t aNonceWordP = TwistMix64::DiffuseB(pNonce * 0xAC7714E60FB65277ULL + 0xA0DE8B283ED7A3E7ULL);
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
        // read from: aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aFireLaneC, aFireLaneD, aOperationLaneA, aOperationLaneB, aOperationLaneC
        // write to: aFireLaneC, aFireLaneD, aOperationLaneA, aOperationLaneB, aOperationLaneC, aOperationLaneD
    
        // kdf_a_loop_b loop 1
        // ingress from: aExpandLaneA, aExpandLaneB
        // ingress directions: aExpandLaneA forward forced, aExpandLaneB forward/backward random
        // cross from: aExpandLaneC, aExpandLaneD
        // cross directions: aExpandLaneC backward forced, aExpandLaneD backward/forward random
        // write to: aFireLaneC
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = RotL64(aExpandLaneA[((aIndex + 4612U)) & S_BLOCK1], 37U) ^ RotL64(aExpandLaneB[((S_BLOCK1 - aIndex + 664U)) & S_BLOCK1], 23U);
            aIngress = TwistMix64::DiffuseB(((aIngress ^ aDomainWordIngress) ^ aNonceWordP));
            //
            aCross = RotL64(aExpandLaneC[((S_BLOCK1 - aIndex + 4478U)) & S_BLOCK1], 11U) ^ RotL64(aExpandLaneD[((S_BLOCK1 - aIndex + 5343U)) & S_BLOCK1], 48U);
            aCross = TwistMix64::DiffuseA(((aCross ^ aDomainWordCross) ^ aNonceWordO));
            //
            aScatter = (RotL64(aPrevious, 41U) + RotL64(aCross, 20U)) ^ (RotL64(aCarry, 5U) + RotL64(aIngress, 53U));
            aScatter = TwistMix64::DiffuseA(((aScatter ^ aDomainWordScatter) ^ aNonceWordB));
            //
            aOrbiterE = (((aWandererD + RotL64(aPrevious, 18U)) + RotL64(aCarry, 35U)) + 14157904117287696136U) + aOrbiterAssignSaltD[((aIndex + 9U)) & S_SALT1];
            aOrbiterK = ((aWandererJ + RotL64(aScatter, 57U)) + 7369512677371640676U) + aNonceWordL;
            aOrbiterH = ((aWandererK + RotL64(aIngress, 29U)) + RotL64(aCarry, 21U)) + 8411250745902073798U;
            aOrbiterF = ((aWandererG + RotL64(aCross, 51U)) + RotL64(aCarry, 13U)) + 5002041814539710275U;
            aOrbiterJ = (aWandererC + RotL64(aScatter, 5U)) + 9538041410816283124U;
            aOrbiterB = (aWandererI + RotL64(aPrevious, 22U)) + 5210700103927513061U;
            aOrbiterC = ((aWandererA + RotL64(aCross, 37U)) + 7600709399101287982U) + aNonceWordN;
            aOrbiterG = ((aWandererE + RotL64(aIngress, 41U)) + 2366369466696580499U) + aOrbiterAssignSaltC[((aIndex + 11U)) & S_SALT1];
            aOrbiterA = (aWandererB + RotL64(aScatter, 47U)) + 5544575244203019109U;
            //
            aOrbiterE = (aOrbiterE + aOrbiterK) + 8710073749110329779U;
            aOrbiterH = (aOrbiterH ^ aOrbiterE) ^ 15998211310115361630U;
            aOrbiterH = RotL64((aOrbiterH * 15275657696897688955U), 57U);
            //
            aOrbiterK = (aOrbiterK + aOrbiterF) + 15354357553877376422U;
            aOrbiterJ = (aOrbiterJ ^ aOrbiterK) ^ 10657523549259276169U;
            aOrbiterJ = RotL64((aOrbiterJ * 13695239532898311073U), 43U);
            //
            aOrbiterF = (aOrbiterF + aOrbiterE) + 10405750198355464768U;
            aOrbiterB = ((aOrbiterB ^ aOrbiterF) ^ 3465819693133515142U) ^ aOrbiterUpdateSaltB[((aIndex + 23U)) & S_SALT1];
            aOrbiterB = RotL64((aOrbiterB * 14678343718277562799U), 5U);
            //
            aOrbiterC = ((aOrbiterC + aOrbiterG) + 16724189641701408630U) + aOrbiterUpdateSaltE[(((31U - aIndex) + 15U)) & S_SALT1];
            aOrbiterE = (aOrbiterE ^ aOrbiterC) ^ 3484340153620198872U;
            aOrbiterE = RotL64((aOrbiterE * 17247547677520703125U), 51U);
            //
            aOrbiterJ = ((aOrbiterJ + aOrbiterB) + 7420442404884871126U) + aOrbiterUpdateSaltA[(((31U - aIndex) + 19U)) & S_SALT1];
            aOrbiterC = ((aOrbiterC ^ aOrbiterJ) ^ 11138445997256757636U) ^ aNonceWordI;
            aOrbiterC = RotL64((aOrbiterC * 11167543379937571127U), 19U);
            //
            aOrbiterA = ((aOrbiterA + aOrbiterC) + 1428191560884663125U) + aNonceWordE;
            aOrbiterF = ((aOrbiterF ^ aOrbiterA) ^ 16950093140800653985U) ^ aOrbiterUpdateSaltF[((aIndex + 10U)) & S_SALT1];
            aOrbiterF = RotL64((aOrbiterF * 4423012306984814805U), 27U);
            //
            aOrbiterH = ((aOrbiterH + aOrbiterJ) + 17288299075036481960U) + aNonceWordM;
            aOrbiterA = (aOrbiterA ^ aOrbiterH) ^ 13793597915359681028U;
            aOrbiterA = RotL64((aOrbiterA * 9639204979982125757U), 13U);
            //
            aOrbiterB = (aOrbiterB + aOrbiterH) + 5017972942710079726U;
            aOrbiterG = (aOrbiterG ^ aOrbiterB) ^ 12409957957614320964U;
            aOrbiterG = RotL64((aOrbiterG * 10273295741911545745U), 23U);
            //
            aOrbiterG = (aOrbiterG + aOrbiterA) + 12487994181992095174U;
            aOrbiterK = ((aOrbiterK ^ aOrbiterG) ^ 1573393166996612118U) ^ aNonceWordH;
            aOrbiterK = RotL64((aOrbiterK * 13364311829104520751U), 39U);
            //
            aIngress = RotL64(aOrbiterH, 3U) ^ aOrbiterG;
            aIngress = aIngress + (RotL64(aOrbiterC, 19U) ^ aOrbiterJ);
            aIngress = aIngress + (aOrbiterA ^ RotL64(aOrbiterB, 23U));
            aIngress = aIngress + (aOrbiterF ^ RotL64(aOrbiterK, 34U));
            aIngress = aIngress + RotL64(aOrbiterE, 41U);
            aIngress = TwistMix64::DiffuseB((aIngress + aScatter));
            //
            aWandererB = aWandererB ^ (((RotL64(aScatter, 3U) + aOrbiterA) + RotL64(aOrbiterH, 37U)) + aNonceWordG);
            aWandererK = aWandererK + ((RotL64(aIngress, 12U) + RotL64(aOrbiterE, 57U)) + aOrbiterB);
            aWandererA = aWandererA ^ (((RotL64(aPrevious, 39U) + RotL64(aOrbiterK, 22U)) + aOrbiterC) + aWandererUpdateSaltF[((aIndex + 25U)) & S_SALT1]);
            aWandererJ = aWandererJ + (((((RotL64(aCross, 29U) + RotL64(aOrbiterC, 53U)) + aOrbiterB) + RotL64(aCarry, 51U)) + aNonceWordD) + aWandererUpdateSaltE[(((31U - aIndex) + 7U)) & S_SALT1]);
            aWandererI = aWandererI ^ (((RotL64(aPrevious, 57U) + aOrbiterA) + RotL64(aOrbiterK, 11U)) + aNonceWordA);
            aWandererD = aWandererD + ((RotL64(aCross, 50U) + aOrbiterF) + RotL64(aOrbiterK, 41U));
            aWandererE = aWandererE ^ ((RotL64(aIngress, 19U) + aOrbiterB) + RotL64(aOrbiterG, 4U));
            aWandererC = aWandererC + (((RotL64(aScatter, 35U) + aOrbiterC) + RotL64(aOrbiterJ, 29U)) + RotL64(aCarry, 27U));
            aWandererG = aWandererG ^ ((RotL64(aPrevious, 43U) + aOrbiterK) + RotL64(aOrbiterJ, 47U));
            //
            aCarry = aCarry + (RotL64(aWandererK, 5U) ^ aWandererB);
            aCarry = aCarry + (aWandererC ^ RotL64(aWandererJ, 41U));
            aCarry = aCarry + (RotL64(aWandererG, 29U) ^ aWandererE);
            aCarry = aCarry + (aWandererI ^ RotL64(aWandererA, 54U));
            aCarry = aCarry + RotL64(aWandererD, 47U);
            aCarry = aCarry + RotL64(aIngress, 13U);
            aCarry = TwistMix64::DiffuseC(aCarry);
            //
            aFireLaneC[aIndex] = aIngress;
        }
    
        // kdf_a_loop_b loop 2
        // ingress from: aFireLaneC, aExpandLaneB, aExpandLaneC
        // ingress directions: aFireLaneC forward forced, aExpandLaneB forward forced, aExpandLaneC forward/backward random
        // cross from: aExpandLaneA, aExpandLaneD
        // cross directions: aExpandLaneA backward forced, aExpandLaneD backward/forward random
        // write to: aFireLaneD
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aFireLaneC[((aIndex + 6734U)) & S_BLOCK1], 53U) ^ RotL64(aExpandLaneB[((aIndex + 7295U)) & S_BLOCK1], 13U));
            aIngress ^= RotL64(aExpandLaneC[((S_BLOCK1 - aIndex + 6027U)) & S_BLOCK1], 34U);
            aIngress = TwistMix64::DiffuseC(((aIngress ^ aDomainWordIngress) ^ aNonceWordC));
            //
            aCross = RotL64(aExpandLaneA[((S_BLOCK1 - aIndex + 10414U)) & S_BLOCK1], 38U) ^ RotL64(aExpandLaneD[((aIndex + 7637U)) & S_BLOCK1], 3U);
            aCross = TwistMix64::DiffuseC(((aCross ^ aDomainWordCross) ^ aNonceWordB));
            //
            aScatter = (RotL64(aIngress, 21U) ^ RotL64(aCarry, 5U)) ^ (RotL64(aCross, 39U) + RotL64(aPrevious, 56U));
            aScatter = TwistMix64::DiffuseB(((aScatter ^ aDomainWordScatter) ^ aNonceWordP));
            //
            aOrbiterG = ((aWandererC + RotL64(aPrevious, 27U)) + 1393781663398437180U) + aNonceWordM;
            aOrbiterF = (aWandererH + RotL64(aCross, 47U)) + 17414594746688585273U;
            aOrbiterA = ((aWandererB + RotL64(aIngress, 52U)) + 2823888497053071250U) + aOrbiterAssignSaltB[((aIndex + 20U)) & S_SALT1];
            aOrbiterK = ((aWandererD + RotL64(aScatter, 39U)) + RotL64(aCarry, 43U)) + 17032631958617884859U;
            aOrbiterE = (((aWandererK + RotL64(aCross, 35U)) + RotL64(aCarry, 19U)) + 15222697630461125019U) + aNonceWordE;
            aOrbiterB = (aWandererA + RotL64(aIngress, 13U)) + 15737414920751551780U;
            aOrbiterD = ((aWandererJ + RotL64(aPrevious, 22U)) + 1357196111055783001U) + aNonceWordA;
            aOrbiterC = (aWandererG + RotL64(aScatter, 57U)) + 5315122321649251691U;
            aOrbiterI = ((((aWandererI + RotL64(aPrevious, 5U)) + RotL64(aCarry, 35U)) + 7893744655508595974U) + aOrbiterAssignSaltA[(((31U - aIndex) + 23U)) & S_SALT1]) + aNonceWordN;
            //
            aOrbiterG = ((aOrbiterG + aOrbiterF) + 16721939414324611738U) + aNonceWordG;
            aOrbiterA = (aOrbiterA ^ aOrbiterG) ^ 3444375866323610848U;
            aOrbiterA = RotL64((aOrbiterA * 10874157227815775661U), 57U);
            //
            aOrbiterK = ((aOrbiterK + aOrbiterE) + 1825716513674511632U) + aOrbiterUpdateSaltA[(((31U - aIndex) + 3U)) & S_SALT1];
            aOrbiterG = ((aOrbiterG ^ aOrbiterK) ^ 15582066843912467318U) ^ aOrbiterUpdateSaltC[(((31U - aIndex) + 19U)) & S_SALT1];
            aOrbiterG = RotL64((aOrbiterG * 12765146555943757373U), 51U);
            //
            aOrbiterF = ((aOrbiterF + aOrbiterB) + 15673590949193923915U) + aOrbiterUpdateSaltD[(((31U - aIndex) + 25U)) & S_SALT1];
            aOrbiterD = (aOrbiterD ^ aOrbiterF) ^ 13887365046280406413U;
            aOrbiterD = RotL64((aOrbiterD * 3169061375011420121U), 11U);
            //
            aOrbiterC = (aOrbiterC + aOrbiterA) + 12730414371734709356U;
            aOrbiterK = (aOrbiterK ^ aOrbiterC) ^ 4819112390640821927U;
            aOrbiterK = RotL64((aOrbiterK * 8782547948627685451U), 47U);
            //
            aOrbiterB = ((aOrbiterB + aOrbiterG) + 3089925954422937464U) + aNonceWordD;
            aOrbiterC = ((aOrbiterC ^ aOrbiterB) ^ 7180179304678622530U) ^ aOrbiterUpdateSaltF[((aIndex + 14U)) & S_SALT1];
            aOrbiterC = RotL64((aOrbiterC * 16118051565147747413U), 5U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterC) + 17030269962085008657U;
            aOrbiterI = ((aOrbiterI ^ aOrbiterD) ^ 6675917351883004046U) ^ aNonceWordL;
            aOrbiterI = RotL64((aOrbiterI * 14134335325316949687U), 35U);
            //
            aOrbiterE = (aOrbiterE + aOrbiterI) + 12572022803491077491U;
            aOrbiterF = (aOrbiterF ^ aOrbiterE) ^ 2801421744689267375U;
            aOrbiterF = RotL64((aOrbiterF * 315045745990934023U), 27U);
            //
            aOrbiterI = (aOrbiterI + aOrbiterK) + 4335148696780313055U;
            aOrbiterB = (aOrbiterB ^ aOrbiterI) ^ 12526298573395110141U;
            aOrbiterB = RotL64((aOrbiterB * 11276803410698178607U), 23U);
            //
            aOrbiterA = (aOrbiterA + aOrbiterD) + 6984239833558496091U;
            aOrbiterE = ((aOrbiterE ^ aOrbiterA) ^ 12195433952105336808U) ^ aNonceWordP;
            aOrbiterE = RotL64((aOrbiterE * 8642600547427664495U), 41U);
            //
            aIngress = aOrbiterI ^ RotL64(aOrbiterB, 56U);
            aIngress = aIngress + (RotL64(aOrbiterD, 23U) ^ aOrbiterK);
            aIngress = aIngress + (aOrbiterC ^ RotL64(aOrbiterG, 11U));
            aIngress = aIngress + (aOrbiterA ^ RotL64(aOrbiterF, 19U));
            aIngress = aIngress + RotL64(aOrbiterE, 5U);
            aIngress = TwistMix64::DiffuseB((aIngress + aScatter));
            //
            aWandererI = aWandererI + ((((RotL64(aScatter, 42U) + aOrbiterE) + RotL64(aOrbiterK, 52U)) + RotL64(aCarry, 3U)) + aWandererUpdateSaltD[(((31U - aIndex) + 27U)) & S_SALT1]);
            aWandererJ = aWandererJ ^ ((RotL64(aCross, 29U) + RotL64(aOrbiterB, 29U)) + aOrbiterA);
            aWandererD = aWandererD + (((RotL64(aIngress, 23U) + RotL64(aOrbiterE, 57U)) + aOrbiterC) + aNonceWordI);
            aWandererG = aWandererG ^ (((RotL64(aPrevious, 37U) + RotL64(aOrbiterK, 41U)) + aOrbiterD) + aWandererUpdateSaltC[(((31U - aIndex) + 29U)) & S_SALT1]);
            aWandererH = aWandererH + (((RotL64(aCross, 13U) + RotL64(aOrbiterG, 47U)) + aOrbiterK) + aNonceWordH);
            aWandererC = aWandererC ^ ((RotL64(aIngress, 48U) + RotL64(aOrbiterI, 6U)) + aOrbiterB);
            aWandererA = aWandererA + (((RotL64(aPrevious, 3U) + aOrbiterI) + RotL64(aOrbiterK, 19U)) + RotL64(aCarry, 53U));
            aWandererB = aWandererB ^ ((RotL64(aScatter, 57U) + aOrbiterE) + RotL64(aOrbiterI, 35U));
            aWandererK = aWandererK + ((RotL64(aPrevious, 19U) + aOrbiterG) + RotL64(aOrbiterF, 11U));
            //
            aCarry = aCarry + (aWandererD ^ RotL64(aWandererC, 57U));
            aCarry = aCarry + (aWandererI ^ RotL64(aWandererB, 34U));
            aCarry = aCarry + (aWandererJ ^ RotL64(aWandererA, 11U));
            aCarry = aCarry + (RotL64(aWandererG, 19U) ^ aWandererK);
            aCarry = aCarry + RotL64(aWandererH, 41U);
            aCarry = aCarry + RotL64(aIngress, 3U);
            aCarry = TwistMix64::DiffuseA(aCarry);
            //
            aFireLaneD[S_BLOCK1 - aIndex] = aIngress;
        }
    
        // kdf_a_loop_b loop 3
        // ingress from: aFireLaneD, aExpandLaneD, aExpandLaneC
        // ingress directions: aFireLaneD forward forced, aExpandLaneD forward forced, aExpandLaneC forward/backward random
        // cross from: aExpandLaneB, aFireLaneC
        // cross directions: aExpandLaneB backward forced, aFireLaneC backward/forward random
        // write to: aOperationLaneA
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aFireLaneD[((aIndex + 11370U)) & S_BLOCK1], 28U) ^ RotL64(aExpandLaneD[((aIndex + 13144U)) & S_BLOCK1], 47U));
            aIngress ^= RotL64(aExpandLaneC[((S_BLOCK1 - aIndex + 13356U)) & S_BLOCK1], 3U);
            aIngress = TwistMix64::DiffuseB(((aIngress ^ aDomainWordIngress) ^ aNonceWordB));
            //
            aCross = RotL64(aExpandLaneB[((S_BLOCK1 - aIndex + 15675U)) & S_BLOCK1], 10U) ^ RotL64(aFireLaneC[((S_BLOCK1 - aIndex + 15410U)) & S_BLOCK1], 21U);
            aCross = TwistMix64::DiffuseB(((aCross ^ aDomainWordCross) ^ aNonceWordG));
            //
            aScatter = (RotL64(aCarry, 23U) + RotL64(aPrevious, 53U)) ^ (RotL64(aIngress, 10U) + RotL64(aCross, 41U));
            aScatter = TwistMix64::DiffuseC(((aScatter ^ aDomainWordScatter) ^ aNonceWordG));
            //
            aOrbiterJ = ((aWandererC + RotL64(aCross, 23U)) + RotL64(aCarry, 57U)) + 15188686795415908074U;
            aOrbiterG = (aWandererA + RotL64(aIngress, 27U)) + 17310049041983079779U;
            aOrbiterB = ((aWandererD + RotL64(aScatter, 41U)) + 8246925977992441471U) + aOrbiterAssignSaltE[(((31U - aIndex) + 26U)) & S_SALT1];
            aOrbiterE = (aWandererB + RotL64(aPrevious, 46U)) + 8644260919918112781U;
            aOrbiterF = ((aWandererF + RotL64(aCross, 11U)) + 13401663736874819483U) + aNonceWordN;
            aOrbiterA = ((((aWandererK + RotL64(aPrevious, 35U)) + RotL64(aCarry, 11U)) + 7940358935238314973U) + aOrbiterAssignSaltF[((aIndex + 25U)) & S_SALT1]) + aNonceWordI;
            aOrbiterK = (((aWandererE + RotL64(aScatter, 3U)) + RotL64(aCarry, 37U)) + 13278990328548007839U) + aNonceWordJ;
            aOrbiterI = (aWandererI + RotL64(aIngress, 18U)) + 11346868298353840706U;
            aOrbiterD = (aWandererG + RotL64(aScatter, 53U)) + 2374077904806833579U;
            //
            aOrbiterJ = (aOrbiterJ + aOrbiterG) + 6978903378645019166U;
            aOrbiterB = ((aOrbiterB ^ aOrbiterJ) ^ 11951633297870965212U) ^ aOrbiterUpdateSaltE[((aIndex + 6U)) & S_SALT1];
            aOrbiterB = RotL64((aOrbiterB * 12778236598654492185U), 47U);
            //
            aOrbiterE = (aOrbiterE + aOrbiterJ) + 17398460995357409673U;
            aOrbiterF = (aOrbiterF ^ aOrbiterE) ^ 1215437945597836770U;
            aOrbiterF = RotL64((aOrbiterF * 9322970054123481621U), 57U);
            //
            aOrbiterA = (aOrbiterA + aOrbiterK) + 1878751468043972239U;
            aOrbiterJ = (aOrbiterJ ^ aOrbiterA) ^ 5343002808239712390U;
            aOrbiterJ = RotL64((aOrbiterJ * 11878640995447558811U), 19U);
            //
            aOrbiterF = (aOrbiterF + aOrbiterB) + 9884918450053276861U;
            aOrbiterI = (aOrbiterI ^ aOrbiterF) ^ 15894599082080422550U;
            aOrbiterI = RotL64((aOrbiterI * 8359936745539546131U), 43U);
            //
            aOrbiterK = (aOrbiterK + aOrbiterI) + 13917339232771145459U;
            aOrbiterG = (aOrbiterG ^ aOrbiterK) ^ 18101134009493720683U;
            aOrbiterG = RotL64((aOrbiterG * 15835859435306756387U), 13U);
            //
            aOrbiterB = (aOrbiterB + aOrbiterA) + 3830086372356903769U;
            aOrbiterE = ((aOrbiterE ^ aOrbiterB) ^ 15894394599564584010U) ^ aNonceWordK;
            aOrbiterE = RotL64((aOrbiterE * 9513921913446609263U), 23U);
            //
            aOrbiterI = ((aOrbiterI + aOrbiterE) + 5127590955274245812U) + aOrbiterUpdateSaltD[(((31U - aIndex) + 18U)) & S_SALT1];
            aOrbiterD = (((aOrbiterD ^ aOrbiterI) ^ 9410946933309720054U) ^ aOrbiterUpdateSaltC[((aIndex + 12U)) & S_SALT1]) ^ aNonceWordF;
            aOrbiterD = RotL64((aOrbiterD * 14507476989423060561U), 39U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterF) + 15544384157294987085U;
            aOrbiterK = ((aOrbiterK ^ aOrbiterD) ^ 998801294460434123U) ^ aOrbiterUpdateSaltA[((aIndex + 7U)) & S_SALT1];
            aOrbiterK = RotL64((aOrbiterK * 5946968142746472745U), 35U);
            //
            aOrbiterG = (aOrbiterG + aOrbiterD) + 16442095194965452163U;
            aOrbiterA = (aOrbiterA ^ aOrbiterG) ^ 14294936349037516932U;
            aOrbiterA = RotL64((aOrbiterA * 14655345374740882581U), 51U);
            //
            aIngress = aOrbiterA ^ RotL64(aOrbiterK, 10U);
            aIngress = aIngress + (RotL64(aOrbiterG, 23U) ^ aOrbiterE);
            aIngress = aIngress + (aOrbiterJ ^ RotL64(aOrbiterI, 19U));
            aIngress = aIngress + (aOrbiterF ^ RotL64(aOrbiterB, 13U));
            aIngress = aIngress + RotL64(aOrbiterD, 41U);
            aIngress = TwistMix64::DiffuseB((aIngress + aScatter));
            //
            aWandererB = aWandererB ^ ((RotL64(aScatter, 39U) + aOrbiterA) + RotL64(aOrbiterE, 53U));
            aWandererF = aWandererF + (((RotL64(aCross, 5U) + aOrbiterB) + RotL64(aOrbiterE, 24U)) + aWandererUpdateSaltA[(((31U - aIndex) + 27U)) & S_SALT1]);
            aWandererG = aWandererG ^ ((RotL64(aPrevious, 53U) + aOrbiterD) + RotL64(aOrbiterK, 19U));
            aWandererD = aWandererD + ((RotL64(aIngress, 22U) + RotL64(aOrbiterA, 29U)) + aOrbiterG);
            aWandererI = aWandererI ^ ((RotL64(aCross, 47U) + RotL64(aOrbiterG, 57U)) + aOrbiterJ);
            aWandererA = aWandererA + (((RotL64(aScatter, 57U) + aOrbiterB) + RotL64(aOrbiterF, 41U)) + RotL64(aCarry, 53U));
            aWandererE = aWandererE ^ (((RotL64(aIngress, 43U) + RotL64(aOrbiterK, 11U)) + aOrbiterI) + aNonceWordC);
            aWandererK = aWandererK + ((((RotL64(aPrevious, 13U) + aOrbiterK) + RotL64(aOrbiterJ, 34U)) + RotL64(aCarry, 5U)) + aNonceWordH);
            aWandererC = aWandererC ^ (((RotL64(aIngress, 18U) + aOrbiterG) + RotL64(aOrbiterI, 47U)) + aWandererUpdateSaltB[((aIndex + 24U)) & S_SALT1]);
            //
            aCarry = aCarry + (RotL64(aWandererA, 23U) ^ aWandererI);
            aCarry = aCarry + (aWandererG ^ RotL64(aWandererE, 10U));
            aCarry = aCarry + (RotL64(aWandererD, 13U) ^ aWandererB);
            aCarry = aCarry + (aWandererK ^ RotL64(aWandererC, 57U));
            aCarry = aCarry + RotL64(aWandererF, 39U);
            aCarry = aCarry + RotL64(aIngress, 19U);
            aCarry = TwistMix64::DiffuseA(aCarry);
            //
            aOperationLaneA[aIndex] = aIngress;
        }
    
        // kdf_a_loop_b loop 4
        // ingress from: aOperationLaneA, aExpandLaneC, aFireLaneC
        // ingress directions: aOperationLaneA forward forced, aExpandLaneC forward forced, aFireLaneC forward/backward random
        // cross from: aExpandLaneD, aFireLaneD
        // cross directions: aExpandLaneD backward forced, aFireLaneD backward/forward random
        // write to: aOperationLaneB
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aOperationLaneA[((aIndex + 17794U)) & S_BLOCK1], 39U) ^ RotL64(aExpandLaneC[((aIndex + 16842U)) & S_BLOCK1], 21U));
            aIngress ^= RotL64(aFireLaneC[((S_BLOCK1 - aIndex + 18204U)) & S_BLOCK1], 13U);
            aIngress = TwistMix64::DiffuseA(((aIngress ^ aDomainWordIngress) ^ aNonceWordA));
            //
            aCross = RotL64(aExpandLaneD[((S_BLOCK1 - aIndex + 18875U)) & S_BLOCK1], 13U) ^ RotL64(aFireLaneD[((S_BLOCK1 - aIndex + 18338U)) & S_BLOCK1], 50U);
            aCross = TwistMix64::DiffuseA(((aCross ^ aDomainWordCross) ^ aNonceWordF));
            //
            aScatter = (RotL64(aIngress, 23U) ^ RotL64(aCarry, 54U)) + (RotL64(aPrevious, 41U) + RotL64(aCross, 5U));
            aScatter = TwistMix64::DiffuseA(((aScatter ^ aDomainWordScatter) ^ aNonceWordM));
            //
            aOrbiterD = ((aWandererK + RotL64(aCross, 12U)) + 3199575576585871314U) + aNonceWordL;
            aOrbiterB = ((aWandererI + RotL64(aPrevious, 57U)) + 2533378188975571824U) + aNonceWordH;
            aOrbiterG = (aWandererC + RotL64(aScatter, 19U)) + 6819782112558312658U;
            aOrbiterF = ((aWandererD + RotL64(aIngress, 47U)) + RotL64(aCarry, 41U)) + 12690060987724798497U;
            aOrbiterC = (((aWandererJ + RotL64(aScatter, 43U)) + RotL64(aCarry, 19U)) + 7088375139715629606U) + aNonceWordB;
            aOrbiterE = ((aWandererB + RotL64(aPrevious, 37U)) + 17785618677423695666U) + aOrbiterAssignSaltC[((aIndex + 26U)) & S_SALT1];
            aOrbiterH = ((aWandererG + RotL64(aIngress, 28U)) + 1714999280296491277U) + aOrbiterAssignSaltD[(((31U - aIndex) + 21U)) & S_SALT1];
            aOrbiterJ = ((aWandererA + RotL64(aCross, 53U)) + RotL64(aCarry, 11U)) + 17611338506932491624U;
            aOrbiterA = (aWandererF + RotL64(aPrevious, 23U)) + 6475727359297421201U;
            //
            aOrbiterD = ((aOrbiterD + aOrbiterB) + 2347744591204119530U) + aOrbiterUpdateSaltF[((aIndex + 3U)) & S_SALT1];
            aOrbiterG = (aOrbiterG ^ aOrbiterD) ^ 2739317903351401068U;
            aOrbiterG = RotL64((aOrbiterG * 15435029315209475631U), 23U);
            //
            aOrbiterF = (aOrbiterF + aOrbiterC) + 8663535261373274338U;
            aOrbiterB = (aOrbiterB ^ aOrbiterF) ^ 8205245127823536479U;
            aOrbiterB = RotL64((aOrbiterB * 13857005110466856439U), 13U);
            //
            aOrbiterE = ((aOrbiterE + aOrbiterG) + 8916510616749754516U) + aOrbiterUpdateSaltB[(((31U - aIndex) + 8U)) & S_SALT1];
            aOrbiterH = (aOrbiterH ^ aOrbiterE) ^ 3944805940148512932U;
            aOrbiterH = RotL64((aOrbiterH * 18082271583211389701U), 35U);
            //
            aOrbiterJ = (aOrbiterJ + aOrbiterH) + 14094751253118853302U;
            aOrbiterF = (aOrbiterF ^ aOrbiterJ) ^ 14094299829196076311U;
            aOrbiterF = RotL64((aOrbiterF * 6370012560657108493U), 29U);
            //
            aOrbiterH = ((aOrbiterH + aOrbiterA) + 3940673811518673802U) + aNonceWordE;
            aOrbiterC = ((aOrbiterC ^ aOrbiterH) ^ 3015106523254484839U) ^ aNonceWordC;
            aOrbiterC = RotL64((aOrbiterC * 9655401190755573379U), 19U);
            //
            aOrbiterB = (aOrbiterB + aOrbiterE) + 15404103131982599922U;
            aOrbiterJ = (aOrbiterJ ^ aOrbiterB) ^ 1828655763233900875U;
            aOrbiterJ = RotL64((aOrbiterJ * 13024358077740310049U), 51U);
            //
            aOrbiterA = (aOrbiterA + aOrbiterF) + 1236981890899916502U;
            aOrbiterD = ((aOrbiterD ^ aOrbiterA) ^ 18208975564570342697U) ^ aOrbiterUpdateSaltE[((aIndex + 11U)) & S_SALT1];
            aOrbiterD = RotL64((aOrbiterD * 4577109989465876801U), 47U);
            //
            aOrbiterG = (aOrbiterG + aOrbiterJ) + 17882273895471449661U;
            aOrbiterA = (aOrbiterA ^ aOrbiterG) ^ 16196010765612713713U;
            aOrbiterA = RotL64((aOrbiterA * 15624856645134182005U), 43U);
            //
            aOrbiterC = (aOrbiterC + aOrbiterD) + 14639250100311162559U;
            aOrbiterE = ((aOrbiterE ^ aOrbiterC) ^ 9139027997336903273U) ^ aOrbiterUpdateSaltA[((aIndex + 14U)) & S_SALT1];
            aOrbiterE = RotL64((aOrbiterE * 1853126389565574293U), 5U);
            //
            aIngress = RotL64(aOrbiterD, 19U) ^ aOrbiterB;
            aIngress = aIngress + (aOrbiterA ^ RotL64(aOrbiterJ, 37U));
            aIngress = aIngress + (aOrbiterC ^ RotL64(aOrbiterE, 14U));
            aIngress = aIngress + (aOrbiterG ^ RotL64(aOrbiterH, 53U));
            aIngress = aIngress + RotL64(aOrbiterF, 11U);
            aIngress = TwistMix64::DiffuseC((aIngress + aScatter));
            //
            aWandererK = aWandererK ^ ((RotL64(aScatter, 14U) + aOrbiterJ) + RotL64(aOrbiterC, 4U));
            aWandererD = aWandererD + (((RotL64(aIngress, 5U) + aOrbiterB) + RotL64(aOrbiterD, 47U)) + RotL64(aCarry, 35U));
            aWandererI = aWandererI ^ (((RotL64(aPrevious, 57U) + aOrbiterH) + RotL64(aOrbiterC, 21U)) + aNonceWordG);
            aWandererB = aWandererB + ((((RotL64(aCross, 53U) + RotL64(aOrbiterH, 53U)) + aOrbiterJ) + RotL64(aCarry, 43U)) + aNonceWordK);
            aWandererG = aWandererG ^ ((RotL64(aPrevious, 43U) + RotL64(aOrbiterA, 57U)) + aOrbiterG);
            aWandererC = aWandererC + (((RotL64(aCross, 29U) + aOrbiterE) + RotL64(aOrbiterD, 10U)) + aWandererUpdateSaltF[(((31U - aIndex) + 18U)) & S_SALT1]);
            aWandererJ = aWandererJ ^ (((RotL64(aIngress, 34U) + RotL64(aOrbiterF, 41U)) + aOrbiterD) + aWandererUpdateSaltE[(((31U - aIndex) + 23U)) & S_SALT1]);
            aWandererF = aWandererF + (((RotL64(aScatter, 21U) + RotL64(aOrbiterA, 37U)) + aOrbiterD) + aNonceWordO);
            aWandererA = aWandererA ^ (((RotL64(aCross, 47U) + aOrbiterA) + RotL64(aOrbiterC, 27U)) + aNonceWordI);
            //
            aCarry = aCarry + (RotL64(aWandererF, 19U) ^ aWandererA);
            aCarry = aCarry + (RotL64(aWandererB, 54U) ^ aWandererG);
            aCarry = aCarry + (RotL64(aWandererC, 37U) ^ aWandererJ);
            aCarry = aCarry + (aWandererK ^ RotL64(aWandererI, 5U));
            aCarry = aCarry + RotL64(aWandererD, 47U);
            aCarry = aCarry + RotL64(aIngress, 41U);
            aCarry = TwistMix64::DiffuseB(aCarry);
            //
            aOperationLaneB[S_BLOCK1 - aIndex] = aIngress;
        }
    
        // kdf_a_loop_b loop 5
        // ingress from: aOperationLaneB, aFireLaneD
        // ingress directions: aOperationLaneB forward forced, aFireLaneD forward/backward random
        // cross from: aOperationLaneA, aExpandLaneA
        // cross directions: aOperationLaneA backward forced, aExpandLaneA backward/forward random
        // write to: aOperationLaneC
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = RotL64(aOperationLaneB[((aIndex + 22749U)) & S_BLOCK1], 10U) ^ RotL64(aFireLaneD[((aIndex + 21908U)) & S_BLOCK1], 53U);
            aIngress = TwistMix64::DiffuseA(((aIngress ^ aDomainWordIngress) ^ aNonceWordE));
            //
            aCross = RotL64(aOperationLaneA[((S_BLOCK1 - aIndex + 23939U)) & S_BLOCK1], 11U) ^ RotL64(aExpandLaneA[((aIndex + 26216U)) & S_BLOCK1], 29U);
            aCross = TwistMix64::DiffuseA(((aCross ^ aDomainWordCross) ^ aNonceWordO));
            //
            aScatter = (RotL64(aIngress, 39U) ^ RotL64(aCross, 5U)) ^ (RotL64(aPrevious, 52U) + RotL64(aCarry, 23U));
            aScatter = TwistMix64::DiffuseB(((aScatter ^ aDomainWordScatter) ^ aNonceWordO));
            //
            aOrbiterI = ((aWandererG + RotL64(aPrevious, 34U)) + RotL64(aCarry, 47U)) + 12046647397183218524U;
            aOrbiterA = ((aWandererK + RotL64(aCross, 19U)) + 2760779375026461991U) + aOrbiterAssignSaltB[(((31U - aIndex) + 20U)) & S_SALT1];
            aOrbiterD = (((aWandererI + RotL64(aScatter, 57U)) + 13735454443176855650U) + aOrbiterAssignSaltA[(((31U - aIndex) + 9U)) & S_SALT1]) + aNonceWordB;
            aOrbiterF = ((aWandererH + RotL64(aIngress, 13U)) + 4370377000586647724U) + aNonceWordL;
            aOrbiterG = ((aWandererA + RotL64(aScatter, 43U)) + RotL64(aCarry, 3U)) + 14566322384189969094U;
            aOrbiterE = (((aWandererJ + RotL64(aCross, 51U)) + RotL64(aCarry, 57U)) + 5056565959818422786U) + aNonceWordD;
            aOrbiterH = (aWandererE + RotL64(aPrevious, 27U)) + 8795403810686579209U;
            aOrbiterK = ((aWandererF + RotL64(aIngress, 6U)) + 9625947666256011567U) + aNonceWordF;
            aOrbiterB = (aWandererB + RotL64(aPrevious, 39U)) + 1703669290934254701U;
            //
            aOrbiterI = ((aOrbiterI + aOrbiterA) + 6664070663184147951U) + aNonceWordP;
            aOrbiterD = (aOrbiterD ^ aOrbiterI) ^ 2104148316797553431U;
            aOrbiterD = RotL64((aOrbiterD * 12887842067180975983U), 13U);
            //
            aOrbiterF = (aOrbiterF + aOrbiterG) + 1197910004222596145U;
            aOrbiterI = (aOrbiterI ^ aOrbiterF) ^ 9922977170060903197U;
            aOrbiterI = RotL64((aOrbiterI * 13047828062605568603U), 3U);
            //
            aOrbiterE = (aOrbiterE + aOrbiterD) + 2048376210852567829U;
            aOrbiterG = ((aOrbiterG ^ aOrbiterE) ^ 12568990647075931409U) ^ aOrbiterUpdateSaltD[(((31U - aIndex) + 4U)) & S_SALT1];
            aOrbiterG = RotL64((aOrbiterG * 9860242601194210927U), 23U);
            //
            aOrbiterH = (aOrbiterH + aOrbiterI) + 15026894775772902751U;
            aOrbiterE = ((aOrbiterE ^ aOrbiterH) ^ 3439447160137900629U) ^ aNonceWordJ;
            aOrbiterE = RotL64((aOrbiterE * 1813754963043785165U), 53U);
            //
            aOrbiterK = ((aOrbiterK + aOrbiterF) + 6532671388552829796U) + aNonceWordN;
            aOrbiterH = ((aOrbiterH ^ aOrbiterK) ^ 17261098369835997661U) ^ aOrbiterUpdateSaltF[((aIndex + 3U)) & S_SALT1];
            aOrbiterH = RotL64((aOrbiterH * 568292591215203521U), 27U);
            //
            aOrbiterB = ((aOrbiterB + aOrbiterE) + 3171300991007459947U) + aOrbiterUpdateSaltE[(((31U - aIndex) + 29U)) & S_SALT1];
            aOrbiterF = (aOrbiterF ^ aOrbiterB) ^ 5935563269327662024U;
            aOrbiterF = RotL64((aOrbiterF * 11271790283157765003U), 35U);
            //
            aOrbiterA = (aOrbiterA + aOrbiterH) + 14290941734320455612U;
            aOrbiterB = (aOrbiterB ^ aOrbiterA) ^ 12371794745736518824U;
            aOrbiterB = RotL64((aOrbiterB * 12208762336145168647U), 41U);
            //
            aOrbiterG = (aOrbiterG + aOrbiterK) + 8782840145467637373U;
            aOrbiterA = (aOrbiterA ^ aOrbiterG) ^ 4067525421190366741U;
            aOrbiterA = RotL64((aOrbiterA * 6671002797916227485U), 57U);
            //
            aOrbiterD = ((aOrbiterD + aOrbiterB) + 11854812920571789853U) + aOrbiterUpdateSaltC[((aIndex + 23U)) & S_SALT1];
            aOrbiterK = (aOrbiterK ^ aOrbiterD) ^ 17564890418553131451U;
            aOrbiterK = RotL64((aOrbiterK * 16657184504366731805U), 19U);
            //
            aIngress = aOrbiterF ^ RotL64(aOrbiterH, 13U);
            aIngress = aIngress + (RotL64(aOrbiterE, 37U) ^ aOrbiterB);
            aIngress = aIngress + (aOrbiterA ^ RotL64(aOrbiterD, 57U));
            aIngress = aIngress + (aOrbiterK ^ RotL64(aOrbiterG, 50U));
            aIngress = aIngress + RotL64(aOrbiterI, 19U);
            aIngress = TwistMix64::DiffuseC((aIngress + aScatter));
            //
            aWandererB = aWandererB + (((RotL64(aScatter, 24U) + RotL64(aOrbiterF, 22U)) + aOrbiterA) + RotL64(aCarry, 35U));
            aWandererI = aWandererI ^ (((RotL64(aIngress, 47U) + RotL64(aOrbiterG, 57U)) + aOrbiterF) + aNonceWordC);
            aWandererG = aWandererG + (((RotL64(aCross, 35U) + aOrbiterG) + RotL64(aOrbiterI, 11U)) + RotL64(aCarry, 13U));
            aWandererH = aWandererH ^ ((RotL64(aPrevious, 19U) + RotL64(aOrbiterH, 53U)) + aOrbiterA);
            aWandererA = aWandererA + (((RotL64(aScatter, 57U) + RotL64(aOrbiterE, 35U)) + aOrbiterB) + aWandererUpdateSaltD[(((31U - aIndex) + 17U)) & S_SALT1]);
            aWandererK = aWandererK ^ (((RotL64(aIngress, 10U) + aOrbiterH) + RotL64(aOrbiterK, 5U)) + aWandererUpdateSaltC[(((31U - aIndex) + 10U)) & S_SALT1]);
            aWandererF = aWandererF + (((RotL64(aCross, 5U) + RotL64(aOrbiterB, 47U)) + aOrbiterA) + aNonceWordI);
            aWandererJ = aWandererJ ^ (((RotL64(aPrevious, 29U) + RotL64(aOrbiterD, 43U)) + aOrbiterK) + aNonceWordM);
            aWandererE = aWandererE + ((RotL64(aScatter, 41U) + aOrbiterG) + RotL64(aOrbiterK, 30U));
            //
            aCarry = aCarry + (aWandererH ^ RotL64(aWandererF, 29U));
            aCarry = aCarry + (RotL64(aWandererK, 35U) ^ aWandererJ);
            aCarry = aCarry + (RotL64(aWandererG, 13U) ^ aWandererA);
            aCarry = aCarry + (RotL64(aWandererB, 23U) ^ aWandererE);
            aCarry = aCarry + RotL64(aWandererI, 44U);
            aCarry = aCarry + RotL64(aIngress, 51U);
            aCarry = TwistMix64::DiffuseA(aCarry);
            //
            aOperationLaneC[aIndex] = aIngress;
        }
    
        // kdf_a_loop_b loop 6
        // ingress from: aOperationLaneC, aOperationLaneA
        // ingress directions: aOperationLaneC forward forced, aOperationLaneA forward/backward random
        // cross from: aOperationLaneB, aExpandLaneB
        // cross directions: aOperationLaneB backward forced, aExpandLaneB backward/forward random
        // write to: aOperationLaneD
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = RotL64(aOperationLaneC[((aIndex + 28266U)) & S_BLOCK1], 41U) ^ RotL64(aOperationLaneA[((aIndex + 28099U)) & S_BLOCK1], 5U);
            aIngress = TwistMix64::DiffuseB(((aIngress ^ aDomainWordIngress) ^ aNonceWordN));
            //
            aCross = RotL64(aOperationLaneB[((S_BLOCK1 - aIndex + 28609U)) & S_BLOCK1], 14U) ^ RotL64(aExpandLaneB[((S_BLOCK1 - aIndex + 27602U)) & S_BLOCK1], 29U);
            aCross = TwistMix64::DiffuseB(((aCross ^ aDomainWordCross) ^ aNonceWordC));
            //
            aScatter = (RotL64(aCarry, 19U) + RotL64(aPrevious, 6U)) + (RotL64(aCross, 35U) ^ RotL64(aIngress, 57U));
            aScatter = TwistMix64::DiffuseC(((aScatter ^ aDomainWordScatter) ^ aNonceWordK));
            //
            aOrbiterH = (((aWandererD + RotL64(aScatter, 53U)) + 4848316479321533394U) + aOrbiterAssignSaltE[(((31U - aIndex) + 12U)) & S_SALT1]) + aNonceWordK;
            aOrbiterI = (aWandererB + RotL64(aCross, 38U)) + 6919360256662636195U;
            aOrbiterK = ((aWandererC + RotL64(aPrevious, 47U)) + 9897013582181108544U) + aOrbiterAssignSaltF[((aIndex + 5U)) & S_SALT1];
            aOrbiterE = (aWandererF + RotL64(aIngress, 43U)) + 7319353809896158678U;
            aOrbiterC = ((aWandererE + RotL64(aScatter, 11U)) + RotL64(aCarry, 51U)) + 2848175435514849859U;
            aOrbiterB = ((aWandererJ + RotL64(aCross, 57U)) + RotL64(aCarry, 41U)) + 6967780718720437934U;
            aOrbiterG = (aWandererG + RotL64(aPrevious, 23U)) + 10143884766603388136U;
            aOrbiterA = ((aWandererH + RotL64(aIngress, 6U)) + 8675965006150972051U) + aNonceWordL;
            aOrbiterD = (((aWandererK + RotL64(aPrevious, 19U)) + RotL64(aCarry, 23U)) + 16350117755560994281U) + aNonceWordH;
            //
            aOrbiterH = (aOrbiterH + aOrbiterI) + 17976597517118423760U;
            aOrbiterK = ((aOrbiterK ^ aOrbiterH) ^ 1399631141355370237U) ^ aOrbiterUpdateSaltD[(((31U - aIndex) + 4U)) & S_SALT1];
            aOrbiterK = RotL64((aOrbiterK * 16537788276543236833U), 47U);
            //
            aOrbiterI = (aOrbiterI + aOrbiterE) + 3590613762034716792U;
            aOrbiterC = (aOrbiterC ^ aOrbiterI) ^ 5134624314245932157U;
            aOrbiterC = RotL64((aOrbiterC * 13077589037975283371U), 39U);
            //
            aOrbiterB = ((aOrbiterB + aOrbiterG) + 10082236952942943654U) + aNonceWordG;
            aOrbiterH = ((aOrbiterH ^ aOrbiterB) ^ 4015535035905433450U) ^ aNonceWordD;
            aOrbiterH = RotL64((aOrbiterH * 4961808568701908559U), 53U);
            //
            aOrbiterK = ((aOrbiterK + aOrbiterC) + 611474103801573800U) + aNonceWordI;
            aOrbiterG = (aOrbiterG ^ aOrbiterK) ^ 5786708483794098001U;
            aOrbiterG = RotL64((aOrbiterG * 7694007039340089267U), 5U);
            //
            aOrbiterC = (aOrbiterC + aOrbiterA) + 5201943497363274455U;
            aOrbiterD = (aOrbiterD ^ aOrbiterC) ^ 9282160506938328489U;
            aOrbiterD = RotL64((aOrbiterD * 5368182164239021367U), 29U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterB) + 4932320527498940158U;
            aOrbiterE = ((aOrbiterE ^ aOrbiterD) ^ 11576526341731392916U) ^ aNonceWordM;
            aOrbiterE = RotL64((aOrbiterE * 1712051774729439363U), 57U);
            //
            aOrbiterA = (aOrbiterA + aOrbiterK) + 10790691517638887125U;
            aOrbiterB = (aOrbiterB ^ aOrbiterA) ^ 16280649213607464422U;
            aOrbiterB = RotL64((aOrbiterB * 10756733801499471873U), 43U);
            //
            aOrbiterG = ((aOrbiterG + aOrbiterD) + 9553716940667712810U) + aOrbiterUpdateSaltA[((aIndex + 27U)) & S_SALT1];
            aOrbiterI = (aOrbiterI ^ aOrbiterG) ^ 11827518270964003341U;
            aOrbiterI = RotL64((aOrbiterI * 1322489827908132831U), 35U);
            //
            aOrbiterE = ((aOrbiterE + aOrbiterH) + 16777463701235809321U) + aOrbiterUpdateSaltC[(((31U - aIndex) + 29U)) & S_SALT1];
            aOrbiterA = ((aOrbiterA ^ aOrbiterE) ^ 3375489084588454149U) ^ aOrbiterUpdateSaltE[((aIndex + 9U)) & S_SALT1];
            aOrbiterA = RotL64((aOrbiterA * 3335010977457647307U), 19U);
            //
            aIngress = RotL64(aOrbiterC, 19U) ^ aOrbiterA;
            aIngress = aIngress + (RotL64(aOrbiterK, 39U) ^ aOrbiterG);
            aIngress = aIngress + (RotL64(aOrbiterI, 29U) ^ aOrbiterE);
            aIngress = aIngress + (aOrbiterB ^ RotL64(aOrbiterH, 48U));
            aIngress = aIngress + RotL64(aOrbiterD, 53U);
            aIngress = TwistMix64::DiffuseB((aIngress + aScatter));
            //
            aWandererH = aWandererH + (((RotL64(aCross, 57U) + RotL64(aOrbiterD, 47U)) + aOrbiterC) + RotL64(aCarry, 51U));
            aWandererD = aWandererD ^ (((RotL64(aIngress, 35U) + aOrbiterD) + RotL64(aOrbiterI, 11U)) + aNonceWordJ);
            aWandererJ = aWandererJ + (((RotL64(aPrevious, 5U) + RotL64(aOrbiterH, 4U)) + aOrbiterA) + aNonceWordP);
            aWandererC = aWandererC ^ ((RotL64(aScatter, 30U) + aOrbiterB) + RotL64(aOrbiterD, 29U));
            aWandererF = aWandererF + ((RotL64(aIngress, 43U) + aOrbiterD) + RotL64(aOrbiterK, 53U));
            aWandererK = aWandererK ^ ((RotL64(aScatter, 21U) + RotL64(aOrbiterH, 43U)) + aOrbiterG);
            aWandererB = aWandererB + (((RotL64(aPrevious, 47U) + RotL64(aOrbiterH, 20U)) + aOrbiterK) + aWandererUpdateSaltA[(((31U - aIndex) + 3U)) & S_SALT1]);
            aWandererG = aWandererG ^ (((RotL64(aCross, 52U) + RotL64(aOrbiterE, 57U)) + aOrbiterB) + aNonceWordE);
            aWandererE = aWandererE + ((((RotL64(aScatter, 13U) + aOrbiterC) + RotL64(aOrbiterK, 39U)) + RotL64(aCarry, 43U)) + aWandererUpdateSaltB[((aIndex + 14U)) & S_SALT1]);
            //
            aCarry = aCarry + (aWandererG ^ RotL64(aWandererJ, 27U));
            aCarry = aCarry + (RotL64(aWandererK, 53U) ^ aWandererH);
            aCarry = aCarry + (aWandererF ^ RotL64(aWandererC, 47U));
            aCarry = aCarry + (RotL64(aWandererD, 14U) ^ aWandererE);
            aCarry = aCarry + RotL64(aWandererB, 3U);
            aCarry = aCarry + RotL64(aIngress, 41U);
            aCarry = TwistMix64::DiffuseA(aCarry);
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

void TwistExpander_Greezy_Arx::KDF_A_C(TwistWorkSpace *pWorkSpace,
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
    std::uint64_t aOrbiterE = 0; std::uint64_t aOrbiterG = 0; std::uint64_t aOrbiterI = 0; std::uint64_t aOrbiterJ = 0;

    // [kdf-a arx]
    std::uint64_t aNonceWordA = TwistMix64::DiffuseA(pNonce * 0xB24207007CD6264FULL + 0xAA051BFDB9DBBB4DULL);
    std::uint64_t aNonceWordB = TwistMix64::DiffuseA(pNonce * 0xD80777DD54059BD1ULL + 0xB50A16CF9194CB32ULL);
    std::uint64_t aNonceWordC = TwistMix64::DiffuseB(pNonce * 0x8DC85AE681EDB765ULL + 0xED8D2061CF876E62ULL);
    std::uint64_t aNonceWordD = TwistMix64::DiffuseC(pNonce * 0x96992EF19ECD57FDULL + 0x841955D62B54FEE3ULL);
    std::uint64_t aNonceWordE = TwistMix64::DiffuseB(pNonce * 0x8492658EABA4110DULL + 0x949822DA3A2147EEULL);
    std::uint64_t aNonceWordF = TwistMix64::DiffuseA(pNonce * 0xD9C4D2C527A2643FULL + 0xB33784350D90E7A4ULL);
    std::uint64_t aNonceWordG = TwistMix64::DiffuseB(pNonce * 0xB6C786A59C0C6431ULL + 0xE3B6975E7862D148ULL);
    std::uint64_t aNonceWordH = TwistMix64::DiffuseB(pNonce * 0xDD283DA7E1CDAE25ULL + 0xBB7DE4C24F20740EULL);
    std::uint64_t aNonceWordI = TwistMix64::DiffuseA(pNonce * 0xF3EC27A3A0D97E15ULL + 0xEF14147A4BAF850FULL);
    std::uint64_t aNonceWordJ = TwistMix64::DiffuseC(pNonce * 0x8EC72EEC07A30BD7ULL + 0xF81C2224D028F518ULL);
    std::uint64_t aNonceWordK = TwistMix64::DiffuseB(pNonce * 0xDFAB42F83E9C6EF7ULL + 0xB49151F8198BDB97ULL);
    std::uint64_t aNonceWordL = TwistMix64::DiffuseC(pNonce * 0x846B2FC7BA59699BULL + 0xEB12D525E22B66AFULL);
    std::uint64_t aNonceWordM = TwistMix64::DiffuseC(pNonce * 0xCC2E5FC5C72326F7ULL + 0x887967E4E4A8662FULL);
    std::uint64_t aNonceWordN = TwistMix64::DiffuseA(pNonce * 0xCC905303345654E9ULL + 0xF56C281835D89C30ULL);
    std::uint64_t aNonceWordO = TwistMix64::DiffuseA(pNonce * 0xA861A72371F7FF13ULL + 0x88F67F010B8341DFULL);
    std::uint64_t aNonceWordP = TwistMix64::DiffuseC(pNonce * 0xBC6CB534FC6DDFD9ULL + 0x93CA4FFA68C1217AULL);
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
        // read from: aOperationLaneA, aOperationLaneB, aFireLaneA, aOperationLaneC, aOperationLaneD, aFireLaneB, aWorkLaneA, aFireLaneC, aFireLaneD, aWorkLaneB, aExpandLaneA, aExpandLaneB, aWorkLaneC, aExpandLaneC, aExpandLaneD
        // write to: aWorkLaneA, aWorkLaneB, aWorkLaneC, aWorkLaneD
    
        // kdf_a_loop_c loop 1
        // ingress from: aOperationLaneA, aOperationLaneB, aFireLaneA
        // ingress directions: aOperationLaneA forward forced, aOperationLaneB forward forced, aFireLaneA forward/backward random
        // cross from: aOperationLaneC, aOperationLaneD, aFireLaneB
        // cross directions: aOperationLaneC backward forced, aOperationLaneD backward forced, aFireLaneB backward/forward random
        // write to: aWorkLaneA
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aOperationLaneA[((aIndex + 308U)) & S_BLOCK1], 52U) ^ RotL64(aOperationLaneB[((aIndex + 867U)) & S_BLOCK1], 37U));
            aIngress ^= RotL64(aFireLaneA[((aIndex + 7657U)) & S_BLOCK1], 5U);
            aIngress = TwistMix64::DiffuseB(((aIngress ^ aDomainWordIngress) ^ aNonceWordO));
            //
            aCross = (RotL64(aOperationLaneC[((S_BLOCK1 - aIndex + 2013U)) & S_BLOCK1], 37U) ^ RotL64(aOperationLaneD[((S_BLOCK1 - aIndex + 8110U)) & S_BLOCK1], 50U));
            aCross ^= RotL64(aFireLaneB[((aIndex + 2014U)) & S_BLOCK1], 5U);
            aCross = TwistMix64::DiffuseA(((aCross ^ aDomainWordCross) ^ aNonceWordI));
            //
            aScatter = (RotL64(aIngress, 47U) ^ RotL64(aCross, 19U)) + (RotL64(aPrevious, 6U) ^ RotL64(aCarry, 35U));
            aScatter = TwistMix64::DiffuseC(((aScatter ^ aDomainWordScatter) ^ aNonceWordN));
            //
            aOrbiterI = (aWandererH + RotL64(aScatter, 27U)) + 6068543441070417854U;
            aOrbiterE = ((aWandererI + RotL64(aIngress, 46U)) + RotL64(aCarry, 41U)) + 2995980468193441856U;
            aOrbiterB = ((aWandererC + RotL64(aPrevious, 35U)) + RotL64(aCarry, 53U)) + 18020277482171594003U;
            aOrbiterG = (((aWandererA + RotL64(aCross, 3U)) + 4293807434721230702U) + aOrbiterAssignSaltF[((aIndex + 29U)) & S_SALT1]) + aNonceWordN;
            aOrbiterJ = ((((aWandererE + RotL64(aScatter, 19U)) + RotL64(aCarry, 11U)) + 7980599111583893156U) + aOrbiterAssignSaltC[((aIndex + 12U)) & S_SALT1]) + aNonceWordM;
            //
            aOrbiterI = ((aOrbiterI + aOrbiterE) + 8593141111851052016U) + aNonceWordK;
            aOrbiterB = ((aOrbiterB ^ aOrbiterI) ^ 5903487523900084325U) ^ aOrbiterUpdateSaltA[(((31U - aIndex) + 27U)) & S_SALT1];
            aOrbiterB = RotL64((aOrbiterB * 2508618861111356699U), 11U);
            //
            aOrbiterG = ((aOrbiterG + aOrbiterI) + 15112035513447930209U) + aOrbiterUpdateSaltC[((aIndex + 17U)) & S_SALT1];
            aOrbiterE = ((aOrbiterE ^ aOrbiterG) ^ 9854037263057006439U) ^ aNonceWordG;
            aOrbiterE = RotL64((aOrbiterE * 396276470208637283U), 57U);
            //
            aOrbiterJ = ((aOrbiterJ + aOrbiterG) + 16759760289688823193U) + aOrbiterUpdateSaltD[(((31U - aIndex) + 23U)) & S_SALT1];
            aOrbiterI = (aOrbiterI ^ aOrbiterJ) ^ 12622628933030601390U;
            aOrbiterI = RotL64((aOrbiterI * 2151912984825538321U), 29U);
            //
            aOrbiterB = (aOrbiterB + aOrbiterJ) + 1264668857268123425U;
            aOrbiterG = ((aOrbiterG ^ aOrbiterB) ^ 16302812053619101593U) ^ aOrbiterUpdateSaltE[(((31U - aIndex) + 18U)) & S_SALT1];
            aOrbiterG = RotL64((aOrbiterG * 18291400055836111547U), 19U);
            //
            aOrbiterE = (aOrbiterE + aOrbiterB) + 16087995784896123610U;
            aOrbiterJ = (aOrbiterJ ^ aOrbiterE) ^ 7970269262800468363U;
            aOrbiterJ = RotL64((aOrbiterJ * 14924752223305807461U), 41U);
            //
            aIngress = aOrbiterJ ^ RotL64(aOrbiterI, 23U);
            aIngress = aIngress + (RotL64(aOrbiterG, 3U) ^ aOrbiterE);
            aIngress = aIngress + RotL64(aOrbiterB, 13U);
            aIngress = TwistMix64::DiffuseB((aIngress + aScatter));
            //
            aWandererC = aWandererC + (((RotL64(aIngress, 48U) + RotL64(aOrbiterI, 29U)) + aOrbiterB) + RotL64(aCarry, 47U));
            aWandererA = aWandererA ^ ((((RotL64(aCross, 57U) + aOrbiterG) + RotL64(aOrbiterE, 39U)) + aNonceWordF) + aWandererUpdateSaltA[((aIndex + 22U)) & S_SALT1]);
            aWandererE = aWandererE + (((RotL64(aPrevious, 39U) + RotL64(aOrbiterB, 11U)) + aOrbiterG) + aNonceWordA);
            aWandererI = aWandererI ^ ((((RotL64(aScatter, 23U) + RotL64(aOrbiterE, 48U)) + aOrbiterJ) + aNonceWordD) + aWandererUpdateSaltE[((aIndex + 26U)) & S_SALT1]);
            aWandererH = aWandererH + (((RotL64(aPrevious, 11U) + aOrbiterE) + RotL64(aOrbiterB, 21U)) + RotL64(aCarry, 13U));
            //
            aCarry = aCarry + (aWandererC ^ RotL64(aWandererH, 21U));
            aCarry = aCarry + (RotL64(aWandererI, 44U) ^ aWandererE);
            aCarry = aCarry + RotL64(aWandererA, 11U);
            aCarry = aCarry + RotL64(aIngress, 57U);
            aCarry = TwistMix64::DiffuseA(aCarry);
            //
            aWorkLaneA[aIndex] = aIngress;
        }
    
        // kdf_a_loop_c loop 2
        // ingress from: aWorkLaneA, aOperationLaneC, aOperationLaneD, aFireLaneC
        // ingress directions: aWorkLaneA forward forced, aOperationLaneC forward forced, aOperationLaneD forward forced, aFireLaneC forward/backward random
        // cross from: aOperationLaneA, aOperationLaneB, aFireLaneD
        // cross directions: aOperationLaneA backward forced, aOperationLaneB backward forced, aFireLaneD backward/forward random
        // write to: aWorkLaneB
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aWorkLaneA[((aIndex + 15391U)) & S_BLOCK1], 11U) ^ RotL64(aOperationLaneC[((aIndex + 9750U)) & S_BLOCK1], 27U));
            aIngress ^= (RotL64(aOperationLaneD[((aIndex + 13175U)) & S_BLOCK1], 56U) ^ RotL64(aFireLaneC[((S_BLOCK1 - aIndex + 10806U)) & S_BLOCK1], 39U));
            aIngress = TwistMix64::DiffuseB(((aIngress ^ aDomainWordIngress) ^ aNonceWordM));
            //
            aCross = (RotL64(aOperationLaneA[((S_BLOCK1 - aIndex + 13736U)) & S_BLOCK1], 13U) ^ RotL64(aOperationLaneB[((S_BLOCK1 - aIndex + 14545U)) & S_BLOCK1], 21U));
            aCross ^= RotL64(aFireLaneD[((aIndex + 10567U)) & S_BLOCK1], 35U);
            aCross = TwistMix64::DiffuseC(((aCross ^ aDomainWordCross) ^ aNonceWordN));
            //
            aScatter = (RotL64(aIngress, 41U) ^ RotL64(aCross, 3U)) + (RotL64(aCarry, 53U) ^ RotL64(aPrevious, 28U));
            aScatter = TwistMix64::DiffuseC(((aScatter ^ aDomainWordScatter) ^ aNonceWordD));
            //
            aOrbiterG = ((((aWandererJ + RotL64(aPrevious, 5U)) + RotL64(aCarry, 53U)) + 2617613537256538553U) + aOrbiterAssignSaltE[((aIndex + 14U)) & S_SALT1]) + aNonceWordB;
            aOrbiterJ = (aWandererK + RotL64(aScatter, 14U)) + 16642868916835132715U;
            aOrbiterE = ((aWandererA + RotL64(aIngress, 39U)) + 10860291124337073254U) + aOrbiterAssignSaltB[((aIndex + 27U)) & S_SALT1];
            aOrbiterI = (((aWandererI + RotL64(aCross, 51U)) + RotL64(aCarry, 39U)) + 6432511273906902472U) + aNonceWordA;
            aOrbiterC = (((aWandererH + RotL64(aScatter, 27U)) + RotL64(aCarry, 23U)) + 7505375005848241910U) + aNonceWordF;
            //
            aOrbiterG = (aOrbiterG + aOrbiterJ) + 11086616004678821329U;
            aOrbiterE = (aOrbiterE ^ aOrbiterG) ^ 3298830587569881951U;
            aOrbiterE = RotL64((aOrbiterE * 4304047944073454489U), 29U);
            //
            aOrbiterJ = (((aOrbiterJ + aOrbiterI) + 9775143140064220979U) + aOrbiterUpdateSaltB[((aIndex + 23U)) & S_SALT1]) + aNonceWordL;
            aOrbiterC = ((aOrbiterC ^ aOrbiterJ) ^ 4147601326580823120U) ^ aNonceWordE;
            aOrbiterC = RotL64((aOrbiterC * 13462244678782260871U), 47U);
            //
            aOrbiterC = ((aOrbiterC + aOrbiterG) + 12245920269898100415U) + aNonceWordI;
            aOrbiterI = (aOrbiterI ^ aOrbiterC) ^ 8391940489176734499U;
            aOrbiterI = RotL64((aOrbiterI * 9119606167674098007U), 39U);
            //
            aOrbiterE = (aOrbiterE + aOrbiterC) + 17876893379544668477U;
            aOrbiterJ = ((aOrbiterJ ^ aOrbiterE) ^ 18301882058180370541U) ^ aOrbiterUpdateSaltE[(((31U - aIndex) + 6U)) & S_SALT1];
            aOrbiterJ = RotL64((aOrbiterJ * 16680384667098921309U), 5U);
            //
            aOrbiterI = ((aOrbiterI + aOrbiterE) + 6869225862715140102U) + aOrbiterUpdateSaltA[(((31U - aIndex) + 11U)) & S_SALT1];
            aOrbiterG = ((aOrbiterG ^ aOrbiterI) ^ 15404118372589259800U) ^ aOrbiterUpdateSaltF[((aIndex + 12U)) & S_SALT1];
            aOrbiterG = RotL64((aOrbiterG * 5766851935950389915U), 19U);
            //
            aIngress = RotL64(aOrbiterE, 23U) ^ aOrbiterC;
            aIngress = aIngress + (RotL64(aOrbiterI, 52U) ^ aOrbiterG);
            aIngress = aIngress + RotL64(aOrbiterJ, 13U);
            aIngress = TwistMix64::DiffuseB((aIngress + aScatter));
            //
            aWandererJ = aWandererJ ^ ((((RotL64(aIngress, 19U) + aOrbiterJ) + RotL64(aOrbiterE, 57U)) + aNonceWordP) + aWandererUpdateSaltF[(((31U - aIndex) + 15U)) & S_SALT1]);
            aWandererI = aWandererI + ((((RotL64(aPrevious, 5U) + aOrbiterE) + RotL64(aOrbiterI, 3U)) + RotL64(aCarry, 11U)) + aWandererUpdateSaltB[(((31U - aIndex) + 3U)) & S_SALT1]);
            aWandererK = aWandererK ^ (((RotL64(aCross, 29U) + RotL64(aOrbiterC, 12U)) + aOrbiterG) + aNonceWordH);
            aWandererA = aWandererA + ((((RotL64(aScatter, 51U) + RotL64(aOrbiterJ, 47U)) + aOrbiterG) + RotL64(aCarry, 41U)) + aNonceWordK);
            aWandererH = aWandererH ^ ((RotL64(aPrevious, 38U) + RotL64(aOrbiterI, 27U)) + aOrbiterJ);
            //
            aCarry = aCarry + (aWandererJ ^ RotL64(aWandererI, 41U));
            aCarry = aCarry + (RotL64(aWandererH, 3U) ^ aWandererK);
            aCarry = aCarry + RotL64(aWandererA, 12U);
            aCarry = aCarry + RotL64(aIngress, 29U);
            aCarry = TwistMix64::DiffuseC(aCarry);
            //
            aWorkLaneB[S_BLOCK1 - aIndex] = aIngress;
        }
    
        // kdf_a_loop_c loop 3
        // ingress from: aWorkLaneB, aOperationLaneA, aOperationLaneB, aExpandLaneA
        // ingress directions: aWorkLaneB forward forced, aOperationLaneA forward forced, aOperationLaneB forward forced, aExpandLaneA forward/backward random
        // cross from: aWorkLaneA, aOperationLaneC, aExpandLaneB
        // cross directions: aWorkLaneA backward forced, aOperationLaneC backward forced, aExpandLaneB backward/forward random
        // write to: aWorkLaneC
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aWorkLaneB[((aIndex + 20059U)) & S_BLOCK1], 23U) ^ RotL64(aOperationLaneA[((aIndex + 22842U)) & S_BLOCK1], 43U));
            aIngress ^= (RotL64(aOperationLaneB[((aIndex + 19370U)) & S_BLOCK1], 11U) ^ RotL64(aExpandLaneA[((S_BLOCK1 - aIndex + 21427U)) & S_BLOCK1], 35U));
            aIngress = TwistMix64::DiffuseC(((aIngress ^ aDomainWordIngress) ^ aNonceWordN));
            //
            aCross = (RotL64(aWorkLaneA[((S_BLOCK1 - aIndex + 24457U)) & S_BLOCK1], 39U) ^ RotL64(aOperationLaneC[((S_BLOCK1 - aIndex + 21182U)) & S_BLOCK1], 19U));
            aCross ^= RotL64(aExpandLaneB[((aIndex + 24041U)) & S_BLOCK1], 53U);
            aCross = TwistMix64::DiffuseB(((aCross ^ aDomainWordCross) ^ aNonceWordE));
            //
            aScatter = (RotL64(aCarry, 39U) ^ RotL64(aPrevious, 27U)) + (RotL64(aIngress, 11U) ^ RotL64(aCross, 54U));
            aScatter = TwistMix64::DiffuseA(((aScatter ^ aDomainWordScatter) ^ aNonceWordF));
            //
            aOrbiterG = (((aWandererE + RotL64(aCross, 19U)) + RotL64(aCarry, 13U)) + 13499155707765393469U) + aNonceWordD;
            aOrbiterC = (((aWandererI + RotL64(aIngress, 27U)) + 3740324981823726185U) + aOrbiterAssignSaltA[((aIndex + 13U)) & S_SALT1]) + aNonceWordP;
            aOrbiterI = ((((aWandererH + RotL64(aPrevious, 43U)) + RotL64(aCarry, 51U)) + 5470765363949735652U) + aOrbiterAssignSaltD[(((31U - aIndex) + 5U)) & S_SALT1]) + aNonceWordG;
            aOrbiterD = ((aWandererC + RotL64(aScatter, 52U)) + RotL64(aCarry, 27U)) + 3446436171274452326U;
            aOrbiterA = ((aWandererF + RotL64(aPrevious, 3U)) + 1778929412631211933U) + aNonceWordI;
            //
            aOrbiterG = (((aOrbiterG + aOrbiterC) + 14666308799855220954U) + aOrbiterUpdateSaltF[((aIndex + 23U)) & S_SALT1]) + aNonceWordB;
            aOrbiterI = (aOrbiterI ^ aOrbiterG) ^ 4548410236791175055U;
            aOrbiterI = RotL64((aOrbiterI * 6822908616815218501U), 41U);
            //
            aOrbiterC = (aOrbiterC + aOrbiterI) + 5829739767694190372U;
            aOrbiterD = ((aOrbiterD ^ aOrbiterC) ^ 14319231414903675748U) ^ aOrbiterUpdateSaltB[(((31U - aIndex) + 10U)) & S_SALT1];
            aOrbiterD = RotL64((aOrbiterD * 4966501102515775601U), 19U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterA) + 1513851750246111405U;
            aOrbiterG = ((aOrbiterG ^ aOrbiterD) ^ 1685620217748986019U) ^ aNonceWordH;
            aOrbiterG = RotL64((aOrbiterG * 9286548037413609445U), 5U);
            //
            aOrbiterA = ((aOrbiterA + aOrbiterG) + 16284162182006054402U) + aNonceWordJ;
            aOrbiterC = ((aOrbiterC ^ aOrbiterA) ^ 6271539598462003309U) ^ aOrbiterUpdateSaltE[(((31U - aIndex) + 21U)) & S_SALT1];
            aOrbiterC = RotL64((aOrbiterC * 13923286694131331137U), 51U);
            //
            aOrbiterI = (aOrbiterI + aOrbiterD) + 12669312437565969473U;
            aOrbiterA = (((aOrbiterA ^ aOrbiterI) ^ 11894755313393001665U) ^ aOrbiterUpdateSaltD[((aIndex + 12U)) & S_SALT1]) ^ aNonceWordL;
            aOrbiterA = RotL64((aOrbiterA * 12556759675372354075U), 27U);
            //
            aIngress = RotL64(aOrbiterC, 14U) ^ aOrbiterD;
            aIngress = aIngress + (aOrbiterA ^ RotL64(aOrbiterI, 57U));
            aIngress = aIngress + RotL64(aOrbiterG, 43U);
            aIngress = TwistMix64::DiffuseC((aIngress + aScatter));
            //
            aWandererE = aWandererE + (((RotL64(aScatter, 43U) + aOrbiterC) + RotL64(aOrbiterD, 37U)) + aNonceWordF);
            aWandererH = aWandererH ^ ((((RotL64(aPrevious, 13U) + RotL64(aOrbiterC, 19U)) + aOrbiterG) + aNonceWordM) + aWandererUpdateSaltD[((aIndex + 14U)) & S_SALT1]);
            aWandererI = aWandererI + ((((RotL64(aCross, 57U) + RotL64(aOrbiterD, 29U)) + aOrbiterI) + RotL64(aCarry, 43U)) + aWandererUpdateSaltC[(((31U - aIndex) + 15U)) & S_SALT1]);
            aWandererF = aWandererF ^ (((RotL64(aIngress, 34U) + RotL64(aOrbiterG, 4U)) + aOrbiterA) + aNonceWordO);
            aWandererC = aWandererC + ((((RotL64(aPrevious, 3U) + aOrbiterD) + RotL64(aOrbiterA, 47U)) + RotL64(aCarry, 23U)) + aNonceWordA);
            //
            aCarry = aCarry + (RotL64(aWandererH, 29U) ^ aWandererI);
            aCarry = aCarry + (RotL64(aWandererC, 5U) ^ aWandererF);
            aCarry = aCarry + RotL64(aWandererE, 41U);
            aCarry = aCarry + RotL64(aIngress, 13U);
            aCarry = TwistMix64::DiffuseA(aCarry);
            //
            aWorkLaneC[aIndex] = aIngress;
        }
    
        // kdf_a_loop_c loop 4
        // ingress from: aWorkLaneC, aWorkLaneA, aOperationLaneD, aExpandLaneC
        // ingress directions: aWorkLaneC forward forced, aWorkLaneA forward forced, aOperationLaneD forward forced, aExpandLaneC forward/backward random
        // cross from: aWorkLaneB, aOperationLaneB, aExpandLaneD
        // cross directions: aWorkLaneB backward forced, aOperationLaneB backward forced, aExpandLaneD backward/forward random
        // write to: aWorkLaneD
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aWorkLaneC[((aIndex + 26013U)) & S_BLOCK1], 27U) ^ RotL64(aWorkLaneA[((aIndex + 32768U)) & S_BLOCK1], 3U));
            aIngress ^= (RotL64(aOperationLaneD[((aIndex + 27880U)) & S_BLOCK1], 35U) ^ RotL64(aExpandLaneC[((S_BLOCK1 - aIndex + 26252U)) & S_BLOCK1], 52U));
            aIngress = TwistMix64::DiffuseA(((aIngress ^ aDomainWordIngress) ^ aNonceWordD));
            //
            aCross = (RotL64(aWorkLaneB[((S_BLOCK1 - aIndex + 29158U)) & S_BLOCK1], 13U) ^ RotL64(aOperationLaneB[((S_BLOCK1 - aIndex + 32596U)) & S_BLOCK1], 29U));
            aCross ^= RotL64(aExpandLaneD[((S_BLOCK1 - aIndex + 32183U)) & S_BLOCK1], 52U);
            aCross = TwistMix64::DiffuseA(((aCross ^ aDomainWordCross) ^ aNonceWordC));
            //
            aScatter = (RotL64(aCross, 41U) ^ RotL64(aIngress, 5U)) + (RotL64(aCarry, 22U) + RotL64(aPrevious, 57U));
            aScatter = TwistMix64::DiffuseC(((aScatter ^ aDomainWordScatter) ^ aNonceWordK));
            //
            aOrbiterE = ((aWandererF + RotL64(aCross, 48U)) + RotL64(aCarry, 47U)) + 2177539223979303669U;
            aOrbiterJ = (((aWandererB + RotL64(aPrevious, 27U)) + RotL64(aCarry, 11U)) + 3962004686551521471U) + aNonceWordE;
            aOrbiterG = (((aWandererI + RotL64(aScatter, 5U)) + RotL64(aCarry, 27U)) + 8457602312617147662U) + aNonceWordI;
            aOrbiterC = ((aWandererK + RotL64(aIngress, 37U)) + 18011802451816510632U) + aOrbiterAssignSaltC[(((31U - aIndex) + 27U)) & S_SALT1];
            aOrbiterA = ((aWandererC + RotL64(aCross, 13U)) + 9046101759168876832U) + aOrbiterAssignSaltF[((aIndex + 24U)) & S_SALT1];
            //
            aOrbiterE = ((aOrbiterE + aOrbiterJ) + 11135620637431969597U) + aNonceWordB;
            aOrbiterG = ((aOrbiterG ^ aOrbiterE) ^ 15913029940697999701U) ^ aOrbiterUpdateSaltF[(((31U - aIndex) + 4U)) & S_SALT1];
            aOrbiterG = RotL64((aOrbiterG * 646524659942693491U), 57U);
            //
            aOrbiterG = (aOrbiterG + aOrbiterC) + 16304193109948135982U;
            aOrbiterA = (aOrbiterA ^ aOrbiterG) ^ 13208892298820080981U;
            aOrbiterA = RotL64((aOrbiterA * 15093751072618884859U), 23U);
            //
            aOrbiterA = ((aOrbiterA + aOrbiterE) + 4182377898949419225U) + aOrbiterUpdateSaltD[((aIndex + 15U)) & S_SALT1];
            aOrbiterJ = ((aOrbiterJ ^ aOrbiterA) ^ 13970137023071326151U) ^ aNonceWordM;
            aOrbiterJ = RotL64((aOrbiterJ * 9075061559681739865U), 5U);
            //
            aOrbiterC = ((aOrbiterC + aOrbiterA) + 8402396284835248583U) + aOrbiterUpdateSaltE[((aIndex + 21U)) & S_SALT1];
            aOrbiterE = (((aOrbiterE ^ aOrbiterC) ^ 8859190834060657829U) ^ aOrbiterUpdateSaltC[(((31U - aIndex) + 26U)) & S_SALT1]) ^ aNonceWordL;
            aOrbiterE = RotL64((aOrbiterE * 13552418608113716117U), 13U);
            //
            aOrbiterJ = ((aOrbiterJ + aOrbiterG) + 9760005337757990392U) + aNonceWordN;
            aOrbiterC = (aOrbiterC ^ aOrbiterJ) ^ 14108277760135744897U;
            aOrbiterC = RotL64((aOrbiterC * 4474681104256093885U), 47U);
            //
            aIngress = aOrbiterG ^ RotL64(aOrbiterA, 13U);
            aIngress = aIngress + (RotL64(aOrbiterJ, 58U) ^ aOrbiterE);
            aIngress = aIngress + RotL64(aOrbiterC, 47U);
            aIngress = TwistMix64::DiffuseC((aIngress + aScatter));
            //
            aWandererC = aWandererC + ((((RotL64(aScatter, 3U) + RotL64(aOrbiterA, 43U)) + aOrbiterE) + RotL64(aCarry, 51U)) + aNonceWordJ);
            aWandererI = aWandererI ^ (((RotL64(aCross, 57U) + RotL64(aOrbiterC, 11U)) + aOrbiterG) + aWandererUpdateSaltE[((aIndex + 6U)) & S_SALT1]);
            aWandererB = aWandererB + (((RotL64(aIngress, 35U) + aOrbiterG) + RotL64(aOrbiterE, 3U)) + RotL64(aCarry, 5U));
            aWandererK = aWandererK ^ (((RotL64(aPrevious, 27U) + RotL64(aOrbiterE, 57U)) + aOrbiterJ) + aNonceWordP);
            aWandererF = aWandererF + ((((RotL64(aCross, 48U) + RotL64(aOrbiterC, 24U)) + aOrbiterA) + aNonceWordO) + aWandererUpdateSaltA[((aIndex + 14U)) & S_SALT1]);
            //
            aCarry = aCarry + (RotL64(aWandererF, 53U) ^ aWandererB);
            aCarry = aCarry + (RotL64(aWandererC, 35U) ^ aWandererI);
            aCarry = aCarry + RotL64(aWandererK, 44U);
            aCarry = aCarry + RotL64(aIngress, 3U);
            aCarry = TwistMix64::DiffuseC(aCarry);
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

void TwistExpander_Greezy_Arx::KDF_A_D(TwistWorkSpace *pWorkSpace,
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
    std::uint64_t aNonceWordA = TwistMix64::DiffuseC(pNonce * 0xAB2E54C9690A361BULL + 0xE7787B94630859A3ULL);
    std::uint64_t aNonceWordB = TwistMix64::DiffuseC(pNonce * 0xD38DCE793AA3C2A5ULL + 0xB2177EFB0AF53296ULL);
    std::uint64_t aNonceWordC = TwistMix64::DiffuseB(pNonce * 0xEDD826C2EB499597ULL + 0x9476D4F12813D9D7ULL);
    std::uint64_t aNonceWordD = TwistMix64::DiffuseC(pNonce * 0xE5B538D5A9F32993ULL + 0x904407ECB0276371ULL);
    std::uint64_t aNonceWordE = TwistMix64::DiffuseB(pNonce * 0xB854C87DF21741EFULL + 0xD1689D9A2CB3F7A8ULL);
    std::uint64_t aNonceWordF = TwistMix64::DiffuseA(pNonce * 0xB41CF08F13709EB7ULL + 0xA76C58E11A586A7FULL);
    std::uint64_t aNonceWordG = TwistMix64::DiffuseC(pNonce * 0xDC252869A42B96CDULL + 0xF571C8CF0C5D66A6ULL);
    std::uint64_t aNonceWordH = TwistMix64::DiffuseB(pNonce * 0xE385CBD802BD448BULL + 0x998B3FC91FD64C72ULL);
    std::uint64_t aNonceWordI = TwistMix64::DiffuseA(pNonce * 0xD5FD82A6E31B4CADULL + 0xDE4B4A9E241B975EULL);
    std::uint64_t aNonceWordJ = TwistMix64::DiffuseC(pNonce * 0xDF07153E096C28C7ULL + 0xB41343F03597DC13ULL);
    std::uint64_t aNonceWordK = TwistMix64::DiffuseC(pNonce * 0x88FFDE9B84600A03ULL + 0xE61DA605ECC2638CULL);
    std::uint64_t aNonceWordL = TwistMix64::DiffuseA(pNonce * 0xAECF0FC70A2BB46BULL + 0xA8CD5F10174052DBULL);
    std::uint64_t aNonceWordM = TwistMix64::DiffuseB(pNonce * 0xE5D637688B856ABBULL + 0xBEF5BC7336F2971EULL);
    std::uint64_t aNonceWordN = TwistMix64::DiffuseA(pNonce * 0x99059936C972C1DFULL + 0xDEF5B190F8E36544ULL);
    std::uint64_t aNonceWordO = TwistMix64::DiffuseC(pNonce * 0x94DCF708379A399FULL + 0x82E4C0AE51EC8605ULL);
    std::uint64_t aNonceWordP = TwistMix64::DiffuseB(pNonce * 0xD6BB50F5C8AD0B0FULL + 0x9CAB7AD0CBD18923ULL);
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
        // read from: aExpandLaneA, aExpandLaneB, aFireLaneA, aExpandLaneC, aExpandLaneD, aFireLaneB, aWorkLaneA, aFireLaneC, aFireLaneD, aWorkLaneB, aOperationLaneA, aOperationLaneB, aWorkLaneC, aOperationLaneC, aOperationLaneD
        // write to: aWorkLaneA, aWorkLaneB, aWorkLaneC, aWorkLaneD
    
        // kdf_a_loop_d loop 1
        // ingress from: aExpandLaneA, aExpandLaneB, aFireLaneA
        // ingress directions: aExpandLaneA forward forced, aExpandLaneB forward forced, aFireLaneA forward/backward random
        // cross from: aExpandLaneC, aExpandLaneD, aFireLaneB
        // cross directions: aExpandLaneC backward forced, aExpandLaneD backward forced, aFireLaneB backward/forward random
        // write to: aWorkLaneA
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aExpandLaneA[((aIndex + 219U)) & S_BLOCK1], 51U) ^ RotL64(aExpandLaneB[((aIndex + 277U)) & S_BLOCK1], 24U));
            aIngress ^= RotL64(aFireLaneA[((S_BLOCK1 - aIndex + 5441U)) & S_BLOCK1], 13U);
            aIngress = TwistMix64::DiffuseA(((aIngress ^ aDomainWordIngress) ^ aNonceWordC));
            //
            aCross = (RotL64(aExpandLaneC[((S_BLOCK1 - aIndex + 2643U)) & S_BLOCK1], 43U) ^ RotL64(aExpandLaneD[((S_BLOCK1 - aIndex + 4466U)) & S_BLOCK1], 53U));
            aCross ^= RotL64(aFireLaneB[((aIndex + 7365U)) & S_BLOCK1], 27U);
            aCross = TwistMix64::DiffuseB(((aCross ^ aDomainWordCross) ^ aNonceWordP));
            //
            aScatter = (RotL64(aIngress, 6U) ^ RotL64(aCross, 23U)) + (RotL64(aCarry, 57U) ^ RotL64(aPrevious, 43U));
            aScatter = TwistMix64::DiffuseA(((aScatter ^ aDomainWordScatter) ^ aNonceWordJ));
            //
            aOrbiterD = (((aWandererI + RotL64(aScatter, 35U)) + RotL64(aCarry, 21U)) + 4739486756133131180U) + aOrbiterAssignSaltF[(((31U - aIndex) + 11U)) & S_SALT1];
            aOrbiterF = (aWandererA + RotL64(aCross, 41U)) + 16089707555501328184U;
            aOrbiterE = (((aWandererB + RotL64(aPrevious, 53U)) + RotL64(aCarry, 53U)) + 15310047330238536453U) + aNonceWordE;
            aOrbiterC = ((aWandererE + RotL64(aIngress, 12U)) + 7901411596386834955U) + aNonceWordA;
            aOrbiterA = ((aWandererF + RotL64(aCross, 5U)) + RotL64(aCarry, 39U)) + 4357555491060982163U;
            aOrbiterB = (((aWandererC + RotL64(aIngress, 47U)) + 15667085602825720102U) + aOrbiterAssignSaltC[(((31U - aIndex) + 17U)) & S_SALT1]) + aNonceWordB;
            aOrbiterG = ((aWandererK + RotL64(aScatter, 29U)) + 8520635334382269253U) + aNonceWordG;
            //
            aOrbiterD = (aOrbiterD + aOrbiterF) + 1772509779231068315U;
            aOrbiterE = (aOrbiterE ^ aOrbiterD) ^ 15336170957886025677U;
            aOrbiterE = RotL64((aOrbiterE * 10996880551392077399U), 21U);
            //
            aOrbiterC = ((aOrbiterC + aOrbiterA) + 8628770833489469980U) + aOrbiterUpdateSaltE[((aIndex + 18U)) & S_SALT1];
            aOrbiterD = (aOrbiterD ^ aOrbiterC) ^ 15469234024247246228U;
            aOrbiterD = RotL64((aOrbiterD * 8905266995119987947U), 3U);
            //
            aOrbiterB = ((aOrbiterB + aOrbiterE) + 10796430900884288328U) + aOrbiterUpdateSaltB[((aIndex + 22U)) & S_SALT1];
            aOrbiterC = ((aOrbiterC ^ aOrbiterB) ^ 10660110397012853289U) ^ aOrbiterUpdateSaltC[((aIndex + 29U)) & S_SALT1];
            aOrbiterC = RotL64((aOrbiterC * 9140007610912037461U), 35U);
            //
            aOrbiterA = (aOrbiterA + aOrbiterB) + 11202284258711214794U;
            aOrbiterF = (aOrbiterF ^ aOrbiterA) ^ 17509491802893182994U;
            aOrbiterF = RotL64((aOrbiterF * 9329107599972703671U), 27U);
            //
            aOrbiterF = (aOrbiterF + aOrbiterC) + 16212572740740103554U;
            aOrbiterG = ((aOrbiterG ^ aOrbiterF) ^ 2190030203761579226U) ^ aNonceWordN;
            aOrbiterG = RotL64((aOrbiterG * 3101886685668871045U), 11U);
            //
            aOrbiterE = ((aOrbiterE + aOrbiterG) + 12014337082293041909U) + aOrbiterUpdateSaltA[((aIndex + 24U)) & S_SALT1];
            aOrbiterA = ((aOrbiterA ^ aOrbiterE) ^ 3733531010807001506U) ^ aNonceWordJ;
            aOrbiterA = RotL64((aOrbiterA * 5797362244066062299U), 57U);
            //
            aOrbiterG = (aOrbiterG + aOrbiterD) + 7100994963061975529U;
            aOrbiterB = (aOrbiterB ^ aOrbiterG) ^ 17837541162838600258U;
            aOrbiterB = RotL64((aOrbiterB * 8745987361678166553U), 47U);
            //
            aIngress = aOrbiterB ^ RotL64(aOrbiterG, 19U);
            aIngress = aIngress + (aOrbiterE ^ RotL64(aOrbiterD, 5U));
            aIngress = aIngress + (RotL64(aOrbiterA, 28U) ^ aOrbiterF);
            aIngress = aIngress + RotL64(aOrbiterC, 57U);
            aIngress = TwistMix64::DiffuseC((aIngress + aScatter));
            //
            aWandererB = aWandererB + (((((RotL64(aScatter, 12U) + RotL64(aOrbiterA, 21U)) + aOrbiterE) + RotL64(aCarry, 23U)) + aNonceWordI) + aWandererUpdateSaltA[((aIndex + 4U)) & S_SALT1]);
            aWandererA = aWandererA ^ (((RotL64(aPrevious, 21U) + aOrbiterC) + RotL64(aOrbiterA, 35U)) + aNonceWordL);
            aWandererF = aWandererF + ((RotL64(aIngress, 5U) + RotL64(aOrbiterA, 5U)) + aOrbiterF);
            aWandererC = aWandererC ^ ((RotL64(aCross, 27U) + RotL64(aOrbiterD, 27U)) + aOrbiterF);
            aWandererK = aWandererK + ((((RotL64(aPrevious, 35U) + RotL64(aOrbiterB, 51U)) + aOrbiterA) + RotL64(aCarry, 5U)) + aNonceWordF);
            aWandererI = aWandererI ^ (((RotL64(aIngress, 51U) + aOrbiterC) + RotL64(aOrbiterF, 57U)) + aWandererUpdateSaltD[(((31U - aIndex) + 12U)) & S_SALT1]);
            aWandererE = aWandererE + ((RotL64(aCross, 43U) + RotL64(aOrbiterG, 42U)) + aOrbiterA);
            //
            aCarry = aCarry + (aWandererC ^ RotL64(aWandererF, 19U));
            aCarry = aCarry + (aWandererB ^ RotL64(aWandererA, 12U));
            aCarry = aCarry + (RotL64(aWandererE, 3U) ^ aWandererI);
            aCarry = aCarry + RotL64(aWandererK, 29U);
            aCarry = aCarry + RotL64(aIngress, 37U);
            aCarry = TwistMix64::DiffuseA(aCarry);
            //
            aWorkLaneA[aIndex] = aIngress;
        }
    
        // kdf_a_loop_d loop 2
        // ingress from: aWorkLaneA, aExpandLaneC, aExpandLaneD, aFireLaneC
        // ingress directions: aWorkLaneA forward forced, aExpandLaneC forward forced, aExpandLaneD forward forced, aFireLaneC forward/backward random
        // cross from: aExpandLaneA, aExpandLaneB, aFireLaneD
        // cross directions: aExpandLaneA backward forced, aExpandLaneB backward forced, aFireLaneD backward/forward random
        // write to: aWorkLaneB
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aWorkLaneA[((aIndex + 9475U)) & S_BLOCK1], 22U) ^ RotL64(aExpandLaneC[((aIndex + 12080U)) & S_BLOCK1], 51U));
            aIngress ^= (RotL64(aExpandLaneD[((aIndex + 15447U)) & S_BLOCK1], 3U) ^ RotL64(aFireLaneC[((aIndex + 12548U)) & S_BLOCK1], 43U));
            aIngress = TwistMix64::DiffuseB(((aIngress ^ aDomainWordIngress) ^ aNonceWordD));
            //
            aCross = (RotL64(aExpandLaneA[((S_BLOCK1 - aIndex + 11402U)) & S_BLOCK1], 43U) ^ RotL64(aExpandLaneB[((S_BLOCK1 - aIndex + 11524U)) & S_BLOCK1], 27U));
            aCross ^= RotL64(aFireLaneD[((S_BLOCK1 - aIndex + 15814U)) & S_BLOCK1], 14U);
            aCross = TwistMix64::DiffuseB(((aCross ^ aDomainWordCross) ^ aNonceWordM));
            //
            aScatter = (RotL64(aCross, 39U) + RotL64(aPrevious, 20U)) ^ (RotL64(aCarry, 3U) + RotL64(aIngress, 51U));
            aScatter = TwistMix64::DiffuseC(((aScatter ^ aDomainWordScatter) ^ aNonceWordO));
            //
            aOrbiterE = ((aWandererH + RotL64(aIngress, 53U)) + 8604208734152026945U) + aOrbiterAssignSaltD[((aIndex + 5U)) & S_SALT1];
            aOrbiterJ = (aWandererG + RotL64(aPrevious, 35U)) + 1374329953253889829U;
            aOrbiterI = ((aWandererA + RotL64(aScatter, 27U)) + 5779278910548228339U) + aOrbiterAssignSaltB[((aIndex + 23U)) & S_SALT1];
            aOrbiterD = (((aWandererD + RotL64(aCross, 5U)) + RotL64(aCarry, 11U)) + 17670451230882805140U) + aNonceWordF;
            aOrbiterC = ((aWandererB + RotL64(aIngress, 21U)) + RotL64(aCarry, 57U)) + 8193848740764866860U;
            aOrbiterG = (((aWandererE + RotL64(aScatter, 13U)) + RotL64(aCarry, 41U)) + 15801168428145650104U) + aNonceWordH;
            aOrbiterK = ((aWandererC + RotL64(aPrevious, 46U)) + 2584718176087499066U) + aNonceWordG;
            //
            aOrbiterE = (aOrbiterE + aOrbiterJ) + 14950366247822737997U;
            aOrbiterI = (aOrbiterI ^ aOrbiterE) ^ 9779293225265670135U;
            aOrbiterI = RotL64((aOrbiterI * 11625969538497982117U), 5U);
            //
            aOrbiterD = ((aOrbiterD + aOrbiterC) + 8688968319288372383U) + aOrbiterUpdateSaltE[((aIndex + 28U)) & S_SALT1];
            aOrbiterJ = ((aOrbiterJ ^ aOrbiterD) ^ 13665723186950342601U) ^ aNonceWordK;
            aOrbiterJ = RotL64((aOrbiterJ * 292035540396910837U), 11U);
            //
            aOrbiterG = ((aOrbiterG + aOrbiterD) + 9395428688359973510U) + aOrbiterUpdateSaltD[(((31U - aIndex) + 15U)) & S_SALT1];
            aOrbiterE = (aOrbiterE ^ aOrbiterG) ^ 2152719218018108418U;
            aOrbiterE = RotL64((aOrbiterE * 15271961483518392671U), 29U);
            //
            aOrbiterJ = (aOrbiterJ + aOrbiterK) + 1350324137411377992U;
            aOrbiterG = (aOrbiterG ^ aOrbiterJ) ^ 8729317951386057921U;
            aOrbiterG = RotL64((aOrbiterG * 6008790836417785083U), 21U);
            //
            aOrbiterC = (aOrbiterC + aOrbiterE) + 6317310451893678411U;
            aOrbiterK = ((aOrbiterK ^ aOrbiterC) ^ 10175620379041384281U) ^ aNonceWordO;
            aOrbiterK = RotL64((aOrbiterK * 14079679617394330781U), 35U);
            //
            aOrbiterK = ((aOrbiterK + aOrbiterI) + 1203082119358827708U) + aOrbiterUpdateSaltF[(((31U - aIndex) + 9U)) & S_SALT1];
            aOrbiterD = ((aOrbiterD ^ aOrbiterK) ^ 523869107818193101U) ^ aNonceWordB;
            aOrbiterD = RotL64((aOrbiterD * 4629501113595689157U), 41U);
            //
            aOrbiterI = ((aOrbiterI + aOrbiterG) + 4028324959540432983U) + aOrbiterUpdateSaltC[(((31U - aIndex) + 3U)) & S_SALT1];
            aOrbiterC = ((aOrbiterC ^ aOrbiterI) ^ 15447631947468213912U) ^ aNonceWordN;
            aOrbiterC = RotL64((aOrbiterC * 6037306615787729185U), 51U);
            //
            aIngress = RotL64(aOrbiterJ, 21U) ^ aOrbiterI;
            aIngress = aIngress + (RotL64(aOrbiterK, 37U) ^ aOrbiterC);
            aIngress = aIngress + (aOrbiterD ^ RotL64(aOrbiterG, 3U));
            aIngress = aIngress + RotL64(aOrbiterE, 47U);
            aIngress = TwistMix64::DiffuseB((aIngress + aScatter));
            //
            aWandererB = aWandererB + ((((RotL64(aIngress, 35U) + RotL64(aOrbiterE, 23U)) + aOrbiterG) + aNonceWordJ) + aWandererUpdateSaltB[((aIndex + 7U)) & S_SALT1]);
            aWandererA = aWandererA ^ (((RotL64(aCross, 3U) + RotL64(aOrbiterK, 5U)) + aOrbiterI) + aNonceWordA);
            aWandererD = aWandererD + ((((RotL64(aPrevious, 27U) + RotL64(aOrbiterD, 57U)) + aOrbiterI) + RotL64(aCarry, 3U)) + aNonceWordP);
            aWandererC = aWandererC ^ (((RotL64(aScatter, 10U) + RotL64(aOrbiterG, 29U)) + aOrbiterJ) + aWandererUpdateSaltF[(((31U - aIndex) + 20U)) & S_SALT1]);
            aWandererH = aWandererH + ((RotL64(aIngress, 21U) + aOrbiterK) + RotL64(aOrbiterD, 51U));
            aWandererE = aWandererE ^ ((RotL64(aPrevious, 47U) + aOrbiterE) + RotL64(aOrbiterC, 37U));
            aWandererG = aWandererG + (((RotL64(aCross, 41U) + RotL64(aOrbiterG, 12U)) + aOrbiterI) + RotL64(aCarry, 19U));
            //
            aCarry = aCarry + (RotL64(aWandererB, 12U) ^ aWandererA);
            aCarry = aCarry + (aWandererG ^ RotL64(aWandererD, 43U));
            aCarry = aCarry + (aWandererC ^ RotL64(aWandererE, 47U));
            aCarry = aCarry + RotL64(aWandererH, 3U);
            aCarry = aCarry + RotL64(aIngress, 51U);
            aCarry = TwistMix64::DiffuseB(aCarry);
            //
            aWorkLaneB[S_BLOCK1 - aIndex] = aIngress;
        }
    
        // kdf_a_loop_d loop 3
        // ingress from: aWorkLaneB, aExpandLaneA, aExpandLaneB, aOperationLaneA
        // ingress directions: aWorkLaneB forward forced, aExpandLaneA forward forced, aExpandLaneB forward forced, aOperationLaneA forward/backward random
        // cross from: aWorkLaneA, aExpandLaneC, aOperationLaneB
        // cross directions: aWorkLaneA backward forced, aExpandLaneC backward forced, aOperationLaneB backward/forward random
        // write to: aWorkLaneC
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aWorkLaneB[((aIndex + 20015U)) & S_BLOCK1], 51U) ^ RotL64(aExpandLaneA[((aIndex + 22237U)) & S_BLOCK1], 3U));
            aIngress ^= (RotL64(aExpandLaneB[((aIndex + 18515U)) & S_BLOCK1], 42U) ^ RotL64(aOperationLaneA[((aIndex + 17807U)) & S_BLOCK1], 27U));
            aIngress = TwistMix64::DiffuseB(((aIngress ^ aDomainWordIngress) ^ aNonceWordI));
            //
            aCross = (RotL64(aWorkLaneA[((S_BLOCK1 - aIndex + 16643U)) & S_BLOCK1], 36U) ^ RotL64(aExpandLaneC[((S_BLOCK1 - aIndex + 20982U)) & S_BLOCK1], 19U));
            aCross ^= RotL64(aOperationLaneB[((S_BLOCK1 - aIndex + 20779U)) & S_BLOCK1], 27U);
            aCross = TwistMix64::DiffuseC(((aCross ^ aDomainWordCross) ^ aNonceWordG));
            //
            aScatter = (RotL64(aCross, 3U) ^ RotL64(aIngress, 39U)) + (RotL64(aPrevious, 19U) + RotL64(aCarry, 54U));
            aScatter = TwistMix64::DiffuseC(((aScatter ^ aDomainWordScatter) ^ aNonceWordJ));
            //
            aOrbiterE = (((aWandererF + RotL64(aScatter, 19U)) + RotL64(aCarry, 19U)) + 18255347001097480328U) + aNonceWordH;
            aOrbiterJ = (aWandererD + RotL64(aPrevious, 13U)) + 13679246790311505735U;
            aOrbiterH = ((aWandererK + RotL64(aCross, 37U)) + RotL64(aCarry, 43U)) + 10565839529765027116U;
            aOrbiterK = ((aWandererI + RotL64(aIngress, 3U)) + 14327172566224769901U) + aOrbiterAssignSaltA[((aIndex + 17U)) & S_SALT1];
            aOrbiterI = ((aWandererA + RotL64(aPrevious, 43U)) + RotL64(aCarry, 5U)) + 16239024612038195174U;
            aOrbiterB = ((aWandererH + RotL64(aIngress, 26U)) + 13800012174212131890U) + aNonceWordP;
            aOrbiterF = ((aWandererC + RotL64(aScatter, 51U)) + 13900288860157577583U) + aOrbiterAssignSaltE[(((31U - aIndex) + 9U)) & S_SALT1];
            //
            aOrbiterE = ((aOrbiterE + aOrbiterJ) + 4144386119777112740U) + aOrbiterUpdateSaltA[(((31U - aIndex) + 8U)) & S_SALT1];
            aOrbiterH = ((aOrbiterH ^ aOrbiterE) ^ 3154558262670631372U) ^ aNonceWordL;
            aOrbiterH = RotL64((aOrbiterH * 13236911910092437063U), 57U);
            //
            aOrbiterK = (aOrbiterK + aOrbiterI) + 7456728543137614001U;
            aOrbiterE = (((aOrbiterE ^ aOrbiterK) ^ 11709519851158935384U) ^ aOrbiterUpdateSaltE[(((31U - aIndex) + 23U)) & S_SALT1]) ^ aNonceWordO;
            aOrbiterE = RotL64((aOrbiterE * 7016689518570071587U), 23U);
            //
            aOrbiterI = (aOrbiterI + aOrbiterE) + 15607438907832240304U;
            aOrbiterJ = (aOrbiterJ ^ aOrbiterI) ^ 9276575329661725624U;
            aOrbiterJ = RotL64((aOrbiterJ * 8879744070762412745U), 5U);
            //
            aOrbiterJ = (aOrbiterJ + aOrbiterH) + 6459435969129449226U;
            aOrbiterB = (aOrbiterB ^ aOrbiterJ) ^ 6442382118416542275U;
            aOrbiterB = RotL64((aOrbiterB * 2921027306686588233U), 29U);
            //
            aOrbiterF = ((aOrbiterF + aOrbiterK) + 12117432107282150865U) + aOrbiterUpdateSaltC[((aIndex + 14U)) & S_SALT1];
            aOrbiterI = ((aOrbiterI ^ aOrbiterF) ^ 6831279293184793243U) ^ aOrbiterUpdateSaltD[((aIndex + 25U)) & S_SALT1];
            aOrbiterI = RotL64((aOrbiterI * 2435360641135249073U), 43U);
            //
            aOrbiterB = (aOrbiterB + aOrbiterF) + 9520022957804572889U;
            aOrbiterK = (aOrbiterK ^ aOrbiterB) ^ 8322178689474588679U;
            aOrbiterK = RotL64((aOrbiterK * 1627707191467537115U), 37U);
            //
            aOrbiterH = (aOrbiterH + aOrbiterB) + 4162401591586869316U;
            aOrbiterF = (aOrbiterF ^ aOrbiterH) ^ 8994015844714895961U;
            aOrbiterF = RotL64((aOrbiterF * 15421910378057951895U), 51U);
            //
            aIngress = aOrbiterI ^ RotL64(aOrbiterK, 50U);
            aIngress = aIngress + (aOrbiterH ^ RotL64(aOrbiterJ, 27U));
            aIngress = aIngress + (aOrbiterB ^ RotL64(aOrbiterE, 37U));
            aIngress = aIngress + RotL64(aOrbiterF, 13U);
            aIngress = TwistMix64::DiffuseC((aIngress + aScatter));
            //
            aWandererK = aWandererK + (((RotL64(aIngress, 60U) + RotL64(aOrbiterK, 35U)) + aOrbiterE) + aNonceWordF);
            aWandererC = aWandererC ^ (((RotL64(aPrevious, 11U) + RotL64(aOrbiterE, 47U)) + aOrbiterI) + aNonceWordJ);
            aWandererH = aWandererH + (((((RotL64(aScatter, 43U) + RotL64(aOrbiterH, 20U)) + aOrbiterJ) + RotL64(aCarry, 3U)) + aNonceWordD) + aWandererUpdateSaltE[(((31U - aIndex) + 29U)) & S_SALT1]);
            aWandererD = aWandererD ^ ((RotL64(aCross, 3U) + RotL64(aOrbiterB, 29U)) + aOrbiterH);
            aWandererA = aWandererA + ((((RotL64(aIngress, 29U) + RotL64(aOrbiterE, 3U)) + aOrbiterH) + RotL64(aCarry, 51U)) + aWandererUpdateSaltC[(((31U - aIndex) + 11U)) & S_SALT1]);
            aWandererF = aWandererF ^ ((RotL64(aCross, 21U) + RotL64(aOrbiterB, 41U)) + aOrbiterE);
            aWandererI = aWandererI + (((RotL64(aScatter, 53U) + RotL64(aOrbiterF, 13U)) + aOrbiterK) + aNonceWordN);
            //
            aCarry = aCarry + (RotL64(aWandererC, 19U) ^ aWandererA);
            aCarry = aCarry + (RotL64(aWandererF, 58U) ^ aWandererI);
            aCarry = aCarry + (RotL64(aWandererK, 53U) ^ aWandererD);
            aCarry = aCarry + RotL64(aWandererH, 37U);
            aCarry = aCarry + RotL64(aIngress, 5U);
            aCarry = TwistMix64::DiffuseB(aCarry);
            //
            aWorkLaneC[aIndex] = aIngress;
        }
    
        // kdf_a_loop_d loop 4
        // ingress from: aWorkLaneC, aWorkLaneA, aExpandLaneD, aOperationLaneC
        // ingress directions: aWorkLaneC forward forced, aWorkLaneA forward forced, aExpandLaneD forward forced, aOperationLaneC forward/backward random
        // cross from: aWorkLaneB, aExpandLaneB, aOperationLaneD
        // cross directions: aWorkLaneB backward forced, aExpandLaneB backward forced, aOperationLaneD backward/forward random
        // write to: aWorkLaneD
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aWorkLaneC[((aIndex + 31367U)) & S_BLOCK1], 39U) ^ RotL64(aWorkLaneA[((aIndex + 27349U)) & S_BLOCK1], 48U));
            aIngress ^= (RotL64(aExpandLaneD[((aIndex + 26328U)) & S_BLOCK1], 19U) ^ RotL64(aOperationLaneC[((aIndex + 27420U)) & S_BLOCK1], 3U));
            aIngress = TwistMix64::DiffuseC(((aIngress ^ aDomainWordIngress) ^ aNonceWordA));
            //
            aCross = (RotL64(aWorkLaneB[((S_BLOCK1 - aIndex + 28168U)) & S_BLOCK1], 37U) ^ RotL64(aExpandLaneB[((S_BLOCK1 - aIndex + 25344U)) & S_BLOCK1], 6U));
            aCross ^= RotL64(aOperationLaneD[((S_BLOCK1 - aIndex + 28107U)) & S_BLOCK1], 53U);
            aCross = TwistMix64::DiffuseC(((aCross ^ aDomainWordCross) ^ aNonceWordG));
            //
            aScatter = (RotL64(aIngress, 37U) + RotL64(aCross, 3U)) ^ (RotL64(aCarry, 53U) ^ RotL64(aPrevious, 24U));
            aScatter = TwistMix64::DiffuseB(((aScatter ^ aDomainWordScatter) ^ aNonceWordC));
            //
            aOrbiterE = ((((aWandererE + RotL64(aCross, 53U)) + RotL64(aCarry, 19U)) + 11410829607777684449U) + aOrbiterAssignSaltC[((aIndex + 5U)) & S_SALT1]) + aNonceWordK;
            aOrbiterG = (aWandererG + RotL64(aIngress, 11U)) + 7502698839700975347U;
            aOrbiterF = ((aWandererA + RotL64(aScatter, 41U)) + 13267685058252106173U) + aNonceWordD;
            aOrbiterH = ((((aWandererC + RotL64(aPrevious, 3U)) + RotL64(aCarry, 39U)) + 238242706996630625U) + aOrbiterAssignSaltF[(((31U - aIndex) + 4U)) & S_SALT1]) + aNonceWordF;
            aOrbiterD = ((aWandererI + RotL64(aScatter, 19U)) + RotL64(aCarry, 51U)) + 8184695499511454281U;
            aOrbiterA = ((aWandererF + RotL64(aCross, 27U)) + 12767823220461985403U) + aNonceWordI;
            aOrbiterK = (aWandererD + RotL64(aIngress, 34U)) + 12293198423143850330U;
            //
            aOrbiterE = (aOrbiterE + aOrbiterG) + 11149495229952495939U;
            aOrbiterF = (((aOrbiterF ^ aOrbiterE) ^ 7556992689338382800U) ^ aOrbiterUpdateSaltE[((aIndex + 23U)) & S_SALT1]) ^ aNonceWordC;
            aOrbiterF = RotL64((aOrbiterF * 18232398462716803063U), 39U);
            //
            aOrbiterH = (aOrbiterH + aOrbiterD) + 3431338808774134649U;
            aOrbiterA = ((aOrbiterA ^ aOrbiterH) ^ 16863099140844995099U) ^ aOrbiterUpdateSaltF[((aIndex + 13U)) & S_SALT1];
            aOrbiterA = RotL64((aOrbiterA * 752376661101787919U), 53U);
            //
            aOrbiterK = ((aOrbiterK + aOrbiterE) + 17872458049880677604U) + aNonceWordJ;
            aOrbiterG = (aOrbiterG ^ aOrbiterK) ^ 16760153457252546974U;
            aOrbiterG = RotL64((aOrbiterG * 11225037229069712805U), 21U);
            //
            aOrbiterD = ((aOrbiterD + aOrbiterA) + 3115544493537438408U) + aOrbiterUpdateSaltD[((aIndex + 21U)) & S_SALT1];
            aOrbiterK = ((aOrbiterK ^ aOrbiterD) ^ 4359882942759752958U) ^ aNonceWordN;
            aOrbiterK = RotL64((aOrbiterK * 561477566995575801U), 47U);
            //
            aOrbiterF = (aOrbiterF + aOrbiterH) + 13387113067202396536U;
            aOrbiterD = (aOrbiterD ^ aOrbiterF) ^ 12955690074544490161U;
            aOrbiterD = RotL64((aOrbiterD * 12449941770827974511U), 29U);
            //
            aOrbiterA = (aOrbiterA + aOrbiterK) + 15614054443728226807U;
            aOrbiterE = (aOrbiterE ^ aOrbiterA) ^ 1939441328066616114U;
            aOrbiterE = RotL64((aOrbiterE * 4484917074808974359U), 11U);
            //
            aOrbiterG = ((aOrbiterG + aOrbiterF) + 4599016263007782537U) + aOrbiterUpdateSaltB[((aIndex + 17U)) & S_SALT1];
            aOrbiterH = (aOrbiterH ^ aOrbiterG) ^ 9962305629016158048U;
            aOrbiterH = RotL64((aOrbiterH * 1496184427500037279U), 5U);
            //
            aIngress = RotL64(aOrbiterG, 53U) ^ aOrbiterE;
            aIngress = aIngress + (RotL64(aOrbiterF, 60U) ^ aOrbiterA);
            aIngress = aIngress + (aOrbiterH ^ RotL64(aOrbiterK, 5U));
            aIngress = aIngress + RotL64(aOrbiterD, 47U);
            aIngress = TwistMix64::DiffuseB((aIngress + aScatter));
            //
            aWandererG = aWandererG + ((((RotL64(aPrevious, 11U) + RotL64(aOrbiterE, 11U)) + aOrbiterH) + RotL64(aCarry, 37U)) + aNonceWordP);
            aWandererF = aWandererF ^ ((RotL64(aScatter, 43U) + aOrbiterK) + RotL64(aOrbiterD, 21U));
            aWandererA = aWandererA + (((RotL64(aIngress, 60U) + RotL64(aOrbiterG, 41U)) + aOrbiterF) + RotL64(aCarry, 5U));
            aWandererC = aWandererC ^ (((RotL64(aCross, 53U) + RotL64(aOrbiterA, 27U)) + aOrbiterE) + aNonceWordB);
            aWandererD = aWandererD + (((RotL64(aScatter, 29U) + RotL64(aOrbiterD, 34U)) + aOrbiterF) + aWandererUpdateSaltD[(((31U - aIndex) + 10U)) & S_SALT1]);
            aWandererI = aWandererI ^ (((RotL64(aIngress, 3U) + RotL64(aOrbiterK, 53U)) + aOrbiterE) + aNonceWordO);
            aWandererE = aWandererE + (((RotL64(aCross, 37U) + RotL64(aOrbiterD, 5U)) + aOrbiterA) + aWandererUpdateSaltA[(((31U - aIndex) + 19U)) & S_SALT1]);
            //
            aCarry = aCarry + (RotL64(aWandererF, 39U) ^ aWandererA);
            aCarry = aCarry + (aWandererD ^ RotL64(aWandererC, 19U));
            aCarry = aCarry + (RotL64(aWandererG, 23U) ^ aWandererI);
            aCarry = aCarry + RotL64(aWandererE, 12U);
            aCarry = aCarry + RotL64(aIngress, 29U);
            aCarry = TwistMix64::DiffuseA(aCarry);
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

void TwistExpander_Greezy_Arx::KDF_B_A(TwistWorkSpace *pWorkSpace,
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
    std::uint64_t aCross = 0; std::uint64_t aScatter = 0;

    std::uint64_t aOrbiterA = 0; std::uint64_t aOrbiterB = 0; std::uint64_t aOrbiterC = 0; std::uint64_t aOrbiterD = 0;
    std::uint64_t aOrbiterE = 0; std::uint64_t aOrbiterF = 0; std::uint64_t aOrbiterG = 0; std::uint64_t aOrbiterH = 0;
    std::uint64_t aOrbiterI = 0; std::uint64_t aOrbiterJ = 0; std::uint64_t aOrbiterK = 0;

    // [kdf-a arx]
    std::uint64_t aNonceWordA = TwistMix64::DiffuseC(pNonce * 0xA18A039972B342A9ULL + 0xED078F3BD4BE62D4ULL);
    std::uint64_t aNonceWordB = TwistMix64::DiffuseB(pNonce * 0x8003BECF742D217BULL + 0xC4BDA344003950F3ULL);
    std::uint64_t aNonceWordC = TwistMix64::DiffuseB(pNonce * 0x894F96FD67378155ULL + 0xB3D4B2EE00883348ULL);
    std::uint64_t aNonceWordD = TwistMix64::DiffuseB(pNonce * 0xD0D70668D8636411ULL + 0xF18AA22B376A43B8ULL);
    std::uint64_t aNonceWordE = TwistMix64::DiffuseC(pNonce * 0xB04968FDC5DC2933ULL + 0xBB49637DD69C4B15ULL);
    std::uint64_t aNonceWordF = TwistMix64::DiffuseB(pNonce * 0x85EFE5EDB4BB1B37ULL + 0xB7E23F017E723A11ULL);
    std::uint64_t aNonceWordG = TwistMix64::DiffuseA(pNonce * 0xB99EB2A4AD36294BULL + 0xEF88310D487D306EULL);
    std::uint64_t aNonceWordH = TwistMix64::DiffuseA(pNonce * 0x851800CC50F56901ULL + 0xA74C41B5334555ABULL);
    std::uint64_t aNonceWordI = TwistMix64::DiffuseC(pNonce * 0xB7A118C31B5DAF83ULL + 0xECBB9F4E483A26B6ULL);
    std::uint64_t aNonceWordJ = TwistMix64::DiffuseA(pNonce * 0xFF7B796F818BA46BULL + 0x8DA24A7A0BDE845AULL);
    std::uint64_t aNonceWordK = TwistMix64::DiffuseB(pNonce * 0xD22494E42C377A0FULL + 0xD8BE338730B61D5EULL);
    std::uint64_t aNonceWordL = TwistMix64::DiffuseA(pNonce * 0xACCD31A9A6075221ULL + 0x994EAF9359BC39ACULL);
    std::uint64_t aNonceWordM = TwistMix64::DiffuseB(pNonce * 0xF53C90E337953AB5ULL + 0xF0B13C12E335A6B9ULL);
    std::uint64_t aNonceWordN = TwistMix64::DiffuseB(pNonce * 0xE2FE789DBC16640FULL + 0xA113A931F4B8A75AULL);
    std::uint64_t aNonceWordO = TwistMix64::DiffuseC(pNonce * 0x9BC2C29541A8E04DULL + 0xA9089B030F9D2E7FULL);
    std::uint64_t aNonceWordP = TwistMix64::DiffuseA(pNonce * 0xF01A2789BD88AD9BULL + 0xC80A739D3919D637ULL);
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
        // read from: aWorkLaneA, aWorkLaneB, aOperationLaneA, aWorkLaneC, aWorkLaneD, aFireLaneA, aOperationLaneB, aFireLaneB, aOperationLaneC, aExpandLaneA, aOperationLaneD, aExpandLaneB, aExpandLaneC
        // write to: aFireLaneA, aFireLaneB, aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD
    
        // kdf_b_loop_a loop 1
        // ingress from: aWorkLaneA, aWorkLaneB, aOperationLaneA
        // ingress directions: aWorkLaneA forward forced, aWorkLaneB forward forced, aOperationLaneA forward/backward random
        // cross from: aWorkLaneC, aWorkLaneD
        // cross directions: aWorkLaneC backward forced, aWorkLaneD backward/forward random
        // write to: aFireLaneA
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aWorkLaneA[((aIndex + 4231U)) & S_BLOCK1], 39U) ^ RotL64(aWorkLaneB[((aIndex + 4581U)) & S_BLOCK1], 5U));
            aIngress ^= RotL64(aOperationLaneA[((aIndex + 4422U)) & S_BLOCK1], 13U);
            aIngress = TwistMix64::DiffuseA(((aIngress ^ aDomainWordIngress) ^ aNonceWordJ));
            //
            aCross = RotL64(aWorkLaneC[((S_BLOCK1 - aIndex + 4811U)) & S_BLOCK1], 54U) ^ RotL64(aWorkLaneD[((S_BLOCK1 - aIndex + 5452U)) & S_BLOCK1], 37U);
            aCross = TwistMix64::DiffuseC(((aCross ^ aDomainWordCross) ^ aNonceWordM));
            //
            aScatter = (RotL64(aIngress, 23U) ^ RotL64(aCross, 54U)) ^ (RotL64(aCarry, 11U) + RotL64(aPrevious, 39U));
            aScatter = TwistMix64::DiffuseC(((aScatter ^ aDomainWordScatter) ^ aNonceWordF));
            //
            aOrbiterI = (aWandererG + RotL64(aScatter, 3U)) + 9133751643283278896U;
            aOrbiterE = ((aWandererF + RotL64(aIngress, 58U)) + 8971581804375380408U) + aNonceWordD;
            aOrbiterG = (((aWandererD + RotL64(aPrevious, 41U)) + 12559650383714566592U) + aOrbiterAssignSaltF[((aIndex + 18U)) & S_SALT1]) + aNonceWordO;
            aOrbiterB = ((((aWandererA + RotL64(aCross, 47U)) + RotL64(aCarry, 39U)) + 15753206088872859163U) + aOrbiterAssignSaltC[((aIndex + 7U)) & S_SALT1]) + aNonceWordI;
            aOrbiterJ = ((aWandererH + RotL64(aPrevious, 19U)) + RotL64(aCarry, 3U)) + 7640756270450762350U;
            aOrbiterK = (aWandererI + RotL64(aScatter, 27U)) + 7340073357551376125U;
            aOrbiterH = (((aWandererB + RotL64(aIngress, 35U)) + RotL64(aCarry, 19U)) + 5270256573644196046U) + aNonceWordH;
            //
            aOrbiterI = (aOrbiterI + aOrbiterE) + 3567367996479995928U;
            aOrbiterG = (aOrbiterG ^ aOrbiterI) ^ 11939634537492733738U;
            aOrbiterG = RotL64((aOrbiterG * 5640541900117183639U), 3U);
            //
            aOrbiterG = (aOrbiterG + aOrbiterB) + 7051817732424527120U;
            aOrbiterJ = ((aOrbiterJ ^ aOrbiterG) ^ 1730487669951837941U) ^ aNonceWordL;
            aOrbiterJ = RotL64((aOrbiterJ * 15191634337956285841U), 21U);
            //
            aOrbiterK = ((aOrbiterK + aOrbiterG) + 18009252467909454817U) + aOrbiterUpdateSaltB[((aIndex + 14U)) & S_SALT1];
            aOrbiterH = (aOrbiterH ^ aOrbiterK) ^ 2361024272031696442U;
            aOrbiterH = RotL64((aOrbiterH * 15215151562500226027U), 47U);
            //
            aOrbiterJ = (aOrbiterJ + aOrbiterK) + 15902755877642960397U;
            aOrbiterE = (aOrbiterE ^ aOrbiterJ) ^ 12243517544704116184U;
            aOrbiterE = RotL64((aOrbiterE * 2576071074148141447U), 57U);
            //
            aOrbiterH = ((aOrbiterH + aOrbiterJ) + 16846181962302186187U) + aOrbiterUpdateSaltD[(((31U - aIndex) + 24U)) & S_SALT1];
            aOrbiterI = (aOrbiterI ^ aOrbiterH) ^ 636121425116506681U;
            aOrbiterI = RotL64((aOrbiterI * 17075030673338779993U), 11U);
            //
            aOrbiterB = ((aOrbiterB + aOrbiterI) + 6887385655828217318U) + aOrbiterUpdateSaltA[(((31U - aIndex) + 16U)) & S_SALT1];
            aOrbiterK = (aOrbiterK ^ aOrbiterB) ^ 3705834550934775862U;
            aOrbiterK = RotL64((aOrbiterK * 11275428284929594435U), 37U);
            //
            aOrbiterE = ((aOrbiterE + aOrbiterH) + 11165142437077969438U) + aNonceWordP;
            aOrbiterB = (((aOrbiterB ^ aOrbiterE) ^ 6426659930331618269U) ^ aOrbiterUpdateSaltE[((aIndex + 25U)) & S_SALT1]) ^ aNonceWordG;
            aOrbiterB = RotL64((aOrbiterB * 17170640810530893705U), 29U);
            //
            aIngress = RotL64(aOrbiterG, 51U) ^ aOrbiterK;
            aIngress = aIngress + (aOrbiterJ ^ RotL64(aOrbiterI, 57U));
            aIngress = aIngress + (aOrbiterH ^ RotL64(aOrbiterE, 27U));
            aIngress = aIngress + RotL64(aOrbiterB, 35U);
            aIngress = TwistMix64::DiffuseA((aIngress + aScatter));
            //
            aWandererD = aWandererD ^ (((RotL64(aCross, 13U) + aOrbiterB) + RotL64(aOrbiterG, 43U)) + aWandererUpdateSaltF[(((31U - aIndex) + 29U)) & S_SALT1]);
            aWandererA = aWandererA + ((((RotL64(aPrevious, 4U) + aOrbiterK) + RotL64(aOrbiterG, 19U)) + RotL64(aCarry, 51U)) + aWandererUpdateSaltA[(((31U - aIndex) + 4U)) & S_SALT1]);
            aWandererI = aWandererI ^ (((RotL64(aIngress, 27U) + RotL64(aOrbiterK, 3U)) + aOrbiterB) + aNonceWordK);
            aWandererG = aWandererG + ((((RotL64(aScatter, 47U) + RotL64(aOrbiterE, 58U)) + aOrbiterI) + RotL64(aCarry, 35U)) + aNonceWordA);
            aWandererB = aWandererB ^ (((RotL64(aIngress, 19U) + aOrbiterE) + RotL64(aOrbiterJ, 11U)) + aNonceWordF);
            aWandererF = aWandererF + ((RotL64(aPrevious, 53U) + aOrbiterH) + RotL64(aOrbiterK, 51U));
            aWandererH = aWandererH ^ (((RotL64(aScatter, 35U) + RotL64(aOrbiterI, 27U)) + aOrbiterG) + aNonceWordN);
            //
            aCarry = aCarry + (aWandererB ^ RotL64(aWandererA, 46U));
            aCarry = aCarry + (aWandererI ^ RotL64(aWandererG, 27U));
            aCarry = aCarry + (aWandererF ^ RotL64(aWandererH, 57U));
            aCarry = aCarry + RotL64(aWandererD, 51U);
            aCarry = aCarry + RotL64(aIngress, 13U);
            aCarry = TwistMix64::DiffuseA(aCarry);
            //
            aFireLaneA[aIndex] = aIngress;
        }
    
        // kdf_b_loop_a loop 2
        // ingress from: aFireLaneA, aWorkLaneC, aOperationLaneB
        // ingress directions: aFireLaneA forward forced, aWorkLaneC forward forced, aOperationLaneB forward/backward random
        // cross from: aWorkLaneA, aWorkLaneD, aWorkLaneB
        // cross directions: aWorkLaneA backward forced, aWorkLaneD backward forced, aWorkLaneB backward/forward random
        // write to: aFireLaneB
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aFireLaneA[((aIndex + 10911U)) & S_BLOCK1], 20U) ^ RotL64(aWorkLaneC[((aIndex + 7666U)) & S_BLOCK1], 37U));
            aIngress ^= RotL64(aOperationLaneB[((aIndex + 10389U)) & S_BLOCK1], 3U);
            aIngress = TwistMix64::DiffuseB(((aIngress ^ aDomainWordIngress) ^ aNonceWordF));
            //
            aCross = (RotL64(aWorkLaneA[((S_BLOCK1 - aIndex + 8337U)) & S_BLOCK1], 41U) ^ RotL64(aWorkLaneD[((S_BLOCK1 - aIndex + 6680U)) & S_BLOCK1], 21U));
            aCross ^= RotL64(aWorkLaneB[((S_BLOCK1 - aIndex + 7966U)) & S_BLOCK1], 30U);
            aCross = TwistMix64::DiffuseB(((aCross ^ aDomainWordCross) ^ aNonceWordD));
            //
            aScatter = (RotL64(aPrevious, 5U) + RotL64(aCarry, 39U)) ^ (RotL64(aCross, 20U) ^ RotL64(aIngress, 57U));
            aScatter = TwistMix64::DiffuseA(((aScatter ^ aDomainWordScatter) ^ aNonceWordD));
            //
            aOrbiterF = (aWandererK + RotL64(aScatter, 37U)) + 12131317914288566437U;
            aOrbiterE = (((aWandererD + RotL64(aPrevious, 11U)) + RotL64(aCarry, 13U)) + 5672805657999385496U) + aNonceWordB;
            aOrbiterB = ((aWandererA + RotL64(aCross, 29U)) + 3581710244233124197U) + aNonceWordP;
            aOrbiterI = (((aWandererE + RotL64(aIngress, 18U)) + RotL64(aCarry, 57U)) + 15251296040538489436U) + aOrbiterAssignSaltE[((aIndex + 8U)) & S_SALT1];
            aOrbiterH = ((aWandererB + RotL64(aScatter, 57U)) + 11295008604679904153U) + aOrbiterAssignSaltA[((aIndex + 17U)) & S_SALT1];
            aOrbiterG = (((aWandererJ + RotL64(aCross, 3U)) + RotL64(aCarry, 43U)) + 2230897493419504490U) + aNonceWordA;
            aOrbiterJ = ((aWandererG + RotL64(aPrevious, 51U)) + 7109600123297458999U) + aNonceWordH;
            //
            aOrbiterF = (aOrbiterF + aOrbiterE) + 13119156643107683803U;
            aOrbiterB = ((aOrbiterB ^ aOrbiterF) ^ 14755160867807355250U) ^ aOrbiterUpdateSaltF[((aIndex + 12U)) & S_SALT1];
            aOrbiterB = RotL64((aOrbiterB * 10007087518844899239U), 21U);
            //
            aOrbiterI = (((aOrbiterI + aOrbiterF) + 16829363373287496832U) + aOrbiterUpdateSaltA[((aIndex + 14U)) & S_SALT1]) + aNonceWordK;
            aOrbiterH = (aOrbiterH ^ aOrbiterI) ^ 16981122946707720883U;
            aOrbiterH = RotL64((aOrbiterH * 5394974422201576627U), 51U);
            //
            aOrbiterG = (aOrbiterG + aOrbiterI) + 8806000776958603317U;
            aOrbiterE = (aOrbiterE ^ aOrbiterG) ^ 16810923047720876014U;
            aOrbiterE = RotL64((aOrbiterE * 17872735050219539145U), 57U);
            //
            aOrbiterB = (aOrbiterB + aOrbiterJ) + 8129657889554436328U;
            aOrbiterI = (((aOrbiterI ^ aOrbiterB) ^ 8653100378491974463U) ^ aOrbiterUpdateSaltD[(((31U - aIndex) + 29U)) & S_SALT1]) ^ aNonceWordM;
            aOrbiterI = RotL64((aOrbiterI * 11395283153912468661U), 3U);
            //
            aOrbiterH = (aOrbiterH + aOrbiterB) + 17048985838727432415U;
            aOrbiterG = ((aOrbiterG ^ aOrbiterH) ^ 10892675550889823573U) ^ aNonceWordO;
            aOrbiterG = RotL64((aOrbiterG * 976298937314081913U), 39U);
            //
            aOrbiterE = (aOrbiterE + aOrbiterH) + 15960158965421254346U;
            aOrbiterJ = ((aOrbiterJ ^ aOrbiterE) ^ 12290011578634850001U) ^ aOrbiterUpdateSaltC[(((31U - aIndex) + 7U)) & S_SALT1];
            aOrbiterJ = RotL64((aOrbiterJ * 9280475585104357745U), 13U);
            //
            aOrbiterJ = ((aOrbiterJ + aOrbiterG) + 16265047040311479093U) + aNonceWordE;
            aOrbiterF = (aOrbiterF ^ aOrbiterJ) ^ 10312956912303656248U;
            aOrbiterF = RotL64((aOrbiterF * 3012584393253845131U), 27U);
            //
            aIngress = aOrbiterJ ^ RotL64(aOrbiterF, 54U);
            aIngress = aIngress + (aOrbiterH ^ RotL64(aOrbiterI, 27U));
            aIngress = aIngress + (RotL64(aOrbiterE, 19U) ^ aOrbiterB);
            aIngress = aIngress + RotL64(aOrbiterG, 13U);
            aIngress = TwistMix64::DiffuseA((aIngress + aScatter));
            //
            aWandererJ = aWandererJ ^ ((RotL64(aCross, 53U) + aOrbiterH) + RotL64(aOrbiterJ, 23U));
            aWandererK = aWandererK + ((((RotL64(aPrevious, 19U) + aOrbiterG) + RotL64(aOrbiterH, 41U)) + RotL64(aCarry, 5U)) + aWandererUpdateSaltC[((aIndex + 11U)) & S_SALT1]);
            aWandererD = aWandererD ^ ((RotL64(aScatter, 11U) + aOrbiterE) + RotL64(aOrbiterG, 13U));
            aWandererE = aWandererE + ((((RotL64(aIngress, 44U) + aOrbiterB) + RotL64(aOrbiterI, 29U)) + RotL64(aCarry, 19U)) + aNonceWordJ);
            aWandererA = aWandererA ^ (((RotL64(aScatter, 5U) + aOrbiterF) + RotL64(aOrbiterB, 48U)) + aWandererUpdateSaltE[(((31U - aIndex) + 27U)) & S_SALT1]);
            aWandererG = aWandererG + (((RotL64(aPrevious, 35U) + RotL64(aOrbiterH, 5U)) + aOrbiterI) + aNonceWordN);
            aWandererB = aWandererB ^ (((RotL64(aIngress, 29U) + aOrbiterE) + RotL64(aOrbiterH, 35U)) + aNonceWordL);
            //
            aCarry = aCarry + (aWandererD ^ RotL64(aWandererG, 57U));
            aCarry = aCarry + (RotL64(aWandererA, 42U) ^ aWandererE);
            aCarry = aCarry + (aWandererJ ^ RotL64(aWandererK, 3U));
            aCarry = aCarry + RotL64(aWandererB, 27U);
            aCarry = aCarry + RotL64(aIngress, 37U);
            aCarry = TwistMix64::DiffuseC(aCarry);
            //
            aFireLaneB[S_BLOCK1 - aIndex] = aIngress;
        }
    
        // kdf_b_loop_a loop 3
        // ingress from: aFireLaneB, aWorkLaneD, aOperationLaneC
        // ingress directions: aFireLaneB forward forced, aWorkLaneD forward forced, aOperationLaneC forward/backward random
        // cross from: aWorkLaneB, aFireLaneA
        // cross directions: aWorkLaneB backward forced, aFireLaneA backward/forward random
        // write to: aExpandLaneA
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aFireLaneB[((aIndex + 13220U)) & S_BLOCK1], 3U) ^ RotL64(aWorkLaneD[((aIndex + 12522U)) & S_BLOCK1], 39U));
            aIngress ^= RotL64(aOperationLaneC[((S_BLOCK1 - aIndex + 14131U)) & S_BLOCK1], 57U);
            aIngress = TwistMix64::DiffuseC(((aIngress ^ aDomainWordIngress) ^ aNonceWordF));
            //
            aCross = RotL64(aWorkLaneB[((S_BLOCK1 - aIndex + 15533U)) & S_BLOCK1], 50U) ^ RotL64(aFireLaneA[((aIndex + 15139U)) & S_BLOCK1], 11U);
            aCross = TwistMix64::DiffuseA(((aCross ^ aDomainWordCross) ^ aNonceWordG));
            //
            aScatter = (RotL64(aCross, 5U) + RotL64(aIngress, 37U)) ^ (RotL64(aPrevious, 19U) ^ RotL64(aCarry, 56U));
            aScatter = TwistMix64::DiffuseC(((aScatter ^ aDomainWordScatter) ^ aNonceWordA));
            //
            aOrbiterK = (((aWandererF + RotL64(aCross, 13U)) + 9471546960258473684U) + aOrbiterAssignSaltD[((aIndex + 23U)) & S_SALT1]) + aNonceWordP;
            aOrbiterI = (aWandererE + RotL64(aScatter, 51U)) + 18050235435948942244U;
            aOrbiterE = (aWandererK + RotL64(aIngress, 4U)) + 3005107102671544641U;
            aOrbiterJ = ((aWandererC + RotL64(aPrevious, 21U)) + 17898396434573801850U) + aNonceWordI;
            aOrbiterH = (((aWandererB + RotL64(aCross, 35U)) + RotL64(aCarry, 57U)) + 15071602525497771648U) + aOrbiterAssignSaltB[(((31U - aIndex) + 25U)) & S_SALT1];
            aOrbiterC = (((aWandererI + RotL64(aScatter, 29U)) + RotL64(aCarry, 11U)) + 5780119462702672108U) + aNonceWordH;
            aOrbiterG = ((aWandererA + RotL64(aPrevious, 41U)) + RotL64(aCarry, 35U)) + 13301326224151025687U;
            //
            aOrbiterK = (aOrbiterK + aOrbiterI) + 18129323022260575961U;
            aOrbiterE = (aOrbiterE ^ aOrbiterK) ^ 1199228670638790709U;
            aOrbiterE = RotL64((aOrbiterE * 1780426336211781025U), 19U);
            //
            aOrbiterI = ((aOrbiterI + aOrbiterE) + 1839199978088021020U) + aNonceWordL;
            aOrbiterJ = ((aOrbiterJ ^ aOrbiterI) ^ 4999517042246790165U) ^ aOrbiterUpdateSaltF[(((31U - aIndex) + 3U)) & S_SALT1];
            aOrbiterJ = RotL64((aOrbiterJ * 4585813675677234577U), 11U);
            //
            aOrbiterH = (aOrbiterH + aOrbiterC) + 8788607633376516299U;
            aOrbiterG = (aOrbiterG ^ aOrbiterH) ^ 15143903839930468749U;
            aOrbiterG = RotL64((aOrbiterG * 12735914889325422675U), 3U);
            //
            aOrbiterC = (aOrbiterC + aOrbiterG) + 16674732686428431869U;
            aOrbiterK = ((aOrbiterK ^ aOrbiterC) ^ 15908873150953195581U) ^ aOrbiterUpdateSaltC[(((31U - aIndex) + 4U)) & S_SALT1];
            aOrbiterK = RotL64((aOrbiterK * 18049755517524334107U), 57U);
            //
            aOrbiterE = (aOrbiterE + aOrbiterJ) + 11204775359756474667U;
            aOrbiterH = (aOrbiterH ^ aOrbiterE) ^ 2525984309543939465U;
            aOrbiterH = RotL64((aOrbiterH * 3988529812023791571U), 35U);
            //
            aOrbiterJ = (((aOrbiterJ + aOrbiterH) + 4566345170476825512U) + aOrbiterUpdateSaltB[(((31U - aIndex) + 6U)) & S_SALT1]) + aNonceWordK;
            aOrbiterC = ((aOrbiterC ^ aOrbiterJ) ^ 14876612901557406267U) ^ aNonceWordA;
            aOrbiterC = RotL64((aOrbiterC * 9047956948845135339U), 51U);
            //
            aOrbiterG = (((aOrbiterG + aOrbiterK) + 14926290877038883931U) + aOrbiterUpdateSaltE[((aIndex + 17U)) & S_SALT1]) + aNonceWordC;
            aOrbiterI = (aOrbiterI ^ aOrbiterG) ^ 12710203178186614846U;
            aOrbiterI = RotL64((aOrbiterI * 14841163494801662515U), 41U);
            //
            aIngress = RotL64(aOrbiterG, 41U) ^ aOrbiterJ;
            aIngress = aIngress + (aOrbiterH ^ RotL64(aOrbiterI, 13U));
            aIngress = aIngress + (RotL64(aOrbiterK, 35U) ^ aOrbiterC);
            aIngress = aIngress + RotL64(aOrbiterE, 5U);
            aIngress = TwistMix64::DiffuseA((aIngress + aScatter));
            //
            aWandererI = aWandererI ^ ((RotL64(aIngress, 26U) + aOrbiterJ) + RotL64(aOrbiterH, 41U));
            aWandererC = aWandererC + (((RotL64(aPrevious, 51U) + RotL64(aOrbiterH, 35U)) + aOrbiterG) + aNonceWordB);
            aWandererE = aWandererE ^ ((RotL64(aCross, 19U) + RotL64(aOrbiterK, 21U)) + aOrbiterG);
            aWandererK = aWandererK + (((RotL64(aScatter, 37U) + aOrbiterI) + RotL64(aOrbiterC, 5U)) + RotL64(aCarry, 23U));
            aWandererF = aWandererF ^ (((RotL64(aCross, 11U) + RotL64(aOrbiterE, 12U)) + aOrbiterI) + aNonceWordO);
            aWandererA = aWandererA + (((((RotL64(aPrevious, 57U) + RotL64(aOrbiterH, 27U)) + aOrbiterE) + RotL64(aCarry, 5U)) + aNonceWordM) + aWandererUpdateSaltB[(((31U - aIndex) + 12U)) & S_SALT1]);
            aWandererB = aWandererB ^ ((((RotL64(aScatter, 5U) + RotL64(aOrbiterG, 51U)) + aOrbiterI) + aNonceWordJ) + aWandererUpdateSaltD[((aIndex + 19U)) & S_SALT1]);
            //
            aCarry = aCarry + (aWandererB ^ RotL64(aWandererE, 22U));
            aCarry = aCarry + (RotL64(aWandererA, 47U) ^ aWandererC);
            aCarry = aCarry + (aWandererI ^ RotL64(aWandererK, 57U));
            aCarry = aCarry + RotL64(aWandererF, 27U);
            aCarry = aCarry + RotL64(aIngress, 35U);
            aCarry = TwistMix64::DiffuseC(aCarry);
            //
            aExpandLaneA[aIndex] = aIngress;
        }
    
        // kdf_b_loop_a loop 4
        // ingress from: aExpandLaneA, aWorkLaneC, aOperationLaneD
        // ingress directions: aExpandLaneA forward forced, aWorkLaneC forward forced, aOperationLaneD forward/backward random
        // cross from: aFireLaneB, aWorkLaneD
        // cross directions: aFireLaneB backward forced, aWorkLaneD backward/forward random
        // write to: aExpandLaneB
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aExpandLaneA[((aIndex + 18158U)) & S_BLOCK1], 35U) ^ RotL64(aWorkLaneC[((aIndex + 18890U)) & S_BLOCK1], 26U));
            aIngress ^= RotL64(aOperationLaneD[((S_BLOCK1 - aIndex + 19015U)) & S_BLOCK1], 3U);
            aIngress = TwistMix64::DiffuseC(((aIngress ^ aDomainWordIngress) ^ aNonceWordJ));
            //
            aCross = RotL64(aFireLaneB[((S_BLOCK1 - aIndex + 20897U)) & S_BLOCK1], 22U) ^ RotL64(aWorkLaneD[((aIndex + 16977U)) & S_BLOCK1], 57U);
            aCross = TwistMix64::DiffuseA(((aCross ^ aDomainWordCross) ^ aNonceWordA));
            //
            aScatter = (RotL64(aIngress, 5U) ^ RotL64(aCross, 52U)) + (RotL64(aCarry, 39U) ^ RotL64(aPrevious, 27U));
            aScatter = TwistMix64::DiffuseA(((aScatter ^ aDomainWordScatter) ^ aNonceWordB));
            //
            aOrbiterE = ((aWandererK + RotL64(aScatter, 43U)) + 9041099828460168106U) + aNonceWordL;
            aOrbiterG = ((aWandererA + RotL64(aCross, 3U)) + RotL64(aCarry, 29U)) + 12883711604096848454U;
            aOrbiterF = ((aWandererD + RotL64(aPrevious, 58U)) + RotL64(aCarry, 43U)) + 17420968786226443079U;
            aOrbiterA = (((aWandererC + RotL64(aIngress, 23U)) + 3448213891716125104U) + aOrbiterAssignSaltC[(((31U - aIndex) + 28U)) & S_SALT1]) + aNonceWordO;
            aOrbiterK = ((aWandererG + RotL64(aPrevious, 35U)) + 11866455977445336560U) + aOrbiterAssignSaltF[(((31U - aIndex) + 22U)) & S_SALT1];
            aOrbiterB = ((aWandererB + RotL64(aScatter, 51U)) + 4119356835384495905U) + aNonceWordB;
            aOrbiterD = ((aWandererE + RotL64(aIngress, 11U)) + RotL64(aCarry, 57U)) + 2186212599698637068U;
            //
            aOrbiterE = (aOrbiterE + aOrbiterG) + 6506144898969301620U;
            aOrbiterF = ((aOrbiterF ^ aOrbiterE) ^ 12556800923644051626U) ^ aOrbiterUpdateSaltB[((aIndex + 15U)) & S_SALT1];
            aOrbiterF = RotL64((aOrbiterF * 15961043406612913121U), 35U);
            //
            aOrbiterA = (aOrbiterA + aOrbiterK) + 4075551535185182945U;
            aOrbiterB = (aOrbiterB ^ aOrbiterA) ^ 17877694808492008749U;
            aOrbiterB = RotL64((aOrbiterB * 901315308379887473U), 51U);
            //
            aOrbiterB = ((aOrbiterB + aOrbiterE) + 5553428900598223316U) + aNonceWordC;
            aOrbiterG = (aOrbiterG ^ aOrbiterB) ^ 14362304852277160675U;
            aOrbiterG = RotL64((aOrbiterG * 11415103199856419303U), 41U);
            //
            aOrbiterG = ((aOrbiterG + aOrbiterF) + 9174200302876075831U) + aNonceWordP;
            aOrbiterD = ((aOrbiterD ^ aOrbiterG) ^ 16110739511917638547U) ^ aOrbiterUpdateSaltD[((aIndex + 11U)) & S_SALT1];
            aOrbiterD = RotL64((aOrbiterD * 7004356839428657949U), 5U);
            //
            aOrbiterK = (aOrbiterK + aOrbiterB) + 10189881974519849402U;
            aOrbiterE = (aOrbiterE ^ aOrbiterK) ^ 2128076632642616677U;
            aOrbiterE = RotL64((aOrbiterE * 8860453653433114929U), 19U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterA) + 18133523799074400083U;
            aOrbiterK = ((aOrbiterK ^ aOrbiterD) ^ 9916472958834153766U) ^ aOrbiterUpdateSaltA[((aIndex + 25U)) & S_SALT1];
            aOrbiterK = RotL64((aOrbiterK * 3454601168808001733U), 27U);
            //
            aOrbiterF = (aOrbiterF + aOrbiterD) + 10274457562795569227U;
            aOrbiterA = ((aOrbiterA ^ aOrbiterF) ^ 14134814273275356425U) ^ aOrbiterUpdateSaltE[(((31U - aIndex) + 4U)) & S_SALT1];
            aOrbiterA = RotL64((aOrbiterA * 15912501063665343159U), 11U);
            //
            aIngress = aOrbiterF ^ RotL64(aOrbiterB, 57U);
            aIngress = aIngress + (RotL64(aOrbiterD, 21U) ^ aOrbiterK);
            aIngress = aIngress + (aOrbiterE ^ RotL64(aOrbiterG, 5U));
            aIngress = aIngress + RotL64(aOrbiterA, 13U);
            aIngress = TwistMix64::DiffuseB((aIngress + aScatter));
            //
            aWandererE = aWandererE + (((RotL64(aScatter, 3U) + aOrbiterF) + RotL64(aOrbiterG, 47U)) + aNonceWordM);
            aWandererB = aWandererB ^ (((RotL64(aCross, 51U) + RotL64(aOrbiterD, 11U)) + aOrbiterK) + aWandererUpdateSaltA[((aIndex + 23U)) & S_SALT1]);
            aWandererG = aWandererG + (((RotL64(aPrevious, 13U) + aOrbiterG) + RotL64(aOrbiterB, 34U)) + RotL64(aCarry, 21U));
            aWandererA = aWandererA ^ (((RotL64(aIngress, 26U) + RotL64(aOrbiterD, 5U)) + aOrbiterA) + aWandererUpdateSaltF[(((31U - aIndex) + 17U)) & S_SALT1]);
            aWandererC = aWandererC + (((RotL64(aScatter, 19U) + aOrbiterE) + RotL64(aOrbiterB, 53U)) + aNonceWordF);
            aWandererD = aWandererD ^ ((RotL64(aCross, 35U) + RotL64(aOrbiterF, 21U)) + aOrbiterD);
            aWandererK = aWandererK + ((((RotL64(aIngress, 41U) + RotL64(aOrbiterK, 41U)) + aOrbiterB) + RotL64(aCarry, 51U)) + aNonceWordK);
            //
            aCarry = aCarry + (aWandererC ^ RotL64(aWandererK, 27U));
            aCarry = aCarry + (aWandererD ^ RotL64(aWandererE, 23U));
            aCarry = aCarry + (RotL64(aWandererB, 35U) ^ aWandererA);
            aCarry = aCarry + RotL64(aWandererG, 46U);
            aCarry = aCarry + RotL64(aIngress, 19U);
            aCarry = TwistMix64::DiffuseA(aCarry);
            //
            aExpandLaneB[S_BLOCK1 - aIndex] = aIngress;
        }
    
        // kdf_b_loop_a loop 5
        // ingress from: aExpandLaneB, aFireLaneB
        // ingress directions: aExpandLaneB forward forced, aFireLaneB forward/backward random
        // cross from: aExpandLaneA, aWorkLaneA
        // cross directions: aExpandLaneA backward forced, aWorkLaneA backward/forward random
        // write to: aExpandLaneC
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = RotL64(aExpandLaneB[((aIndex + 23161U)) & S_BLOCK1], 43U) ^ RotL64(aFireLaneB[((aIndex + 22938U)) & S_BLOCK1], 53U);
            aIngress = TwistMix64::DiffuseC(((aIngress ^ aDomainWordIngress) ^ aNonceWordE));
            //
            aCross = RotL64(aExpandLaneA[((S_BLOCK1 - aIndex + 22274U)) & S_BLOCK1], 5U) ^ RotL64(aWorkLaneA[((S_BLOCK1 - aIndex + 25752U)) & S_BLOCK1], 21U);
            aCross = TwistMix64::DiffuseA(((aCross ^ aDomainWordCross) ^ aNonceWordL));
            //
            aScatter = (RotL64(aIngress, 5U) + RotL64(aCross, 35U)) ^ (RotL64(aCarry, 54U) + RotL64(aPrevious, 19U));
            aScatter = TwistMix64::DiffuseB(((aScatter ^ aDomainWordScatter) ^ aNonceWordG));
            //
            aOrbiterF = ((aWandererE + RotL64(aCross, 29U)) + 11177787645248006236U) + aNonceWordB;
            aOrbiterD = (((aWandererH + RotL64(aScatter, 5U)) + RotL64(aCarry, 11U)) + 3808340254579817169U) + aNonceWordM;
            aOrbiterI = (((aWandererK + RotL64(aPrevious, 13U)) + 828030667598518279U) + aOrbiterAssignSaltA[((aIndex + 14U)) & S_SALT1]) + aNonceWordF;
            aOrbiterA = (((aWandererI + RotL64(aIngress, 60U)) + RotL64(aCarry, 51U)) + 16177835921238398371U) + aOrbiterAssignSaltE[((aIndex + 29U)) & S_SALT1];
            aOrbiterG = (((aWandererD + RotL64(aPrevious, 41U)) + RotL64(aCarry, 29U)) + 5518747735458708741U) + aNonceWordJ;
            aOrbiterK = (aWandererA + RotL64(aIngress, 51U)) + 17346319082399995165U;
            aOrbiterC = (aWandererB + RotL64(aCross, 35U)) + 6397156921893030937U;
            //
            aOrbiterF = (aOrbiterF + aOrbiterD) + 15559381654710713582U;
            aOrbiterI = (aOrbiterI ^ aOrbiterF) ^ 940404446491415088U;
            aOrbiterI = RotL64((aOrbiterI * 16401260971303026881U), 41U);
            //
            aOrbiterI = (aOrbiterI + aOrbiterA) + 8047166032048732645U;
            aOrbiterG = (aOrbiterG ^ aOrbiterI) ^ 4688468645859470491U;
            aOrbiterG = RotL64((aOrbiterG * 14383536431614496369U), 3U);
            //
            aOrbiterA = ((aOrbiterA + aOrbiterK) + 3710878044770337260U) + aNonceWordP;
            aOrbiterF = (aOrbiterF ^ aOrbiterA) ^ 116343189456629220U;
            aOrbiterF = RotL64((aOrbiterF * 5637725064169289339U), 35U);
            //
            aOrbiterG = ((aOrbiterG + aOrbiterF) + 883908030159391659U) + aOrbiterUpdateSaltD[(((31U - aIndex) + 21U)) & S_SALT1];
            aOrbiterC = (aOrbiterC ^ aOrbiterG) ^ 18058691521694880482U;
            aOrbiterC = RotL64((aOrbiterC * 3132200449123497619U), 57U);
            //
            aOrbiterK = ((aOrbiterK + aOrbiterG) + 17521015077103586117U) + aOrbiterUpdateSaltC[((aIndex + 24U)) & S_SALT1];
            aOrbiterD = ((aOrbiterD ^ aOrbiterK) ^ 3668332225435714918U) ^ aOrbiterUpdateSaltB[(((31U - aIndex) + 5U)) & S_SALT1];
            aOrbiterD = RotL64((aOrbiterD * 12658899101297839881U), 51U);
            //
            aOrbiterD = ((aOrbiterD + aOrbiterC) + 12229480388278883300U) + aNonceWordD;
            aOrbiterA = (aOrbiterA ^ aOrbiterD) ^ 16206524049491531816U;
            aOrbiterA = RotL64((aOrbiterA * 11122340196620859805U), 19U);
            //
            aOrbiterC = ((aOrbiterC + aOrbiterI) + 5743265849441077466U) + aNonceWordC;
            aOrbiterK = (((aOrbiterK ^ aOrbiterC) ^ 2812293020719282236U) ^ aOrbiterUpdateSaltA[(((31U - aIndex) + 15U)) & S_SALT1]) ^ aNonceWordH;
            aOrbiterK = RotL64((aOrbiterK * 8903956475200417109U), 13U);
            //
            aIngress = RotL64(aOrbiterF, 29U) ^ aOrbiterI;
            aIngress = aIngress + (RotL64(aOrbiterG, 53U) ^ aOrbiterK);
            aIngress = aIngress + (RotL64(aOrbiterA, 35U) ^ aOrbiterD);
            aIngress = aIngress + RotL64(aOrbiterC, 5U);
            aIngress = TwistMix64::DiffuseB((aIngress + aScatter));
            //
            aWandererA = aWandererA ^ (((RotL64(aScatter, 27U) + RotL64(aOrbiterC, 51U)) + aOrbiterI) + aNonceWordO);
            aWandererD = aWandererD + (((((RotL64(aIngress, 43U) + RotL64(aOrbiterF, 21U)) + aOrbiterG) + RotL64(aCarry, 39U)) + aNonceWordK) + aWandererUpdateSaltE[((aIndex + 19U)) & S_SALT1]);
            aWandererH = aWandererH ^ ((RotL64(aPrevious, 34U) + aOrbiterK) + RotL64(aOrbiterA, 5U));
            aWandererI = aWandererI + ((RotL64(aCross, 13U) + RotL64(aOrbiterD, 37U)) + aOrbiterF);
            aWandererE = aWandererE ^ (((RotL64(aIngress, 19U) + RotL64(aOrbiterK, 57U)) + aOrbiterD) + aNonceWordI);
            aWandererB = aWandererB + (((((RotL64(aPrevious, 5U) + aOrbiterI) + RotL64(aOrbiterA, 28U)) + RotL64(aCarry, 51U)) + aNonceWordN) + aWandererUpdateSaltC[(((31U - aIndex) + 6U)) & S_SALT1]);
            aWandererK = aWandererK ^ ((RotL64(aScatter, 51U) + RotL64(aOrbiterC, 43U)) + aOrbiterF);
            //
            aCarry = aCarry + (RotL64(aWandererE, 57U) ^ aWandererI);
            aCarry = aCarry + (RotL64(aWandererA, 37U) ^ aWandererK);
            aCarry = aCarry + (aWandererH ^ RotL64(aWandererB, 6U));
            aCarry = aCarry + RotL64(aWandererD, 23U);
            aCarry = aCarry + RotL64(aIngress, 19U);
            aCarry = TwistMix64::DiffuseB(aCarry);
            //
            aExpandLaneC[aIndex] = aIngress;
        }
    
        // kdf_b_loop_a loop 6
        // ingress from: aExpandLaneC, aExpandLaneA
        // ingress directions: aExpandLaneC forward forced, aExpandLaneA forward/backward random
        // cross from: aExpandLaneB, aWorkLaneB
        // cross directions: aExpandLaneB backward forced, aWorkLaneB backward/forward random
        // write to: aExpandLaneD
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = RotL64(aExpandLaneC[((aIndex + 28439U)) & S_BLOCK1], 11U) ^ RotL64(aExpandLaneA[((S_BLOCK1 - aIndex + 29807U)) & S_BLOCK1], 19U);
            aIngress = TwistMix64::DiffuseC(((aIngress ^ aDomainWordIngress) ^ aNonceWordK));
            //
            aCross = RotL64(aExpandLaneB[((S_BLOCK1 - aIndex + 31425U)) & S_BLOCK1], 53U) ^ RotL64(aWorkLaneB[((S_BLOCK1 - aIndex + 30009U)) & S_BLOCK1], 37U);
            aCross = TwistMix64::DiffuseC(((aCross ^ aDomainWordCross) ^ aNonceWordJ));
            //
            aScatter = (RotL64(aCarry, 35U) + RotL64(aPrevious, 52U)) + (RotL64(aCross, 23U) ^ RotL64(aIngress, 3U));
            aScatter = TwistMix64::DiffuseB(((aScatter ^ aDomainWordScatter) ^ aNonceWordG));
            //
            aOrbiterB = (((aWandererE + RotL64(aIngress, 37U)) + 10726035965553989335U) + aOrbiterAssignSaltD[((aIndex + 19U)) & S_SALT1]) + aNonceWordG;
            aOrbiterF = ((aWandererG + RotL64(aPrevious, 27U)) + RotL64(aCarry, 53U)) + 967354339530195662U;
            aOrbiterD = ((aWandererD + RotL64(aCross, 44U)) + RotL64(aCarry, 27U)) + 10834593005478605624U;
            aOrbiterA = (((aWandererK + RotL64(aScatter, 21U)) + RotL64(aCarry, 3U)) + 1012888282838656933U) + aNonceWordN;
            aOrbiterI = (aWandererB + RotL64(aCross, 3U)) + 15283530351725183253U;
            aOrbiterH = ((aWandererC + RotL64(aScatter, 53U)) + 11724495956731703750U) + aNonceWordI;
            aOrbiterG = (((aWandererF + RotL64(aPrevious, 13U)) + 4288330117317505776U) + aOrbiterAssignSaltB[(((31U - aIndex) + 23U)) & S_SALT1]) + aNonceWordD;
            //
            aOrbiterB = (aOrbiterB + aOrbiterF) + 10894778070022873473U;
            aOrbiterD = ((aOrbiterD ^ aOrbiterB) ^ 15563886747621617467U) ^ aNonceWordO;
            aOrbiterD = RotL64((aOrbiterD * 17884709931569040065U), 35U);
            //
            aOrbiterA = (((aOrbiterA + aOrbiterB) + 11182488628562891937U) + aOrbiterUpdateSaltB[(((31U - aIndex) + 28U)) & S_SALT1]) + aNonceWordH;
            aOrbiterI = (aOrbiterI ^ aOrbiterA) ^ 10420140066310588580U;
            aOrbiterI = RotL64((aOrbiterI * 13898299782819948719U), 13U);
            //
            aOrbiterF = ((aOrbiterF + aOrbiterH) + 11775138062167543111U) + aNonceWordM;
            aOrbiterA = (aOrbiterA ^ aOrbiterF) ^ 16545391898578161683U;
            aOrbiterA = RotL64((aOrbiterA * 14588306527161321535U), 29U);
            //
            aOrbiterI = (aOrbiterI + aOrbiterD) + 1550144656312299266U;
            aOrbiterH = ((aOrbiterH ^ aOrbiterI) ^ 14903504853138279883U) ^ aOrbiterUpdateSaltC[((aIndex + 12U)) & S_SALT1];
            aOrbiterH = RotL64((aOrbiterH * 8003033561266164387U), 57U);
            //
            aOrbiterG = (aOrbiterG + aOrbiterI) + 309935535526750396U;
            aOrbiterF = (aOrbiterF ^ aOrbiterG) ^ 13991265868040011411U;
            aOrbiterF = RotL64((aOrbiterF * 2887531132228588441U), 23U);
            //
            aOrbiterH = ((aOrbiterH + aOrbiterG) + 1755976294857114222U) + aOrbiterUpdateSaltF[(((31U - aIndex) + 21U)) & S_SALT1];
            aOrbiterB = (aOrbiterB ^ aOrbiterH) ^ 2259275858478396846U;
            aOrbiterB = RotL64((aOrbiterB * 7416165760067878161U), 51U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterA) + 4838175912944552936U;
            aOrbiterG = ((aOrbiterG ^ aOrbiterD) ^ 12307900457200936013U) ^ aOrbiterUpdateSaltA[(((31U - aIndex) + 13U)) & S_SALT1];
            aOrbiterG = RotL64((aOrbiterG * 14719363144850838805U), 3U);
            //
            aIngress = aOrbiterF ^ RotL64(aOrbiterG, 51U);
            aIngress = aIngress + (RotL64(aOrbiterB, 21U) ^ aOrbiterA);
            aIngress = aIngress + (aOrbiterD ^ RotL64(aOrbiterH, 37U));
            aIngress = aIngress + RotL64(aOrbiterI, 29U);
            aIngress = TwistMix64::DiffuseB((aIngress + aScatter));
            //
            aWandererG = aWandererG + (((RotL64(aIngress, 3U) + aOrbiterB) + RotL64(aOrbiterA, 38U)) + aNonceWordE);
            aWandererC = aWandererC ^ (((RotL64(aScatter, 41U) + RotL64(aOrbiterD, 53U)) + aOrbiterA) + aNonceWordP);
            aWandererK = aWandererK + ((((RotL64(aPrevious, 19U) + aOrbiterI) + RotL64(aOrbiterH, 29U)) + RotL64(aCarry, 39U)) + aNonceWordC);
            aWandererB = aWandererB ^ (((RotL64(aCross, 11U) + RotL64(aOrbiterH, 13U)) + aOrbiterB) + aWandererUpdateSaltD[(((31U - aIndex) + 15U)) & S_SALT1]);
            aWandererF = aWandererF + (((RotL64(aScatter, 60U) + aOrbiterG) + RotL64(aOrbiterF, 5U)) + RotL64(aCarry, 13U));
            aWandererE = aWandererE ^ ((RotL64(aIngress, 53U) + RotL64(aOrbiterG, 19U)) + aOrbiterA);
            aWandererD = aWandererD + (((RotL64(aPrevious, 27U) + RotL64(aOrbiterI, 47U)) + aOrbiterG) + aWandererUpdateSaltB[((aIndex + 25U)) & S_SALT1]);
            //
            aCarry = aCarry + (RotL64(aWandererE, 19U) ^ aWandererC);
            aCarry = aCarry + (aWandererF ^ RotL64(aWandererG, 14U));
            aCarry = aCarry + (RotL64(aWandererB, 27U) ^ aWandererD);
            aCarry = aCarry + RotL64(aWandererK, 57U);
            aCarry = aCarry + RotL64(aIngress, 47U);
            aCarry = TwistMix64::DiffuseA(aCarry);
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

void TwistExpander_Greezy_Arx::KDF_B_B(TwistWorkSpace *pWorkSpace,
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
    std::uint64_t aNonceWordA = TwistMix64::DiffuseB(pNonce * 0xC44AD0A111F27ED5ULL + 0x9EB42C6B6152FFA0ULL);
    std::uint64_t aNonceWordB = TwistMix64::DiffuseA(pNonce * 0x86947FED3F6E0B51ULL + 0x94039964FEAC3A1FULL);
    std::uint64_t aNonceWordC = TwistMix64::DiffuseC(pNonce * 0xB1F0A2FD2A434397ULL + 0xE245F9310F0FFB4AULL);
    std::uint64_t aNonceWordD = TwistMix64::DiffuseC(pNonce * 0x96A7166EB726F3E3ULL + 0xF82AA4042A1FBDC9ULL);
    std::uint64_t aNonceWordE = TwistMix64::DiffuseA(pNonce * 0xCFCDE53CED548EEFULL + 0xB4E747278B575613ULL);
    std::uint64_t aNonceWordF = TwistMix64::DiffuseC(pNonce * 0xB59ADD63F7153909ULL + 0xD8F4C34EA54BA8DFULL);
    std::uint64_t aNonceWordG = TwistMix64::DiffuseB(pNonce * 0xA0C7D1425CA50885ULL + 0xD48C5EC0373AD35BULL);
    std::uint64_t aNonceWordH = TwistMix64::DiffuseB(pNonce * 0xC566138E27993BC5ULL + 0xAB5F906F8F2AB1A8ULL);
    std::uint64_t aNonceWordI = TwistMix64::DiffuseB(pNonce * 0xABE02C564704C841ULL + 0xD4BA5F9BC9B84A4CULL);
    std::uint64_t aNonceWordJ = TwistMix64::DiffuseC(pNonce * 0xAD949D84D3CF609FULL + 0x9C6E16B376060BF1ULL);
    std::uint64_t aNonceWordK = TwistMix64::DiffuseB(pNonce * 0xECB15CB54B2EEE97ULL + 0xA62DB94F6C48818AULL);
    std::uint64_t aNonceWordL = TwistMix64::DiffuseC(pNonce * 0xE759503F71BD984FULL + 0x85C14FECE20F05BEULL);
    std::uint64_t aNonceWordM = TwistMix64::DiffuseC(pNonce * 0xAF10D98F1C013141ULL + 0xE6024DA7D6A9CD9CULL);
    std::uint64_t aNonceWordN = TwistMix64::DiffuseA(pNonce * 0xF550168F0289B1EFULL + 0xEA84F3E19CC16111ULL);
    std::uint64_t aNonceWordO = TwistMix64::DiffuseC(pNonce * 0xBA4B3B98738C17BBULL + 0xC5756F9783D1B017ULL);
    std::uint64_t aNonceWordP = TwistMix64::DiffuseC(pNonce * 0xC89F357564DD2E85ULL + 0xD8E08FA05365745EULL);
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
        // read from: aExpandLaneA, aExpandLaneB, aFireLaneA, aExpandLaneC, aExpandLaneD, aFireLaneB, aOperationLaneA, aFireLaneC, aFireLaneD, aOperationLaneB, aWorkLaneA, aWorkLaneB, aOperationLaneC, aWorkLaneC, aWorkLaneD
        // write to: aOperationLaneA, aOperationLaneB, aOperationLaneC, aOperationLaneD
    
        // kdf_b_loop_b loop 1
        // ingress from: aExpandLaneA, aExpandLaneB, aFireLaneA
        // ingress directions: aExpandLaneA forward forced, aExpandLaneB forward forced, aFireLaneA forward/backward random
        // cross from: aExpandLaneC, aExpandLaneD, aFireLaneB
        // cross directions: aExpandLaneC backward forced, aExpandLaneD backward forced, aFireLaneB backward/forward random
        // write to: aOperationLaneA
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aExpandLaneA[((aIndex + 564U)) & S_BLOCK1], 41U) ^ RotL64(aExpandLaneB[((aIndex + 1920U)) & S_BLOCK1], 14U));
            aIngress ^= RotL64(aFireLaneA[((aIndex + 3919U)) & S_BLOCK1], 27U);
            aIngress = TwistMix64::DiffuseB(((aIngress ^ aDomainWordIngress) ^ aNonceWordE));
            //
            aCross = (RotL64(aExpandLaneC[((S_BLOCK1 - aIndex + 6393U)) & S_BLOCK1], 56U) ^ RotL64(aExpandLaneD[((S_BLOCK1 - aIndex + 6782U)) & S_BLOCK1], 47U));
            aCross ^= RotL64(aFireLaneB[((S_BLOCK1 - aIndex + 4059U)) & S_BLOCK1], 13U);
            aCross = TwistMix64::DiffuseC(((aCross ^ aDomainWordCross) ^ aNonceWordN));
            //
            aScatter = (RotL64(aPrevious, 43U) + RotL64(aCross, 10U)) ^ (RotL64(aIngress, 29U) + RotL64(aCarry, 57U));
            aScatter = TwistMix64::DiffuseC(((aScatter ^ aDomainWordScatter) ^ aNonceWordP));
            //
            aOrbiterJ = (((aWandererB + RotL64(aCross, 11U)) + RotL64(aCarry, 37U)) + 5906639480605353429U) + aNonceWordA;
            aOrbiterI = (((aWandererH + RotL64(aPrevious, 19U)) + RotL64(aCarry, 27U)) + 5293518570213287605U) + aOrbiterAssignSaltB[((aIndex + 3U)) & S_SALT1];
            aOrbiterA = ((aWandererK + RotL64(aIngress, 13U)) + 15383185501428521377U) + aNonceWordF;
            aOrbiterE = (aWandererA + RotL64(aScatter, 28U)) + 15364072512743978902U;
            aOrbiterH = (aWandererJ + RotL64(aCross, 51U)) + 4525473357144014271U;
            aOrbiterG = (aWandererG + RotL64(aPrevious, 43U)) + 10400911938125603074U;
            aOrbiterD = (aWandererI + RotL64(aIngress, 41U)) + 16417506293824627550U;
            aOrbiterB = (((aWandererF + RotL64(aScatter, 35U)) + RotL64(aCarry, 41U)) + 2419329331753341815U) + aOrbiterAssignSaltF[((aIndex + 18U)) & S_SALT1];
            aOrbiterF = (aWandererE + RotL64(aIngress, 54U)) + 14929222427923332069U;
            aOrbiterK = (aWandererD + RotL64(aCross, 37U)) + 16771573504983922586U;
            aOrbiterC = (aWandererC + RotL64(aPrevious, 5U)) + 1863466450051787622U;
            //
            aOrbiterJ = (aOrbiterJ + aOrbiterI) + 12895350137096692415U;
            aOrbiterA = (aOrbiterA ^ aOrbiterJ) ^ 3700979086526298327U;
            aOrbiterA = RotL64((aOrbiterA * 10279730254867618193U), 41U);
            //
            aOrbiterE = ((aOrbiterE + aOrbiterJ) + 1977099106211282426U) + aOrbiterUpdateSaltE[(((31U - aIndex) + 14U)) & S_SALT1];
            aOrbiterH = (aOrbiterH ^ aOrbiterE) ^ 6144698304096915742U;
            aOrbiterH = RotL64((aOrbiterH * 5039822990560519609U), 51U);
            //
            aOrbiterH = (aOrbiterH + aOrbiterA) + 3858895556659724975U;
            aOrbiterG = (aOrbiterG ^ aOrbiterH) ^ 1283646340363435327U;
            aOrbiterG = RotL64((aOrbiterG * 11622421841377018069U), 3U);
            //
            aOrbiterG = (aOrbiterG + aOrbiterD) + 6240532051889108891U;
            aOrbiterJ = (aOrbiterJ ^ aOrbiterG) ^ 757364889381634634U;
            aOrbiterJ = RotL64((aOrbiterJ * 943852137901972945U), 47U);
            //
            aOrbiterB = ((aOrbiterB + aOrbiterF) + 5272945693977418174U) + aOrbiterUpdateSaltB[(((31U - aIndex) + 11U)) & S_SALT1];
            aOrbiterK = (aOrbiterK ^ aOrbiterB) ^ 6850528198786172283U;
            aOrbiterK = RotL64((aOrbiterK * 1966383079897679953U), 35U);
            //
            aOrbiterA = (((aOrbiterA + aOrbiterB) + 14431587733859573714U) + aOrbiterUpdateSaltF[(((31U - aIndex) + 7U)) & S_SALT1]) + aNonceWordI;
            aOrbiterD = (aOrbiterD ^ aOrbiterA) ^ 16124590257870999553U;
            aOrbiterD = RotL64((aOrbiterD * 7755796211433191143U), 21U);
            //
            aOrbiterK = (aOrbiterK + aOrbiterE) + 14912695018110241411U;
            aOrbiterC = ((aOrbiterC ^ aOrbiterK) ^ 11098623474413346520U) ^ aOrbiterUpdateSaltC[((aIndex + 17U)) & S_SALT1];
            aOrbiterC = RotL64((aOrbiterC * 15167688959990872051U), 5U);
            //
            aOrbiterI = ((aOrbiterI + aOrbiterC) + 3484847683376368686U) + aNonceWordD;
            aOrbiterB = (aOrbiterB ^ aOrbiterI) ^ 2295388097292719800U;
            aOrbiterB = RotL64((aOrbiterB * 1240808318176106909U), 29U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterK) + 923199510066894111U;
            aOrbiterI = (aOrbiterI ^ aOrbiterD) ^ 311875852510926196U;
            aOrbiterI = RotL64((aOrbiterI * 9797881750305289335U), 43U);
            //
            aOrbiterC = (aOrbiterC + aOrbiterH) + 3543141837224843684U;
            aOrbiterF = (aOrbiterF ^ aOrbiterC) ^ 12889943043568922084U;
            aOrbiterF = RotL64((aOrbiterF * 8682278766727990427U), 39U);
            //
            aOrbiterF = ((aOrbiterF + aOrbiterG) + 6105656539077757510U) + aNonceWordC;
            aOrbiterE = (aOrbiterE ^ aOrbiterF) ^ 5906639480605353429U;
            aOrbiterE = RotL64((aOrbiterE * 9555916235293954383U), 53U);
            //
            aIngress = aOrbiterJ ^ RotL64(aOrbiterD, 51U);
            aIngress = aIngress + (RotL64(aOrbiterB, 35U) ^ aOrbiterH);
            aIngress = aIngress + (RotL64(aOrbiterI, 3U) ^ aOrbiterG);
            aIngress = aIngress + (aOrbiterE ^ RotL64(aOrbiterC, 30U));
            aIngress = aIngress + (aOrbiterA ^ RotL64(aOrbiterF, 53U));
            aIngress = aIngress + RotL64(aOrbiterK, 13U);
            aIngress = TwistMix64::DiffuseB((aIngress + aScatter));
            //
            aWandererA = aWandererA ^ (((RotL64(aPrevious, 39U) + aOrbiterK) + RotL64(aOrbiterH, 53U)) + aWandererUpdateSaltA[((aIndex + 23U)) & S_SALT1]);
            aWandererB = aWandererB + ((RotL64(aCross, 5U) + aOrbiterE) + RotL64(aOrbiterF, 43U));
            aWandererK = aWandererK ^ ((RotL64(aScatter, 53U) + aOrbiterB) + RotL64(aOrbiterK, 48U));
            aWandererF = aWandererF + ((RotL64(aIngress, 3U) + aOrbiterA) + RotL64(aOrbiterH, 21U));
            aWandererC = aWandererC ^ (((RotL64(aCross, 10U) + RotL64(aOrbiterK, 35U)) + aOrbiterD) + aNonceWordG);
            aWandererG = aWandererG + (((RotL64(aIngress, 47U) + aOrbiterK) + RotL64(aOrbiterC, 3U)) + aNonceWordL);
            aWandererD = aWandererD ^ (((RotL64(aScatter, 21U) + RotL64(aOrbiterI, 13U)) + aOrbiterJ) + aNonceWordM);
            aWandererI = aWandererI + (((RotL64(aPrevious, 43U) + aOrbiterK) + RotL64(aOrbiterE, 41U)) + RotL64(aCarry, 37U));
            aWandererE = aWandererE ^ ((RotL64(aCross, 57U) + RotL64(aOrbiterH, 39U)) + aOrbiterG);
            aWandererJ = aWandererJ + ((((RotL64(aScatter, 37U) + RotL64(aOrbiterE, 50U)) + aOrbiterI) + RotL64(aCarry, 41U)) + aWandererUpdateSaltE[((aIndex + 6U)) & S_SALT1]);
            aWandererH = aWandererH ^ ((RotL64(aPrevious, 18U) + aOrbiterD) + RotL64(aOrbiterI, 19U));
            //
            aCarry = aCarry + (RotL64(aWandererF, 3U) ^ aWandererE);
            aCarry = aCarry + (aWandererI ^ RotL64(aWandererH, 11U));
            aCarry = aCarry + (aWandererJ ^ RotL64(aWandererB, 30U));
            aCarry = aCarry + (RotL64(aWandererK, 41U) ^ aWandererG);
            aCarry = aCarry + (aWandererC ^ RotL64(aWandererA, 39U));
            aCarry = aCarry + RotL64(aWandererD, 37U);
            aCarry = aCarry + RotL64(aIngress, 28U);
            aCarry = TwistMix64::DiffuseC(aCarry);
            //
            aOperationLaneA[aIndex] = aIngress;
        }
    
        // kdf_b_loop_b loop 2
        // ingress from: aOperationLaneA, aExpandLaneC, aExpandLaneD, aFireLaneC
        // ingress directions: aOperationLaneA forward forced, aExpandLaneC forward forced, aExpandLaneD forward forced, aFireLaneC forward/backward random
        // cross from: aExpandLaneA, aExpandLaneB, aFireLaneD
        // cross directions: aExpandLaneA backward forced, aExpandLaneB backward forced, aFireLaneD backward/forward random
        // write to: aOperationLaneB
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aOperationLaneA[((aIndex + 8801U)) & S_BLOCK1], 11U) ^ RotL64(aExpandLaneC[((aIndex + 11285U)) & S_BLOCK1], 19U));
            aIngress ^= (RotL64(aExpandLaneD[((aIndex + 16025U)) & S_BLOCK1], 57U) ^ RotL64(aFireLaneC[((S_BLOCK1 - aIndex + 10160U)) & S_BLOCK1], 43U));
            aIngress = TwistMix64::DiffuseA(((aIngress ^ aDomainWordIngress) ^ aNonceWordF));
            //
            aCross = (RotL64(aExpandLaneA[((S_BLOCK1 - aIndex + 8301U)) & S_BLOCK1], 5U) ^ RotL64(aExpandLaneB[((S_BLOCK1 - aIndex + 12844U)) & S_BLOCK1], 60U));
            aCross ^= RotL64(aFireLaneD[((S_BLOCK1 - aIndex + 13356U)) & S_BLOCK1], 21U);
            aCross = TwistMix64::DiffuseA(((aCross ^ aDomainWordCross) ^ aNonceWordO));
            //
            aScatter = (RotL64(aCross, 19U) ^ RotL64(aPrevious, 5U)) ^ (RotL64(aCarry, 47U) + RotL64(aIngress, 34U));
            aScatter = TwistMix64::DiffuseB(((aScatter ^ aDomainWordScatter) ^ aNonceWordH));
            //
            aOrbiterF = (aWandererJ + RotL64(aIngress, 57U)) + 8793908991006073956U;
            aOrbiterD = ((aWandererB + RotL64(aScatter, 51U)) + 2932916283348441943U) + aOrbiterAssignSaltD[(((31U - aIndex) + 9U)) & S_SALT1];
            aOrbiterJ = (aWandererF + RotL64(aPrevious, 34U)) + 11069042087940968262U;
            aOrbiterH = (aWandererD + RotL64(aCross, 53U)) + 14369628676782894441U;
            aOrbiterI = (aWandererA + RotL64(aScatter, 5U)) + 8602903272780978282U;
            aOrbiterE = (((aWandererI + RotL64(aCross, 3U)) + RotL64(aCarry, 21U)) + 3827036107178568820U) + aNonceWordL;
            aOrbiterK = ((aWandererH + RotL64(aIngress, 19U)) + 8905245209036772489U) + aNonceWordI;
            aOrbiterC = ((aWandererE + RotL64(aPrevious, 29U)) + RotL64(aCarry, 11U)) + 13331387530760017893U;
            aOrbiterG = (aWandererK + RotL64(aCross, 21U)) + 9880107580289737823U;
            aOrbiterA = (aWandererG + RotL64(aPrevious, 11U)) + 10199619040626900278U;
            aOrbiterB = ((((aWandererC + RotL64(aIngress, 42U)) + RotL64(aCarry, 37U)) + 2466307560891374281U) + aOrbiterAssignSaltA[(((31U - aIndex) + 29U)) & S_SALT1]) + aNonceWordN;
            //
            aOrbiterF = ((aOrbiterF + aOrbiterD) + 13973403407981259448U) + aNonceWordM;
            aOrbiterJ = (aOrbiterJ ^ aOrbiterF) ^ 2851460278409385243U;
            aOrbiterJ = RotL64((aOrbiterJ * 11226902976321781743U), 53U);
            //
            aOrbiterH = (aOrbiterH + aOrbiterI) + 10365453393815690776U;
            aOrbiterE = ((aOrbiterE ^ aOrbiterH) ^ 2382382358987358791U) ^ aOrbiterUpdateSaltA[((aIndex + 3U)) & S_SALT1];
            aOrbiterE = RotL64((aOrbiterE * 481563628980705781U), 29U);
            //
            aOrbiterK = (aOrbiterK + aOrbiterC) + 5058198848163792422U;
            aOrbiterH = (aOrbiterH ^ aOrbiterK) ^ 10500434740387593487U;
            aOrbiterH = RotL64((aOrbiterH * 5946747708776079787U), 37U);
            //
            aOrbiterJ = (aOrbiterJ + aOrbiterG) + 11289798395177667084U;
            aOrbiterA = (aOrbiterA ^ aOrbiterJ) ^ 14327152153231286666U;
            aOrbiterA = RotL64((aOrbiterA * 18155778059595245561U), 5U);
            //
            aOrbiterG = (aOrbiterG + aOrbiterH) + 8065137263811956313U;
            aOrbiterB = (aOrbiterB ^ aOrbiterG) ^ 3865153574847924816U;
            aOrbiterB = RotL64((aOrbiterB * 9495741102667755161U), 39U);
            //
            aOrbiterE = ((aOrbiterE + aOrbiterF) + 18102279969722473375U) + aOrbiterUpdateSaltD[(((31U - aIndex) + 27U)) & S_SALT1];
            aOrbiterC = ((aOrbiterC ^ aOrbiterE) ^ 6306428427188742325U) ^ aNonceWordE;
            aOrbiterC = RotL64((aOrbiterC * 17826782872351406167U), 19U);
            //
            aOrbiterA = (aOrbiterA + aOrbiterB) + 16953348204663693724U;
            aOrbiterD = (aOrbiterD ^ aOrbiterA) ^ 11950791817032898613U;
            aOrbiterD = RotL64((aOrbiterD * 1498946055469611133U), 41U);
            //
            aOrbiterC = (aOrbiterC + aOrbiterJ) + 11980823193543752994U;
            aOrbiterI = ((aOrbiterI ^ aOrbiterC) ^ 17845490308799454871U) ^ aOrbiterUpdateSaltB[(((31U - aIndex) + 13U)) & S_SALT1];
            aOrbiterI = RotL64((aOrbiterI * 16385153013485463791U), 47U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterK) + 5566398755702887071U;
            aOrbiterG = (aOrbiterG ^ aOrbiterD) ^ 10308378271388889968U;
            aOrbiterG = RotL64((aOrbiterG * 142732084484961281U), 51U);
            //
            aOrbiterB = (aOrbiterB + aOrbiterE) + 6717846700455219260U;
            aOrbiterK = (aOrbiterK ^ aOrbiterB) ^ 8297225372883997017U;
            aOrbiterK = RotL64((aOrbiterK * 14102812043481327907U), 27U);
            //
            aOrbiterI = (aOrbiterI + aOrbiterA) + 12249337046267666603U;
            aOrbiterF = ((aOrbiterF ^ aOrbiterI) ^ 8793908991006073956U) ^ aOrbiterUpdateSaltE[((aIndex + 16U)) & S_SALT1];
            aOrbiterF = RotL64((aOrbiterF * 5851229209188473467U), 21U);
            //
            aIngress = RotL64(aOrbiterC, 54U) ^ aOrbiterJ;
            aIngress = aIngress + (RotL64(aOrbiterE, 13U) ^ aOrbiterI);
            aIngress = aIngress + (aOrbiterD ^ RotL64(aOrbiterH, 19U));
            aIngress = aIngress + (RotL64(aOrbiterB, 23U) ^ aOrbiterG);
            aIngress = aIngress + (RotL64(aOrbiterF, 47U) ^ aOrbiterA);
            aIngress = aIngress + RotL64(aOrbiterK, 57U);
            aIngress = TwistMix64::DiffuseC((aIngress + aScatter));
            //
            aWandererD = aWandererD + ((RotL64(aIngress, 51U) + RotL64(aOrbiterB, 3U)) + aOrbiterF);
            aWandererB = aWandererB ^ (((RotL64(aCross, 10U) + RotL64(aOrbiterE, 35U)) + aOrbiterK) + aWandererUpdateSaltB[(((31U - aIndex) + 7U)) & S_SALT1]);
            aWandererE = aWandererE + (((RotL64(aPrevious, 53U) + aOrbiterH) + RotL64(aOrbiterG, 29U)) + RotL64(aCarry, 3U));
            aWandererF = aWandererF ^ ((RotL64(aScatter, 5U) + RotL64(aOrbiterJ, 58U)) + aOrbiterG);
            aWandererJ = aWandererJ + ((RotL64(aPrevious, 41U) + RotL64(aOrbiterE, 37U)) + aOrbiterA);
            aWandererK = aWandererK ^ (((RotL64(aCross, 34U) + aOrbiterH) + RotL64(aOrbiterB, 53U)) + aNonceWordC);
            aWandererA = aWandererA + ((((RotL64(aScatter, 3U) + RotL64(aOrbiterC, 5U)) + aOrbiterK) + RotL64(aCarry, 29U)) + aNonceWordP);
            aWandererI = aWandererI ^ ((RotL64(aIngress, 23U) + aOrbiterH) + RotL64(aOrbiterI, 27U));
            aWandererC = aWandererC + ((RotL64(aPrevious, 13U) + aOrbiterD) + RotL64(aOrbiterK, 43U));
            aWandererH = aWandererH ^ ((RotL64(aScatter, 27U) + RotL64(aOrbiterE, 47U)) + aOrbiterH);
            aWandererG = aWandererG + (((RotL64(aIngress, 47U) + aOrbiterF) + RotL64(aOrbiterD, 60U)) + aWandererUpdateSaltD[((aIndex + 20U)) & S_SALT1]);
            //
            aCarry = aCarry + (RotL64(aWandererH, 43U) ^ aWandererA);
            aCarry = aCarry + (aWandererJ ^ RotL64(aWandererE, 4U));
            aCarry = aCarry + (aWandererF ^ RotL64(aWandererK, 51U));
            aCarry = aCarry + (RotL64(aWandererC, 13U) ^ aWandererB);
            aCarry = aCarry + (RotL64(aWandererI, 29U) ^ aWandererG);
            aCarry = aCarry + RotL64(aWandererD, 34U);
            aCarry = aCarry + RotL64(aIngress, 19U);
            aCarry = TwistMix64::DiffuseC(aCarry);
            //
            aOperationLaneB[S_BLOCK1 - aIndex] = aIngress;
        }
    
        // kdf_b_loop_b loop 3
        // ingress from: aOperationLaneB, aExpandLaneA, aExpandLaneB, aWorkLaneA
        // ingress directions: aOperationLaneB forward forced, aExpandLaneA forward forced, aExpandLaneB forward forced, aWorkLaneA forward/backward random
        // cross from: aOperationLaneA, aExpandLaneC, aWorkLaneB
        // cross directions: aOperationLaneA backward forced, aExpandLaneC backward forced, aWorkLaneB backward/forward random
        // write to: aOperationLaneC
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aOperationLaneB[((aIndex + 23100U)) & S_BLOCK1], 5U) ^ RotL64(aExpandLaneA[((aIndex + 20667U)) & S_BLOCK1], 13U));
            aIngress ^= (RotL64(aExpandLaneB[((aIndex + 16569U)) & S_BLOCK1], 60U) ^ RotL64(aWorkLaneA[((aIndex + 18014U)) & S_BLOCK1], 21U));
            aIngress = TwistMix64::DiffuseC(((aIngress ^ aDomainWordIngress) ^ aNonceWordN));
            //
            aCross = (RotL64(aOperationLaneA[((S_BLOCK1 - aIndex + 17206U)) & S_BLOCK1], 3U) ^ RotL64(aExpandLaneC[((S_BLOCK1 - aIndex + 21269U)) & S_BLOCK1], 21U));
            aCross ^= RotL64(aWorkLaneB[((S_BLOCK1 - aIndex + 20228U)) & S_BLOCK1], 53U);
            aCross = TwistMix64::DiffuseC(((aCross ^ aDomainWordCross) ^ aNonceWordC));
            //
            aScatter = (RotL64(aIngress, 5U) ^ RotL64(aCross, 48U)) + (RotL64(aPrevious, 35U) + RotL64(aCarry, 19U));
            aScatter = TwistMix64::DiffuseA(((aScatter ^ aDomainWordScatter) ^ aNonceWordC));
            //
            aOrbiterI = ((aWandererF + RotL64(aCross, 10U)) + 5573188770530340913U) + aNonceWordP;
            aOrbiterB = (aWandererE + RotL64(aPrevious, 21U)) + 1431772230889897111U;
            aOrbiterG = ((aWandererI + RotL64(aIngress, 37U)) + 4809192776429682319U) + aNonceWordH;
            aOrbiterD = ((aWandererJ + RotL64(aScatter, 53U)) + RotL64(aCarry, 57U)) + 5576603692574369341U;
            aOrbiterJ = (((aWandererH + RotL64(aPrevious, 19U)) + RotL64(aCarry, 19U)) + 2720143226007220386U) + aOrbiterAssignSaltE[((aIndex + 25U)) & S_SALT1];
            aOrbiterK = ((aWandererA + RotL64(aIngress, 48U)) + RotL64(aCarry, 29U)) + 17220328778565331629U;
            aOrbiterA = ((aWandererB + RotL64(aCross, 3U)) + 9629485808442089423U) + aNonceWordM;
            aOrbiterF = ((aWandererD + RotL64(aScatter, 35U)) + 1136998437010390983U) + aOrbiterAssignSaltC[((aIndex + 21U)) & S_SALT1];
            aOrbiterH = (aWandererG + RotL64(aCross, 57U)) + 11893390497814523841U;
            aOrbiterE = ((aWandererK + RotL64(aScatter, 43U)) + 1764986431917532370U) + aNonceWordE;
            aOrbiterC = (aWandererC + RotL64(aPrevious, 23U)) + 1741014798007010376U;
            //
            aOrbiterI = (((aOrbiterI + aOrbiterB) + 12221368453236547044U) + aOrbiterUpdateSaltD[(((31U - aIndex) + 18U)) & S_SALT1]) + aNonceWordJ;
            aOrbiterG = (aOrbiterG ^ aOrbiterI) ^ 7694538641172350430U;
            aOrbiterG = RotL64((aOrbiterG * 8439120733670016501U), 19U);
            //
            aOrbiterG = ((aOrbiterG + aOrbiterD) + 17472344518811560603U) + aOrbiterUpdateSaltC[(((31U - aIndex) + 13U)) & S_SALT1];
            aOrbiterJ = (aOrbiterJ ^ aOrbiterG) ^ 3308740700728172984U;
            aOrbiterJ = RotL64((aOrbiterJ * 15290400462887712083U), 51U);
            //
            aOrbiterK = (aOrbiterK + aOrbiterI) + 9535358833412446771U;
            aOrbiterA = (aOrbiterA ^ aOrbiterK) ^ 11192312491731312451U;
            aOrbiterA = RotL64((aOrbiterA * 17405609148475445743U), 27U);
            //
            aOrbiterF = ((aOrbiterF + aOrbiterH) + 14850451970047190039U) + aNonceWordD;
            aOrbiterI = (aOrbiterI ^ aOrbiterF) ^ 11932493299452443256U;
            aOrbiterI = RotL64((aOrbiterI * 7964808728820467795U), 57U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterE) + 5972619895614731870U;
            aOrbiterF = (aOrbiterF ^ aOrbiterD) ^ 17174497535809891690U;
            aOrbiterF = RotL64((aOrbiterF * 15471084511364572533U), 41U);
            //
            aOrbiterA = (aOrbiterA + aOrbiterG) + 17412894714378898351U;
            aOrbiterC = (aOrbiterC ^ aOrbiterA) ^ 14675615208706549810U;
            aOrbiterC = RotL64((aOrbiterC * 7864845089606499769U), 21U);
            //
            aOrbiterJ = (aOrbiterJ + aOrbiterF) + 16116792108013658523U;
            aOrbiterK = ((aOrbiterK ^ aOrbiterJ) ^ 9702262005960966336U) ^ aNonceWordL;
            aOrbiterK = RotL64((aOrbiterK * 970452849653781703U), 47U);
            //
            aOrbiterE = (aOrbiterE + aOrbiterK) + 17337264966818542841U;
            aOrbiterH = ((aOrbiterH ^ aOrbiterE) ^ 7004462033775827275U) ^ aOrbiterUpdateSaltA[((aIndex + 29U)) & S_SALT1];
            aOrbiterH = RotL64((aOrbiterH * 11943575980344402681U), 13U);
            //
            aOrbiterC = (aOrbiterC + aOrbiterJ) + 17499850384482055438U;
            aOrbiterE = (aOrbiterE ^ aOrbiterC) ^ 1839357713256560566U;
            aOrbiterE = RotL64((aOrbiterE * 12943750650487416281U), 39U);
            //
            aOrbiterH = (aOrbiterH + aOrbiterA) + 8144238113917577524U;
            aOrbiterB = (aOrbiterB ^ aOrbiterH) ^ 888195876227325908U;
            aOrbiterB = RotL64((aOrbiterB * 7941506708630993709U), 35U);
            //
            aOrbiterB = ((aOrbiterB + aOrbiterC) + 5081763359501717653U) + aOrbiterUpdateSaltB[(((31U - aIndex) + 22U)) & S_SALT1];
            aOrbiterD = (aOrbiterD ^ aOrbiterB) ^ 5573188770530340913U;
            aOrbiterD = RotL64((aOrbiterD * 9699901099898698965U), 5U);
            //
            aIngress = RotL64(aOrbiterC, 21U) ^ aOrbiterK;
            aIngress = aIngress + (RotL64(aOrbiterH, 23U) ^ aOrbiterE);
            aIngress = aIngress + (aOrbiterJ ^ RotL64(aOrbiterB, 26U));
            aIngress = aIngress + (RotL64(aOrbiterD, 29U) ^ aOrbiterI);
            aIngress = aIngress + (aOrbiterA ^ RotL64(aOrbiterG, 57U));
            aIngress = aIngress + RotL64(aOrbiterF, 3U);
            aIngress = TwistMix64::DiffuseB((aIngress + aScatter));
            //
            aWandererJ = aWandererJ + (((RotL64(aScatter, 53U) + aOrbiterI) + RotL64(aOrbiterF, 51U)) + aNonceWordG);
            aWandererA = aWandererA ^ ((RotL64(aCross, 19U) + aOrbiterG) + RotL64(aOrbiterK, 19U));
            aWandererB = aWandererB + (((RotL64(aIngress, 23U) + RotL64(aOrbiterC, 58U)) + aOrbiterJ) + aWandererUpdateSaltF[(((31U - aIndex) + 10U)) & S_SALT1]);
            aWandererC = aWandererC ^ ((RotL64(aPrevious, 26U) + aOrbiterJ) + RotL64(aOrbiterB, 41U));
            aWandererF = aWandererF + ((((RotL64(aScatter, 39U) + aOrbiterI) + RotL64(aOrbiterC, 29U)) + RotL64(aCarry, 35U)) + aNonceWordI);
            aWandererG = aWandererG ^ ((RotL64(aPrevious, 29U) + aOrbiterC) + RotL64(aOrbiterG, 37U));
            aWandererK = aWandererK + (((RotL64(aCross, 3U) + RotL64(aOrbiterH, 10U)) + aOrbiterA) + RotL64(aCarry, 51U));
            aWandererE = aWandererE ^ (((RotL64(aIngress, 5U) + aOrbiterA) + RotL64(aOrbiterE, 21U)) + aNonceWordK);
            aWandererI = aWandererI + ((RotL64(aScatter, 35U) + aOrbiterH) + RotL64(aOrbiterF, 27U));
            aWandererD = aWandererD ^ ((RotL64(aCross, 57U) + RotL64(aOrbiterJ, 3U)) + aOrbiterI);
            aWandererH = aWandererH + (((RotL64(aPrevious, 44U) + aOrbiterF) + RotL64(aOrbiterD, 47U)) + aWandererUpdateSaltC[((aIndex + 12U)) & S_SALT1]);
            //
            aCarry = aCarry + (RotL64(aWandererA, 60U) ^ aWandererI);
            aCarry = aCarry + (RotL64(aWandererD, 35U) ^ aWandererE);
            aCarry = aCarry + (RotL64(aWandererF, 27U) ^ aWandererB);
            aCarry = aCarry + (RotL64(aWandererC, 43U) ^ aWandererK);
            aCarry = aCarry + (aWandererH ^ RotL64(aWandererJ, 30U));
            aCarry = aCarry + RotL64(aWandererG, 11U);
            aCarry = aCarry + RotL64(aIngress, 39U);
            aCarry = TwistMix64::DiffuseB(aCarry);
            //
            aOperationLaneC[aIndex] = aIngress;
        }
    
        // kdf_b_loop_b loop 4
        // ingress from: aOperationLaneC, aOperationLaneA, aExpandLaneD, aWorkLaneC
        // ingress directions: aOperationLaneC forward forced, aOperationLaneA forward forced, aExpandLaneD forward forced, aWorkLaneC forward/backward random
        // cross from: aOperationLaneB, aExpandLaneB, aWorkLaneD
        // cross directions: aOperationLaneB backward forced, aExpandLaneB backward forced, aWorkLaneD backward/forward random
        // write to: aOperationLaneD
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aOperationLaneC[((aIndex + 29260U)) & S_BLOCK1], 11U) ^ RotL64(aOperationLaneA[((aIndex + 30900U)) & S_BLOCK1], 19U));
            aIngress ^= (RotL64(aExpandLaneD[((aIndex + 31592U)) & S_BLOCK1], 27U) ^ RotL64(aWorkLaneC[((S_BLOCK1 - aIndex + 28455U)) & S_BLOCK1], 39U));
            aIngress = TwistMix64::DiffuseB(((aIngress ^ aDomainWordIngress) ^ aNonceWordO));
            //
            aCross = (RotL64(aOperationLaneB[((S_BLOCK1 - aIndex + 28140U)) & S_BLOCK1], 37U) ^ RotL64(aExpandLaneB[((S_BLOCK1 - aIndex + 28098U)) & S_BLOCK1], 4U));
            aCross ^= RotL64(aWorkLaneD[((S_BLOCK1 - aIndex + 25694U)) & S_BLOCK1], 27U);
            aCross = TwistMix64::DiffuseA(((aCross ^ aDomainWordCross) ^ aNonceWordM));
            //
            aScatter = (RotL64(aCross, 51U) ^ RotL64(aIngress, 21U)) + (RotL64(aPrevious, 3U) + RotL64(aCarry, 38U));
            aScatter = TwistMix64::DiffuseB(((aScatter ^ aDomainWordScatter) ^ aNonceWordB));
            //
            aOrbiterH = (aWandererH + RotL64(aIngress, 58U)) + 6733949564325516029U;
            aOrbiterD = (aWandererE + RotL64(aCross, 41U)) + 7304098437143918796U;
            aOrbiterG = ((aWandererB + RotL64(aPrevious, 27U)) + RotL64(aCarry, 39U)) + 3923949518391777800U;
            aOrbiterC = (((aWandererA + RotL64(aScatter, 13U)) + 14243591003388927124U) + aOrbiterAssignSaltB[((aIndex + 15U)) & S_SALT1]) + aNonceWordD;
            aOrbiterB = (aWandererK + RotL64(aPrevious, 44U)) + 18329498724605410406U;
            aOrbiterE = (aWandererC + RotL64(aCross, 53U)) + 13118172167747037249U;
            aOrbiterI = (aWandererG + RotL64(aIngress, 47U)) + 5272025143849174212U;
            aOrbiterA = (aWandererF + RotL64(aScatter, 19U)) + 16075917179214318424U;
            aOrbiterK = ((((aWandererD + RotL64(aIngress, 23U)) + RotL64(aCarry, 21U)) + 15263590648674658399U) + aOrbiterAssignSaltF[(((31U - aIndex) + 12U)) & S_SALT1]) + aNonceWordN;
            aOrbiterF = (aWandererJ + RotL64(aPrevious, 35U)) + 13730046728289525921U;
            aOrbiterJ = ((aWandererI + RotL64(aScatter, 37U)) + RotL64(aCarry, 35U)) + 7703141464499623408U;
            //
            aOrbiterH = (aOrbiterH + aOrbiterD) + 1382279753822135359U;
            aOrbiterG = (aOrbiterG ^ aOrbiterH) ^ 2973369221699098292U;
            aOrbiterG = RotL64((aOrbiterG * 7440242040663550631U), 35U);
            //
            aOrbiterC = (((aOrbiterC + aOrbiterG) + 11578274119583013219U) + aOrbiterUpdateSaltC[(((31U - aIndex) + 5U)) & S_SALT1]) + aNonceWordK;
            aOrbiterB = (aOrbiterB ^ aOrbiterC) ^ 3419411247737896674U;
            aOrbiterB = RotL64((aOrbiterB * 17814942652262802991U), 57U);
            //
            aOrbiterE = ((aOrbiterE + aOrbiterB) + 2582783513078999303U) + aNonceWordI;
            aOrbiterI = ((aOrbiterI ^ aOrbiterE) ^ 3959762790273529677U) ^ aOrbiterUpdateSaltA[((aIndex + 17U)) & S_SALT1];
            aOrbiterI = RotL64((aOrbiterI * 383974377372162751U), 29U);
            //
            aOrbiterA = (aOrbiterA + aOrbiterK) + 465795011576934604U;
            aOrbiterD = (aOrbiterD ^ aOrbiterA) ^ 17880826624185821135U;
            aOrbiterD = RotL64((aOrbiterD * 4445949147592860913U), 43U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterC) + 10819659185349413173U;
            aOrbiterE = (aOrbiterE ^ aOrbiterD) ^ 17298208553586835030U;
            aOrbiterE = RotL64((aOrbiterE * 1965860510614222093U), 11U);
            //
            aOrbiterF = ((aOrbiterF + aOrbiterA) + 12585880006661489402U) + aOrbiterUpdateSaltF[((aIndex + 21U)) & S_SALT1];
            aOrbiterH = (aOrbiterH ^ aOrbiterF) ^ 16650193903267408586U;
            aOrbiterH = RotL64((aOrbiterH * 5781132589396936615U), 53U);
            //
            aOrbiterG = (aOrbiterG + aOrbiterE) + 885882046325991589U;
            aOrbiterJ = (aOrbiterJ ^ aOrbiterG) ^ 869560078374809974U;
            aOrbiterJ = RotL64((aOrbiterJ * 13440973563438747181U), 23U);
            //
            aOrbiterJ = (aOrbiterJ + aOrbiterI) + 11871305571797951851U;
            aOrbiterA = (aOrbiterA ^ aOrbiterJ) ^ 12137095015607196226U;
            aOrbiterA = RotL64((aOrbiterA * 7618152256560808581U), 37U);
            //
            aOrbiterK = (aOrbiterK + aOrbiterH) + 6044048326509186958U;
            aOrbiterC = ((aOrbiterC ^ aOrbiterK) ^ 622564532811968856U) ^ aNonceWordC;
            aOrbiterC = RotL64((aOrbiterC * 14988345089359014037U), 39U);
            //
            aOrbiterI = (aOrbiterI + aOrbiterF) + 17133994029325040272U;
            aOrbiterK = (aOrbiterK ^ aOrbiterI) ^ 8612895899003926829U;
            aOrbiterK = RotL64((aOrbiterK * 2128664397481732179U), 3U);
            //
            aOrbiterB = (((aOrbiterB + aOrbiterJ) + 2169081503433534750U) + aOrbiterUpdateSaltE[(((31U - aIndex) + 14U)) & S_SALT1]) + aNonceWordA;
            aOrbiterF = (aOrbiterF ^ aOrbiterB) ^ 6733949564325516029U;
            aOrbiterF = RotL64((aOrbiterF * 10062179904046311601U), 27U);
            //
            aIngress = aOrbiterD ^ RotL64(aOrbiterA, 35U);
            aIngress = aIngress + (aOrbiterB ^ RotL64(aOrbiterK, 3U));
            aIngress = aIngress + (aOrbiterF ^ RotL64(aOrbiterC, 6U));
            aIngress = aIngress + (aOrbiterE ^ RotL64(aOrbiterJ, 53U));
            aIngress = aIngress + (RotL64(aOrbiterI, 43U) ^ aOrbiterG);
            aIngress = aIngress + RotL64(aOrbiterH, 51U);
            aIngress = TwistMix64::DiffuseC((aIngress + aScatter));
            //
            aWandererJ = aWandererJ ^ ((RotL64(aCross, 29U) + aOrbiterB) + RotL64(aOrbiterJ, 47U));
            aWandererC = aWandererC + (((RotL64(aPrevious, 43U) + aOrbiterF) + RotL64(aOrbiterI, 3U)) + aWandererUpdateSaltA[(((31U - aIndex) + 13U)) & S_SALT1]);
            aWandererK = aWandererK ^ (((RotL64(aIngress, 13U) + RotL64(aOrbiterI, 12U)) + aOrbiterK) + aWandererUpdateSaltE[((aIndex + 28U)) & S_SALT1]);
            aWandererG = aWandererG + (((RotL64(aScatter, 11U) + RotL64(aOrbiterB, 21U)) + aOrbiterD) + aNonceWordP);
            aWandererI = aWandererI ^ ((RotL64(aCross, 47U) + RotL64(aOrbiterE, 51U)) + aOrbiterK);
            aWandererF = aWandererF + (((RotL64(aIngress, 26U) + aOrbiterD) + RotL64(aOrbiterE, 29U)) + RotL64(aCarry, 23U));
            aWandererE = aWandererE ^ ((RotL64(aPrevious, 51U) + aOrbiterH) + RotL64(aOrbiterF, 19U));
            aWandererA = aWandererA + ((RotL64(aScatter, 39U) + RotL64(aOrbiterC, 57U)) + aOrbiterG);
            aWandererH = aWandererH ^ (((RotL64(aIngress, 3U) + RotL64(aOrbiterG, 39U)) + aOrbiterF) + aNonceWordG);
            aWandererB = aWandererB + (((RotL64(aCross, 53U) + RotL64(aOrbiterI, 26U)) + aOrbiterC) + RotL64(aCarry, 57U));
            aWandererD = aWandererD ^ ((RotL64(aScatter, 18U) + aOrbiterE) + RotL64(aOrbiterA, 41U));
            //
            aCarry = aCarry + (RotL64(aWandererG, 34U) ^ aWandererK);
            aCarry = aCarry + (aWandererE ^ RotL64(aWandererJ, 19U));
            aCarry = aCarry + (aWandererB ^ RotL64(aWandererH, 5U));
            aCarry = aCarry + (aWandererI ^ RotL64(aWandererF, 3U));
            aCarry = aCarry + (RotL64(aWandererA, 43U) ^ aWandererC);
            aCarry = aCarry + RotL64(aWandererD, 57U);
            aCarry = aCarry + RotL64(aIngress, 14U);
            aCarry = TwistMix64::DiffuseA(aCarry);
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

void TwistExpander_Greezy_Arx::KDF_B_C(TwistWorkSpace *pWorkSpace,
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
    std::uint64_t aNonceWordA = TwistMix64::DiffuseC(pNonce * 0xC046D3233654C691ULL + 0x84886E5E189BE7C6ULL);
    std::uint64_t aNonceWordB = TwistMix64::DiffuseA(pNonce * 0xB2B7A7CE0A5D347DULL + 0x8FA50767BD471FDCULL);
    std::uint64_t aNonceWordC = TwistMix64::DiffuseB(pNonce * 0xD66CEB4A28C18B4BULL + 0x86B31D328E8C483BULL);
    std::uint64_t aNonceWordD = TwistMix64::DiffuseB(pNonce * 0x8B4E7D0354871BAFULL + 0xE8BF28A9247E76D7ULL);
    std::uint64_t aNonceWordE = TwistMix64::DiffuseB(pNonce * 0xE076C9D4404588F7ULL + 0xC041AD44AD7C2084ULL);
    std::uint64_t aNonceWordF = TwistMix64::DiffuseC(pNonce * 0x824FA7620306A1A1ULL + 0xF345B689029DD974ULL);
    std::uint64_t aNonceWordG = TwistMix64::DiffuseA(pNonce * 0x889F4F06D6A3562FULL + 0xDC4C0D29718F2AC4ULL);
    std::uint64_t aNonceWordH = TwistMix64::DiffuseB(pNonce * 0xB1D07A947E3C1AD1ULL + 0xB6E8E5E1C71BB28FULL);
    std::uint64_t aNonceWordI = TwistMix64::DiffuseA(pNonce * 0x8979E0FB0A229B0DULL + 0xF53EFF3AD390C946ULL);
    std::uint64_t aNonceWordJ = TwistMix64::DiffuseB(pNonce * 0x875D8EBDB38E0B73ULL + 0x800C10E348249890ULL);
    std::uint64_t aNonceWordK = TwistMix64::DiffuseA(pNonce * 0x8A2986085AFB8569ULL + 0xC53EC30BC6DFFE3DULL);
    std::uint64_t aNonceWordL = TwistMix64::DiffuseC(pNonce * 0xEBD41A808D46BAADULL + 0xC080A240D3560E27ULL);
    std::uint64_t aNonceWordM = TwistMix64::DiffuseC(pNonce * 0xFAE9748AAEE140E1ULL + 0xC84BB331627B166CULL);
    std::uint64_t aNonceWordN = TwistMix64::DiffuseA(pNonce * 0xFAB06048C41D559FULL + 0x9DEED22A8C7AFC0FULL);
    std::uint64_t aNonceWordO = TwistMix64::DiffuseC(pNonce * 0xA2CBDE99C79F86DFULL + 0xE1E962B11302B34FULL);
    std::uint64_t aNonceWordP = TwistMix64::DiffuseA(pNonce * 0xDD3E49E8F33B3D87ULL + 0x8032B6A8A4C51B5DULL);
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
        // read from: aOperationLaneA, aOperationLaneB, aFireLaneA, aOperationLaneC, aOperationLaneD, aFireLaneB, aExpandLaneA, aFireLaneC, aFireLaneD, aExpandLaneB, aWorkLaneA, aWorkLaneB, aExpandLaneC, aWorkLaneC, aWorkLaneD
        // write to: aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD
    
        // kdf_b_loop_c loop 1
        // ingress from: aOperationLaneA, aOperationLaneB, aFireLaneA
        // ingress directions: aOperationLaneA forward forced, aOperationLaneB forward forced, aFireLaneA forward/backward random
        // cross from: aOperationLaneC, aOperationLaneD, aFireLaneB
        // cross directions: aOperationLaneC backward forced, aOperationLaneD backward forced, aFireLaneB backward/forward random
        // write to: aExpandLaneA
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aOperationLaneA[((aIndex + 282U)) & S_BLOCK1], 29U) ^ RotL64(aOperationLaneB[((aIndex + 8103U)) & S_BLOCK1], 21U));
            aIngress ^= RotL64(aFireLaneA[((aIndex + 4498U)) & S_BLOCK1], 37U);
            aIngress = TwistMix64::DiffuseC(((aIngress ^ aDomainWordIngress) ^ aNonceWordI));
            //
            aCross = (RotL64(aOperationLaneC[((S_BLOCK1 - aIndex + 6778U)) & S_BLOCK1], 23U) ^ RotL64(aOperationLaneD[((S_BLOCK1 - aIndex + 938U)) & S_BLOCK1], 3U));
            aCross ^= RotL64(aFireLaneB[((S_BLOCK1 - aIndex + 6291U)) & S_BLOCK1], 44U);
            aCross = TwistMix64::DiffuseC(((aCross ^ aDomainWordCross) ^ aNonceWordD));
            //
            aScatter = (RotL64(aPrevious, 50U) + RotL64(aCarry, 19U)) ^ (RotL64(aIngress, 5U) + RotL64(aCross, 35U));
            aScatter = TwistMix64::DiffuseB(((aScatter ^ aDomainWordScatter) ^ aNonceWordE));
            //
            aOrbiterH = ((aWandererF + RotL64(aScatter, 19U)) + 15045917390223766480U) + aOrbiterAssignSaltC[((aIndex + 4U)) & S_SALT1];
            aOrbiterK = (((aWandererB + RotL64(aPrevious, 13U)) + RotL64(aCarry, 19U)) + 10763054007033668758U) + aOrbiterAssignSaltE[(((31U - aIndex) + 22U)) & S_SALT1];
            aOrbiterC = ((aWandererG + RotL64(aCross, 51U)) + RotL64(aCarry, 29U)) + 13190170142593666607U;
            aOrbiterB = (aWandererE + RotL64(aIngress, 24U)) + 9657025731441167065U;
            aOrbiterE = (aWandererJ + RotL64(aPrevious, 29U)) + 11433367178975954211U;
            aOrbiterG = ((aWandererH + RotL64(aIngress, 43U)) + RotL64(aCarry, 41U)) + 17904920143996810366U;
            aOrbiterA = ((aWandererK + RotL64(aScatter, 39U)) + 3244383020512113283U) + aNonceWordE;
            aOrbiterI = ((aWandererC + RotL64(aCross, 6U)) + 6538815775171139091U) + aNonceWordH;
            aOrbiterF = (aWandererA + RotL64(aScatter, 35U)) + 7195368312757976343U;
            //
            aOrbiterH = (aOrbiterH + aOrbiterK) + 18134430713910279374U;
            aOrbiterC = (aOrbiterC ^ aOrbiterH) ^ 6571776588427107976U;
            aOrbiterC = RotL64((aOrbiterC * 11916502085252589161U), 19U);
            //
            aOrbiterB = (aOrbiterB + aOrbiterE) + 11830778129647517758U;
            aOrbiterG = ((aOrbiterG ^ aOrbiterB) ^ 9793702760907767365U) ^ aOrbiterUpdateSaltD[((aIndex + 21U)) & S_SALT1];
            aOrbiterG = RotL64((aOrbiterG * 4096246227968677179U), 47U);
            //
            aOrbiterA = (aOrbiterA + aOrbiterG) + 2287235876793192036U;
            aOrbiterI = (aOrbiterI ^ aOrbiterA) ^ 8951959188326141794U;
            aOrbiterI = RotL64((aOrbiterI * 9968356718110753845U), 23U);
            //
            aOrbiterF = (aOrbiterF + aOrbiterA) + 7583061790273240157U;
            aOrbiterK = (aOrbiterK ^ aOrbiterF) ^ 3571364625022806085U;
            aOrbiterK = RotL64((aOrbiterK * 6238360922735480669U), 57U);
            //
            aOrbiterE = (aOrbiterE + aOrbiterC) + 13869345563551689212U;
            aOrbiterF = (aOrbiterF ^ aOrbiterE) ^ 277480328952975002U;
            aOrbiterF = RotL64((aOrbiterF * 1057564597096163085U), 53U);
            //
            aOrbiterK = (aOrbiterK + aOrbiterI) + 4983735092494677578U;
            aOrbiterB = ((aOrbiterB ^ aOrbiterK) ^ 9490022869381030928U) ^ aOrbiterUpdateSaltC[(((31U - aIndex) + 6U)) & S_SALT1];
            aOrbiterB = RotL64((aOrbiterB * 12926352917961703123U), 43U);
            //
            aOrbiterI = ((aOrbiterI + aOrbiterH) + 7928039573014765566U) + aOrbiterUpdateSaltE[((aIndex + 29U)) & S_SALT1];
            aOrbiterE = (((aOrbiterE ^ aOrbiterI) ^ 6504190875809407084U) ^ aOrbiterUpdateSaltF[(((31U - aIndex) + 17U)) & S_SALT1]) ^ aNonceWordC;
            aOrbiterE = RotL64((aOrbiterE * 14648214826494826711U), 11U);
            //
            aOrbiterG = (aOrbiterG + aOrbiterF) + 2787985600176307413U;
            aOrbiterH = ((aOrbiterH ^ aOrbiterG) ^ 16308785053443116826U) ^ aNonceWordF;
            aOrbiterH = RotL64((aOrbiterH * 17867565986311256691U), 35U);
            //
            aOrbiterC = (aOrbiterC + aOrbiterB) + 12788128335006767824U;
            aOrbiterA = (aOrbiterA ^ aOrbiterC) ^ 1187040019537798339U;
            aOrbiterA = RotL64((aOrbiterA * 10834905007658184183U), 3U);
            //
            aIngress = RotL64(aOrbiterC, 5U) ^ aOrbiterA;
            aIngress = aIngress + (aOrbiterI ^ RotL64(aOrbiterK, 39U));
            aIngress = aIngress + (RotL64(aOrbiterE, 57U) ^ aOrbiterB);
            aIngress = aIngress + (aOrbiterH ^ RotL64(aOrbiterF, 50U));
            aIngress = aIngress + RotL64(aOrbiterG, 43U);
            aIngress = TwistMix64::DiffuseC((aIngress + aScatter));
            //
            aWandererG = aWandererG + ((RotL64(aPrevious, 34U) + aOrbiterA) + RotL64(aOrbiterC, 29U));
            aWandererH = aWandererH ^ (((RotL64(aScatter, 57U) + aOrbiterF) + RotL64(aOrbiterH, 19U)) + aWandererUpdateSaltA[((aIndex + 11U)) & S_SALT1]);
            aWandererC = aWandererC + (((RotL64(aCross, 47U) + aOrbiterH) + RotL64(aOrbiterI, 24U)) + aNonceWordM);
            aWandererF = aWandererF ^ (((RotL64(aIngress, 51U) + RotL64(aOrbiterK, 41U)) + aOrbiterF) + aNonceWordL);
            aWandererA = aWandererA + ((((RotL64(aScatter, 22U) + RotL64(aOrbiterC, 3U)) + aOrbiterG) + RotL64(aCarry, 11U)) + aNonceWordJ);
            aWandererE = aWandererE ^ (((RotL64(aIngress, 29U) + RotL64(aOrbiterI, 51U)) + aOrbiterC) + aWandererUpdateSaltD[(((31U - aIndex) + 8U)) & S_SALT1]);
            aWandererK = aWandererK + ((RotL64(aPrevious, 41U) + aOrbiterB) + RotL64(aOrbiterA, 14U));
            aWandererB = aWandererB ^ ((RotL64(aCross, 11U) + RotL64(aOrbiterB, 57U)) + aOrbiterE);
            aWandererJ = aWandererJ + (((RotL64(aIngress, 3U) + aOrbiterH) + RotL64(aOrbiterC, 37U)) + RotL64(aCarry, 47U));
            //
            aCarry = aCarry + (RotL64(aWandererB, 39U) ^ aWandererJ);
            aCarry = aCarry + (RotL64(aWandererF, 50U) ^ aWandererK);
            aCarry = aCarry + (aWandererA ^ RotL64(aWandererE, 35U));
            aCarry = aCarry + (RotL64(aWandererG, 47U) ^ aWandererH);
            aCarry = aCarry + RotL64(aWandererC, 57U);
            aCarry = aCarry + RotL64(aIngress, 11U);
            aCarry = TwistMix64::DiffuseA(aCarry);
            //
            aExpandLaneA[aIndex] = aIngress;
        }
    
        // kdf_b_loop_c loop 2
        // ingress from: aExpandLaneA, aOperationLaneC, aOperationLaneD, aFireLaneC
        // ingress directions: aExpandLaneA forward forced, aOperationLaneC forward forced, aOperationLaneD forward forced, aFireLaneC forward/backward random
        // cross from: aOperationLaneA, aOperationLaneB, aFireLaneD
        // cross directions: aOperationLaneA backward forced, aOperationLaneB backward forced, aFireLaneD backward/forward random
        // write to: aExpandLaneB
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aExpandLaneA[((aIndex + 8606U)) & S_BLOCK1], 23U) ^ RotL64(aOperationLaneC[((aIndex + 12767U)) & S_BLOCK1], 3U));
            aIngress ^= (RotL64(aOperationLaneD[((aIndex + 12761U)) & S_BLOCK1], 42U) ^ RotL64(aFireLaneC[((aIndex + 14993U)) & S_BLOCK1], 57U));
            aIngress = TwistMix64::DiffuseB(((aIngress ^ aDomainWordIngress) ^ aNonceWordF));
            //
            aCross = (RotL64(aOperationLaneA[((S_BLOCK1 - aIndex + 14487U)) & S_BLOCK1], 51U) ^ RotL64(aOperationLaneB[((S_BLOCK1 - aIndex + 15245U)) & S_BLOCK1], 30U));
            aCross ^= RotL64(aFireLaneD[((aIndex + 9194U)) & S_BLOCK1], 21U);
            aCross = TwistMix64::DiffuseB(((aCross ^ aDomainWordCross) ^ aNonceWordN));
            //
            aScatter = (RotL64(aCarry, 27U) ^ RotL64(aIngress, 57U)) + (RotL64(aCross, 5U) + RotL64(aPrevious, 44U));
            aScatter = TwistMix64::DiffuseC(((aScatter ^ aDomainWordScatter) ^ aNonceWordC));
            //
            aOrbiterC = (((aWandererG + RotL64(aIngress, 58U)) + RotL64(aCarry, 29U)) + 16016931609704150191U) + aOrbiterAssignSaltD[(((31U - aIndex) + 29U)) & S_SALT1];
            aOrbiterG = ((aWandererC + RotL64(aScatter, 47U)) + 14511433515861302636U) + aNonceWordD;
            aOrbiterB = (((aWandererJ + RotL64(aCross, 11U)) + RotL64(aCarry, 53U)) + 11691237442613269593U) + aNonceWordK;
            aOrbiterJ = ((aWandererH + RotL64(aPrevious, 29U)) + RotL64(aCarry, 11U)) + 16383220587320484649U;
            aOrbiterE = (((aWandererF + RotL64(aIngress, 34U)) + 14293015313458219868U) + aOrbiterAssignSaltF[((aIndex + 26U)) & S_SALT1]) + aNonceWordM;
            aOrbiterD = ((aWandererK + RotL64(aPrevious, 51U)) + 4407695248205526670U) + aNonceWordE;
            aOrbiterK = (aWandererB + RotL64(aCross, 21U)) + 1158323195324398372U;
            aOrbiterF = (aWandererA + RotL64(aScatter, 43U)) + 6577683409653864555U;
            aOrbiterA = (aWandererI + RotL64(aCross, 3U)) + 171080079472863843U;
            //
            aOrbiterC = (aOrbiterC + aOrbiterG) + 5766333425872228205U;
            aOrbiterB = (aOrbiterB ^ aOrbiterC) ^ 16173508656917582960U;
            aOrbiterB = RotL64((aOrbiterB * 12187968015372936695U), 27U);
            //
            aOrbiterJ = (aOrbiterJ + aOrbiterE) + 11781450063402219202U;
            aOrbiterD = (aOrbiterD ^ aOrbiterJ) ^ 13033139686637576694U;
            aOrbiterD = RotL64((aOrbiterD * 4331137994135472025U), 57U);
            //
            aOrbiterK = (aOrbiterK + aOrbiterD) + 4006310759400926020U;
            aOrbiterG = ((aOrbiterG ^ aOrbiterK) ^ 13156817947481574467U) ^ aNonceWordI;
            aOrbiterG = RotL64((aOrbiterG * 563189239835001483U), 23U);
            //
            aOrbiterE = (aOrbiterE + aOrbiterB) + 12791290558893516411U;
            aOrbiterF = (aOrbiterF ^ aOrbiterE) ^ 989729955679243234U;
            aOrbiterF = RotL64((aOrbiterF * 8757228712495095017U), 47U);
            //
            aOrbiterG = (aOrbiterG + aOrbiterA) + 838379839663022790U;
            aOrbiterJ = (aOrbiterJ ^ aOrbiterG) ^ 2830743864262313606U;
            aOrbiterJ = RotL64((aOrbiterJ * 10173947177104802797U), 39U);
            //
            aOrbiterF = (aOrbiterF + aOrbiterK) + 2146646527331684652U;
            aOrbiterC = ((aOrbiterC ^ aOrbiterF) ^ 4629168181742174906U) ^ aOrbiterUpdateSaltB[((aIndex + 7U)) & S_SALT1];
            aOrbiterC = RotL64((aOrbiterC * 9046124907945045131U), 51U);
            //
            aOrbiterA = (((aOrbiterA + aOrbiterC) + 1150129989168501777U) + aOrbiterUpdateSaltC[((aIndex + 19U)) & S_SALT1]) + aNonceWordA;
            aOrbiterE = ((aOrbiterE ^ aOrbiterA) ^ 619659995945229440U) ^ aOrbiterUpdateSaltE[(((31U - aIndex) + 13U)) & S_SALT1];
            aOrbiterE = RotL64((aOrbiterE * 13734821008174603409U), 43U);
            //
            aOrbiterB = (aOrbiterB + aOrbiterJ) + 8120315647582116952U;
            aOrbiterK = (aOrbiterK ^ aOrbiterB) ^ 13754584116324996165U;
            aOrbiterK = RotL64((aOrbiterK * 12295486140772079747U), 13U);
            //
            aOrbiterD = ((aOrbiterD + aOrbiterF) + 6084566798869999580U) + aOrbiterUpdateSaltA[((aIndex + 11U)) & S_SALT1];
            aOrbiterA = (aOrbiterA ^ aOrbiterD) ^ 5731665119233722504U;
            aOrbiterA = RotL64((aOrbiterA * 5921510209025133639U), 5U);
            //
            aIngress = RotL64(aOrbiterD, 43U) ^ aOrbiterG;
            aIngress = aIngress + (aOrbiterK ^ RotL64(aOrbiterE, 36U));
            aIngress = aIngress + (RotL64(aOrbiterA, 51U) ^ aOrbiterF);
            aIngress = aIngress + (aOrbiterJ ^ RotL64(aOrbiterB, 5U));
            aIngress = aIngress + RotL64(aOrbiterC, 27U);
            aIngress = TwistMix64::DiffuseA((aIngress + aScatter));
            //
            aWandererJ = aWandererJ + (((RotL64(aPrevious, 28U) + aOrbiterE) + RotL64(aOrbiterF, 37U)) + aWandererUpdateSaltC[((aIndex + 10U)) & S_SALT1]);
            aWandererA = aWandererA ^ ((RotL64(aCross, 35U) + RotL64(aOrbiterA, 18U)) + aOrbiterD);
            aWandererK = aWandererK + ((RotL64(aIngress, 39U) + aOrbiterG) + RotL64(aOrbiterF, 3U));
            aWandererI = aWandererI ^ ((RotL64(aScatter, 53U) + aOrbiterF) + RotL64(aOrbiterC, 57U));
            aWandererH = aWandererH + ((((RotL64(aPrevious, 19U) + aOrbiterC) + RotL64(aOrbiterD, 43U)) + RotL64(aCarry, 19U)) + aNonceWordB);
            aWandererG = aWandererG ^ ((RotL64(aCross, 43U) + RotL64(aOrbiterJ, 29U)) + aOrbiterG);
            aWandererB = aWandererB + ((((RotL64(aIngress, 48U) + aOrbiterD) + RotL64(aOrbiterB, 23U)) + RotL64(aCarry, 39U)) + aNonceWordJ);
            aWandererF = aWandererF ^ (((RotL64(aScatter, 3U) + aOrbiterB) + RotL64(aOrbiterK, 51U)) + aWandererUpdateSaltE[(((31U - aIndex) + 8U)) & S_SALT1]);
            aWandererC = aWandererC + ((RotL64(aPrevious, 57U) + RotL64(aOrbiterB, 10U)) + aOrbiterF);
            //
            aCarry = aCarry + (RotL64(aWandererG, 29U) ^ aWandererA);
            aCarry = aCarry + (aWandererK ^ RotL64(aWandererF, 19U));
            aCarry = aCarry + (aWandererJ ^ RotL64(aWandererI, 3U));
            aCarry = aCarry + (aWandererB ^ RotL64(aWandererC, 39U));
            aCarry = aCarry + RotL64(aWandererH, 26U);
            aCarry = aCarry + RotL64(aIngress, 13U);
            aCarry = TwistMix64::DiffuseB(aCarry);
            //
            aExpandLaneB[S_BLOCK1 - aIndex] = aIngress;
        }
    
        // kdf_b_loop_c loop 3
        // ingress from: aExpandLaneB, aOperationLaneA, aOperationLaneB, aWorkLaneA
        // ingress directions: aExpandLaneB forward forced, aOperationLaneA forward forced, aOperationLaneB forward forced, aWorkLaneA forward/backward random
        // cross from: aExpandLaneA, aOperationLaneC, aWorkLaneB
        // cross directions: aExpandLaneA backward forced, aOperationLaneC backward forced, aWorkLaneB backward/forward random
        // write to: aExpandLaneC
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aExpandLaneB[((aIndex + 22772U)) & S_BLOCK1], 39U) ^ RotL64(aOperationLaneA[((aIndex + 18572U)) & S_BLOCK1], 19U));
            aIngress ^= (RotL64(aOperationLaneB[((aIndex + 22701U)) & S_BLOCK1], 60U) ^ RotL64(aWorkLaneA[((aIndex + 16727U)) & S_BLOCK1], 5U));
            aIngress = TwistMix64::DiffuseA(((aIngress ^ aDomainWordIngress) ^ aNonceWordF));
            //
            aCross = (RotL64(aExpandLaneA[((S_BLOCK1 - aIndex + 18004U)) & S_BLOCK1], 21U) ^ RotL64(aOperationLaneC[((S_BLOCK1 - aIndex + 22526U)) & S_BLOCK1], 4U));
            aCross ^= RotL64(aWorkLaneB[((aIndex + 22605U)) & S_BLOCK1], 13U);
            aCross = TwistMix64::DiffuseA(((aCross ^ aDomainWordCross) ^ aNonceWordM));
            //
            aScatter = (RotL64(aCarry, 5U) ^ RotL64(aPrevious, 23U)) + (RotL64(aIngress, 37U) + RotL64(aCross, 56U));
            aScatter = TwistMix64::DiffuseA(((aScatter ^ aDomainWordScatter) ^ aNonceWordL));
            //
            aOrbiterJ = ((aWandererH + RotL64(aPrevious, 20U)) + 1457104756581596530U) + aNonceWordL;
            aOrbiterD = (aWandererE + RotL64(aScatter, 53U)) + 6127240317844622874U;
            aOrbiterH = (aWandererF + RotL64(aIngress, 47U)) + 16492290056044189421U;
            aOrbiterK = (aWandererD + RotL64(aCross, 11U)) + 10963676850938416468U;
            aOrbiterA = (((aWandererC + RotL64(aScatter, 5U)) + RotL64(aCarry, 19U)) + 4872917367399752405U) + aOrbiterAssignSaltA[(((31U - aIndex) + 15U)) & S_SALT1];
            aOrbiterC = ((aWandererK + RotL64(aCross, 57U)) + RotL64(aCarry, 47U)) + 15218882377875616148U;
            aOrbiterI = ((aWandererG + RotL64(aIngress, 40U)) + 5934166612122118251U) + aOrbiterAssignSaltB[((aIndex + 11U)) & S_SALT1];
            aOrbiterG = (aWandererB + RotL64(aPrevious, 29U)) + 14215280930872003003U;
            aOrbiterE = (((aWandererA + RotL64(aIngress, 35U)) + RotL64(aCarry, 39U)) + 11428034799044600979U) + aNonceWordH;
            //
            aOrbiterJ = (aOrbiterJ + aOrbiterD) + 5453003654321728726U;
            aOrbiterH = (aOrbiterH ^ aOrbiterJ) ^ 14273775120265649389U;
            aOrbiterH = RotL64((aOrbiterH * 5139018128323795309U), 35U);
            //
            aOrbiterK = (aOrbiterK + aOrbiterJ) + 328723770018440271U;
            aOrbiterA = ((aOrbiterA ^ aOrbiterK) ^ 13032190719588211088U) ^ aOrbiterUpdateSaltE[((aIndex + 5U)) & S_SALT1];
            aOrbiterA = RotL64((aOrbiterA * 13363368478932798315U), 43U);
            //
            aOrbiterC = (aOrbiterC + aOrbiterA) + 2386881543033598494U;
            aOrbiterI = (aOrbiterI ^ aOrbiterC) ^ 1649501123340887116U;
            aOrbiterI = RotL64((aOrbiterI * 11148976582360499033U), 57U);
            //
            aOrbiterG = (aOrbiterG + aOrbiterK) + 16462401546754210583U;
            aOrbiterC = (aOrbiterC ^ aOrbiterG) ^ 1510579201823042227U;
            aOrbiterC = RotL64((aOrbiterC * 16287912400104043275U), 23U);
            //
            aOrbiterI = ((aOrbiterI + aOrbiterG) + 6889066000014251983U) + aOrbiterUpdateSaltC[(((31U - aIndex) + 21U)) & S_SALT1];
            aOrbiterD = (aOrbiterD ^ aOrbiterI) ^ 11324594596597724357U;
            aOrbiterD = RotL64((aOrbiterD * 15344987814648586023U), 27U);
            //
            aOrbiterH = (aOrbiterH + aOrbiterE) + 12237796033168436537U;
            aOrbiterK = (((aOrbiterK ^ aOrbiterH) ^ 17306069670330000343U) ^ aOrbiterUpdateSaltF[(((31U - aIndex) + 23U)) & S_SALT1]) ^ aNonceWordE;
            aOrbiterK = RotL64((aOrbiterK * 3167451351403385259U), 39U);
            //
            aOrbiterA = (((aOrbiterA + aOrbiterH) + 14197284538008811658U) + aOrbiterUpdateSaltB[((aIndex + 16U)) & S_SALT1]) + aNonceWordG;
            aOrbiterG = (aOrbiterG ^ aOrbiterA) ^ 4754134852883071927U;
            aOrbiterG = RotL64((aOrbiterG * 3484427259538998699U), 3U);
            //
            aOrbiterE = ((aOrbiterE + aOrbiterI) + 17201907781639753736U) + aNonceWordO;
            aOrbiterJ = (aOrbiterJ ^ aOrbiterE) ^ 8318419319239859855U;
            aOrbiterJ = RotL64((aOrbiterJ * 10320390501983802091U), 13U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterC) + 16012488623961565780U;
            aOrbiterE = ((aOrbiterE ^ aOrbiterD) ^ 15583721012865354925U) ^ aNonceWordD;
            aOrbiterE = RotL64((aOrbiterE * 10656414363201743961U), 19U);
            //
            aIngress = aOrbiterD ^ RotL64(aOrbiterG, 42U);
            aIngress = aIngress + (aOrbiterA ^ RotL64(aOrbiterK, 51U));
            aIngress = aIngress + (RotL64(aOrbiterJ, 35U) ^ aOrbiterH);
            aIngress = aIngress + (RotL64(aOrbiterE, 27U) ^ aOrbiterI);
            aIngress = aIngress + RotL64(aOrbiterC, 38U);
            aIngress = TwistMix64::DiffuseC((aIngress + aScatter));
            //
            aWandererB = aWandererB ^ ((RotL64(aScatter, 19U) + aOrbiterD) + RotL64(aOrbiterI, 52U));
            aWandererG = aWandererG + ((RotL64(aCross, 60U) + aOrbiterD) + RotL64(aOrbiterC, 47U));
            aWandererF = aWandererF ^ (((RotL64(aIngress, 47U) + RotL64(aOrbiterJ, 39U)) + aOrbiterH) + aNonceWordB);
            aWandererC = aWandererC + (((((RotL64(aPrevious, 37U) + aOrbiterH) + RotL64(aOrbiterE, 29U)) + RotL64(aCarry, 5U)) + aNonceWordA) + aWandererUpdateSaltF[(((31U - aIndex) + 7U)) & S_SALT1]);
            aWandererK = aWandererK ^ (((RotL64(aIngress, 51U) + aOrbiterG) + RotL64(aOrbiterA, 23U)) + aNonceWordP);
            aWandererA = aWandererA + (((RotL64(aPrevious, 11U) + aOrbiterD) + RotL64(aOrbiterH, 34U)) + aWandererUpdateSaltB[((aIndex + 13U)) & S_SALT1]);
            aWandererH = aWandererH ^ ((RotL64(aScatter, 28U) + RotL64(aOrbiterA, 13U)) + aOrbiterJ);
            aWandererD = aWandererD + (((RotL64(aCross, 23U) + RotL64(aOrbiterG, 57U)) + aOrbiterC) + RotL64(aCarry, 51U));
            aWandererE = aWandererE ^ ((RotL64(aScatter, 41U) + aOrbiterK) + RotL64(aOrbiterD, 19U));
            //
            aCarry = aCarry + (aWandererC ^ RotL64(aWandererD, 39U));
            aCarry = aCarry + (aWandererF ^ RotL64(aWandererE, 13U));
            aCarry = aCarry + (aWandererK ^ RotL64(aWandererH, 26U));
            aCarry = aCarry + (aWandererG ^ RotL64(aWandererA, 47U));
            aCarry = aCarry + RotL64(aWandererB, 5U);
            aCarry = aCarry + RotL64(aIngress, 43U);
            aCarry = TwistMix64::DiffuseA(aCarry);
            //
            aExpandLaneC[aIndex] = aIngress;
        }
    
        // kdf_b_loop_c loop 4
        // ingress from: aExpandLaneC, aExpandLaneA, aOperationLaneD, aWorkLaneC
        // ingress directions: aExpandLaneC forward forced, aExpandLaneA forward forced, aOperationLaneD forward forced, aWorkLaneC forward/backward random
        // cross from: aExpandLaneB, aOperationLaneB, aWorkLaneD
        // cross directions: aExpandLaneB backward forced, aOperationLaneB backward forced, aWorkLaneD backward/forward random
        // write to: aExpandLaneD
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aExpandLaneC[((aIndex + 27287U)) & S_BLOCK1], 5U) ^ RotL64(aExpandLaneA[((aIndex + 25844U)) & S_BLOCK1], 13U));
            aIngress ^= (RotL64(aOperationLaneD[((aIndex + 25759U)) & S_BLOCK1], 39U) ^ RotL64(aWorkLaneC[((aIndex + 25673U)) & S_BLOCK1], 27U));
            aIngress = TwistMix64::DiffuseA(((aIngress ^ aDomainWordIngress) ^ aNonceWordL));
            //
            aCross = (RotL64(aExpandLaneB[((S_BLOCK1 - aIndex + 26236U)) & S_BLOCK1], 27U) ^ RotL64(aOperationLaneB[((S_BLOCK1 - aIndex + 30998U)) & S_BLOCK1], 41U));
            aCross ^= RotL64(aWorkLaneD[((aIndex + 24735U)) & S_BLOCK1], 53U);
            aCross = TwistMix64::DiffuseB(((aCross ^ aDomainWordCross) ^ aNonceWordN));
            //
            aScatter = (RotL64(aIngress, 35U) + RotL64(aCross, 50U)) + (RotL64(aPrevious, 19U) ^ RotL64(aCarry, 5U));
            aScatter = TwistMix64::DiffuseA(((aScatter ^ aDomainWordScatter) ^ aNonceWordO));
            //
            aOrbiterK = (((aWandererI + RotL64(aCross, 47U)) + RotL64(aCarry, 21U)) + 8767379393098711499U) + aNonceWordJ;
            aOrbiterJ = ((aWandererD + RotL64(aPrevious, 53U)) + 7168159491580816433U) + aNonceWordH;
            aOrbiterD = ((aWandererF + RotL64(aIngress, 21U)) + 9879279829061883406U) + aOrbiterAssignSaltE[(((31U - aIndex) + 15U)) & S_SALT1];
            aOrbiterB = ((aWandererC + RotL64(aScatter, 14U)) + 10537167136053399303U) + aNonceWordK;
            aOrbiterC = (aWandererE + RotL64(aIngress, 57U)) + 2839070018069188936U;
            aOrbiterF = (aWandererH + RotL64(aCross, 5U)) + 13844278063968429732U;
            aOrbiterH = (((aWandererK + RotL64(aScatter, 41U)) + RotL64(aCarry, 3U)) + 11278946626186474646U) + aOrbiterAssignSaltC[(((31U - aIndex) + 10U)) & S_SALT1];
            aOrbiterI = ((aWandererB + RotL64(aPrevious, 36U)) + RotL64(aCarry, 53U)) + 11798425216660557799U;
            aOrbiterG = (aWandererG + RotL64(aScatter, 27U)) + 7618446090703335192U;
            //
            aOrbiterK = (aOrbiterK + aOrbiterJ) + 695423597006983660U;
            aOrbiterD = (aOrbiterD ^ aOrbiterK) ^ 14344728202803488813U;
            aOrbiterD = RotL64((aOrbiterD * 5168825904902285909U), 47U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterB) + 11656100506575697086U;
            aOrbiterC = (aOrbiterC ^ aOrbiterD) ^ 10384358779985773937U;
            aOrbiterC = RotL64((aOrbiterC * 247494692039140973U), 27U);
            //
            aOrbiterF = ((aOrbiterF + aOrbiterK) + 17585001605131977341U) + aNonceWordI;
            aOrbiterH = (aOrbiterH ^ aOrbiterF) ^ 9964478171465522911U;
            aOrbiterH = RotL64((aOrbiterH * 13484044854790175315U), 19U);
            //
            aOrbiterH = (aOrbiterH + aOrbiterD) + 2710943171829692624U;
            aOrbiterI = (aOrbiterI ^ aOrbiterH) ^ 17809072853457153057U;
            aOrbiterI = RotL64((aOrbiterI * 16341884203303271365U), 23U);
            //
            aOrbiterJ = ((aOrbiterJ + aOrbiterH) + 12814092033910687774U) + aOrbiterUpdateSaltE[((aIndex + 29U)) & S_SALT1];
            aOrbiterB = (aOrbiterB ^ aOrbiterJ) ^ 1743186323268668740U;
            aOrbiterB = RotL64((aOrbiterB * 11150822630624332557U), 35U);
            //
            aOrbiterC = (aOrbiterC + aOrbiterG) + 10750472346626754704U;
            aOrbiterK = (aOrbiterK ^ aOrbiterC) ^ 15925901217078035356U;
            aOrbiterK = RotL64((aOrbiterK * 9276504171291801637U), 53U);
            //
            aOrbiterB = (aOrbiterB + aOrbiterI) + 2569102106359362359U;
            aOrbiterG = (aOrbiterG ^ aOrbiterB) ^ 8868261301410769739U;
            aOrbiterG = RotL64((aOrbiterG * 3662495603133918101U), 11U);
            //
            aOrbiterI = (((aOrbiterI + aOrbiterC) + 2143691008373582476U) + aOrbiterUpdateSaltF[((aIndex + 19U)) & S_SALT1]) + aNonceWordP;
            aOrbiterF = ((aOrbiterF ^ aOrbiterI) ^ 10606616796243205921U) ^ aOrbiterUpdateSaltD[(((31U - aIndex) + 17U)) & S_SALT1];
            aOrbiterF = RotL64((aOrbiterF * 15794414817813485643U), 57U);
            //
            aOrbiterG = (aOrbiterG + aOrbiterF) + 16258070651850746855U;
            aOrbiterJ = ((aOrbiterJ ^ aOrbiterG) ^ 11720192793689633315U) ^ aOrbiterUpdateSaltC[(((31U - aIndex) + 3U)) & S_SALT1];
            aOrbiterJ = RotL64((aOrbiterJ * 14475623219460678021U), 39U);
            //
            aIngress = RotL64(aOrbiterI, 27U) ^ aOrbiterK;
            aIngress = aIngress + (aOrbiterD ^ RotL64(aOrbiterG, 6U));
            aIngress = aIngress + (aOrbiterB ^ RotL64(aOrbiterH, 57U));
            aIngress = aIngress + (RotL64(aOrbiterF, 43U) ^ aOrbiterC);
            aIngress = aIngress + RotL64(aOrbiterJ, 47U);
            aIngress = TwistMix64::DiffuseB((aIngress + aScatter));
            //
            aWandererD = aWandererD + ((((RotL64(aPrevious, 13U) + RotL64(aOrbiterD, 48U)) + aOrbiterG) + RotL64(aCarry, 3U)) + aNonceWordC);
            aWandererE = aWandererE ^ (((RotL64(aIngress, 19U) + aOrbiterF) + RotL64(aOrbiterI, 37U)) + aNonceWordM);
            aWandererF = aWandererF + (((RotL64(aScatter, 34U) + aOrbiterJ) + RotL64(aOrbiterK, 53U)) + RotL64(aCarry, 23U));
            aWandererB = aWandererB ^ (((RotL64(aCross, 27U) + aOrbiterH) + RotL64(aOrbiterJ, 57U)) + aWandererUpdateSaltD[(((31U - aIndex) + 18U)) & S_SALT1]);
            aWandererH = aWandererH + ((RotL64(aScatter, 57U) + RotL64(aOrbiterB, 24U)) + aOrbiterJ);
            aWandererG = aWandererG ^ ((RotL64(aCross, 5U) + RotL64(aOrbiterC, 3U)) + aOrbiterD);
            aWandererI = aWandererI + ((RotL64(aPrevious, 23U) + aOrbiterH) + RotL64(aOrbiterK, 19U));
            aWandererK = aWandererK ^ (((RotL64(aIngress, 39U) + RotL64(aOrbiterF, 13U)) + aOrbiterK) + aWandererUpdateSaltA[(((31U - aIndex) + 7U)) & S_SALT1]);
            aWandererC = aWandererC + ((RotL64(aScatter, 44U) + RotL64(aOrbiterC, 41U)) + aOrbiterK);
            //
            aCarry = aCarry + (RotL64(aWandererC, 5U) ^ aWandererF);
            aCarry = aCarry + (aWandererE ^ RotL64(aWandererD, 41U));
            aCarry = aCarry + (RotL64(aWandererH, 46U) ^ aWandererK);
            aCarry = aCarry + (aWandererB ^ RotL64(aWandererI, 19U));
            aCarry = aCarry + RotL64(aWandererG, 51U);
            aCarry = aCarry + RotL64(aIngress, 37U);
            aCarry = TwistMix64::DiffuseA(aCarry);
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

void TwistExpander_Greezy_Arx::KDF_B_D(TwistWorkSpace *pWorkSpace,
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
    std::uint64_t aNonceWordA = TwistMix64::DiffuseA(pNonce * 0xBD373090E269E1D7ULL + 0xCC163DDF37633563ULL);
    std::uint64_t aNonceWordB = TwistMix64::DiffuseC(pNonce * 0x9BF716CD2C68A101ULL + 0xA45E102AC8DC467EULL);
    std::uint64_t aNonceWordC = TwistMix64::DiffuseB(pNonce * 0x8FC2E9DF8B25E9CDULL + 0xAB26601E8643B529ULL);
    std::uint64_t aNonceWordD = TwistMix64::DiffuseB(pNonce * 0xBA4E1216B40F4871ULL + 0x8182C59853B89A04ULL);
    std::uint64_t aNonceWordE = TwistMix64::DiffuseC(pNonce * 0xCA594CD53AD996B5ULL + 0x8F88B48D10413807ULL);
    std::uint64_t aNonceWordF = TwistMix64::DiffuseB(pNonce * 0xAD84E2F1ADCAE7E7ULL + 0xD31C1E9667AAE3B7ULL);
    std::uint64_t aNonceWordG = TwistMix64::DiffuseC(pNonce * 0xCED4A7AC73D9516FULL + 0x9A98900A4184B048ULL);
    std::uint64_t aNonceWordH = TwistMix64::DiffuseB(pNonce * 0x857BB178EFDD1683ULL + 0x8986111D06AF9BC0ULL);
    std::uint64_t aNonceWordI = TwistMix64::DiffuseA(pNonce * 0xA3AD638E3391BDD9ULL + 0x8700DF74C3040D6BULL);
    std::uint64_t aNonceWordJ = TwistMix64::DiffuseA(pNonce * 0xC0582653CDB4C0EBULL + 0xA3CDADB07562076AULL);
    std::uint64_t aNonceWordK = TwistMix64::DiffuseB(pNonce * 0xA5DCB33EB3F6CFB9ULL + 0xDF9A1D7932271561ULL);
    std::uint64_t aNonceWordL = TwistMix64::DiffuseC(pNonce * 0xA43C60941A893265ULL + 0xED6298467C7A81E1ULL);
    std::uint64_t aNonceWordM = TwistMix64::DiffuseB(pNonce * 0x91DBBE86E472EFE5ULL + 0xB9E9542BCB75C55BULL);
    std::uint64_t aNonceWordN = TwistMix64::DiffuseC(pNonce * 0xFDA7FA09F2D0ACABULL + 0x93C60AA2AD6E8812ULL);
    std::uint64_t aNonceWordO = TwistMix64::DiffuseC(pNonce * 0xEA3057A95C4F9ED3ULL + 0x88908DA9BA1778F8ULL);
    std::uint64_t aNonceWordP = TwistMix64::DiffuseC(pNonce * 0xD2869C1803E07CF5ULL + 0x97F8B19CE1F309F2ULL);
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
        // read from: aWorkLaneA, aWorkLaneB, aFireLaneA, aWorkLaneC, aWorkLaneD, aFireLaneB, aExpandLaneA, aFireLaneC, aFireLaneD, aExpandLaneB, aOperationLaneA, aOperationLaneB, aExpandLaneC, aOperationLaneC, aOperationLaneD
        // write to: aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD
    
        // kdf_b_loop_d loop 1
        // ingress from: aWorkLaneA, aWorkLaneB, aFireLaneA
        // ingress directions: aWorkLaneA forward forced, aWorkLaneB forward forced, aFireLaneA forward/backward random
        // cross from: aWorkLaneC, aWorkLaneD, aFireLaneB
        // cross directions: aWorkLaneC backward forced, aWorkLaneD backward forced, aFireLaneB backward/forward random
        // write to: aExpandLaneA
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aWorkLaneA[((aIndex + 7074U)) & S_BLOCK1], 13U) ^ RotL64(aWorkLaneB[((aIndex + 7641U)) & S_BLOCK1], 44U));
            aIngress ^= RotL64(aFireLaneA[((S_BLOCK1 - aIndex + 1059U)) & S_BLOCK1], 53U);
            aIngress = TwistMix64::DiffuseC(((aIngress ^ aDomainWordIngress) ^ aNonceWordG));
            //
            aCross = (RotL64(aWorkLaneC[((S_BLOCK1 - aIndex + 6774U)) & S_BLOCK1], 23U) ^ RotL64(aWorkLaneD[((S_BLOCK1 - aIndex + 3714U)) & S_BLOCK1], 6U));
            aCross ^= RotL64(aFireLaneB[((S_BLOCK1 - aIndex + 472U)) & S_BLOCK1], 51U);
            aCross = TwistMix64::DiffuseB(((aCross ^ aDomainWordCross) ^ aNonceWordJ));
            //
            aScatter = (RotL64(aCross, 54U) ^ RotL64(aPrevious, 21U)) + (RotL64(aCarry, 35U) ^ RotL64(aIngress, 3U));
            aScatter = TwistMix64::DiffuseB(((aScatter ^ aDomainWordScatter) ^ aNonceWordE));
            //
            aOrbiterI = (aWandererJ + RotL64(aIngress, 44U)) + 1087148170018530502U;
            aOrbiterK = ((aWandererE + RotL64(aPrevious, 21U)) + RotL64(aCarry, 13U)) + 15530846874509311414U;
            aOrbiterE = ((aWandererF + RotL64(aScatter, 13U)) + RotL64(aCarry, 29U)) + 16987358651515511212U;
            aOrbiterC = ((aWandererI + RotL64(aCross, 35U)) + 12504143181007924259U) + aNonceWordI;
            aOrbiterG = (((aWandererA + RotL64(aScatter, 57U)) + 393322117322732418U) + aOrbiterAssignSaltF[((aIndex + 26U)) & S_SALT1]) + aNonceWordK;
            aOrbiterA = (aWandererG + RotL64(aCross, 5U)) + 14325937299241887166U;
            aOrbiterJ = ((((aWandererK + RotL64(aIngress, 51U)) + RotL64(aCarry, 53U)) + 9395262907017475742U) + aOrbiterAssignSaltD[((aIndex + 23U)) & S_SALT1]) + aNonceWordF;
            //
            aOrbiterI = (aOrbiterI + aOrbiterK) + 13658510441418344769U;
            aOrbiterE = ((aOrbiterE ^ aOrbiterI) ^ 6410754322737005336U) ^ aOrbiterUpdateSaltB[((aIndex + 29U)) & S_SALT1];
            aOrbiterE = RotL64((aOrbiterE * 6932217611373076391U), 27U);
            //
            aOrbiterE = (aOrbiterE + aOrbiterC) + 9257290738538818434U;
            aOrbiterG = ((aOrbiterG ^ aOrbiterE) ^ 7489828960857692286U) ^ aOrbiterUpdateSaltA[((aIndex + 7U)) & S_SALT1];
            aOrbiterG = RotL64((aOrbiterG * 16519674788777989043U), 19U);
            //
            aOrbiterA = (aOrbiterA + aOrbiterG) + 4118778591214588387U;
            aOrbiterI = (((aOrbiterI ^ aOrbiterA) ^ 16619215231168796563U) ^ aOrbiterUpdateSaltE[(((31U - aIndex) + 9U)) & S_SALT1]) ^ aNonceWordC;
            aOrbiterI = RotL64((aOrbiterI * 14876884956536265157U), 5U);
            //
            aOrbiterJ = (aOrbiterJ + aOrbiterE) + 11326283811003573430U;
            aOrbiterA = ((aOrbiterA ^ aOrbiterJ) ^ 1865401866017614604U) ^ aNonceWordL;
            aOrbiterA = RotL64((aOrbiterA * 8378326058282460073U), 13U);
            //
            aOrbiterK = (aOrbiterK + aOrbiterA) + 670150121105733604U;
            aOrbiterC = (aOrbiterC ^ aOrbiterK) ^ 1499331510641068749U;
            aOrbiterC = RotL64((aOrbiterC * 16623742535540383107U), 57U);
            //
            aOrbiterC = ((aOrbiterC + aOrbiterI) + 1116410848560838532U) + aOrbiterUpdateSaltC[(((31U - aIndex) + 11U)) & S_SALT1];
            aOrbiterJ = (aOrbiterJ ^ aOrbiterC) ^ 2696841341036281779U;
            aOrbiterJ = RotL64((aOrbiterJ * 9598953298074904869U), 41U);
            //
            aOrbiterG = (aOrbiterG + aOrbiterJ) + 5487352391229549881U;
            aOrbiterK = (aOrbiterK ^ aOrbiterG) ^ 12008243050943342979U;
            aOrbiterK = RotL64((aOrbiterK * 9087261224804582459U), 51U);
            //
            aIngress = RotL64(aOrbiterC, 58U) ^ aOrbiterJ;
            aIngress = aIngress + (RotL64(aOrbiterA, 39U) ^ aOrbiterI);
            aIngress = aIngress + (aOrbiterG ^ RotL64(aOrbiterK, 51U));
            aIngress = aIngress + RotL64(aOrbiterE, 19U);
            aIngress = TwistMix64::DiffuseB((aIngress + aScatter));
            //
            aWandererJ = aWandererJ + ((((RotL64(aPrevious, 27U) + aOrbiterE) + RotL64(aOrbiterI, 11U)) + RotL64(aCarry, 51U)) + aNonceWordM);
            aWandererK = aWandererK ^ (((RotL64(aScatter, 43U) + aOrbiterC) + RotL64(aOrbiterE, 37U)) + aWandererUpdateSaltC[(((31U - aIndex) + 5U)) & S_SALT1]);
            aWandererA = aWandererA + ((RotL64(aCross, 3U) + RotL64(aOrbiterC, 57U)) + aOrbiterA);
            aWandererE = aWandererE ^ (((RotL64(aIngress, 13U) + RotL64(aOrbiterE, 3U)) + aOrbiterJ) + aNonceWordH);
            aWandererG = aWandererG + (((RotL64(aCross, 58U) + RotL64(aOrbiterJ, 44U)) + aOrbiterG) + RotL64(aCarry, 11U));
            aWandererF = aWandererF ^ (((RotL64(aScatter, 19U) + aOrbiterK) + RotL64(aOrbiterA, 29U)) + aNonceWordA);
            aWandererI = aWandererI + ((((RotL64(aPrevious, 51U) + RotL64(aOrbiterC, 21U)) + aOrbiterJ) + aNonceWordO) + aWandererUpdateSaltF[((aIndex + 24U)) & S_SALT1]);
            //
            aCarry = aCarry + (aWandererA ^ RotL64(aWandererG, 60U));
            aCarry = aCarry + (aWandererK ^ RotL64(aWandererJ, 47U));
            aCarry = aCarry + (aWandererI ^ RotL64(aWandererF, 23U));
            aCarry = aCarry + RotL64(aWandererE, 51U);
            aCarry = aCarry + RotL64(aIngress, 11U);
            aCarry = TwistMix64::DiffuseA(aCarry);
            //
            aExpandLaneA[aIndex] = aIngress;
        }
    
        // kdf_b_loop_d loop 2
        // ingress from: aExpandLaneA, aWorkLaneC, aWorkLaneD, aFireLaneC
        // ingress directions: aExpandLaneA forward forced, aWorkLaneC forward forced, aWorkLaneD forward forced, aFireLaneC forward/backward random
        // cross from: aWorkLaneA, aWorkLaneB, aFireLaneD
        // cross directions: aWorkLaneA backward forced, aWorkLaneB backward forced, aFireLaneD backward/forward random
        // write to: aExpandLaneB
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aExpandLaneA[((aIndex + 8415U)) & S_BLOCK1], 27U) ^ RotL64(aWorkLaneC[((aIndex + 16040U)) & S_BLOCK1], 60U));
            aIngress ^= (RotL64(aWorkLaneD[((aIndex + 15004U)) & S_BLOCK1], 11U) ^ RotL64(aFireLaneC[((aIndex + 12494U)) & S_BLOCK1], 47U));
            aIngress = TwistMix64::DiffuseB(((aIngress ^ aDomainWordIngress) ^ aNonceWordN));
            //
            aCross = (RotL64(aWorkLaneA[((S_BLOCK1 - aIndex + 10897U)) & S_BLOCK1], 41U) ^ RotL64(aWorkLaneB[((S_BLOCK1 - aIndex + 12967U)) & S_BLOCK1], 5U));
            aCross ^= RotL64(aFireLaneD[((aIndex + 16202U)) & S_BLOCK1], 60U);
            aCross = TwistMix64::DiffuseA(((aCross ^ aDomainWordCross) ^ aNonceWordP));
            //
            aScatter = (RotL64(aCross, 53U) ^ RotL64(aPrevious, 5U)) + (RotL64(aIngress, 26U) ^ RotL64(aCarry, 41U));
            aScatter = TwistMix64::DiffuseB(((aScatter ^ aDomainWordScatter) ^ aNonceWordB));
            //
            aOrbiterG = (aWandererI + RotL64(aCross, 28U)) + 3612110001869385068U;
            aOrbiterA = ((aWandererD + RotL64(aPrevious, 57U)) + RotL64(aCarry, 27U)) + 16340824141280225936U;
            aOrbiterJ = ((aWandererA + RotL64(aScatter, 47U)) + RotL64(aCarry, 53U)) + 15222338965130765231U;
            aOrbiterE = (((aWandererK + RotL64(aIngress, 5U)) + RotL64(aCarry, 41U)) + 6649270508107155041U) + aNonceWordJ;
            aOrbiterC = ((aWandererF + RotL64(aCross, 39U)) + 768217258655426384U) + aNonceWordC;
            aOrbiterB = (((aWandererH + RotL64(aPrevious, 21U)) + 4481855259658861851U) + aOrbiterAssignSaltC[((aIndex + 19U)) & S_SALT1]) + aNonceWordM;
            aOrbiterH = (((aWandererC + RotL64(aScatter, 11U)) + 18318041934562434016U) + aOrbiterAssignSaltB[((aIndex + 8U)) & S_SALT1]) + aNonceWordO;
            //
            aOrbiterG = (((aOrbiterG + aOrbiterA) + 4212457153804401807U) + aOrbiterUpdateSaltD[(((31U - aIndex) + 22U)) & S_SALT1]) + aNonceWordB;
            aOrbiterJ = (((aOrbiterJ ^ aOrbiterG) ^ 16143621095636987628U) ^ aOrbiterUpdateSaltA[(((31U - aIndex) + 28U)) & S_SALT1]) ^ aNonceWordD;
            aOrbiterJ = RotL64((aOrbiterJ * 6576072860505961427U), 35U);
            //
            aOrbiterE = (aOrbiterE + aOrbiterC) + 2095664232866642086U;
            aOrbiterA = (aOrbiterA ^ aOrbiterE) ^ 4339527736737366572U;
            aOrbiterA = RotL64((aOrbiterA * 17503569508822244125U), 3U);
            //
            aOrbiterB = ((aOrbiterB + aOrbiterJ) + 13679353177869884790U) + aOrbiterUpdateSaltF[(((31U - aIndex) + 23U)) & S_SALT1];
            aOrbiterE = (aOrbiterE ^ aOrbiterB) ^ 11582168502846418236U;
            aOrbiterE = RotL64((aOrbiterE * 135539430034462861U), 51U);
            //
            aOrbiterC = (aOrbiterC + aOrbiterG) + 10451330452898542191U;
            aOrbiterB = (aOrbiterB ^ aOrbiterC) ^ 12951448817640617841U;
            aOrbiterB = RotL64((aOrbiterB * 4141870904192742091U), 43U);
            //
            aOrbiterH = ((aOrbiterH + aOrbiterE) + 15389161934419370747U) + aNonceWordI;
            aOrbiterG = (aOrbiterG ^ aOrbiterH) ^ 4754886272708253014U;
            aOrbiterG = RotL64((aOrbiterG * 16638243718191281597U), 29U);
            //
            aOrbiterJ = (aOrbiterJ + aOrbiterH) + 11746389873929280688U;
            aOrbiterC = (aOrbiterC ^ aOrbiterJ) ^ 12042680172517298768U;
            aOrbiterC = RotL64((aOrbiterC * 3814780289755857543U), 13U);
            //
            aOrbiterA = (((aOrbiterA + aOrbiterB) + 2648103752465009244U) + aOrbiterUpdateSaltE[(((31U - aIndex) + 6U)) & S_SALT1]) + aNonceWordG;
            aOrbiterH = (aOrbiterH ^ aOrbiterA) ^ 451594673632597973U;
            aOrbiterH = RotL64((aOrbiterH * 8496763663271072425U), 19U);
            //
            aIngress = aOrbiterH ^ RotL64(aOrbiterE, 13U);
            aIngress = aIngress + (RotL64(aOrbiterC, 3U) ^ aOrbiterB);
            aIngress = aIngress + (aOrbiterA ^ RotL64(aOrbiterJ, 21U));
            aIngress = aIngress + RotL64(aOrbiterG, 27U);
            aIngress = TwistMix64::DiffuseA((aIngress + aScatter));
            //
            aWandererA = aWandererA + ((RotL64(aIngress, 43U) + RotL64(aOrbiterE, 29U)) + aOrbiterH);
            aWandererC = aWandererC ^ ((RotL64(aCross, 19U) + aOrbiterA) + RotL64(aOrbiterB, 37U));
            aWandererF = aWandererF + ((RotL64(aPrevious, 56U) + aOrbiterG) + RotL64(aOrbiterJ, 23U));
            aWandererH = aWandererH ^ (((RotL64(aScatter, 3U) + RotL64(aOrbiterB, 10U)) + aOrbiterC) + aNonceWordA);
            aWandererD = aWandererD + ((((RotL64(aIngress, 35U) + RotL64(aOrbiterH, 3U)) + aOrbiterJ) + RotL64(aCarry, 51U)) + aWandererUpdateSaltD[(((31U - aIndex) + 5U)) & S_SALT1]);
            aWandererI = aWandererI ^ (((RotL64(aPrevious, 13U) + aOrbiterC) + RotL64(aOrbiterE, 47U)) + aWandererUpdateSaltE[((aIndex + 9U)) & S_SALT1]);
            aWandererK = aWandererK + ((((RotL64(aScatter, 29U) + RotL64(aOrbiterE, 53U)) + aOrbiterB) + RotL64(aCarry, 29U)) + aNonceWordE);
            //
            aCarry = aCarry + (aWandererC ^ RotL64(aWandererA, 30U));
            aCarry = aCarry + (RotL64(aWandererK, 51U) ^ aWandererH);
            aCarry = aCarry + (RotL64(aWandererF, 13U) ^ aWandererI);
            aCarry = aCarry + RotL64(aWandererD, 47U);
            aCarry = aCarry + RotL64(aIngress, 5U);
            aCarry = TwistMix64::DiffuseA(aCarry);
            //
            aExpandLaneB[S_BLOCK1 - aIndex] = aIngress;
        }
    
        // kdf_b_loop_d loop 3
        // ingress from: aExpandLaneB, aWorkLaneA, aWorkLaneB, aOperationLaneA
        // ingress directions: aExpandLaneB forward forced, aWorkLaneA forward forced, aWorkLaneB forward forced, aOperationLaneA forward/backward random
        // cross from: aExpandLaneA, aWorkLaneC, aOperationLaneB
        // cross directions: aExpandLaneA backward forced, aWorkLaneC backward forced, aOperationLaneB backward/forward random
        // write to: aExpandLaneC
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aExpandLaneB[((aIndex + 22918U)) & S_BLOCK1], 30U) ^ RotL64(aWorkLaneA[((aIndex + 24023U)) & S_BLOCK1], 19U));
            aIngress ^= (RotL64(aWorkLaneB[((aIndex + 23613U)) & S_BLOCK1], 57U) ^ RotL64(aOperationLaneA[((aIndex + 22748U)) & S_BLOCK1], 47U));
            aIngress = TwistMix64::DiffuseA(((aIngress ^ aDomainWordIngress) ^ aNonceWordF));
            //
            aCross = (RotL64(aExpandLaneA[((S_BLOCK1 - aIndex + 21464U)) & S_BLOCK1], 27U) ^ RotL64(aWorkLaneC[((S_BLOCK1 - aIndex + 16826U)) & S_BLOCK1], 5U));
            aCross ^= RotL64(aOperationLaneB[((S_BLOCK1 - aIndex + 21322U)) & S_BLOCK1], 38U);
            aCross = TwistMix64::DiffuseB(((aCross ^ aDomainWordCross) ^ aNonceWordC));
            //
            aScatter = (RotL64(aCross, 23U) ^ RotL64(aIngress, 51U)) ^ (RotL64(aPrevious, 38U) + RotL64(aCarry, 11U));
            aScatter = TwistMix64::DiffuseB(((aScatter ^ aDomainWordScatter) ^ aNonceWordH));
            //
            aOrbiterB = ((aWandererD + RotL64(aPrevious, 41U)) + 252059974543142812U) + aNonceWordA;
            aOrbiterC = (((aWandererI + RotL64(aScatter, 11U)) + 11690823093681457368U) + aOrbiterAssignSaltA[(((31U - aIndex) + 9U)) & S_SALT1]) + aNonceWordM;
            aOrbiterF = (aWandererC + RotL64(aIngress, 47U)) + 13282189752890971123U;
            aOrbiterJ = (((aWandererG + RotL64(aCross, 53U)) + RotL64(aCarry, 21U)) + 9507416294305708435U) + aNonceWordN;
            aOrbiterA = ((aWandererK + RotL64(aIngress, 3U)) + 14053038174390776539U) + aOrbiterAssignSaltE[((aIndex + 28U)) & S_SALT1];
            aOrbiterI = (((aWandererJ + RotL64(aPrevious, 20U)) + RotL64(aCarry, 35U)) + 14605253312318725009U) + aNonceWordL;
            aOrbiterG = ((aWandererF + RotL64(aScatter, 35U)) + RotL64(aCarry, 51U)) + 18138286582677863671U;
            //
            aOrbiterB = (aOrbiterB + aOrbiterC) + 8530091235978489988U;
            aOrbiterF = (aOrbiterF ^ aOrbiterB) ^ 14381731677571170073U;
            aOrbiterF = RotL64((aOrbiterF * 11675896999665768253U), 13U);
            //
            aOrbiterJ = (aOrbiterJ + aOrbiterA) + 13316413456378978456U;
            aOrbiterI = ((aOrbiterI ^ aOrbiterJ) ^ 3910529530149320706U) ^ aNonceWordI;
            aOrbiterI = RotL64((aOrbiterI * 16000139333493588429U), 21U);
            //
            aOrbiterA = (aOrbiterA + aOrbiterI) + 6302070286831566901U;
            aOrbiterG = (aOrbiterG ^ aOrbiterA) ^ 12324134652758551396U;
            aOrbiterG = RotL64((aOrbiterG * 17136438281540250165U), 3U);
            //
            aOrbiterI = ((aOrbiterI + aOrbiterG) + 4773478557638475048U) + aOrbiterUpdateSaltF[(((31U - aIndex) + 25U)) & S_SALT1];
            aOrbiterB = ((aOrbiterB ^ aOrbiterI) ^ 4031153435446078944U) ^ aOrbiterUpdateSaltB[(((31U - aIndex) + 27U)) & S_SALT1];
            aOrbiterB = RotL64((aOrbiterB * 3876928995240982769U), 47U);
            //
            aOrbiterF = (aOrbiterF + aOrbiterJ) + 3114794895962903899U;
            aOrbiterA = ((aOrbiterA ^ aOrbiterF) ^ 3552936509969106796U) ^ aOrbiterUpdateSaltE[((aIndex + 29U)) & S_SALT1];
            aOrbiterA = RotL64((aOrbiterA * 16823186892738820299U), 37U);
            //
            aOrbiterG = (aOrbiterG + aOrbiterB) + 5828754613946145627U;
            aOrbiterC = ((aOrbiterC ^ aOrbiterG) ^ 17985241114076114558U) ^ aOrbiterUpdateSaltD[((aIndex + 13U)) & S_SALT1];
            aOrbiterC = RotL64((aOrbiterC * 1986669631395606833U), 53U);
            //
            aOrbiterC = ((aOrbiterC + aOrbiterF) + 11319331046368072261U) + aNonceWordB;
            aOrbiterJ = (aOrbiterJ ^ aOrbiterC) ^ 6104267020171882160U;
            aOrbiterJ = RotL64((aOrbiterJ * 12525117969211576177U), 27U);
            //
            aIngress = RotL64(aOrbiterA, 20U) ^ aOrbiterJ;
            aIngress = aIngress + (RotL64(aOrbiterB, 57U) ^ aOrbiterI);
            aIngress = aIngress + (aOrbiterF ^ RotL64(aOrbiterC, 5U));
            aIngress = aIngress + RotL64(aOrbiterG, 43U);
            aIngress = TwistMix64::DiffuseC((aIngress + aScatter));
            //
            aWandererC = aWandererC + (((RotL64(aIngress, 13U) + RotL64(aOrbiterJ, 27U)) + aOrbiterI) + aNonceWordP);
            aWandererD = aWandererD ^ ((RotL64(aCross, 5U) + RotL64(aOrbiterF, 51U)) + aOrbiterJ);
            aWandererG = aWandererG + ((((RotL64(aPrevious, 21U) + aOrbiterF) + RotL64(aOrbiterA, 13U)) + RotL64(aCarry, 39U)) + aNonceWordO);
            aWandererJ = aWandererJ ^ ((RotL64(aScatter, 27U) + aOrbiterG) + RotL64(aOrbiterA, 44U));
            aWandererF = aWandererF + ((((RotL64(aIngress, 37U) + aOrbiterB) + RotL64(aOrbiterI, 19U)) + RotL64(aCarry, 57U)) + aNonceWordD);
            aWandererI = aWandererI ^ (((RotL64(aCross, 60U) + aOrbiterF) + RotL64(aOrbiterC, 3U)) + aWandererUpdateSaltA[(((31U - aIndex) + 20U)) & S_SALT1]);
            aWandererK = aWandererK + (((RotL64(aPrevious, 51U) + RotL64(aOrbiterG, 57U)) + aOrbiterC) + aWandererUpdateSaltB[((aIndex + 15U)) & S_SALT1]);
            //
            aCarry = aCarry + (RotL64(aWandererI, 18U) ^ aWandererJ);
            aCarry = aCarry + (aWandererD ^ RotL64(aWandererF, 13U));
            aCarry = aCarry + (RotL64(aWandererG, 23U) ^ aWandererC);
            aCarry = aCarry + RotL64(aWandererK, 57U);
            aCarry = aCarry + RotL64(aIngress, 34U);
            aCarry = TwistMix64::DiffuseB(aCarry);
            //
            aExpandLaneC[aIndex] = aIngress;
        }
    
        // kdf_b_loop_d loop 4
        // ingress from: aExpandLaneC, aExpandLaneA, aWorkLaneD, aOperationLaneC
        // ingress directions: aExpandLaneC forward forced, aExpandLaneA forward forced, aWorkLaneD forward forced, aOperationLaneC forward/backward random
        // cross from: aExpandLaneB, aWorkLaneB, aOperationLaneD
        // cross directions: aExpandLaneB backward forced, aWorkLaneB backward forced, aOperationLaneD backward/forward random
        // write to: aExpandLaneD
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aExpandLaneC[((aIndex + 30343U)) & S_BLOCK1], 58U) ^ RotL64(aExpandLaneA[((aIndex + 32029U)) & S_BLOCK1], 21U));
            aIngress ^= (RotL64(aWorkLaneD[((aIndex + 30456U)) & S_BLOCK1], 41U) ^ RotL64(aOperationLaneC[((aIndex + 25496U)) & S_BLOCK1], 13U));
            aIngress = TwistMix64::DiffuseA(((aIngress ^ aDomainWordIngress) ^ aNonceWordD));
            //
            aCross = (RotL64(aExpandLaneB[((S_BLOCK1 - aIndex + 26649U)) & S_BLOCK1], 19U) ^ RotL64(aWorkLaneB[((S_BLOCK1 - aIndex + 31080U)) & S_BLOCK1], 3U));
            aCross ^= RotL64(aOperationLaneD[((aIndex + 27242U)) & S_BLOCK1], 57U);
            aCross = TwistMix64::DiffuseC(((aCross ^ aDomainWordCross) ^ aNonceWordO));
            //
            aScatter = (RotL64(aCarry, 23U) + RotL64(aPrevious, 11U)) + (RotL64(aCross, 35U) ^ RotL64(aIngress, 52U));
            aScatter = TwistMix64::DiffuseB(((aScatter ^ aDomainWordScatter) ^ aNonceWordH));
            //
            aOrbiterG = ((aWandererC + RotL64(aScatter, 29U)) + 7075016829833562104U) + aNonceWordM;
            aOrbiterD = (((aWandererH + RotL64(aPrevious, 5U)) + RotL64(aCarry, 53U)) + 8783765886115517036U) + aNonceWordH;
            aOrbiterA = ((aWandererD + RotL64(aCross, 11U)) + RotL64(aCarry, 37U)) + 2996723892384565829U;
            aOrbiterE = ((aWandererA + RotL64(aIngress, 37U)) + RotL64(aCarry, 23U)) + 9494134707342189476U;
            aOrbiterH = ((aWandererB + RotL64(aCross, 52U)) + 5052642981395679904U) + aOrbiterAssignSaltD[(((31U - aIndex) + 11U)) & S_SALT1];
            aOrbiterB = (((aWandererI + RotL64(aIngress, 43U)) + 8766787055127962238U) + aOrbiterAssignSaltF[(((31U - aIndex) + 16U)) & S_SALT1]) + aNonceWordE;
            aOrbiterF = (aWandererK + RotL64(aScatter, 19U)) + 4467211954388738079U;
            //
            aOrbiterG = (aOrbiterG + aOrbiterD) + 8030255604633658608U;
            aOrbiterA = (aOrbiterA ^ aOrbiterG) ^ 16962408063455702251U;
            aOrbiterA = RotL64((aOrbiterA * 11171737929747471631U), 11U);
            //
            aOrbiterD = (((aOrbiterD + aOrbiterA) + 3768222186567699076U) + aOrbiterUpdateSaltE[(((31U - aIndex) + 18U)) & S_SALT1]) + aNonceWordN;
            aOrbiterE = (aOrbiterE ^ aOrbiterD) ^ 14930990410207899871U;
            aOrbiterE = RotL64((aOrbiterE * 10930005786146268241U), 19U);
            //
            aOrbiterH = (aOrbiterH + aOrbiterB) + 14179761938395502502U;
            aOrbiterF = ((aOrbiterF ^ aOrbiterH) ^ 1879084742719898108U) ^ aOrbiterUpdateSaltB[((aIndex + 6U)) & S_SALT1];
            aOrbiterF = RotL64((aOrbiterF * 16783034788172670121U), 29U);
            //
            aOrbiterA = ((aOrbiterA + aOrbiterE) + 5535012408925981515U) + aNonceWordC;
            aOrbiterH = (aOrbiterH ^ aOrbiterA) ^ 12792553516710295939U;
            aOrbiterH = RotL64((aOrbiterH * 8577530993755159329U), 47U);
            //
            aOrbiterB = ((aOrbiterB + aOrbiterF) + 8979253163346099252U) + aOrbiterUpdateSaltC[((aIndex + 9U)) & S_SALT1];
            aOrbiterG = ((aOrbiterG ^ aOrbiterB) ^ 5559189896063990740U) ^ aOrbiterUpdateSaltA[(((31U - aIndex) + 3U)) & S_SALT1];
            aOrbiterG = RotL64((aOrbiterG * 8832485423727331621U), 53U);
            //
            aOrbiterF = (aOrbiterF + aOrbiterG) + 13937564337299044079U;
            aOrbiterD = (aOrbiterD ^ aOrbiterF) ^ 2393376759689394948U;
            aOrbiterD = RotL64((aOrbiterD * 2352815657830413941U), 35U);
            //
            aOrbiterE = ((aOrbiterE + aOrbiterH) + 12647519563697356479U) + aNonceWordB;
            aOrbiterB = ((aOrbiterB ^ aOrbiterE) ^ 10946871249960389549U) ^ aNonceWordG;
            aOrbiterB = RotL64((aOrbiterB * 6272580371881237173U), 41U);
            //
            aIngress = RotL64(aOrbiterD, 3U) ^ aOrbiterB;
            aIngress = aIngress + (aOrbiterF ^ RotL64(aOrbiterE, 35U));
            aIngress = aIngress + (aOrbiterA ^ RotL64(aOrbiterG, 29U));
            aIngress = aIngress + RotL64(aOrbiterH, 21U);
            aIngress = TwistMix64::DiffuseC((aIngress + aScatter));
            //
            aWandererI = aWandererI ^ (((RotL64(aCross, 37U) + aOrbiterA) + RotL64(aOrbiterG, 48U)) + aWandererUpdateSaltC[((aIndex + 14U)) & S_SALT1]);
            aWandererC = aWandererC + ((((RotL64(aPrevious, 29U) + RotL64(aOrbiterE, 39U)) + aOrbiterB) + RotL64(aCarry, 13U)) + aNonceWordP);
            aWandererD = aWandererD ^ (((RotL64(aIngress, 14U) + aOrbiterB) + RotL64(aOrbiterA, 5U)) + aNonceWordI);
            aWandererB = aWandererB + ((((RotL64(aScatter, 51U) + RotL64(aOrbiterF, 21U)) + aOrbiterH) + RotL64(aCarry, 43U)) + aNonceWordF);
            aWandererK = aWandererK ^ (((RotL64(aCross, 43U) + aOrbiterH) + RotL64(aOrbiterB, 27U)) + aWandererUpdateSaltF[(((31U - aIndex) + 17U)) & S_SALT1]);
            aWandererA = aWandererA + ((RotL64(aPrevious, 5U) + RotL64(aOrbiterF, 11U)) + aOrbiterD);
            aWandererH = aWandererH ^ (((RotL64(aScatter, 57U) + aOrbiterF) + RotL64(aOrbiterG, 57U)) + aNonceWordA);
            //
            aCarry = aCarry + (RotL64(aWandererB, 29U) ^ aWandererA);
            aCarry = aCarry + (aWandererD ^ RotL64(aWandererC, 57U));
            aCarry = aCarry + (aWandererI ^ RotL64(aWandererK, 24U));
            aCarry = aCarry + RotL64(aWandererH, 51U);
            aCarry = aCarry + RotL64(aIngress, 41U);
            aCarry = TwistMix64::DiffuseC(aCarry);
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

void TwistExpander_Greezy_Arx::Seed_A(TwistWorkSpace *pWorkSpace,
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
    [[maybe_unused]] std::uint64_t *aPhaseEOrbiterAssignSaltB = pWorkSpace->mDomainBundle.mPhaseESalts.mOrbiterAssign.mSaltB;
    [[maybe_unused]] std::uint64_t *aPhaseEOrbiterAssignSaltC = pWorkSpace->mDomainBundle.mPhaseESalts.mOrbiterAssign.mSaltC;
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
    [[maybe_unused]] std::uint64_t *aPhaseFWandererUpdateSaltD = pWorkSpace->mDomainBundle.mPhaseFSalts.mWandererUpdate.mSaltD;
    [[maybe_unused]] std::uint64_t *aPhaseFWandererUpdateSaltE = pWorkSpace->mDomainBundle.mPhaseFSalts.mWandererUpdate.mSaltE;
    [[maybe_unused]] std::uint64_t *aPhaseFWandererUpdateSaltF = pWorkSpace->mDomainBundle.mPhaseFSalts.mWandererUpdate.mSaltF;
    [[maybe_unused]] std::uint64_t *aPhaseGOrbiterAssignSaltA = pWorkSpace->mDomainBundle.mPhaseGSalts.mOrbiterAssign.mSaltA;
    [[maybe_unused]] std::uint64_t *aPhaseGOrbiterAssignSaltB = pWorkSpace->mDomainBundle.mPhaseGSalts.mOrbiterAssign.mSaltB;
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
    [[maybe_unused]] std::uint64_t *aPhaseGWandererUpdateSaltD = pWorkSpace->mDomainBundle.mPhaseGSalts.mWandererUpdate.mSaltD;
    [[maybe_unused]] std::uint64_t *aPhaseGWandererUpdateSaltE = pWorkSpace->mDomainBundle.mPhaseGSalts.mWandererUpdate.mSaltE;
    [[maybe_unused]] std::uint64_t *aPhaseGWandererUpdateSaltF = pWorkSpace->mDomainBundle.mPhaseGSalts.mWandererUpdate.mSaltF;
    [[maybe_unused]] std::uint64_t *aPhaseHOrbiterAssignSaltA = pWorkSpace->mDomainBundle.mPhaseHSalts.mOrbiterAssign.mSaltA;
    [[maybe_unused]] std::uint64_t *aPhaseHOrbiterAssignSaltB = pWorkSpace->mDomainBundle.mPhaseHSalts.mOrbiterAssign.mSaltB;
    [[maybe_unused]] std::uint64_t *aPhaseHOrbiterAssignSaltC = pWorkSpace->mDomainBundle.mPhaseHSalts.mOrbiterAssign.mSaltC;
    [[maybe_unused]] std::uint64_t *aPhaseHOrbiterAssignSaltE = pWorkSpace->mDomainBundle.mPhaseHSalts.mOrbiterAssign.mSaltE;
    [[maybe_unused]] std::uint64_t *aPhaseHOrbiterAssignSaltF = pWorkSpace->mDomainBundle.mPhaseHSalts.mOrbiterAssign.mSaltF;
    [[maybe_unused]] std::uint64_t *aPhaseHOrbiterUpdateSaltA = pWorkSpace->mDomainBundle.mPhaseHSalts.mOrbiterUpdate.mSaltA;
    [[maybe_unused]] std::uint64_t *aPhaseHOrbiterUpdateSaltB = pWorkSpace->mDomainBundle.mPhaseHSalts.mOrbiterUpdate.mSaltB;
    [[maybe_unused]] std::uint64_t *aPhaseHOrbiterUpdateSaltD = pWorkSpace->mDomainBundle.mPhaseHSalts.mOrbiterUpdate.mSaltD;
    [[maybe_unused]] std::uint64_t *aPhaseHOrbiterUpdateSaltE = pWorkSpace->mDomainBundle.mPhaseHSalts.mOrbiterUpdate.mSaltE;
    [[maybe_unused]] std::uint64_t *aPhaseHOrbiterUpdateSaltF = pWorkSpace->mDomainBundle.mPhaseHSalts.mOrbiterUpdate.mSaltF;
    [[maybe_unused]] std::uint64_t *aPhaseHWandererUpdateSaltA = pWorkSpace->mDomainBundle.mPhaseHSalts.mWandererUpdate.mSaltA;
    [[maybe_unused]] std::uint64_t *aPhaseHWandererUpdateSaltB = pWorkSpace->mDomainBundle.mPhaseHSalts.mWandererUpdate.mSaltB;
    [[maybe_unused]] std::uint64_t *aPhaseHWandererUpdateSaltC = pWorkSpace->mDomainBundle.mPhaseHSalts.mWandererUpdate.mSaltC;
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
    std::uint64_t aNonceWordA = TwistMix64::DiffuseA(pNonce * 0xBCEC09B629239519ULL + 0xBA6DEA29C199436EULL);
    std::uint64_t aNonceWordB = TwistMix64::DiffuseA(pNonce * 0x9D3C018D68BDEB5DULL + 0xC0D3BC82DE99D6AAULL);
    std::uint64_t aNonceWordC = TwistMix64::DiffuseC(pNonce * 0x83871B57C06F745FULL + 0x898D2D118A998127ULL);
    std::uint64_t aNonceWordD = TwistMix64::DiffuseC(pNonce * 0xECAE2D4AD75F1BB3ULL + 0xC47FF382ED728615ULL);
    std::uint64_t aNonceWordE = TwistMix64::DiffuseC(pNonce * 0x8621E5DE4ACD8BA5ULL + 0xAB44ADBC0131D0F0ULL);
    std::uint64_t aNonceWordF = TwistMix64::DiffuseC(pNonce * 0xAE1630FEA9663F03ULL + 0xC6C07F0F4862DDEAULL);
    std::uint64_t aNonceWordG = TwistMix64::DiffuseC(pNonce * 0x9A7EC51BCF41023BULL + 0xAE108169C2E6BCBFULL);
    std::uint64_t aNonceWordH = TwistMix64::DiffuseB(pNonce * 0xA37888179C4E37B3ULL + 0xF68A33B882E9FF26ULL);
    std::uint64_t aNonceWordI = TwistMix64::DiffuseB(pNonce * 0xB3656EFFFEB4E47DULL + 0xBE28BF052A747525ULL);
    std::uint64_t aNonceWordJ = TwistMix64::DiffuseB(pNonce * 0xD9F21BEDD5823CE5ULL + 0x9F6E604B6DC6D3C8ULL);
    std::uint64_t aNonceWordK = TwistMix64::DiffuseB(pNonce * 0xD94DED2867CD2A71ULL + 0x9ED99E9C4308F3BDULL);
    std::uint64_t aNonceWordL = TwistMix64::DiffuseC(pNonce * 0xDE7F22F1A8DA3E33ULL + 0xE2E5FE8BAE6A8D73ULL);
    std::uint64_t aNonceWordM = TwistMix64::DiffuseA(pNonce * 0xB0B55C939B3B76EFULL + 0x8BC14237D46A6744ULL);
    std::uint64_t aNonceWordN = TwistMix64::DiffuseA(pNonce * 0x84E4DB3ABC861C55ULL + 0xA082C9F0A3A57D9AULL);
    std::uint64_t aNonceWordO = TwistMix64::DiffuseA(pNonce * 0xE03469A0CB1C297BULL + 0xE52280AB88C8361EULL);
    std::uint64_t aNonceWordP = TwistMix64::DiffuseA(pNonce * 0x847E4E10CFA33E57ULL + 0xB79C5DB22DF25F3CULL);
    // GSeedRunSeed_A seed_loop_a (start)
    {
        // GSeedRunSeed_A seed_loop_a lane group
        // read from: aKeyRowReadA, aKeyRowReadB, mSource, aFireLaneA, aFireLaneB, aFireLaneC, aFireLaneD, aWorkLaneA, aWorkLaneB, aWorkLaneC, aWorkLaneD, aExpandLaneA, aExpandLaneB, aExpandLaneC
        // write to: aFireLaneA, aFireLaneB, aFireLaneC, aFireLaneD, aWorkLaneA, aWorkLaneB, aWorkLaneC, aWorkLaneD, aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD
    
        // seed_loop_a loop 1
        // ingress from: aKeyRowReadA, aKeyRowReadB
        // ingress directions: aKeyRowReadA forward forced, aKeyRowReadB forward/backward random
        // cross from: aKeyRowReadA, mSource
        // cross directions: aKeyRowReadA backward forced, mSource backward/forward random
        // write to: aFireLaneA
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = RotL64(aKeyRowReadA[((aIndex + 1350U)) & W_KEY1], 29U) ^ RotL64(aKeyRowReadB[(((2047U - aIndex) + 1937U)) & W_KEY1], 54U);
            aIngress = TwistMix64::DiffuseC(((aIngress ^ aPhaseEDomainWordIngress) ^ aNonceWordD));
            //
            aCross = RotL64(aKeyRowReadA[(((2047U - aIndex) + 2192U)) & W_KEY1], 27U) ^ RotL64(mSource[((S_BLOCK1 - aIndex + 1729U)) & S_BLOCK1], 18U);
            aCross = TwistMix64::DiffuseC(((aCross ^ aPhaseEDomainWordCross) ^ aNonceWordP));
            //
            aScatter = (RotL64(aIngress, 39U) + RotL64(aCross, 51U)) + (RotL64(aCarry, 27U) ^ RotL64(aPrevious, 10U));
            aScatter = TwistMix64::DiffuseB(((aScatter ^ aPhaseEDomainWordScatter) ^ aNonceWordE));
            //
            aOrbiterJ = (((aWandererK + RotL64(aPrevious, 4U)) + RotL64(aCarry, 27U)) + 964165145848253292U) + aPhaseEOrbiterAssignSaltF[((aIndex + 25U)) & S_SALT1];
            aOrbiterB = ((aWandererF + RotL64(aScatter, 19U)) + 10645976767204934746U) + aNonceWordJ;
            aOrbiterH = (aWandererE + RotL64(aIngress, 43U)) + 8241612229349212650U;
            aOrbiterD = (((aWandererC + RotL64(aCross, 57U)) + RotL64(aCarry, 39U)) + 4159196033256913347U) + aNonceWordG;
            aOrbiterK = ((aWandererG + RotL64(aIngress, 51U)) + RotL64(aCarry, 11U)) + 7194795864620233507U;
            aOrbiterG = (aWandererI + RotL64(aCross, 11U)) + 7638928444536778384U;
            aOrbiterI = ((aWandererD + RotL64(aScatter, 27U)) + 11819105916503968109U) + aPhaseEOrbiterAssignSaltE[(((31U - aIndex) + 16U)) & S_SALT1];
            //
            aOrbiterJ = (((aOrbiterJ + aOrbiterB) + 18052213302858186237U) + aPhaseEOrbiterUpdateSaltB[(((31U - aIndex) + 8U)) & S_SALT1]) + aNonceWordE;
            aOrbiterH = (aOrbiterH ^ aOrbiterJ) ^ 8663575313970041570U;
            aOrbiterH = RotL64((aOrbiterH * 14131073322476609161U), 3U);
            //
            aOrbiterD = ((aOrbiterD + aOrbiterK) + 16644136720439299786U) + aPhaseEOrbiterUpdateSaltA[(((31U - aIndex) + 5U)) & S_SALT1];
            aOrbiterJ = (aOrbiterJ ^ aOrbiterD) ^ 16930316530442679864U;
            aOrbiterJ = RotL64((aOrbiterJ * 2650922074098320859U), 41U);
            //
            aOrbiterK = (aOrbiterK + aOrbiterG) + 16251107616988250593U;
            aOrbiterB = (aOrbiterB ^ aOrbiterK) ^ 7171986193609401665U;
            aOrbiterB = RotL64((aOrbiterB * 3543709971414550087U), 27U);
            //
            aOrbiterG = (aOrbiterG + aOrbiterH) + 17885046834432626644U;
            aOrbiterD = ((aOrbiterD ^ aOrbiterG) ^ 7757069274715713557U) ^ aPhaseEOrbiterUpdateSaltC[((aIndex + 7U)) & S_SALT1];
            aOrbiterD = RotL64((aOrbiterD * 15766885299397923879U), 57U);
            //
            aOrbiterI = (aOrbiterI + aOrbiterJ) + 2212805322061155615U;
            aOrbiterG = ((aOrbiterG ^ aOrbiterI) ^ 6368539134638838822U) ^ aNonceWordI;
            aOrbiterG = RotL64((aOrbiterG * 13383744883433594259U), 51U);
            //
            aOrbiterH = (aOrbiterH + aOrbiterI) + 5264326094252925613U;
            aOrbiterK = (aOrbiterK ^ aOrbiterH) ^ 6126345334815012938U;
            aOrbiterK = RotL64((aOrbiterK * 17180934809764905307U), 35U);
            //
            aOrbiterB = ((aOrbiterB + aOrbiterD) + 13826731214018407061U) + aPhaseEOrbiterUpdateSaltD[((aIndex + 11U)) & S_SALT1];
            aOrbiterI = (aOrbiterI ^ aOrbiterB) ^ 6621261811613643620U;
            aOrbiterI = RotL64((aOrbiterI * 2823596473596114171U), 11U);
            //
            aIngress = RotL64(aOrbiterJ, 11U) ^ aOrbiterI;
            aIngress = aIngress + (aOrbiterH ^ RotL64(aOrbiterK, 36U));
            aIngress = aIngress + (RotL64(aOrbiterG, 29U) ^ aOrbiterD);
            aIngress = aIngress + RotL64(aOrbiterB, 19U);
            aIngress = TwistMix64::DiffuseA((aIngress + aScatter));
            //
            aWandererK = aWandererK ^ ((((RotL64(aScatter, 51U) + RotL64(aOrbiterJ, 29U)) + aOrbiterD) + aNonceWordA) + aPhaseEWandererUpdateSaltA[(((31U - aIndex) + 19U)) & S_SALT1]);
            aWandererD = aWandererD + ((((RotL64(aPrevious, 27U) + RotL64(aOrbiterG, 11U)) + aOrbiterH) + RotL64(aCarry, 23U)) + aNonceWordO);
            aWandererI = aWandererI ^ (((RotL64(aCross, 57U) + RotL64(aOrbiterK, 47U)) + aOrbiterB) + aNonceWordB);
            aWandererF = aWandererF + (((RotL64(aIngress, 43U) + RotL64(aOrbiterH, 35U)) + aOrbiterI) + RotL64(aCarry, 11U));
            aWandererE = aWandererE ^ (((RotL64(aPrevious, 3U) + RotL64(aOrbiterK, 23U)) + aOrbiterH) + aNonceWordH);
            aWandererC = aWandererC + (((RotL64(aScatter, 37U) + aOrbiterK) + RotL64(aOrbiterD, 60U)) + aPhaseEWandererUpdateSaltE[(((31U - aIndex) + 17U)) & S_SALT1]);
            aWandererG = aWandererG ^ ((RotL64(aCross, 20U) + RotL64(aOrbiterI, 53U)) + aOrbiterJ);
            //
            aCarry = aCarry + (RotL64(aWandererK, 28U) ^ aWandererE);
            aCarry = aCarry + (aWandererI ^ RotL64(aWandererC, 13U));
            aCarry = aCarry + (RotL64(aWandererG, 35U) ^ aWandererD);
            aCarry = aCarry + RotL64(aWandererF, 47U);
            aCarry = aCarry + RotL64(aIngress, 41U);
            aCarry = TwistMix64::DiffuseA(aCarry);
            //
            aFireLaneA[aIndex] = aIngress;
        }
    
        // seed_loop_a loop 2
        // ingress from: aFireLaneA, aKeyRowReadA
        // ingress directions: aFireLaneA forward forced, aKeyRowReadA forward/backward random
        // cross from: aKeyRowReadB, mSource
        // cross directions: aKeyRowReadB backward forced, mSource backward/forward random
        // write to: aFireLaneB
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = RotL64(aFireLaneA[((aIndex + 3653U)) & S_BLOCK1], 37U) ^ RotL64(aKeyRowReadA[((aIndex + 3096U)) & W_KEY1], 56U);
            aIngress = TwistMix64::DiffuseC(((aIngress ^ aPhaseEDomainWordIngress) ^ aNonceWordO));
            //
            aCross = RotL64(aKeyRowReadB[(((2047U - aIndex) + 5100U)) & W_KEY1], 54U) ^ RotL64(mSource[((S_BLOCK1 - aIndex + 3528U)) & S_BLOCK1], 19U);
            aCross = TwistMix64::DiffuseA(((aCross ^ aPhaseEDomainWordCross) ^ aNonceWordI));
            //
            aScatter = (RotL64(aCross, 26U) ^ RotL64(aIngress, 5U)) + (RotL64(aCarry, 41U) + RotL64(aPrevious, 53U));
            aScatter = TwistMix64::DiffuseC(((aScatter ^ aPhaseEDomainWordScatter) ^ aNonceWordC));
            //
            aOrbiterA = ((aWandererA + RotL64(aCross, 35U)) + 380024772508948442U) + aNonceWordH;
            aOrbiterB = (aWandererB + RotL64(aScatter, 51U)) + 7649029098162567210U;
            aOrbiterH = (((aWandererD + RotL64(aIngress, 29U)) + RotL64(aCarry, 57U)) + 5329304598870421851U) + aPhaseEOrbiterAssignSaltA[(((31U - aIndex) + 4U)) & S_SALT1];
            aOrbiterG = ((aWandererH + RotL64(aPrevious, 58U)) + RotL64(aCarry, 41U)) + 12306118665045151326U;
            aOrbiterD = (((aWandererK + RotL64(aCross, 43U)) + RotL64(aCarry, 21U)) + 960751560457324256U) + aNonceWordC;
            aOrbiterF = (((aWandererF + RotL64(aPrevious, 11U)) + 3244070254386191876U) + aPhaseEOrbiterAssignSaltC[((aIndex + 27U)) & S_SALT1]) + aNonceWordB;
            aOrbiterJ = (aWandererI + RotL64(aIngress, 23U)) + 15733408571609521746U;
            //
            aOrbiterA = (aOrbiterA + aOrbiterB) + 17623448932647018544U;
            aOrbiterH = ((aOrbiterH ^ aOrbiterA) ^ 8787759896149035829U) ^ aNonceWordG;
            aOrbiterH = RotL64((aOrbiterH * 7092515868845497573U), 35U);
            //
            aOrbiterG = ((aOrbiterG + aOrbiterD) + 14741681792348288162U) + aPhaseEOrbiterUpdateSaltB[(((31U - aIndex) + 17U)) & S_SALT1];
            aOrbiterB = (((aOrbiterB ^ aOrbiterG) ^ 8801731213568307302U) ^ aPhaseEOrbiterUpdateSaltE[(((31U - aIndex) + 29U)) & S_SALT1]) ^ aNonceWordL;
            aOrbiterB = RotL64((aOrbiterB * 12127126999570616489U), 27U);
            //
            aOrbiterF = (aOrbiterF + aOrbiterG) + 9872248187499779222U;
            aOrbiterA = ((aOrbiterA ^ aOrbiterF) ^ 15407371518644528235U) ^ aNonceWordD;
            aOrbiterA = RotL64((aOrbiterA * 1245102406469471673U), 5U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterA) + 4242060317152943062U;
            aOrbiterJ = (aOrbiterJ ^ aOrbiterD) ^ 9942784962409917541U;
            aOrbiterJ = RotL64((aOrbiterJ * 888649755587764533U), 19U);
            //
            aOrbiterB = ((aOrbiterB + aOrbiterJ) + 7296348796484458631U) + aPhaseEOrbiterUpdateSaltD[((aIndex + 5U)) & S_SALT1];
            aOrbiterF = (aOrbiterF ^ aOrbiterB) ^ 15061417216070157797U;
            aOrbiterF = RotL64((aOrbiterF * 10349554676953256231U), 47U);
            //
            aOrbiterH = ((aOrbiterH + aOrbiterF) + 3233185810644297433U) + aPhaseEOrbiterUpdateSaltF[((aIndex + 15U)) & S_SALT1];
            aOrbiterD = ((aOrbiterD ^ aOrbiterH) ^ 9241229457641024287U) ^ aNonceWordM;
            aOrbiterD = RotL64((aOrbiterD * 2728237515724597517U), 11U);
            //
            aOrbiterJ = (aOrbiterJ + aOrbiterH) + 8464051359381554575U;
            aOrbiterG = (aOrbiterG ^ aOrbiterJ) ^ 3307872165699029375U;
            aOrbiterG = RotL64((aOrbiterG * 4859663401033023433U), 53U);
            //
            aIngress = RotL64(aOrbiterB, 51U) ^ aOrbiterG;
            aIngress = aIngress + (aOrbiterD ^ RotL64(aOrbiterH, 10U));
            aIngress = aIngress + (aOrbiterF ^ RotL64(aOrbiterJ, 57U));
            aIngress = aIngress + RotL64(aOrbiterA, 3U);
            aIngress = TwistMix64::DiffuseB((aIngress + aScatter));
            //
            aWandererB = aWandererB ^ ((((RotL64(aPrevious, 29U) + aOrbiterH) + RotL64(aOrbiterJ, 34U)) + aNonceWordP) + aPhaseEWandererUpdateSaltC[((aIndex + 23U)) & S_SALT1]);
            aWandererI = aWandererI + ((((RotL64(aScatter, 44U) + aOrbiterD) + RotL64(aOrbiterF, 5U)) + RotL64(aCarry, 13U)) + aNonceWordJ);
            aWandererA = aWandererA ^ (((RotL64(aCross, 13U) + RotL64(aOrbiterF, 23U)) + aOrbiterA) + aNonceWordA);
            aWandererD = aWandererD + ((RotL64(aIngress, 23U) + aOrbiterB) + RotL64(aOrbiterA, 53U));
            aWandererK = aWandererK ^ ((((RotL64(aScatter, 5U) + aOrbiterG) + RotL64(aOrbiterD, 13U)) + aNonceWordK) + aPhaseEWandererUpdateSaltE[(((31U - aIndex) + 8U)) & S_SALT1]);
            aWandererF = aWandererF + (((RotL64(aIngress, 51U) + aOrbiterJ) + RotL64(aOrbiterG, 41U)) + RotL64(aCarry, 43U));
            aWandererH = aWandererH ^ ((RotL64(aCross, 57U) + aOrbiterD) + RotL64(aOrbiterA, 47U));
            //
            aCarry = aCarry + (RotL64(aWandererA, 42U) ^ aWandererD);
            aCarry = aCarry + (RotL64(aWandererK, 11U) ^ aWandererB);
            aCarry = aCarry + (aWandererI ^ RotL64(aWandererF, 23U));
            aCarry = aCarry + RotL64(aWandererH, 5U);
            aCarry = aCarry + RotL64(aIngress, 27U);
            aCarry = TwistMix64::DiffuseB(aCarry);
            //
            aFireLaneB[S_BLOCK1 - aIndex] = aIngress;
        }
    
        // seed_loop_a loop 3
        // ingress from: aFireLaneB, aKeyRowReadB
        // ingress directions: aFireLaneB forward forced, aKeyRowReadB forward/backward random
        // cross from: aKeyRowReadA, mSource, aFireLaneA
        // cross directions: aKeyRowReadA backward forced, mSource backward forced, aFireLaneA backward/forward random
        // write to: aFireLaneC
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = RotL64(aFireLaneB[((aIndex + 6653U)) & S_BLOCK1], 29U) ^ RotL64(aKeyRowReadB[((aIndex + 5935U)) & W_KEY1], 56U);
            aIngress = TwistMix64::DiffuseA(((aIngress ^ aPhaseEDomainWordIngress) ^ aNonceWordB));
            //
            aCross = (RotL64(aKeyRowReadA[(((2047U - aIndex) + 5502U)) & W_KEY1], 24U) ^ RotL64(mSource[((S_BLOCK1 - aIndex + 5813U)) & S_BLOCK1], 3U));
            aCross ^= RotL64(aFireLaneA[((S_BLOCK1 - aIndex + 7204U)) & S_BLOCK1], 35U);
            aCross = TwistMix64::DiffuseC(((aCross ^ aPhaseEDomainWordCross) ^ aNonceWordK));
            //
            aScatter = (RotL64(aIngress, 53U) + RotL64(aCarry, 24U)) ^ (RotL64(aPrevious, 39U) ^ RotL64(aCross, 5U));
            aScatter = TwistMix64::DiffuseA(((aScatter ^ aPhaseEDomainWordScatter) ^ aNonceWordF));
            //
            aOrbiterA = (((aWandererF + RotL64(aPrevious, 5U)) + RotL64(aCarry, 51U)) + 5088525177670191619U) + aNonceWordO;
            aOrbiterE = ((aWandererC + RotL64(aScatter, 60U)) + RotL64(aCarry, 21U)) + 9966456257813932112U;
            aOrbiterD = ((aWandererE + RotL64(aCross, 11U)) + 7707646574027146307U) + aPhaseEOrbiterAssignSaltB[(((31U - aIndex) + 5U)) & S_SALT1];
            aOrbiterH = ((aWandererK + RotL64(aIngress, 19U)) + RotL64(aCarry, 35U)) + 75480203757681173U;
            aOrbiterK = (aWandererD + RotL64(aScatter, 47U)) + 384659134071835163U;
            aOrbiterC = ((aWandererI + RotL64(aIngress, 53U)) + 3158769775373307778U) + aNonceWordN;
            aOrbiterI = (((aWandererH + RotL64(aPrevious, 27U)) + 17360830943513941272U) + aPhaseEOrbiterAssignSaltE[((aIndex + 3U)) & S_SALT1]) + aNonceWordE;
            //
            aOrbiterA = ((aOrbiterA + aOrbiterE) + 5317278822721604586U) + aPhaseEOrbiterUpdateSaltB[((aIndex + 29U)) & S_SALT1];
            aOrbiterD = ((aOrbiterD ^ aOrbiterA) ^ 1371427105215954781U) ^ aPhaseEOrbiterUpdateSaltD[((aIndex + 8U)) & S_SALT1];
            aOrbiterD = RotL64((aOrbiterD * 10956603063464438611U), 57U);
            //
            aOrbiterH = ((aOrbiterH + aOrbiterK) + 3162710551223553423U) + aNonceWordC;
            aOrbiterC = (((aOrbiterC ^ aOrbiterH) ^ 5332921933853550756U) ^ aPhaseEOrbiterUpdateSaltA[((aIndex + 10U)) & S_SALT1]) ^ aNonceWordF;
            aOrbiterC = RotL64((aOrbiterC * 11709546145149357887U), 47U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterH) + 10572462410297815854U;
            aOrbiterK = (aOrbiterK ^ aOrbiterD) ^ 10234389605554817892U;
            aOrbiterK = RotL64((aOrbiterK * 2130374833440291193U), 37U);
            //
            aOrbiterK = (aOrbiterK + aOrbiterC) + 13421365517991380605U;
            aOrbiterI = ((aOrbiterI ^ aOrbiterK) ^ 10186643614984034083U) ^ aPhaseEOrbiterUpdateSaltE[((aIndex + 11U)) & S_SALT1];
            aOrbiterI = RotL64((aOrbiterI * 8554471709467808453U), 5U);
            //
            aOrbiterC = ((aOrbiterC + aOrbiterI) + 4742438973260817120U) + aNonceWordI;
            aOrbiterA = (aOrbiterA ^ aOrbiterC) ^ 6081590345899008846U;
            aOrbiterA = RotL64((aOrbiterA * 7069396301823124931U), 13U);
            //
            aOrbiterI = (aOrbiterI + aOrbiterA) + 15360092808493795340U;
            aOrbiterE = (aOrbiterE ^ aOrbiterI) ^ 12186413069553132646U;
            aOrbiterE = RotL64((aOrbiterE * 3815981440611914267U), 23U);
            //
            aOrbiterE = (aOrbiterE + aOrbiterD) + 16756221656224451552U;
            aOrbiterH = ((aOrbiterH ^ aOrbiterE) ^ 12232880965861373143U) ^ aNonceWordM;
            aOrbiterH = RotL64((aOrbiterH * 14196910735715726471U), 29U);
            //
            aIngress = aOrbiterI ^ RotL64(aOrbiterC, 19U);
            aIngress = aIngress + (aOrbiterD ^ RotL64(aOrbiterA, 37U));
            aIngress = aIngress + (aOrbiterE ^ RotL64(aOrbiterK, 6U));
            aIngress = aIngress + RotL64(aOrbiterH, 27U);
            aIngress = TwistMix64::DiffuseB((aIngress + aScatter));
            //
            aWandererF = aWandererF ^ ((RotL64(aCross, 44U) + aOrbiterH) + RotL64(aOrbiterK, 29U));
            aWandererK = aWandererK + (((RotL64(aPrevious, 19U) + RotL64(aOrbiterD, 37U)) + aOrbiterE) + RotL64(aCarry, 51U));
            aWandererC = aWandererC ^ (((RotL64(aIngress, 51U) + aOrbiterC) + RotL64(aOrbiterA, 47U)) + aNonceWordG);
            aWandererD = aWandererD + ((((RotL64(aScatter, 57U) + aOrbiterI) + RotL64(aOrbiterK, 3U)) + RotL64(aCarry, 27U)) + aPhaseEWandererUpdateSaltB[(((31U - aIndex) + 9U)) & S_SALT1]);
            aWandererH = aWandererH ^ (((RotL64(aCross, 13U) + RotL64(aOrbiterD, 58U)) + aOrbiterH) + aNonceWordD);
            aWandererI = aWandererI + (((RotL64(aPrevious, 29U) + aOrbiterC) + RotL64(aOrbiterK, 23U)) + aNonceWordH);
            aWandererE = aWandererE ^ ((((RotL64(aScatter, 3U) + RotL64(aOrbiterH, 13U)) + aOrbiterC) + aNonceWordA) + aPhaseEWandererUpdateSaltC[((aIndex + 28U)) & S_SALT1]);
            //
            aCarry = aCarry + (aWandererI ^ RotL64(aWandererE, 23U));
            aCarry = aCarry + (RotL64(aWandererH, 47U) ^ aWandererC);
            aCarry = aCarry + (aWandererK ^ RotL64(aWandererF, 51U));
            aCarry = aCarry + RotL64(aWandererD, 36U);
            aCarry = aCarry + RotL64(aIngress, 3U);
            aCarry = TwistMix64::DiffuseC(aCarry);
            //
            aFireLaneC[aIndex] = aIngress;
        }
    
        // seed_loop_a loop 4
        // ingress from: aFireLaneC, aKeyRowReadB, mSource, aFireLaneA
        // ingress directions: aFireLaneC forward forced, aKeyRowReadB forward forced, mSource forward forced, aFireLaneA forward/backward random
        // cross from: aKeyRowReadA, aFireLaneB
        // cross directions: aKeyRowReadA backward forced, aFireLaneB backward/forward random
        // write to: aFireLaneD
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aFireLaneC[((aIndex + 10318U)) & S_BLOCK1], 51U) ^ RotL64(aKeyRowReadB[((aIndex + 9767U)) & W_KEY1], 5U));
            aIngress ^= (RotL64(mSource[((aIndex + 9223U)) & S_BLOCK1], 43U) ^ RotL64(aFireLaneA[((S_BLOCK1 - aIndex + 10144U)) & S_BLOCK1], 24U));
            aIngress = TwistMix64::DiffuseA(((aIngress ^ aPhaseFDomainWordIngress) ^ aNonceWordC));
            //
            aCross = RotL64(aKeyRowReadA[(((2047U - aIndex) + 9972U)) & W_KEY1], 21U) ^ RotL64(aFireLaneB[((aIndex + 9625U)) & S_BLOCK1], 39U);
            aCross = TwistMix64::DiffuseB(((aCross ^ aPhaseFDomainWordCross) ^ aNonceWordK));
            //
            aScatter = (RotL64(aCarry, 10U) + RotL64(aIngress, 23U)) ^ (RotL64(aCross, 53U) + RotL64(aPrevious, 35U));
            aScatter = TwistMix64::DiffuseC(((aScatter ^ aPhaseFDomainWordScatter) ^ aNonceWordM));
            //
            aOrbiterK = ((aWandererD + RotL64(aScatter, 47U)) + RotL64(aCarry, 39U)) + 4634399531433127141U;
            aOrbiterE = ((aWandererH + RotL64(aCross, 5U)) + 16961792729406903200U) + aPhaseFOrbiterAssignSaltF[(((31U - aIndex) + 13U)) & S_SALT1];
            aOrbiterI = ((aWandererA + RotL64(aIngress, 19U)) + 4105280732301137738U) + aNonceWordM;
            aOrbiterB = (((aWandererI + RotL64(aPrevious, 37U)) + RotL64(aCarry, 3U)) + 15692013501147331191U) + aNonceWordE;
            aOrbiterA = ((aWandererE + RotL64(aScatter, 26U)) + 1252216715968780587U) + aNonceWordP;
            aOrbiterD = (((aWandererJ + RotL64(aCross, 13U)) + 7958289043012473752U) + aPhaseFOrbiterAssignSaltC[(((31U - aIndex) + 26U)) & S_SALT1]) + aNonceWordJ;
            aOrbiterF = ((aWandererB + RotL64(aIngress, 57U)) + RotL64(aCarry, 21U)) + 6611577301818896615U;
            //
            aOrbiterK = ((aOrbiterK + aOrbiterE) + 8506226754305949140U) + aPhaseFOrbiterUpdateSaltA[((aIndex + 27U)) & S_SALT1];
            aOrbiterI = (aOrbiterI ^ aOrbiterK) ^ 3648813120449403353U;
            aOrbiterI = RotL64((aOrbiterI * 9521367946879238849U), 13U);
            //
            aOrbiterB = (aOrbiterB + aOrbiterA) + 5195245426245535735U;
            aOrbiterD = (aOrbiterD ^ aOrbiterB) ^ 542948051600803051U;
            aOrbiterD = RotL64((aOrbiterD * 4631106308856448475U), 35U);
            //
            aOrbiterA = (aOrbiterA + aOrbiterD) + 11974253551208964789U;
            aOrbiterF = (aOrbiterF ^ aOrbiterA) ^ 10596463592332655367U;
            aOrbiterF = RotL64((aOrbiterF * 10941161258815714641U), 57U);
            //
            aOrbiterD = ((aOrbiterD + aOrbiterF) + 12015129484061440159U) + aNonceWordB;
            aOrbiterK = ((aOrbiterK ^ aOrbiterD) ^ 8254944355710109060U) ^ aPhaseFOrbiterUpdateSaltF[(((31U - aIndex) + 11U)) & S_SALT1];
            aOrbiterK = RotL64((aOrbiterK * 3233697992479357615U), 27U);
            //
            aOrbiterI = (((aOrbiterI + aOrbiterB) + 2754858806943915419U) + aPhaseFOrbiterUpdateSaltE[(((31U - aIndex) + 25U)) & S_SALT1]) + aNonceWordO;
            aOrbiterA = ((aOrbiterA ^ aOrbiterI) ^ 5007802002906662779U) ^ aPhaseFOrbiterUpdateSaltC[(((31U - aIndex) + 29U)) & S_SALT1];
            aOrbiterA = RotL64((aOrbiterA * 15613733948331639723U), 51U);
            //
            aOrbiterF = ((aOrbiterF + aOrbiterK) + 6262190752136523216U) + aNonceWordI;
            aOrbiterE = (aOrbiterE ^ aOrbiterF) ^ 10528977986487821428U;
            aOrbiterE = RotL64((aOrbiterE * 1184258264034585525U), 5U);
            //
            aOrbiterE = (aOrbiterE + aOrbiterI) + 8511097226098211854U;
            aOrbiterB = (aOrbiterB ^ aOrbiterE) ^ 12091864735686692582U;
            aOrbiterB = RotL64((aOrbiterB * 6128140528141411237U), 43U);
            //
            aIngress = RotL64(aOrbiterA, 13U) ^ aOrbiterE;
            aIngress = aIngress + (aOrbiterF ^ RotL64(aOrbiterK, 60U));
            aIngress = aIngress + (aOrbiterI ^ RotL64(aOrbiterD, 39U));
            aIngress = aIngress + RotL64(aOrbiterB, 51U);
            aIngress = TwistMix64::DiffuseB((aIngress + aScatter));
            //
            aWandererD = aWandererD + (((RotL64(aPrevious, 19U) + RotL64(aOrbiterF, 21U)) + aOrbiterK) + aPhaseFWandererUpdateSaltF[((aIndex + 23U)) & S_SALT1]);
            aWandererI = aWandererI ^ (((RotL64(aCross, 3U) + aOrbiterB) + RotL64(aOrbiterA, 41U)) + aNonceWordG);
            aWandererE = aWandererE + (((RotL64(aScatter, 13U) + aOrbiterK) + RotL64(aOrbiterE, 47U)) + RotL64(aCarry, 57U));
            aWandererH = aWandererH ^ (((RotL64(aIngress, 47U) + RotL64(aOrbiterK, 53U)) + aOrbiterI) + aNonceWordN);
            aWandererB = aWandererB + (((RotL64(aScatter, 41U) + RotL64(aOrbiterF, 60U)) + aOrbiterD) + aNonceWordA);
            aWandererJ = aWandererJ ^ ((((RotL64(aPrevious, 53U) + aOrbiterB) + RotL64(aOrbiterI, 11U)) + aNonceWordF) + aPhaseFWandererUpdateSaltD[(((31U - aIndex) + 8U)) & S_SALT1]);
            aWandererA = aWandererA + (((RotL64(aCross, 28U) + aOrbiterI) + RotL64(aOrbiterE, 29U)) + RotL64(aCarry, 37U));
            //
            aCarry = aCarry + (RotL64(aWandererI, 22U) ^ aWandererB);
            aCarry = aCarry + (RotL64(aWandererA, 27U) ^ aWandererE);
            aCarry = aCarry + (RotL64(aWandererH, 47U) ^ aWandererJ);
            aCarry = aCarry + RotL64(aWandererD, 3U);
            aCarry = aCarry + RotL64(aIngress, 13U);
            aCarry = TwistMix64::DiffuseC(aCarry);
            //
            aFireLaneD[S_BLOCK1 - aIndex] = aIngress;
        }
    
        // seed_loop_a loop 5
        // ingress from: aFireLaneD, aKeyRowReadA, aKeyRowReadB, mSource, aFireLaneB
        // ingress directions: aFireLaneD forward forced, aKeyRowReadA forward forced, aKeyRowReadB forward forced, mSource forward forced, aFireLaneB forward/backward random
        // cross from: aFireLaneA, aFireLaneC
        // cross directions: aFireLaneA backward forced, aFireLaneC backward/forward random
        // write to: aWorkLaneA
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aFireLaneD[((aIndex + 11197U)) & S_BLOCK1], 54U) ^ RotL64(aKeyRowReadA[((aIndex + 12988U)) & W_KEY1], 29U));
            aIngress ^= (RotL64(aKeyRowReadB[((aIndex + 12507U)) & W_KEY1], 43U) ^ RotL64(mSource[((aIndex + 11994U)) & S_BLOCK1], 21U));
            aIngress ^= RotL64(aFireLaneB[((S_BLOCK1 - aIndex + 12795U)) & S_BLOCK1], 13U);
            aIngress = TwistMix64::DiffuseB(((aIngress ^ aPhaseFDomainWordIngress) ^ aNonceWordA));
            //
            aCross = RotL64(aFireLaneA[((S_BLOCK1 - aIndex + 12581U)) & S_BLOCK1], 43U) ^ RotL64(aFireLaneC[((aIndex + 11989U)) & S_BLOCK1], 24U);
            aCross = TwistMix64::DiffuseA(((aCross ^ aPhaseFDomainWordCross) ^ aNonceWordB));
            //
            aScatter = (RotL64(aCarry, 37U) ^ RotL64(aIngress, 11U)) + (RotL64(aCross, 23U) + RotL64(aPrevious, 54U));
            aScatter = TwistMix64::DiffuseA(((aScatter ^ aPhaseFDomainWordScatter) ^ aNonceWordI));
            //
            aOrbiterI = (aWandererE + RotL64(aScatter, 21U)) + 17074147006464019918U;
            aOrbiterD = ((((aWandererI + RotL64(aPrevious, 47U)) + RotL64(aCarry, 43U)) + 10559516626129419928U) + aPhaseFOrbiterAssignSaltB[(((31U - aIndex) + 27U)) & S_SALT1]) + aNonceWordN;
            aOrbiterJ = ((aWandererF + RotL64(aCross, 35U)) + 13280363679503946221U) + aNonceWordO;
            aOrbiterE = (((aWandererA + RotL64(aIngress, 56U)) + RotL64(aCarry, 57U)) + 17657115422132457413U) + aPhaseFOrbiterAssignSaltA[(((31U - aIndex) + 5U)) & S_SALT1];
            aOrbiterB = ((aWandererK + RotL64(aScatter, 41U)) + RotL64(aCarry, 19U)) + 13325837013304973008U;
            aOrbiterH = ((aWandererJ + RotL64(aPrevious, 11U)) + 3059707750486106037U) + aNonceWordC;
            aOrbiterC = ((aWandererD + RotL64(aIngress, 3U)) + 4529045702503050852U) + aNonceWordJ;
            //
            aOrbiterI = (aOrbiterI + aOrbiterD) + 10726578475550904292U;
            aOrbiterJ = (((aOrbiterJ ^ aOrbiterI) ^ 14832537837996659885U) ^ aPhaseFOrbiterUpdateSaltD[(((31U - aIndex) + 24U)) & S_SALT1]) ^ aNonceWordF;
            aOrbiterJ = RotL64((aOrbiterJ * 808060368961520519U), 41U);
            //
            aOrbiterJ = (aOrbiterJ + aOrbiterE) + 220094417441809246U;
            aOrbiterB = (aOrbiterB ^ aOrbiterJ) ^ 15343130035105342194U;
            aOrbiterB = RotL64((aOrbiterB * 7984652435043810845U), 29U);
            //
            aOrbiterB = ((aOrbiterB + aOrbiterI) + 16592263353426409884U) + aNonceWordE;
            aOrbiterH = (aOrbiterH ^ aOrbiterB) ^ 15649290906447931918U;
            aOrbiterH = RotL64((aOrbiterH * 8405875177836650731U), 13U);
            //
            aOrbiterD = ((aOrbiterD + aOrbiterH) + 11437410545843708269U) + aPhaseFOrbiterUpdateSaltB[((aIndex + 10U)) & S_SALT1];
            aOrbiterE = ((aOrbiterE ^ aOrbiterD) ^ 5859769136073011444U) ^ aNonceWordI;
            aOrbiterE = RotL64((aOrbiterE * 1065016088086441107U), 35U);
            //
            aOrbiterC = (aOrbiterC + aOrbiterB) + 15188064100307340341U;
            aOrbiterD = ((aOrbiterD ^ aOrbiterC) ^ 4367466521843260049U) ^ aPhaseFOrbiterUpdateSaltA[(((31U - aIndex) + 26U)) & S_SALT1];
            aOrbiterD = RotL64((aOrbiterD * 15916715854192820923U), 5U);
            //
            aOrbiterH = ((aOrbiterH + aOrbiterJ) + 8482617283860566845U) + aPhaseFOrbiterUpdateSaltE[((aIndex + 3U)) & S_SALT1];
            aOrbiterC = (aOrbiterC ^ aOrbiterH) ^ 2585745804937342972U;
            aOrbiterC = RotL64((aOrbiterC * 8267269625632139809U), 51U);
            //
            aOrbiterE = (aOrbiterE + aOrbiterC) + 1687641344403425541U;
            aOrbiterI = ((aOrbiterI ^ aOrbiterE) ^ 13667916445979421400U) ^ aNonceWordH;
            aOrbiterI = RotL64((aOrbiterI * 8191322670355590027U), 21U);
            //
            aIngress = RotL64(aOrbiterH, 39U) ^ aOrbiterB;
            aIngress = aIngress + (RotL64(aOrbiterJ, 51U) ^ aOrbiterE);
            aIngress = aIngress + (aOrbiterI ^ RotL64(aOrbiterD, 19U));
            aIngress = aIngress + RotL64(aOrbiterC, 3U);
            aIngress = TwistMix64::DiffuseA((aIngress + aScatter));
            //
            aWandererF = aWandererF + (((RotL64(aScatter, 29U) + aOrbiterI) + RotL64(aOrbiterB, 27U)) + aPhaseFWandererUpdateSaltA[((aIndex + 7U)) & S_SALT1]);
            aWandererE = aWandererE ^ ((RotL64(aIngress, 11U) + RotL64(aOrbiterJ, 57U)) + aOrbiterE);
            aWandererD = aWandererD + (((RotL64(aPrevious, 47U) + RotL64(aOrbiterD, 11U)) + aOrbiterH) + aNonceWordM);
            aWandererK = aWandererK ^ (((RotL64(aCross, 18U) + RotL64(aOrbiterI, 37U)) + aOrbiterD) + aPhaseFWandererUpdateSaltE[((aIndex + 18U)) & S_SALT1]);
            aWandererJ = aWandererJ + (((RotL64(aPrevious, 35U) + RotL64(aOrbiterJ, 43U)) + aOrbiterD) + RotL64(aCarry, 53U));
            aWandererI = aWandererI ^ ((RotL64(aScatter, 41U) + RotL64(aOrbiterH, 19U)) + aOrbiterJ);
            aWandererA = aWandererA + ((((RotL64(aCross, 5U) + RotL64(aOrbiterC, 50U)) + aOrbiterE) + RotL64(aCarry, 3U)) + aNonceWordP);
            //
            aCarry = aCarry + (RotL64(aWandererJ, 44U) ^ aWandererD);
            aCarry = aCarry + (aWandererF ^ RotL64(aWandererA, 19U));
            aCarry = aCarry + (aWandererE ^ RotL64(aWandererI, 5U));
            aCarry = aCarry + RotL64(aWandererK, 23U);
            aCarry = aCarry + RotL64(aIngress, 39U);
            aCarry = TwistMix64::DiffuseB(aCarry);
            //
            aWorkLaneA[aIndex] = aIngress;
        }
    
        // seed_loop_a loop 6
        // ingress from: aWorkLaneA, aFireLaneC
        // ingress directions: aWorkLaneA forward forced, aFireLaneC forward/backward random
        // cross from: aKeyRowReadA, aKeyRowReadB, mSource, aFireLaneB, aFireLaneA
        // cross directions: aKeyRowReadA backward forced, aKeyRowReadB backward forced, mSource backward forced, aFireLaneB backward forced, aFireLaneA backward/forward random
        // write to: aWorkLaneB
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = RotL64(aWorkLaneA[((aIndex + 15953U)) & S_BLOCK1], 27U) ^ RotL64(aFireLaneC[((aIndex + 14380U)) & S_BLOCK1], 57U);
            aIngress = TwistMix64::DiffuseB(((aIngress ^ aPhaseFDomainWordIngress) ^ aNonceWordB));
            //
            aCross = (RotL64(aKeyRowReadA[(((2047U - aIndex) + 13753U)) & W_KEY1], 48U) ^ RotL64(aKeyRowReadB[(((2047U - aIndex) + 16278U)) & W_KEY1], 5U));
            aCross ^= (RotL64(mSource[((S_BLOCK1 - aIndex + 16175U)) & S_BLOCK1], 39U) ^ RotL64(aFireLaneB[((S_BLOCK1 - aIndex + 15162U)) & S_BLOCK1], 21U));
            aCross ^= RotL64(aFireLaneA[((aIndex + 16342U)) & S_BLOCK1], 29U);
            aCross = TwistMix64::DiffuseB(((aCross ^ aPhaseFDomainWordCross) ^ aNonceWordJ));
            //
            aScatter = (RotL64(aIngress, 37U) ^ RotL64(aCross, 3U)) + (RotL64(aCarry, 50U) ^ RotL64(aPrevious, 19U));
            aScatter = TwistMix64::DiffuseC(((aScatter ^ aPhaseFDomainWordScatter) ^ aNonceWordM));
            //
            aOrbiterD = ((aWandererD + RotL64(aScatter, 23U)) + 5171470532667965920U) + aPhaseFOrbiterAssignSaltD[(((31U - aIndex) + 27U)) & S_SALT1];
            aOrbiterI = ((((aWandererF + RotL64(aPrevious, 43U)) + RotL64(aCarry, 5U)) + 750549462358682403U) + aPhaseFOrbiterAssignSaltE[(((31U - aIndex) + 17U)) & S_SALT1]) + aNonceWordC;
            aOrbiterK = ((aWandererG + RotL64(aCross, 6U)) + RotL64(aCarry, 21U)) + 3325689257577120525U;
            aOrbiterH = (aWandererB + RotL64(aIngress, 57U)) + 18031575461559790826U;
            aOrbiterE = (aWandererK + RotL64(aPrevious, 35U)) + 13874739537012288677U;
            aOrbiterF = (((aWandererC + RotL64(aScatter, 29U)) + RotL64(aCarry, 41U)) + 4250029868785016865U) + aNonceWordG;
            aOrbiterJ = ((aWandererA + RotL64(aCross, 51U)) + 8211158803112611161U) + aNonceWordM;
            //
            aOrbiterD = (aOrbiterD + aOrbiterI) + 1083939790236786027U;
            aOrbiterK = ((aOrbiterK ^ aOrbiterD) ^ 3446525462376962464U) ^ aNonceWordO;
            aOrbiterK = RotL64((aOrbiterK * 13603702473750888213U), 37U);
            //
            aOrbiterH = (aOrbiterH + aOrbiterK) + 6973817815000417325U;
            aOrbiterE = (aOrbiterE ^ aOrbiterH) ^ 15230876489676945543U;
            aOrbiterE = RotL64((aOrbiterE * 7737039082964537651U), 53U);
            //
            aOrbiterI = ((aOrbiterI + aOrbiterE) + 9359727659738755880U) + aNonceWordF;
            aOrbiterF = (aOrbiterF ^ aOrbiterI) ^ 8775170107816327654U;
            aOrbiterF = RotL64((aOrbiterF * 6910680458261008653U), 27U);
            //
            aOrbiterF = ((aOrbiterF + aOrbiterD) + 11958941755525038545U) + aPhaseFOrbiterUpdateSaltD[((aIndex + 19U)) & S_SALT1];
            aOrbiterH = (aOrbiterH ^ aOrbiterF) ^ 16966819714283167348U;
            aOrbiterH = RotL64((aOrbiterH * 16363457661846050749U), 3U);
            //
            aOrbiterJ = (aOrbiterJ + aOrbiterH) + 14556087985619763243U;
            aOrbiterI = ((aOrbiterI ^ aOrbiterJ) ^ 17915047508377045221U) ^ aPhaseFOrbiterUpdateSaltC[((aIndex + 13U)) & S_SALT1];
            aOrbiterI = RotL64((aOrbiterI * 6727635453185130109U), 43U);
            //
            aOrbiterK = (aOrbiterK + aOrbiterF) + 8578745677485367222U;
            aOrbiterJ = (aOrbiterJ ^ aOrbiterK) ^ 7002181668717618866U;
            aOrbiterJ = RotL64((aOrbiterJ * 12329703532414955235U), 19U);
            //
            aOrbiterE = ((aOrbiterE + aOrbiterJ) + 3569939503066735457U) + aPhaseFOrbiterUpdateSaltA[(((31U - aIndex) + 5U)) & S_SALT1];
            aOrbiterD = ((aOrbiterD ^ aOrbiterE) ^ 2956247934282522184U) ^ aPhaseFOrbiterUpdateSaltF[(((31U - aIndex) + 12U)) & S_SALT1];
            aOrbiterD = RotL64((aOrbiterD * 9946650822131152531U), 13U);
            //
            aIngress = RotL64(aOrbiterF, 39U) ^ aOrbiterE;
            aIngress = aIngress + (aOrbiterD ^ RotL64(aOrbiterK, 58U));
            aIngress = aIngress + (RotL64(aOrbiterH, 19U) ^ aOrbiterI);
            aIngress = aIngress + RotL64(aOrbiterJ, 5U);
            aIngress = TwistMix64::DiffuseB((aIngress + aScatter));
            //
            aWandererA = aWandererA ^ ((RotL64(aIngress, 30U) + RotL64(aOrbiterF, 3U)) + aOrbiterD);
            aWandererB = aWandererB + (((((RotL64(aScatter, 47U) + RotL64(aOrbiterE, 51U)) + aOrbiterI) + RotL64(aCarry, 41U)) + aNonceWordP) + aPhaseFWandererUpdateSaltB[((aIndex + 20U)) & S_SALT1]);
            aWandererF = aWandererF ^ ((RotL64(aCross, 13U) + aOrbiterD) + RotL64(aOrbiterE, 37U));
            aWandererK = aWandererK + (((RotL64(aPrevious, 21U) + RotL64(aOrbiterI, 11U)) + aOrbiterD) + RotL64(aCarry, 5U));
            aWandererD = aWandererD ^ (((RotL64(aScatter, 37U) + RotL64(aOrbiterD, 57U)) + aOrbiterH) + aPhaseFWandererUpdateSaltE[((aIndex + 9U)) & S_SALT1]);
            aWandererC = aWandererC + (((RotL64(aPrevious, 57U) + RotL64(aOrbiterJ, 27U)) + aOrbiterI) + aNonceWordN);
            aWandererG = aWandererG ^ ((RotL64(aCross, 5U) + aOrbiterK) + RotL64(aOrbiterF, 18U));
            //
            aCarry = aCarry + (aWandererG ^ RotL64(aWandererB, 5U));
            aCarry = aCarry + (aWandererC ^ RotL64(aWandererA, 24U));
            aCarry = aCarry + (aWandererK ^ RotL64(aWandererD, 19U));
            aCarry = aCarry + RotL64(aWandererF, 11U);
            aCarry = aCarry + RotL64(aIngress, 37U);
            aCarry = TwistMix64::DiffuseA(aCarry);
            //
            aWorkLaneB[S_BLOCK1 - aIndex] = aIngress;
        }
    
        // seed_loop_a loop 7
        // ingress from: aWorkLaneB, aKeyRowReadA, mSource, aFireLaneA
        // ingress directions: aWorkLaneB forward forced, aKeyRowReadA forward forced, mSource forward forced, aFireLaneA forward/backward random
        // cross from: aKeyRowReadB, aFireLaneD, aWorkLaneA
        // cross directions: aKeyRowReadB backward forced, aFireLaneD backward forced, aWorkLaneA backward/forward random
        // write to: aWorkLaneC
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aWorkLaneB[((aIndex + 17079U)) & S_BLOCK1], 51U) ^ RotL64(aKeyRowReadA[((aIndex + 18857U)) & W_KEY1], 43U));
            aIngress ^= (RotL64(mSource[((aIndex + 18415U)) & S_BLOCK1], 35U) ^ RotL64(aFireLaneA[((aIndex + 17061U)) & S_BLOCK1], 22U));
            aIngress = TwistMix64::DiffuseA(((aIngress ^ aPhaseGDomainWordIngress) ^ aNonceWordG));
            //
            aCross = (RotL64(aKeyRowReadB[(((2047U - aIndex) + 16496U)) & W_KEY1], 36U) ^ RotL64(aFireLaneD[((S_BLOCK1 - aIndex + 16603U)) & S_BLOCK1], 57U));
            aCross ^= RotL64(aWorkLaneA[((S_BLOCK1 - aIndex + 16633U)) & S_BLOCK1], 11U);
            aCross = TwistMix64::DiffuseA(((aCross ^ aPhaseGDomainWordCross) ^ aNonceWordL));
            //
            aScatter = (RotL64(aCarry, 50U) ^ RotL64(aIngress, 35U)) ^ (RotL64(aPrevious, 11U) + RotL64(aCross, 23U));
            aScatter = TwistMix64::DiffuseA(((aScatter ^ aPhaseGDomainWordScatter) ^ aNonceWordO));
            //
            aOrbiterC = (((aWandererG + RotL64(aIngress, 5U)) + 9133751643283278896U) + aPhaseGOrbiterAssignSaltA[((aIndex + 18U)) & S_SALT1]) + aNonceWordE;
            aOrbiterI = ((aWandererH + RotL64(aScatter, 51U)) + RotL64(aCarry, 53U)) + 8971581804375380408U;
            aOrbiterF = (aWandererE + RotL64(aCross, 35U)) + 12559650383714566592U;
            aOrbiterK = ((aWandererI + RotL64(aPrevious, 57U)) + 15753206088872859163U) + aNonceWordN;
            aOrbiterH = ((aWandererB + RotL64(aIngress, 41U)) + RotL64(aCarry, 11U)) + 7640756270450762350U;
            aOrbiterA = (((aWandererC + RotL64(aPrevious, 11U)) + RotL64(aCarry, 37U)) + 7340073357551376125U) + aNonceWordK;
            aOrbiterD = ((aWandererF + RotL64(aCross, 18U)) + 5270256573644196046U) + aPhaseGOrbiterAssignSaltB[((aIndex + 25U)) & S_SALT1];
            //
            aOrbiterC = ((aOrbiterC + aOrbiterI) + 3567367996479995928U) + aPhaseGOrbiterUpdateSaltB[((aIndex + 3U)) & S_SALT1];
            aOrbiterF = ((aOrbiterF ^ aOrbiterC) ^ 11939634537492733738U) ^ aPhaseGOrbiterUpdateSaltD[(((31U - aIndex) + 15U)) & S_SALT1];
            aOrbiterF = RotL64((aOrbiterF * 5640541900117183639U), 37U);
            //
            aOrbiterK = (((aOrbiterK + aOrbiterH) + 7051817732424527120U) + aPhaseGOrbiterUpdateSaltF[((aIndex + 26U)) & S_SALT1]) + aNonceWordA;
            aOrbiterC = (aOrbiterC ^ aOrbiterK) ^ 1730487669951837941U;
            aOrbiterC = RotL64((aOrbiterC * 15191634337956285841U), 23U);
            //
            aOrbiterH = (aOrbiterH + aOrbiterA) + 18009252467909454817U;
            aOrbiterI = (aOrbiterI ^ aOrbiterH) ^ 2361024272031696442U;
            aOrbiterI = RotL64((aOrbiterI * 15215151562500226027U), 3U);
            //
            aOrbiterF = (aOrbiterF + aOrbiterD) + 15902755877642960397U;
            aOrbiterH = (aOrbiterH ^ aOrbiterF) ^ 12243517544704116184U;
            aOrbiterH = RotL64((aOrbiterH * 2576071074148141447U), 57U);
            //
            aOrbiterA = ((aOrbiterA + aOrbiterF) + 16846181962302186187U) + aPhaseGOrbiterUpdateSaltA[(((31U - aIndex) + 10U)) & S_SALT1];
            aOrbiterK = (aOrbiterK ^ aOrbiterA) ^ 636121425116506681U;
            aOrbiterK = RotL64((aOrbiterK * 17075030673338779993U), 43U);
            //
            aOrbiterI = (aOrbiterI + aOrbiterK) + 6887385655828217318U;
            aOrbiterD = (aOrbiterD ^ aOrbiterI) ^ 3705834550934775862U;
            aOrbiterD = RotL64((aOrbiterD * 11275428284929594435U), 51U);
            //
            aOrbiterD = ((aOrbiterD + aOrbiterC) + 11165142437077969438U) + aNonceWordD;
            aOrbiterA = (aOrbiterA ^ aOrbiterD) ^ 6426659930331618269U;
            aOrbiterA = RotL64((aOrbiterA * 17170640810530893705U), 13U);
            //
            aIngress = RotL64(aOrbiterI, 21U) ^ aOrbiterD;
            aIngress = aIngress + (aOrbiterK ^ RotL64(aOrbiterH, 3U));
            aIngress = aIngress + (RotL64(aOrbiterF, 51U) ^ aOrbiterA);
            aIngress = aIngress + RotL64(aOrbiterC, 13U);
            aIngress = TwistMix64::DiffuseB((aIngress + aScatter));
            //
            aWandererE = aWandererE ^ ((RotL64(aScatter, 23U) + RotL64(aOrbiterH, 46U)) + aOrbiterA);
            aWandererH = aWandererH + (((RotL64(aPrevious, 29U) + aOrbiterF) + RotL64(aOrbiterD, 11U)) + RotL64(aCarry, 3U));
            aWandererF = aWandererF ^ (((RotL64(aIngress, 57U) + RotL64(aOrbiterI, 19U)) + aOrbiterK) + aNonceWordC);
            aWandererC = aWandererC + ((((RotL64(aCross, 44U) + RotL64(aOrbiterD, 57U)) + aOrbiterA) + RotL64(aCarry, 23U)) + aNonceWordB);
            aWandererB = aWandererB ^ (((RotL64(aIngress, 51U) + RotL64(aOrbiterK, 29U)) + aOrbiterH) + aPhaseGWandererUpdateSaltE[((aIndex + 19U)) & S_SALT1]);
            aWandererG = aWandererG + (((RotL64(aPrevious, 3U) + aOrbiterC) + RotL64(aOrbiterF, 5U)) + aPhaseGWandererUpdateSaltF[(((31U - aIndex) + 20U)) & S_SALT1]);
            aWandererI = aWandererI ^ ((RotL64(aScatter, 35U) + RotL64(aOrbiterH, 39U)) + aOrbiterD);
            //
            aCarry = aCarry + (aWandererG ^ RotL64(aWandererH, 34U));
            aCarry = aCarry + (RotL64(aWandererF, 23U) ^ aWandererC);
            aCarry = aCarry + (aWandererE ^ RotL64(aWandererI, 57U));
            aCarry = aCarry + RotL64(aWandererB, 27U);
            aCarry = aCarry + RotL64(aIngress, 53U);
            aCarry = TwistMix64::DiffuseB(aCarry);
            //
            aWorkLaneC[aIndex] = aIngress;
        }
    
        // seed_loop_a loop 8
        // ingress from: aWorkLaneC, mSource, aWorkLaneA, aFireLaneA
        // ingress directions: aWorkLaneC forward forced, mSource forward forced, aWorkLaneA forward forced, aFireLaneA forward/backward random
        // cross from: aKeyRowReadA, aKeyRowReadB, aWorkLaneB, aFireLaneB
        // cross directions: aKeyRowReadA backward forced, aKeyRowReadB backward forced, aWorkLaneB backward forced, aFireLaneB backward/forward random
        // write to: aWorkLaneD
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aWorkLaneC[((aIndex + 19956U)) & S_BLOCK1], 21U) ^ RotL64(mSource[((aIndex + 19411U)) & S_BLOCK1], 12U));
            aIngress ^= (RotL64(aWorkLaneA[((aIndex + 19115U)) & S_BLOCK1], 51U) ^ RotL64(aFireLaneA[((S_BLOCK1 - aIndex + 21826U)) & S_BLOCK1], 37U));
            aIngress = TwistMix64::DiffuseC(((aIngress ^ aPhaseGDomainWordIngress) ^ aNonceWordE));
            //
            aCross = (RotL64(aKeyRowReadA[(((2047U - aIndex) + 19569U)) & W_KEY1], 11U) ^ RotL64(aKeyRowReadB[(((2047U - aIndex) + 19334U)) & W_KEY1], 27U));
            aCross ^= (RotL64(aWorkLaneB[((S_BLOCK1 - aIndex + 20878U)) & S_BLOCK1], 36U) ^ RotL64(aFireLaneB[((S_BLOCK1 - aIndex + 21449U)) & S_BLOCK1], 3U));
            aCross = TwistMix64::DiffuseC(((aCross ^ aPhaseGDomainWordCross) ^ aNonceWordP));
            //
            aScatter = (RotL64(aIngress, 41U) + RotL64(aCross, 11U)) ^ (RotL64(aPrevious, 53U) + RotL64(aCarry, 28U));
            aScatter = TwistMix64::DiffuseC(((aScatter ^ aPhaseGDomainWordScatter) ^ aNonceWordN));
            //
            aOrbiterD = (aWandererK + RotL64(aCross, 21U)) + 77518479758428414U;
            aOrbiterF = ((aWandererG + RotL64(aPrevious, 27U)) + RotL64(aCarry, 37U)) + 4832061802166300011U;
            aOrbiterC = ((aWandererI + RotL64(aIngress, 43U)) + 11695291171006574112U) + aNonceWordA;
            aOrbiterG = ((aWandererF + RotL64(aScatter, 57U)) + 7467412817843260094U) + aPhaseGOrbiterAssignSaltE[(((31U - aIndex) + 23U)) & S_SALT1];
            aOrbiterA = (aWandererJ + RotL64(aPrevious, 13U)) + 17801484124471154757U;
            aOrbiterE = (((aWandererA + RotL64(aIngress, 37U)) + RotL64(aCarry, 5U)) + 5555455638503958639U) + aPhaseGOrbiterAssignSaltF[((aIndex + 21U)) & S_SALT1];
            aOrbiterJ = (((aWandererD + RotL64(aCross, 4U)) + RotL64(aCarry, 57U)) + 5669470540733721606U) + aNonceWordI;
            //
            aOrbiterD = (aOrbiterD + aOrbiterF) + 3042388456327784163U;
            aOrbiterC = (((aOrbiterC ^ aOrbiterD) ^ 2236734925228156691U) ^ aPhaseGOrbiterUpdateSaltA[(((31U - aIndex) + 26U)) & S_SALT1]) ^ aNonceWordM;
            aOrbiterC = RotL64((aOrbiterC * 10076582424701705531U), 41U);
            //
            aOrbiterG = (aOrbiterG + aOrbiterD) + 14459720401528685450U;
            aOrbiterA = ((aOrbiterA ^ aOrbiterG) ^ 4814967631216658856U) ^ aPhaseGOrbiterUpdateSaltF[(((31U - aIndex) + 24U)) & S_SALT1];
            aOrbiterA = RotL64((aOrbiterA * 18288097536171386643U), 35U);
            //
            aOrbiterE = (aOrbiterE + aOrbiterJ) + 16950679344449075945U;
            aOrbiterD = ((aOrbiterD ^ aOrbiterE) ^ 6262238639302011050U) ^ aPhaseGOrbiterUpdateSaltE[(((31U - aIndex) + 28U)) & S_SALT1];
            aOrbiterD = RotL64((aOrbiterD * 9942659897425088183U), 19U);
            //
            aOrbiterC = (aOrbiterC + aOrbiterE) + 3522256359074996724U;
            aOrbiterG = (aOrbiterG ^ aOrbiterC) ^ 12524717897707074242U;
            aOrbiterG = RotL64((aOrbiterG * 6787771338063891989U), 47U);
            //
            aOrbiterA = ((aOrbiterA + aOrbiterC) + 13891759914865623828U) + aNonceWordF;
            aOrbiterJ = (aOrbiterJ ^ aOrbiterA) ^ 11910250571469028666U;
            aOrbiterJ = RotL64((aOrbiterJ * 12311343917878428995U), 53U);
            //
            aOrbiterJ = (aOrbiterJ + aOrbiterG) + 2240189915640314069U;
            aOrbiterF = ((aOrbiterF ^ aOrbiterJ) ^ 5365912986308810837U) ^ aPhaseGOrbiterUpdateSaltB[((aIndex + 3U)) & S_SALT1];
            aOrbiterF = RotL64((aOrbiterF * 15133972552032469957U), 29U);
            //
            aOrbiterF = (aOrbiterF + aOrbiterA) + 9323732721344489753U;
            aOrbiterE = ((aOrbiterE ^ aOrbiterF) ^ 13087326560957916553U) ^ aNonceWordL;
            aOrbiterE = RotL64((aOrbiterE * 14659491687401151733U), 5U);
            //
            aIngress = RotL64(aOrbiterF, 35U) ^ aOrbiterD;
            aIngress = aIngress + (aOrbiterJ ^ RotL64(aOrbiterE, 27U));
            aIngress = aIngress + (RotL64(aOrbiterC, 53U) ^ aOrbiterA);
            aIngress = aIngress + RotL64(aOrbiterG, 5U);
            aIngress = TwistMix64::DiffuseA((aIngress + aScatter));
            //
            aWandererK = aWandererK + (((((RotL64(aPrevious, 41U) + RotL64(aOrbiterD, 21U)) + aOrbiterE) + RotL64(aCarry, 27U)) + aNonceWordH) + aPhaseGWandererUpdateSaltD[(((31U - aIndex) + 4U)) & S_SALT1]);
            aWandererD = aWandererD ^ ((RotL64(aCross, 19U) + RotL64(aOrbiterD, 53U)) + aOrbiterG);
            aWandererG = aWandererG + ((RotL64(aIngress, 27U) + aOrbiterG) + RotL64(aOrbiterE, 29U));
            aWandererA = aWandererA ^ (((RotL64(aScatter, 3U) + RotL64(aOrbiterG, 35U)) + aOrbiterA) + aPhaseGWandererUpdateSaltB[((aIndex + 11U)) & S_SALT1]);
            aWandererF = aWandererF + ((((RotL64(aIngress, 35U) + aOrbiterJ) + RotL64(aOrbiterF, 4U)) + RotL64(aCarry, 13U)) + aNonceWordO);
            aWandererI = aWandererI ^ ((RotL64(aCross, 57U) + RotL64(aOrbiterE, 47U)) + aOrbiterC);
            aWandererJ = aWandererJ + (((RotL64(aScatter, 50U) + aOrbiterA) + RotL64(aOrbiterF, 13U)) + aNonceWordD);
            //
            aCarry = aCarry + (aWandererG ^ RotL64(aWandererI, 4U));
            aCarry = aCarry + (aWandererF ^ RotL64(aWandererK, 39U));
            aCarry = aCarry + (RotL64(aWandererD, 11U) ^ aWandererA);
            aCarry = aCarry + RotL64(aWandererJ, 29U);
            aCarry = aCarry + RotL64(aIngress, 18U);
            aCarry = TwistMix64::DiffuseB(aCarry);
            //
            aWorkLaneD[S_BLOCK1 - aIndex] = aIngress;
        }
    
        // seed_loop_a loop 9
        // ingress from: aWorkLaneD, aKeyRowReadA, aKeyRowReadB, aWorkLaneC
        // ingress directions: aWorkLaneD forward forced, aKeyRowReadA forward forced, aKeyRowReadB forward forced, aWorkLaneC forward/backward random
        // cross from: mSource, aWorkLaneA, aFireLaneC, aFireLaneD
        // cross directions: mSource backward forced, aWorkLaneA backward forced, aFireLaneC backward forced, aFireLaneD backward/forward random
        // write to: aExpandLaneA
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aWorkLaneD[((aIndex + 22368U)) & S_BLOCK1], 37U) ^ RotL64(aKeyRowReadA[((aIndex + 23515U)) & W_KEY1], 47U));
            aIngress ^= (RotL64(aKeyRowReadB[((aIndex + 23675U)) & W_KEY1], 3U) ^ RotL64(aWorkLaneC[((aIndex + 21867U)) & S_BLOCK1], 12U));
            aIngress = TwistMix64::DiffuseA(((aIngress ^ aPhaseGDomainWordIngress) ^ aNonceWordH));
            //
            aCross = (RotL64(mSource[((S_BLOCK1 - aIndex + 22083U)) & S_BLOCK1], 19U) ^ RotL64(aWorkLaneA[((S_BLOCK1 - aIndex + 22075U)) & S_BLOCK1], 58U));
            aCross ^= (RotL64(aFireLaneC[((S_BLOCK1 - aIndex + 23566U)) & S_BLOCK1], 27U) ^ RotL64(aFireLaneD[((aIndex + 22659U)) & S_BLOCK1], 41U));
            aCross = TwistMix64::DiffuseC(((aCross ^ aPhaseGDomainWordCross) ^ aNonceWordK));
            //
            aScatter = (RotL64(aIngress, 24U) + RotL64(aCarry, 41U)) + (RotL64(aPrevious, 53U) ^ RotL64(aCross, 11U));
            aScatter = TwistMix64::DiffuseC(((aScatter ^ aPhaseGDomainWordScatter) ^ aNonceWordN));
            //
            aOrbiterB = (((aWandererD + RotL64(aScatter, 14U)) + RotL64(aCarry, 57U)) + 7790166497945719700U) + aNonceWordL;
            aOrbiterF = (((aWandererC + RotL64(aIngress, 51U)) + 7136208896846119188U) + aPhaseGOrbiterAssignSaltB[((aIndex + 11U)) & S_SALT1]) + aNonceWordI;
            aOrbiterK = (((aWandererK + RotL64(aPrevious, 57U)) + 12123156943355100886U) + aPhaseGOrbiterAssignSaltD[(((31U - aIndex) + 10U)) & S_SALT1]) + aNonceWordE;
            aOrbiterJ = ((aWandererB + RotL64(aCross, 5U)) + RotL64(aCarry, 21U)) + 5095546037880875199U;
            aOrbiterE = (aWandererA + RotL64(aPrevious, 35U)) + 17642705393916765992U;
            aOrbiterH = ((aWandererE + RotL64(aIngress, 43U)) + RotL64(aCarry, 41U)) + 9918479837334416990U;
            aOrbiterI = (aWandererF + RotL64(aCross, 21U)) + 4890009823843176466U;
            //
            aOrbiterB = ((aOrbiterB + aOrbiterF) + 17652590786213674124U) + aNonceWordG;
            aOrbiterK = (aOrbiterK ^ aOrbiterB) ^ 870002527644696135U;
            aOrbiterK = RotL64((aOrbiterK * 915408393979165539U), 35U);
            //
            aOrbiterJ = (aOrbiterJ + aOrbiterE) + 12545429703552643682U;
            aOrbiterB = (aOrbiterB ^ aOrbiterJ) ^ 5310272867406182581U;
            aOrbiterB = RotL64((aOrbiterB * 10420003334833925011U), 57U);
            //
            aOrbiterF = ((aOrbiterF + aOrbiterK) + 3264719049050179440U) + aPhaseGOrbiterUpdateSaltC[(((31U - aIndex) + 8U)) & S_SALT1];
            aOrbiterH = ((aOrbiterH ^ aOrbiterF) ^ 1967241238180278937U) ^ aNonceWordN;
            aOrbiterH = RotL64((aOrbiterH * 13004319774269457957U), 3U);
            //
            aOrbiterE = ((aOrbiterE + aOrbiterB) + 773883832927040736U) + aNonceWordD;
            aOrbiterF = (aOrbiterF ^ aOrbiterE) ^ 12766817190261232485U;
            aOrbiterF = RotL64((aOrbiterF * 7448864556802318431U), 51U);
            //
            aOrbiterH = (aOrbiterH + aOrbiterI) + 260069382395598265U;
            aOrbiterJ = (aOrbiterJ ^ aOrbiterH) ^ 15462103891287350123U;
            aOrbiterJ = RotL64((aOrbiterJ * 5029268763635635753U), 11U);
            //
            aOrbiterK = ((aOrbiterK + aOrbiterH) + 4072032867513289827U) + aPhaseGOrbiterUpdateSaltF[((aIndex + 22U)) & S_SALT1];
            aOrbiterI = ((aOrbiterI ^ aOrbiterK) ^ 17153061419083897076U) ^ aPhaseGOrbiterUpdateSaltB[((aIndex + 25U)) & S_SALT1];
            aOrbiterI = RotL64((aOrbiterI * 11934532169271718913U), 19U);
            //
            aOrbiterI = (aOrbiterI + aOrbiterJ) + 6207264270332656966U;
            aOrbiterE = ((aOrbiterE ^ aOrbiterI) ^ 18048064697837314947U) ^ aPhaseGOrbiterUpdateSaltA[(((31U - aIndex) + 15U)) & S_SALT1];
            aOrbiterE = RotL64((aOrbiterE * 13632594619404208489U), 29U);
            //
            aIngress = aOrbiterE ^ RotL64(aOrbiterJ, 60U);
            aIngress = aIngress + (RotL64(aOrbiterH, 41U) ^ aOrbiterK);
            aIngress = aIngress + (aOrbiterF ^ RotL64(aOrbiterI, 21U));
            aIngress = aIngress + RotL64(aOrbiterB, 13U);
            aIngress = TwistMix64::DiffuseC((aIngress + aScatter));
            //
            aWandererC = aWandererC ^ (((RotL64(aIngress, 5U) + aOrbiterB) + RotL64(aOrbiterK, 44U)) + aNonceWordC);
            aWandererA = aWandererA + (((RotL64(aCross, 43U) + RotL64(aOrbiterJ, 13U)) + aOrbiterH) + RotL64(aCarry, 3U));
            aWandererF = aWandererF ^ ((((RotL64(aPrevious, 35U) + RotL64(aOrbiterH, 19U)) + aOrbiterF) + aNonceWordJ) + aPhaseGWandererUpdateSaltD[(((31U - aIndex) + 13U)) & S_SALT1]);
            aWandererB = aWandererB + (((RotL64(aScatter, 58U) + aOrbiterF) + RotL64(aOrbiterE, 51U)) + aNonceWordF);
            aWandererK = aWandererK ^ ((RotL64(aCross, 29U) + aOrbiterE) + RotL64(aOrbiterB, 3U));
            aWandererD = aWandererD + (((RotL64(aScatter, 19U) + aOrbiterB) + RotL64(aOrbiterI, 37U)) + RotL64(aCarry, 19U));
            aWandererE = aWandererE ^ (((RotL64(aIngress, 11U) + RotL64(aOrbiterJ, 57U)) + aOrbiterB) + aPhaseGWandererUpdateSaltA[(((31U - aIndex) + 19U)) & S_SALT1]);
            //
            aCarry = aCarry + (aWandererB ^ RotL64(aWandererF, 11U));
            aCarry = aCarry + (aWandererE ^ RotL64(aWandererD, 22U));
            aCarry = aCarry + (aWandererK ^ RotL64(aWandererA, 39U));
            aCarry = aCarry + RotL64(aWandererC, 47U);
            aCarry = aCarry + RotL64(aIngress, 3U);
            aCarry = TwistMix64::DiffuseB(aCarry);
            //
            aExpandLaneA[aIndex] = aIngress;
        }
    
        // seed_loop_a loop 10
        // ingress from: aExpandLaneA, aKeyRowReadA, aWorkLaneD, aWorkLaneB
        // ingress directions: aExpandLaneA forward forced, aKeyRowReadA forward forced, aWorkLaneD forward forced, aWorkLaneB forward/backward random
        // cross from: aKeyRowReadB, mSource, aWorkLaneC, aFireLaneD
        // cross directions: aKeyRowReadB backward forced, mSource backward forced, aWorkLaneC backward forced, aFireLaneD backward/forward random
        // write to: aExpandLaneB
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aExpandLaneA[((aIndex + 26379U)) & S_BLOCK1], 29U) ^ RotL64(aKeyRowReadA[((aIndex + 25027U)) & W_KEY1], 4U));
            aIngress ^= (RotL64(aWorkLaneD[((aIndex + 25220U)) & S_BLOCK1], 39U) ^ RotL64(aWorkLaneB[((aIndex + 25962U)) & S_BLOCK1], 47U));
            aIngress = TwistMix64::DiffuseC(((aIngress ^ aPhaseHDomainWordIngress) ^ aNonceWordB));
            //
            aCross = (RotL64(aKeyRowReadB[(((2047U - aIndex) + 25428U)) & W_KEY1], 5U) ^ RotL64(mSource[((S_BLOCK1 - aIndex + 26150U)) & S_BLOCK1], 54U));
            aCross ^= (RotL64(aWorkLaneC[((S_BLOCK1 - aIndex + 25125U)) & S_BLOCK1], 13U) ^ RotL64(aFireLaneD[((S_BLOCK1 - aIndex + 24655U)) & S_BLOCK1], 39U));
            aCross = TwistMix64::DiffuseC(((aCross ^ aPhaseHDomainWordCross) ^ aNonceWordA));
            //
            aScatter = (RotL64(aCarry, 41U) + RotL64(aPrevious, 60U)) ^ (RotL64(aIngress, 11U) + RotL64(aCross, 23U));
            aScatter = TwistMix64::DiffuseC(((aScatter ^ aPhaseHDomainWordScatter) ^ aNonceWordM));
            //
            aOrbiterH = (aWandererC + RotL64(aPrevious, 23U)) + 11480359716598965890U;
            aOrbiterD = (((aWandererG + RotL64(aCross, 30U)) + RotL64(aCarry, 47U)) + 15431182525482873419U) + aNonceWordI;
            aOrbiterE = (((aWandererJ + RotL64(aIngress, 11U)) + RotL64(aCarry, 5U)) + 11360504974812776707U) + aNonceWordD;
            aOrbiterA = (aWandererA + RotL64(aScatter, 39U)) + 9292576416573382769U;
            aOrbiterB = ((aWandererI + RotL64(aIngress, 5U)) + 1549257414531028975U) + aPhaseHOrbiterAssignSaltF[(((31U - aIndex) + 15U)) & S_SALT1];
            aOrbiterI = (((aWandererD + RotL64(aPrevious, 47U)) + RotL64(aCarry, 21U)) + 5347769463033129317U) + aNonceWordO;
            aOrbiterC = ((aWandererB + RotL64(aScatter, 57U)) + 17019199177478377234U) + aPhaseHOrbiterAssignSaltE[(((31U - aIndex) + 6U)) & S_SALT1];
            //
            aOrbiterH = ((aOrbiterH + aOrbiterD) + 16558106007323125094U) + aPhaseHOrbiterUpdateSaltB[(((31U - aIndex) + 8U)) & S_SALT1];
            aOrbiterE = (aOrbiterE ^ aOrbiterH) ^ 3976182233825939422U;
            aOrbiterE = RotL64((aOrbiterE * 4392162052317572289U), 35U);
            //
            aOrbiterA = (aOrbiterA + aOrbiterB) + 2889047161195954395U;
            aOrbiterI = ((aOrbiterI ^ aOrbiterA) ^ 2241831345026962605U) ^ aPhaseHOrbiterUpdateSaltF[((aIndex + 12U)) & S_SALT1];
            aOrbiterI = RotL64((aOrbiterI * 5757458560979927857U), 43U);
            //
            aOrbiterI = (aOrbiterI + aOrbiterH) + 12850802412140579294U;
            aOrbiterD = (aOrbiterD ^ aOrbiterI) ^ 13541744735436450160U;
            aOrbiterD = RotL64((aOrbiterD * 906089290000537439U), 51U);
            //
            aOrbiterE = (aOrbiterE + aOrbiterC) + 2085863085516538212U;
            aOrbiterA = ((aOrbiterA ^ aOrbiterE) ^ 2969034221711544086U) ^ aPhaseHOrbiterUpdateSaltA[((aIndex + 29U)) & S_SALT1];
            aOrbiterA = RotL64((aOrbiterA * 7768528124408400403U), 13U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterE) + 6482666944512391472U;
            aOrbiterC = (aOrbiterC ^ aOrbiterD) ^ 16969153556875844613U;
            aOrbiterC = RotL64((aOrbiterC * 9483462388353216219U), 3U);
            //
            aOrbiterB = ((aOrbiterB + aOrbiterI) + 5161314086757363678U) + aNonceWordF;
            aOrbiterH = ((aOrbiterH ^ aOrbiterB) ^ 7150282484670673211U) ^ aPhaseHOrbiterUpdateSaltD[(((31U - aIndex) + 3U)) & S_SALT1];
            aOrbiterH = RotL64((aOrbiterH * 8522427002337918663U), 29U);
            //
            aOrbiterC = ((aOrbiterC + aOrbiterA) + 5465304381272305847U) + aNonceWordH;
            aOrbiterB = (aOrbiterB ^ aOrbiterC) ^ 2344610773390354017U;
            aOrbiterB = RotL64((aOrbiterB * 17010258514288089191U), 19U);
            //
            aIngress = RotL64(aOrbiterD, 60U) ^ aOrbiterC;
            aIngress = aIngress + (RotL64(aOrbiterB, 29U) ^ aOrbiterA);
            aIngress = aIngress + (aOrbiterE ^ RotL64(aOrbiterI, 19U));
            aIngress = aIngress + RotL64(aOrbiterH, 53U);
            aIngress = TwistMix64::DiffuseB((aIngress + aScatter));
            //
            aWandererD = aWandererD ^ ((RotL64(aScatter, 51U) + RotL64(aOrbiterH, 47U)) + aOrbiterE);
            aWandererA = aWandererA + (((RotL64(aPrevious, 57U) + aOrbiterC) + RotL64(aOrbiterE, 58U)) + RotL64(aCarry, 39U));
            aWandererG = aWandererG ^ (((RotL64(aCross, 13U) + aOrbiterA) + RotL64(aOrbiterC, 3U)) + aNonceWordL);
            aWandererJ = aWandererJ + (((RotL64(aIngress, 28U) + aOrbiterD) + RotL64(aOrbiterH, 27U)) + aPhaseHWandererUpdateSaltC[(((31U - aIndex) + 19U)) & S_SALT1]);
            aWandererI = aWandererI ^ (((RotL64(aCross, 39U) + RotL64(aOrbiterC, 21U)) + aOrbiterD) + aNonceWordC);
            aWandererB = aWandererB + (((RotL64(aIngress, 5U) + aOrbiterD) + RotL64(aOrbiterI, 41U)) + RotL64(aCarry, 3U));
            aWandererC = aWandererC ^ (((RotL64(aPrevious, 21U) + aOrbiterA) + RotL64(aOrbiterB, 11U)) + aPhaseHWandererUpdateSaltD[(((31U - aIndex) + 17U)) & S_SALT1]);
            //
            aCarry = aCarry + (RotL64(aWandererD, 29U) ^ aWandererB);
            aCarry = aCarry + (aWandererI ^ RotL64(aWandererA, 56U));
            aCarry = aCarry + (aWandererC ^ RotL64(aWandererG, 39U));
            aCarry = aCarry + RotL64(aWandererJ, 43U);
            aCarry = aCarry + RotL64(aIngress, 5U);
            aCarry = TwistMix64::DiffuseB(aCarry);
            //
            aExpandLaneB[S_BLOCK1 - aIndex] = aIngress;
        }
    
        // seed_loop_a loop 11
        // ingress from: aExpandLaneB, aWorkLaneD, aKeyRowReadB, aWorkLaneC
        // ingress directions: aExpandLaneB forward forced, aWorkLaneD forward forced, aKeyRowReadB forward forced, aWorkLaneC forward/backward random
        // cross from: aKeyRowReadA, mSource, aExpandLaneA, aWorkLaneB
        // cross directions: aKeyRowReadA backward forced, mSource backward forced, aExpandLaneA backward forced, aWorkLaneB backward/forward random
        // write to: aExpandLaneC
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aExpandLaneB[((aIndex + 27618U)) & S_BLOCK1], 30U) ^ RotL64(aWorkLaneD[((aIndex + 27782U)) & S_BLOCK1], 41U));
            aIngress ^= (RotL64(aKeyRowReadB[((aIndex + 27976U)) & W_KEY1], 19U) ^ RotL64(aWorkLaneC[((aIndex + 27755U)) & S_BLOCK1], 3U));
            aIngress = TwistMix64::DiffuseC(((aIngress ^ aPhaseHDomainWordIngress) ^ aNonceWordA));
            //
            aCross = (RotL64(aKeyRowReadA[(((2047U - aIndex) + 29259U)) & W_KEY1], 35U) ^ RotL64(mSource[((S_BLOCK1 - aIndex + 28464U)) & S_BLOCK1], 46U));
            aCross ^= (RotL64(aExpandLaneA[((S_BLOCK1 - aIndex + 27579U)) & S_BLOCK1], 27U) ^ RotL64(aWorkLaneB[((aIndex + 27955U)) & S_BLOCK1], 57U));
            aCross = TwistMix64::DiffuseB(((aCross ^ aPhaseHDomainWordCross) ^ aNonceWordG));
            //
            aScatter = (RotL64(aPrevious, 35U) + RotL64(aCarry, 47U)) ^ (RotL64(aCross, 18U) + RotL64(aIngress, 5U));
            aScatter = TwistMix64::DiffuseC(((aScatter ^ aPhaseHDomainWordScatter) ^ aNonceWordI));
            //
            aOrbiterF = ((aWandererA + RotL64(aIngress, 14U)) + RotL64(aCarry, 19U)) + 11450949896247900941U;
            aOrbiterB = (aWandererF + RotL64(aScatter, 53U)) + 3905542253538116335U;
            aOrbiterK = ((aWandererI + RotL64(aPrevious, 27U)) + 9529740545977785305U) + aNonceWordL;
            aOrbiterG = (((aWandererH + RotL64(aCross, 37U)) + RotL64(aCarry, 3U)) + 1856876631533143492U) + aNonceWordE;
            aOrbiterI = ((aWandererE + RotL64(aIngress, 43U)) + 84253466320181686U) + aPhaseHOrbiterAssignSaltA[((aIndex + 17U)) & S_SALT1];
            aOrbiterH = ((aWandererJ + RotL64(aPrevious, 21U)) + RotL64(aCarry, 53U)) + 12577480918745432444U;
            aOrbiterC = (((aWandererK + RotL64(aScatter, 3U)) + 5625703170397704029U) + aPhaseHOrbiterAssignSaltE[((aIndex + 21U)) & S_SALT1]) + aNonceWordC;
            //
            aOrbiterF = (aOrbiterF + aOrbiterB) + 694608607323629282U;
            aOrbiterK = (aOrbiterK ^ aOrbiterF) ^ 3993981243536262204U;
            aOrbiterK = RotL64((aOrbiterK * 2502835860198146381U), 5U);
            //
            aOrbiterG = (aOrbiterG + aOrbiterI) + 4119215953484892051U;
            aOrbiterF = (aOrbiterF ^ aOrbiterG) ^ 8785040118556157146U;
            aOrbiterF = RotL64((aOrbiterF * 17113521266125471625U), 27U);
            //
            aOrbiterH = (aOrbiterH + aOrbiterF) + 16234403619456882890U;
            aOrbiterC = (aOrbiterC ^ aOrbiterH) ^ 10398727475672860610U;
            aOrbiterC = RotL64((aOrbiterC * 5086871400049644715U), 11U);
            //
            aOrbiterK = ((aOrbiterK + aOrbiterG) + 18327987141759096769U) + aNonceWordD;
            aOrbiterH = ((aOrbiterH ^ aOrbiterK) ^ 2645964788056875452U) ^ aPhaseHOrbiterUpdateSaltA[(((31U - aIndex) + 11U)) & S_SALT1];
            aOrbiterH = RotL64((aOrbiterH * 8778681366114628045U), 21U);
            //
            aOrbiterC = (((aOrbiterC + aOrbiterK) + 2859452497983106129U) + aPhaseHOrbiterUpdateSaltF[((aIndex + 27U)) & S_SALT1]) + aNonceWordO;
            aOrbiterI = ((aOrbiterI ^ aOrbiterC) ^ 7196557924940881076U) ^ aPhaseHOrbiterUpdateSaltD[((aIndex + 7U)) & S_SALT1];
            aOrbiterI = RotL64((aOrbiterI * 14415389907490256711U), 53U);
            //
            aOrbiterI = (aOrbiterI + aOrbiterH) + 930127943984174668U;
            aOrbiterB = (aOrbiterB ^ aOrbiterI) ^ 15673596916054795749U;
            aOrbiterB = RotL64((aOrbiterB * 7505660488733199479U), 41U);
            //
            aOrbiterB = ((aOrbiterB + aOrbiterC) + 16673140529110941163U) + aPhaseHOrbiterUpdateSaltB[((aIndex + 19U)) & S_SALT1];
            aOrbiterG = ((aOrbiterG ^ aOrbiterB) ^ 2258448294877833760U) ^ aNonceWordM;
            aOrbiterG = RotL64((aOrbiterG * 1821550319748977445U), 47U);
            //
            aIngress = aOrbiterI ^ RotL64(aOrbiterH, 27U);
            aIngress = aIngress + (aOrbiterF ^ RotL64(aOrbiterK, 5U));
            aIngress = aIngress + (RotL64(aOrbiterB, 21U) ^ aOrbiterG);
            aIngress = aIngress + RotL64(aOrbiterC, 52U);
            aIngress = TwistMix64::DiffuseC((aIngress + aScatter));
            //
            aWandererK = aWandererK + (((RotL64(aIngress, 11U) + RotL64(aOrbiterC, 21U)) + aOrbiterI) + RotL64(aCarry, 39U));
            aWandererJ = aWandererJ ^ ((RotL64(aScatter, 51U) + aOrbiterB) + RotL64(aOrbiterC, 13U));
            aWandererH = aWandererH + (((RotL64(aPrevious, 43U) + RotL64(aOrbiterK, 5U)) + aOrbiterG) + RotL64(aCarry, 27U));
            aWandererA = aWandererA ^ (((RotL64(aCross, 34U) + aOrbiterF) + RotL64(aOrbiterK, 43U)) + aNonceWordF);
            aWandererI = aWandererI + (((RotL64(aIngress, 5U) + aOrbiterF) + RotL64(aOrbiterH, 36U)) + aPhaseHWandererUpdateSaltE[(((31U - aIndex) + 26U)) & S_SALT1]);
            aWandererE = aWandererE ^ ((RotL64(aPrevious, 23U) + RotL64(aOrbiterF, 27U)) + aOrbiterG);
            aWandererF = aWandererF + ((((RotL64(aScatter, 57U) + aOrbiterB) + RotL64(aOrbiterI, 57U)) + aNonceWordH) + aPhaseHWandererUpdateSaltA[((aIndex + 12U)) & S_SALT1]);
            //
            aCarry = aCarry + (aWandererJ ^ RotL64(aWandererF, 22U));
            aCarry = aCarry + (aWandererA ^ RotL64(aWandererH, 37U));
            aCarry = aCarry + (RotL64(aWandererE, 3U) ^ aWandererK);
            aCarry = aCarry + RotL64(aWandererI, 11U);
            aCarry = aCarry + RotL64(aIngress, 51U);
            aCarry = TwistMix64::DiffuseB(aCarry);
            //
            aExpandLaneC[aIndex] = aIngress;
        }
    
        // seed_loop_a loop 12
        // ingress from: aExpandLaneC, aKeyRowReadA
        // ingress directions: aExpandLaneC forward forced, aKeyRowReadA forward/backward random
        // cross from: aWorkLaneD, aExpandLaneA, aExpandLaneB, aKeyRowReadB
        // cross directions: aWorkLaneD backward forced, aExpandLaneA backward forced, aExpandLaneB backward forced, aKeyRowReadB backward/forward random
        // write to: aExpandLaneD
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = RotL64(aExpandLaneC[((aIndex + 32729U)) & S_BLOCK1], 11U) ^ RotL64(aKeyRowReadA[((aIndex + 31096U)) & W_KEY1], 30U);
            aIngress = TwistMix64::DiffuseB(((aIngress ^ aPhaseHDomainWordIngress) ^ aNonceWordH));
            //
            aCross = (RotL64(aWorkLaneD[((S_BLOCK1 - aIndex + 30414U)) & S_BLOCK1], 13U) ^ RotL64(aExpandLaneA[((S_BLOCK1 - aIndex + 31537U)) & S_BLOCK1], 5U));
            aCross ^= (RotL64(aExpandLaneB[((S_BLOCK1 - aIndex + 30442U)) & S_BLOCK1], 35U) ^ RotL64(aKeyRowReadB[((aIndex + 30973U)) & W_KEY1], 50U));
            aCross = TwistMix64::DiffuseB(((aCross ^ aPhaseHDomainWordCross) ^ aNonceWordJ));
            //
            aScatter = (RotL64(aCross, 39U) ^ RotL64(aIngress, 26U)) + (RotL64(aCarry, 53U) ^ RotL64(aPrevious, 3U));
            aScatter = TwistMix64::DiffuseA(((aScatter ^ aPhaseHDomainWordScatter) ^ aNonceWordC));
            //
            aOrbiterJ = ((aWandererH + RotL64(aIngress, 6U)) + RotL64(aCarry, 5U)) + 7960325128608297381U;
            aOrbiterI = ((aWandererE + RotL64(aPrevious, 23U)) + 12773836012104052042U) + aNonceWordG;
            aOrbiterB = (((aWandererA + RotL64(aScatter, 35U)) + RotL64(aCarry, 21U)) + 3173972621347773016U) + aNonceWordF;
            aOrbiterF = (((aWandererI + RotL64(aCross, 47U)) + RotL64(aCarry, 51U)) + 3708401356314308171U) + aPhaseHOrbiterAssignSaltC[(((31U - aIndex) + 17U)) & S_SALT1];
            aOrbiterA = (aWandererC + RotL64(aScatter, 29U)) + 950774285720019449U;
            aOrbiterE = ((aWandererF + RotL64(aIngress, 53U)) + 4170092315705438265U) + aNonceWordN;
            aOrbiterD = ((aWandererB + RotL64(aPrevious, 13U)) + 17000449130864980747U) + aPhaseHOrbiterAssignSaltB[(((31U - aIndex) + 4U)) & S_SALT1];
            //
            aOrbiterJ = ((aOrbiterJ + aOrbiterI) + 8793910540062893860U) + aNonceWordP;
            aOrbiterB = (aOrbiterB ^ aOrbiterJ) ^ 520277969543516469U;
            aOrbiterB = RotL64((aOrbiterB * 4150613128885828229U), 27U);
            //
            aOrbiterF = ((aOrbiterF + aOrbiterB) + 12762214857389827271U) + aPhaseHOrbiterUpdateSaltA[((aIndex + 7U)) & S_SALT1];
            aOrbiterA = (aOrbiterA ^ aOrbiterF) ^ 2932451184340207695U;
            aOrbiterA = RotL64((aOrbiterA * 7513337346940091655U), 57U);
            //
            aOrbiterE = ((aOrbiterE + aOrbiterJ) + 11062179998786293839U) + aNonceWordI;
            aOrbiterF = (aOrbiterF ^ aOrbiterE) ^ 7919119215271524178U;
            aOrbiterF = RotL64((aOrbiterF * 9053677007180081359U), 47U);
            //
            aOrbiterI = (aOrbiterI + aOrbiterA) + 1774988449597115155U;
            aOrbiterE = (aOrbiterE ^ aOrbiterI) ^ 3799792889466518953U;
            aOrbiterE = RotL64((aOrbiterE * 17512791286490623455U), 5U);
            //
            aOrbiterA = (aOrbiterA + aOrbiterD) + 1815062051307896589U;
            aOrbiterJ = (aOrbiterJ ^ aOrbiterA) ^ 15260373951371654483U;
            aOrbiterJ = RotL64((aOrbiterJ * 2208604434669491625U), 39U);
            //
            aOrbiterD = (((aOrbiterD + aOrbiterF) + 12867546628945676853U) + aPhaseHOrbiterUpdateSaltE[((aIndex + 20U)) & S_SALT1]) + aNonceWordM;
            aOrbiterI = ((aOrbiterI ^ aOrbiterD) ^ 7772820973895846946U) ^ aPhaseHOrbiterUpdateSaltB[((aIndex + 5U)) & S_SALT1];
            aOrbiterI = RotL64((aOrbiterI * 7581704643538761985U), 13U);
            //
            aOrbiterB = (aOrbiterB + aOrbiterE) + 14213957831821966834U;
            aOrbiterD = ((aOrbiterD ^ aOrbiterB) ^ 16561105721170419454U) ^ aPhaseHOrbiterUpdateSaltD[(((31U - aIndex) + 9U)) & S_SALT1];
            aOrbiterD = RotL64((aOrbiterD * 2540533987337175367U), 21U);
            //
            aIngress = aOrbiterB ^ RotL64(aOrbiterE, 11U);
            aIngress = aIngress + (RotL64(aOrbiterI, 5U) ^ aOrbiterJ);
            aIngress = aIngress + (RotL64(aOrbiterF, 34U) ^ aOrbiterD);
            aIngress = aIngress + RotL64(aOrbiterA, 57U);
            aIngress = TwistMix64::DiffuseA((aIngress + aScatter));
            //
            aWandererA = aWandererA ^ ((RotL64(aPrevious, 57U) + RotL64(aOrbiterB, 5U)) + aOrbiterJ);
            aWandererF = aWandererF + (((RotL64(aScatter, 37U) + aOrbiterD) + RotL64(aOrbiterA, 53U)) + RotL64(aCarry, 47U));
            aWandererB = aWandererB ^ ((RotL64(aIngress, 5U) + aOrbiterI) + RotL64(aOrbiterF, 47U));
            aWandererE = aWandererE + ((((RotL64(aCross, 48U) + RotL64(aOrbiterF, 19U)) + aOrbiterE) + RotL64(aCarry, 35U)) + aPhaseHWandererUpdateSaltA[((aIndex + 8U)) & S_SALT1]);
            aWandererI = aWandererI ^ ((((RotL64(aIngress, 23U) + aOrbiterI) + RotL64(aOrbiterA, 41U)) + aNonceWordD) + aPhaseHWandererUpdateSaltB[((aIndex + 14U)) & S_SALT1]);
            aWandererH = aWandererH + ((RotL64(aCross, 29U) + aOrbiterA) + RotL64(aOrbiterJ, 60U));
            aWandererC = aWandererC ^ (((RotL64(aScatter, 11U) + aOrbiterF) + RotL64(aOrbiterA, 35U)) + aNonceWordE);
            //
            aCarry = aCarry + (aWandererI ^ RotL64(aWandererH, 29U));
            aCarry = aCarry + (RotL64(aWandererB, 46U) ^ aWandererE);
            aCarry = aCarry + (aWandererF ^ RotL64(aWandererA, 19U));
            aCarry = aCarry + RotL64(aWandererC, 57U);
            aCarry = aCarry + RotL64(aIngress, 39U);
            aCarry = TwistMix64::DiffuseC(aCarry);
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

void TwistExpander_Greezy_Arx::Seed_B(TwistWorkSpace *pWorkSpace,
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
    std::uint64_t aNonceWordA = TwistMix64::DiffuseC(pNonce * 0x911144081773C539ULL + 0xE1A68880B286CE09ULL);
    std::uint64_t aNonceWordB = TwistMix64::DiffuseB(pNonce * 0xA02BA1760D727741ULL + 0xE6A8592154F7CF94ULL);
    std::uint64_t aNonceWordC = TwistMix64::DiffuseC(pNonce * 0xF4F301846B549C7DULL + 0xB323C40F42A54053ULL);
    std::uint64_t aNonceWordD = TwistMix64::DiffuseB(pNonce * 0xED47E041AE23A93DULL + 0x84A71A931AF52969ULL);
    std::uint64_t aNonceWordE = TwistMix64::DiffuseB(pNonce * 0x9168F2F07F9522BDULL + 0xE2C779A75C7121A3ULL);
    std::uint64_t aNonceWordF = TwistMix64::DiffuseB(pNonce * 0x8DC14857641C32FDULL + 0xE45B17B817FDD68EULL);
    std::uint64_t aNonceWordG = TwistMix64::DiffuseC(pNonce * 0xC0EFFE8ADE001E03ULL + 0xBF65BE90C7057731ULL);
    std::uint64_t aNonceWordH = TwistMix64::DiffuseC(pNonce * 0xBD7A9E3954A41953ULL + 0xB7075726D7E9B408ULL);
    std::uint64_t aNonceWordI = TwistMix64::DiffuseA(pNonce * 0xF8BE0CD4F50BFE4FULL + 0xA4268C97E5E03AB6ULL);
    std::uint64_t aNonceWordJ = TwistMix64::DiffuseB(pNonce * 0x8006F0E142D45301ULL + 0xFA5C7459782DCCBCULL);
    std::uint64_t aNonceWordK = TwistMix64::DiffuseA(pNonce * 0xD65D474C90573283ULL + 0x8842F1907677A48DULL);
    std::uint64_t aNonceWordL = TwistMix64::DiffuseA(pNonce * 0xA18E161C737E8187ULL + 0xCA00EC52CC1492CAULL);
    std::uint64_t aNonceWordM = TwistMix64::DiffuseC(pNonce * 0xBB857D9B39826835ULL + 0xF553DDCD30405BC2ULL);
    std::uint64_t aNonceWordN = TwistMix64::DiffuseB(pNonce * 0xDE25E61A3CBEA3A1ULL + 0x8E490C10D17DA2E2ULL);
    std::uint64_t aNonceWordO = TwistMix64::DiffuseA(pNonce * 0x9E29BEA70B64EAA3ULL + 0x975AF2A52AF5A714ULL);
    std::uint64_t aNonceWordP = TwistMix64::DiffuseA(pNonce * 0xA5B695D1E4F28E79ULL + 0xC113C00CD910489EULL);
    // GSeedRunSeed_B seed_loop_a (start)
    {
        // GSeedRunSeed_B seed_loop_a lane group
        // read from: aExpandLaneA, aExpandLaneB, aFireLaneA, aExpandLaneC, aExpandLaneD, aFireLaneB, aInvestLaneA, aFireLaneC, aFireLaneD, aInvestLaneB, aWorkLaneA, aOperationLaneA, aWorkLaneB, aOperationLaneB, aWorkLaneC, aOperationLaneC, aWorkLaneD
        // write to: aInvestLaneA, aInvestLaneB, aOperationLaneA, aOperationLaneB, aOperationLaneC, aOperationLaneD
    
        // seed_loop_a loop 1
        // ingress from: aExpandLaneA, aExpandLaneB, aFireLaneA
        // ingress directions: aExpandLaneA forward forced, aExpandLaneB forward forced, aFireLaneA forward/backward random
        // cross from: aExpandLaneC, aExpandLaneD, aFireLaneB
        // cross directions: aExpandLaneC backward forced, aExpandLaneD backward forced, aFireLaneB backward/forward random
        // write to: aInvestLaneA
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aExpandLaneA[((aIndex + 780U)) & S_BLOCK1], 26U) ^ RotL64(aExpandLaneB[((aIndex + 3343U)) & S_BLOCK1], 39U));
            aIngress ^= RotL64(aFireLaneA[((S_BLOCK1 - aIndex + 2240U)) & S_BLOCK1], 3U);
            aIngress = TwistMix64::DiffuseA(((aIngress ^ aPhaseADomainWordIngress) ^ aNonceWordH));
            //
            aCross = (RotL64(aExpandLaneC[((S_BLOCK1 - aIndex + 1334U)) & S_BLOCK1], 12U) ^ RotL64(aExpandLaneD[((S_BLOCK1 - aIndex + 3627U)) & S_BLOCK1], 53U));
            aCross ^= RotL64(aFireLaneB[((aIndex + 5280U)) & S_BLOCK1], 35U);
            aCross = TwistMix64::DiffuseC(((aCross ^ aPhaseADomainWordCross) ^ aNonceWordN));
            //
            aScatter = (RotL64(aCarry, 4U) + RotL64(aPrevious, 37U)) ^ (RotL64(aIngress, 23U) + RotL64(aCross, 51U));
            aScatter = TwistMix64::DiffuseC(((aScatter ^ aPhaseADomainWordScatter) ^ aNonceWordB));
            //
            aOrbiterA = (((aWandererK + RotL64(aIngress, 39U)) + RotL64(aCarry, 47U)) + 14157904117287696136U) + aNonceWordB;
            aOrbiterI = ((((aWandererB + RotL64(aCross, 56U)) + RotL64(aCarry, 27U)) + 7369512677371640676U) + aPhaseAOrbiterAssignSaltA[((aIndex + 23U)) & S_SALT1]) + aNonceWordI;
            aOrbiterE = ((aWandererD + RotL64(aScatter, 5U)) + 8411250745902073798U) + aPhaseAOrbiterAssignSaltF[(((31U - aIndex) + 8U)) & S_SALT1];
            aOrbiterB = (((aWandererJ + RotL64(aPrevious, 19U)) + RotL64(aCarry, 5U)) + 5002041814539710275U) + aNonceWordJ;
            aOrbiterH = ((aWandererH + RotL64(aIngress, 27U)) + 9538041410816283124U) + aNonceWordA;
            //
            aOrbiterA = (aOrbiterA + aOrbiterI) + 5210700103927513061U;
            aOrbiterE = (((aOrbiterE ^ aOrbiterA) ^ 7600709399101287982U) ^ aPhaseAOrbiterUpdateSaltF[((aIndex + 29U)) & S_SALT1]) ^ aNonceWordO;
            aOrbiterE = RotL64((aOrbiterE * 6777896926889560889U), 11U);
            //
            aOrbiterE = (aOrbiterE + aOrbiterB) + 2366369466696580499U;
            aOrbiterH = ((aOrbiterH ^ aOrbiterE) ^ 5544575244203019109U) ^ aNonceWordD;
            aOrbiterH = RotL64((aOrbiterH * 16231219246786333057U), 3U);
            //
            aOrbiterI = (aOrbiterI + aOrbiterE) + 8710073749110329779U;
            aOrbiterB = (((aOrbiterB ^ aOrbiterI) ^ 15998211310115361630U) ^ aPhaseAOrbiterUpdateSaltE[(((31U - aIndex) + 27U)) & S_SALT1]) ^ aNonceWordE;
            aOrbiterB = RotL64((aOrbiterB * 15275657696897688955U), 39U);
            //
            aOrbiterH = ((aOrbiterH + aOrbiterA) + 15354357553877376422U) + aNonceWordG;
            aOrbiterI = ((aOrbiterI ^ aOrbiterH) ^ 10657523549259276169U) ^ aPhaseAOrbiterUpdateSaltC[((aIndex + 9U)) & S_SALT1];
            aOrbiterI = RotL64((aOrbiterI * 13695239532898311073U), 29U);
            //
            aOrbiterB = (aOrbiterB + aOrbiterH) + 10405750198355464768U;
            aOrbiterA = ((aOrbiterA ^ aOrbiterB) ^ 3465819693133515142U) ^ aPhaseAOrbiterUpdateSaltB[((aIndex + 3U)) & S_SALT1];
            aOrbiterA = RotL64((aOrbiterA * 14678343718277562799U), 57U);
            //
            aIngress = aOrbiterE ^ RotL64(aOrbiterH, 41U);
            aIngress = aIngress + (RotL64(aOrbiterI, 3U) ^ aOrbiterB);
            aIngress = aIngress + RotL64(aOrbiterA, 29U);
            aIngress = TwistMix64::DiffuseC((aIngress + aScatter));
            //
            aWandererK = aWandererK ^ (((RotL64(aScatter, 27U) + RotL64(aOrbiterH, 13U)) + aOrbiterA) + aNonceWordK);
            aWandererH = aWandererH + (((((RotL64(aPrevious, 11U) + RotL64(aOrbiterA, 4U)) + aOrbiterB) + RotL64(aCarry, 53U)) + aNonceWordP) + aPhaseAWandererUpdateSaltB[((aIndex + 26U)) & S_SALT1]);
            aWandererB = aWandererB ^ (((RotL64(aCross, 19U) + aOrbiterE) + RotL64(aOrbiterH, 35U)) + aNonceWordL);
            aWandererJ = aWandererJ + ((((RotL64(aIngress, 54U) + aOrbiterB) + RotL64(aOrbiterI, 47U)) + RotL64(aCarry, 39U)) + aPhaseAWandererUpdateSaltE[((aIndex + 5U)) & S_SALT1]);
            aWandererD = aWandererD ^ (((RotL64(aScatter, 41U) + aOrbiterH) + RotL64(aOrbiterI, 27U)) + aNonceWordC);
            //
            aCarry = aCarry + (aWandererH ^ RotL64(aWandererD, 47U));
            aCarry = aCarry + (aWandererK ^ RotL64(aWandererB, 56U));
            aCarry = aCarry + RotL64(aWandererJ, 27U);
            aCarry = aCarry + RotL64(aIngress, 19U);
            aCarry = TwistMix64::DiffuseA(aCarry);
            //
            aInvestLaneA[aIndex] = aIngress;
        }
    
        // seed_loop_a loop 2
        // ingress from: aInvestLaneA, aExpandLaneC, aExpandLaneD, aFireLaneC
        // ingress directions: aInvestLaneA forward forced, aExpandLaneC forward forced, aExpandLaneD forward forced, aFireLaneC forward/backward random
        // cross from: aExpandLaneA, aExpandLaneB, aFireLaneD
        // cross directions: aExpandLaneA backward forced, aExpandLaneB backward forced, aFireLaneD backward/forward random
        // write to: aInvestLaneB
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aInvestLaneA[((aIndex + 10605U)) & S_BLOCK1], 43U) ^ RotL64(aExpandLaneC[((aIndex + 8374U)) & S_BLOCK1], 19U));
            aIngress ^= (RotL64(aExpandLaneD[((aIndex + 8760U)) & S_BLOCK1], 58U) ^ RotL64(aFireLaneC[((aIndex + 8125U)) & S_BLOCK1], 5U));
            aIngress = TwistMix64::DiffuseB(((aIngress ^ aPhaseADomainWordIngress) ^ aNonceWordF));
            //
            aCross = (RotL64(aExpandLaneA[((S_BLOCK1 - aIndex + 8161U)) & S_BLOCK1], 57U) ^ RotL64(aExpandLaneB[((S_BLOCK1 - aIndex + 10708U)) & S_BLOCK1], 43U));
            aCross ^= RotL64(aFireLaneD[((S_BLOCK1 - aIndex + 6987U)) & S_BLOCK1], 4U);
            aCross = TwistMix64::DiffuseA(((aCross ^ aPhaseADomainWordCross) ^ aNonceWordD));
            //
            aScatter = (RotL64(aCross, 23U) ^ RotL64(aPrevious, 53U)) + (RotL64(aCarry, 3U) + RotL64(aIngress, 40U));
            aScatter = TwistMix64::DiffuseC(((aScatter ^ aPhaseADomainWordScatter) ^ aNonceWordD));
            //
            aOrbiterI = (((aWandererB + RotL64(aScatter, 29U)) + RotL64(aCarry, 37U)) + 18180797995100240808U) + aPhaseAOrbiterAssignSaltD[((aIndex + 9U)) & S_SALT1];
            aOrbiterG = ((aWandererC + RotL64(aIngress, 21U)) + 6585906608223552885U) + aNonceWordK;
            aOrbiterD = ((((aWandererI + RotL64(aPrevious, 11U)) + RotL64(aCarry, 23U)) + 14088708930575939855U) + aPhaseAOrbiterAssignSaltE[((aIndex + 20U)) & S_SALT1]) + aNonceWordI;
            aOrbiterK = ((aWandererA + RotL64(aCross, 39U)) + RotL64(aCarry, 3U)) + 468974153311516044U;
            aOrbiterF = ((aWandererK + RotL64(aIngress, 50U)) + 12481951025619894110U) + aNonceWordB;
            //
            aOrbiterI = ((aOrbiterI + aOrbiterG) + 17227987923860711763U) + aNonceWordP;
            aOrbiterD = ((aOrbiterD ^ aOrbiterI) ^ 4373962756657477139U) ^ aNonceWordA;
            aOrbiterD = RotL64((aOrbiterD * 6069068316234356267U), 39U);
            //
            aOrbiterD = ((aOrbiterD + aOrbiterK) + 2077576476565420951U) + aPhaseAOrbiterUpdateSaltF[((aIndex + 11U)) & S_SALT1];
            aOrbiterG = (aOrbiterG ^ aOrbiterD) ^ 17435011300234663764U;
            aOrbiterG = RotL64((aOrbiterG * 8910133867294004711U), 47U);
            //
            aOrbiterK = (((aOrbiterK + aOrbiterI) + 4118039398293246896U) + aPhaseAOrbiterUpdateSaltB[((aIndex + 4U)) & S_SALT1]) + aNonceWordG;
            aOrbiterF = ((aOrbiterF ^ aOrbiterK) ^ 13724716599855216683U) ^ aPhaseAOrbiterUpdateSaltD[(((31U - aIndex) + 19U)) & S_SALT1];
            aOrbiterF = RotL64((aOrbiterF * 17556333902751079677U), 3U);
            //
            aOrbiterG = (aOrbiterG + aOrbiterF) + 12391461204689596339U;
            aOrbiterK = ((aOrbiterK ^ aOrbiterG) ^ 9900605191533799627U) ^ aPhaseAOrbiterUpdateSaltA[((aIndex + 7U)) & S_SALT1];
            aOrbiterK = RotL64((aOrbiterK * 13553565332531046301U), 11U);
            //
            aOrbiterF = ((aOrbiterF + aOrbiterD) + 972946858824366125U) + aNonceWordH;
            aOrbiterI = (aOrbiterI ^ aOrbiterF) ^ 17247681919694541215U;
            aOrbiterI = RotL64((aOrbiterI * 2974639094630445643U), 57U);
            //
            aIngress = aOrbiterG ^ RotL64(aOrbiterI, 13U);
            aIngress = aIngress + (aOrbiterK ^ RotL64(aOrbiterF, 29U));
            aIngress = aIngress + RotL64(aOrbiterD, 51U);
            aIngress = TwistMix64::DiffuseC((aIngress + aScatter));
            //
            aWandererK = aWandererK + (((RotL64(aCross, 41U) + RotL64(aOrbiterF, 21U)) + aOrbiterD) + RotL64(aCarry, 51U));
            aWandererI = aWandererI ^ (((RotL64(aIngress, 21U) + RotL64(aOrbiterK, 3U)) + aOrbiterF) + aNonceWordM);
            aWandererA = aWandererA + (((RotL64(aPrevious, 3U) + RotL64(aOrbiterI, 58U)) + aOrbiterG) + aNonceWordL);
            aWandererB = aWandererB ^ ((((RotL64(aScatter, 30U) + aOrbiterK) + RotL64(aOrbiterD, 11U)) + aNonceWordJ) + aPhaseAWandererUpdateSaltC[(((31U - aIndex) + 27U)) & S_SALT1]);
            aWandererC = aWandererC + (((((RotL64(aIngress, 13U) + RotL64(aOrbiterK, 41U)) + aOrbiterI) + RotL64(aCarry, 13U)) + aNonceWordC) + aPhaseAWandererUpdateSaltD[((aIndex + 8U)) & S_SALT1]);
            //
            aCarry = aCarry + (RotL64(aWandererB, 21U) ^ aWandererC);
            aCarry = aCarry + (RotL64(aWandererI, 47U) ^ aWandererA);
            aCarry = aCarry + RotL64(aWandererK, 29U);
            aCarry = aCarry + RotL64(aIngress, 38U);
            aCarry = TwistMix64::DiffuseC(aCarry);
            //
            aInvestLaneB[S_BLOCK1 - aIndex] = aIngress;
        }
    
        // seed_loop_a loop 3
        // ingress from: aInvestLaneB, aExpandLaneA, aWorkLaneA
        // ingress directions: aInvestLaneB forward forced, aExpandLaneA forward forced, aWorkLaneA forward/backward random
        // cross from: aInvestLaneA, aExpandLaneC
        // cross directions: aInvestLaneA backward forced, aExpandLaneC backward/forward random
        // write to: aOperationLaneA
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aInvestLaneB[((aIndex + 10940U)) & S_BLOCK1], 27U) ^ RotL64(aExpandLaneA[((aIndex + 14107U)) & S_BLOCK1], 10U));
            aIngress ^= RotL64(aWorkLaneA[((S_BLOCK1 - aIndex + 13171U)) & S_BLOCK1], 53U);
            aIngress = TwistMix64::DiffuseB(((aIngress ^ aPhaseADomainWordIngress) ^ aNonceWordE));
            //
            aCross = RotL64(aInvestLaneA[((S_BLOCK1 - aIndex + 13553U)) & S_BLOCK1], 11U) ^ RotL64(aExpandLaneC[((S_BLOCK1 - aIndex + 14620U)) & S_BLOCK1], 39U);
            aCross = TwistMix64::DiffuseB(((aCross ^ aPhaseADomainWordCross) ^ aNonceWordL));
            //
            aScatter = (RotL64(aCross, 4U) ^ RotL64(aPrevious, 41U)) + (RotL64(aCarry, 29U) ^ RotL64(aIngress, 53U));
            aScatter = TwistMix64::DiffuseA(((aScatter ^ aPhaseADomainWordScatter) ^ aNonceWordI));
            //
            aOrbiterC = (((aWandererI + RotL64(aIngress, 57U)) + RotL64(aCarry, 23U)) + 15383045568644941552U) + aNonceWordF;
            aOrbiterH = (((aWandererE + RotL64(aPrevious, 13U)) + 17452811657750910067U) + aPhaseAOrbiterAssignSaltB[(((31U - aIndex) + 17U)) & S_SALT1]) + aNonceWordK;
            aOrbiterJ = (((aWandererD + RotL64(aScatter, 47U)) + RotL64(aCarry, 35U)) + 15660117718455155603U) + aNonceWordD;
            aOrbiterF = (((aWandererJ + RotL64(aCross, 29U)) + RotL64(aCarry, 5U)) + 10396441207743665753U) + aPhaseAOrbiterAssignSaltC[(((31U - aIndex) + 27U)) & S_SALT1];
            aOrbiterG = ((aWandererA + RotL64(aScatter, 38U)) + 3708971058200841442U) + aNonceWordO;
            //
            aOrbiterC = (aOrbiterC + aOrbiterH) + 7000673057768598750U;
            aOrbiterJ = (aOrbiterJ ^ aOrbiterC) ^ 9886354469011131596U;
            aOrbiterJ = RotL64((aOrbiterJ * 296615166652808759U), 5U);
            //
            aOrbiterF = ((aOrbiterF + aOrbiterC) + 16018065329058043467U) + aNonceWordJ;
            aOrbiterH = ((aOrbiterH ^ aOrbiterF) ^ 5024756166109352320U) ^ aNonceWordG;
            aOrbiterH = RotL64((aOrbiterH * 11660932185479046483U), 35U);
            //
            aOrbiterH = ((aOrbiterH + aOrbiterJ) + 6587818720728886652U) + aPhaseAOrbiterUpdateSaltF[((aIndex + 11U)) & S_SALT1];
            aOrbiterG = ((aOrbiterG ^ aOrbiterH) ^ 3652672354944162319U) ^ aPhaseAOrbiterUpdateSaltD[(((31U - aIndex) + 20U)) & S_SALT1];
            aOrbiterG = RotL64((aOrbiterG * 10807121230791716109U), 57U);
            //
            aOrbiterJ = (((aOrbiterJ + aOrbiterG) + 6307315649915348048U) + aPhaseAOrbiterUpdateSaltC[((aIndex + 14U)) & S_SALT1]) + aNonceWordH;
            aOrbiterF = (aOrbiterF ^ aOrbiterJ) ^ 16405347331742979258U;
            aOrbiterF = RotL64((aOrbiterF * 7183142442906743699U), 27U);
            //
            aOrbiterG = (((aOrbiterG + aOrbiterF) + 5427299664054601957U) + aPhaseAOrbiterUpdateSaltE[((aIndex + 16U)) & S_SALT1]) + aNonceWordA;
            aOrbiterC = (aOrbiterC ^ aOrbiterG) ^ 4983381733483185898U;
            aOrbiterC = RotL64((aOrbiterC * 14646556236306407673U), 13U);
            //
            aIngress = RotL64(aOrbiterF, 3U) ^ aOrbiterH;
            aIngress = aIngress + (RotL64(aOrbiterG, 13U) ^ aOrbiterC);
            aIngress = aIngress + RotL64(aOrbiterJ, 29U);
            aIngress = TwistMix64::DiffuseC((aIngress + aScatter));
            //
            aWandererJ = aWandererJ + ((((RotL64(aIngress, 3U) + RotL64(aOrbiterC, 35U)) + aOrbiterH) + RotL64(aCarry, 23U)) + aNonceWordP);
            aWandererI = aWandererI ^ (((RotL64(aCross, 22U) + aOrbiterF) + RotL64(aOrbiterJ, 5U)) + aPhaseAWandererUpdateSaltA[(((31U - aIndex) + 25U)) & S_SALT1]);
            aWandererD = aWandererD + ((((RotL64(aPrevious, 47U) + aOrbiterJ) + RotL64(aOrbiterH, 56U)) + aNonceWordI) + aPhaseAWandererUpdateSaltF[(((31U - aIndex) + 12U)) & S_SALT1]);
            aWandererE = aWandererE ^ (((RotL64(aScatter, 35U) + aOrbiterH) + RotL64(aOrbiterG, 43U)) + aNonceWordM);
            aWandererA = aWandererA + ((((RotL64(aPrevious, 11U) + RotL64(aOrbiterG, 21U)) + aOrbiterJ) + RotL64(aCarry, 57U)) + aNonceWordB);
            //
            aCarry = aCarry + (aWandererI ^ RotL64(aWandererE, 43U));
            aCarry = aCarry + (aWandererA ^ RotL64(aWandererD, 3U));
            aCarry = aCarry + RotL64(aWandererJ, 11U);
            aCarry = aCarry + RotL64(aIngress, 20U);
            aCarry = TwistMix64::DiffuseA(aCarry);
            //
            aOperationLaneA[aIndex] = aIngress;
        }
    
        // seed_loop_a loop 4
        // ingress from: aOperationLaneA, aInvestLaneA, aWorkLaneB
        // ingress directions: aOperationLaneA forward forced, aInvestLaneA forward forced, aWorkLaneB forward/backward random
        // cross from: aInvestLaneB, aExpandLaneD
        // cross directions: aInvestLaneB backward forced, aExpandLaneD backward/forward random
        // write to: aOperationLaneB
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aOperationLaneA[((aIndex + 20390U)) & S_BLOCK1], 53U) ^ RotL64(aInvestLaneA[((aIndex + 20360U)) & S_BLOCK1], 10U));
            aIngress ^= RotL64(aWorkLaneB[((aIndex + 17247U)) & S_BLOCK1], 27U);
            aIngress = TwistMix64::DiffuseA(((aIngress ^ aPhaseADomainWordIngress) ^ aNonceWordL));
            //
            aCross = RotL64(aInvestLaneB[((S_BLOCK1 - aIndex + 16770U)) & S_BLOCK1], 11U) ^ RotL64(aExpandLaneD[((aIndex + 18989U)) & S_BLOCK1], 60U);
            aCross = TwistMix64::DiffuseA(((aCross ^ aPhaseADomainWordCross) ^ aNonceWordK));
            //
            aScatter = (RotL64(aCarry, 53U) + RotL64(aPrevious, 12U)) + (RotL64(aCross, 27U) ^ RotL64(aIngress, 41U));
            aScatter = TwistMix64::DiffuseA(((aScatter ^ aPhaseADomainWordScatter) ^ aNonceWordG));
            //
            aOrbiterE = (((aWandererI + RotL64(aPrevious, 21U)) + RotL64(aCarry, 23U)) + 6361545377408870615U) + aNonceWordG;
            aOrbiterB = ((aWandererB + RotL64(aIngress, 43U)) + RotL64(aCarry, 3U)) + 2967245486744774933U;
            aOrbiterJ = (((aWandererD + RotL64(aScatter, 35U)) + RotL64(aCarry, 47U)) + 3836634268482850139U) + aPhaseAOrbiterAssignSaltF[((aIndex + 4U)) & S_SALT1];
            aOrbiterF = ((aWandererJ + RotL64(aCross, 3U)) + 7691642115360086297U) + aNonceWordH;
            aOrbiterD = ((aWandererF + RotL64(aPrevious, 54U)) + 16479280384178279281U) + aPhaseAOrbiterAssignSaltA[(((31U - aIndex) + 26U)) & S_SALT1];
            //
            aOrbiterE = ((aOrbiterE + aOrbiterB) + 2901468732552539249U) + aNonceWordF;
            aOrbiterJ = ((aOrbiterJ ^ aOrbiterE) ^ 2600353867755647475U) ^ aPhaseAOrbiterUpdateSaltF[((aIndex + 3U)) & S_SALT1];
            aOrbiterJ = RotL64((aOrbiterJ * 1140827276372862433U), 57U);
            //
            aOrbiterB = (aOrbiterB + aOrbiterJ) + 5666596904781510956U;
            aOrbiterF = (aOrbiterF ^ aOrbiterB) ^ 16108791609267427553U;
            aOrbiterF = RotL64((aOrbiterF * 8904649663479834199U), 27U);
            //
            aOrbiterF = ((aOrbiterF + aOrbiterD) + 8389926875737312112U) + aPhaseAOrbiterUpdateSaltE[(((31U - aIndex) + 29U)) & S_SALT1];
            aOrbiterE = ((aOrbiterE ^ aOrbiterF) ^ 1689501721163024426U) ^ aPhaseAOrbiterUpdateSaltC[((aIndex + 7U)) & S_SALT1];
            aOrbiterE = RotL64((aOrbiterE * 6517194895779049139U), 19U);
            //
            aOrbiterD = ((aOrbiterD + aOrbiterE) + 11721701506949917719U) + aNonceWordB;
            aOrbiterB = (aOrbiterB ^ aOrbiterD) ^ 3963842745030140473U;
            aOrbiterB = RotL64((aOrbiterB * 6692473494944919373U), 47U);
            //
            aOrbiterJ = ((aOrbiterJ + aOrbiterF) + 8510538243472109368U) + aNonceWordP;
            aOrbiterD = (((aOrbiterD ^ aOrbiterJ) ^ 18281865214102080387U) ^ aPhaseAOrbiterUpdateSaltA[((aIndex + 5U)) & S_SALT1]) ^ aNonceWordI;
            aOrbiterD = RotL64((aOrbiterD * 1351546966368884609U), 3U);
            //
            aIngress = aOrbiterF ^ RotL64(aOrbiterD, 50U);
            aIngress = aIngress + (RotL64(aOrbiterE, 5U) ^ aOrbiterJ);
            aIngress = aIngress + RotL64(aOrbiterB, 39U);
            aIngress = TwistMix64::DiffuseC((aIngress + aScatter));
            //
            aWandererD = aWandererD ^ ((RotL64(aCross, 21U) + aOrbiterJ) + RotL64(aOrbiterB, 42U));
            aWandererB = aWandererB + ((((RotL64(aPrevious, 39U) + aOrbiterJ) + RotL64(aOrbiterF, 53U)) + RotL64(aCarry, 27U)) + aPhaseAWandererUpdateSaltB[((aIndex + 13U)) & S_SALT1]);
            aWandererI = aWandererI ^ (((RotL64(aIngress, 53U) + aOrbiterE) + RotL64(aOrbiterJ, 3U)) + aNonceWordC);
            aWandererF = aWandererF + (((((RotL64(aScatter, 5U) + aOrbiterD) + RotL64(aOrbiterF, 19U)) + RotL64(aCarry, 39U)) + aNonceWordA) + aPhaseAWandererUpdateSaltE[((aIndex + 16U)) & S_SALT1]);
            aWandererJ = aWandererJ ^ (((RotL64(aPrevious, 30U) + aOrbiterE) + RotL64(aOrbiterF, 29U)) + aNonceWordE);
            //
            aCarry = aCarry + (RotL64(aWandererJ, 3U) ^ aWandererF);
            aCarry = aCarry + (aWandererI ^ RotL64(aWandererB, 29U));
            aCarry = aCarry + RotL64(aWandererD, 13U);
            aCarry = aCarry + RotL64(aIngress, 47U);
            aCarry = TwistMix64::DiffuseB(aCarry);
            //
            aOperationLaneB[S_BLOCK1 - aIndex] = aIngress;
        }
    
        // seed_loop_a loop 5
        // ingress from: aOperationLaneB, aInvestLaneB, aWorkLaneC
        // ingress directions: aOperationLaneB forward forced, aInvestLaneB forward forced, aWorkLaneC forward/backward random
        // cross from: aOperationLaneA, aInvestLaneA
        // cross directions: aOperationLaneA backward forced, aInvestLaneA backward/forward random
        // write to: aOperationLaneC
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aOperationLaneB[((aIndex + 23831U)) & S_BLOCK1], 43U) ^ RotL64(aInvestLaneB[((aIndex + 24749U)) & S_BLOCK1], 3U));
            aIngress ^= RotL64(aWorkLaneC[((aIndex + 25363U)) & S_BLOCK1], 11U);
            aIngress = TwistMix64::DiffuseB(((aIngress ^ aPhaseADomainWordIngress) ^ aNonceWordN));
            //
            aCross = RotL64(aOperationLaneA[((S_BLOCK1 - aIndex + 23350U)) & S_BLOCK1], 29U) ^ RotL64(aInvestLaneA[((aIndex + 25529U)) & S_BLOCK1], 58U);
            aCross = TwistMix64::DiffuseC(((aCross ^ aPhaseADomainWordCross) ^ aNonceWordH));
            //
            aScatter = (RotL64(aCarry, 43U) ^ RotL64(aIngress, 11U)) ^ (RotL64(aPrevious, 60U) + RotL64(aCross, 23U));
            aScatter = TwistMix64::DiffuseB(((aScatter ^ aPhaseADomainWordScatter) ^ aNonceWordA));
            //
            aOrbiterD = ((aWandererJ + RotL64(aCross, 57U)) + 6381335981879993247U) + aNonceWordJ;
            aOrbiterC = (((aWandererC + RotL64(aPrevious, 19U)) + RotL64(aCarry, 47U)) + 15595429101600023172U) + aNonceWordC;
            aOrbiterB = (((aWandererI + RotL64(aIngress, 39U)) + RotL64(aCarry, 3U)) + 5449234297249826461U) + aPhaseAOrbiterAssignSaltD[(((31U - aIndex) + 3U)) & S_SALT1];
            aOrbiterJ = (((aWandererD + RotL64(aScatter, 3U)) + RotL64(aCarry, 29U)) + 11213734849329731168U) + aPhaseAOrbiterAssignSaltE[((aIndex + 15U)) & S_SALT1];
            aOrbiterF = ((aWandererE + RotL64(aCross, 28U)) + 16438473952464514248U) + aNonceWordO;
            //
            aOrbiterD = ((aOrbiterD + aOrbiterC) + 7357872882115186976U) + aPhaseAOrbiterUpdateSaltF[(((31U - aIndex) + 29U)) & S_SALT1];
            aOrbiterB = ((aOrbiterB ^ aOrbiterD) ^ 394402075160738643U) ^ aPhaseAOrbiterUpdateSaltB[((aIndex + 28U)) & S_SALT1];
            aOrbiterB = RotL64((aOrbiterB * 11961225338735982661U), 29U);
            //
            aOrbiterJ = (aOrbiterJ + aOrbiterD) + 11112941985410283532U;
            aOrbiterF = (aOrbiterF ^ aOrbiterJ) ^ 14955125011182736212U;
            aOrbiterF = RotL64((aOrbiterF * 10711684773326395603U), 37U);
            //
            aOrbiterC = ((aOrbiterC + aOrbiterF) + 14770727009821304070U) + aNonceWordK;
            aOrbiterJ = (aOrbiterJ ^ aOrbiterC) ^ 11286366598129204910U;
            aOrbiterJ = RotL64((aOrbiterJ * 15884310771003021989U), 47U);
            //
            aOrbiterB = (((aOrbiterB + aOrbiterJ) + 7358400908565425780U) + aPhaseAOrbiterUpdateSaltC[(((31U - aIndex) + 20U)) & S_SALT1]) + aNonceWordM;
            aOrbiterC = (aOrbiterC ^ aOrbiterB) ^ 15635109923749114761U;
            aOrbiterC = RotL64((aOrbiterC * 12415152149408700329U), 21U);
            //
            aOrbiterF = ((aOrbiterF + aOrbiterB) + 13826842523738623579U) + aPhaseAOrbiterUpdateSaltE[(((31U - aIndex) + 27U)) & S_SALT1];
            aOrbiterD = (aOrbiterD ^ aOrbiterF) ^ 1072811298828325231U;
            aOrbiterD = RotL64((aOrbiterD * 9662800288646215083U), 57U);
            //
            aIngress = aOrbiterF ^ RotL64(aOrbiterB, 6U);
            aIngress = aIngress + (aOrbiterC ^ RotL64(aOrbiterD, 57U));
            aIngress = aIngress + RotL64(aOrbiterJ, 21U);
            aIngress = TwistMix64::DiffuseA((aIngress + aScatter));
            //
            aWandererE = aWandererE + ((RotL64(aIngress, 29U) + RotL64(aOrbiterB, 43U)) + aOrbiterJ);
            aWandererI = aWandererI ^ ((RotL64(aCross, 11U) + RotL64(aOrbiterF, 60U)) + aOrbiterC);
            aWandererJ = aWandererJ + (((((RotL64(aScatter, 42U) + RotL64(aOrbiterF, 11U)) + aOrbiterJ) + RotL64(aCarry, 29U)) + aNonceWordF) + aPhaseAWandererUpdateSaltC[(((31U - aIndex) + 5U)) & S_SALT1]);
            aWandererC = aWandererC ^ (((RotL64(aPrevious, 3U) + RotL64(aOrbiterD, 19U)) + aOrbiterC) + aPhaseAWandererUpdateSaltD[(((31U - aIndex) + 24U)) & S_SALT1]);
            aWandererD = aWandererD + ((((RotL64(aIngress, 53U) + RotL64(aOrbiterD, 51U)) + aOrbiterJ) + RotL64(aCarry, 53U)) + aNonceWordB);
            //
            aCarry = aCarry + (RotL64(aWandererD, 3U) ^ aWandererE);
            aCarry = aCarry + (RotL64(aWandererJ, 11U) ^ aWandererC);
            aCarry = aCarry + RotL64(aWandererI, 47U);
            aCarry = aCarry + RotL64(aIngress, 24U);
            aCarry = TwistMix64::DiffuseB(aCarry);
            //
            aOperationLaneC[aIndex] = aIngress;
        }
    
        // seed_loop_a loop 6
        // ingress from: aOperationLaneC, aOperationLaneA, aWorkLaneD
        // ingress directions: aOperationLaneC forward forced, aOperationLaneA forward forced, aWorkLaneD forward/backward random
        // cross from: aOperationLaneB, aExpandLaneB
        // cross directions: aOperationLaneB backward forced, aExpandLaneB backward/forward random
        // write to: aOperationLaneD
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aOperationLaneC[((aIndex + 28668U)) & S_BLOCK1], 57U) ^ RotL64(aOperationLaneA[((aIndex + 32091U)) & S_BLOCK1], 27U));
            aIngress ^= RotL64(aWorkLaneD[((S_BLOCK1 - aIndex + 27538U)) & S_BLOCK1], 13U);
            aIngress = TwistMix64::DiffuseA(((aIngress ^ aPhaseADomainWordIngress) ^ aNonceWordM));
            //
            aCross = RotL64(aOperationLaneB[((S_BLOCK1 - aIndex + 31892U)) & S_BLOCK1], 53U) ^ RotL64(aExpandLaneB[((S_BLOCK1 - aIndex + 29998U)) & S_BLOCK1], 37U);
            aCross = TwistMix64::DiffuseC(((aCross ^ aPhaseADomainWordCross) ^ aNonceWordB));
            //
            aScatter = (RotL64(aPrevious, 39U) + RotL64(aCarry, 21U)) ^ (RotL64(aIngress, 54U) ^ RotL64(aCross, 5U));
            aScatter = TwistMix64::DiffuseA(((aScatter ^ aPhaseADomainWordScatter) ^ aNonceWordM));
            //
            aOrbiterI = (((aWandererI + RotL64(aIngress, 11U)) + 9220392006207660113U) + aPhaseAOrbiterAssignSaltB[((aIndex + 12U)) & S_SALT1]) + aNonceWordJ;
            aOrbiterG = ((((aWandererE + RotL64(aCross, 39U)) + RotL64(aCarry, 23U)) + 11305018553489132882U) + aPhaseAOrbiterAssignSaltC[((aIndex + 24U)) & S_SALT1]) + aNonceWordO;
            aOrbiterH = ((aWandererH + RotL64(aPrevious, 57U)) + RotL64(aCarry, 11U)) + 5860373868073513684U;
            aOrbiterD = (((aWandererF + RotL64(aScatter, 3U)) + RotL64(aCarry, 43U)) + 12319586170883987589U) + aNonceWordI;
            aOrbiterE = ((aWandererK + RotL64(aPrevious, 26U)) + 14072333614354649021U) + aNonceWordA;
            //
            aOrbiterI = ((aOrbiterI + aOrbiterG) + 9332158529453194608U) + aPhaseAOrbiterUpdateSaltD[(((31U - aIndex) + 25U)) & S_SALT1];
            aOrbiterH = ((aOrbiterH ^ aOrbiterI) ^ 3860569321145958686U) ^ aNonceWordK;
            aOrbiterH = RotL64((aOrbiterH * 907977527866467591U), 47U);
            //
            aOrbiterG = (aOrbiterG + aOrbiterH) + 8119005668901240093U;
            aOrbiterD = (aOrbiterD ^ aOrbiterG) ^ 13918259792880333239U;
            aOrbiterD = RotL64((aOrbiterD * 5441062406822088853U), 11U);
            //
            aOrbiterH = (aOrbiterH + aOrbiterD) + 6938856216758228704U;
            aOrbiterE = ((aOrbiterE ^ aOrbiterH) ^ 3960905839118710604U) ^ aPhaseAOrbiterUpdateSaltF[((aIndex + 21U)) & S_SALT1];
            aOrbiterE = RotL64((aOrbiterE * 16203746868670689793U), 21U);
            //
            aOrbiterD = (((aOrbiterD + aOrbiterE) + 6043879193734253929U) + aPhaseAOrbiterUpdateSaltC[(((31U - aIndex) + 11U)) & S_SALT1]) + aNonceWordH;
            aOrbiterI = (aOrbiterI ^ aOrbiterD) ^ 15691425268831319195U;
            aOrbiterI = RotL64((aOrbiterI * 7189195135654636271U), 29U);
            //
            aOrbiterE = ((aOrbiterE + aOrbiterI) + 14912209933584715274U) + aPhaseAOrbiterUpdateSaltE[(((31U - aIndex) + 13U)) & S_SALT1];
            aOrbiterG = (aOrbiterG ^ aOrbiterE) ^ 16180183395910618923U;
            aOrbiterG = RotL64((aOrbiterG * 3942858974766467849U), 37U);
            //
            aIngress = RotL64(aOrbiterH, 26U) ^ aOrbiterI;
            aIngress = aIngress + (aOrbiterG ^ RotL64(aOrbiterD, 3U));
            aIngress = aIngress + RotL64(aOrbiterE, 13U);
            aIngress = TwistMix64::DiffuseC((aIngress + aScatter));
            //
            aWandererH = aWandererH + (((RotL64(aIngress, 51U) + aOrbiterI) + RotL64(aOrbiterD, 43U)) + aNonceWordG);
            aWandererI = aWandererI ^ (((RotL64(aScatter, 3U) + RotL64(aOrbiterG, 11U)) + aOrbiterE) + aNonceWordD);
            aWandererF = aWandererF + ((((RotL64(aCross, 29U) + RotL64(aOrbiterH, 58U)) + aOrbiterI) + RotL64(aCarry, 47U)) + aPhaseAWandererUpdateSaltA[((aIndex + 23U)) & S_SALT1]);
            aWandererK = aWandererK ^ (((RotL64(aPrevious, 41U) + aOrbiterE) + RotL64(aOrbiterD, 21U)) + aNonceWordP);
            aWandererE = aWandererE + ((((RotL64(aIngress, 14U) + aOrbiterI) + RotL64(aOrbiterE, 29U)) + RotL64(aCarry, 11U)) + aPhaseAWandererUpdateSaltF[((aIndex + 27U)) & S_SALT1]);
            //
            aCarry = aCarry + (RotL64(aWandererI, 47U) ^ aWandererH);
            aCarry = aCarry + (RotL64(aWandererF, 19U) ^ aWandererK);
            aCarry = aCarry + RotL64(aWandererE, 3U);
            aCarry = aCarry + RotL64(aIngress, 11U);
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

void TwistExpander_Greezy_Arx::Seed_C(TwistWorkSpace *pWorkSpace,
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
    std::uint64_t aNonceWordA = TwistMix64::DiffuseB(pNonce * 0x8F1373CA29B0E6E7ULL + 0xA59AA75F7BDC58FAULL);
    std::uint64_t aNonceWordB = TwistMix64::DiffuseB(pNonce * 0xBB57502DC2619E91ULL + 0x932E99A7A0CF7B2BULL);
    std::uint64_t aNonceWordC = TwistMix64::DiffuseB(pNonce * 0x897CD3CB4CCA3AE5ULL + 0x91679E3576392869ULL);
    std::uint64_t aNonceWordD = TwistMix64::DiffuseA(pNonce * 0xA2F4D8238A7BAEA7ULL + 0xAF10351D2A8CFA91ULL);
    std::uint64_t aNonceWordE = TwistMix64::DiffuseB(pNonce * 0xD31875F467CF8B0FULL + 0x8637278EF00CCE6BULL);
    std::uint64_t aNonceWordF = TwistMix64::DiffuseA(pNonce * 0xF806FEAEB61CE6FDULL + 0xEB66715970FD9384ULL);
    std::uint64_t aNonceWordG = TwistMix64::DiffuseB(pNonce * 0xA5E5B6C2FAAA4BABULL + 0x8ADCC98044A5D65FULL);
    std::uint64_t aNonceWordH = TwistMix64::DiffuseB(pNonce * 0xD063752A9069ABB9ULL + 0xE732F80A4ED56EE5ULL);
    std::uint64_t aNonceWordI = TwistMix64::DiffuseA(pNonce * 0x94EC0928F7EB7BB9ULL + 0xF61CC5E8A3614B1BULL);
    std::uint64_t aNonceWordJ = TwistMix64::DiffuseB(pNonce * 0xF464F5C5F2C635D1ULL + 0xD1162FB7C0BBD1B0ULL);
    std::uint64_t aNonceWordK = TwistMix64::DiffuseC(pNonce * 0xD89E569CEE69AB05ULL + 0xD8CF70328F6D0032ULL);
    std::uint64_t aNonceWordL = TwistMix64::DiffuseA(pNonce * 0xB26B1769BA5C6275ULL + 0xC589FAAEF5011B45ULL);
    std::uint64_t aNonceWordM = TwistMix64::DiffuseB(pNonce * 0x9F7FB2B017A8AE45ULL + 0xFC3006B83EB6E58CULL);
    std::uint64_t aNonceWordN = TwistMix64::DiffuseA(pNonce * 0xA5FEF5A69530E253ULL + 0xD6F6251B4F8E08A2ULL);
    std::uint64_t aNonceWordO = TwistMix64::DiffuseB(pNonce * 0x9A3A205BBCA7FE9FULL + 0xCCC18070FD02ECEBULL);
    std::uint64_t aNonceWordP = TwistMix64::DiffuseA(pNonce * 0x929364532EFB53D9ULL + 0xCA7489ADF3A82BF4ULL);
    // GSeedRunSeed_C seed_loop_b (start)
    {
        // GSeedRunSeed_C seed_loop_b lane group
        // read from: aOperationLaneA, aOperationLaneB, aFireLaneA, aOperationLaneC, aOperationLaneD, aFireLaneB, aWorkLaneA, aFireLaneC, aFireLaneD, aWorkLaneB, aExpandLaneA, aExpandLaneB, aWorkLaneC, aExpandLaneC, aExpandLaneD
        // write to: aWorkLaneA, aWorkLaneB, aWorkLaneC, aWorkLaneD
    
        // seed_loop_b loop 1
        // ingress from: aOperationLaneA, aOperationLaneB, aFireLaneA
        // ingress directions: aOperationLaneA forward forced, aOperationLaneB forward forced, aFireLaneA forward/backward random
        // cross from: aOperationLaneC, aOperationLaneD, aFireLaneB
        // cross directions: aOperationLaneC backward forced, aOperationLaneD backward forced, aFireLaneB backward/forward random
        // write to: aWorkLaneA
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aOperationLaneA[((aIndex + 5627U)) & S_BLOCK1], 23U) ^ RotL64(aOperationLaneB[((aIndex + 1872U)) & S_BLOCK1], 56U));
            aIngress ^= RotL64(aFireLaneA[((S_BLOCK1 - aIndex + 3129U)) & S_BLOCK1], 13U);
            aIngress = TwistMix64::DiffuseC(((aIngress ^ aPhaseBDomainWordIngress) ^ aNonceWordB));
            //
            aCross = (RotL64(aOperationLaneC[((S_BLOCK1 - aIndex + 2844U)) & S_BLOCK1], 13U) ^ RotL64(aOperationLaneD[((S_BLOCK1 - aIndex + 6751U)) & S_BLOCK1], 37U));
            aCross ^= RotL64(aFireLaneB[((aIndex + 4905U)) & S_BLOCK1], 28U);
            aCross = TwistMix64::DiffuseC(((aCross ^ aPhaseBDomainWordCross) ^ aNonceWordD));
            //
            aScatter = (RotL64(aCross, 11U) ^ RotL64(aPrevious, 53U)) ^ (RotL64(aIngress, 27U) + RotL64(aCarry, 40U));
            aScatter = TwistMix64::DiffuseC(((aScatter ^ aPhaseBDomainWordScatter) ^ aNonceWordE));
            //
            aOrbiterG = (((aWandererC + RotL64(aIngress, 47U)) + 15316464782468770057U) + aPhaseBOrbiterAssignSaltF[((aIndex + 13U)) & S_SALT1]) + aNonceWordH;
            aOrbiterE = (aWandererD + RotL64(aPrevious, 22U)) + 6642872057476351588U;
            aOrbiterH = (aWandererK + RotL64(aScatter, 27U)) + 660732654689529192U;
            aOrbiterC = ((aWandererJ + RotL64(aCross, 35U)) + RotL64(aCarry, 13U)) + 7235418086884000655U;
            aOrbiterB = (aWandererE + RotL64(aIngress, 11U)) + 14784518476694580493U;
            aOrbiterA = ((aWandererA + RotL64(aCross, 39U)) + 12222433977933449375U) + aPhaseBOrbiterAssignSaltB[(((31U - aIndex) + 6U)) & S_SALT1];
            aOrbiterK = (((aWandererG + RotL64(aScatter, 6U)) + RotL64(aCarry, 27U)) + 8573001207708329927U) + aNonceWordC;
            aOrbiterI = (((aWandererF + RotL64(aPrevious, 51U)) + RotL64(aCarry, 3U)) + 16035256260815013172U) + aNonceWordO;
            aOrbiterF = ((aWandererB + RotL64(aCross, 43U)) + 15767726974121910203U) + aNonceWordA;
            //
            aOrbiterG = (aOrbiterG + aOrbiterE) + 17712217935322939971U;
            aOrbiterH = ((aOrbiterH ^ aOrbiterG) ^ 13488963456923357159U) ^ aPhaseBOrbiterUpdateSaltE[((aIndex + 14U)) & S_SALT1];
            aOrbiterH = RotL64((aOrbiterH * 16785285630840310405U), 41U);
            //
            aOrbiterC = ((aOrbiterC + aOrbiterB) + 10222949131965611079U) + aNonceWordN;
            aOrbiterG = (aOrbiterG ^ aOrbiterC) ^ 1495561412321657209U;
            aOrbiterG = RotL64((aOrbiterG * 9706305581868526265U), 47U);
            //
            aOrbiterA = (aOrbiterA + aOrbiterH) + 16156530750584361434U;
            aOrbiterB = (((aOrbiterB ^ aOrbiterA) ^ 7773792489045606309U) ^ aPhaseBOrbiterUpdateSaltD[(((31U - aIndex) + 27U)) & S_SALT1]) ^ aNonceWordF;
            aOrbiterB = RotL64((aOrbiterB * 10730624207715601393U), 29U);
            //
            aOrbiterK = (aOrbiterK + aOrbiterG) + 11544578291333360613U;
            aOrbiterA = ((aOrbiterA ^ aOrbiterK) ^ 3665587867634242865U) ^ aNonceWordJ;
            aOrbiterA = RotL64((aOrbiterA * 4840528190844842595U), 35U);
            //
            aOrbiterE = (aOrbiterE + aOrbiterK) + 15248434984650998090U;
            aOrbiterI = (aOrbiterI ^ aOrbiterE) ^ 15487979645426567581U;
            aOrbiterI = RotL64((aOrbiterI * 10868107809356766183U), 11U);
            //
            aOrbiterH = (aOrbiterH + aOrbiterI) + 6972347795052712690U;
            aOrbiterF = (aOrbiterF ^ aOrbiterH) ^ 16074994810010431338U;
            aOrbiterF = RotL64((aOrbiterF * 1262655238856775853U), 51U);
            //
            aOrbiterB = ((aOrbiterB + aOrbiterF) + 16851139687900415292U) + aPhaseBOrbiterUpdateSaltF[((aIndex + 7U)) & S_SALT1];
            aOrbiterE = ((aOrbiterE ^ aOrbiterB) ^ 14630026837021552812U) ^ aPhaseBOrbiterUpdateSaltB[(((31U - aIndex) + 3U)) & S_SALT1];
            aOrbiterE = RotL64((aOrbiterE * 9577900853521254603U), 57U);
            //
            aOrbiterF = ((aOrbiterF + aOrbiterC) + 14236330619137368169U) + aNonceWordM;
            aOrbiterK = (aOrbiterK ^ aOrbiterF) ^ 17778707026111136216U;
            aOrbiterK = RotL64((aOrbiterK * 16239561893843454747U), 19U);
            //
            aOrbiterI = (aOrbiterI + aOrbiterA) + 9390961969105999083U;
            aOrbiterC = (aOrbiterC ^ aOrbiterI) ^ 1174881758316573228U;
            aOrbiterC = RotL64((aOrbiterC * 6602061268277529311U), 23U);
            //
            aIngress = aOrbiterA ^ RotL64(aOrbiterC, 34U);
            aIngress = aIngress + (RotL64(aOrbiterI, 19U) ^ aOrbiterE);
            aIngress = aIngress + (RotL64(aOrbiterF, 27U) ^ aOrbiterK);
            aIngress = aIngress + (RotL64(aOrbiterH, 47U) ^ aOrbiterB);
            aIngress = aIngress + RotL64(aOrbiterG, 5U);
            aIngress = TwistMix64::DiffuseB((aIngress + aScatter));
            //
            aWandererK = aWandererK + (((RotL64(aPrevious, 6U) + RotL64(aOrbiterB, 27U)) + aOrbiterA) + aPhaseBWandererUpdateSaltA[((aIndex + 17U)) & S_SALT1]);
            aWandererE = aWandererE ^ ((RotL64(aIngress, 23U) + RotL64(aOrbiterH, 5U)) + aOrbiterI);
            aWandererB = aWandererB + ((((RotL64(aCross, 11U) + RotL64(aOrbiterE, 35U)) + aOrbiterK) + RotL64(aCarry, 19U)) + aNonceWordE);
            aWandererC = aWandererC ^ ((RotL64(aScatter, 35U) + aOrbiterK) + RotL64(aOrbiterG, 46U));
            aWandererJ = aWandererJ + (((RotL64(aPrevious, 27U) + aOrbiterB) + RotL64(aOrbiterI, 19U)) + RotL64(aCarry, 41U));
            aWandererF = aWandererF ^ (((RotL64(aCross, 51U) + aOrbiterH) + RotL64(aOrbiterC, 53U)) + aNonceWordP);
            aWandererD = aWandererD + ((RotL64(aIngress, 57U) + RotL64(aOrbiterC, 57U)) + aOrbiterE);
            aWandererA = aWandererA ^ ((((RotL64(aScatter, 47U) + RotL64(aOrbiterH, 40U)) + aOrbiterG) + aNonceWordG) + aPhaseBWandererUpdateSaltD[(((31U - aIndex) + 29U)) & S_SALT1]);
            aWandererG = aWandererG + ((RotL64(aIngress, 42U) + RotL64(aOrbiterE, 11U)) + aOrbiterF);
            //
            aCarry = aCarry + (RotL64(aWandererB, 37U) ^ aWandererA);
            aCarry = aCarry + (aWandererJ ^ RotL64(aWandererD, 30U));
            aCarry = aCarry + (aWandererG ^ RotL64(aWandererC, 41U));
            aCarry = aCarry + (aWandererE ^ RotL64(aWandererF, 53U));
            aCarry = aCarry + RotL64(aWandererK, 27U);
            aCarry = aCarry + RotL64(aIngress, 5U);
            aCarry = TwistMix64::DiffuseB(aCarry);
            //
            aWorkLaneA[aIndex] = aIngress;
        }
    
        // seed_loop_b loop 2
        // ingress from: aWorkLaneA, aOperationLaneC, aOperationLaneD, aFireLaneC
        // ingress directions: aWorkLaneA forward forced, aOperationLaneC forward forced, aOperationLaneD forward forced, aFireLaneC forward/backward random
        // cross from: aOperationLaneA, aOperationLaneB, aFireLaneD
        // cross directions: aOperationLaneA backward forced, aOperationLaneB backward forced, aFireLaneD backward/forward random
        // write to: aWorkLaneB
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aWorkLaneA[((aIndex + 13535U)) & S_BLOCK1], 57U) ^ RotL64(aOperationLaneC[((aIndex + 14935U)) & S_BLOCK1], 47U));
            aIngress ^= (RotL64(aOperationLaneD[((aIndex + 8821U)) & S_BLOCK1], 19U) ^ RotL64(aFireLaneC[((S_BLOCK1 - aIndex + 8314U)) & S_BLOCK1], 38U));
            aIngress = TwistMix64::DiffuseB(((aIngress ^ aPhaseBDomainWordIngress) ^ aNonceWordL));
            //
            aCross = (RotL64(aOperationLaneA[((S_BLOCK1 - aIndex + 12821U)) & S_BLOCK1], 21U) ^ RotL64(aOperationLaneB[((S_BLOCK1 - aIndex + 10431U)) & S_BLOCK1], 51U));
            aCross ^= RotL64(aFireLaneD[((aIndex + 16226U)) & S_BLOCK1], 34U);
            aCross = TwistMix64::DiffuseB(((aCross ^ aPhaseBDomainWordCross) ^ aNonceWordI));
            //
            aScatter = (RotL64(aIngress, 6U) + RotL64(aCarry, 27U)) + (RotL64(aCross, 51U) ^ RotL64(aPrevious, 39U));
            aScatter = TwistMix64::DiffuseA(((aScatter ^ aPhaseBDomainWordScatter) ^ aNonceWordC));
            //
            aOrbiterK = (aWandererF + RotL64(aPrevious, 3U)) + 4634399531433127141U;
            aOrbiterJ = ((aWandererA + RotL64(aCross, 47U)) + 16961792729406903200U) + aNonceWordF;
            aOrbiterA = ((aWandererD + RotL64(aIngress, 42U)) + 4105280732301137738U) + aPhaseBOrbiterAssignSaltA[(((31U - aIndex) + 15U)) & S_SALT1];
            aOrbiterB = (((aWandererK + RotL64(aScatter, 57U)) + RotL64(aCarry, 39U)) + 15692013501147331191U) + aNonceWordD;
            aOrbiterG = (((aWandererE + RotL64(aCross, 19U)) + RotL64(aCarry, 29U)) + 1252216715968780587U) + aNonceWordM;
            aOrbiterI = (((aWandererJ + RotL64(aPrevious, 29U)) + RotL64(aCarry, 11U)) + 7958289043012473752U) + aPhaseBOrbiterAssignSaltC[((aIndex + 11U)) & S_SALT1];
            aOrbiterF = ((aWandererI + RotL64(aScatter, 36U)) + 6611577301818896615U) + aNonceWordA;
            aOrbiterD = (aWandererG + RotL64(aIngress, 23U)) + 8506226754305949140U;
            aOrbiterH = (aWandererB + RotL64(aCross, 11U)) + 3648813120449403353U;
            //
            aOrbiterK = (aOrbiterK + aOrbiterJ) + 5195245426245535735U;
            aOrbiterA = ((aOrbiterA ^ aOrbiterK) ^ 542948051600803051U) ^ aNonceWordN;
            aOrbiterA = RotL64((aOrbiterA * 4631106308856448475U), 5U);
            //
            aOrbiterA = (aOrbiterA + aOrbiterB) + 11974253551208964789U;
            aOrbiterG = ((aOrbiterG ^ aOrbiterA) ^ 10596463592332655367U) ^ aPhaseBOrbiterUpdateSaltC[((aIndex + 12U)) & S_SALT1];
            aOrbiterG = RotL64((aOrbiterG * 10941161258815714641U), 41U);
            //
            aOrbiterI = ((aOrbiterI + aOrbiterF) + 12015129484061440159U) + aPhaseBOrbiterUpdateSaltA[(((31U - aIndex) + 21U)) & S_SALT1];
            aOrbiterD = (aOrbiterD ^ aOrbiterI) ^ 8254944355710109060U;
            aOrbiterD = RotL64((aOrbiterD * 3233697992479357615U), 47U);
            //
            aOrbiterG = (aOrbiterG + aOrbiterI) + 2754858806943915419U;
            aOrbiterJ = (aOrbiterJ ^ aOrbiterG) ^ 5007802002906662779U;
            aOrbiterJ = RotL64((aOrbiterJ * 15613733948331639723U), 51U);
            //
            aOrbiterF = ((aOrbiterF + aOrbiterG) + 6262190752136523216U) + aNonceWordO;
            aOrbiterK = ((aOrbiterK ^ aOrbiterF) ^ 10528977986487821428U) ^ aNonceWordP;
            aOrbiterK = RotL64((aOrbiterK * 1184258264034585525U), 57U);
            //
            aOrbiterJ = ((aOrbiterJ + aOrbiterD) + 8511097226098211854U) + aPhaseBOrbiterUpdateSaltD[((aIndex + 5U)) & S_SALT1];
            aOrbiterB = ((aOrbiterB ^ aOrbiterJ) ^ 12091864735686692582U) ^ aNonceWordG;
            aOrbiterB = RotL64((aOrbiterB * 6128140528141411237U), 27U);
            //
            aOrbiterB = (aOrbiterB + aOrbiterH) + 4970966265236842566U;
            aOrbiterI = (aOrbiterI ^ aOrbiterB) ^ 10728884018459718341U;
            aOrbiterI = RotL64((aOrbiterI * 18205183219769602827U), 23U);
            //
            aOrbiterH = (aOrbiterH + aOrbiterA) + 13760057185629905360U;
            aOrbiterF = ((aOrbiterF ^ aOrbiterH) ^ 6590269178744829056U) ^ aPhaseBOrbiterUpdateSaltB[((aIndex + 14U)) & S_SALT1];
            aOrbiterF = RotL64((aOrbiterF * 14482684769712170123U), 13U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterK) + 765826377665103262U;
            aOrbiterH = (aOrbiterH ^ aOrbiterD) ^ 9364759196106579706U;
            aOrbiterH = RotL64((aOrbiterH * 10315111163659289329U), 19U);
            //
            aIngress = RotL64(aOrbiterH, 26U) ^ aOrbiterF;
            aIngress = aIngress + (aOrbiterD ^ RotL64(aOrbiterA, 57U));
            aIngress = aIngress + (aOrbiterK ^ RotL64(aOrbiterJ, 37U));
            aIngress = aIngress + (RotL64(aOrbiterG, 41U) ^ aOrbiterB);
            aIngress = aIngress + RotL64(aOrbiterI, 23U);
            aIngress = TwistMix64::DiffuseA((aIngress + aScatter));
            //
            aWandererD = aWandererD + ((((RotL64(aScatter, 47U) + RotL64(aOrbiterK, 47U)) + aOrbiterA) + RotL64(aCarry, 19U)) + aPhaseBWandererUpdateSaltE[((aIndex + 18U)) & S_SALT1]);
            aWandererI = aWandererI ^ (((RotL64(aIngress, 21U) + RotL64(aOrbiterG, 35U)) + aOrbiterH) + aPhaseBWandererUpdateSaltC[(((31U - aIndex) + 17U)) & S_SALT1]);
            aWandererK = aWandererK + ((((RotL64(aPrevious, 52U) + RotL64(aOrbiterJ, 40U)) + aOrbiterH) + RotL64(aCarry, 53U)) + aNonceWordJ);
            aWandererJ = aWandererJ ^ ((RotL64(aCross, 11U) + RotL64(aOrbiterD, 21U)) + aOrbiterG);
            aWandererG = aWandererG + ((RotL64(aIngress, 3U) + aOrbiterA) + RotL64(aOrbiterF, 5U));
            aWandererE = aWandererE ^ ((RotL64(aCross, 57U) + RotL64(aOrbiterI, 13U)) + aOrbiterD);
            aWandererF = aWandererF + ((RotL64(aPrevious, 39U) + RotL64(aOrbiterG, 56U)) + aOrbiterI);
            aWandererB = aWandererB ^ ((RotL64(aScatter, 35U) + aOrbiterG) + RotL64(aOrbiterA, 27U));
            aWandererA = aWandererA + (((RotL64(aIngress, 28U) + RotL64(aOrbiterJ, 51U)) + aOrbiterB) + aNonceWordK);
            //
            aCarry = aCarry + (RotL64(aWandererD, 23U) ^ aWandererF);
            aCarry = aCarry + (RotL64(aWandererI, 47U) ^ aWandererE);
            aCarry = aCarry + (aWandererK ^ RotL64(aWandererA, 3U));
            aCarry = aCarry + (RotL64(aWandererJ, 13U) ^ aWandererG);
            aCarry = aCarry + RotL64(aWandererB, 60U);
            aCarry = aCarry + RotL64(aIngress, 51U);
            aCarry = TwistMix64::DiffuseC(aCarry);
            //
            aWorkLaneB[S_BLOCK1 - aIndex] = aIngress;
        }
    
        // seed_loop_b loop 3
        // ingress from: aWorkLaneB, aOperationLaneA, aOperationLaneB, aExpandLaneA
        // ingress directions: aWorkLaneB forward forced, aOperationLaneA forward forced, aOperationLaneB forward forced, aExpandLaneA forward/backward random
        // cross from: aWorkLaneA, aOperationLaneC, aExpandLaneB
        // cross directions: aWorkLaneA backward forced, aOperationLaneC backward forced, aExpandLaneB backward/forward random
        // write to: aWorkLaneC
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aWorkLaneB[((aIndex + 19238U)) & S_BLOCK1], 35U) ^ RotL64(aOperationLaneA[((aIndex + 18428U)) & S_BLOCK1], 27U));
            aIngress ^= (RotL64(aOperationLaneB[((aIndex + 16468U)) & S_BLOCK1], 19U) ^ RotL64(aExpandLaneA[((aIndex + 19737U)) & S_BLOCK1], 5U));
            aIngress = TwistMix64::DiffuseA(((aIngress ^ aPhaseBDomainWordIngress) ^ aNonceWordI));
            //
            aCross = (RotL64(aWorkLaneA[((S_BLOCK1 - aIndex + 21945U)) & S_BLOCK1], 51U) ^ RotL64(aOperationLaneC[((S_BLOCK1 - aIndex + 16779U)) & S_BLOCK1], 14U));
            aCross ^= RotL64(aExpandLaneB[((S_BLOCK1 - aIndex + 24083U)) & S_BLOCK1], 5U);
            aCross = TwistMix64::DiffuseC(((aCross ^ aPhaseBDomainWordCross) ^ aNonceWordL));
            //
            aScatter = (RotL64(aIngress, 39U) ^ RotL64(aCross, 23U)) + (RotL64(aPrevious, 3U) ^ RotL64(aCarry, 54U));
            aScatter = TwistMix64::DiffuseB(((aScatter ^ aPhaseBDomainWordScatter) ^ aNonceWordK));
            //
            aOrbiterE = (aWandererC + RotL64(aScatter, 51U)) + 14249093584376402677U;
            aOrbiterK = (((aWandererK + RotL64(aIngress, 56U)) + 8756965951816492264U) + aPhaseBOrbiterAssignSaltD[((aIndex + 9U)) & S_SALT1]) + aNonceWordD;
            aOrbiterJ = (aWandererE + RotL64(aPrevious, 11U)) + 11221139480258176330U;
            aOrbiterG = ((aWandererJ + RotL64(aCross, 43U)) + 17218894445564194851U) + aNonceWordK;
            aOrbiterA = (((aWandererI + RotL64(aScatter, 39U)) + RotL64(aCarry, 19U)) + 8064642692524949490U) + aNonceWordM;
            aOrbiterH = (((aWandererA + RotL64(aCross, 47U)) + RotL64(aCarry, 39U)) + 5822093203710704646U) + aPhaseBOrbiterAssignSaltE[((aIndex + 27U)) & S_SALT1];
            aOrbiterC = (aWandererH + RotL64(aPrevious, 23U)) + 3217799620158102238U;
            aOrbiterI = ((aWandererD + RotL64(aIngress, 5U)) + 2613757677892120843U) + aNonceWordP;
            aOrbiterB = ((aWandererG + RotL64(aPrevious, 30U)) + RotL64(aCarry, 57U)) + 13647481499551657237U;
            //
            aOrbiterE = (((aOrbiterE + aOrbiterK) + 3545714196663685016U) + aPhaseBOrbiterUpdateSaltA[(((31U - aIndex) + 13U)) & S_SALT1]) + aNonceWordC;
            aOrbiterJ = (aOrbiterJ ^ aOrbiterE) ^ 9735422670576621521U;
            aOrbiterJ = RotL64((aOrbiterJ * 7276207208162697249U), 11U);
            //
            aOrbiterG = ((aOrbiterG + aOrbiterA) + 3911046580637583767U) + aNonceWordB;
            aOrbiterK = (aOrbiterK ^ aOrbiterG) ^ 9315984027042049203U;
            aOrbiterK = RotL64((aOrbiterK * 12568550776487242469U), 23U);
            //
            aOrbiterK = (aOrbiterK + aOrbiterH) + 8926367674641729058U;
            aOrbiterC = (aOrbiterC ^ aOrbiterK) ^ 11035347490524961446U;
            aOrbiterC = RotL64((aOrbiterC * 10948288997163592463U), 3U);
            //
            aOrbiterI = (aOrbiterI + aOrbiterJ) + 10748158733051120339U;
            aOrbiterA = (aOrbiterA ^ aOrbiterI) ^ 2467801787989056455U;
            aOrbiterA = RotL64((aOrbiterA * 12621934274702358977U), 57U);
            //
            aOrbiterA = (aOrbiterA + aOrbiterB) + 9244415080474351390U;
            aOrbiterH = ((aOrbiterH ^ aOrbiterA) ^ 8517784887959492079U) ^ aPhaseBOrbiterUpdateSaltB[(((31U - aIndex) + 23U)) & S_SALT1];
            aOrbiterH = RotL64((aOrbiterH * 17022899813765884147U), 35U);
            //
            aOrbiterB = ((aOrbiterB + aOrbiterE) + 8409307332803038455U) + aPhaseBOrbiterUpdateSaltC[((aIndex + 4U)) & S_SALT1];
            aOrbiterI = (aOrbiterI ^ aOrbiterB) ^ 11043806021873232950U;
            aOrbiterI = RotL64((aOrbiterI * 8294888329708842989U), 53U);
            //
            aOrbiterC = ((aOrbiterC + aOrbiterG) + 17512395828450251457U) + aPhaseBOrbiterUpdateSaltD[(((31U - aIndex) + 19U)) & S_SALT1];
            aOrbiterE = (aOrbiterE ^ aOrbiterC) ^ 16849067939795823992U;
            aOrbiterE = RotL64((aOrbiterE * 9361991804481514337U), 29U);
            //
            aOrbiterJ = (aOrbiterJ + aOrbiterC) + 17541946638063238056U;
            aOrbiterB = (aOrbiterB ^ aOrbiterJ) ^ 11430501673960586718U;
            aOrbiterB = RotL64((aOrbiterB * 15074409630605450091U), 43U);
            //
            aOrbiterH = ((aOrbiterH + aOrbiterI) + 78307505705383302U) + aNonceWordE;
            aOrbiterG = ((aOrbiterG ^ aOrbiterH) ^ 4834528975263832983U) ^ aNonceWordG;
            aOrbiterG = RotL64((aOrbiterG * 17245673681686752861U), 19U);
            //
            aIngress = aOrbiterC ^ RotL64(aOrbiterA, 47U);
            aIngress = aIngress + (aOrbiterG ^ RotL64(aOrbiterI, 3U));
            aIngress = aIngress + (aOrbiterE ^ RotL64(aOrbiterK, 14U));
            aIngress = aIngress + (RotL64(aOrbiterH, 21U) ^ aOrbiterB);
            aIngress = aIngress + RotL64(aOrbiterJ, 51U);
            aIngress = TwistMix64::DiffuseC((aIngress + aScatter));
            //
            aWandererI = aWandererI + ((((RotL64(aScatter, 43U) + RotL64(aOrbiterJ, 11U)) + aOrbiterC) + RotL64(aCarry, 19U)) + aNonceWordF);
            aWandererA = aWandererA ^ ((RotL64(aPrevious, 52U) + aOrbiterJ) + RotL64(aOrbiterE, 18U));
            aWandererK = aWandererK + (((RotL64(aIngress, 29U) + RotL64(aOrbiterK, 27U)) + aOrbiterC) + RotL64(aCarry, 35U));
            aWandererE = aWandererE ^ ((RotL64(aCross, 3U) + RotL64(aOrbiterK, 35U)) + aOrbiterH);
            aWandererH = aWandererH + (((RotL64(aPrevious, 57U) + RotL64(aOrbiterB, 5U)) + aOrbiterA) + aNonceWordH);
            aWandererD = aWandererD ^ (((RotL64(aCross, 38U) + aOrbiterC) + RotL64(aOrbiterH, 51U)) + aNonceWordN);
            aWandererJ = aWandererJ + (((RotL64(aIngress, 47U) + RotL64(aOrbiterG, 23U)) + aOrbiterI) + aPhaseBWandererUpdateSaltF[((aIndex + 24U)) & S_SALT1]);
            aWandererC = aWandererC ^ (((RotL64(aScatter, 23U) + RotL64(aOrbiterI, 47U)) + aOrbiterE) + aPhaseBWandererUpdateSaltB[(((31U - aIndex) + 20U)) & S_SALT1]);
            aWandererG = aWandererG + (((RotL64(aIngress, 13U) + RotL64(aOrbiterB, 60U)) + aOrbiterE) + aNonceWordA);
            //
            aCarry = aCarry + (RotL64(aWandererD, 19U) ^ aWandererJ);
            aCarry = aCarry + (aWandererG ^ RotL64(aWandererC, 37U));
            aCarry = aCarry + (RotL64(aWandererH, 22U) ^ aWandererI);
            aCarry = aCarry + (aWandererE ^ RotL64(aWandererK, 51U));
            aCarry = aCarry + RotL64(aWandererA, 57U);
            aCarry = aCarry + RotL64(aIngress, 5U);
            aCarry = TwistMix64::DiffuseB(aCarry);
            //
            aWorkLaneC[aIndex] = aIngress;
        }
    
        // seed_loop_b loop 4
        // ingress from: aWorkLaneC, aWorkLaneA, aOperationLaneD, aExpandLaneC
        // ingress directions: aWorkLaneC forward forced, aWorkLaneA forward forced, aOperationLaneD forward forced, aExpandLaneC forward/backward random
        // cross from: aWorkLaneB, aOperationLaneB, aExpandLaneD
        // cross directions: aWorkLaneB backward forced, aOperationLaneB backward forced, aExpandLaneD backward/forward random
        // write to: aWorkLaneD
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aWorkLaneC[((aIndex + 26049U)) & S_BLOCK1], 23U) ^ RotL64(aWorkLaneA[((aIndex + 27012U)) & S_BLOCK1], 5U));
            aIngress ^= (RotL64(aOperationLaneD[((aIndex + 28483U)) & S_BLOCK1], 57U) ^ RotL64(aExpandLaneC[((aIndex + 29310U)) & S_BLOCK1], 13U));
            aIngress = TwistMix64::DiffuseB(((aIngress ^ aPhaseBDomainWordIngress) ^ aNonceWordE));
            //
            aCross = (RotL64(aWorkLaneB[((S_BLOCK1 - aIndex + 30903U)) & S_BLOCK1], 57U) ^ RotL64(aOperationLaneB[((S_BLOCK1 - aIndex + 31378U)) & S_BLOCK1], 42U));
            aCross ^= RotL64(aExpandLaneD[((aIndex + 27404U)) & S_BLOCK1], 29U);
            aCross = TwistMix64::DiffuseB(((aCross ^ aPhaseBDomainWordCross) ^ aNonceWordA));
            //
            aScatter = (RotL64(aCarry, 27U) + RotL64(aIngress, 56U)) + (RotL64(aCross, 43U) ^ RotL64(aPrevious, 13U));
            aScatter = TwistMix64::DiffuseA(((aScatter ^ aPhaseBDomainWordScatter) ^ aNonceWordH));
            //
            aOrbiterD = (((aWandererJ + RotL64(aScatter, 18U)) + 10805654776556844351U) + aPhaseBOrbiterAssignSaltF[((aIndex + 5U)) & S_SALT1]) + aNonceWordN;
            aOrbiterG = (aWandererE + RotL64(aIngress, 39U)) + 582794182442795335U;
            aOrbiterC = (((aWandererD + RotL64(aCross, 35U)) + RotL64(aCarry, 5U)) + 2858343650974681068U) + aNonceWordB;
            aOrbiterA = ((aWandererC + RotL64(aPrevious, 57U)) + 8189584049022064284U) + aPhaseBOrbiterAssignSaltB[(((31U - aIndex) + 19U)) & S_SALT1];
            aOrbiterI = (aWandererF + RotL64(aCross, 43U)) + 1565100751996962893U;
            aOrbiterJ = ((aWandererH + RotL64(aIngress, 26U)) + RotL64(aCarry, 13U)) + 8062028016947611891U;
            aOrbiterF = (aWandererG + RotL64(aScatter, 51U)) + 8280504280578451745U;
            aOrbiterH = ((aWandererB + RotL64(aPrevious, 11U)) + RotL64(aCarry, 43U)) + 11326869194491655350U;
            aOrbiterK = (aWandererK + RotL64(aScatter, 47U)) + 1671695656567777163U;
            //
            aOrbiterD = (aOrbiterD + aOrbiterG) + 2349843105293943452U;
            aOrbiterC = (aOrbiterC ^ aOrbiterD) ^ 13015545152052004254U;
            aOrbiterC = RotL64((aOrbiterC * 1316662811685429983U), 19U);
            //
            aOrbiterC = (aOrbiterC + aOrbiterA) + 16703354404749291869U;
            aOrbiterI = (aOrbiterI ^ aOrbiterC) ^ 8713231044374305801U;
            aOrbiterI = RotL64((aOrbiterI * 9242480982197688625U), 13U);
            //
            aOrbiterJ = (aOrbiterJ + aOrbiterD) + 11118401674497783533U;
            aOrbiterF = (aOrbiterF ^ aOrbiterJ) ^ 14857556493734710364U;
            aOrbiterF = RotL64((aOrbiterF * 3452566050389715195U), 43U);
            //
            aOrbiterG = ((aOrbiterG + aOrbiterF) + 12953419670951660965U) + aPhaseBOrbiterUpdateSaltE[((aIndex + 15U)) & S_SALT1];
            aOrbiterA = ((aOrbiterA ^ aOrbiterG) ^ 12666121730825089017U) ^ aPhaseBOrbiterUpdateSaltA[((aIndex + 21U)) & S_SALT1];
            aOrbiterA = RotL64((aOrbiterA * 14049925256934142519U), 35U);
            //
            aOrbiterH = (aOrbiterH + aOrbiterJ) + 11075249639473053423U;
            aOrbiterG = ((aOrbiterG ^ aOrbiterH) ^ 9374217688244187867U) ^ aPhaseBOrbiterUpdateSaltC[(((31U - aIndex) + 3U)) & S_SALT1];
            aOrbiterG = RotL64((aOrbiterG * 5261156325627117877U), 3U);
            //
            aOrbiterF = (aOrbiterF + aOrbiterC) + 17608340953291367867U;
            aOrbiterK = ((aOrbiterK ^ aOrbiterF) ^ 13159437499327086340U) ^ aNonceWordC;
            aOrbiterK = RotL64((aOrbiterK * 4882100944453534805U), 23U);
            //
            aOrbiterK = (aOrbiterK + aOrbiterI) + 4304700511322366815U;
            aOrbiterJ = (aOrbiterJ ^ aOrbiterK) ^ 10172544755256706767U;
            aOrbiterJ = RotL64((aOrbiterJ * 4013006212154771797U), 39U);
            //
            aOrbiterA = ((aOrbiterA + aOrbiterK) + 17340067939877432472U) + aPhaseBOrbiterUpdateSaltF[(((31U - aIndex) + 27U)) & S_SALT1];
            aOrbiterH = (aOrbiterH ^ aOrbiterA) ^ 14130447570008179105U;
            aOrbiterH = RotL64((aOrbiterH * 8178075071208718915U), 57U);
            //
            aOrbiterI = (aOrbiterI + aOrbiterH) + 2652532710498072378U;
            aOrbiterD = ((aOrbiterD ^ aOrbiterI) ^ 10384945384238518296U) ^ aNonceWordI;
            aOrbiterD = RotL64((aOrbiterD * 17137694272394304045U), 51U);
            //
            aIngress = RotL64(aOrbiterG, 43U) ^ aOrbiterD;
            aIngress = aIngress + (RotL64(aOrbiterK, 57U) ^ aOrbiterH);
            aIngress = aIngress + (aOrbiterI ^ RotL64(aOrbiterF, 60U));
            aIngress = aIngress + (aOrbiterC ^ RotL64(aOrbiterA, 21U));
            aIngress = aIngress + RotL64(aOrbiterJ, 53U);
            aIngress = TwistMix64::DiffuseB((aIngress + aScatter));
            //
            aWandererH = aWandererH + (((RotL64(aCross, 35U) + RotL64(aOrbiterD, 10U)) + aOrbiterJ) + aPhaseBWandererUpdateSaltA[(((31U - aIndex) + 14U)) & S_SALT1]);
            aWandererJ = aWandererJ ^ (((RotL64(aScatter, 52U) + RotL64(aOrbiterH, 23U)) + aOrbiterK) + aPhaseBWandererUpdateSaltD[(((31U - aIndex) + 13U)) & S_SALT1]);
            aWandererD = aWandererD + ((RotL64(aIngress, 29U) + RotL64(aOrbiterI, 43U)) + aOrbiterJ);
            aWandererC = aWandererC ^ ((RotL64(aPrevious, 57U) + aOrbiterJ) + RotL64(aOrbiterF, 37U));
            aWandererG = aWandererG + ((RotL64(aScatter, 23U) + RotL64(aOrbiterC, 5U)) + aOrbiterG);
            aWandererB = aWandererB ^ ((RotL64(aPrevious, 3U) + aOrbiterI) + RotL64(aOrbiterH, 47U));
            aWandererF = aWandererF + ((((RotL64(aIngress, 13U) + RotL64(aOrbiterI, 51U)) + aOrbiterA) + RotL64(aCarry, 37U)) + aNonceWordM);
            aWandererK = aWandererK ^ ((RotL64(aCross, 18U) + RotL64(aOrbiterA, 57U)) + aOrbiterC);
            aWandererE = aWandererE + ((((RotL64(aScatter, 39U) + aOrbiterK) + RotL64(aOrbiterC, 30U)) + RotL64(aCarry, 19U)) + aNonceWordD);
            //
            aCarry = aCarry + (aWandererE ^ RotL64(aWandererB, 44U));
            aCarry = aCarry + (RotL64(aWandererF, 19U) ^ aWandererG);
            aCarry = aCarry + (aWandererC ^ RotL64(aWandererK, 51U));
            aCarry = aCarry + (RotL64(aWandererJ, 37U) ^ aWandererD);
            aCarry = aCarry + RotL64(aWandererH, 57U);
            aCarry = aCarry + RotL64(aIngress, 13U);
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

void TwistExpander_Greezy_Arx::Seed_D(TwistWorkSpace *pWorkSpace,
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
    std::uint64_t aNonceWordA = TwistMix64::DiffuseA(pNonce * 0x836C736AA7EDF81FULL + 0xBAC7ED500371CA7AULL);
    std::uint64_t aNonceWordB = TwistMix64::DiffuseC(pNonce * 0xDDA69502E36282ABULL + 0x92062B0657702BF4ULL);
    std::uint64_t aNonceWordC = TwistMix64::DiffuseC(pNonce * 0xCCBBD8667AE8CC5BULL + 0xBA693520744C59ACULL);
    std::uint64_t aNonceWordD = TwistMix64::DiffuseC(pNonce * 0xB16F4F9F549A29BBULL + 0x9EF41A62EA1452F4ULL);
    std::uint64_t aNonceWordE = TwistMix64::DiffuseB(pNonce * 0xBD8C9F83BE2C48B9ULL + 0xDA7714A7593A8606ULL);
    std::uint64_t aNonceWordF = TwistMix64::DiffuseB(pNonce * 0xE43927E2CE776235ULL + 0xCB25E9104881E0FFULL);
    std::uint64_t aNonceWordG = TwistMix64::DiffuseB(pNonce * 0xD6463873CB45A69FULL + 0xCDE07354CBE24E53ULL);
    std::uint64_t aNonceWordH = TwistMix64::DiffuseA(pNonce * 0x88619C9D5B60AAFBULL + 0xD32076C9526C13D2ULL);
    std::uint64_t aNonceWordI = TwistMix64::DiffuseA(pNonce * 0xB9532E7F46B37D5FULL + 0xAB1A933C269003C7ULL);
    std::uint64_t aNonceWordJ = TwistMix64::DiffuseC(pNonce * 0xB07793EDD90700E3ULL + 0xFA132EEB73B67777ULL);
    std::uint64_t aNonceWordK = TwistMix64::DiffuseA(pNonce * 0xF7DFD3D507647CC1ULL + 0xC2E5C12C5C3C9FC9ULL);
    std::uint64_t aNonceWordL = TwistMix64::DiffuseA(pNonce * 0xFEB63F478F39F339ULL + 0xE0F85E00237B24E0ULL);
    std::uint64_t aNonceWordM = TwistMix64::DiffuseC(pNonce * 0xB238A982550F18B1ULL + 0xCA46CC5E28D7E02AULL);
    std::uint64_t aNonceWordN = TwistMix64::DiffuseB(pNonce * 0xCFD81B6B1D8B1ED9ULL + 0xF7BC56BA38497137ULL);
    std::uint64_t aNonceWordO = TwistMix64::DiffuseC(pNonce * 0xBFCB6FADFD049651ULL + 0xAE3B6BC351E922E3ULL);
    std::uint64_t aNonceWordP = TwistMix64::DiffuseA(pNonce * 0xD92A5CA635DA38CDULL + 0x8ED52EAB6D6A0DB0ULL);
    // GSeedRunSeed_D seed_loop_d (start)
    {
        // GSeedRunSeed_D seed_loop_d lane group
        // read from: aExpandLaneA, aExpandLaneB, aFireLaneA, aExpandLaneC, aExpandLaneD, aFireLaneB, aWorkLaneA, aFireLaneC, aFireLaneD, aWorkLaneB, aOperationLaneA, aInvestLaneA, aOperationLaneB, aInvestLaneB, aOperationLaneC, aInvestLaneC, aOperationLaneD
        // write to: aWorkLaneA, aWorkLaneB, aInvestLaneA, aInvestLaneB, aInvestLaneC, aInvestLaneD
    
        // seed_loop_d loop 1
        // ingress from: aExpandLaneA, aExpandLaneB, aFireLaneA
        // ingress directions: aExpandLaneA forward forced, aExpandLaneB forward forced, aFireLaneA forward/backward random
        // cross from: aExpandLaneC, aExpandLaneD, aFireLaneB
        // cross directions: aExpandLaneC backward forced, aExpandLaneD backward forced, aFireLaneB backward/forward random
        // write to: aWorkLaneA
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aExpandLaneA[((aIndex + 2575U)) & S_BLOCK1], 6U) ^ RotL64(aExpandLaneB[((aIndex + 2768U)) & S_BLOCK1], 23U));
            aIngress ^= RotL64(aFireLaneA[((aIndex + 4764U)) & S_BLOCK1], 47U);
            aIngress = TwistMix64::DiffuseB(((aIngress ^ aPhaseDDomainWordIngress) ^ aNonceWordJ));
            //
            aCross = (RotL64(aExpandLaneC[((S_BLOCK1 - aIndex + 1694U)) & S_BLOCK1], 5U) ^ RotL64(aExpandLaneD[((S_BLOCK1 - aIndex + 1458U)) & S_BLOCK1], 35U));
            aCross ^= RotL64(aFireLaneB[((aIndex + 3383U)) & S_BLOCK1], 60U);
            aCross = TwistMix64::DiffuseC(((aCross ^ aPhaseDDomainWordCross) ^ aNonceWordC));
            //
            aScatter = (RotL64(aIngress, 39U) + RotL64(aCarry, 24U)) ^ (RotL64(aPrevious, 51U) ^ RotL64(aCross, 3U));
            aScatter = TwistMix64::DiffuseB(((aScatter ^ aPhaseDDomainWordScatter) ^ aNonceWordK));
            //
            aOrbiterD = (aWandererB + RotL64(aPrevious, 11U)) + 16200278595895089008U;
            aOrbiterE = ((aWandererC + RotL64(aIngress, 19U)) + 1029614154810465897U) + aNonceWordO;
            aOrbiterA = (((aWandererH + RotL64(aCross, 37U)) + RotL64(aCarry, 19U)) + 7129562468705441295U) + aNonceWordF;
            aOrbiterC = (aWandererA + RotL64(aScatter, 3U)) + 14388903902433951274U;
            aOrbiterK = (((aWandererI + RotL64(aPrevious, 29U)) + 1013568949315967455U) + aPhaseDOrbiterAssignSaltB[((aIndex + 9U)) & S_SALT1]) + aNonceWordA;
            aOrbiterI = (((aWandererJ + RotL64(aIngress, 46U)) + RotL64(aCarry, 41U)) + 3128823373497815651U) + aNonceWordK;
            aOrbiterF = (((aWandererK + RotL64(aScatter, 53U)) + RotL64(aCarry, 57U)) + 14525694606889470589U) + aPhaseDOrbiterAssignSaltF[(((31U - aIndex) + 27U)) & S_SALT1];
            //
            aOrbiterD = (aOrbiterD + aOrbiterE) + 14443983602196782887U;
            aOrbiterA = (aOrbiterA ^ aOrbiterD) ^ 12244220415328641190U;
            aOrbiterA = RotL64((aOrbiterA * 15052949098014803181U), 29U);
            //
            aOrbiterE = ((aOrbiterE + aOrbiterC) + 10477159225338766614U) + aPhaseDOrbiterUpdateSaltE[((aIndex + 15U)) & S_SALT1];
            aOrbiterK = ((aOrbiterK ^ aOrbiterE) ^ 2842870123078131566U) ^ aNonceWordB;
            aOrbiterK = RotL64((aOrbiterK * 11522265477555954071U), 35U);
            //
            aOrbiterA = (aOrbiterA + aOrbiterK) + 8621138818955849917U;
            aOrbiterI = (aOrbiterI ^ aOrbiterA) ^ 5038396344400303181U;
            aOrbiterI = RotL64((aOrbiterI * 14636756322207385447U), 51U);
            //
            aOrbiterI = ((aOrbiterI + aOrbiterF) + 2768613802894372496U) + aPhaseDOrbiterUpdateSaltF[((aIndex + 26U)) & S_SALT1];
            aOrbiterE = (((aOrbiterE ^ aOrbiterI) ^ 2027754864051410015U) ^ aPhaseDOrbiterUpdateSaltB[(((31U - aIndex) + 7U)) & S_SALT1]) ^ aNonceWordL;
            aOrbiterE = RotL64((aOrbiterE * 2461322540050569287U), 23U);
            //
            aOrbiterF = (aOrbiterF + aOrbiterA) + 2848088309172056399U;
            aOrbiterC = (aOrbiterC ^ aOrbiterF) ^ 15017458513904884651U;
            aOrbiterC = RotL64((aOrbiterC * 9926904679902843055U), 57U);
            //
            aOrbiterK = (aOrbiterK + aOrbiterD) + 9079797279596336139U;
            aOrbiterF = (((aOrbiterF ^ aOrbiterK) ^ 15424866642305110811U) ^ aPhaseDOrbiterUpdateSaltA[(((31U - aIndex) + 24U)) & S_SALT1]) ^ aNonceWordN;
            aOrbiterF = RotL64((aOrbiterF * 12912331089970158845U), 43U);
            //
            aOrbiterC = (aOrbiterC + aOrbiterI) + 13751764050290602740U;
            aOrbiterD = (aOrbiterD ^ aOrbiterC) ^ 7694557131324740282U;
            aOrbiterD = RotL64((aOrbiterD * 14980807690491467023U), 13U);
            //
            aIngress = aOrbiterF ^ RotL64(aOrbiterI, 13U);
            aIngress = aIngress + (RotL64(aOrbiterD, 3U) ^ aOrbiterE);
            aIngress = aIngress + (aOrbiterC ^ RotL64(aOrbiterA, 21U));
            aIngress = aIngress + RotL64(aOrbiterK, 36U);
            aIngress = TwistMix64::DiffuseB((aIngress + aScatter));
            //
            aWandererB = aWandererB ^ (((RotL64(aCross, 57U) + RotL64(aOrbiterE, 37U)) + aOrbiterK) + aPhaseDWandererUpdateSaltB[(((31U - aIndex) + 20U)) & S_SALT1]);
            aWandererH = aWandererH + (((RotL64(aScatter, 5U) + RotL64(aOrbiterI, 19U)) + aOrbiterF) + aNonceWordI);
            aWandererJ = aWandererJ ^ ((RotL64(aPrevious, 11U) + aOrbiterF) + RotL64(aOrbiterE, 51U));
            aWandererC = aWandererC + ((((RotL64(aIngress, 27U) + RotL64(aOrbiterC, 43U)) + aOrbiterD) + RotL64(aCarry, 51U)) + aNonceWordM);
            aWandererK = aWandererK ^ ((RotL64(aScatter, 20U) + aOrbiterK) + RotL64(aOrbiterD, 30U));
            aWandererI = aWandererI + ((((RotL64(aPrevious, 35U) + RotL64(aOrbiterE, 13U)) + aOrbiterD) + RotL64(aCarry, 29U)) + aNonceWordH);
            aWandererA = aWandererA ^ ((((RotL64(aCross, 51U) + RotL64(aOrbiterF, 5U)) + aOrbiterA) + aNonceWordE) + aPhaseDWandererUpdateSaltD[((aIndex + 21U)) & S_SALT1]);
            //
            aCarry = aCarry + (aWandererB ^ RotL64(aWandererJ, 37U));
            aCarry = aCarry + (aWandererI ^ RotL64(aWandererH, 22U));
            aCarry = aCarry + (aWandererC ^ RotL64(aWandererA, 5U));
            aCarry = aCarry + RotL64(aWandererK, 57U);
            aCarry = aCarry + RotL64(aIngress, 43U);
            aCarry = TwistMix64::DiffuseA(aCarry);
            //
            aWorkLaneA[aIndex] = aIngress;
        }
    
        // seed_loop_d loop 2
        // ingress from: aWorkLaneA, aExpandLaneC, aExpandLaneD, aFireLaneC
        // ingress directions: aWorkLaneA forward forced, aExpandLaneC forward forced, aExpandLaneD forward forced, aFireLaneC forward/backward random
        // cross from: aExpandLaneA, aExpandLaneB, aFireLaneD
        // cross directions: aExpandLaneA backward forced, aExpandLaneB backward forced, aFireLaneD backward/forward random
        // write to: aWorkLaneB
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aWorkLaneA[((aIndex + 8080U)) & S_BLOCK1], 21U) ^ RotL64(aExpandLaneC[((aIndex + 10758U)) & S_BLOCK1], 11U));
            aIngress ^= (RotL64(aExpandLaneD[((aIndex + 9232U)) & S_BLOCK1], 53U) ^ RotL64(aFireLaneC[((aIndex + 7700U)) & S_BLOCK1], 30U));
            aIngress = TwistMix64::DiffuseB(((aIngress ^ aPhaseDDomainWordIngress) ^ aNonceWordB));
            //
            aCross = (RotL64(aExpandLaneA[((S_BLOCK1 - aIndex + 7615U)) & S_BLOCK1], 28U) ^ RotL64(aExpandLaneB[((S_BLOCK1 - aIndex + 9108U)) & S_BLOCK1], 13U));
            aCross ^= RotL64(aFireLaneD[((aIndex + 10234U)) & S_BLOCK1], 41U);
            aCross = TwistMix64::DiffuseB(((aCross ^ aPhaseDDomainWordCross) ^ aNonceWordE));
            //
            aScatter = (RotL64(aIngress, 4U) + RotL64(aCross, 19U)) ^ (RotL64(aPrevious, 53U) + RotL64(aCarry, 41U));
            aScatter = TwistMix64::DiffuseA(((aScatter ^ aPhaseDDomainWordScatter) ^ aNonceWordJ));
            //
            aOrbiterB = (((aWandererE + RotL64(aIngress, 11U)) + 8375305456876489425U) + aPhaseDOrbiterAssignSaltD[(((31U - aIndex) + 22U)) & S_SALT1]) + aNonceWordJ;
            aOrbiterD = (aWandererB + RotL64(aScatter, 19U)) + 16193562952772453047U;
            aOrbiterG = ((aWandererD + RotL64(aPrevious, 41U)) + RotL64(aCarry, 29U)) + 18088652458594816223U;
            aOrbiterK = (((aWandererJ + RotL64(aCross, 60U)) + RotL64(aCarry, 3U)) + 767344788620249944U) + aNonceWordI;
            aOrbiterH = ((((aWandererH + RotL64(aIngress, 53U)) + RotL64(aCarry, 51U)) + 7705194930396368752U) + aPhaseDOrbiterAssignSaltE[(((31U - aIndex) + 9U)) & S_SALT1]) + aNonceWordC;
            aOrbiterA = (aWandererK + RotL64(aCross, 29U)) + 3829736891311272834U;
            aOrbiterE = ((aWandererG + RotL64(aScatter, 3U)) + 9881681671347640061U) + aNonceWordK;
            //
            aOrbiterB = (aOrbiterB + aOrbiterD) + 1721196560190164264U;
            aOrbiterG = (aOrbiterG ^ aOrbiterB) ^ 3002652618388454213U;
            aOrbiterG = RotL64((aOrbiterG * 15289749311593032657U), 35U);
            //
            aOrbiterG = ((aOrbiterG + aOrbiterK) + 9811621464004005202U) + aNonceWordM;
            aOrbiterH = (aOrbiterH ^ aOrbiterG) ^ 5652598941069986530U;
            aOrbiterH = RotL64((aOrbiterH * 4797973356708091621U), 57U);
            //
            aOrbiterA = ((aOrbiterA + aOrbiterH) + 6250499348327316328U) + aPhaseDOrbiterUpdateSaltA[((aIndex + 4U)) & S_SALT1];
            aOrbiterD = ((aOrbiterD ^ aOrbiterA) ^ 16025054277615264530U) ^ aPhaseDOrbiterUpdateSaltD[(((31U - aIndex) + 19U)) & S_SALT1];
            aOrbiterD = RotL64((aOrbiterD * 16446892258704281903U), 41U);
            //
            aOrbiterE = (((aOrbiterE + aOrbiterG) + 13800298546867243172U) + aPhaseDOrbiterUpdateSaltC[(((31U - aIndex) + 17U)) & S_SALT1]) + aNonceWordF;
            aOrbiterA = (aOrbiterA ^ aOrbiterE) ^ 12256104592865905782U;
            aOrbiterA = RotL64((aOrbiterA * 16983140179497142713U), 13U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterE) + 17817225416918329229U;
            aOrbiterK = (aOrbiterK ^ aOrbiterD) ^ 17738671327352776217U;
            aOrbiterK = RotL64((aOrbiterK * 393488251327705063U), 51U);
            //
            aOrbiterH = (aOrbiterH + aOrbiterB) + 6816031224188400541U;
            aOrbiterE = (aOrbiterE ^ aOrbiterH) ^ 16989563985059237014U;
            aOrbiterE = RotL64((aOrbiterE * 8677884225771717797U), 23U);
            //
            aOrbiterK = (aOrbiterK + aOrbiterA) + 16891524847268207549U;
            aOrbiterB = ((aOrbiterB ^ aOrbiterK) ^ 1833508573940405571U) ^ aPhaseDOrbiterUpdateSaltB[(((31U - aIndex) + 5U)) & S_SALT1];
            aOrbiterB = RotL64((aOrbiterB * 9709196587703979539U), 5U);
            //
            aIngress = aOrbiterD ^ RotL64(aOrbiterK, 12U);
            aIngress = aIngress + (RotL64(aOrbiterE, 43U) ^ aOrbiterA);
            aIngress = aIngress + (RotL64(aOrbiterG, 21U) ^ aOrbiterB);
            aIngress = aIngress + RotL64(aOrbiterH, 3U);
            aIngress = TwistMix64::DiffuseA((aIngress + aScatter));
            //
            aWandererD = aWandererD ^ (((RotL64(aScatter, 53U) + aOrbiterB) + RotL64(aOrbiterD, 3U)) + aNonceWordN);
            aWandererH = aWandererH + (((((RotL64(aCross, 6U) + RotL64(aOrbiterE, 13U)) + aOrbiterG) + RotL64(aCarry, 39U)) + aNonceWordL) + aPhaseDWandererUpdateSaltC[((aIndex + 21U)) & S_SALT1]);
            aWandererK = aWandererK ^ ((RotL64(aIngress, 21U) + RotL64(aOrbiterK, 21U)) + aOrbiterD);
            aWandererJ = aWandererJ + ((RotL64(aPrevious, 13U) + aOrbiterK) + RotL64(aOrbiterG, 57U));
            aWandererE = aWandererE ^ ((((RotL64(aIngress, 27U) + aOrbiterH) + RotL64(aOrbiterG, 47U)) + aNonceWordA) + aPhaseDWandererUpdateSaltE[((aIndex + 7U)) & S_SALT1]);
            aWandererG = aWandererG + ((((RotL64(aPrevious, 35U) + RotL64(aOrbiterD, 39U)) + aOrbiterA) + RotL64(aCarry, 5U)) + aNonceWordO);
            aWandererB = aWandererB ^ ((RotL64(aScatter, 41U) + aOrbiterE) + RotL64(aOrbiterD, 30U));
            //
            aCarry = aCarry + (aWandererH ^ RotL64(aWandererB, 20U));
            aCarry = aCarry + (aWandererE ^ RotL64(aWandererK, 51U));
            aCarry = aCarry + (aWandererJ ^ RotL64(aWandererD, 3U));
            aCarry = aCarry + RotL64(aWandererG, 11U);
            aCarry = aCarry + RotL64(aIngress, 39U);
            aCarry = TwistMix64::DiffuseC(aCarry);
            //
            aWorkLaneB[S_BLOCK1 - aIndex] = aIngress;
        }
    
        // seed_loop_d loop 3
        // ingress from: aWorkLaneB, aExpandLaneA, aOperationLaneA
        // ingress directions: aWorkLaneB forward forced, aExpandLaneA forward forced, aOperationLaneA forward/backward random
        // cross from: aWorkLaneA, aExpandLaneC
        // cross directions: aWorkLaneA backward forced, aExpandLaneC backward/forward random
        // write to: aInvestLaneA
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aWorkLaneB[((aIndex + 12650U)) & S_BLOCK1], 3U) ^ RotL64(aExpandLaneA[((aIndex + 11141U)) & S_BLOCK1], 26U));
            aIngress ^= RotL64(aOperationLaneA[((aIndex + 13216U)) & S_BLOCK1], 35U);
            aIngress = TwistMix64::DiffuseA(((aIngress ^ aPhaseDDomainWordIngress) ^ aNonceWordE));
            //
            aCross = RotL64(aWorkLaneA[((S_BLOCK1 - aIndex + 13905U)) & S_BLOCK1], 43U) ^ RotL64(aExpandLaneC[((aIndex + 12057U)) & S_BLOCK1], 30U);
            aCross = TwistMix64::DiffuseB(((aCross ^ aPhaseDDomainWordCross) ^ aNonceWordK));
            //
            aScatter = (RotL64(aCarry, 53U) + RotL64(aIngress, 39U)) ^ (RotL64(aCross, 11U) ^ RotL64(aPrevious, 26U));
            aScatter = TwistMix64::DiffuseB(((aScatter ^ aPhaseDDomainWordScatter) ^ aNonceWordD));
            //
            aOrbiterK = (((aWandererJ + RotL64(aIngress, 27U)) + RotL64(aCarry, 53U)) + 13333509828310369865U) + aNonceWordI;
            aOrbiterB = ((aWandererA + RotL64(aCross, 5U)) + 7645352517103840797U) + aNonceWordL;
            aOrbiterD = ((aWandererI + RotL64(aPrevious, 52U)) + 5310766306660062655U) + aNonceWordB;
            aOrbiterC = (((aWandererH + RotL64(aScatter, 13U)) + RotL64(aCarry, 3U)) + 5165635069832352932U) + aPhaseDOrbiterAssignSaltC[((aIndex + 7U)) & S_SALT1];
            aOrbiterA = ((aWandererE + RotL64(aCross, 19U)) + RotL64(aCarry, 29U)) + 15684141764734281849U;
            aOrbiterE = (aWandererB + RotL64(aPrevious, 41U)) + 3327963374225061738U;
            aOrbiterH = ((aWandererG + RotL64(aIngress, 35U)) + 8625811794878848871U) + aPhaseDOrbiterAssignSaltA[(((31U - aIndex) + 27U)) & S_SALT1];
            //
            aOrbiterK = (aOrbiterK + aOrbiterB) + 7598657468430485291U;
            aOrbiterD = (aOrbiterD ^ aOrbiterK) ^ 2881171216276746485U;
            aOrbiterD = RotL64((aOrbiterD * 3331350584102843605U), 37U);
            //
            aOrbiterC = (aOrbiterC + aOrbiterA) + 10237691227222918101U;
            aOrbiterK = (aOrbiterK ^ aOrbiterC) ^ 6419254255884834497U;
            aOrbiterK = RotL64((aOrbiterK * 3816625473642865305U), 53U);
            //
            aOrbiterA = ((aOrbiterA + aOrbiterK) + 4238455444646479956U) + aPhaseDOrbiterUpdateSaltE[(((31U - aIndex) + 13U)) & S_SALT1];
            aOrbiterB = (((aOrbiterB ^ aOrbiterA) ^ 14936613353493061492U) ^ aPhaseDOrbiterUpdateSaltD[((aIndex + 15U)) & S_SALT1]) ^ aNonceWordD;
            aOrbiterB = RotL64((aOrbiterB * 3544216916806292273U), 13U);
            //
            aOrbiterE = ((aOrbiterE + aOrbiterC) + 15324699725208372627U) + aNonceWordM;
            aOrbiterA = ((aOrbiterA ^ aOrbiterE) ^ 9506640480601832011U) ^ aPhaseDOrbiterUpdateSaltB[(((31U - aIndex) + 19U)) & S_SALT1];
            aOrbiterA = RotL64((aOrbiterA * 12819564111348390227U), 5U);
            //
            aOrbiterH = (aOrbiterH + aOrbiterE) + 3709149613660215641U;
            aOrbiterC = (aOrbiterC ^ aOrbiterH) ^ 1724290199312754307U;
            aOrbiterC = RotL64((aOrbiterC * 12597580418257897965U), 21U);
            //
            aOrbiterB = (aOrbiterB + aOrbiterD) + 13191172833570139194U;
            aOrbiterH = ((aOrbiterH ^ aOrbiterB) ^ 3686087945377837886U) ^ aNonceWordO;
            aOrbiterH = RotL64((aOrbiterH * 10883609557429936283U), 43U);
            //
            aOrbiterD = ((aOrbiterD + aOrbiterH) + 10418330386245397022U) + aPhaseDOrbiterUpdateSaltC[(((31U - aIndex) + 23U)) & S_SALT1];
            aOrbiterE = ((aOrbiterE ^ aOrbiterD) ^ 5383531313632347245U) ^ aNonceWordH;
            aOrbiterE = RotL64((aOrbiterE * 2987755379396160073U), 27U);
            //
            aIngress = aOrbiterC ^ RotL64(aOrbiterH, 21U);
            aIngress = aIngress + (RotL64(aOrbiterE, 13U) ^ aOrbiterB);
            aIngress = aIngress + (RotL64(aOrbiterK, 41U) ^ aOrbiterD);
            aIngress = aIngress + RotL64(aOrbiterA, 50U);
            aIngress = TwistMix64::DiffuseB((aIngress + aScatter));
            //
            aWandererE = aWandererE + ((((RotL64(aPrevious, 10U) + RotL64(aOrbiterK, 41U)) + aOrbiterB) + RotL64(aCarry, 53U)) + aPhaseDWandererUpdateSaltA[((aIndex + 17U)) & S_SALT1]);
            aWandererH = aWandererH ^ (((RotL64(aScatter, 27U) + RotL64(aOrbiterK, 35U)) + aOrbiterC) + aPhaseDWandererUpdateSaltF[((aIndex + 8U)) & S_SALT1]);
            aWandererB = aWandererB + (((RotL64(aCross, 53U) + RotL64(aOrbiterA, 12U)) + aOrbiterB) + aNonceWordN);
            aWandererI = aWandererI ^ (((RotL64(aIngress, 3U) + aOrbiterD) + RotL64(aOrbiterH, 5U)) + aNonceWordC);
            aWandererJ = aWandererJ + ((RotL64(aScatter, 43U) + RotL64(aOrbiterE, 47U)) + aOrbiterA);
            aWandererA = aWandererA ^ ((RotL64(aIngress, 21U) + aOrbiterB) + RotL64(aOrbiterD, 57U));
            aWandererG = aWandererG + (((RotL64(aCross, 35U) + RotL64(aOrbiterB, 27U)) + aOrbiterH) + RotL64(aCarry, 5U));
            //
            aCarry = aCarry + (RotL64(aWandererB, 56U) ^ aWandererE);
            aCarry = aCarry + (RotL64(aWandererI, 43U) ^ aWandererH);
            aCarry = aCarry + (RotL64(aWandererA, 29U) ^ aWandererG);
            aCarry = aCarry + RotL64(aWandererJ, 13U);
            aCarry = aCarry + RotL64(aIngress, 5U);
            aCarry = TwistMix64::DiffuseC(aCarry);
            //
            aInvestLaneA[aIndex] = aIngress;
        }
    
        // seed_loop_d loop 4
        // ingress from: aInvestLaneA, aWorkLaneA, aOperationLaneB
        // ingress directions: aInvestLaneA forward forced, aWorkLaneA forward forced, aOperationLaneB forward/backward random
        // cross from: aWorkLaneB, aExpandLaneD
        // cross directions: aWorkLaneB backward forced, aExpandLaneD backward/forward random
        // write to: aInvestLaneB
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aInvestLaneA[((aIndex + 21809U)) & S_BLOCK1], 27U) ^ RotL64(aWorkLaneA[((aIndex + 21684U)) & S_BLOCK1], 3U));
            aIngress ^= RotL64(aOperationLaneB[((S_BLOCK1 - aIndex + 17450U)) & S_BLOCK1], 57U);
            aIngress = TwistMix64::DiffuseB(((aIngress ^ aPhaseDDomainWordIngress) ^ aNonceWordJ));
            //
            aCross = RotL64(aWorkLaneB[((S_BLOCK1 - aIndex + 21201U)) & S_BLOCK1], 43U) ^ RotL64(aExpandLaneD[((S_BLOCK1 - aIndex + 20437U)) & S_BLOCK1], 27U);
            aCross = TwistMix64::DiffuseC(((aCross ^ aPhaseDDomainWordCross) ^ aNonceWordH));
            //
            aScatter = (RotL64(aIngress, 53U) + RotL64(aCross, 18U)) + (RotL64(aCarry, 3U) ^ RotL64(aPrevious, 35U));
            aScatter = TwistMix64::DiffuseA(((aScatter ^ aPhaseDDomainWordScatter) ^ aNonceWordI));
            //
            aOrbiterC = (((aWandererE + RotL64(aCross, 47U)) + RotL64(aCarry, 19U)) + 1708250618750199233U) + aPhaseDOrbiterAssignSaltF[((aIndex + 11U)) & S_SALT1];
            aOrbiterK = ((aWandererG + RotL64(aPrevious, 21U)) + RotL64(aCarry, 3U)) + 12009147777553691142U;
            aOrbiterF = ((aWandererI + RotL64(aIngress, 27U)) + 8393982703399156592U) + aPhaseDOrbiterAssignSaltB[(((31U - aIndex) + 21U)) & S_SALT1];
            aOrbiterI = (((aWandererK + RotL64(aScatter, 11U)) + RotL64(aCarry, 35U)) + 3247327098356831221U) + aNonceWordF;
            aOrbiterH = (aWandererC + RotL64(aIngress, 60U)) + 3403590155376353737U;
            aOrbiterA = (aWandererJ + RotL64(aScatter, 37U)) + 18197244558104735044U;
            aOrbiterD = ((aWandererF + RotL64(aCross, 53U)) + 3096253642040701606U) + aNonceWordG;
            //
            aOrbiterC = (aOrbiterC + aOrbiterK) + 8012692688785412179U;
            aOrbiterF = ((aOrbiterF ^ aOrbiterC) ^ 17531946907545680745U) ^ aPhaseDOrbiterUpdateSaltC[(((31U - aIndex) + 13U)) & S_SALT1];
            aOrbiterF = RotL64((aOrbiterF * 16510602981731506381U), 29U);
            //
            aOrbiterI = (aOrbiterI + aOrbiterH) + 17687695944270225817U;
            aOrbiterC = (aOrbiterC ^ aOrbiterI) ^ 16147773866007628769U;
            aOrbiterC = RotL64((aOrbiterC * 16926442582711557877U), 57U);
            //
            aOrbiterF = ((aOrbiterF + aOrbiterA) + 18244641303026196497U) + aNonceWordP;
            aOrbiterD = (((aOrbiterD ^ aOrbiterF) ^ 8839160526348897457U) ^ aPhaseDOrbiterUpdateSaltF[(((31U - aIndex) + 9U)) & S_SALT1]) ^ aNonceWordK;
            aOrbiterD = RotL64((aOrbiterD * 14268021129087663397U), 5U);
            //
            aOrbiterA = (aOrbiterA + aOrbiterD) + 10599266240854068246U;
            aOrbiterI = ((aOrbiterI ^ aOrbiterA) ^ 2056723540756216155U) ^ aPhaseDOrbiterUpdateSaltE[(((31U - aIndex) + 6U)) & S_SALT1];
            aOrbiterI = RotL64((aOrbiterI * 13311591601230386375U), 23U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterI) + 4629354220460621284U;
            aOrbiterH = (aOrbiterH ^ aOrbiterD) ^ 9505955649473204942U;
            aOrbiterH = RotL64((aOrbiterH * 17775391885312236187U), 47U);
            //
            aOrbiterK = ((aOrbiterK + aOrbiterF) + 17078153810088721310U) + aPhaseDOrbiterUpdateSaltA[((aIndex + 16U)) & S_SALT1];
            aOrbiterA = (aOrbiterA ^ aOrbiterK) ^ 9470436761716263000U;
            aOrbiterA = RotL64((aOrbiterA * 5431855497250357229U), 11U);
            //
            aOrbiterH = (aOrbiterH + aOrbiterC) + 3305863413630104742U;
            aOrbiterK = (aOrbiterK ^ aOrbiterH) ^ 14377172434239576161U;
            aOrbiterK = RotL64((aOrbiterK * 6880176890091033423U), 39U);
            //
            aIngress = RotL64(aOrbiterC, 37U) ^ aOrbiterI;
            aIngress = aIngress + (RotL64(aOrbiterK, 27U) ^ aOrbiterD);
            aIngress = aIngress + (RotL64(aOrbiterH, 11U) ^ aOrbiterA);
            aIngress = aIngress + RotL64(aOrbiterF, 51U);
            aIngress = TwistMix64::DiffuseB((aIngress + aScatter));
            //
            aWandererG = aWandererG ^ (((RotL64(aIngress, 52U) + aOrbiterD) + RotL64(aOrbiterI, 57U)) + aPhaseDWandererUpdateSaltB[((aIndex + 19U)) & S_SALT1]);
            aWandererE = aWandererE + (((RotL64(aScatter, 37U) + aOrbiterI) + RotL64(aOrbiterA, 3U)) + RotL64(aCarry, 53U));
            aWandererF = aWandererF ^ (((RotL64(aPrevious, 13U) + aOrbiterF) + RotL64(aOrbiterC, 19U)) + aNonceWordI);
            aWandererJ = aWandererJ + ((((RotL64(aCross, 27U) + RotL64(aOrbiterK, 12U)) + aOrbiterA) + aNonceWordC) + aPhaseDWandererUpdateSaltD[((aIndex + 5U)) & S_SALT1]);
            aWandererK = aWandererK ^ ((RotL64(aIngress, 5U) + RotL64(aOrbiterI, 29U)) + aOrbiterH);
            aWandererI = aWandererI + ((((RotL64(aPrevious, 43U) + aOrbiterH) + RotL64(aOrbiterC, 47U)) + RotL64(aCarry, 37U)) + aNonceWordD);
            aWandererC = aWandererC ^ ((RotL64(aScatter, 19U) + aOrbiterF) + RotL64(aOrbiterD, 39U));
            //
            aCarry = aCarry + (aWandererF ^ RotL64(aWandererK, 28U));
            aCarry = aCarry + (RotL64(aWandererG, 43U) ^ aWandererI);
            aCarry = aCarry + (aWandererC ^ RotL64(aWandererJ, 13U));
            aCarry = aCarry + RotL64(aWandererE, 57U);
            aCarry = aCarry + RotL64(aIngress, 48U);
            aCarry = TwistMix64::DiffuseA(aCarry);
            //
            aInvestLaneB[S_BLOCK1 - aIndex] = aIngress;
        }
    
        // seed_loop_d loop 5
        // ingress from: aInvestLaneB, aWorkLaneB, aOperationLaneC
        // ingress directions: aInvestLaneB forward forced, aWorkLaneB forward forced, aOperationLaneC forward/backward random
        // cross from: aInvestLaneA, aWorkLaneA
        // cross directions: aInvestLaneA backward forced, aWorkLaneA backward/forward random
        // write to: aInvestLaneC
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aInvestLaneB[((aIndex + 23021U)) & S_BLOCK1], 11U) ^ RotL64(aWorkLaneB[((aIndex + 24974U)) & S_BLOCK1], 60U));
            aIngress ^= RotL64(aOperationLaneC[((S_BLOCK1 - aIndex + 23532U)) & S_BLOCK1], 23U);
            aIngress = TwistMix64::DiffuseA(((aIngress ^ aPhaseDDomainWordIngress) ^ aNonceWordA));
            //
            aCross = RotL64(aInvestLaneA[((S_BLOCK1 - aIndex + 25547U)) & S_BLOCK1], 11U) ^ RotL64(aWorkLaneA[((aIndex + 23965U)) & S_BLOCK1], 57U);
            aCross = TwistMix64::DiffuseB(((aCross ^ aPhaseDDomainWordCross) ^ aNonceWordC));
            //
            aScatter = (RotL64(aCarry, 5U) + RotL64(aPrevious, 41U)) + (RotL64(aCross, 23U) ^ RotL64(aIngress, 54U));
            aScatter = TwistMix64::DiffuseA(((aScatter ^ aPhaseDDomainWordScatter) ^ aNonceWordF));
            //
            aOrbiterI = ((aWandererB + RotL64(aCross, 5U)) + RotL64(aCarry, 39U)) + 13854738573712660276U;
            aOrbiterJ = ((aWandererI + RotL64(aIngress, 27U)) + 16835460633412286294U) + aPhaseDOrbiterAssignSaltD[(((31U - aIndex) + 13U)) & S_SALT1];
            aOrbiterB = ((aWandererC + RotL64(aScatter, 41U)) + 6785859293758091931U) + aNonceWordO;
            aOrbiterK = (((aWandererG + RotL64(aPrevious, 53U)) + RotL64(aCarry, 5U)) + 126317283127992659U) + aNonceWordB;
            aOrbiterF = ((aWandererD + RotL64(aScatter, 47U)) + 7568963536291415413U) + aNonceWordM;
            aOrbiterH = (((aWandererJ + RotL64(aIngress, 35U)) + RotL64(aCarry, 27U)) + 12294016745653004819U) + aNonceWordH;
            aOrbiterC = ((aWandererA + RotL64(aPrevious, 18U)) + 18269588932920281147U) + aPhaseDOrbiterAssignSaltE[(((31U - aIndex) + 14U)) & S_SALT1];
            //
            aOrbiterI = ((aOrbiterI + aOrbiterJ) + 5872406424994751026U) + aPhaseDOrbiterUpdateSaltB[(((31U - aIndex) + 28U)) & S_SALT1];
            aOrbiterB = (aOrbiterB ^ aOrbiterI) ^ 7764434758831474129U;
            aOrbiterB = RotL64((aOrbiterB * 3772146788188420071U), 23U);
            //
            aOrbiterK = ((aOrbiterK + aOrbiterF) + 4804168969415573371U) + aNonceWordK;
            aOrbiterJ = ((aOrbiterJ ^ aOrbiterK) ^ 959601763507651280U) ^ aNonceWordG;
            aOrbiterJ = RotL64((aOrbiterJ * 4647396592804833217U), 41U);
            //
            aOrbiterF = (aOrbiterF + aOrbiterI) + 9257644462479293048U;
            aOrbiterH = (aOrbiterH ^ aOrbiterF) ^ 14332699366894494579U;
            aOrbiterH = RotL64((aOrbiterH * 8829304078930625541U), 5U);
            //
            aOrbiterC = (((aOrbiterC + aOrbiterK) + 10487012596470786004U) + aPhaseDOrbiterUpdateSaltD[(((31U - aIndex) + 23U)) & S_SALT1]) + aNonceWordL;
            aOrbiterI = (aOrbiterI ^ aOrbiterC) ^ 612729229562321440U;
            aOrbiterI = RotL64((aOrbiterI * 11380387280507726003U), 51U);
            //
            aOrbiterJ = (((aOrbiterJ + aOrbiterH) + 7845523921295625315U) + aPhaseDOrbiterUpdateSaltF[((aIndex + 19U)) & S_SALT1]) + aNonceWordP;
            aOrbiterC = ((aOrbiterC ^ aOrbiterJ) ^ 12742115479740024747U) ^ aPhaseDOrbiterUpdateSaltC[(((31U - aIndex) + 25U)) & S_SALT1];
            aOrbiterC = RotL64((aOrbiterC * 15578543510683986421U), 35U);
            //
            aOrbiterH = (aOrbiterH + aOrbiterB) + 10294667720904610944U;
            aOrbiterK = (aOrbiterK ^ aOrbiterH) ^ 14369711143154904567U;
            aOrbiterK = RotL64((aOrbiterK * 13753005602288309379U), 13U);
            //
            aOrbiterB = (aOrbiterB + aOrbiterC) + 10918344717497681894U;
            aOrbiterF = (aOrbiterF ^ aOrbiterB) ^ 18136794828308636957U;
            aOrbiterF = RotL64((aOrbiterF * 17899418637978002409U), 29U);
            //
            aIngress = RotL64(aOrbiterI, 29U) ^ aOrbiterJ;
            aIngress = aIngress + (aOrbiterF ^ RotL64(aOrbiterB, 57U));
            aIngress = aIngress + (aOrbiterK ^ RotL64(aOrbiterH, 51U));
            aIngress = aIngress + RotL64(aOrbiterC, 19U);
            aIngress = TwistMix64::DiffuseB((aIngress + aScatter));
            //
            aWandererB = aWandererB ^ (((RotL64(aIngress, 38U) + aOrbiterF) + RotL64(aOrbiterK, 29U)) + aNonceWordE);
            aWandererA = aWandererA + ((((RotL64(aScatter, 21U) + RotL64(aOrbiterI, 58U)) + aOrbiterH) + aNonceWordN) + aPhaseDWandererUpdateSaltE[((aIndex + 4U)) & S_SALT1]);
            aWandererC = aWandererC ^ ((((RotL64(aPrevious, 47U) + RotL64(aOrbiterJ, 37U)) + aOrbiterC) + aNonceWordF) + aPhaseDWandererUpdateSaltC[((aIndex + 17U)) & S_SALT1]);
            aWandererI = aWandererI + (((RotL64(aCross, 29U) + RotL64(aOrbiterK, 43U)) + aOrbiterC) + RotL64(aCarry, 53U));
            aWandererJ = aWandererJ ^ (((RotL64(aScatter, 57U) + RotL64(aOrbiterF, 5U)) + aOrbiterH) + aNonceWordI);
            aWandererG = aWandererG + (((RotL64(aIngress, 11U) + aOrbiterF) + RotL64(aOrbiterI, 19U)) + RotL64(aCarry, 5U));
            aWandererD = aWandererD ^ ((RotL64(aCross, 5U) + aOrbiterF) + RotL64(aOrbiterB, 11U));
            //
            aCarry = aCarry + (aWandererG ^ RotL64(aWandererJ, 57U));
            aCarry = aCarry + (aWandererB ^ RotL64(aWandererD, 5U));
            aCarry = aCarry + (aWandererI ^ RotL64(aWandererA, 10U));
            aCarry = aCarry + RotL64(aWandererC, 43U);
            aCarry = aCarry + RotL64(aIngress, 53U);
            aCarry = TwistMix64::DiffuseA(aCarry);
            //
            aInvestLaneC[aIndex] = aIngress;
        }
    
        // seed_loop_d loop 6
        // ingress from: aInvestLaneC, aInvestLaneA, aOperationLaneD
        // ingress directions: aInvestLaneC forward forced, aInvestLaneA forward forced, aOperationLaneD forward/backward random
        // cross from: aInvestLaneB, aExpandLaneB
        // cross directions: aInvestLaneB backward forced, aExpandLaneB backward/forward random
        // write to: aInvestLaneD
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aInvestLaneC[((aIndex + 30617U)) & S_BLOCK1], 28U) ^ RotL64(aInvestLaneA[((aIndex + 30412U)) & S_BLOCK1], 53U));
            aIngress ^= RotL64(aOperationLaneD[((aIndex + 30594U)) & S_BLOCK1], 37U);
            aIngress = TwistMix64::DiffuseC(((aIngress ^ aPhaseDDomainWordIngress) ^ aNonceWordC));
            //
            aCross = RotL64(aInvestLaneB[((S_BLOCK1 - aIndex + 28879U)) & S_BLOCK1], 4U) ^ RotL64(aExpandLaneB[((aIndex + 31892U)) & S_BLOCK1], 41U);
            aCross = TwistMix64::DiffuseA(((aCross ^ aPhaseDDomainWordCross) ^ aNonceWordM));
            //
            aScatter = (RotL64(aCarry, 19U) + RotL64(aIngress, 39U)) + (RotL64(aCross, 3U) ^ RotL64(aPrevious, 54U));
            aScatter = TwistMix64::DiffuseC(((aScatter ^ aPhaseDDomainWordScatter) ^ aNonceWordF));
            //
            aOrbiterJ = ((aWandererH + RotL64(aIngress, 51U)) + 7825479804710770560U) + aPhaseDOrbiterAssignSaltC[(((31U - aIndex) + 3U)) & S_SALT1];
            aOrbiterF = ((aWandererD + RotL64(aScatter, 58U)) + RotL64(aCarry, 57U)) + 5298124167101358123U;
            aOrbiterG = ((aWandererC + RotL64(aCross, 35U)) + RotL64(aCarry, 27U)) + 17774541024369233726U;
            aOrbiterH = ((aWandererF + RotL64(aPrevious, 21U)) + 7679371833537454082U) + aPhaseDOrbiterAssignSaltA[(((31U - aIndex) + 15U)) & S_SALT1];
            aOrbiterE = ((aWandererK + RotL64(aScatter, 43U)) + 5385914900748772224U) + aNonceWordD;
            aOrbiterA = ((aWandererG + RotL64(aIngress, 11U)) + RotL64(aCarry, 41U)) + 3879781930908486531U;
            aOrbiterC = ((aWandererE + RotL64(aPrevious, 3U)) + 659110346638873236U) + aNonceWordG;
            //
            aOrbiterJ = (((aOrbiterJ + aOrbiterF) + 10749021728538539749U) + aPhaseDOrbiterUpdateSaltC[((aIndex + 12U)) & S_SALT1]) + aNonceWordE;
            aOrbiterG = (aOrbiterG ^ aOrbiterJ) ^ 3631252455767429457U;
            aOrbiterG = RotL64((aOrbiterG * 8552825360915119613U), 51U);
            //
            aOrbiterH = ((aOrbiterH + aOrbiterG) + 2271978810960685021U) + aPhaseDOrbiterUpdateSaltD[((aIndex + 9U)) & S_SALT1];
            aOrbiterE = ((aOrbiterE ^ aOrbiterH) ^ 5963558780692551176U) ^ aNonceWordK;
            aOrbiterE = RotL64((aOrbiterE * 4772055335210781149U), 35U);
            //
            aOrbiterG = (aOrbiterG + aOrbiterA) + 974909966119198104U;
            aOrbiterC = ((aOrbiterC ^ aOrbiterG) ^ 9296998242911152296U) ^ aPhaseDOrbiterUpdateSaltF[(((31U - aIndex) + 5U)) & S_SALT1];
            aOrbiterC = RotL64((aOrbiterC * 2613629915877957661U), 13U);
            //
            aOrbiterA = (((aOrbiterA + aOrbiterJ) + 2245318466901521959U) + aPhaseDOrbiterUpdateSaltA[((aIndex + 7U)) & S_SALT1]) + aNonceWordA;
            aOrbiterH = (aOrbiterH ^ aOrbiterA) ^ 13391076374843288568U;
            aOrbiterH = RotL64((aOrbiterH * 18094558036982107419U), 57U);
            //
            aOrbiterC = (aOrbiterC + aOrbiterH) + 6184487746594236737U;
            aOrbiterF = (aOrbiterF ^ aOrbiterC) ^ 1563385912137291418U;
            aOrbiterF = RotL64((aOrbiterF * 4805455299959232321U), 29U);
            //
            aOrbiterE = (aOrbiterE + aOrbiterC) + 1744840092006498629U;
            aOrbiterJ = (aOrbiterJ ^ aOrbiterE) ^ 2100927276837188416U;
            aOrbiterJ = RotL64((aOrbiterJ * 3541788262067077997U), 41U);
            //
            aOrbiterF = (aOrbiterF + aOrbiterE) + 9998911862807246338U;
            aOrbiterA = (aOrbiterA ^ aOrbiterF) ^ 12239948725635220096U;
            aOrbiterA = RotL64((aOrbiterA * 7098620484129489129U), 23U);
            //
            aIngress = aOrbiterH ^ RotL64(aOrbiterJ, 29U);
            aIngress = aIngress + (aOrbiterF ^ RotL64(aOrbiterE, 57U));
            aIngress = aIngress + (aOrbiterA ^ RotL64(aOrbiterG, 41U));
            aIngress = aIngress + RotL64(aOrbiterC, 23U);
            aIngress = TwistMix64::DiffuseC((aIngress + aScatter));
            //
            aWandererH = aWandererH ^ (((RotL64(aIngress, 5U) + aOrbiterG) + RotL64(aOrbiterJ, 4U)) + aNonceWordO);
            aWandererF = aWandererF + (((RotL64(aScatter, 13U) + RotL64(aOrbiterJ, 53U)) + aOrbiterA) + RotL64(aCarry, 19U));
            aWandererC = aWandererC ^ (((RotL64(aCross, 58U) + aOrbiterH) + RotL64(aOrbiterF, 11U)) + aPhaseDWandererUpdateSaltF[(((31U - aIndex) + 17U)) & S_SALT1]);
            aWandererD = aWandererD + ((((RotL64(aPrevious, 27U) + aOrbiterH) + RotL64(aOrbiterG, 21U)) + RotL64(aCarry, 41U)) + aPhaseDWandererUpdateSaltA[((aIndex + 29U)) & S_SALT1]);
            aWandererE = aWandererE ^ (((RotL64(aScatter, 51U) + aOrbiterF) + RotL64(aOrbiterC, 35U)) + aNonceWordL);
            aWandererG = aWandererG + ((RotL64(aPrevious, 43U) + RotL64(aOrbiterF, 29U)) + aOrbiterE);
            aWandererK = aWandererK ^ ((RotL64(aIngress, 21U) + RotL64(aOrbiterH, 43U)) + aOrbiterE);
            //
            aCarry = aCarry + (RotL64(aWandererG, 6U) ^ aWandererF);
            aCarry = aCarry + (RotL64(aWandererH, 23U) ^ aWandererC);
            aCarry = aCarry + (RotL64(aWandererD, 43U) ^ aWandererE);
            aCarry = aCarry + RotL64(aWandererK, 35U);
            aCarry = aCarry + RotL64(aIngress, 19U);
            aCarry = TwistMix64::DiffuseC(aCarry);
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

void TwistExpander_Greezy_Arx::Seed_E(TwistWorkSpace *pWorkSpace,
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
    std::uint64_t aNonceWordA = TwistMix64::DiffuseA(pNonce * 0xB9008940EC0B81EBULL + 0x9025D5E15888E3EAULL);
    std::uint64_t aNonceWordB = TwistMix64::DiffuseA(pNonce * 0xC5EE51D0A06C26AFULL + 0xA679DD04263FF38FULL);
    std::uint64_t aNonceWordC = TwistMix64::DiffuseB(pNonce * 0xBC9F5E2390EF9185ULL + 0xA956F0180C0EE546ULL);
    std::uint64_t aNonceWordD = TwistMix64::DiffuseB(pNonce * 0x8A575D08205397CFULL + 0xCB555A165DA86C6DULL);
    std::uint64_t aNonceWordE = TwistMix64::DiffuseB(pNonce * 0xACE52D89A34BEC47ULL + 0x9AE62A16BFDD9A3DULL);
    std::uint64_t aNonceWordF = TwistMix64::DiffuseC(pNonce * 0xA6ED8DA5AABDBF07ULL + 0xE978CDDDB17C5D6AULL);
    std::uint64_t aNonceWordG = TwistMix64::DiffuseB(pNonce * 0xA0B125C02C26D363ULL + 0xE4D06F2C7C761635ULL);
    std::uint64_t aNonceWordH = TwistMix64::DiffuseA(pNonce * 0x905CCCF690720813ULL + 0xBF8F59A0642E484EULL);
    std::uint64_t aNonceWordI = TwistMix64::DiffuseC(pNonce * 0xD8F3FA71AA9D1039ULL + 0xC6BDB263E9D343EAULL);
    std::uint64_t aNonceWordJ = TwistMix64::DiffuseC(pNonce * 0x9334617F67E0C7C3ULL + 0xD35BC65FA11243D9ULL);
    std::uint64_t aNonceWordK = TwistMix64::DiffuseB(pNonce * 0x939C822830B9940BULL + 0xAA7B0B18B98F6988ULL);
    std::uint64_t aNonceWordL = TwistMix64::DiffuseB(pNonce * 0xAD463A191093B60FULL + 0xCDBF515EF45F3855ULL);
    std::uint64_t aNonceWordM = TwistMix64::DiffuseB(pNonce * 0xE67BC1FB8E07FD77ULL + 0xF42737860146564EULL);
    std::uint64_t aNonceWordN = TwistMix64::DiffuseB(pNonce * 0x971A533B633176BDULL + 0xBFC94466CB64189CULL);
    std::uint64_t aNonceWordO = TwistMix64::DiffuseA(pNonce * 0xD800A852816F34E5ULL + 0x8D75818B69C17947ULL);
    std::uint64_t aNonceWordP = TwistMix64::DiffuseC(pNonce * 0xD9472CB65F400A5BULL + 0x975720F6E0B367D3ULL);
    // GSeedRunSeed_E seed_loop_e (start)
    {
        // GSeedRunSeed_E seed_loop_e lane group
        // read from: aInvestLaneA, aInvestLaneB, aFireLaneA, aInvestLaneC, aInvestLaneD, aFireLaneB, aSnowLaneA, aFireLaneC, aFireLaneD, aSnowLaneB, aWorkLaneA, aOperationLaneA, aWorkLaneB, aOperationLaneB, aWorkLaneC, aOperationLaneC, aWorkLaneD
        // write to: aSnowLaneA, aSnowLaneB, aOperationLaneA, aOperationLaneB, aOperationLaneC, aOperationLaneD
    
        // seed_loop_e loop 1
        // ingress from: aInvestLaneA, aInvestLaneB, aFireLaneA
        // ingress directions: aInvestLaneA forward forced, aInvestLaneB forward forced, aFireLaneA forward/backward random
        // cross from: aInvestLaneC, aInvestLaneD, aFireLaneB
        // cross directions: aInvestLaneC backward forced, aInvestLaneD backward forced, aFireLaneB backward/forward random
        // write to: aSnowLaneA
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aInvestLaneA[((aIndex + 2904U)) & S_BLOCK1], 60U) ^ RotL64(aInvestLaneB[((aIndex + 776U)) & S_BLOCK1], 19U));
            aIngress ^= RotL64(aFireLaneA[((S_BLOCK1 - aIndex + 3960U)) & S_BLOCK1], 27U);
            aIngress = TwistMix64::DiffuseC(((aIngress ^ aPhaseEDomainWordIngress) ^ aNonceWordK));
            //
            aCross = (RotL64(aInvestLaneC[((S_BLOCK1 - aIndex + 5404U)) & S_BLOCK1], 5U) ^ RotL64(aInvestLaneD[((S_BLOCK1 - aIndex + 5460U)) & S_BLOCK1], 13U));
            aCross ^= RotL64(aFireLaneB[((aIndex + 5183U)) & S_BLOCK1], 22U);
            aCross = TwistMix64::DiffuseC(((aCross ^ aPhaseEDomainWordCross) ^ aNonceWordA));
            //
            aScatter = (RotL64(aIngress, 56U) ^ RotL64(aCarry, 27U)) ^ (RotL64(aCross, 5U) + RotL64(aPrevious, 39U));
            aScatter = TwistMix64::DiffuseA(((aScatter ^ aPhaseEDomainWordScatter) ^ aNonceWordH));
            //
            aOrbiterB = (aWandererB + RotL64(aPrevious, 34U)) + 12669015908335980355U;
            aOrbiterA = ((aWandererG + RotL64(aCross, 21U)) + RotL64(aCarry, 11U)) + 5438715179868613192U;
            aOrbiterI = ((aWandererK + RotL64(aIngress, 57U)) + RotL64(aCarry, 41U)) + 13172104448184536460U;
            aOrbiterG = ((aWandererC + RotL64(aScatter, 27U)) + 13421421503244744803U) + aPhaseEOrbiterAssignSaltD[((aIndex + 21U)) & S_SALT1];
            aOrbiterD = (((aWandererH + RotL64(aPrevious, 51U)) + RotL64(aCarry, 47U)) + 13327113302994856582U) + aPhaseEOrbiterAssignSaltA[(((31U - aIndex) + 12U)) & S_SALT1];
            aOrbiterF = (aWandererI + RotL64(aCross, 44U)) + 4671768205922454413U;
            aOrbiterK = (aWandererD + RotL64(aIngress, 39U)) + 5355759962838579929U;
            aOrbiterJ = (aWandererA + RotL64(aScatter, 41U)) + 6691720614265406851U;
            aOrbiterE = ((aWandererF + RotL64(aCross, 3U)) + 7063906424700911378U) + aNonceWordD;
            aOrbiterC = ((aWandererE + RotL64(aScatter, 47U)) + 17328616394166672263U) + aNonceWordJ;
            aOrbiterH = (aWandererJ + RotL64(aPrevious, 29U)) + 1542940602574207068U;
            //
            aOrbiterB = (aOrbiterB + aOrbiterA) + 7203866278803132454U;
            aOrbiterI = ((aOrbiterI ^ aOrbiterB) ^ 993485696233139264U) ^ aPhaseEOrbiterUpdateSaltC[(((31U - aIndex) + 9U)) & S_SALT1];
            aOrbiterI = RotL64((aOrbiterI * 11609009908810366447U), 51U);
            //
            aOrbiterG = ((aOrbiterG + aOrbiterD) + 15659679028507488331U) + aNonceWordO;
            aOrbiterF = (aOrbiterF ^ aOrbiterG) ^ 18321361454094675842U;
            aOrbiterF = RotL64((aOrbiterF * 3966860765622641843U), 41U);
            //
            aOrbiterK = (aOrbiterK + aOrbiterJ) + 9633319822696783352U;
            aOrbiterG = (aOrbiterG ^ aOrbiterK) ^ 3496559332232402963U;
            aOrbiterG = RotL64((aOrbiterG * 7772060229838162977U), 39U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterI) + 1918349708324205526U;
            aOrbiterE = (aOrbiterE ^ aOrbiterD) ^ 7701088402761359134U;
            aOrbiterE = RotL64((aOrbiterE * 9649485438465644795U), 47U);
            //
            aOrbiterJ = (aOrbiterJ + aOrbiterB) + 6006824348814439686U;
            aOrbiterD = ((aOrbiterD ^ aOrbiterJ) ^ 18088375375347012557U) ^ aPhaseEOrbiterUpdateSaltD[(((31U - aIndex) + 25U)) & S_SALT1];
            aOrbiterD = RotL64((aOrbiterD * 12801082943086128385U), 35U);
            //
            aOrbiterE = ((aOrbiterE + aOrbiterC) + 12816533373478543584U) + aPhaseEOrbiterUpdateSaltF[(((31U - aIndex) + 7U)) & S_SALT1];
            aOrbiterB = (aOrbiterB ^ aOrbiterE) ^ 17951880253818836433U;
            aOrbiterB = RotL64((aOrbiterB * 8935839101517220201U), 23U);
            //
            aOrbiterA = (aOrbiterA + aOrbiterG) + 11311632024372748238U;
            aOrbiterH = (aOrbiterH ^ aOrbiterA) ^ 9891349164779752351U;
            aOrbiterH = RotL64((aOrbiterH * 11405973752233193209U), 13U);
            //
            aOrbiterC = (aOrbiterC + aOrbiterK) + 711130292000437038U;
            aOrbiterA = ((aOrbiterA ^ aOrbiterC) ^ 17818800917771709681U) ^ aPhaseEOrbiterUpdateSaltE[((aIndex + 5U)) & S_SALT1];
            aOrbiterA = RotL64((aOrbiterA * 10567029732245868263U), 37U);
            //
            aOrbiterF = ((aOrbiterF + aOrbiterE) + 10188714200240109442U) + aNonceWordC;
            aOrbiterJ = (aOrbiterJ ^ aOrbiterF) ^ 9745615081760948652U;
            aOrbiterJ = RotL64((aOrbiterJ * 9321909462220134035U), 57U);
            //
            aOrbiterI = (aOrbiterI + aOrbiterH) + 6508703788527163965U;
            aOrbiterC = (aOrbiterC ^ aOrbiterI) ^ 7536038073603467381U;
            aOrbiterC = RotL64((aOrbiterC * 12015514242701199813U), 5U);
            //
            aOrbiterH = ((aOrbiterH + aOrbiterF) + 2793951597846756844U) + aNonceWordH;
            aOrbiterK = (aOrbiterK ^ aOrbiterH) ^ 12669015908335980355U;
            aOrbiterK = RotL64((aOrbiterK * 7355285540199760689U), 27U);
            //
            aIngress = RotL64(aOrbiterD, 3U) ^ aOrbiterJ;
            aIngress = aIngress + (RotL64(aOrbiterH, 44U) ^ aOrbiterE);
            aIngress = aIngress + (RotL64(aOrbiterI, 57U) ^ aOrbiterA);
            aIngress = aIngress + (RotL64(aOrbiterK, 29U) ^ aOrbiterB);
            aIngress = aIngress + (RotL64(aOrbiterC, 35U) ^ aOrbiterG);
            aIngress = aIngress + RotL64(aOrbiterF, 19U);
            aIngress = TwistMix64::DiffuseC((aIngress + aScatter));
            //
            aWandererA = aWandererA + (((((RotL64(aPrevious, 5U) + RotL64(aOrbiterH, 36U)) + aOrbiterD) + RotL64(aCarry, 21U)) + aNonceWordG) + aPhaseEWandererUpdateSaltE[(((31U - aIndex) + 10U)) & S_SALT1]);
            aWandererJ = aWandererJ ^ ((RotL64(aScatter, 41U) + aOrbiterK) + RotL64(aOrbiterD, 13U));
            aWandererK = aWandererK + ((RotL64(aIngress, 60U) + aOrbiterI) + RotL64(aOrbiterF, 27U));
            aWandererC = aWandererC ^ ((RotL64(aCross, 27U) + RotL64(aOrbiterC, 57U)) + aOrbiterF);
            aWandererE = aWandererE + ((RotL64(aPrevious, 35U) + RotL64(aOrbiterE, 11U)) + aOrbiterA);
            aWandererH = aWandererH ^ ((RotL64(aIngress, 21U) + RotL64(aOrbiterJ, 53U)) + aOrbiterF);
            aWandererD = aWandererD + (((RotL64(aCross, 43U) + aOrbiterA) + RotL64(aOrbiterH, 43U)) + aNonceWordB);
            aWandererB = aWandererB ^ ((RotL64(aScatter, 19U) + aOrbiterK) + RotL64(aOrbiterF, 29U));
            aWandererI = aWandererI + ((RotL64(aIngress, 13U) + RotL64(aOrbiterF, 40U)) + aOrbiterE);
            aWandererG = aWandererG ^ (((RotL64(aCross, 57U) + aOrbiterB) + RotL64(aOrbiterE, 51U)) + aPhaseEWandererUpdateSaltF[((aIndex + 27U)) & S_SALT1]);
            aWandererF = aWandererF + (((RotL64(aScatter, 38U) + RotL64(aOrbiterG, 5U)) + aOrbiterA) + RotL64(aCarry, 3U));
            //
            aCarry = aCarry + (RotL64(aWandererA, 46U) ^ aWandererC);
            aCarry = aCarry + (RotL64(aWandererB, 13U) ^ aWandererG);
            aCarry = aCarry + (aWandererJ ^ RotL64(aWandererH, 27U));
            aCarry = aCarry + (aWandererF ^ RotL64(aWandererI, 41U));
            aCarry = aCarry + (RotL64(aWandererK, 58U) ^ aWandererD);
            aCarry = aCarry + RotL64(aWandererE, 51U);
            aCarry = aCarry + RotL64(aIngress, 43U);
            aCarry = TwistMix64::DiffuseA(aCarry);
            //
            aSnowLaneA[aIndex] = aIngress;
        }
    
        // seed_loop_e loop 2
        // ingress from: aSnowLaneA, aInvestLaneC, aInvestLaneD, aFireLaneC
        // ingress directions: aSnowLaneA forward forced, aInvestLaneC forward forced, aInvestLaneD forward forced, aFireLaneC forward/backward random
        // cross from: aInvestLaneA, aInvestLaneB, aFireLaneD
        // cross directions: aInvestLaneA backward forced, aInvestLaneB backward forced, aFireLaneD backward/forward random
        // write to: aSnowLaneB
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aSnowLaneA[((aIndex + 10693U)) & S_BLOCK1], 43U) ^ RotL64(aInvestLaneC[((aIndex + 7153U)) & S_BLOCK1], 14U));
            aIngress ^= (RotL64(aInvestLaneD[((aIndex + 10522U)) & S_BLOCK1], 3U) ^ RotL64(aFireLaneC[((aIndex + 9545U)) & S_BLOCK1], 27U));
            aIngress = TwistMix64::DiffuseC(((aIngress ^ aPhaseEDomainWordIngress) ^ aNonceWordN));
            //
            aCross = (RotL64(aInvestLaneA[((S_BLOCK1 - aIndex + 9925U)) & S_BLOCK1], 20U) ^ RotL64(aInvestLaneB[((S_BLOCK1 - aIndex + 7508U)) & S_BLOCK1], 3U));
            aCross ^= RotL64(aFireLaneD[((aIndex + 5609U)) & S_BLOCK1], 37U);
            aCross = TwistMix64::DiffuseC(((aCross ^ aPhaseEDomainWordCross) ^ aNonceWordL));
            //
            aScatter = (RotL64(aIngress, 19U) + RotL64(aCarry, 5U)) + (RotL64(aPrevious, 53U) ^ RotL64(aCross, 40U));
            aScatter = TwistMix64::DiffuseB(((aScatter ^ aPhaseEDomainWordScatter) ^ aNonceWordD));
            //
            aOrbiterG = (aWandererF + RotL64(aScatter, 48U)) + 17074147006464019918U;
            aOrbiterD = ((aWandererG + RotL64(aCross, 41U)) + RotL64(aCarry, 47U)) + 10559516626129419928U;
            aOrbiterE = (aWandererC + RotL64(aIngress, 43U)) + 13280363679503946221U;
            aOrbiterC = (((aWandererH + RotL64(aPrevious, 37U)) + RotL64(aCarry, 11U)) + 17657115422132457413U) + aPhaseEOrbiterAssignSaltB[(((31U - aIndex) + 21U)) & S_SALT1];
            aOrbiterJ = ((aWandererB + RotL64(aScatter, 19U)) + 13325837013304973008U) + aNonceWordG;
            aOrbiterA = ((aWandererI + RotL64(aCross, 53U)) + 3059707750486106037U) + aPhaseEOrbiterAssignSaltE[(((31U - aIndex) + 11U)) & S_SALT1];
            aOrbiterK = (((aWandererK + RotL64(aIngress, 5U)) + RotL64(aCarry, 5U)) + 4529045702503050852U) + aNonceWordB;
            aOrbiterB = (aWandererE + RotL64(aPrevious, 51U)) + 10726578475550904292U;
            aOrbiterH = (aWandererJ + RotL64(aScatter, 39U)) + 14832537837996659885U;
            aOrbiterF = ((aWandererD + RotL64(aIngress, 11U)) + 220094417441809246U) + aNonceWordH;
            aOrbiterI = ((aWandererA + RotL64(aPrevious, 30U)) + 15343130035105342194U) + aNonceWordE;
            //
            aOrbiterG = (aOrbiterG + aOrbiterD) + 16592263353426409884U;
            aOrbiterE = (aOrbiterE ^ aOrbiterG) ^ 15649290906447931918U;
            aOrbiterE = RotL64((aOrbiterE * 8405875177836650731U), 51U);
            //
            aOrbiterC = (aOrbiterC + aOrbiterE) + 11437410545843708269U;
            aOrbiterJ = (((aOrbiterJ ^ aOrbiterC) ^ 5859769136073011444U) ^ aPhaseEOrbiterUpdateSaltF[(((31U - aIndex) + 14U)) & S_SALT1]) ^ aNonceWordJ;
            aOrbiterJ = RotL64((aOrbiterJ * 1065016088086441107U), 21U);
            //
            aOrbiterA = (aOrbiterA + aOrbiterK) + 15188064100307340341U;
            aOrbiterD = (aOrbiterD ^ aOrbiterA) ^ 4367466521843260049U;
            aOrbiterD = RotL64((aOrbiterD * 15916715854192820923U), 57U);
            //
            aOrbiterB = (aOrbiterB + aOrbiterG) + 8482617283860566845U;
            aOrbiterC = ((aOrbiterC ^ aOrbiterB) ^ 2585745804937342972U) ^ aPhaseEOrbiterUpdateSaltD[(((31U - aIndex) + 13U)) & S_SALT1];
            aOrbiterC = RotL64((aOrbiterC * 8267269625632139809U), 5U);
            //
            aOrbiterH = (aOrbiterH + aOrbiterJ) + 1687641344403425541U;
            aOrbiterB = (aOrbiterB ^ aOrbiterH) ^ 13667916445979421400U;
            aOrbiterB = RotL64((aOrbiterB * 8191322670355590027U), 19U);
            //
            aOrbiterF = ((aOrbiterF + aOrbiterH) + 7684258716388029228U) + aNonceWordO;
            aOrbiterK = (aOrbiterK ^ aOrbiterF) ^ 14764266202380443369U;
            aOrbiterK = RotL64((aOrbiterK * 1746254773647650741U), 41U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterI) + 12685190466981675661U;
            aOrbiterF = ((aOrbiterF ^ aOrbiterD) ^ 9958374400222383893U) ^ aPhaseEOrbiterUpdateSaltA[((aIndex + 20U)) & S_SALT1];
            aOrbiterF = RotL64((aOrbiterF * 12696606920219838929U), 27U);
            //
            aOrbiterJ = (aOrbiterJ + aOrbiterA) + 1352584794098160330U;
            aOrbiterG = ((aOrbiterG ^ aOrbiterJ) ^ 16057453941015251708U) ^ aPhaseEOrbiterUpdateSaltB[((aIndex + 3U)) & S_SALT1];
            aOrbiterG = RotL64((aOrbiterG * 6051546505117202495U), 3U);
            //
            aOrbiterE = (aOrbiterE + aOrbiterF) + 5642244742563733299U;
            aOrbiterA = ((aOrbiterA ^ aOrbiterE) ^ 2946279435712646692U) ^ aNonceWordI;
            aOrbiterA = RotL64((aOrbiterA * 3711867103848631343U), 35U);
            //
            aOrbiterI = (aOrbiterI + aOrbiterC) + 17305358424001395035U;
            aOrbiterH = (aOrbiterH ^ aOrbiterI) ^ 1831722001182742673U;
            aOrbiterH = RotL64((aOrbiterH * 13867284970939557547U), 11U);
            //
            aOrbiterK = (aOrbiterK + aOrbiterB) + 12354430852596737299U;
            aOrbiterI = (aOrbiterI ^ aOrbiterK) ^ 17074147006464019918U;
            aOrbiterI = RotL64((aOrbiterI * 17316050599218057961U), 23U);
            //
            aIngress = RotL64(aOrbiterJ, 19U) ^ aOrbiterG;
            aIngress = aIngress + (aOrbiterH ^ RotL64(aOrbiterE, 53U));
            aIngress = aIngress + (aOrbiterB ^ RotL64(aOrbiterK, 44U));
            aIngress = aIngress + (RotL64(aOrbiterF, 27U) ^ aOrbiterD);
            aIngress = aIngress + (aOrbiterC ^ RotL64(aOrbiterI, 57U));
            aIngress = aIngress + RotL64(aOrbiterA, 39U);
            aIngress = TwistMix64::DiffuseA((aIngress + aScatter));
            //
            aWandererG = aWandererG + (((RotL64(aPrevious, 37U) + aOrbiterI) + RotL64(aOrbiterC, 30U)) + RotL64(aCarry, 29U));
            aWandererF = aWandererF ^ (((RotL64(aCross, 18U) + RotL64(aOrbiterJ, 51U)) + aOrbiterG) + aPhaseEWandererUpdateSaltA[((aIndex + 28U)) & S_SALT1]);
            aWandererJ = aWandererJ + ((RotL64(aScatter, 29U) + aOrbiterC) + RotL64(aOrbiterB, 23U));
            aWandererE = aWandererE ^ ((RotL64(aIngress, 5U) + aOrbiterC) + RotL64(aOrbiterD, 37U));
            aWandererH = aWandererH + ((RotL64(aCross, 27U) + RotL64(aOrbiterF, 21U)) + aOrbiterE);
            aWandererI = aWandererI ^ (((RotL64(aScatter, 47U) + aOrbiterA) + RotL64(aOrbiterK, 11U)) + aNonceWordM);
            aWandererK = aWandererK + ((RotL64(aPrevious, 24U) + aOrbiterE) + RotL64(aOrbiterA, 44U));
            aWandererA = aWandererA ^ ((RotL64(aIngress, 21U) + RotL64(aOrbiterE, 27U)) + aOrbiterI);
            aWandererB = aWandererB + ((RotL64(aCross, 43U) + RotL64(aOrbiterJ, 53U)) + aOrbiterI);
            aWandererD = aWandererD ^ ((((RotL64(aScatter, 11U) + RotL64(aOrbiterH, 19U)) + aOrbiterF) + aNonceWordC) + aPhaseEWandererUpdateSaltB[(((31U - aIndex) + 8U)) & S_SALT1]);
            aWandererC = aWandererC + (((RotL64(aIngress, 13U) + RotL64(aOrbiterC, 39U)) + aOrbiterA) + RotL64(aCarry, 53U));
            //
            aCarry = aCarry + (RotL64(aWandererI, 29U) ^ aWandererD);
            aCarry = aCarry + (RotL64(aWandererB, 14U) ^ aWandererF);
            aCarry = aCarry + (RotL64(aWandererE, 41U) ^ aWandererK);
            aCarry = aCarry + (RotL64(aWandererH, 51U) ^ aWandererJ);
            aCarry = aCarry + (RotL64(aWandererC, 53U) ^ aWandererG);
            aCarry = aCarry + RotL64(aWandererA, 48U);
            aCarry = aCarry + RotL64(aIngress, 35U);
            aCarry = TwistMix64::DiffuseB(aCarry);
            //
            aSnowLaneB[S_BLOCK1 - aIndex] = aIngress;
        }
    
        // seed_loop_e loop 3
        // ingress from: aSnowLaneB, aInvestLaneA, aWorkLaneA
        // ingress directions: aSnowLaneB forward forced, aInvestLaneA forward forced, aWorkLaneA forward/backward random
        // cross from: aSnowLaneA, aInvestLaneC
        // cross directions: aSnowLaneA backward forced, aInvestLaneC backward/forward random
        // write to: aOperationLaneA
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aSnowLaneB[((aIndex + 11718U)) & S_BLOCK1], 39U) ^ RotL64(aInvestLaneA[((aIndex + 13908U)) & S_BLOCK1], 11U));
            aIngress ^= RotL64(aWorkLaneA[((aIndex + 11380U)) & S_BLOCK1], 56U);
            aIngress = TwistMix64::DiffuseB(((aIngress ^ aPhaseEDomainWordIngress) ^ aNonceWordB));
            //
            aCross = RotL64(aSnowLaneA[((S_BLOCK1 - aIndex + 12289U)) & S_BLOCK1], 54U) ^ RotL64(aInvestLaneC[((S_BLOCK1 - aIndex + 13861U)) & S_BLOCK1], 19U);
            aCross = TwistMix64::DiffuseB(((aCross ^ aPhaseEDomainWordCross) ^ aNonceWordF));
            //
            aScatter = (RotL64(aCarry, 38U) + RotL64(aPrevious, 57U)) ^ (RotL64(aIngress, 23U) ^ RotL64(aCross, 11U));
            aScatter = TwistMix64::DiffuseB(((aScatter ^ aPhaseEDomainWordScatter) ^ aNonceWordO));
            //
            aOrbiterA = ((aWandererH + RotL64(aIngress, 11U)) + 3339283916456813609U) + aPhaseEOrbiterAssignSaltC[(((31U - aIndex) + 12U)) & S_SALT1];
            aOrbiterH = (aWandererJ + RotL64(aCross, 13U)) + 11339086426180649584U;
            aOrbiterJ = ((aWandererD + RotL64(aPrevious, 29U)) + 16819191669329316585U) + aNonceWordE;
            aOrbiterC = ((aWandererA + RotL64(aScatter, 23U)) + RotL64(aCarry, 19U)) + 8361916937762630725U;
            aOrbiterF = ((aWandererI + RotL64(aIngress, 50U)) + 18031328374429899857U) + aNonceWordG;
            aOrbiterE = (aWandererC + RotL64(aPrevious, 35U)) + 18261756894092897276U;
            aOrbiterD = (((aWandererB + RotL64(aCross, 39U)) + 4250319792907645666U) + aPhaseEOrbiterAssignSaltF[((aIndex + 19U)) & S_SALT1]) + aNonceWordA;
            aOrbiterG = (aWandererF + RotL64(aScatter, 21U)) + 1492411503643460886U;
            aOrbiterB = ((aWandererK + RotL64(aCross, 19U)) + RotL64(aCarry, 47U)) + 17369549067879344180U;
            aOrbiterI = (((aWandererG + RotL64(aIngress, 27U)) + RotL64(aCarry, 11U)) + 7301713524358676722U) + aNonceWordI;
            aOrbiterK = (aWandererE + RotL64(aPrevious, 56U)) + 2985193736033012535U;
            //
            aOrbiterA = (aOrbiterA + aOrbiterH) + 14086975808140927408U;
            aOrbiterJ = (aOrbiterJ ^ aOrbiterA) ^ 10390516547834639800U;
            aOrbiterJ = RotL64((aOrbiterJ * 11441293212275890819U), 37U);
            //
            aOrbiterJ = (aOrbiterJ + aOrbiterC) + 18205555540941493267U;
            aOrbiterF = (aOrbiterF ^ aOrbiterJ) ^ 16967799565443938873U;
            aOrbiterF = RotL64((aOrbiterF * 3009081009044782443U), 57U);
            //
            aOrbiterE = (aOrbiterE + aOrbiterD) + 9209505304067579944U;
            aOrbiterG = ((aOrbiterG ^ aOrbiterE) ^ 3522631966146762306U) ^ aNonceWordD;
            aOrbiterG = RotL64((aOrbiterG * 3441982898533162599U), 23U);
            //
            aOrbiterC = (aOrbiterC + aOrbiterE) + 8811497120829041188U;
            aOrbiterB = (aOrbiterB ^ aOrbiterC) ^ 14707301680850257294U;
            aOrbiterB = RotL64((aOrbiterB * 11383709499376464085U), 41U);
            //
            aOrbiterF = (aOrbiterF + aOrbiterB) + 10080595991787801029U;
            aOrbiterD = (aOrbiterD ^ aOrbiterF) ^ 6822892187784299166U;
            aOrbiterD = RotL64((aOrbiterD * 7417016898027778287U), 11U);
            //
            aOrbiterG = (aOrbiterG + aOrbiterI) + 1981637172055758689U;
            aOrbiterH = ((aOrbiterH ^ aOrbiterG) ^ 16463077485583119324U) ^ aPhaseEOrbiterUpdateSaltF[(((31U - aIndex) + 4U)) & S_SALT1];
            aOrbiterH = RotL64((aOrbiterH * 2876782050665869121U), 35U);
            //
            aOrbiterK = ((aOrbiterK + aOrbiterF) + 8383837717361569465U) + aPhaseEOrbiterUpdateSaltD[((aIndex + 17U)) & S_SALT1];
            aOrbiterE = (aOrbiterE ^ aOrbiterK) ^ 2788511294985017326U;
            aOrbiterE = RotL64((aOrbiterE * 2809163242875130677U), 43U);
            //
            aOrbiterH = (aOrbiterH + aOrbiterK) + 3529607472855930041U;
            aOrbiterC = (((aOrbiterC ^ aOrbiterH) ^ 8850940802020173766U) ^ aPhaseEOrbiterUpdateSaltE[(((31U - aIndex) + 11U)) & S_SALT1]) ^ aNonceWordL;
            aOrbiterC = RotL64((aOrbiterC * 7821450253655655943U), 51U);
            //
            aOrbiterB = (aOrbiterB + aOrbiterG) + 7469160295100147267U;
            aOrbiterA = ((aOrbiterA ^ aOrbiterB) ^ 16973986572163482061U) ^ aPhaseEOrbiterUpdateSaltB[(((31U - aIndex) + 5U)) & S_SALT1];
            aOrbiterA = RotL64((aOrbiterA * 15660743778376905023U), 27U);
            //
            aOrbiterI = (aOrbiterI + aOrbiterJ) + 12371372942863279718U;
            aOrbiterK = (aOrbiterK ^ aOrbiterI) ^ 12098525148034303633U;
            aOrbiterK = RotL64((aOrbiterK * 11234127652230231751U), 5U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterA) + 5138683482859889480U;
            aOrbiterI = (aOrbiterI ^ aOrbiterD) ^ 3339283916456813609U;
            aOrbiterI = RotL64((aOrbiterI * 10975353228235695455U), 47U);
            //
            aIngress = aOrbiterA ^ RotL64(aOrbiterI, 11U);
            aIngress = aIngress + (aOrbiterJ ^ RotL64(aOrbiterG, 41U));
            aIngress = aIngress + (RotL64(aOrbiterE, 39U) ^ aOrbiterF);
            aIngress = aIngress + (aOrbiterC ^ RotL64(aOrbiterB, 52U));
            aIngress = aIngress + (aOrbiterH ^ RotL64(aOrbiterK, 37U));
            aIngress = aIngress + RotL64(aOrbiterD, 13U);
            aIngress = TwistMix64::DiffuseA((aIngress + aScatter));
            //
            aWandererH = aWandererH ^ (((RotL64(aScatter, 57U) + aOrbiterI) + RotL64(aOrbiterB, 12U)) + aNonceWordP);
            aWandererB = aWandererB + (((RotL64(aIngress, 37U) + aOrbiterB) + RotL64(aOrbiterK, 21U)) + aNonceWordC);
            aWandererF = aWandererF ^ ((RotL64(aCross, 5U) + RotL64(aOrbiterJ, 51U)) + aOrbiterF);
            aWandererC = aWandererC + ((RotL64(aPrevious, 13U) + RotL64(aOrbiterI, 27U)) + aOrbiterC);
            aWandererI = aWandererI ^ ((RotL64(aScatter, 11U) + aOrbiterI) + RotL64(aOrbiterJ, 29U));
            aWandererA = aWandererA + ((((RotL64(aIngress, 46U) + aOrbiterD) + RotL64(aOrbiterE, 34U)) + RotL64(aCarry, 39U)) + aPhaseEWandererUpdateSaltC[((aIndex + 24U)) & S_SALT1]);
            aWandererJ = aWandererJ ^ ((RotL64(aCross, 27U) + RotL64(aOrbiterI, 5U)) + aOrbiterE);
            aWandererK = aWandererK + ((((RotL64(aPrevious, 23U) + RotL64(aOrbiterJ, 37U)) + aOrbiterA) + RotL64(aCarry, 43U)) + aPhaseEWandererUpdateSaltD[((aIndex + 18U)) & S_SALT1]);
            aWandererG = aWandererG ^ ((RotL64(aScatter, 21U) + RotL64(aOrbiterB, 19U)) + aOrbiterA);
            aWandererE = aWandererE + ((RotL64(aPrevious, 60U) + RotL64(aOrbiterF, 47U)) + aOrbiterH);
            aWandererD = aWandererD ^ ((RotL64(aCross, 35U) + aOrbiterG) + RotL64(aOrbiterI, 23U));
            //
            aCarry = aCarry + (RotL64(aWandererH, 53U) ^ aWandererF);
            aCarry = aCarry + (aWandererG ^ RotL64(aWandererA, 41U));
            aCarry = aCarry + (RotL64(aWandererJ, 44U) ^ aWandererC);
            aCarry = aCarry + (RotL64(aWandererK, 19U) ^ aWandererE);
            aCarry = aCarry + (RotL64(aWandererI, 5U) ^ aWandererD);
            aCarry = aCarry + RotL64(aWandererB, 37U);
            aCarry = aCarry + RotL64(aIngress, 21U);
            aCarry = TwistMix64::DiffuseC(aCarry);
            //
            aOperationLaneA[aIndex] = aIngress;
        }
    
        // seed_loop_e loop 4
        // ingress from: aOperationLaneA, aSnowLaneA, aWorkLaneB
        // ingress directions: aOperationLaneA forward forced, aSnowLaneA forward forced, aWorkLaneB forward/backward random
        // cross from: aSnowLaneB, aInvestLaneD
        // cross directions: aSnowLaneB backward forced, aInvestLaneD backward/forward random
        // write to: aOperationLaneB
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aOperationLaneA[((aIndex + 20506U)) & S_BLOCK1], 5U) ^ RotL64(aSnowLaneA[((aIndex + 19434U)) & S_BLOCK1], 51U));
            aIngress ^= RotL64(aWorkLaneB[((aIndex + 19854U)) & S_BLOCK1], 21U);
            aIngress = TwistMix64::DiffuseC(((aIngress ^ aPhaseEDomainWordIngress) ^ aNonceWordD));
            //
            aCross = RotL64(aSnowLaneB[((S_BLOCK1 - aIndex + 18986U)) & S_BLOCK1], 24U) ^ RotL64(aInvestLaneD[((S_BLOCK1 - aIndex + 16920U)) & S_BLOCK1], 35U);
            aCross = TwistMix64::DiffuseC(((aCross ^ aPhaseEDomainWordCross) ^ aNonceWordM));
            //
            aScatter = (RotL64(aCross, 51U) ^ RotL64(aIngress, 3U)) ^ (RotL64(aPrevious, 35U) + RotL64(aCarry, 22U));
            aScatter = TwistMix64::DiffuseA(((aScatter ^ aPhaseEDomainWordScatter) ^ aNonceWordC));
            //
            aOrbiterI = (aWandererB + RotL64(aScatter, 57U)) + 9751314027302668907U;
            aOrbiterK = ((aWandererE + RotL64(aPrevious, 29U)) + 12175450995523107056U) + aNonceWordE;
            aOrbiterF = ((aWandererD + RotL64(aCross, 20U)) + RotL64(aCarry, 37U)) + 17519694958730119552U;
            aOrbiterE = (((aWandererI + RotL64(aIngress, 35U)) + RotL64(aCarry, 13U)) + 9093525527925682263U) + aPhaseEOrbiterAssignSaltD[(((31U - aIndex) + 24U)) & S_SALT1];
            aOrbiterJ = (aWandererG + RotL64(aCross, 39U)) + 3713831321786810138U;
            aOrbiterC = (((aWandererF + RotL64(aPrevious, 11U)) + RotL64(aCarry, 19U)) + 10108355209191835040U) + aNonceWordP;
            aOrbiterA = (aWandererC + RotL64(aScatter, 41U)) + 12956307447311314768U;
            aOrbiterH = (aWandererA + RotL64(aIngress, 47U)) + 1904298513945877359U;
            aOrbiterB = (aWandererJ + RotL64(aScatter, 51U)) + 4658049993308574460U;
            aOrbiterG = ((aWandererK + RotL64(aIngress, 18U)) + 9826333658248851902U) + aNonceWordJ;
            aOrbiterD = (((aWandererH + RotL64(aCross, 3U)) + 12058666914724365134U) + aPhaseEOrbiterAssignSaltA[((aIndex + 8U)) & S_SALT1]) + aNonceWordL;
            //
            aOrbiterI = ((aOrbiterI + aOrbiterK) + 2516574707110528099U) + aPhaseEOrbiterUpdateSaltC[(((31U - aIndex) + 28U)) & S_SALT1];
            aOrbiterF = ((aOrbiterF ^ aOrbiterI) ^ 13335308331049750235U) ^ aPhaseEOrbiterUpdateSaltE[(((31U - aIndex) + 3U)) & S_SALT1];
            aOrbiterF = RotL64((aOrbiterF * 5880227828760598587U), 41U);
            //
            aOrbiterE = (aOrbiterE + aOrbiterI) + 8230749255538495304U;
            aOrbiterJ = (aOrbiterJ ^ aOrbiterE) ^ 16536559486797811486U;
            aOrbiterJ = RotL64((aOrbiterJ * 7097036838156464969U), 23U);
            //
            aOrbiterC = (aOrbiterC + aOrbiterA) + 12387639130570188998U;
            aOrbiterI = (aOrbiterI ^ aOrbiterC) ^ 8459259798142872020U;
            aOrbiterI = RotL64((aOrbiterI * 8001346480955847013U), 43U);
            //
            aOrbiterF = ((aOrbiterF + aOrbiterH) + 16083784052002800300U) + aPhaseEOrbiterUpdateSaltA[((aIndex + 15U)) & S_SALT1];
            aOrbiterB = (aOrbiterB ^ aOrbiterF) ^ 1957284290736468379U;
            aOrbiterB = RotL64((aOrbiterB * 5046501301740813065U), 51U);
            //
            aOrbiterG = ((aOrbiterG + aOrbiterC) + 7349538179311335863U) + aPhaseEOrbiterUpdateSaltF[((aIndex + 7U)) & S_SALT1];
            aOrbiterE = (aOrbiterE ^ aOrbiterG) ^ 16395170077006105258U;
            aOrbiterE = RotL64((aOrbiterE * 4230485452156662763U), 13U);
            //
            aOrbiterK = (aOrbiterK + aOrbiterJ) + 3317652065873784068U;
            aOrbiterH = (aOrbiterH ^ aOrbiterK) ^ 5517155804799120700U;
            aOrbiterH = RotL64((aOrbiterH * 9789270651974719183U), 19U);
            //
            aOrbiterJ = (aOrbiterJ + aOrbiterF) + 5568525912112200094U;
            aOrbiterD = ((aOrbiterD ^ aOrbiterJ) ^ 9334250662962319598U) ^ aNonceWordB;
            aOrbiterD = RotL64((aOrbiterD * 5034887614541768961U), 39U);
            //
            aOrbiterA = (aOrbiterA + aOrbiterE) + 5641394627075994165U;
            aOrbiterK = (aOrbiterK ^ aOrbiterA) ^ 13524971148931512745U;
            aOrbiterK = RotL64((aOrbiterK * 3699457147759854357U), 11U);
            //
            aOrbiterH = (aOrbiterH + aOrbiterD) + 15124425790244392471U;
            aOrbiterG = (aOrbiterG ^ aOrbiterH) ^ 7896294947517723306U;
            aOrbiterG = RotL64((aOrbiterG * 7526632360108129915U), 27U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterB) + 15241686066829586263U;
            aOrbiterC = ((aOrbiterC ^ aOrbiterD) ^ 12099799118961857495U) ^ aNonceWordK;
            aOrbiterC = RotL64((aOrbiterC * 10456171163074630861U), 5U);
            //
            aOrbiterB = (aOrbiterB + aOrbiterG) + 17529688916595727188U;
            aOrbiterA = (aOrbiterA ^ aOrbiterB) ^ 9751314027302668907U;
            aOrbiterA = RotL64((aOrbiterA * 521888849578281715U), 47U);
            //
            aIngress = RotL64(aOrbiterF, 11U) ^ aOrbiterA;
            aIngress = aIngress + (RotL64(aOrbiterG, 51U) ^ aOrbiterB);
            aIngress = aIngress + (aOrbiterJ ^ RotL64(aOrbiterH, 21U));
            aIngress = aIngress + (RotL64(aOrbiterK, 34U) ^ aOrbiterC);
            aIngress = aIngress + (aOrbiterE ^ RotL64(aOrbiterD, 47U));
            aIngress = aIngress + RotL64(aOrbiterI, 13U);
            aIngress = TwistMix64::DiffuseC((aIngress + aScatter));
            //
            aWandererC = aWandererC + ((RotL64(aIngress, 41U) + aOrbiterC) + RotL64(aOrbiterI, 56U));
            aWandererG = aWandererG ^ (((RotL64(aPrevious, 23U) + RotL64(aOrbiterK, 43U)) + aOrbiterG) + aNonceWordN);
            aWandererA = aWandererA + ((RotL64(aScatter, 36U) + aOrbiterA) + RotL64(aOrbiterH, 11U));
            aWandererF = aWandererF ^ (((RotL64(aCross, 53U) + RotL64(aOrbiterG, 23U)) + aOrbiterJ) + aPhaseEWandererUpdateSaltE[(((31U - aIndex) + 22U)) & S_SALT1]);
            aWandererE = aWandererE + ((RotL64(aScatter, 21U) + RotL64(aOrbiterE, 37U)) + aOrbiterD);
            aWandererJ = aWandererJ ^ (((RotL64(aIngress, 3U) + aOrbiterK) + RotL64(aOrbiterD, 51U)) + aPhaseEWandererUpdateSaltF[((aIndex + 13U)) & S_SALT1]);
            aWandererD = aWandererD + (((RotL64(aPrevious, 19U) + aOrbiterG) + RotL64(aOrbiterF, 13U)) + RotL64(aCarry, 19U));
            aWandererK = aWandererK ^ ((RotL64(aCross, 11U) + aOrbiterD) + RotL64(aOrbiterB, 28U));
            aWandererH = aWandererH + (((RotL64(aIngress, 57U) + aOrbiterJ) + RotL64(aOrbiterK, 5U)) + RotL64(aCarry, 41U));
            aWandererI = aWandererI ^ ((RotL64(aPrevious, 38U) + RotL64(aOrbiterA, 21U)) + aOrbiterK);
            aWandererB = aWandererB + (((RotL64(aScatter, 5U) + RotL64(aOrbiterH, 47U)) + aOrbiterI) + aNonceWordH);
            //
            aCarry = aCarry + (RotL64(aWandererH, 18U) ^ aWandererD);
            aCarry = aCarry + (RotL64(aWandererK, 47U) ^ aWandererI);
            aCarry = aCarry + (aWandererG ^ RotL64(aWandererE, 29U));
            aCarry = aCarry + (RotL64(aWandererB, 37U) ^ aWandererF);
            aCarry = aCarry + (RotL64(aWandererJ, 60U) ^ aWandererC);
            aCarry = aCarry + RotL64(aWandererA, 43U);
            aCarry = aCarry + RotL64(aIngress, 27U);
            aCarry = TwistMix64::DiffuseC(aCarry);
            //
            aOperationLaneB[S_BLOCK1 - aIndex] = aIngress;
        }
    
        // seed_loop_e loop 5
        // ingress from: aOperationLaneB, aSnowLaneB, aWorkLaneC
        // ingress directions: aOperationLaneB forward forced, aSnowLaneB forward forced, aWorkLaneC forward/backward random
        // cross from: aOperationLaneA, aSnowLaneA
        // cross directions: aOperationLaneA backward forced, aSnowLaneA backward/forward random
        // write to: aOperationLaneC
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aOperationLaneB[((aIndex + 21960U)) & S_BLOCK1], 39U) ^ RotL64(aSnowLaneB[((aIndex + 27196U)) & S_BLOCK1], 60U));
            aIngress ^= RotL64(aWorkLaneC[((S_BLOCK1 - aIndex + 24968U)) & S_BLOCK1], 47U);
            aIngress = TwistMix64::DiffuseB(((aIngress ^ aPhaseEDomainWordIngress) ^ aNonceWordK));
            //
            aCross = RotL64(aOperationLaneA[((S_BLOCK1 - aIndex + 26479U)) & S_BLOCK1], 42U) ^ RotL64(aSnowLaneA[((aIndex + 25002U)) & S_BLOCK1], 11U);
            aCross = TwistMix64::DiffuseB(((aCross ^ aPhaseEDomainWordCross) ^ aNonceWordB));
            //
            aScatter = (RotL64(aCarry, 39U) + RotL64(aIngress, 53U)) + (RotL64(aPrevious, 10U) ^ RotL64(aCross, 23U));
            aScatter = TwistMix64::DiffuseB(((aScatter ^ aPhaseEDomainWordScatter) ^ aNonceWordF));
            //
            aOrbiterG = (aWandererF + RotL64(aScatter, 47U)) + 12849591986267890852U;
            aOrbiterE = (aWandererK + RotL64(aIngress, 21U)) + 8232614804696815750U;
            aOrbiterC = ((aWandererA + RotL64(aPrevious, 36U)) + 12141567259210877281U) + aNonceWordN;
            aOrbiterH = (aWandererC + RotL64(aCross, 39U)) + 2928641981037885644U;
            aOrbiterF = (aWandererJ + RotL64(aIngress, 51U)) + 980733350554783938U;
            aOrbiterJ = ((aWandererH + RotL64(aCross, 53U)) + RotL64(aCarry, 41U)) + 2683985177993350746U;
            aOrbiterD = ((((aWandererG + RotL64(aScatter, 29U)) + RotL64(aCarry, 3U)) + 14532148403815527355U) + aPhaseEOrbiterAssignSaltE[((aIndex + 17U)) & S_SALT1]) + aNonceWordO;
            aOrbiterK = (((aWandererI + RotL64(aPrevious, 26U)) + 7736296629433884203U) + aPhaseEOrbiterAssignSaltB[(((31U - aIndex) + 14U)) & S_SALT1]) + aNonceWordC;
            aOrbiterI = (aWandererD + RotL64(aCross, 43U)) + 10428437770166310549U;
            aOrbiterA = ((aWandererB + RotL64(aIngress, 57U)) + RotL64(aCarry, 11U)) + 18327174144859461029U;
            aOrbiterB = (aWandererE + RotL64(aScatter, 23U)) + 6810436935194432002U;
            //
            aOrbiterG = ((aOrbiterG + aOrbiterE) + 12606153309690753435U) + aPhaseEOrbiterUpdateSaltA[(((31U - aIndex) + 4U)) & S_SALT1];
            aOrbiterC = (aOrbiterC ^ aOrbiterG) ^ 17123256945895150555U;
            aOrbiterC = RotL64((aOrbiterC * 13469111258504672565U), 37U);
            //
            aOrbiterH = ((aOrbiterH + aOrbiterF) + 9057777759026189541U) + aNonceWordD;
            aOrbiterE = (aOrbiterE ^ aOrbiterH) ^ 16478485918911194442U;
            aOrbiterE = RotL64((aOrbiterE * 11054247078884894131U), 39U);
            //
            aOrbiterJ = (aOrbiterJ + aOrbiterD) + 18064460487552100483U;
            aOrbiterK = ((aOrbiterK ^ aOrbiterJ) ^ 11477276762421684083U) ^ aNonceWordA;
            aOrbiterK = RotL64((aOrbiterK * 3886501230380184395U), 43U);
            //
            aOrbiterE = (aOrbiterE + aOrbiterI) + 18318375441973295081U;
            aOrbiterA = ((aOrbiterA ^ aOrbiterE) ^ 13849305985380030986U) ^ aPhaseEOrbiterUpdateSaltD[((aIndex + 22U)) & S_SALT1];
            aOrbiterA = RotL64((aOrbiterA * 12962140243967824959U), 19U);
            //
            aOrbiterC = (aOrbiterC + aOrbiterA) + 10240409420338313641U;
            aOrbiterF = ((aOrbiterF ^ aOrbiterC) ^ 18360586077779529086U) ^ aNonceWordI;
            aOrbiterF = RotL64((aOrbiterF * 18196875422391501927U), 23U);
            //
            aOrbiterB = (aOrbiterB + aOrbiterG) + 16801797158622424257U;
            aOrbiterD = (aOrbiterD ^ aOrbiterB) ^ 4950305991208513887U;
            aOrbiterD = RotL64((aOrbiterD * 4437082499761416951U), 41U);
            //
            aOrbiterI = (aOrbiterI + aOrbiterK) + 15790878572843321918U;
            aOrbiterB = (aOrbiterB ^ aOrbiterI) ^ 9808781805065559728U;
            aOrbiterB = RotL64((aOrbiterB * 9394280083159162953U), 35U);
            //
            aOrbiterK = (aOrbiterK + aOrbiterH) + 11974996650410830731U;
            aOrbiterG = ((aOrbiterG ^ aOrbiterK) ^ 4955004489435232515U) ^ aPhaseEOrbiterUpdateSaltF[(((31U - aIndex) + 11U)) & S_SALT1];
            aOrbiterG = RotL64((aOrbiterG * 13301966529515483085U), 13U);
            //
            aOrbiterF = (aOrbiterF + aOrbiterJ) + 1187569634223338864U;
            aOrbiterI = ((aOrbiterI ^ aOrbiterF) ^ 5351017164244226367U) ^ aPhaseEOrbiterUpdateSaltE[(((31U - aIndex) + 6U)) & S_SALT1];
            aOrbiterI = RotL64((aOrbiterI * 14735674576470803699U), 57U);
            //
            aOrbiterA = (aOrbiterA + aOrbiterB) + 9587142385246940125U;
            aOrbiterJ = (aOrbiterJ ^ aOrbiterA) ^ 16253850371962732943U;
            aOrbiterJ = RotL64((aOrbiterJ * 3408021872390904463U), 29U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterC) + 14990060157351237661U;
            aOrbiterH = (aOrbiterH ^ aOrbiterD) ^ 12849591986267890852U;
            aOrbiterH = RotL64((aOrbiterH * 2158106726261981983U), 53U);
            //
            aIngress = aOrbiterD ^ RotL64(aOrbiterH, 27U);
            aIngress = aIngress + (aOrbiterK ^ RotL64(aOrbiterB, 3U));
            aIngress = aIngress + (aOrbiterA ^ RotL64(aOrbiterE, 47U));
            aIngress = aIngress + (aOrbiterC ^ RotL64(aOrbiterF, 6U));
            aIngress = aIngress + (RotL64(aOrbiterI, 41U) ^ aOrbiterJ);
            aIngress = aIngress + RotL64(aOrbiterG, 23U);
            aIngress = TwistMix64::DiffuseB((aIngress + aScatter));
            //
            aWandererF = aWandererF ^ ((RotL64(aPrevious, 47U) + aOrbiterG) + RotL64(aOrbiterJ, 58U));
            aWandererD = aWandererD + (((RotL64(aScatter, 5U) + aOrbiterK) + RotL64(aOrbiterC, 39U)) + aNonceWordL);
            aWandererK = aWandererK ^ ((RotL64(aIngress, 30U) + aOrbiterJ) + RotL64(aOrbiterE, 3U));
            aWandererB = aWandererB + (((RotL64(aCross, 43U) + aOrbiterD) + RotL64(aOrbiterG, 29U)) + RotL64(aCarry, 5U));
            aWandererI = aWandererI ^ ((RotL64(aIngress, 41U) + aOrbiterG) + RotL64(aOrbiterI, 46U));
            aWandererH = aWandererH + (((RotL64(aScatter, 23U) + aOrbiterB) + RotL64(aOrbiterF, 21U)) + RotL64(aCarry, 51U));
            aWandererE = aWandererE ^ (((RotL64(aCross, 28U) + RotL64(aOrbiterB, 43U)) + aOrbiterE) + aPhaseEWandererUpdateSaltA[(((31U - aIndex) + 27U)) & S_SALT1]);
            aWandererA = aWandererA + (((RotL64(aPrevious, 57U) + aOrbiterK) + RotL64(aOrbiterG, 37U)) + aNonceWordE);
            aWandererC = aWandererC ^ ((RotL64(aCross, 11U) + RotL64(aOrbiterD, 41U)) + aOrbiterE);
            aWandererJ = aWandererJ + (((RotL64(aPrevious, 35U) + aOrbiterH) + RotL64(aOrbiterF, 5U)) + aPhaseEWandererUpdateSaltB[((aIndex + 9U)) & S_SALT1]);
            aWandererG = aWandererG ^ (((RotL64(aScatter, 51U) + RotL64(aOrbiterJ, 19U)) + aOrbiterA) + aNonceWordF);
            //
            aCarry = aCarry + (RotL64(aWandererH, 13U) ^ aWandererJ);
            aCarry = aCarry + (aWandererB ^ RotL64(aWandererK, 36U));
            aCarry = aCarry + (aWandererF ^ RotL64(aWandererD, 41U));
            aCarry = aCarry + (RotL64(aWandererA, 27U) ^ aWandererE);
            aCarry = aCarry + (aWandererI ^ RotL64(aWandererC, 11U));
            aCarry = aCarry + RotL64(aWandererG, 29U);
            aCarry = aCarry + RotL64(aIngress, 6U);
            aCarry = TwistMix64::DiffuseB(aCarry);
            //
            aOperationLaneC[aIndex] = aIngress;
        }
    
        // seed_loop_e loop 6
        // ingress from: aOperationLaneC, aOperationLaneA, aWorkLaneD
        // ingress directions: aOperationLaneC forward forced, aOperationLaneA forward forced, aWorkLaneD forward/backward random
        // cross from: aOperationLaneB, aInvestLaneB
        // cross directions: aOperationLaneB backward forced, aInvestLaneB backward/forward random
        // write to: aOperationLaneD
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aOperationLaneC[((aIndex + 29815U)) & S_BLOCK1], 58U) ^ RotL64(aOperationLaneA[((aIndex + 31066U)) & S_BLOCK1], 3U));
            aIngress ^= RotL64(aWorkLaneD[((aIndex + 28806U)) & S_BLOCK1], 21U);
            aIngress = TwistMix64::DiffuseA(((aIngress ^ aPhaseEDomainWordIngress) ^ aNonceWordL));
            //
            aCross = RotL64(aOperationLaneB[((S_BLOCK1 - aIndex + 28210U)) & S_BLOCK1], 27U) ^ RotL64(aInvestLaneB[((S_BLOCK1 - aIndex + 30341U)) & S_BLOCK1], 51U);
            aCross = TwistMix64::DiffuseC(((aCross ^ aPhaseEDomainWordCross) ^ aNonceWordH));
            //
            aScatter = (RotL64(aIngress, 29U) + RotL64(aCarry, 53U)) + (RotL64(aCross, 41U) ^ RotL64(aPrevious, 14U));
            aScatter = TwistMix64::DiffuseA(((aScatter ^ aPhaseEDomainWordScatter) ^ aNonceWordA));
            //
            aOrbiterJ = (aWandererB + RotL64(aIngress, 46U)) + 3105313968748067810U;
            aOrbiterK = ((aWandererA + RotL64(aCross, 41U)) + 9977249451119627064U) + aNonceWordD;
            aOrbiterE = (aWandererD + RotL64(aPrevious, 19U)) + 17941392803495349366U;
            aOrbiterI = (aWandererH + RotL64(aScatter, 23U)) + 4279533326705471133U;
            aOrbiterD = (aWandererJ + RotL64(aPrevious, 11U)) + 13983828966811580039U;
            aOrbiterA = (((aWandererI + RotL64(aCross, 53U)) + RotL64(aCarry, 35U)) + 3983490984234810378U) + aPhaseEOrbiterAssignSaltC[((aIndex + 19U)) & S_SALT1];
            aOrbiterF = ((aWandererE + RotL64(aIngress, 51U)) + RotL64(aCarry, 5U)) + 308786542215259956U;
            aOrbiterH = (aWandererK + RotL64(aScatter, 39U)) + 8443607695364427037U;
            aOrbiterG = ((aWandererG + RotL64(aPrevious, 36U)) + 14939626441464340668U) + aNonceWordK;
            aOrbiterB = ((aWandererF + RotL64(aScatter, 29U)) + RotL64(aCarry, 23U)) + 9350693577306121110U;
            aOrbiterC = ((aWandererC + RotL64(aCross, 21U)) + 1717071159396961752U) + aPhaseEOrbiterAssignSaltF[(((31U - aIndex) + 14U)) & S_SALT1];
            //
            aOrbiterJ = ((aOrbiterJ + aOrbiterK) + 15911765265202100610U) + aNonceWordJ;
            aOrbiterE = (aOrbiterE ^ aOrbiterJ) ^ 14898546272333182767U;
            aOrbiterE = RotL64((aOrbiterE * 2674900543810733067U), 35U);
            //
            aOrbiterI = ((aOrbiterI + aOrbiterD) + 3560903518513465868U) + aPhaseEOrbiterUpdateSaltD[(((31U - aIndex) + 15U)) & S_SALT1];
            aOrbiterJ = ((aOrbiterJ ^ aOrbiterI) ^ 5367062725726860234U) ^ aPhaseEOrbiterUpdateSaltE[((aIndex + 26U)) & S_SALT1];
            aOrbiterJ = RotL64((aOrbiterJ * 8521908836601319553U), 39U);
            //
            aOrbiterA = ((aOrbiterA + aOrbiterI) + 15233321480618877327U) + aNonceWordP;
            aOrbiterF = (aOrbiterF ^ aOrbiterA) ^ 9288449812290126074U;
            aOrbiterF = RotL64((aOrbiterF * 6815298520404038519U), 5U);
            //
            aOrbiterH = (aOrbiterH + aOrbiterG) + 5504840529511585676U;
            aOrbiterI = (aOrbiterI ^ aOrbiterH) ^ 6825598386801620046U;
            aOrbiterI = RotL64((aOrbiterI * 11666542445846250077U), 53U);
            //
            aOrbiterB = ((aOrbiterB + aOrbiterH) + 6433024450721339470U) + aNonceWordI;
            aOrbiterA = (aOrbiterA ^ aOrbiterB) ^ 97934156644929458U;
            aOrbiterA = RotL64((aOrbiterA * 8630530773006923215U), 3U);
            //
            aOrbiterC = (aOrbiterC + aOrbiterE) + 3260053604798744515U;
            aOrbiterH = (aOrbiterH ^ aOrbiterC) ^ 16539416623243059076U;
            aOrbiterH = RotL64((aOrbiterH * 12199577351166064503U), 23U);
            //
            aOrbiterE = (aOrbiterE + aOrbiterB) + 9814290051339038920U;
            aOrbiterG = ((aOrbiterG ^ aOrbiterE) ^ 13280156404507444041U) ^ aPhaseEOrbiterUpdateSaltB[(((31U - aIndex) + 27U)) & S_SALT1];
            aOrbiterG = RotL64((aOrbiterG * 15269010043398910061U), 51U);
            //
            aOrbiterF = (aOrbiterF + aOrbiterJ) + 11853942590993546833U;
            aOrbiterC = (aOrbiterC ^ aOrbiterF) ^ 13207869904312989977U;
            aOrbiterC = RotL64((aOrbiterC * 15503461937625795969U), 37U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterF) + 14536032167989376750U;
            aOrbiterK = (aOrbiterK ^ aOrbiterD) ^ 3693282775047432356U;
            aOrbiterK = RotL64((aOrbiterK * 5290349323647887877U), 27U);
            //
            aOrbiterK = ((aOrbiterK + aOrbiterC) + 5803176485246280271U) + aPhaseEOrbiterUpdateSaltA[((aIndex + 11U)) & S_SALT1];
            aOrbiterB = (aOrbiterB ^ aOrbiterK) ^ 16702526675475954730U;
            aOrbiterB = RotL64((aOrbiterB * 13695676754973145769U), 41U);
            //
            aOrbiterG = ((aOrbiterG + aOrbiterA) + 16454171963808313625U) + aNonceWordB;
            aOrbiterD = (aOrbiterD ^ aOrbiterG) ^ 3105313968748067810U;
            aOrbiterD = RotL64((aOrbiterD * 16572687178789102843U), 11U);
            //
            aIngress = aOrbiterE ^ RotL64(aOrbiterI, 39U);
            aIngress = aIngress + (RotL64(aOrbiterG, 23U) ^ aOrbiterB);
            aIngress = aIngress + (RotL64(aOrbiterF, 21U) ^ aOrbiterA);
            aIngress = aIngress + (RotL64(aOrbiterD, 57U) ^ aOrbiterJ);
            aIngress = aIngress + (RotL64(aOrbiterK, 41U) ^ aOrbiterC);
            aIngress = aIngress + RotL64(aOrbiterH, 19U);
            aIngress = TwistMix64::DiffuseC((aIngress + aScatter));
            //
            aWandererI = aWandererI ^ ((RotL64(aPrevious, 29U) + RotL64(aOrbiterH, 46U)) + aOrbiterI);
            aWandererH = aWandererH + (((RotL64(aScatter, 3U) + RotL64(aOrbiterB, 11U)) + aOrbiterK) + RotL64(aCarry, 47U));
            aWandererA = aWandererA ^ (((RotL64(aCross, 11U) + aOrbiterC) + RotL64(aOrbiterA, 51U)) + aNonceWordC);
            aWandererG = aWandererG + ((RotL64(aIngress, 27U) + RotL64(aOrbiterK, 39U)) + aOrbiterA);
            aWandererB = aWandererB ^ (((RotL64(aScatter, 58U) + RotL64(aOrbiterG, 27U)) + aOrbiterF) + aNonceWordG);
            aWandererJ = aWandererJ + ((((RotL64(aCross, 53U) + aOrbiterG) + RotL64(aOrbiterC, 53U)) + RotL64(aCarry, 3U)) + aPhaseEWandererUpdateSaltD[(((31U - aIndex) + 5U)) & S_SALT1]);
            aWandererC = aWandererC ^ (((RotL64(aIngress, 5U) + aOrbiterJ) + RotL64(aOrbiterB, 4U)) + aPhaseEWandererUpdateSaltC[((aIndex + 24U)) & S_SALT1]);
            aWandererD = aWandererD + ((RotL64(aPrevious, 47U) + RotL64(aOrbiterF, 29U)) + aOrbiterD);
            aWandererK = aWandererK ^ (((RotL64(aIngress, 51U) + aOrbiterI) + RotL64(aOrbiterC, 13U)) + aNonceWordM);
            aWandererE = aWandererE + ((RotL64(aPrevious, 21U) + RotL64(aOrbiterG, 37U)) + aOrbiterE);
            aWandererF = aWandererF ^ ((RotL64(aScatter, 14U) + RotL64(aOrbiterE, 43U)) + aOrbiterD);
            //
            aCarry = aCarry + (RotL64(aWandererF, 27U) ^ aWandererG);
            aCarry = aCarry + (aWandererK ^ RotL64(aWandererB, 48U));
            aCarry = aCarry + (RotL64(aWandererJ, 5U) ^ aWandererA);
            aCarry = aCarry + (aWandererI ^ RotL64(aWandererC, 53U));
            aCarry = aCarry + (aWandererD ^ RotL64(aWandererE, 57U));
            aCarry = aCarry + RotL64(aWandererH, 18U);
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

void TwistExpander_Greezy_Arx::Seed_F(TwistWorkSpace *pWorkSpace,
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
    std::uint64_t aNonceWordA = TwistMix64::DiffuseA(pNonce * 0xD5BDB2F8700E350FULL + 0xF21E6EB6289D77ECULL);
    std::uint64_t aNonceWordB = TwistMix64::DiffuseB(pNonce * 0xBB5DB5634144E97BULL + 0x899393215528696AULL);
    std::uint64_t aNonceWordC = TwistMix64::DiffuseC(pNonce * 0xE8D3C9AC6C3AFDEFULL + 0x817DD520FDE6362AULL);
    std::uint64_t aNonceWordD = TwistMix64::DiffuseB(pNonce * 0xF225DE9C599CD4D1ULL + 0xEC370FE47E0A3FC5ULL);
    std::uint64_t aNonceWordE = TwistMix64::DiffuseB(pNonce * 0x93F1EAB16BFC0211ULL + 0xBC64EB0BCC7E9E9EULL);
    std::uint64_t aNonceWordF = TwistMix64::DiffuseB(pNonce * 0xD518CDECE8F56433ULL + 0x9EF13B807F6FF3FEULL);
    std::uint64_t aNonceWordG = TwistMix64::DiffuseC(pNonce * 0xC45EEDD8D935924DULL + 0x835D52A7864EA81AULL);
    std::uint64_t aNonceWordH = TwistMix64::DiffuseA(pNonce * 0x830CF17BE63D0C09ULL + 0xC233ADFEC25E9118ULL);
    std::uint64_t aNonceWordI = TwistMix64::DiffuseC(pNonce * 0xD439ECEC0AF44AC5ULL + 0xA8F168D6862F1411ULL);
    std::uint64_t aNonceWordJ = TwistMix64::DiffuseB(pNonce * 0xEF48413381D8A6EDULL + 0xBBA23CF69D7C3515ULL);
    std::uint64_t aNonceWordK = TwistMix64::DiffuseC(pNonce * 0x96BB7FDEB33E8C0FULL + 0xECDEC69FBC125595ULL);
    std::uint64_t aNonceWordL = TwistMix64::DiffuseA(pNonce * 0x8CA9FC6538EDD20BULL + 0xCEB6EEB0E825D630ULL);
    std::uint64_t aNonceWordM = TwistMix64::DiffuseA(pNonce * 0x95C0058147983A75ULL + 0xDE60E250574D8C6AULL);
    std::uint64_t aNonceWordN = TwistMix64::DiffuseC(pNonce * 0xE54B26157306265DULL + 0xEC6DBC36119CA71CULL);
    std::uint64_t aNonceWordO = TwistMix64::DiffuseB(pNonce * 0x8E769CD55CFED88BULL + 0xD7EBA6008A77F75AULL);
    std::uint64_t aNonceWordP = TwistMix64::DiffuseC(pNonce * 0x82108A65156A2021ULL + 0xC3FC4447607ED93AULL);
    // GSeedRunSeed_F seed_loop_f (start)
    {
        // GSeedRunSeed_F seed_loop_f lane group
        // read from: aOperationLaneA, aOperationLaneB, aFireLaneA, aOperationLaneC, aOperationLaneD, aFireLaneB, aSnowLaneA, aFireLaneC, aFireLaneD, aSnowLaneB, aInvestLaneA, aExpandLaneA, aInvestLaneB, aExpandLaneB, aInvestLaneC, aExpandLaneC, aInvestLaneD
        // write to: aSnowLaneA, aSnowLaneB, aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD
    
        // seed_loop_f loop 1
        // ingress from: aOperationLaneA, aOperationLaneB, aFireLaneA
        // ingress directions: aOperationLaneA forward forced, aOperationLaneB forward forced, aFireLaneA forward/backward random
        // cross from: aOperationLaneC, aOperationLaneD, aFireLaneB
        // cross directions: aOperationLaneC backward forced, aOperationLaneD backward forced, aFireLaneB backward/forward random
        // write to: aSnowLaneA
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aOperationLaneA[((aIndex + 3807U)) & S_BLOCK1], 27U) ^ RotL64(aOperationLaneB[((aIndex + 3483U)) & S_BLOCK1], 12U));
            aIngress ^= RotL64(aFireLaneA[((S_BLOCK1 - aIndex + 4148U)) & S_BLOCK1], 41U);
            aIngress = TwistMix64::DiffuseB(((aIngress ^ aPhaseFDomainWordIngress) ^ aNonceWordN));
            //
            aCross = (RotL64(aOperationLaneC[((S_BLOCK1 - aIndex + 4642U)) & S_BLOCK1], 57U) ^ RotL64(aOperationLaneD[((S_BLOCK1 - aIndex + 3376U)) & S_BLOCK1], 18U));
            aCross ^= RotL64(aFireLaneB[((S_BLOCK1 - aIndex + 2967U)) & S_BLOCK1], 39U);
            aCross = TwistMix64::DiffuseC(((aCross ^ aPhaseFDomainWordCross) ^ aNonceWordA));
            //
            aScatter = (RotL64(aCross, 41U) ^ RotL64(aPrevious, 28U)) + (RotL64(aCarry, 57U) ^ RotL64(aIngress, 13U));
            aScatter = TwistMix64::DiffuseC(((aScatter ^ aPhaseFDomainWordScatter) ^ aNonceWordG));
            //
            aOrbiterF = ((aWandererG + RotL64(aPrevious, 18U)) + 5041131702736607991U) + aNonceWordK;
            aOrbiterK = ((aWandererA + RotL64(aIngress, 57U)) + 9295010428212681446U) + aNonceWordB;
            aOrbiterC = (aWandererJ + RotL64(aCross, 23U)) + 6235875895358766017U;
            aOrbiterB = ((aWandererK + RotL64(aScatter, 41U)) + RotL64(aCarry, 35U)) + 2622227802531866918U;
            aOrbiterG = ((aWandererB + RotL64(aIngress, 11U)) + RotL64(aCarry, 53U)) + 3888894734834524972U;
            aOrbiterH = (aWandererD + RotL64(aScatter, 27U)) + 241682012014701753U;
            aOrbiterA = ((aWandererF + RotL64(aCross, 47U)) + 15758000422451568079U) + aPhaseFOrbiterAssignSaltB[(((31U - aIndex) + 25U)) & S_SALT1];
            aOrbiterD = (aWandererH + RotL64(aPrevious, 4U)) + 2061944548396976912U;
            aOrbiterI = (((aWandererI + RotL64(aCross, 51U)) + RotL64(aCarry, 5U)) + 8177144990755754531U) + aPhaseFOrbiterAssignSaltF[(((31U - aIndex) + 12U)) & S_SALT1];
            //
            aOrbiterF = (aOrbiterF + aOrbiterK) + 554978075608818497U;
            aOrbiterC = (aOrbiterC ^ aOrbiterF) ^ 250408260560714933U;
            aOrbiterC = RotL64((aOrbiterC * 1295379390497107727U), 11U);
            //
            aOrbiterB = (aOrbiterB + aOrbiterG) + 8700027645880997552U;
            aOrbiterK = ((aOrbiterK ^ aOrbiterB) ^ 10026130047465480902U) ^ aPhaseFOrbiterUpdateSaltA[((aIndex + 18U)) & S_SALT1];
            aOrbiterK = RotL64((aOrbiterK * 12417270861933696623U), 35U);
            //
            aOrbiterH = (aOrbiterH + aOrbiterC) + 9785843014096326696U;
            aOrbiterB = (aOrbiterB ^ aOrbiterH) ^ 9998582683258411251U;
            aOrbiterB = RotL64((aOrbiterB * 7197956237569462269U), 57U);
            //
            aOrbiterC = ((aOrbiterC + aOrbiterA) + 13817734599383455151U) + aNonceWordJ;
            aOrbiterG = ((aOrbiterG ^ aOrbiterC) ^ 6647207154174092691U) ^ aPhaseFOrbiterUpdateSaltE[((aIndex + 4U)) & S_SALT1];
            aOrbiterG = RotL64((aOrbiterG * 1578528131687283531U), 47U);
            //
            aOrbiterK = (aOrbiterK + aOrbiterD) + 4957715980509035719U;
            aOrbiterA = ((aOrbiterA ^ aOrbiterK) ^ 4994885315786213197U) ^ aPhaseFOrbiterUpdateSaltC[(((31U - aIndex) + 15U)) & S_SALT1];
            aOrbiterA = RotL64((aOrbiterA * 5676683798126497011U), 5U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterF) + 5072908311783966503U;
            aOrbiterH = (aOrbiterH ^ aOrbiterD) ^ 5535039946192891515U;
            aOrbiterH = RotL64((aOrbiterH * 2989412783482309753U), 51U);
            //
            aOrbiterA = ((aOrbiterA + aOrbiterH) + 6594577050344146271U) + aNonceWordH;
            aOrbiterI = ((aOrbiterI ^ aOrbiterA) ^ 8750154123258714856U) ^ aNonceWordC;
            aOrbiterI = RotL64((aOrbiterI * 6942158167127532003U), 43U);
            //
            aOrbiterI = (((aOrbiterI + aOrbiterB) + 3514769314840874873U) + aPhaseFOrbiterUpdateSaltF[((aIndex + 11U)) & S_SALT1]) + aNonceWordP;
            aOrbiterF = (aOrbiterF ^ aOrbiterI) ^ 8626045200273524281U;
            aOrbiterF = RotL64((aOrbiterF * 4315441782689789689U), 29U);
            //
            aOrbiterG = (aOrbiterG + aOrbiterI) + 8524870284841706517U;
            aOrbiterD = (aOrbiterD ^ aOrbiterG) ^ 1841819423572964209U;
            aOrbiterD = RotL64((aOrbiterD * 9802481758007234681U), 19U);
            //
            aIngress = RotL64(aOrbiterF, 37U) ^ aOrbiterK;
            aIngress = aIngress + (RotL64(aOrbiterB, 27U) ^ aOrbiterC);
            aIngress = aIngress + (aOrbiterA ^ RotL64(aOrbiterH, 18U));
            aIngress = aIngress + (aOrbiterI ^ RotL64(aOrbiterG, 47U));
            aIngress = aIngress + RotL64(aOrbiterD, 3U);
            aIngress = TwistMix64::DiffuseC((aIngress + aScatter));
            //
            aWandererI = aWandererI ^ (((RotL64(aPrevious, 26U) + aOrbiterK) + RotL64(aOrbiterD, 11U)) + aNonceWordD);
            aWandererG = aWandererG + (((((RotL64(aScatter, 51U) + RotL64(aOrbiterA, 24U)) + aOrbiterF) + RotL64(aCarry, 21U)) + aNonceWordM) + aPhaseFWandererUpdateSaltC[((aIndex + 5U)) & S_SALT1]);
            aWandererA = aWandererA ^ (((RotL64(aCross, 19U) + RotL64(aOrbiterB, 29U)) + aOrbiterH) + aNonceWordE);
            aWandererF = aWandererF + (((RotL64(aIngress, 57U) + RotL64(aOrbiterI, 37U)) + aOrbiterH) + aNonceWordF);
            aWandererK = aWandererK ^ ((RotL64(aPrevious, 11U) + aOrbiterG) + RotL64(aOrbiterB, 47U));
            aWandererJ = aWandererJ + ((RotL64(aScatter, 41U) + aOrbiterF) + RotL64(aOrbiterG, 19U));
            aWandererD = aWandererD ^ (((RotL64(aIngress, 5U) + aOrbiterH) + RotL64(aOrbiterC, 41U)) + aPhaseFWandererUpdateSaltB[((aIndex + 13U)) & S_SALT1]);
            aWandererB = aWandererB + (((RotL64(aCross, 30U) + aOrbiterA) + RotL64(aOrbiterK, 54U)) + RotL64(aCarry, 41U));
            aWandererH = aWandererH ^ ((RotL64(aIngress, 37U) + aOrbiterA) + RotL64(aOrbiterH, 3U));
            //
            aCarry = aCarry + (aWandererH ^ RotL64(aWandererI, 13U));
            aCarry = aCarry + (aWandererD ^ RotL64(aWandererF, 60U));
            aCarry = aCarry + (RotL64(aWandererB, 37U) ^ aWandererG);
            aCarry = aCarry + (aWandererJ ^ RotL64(aWandererK, 57U));
            aCarry = aCarry + RotL64(aWandererA, 47U);
            aCarry = aCarry + RotL64(aIngress, 29U);
            aCarry = TwistMix64::DiffuseA(aCarry);
            //
            aSnowLaneA[aIndex] = aIngress;
        }
    
        // seed_loop_f loop 2
        // ingress from: aSnowLaneA, aOperationLaneC, aOperationLaneD, aFireLaneC
        // ingress directions: aSnowLaneA forward forced, aOperationLaneC forward forced, aOperationLaneD forward forced, aFireLaneC forward/backward random
        // cross from: aOperationLaneA, aOperationLaneB, aFireLaneD
        // cross directions: aOperationLaneA backward forced, aOperationLaneB backward forced, aFireLaneD backward/forward random
        // write to: aSnowLaneB
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aSnowLaneA[((aIndex + 6876U)) & S_BLOCK1], 24U) ^ RotL64(aOperationLaneC[((aIndex + 8522U)) & S_BLOCK1], 47U));
            aIngress ^= (RotL64(aOperationLaneD[((aIndex + 10589U)) & S_BLOCK1], 57U) ^ RotL64(aFireLaneC[((aIndex + 5864U)) & S_BLOCK1], 11U));
            aIngress = TwistMix64::DiffuseC(((aIngress ^ aPhaseFDomainWordIngress) ^ aNonceWordA));
            //
            aCross = (RotL64(aOperationLaneA[((S_BLOCK1 - aIndex + 5791U)) & S_BLOCK1], 23U) ^ RotL64(aOperationLaneB[((S_BLOCK1 - aIndex + 7786U)) & S_BLOCK1], 13U));
            aCross ^= RotL64(aFireLaneD[((S_BLOCK1 - aIndex + 7348U)) & S_BLOCK1], 47U);
            aCross = TwistMix64::DiffuseB(((aCross ^ aPhaseFDomainWordCross) ^ aNonceWordF));
            //
            aScatter = (RotL64(aCross, 57U) + RotL64(aPrevious, 20U)) ^ (RotL64(aIngress, 37U) ^ RotL64(aCarry, 5U));
            aScatter = TwistMix64::DiffuseB(((aScatter ^ aPhaseFDomainWordScatter) ^ aNonceWordF));
            //
            aOrbiterA = ((aWandererD + RotL64(aIngress, 13U)) + RotL64(aCarry, 27U)) + 10336802574069791273U;
            aOrbiterF = ((aWandererI + RotL64(aCross, 51U)) + RotL64(aCarry, 3U)) + 169025388197058936U;
            aOrbiterE = ((aWandererK + RotL64(aPrevious, 4U)) + 6541354188379168846U) + aNonceWordH;
            aOrbiterC = ((aWandererA + RotL64(aScatter, 23U)) + 16223920526599306104U) + aPhaseFOrbiterAssignSaltC[(((31U - aIndex) + 7U)) & S_SALT1];
            aOrbiterK = ((aWandererF + RotL64(aPrevious, 19U)) + RotL64(aCarry, 41U)) + 12756613707692514808U;
            aOrbiterH = (aWandererC + RotL64(aCross, 27U)) + 5082475548176484035U;
            aOrbiterB = (((aWandererG + RotL64(aIngress, 43U)) + 4907435526952698526U) + aPhaseFOrbiterAssignSaltE[((aIndex + 27U)) & S_SALT1]) + aNonceWordG;
            aOrbiterI = ((aWandererE + RotL64(aScatter, 56U)) + 14236627073831834337U) + aNonceWordP;
            aOrbiterD = ((aWandererH + RotL64(aPrevious, 47U)) + 11502511046130497584U) + aNonceWordB;
            //
            aOrbiterA = (aOrbiterA + aOrbiterF) + 3679044835550219497U;
            aOrbiterE = (aOrbiterE ^ aOrbiterA) ^ 11254838916686736746U;
            aOrbiterE = RotL64((aOrbiterE * 8631695922983532915U), 43U);
            //
            aOrbiterC = ((aOrbiterC + aOrbiterA) + 10582608424233200966U) + aNonceWordI;
            aOrbiterK = (aOrbiterK ^ aOrbiterC) ^ 10449735026385340313U;
            aOrbiterK = RotL64((aOrbiterK * 7363770199734997411U), 47U);
            //
            aOrbiterE = (aOrbiterE + aOrbiterH) + 4628253464169957835U;
            aOrbiterB = ((aOrbiterB ^ aOrbiterE) ^ 17664454668473204465U) ^ aPhaseFOrbiterUpdateSaltE[((aIndex + 24U)) & S_SALT1];
            aOrbiterB = RotL64((aOrbiterB * 4234720298731378527U), 19U);
            //
            aOrbiterK = (aOrbiterK + aOrbiterE) + 3798386391743884889U;
            aOrbiterI = (((aOrbiterI ^ aOrbiterK) ^ 1379331161819246587U) ^ aPhaseFOrbiterUpdateSaltD[(((31U - aIndex) + 21U)) & S_SALT1]) ^ aNonceWordJ;
            aOrbiterI = RotL64((aOrbiterI * 13086160171095077295U), 51U);
            //
            aOrbiterH = ((aOrbiterH + aOrbiterK) + 9816600392407327227U) + aPhaseFOrbiterUpdateSaltC[(((31U - aIndex) + 4U)) & S_SALT1];
            aOrbiterD = (aOrbiterD ^ aOrbiterH) ^ 16781971616348376878U;
            aOrbiterD = RotL64((aOrbiterD * 12503867584828289879U), 37U);
            //
            aOrbiterB = ((aOrbiterB + aOrbiterD) + 4807797577690520554U) + aPhaseFOrbiterUpdateSaltB[(((31U - aIndex) + 15U)) & S_SALT1];
            aOrbiterF = (aOrbiterF ^ aOrbiterB) ^ 2492057261148595922U;
            aOrbiterF = RotL64((aOrbiterF * 9453302540675483005U), 3U);
            //
            aOrbiterF = (aOrbiterF + aOrbiterC) + 7909676419643119585U;
            aOrbiterH = (aOrbiterH ^ aOrbiterF) ^ 256053568910383007U;
            aOrbiterH = RotL64((aOrbiterH * 11965085163352053161U), 29U);
            //
            aOrbiterI = (aOrbiterI + aOrbiterB) + 16179914439220412472U;
            aOrbiterA = (aOrbiterA ^ aOrbiterI) ^ 3968867762761955845U;
            aOrbiterA = RotL64((aOrbiterA * 7473632378251893139U), 11U);
            //
            aOrbiterD = ((aOrbiterD + aOrbiterI) + 7474832923901283742U) + aNonceWordC;
            aOrbiterC = (aOrbiterC ^ aOrbiterD) ^ 4736994731050735779U;
            aOrbiterC = RotL64((aOrbiterC * 9839654409121414047U), 57U);
            //
            aIngress = aOrbiterI ^ RotL64(aOrbiterK, 26U);
            aIngress = aIngress + (aOrbiterE ^ RotL64(aOrbiterA, 39U));
            aIngress = aIngress + (aOrbiterB ^ RotL64(aOrbiterD, 35U));
            aIngress = aIngress + (RotL64(aOrbiterF, 47U) ^ aOrbiterC);
            aIngress = aIngress + RotL64(aOrbiterH, 23U);
            aIngress = TwistMix64::DiffuseC((aIngress + aScatter));
            //
            aWandererA = aWandererA ^ ((RotL64(aScatter, 13U) + RotL64(aOrbiterB, 5U)) + aOrbiterF);
            aWandererG = aWandererG + (((RotL64(aCross, 35U) + aOrbiterK) + RotL64(aOrbiterI, 35U)) + RotL64(aCarry, 5U));
            aWandererK = aWandererK ^ ((RotL64(aPrevious, 56U) + RotL64(aOrbiterC, 19U)) + aOrbiterE);
            aWandererI = aWandererI + ((((RotL64(aIngress, 47U) + aOrbiterB) + RotL64(aOrbiterD, 47U)) + RotL64(aCarry, 35U)) + aNonceWordD);
            aWandererE = aWandererE ^ (((RotL64(aCross, 51U) + RotL64(aOrbiterI, 10U)) + aOrbiterD) + aNonceWordM);
            aWandererF = aWandererF + ((((RotL64(aIngress, 5U) + RotL64(aOrbiterA, 51U)) + aOrbiterH) + aNonceWordE) + aPhaseFWandererUpdateSaltE[((aIndex + 20U)) & S_SALT1]);
            aWandererC = aWandererC ^ ((RotL64(aScatter, 18U) + RotL64(aOrbiterA, 29U)) + aOrbiterD);
            aWandererH = aWandererH + (((RotL64(aPrevious, 43U) + aOrbiterB) + RotL64(aOrbiterK, 23U)) + aPhaseFWandererUpdateSaltD[((aIndex + 29U)) & S_SALT1]);
            aWandererD = aWandererD ^ (((RotL64(aScatter, 27U) + aOrbiterH) + RotL64(aOrbiterE, 56U)) + aNonceWordL);
            //
            aCarry = aCarry + (RotL64(aWandererI, 27U) ^ aWandererG);
            aCarry = aCarry + (RotL64(aWandererA, 13U) ^ aWandererE);
            aCarry = aCarry + (aWandererD ^ RotL64(aWandererH, 34U));
            aCarry = aCarry + (RotL64(aWandererF, 3U) ^ aWandererK);
            aCarry = aCarry + RotL64(aWandererC, 53U);
            aCarry = aCarry + RotL64(aIngress, 57U);
            aCarry = TwistMix64::DiffuseC(aCarry);
            //
            aSnowLaneB[S_BLOCK1 - aIndex] = aIngress;
        }
    
        // seed_loop_f loop 3
        // ingress from: aSnowLaneB, aOperationLaneA, aInvestLaneA
        // ingress directions: aSnowLaneB forward forced, aOperationLaneA forward forced, aInvestLaneA forward/backward random
        // cross from: aSnowLaneA, aOperationLaneC
        // cross directions: aSnowLaneA backward forced, aOperationLaneC backward/forward random
        // write to: aExpandLaneA
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aSnowLaneB[((aIndex + 13789U)) & S_BLOCK1], 21U) ^ RotL64(aOperationLaneA[((aIndex + 14733U)) & S_BLOCK1], 47U));
            aIngress ^= RotL64(aInvestLaneA[((aIndex + 16233U)) & S_BLOCK1], 37U);
            aIngress = TwistMix64::DiffuseC(((aIngress ^ aPhaseFDomainWordIngress) ^ aNonceWordN));
            //
            aCross = RotL64(aSnowLaneA[((S_BLOCK1 - aIndex + 13405U)) & S_BLOCK1], 23U) ^ RotL64(aOperationLaneC[((S_BLOCK1 - aIndex + 13911U)) & S_BLOCK1], 43U);
            aCross = TwistMix64::DiffuseC(((aCross ^ aPhaseFDomainWordCross) ^ aNonceWordJ));
            //
            aScatter = (RotL64(aIngress, 57U) + RotL64(aCross, 36U)) + (RotL64(aPrevious, 5U) ^ RotL64(aCarry, 21U));
            aScatter = TwistMix64::DiffuseB(((aScatter ^ aPhaseFDomainWordScatter) ^ aNonceWordO));
            //
            aOrbiterJ = ((aWandererA + RotL64(aScatter, 5U)) + 16189787374324972735U) + aNonceWordH;
            aOrbiterD = ((aWandererK + RotL64(aIngress, 47U)) + RotL64(aCarry, 13U)) + 17563763730956242224U;
            aOrbiterB = ((aWandererC + RotL64(aCross, 26U)) + 10572803498593789385U) + aNonceWordG;
            aOrbiterG = ((aWandererI + RotL64(aPrevious, 19U)) + RotL64(aCarry, 3U)) + 7713105232072974166U;
            aOrbiterF = ((aWandererE + RotL64(aCross, 13U)) + 10760839534772718139U) + aPhaseFOrbiterAssignSaltD[((aIndex + 27U)) & S_SALT1];
            aOrbiterE = ((aWandererD + RotL64(aPrevious, 57U)) + 13397069448391230253U) + aNonceWordD;
            aOrbiterH = ((aWandererG + RotL64(aScatter, 53U)) + RotL64(aCarry, 37U)) + 4569255679998375682U;
            aOrbiterK = (aWandererH + RotL64(aIngress, 34U)) + 9888769350817876949U;
            aOrbiterI = ((aWandererJ + RotL64(aPrevious, 41U)) + 11351796060878856300U) + aPhaseFOrbiterAssignSaltA[(((31U - aIndex) + 29U)) & S_SALT1];
            //
            aOrbiterJ = (aOrbiterJ + aOrbiterD) + 18153775071965707204U;
            aOrbiterB = ((aOrbiterB ^ aOrbiterJ) ^ 1282846411145853435U) ^ aPhaseFOrbiterUpdateSaltE[(((31U - aIndex) + 19U)) & S_SALT1];
            aOrbiterB = RotL64((aOrbiterB * 12294455920906257823U), 29U);
            //
            aOrbiterB = (aOrbiterB + aOrbiterG) + 16457743979262460660U;
            aOrbiterF = (aOrbiterF ^ aOrbiterB) ^ 173493260775251032U;
            aOrbiterF = RotL64((aOrbiterF * 4935807229040883505U), 19U);
            //
            aOrbiterE = (aOrbiterE + aOrbiterH) + 3927345926316409630U;
            aOrbiterD = (aOrbiterD ^ aOrbiterE) ^ 5158769729850853623U;
            aOrbiterD = RotL64((aOrbiterD * 2446452358663812945U), 41U);
            //
            aOrbiterK = (aOrbiterK + aOrbiterB) + 12331351600010165154U;
            aOrbiterH = ((aOrbiterH ^ aOrbiterK) ^ 3940794200348684050U) ^ aNonceWordB;
            aOrbiterH = RotL64((aOrbiterH * 13248997263062075043U), 37U);
            //
            aOrbiterI = (aOrbiterI + aOrbiterK) + 11248514843822945425U;
            aOrbiterE = (aOrbiterE ^ aOrbiterI) ^ 1391497323278226522U;
            aOrbiterE = RotL64((aOrbiterE * 8376841806072565005U), 5U);
            //
            aOrbiterD = ((aOrbiterD + aOrbiterI) + 13265623528678787307U) + aPhaseFOrbiterUpdateSaltB[(((31U - aIndex) + 20U)) & S_SALT1];
            aOrbiterG = (aOrbiterG ^ aOrbiterD) ^ 2802033745265647317U;
            aOrbiterG = RotL64((aOrbiterG * 3437626962562016147U), 47U);
            //
            aOrbiterF = ((aOrbiterF + aOrbiterJ) + 6938444301018051844U) + aPhaseFOrbiterUpdateSaltF[((aIndex + 21U)) & S_SALT1];
            aOrbiterK = ((aOrbiterK ^ aOrbiterF) ^ 1086544666755559028U) ^ aPhaseFOrbiterUpdateSaltA[(((31U - aIndex) + 14U)) & S_SALT1];
            aOrbiterK = RotL64((aOrbiterK * 16039728388882079889U), 53U);
            //
            aOrbiterG = (aOrbiterG + aOrbiterE) + 16156443117365816536U;
            aOrbiterJ = (aOrbiterJ ^ aOrbiterG) ^ 3619942859562697142U;
            aOrbiterJ = RotL64((aOrbiterJ * 7589346043159112151U), 23U);
            //
            aOrbiterH = ((aOrbiterH + aOrbiterF) + 17681848914912743292U) + aNonceWordM;
            aOrbiterI = (aOrbiterI ^ aOrbiterH) ^ 8848238631758130416U;
            aOrbiterI = RotL64((aOrbiterI * 810402256099500607U), 57U);
            //
            aIngress = aOrbiterD ^ RotL64(aOrbiterG, 41U);
            aIngress = aIngress + (RotL64(aOrbiterH, 19U) ^ aOrbiterF);
            aIngress = aIngress + (RotL64(aOrbiterB, 47U) ^ aOrbiterE);
            aIngress = aIngress + (aOrbiterK ^ RotL64(aOrbiterJ, 56U));
            aIngress = aIngress + RotL64(aOrbiterI, 23U);
            aIngress = TwistMix64::DiffuseA((aIngress + aScatter));
            //
            aWandererE = aWandererE + (((RotL64(aPrevious, 34U) + RotL64(aOrbiterF, 57U)) + aOrbiterI) + RotL64(aCarry, 43U));
            aWandererK = aWandererK ^ ((((RotL64(aCross, 43U) + RotL64(aOrbiterD, 3U)) + aOrbiterE) + aNonceWordF) + aPhaseFWandererUpdateSaltF[((aIndex + 3U)) & S_SALT1]);
            aWandererG = aWandererG + (((RotL64(aIngress, 3U) + RotL64(aOrbiterJ, 30U)) + aOrbiterK) + aNonceWordI);
            aWandererD = aWandererD ^ (((RotL64(aScatter, 19U) + aOrbiterJ) + RotL64(aOrbiterD, 11U)) + aNonceWordA);
            aWandererI = aWandererI + ((RotL64(aIngress, 47U) + aOrbiterD) + RotL64(aOrbiterI, 37U));
            aWandererA = aWandererA ^ (((RotL64(aScatter, 23U) + RotL64(aOrbiterH, 43U)) + aOrbiterD) + aPhaseFWandererUpdateSaltA[(((31U - aIndex) + 26U)) & S_SALT1]);
            aWandererH = aWandererH + ((RotL64(aPrevious, 13U) + RotL64(aOrbiterJ, 47U)) + aOrbiterB);
            aWandererJ = aWandererJ ^ (((RotL64(aCross, 51U) + aOrbiterG) + RotL64(aOrbiterB, 53U)) + aNonceWordC);
            aWandererC = aWandererC + (((RotL64(aScatter, 60U) + RotL64(aOrbiterB, 22U)) + aOrbiterD) + RotL64(aCarry, 51U));
            //
            aCarry = aCarry + (aWandererC ^ RotL64(aWandererH, 24U));
            aCarry = aCarry + (RotL64(aWandererD, 27U) ^ aWandererG);
            aCarry = aCarry + (RotL64(aWandererE, 47U) ^ aWandererI);
            aCarry = aCarry + (aWandererK ^ RotL64(aWandererA, 5U));
            aCarry = aCarry + RotL64(aWandererJ, 53U);
            aCarry = aCarry + RotL64(aIngress, 43U);
            aCarry = TwistMix64::DiffuseB(aCarry);
            //
            aExpandLaneA[aIndex] = aIngress;
        }
    
        // seed_loop_f loop 4
        // ingress from: aExpandLaneA, aSnowLaneA, aInvestLaneB
        // ingress directions: aExpandLaneA forward forced, aSnowLaneA forward forced, aInvestLaneB forward/backward random
        // cross from: aSnowLaneB, aOperationLaneD
        // cross directions: aSnowLaneB backward forced, aOperationLaneD backward/forward random
        // write to: aExpandLaneB
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aExpandLaneA[((aIndex + 20831U)) & S_BLOCK1], 39U) ^ RotL64(aSnowLaneA[((aIndex + 16694U)) & S_BLOCK1], 28U));
            aIngress ^= RotL64(aInvestLaneB[((S_BLOCK1 - aIndex + 18385U)) & S_BLOCK1], 13U);
            aIngress = TwistMix64::DiffuseB(((aIngress ^ aPhaseFDomainWordIngress) ^ aNonceWordJ));
            //
            aCross = RotL64(aSnowLaneB[((S_BLOCK1 - aIndex + 18300U)) & S_BLOCK1], 23U) ^ RotL64(aOperationLaneD[((aIndex + 17458U)) & S_BLOCK1], 52U);
            aCross = TwistMix64::DiffuseC(((aCross ^ aPhaseFDomainWordCross) ^ aNonceWordD));
            //
            aScatter = (RotL64(aCross, 48U) + RotL64(aPrevious, 35U)) ^ (RotL64(aIngress, 5U) ^ RotL64(aCarry, 23U));
            aScatter = TwistMix64::DiffuseC(((aScatter ^ aPhaseFDomainWordScatter) ^ aNonceWordF));
            //
            aOrbiterG = (((aWandererJ + RotL64(aIngress, 24U)) + RotL64(aCarry, 3U)) + 4384716820085860551U) + aNonceWordH;
            aOrbiterF = ((aWandererI + RotL64(aScatter, 5U)) + RotL64(aCarry, 21U)) + 9715780315942116888U;
            aOrbiterA = (aWandererF + RotL64(aPrevious, 29U)) + 15963520052789178632U;
            aOrbiterK = ((aWandererK + RotL64(aCross, 19U)) + RotL64(aCarry, 39U)) + 14346700690686392938U;
            aOrbiterH = (aWandererH + RotL64(aPrevious, 53U)) + 6005518012489966643U;
            aOrbiterB = (aWandererE + RotL64(aScatter, 57U)) + 2506732930310252119U;
            aOrbiterD = (((aWandererC + RotL64(aIngress, 35U)) + 16782163084851775826U) + aPhaseFOrbiterAssignSaltB[(((31U - aIndex) + 4U)) & S_SALT1]) + aNonceWordA;
            aOrbiterJ = ((aWandererA + RotL64(aCross, 10U)) + 823673076571076303U) + aNonceWordO;
            aOrbiterC = ((aWandererG + RotL64(aPrevious, 39U)) + 1634084509064077736U) + aPhaseFOrbiterAssignSaltF[((aIndex + 19U)) & S_SALT1];
            //
            aOrbiterG = (aOrbiterG + aOrbiterF) + 1288134975466877686U;
            aOrbiterA = (aOrbiterA ^ aOrbiterG) ^ 2998220403162908444U;
            aOrbiterA = RotL64((aOrbiterA * 4321412662318298283U), 21U);
            //
            aOrbiterK = ((aOrbiterK + aOrbiterH) + 220430672180734911U) + aPhaseFOrbiterUpdateSaltE[(((31U - aIndex) + 29U)) & S_SALT1];
            aOrbiterB = (aOrbiterB ^ aOrbiterK) ^ 10223923547068528867U;
            aOrbiterB = RotL64((aOrbiterB * 12577370238343872139U), 51U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterA) + 11696469696177647608U;
            aOrbiterK = (aOrbiterK ^ aOrbiterD) ^ 6545430420379636963U;
            aOrbiterK = RotL64((aOrbiterK * 8387163146257553773U), 37U);
            //
            aOrbiterJ = (((aOrbiterJ + aOrbiterB) + 79691451831797107U) + aPhaseFOrbiterUpdateSaltA[(((31U - aIndex) + 11U)) & S_SALT1]) + aNonceWordP;
            aOrbiterF = (((aOrbiterF ^ aOrbiterJ) ^ 8971444023498649419U) ^ aPhaseFOrbiterUpdateSaltC[(((31U - aIndex) + 5U)) & S_SALT1]) ^ aNonceWordN;
            aOrbiterF = RotL64((aOrbiterF * 7148919880477390009U), 43U);
            //
            aOrbiterA = (aOrbiterA + aOrbiterC) + 5624403902454498793U;
            aOrbiterH = (aOrbiterH ^ aOrbiterA) ^ 9468064161002030997U;
            aOrbiterH = RotL64((aOrbiterH * 8243560528100864595U), 57U);
            //
            aOrbiterH = (aOrbiterH + aOrbiterJ) + 4619361544913629805U;
            aOrbiterG = ((aOrbiterG ^ aOrbiterH) ^ 12682446273369750704U) ^ aNonceWordM;
            aOrbiterG = RotL64((aOrbiterG * 10879074713156075641U), 5U);
            //
            aOrbiterC = (aOrbiterC + aOrbiterK) + 8728730962617599223U;
            aOrbiterJ = (aOrbiterJ ^ aOrbiterC) ^ 9099675924074253030U;
            aOrbiterJ = RotL64((aOrbiterJ * 5525644236954497523U), 13U);
            //
            aOrbiterB = (aOrbiterB + aOrbiterG) + 3298303921318288541U;
            aOrbiterD = (aOrbiterD ^ aOrbiterB) ^ 5953276499411658358U;
            aOrbiterD = RotL64((aOrbiterD * 10565471305001292693U), 47U);
            //
            aOrbiterF = ((aOrbiterF + aOrbiterD) + 6725769507592688539U) + aPhaseFOrbiterUpdateSaltB[(((31U - aIndex) + 7U)) & S_SALT1];
            aOrbiterC = (aOrbiterC ^ aOrbiterF) ^ 1057277456510215817U;
            aOrbiterC = RotL64((aOrbiterC * 8269412198279297075U), 29U);
            //
            aIngress = RotL64(aOrbiterA, 57U) ^ aOrbiterK;
            aIngress = aIngress + (aOrbiterC ^ RotL64(aOrbiterG, 5U));
            aIngress = aIngress + (aOrbiterF ^ RotL64(aOrbiterB, 50U));
            aIngress = aIngress + (aOrbiterH ^ RotL64(aOrbiterJ, 47U));
            aIngress = aIngress + RotL64(aOrbiterD, 29U);
            aIngress = TwistMix64::DiffuseB((aIngress + aScatter));
            //
            aWandererK = aWandererK + ((RotL64(aScatter, 3U) + RotL64(aOrbiterD, 57U)) + aOrbiterK);
            aWandererH = aWandererH ^ ((((RotL64(aCross, 41U) + aOrbiterB) + RotL64(aOrbiterF, 44U)) + aNonceWordI) + aPhaseFWandererUpdateSaltC[((aIndex + 21U)) & S_SALT1]);
            aWandererA = aWandererA + ((RotL64(aIngress, 47U) + aOrbiterJ) + RotL64(aOrbiterH, 35U));
            aWandererF = aWandererF ^ ((RotL64(aPrevious, 28U) + aOrbiterB) + RotL64(aOrbiterJ, 27U));
            aWandererI = aWandererI + (((RotL64(aCross, 53U) + RotL64(aOrbiterK, 5U)) + aOrbiterF) + aPhaseFWandererUpdateSaltB[((aIndex + 6U)) & S_SALT1]);
            aWandererC = aWandererC ^ ((RotL64(aScatter, 35U) + RotL64(aOrbiterA, 23U)) + aOrbiterH);
            aWandererJ = aWandererJ + ((((RotL64(aIngress, 21U) + RotL64(aOrbiterB, 48U)) + aOrbiterD) + RotL64(aCarry, 57U)) + aNonceWordE);
            aWandererE = aWandererE ^ ((RotL64(aPrevious, 58U) + RotL64(aOrbiterK, 19U)) + aOrbiterC);
            aWandererG = aWandererG + ((((RotL64(aScatter, 13U) + aOrbiterJ) + RotL64(aOrbiterG, 39U)) + RotL64(aCarry, 27U)) + aNonceWordG);
            //
            aCarry = aCarry + (aWandererA ^ RotL64(aWandererF, 57U));
            aCarry = aCarry + (RotL64(aWandererI, 6U) ^ aWandererK);
            aCarry = aCarry + (aWandererG ^ RotL64(aWandererE, 41U));
            aCarry = aCarry + (RotL64(aWandererC, 37U) ^ aWandererH);
            aCarry = aCarry + RotL64(aWandererJ, 23U);
            aCarry = aCarry + RotL64(aIngress, 3U);
            aCarry = TwistMix64::DiffuseA(aCarry);
            //
            aExpandLaneB[S_BLOCK1 - aIndex] = aIngress;
        }
    
        // seed_loop_f loop 5
        // ingress from: aExpandLaneB, aSnowLaneB, aInvestLaneC
        // ingress directions: aExpandLaneB forward forced, aSnowLaneB forward forced, aInvestLaneC forward/backward random
        // cross from: aExpandLaneA, aSnowLaneA
        // cross directions: aExpandLaneA backward forced, aSnowLaneA backward/forward random
        // write to: aExpandLaneC
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aExpandLaneB[((aIndex + 23037U)) & S_BLOCK1], 57U) ^ RotL64(aSnowLaneB[((aIndex + 23792U)) & S_BLOCK1], 11U));
            aIngress ^= RotL64(aInvestLaneC[((aIndex + 26756U)) & S_BLOCK1], 23U);
            aIngress = TwistMix64::DiffuseC(((aIngress ^ aPhaseFDomainWordIngress) ^ aNonceWordF));
            //
            aCross = RotL64(aExpandLaneA[((S_BLOCK1 - aIndex + 26844U)) & S_BLOCK1], 5U) ^ RotL64(aSnowLaneA[((aIndex + 27226U)) & S_BLOCK1], 19U);
            aCross = TwistMix64::DiffuseA(((aCross ^ aPhaseFDomainWordCross) ^ aNonceWordJ));
            //
            aScatter = (RotL64(aPrevious, 57U) ^ RotL64(aCross, 40U)) + (RotL64(aCarry, 5U) + RotL64(aIngress, 23U));
            aScatter = TwistMix64::DiffuseC(((aScatter ^ aPhaseFDomainWordScatter) ^ aNonceWordE));
            //
            aOrbiterK = (aWandererH + RotL64(aIngress, 21U)) + 12029393034357490020U;
            aOrbiterD = (((aWandererI + RotL64(aCross, 37U)) + 4526754731580694987U) + aPhaseFOrbiterAssignSaltE[((aIndex + 20U)) & S_SALT1]) + aNonceWordL;
            aOrbiterJ = (aWandererJ + RotL64(aPrevious, 58U)) + 17060419646421271853U;
            aOrbiterA = (aWandererK + RotL64(aScatter, 13U)) + 4128488893837059683U;
            aOrbiterF = (((aWandererG + RotL64(aIngress, 53U)) + RotL64(aCarry, 27U)) + 12706894827547160110U) + aNonceWordG;
            aOrbiterC = (aWandererA + RotL64(aPrevious, 5U)) + 12506324593645825056U;
            aOrbiterE = ((aWandererC + RotL64(aScatter, 41U)) + RotL64(aCarry, 37U)) + 12581344490649250025U;
            aOrbiterH = ((aWandererE + RotL64(aCross, 46U)) + RotL64(aCarry, 13U)) + 14357032418199130132U;
            aOrbiterB = (((aWandererD + RotL64(aPrevious, 29U)) + 15341977701796331249U) + aPhaseFOrbiterAssignSaltC[(((31U - aIndex) + 12U)) & S_SALT1]) + aNonceWordB;
            //
            aOrbiterK = (aOrbiterK + aOrbiterD) + 7086602307544733241U;
            aOrbiterJ = (aOrbiterJ ^ aOrbiterK) ^ 12398300065276832486U;
            aOrbiterJ = RotL64((aOrbiterJ * 18157408831225635333U), 11U);
            //
            aOrbiterA = (aOrbiterA + aOrbiterJ) + 2499745046076601988U;
            aOrbiterF = ((aOrbiterF ^ aOrbiterA) ^ 7249361592814001829U) ^ aPhaseFOrbiterUpdateSaltB[((aIndex + 17U)) & S_SALT1];
            aOrbiterF = RotL64((aOrbiterF * 14597139848072319685U), 3U);
            //
            aOrbiterJ = (aOrbiterJ + aOrbiterC) + 3254456186337366437U;
            aOrbiterE = ((aOrbiterE ^ aOrbiterJ) ^ 3472973415969046680U) ^ aPhaseFOrbiterUpdateSaltF[((aIndex + 14U)) & S_SALT1];
            aOrbiterE = RotL64((aOrbiterE * 14583566953969168353U), 21U);
            //
            aOrbiterE = ((aOrbiterE + aOrbiterH) + 7905718972111691591U) + aPhaseFOrbiterUpdateSaltD[(((31U - aIndex) + 22U)) & S_SALT1];
            aOrbiterB = (aOrbiterB ^ aOrbiterE) ^ 15941413652144021522U;
            aOrbiterB = RotL64((aOrbiterB * 3473779492962783565U), 29U);
            //
            aOrbiterB = (aOrbiterB + aOrbiterK) + 10583964125960308762U;
            aOrbiterA = (aOrbiterA ^ aOrbiterB) ^ 13659925272340853715U;
            aOrbiterA = RotL64((aOrbiterA * 16708294803316630743U), 39U);
            //
            aOrbiterF = (aOrbiterF + aOrbiterE) + 9487054537489454887U;
            aOrbiterD = (aOrbiterD ^ aOrbiterF) ^ 13287757570441887517U;
            aOrbiterD = RotL64((aOrbiterD * 17351439045329892107U), 43U);
            //
            aOrbiterH = ((aOrbiterH + aOrbiterF) + 15279245465808571942U) + aNonceWordA;
            aOrbiterK = (aOrbiterK ^ aOrbiterH) ^ 12424999114621745879U;
            aOrbiterK = RotL64((aOrbiterK * 2274918760256527137U), 57U);
            //
            aOrbiterC = (aOrbiterC + aOrbiterA) + 13915392738892970475U;
            aOrbiterH = (((aOrbiterH ^ aOrbiterC) ^ 13797668053788805126U) ^ aPhaseFOrbiterUpdateSaltE[(((31U - aIndex) + 5U)) & S_SALT1]) ^ aNonceWordE;
            aOrbiterH = RotL64((aOrbiterH * 13752161103680525317U), 35U);
            //
            aOrbiterD = ((aOrbiterD + aOrbiterB) + 14344766585550401077U) + aNonceWordC;
            aOrbiterC = ((aOrbiterC ^ aOrbiterD) ^ 13727554194373146727U) ^ aNonceWordK;
            aOrbiterC = RotL64((aOrbiterC * 17164450431362670223U), 53U);
            //
            aIngress = RotL64(aOrbiterH, 60U) ^ aOrbiterD;
            aIngress = aIngress + (RotL64(aOrbiterK, 53U) ^ aOrbiterE);
            aIngress = aIngress + (aOrbiterJ ^ RotL64(aOrbiterA, 35U));
            aIngress = aIngress + (RotL64(aOrbiterB, 39U) ^ aOrbiterF);
            aIngress = aIngress + RotL64(aOrbiterC, 43U);
            aIngress = TwistMix64::DiffuseA((aIngress + aScatter));
            //
            aWandererH = aWandererH + ((((RotL64(aPrevious, 21U) + aOrbiterH) + RotL64(aOrbiterF, 28U)) + RotL64(aCarry, 27U)) + aNonceWordH);
            aWandererI = aWandererI ^ ((RotL64(aScatter, 42U) + RotL64(aOrbiterF, 51U)) + aOrbiterE);
            aWandererD = aWandererD + (((RotL64(aCross, 47U) + RotL64(aOrbiterJ, 19U)) + aOrbiterC) + RotL64(aCarry, 51U));
            aWandererG = aWandererG ^ ((RotL64(aIngress, 29U) + RotL64(aOrbiterA, 13U)) + aOrbiterD);
            aWandererK = aWandererK + (((RotL64(aCross, 51U) + aOrbiterD) + RotL64(aOrbiterH, 36U)) + aPhaseFWandererUpdateSaltD[(((31U - aIndex) + 23U)) & S_SALT1]);
            aWandererA = aWandererA ^ (((RotL64(aPrevious, 57U) + RotL64(aOrbiterJ, 47U)) + aOrbiterB) + aNonceWordP);
            aWandererJ = aWandererJ + ((RotL64(aScatter, 6U) + RotL64(aOrbiterD, 23U)) + aOrbiterF);
            aWandererE = aWandererE ^ (((RotL64(aIngress, 37U) + aOrbiterK) + RotL64(aOrbiterB, 41U)) + aNonceWordM);
            aWandererC = aWandererC + ((((RotL64(aScatter, 11U) + RotL64(aOrbiterE, 5U)) + aOrbiterJ) + aNonceWordO) + aPhaseFWandererUpdateSaltE[(((31U - aIndex) + 26U)) & S_SALT1]);
            //
            aCarry = aCarry + (RotL64(aWandererC, 36U) ^ aWandererE);
            aCarry = aCarry + (aWandererI ^ RotL64(aWandererA, 39U));
            aCarry = aCarry + (aWandererG ^ RotL64(aWandererK, 3U));
            aCarry = aCarry + (aWandererD ^ RotL64(aWandererH, 57U));
            aCarry = aCarry + RotL64(aWandererJ, 23U);
            aCarry = aCarry + RotL64(aIngress, 11U);
            aCarry = TwistMix64::DiffuseB(aCarry);
            //
            aExpandLaneC[aIndex] = aIngress;
        }
    
        // seed_loop_f loop 6
        // ingress from: aExpandLaneC, aExpandLaneA, aInvestLaneD
        // ingress directions: aExpandLaneC forward forced, aExpandLaneA forward forced, aInvestLaneD forward/backward random
        // cross from: aExpandLaneB, aOperationLaneB
        // cross directions: aExpandLaneB backward forced, aOperationLaneB backward/forward random
        // write to: aExpandLaneD
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aExpandLaneC[((aIndex + 27922U)) & S_BLOCK1], 57U) ^ RotL64(aExpandLaneA[((aIndex + 27427U)) & S_BLOCK1], 23U));
            aIngress ^= RotL64(aInvestLaneD[((aIndex + 27755U)) & S_BLOCK1], 35U);
            aIngress = TwistMix64::DiffuseB(((aIngress ^ aPhaseFDomainWordIngress) ^ aNonceWordE));
            //
            aCross = RotL64(aExpandLaneB[((S_BLOCK1 - aIndex + 28808U)) & S_BLOCK1], 12U) ^ RotL64(aOperationLaneB[((S_BLOCK1 - aIndex + 28243U)) & S_BLOCK1], 53U);
            aCross = TwistMix64::DiffuseA(((aCross ^ aPhaseFDomainWordCross) ^ aNonceWordK));
            //
            aScatter = (RotL64(aPrevious, 57U) ^ RotL64(aCarry, 5U)) ^ (RotL64(aIngress, 40U) + RotL64(aCross, 23U));
            aScatter = TwistMix64::DiffuseB(((aScatter ^ aPhaseFDomainWordScatter) ^ aNonceWordJ));
            //
            aOrbiterI = ((aWandererE + RotL64(aPrevious, 43U)) + RotL64(aCarry, 27U)) + 7790166497945719700U;
            aOrbiterH = (((aWandererC + RotL64(aScatter, 47U)) + RotL64(aCarry, 53U)) + 7136208896846119188U) + aNonceWordO;
            aOrbiterE = (aWandererB + RotL64(aIngress, 5U)) + 12123156943355100886U;
            aOrbiterF = (((aWandererH + RotL64(aCross, 19U)) + 5095546037880875199U) + aPhaseFOrbiterAssignSaltA[((aIndex + 9U)) & S_SALT1]) + aNonceWordM;
            aOrbiterA = (aWandererA + RotL64(aPrevious, 14U)) + 17642705393916765992U;
            aOrbiterB = (aWandererK + RotL64(aScatter, 35U)) + 9918479837334416990U;
            aOrbiterK = (aWandererG + RotL64(aCross, 39U)) + 4890009823843176466U;
            aOrbiterC = ((aWandererJ + RotL64(aIngress, 27U)) + RotL64(aCarry, 19U)) + 17652590786213674124U;
            aOrbiterJ = (((aWandererI + RotL64(aCross, 10U)) + 870002527644696135U) + aPhaseFOrbiterAssignSaltD[((aIndex + 22U)) & S_SALT1]) + aNonceWordL;
            //
            aOrbiterI = ((aOrbiterI + aOrbiterH) + 12545429703552643682U) + aPhaseFOrbiterUpdateSaltD[(((31U - aIndex) + 25U)) & S_SALT1];
            aOrbiterE = ((aOrbiterE ^ aOrbiterI) ^ 5310272867406182581U) ^ aPhaseFOrbiterUpdateSaltF[((aIndex + 28U)) & S_SALT1];
            aOrbiterE = RotL64((aOrbiterE * 10420003334833925011U), 51U);
            //
            aOrbiterE = (aOrbiterE + aOrbiterF) + 3264719049050179440U;
            aOrbiterA = (aOrbiterA ^ aOrbiterE) ^ 1967241238180278937U;
            aOrbiterA = RotL64((aOrbiterA * 13004319774269457957U), 57U);
            //
            aOrbiterB = ((aOrbiterB + aOrbiterI) + 773883832927040736U) + aNonceWordN;
            aOrbiterK = (((aOrbiterK ^ aOrbiterB) ^ 12766817190261232485U) ^ aPhaseFOrbiterUpdateSaltC[((aIndex + 27U)) & S_SALT1]) ^ aNonceWordD;
            aOrbiterK = RotL64((aOrbiterK * 7448864556802318431U), 19U);
            //
            aOrbiterC = (aOrbiterC + aOrbiterJ) + 260069382395598265U;
            aOrbiterB = (aOrbiterB ^ aOrbiterC) ^ 15462103891287350123U;
            aOrbiterB = RotL64((aOrbiterB * 5029268763635635753U), 43U);
            //
            aOrbiterF = (aOrbiterF + aOrbiterK) + 4072032867513289827U;
            aOrbiterC = ((aOrbiterC ^ aOrbiterF) ^ 17153061419083897076U) ^ aPhaseFOrbiterUpdateSaltA[(((31U - aIndex) + 3U)) & S_SALT1];
            aOrbiterC = RotL64((aOrbiterC * 11934532169271718913U), 23U);
            //
            aOrbiterA = ((aOrbiterA + aOrbiterC) + 6207264270332656966U) + aNonceWordI;
            aOrbiterH = ((aOrbiterH ^ aOrbiterA) ^ 18048064697837314947U) ^ aNonceWordG;
            aOrbiterH = RotL64((aOrbiterH * 13632594619404208489U), 35U);
            //
            aOrbiterK = (aOrbiterK + aOrbiterE) + 14484617445340272026U;
            aOrbiterJ = (aOrbiterJ ^ aOrbiterK) ^ 16160443600497652026U;
            aOrbiterJ = RotL64((aOrbiterJ * 1988599349457831597U), 11U);
            //
            aOrbiterH = (aOrbiterH + aOrbiterB) + 5873314228291583482U;
            aOrbiterF = (aOrbiterF ^ aOrbiterH) ^ 16418290052752166515U;
            aOrbiterF = RotL64((aOrbiterF * 18270363452003213317U), 39U);
            //
            aOrbiterJ = (aOrbiterJ + aOrbiterA) + 9158414409987627714U;
            aOrbiterI = (aOrbiterI ^ aOrbiterJ) ^ 8205937960146492168U;
            aOrbiterI = RotL64((aOrbiterI * 14008398661393344261U), 5U);
            //
            aIngress = RotL64(aOrbiterE, 11U) ^ aOrbiterB;
            aIngress = aIngress + (aOrbiterI ^ RotL64(aOrbiterJ, 4U));
            aIngress = aIngress + (aOrbiterF ^ RotL64(aOrbiterK, 51U));
            aIngress = aIngress + (RotL64(aOrbiterH, 57U) ^ aOrbiterC);
            aIngress = aIngress + RotL64(aOrbiterA, 35U);
            aIngress = TwistMix64::DiffuseB((aIngress + aScatter));
            //
            aWandererE = aWandererE + ((RotL64(aScatter, 36U) + RotL64(aOrbiterI, 56U)) + aOrbiterK);
            aWandererI = aWandererI ^ ((RotL64(aPrevious, 11U) + RotL64(aOrbiterK, 51U)) + aOrbiterJ);
            aWandererH = aWandererH + (((RotL64(aIngress, 19U) + aOrbiterJ) + RotL64(aOrbiterI, 47U)) + RotL64(aCarry, 21U));
            aWandererA = aWandererA ^ ((RotL64(aCross, 23U) + RotL64(aOrbiterA, 37U)) + aOrbiterC);
            aWandererK = aWandererK + (((RotL64(aScatter, 47U) + aOrbiterC) + RotL64(aOrbiterF, 41U)) + aPhaseFWandererUpdateSaltF[(((31U - aIndex) + 17U)) & S_SALT1]);
            aWandererJ = aWandererJ ^ (((RotL64(aCross, 3U) + RotL64(aOrbiterJ, 29U)) + aOrbiterC) + aNonceWordB);
            aWandererB = aWandererB + ((RotL64(aPrevious, 43U) + RotL64(aOrbiterJ, 3U)) + aOrbiterE);
            aWandererC = aWandererC ^ ((RotL64(aIngress, 30U) + aOrbiterB) + RotL64(aOrbiterC, 10U));
            aWandererG = aWandererG + (((((RotL64(aPrevious, 57U) + aOrbiterK) + RotL64(aOrbiterH, 21U)) + RotL64(aCarry, 3U)) + aNonceWordC) + aPhaseFWandererUpdateSaltA[(((31U - aIndex) + 15U)) & S_SALT1]);
            //
            aCarry = aCarry + (RotL64(aWandererB, 57U) ^ aWandererE);
            aCarry = aCarry + (RotL64(aWandererG, 13U) ^ aWandererK);
            aCarry = aCarry + (aWandererI ^ RotL64(aWandererJ, 3U));
            aCarry = aCarry + (aWandererC ^ RotL64(aWandererA, 6U));
            aCarry = aCarry + RotL64(aWandererH, 35U);
            aCarry = aCarry + RotL64(aIngress, 47U);
            aCarry = TwistMix64::DiffuseC(aCarry);
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

void TwistExpander_Greezy_Arx::Seed_G(TwistWorkSpace *pWorkSpace,
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
    [[maybe_unused]] std::uint8_t *aOperationLaneA = pWorkSpace->mOperationLaneA;
    [[maybe_unused]] std::uint8_t *aOperationLaneB = pWorkSpace->mOperationLaneB;
    [[maybe_unused]] std::uint8_t *aOperationLaneC = pWorkSpace->mOperationLaneC;
    [[maybe_unused]] std::uint8_t *aOperationLaneD = pWorkSpace->mOperationLaneD;
    [[maybe_unused]] std::uint8_t *aSnowLaneA = pWorkSpace->mSnowLaneA;
    [[maybe_unused]] std::uint8_t *aSnowLaneB = pWorkSpace->mSnowLaneB;
    [[maybe_unused]] std::uint8_t *aSnowLaneC = pWorkSpace->mSnowLaneC;
    [[maybe_unused]] std::uint8_t *aSnowLaneD = pWorkSpace->mSnowLaneD;
    [[maybe_unused]] std::uint8_t *aFireLaneA = pWorkSpace->mFireLaneA;
    [[maybe_unused]] std::uint8_t *aFireLaneB = pWorkSpace->mFireLaneB;
    [[maybe_unused]] std::uint8_t *aFireLaneC = pWorkSpace->mFireLaneC;
    [[maybe_unused]] std::uint8_t *aFireLaneD = pWorkSpace->mFireLaneD;
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
    std::uint64_t aNonceWordA = TwistMix64::DiffuseA(pNonce * 0x82505CCA432FD1DFULL + 0x873D5E1657263C8BULL);
    std::uint64_t aNonceWordB = TwistMix64::DiffuseB(pNonce * 0xA524D26802A4A4C7ULL + 0xEAD0518F710C4327ULL);
    std::uint64_t aNonceWordC = TwistMix64::DiffuseB(pNonce * 0xF40767BF4C966CDBULL + 0xA7CEF902925561F8ULL);
    std::uint64_t aNonceWordD = TwistMix64::DiffuseB(pNonce * 0xAADA91EA757FE4B9ULL + 0xE750D5659F4AD41DULL);
    std::uint64_t aNonceWordE = TwistMix64::DiffuseA(pNonce * 0x98A319FF10AA9A15ULL + 0xB3CEDD6B2EE6DF7FULL);
    std::uint64_t aNonceWordF = TwistMix64::DiffuseA(pNonce * 0x868B7EB234DC091FULL + 0xFE8039FF6227A783ULL);
    std::uint64_t aNonceWordG = TwistMix64::DiffuseB(pNonce * 0xF17D7B93013B09ADULL + 0x9D65D332826F5930ULL);
    std::uint64_t aNonceWordH = TwistMix64::DiffuseB(pNonce * 0xCF81AE1DC9255693ULL + 0xE659D1EE66B61F02ULL);
    std::uint64_t aNonceWordI = TwistMix64::DiffuseC(pNonce * 0xF68F7D3AD526C1BDULL + 0x9EA3C5B0DC99167EULL);
    std::uint64_t aNonceWordJ = TwistMix64::DiffuseA(pNonce * 0xFECDE5BEC9787D2DULL + 0x86E1C472BBF5696BULL);
    std::uint64_t aNonceWordK = TwistMix64::DiffuseB(pNonce * 0xEE02CA04EB32DB3DULL + 0x8997F0E06A3DE22FULL);
    std::uint64_t aNonceWordL = TwistMix64::DiffuseA(pNonce * 0xD4E771D39DD0FF6FULL + 0xA796F63D329FE29BULL);
    std::uint64_t aNonceWordM = TwistMix64::DiffuseC(pNonce * 0xA0B826D39E59DE07ULL + 0xC2140DAFFFDBB90EULL);
    std::uint64_t aNonceWordN = TwistMix64::DiffuseA(pNonce * 0x9DD6763324CD523FULL + 0xBBEA9D39EA34096BULL);
    std::uint64_t aNonceWordO = TwistMix64::DiffuseB(pNonce * 0x8B9C1CA481884B8DULL + 0xE5D18B5BBFCFF1FBULL);
    std::uint64_t aNonceWordP = TwistMix64::DiffuseA(pNonce * 0xE3EC55CD3D00F9D7ULL + 0xCFF0691E5EC0D9CAULL);
    // GSeedRunSeed_G seed_loop_h (start)
    {
        // GSeedRunSeed_G seed_loop_h lane group
        // read from: aSnowLaneA, aSnowLaneB, aFireLaneA, aSnowLaneC, aSnowLaneD, aFireLaneB, aWorkLaneA, aFireLaneC, aFireLaneD, aWorkLaneB, aOperationLaneA, aExpandLaneA, aOperationLaneB, aExpandLaneB, aOperationLaneC, aExpandLaneC, aOperationLaneD
        // write to: aWorkLaneA, aWorkLaneB, aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD
    
        // seed_loop_h loop 1
        // ingress from: aSnowLaneA, aSnowLaneB, aFireLaneA
        // ingress directions: aSnowLaneA forward forced, aSnowLaneB forward forced, aFireLaneA forward/backward random
        // cross from: aSnowLaneC, aSnowLaneD, aFireLaneB
        // cross directions: aSnowLaneC backward forced, aSnowLaneD backward forced, aFireLaneB backward/forward random
        // write to: aWorkLaneA
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aSnowLaneA[((aIndex + 4061U)) & S_BLOCK1], 11U) ^ RotL64(aSnowLaneB[((aIndex + 4440U)) & S_BLOCK1], 53U));
            aIngress ^= RotL64(aFireLaneA[((aIndex + 3156U)) & S_BLOCK1], 24U);
            aIngress = TwistMix64::DiffuseA(((aIngress ^ aPhaseHDomainWordIngress) ^ aNonceWordL));
            //
            aCross = (RotL64(aSnowLaneC[((S_BLOCK1 - aIndex + 3580U)) & S_BLOCK1], 39U) ^ RotL64(aSnowLaneD[((S_BLOCK1 - aIndex + 4086U)) & S_BLOCK1], 47U));
            aCross ^= RotL64(aFireLaneB[((S_BLOCK1 - aIndex + 1798U)) & S_BLOCK1], 27U);
            aCross = TwistMix64::DiffuseC(((aCross ^ aPhaseHDomainWordCross) ^ aNonceWordM));
            //
            aScatter = (RotL64(aIngress, 35U) ^ RotL64(aCross, 23U)) ^ (RotL64(aPrevious, 50U) + RotL64(aCarry, 11U));
            aScatter = TwistMix64::DiffuseB(((aScatter ^ aPhaseHDomainWordScatter) ^ aNonceWordC));
            //
            aOrbiterJ = ((aWandererC + RotL64(aPrevious, 27U)) + RotL64(aCarry, 35U)) + 16462052553719977502U;
            aOrbiterE = (aWandererE + RotL64(aCross, 13U)) + 12337064059566619581U;
            aOrbiterG = ((aWandererG + RotL64(aScatter, 43U)) + RotL64(aCarry, 5U)) + 15801005007094515447U;
            aOrbiterK = ((aWandererI + RotL64(aIngress, 50U)) + RotL64(aCarry, 51U)) + 8228706742665081656U;
            aOrbiterF = (((aWandererA + RotL64(aPrevious, 57U)) + 11006723027845190869U) + aPhaseHOrbiterAssignSaltD[((aIndex + 18U)) & S_SALT1]) + aNonceWordA;
            aOrbiterB = (((aWandererJ + RotL64(aIngress, 37U)) + 18173765337829177450U) + aPhaseHOrbiterAssignSaltC[(((31U - aIndex) + 9U)) & S_SALT1]) + aNonceWordE;
            aOrbiterD = (aWandererF + RotL64(aScatter, 3U)) + 530215083653542558U;
            //
            aOrbiterJ = (aOrbiterJ + aOrbiterE) + 6608611827035564511U;
            aOrbiterG = (aOrbiterG ^ aOrbiterJ) ^ 2246051826221626809U;
            aOrbiterG = RotL64((aOrbiterG * 6333352641495253539U), 29U);
            //
            aOrbiterE = ((aOrbiterE + aOrbiterK) + 5228575308895381421U) + aPhaseHOrbiterUpdateSaltF[(((31U - aIndex) + 17U)) & S_SALT1];
            aOrbiterF = ((aOrbiterF ^ aOrbiterE) ^ 10999213210689606857U) ^ aPhaseHOrbiterUpdateSaltC[(((31U - aIndex) + 29U)) & S_SALT1];
            aOrbiterF = RotL64((aOrbiterF * 5467601259546342925U), 51U);
            //
            aOrbiterK = (aOrbiterK + aOrbiterB) + 3773371037240485696U;
            aOrbiterJ = (aOrbiterJ ^ aOrbiterK) ^ 8887985779436152504U;
            aOrbiterJ = RotL64((aOrbiterJ * 698713082830739677U), 19U);
            //
            aOrbiterB = ((aOrbiterB + aOrbiterD) + 11150566414723818350U) + aNonceWordP;
            aOrbiterE = ((aOrbiterE ^ aOrbiterB) ^ 8336366151003049546U) ^ aPhaseHOrbiterUpdateSaltA[((aIndex + 3U)) & S_SALT1];
            aOrbiterE = RotL64((aOrbiterE * 9033771197242493699U), 37U);
            //
            aOrbiterD = ((aOrbiterD + aOrbiterG) + 13233968794237090787U) + aNonceWordG;
            aOrbiterK = (aOrbiterK ^ aOrbiterD) ^ 8172558473508478819U;
            aOrbiterK = RotL64((aOrbiterK * 17837070423649268435U), 57U);
            //
            aOrbiterF = (((aOrbiterF + aOrbiterJ) + 133564480283347997U) + aPhaseHOrbiterUpdateSaltD[((aIndex + 7U)) & S_SALT1]) + aNonceWordC;
            aOrbiterD = (aOrbiterD ^ aOrbiterF) ^ 15104810248883567064U;
            aOrbiterD = RotL64((aOrbiterD * 706802420642303533U), 43U);
            //
            aOrbiterG = (aOrbiterG + aOrbiterF) + 9138629520201127075U;
            aOrbiterB = (aOrbiterB ^ aOrbiterG) ^ 13993086066341664080U;
            aOrbiterB = RotL64((aOrbiterB * 4875046427147105077U), 5U);
            //
            aIngress = aOrbiterB ^ RotL64(aOrbiterK, 57U);
            aIngress = aIngress + (RotL64(aOrbiterJ, 43U) ^ aOrbiterG);
            aIngress = aIngress + (aOrbiterE ^ RotL64(aOrbiterD, 51U));
            aIngress = aIngress + RotL64(aOrbiterF, 37U);
            aIngress = TwistMix64::DiffuseC((aIngress + aScatter));
            //
            aWandererE = aWandererE + ((((RotL64(aCross, 43U) + RotL64(aOrbiterB, 3U)) + aOrbiterK) + RotL64(aCarry, 29U)) + aNonceWordI);
            aWandererF = aWandererF ^ (((RotL64(aIngress, 26U) + RotL64(aOrbiterE, 36U)) + aOrbiterK) + aPhaseHWandererUpdateSaltE[((aIndex + 11U)) & S_SALT1]);
            aWandererA = aWandererA + ((RotL64(aPrevious, 37U) + aOrbiterD) + RotL64(aOrbiterK, 57U));
            aWandererJ = aWandererJ ^ (((RotL64(aScatter, 5U) + RotL64(aOrbiterJ, 23U)) + aOrbiterG) + aNonceWordB);
            aWandererG = aWandererG + ((RotL64(aCross, 13U) + RotL64(aOrbiterF, 13U)) + aOrbiterG);
            aWandererI = aWandererI ^ (((RotL64(aPrevious, 19U) + aOrbiterD) + RotL64(aOrbiterB, 51U)) + aNonceWordJ);
            aWandererC = aWandererC + ((((RotL64(aScatter, 51U) + RotL64(aOrbiterJ, 43U)) + aOrbiterK) + RotL64(aCarry, 5U)) + aPhaseHWandererUpdateSaltC[(((31U - aIndex) + 27U)) & S_SALT1]);
            //
            aCarry = aCarry + (aWandererG ^ RotL64(aWandererE, 41U));
            aCarry = aCarry + (aWandererA ^ RotL64(aWandererI, 19U));
            aCarry = aCarry + (aWandererJ ^ RotL64(aWandererF, 48U));
            aCarry = aCarry + RotL64(aWandererC, 37U);
            aCarry = aCarry + RotL64(aIngress, 29U);
            aCarry = TwistMix64::DiffuseC(aCarry);
            //
            aWorkLaneA[aIndex] = aIngress;
        }
    
        // seed_loop_h loop 2
        // ingress from: aWorkLaneA, aSnowLaneC, aSnowLaneD, aFireLaneC
        // ingress directions: aWorkLaneA forward forced, aSnowLaneC forward forced, aSnowLaneD forward forced, aFireLaneC forward/backward random
        // cross from: aSnowLaneA, aSnowLaneB, aFireLaneD
        // cross directions: aSnowLaneA backward forced, aSnowLaneB backward forced, aFireLaneD backward/forward random
        // write to: aWorkLaneB
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aWorkLaneA[((aIndex + 6486U)) & S_BLOCK1], 53U) ^ RotL64(aSnowLaneC[((aIndex + 8898U)) & S_BLOCK1], 21U));
            aIngress ^= (RotL64(aSnowLaneD[((aIndex + 9624U)) & S_BLOCK1], 29U) ^ RotL64(aFireLaneC[((S_BLOCK1 - aIndex + 6336U)) & S_BLOCK1], 44U));
            aIngress = TwistMix64::DiffuseC(((aIngress ^ aPhaseHDomainWordIngress) ^ aNonceWordL));
            //
            aCross = (RotL64(aSnowLaneA[((S_BLOCK1 - aIndex + 7867U)) & S_BLOCK1], 5U) ^ RotL64(aSnowLaneB[((S_BLOCK1 - aIndex + 10295U)) & S_BLOCK1], 50U));
            aCross ^= RotL64(aFireLaneD[((aIndex + 10656U)) & S_BLOCK1], 19U);
            aCross = TwistMix64::DiffuseA(((aCross ^ aPhaseHDomainWordCross) ^ aNonceWordI));
            //
            aScatter = (RotL64(aCross, 57U) ^ RotL64(aPrevious, 38U)) + (RotL64(aIngress, 19U) + RotL64(aCarry, 5U));
            aScatter = TwistMix64::DiffuseC(((aScatter ^ aPhaseHDomainWordScatter) ^ aNonceWordO));
            //
            aOrbiterE = (((aWandererJ + RotL64(aIngress, 51U)) + RotL64(aCarry, 57U)) + 3248574644570178787U) + aNonceWordH;
            aOrbiterC = (aWandererK + RotL64(aScatter, 3U)) + 4506961512959200024U;
            aOrbiterK = ((aWandererH + RotL64(aCross, 27U)) + 8423739774540738590U) + aNonceWordM;
            aOrbiterA = ((aWandererI + RotL64(aPrevious, 10U)) + 6593975869641735337U) + aPhaseHOrbiterAssignSaltE[(((31U - aIndex) + 25U)) & S_SALT1];
            aOrbiterI = ((((aWandererF + RotL64(aCross, 19U)) + RotL64(aCarry, 27U)) + 16441716090557369103U) + aPhaseHOrbiterAssignSaltA[(((31U - aIndex) + 8U)) & S_SALT1]) + aNonceWordC;
            aOrbiterJ = ((aWandererG + RotL64(aScatter, 57U)) + RotL64(aCarry, 41U)) + 7936601450453207914U;
            aOrbiterD = (aWandererE + RotL64(aPrevious, 35U)) + 13333752583560167065U;
            //
            aOrbiterE = (((aOrbiterE + aOrbiterC) + 8013703284795432973U) + aPhaseHOrbiterUpdateSaltE[(((31U - aIndex) + 21U)) & S_SALT1]) + aNonceWordG;
            aOrbiterK = ((aOrbiterK ^ aOrbiterE) ^ 2349852779887439236U) ^ aPhaseHOrbiterUpdateSaltB[((aIndex + 15U)) & S_SALT1];
            aOrbiterK = RotL64((aOrbiterK * 2422888500648100783U), 53U);
            //
            aOrbiterA = (aOrbiterA + aOrbiterI) + 5318539364763284138U;
            aOrbiterC = (aOrbiterC ^ aOrbiterA) ^ 11450957608502944376U;
            aOrbiterC = RotL64((aOrbiterC * 1957880366707810635U), 11U);
            //
            aOrbiterJ = ((aOrbiterJ + aOrbiterK) + 9058992558327552687U) + aNonceWordP;
            aOrbiterA = (aOrbiterA ^ aOrbiterJ) ^ 632095686920230926U;
            aOrbiterA = RotL64((aOrbiterA * 12460364388358520799U), 37U);
            //
            aOrbiterI = ((aOrbiterI + aOrbiterE) + 14734218428913777098U) + aPhaseHOrbiterUpdateSaltC[((aIndex + 27U)) & S_SALT1];
            aOrbiterJ = (aOrbiterJ ^ aOrbiterI) ^ 16344357661370784442U;
            aOrbiterJ = RotL64((aOrbiterJ * 15049472842002138369U), 43U);
            //
            aOrbiterK = (aOrbiterK + aOrbiterD) + 2981145363531184308U;
            aOrbiterI = (aOrbiterI ^ aOrbiterK) ^ 14176472085175714494U;
            aOrbiterI = RotL64((aOrbiterI * 2584623327412130939U), 27U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterA) + 11198457590069700889U;
            aOrbiterE = (aOrbiterE ^ aOrbiterD) ^ 952584436750426828U;
            aOrbiterE = RotL64((aOrbiterE * 1165713888651280355U), 19U);
            //
            aOrbiterC = (aOrbiterC + aOrbiterJ) + 4311591763498985972U;
            aOrbiterD = (((aOrbiterD ^ aOrbiterC) ^ 16194341833989936369U) ^ aPhaseHOrbiterUpdateSaltA[(((31U - aIndex) + 26U)) & S_SALT1]) ^ aNonceWordK;
            aOrbiterD = RotL64((aOrbiterD * 9997934560195932575U), 3U);
            //
            aIngress = aOrbiterK ^ RotL64(aOrbiterC, 35U);
            aIngress = aIngress + (aOrbiterJ ^ RotL64(aOrbiterD, 43U));
            aIngress = aIngress + (aOrbiterI ^ RotL64(aOrbiterA, 51U));
            aIngress = aIngress + RotL64(aOrbiterE, 11U);
            aIngress = TwistMix64::DiffuseC((aIngress + aScatter));
            //
            aWandererK = aWandererK ^ ((RotL64(aCross, 41U) + RotL64(aOrbiterK, 41U)) + aOrbiterJ);
            aWandererI = aWandererI + ((((RotL64(aScatter, 51U) + aOrbiterK) + RotL64(aOrbiterE, 26U)) + RotL64(aCarry, 21U)) + aPhaseHWandererUpdateSaltD[((aIndex + 5U)) & S_SALT1]);
            aWandererE = aWandererE ^ ((RotL64(aIngress, 35U) + aOrbiterD) + RotL64(aOrbiterC, 19U));
            aWandererJ = aWandererJ + ((((RotL64(aPrevious, 57U) + RotL64(aOrbiterJ, 13U)) + aOrbiterI) + RotL64(aCarry, 37U)) + aNonceWordF);
            aWandererG = aWandererG ^ (((RotL64(aScatter, 12U) + aOrbiterC) + RotL64(aOrbiterE, 3U)) + aNonceWordB);
            aWandererH = aWandererH + (((RotL64(aPrevious, 27U) + aOrbiterC) + RotL64(aOrbiterA, 57U)) + aPhaseHWandererUpdateSaltF[((aIndex + 10U)) & S_SALT1]);
            aWandererF = aWandererF ^ ((RotL64(aIngress, 5U) + RotL64(aOrbiterA, 51U)) + aOrbiterE);
            //
            aCarry = aCarry + (aWandererJ ^ RotL64(aWandererG, 36U));
            aCarry = aCarry + (aWandererE ^ RotL64(aWandererK, 27U));
            aCarry = aCarry + (aWandererH ^ RotL64(aWandererF, 5U));
            aCarry = aCarry + RotL64(aWandererI, 53U);
            aCarry = aCarry + RotL64(aIngress, 13U);
            aCarry = TwistMix64::DiffuseC(aCarry);
            //
            aWorkLaneB[S_BLOCK1 - aIndex] = aIngress;
        }
    
        // seed_loop_h loop 3
        // ingress from: aWorkLaneB, aSnowLaneA, aOperationLaneA
        // ingress directions: aWorkLaneB forward forced, aSnowLaneA forward forced, aOperationLaneA forward/backward random
        // cross from: aWorkLaneA, aSnowLaneC
        // cross directions: aWorkLaneA backward forced, aSnowLaneC backward/forward random
        // write to: aExpandLaneA
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aWorkLaneB[((aIndex + 13824U)) & S_BLOCK1], 13U) ^ RotL64(aSnowLaneA[((aIndex + 15124U)) & S_BLOCK1], 5U));
            aIngress ^= RotL64(aOperationLaneA[((aIndex + 10987U)) & S_BLOCK1], 53U);
            aIngress = TwistMix64::DiffuseC(((aIngress ^ aPhaseHDomainWordIngress) ^ aNonceWordB));
            //
            aCross = RotL64(aWorkLaneA[((S_BLOCK1 - aIndex + 14042U)) & S_BLOCK1], 13U) ^ RotL64(aSnowLaneC[((aIndex + 12423U)) & S_BLOCK1], 3U);
            aCross = TwistMix64::DiffuseB(((aCross ^ aPhaseHDomainWordCross) ^ aNonceWordC));
            //
            aScatter = (RotL64(aIngress, 23U) ^ RotL64(aCross, 5U)) ^ (RotL64(aCarry, 36U) + RotL64(aPrevious, 57U));
            aScatter = TwistMix64::DiffuseC(((aScatter ^ aPhaseHDomainWordScatter) ^ aNonceWordP));
            //
            aOrbiterB = ((aWandererH + RotL64(aScatter, 51U)) + 13960289014350612206U) + aPhaseHOrbiterAssignSaltB[((aIndex + 28U)) & S_SALT1];
            aOrbiterK = ((aWandererB + RotL64(aCross, 58U)) + RotL64(aCarry, 43U)) + 3483331015269589730U;
            aOrbiterJ = (aWandererF + RotL64(aIngress, 37U)) + 6873299241002444518U;
            aOrbiterC = (aWandererJ + RotL64(aPrevious, 13U)) + 3562094007125534229U;
            aOrbiterD = (((aWandererC + RotL64(aIngress, 3U)) + 11422367439932782705U) + aPhaseHOrbiterAssignSaltF[((aIndex + 14U)) & S_SALT1]) + aNonceWordN;
            aOrbiterF = (((aWandererK + RotL64(aPrevious, 43U)) + RotL64(aCarry, 23U)) + 532453428514259816U) + aNonceWordH;
            aOrbiterA = (((aWandererG + RotL64(aScatter, 19U)) + RotL64(aCarry, 11U)) + 17810941465810193088U) + aNonceWordP;
            //
            aOrbiterB = (aOrbiterB + aOrbiterK) + 11869759058631106331U;
            aOrbiterJ = (aOrbiterJ ^ aOrbiterB) ^ 8837581071876177566U;
            aOrbiterJ = RotL64((aOrbiterJ * 15329827515970522213U), 35U);
            //
            aOrbiterC = (aOrbiterC + aOrbiterD) + 17185378327053837778U;
            aOrbiterB = (aOrbiterB ^ aOrbiterC) ^ 7578253375676981500U;
            aOrbiterB = RotL64((aOrbiterB * 13371647568758721729U), 27U);
            //
            aOrbiterK = ((aOrbiterK + aOrbiterJ) + 17112646434432814442U) + aPhaseHOrbiterUpdateSaltA[((aIndex + 25U)) & S_SALT1];
            aOrbiterF = (aOrbiterF ^ aOrbiterK) ^ 14949096407295697881U;
            aOrbiterF = RotL64((aOrbiterF * 14770977858283051753U), 13U);
            //
            aOrbiterF = ((aOrbiterF + aOrbiterA) + 4259590620758467836U) + aPhaseHOrbiterUpdateSaltE[((aIndex + 7U)) & S_SALT1];
            aOrbiterC = ((aOrbiterC ^ aOrbiterF) ^ 6534899413644542303U) ^ aPhaseHOrbiterUpdateSaltC[(((31U - aIndex) + 11U)) & S_SALT1];
            aOrbiterC = RotL64((aOrbiterC * 7987609419215568661U), 51U);
            //
            aOrbiterJ = (aOrbiterJ + aOrbiterF) + 2637407498893694243U;
            aOrbiterA = (aOrbiterA ^ aOrbiterJ) ^ 15819295597921425711U;
            aOrbiterA = RotL64((aOrbiterA * 5202015597375051399U), 57U);
            //
            aOrbiterA = ((aOrbiterA + aOrbiterC) + 6373559542002699718U) + aNonceWordJ;
            aOrbiterD = (((aOrbiterD ^ aOrbiterA) ^ 11694562937392022505U) ^ aPhaseHOrbiterUpdateSaltD[(((31U - aIndex) + 15U)) & S_SALT1]) ^ aNonceWordE;
            aOrbiterD = RotL64((aOrbiterD * 9311557972331218597U), 19U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterB) + 3308736483775453062U;
            aOrbiterK = (aOrbiterK ^ aOrbiterD) ^ 12749929710650475901U;
            aOrbiterK = RotL64((aOrbiterK * 248428400724560945U), 41U);
            //
            aIngress = RotL64(aOrbiterK, 60U) ^ aOrbiterB;
            aIngress = aIngress + (aOrbiterC ^ RotL64(aOrbiterA, 53U));
            aIngress = aIngress + (RotL64(aOrbiterF, 27U) ^ aOrbiterJ);
            aIngress = aIngress + RotL64(aOrbiterD, 37U);
            aIngress = TwistMix64::DiffuseC((aIngress + aScatter));
            //
            aWandererJ = aWandererJ + ((((RotL64(aScatter, 19U) + RotL64(aOrbiterJ, 57U)) + aOrbiterB) + RotL64(aCarry, 23U)) + aNonceWordD);
            aWandererB = aWandererB ^ ((RotL64(aPrevious, 51U) + RotL64(aOrbiterF, 51U)) + aOrbiterC);
            aWandererF = aWandererF + (((RotL64(aIngress, 57U) + RotL64(aOrbiterJ, 41U)) + aOrbiterF) + aNonceWordA);
            aWandererK = aWandererK ^ (((RotL64(aCross, 11U) + aOrbiterD) + RotL64(aOrbiterA, 5U)) + aPhaseHWandererUpdateSaltB[((aIndex + 24U)) & S_SALT1]);
            aWandererH = aWandererH + ((RotL64(aIngress, 29U) + aOrbiterB) + RotL64(aOrbiterD, 20U));
            aWandererC = aWandererC ^ (((RotL64(aPrevious, 4U) + aOrbiterB) + RotL64(aOrbiterK, 13U)) + aPhaseHWandererUpdateSaltA[(((31U - aIndex) + 3U)) & S_SALT1]);
            aWandererG = aWandererG + ((((RotL64(aCross, 43U) + RotL64(aOrbiterB, 35U)) + aOrbiterC) + RotL64(aCarry, 37U)) + aNonceWordM);
            //
            aCarry = aCarry + (aWandererB ^ RotL64(aWandererC, 60U));
            aCarry = aCarry + (RotL64(aWandererH, 41U) ^ aWandererG);
            aCarry = aCarry + (RotL64(aWandererK, 27U) ^ aWandererJ);
            aCarry = aCarry + RotL64(aWandererF, 37U);
            aCarry = aCarry + RotL64(aIngress, 23U);
            aCarry = TwistMix64::DiffuseA(aCarry);
            //
            aExpandLaneA[aIndex] = aIngress;
        }
    
        // seed_loop_h loop 4
        // ingress from: aExpandLaneA, aWorkLaneA, aOperationLaneB
        // ingress directions: aExpandLaneA forward forced, aWorkLaneA forward forced, aOperationLaneB forward/backward random
        // cross from: aWorkLaneB, aSnowLaneD
        // cross directions: aWorkLaneB backward forced, aSnowLaneD backward/forward random
        // write to: aExpandLaneB
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aExpandLaneA[((aIndex + 17716U)) & S_BLOCK1], 3U) ^ RotL64(aWorkLaneA[((aIndex + 18390U)) & S_BLOCK1], 42U));
            aIngress ^= RotL64(aOperationLaneB[((aIndex + 17555U)) & S_BLOCK1], 57U);
            aIngress = TwistMix64::DiffuseA(((aIngress ^ aPhaseHDomainWordIngress) ^ aNonceWordM));
            //
            aCross = RotL64(aWorkLaneB[((S_BLOCK1 - aIndex + 16913U)) & S_BLOCK1], 43U) ^ RotL64(aSnowLaneD[((aIndex + 17090U)) & S_BLOCK1], 11U);
            aCross = TwistMix64::DiffuseA(((aCross ^ aPhaseHDomainWordCross) ^ aNonceWordF));
            //
            aScatter = (RotL64(aPrevious, 56U) + RotL64(aCarry, 13U)) + (RotL64(aCross, 29U) ^ RotL64(aIngress, 43U));
            aScatter = TwistMix64::DiffuseB(((aScatter ^ aPhaseHDomainWordScatter) ^ aNonceWordD));
            //
            aOrbiterF = ((aWandererF + RotL64(aIngress, 35U)) + RotL64(aCarry, 27U)) + 5576732410244514238U;
            aOrbiterJ = ((aWandererJ + RotL64(aScatter, 47U)) + RotL64(aCarry, 43U)) + 2833808925935929629U;
            aOrbiterB = ((aWandererI + RotL64(aCross, 5U)) + 3670188682914544792U) + aNonceWordI;
            aOrbiterE = (((aWandererC + RotL64(aPrevious, 41U)) + RotL64(aCarry, 5U)) + 15759072378887814995U) + aNonceWordG;
            aOrbiterK = ((aWandererH + RotL64(aIngress, 29U)) + 13934007231137439994U) + aPhaseHOrbiterAssignSaltD[((aIndex + 17U)) & S_SALT1];
            aOrbiterA = ((aWandererD + RotL64(aPrevious, 19U)) + 11022225696007690512U) + aPhaseHOrbiterAssignSaltC[((aIndex + 8U)) & S_SALT1];
            aOrbiterC = ((aWandererG + RotL64(aCross, 12U)) + 16989177104453635790U) + aNonceWordN;
            //
            aOrbiterF = ((aOrbiterF + aOrbiterJ) + 9256930045263527091U) + aNonceWordD;
            aOrbiterB = (aOrbiterB ^ aOrbiterF) ^ 17788596104417068290U;
            aOrbiterB = RotL64((aOrbiterB * 675554110563253305U), 5U);
            //
            aOrbiterE = ((aOrbiterE + aOrbiterK) + 17044369456673337625U) + aPhaseHOrbiterUpdateSaltE[((aIndex + 11U)) & S_SALT1];
            aOrbiterA = ((aOrbiterA ^ aOrbiterE) ^ 1310908395523250343U) ^ aPhaseHOrbiterUpdateSaltC[(((31U - aIndex) + 3U)) & S_SALT1];
            aOrbiterA = RotL64((aOrbiterA * 16305084373037705921U), 41U);
            //
            aOrbiterJ = ((aOrbiterJ + aOrbiterB) + 12067065689034065422U) + aNonceWordK;
            aOrbiterC = ((aOrbiterC ^ aOrbiterJ) ^ 15130844248737512262U) ^ aNonceWordP;
            aOrbiterC = RotL64((aOrbiterC * 9409499577465934107U), 23U);
            //
            aOrbiterK = (aOrbiterK + aOrbiterA) + 14532689204495587494U;
            aOrbiterF = (aOrbiterF ^ aOrbiterK) ^ 8198147292120244178U;
            aOrbiterF = RotL64((aOrbiterF * 1418356389507740991U), 11U);
            //
            aOrbiterB = ((aOrbiterB + aOrbiterC) + 5485494458627163347U) + aPhaseHOrbiterUpdateSaltA[((aIndex + 25U)) & S_SALT1];
            aOrbiterE = (aOrbiterE ^ aOrbiterB) ^ 10830008207150307611U;
            aOrbiterE = RotL64((aOrbiterE * 6526039534042499457U), 29U);
            //
            aOrbiterA = ((aOrbiterA + aOrbiterF) + 17770065502486618029U) + aNonceWordC;
            aOrbiterJ = (aOrbiterJ ^ aOrbiterA) ^ 6397859353395335459U;
            aOrbiterJ = RotL64((aOrbiterJ * 14286997752368893825U), 35U);
            //
            aOrbiterC = (aOrbiterC + aOrbiterE) + 5128700697381508319U;
            aOrbiterK = ((aOrbiterK ^ aOrbiterC) ^ 7103394110057060499U) ^ aPhaseHOrbiterUpdateSaltF[(((31U - aIndex) + 26U)) & S_SALT1];
            aOrbiterK = RotL64((aOrbiterK * 5053680689949149633U), 47U);
            //
            aIngress = RotL64(aOrbiterE, 47U) ^ aOrbiterA;
            aIngress = aIngress + (RotL64(aOrbiterF, 41U) ^ aOrbiterB);
            aIngress = aIngress + (RotL64(aOrbiterK, 57U) ^ aOrbiterC);
            aIngress = aIngress + RotL64(aOrbiterJ, 29U);
            aIngress = TwistMix64::DiffuseC((aIngress + aScatter));
            //
            aWandererD = aWandererD ^ (((RotL64(aIngress, 53U) + aOrbiterA) + RotL64(aOrbiterF, 57U)) + aPhaseHWandererUpdateSaltC[((aIndex + 28U)) & S_SALT1]);
            aWandererG = aWandererG + ((((RotL64(aPrevious, 47U) + aOrbiterB) + RotL64(aOrbiterF, 47U)) + RotL64(aCarry, 37U)) + aPhaseHWandererUpdateSaltE[(((31U - aIndex) + 29U)) & S_SALT1]);
            aWandererI = aWandererI ^ (((RotL64(aCross, 27U) + RotL64(aOrbiterA, 5U)) + aOrbiterK) + aNonceWordH);
            aWandererC = aWandererC + (((RotL64(aScatter, 39U) + aOrbiterE) + RotL64(aOrbiterB, 35U)) + RotL64(aCarry, 53U));
            aWandererJ = aWandererJ ^ (((RotL64(aCross, 21U) + aOrbiterJ) + RotL64(aOrbiterA, 18U)) + aNonceWordA);
            aWandererF = aWandererF + (((RotL64(aScatter, 5U) + aOrbiterA) + RotL64(aOrbiterE, 27U)) + aNonceWordB);
            aWandererH = aWandererH ^ (((RotL64(aPrevious, 14U) + RotL64(aOrbiterJ, 11U)) + aOrbiterC) + aNonceWordJ);
            //
            aCarry = aCarry + (RotL64(aWandererD, 29U) ^ aWandererH);
            aCarry = aCarry + (aWandererJ ^ RotL64(aWandererG, 42U));
            aCarry = aCarry + (aWandererF ^ RotL64(aWandererC, 21U));
            aCarry = aCarry + RotL64(aWandererI, 53U);
            aCarry = aCarry + RotL64(aIngress, 47U);
            aCarry = TwistMix64::DiffuseC(aCarry);
            //
            aExpandLaneB[S_BLOCK1 - aIndex] = aIngress;
        }
    
        // seed_loop_h loop 5
        // ingress from: aExpandLaneB, aWorkLaneB, aOperationLaneC
        // ingress directions: aExpandLaneB forward forced, aWorkLaneB forward forced, aOperationLaneC forward/backward random
        // cross from: aExpandLaneA, aWorkLaneA
        // cross directions: aExpandLaneA backward forced, aWorkLaneA backward/forward random
        // write to: aExpandLaneC
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aExpandLaneB[((aIndex + 22777U)) & S_BLOCK1], 5U) ^ RotL64(aWorkLaneB[((aIndex + 25005U)) & S_BLOCK1], 23U));
            aIngress ^= RotL64(aOperationLaneC[((aIndex + 26091U)) & S_BLOCK1], 34U);
            aIngress = TwistMix64::DiffuseA(((aIngress ^ aPhaseHDomainWordIngress) ^ aNonceWordM));
            //
            aCross = RotL64(aExpandLaneA[((S_BLOCK1 - aIndex + 25133U)) & S_BLOCK1], 36U) ^ RotL64(aWorkLaneA[((S_BLOCK1 - aIndex + 25011U)) & S_BLOCK1], 21U);
            aCross = TwistMix64::DiffuseC(((aCross ^ aPhaseHDomainWordCross) ^ aNonceWordB));
            //
            aScatter = (RotL64(aCarry, 48U) ^ RotL64(aIngress, 5U)) + (RotL64(aPrevious, 19U) ^ RotL64(aCross, 35U));
            aScatter = TwistMix64::DiffuseB(((aScatter ^ aPhaseHDomainWordScatter) ^ aNonceWordN));
            //
            aOrbiterE = (aWandererD + RotL64(aScatter, 3U)) + 8367680518550579791U;
            aOrbiterK = (aWandererH + RotL64(aPrevious, 19U)) + 11491674725611181241U;
            aOrbiterJ = (((aWandererJ + RotL64(aIngress, 57U)) + RotL64(aCarry, 19U)) + 16673861720782164214U) + aPhaseHOrbiterAssignSaltA[((aIndex + 19U)) & S_SALT1];
            aOrbiterC = ((((aWandererG + RotL64(aCross, 41U)) + RotL64(aCarry, 37U)) + 9786610124108350855U) + aPhaseHOrbiterAssignSaltE[(((31U - aIndex) + 17U)) & S_SALT1]) + aNonceWordH;
            aOrbiterG = ((aWandererB + RotL64(aPrevious, 29U)) + 5745080601557577637U) + aNonceWordG;
            aOrbiterI = ((aWandererI + RotL64(aCross, 50U)) + 1959402215131684684U) + aNonceWordI;
            aOrbiterF = (((aWandererK + RotL64(aScatter, 13U)) + RotL64(aCarry, 5U)) + 6121650036079196522U) + aNonceWordA;
            //
            aOrbiterE = (aOrbiterE + aOrbiterK) + 12016309761037342392U;
            aOrbiterJ = (aOrbiterJ ^ aOrbiterE) ^ 5986936646177049603U;
            aOrbiterJ = RotL64((aOrbiterJ * 3585650475703294895U), 13U);
            //
            aOrbiterC = ((aOrbiterC + aOrbiterE) + 1000367700904043468U) + aPhaseHOrbiterUpdateSaltF[((aIndex + 14U)) & S_SALT1];
            aOrbiterG = (aOrbiterG ^ aOrbiterC) ^ 17425288243569101032U;
            aOrbiterG = RotL64((aOrbiterG * 2174614006719048535U), 3U);
            //
            aOrbiterG = (aOrbiterG + aOrbiterJ) + 4856917474950325209U;
            aOrbiterI = (aOrbiterI ^ aOrbiterG) ^ 16312111093223166419U;
            aOrbiterI = RotL64((aOrbiterI * 11046477664487805241U), 41U);
            //
            aOrbiterJ = (aOrbiterJ + aOrbiterF) + 456110002032422270U;
            aOrbiterC = ((aOrbiterC ^ aOrbiterJ) ^ 11393724374787795662U) ^ aPhaseHOrbiterUpdateSaltA[((aIndex + 25U)) & S_SALT1];
            aOrbiterC = RotL64((aOrbiterC * 1176984359123668389U), 57U);
            //
            aOrbiterI = ((aOrbiterI + aOrbiterC) + 8378176867715697176U) + aPhaseHOrbiterUpdateSaltE[((aIndex + 11U)) & S_SALT1];
            aOrbiterK = (aOrbiterK ^ aOrbiterI) ^ 8086186452345234815U;
            aOrbiterK = RotL64((aOrbiterK * 8450438271765985235U), 35U);
            //
            aOrbiterK = ((aOrbiterK + aOrbiterG) + 8470349167474173245U) + aNonceWordD;
            aOrbiterF = ((aOrbiterF ^ aOrbiterK) ^ 2528229938740192694U) ^ aPhaseHOrbiterUpdateSaltB[(((31U - aIndex) + 26U)) & S_SALT1];
            aOrbiterF = RotL64((aOrbiterF * 8717790851266520943U), 19U);
            //
            aOrbiterF = ((aOrbiterF + aOrbiterI) + 13247168811545753141U) + aNonceWordO;
            aOrbiterE = (aOrbiterE ^ aOrbiterF) ^ 8745293957516815264U;
            aOrbiterE = RotL64((aOrbiterE * 14270617180621072619U), 47U);
            //
            aIngress = aOrbiterE ^ RotL64(aOrbiterG, 57U);
            aIngress = aIngress + (RotL64(aOrbiterJ, 35U) ^ aOrbiterC);
            aIngress = aIngress + (RotL64(aOrbiterI, 5U) ^ aOrbiterK);
            aIngress = aIngress + RotL64(aOrbiterF, 41U);
            aIngress = TwistMix64::DiffuseB((aIngress + aScatter));
            //
            aWandererB = aWandererB + (((RotL64(aCross, 51U) + RotL64(aOrbiterG, 47U)) + aOrbiterK) + aNonceWordF);
            aWandererK = aWandererK ^ ((((RotL64(aIngress, 57U) + aOrbiterG) + RotL64(aOrbiterJ, 21U)) + aNonceWordP) + aPhaseHWandererUpdateSaltF[(((31U - aIndex) + 12U)) & S_SALT1]);
            aWandererD = aWandererD + (((RotL64(aPrevious, 41U) + RotL64(aOrbiterJ, 35U)) + aOrbiterE) + aNonceWordL);
            aWandererI = aWandererI ^ ((RotL64(aScatter, 13U) + RotL64(aOrbiterF, 29U)) + aOrbiterG);
            aWandererG = aWandererG + (((RotL64(aIngress, 35U) + RotL64(aOrbiterE, 5U)) + aOrbiterC) + RotL64(aCarry, 47U));
            aWandererJ = aWandererJ ^ ((((RotL64(aScatter, 26U) + RotL64(aOrbiterI, 41U)) + aOrbiterC) + aNonceWordK) + aPhaseHWandererUpdateSaltD[(((31U - aIndex) + 4U)) & S_SALT1]);
            aWandererH = aWandererH + (((RotL64(aPrevious, 3U) + aOrbiterF) + RotL64(aOrbiterE, 56U)) + RotL64(aCarry, 3U));
            //
            aCarry = aCarry + (RotL64(aWandererI, 39U) ^ aWandererK);
            aCarry = aCarry + (aWandererJ ^ RotL64(aWandererD, 46U));
            aCarry = aCarry + (aWandererH ^ RotL64(aWandererB, 19U));
            aCarry = aCarry + RotL64(aWandererG, 23U);
            aCarry = aCarry + RotL64(aIngress, 53U);
            aCarry = TwistMix64::DiffuseA(aCarry);
            //
            aExpandLaneC[aIndex] = aIngress;
        }
    
        // seed_loop_h loop 6
        // ingress from: aExpandLaneC, aExpandLaneA, aOperationLaneD
        // ingress directions: aExpandLaneC forward forced, aExpandLaneA forward forced, aOperationLaneD forward/backward random
        // cross from: aExpandLaneB, aSnowLaneB
        // cross directions: aExpandLaneB backward forced, aSnowLaneB backward/forward random
        // write to: aExpandLaneD
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aExpandLaneC[((aIndex + 32365U)) & S_BLOCK1], 5U) ^ RotL64(aExpandLaneA[((aIndex + 28277U)) & S_BLOCK1], 19U));
            aIngress ^= RotL64(aOperationLaneD[((S_BLOCK1 - aIndex + 28310U)) & S_BLOCK1], 30U);
            aIngress = TwistMix64::DiffuseB(((aIngress ^ aPhaseHDomainWordIngress) ^ aNonceWordB));
            //
            aCross = RotL64(aExpandLaneB[((S_BLOCK1 - aIndex + 29214U)) & S_BLOCK1], 29U) ^ RotL64(aSnowLaneB[((aIndex + 27759U)) & S_BLOCK1], 18U);
            aCross = TwistMix64::DiffuseB(((aCross ^ aPhaseHDomainWordCross) ^ aNonceWordM));
            //
            aScatter = (RotL64(aCross, 56U) ^ RotL64(aPrevious, 37U)) + (RotL64(aCarry, 23U) ^ RotL64(aIngress, 5U));
            aScatter = TwistMix64::DiffuseA(((aScatter ^ aPhaseHDomainWordScatter) ^ aNonceWordP));
            //
            aOrbiterF = (((aWandererI + RotL64(aCross, 57U)) + 6916817163240024692U) + aPhaseHOrbiterAssignSaltB[((aIndex + 29U)) & S_SALT1]) + aNonceWordK;
            aOrbiterH = ((aWandererF + RotL64(aScatter, 5U)) + 14554930751292077817U) + aNonceWordC;
            aOrbiterG = (aWandererB + RotL64(aPrevious, 19U)) + 1098305064484336101U;
            aOrbiterA = (((aWandererA + RotL64(aIngress, 27U)) + RotL64(aCarry, 3U)) + 12192821172420471527U) + aNonceWordO;
            aOrbiterI = ((((aWandererC + RotL64(aCross, 13U)) + RotL64(aCarry, 41U)) + 2435134991707318845U) + aPhaseHOrbiterAssignSaltF[((aIndex + 10U)) & S_SALT1]) + aNonceWordE;
            aOrbiterC = (aWandererE + RotL64(aIngress, 42U)) + 1896745368738512624U;
            aOrbiterJ = ((aWandererD + RotL64(aScatter, 35U)) + RotL64(aCarry, 53U)) + 1114996424222923873U;
            //
            aOrbiterF = (aOrbiterF + aOrbiterH) + 9839135798371512656U;
            aOrbiterG = (aOrbiterG ^ aOrbiterF) ^ 8037967239603177043U;
            aOrbiterG = RotL64((aOrbiterG * 7848951103759663025U), 23U);
            //
            aOrbiterA = (aOrbiterA + aOrbiterI) + 15185468738487237432U;
            aOrbiterH = (aOrbiterH ^ aOrbiterA) ^ 4912098316394854543U;
            aOrbiterH = RotL64((aOrbiterH * 3072785550384399929U), 47U);
            //
            aOrbiterC = ((aOrbiterC + aOrbiterA) + 13142688607850380888U) + aNonceWordN;
            aOrbiterF = ((aOrbiterF ^ aOrbiterC) ^ 4507379759608945839U) ^ aPhaseHOrbiterUpdateSaltD[(((31U - aIndex) + 13U)) & S_SALT1];
            aOrbiterF = RotL64((aOrbiterF * 2989332387754215967U), 35U);
            //
            aOrbiterH = ((aOrbiterH + aOrbiterC) + 7299006009652289342U) + aPhaseHOrbiterUpdateSaltF[(((31U - aIndex) + 23U)) & S_SALT1];
            aOrbiterJ = ((aOrbiterJ ^ aOrbiterH) ^ 5390655277207053627U) ^ aNonceWordL;
            aOrbiterJ = RotL64((aOrbiterJ * 10973744708856143715U), 11U);
            //
            aOrbiterI = ((aOrbiterI + aOrbiterG) + 6744737023577785725U) + aPhaseHOrbiterUpdateSaltB[((aIndex + 15U)) & S_SALT1];
            aOrbiterC = ((aOrbiterC ^ aOrbiterI) ^ 15539737698867067285U) ^ aNonceWordG;
            aOrbiterC = RotL64((aOrbiterC * 4686092035261336911U), 41U);
            //
            aOrbiterJ = (aOrbiterJ + aOrbiterF) + 13329866734681377952U;
            aOrbiterI = ((aOrbiterI ^ aOrbiterJ) ^ 13284937458969166257U) ^ aPhaseHOrbiterUpdateSaltA[(((31U - aIndex) + 26U)) & S_SALT1];
            aOrbiterI = RotL64((aOrbiterI * 3965985432462699445U), 5U);
            //
            aOrbiterG = (aOrbiterG + aOrbiterJ) + 8695002088915702168U;
            aOrbiterA = ((aOrbiterA ^ aOrbiterG) ^ 3858059421620839286U) ^ aNonceWordI;
            aOrbiterA = RotL64((aOrbiterA * 9559783727301092937U), 29U);
            //
            aIngress = aOrbiterF ^ RotL64(aOrbiterI, 53U);
            aIngress = aIngress + (RotL64(aOrbiterA, 21U) ^ aOrbiterG);
            aIngress = aIngress + (aOrbiterH ^ RotL64(aOrbiterC, 60U));
            aIngress = aIngress + RotL64(aOrbiterJ, 13U);
            aIngress = TwistMix64::DiffuseA((aIngress + aScatter));
            //
            aWandererA = aWandererA ^ (((RotL64(aScatter, 51U) + aOrbiterI) + RotL64(aOrbiterG, 21U)) + aPhaseHWandererUpdateSaltA[(((31U - aIndex) + 9U)) & S_SALT1]);
            aWandererF = aWandererF + ((((RotL64(aPrevious, 58U) + aOrbiterC) + RotL64(aOrbiterF, 11U)) + RotL64(aCarry, 57U)) + aNonceWordF);
            aWandererE = aWandererE ^ (((RotL64(aIngress, 3U) + aOrbiterF) + RotL64(aOrbiterG, 51U)) + aPhaseHWandererUpdateSaltB[((aIndex + 19U)) & S_SALT1]);
            aWandererI = aWandererI + (((RotL64(aCross, 27U) + aOrbiterF) + RotL64(aOrbiterJ, 28U)) + aNonceWordP);
            aWandererB = aWandererB ^ ((RotL64(aIngress, 35U) + aOrbiterJ) + RotL64(aOrbiterH, 5U));
            aWandererC = aWandererC + (((RotL64(aScatter, 43U) + aOrbiterH) + RotL64(aOrbiterF, 57U)) + RotL64(aCarry, 43U));
            aWandererD = aWandererD ^ ((RotL64(aPrevious, 19U) + RotL64(aOrbiterH, 39U)) + aOrbiterA);
            //
            aCarry = aCarry + (aWandererI ^ RotL64(aWandererA, 53U));
            aCarry = aCarry + (RotL64(aWandererD, 20U) ^ aWandererC);
            aCarry = aCarry + (RotL64(aWandererE, 41U) ^ aWandererF);
            aCarry = aCarry + RotL64(aWandererB, 57U);
            aCarry = aCarry + RotL64(aIngress, 47U);
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

void TwistExpander_Greezy_Arx::Twist_A(TwistWorkSpace *pWorkSpace,
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
    [[maybe_unused]] std::uint8_t *aFireLaneA = pWorkSpace->mFireLaneA;
    [[maybe_unused]] std::uint8_t *aFireLaneB = pWorkSpace->mFireLaneB;
    [[maybe_unused]] std::uint8_t *aFireLaneC = pWorkSpace->mFireLaneC;
    [[maybe_unused]] std::uint8_t *aFireLaneD = pWorkSpace->mFireLaneD;
    [[maybe_unused]] std::uint8_t *aKeyRowReadA = &(pWorkSpace->mKeyBoxA[H_KEY - 1][0]);
    [[maybe_unused]] std::uint8_t *aKeyRowReadB = &(pWorkSpace->mKeyBoxB[H_KEY - 1][0]);
    [[maybe_unused]] std::uint64_t *aPhaseAOrbiterAssignSaltA = pWorkSpace->mDomainBundle.mPhaseASalts.mOrbiterAssign.mSaltA;
    [[maybe_unused]] std::uint64_t *aPhaseAOrbiterAssignSaltB = pWorkSpace->mDomainBundle.mPhaseASalts.mOrbiterAssign.mSaltB;
    [[maybe_unused]] std::uint64_t *aPhaseAOrbiterAssignSaltD = pWorkSpace->mDomainBundle.mPhaseASalts.mOrbiterAssign.mSaltD;
    [[maybe_unused]] std::uint64_t *aPhaseAOrbiterAssignSaltF = pWorkSpace->mDomainBundle.mPhaseASalts.mOrbiterAssign.mSaltF;
    [[maybe_unused]] std::uint64_t *aPhaseAOrbiterUpdateSaltA = pWorkSpace->mDomainBundle.mPhaseASalts.mOrbiterUpdate.mSaltA;
    [[maybe_unused]] std::uint64_t *aPhaseAOrbiterUpdateSaltB = pWorkSpace->mDomainBundle.mPhaseASalts.mOrbiterUpdate.mSaltB;
    [[maybe_unused]] std::uint64_t *aPhaseAOrbiterUpdateSaltC = pWorkSpace->mDomainBundle.mPhaseASalts.mOrbiterUpdate.mSaltC;
    [[maybe_unused]] std::uint64_t *aPhaseAOrbiterUpdateSaltD = pWorkSpace->mDomainBundle.mPhaseASalts.mOrbiterUpdate.mSaltD;
    [[maybe_unused]] std::uint64_t *aPhaseAOrbiterUpdateSaltE = pWorkSpace->mDomainBundle.mPhaseASalts.mOrbiterUpdate.mSaltE;
    [[maybe_unused]] std::uint64_t *aPhaseAOrbiterUpdateSaltF = pWorkSpace->mDomainBundle.mPhaseASalts.mOrbiterUpdate.mSaltF;
    [[maybe_unused]] std::uint64_t *aPhaseAWandererUpdateSaltA = pWorkSpace->mDomainBundle.mPhaseASalts.mWandererUpdate.mSaltA;
    [[maybe_unused]] std::uint64_t *aPhaseAWandererUpdateSaltC = pWorkSpace->mDomainBundle.mPhaseASalts.mWandererUpdate.mSaltC;
    [[maybe_unused]] std::uint64_t *aPhaseAWandererUpdateSaltD = pWorkSpace->mDomainBundle.mPhaseASalts.mWandererUpdate.mSaltD;
    [[maybe_unused]] std::uint64_t *aPhaseAWandererUpdateSaltF = pWorkSpace->mDomainBundle.mPhaseASalts.mWandererUpdate.mSaltF;
    [[maybe_unused]] std::uint64_t *aPhaseBOrbiterAssignSaltA = pWorkSpace->mDomainBundle.mPhaseBSalts.mOrbiterAssign.mSaltA;
    [[maybe_unused]] std::uint64_t *aPhaseBOrbiterAssignSaltC = pWorkSpace->mDomainBundle.mPhaseBSalts.mOrbiterAssign.mSaltC;
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
    [[maybe_unused]] std::uint64_t *aPhaseCOrbiterAssignSaltA = pWorkSpace->mDomainBundle.mPhaseCSalts.mOrbiterAssign.mSaltA;
    [[maybe_unused]] std::uint64_t *aPhaseCOrbiterAssignSaltB = pWorkSpace->mDomainBundle.mPhaseCSalts.mOrbiterAssign.mSaltB;
    [[maybe_unused]] std::uint64_t *aPhaseCOrbiterAssignSaltC = pWorkSpace->mDomainBundle.mPhaseCSalts.mOrbiterAssign.mSaltC;
    [[maybe_unused]] std::uint64_t *aPhaseCOrbiterAssignSaltD = pWorkSpace->mDomainBundle.mPhaseCSalts.mOrbiterAssign.mSaltD;
    [[maybe_unused]] std::uint64_t *aPhaseCOrbiterAssignSaltF = pWorkSpace->mDomainBundle.mPhaseCSalts.mOrbiterAssign.mSaltF;
    [[maybe_unused]] std::uint64_t *aPhaseCOrbiterUpdateSaltA = pWorkSpace->mDomainBundle.mPhaseCSalts.mOrbiterUpdate.mSaltA;
    [[maybe_unused]] std::uint64_t *aPhaseCOrbiterUpdateSaltB = pWorkSpace->mDomainBundle.mPhaseCSalts.mOrbiterUpdate.mSaltB;
    [[maybe_unused]] std::uint64_t *aPhaseCOrbiterUpdateSaltC = pWorkSpace->mDomainBundle.mPhaseCSalts.mOrbiterUpdate.mSaltC;
    [[maybe_unused]] std::uint64_t *aPhaseCOrbiterUpdateSaltD = pWorkSpace->mDomainBundle.mPhaseCSalts.mOrbiterUpdate.mSaltD;
    [[maybe_unused]] std::uint64_t *aPhaseCOrbiterUpdateSaltE = pWorkSpace->mDomainBundle.mPhaseCSalts.mOrbiterUpdate.mSaltE;
    [[maybe_unused]] std::uint64_t *aPhaseCOrbiterUpdateSaltF = pWorkSpace->mDomainBundle.mPhaseCSalts.mOrbiterUpdate.mSaltF;
    [[maybe_unused]] std::uint64_t *aPhaseCWandererUpdateSaltC = pWorkSpace->mDomainBundle.mPhaseCSalts.mWandererUpdate.mSaltC;
    [[maybe_unused]] std::uint64_t *aPhaseCWandererUpdateSaltD = pWorkSpace->mDomainBundle.mPhaseCSalts.mWandererUpdate.mSaltD;
    [[maybe_unused]] std::uint64_t *aPhaseCWandererUpdateSaltE = pWorkSpace->mDomainBundle.mPhaseCSalts.mWandererUpdate.mSaltE;
    [[maybe_unused]] std::uint64_t *aPhaseCWandererUpdateSaltF = pWorkSpace->mDomainBundle.mPhaseCSalts.mWandererUpdate.mSaltF;
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
    [[maybe_unused]] std::uint64_t *aPhaseDWandererUpdateSaltD = pWorkSpace->mDomainBundle.mPhaseDSalts.mWandererUpdate.mSaltD;
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
        // read from: aKeyRowReadA, aKeyRowReadB, mSource, aFireLaneA, aFireLaneB, aFireLaneC, aFireLaneD, aWorkLaneA, aWorkLaneB, aWorkLaneC, aWorkLaneD, aExpandLaneA, aExpandLaneB, aExpandLaneC
        // write to: aFireLaneA, aFireLaneB, aFireLaneC, aFireLaneD, aWorkLaneA, aWorkLaneB, aWorkLaneC, aWorkLaneD, aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD
    
        // twist_loop_a loop 1
        // ingress from: aKeyRowReadA, aKeyRowReadB
        // ingress directions: aKeyRowReadA forward forced, aKeyRowReadB forward/backward random
        // cross from: aKeyRowReadA, mSource
        // cross directions: aKeyRowReadA backward forced, mSource backward/forward random
        // write to: aFireLaneA
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = RotL64(aKeyRowReadA[((aIndex + 1229U)) & W_KEY1], 23U) ^ RotL64(aKeyRowReadB[(((2047U - aIndex) + 2220U)) & W_KEY1], 14U);
            aIngress = TwistMix64::DiffuseA(aIngress);
            //
            aCross = RotL64(aKeyRowReadA[(((2047U - aIndex) + 2680U)) & W_KEY1], 4U) ^ RotL64(mSource[((S_BLOCK1 - aIndex + 435U)) & S_BLOCK1], 53U);
            aCross = TwistMix64::DiffuseC(aCross);
            //
            aScatter = (RotL64(aPrevious, 43U) + RotL64(aCarry, 11U)) ^ (RotL64(aIngress, 60U) ^ RotL64(aCross, 29U));
            aScatter = TwistMix64::DiffuseB(aScatter);
            //
            aOrbiterD = (aWandererD + RotL64(aPrevious, 39U)) + 13204735390996728477U;
            aOrbiterJ = ((aWandererG + RotL64(aCross, 13U)) + RotL64(aCarry, 3U)) + 851171359595647173U;
            aOrbiterB = ((aWandererE + RotL64(aScatter, 60U)) + RotL64(aCarry, 19U)) + 16745304202825290723U;
            aOrbiterA = (aWandererA + RotL64(aIngress, 43U)) + 562392736584913979U;
            aOrbiterC = (aWandererI + RotL64(aScatter, 53U)) + 3244267012529053918U;
            aOrbiterG = ((aWandererH + RotL64(aIngress, 19U)) + 17282536111067869133U) + aPhaseAOrbiterAssignSaltF[((aIndex + 19U)) & S_SALT1];
            aOrbiterE = (((aWandererC + RotL64(aPrevious, 34U)) + RotL64(aCarry, 39U)) + 14851130066471729068U) + aPhaseAOrbiterAssignSaltA[(((31U - aIndex) + 23U)) & S_SALT1];
            aOrbiterI = (aWandererJ + RotL64(aCross, 5U)) + 5256130407952363129U;
            aOrbiterF = (aWandererF + RotL64(aScatter, 23U)) + 2904742485828362001U;
            //
            aOrbiterD = (aOrbiterD + aOrbiterJ) + 3723346325449225387U;
            aOrbiterB = (aOrbiterB ^ aOrbiterD) ^ 5344621093694027341U;
            aOrbiterB = RotL64((aOrbiterB * 9044881458629673499U), 5U);
            //
            aOrbiterA = (aOrbiterA + aOrbiterB) + 12919263300833603026U;
            aOrbiterC = (aOrbiterC ^ aOrbiterA) ^ 17989801264160996071U;
            aOrbiterC = RotL64((aOrbiterC * 15468293047311883751U), 43U);
            //
            aOrbiterC = (aOrbiterC + aOrbiterG) + 5022175042377172157U;
            aOrbiterJ = (aOrbiterJ ^ aOrbiterC) ^ 16684822380107847758U;
            aOrbiterJ = RotL64((aOrbiterJ * 2834049270263837537U), 39U);
            //
            aOrbiterJ = (aOrbiterJ + aOrbiterE) + 2740326510600876682U;
            aOrbiterI = ((aOrbiterI ^ aOrbiterJ) ^ 13981423865219318820U) ^ aPhaseAOrbiterUpdateSaltD[(((31U - aIndex) + 7U)) & S_SALT1];
            aOrbiterI = RotL64((aOrbiterI * 14593082145080056441U), 27U);
            //
            aOrbiterF = (aOrbiterF + aOrbiterC) + 231945878229848395U;
            aOrbiterD = ((aOrbiterD ^ aOrbiterF) ^ 14139797734944312580U) ^ aPhaseAOrbiterUpdateSaltE[((aIndex + 5U)) & S_SALT1];
            aOrbiterD = RotL64((aOrbiterD * 6492256080432266407U), 19U);
            //
            aOrbiterI = (aOrbiterI + aOrbiterA) + 16704102101387552373U;
            aOrbiterF = (aOrbiterF ^ aOrbiterI) ^ 8506734780526852552U;
            aOrbiterF = RotL64((aOrbiterF * 4684566118627414659U), 35U);
            //
            aOrbiterE = (aOrbiterE + aOrbiterD) + 2774630043988894695U;
            aOrbiterA = (aOrbiterA ^ aOrbiterE) ^ 12490034334296488127U;
            aOrbiterA = RotL64((aOrbiterA * 16765455396278233145U), 13U);
            //
            aOrbiterB = (aOrbiterB + aOrbiterI) + 545238171291436006U;
            aOrbiterG = (aOrbiterG ^ aOrbiterB) ^ 1023872898002379590U;
            aOrbiterG = RotL64((aOrbiterG * 8626333831510136515U), 57U);
            //
            aOrbiterG = ((aOrbiterG + aOrbiterF) + 5065187021047872560U) + aPhaseAOrbiterUpdateSaltF[(((31U - aIndex) + 11U)) & S_SALT1];
            aOrbiterE = ((aOrbiterE ^ aOrbiterG) ^ 10391809965648089863U) ^ aPhaseAOrbiterUpdateSaltC[((aIndex + 26U)) & S_SALT1];
            aOrbiterE = RotL64((aOrbiterE * 10912471108849550469U), 47U);
            //
            aIngress = RotL64(aOrbiterA, 44U) ^ aOrbiterF;
            aIngress = aIngress + (aOrbiterG ^ RotL64(aOrbiterD, 47U));
            aIngress = aIngress + (RotL64(aOrbiterC, 57U) ^ aOrbiterJ);
            aIngress = aIngress + (RotL64(aOrbiterB, 5U) ^ aOrbiterI);
            aIngress = aIngress + RotL64(aOrbiterE, 20U);
            aIngress = TwistMix64::DiffuseC((aIngress + aScatter));
            //
            aWandererE = aWandererE ^ ((RotL64(aScatter, 13U) + RotL64(aOrbiterE, 19U)) + aOrbiterJ);
            aWandererJ = aWandererJ + (((RotL64(aCross, 35U) + RotL64(aOrbiterB, 27U)) + aOrbiterC) + aPhaseAWandererUpdateSaltA[(((31U - aIndex) + 8U)) & S_SALT1]);
            aWandererA = aWandererA ^ ((RotL64(aPrevious, 39U) + aOrbiterG) + RotL64(aOrbiterD, 23U));
            aWandererC = aWandererC + (((RotL64(aIngress, 51U) + RotL64(aOrbiterE, 58U)) + aOrbiterI) + aPhaseAWandererUpdateSaltC[(((31U - aIndex) + 15U)) & S_SALT1]);
            aWandererI = aWandererI ^ ((RotL64(aScatter, 30U) + aOrbiterB) + RotL64(aOrbiterA, 47U));
            aWandererD = aWandererD + (((RotL64(aIngress, 19U) + aOrbiterD) + RotL64(aOrbiterJ, 43U)) + RotL64(aCarry, 29U));
            aWandererH = aWandererH ^ ((RotL64(aPrevious, 23U) + aOrbiterC) + RotL64(aOrbiterF, 37U));
            aWandererG = aWandererG + (((RotL64(aCross, 5U) + aOrbiterF) + RotL64(aOrbiterJ, 4U)) + RotL64(aCarry, 19U));
            aWandererF = aWandererF ^ ((RotL64(aPrevious, 44U) + RotL64(aOrbiterI, 51U)) + aOrbiterF);
            //
            aCarry = aCarry + (aWandererD ^ RotL64(aWandererJ, 57U));
            aCarry = aCarry + (aWandererF ^ RotL64(aWandererI, 29U));
            aCarry = aCarry + (aWandererG ^ RotL64(aWandererC, 37U));
            aCarry = aCarry + (RotL64(aWandererA, 5U) ^ aWandererH);
            aCarry = aCarry + RotL64(aWandererE, 48U);
            aCarry = aCarry + RotL64(aIngress, 51U);
            aCarry = TwistMix64::DiffuseC(aCarry);
            //
            aFireLaneA[aIndex] = aIngress;
        }
    
        // twist_loop_a loop 2
        // ingress from: aFireLaneA, aKeyRowReadA
        // ingress directions: aFireLaneA forward forced, aKeyRowReadA forward/backward random
        // cross from: aKeyRowReadB, mSource
        // cross directions: aKeyRowReadB backward forced, mSource backward/forward random
        // write to: aFireLaneB
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = RotL64(aFireLaneA[((aIndex + 3706U)) & S_BLOCK1], 37U) ^ RotL64(aKeyRowReadA[(((2047U - aIndex) + 5252U)) & W_KEY1], 24U);
            aIngress = TwistMix64::DiffuseB(aIngress);
            //
            aCross = RotL64(aKeyRowReadB[(((2047U - aIndex) + 3151U)) & W_KEY1], 13U) ^ RotL64(mSource[((S_BLOCK1 - aIndex + 3441U)) & S_BLOCK1], 22U);
            aCross = TwistMix64::DiffuseB(aCross);
            //
            aScatter = (RotL64(aCarry, 22U) ^ RotL64(aIngress, 5U)) + (RotL64(aCross, 57U) ^ RotL64(aPrevious, 43U));
            aScatter = TwistMix64::DiffuseA(aScatter);
            //
            aOrbiterF = (aWandererA + RotL64(aScatter, 34U)) + 10881271196314989997U;
            aOrbiterB = (aWandererD + RotL64(aCross, 11U)) + 6406461249988567558U;
            aOrbiterK = (aWandererJ + RotL64(aPrevious, 43U)) + 17255067918280095959U;
            aOrbiterA = ((aWandererH + RotL64(aIngress, 47U)) + 16690850682497718411U) + aPhaseAOrbiterAssignSaltF[(((31U - aIndex) + 12U)) & S_SALT1];
            aOrbiterH = ((aWandererG + RotL64(aPrevious, 28U)) + RotL64(aCarry, 23U)) + 5576201059361086866U;
            aOrbiterE = ((aWandererF + RotL64(aCross, 51U)) + RotL64(aCarry, 57U)) + 11991259685693687554U;
            aOrbiterI = ((aWandererE + RotL64(aIngress, 19U)) + RotL64(aCarry, 13U)) + 14652535244217836909U;
            aOrbiterC = ((aWandererC + RotL64(aScatter, 39U)) + 1701789037170782122U) + aPhaseAOrbiterAssignSaltA[((aIndex + 14U)) & S_SALT1];
            aOrbiterG = (aWandererB + RotL64(aIngress, 57U)) + 953429054903473833U;
            //
            aOrbiterF = (aOrbiterF + aOrbiterB) + 12064513610469714211U;
            aOrbiterK = (aOrbiterK ^ aOrbiterF) ^ 7993881398822002424U;
            aOrbiterK = RotL64((aOrbiterK * 11572884842788918377U), 5U);
            //
            aOrbiterB = (aOrbiterB + aOrbiterA) + 14421313768013320050U;
            aOrbiterH = (aOrbiterH ^ aOrbiterB) ^ 11112386845630998889U;
            aOrbiterH = RotL64((aOrbiterH * 11771526352030371669U), 11U);
            //
            aOrbiterE = ((aOrbiterE + aOrbiterI) + 17069630896535699015U) + aPhaseAOrbiterUpdateSaltC[((aIndex + 11U)) & S_SALT1];
            aOrbiterF = ((aOrbiterF ^ aOrbiterE) ^ 3308240081138623373U) ^ aPhaseAOrbiterUpdateSaltB[((aIndex + 21U)) & S_SALT1];
            aOrbiterF = RotL64((aOrbiterF * 10449509484417835159U), 43U);
            //
            aOrbiterK = (aOrbiterK + aOrbiterH) + 17615529807112933619U;
            aOrbiterI = ((aOrbiterI ^ aOrbiterK) ^ 11782807146851563541U) ^ aPhaseAOrbiterUpdateSaltE[((aIndex + 3U)) & S_SALT1];
            aOrbiterI = RotL64((aOrbiterI * 12992075832343669221U), 37U);
            //
            aOrbiterH = (aOrbiterH + aOrbiterC) + 14401645829607611983U;
            aOrbiterG = ((aOrbiterG ^ aOrbiterH) ^ 6736397344219993532U) ^ aPhaseAOrbiterUpdateSaltA[((aIndex + 13U)) & S_SALT1];
            aOrbiterG = RotL64((aOrbiterG * 1667287547938175641U), 47U);
            //
            aOrbiterI = (aOrbiterI + aOrbiterG) + 6446974060524700550U;
            aOrbiterB = (aOrbiterB ^ aOrbiterI) ^ 7840991992443308254U;
            aOrbiterB = RotL64((aOrbiterB * 6891023544882740107U), 57U);
            //
            aOrbiterA = (aOrbiterA + aOrbiterF) + 10362169906019794305U;
            aOrbiterC = (aOrbiterC ^ aOrbiterA) ^ 4503700997923168911U;
            aOrbiterC = RotL64((aOrbiterC * 15066164494038852559U), 19U);
            //
            aOrbiterG = (aOrbiterG + aOrbiterE) + 13492041134973259041U;
            aOrbiterA = (aOrbiterA ^ aOrbiterG) ^ 14337899277551397976U;
            aOrbiterA = RotL64((aOrbiterA * 5966740718899290915U), 29U);
            //
            aOrbiterC = (aOrbiterC + aOrbiterK) + 13693100781608180748U;
            aOrbiterE = (aOrbiterE ^ aOrbiterC) ^ 16177545026405910052U;
            aOrbiterE = RotL64((aOrbiterE * 6019231448444020563U), 51U);
            //
            aIngress = RotL64(aOrbiterG, 35U) ^ aOrbiterC;
            aIngress = aIngress + (aOrbiterA ^ RotL64(aOrbiterB, 23U));
            aIngress = aIngress + (aOrbiterE ^ RotL64(aOrbiterH, 38U));
            aIngress = aIngress + (aOrbiterK ^ RotL64(aOrbiterF, 27U));
            aIngress = aIngress + RotL64(aOrbiterI, 11U);
            aIngress = TwistMix64::DiffuseC((aIngress + aScatter));
            //
            aWandererD = aWandererD ^ ((RotL64(aScatter, 39U) + RotL64(aOrbiterF, 30U)) + aOrbiterE);
            aWandererJ = aWandererJ + ((((RotL64(aPrevious, 12U) + aOrbiterA) + RotL64(aOrbiterI, 5U)) + RotL64(aCarry, 21U)) + aPhaseAWandererUpdateSaltA[((aIndex + 24U)) & S_SALT1]);
            aWandererG = aWandererG ^ ((RotL64(aCross, 51U) + aOrbiterC) + RotL64(aOrbiterE, 43U));
            aWandererF = aWandererF + ((RotL64(aIngress, 29U) + RotL64(aOrbiterC, 39U)) + aOrbiterF);
            aWandererE = aWandererE ^ ((RotL64(aCross, 43U) + RotL64(aOrbiterA, 18U)) + aOrbiterF);
            aWandererA = aWandererA + (((RotL64(aScatter, 19U) + aOrbiterH) + RotL64(aOrbiterC, 53U)) + RotL64(aCarry, 47U));
            aWandererC = aWandererC ^ ((RotL64(aIngress, 35U) + aOrbiterK) + RotL64(aOrbiterG, 57U));
            aWandererH = aWandererH + (((RotL64(aPrevious, 5U) + aOrbiterK) + RotL64(aOrbiterH, 11U)) + aPhaseAWandererUpdateSaltF[(((31U - aIndex) + 29U)) & S_SALT1]);
            aWandererB = aWandererB ^ ((RotL64(aScatter, 58U) + RotL64(aOrbiterB, 35U)) + aOrbiterC);
            //
            aCarry = aCarry + (aWandererB ^ RotL64(aWandererF, 47U));
            aCarry = aCarry + (aWandererD ^ RotL64(aWandererJ, 39U));
            aCarry = aCarry + (aWandererA ^ RotL64(aWandererE, 29U));
            aCarry = aCarry + (RotL64(aWandererH, 11U) ^ aWandererC);
            aCarry = aCarry + RotL64(aWandererG, 5U);
            aCarry = aCarry + RotL64(aIngress, 56U);
            aCarry = TwistMix64::DiffuseB(aCarry);
            //
            aFireLaneB[S_BLOCK1 - aIndex] = aIngress;
        }
    
        // twist_loop_a loop 3
        // ingress from: aFireLaneB, aKeyRowReadB
        // ingress directions: aFireLaneB forward forced, aKeyRowReadB forward/backward random
        // cross from: aKeyRowReadA, mSource, aFireLaneA
        // cross directions: aKeyRowReadA backward forced, mSource backward forced, aFireLaneA backward/forward random
        // write to: aFireLaneC
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = RotL64(aFireLaneB[((aIndex + 7431U)) & S_BLOCK1], 19U) ^ RotL64(aKeyRowReadB[(((2047U - aIndex) + 7525U)) & W_KEY1], 10U);
            aIngress = TwistMix64::DiffuseA(aIngress);
            //
            aCross = (RotL64(aKeyRowReadA[(((2047U - aIndex) + 6979U)) & W_KEY1], 5U) ^ RotL64(mSource[((S_BLOCK1 - aIndex + 7814U)) & S_BLOCK1], 29U));
            aCross ^= RotL64(aFireLaneA[((S_BLOCK1 - aIndex + 6970U)) & S_BLOCK1], 20U);
            aCross = TwistMix64::DiffuseA(aCross);
            //
            aScatter = (RotL64(aPrevious, 53U) + RotL64(aCarry, 13U)) ^ (RotL64(aCross, 26U) + RotL64(aIngress, 41U));
            aScatter = TwistMix64::DiffuseC(aScatter);
            //
            aOrbiterF = ((aWandererI + RotL64(aIngress, 52U)) + RotL64(aCarry, 13U)) + 6068543441070417854U;
            aOrbiterE = (aWandererF + RotL64(aCross, 23U)) + 2995980468193441856U;
            aOrbiterH = (aWandererC + RotL64(aPrevious, 19U)) + 18020277482171594003U;
            aOrbiterK = ((aWandererK + RotL64(aScatter, 3U)) + RotL64(aCarry, 41U)) + 4293807434721230702U;
            aOrbiterC = (((aWandererD + RotL64(aCross, 27U)) + RotL64(aCarry, 53U)) + 7980599111583893156U) + aPhaseAOrbiterAssignSaltB[((aIndex + 25U)) & S_SALT1];
            aOrbiterD = (aWandererB + RotL64(aScatter, 12U)) + 8593141111851052016U;
            aOrbiterA = (aWandererJ + RotL64(aPrevious, 47U)) + 5903487523900084325U;
            aOrbiterI = (aWandererE + RotL64(aIngress, 43U)) + 15112035513447930209U;
            aOrbiterG = ((aWandererA + RotL64(aPrevious, 37U)) + 9854037263057006439U) + aPhaseAOrbiterAssignSaltD[((aIndex + 3U)) & S_SALT1];
            //
            aOrbiterF = (aOrbiterF + aOrbiterE) + 16759760289688823193U;
            aOrbiterH = (aOrbiterH ^ aOrbiterF) ^ 12622628933030601390U;
            aOrbiterH = RotL64((aOrbiterH * 2151912984825538321U), 57U);
            //
            aOrbiterK = (aOrbiterK + aOrbiterC) + 1264668857268123425U;
            aOrbiterD = ((aOrbiterD ^ aOrbiterK) ^ 16302812053619101593U) ^ aPhaseAOrbiterUpdateSaltE[((aIndex + 15U)) & S_SALT1];
            aOrbiterD = RotL64((aOrbiterD * 18291400055836111547U), 13U);
            //
            aOrbiterC = (aOrbiterC + aOrbiterF) + 16087995784896123610U;
            aOrbiterA = ((aOrbiterA ^ aOrbiterC) ^ 7970269262800468363U) ^ aPhaseAOrbiterUpdateSaltC[(((31U - aIndex) + 14U)) & S_SALT1];
            aOrbiterA = RotL64((aOrbiterA * 14924752223305807461U), 53U);
            //
            aOrbiterI = (aOrbiterI + aOrbiterK) + 5331477046030959632U;
            aOrbiterE = ((aOrbiterE ^ aOrbiterI) ^ 16534913204255550893U) ^ aPhaseAOrbiterUpdateSaltD[((aIndex + 7U)) & S_SALT1];
            aOrbiterE = RotL64((aOrbiterE * 1013433634373673565U), 43U);
            //
            aOrbiterG = (aOrbiterG + aOrbiterI) + 11042821902537871209U;
            aOrbiterF = (aOrbiterF ^ aOrbiterG) ^ 8069677512345031660U;
            aOrbiterF = RotL64((aOrbiterF * 13622218526054132397U), 37U);
            //
            aOrbiterA = (aOrbiterA + aOrbiterH) + 5737130058129936372U;
            aOrbiterK = (aOrbiterK ^ aOrbiterA) ^ 1076627182956662997U;
            aOrbiterK = RotL64((aOrbiterK * 14342191224014199929U), 21U);
            //
            aOrbiterH = (aOrbiterH + aOrbiterG) + 13911061091801078190U;
            aOrbiterC = (aOrbiterC ^ aOrbiterH) ^ 15397603151098990373U;
            aOrbiterC = RotL64((aOrbiterC * 1802890451633592245U), 5U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterA) + 15137326716738637972U;
            aOrbiterI = (aOrbiterI ^ aOrbiterD) ^ 11248737008959896786U;
            aOrbiterI = RotL64((aOrbiterI * 90789374131547005U), 47U);
            //
            aOrbiterE = (aOrbiterE + aOrbiterD) + 1847847987633923657U;
            aOrbiterG = ((aOrbiterG ^ aOrbiterE) ^ 10560748778679145431U) ^ aPhaseAOrbiterUpdateSaltB[((aIndex + 9U)) & S_SALT1];
            aOrbiterG = RotL64((aOrbiterG * 2919333327817231099U), 29U);
            //
            aIngress = aOrbiterI ^ RotL64(aOrbiterF, 34U);
            aIngress = aIngress + (aOrbiterH ^ RotL64(aOrbiterA, 19U));
            aIngress = aIngress + (RotL64(aOrbiterE, 23U) ^ aOrbiterC);
            aIngress = aIngress + (RotL64(aOrbiterD, 43U) ^ aOrbiterG);
            aIngress = aIngress + RotL64(aOrbiterK, 27U);
            aIngress = TwistMix64::DiffuseA((aIngress + aScatter));
            //
            aWandererD = aWandererD + ((((RotL64(aIngress, 47U) + aOrbiterC) + RotL64(aOrbiterF, 60U)) + RotL64(aCarry, 11U)) + aPhaseAWandererUpdateSaltD[(((31U - aIndex) + 28U)) & S_SALT1]);
            aWandererI = aWandererI ^ ((RotL64(aCross, 56U) + aOrbiterD) + RotL64(aOrbiterE, 53U));
            aWandererA = aWandererA + (((RotL64(aScatter, 23U) + RotL64(aOrbiterE, 13U)) + aOrbiterF) + RotL64(aCarry, 23U));
            aWandererC = aWandererC ^ ((RotL64(aPrevious, 19U) + RotL64(aOrbiterC, 3U)) + aOrbiterA);
            aWandererB = aWandererB + ((RotL64(aIngress, 41U) + RotL64(aOrbiterK, 48U)) + aOrbiterH);
            aWandererK = aWandererK ^ (((RotL64(aScatter, 3U) + aOrbiterG) + RotL64(aOrbiterF, 19U)) + aPhaseAWandererUpdateSaltA[(((31U - aIndex) + 8U)) & S_SALT1]);
            aWandererJ = aWandererJ + ((RotL64(aPrevious, 29U) + aOrbiterI) + RotL64(aOrbiterF, 39U));
            aWandererE = aWandererE ^ ((RotL64(aCross, 60U) + RotL64(aOrbiterD, 43U)) + aOrbiterK);
            aWandererF = aWandererF + ((RotL64(aIngress, 51U) + aOrbiterE) + RotL64(aOrbiterK, 29U));
            //
            aCarry = aCarry + (RotL64(aWandererC, 35U) ^ aWandererD);
            aCarry = aCarry + (RotL64(aWandererK, 43U) ^ aWandererA);
            aCarry = aCarry + (aWandererF ^ RotL64(aWandererE, 10U));
            aCarry = aCarry + (RotL64(aWandererJ, 23U) ^ aWandererB);
            aCarry = aCarry + RotL64(aWandererI, 19U);
            aCarry = aCarry + RotL64(aIngress, 13U);
            aCarry = TwistMix64::DiffuseC(aCarry);
            //
            aFireLaneC[aIndex] = aIngress;
        }
    
        // twist_loop_a loop 4
        // ingress from: aFireLaneC, aKeyRowReadB, mSource, aFireLaneA
        // ingress directions: aFireLaneC forward forced, aKeyRowReadB forward forced, mSource forward forced, aFireLaneA forward/backward random
        // cross from: aKeyRowReadA, aFireLaneB
        // cross directions: aKeyRowReadA backward forced, aFireLaneB backward/forward random
        // write to: aFireLaneD
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aFireLaneC[((aIndex + 8378U)) & S_BLOCK1], 35U) ^ RotL64(aKeyRowReadB[((aIndex + 9867U)) & W_KEY1], 5U));
            aIngress ^= (RotL64(mSource[((aIndex + 10140U)) & S_BLOCK1], 23U) ^ RotL64(aFireLaneA[((S_BLOCK1 - aIndex + 9342U)) & S_BLOCK1], 54U));
            aIngress = TwistMix64::DiffuseB(aIngress);
            //
            aCross = RotL64(aKeyRowReadA[(((2047U - aIndex) + 9876U)) & W_KEY1], 10U) ^ RotL64(aFireLaneB[((S_BLOCK1 - aIndex + 8866U)) & S_BLOCK1], 37U);
            aCross = TwistMix64::DiffuseB(aCross);
            //
            aScatter = (RotL64(aPrevious, 23U) + RotL64(aCross, 6U)) + (RotL64(aIngress, 35U) ^ RotL64(aCarry, 53U));
            aScatter = TwistMix64::DiffuseB(aScatter);
            //
            aOrbiterI = (aWandererF + RotL64(aScatter, 6U)) + 5510690816044082200U;
            aOrbiterC = (aWandererG + RotL64(aCross, 29U)) + 15967820875033940530U;
            aOrbiterF = (aWandererC + RotL64(aIngress, 57U)) + 539348720848176221U;
            aOrbiterJ = (aWandererB + RotL64(aPrevious, 19U)) + 15779318183635560817U;
            aOrbiterE = ((aWandererA + RotL64(aCross, 11U)) + 14511058534424187469U) + aPhaseBOrbiterAssignSaltE[((aIndex + 29U)) & S_SALT1];
            aOrbiterK = (((aWandererH + RotL64(aScatter, 43U)) + RotL64(aCarry, 11U)) + 5811130556873428391U) + aPhaseBOrbiterAssignSaltA[((aIndex + 7U)) & S_SALT1];
            aOrbiterG = (aWandererJ + RotL64(aIngress, 24U)) + 1085928476499444025U;
            aOrbiterD = ((aWandererD + RotL64(aPrevious, 35U)) + RotL64(aCarry, 19U)) + 6973335316600768130U;
            aOrbiterH = ((aWandererI + RotL64(aCross, 39U)) + RotL64(aCarry, 53U)) + 10747243745475009744U;
            //
            aOrbiterI = (aOrbiterI + aOrbiterC) + 1072260008981349754U;
            aOrbiterF = (aOrbiterF ^ aOrbiterI) ^ 2018772405352495753U;
            aOrbiterF = RotL64((aOrbiterF * 10840562112080574241U), 39U);
            //
            aOrbiterJ = ((aOrbiterJ + aOrbiterE) + 1092091597048996547U) + aPhaseBOrbiterUpdateSaltB[(((31U - aIndex) + 23U)) & S_SALT1];
            aOrbiterC = (aOrbiterC ^ aOrbiterJ) ^ 15103140149542167197U;
            aOrbiterC = RotL64((aOrbiterC * 621856991658027989U), 43U);
            //
            aOrbiterF = (aOrbiterF + aOrbiterK) + 13194619321108681542U;
            aOrbiterG = (aOrbiterG ^ aOrbiterF) ^ 16749188603268621850U;
            aOrbiterG = RotL64((aOrbiterG * 9575408950550922039U), 35U);
            //
            aOrbiterE = (aOrbiterE + aOrbiterI) + 7427959503086895166U;
            aOrbiterD = (aOrbiterD ^ aOrbiterE) ^ 9895804051379551393U;
            aOrbiterD = RotL64((aOrbiterD * 2701997336201570715U), 57U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterF) + 4526020800679774259U;
            aOrbiterH = (aOrbiterH ^ aOrbiterD) ^ 4484850928870048176U;
            aOrbiterH = RotL64((aOrbiterH * 17556987520625677313U), 51U);
            //
            aOrbiterG = ((aOrbiterG + aOrbiterJ) + 1837404844299040155U) + aPhaseBOrbiterUpdateSaltC[(((31U - aIndex) + 16U)) & S_SALT1];
            aOrbiterI = ((aOrbiterI ^ aOrbiterG) ^ 15213208978489570694U) ^ aPhaseBOrbiterUpdateSaltD[((aIndex + 15U)) & S_SALT1];
            aOrbiterI = RotL64((aOrbiterI * 7062740584650274133U), 47U);
            //
            aOrbiterK = (aOrbiterK + aOrbiterH) + 9615231781751396800U;
            aOrbiterJ = (aOrbiterJ ^ aOrbiterK) ^ 15872192167825648096U;
            aOrbiterJ = RotL64((aOrbiterJ * 2900526493682580729U), 23U);
            //
            aOrbiterH = (aOrbiterH + aOrbiterG) + 12530672039655918903U;
            aOrbiterE = ((aOrbiterE ^ aOrbiterH) ^ 10617836782870315804U) ^ aPhaseBOrbiterUpdateSaltE[(((31U - aIndex) + 25U)) & S_SALT1];
            aOrbiterE = RotL64((aOrbiterE * 9716778004909794973U), 29U);
            //
            aOrbiterC = (aOrbiterC + aOrbiterD) + 550750725406860977U;
            aOrbiterK = (aOrbiterK ^ aOrbiterC) ^ 3498554352021622907U;
            aOrbiterK = RotL64((aOrbiterK * 9846933294851238495U), 19U);
            //
            aIngress = RotL64(aOrbiterH, 13U) ^ aOrbiterJ;
            aIngress = aIngress + (RotL64(aOrbiterG, 54U) ^ aOrbiterK);
            aIngress = aIngress + (aOrbiterC ^ RotL64(aOrbiterE, 37U));
            aIngress = aIngress + (aOrbiterF ^ RotL64(aOrbiterD, 47U));
            aIngress = aIngress + RotL64(aOrbiterI, 51U);
            aIngress = TwistMix64::DiffuseB((aIngress + aScatter));
            //
            aWandererC = aWandererC + (((RotL64(aIngress, 47U) + RotL64(aOrbiterC, 13U)) + aOrbiterF) + RotL64(aCarry, 35U));
            aWandererA = aWandererA ^ (((RotL64(aCross, 34U) + aOrbiterE) + RotL64(aOrbiterC, 5U)) + aPhaseBWandererUpdateSaltC[((aIndex + 3U)) & S_SALT1]);
            aWandererI = aWandererI + ((RotL64(aScatter, 27U) + RotL64(aOrbiterK, 34U)) + aOrbiterD);
            aWandererF = aWandererF ^ (((RotL64(aPrevious, 19U) + aOrbiterH) + RotL64(aOrbiterJ, 57U)) + aPhaseBWandererUpdateSaltD[((aIndex + 8U)) & S_SALT1]);
            aWandererG = aWandererG + ((RotL64(aScatter, 5U) + RotL64(aOrbiterC, 39U)) + aOrbiterK);
            aWandererH = aWandererH ^ ((RotL64(aIngress, 58U) + RotL64(aOrbiterC, 51U)) + aOrbiterI);
            aWandererD = aWandererD + (((RotL64(aCross, 43U) + RotL64(aOrbiterG, 28U)) + aOrbiterJ) + RotL64(aCarry, 11U));
            aWandererB = aWandererB ^ ((RotL64(aPrevious, 39U) + aOrbiterG) + RotL64(aOrbiterE, 43U));
            aWandererJ = aWandererJ + ((RotL64(aCross, 11U) + RotL64(aOrbiterJ, 21U)) + aOrbiterC);
            //
            aCarry = aCarry + (aWandererG ^ RotL64(aWandererH, 19U));
            aCarry = aCarry + (RotL64(aWandererA, 43U) ^ aWandererJ);
            aCarry = aCarry + (aWandererI ^ RotL64(aWandererF, 27U));
            aCarry = aCarry + (RotL64(aWandererB, 50U) ^ aWandererC);
            aCarry = aCarry + RotL64(aWandererD, 37U);
            aCarry = aCarry + RotL64(aIngress, 3U);
            aCarry = TwistMix64::DiffuseB(aCarry);
            //
            aFireLaneD[S_BLOCK1 - aIndex] = aIngress;
        }
    
        // twist_loop_a loop 5
        // ingress from: aFireLaneD, aKeyRowReadA, aKeyRowReadB, mSource, aFireLaneB
        // ingress directions: aFireLaneD forward forced, aKeyRowReadA forward forced, aKeyRowReadB forward forced, mSource forward forced, aFireLaneB forward/backward random
        // cross from: aFireLaneA, aFireLaneC
        // cross directions: aFireLaneA backward forced, aFireLaneC backward/forward random
        // write to: aWorkLaneA
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aFireLaneD[((aIndex + 12354U)) & S_BLOCK1], 47U) ^ RotL64(aKeyRowReadA[((aIndex + 12362U)) & W_KEY1], 29U));
            aIngress ^= (RotL64(aKeyRowReadB[((aIndex + 13563U)) & W_KEY1], 57U) ^ RotL64(mSource[((aIndex + 11095U)) & S_BLOCK1], 14U));
            aIngress ^= RotL64(aFireLaneB[((aIndex + 11181U)) & S_BLOCK1], 5U);
            aIngress = TwistMix64::DiffuseA(aIngress);
            //
            aCross = RotL64(aFireLaneA[((S_BLOCK1 - aIndex + 12336U)) & S_BLOCK1], 56U) ^ RotL64(aFireLaneC[((aIndex + 13054U)) & S_BLOCK1], 21U);
            aCross = TwistMix64::DiffuseC(aCross);
            //
            aScatter = (RotL64(aCross, 43U) ^ RotL64(aPrevious, 56U)) + (RotL64(aCarry, 29U) ^ RotL64(aIngress, 11U));
            aScatter = TwistMix64::DiffuseA(aScatter);
            //
            aOrbiterB = (aWandererK + RotL64(aScatter, 35U)) + 5088525177670191619U;
            aOrbiterA = (((aWandererD + RotL64(aPrevious, 18U)) + RotL64(aCarry, 53U)) + 9966456257813932112U) + aPhaseBOrbiterAssignSaltC[((aIndex + 28U)) & S_SALT1];
            aOrbiterD = (aWandererJ + RotL64(aIngress, 57U)) + 7707646574027146307U;
            aOrbiterI = ((aWandererC + RotL64(aCross, 5U)) + RotL64(aCarry, 37U)) + 75480203757681173U;
            aOrbiterE = (aWandererE + RotL64(aPrevious, 53U)) + 384659134071835163U;
            aOrbiterK = (((aWandererF + RotL64(aIngress, 11U)) + RotL64(aCarry, 3U)) + 3158769775373307778U) + aPhaseBOrbiterAssignSaltF[((aIndex + 8U)) & S_SALT1];
            aOrbiterC = (aWandererA + RotL64(aScatter, 48U)) + 17360830943513941272U;
            aOrbiterF = (aWandererB + RotL64(aCross, 41U)) + 5317278822721604586U;
            aOrbiterH = (aWandererG + RotL64(aIngress, 23U)) + 1371427105215954781U;
            //
            aOrbiterB = (aOrbiterB + aOrbiterA) + 3162710551223553423U;
            aOrbiterD = (aOrbiterD ^ aOrbiterB) ^ 5332921933853550756U;
            aOrbiterD = RotL64((aOrbiterD * 11709546145149357887U), 57U);
            //
            aOrbiterI = (aOrbiterI + aOrbiterD) + 10572462410297815854U;
            aOrbiterE = (aOrbiterE ^ aOrbiterI) ^ 10234389605554817892U;
            aOrbiterE = RotL64((aOrbiterE * 2130374833440291193U), 29U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterK) + 13421365517991380605U;
            aOrbiterC = (aOrbiterC ^ aOrbiterD) ^ 10186643614984034083U;
            aOrbiterC = RotL64((aOrbiterC * 8554471709467808453U), 23U);
            //
            aOrbiterA = (aOrbiterA + aOrbiterF) + 4742438973260817120U;
            aOrbiterK = (aOrbiterK ^ aOrbiterA) ^ 6081590345899008846U;
            aOrbiterK = RotL64((aOrbiterK * 7069396301823124931U), 13U);
            //
            aOrbiterF = ((aOrbiterF + aOrbiterB) + 15360092808493795340U) + aPhaseBOrbiterUpdateSaltD[(((31U - aIndex) + 7U)) & S_SALT1];
            aOrbiterI = (aOrbiterI ^ aOrbiterF) ^ 12186413069553132646U;
            aOrbiterI = RotL64((aOrbiterI * 3815981440611914267U), 47U);
            //
            aOrbiterK = ((aOrbiterK + aOrbiterI) + 16756221656224451552U) + aPhaseBOrbiterUpdateSaltA[((aIndex + 19U)) & S_SALT1];
            aOrbiterH = (aOrbiterH ^ aOrbiterK) ^ 12232880965861373143U;
            aOrbiterH = RotL64((aOrbiterH * 14196910735715726471U), 51U);
            //
            aOrbiterE = (aOrbiterE + aOrbiterC) + 10090954323470840557U;
            aOrbiterA = ((aOrbiterA ^ aOrbiterE) ^ 15615770271463853537U) ^ aPhaseBOrbiterUpdateSaltC[((aIndex + 6U)) & S_SALT1];
            aOrbiterA = RotL64((aOrbiterA * 13544181592829027283U), 3U);
            //
            aOrbiterH = (aOrbiterH + aOrbiterE) + 556029032505658411U;
            aOrbiterB = ((aOrbiterB ^ aOrbiterH) ^ 13311879111583579039U) ^ aPhaseBOrbiterUpdateSaltF[(((31U - aIndex) + 23U)) & S_SALT1];
            aOrbiterB = RotL64((aOrbiterB * 3924744868168749003U), 41U);
            //
            aOrbiterC = (aOrbiterC + aOrbiterH) + 8646360871497847336U;
            aOrbiterF = (aOrbiterF ^ aOrbiterC) ^ 2064833941982069154U;
            aOrbiterF = RotL64((aOrbiterF * 10016546852137913163U), 19U);
            //
            aIngress = RotL64(aOrbiterD, 47U) ^ aOrbiterC;
            aIngress = aIngress + (RotL64(aOrbiterK, 19U) ^ aOrbiterB);
            aIngress = aIngress + (RotL64(aOrbiterH, 58U) ^ aOrbiterF);
            aIngress = aIngress + (RotL64(aOrbiterI, 23U) ^ aOrbiterA);
            aIngress = aIngress + RotL64(aOrbiterE, 11U);
            aIngress = TwistMix64::DiffuseA((aIngress + aScatter));
            //
            aWandererF = aWandererF ^ ((RotL64(aPrevious, 56U) + RotL64(aOrbiterE, 58U)) + aOrbiterH);
            aWandererK = aWandererK + (((RotL64(aCross, 19U) + aOrbiterD) + RotL64(aOrbiterI, 29U)) + RotL64(aCarry, 39U));
            aWandererD = aWandererD ^ (((RotL64(aScatter, 3U) + aOrbiterC) + RotL64(aOrbiterB, 51U)) + aPhaseBWandererUpdateSaltA[((aIndex + 25U)) & S_SALT1]);
            aWandererC = aWandererC + ((RotL64(aIngress, 27U) + aOrbiterI) + RotL64(aOrbiterB, 13U));
            aWandererJ = aWandererJ ^ ((RotL64(aCross, 13U) + RotL64(aOrbiterD, 35U)) + aOrbiterH);
            aWandererG = aWandererG + (((RotL64(aIngress, 35U) + aOrbiterH) + RotL64(aOrbiterB, 23U)) + RotL64(aCarry, 29U));
            aWandererE = aWandererE ^ ((RotL64(aPrevious, 52U) + RotL64(aOrbiterB, 5U)) + aOrbiterF);
            aWandererB = aWandererB + (((RotL64(aScatter, 39U) + RotL64(aOrbiterA, 19U)) + aOrbiterK) + aPhaseBWandererUpdateSaltB[(((31U - aIndex) + 17U)) & S_SALT1]);
            aWandererA = aWandererA ^ ((RotL64(aIngress, 43U) + aOrbiterA) + RotL64(aOrbiterD, 42U));
            //
            aCarry = aCarry + (aWandererJ ^ RotL64(aWandererG, 50U));
            aCarry = aCarry + (aWandererB ^ RotL64(aWandererE, 53U));
            aCarry = aCarry + (RotL64(aWandererD, 23U) ^ aWandererF);
            aCarry = aCarry + (aWandererC ^ RotL64(aWandererA, 41U));
            aCarry = aCarry + RotL64(aWandererK, 13U);
            aCarry = aCarry + RotL64(aIngress, 47U);
            aCarry = TwistMix64::DiffuseC(aCarry);
            //
            aWorkLaneA[aIndex] = aIngress;
        }
    
        // twist_loop_a loop 6
        // ingress from: aWorkLaneA, aFireLaneC
        // ingress directions: aWorkLaneA forward forced, aFireLaneC forward/backward random
        // cross from: aKeyRowReadA, aKeyRowReadB, mSource, aFireLaneB, aFireLaneA
        // cross directions: aKeyRowReadA backward forced, aKeyRowReadB backward forced, mSource backward forced, aFireLaneB backward forced, aFireLaneA backward/forward random
        // write to: aWorkLaneB
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = RotL64(aWorkLaneA[((aIndex + 13756U)) & S_BLOCK1], 3U) ^ RotL64(aFireLaneC[((aIndex + 14616U)) & S_BLOCK1], 40U);
            aIngress = TwistMix64::DiffuseB(aIngress);
            //
            aCross = (RotL64(aKeyRowReadA[(((2047U - aIndex) + 14534U)) & W_KEY1], 35U) ^ RotL64(aKeyRowReadB[(((2047U - aIndex) + 15090U)) & W_KEY1], 6U));
            aCross ^= (RotL64(mSource[((S_BLOCK1 - aIndex + 15803U)) & S_BLOCK1], 23U) ^ RotL64(aFireLaneB[((S_BLOCK1 - aIndex + 14471U)) & S_BLOCK1], 53U));
            aCross ^= RotL64(aFireLaneA[((aIndex + 15544U)) & S_BLOCK1], 43U);
            aCross = TwistMix64::DiffuseC(aCross);
            //
            aScatter = (RotL64(aPrevious, 5U) + RotL64(aCross, 27U)) ^ (RotL64(aIngress, 54U) + RotL64(aCarry, 39U));
            aScatter = TwistMix64::DiffuseB(aScatter);
            //
            aOrbiterC = (((aWandererI + RotL64(aIngress, 34U)) + RotL64(aCarry, 57U)) + 9435962834163239322U) + aPhaseBOrbiterAssignSaltE[(((31U - aIndex) + 18U)) & S_SALT1];
            aOrbiterJ = (aWandererJ + RotL64(aCross, 19U)) + 10524704356081318973U;
            aOrbiterI = ((aWandererB + RotL64(aScatter, 57U)) + RotL64(aCarry, 27U)) + 7403401305665208680U;
            aOrbiterE = (aWandererK + RotL64(aPrevious, 39U)) + 7525414805023556493U;
            aOrbiterF = (aWandererH + RotL64(aScatter, 51U)) + 1116686470029070951U;
            aOrbiterB = (aWandererG + RotL64(aCross, 43U)) + 13257612299137802420U;
            aOrbiterG = ((aWandererA + RotL64(aIngress, 30U)) + 9181543003986598283U) + aPhaseBOrbiterAssignSaltF[((aIndex + 15U)) & S_SALT1];
            aOrbiterK = ((aWandererF + RotL64(aPrevious, 23U)) + RotL64(aCarry, 39U)) + 9739384852307501107U;
            aOrbiterA = (aWandererC + RotL64(aIngress, 3U)) + 11308402900229016057U;
            //
            aOrbiterC = (aOrbiterC + aOrbiterJ) + 14935167593705272337U;
            aOrbiterI = (aOrbiterI ^ aOrbiterC) ^ 7171824007631943535U;
            aOrbiterI = RotL64((aOrbiterI * 4839974427616194289U), 11U);
            //
            aOrbiterE = ((aOrbiterE + aOrbiterC) + 8068411284829563567U) + aPhaseBOrbiterUpdateSaltA[((aIndex + 11U)) & S_SALT1];
            aOrbiterF = (aOrbiterF ^ aOrbiterE) ^ 12350207458513447578U;
            aOrbiterF = RotL64((aOrbiterF * 813973258659041895U), 47U);
            //
            aOrbiterF = (aOrbiterF + aOrbiterI) + 17039236343991574134U;
            aOrbiterB = (aOrbiterB ^ aOrbiterF) ^ 18291683592714999632U;
            aOrbiterB = RotL64((aOrbiterB * 7771718817924840713U), 27U);
            //
            aOrbiterI = (aOrbiterI + aOrbiterG) + 6239616841884430968U;
            aOrbiterK = (aOrbiterK ^ aOrbiterI) ^ 10604527977569876774U;
            aOrbiterK = RotL64((aOrbiterK * 6972820410084939637U), 23U);
            //
            aOrbiterB = (aOrbiterB + aOrbiterK) + 1707724300671717658U;
            aOrbiterC = (aOrbiterC ^ aOrbiterB) ^ 3802268808625297647U;
            aOrbiterC = RotL64((aOrbiterC * 11296811630387191563U), 19U);
            //
            aOrbiterJ = ((aOrbiterJ + aOrbiterE) + 9423064323799920219U) + aPhaseBOrbiterUpdateSaltC[(((31U - aIndex) + 20U)) & S_SALT1];
            aOrbiterG = (aOrbiterG ^ aOrbiterJ) ^ 242153923313096551U;
            aOrbiterG = RotL64((aOrbiterG * 12117679073775630197U), 57U);
            //
            aOrbiterA = (aOrbiterA + aOrbiterB) + 945801070951928277U;
            aOrbiterE = (aOrbiterE ^ aOrbiterA) ^ 13094814302414492064U;
            aOrbiterE = RotL64((aOrbiterE * 14638176479878969775U), 41U);
            //
            aOrbiterK = (aOrbiterK + aOrbiterA) + 7572219725951040117U;
            aOrbiterJ = ((aOrbiterJ ^ aOrbiterK) ^ 16494986983782503428U) ^ aPhaseBOrbiterUpdateSaltE[((aIndex + 14U)) & S_SALT1];
            aOrbiterJ = RotL64((aOrbiterJ * 2739189408707408171U), 51U);
            //
            aOrbiterG = ((aOrbiterG + aOrbiterF) + 10949497978229234856U) + aPhaseBOrbiterUpdateSaltD[((aIndex + 21U)) & S_SALT1];
            aOrbiterA = (aOrbiterA ^ aOrbiterG) ^ 11219643352002119905U;
            aOrbiterA = RotL64((aOrbiterA * 16900635614259262873U), 5U);
            //
            aIngress = aOrbiterA ^ RotL64(aOrbiterB, 24U);
            aIngress = aIngress + (aOrbiterF ^ RotL64(aOrbiterI, 39U));
            aIngress = aIngress + (aOrbiterK ^ RotL64(aOrbiterC, 11U));
            aIngress = aIngress + (aOrbiterJ ^ RotL64(aOrbiterG, 5U));
            aIngress = aIngress + RotL64(aOrbiterE, 60U);
            aIngress = TwistMix64::DiffuseC((aIngress + aScatter));
            //
            aWandererA = aWandererA + ((RotL64(aCross, 46U) + RotL64(aOrbiterK, 18U)) + aOrbiterG);
            aWandererK = aWandererK ^ ((RotL64(aIngress, 41U) + aOrbiterG) + RotL64(aOrbiterE, 3U));
            aWandererG = aWandererG + ((RotL64(aScatter, 27U) + RotL64(aOrbiterC, 23U)) + aOrbiterB);
            aWandererI = aWandererI ^ ((RotL64(aPrevious, 53U) + RotL64(aOrbiterB, 11U)) + aOrbiterF);
            aWandererH = aWandererH + (((RotL64(aIngress, 37U) + aOrbiterG) + RotL64(aOrbiterF, 38U)) + RotL64(aCarry, 27U));
            aWandererF = aWandererF ^ (((RotL64(aPrevious, 13U) + RotL64(aOrbiterE, 47U)) + aOrbiterI) + aPhaseBWandererUpdateSaltD[(((31U - aIndex) + 22U)) & S_SALT1]);
            aWandererC = aWandererC + ((((RotL64(aCross, 4U) + aOrbiterJ) + RotL64(aOrbiterG, 57U)) + RotL64(aCarry, 41U)) + aPhaseBWandererUpdateSaltE[((aIndex + 29U)) & S_SALT1]);
            aWandererJ = aWandererJ ^ ((RotL64(aScatter, 23U) + aOrbiterJ) + RotL64(aOrbiterE, 27U));
            aWandererB = aWandererB + ((RotL64(aCross, 19U) + aOrbiterB) + RotL64(aOrbiterA, 53U));
            //
            aCarry = aCarry + (RotL64(aWandererC, 58U) ^ aWandererG);
            aCarry = aCarry + (RotL64(aWandererJ, 47U) ^ aWandererA);
            aCarry = aCarry + (aWandererK ^ RotL64(aWandererI, 27U));
            aCarry = aCarry + (RotL64(aWandererF, 53U) ^ aWandererH);
            aCarry = aCarry + RotL64(aWandererB, 24U);
            aCarry = aCarry + RotL64(aIngress, 13U);
            aCarry = TwistMix64::DiffuseA(aCarry);
            //
            aWorkLaneB[S_BLOCK1 - aIndex] = aIngress;
        }
    
        // twist_loop_a loop 7
        // ingress from: aWorkLaneB, aKeyRowReadA, mSource, aFireLaneA
        // ingress directions: aWorkLaneB forward forced, aKeyRowReadA forward forced, mSource forward forced, aFireLaneA forward/backward random
        // cross from: aKeyRowReadB, aFireLaneD, aWorkLaneA
        // cross directions: aKeyRowReadB backward forced, aFireLaneD backward forced, aWorkLaneA backward/forward random
        // write to: aWorkLaneC
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aWorkLaneB[((aIndex + 17339U)) & S_BLOCK1], 24U) ^ RotL64(aKeyRowReadA[((aIndex + 17119U)) & W_KEY1], 11U));
            aIngress ^= (RotL64(mSource[((aIndex + 16493U)) & S_BLOCK1], 3U) ^ RotL64(aFireLaneA[((S_BLOCK1 - aIndex + 18239U)) & S_BLOCK1], 35U));
            aIngress = TwistMix64::DiffuseA(aIngress);
            //
            aCross = (RotL64(aKeyRowReadB[(((2047U - aIndex) + 16474U)) & W_KEY1], 24U) ^ RotL64(aFireLaneD[((S_BLOCK1 - aIndex + 18717U)) & S_BLOCK1], 35U));
            aCross ^= RotL64(aWorkLaneA[((S_BLOCK1 - aIndex + 18195U)) & S_BLOCK1], 3U);
            aCross = TwistMix64::DiffuseA(aCross);
            //
            aScatter = (RotL64(aCarry, 19U) + RotL64(aIngress, 43U)) ^ (RotL64(aCross, 6U) ^ RotL64(aPrevious, 57U));
            aScatter = TwistMix64::DiffuseB(aScatter);
            //
            aOrbiterK = ((aWandererF + RotL64(aIngress, 53U)) + RotL64(aCarry, 35U)) + 16651241552253078315U;
            aOrbiterA = (aWandererK + RotL64(aPrevious, 23U)) + 4558144676982478003U;
            aOrbiterH = ((aWandererE + RotL64(aCross, 57U)) + RotL64(aCarry, 19U)) + 8814884320080367550U;
            aOrbiterE = (aWandererB + RotL64(aScatter, 19U)) + 16011579668555672117U;
            aOrbiterG = ((aWandererD + RotL64(aCross, 6U)) + 4738918668759862438U) + aPhaseCOrbiterAssignSaltC[((aIndex + 7U)) & S_SALT1];
            aOrbiterD = ((aWandererG + RotL64(aScatter, 39U)) + 12526083125540985108U) + aPhaseCOrbiterAssignSaltB[((aIndex + 5U)) & S_SALT1];
            aOrbiterJ = (aWandererJ + RotL64(aPrevious, 43U)) + 8048723561746000552U;
            aOrbiterF = (aWandererI + RotL64(aIngress, 13U)) + 1082218464034639039U;
            aOrbiterC = ((aWandererH + RotL64(aScatter, 48U)) + RotL64(aCarry, 51U)) + 8432043246965946816U;
            //
            aOrbiterK = (aOrbiterK + aOrbiterA) + 9982080524048636852U;
            aOrbiterH = (aOrbiterH ^ aOrbiterK) ^ 6720069955755215919U;
            aOrbiterH = RotL64((aOrbiterH * 1025046364205332059U), 29U);
            //
            aOrbiterH = ((aOrbiterH + aOrbiterE) + 1019035028070247757U) + aPhaseCOrbiterUpdateSaltC[(((31U - aIndex) + 25U)) & S_SALT1];
            aOrbiterG = (aOrbiterG ^ aOrbiterH) ^ 7360619079463870467U;
            aOrbiterG = RotL64((aOrbiterG * 6623074813047915863U), 53U);
            //
            aOrbiterE = (aOrbiterE + aOrbiterD) + 10893918488381348474U;
            aOrbiterJ = (aOrbiterJ ^ aOrbiterE) ^ 1390297670907738019U;
            aOrbiterJ = RotL64((aOrbiterJ * 11909657437658597735U), 3U);
            //
            aOrbiterF = (aOrbiterF + aOrbiterK) + 12512200589031203480U;
            aOrbiterD = (aOrbiterD ^ aOrbiterF) ^ 14741471280748399540U;
            aOrbiterD = RotL64((aOrbiterD * 3012135242889901095U), 39U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterH) + 8543897248359826770U;
            aOrbiterC = (aOrbiterC ^ aOrbiterD) ^ 8545972622733791272U;
            aOrbiterC = RotL64((aOrbiterC * 11793879362775346821U), 47U);
            //
            aOrbiterJ = (aOrbiterJ + aOrbiterC) + 7049384618581928664U;
            aOrbiterK = ((aOrbiterK ^ aOrbiterJ) ^ 14730773807906925408U) ^ aPhaseCOrbiterUpdateSaltB[(((31U - aIndex) + 19U)) & S_SALT1];
            aOrbiterK = RotL64((aOrbiterK * 10711566871536755073U), 23U);
            //
            aOrbiterA = (aOrbiterA + aOrbiterF) + 11480717275652449986U;
            aOrbiterE = ((aOrbiterE ^ aOrbiterA) ^ 1135397594974536859U) ^ aPhaseCOrbiterUpdateSaltD[((aIndex + 27U)) & S_SALT1];
            aOrbiterE = RotL64((aOrbiterE * 6347492892938856497U), 19U);
            //
            aOrbiterG = (aOrbiterG + aOrbiterJ) + 6897207625849516702U;
            aOrbiterF = (aOrbiterF ^ aOrbiterG) ^ 10920630712550287148U;
            aOrbiterF = RotL64((aOrbiterF * 4140705091806993359U), 35U);
            //
            aOrbiterC = (aOrbiterC + aOrbiterG) + 1094056478999931332U;
            aOrbiterA = ((aOrbiterA ^ aOrbiterC) ^ 6784487144549717207U) ^ aPhaseCOrbiterUpdateSaltA[(((31U - aIndex) + 15U)) & S_SALT1];
            aOrbiterA = RotL64((aOrbiterA * 6295177724167067891U), 43U);
            //
            aIngress = RotL64(aOrbiterA, 3U) ^ aOrbiterG;
            aIngress = aIngress + (RotL64(aOrbiterD, 57U) ^ aOrbiterE);
            aIngress = aIngress + (RotL64(aOrbiterJ, 6U) ^ aOrbiterK);
            aIngress = aIngress + (RotL64(aOrbiterC, 29U) ^ aOrbiterF);
            aIngress = aIngress + RotL64(aOrbiterH, 43U);
            aIngress = TwistMix64::DiffuseC((aIngress + aScatter));
            //
            aWandererG = aWandererG + ((RotL64(aPrevious, 21U) + RotL64(aOrbiterF, 53U)) + aOrbiterC);
            aWandererI = aWandererI ^ (((RotL64(aCross, 41U) + aOrbiterF) + RotL64(aOrbiterG, 48U)) + aPhaseCWandererUpdateSaltE[((aIndex + 20U)) & S_SALT1]);
            aWandererH = aWandererH + ((RotL64(aIngress, 51U) + aOrbiterK) + RotL64(aOrbiterA, 35U));
            aWandererB = aWandererB ^ ((RotL64(aScatter, 60U) + RotL64(aOrbiterA, 27U)) + aOrbiterD);
            aWandererF = aWandererF + ((((RotL64(aCross, 47U) + aOrbiterH) + RotL64(aOrbiterG, 57U)) + RotL64(aCarry, 53U)) + aPhaseCWandererUpdateSaltD[(((31U - aIndex) + 29U)) & S_SALT1]);
            aWandererE = aWandererE ^ ((RotL64(aScatter, 13U) + RotL64(aOrbiterA, 23U)) + aOrbiterE);
            aWandererD = aWandererD + (((RotL64(aPrevious, 29U) + RotL64(aOrbiterJ, 43U)) + aOrbiterK) + RotL64(aCarry, 23U));
            aWandererK = aWandererK ^ ((RotL64(aIngress, 3U) + aOrbiterG) + RotL64(aOrbiterD, 13U));
            aWandererJ = aWandererJ + ((RotL64(aPrevious, 34U) + RotL64(aOrbiterE, 6U)) + aOrbiterD);
            //
            aCarry = aCarry + (aWandererK ^ RotL64(aWandererB, 10U));
            aCarry = aCarry + (aWandererG ^ RotL64(aWandererE, 13U));
            aCarry = aCarry + (aWandererJ ^ RotL64(aWandererI, 51U));
            aCarry = aCarry + (aWandererH ^ RotL64(aWandererD, 43U));
            aCarry = aCarry + RotL64(aWandererF, 47U);
            aCarry = aCarry + RotL64(aIngress, 21U);
            aCarry = TwistMix64::DiffuseC(aCarry);
            //
            aWorkLaneC[aIndex] = aIngress;
        }
    
        // twist_loop_a loop 8
        // ingress from: aWorkLaneC, mSource, aWorkLaneA, aFireLaneA
        // ingress directions: aWorkLaneC forward forced, mSource forward forced, aWorkLaneA forward forced, aFireLaneA forward/backward random
        // cross from: aKeyRowReadA, aKeyRowReadB, aWorkLaneB, aFireLaneB
        // cross directions: aKeyRowReadA backward forced, aKeyRowReadB backward forced, aWorkLaneB backward forced, aFireLaneB backward/forward random
        // write to: aWorkLaneD
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aWorkLaneC[((aIndex + 20004U)) & S_BLOCK1], 21U) ^ RotL64(mSource[((aIndex + 21430U)) & S_BLOCK1], 13U));
            aIngress ^= (RotL64(aWorkLaneA[((aIndex + 21647U)) & S_BLOCK1], 46U) ^ RotL64(aFireLaneA[((aIndex + 21559U)) & S_BLOCK1], 35U));
            aIngress = TwistMix64::DiffuseC(aIngress);
            //
            aCross = (RotL64(aKeyRowReadA[(((2047U - aIndex) + 20576U)) & W_KEY1], 3U) ^ RotL64(aKeyRowReadB[(((2047U - aIndex) + 20697U)) & W_KEY1], 58U));
            aCross ^= (RotL64(aWorkLaneB[((S_BLOCK1 - aIndex + 20400U)) & S_BLOCK1], 39U) ^ RotL64(aFireLaneB[((S_BLOCK1 - aIndex + 20311U)) & S_BLOCK1], 47U));
            aCross = TwistMix64::DiffuseA(aCross);
            //
            aScatter = (RotL64(aIngress, 27U) ^ RotL64(aCarry, 43U)) + (RotL64(aPrevious, 14U) + RotL64(aCross, 57U));
            aScatter = TwistMix64::DiffuseB(aScatter);
            //
            aOrbiterD = (((aWandererJ + RotL64(aIngress, 12U)) + RotL64(aCarry, 53U)) + 16124889768301047791U) + aPhaseCOrbiterAssignSaltA[(((31U - aIndex) + 26U)) & S_SALT1];
            aOrbiterA = ((aWandererG + RotL64(aCross, 39U)) + 11912338587186717280U) + aPhaseCOrbiterAssignSaltD[(((31U - aIndex) + 10U)) & S_SALT1];
            aOrbiterB = (aWandererA + RotL64(aPrevious, 23U)) + 8594012868813114354U;
            aOrbiterK = (aWandererB + RotL64(aScatter, 53U)) + 18281043566156682815U;
            aOrbiterE = (aWandererH + RotL64(aIngress, 34U)) + 16853106130200942302U;
            aOrbiterJ = (aWandererE + RotL64(aCross, 3U)) + 2611212958619673086U;
            aOrbiterH = ((aWandererK + RotL64(aPrevious, 29U)) + RotL64(aCarry, 23U)) + 18039472325066855180U;
            aOrbiterC = ((aWandererC + RotL64(aScatter, 47U)) + RotL64(aCarry, 3U)) + 14495785571345122046U;
            aOrbiterI = (aWandererI + RotL64(aCross, 43U)) + 4556063793412832418U;
            //
            aOrbiterD = (aOrbiterD + aOrbiterA) + 14896419970271244358U;
            aOrbiterB = (aOrbiterB ^ aOrbiterD) ^ 880028529183500036U;
            aOrbiterB = RotL64((aOrbiterB * 14228281807461251361U), 51U);
            //
            aOrbiterK = ((aOrbiterK + aOrbiterE) + 2379557167489415783U) + aPhaseCOrbiterUpdateSaltA[(((31U - aIndex) + 19U)) & S_SALT1];
            aOrbiterJ = ((aOrbiterJ ^ aOrbiterK) ^ 11854373946064529806U) ^ aPhaseCOrbiterUpdateSaltF[(((31U - aIndex) + 7U)) & S_SALT1];
            aOrbiterJ = RotL64((aOrbiterJ * 150755294320438887U), 41U);
            //
            aOrbiterJ = (aOrbiterJ + aOrbiterD) + 1487252775956449964U;
            aOrbiterH = (aOrbiterH ^ aOrbiterJ) ^ 12777924204511625545U;
            aOrbiterH = RotL64((aOrbiterH * 1366019527386994789U), 5U);
            //
            aOrbiterB = (aOrbiterB + aOrbiterC) + 15998631485222477969U;
            aOrbiterI = (aOrbiterI ^ aOrbiterB) ^ 8864212892296191613U;
            aOrbiterI = RotL64((aOrbiterI * 579242788050369815U), 47U);
            //
            aOrbiterC = (aOrbiterC + aOrbiterH) + 17069347835763226743U;
            aOrbiterK = (aOrbiterK ^ aOrbiterC) ^ 7443008171694679791U;
            aOrbiterK = RotL64((aOrbiterK * 748894368884566607U), 13U);
            //
            aOrbiterH = ((aOrbiterH + aOrbiterB) + 17334256152350782002U) + aPhaseCOrbiterUpdateSaltD[(((31U - aIndex) + 3U)) & S_SALT1];
            aOrbiterE = ((aOrbiterE ^ aOrbiterH) ^ 8986626119086556393U) ^ aPhaseCOrbiterUpdateSaltB[(((31U - aIndex) + 13U)) & S_SALT1];
            aOrbiterE = RotL64((aOrbiterE * 2258172145924120235U), 37U);
            //
            aOrbiterE = (aOrbiterE + aOrbiterI) + 8528180968228358674U;
            aOrbiterD = (aOrbiterD ^ aOrbiterE) ^ 12702290928064582589U;
            aOrbiterD = RotL64((aOrbiterD * 15673603224146737631U), 57U);
            //
            aOrbiterI = (aOrbiterI + aOrbiterK) + 7742438100860023610U;
            aOrbiterA = (aOrbiterA ^ aOrbiterI) ^ 3729687240959702198U;
            aOrbiterA = RotL64((aOrbiterA * 3756794766163746783U), 29U);
            //
            aOrbiterA = (aOrbiterA + aOrbiterJ) + 426129097367382096U;
            aOrbiterC = (aOrbiterC ^ aOrbiterA) ^ 16782175452274911213U;
            aOrbiterC = RotL64((aOrbiterC * 1041477289638333659U), 23U);
            //
            aIngress = RotL64(aOrbiterE, 11U) ^ aOrbiterC;
            aIngress = aIngress + (aOrbiterK ^ RotL64(aOrbiterB, 37U));
            aIngress = aIngress + (RotL64(aOrbiterD, 44U) ^ aOrbiterA);
            aIngress = aIngress + (RotL64(aOrbiterH, 5U) ^ aOrbiterI);
            aIngress = aIngress + RotL64(aOrbiterJ, 47U);
            aIngress = TwistMix64::DiffuseA((aIngress + aScatter));
            //
            aWandererG = aWandererG + ((RotL64(aPrevious, 43U) + RotL64(aOrbiterB, 51U)) + aOrbiterH);
            aWandererH = aWandererH ^ ((RotL64(aScatter, 5U) + RotL64(aOrbiterE, 27U)) + aOrbiterD);
            aWandererI = aWandererI + ((RotL64(aIngress, 39U) + aOrbiterC) + RotL64(aOrbiterA, 47U));
            aWandererB = aWandererB ^ (((RotL64(aCross, 27U) + aOrbiterI) + RotL64(aOrbiterD, 43U)) + aPhaseCWandererUpdateSaltD[((aIndex + 25U)) & S_SALT1]);
            aWandererC = aWandererC + ((RotL64(aPrevious, 10U) + aOrbiterJ) + RotL64(aOrbiterI, 56U));
            aWandererE = aWandererE ^ ((RotL64(aIngress, 51U) + aOrbiterK) + RotL64(aOrbiterB, 37U));
            aWandererA = aWandererA + ((((RotL64(aCross, 23U) + aOrbiterK) + RotL64(aOrbiterJ, 23U)) + RotL64(aCarry, 51U)) + aPhaseCWandererUpdateSaltE[((aIndex + 27U)) & S_SALT1]);
            aWandererJ = aWandererJ ^ ((RotL64(aScatter, 35U) + aOrbiterE) + RotL64(aOrbiterC, 5U));
            aWandererK = aWandererK + (((RotL64(aIngress, 56U) + aOrbiterD) + RotL64(aOrbiterK, 60U)) + RotL64(aCarry, 27U));
            //
            aCarry = aCarry + (aWandererG ^ RotL64(aWandererA, 11U));
            aCarry = aCarry + (RotL64(aWandererC, 30U) ^ aWandererK);
            aCarry = aCarry + (RotL64(aWandererJ, 35U) ^ aWandererB);
            aCarry = aCarry + (aWandererI ^ RotL64(aWandererH, 39U));
            aCarry = aCarry + RotL64(aWandererE, 43U);
            aCarry = aCarry + RotL64(aIngress, 18U);
            aCarry = TwistMix64::DiffuseA(aCarry);
            //
            aWorkLaneD[S_BLOCK1 - aIndex] = aIngress;
        }
    
        // twist_loop_a loop 9
        // ingress from: aWorkLaneD, aKeyRowReadA, aKeyRowReadB, aWorkLaneC
        // ingress directions: aWorkLaneD forward forced, aKeyRowReadA forward forced, aKeyRowReadB forward forced, aWorkLaneC forward/backward random
        // cross from: mSource, aWorkLaneA, aFireLaneC, aFireLaneD
        // cross directions: mSource backward forced, aWorkLaneA backward forced, aFireLaneC backward forced, aFireLaneD backward/forward random
        // write to: aExpandLaneA
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aWorkLaneD[((aIndex + 22713U)) & S_BLOCK1], 39U) ^ RotL64(aKeyRowReadA[((aIndex + 21888U)) & W_KEY1], 3U));
            aIngress ^= (RotL64(aKeyRowReadB[((aIndex + 22190U)) & W_KEY1], 23U) ^ RotL64(aWorkLaneC[((aIndex + 22299U)) & S_BLOCK1], 50U));
            aIngress = TwistMix64::DiffuseA(aIngress);
            //
            aCross = (RotL64(mSource[((S_BLOCK1 - aIndex + 22046U)) & S_BLOCK1], 11U) ^ RotL64(aWorkLaneA[((S_BLOCK1 - aIndex + 24168U)) & S_BLOCK1], 37U));
            aCross ^= (RotL64(aFireLaneC[((S_BLOCK1 - aIndex + 22079U)) & S_BLOCK1], 54U) ^ RotL64(aFireLaneD[((aIndex + 22841U)) & S_BLOCK1], 19U));
            aCross = TwistMix64::DiffuseA(aCross);
            //
            aScatter = (RotL64(aIngress, 20U) + RotL64(aCross, 5U)) + (RotL64(aPrevious, 35U) ^ RotL64(aCarry, 51U));
            aScatter = TwistMix64::DiffuseC(aScatter);
            //
            aOrbiterH = (aWandererA + RotL64(aIngress, 51U)) + 13960289014350612206U;
            aOrbiterD = (aWandererF + RotL64(aCross, 27U)) + 3483331015269589730U;
            aOrbiterB = (((aWandererH + RotL64(aPrevious, 35U)) + RotL64(aCarry, 27U)) + 6873299241002444518U) + aPhaseCOrbiterAssignSaltD[(((31U - aIndex) + 19U)) & S_SALT1];
            aOrbiterE = ((aWandererC + RotL64(aScatter, 14U)) + RotL64(aCarry, 47U)) + 3562094007125534229U;
            aOrbiterF = ((aWandererG + RotL64(aPrevious, 19U)) + 11422367439932782705U) + aPhaseCOrbiterAssignSaltF[(((31U - aIndex) + 27U)) & S_SALT1];
            aOrbiterI = (aWandererB + RotL64(aScatter, 43U)) + 532453428514259816U;
            aOrbiterG = (aWandererE + RotL64(aCross, 23U)) + 17810941465810193088U;
            aOrbiterK = ((aWandererK + RotL64(aIngress, 6U)) + RotL64(aCarry, 57U)) + 11869759058631106331U;
            aOrbiterA = (aWandererI + RotL64(aScatter, 39U)) + 8837581071876177566U;
            //
            aOrbiterH = (aOrbiterH + aOrbiterD) + 17185378327053837778U;
            aOrbiterB = (aOrbiterB ^ aOrbiterH) ^ 7578253375676981500U;
            aOrbiterB = RotL64((aOrbiterB * 13371647568758721729U), 47U);
            //
            aOrbiterE = ((aOrbiterE + aOrbiterF) + 17112646434432814442U) + aPhaseCOrbiterUpdateSaltA[(((31U - aIndex) + 9U)) & S_SALT1];
            aOrbiterI = (aOrbiterI ^ aOrbiterE) ^ 14949096407295697881U;
            aOrbiterI = RotL64((aOrbiterI * 14770977858283051753U), 53U);
            //
            aOrbiterF = ((aOrbiterF + aOrbiterH) + 4259590620758467836U) + aPhaseCOrbiterUpdateSaltE[(((31U - aIndex) + 28U)) & S_SALT1];
            aOrbiterG = (aOrbiterG ^ aOrbiterF) ^ 6534899413644542303U;
            aOrbiterG = RotL64((aOrbiterG * 7987609419215568661U), 57U);
            //
            aOrbiterK = ((aOrbiterK + aOrbiterE) + 2637407498893694243U) + aPhaseCOrbiterUpdateSaltD[((aIndex + 17U)) & S_SALT1];
            aOrbiterD = (aOrbiterD ^ aOrbiterK) ^ 15819295597921425711U;
            aOrbiterD = RotL64((aOrbiterD * 5202015597375051399U), 43U);
            //
            aOrbiterA = ((aOrbiterA + aOrbiterK) + 6373559542002699718U) + aPhaseCOrbiterUpdateSaltF[((aIndex + 3U)) & S_SALT1];
            aOrbiterH = (aOrbiterH ^ aOrbiterA) ^ 11694562937392022505U;
            aOrbiterH = RotL64((aOrbiterH * 9311557972331218597U), 11U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterI) + 3308736483775453062U;
            aOrbiterA = (aOrbiterA ^ aOrbiterD) ^ 12749929710650475901U;
            aOrbiterA = RotL64((aOrbiterA * 248428400724560945U), 21U);
            //
            aOrbiterG = (aOrbiterG + aOrbiterB) + 1569528215675579656U;
            aOrbiterE = (aOrbiterE ^ aOrbiterG) ^ 1044077933631689572U;
            aOrbiterE = RotL64((aOrbiterE * 6443796233912755143U), 3U);
            //
            aOrbiterB = (aOrbiterB + aOrbiterA) + 8393422728124537471U;
            aOrbiterF = (aOrbiterF ^ aOrbiterB) ^ 2002732612516530754U;
            aOrbiterF = RotL64((aOrbiterF * 13702146823622364279U), 29U);
            //
            aOrbiterI = (aOrbiterI + aOrbiterG) + 13469191942843147943U;
            aOrbiterK = (aOrbiterK ^ aOrbiterI) ^ 7633171368709520560U;
            aOrbiterK = RotL64((aOrbiterK * 9713514012478203047U), 39U);
            //
            aIngress = aOrbiterG ^ RotL64(aOrbiterH, 3U);
            aIngress = aIngress + (aOrbiterB ^ RotL64(aOrbiterF, 10U));
            aIngress = aIngress + (aOrbiterD ^ RotL64(aOrbiterI, 21U));
            aIngress = aIngress + (RotL64(aOrbiterA, 47U) ^ aOrbiterE);
            aIngress = aIngress + RotL64(aOrbiterK, 13U);
            aIngress = TwistMix64::DiffuseC((aIngress + aScatter));
            //
            aWandererK = aWandererK + ((((RotL64(aScatter, 3U) + RotL64(aOrbiterK, 13U)) + aOrbiterI) + RotL64(aCarry, 29U)) + aPhaseCWandererUpdateSaltC[(((31U - aIndex) + 26U)) & S_SALT1]);
            aWandererC = aWandererC ^ ((RotL64(aCross, 19U) + aOrbiterH) + RotL64(aOrbiterB, 37U));
            aWandererE = aWandererE + (((RotL64(aIngress, 60U) + RotL64(aOrbiterI, 4U)) + aOrbiterF) + aPhaseCWandererUpdateSaltF[(((31U - aIndex) + 15U)) & S_SALT1]);
            aWandererI = aWandererI ^ ((RotL64(aPrevious, 29U) + RotL64(aOrbiterG, 29U)) + aOrbiterE);
            aWandererF = aWandererF + ((RotL64(aScatter, 23U) + RotL64(aOrbiterD, 19U)) + aOrbiterH);
            aWandererH = aWandererH ^ ((RotL64(aPrevious, 53U) + RotL64(aOrbiterH, 41U)) + aOrbiterK);
            aWandererG = aWandererG + (((RotL64(aIngress, 35U) + RotL64(aOrbiterH, 51U)) + aOrbiterA) + RotL64(aCarry, 53U));
            aWandererB = aWandererB ^ ((RotL64(aCross, 46U) + RotL64(aOrbiterF, 57U)) + aOrbiterB);
            aWandererA = aWandererA + ((RotL64(aPrevious, 13U) + RotL64(aOrbiterG, 46U)) + aOrbiterF);
            //
            aCarry = aCarry + (RotL64(aWandererK, 57U) ^ aWandererC);
            aCarry = aCarry + (RotL64(aWandererA, 41U) ^ aWandererE);
            aCarry = aCarry + (aWandererG ^ RotL64(aWandererH, 44U));
            aCarry = aCarry + (aWandererF ^ RotL64(aWandererI, 35U));
            aCarry = aCarry + RotL64(aWandererB, 5U);
            aCarry = aCarry + RotL64(aIngress, 23U);
            aCarry = TwistMix64::DiffuseC(aCarry);
            //
            aExpandLaneA[aIndex] = aIngress;
        }
    
        // twist_loop_a loop 10
        // ingress from: aExpandLaneA, aKeyRowReadA, aWorkLaneD, aWorkLaneB
        // ingress directions: aExpandLaneA forward forced, aKeyRowReadA forward forced, aWorkLaneD forward forced, aWorkLaneB forward/backward random
        // cross from: aKeyRowReadB, mSource, aWorkLaneC, aFireLaneD
        // cross directions: aKeyRowReadB backward forced, mSource backward forced, aWorkLaneC backward forced, aFireLaneD backward/forward random
        // write to: aExpandLaneB
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aExpandLaneA[((aIndex + 27133U)) & S_BLOCK1], 57U) ^ RotL64(aKeyRowReadA[((aIndex + 26477U)) & W_KEY1], 19U));
            aIngress ^= (RotL64(aWorkLaneD[((aIndex + 24638U)) & S_BLOCK1], 28U) ^ RotL64(aWorkLaneB[((aIndex + 25339U)) & S_BLOCK1], 41U));
            aIngress = TwistMix64::DiffuseA(aIngress);
            //
            aCross = (RotL64(aKeyRowReadB[(((2047U - aIndex) + 25002U)) & W_KEY1], 27U) ^ RotL64(mSource[((S_BLOCK1 - aIndex + 26131U)) & S_BLOCK1], 4U));
            aCross ^= (RotL64(aWorkLaneC[((S_BLOCK1 - aIndex + 26273U)) & S_BLOCK1], 51U) ^ RotL64(aFireLaneD[((aIndex + 26419U)) & S_BLOCK1], 13U));
            aCross = TwistMix64::DiffuseC(aCross);
            //
            aScatter = (RotL64(aCross, 39U) + RotL64(aPrevious, 13U)) ^ (RotL64(aIngress, 26U) + RotL64(aCarry, 51U));
            aScatter = TwistMix64::DiffuseB(aScatter);
            //
            aOrbiterH = ((aWandererC + RotL64(aScatter, 11U)) + 18255347001097480328U) + aPhaseDOrbiterAssignSaltA[((aIndex + 23U)) & S_SALT1];
            aOrbiterD = ((aWandererE + RotL64(aCross, 57U)) + 13679246790311505735U) + aPhaseDOrbiterAssignSaltE[(((31U - aIndex) + 4U)) & S_SALT1];
            aOrbiterF = ((aWandererD + RotL64(aIngress, 46U)) + RotL64(aCarry, 41U)) + 10565839529765027116U;
            aOrbiterC = ((aWandererI + RotL64(aPrevious, 23U)) + RotL64(aCarry, 57U)) + 14327172566224769901U;
            aOrbiterI = (aWandererH + RotL64(aCross, 5U)) + 16239024612038195174U;
            aOrbiterA = (aWandererG + RotL64(aIngress, 41U)) + 13800012174212131890U;
            aOrbiterE = (aWandererF + RotL64(aScatter, 29U)) + 13900288860157577583U;
            aOrbiterJ = (aWandererA + RotL64(aPrevious, 35U)) + 4144386119777112740U;
            aOrbiterK = ((aWandererK + RotL64(aScatter, 18U)) + RotL64(aCarry, 27U)) + 3154558262670631372U;
            //
            aOrbiterH = (aOrbiterH + aOrbiterD) + 7456728543137614001U;
            aOrbiterF = (aOrbiterF ^ aOrbiterH) ^ 11709519851158935384U;
            aOrbiterF = RotL64((aOrbiterF * 7016689518570071587U), 51U);
            //
            aOrbiterC = (aOrbiterC + aOrbiterH) + 15607438907832240304U;
            aOrbiterI = (aOrbiterI ^ aOrbiterC) ^ 9276575329661725624U;
            aOrbiterI = RotL64((aOrbiterI * 8879744070762412745U), 39U);
            //
            aOrbiterA = (aOrbiterA + aOrbiterE) + 6459435969129449226U;
            aOrbiterJ = (aOrbiterJ ^ aOrbiterA) ^ 6442382118416542275U;
            aOrbiterJ = RotL64((aOrbiterJ * 2921027306686588233U), 19U);
            //
            aOrbiterF = (aOrbiterF + aOrbiterA) + 12117432107282150865U;
            aOrbiterK = (aOrbiterK ^ aOrbiterF) ^ 6831279293184793243U;
            aOrbiterK = RotL64((aOrbiterK * 2435360641135249073U), 29U);
            //
            aOrbiterI = ((aOrbiterI + aOrbiterF) + 9520022957804572889U) + aPhaseDOrbiterUpdateSaltB[((aIndex + 18U)) & S_SALT1];
            aOrbiterE = ((aOrbiterE ^ aOrbiterI) ^ 8322178689474588679U) ^ aPhaseDOrbiterUpdateSaltA[(((31U - aIndex) + 28U)) & S_SALT1];
            aOrbiterE = RotL64((aOrbiterE * 1627707191467537115U), 35U);
            //
            aOrbiterJ = (aOrbiterJ + aOrbiterC) + 4162401591586869316U;
            aOrbiterD = (aOrbiterD ^ aOrbiterJ) ^ 8994015844714895961U;
            aOrbiterD = RotL64((aOrbiterD * 15421910378057951895U), 43U);
            //
            aOrbiterE = (aOrbiterE + aOrbiterK) + 10038095909727959633U;
            aOrbiterC = ((aOrbiterC ^ aOrbiterE) ^ 17756404450592957616U) ^ aPhaseDOrbiterUpdateSaltC[(((31U - aIndex) + 8U)) & S_SALT1];
            aOrbiterC = RotL64((aOrbiterC * 14255952184627347295U), 3U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterI) + 3379089265413427719U;
            aOrbiterA = ((aOrbiterA ^ aOrbiterD) ^ 11341713098678108441U) ^ aPhaseDOrbiterUpdateSaltE[((aIndex + 21U)) & S_SALT1];
            aOrbiterA = RotL64((aOrbiterA * 2500587373161411961U), 57U);
            //
            aOrbiterK = (aOrbiterK + aOrbiterJ) + 4030296130743454165U;
            aOrbiterH = (aOrbiterH ^ aOrbiterK) ^ 6332387792111212064U;
            aOrbiterH = RotL64((aOrbiterH * 16490982218150897861U), 47U);
            //
            aIngress = RotL64(aOrbiterA, 13U) ^ aOrbiterK;
            aIngress = aIngress + (RotL64(aOrbiterD, 43U) ^ aOrbiterC);
            aIngress = aIngress + (aOrbiterJ ^ RotL64(aOrbiterF, 60U));
            aIngress = aIngress + (RotL64(aOrbiterH, 35U) ^ aOrbiterE);
            aIngress = aIngress + RotL64(aOrbiterI, 51U);
            aIngress = TwistMix64::DiffuseB((aIngress + aScatter));
            //
            aWandererC = aWandererC + ((RotL64(aPrevious, 35U) + RotL64(aOrbiterH, 47U)) + aOrbiterJ);
            aWandererI = aWandererI ^ ((RotL64(aScatter, 3U) + aOrbiterF) + RotL64(aOrbiterA, 56U));
            aWandererE = aWandererE + ((RotL64(aCross, 22U) + aOrbiterE) + RotL64(aOrbiterC, 5U));
            aWandererA = aWandererA ^ ((RotL64(aIngress, 11U) + aOrbiterC) + RotL64(aOrbiterK, 13U));
            aWandererG = aWandererG + (((RotL64(aScatter, 57U) + aOrbiterI) + RotL64(aOrbiterF, 51U)) + aPhaseDWandererUpdateSaltA[(((31U - aIndex) + 19U)) & S_SALT1]);
            aWandererD = aWandererD ^ (((RotL64(aCross, 51U) + RotL64(aOrbiterF, 41U)) + aOrbiterD) + aPhaseDWandererUpdateSaltD[((aIndex + 7U)) & S_SALT1]);
            aWandererF = aWandererF + (((RotL64(aPrevious, 42U) + aOrbiterI) + RotL64(aOrbiterE, 27U)) + RotL64(aCarry, 53U));
            aWandererK = aWandererK ^ ((RotL64(aIngress, 27U) + aOrbiterC) + RotL64(aOrbiterH, 22U));
            aWandererH = aWandererH + (((RotL64(aCross, 47U) + aOrbiterK) + RotL64(aOrbiterJ, 37U)) + RotL64(aCarry, 29U));
            //
            aCarry = aCarry + (aWandererE ^ RotL64(aWandererA, 47U));
            aCarry = aCarry + (aWandererK ^ RotL64(aWandererH, 29U));
            aCarry = aCarry + (aWandererI ^ RotL64(aWandererC, 11U));
            aCarry = aCarry + (RotL64(aWandererF, 5U) ^ aWandererD);
            aCarry = aCarry + RotL64(aWandererG, 18U);
            aCarry = aCarry + RotL64(aIngress, 23U);
            aCarry = TwistMix64::DiffuseB(aCarry);
            //
            aExpandLaneB[S_BLOCK1 - aIndex] = aIngress;
        }
    
        // twist_loop_a loop 11
        // ingress from: aExpandLaneB, aWorkLaneD, aKeyRowReadB, aWorkLaneC
        // ingress directions: aExpandLaneB forward forced, aWorkLaneD forward forced, aKeyRowReadB forward forced, aWorkLaneC forward/backward random
        // cross from: aKeyRowReadA, mSource, aExpandLaneA, aWorkLaneB
        // cross directions: aKeyRowReadA backward forced, mSource backward forced, aExpandLaneA backward forced, aWorkLaneB backward/forward random
        // write to: aExpandLaneC
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aExpandLaneB[((aIndex + 28637U)) & S_BLOCK1], 47U) ^ RotL64(aWorkLaneD[((aIndex + 29622U)) & S_BLOCK1], 57U));
            aIngress ^= (RotL64(aKeyRowReadB[((aIndex + 29591U)) & W_KEY1], 30U) ^ RotL64(aWorkLaneC[((aIndex + 28831U)) & S_BLOCK1], 21U));
            aIngress = TwistMix64::DiffuseB(aIngress);
            //
            aCross = (RotL64(aKeyRowReadA[(((2047U - aIndex) + 27576U)) & W_KEY1], 11U) ^ RotL64(mSource[((S_BLOCK1 - aIndex + 27968U)) & S_BLOCK1], 21U));
            aCross ^= (RotL64(aExpandLaneA[((S_BLOCK1 - aIndex + 29711U)) & S_BLOCK1], 40U) ^ RotL64(aWorkLaneB[((aIndex + 27468U)) & S_BLOCK1], 53U));
            aCross = TwistMix64::DiffuseC(aCross);
            //
            aScatter = (RotL64(aCross, 4U) + RotL64(aIngress, 19U)) ^ (RotL64(aPrevious, 37U) ^ RotL64(aCarry, 53U));
            aScatter = TwistMix64::DiffuseA(aScatter);
            //
            aOrbiterF = (aWandererH + RotL64(aPrevious, 57U)) + 3621877681473089725U;
            aOrbiterC = (aWandererF + RotL64(aScatter, 39U)) + 4451752751536414717U;
            aOrbiterG = (aWandererD + RotL64(aIngress, 43U)) + 11371625415377772117U;
            aOrbiterA = (aWandererI + RotL64(aCross, 48U)) + 6046792758881150619U;
            aOrbiterI = ((aWandererA + RotL64(aScatter, 13U)) + 8213166120394461682U) + aPhaseDOrbiterAssignSaltC[(((31U - aIndex) + 25U)) & S_SALT1];
            aOrbiterJ = (aWandererG + RotL64(aIngress, 53U)) + 4343156661140422645U;
            aOrbiterH = ((aWandererJ + RotL64(aPrevious, 3U)) + RotL64(aCarry, 41U)) + 11105271483234947905U;
            aOrbiterD = (((aWandererC + RotL64(aCross, 19U)) + RotL64(aCarry, 19U)) + 348904609985341372U) + aPhaseDOrbiterAssignSaltD[(((31U - aIndex) + 19U)) & S_SALT1];
            aOrbiterB = ((aWandererK + RotL64(aScatter, 26U)) + RotL64(aCarry, 27U)) + 12924652822526858767U;
            //
            aOrbiterF = (aOrbiterF + aOrbiterC) + 7461211697358520287U;
            aOrbiterG = (aOrbiterG ^ aOrbiterF) ^ 16551553555297890558U;
            aOrbiterG = RotL64((aOrbiterG * 16432952324635746293U), 13U);
            //
            aOrbiterA = (aOrbiterA + aOrbiterF) + 11908056404140782995U;
            aOrbiterI = (aOrbiterI ^ aOrbiterA) ^ 9147367258259948715U;
            aOrbiterI = RotL64((aOrbiterI * 10777628928376261667U), 39U);
            //
            aOrbiterG = (aOrbiterG + aOrbiterJ) + 8876461054692728610U;
            aOrbiterH = (aOrbiterH ^ aOrbiterG) ^ 10546855952702525404U;
            aOrbiterH = RotL64((aOrbiterH * 10071104785895309677U), 51U);
            //
            aOrbiterH = (aOrbiterH + aOrbiterD) + 4748636139110443794U;
            aOrbiterA = ((aOrbiterA ^ aOrbiterH) ^ 783046909529525098U) ^ aPhaseDOrbiterUpdateSaltA[((aIndex + 29U)) & S_SALT1];
            aOrbiterA = RotL64((aOrbiterA * 8969157702460927215U), 23U);
            //
            aOrbiterI = (aOrbiterI + aOrbiterG) + 16683965945838696665U;
            aOrbiterB = (aOrbiterB ^ aOrbiterI) ^ 12385412690177109575U;
            aOrbiterB = RotL64((aOrbiterB * 10795062772707143187U), 27U);
            //
            aOrbiterJ = ((aOrbiterJ + aOrbiterI) + 8210546822184469023U) + aPhaseDOrbiterUpdateSaltC[(((31U - aIndex) + 24U)) & S_SALT1];
            aOrbiterD = (aOrbiterD ^ aOrbiterJ) ^ 13146493623236979963U;
            aOrbiterD = RotL64((aOrbiterD * 13199947810161148155U), 5U);
            //
            aOrbiterB = (aOrbiterB + aOrbiterH) + 13857628148804187115U;
            aOrbiterC = (aOrbiterC ^ aOrbiterB) ^ 7241297989337473475U;
            aOrbiterC = RotL64((aOrbiterC * 16223448508809614229U), 57U);
            //
            aOrbiterD = ((aOrbiterD + aOrbiterB) + 773904571213804946U) + aPhaseDOrbiterUpdateSaltD[(((31U - aIndex) + 15U)) & S_SALT1];
            aOrbiterF = ((aOrbiterF ^ aOrbiterD) ^ 7660676598236419707U) ^ aPhaseDOrbiterUpdateSaltE[((aIndex + 14U)) & S_SALT1];
            aOrbiterF = RotL64((aOrbiterF * 14467390638468925567U), 47U);
            //
            aOrbiterC = (aOrbiterC + aOrbiterA) + 16822672435156055469U;
            aOrbiterJ = (aOrbiterJ ^ aOrbiterC) ^ 6514707119190640433U;
            aOrbiterJ = RotL64((aOrbiterJ * 7097496727567460535U), 19U);
            //
            aIngress = aOrbiterB ^ RotL64(aOrbiterA, 54U);
            aIngress = aIngress + (RotL64(aOrbiterI, 51U) ^ aOrbiterJ);
            aIngress = aIngress + (aOrbiterF ^ RotL64(aOrbiterG, 21U));
            aIngress = aIngress + (RotL64(aOrbiterH, 57U) ^ aOrbiterC);
            aIngress = aIngress + RotL64(aOrbiterD, 29U);
            aIngress = TwistMix64::DiffuseA((aIngress + aScatter));
            //
            aWandererK = aWandererK + ((RotL64(aIngress, 57U) + RotL64(aOrbiterF, 58U)) + aOrbiterC);
            aWandererH = aWandererH ^ ((RotL64(aScatter, 18U) + RotL64(aOrbiterF, 3U)) + aOrbiterJ);
            aWandererI = aWandererI + ((((RotL64(aCross, 35U) + aOrbiterH) + RotL64(aOrbiterA, 51U)) + RotL64(aCarry, 39U)) + aPhaseDWandererUpdateSaltB[((aIndex + 16U)) & S_SALT1]);
            aWandererJ = aWandererJ ^ ((RotL64(aPrevious, 39U) + aOrbiterB) + RotL64(aOrbiterH, 35U));
            aWandererD = aWandererD + ((RotL64(aScatter, 29U) + RotL64(aOrbiterJ, 41U)) + aOrbiterI);
            aWandererG = aWandererG ^ ((RotL64(aCross, 43U) + aOrbiterJ) + RotL64(aOrbiterG, 22U));
            aWandererA = aWandererA + (((RotL64(aPrevious, 48U) + aOrbiterG) + RotL64(aOrbiterH, 27U)) + RotL64(aCarry, 53U));
            aWandererF = aWandererF ^ (((RotL64(aIngress, 3U) + aOrbiterD) + RotL64(aOrbiterJ, 47U)) + aPhaseDWandererUpdateSaltA[(((31U - aIndex) + 6U)) & S_SALT1]);
            aWandererC = aWandererC + ((RotL64(aCross, 13U) + aOrbiterG) + RotL64(aOrbiterI, 13U));
            //
            aCarry = aCarry + (RotL64(aWandererK, 3U) ^ aWandererJ);
            aCarry = aCarry + (RotL64(aWandererH, 35U) ^ aWandererI);
            aCarry = aCarry + (RotL64(aWandererF, 58U) ^ aWandererA);
            aCarry = aCarry + (RotL64(aWandererC, 21U) ^ aWandererD);
            aCarry = aCarry + RotL64(aWandererG, 13U);
            aCarry = aCarry + RotL64(aIngress, 39U);
            aCarry = TwistMix64::DiffuseC(aCarry);
            //
            aExpandLaneC[aIndex] = aIngress;
        }
    
        // twist_loop_a loop 12
        // ingress from: aExpandLaneC, aKeyRowReadA
        // ingress directions: aExpandLaneC forward forced, aKeyRowReadA forward/backward random
        // cross from: aWorkLaneD, aExpandLaneA, aExpandLaneB, aKeyRowReadB
        // cross directions: aWorkLaneD backward forced, aExpandLaneA backward forced, aExpandLaneB backward forced, aKeyRowReadB backward/forward random
        // write to: aExpandLaneD
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = RotL64(aExpandLaneC[((aIndex + 32039U)) & S_BLOCK1], 35U) ^ RotL64(aKeyRowReadA[(((2047U - aIndex) + 32608U)) & W_KEY1], 22U);
            aIngress = TwistMix64::DiffuseB(aIngress);
            //
            aCross = (RotL64(aWorkLaneD[((S_BLOCK1 - aIndex + 30289U)) & S_BLOCK1], 24U) ^ RotL64(aExpandLaneA[((S_BLOCK1 - aIndex + 31634U)) & S_BLOCK1], 5U));
            aCross ^= (RotL64(aExpandLaneB[((S_BLOCK1 - aIndex + 32473U)) & S_BLOCK1], 13U) ^ RotL64(aKeyRowReadB[(((2047U - aIndex) + 31801U)) & W_KEY1], 39U));
            aCross = TwistMix64::DiffuseC(aCross);
            //
            aScatter = (RotL64(aPrevious, 37U) ^ RotL64(aCarry, 21U)) + (RotL64(aIngress, 3U) + RotL64(aCross, 52U));
            aScatter = TwistMix64::DiffuseC(aScatter);
            //
            aOrbiterB = ((aWandererK + RotL64(aPrevious, 11U)) + 6069475454765660321U) + aPhaseDOrbiterAssignSaltF[((aIndex + 11U)) & S_SALT1];
            aOrbiterA = ((aWandererI + RotL64(aScatter, 57U)) + RotL64(aCarry, 23U)) + 11483704742497268068U;
            aOrbiterK = (aWandererD + RotL64(aIngress, 29U)) + 11055697447388986418U;
            aOrbiterC = (aWandererE + RotL64(aCross, 35U)) + 10897095046039997004U;
            aOrbiterG = (aWandererJ + RotL64(aScatter, 52U)) + 4731637118230457840U;
            aOrbiterI = (aWandererG + RotL64(aIngress, 21U)) + 13855839187084986751U;
            aOrbiterE = ((aWandererF + RotL64(aPrevious, 3U)) + 5328208115460188239U) + aPhaseDOrbiterAssignSaltB[((aIndex + 27U)) & S_SALT1];
            aOrbiterD = ((aWandererH + RotL64(aCross, 43U)) + RotL64(aCarry, 39U)) + 12479538544291412985U;
            aOrbiterJ = ((aWandererB + RotL64(aIngress, 48U)) + RotL64(aCarry, 53U)) + 10740165998792608231U;
            //
            aOrbiterB = (aOrbiterB + aOrbiterA) + 6492798157284955373U;
            aOrbiterK = (aOrbiterK ^ aOrbiterB) ^ 13056825957483891921U;
            aOrbiterK = RotL64((aOrbiterK * 14882112110627751751U), 57U);
            //
            aOrbiterA = (aOrbiterA + aOrbiterC) + 2068184064919194657U;
            aOrbiterG = (aOrbiterG ^ aOrbiterA) ^ 5656302738780746294U;
            aOrbiterG = RotL64((aOrbiterG * 16493021179127646345U), 39U);
            //
            aOrbiterG = (aOrbiterG + aOrbiterI) + 11193756120230763294U;
            aOrbiterE = ((aOrbiterE ^ aOrbiterG) ^ 17306750816837208999U) ^ aPhaseDOrbiterUpdateSaltD[(((31U - aIndex) + 3U)) & S_SALT1];
            aOrbiterE = RotL64((aOrbiterE * 7949360041241439741U), 21U);
            //
            aOrbiterE = (aOrbiterE + aOrbiterD) + 12952818800389361804U;
            aOrbiterC = ((aOrbiterC ^ aOrbiterE) ^ 15380412293642628312U) ^ aPhaseDOrbiterUpdateSaltE[((aIndex + 4U)) & S_SALT1];
            aOrbiterC = RotL64((aOrbiterC * 2914662289178925547U), 47U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterJ) + 7706090204767242996U;
            aOrbiterB = (aOrbiterB ^ aOrbiterD) ^ 14598802276412649570U;
            aOrbiterB = RotL64((aOrbiterB * 4821408736292041399U), 53U);
            //
            aOrbiterC = (aOrbiterC + aOrbiterB) + 17819762117328075515U;
            aOrbiterI = ((aOrbiterI ^ aOrbiterC) ^ 6481384240915075101U) ^ aPhaseDOrbiterUpdateSaltF[((aIndex + 21U)) & S_SALT1];
            aOrbiterI = RotL64((aOrbiterI * 4836701121865783029U), 27U);
            //
            aOrbiterK = (aOrbiterK + aOrbiterG) + 754936290510338717U;
            aOrbiterJ = ((aOrbiterJ ^ aOrbiterK) ^ 15510875946573720154U) ^ aPhaseDOrbiterUpdateSaltB[(((31U - aIndex) + 9U)) & S_SALT1];
            aOrbiterJ = RotL64((aOrbiterJ * 2994718968852184303U), 13U);
            //
            aOrbiterJ = (aOrbiterJ + aOrbiterE) + 9245381722813944586U;
            aOrbiterA = (aOrbiterA ^ aOrbiterJ) ^ 2629847912019726214U;
            aOrbiterA = RotL64((aOrbiterA * 6718795794951106961U), 35U);
            //
            aOrbiterI = (aOrbiterI + aOrbiterK) + 3909987749797113773U;
            aOrbiterD = (aOrbiterD ^ aOrbiterI) ^ 9277056074757335265U;
            aOrbiterD = RotL64((aOrbiterD * 11580847505996697115U), 3U);
            //
            aIngress = RotL64(aOrbiterA, 23U) ^ aOrbiterG;
            aIngress = aIngress + (RotL64(aOrbiterD, 57U) ^ aOrbiterI);
            aIngress = aIngress + (RotL64(aOrbiterK, 47U) ^ aOrbiterE);
            aIngress = aIngress + (RotL64(aOrbiterB, 3U) ^ aOrbiterC);
            aIngress = aIngress + RotL64(aOrbiterJ, 6U);
            aIngress = TwistMix64::DiffuseA((aIngress + aScatter));
            //
            aWandererE = aWandererE ^ ((RotL64(aIngress, 29U) + aOrbiterE) + RotL64(aOrbiterG, 41U));
            aWandererD = aWandererD + (((RotL64(aPrevious, 19U) + aOrbiterE) + RotL64(aOrbiterD, 46U)) + RotL64(aCarry, 53U));
            aWandererF = aWandererF ^ (((RotL64(aScatter, 39U) + RotL64(aOrbiterA, 29U)) + aOrbiterD) + aPhaseDWandererUpdateSaltB[((aIndex + 14U)) & S_SALT1]);
            aWandererI = aWandererI + (((RotL64(aCross, 48U) + RotL64(aOrbiterA, 19U)) + aOrbiterK) + RotL64(aCarry, 13U));
            aWandererG = aWandererG ^ ((RotL64(aScatter, 3U) + aOrbiterE) + RotL64(aOrbiterC, 23U));
            aWandererH = aWandererH + ((RotL64(aPrevious, 23U) + RotL64(aOrbiterG, 51U)) + aOrbiterJ);
            aWandererB = aWandererB ^ ((RotL64(aCross, 35U) + RotL64(aOrbiterC, 3U)) + aOrbiterB);
            aWandererJ = aWandererJ + ((RotL64(aIngress, 43U) + RotL64(aOrbiterE, 10U)) + aOrbiterK);
            aWandererK = aWandererK ^ (((RotL64(aScatter, 58U) + aOrbiterK) + RotL64(aOrbiterI, 37U)) + aPhaseDWandererUpdateSaltD[((aIndex + 7U)) & S_SALT1]);
            //
            aCarry = aCarry + (RotL64(aWandererF, 53U) ^ aWandererE);
            aCarry = aCarry + (RotL64(aWandererI, 47U) ^ aWandererK);
            aCarry = aCarry + (RotL64(aWandererB, 14U) ^ aWandererH);
            aCarry = aCarry + (aWandererD ^ RotL64(aWandererJ, 3U));
            aCarry = aCarry + RotL64(aWandererG, 11U);
            aCarry = aCarry + RotL64(aIngress, 29U);
            aCarry = TwistMix64::DiffuseA(aCarry);
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

void TwistExpander_Greezy_Arx::Twist_B(TwistWorkSpace *pWorkSpace,
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
    [[maybe_unused]] std::uint8_t *aFireLaneA = pWorkSpace->mFireLaneA;
    [[maybe_unused]] std::uint8_t *aFireLaneB = pWorkSpace->mFireLaneB;
    [[maybe_unused]] std::uint8_t *aFireLaneC = pWorkSpace->mFireLaneC;
    [[maybe_unused]] std::uint8_t *aFireLaneD = pWorkSpace->mFireLaneD;
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
        // read from: aExpandLaneA, aExpandLaneB, aFireLaneA, aExpandLaneC, aExpandLaneD, aFireLaneB, aOperationLaneA, aFireLaneC, aFireLaneD, aOperationLaneB, aWorkLaneA, aWorkLaneB, aOperationLaneC, aWorkLaneC, aWorkLaneD
        // write to: aOperationLaneA, aOperationLaneB, aOperationLaneC, aOperationLaneD
    
        // twist_loop_b loop 1
        // ingress from: aExpandLaneA, aExpandLaneB, aFireLaneA
        // ingress directions: aExpandLaneA forward forced, aExpandLaneB forward forced, aFireLaneA forward/backward random
        // cross from: aExpandLaneC, aExpandLaneD, aFireLaneB
        // cross directions: aExpandLaneC backward forced, aExpandLaneD backward forced, aFireLaneB backward/forward random
        // write to: aOperationLaneA
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aExpandLaneA[((aIndex + 5960U)) & S_BLOCK1], 50U) ^ RotL64(aExpandLaneB[((aIndex + 4940U)) & S_BLOCK1], 11U));
            aIngress ^= RotL64(aFireLaneA[((S_BLOCK1 - aIndex + 6358U)) & S_BLOCK1], 35U);
            aIngress = TwistMix64::DiffuseA(aIngress);
            //
            aCross = (RotL64(aExpandLaneC[((S_BLOCK1 - aIndex + 3193U)) & S_BLOCK1], 57U) ^ RotL64(aExpandLaneD[((S_BLOCK1 - aIndex + 4696U)) & S_BLOCK1], 37U));
            aCross ^= RotL64(aFireLaneB[((S_BLOCK1 - aIndex + 7153U)) & S_BLOCK1], 46U);
            aCross = TwistMix64::DiffuseC(aCross);
            //
            aScatter = (RotL64(aCross, 22U) + RotL64(aPrevious, 39U)) ^ (RotL64(aCarry, 5U) + RotL64(aIngress, 57U));
            aScatter = TwistMix64::DiffuseB(aScatter);
            //
            aOrbiterI = (aWandererB + RotL64(aPrevious, 51U)) + 7790166497945719700U;
            aOrbiterK = ((aWandererD + RotL64(aScatter, 34U)) + 7136208896846119188U) + aPhaseEOrbiterAssignSaltA[((aIndex + 17U)) & S_SALT1];
            aOrbiterB = (aWandererF + RotL64(aCross, 13U)) + 12123156943355100886U;
            aOrbiterJ = ((aWandererG + RotL64(aIngress, 19U)) + RotL64(aCarry, 51U)) + 5095546037880875199U;
            aOrbiterH = ((aWandererI + RotL64(aCross, 57U)) + RotL64(aCarry, 35U)) + 17642705393916765992U;
            aOrbiterA = (((aWandererK + RotL64(aPrevious, 5U)) + RotL64(aCarry, 11U)) + 9918479837334416990U) + aPhaseEOrbiterAssignSaltF[((aIndex + 23U)) & S_SALT1];
            aOrbiterF = (aWandererE + RotL64(aIngress, 41U)) + 4890009823843176466U;
            //
            aOrbiterI = (aOrbiterI + aOrbiterK) + 17652590786213674124U;
            aOrbiterB = (aOrbiterB ^ aOrbiterI) ^ 870002527644696135U;
            aOrbiterB = RotL64((aOrbiterB * 915408393979165539U), 13U);
            //
            aOrbiterJ = (aOrbiterJ + aOrbiterH) + 12545429703552643682U;
            aOrbiterK = ((aOrbiterK ^ aOrbiterJ) ^ 5310272867406182581U) ^ aPhaseEOrbiterUpdateSaltA[(((31U - aIndex) + 3U)) & S_SALT1];
            aOrbiterK = RotL64((aOrbiterK * 10420003334833925011U), 51U);
            //
            aOrbiterA = ((aOrbiterA + aOrbiterJ) + 3264719049050179440U) + aPhaseEOrbiterUpdateSaltE[((aIndex + 10U)) & S_SALT1];
            aOrbiterI = (aOrbiterI ^ aOrbiterA) ^ 1967241238180278937U;
            aOrbiterI = RotL64((aOrbiterI * 13004319774269457957U), 29U);
            //
            aOrbiterF = (aOrbiterF + aOrbiterI) + 773883832927040736U;
            aOrbiterH = ((aOrbiterH ^ aOrbiterF) ^ 12766817190261232485U) ^ aPhaseEOrbiterUpdateSaltF[(((31U - aIndex) + 7U)) & S_SALT1];
            aOrbiterH = RotL64((aOrbiterH * 7448864556802318431U), 5U);
            //
            aOrbiterB = (aOrbiterB + aOrbiterF) + 260069382395598265U;
            aOrbiterJ = ((aOrbiterJ ^ aOrbiterB) ^ 15462103891287350123U) ^ aPhaseEOrbiterUpdateSaltD[((aIndex + 27U)) & S_SALT1];
            aOrbiterJ = RotL64((aOrbiterJ * 5029268763635635753U), 57U);
            //
            aOrbiterK = (aOrbiterK + aOrbiterA) + 4072032867513289827U;
            aOrbiterF = (aOrbiterF ^ aOrbiterK) ^ 17153061419083897076U;
            aOrbiterF = RotL64((aOrbiterF * 11934532169271718913U), 43U);
            //
            aOrbiterH = (aOrbiterH + aOrbiterB) + 6207264270332656966U;
            aOrbiterA = (aOrbiterA ^ aOrbiterH) ^ 18048064697837314947U;
            aOrbiterA = RotL64((aOrbiterA * 13632594619404208489U), 37U);
            //
            aIngress = RotL64(aOrbiterK, 13U) ^ aOrbiterI;
            aIngress = aIngress + (aOrbiterA ^ RotL64(aOrbiterH, 35U));
            aIngress = aIngress + (RotL64(aOrbiterB, 47U) ^ aOrbiterJ);
            aIngress = aIngress + RotL64(aOrbiterF, 29U);
            aIngress = TwistMix64::DiffuseA((aIngress + aScatter));
            //
            aWandererK = aWandererK + (((RotL64(aIngress, 11U) + aOrbiterI) + RotL64(aOrbiterF, 35U)) + RotL64(aCarry, 57U));
            aWandererE = aWandererE ^ ((RotL64(aScatter, 18U) + RotL64(aOrbiterI, 11U)) + aOrbiterA);
            aWandererD = aWandererD + (((RotL64(aPrevious, 29U) + aOrbiterI) + RotL64(aOrbiterB, 51U)) + aPhaseEWandererUpdateSaltC[(((31U - aIndex) + 21U)) & S_SALT1]);
            aWandererI = aWandererI ^ ((RotL64(aCross, 43U) + RotL64(aOrbiterK, 57U)) + aOrbiterI);
            aWandererF = aWandererF + ((RotL64(aIngress, 51U) + aOrbiterJ) + RotL64(aOrbiterH, 43U));
            aWandererG = aWandererG ^ ((RotL64(aPrevious, 5U) + RotL64(aOrbiterB, 4U)) + aOrbiterJ);
            aWandererB = aWandererB + ((((RotL64(aScatter, 57U) + RotL64(aOrbiterK, 21U)) + aOrbiterJ) + RotL64(aCarry, 21U)) + aPhaseEWandererUpdateSaltF[(((31U - aIndex) + 18U)) & S_SALT1]);
            //
            aCarry = aCarry + (RotL64(aWandererD, 23U) ^ aWandererG);
            aCarry = aCarry + (RotL64(aWandererB, 38U) ^ aWandererE);
            aCarry = aCarry + (aWandererI ^ RotL64(aWandererK, 29U));
            aCarry = aCarry + RotL64(aWandererF, 5U);
            aCarry = aCarry + RotL64(aIngress, 57U);
            aCarry = TwistMix64::DiffuseA(aCarry);
            //
            aOperationLaneA[aIndex] = aIngress;
        }
    
        // twist_loop_b loop 2
        // ingress from: aOperationLaneA, aExpandLaneC, aExpandLaneD, aFireLaneC
        // ingress directions: aOperationLaneA forward forced, aExpandLaneC forward forced, aExpandLaneD forward forced, aFireLaneC forward/backward random
        // cross from: aExpandLaneA, aExpandLaneB, aFireLaneD
        // cross directions: aExpandLaneA backward forced, aExpandLaneB backward forced, aFireLaneD backward/forward random
        // write to: aOperationLaneB
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aOperationLaneA[((aIndex + 12650U)) & S_BLOCK1], 48U) ^ RotL64(aExpandLaneC[((aIndex + 15743U)) & S_BLOCK1], 5U));
            aIngress ^= (RotL64(aExpandLaneD[((aIndex + 8818U)) & S_BLOCK1], 27U) ^ RotL64(aFireLaneC[((S_BLOCK1 - aIndex + 11718U)) & S_BLOCK1], 13U));
            aIngress = TwistMix64::DiffuseC(aIngress);
            //
            aCross = (RotL64(aExpandLaneA[((S_BLOCK1 - aIndex + 13237U)) & S_BLOCK1], 22U) ^ RotL64(aExpandLaneB[((S_BLOCK1 - aIndex + 12722U)) & S_BLOCK1], 3U));
            aCross ^= RotL64(aFireLaneD[((S_BLOCK1 - aIndex + 11765U)) & S_BLOCK1], 51U);
            aCross = TwistMix64::DiffuseA(aCross);
            //
            aScatter = (RotL64(aCross, 3U) ^ RotL64(aIngress, 41U)) + (RotL64(aPrevious, 22U) ^ RotL64(aCarry, 53U));
            aScatter = TwistMix64::DiffuseA(aScatter);
            //
            aOrbiterG = (((aWandererF + RotL64(aCross, 11U)) + RotL64(aCarry, 11U)) + 4476099022490972343U) + aPhaseEOrbiterAssignSaltC[(((31U - aIndex) + 5U)) & S_SALT1];
            aOrbiterD = (aWandererG + RotL64(aIngress, 54U)) + 16836423700375760429U;
            aOrbiterF = (aWandererB + RotL64(aScatter, 29U)) + 8850577488928703557U;
            aOrbiterA = (aWandererI + RotL64(aPrevious, 19U)) + 7091631824560042743U;
            aOrbiterE = (aWandererE + RotL64(aScatter, 3U)) + 12560498899956759494U;
            aOrbiterJ = (((aWandererC + RotL64(aIngress, 35U)) + RotL64(aCarry, 47U)) + 7797973377112012161U) + aPhaseEOrbiterAssignSaltB[((aIndex + 9U)) & S_SALT1];
            aOrbiterI = ((aWandererD + RotL64(aPrevious, 47U)) + RotL64(aCarry, 27U)) + 6173820673874805794U;
            //
            aOrbiterG = (aOrbiterG + aOrbiterD) + 10805025132310245348U;
            aOrbiterF = (aOrbiterF ^ aOrbiterG) ^ 7139216143268029968U;
            aOrbiterF = RotL64((aOrbiterF * 8349754682635765573U), 21U);
            //
            aOrbiterA = (aOrbiterA + aOrbiterF) + 8241544862261635722U;
            aOrbiterE = (aOrbiterE ^ aOrbiterA) ^ 4735527016563596150U;
            aOrbiterE = RotL64((aOrbiterE * 6621354217673598381U), 53U);
            //
            aOrbiterJ = ((aOrbiterJ + aOrbiterE) + 5166171126690294033U) + aPhaseEOrbiterUpdateSaltD[(((31U - aIndex) + 19U)) & S_SALT1];
            aOrbiterG = ((aOrbiterG ^ aOrbiterJ) ^ 11117641762075368393U) ^ aPhaseEOrbiterUpdateSaltB[(((31U - aIndex) + 20U)) & S_SALT1];
            aOrbiterG = RotL64((aOrbiterG * 4980156869201219393U), 3U);
            //
            aOrbiterE = (aOrbiterE + aOrbiterI) + 6312932356458415421U;
            aOrbiterD = (aOrbiterD ^ aOrbiterE) ^ 1304139291184508668U;
            aOrbiterD = RotL64((aOrbiterD * 90744653170922319U), 47U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterA) + 10085025354842771067U;
            aOrbiterJ = (aOrbiterJ ^ aOrbiterD) ^ 16745854428789531080U;
            aOrbiterJ = RotL64((aOrbiterJ * 1945983905747274355U), 13U);
            //
            aOrbiterF = ((aOrbiterF + aOrbiterJ) + 2497187958708890337U) + aPhaseEOrbiterUpdateSaltE[((aIndex + 4U)) & S_SALT1];
            aOrbiterI = (aOrbiterI ^ aOrbiterF) ^ 16069701876646548995U;
            aOrbiterI = RotL64((aOrbiterI * 16606039730973709495U), 27U);
            //
            aOrbiterI = ((aOrbiterI + aOrbiterG) + 17242004368025978091U) + aPhaseEOrbiterUpdateSaltC[((aIndex + 25U)) & S_SALT1];
            aOrbiterA = (aOrbiterA ^ aOrbiterI) ^ 12334315722243232121U;
            aOrbiterA = RotL64((aOrbiterA * 16528598396696346719U), 41U);
            //
            aIngress = RotL64(aOrbiterF, 5U) ^ aOrbiterI;
            aIngress = aIngress + (aOrbiterJ ^ RotL64(aOrbiterD, 51U));
            aIngress = aIngress + (aOrbiterA ^ RotL64(aOrbiterE, 13U));
            aIngress = aIngress + RotL64(aOrbiterG, 57U);
            aIngress = TwistMix64::DiffuseA((aIngress + aScatter));
            //
            aWandererG = aWandererG ^ ((RotL64(aScatter, 11U) + RotL64(aOrbiterD, 51U)) + aOrbiterE);
            aWandererB = aWandererB + (((RotL64(aCross, 5U) + RotL64(aOrbiterA, 35U)) + aOrbiterE) + RotL64(aCarry, 51U));
            aWandererI = aWandererI ^ (((RotL64(aPrevious, 29U) + aOrbiterG) + RotL64(aOrbiterF, 14U)) + aPhaseEWandererUpdateSaltB[(((31U - aIndex) + 14U)) & S_SALT1]);
            aWandererD = aWandererD + (((RotL64(aIngress, 53U) + aOrbiterD) + RotL64(aOrbiterJ, 29U)) + aPhaseEWandererUpdateSaltA[((aIndex + 18U)) & S_SALT1]);
            aWandererF = aWandererF ^ ((RotL64(aPrevious, 41U) + RotL64(aOrbiterA, 5U)) + aOrbiterF);
            aWandererE = aWandererE + (((RotL64(aScatter, 22U) + RotL64(aOrbiterD, 41U)) + aOrbiterA) + RotL64(aCarry, 3U));
            aWandererC = aWandererC ^ ((RotL64(aIngress, 35U) + RotL64(aOrbiterA, 57U)) + aOrbiterI);
            //
            aCarry = aCarry + (RotL64(aWandererB, 12U) ^ aWandererD);
            aCarry = aCarry + (aWandererI ^ RotL64(aWandererE, 23U));
            aCarry = aCarry + (aWandererG ^ RotL64(aWandererF, 57U));
            aCarry = aCarry + RotL64(aWandererC, 3U);
            aCarry = aCarry + RotL64(aIngress, 39U);
            aCarry = TwistMix64::DiffuseB(aCarry);
            //
            aOperationLaneB[S_BLOCK1 - aIndex] = aIngress;
        }
    
        // twist_loop_b loop 3
        // ingress from: aOperationLaneB, aExpandLaneA, aExpandLaneB, aWorkLaneA
        // ingress directions: aOperationLaneB forward forced, aExpandLaneA forward forced, aExpandLaneB forward forced, aWorkLaneA forward/backward random
        // cross from: aOperationLaneA, aExpandLaneC, aWorkLaneB
        // cross directions: aOperationLaneA backward forced, aExpandLaneC backward forced, aWorkLaneB backward/forward random
        // write to: aOperationLaneC
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aOperationLaneB[((aIndex + 23955U)) & S_BLOCK1], 35U) ^ RotL64(aExpandLaneA[((aIndex + 16963U)) & S_BLOCK1], 3U));
            aIngress ^= (RotL64(aExpandLaneB[((aIndex + 22819U)) & S_BLOCK1], 14U) ^ RotL64(aWorkLaneA[((S_BLOCK1 - aIndex + 21925U)) & S_BLOCK1], 43U));
            aIngress = TwistMix64::DiffuseB(aIngress);
            //
            aCross = (RotL64(aOperationLaneA[((S_BLOCK1 - aIndex + 16500U)) & S_BLOCK1], 24U) ^ RotL64(aExpandLaneC[((S_BLOCK1 - aIndex + 23929U)) & S_BLOCK1], 39U));
            aCross ^= RotL64(aWorkLaneB[((S_BLOCK1 - aIndex + 19462U)) & S_BLOCK1], 53U);
            aCross = TwistMix64::DiffuseB(aCross);
            //
            aScatter = (RotL64(aIngress, 39U) + RotL64(aCarry, 27U)) ^ (RotL64(aPrevious, 54U) ^ RotL64(aCross, 13U));
            aScatter = TwistMix64::DiffuseB(aScatter);
            //
            aOrbiterJ = (aWandererB + RotL64(aCross, 51U)) + 12262991801139086177U;
            aOrbiterG = (aWandererC + RotL64(aPrevious, 13U)) + 7963038771924890197U;
            aOrbiterK = (((aWandererG + RotL64(aScatter, 23U)) + RotL64(aCarry, 11U)) + 15540520327933568896U) + aPhaseEOrbiterAssignSaltE[(((31U - aIndex) + 4U)) & S_SALT1];
            aOrbiterI = (aWandererE + RotL64(aIngress, 42U)) + 8745565892055020722U;
            aOrbiterB = (aWandererH + RotL64(aPrevious, 5U)) + 16619329199683755286U;
            aOrbiterA = ((aWandererF + RotL64(aIngress, 29U)) + RotL64(aCarry, 53U)) + 10865705026433867260U;
            aOrbiterC = (((aWandererA + RotL64(aCross, 57U)) + RotL64(aCarry, 37U)) + 2743368697984518059U) + aPhaseEOrbiterAssignSaltD[(((31U - aIndex) + 7U)) & S_SALT1];
            //
            aOrbiterJ = (aOrbiterJ + aOrbiterG) + 5556006271515473135U;
            aOrbiterK = (aOrbiterK ^ aOrbiterJ) ^ 5355833281353498588U;
            aOrbiterK = RotL64((aOrbiterK * 4190140212757841511U), 29U);
            //
            aOrbiterI = (aOrbiterI + aOrbiterB) + 8313616108963479829U;
            aOrbiterA = (aOrbiterA ^ aOrbiterI) ^ 16657121016801866434U;
            aOrbiterA = RotL64((aOrbiterA * 331533349428472477U), 53U);
            //
            aOrbiterA = (aOrbiterA + aOrbiterC) + 16532226425013000833U;
            aOrbiterJ = (aOrbiterJ ^ aOrbiterA) ^ 5800465874932467232U;
            aOrbiterJ = RotL64((aOrbiterJ * 5966395771690704577U), 19U);
            //
            aOrbiterB = ((aOrbiterB + aOrbiterA) + 17882948163883121328U) + aPhaseEOrbiterUpdateSaltB[(((31U - aIndex) + 5U)) & S_SALT1];
            aOrbiterC = (aOrbiterC ^ aOrbiterB) ^ 15029375310296563175U;
            aOrbiterC = RotL64((aOrbiterC * 17021415832288477713U), 41U);
            //
            aOrbiterC = (aOrbiterC + aOrbiterJ) + 10170682648007918739U;
            aOrbiterG = (aOrbiterG ^ aOrbiterC) ^ 11829089574189398773U;
            aOrbiterG = RotL64((aOrbiterG * 15755874363488568849U), 35U);
            //
            aOrbiterK = ((aOrbiterK + aOrbiterI) + 1746524867389196322U) + aPhaseEOrbiterUpdateSaltC[((aIndex + 12U)) & S_SALT1];
            aOrbiterB = ((aOrbiterB ^ aOrbiterK) ^ 10217423427886742775U) ^ aPhaseEOrbiterUpdateSaltF[((aIndex + 19U)) & S_SALT1];
            aOrbiterB = RotL64((aOrbiterB * 9166162099575333519U), 5U);
            //
            aOrbiterG = ((aOrbiterG + aOrbiterK) + 1338457710729082656U) + aPhaseEOrbiterUpdateSaltE[(((31U - aIndex) + 26U)) & S_SALT1];
            aOrbiterI = (aOrbiterI ^ aOrbiterG) ^ 1319981417675542556U;
            aOrbiterI = RotL64((aOrbiterI * 9518448254565489715U), 47U);
            //
            aIngress = aOrbiterK ^ RotL64(aOrbiterC, 35U);
            aIngress = aIngress + (RotL64(aOrbiterA, 3U) ^ aOrbiterB);
            aIngress = aIngress + (aOrbiterJ ^ RotL64(aOrbiterG, 19U));
            aIngress = aIngress + RotL64(aOrbiterI, 41U);
            aIngress = TwistMix64::DiffuseC((aIngress + aScatter));
            //
            aWandererG = aWandererG ^ ((RotL64(aCross, 5U) + aOrbiterA) + RotL64(aOrbiterC, 21U));
            aWandererC = aWandererC + ((((RotL64(aIngress, 41U) + aOrbiterI) + RotL64(aOrbiterA, 30U)) + RotL64(aCarry, 51U)) + aPhaseEWandererUpdateSaltE[((aIndex + 22U)) & S_SALT1]);
            aWandererE = aWandererE ^ ((RotL64(aPrevious, 11U) + aOrbiterB) + RotL64(aOrbiterK, 51U));
            aWandererF = aWandererF + ((((RotL64(aScatter, 24U) + aOrbiterA) + RotL64(aOrbiterB, 43U)) + RotL64(aCarry, 35U)) + aPhaseEWandererUpdateSaltD[((aIndex + 13U)) & S_SALT1]);
            aWandererH = aWandererH ^ ((RotL64(aPrevious, 35U) + RotL64(aOrbiterJ, 37U)) + aOrbiterK);
            aWandererA = aWandererA + ((RotL64(aIngress, 51U) + aOrbiterG) + RotL64(aOrbiterK, 5U));
            aWandererB = aWandererB ^ ((RotL64(aCross, 57U) + RotL64(aOrbiterA, 11U)) + aOrbiterJ);
            //
            aCarry = aCarry + (aWandererH ^ RotL64(aWandererC, 53U));
            aCarry = aCarry + (RotL64(aWandererA, 47U) ^ aWandererE);
            aCarry = aCarry + (aWandererF ^ RotL64(aWandererG, 20U));
            aCarry = aCarry + RotL64(aWandererB, 43U);
            aCarry = aCarry + RotL64(aIngress, 27U);
            aCarry = TwistMix64::DiffuseB(aCarry);
            //
            aOperationLaneC[aIndex] = aIngress;
        }
    
        // twist_loop_b loop 4
        // ingress from: aOperationLaneC, aOperationLaneA, aExpandLaneD, aWorkLaneC
        // ingress directions: aOperationLaneC forward forced, aOperationLaneA forward forced, aExpandLaneD forward forced, aWorkLaneC forward/backward random
        // cross from: aOperationLaneB, aExpandLaneB, aWorkLaneD
        // cross directions: aOperationLaneB backward forced, aExpandLaneB backward forced, aWorkLaneD backward/forward random
        // write to: aOperationLaneD
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aOperationLaneC[((aIndex + 30136U)) & S_BLOCK1], 54U) ^ RotL64(aOperationLaneA[((aIndex + 27334U)) & S_BLOCK1], 23U));
            aIngress ^= (RotL64(aExpandLaneD[((aIndex + 27300U)) & S_BLOCK1], 3U) ^ RotL64(aWorkLaneC[((S_BLOCK1 - aIndex + 30886U)) & S_BLOCK1], 11U));
            aIngress = TwistMix64::DiffuseB(aIngress);
            //
            aCross = (RotL64(aOperationLaneB[((S_BLOCK1 - aIndex + 31804U)) & S_BLOCK1], 27U) ^ RotL64(aExpandLaneB[((S_BLOCK1 - aIndex + 32695U)) & S_BLOCK1], 38U));
            aCross ^= RotL64(aWorkLaneD[((S_BLOCK1 - aIndex + 28467U)) & S_BLOCK1], 3U);
            aCross = TwistMix64::DiffuseA(aCross);
            //
            aScatter = (RotL64(aPrevious, 23U) + RotL64(aCarry, 56U)) ^ (RotL64(aIngress, 37U) + RotL64(aCross, 5U));
            aScatter = TwistMix64::DiffuseA(aScatter);
            //
            aOrbiterA = ((aWandererE + RotL64(aIngress, 41U)) + RotL64(aCarry, 27U)) + 785861751704720606U;
            aOrbiterE = ((aWandererA + RotL64(aPrevious, 19U)) + 15968088718435606299U) + aPhaseEOrbiterAssignSaltA[(((31U - aIndex) + 13U)) & S_SALT1];
            aOrbiterB = ((aWandererI + RotL64(aCross, 51U)) + RotL64(aCarry, 5U)) + 1393976526590347151U;
            aOrbiterG = ((aWandererH + RotL64(aScatter, 11U)) + 17240750947292745884U) + aPhaseEOrbiterAssignSaltF[((aIndex + 4U)) & S_SALT1];
            aOrbiterF = (aWandererD + RotL64(aPrevious, 3U)) + 4921576136163183137U;
            aOrbiterD = ((aWandererF + RotL64(aScatter, 60U)) + RotL64(aCarry, 51U)) + 3334047873553153032U;
            aOrbiterK = (aWandererJ + RotL64(aCross, 35U)) + 15086509978458408698U;
            //
            aOrbiterA = ((aOrbiterA + aOrbiterE) + 892391205397581998U) + aPhaseEOrbiterUpdateSaltB[((aIndex + 9U)) & S_SALT1];
            aOrbiterB = (aOrbiterB ^ aOrbiterA) ^ 2965686403183767521U;
            aOrbiterB = RotL64((aOrbiterB * 709160942482770225U), 41U);
            //
            aOrbiterG = ((aOrbiterG + aOrbiterF) + 14632215393655706170U) + aPhaseEOrbiterUpdateSaltA[(((31U - aIndex) + 7U)) & S_SALT1];
            aOrbiterD = (aOrbiterD ^ aOrbiterG) ^ 15740589515342377322U;
            aOrbiterD = RotL64((aOrbiterD * 15677716942904794913U), 57U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterA) + 11131164813943086445U;
            aOrbiterE = (aOrbiterE ^ aOrbiterD) ^ 6988080581278900960U;
            aOrbiterE = RotL64((aOrbiterE * 6412189142344044255U), 21U);
            //
            aOrbiterK = ((aOrbiterK + aOrbiterG) + 16021254613117657178U) + aPhaseEOrbiterUpdateSaltD[(((31U - aIndex) + 22U)) & S_SALT1];
            aOrbiterF = (aOrbiterF ^ aOrbiterK) ^ 6183615599897921154U;
            aOrbiterF = RotL64((aOrbiterF * 9976411093264211033U), 11U);
            //
            aOrbiterE = (aOrbiterE + aOrbiterB) + 12533992547026652747U;
            aOrbiterK = (aOrbiterK ^ aOrbiterE) ^ 3104325358982904219U;
            aOrbiterK = RotL64((aOrbiterK * 14977348108778147265U), 47U);
            //
            aOrbiterB = (aOrbiterB + aOrbiterK) + 3878525937957474644U;
            aOrbiterG = (aOrbiterG ^ aOrbiterB) ^ 2120435259884368445U;
            aOrbiterG = RotL64((aOrbiterG * 15964718652193073177U), 5U);
            //
            aOrbiterF = ((aOrbiterF + aOrbiterD) + 14928658302694194856U) + aPhaseEOrbiterUpdateSaltE[(((31U - aIndex) + 3U)) & S_SALT1];
            aOrbiterA = (aOrbiterA ^ aOrbiterF) ^ 9121310461310309348U;
            aOrbiterA = RotL64((aOrbiterA * 17304439784647477491U), 29U);
            //
            aIngress = RotL64(aOrbiterG, 13U) ^ aOrbiterF;
            aIngress = aIngress + (RotL64(aOrbiterD, 29U) ^ aOrbiterB);
            aIngress = aIngress + (RotL64(aOrbiterE, 23U) ^ aOrbiterA);
            aIngress = aIngress + RotL64(aOrbiterK, 43U);
            aIngress = TwistMix64::DiffuseA((aIngress + aScatter));
            //
            aWandererH = aWandererH + (((RotL64(aCross, 29U) + RotL64(aOrbiterA, 21U)) + aOrbiterE) + RotL64(aCarry, 29U));
            aWandererJ = aWandererJ ^ ((RotL64(aScatter, 37U) + aOrbiterK) + RotL64(aOrbiterB, 35U));
            aWandererE = aWandererE + (((RotL64(aPrevious, 19U) + RotL64(aOrbiterB, 3U)) + aOrbiterE) + RotL64(aCarry, 3U));
            aWandererF = aWandererF ^ (((RotL64(aIngress, 13U) + aOrbiterD) + RotL64(aOrbiterF, 11U)) + aPhaseEWandererUpdateSaltF[((aIndex + 28U)) & S_SALT1]);
            aWandererI = aWandererI + ((RotL64(aScatter, 43U) + aOrbiterK) + RotL64(aOrbiterG, 48U));
            aWandererD = aWandererD ^ (((RotL64(aIngress, 6U) + aOrbiterF) + RotL64(aOrbiterA, 41U)) + aPhaseEWandererUpdateSaltC[(((31U - aIndex) + 6U)) & S_SALT1]);
            aWandererA = aWandererA + ((RotL64(aPrevious, 53U) + aOrbiterF) + RotL64(aOrbiterK, 29U));
            //
            aCarry = aCarry + (RotL64(aWandererA, 34U) ^ aWandererF);
            aCarry = aCarry + (aWandererD ^ RotL64(aWandererH, 41U));
            aCarry = aCarry + (RotL64(aWandererI, 57U) ^ aWandererJ);
            aCarry = aCarry + RotL64(aWandererE, 3U);
            aCarry = aCarry + RotL64(aIngress, 47U);
            aCarry = TwistMix64::DiffuseB(aCarry);
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

void TwistExpander_Greezy_Arx::Twist_C(TwistWorkSpace *pWorkSpace,
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
    [[maybe_unused]] std::uint8_t *aFireLaneA = pWorkSpace->mFireLaneA;
    [[maybe_unused]] std::uint8_t *aFireLaneB = pWorkSpace->mFireLaneB;
    [[maybe_unused]] std::uint8_t *aFireLaneC = pWorkSpace->mFireLaneC;
    [[maybe_unused]] std::uint8_t *aFireLaneD = pWorkSpace->mFireLaneD;
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
        // read from: aOperationLaneA, aOperationLaneB, aFireLaneA, aOperationLaneC, aOperationLaneD, aFireLaneB, aWorkLaneA, aFireLaneC, aFireLaneD, aWorkLaneB, aExpandLaneA, aExpandLaneB, aWorkLaneC, aExpandLaneC, aExpandLaneD
        // write to: aWorkLaneA, aWorkLaneB, aWorkLaneC, aWorkLaneD
    
        // twist_loop_c loop 1
        // ingress from: aOperationLaneA, aOperationLaneB, aFireLaneA
        // ingress directions: aOperationLaneA forward forced, aOperationLaneB forward forced, aFireLaneA forward/backward random
        // cross from: aOperationLaneC, aOperationLaneD, aFireLaneB
        // cross directions: aOperationLaneC backward forced, aOperationLaneD backward forced, aFireLaneB backward/forward random
        // write to: aWorkLaneA
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aOperationLaneA[((aIndex + 2581U)) & S_BLOCK1], 29U) ^ RotL64(aOperationLaneB[((aIndex + 1703U)) & S_BLOCK1], 48U));
            aIngress ^= RotL64(aFireLaneA[((S_BLOCK1 - aIndex + 6690U)) & S_BLOCK1], 39U);
            aIngress = TwistMix64::DiffuseC(aIngress);
            //
            aCross = (RotL64(aOperationLaneC[((S_BLOCK1 - aIndex + 4426U)) & S_BLOCK1], 41U) ^ RotL64(aOperationLaneD[((S_BLOCK1 - aIndex + 7877U)) & S_BLOCK1], 6U));
            aCross ^= RotL64(aFireLaneB[((aIndex + 1171U)) & S_BLOCK1], 57U);
            aCross = TwistMix64::DiffuseA(aCross);
            //
            aScatter = (RotL64(aCross, 20U) ^ RotL64(aIngress, 47U)) + (RotL64(aCarry, 35U) + RotL64(aPrevious, 5U));
            aScatter = TwistMix64::DiffuseA(aScatter);
            //
            aOrbiterD = ((aWandererE + RotL64(aIngress, 41U)) + 6342299552323486695U) + aPhaseFOrbiterAssignSaltD[((aIndex + 24U)) & S_SALT1];
            aOrbiterE = ((aWandererD + RotL64(aScatter, 23U)) + RotL64(aCarry, 5U)) + 12692748514781367538U;
            aOrbiterI = ((aWandererI + RotL64(aPrevious, 50U)) + 8202639945493229155U) + aPhaseFOrbiterAssignSaltC[((aIndex + 26U)) & S_SALT1];
            aOrbiterG = (aWandererH + RotL64(aCross, 19U)) + 4439975701793231639U;
            aOrbiterA = (aWandererB + RotL64(aPrevious, 47U)) + 16774235182859553759U;
            aOrbiterB = (aWandererK + RotL64(aIngress, 13U)) + 8764155413335405667U;
            aOrbiterC = (aWandererC + RotL64(aScatter, 5U)) + 7167848811974967685U;
            aOrbiterK = ((aWandererF + RotL64(aCross, 11U)) + RotL64(aCarry, 19U)) + 16768278912125334220U;
            aOrbiterH = ((aWandererJ + RotL64(aPrevious, 28U)) + RotL64(aCarry, 27U)) + 9090838954826296201U;
            aOrbiterF = (aWandererA + RotL64(aCross, 57U)) + 7644075729758006298U;
            aOrbiterJ = (aWandererG + RotL64(aIngress, 3U)) + 17326182797908071215U;
            //
            aOrbiterD = (aOrbiterD + aOrbiterE) + 16158809721888137555U;
            aOrbiterI = ((aOrbiterI ^ aOrbiterD) ^ 8029938783858263694U) ^ aPhaseFOrbiterUpdateSaltB[(((31U - aIndex) + 29U)) & S_SALT1];
            aOrbiterI = RotL64((aOrbiterI * 12628072435324195483U), 39U);
            //
            aOrbiterG = ((aOrbiterG + aOrbiterA) + 8716553521415553404U) + aPhaseFOrbiterUpdateSaltD[((aIndex + 11U)) & S_SALT1];
            aOrbiterD = (aOrbiterD ^ aOrbiterG) ^ 7012599977009208840U;
            aOrbiterD = RotL64((aOrbiterD * 8775355876188948851U), 41U);
            //
            aOrbiterB = (aOrbiterB + aOrbiterI) + 13250558696578541499U;
            aOrbiterG = (aOrbiterG ^ aOrbiterB) ^ 13705957059101025396U;
            aOrbiterG = RotL64((aOrbiterG * 16889495686487056367U), 53U);
            //
            aOrbiterC = (aOrbiterC + aOrbiterK) + 2796775206291902461U;
            aOrbiterH = (aOrbiterH ^ aOrbiterC) ^ 13741676263512390669U;
            aOrbiterH = RotL64((aOrbiterH * 10455782033465595947U), 29U);
            //
            aOrbiterH = (aOrbiterH + aOrbiterF) + 1691908360612389252U;
            aOrbiterJ = (aOrbiterJ ^ aOrbiterH) ^ 4114939415206031540U;
            aOrbiterJ = RotL64((aOrbiterJ * 2797401802892718297U), 43U);
            //
            aOrbiterK = (aOrbiterK + aOrbiterG) + 2374911514440738727U;
            aOrbiterF = (aOrbiterF ^ aOrbiterK) ^ 12377616933668803091U;
            aOrbiterF = RotL64((aOrbiterF * 2505164835116651215U), 35U);
            //
            aOrbiterI = ((aOrbiterI + aOrbiterC) + 681094033415259645U) + aPhaseFOrbiterUpdateSaltA[((aIndex + 28U)) & S_SALT1];
            aOrbiterA = (aOrbiterA ^ aOrbiterI) ^ 13841322124900463362U;
            aOrbiterA = RotL64((aOrbiterA * 4210414203856902329U), 23U);
            //
            aOrbiterF = (aOrbiterF + aOrbiterD) + 18082983557580381338U;
            aOrbiterB = (aOrbiterB ^ aOrbiterF) ^ 15731122225678626778U;
            aOrbiterB = RotL64((aOrbiterB * 7785999919955613789U), 3U);
            //
            aOrbiterJ = ((aOrbiterJ + aOrbiterB) + 2084336993254383330U) + aPhaseFOrbiterUpdateSaltC[(((31U - aIndex) + 17U)) & S_SALT1];
            aOrbiterK = (aOrbiterK ^ aOrbiterJ) ^ 3600882019682875370U;
            aOrbiterK = RotL64((aOrbiterK * 2977569829649654329U), 27U);
            //
            aOrbiterE = (aOrbiterE + aOrbiterJ) + 11436602278656592334U;
            aOrbiterC = (aOrbiterC ^ aOrbiterE) ^ 5775886971784627864U;
            aOrbiterC = RotL64((aOrbiterC * 6765942246225582787U), 13U);
            //
            aOrbiterA = (aOrbiterA + aOrbiterH) + 17120308925134658794U;
            aOrbiterE = (aOrbiterE ^ aOrbiterA) ^ 6342299552323486695U;
            aOrbiterE = RotL64((aOrbiterE * 5788669985396507227U), 21U);
            //
            aIngress = RotL64(aOrbiterH, 3U) ^ aOrbiterA;
            aIngress = aIngress + (RotL64(aOrbiterC, 21U) ^ aOrbiterI);
            aIngress = aIngress + (aOrbiterD ^ RotL64(aOrbiterJ, 57U));
            aIngress = aIngress + (RotL64(aOrbiterF, 5U) ^ aOrbiterG);
            aIngress = aIngress + (RotL64(aOrbiterE, 54U) ^ aOrbiterB);
            aIngress = aIngress + RotL64(aOrbiterK, 23U);
            aIngress = TwistMix64::DiffuseA((aIngress + aScatter));
            //
            aWandererH = aWandererH + ((RotL64(aCross, 23U) + aOrbiterF) + RotL64(aOrbiterH, 51U));
            aWandererE = aWandererE ^ ((RotL64(aScatter, 54U) + RotL64(aOrbiterA, 26U)) + aOrbiterJ);
            aWandererK = aWandererK + ((RotL64(aIngress, 39U) + aOrbiterC) + RotL64(aOrbiterJ, 41U));
            aWandererI = aWandererI ^ ((RotL64(aPrevious, 19U) + aOrbiterH) + RotL64(aOrbiterK, 53U));
            aWandererG = aWandererG + (((RotL64(aScatter, 41U) + aOrbiterB) + RotL64(aOrbiterC, 47U)) + aPhaseFWandererUpdateSaltC[((aIndex + 25U)) & S_SALT1]);
            aWandererJ = aWandererJ ^ ((RotL64(aCross, 35U) + RotL64(aOrbiterK, 44U)) + aOrbiterE);
            aWandererF = aWandererF + ((RotL64(aIngress, 3U) + RotL64(aOrbiterJ, 57U)) + aOrbiterB);
            aWandererB = aWandererB ^ ((RotL64(aPrevious, 11U) + RotL64(aOrbiterH, 35U)) + aOrbiterG);
            aWandererD = aWandererD + ((((RotL64(aCross, 52U) + RotL64(aOrbiterK, 3U)) + aOrbiterI) + RotL64(aCarry, 11U)) + aPhaseFWandererUpdateSaltF[(((31U - aIndex) + 3U)) & S_SALT1]);
            aWandererC = aWandererC ^ ((RotL64(aPrevious, 13U) + RotL64(aOrbiterE, 19U)) + aOrbiterG);
            aWandererA = aWandererA + (((RotL64(aScatter, 21U) + aOrbiterH) + RotL64(aOrbiterD, 21U)) + RotL64(aCarry, 19U));
            //
            aCarry = aCarry + (aWandererG ^ RotL64(aWandererD, 3U));
            aCarry = aCarry + (RotL64(aWandererF, 5U) ^ aWandererK);
            aCarry = aCarry + (RotL64(aWandererI, 46U) ^ aWandererH);
            aCarry = aCarry + (RotL64(aWandererC, 35U) ^ aWandererJ);
            aCarry = aCarry + (RotL64(aWandererE, 23U) ^ aWandererA);
            aCarry = aCarry + RotL64(aWandererB, 53U);
            aCarry = aCarry + RotL64(aIngress, 28U);
            aCarry = TwistMix64::DiffuseC(aCarry);
            //
            aWorkLaneA[aIndex] = aIngress;
        }
    
        // twist_loop_c loop 2
        // ingress from: aWorkLaneA, aOperationLaneC, aOperationLaneD, aFireLaneC
        // ingress directions: aWorkLaneA forward forced, aOperationLaneC forward forced, aOperationLaneD forward forced, aFireLaneC forward/backward random
        // cross from: aOperationLaneA, aOperationLaneB, aFireLaneD
        // cross directions: aOperationLaneA backward forced, aOperationLaneB backward forced, aFireLaneD backward/forward random
        // write to: aWorkLaneB
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aWorkLaneA[((aIndex + 11018U)) & S_BLOCK1], 34U) ^ RotL64(aOperationLaneC[((aIndex + 14810U)) & S_BLOCK1], 47U));
            aIngress ^= (RotL64(aOperationLaneD[((aIndex + 13319U)) & S_BLOCK1], 5U) ^ RotL64(aFireLaneC[((S_BLOCK1 - aIndex + 8453U)) & S_BLOCK1], 57U));
            aIngress = TwistMix64::DiffuseA(aIngress);
            //
            aCross = (RotL64(aOperationLaneA[((S_BLOCK1 - aIndex + 11286U)) & S_BLOCK1], 34U) ^ RotL64(aOperationLaneB[((S_BLOCK1 - aIndex + 14975U)) & S_BLOCK1], 43U));
            aCross ^= RotL64(aFireLaneD[((S_BLOCK1 - aIndex + 14713U)) & S_BLOCK1], 19U);
            aCross = TwistMix64::DiffuseA(aCross);
            //
            aScatter = (RotL64(aCarry, 13U) + RotL64(aIngress, 27U)) ^ (RotL64(aPrevious, 54U) ^ RotL64(aCross, 39U));
            aScatter = TwistMix64::DiffuseB(aScatter);
            //
            aOrbiterK = (aWandererD + RotL64(aCross, 41U)) + 5131645209694953015U;
            aOrbiterJ = ((aWandererC + RotL64(aScatter, 46U)) + RotL64(aCarry, 27U)) + 12070391048835379854U;
            aOrbiterA = (aWandererI + RotL64(aPrevious, 39U)) + 2604295836242338724U;
            aOrbiterH = ((aWandererK + RotL64(aIngress, 19U)) + 14042039029284001596U) + aPhaseFOrbiterAssignSaltB[((aIndex + 25U)) & S_SALT1];
            aOrbiterB = (aWandererJ + RotL64(aScatter, 57U)) + 8914654543854559327U;
            aOrbiterI = (aWandererB + RotL64(aIngress, 13U)) + 2185619407969359869U;
            aOrbiterG = ((aWandererH + RotL64(aPrevious, 51U)) + 5187406295103352574U) + aPhaseFOrbiterAssignSaltA[(((31U - aIndex) + 14U)) & S_SALT1];
            aOrbiterC = ((aWandererG + RotL64(aCross, 3U)) + RotL64(aCarry, 13U)) + 8022832481290871217U;
            aOrbiterD = (aWandererF + RotL64(aPrevious, 60U)) + 8783061916740573472U;
            aOrbiterF = ((aWandererE + RotL64(aIngress, 37U)) + RotL64(aCarry, 53U)) + 10711028365596196301U;
            aOrbiterE = (aWandererA + RotL64(aCross, 5U)) + 13387065038269133571U;
            //
            aOrbiterK = (aOrbiterK + aOrbiterJ) + 11187001318931801582U;
            aOrbiterA = (aOrbiterA ^ aOrbiterK) ^ 14191473173276034019U;
            aOrbiterA = RotL64((aOrbiterA * 2491253922434756431U), 37U);
            //
            aOrbiterH = (aOrbiterH + aOrbiterK) + 16207761776716426435U;
            aOrbiterB = (aOrbiterB ^ aOrbiterH) ^ 9677408414452078760U;
            aOrbiterB = RotL64((aOrbiterB * 5487303383095129949U), 21U);
            //
            aOrbiterJ = (aOrbiterJ + aOrbiterI) + 17812460332794370649U;
            aOrbiterG = (aOrbiterG ^ aOrbiterJ) ^ 7736423148554132028U;
            aOrbiterG = RotL64((aOrbiterG * 15588733747232852555U), 47U);
            //
            aOrbiterC = (aOrbiterC + aOrbiterD) + 17293203944059014763U;
            aOrbiterK = (aOrbiterK ^ aOrbiterC) ^ 13487243633338010243U;
            aOrbiterK = RotL64((aOrbiterK * 9468688858740539095U), 57U);
            //
            aOrbiterF = (aOrbiterF + aOrbiterH) + 15979293016815060755U;
            aOrbiterI = (aOrbiterI ^ aOrbiterF) ^ 17645215484691359547U;
            aOrbiterI = RotL64((aOrbiterI * 1449450767288733995U), 39U);
            //
            aOrbiterA = ((aOrbiterA + aOrbiterG) + 11635961468586927692U) + aPhaseFOrbiterUpdateSaltF[(((31U - aIndex) + 21U)) & S_SALT1];
            aOrbiterD = (aOrbiterD ^ aOrbiterA) ^ 10530136578329059784U;
            aOrbiterD = RotL64((aOrbiterD * 8785021493374398437U), 19U);
            //
            aOrbiterE = (aOrbiterE + aOrbiterC) + 4900370530116992731U;
            aOrbiterH = (aOrbiterH ^ aOrbiterE) ^ 15952900504821599445U;
            aOrbiterH = RotL64((aOrbiterH * 5413316082800365261U), 23U);
            //
            aOrbiterB = (aOrbiterB + aOrbiterA) + 9938000151832814778U;
            aOrbiterC = (aOrbiterC ^ aOrbiterB) ^ 14170277411106520726U;
            aOrbiterC = RotL64((aOrbiterC * 5058343552974910737U), 11U);
            //
            aOrbiterI = (aOrbiterI + aOrbiterB) + 14091010427448547620U;
            aOrbiterE = (aOrbiterE ^ aOrbiterI) ^ 13658560822164111421U;
            aOrbiterE = RotL64((aOrbiterE * 9523184040517290629U), 53U);
            //
            aOrbiterG = ((aOrbiterG + aOrbiterE) + 13954269172267844623U) + aPhaseFOrbiterUpdateSaltB[((aIndex + 29U)) & S_SALT1];
            aOrbiterF = ((aOrbiterF ^ aOrbiterG) ^ 3921811946419945868U) ^ aPhaseFOrbiterUpdateSaltA[((aIndex + 3U)) & S_SALT1];
            aOrbiterF = RotL64((aOrbiterF * 6839440867046147039U), 3U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterF) + 14296483810577739898U;
            aOrbiterJ = ((aOrbiterJ ^ aOrbiterD) ^ 5131645209694953015U) ^ aPhaseFOrbiterUpdateSaltE[(((31U - aIndex) + 26U)) & S_SALT1];
            aOrbiterJ = RotL64((aOrbiterJ * 10190969526209064367U), 29U);
            //
            aIngress = aOrbiterB ^ RotL64(aOrbiterD, 51U);
            aIngress = aIngress + (RotL64(aOrbiterH, 10U) ^ aOrbiterG);
            aIngress = aIngress + (aOrbiterC ^ RotL64(aOrbiterI, 29U));
            aIngress = aIngress + (RotL64(aOrbiterE, 19U) ^ aOrbiterK);
            aIngress = aIngress + (RotL64(aOrbiterA, 5U) ^ aOrbiterJ);
            aIngress = aIngress + RotL64(aOrbiterF, 13U);
            aIngress = TwistMix64::DiffuseB((aIngress + aScatter));
            //
            aWandererE = aWandererE ^ ((RotL64(aScatter, 52U) + aOrbiterI) + RotL64(aOrbiterK, 34U));
            aWandererD = aWandererD + ((RotL64(aPrevious, 43U) + aOrbiterF) + RotL64(aOrbiterJ, 13U));
            aWandererI = aWandererI ^ ((RotL64(aCross, 39U) + RotL64(aOrbiterJ, 41U)) + aOrbiterK);
            aWandererJ = aWandererJ + ((RotL64(aIngress, 13U) + aOrbiterG) + RotL64(aOrbiterE, 47U));
            aWandererA = aWandererA ^ ((RotL64(aPrevious, 57U) + RotL64(aOrbiterD, 19U)) + aOrbiterJ);
            aWandererF = aWandererF + (((RotL64(aScatter, 5U) + RotL64(aOrbiterC, 43U)) + aOrbiterK) + RotL64(aCarry, 27U));
            aWandererK = aWandererK ^ ((RotL64(aIngress, 3U) + RotL64(aOrbiterI, 23U)) + aOrbiterE);
            aWandererH = aWandererH + ((((RotL64(aCross, 30U) + aOrbiterI) + RotL64(aOrbiterJ, 11U)) + RotL64(aCarry, 13U)) + aPhaseFWandererUpdateSaltB[(((31U - aIndex) + 13U)) & S_SALT1]);
            aWandererC = aWandererC ^ ((RotL64(aScatter, 27U) + aOrbiterJ) + RotL64(aOrbiterA, 29U));
            aWandererG = aWandererG + (((RotL64(aIngress, 35U) + RotL64(aOrbiterI, 37U)) + aOrbiterH) + aPhaseFWandererUpdateSaltA[((aIndex + 8U)) & S_SALT1]);
            aWandererB = aWandererB ^ ((RotL64(aPrevious, 37U) + aOrbiterB) + RotL64(aOrbiterK, 6U));
            //
            aCarry = aCarry + (RotL64(aWandererA, 41U) ^ aWandererE);
            aCarry = aCarry + (aWandererI ^ RotL64(aWandererC, 23U));
            aCarry = aCarry + (RotL64(aWandererG, 38U) ^ aWandererD);
            aCarry = aCarry + (RotL64(aWandererJ, 43U) ^ aWandererB);
            aCarry = aCarry + (RotL64(aWandererF, 19U) ^ aWandererH);
            aCarry = aCarry + RotL64(aWandererK, 53U);
            aCarry = aCarry + RotL64(aIngress, 50U);
            aCarry = TwistMix64::DiffuseC(aCarry);
            //
            aWorkLaneB[S_BLOCK1 - aIndex] = aIngress;
        }
    
        // twist_loop_c loop 3
        // ingress from: aWorkLaneB, aOperationLaneA, aOperationLaneB, aExpandLaneA
        // ingress directions: aWorkLaneB forward forced, aOperationLaneA forward forced, aOperationLaneB forward forced, aExpandLaneA forward/backward random
        // cross from: aWorkLaneA, aOperationLaneC, aExpandLaneB
        // cross directions: aWorkLaneA backward forced, aOperationLaneC backward forced, aExpandLaneB backward/forward random
        // write to: aWorkLaneC
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aWorkLaneB[((aIndex + 19302U)) & S_BLOCK1], 54U) ^ RotL64(aOperationLaneA[((aIndex + 21385U)) & S_BLOCK1], 41U));
            aIngress ^= (RotL64(aOperationLaneB[((aIndex + 24172U)) & S_BLOCK1], 5U) ^ RotL64(aExpandLaneA[((aIndex + 23312U)) & S_BLOCK1], 13U));
            aIngress = TwistMix64::DiffuseA(aIngress);
            //
            aCross = (RotL64(aWorkLaneA[((S_BLOCK1 - aIndex + 18612U)) & S_BLOCK1], 27U) ^ RotL64(aOperationLaneC[((S_BLOCK1 - aIndex + 21916U)) & S_BLOCK1], 58U));
            aCross ^= RotL64(aExpandLaneB[((S_BLOCK1 - aIndex + 18299U)) & S_BLOCK1], 47U);
            aCross = TwistMix64::DiffuseB(aCross);
            //
            aScatter = (RotL64(aCross, 53U) ^ RotL64(aPrevious, 22U)) ^ (RotL64(aIngress, 41U) + RotL64(aCarry, 3U));
            aScatter = TwistMix64::DiffuseA(aScatter);
            //
            aOrbiterH = (aWandererF + RotL64(aScatter, 37U)) + 8767379393098711499U;
            aOrbiterI = (aWandererC + RotL64(aCross, 51U)) + 7168159491580816433U;
            aOrbiterG = (((aWandererK + RotL64(aIngress, 11U)) + RotL64(aCarry, 53U)) + 9879279829061883406U) + aPhaseFOrbiterAssignSaltF[(((31U - aIndex) + 13U)) & S_SALT1];
            aOrbiterE = (aWandererA + RotL64(aPrevious, 40U)) + 10537167136053399303U;
            aOrbiterJ = ((aWandererG + RotL64(aScatter, 53U)) + RotL64(aCarry, 47U)) + 2839070018069188936U;
            aOrbiterD = ((aWandererJ + RotL64(aCross, 57U)) + 13844278063968429732U) + aPhaseFOrbiterAssignSaltE[((aIndex + 9U)) & S_SALT1];
            aOrbiterC = (aWandererI + RotL64(aIngress, 13U)) + 11278946626186474646U;
            aOrbiterK = ((aWandererB + RotL64(aPrevious, 3U)) + RotL64(aCarry, 11U)) + 11798425216660557799U;
            aOrbiterF = (aWandererD + RotL64(aIngress, 43U)) + 7618446090703335192U;
            aOrbiterB = (aWandererE + RotL64(aPrevious, 26U)) + 695423597006983660U;
            aOrbiterA = (aWandererH + RotL64(aScatter, 5U)) + 14344728202803488813U;
            //
            aOrbiterH = (aOrbiterH + aOrbiterI) + 11656100506575697086U;
            aOrbiterG = (aOrbiterG ^ aOrbiterH) ^ 10384358779985773937U;
            aOrbiterG = RotL64((aOrbiterG * 247494692039140973U), 41U);
            //
            aOrbiterE = (aOrbiterE + aOrbiterH) + 17585001605131977341U;
            aOrbiterJ = (aOrbiterJ ^ aOrbiterE) ^ 9964478171465522911U;
            aOrbiterJ = RotL64((aOrbiterJ * 13484044854790175315U), 3U);
            //
            aOrbiterI = (aOrbiterI + aOrbiterD) + 2710943171829692624U;
            aOrbiterC = ((aOrbiterC ^ aOrbiterI) ^ 17809072853457153057U) ^ aPhaseFOrbiterUpdateSaltC[((aIndex + 18U)) & S_SALT1];
            aOrbiterC = RotL64((aOrbiterC * 16341884203303271365U), 53U);
            //
            aOrbiterK = (aOrbiterK + aOrbiterE) + 12814092033910687774U;
            aOrbiterF = (aOrbiterF ^ aOrbiterK) ^ 1743186323268668740U;
            aOrbiterF = RotL64((aOrbiterF * 11150822630624332557U), 43U);
            //
            aOrbiterD = ((aOrbiterD + aOrbiterB) + 10750472346626754704U) + aPhaseFOrbiterUpdateSaltB[(((31U - aIndex) + 27U)) & S_SALT1];
            aOrbiterK = (aOrbiterK ^ aOrbiterD) ^ 15925901217078035356U;
            aOrbiterK = RotL64((aOrbiterK * 9276504171291801637U), 11U);
            //
            aOrbiterJ = (aOrbiterJ + aOrbiterG) + 2569102106359362359U;
            aOrbiterD = (aOrbiterD ^ aOrbiterJ) ^ 8868261301410769739U;
            aOrbiterD = RotL64((aOrbiterD * 3662495603133918101U), 13U);
            //
            aOrbiterF = ((aOrbiterF + aOrbiterJ) + 2143691008373582476U) + aPhaseFOrbiterUpdateSaltF[(((31U - aIndex) + 21U)) & S_SALT1];
            aOrbiterI = (aOrbiterI ^ aOrbiterF) ^ 10606616796243205921U;
            aOrbiterI = RotL64((aOrbiterI * 15794414817813485643U), 27U);
            //
            aOrbiterA = (aOrbiterA + aOrbiterF) + 16258070651850746855U;
            aOrbiterH = (aOrbiterH ^ aOrbiterA) ^ 11720192793689633315U;
            aOrbiterH = RotL64((aOrbiterH * 14475623219460678021U), 5U);
            //
            aOrbiterB = ((aOrbiterB + aOrbiterA) + 8230871037292355675U) + aPhaseFOrbiterUpdateSaltA[((aIndex + 3U)) & S_SALT1];
            aOrbiterE = (aOrbiterE ^ aOrbiterB) ^ 16898650748046368353U;
            aOrbiterE = RotL64((aOrbiterE * 7368697435476300255U), 51U);
            //
            aOrbiterG = (aOrbiterG + aOrbiterC) + 9071122174426904737U;
            aOrbiterB = (aOrbiterB ^ aOrbiterG) ^ 4506737259011736474U;
            aOrbiterB = RotL64((aOrbiterB * 11903039808814842447U), 35U);
            //
            aOrbiterC = (aOrbiterC + aOrbiterK) + 4545409671845718259U;
            aOrbiterA = (aOrbiterA ^ aOrbiterC) ^ 8767379393098711499U;
            aOrbiterA = RotL64((aOrbiterA * 1210632171306946669U), 37U);
            //
            aIngress = aOrbiterI ^ RotL64(aOrbiterK, 41U);
            aIngress = aIngress + (aOrbiterB ^ RotL64(aOrbiterG, 39U));
            aIngress = aIngress + (RotL64(aOrbiterE, 58U) ^ aOrbiterC);
            aIngress = aIngress + (aOrbiterH ^ RotL64(aOrbiterF, 11U));
            aIngress = aIngress + (RotL64(aOrbiterJ, 37U) ^ aOrbiterD);
            aIngress = aIngress + RotL64(aOrbiterA, 27U);
            aIngress = TwistMix64::DiffuseB((aIngress + aScatter));
            //
            aWandererA = aWandererA + (((RotL64(aScatter, 27U) + aOrbiterJ) + RotL64(aOrbiterE, 53U)) + aPhaseFWandererUpdateSaltE[(((31U - aIndex) + 26U)) & S_SALT1]);
            aWandererB = aWandererB ^ ((RotL64(aPrevious, 46U) + RotL64(aOrbiterF, 58U)) + aOrbiterD);
            aWandererF = aWandererF + (((RotL64(aCross, 21U) + RotL64(aOrbiterK, 13U)) + aOrbiterH) + RotL64(aCarry, 5U));
            aWandererK = aWandererK ^ ((RotL64(aIngress, 53U) + RotL64(aOrbiterK, 35U)) + aOrbiterC);
            aWandererJ = aWandererJ + ((RotL64(aPrevious, 23U) + RotL64(aOrbiterB, 41U)) + aOrbiterF);
            aWandererE = aWandererE ^ ((RotL64(aCross, 56U) + aOrbiterI) + RotL64(aOrbiterH, 60U));
            aWandererG = aWandererG + (((RotL64(aScatter, 35U) + aOrbiterD) + RotL64(aOrbiterK, 37U)) + RotL64(aCarry, 53U));
            aWandererD = aWandererD ^ ((RotL64(aIngress, 41U) + aOrbiterB) + RotL64(aOrbiterA, 47U));
            aWandererI = aWandererI + (((RotL64(aCross, 51U) + RotL64(aOrbiterK, 43U)) + aOrbiterG) + aPhaseFWandererUpdateSaltD[(((31U - aIndex) + 4U)) & S_SALT1]);
            aWandererH = aWandererH ^ ((RotL64(aPrevious, 37U) + RotL64(aOrbiterH, 5U)) + aOrbiterG);
            aWandererC = aWandererC + ((RotL64(aScatter, 19U) + RotL64(aOrbiterE, 23U)) + aOrbiterG);
            //
            aCarry = aCarry + (RotL64(aWandererG, 51U) ^ aWandererF);
            aCarry = aCarry + (RotL64(aWandererK, 23U) ^ aWandererA);
            aCarry = aCarry + (aWandererB ^ RotL64(aWandererE, 60U));
            aCarry = aCarry + (aWandererC ^ RotL64(aWandererI, 35U));
            aCarry = aCarry + (aWandererD ^ RotL64(aWandererH, 27U));
            aCarry = aCarry + RotL64(aWandererJ, 47U);
            aCarry = aCarry + RotL64(aIngress, 58U);
            aCarry = TwistMix64::DiffuseA(aCarry);
            //
            aWorkLaneC[aIndex] = aIngress;
        }
    
        // twist_loop_c loop 4
        // ingress from: aWorkLaneC, aWorkLaneA, aOperationLaneD, aExpandLaneC
        // ingress directions: aWorkLaneC forward forced, aWorkLaneA forward forced, aOperationLaneD forward forced, aExpandLaneC forward/backward random
        // cross from: aWorkLaneB, aOperationLaneB, aExpandLaneD
        // cross directions: aWorkLaneB backward forced, aOperationLaneB backward forced, aExpandLaneD backward/forward random
        // write to: aWorkLaneD
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aWorkLaneC[((aIndex + 28104U)) & S_BLOCK1], 28U) ^ RotL64(aWorkLaneA[((aIndex + 31323U)) & S_BLOCK1], 43U));
            aIngress ^= (RotL64(aOperationLaneD[((aIndex + 30664U)) & S_BLOCK1], 53U) ^ RotL64(aExpandLaneC[((S_BLOCK1 - aIndex + 26934U)) & S_BLOCK1], 3U));
            aIngress = TwistMix64::DiffuseC(aIngress);
            //
            aCross = (RotL64(aWorkLaneB[((S_BLOCK1 - aIndex + 29599U)) & S_BLOCK1], 23U) ^ RotL64(aOperationLaneB[((S_BLOCK1 - aIndex + 31557U)) & S_BLOCK1], 43U));
            aCross ^= RotL64(aExpandLaneD[((S_BLOCK1 - aIndex + 32523U)) & S_BLOCK1], 60U);
            aCross = TwistMix64::DiffuseA(aCross);
            //
            aScatter = (RotL64(aIngress, 11U) ^ RotL64(aCarry, 27U)) + (RotL64(aPrevious, 60U) ^ RotL64(aCross, 41U));
            aScatter = TwistMix64::DiffuseA(aScatter);
            //
            aOrbiterC = (aWandererE + RotL64(aPrevious, 44U)) + 10336802574069791273U;
            aOrbiterF = (((aWandererF + RotL64(aScatter, 19U)) + RotL64(aCarry, 51U)) + 169025388197058936U) + aPhaseFOrbiterAssignSaltD[(((31U - aIndex) + 25U)) & S_SALT1];
            aOrbiterI = (aWandererI + RotL64(aCross, 11U)) + 6541354188379168846U;
            aOrbiterE = ((aWandererH + RotL64(aIngress, 21U)) + RotL64(aCarry, 19U)) + 16223920526599306104U;
            aOrbiterJ = ((aWandererA + RotL64(aCross, 37U)) + RotL64(aCarry, 37U)) + 12756613707692514808U;
            aOrbiterD = (aWandererK + RotL64(aScatter, 53U)) + 5082475548176484035U;
            aOrbiterB = ((aWandererJ + RotL64(aPrevious, 5U)) + 4907435526952698526U) + aPhaseFOrbiterAssignSaltC[((aIndex + 7U)) & S_SALT1];
            aOrbiterG = (aWandererC + RotL64(aIngress, 51U)) + 14236627073831834337U;
            aOrbiterH = (aWandererD + RotL64(aPrevious, 39U)) + 11502511046130497584U;
            aOrbiterA = (aWandererG + RotL64(aScatter, 34U)) + 3679044835550219497U;
            aOrbiterK = (aWandererB + RotL64(aCross, 27U)) + 11254838916686736746U;
            //
            aOrbiterC = (aOrbiterC + aOrbiterF) + 10582608424233200966U;
            aOrbiterI = (aOrbiterI ^ aOrbiterC) ^ 10449735026385340313U;
            aOrbiterI = RotL64((aOrbiterI * 7363770199734997411U), 39U);
            //
            aOrbiterE = (aOrbiterE + aOrbiterC) + 4628253464169957835U;
            aOrbiterJ = (aOrbiterJ ^ aOrbiterE) ^ 17664454668473204465U;
            aOrbiterJ = RotL64((aOrbiterJ * 4234720298731378527U), 23U);
            //
            aOrbiterF = (aOrbiterF + aOrbiterJ) + 3798386391743884889U;
            aOrbiterD = ((aOrbiterD ^ aOrbiterF) ^ 1379331161819246587U) ^ aPhaseFOrbiterUpdateSaltD[(((31U - aIndex) + 5U)) & S_SALT1];
            aOrbiterD = RotL64((aOrbiterD * 13086160171095077295U), 53U);
            //
            aOrbiterB = (aOrbiterB + aOrbiterG) + 9816600392407327227U;
            aOrbiterH = ((aOrbiterH ^ aOrbiterB) ^ 16781971616348376878U) ^ aPhaseFOrbiterUpdateSaltF[(((31U - aIndex) + 23U)) & S_SALT1];
            aOrbiterH = RotL64((aOrbiterH * 12503867584828289879U), 5U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterA) + 4807797577690520554U;
            aOrbiterG = (aOrbiterG ^ aOrbiterD) ^ 2492057261148595922U;
            aOrbiterG = RotL64((aOrbiterG * 9453302540675483005U), 13U);
            //
            aOrbiterI = ((aOrbiterI + aOrbiterD) + 7909676419643119585U) + aPhaseFOrbiterUpdateSaltE[((aIndex + 24U)) & S_SALT1];
            aOrbiterB = (aOrbiterB ^ aOrbiterI) ^ 256053568910383007U;
            aOrbiterB = RotL64((aOrbiterB * 11965085163352053161U), 27U);
            //
            aOrbiterK = ((aOrbiterK + aOrbiterH) + 16179914439220412472U) + aPhaseFOrbiterUpdateSaltB[((aIndex + 6U)) & S_SALT1];
            aOrbiterC = (aOrbiterC ^ aOrbiterK) ^ 3968867762761955845U;
            aOrbiterC = RotL64((aOrbiterC * 7473632378251893139U), 47U);
            //
            aOrbiterH = (aOrbiterH + aOrbiterE) + 7474832923901283742U;
            aOrbiterF = (aOrbiterF ^ aOrbiterH) ^ 4736994731050735779U;
            aOrbiterF = RotL64((aOrbiterF * 9839654409121414047U), 51U);
            //
            aOrbiterJ = (aOrbiterJ + aOrbiterI) + 596484364660389193U;
            aOrbiterA = (aOrbiterA ^ aOrbiterJ) ^ 13822222274464306169U;
            aOrbiterA = RotL64((aOrbiterA * 1723502278319885511U), 3U);
            //
            aOrbiterG = (aOrbiterG + aOrbiterK) + 16307920280681985443U;
            aOrbiterE = (aOrbiterE ^ aOrbiterG) ^ 3505106171801702915U;
            aOrbiterE = RotL64((aOrbiterE * 8479675421552861243U), 29U);
            //
            aOrbiterA = (aOrbiterA + aOrbiterB) + 4987142580981135150U;
            aOrbiterK = (aOrbiterK ^ aOrbiterA) ^ 10336802574069791273U;
            aOrbiterK = RotL64((aOrbiterK * 2670706512498539705U), 37U);
            //
            aIngress = RotL64(aOrbiterB, 60U) ^ aOrbiterK;
            aIngress = aIngress + (aOrbiterH ^ RotL64(aOrbiterJ, 13U));
            aIngress = aIngress + (RotL64(aOrbiterF, 27U) ^ aOrbiterA);
            aIngress = aIngress + (aOrbiterI ^ RotL64(aOrbiterE, 35U));
            aIngress = aIngress + (RotL64(aOrbiterG, 3U) ^ aOrbiterD);
            aIngress = aIngress + RotL64(aOrbiterC, 51U);
            aIngress = TwistMix64::DiffuseB((aIngress + aScatter));
            //
            aWandererB = aWandererB + ((RotL64(aIngress, 13U) + aOrbiterH) + RotL64(aOrbiterJ, 47U));
            aWandererA = aWandererA ^ ((RotL64(aPrevious, 53U) + aOrbiterC) + RotL64(aOrbiterE, 54U));
            aWandererH = aWandererH + ((RotL64(aCross, 51U) + aOrbiterA) + RotL64(aOrbiterC, 35U));
            aWandererG = aWandererG ^ ((RotL64(aScatter, 47U) + aOrbiterC) + RotL64(aOrbiterI, 5U));
            aWandererJ = aWandererJ + (((RotL64(aCross, 26U) + aOrbiterB) + RotL64(aOrbiterG, 21U)) + RotL64(aCarry, 39U));
            aWandererC = aWandererC ^ ((RotL64(aIngress, 43U) + aOrbiterH) + RotL64(aOrbiterF, 23U));
            aWandererK = aWandererK + (((RotL64(aScatter, 21U) + RotL64(aOrbiterD, 41U)) + aOrbiterE) + aPhaseFWandererUpdateSaltF[((aIndex + 15U)) & S_SALT1]);
            aWandererE = aWandererE ^ ((RotL64(aPrevious, 29U) + RotL64(aOrbiterG, 38U)) + aOrbiterH);
            aWandererF = aWandererF + ((RotL64(aCross, 40U) + aOrbiterB) + RotL64(aOrbiterA, 3U));
            aWandererI = aWandererI ^ ((RotL64(aPrevious, 11U) + RotL64(aOrbiterG, 51U)) + aOrbiterK);
            aWandererD = aWandererD + ((((RotL64(aIngress, 57U) + aOrbiterI) + RotL64(aOrbiterK, 29U)) + RotL64(aCarry, 19U)) + aPhaseFWandererUpdateSaltC[((aIndex + 18U)) & S_SALT1]);
            //
            aCarry = aCarry + (aWandererD ^ RotL64(aWandererK, 52U));
            aCarry = aCarry + (aWandererH ^ RotL64(aWandererC, 39U));
            aCarry = aCarry + (aWandererJ ^ RotL64(aWandererI, 27U));
            aCarry = aCarry + (RotL64(aWandererA, 57U) ^ aWandererB);
            aCarry = aCarry + (aWandererE ^ RotL64(aWandererG, 37U));
            aCarry = aCarry + RotL64(aWandererF, 19U);
            aCarry = aCarry + RotL64(aIngress, 14U);
            aCarry = TwistMix64::DiffuseB(aCarry);
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

void TwistExpander_Greezy_Arx::GROW_A(TwistWorkSpace *pWorkSpace,
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

    std::uint64_t aOrbiterA = 0; std::uint64_t aOrbiterB = 0; std::uint64_t aOrbiterC = 0; std::uint64_t aOrbiterD = 0;
    std::uint64_t aOrbiterE = 0; std::uint64_t aOrbiterF = 0; std::uint64_t aOrbiterG = 0; std::uint64_t aOrbiterH = 0;
    std::uint64_t aOrbiterI = 0; std::uint64_t aOrbiterK = 0;

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
        // ingress from: aWorkLaneA, aWorkLaneB, aWorkLaneC
        // ingress directions: aWorkLaneA forward forced, aWorkLaneB forward forced, aWorkLaneC forward/backward random
        // cross from: aWorkLaneB, aWorkLaneC, aWorkLaneD
        // cross directions: aWorkLaneB backward forced, aWorkLaneC backward forced, aWorkLaneD backward/forward random
        // write to: aExpandLaneA
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aWorkLaneA[((aIndex + 4357U)) & S_BLOCK1], 46U) ^ RotL64(aWorkLaneB[((aIndex + 6305U)) & S_BLOCK1], 11U));
            aIngress ^= RotL64(aWorkLaneC[((aIndex + 4899U)) & S_BLOCK1], 3U);
            aIngress = TwistMix64::DiffuseA(aIngress);
            //
            aCross = (RotL64(aWorkLaneB[((S_BLOCK1 - aIndex + 2123U)) & S_BLOCK1], 37U) ^ RotL64(aWorkLaneC[((S_BLOCK1 - aIndex + 6962U)) & S_BLOCK1], 13U));
            aCross ^= RotL64(aWorkLaneD[((S_BLOCK1 - aIndex + 839U)) & S_BLOCK1], 46U);
            aCross = TwistMix64::DiffuseA(aCross);
            //
            aScatter = (RotL64(aCross, 52U) ^ RotL64(aPrevious, 23U)) + (RotL64(aIngress, 37U) + RotL64(aCarry, 3U));
            aScatter = TwistMix64::DiffuseC(aScatter);
            //
            aOrbiterC = (aWandererC + RotL64(aScatter, 47U)) + 9630214189402543339U;
            aOrbiterI = (((aWandererB + RotL64(aPrevious, 29U)) + RotL64(aCarry, 35U)) + 4072576573737526819U) + aPhaseGOrbiterAssignSaltE[(((31U - aIndex) + 15U)) & S_SALT1];
            aOrbiterK = ((aWandererI + RotL64(aCross, 21U)) + RotL64(aCarry, 3U)) + 15994787452709618869U;
            aOrbiterB = (((aWandererF + RotL64(aIngress, 57U)) + RotL64(aCarry, 47U)) + 6403240137132259482U) + aPhaseGOrbiterAssignSaltF[((aIndex + 9U)) & S_SALT1];
            aOrbiterE = (aWandererK + RotL64(aCross, 6U)) + 10229266900170507720U;
            //
            aOrbiterC = ((aOrbiterC + aOrbiterI) + 5025294577989748989U) + aPhaseGOrbiterUpdateSaltB[((aIndex + 26U)) & S_SALT1];
            aOrbiterK = ((aOrbiterK ^ aOrbiterC) ^ 16696461238217956883U) ^ aPhaseGOrbiterUpdateSaltC[(((31U - aIndex) + 25U)) & S_SALT1];
            aOrbiterK = RotL64((aOrbiterK * 15993828976234917577U), 21U);
            //
            aOrbiterK = (aOrbiterK + aOrbiterB) + 9878318855341719119U;
            aOrbiterE = (aOrbiterE ^ aOrbiterK) ^ 16086635438116177346U;
            aOrbiterE = RotL64((aOrbiterE * 5585682357395705671U), 29U);
            //
            aOrbiterE = (aOrbiterE + aOrbiterC) + 12295437783084203730U;
            aOrbiterI = ((aOrbiterI ^ aOrbiterE) ^ 7681150419912842402U) ^ aPhaseGOrbiterUpdateSaltD[(((31U - aIndex) + 23U)) & S_SALT1];
            aOrbiterI = RotL64((aOrbiterI * 7289497379725191451U), 53U);
            //
            aOrbiterI = ((aOrbiterI + aOrbiterK) + 2639104034287637448U) + aPhaseGOrbiterUpdateSaltA[((aIndex + 11U)) & S_SALT1];
            aOrbiterB = (aOrbiterB ^ aOrbiterI) ^ 12298170009332243573U;
            aOrbiterB = RotL64((aOrbiterB * 9397919591171238575U), 13U);
            //
            aOrbiterB = (aOrbiterB + aOrbiterE) + 3485932317267669626U;
            aOrbiterC = (aOrbiterC ^ aOrbiterB) ^ 16569551670038752475U;
            aOrbiterC = RotL64((aOrbiterC * 8139802826402217631U), 41U);
            //
            aIngress = aOrbiterB ^ RotL64(aOrbiterK, 13U);
            aIngress = aIngress + (RotL64(aOrbiterI, 3U) ^ aOrbiterC);
            aIngress = aIngress + RotL64(aOrbiterE, 51U);
            aIngress = TwistMix64::DiffuseB((aIngress + aScatter));
            //
            aWandererB = aWandererB + ((((RotL64(aIngress, 13U) + aOrbiterK) + RotL64(aOrbiterE, 23U)) + RotL64(aCarry, 11U)) + aPhaseGWandererUpdateSaltF[((aIndex + 13U)) & S_SALT1]);
            aWandererC = aWandererC ^ ((RotL64(aCross, 60U) + aOrbiterB) + RotL64(aOrbiterI, 43U));
            aWandererF = aWandererF + (((RotL64(aScatter, 5U) + RotL64(aOrbiterK, 14U)) + aOrbiterC) + RotL64(aCarry, 35U));
            aWandererK = aWandererK ^ ((RotL64(aPrevious, 47U) + RotL64(aOrbiterI, 3U)) + aOrbiterK);
            aWandererI = aWandererI + (((RotL64(aScatter, 23U) + RotL64(aOrbiterE, 57U)) + aOrbiterI) + aPhaseGWandererUpdateSaltD[((aIndex + 18U)) & S_SALT1]);
            //
            aCarry = aCarry + (aWandererI ^ RotL64(aWandererF, 47U));
            aCarry = aCarry + (RotL64(aWandererB, 57U) ^ aWandererK);
            aCarry = aCarry + RotL64(aWandererC, 13U);
            aCarry = aCarry + RotL64(aIngress, 3U);
            aCarry = TwistMix64::DiffuseC(aCarry);
            //
            aExpandLaneA[aIndex] = aIngress;
        }
    
        // grow_key_a loop 2
        // ingress from: aExpandLaneA, aWorkLaneB, aWorkLaneC
        // ingress directions: aExpandLaneA forward forced, aWorkLaneB forward forced, aWorkLaneC forward/backward random
        // cross from: aWorkLaneB, aWorkLaneC, aWorkLaneD
        // cross directions: aWorkLaneB backward forced, aWorkLaneC backward forced, aWorkLaneD backward/forward random
        // write to: aExpandLaneB
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aExpandLaneA[((aIndex + 12068U)) & S_BLOCK1], 24U) ^ RotL64(aWorkLaneB[((aIndex + 10749U)) & S_BLOCK1], 37U));
            aIngress ^= RotL64(aWorkLaneC[((aIndex + 13075U)) & S_BLOCK1], 11U);
            aIngress = TwistMix64::DiffuseB(aIngress);
            //
            aCross = (RotL64(aWorkLaneB[((S_BLOCK1 - aIndex + 9371U)) & S_BLOCK1], 4U) ^ RotL64(aWorkLaneC[((S_BLOCK1 - aIndex + 11540U)) & S_BLOCK1], 13U));
            aCross ^= RotL64(aWorkLaneD[((S_BLOCK1 - aIndex + 12489U)) & S_BLOCK1], 57U);
            aCross = TwistMix64::DiffuseB(aCross);
            //
            aScatter = (RotL64(aCarry, 5U) + RotL64(aIngress, 21U)) ^ (RotL64(aPrevious, 35U) ^ RotL64(aCross, 48U));
            aScatter = TwistMix64::DiffuseC(aScatter);
            //
            aOrbiterF = (((aWandererA + RotL64(aPrevious, 21U)) + RotL64(aCarry, 13U)) + 9041099828460168106U) + aPhaseGOrbiterAssignSaltA[(((31U - aIndex) + 28U)) & S_SALT1];
            aOrbiterB = (aWandererE + RotL64(aIngress, 54U)) + 12883711604096848454U;
            aOrbiterG = ((aWandererD + RotL64(aCross, 5U)) + RotL64(aCarry, 29U)) + 17420968786226443079U;
            aOrbiterE = (((aWandererB + RotL64(aScatter, 29U)) + RotL64(aCarry, 41U)) + 3448213891716125104U) + aPhaseGOrbiterAssignSaltD[((aIndex + 29U)) & S_SALT1];
            aOrbiterA = (aWandererK + RotL64(aCross, 13U)) + 11866455977445336560U;
            //
            aOrbiterF = (aOrbiterF + aOrbiterB) + 4119356835384495905U;
            aOrbiterG = (aOrbiterG ^ aOrbiterF) ^ 2186212599698637068U;
            aOrbiterG = RotL64((aOrbiterG * 6756888950976735707U), 39U);
            //
            aOrbiterG = ((aOrbiterG + aOrbiterE) + 6506144898969301620U) + aPhaseGOrbiterUpdateSaltA[(((31U - aIndex) + 17U)) & S_SALT1];
            aOrbiterB = ((aOrbiterB ^ aOrbiterG) ^ 12556800923644051626U) ^ aPhaseGOrbiterUpdateSaltD[(((31U - aIndex) + 19U)) & S_SALT1];
            aOrbiterB = RotL64((aOrbiterB * 15961043406612913121U), 47U);
            //
            aOrbiterB = (aOrbiterB + aOrbiterA) + 4075551535185182945U;
            aOrbiterE = ((aOrbiterE ^ aOrbiterB) ^ 17877694808492008749U) ^ aPhaseGOrbiterUpdateSaltF[((aIndex + 13U)) & S_SALT1];
            aOrbiterE = RotL64((aOrbiterE * 901315308379887473U), 19U);
            //
            aOrbiterA = (aOrbiterA + aOrbiterG) + 5553428900598223316U;
            aOrbiterF = (aOrbiterF ^ aOrbiterA) ^ 14362304852277160675U;
            aOrbiterF = RotL64((aOrbiterF * 11415103199856419303U), 3U);
            //
            aOrbiterE = (aOrbiterE + aOrbiterF) + 9174200302876075831U;
            aOrbiterA = ((aOrbiterA ^ aOrbiterE) ^ 16110739511917638547U) ^ aPhaseGOrbiterUpdateSaltE[((aIndex + 12U)) & S_SALT1];
            aOrbiterA = RotL64((aOrbiterA * 7004356839428657949U), 27U);
            //
            aIngress = aOrbiterE ^ RotL64(aOrbiterG, 3U);
            aIngress = aIngress + (aOrbiterB ^ RotL64(aOrbiterA, 13U));
            aIngress = aIngress + RotL64(aOrbiterF, 44U);
            aIngress = TwistMix64::DiffuseC((aIngress + aScatter));
            //
            aWandererK = aWandererK ^ ((RotL64(aIngress, 48U) + aOrbiterG) + RotL64(aOrbiterF, 13U));
            aWandererE = aWandererE + ((((RotL64(aScatter, 3U) + aOrbiterA) + RotL64(aOrbiterG, 35U)) + RotL64(aCarry, 11U)) + aPhaseGWandererUpdateSaltA[(((31U - aIndex) + 20U)) & S_SALT1]);
            aWandererD = aWandererD ^ (((RotL64(aCross, 11U) + aOrbiterB) + RotL64(aOrbiterF, 5U)) + aPhaseGWandererUpdateSaltB[((aIndex + 15U)) & S_SALT1]);
            aWandererB = aWandererB + (((RotL64(aPrevious, 57U) + RotL64(aOrbiterF, 58U)) + aOrbiterE) + RotL64(aCarry, 51U));
            aWandererA = aWandererA ^ ((RotL64(aIngress, 35U) + RotL64(aOrbiterB, 21U)) + aOrbiterA);
            //
            aCarry = aCarry + (RotL64(aWandererB, 3U) ^ aWandererE);
            aCarry = aCarry + (aWandererA ^ RotL64(aWandererD, 11U));
            aCarry = aCarry + RotL64(aWandererK, 27U);
            aCarry = aCarry + RotL64(aIngress, 48U);
            aCarry = TwistMix64::DiffuseA(aCarry);
            //
            aExpandLaneB[S_BLOCK1 - aIndex] = aIngress;
        }
    
        // grow_key_a loop 3
        // ingress from: aExpandLaneB, aExpandLaneA, aWorkLaneD
        // ingress directions: aExpandLaneB forward forced, aExpandLaneA forward forced, aWorkLaneD forward/backward random
        // cross from: aExpandLaneA, aWorkLaneD, aWorkLaneC
        // cross directions: aExpandLaneA backward forced, aWorkLaneD backward forced, aWorkLaneC backward/forward random
        // write to: aExpandLaneC
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aExpandLaneB[((aIndex + 24313U)) & S_BLOCK1], 39U) ^ RotL64(aExpandLaneA[((aIndex + 17293U)) & S_BLOCK1], 19U));
            aIngress ^= RotL64(aWorkLaneD[((aIndex + 16912U)) & S_BLOCK1], 60U);
            aIngress = TwistMix64::DiffuseB(aIngress);
            //
            aCross = (RotL64(aExpandLaneA[((S_BLOCK1 - aIndex + 23532U)) & S_BLOCK1], 23U) ^ RotL64(aWorkLaneD[((S_BLOCK1 - aIndex + 21987U)) & S_BLOCK1], 13U));
            aCross ^= RotL64(aWorkLaneC[((S_BLOCK1 - aIndex + 19686U)) & S_BLOCK1], 42U);
            aCross = TwistMix64::DiffuseC(aCross);
            //
            aScatter = (RotL64(aIngress, 3U) ^ RotL64(aCarry, 20U)) + (RotL64(aCross, 53U) + RotL64(aPrevious, 39U));
            aScatter = TwistMix64::DiffuseC(aScatter);
            //
            aOrbiterC = (aWandererB + RotL64(aIngress, 58U)) + 13204735390996728477U;
            aOrbiterG = (((aWandererI + RotL64(aScatter, 23U)) + RotL64(aCarry, 53U)) + 851171359595647173U) + aPhaseGOrbiterAssignSaltC[(((31U - aIndex) + 26U)) & S_SALT1];
            aOrbiterD = ((aWandererG + RotL64(aCross, 37U)) + RotL64(aCarry, 3U)) + 16745304202825290723U;
            aOrbiterH = ((aWandererK + RotL64(aPrevious, 13U)) + RotL64(aCarry, 41U)) + 562392736584913979U;
            aOrbiterA = ((aWandererE + RotL64(aIngress, 47U)) + 3244267012529053918U) + aPhaseGOrbiterAssignSaltB[(((31U - aIndex) + 5U)) & S_SALT1];
            //
            aOrbiterC = ((aOrbiterC + aOrbiterG) + 17282536111067869133U) + aPhaseGOrbiterUpdateSaltF[((aIndex + 23U)) & S_SALT1];
            aOrbiterD = (aOrbiterD ^ aOrbiterC) ^ 14851130066471729068U;
            aOrbiterD = RotL64((aOrbiterD * 6308165353504550619U), 57U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterH) + 5256130407952363129U;
            aOrbiterA = (aOrbiterA ^ aOrbiterD) ^ 2904742485828362001U;
            aOrbiterA = RotL64((aOrbiterA * 12941135856735075457U), 27U);
            //
            aOrbiterH = ((aOrbiterH + aOrbiterA) + 3723346325449225387U) + aPhaseGOrbiterUpdateSaltC[(((31U - aIndex) + 3U)) & S_SALT1];
            aOrbiterC = (aOrbiterC ^ aOrbiterH) ^ 5344621093694027341U;
            aOrbiterC = RotL64((aOrbiterC * 9044881458629673499U), 5U);
            //
            aOrbiterG = (aOrbiterG + aOrbiterD) + 12919263300833603026U;
            aOrbiterH = (aOrbiterH ^ aOrbiterG) ^ 17989801264160996071U;
            aOrbiterH = RotL64((aOrbiterH * 15468293047311883751U), 41U);
            //
            aOrbiterA = ((aOrbiterA + aOrbiterC) + 5022175042377172157U) + aPhaseGOrbiterUpdateSaltB[(((31U - aIndex) + 19U)) & S_SALT1];
            aOrbiterG = ((aOrbiterG ^ aOrbiterA) ^ 16684822380107847758U) ^ aPhaseGOrbiterUpdateSaltA[((aIndex + 9U)) & S_SALT1];
            aOrbiterG = RotL64((aOrbiterG * 2834049270263837537U), 13U);
            //
            aIngress = aOrbiterA ^ RotL64(aOrbiterD, 3U);
            aIngress = aIngress + (RotL64(aOrbiterG, 34U) ^ aOrbiterC);
            aIngress = aIngress + RotL64(aOrbiterH, 19U);
            aIngress = TwistMix64::DiffuseC((aIngress + aScatter));
            //
            aWandererK = aWandererK + (((RotL64(aScatter, 58U) + RotL64(aOrbiterD, 37U)) + aOrbiterH) + RotL64(aCarry, 47U));
            aWandererB = aWandererB ^ ((RotL64(aIngress, 13U) + aOrbiterG) + RotL64(aOrbiterD, 28U));
            aWandererG = aWandererG + ((RotL64(aPrevious, 43U) + aOrbiterH) + RotL64(aOrbiterC, 53U));
            aWandererI = aWandererI ^ (((RotL64(aCross, 23U) + RotL64(aOrbiterC, 5U)) + aOrbiterG) + aPhaseGWandererUpdateSaltC[(((31U - aIndex) + 21U)) & S_SALT1]);
            aWandererE = aWandererE + ((((RotL64(aIngress, 35U) + RotL64(aOrbiterH, 19U)) + aOrbiterA) + RotL64(aCarry, 23U)) + aPhaseGWandererUpdateSaltE[((aIndex + 15U)) & S_SALT1]);
            //
            aCarry = aCarry + (RotL64(aWandererI, 39U) ^ aWandererE);
            aCarry = aCarry + (RotL64(aWandererG, 11U) ^ aWandererK);
            aCarry = aCarry + RotL64(aWandererB, 51U);
            aCarry = aCarry + RotL64(aIngress, 19U);
            aCarry = TwistMix64::DiffuseC(aCarry);
            //
            aExpandLaneC[aIndex] = aIngress;
        }
    
        // grow_key_a loop 4
        // ingress from: aExpandLaneC, aExpandLaneB, aExpandLaneA
        // ingress directions: aExpandLaneC forward forced, aExpandLaneB forward forced, aExpandLaneA forward/backward random
        // cross from: aExpandLaneA, aExpandLaneB, aExpandLaneC
        // cross directions: aExpandLaneA backward forced, aExpandLaneB backward forced, aExpandLaneC backward/forward random
        // write to: aExpandLaneD
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aExpandLaneC[((aIndex + 26443U)) & S_BLOCK1], 11U) ^ RotL64(aExpandLaneB[((aIndex + 30842U)) & S_BLOCK1], 20U));
            aIngress ^= RotL64(aExpandLaneA[((aIndex + 26064U)) & S_BLOCK1], 57U);
            aIngress = TwistMix64::DiffuseC(aIngress);
            //
            aCross = (RotL64(aExpandLaneA[((S_BLOCK1 - aIndex + 27456U)) & S_BLOCK1], 53U) ^ RotL64(aExpandLaneB[((S_BLOCK1 - aIndex + 31611U)) & S_BLOCK1], 40U));
            aCross ^= RotL64(aExpandLaneC[((S_BLOCK1 - aIndex + 28216U)) & S_BLOCK1], 19U);
            aCross = TwistMix64::DiffuseB(aCross);
            //
            aScatter = (RotL64(aPrevious, 3U) ^ RotL64(aCross, 19U)) + (RotL64(aIngress, 35U) + RotL64(aCarry, 48U));
            aScatter = TwistMix64::DiffuseB(aScatter);
            //
            aOrbiterK = ((aWandererK + RotL64(aIngress, 37U)) + 4384716820085860551U) + aPhaseGOrbiterAssignSaltF[(((31U - aIndex) + 15U)) & S_SALT1];
            aOrbiterH = (((aWandererH + RotL64(aPrevious, 11U)) + RotL64(aCarry, 39U)) + 9715780315942116888U) + aPhaseGOrbiterAssignSaltE[((aIndex + 5U)) & S_SALT1];
            aOrbiterA = ((aWandererG + RotL64(aScatter, 28U)) + RotL64(aCarry, 51U)) + 15963520052789178632U;
            aOrbiterG = ((aWandererF + RotL64(aCross, 53U)) + RotL64(aCarry, 11U)) + 14346700690686392938U;
            aOrbiterE = (aWandererD + RotL64(aIngress, 3U)) + 6005518012489966643U;
            //
            aOrbiterK = (aOrbiterK + aOrbiterH) + 2506732930310252119U;
            aOrbiterA = ((aOrbiterA ^ aOrbiterK) ^ 16782163084851775826U) ^ aPhaseGOrbiterUpdateSaltE[((aIndex + 9U)) & S_SALT1];
            aOrbiterA = RotL64((aOrbiterA * 1527050617428162663U), 13U);
            //
            aOrbiterG = (aOrbiterG + aOrbiterE) + 823673076571076303U;
            aOrbiterK = (aOrbiterK ^ aOrbiterG) ^ 1634084509064077736U;
            aOrbiterK = RotL64((aOrbiterK * 1128407326773234517U), 39U);
            //
            aOrbiterE = ((aOrbiterE + aOrbiterK) + 1288134975466877686U) + aPhaseGOrbiterUpdateSaltA[(((31U - aIndex) + 22U)) & S_SALT1];
            aOrbiterH = (aOrbiterH ^ aOrbiterE) ^ 2998220403162908444U;
            aOrbiterH = RotL64((aOrbiterH * 4321412662318298283U), 23U);
            //
            aOrbiterH = (aOrbiterH + aOrbiterA) + 220430672180734911U;
            aOrbiterG = ((aOrbiterG ^ aOrbiterH) ^ 10223923547068528867U) ^ aPhaseGOrbiterUpdateSaltD[((aIndex + 11U)) & S_SALT1];
            aOrbiterG = RotL64((aOrbiterG * 12577370238343872139U), 57U);
            //
            aOrbiterA = ((aOrbiterA + aOrbiterG) + 11696469696177647608U) + aPhaseGOrbiterUpdateSaltC[((aIndex + 4U)) & S_SALT1];
            aOrbiterE = (aOrbiterE ^ aOrbiterA) ^ 6545430420379636963U;
            aOrbiterE = RotL64((aOrbiterE * 8387163146257553773U), 5U);
            //
            aIngress = aOrbiterK ^ RotL64(aOrbiterH, 5U);
            aIngress = aIngress + (aOrbiterE ^ RotL64(aOrbiterA, 58U));
            aIngress = aIngress + RotL64(aOrbiterG, 47U);
            aIngress = TwistMix64::DiffuseC((aIngress + aScatter));
            //
            aWandererH = aWandererH ^ (((RotL64(aCross, 35U) + aOrbiterG) + RotL64(aOrbiterA, 41U)) + aPhaseGWandererUpdateSaltF[((aIndex + 6U)) & S_SALT1]);
            aWandererF = aWandererF + (((RotL64(aScatter, 27U) + RotL64(aOrbiterH, 51U)) + aOrbiterK) + RotL64(aCarry, 53U));
            aWandererD = aWandererD ^ ((RotL64(aIngress, 51U) + aOrbiterE) + RotL64(aOrbiterK, 11U));
            aWandererK = aWandererK + ((((RotL64(aPrevious, 60U) + RotL64(aOrbiterK, 3U)) + aOrbiterG) + RotL64(aCarry, 3U)) + aPhaseGWandererUpdateSaltD[(((31U - aIndex) + 19U)) & S_SALT1]);
            aWandererG = aWandererG ^ ((RotL64(aIngress, 19U) + RotL64(aOrbiterE, 24U)) + aOrbiterG);
            //
            aCarry = aCarry + (aWandererH ^ RotL64(aWandererD, 53U));
            aCarry = aCarry + (RotL64(aWandererF, 22U) ^ aWandererK);
            aCarry = aCarry + RotL64(aWandererG, 35U);
            aCarry = aCarry + RotL64(aIngress, 43U);
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

void TwistExpander_Greezy_Arx::GROW_B(TwistWorkSpace *pWorkSpace,
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

    std::uint64_t aOrbiterA = 0; std::uint64_t aOrbiterB = 0; std::uint64_t aOrbiterC = 0; std::uint64_t aOrbiterD = 0;
    std::uint64_t aOrbiterE = 0; std::uint64_t aOrbiterF = 0; std::uint64_t aOrbiterG = 0; std::uint64_t aOrbiterH = 0;
    std::uint64_t aOrbiterI = 0; std::uint64_t aOrbiterJ = 0; std::uint64_t aOrbiterK = 0;

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
        // ingress from: aExpandLaneA, aExpandLaneB, aExpandLaneC
        // ingress directions: aExpandLaneA forward forced, aExpandLaneB forward forced, aExpandLaneC forward/backward random
        // cross from: aExpandLaneB, aExpandLaneC, aExpandLaneD
        // cross directions: aExpandLaneB backward forced, aExpandLaneC backward forced, aExpandLaneD backward/forward random
        // write to: aWorkLaneA
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aExpandLaneA[((aIndex + 1604U)) & S_BLOCK1], 3U) ^ RotL64(aExpandLaneB[((aIndex + 3252U)) & S_BLOCK1], 38U));
            aIngress ^= RotL64(aExpandLaneC[((S_BLOCK1 - aIndex + 928U)) & S_BLOCK1], 23U);
            aIngress = TwistMix64::DiffuseA(aIngress);
            //
            aCross = (RotL64(aExpandLaneB[((S_BLOCK1 - aIndex + 1985U)) & S_BLOCK1], 40U) ^ RotL64(aExpandLaneC[((S_BLOCK1 - aIndex + 2785U)) & S_BLOCK1], 13U));
            aCross ^= RotL64(aExpandLaneD[((aIndex + 415U)) & S_BLOCK1], 51U);
            aCross = TwistMix64::DiffuseC(aCross);
            //
            aScatter = (RotL64(aIngress, 24U) + RotL64(aCross, 39U)) ^ (RotL64(aPrevious, 53U) + RotL64(aCarry, 3U));
            aScatter = TwistMix64::DiffuseC(aScatter);
            //
            aOrbiterE = (((aWandererD + RotL64(aPrevious, 5U)) + RotL64(aCarry, 23U)) + 6068543441070417854U) + aPhaseHOrbiterAssignSaltB[((aIndex + 8U)) & S_SALT1];
            aOrbiterA = (aWandererI + RotL64(aIngress, 21U)) + 2995980468193441856U;
            aOrbiterJ = (((aWandererF + RotL64(aCross, 60U)) + RotL64(aCarry, 53U)) + 18020277482171594003U) + aPhaseHOrbiterAssignSaltF[((aIndex + 23U)) & S_SALT1];
            aOrbiterG = ((aWandererB + RotL64(aScatter, 37U)) + RotL64(aCarry, 35U)) + 4293807434721230702U;
            aOrbiterB = (aWandererJ + RotL64(aIngress, 51U)) + 7980599111583893156U;
            //
            aOrbiterE = ((aOrbiterE + aOrbiterA) + 8593141111851052016U) + aPhaseHOrbiterUpdateSaltD[((aIndex + 19U)) & S_SALT1];
            aOrbiterJ = (aOrbiterJ ^ aOrbiterE) ^ 5903487523900084325U;
            aOrbiterJ = RotL64((aOrbiterJ * 2508618861111356699U), 57U);
            //
            aOrbiterJ = (aOrbiterJ + aOrbiterG) + 15112035513447930209U;
            aOrbiterB = (aOrbiterB ^ aOrbiterJ) ^ 9854037263057006439U;
            aOrbiterB = RotL64((aOrbiterB * 396276470208637283U), 35U);
            //
            aOrbiterG = (aOrbiterG + aOrbiterB) + 16759760289688823193U;
            aOrbiterE = ((aOrbiterE ^ aOrbiterG) ^ 12622628933030601390U) ^ aPhaseHOrbiterUpdateSaltC[(((31U - aIndex) + 5U)) & S_SALT1];
            aOrbiterE = RotL64((aOrbiterE * 2151912984825538321U), 27U);
            //
            aOrbiterA = ((aOrbiterA + aOrbiterJ) + 1264668857268123425U) + aPhaseHOrbiterUpdateSaltF[(((31U - aIndex) + 27U)) & S_SALT1];
            aOrbiterG = (aOrbiterG ^ aOrbiterA) ^ 16302812053619101593U;
            aOrbiterG = RotL64((aOrbiterG * 18291400055836111547U), 47U);
            //
            aOrbiterB = (aOrbiterB + aOrbiterE) + 16087995784896123610U;
            aOrbiterA = ((aOrbiterA ^ aOrbiterB) ^ 7970269262800468363U) ^ aPhaseHOrbiterUpdateSaltE[(((31U - aIndex) + 14U)) & S_SALT1];
            aOrbiterA = RotL64((aOrbiterA * 14924752223305807461U), 19U);
            //
            aIngress = aOrbiterE ^ RotL64(aOrbiterB, 40U);
            aIngress = aIngress + (RotL64(aOrbiterG, 51U) ^ aOrbiterJ);
            aIngress = aIngress + RotL64(aOrbiterA, 29U);
            aIngress = TwistMix64::DiffuseC((aIngress + aScatter));
            //
            aWandererJ = aWandererJ + ((((RotL64(aPrevious, 60U) + RotL64(aOrbiterJ, 3U)) + aOrbiterA) + RotL64(aCarry, 11U)) + aPhaseHWandererUpdateSaltF[((aIndex + 11U)) & S_SALT1]);
            aWandererF = aWandererF ^ ((RotL64(aCross, 47U) + RotL64(aOrbiterA, 19U)) + aOrbiterG);
            aWandererB = aWandererB + (((RotL64(aIngress, 23U) + aOrbiterB) + RotL64(aOrbiterJ, 29U)) + RotL64(aCarry, 23U));
            aWandererD = aWandererD ^ ((RotL64(aScatter, 5U) + RotL64(aOrbiterJ, 41U)) + aOrbiterE);
            aWandererI = aWandererI + (((RotL64(aPrevious, 37U) + RotL64(aOrbiterA, 58U)) + aOrbiterB) + aPhaseHWandererUpdateSaltE[(((31U - aIndex) + 28U)) & S_SALT1]);
            //
            aCarry = aCarry + (RotL64(aWandererF, 47U) ^ aWandererD);
            aCarry = aCarry + (aWandererB ^ RotL64(aWandererI, 39U));
            aCarry = aCarry + RotL64(aWandererJ, 21U);
            aCarry = aCarry + RotL64(aIngress, 29U);
            aCarry = TwistMix64::DiffuseA(aCarry);
            //
            aWorkLaneA[aIndex] = aIngress;
        }
    
        // grow_key_b loop 2
        // ingress from: aWorkLaneA, aExpandLaneB, aExpandLaneC
        // ingress directions: aWorkLaneA forward forced, aExpandLaneB forward forced, aExpandLaneC forward/backward random
        // cross from: aExpandLaneC, aExpandLaneD, aWorkLaneA
        // cross directions: aExpandLaneC backward forced, aExpandLaneD backward forced, aWorkLaneA backward/forward random
        // write to: aWorkLaneB
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aWorkLaneA[((aIndex + 12999U)) & S_BLOCK1], 51U) ^ RotL64(aExpandLaneB[((aIndex + 13489U)) & S_BLOCK1], 30U));
            aIngress ^= RotL64(aExpandLaneC[((S_BLOCK1 - aIndex + 11582U)) & S_BLOCK1], 11U);
            aIngress = TwistMix64::DiffuseA(aIngress);
            //
            aCross = (RotL64(aExpandLaneC[((S_BLOCK1 - aIndex + 8590U)) & S_BLOCK1], 13U) ^ RotL64(aExpandLaneD[((S_BLOCK1 - aIndex + 12187U)) & S_BLOCK1], 37U));
            aCross ^= RotL64(aWorkLaneA[((S_BLOCK1 - aIndex + 11266U)) & S_BLOCK1], 60U);
            aCross = TwistMix64::DiffuseC(aCross);
            //
            aScatter = (RotL64(aPrevious, 30U) ^ RotL64(aCarry, 43U)) ^ (RotL64(aIngress, 57U) + RotL64(aCross, 13U));
            aScatter = TwistMix64::DiffuseB(aScatter);
            //
            aOrbiterI = ((aWandererI + RotL64(aIngress, 43U)) + 3970829908171131502U) + aPhaseHOrbiterAssignSaltD[((aIndex + 19U)) & S_SALT1];
            aOrbiterD = ((aWandererF + RotL64(aScatter, 21U)) + RotL64(aCarry, 57U)) + 7040283759419531991U;
            aOrbiterF = ((aWandererG + RotL64(aPrevious, 35U)) + RotL64(aCarry, 43U)) + 11856292169397052901U;
            aOrbiterA = (((aWandererJ + RotL64(aCross, 12U)) + RotL64(aCarry, 21U)) + 819598588791819022U) + aPhaseHOrbiterAssignSaltE[(((31U - aIndex) + 17U)) & S_SALT1];
            aOrbiterK = (aWandererD + RotL64(aIngress, 3U)) + 2176451710970866848U;
            //
            aOrbiterI = ((aOrbiterI + aOrbiterD) + 6454704928613390494U) + aPhaseHOrbiterUpdateSaltE[(((31U - aIndex) + 5U)) & S_SALT1];
            aOrbiterF = ((aOrbiterF ^ aOrbiterI) ^ 11792122387218053841U) ^ aPhaseHOrbiterUpdateSaltB[(((31U - aIndex) + 23U)) & S_SALT1];
            aOrbiterF = RotL64((aOrbiterF * 17994898985794518565U), 5U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterA) + 9254780213489752211U;
            aOrbiterK = ((aOrbiterK ^ aOrbiterD) ^ 16591812589999846482U) ^ aPhaseHOrbiterUpdateSaltD[(((31U - aIndex) + 25U)) & S_SALT1];
            aOrbiterK = RotL64((aOrbiterK * 5425771603523423167U), 13U);
            //
            aOrbiterK = (aOrbiterK + aOrbiterI) + 1471246223935074832U;
            aOrbiterA = (aOrbiterA ^ aOrbiterK) ^ 1424843083106386453U;
            aOrbiterA = RotL64((aOrbiterA * 15020536982657410783U), 23U);
            //
            aOrbiterA = (aOrbiterA + aOrbiterF) + 1856469958050891629U;
            aOrbiterI = (aOrbiterI ^ aOrbiterA) ^ 6331743690452052712U;
            aOrbiterI = RotL64((aOrbiterI * 15327924647897459645U), 47U);
            //
            aOrbiterF = (aOrbiterF + aOrbiterK) + 10351075711345476487U;
            aOrbiterD = ((aOrbiterD ^ aOrbiterF) ^ 9518585245330480185U) ^ aPhaseHOrbiterUpdateSaltA[((aIndex + 11U)) & S_SALT1];
            aOrbiterD = RotL64((aOrbiterD * 3792179827396760391U), 35U);
            //
            aIngress = RotL64(aOrbiterK, 6U) ^ aOrbiterD;
            aIngress = aIngress + (RotL64(aOrbiterI, 47U) ^ aOrbiterF);
            aIngress = aIngress + RotL64(aOrbiterA, 23U);
            aIngress = TwistMix64::DiffuseC((aIngress + aScatter));
            //
            aWandererF = aWandererF + ((((RotL64(aPrevious, 48U) + aOrbiterI) + RotL64(aOrbiterK, 37U)) + RotL64(aCarry, 5U)) + aPhaseHWandererUpdateSaltB[((aIndex + 9U)) & S_SALT1]);
            aWandererJ = aWandererJ ^ ((RotL64(aIngress, 13U) + aOrbiterD) + RotL64(aOrbiterF, 29U));
            aWandererI = aWandererI + (((RotL64(aScatter, 29U) + aOrbiterI) + RotL64(aOrbiterD, 50U)) + RotL64(aCarry, 21U));
            aWandererG = aWandererG ^ ((RotL64(aCross, 3U) + aOrbiterA) + RotL64(aOrbiterF, 3U));
            aWandererD = aWandererD + (((RotL64(aIngress, 37U) + aOrbiterK) + RotL64(aOrbiterF, 11U)) + aPhaseHWandererUpdateSaltD[(((31U - aIndex) + 4U)) & S_SALT1]);
            //
            aCarry = aCarry + (aWandererJ ^ RotL64(aWandererG, 37U));
            aCarry = aCarry + (RotL64(aWandererF, 19U) ^ aWandererD);
            aCarry = aCarry + RotL64(aWandererI, 27U);
            aCarry = aCarry + RotL64(aIngress, 11U);
            aCarry = TwistMix64::DiffuseA(aCarry);
            //
            aWorkLaneB[S_BLOCK1 - aIndex] = aIngress;
        }
    
        // grow_key_b loop 3
        // ingress from: aWorkLaneB, aWorkLaneA, aExpandLaneD
        // ingress directions: aWorkLaneB forward forced, aWorkLaneA forward forced, aExpandLaneD forward/backward random
        // cross from: aWorkLaneA, aExpandLaneD, aExpandLaneC
        // cross directions: aWorkLaneA backward forced, aExpandLaneD backward forced, aExpandLaneC backward/forward random
        // write to: aWorkLaneC
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aWorkLaneB[((aIndex + 23737U)) & S_BLOCK1], 56U) ^ RotL64(aWorkLaneA[((aIndex + 21314U)) & S_BLOCK1], 11U));
            aIngress ^= RotL64(aExpandLaneD[((S_BLOCK1 - aIndex + 24287U)) & S_BLOCK1], 19U);
            aIngress = TwistMix64::DiffuseB(aIngress);
            //
            aCross = (RotL64(aWorkLaneA[((S_BLOCK1 - aIndex + 23101U)) & S_BLOCK1], 22U) ^ RotL64(aExpandLaneD[((S_BLOCK1 - aIndex + 18912U)) & S_BLOCK1], 53U));
            aCross ^= RotL64(aExpandLaneC[((aIndex + 18615U)) & S_BLOCK1], 11U);
            aCross = TwistMix64::DiffuseB(aCross);
            //
            aScatter = (RotL64(aIngress, 57U) ^ RotL64(aCross, 41U)) + (RotL64(aCarry, 27U) + RotL64(aPrevious, 6U));
            aScatter = TwistMix64::DiffuseA(aScatter);
            //
            aOrbiterH = ((aWandererG + RotL64(aCross, 39U)) + RotL64(aCarry, 53U)) + 15813325389431304548U;
            aOrbiterC = (((aWandererB + RotL64(aPrevious, 21U)) + RotL64(aCarry, 27U)) + 2223874171125403602U) + aPhaseHOrbiterAssignSaltC[(((31U - aIndex) + 18U)) & S_SALT1];
            aOrbiterA = ((aWandererI + RotL64(aIngress, 12U)) + RotL64(aCarry, 39U)) + 5510483568496824130U;
            aOrbiterD = ((aWandererA + RotL64(aScatter, 51U)) + 15474152493495661876U) + aPhaseHOrbiterAssignSaltA[(((31U - aIndex) + 15U)) & S_SALT1];
            aOrbiterI = (aWandererD + RotL64(aPrevious, 29U)) + 16846339705130829195U;
            //
            aOrbiterH = (aOrbiterH + aOrbiterC) + 1289670576865739669U;
            aOrbiterA = ((aOrbiterA ^ aOrbiterH) ^ 18017354919647006944U) ^ aPhaseHOrbiterUpdateSaltE[(((31U - aIndex) + 3U)) & S_SALT1];
            aOrbiterA = RotL64((aOrbiterA * 13103155460891498469U), 35U);
            //
            aOrbiterA = ((aOrbiterA + aOrbiterD) + 8539685539928984921U) + aPhaseHOrbiterUpdateSaltA[((aIndex + 29U)) & S_SALT1];
            aOrbiterI = (aOrbiterI ^ aOrbiterA) ^ 3333721400836704048U;
            aOrbiterI = RotL64((aOrbiterI * 3745286323481400085U), 47U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterI) + 2261560416623815491U;
            aOrbiterH = (aOrbiterH ^ aOrbiterD) ^ 4377786131746816567U;
            aOrbiterH = RotL64((aOrbiterH * 9164777834392621157U), 5U);
            //
            aOrbiterC = (aOrbiterC + aOrbiterA) + 18047393176583722719U;
            aOrbiterD = ((aOrbiterD ^ aOrbiterC) ^ 8184724021940434631U) ^ aPhaseHOrbiterUpdateSaltB[((aIndex + 27U)) & S_SALT1];
            aOrbiterD = RotL64((aOrbiterD * 9800116157750921119U), 23U);
            //
            aOrbiterI = (aOrbiterI + aOrbiterH) + 10469895939183324807U;
            aOrbiterC = ((aOrbiterC ^ aOrbiterI) ^ 14543391765109879223U) ^ aPhaseHOrbiterUpdateSaltD[(((31U - aIndex) + 20U)) & S_SALT1];
            aOrbiterC = RotL64((aOrbiterC * 4817987697437667225U), 57U);
            //
            aIngress = aOrbiterA ^ RotL64(aOrbiterI, 14U);
            aIngress = aIngress + (aOrbiterD ^ RotL64(aOrbiterC, 57U));
            aIngress = aIngress + RotL64(aOrbiterH, 29U);
            aIngress = TwistMix64::DiffuseA((aIngress + aScatter));
            //
            aWandererG = aWandererG ^ ((RotL64(aIngress, 60U) + RotL64(aOrbiterD, 47U)) + aOrbiterH);
            aWandererI = aWandererI + ((((RotL64(aPrevious, 5U) + aOrbiterI) + RotL64(aOrbiterH, 23U)) + RotL64(aCarry, 11U)) + aPhaseHWandererUpdateSaltA[((aIndex + 23U)) & S_SALT1]);
            aWandererD = aWandererD ^ (((RotL64(aScatter, 13U) + RotL64(aOrbiterH, 60U)) + aOrbiterC) + aPhaseHWandererUpdateSaltC[(((31U - aIndex) + 7U)) & S_SALT1]);
            aWandererB = aWandererB + (((RotL64(aCross, 51U) + aOrbiterA) + RotL64(aOrbiterC, 39U)) + RotL64(aCarry, 57U));
            aWandererA = aWandererA ^ ((RotL64(aPrevious, 23U) + aOrbiterI) + RotL64(aOrbiterC, 11U));
            //
            aCarry = aCarry + (RotL64(aWandererA, 27U) ^ aWandererG);
            aCarry = aCarry + (RotL64(aWandererI, 57U) ^ aWandererD);
            aCarry = aCarry + RotL64(aWandererB, 36U);
            aCarry = aCarry + RotL64(aIngress, 47U);
            aCarry = TwistMix64::DiffuseA(aCarry);
            //
            aWorkLaneC[aIndex] = aIngress;
        }
    
        // grow_key_b loop 4
        // ingress from: aWorkLaneC, aWorkLaneB, aWorkLaneA
        // ingress directions: aWorkLaneC forward forced, aWorkLaneB forward forced, aWorkLaneA forward/backward random
        // cross from: aWorkLaneA, aWorkLaneB, aWorkLaneC
        // cross directions: aWorkLaneA backward forced, aWorkLaneB backward forced, aWorkLaneC backward/forward random
        // write to: aWorkLaneD
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aWorkLaneC[((aIndex + 31440U)) & S_BLOCK1], 21U) ^ RotL64(aWorkLaneB[((aIndex + 30728U)) & S_BLOCK1], 34U));
            aIngress ^= RotL64(aWorkLaneA[((S_BLOCK1 - aIndex + 32626U)) & S_BLOCK1], 47U);
            aIngress = TwistMix64::DiffuseC(aIngress);
            //
            aCross = (RotL64(aWorkLaneA[((S_BLOCK1 - aIndex + 25901U)) & S_BLOCK1], 27U) ^ RotL64(aWorkLaneB[((S_BLOCK1 - aIndex + 31742U)) & S_BLOCK1], 43U));
            aCross ^= RotL64(aWorkLaneC[((aIndex + 24907U)) & S_BLOCK1], 60U);
            aCross = TwistMix64::DiffuseA(aCross);
            //
            aScatter = (RotL64(aCarry, 52U) ^ RotL64(aPrevious, 37U)) + (RotL64(aCross, 23U) ^ RotL64(aIngress, 3U));
            aScatter = TwistMix64::DiffuseA(aScatter);
            //
            aOrbiterI = ((aWandererD + RotL64(aIngress, 29U)) + 7722279280863371124U) + aPhaseHOrbiterAssignSaltF[(((31U - aIndex) + 8U)) & S_SALT1];
            aOrbiterB = ((aWandererH + RotL64(aScatter, 4U)) + 11584220561732385598U) + aPhaseHOrbiterAssignSaltB[((aIndex + 14U)) & S_SALT1];
            aOrbiterA = ((aWandererI + RotL64(aPrevious, 53U)) + RotL64(aCarry, 23U)) + 7834679350105534657U;
            aOrbiterF = ((aWandererG + RotL64(aCross, 39U)) + RotL64(aCarry, 37U)) + 11347994382444180879U;
            aOrbiterK = ((aWandererC + RotL64(aScatter, 19U)) + RotL64(aCarry, 3U)) + 9449903188047063431U;
            //
            aOrbiterI = ((aOrbiterI + aOrbiterB) + 6516243976652795170U) + aPhaseHOrbiterUpdateSaltA[(((31U - aIndex) + 17U)) & S_SALT1];
            aOrbiterA = (aOrbiterA ^ aOrbiterI) ^ 8420815253991184777U;
            aOrbiterA = RotL64((aOrbiterA * 1358649408967265415U), 21U);
            //
            aOrbiterA = (aOrbiterA + aOrbiterF) + 9081386852515170937U;
            aOrbiterK = (aOrbiterK ^ aOrbiterA) ^ 14375955191735286867U;
            aOrbiterK = RotL64((aOrbiterK * 2772840314542262283U), 57U);
            //
            aOrbiterB = ((aOrbiterB + aOrbiterA) + 880757589768436072U) + aPhaseHOrbiterUpdateSaltC[((aIndex + 11U)) & S_SALT1];
            aOrbiterF = ((aOrbiterF ^ aOrbiterB) ^ 3349856625725164229U) ^ aPhaseHOrbiterUpdateSaltD[((aIndex + 5U)) & S_SALT1];
            aOrbiterF = RotL64((aOrbiterF * 681514212582331781U), 43U);
            //
            aOrbiterF = ((aOrbiterF + aOrbiterK) + 7826309957607577207U) + aPhaseHOrbiterUpdateSaltF[((aIndex + 10U)) & S_SALT1];
            aOrbiterI = (aOrbiterI ^ aOrbiterF) ^ 8057435761214313635U;
            aOrbiterI = RotL64((aOrbiterI * 4718430712767038607U), 3U);
            //
            aOrbiterK = (aOrbiterK + aOrbiterI) + 9565237500443303103U;
            aOrbiterB = (aOrbiterB ^ aOrbiterK) ^ 15893066735310588501U;
            aOrbiterB = RotL64((aOrbiterB * 8457633439171452397U), 29U);
            //
            aIngress = RotL64(aOrbiterK, 47U) ^ aOrbiterI;
            aIngress = aIngress + (RotL64(aOrbiterB, 24U) ^ aOrbiterA);
            aIngress = aIngress + RotL64(aOrbiterF, 13U);
            aIngress = TwistMix64::DiffuseA((aIngress + aScatter));
            //
            aWandererH = aWandererH ^ ((RotL64(aIngress, 21U) + aOrbiterI) + RotL64(aOrbiterA, 30U));
            aWandererD = aWandererD + ((((RotL64(aScatter, 48U) + RotL64(aOrbiterK, 3U)) + aOrbiterF) + RotL64(aCarry, 11U)) + aPhaseHWandererUpdateSaltE[((aIndex + 21U)) & S_SALT1]);
            aWandererG = aWandererG ^ (((RotL64(aPrevious, 3U) + aOrbiterA) + RotL64(aOrbiterB, 57U)) + aPhaseHWandererUpdateSaltF[((aIndex + 16U)) & S_SALT1]);
            aWandererC = aWandererC + (((RotL64(aCross, 37U) + aOrbiterF) + RotL64(aOrbiterA, 19U)) + RotL64(aCarry, 53U));
            aWandererI = aWandererI ^ ((RotL64(aIngress, 13U) + RotL64(aOrbiterK, 47U)) + aOrbiterI);
            //
            aCarry = aCarry + (RotL64(aWandererG, 27U) ^ aWandererI);
            aCarry = aCarry + (aWandererC ^ RotL64(aWandererH, 5U));
            aCarry = aCarry + RotL64(aWandererD, 19U);
            aCarry = aCarry + RotL64(aIngress, 58U);
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

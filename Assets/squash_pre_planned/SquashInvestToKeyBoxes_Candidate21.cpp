// SmartSquash candidate 21 of 33
// Exploration cases: 50000000
// Nearest-family diversity: 1798 / 1984 (90.62%)
// Total distance from earlier candidates: 36343
void TwistExpander_Mirfak::SquashInvestToKeyBoxes() {
    static_assert((S_BLOCK / W_KEY) == 16, "SquashInvestToKeyBoxes expects 16 invest fragments.");
    static_assert(H_KEY == 8, "SquashInvestToKeyBoxes expects 8 key rows per box.");
    if (mWorkspace == nullptr) { return; }
    std::uint8_t *aInvestLaneA = mWorkspace->mInvestLaneA;
    std::uint8_t *aInvestLaneB = mWorkspace->mInvestLaneB;
    std::uint8_t *aInvestLaneC = mWorkspace->mInvestLaneC;
    std::uint8_t *aInvestLaneD = mWorkspace->mInvestLaneD;
    std::uint8_t *aInvestLaneE = mWorkspace->mInvestLaneE;
    std::uint8_t *aInvestLaneF = mWorkspace->mInvestLaneF;
    std::uint8_t *aInvestLaneG = mWorkspace->mInvestLaneG;
    std::uint8_t *aInvestLaneH = mWorkspace->mInvestLaneH;

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 3U), *aFragmentB = aInvestLaneB + (W_KEY * 12U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 3U), *aFragmentD = aInvestLaneD + (W_KEY * 6U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 12U), *aFragmentF = aInvestLaneF + (W_KEY * 7U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 0U), *aFragmentH = aInvestLaneH + (W_KEY * 13U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 944U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1911U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1515U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1836U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1223U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1426U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 729U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1037U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 7U), *aFragmentB = aInvestLaneB + (W_KEY * 11U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 13U), *aFragmentD = aInvestLaneD + (W_KEY * 0U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 5U), *aFragmentF = aInvestLaneF + (W_KEY * 4U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 10U), *aFragmentH = aInvestLaneH + (W_KEY * 10U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1888U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 221U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1253U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1395U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1400U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1446U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 467U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 310U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 14U), *aFragmentB = aInvestLaneB + (W_KEY * 5U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 2U), *aFragmentD = aInvestLaneD + (W_KEY * 13U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 13U), *aFragmentF = aInvestLaneF + (W_KEY * 13U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 8U), *aFragmentH = aInvestLaneH + (W_KEY * 1U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1820U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 905U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 619U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 97U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 418U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1745U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1140U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1076U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 0U), *aFragmentB = aInvestLaneB + (W_KEY * 9U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 15U), *aFragmentD = aInvestLaneD + (W_KEY * 3U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 9U), *aFragmentF = aInvestLaneF + (W_KEY * 9U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 14U), *aFragmentH = aInvestLaneH + (W_KEY * 0U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 2017U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1141U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 865U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 317U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1876U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1377U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 202U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 572U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 12U), *aFragmentB = aInvestLaneB + (W_KEY * 2U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 5U), *aFragmentD = aInvestLaneD + (W_KEY * 14U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 14U), *aFragmentF = aInvestLaneF + (W_KEY * 1U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 6U), *aFragmentH = aInvestLaneH + (W_KEY * 11U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 873U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1581U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 481U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 698U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1473U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1207U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1128U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1886U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 10U), *aFragmentB = aInvestLaneB + (W_KEY * 3U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 9U), *aFragmentD = aInvestLaneD + (W_KEY * 4U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 10U), *aFragmentF = aInvestLaneF + (W_KEY * 2U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 1U), *aFragmentH = aInvestLaneH + (W_KEY * 3U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1176U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 997U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 294U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 27U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 428U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 592U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 36U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1633U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 15U), *aFragmentB = aInvestLaneB + (W_KEY * 15U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 8U), *aFragmentD = aInvestLaneD + (W_KEY * 1U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 4U), *aFragmentF = aInvestLaneF + (W_KEY * 8U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 2U), *aFragmentH = aInvestLaneH + (W_KEY * 7U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 427U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 260U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1520U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1992U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1238U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 413U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 995U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 914U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 6U), *aFragmentB = aInvestLaneB + (W_KEY * 13U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 10U), *aFragmentD = aInvestLaneD + (W_KEY * 11U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 2U), *aFragmentF = aInvestLaneF + (W_KEY * 6U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 3U), *aFragmentH = aInvestLaneH + (W_KEY * 9U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1375U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1743U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1151U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 899U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1721U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1208U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1610U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 402U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 9U), *aFragmentB = aInvestLaneB + (W_KEY * 10U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 11U), *aFragmentD = aInvestLaneD + (W_KEY * 10U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 8U), *aFragmentF = aInvestLaneF + (W_KEY * 10U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 11U), *aFragmentH = aInvestLaneH + (W_KEY * 4U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 492U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1511U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 455U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1756U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1362U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1747U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 626U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 457U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 11U), *aFragmentB = aInvestLaneB + (W_KEY * 14U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 6U), *aFragmentD = aInvestLaneD + (W_KEY * 12U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 11U), *aFragmentF = aInvestLaneF + (W_KEY * 15U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 9U), *aFragmentH = aInvestLaneH + (W_KEY * 8U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 681U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 262U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1152U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1182U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1704U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 240U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1272U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1053U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 5U), *aFragmentB = aInvestLaneB + (W_KEY * 4U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 14U), *aFragmentD = aInvestLaneD + (W_KEY * 8U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 1U), *aFragmentF = aInvestLaneF + (W_KEY * 3U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 7U), *aFragmentH = aInvestLaneH + (W_KEY * 14U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1123U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 87U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1889U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 269U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1539U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1498U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1587U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 192U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 1U), *aFragmentB = aInvestLaneB + (W_KEY * 8U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 4U), *aFragmentD = aInvestLaneD + (W_KEY * 9U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 0U), *aFragmentF = aInvestLaneF + (W_KEY * 12U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 5U), *aFragmentH = aInvestLaneH + (W_KEY * 2U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 144U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1179U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1145U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 911U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1999U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1019U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 963U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 759U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 4U), *aFragmentB = aInvestLaneB + (W_KEY * 7U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 7U), *aFragmentD = aInvestLaneD + (W_KEY * 15U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 6U), *aFragmentF = aInvestLaneF + (W_KEY * 0U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 13U), *aFragmentH = aInvestLaneH + (W_KEY * 12U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 458U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1264U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 94U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1247U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1826U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1482U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1726U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1624U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 8U), *aFragmentB = aInvestLaneB + (W_KEY * 6U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 0U), *aFragmentD = aInvestLaneD + (W_KEY * 2U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 7U), *aFragmentF = aInvestLaneF + (W_KEY * 5U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 15U), *aFragmentH = aInvestLaneH + (W_KEY * 5U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1732U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1120U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 883U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1246U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 996U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1317U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1590U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1927U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 2U), *aFragmentB = aInvestLaneB + (W_KEY * 1U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 12U), *aFragmentD = aInvestLaneD + (W_KEY * 5U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 15U), *aFragmentF = aInvestLaneF + (W_KEY * 11U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 4U), *aFragmentH = aInvestLaneH + (W_KEY * 6U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 737U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1441U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1599U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 781U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 225U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1941U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1026U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1399U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 13U), *aFragmentB = aInvestLaneB + (W_KEY * 0U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 1U), *aFragmentD = aInvestLaneD + (W_KEY * 7U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 3U), *aFragmentF = aInvestLaneF + (W_KEY * 14U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 12U), *aFragmentH = aInvestLaneH + (W_KEY * 15U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 633U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1486U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1525U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 757U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1064U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1640U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 15U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 582U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }
}

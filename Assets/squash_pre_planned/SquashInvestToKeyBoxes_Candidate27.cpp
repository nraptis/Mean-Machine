// SmartSquash candidate 27 of 33
// Exploration cases: 50000000
// Nearest-family diversity: 1796 / 1984 (90.52%)
// Total distance from earlier candidates: 47375
void TwistExpander_Regulus::SquashInvestToKeyBoxes() {
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
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 4U), *aFragmentB = aInvestLaneB + (W_KEY * 11U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 4U), *aFragmentD = aInvestLaneD + (W_KEY * 1U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 11U), *aFragmentF = aInvestLaneF + (W_KEY * 1U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 7U), *aFragmentH = aInvestLaneH + (W_KEY * 7U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1569U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 875U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 129U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 952U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1509U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 849U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 531U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1317U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 2U), *aFragmentB = aInvestLaneB + (W_KEY * 12U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 8U), *aFragmentD = aInvestLaneD + (W_KEY * 13U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 8U), *aFragmentF = aInvestLaneF + (W_KEY * 2U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 1U), *aFragmentH = aInvestLaneH + (W_KEY * 11U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1565U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1597U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1680U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 56U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1954U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1743U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 793U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 205U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 13U), *aFragmentB = aInvestLaneB + (W_KEY * 7U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 9U), *aFragmentD = aInvestLaneD + (W_KEY * 3U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 0U), *aFragmentF = aInvestLaneF + (W_KEY * 0U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 3U), *aFragmentH = aInvestLaneH + (W_KEY * 6U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1256U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 681U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1104U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1355U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1963U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 306U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 803U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1389U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 12U), *aFragmentB = aInvestLaneB + (W_KEY * 2U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 13U), *aFragmentD = aInvestLaneD + (W_KEY * 8U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 7U), *aFragmentF = aInvestLaneF + (W_KEY * 8U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 5U), *aFragmentH = aInvestLaneH + (W_KEY * 1U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 594U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1073U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1885U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1625U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 2018U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1273U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 445U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1966U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 6U), *aFragmentB = aInvestLaneB + (W_KEY * 15U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 10U), *aFragmentD = aInvestLaneD + (W_KEY * 10U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 9U), *aFragmentF = aInvestLaneF + (W_KEY * 13U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 13U), *aFragmentH = aInvestLaneH + (W_KEY * 5U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1206U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1515U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 218U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1125U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1578U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 912U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 374U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 364U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 15U), *aFragmentB = aInvestLaneB + (W_KEY * 14U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 7U), *aFragmentD = aInvestLaneD + (W_KEY * 5U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 13U), *aFragmentF = aInvestLaneF + (W_KEY * 3U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 11U), *aFragmentH = aInvestLaneH + (W_KEY * 4U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1491U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 624U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 138U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1591U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 861U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 351U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1081U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1933U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 10U), *aFragmentB = aInvestLaneB + (W_KEY * 6U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 1U), *aFragmentD = aInvestLaneD + (W_KEY * 9U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 3U), *aFragmentF = aInvestLaneF + (W_KEY * 9U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 4U), *aFragmentH = aInvestLaneH + (W_KEY * 12U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1360U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1965U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 2027U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1028U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 401U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1679U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 17U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 893U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 9U), *aFragmentB = aInvestLaneB + (W_KEY * 0U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 14U), *aFragmentD = aInvestLaneD + (W_KEY * 2U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 1U), *aFragmentF = aInvestLaneF + (W_KEY * 7U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 0U), *aFragmentH = aInvestLaneH + (W_KEY * 0U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 858U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 497U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1022U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1093U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1866U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 524U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 708U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 678U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 7U), *aFragmentB = aInvestLaneB + (W_KEY * 9U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 3U), *aFragmentD = aInvestLaneD + (W_KEY * 4U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 2U), *aFragmentF = aInvestLaneF + (W_KEY * 5U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 6U), *aFragmentH = aInvestLaneH + (W_KEY * 15U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 983U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 184U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1862U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 2029U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1455U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1881U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1178U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1452U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 8U), *aFragmentB = aInvestLaneB + (W_KEY * 4U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 11U), *aFragmentD = aInvestLaneD + (W_KEY * 0U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 15U), *aFragmentF = aInvestLaneF + (W_KEY * 12U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 15U), *aFragmentH = aInvestLaneH + (W_KEY * 10U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1025U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 998U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1213U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 2012U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1824U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 741U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1613U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1388U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 11U), *aFragmentB = aInvestLaneB + (W_KEY * 8U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 6U), *aFragmentD = aInvestLaneD + (W_KEY * 11U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 5U), *aFragmentF = aInvestLaneF + (W_KEY * 15U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 10U), *aFragmentH = aInvestLaneH + (W_KEY * 2U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1220U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1662U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1129U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1646U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 170U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 162U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 215U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 318U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 3U), *aFragmentB = aInvestLaneB + (W_KEY * 13U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 2U), *aFragmentD = aInvestLaneD + (W_KEY * 15U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 10U), *aFragmentF = aInvestLaneF + (W_KEY * 14U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 12U), *aFragmentH = aInvestLaneH + (W_KEY * 13U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 99U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1412U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1517U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 682U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1350U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1945U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1951U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1703U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 5U), *aFragmentB = aInvestLaneB + (W_KEY * 3U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 12U), *aFragmentD = aInvestLaneD + (W_KEY * 7U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 4U), *aFragmentF = aInvestLaneF + (W_KEY * 6U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 8U), *aFragmentH = aInvestLaneH + (W_KEY * 14U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1560U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1346U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 333U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 115U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 111U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1397U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 161U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 810U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 14U), *aFragmentB = aInvestLaneB + (W_KEY * 1U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 5U), *aFragmentD = aInvestLaneD + (W_KEY * 6U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 6U), *aFragmentF = aInvestLaneF + (W_KEY * 10U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 9U), *aFragmentH = aInvestLaneH + (W_KEY * 9U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1779U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 75U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 797U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 966U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1970U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1813U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1867U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 62U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 1U), *aFragmentB = aInvestLaneB + (W_KEY * 5U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 15U), *aFragmentD = aInvestLaneD + (W_KEY * 14U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 12U), *aFragmentF = aInvestLaneF + (W_KEY * 11U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 2U), *aFragmentH = aInvestLaneH + (W_KEY * 8U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 157U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 92U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 148U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 408U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 560U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1630U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1185U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 855U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 0U), *aFragmentB = aInvestLaneB + (W_KEY * 10U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 0U), *aFragmentD = aInvestLaneD + (W_KEY * 12U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 14U), *aFragmentF = aInvestLaneF + (W_KEY * 4U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 14U), *aFragmentH = aInvestLaneH + (W_KEY * 3U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1934U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 2044U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1189U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1096U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1435U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1105U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1992U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1996U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }
}

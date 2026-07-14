// SmartSquash candidate 11 of 33
// Exploration cases: 50000000
// Nearest-family diversity: 1849 / 1984 (93.20%)
// Total distance from earlier candidates: 18633
void TwistExpander_Athebyne::SquashInvestToKeyBoxes() {
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
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 12U), *aFragmentB = aInvestLaneB + (W_KEY * 3U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 9U), *aFragmentD = aInvestLaneD + (W_KEY * 3U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 3U), *aFragmentF = aInvestLaneF + (W_KEY * 3U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 2U), *aFragmentH = aInvestLaneH + (W_KEY * 6U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 76U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 2026U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1015U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1773U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1972U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1178U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1273U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 180U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 10U), *aFragmentB = aInvestLaneB + (W_KEY * 12U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 11U), *aFragmentD = aInvestLaneD + (W_KEY * 11U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 1U), *aFragmentF = aInvestLaneF + (W_KEY * 7U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 1U), *aFragmentH = aInvestLaneH + (W_KEY * 5U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 416U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1826U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1060U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 104U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 958U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 94U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 805U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1997U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 13U), *aFragmentB = aInvestLaneB + (W_KEY * 2U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 2U), *aFragmentD = aInvestLaneD + (W_KEY * 0U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 9U), *aFragmentF = aInvestLaneF + (W_KEY * 2U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 4U), *aFragmentH = aInvestLaneH + (W_KEY * 14U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1665U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 447U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 2025U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1482U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 871U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1049U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1024U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1429U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 9U), *aFragmentB = aInvestLaneB + (W_KEY * 0U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 0U), *aFragmentD = aInvestLaneD + (W_KEY * 6U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 13U), *aFragmentF = aInvestLaneF + (W_KEY * 11U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 12U), *aFragmentH = aInvestLaneH + (W_KEY * 9U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 251U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 189U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 566U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1080U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 662U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1841U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 403U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1122U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 6U), *aFragmentB = aInvestLaneB + (W_KEY * 14U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 10U), *aFragmentD = aInvestLaneD + (W_KEY * 7U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 15U), *aFragmentF = aInvestLaneF + (W_KEY * 13U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 14U), *aFragmentH = aInvestLaneH + (W_KEY * 12U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 595U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1941U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 99U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 0U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1738U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1258U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1922U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 28U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 5U), *aFragmentB = aInvestLaneB + (W_KEY * 1U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 14U), *aFragmentD = aInvestLaneD + (W_KEY * 14U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 5U), *aFragmentF = aInvestLaneF + (W_KEY * 10U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 10U), *aFragmentH = aInvestLaneH + (W_KEY * 3U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 119U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 982U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1155U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 308U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 95U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 18U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1202U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1012U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 3U), *aFragmentB = aInvestLaneB + (W_KEY * 6U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 4U), *aFragmentD = aInvestLaneD + (W_KEY * 5U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 7U), *aFragmentF = aInvestLaneF + (W_KEY * 14U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 13U), *aFragmentH = aInvestLaneH + (W_KEY * 7U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1631U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 652U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 232U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1880U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1048U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1655U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 990U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 970U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 14U), *aFragmentB = aInvestLaneB + (W_KEY * 7U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 13U), *aFragmentD = aInvestLaneD + (W_KEY * 1U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 6U), *aFragmentF = aInvestLaneF + (W_KEY * 1U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 7U), *aFragmentH = aInvestLaneH + (W_KEY * 0U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 162U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1210U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1034U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 698U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 2013U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1356U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 526U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1115U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 2U), *aFragmentB = aInvestLaneB + (W_KEY * 4U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 7U), *aFragmentD = aInvestLaneD + (W_KEY * 13U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 4U), *aFragmentF = aInvestLaneF + (W_KEY * 6U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 5U), *aFragmentH = aInvestLaneH + (W_KEY * 10U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 160U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 230U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1968U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 515U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1742U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 988U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1127U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 381U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 4U), *aFragmentB = aInvestLaneB + (W_KEY * 13U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 6U), *aFragmentD = aInvestLaneD + (W_KEY * 10U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 0U), *aFragmentF = aInvestLaneF + (W_KEY * 8U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 3U), *aFragmentH = aInvestLaneH + (W_KEY * 15U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 229U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 492U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 868U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 791U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1324U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1174U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1460U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 842U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 0U), *aFragmentB = aInvestLaneB + (W_KEY * 8U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 12U), *aFragmentD = aInvestLaneD + (W_KEY * 15U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 12U), *aFragmentF = aInvestLaneF + (W_KEY * 9U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 15U), *aFragmentH = aInvestLaneH + (W_KEY * 2U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1110U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1221U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 914U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 100U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 201U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 720U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 794U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 717U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 8U), *aFragmentB = aInvestLaneB + (W_KEY * 5U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 8U), *aFragmentD = aInvestLaneD + (W_KEY * 4U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 2U), *aFragmentF = aInvestLaneF + (W_KEY * 4U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 0U), *aFragmentH = aInvestLaneH + (W_KEY * 11U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 918U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 935U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1422U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 2021U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 387U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 505U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 428U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 171U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 7U), *aFragmentB = aInvestLaneB + (W_KEY * 15U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 15U), *aFragmentD = aInvestLaneD + (W_KEY * 8U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 10U), *aFragmentF = aInvestLaneF + (W_KEY * 15U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 9U), *aFragmentH = aInvestLaneH + (W_KEY * 13U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1932U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1791U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1082U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 696U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1136U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1411U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1650U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1578U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 1U), *aFragmentB = aInvestLaneB + (W_KEY * 10U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 5U), *aFragmentD = aInvestLaneD + (W_KEY * 9U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 14U), *aFragmentF = aInvestLaneF + (W_KEY * 12U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 8U), *aFragmentH = aInvestLaneH + (W_KEY * 8U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1114U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1087U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1815U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1391U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 751U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1829U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 457U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 223U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 11U), *aFragmentB = aInvestLaneB + (W_KEY * 9U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 3U), *aFragmentD = aInvestLaneD + (W_KEY * 2U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 11U), *aFragmentF = aInvestLaneF + (W_KEY * 5U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 6U), *aFragmentH = aInvestLaneH + (W_KEY * 1U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 2023U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 880U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1002U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1564U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1211U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 2032U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1446U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 314U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 15U), *aFragmentB = aInvestLaneB + (W_KEY * 11U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 1U), *aFragmentD = aInvestLaneD + (W_KEY * 12U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 8U), *aFragmentF = aInvestLaneF + (W_KEY * 0U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 11U), *aFragmentH = aInvestLaneH + (W_KEY * 4U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 745U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1857U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 985U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 521U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1906U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 572U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1162U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 412U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }
}

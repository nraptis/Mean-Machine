// SmartSquash candidate 9 of 33
// Exploration cases: 50000000
// Nearest-family diversity: 1861 / 1984 (93.80%)
// Total distance from earlier candidates: 14924
void TwistExpander_Antares::SquashInvestToKeyBoxes() {
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
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 9U), *aFragmentB = aInvestLaneB + (W_KEY * 14U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 7U), *aFragmentD = aInvestLaneD + (W_KEY * 7U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 10U), *aFragmentF = aInvestLaneF + (W_KEY * 13U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 0U), *aFragmentH = aInvestLaneH + (W_KEY * 10U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1107U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1450U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 485U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 723U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1440U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 960U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 493U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1071U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 2U), *aFragmentB = aInvestLaneB + (W_KEY * 13U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 2U), *aFragmentD = aInvestLaneD + (W_KEY * 0U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 7U), *aFragmentF = aInvestLaneF + (W_KEY * 10U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 12U), *aFragmentH = aInvestLaneH + (W_KEY * 15U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 605U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 434U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 116U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1438U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 721U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 672U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 78U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1875U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 12U), *aFragmentB = aInvestLaneB + (W_KEY * 15U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 14U), *aFragmentD = aInvestLaneD + (W_KEY * 8U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 3U), *aFragmentF = aInvestLaneF + (W_KEY * 7U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 8U), *aFragmentH = aInvestLaneH + (W_KEY * 13U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 100U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1346U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1259U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 349U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 748U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1218U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1201U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1881U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 10U), *aFragmentB = aInvestLaneB + (W_KEY * 4U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 15U), *aFragmentD = aInvestLaneD + (W_KEY * 13U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 12U), *aFragmentF = aInvestLaneF + (W_KEY * 12U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 10U), *aFragmentH = aInvestLaneH + (W_KEY * 6U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1360U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1640U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 283U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 647U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1124U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 179U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1235U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 15U), *aFragmentB = aInvestLaneB + (W_KEY * 7U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 6U), *aFragmentD = aInvestLaneD + (W_KEY * 15U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 11U), *aFragmentF = aInvestLaneF + (W_KEY * 11U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 2U), *aFragmentH = aInvestLaneH + (W_KEY * 11U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 483U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 518U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 71U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 949U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1399U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1604U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1163U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1619U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 11U), *aFragmentB = aInvestLaneB + (W_KEY * 8U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 11U), *aFragmentD = aInvestLaneD + (W_KEY * 9U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 2U), *aFragmentF = aInvestLaneF + (W_KEY * 0U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 7U), *aFragmentH = aInvestLaneH + (W_KEY * 8U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 21U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 301U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1437U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1101U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 77U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1700U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1194U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1095U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 0U), *aFragmentB = aInvestLaneB + (W_KEY * 5U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 8U), *aFragmentD = aInvestLaneD + (W_KEY * 14U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 0U), *aFragmentF = aInvestLaneF + (W_KEY * 9U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 6U), *aFragmentH = aInvestLaneH + (W_KEY * 5U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 938U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 2039U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1712U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 35U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1947U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1920U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1885U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 274U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 3U), *aFragmentB = aInvestLaneB + (W_KEY * 0U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 1U), *aFragmentD = aInvestLaneD + (W_KEY * 2U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 1U), *aFragmentF = aInvestLaneF + (W_KEY * 6U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 15U), *aFragmentH = aInvestLaneH + (W_KEY * 2U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 124U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 41U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 449U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1096U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 844U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1652U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 335U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1584U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 8U), *aFragmentB = aInvestLaneB + (W_KEY * 9U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 5U), *aFragmentD = aInvestLaneD + (W_KEY * 12U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 5U), *aFragmentF = aInvestLaneF + (W_KEY * 5U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 4U), *aFragmentH = aInvestLaneH + (W_KEY * 3U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1621U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 691U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1565U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1705U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 3U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 205U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1033U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 989U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 6U), *aFragmentB = aInvestLaneB + (W_KEY * 2U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 10U), *aFragmentD = aInvestLaneD + (W_KEY * 1U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 6U), *aFragmentF = aInvestLaneF + (W_KEY * 15U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 5U), *aFragmentH = aInvestLaneH + (W_KEY * 1U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1314U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 104U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 635U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 311U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1635U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 717U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 88U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1337U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 7U), *aFragmentB = aInvestLaneB + (W_KEY * 11U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 9U), *aFragmentD = aInvestLaneD + (W_KEY * 4U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 4U), *aFragmentF = aInvestLaneF + (W_KEY * 4U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 9U), *aFragmentH = aInvestLaneH + (W_KEY * 0U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 61U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 160U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 749U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 558U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1672U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 384U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1097U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 360U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 5U), *aFragmentB = aInvestLaneB + (W_KEY * 3U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 4U), *aFragmentD = aInvestLaneD + (W_KEY * 11U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 14U), *aFragmentF = aInvestLaneF + (W_KEY * 2U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 13U), *aFragmentH = aInvestLaneH + (W_KEY * 7U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 625U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 122U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 391U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1871U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 744U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 210U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 848U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1421U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 1U), *aFragmentB = aInvestLaneB + (W_KEY * 10U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 3U), *aFragmentD = aInvestLaneD + (W_KEY * 6U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 15U), *aFragmentF = aInvestLaneF + (W_KEY * 1U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 1U), *aFragmentH = aInvestLaneH + (W_KEY * 14U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1293U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1374U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1427U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 109U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 920U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 324U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1532U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 372U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 4U), *aFragmentB = aInvestLaneB + (W_KEY * 12U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 12U), *aFragmentD = aInvestLaneD + (W_KEY * 10U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 13U), *aFragmentF = aInvestLaneF + (W_KEY * 3U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 11U), *aFragmentH = aInvestLaneH + (W_KEY * 12U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 649U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 700U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 628U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 32U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1027U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1210U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1452U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 968U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 14U), *aFragmentB = aInvestLaneB + (W_KEY * 1U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 13U), *aFragmentD = aInvestLaneD + (W_KEY * 5U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 8U), *aFragmentF = aInvestLaneF + (W_KEY * 14U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 3U), *aFragmentH = aInvestLaneH + (W_KEY * 4U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 826U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1549U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 261U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 2032U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 440U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1511U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1994U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 803U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 13U), *aFragmentB = aInvestLaneB + (W_KEY * 6U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 0U), *aFragmentD = aInvestLaneD + (W_KEY * 3U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 9U), *aFragmentF = aInvestLaneF + (W_KEY * 8U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 14U), *aFragmentH = aInvestLaneH + (W_KEY * 9U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1479U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1643U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 868U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1467U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 251U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 299U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 581U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 641U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }
}

//
//  GKeyFoldA.hpp
//  MeanMachine
//

#ifndef GKeyFoldA_hpp
#define GKeyFoldA_hpp

#include "GTwistExpander.hpp"
#include "GSymbol.hpp"
#include "Random.hpp"

#include <sstream>
#include <string>
#include <vector>

class GKeyFoldA {
public:
    bool BakeGrowKeyA(TwistProgramBranch &pBranch,
                      std::string *pErrorMessage) {
        using Slot = TwistWorkSpaceSlot;
        return BakeKeyA(pBranch,
                        GSymbol::Buf(Slot::kExpansionLaneA),
                        GSymbol::Buf(Slot::kExpansionLaneB),
                        GSymbol::Buf(Slot::kExpansionLaneC),
                        GSymbol::Buf(Slot::kExpansionLaneD),
                        pErrorMessage);
    }

    bool BakeGrowKeyB(TwistProgramBranch &pBranch,
                      std::string *pErrorMessage) {
        using Slot = TwistWorkSpaceSlot;
        return BakeKeyB(pBranch,
                        GSymbol::Buf(Slot::kWorkLaneA),
                        GSymbol::Buf(Slot::kWorkLaneB),
                        GSymbol::Buf(Slot::kWorkLaneC),
                        GSymbol::Buf(Slot::kWorkLaneD),
                        pErrorMessage);
    }

private:
    static std::string Pack4(const std::string &pSourceA,
                             const std::string &pSourceB,
                             const std::string &pSourceC,
                             const std::string &pSourceD) {
        return "(static_cast<std::uint32_t>(" + pSourceA + ") << 0U) | " +
               "(static_cast<std::uint32_t>(" + pSourceB + ") << 8U) | " +
               "(static_cast<std::uint32_t>(" + pSourceC + ") << 16U) | " +
               "(static_cast<std::uint32_t>(" + pSourceD + ") << 24U)";
    }

    static std::string Pack4WithShifts(const std::string &pSourceA,
                                       const std::string &pSourceB,
                                       const std::string &pSourceC,
                                       const std::string &pSourceD,
                                       const std::vector<int> &pShifts) {
        return "(static_cast<std::uint32_t>(" + pSourceA + ") << " + SizeLiteral(pShifts[0]) + ") | " +
               "(static_cast<std::uint32_t>(" + pSourceB + ") << " + SizeLiteral(pShifts[1]) + ") | " +
               "(static_cast<std::uint32_t>(" + pSourceC + ") << " + SizeLiteral(pShifts[2]) + ") | " +
               "(static_cast<std::uint32_t>(" + pSourceD + ") << " + SizeLiteral(pShifts[3]) + ")";
    }

    static std::string ShiftedTerm(const std::string &pSource,
                                   const int pShift) {
        return "(static_cast<std::uint32_t>(" + pSource + ") << " + SizeLiteral(pShift) + ")";
    }

    static std::string Indexed(const GSymbol &pSymbol,
                               const std::string &pIndex) {
        return BufAliasName(pSymbol) + "[" + pIndex + "]";
    }

    static std::string Chunked(const GSymbol &pSymbol,
                               const int pChunk) {
        return Indexed(pSymbol, "aIndex + (W_KEY * " + std::to_string(pChunk) + "U)");
    }

    static std::string DiffuseLine(const std::string &pDest,
                                   const std::string &pMethod,
                                   const std::string &pWord) {
        return pDest + " = TwistMix32::" + pMethod + "(" + pWord + ");";
    }

    static std::string RandomDiffuse32Name() {
        switch (Random::Get(3)) {
            case 0:
                return "DiffuseA";
            case 1:
                return "DiffuseB";
            default:
                return "DiffuseC";
        }
    }

    static std::string SizeLiteral(const int pValue) {
        return std::to_string(pValue) + "U";
    }

    static std::string ShiftListText(const std::vector<int> &pShifts) {
        std::ostringstream aStream;
        for (std::size_t i = 0U; i < pShifts.size(); i += 1U) {
            if (i > 0U) {
                aStream << ", ";
            }
            aStream << SizeLiteral(pShifts[i]);
        }
        return aStream.str();
    }

    static std::vector<int> RandomByteShifts() {
        std::vector<int> aShifts = { 0, 8, 16, 24 };
        Random::Shuffle(&aShifts);
        return aShifts;
    }

    static std::vector<int> RandomFourOrder() {
        std::vector<int> aOrder = { 0, 1, 2, 3 };
        Random::Shuffle(&aOrder);
        return aOrder;
    }

    static int UniqueQuarterCount(const int pQuarterA,
                                  const int pQuarterB,
                                  const int pQuarterC,
                                  const int pQuarterD) {
        bool aSeen[4] = { false, false, false, false };
        aSeen[pQuarterA] = true;
        aSeen[pQuarterB] = true;
        aSeen[pQuarterC] = true;
        aSeen[pQuarterD] = true;

        int aCount = 0;
        for (int i = 0; i < 4; i += 1) {
            if (aSeen[i]) {
                aCount += 1;
            }
        }
        return aCount;
    }

    static bool EveryFoldRowUsesAtLeastThreeQuarters(const std::vector<int> &pQuartersA,
                                                     const std::vector<int> &pQuartersB,
                                                     const std::vector<int> &pQuartersC,
                                                     const std::vector<int> &pQuartersD) {
        for (std::size_t i = 0U; i < 4U; i += 1U) {
            if (UniqueQuarterCount(pQuartersA[i], pQuartersB[i], pQuartersC[i], pQuartersD[i]) < 3) {
                return false;
            }
        }
        return true;
    }

    static bool RandomBalancedFourOrders(std::vector<int> *pQuartersA,
                                         std::vector<int> *pQuartersB,
                                         std::vector<int> *pQuartersC,
                                         std::vector<int> *pQuartersD) {
        for (int aAttempt = 0; aAttempt < 100000; aAttempt += 1) {
            *pQuartersA = RandomFourOrder();
            *pQuartersB = RandomFourOrder();
            *pQuartersC = RandomFourOrder();
            *pQuartersD = RandomFourOrder();

            if (EveryFoldRowUsesAtLeastThreeQuarters(*pQuartersA, *pQuartersB, *pQuartersC, *pQuartersD)) {
                return true;
            }
        }
        return false;
    }

    static bool ValidateBlockLane(const GSymbol &pSymbol,
                                  const char *pLabel,
                                  std::string *pErrorMessage) {
        if (!pSymbol.IsBuf()) {
            if (pErrorMessage != nullptr) {
                *pErrorMessage = std::string("GKeyFoldA ") + pLabel + " must be a buffer symbol.";
            }
            return false;
        }
        const int aLength = pSymbol.mKey.IsValid()
            ? TwistWorkSpace::GetBufferLength(pSymbol.mKey)
            : TwistWorkSpace::GetBufferLength(pSymbol.mSlot);
        if (aLength != S_BLOCK) {
            if (pErrorMessage != nullptr) {
                *pErrorMessage = std::string("GKeyFoldA ") + pLabel + " must be block-sized.";
            }
            return false;
        }
        return true;
    }

    static bool ValidateKeyRow(const GSymbol &pSymbol,
                               std::string *pErrorMessage) {
        if (!pSymbol.IsBuf()) {
            if (pErrorMessage != nullptr) {
                *pErrorMessage = "GKeyFoldA key row must be a buffer symbol.";
            }
            return false;
        }
        const int aLength = pSymbol.mKey.IsValid()
            ? TwistWorkSpace::GetBufferLength(pSymbol.mKey)
            : TwistWorkSpace::GetBufferLength(pSymbol.mSlot);
        if (aLength != W_KEY) {
            if (pErrorMessage != nullptr) {
                *pErrorMessage = "GKeyFoldA key row must be W_KEY bytes.";
            }
            return false;
        }
        return true;
    }

    bool BakeKeyA(TwistProgramBranch &pBranch,
                  const GSymbol &pSourceA,
                  const GSymbol &pSourceB,
                  const GSymbol &pSourceC,
                  const GSymbol &pSourceD,
                  std::string *pErrorMessage) {
        if ((S_BLOCK % 4) != 0) {
            if (pErrorMessage != nullptr) {
                *pErrorMessage = "GKeyFoldA grow key A requires S_BLOCK to divide evenly by 4.";
            }
            return false;
        }
        if ((S_BLOCK % W_KEY) != 0) {
            if (pErrorMessage != nullptr) {
                *pErrorMessage = "GKeyFoldA grow key A requires S_BLOCK to divide evenly by W_KEY.";
            }
            return false;
        }
        if ((S_BLOCK / W_KEY) != 16) {
            if (pErrorMessage != nullptr) {
                *pErrorMessage = "GKeyFoldA grow key A currently expects exactly 16 W_KEY chunks.";
            }
            return false;
        }

        if (!ValidateBlockLane(pSourceA, "source A", pErrorMessage) ||
            !ValidateBlockLane(pSourceB, "source B", pErrorMessage) ||
            !ValidateBlockLane(pSourceC, "source C", pErrorMessage) ||
            !ValidateBlockLane(pSourceD, "source D", pErrorMessage)) {
            return false;
        }

        using Slot = TwistWorkSpaceSlot;
        const GSymbol aOperationA = GSymbol::Buf(Slot::kOperationLaneA);
        const GSymbol aOperationB = GSymbol::Buf(Slot::kOperationLaneB);
        const GSymbol aOperationC = GSymbol::Buf(Slot::kOperationLaneC);
        const GSymbol aOperationD = GSymbol::Buf(Slot::kOperationLaneD);
        const GSymbol aKeyRowWriteA = GSymbol::Buf(Slot::kKeyRowWriteA);
        const GSymbol aWorkA = GSymbol::Buf(Slot::kWorkLaneA);
        const GSymbol aWorkB = GSymbol::Buf(Slot::kWorkLaneB);
        const GSymbol aWorkC = GSymbol::Buf(Slot::kWorkLaneC);
        const GSymbol aWorkD = GSymbol::Buf(Slot::kWorkLaneD);
        const GSymbol aOperationLanes[4] = { aOperationA, aOperationB, aOperationC, aOperationD };

        auto AddLine = [&pBranch](const int pIndent,
                                  const std::string &pLine) {
            pBranch.AddLine(std::string(static_cast<std::size_t>(pIndent * 4), ' ') + pLine);
        };

        auto AddFoldWord = [&AddLine](const int pIndent,
                                      const std::string &pSourceA,
                                      const std::string &pSourceB,
                                      const std::string &pSourceC,
                                      const std::string &pSourceD,
                                      const std::vector<int> &pShifts) {
            AddLine(pIndent, "std::uint32_t aFoldWord =");
            AddLine(pIndent + 1, ShiftedTerm(pSourceA, pShifts[0]) + " | " +
                                 ShiftedTerm(pSourceB, pShifts[1]) + " |");
            AddLine(pIndent + 1, ShiftedTerm(pSourceC, pShifts[2]) + " | " +
                                 ShiftedTerm(pSourceD, pShifts[3]) + ";");
        };

        const std::string aInitialDiffuseName = RandomDiffuse32Name();
        const std::vector<int> aInitialByteShifts = RandomByteShifts();

        AddLine(0, "// GKeyFoldA grow_key_a_fold (start)");
        AddLine(0, "static_assert((S_BLOCK / W_KEY) == 16, \"GKeyFoldA expects 16 key-row chunks.\");");
        AddLine(0, "TwistShiftBox::ShiftKeyBoxA(pWorkSpace);");
        AddLine(0, "{");
        AddLine(1, "// read from: " + BufAliasName(pSourceA) + ", " + BufAliasName(pSourceB) + ", " + BufAliasName(pSourceC) + ", " + BufAliasName(pSourceD));
        AddLine(1, "// byte shifts: " + ShiftListText(aInitialByteShifts) + "; diffuse: " + aInitialDiffuseName);
        AddLine(1, "// write to: " + BufAliasName(aOperationA));
        AddLine(1, "for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {");
        AddFoldWord(2,
                    Indexed(pSourceA, "aIndex"),
                    Indexed(pSourceB, "aIndex"),
                    Indexed(pSourceC, "aIndex"),
                    Indexed(pSourceD, "aIndex"),
                    aInitialByteShifts);
        AddLine(2, DiffuseLine("aFoldWord", aInitialDiffuseName, "aFoldWord"));
        AddLine(2, Indexed(aOperationA, "aIndex") + " = aFoldWord;");
        AddLine(1, "}");
        AddLine(0, "}");

        const int aQuarterSize = S_BLOCK >> 2;
        const GSymbol aWorkLanes[4] = { aWorkA, aWorkB, aWorkC, aWorkD };
        std::vector<int> aSourceQuartersA;
        std::vector<int> aSourceQuartersB;
        std::vector<int> aSourceQuartersC;
        std::vector<int> aSourceQuartersD;
        if (!RandomBalancedFourOrders(&aSourceQuartersA, &aSourceQuartersB, &aSourceQuartersC, &aSourceQuartersD)) {
            if (pErrorMessage != nullptr) {
                *pErrorMessage = "GKeyFoldA grow key A could not generate fold quarters with at least 3 unique quarters per loop.";
            }
            return false;
        }
        for (int aQuarter = 0; aQuarter < 4; aQuarter += 1) {
            const std::size_t aQuarterIndex = static_cast<std::size_t>(aQuarter);
            const int aSourceQuarterA = aSourceQuartersA[aQuarterIndex];
            const int aSourceQuarterB = aSourceQuartersB[aQuarterIndex];
            const int aSourceQuarterC = aSourceQuartersC[aQuarterIndex];
            const int aSourceQuarterD = aSourceQuartersD[aQuarterIndex];
            const int aShiftA = Random::Get(aQuarterSize);
            const int aShiftB = Random::Get(aQuarterSize);
            const int aShiftC = Random::Get(aQuarterSize);
            const int aShiftD = Random::Get(aQuarterSize);
            const std::string aDiffuseName = RandomDiffuse32Name();
            const std::vector<int> aByteShifts = RandomByteShifts();

            AddLine(0, "{");
            AddLine(1, "// read from: " + BufAliasName(aOperationA) + " source quarters " +
                    std::to_string(aSourceQuarterA) + ", " +
                    std::to_string(aSourceQuarterB) + ", " +
                    std::to_string(aSourceQuarterC) + ", " +
                    std::to_string(aSourceQuarterD) + " with offsets " +
                    SizeLiteral(aShiftA) + ", " + SizeLiteral(aShiftB) + ", " + SizeLiteral(aShiftC) + ", " + SizeLiteral(aShiftD));
            AddLine(1, "// byte shifts: " + ShiftListText(aByteShifts) + "; diffuse: " + aDiffuseName);
            AddLine(1, "// write to: " + BufAliasName(aWorkLanes[aQuarter]) + " [0..<(S_BLOCK >> 2U)]");
            AddLine(1, "const std::size_t aFoldBaseA = " + std::to_string(aSourceQuarterA) + "U * (S_BLOCK >> 2U);");
            AddLine(1, "const std::size_t aFoldBaseB = " + std::to_string(aSourceQuarterB) + "U * (S_BLOCK >> 2U);");
            AddLine(1, "const std::size_t aFoldBaseC = " + std::to_string(aSourceQuarterC) + "U * (S_BLOCK >> 2U);");
            AddLine(1, "const std::size_t aFoldBaseD = " + std::to_string(aSourceQuarterD) + "U * (S_BLOCK >> 2U);");
            AddLine(1, "for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK >> 2U); aIndex += 1U) {");
            AddLine(2, "const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + " + SizeLiteral(aShiftA) + ") & ((S_BLOCK >> 2U) - 1U));");
            AddLine(2, "const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + " + SizeLiteral(aShiftB) + ") & ((S_BLOCK >> 2U) - 1U));");
            AddLine(2, "const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + " + SizeLiteral(aShiftC) + ") & ((S_BLOCK >> 2U) - 1U));");
            AddLine(2, "const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + " + SizeLiteral(aShiftD) + ") & ((S_BLOCK >> 2U) - 1U));");
            AddFoldWord(2,
                        Indexed(aOperationA, "aFoldIndexA"),
                        Indexed(aOperationA, "aFoldIndexB"),
                        Indexed(aOperationA, "aFoldIndexC"),
                        Indexed(aOperationA, "aFoldIndexD"),
                        aByteShifts);
            AddLine(2, DiffuseLine("aFoldWord", aDiffuseName, "aFoldWord"));
            AddLine(2, Indexed(aWorkLanes[aQuarter], "aIndex") + " = aFoldWord;");
            AddLine(1, "}");
            AddLine(0, "}");
        }

        for (int aLane = 0; aLane < 4; aLane += 1) {
            const int aShiftA = Random::Get(W_KEY);
            const int aShiftB = Random::Get(W_KEY);
            const int aShiftC = Random::Get(W_KEY);
            const int aShiftD = Random::Get(W_KEY);
            const std::string aDiffuseName = RandomDiffuse32Name();
            const std::vector<int> aByteShifts = RandomByteShifts();
            const std::vector<int> aFragments = RandomFourOrder();

            AddLine(0, "{");
            AddLine(1, "// read from: " + BufAliasName(aWorkLanes[aLane]) + " fragments " +
                    std::to_string(aFragments[0]) + ", " +
                    std::to_string(aFragments[1]) + ", " +
                    std::to_string(aFragments[2]) + ", " +
                    std::to_string(aFragments[3]) + " with offsets " +
                    SizeLiteral(aShiftA) + ", " + SizeLiteral(aShiftB) + ", " + SizeLiteral(aShiftC) + ", " + SizeLiteral(aShiftD));
            AddLine(1, "// byte shifts: " + ShiftListText(aByteShifts) + "; diffuse: " + aDiffuseName);
            AddLine(1, "// write to: " + BufAliasName(aOperationLanes[aLane]) + " [0..<W_KEY]");
            AddLine(1, "const std::size_t aFoldBaseA = " + std::to_string(aFragments[0]) + "U * W_KEY;");
            AddLine(1, "const std::size_t aFoldBaseB = " + std::to_string(aFragments[1]) + "U * W_KEY;");
            AddLine(1, "const std::size_t aFoldBaseC = " + std::to_string(aFragments[2]) + "U * W_KEY;");
            AddLine(1, "const std::size_t aFoldBaseD = " + std::to_string(aFragments[3]) + "U * W_KEY;");
            AddLine(1, "for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {");
            AddLine(2, "const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + " + SizeLiteral(aShiftA) + ") & W_KEY1);");
            AddLine(2, "const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + " + SizeLiteral(aShiftB) + ") & W_KEY1);");
            AddLine(2, "const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + " + SizeLiteral(aShiftC) + ") & W_KEY1);");
            AddLine(2, "const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + " + SizeLiteral(aShiftD) + ") & W_KEY1);");
            AddFoldWord(2,
                        Indexed(aWorkLanes[aLane], "aFoldIndexA"),
                        Indexed(aWorkLanes[aLane], "aFoldIndexB"),
                        Indexed(aWorkLanes[aLane], "aFoldIndexC"),
                        Indexed(aWorkLanes[aLane], "aFoldIndexD"),
                        aByteShifts);
            AddLine(2, DiffuseLine("aFoldWord", aDiffuseName, "aFoldWord"));
            AddLine(2, Indexed(aOperationLanes[aLane], "aIndex") + " = aFoldWord;");
            AddLine(1, "}");
            AddLine(0, "}");
        }

        {
            const int aShiftA = Random::Get(W_KEY);
            const int aShiftB = Random::Get(W_KEY);
            const int aShiftC = Random::Get(W_KEY);
            const int aShiftD = Random::Get(W_KEY);
            const std::string aDiffuseName = RandomDiffuse32Name();
            const std::vector<int> aByteShifts = RandomByteShifts();

            AddLine(0, "{");
            AddLine(1, "// read from: " + BufAliasName(aOperationA) + ", " + BufAliasName(aOperationB) + ", " + BufAliasName(aOperationC) + ", " + BufAliasName(aOperationD) + " [0..<W_KEY]");
            AddLine(1, "// offsets: " + SizeLiteral(aShiftA) + ", " + SizeLiteral(aShiftB) + ", " + SizeLiteral(aShiftC) + ", " + SizeLiteral(aShiftD));
            AddLine(1, "// byte shifts: " + ShiftListText(aByteShifts) + "; diffuse: " + aDiffuseName);
            AddLine(1, "// write to: " + BufAliasName(aKeyRowWriteA));
            AddLine(1, "for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {");
            AddLine(2, "const std::size_t aFoldIndexA = (aIndex + " + SizeLiteral(aShiftA) + ") & W_KEY1;");
            AddLine(2, "const std::size_t aFoldIndexB = (aIndex + " + SizeLiteral(aShiftB) + ") & W_KEY1;");
            AddLine(2, "const std::size_t aFoldIndexC = (aIndex + " + SizeLiteral(aShiftC) + ") & W_KEY1;");
            AddLine(2, "const std::size_t aFoldIndexD = (aIndex + " + SizeLiteral(aShiftD) + ") & W_KEY1;");
            AddFoldWord(2,
                        Indexed(aOperationA, "aFoldIndexA"),
                        Indexed(aOperationB, "aFoldIndexB"),
                        Indexed(aOperationC, "aFoldIndexC"),
                        Indexed(aOperationD, "aFoldIndexD"),
                        aByteShifts);
            AddLine(2, DiffuseLine("aFoldWord", aDiffuseName, "aFoldWord"));
            AddLine(2, Indexed(aKeyRowWriteA, "aIndex") + " = aFoldWord;");
            AddLine(1, "}");
            AddLine(0, "}");
        }

        AddLine(0, "// GKeyFoldA grow_key_a_fold (end)");
        return true;
    }

    bool BakeKeyB(TwistProgramBranch &pBranch,
                  const GSymbol &pSourceA,
                  const GSymbol &pSourceB,
                  const GSymbol &pSourceC,
                  const GSymbol &pSourceD,
                  std::string *pErrorMessage) {
        if ((S_BLOCK % 4) != 0) {
            if (pErrorMessage != nullptr) {
                *pErrorMessage = "GKeyFoldA grow key B requires S_BLOCK to divide evenly by 4.";
            }
            return false;
        }
        if ((S_BLOCK % W_KEY) != 0) {
            if (pErrorMessage != nullptr) {
                *pErrorMessage = "GKeyFoldA grow key B requires S_BLOCK to divide evenly by W_KEY.";
            }
            return false;
        }
        if ((S_BLOCK / W_KEY) != 16) {
            if (pErrorMessage != nullptr) {
                *pErrorMessage = "GKeyFoldA grow key B currently expects exactly 16 W_KEY chunks.";
            }
            return false;
        }

        if (!ValidateBlockLane(pSourceA, "source A", pErrorMessage) ||
            !ValidateBlockLane(pSourceB, "source B", pErrorMessage) ||
            !ValidateBlockLane(pSourceC, "source C", pErrorMessage) ||
            !ValidateBlockLane(pSourceD, "source D", pErrorMessage)) {
            return false;
        }

        using Slot = TwistWorkSpaceSlot;
        const GSymbol aOperationA = GSymbol::Buf(Slot::kOperationLaneA);
        const GSymbol aKeyRowWriteB = GSymbol::Buf(Slot::kKeyRowWriteB);
        const GSymbol aExpandA = GSymbol::Buf(Slot::kExpansionLaneA);
        const GSymbol aExpandB = GSymbol::Buf(Slot::kExpansionLaneB);
        const GSymbol aExpandC = GSymbol::Buf(Slot::kExpansionLaneC);
        const GSymbol aExpandD = GSymbol::Buf(Slot::kExpansionLaneD);

        auto AddLine = [&pBranch](const int pIndent,
                                  const std::string &pLine) {
            pBranch.AddLine(std::string(static_cast<std::size_t>(pIndent * 4), ' ') + pLine);
        };

        auto AddFoldWord = [&AddLine](const int pIndent,
                                      const std::string &pSourceA,
                                      const std::string &pSourceB,
                                      const std::string &pSourceC,
                                      const std::string &pSourceD,
                                      const std::vector<int> &pShifts) {
            AddLine(pIndent, "std::uint32_t aFoldWord =");
            AddLine(pIndent + 1, ShiftedTerm(pSourceA, pShifts[0]) + " | " +
                                 ShiftedTerm(pSourceB, pShifts[1]) + " |");
            AddLine(pIndent + 1, ShiftedTerm(pSourceC, pShifts[2]) + " | " +
                                 ShiftedTerm(pSourceD, pShifts[3]) + ";");
        };

        AddLine(0, "// GKeyFoldB grow_key_b_fold (start)");
        AddLine(0, "static_assert((S_BLOCK / W_KEY) == 16, \"GKeyFoldB expects 16 key-row chunks.\");");
        AddLine(0, "TwistShiftBox::ShiftKeyBoxB(pWorkSpace);");

        const int aQuarterSize = S_BLOCK >> 2;
        const GSymbol aExpandLanes[4] = { aExpandA, aExpandB, aExpandC, aExpandD };
        std::vector<int> aSourceQuartersA;
        std::vector<int> aSourceQuartersB;
        std::vector<int> aSourceQuartersC;
        std::vector<int> aSourceQuartersD;
        if (!RandomBalancedFourOrders(&aSourceQuartersA, &aSourceQuartersB, &aSourceQuartersC, &aSourceQuartersD)) {
            if (pErrorMessage != nullptr) {
                *pErrorMessage = "GKeyFoldA grow key B could not generate fold quarters with at least 3 unique quarters per loop.";
            }
            return false;
        }
        for (int aQuarter = 0; aQuarter < 4; aQuarter += 1) {
            const std::size_t aQuarterIndex = static_cast<std::size_t>(aQuarter);
            const int aSourceQuarterA = aSourceQuartersA[aQuarterIndex];
            const int aSourceQuarterB = aSourceQuartersB[aQuarterIndex];
            const int aSourceQuarterC = aSourceQuartersC[aQuarterIndex];
            const int aSourceQuarterD = aSourceQuartersD[aQuarterIndex];
            const int aShiftA = Random::Get(aQuarterSize);
            const int aShiftB = Random::Get(aQuarterSize);
            const int aShiftC = Random::Get(aQuarterSize);
            const int aShiftD = Random::Get(aQuarterSize);
            const std::string aDiffuseName = RandomDiffuse32Name();
            const std::vector<int> aByteShifts = RandomByteShifts();

            AddLine(0, "{");
            AddLine(1, "// read from: " + BufAliasName(pSourceA) + ", " + BufAliasName(pSourceB) + ", " + BufAliasName(pSourceC) + ", " + BufAliasName(pSourceD) +
                    " source quarters " +
                    std::to_string(aSourceQuarterA) + ", " +
                    std::to_string(aSourceQuarterB) + ", " +
                    std::to_string(aSourceQuarterC) + ", " +
                    std::to_string(aSourceQuarterD) + " with offsets " +
                    SizeLiteral(aShiftA) + ", " + SizeLiteral(aShiftB) + ", " + SizeLiteral(aShiftC) + ", " + SizeLiteral(aShiftD));
            AddLine(1, "// byte shifts: " + ShiftListText(aByteShifts) + "; diffuse: " + aDiffuseName);
            AddLine(1, "// write to: " + BufAliasName(aExpandLanes[aQuarter]) + " [0..<(S_BLOCK >> 2U)]");
            AddLine(1, "const std::size_t aFoldBaseA = " + std::to_string(aSourceQuarterA) + "U * (S_BLOCK >> 2U);");
            AddLine(1, "const std::size_t aFoldBaseB = " + std::to_string(aSourceQuarterB) + "U * (S_BLOCK >> 2U);");
            AddLine(1, "const std::size_t aFoldBaseC = " + std::to_string(aSourceQuarterC) + "U * (S_BLOCK >> 2U);");
            AddLine(1, "const std::size_t aFoldBaseD = " + std::to_string(aSourceQuarterD) + "U * (S_BLOCK >> 2U);");
            AddLine(1, "for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK >> 2U); aIndex += 1U) {");
            AddLine(2, "const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + " + SizeLiteral(aShiftA) + ") & ((S_BLOCK >> 2U) - 1U));");
            AddLine(2, "const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + " + SizeLiteral(aShiftB) + ") & ((S_BLOCK >> 2U) - 1U));");
            AddLine(2, "const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + " + SizeLiteral(aShiftC) + ") & ((S_BLOCK >> 2U) - 1U));");
            AddLine(2, "const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + " + SizeLiteral(aShiftD) + ") & ((S_BLOCK >> 2U) - 1U));");
            AddFoldWord(2,
                        Indexed(pSourceA, "aFoldIndexA"),
                        Indexed(pSourceB, "aFoldIndexB"),
                        Indexed(pSourceC, "aFoldIndexC"),
                        Indexed(pSourceD, "aFoldIndexD"),
                        aByteShifts);
            AddLine(2, DiffuseLine("aFoldWord", aDiffuseName, "aFoldWord"));
            AddLine(2, Indexed(aExpandLanes[aQuarter], "aIndex") + " = aFoldWord;");
            AddLine(1, "}");
            AddLine(0, "}");
        }

        {
            const int aShiftA = Random::Get(aQuarterSize);
            const int aShiftB = Random::Get(aQuarterSize);
            const int aShiftC = Random::Get(aQuarterSize);
            const int aShiftD = Random::Get(aQuarterSize);
            const std::string aDiffuseName = RandomDiffuse32Name();
            const std::vector<int> aByteShifts = RandomByteShifts();

            AddLine(0, "{");
            AddLine(1, "// read from: " + BufAliasName(aExpandA) + ", " + BufAliasName(aExpandB) + ", " + BufAliasName(aExpandC) + ", " + BufAliasName(aExpandD) + " [0..<(S_BLOCK >> 2U)]");
            AddLine(1, "// offsets: " + SizeLiteral(aShiftA) + ", " + SizeLiteral(aShiftB) + ", " + SizeLiteral(aShiftC) + ", " + SizeLiteral(aShiftD));
            AddLine(1, "// byte shifts: " + ShiftListText(aByteShifts) + "; diffuse: " + aDiffuseName);
            AddLine(1, "// write to: " + BufAliasName(aOperationA) + " [0..<(S_BLOCK >> 2U)]");
            AddLine(1, "for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK >> 2U); aIndex += 1U) {");
            AddLine(2, "const std::size_t aFoldIndexA = (aIndex + " + SizeLiteral(aShiftA) + ") & ((S_BLOCK >> 2U) - 1U);");
            AddLine(2, "const std::size_t aFoldIndexB = (aIndex + " + SizeLiteral(aShiftB) + ") & ((S_BLOCK >> 2U) - 1U);");
            AddLine(2, "const std::size_t aFoldIndexC = (aIndex + " + SizeLiteral(aShiftC) + ") & ((S_BLOCK >> 2U) - 1U);");
            AddLine(2, "const std::size_t aFoldIndexD = (aIndex + " + SizeLiteral(aShiftD) + ") & ((S_BLOCK >> 2U) - 1U);");
            AddFoldWord(2,
                        Indexed(aExpandA, "aFoldIndexA"),
                        Indexed(aExpandB, "aFoldIndexB"),
                        Indexed(aExpandC, "aFoldIndexC"),
                        Indexed(aExpandD, "aFoldIndexD"),
                        aByteShifts);
            AddLine(2, DiffuseLine("aFoldWord", aDiffuseName, "aFoldWord"));
            AddLine(2, Indexed(aOperationA, "aIndex") + " = aFoldWord;");
            AddLine(1, "}");
            AddLine(0, "}");
        }

        const GSymbol aFoldScratch = pSourceA;
        const std::vector<int> aSourceFragments = RandomFourOrder();
        const std::vector<int> aScratchFragments = RandomFourOrder();
        for (int aLane = 0; aLane < 4; aLane += 1) {
            const int aShiftA = Random::Get(W_KEY);
            const int aShiftB = Random::Get(W_KEY);
            const int aShiftC = Random::Get(W_KEY);
            const int aShiftD = Random::Get(W_KEY);
            const std::string aDiffuseName = RandomDiffuse32Name();
            const std::vector<int> aByteShifts = RandomByteShifts();
            const int aSourceFragment = aSourceFragments[static_cast<std::size_t>(aLane)];
            const int aScratchFragment = aScratchFragments[static_cast<std::size_t>(aLane)];

            AddLine(0, "{");
            AddLine(1, "// read from: " + BufAliasName(aOperationA) + " fragment " +
                    std::to_string(aSourceFragment) + " with offsets " +
                    SizeLiteral(aShiftA) + ", " + SizeLiteral(aShiftB) + ", " + SizeLiteral(aShiftC) + ", " + SizeLiteral(aShiftD));
            AddLine(1, "// byte shifts: " + ShiftListText(aByteShifts) + "; diffuse: " + aDiffuseName);
            AddLine(1, "// write to: " + BufAliasName(aFoldScratch) + " fragment " + std::to_string(aScratchFragment));
            AddLine(1, "const std::size_t aReadBase = " + std::to_string(aSourceFragment) + "U * W_KEY;");
            AddLine(1, "const std::size_t aWriteBase = " + std::to_string(aScratchFragment) + "U * W_KEY;");
            AddLine(1, "for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {");
            AddLine(2, "const std::size_t aFoldIndexA = aReadBase + ((aIndex + " + SizeLiteral(aShiftA) + ") & W_KEY1);");
            AddLine(2, "const std::size_t aFoldIndexB = aReadBase + ((aIndex + " + SizeLiteral(aShiftB) + ") & W_KEY1);");
            AddLine(2, "const std::size_t aFoldIndexC = aReadBase + ((aIndex + " + SizeLiteral(aShiftC) + ") & W_KEY1);");
            AddLine(2, "const std::size_t aFoldIndexD = aReadBase + ((aIndex + " + SizeLiteral(aShiftD) + ") & W_KEY1);");
            AddFoldWord(2,
                        Indexed(aOperationA, "aFoldIndexA"),
                        Indexed(aOperationA, "aFoldIndexB"),
                        Indexed(aOperationA, "aFoldIndexC"),
                        Indexed(aOperationA, "aFoldIndexD"),
                        aByteShifts);
            AddLine(2, DiffuseLine("aFoldWord", aDiffuseName, "aFoldWord"));
            AddLine(2, Indexed(aFoldScratch, "aWriteBase + aIndex") + " = aFoldWord;");
            AddLine(1, "}");
            AddLine(0, "}");
        }

        {
            const int aShiftA = Random::Get(W_KEY);
            const int aShiftB = Random::Get(W_KEY);
            const int aShiftC = Random::Get(W_KEY);
            const int aShiftD = Random::Get(W_KEY);
            const std::string aDiffuseName = RandomDiffuse32Name();
            const std::vector<int> aByteShifts = RandomByteShifts();
            const std::vector<int> aKeyFragments = RandomFourOrder();

            AddLine(0, "{");
            AddLine(1, "// read from: " + BufAliasName(aFoldScratch) + " fragments " +
                    std::to_string(aKeyFragments[0]) + ", " +
                    std::to_string(aKeyFragments[1]) + ", " +
                    std::to_string(aKeyFragments[2]) + ", " +
                    std::to_string(aKeyFragments[3]) + " [0..<W_KEY]");
            AddLine(1, "// offsets: " + SizeLiteral(aShiftA) + ", " + SizeLiteral(aShiftB) + ", " + SizeLiteral(aShiftC) + ", " + SizeLiteral(aShiftD));
            AddLine(1, "// byte shifts: " + ShiftListText(aByteShifts) + "; diffuse: " + aDiffuseName);
            AddLine(1, "// write to: " + BufAliasName(aKeyRowWriteB));
            AddLine(1, "const std::size_t aFoldBaseA = " + std::to_string(aKeyFragments[0]) + "U * W_KEY;");
            AddLine(1, "const std::size_t aFoldBaseB = " + std::to_string(aKeyFragments[1]) + "U * W_KEY;");
            AddLine(1, "const std::size_t aFoldBaseC = " + std::to_string(aKeyFragments[2]) + "U * W_KEY;");
            AddLine(1, "const std::size_t aFoldBaseD = " + std::to_string(aKeyFragments[3]) + "U * W_KEY;");
            AddLine(1, "for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {");
            AddLine(2, "const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + " + SizeLiteral(aShiftA) + ") & W_KEY1);");
            AddLine(2, "const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + " + SizeLiteral(aShiftB) + ") & W_KEY1);");
            AddLine(2, "const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + " + SizeLiteral(aShiftC) + ") & W_KEY1);");
            AddLine(2, "const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + " + SizeLiteral(aShiftD) + ") & W_KEY1);");
            AddFoldWord(2,
                        Indexed(aFoldScratch, "aFoldIndexA"),
                        Indexed(aFoldScratch, "aFoldIndexB"),
                        Indexed(aFoldScratch, "aFoldIndexC"),
                        Indexed(aFoldScratch, "aFoldIndexD"),
                        aByteShifts);
            AddLine(2, DiffuseLine("aFoldWord", aDiffuseName, "aFoldWord"));
            AddLine(2, Indexed(aKeyRowWriteB, "aIndex") + " = aFoldWord;");
            AddLine(1, "}");
            AddLine(0, "}");
        }

        AddLine(0, "// GKeyFoldB grow_key_b_fold (end)");
        return true;
    }
};

#endif /* GKeyFoldA_hpp */

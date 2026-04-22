//
//  Random.cpp
//  HomeGrownTests
//
//  Created by Lucky Squirrel on 4/3/26.
//

#include "Random.hpp"
#include <limits>

std::random_device cRandomDevice;
std::mt19937 cRandomGenerator(cRandomDevice());

void Random::Seed(uint32_t pSeed) {
    cRandomGenerator.seed(pSeed);
}

bool Random::Bool() {
    return (Get(16) > 7);
}

uint64_t Random::Get() {
    std::uniform_int_distribution<uint64_t> aDist(0, std::numeric_limits<std::uint64_t>::max());
    return aDist(cRandomGenerator);
}

uint64_t Random::Get(uint64_t pMax) {
    if (pMax <= 0) {
        return 0;
    }
    std::uniform_int_distribution<uint64_t> aDist(0, pMax - 1);
    return aDist(cRandomGenerator);
}

uint64_t Random::Get(uint64_t pMin, uint64_t pMax) {
    if (pMin >= pMax) {
        return pMin;
    }
    std::uniform_int_distribution<uint64_t> aDist(pMin, pMax);
    return aDist(cRandomGenerator);
}

float Random::GetFloat() {
    std::uniform_real_distribution<float> aDist(0.0f, 1.0f);
    return aDist(cRandomGenerator);
}

float Random::GetFloat(float pMax) {
    if (pMax <= 0.0f) {
        return 0.0f;
    }
    std::uniform_real_distribution<float> aDist(0.0f, pMax);
    return aDist(cRandomGenerator);
}

float Random::GetFloat(float pMin, float pMax) {
    if (pMin >= pMax) {
        return pMin;
    }
    std::uniform_real_distribution<float> aDist(pMin, pMax);
    return aDist(cRandomGenerator);
}

ByteString Random::GetByteString(int pLength) {
    ByteString aResult;
    if (pLength > 0) {
        aResult.Size(pLength);
        aResult.mLength = pLength;
        for (int aIndex=0; aIndex<pLength; aIndex++) {
            aResult.mData[aIndex] = (Get(4) & 0xFF);
        }
    }
    return aResult;
}

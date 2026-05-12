//
//  TwistDomains.cpp
//  MeanMachine
//
//  Created by Xenegos of the Revel on 5/7/26.
//

#include "TwistDomains.hpp"

constexpr const unsigned char *TwistDomains::GetDomainMask(TwistSaltDomain pDomain) {    
    switch (pDomain) {
        case TwistSaltDomain::kCSPRNG_Wanderera:
            return cDomainMaskkWanderers;
        case TwistSaltDomain::kCSPRNG_Orbitera:
            return cDomainMaskOrbiters;
        case TwistSaltDomain::kCSPRNG_Prisms:
            return cDomainMaskPrisms;
        case TwistSaltDomain::kCSPRNG_Carries:
            return cDomainMaskCarries;
        case TwistSaltDomain::kSources:
            return cDomainMaskSources;
        case TwistSaltDomain::kWorkLanes:
            return cDomainMaskWorkLanes;
        case TwistSaltDomain::kExpansionLanes:
            return cDomainMaskExpansionLanes;
        case TwistSaltDomain::kMaskLanes:
            return cDomainMaskMaskLanes;
        case TwistSaltDomain::kOperationLanes:
            return cDomainMaskOperationLanes;
        case TwistSaltDomain::kKeyBoxes:
            return cDomainMaskKeyBoxes;
        case TwistSaltDomain::kMaskBoxes:
            return cDomainMaskMaskBoxes;
        default:
            return cDomainUnknown;
    }
}

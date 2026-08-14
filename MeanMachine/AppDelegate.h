//
//  AppDelegate.h
//  MeanMachine
//
//  Created by John Snow on 4/20/26.
//

/*
 ==============================================================================
 COHESIVE LANE PLAN
 ==============================================================================

 Final-material rules
 --------------------

   Crystal is always the last workspace family before writing a destination:

       Crystal --TwistSquash--> destination buffer

   Ice is always the last workspace family before writing a key:

       Ice --TwistSquash::SquashKeyA--> key buffer

   "destination material" therefore means Crystal.  It does not mean the
   caller's destination pointer.  "key material" means Ice.  It does not mean
   a key-box row until the corresponding squash has completed.


 External inputs
 ---------------

   KDF and Seed begin with [source, nonce].  These are parameters, not an
   existing workspace lane family.

   Twist begins with [source, key_read_a, key_read_b].  It must not begin by
   reading Abjuration left behind by an earlier operation.

   Grow A receives cross lanes A and C.  Grow B receives cross lanes B and D.


 Global main-flow symbols
 ------------------------

   b  = Ice                 n  = Gloom
   c  = Rainbow             o  = Lightning
   d  = Alchemy             p  = Wind
   e  = Augury              q  = Shadow
   f  = Spirit              r  = Fire
   g  = Divination          s  = Kinetic
   h  = Psychic             t  = Evocation
   i  = Voodoo              u  = Runic
   j  = Spirit              v  = Abjuration
   k  = Sonic               w  = Aether
   l  = Planar              x  = Lunar
   m  = Divination          y  = Earth

   destination material = Crystal

   The repeated families are deliberate, non-overlapping generations:

       j reuses f = Spirit
       m reuses g = Divination

   A destination family is removed from its residual bucket before an
   overwrite and re-added afterward.  This makes the new write a fresh
   residual generation instead of inheriting the old generation's count.


 Shared key/grow symbols
 -----------------------

   alpha = Arcane
   beta  = Plasma
   delta = Rainbow
   mu    = Water
   pi    = Vapor
   sigma = Frost

   key material = Ice

   Key A, Key B, Grow A, and Grow B execute sequentially.  They may therefore
   share these scratch families.  Each flow must squash Ice into its final key
   row before the following flow overwrites the shared route.


 KDF flow -- repeated independently for each domain
 --------------------------------------------------

   KDF A:

       [source, nonce] -> q Shadow
       q Shadow        -> r Fire
       diffuse(input: r Fire, entropy: q Shadow) -> d Vapor
       d Vapor         -> s Kinetic

       Farm Kinetic:
           constants source = Kinetic A
           salt sources      = Kinetic B, C, D
           constants fold    = Stasis A -> Stasis B -> Stasis C
           result            = ephemeral domain bundle A

   KDF B:

       s Kinetic       -> t Evocation
       t Evocation     -> u Runic
       diffuse(input: u Runic, entropy: t Evocation) -> g Divination
       g Divination    -> v Abjuration

       Farm Abjuration:
           constants source = Abjuration A
           salt sources      = Abjuration B, C, D
           constants fold    = Stasis A -> Stasis B -> Stasis C
           result            = ephemeral domain bundle B

   KDF C:

       v Abjuration    -> w Aether
       w Aether        -> x Lunar
       diffuse(input: x Lunar, entropy: w Aether) -> y Earth
       y Earth         -> Crystal

       Farm Crystal:
           constants source = Crystal A
           salt sources      = Crystal B, C, D
           constants fold    = Stasis A -> Stasis B -> Stasis C
           result            = workspace domain bundle

   KDF does not pass a residual bucket into Seed.  Seed starts again from its
   external source and nonce.


 Seed flow
 ---------

       [source, nonce] -> b Ice
       b Ice           -> c Rainbow
       diffuse(input: c Rainbow, entropy: b Ice) -> d Alchemy

       d Alchemy       -> e Augury
       e Augury        -> f Spirit
       diffuse(input: f Spirit, entropy: e Augury) -> g Divination

       g Divination    -> h Psychic
       h Psychic       -> i Voodoo
       diffuse(input: i Voodoo, entropy: h Psychic) -> j Spirit

       j Spirit        -> k Sonic
       k Sonic         -> l Planar
       diffuse(input: l Planar, entropy: k Sonic) -> m Divination

       m Divination    -> n Gloom
       n Gloom         -> o Lightning
       diffuse(input: o Lightning, entropy: n Gloom) -> p Wind

       p Wind          -> q Shadow
       q Shadow        -> r Fire
       diffuse(input: r Fire, entropy: q Shadow) -> s Kinetic

       s Kinetic       -> t Evocation
       t Evocation     -> u Runic
       diffuse(input: u Runic, entropy: t Evocation) -> v Abjuration

       v Abjuration    -> w Aether
       w Aether        -> x Lunar
       diffuse(input: x Lunar, entropy: w Aether) -> y Earth

       y Earth         -> Crystal
       Crystal --Squash--> destination buffer

   Earth and Crystal remain intact after the destination squash.  Both are
   needed as the entry material for every independent Seed key-row flow.

   Seed writes 25 family generations across 23 distinct families.  Spirit
   and Divination are the only two families overwritten inside Seed (eight
   physical lanes).  The fixed Seed/key route overlaps on four families:
   Ice, Rainbow, Earth, and Crystal (sixteen physical lanes).

   After the fixed key-route families, Source, and Nonce are excluded, each
   independent key-row flow inherits nineteen residual families (76 lanes).
   Its five phases consume 8 + 13 + 13 + 13 + 13 = 60 distinct lanes and must
   finish with a sixteen-lane residual surplus.


 Twist flow
 ----------

       [source, key_read_a, key_read_b] -> w Aether
       w Aether                         -> x Lunar
       diffuse(input: x Lunar, entropy: w Aether) -> y Earth
       y Earth                          -> Crystal
       Crystal --Squash--> destination buffer

   Twist uses the same final Aether -> Lunar -> Earth -> Crystal suffix as KDF
   and Seed, but obtains Aether directly from the current block and key rows.


 Seed key-row flows -- Key A and Key B
 -------------------------------------

   Each key has eight independent row flows.  Every row uses its assigned
   one-sixteenth slices, but follows the same family route:

        [y Earth, Crystal] -> alpha Arcane
        alpha Arcane       -> beta Plasma
        diffuse(input: beta Plasma, entropy: alpha Arcane) -> delta Rainbow

        delta Rainbow      -> mu Water
        mu Water           -> pi Vapor
        diffuse(input: pi Vapor, entropy: mu Water) -> sigma Frost

        sigma Frost        -> Ice
        Ice --SquashKeyA/B--> corresponding key row

   Key A completes and saves each row before Key B reuses the shared scratch
   families.  Neither flow overwrites Earth or Crystal before the other has
   consumed them.


 Twist key forks
 ---------------

   Both forks consume the four full Crystal lanes left by Twist.  Celestial is
   the shared fold-through family.  The second fork may overwrite Celestial
   only after the first fork has completed its final Spirit output.

   Fork A:

       Crystal --Fold Stage I--> Celestial
       Celestial --Fold Stage II--> j Spirit, four W_KEY regions

   Fork B:

       Crystal --Fold Stage I--> Celestial
       Celestial --Fold Stage II--> m Divination, four W_KEY regions

   Both forks run before Grow A starts.  Spirit and Divination must not be
   members of the shared alpha-through-sigma scratch route.


 Grow A
 ------

       [j Spirit, cross A, cross C] -> alpha Arcane
       alpha Arcane                 -> beta Plasma
       diffuse(input: beta Plasma, entropy: alpha Arcane) -> delta Rainbow

       delta Rainbow                -> mu Water
       mu Water                     -> pi Vapor
       diffuse(input: pi Vapor, entropy: mu Water) -> sigma Frost

       sigma Frost                  -> Ice
       Ice --SquashKeyA--> key buffer A


 Grow B
 ------

       [m Divination, cross B, cross D] -> alpha Arcane
       alpha Arcane                     -> beta Plasma
       diffuse(input: beta Plasma, entropy: alpha Arcane) -> delta Rainbow

       delta Rainbow                    -> mu Water
       mu Water                         -> pi Vapor
       diffuse(input: pi Vapor, entropy: mu Water) -> sigma Frost

       sigma Frost                      -> Ice
       Ice --SquashKeyA--> key buffer B


 Execution and lifetime requirements
 -----------------------------------

   1. KDF domains execute sequentially; each domain begins from source/nonce.
   2. Seed begins from source/nonce, not from KDF residual material.
   3. Crystal is squashed non-destructively before Seed key flows or Twist
      forks consume it.
   4. Seed Key A and Key B are sequential and share their scratch families.
   5. Twist Fork A and Fork B both finish before either Grow flow begins.
   6. Grow A squashes Ice before Grow B reuses the shared scratch families.
   7. The A/B mini-grow regions and the sixteen Seed key-row slices remain
      disjoint according to their generated lane assignments.
   8. No diffuser aliases its input, entropy, or output family.


 Families reserved by this plan
 ------------------------------

   Stasis A/B/C  = TwistFarm constant-fold scratch
   Celestial     = shared TwistForkKeyHalf fold-through family

   Alchemy, Augury, Psychic, and Voodoo are early Seed-only families.  They
   replace key-route scratch at the front of Seed and remain eligible for the
   inherited key residual pool.

   Prophecy, Transmutation, Restoration, Mystical, Fuse, and Stasis D were
   removed after this plan made them unreachable.
 ==============================================================================
*/

#import <Cocoa/Cocoa.h>
#include "stdafx.hpp"

@interface AppDelegate : NSObject <NSApplicationDelegate>


@end

/*
 {
     { D, A, B },
     { J, G, H },
     { E, B, C },
     { K, H, I },
     { F, C, D },
     { A, I, J },
     { G, D, E },
     { B, J, K },
     { H, E, F },
     { C, K, A },
     { I, F, G },
 }

lead = (lead + source) + add_constant;
feedback = (feedback ^ lead) ^ xor_constant;
feedback = RotL64(feedback * multiply_constant, rotation);

*/

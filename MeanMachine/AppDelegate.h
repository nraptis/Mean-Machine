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


 KDF flow -- repeated independently for each domain
 --------------------------------------------------

   KDF A:

       [source, nonce] -> Shadow
       Shadow          -> Fire
       diffuse(input: Fire, entropy: Shadow) -> Vapor
       Vapor           -> Kinetic

   KDF B:

       Kinetic         -> Evocation
       Evocation       -> Runic
       diffuse(input: Runic, entropy: Evocation) -> Divination
       Divination      -> Abjuration

   KDF C:

       Abjuration      -> Aether
       Aether          -> Lunar
       diffuse(input: Lunar, entropy: Aether) -> Earth
       Earth           -> Crystal

   KDF does not pass a residual bucket into Seed.  Seed starts again from its
   external source and nonce.


 Seed flow
 ---------

       [source, nonce] -> Ice
       Ice             -> Rainbow
       diffuse(input: Rainbow, entropy: Ice) -> Alchemy

       Alchemy         -> Augury
       Augury          -> Spirit
       diffuse(input: Spirit, entropy: Augury) -> Divination

       Divination      -> Psychic
       Psychic         -> Voodoo
       diffuse(input: Voodoo, entropy: Psychic) -> Vapor

       Vapor           -> Sonic
       Sonic           -> Planar
       diffuse(input: Planar, entropy: Sonic) -> Frost

       Frost           -> Gloom
       Gloom           -> Lightning
       diffuse(input: Lightning, entropy: Gloom) -> Wind

       Wind            -> Shadow
       Shadow          -> Fire
       diffuse(input: Fire, entropy: Shadow) -> Kinetic

       Kinetic         -> Evocation
       Evocation       -> Runic
       diffuse(input: Runic, entropy: Evocation) -> Abjuration

       Abjuration      -> Aether
       Aether          -> Lunar
       diffuse(input: Lunar, entropy: Aether) -> Earth

       Earth           -> Crystal
       Crystal --Squash--> destination buffer

   Earth and Crystal remain intact after the destination squash.  Both are
   needed as the entry material for every independent Seed key-row flow.

   Seed writes 25 generations into 25 distinct lane families.  There is no
   family overwrite inside the main Seed flow.

   Frost and Vapor replace the old repeated Spirit and Divination writes.
   They are borrowed from the later key route.  Vapor is placed in the earlier
   Seed position because it reappears first in the key route; Frost occupies
   the later Seed position because it reappears afterward.  This pairing
   maximizes the minimum reuse distance without adding another lane family.

   Each key flow starts with 23 eligible residual families (92 physical
   lanes) after Earth and Crystal are reserved for Phase A.  Rainbow, Vapor,
   Frost, and Ice remain eligible until the phase that overwrites them.  The
   flow consumes sixty distinct residual lanes and finishes with at least
   sixteen lanes unused.


 Twist flow
 ----------

       [source, key_read_a, key_read_b] -> Aether
       Aether                           -> Lunar
       diffuse(input: Lunar, entropy: Aether) -> Earth
       Earth                            -> Crystal
       Crystal --Squash--> destination buffer

   Twist uses the same final Aether -> Lunar -> Earth -> Crystal suffix as KDF
   and Seed, but obtains Aether directly from the current block and key rows.


 Seed key-row flows -- Key A and Key B
 -------------------------------------

   Each key has eight independent row flows.  Every row uses its assigned
   one-sixteenth slices, but follows the same family route:

        [Earth, Crystal] -> Arcane
        Arcane           -> Plasma
        diffuse(input: Plasma, entropy: Arcane) -> Rainbow

        Rainbow          -> Water
        Water            -> Vapor
        diffuse(input: Vapor, entropy: Water) -> Frost

        Frost            -> Ice
        Ice --SquashKeyA/B--> corresponding key row

   Key A completes and saves each row before Key B reuses the shared scratch
   families.  Neither flow overwrites Earth or Crystal before the other has
   consumed them.


Twist key forks
---------------

   The two forks partition the Earth/Crystal pair left by Twist.  Every block
   in every tier is 512 bytes.  Fork A alternates source parity across A-D:
   odd/even/odd/even in both Earth and Crystal.  Fork B owns the complementary
   even/odd/even/odd blocks.  Together they consume every block of every
   original lane exactly once.

   The topology is constructed backward from the final key blocks so that its
   ancestry is exact rather than statistical:

       each Mu block contains two different original source lanes;
       each Lel block contains four different original source lanes;
       each Goz block contains all eight Earth/Crystal source lanes once;
       each final key block contains all eight source lanes twice.

   The topology also balances immediate predecessor lanes within every tier.
   After the ancestry is fixed, each fork assigns its 32 logical source blocks
   independently, then maps them mechanically to even or odd physical blocks.
   For every original source lane in every final key block, its two source
   blocks come from opposite physical quarters: 0 with 2, or 1 with 3.  Each
   source lane uses eight final blocks of each quarter pair, and consumes all
   eight available blocks in every quarter exactly once.  Root assignment,
   within-quarter order, and pair orientation are shuffled.  Candidate
   distance weights Mu/Lel/Goz as 4/8/12, emphasizing differences nearest the
   key output.  The final two-input Goz braid remains fixed.

   Fork A:
       alternating [Earth, Crystal] --Mu  (4 x 8 x 512)--> Celestial
       Celestial             --Lel (4 x 4 x 512)--> Alchemy
       Alchemy               --Goz (4 x 2 x 512)--> Augury
       Augury                --fixed Mix16-----> Spirit, four W_KEY regions

   Fork B:
       complementary [Earth, Crystal] --Mu  (4 x 8 x 512)--> Celestial
       Celestial            --Lel (4 x 4 x 512)--> Alchemy
       Alchemy              --Goz (4 x 2 x 512)--> Augury
       Augury               --fixed Mix16-----> Divination, four W_KEY regions

   Fork A finishes Spirit before Fork B reuses Celestial, Alchemy, and Augury.
   Both forks finish before Grow A starts.  Spirit and Divination must not be
   members of the shared Arcane-through-Frost scratch route.

 Grow A
 ------

       [Spirit, cross A, cross C] -> Arcane
       Arcane                     -> Plasma
       diffuse(input: Plasma, entropy: Arcane) -> Rainbow

       Rainbow                    -> Water
       Water                      -> Vapor
       diffuse(input: Vapor, entropy: Water) -> Frost

       Frost                      -> Ice
       Ice --SquashKeyA--> key buffer A

 Grow B
 ------

       [Divination, cross B, cross D] -> Arcane
       Arcane                          -> Plasma
       diffuse(input: Plasma, entropy: Arcane) -> Rainbow

       Rainbow                         -> Water
       Water                           -> Vapor
       diffuse(input: Vapor, entropy: Water) -> Frost

       Frost                           -> Ice
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
   Celestial     = TwistForkKeyHalf Mu scratch
   Alchemy       = TwistForkKeyHalf Lel scratch
   Augury        = TwistForkKeyHalf Goz scratch
   Spirit        = Fork A output / Grow A input
   Divination    = Fork B output / Grow B input

   Psychic and Voodoo are Seed-only families.  Alchemy and Augury remain
   eligible for Seed key residuals before the later Twist forks reuse them.
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

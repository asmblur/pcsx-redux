/*  Cheat Support for PCSX-Reloaded
 *  Copyright (C) 2009, Wei Mingzhi <whistler_wmz@users.sf.net>.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#pragma once

#include "core/psxemulator.h"

namespace PCSX {

class Cheats {
  public:
    typedef struct {
        uint32_t Addr;
        uint16_t Val;
    } CheatCode;

    typedef struct {
        char* Descr;
        int First;  // index of the first cheat code
        int n;      // number of cheat codes for this cheat
        int Enabled;
    } Cheat;

    void ClearAllCheats();

    void LoadCheats(const char* filename);
    void SaveCheats(const char* filename);

    void ApplyCheats();

    int AddCheat(const char* descr, char* code);
    void RemoveCheat(int index);
    int EditCheat(int index, const char* descr, char* code);

    void FreeCheatSearchResults();
    void FreeCheatSearchMem();
    void CheatSearchBackupMemory();

    void CheatSearchEqual8(uint8_t val);
    void CheatSearchEqual16(uint16_t val);
    void CheatSearchEqual32(uint32_t val);
    void CheatSearchNotEqual8(uint8_t val);
    void CheatSearchNotEqual16(uint16_t val);
    void CheatSearchNotEqual32(uint32_t val);
    void CheatSearchRange8(uint8_t min, uint8_t max);
    void CheatSearchRange16(uint16_t min, uint16_t max);
    void CheatSearchRange32(uint32_t min, uint32_t max);
    void CheatSearchIncreasedBy8(uint8_t val);
    void CheatSearchIncreasedBy16(uint16_t val);
    void CheatSearchIncreasedBy32(uint32_t val);
    void CheatSearchDecreasedBy8(uint8_t val);
    void CheatSearchDecreasedBy16(uint16_t val);
    void CheatSearchDecreasedBy32(uint32_t val);
    void CheatSearchIncreased8();
    void CheatSearchIncreased16();
    void CheatSearchIncreased32();
    void CheatSearchDecreased8();
    void CheatSearchDecreased16();
    void CheatSearchDecreased32();
    void CheatSearchDifferent8();
    void CheatSearchDifferent16();
    void CheatSearchDifferent32();
    void CheatSearchNoChange8();
    void CheatSearchNoChange16();
    void CheatSearchNoChange32();

#define PREVM(mem) (&g_prevM[mem])
#define PrevMu8(mem) (*(uint8_t*)PREVM(mem))
#define PrevMu16(mem) (SWAP_LE16(*(uint16_t*)PREVM(mem)))
#define PrevMu32(mem) (SWAP_LE32(*(uint32_t*)PREVM(mem)))

    // cheat types
    enum {
        CHEAT_CONST8 = 0x30,  /* 8-bit Constant Write */
        CHEAT_CONST16 = 0x80, /* 16-bit Constant Write */
        CHEAT_INC16 = 0x10,   /* 16-bit Increment */
        CHEAT_DEC16 = 0x11,   /* 16-bit Decrement */
        CHEAT_INC8 = 0x20,    /* 8-bit Increment */
        CHEAT_DEC8 = 0x21,    /* 8-bit Decrement */
        CHEAT_SLIDE = 0x50,   /* Slide Codes */
        CHEAT_MEMCPY = 0xC2,  /* Memory Copy */

        CHEAT_EQU8 = 0xE0,          /* 8-bit Equal To */
        CHEAT_NOTEQU8 = 0xE1,       /* 8-bit Not Equal To */
        CHEAT_LESSTHAN8 = 0xE2,     /* 8-bit Less Than */
        CHEAT_GREATERTHAN8 = 0xE3,  /* 8-bit Greater Than */
        CHEAT_EQU16 = 0xD0,         /* 16-bit Equal To */
        CHEAT_NOTEQU16 = 0xD1,      /* 16-bit Not Equal To */
        CHEAT_LESSTHAN16 = 0xD2,    /* 16-bit Less Than */
        CHEAT_GREATERTHAN16 = 0xD3, /* 16-bit Greater Than */
    };

  private:
    Cheat* g_cheats = NULL;
    CheatCode* g_cheatCodes = NULL;
    int g_numCodes = 0;

    int8_t* g_prevM = NULL;
    uint32_t* g_searchResults = NULL;
    int g_numSearchResults = 0;

    int g_numCheats = 0;
    int s_numCheatsAllocated = 0;
    int s_numCodesAllocated = 0;
    int s_numSearchResultsAllocated = 0;

    static const unsigned ALLOC_INCREMENT = 100;

    void CheatSearchInitBackupMemory();
    void CheatSearchAddResult(uint32_t addr);
};

}  // namespace PCSX

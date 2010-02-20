/*
  Stockfish, a UCI chess playing engine derived from Glaurung 2.1
  Copyright (C) 2004-2008 Tord Romstad (Glaurung author)
  Copyright (C) 2008-2009 Marco Costalba

  Stockfish is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  Stockfish is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#if !defined(THREAD_H_INCLUDED)
#define THREAD_H_INCLUDED


////
//// Includes
////

#include <cstring>

#include "lock.h"
#include "movepick.h"
#include "position.h"
#include "search.h"


////
//// Constants and variables
////

const int MAX_THREADS = 8;
const int ACTIVE_SPLIT_POINTS_MAX = 8;


////
//// Types
////

struct SplitPoint {
  SplitPoint *parent;
  const Position* pos;
  SearchStack sstack[MAX_THREADS][PLY_MAX_PLUS_2];
  SearchStack *parentSstack;
  int ply;
  Depth depth;
  volatile Value alpha, beta, bestValue;
  Value futilityValue;
  bool pvNode;
  int master, slaves[MAX_THREADS];
  Lock lock;
  MovePicker *mp;
  volatile int moves;
  volatile int cpus;
  bool finished;
};


struct Thread {
  SplitPoint *splitPoint;
  volatile int activeSplitPoints;
  uint64_t nodes;
  uint64_t betaCutOffs[2];
  volatile bool stopRequest;
  volatile bool running;
  volatile bool idle;
  volatile bool sleeping;
  volatile bool workIsWaiting;
  volatile bool printCurrentLineRequest;
  unsigned char pad[64]; // set some distance among local data for each thread
};


#endif // !defined(THREAD_H_INCLUDED)

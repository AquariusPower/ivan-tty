/*
 *
 *  Iter Vehemens ad Necem (IVAN)
 *  Copyright (C) Timo Kiviluoto
 *  Released under the GNU General
 *  Public License
 *
 *  See LICENSING which should be included
 *  along with this file for more details
 *
 */

#ifndef __HSCORE_H__
#define __HSCORE_H__

#include <vector>
#include <ctime>

#include "festring.h"

#ifdef LINUX
#define HIGH_SCORE_FILENAME LOCAL_STATE_DIR "/ivan-highscore.scores"
#define LOG_FILENAME LOCAL_STATE_DIR "/ivan-logfile"
#endif

class festring;

struct logentry
{
  void WriteLog(const festring& = LOG_FILENAME);
  festring Name;
  time_t Start;
  time_t End;
  int Hp;
  int Mhp;
  festring Ktyp;
  festring Killer;
  festring Kaux;
  festring Msg;
  festring Place;
  int Score;
  int Turn;
  int Tick; // ivan time
  time_t Dur; // real time
};

class highscore
{
 public:
  highscore(const festring& = HIGH_SCORE_FILENAME);
  truth Add(long, const festring&);
  void Draw() const;
  void Save(const festring& = HIGH_SCORE_FILENAME) const;
  void Load(const festring& = HIGH_SCORE_FILENAME);
  truth LastAddFailed() const;
  void AddToFile(highscore*) const;
  truth MergeToFile(highscore*) const;
  int Find(long, const festring&, time_t, long);
  const festring& GetEntry(int) const;
  long GetScore(int) const;
  long GetSize() const;
  ushort GetVersion() const { return Version; }
  void Clear();
  truth CheckVersion() const;
 private:
  truth Add(long, const festring&, time_t, long);
  std::vector<festring> Entry;
  std::vector<long> Score;
  std::vector<time_t> Time;
  std::vector<long> RandomID;
  int LastAdd;
  ushort Version;
};

#endif

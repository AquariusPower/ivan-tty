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

#ifndef __ID_H__
#define __ID_H__

#include "typedef.h"

class festring;

#define CHAR_NAME(Case) GetName(Case).CStr()
#define CHAR_DESCRIPTION(Case) GetDescription(Case).CStr()

class id
{
 public:
  virtual void AddName(festring&, int, int) const;
  virtual festring GetName(int, int) const;
  virtual void AddName(festring&, int) const;
  virtual festring GetName(int) const;
  const char* GetArticle() const { return UsesLongArticle() ? "an" : "a"; }
 protected:
  virtual const festring& GetNameSingular() const = 0;
  virtual void AddNameSingular(festring&, truth) const;
  virtual const festring& GetNamePlural() const = 0;
  virtual truth UsesLongArticle() const = 0;
  virtual truth AddRustLevelDescription(festring&, truth) const { return false; }
  virtual truth AddAdjective(festring&, truth) const;
  virtual const festring& GetAdjective() const = 0;
  virtual truth UsesLongAdjectiveArticle() const = 0;
  virtual truth AddMaterialDescription(festring&, truth) const { return false; }
  virtual const festring& GetPostFix() const = 0;
  virtual void AddPostFix(festring&) const;
  virtual int GetArticleMode() const { return 0; }
  virtual truth ShowMaterial() const { return false; }
  virtual truth AddActiveAdjective(festring&, truth) const;
};

#endif

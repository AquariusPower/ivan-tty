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

#ifndef __LTERRAS_H__
#define __LTERRAS_H__

#include "lterra.h"

OLTERRAIN(wall, olterrain)
{
 public:
  virtual int GetGlyph() const { return '#'; }
};

OLTERRAIN(decoration, olterrain)
{
 public:
  virtual int GetGlyph() const { return '~'; }
};

GLTERRAIN(solidterrain, glterrain)
{
 public:
  virtual int GetGlyph() const { return '.'; }
};

OLTERRAIN(door, olterrain)
{
 public:
  virtual truth Open(character*);
  virtual truth Close(character*);
  virtual truth CanBeOpened() const { return !Opened; }
  virtual void BeKicked(character*, int, int);
  virtual void SetIsOpened(truth What) { Opened = What; }
  virtual void Save(outputfile&) const;
  virtual void Load(inputfile&);
  virtual truth IsDoor() const { return true; }
  virtual void SetIsLocked(truth What) { Locked = What; }
  virtual truth IsLocked() const { return Locked; }
  virtual truth CanBeOpenedByAI();
  virtual void ReceiveDamage(character*, int, int);
  virtual void CreateBoobyTrap();
  virtual void ActivateBoobyTrap();
  virtual truth TryKey(item*, character*);
  virtual void SetParameters(int);
  virtual void Lock() { SetIsLocked(true); }
  virtual void HasBeenHitByItem(character*, item*, int);
  virtual truth IsTransparent() const;
  virtual int GetWalkability() const;
  virtual int GetTheoreticalWalkability() const;
  virtual void BeDestroyed();
  virtual int GetGlyph() const { if(Opened) return '\''; else return '+'; }
 protected:
  virtual void PostConstruct();
  virtual truth AddAdjective(festring&, truth) const;
  virtual void Break();
  virtual v2 GetBitmapPos(int) const;
  virtual void MakeWalkable();
  virtual void MakeNotWalkable();
  virtual int GetBoobyTrap() { return BoobyTrap; }
  virtual void SetBoobyTrap(int What) { BoobyTrap = What; }
  truth Opened;
  truth Locked;
  int BoobyTrap;
};

OLTERRAIN(stairs, olterrain)
{
 public:
  virtual int GetGlyph() const { return IsUpLink() ? '<' : '>'; }
  virtual void Save(outputfile&) const;
  virtual void Load(inputfile&);
  virtual truth Enter(truth) const;
  virtual void StepOn(character*);
  virtual void SetAttachedArea(int What) { AttachedArea = What; }
  virtual void SetAttachedEntry(int What) { AttachedEntry = What; }
  int GetAttachedArea() const { return AttachedArea; }
  int GetAttachedEntry() const { return AttachedEntry; }
 protected:
  virtual void PostConstruct();
  int AttachedArea;
  int AttachedEntry;
};

OLTERRAIN(portal, stairs)
{
 public:
  virtual int GetGlyph() const { return '\\'; }
 protected:
  virtual v2 GetBitmapPos(int) const;
};

OLTERRAIN(altar, olterrain)
{
 public:
  virtual int GetGlyph() const { return '_'; }
  virtual truth AcceptsOffers() const { return true; }
  virtual void StepOn(character*);
  virtual void BeKicked(character*, int, int);
  virtual truth ReceiveVomit(character*, liquid*);
  virtual truth Polymorph(character*);
  virtual truth SitOn(character*);
  virtual void Draw(blitdata&) const;
  virtual truth VomitingIsDangerous(const character*) const;
};

OLTERRAIN(throne, decoration)
{
 public:
  virtual int GetGlyph() const { return '_'; }
  virtual truth SitOn(character*);
};

OLTERRAIN(olterraincontainer, olterrain)
{
 public:
  virtual int GetGlyph() const { return '~'; }
  olterraincontainer();
  virtual ~olterraincontainer();
  virtual truth Open(character*);
  virtual truth CanBeOpened() const { return true; }
  virtual stack* GetContained() const { return Contained; }
  virtual void Load(inputfile&);
  virtual void Save(outputfile&) const;
  virtual void SetItemsInside(const fearray<contentscript<item> >&, int);
  virtual void Break();
  virtual truth AllowContentEmitation() const { return false; }
  virtual void PreProcessForBone();
  virtual void PostProcessForBone();
  virtual void FinalProcessForBone();
 protected:
  stack* Contained;
};

OLTERRAIN(fountain, olterrain)
{
 public:
  virtual int GetGlyph() const { return '{'; }
  virtual ~fountain();
  virtual truth SitOn(character*);
  virtual truth Drink(character*);
  virtual truth HasDrinkEffect() const { return true; }
  virtual void DryOut();
  virtual truth DipInto(item*, character*);
  virtual truth IsDipDestination() const;
  virtual material* GetSecondaryMaterial() const { return SecondaryMaterial; }
  virtual void SetSecondaryMaterial(material*, int = 0);
  virtual void ChangeSecondaryMaterial(material*, int = 0);
  void InitMaterials(material*, material*, truth = true);
  virtual void Save(outputfile&) const;
  virtual void Load(inputfile&);
  virtual int GetMaterials() const { return 2; }
  virtual material* GetMaterial(int) const;
  virtual void InitMaterials(const materialscript*, const materialscript*, truth);
  virtual truth IsFountainWithWater() const;
  virtual int GetSparkleFlags() const;
 protected:
  virtual void GenerateMaterials();
  virtual col16 GetMaterialColorB(int) const;
  virtual void AddPostFix(festring& String) const { AddContainerPostFix(String); }
  virtual truth AddAdjective(festring&, truth) const;
  virtual v2 GetBitmapPos(int) const;
  material* SecondaryMaterial;
};

OLTERRAIN(brokendoor, door)
{
 public:
  virtual void BeKicked(character*, int, int);
  virtual void ReceiveDamage(character*, int, int);
  virtual void HasBeenHitByItem(character*, item*, int);
  virtual void Break() { olterrain::Break(); }
};

GLTERRAIN(liquidterrain, glterrain)
{
 public:
  virtual int GetGlyph() const { return '~'; }
  virtual const char* SurviveMessage() const;
  virtual const char* MonsterSurviveMessage() const;
  virtual const char* DeathMessage() const;
  virtual const char* MonsterDeathVerb() const;
  virtual const char* ScoreEntry() const;
  virtual truth IsFatalToStay() const { return true; }
  virtual truth DipInto(item*, character*);
  virtual truth IsDipDestination() const { return true; }
  virtual void SurviveEffect(character*);
  virtual void AddLocationDescription(festring&) const;
 protected:
  virtual void AddPostFix(festring& String) const { AddLumpyPostFix(String); }
  virtual v2 GetBitmapPos(int) const;
};

OLTERRAIN(boulder, olterrain)
{
 public:
  virtual int GetGlyph() const { return ';'; }
};

OLTERRAIN(sign, olterrain)
{
 public:
  virtual int GetGlyph() const { return ';'; }
  virtual void Save(outputfile&) const;
  virtual void Load(inputfile&);
  virtual void SetText(const festring& What) { Text = What; }
  virtual festring GetText() const;
  virtual void AddPostFix(festring&) const;
  virtual void StepOn(character*);
 protected:
  festring Text;
};

OLTERRAIN(earth, olterrain)
{
 public:
  virtual int GetGlyph() const { return '#'; }
  virtual void Save(outputfile&) const;
  virtual void Load(inputfile&);
 protected:
  virtual void PostConstruct();
  virtual v2 GetBitmapPos(int) const;
  int PictureIndex;
};

OLTERRAIN(monsterportal, olterrain)
{
 public:
  virtual int GetGlyph() const { return '\\'; }
  monsterportal();
 protected:
  virtual v2 GetBitmapPos(int) const;
};

#endif

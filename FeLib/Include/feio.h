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

#ifndef __FEIO_H__
#define __FEIO_H__

#include "v2.h"
#include "festring.h"

typedef truth (*stringkeyhandler)(int, festring&);

class iosystem
{
 public:
//  static festring ContinueMenu(col16, col16, const festring&);
  static int StringQuestion(festring&, const festring&, col16,
			    festring::sizetype, festring::sizetype,
			    truth, stringkeyhandler = 0);
  static long NumberQuestion(const festring&, col16,
			     truth = false);
  static long ScrollBarQuestion(const festring&, v2, long, long, long,
				long, long, col16, col16, col16, int,
				int, truth, void (*)(long) = 0);
/*  static int Menu(const bitmap*, v2, const festring&,
		  const festring&, col16,
		  const festring& = CONST_S(""),
		  const festring& = CONST_S(""));*/
  static void TextScreen(const festring&, col16 = WHITE, truth = true);
  static truth IsAcceptableForStringQuestion(char);
};

#endif

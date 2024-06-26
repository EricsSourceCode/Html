// Copyright Eric Chauvin 2024
// The Java version was started in 2020.


// This is licensed under the GNU General
// Public License (GPL).  It is the
// same license that Linux has.
// https://www.gnu.org/licenses/gpl-3.0.html



#pragma once



#include "../CppBase/BasicTypes.h"
#include "../CppBase/CharBuf.h"
#include "../CppBase/Uint16Buf.h"




class HtmlFile
  {
  private:
  bool testForCopy = false;

  // URLFileDictionary urlFileDictionary;
  // URLParse urlParse;
  // StrA inURL = StrA.Empty;
  // StrA fileName = StrA.Empty;
  Uint16Buf markedUpBuf;
  Uint16Buf htmlBuf;
  Uint16Buf scriptBuf;



  // private static final StrA TagTitleStart = new
  //                              StrA( "title" );

  // private static final StrA TagTitleEnd = new
  //                               StrA( "/title" );

  // private static final StrA TagAnchorStart = new
  //                                   StrA( "a" );

  // static final StrA TagAnchorEnd = new
  //                                   StrA( "/a" );

  // private static final StrA TagHeadStart = new
  //                                StrA( "head" );

  // private static final StrA TagHeadEnd = new
  //                             StrA( "/head" );

  public:
  HtmlFile( void )
    {
    }

  HtmlFile( const HtmlFile& in )
    {
    if( in.testForCopy )
      return;

    throw "HtmlFile copy constructor.";
    }

  ~HtmlFile( void )
    {
    }

  void markUpFile( const CharBuf& fileName );
  void markupSections( const Uint16Buf& inBuf );

  };

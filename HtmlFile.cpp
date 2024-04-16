// Copyright Eric Chauvin 2024.



// This is licensed under the GNU General
// Public License (GPL).  It is the
// same license that Linux has.
// https://www.gnu.org/licenses/gpl-3.0.html



// See https://ericssourcecode.github.io/
// For guides and information.




#include "HtmlFile.h"
#include "../CppBase/FileIO.h"
#include "../CppBase/UTF8Str.h"
#include "../CppBase/StIO.h"



/*

  public HtmlFile( MainApp appToUse, URLFileDictionary
                                   useDictionary,
                                   StrA baseURL,
                                   StrA fileNameToUse )
    {
    mApp = appToUse;
    inURL = baseURL;
    urlParse = new URLParse( mApp, baseURL );
    urlFileDictionary = useDictionary;
    fileName = fileNameToUse;
    }
*/



void HtmlFile::markUpFile(
                      const CharBuf& fileName )
{
StIO::putS( "Top of markUpFile." );

CharBuf fileS;
FileIO::readAll( fileName, fileS );

const Int32 last = fileS.getLast();
if( last == 0 )
  return;

UTF8Str utf8Str;
Uint16Buf fileBuf;

// Need to check that it is really UTF8.
utf8Str.charBufToU16Buf( fileS, fileBuf );

markupSections( fileBuf );
}




/*
  public void processNewAnchorTags()
    {
    boolean isInsideAnchor = false;

    urlParse.clear();

    // if( inURL.containsStrA( new StrA( "/classified" )))
      // mApp.showStatusAsync( "\n\nClassified: " + htmlS );

    // The link tag is for style sheets.

    StrArray tagParts = htmlS.splitChar( '<' );
    final int last = tagParts.length();
    // mApp.showStatusAsync( "Before first tag: " + tagParts.getStrAt( 0 ));

    for( int count = 1; count < last; count++ )
      {
      StrA line = tagParts.getStrAt( count );

      StrA lowerLine = line.toLowerCase();
      if( !( lowerLine.startsWith( TagAnchorStart ) ||
             lowerLine.startsWith( TagAnchorEnd ) ))
        continue;

      StrArray lineParts = line.splitChar( '>' );
      final int lastPart = lineParts.length();
      if( lastPart == 0 )
        {
        mApp.showStatusAsync( "The tag doesn't have any parts." );
        mApp.showStatusAsync( "line: " + line );
        return;
        }

      if( lastPart > 2 )
        {
        // line: /span> Posting">Post comment

        // mApp.showStatusAsync( "lastPart > 2." );
        // mApp.showStatusAsync( "line: " + line );
        continue;
        }

      StrA tag = lineParts.getStrAt( 0 );
      // It's a short tag that I don't want to
      // deal with yet.
      if( tag.endsWithChar( '/' ))
        {
        // if( tag.startsWithChar( 'a' ))
          // mApp.showStatusAsync( "Short tag: " + tag );

        continue;
        }

      // mApp.showStatusAsync( "tag: " + tag );
      StrArray tagAttr = tag.splitChar( ' ' );
      final int lastAttr = tagAttr.length();
      if( lastAttr == 0 )
        {
        mApp.showStatusAsync( "lastAttr is zero for the tag." );
        mApp.showStatusAsync( "tag: " + tag );
        return;
        }

      StrA tagName = tagAttr.getStrAt( 0 );
      tagName = tagName.toLowerCase();
      // mApp.showStatusAsync( "\n\ntagName: " + tagName );

      if( tagName.equalTo( TagAnchorStart ))
        {
        // It is called an anchor tag.
        isInsideAnchor = true;
        urlParse.clear();

        for( int countA = 1; countA < lastAttr; countA++ )
          {
          StrA attr = tagAttr.getStrAt( countA );
          attr = attr.concat( new StrA( " " ));
          urlParse.addRawText( attr );
          }

        urlParse.addRawText( new StrA( " >" ));
        }

      if( tagName.equalTo( TagAnchorEnd ))
        {
        if( urlParse.processLink())
          {
          StrA link = urlParse.getLink();
          StrA linkText = urlParse.getLinkText();
          if( linkText.length() > 0 )
            {
            if( !urlFileDictionary.keyExists( link ))
              {
              mApp.showStatusAsync( "\n\nLinkText: " + linkText );
              mApp.showStatusAsync( "Link: " + link );
              URLFile uFile = new URLFile( mApp,
                                     linkText, link );
              urlFileDictionary.setValue( link, uFile );
              }
            }
          }
        }

      if( isInsideAnchor )
        {
        if( lastPart >= 2 )
          {
          urlParse.addRawText( lineParts.getStrAt( 1 ));
          }
        }
      }
    }
*/



/*
  public StrA getTitle()
    {
    boolean isInsideHeader = false;
    boolean isInsideTitle = false;

    StrArray tagParts = htmlS.splitChar( '<' );
    final int last = tagParts.length();

    StrA styleS = new StrA( "style" );
    StrA metaS = new StrA( "meta" );
    StrA linkS = new StrA( "link" );
    StrA divS = new StrA( "div" );
    StrA spanS = new StrA( "span" );
    StrA cDashData = new StrA( "c-data" );

    for( int count = 1; count < last; count++ )
      {
      StrA line = tagParts.getStrAt( count );

      if( line.startsWith( styleS ))
        continue;

      if( line.startsWith( metaS ))
        continue;

      if( line.startsWith( linkS ))
        continue;

      if( line.startsWith( divS ))
        continue;

      if( line.startsWith( spanS ))
        continue;

      if( line.startsWith( cDashData ))
        continue;

      StrArray lineParts = line.splitChar( '>' );
      final int lastPart = lineParts.length();
      if( lastPart == 0 )
        {
        mApp.showStatusAsync( "The tag doesn't have any parts." );
        mApp.showStatusAsync( "line: " + line );
        return StrA.Empty;
        }

      if( lastPart > 2 )
        {
        // line: /span> Posting">Post comment

        // mApp.showStatusAsync( "lastPart > 2." );
        // mApp.showStatusAsync( "line: " + line );
        // return;
        }

      StrA tag = lineParts.getStrAt( 0 );
      if( tag.endsWithChar( '/' ))
        {
        // It's a short tag.
        continue;
        }

      // mApp.showStatusAsync( "tag: " + tag );
      StrArray tagAttr = tag.splitChar( ' ' );
      final int lastAttr = tagAttr.length();
      if( lastAttr == 0 )
        {
        mApp.showStatusAsync( "lastAttr is zero for the tag." );
        mApp.showStatusAsync( "tag: " + tag );
        return StrA.Empty;
        }

      StrA tagName = tagAttr.getStrAt( 0 );
      tagName = tagName.toLowerCase();
      // mApp.showStatusAsync( "\n\ntagName: " + tagName );

      if( tagName.equalTo( TagHeadStart ))
        {
        isInsideHeader = true;
        continue;
        }

      if( tagName.equalTo( TagHeadEnd ))
        {
        return StrA.Empty;
        }

      if( tagName.equalTo( TagTitleStart ))
        isInsideTitle = true;

      if( tagName.equalTo( TagTitleEnd ))
        return StrA.Empty;

      // Inside the div tag there can be a title tag
      // for that division.

      if( isInsideTitle && isInsideHeader )
        {
        if( lastPart < 2 )
          {
          mApp.showStatusAsync( "Title has no text: " +
                         line );
          return StrA.Empty;
          }

        StrA result = lineParts.getStrAt( 1 ).
                           cleanUnicodeField().trim();

        return fixAmpersandChars( result );
        }
      }

    return StrA.Empty;
    }
*/



void HtmlFile::markupSections(
                      const Uint16Buf& inBuf )
{
Uint16Buf resultBuf;
resultBuf.copy( inBuf );


// CData can be commented out within a script:
// slash star  ]]><![CDATA[  star slash.
// It is to make it so it doesn't get
// interpreted.  But it's within a script.
// And then the script interprets the CData
// begin and end markers as something within
// star slash comments.  To be ignored.

// You could also have // -->
// Two slashes for comments, which comment out
// the ending --> comment marker.
// Or a script tag followed by: <!--

/*
result = result.replace(
               new StrA( "<![CDATA[" ),
           new StrA( "" + Markers.BeginCData ));

    result = result.replace(
                             new StrA( "]]>" ),
              new StrA( "" + Markers.EndCData ));

    result = result.replace(
                             new StrA( "<script" ),
                 new StrA( "" + Markers.BeginScript ));

    result = result.replace(
                             new StrA( "</script>" ),
                 new StrA( "" + Markers.EndScript ));


    result = result.replace(
                             new StrA( "<!--" ),
       new StrA( "" + Markers.BeginHtmlComment ));

    result = result.replace(
                           new StrA( "-->" ),
       new StrA( "" + Markers.EndHtmlComment ));

    boolean isInsideCData = false;
    boolean isInsideScript = false;
    boolean isInsideHtmlComment = false;
    final int last = result.length();
    for( int count = 0; count < last; count++ )
      {
      char testC = result.charAt( count );

      if( isInsideScript )
        {
        if( inURL.toString().contains(
                        "coloradomtn.edu/" ))
          {
          ScriptBuf.appendU16( testC );
          }
        }


      if( testC == Markers.BeginCData )
        {
        // This is very common.
        // if( isInsideScript )
          // mApp.showStatusAsync( "\nBegin CData inside script.\n" + fileName );

        isInsideCData = true;
        continue;
        }

      if( testC == Markers.EndCData )
        {
        isInsideCData = false;
        continue;
        }

      if( testC == Markers.BeginScript )
        {
        ScrBuilder.append( "\n" );

        if( isInsideCData )
          mApp.showStatusAsync( "\nBegin script tag inside CData.\n" + fileName );

        isInsideScript = true;
        continue;
        }

      if( testC == Markers.EndScript )
        {
        ScrBuilder.append( "\n" );

        if( isInsideCData )
          mApp.showStatusAsync( "\nEnd script tag inside CData.\n" + fileName );

        isInsideScript = false;
        continue;
        }

      if( testC == Markers.BeginHtmlComment )
        {
        // if( isInsideCData )
          // mApp.showStatusAsync( "\nBegin html comment tag inside CData.\n" + fileName );

        isInsideHtmlComment = true;
        continue;
        }

      if( testC == Markers.EndHtmlComment )
        {
        // if( isInsideCData )
          // mApp.showStatusAsync( "\nEnd html comment tag inside CData.\n" + fileName );

        isInsideHtmlComment = false;
        continue;
        }

      // if( !(isInsideCData ||
      //      isInsideScript ||
      //      isInsideHtmlComment ))
        {
        htmlBld.appendChar( testC );
        }
      }

// ==========
   // mApp.showStatusAsync(
    //            ScrBuilder.toString() + "\n" );

    htmlS = htmlBld.toStrA();

*/

markedUpBuf.copy( resultBuf );
}

#include "stdafx.h"


void parseStr(char tokenDelimiter, CString &delimitedStr, CStringArray& outputArray)
{            
     CString inputStr = delimitedStr;       
     outputArray.RemoveAll();
    
     CString tmpStr;
     int charPos;
     while(1)
       {
       charPos = inputStr.Find(tokenDelimiter);
       if (charPos == -1)   
          {
          if (inputStr.GetLength() > 0)
             {
             outputArray.Add(inputStr);
             inputStr.Empty();
             }
          break;
          }
       tmpStr = inputStr.Left(charPos);
       outputArray.Add(tmpStr);
       inputStr = inputStr.Mid(charPos+1);    
       }
}  
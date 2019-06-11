; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMultiFilezDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "MultiFilez.h"

ClassCount=2
Class1=CMultiFilezApp
Class2=CMultiFilezDlg

ResourceCount=11
Resource2=IDR_MAINFRAME
Resource3=IDR_LV_COMMANDS
Resource4=IDD_MULTIFILEZ_DIALOG
Resource5=IDR_MENU
Resource6=IDD_SPLASH
Resource7=IDD_REPORT
Resource8=IDD_ABOUT
Resource9=IDD_REGISTER
Resource10=IDR_LV_MENU
Resource11=IDR_MAIN

[CLS:CMultiFilezApp]
Type=0
HeaderFile=MultiFilez.h
ImplementationFile=MultiFilez.cpp
Filter=N

[CLS:CMultiFilezDlg]
Type=0
HeaderFile=MultiFilezDlg.h
ImplementationFile=MultiFilezDlg.cpp
Filter=W
LastObject=CMultiFilezDlg
BaseClass=CDialog
VirtualFilter=dWC



[DLG:IDD_ABOUT]
Type=1
Class=?
ControlCount=9
Control1=IDOK,button,1342242817
Control2=IDC_STATIC,static,1342177283
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,button,1342177287
Control6=IDC_VERSION,static,1342312449
Control7=IDC_INFO,static,1342177280
Control8=IDC_REGISTERED,static,1342177280
Control9=IDC_REG_EXPLORER,button,1342242816

[DLG:IDD_REGISTER]
Type=1
Class=?
ControlCount=7
Control1=IDC_STATIC,static,1342308352
Control2=IDC_REGNUMBER,edit,1350631552
Control3=IDOK,button,1342242817
Control4=IDCANCEL,button,1342242816
Control5=IDC_STATIC,static,1342177283
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,button,1342177287

[DLG:IDD_REPORT]
Type=1
Class=?
ControlCount=6
Control1=IDOK,button,1342242817
Control2=IDC_STATIC,static,1342177283
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,button,1342177287
Control6=IDC_RESULTS,SysListView32,1342275597

[DLG:IDD_SPLASH]
Type=1
Class=?
ControlCount=1
Control1=IDC_STATIC,static,1342177294

[DLG:IDD_MULTIFILEZ_DIALOG]
Type=1
Class=CMultiFilezDlg
ControlCount=30
Control1=IDC_STATIC,static,1342308352
Control2=IDC_FILTER,combobox,1344340034
Control3=IDC_STATIC,static,1342308352
Control4=IDC_WHERE,combobox,1344340034
Control5=IDC_EXPLORE,button,1342242819
Control6=IDC_DRIVES,SysTreeView32,1476464695
Control7=IDC_ADD_FILES,button,1342242816
Control8=IDC_STATIC,static,1342177297
Control9=IDC_STATIC,static,1342177792
Control10=IDC_FILES,SysListView32,1342243083
Control11=IDC_STATIC,static,1342177792
Control12=IDC_DO,combobox,1344339971
Control13=IDC_LBL_THIS,static,1342308352
Control14=IDC_REPLACE,edit,1352728708
Control15=IDC_LBL_WITH,static,1342308352
Control16=IDC_WITH,edit,1352728708
Control17=IDC_ADD_COMMAND,button,1342242816
Control18=IDC_STATIC,static,1342177804
Control19=IDC_GO,button,1342242816
Control20=IDC_STATIC,static,1342177792
Control21=IDC_STATIC,static,1342177296
Control22=IDC_LINE_CRITERIA,static,1342177296
Control23=IDC_LINE_PERFORM,static,1342177296
Control24=IDC_SUBS,button,1342242819
Control25=IDC_LINE_FILES,static,1342177296
Control26=IDC_COMMANDS,SysListView32,1342259465
Control27=IDC_CLICKCANCEL,button,1073807360
Control28=IDC_UP,button,1342242816
Control29=IDC_DOWN,button,1342242816
Control30=IDC_CHK_RESULTS,button,1342242819

[MNU:IDR_LV_COMMANDS]
Type=1
Class=?
Command1=IDM_LV_CMDDELETE
Command2=IDM_UP
Command3=IDM_DOWN
Command4=IDM_LV_CMDSELECTALL
Command5=IDM_LV_CMDDELETEALL
Command6=IDM_HELP
Command7=IDM_ABOUT
CommandCount=7

[MNU:IDR_LV_MENU]
Type=1
Class=?
Command1=IDM_OPEN
Command2=IDM_LV_DELETE
Command3=IDM_LV_SELECTALL
Command4=IDM_LV_DELETEALL
Command5=IDM_HELP
Command6=IDM_ABOUT
CommandCount=6

[MNU:IDR_MENU]
Type=1
Class=?
Command1=IDM_HELP
Command2=IDM_ABOUT
CommandCount=2

[MNU:IDR_MAIN]
Type=1
Class=?
Command1=IDM_OPEN
Command2=IDM_LV_DELETE
Command3=IDM_LV_SELECTALL
Command4=IDM_LV_DELETEALL
Command5=IDM_LV_CMDDELETE
Command6=IDM_UP
Command7=IDM_DOWN
Command8=IDM_LV_CMDSELECTALL
Command9=IDM_LV_CMDDELETEALL
Command10=IDM_HELP
Command11=IDM_ABOUT
CommandCount=11


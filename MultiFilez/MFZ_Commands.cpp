#include "stdafx.h"
#include "MultiFilezDlg.h"

void CMultiFilezDlg::DeleteFiles(CListCtrl *lv) {
  int nTot = lv->GetSelectedCount();
  for (int n=0; n < nTot; n++) {
    int nItem = lv->GetNextItem(-1, LVNI_SELECTED);
    lv->DeleteItem(nItem);
  }
}

void CMultiFilezDlg::DeleteAllFiles(CListCtrl *lv) {
  lv->DeleteAllItems();
}

void CMultiFilezDlg::SelectAllFiles(CListCtrl *lv) {
  int nTot = lv->GetItemCount();
  for (int n=0; n < nTot; n++) {
    lv->SetItemState(n, LVIS_SELECTED, LVIS_SELECTED);
  }
}

void CMultiFilezDlg::OnDown() 
{
  int nPos = m_lvCommands.GetNextItem(-1, LVNI_SELECTED);
  if (nPos == m_lvCommands.GetItemCount()-1) {
    // At the end of the line already
    return;
  }
  if (nPos == -1) {
    // nothing to do here
    return;
  }
  CString strName, strSub;
  DWORD dw = m_lvCommands.GetItemData(nPos);
  strName = m_lvCommands.GetItemText(nPos, 0);
  strSub = m_lvCommands.GetItemText(nPos, 1);
  m_lvCommands.DeleteItem(nPos);
  nPos = m_lvCommands.InsertItem(nPos+1, strName, dw);
  m_lvCommands.SetItemData(nPos, dw);
  m_lvCommands.SetItemText(nPos, 1, strSub);  
  m_lvCommands.SetItemState(nPos, LVIS_SELECTED, LVIS_SELECTED);
}

void CMultiFilezDlg::OnUp() 
{
  int nPos = m_lvCommands.GetNextItem(-1, LVNI_SELECTED);
  if (nPos == 0) {
    // At the top of the line already
    return;
  }
  if (nPos == -1) {
    // nothing to do here
    return;
  }
  CString strName, strSub;
  DWORD dw = m_lvCommands.GetItemData(nPos);
  strName = m_lvCommands.GetItemText(nPos, 0);
  strSub = m_lvCommands.GetItemText(nPos, 1);
  m_lvCommands.DeleteItem(nPos);
  nPos = m_lvCommands.InsertItem(nPos-1, strName, dw);
  m_lvCommands.SetItemData(nPos, dw);
  m_lvCommands.SetItemText(nPos, 1, strSub);  
  m_lvCommands.SetItemState(nPos, LVIS_SELECTED, LVIS_SELECTED);
}

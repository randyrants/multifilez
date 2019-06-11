#include "stdafx.h"
#include "MultiFilezDlg.h"

LRESULT CMultiFilezDlg::OnPostReports(WPARAM wParam, LPARAM lParam) {
  ShowResults();
  return 0L;
}
void CMultiFilezDlg::ShowResults()
{
  CDlgResults dlg;
  dlg.ma_str.Copy(ma_strFiles);
  dlg.ma_n.Copy(ma_nStatus);
  dlg.DoModal();
  ma_strFiles.RemoveAll();
  ma_nStatus.RemoveAll();
}

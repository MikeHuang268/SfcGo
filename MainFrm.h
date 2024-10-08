
// MainFrm.h : CMainFrame 类的接口
//

#pragma once

class CMainFrame : public CMDIFrameWnd
{
	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame();

// 特性
public:

// 操作
public:
// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 实现
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // 控件条嵌入成员
	CToolBar          m_wndToolBar;
	CStatusBar        m_wndStatusBar;

// 生成的消息映射函数
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnPaint();
	afx_msg void OnMSh();
	afx_msg void OnUpdateMSh(CCmdUI *pCmdUI);
	afx_msg void OnMPlay();
	afx_msg void OnUpdateMPlay(CCmdUI *pCmdUI);
	afx_msg void OnMPersistencestudy();
	afx_msg void OnUpdateMPersistencestudy(CCmdUI* pCmdUI);
};



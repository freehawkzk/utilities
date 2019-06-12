
// MattingResultUtilityDlg.h : 头文件
//

#pragma once
#include "document.h"
#include "opencv2/core.hpp"
#include <string>
// CMattingResultUtilityDlg 对话框
class CMattingResultUtilityDlg : public CDialogEx
{
// 构造
public:
	CMattingResultUtilityDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MATTINGRESULTUTILITY_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
    CString m_strResPath;
    int m_nUsable;
    int m_nSrcNotQualify;
    int m_nAlgorithmError;
    int m_nForeignMatter;
    int m_nTooMuch;
    int m_nNotAll;
    int m_nTotal =0;
    int m_nCurrentIndex;
    afx_msg void OnBnClickedBtnNext();
    afx_msg void OnBnClickedBtnPre();
    BOOL m_bEyeClosedLeft;
    BOOL m_bEyeClosedRight;
    BOOL m_bEyeBlowUncoveredLeft;
    BOOL m_bEyeBlowUncoveredRight;
    BOOL m_bMouthOpen;
    BOOL m_bHaveEarDrop;
    int m_nResult;
    afx_msg void OnClose();
    afx_msg void OnBnClickedBtnSet();
    afx_msg void OnBnClickedEyeopenL();
    afx_msg void OnBnClickedEyecloseL();
    afx_msg void OnBnClickedEyeopenR();
    afx_msg void OnBnClickedEyecloseR();
    afx_msg void OnBnClickedEyeblowCoverL();
    afx_msg void OnBnClickedEyeblowNotcoverL();
    afx_msg void OnBnClickedEyeblowCoverR();
    afx_msg void OnBnClickedEyeblowNotcoverR();
    afx_msg void OnBnClickedMouthO();
    afx_msg void OnBnClickedMouthC();
    afx_msg void OnBnClickedEardrop();
    afx_msg void OnBnClickedEardropNo();
    afx_msg void OnBnClickedUsable();
    afx_msg void OnBnClickedSrcnotqualify();
    afx_msg void OnBnClickedAlgorithmerror();
    afx_msg void OnBnClickedForeignmatter();
    afx_msg void OnBnClickedToomuch();
    afx_msg void OnBnClickedNotall();
    afx_msg void OnBnClickedBtnReset();

    void removeCurImgInfo();
public:
    RAPIDJSON_NAMESPACE::Document m_jsondoc;
    cv::Mat m_src;
    cv::Mat m_res;
    std::string m_str00;
    std::string m_str01;
    std::string m_str02;
    std::string m_str03;
    std::string m_str04;
    std::string m_str05;
    std::string m_str10;
    std::string m_str11;
    std::string m_str20;
    std::string m_str21;
    std::string m_str30;
    std::string m_str31;
    std::string m_str40;
    std::string m_str41;
    std::string m_str50;
    std::string m_str51;
    std::string m_str60;
    std::string m_str61;
};

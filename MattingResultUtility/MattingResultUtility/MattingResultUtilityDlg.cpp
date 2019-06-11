
// MattingResultUtilityDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MattingResultUtility.h"
#include "MattingResultUtilityDlg.h"
#include "afxdialogex.h"
#include <string>
#include <sstream>
#include <fstream>
#include "opencv2/opencv.hpp"
#include "rapidjson.h"
#include "document.h"
#include "writer.h"
#include "prettywriter.h"
#include "stringbuffer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMattingResultUtilityDlg 对话框



CMattingResultUtilityDlg::CMattingResultUtilityDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MATTINGRESULTUTILITY_DIALOG, pParent)
    , m_strResPath(_T(""))
    , m_nUsable(0)
    , m_nSrcNotQualify(0)
    , m_nAlgorithmError(0)
    , m_nForeignMatter(0)
    , m_nTooMuch(0)
    , m_nNotAll(0)
    , m_bEyeClosedLeft(FALSE)
    , m_bEyeClosedRight(FALSE)
    , m_bEyeBlowUncoveredLeft(FALSE)
    , m_bEyeBlowUncoveredRight(FALSE)
    , m_bMouthOpen(FALSE)
    , m_bHaveEarDrop(FALSE)
    , m_nResult(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMattingResultUtilityDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_ERSULTPATH, m_strResPath);
    DDX_Text(pDX, IDC_S_USABLE, m_nUsable);
    DDX_Text(pDX, IDC_S_SRCNOTQUALIFY, m_nSrcNotQualify);
    DDX_Text(pDX, IDC_S_ALGORITHMERROR, m_nAlgorithmError);
    DDX_Text(pDX, IDC_S_FOREIGNMATTER, m_nForeignMatter);
    DDX_Text(pDX, IDC_S_TOOMUCH, m_nTooMuch);
    DDX_Text(pDX, IDC_S_NOTALL, m_nNotAll);
    DDX_Radio(pDX, IDC_EYEOPEN_L, m_bEyeClosedLeft);
    DDX_Radio(pDX, IDC_EYEOPEN_R, m_bEyeClosedRight);
    DDX_Radio(pDX, IDC_EYEBLOW_COVER_L, m_bEyeBlowUncoveredLeft);
    DDX_Radio(pDX, IDC_EYEBLOW_COVER_R, m_bEyeBlowUncoveredRight);
    DDX_Radio(pDX, IDC_MOUTH_O, m_bMouthOpen);
    DDX_Radio(pDX, IDC_EARDROP, m_bHaveEarDrop);
    DDX_Radio(pDX, IDC_USABLE, m_nResult);
}

BEGIN_MESSAGE_MAP(CMattingResultUtilityDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(IDC_BTN_NEXT, &CMattingResultUtilityDlg::OnBnClickedBtnNext)
    ON_BN_CLICKED(IDC_BTN_PRE, &CMattingResultUtilityDlg::OnBnClickedBtnPre)
    ON_WM_CLOSE()
    ON_BN_CLICKED(IDC_BTN_SET, &CMattingResultUtilityDlg::OnBnClickedBtnSet)
    ON_BN_CLICKED(IDC_EYEOPEN_L, &CMattingResultUtilityDlg::OnBnClickedEyeopenL)
    ON_BN_CLICKED(IDC_EYECLOSE_L, &CMattingResultUtilityDlg::OnBnClickedEyecloseL)
    ON_BN_CLICKED(IDC_EYEOPEN_R, &CMattingResultUtilityDlg::OnBnClickedEyeopenR)
    ON_BN_CLICKED(IDC_EYECLOSE_R, &CMattingResultUtilityDlg::OnBnClickedEyecloseR)
    ON_BN_CLICKED(IDC_EYEBLOW_COVER_L, &CMattingResultUtilityDlg::OnBnClickedEyeblowCoverL)
    ON_BN_CLICKED(IDC_EYEBLOW_NOTCOVER_L, &CMattingResultUtilityDlg::OnBnClickedEyeblowNotcoverL)
    ON_BN_CLICKED(IDC_EYEBLOW_COVER_R, &CMattingResultUtilityDlg::OnBnClickedEyeblowCoverR)
    ON_BN_CLICKED(IDC_EYEBLOW_NOTCOVER_R, &CMattingResultUtilityDlg::OnBnClickedEyeblowNotcoverR)
    ON_BN_CLICKED(IDC_MOUTH_O, &CMattingResultUtilityDlg::OnBnClickedMouthO)
    ON_BN_CLICKED(IDC_MOUTH_C, &CMattingResultUtilityDlg::OnBnClickedMouthC)
    ON_BN_CLICKED(IDC_EARDROP, &CMattingResultUtilityDlg::OnBnClickedEardrop)
    ON_BN_CLICKED(IDC_EARDROP_NO, &CMattingResultUtilityDlg::OnBnClickedEardropNo)
    ON_BN_CLICKED(IDC_USABLE, &CMattingResultUtilityDlg::OnBnClickedUsable)
    ON_BN_CLICKED(IDC_SRCNOTQUALIFY, &CMattingResultUtilityDlg::OnBnClickedSrcnotqualify)
    ON_BN_CLICKED(IDC_ALGORITHMERROR, &CMattingResultUtilityDlg::OnBnClickedAlgorithmerror)
    ON_BN_CLICKED(IDC_FOREIGNMATTER, &CMattingResultUtilityDlg::OnBnClickedForeignmatter)
    ON_BN_CLICKED(IDC_TOOMUCH, &CMattingResultUtilityDlg::OnBnClickedToomuch)
    ON_BN_CLICKED(IDC_NOTALL, &CMattingResultUtilityDlg::OnBnClickedNotall)
    ON_BN_CLICKED(IDC_BTN_RESET, &CMattingResultUtilityDlg::OnBnClickedBtnReset)
END_MESSAGE_MAP()


// CMattingResultUtilityDlg 消息处理程序

BOOL CMattingResultUtilityDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
    m_strResPath = "E:\\XiongDi\\portrait_images\\globalmatting+guidedfilter\\";
    m_nCurrentIndex = 0;
    m_bEyeClosedLeft = FALSE;
    m_bEyeClosedRight = FALSE;
    m_bEyeBlowUncoveredLeft = TRUE;
    m_bEyeBlowUncoveredRight = TRUE;
    m_bMouthOpen = FALSE;
    m_bHaveEarDrop = FALSE;
    m_nResult = 0;

    // read json content into string.
    std::string      stringFromStream;
    std::ifstream    in;
    in.open("./datas/infos-bak.json", std::ifstream::in);
    if (!in.is_open())
        return FALSE;
    std::string line;
    while (getline(in, line)) {
        stringFromStream.append(line + "\n");
    }
    in.close();

    m_jsondoc.Parse<0>(stringFromStream.c_str());
    if (m_jsondoc.HasParseError())
    {
        rapidjson::ParseErrorCode code = m_jsondoc.GetParseError();
        return FALSE;
    }

    UpdateData(FALSE);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMattingResultUtilityDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMattingResultUtilityDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMattingResultUtilityDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMattingResultUtilityDlg::OnBnClickedBtnNext()
{
    // TODO: 在此添加控件通知处理程序代码
    USES_CONVERSION;
    m_nCurrentIndex++;
    CStringA strCurDstImg;
    strCurDstImg.Format("%d-dst.jpg", m_nCurrentIndex);
    strCurDstImg = W2A(m_strResPath) + strCurDstImg;

    CStringA strCurSrcImg;
    strCurSrcImg.Format("%d-src.jpg", m_nCurrentIndex);
    strCurSrcImg = W2A(m_strResPath )+ strCurSrcImg;

    m_src = cv::imread(strCurSrcImg.GetBuffer(strCurSrcImg.GetLength()));
    strCurSrcImg.ReleaseBuffer();
    m_res = cv::imread(strCurDstImg.GetBuffer(strCurDstImg.GetLength()));
    strCurDstImg.ReleaseBuffer();
    if (!m_src.empty())
    {
        cv::imshow("src", m_src);
    }
    if (!m_res.empty())
    {
        cv::imshow("res", m_res);
    }
    
}


void CMattingResultUtilityDlg::OnBnClickedBtnPre()
{
    // TODO: 在此添加控件通知处理程序代码
    USES_CONVERSION;
    m_nCurrentIndex--;
    CStringA strCurDstImg;
    strCurDstImg.Format("%d-dst.jpg", m_nCurrentIndex);
    strCurDstImg = W2A(m_strResPath) + strCurDstImg;

    CStringA strCurSrcImg;
    strCurSrcImg.Format("%d-src.jpg", m_nCurrentIndex);
    strCurSrcImg = W2A(m_strResPath) + strCurSrcImg;

    m_src = cv::imread(strCurSrcImg.GetBuffer(strCurSrcImg.GetLength()));
    strCurSrcImg.ReleaseBuffer();
    m_res = cv::imread(strCurDstImg.GetBuffer(strCurDstImg.GetLength()));
    strCurDstImg.ReleaseBuffer();
    if (!m_src.empty())
    {
        cv::imshow("src", m_src);
    }
    if (!m_res.empty())
    {
        cv::imshow("res", m_res);
    }
    
}


void CMattingResultUtilityDlg::OnClose()
{
    // TODO: 在此添加消息处理程序代码和/或调用默认值
    RAPIDJSON_NAMESPACE::StringBuffer buffer;
    RAPIDJSON_NAMESPACE::PrettyWriter<RAPIDJSON_NAMESPACE::StringBuffer> writer(buffer);
    m_jsondoc.Accept(writer);


    std::string sinfo = buffer.GetString();

    std::ofstream of("./datas/infos.json");
    of << sinfo << std::endl;
    of.close();
    cv::destroyAllWindows();
    CDialogEx::OnClose();
}


void CMattingResultUtilityDlg::OnBnClickedBtnSet()
{
    // TODO: 在此添加控件通知处理程序代码
    UpdateData(TRUE);
    USES_CONVERSION;
    CStringA jsonPath;
    jsonPath.Format("%d.json", m_nCurrentIndex);
    jsonPath = W2A(m_strResPath) + jsonPath;
    CStringA srcImgPath; srcImgPath.Format("%d-src.jpg", m_nCurrentIndex); srcImgPath = W2A(m_strResPath) + srcImgPath;
    CStringA resImgPath; resImgPath.Format("%d-dst.jpg", m_nCurrentIndex); resImgPath = W2A(m_strResPath) + resImgPath;
    CStringA dstsrcImgPath;
    CStringA dstresImgPath;
    if (m_bEyeClosedLeft)
    {
        if (m_jsondoc.HasMember("lefteyeclosed"))
        {
            RAPIDJSON_NAMESPACE::Value& v = m_jsondoc["lefteyeclosed"];
            if (v.IsArray())
            {
                v.PushBack(m_nCurrentIndex, m_jsondoc.GetAllocator());
            }
        }
        dstsrcImgPath.Format("./datas/lefteyeclosed/%d-src.jpg", m_nCurrentIndex);
        dstresImgPath.Format("./datas/lefteyeclosed/%d-dst.jpg", m_nCurrentIndex);
        cv::imwrite(dstsrcImgPath.GetBuffer(dstsrcImgPath.GetLength()), m_src); dstsrcImgPath.ReleaseBuffer();
        cv::imwrite(dstresImgPath.GetBuffer(dstresImgPath.GetLength()), m_res); dstresImgPath.ReleaseBuffer();
    }
    else
    {
        if (m_jsondoc.HasMember("lefteyeopen"))
        {
            RAPIDJSON_NAMESPACE::Value& v = m_jsondoc["lefteyeopen"];
            if (v.IsArray())
            {
                v.PushBack(m_nCurrentIndex, m_jsondoc.GetAllocator());
            }
        }
        dstsrcImgPath.Format("./datas/lefteyeopen/%d-src.jpg", m_nCurrentIndex);
        dstresImgPath.Format("./datas/lefteyeopen/%d-dst.jpg", m_nCurrentIndex);
        cv::imwrite(dstsrcImgPath.GetBuffer(dstsrcImgPath.GetLength()), m_src); dstsrcImgPath.ReleaseBuffer();
        cv::imwrite(dstresImgPath.GetBuffer(dstresImgPath.GetLength()), m_res); dstresImgPath.ReleaseBuffer();
    }

    if (m_bEyeClosedRight)
    {
        if (m_jsondoc.HasMember("righteyeclosed"))
        {
            RAPIDJSON_NAMESPACE::Value& v = m_jsondoc["righteyeclosed"];
            if (v.IsArray())
            {
                v.PushBack(m_nCurrentIndex, m_jsondoc.GetAllocator());
            }
        }
        dstsrcImgPath.Format("./datas/righteyeclosed/%d-src.jpg", m_nCurrentIndex);
        dstresImgPath.Format("./datas/righteyeclosed/%d-dst.jpg", m_nCurrentIndex);
        cv::imwrite(dstsrcImgPath.GetBuffer(dstsrcImgPath.GetLength()), m_src); dstsrcImgPath.ReleaseBuffer();
        cv::imwrite(dstresImgPath.GetBuffer(dstresImgPath.GetLength()), m_res); dstresImgPath.ReleaseBuffer();
    }
    else
    {
        if (m_jsondoc.HasMember("righteyeopen"))
        {
            RAPIDJSON_NAMESPACE::Value& v = m_jsondoc["righteyeopen"];
            if (v.IsArray())
            {
                v.PushBack(m_nCurrentIndex, m_jsondoc.GetAllocator());
            }
        }
        dstsrcImgPath.Format("./datas/righteyeopen/%d-src.jpg", m_nCurrentIndex);
        dstresImgPath.Format("./datas/righteyeopen/%d-dst.jpg", m_nCurrentIndex);
        cv::imwrite(dstsrcImgPath.GetBuffer(dstsrcImgPath.GetLength()), m_src); dstsrcImgPath.ReleaseBuffer();
        cv::imwrite(dstresImgPath.GetBuffer(dstresImgPath.GetLength()), m_res); dstresImgPath.ReleaseBuffer();
    }

    if (m_bEyeBlowUncoveredLeft)
    {
        if (m_jsondoc.HasMember("lefteyeblowuncovered"))
        {
            RAPIDJSON_NAMESPACE::Value& v = m_jsondoc["lefteyeblowuncovered"];
            if (v.IsArray())
            {
                v.PushBack(m_nCurrentIndex, m_jsondoc.GetAllocator());
            }
        }
        dstsrcImgPath.Format("./datas/lefteyeblowuncovered/%d-src.jpg", m_nCurrentIndex);
        dstresImgPath.Format("./datas/lefteyeblowuncovered/%d-dst.jpg", m_nCurrentIndex);
        cv::imwrite(dstsrcImgPath.GetBuffer(dstsrcImgPath.GetLength()), m_src); dstsrcImgPath.ReleaseBuffer();
        cv::imwrite(dstresImgPath.GetBuffer(dstresImgPath.GetLength()), m_res); dstresImgPath.ReleaseBuffer();
    }
    else
    {
        if (m_jsondoc.HasMember("lefteyeblowcovered"))
        {
            RAPIDJSON_NAMESPACE::Value& v = m_jsondoc["lefteyeblowcovered"];
            if (v.IsArray())
            {
                v.PushBack(m_nCurrentIndex, m_jsondoc.GetAllocator());
            }
        }
        dstsrcImgPath.Format("./datas/lefteyeblowcovered/%d-src.jpg", m_nCurrentIndex);
        dstresImgPath.Format("./datas/lefteyeblowcovered/%d-dst.jpg", m_nCurrentIndex);
        cv::imwrite(dstsrcImgPath.GetBuffer(dstsrcImgPath.GetLength()), m_src); dstsrcImgPath.ReleaseBuffer();
        cv::imwrite(dstresImgPath.GetBuffer(dstresImgPath.GetLength()), m_res); dstresImgPath.ReleaseBuffer();
    }

    if (m_bEyeBlowUncoveredRight)
    {
        if (m_jsondoc.HasMember("righteyeblowuncovered"))
        {
            RAPIDJSON_NAMESPACE::Value& v = m_jsondoc["righteyeblowuncovered"];
            if (v.IsArray())
            {
                v.PushBack(m_nCurrentIndex, m_jsondoc.GetAllocator());
            }
        }
        dstsrcImgPath.Format("./datas/righteyeblowuncovered/%d-src.jpg", m_nCurrentIndex);
        dstresImgPath.Format("./datas/righteyeblowuncovered/%d-dst.jpg", m_nCurrentIndex);
        cv::imwrite(dstsrcImgPath.GetBuffer(dstsrcImgPath.GetLength()), m_src); dstsrcImgPath.ReleaseBuffer();
        cv::imwrite(dstresImgPath.GetBuffer(dstresImgPath.GetLength()), m_res); dstresImgPath.ReleaseBuffer();
    }
    else
    {
        if (m_jsondoc.HasMember("righteyeblowcovered"))
        {
            RAPIDJSON_NAMESPACE::Value& v = m_jsondoc["righteyeblowcovered"];
            if (v.IsArray())
            {
                v.PushBack(m_nCurrentIndex, m_jsondoc.GetAllocator());
            }
        }
        dstsrcImgPath.Format("./datas/righteyeblowcovered/%d-src.jpg", m_nCurrentIndex);
        dstresImgPath.Format("./datas/righteyeblowcovered/%d-dst.jpg", m_nCurrentIndex);
        cv::imwrite(dstsrcImgPath.GetBuffer(dstsrcImgPath.GetLength()), m_src); dstsrcImgPath.ReleaseBuffer();
        cv::imwrite(dstresImgPath.GetBuffer(dstresImgPath.GetLength()), m_res); dstresImgPath.ReleaseBuffer();
    }

    if (m_bMouthOpen)
    {
        if (m_jsondoc.HasMember("mouthopen"))
        {
            RAPIDJSON_NAMESPACE::Value& v = m_jsondoc["mouthopen"];
            if (v.IsArray())
            {
                v.PushBack(m_nCurrentIndex, m_jsondoc.GetAllocator());
            }
        }
        dstsrcImgPath.Format("./datas/mouthopen/%d-src.jpg", m_nCurrentIndex);
        dstresImgPath.Format("./datas/mouthopen/%d-dst.jpg", m_nCurrentIndex);
        cv::imwrite(dstsrcImgPath.GetBuffer(dstsrcImgPath.GetLength()), m_src); dstsrcImgPath.ReleaseBuffer();
        cv::imwrite(dstresImgPath.GetBuffer(dstresImgPath.GetLength()), m_res); dstresImgPath.ReleaseBuffer();
    }
    else
    {
        if (m_jsondoc.HasMember("mouthclosed"))
        {
            RAPIDJSON_NAMESPACE::Value& v = m_jsondoc["mouthclosed"];
            if (v.IsArray())
            {
                v.PushBack(m_nCurrentIndex, m_jsondoc.GetAllocator());
            }
        }
        dstsrcImgPath.Format("./datas/mouthclosed/%d-src.jpg", m_nCurrentIndex);
        dstresImgPath.Format("./datas/mouthclosed/%d-dst.jpg", m_nCurrentIndex);
        cv::imwrite(dstsrcImgPath.GetBuffer(dstsrcImgPath.GetLength()), m_src); dstsrcImgPath.ReleaseBuffer();
        cv::imwrite(dstresImgPath.GetBuffer(dstresImgPath.GetLength()), m_res); dstresImgPath.ReleaseBuffer();
    }

    if (m_bHaveEarDrop)
    {
        if (m_jsondoc.HasMember("eardropexist"))
        {
            RAPIDJSON_NAMESPACE::Value& v = m_jsondoc["eardropexist"];
            if (v.IsArray())
            {
                v.PushBack(m_nCurrentIndex, m_jsondoc.GetAllocator());
            }
        }
        dstsrcImgPath.Format("./datas/eardropexist/%d-src.jpg", m_nCurrentIndex);
        dstresImgPath.Format("./datas/eardropexist/%d-dst.jpg", m_nCurrentIndex);
        cv::imwrite(dstsrcImgPath.GetBuffer(dstsrcImgPath.GetLength()), m_src); dstsrcImgPath.ReleaseBuffer();
        cv::imwrite(dstresImgPath.GetBuffer(dstresImgPath.GetLength()), m_res); dstresImgPath.ReleaseBuffer();
    }
    else
    {
        if (m_jsondoc.HasMember("eardropnotexist"))
        {
            RAPIDJSON_NAMESPACE::Value& v = m_jsondoc["eardropnotexist"];
            if (v.IsArray())
            {
                v.PushBack(m_nCurrentIndex, m_jsondoc.GetAllocator());
            }
        }
        dstsrcImgPath.Format("./datas/eardropnotexist/%d-src.jpg", m_nCurrentIndex);
        dstresImgPath.Format("./datas/eardropnotexist/%d-dst.jpg", m_nCurrentIndex);
        cv::imwrite(dstsrcImgPath.GetBuffer(dstsrcImgPath.GetLength()), m_src); dstsrcImgPath.ReleaseBuffer();
        cv::imwrite(dstresImgPath.GetBuffer(dstresImgPath.GetLength()), m_res); dstresImgPath.ReleaseBuffer();
    }

    switch (m_nResult)
    {
    case 0:
    {
        m_nUsable++;
        RAPIDJSON_NAMESPACE::Value& v = m_jsondoc["usable"];
        v.PushBack(m_nCurrentIndex, m_jsondoc.GetAllocator());
        dstsrcImgPath.Format("./datas/0-0-usable/%d-src.jpg", m_nCurrentIndex);
        dstresImgPath.Format("./datas/0-0-usable/%d-dst.jpg", m_nCurrentIndex);
    }
        break;
    case 1:
    {
        m_nSrcNotQualify++;
        RAPIDJSON_NAMESPACE::Value& v = m_jsondoc["srcunqualify"];
        v.PushBack(m_nCurrentIndex, m_jsondoc.GetAllocator());
        dstsrcImgPath.Format("./datas/0-1-srcunqualify/%d-src.jpg", m_nCurrentIndex);
        dstresImgPath.Format("./datas/0-1-srcunqualify/%d-dst.jpg", m_nCurrentIndex);
    }
        break;
    case 2:
    {
        m_nAlgorithmError++;
        RAPIDJSON_NAMESPACE::Value& v = m_jsondoc["algorithmerror"];
        v.PushBack(m_nCurrentIndex, m_jsondoc.GetAllocator());
        dstsrcImgPath.Format("./datas/0-2-algorithmerror/%d-src.jpg", m_nCurrentIndex);
        dstresImgPath.Format("./datas/0-2-algorithmerror/%d-dst.jpg", m_nCurrentIndex);
    }
        break;
    case 3:
    {
        m_nForeignMatter++;
        RAPIDJSON_NAMESPACE::Value& v = m_jsondoc["foreignmatter"];
        v.PushBack(m_nCurrentIndex, m_jsondoc.GetAllocator());
        dstsrcImgPath.Format("./datas/0-3-foreignmatter/%d-src.jpg", m_nCurrentIndex);
        dstresImgPath.Format("./datas/0-3-foreignmatter/%d-dst.jpg", m_nCurrentIndex);
    }
        break;
    case 4:
    {
        m_nTooMuch++;
        RAPIDJSON_NAMESPACE::Value& v = m_jsondoc["toomuch"];
        v.PushBack(m_nCurrentIndex, m_jsondoc.GetAllocator());
        dstsrcImgPath.Format("./datas/0-4-toomuch/%d-src.jpg", m_nCurrentIndex);
        dstresImgPath.Format("./datas/0-4-toomuch/%d-dst.jpg", m_nCurrentIndex);
    }
        break;
    case 5:
    {
        m_nNotAll++;
        RAPIDJSON_NAMESPACE::Value& v = m_jsondoc["notall"];
        v.PushBack(m_nCurrentIndex, m_jsondoc.GetAllocator());
        dstsrcImgPath.Format("./datas/0-5-notall/%d-src.jpg", m_nCurrentIndex);
        dstresImgPath.Format("./datas/0-5-notall/%d-dst.jpg", m_nCurrentIndex);
    }
        break;
    }
    cv::imwrite(dstsrcImgPath.GetBuffer(dstsrcImgPath.GetLength()), m_src); dstsrcImgPath.ReleaseBuffer();
    cv::imwrite(dstresImgPath.GetBuffer(dstresImgPath.GetLength()), m_res); dstresImgPath.ReleaseBuffer();

    m_nTotal++;
    CString str;
    str.Format(L"%d/%d", m_nUsable, m_nTotal);
    GetDlgItem(IDC_S_ALL)->SetWindowTextW(str);
    UpdateData(FALSE);

    RAPIDJSON_NAMESPACE::StringBuffer buffer;
    RAPIDJSON_NAMESPACE::PrettyWriter<RAPIDJSON_NAMESPACE::StringBuffer> writer(buffer);
    m_jsondoc.Accept(writer);
    std::string sinfo = buffer.GetString();
    std::ofstream of("./datas/infos.json");
    of << sinfo << std::endl;
    of.close();

    //RAPIDJSON_NAMESPACE::Document doc;
    //doc.SetObject();

    //std::string s;
    //std::stringstream ostr;
    //ostr <<"./datas/"<< m_nCurrentIndex << ".json" << std::endl;
    //ostr >> s;
    //ostr.clear();
    //ostr.str("");

    //doc.AddMember("name", m_nCurrentIndex, doc.GetAllocator());
    //doc.AddMember("eyeclosedleft", m_bEyeClosedLeft, doc.GetAllocator());
    //doc.AddMember("eyeclosedright", m_bEyeClosedRight, doc.GetAllocator());
    //doc.AddMember("eyeblowuncoveredleft", m_bEyeBlowUncoveredLeft, doc.GetAllocator());
    //doc.AddMember("eyeblowuncoveredright", m_bEyeBlowUncoveredRight, doc.GetAllocator());
    //doc.AddMember("haveeardrop", m_bHaveEarDrop, doc.GetAllocator());
    //doc.AddMember("mouthopen", m_bMouthOpen, doc.GetAllocator());
    //doc.AddMember("usable", m_nResult, doc.GetAllocator());

    //
    //RAPIDJSON_NAMESPACE::StringBuffer buffer;
    //RAPIDJSON_NAMESPACE::PrettyWriter<RAPIDJSON_NAMESPACE::StringBuffer> writer(buffer);
    //doc.Accept(writer);

 
    //std::string sinfo = buffer.GetString();

    //std::ofstream of(s);
    //of << sinfo << std::endl;
    //of.close();

    //switch (m_nResult)
    //{
    //case 0:
    //    m_nUsable++;
    //    break;
    //case 1:
    //    m_nSrcNotQualify++;
    //    break;
    //case 2:
    //    m_nAlgorithmError++;
    //    break;
    //case 3:
    //    m_nForeignMatter++;
    //    break;
    //case 4:
    //    m_nTooMuch++;
    //    break;
    //case 5:
    //    m_nNotAll++;
    //    break;
    //}
    //m_nTotal++;
    //CString str;
    //str.Format(L"%d/%d", m_nUsable, m_nTotal);
    //GetDlgItem(IDC_S_ALL)->SetWindowTextW(str);
    //UpdateData(FALSE);
}


void CMattingResultUtilityDlg::OnBnClickedEyeopenL()
{
    // TODO: 在此添加控件通知处理程序代码
    m_bEyeClosedLeft = TRUE;
}


void CMattingResultUtilityDlg::OnBnClickedEyecloseL()
{
    // TODO: 在此添加控件通知处理程序代码
    m_bEyeClosedLeft = FALSE;
}


void CMattingResultUtilityDlg::OnBnClickedEyeopenR()
{
    // TODO: 在此添加控件通知处理程序代码
    m_bEyeClosedRight = TRUE;
}


void CMattingResultUtilityDlg::OnBnClickedEyecloseR()
{
    // TODO: 在此添加控件通知处理程序代码
    m_bEyeClosedRight = FALSE;
}


void CMattingResultUtilityDlg::OnBnClickedEyeblowCoverL()
{
    // TODO: 在此添加控件通知处理程序代码
    m_bEyeBlowUncoveredLeft = TRUE;
}


void CMattingResultUtilityDlg::OnBnClickedEyeblowNotcoverL()
{
    // TODO: 在此添加控件通知处理程序代码
    m_bEyeBlowUncoveredLeft = FALSE;
}


void CMattingResultUtilityDlg::OnBnClickedEyeblowCoverR()
{
    // TODO: 在此添加控件通知处理程序代码
    m_bEyeBlowUncoveredRight = TRUE;
}


void CMattingResultUtilityDlg::OnBnClickedEyeblowNotcoverR()
{
    // TODO: 在此添加控件通知处理程序代码
    m_bEyeBlowUncoveredRight = FALSE;
}


void CMattingResultUtilityDlg::OnBnClickedMouthO()
{
    // TODO: 在此添加控件通知处理程序代码
    m_bMouthOpen = TRUE;
}


void CMattingResultUtilityDlg::OnBnClickedMouthC()
{
    // TODO: 在此添加控件通知处理程序代码
    m_bMouthOpen = FALSE;
}


void CMattingResultUtilityDlg::OnBnClickedEardrop()
{
    // TODO: 在此添加控件通知处理程序代码
    m_bHaveEarDrop = FALSE;
}


void CMattingResultUtilityDlg::OnBnClickedEardropNo()
{
    // TODO: 在此添加控件通知处理程序代码
    m_bHaveEarDrop = TRUE;
}


void CMattingResultUtilityDlg::OnBnClickedUsable()
{
    // TODO: 在此添加控件通知处理程序代码
    m_nResult = 0;
}


void CMattingResultUtilityDlg::OnBnClickedSrcnotqualify()
{
    // TODO: 在此添加控件通知处理程序代码
    m_nResult = 1;
}


void CMattingResultUtilityDlg::OnBnClickedAlgorithmerror()
{
    // TODO: 在此添加控件通知处理程序代码
    m_nResult = 2;
}


void CMattingResultUtilityDlg::OnBnClickedForeignmatter()
{
    // TODO: 在此添加控件通知处理程序代码
    m_nResult = 3;
}


void CMattingResultUtilityDlg::OnBnClickedToomuch()
{
    // TODO: 在此添加控件通知处理程序代码
    m_nResult = 4;
}


void CMattingResultUtilityDlg::OnBnClickedNotall()
{
    // TODO: 在此添加控件通知处理程序代码
    m_nResult = 5;
}


void CMattingResultUtilityDlg::OnBnClickedBtnReset()
{
    // TODO: 在此添加控件通知处理程序代码
    switch (m_nResult)
    {
    case 0:
        m_nUsable--;
        break;
    case 1:
        m_nSrcNotQualify--;
        break;
    case 2:
        m_nAlgorithmError--;
        break;
    case 3:
        m_nForeignMatter--;
        break;
    case 4:
        m_nTooMuch--;
        break;
    case 5:
        m_nNotAll--;
        break;
    }
    m_nTotal--;
    CString str;
    str.Format(L"%d/%d", m_nUsable, m_nTotal);
    GetDlgItem(IDC_S_ALL)->SetWindowTextW(str);
    UpdateData(FALSE);
}

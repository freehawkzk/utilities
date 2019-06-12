
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

//#ifdef _DEBUG
//#define new DEBUG_NEW
//#endif

void appendstring(std::string& str0, std::string& str1)
{
    if (str1.length() != 0)
    {
        if (str1[0] != ' ')
        {
            std::string temp = " " + str1;
            str1 = temp;
        }
        if (str1[str1.length() - 1] != ' ')
        {
            std::string temp = str1 + " ";
            str1 = temp;
        }
    }
    if (str0.find(str1) == std::string::npos)
    {
        str0 = str0 + str1;
    }
}

void removestring(std::string& str0, std::string& str1)
{
    if (str1.length() != 0)
    {
        if (str1[0] != ' ')
        {
            std::string temp = " " + str1;
            str1 = temp;
        }
        if (str1[str1.length() - 1] != ' ')
        {
            std::string temp = str1 + " ";
            str1 = temp;
        }
    }

    std::string::size_type pos = str0.find(str1);
    if (pos != std::string::npos)
    {
        str0.replace(pos, str1.length(), "");
    }
}

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

    GetDlgItem(IDC_BTN_PRE)->EnableWindow(FALSE);
    GetDlgItem(IDC_BTN_SET)->EnableWindow(FALSE);
    GetDlgItem(IDC_BTN_RESET)->EnableWindow(FALSE);



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
    while (getline(in, line)) 
    {
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
    GetDlgItem(IDC_BTN_PRE)->EnableWindow(FALSE);
    GetDlgItem(IDC_BTN_SET)->EnableWindow(TRUE);
    GetDlgItem(IDC_BTN_RESET)->EnableWindow(FALSE);
    GetDlgItem(IDC_BTN_NEXT)->EnableWindow(FALSE);
    m_nResult = 0;
    UpdateData(FALSE);
}


void CMattingResultUtilityDlg::OnBnClickedBtnPre()
{
    // TODO: 在此添加控件通知处理程序代码
    removeCurImgInfo();

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

    GetDlgItem(IDC_BTN_PRE)->EnableWindow(FALSE);
    GetDlgItem(IDC_BTN_SET)->EnableWindow(TRUE);
    GetDlgItem(IDC_BTN_RESET)->EnableWindow(FALSE);
    GetDlgItem(IDC_BTN_NEXT)->EnableWindow(FALSE);
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

    std::ofstream of00("./datas/0-0-usable.tags");
    std::ofstream of01("./datas/0-1-srcunqualify.tags");
    std::ofstream of02("./datas/0-2-algorithmerror.tags");
    std::ofstream of03("./datas/0-3-foreignmatter.tags");
    std::ofstream of04("./datas/0-4-toomuch.tags");
    std::ofstream of05("./datas/0-5-notall.tags");
    std::ofstream of10("./datas/1-0-lefteyeclosed.tags");
    std::ofstream of11("./datas/1-1-lefteyeopen.tags");
    std::ofstream of20("./datas/2-0-righteyeclosed.tags");
    std::ofstream of21("./datas/2-1-righteyeopen.tags");
    std::ofstream of30("./datas/3-0-lefteyeblowcovered.tags");
    std::ofstream of31("./datas/3-1-lefteyeblowuncovered.tags");
    std::ofstream of40("./datas/4-0-righteyeblowcovered.tags");
    std::ofstream of41("./datas/4-1-righteyeblowuncovered.tags");
    std::ofstream of50("./datas/5-0-mouthclosed.tags");
    std::ofstream of51("./datas/5-1-mouthopen.tags");
    std::ofstream of60("./datas/6-0-eardropexist.tags");
    std::ofstream of61("./datas/6-1-eardropnotexist.tags");

    of00 << m_str00 << std::endl;
    of01 << m_str01 << std::endl;
    of02 << m_str02 << std::endl;
    of03 << m_str03 << std::endl;
    of04 << m_str04 << std::endl;
    of05 << m_str05 << std::endl;
    of10 << m_str10 << std::endl;
    of11 << m_str11 << std::endl;
    of20 << m_str20 << std::endl;
    of21 << m_str21 << std::endl;
    of30 << m_str30 << std::endl;
    of31 << m_str31 << std::endl;
    of40 << m_str40 << std::endl;
    of41 << m_str41 << std::endl;
    of50 << m_str50 << std::endl;
    of51 << m_str51 << std::endl;
    of60 << m_str60 << std::endl;
    of61 << m_str61 << std::endl;

    of00.close();
    of01.close();
    of02.close();
    of03.close();
    of04.close();
    of05.close();
    of10.close();
    of11.close();
    of20.close();
    of21.close();
    of30.close();
    of31.close();
    of40.close();
    of41.close();
    of50.close();
    of51.close();
    of60.close();
    of61.close();

    m_src = cv::Mat();
    m_res = cv::Mat();
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
    std::string strCurIndex;
    std::stringstream ss;
    ss << " "<<m_nCurrentIndex<<" ";
    ss >> strCurIndex;
    ss.clear();
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
        appendstring(m_str10, strCurIndex);
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
        appendstring(m_str11, strCurIndex);
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
        appendstring(m_str20, strCurIndex);
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
        appendstring(m_str21, strCurIndex);
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
        appendstring(m_str31, strCurIndex);
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
        appendstring(m_str30, strCurIndex);
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
        appendstring(m_str41, strCurIndex);
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
        appendstring(m_str40, strCurIndex);
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
        appendstring(m_str51, strCurIndex);
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
        appendstring(m_str50, strCurIndex);
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
        appendstring(m_str60, strCurIndex);
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
        appendstring(m_str61, strCurIndex);
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
        appendstring(m_str00, strCurIndex);
        RAPIDJSON_NAMESPACE::Value& v = m_jsondoc["usable"];
        v.PushBack(m_nCurrentIndex, m_jsondoc.GetAllocator());
        dstsrcImgPath.Format("./datas/0-0-usable/%d-src.jpg", m_nCurrentIndex);
        dstresImgPath.Format("./datas/0-0-usable/%d-dst.jpg", m_nCurrentIndex);
    }
        break;
    case 1:
    {
        m_nSrcNotQualify++;
        appendstring(m_str01, strCurIndex);
        RAPIDJSON_NAMESPACE::Value& v = m_jsondoc["srcunqualify"];
        v.PushBack(m_nCurrentIndex, m_jsondoc.GetAllocator());
        dstsrcImgPath.Format("./datas/0-1-srcunqualify/%d-src.jpg", m_nCurrentIndex);
        dstresImgPath.Format("./datas/0-1-srcunqualify/%d-dst.jpg", m_nCurrentIndex);
    }
        break;
    case 2:
    {
        m_nAlgorithmError++;
        appendstring(m_str02, strCurIndex);
        RAPIDJSON_NAMESPACE::Value& v = m_jsondoc["algorithmerror"];
        v.PushBack(m_nCurrentIndex, m_jsondoc.GetAllocator());
        dstsrcImgPath.Format("./datas/0-2-algorithmerror/%d-src.jpg", m_nCurrentIndex);
        dstresImgPath.Format("./datas/0-2-algorithmerror/%d-dst.jpg", m_nCurrentIndex);
    }
        break;
    case 3:
    {
        m_nForeignMatter++;
        appendstring(m_str03, strCurIndex);
        RAPIDJSON_NAMESPACE::Value& v = m_jsondoc["foreignmatter"];
        v.PushBack(m_nCurrentIndex, m_jsondoc.GetAllocator());
        dstsrcImgPath.Format("./datas/0-3-foreignmatter/%d-src.jpg", m_nCurrentIndex);
        dstresImgPath.Format("./datas/0-3-foreignmatter/%d-dst.jpg", m_nCurrentIndex);
    }
        break;
    case 4:
    {
        m_nTooMuch++;
        appendstring(m_str04, strCurIndex);
        RAPIDJSON_NAMESPACE::Value& v = m_jsondoc["toomuch"];
        v.PushBack(m_nCurrentIndex, m_jsondoc.GetAllocator());
        dstsrcImgPath.Format("./datas/0-4-toomuch/%d-src.jpg", m_nCurrentIndex);
        dstresImgPath.Format("./datas/0-4-toomuch/%d-dst.jpg", m_nCurrentIndex);
    }
        break;
    case 5:
    {
        m_nNotAll++;
        appendstring(m_str05, strCurIndex);
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

    GetDlgItem(IDC_BTN_PRE)->EnableWindow(TRUE);
    GetDlgItem(IDC_BTN_SET)->EnableWindow(FALSE);
    GetDlgItem(IDC_BTN_RESET)->EnableWindow(TRUE);
    GetDlgItem(IDC_BTN_NEXT)->EnableWindow(TRUE);

    UpdateData(FALSE);

    //RAPIDJSON_NAMESPACE::StringBuffer buffer;
    //RAPIDJSON_NAMESPACE::PrettyWriter<RAPIDJSON_NAMESPACE::StringBuffer> writer(buffer);
    //m_jsondoc.Accept(writer);
    //std::string sinfo = buffer.GetString();
    //std::ofstream of("./datas/infos.json");
    //of << sinfo << std::endl;
    //of.close();
    
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
    removeCurImgInfo();

    GetDlgItem(IDC_BTN_PRE)->EnableWindow(TRUE);
    GetDlgItem(IDC_BTN_SET)->EnableWindow(TRUE);
    GetDlgItem(IDC_BTN_RESET)->EnableWindow(FALSE);
    GetDlgItem(IDC_BTN_NEXT)->EnableWindow(FALSE);
}

void CMattingResultUtilityDlg::removeCurImgInfo()
{
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

    std::string strCurIndex;
    std::stringstream ss;
    ss << " " << m_nCurrentIndex << " ";
    ss >> strCurIndex;
    ss.clear();
    removestring(m_str00, strCurIndex);
    removestring(m_str01, strCurIndex);
    removestring(m_str02, strCurIndex);
    removestring(m_str03, strCurIndex);
    removestring(m_str04, strCurIndex);
    removestring(m_str05, strCurIndex);
    removestring(m_str10, strCurIndex);
    removestring(m_str11, strCurIndex);
    removestring(m_str20, strCurIndex);
    removestring(m_str21, strCurIndex);
    removestring(m_str30, strCurIndex);
    removestring(m_str31, strCurIndex);
    removestring(m_str40, strCurIndex);
    removestring(m_str41, strCurIndex);
    removestring(m_str50, strCurIndex);
    removestring(m_str51, strCurIndex);
    removestring(m_str60, strCurIndex);
    removestring(m_str61, strCurIndex);
}
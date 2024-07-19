#include "stdafx.h"
#include <windows.h> 
#include <tchar.h>
#include <stdio.h> 
#include <strsafe.h>

#include "SfcGtp.h"

#define BUFSIZE 8192 

/*HANDLE g_hChildStd_IN_Rd = NULL;
HANDLE g_hChildStd_IN_Wr = NULL;
HANDLE g_hChildStd_OUT_Rd = NULL;
HANDLE g_hChildStd_OUT_Wr = NULL;

HANDLE g_hInputFile = NULL;
*/
extern int iState;
extern CString strDirectry;//数据目录
extern bool bLog;;//是否记录日志

SfcGtp::SfcGtp(void)
{
    m_bEngineLoaded = false;
    m_Id = 0;
    m_iType = 0;
}


SfcGtp::~SfcGtp(void)
{
    CloseEngine();
}

bool SfcGtp::LoadEngine(int type)
{
    SECURITY_ATTRIBUTES saAttr;

    printf("\n->Start of parent execution.\n");

    // Set the bInheritHandle flag so pipe handles are inherited. 

    saAttr.nLength = sizeof(SECURITY_ATTRIBUTES);
    saAttr.bInheritHandle = TRUE;
    saAttr.lpSecurityDescriptor = NULL;

    // Create a pipe for the child process's STDOUT. 

    if (!CreatePipe(&m_hChildStd_OUT_Rd, &m_hChildStd_OUT_Wr, &saAttr, 0))
        ErrorExit(TEXT("StdoutRd CreatePipe"));

    // Ensure the read handle to the pipe for STDOUT is not inherited.

    if (!SetHandleInformation(m_hChildStd_OUT_Rd, HANDLE_FLAG_INHERIT, 0))
        ErrorExit(TEXT("Stdout SetHandleInformation"));

    // Create a pipe for the child process's STDIN. 

    if (!CreatePipe(&m_hChildStd_IN_Rd, &m_hChildStd_IN_Wr, &saAttr, 0))
        ErrorExit(TEXT("Stdin CreatePipe"));

    // Ensure the write handle to the pipe for STDIN is not inherited. 

    if (!SetHandleInformation(m_hChildStd_IN_Wr, HANDLE_FLAG_INHERIT, 0))
        ErrorExit(TEXT("Stdin SetHandleInformation"));

    // Create the child process. 
    TCHAR appName[1024];// = TEXT("E:\\Game\\KataGo\\katago.exe");
    TCHAR cmdLine[1024]; //= TEXT("E:\\Game\\KataGo\\katago.exe gtp -model kata1-b18c384nbt-s7709731328-d3715293823.bin.gz -config SfcGo.cfg");
    TCHAR cmdLine1[1024]; //= TEXT("E:\\Game\\KataGo\\katago.exe gtp -model kata1-b18c384nbt-s7709731328-d3715293823.bin.gz -config SfcGo_LifeDeth.cfg");
    TCHAR appDir[1024]; //= TEXT("E:\\Game\\KataGo");
 
    strcpy_s(appName, m_AppName);
    strcpy_s(cmdLine, m_CmdLine);
    strcpy_s(cmdLine1, m_CmdLine1);
    strcpy_s(appDir, m_AppDir);

    if(type==1)//死活分析，katago不允许认输；对于leelaz则是较强的网络权重
        CreateChildProcess(appName, cmdLine1, appDir);
    else
        CreateChildProcess(appName,cmdLine,appDir);

    m_iType = type;
    m_bEngineLoaded = true;

    //创建日志文件
    if (bLog)
    {
        CString fname = strDirectry + "\\Log\\";
        time_t rawtime;
        tm lctime;
        time(&rawtime);
        localtime_s(&lctime, &rawtime);
        CString str1;
        str1.Format("Engine%d%d%d%02d%02d-%02d%02d%02d.log", m_Id, m_iType, lctime.tm_year+1900, lctime.tm_mon+1, lctime.tm_mday, lctime.tm_hour, lctime.tm_min, lctime.tm_sec);
        fname += str1;
        m_hInputFile = CreateFile(
            fname,
            GENERIC_READ | GENERIC_WRITE,
            0,
            NULL,
            OPEN_ALWAYS,
            FILE_ATTRIBUTE_NORMAL,
            NULL);

        if (m_hInputFile == INVALID_HANDLE_VALUE)
            AfxMessageBox("创建日志文件失败！", NULL, MB_OK);
    }
    CString str = "name\r\n";
    WriteToPipe(str);
    int count;
    CString* strs = GetMsg(count);
    delete[] strs;

    // Get a handle to an input file for the parent. 
    // This example assumes a plain text file and uses string output to verify data flow. 

    /*g_hInputFile = CreateFile(
        "Gtptmp.txt",
        GENERIC_READ | GENERIC_WRITE,
        0,
        NULL,
        OPEN_ALWAYS,
        FILE_ATTRIBUTE_NORMAL,
        NULL);

    if (g_hInputFile == INVALID_HANDLE_VALUE)
        ErrorExit(TEXT("CreateFile"));*/

    //ReadFromPipe();
    // Write to the pipe that is the standard input for a child process. 
    // Data is written to the pipe's buffers, so it is not necessary to wait
    // until the child process is running before writing data.

    //WriteToPipe("komi 6.5\n");

    // Read from pipe that is the standard output for child process. 

    //ReadFromPipe();
    //WriteToPipe("boardsize 19\n");
    //ReadFromPipe();
    //WriteToPipe("quit\n");
    //CloseHandle(g_hInputFile);

    //printf("\n->End of parent execution.\n");

    // The remaining open handles are cleaned up when this process terminates. 
    // To avoid resource leaks in a larger application, close handles explicitly. 

    return true;
}

void SfcGtp::CloseEngine()
{
    if (m_bEngineLoaded)
    {
        WriteToPipe("quit\n");
        m_bEngineLoaded = false;
        if (bLog)
            CloseHandle(m_hInputFile);
    }
}
void SfcGtp::CreateChildProcess(TCHAR appName[], TCHAR cmdLine[], TCHAR appDir[])
// Create a child process that uses the previously created pipes for STDIN and STDOUT.
{
    //TCHAR szCmdline[] = TEXT("child");
    PROCESS_INFORMATION piProcInfo;
    STARTUPINFO siStartInfo;
    BOOL bSuccess = FALSE;

    // Set up members of the PROCESS_INFORMATION structure. 

    ZeroMemory(&piProcInfo, sizeof(PROCESS_INFORMATION));

    // Set up members of the STARTUPINFO structure. 
    // This structure specifies the STDIN and STDOUT handles for redirection.

    ZeroMemory(&siStartInfo, sizeof(STARTUPINFO));
    siStartInfo.cb = sizeof(STARTUPINFO);
    siStartInfo.hStdError = m_hChildStd_OUT_Wr;
    siStartInfo.hStdOutput = m_hChildStd_OUT_Wr;
    siStartInfo.hStdInput = m_hChildStd_IN_Rd;
    siStartInfo.dwFlags |= STARTF_USESTDHANDLES;

    // Create the child process. 
    //TCHAR curDir[1000];
    //GetCurrentDirectory(1000, curDir);
    //SetCurrentDirectory(appDir);

    bSuccess = CreateProcess(appName,
        cmdLine,     // command line 
        NULL,          // process security attributes 
        NULL,          // primary thread security attributes 
        TRUE,          // handles are inherited 
        CREATE_NO_WINDOW,             // creation flags 
        NULL,          // use parent's environment 
        appDir,          // use parent's current directory 
        &siStartInfo,  // STARTUPINFO pointer 
        &piProcInfo);  // receives PROCESS_INFORMATION 

     // If an error occurs, exit the application. 
    if (!bSuccess)
        ErrorExit(TEXT("CreateProcess"));
    else
    {
        // Close handles to the child process and its primary thread.
        // Some applications might keep these handles to monitor the status
        // of the child process, for example. 

        CloseHandle(piProcInfo.hProcess);
        CloseHandle(piProcInfo.hThread);

        // Close handles to the stdin and stdout pipes no longer needed by the child process.
        // If they are not explicitly closed, there is no way to recognize that the child process has ended.

        CloseHandle(m_hChildStd_OUT_Wr);
        CloseHandle(m_hChildStd_IN_Rd);
    }
}

void SfcGtp::WriteToPipe(CString str)

// Read from a file and write its contents to the pipe for the child's STDIN.
// Stop when there is no more data. 
{
    DWORD dwRead, dwWritten;
    CHAR chBuf[BUFSIZE];
    strcpy_s(chBuf, str);
    dwRead = str.GetLength();
    BOOL bSuccess = FALSE;

    //写入日志文件
    if (bLog)
    {
        CString s = "SfcGo  : ";
        bSuccess = WriteFile(m_hInputFile, s,
            s.GetLength(), &dwWritten, NULL);
        dwRead = str.GetLength();
        bSuccess = WriteFile(m_hInputFile, str,
            dwRead, &dwWritten, NULL);
        if (!bSuccess)
            AfxMessageBox("写入日志文件失败！", NULL, MB_OK);
    }
    //for (;;)
    //{
        //bSuccess = ReadFile(g_hInputFile, chBuf, BUFSIZE, &dwRead, NULL);
        //if (!bSuccess || dwRead == 0) break;

        bSuccess = WriteFile(m_hChildStd_IN_Wr, chBuf, dwRead, &dwWritten, NULL);
        //if (!bSuccess) return;
        //bSuccess = WriteFile(g_hInputFile, chBuf,
          //  dwRead, &dwWritten, NULL);
        //if (!bSuccess) return;
    //}

    // Close the pipe handle so the child process stops reading. 

    //if (!CloseHandle(g_hChildStd_IN_Wr))
      //  ErrorExit(TEXT("StdInWr CloseHandle"));
}

void SfcGtp::ReadFromPipe(CHAR chBuf[],DWORD &dwRead)

// Read output from the child process's pipe for STDOUT
// and write to the parent process's pipe for STDOUT. 
// Stop when there is no more data. 
{
    //DWORD dwRead, dwWritten;
    //CHAR chBuf[BUFSIZE];
    BOOL bSuccess = FALSE;
    //HANDLE hParentStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

    //for (;;)
    //{
        bSuccess = ReadFile(m_hChildStd_OUT_Rd, chBuf, BUFSIZE, &dwRead, NULL);
        //if (!bSuccess || dwRead == 0) return;

        //bSuccess = WriteFile(g_hInputFile, chBuf,
          //  dwRead, &dwWritten, NULL);
        //if (!bSuccess) return;
    //}
}

void SfcGtp::ErrorExit(PTSTR lpszFunction)

// Format a readable error message, display a message box, 
// and exit from the application.
{
    LPVOID lpMsgBuf;
    LPVOID lpDisplayBuf;
    DWORD dw = GetLastError();

    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER |
        FORMAT_MESSAGE_FROM_SYSTEM |
        FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        dw,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPTSTR)&lpMsgBuf,
        0, NULL);

    lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT,
        (lstrlen((LPCTSTR)lpMsgBuf) + lstrlen((LPCTSTR)lpszFunction) + 40) * sizeof(TCHAR));
    StringCchPrintf((LPTSTR)lpDisplayBuf,
        LocalSize(lpDisplayBuf) / sizeof(TCHAR),
        TEXT("%s failed with error %d: %s"),
        lpszFunction, dw, lpMsgBuf);
    MessageBox(NULL, (LPCTSTR)lpDisplayBuf, TEXT("Error"), MB_OK);

    LocalFree(lpMsgBuf);
    LocalFree(lpDisplayBuf);
    ExitProcess(1);
}

CString* SfcGtp::GetMsg(int& count)
{
    DWORD dwRead, dwWritten;
    CHAR chBuf[BUFSIZE+1];
    BOOL bSuccess = FALSE;
    CString retstr = "";
    for (;;)
    {
        bSuccess = ReadFile(m_hChildStd_OUT_Rd, chBuf, BUFSIZE, &dwRead, NULL);
        if (!bSuccess || dwRead == 0) break;
        chBuf[dwRead] = 0;
        CString str = chBuf;
        retstr += str;
        int l = retstr.GetLength();
        if (l >= 4 && retstr.Right(4)=="\r\n\r\n")
            break;
    }
    //写入日志文件
    if (bLog)
    {
        CString s = "Engine : ";
        bSuccess = WriteFile(m_hInputFile, s,
            s.GetLength(), &dwWritten, NULL);
        dwRead = retstr.GetLength();
        bSuccess = WriteFile(m_hInputFile, retstr,
            dwRead, &dwWritten, NULL);
        if (!bSuccess)
            AfxMessageBox("写入日志文件失败！", NULL, MB_OK);
    }
    return SplitString(retstr, "\n", count);
}
// 分割字符串为字符数组
CString* SfcGtp::SplitString(CString strSource, CString strSeperator, int& count)
{
    count = 0;
    int len = strSource.GetLength();
    int len1 = strSeperator.GetLength();
    if (len == 0 || len1 == 0)
    {
        return NULL;
    }
    CString* pstrSubStrings;
    int iSubStringCount, nIndex = 0;
    //seprator中的所有分隔符全部替换成第一个,并统计source中seprator的个数  
    iSubStringCount = 1;

    for (int i = 0; i < len; i++)
    {
        if (strSource[i] == strSeperator[0])
            iSubStringCount++;
    }

    for (int i = 1; i < len1; i++)
    {
        iSubStringCount += strSource.Replace(strSeperator[i], strSeperator[0]);
    }

    pstrSubStrings = new CString[iSubStringCount];

    int nNewIndex, nCount = 0;
    while (nIndex < len)
    {
        nNewIndex = strSource.Find(strSeperator[0], nIndex);
        if (nNewIndex >= 0)
            pstrSubStrings[nCount++] = strSource.Mid(nIndex, nNewIndex - nIndex);
        else
            pstrSubStrings[nCount++] = strSource.Mid(nIndex);

        nIndex += pstrSubStrings[nCount - 1].GetLength() + 1;
    }

    count = iSubStringCount;

    return pstrSubStrings;
}


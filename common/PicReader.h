/****************************************************************
 * Project Name:  common
 * File Name:     PicReader.h
 * File Function: 读取图像文件函数工具集的头文件
 * Author:        Jishen Lin (林继申)
 * Update Date:   2023/9/27
 ****************************************************************/

#pragma once
#include <Windows.h>
#include <wincodec.h>
#include <commdlg.h>

/*
 * Function Name:    SafeRelease
 * Function:         Release safely
 * Input Parameters: T*& p
 * Return Value:     void
 */
template <typename T>
inline void SafeRelease(T*& p)
{
    if (nullptr != p) {
        p->Release();
        p = nullptr;
    }
}

/* Define PicReader class */
class PicReader {
private:
    HWND hWnd;
    HANDLE hFile;
    IWICImagingFactory* m_pIWICFactory;
    IWICFormatConverter* m_pConvertedSourceBitmap;
    void init(void);
    bool checkHR(HRESULT hr);
    void quitWithError(LPCSTR message);
public:
    PicReader();
    ~PicReader();
    void readPic(LPCSTR fileName);
    void getData(BYTE*& data, UINT& _x, UINT& _y);
};
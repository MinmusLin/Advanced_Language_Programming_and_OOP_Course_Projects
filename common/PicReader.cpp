/****************************************************************
 * Project Name:  common
 * File Name:     PicReader.cpp
 * File Function: 读取图像文件函数工具集的实现
 * Author:        Jishen Lin (林继申)
 * Update Date:   2023/9/28
 ****************************************************************/

#include <iostream>
#include "../common/PicReader.h"

using namespace std;

/*
 * Function Name:    init
 * Function:         Initialized function
 * Input Parameters: void
 * Return Value:     void
 * Notes:            Class external implementation of member functions
 */
void PicReader::init(void)
{
    /* Enables the terminate-on-corruption feature */
    hWnd = GetForegroundWindow();
    HeapSetInformation(nullptr, HeapEnableTerminationOnCorruption, nullptr, 0);
    HRESULT hr = S_OK;

    /* Init the WIC */
    hr = CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);

    /* Create WIC factory */
    hr = CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&m_pIWICFactory));

    /* Throw error if create factor failed */
    if (checkHR(hr))
        quitWithError("Init Reader Failed");
}

/*
 * Function Name:    checkHR
 * Function:         Check HR
 * Input Parameters: HRESULT hr
 * Return Value:     (hr < 0)
 * Notes:            Class external implementation of member functions
 */
bool PicReader::checkHR(HRESULT hr)
{
    return (hr < 0);
}

/*
 * Function Name:    quitWithError
 * Function:         Quit with error
 * Input Parameters: LPCSTR message
 * Return Value:     void
 * Notes:            Class external implementation of member functions
 */
void PicReader::quitWithError(LPCSTR message)
{
    MessageBoxA(hWnd, message, "Application Error", MB_ICONEXCLAMATION | MB_OK);
    quick_exit(0xffffffff);
}

/*
 * Function Name:    PicReader
 * Function:         Constructed function
 * Notes:            Class external implementation of member functions
 */
PicReader::PicReader() : m_pConvertedSourceBitmap(nullptr), m_pIWICFactory(nullptr)
{
    init();
}

/*
 * Function Name:    ~PicReader
 * Function:         Destructor
 * Notes:            Class external implementation of member functions
 */
PicReader::~PicReader()
{
    if (hFile != NULL)
        CloseHandle(hFile);
    SafeRelease(m_pConvertedSourceBitmap);
    SafeRelease(m_pIWICFactory);
    CoUninitialize();
}

/*
 * Function Name:    readPic
 * Function:         Read the image as RGBA bitmap data
 * Input Parameters: LPCSTR fileName
 * Return Value:     void
 * Notes:            Class external implementation of member functions
 */
void PicReader::readPic(LPCSTR fileName)
{
    /* Create a file handle (WinAPI method not std c) */
    HRESULT hr = S_OK;
    if (hFile != NULL)
        CloseHandle(hFile);
    hFile = CreateFileA(fileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (GetLastError() == ERROR_FILE_NOT_FOUND)
        quitWithError("Cannot find such file, please retry or check the access");

    /* Create a decoder */
    IWICBitmapDecoder* pDecoder = nullptr;
    hr = m_pIWICFactory->CreateDecoderFromFileHandle((ULONG_PTR)hFile, nullptr, WICDecodeMetadataCacheOnDemand, &pDecoder);
    if (checkHR(hr))
        quitWithError("Create Decoder Failed");

    /* Retrieve the first frame of the image from the decoder */
    IWICBitmapFrameDecode* pFrame = nullptr;
    hr = pDecoder->GetFrame(0, &pFrame);
    if (checkHR(hr))
        quitWithError("Get Frame Failed");

    /* Format convert the frame to 32bppRGBA */
    SafeRelease(m_pConvertedSourceBitmap);
    hr = m_pIWICFactory->CreateFormatConverter(&m_pConvertedSourceBitmap);
    if (checkHR(hr))
        quitWithError("Get Format Converter Failed");
    hr = m_pConvertedSourceBitmap->Initialize(pFrame, GUID_WICPixelFormat32bppRGBA, WICBitmapDitherTypeNone, nullptr, 0.f, WICBitmapPaletteTypeCustom);
    if (checkHR(hr))
        quitWithError("Init Bitmap Failed");

    /* Clear up memory */
    SafeRelease(pDecoder);
    SafeRelease(pFrame);
}

/*
 * Function Name:    getData
 * Function:         Get data
 * Input Parameters: BYTE*& _out
 *                   UINT& _x
 *                   UINT& _y
 * Return Value:     void
 * Notes:            Class external implementation of member functions
 *                   The data copied from the Bitmap consists of groups of four, representing
 *                   a single pixel in each group. The data forms a one-dimensional array with
 *                   a length of (height * width * 4), where each pixel's data is arranged as
 *                   R G B A R G B A R G B A ... Since the getData function is implemented using
 *                   memory pointers allocated within the function, it's necessary to free the
 *                   data each time.
 */
void PicReader::getData(BYTE*& data, UINT& _x, UINT& _y)
{
    /* Get the size of image */
    HRESULT hr = S_OK;
    UINT x, y;
    hr = m_pConvertedSourceBitmap->GetSize(&x, &y);
    if (checkHR(hr))
        quitWithError("Check Bitmap Size Failed");

    /* Create the buffer of pixels, the type of BYTE is unsigned char */
    data = new(nothrow) BYTE[x * y * 4];
    if (data == NULL)
        exit(-1);
    memset(data, 0, x * y * 4);

    /* Copy the pixels to the buffer */
    UINT stride = x * 4;
    hr = m_pConvertedSourceBitmap->CopyPixels(nullptr, stride, x * y * 4, data);
    if (checkHR(hr))
        quitWithError("Copy Pixels Failed");

    /* Return the size of image */
    _x = x;
    _y = y;

    /* Close the file handle */
    CloseHandle(hFile);
    hFile = NULL;
}
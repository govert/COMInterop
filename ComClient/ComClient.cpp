﻿#include "stdafx.h"
#include <Windows.h>
#include <atlbase.h>

using namespace ATL;

// IServer definition
DECLARE_INTERFACE_IID_(IServer, IUnknown, "F38720E5-2D64-445E-88FB-1D696F614C78")
{
    // Compute and return the value of PI
    STDMETHOD(ComputePi)(_Out_ double *pi) PURE;
};

const IID IID_IServer = __uuidof(IServer);

// {114383E9-1969-47D2-9AA9-91388C961A19}
const CLSID CLSID_Server = { 0x114383E9, 0x1969, 0x47D2, { 0x9A, 0xA9, 0x91, 0x38, 0x8C, 0x96, 0x1A, 0x19 } };

HRESULT QueryServer()
{
    CComPtr<IServer> server;
    HRESULT hr = ::CoCreateInstance(CLSID_Server, nullptr, CLSCTX_INPROC, IID_IServer, (void**)&server);
    if (FAILED(hr))
        return hr;

    double pi;
    hr = server->ComputePi(&pi);
    if (FAILED(hr))
        return hr;

    ::printf("\u03C0 = %f\n", pi);

    return S_OK;
}

int main()
{
    // Set console codepage to utf-8. Also note the '/utf-8' compiler flag.
    ::SetConsoleOutputCP(65001);

    ::CoInitializeEx(0, COINITBASE_MULTITHREADED);

    HRESULT hr = QueryServer();

    ::CoUninitialize();

    if (FAILED(hr))
    {
        ::printf("Failure: 0x%08x\n", hr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}


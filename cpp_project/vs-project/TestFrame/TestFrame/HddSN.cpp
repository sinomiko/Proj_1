#include <Windows.h>
#include <winioctl.h>
#include <iostream>
#include <string>

using namespace std;
BOOL getSerial(string diskSerial) {
    BOOL   bResult = FALSE;

    STORAGE_PROPERTY_QUERY    storagePropertyQuery;
    STORAGE_DESCRIPTOR_HEADER storageDescHeader = { 0 };
    STORAGE_DEVICE_DESCRIPTOR *pDeviceDesc;

    DWORD dwBytes = 0;
    DWORD dwOutBufferSize = 0;
    DWORD dwSerialNumberOffset = 0;

    BYTE *pOutBuffer = nullptr;

    ZeroMemory(&storagePropertyQuery, sizeof(STORAGE_PROPERTY_QUERY));
    storagePropertyQuery.PropertyId = StorageDeviceProperty;
    storagePropertyQuery.QueryType = PropertyStandardQuery;


    HANDLE hDevice = CreateFile(L"\\\\.\\PhysicalDrive0", 0,
        FILE_SHARE_READ | FILE_SHARE_WRITE,
        NULL, OPEN_EXISTING, 0, NULL);

    if (hDevice == INVALID_HANDLE_VALUE) {
        std::cout << "Can't get access to HDD.\nTerminating." << std::endl;
        exit(EXIT_FAILURE);
    }

    bResult = DeviceIoControl(hDevice, IOCTL_STORAGE_QUERY_PROPERTY,
        &storagePropertyQuery, sizeof(storagePropertyQuery),
        &storageDescHeader, sizeof(storageDescHeader),
        &dwBytes, NULL);

    dwOutBufferSize = storageDescHeader.Size;

    try {
        pOutBuffer = new BYTE[dwOutBufferSize];
        ZeroMemory(pOutBuffer, sizeof(pOutBuffer));
    }
    catch (std::bad_alloc exp) {
        CloseHandle(hDevice);
        std::cout << exp.what() << std::endl;
        return FALSE;
    }

    bResult = DeviceIoControl(hDevice, IOCTL_STORAGE_QUERY_PROPERTY,
        &storagePropertyQuery, sizeof(STORAGE_PROPERTY_QUERY),
        pOutBuffer, dwOutBufferSize, &dwBytes, NULL);

    pDeviceDesc = (STORAGE_DEVICE_DESCRIPTOR *)pOutBuffer;
    dwSerialNumberOffset = pDeviceDesc->SerialNumberOffset;
    diskSerial = (char*)(pOutBuffer + dwSerialNumberOffset);

    std::cout << "Serial Number: " << diskSerial << std::endl;

    delete[] pOutBuffer;
    CloseHandle(hDevice);


    return TRUE;
}

#include <windows.h>
#include <iostream>
#include <bitset>
#include <vector>
using namespace std;
// 
// typedef struct _DISK_EXTENT {
//     DWORD         DiskNumber;
//     LARGE_INTEGER StartingOffset;
//     LARGE_INTEGER ExtentLength;
// } DISK_EXTENT, *PDISK_EXTENT;

// typedef struct _VOLUME_DISK_EXTENTS {
//     DWORD       NumberOfDiskExtents;
//     DISK_EXTENT Extents[ANYSIZE_ARRAY];
// } VOLUME_DISK_EXTENTS, *PVOLUME_DISK_EXTENTS;
// 
// #define CTL_CODE(DeviceType, Function, Method, Access) \
//     (((DeviceType) << 16) | ((Access) << 14) | ((Function) << 2) | (Method))
// #define IOCTL_VOLUME_BASE ((DWORD)'V')
// #define METHOD_BUFFERED 0
// #define FILE_ANY_ACCESS 0x00000000
// #define IOCTL_VOLUME_GET_VOLUME_DISK_EXTENTS CTL_CODE(IOCTL_VOLUME_BASE, 0, METHOD_BUFFERED, FILE_ANY_ACCESS)

int getDisk() {
    bitset<32> drives(GetLogicalDrives());
    vector<char> goodDrives;
    for (char c = 'A'; c <= 'Z'; ++c) {
        if (drives[c - 'A']) {
            if (GetDriveTypeA((c + string(":\\")).c_str()) == DRIVE_FIXED) {
                goodDrives.push_back(c);
            }
        }
    }
    for (auto & drive : goodDrives) {
        string s = string("\\\\.\\") + drive + ":";
        HANDLE h = CreateFileA(
            s.c_str(), GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL,
            OPEN_EXISTING, FILE_FLAG_NO_BUFFERING | FILE_FLAG_RANDOM_ACCESS, NULL
        );
        if (h == INVALID_HANDLE_VALUE) {
            cerr << "Drive " << drive << ":\\ cannot be opened";
            continue;
        }
        DWORD bytesReturned;
        VOLUME_DISK_EXTENTS vde;
        if (!DeviceIoControl(
            h, IOCTL_VOLUME_GET_VOLUME_DISK_EXTENTS,
            NULL, 0, &vde, sizeof(vde), &bytesReturned, NULL
        )) {
            cerr << "Drive " << drive << ":\\ cannot be mapped into physical drive";
            continue;
        }
        cout << "Drive " << drive << ":\\ is on the following physical drives: ";
        for (int i = 0; i < vde.NumberOfDiskExtents; ++i) {
            cout << vde.Extents[i].DiskNumber << ' ';
        }
        cout << endl;
    }
    return 0;
}

void FillWithSN(char* psn)
{
    auto new_sn = "wd-aabbccddeeff";
    if (new_sn && new_sn[0])
    {

        string nsstr = new_sn;
        if (nsstr.length() % 2)
        {
            //有奇数个字符，补全到偶数个
            nsstr.resize((nsstr.length() + 1) / 2 * 2);
            nsstr[nsstr.length() - 1] = ' ';
        }

        //change the orders
        for (unsigned int i = 0; i < nsstr.length(); i += 2)
        {
            auto p = nsstr[i + 1];
            nsstr[i + 1] = nsstr[i];
            nsstr[i] = p;
        }

        //copy SN to buffer
        auto psnlen = strnlen_s(psn, nsstr.length());
        for (unsigned int i = 0; i < min(psnlen, nsstr.length()); ++i)
        {
            psn[i] = nsstr[i];
        }

        //fill with zero at the end of SN
        int zeroPos = min(psnlen, nsstr.length());
        while (psn[zeroPos])
        {
            psn[zeroPos++] = 0;
        }
    }
}

void testFillSN()
{
    const char* strTest = "123";
    char* str = (char*)malloc(sizeof(char)*(strlen(strTest) * 2));

    FillWithSN(str);
    string ss;
    int i = 0;
    while (str[i + 1])
    {
        ss += str[i + 1];
        ss += str[i];
        i = i + 2;
    }
    cout << ss << endl;
}

int main(int argc, char* argv[])
{
//     string serial_num;
//     getSerial(serial_num);

    testFillSN();
    getchar();
    return 0;
}

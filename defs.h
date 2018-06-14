#define         INITGUID
#include        <windows.h>
#include        <ntsecapi.h>
#include        <stdio.h>
#include        <shobjidl.h>
#include        <shlobj.h>
#include        <sddl.h>
#include        <psapi.h>
#include        "ispplua.h"

DEFINE_GUID(CLSID_SPPLUAObject,
            0x179CC917, 0x3A82, 0x40E7, 0x9F, 0x8C, 0x2F, 0xC8, 0xA3, 0xD2, 0x21, 0x2B);
            
DEFINE_GUID(IID_ISPPLUA,
            0x12FBFECB, 0x7CCE, 0x473E, 0x87, 0x37, 0x78, 0xEE, 0x6C, 0x9C, 0xCA, 0xEB);
            
#define SAFE_RELEASE(x)                 \
        if (x){                         \
                x->lpVtbl->Release(x);  \
                x = NULL;               \
        } 
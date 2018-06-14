#ifndef __CMLUA__
#define __CMLUA__

typedef enum _SLLUA_ROOTKEY{
        SSLUA_HKEY_CLASSES_ROOT = 1,
        SSLUA_HKEY_CURRENT_CONFIG,
        SSLUA_HKEY_LOCAL_MACHINE,
        SSLUA_HKEY_USERS,
}SSLUA_ROOTKEY, *PSSLUA_ROOTKEY;

typedef interface ISLLUAComInstance ISLLUAComInstance;

    typedef struct ISLLUAComInstanceVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ISLLUAComInstance * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ISLLUAComInstance * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ISLLUAComInstance * This);
        
        ULONG ( STDMETHODCALLTYPE *SLLUAActivateProduct)(
            ISLLUAComInstance *This,
            GUID             *unknown,
            SAFEARRAY        *unknown0,
            VARIANT          *unknown1);
        
        ULONG ( STDMETHODCALLTYPE *SLLUADepositOfflineConfirmationId)(
            ISLLUAComInstance *This,
            GUID             *unknown,
            WCHAR            *unknown0,
            WCHAR            *unknown1);
        
        ULONG ( STDMETHODCALLTYPE *SLLUAInstallProofOfPurchase)(
            ISLLUAComInstance *This,
            WCHAR            *unknown,
            WCHAR            *unknown1,
            SAFEARRAY        *unknown2,
            GUID             *unknown3);
        
        ULONG ( STDMETHODCALLTYPE *SLLUARegKeySetValue)(
            ISLLUAComInstance *This,
            SSLUA_ROOTKEY    RegType,
            WCHAR            *wsRegPath,
            WCHAR            *wsValueName,
            SAFEARRAY        *ArrayData,
            DWORD            dwKeyType);    
                
                
        END_INTERFACE
    } ISLLUAComInstanceVtbl;

    interface ISLLUAComInstance
    {
        CONST_VTBL struct ISLLUAComInstanceVtbl *lpVtbl;
    };


#endif
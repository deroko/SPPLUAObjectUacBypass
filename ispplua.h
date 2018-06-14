#ifndef __SSPLUA__
#define __SPPLUA__

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


//Win7 definition
typedef interface ISLLUAComInstanceWin7 ISLLUAComInstanceWin7;

    typedef struct ISLLUAComInstanceWin7Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ISLLUAComInstanceWin7 * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ISLLUAComInstanceWin7 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ISLLUAComInstanceWin7 * This);
        
        ULONG ( STDMETHODCALLTYPE *SLLUAActivateProduct)(
            ISLLUAComInstanceWin7 *This,
            GUID             *unknown,
            SAFEARRAY        *unknown0,
            VARIANT          *unknown1);
        
        ULONG ( STDMETHODCALLTYPE *SLLUADepositOfflineConfirmationId)(
            ISLLUAComInstanceWin7 *This,
            GUID             *unknown,
            WCHAR            *unknown0,
            WCHAR            *unknown1);
        
        ULONG ( STDMETHODCALLTYPE *SLLUAFireEvent)(
            ISLLUAComInstanceWin7 *This,
            WCHAR                 *unknown,
            GUID                  *unknown0);
        
        ULONG ( STDMETHODCALLTYPE *SLLUAInstallLicense)(
            ISLLUAComInstanceWin7 *This,
            SAFEARRAY             *unknown,
            GUID                  *unknown0);
        
        ULONG ( STDMETHODCALLTYPE *SLLUAUninstallLicense)(
            ISLLUAComInstanceWin7 *This,
            GUID                  *unknown);             
        
        ULONG ( STDMETHODCALLTYPE *SLLUAInstallPackage)(
            ISLLUAComInstanceWin7 *This,
            ULONG                 unknown,
            ULONG                 unknown0,
            SAFEARRAY             *unknown1);
        
        ULONG ( STDMETHODCALLTYPE *SLLUACancelPackageInstall)(
            ISLLUAComInstanceWin7 *This);
            
        ULONG ( STDMETHODCALLTYPE *SLLUAQueryLicensePackageProgress)(
            ISLLUAComInstanceWin7 *This,
            ULONG_PTR             *unknown,
            ULONG_PTR             *unknown0,
            ULONG_PTR             *unknown1);
            
        ULONG ( STDMETHODCALLTYPE *SLLUAUninstallPackage)(
            ISLLUAComInstanceWin7 *This,
            SAFEARRAY             *unknown);
             
        ULONG ( STDMETHODCALLTYPE *SLLUAInstallProofOfPurchase)(
            ISLLUAComInstanceWin7 *This,
            WCHAR            *unknown,
            WCHAR            *unknown1,
            SAFEARRAY        *unknown2,
            GUID             *unknown3);
        
        ULONG (STDMETHODCALLTYPE *SLLUAUninstallProofOfPurchase)(
            ISLLUAComInstanceWin7 *This,
            GUID                  *unknown0);
        
        ULONG ( STDMETHODCALLTYPE *SLLUARegKeySetValue)(
            ISLLUAComInstanceWin7 *This,
            SSLUA_ROOTKEY    RegType,
            WCHAR            *wsRegPath,
            WCHAR            *wsValueName,
            SAFEARRAY        *ArrayData,
            DWORD            dwKeyType);    
                
                
        END_INTERFACE
    } ISLLUAComInstanceWin7Vtbl;

    interface ISLLUAComInstanceWin7
    {
        CONST_VTBL struct ISLLUAComInstanceWin7Vtbl *lpVtbl;
    };
#endif
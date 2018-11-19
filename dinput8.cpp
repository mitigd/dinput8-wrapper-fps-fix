#include "dinput8.h"

#pragma comment (lib, "dxguid.lib")

HINSTANCE mHinst, mHinstDLL;

DI8C proc_ddcreate;

HRESULT WINAPI DirectInput8Create(HINSTANCE hinst, DWORD dwVersion, REFIID riidltf, LPVOID * ppvOut, LPUNKNOWN punkOuter)
{

	HRESULT ret = proc_ddcreate(hinst, dwVersion, riidltf, ppvOut, punkOuter);

	// Redirect ANSI
	if (IsEqualIID(riidltf, IID_IDirectInput8A))
	{
		IDirectInput8A * pDInput = (IDirectInput8A *)*ppvOut;
		*ppvOut = new DirectInput8ProxyA(pDInput);

	}	
	// Redirect UNICODE
	else
	{
		IDirectInput8W * pDInput = (IDirectInput8W *)*ppvOut;
		*ppvOut = new DirectInput8ProxyW(pDInput);

	}

	return ret;

}

bool WINAPI DllMain(HMODULE hModule, DWORD fdwReason, LPVOID lpReserved) {
	static HMODULE dinput8dll = nullptr;
	switch (fdwReason)
	{
	case DLL_PROCESS_ATTACH:
	{

		char path[MAX_PATH];
		GetSystemDirectory(path, MAX_PATH);
		strcat_s(path, "\\dinput8.dll");
		dinput8dll = LoadLibrary(path);

		proc_ddcreate = (DI8C)GetProcAddress(dinput8dll, "DirectInput8Create");

	}
	case DLL_PROCESS_DETACH:
		FreeLibrary(hModule);
		break;
	}
	return true;
}

// ANSI
DirectInput8ProxyA::DirectInput8ProxyA(IDirectInput8A* pDInput)
{
	m_pDInput = pDInput;
}

HRESULT DirectInput8ProxyA::QueryInterface(REFIID riid, LPVOID * ppvObj)
{
	return m_pDInput->QueryInterface(riid, ppvObj);
}

ULONG DirectInput8ProxyA::AddRef()
{
	return m_pDInput->AddRef();
}

ULONG DirectInput8ProxyA::Release()
{

	ULONG uRet = m_pDInput->Release();

  if (uRet == 0)
		delete this;

	return uRet;
  
}

HRESULT DirectInput8ProxyA::CreateDevice(REFGUID rguid, LPDIRECTINPUTDEVICE8A * lplpDirectInputDevice, LPUNKNOWN pUknOuter)
{

	return m_pDInput->CreateDevice(rguid, lplpDirectInputDevice, pUknOuter);

}

HRESULT WINAPI DirectInput8ProxyA::EnumDevices(DWORD dwDevType, LPDIENUMDEVICESCALLBACKA lpCallback, LPVOID pvRef, DWORD dwFlags)
{

	if (dwDevType == DI8DEVTYPE_KEYBOARD)
	{
		HRESULT ret = m_pDInput->EnumDevices(dwDevType, lpCallback, pvRef, dwFlags);
		return ret;
	}

	if (dwDevType == DI8DEVTYPE_MOUSE)
	{
		HRESULT ret = m_pDInput->EnumDevices(dwDevType, lpCallback, pvRef, dwFlags);
		return ret;
	}

	else 
	{
		return NULL;
	}

}

HRESULT DirectInput8ProxyA::GetDeviceStatus(REFGUID rguidInstance)
{
	return m_pDInput->GetDeviceStatus(rguidInstance);
}

HRESULT DirectInput8ProxyA::RunControlPanel(HWND hwndOwner, DWORD dwFlags)
{
	return m_pDInput->RunControlPanel(hwndOwner, dwFlags);
}

HRESULT DirectInput8ProxyA::Initialize(HINSTANCE hinst, DWORD dwVersion)
{
	return m_pDInput->Initialize(hinst, dwVersion);
}

HRESULT DirectInput8ProxyA::FindDevice(REFGUID rguidClass, LPCSTR ptszName, LPGUID pguidInstance)
{
	return m_pDInput->FindDevice(rguidClass, ptszName, pguidInstance);
}

HRESULT DirectInput8ProxyA::EnumDevicesBySemantics(LPCSTR ptszUserName, LPDIACTIONFORMATA lpdiActionFormat, LPDIENUMDEVICESBYSEMANTICSCBA lpCallback, LPVOID pvRef, DWORD dwFlags)
{
	return m_pDInput->EnumDevicesBySemantics(ptszUserName, lpdiActionFormat, lpCallback, pvRef, dwFlags);
}

HRESULT DirectInput8ProxyA::ConfigureDevices(LPDICONFIGUREDEVICESCALLBACK lpdiCallback, LPDICONFIGUREDEVICESPARAMSA lpdiCDParams, DWORD dwFlags, LPVOID pvRefData)
{
	return m_pDInput->ConfigureDevices(lpdiCallback, lpdiCDParams, dwFlags, pvRefData);
}

// UNICODE
DirectInput8ProxyW::DirectInput8ProxyW(IDirectInput8W* pDInput)
{
	m_pDInput = pDInput;
}

HRESULT DirectInput8ProxyW::QueryInterface(REFIID riid, LPVOID * ppvObj)
{
	return m_pDInput->QueryInterface(riid, ppvObj);
}

ULONG DirectInput8ProxyW::AddRef()
{
	return m_pDInput->AddRef();
}

ULONG DirectInput8ProxyW::Release()
{

	ULONG uRet = m_pDInput->Release();

	if (uRet == 0)
		delete this;

	return uRet;
  
}

HRESULT DirectInput8ProxyW::CreateDevice(REFGUID rguid, LPDIRECTINPUTDEVICE8W * lplpDirectInputDevice, LPUNKNOWN pUknOuter)
{

	return m_pDInput->CreateDevice(rguid, lplpDirectInputDevice, pUknOuter);

}

HRESULT DirectInput8ProxyW::EnumDevices(DWORD dwDevType, LPDIENUMDEVICESCALLBACKW lpCallback, LPVOID pvRef, DWORD dwFlags)
{

	if (dwDevType == DI8DEVTYPE_KEYBOARD)
	{
		HRESULT ret = m_pDInput->EnumDevices(dwDevType, lpCallback, pvRef, dwFlags);
		return ret;
	}

	if (dwDevType == DI8DEVTYPE_MOUSE)
	{
		HRESULT ret = m_pDInput->EnumDevices(dwDevType, lpCallback, pvRef, dwFlags);
		return ret;
	}

	else
	{
		return NULL;
	}

}

HRESULT DirectInput8ProxyW::GetDeviceStatus(REFGUID rguidInstance)
{
	return m_pDInput->GetDeviceStatus(rguidInstance);
}

HRESULT DirectInput8ProxyW::RunControlPanel(HWND hwndOwner, DWORD dwFlags)
{
	return m_pDInput->RunControlPanel(hwndOwner, dwFlags);
}

HRESULT DirectInput8ProxyW::Initialize(HINSTANCE hinst, DWORD dwVersion)
{
	return m_pDInput->Initialize(hinst, dwVersion);
}

HRESULT DirectInput8ProxyW::FindDevice(REFGUID rguidClass, LPCWSTR ptszName, LPGUID pguidInstance)
{
	return m_pDInput->FindDevice(rguidClass, ptszName, pguidInstance);
}

HRESULT DirectInput8ProxyW::EnumDevicesBySemantics(LPCWSTR ptszUserName, LPDIACTIONFORMATW lpdiActionFormat, LPDIENUMDEVICESBYSEMANTICSCBW lpCallback, LPVOID pvRef, DWORD dwFlags)
{
	return m_pDInput->EnumDevicesBySemantics(ptszUserName, lpdiActionFormat, lpCallback, pvRef, dwFlags);
}

HRESULT DirectInput8ProxyW::ConfigureDevices(LPDICONFIGUREDEVICESCALLBACK lpdiCallback, LPDICONFIGUREDEVICESPARAMSW lpdiCDParams, DWORD dwFlags, LPVOID pvRefData)
{
	return m_pDInput->ConfigureDevices(lpdiCallback, lpdiCDParams, dwFlags, pvRefData);
}

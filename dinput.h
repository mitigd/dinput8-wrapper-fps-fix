#include <dinput.h>

typedef HRESULT(WINAPI *DI8C)(HINSTANCE hinst, DWORD dwVersion, REFIID riidltf, LPVOID * ppvOut, LPUNKNOWN punkOuter);

class DirectInput8ProxyA : public IDirectInput8A
{
private:
	IDirectInput8A* m_pDInput;

public:
	DirectInput8ProxyA(IDirectInput8A* pDInput);

	/*** IUnknown methods ***/
	STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID * ppvObj);
	STDMETHOD_(ULONG,AddRef)(THIS_);
	STDMETHOD_(ULONG,Release)(THIS_);

	/*** IDirectInput8A methods ***/
	STDMETHOD(CreateDevice)(THIS_ REFGUID rguid, LPDIRECTINPUTDEVICE8A * lplpDirectInputDevice, LPUNKNOWN pUknOuter);
	STDMETHOD(EnumDevices)(THIS_ DWORD dwDevType, LPDIENUMDEVICESCALLBACKA lpCallback, LPVOID pvRef, DWORD dwFlags);
	STDMETHOD(GetDeviceStatus)(THIS_ REFGUID rguidInstance);
	STDMETHOD(RunControlPanel)(THIS_ HWND hwndOwner, DWORD dwFlags);
	STDMETHOD(Initialize)(THIS_ HINSTANCE hinst, DWORD dwVersion);
	STDMETHOD(FindDevice)(THIS_ REFGUID rguidClass, LPCSTR ptszName, LPGUID pguidInstance);
	STDMETHOD(EnumDevicesBySemantics)(THIS_ LPCSTR ptszUserName, LPDIACTIONFORMATA lpdiActionFormat, LPDIENUMDEVICESBYSEMANTICSCBA lpCallback, LPVOID pvRef, DWORD dwFlags);
	STDMETHOD(ConfigureDevices)(THIS_ LPDICONFIGUREDEVICESCALLBACK lpdiCallback, LPDICONFIGUREDEVICESPARAMSA lpdiCDParams, DWORD dwFlags, LPVOID pvRefData);
};

class DirectInput8ProxyW : public IDirectInput8W
{
private:
	IDirectInput8W* m_pDInput;

public:
	DirectInput8ProxyW(IDirectInput8W* pDInput);

	/*** IUnknown methods ***/
	STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID * ppvObj);
	STDMETHOD_(ULONG, AddRef)(THIS_);
	STDMETHOD_(ULONG, Release)(THIS_);

	/*** IDirectInput8A methods ***/
	STDMETHOD(CreateDevice)(THIS_ REFGUID rguid, LPDIRECTINPUTDEVICE8W * lplpDirectInputDevice, LPUNKNOWN pUknOuter);
	STDMETHOD(EnumDevices)(THIS_ DWORD dwDevType, LPDIENUMDEVICESCALLBACKW lpCallback, LPVOID pvRef, DWORD dwFlags);
	STDMETHOD(GetDeviceStatus)(THIS_ REFGUID rguidInstance);
	STDMETHOD(RunControlPanel)(THIS_ HWND hwndOwner, DWORD dwFlags);
	STDMETHOD(Initialize)(THIS_ HINSTANCE hinst, DWORD dwVersion);
	STDMETHOD(FindDevice)(THIS_ REFGUID rguidClass, LPCWSTR ptszName, LPGUID pguidInstance);
	STDMETHOD(EnumDevicesBySemantics)(THIS_ LPCWSTR ptszUserName, LPDIACTIONFORMATW lpdiActionFormat, LPDIENUMDEVICESBYSEMANTICSCBW lpCallback, LPVOID pvRef, DWORD dwFlags);
	STDMETHOD(ConfigureDevices)(THIS_ LPDICONFIGUREDEVICESCALLBACK lpdiCallback, LPDICONFIGUREDEVICESPARAMSW lpdiCDParams, DWORD dwFlags, LPVOID pvRefData);
};

#ifndef __CADL_HPP__
#define __CADL_HPP__

// Class for ADL interface
class CADLCalls
{
	enum CallID
	{
		E_ADL_Main_Control_Create,
		E_ADL_Main_Control_Destroy,
		E_ADL_Adapter_Active_Get,
		E_ADL_Adapter_NumberOfAdapters_Get,
		E_ADL_Adapter_AdapterInfo_Get,
		E_ADL_Adapter_ID_Get,
		E_ADL_Overdrive5_CurrentActivity_Get,
		E_ADL_Overdrive5_ThermalDevices_Enum,
		E_ADL_Overdrive5_Temperature_Get,
		E_ADL_Overdrive5_FanSpeedInfo_Get,
		E_ADL_Overdrive5_FanSpeed_Get,
		E_ADL_Overdrive5_FanSpeed_Set,
		E_ADL_Overdrive5_FanSpeedToDefault_Set,
		E_ADL_Overdrive5_ODParameters_Get,
		E_ADL_Overdrive5_ODPerformanceLevels_Get,
		E_ADL_Overdrive5_ODPerformanceLevels_Set,
		E_ADL_Overdrive5_PowerControl_Caps,
		E_ADL_Overdrive5_PowerControlInfo_Get,
		E_ADL_Overdrive5_PowerControl_Get,
		E_ADL_Overdrive5_PowerControl_Set,
		E_ADL_CALLID_MAX
	};
	
	int               Error; // error code of the last call

protected:
	HINSTANCE         mHDLL;	// Handle to DLL
	char              *mCallName[E_ADL_CALLID_MAX];
	void              *mProcAddress[E_ADL_CALLID_MAX];

	static int ADL_Call_Stub(void)
	{
		return ADL_ERR_NOT_SUPPORTED;
	}

public:

	CADLCalls(): mHDLL(NULL)
	{
		for (int i = 0; i < E_ADL_CALLID_MAX; i++)
			mProcAddress[i] = ADL_Call_Stub;
	};

	CADLCalls(const char* dll_name): mHDLL(NULL)
	{
		for (int i = 0; i < E_ADL_CALLID_MAX; i++)
			mProcAddress[i] = ADL_Call_Stub;

		Init(dll_name);
	};

	~CADLCalls() 
	{
		if (mHDLL) FreeLibrary(mHDLL);
	}

	bool IsOK() { return mHDLL != NULL; }

	int LastError() { return Error; }

	const char* LastErrorStr()
	{
		switch (Error)
		{
			case ADL_OK_WAIT:
				return "All OK, but need to wait";
			case ADL_OK_RESTART:
				return "All OK, but need restart";
			case ADL_OK_MODE_CHANGE:
				return "All OK but need mode change";
			case ADL_OK_WARNING:
				return "All OK, but with warning";
			case ADL_OK:
				return "ADL function completed successfully";
			case ADL_ERR:
				return "Generic Error. Most likely one or more of the Escape calls to the driver failed!";
			case ADL_ERR_NOT_INIT:
				return "ADL not initialized";
			case ADL_ERR_INVALID_PARAM:
				return "One of the parameter passed is invalid";
			case ADL_ERR_INVALID_PARAM_SIZE:
				return "One of the parameter size is invalid";
			case ADL_ERR_INVALID_ADL_IDX:
				return "Invalid ADL index passed";
			case ADL_ERR_INVALID_CONTROLLER_IDX:
				return "Invalid controller index passed";
			case ADL_ERR_INVALID_DIPLAY_IDX:
				return "Invalid display index passed";
			case ADL_ERR_NOT_SUPPORTED:
				return "Function not supported by the driver";
			case ADL_ERR_NULL_POINTER:
				return "Null Pointer error";
			case ADL_ERR_DISABLED_ADAPTER:
				return "Call can't be made due to disabled adapter";
			case ADL_ERR_INVALID_CALLBACK:
				return "Invalid Callback";
			case ADL_ERR_RESOURCE_CONFLICT:
				return "Display Resource conflict";
			default:
				return "Unknown error";
		}
	}

	bool Init(const char* dll_name)
	{
		mCallName[E_ADL_Main_Control_Create]					= "ADL_Main_Control_Create";
		mCallName[E_ADL_Main_Control_Destroy]					= "ADL_Main_Control_Destroy";
		mCallName[E_ADL_Adapter_Active_Get]						= "ADL_Adapter_Active_Get";
		mCallName[E_ADL_Adapter_NumberOfAdapters_Get]			= "ADL_Adapter_NumberOfAdapters_Get";
		mCallName[E_ADL_Adapter_AdapterInfo_Get]				= "ADL_Adapter_AdapterInfo_Get";
		mCallName[E_ADL_Adapter_ID_Get]							= "ADL_Adapter_ID_Get";
		mCallName[E_ADL_Overdrive5_CurrentActivity_Get]			= "ADL_Overdrive5_CurrentActivity_Get";
		mCallName[E_ADL_Overdrive5_ThermalDevices_Enum]			= "ADL_Overdrive5_ThermalDevices_Enum";
		mCallName[E_ADL_Overdrive5_Temperature_Get]				= "ADL_Overdrive5_Temperature_Get";
		mCallName[E_ADL_Overdrive5_FanSpeedInfo_Get]			= "ADL_Overdrive5_FanSpeedInfo_Get";
		mCallName[E_ADL_Overdrive5_FanSpeed_Get]				= "ADL_Overdrive5_FanSpeed_Get";
		mCallName[E_ADL_Overdrive5_FanSpeed_Set]				= "ADL_Overdrive5_FanSpeed_Set";
		mCallName[E_ADL_Overdrive5_FanSpeedToDefault_Set]		= "ADL_Overdrive5_FanSpeedToDefault_Set";
		mCallName[E_ADL_Overdrive5_ODParameters_Get]			= "ADL_Overdrive5_ODParameters_Get";
		mCallName[E_ADL_Overdrive5_ODPerformanceLevels_Get]		= "ADL_Overdrive5_ODPerformanceLevels_Get";
		mCallName[E_ADL_Overdrive5_ODPerformanceLevels_Set]		= "ADL_Overdrive5_ODPerformanceLevels_Set";
		mCallName[E_ADL_Overdrive5_PowerControl_Caps]			= "ADL_Overdrive5_PowerControl_Caps";
		mCallName[E_ADL_Overdrive5_PowerControlInfo_Get]		= "ADL_Overdrive5_PowerControlInfo_Get";
		mCallName[E_ADL_Overdrive5_PowerControl_Get]			= "ADL_Overdrive5_PowerControl_Get";
		mCallName[E_ADL_Overdrive5_PowerControl_Set]			= "ADL_Overdrive5_PowerControl_Set";

		mHDLL = LoadLibrary(dll_name);

		if (mHDLL)
		{
			for (int i = 0; i < E_ADL_CALLID_MAX; i++)
			{
				void *addr = GetProcAddress(mHDLL, mCallName[i]);

				if (addr)
					mProcAddress[i] = addr;
			}
		}
		else fprintf(stderr, "Error: cannot load %d.\n", dll_name);

		return IsOK();
	}

	// ------------------------ wrappers for DLL calls ------------------------

	int ADL_Main_Control_Create(ADL_MAIN_MALLOC_CALLBACK callback, int iEnumConnectedAdapters)
	{
		return Error = (static_cast <int (*)(ADL_MAIN_MALLOC_CALLBACK, int)> (mProcAddress[E_ADL_Main_Control_Create]))
			(callback, iEnumConnectedAdapters);
	};
	
	int ADL_Main_Control_Destroy()
	{
		return Error = (static_cast <int (*)()> (mProcAddress[E_ADL_Main_Control_Destroy]))
			();
	};

	int ADL_Adapter_Active_Get(int iAdapterIndex, int *lpStatus)
	{
		return Error = (static_cast <int (*)(int,int*)> (mProcAddress[E_ADL_Adapter_Active_Get]))
			(iAdapterIndex, lpStatus);
	}

	int ADL_Adapter_NumberOfAdapters_Get(int *lpNumAdapters)
	{
		return Error = (static_cast <int (*)(int*)> (mProcAddress[E_ADL_Adapter_NumberOfAdapters_Get]))
			(lpNumAdapters);
	}

	int ADL_Adapter_AdapterInfo_Get(LPAdapterInfo lpInfo, int iInputSize)
	{
		return Error = (static_cast <int (*)(LPAdapterInfo, int)> (mProcAddress[E_ADL_Adapter_AdapterInfo_Get]))
			(lpInfo, iInputSize);
	}

	int ADL_Adapter_ID_Get(int iAdapterIndex, int *lpAdapterID)
	{
		return Error = (static_cast <int (*)(int,int*)> (mProcAddress[E_ADL_Adapter_ID_Get]))
			(iAdapterIndex, lpAdapterID);
	}
	
	// Overdrive 5 API
	int ADL_Overdrive5_CurrentActivity_Get(int iAdapterIndex, ADLPMActivity *lpActivity)
	{
		return Error = (static_cast <int (*)(int,ADLPMActivity*)> (mProcAddress[E_ADL_Overdrive5_CurrentActivity_Get]))
			(iAdapterIndex, lpActivity);
	}

	int ADL_Overdrive5_ThermalDevices_Enum(int iAdapterIndex, int iThermalControllerIndex, ADLThermalControllerInfo *lpThermalControllerInfo)
	{
		return Error = (static_cast <int (*)(int,int,ADLThermalControllerInfo*)> (mProcAddress[E_ADL_Overdrive5_ThermalDevices_Enum]))
			(iAdapterIndex, iThermalControllerIndex, lpThermalControllerInfo);
	}

	int ADL_Overdrive5_Temperature_Get(int iAdapterIndex, int iThermalControllerIndex, ADLTemperature *lpTemperature)
	{
		return Error = (static_cast <int (*)(int,int,ADLTemperature*)> (mProcAddress[E_ADL_Overdrive5_Temperature_Get]))
			(iAdapterIndex, iThermalControllerIndex, lpTemperature);
	}

	int ADL_Overdrive5_FanSpeedInfo_Get(int iAdapterIndex, int iThermalControllerIndex, ADLFanSpeedInfo *lpFanSpeedInfo)
	{
		return Error = (static_cast <int (*)(int,int,ADLFanSpeedInfo*)> (mProcAddress[E_ADL_Overdrive5_FanSpeedInfo_Get]))
			(iAdapterIndex, iThermalControllerIndex, lpFanSpeedInfo);
	}

	int ADL_Overdrive5_FanSpeed_Get(int iAdapterIndex, int iThermalControllerIndex, ADLFanSpeedValue *lpFanSpeedValue)
	{
		return Error = (static_cast <int (*)(int,int,ADLFanSpeedValue*)> (mProcAddress[E_ADL_Overdrive5_FanSpeed_Get]))
			(iAdapterIndex, iThermalControllerIndex, lpFanSpeedValue);
	}

	int ADL_Overdrive5_FanSpeed_Set(int iAdapterIndex, int iThermalControllerIndex, ADLFanSpeedValue *lpFanSpeedValue)
	{
		return Error = (static_cast <int (*)(int,int,ADLFanSpeedValue*)> (mProcAddress[E_ADL_Overdrive5_FanSpeed_Set]))
			(iAdapterIndex, iThermalControllerIndex, lpFanSpeedValue);
	}

	int ADL_Overdrive5_FanSpeedToDefault_Set(int iAdapterIndex, int iThermalControllerIndex)
	{
		return Error = (static_cast <int (*)(int,int)> (mProcAddress[E_ADL_Overdrive5_FanSpeedToDefault_Set]))
			(iAdapterIndex, iThermalControllerIndex);
	}
	int ADL_Overdrive5_ODParameters_Get(int iAdapterIndex, ADLODParameters *lpOdParameters)
	{
		return Error = (static_cast <int (*)(int,ADLODParameters*)> (mProcAddress[E_ADL_Overdrive5_ODParameters_Get]))
			(iAdapterIndex, lpOdParameters);
	}
	int ADL_Overdrive5_ODPerformanceLevels_Get(int iAdapterIndex, int iDefault, ADLODPerformanceLevels *lpOdPerformanceLevels)
	{
		return Error = (static_cast <int (*)(int,int,ADLODPerformanceLevels*)> (mProcAddress[E_ADL_Overdrive5_ODPerformanceLevels_Get]))
			(iAdapterIndex, iDefault, lpOdPerformanceLevels);
	}
	int ADL_Overdrive5_ODPerformanceLevels_Set(int iAdapterIndex, ADLODPerformanceLevels *lpOdPerformanceLevels)
	{
		return Error = (static_cast <int (*)(int,ADLODPerformanceLevels*)> (mProcAddress[E_ADL_Overdrive5_ODPerformanceLevels_Set]))
			(iAdapterIndex, lpOdPerformanceLevels);
	}

	int ADL_Overdrive5_PowerControl_Caps(int iAdapterIndex, int *lpSupported)
	{
		return Error = (static_cast <int (*)(int,int*)> (mProcAddress[E_ADL_Overdrive5_PowerControl_Caps]))
			(iAdapterIndex, lpSupported);
	}
	int ADL_Overdrive5_PowerControlInfo_Get(int iAdapterIndex, ADLPowerControlInfo *lpPowerControlInfo)
	{
		return Error = (static_cast <int (*)(int,ADLPowerControlInfo*)> (mProcAddress[E_ADL_Overdrive5_PowerControlInfo_Get]))
			(iAdapterIndex, lpPowerControlInfo);
	}
	int ADL_Overdrive5_PowerControl_Get(int iAdapterIndex, int *lpCurrentValue, int *lpDefaultValue)
	{
		return Error = (static_cast <int (*)(int,int*,int*)> (mProcAddress[E_ADL_Overdrive5_PowerControl_Get]))
			(iAdapterIndex, lpCurrentValue, lpDefaultValue);
	}
	int ADL_Overdrive5_PowerControl_Set(int iAdapterIndex, int iValue)
	{
		return Error = (static_cast <int (*)(int,int)> (mProcAddress[E_ADL_Overdrive5_PowerControl_Set]))
			(iAdapterIndex, iValue);
	}
};


class CADL: public CADLCalls
{
	bool mOK;

protected:
	static void* __stdcall ADL_Main_Memory_Alloc(int size)
	{
		return malloc(size);
	}

	static void __stdcall ADL_Main_Memory_Free(void* ptr)
	{
		if (ptr) free(ptr);
	}

public:
	int               mNumberAdapters;
	LPAdapterInfo     mpAdapterInfo;

	CADL(): mOK(false), mNumberAdapters(0), mpAdapterInfo(NULL) {}

	~CADL() 
	{
		ADL_Main_Control_Destroy();

		if (mpAdapterInfo) delete[] mpAdapterInfo;
	}

	bool IsOK() { return mOK && CADLCalls::IsOK(); }

	// init parent and some usefull structs
	bool Init(const char *dll_name)
	{
		if (CADLCalls::Init(dll_name))
		{
			if (ADL_OK == ADL_Main_Control_Create(ADL_Main_Memory_Alloc, 1))
			{
				if (ADL_OK == ADL_Adapter_NumberOfAdapters_Get(&mNumberAdapters))
				{
					if (mNumberAdapters)
					{
						mpAdapterInfo = new AdapterInfo[mNumberAdapters];

						if (mpAdapterInfo)
						{
							memset(mpAdapterInfo, 0, sizeof(AdapterInfo)*mNumberAdapters);

							// Get the AdapterInfo structure for all adapters in the system
							if (ADL_OK == ADL_Adapter_AdapterInfo_Get(mpAdapterInfo, sizeof(AdapterInfo)*mNumberAdapters))
							{
								mOK = true;
							}
							else fprintf(stderr, "Error: cannot get adapter info.\n");
						}
						else fprintf(stderr, "Error: cannot allocate memory for adapters.\n");
					}
					else fprintf(stderr, "Error: no any adapters present.\n");
				}
				else fprintf(stderr, "Error: cannot get the number of adapters.\n");
			}
			else fprintf(stderr, "Error: cannot initialize ADL interface.\n");
		}

		return mOK;
	};
};

#endif //__CADL_HPP__

#pragma once
#include <ctime>
#include <algorithm>
#include <functional>
#include <mutex> 
#include <list>

#include "skse64_common/Relocation.h"
#include "skse64_common/BranchTrampoline.h"

#include "skse64/PapyrusNativeFunctions.h"
#include "skse64/PapyrusEvents.h"
#include "skse64/GameRTTI.h"
#include "skse64/BSModelDB.h"
#include "skse64/PluginManager.h"
#include "skse64/PluginAPI.h"

#include "api/PapyrusVRAPI.h"
#include "api/VRManagerAPI.h"

#include "OpenVRUtils.h"
#include "VRManager.h"

namespace PapyrusVR
{
	//TODO: Trackers
	enum TrackedDevice
	{
		HMD = 0,
		RightController = 1,
		LeftController = 2
	};

	/***
		EXPERIMENTAL

		Returns a float array with the current pose for a device
		position[x,y,z] = returnValues[0,1,2] (currently in meters from playspace origin)
		rotation[x,y,z,w] = returnValues[3,4,5,6]
	***/
	void GetTrackedDevicePoseByID(StaticFunctionTag *base, UInt32 deviceEnum, VMArray<float> returnValues);

	//Used by papyrus scripts to register for Pose Events
	void RegisterForPoseUpdates(StaticFunctionTag *base, TESForm * thisForm);	
	void UnregisterForPoseUpdates(StaticFunctionTag *base, TESForm * thisForm);

	bool RegisterFuncs(VMClassRegistry* registry);

	void OnVRUpdate(); //Called once every pose update by the rendering thread

	#pragma region API

	//Papyrus
	extern RegistrationSetHolder<TESForm*> g_posesUpdateEventRegs;

	//C++ Plugins
	typedef std::function<void(float)> OnPoseUpdateCallback;
	typedef std::list<OnPoseUpdateCallback> PoseUpdateListeners;
	extern PoseUpdateListeners g_poseUpdateListeners; 
	VRManagerAPI* GetVRManager();

	#pragma endregion
	
	#pragma region Messaging Interface
	void OnSKSEMessageRecived(SKSEMessagingInterface::Message* message);
	void RegisterMessagingInterface(SKSEMessagingInterface* messagingInterface);
	void RegisterHandle(PluginHandle* handle);
	#pragma endregion
}
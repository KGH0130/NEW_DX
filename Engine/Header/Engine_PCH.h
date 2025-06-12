#pragma once
#pragma warning(disable: 4251)

#include <Windows.h>
#include <cassert>
#include <chrono>
#include <cstdint>
#include <d3d9.h>
#include <d3dx9.h>
#include <string>
#include <thread>
#include <typeindex>
#include <typeinfo>
#include <unordered_map>
#include <vector>

#include "Engine_Enum.h"
#include "Engine_Function.h"
#include "Engine_Macro.h"
#include "Engine_Struct.h"
#include "Engine_Typedef.h"

#include "Graphic_Device.h"
#include "Input_Enum.h"
#include "ObjectInfo.h"

#include "IClone.h"
#include "ILevel.h"
#include "ILoad.h"
#include "IObject.h"
#include "IResource.h"
#include "IState.h"

#include "ComponentManager.h"
#include "InputManager.h"
#include "LevelManager.h"
#include "ObjectManager.h"
#include "ResourceManager.h"
#include "StateMachine.h"
#include "TimeManager.h"

#include "GameInstance.h"

#include "Transform.h"
#include "ILevel.h"

bool ILevel::OnLoading(GameInstance* Instance)
{
	instance = Instance;
	Loading();
	Initialize();
	return true;
}

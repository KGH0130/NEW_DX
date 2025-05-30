#include "ILevel.h"

void ILevel::OnLoading(GameInstance* Instance)
{
	instance = Instance;
	Loading();
	Initialize();
}

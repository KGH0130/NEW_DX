

void Main_Level::Initialize()
{
	instance->Object.Init(RENDER_TYPE::PRIORITY, "Player");
	instance->Object.Init(RENDER_TYPE::NONE, "MainCamera");
}

void Main_Level::Loading()
{
	instance->Object.Register("Player", new Player(instance), CREATE_TYPE::STATIC);
	instance->Object.Register("MainCamera", new MainCamera(instance), CREATE_TYPE::STATIC);
}

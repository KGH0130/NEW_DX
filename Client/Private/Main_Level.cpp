

void Main_Level::Initialize()
{
	instance->Object.Init(RENDER_TYPE::PRIORITY, "Player");
}

void Main_Level::Loading()
{
	instance->Camera.Register("MainCamera", new MainCamera(instance));
	instance->Object.Register("Player", new Player(instance), CREATE_TYPE::STATIC);

}

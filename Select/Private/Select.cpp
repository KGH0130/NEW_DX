
int main()
{
	ServerManager server;
	if(!server.Init())
		return -1;

	server.Run();
}
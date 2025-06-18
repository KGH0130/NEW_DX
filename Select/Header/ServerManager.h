#pragma once

class ClientSession;

class ServerManager
{
public:
	~ServerManager();

public:
	bool Init();

	void Run();

	void FixedUpdate();
	void SelectUpdate();

private:
	void AcceptClient();
	void CloseClient(SOCKET Sock);
private:
	SOCKET m_Socket = INVALID_SOCKET;
	std::unordered_map<SOCKET, ClientSession*> m_Clients;

	uint32_t m_ClientCount = 0u;
};
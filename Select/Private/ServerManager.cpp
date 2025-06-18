#include "ServerManager.h"

ServerManager::~ServerManager()
{
	for(auto& [socket, session] : m_Clients)
	{
		delete session;
		session = nullptr;
	}
	m_Clients.clear();

	if(m_Socket != INVALID_SOCKET)
	{
		closesocket(m_Socket);
		m_Socket = INVALID_SOCKET;
	}
	WSACleanup();
}

bool ServerManager::Init()
{
	WSADATA data{};
	if(WSAStartup(MAKEWORD(2, 2), &data) != 0)
	{
		std::cerr << "초기화 실패\n";
		return false;
	}

	m_Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(m_Socket == INVALID_SOCKET)
	{
		std::cerr << "소켓 생성 실패\n";
		WSACleanup();
		return false;
	}

	SOCKADDR_IN addr{};
	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	if(bind(m_Socket, reinterpret_cast<const sockaddr*>(&addr), sizeof(SOCKADDR_IN)) == SOCKET_ERROR)
	{
		std::cerr << "바인드 실패\n";
		closesocket(m_Socket);
		WSACleanup();
		return false;
	}

	if(listen(m_Socket, SOMAXCONN) == SOCKET_ERROR)
	{
		std::cerr << "리슨 실패\n";
		closesocket(m_Socket);
		WSACleanup();
		return false;
	}

	std::cout << "서버 대기 중\n";
	return true;
}

void ServerManager::Run()
{
	const int TICK_RATE = 30;
	const int TICK_INTERVAL_MS = 1000 / TICK_RATE;

	std::chrono::steady_clock::time_point lastTick = std::chrono::steady_clock::now();

	while(true)
	{
		auto now = std::chrono::steady_clock::now();
		auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastTick);

		if(elapsed.count() >= TICK_INTERVAL_MS)
		{
			FixedUpdate();
			lastTick = now;
		}

		SelectUpdate();
	}
}

void ServerManager::FixedUpdate()
{

}

void ServerManager::SelectUpdate()
{
	while(true)
	{
		FD_SET readSet{}, writeSet{};

		FD_SET(m_Socket, &readSet);

		//for(auto& [socket, session] : m_Clients)
		//{
		//	FD_SET(socket, &readSet);
		//	// if(session->NeadSend())
		//	//	FD_SET(socket, &writeSet);
		//}

		if(select(0, &readSet, &writeSet, nullptr, nullptr) == SOCKET_ERROR)
			continue;

		if(FD_ISSET(m_Socket, &readSet))
			AcceptClient();

		std::unordered_set<SOCKET> removeSock;

		//for(auto& [socket, session] : m_Clients)
		//{
		//	if(FD_ISSET(socket, &readSet) && session->OnRecv())
		//		removeSock.emplace(socket);
		//	if(FD_ISSET(socket, &writeSet) && session->OnSend())
		//		removeSock.emplace(socket);
		//}

		//for(auto& var : removeSock)
		//{
		//	if(m_Clients.count(var))
		// {
		// CloseClient(var);
		// 
		//	}	
		//}
	}
}

void ServerManager::AcceptClient()
{
	SOCKET sock = accept(m_Socket, nullptr, nullptr);
	if(sock == INVALID_SOCKET)
	{
		std::cout << "클라이언트 접속 실패\n";
		return;
	}
	//ClientSession* session = new ClientSession(sock, this);
	//m_Clients.emplace(sock, session);
	++m_ClientCount;
	std::cout << "클라이언트 접속(" << sock << ")\n" << "현재 인원(" << m_ClientCount << ")\n";
}

void ServerManager::CloseClient(SOCKET Sock)
{
	--m_ClientCount;
	std::cout << "클라이언트 종료(" << Sock << ")\n" << "현재 인원(" << m_ClientCount << ")\n";
	delete m_Clients[Sock];
	m_Clients[Sock] = nullptr;
	m_Clients.erase(Sock);
	closesocket(Sock);
}
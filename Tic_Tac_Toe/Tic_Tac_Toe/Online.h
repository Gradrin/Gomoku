#pragma once
#include <SFML/Network.hpp>
#include<string>
#include<thread>
#include <condition_variable>
#include <mutex>
#include"GameState.h"


#define logl(x) std::cout << x << std::endl
#define log(x) std::cout << x

class Online 
{
private:
	std::size_t received;

	sf::IpAddress address = "localHost";
	
	sf::TcpListener listener;

	std::vector<sf::TcpSocket*> client_array;


	GameState &gameState;
	std::condition_variable cv;

	//Indicating flags (you are host or client)
	bool hosting;
	bool connected;

	//Flags to connect or hosting server
	bool connection;
	bool host;

	int port;


public:
	std::mutex mutex;
	sf::TcpSocket hostSocket;
	sf::TcpSocket socket;
	sf::Packet packet;
	Online(GameState& gameState)
		:gameState(gameState)
	{
		port = 9999;
		received = 0;
		hosting = false;
		connected = false;

		connection = false;
		host = false;;
	}

	~Online()
	{

	}



	//Functions that return connection or hosting flag

	bool Hosting() const
	{
		return this->hosting;
	}

	bool IsConnected() const
	{
		return this->connected;
	}

	//Functions that return host or client flag

	bool IsHosted() const
	{
		return this->host;
	}

	//Functions that return packet

	const sf::Packet& getPacket()const
	{
		return this->packet;
	}

	//Functions that return sockets

	const sf::TcpSocket& getSocket()
	{
		return this->socket;
	}

	const sf::TcpSocket& getHostSocket()
	{
		return this->hostSocket;
	}

	bool Connection() const
	{
		return this->connection;
	}

	//Functions that return address and port

	sf::IpAddress getAdress() const
	{
		return this->address;
	}

	std::string getPort()
	{
		return std::to_string(port);
	}

	//void functions

	void ConnectClients()
	{
		while (true)
		{
			std::unique_lock<std::mutex> lock(mutex);
			cv.wait(lock, [this] { return hosting == true || connection == true || host == true || connected == true; });


			if ((hosting == true) && (connected == false))
			{
				hosting = false;
				if (listener.listen(port) == sf::Socket::Done)
				{
					logl(" Server is Started");
					hostSocket.connect(address, port);
					if (listener.accept(hostSocket) == sf::Socket::Done)
					{
						socket.setBlocking(false);
						logl("Added client " << socket.getRemoteAddress() << ":" << socket.getRemotePort() << " on slot ");
						host = true;
					}
				}
				else
					logl("Can not create the server");
			}


			if ((connection == true) && (host == false))
			{
				connection = false;
				if (socket.connect(address, port) != sf::Socket::Done)
				{
					logl("Could not connect to the server\n");
				}
				else
				{
					logl("Connected to the server\n");
					connected = true;
				}
			}

			if ((host == true) && (connected == false))
			{
				if (listener.accept(socket) == sf::Socket::Done)
				{
					socket.setBlocking(false);
					logl("Added client " << socket.getRemoteAddress() << ":" << socket.getRemotePort() << " on slot ");
					host = true;
				}
			}	

		}
	}
	
	void IsConnectionVariable(bool variable)
	{
		std::unique_lock<std::mutex> lock(mutex);
		connection = true;
		cv.notify_all();
	}

	void HostingVariable(bool variable)
	{
		std::unique_lock<std::mutex> lock(mutex);
		hosting = variable;
		cv.notify_all();
	}

	//Functions to send information to sockets

	void HostSocket(int* variable, GameState& gamestate)
	{
		hostSocket.send(variable, gamestate);
	}

	void ClientSocket(int *variable,GameState &gamestate)
	{
		socket.send(variable, gamestate);
	}

	void HostSocket(int gamestate)
	{
		packet << gamestate;
		hostSocket.send(packet);
	}

	void ClientSocketReceive()
	{
		
	}
	void c()
	{
		connected = false;
	}
};


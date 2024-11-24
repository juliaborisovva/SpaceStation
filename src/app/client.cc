#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#include <cstring>
#include <iostream>
#include <string>

#define PORT 8080
#define BUF_SIZE 1024

namespace client {
enum class ErrorCode {
    kSuccess = 0,
    kSocketCreationFail = -1,
    kConnectionFail = -2,
    kDisconnected
};

enum class OperatingMode { kRead = 0, kSend = 1, kExit = -1 };
}  // namespace client

client::ErrorCode ReadServer(const int& sock, char* buf)
{
    client::ErrorCode err = client::ErrorCode::kSuccess;
    ssize_t bytes_received = read(sock, buf, BUF_SIZE);
    if (bytes_received <= 0) {
        // проверка, что не отключился
        std::cerr << "Server disconnected\n";
        err = client::ErrorCode::kDisconnected;
    }
    buf[bytes_received] = '\0';  // Завершаем строку
    return err;
}

int main()
{
    int err = static_cast<int>(client::ErrorCode::kSuccess);

    // сокет для подключения к серверу
    // AF_INET - ipv4
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        std::cerr << "Socket creation failed\n";
        err = static_cast<int>(client::ErrorCode::kSocketCreationFail);
    } else {
        // адрес сервера
        sockaddr_in server_address;
        server_address.sin_family = AF_INET;
        server_address.sin_port = htons(PORT);
        server_address.sin_addr.s_addr = inet_addr("127.0.0.1");  // Адрес локальной машины

        // подключение
        if (connect(sock, (struct sockaddr*)&server_address, sizeof(server_address)) < 0) {
            std::cerr << "Connection failed\n";
            err = static_cast<int>(client::ErrorCode::kConnectionFail);
        } else {
            std::cout << "Connected to server!\n";
            char buf[BUF_SIZE];
            client::OperatingMode flag = client::OperatingMode::kRead;
            while (true) {
                // Чтение и вывод
                if (flag == client::OperatingMode::kRead) {
                    // читаем сообщение от сервера
                    if (ReadServer(sock, buf) == client::ErrorCode::kDisconnected) {
                        break;
                    }
                    // найден запрос на сообщение
                    if (std::strstr(buf, "REQUEST") != nullptr) {
                        flag = client::OperatingMode::kSend;

                        std::string str_buf = std::string(buf);
                        str_buf.resize(str_buf.size() - 7);
                        std::cout << str_buf << std::endl;
                        continue;
                    } else if (std::strstr(buf, "EXIT") != nullptr) {
                        // найден запрос на выход
                        std::cout << std::string(buf) << std::endl;
                        std::cout << "Exit. Closing connection...\n";
                        break;
                    }
                    std::cout << std::string(buf) << std::endl;
                } else if (flag == client::OperatingMode::kSend) {
                    //  ввод команды клиентом
                    std::string user_input;
                    std::getline(std::cin, user_input);
                    if (user_input.empty() == true) {
                        std::cout << "There is no input, try again\n";
                        continue;
                    }
                    send(sock, user_input.c_str(), user_input.length(), 0);
                    flag = client::OperatingMode::kRead;  // снова чтение и вывод
                } else {
                    break;
                }
            }
        }
        // закрываем сокет
        close(sock);
    }
    return err;
}

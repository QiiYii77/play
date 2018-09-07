#include <iostream>
#include <arpa/inet.h>
#include <sys/socket.h>

using namespace std;

bool routine(int routine_socket)
{
    char buff[200];
    int received_byte = recv(routine_socket, buff, 200, 0);
    //cout << "received " << received_byte << " bytes" << endl;
    cout << buff << endl;
}

int main()
{
    const char *ip_addr_str = "127.0.0.1";
    sockaddr_in local_sin;
    local_sin.sin_family = AF_INET;
    inet_pton(AF_INET, ip_addr_str, &local_sin.sin_addr.s_addr);
    local_sin.sin_port = htons(7777);
    
    int listen_socket = socket(AF_INET, SOCK_STREAM, 0);
    bind(listen_socket, (sockaddr *) &local_sin, sizeof(local_sin));
    listen(listen_socket, 16);

    while (true)
    {
        sockaddr_in remote_sin;
        socklen_t remote_sin_len;
        int routine_socket = accept(listen_socket, (sockaddr *) &remote_sin, &remote_sin_len);
        routine(routine_socket);
    }
    
    return 0;
}

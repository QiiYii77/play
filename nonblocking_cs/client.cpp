#include <iostream>
#include <string>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

using namespace std;

int count = 1;

bool routine()
{
    cout<<"run routine"<<endl;
}

int main()
{
    const char *ip_addr_str = "127.0.0.1";
    sockaddr_in remote_sin;
    remote_sin.sin_family = AF_INET;
    inet_pton(AF_INET, ip_addr_str, &remote_sin.sin_addr.s_addr);
    remote_sin.sin_port = htons(7777);
    
    for (int i=0; i<10; i++)
    {
        int client_socket = socket(AF_INET, SOCK_STREAM, 0);
        connect(client_socket, (sockaddr *) &remote_sin, sizeof(remote_sin));

        string sending_msg = "Hello from client " + to_string(count);
        int remaining = sending_msg.length();
        const char *cp = sending_msg.c_str();
        cout<<sending_msg<<endl;
        while (remaining)
        {
            int sent_byte = send(client_socket, cp, remaining, 0);
	    cout << "sent " << sent_byte << " bytes" << endl;
            remaining -= sent_byte;
            cp += sent_byte;
        }
	close(client_socket);
	count++;
    }

    return 0;
}

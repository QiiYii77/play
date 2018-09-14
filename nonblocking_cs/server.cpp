#include <iostream>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <string.h>

using namespace std;

bool add_socket(int epoll_fd, int socket)
{
    struct epoll_event ev;
    ev.events = EPOLLIN;
    ev.data.fd = socket;
    epoll_ctl(epoll_fd, EPOLL_CTL_ADD, socket, &ev);
}

bool do_accept(int epoll_fd, int listen_socket)
{
    sockaddr_in remote_sin;
    socklen_t remote_sin_len;
    int routine_socket = accept(listen_socket, (sockaddr *) &remote_sin, &remote_sin_len);
    fcntl(routine_socket, F_SETFL, O_NONBLOCK);
    add_socket(epoll_fd, routine_socket);
}

bool routine(int routine_socket)
{
    char buff[200];
    memset(buff, 0x00, sizeof(buff));
    int received_byte = recv(routine_socket, buff, 200, 0);
    if (received_byte == 0)
    {
        close(routine_socket);
	return false;
    }
    cout << "received " << received_byte << " bytes" << endl;
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
    fcntl(listen_socket, F_SETFL, O_NONBLOCK);
    bind(listen_socket, (sockaddr *) &local_sin, sizeof(local_sin));
    listen(listen_socket, 16);

    int epoll_fd = epoll_create(10);
    add_socket(epoll_fd, listen_socket);

    struct epoll_event events[10];
    while (true)
    {
        int fds = epoll_wait(epoll_fd, events, 10, -1);
        for (int i=0; i<fds; i++)
	{
            if (events[i].data.fd == listen_socket)
            {
                do_accept(epoll_fd, listen_socket);
	    }
	    else if (events[i].events & EPOLLHUP)
	    {
		close(events[i].data.fd);
		cout << "closed socket " << events[i].data.fd << endl;
	    }
	    else if (events[i].events & EPOLLIN)
            {
                routine(events[i].data.fd);
            }
        }
    }
    
    return 0;
}

#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define CLIENT_PIPE_PATH "/tmp/fifo.client"
#define SERVER_PIPE_PATH "/tmp/fifo.server"

int main()
{
    auto &log = std::cout;
    
    log << "Open read-pipe(in-progress)\n";
    auto server_pipe = open(SERVER_PIPE_PATH, O_RDONLY);
    if (server_pipe != -1)
    {
        log << "Open read-pipe(done)\n";
        {
            char buf[BUFSIZ];
            for (ssize_t(msg_siz); msg_siz = read(server_pipe, buf, sizeof(buf)), msg_siz > 0;)
            {
                log << "from server: " << buf << '\n';
            }
        }
        log << "Close read-pipe(done)\n";
        close(server_pipe);
    }
    else
    {
        log << "Open read-pipe(failed)\n";
    }

    log << "Open write-pipe(in-progress)\n";
    auto client_pipe = open(CLIENT_PIPE_PATH, O_WRONLY);
    if (client_pipe != -1)
    {
        log << "Open write-pipe(done)\n";
        {
            auto msg = "exit";
            log << "Send message",
                write(client_pipe, msg, strlen(msg)),
                log << "(done)\n";
        }
        log << "Close write-pipe(done)\n";
        close(client_pipe);
    }
    else
    {
        log << "Open read-pipe(failed)\n";
    }

    return EXIT_SUCCESS;
}
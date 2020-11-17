#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>

#define FILE_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)
#define CLIENT_PIPE_PATH "/tmp/fifo.client"
#define SERVER_PIPE_PATH "/tmp/fifo.server"

int main()
{
    auto &log = std::cout;

    log << "Creating pipes",
        mkfifo(CLIENT_PIPE_PATH, FILE_MODE),
        mkfifo(SERVER_PIPE_PATH, FILE_MODE),
        log << "(done)\n";
        

    log << "Open write-pipe(in-progress)\n";
    auto server_pipe = open(SERVER_PIPE_PATH, O_WRONLY);
    if (server_pipe != -1)
    {
        log << "Open write-pipe(done)\n";
        {
            auto msg = "message from the server";
            log << "Send message",
                write(server_pipe, msg, strlen(msg)),
                log << "(done)\n";
        }
        log << "Close write-pipe(done)\n";
        close(server_pipe);
    }
    else
    {
        log << "(failed)\n";
    }

    log << "Open read-pipe(in-progress)\n";
    auto client_pipe = open(CLIENT_PIPE_PATH, O_RDONLY);
    if (client_pipe != -1)
    {
        log << "Open read-pipe(done)\n";
        {
            char buf[BUFSIZ];
            for (ssize_t(msg_siz); msg_siz = read(client_pipe, buf, sizeof(buf)), msg_siz > 0;)
            {
                log << "from client: " << buf << '\n';
            }
        }
        log << "Close read-pipe(done)\n";
        close(client_pipe);
    }
    else
    {
        log << "(failed)\n";
    }

    return EXIT_SUCCESS;
}
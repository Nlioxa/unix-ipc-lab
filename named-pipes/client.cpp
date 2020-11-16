#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>

#define WRIT_PIPE "../fifo1.txt"
#define READ_PIPE "../fifo2.txt"

int main(int argc, char **argv)
{
    auto &log = std::cout;
    
    log << "Open read-pipe(in-progress)\n";
    auto server_pipe = open(READ_PIPE, O_RDONLY);
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
        close(server_pipe);
        log << "Close read-pipe(done)\n";
    }
    else
    {
        log << "Open read-pipe(failed)\n";
    }

    log << "Open write-pipe(in-progress)\n";
    auto client_pipe = open(WRIT_PIPE, O_WRONLY);
    if (client_pipe != -1)
    {
        log << "Open write-pipe(done)\n";
        {
            auto msg = "exit";
            log << "Send message",
                write(client_pipe, msg, strlen(msg)),
                log << "(done)\n";
        }
        close(client_pipe);
        log << "Close write-pipe(done)\n";
    }
    else
    {
        log << "Open read-pipe(failed)\n";
    }

    return EXIT_FAILURE;
}
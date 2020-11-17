#include "channel.hpp"
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

#define FILE_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)
#define PIPE_DIR_PATH "/tmp/fifo."

ipc::Channel ipc::Channel::Client(int port)
{
    return Channel(port, SideType::Client);
}

ipc::Channel ipc::Channel::Server(int port)
{
    return Channel(port, SideType::Server);
}

bool ipc::Channel::Write(char *inp_stream, unsigned size, bool blocking)
{
    auto mode = O_WRONLY | (blocking ? 0 : O_NONBLOCK);
    
    auto write_dsc = open(_pipe_write, mode);

    auto written_bytes_num = write(write_dsc, inp_stream, size);

    close(write_dsc);

    return written_bytes_num != -1;
}

bool ipc::Channel::Read(char *out_stream, unsigned size, bool blocking)
{
    auto mode = O_RDONLY | (blocking ? 0 : O_NONBLOCK);
    
    auto read_dsc = open(_pipe_read, mode);

    auto result = read(read_dsc, out_stream, size);

    close(read_dsc);

    return result > 0; // test for either EOF or any error
}

ipc::Channel::Channel(int port, SideType type)
    : _type(type)
{
    const auto buf_siz = 50u;
    char port_name[buf_siz];

    sprintf(port_name, "%d", port);

    strcpy(_pipe_read, PIPE_DIR_PATH);
    strcpy(_pipe_write, PIPE_DIR_PATH);

    switch (type)
    {
    case SideType::Client:
        strcat(_pipe_read, "server.");
        strcat(_pipe_write, "client.");
        break;
    case SideType::Server:
        strcat(_pipe_read, "client.");
        strcat(_pipe_write, "server.");
    }

    strcat(_pipe_read, port_name);
    strcat(_pipe_write, port_name);

    mkfifo(_pipe_read, FILE_MODE);
    mkfifo(_pipe_write, FILE_MODE);
}
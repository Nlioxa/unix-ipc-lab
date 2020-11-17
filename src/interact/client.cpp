#include "../message.hpp"
#include "../channel.hpp"

#include <unistd.h>

int main(int argc, char **argv)
{
    auto &log = std::cout;

    if (argc <= 1)
    {
        log << "usage: Client [-t]<message_text>\n";
        return EXIT_SUCCESS;
    }

    auto msg = data::Message();

    for (int opt; opt = getopt(argc, argv, "ts:m:"), opt != -1;)
    {
        switch (opt)
        {
        case 't':
            msg = data::Message::Terminate();
            break;
        case 's':
            msg.set_type(data::MessageType::Service);
        case 'm':
            msg.set_data(optarg);
        }
    }

    auto channel = ipc::Channel::Client(8000);

    channel.Write((char *)&msg, sizeof(data::Message), false);

    if (msg.type() == data::MessageType::Service)
    {
        channel.Read((char *)&msg, sizeof(data::Message));
        log << "server: " << msg << '\n';
    }

    return EXIT_SUCCESS;
}
#include "../message.hpp"
#include "../channel.hpp"

#include <unistd.h>

int main()
{
    auto &log = std::cout;

    auto channel = ipc::Channel::Server(8000);

    log << "listening...\n";

    for (auto msg = data::Message(); msg.type() != data::MessageType::Terminate;)
    {
        channel.Read((char *)&msg, sizeof(data::Message));

        log << "server: ";

        switch (msg.type())
        {
        case data::MessageType::Notice:
        {
            log << "got message \"" << msg << "\"\n";
        }
        break;
        case data::MessageType::Service:
        {
            log << "running a service \"" << msg << "\"\n";
            
            sleep(2);
            
            log << "server: finished \"" << msg << "\"\n";
            
            msg.set_data("service finished");
            channel.Write((char *)&msg, sizeof(data::Message));
        }
        break;
        case data::MessageType::Terminate:
        {
            log << "terminated\n";
        }
        break;
        }
    }

    return EXIT_SUCCESS;
}
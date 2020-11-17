#include "../message.hpp"
#include "../channel.hpp"

int main()
{
    auto channel = ipc::Channel::Server(8000);

    {
        auto msg = data::Message::Notice("Connection established.");
        channel.Write((char *)&msg, sizeof(msg));
    }

    {
        auto msg = data::Message();
        channel.Read((char *)&msg, sizeof(msg));
        std::cout << "broadcast: " << msg << '\n';
    }

    return EXIT_SUCCESS;
}
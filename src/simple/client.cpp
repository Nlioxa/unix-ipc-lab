#include "../message.hpp"
#include "../channel.hpp"

int main(int argc, char **argv)
{
    auto channel = ipc::Channel::Client(8000);

    {
        auto msg = data::Message();
        channel.Read((char *)&msg, sizeof(msg));
        std::cout << msg << '\n';
    }

    {
        auto msg = data::Message::Notice("Hi, All!");
        channel.Write((char *)&msg, sizeof(msg));
    }

    return EXIT_SUCCESS;
}
#include <cstring>
#include "message.hpp"

data::Message data::Message::Notice(char const *data)
{
    auto msg = Message(MessageType::Notice);
    msg._size = std::min(strlen(data), size_t(BUFSIZ));
    strncpy(msg._data, data, msg._size);
    msg._data[msg._size] = 0;
    return msg;
}

data::Message data::Message::Terminate()
{
    auto msg = Message(MessageType::Terminate);
    return msg;
}

data::MessageType data::Message::type() const
{
    return _type;
}

void data::Message::set_type(MessageType type)
{
    _type = type;
}

void data::Message::set_data(char const *data)
{
    strncpy(_data, data, std::min(strlen(data), size_t(BUFSIZ)));
}

data::Message::Message(MessageType type)
    : _type(type)
{
}

#include <iostream>

namespace data
{
    enum class MessageType
    {
        Service = 0,
        Notice,
        Terminate
    };

    class Message
    {
    public:
        Message() = default;

        static Message Notice(char const *msg);
        static Message Terminate();

        friend std::ostream &operator<<(std::ostream &os, Message const &msg)
        {
            return os << msg._data;
        }

        MessageType type() const;
        void set_type(MessageType type);
        void set_data(char const *data);

    protected:
        Message(MessageType type);

    private:
        MessageType _type = MessageType::Notice;
        size_t _size = 0;
        char _data[BUFSIZ];
    };
} // namespace msg
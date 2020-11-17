#define PIPE_PATH_LEN 100

namespace ipc
{
    enum class SideType
    {
        Server = 0,
        Client
    };

    class Channel
    {
    public:
        static Channel Client(int port);
        static Channel Server(int port);

        bool Write(char *data, unsigned size, bool blocking = true);
        bool Read(char *data, unsigned size, bool blocking = true);

    protected:
        Channel(int port, SideType);

    private:
        SideType _type;
        char _pipe_write[PIPE_PATH_LEN];
        char _pipe_read[PIPE_PATH_LEN];
    };
} // namespace ipc
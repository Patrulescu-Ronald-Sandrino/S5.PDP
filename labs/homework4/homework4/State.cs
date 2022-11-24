using System.Net;
using System.Net.Sockets;
using System.Text;

namespace homework4
{
    public class State
    {
        public Socket Socket;
        public string Hostname;
        public string EndPointPath;
        public IPEndPoint RemoteEndPoint;
        public int ClientId;

        public const int BufferSize = 1024;
        public readonly byte[] Buffer = new byte[BufferSize];
        public readonly StringBuilder Response = new StringBuilder();

        
        public void ReleaseSocket()
        {
            Socket.Shutdown(SocketShutdown.Both);
            Socket.Close();
        }
    }
}
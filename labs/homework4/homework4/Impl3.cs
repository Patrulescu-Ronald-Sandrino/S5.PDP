using System;
using System.Threading.Tasks;

namespace homework4
{
    public static class Impl3 // async tasks
    {
        public static void Run(string[] hosts)
        {
            var tasks = new Task[hosts.Length];
            
            for (var i = 0; i < hosts.Length; i++)
            {
                var id = i; // because -i- is not effectively final
                tasks[i] = Task.Factory.StartNew(() => StartClient(hosts[id], id));
            }

            Task.WaitAll(tasks);
        }

        private static async void StartClient(string host, int id)
        {
            var state = Http.GetState(host, id);
            
            // connect to the remote endpoint
            await Connect(state);
            
            // request data from the server
            await Send(state, Http.GetRequestStringAsBytes(host, state.EndPointPath));
            
            // receive the response from the server
            await Receive(state);

            // all data received
            var body = Http.GetResponseBody(state.Response.ToString());
            Console.WriteLine($"Client {state.ClientId} received {body.Length} bytes from server.");
            Console.WriteLine($"Client {state.ClientId} received response: {body}\n");
                    
            state.ReleaseSocket();
        }

        private static async Task Connect(State state)
        {
            state.Socket.BeginConnect(state.RemoteEndPoint, ConnectCallback, state);
            
            await Task.FromResult(state.ConnectDone.WaitOne());
        }

        private static void ConnectCallback(IAsyncResult ar)
        {
            // retrieve the connection info
            var state = (State) ar.AsyncState;
            var clientSocket = state.Socket;
            var clientId = state.ClientId;
            var hostname = state.Hostname;
            
            // complete the connection
            clientSocket.EndConnect(ar);
            Console.WriteLine($"Client {clientId} connected to {hostname} ({clientSocket.RemoteEndPoint})");
            
            // signal that the connection has been made
            state.ConnectDone.Set();
        }

        private static async Task Send(State state, byte[] data)
        {
            state.Socket.BeginSend(data, 0, data.Length, 0, SendCallback, state);

            await Task.FromResult(state.SendDone.WaitOne());
        }

        private static void SendCallback(IAsyncResult ar)
        {
            var state = (State) ar.AsyncState;
            var clientSocket = state.Socket;
            var clientId = state.ClientId;
            
            // complete the sending of the data to the server
            var bytesSent = clientSocket.EndSend(ar);
            Console.WriteLine($"Client {clientId} sent {bytesSent} bytes to server.");

            state.SendDone.Set();
        }

        private static async Task Receive(State state)
        {
            state.Socket.BeginReceive(state.Buffer, 0, State.BufferSize, 0, ReceiveCallback, state);

            await Task.FromResult(state.ReceiveDone.WaitOne());
        }

        private static void ReceiveCallback(IAsyncResult ar)
        {
            var state = (State) ar.AsyncState;
            var clientSocket = state.Socket;
            
            // read data from the server
            var bytesRead = clientSocket.EndReceive(ar);

            state.Response.Append(Http.GetStringFromBytes(state.Buffer, bytesRead));
            var response = state.Response.ToString();
            
            if (!Http.IsResponseHeaderObtained(response))
            {
                // continue reading the header from the server
                clientSocket.BeginReceive(state.Buffer, 0, State.BufferSize, 0, ReceiveCallback, state);
            }
            else
            {
                var contentLength = Http.GetContentLength(response);
                var body = Http.GetResponseBody(response);
                
                if (body.Length < contentLength)
                {
                    // continue reading the body from the server
                    clientSocket.BeginReceive(state.Buffer, 0, State.BufferSize, 0, ReceiveCallback, state);
                }
                else
                {
                    state.ReceiveDone.Set();
                }
            }
        }
    }
}
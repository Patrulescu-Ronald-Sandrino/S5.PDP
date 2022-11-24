using System;
using System.Threading;

namespace homework4
{
    public static class Impl1
    {
        public static void Run(string[] hosts)
        {
            for (var i = 0; i < hosts.Length; i++)
            {
                StartClient(hosts[i], i);
                Thread.Sleep(2000); // w/o it no connection is made (maybe too fast)
            }
        }

        private static void StartClient(string host, int id)
        {
            var state = Http.GetState(host, id);
            
            state.Socket.BeginConnect(state.RemoteEndPoint, OnConnectCallback, state);
        }

        private static void OnConnectCallback(IAsyncResult ar)
        {
            // retrieve the connection info
            var state = (State) ar.AsyncState;
            var clientSocket = state.Socket;
            var clientId = state.ClientId;
            var hostname = state.Hostname;
            
            // complete the connection
            clientSocket.EndConnect(ar);
            Console.WriteLine($"Client {clientId} connected to {hostname} ({clientSocket.RemoteEndPoint})");
            
            var data = Http.GetRequestStringAsBytes(hostname, state.EndPointPath);
            clientSocket.BeginSend(data, 0, data.Length, 0, OnSendCallback, state);
        }

        private static void OnSendCallback(IAsyncResult ar)
        {
            var state = (State) ar.AsyncState;
            var clientSocket = state.Socket;
            var clientId = state.ClientId;
            
            // complete the sending of the data to the server
            var bytesSent = clientSocket.EndSend(ar);
            Console.WriteLine($"Client {clientId} sent {bytesSent} bytes to server.");
            
            // begin receiving the data from the server
            clientSocket.BeginReceive(state.Buffer, 0, State.BufferSize, 0, OnReceiveCallback, state);
        }

        private static void OnReceiveCallback(IAsyncResult ar)
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
                clientSocket.BeginReceive(state.Buffer, 0, State.BufferSize, 0, OnReceiveCallback, state);
            }
            else
            {
                var contentLength = Http.GetContentLength(response);
                var body = Http.GetResponseBody(response);
                
                if (body.Length < contentLength)
                {
                    // continue reading the body from the server
                    clientSocket.BeginReceive(state.Buffer, 0, State.BufferSize, 0, OnReceiveCallback, state);
                }
                else
                {
                    // all data received
                    Console.WriteLine($"Client {state.ClientId} received {body.Length} bytes from server.");
                    Console.WriteLine($"Client {state.ClientId} received response: {body}\n");
                    
                    state.ReleaseSocket();
                }
            }
        }
    }
}
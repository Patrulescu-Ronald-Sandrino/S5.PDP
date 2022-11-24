using System;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;

namespace homework4
{
    public static class Http
    {
        private const string LineEnd = "\r\n";

        public static State GetState(string host, int id)
        {
            // establish the remote endpoint of the server  
            var hostInfo = Dns.GetHostEntry(host.Split('/')[0]);
            var hostIpAddress = hostInfo.AddressList[0];
            var remoteEndPoint = new IPEndPoint(hostIpAddress, 80);

            // create the TCP/IP socket
            var client = new Socket(hostIpAddress.AddressFamily, SocketType.Stream, ProtocolType.Tcp);

            // create object to store the connection info
            var state = new State
            {
                ClientId = id,
                EndPointPath = host.Contains("/") ? host.Split('/')[1] : "/",
                RemoteEndPoint = remoteEndPoint,
                Hostname = host.Split('/')[0],
                Socket = client
            };
            
            return state;
        }

        public static byte[] GetRequestStringAsBytes(string hostname, string endpoint)
        {
            return Encoding.ASCII.GetBytes("GET " + endpoint + " HTTP/1.1" + LineEnd +
                                           "Host: " + hostname + LineEnd +
                                           "Content-Length: 0" + LineEnd + LineEnd +
                                           "Content-Type: text/html");
        }

        public static string GetStringFromBytes(byte[] buffer, int bytesRead)
        {
            return Encoding.ASCII.GetString(buffer, 0, bytesRead);
        }

        public static bool IsResponseHeaderObtained(string response)
        {
            return response.Contains(LineEnd + LineEnd);
        }

        public static string GetResponseBody(string response)
        {
            var responseParts = response.Split(new[] { LineEnd + LineEnd }, StringSplitOptions.RemoveEmptyEntries);

            return responseParts.Length > 1 ? responseParts[1] : string.Empty;
        }

        public static int GetContentLength(string response)
        {
            return (from line in response.Split(LineEnd.ToCharArray())
                select line.Split(':') into headerParts
                where headerParts[0].Trim() == "Content-Length"
                select int.Parse(headerParts[1].Trim())).FirstOrDefault();
        }
    }
}
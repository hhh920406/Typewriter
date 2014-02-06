using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Net;
using System.Net.Sockets;
using System.IO;
using System.Threading;

namespace ZComm
{
    class FileSender
    {
        private static int BufferSize = 4096;

        public UserInfo userInfo;
        public long fileSize;
        public string sendPath;
        public string receivePath;
        public int listenedPort;

        public FileSender(UserInfo userInfo)
        {
            this.userInfo = userInfo;
        }

        public void send()
        {
            sendFile();
        }

        public void receive()
        {
            TcpListener listener = new TcpListener(IPAddress.Loopback, 0);
            listener.Start();
            listenedPort = ((IPEndPoint)listener.LocalEndpoint).Port;
            listener.Stop();
            string send = "FIRE" + listenedPort + "\0" + userInfo.Port;
            IPEndPoint ip = new IPEndPoint(IPAddress.Parse(userInfo.IP), userInfo.Port);
            Socket server = new Socket(AddressFamily.InterNetwork, SocketType.Dgram, ProtocolType.Udp);
            byte[] bytes = Encoding.UTF8.GetBytes(send);
            server.SendTo(bytes, ip);
            server.Close();
            receiveFile();
        }

        private void sendFile()
        {
            TcpClient client = new TcpClient();
            client.Connect(IPAddress.Parse(userInfo.IP), userInfo.Port);
            NetworkStream stream = client.GetStream();
            sendFileStream(sendPath, stream);
            client.Close();
        }

        private void receiveFile()
        {
            TcpListener listener = new TcpListener(IPAddress.Any, listenedPort);
            listener.Start();
            TcpClient client = listener.AcceptTcpClient();
            NetworkStream stream = client.GetStream();
            receiveFileStream(receivePath, stream);
            listener.Stop();
        }

        private void sendFileStream(string filePath, NetworkStream stream)
        {
            FileStream fileStream = File.Open(filePath, FileMode.Open);
            int readLength;
            byte[] buffer = new byte[BufferSize];
            while ((readLength = fileStream.Read(buffer, 0, BufferSize)) > 0)
            {
                stream.Write(buffer, 0, readLength);
            }
            fileStream.Close();
        }

        private void receiveFileStream(string filePath, NetworkStream stream)
        {
            FileStream fileStream = File.Open(filePath, FileMode.OpenOrCreate);
            byte[] buffer = new byte[BufferSize];
            long remain = fileSize;
            while (remain > 0)
            {
                int nextLength = BufferSize;
                if (remain < BufferSize)
                {
                    nextLength = (int)remain;
                }
                int read = stream.Read(buffer, 0, BufferSize);
                fileStream.Write(buffer, 0, read);
                remain -= read;
                fileStream.Flush();
            }
            fileStream.Close();
        }
    }
}

using System;
using System.Collections;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading;

namespace ZComm
{
    class Scanner
    {
        class IPAddr
        {
            private int[] ip = new int[4];

            public IPAddr(IPAddr ipAddr)
            {
                for (int i = 0; i < 4; ++i)
                {
                    this.ip[i] = ipAddr.ip[i];
                }
            }

            private IPAddr(int[] ipAddr)
            {
                for (int i = 0; i < 4; ++i)
                {
                    this.ip[i] = ipAddr[i];
                }
            }

            public bool larger(IPAddr addr)
            {
                for (int i = 0; i < 4; ++i)
                {
                    if (this.ip[i] < addr.ip[i])
                    {
                        return false;
                    }
                }
                return true;
            }

            public void increase()
            {
                bool carry = true;
                for (int i = 3; i >= 0; --i)
                {
                    if (carry)
                    {
                        carry = false;
                    }
                    else
                    {
                        break;
                    }
                    ++this.ip[i];
                    if (this.ip[i] == 256)
                    {
                        this.ip[i] = 0;
                        carry = true;
                    }
                }
            }

            public override string ToString()
            {
                return ip[0] + "." + ip[1] + "." + ip[2] + "." + ip[3];
            }

            public static bool TryParse(string ipAddr, out IPAddr addr)
            {
                addr = null;
                if (Regex.IsMatch(ipAddr, @"^((2[0-4]\d|25[0-5]|[01]?\d\d?)\.){3}(2[0-4]\d|25[0-5]|[01]?\d\d?)$"))
                {
                    int[] ip = new int[4];
                    int index = 0;
                    for (int i = 0; i < ipAddr.Length; ++i)
                    {
                        if (ipAddr[i] == '.')
                        {
                            ++index;
                        }
                        else
                        {
                            ip[index] = ip[index] * 10 + ipAddr[i] - '0';
                        }
                    }
                    addr = new IPAddr(ip);
                    return true;
                }
                return false;
            }
        }

        private UdpListener listener;
        private IPAddr startIP;
        private IPAddr endIP;
        private int port;

        private InfoSender infoSender;
        private Thread scanThread;
        private bool isStopScan = false;

        public string StartIP
        {
            get { return startIP.ToString(); }
            set { IPAddr.TryParse(value, out startIP); }
        }

        public string EndIP
        {
            get { return endIP.ToString(); }
            set { IPAddr.TryParse(value, out endIP); }
        }

        public int Port
        {
            get { return port; }
            set { port = value; }
        }

        public Scanner(UdpListener listener)
        {
            this.listener = listener;
            infoSender = InfoSender.getInstance();
        }

        public void scan()
        {
            bool flag = false;
            if (this.scanThread == null)
            {
                flag = true;
            }
            else if (!this.scanThread.IsAlive)
            {
                flag = true;
            }
            if (flag)
            {
                this.scanThread = new Thread(new ThreadStart(this.scanAll));
                this.scanThread.Start();
            }
        }

        public void stopScan()
        {
            this.isStopScan = true;
        }

        public void scanAll()
        {
            if (startIP != null && endIP != null)
            {
                IPAddr ipAddr = new IPAddr(startIP);
                while (endIP.larger(ipAddr))
                {
                    scanUser(ipAddr);
                    ipAddr.increase();
                    if (isStopScan)
                    {
                        break;
                    }
                }
            }
        }

        private void scanUser(IPAddr ipAddr)
        {
            string send = "SCAN" + listener.localInfo.Name + "\0" + listener.localInfo.Port;
            IPEndPoint ip = new IPEndPoint(IPAddress.Parse(ipAddr.ToString()), this.port);
            Socket server = new Socket(AddressFamily.InterNetwork, SocketType.Dgram, ProtocolType.Udp);
            byte[] bytes = Encoding.UTF8.GetBytes(send);
            server.SendTo(bytes, ip);
            bytes = new byte[1024];
            IPEndPoint sender = new IPEndPoint(IPAddress.Any, 0);
            EndPoint remote = (EndPoint)sender;
            server.SetSocketOption(SocketOptionLevel.Socket, SocketOptionName.ReceiveTimeout, 1000);
            try
            {
                lock (infoSender)
                {
                    infoSender.sendInfo("扫描：" + ipAddr.ToString() + ":" + this.port);
                }
                int recv = server.ReceiveFrom(bytes, ref remote);
                if (recv >= 4)
                {
                    UserInfo info = new UserInfo();
                    string[] strs = Encoding.UTF8.GetString(bytes, 0, recv).Substring(4).Split(new char[1] { '\0' });
                    info.Name = strs[0];
                    info.IP = ipAddr.ToString();
                    info.Port = this.port;
                    lock (infoSender)
                    {
                        infoSender.sendInfo(" 连接成功。" + info.Name + "\n");
                    }
                    lock (listener)
                    {
                        listener.addUser(info);
                    }
                }
            }
            catch
            {
                lock (infoSender)
                {
                    infoSender.sendInfo(" 无连接。\n");
                }
            }
            server.Close();
        }
    }
}

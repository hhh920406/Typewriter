using System;
using System.Net;
using System.Net.Sockets;

namespace ZComm
{
    class UserInfo
    {
        private string name;
        private string ip;
        private int port;

        public string Name
        {
            get { return name; }
            set { name = value; }
        }

        public string IP
        {
            get { return ip; }
            set { ip = value; }
        }

        public int Port
        {
            get { return port; }
            set { port = value; }
        }

        public UserInfo()
        {
            this.name = "Anonymous";
            this.ip = "127.0.0.1";
            this.port = 19627;
        }

        /// <summary>
        /// 获取主机名和联网的IP。
        /// </summary>
        public void getLocalInfo()
        {
            this.name = Dns.GetHostName();
            IPHostEntry host = Dns.GetHostEntry(this.name);
            foreach (var ipAddress in host.AddressList)
            {
                if (ipAddress.AddressFamily == System.Net.Sockets.AddressFamily.InterNetwork)
                {
                    this.ip = ipAddress.ToString();
                    break;
                }
            }
        }
    }
}

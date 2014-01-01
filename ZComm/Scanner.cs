using System;
using System.Collections;
using System.Net;
using System.Net.Sockets;
using System.Text.RegularExpressions;

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
                    if (this.ip[i] > addr.ip[i])
                    {
                        return true;
                    }
                }
                return false;
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

            public string toString()
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

        private IPAddr startIP;
        private IPAddr endIP;
        private int port;

        public string StartIP
        {
            get { return startIP.toString(); }
            set { IPAddr.TryParse(value, out startIP); }
        }

        public string EndIP
        {
            get { return endIP.toString(); }
            set { IPAddr.TryParse(value, out endIP); }
        }

        public int Port
        {
            get { return port; }
            set { port = value; }
        }

        public Scanner()
        {
        }

        ArrayList scan()
        {
            ArrayList userList = new ArrayList();
            if (startIP != null && endIP != null)
            {
                IPAddr ipAddr = new IPAddr(startIP);
                while (endIP.larger(ipAddr))
                {
                    ipAddr.increase();
                }
            }
            return userList;
        }
    }
}

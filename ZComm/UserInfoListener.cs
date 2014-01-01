using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Net;
using System.Net.Sockets;
using System.Collections;
using System.Threading;

namespace ZComm
{
    class UserInfoListener
    {
        public ArrayList users = new ArrayList();
        public UserInfo localInfo;

        private Thread listenThread;
        private bool isListen = false;
        private InfoSender infoSender;

        public bool IsListen
        {
            get { return this.isListen; }
        }

        public UserInfoListener()
        {
            this.users = new ArrayList();
            this.localInfo = new UserInfo();
            this.localInfo.getLocalInfo();
            infoSender = InfoSender.getInstance();
        }

        public void startListen()
        {
            this.isListen = true;
            listenThread = new Thread(new ThreadStart(this.listen));
            listenThread.Start();
            infoSender.sendInfo("开始监听扫描：" + localInfo.IP + ":" + localInfo.Port + "\n");
        }

        public void stopListen()
        {
            this.isListen = false;
            listenThread.Join();
            infoSender.sendInfo("停止监听扫描\n");
        }

        private void listen()
        {
            IPEndPoint end = new IPEndPoint(IPAddress.Any, localInfo.Port);
            Socket server = new Socket(AddressFamily.InterNetwork, SocketType.Dgram, ProtocolType.Udp);
            server.SetSocketOption(SocketOptionLevel.Socket, SocketOptionName.ReceiveTimeout, 1000);
            server.Bind(end);
            IPEndPoint sender = new IPEndPoint(IPAddress.Any, 0);
            EndPoint remote = (EndPoint)sender;
            while (this.isListen)
            {
                byte[] bytes = new byte[1024];
                try
                {
                    int recv = server.ReceiveFrom(bytes, ref remote);
                    if (recv >= 4)
                    {
                        UserInfo info = new UserInfo();
                        info.Name = Encoding.ASCII.GetString(bytes, 0, recv).Substring(4);
                        string[] strs = remote.ToString().Split(new char[1] { ':' });
                        info.IP = strs[0];
                        info.Port = Int32.Parse(strs[1]);
                        this.addUser(info);
                    }
                    string send = "SCAN" + localInfo.Name;
                    bytes = Encoding.ASCII.GetBytes(send);
                    server.SendTo(bytes, bytes.Length, SocketFlags.None, remote);
                    lock (infoSender)
                    {
                        infoSender.sendInfo("监听到连接：" + remote.ToString() + "\n");
                    }
                }
                catch
                {
                }
            }
            server.Close();
        }

        public void addUser(UserInfo userInfo)
        {
            for (int i = 0; i < users.Count; ++i)
            {
                if (((UserInfo)users[i]).IP.ToString() == userInfo.IP.ToString())
                {
                    return;
                }
            }
            users.Add(userInfo);
        }
    }
}

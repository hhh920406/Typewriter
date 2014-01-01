using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Net;
using System.Net.Sockets;
using System.Collections;
using System.Threading;
using System.Windows.Forms;

namespace ZComm
{
    public class UdpListener
    {
        public ArrayList users = new ArrayList();
        public ArrayList chats = new ArrayList();
        public UserInfo localInfo;

        private Thread listenThread;
        private bool isListen = false;
        private InfoSender infoSender;

        private MainWindow mainWindow;

        public bool IsListen
        {
            get { return this.isListen; }
        }

        public UdpListener(MainWindow mainWindow)
        {
            this.users = new ArrayList();
            this.localInfo = new UserInfo();
            this.localInfo.getLocalInfo();
            infoSender = InfoSender.getInstance();
            this.mainWindow = mainWindow;
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
            if (this.isListen)
            {
                this.isListen = false;
                listenThread.Join();
                infoSender.sendInfo("停止监听扫描\n");
            }
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
                    string rstr = Encoding.UTF8.GetString(bytes, 0, recv);
                    UserInfo info = new UserInfo();
                    string[] strs = rstr.Substring(4).Split(new char[1]{'\0'});
                    info.Name = strs[0];
                    info.IP = remote.ToString().Split(new char[1] { ':' })[0];
                    info.Port = Int32.Parse(strs[1]);
                    if (rstr.Substring(0, 4).Equals("SCAN"))
                    {
                        this.addUser(info);
                        lock (infoSender)
                        {
                            infoSender.sendInfo("监听到连接：" + remote.ToString() + "\n");
                        }
                    }
                    else if (rstr.Substring(0, 4).Equals("MESS"))
                    {
                        this.addMessage(info);
                        lock (infoSender)
                        {
                            infoSender.sendInfo("监听到消息：" + remote.ToString() + " " + info.Name + "\n");
                        }
                    }
                    string send = "SCAN" + localInfo.Name + "\0" + localInfo.Port;
                    bytes = Encoding.UTF8.GetBytes(send);
                    server.SendTo(bytes, bytes.Length, SocketFlags.None, remote);
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
                if (((UserInfo)users[i]).IP == userInfo.IP && ((UserInfo)users[i]).Port == userInfo.Port)
                {
                    return;
                }
            }
            users.Add(userInfo);
            chats.Add(null);
            this.mainWindow.addUserControl(new UserInfoControl(this, userInfo));
        }

        public void addChat(UserInfo userInfo)
        {
            for (int i = 0; i < users.Count; ++i)
            {
                if (((UserInfo)users[i]).IP == userInfo.IP && ((UserInfo)users[i]).Port == userInfo.Port)
                {
                    bool flag = false;
                    if (chats[i] == null)
                    {
                        flag = true;
                    }
                    else if (((ChatDialog)chats[i]).IsDisposed)
                    {
                        flag = true;
                    }
                    if (flag)
                    {
                        chats[i] = new ChatDialog((UserInfo)users[i]);
                        ((ChatDialog)chats[i]).Show();
                    }
                    else
                    {
                        ((ChatDialog)chats[i]).BringToFront();
                    }
                    break;
                }
            }
        }

        public void addMessage(UserInfo userInfo)
        {
            for (int i = 0; i < users.Count; ++i)
            {
                if (((UserInfo)users[i]).IP == userInfo.IP && ((UserInfo)users[i]).Port == userInfo.Port)
                {
                    bool flag = true;
                    if (chats[i] == null)
                    {
                        flag = false;
                    }
                    else if (((ChatDialog)chats[i]).IsDisposed)
                    {
                        flag = false;
                    }
                    if (flag)
                    {
                        ((ChatDialog)chats[i]).appendReceive(userInfo.Name);
                    }
                    break;
                }
            }
        }
    }
}

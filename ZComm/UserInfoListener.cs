using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Net;
using System.Net.Sockets;
using System.Collections;

namespace ZComm
{
    class UserInfoListener
    {
        public ArrayList users = new ArrayList();
        public UserInfo localInfo;

        public UserInfoListener()
        {
            this.users = new ArrayList();
            this.localInfo = new UserInfo();
            this.localInfo.getLocalInfo();
        }

        public void startListen()
        {
            IPEndPoint end = new IPEndPoint(IPAddress.Any, localInfo.Port);
        }

        public void stopListen()
        {

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

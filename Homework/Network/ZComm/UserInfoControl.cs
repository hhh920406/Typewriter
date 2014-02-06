using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace ZComm
{
    public partial class UserInfoControl : UserControl
    {
        private UserInfo userInfo;
        private UdpListener listener;

        public UserInfoControl(UdpListener listener, UserInfo userInfo)
        {
            InitializeComponent();
            this.listener = listener;
            this.userInfo = userInfo;
            this.labelHostName.Text = userInfo.Name;
            this.labelAddress.Text = userInfo.IP + ":" + userInfo.Port;
        }

        private void buttonChat_Click(object sender, EventArgs e)
        {
            this.listener.addChat(userInfo);
        }
    }
}

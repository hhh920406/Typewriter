using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace ZComm
{
    public partial class ChatDialog : Form
    {
        private UserInfo userInfo;
        private InfoSender infoSender;
        private bool loadFinished = false;

        public bool LoadFinished
        {
            get { return this.loadFinished; }
        }

        public ChatDialog(UserInfo userInfo)
        {
            InitializeComponent();
            this.userInfo = userInfo;
            this.infoSender = InfoSender.getInstance();
        }

        private void ChatDialog_Load(object sender, EventArgs e)
        {
            this.Text = this.userInfo.Name;
        }

        private void buttonMessage_Click(object sender, EventArgs e)
        {
            string send = "MESS" + this.richTextBoxInput.Text + "\0" + userInfo.Port;
            IPEndPoint ip = new IPEndPoint(IPAddress.Parse(userInfo.IP), userInfo.Port);
            Socket server = new Socket(AddressFamily.InterNetwork, SocketType.Dgram, ProtocolType.Udp);
            byte[] bytes = Encoding.UTF8.GetBytes(send);
            server.SendTo(bytes, ip);
            this.richTextBoxShow.SelectionColor = Color.DarkGreen;
            this.richTextBoxShow.AppendText("本地 " + DateTime.Now.ToLongTimeString() + "\n\n");
            this.richTextBoxShow.SelectionColor = Color.Black;
            this.richTextBoxShow.AppendText(this.richTextBoxInput.Text + "\n\n");
            this.infoSender.sendInfo("发送信息到" + this.Text + "：" + this.richTextBoxInput.Text);
            this.richTextBoxInput.Text = "";
        }

        delegate void AppendReceiveCallback(string text);

        public void appendReceive(string text)
        {
            if (this.richTextBoxInput.InvokeRequired)
            {

                AppendReceiveCallback d = new AppendReceiveCallback(appendReceive);
                this.Invoke(d, new object[] { text });
            }
            else
            {
                this.richTextBoxShow.SelectionColor = Color.DarkBlue;
                this.richTextBoxShow.AppendText(this.Text + " " + DateTime.Now.ToLongTimeString() + "\n\n");
                this.richTextBoxShow.SelectionColor = Color.Black;
                this.richTextBoxShow.AppendText(text + "\n\n");
            }
        }

        private void ChatDialog_Shown(object sender, EventArgs e)
        {
            this.loadFinished = true;
        }
    }
}

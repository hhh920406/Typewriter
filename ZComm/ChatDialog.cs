using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
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
        private FileSender fileSender;

        public ChatDialog(UserInfo userInfo)
        {
            InitializeComponent();
            this.userInfo = userInfo;
            this.fileSender = new FileSender(userInfo);
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
            server.Close();
            this.richTextBoxShow.SelectionStart = this.richTextBoxShow.Text.Length;
            this.richTextBoxShow.SelectionColor = Color.DarkGreen;
            this.richTextBoxShow.AppendText("本地 " + DateTime.Now.ToLongTimeString() + "\n");
            this.richTextBoxShow.SelectionColor = Color.Black;
            this.richTextBoxShow.AppendText(this.richTextBoxInput.Text + "\n");
            this.richTextBoxShow.SelectionStart = this.richTextBoxShow.Text.Length;
            this.richTextBoxShow.ScrollToCaret();
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
                this.richTextBoxShow.SelectionStart = this.richTextBoxShow.Text.Length;
                this.richTextBoxShow.SelectionColor = Color.DarkBlue;
                this.richTextBoxShow.AppendText(this.Text + " " + DateTime.Now.ToLongTimeString() + "\n");
                this.richTextBoxShow.SelectionColor = Color.Black;
                this.richTextBoxShow.AppendText(text + "\n");
                this.richTextBoxShow.SelectionStart = this.richTextBoxShow.Text.Length;
                this.richTextBoxShow.ScrollToCaret();
            }
        }

        private void buttonFile_Click(object sender, EventArgs e)
        {
            OpenFileDialog fileDialog = new OpenFileDialog();
            fileDialog.Multiselect = false;
            if (fileDialog.ShowDialog() == DialogResult.OK)
            {
                string send = "FISE" + (new FileInfo(fileDialog.FileName).Name) + "/" + (new FileInfo(fileDialog.FileName).Length) + "\0" + userInfo.Port;
                IPEndPoint ip = new IPEndPoint(IPAddress.Parse(userInfo.IP), userInfo.Port);
                Socket server = new Socket(AddressFamily.InterNetwork, SocketType.Dgram, ProtocolType.Udp);
                byte[] bytes = Encoding.UTF8.GetBytes(send);
                server.SendTo(bytes, ip);
                server.Close();
                fileSender.sendPath = fileDialog.FileName;
            }
        }

        delegate void SendFileCallback(string fileName, long size);

        public void sendFileRequest(string fileName, long size)
        {
            if (this.InvokeRequired)
            {
                SendFileCallback d = new SendFileCallback(sendFileRequest);
                this.Invoke(d, new object[] { fileName, size });
            }
            else
            {
                if (MessageBox.Show(this.Text + " 想要发送文件 " + fileName + " (" + (size / 1024) + "KB)，是否接收？", "发送文件请求", MessageBoxButtons.YesNo) == DialogResult.Yes)
                {
                    SaveFileDialog fileDialog = new SaveFileDialog();
                    fileDialog.FileName = fileName;
                    if (fileDialog.ShowDialog() == DialogResult.OK)
                    {
                        fileSender.fileSize = size;
                        fileSender.receivePath = fileDialog.FileName;
                        fileSender.receive();
                    }
                }
            }
        }

        public void receiveFileRequest(int port)
        {
            fileSender.userInfo.Port = port;
            fileSender.send();
        }

        private void richTextBoxInput_KeyUp(object sender, KeyEventArgs e)
        {
            if (e.Modifiers == Keys.Control && e.KeyCode == Keys.Enter)
            {
                this.buttonMessage.PerformClick();
            }
        }
    }
}

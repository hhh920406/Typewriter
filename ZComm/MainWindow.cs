using System;
using System.Collections;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace ZComm
{
    public partial class MainWindow : Form
    {
        private Scanner scanner;
        private UserInfo localInfo;

        public MainWindow()
        {
            InitializeComponent();
            this.localInfo = new UserInfo();
            this.localInfo.getLocalInfo();
            this.textBoxLocalHostName.Text = localInfo.Name;
            this.textBoxLocalIP.Text = localInfo.IP;
            this.numericUpDownLocalPort.Value = localInfo.Port;
        }

        private void buttonScan_Click(object sender, EventArgs e)
        {
            if (scanner == null)
            {
                scanner = new Scanner();
            }
            scanner.StartIP = this.textBoxStartIP.Text;
            scanner.EndIP = this.textBoxEndIP.Text;
            scanner.Port = (int)this.numericUpDownRemotePort.Value;
            ArrayList userList = scanner.scan(localInfo);
        }

        private void buttonStart_Click(object sender, EventArgs e)
        {

        }
    }
}

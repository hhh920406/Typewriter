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
        private UserInfoListener listener;

        public MainWindow()
        {
            InitializeComponent();
            this.listener = new UserInfoListener();
            this.scanner = new Scanner(this.listener);
            this.textBoxLocalHostName.Text = listener.localInfo.Name;
            this.textBoxLocalIP.Text = listener.localInfo.IP;
            this.numericUpDownLocalPort.Value = listener.localInfo.Port;
        }

        private void buttonScan_Click(object sender, EventArgs e)
        {
            scanner.StartIP = this.textBoxStartIP.Text;
            scanner.EndIP = this.textBoxEndIP.Text;
            scanner.Port = (int)this.numericUpDownRemotePort.Value;
            scanner.scan();
        }

        private void buttonStart_Click(object sender, EventArgs e)
        {

        }
    }
}

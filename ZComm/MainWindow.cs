using System;
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
    }
}

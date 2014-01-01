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
    public partial class InfoDialog : Form
    {
        public InfoDialog()
        {
            InitializeComponent();
        }

        delegate void AppendTextCallback(string text); 

        public void appendText(string text)
        {
            if (this.richTextBoxInfo.InvokeRequired)
            {
                AppendTextCallback d = new AppendTextCallback(appendText);
                this.Invoke(d, new object[] { text });
            }
            else
            {
                this.richTextBoxInfo.AppendText(text);
            }
        }

    }
}

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ZComm
{
    class InfoSender
    {
        private static InfoSender instance = null;
        private static InfoDialog dialog = null;

        private InfoSender()
        {
            if (dialog == null)
            {
                dialog = new InfoDialog();
                dialog.Show();
            }
        }

        public static InfoSender getInstance()
        {
            if (null == instance)
            {
                instance = new InfoSender();
            }
            return instance;
        }

        public void sendInfo(string text)
        {
            if (!dialog.IsDisposed)
            {
                dialog.appendText(text);
            }
        }
    }
}

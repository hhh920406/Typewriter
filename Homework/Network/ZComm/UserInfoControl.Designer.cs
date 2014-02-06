namespace ZComm
{
    partial class UserInfoControl
    {
        /// <summary> 
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary> 
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region 组件设计器生成的代码

        /// <summary> 
        /// 设计器支持所需的方法 - 不要
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.label1 = new System.Windows.Forms.Label();
            this.labelHostName = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.labelAddress = new System.Windows.Forms.Label();
            this.buttonChat = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(15, 13);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(55, 13);
            this.label1.TabIndex = 0;
            this.label1.Text = "主机名：";
            // 
            // labelHostName
            // 
            this.labelHostName.AutoSize = true;
            this.labelHostName.Location = new System.Drawing.Point(77, 13);
            this.labelHostName.Name = "labelHostName";
            this.labelHostName.Size = new System.Drawing.Size(60, 13);
            this.labelHostName.TabIndex = 1;
            this.labelHostName.Text = "Host Name";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(15, 35);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(43, 13);
            this.label2.TabIndex = 2;
            this.label2.Text = "地址：";
            // 
            // labelAddress
            // 
            this.labelAddress.AutoSize = true;
            this.labelAddress.Location = new System.Drawing.Point(77, 35);
            this.labelAddress.Name = "labelAddress";
            this.labelAddress.Size = new System.Drawing.Size(55, 13);
            this.labelAddress.TabIndex = 3;
            this.labelAddress.Text = "IPAddress";
            // 
            // buttonChat
            // 
            this.buttonChat.Location = new System.Drawing.Point(16, 56);
            this.buttonChat.Name = "buttonChat";
            this.buttonChat.Size = new System.Drawing.Size(172, 28);
            this.buttonChat.TabIndex = 4;
            this.buttonChat.Text = "发起会话";
            this.buttonChat.UseVisualStyleBackColor = true;
            this.buttonChat.Click += new System.EventHandler(this.buttonChat_Click);
            // 
            // UserInfoControl
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.Snow;
            this.Controls.Add(this.buttonChat);
            this.Controls.Add(this.labelAddress);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.labelHostName);
            this.Controls.Add(this.label1);
            this.Name = "UserInfoControl";
            this.Size = new System.Drawing.Size(204, 96);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label labelHostName;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label labelAddress;
        private System.Windows.Forms.Button buttonChat;
    }
}

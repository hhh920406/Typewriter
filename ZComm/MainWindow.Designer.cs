namespace ZComm
{
    partial class MainWindow
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

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.textBoxLocalHostName = new System.Windows.Forms.TextBox();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.textBoxLocalIP = new System.Windows.Forms.TextBox();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.textBoxStartIP = new System.Windows.Forms.TextBox();
            this.textBoxEndIP = new System.Windows.Forms.TextBox();
            this.flowLayoutPanel1 = new System.Windows.Forms.FlowLayoutPanel();
            this.buttonScan = new System.Windows.Forms.Button();
            this.label6 = new System.Windows.Forms.Label();
            this.buttonStart = new System.Windows.Forms.Button();
            this.numericUpDownLocalPort = new System.Windows.Forms.NumericUpDown();
            this.numericUpDownRemotePort = new System.Windows.Forms.NumericUpDown();
            this.groupBox1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownLocalPort)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownRemotePort)).BeginInit();
            this.SuspendLayout();
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(6, 27);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(67, 13);
            this.label2.TabIndex = 1;
            this.label2.Text = "计算机名：";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(6, 53);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(53, 13);
            this.label3.TabIndex = 2;
            this.label3.Text = "IP地址：";
            // 
            // textBoxLocalHostName
            // 
            this.textBoxLocalHostName.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.textBoxLocalHostName.Location = new System.Drawing.Point(79, 24);
            this.textBoxLocalHostName.Name = "textBoxLocalHostName";
            this.textBoxLocalHostName.Size = new System.Drawing.Size(105, 20);
            this.textBoxLocalHostName.TabIndex = 3;
            this.textBoxLocalHostName.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // groupBox1
            // 
            this.groupBox1.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.groupBox1.Controls.Add(this.numericUpDownLocalPort);
            this.groupBox1.Controls.Add(this.buttonStart);
            this.groupBox1.Controls.Add(this.label6);
            this.groupBox1.Controls.Add(this.textBoxLocalIP);
            this.groupBox1.Controls.Add(this.label2);
            this.groupBox1.Controls.Add(this.label3);
            this.groupBox1.Controls.Add(this.textBoxLocalHostName);
            this.groupBox1.Location = new System.Drawing.Point(12, 12);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(190, 143);
            this.groupBox1.TabIndex = 4;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "本地信息";
            // 
            // textBoxLocalIP
            // 
            this.textBoxLocalIP.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.textBoxLocalIP.Location = new System.Drawing.Point(79, 50);
            this.textBoxLocalIP.Name = "textBoxLocalIP";
            this.textBoxLocalIP.ReadOnly = true;
            this.textBoxLocalIP.Size = new System.Drawing.Size(105, 20);
            this.textBoxLocalIP.TabIndex = 4;
            this.textBoxLocalIP.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // groupBox2
            // 
            this.groupBox2.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.groupBox2.Controls.Add(this.numericUpDownRemotePort);
            this.groupBox2.Controls.Add(this.buttonScan);
            this.groupBox2.Controls.Add(this.textBoxEndIP);
            this.groupBox2.Controls.Add(this.textBoxStartIP);
            this.groupBox2.Controls.Add(this.label5);
            this.groupBox2.Controls.Add(this.label4);
            this.groupBox2.Controls.Add(this.label1);
            this.groupBox2.Location = new System.Drawing.Point(12, 380);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(190, 141);
            this.groupBox2.TabIndex = 5;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "用户扫描";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(6, 26);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(53, 13);
            this.label1.TabIndex = 0;
            this.label1.Text = "起始IP：";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(6, 52);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(53, 13);
            this.label4.TabIndex = 1;
            this.label4.Text = "终止IP：";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(6, 78);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(43, 13);
            this.label5.TabIndex = 2;
            this.label5.Text = "端口：";
            // 
            // textBoxStartIP
            // 
            this.textBoxStartIP.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.textBoxStartIP.Location = new System.Drawing.Point(65, 23);
            this.textBoxStartIP.Name = "textBoxStartIP";
            this.textBoxStartIP.Size = new System.Drawing.Size(119, 20);
            this.textBoxStartIP.TabIndex = 3;
            this.textBoxStartIP.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // textBoxEndIP
            // 
            this.textBoxEndIP.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.textBoxEndIP.Location = new System.Drawing.Point(65, 49);
            this.textBoxEndIP.Name = "textBoxEndIP";
            this.textBoxEndIP.Size = new System.Drawing.Size(119, 20);
            this.textBoxEndIP.TabIndex = 4;
            this.textBoxEndIP.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // flowLayoutPanel1
            // 
            this.flowLayoutPanel1.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.flowLayoutPanel1.Location = new System.Drawing.Point(12, 161);
            this.flowLayoutPanel1.Name = "flowLayoutPanel1";
            this.flowLayoutPanel1.Size = new System.Drawing.Size(190, 213);
            this.flowLayoutPanel1.TabIndex = 6;
            // 
            // buttonScan
            // 
            this.buttonScan.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.buttonScan.Location = new System.Drawing.Point(9, 104);
            this.buttonScan.Name = "buttonScan";
            this.buttonScan.Size = new System.Drawing.Size(175, 31);
            this.buttonScan.TabIndex = 6;
            this.buttonScan.Text = "扫描";
            this.buttonScan.UseVisualStyleBackColor = true;
            this.buttonScan.Click += new System.EventHandler(this.buttonScan_Click);
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(6, 79);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(67, 13);
            this.label6.TabIndex = 5;
            this.label6.Text = "监听端口：";
            // 
            // buttonStart
            // 
            this.buttonStart.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.buttonStart.Location = new System.Drawing.Point(9, 102);
            this.buttonStart.Name = "buttonStart";
            this.buttonStart.Size = new System.Drawing.Size(175, 35);
            this.buttonStart.TabIndex = 7;
            this.buttonStart.Text = "开始";
            this.buttonStart.UseVisualStyleBackColor = true;
            this.buttonStart.Click += new System.EventHandler(this.buttonStart_Click);
            // 
            // numericUpDownLocalPort
            // 
            this.numericUpDownLocalPort.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.numericUpDownLocalPort.Location = new System.Drawing.Point(79, 77);
            this.numericUpDownLocalPort.Maximum = new decimal(new int[] {
            65535,
            0,
            0,
            0});
            this.numericUpDownLocalPort.Name = "numericUpDownLocalPort";
            this.numericUpDownLocalPort.Size = new System.Drawing.Size(105, 20);
            this.numericUpDownLocalPort.TabIndex = 8;
            this.numericUpDownLocalPort.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.numericUpDownLocalPort.Value = new decimal(new int[] {
            19627,
            0,
            0,
            0});
            // 
            // numericUpDownRemotePort
            // 
            this.numericUpDownRemotePort.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.numericUpDownRemotePort.Location = new System.Drawing.Point(65, 75);
            this.numericUpDownRemotePort.Maximum = new decimal(new int[] {
            65535,
            0,
            0,
            0});
            this.numericUpDownRemotePort.Name = "numericUpDownRemotePort";
            this.numericUpDownRemotePort.Size = new System.Drawing.Size(119, 20);
            this.numericUpDownRemotePort.TabIndex = 9;
            this.numericUpDownRemotePort.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.numericUpDownRemotePort.Value = new decimal(new int[] {
            19627,
            0,
            0,
            0});
            // 
            // MainWindow
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(214, 533);
            this.Controls.Add(this.flowLayoutPanel1);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.groupBox1);
            this.Name = "MainWindow";
            this.Text = "局域网通信";
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownLocalPort)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownRemotePort)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox textBoxLocalHostName;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.TextBox textBoxLocalIP;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.TextBox textBoxEndIP;
        private System.Windows.Forms.TextBox textBoxStartIP;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.FlowLayoutPanel flowLayoutPanel1;
        private System.Windows.Forms.Button buttonStart;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Button buttonScan;
        private System.Windows.Forms.NumericUpDown numericUpDownLocalPort;
        private System.Windows.Forms.NumericUpDown numericUpDownRemotePort;

    }
}


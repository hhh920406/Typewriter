namespace ZComm
{
    partial class ChatDialog
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(ChatDialog));
            this.richTextBoxShow = new System.Windows.Forms.RichTextBox();
            this.richTextBoxInput = new System.Windows.Forms.RichTextBox();
            this.buttonMessage = new System.Windows.Forms.Button();
            this.buttonFile = new System.Windows.Forms.Button();
            this.progressBarFile = new System.Windows.Forms.ProgressBar();
            this.SuspendLayout();
            // 
            // richTextBoxShow
            // 
            this.richTextBoxShow.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.richTextBoxShow.Location = new System.Drawing.Point(12, 12);
            this.richTextBoxShow.Name = "richTextBoxShow";
            this.richTextBoxShow.Size = new System.Drawing.Size(424, 270);
            this.richTextBoxShow.TabIndex = 0;
            this.richTextBoxShow.TabStop = false;
            this.richTextBoxShow.Text = "";
            // 
            // richTextBoxInput
            // 
            this.richTextBoxInput.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.richTextBoxInput.Location = new System.Drawing.Point(12, 317);
            this.richTextBoxInput.Name = "richTextBoxInput";
            this.richTextBoxInput.Size = new System.Drawing.Size(309, 76);
            this.richTextBoxInput.TabIndex = 1;
            this.richTextBoxInput.Text = "";
            // 
            // buttonMessage
            // 
            this.buttonMessage.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.buttonMessage.Location = new System.Drawing.Point(327, 316);
            this.buttonMessage.Name = "buttonMessage";
            this.buttonMessage.Size = new System.Drawing.Size(109, 35);
            this.buttonMessage.TabIndex = 2;
            this.buttonMessage.Text = "发送消息";
            this.buttonMessage.UseVisualStyleBackColor = true;
            this.buttonMessage.Click += new System.EventHandler(this.buttonMessage_Click);
            // 
            // buttonFile
            // 
            this.buttonFile.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.buttonFile.Location = new System.Drawing.Point(327, 357);
            this.buttonFile.Name = "buttonFile";
            this.buttonFile.Size = new System.Drawing.Size(109, 35);
            this.buttonFile.TabIndex = 3;
            this.buttonFile.Text = "传送文件";
            this.buttonFile.UseVisualStyleBackColor = true;
            // 
            // progressBarFile
            // 
            this.progressBarFile.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.progressBarFile.Location = new System.Drawing.Point(12, 288);
            this.progressBarFile.Name = "progressBarFile";
            this.progressBarFile.Size = new System.Drawing.Size(424, 23);
            this.progressBarFile.TabIndex = 4;
            // 
            // ChatDialog
            // 
            this.AcceptButton = this.buttonFile;
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(448, 404);
            this.Controls.Add(this.progressBarFile);
            this.Controls.Add(this.buttonFile);
            this.Controls.Add(this.buttonMessage);
            this.Controls.Add(this.richTextBoxInput);
            this.Controls.Add(this.richTextBoxShow);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "ChatDialog";
            this.Text = "ChatDialog";
            this.Load += new System.EventHandler(this.ChatDialog_Load);
            this.Shown += new System.EventHandler(this.ChatDialog_Shown);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.RichTextBox richTextBoxShow;
        private System.Windows.Forms.RichTextBox richTextBoxInput;
        private System.Windows.Forms.Button buttonMessage;
        private System.Windows.Forms.Button buttonFile;
        private System.Windows.Forms.ProgressBar progressBarFile;
    }
}
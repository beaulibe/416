namespace DemoSerieTrame
{
    partial class Form1
    {
        /// <summary>
        /// Variable nécessaire au concepteur.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Nettoyage des ressources utilisées.
        /// </summary>
        /// <param name="disposing">true si les ressources managées doivent être supprimées ; sinon, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Code généré par le Concepteur Windows Form

        /// <summary>
        /// Méthode requise pour la prise en charge du concepteur - ne modifiez pas
        /// le contenu de cette méthode avec l'éditeur de code.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.monSerialPort = new System.IO.Ports.SerialPort(this.components);
            this.ouvrirPort = new System.Windows.Forms.Button();
            this.statusStrip1 = new System.Windows.Forms.StatusStrip();
            this.info1StatusLabel = new System.Windows.Forms.ToolStripStatusLabel();
            this.info2StatusLabel = new System.Windows.Forms.ToolStripStatusLabel();
            this.nomPortComboBox = new System.Windows.Forms.ComboBox();
            this.btnTx = new System.Windows.Forms.Button();
            this.trackBarRouge = new System.Windows.Forms.TrackBar();
            this.label1 = new System.Windows.Forms.Label();
            this.txtValRouge = new System.Windows.Forms.TextBox();
            this.trackBarVert = new System.Windows.Forms.TrackBar();
            this.label2 = new System.Windows.Forms.Label();
            this.txtValVert = new System.Windows.Forms.TextBox();
            this.trackBarBleu = new System.Windows.Forms.TrackBar();
            this.label3 = new System.Windows.Forms.Label();
            this.txtValBleu = new System.Windows.Forms.TextBox();
            this.checkBoxAuto = new System.Windows.Forms.CheckBox();
            this.timerAuto = new System.Windows.Forms.Timer(this.components);
            this.rbPot = new System.Windows.Forms.RadioButton();
            this.rbChoixD = new System.Windows.Forms.RadioButton();
            this.rbChoixC = new System.Windows.Forms.RadioButton();
            this.rbChoixB = new System.Windows.Forms.RadioButton();
            this.rbChoixA = new System.Windows.Forms.RadioButton();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.rbSOH = new System.Windows.Forms.RadioButton();
            this.rbChkSum = new System.Windows.Forms.RadioButton();
            this.rbAucune = new System.Windows.Forms.RadioButton();
            this.statusStrip1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.trackBarRouge)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackBarVert)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackBarBleu)).BeginInit();
            this.groupBox1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.SuspendLayout();
            // 
            // ouvrirPort
            // 
            this.ouvrirPort.Location = new System.Drawing.Point(167, 21);
            this.ouvrirPort.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.ouvrirPort.Name = "ouvrirPort";
            this.ouvrirPort.Size = new System.Drawing.Size(84, 26);
            this.ouvrirPort.TabIndex = 0;
            this.ouvrirPort.Text = "OuvrirPort";
            this.ouvrirPort.UseVisualStyleBackColor = true;
            this.ouvrirPort.Click += new System.EventHandler(this.ouvrirPort_Click);
            // 
            // statusStrip1
            // 
            this.statusStrip1.ImageScalingSize = new System.Drawing.Size(20, 20);
            this.statusStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.info1StatusLabel,
            this.info2StatusLabel});
            this.statusStrip1.Location = new System.Drawing.Point(0, 378);
            this.statusStrip1.Name = "statusStrip1";
            this.statusStrip1.Padding = new System.Windows.Forms.Padding(2, 0, 13, 0);
            this.statusStrip1.Size = new System.Drawing.Size(774, 26);
            this.statusStrip1.TabIndex = 1;
            this.statusStrip1.Text = "statusStrip1";
            // 
            // info1StatusLabel
            // 
            this.info1StatusLabel.Name = "info1StatusLabel";
            this.info1StatusLabel.Size = new System.Drawing.Size(49, 20);
            this.info1StatusLabel.Text = "COM?";
            // 
            // info2StatusLabel
            // 
            this.info2StatusLabel.Name = "info2StatusLabel";
            this.info2StatusLabel.Size = new System.Drawing.Size(48, 20);
            this.info2StatusLabel.Text = "fermé";
            // 
            // nomPortComboBox
            // 
            this.nomPortComboBox.FormattingEnabled = true;
            this.nomPortComboBox.Location = new System.Drawing.Point(23, 22);
            this.nomPortComboBox.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.nomPortComboBox.Name = "nomPortComboBox";
            this.nomPortComboBox.Size = new System.Drawing.Size(121, 24);
            this.nomPortComboBox.TabIndex = 2;
            // 
            // btnTx
            // 
            this.btnTx.Enabled = false;
            this.btnTx.Location = new System.Drawing.Point(267, 21);
            this.btnTx.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.btnTx.Name = "btnTx";
            this.btnTx.Size = new System.Drawing.Size(89, 25);
            this.btnTx.TabIndex = 3;
            this.btnTx.Text = "Tx";
            this.btnTx.UseVisualStyleBackColor = true;
            this.btnTx.Click += new System.EventHandler(this.btnTx_Click);
            // 
            // trackBarRouge
            // 
            this.trackBarRouge.Location = new System.Drawing.Point(31, 79);
            this.trackBarRouge.Margin = new System.Windows.Forms.Padding(4);
            this.trackBarRouge.Maximum = 100;
            this.trackBarRouge.Name = "trackBarRouge";
            this.trackBarRouge.Orientation = System.Windows.Forms.Orientation.Vertical;
            this.trackBarRouge.Size = new System.Drawing.Size(56, 219);
            this.trackBarRouge.TabIndex = 5;
            this.trackBarRouge.Value = 50;
            this.trackBarRouge.ValueChanged += new System.EventHandler(this.trackBarRouge_ValueChanged);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(27, 60);
            this.label1.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(50, 17);
            this.label1.TabIndex = 6;
            this.label1.Text = "Rouge";
            // 
            // txtValRouge
            // 
            this.txtValRouge.Location = new System.Drawing.Point(31, 307);
            this.txtValRouge.Margin = new System.Windows.Forms.Padding(4);
            this.txtValRouge.Name = "txtValRouge";
            this.txtValRouge.ReadOnly = true;
            this.txtValRouge.Size = new System.Drawing.Size(48, 22);
            this.txtValRouge.TabIndex = 7;
            // 
            // trackBarVert
            // 
            this.trackBarVert.Location = new System.Drawing.Point(114, 79);
            this.trackBarVert.Margin = new System.Windows.Forms.Padding(4);
            this.trackBarVert.Maximum = 100;
            this.trackBarVert.Name = "trackBarVert";
            this.trackBarVert.Orientation = System.Windows.Forms.Orientation.Vertical;
            this.trackBarVert.Size = new System.Drawing.Size(56, 219);
            this.trackBarVert.TabIndex = 5;
            this.trackBarVert.Value = 50;
            this.trackBarVert.ValueChanged += new System.EventHandler(this.trackBarVert_ValueChanged);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(110, 60);
            this.label2.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(34, 17);
            this.label2.TabIndex = 6;
            this.label2.Text = "Vert";
            // 
            // txtValVert
            // 
            this.txtValVert.Location = new System.Drawing.Point(114, 307);
            this.txtValVert.Margin = new System.Windows.Forms.Padding(4);
            this.txtValVert.Name = "txtValVert";
            this.txtValVert.ReadOnly = true;
            this.txtValVert.Size = new System.Drawing.Size(48, 22);
            this.txtValVert.TabIndex = 7;
            // 
            // trackBarBleu
            // 
            this.trackBarBleu.Location = new System.Drawing.Point(190, 79);
            this.trackBarBleu.Margin = new System.Windows.Forms.Padding(4);
            this.trackBarBleu.Maximum = 100;
            this.trackBarBleu.Name = "trackBarBleu";
            this.trackBarBleu.Orientation = System.Windows.Forms.Orientation.Vertical;
            this.trackBarBleu.Size = new System.Drawing.Size(56, 219);
            this.trackBarBleu.TabIndex = 5;
            this.trackBarBleu.Value = 50;
            this.trackBarBleu.ValueChanged += new System.EventHandler(this.trackBarBleu_MouseCaptureChanged);
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(186, 60);
            this.label3.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(36, 17);
            this.label3.TabIndex = 6;
            this.label3.Text = "Bleu";
            // 
            // txtValBleu
            // 
            this.txtValBleu.Location = new System.Drawing.Point(190, 307);
            this.txtValBleu.Margin = new System.Windows.Forms.Padding(4);
            this.txtValBleu.Name = "txtValBleu";
            this.txtValBleu.ReadOnly = true;
            this.txtValBleu.Size = new System.Drawing.Size(48, 22);
            this.txtValBleu.TabIndex = 7;
            // 
            // checkBoxAuto
            // 
            this.checkBoxAuto.AutoSize = true;
            this.checkBoxAuto.Enabled = false;
            this.checkBoxAuto.Location = new System.Drawing.Point(368, 24);
            this.checkBoxAuto.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.checkBoxAuto.Name = "checkBoxAuto";
            this.checkBoxAuto.Size = new System.Drawing.Size(115, 21);
            this.checkBoxAuto.TabIndex = 8;
            this.checkBoxAuto.Text = "Auto (100ms)";
            this.checkBoxAuto.UseVisualStyleBackColor = true;
            this.checkBoxAuto.CheckedChanged += new System.EventHandler(this.checkBoxAuto_CheckedChanged);
            // 
            // timerAuto
            // 
            this.timerAuto.Tick += new System.EventHandler(this.timerAuto_Tick);
            // 
            // rbPot
            // 
            this.rbPot.AutoSize = true;
            this.rbPot.Location = new System.Drawing.Point(18, 35);
            this.rbPot.Name = "rbPot";
            this.rbPot.Size = new System.Drawing.Size(124, 21);
            this.rbPot.TabIndex = 9;
            this.rbPot.TabStop = true;
            this.rbPot.Text = "Potentiomètres";
            this.rbPot.UseVisualStyleBackColor = true;
            // 
            // rbChoixD
            // 
            this.rbChoixD.AutoSize = true;
            this.rbChoixD.Location = new System.Drawing.Point(18, 190);
            this.rbChoixD.Name = "rbChoixD";
            this.rbChoixD.Size = new System.Drawing.Size(77, 21);
            this.rbChoixD.TabIndex = 9;
            this.rbChoixD.TabStop = true;
            this.rbChoixD.Text = "Choix D";
            this.rbChoixD.UseVisualStyleBackColor = true;
            // 
            // rbChoixC
            // 
            this.rbChoixC.AutoSize = true;
            this.rbChoixC.Location = new System.Drawing.Point(17, 148);
            this.rbChoixC.Name = "rbChoixC";
            this.rbChoixC.Size = new System.Drawing.Size(76, 21);
            this.rbChoixC.TabIndex = 9;
            this.rbChoixC.TabStop = true;
            this.rbChoixC.Text = "Choix C";
            this.rbChoixC.UseVisualStyleBackColor = true;
            // 
            // rbChoixB
            // 
            this.rbChoixB.AutoSize = true;
            this.rbChoixB.Location = new System.Drawing.Point(17, 111);
            this.rbChoixB.Name = "rbChoixB";
            this.rbChoixB.Size = new System.Drawing.Size(76, 21);
            this.rbChoixB.TabIndex = 9;
            this.rbChoixB.TabStop = true;
            this.rbChoixB.Text = "Choix B";
            this.rbChoixB.UseVisualStyleBackColor = true;
            // 
            // rbChoixA
            // 
            this.rbChoixA.AutoSize = true;
            this.rbChoixA.Location = new System.Drawing.Point(18, 73);
            this.rbChoixA.Name = "rbChoixA";
            this.rbChoixA.Size = new System.Drawing.Size(76, 21);
            this.rbChoixA.TabIndex = 9;
            this.rbChoixA.TabStop = true;
            this.rbChoixA.Text = "Choix A";
            this.rbChoixA.UseVisualStyleBackColor = true;
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.rbChoixD);
            this.groupBox1.Controls.Add(this.rbPot);
            this.groupBox1.Controls.Add(this.rbChoixC);
            this.groupBox1.Controls.Add(this.rbChoixA);
            this.groupBox1.Controls.Add(this.rbChoixB);
            this.groupBox1.Location = new System.Drawing.Point(278, 78);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(205, 220);
            this.groupBox1.TabIndex = 11;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Effets :";
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.rbChkSum);
            this.groupBox2.Controls.Add(this.rbAucune);
            this.groupBox2.Controls.Add(this.rbSOH);
            this.groupBox2.Location = new System.Drawing.Point(520, 79);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(200, 156);
            this.groupBox2.TabIndex = 12;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Erreurs de trame :";
            // 
            // rbSOH
            // 
            this.rbSOH.AutoSize = true;
            this.rbSOH.Location = new System.Drawing.Point(19, 73);
            this.rbSOH.Name = "rbSOH";
            this.rbSOH.Size = new System.Drawing.Size(111, 21);
            this.rbSOH.TabIndex = 0;
            this.rbSOH.TabStop = true;
            this.rbSOH.Text = "SOH invalide";
            this.rbSOH.UseVisualStyleBackColor = true;
            // 
            // rbChkSum
            // 
            this.rbChkSum.AutoSize = true;
            this.rbChkSum.Location = new System.Drawing.Point(19, 111);
            this.rbChkSum.Name = "rbChkSum";
            this.rbChkSum.Size = new System.Drawing.Size(94, 21);
            this.rbChkSum.TabIndex = 0;
            this.rbChkSum.TabStop = true;
            this.rbChkSum.Text = "Checksum";
            this.rbChkSum.UseVisualStyleBackColor = true;
            // 
            // rbAucune
            // 
            this.rbAucune.AutoSize = true;
            this.rbAucune.Location = new System.Drawing.Point(18, 35);
            this.rbAucune.Name = "rbAucune";
            this.rbAucune.Size = new System.Drawing.Size(77, 21);
            this.rbAucune.TabIndex = 0;
            this.rbAucune.TabStop = true;
            this.rbAucune.Text = "Aucune";
            this.rbAucune.UseVisualStyleBackColor = true;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(774, 404);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.checkBoxAuto);
            this.Controls.Add(this.txtValBleu);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.txtValVert);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.txtValRouge);
            this.Controls.Add(this.trackBarBleu);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.trackBarVert);
            this.Controls.Add(this.trackBarRouge);
            this.Controls.Add(this.btnTx);
            this.Controls.Add(this.nomPortComboBox);
            this.Controls.Add(this.statusStrip1);
            this.Controls.Add(this.ouvrirPort);
            this.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.Name = "Form1";
            this.Text = "Simulateur Laboratoire anneau de DEL cours 416";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Form1_FormClosing);
            this.Load += new System.EventHandler(this.Form1_Load);
            this.statusStrip1.ResumeLayout(false);
            this.statusStrip1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.trackBarRouge)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackBarVert)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackBarBleu)).EndInit();
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.IO.Ports.SerialPort monSerialPort;
        private System.Windows.Forms.Button ouvrirPort;
        private System.Windows.Forms.StatusStrip statusStrip1;
        private System.Windows.Forms.ToolStripStatusLabel info1StatusLabel;
        private System.Windows.Forms.ToolStripStatusLabel info2StatusLabel;
        private System.Windows.Forms.ComboBox nomPortComboBox;
        private System.Windows.Forms.Button btnTx;
        private System.Windows.Forms.TrackBar trackBarRouge;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox txtValRouge;
        private System.Windows.Forms.TrackBar trackBarVert;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox txtValVert;
        private System.Windows.Forms.TrackBar trackBarBleu;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox txtValBleu;
        private System.Windows.Forms.CheckBox checkBoxAuto;
        private System.Windows.Forms.Timer timerAuto;
        private System.Windows.Forms.RadioButton rbPot;
        private System.Windows.Forms.RadioButton rbChoixB;
        private System.Windows.Forms.RadioButton rbChoixA;
        private System.Windows.Forms.RadioButton rbChoixD;
        private System.Windows.Forms.RadioButton rbChoixC;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.RadioButton rbChkSum;
        private System.Windows.Forms.RadioButton rbSOH;
        private System.Windows.Forms.RadioButton rbAucune;
    }
}


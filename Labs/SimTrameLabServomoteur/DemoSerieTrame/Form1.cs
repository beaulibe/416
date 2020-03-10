using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO.Ports;



namespace DemoSerieTrame
{



    public partial class Form1 : Form
    {
        const int SOH = 1;

        const int LIMITE_BUFFER = 6;
        byte[] trameTx = new byte[LIMITE_BUFFER];

        public Form1()
        {
            string[] portsDisponibles;

            InitializeComponent();

            portsDisponibles = SerialPort.GetPortNames();
            nomPortComboBox.Items.AddRange(portsDisponibles);
            if (nomPortComboBox.Items.Count > 0)
                nomPortComboBox.SelectedIndex = 0;
            rbPot.Checked = true;
            rbAucune.Checked = true;

        }


    
        private void ouvrirPort_Click(object sender, EventArgs e)
        {


            try
            {

                monSerialPort.PortName = nomPortComboBox.Text;
                info1StatusLabel.Text = monSerialPort.PortName + ":" + monSerialPort.BaudRate + "," + monSerialPort.Parity + "," + monSerialPort.DataBits + "," + monSerialPort.StopBits;
                


                monSerialPort.Open();

                

                info2StatusLabel.ForeColor = System.Drawing.Color.Green;
                info2StatusLabel.Text = "Ouvert";
                btnTx.Enabled = true;
                checkBoxAuto.Enabled = true;
                nomPortComboBox.Enabled = false;
                ouvrirPort.Enabled = false;

            }
            catch
            {

                info2StatusLabel.ForeColor = System.Drawing.Color.Red;
                info2StatusLabel.Text = "Fermé";

            }
        }


        private void btnTx_Click(object sender, EventArgs e)
        {
            int somme=0;
            byte effet = (byte)'P'; //effet pot par défaut
            if (rbChoixA.Checked) effet = (byte)'A';
            else if (rbChoixB.Checked) effet = (byte)'B';
            else if (rbChoixC.Checked) effet = (byte)'C';
            else if (rbChoixD.Checked) effet = (byte)'D';


            if (monSerialPort.IsOpen)
            {
                trameTx[0] = SOH;
                trameTx[1] = effet; //choix de l'animation à mettre
                trameTx[2] = Convert.ToByte(txtValRouge.Text);
                trameTx[3] = Convert.ToByte(txtValVert.Text);
                trameTx[4] = Convert.ToByte(txtValBleu.Text);
                for (int i = 1; i < 5; i++)
                    somme += trameTx[i];
                trameTx[5] = (byte)(somme & 0xFF);
                ajouteErreurTrame();
                monSerialPort.Write(trameTx, 0, LIMITE_BUFFER);
            }
            else
            {
                timerAuto.Enabled = false;
                MessageBox.Show("Ouvrir le port de communication");
                btnTx.Enabled = false;
                checkBoxAuto.Enabled = false;
                checkBoxAuto.Checked = false;

                //on doit garder les lignes ci-dessous, car port peut avoir été débranché
                ouvrirPort.Enabled = true;
                info2StatusLabel.ForeColor = System.Drawing.Color.Red;
                info2StatusLabel.Text = "Fermé";



            }
        }

        private void ajouteErreurTrame()
        {
            if (rbSOH.Checked)
                trameTx[0] = SOH + 1;

            else if (rbChkSum.Checked)
                trameTx[5] = (byte)(trameTx[5] + 1);

        }


        private void Form1_Load(object sender, EventArgs e)
        {
            txtValRouge.Text = trackBarRouge.Value.ToString();
            txtValVert.Text = trackBarVert.Value.ToString();
            txtValBleu.Text = trackBarBleu.Value.ToString();
        }

        private void trackBarRouge_ValueChanged(object sender, EventArgs e)
        {
            txtValRouge.Text = trackBarRouge.Value.ToString();
        }

        private void trackBarVert_ValueChanged(object sender, EventArgs e)
        {
            txtValVert.Text = trackBarVert.Value.ToString();
        }

        private void trackBarBleu_MouseCaptureChanged(object sender, EventArgs e)
        {
            txtValBleu.Text = trackBarBleu.Value.ToString();
        }

        private void checkBoxAuto_CheckedChanged(object sender, EventArgs e)
        {
            if (checkBoxAuto.Checked)
                timerAuto.Enabled = true;
            else
                timerAuto.Enabled = false;

        }

        private void timerAuto_Tick(object sender, EventArgs e)
        {
            btnTx_Click(sender, e);
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (monSerialPort.IsOpen)
            {
                monSerialPort.Close();
            }

        }
    }
}

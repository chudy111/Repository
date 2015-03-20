using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Threading;
using System.Windows.Forms.DataVisualization.Charting;
namespace AlgorytmGenetyczny
{
    public partial class MainWindow : Form
    {
        double x, y;
        Thread m_oThread;
        private double min;
        public MainWindow()
        {
            InitializeComponent();
            chart1.Series.Add("Pawel");
            chart1.Series["Pawel"].ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.FastLine;
            chart1.Series["Pawel"].IsVisibleInLegend = false;
            x = 0;
            y = 0;
        }

        public void updateGraph(int a_y,int[] o)
        {
            y = a_y;
            if (chart1.Series["Pawel"].Points.Count == 0 || min > y)
            {
                min = y;
                this.Invoke((MethodInvoker)delegate()
                {
                    String text = "";
                    for (int i = 0; i < 10; i++)
                    {
                        text += o[i] + " ";
                    }
                    textBox2.Text = text;
                    textBox1.Text = min.ToString();
                });
            }
            dodaj();
        }
        public void updateGraph(int a_y)
        {
            y = a_y;
            if (chart1.Series["Pawel"].Points.Count == 0 || min > y)
            {
                min = y;
                this.Invoke((MethodInvoker)delegate()
                {
                    textBox1.Text = min.ToString();
                });
            }
            dodaj();
        }
        private void button1_Click(object sender, EventArgs e)
        {
            m_oThread.Abort();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            //generator gen = new generator();
            //gen.createNew();
            //gen.loadFromFile();
            x = 0;
            foreach (var series in chart1.Series)
            {
                series.Points.Clear();
            }
            genetyczny gen = new genetyczny((int)numericUpDown3.Value, (int)numericUpDown2.Value
                , (int)numericUpDown1.Value, this);
            m_oThread = new Thread(gen.solve);
            m_oThread.Start();
        }

        void dodaj()
        {
                this.Invoke((MethodInvoker)delegate()
                {
                    chart1.Series["Pawel"].Points.AddXY(x++, y);    
                });
                Thread.Sleep(50);
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (null != m_oThread && m_oThread.IsAlive)
                m_oThread.Abort();
        }
    }
}

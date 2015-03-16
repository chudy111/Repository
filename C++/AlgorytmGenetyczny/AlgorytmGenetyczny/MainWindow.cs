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
        public MainWindow()
        {
            InitializeComponent();
            chart1.Series.Add("Pawel");
            chart1.Series["Pawel"].ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.FastLine;
            chart1.Series["Pawel"].IsVisibleInLegend = false;
            x = 0;
            y = 0;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            m_oThread = new Thread(SampleFunction);
            m_oThread.Start();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            //generator gen = new generator();
            //gen.createNew();
            //gen.loadFromFile();

            genetyczny gen = new genetyczny(50);
            gen.solve();
        }

        void SampleFunction()
        {
            int x = 0;
            Random rm = new Random();
            int y = 0;
            // Gets executed on a seperate thread and 
            // doesn't block the UI while sleeping
            for (int i = 0; i < 500; i++)
            {
                if (5 < rm.Next(1, 11))
                {
                    x++;
                    y++;
                }
                else
                {
                    x++;
                    y--;
                }
                this.Invoke((MethodInvoker)delegate()
                {
                    chart1.Series["Pawel"].Points.AddXY(x, y);
                    
                });
                Thread.Sleep(100);
               
            }
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (null != m_oThread && m_oThread.IsAlive)
                m_oThread.Abort();
        }
    }
}

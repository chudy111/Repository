using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
namespace AlgorytmGenetyczny
{
    class generator
    {
        private const int x = 10;
        private int[,] m_iMatrix;
        public generator() 
        {
            m_iMatrix = new int[x, x];
        }
        public int getX()
        {
            return x;
        }
        public void createNew()
        {
            Random rand = new Random();
            for (int i=0;i<x;i++)
            {
                for (int j=0;j<x;j++)
                {
                    m_iMatrix[i,j] = 0;
                }
            }
            for (int i = 0; i < x; i++)
            {
                for (int j = 0; j < x; j++)
                {
                    if (i == j)
                        m_iMatrix[i, j] = 0;
                    else if (m_iMatrix[j, i] != 0 && 0 == m_iMatrix[i, j])
                        m_iMatrix[i, j] = m_iMatrix[j, i];
                    else
                        m_iMatrix[i, j] = rand.Next(10, 80);
                }
            }
            StreamWriter writer = new StreamWriter("miasta.txt");
            for (int i = 0; i < x; i++)
            {
                for (int j = 0; j < x; j++)
                {
                    writer.Write(m_iMatrix[i, j] + " ");
                }
                writer.Write("\r\n");
            }
            writer.Close();
        }

        public int[,] loadFromFile()
        {
            StreamReader reader = new StreamReader("miasta.txt");
            string[] line;
            for (int i = 0; i < x; i++)
            {
                line = reader.ReadLine().Split(' ');
                for (int j = 0; j < x; j++)
                {
                    m_iMatrix[i, j] = int.Parse(line[j]);
                }
            }
            return m_iMatrix;
        }
    }
}

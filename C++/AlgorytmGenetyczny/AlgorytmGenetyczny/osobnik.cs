using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
namespace AlgorytmGenetyczny
{
    class osobnik
    {
        private int[] sciezka;
        private int x;
        private int[,] miasta;
        private int wartoscPrzystosowania;
        public osobnik(int a_x, int[,] a_miasta)
        {
            wartoscPrzystosowania = 0;
            sciezka = new int[a_x];
            x = a_x;
            miasta = a_miasta;
            for (int i=0;i<x;i++)
            {
                sciezka[i] = 0;
            }
        }
        public void losuj()
        {
            Random rand = new Random();
            int temp;
            List<int> index = new List<int>();
            for (int i=1;i<=x;i++)
            {
                index.Add(i);
            }
            int left = x;
            for (int i=0;i<x;i++)
            {
                temp = rand.Next(1,left+1);
                sciezka[i] = index.ElementAt(temp-1);
                index.RemoveAt(temp-1);
                left--;
            }
            for (int i=0;i<x;i++)
            {
                Console.Write(sciezka[i] + " ");
            }
            Console.Write("\n");
        }
        public void obliczWartoscP()
        {
            wartoscPrzystosowania = 0;
            for (int i=0;i<sciezka.Length-1;i++)
            {
                wartoscPrzystosowania += miasta[sciezka[i]-1, sciezka[i + 1]-1];
            }
        }
        public void setWartoscP(int a_wartosc)
        {
            wartoscPrzystosowania = a_wartosc;
        }
        public int getWartoscP()
        {
            return wartoscPrzystosowania;
        }
    }
}

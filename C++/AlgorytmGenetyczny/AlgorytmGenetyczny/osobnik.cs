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
        private double wartoscPrzystosowania;
        private double wartoscPoOdjeciuJedynki;
        private double wartoscDouble;
        private double poDodaniu;
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
        public void setPoDodaniu(double a_war)
        {
            poDodaniu = a_war;
        }
        public double getPoDodaniu()
        {
            return poDodaniu;
        }
        public void setWartoscDouble(double a_war)
        {
            wartoscDouble = a_war;
        }
        public double getWartoscDouble()
        {
            return wartoscDouble;
        }
        public void setWartoscPoOdjeciuJedynki(double a_war)
        {
            wartoscPoOdjeciuJedynki = a_war;
        }
        public double getWartoscPoOdjeciuJedynki()
        {
            return wartoscPoOdjeciuJedynki;
        }
        public void losuj(Random rand)
        {
            //Random rand = new Random();
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
           
        }
        public void obliczWartoscP()
        {
            wartoscPrzystosowania = 0;
            for (int i=0;i<sciezka.Length-1;i++)
            {
                wartoscPrzystosowania += miasta[sciezka[i]-1, sciezka[i + 1]-1];
            }
        }
        public void setWartoscP(double a_wartosc)
        {
            wartoscPrzystosowania = a_wartosc;
        }
        public double getWartoscP()
        {
            return wartoscPrzystosowania;
        }
        public int[] getSciezka()
        {
            return sciezka;
        }
        public void setSciezka(int[] a_sciezka)
        {
            sciezka = a_sciezka;
        }
    }
}

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AlgorytmGenetyczny
{
    class genetyczny
    {
        private int[,] miasta;
        private osobnik[] populacja;
        private double sumaWartosci;
        public genetyczny(int a_populacja)
        {
            generator gen = new generator();
            miasta = gen.loadFromFile();
            populacja = new osobnik[a_populacja];
            for (int i=0;i<a_populacja;i++)
            {
                populacja[i] = new osobnik(gen.getX(), miasta);
            }
        }

        public void solve()
        {
            obliczWartoscP();
            selekcja();
            krzyzowanie();
        }

        private void obliczWartoscP()
        {
            sumaWartosci = 0;
            Random rand = new Random();
            for(int i=0;i<populacja.Length;i++)
            {
                populacja[i].losuj(rand);
                populacja[i].obliczWartoscP();
                sumaWartosci += populacja[i].getWartoscP();
            }
        }
        private double sumaWartosciMianownik()
        {
            double wynik = 0;
            for (int i = 0; i < populacja.Length;i++)
            {
                populacja[i].setWartoscPoOdjeciuJedynki(sumaWartosci - populacja[i].getWartoscP());
                wynik += sumaWartosci - populacja[i].getWartoscP();
            }
            return wynik;
        }
        private void selekcja()
        {
            Random rand = new Random();
            osobnik[] temp = new osobnik[populacja.Length];
            double suma = sumaWartosciMianownik();
            double[] wartosci = new double[populacja.Length];
            populacja[0].setWartoscDouble(populacja[0].getWartoscPoOdjeciuJedynki() / suma);
            populacja[0].setPoDodaniu(populacja[0].getWartoscPoOdjeciuJedynki());
            
            //Dodaje wartosc poprzenich osobnikow
            for (int i = 1; i < populacja.Length;i++ )
            {
                populacja[i].setPoDodaniu(populacja[i].getWartoscPoOdjeciuJedynki()
                    + populacja[i - 1].getPoDodaniu());
                populacja[i].setWartoscDouble((populacja[i].getWartoscPoOdjeciuJedynki()
                    + populacja[i - 1].getPoDodaniu())/suma);
            }
            for (int i = 0; i < populacja.Length; i++)
            {
                wartosci[i] = 0;
            }
            
            for (int i=0;i<populacja.Length;i++)
            {
                wartosci[i] = rand.Next(1,(int)suma+1)/suma;
                for (int j=0;j<populacja.Length;j++)
                {
                    if (wartosci[i] == wartosci[j] && i != j)
                    {
                        i--;
                        break;
                    }
                }
            }

            for (int j = 0; j < wartosci.Length; j++)
            {
                for (int i=0;i<populacja.Length;i++)
                {
                    if (0 == j && ((double)populacja[i].getWartoscDouble() / sumaWartosci) < wartosci[j])
                    {
                        temp[j] = populacja[i];
                        break;
                    }
                    else if (j>0 && ((double)populacja[i].getWartoscDouble()) > wartosci[j-1] &&
                        ((double)populacja[i].getWartoscDouble() / sumaWartosci) < wartosci[j])
                    {
                        temp[j] = populacja[i];
                        break;
                    }
                }
                if (null == temp[j])
                {
                    temp[j] = populacja[populacja.Length - 1];
                }
            }
            populacja = temp;
        }

        private void krzyzowanie()
        {
            Random rand = new Random();
            osobnik[,] pary = new osobnik[populacja.Length/2,2];
            int temp;
            List<int> index = new List<int>();
            for (int i = 0; i < populacja.Length; i++)
            {
                index.Add(i);
            }
            int left = populacja.Length;
            for (int i = 0; i < populacja.Length / 2; i++)
            {
                temp = rand.Next(1, left + 1);
                pary[i,0] = populacja[index.ElementAt(temp)];
                left--;
                temp = rand.Next(1, left + 1);
                pary[i, 1] = populacja[index.ElementAt(temp)];
                index.RemoveAt(temp - 1);
                left--;
            }
            int dzielnik = rand.Next(1, miasta.GetLength(1));
            for (int i=0;i<populacja.Length / 2; i++)
            {
                int[] sciezka1 = pary[i, 0].getSciezka();
                int[] sciezka2 = pary[i, 1].getSciezka();

            }
        }
    }
}

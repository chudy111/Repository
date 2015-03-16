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
        private int sumaWartosci;
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
        }

        private void obliczWartoscP()
        {
            sumaWartosci = 0;
            for(int i=0;i<populacja.Length;i++)
            {
                populacja[i].losuj();
                populacja[i].obliczWartoscP();
                sumaWartosci += populacja[i].getWartoscP();
            }
        }

        private void selekcja()
        {
            Random rand = new Random();
            osobnik[] temp = new osobnik[populacja.Length];
            
            int[] wartosci = new int[populacja.Length];
            for (int i = 1; i < populacja.Length;i++ )
            {
                populacja[i].setWartoscP(populacja[i].getWartoscP() + populacja[i - 1].getWartoscP());
            }
            for (int i = 0; i < populacja.Length; i++)
            {
                wartosci[i] = 0;
            }
            for (int i=0;i<populacja.Length;i++)
            {
                wartosci[i] = rand.Next(1, sumaWartosci+1);
                for (int j=0;j<populacja.Length;j++)
                {
                    if (wartosci[i] == wartosci[j] && i != j)
                    {
                        i--;
                        break;
                    }
                }
            }
            bool bPut;
            for (int k=0;k<temp.Length;k++)
            {
                bPut = false;
                for (int i=0;i<populacja.Length;i++)
                {
                    for (int j=0;j<wartosci.Length;j++)
                    {
                        if (populacja[i].getWartoscP() < wartosci[j])
                        {
                            temp[k] = populacja[i];
                            bPut = true;
                            break;
                        }
                    }
                    if (bPut)
                    {
                        break;
                    }
                }
            }
            populacja = temp;
        }
    }
}

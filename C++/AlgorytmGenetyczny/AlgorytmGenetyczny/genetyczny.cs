using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AlgorytmGenetyczny
{
    class genetyczny
    {
        private int iteracje;
        MainWindow window;
        private int mutacjaSzansa;
        Random rand;
        private int[,] miasta;
        private osobnik[] populacja;
        private double sumaWartosci;
        public genetyczny(int a_populacja, int a_mutacja,int a_iteracje, MainWindow a_window)
        {

            iteracje = a_iteracje;
            window = a_window;
            mutacjaSzansa = a_mutacja;
            rand = new Random();
            generator gen = new generator();
            miasta = gen.loadFromFile();
            populacja = new osobnik[a_populacja];
            for (int i=0;i<a_populacja;i++)
            {
                populacja[i] = new osobnik(gen.getX(), miasta);
                populacja[i].losuj(rand);
            }
        }

        public void solve()
        {
            for (int i = 0; i < iteracje; i++)
            {
                obliczWartoscP();
                getMinP();
                selekcja();
                krzyzowanie();
                //mutacja();
            }
        }

        private void obliczWartoscP()
        {
            sumaWartosci = 0;
            for(int i=0;i<populacja.Length;i++)
            {
                populacja[i].obliczWartoscP();
                sumaWartosci += populacja[i].getWartoscP();
            }
        }

        private void getMinP()
        {
            double min = populacja[0].getWartoscP();
            osobnik minn=null;
            for (int i=0;i<populacja.Length;i++)
            {
                if (min > populacja[i].getWartoscP())
                {
                    min = populacja[i].getWartoscP();
                    minn = populacja[i];
                }
            }
            if (null != minn)
                window.updateGraph((int)min, minn.getSciezka());
            else
                window.updateGraph((int)min);
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
                temp = rand.Next(0, left);
                pary[i,0] = populacja[index.ElementAt(temp)];
                index.RemoveAt(temp);
                left--;
                temp = rand.Next(0, left);
                pary[i, 1] = populacja[index.ElementAt(temp)];
                index.RemoveAt(temp);
                left--;
            }
            
            for (int i=0;i<pary.GetLength(1); i++)
            {                
                int[] sciezka1 = pary[i, 0].getSciezka();
                int[] sciezka2 = pary[i, 1].getSciezka();
                pary[i,0].setSciezka(krzyzujSciezke(sciezka1,sciezka2));
                pary[i,1].setSciezka(krzyzujSciezke(sciezka2,sciezka1));
            }
            int k = 0;
            for (int i=1;i<populacja.Length;i=i+2)
            {
                populacja[i - 1] = pary[k, 0];
                populacja[i] = pary[k, 1];
                k++;
            }
        }

        private int[] krzyzujSciezke(int[] sciezka1, int[] sciezka2)
        {
            int k;
            int dzielnik = rand.Next(1, miasta.GetLength(1)-1);
            bool powtorka = false;
            for (int j = dzielnik+1;j<sciezka1.Length;j++)
            {
                for (k=0;k<dzielnik+1;k++)
                {
                    if (sciezka1[j] == sciezka2[k])
                    {
                        powtorka = true;
                        break;
                    }
                }
                if (powtorka)
                {
                    break;
                }
            }
            if (powtorka)
            {
                for (int j = 0; j < sciezka2.Length; j++)
                {
                    powtorka = false;
                    for (k = 0; k < dzielnik + 1; k++)
                    {
                        if (sciezka1[k] == sciezka2[j])
                        {
                            powtorka = true;
                            break;
                        }
                    }
                    if (!powtorka)
                    {
                        sciezka1[k] = sciezka2[j];
                    }
                }
            }
            else
            {
                for (int j = dzielnik + 1; j < sciezka2.Length;j++ )
                {
                    sciezka1[j] = sciezka2[j];
                }
            }
            for (int i = 0; i < sciezka2.Length; i++)
            {
                for (int j = 0; j < sciezka2.Length; j++)
                {
                    if (i==j)
                        continue;
                    if (sciezka1[i] == sciezka1[j])
                        Console.Write("da");
                }
            }
            return sciezka1;
        }

        public void mutacja()
        {
            for (int i=0;i<populacja.Length;i++)
            {
                if (mutacjaSzansa >= rand.Next(0, 101))
                {
                    int temp1 = rand.Next(0, populacja[i].getSciezka().Length);
                    int temp2;
                    do
                    {
                        temp2 = rand.Next(0, populacja[i].getSciezka().Length);
                    } while (temp1 == temp2);
                    int num1 = populacja[i].getSciezka()[temp1];
                    int num2 = populacja[i].getSciezka()[temp2];
                    populacja[i].setSciezka(temp1, num2);
                    populacja[i].setSciezka(temp2, num1);
                }
            }
        }
    }
 
}

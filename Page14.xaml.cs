using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Runtime.InteropServices;
using System.Threading;
using System.Windows.Threading;

namespace WpfApp1
{
    /// <summary>
    /// Interaction logic for Page1.xaml
    /// </summary>
    public partial class Page14 : Window
    {
        [DllImport("SSCLibrary", SetLastError = true)]
        static extern IntPtr perf_mem_acc(int nb_tests);

        public struct MyData
        {
            public string id { set; get; }
            public double time { set; get; }
            public double instr_sec { set; get; }
        }

        public static double[] returnDoubleArray(int nb_tests)
        {
           IntPtr intPtr = perf_mem_acc(nb_tests);
            double[] ReturnArray = new double[nb_tests * 2 + 2];
            for (int j = 0; j < nb_tests * 2 + 2; j++)
            {
                byte[] ba = new byte[sizeof(double)];
                

                for (int i = 0; i < ba.Length; i++)
                   ba[i] = Marshal.ReadByte(intPtr, 8 * j + i);

                ReturnArray[j] = BitConverter.ToDouble(ba, 0);
            }

            return ReturnArray;
        }

        public Page14()
        {
            InitializeComponent();
        }

        public static void thread1()
        {
            Running runningPage = new Running();
            runningPage.Show();
            Dispatcher.Run();
        }

        public static void thread2(Page14 page14, Thread t1)
        {
            int nb_tests = Int32.Parse(page14.textBox.Text.ToString());
            double[] res = returnDoubleArray(nb_tests);

            for (int j = 0; j < 2 * nb_tests; j = j + 2)
            {
                page14.dataGrid.Items.Add(new MyData { id = (j / 2 + 1).ToString(), time = res[j], instr_sec = res[j + 1] });
            }
            page14.dataGrid.Items.Add(new MyData { id = "AVERAGE", time = res[2 * nb_tests], instr_sec = res[2 * nb_tests + 1] });

            t1.Abort();
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            Thread t1 = new Thread(() => thread1());
            t1.SetApartmentState(ApartmentState.STA);
            t1.Start();

            Dispatcher.BeginInvoke(new ThreadStart(() => thread2(this, t1)));
        }
    }
}

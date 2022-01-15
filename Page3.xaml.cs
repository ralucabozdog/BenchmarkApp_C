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

namespace WpfApp1
{
    /// <summary>
    /// Interaction logic for Page1.xaml
    /// </summary>
    public partial class Page3 : Window
    {
        public Page3(String l1, String l2, String l3, String l4, String l5, String l6)
        {
            InitializeComponent();
            label1.Content = l1;
            label2.Content = l2;
            label3.Content = l3;
            label4.Content = l4;
            label5.Content = l5;
            label6.Content = l6;
        }
    }
}

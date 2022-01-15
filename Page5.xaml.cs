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
    public partial class Page5 : Window
    {
        public Page5(int i1, int i2, int i3, int i4)
        {
            InitializeComponent();
            label1.Content = i1;
            label2.Content = i2;
            label3.Content = i3;
            label4.Content = i4.ToString("X4");
        }
    }
}

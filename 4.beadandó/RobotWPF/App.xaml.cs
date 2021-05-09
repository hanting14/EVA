using System;
using System.Collections.Generic;
using System.Configuration;
using System.Data;
using System.Linq;
using System.Threading.Tasks;
using System.Windows;
using RobotWPF.View;
using RobotWPF.ViewModel;

namespace RobotWPF
{
    /// <summary>
    /// Interaction logic for App.xaml
    /// </summary>
    public partial class App : Application
    {
        RobotViewModel viewModel;
        MainWindow window;

        public App()
        {
            viewModel = new RobotViewModel();
            window = new MainWindow();
            window.DataContext = viewModel;
            window.Show();
        }
    }
}

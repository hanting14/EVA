using System;
using System.Collections.Generic;
using System.Text;

namespace RobotWPF.ViewModel
{
    public class Field : ViewModelBase
    {
        private int x;
        private int y;
        private int value;
        private bool isRobot;
        private DelegateCommand raiseWall;
        public EventHandler RaiseWallEvent;

        public int X { get => x; set { x = value; OnPropertyChanged(); } }
        public int Y { get => y; set { y = value; OnPropertyChanged(); } }
        public int Value { get => value; set { this.value = value; OnPropertyChanged(); } }
        public bool IsRobot { get => isRobot; set { isRobot = value; OnPropertyChanged(); } }
        public DelegateCommand RaiseWall { get => raiseWall; set => raiseWall = value; }

        public Field(int x, int y, int value, bool isRobot)
        {
            this.x = x;
            this.y = y;
            this.value = value;
            this.isRobot = isRobot;
            RaiseWall = new DelegateCommand(WallRaiser);
        }

        private void WallRaiser(object param)
        {
            RaiseWallEvent(this, null);
        }
    }
}

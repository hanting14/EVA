using System;
using System.Collections.Generic;
using System.Drawing;
using System.Text;
using System.Threading.Tasks;
using System.Timers;
using Robot.Persistence;

namespace Robot.Model
{
    public class RobotGameModel
    {
        public enum GameDifficulty { Easy, Medium, Hard }     
        public enum RobotDirection { Up, Down, Left, Right }  

        #region Difficulty constants

        private const int TableSizeEasy = 7;
        private const int TableSizeMedium = 11;
        private const int TableSizeHard = 15;
        private const int RobotSpeedEasy = 1000;
        private const int RobotSpeedMedium = 800;
        private const int RobotSpeedHard = 700;

        #endregion

        #region Fields

        private GameDifficulty difficulty;          //Játék nehézsége
        private RobotDirection direction;           //Robot mozgásának iránya
        private List<List<int>> gameTable;          //Játék tábla adatai
        private Point robotLocation;                //Robot helyzete
        private int tableSize;                      //Játék tábla mérete
        private Timer gameTimer;                    //Idő mérése
        private Timer robotTimer;                   //Pályát szabályozó időzítő
        private int gameTime;                       //Játék ideje
        private int robotSpeed;                     //Robot sebessége
        private IRobotDataAccess robotDataAccess;   //Játék betöltése, mentése

        #endregion

        #region Proporties
        public GameDifficulty Difficulty { get { return difficulty; } set { difficulty = value; } }
        public RobotDirection Direction { get { return direction; } set { direction = value; } }
        public List<List<int>> GameTable { get { return gameTable; } }
        public Point RobotLocation { get { return robotLocation; } set { 
                robotLocation = value; 
                if (gameTable[robotLocation.X][robotLocation.Y] == 1)
                {
                    gameTable[robotLocation.X][robotLocation.Y] = 2;
                }
            } 
        }
        public int TableSize { get { return tableSize; } }
        public Timer GameTimer { get { return gameTimer; } }
        public Timer RobotTimer { get { return robotTimer; } }
        public int GameTime { get { return gameTime; } }
        public int RobotSpeed { get { return robotSpeed; } set { robotSpeed = value; } }

        #endregion

        #region Events

        public event EventHandler<string> TimerEvent;       //Játék idő átadása
        public event EventHandler<bool> UpdateGame;         //Pálya változások jelzése

        #endregion

        #region Contructor

        /// <summary>
        /// Játék logika alaphelyzetbe állítása
        /// </summary>
        public RobotGameModel()
        {
            difficulty = GameDifficulty.Easy;
            direction = RobotDirection.Up;
            robotDataAccess = new RobotDataAccess();
            gameTimer = new Timer();
            gameTimer.Interval = 1000;
            gameTimer.Elapsed += GameTimer_Elapsed;
            robotTimer = new Timer();
            robotTimer.Elapsed += Step;
        }

        #endregion

        #region Timer event handlers

        /// <summary>
        /// Játék idő átalakítása megfelelő formátumba
        /// </summary>
        /// <param name="sender">Játék időzítője.</param>
        /// <param name="e">Másodpercek telése.</param>
        private void GameTimer_Elapsed(object sender, ElapsedEventArgs e)
        {
            gameTime++;
            string time = "";
            if (gameTime / 60 < 10)
            {
                if (gameTime % 60 < 10)
                    time = (gameTime / 3600).ToString() + ":0" + (gameTime / 60).ToString() + ":0" + (gameTime % 60).ToString();
                else
                    time = (gameTime / 3600).ToString() + ":0" + (gameTime / 60).ToString() + ":" + (gameTime % 60).ToString();
            }
            else
            {
                if (gameTime % 60 < 10)
                    time = (gameTime / 3600).ToString() + ":" + (gameTime / 60).ToString() + ":0" + (gameTime % 60).ToString();
                else
                    time = (gameTime / 3600).ToString() + ":" + (gameTime / 60).ToString() + ":" + (gameTime % 60).ToString();
            }
            if (TimerEvent != null)
                TimerEvent(this, time);
        }

        /// <summary>
        /// Robot mozgatása
        /// </summary>
        /// <param name="sender">Robot időzítője.</param>
        /// <param name="e">Idő telése, robot sebességtől függ.</param>
        private void Step(object sender, ElapsedEventArgs e)
        {
            Random random = new Random();
            if (direction == RobotDirection.Up)
            {
                if (robotLocation.X - 1 >= 0)
                {
                    if (gameTable[robotLocation.X - 1][robotLocation.Y] == 1)
                    {
                        gameTable[robotLocation.X - 1][robotLocation.Y] = 2;
                        int r = random.Next(2);
                        if (r == 0)
                        {
                            direction = RobotDirection.Left;
                        }
                        else if (r == 1)
                        {
                            direction = RobotDirection.Right;
                        }
                    }
                    else
                    {
                        robotLocation.X--;
                        int r = random.Next(10);
                        if (r == 6 || r == 7)
                        {
                            direction = RobotDirection.Left;
                        }
                        else if (r == 8 || r == 9)
                        {
                            direction = RobotDirection.Right;
                        }
                    }

                }
                else
                    direction = RobotDirection.Down;
            }
            else if (direction == RobotDirection.Down)
            {
                if (robotLocation.X + 1 < tableSize)
                {
                    if (gameTable[robotLocation.X + 1][robotLocation.Y] == 1)
                    {
                        gameTable[robotLocation.X + 1][robotLocation.Y] = 2;
                        int r = random.Next(2);
                        if (r == 0)
                        {
                            direction = RobotDirection.Left;
                        }
                        else if (r == 1)
                        {
                            direction = RobotDirection.Right;
                        }
                    }
                    else
                    {
                        robotLocation.X++;
                        int r = random.Next(10);
                        if (r == 6 || r == 7)
                        {
                            direction = RobotDirection.Left;
                        }
                        else if (r == 8 || r == 9)
                        {
                            direction = RobotDirection.Right;
                        }
                    }

                }
                else
                    direction = RobotDirection.Up;
            }
            else if (direction == RobotDirection.Right)
            {
                if (robotLocation.Y + 1 < tableSize)
                {
                    if (gameTable[robotLocation.X][robotLocation.Y + 1] == 1)
                    {
                        gameTable[robotLocation.X][robotLocation.Y + 1] = 2;
                        int r = random.Next(2);
                        if (r == 0)
                        {
                            direction = RobotDirection.Up;
                        }
                        else if (r == 1)
                        {
                            direction = RobotDirection.Down;
                        }
                    }
                    else
                    {
                        robotLocation.Y++;
                        int r = random.Next(10);
                        if (r == 6 || r == 7)
                        {
                            direction = RobotDirection.Up;
                        }
                        else if (r == 8 || r == 9)
                        {
                            direction = RobotDirection.Down;
                        }
                    }

                }
                else
                    direction = RobotDirection.Left;
            }
            else if (direction == RobotDirection.Left)
            {
                if (robotLocation.Y - 1 >= 0)
                {
                    if (gameTable[robotLocation.X][robotLocation.Y - 1] == 1)
                    {
                        gameTable[robotLocation.X][robotLocation.Y - 1] = 2;
                        int r = random.Next(2);
                        if (r == 0)
                        {
                            direction = RobotDirection.Up;
                        }
                        else if (r == 1)
                        {
                            direction = RobotDirection.Down;
                        }
                    }
                    else
                    {
                        robotLocation.Y--;
                        int r = random.Next(10);
                        if (r == 6 || r == 7)
                        {
                            direction = RobotDirection.Up;
                        }
                        else if (r == 8 || r == 9)
                        {
                            direction = RobotDirection.Down;
                        }
                    }

                }
                else
                    direction = RobotDirection.Right;
            }
            bool gameEnd = robotLocation.X == tableSize / 2 && robotLocation.Y == tableSize / 2;
            if (gameEnd)
            {
                robotTimer.Stop();
                gameTimer.Stop();
            }
            if (UpdateGame != null)
                UpdateGame(this, gameEnd);
        }

        #endregion

        #region Public game methods

        /// <summary>
        /// Játék elindítása
        /// </summary>
        public void NewGame()
        {
            if (gameTimer.Enabled)
                gameTimer.Stop();
            if (robotTimer.Enabled)
                robotTimer.Stop();
            gameTime = 0;
            switch(difficulty)
            {
                case GameDifficulty.Easy:
                    GenerateTable(TableSizeEasy);
                    robotSpeed = RobotSpeedEasy;
                    break;
                case GameDifficulty.Medium:
                    GenerateTable(TableSizeMedium);
                    robotSpeed = RobotSpeedMedium;
                    break;
                case GameDifficulty.Hard:
                    GenerateTable(TableSizeHard);
                    robotSpeed = RobotSpeedHard;
                    break;
            }
            robotTimer.Interval = robotSpeed;
            robotTimer.Start();
            gameTimer.Start();
        }

        /// <summary>
        /// Játék állapotának szabályozása
        /// </summary>
        /// <param name="stop">Játék megállítása/elindítása.</param>
        public void StopGame(bool stop)
        {
            if (stop)
            {
                gameTimer.Stop();
                robotTimer.Stop();
            }
            else
            {
                gameTimer.Start();
                robotTimer.Start();
            }
        }

        /// <summary>
        /// Fal felemelése
        /// </summary>
        /// <param name="x">X koordináta.</param>
        /// <param name="y">Y koordináta.</param>
        public void RaiseWall(int x, int y)
        {
            gameTable[x][y] = 1;
        }

        /// <summary>
        /// Játék betöltése.
        /// </summary>
        /// <param name="path">Elérési útvonal.</param>
        public async Task LoadGameAsync(String path)
        {
            if (robotDataAccess == null)
                throw new InvalidOperationException("No data access is provided.");

            gameTable = await robotDataAccess.LoadAsync(path);
            tableSize = gameTable.Count;
            gameTime = gameTable[tableSize - 1][tableSize];
            robotLocation.X = gameTable[tableSize - 1][tableSize+1];
            robotLocation.Y = gameTable[tableSize - 1][tableSize+2];
            switch (tableSize)
            {
                case TableSizeEasy:
                    difficulty = GameDifficulty.Easy;
                    robotSpeed = RobotSpeedEasy;
                    break;
                case TableSizeMedium:
                    difficulty = GameDifficulty.Medium;
                    robotSpeed = RobotSpeedMedium;
                    break;
                case TableSizeHard:
                    difficulty = GameDifficulty.Hard;
                    robotSpeed = RobotSpeedHard;
                    break;
            }
        }

        /// <summary>
        /// Játék mentése.
        /// </summary>
        /// <param name="path">Elérési útvonal.</param>
        public async Task SaveGameAsync(String path)
        {
            if (robotDataAccess == null)
                throw new InvalidOperationException("No data access is provided.");

            gameTable[tableSize - 1].Add(GameTime);
            gameTable[tableSize - 1].Add(robotLocation.X);
            gameTable[tableSize - 1].Add(robotLocation.Y);
            await robotDataAccess.SaveAsync(path, gameTable);
        }


        #endregion

        #region Private game methods

        /// <summary>
        /// Játék tábla legenerálása
        /// </summary>
        /// <param name="size">Játék tábla mérete.</param>
        private void GenerateTable(int size)
        {
            tableSize = size;
            Random random = new Random();
            do
            {
                robotLocation.X = random.Next(size - 1);
                robotLocation.Y = random.Next(size - 1);
            } while (robotLocation.X == size / 2 && robotLocation.Y == size / 2);
            gameTable = new List<List<int>>();
            for (int i = 0; i < size; ++i)
            {
                gameTable.Add(new List<int>());
            }
            for (int i = 0; i<size; ++i)
            {
                for (int j = 0; j<size; ++j)
                {
                    if (i == size / 2 && j == size / 2)
                        gameTable[i].Add(3);
                    else
                        gameTable[i].Add(0);
                }
            }
        }

        #endregion
    }
}

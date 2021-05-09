using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Text;
using System.Windows;
using Microsoft.Win32;
using RobotWPF.Model;
using RobotWPF.Model.Persistence;

namespace RobotWPF.ViewModel
{
    public class RobotViewModel : ViewModelBase
    {
        private ObservableCollection<Field> fields;
        private int tableSize;
        private RobotGameModel model;
        private int width;
        private int height;
        private string time;
        private bool gameStopped;
        private DelegateCommand newGame;
        private DelegateCommand pauseGame;
        private DelegateCommand saveGame;
        private DelegateCommand loadGame;
        private DelegateCommand difficultyEasy;
        private DelegateCommand difficultyMedium;
        private DelegateCommand difficultyHard;

        public ObservableCollection<Field> Fields { get => fields; set => fields = value; }
        public int TableSize { get => tableSize; set { tableSize = value; OnPropertyChanged(); } }
        public RobotGameModel Model { get => model; set => model = value; }
        public int Width { get => width; set { width = value; OnPropertyChanged(); } }
        public int Height { get => height; set { height = value; OnPropertyChanged(); } }
        public string Time { get => time; set { time = value; OnPropertyChanged(); } }
        public DelegateCommand NewGame { get => newGame; set => newGame = value; }
        public DelegateCommand PauseGame { get => pauseGame; set => pauseGame = value; }
        public DelegateCommand SaveGame { get => saveGame; set => saveGame = value; }
        public DelegateCommand LoadGame { get => loadGame; set => loadGame = value; }
        public DelegateCommand DifficultyEasy { get => difficultyEasy; set => difficultyEasy = value; }
        public DelegateCommand DifficultyMedium { get => difficultyMedium; set => difficultyMedium = value; }
        public DelegateCommand DifficultyHard { get => difficultyHard; set => difficultyHard = value; }

        public RobotViewModel()
        {
            fields = new ObservableCollection<Field>();
            model = new RobotGameModel();
            newGame = new DelegateCommand(NewGameButton);
            pauseGame = new DelegateCommand(PauseButton);
            saveGame = new DelegateCommand(SaveButton);
            loadGame = new DelegateCommand(LoadButton);
            difficultyEasy = new DelegateCommand(EasyButton);
            difficultyMedium = new DelegateCommand(MediumButton);
            difficultyHard = new DelegateCommand(HardButton);
            model.TimerEvent += Model_TimerEvent;
            model.UpdateGame += Model_UpdateGame;
            model.Difficulty = RobotGameModel.GameDifficulty.Easy;
            gameStopped = false;
            StartNewGame();
        }

        private void Model_UpdateGame(object sender, bool e)
        {
            if (e)
            {
                MessageBox.Show("Congratulations on your victory! \n Your " + Time,
                    "Game End");
            }
            else
            {
                for (int i = 0; i < TableSize; ++i)
                {
                    for (int j = 0; j < TableSize; ++j)
                    {
                        bool isRobot = model.RobotLocation.X == i && model.RobotLocation.Y == j;
                        Fields[i * TableSize + j].Value = model.GameTable[i][j];
                        Fields[i * TableSize + j].IsRobot = isRobot;
                    }
                }
            }
        }

        private void Model_TimerEvent(object sender, string e)
        {
            Time = "Gametime: " + e;
        }

        private void StartNewGame()
        {
            if (model.Difficulty == RobotGameModel.GameDifficulty.Easy)
            {
                Width = 400;
                Height = 460;
            }
            else if (model.Difficulty == RobotGameModel.GameDifficulty.Medium)
            {
                Width = 600;
                Height = 660;
            }
            else if (model.Difficulty == RobotGameModel.GameDifficulty.Hard)
            {
                Width = 800;
                Height = 860;
            }
            model.NewGame();
            TableSize = model.TableSize;
            Fields.Clear();
            for (int i = 0; i < TableSize; i++)
            {
                for (int j = 0; j < TableSize; j++)
                {
                    bool isRobot = model.RobotLocation.X == i && model.RobotLocation.Y == j;
                    Field field = new Field(i, j, model.GameTable[i][j], isRobot);
                    Fields.Add(field);
                    field.RaiseWallEvent += RaiseWall;
                }
            }
        }

        private void RaiseWall(object sender, EventArgs e)
        {
            Field field = sender as Field;
            model.RaiseWall(field.X, field.Y);
        }
        private void NewGameButton(object param)
        {
            StartNewGame();
        }
        private void PauseButton(object param)
        {
            if (!gameStopped)
            {
                model.StopGame(true);
            }
            else
            {
                model.StopGame(false);
            }
            gameStopped = !gameStopped;
        }
        private async void SaveButton(object param)
        {
            SaveFileDialog saveFileDialog = new SaveFileDialog();
            if (saveFileDialog.ShowDialog() == true)
            {
                try
                {
                    await model.SaveGameAsync(saveFileDialog.FileName);
                }
                catch (RobotDataException)
                {
                    MessageBox.Show("Játék mentése sikertelen!" + Environment.NewLine +
                        "Hibás az elérési út, vagy a könyvtár nem írható.", "Hiba!");
                }
            }
        }
        private async void LoadButton(object param)
        {
            OpenFileDialog openFileDialog = new OpenFileDialog();
            if (openFileDialog.ShowDialog() == true)
            {
                try
                {
                    await model.LoadGameAsync(openFileDialog.FileName);
                    if (model.Difficulty == RobotGameModel.GameDifficulty.Easy)
                    {
                        Width = 400;
                        Height = 460;
                    }
                    else if (model.Difficulty == RobotGameModel.GameDifficulty.Medium)
                    {
                        Width = 600;
                        Height = 660;
                    }
                    else if (model.Difficulty == RobotGameModel.GameDifficulty.Hard)
                    {
                        Width = 800;
                        Height = 860;
                    }
                    TableSize = model.TableSize;
                    Fields.Clear();
                    for (int i = 0; i < TableSize; i++)
                    {
                        for (int j = 0; j < TableSize; j++)
                        {
                            bool isRobot = model.RobotLocation.X == i && model.RobotLocation.Y == j;
                            Field field = new Field(i, j, model.GameTable[i][j], isRobot);
                            Fields.Add(field);
                            field.RaiseWallEvent += RaiseWall;
                        }
                    }
                }
                catch (RobotDataException)
                {
                    MessageBox.Show("Játék betöltése sikertelen!" + Environment.NewLine +
                        "Hibás az elérési út, vagy a fájlformátum.", "Hiba!");
                }
            }
        }
        private void EasyButton(object param)
        {
            model.Difficulty = RobotGameModel.GameDifficulty.Easy;
            StartNewGame();
        }
        private void MediumButton(object param)
        {
            model.Difficulty = RobotGameModel.GameDifficulty.Medium;
            StartNewGame();
        }
        private void HardButton(object param)
        {
            model.Difficulty = RobotGameModel.GameDifficulty.Hard;
            StartNewGame();
        }
    }
}

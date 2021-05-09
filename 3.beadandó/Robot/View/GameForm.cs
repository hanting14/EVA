using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using Robot.Model;
using Robot.Persistence;

namespace Robot
{
    public partial class GameForm : Form
    {
        #region Fields

        private RobotGameModel model; //Játék logikája
        private Button[][] grid;      //Pálya egy 2d gomb tömbben
        private bool gameStopped;     //Játék álló helyzete

        #endregion

        #region Constructor
        public GameForm()
        {
            InitializeComponent();
        }

        #endregion

        #region View event handlers

        /// <summary>
        /// Felület betöltése
        /// </summary>
        /// <param name="sender">Felület.</param>
        /// <param name="e">Felület betöltött.</param>
        private void GameForm_Load(object sender, EventArgs e)
        {
            model = new RobotGameModel();
            model.TimerEvent += Model_TimerEvent;
            model.UpdateGame += Model_UpdateGame;
            newGameFileMenu.Click += NewGameFileMenu_Click;
            pauseGameFileMenu.Click += PauseGameFileMenu_Click;
            saveGameFileMenu.Click += SaveGameFileMenu_Click;
            loadGameFileMenu.Click += LoadGameFileMenu_Click;
            closeGameFileMenu.Click += CloseGameFileMenu_Click;
            easyDifficultyMenu.Click += EasyDifficultyMenu_Click;
            mediumDifficultyMenu.Click += MediumDifficultyMenu_Click;
            hardDifficultyMenu.Click += HardDifficultyMenu_Click;
            saveGameFileMenu.Enabled = false;
            loadGameFileMenu.Enabled = false;
            easyDifficultyMenu.Checked = true;
            gameStopped = false;
            NewGame();
        }

        /// <summary>
        /// Új játék hívása
        /// </summary>
        /// <param name="sender">Új játék gomb.</param>
        /// <param name="e">Gomb lenyomása.</param>
        private void NewGameFileMenu_Click(object sender, EventArgs e)
        {
            NewGame();
        }

        /// <summary>
        /// Játék megállítása/elindítása
        /// </summary>
        /// <param name="sender">Megállít/elindít játék gomb.</param>
        /// <param name="e">Gomb lenyomása.</param>
        private void PauseGameFileMenu_Click(object sender, EventArgs e)
        {
            if (!gameStopped)
            {
                pauseGameFileMenu.Text = "Resume";
                model.StopGame(true);
                for (int i = 0; i < grid.Length; ++i)
                {
                    for (int j = 0; j < grid.Length; ++j)
                    {
                        grid[i][j].Enabled = false;
                    }
                }
                saveGameFileMenu.Enabled = true;
                loadGameFileMenu.Enabled = true;
            }
            else if (gameStopped)
            {
                pauseGameFileMenu.Text = "Pause";
                model.StopGame(false);
                saveGameFileMenu.Enabled = false;
                loadGameFileMenu.Enabled = false;
            }
            gameStopped = !gameStopped;
        }

        /// <summary>
        /// Játék betöltése
        /// </summary>
        /// <param name="sender">Játék betöltése gomb.</param>
        /// <param name="e">Gomb lenyomása.</param>
        private async void LoadGameFileMenu_Click(object sender, EventArgs e)
        {
            OpenFileDialog openFileDialog = new OpenFileDialog();
            if (openFileDialog.ShowDialog() == DialogResult.OK)
            {
                try
                {
                    await model.LoadGameAsync(openFileDialog.FileName);
                    if (model.Difficulty == RobotGameModel.GameDifficulty.Easy)
                    {
                        this.Size = new Size(400, 460);
                        currentDifficultyStatusLabel.Text = "Easy";
                    }
                    else if (model.Difficulty == RobotGameModel.GameDifficulty.Medium)
                    {
                        this.Size = new Size(600, 660);
                        currentDifficultyStatusLabel.Text = "Medium";
                    }
                    else if (model.Difficulty == RobotGameModel.GameDifficulty.Hard)
                    {
                        this.Size = new Size(800, 860);
                        currentDifficultyStatusLabel.Text = "Hard";
                    }
                    GenerateTable();
                    UpdateTable();
                    for (int i = 0; i < model.TableSize; ++i)
                    {
                        for (int j = 0; j < model.TableSize; ++j)
                        {
                            grid[i][j].Enabled = false;
                        }
                    }
                }
                catch (RobotDataException)
                {
                    MessageBox.Show("Játék betöltése sikertelen!" + Environment.NewLine + 
                        "Hibás az elérési út, vagy a fájlformátum.", "Hiba!", MessageBoxButtons.OK, MessageBoxIcon.Error);
                }
            }
        }

        /// <summary>
        /// Játék mentése
        /// </summary>
        /// <param name="sender">Játék mentése gomb.</param>
        /// <param name="e">Gomb lenyomása.</param>
        private async void SaveGameFileMenu_Click(object sender, EventArgs e)
        {
            SaveFileDialog saveFileDialog = new SaveFileDialog();
            if (saveFileDialog.ShowDialog() == DialogResult.OK)
            {
                try
                {
                    await model.SaveGameAsync(saveFileDialog.FileName);
                }
                catch (RobotDataException)
                {
                    MessageBox.Show("Játék mentése sikertelen!" + Environment.NewLine + 
                        "Hibás az elérési út, vagy a könyvtár nem írható.", "Hiba!", MessageBoxButtons.OK, MessageBoxIcon.Error);
                }
            }
        }

        /// <summary>
        /// Játék nehézségének átállítása és játék megállítása
        /// </summary>
        /// <param name="sender">Nehéz játék gomb.</param>
        /// <param name="e">Gomb lenyomása.</param>
        private void HardDifficultyMenu_Click(object sender, EventArgs e)
        {
            if (model.Difficulty != RobotGameModel.GameDifficulty.Hard)
            {
                model.Difficulty = RobotGameModel.GameDifficulty.Hard;
                currentDifficultyStatusLabel.Text = "Hard";
                model.StopGame(true);
                for (int i = 0; i < grid.Length; ++i)
                {
                    for (int j = 0; j < grid.Length; ++j)
                    {
                        grid[i][j].Enabled = false;
                    }
                }
                gameStopped = true;
                pauseGameFileMenu.Enabled = false;
                saveGameFileMenu.Enabled = true;
                loadGameFileMenu.Enabled = true;
                easyDifficultyMenu.Checked = false;
                mediumDifficultyMenu.Checked = false;
                hardDifficultyMenu.Checked = true;
            }
        }

        /// <summary>
        /// Játék nehézségének átállítása és játék megállítása
        /// </summary>
        /// <param name="sender">Közepes játék gomb.</param>
        /// <param name="e">Gomb lenyomása.</param>
        private void MediumDifficultyMenu_Click(object sender, EventArgs e)
        {
            if (model.Difficulty != RobotGameModel.GameDifficulty.Medium)
            {
                model.Difficulty = RobotGameModel.GameDifficulty.Medium;
                currentDifficultyStatusLabel.Text = "Medium";
                model.StopGame(true);
                for (int i = 0; i < grid.Length; ++i)
                {
                    for (int j = 0; j < grid.Length; ++j)
                    {
                        grid[i][j].Enabled = false;
                    }
                }
                gameStopped = true;
                pauseGameFileMenu.Enabled = false;
                saveGameFileMenu.Enabled = true;
                loadGameFileMenu.Enabled = true;
                easyDifficultyMenu.Checked = false;
                mediumDifficultyMenu.Checked = true;
                hardDifficultyMenu.Checked = false;
            }
        }

        /// <summary>
        /// Játék nehézségének átállítása és játék megállítása
        /// </summary>
        /// <param name="sender">Könnyű játék gomb.</param>
        /// <param name="e">Gomb lenyomása.</param>
        private void EasyDifficultyMenu_Click(object sender, EventArgs e)
        {
            if (model.Difficulty != RobotGameModel.GameDifficulty.Easy)
            {
                model.Difficulty = RobotGameModel.GameDifficulty.Easy;
                currentDifficultyStatusLabel.Text = "Easy";
                model.StopGame(true);
                for (int i = 0; i < grid.Length; ++i)
                {
                    for (int j = 0; j < grid.Length; ++j)
                    {
                        grid[i][j].Enabled = false;
                    }
                }
                gameStopped = true;
                pauseGameFileMenu.Enabled = false;
                saveGameFileMenu.Enabled = true;
                loadGameFileMenu.Enabled = true;
                easyDifficultyMenu.Checked = true;
                mediumDifficultyMenu.Checked = false;
                hardDifficultyMenu.Checked = false;
            }
        }

        /// <summary>
        /// Játék bezárása
        /// </summary>
        /// <param name="sender">Játék bezárása gomb.</param>
        /// <param name="e">Gomb lenyomása.</param>
        private void CloseGameFileMenu_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        /// <summary>
        /// Fal felemelése
        /// </summary>
        /// <param name="sender">Játék tábla gombjai.</param>
        /// <param name="e">Gomb lenyomása.</param>
        private void Grid_Click(object sender, EventArgs e)
        {
            int x = 0;
            int y = 0;
            for (int i = 0; i < grid.Length; ++i)
            {
                for (int j = 0; j < grid.Length; ++j)
                {
                    if (grid[i][j] == sender)
                    {
                        x = i;
                        y = j;
                    }
                }
            }
            model.RaiseWall(x, y);
            UpdateTable();
        }

        #endregion

        #region Model event handlers

        /// <summary>
        /// Játék idő kiírása
        /// </summary>
        /// <param name="sender">Játék logika.</param>
        /// <param name="e">Játék idő.</param>
        private void Model_TimerEvent(object sender, string e)
        {
            currentTimeStatusLabel.Text = e;
        }

        /// <summary>
        /// Játék tábla felülírása és játék végének ellenőrzése
        /// </summary>
        /// <param name="sender">Játék logika.</param>
        /// <param name="e">Játék vége.</param>
        private void Model_UpdateGame(object sender, bool e)
        {
            if (e)
            {
                MessageBox.Show("Congratulations on your victory! \n Your time: " + currentTimeStatusLabel.Text,
                    "Game End", MessageBoxButtons.OK );
            }
            else if (!gameStopped)
                UpdateTable();
        }

        #endregion

        #region Private methods

        /// <summary>
        /// Új játék indítása
        /// </summary>
        private void NewGame()
        {
            pauseGameFileMenu.Enabled = true;
            saveGameFileMenu.Enabled = false;
            loadGameFileMenu.Enabled = false;
            pauseGameFileMenu.Text = "Pause";
            gameStopped = false;
            model.NewGame();
            if (model.Difficulty == RobotGameModel.GameDifficulty.Easy)
                this.Size = new Size(400, 460);
            else if (model.Difficulty == RobotGameModel.GameDifficulty.Medium)
                this.Size = new Size(600, 660);
            else if (model.Difficulty == RobotGameModel.GameDifficulty.Hard)
                this.Size = new Size(800, 860);
            GenerateTable();
            UpdateTable();
        }

        /// <summary>
        /// Játék tábla legenerálása
        /// </summary>
        private void GenerateTable()
        {
            if (grid != null)
            {
                for (int i = 0; i < grid.Length; ++i)
                {
                    for (int j = 0; j < grid.Length; ++j)
                    {
                        grid[i][j].Click -= Grid_Click;
                        Controls.Remove(grid[i][j]);
                    }
                }
            }
            grid = new Button[model.TableSize][];
            for (int i = 0; i < model.TableSize; ++i)
            {
                grid[i] = new Button[model.TableSize];
                for (int j = 0; j < model.TableSize; ++j)
                {
                    grid[i][j] = new Button();
                    grid[i][j].Location = new Point(15 + 50 * j, 30 + 50 * i);
                    grid[i][j].Size = new Size(50, 50);
                    grid[i][j].FlatStyle = FlatStyle.Flat;
                    grid[i][j].Click += Grid_Click;
                    if (model.GameTable[i][j] != 0)
                        grid[i][j].Enabled = false;
                    else
                        grid[i][j].Enabled = true;
                    Controls.Add(grid[i][j]);
                }
            }
        }

        /// <summary>
        /// Játék tábla frissítése
        /// </summary>
        private void UpdateTable()
        {
            for (int i = 0; i < model.TableSize; ++i)
            {
                for (int j = 0; j < model.TableSize; ++j)
                {
                    if (model.GameTable[i][j] == 0)
                        grid[i][j].Image = Image.FromFile(@"..\..\..\Pictures\grass.png");
                    else if (model.GameTable[i][j] == 1)
                        grid[i][j].Image = Image.FromFile(@"..\..\..\Pictures\wall.png");
                    else if (model.GameTable[i][j] == 2)
                        grid[i][j].Image = Image.FromFile(@"..\..\..\Pictures\brokenWall.png");
                    else if (model.GameTable[i][j] == 3)
                        grid[i][j].Image = Image.FromFile(@"..\..\..\Pictures\magnet.png");
                    if (model.GameTable[i][j] != 0 || gameStopped)
                    {
                        if (grid[i][j].InvokeRequired)
                        {
                            grid[i][j].Invoke(new MethodInvoker(delegate
                            {
                                grid[i][j].Enabled = false;
                            }));
                        }
                    }
                    else
                    {
                        if (grid[i][j].InvokeRequired)
                        {
                            grid[i][j].Invoke(new MethodInvoker(delegate
                            {
                                grid[i][j].Enabled = true;
                            }));
                        }
                    }
                    if (i == model.RobotLocation.X && j == model.RobotLocation.Y)
                    {
                        if (model.Direction == RobotGameModel.RobotDirection.Right)
                            grid[i][j].Image = Image.FromFile(@"..\..\..\Pictures\robotRight.png");
                        else if (model.Direction == RobotGameModel.RobotDirection.Left)
                            grid[i][j].Image = Image.FromFile(@"..\..\..\Pictures\robotLeft.png");
                        else if (model.Direction == RobotGameModel.RobotDirection.Down)
                            grid[i][j].Image = Image.FromFile(@"..\..\..\Pictures\robotDown.png");
                        else if (model.Direction == RobotGameModel.RobotDirection.Up)
                            grid[i][j].Image = Image.FromFile(@"..\..\..\Pictures\robotUp.png");
                    }
                }
            }
        }

        #endregion
    }
}

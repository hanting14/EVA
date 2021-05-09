using Microsoft.VisualStudio.TestTools.UnitTesting;
using Robot.Model;
using static Robot.Model.RobotGameModel;

namespace RobotTest
{
    [TestClass]
    public class RobotUnitTest
    {
        private RobotGameModel model;

        [TestInitialize]
        public void Initialize()
        {
            model = new RobotGameModel();
            model.UpdateGame += Model_UpdateGame;
            model.NewGame();
        }

        private void Model_UpdateGame(object sender, bool e)
        {
            Assert.AreEqual(false, e);
            model.RobotLocation = new System.Drawing.Point(model.TableSize/2, model.TableSize/2);
            Assert.AreEqual(true, e);
            RobotGameModelWallTest();
        }

        [TestMethod]
        public void RobotGameModelWallTest()
        {
            Assert.AreEqual(model.GameTable[1][1], 0);
            model.RaiseWall(1, 1);
            Assert.AreEqual(model.GameTable[1][1], 1);
            model.RobotLocation = new System.Drawing.Point(1, 1);
            Assert.AreEqual(model.GameTable[1][1], 2);
        }

        [TestMethod]
        public void RobotGameModelNewGameEasyTest()
        {
            Assert.AreEqual(0, model.GameTime);

            model.NewGame();

            Assert.AreEqual(GameDifficulty.Easy, model.Difficulty);
            Assert.AreEqual(7, model.TableSize);
            Assert.AreEqual(1000, model.RobotSpeed);

            int emptyFields = 0;
            for (int i = 0; i < model.TableSize; i++)
            {
                for (int j = 0; j < model.TableSize; j++)
                {
                    if (model.GameTable[i][j] == 0)
                        emptyFields++;
                }
            }
            Assert.AreEqual(48, emptyFields);
        }

        [TestMethod]
        public void RobotGameModelNewGameMediumTest()
        {
            Assert.AreEqual(0, model.GameTime);

            model.Difficulty = GameDifficulty.Medium;
            model.NewGame();

            Assert.AreEqual(GameDifficulty.Medium, model.Difficulty);
            Assert.AreEqual(11, model.TableSize);
            Assert.AreEqual(800, model.RobotSpeed);

            int emptyFields = 0;
            for (int i = 0; i < model.TableSize; i++)
            {
                for (int j = 0; j < model.TableSize; j++)
                {
                    if (model.GameTable[i][j] == 0)
                        emptyFields++;
                }
            }
            Assert.AreEqual(120, emptyFields);
        }

        [TestMethod]
        public void RobotGameModelNewGameHardTest()
        {
            Assert.AreEqual(0, model.GameTime);

            model.Difficulty = GameDifficulty.Hard;
            model.NewGame();

            Assert.AreEqual(GameDifficulty.Hard, model.Difficulty);
            Assert.AreEqual(15, model.TableSize);
            Assert.AreEqual(700, model.RobotSpeed);

            int emptyFields = 0;
            for (int i = 0; i < model.TableSize; i++)
            {
                for (int j = 0; j < model.TableSize; j++)
                {
                    if (model.GameTable[i][j] == 0)
                        emptyFields++;
                }
            }
            Assert.AreEqual(224, emptyFields);
        }

        [TestMethod]
        public void RobotGameModelStopGame()
        {
            model.StopGame(true);

            Assert.IsFalse(model.GameTimer.Enabled);
            Assert.IsFalse(model.RobotTimer.Enabled);

            model.StopGame(false);

            Assert.IsTrue(model.GameTimer.Enabled);
            Assert.IsTrue(model.RobotTimer.Enabled);
        }

        [TestMethod]
        public void RobotGameModelRaiseWall()
        {
            model.NewGame();
            model.RaiseWall(1, 1);
            Assert.AreEqual(1, model.GameTable[1][1]);
        }

    }
}

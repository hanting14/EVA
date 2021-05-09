namespace Robot
{
    partial class GameForm
    {
        /// <summary>
        ///  Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        ///  Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        ///  Required method for Designer support - do not modify
        ///  the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.robotMenu = new System.Windows.Forms.MenuStrip();
            this.fileMenu = new System.Windows.Forms.ToolStripMenuItem();
            this.newGameFileMenu = new System.Windows.Forms.ToolStripMenuItem();
            this.pauseGameFileMenu = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
            this.saveGameFileMenu = new System.Windows.Forms.ToolStripMenuItem();
            this.loadGameFileMenu = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator2 = new System.Windows.Forms.ToolStripSeparator();
            this.closeGameFileMenu = new System.Windows.Forms.ToolStripMenuItem();
            this.settingsMenu = new System.Windows.Forms.ToolStripMenuItem();
            this.easyDifficultyMenu = new System.Windows.Forms.ToolStripMenuItem();
            this.mediumDifficultyMenu = new System.Windows.Forms.ToolStripMenuItem();
            this.hardDifficultyMenu = new System.Windows.Forms.ToolStripMenuItem();
            this.statusStrip = new System.Windows.Forms.StatusStrip();
            this.difficultyStatusLabel = new System.Windows.Forms.ToolStripStatusLabel();
            this.currentDifficultyStatusLabel = new System.Windows.Forms.ToolStripStatusLabel();
            this.toolStripStatusLabel1 = new System.Windows.Forms.ToolStripStatusLabel();
            this.timeStatusLabel = new System.Windows.Forms.ToolStripStatusLabel();
            this.currentTimeStatusLabel = new System.Windows.Forms.ToolStripStatusLabel();
            this.robotMenu.SuspendLayout();
            this.statusStrip.SuspendLayout();
            this.SuspendLayout();
            // 
            // robotMenu
            // 
            this.robotMenu.ImageScalingSize = new System.Drawing.Size(20, 20);
            this.robotMenu.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fileMenu,
            this.settingsMenu});
            this.robotMenu.Location = new System.Drawing.Point(0, 0);
            this.robotMenu.Name = "robotMenu";
            this.robotMenu.Size = new System.Drawing.Size(800, 28);
            this.robotMenu.TabIndex = 0;
            this.robotMenu.Text = "File";
            // 
            // fileMenu
            // 
            this.fileMenu.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.newGameFileMenu,
            this.pauseGameFileMenu,
            this.toolStripSeparator1,
            this.saveGameFileMenu,
            this.loadGameFileMenu,
            this.toolStripSeparator2,
            this.closeGameFileMenu});
            this.fileMenu.Name = "fileMenu";
            this.fileMenu.Size = new System.Drawing.Size(46, 24);
            this.fileMenu.Text = "File";
            // 
            // newGameFileMenu
            // 
            this.newGameFileMenu.Name = "newGameFileMenu";
            this.newGameFileMenu.Size = new System.Drawing.Size(165, 26);
            this.newGameFileMenu.Text = "New Game";
            // 
            // pauseGameFileMenu
            // 
            this.pauseGameFileMenu.Name = "pauseGameFileMenu";
            this.pauseGameFileMenu.Size = new System.Drawing.Size(165, 26);
            this.pauseGameFileMenu.Text = "Pause";
            // 
            // toolStripSeparator1
            // 
            this.toolStripSeparator1.Name = "toolStripSeparator1";
            this.toolStripSeparator1.Size = new System.Drawing.Size(162, 6);
            // 
            // saveGameFileMenu
            // 
            this.saveGameFileMenu.Name = "saveGameFileMenu";
            this.saveGameFileMenu.Size = new System.Drawing.Size(165, 26);
            this.saveGameFileMenu.Text = "Save";
            // 
            // loadGameFileMenu
            // 
            this.loadGameFileMenu.Name = "loadGameFileMenu";
            this.loadGameFileMenu.Size = new System.Drawing.Size(165, 26);
            this.loadGameFileMenu.Text = "Load";
            // 
            // toolStripSeparator2
            // 
            this.toolStripSeparator2.Name = "toolStripSeparator2";
            this.toolStripSeparator2.Size = new System.Drawing.Size(162, 6);
            // 
            // closeGameFileMenu
            // 
            this.closeGameFileMenu.Name = "closeGameFileMenu";
            this.closeGameFileMenu.Size = new System.Drawing.Size(165, 26);
            this.closeGameFileMenu.Text = "Close";
            // 
            // settingsMenu
            // 
            this.settingsMenu.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.easyDifficultyMenu,
            this.mediumDifficultyMenu,
            this.hardDifficultyMenu});
            this.settingsMenu.Name = "settingsMenu";
            this.settingsMenu.Size = new System.Drawing.Size(76, 24);
            this.settingsMenu.Text = "Settings";
            // 
            // easyDifficultyMenu
            // 
            this.easyDifficultyMenu.Name = "easyDifficultyMenu";
            this.easyDifficultyMenu.Size = new System.Drawing.Size(147, 26);
            this.easyDifficultyMenu.Text = "Easy";
            // 
            // mediumDifficultyMenu
            // 
            this.mediumDifficultyMenu.Name = "mediumDifficultyMenu";
            this.mediumDifficultyMenu.Size = new System.Drawing.Size(147, 26);
            this.mediumDifficultyMenu.Text = "Medium";
            // 
            // hardDifficultyMenu
            // 
            this.hardDifficultyMenu.Name = "hardDifficultyMenu";
            this.hardDifficultyMenu.Size = new System.Drawing.Size(147, 26);
            this.hardDifficultyMenu.Text = "Hard";
            // 
            // statusStrip
            // 
            this.statusStrip.ImageScalingSize = new System.Drawing.Size(20, 20);
            this.statusStrip.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.difficultyStatusLabel,
            this.currentDifficultyStatusLabel,
            this.toolStripStatusLabel1,
            this.timeStatusLabel,
            this.currentTimeStatusLabel});
            this.statusStrip.Location = new System.Drawing.Point(0, 424);
            this.statusStrip.Name = "statusStrip";
            this.statusStrip.Size = new System.Drawing.Size(800, 26);
            this.statusStrip.TabIndex = 1;
            this.statusStrip.Text = "statusStrip1";
            // 
            // difficultyStatusLabel
            // 
            this.difficultyStatusLabel.Name = "difficultyStatusLabel";
            this.difficultyStatusLabel.Size = new System.Drawing.Size(72, 20);
            this.difficultyStatusLabel.Text = "Difficulty:";
            // 
            // currentDifficultyStatusLabel
            // 
            this.currentDifficultyStatusLabel.Name = "currentDifficultyStatusLabel";
            this.currentDifficultyStatusLabel.Size = new System.Drawing.Size(38, 20);
            this.currentDifficultyStatusLabel.Text = "Easy";
            // 
            // toolStripStatusLabel1
            // 
            this.toolStripStatusLabel1.Name = "toolStripStatusLabel1";
            this.toolStripStatusLabel1.Size = new System.Drawing.Size(53, 20);
            this.toolStripStatusLabel1.Text = "           ";
            // 
            // timeStatusLabel
            // 
            this.timeStatusLabel.Name = "timeStatusLabel";
            this.timeStatusLabel.Size = new System.Drawing.Size(45, 20);
            this.timeStatusLabel.Text = "Time:";
            // 
            // currentTimeStatusLabel
            // 
            this.currentTimeStatusLabel.Name = "currentTimeStatusLabel";
            this.currentTimeStatusLabel.Size = new System.Drawing.Size(55, 20);
            this.currentTimeStatusLabel.Text = "0:00:00";
            // 
            // GameForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 20F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(this.statusStrip);
            this.Controls.Add(this.robotMenu);
            this.MainMenuStrip = this.robotMenu;
            this.Name = "GameForm";
            this.Text = "Elszabadult robot";
            this.Load += new System.EventHandler(this.GameForm_Load);
            this.robotMenu.ResumeLayout(false);
            this.robotMenu.PerformLayout();
            this.statusStrip.ResumeLayout(false);
            this.statusStrip.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.MenuStrip robotMenu;
        private System.Windows.Forms.ToolStripMenuItem fileMenu;
        private System.Windows.Forms.ToolStripMenuItem newGameFileMenu;
        private System.Windows.Forms.ToolStripMenuItem pauseGameFileMenu;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
        private System.Windows.Forms.ToolStripMenuItem saveGameFileMenu;
        private System.Windows.Forms.ToolStripMenuItem loadGameFileMenu;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator2;
        private System.Windows.Forms.ToolStripMenuItem closeGameFileMenu;
        private System.Windows.Forms.ToolStripMenuItem settingsMenu;
        private System.Windows.Forms.ToolStripMenuItem easyDifficultyMenu;
        private System.Windows.Forms.ToolStripMenuItem mediumDifficultyMenu;
        private System.Windows.Forms.ToolStripMenuItem hardDifficultyMenu;
        private System.Windows.Forms.StatusStrip statusStrip;
        private System.Windows.Forms.ToolStripStatusLabel difficultyStatusLabel;
        private System.Windows.Forms.ToolStripStatusLabel currentDifficultyStatusLabel;
        private System.Windows.Forms.ToolStripStatusLabel timeStatusLabel;
        private System.Windows.Forms.ToolStripStatusLabel currentTimeStatusLabel;
        private System.Windows.Forms.ToolStripStatusLabel toolStripStatusLabel1;
    }
}


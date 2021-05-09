using System;
using System.Collections.Generic;
using System.IO;
using System.Text;
using System.Threading.Tasks;

namespace Robot.Persistence
{
    class RobotDataAccess : IRobotDataAccess
    {
        /// <summary>
        /// Fájl betöltése.
        /// </summary>
        /// <param name="path">Elérési útvonal.</param>
        /// <returns>A fájlból beolvasott játéktábla.</returns>
        public async Task<List<List<int>>> LoadAsync(String path)
        {
            try
            {
                using (StreamReader reader = new StreamReader(path))
                {
                    String line = await reader.ReadLineAsync();
                    String[] numbers = line.Split(' ');
                    List<List<int>> table = new List<List<int>>();

                    for (int i = 0; i < numbers.Length-2; ++i)
                    {
                        table.Add(new List<int>());
                        for (int j = 0; j < numbers.Length - 1; ++j)
                        {
                            string n = numbers[j];
                            table[i].Add(int.Parse(numbers[j]));
                        }
                        line = await reader.ReadLineAsync();
                        numbers = line.Split(' ');
                    }
                    table.Add(new List<int>());
                    for (int j = 0; j < numbers.Length - 1; ++j)
                    {
                        string n = numbers[j];
                        table[table.Count-1].Add(int.Parse(numbers[j]));
                    }
                    line = await reader.ReadLineAsync();
                    numbers = line.Split(' ');
                    table[table.Count - 1].Add(int.Parse(numbers[0]));
                    table[table.Count - 1].Add(int.Parse(numbers[1]));
                    table[table.Count - 1].Add(int.Parse(numbers[2]));
                    return table;
                }
            }
            catch
            {
                throw new RobotDataException();
            }
        }

        /// <summary>
        /// Fájl mentése.
        /// </summary>
        /// <param name="path">Elérési útvonal.</param>
        /// <param name="table">A fájlba kiírandó játéktábla.</param>
        public async Task SaveAsync(String path, List<List<int>> table)
        {
            try
            {
                using (StreamWriter writer = new StreamWriter(path))
                {
                    for (int i = 0; i < table.Count; ++i)
                    {
                        for (int j = 0; j < table.Count; ++j)
                        {
                            await writer.WriteAsync(table[i][j] + " ");
                        }
                        await writer.WriteLineAsync();
                    }
                    await writer.WriteAsync(table[table.Count-1][table.Count] + " ");
                    await writer.WriteAsync(table[table.Count - 1][table.Count+1] + " ");
                    await writer.WriteAsync(table[table.Count - 1][table.Count+2] + " ");
                }
            }
            catch
            {
                throw new RobotDataException();
            }
        }
    }
}

using System;
using System.Collections.Generic;
using System.Text;
using System.Threading.Tasks;

namespace RobotWPF.Model.Persistence
{
    /// <summary>
    /// Robot fájl kezelő felülete.
    /// </summary>
    public interface IRobotDataAccess
    {
        /// <summary>
        /// Fájl betöltése.
        /// </summary>
        /// <param name="path">Elérési útvonal.</param>
        /// <returns>A fájlból beolvasott játéktábla.</returns>
        Task<List<List<int>>> LoadAsync(string path);

        /// <summary>
        /// Fájl mentése.
        /// </summary>
        /// <param name="path">Elérési útvonal.</param>
        /// <param name="table">A fájlba kiírandó játéktábla.</param>
        Task SaveAsync(String path, List<List<int>> table);
    }
}

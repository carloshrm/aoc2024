namespace aoc2024;
using System.IO;
using System;
using System.Numerics;

public class Program
{
    public record Antenna(Vector2 pos, char label);

    static void Main(string[] args)
    {
        var input = File.ReadAllLines($@"{Directory.GetParent(Environment.CurrentDirectory).Parent.Parent.FullName}\inputs\Day8.txt");

        var antennaList = new List<Antenna>();
        for (int i = 0; i < input.Length; i++)
        {
            for (int j = 0; j < input.First().Length; j++)
            {
                if (input[i][j] != '.')
                    antennaList.Add(new Antenna(new Vector2(j, i), input[i][j]));
            }
        }

        var antinodes = new HashSet<Vector2>();
        foreach (var antennaGroup in antennaList.GroupBy(a => a.label))
        {
            foreach (var ant_a in antennaGroup)
            {
                foreach (var ant_b in antennaGroup)
                {
                    if (ant_a == ant_b)
                        continue;

                    var distance = ant_a.pos - ant_b.pos;
                    int multiplier = 0;
                    while (true)
                    {
                        var antinodeEcho = ant_a.pos + (multiplier * distance);
                        if (!input.checkBounds(antinodeEcho))
                            break;
                    
                        if (!antinodes.Contains(antinodeEcho))
                            antinodes.Add(antinodeEcho);

                        multiplier++;
                    }
                }
            }
        }

        Console.WriteLine(antinodes.Count());
    }
}

public static class Helpers
{
    public static bool checkBounds<T>(this IEnumerable<IEnumerable<T>> field, Vector2 pos) => pos.X >= 0 && pos.Y >= 0 && pos.X < field.First().Count() && pos.Y < field.Count();
}
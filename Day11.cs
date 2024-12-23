namespace aoc2024;
using System.IO;
using System;
using System.Numerics;

public class Program
{
    static void Main(string[] args)
    {
        
        var stoneTracker = "572556 22 0 528 4679021 1 10725 2790".Split(' ').ToDictionary(ulong.Parse, (_) => (ulong)1);
        for (int i = 0; i < 75; i++)
        {            
            var newBlink = new Dictionary<ulong, ulong>();
            foreach (var (stone, count) in stoneTracker)
            {
                var blink = changeStone(stone);
                foreach (var newStone in blink)
                {
                    if (newBlink.ContainsKey(newStone))
                        newBlink[newStone] += count;
                    else
                        newBlink.Add(newStone, count);
                }
            }
            stoneTracker = newBlink;
        }

        ulong sum = 0;
        foreach (var (_, count) in stoneTracker)
            sum += count;

        Console.WriteLine(sum);
    }

    public static List<ulong> changeStone(ulong stone)
    {
        if (stone == 0)
            return [1];

        var currentNumber = stone.ToString();
        if (currentNumber.Length % 2 == 0)
        {
            var left = currentNumber.Substring(0, currentNumber.Length / 2);
            var right = currentNumber.Substring(currentNumber.Length / 2);
            return [ulong.Parse(left), ulong.Parse(right)];
        }
        return [stone * 2024];
    }
}

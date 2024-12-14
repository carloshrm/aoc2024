namespace aoc2024;
using System.IO;
using System;
using System.Data;

public class Program
{
    static void Main(string[] args)
    {
        var input = File.ReadAllLines($@"{Directory.GetParent(Environment.CurrentDirectory).Parent.Parent.FullName}\inputs\Day7.txt");

        var results = new List<(ulong, IEnumerable<ulong>)>();
        foreach (var line in input)
        {
            var split = line.Split(':');

            ulong val = ulong.Parse(split.First());
            var nums = split.Last().Split(" ", StringSplitOptions.RemoveEmptyEntries).Select(num => ulong.Parse(num));
            results.Add((val, nums));
        }

        ulong result = 0;
        foreach (var (value, numbers) in results)
        {
            if (checkOp(value, numbers, 0, 0))
                result += value;
        }

        Console.WriteLine(result);
    }

    public static bool checkOp(ulong targetResult, IEnumerable<ulong> numbers, int currentIndex, ulong currentResult)
    {
        if (currentResult > targetResult)
            return false;

        if (currentIndex == numbers.Count())
            return (currentResult == targetResult);

        var sum = currentResult + numbers.ElementAt(currentIndex);
        var mult = currentResult * numbers.ElementAt(currentIndex);
        var cat = ulong.Parse(currentResult.ToString() + numbers.ElementAt(currentIndex));

        return checkOp(targetResult, numbers, currentIndex + 1, sum) 
            || checkOp(targetResult, numbers, currentIndex + 1, mult)
            || checkOp(targetResult, numbers, currentIndex + 1, cat);
    }
}
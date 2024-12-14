namespace aoc2024;
using System.IO;
using System;
using System.Numerics;
using System.Security.Cryptography.X509Certificates;
using System.Data;
using System.Runtime.CompilerServices;

public class Program
{
    public static readonly Vector2 up = new Vector2(0, -1);
    public static readonly Vector2 down = new Vector2(0, 1);
    public static readonly Vector2 left = new Vector2(-1, 0);
    public static readonly Vector2 right = new Vector2(1, 0);

    public enum Spots
    {
        Empty = 0,
        Wall = 1,
        Visited = -1,
    }

    public enum StepResult
    {
        End,
        OK,
        Loop,
    }

    static void Main(string[] args)
    {
        var input = File.ReadAllLines($@"{Directory.GetParent(Environment.CurrentDirectory).Parent.Parent.FullName}\inputs\Day6.txt");

        var startingPos = Vector2.Zero;
        Guard? guard = null;
        var board = new Spots[input.Length][];
        var map = new Dictionary<char, Spots>
        {
            {'.', Spots.Empty},
            {'#', Spots.Wall },
            {'X', Spots.Visited },
        };

        for (int i = 0; i < input.Length; i++)
        {
            board[i] = new Spots[input[i].Length];
            for (int j = 0; j < input[i].Length; j++)
            {
                if (input[i][j] == '^')
                {
                    startingPos = new Vector2(j, i);
                    guard = new(startingPos);
                }
                else
                    board[i][j] = map[input[i][j]];
            }
        }

        while (guard.step(board) != StepResult.End)
        {
            //
        }

        Console.WriteLine(board.Sum((l) => l.Sum(s => s == Spots.Visited ? 1 : 0)));

        var obstaclePositions = new List<(int, int)>();
        for (int i = 0; i < board.Length; i++)
        {
            for (int j = 0; j < board[i].Length; j++)
            {
                if (board[i][j] == Spots.Visited)
                    obstaclePositions.Add((i, j));
            }
        }

        int loops = 0;

        foreach (var (i, j) in obstaclePositions)
        {
            var tempGuard = new Guard(startingPos);
            var tempBoard = board.Select(l => l.ToArray()).ToArray();
            tempBoard[i][j] = Spots.Wall;

            StepResult guardStep = StepResult.OK;
            do
            {
                guardStep = tempGuard.step(tempBoard);
                if (guardStep == StepResult.Loop)
                {
                    loops++;
                    break;
                }
            }
            while (guardStep != StepResult.End);
        }

        Console.WriteLine(loops);
    }

    static bool outOfBounds(Vector2 pos, Spots[][] board)
    {
        return (pos.X < 0 || pos.Y < 0 || pos.X >= board.First().Length || pos.Y >= board.Length);
    }

    public class Guard
    {
        public Vector2 pos { get; set; }
        public Vector2 dir { get; set; }
        public HashSet<(Vector2, Vector2)> visitedTurns = [];

        public Guard(Vector2 pos)
        {
            this.pos = pos;
            dir = up;
        }

        public StepResult step(Spots[][] board)
        {
            Vector2 nextStep = pos + dir;

            if (outOfBounds(nextStep, board))
            {
                board[(int)pos.Y][(int)pos.X] = Spots.Visited;
                return StepResult.End;
            }


            if (board[(int)nextStep.Y][(int)nextStep.X] == Spots.Wall)
            {
                if (visitedTurns.Contains((pos, dir)))
                    return StepResult.Loop;
                else
                    visitedTurns.Add((pos, dir));

                dir = nextDir();
            }
            else
            {
                board[(int)pos.Y][(int)pos.X] = Spots.Visited;
                pos = nextStep;
            }

            return StepResult.OK;
        }

        private Vector2 nextDir()
        {
            if (dir == up)
                return right;
            else if (dir == right)
                return down;
            else if (dir == down)
                return left;
            else
                return up;
        }
    }
}





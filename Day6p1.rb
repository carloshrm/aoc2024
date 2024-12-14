require 'debug'

Vector2 = Struct.new(:x, :y)
$up = Vector2.new(0, -1)
$down = Vector2.new(0, 1)
$left = Vector2.new(-1, 0)
$right = Vector2.new(1, 0)

$loops = 0

$SPOTS = {
    VISITED: -1,
    WALL: 1,
    EMPTY: nil
}

class Guard
    attr_accessor :pos, :dir, :visited_turns

    def initialize(pos, dir)
        @pos = pos
        @dir = dir
        @visited_turns = {}
    end

    def step(board)
        next_step = Vector2.new(@pos.x + @dir.x, @pos.y + @dir.y)

        if next_step.x < 0 || next_step.x >= board[0].length || next_step.y < 0 || next_step.y >= board.length
            return false
        end
        
        if board[next_step.y][next_step.x] == $SPOTS[:WALL]
            visited_turns[@pos] = @dir

            [-1, 0, 1].each do |i|
                [-1, 0, 1].each do |j|
                    if board[@pos.y + j][@pos.x + i] == $SPOTS[:EMPTY] || board[@pos.y + j][@pos.x + i] == $SPOTS[:VISITED]
                        loops += 1 if checkLoop(board, Vector2.new(@pos.x + i, @pos.y + j))
                    end
                end
            end

            @dir = nextDir(@dir)
        else
            board[@pos.y][@pos.x] = $SPOTS[:VISITED]
            @pos = next_step
            board[@pos.y][@pos.x] = self
        end
        
        return true
    end

    def checkLoop(board, obstr_pos)
        temp_guard = Guard.new(@pos, @dir)
        
        temp_board = Marshal.load(Marshal.dump(board))
        temp_board[obstr_pos.y][obstr_pos.x] = 1
        while temp_guard.step(temp_board)
            if temp_guard.visited_turns[temp_guard.pos] == temp_guard.dir
                return true
            end
        end

        return false
    end
end


def nextDir(dir)
    if dir == $up
        return $right
    elsif dir == $right
        return $down
    elsif dir == $down
        return $left
    else
        return $up
    end
end

def readInput(day)
    input = []
    guard = nil

    file = File.new("./inputs/Day#{day}.txt", "r")
    while (line = file.gets)
        parsed_line = []
        line.each_char do |char|
            if char == '^'
                guard = Guard.new(Vector2.new(parsed_line.length, input.length), Vector2.new(0, -1))
                parsed_line.push(guard)
            elsif char == '#'
                parsed_line.push($SPOTS[:WALL])
            else
                parsed_line.push($SPOTS[:EMPTY])
            end
        end
        
        input.push(parsed_line)
    end
    file.close

    return {input: input, guard: guard}
end

def main()
    input, guard = readInput(6).values_at(:input, :guard)

    while guard.step(input)
    end

    spots = input.flatten.count($SPOTS[:VISITED])
    puts "Spots visited: #{spots + 1}"
    puts guard.visited_turns.length
    puts $loops
end

main()
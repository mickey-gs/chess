require_relative "stockfish.rb"

engine = Stockfish::Engine::new
position = ARGV.join(" ")
output = engine.analyze position, { :depth => 10 }
output = output.split("\n")
best_move = output[-1].split(" ")[1]
score = output.filter { |line| line.include?("score") || line.include?("mate") }

puts "here it is: " + position

if best_move == "(none)" 
    if score[score[0].index("score")+6] == "0"
        File.open("bestmove.txt", "w").write("stalemate")
    else
        File.open("bestmove.txt", "w").write("checkmate")
    end
else 
    File.open("bestmove.txt", "w").write(best_move)
end
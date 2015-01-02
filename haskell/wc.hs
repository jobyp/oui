-- wc -l

main = interact word_count
  where
    word_count input = show (length (lines input)) ++ "\n"

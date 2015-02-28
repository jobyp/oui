import CommonWords (common_words)

cwords :: Int -> FilePath -> FilePath -> IO ()
cwords n in_f out_f = do
  text <- readFile in_f
  writeFile out_f (common_words n text)
  putStrLn "cwords done!"


main :: IO ()
main = do
  putStrLn "Take text from: "
  infile <- getLine
  putStrLn "How many words? "
  n <- getLine
  putStrLn "Write results to: "
  outfile <- getLine
  cwords (read n) infile outfile


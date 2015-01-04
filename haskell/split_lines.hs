import System.Environment (getArgs)

interact_with :: (String -> String) -> FilePath -> FilePath -> IO ()
interact_with function in_file out_file = do
  input <- readFile in_file
  writeFile out_file (function input)
  

split_lines :: String -> [String]
split_lines [] = []
split_lines cs = 
  let (pre, suf) = break is_line_terminator cs
  in pre : 
     case suf of
       ('\r' : '\n' : rest) -> split_lines rest
       ('\r' : rest) -> split_lines rest
       ('\n' : rest) -> split_lines rest
       _  -> []

is_line_terminator :: Char -> Bool
is_line_terminator c = c == '\r' || c == '\n'

fix_lines :: String -> String
fix_lines input = unlines (split_lines input)


main :: IO ()
main = main_with my_function
  where
    main_with function = do
      args <- getArgs
      case args of 
        [input, output] -> interact_with function input output
        _ -> putStrLn "error: exactly two arguments needed"
    my_function = fix_lines

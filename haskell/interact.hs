import System.Environment (getArgs)

main :: IO ()
main = main_with my_function
  where
    main_with function = do
      args <- getArgs
      case args of 
        [input, output] -> interact_with function input output
        _ -> putStrLn "error: exactly two arguments needed"
    my_function = id


interact_with :: (String -> String) -> FilePath -> FilePath -> IO ()
interact_with function in_file out_file = do
  input <- readFile in_file
  writeFile out_file (function input)
  

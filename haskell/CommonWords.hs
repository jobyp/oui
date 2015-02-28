module CommonWords (common_words) where
import Data.Char (toLower)
import Data.List (sort, sortBy)

-- Trying with ghc --make

common_words :: Int -> String -> String
common_words n = concat . map showRun . take n . 
                 sortRuns . countRuns. sortWords .
                 words . map toLower

showRun :: (Int, String) -> String
showRun (n, s) = "\t" ++ s ++ ": " ++ show n ++ "\n"

sortRuns :: [(Int, String)] -> [(Int, String)]
sortRuns = sortBy cmp
           where cmp (n, _) (m, _) = compare m n
                                     
countRuns :: [String] -> [(Int, String)]
countRuns [] = []
countRuns (w:ws) =
  (n, w) : countRuns ws'
  where (ns, ws') = break (\x -> x /= w) ws
        n = length ns + 1
        
sortWords :: [String] -> [String]
sortWords = sort


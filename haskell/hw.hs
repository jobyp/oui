import Data.Char
import Data.List

units, teens, tens :: [String]
units = ["zero", "one", "two", "three", "four", "five",
         "six", "seven", "eight", "nine"]
teens = ["ten", "eleven", "twelve", "thirteen", "fourteen",
         "fifteen", "sixteen", "seventeen", "eighteen",
         "nineteen"]
tens = ["twenty", "thirty", "fourty", "fifty", "sixty",
        "seventy", "eighty", "ninety"]

convert1 :: Int -> String
convert1 n | n >= 0 && n < 10 = units !! n
           | otherwise = ""

digits2 :: Int -> (Int, Int)
digits2 n = (n `div` 10, n `mod` 10)

combine2 :: (Int, Int) -> String
combine2 (t, u)
  | t == 0 = units !! u
  | t == 1 = teens !! u
  | 2 <= t && u == 0 = tens !! (t - 2)
  | 2 <= t && u /= 0 = tens !! (t - 2) ++ "-" ++ units !! u
  | otherwise = ""

convert2 :: Int -> String
convert2 = combine2 . digits2

convert3 :: Int -> String
convert3 n
  | h == 0 = convert2 t
  | t == 0 = units !! h ++ " hundred"
  | h > 0 && h < 10 = units !! h ++ " hundred and " ++ convert2 t
  | otherwise = ""  -- failure case
  where (h, t) = (n `div` 100, n `mod` 100)

convert6 :: Int -> String
convert6 n
  | m == 0 = convert3 h
  | h == 0 = convert3 m ++ " thousand"
  | m > 0 && m < 1000 = convert3 m ++ " thousand" ++ link h ++
                        convert3 h
  | otherwise = ""
  where (m, h) = (n `div` 1000, n `mod` 1000)
    
link :: Int -> String
link h = if h < 100 then " and " else " "

convert :: Int -> String
convert = convert6


type Word = String
type Label = String

-- anagrams :: Int -> [String] -> String


getWords :: Int -> [Word] -> [Word]
getWords n = filter (\s -> length s == n)

addLabel :: [Word] -> [(Label, Word)]
addLabel = map (\w -> (sort w, w))

sortByLabel :: [(Label, Word)] -> [(Label, Word)]
sortByLabel = sortBy (\x y -> compare (fst x) (fst y))

groupByLabel :: [(Label, Word)] -> [(Label, [Word])]
groupByLabel [] = []
groupByLabel (l:ls) =
  let label = fst l
      (ls', ls'') = break (\l -> (fst l) == label) ls
      words = (snd l) : map snd ls'
  in (label, words) : groupByLabel ls''

showEntry :: (Label, [Word]) -> String
showEntry (label, words) = label ++ ": " ++
                           foldr (\w rest -> w ++ " " ++ rest) "\n" words

showItems :: [(Label, [Word])] -> String
showItems = concat . map showEntry

anagrams :: Int -> [Word] -> String
anagrams n = showItems . groupByLabel . sortByLabel . addLabel . getWords n



upcase :: Word -> Word
upcase [] = []
upcase (x:xs) = toUpper x : xs



line1 :: Int -> String
line1 n = (if n == 1
           then "One man"
           else (upcase (units !! n) ++ " men"))
          ++ " went to mow\n"

line2 :: String
line2 = "Went to mow a meadow\n"

line3 :: Int -> String
line3 n = if n == 1
          then "One man and this dog\n"
          else (upcase (units !! n) ++ " men, ") ++ map toLower (line3 (n - 1))

line4 :: String
line4 = line2

verse n = line1 n ++ line2 ++ line3 n ++ line4

song :: Int -> String
song n = if n == 0 then ""
         else song (n - 1) ++ "\n" ++ verse n

factorial :: Integer -> Integer
factorial n = fact (n, 1)

fact :: (Integer, Integer) -> Integer
fact (n, p) = if n <= 0 then p
              else fact $! (n - 1, n * p)
                   

p_take :: Int -> [a] -> [a]
p_take _ [] = []
p_take n (x : xs)
  | n <= 0 = []
  | otherwise = x : (p_take $! (n - 1)) xs
                


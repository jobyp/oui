let sort l =
  let rec insert n l = 
    match l with
    | [] -> [n]
    | h :: t -> 
      if n > h 
      then h :: (insert n t)
      else n :: l
  in
  let rec sort_aux l =
    match l with
    | [] -> []
    | h :: t -> insert h (sort_aux t)
  in
  sort_aux l
      
let rec take n l = 
  if n <= 0
  then []
  else 
    match l with
    | [] -> []
    | h :: t -> h :: take (n - 1) t

let rec drop n l = 
  if n <= 0
  then l
  else 
    match l with
    | [] -> []
    | _ :: t -> drop (n - 1) t

let rec merge x y = 
  match x, y with
  | [], [] -> []
  | [], l -> l
  | l, [] -> l
  | (hx :: tx), (hy :: ty) ->
    if hx <= hy
    then hx :: merge tx (hy :: ty)
    else hy :: merge (hx :: tx) ty

let rec msort l =
  match l with
  | [] -> []
  | [x] -> [x]
  | _ ->
    let mid = List.length l / 2 in
    let left = take mid l in
    let right = drop mid l in
    merge (msort left) (msort right)

let rec detect l = 
  match l with
  | [] -> true
  | [x] -> true
  | h :: x :: t ->
    if h <= x
    then detect (x :: t)
    else false

let halve x = x / 2

let is_even n = 
  (n mod 2) = 0

let evens l = List.map is_even l

let range n = (* ->  [0; 1; ... ] *)
  let rec range_aux m l = 
    if m = 0 
    then 0 :: l
    else range_aux (m - 1) (m :: l) 
  in
  if n <= 0
  then []
  else range_aux (n - 1) []


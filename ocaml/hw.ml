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

let rec merge cmp x y = 
  match x, y with
  | [], [] -> []
  | [], l -> l
  | l, [] -> l
  | (hx :: tx), (hy :: ty) ->
    if cmp hx hy
    then hx :: merge cmp tx (hy :: ty)
    else hy :: merge cmp (hx :: tx) ty

let rec msort cmp l =
  match l with
  | [] -> []
  | [x] -> [x]
  | _ ->
    let mid = List.length l / 2 in
    let left = take mid l in
    let right = drop mid l in
    merge cmp (msort cmp left) (msort cmp right)

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

let calm = List.map (fun c -> if c = '!' then '.' else c)

let clip n = 
  if n < 1
  then 1
  else if n > 10
  then 10 
  else n

let cliplist = List.map clip

let rec apply f n x = 
  if n <= 0
  then x
  else apply f (n - 1) (f x)

let filter f = List.fold_right (fun x l -> if f x then x :: l else l) []

let for_all f = List.fold_left (fun b x -> (f x) && b) true

let mapl f = List.map (List.map f)


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

let rec last l =
  match l with
  | [] -> raise Not_found
  | [x] -> x
  | h :: t -> last t

let is_nil l =
  match l with
  | [] -> true
  | _ -> false


let smallest l =
  let rec smaller n l =
    match l with
    | [] -> n
    | h :: t -> 
       if n < h 
       then smaller n t 
       else smaller h t
  in
  if for_all (fun n -> n < 0) l
  then raise Not_found
  else match l with
       | [] -> raise Not_found
       | h :: t -> smaller h t


let smallest_or_zero l =
  try smallest l with
  | Not_found -> 0

let fst (x, _) = x
let snd (_, y) = y

let rec lookup x l = 
  match l with
  | [] -> raise Not_found
  | (k, v) :: t ->
     if k = x then v else lookup x t

let rec add k v d = 
  match d with
  | [] -> [(k, v)]
  | (k', v') :: t ->
     if k' = k 
     then (k, v) :: t 
     else (k', v') :: add k v t

let rec remove k d =
  match d with
  | [] -> []
  | (k', v') :: t -> 
     if k' = k 
     then t 
     else (k', v') :: remove k t

let key_exists k d =
  try 
    let _ = lookup k d 
    in true
  with Not_found -> false


let rec replace k v d = 
  match d with
  | [] -> raise Not_found
  | (k', v') :: t ->
     if k = k' 
     then (k, v) :: t
     else (k', v') :: replace k v t

let rec build_dict x y = 
  match x, y with
  | [], [] -> []
  | (_::_), [] -> raise (Invalid_argument "length x <> length y")
  | [], (_::_) -> raise (Invalid_argument "length x <> length y")
  | (hx :: tx), (hy :: ty) -> add hx hy (build_dict tx ty)


let rec dict_to_pairs d = 
  match d with
  | [] -> ([], [])
  | (k, v) :: t -> 
     let (tx, ty) = dict_to_pairs t
     in (k :: tx, v :: ty)

let rec pairs_to_dict d = 
  match d with
  | [] -> []
  | (x, y) :: t -> add x y (pairs_to_dict t)

let rec union x y = 
  match x with
  | [] -> y
  | (k, v) :: t -> add k v (union t y)

let rec member x l =
  match l with
  | [] -> false
  | h :: t -> x = h || member x t

let rec member_all x ls = 
  match ls with
  | [] -> false
  | l :: t -> member x l && member_all x t

let truncate n ls = List.map (take n) ls

let list_heads n = List.map (fun l -> if is_nil l then n else List.hd l)

type color = 
| Red 
| Green 
| Blue 
| Yellow
| RGB of int * int * int

let components c = 
  match c with
  | Red -> (255, 0, 0)
  | Green -> (0, 255, 0)
  | Blue -> (0, 0, 255)
  | Yellow -> (255, 255, 0)
  | RGB (r, g, b) -> (r, g, b)

type 'a option =
| None
| Some of 'a


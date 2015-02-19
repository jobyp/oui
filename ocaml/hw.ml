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

type ('a , 'b) pair =
  | P of 'a 
  | Q of 'b

type 'a sequence = 
  | Nil 
  | Cons of 'a * 'a sequence

let rec seq_fold_l f default s = 
  match s with
  | Nil -> default
  | Cons (h, t) -> seq_fold_l f (f default h) t
    
let length_s = seq_fold_l (fun n _ -> 1 + n) 0

let list_to_seq l = List.fold_right (fun h s -> Cons (h, s)) l Nil

type expr = 
  | Num of int
  | Add of expr * expr
  | Sub of expr * expr
  | Mul of expr * expr
  | Div of expr * expr

		    
let m_return n = Some n

let m_bind m g =
  match m with
  | None -> None
  | Some n -> g n
		
let rec evaluate e =
  match e with
  | Num n -> m_return n

  | Add (e1, e2) -> 
     let m_add e = 
       fun x -> m_bind (evaluate e) (fun y -> m_return (x + y))
     in m_bind (evaluate e1) (m_add e2)

  | Sub (e1, e2) -> 
     let m_sub e = 
       fun x -> m_bind (evaluate e) (fun y -> m_return (x - y))
     in m_bind (evaluate e1) (m_sub e2)
	       
  | Mul (e1, e2) -> 
     let m_mul e = 
       fun x -> m_bind (evaluate e) (fun y -> m_return (x * y))
     in m_bind (evaluate e1) (m_mul e2)

  | Div (e1, e2) -> 
     let m_div e = 
       fun x -> m_bind (evaluate e) (fun y -> 
				     if y = 0 
				     then None 
				     else m_return (x / y))
     in m_bind (evaluate e1) (m_div e2)


(* Key ideas from arithmetic expression interpreter 'evaluate'*)
     (* (1) Monad   *)
     (* (2) lazy evaluation with the help of partial functions *)

(* Laws of Monad *)
(* Every 'return' and 'bind' should obey following rules*)
(*     m >>= return     =  m                        -- right unit *)
(*     return x >>= f   =  f x                      -- left unit *)
 
(*     (m >>= f) >>= g  =  m >>= (\x -> f x >>= g)  -- associativity*)

type 'a btree = 
| BLf
| BNode of 'a * 'a btree * 'a btree

(*The empty tree is BLf *)

let rec size tr = 
  match tr with
  | BLf -> 0
  | BNode (_, l, r) -> 1 + size l + size r

let rec total tr =
  match tr with
  | BLf -> 0
  | BNode (n, l, r) -> n + total l + total r


let rec max_depth tr = 
  match tr with
  | BLf -> 0
  | BNode (_, l, r) -> 1 + max (max_depth l) (max_depth r)


let rec list_of_tree tr = 
  match tr with
  | BLf -> []
  | BNode (x, l, r) -> (list_of_tree l) @ [x] @ (list_of_tree r)


let rec tree_map f tr = 
  match tr with
  | BLf -> BLf
  | BNode (x, l, r) -> BNode (f x, tree_map f l, tree_map f r)


let rec lookup tr k = 
  match tr with
  | BLf -> None
  | BNode ((k', v'), l, r) -> 
    if k = k' then Some v'
    else if k < k' then lookup l k 
    else lookup r k


let rec insert tr k v = 
  match tr with
  | BLf -> BNode ((k, v), BLf, BLf)
  | BNode ((k', v'), l, r) ->
    if k = k' then BNode ((k, v), l, r)
    else if k < k' then BNode ((k', v'), insert l k v, r)
    else BNode ((k', v'), l, insert r k v)


let rec member x tr = 
  match tr with
  | BLf -> false
  | BNode (y, l, r) -> x = y || member x l || member x r


let rec flip_tree tr =
  match tr with
  | BLf -> BLf
  | BNode (x, l, r) -> BNode (x, flip_tree r, flip_tree l)


let rec same_shape p q = 
  match p, q with
  | BLf, BLf -> true
  | BLf, _ -> false
  | _, BLf -> false
  | BNode (_, lp, rp), BNode (_, lq, rq) ->
    same_shape lp lq && same_shape rp rq

let tree_of_list l = 
  let f d (k, v) = insert d k v in
  List.fold_left f BLf l

let rec combine_trees p q = 
  match p with
  | BLf -> q
  | BNode ((k, v), l, r) -> 
    combine_trees l 
      (combine_trees r 
	 (insert q k v))

type 'a tree = 
| Lf
| Nodes of 'a * 'a tree list

let rec size tr = 
  match tr with
  | Lf -> 0
  | Nodes (_, l) -> List.fold_left (+) 1 (List.map size l)

let rec total tr = 
  match tr with
  | Lf -> 0
  | Nodes (n, l) -> List.fold_left (+) n (List.map total l)


let rec tr_map f tr = 
  match tr with
  | Lf -> Lf
  | Nodes (n, l) -> Nodes (f n, List.map (tr_map f) l)


let print_dict_entry (k, v) =
  print_char '(' ; 
  print_int k ; 
  print_string ", "; 
  print_string v; 
  print_char ')'; 
  print_newline ()

let rec iter f l = 
  match l with
  | [] -> ()
  | h :: t -> f h ; iter f t

let print_dict  = iter print_dict_entry


let () = Printf.printf "Hello, World\n" 



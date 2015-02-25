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
    
let length_s s = seq_fold_l (fun n _ -> 1 + n) 0 s

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
  print_int k; print_newline ();
  print_string v; print_newline ()

let rec iter f l = 
  match l with
  | [] -> ()
  | h :: t -> f h; iter f t

let print_dict d = iter print_dict_entry d

let rec read_dict_entry () =
  try
    let n = read_int () in
    let s = read_line () in
    (n, s)
  with Failure "int_of_string" -> 
    print_string "This is not a valid integer. Please try again.";
    print_newline () ;
    read_dict_entry ()

let rec read_dict () =
  try 
    let e = read_dict_entry () in
    e :: read_dict ()
  with End_of_file -> []

let entry_to_channel ch (k, v) =
  output_string ch (string_of_int k); output_char ch '\n';
  output_string ch v; output_char ch '\n'

let dict_to_channel ch d = iter (entry_to_channel ch) d

let dict_to_file filename d = 
  let ch = open_out filename in
  dict_to_channel ch d;
  close_out ch

let entry_of_channel ch = 
  let n = input_line ch in
  let v = input_line ch in
  (int_of_string n, v)

let rec dict_of_channel ch = 
  try
    let e = entry_of_channel ch in
    e :: dict_of_channel ch
  with 
    End_of_file -> []

let dict_of_file filename = 
  let ch = open_in filename in
  let d = dict_of_channel ch in
  close_in ch; d

(* Summary of I/O functions *)
(* ------------------------ *)
(* print_int *)
(* print_string *)
(* print_newline *)
(* read_line  *)
(* read_int *)
(* int_of_string *)
(* string_of_int *)
(* open_out *)
(* close_out *)
(* open_in *)
(* close_in *)
(* output_string *)
(* output_char  *)

let print_list l = 
  match l with
  | [] -> print_string "[]" ; print_newline ()
  | [x] -> print_string ("[" ^ string_of_int x ^ "]"); 
	   print_newline ()
  | h :: t ->
     let ts = List.map (fun n -> "; " ^ string_of_int n) t in
     let s = "[" ^ string_of_int h ^ List.fold_right (^) ts "]" in
     print_string s ; print_newline ()

let rec repeat n x = 
  if n <= 0 then [] else x :: repeat (n - 1) x

let rec upto n m = 
  if n > m then [] else n :: upto (n + 1) m

let table filename n = 
  let row l n = List.map (fun x -> x * n) l in
  let rows l = List.map (row l) l in
  let string_of_row l = 
    List.fold_right (^) (List.map (fun n -> string_of_int n ^ "\t") l) ""
  in
  let string_of_rows ll = 
    List.fold_right (^) (List.map (fun l -> string_of_row l ^ "\n") ll) ""
  in
  if n < 1
  then ()
  else
    let ch = open_out filename in
    let m_tbl = rows (upto 1 n) in
    let m_tbl_str = string_of_rows m_tbl in
    output_string ch m_tbl_str;
    close_out ch

let rec read_num () =
  try read_int () with
  | Failure "int_of_string" ->
     print_string "Integer expected. Please try again.";
     print_newline ();
     read_num ()

let read_tuple_of_3 () =
  try (read_num (), read_num (), read_num ()) with
  | End_of_file ->
     failwith "Failed to read 3 integers."

let rec read_lines_of_channel ch = 
  try
    let line = input_line ch in
    line :: read_lines_of_channel ch
  with
    End_of_file -> []

let num_lines_of_file filename = 
  let ch = open_in filename in
  let lines = read_lines_of_channel ch in
  close_in ch;
  List.fold_left (+) 0 (List.map (fun _ -> 1) lines)

let swap a b = 
  let t = !a in
  a := !b ; b := t

let print_hello () =
  for i = 1 to 5
  do
    print_string "Hello...";
    print_newline () 
  done
    
let smallest_pow2 x = 
  let t = ref 1 in
  while !t < x
  do
    t := !t * 2
  done;
  !t

let print_histogram arr = 
  print_string "Character frequencies:";
  print_newline ();
  for x = 0 to 255 do
    if arr.(x) > 0 then
      begin
	print_string "For character '"; 
	print_char (char_of_int x);
	print_string "' (ascii ";
	print_int x;
	print_string ") the count is ";
	print_int arr.(x);
	print_string ".";
	print_newline ()
      end
  done

let channel_statistics ch = 
  let lines = ref 0 in
  let characters = ref 0 in
  let words = ref 0 in
  let sentences = ref 0 in
  let histogram = Array.make 256 0 in
  try
    while true 
    do
      let line = input_line ch in
      lines := !lines + 1;
      characters := !characters + String.length line ;
      String.iter (fun c ->
		   match c with
		   | '.' | '?' | '!' -> sentences := !sentences + 1
		   | ' ' -> words := !words + 1
		   | _ -> ()) 
		  line;
      String.iter (fun c ->
		   let i = int_of_char c in
		   histogram.(i) <- histogram.(i) + 1)
		  line
    done
  with
  | End_of_file ->
     print_string "There were "; 
     print_int !lines; 
     print_string " lines, making up ";
     print_int !characters;
     print_string " characters with ";
     print_int !words;
     print_string " words in ";
     print_int !sentences;
     print_string " sentences.";
     print_newline ();
     print_histogram histogram

let file_statistics filename = 
  let ch = open_in filename in
  channel_statistics ch;
  close_in ch

let make_vector (x0, y0) (x1, y1) =
  (x1 -. x0, y1 -. y0)

let vector_length (x, y) = 
  sqrt (x *. x +. y *. y)

let offset_point (x, y) (px, py) =
  (x +. px, y +. py)		 

let scale_to_length l (a, b) =
  let current_length = vector_length (a, b) in
  if current_length = 0. then (a, b) else
    let factor = l /. current_length in
    (a *. factor, b *. factor)

let round f = 
  floor (f +. 0.5)

let mid_point (x0, y0) (x1, y1) = 
  ((x0 +. x1) /. 2., (y0 +. y1) /. 2.)

let split_float f = 
  let p = floor f in
  (p, f -. p)

let star f =
  if f < 0. || f > 1. 
  then (print_string "invalid number"; print_newline ())
  else
    let m = 50. *. f in
    let i = int_of_float (fst (split_float m)) in
    let j = if i = 50 then 49 else i in
    let s1 = String.make 50 ' ' in
    let s2 = String.mapi (fun k c -> if k = j then '*' else c) s1 in
    print_string s2; print_newline ()

let pi = asin 1. *. 2. 

let rec f_range fn b e step = 
  if b > e
  then []
  else fn b :: f_range fn (b +. step) e step

let rec plot fn b e step = 
  let fs = f_range fn b e step in
  List.iter star fs

let s_concat ls = 
  let buf = Buffer.create 0 in
  List.iter (fun s -> Buffer.add_string buf s) ls;
  Buffer.contents buf

let string_to_list s =
  let indices = range (String.length s) in
  List.map (fun i -> s.[i]) indices

let string_of_list l = 
  let buf = Buffer.create 0 in
  List.iter (fun c -> Buffer.add_char buf c) l;
  Buffer.contents buf

let rec startswith x y = 
  match x, y with
  | [], [] -> true
  | _::_, [] -> false
  | [], _::_ -> true
  | hx::tx, hy::ty -> hx = hy && startswith tx ty

let rec substring x y =
  match y with
  | [] -> [startswith x y]
  | _ :: t -> startswith x y :: substring x t

let count_s x y = 
  let l_x = string_to_list x in
  let l_y = string_to_list y in
  let ll = substring l_x l_y in
  List.fold_left (fun n b -> n + (if b then 1 else 0)) 0 ll

(* A tutorial on the universality and expressiveness *)
(* of fold - Graham Hutton *)

let rec foldr f v ls = 
  match ls with
  | [] -> v
  | h :: t -> f h (foldr f v t)

let sum = foldr (+) 0
let all = foldr (&&) true

let append xs ys = foldr (fun h t -> h :: t) ys xs

let length ls = foldr (fun _ n -> 1 + n) 0 ls

let rev ls = foldr (fun h t -> append t [h]) [] ls

let map f xs = foldr (fun h t -> f h :: t) [] xs

let filter f ls = foldr (fun h t -> if f h then h :: t else t) [] ls

let sumlength xs = (sum xs, length xs)

let sumlength' xs = foldr (fun n (x, y) -> (n + x, y + 1)) (0, 0) xs

let rec drop_while f xs = 
  match xs with
  | [] -> []
  | h :: t -> if f h then drop_while f t else h :: t


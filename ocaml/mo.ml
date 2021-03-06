(* Programs from More OCaml *)

(* Unravelling fold *)

let rec fold_left f v l =
  match l with
  | [] -> v
  | h :: t -> fold_left f (f v h) t

let rec fold_right f l v = 
  match l with
  | [] -> v
  | h :: t -> f h (fold_right f t v)


let max_l l = 
  let fn = fun x h ->
    match x with
    | None -> Some h
    | Some x' -> Some (max x' h)
  in
  fold_left fn None l

let all l = fold_left (&&) true l
let any l = fold_left (||) false l

let length l = fold_left (fun n _ -> n + 1) 0 l

let setify l = 
  fold_left (fun xs h -> if List.mem h xs then xs else h :: xs) [] l

let map f l = fold_right (fun h xs -> f h :: xs) l []

(* let fold_right f l e =  *)
(*   fold_left (fun xs h -> f h xs) e (List.rev l) *)

let split l = 
  fold_right 
    (fun (x, y) (xs, ys) -> (x :: xs, y :: ys)) l ([], [])


let concat lls = fold_right (@) lls [] 
(* let concat' lls = fold_left (@) [] lls   --- this is a bad definition --- *)

let last l = fold_left (fun _ h -> Some h) None l

let list_mem x l = 
  fold_left (fun v h -> v || x = h) false l
(* list_mem is less efficient that List.mem since there is no early exit *)

let rev l = fold_left (fun xs h -> h :: xs) [] l

let str_join l = 
  fold_right (fun s v -> s ^ " " ^ v) l ""


type 'a tree = 
| Lf
| Br of 'a * 'a tree * 'a tree
  

let rec fold_tree f e t = 
  match t with
  | Lf -> e
  | Br (x, l, r) -> f x (fold_tree f e l) (fold_tree f e r)


let tree_size t = fold_tree (fun _ n m -> 1 + n + m) 0 t

let tree_sum t  = fold_tree (fun x n m -> x + n + m) 0 t

let tree_preorder t = fold_tree (fun x l r -> [x] @ l @ r) [] t
let tree_inorder t = fold_tree (fun x l r -> l @ [x] @ r) [] t
let tree_postorder t = fold_tree (fun x l r -> l @ r @ [x]) [] t

let tree_max_depth t = fold_tree (fun _ n m -> 1 + max n m) 0 t

(* Being Lazy *)

let rec repeat c n =
  if n <= 0 then [] else c :: repeat c (n - 1)

let range n = 
  let rec upto n m = 
    if n < m then n :: upto (n + 1) m else []
  in
  upto 0 n

type 'a lazylist =
  Cons of 'a * (unit -> 'a lazylist)

let rec lseq n = 
  Cons (n, fun () -> lseq (n + 1))

let lhd (Cons (n, _)) = n
let ltl (Cons (_, tf)) = tf ()

let rec ltake (Cons (h, tf)) n =
  if n <= 0 
  then [] 
  else 
    h :: ltake (tf ()) (n - 1)

let rec ldrop (Cons (h, tf) as ll) n = 
  if n <= 0
  then ll
  else ldrop (tf ()) (n - 1)

let rec lmap f (Cons (h, tf)) =
  Cons (f h, fun () -> lmap f (tf ()))

let rec lfilter f (Cons (h, tf)) =
  if f h
  then Cons (h, fun () -> lfilter f (tf ()))
  else lfilter f (tf ())

let cubes =
  lfilter (fun n -> n mod 5 = 0)
	  (lmap (fun n -> n * n * n)
		(lseq 1))

let rec mkprimes (Cons (h, tf)) =
  Cons (h, fun () ->
	   mkprimes 
	     (lfilter 
		(fun x -> x mod h <> 0) 
		(tf ())))

let primes = mkprimes (lseq 2)

let rec interleave (Cons (h, tf)) l =
  Cons (h, fun () -> interleave l (tf ()))

let rec lconst n =
  Cons (n, fun () -> lconst n)

let rec allfrom l = 
  Cons (l, fun () ->
	   interleave (allfrom (0 :: l)) (allfrom (1 :: l)))

let allones = allfrom []

let rec lpow_2 n = 
  Cons (n, fun () -> lpow_2 (2 * n))

let rec lnth (Cons (h, tf)) n = 
  if n <= 0
  then h
  else lnth (tf ()) (n - 1)


let cycle lst = 
  let rec cycle_aux l = 
    match l with
    | [] -> cycle_aux lst
    | h :: t ->
      Cons (h, fun () -> cycle_aux t)
  in
  match lst with
  | [] -> failwith "Empty list"
  | _ -> cycle_aux lst


let lfibs = 
  let rec lfib_aux a b =
    Cons (a, fun () -> lfib_aux b (a + b))
  in lfib_aux 0 1


(* Named Tuples with Records *)

type 'a point = {
  x : float;
  y : float;
  label : string;
  mutable content : 'a
}
 

let make_point x y label content = {x; y; label; content;}

let string_of_point {label; x; y; _} =
  label 
  ^ " = ("
  ^ string_of_float x
  ^ ", "
  ^ string_of_float y
  ^ ")"

let relabel p l = {p with label = l}

let mirror p = {p with x = p.y; y = p.x}

open Unix

let day_of_tm tm = 
  match tm.tm_wday with
  | 0 -> "Sunday"
  | 1 -> "Monday"
  | 2 -> "Tuesday"
  | 3 -> "Wednesday"
  | 4 -> "Thursday"
  | 5 -> "Friday"
  | 6 -> "Saturday"
  | _ -> failwith "Invalid day"


let month_of_tm tm = 
  match tm.tm_mon with
  | 0 -> "January"
  | 1 -> "February"
  | 2 -> "March"
  | 3 -> "April"
  | 4 -> "May"
  | 5 -> "June"
  | 6 -> "July"
  | 7 -> "August"
  | 8 -> "September"
  | 9 -> "October"
  | 10 -> "November"
  | 11 -> "December"
  | _ -> failwith "Invalid month"


let time_str () =
  let tm = Unix.localtime (Unix.gettimeofday ()) in
  let day = day_of_tm tm in
  let month = month_of_tm tm in
  "It is "
  ^ string_of_int (tm.tm_hour)
  ^ ":"
  ^ string_of_int (tm.tm_min)
  ^ " on " 
  ^ day
  ^ " "
  ^ string_of_int (tm.tm_mday)
  ^ " "
  ^ month
  ^ " "
  ^ string_of_int (tm.tm_year + 1900)

type ('a,  'b,  'c) six_items = 
  {
    a : 'a;
    b : 'a;
    c : 'b;
    d : 'b;
    e : 'c;
    f : 'c
  }


(* Generalized Input/Output *)


type input = {
  pos_in : unit -> int;
  seek_in : int -> unit;
  input_char : unit -> char;
  in_channel_length : int;
}

let input_of_channel ch = 
  {
    pos_in = (fun () -> pos_in ch);
    seek_in = seek_in ch;
    input_char = (fun () -> input_char ch);
    in_channel_length = in_channel_length ch;
  }


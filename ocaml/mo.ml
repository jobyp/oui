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

let rec ltake l n =
  if n <= 0 
  then [] 
  else 
    let h = lhd l in
    let tl = ltl l in
    h :: ltake tl (n - 1)

let rec ldrop l n = 
  if n <= 0
  then l
  else ldrop (ltl l) (n - 1)



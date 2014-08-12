open Core.Std

type point2d = { 
    x : float ; 
    y : float 
  }

type circle_desc = { 
    center : point2d ; 
    radius : float 
  }

type rect_desc = { 
    lower_left : point2d; 
    width : float ; 
    height : float 
  }

type segment_desc = { 
    end_point1 : point2d; 
    end_point2 : point2d 
  }

type scene_element = 
  | Circle of circle_desc
  | Rect of rect_desc
  | Segment of segment_desc

let magnitude { x ; y } =
  sqrt ( x ** 2. +. y ** 2. )

let distance p1 p2 = 
  magnitude { x = (p1.x -. p2.x) ; y  = (p1.y -. p2.y) }

let is_inside_scene_element point scene_element = 
  match scene_element with
  | Circle { center ; radius } -> 
     distance center point < radius
  | Rect { lower_left ; width ; height } ->
     (point.x -. lower_left.x)     < width 
     && (point.y -.  lower_left.y) < height
  | Segment _ -> false
       
let is_inside_scene point scene = 
  List.exists scene ~f:(fun el -> is_inside_scene_element point el)

type running_sum = {
    mutable sum : float;
    mutable sum_sq : float;
    mutable samples : int
  }

let create () = { sum = 0. ; sum_sq = 0. ; samples = 0 }

let update rsum x = 
  rsum.samples <- rsum.samples + 1;
  rsum.sum <- rsum.sum +. x;
  rsum.sum_sq <- rsum.sum +. (x *. x)

let permute array =
  let length = Array.length array in 
  for i = 0 to length - 1 
  do
    let j = i + Random.int (length - i) in
    let tmp = array.(i) in
    array.(i) <- array.(j);
    array.(j) <- tmp
  done

let find_first_negative_entry nums =
  let i = ref 0 in
  while !i < Array.length nums && nums.(!i) >= 0
  do
    i := !i + 1
  done;
  if !i = Array.length nums then None else Some !i

let rec read_and_accumulate accum =
  let line = In_channel.input_line In_channel.stdin in
  match line with
  | Some x -> read_and_accumulate (accum +. Float.of_string x)
  | None -> accum

(* let () =  *)
(*   printf "Total: %F\n" (read_and_accumulate 0.) *)


let languages = "OCaml,Perl,C++,C"

let dashed_languages = 
  let language_list = String.split languages ~on:',' in
  String.concat language_list ~sep:"-"


let area_of_ring inner_radius outer_radius =
  let pi = acos(-1.) in
  let area_of_circle r = pi *. r *. r in
  area_of_circle outer_radius -. area_of_circle inner_radius

let enumerate list = 
  let zip = List.zip (List.range 0 (List.length list)) list in
  match zip with
  | Some z' -> z'
  | None -> []

let upcase_first_entry line = 
  match String.split line ~on:',' with
  | first :: rest -> String.concat ~sep:"," (String.uppercase first :: rest)
  | [] -> assert false (* String.split returns atleast one element *)

let rec find_first_stutter list = 
  match list with
  | x :: y :: tl -> 
     if x = y then Some x else find_first_stutter (y :: tl)
  | [_] 
  | [] -> None  (* Only zero or one elements, so no repeats *)

let rec is_even x = 
  if x = 0 then true else is_odd (x - 1)
and is_odd x =
  if x = 0 then false else is_even (x - 1)


let range n = (* ->  [0; 1; ... ] *)
  let rec range_aux m l = 
    if m = 0 
    then 0 :: l
    else range_aux (m - 1) (m :: l) 
  in
  if n <= 0
  then []
  else range_aux (n - 1) []

let string_to_list s =
  let indices = range (String.length s) in
  List.map (fun i -> s.[i]) indices

(* let string_of_list l =  *)
(*   let buf = Buffer.create 0 in *)
(*   List.iter (fun c -> Buffer.add_char buf c) l; *)
(*   Buffer.contents buf *)

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

let is_part_of_s x y = 
  let l_x = string_to_list x in
  let l_y = string_to_list y in
  let ll = substring l_x l_y in
  List.mem true ll

let rec print_lines_containing_str ch str = 
  try
    let line = input_line ch in
    if is_part_of_s str line
    then 
      begin
	print_string line;
	print_newline ();
      end
    else ();
    print_lines_containing_str ch str
  with
  | End_of_file -> ()

let () = 
  try 
    match Sys.argv with
    | [|_; file; str |] ->
       let ch = open_in file in
       print_lines_containing_str ch str;
       close_in ch
    | _ -> 
       print_string "usage: grml <filename>";
       print_newline ()
  with e ->
    print_string "An erro occurred: ";
    print_string (Printexc.to_string e);
    print_newline ();
    exit 1

	


open Core.Std

let lang_info_header = ["language"; "architect"; "first release"]

let lang_info = [
    ["Lisp";  "John McCarthy";   "1958"];
    ["C";     "Dennis Ritchie";  "1969"];
    ["ML";    "Robin Milner";    "1973"];
    ["OCaml"; "Xavier Leroy";    "1996"];
  ]

let rev = List.fold ~init:[] ~f:(fun accum x -> x :: accum)

let max_widths header rows = 
  let lengths l = List.map ~f:String.length l in
  let f2 = List.map2_exn ~f:Int.max in
  List.fold ~init:(lengths header) ~f:(fun acc row -> f2 acc (lengths row)) rows

let render_seperator widths = 
  let peices = List.map ~f:(fun w -> String.make (w + 2) '-') widths in
  "|" ^ String.concat ~sep:"+" peices ^ "|" 

let pad s length = 
  " " ^ s ^ String.make (length - String.length s + 1) ' '

let render_row row widths = 
  let padded = List.map2_exn row widths ~f:pad in
  "|" ^ String.concat ~sep:"|" padded ^ "|" 

let render_table header rows = 
  let widths = max_widths header rows in
  String.concat ~sep:"\n" 
		(render_row header widths
		 :: render_seperator widths 
		 :: List.map ~f:(fun row -> render_row row widths) rows)
		
let () = 
  printf "%s\n" (render_table lang_info_header lang_info)


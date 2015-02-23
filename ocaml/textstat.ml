(* Text statistics *)

type stats = int * int * int * int * int array

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


let lines (l, _, _, _, _) = l
let characters (_, c, _, _, _) = c
let words (_, _, w, _, _) = w
let sentences (_, _, _, s, _) = s
let histogram (_, _, _, _, h) = print_histogram h

let stats_from_channel ch =
  let lines = ref 0 in
  let characters = ref 0 in
  let words = ref 0 in
  let sentences = ref 0 in
  let histogram = Array.make 256 0 in
  try
    while true do
      let line = input_line ch in
      lines := !lines + 1;
      characters := !characters + String.length line;
      String.iter (fun c ->
		   match c with
		   | '.' | '!' | '?' -> sentences := !sentences + 1
		   | ' ' -> words := !words + 1
		   | _ -> ()
		  )
		  line;
      String.iter (fun c -> 
		   let i = int_of_char c in
		   histogram.(i) <- histogram.(i) + 1)
		  line
    done;
    (0, 0, 0, 0, histogram)
  with
  | End_of_file -> (!lines, !characters, !words, !sentences, histogram)


let stats_from_file filename = 
  let ch = open_in filename in
  let result = stats_from_channel ch in
  close_in ch;
  result


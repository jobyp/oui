let rec channel_to_list ch =
  try 
    let line = input_line ch in
    line :: channel_to_list ch
  with End_of_file -> []

let list_to_channel ch l = 
  List.iter (fun s -> output_string ch s; output_char ch '\n') l

let () = 
  try match Sys.argv with
      | [|_; src; dest |] ->
	 let in_ch = open_in src in
	 let out_ch = open_out dest in
	 let src_lst = channel_to_list in_ch in
	 close_in in_ch;
	 let dest_lst = List.rev src_lst in
	 list_to_channel out_ch dest_lst;
	 close_out out_ch
      | _ -> 
	 print_string "Usage: tac <filename>";
	 print_newline ()
  with e -> 
    print_string "An error occurred: ";
    print_string (Printexc.to_string e);
    print_newline ();
    exit 1

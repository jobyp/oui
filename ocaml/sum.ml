open Core.Std

let rec read_and_accumulate accum =
  let line = In_channel.input_line In_channel.stdin in
  match line with
  | Some x -> read_and_accumulate (accum +. Float.of_string x)
  | None -> accum

let () =
  printf "Total: %F\n" (read_and_accumulate 0.)


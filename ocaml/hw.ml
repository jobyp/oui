open Core.Std

let range n = (* ->  [0; 1; ... ] *)
  let rec range_aux m l = 
    if m = 0 
    then 0 :: l
    else range_aux (m - 1) (m :: l) 
  in
  if n <= 0
  then []
  else range_aux (n - 1) []

let log_entry maybe_time message =
  let time = 
    match maybe_time with
    | Some x -> x
    | None -> Time.now ()
  in
  let tz = Time.Zone.local in
  Time.to_sec_string ~zone:tz time ^ " -- " ^ message

type point2d = {
    x : float;
    y : float;
  }

let magnitude { x = x_pos; y = y_pos } =
  sqrt (x_pos ** 2. +. y_pos ** 2.)

let magnitude' {x; y} = 
  sqrt (x ** 2. +. y ** 2.)


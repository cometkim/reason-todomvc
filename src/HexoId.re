type t = unit => string;

[@bs.module] external create: int => t = "hexoid/dist/index.js";

let make: t => string = t => t();

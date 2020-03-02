type t =
  | Home;

type t';

let fromUrl = (url: ReasonReactRouter.url) =>
  switch (url.path) {
  | [] => Some(Home)
  | _ => None
  };

external make: string => t' = "%identity";
external toString: t' => string = "%identity";

let home = "/"->make;

module Styles = {
  open Css;

  let title =
    style([
      position(`absolute),
      top(`px(-155)),
      width(pct(100.0)),
      fontSize(`px(100)),
      fontWeight(`num(100)),
      textAlign(`center),
      color(rgba(175, 47, 47, 0.15)),
      unsafe("text-rendering", "optimizeLegibility"),
    ]);
};

[@react.component]
let make =
  React.memo(() => {
    <h1 className=Styles.title> {React.string("todos")} </h1>
  });

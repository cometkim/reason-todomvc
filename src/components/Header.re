module Styles = {
  open Css;

  let title = style([color(rgba(176, 24, 24, 0.4)), fontSize(rem(2.4))]);
};

[@react.component]
let make =
  React.memo(() => {
    <header>
      <h1 className=Styles.title> {React.string("todomvc")} </h1>
    </header>
  });

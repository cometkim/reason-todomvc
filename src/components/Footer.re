module Styles = {
  open Css;

  let container =
    style([
      margin4(~top=`px(65), ~right=`auto, ~bottom=`zero, ~left=`auto),
      fontSize(`px(10)),
      color(`hex("bfbfbf")),
      textAlign(`center),
      textShadow(Shadow.text(~y=`px(1), `rgba((255, 255, 255, 0.5)))),
      selector("> p", [lineHeight(`em(1.0))]),
      selector(
        "& a",
        [
          color(`currentColor),
          fontWeight(`num(400)),
          textDecoration(`none),
          hover([textDecoration(`underline)]),
        ],
      ),
    ]);
};

[@react.component]
let make =
  React.memo(() => {
    <footer className=Styles.container>
      <p> {React.string("Double-click to edit a todo")} </p>
      <p>
        {React.string("Created by ")}
        <a href="https://github.com/cometkim"> {React.string("cometkim")} </a>
      </p>
      <p>
        {React.string("Part of ")}
        <a href="http://todomvc.com"> {React.string("TodoMVC")} </a>
      </p>
    </footer>
  });

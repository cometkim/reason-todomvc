module Styles = {
  open Css;

  let container = style([textAlign(`center)]);
};

[@react.component]
let make =
  React.memo(() => {
    <footer className=Styles.container>
      <p> {React.string("Double-click to edit a todo")} </p>
      <p>
        {React.string("Created by ")}
        <a href="https://github.com/cometkim" target="_blank" rel="noopener">
          {React.string("cometkim")}
        </a>
      </p>
      <p>
        {React.string("Part of ")}
        <a href="http://todomvc.com" target="_blank" rel="noopener">
          {React.string("TodoMVC")}
        </a>
      </p>
    </footer>
  });

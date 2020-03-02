module Styles = {
  open Css;

  let container = style([]);

  let paragraph = style([textAlign(center)]);
};

[@react.component]
let make =
  React.memo(() => {
    <div className=Styles.container>
      <p className=Styles.paragraph>
        {React.string("Double-click to edit a todo")}
      </p>
      <p className=Styles.paragraph>
        {React.string("Created by ")}
        <a href="https://github.com/cometkim" target="_blank" rel="noopener">
          {React.string("cometkim")}
        </a>
      </p>
      <p className=Styles.paragraph>
        {React.string("Part of ")}
        <a href="http://todomvc.com" target="_blank" rel="noopener">
          {React.string("TodoMVC")}
        </a>
      </p>
    </div>
  });
